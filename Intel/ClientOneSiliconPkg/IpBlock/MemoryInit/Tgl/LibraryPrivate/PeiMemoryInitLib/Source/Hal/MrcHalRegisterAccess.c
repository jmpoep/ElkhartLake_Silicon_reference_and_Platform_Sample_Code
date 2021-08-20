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

// Include files
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
#define ROUNDTRIP_DELAY_MAX (8)

#ifdef MRC_DEBUG_PRINT
///
/// DDR IO Debug Strings
///
const CHAR8* GsmGtDebugStrings[GsmDebugStringMax] = {
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
  "RxDqBitOffset",
  "CkeGrpPi",
  "WckGrpPi",
  "DqsOdtDelay",
  "DqsOdtDuration",
  "RxBiasCtl",
  "RxDqsAmpOffset",
  "RxDqsUnmatchedAmpOffset",
  "RxCben",
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
  "TxDqsTco",
  "CmdTxEq",
  "CtlTxEq",
  "RxVrefVttDecap",
  "RxVrefVddqDecap",
  "PanicVttDnLp",
  "VttGenStatusSelCount",
  "VttGenStatusCount",
  "RxR",
  "RxC",
  "RxTap0",
  "RxTap1",
  "RloadDqsDn",
  "DataRxD0PiCb",
  "DataSDllPiCb",
  "VccDllRxD0PiCb",
  "VccDllSDllPiCb",
  "DqsOdtCompOffset",
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
  "CompOffsetVssHiFF",
  "CompOffsetAll",
  "VsxHiClkFFOffset",
  "VsxHiCaFFOffset",
  "VsxHiCtlFFOffset",
  "CmdSlewRate",
  "ClkSlewRate",
  "ClkRon",
  "CtlSlewRate",
  "CtlRon",
  "DqScompPC",
  "CmdScompPC",
  "CtlScompPC",
  "ClkScompPC",
  "SCompCodeDq",
  "SCompCodeCmd",
  "SCompCodeCtl",
  "SCompCodeClk",
  "SCompBypassDq",
  "SCompBypassCmd",
  "SCompBypassCtl",
  "SCompBypassClk",
  "WrDSCodeUpCmd",
  "WrDSCodeUpCtl",
  "WrDSCodeUpClk",
  "WrDSCodeDnCmd",
  "WrDSCodeDnCtl",
  "WrDSCodeDnClk",
  "TcoCompCodeCmd",
  "TcoCompCodeCtl",
  "TcoCompCodeClk",
  "DqOdtVrefUp",
  "DqOdtVrefDn",
  "DqDrvVrefUp",
  "DqDrvVrefDn",
  "CmdDrvVrefUp",
  "CmdDrvVrefDn",
  "CtlDrvVrefUp",
  "CtlDrvVrefDn",
  "ClkDrvVrefUp",
  "ClkDrvVrefDn",
  "CompRcompOdtUp",
  "CompRcompOdtDn",
  "TxDqsBitDelay",
  "RxVocUnmatched",
  "RxPerBitDeskewCal",
  "TxPerBitDeskewCal",
  "CccPerBitDeskewCal",
  "EndOfPhyMarker",
  "GsmIocIoReset",
  "GsmIocWlWakeCyc",
  "GsmIocWlSleepCyclesAct",
  "GsmIocWlSleepCyclesLp",
  "GsmIocForceCmpUpdt",
  "GsmIocNoDqInterleave",
  "GsmIocScramLpMode",
  "GsmIocScramDdr4Mode",
  "GsmIocScramDdr5Mode",
  "GsmIocScramGear1",
  "GsmIocVccDllGear1",
  "GsmIocVccDllControlBypass_V",
  "GsmIocVccDllControlSelCode_V",
  "GsmIocVccDllControlTarget_V",
  "GsmIocVccDllControlOpenLoop_V",
  "GsmIocVsxHiControlSelCode_V",
  "GsmIocVsxHiControlOpenLoop_V",
  "GsmIocCccPiEn",
  "GsmIocCccPiEnOverride",
  "GsmIocDisClkGate",
  "GsmIocDisDataIdlClkGate",
  "GsmIocScramLp4Mode",
  "GsmIocScramLp5Mode",
  "GsmIocScramOvrdPeriodicToDvfsComp",
  "GsmIocLp5Wck2CkRatio",
  "GsmIocChNotPop",
  "GsmIocDisIosfSbClkGate",
  "GsmIocEccEn",
  "GsmIocDataOdtStaticDis",
  "GsmIocCompOdtStaticDis",
  "GsmIocStrobeOdtStaticDis",
  "GsmIocDataODTSingleSegEn",
  "GsmIocDllMask",
  "GsmIocDataOdtMode",
  "GsmIocDataDqOdtParkMode",
  "GsmIocCompVttOdtEn",
  "GsmIocCmdDrvVref200ohm",
  "GsmIocVttPanicCompUpMult",
  "GsmIocVttPanicCompDnMult",
  "GsmIocRxVrefMFC",
  "GsmIocVccDllRxDeskewCal",
  "GsmIocVccDllTxDeskewCal",
  "GsmIocVccDllCccDeskewCal",
  "GsmIocForceRxAmpOn",
  "GsmIocTxOn",
  "GsmIocRxDisable",
  "GsmIocSenseAmpMode",
  "GsmIocCaTrainingMode",
  "GsmIocReadLevelMode",
  "GsmIocWriteLevelMode",
  "GsmIocReadDqDqsMode",
  "GsmIocRxClkStg",
  "GsmIocDataRxBurstLen",
  "GsmIocEnDqsNRcvEn",
  "GsmIocForceOdtOn",
  "GsmIocRxPiPwrDnDis",
  "GsmIocTxPiPwrDnDis",
  "GsmIocTxDisable",
  "GsmIocCmdVrefConverge",
  "GsmIocCompClkOn",
  "GsmIocConstZTxEqEn",
  "GsmIocDisableQuickComp",
  "GsmIocSinStep",
  "GsmIocSinStepAdv",
  "GsmIocSdllSegmentDisable",
  "GsmIocRXDeskewForceOn",
  "GsmIocDllWeakLock",
  "GsmIocDllWeakLock1",
  "GsmIocTxEqDis",
  "GsmIocDqSlewDlyByPass",
  "GsmIocWlLongDelEn",
  "GsmIocCompVddqOdtEn",
  "GsmIocRptChRepClkOn",
  "GsmIocCmdAnlgEnGraceCnt",
  "GsmIocTxAnlgEnGraceCnt",
  "GsmIocTxDqFifoRdEnPerRankDelDis",
  "GsmIocInternalClocksOn",
  "GsmIocDqsMaskPulseCnt",
  "GsmIocDqsPulseCnt",
  "GsmIocDqOverrideData",
  "GsmIocDqOverrideEn",
  "GsmIocRankOverrideEn",
  "GsmIocRankOverrideVal",
  "GsmIocDataCtlGear1",
  "GsmIocDataWrPreamble",
  "GsmIocDccTrainingMode",
  "GsmIocDccTrainingDone",
  "GsmIocDccDrain",
  "GsmIocDccActiveClks",
  "GsmIocDccActiveBytes",
  "GsmIocDccDcoCompEn",
  "GsmIocDccClkTrainVal",
  "GsmIocDccDataTrainDqsVal",
  "GsmIocRxVocMode",
  "GsmIocDataTrainFeedback",
  "GsmIocDataDqsOdtParkMode",
  "GsmIocDataDqsNParkLow",
  "GsmIocRxAmpOffsetEn",
  "GsmIocBiasPMCtrl",
  "GsmIocFFCodePiOffset",
  "GsmIocFFCodeIdleOffset",
  "GsmIocFFCodeWeakOffset",
  "GsmIocFFCodeWriteOffset",
  "GsmIocFFCodeReadOffset",
  "GsmIocFFCodePBDOffset",
  "GsmIocFFCodeCCCDistOffset",
  "GsmIocDataInvertNibble",
  "GsmIocCapCancelCodeIdle",
  "GsmIocCapCancelCodePBD",
  "GsmIocCapCancelCodeWrite",
  "GsmIocCapCancelCodeRead",
  "GsmIocCapCancelCodePi",
  "GsmIocVssHiFFCodeIdle",
  "GsmIocVssHiFFCodeWrite",
  "GsmIocVssHiFFCodeRead",
  "GsmIocVssHiFFCodePBD",
  "GsmIocVssHiFFCodePi",
  "GsmIocEnableSpineGate",
  "EndOfIocMarker",
  "GsmMctRCD",
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
  "GsmMctCA2CS",
  "GsmMctCSL",
  "GsmMctCSH",
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
  "GsmMccStackedMode",
  "GsmMccStackChMap",
  "GsmMccLChannelMap",
  "GsmMccSChannelSize",
  "GsmMccStackedChHash",
  "GsmMccChWidth",
  "GsmMccHalfCachelineMode",
  "GsmMccLDimmSize",
  "GsmMccLDimmDramWidth",
  "GsmMccLDimmRankCnt",
  "GsmMccSDimmSize",
  "GsmMccSDimmDramWidth",
  "GsmMccSDimmRankCnt",
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
  "GsmMccPbrDisOnHot",
  "GsmMccOdtOverride",
  "GsmMccOdtOn",
  "GsmMccMprTrainDdrOn",
  "GsmMccCkeOverride",
  "GsmMccCkeOn",
  "EndOfMccMarker",
  "GsmCmiHashMask",
  "GsmCmiLsbMaskBit",
  "GsmCmiHashMode",
  "GsmCmiStackedMode",
  "GsmCmiStackMsMap",
  "GsmCmiLMadSliceMap",
  "GsmCmiSMadSliceSize",
  "GsmCmiStackedMsHash",
  "EndOfCmiMarker",
  "GsmComplexRcvEn",
  "GsmComplexRxBias",
  "GsmGtMax"
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
  UINT32  Encoding;
  UINT32  Vdd;

  Outputs = &MrcData->Outputs;

  Vdd = Outputs->VccddqVoltage;

  // Register moves in steps of VDD/382.  The encoding would be:
  //   Step = Vdd / 382
  //   Encoding = Vref / Step
  //   Encoding = Vref / Vdd / 382
  // To avoid loss of precision, multiply Vref by the step size, then DIVIDEROUND with VDD
  Encoding = Vref * 382;
  Encoding = UDIVIDEROUND (Encoding, Vdd);

  MRC_DEBUG_ASSERT (VrefEncoded != 0, &MrcData->Outputs.Debug, "%s", gNullPtrErrStr);
  *VrefEncoded = Encoding;
}

/**
  This function is used to translate between MRC Offsets to CR functionality.
  CR is encoded in Sign:Magnitude which creates a non-monotonic response in SenseAmp Vref levels
  when sweeping from 0 - 31.

  @param[in]  SotOffset - Current offset.
  @param[out] Value     - Pointer to return variable to store translated value.
  @param[in]  CrIdx     - TRUE means SotOffset is from the CR encoding.  FALSE means SotOffset is from the MRC encoding.
  @param[in]  Dqs       - Selector on the translation for either Dqs (TRUE) or DQ (FALSE).

  @retval - MrcStatus: mrcFail if inputs are invalid, otherwise mrcSuccess.
**/
MrcStatus
MrcTranslateSotOffset (
  IN  INT64   SotOffset,
  OUT INT64   *Value,
  IN  BOOLEAN CrIdx,
  IN  BOOLEAN Dqs
  )
{
  MrcStatus Status;
  INT64 Result;

  Status = mrcSuccess;
  Result = -1;

  if (CrIdx) {
    if ((SotOffset > 31) || (SotOffset < 0)) {
      Status = mrcFail;
    } else if (SotOffset > 15) {
      // CR Value | HW Value | MRC Idx | Group
      // 16 : 31  |  0 : -15 | 15 :  0 |  DQ
      // 17 : 31  | 15 :  1  | 30 : 16 |  DQS
      //    16    |    0     |    15   |  DQS
      if (Dqs) {
        if (SotOffset == 16) {
          Result = 15;
        } else {
          Result = 31 + 16 - SotOffset;
        }
      } else {
        Result = (31 - SotOffset);
      }
    } else {
      // CR Value | HW Value | MRC Idx | Group
      // 15 :  0  |  15 :  0 | 30 : 15 |  DQ
      // 15 :  0  | -15 :  0 |  0 : 15 |  DQS
      Result = 15;
      if (Dqs) {
        Result -= SotOffset;
      } else {
        Result += SotOffset;
      }
    }
  } else {
    if ((SotOffset < 0) || (SotOffset > 30)) {
      Status = mrcFail;
    } else if (SotOffset > 15) {
      // CR Value | HW Value | MRC Idx | Group
      //  1 : 15  |  1 : 15  | 16 : 30 |  DQ
      // 31 : 17  |  1 : 15  | 16 : 30 |  DQS
      if (Dqs) {
        Result = (31 + 16 - SotOffset);
      } else {
        Result = (SotOffset - 15);
      }
    } else {
      // CR Value | HW Value | MRC Idx | Group
      // 16 : 31  |  0 : -15 | 15 : 0  |  DQ
      //  0 : 15  |  0 : -15 | 15 : 0  |  DQS
      Result = (Dqs) ? 15 : 31;
      Result -= SotOffset;
    }
  }

  if (Value != NULL) {
    *Value = Result;
  } else {
    Status = mrcWrongInputParameter;
  }

  return Status;
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
  MrcInput  *Inputs;
  BOOLEAN   IsSupported;

  Inputs      = &MrcData->Inputs;
  IsSupported = TRUE;

  switch (Group) {
    case RecEnDelay:
    case RxDqsPDelay:
    case RxDqsNDelay:
    case RxVref:
    case RxVoc:
    case RxVocUnmatched:
    case RxEq:
    case RxDqBitDelay:
    case RxDqBitOffset:
    case RxRankMuxDelay:
    case TxDqsDelay:
    case TxDqDelay:
    case TxEq:
    case CmdTxEq:
    case CtlTxEq:
    case RxVrefVttDecap:
    case RxVrefVddqDecap:
    case PanicVttDnLp:
    case VttGenStatusSelCount:
    case VttGenStatusCount:
    case DqsOdtCompOffset:
    case TxRankMuxDelay:
    case TxDqsRankMuxDelay:
    case TxDqBitDelay:
    case TxDqsBitDelay:
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
    case DqsOdtDelay:
    case DqsOdtDuration:
    case RxDqsAmpOffset:
    case RxDqsUnmatchedAmpOffset:
    case CmdVref:
    case CmdGrpPi:
    case CtlGrpPi:
    case ClkGrpPi:
    case CkeGrpPi:
    case WckGrpPi:
    case TxSlewRate:
    case DqScompPC:
    case CmdSlewRate:
    case CmdScompPC:
    case CtlSlewRate:
    case CtlScompPC:
    case ClkSlewRate:
    case ClkScompPC:
    case SCompCodeDq:
    case SCompCodeCmd:
    case SCompCodeCtl:
    case SCompCodeClk:
    case SCompBypassDq:
    case SCompBypassCmd:
    case SCompBypassCtl:
    case SCompBypassClk:
    case TxRonUp:
    case WrDSCodeUpCmd:
    case WrDSCodeUpCtl:
    case WrDSCodeUpClk:
    case TxRonDn:
    case WrDSCodeDnCmd:
    case WrDSCodeDnCtl:
    case WrDSCodeDnClk:
    case TxTco:
    case TxDqsTco:
    case TcoCompCodeCmd:
    case TcoCompCodeCtl:
    case TcoCompCodeClk:
    case CompRcompOdtUp:
    case CompRcompOdtDn:
    case ClkRCompDrvDownOffset:
    case ClkRCompDrvUpOffset:
//    case ClkCompOnTheFlyUpdtEn:
    case ClkSCompOffset:
    case CtlSCompOffset:
    case CtlRCompDrvUpOffset:
    case CtlRCompDrvDownOffset:
    case CkeRCompDrvDownOffset:
    case CkeRCompDrvUpOffset:
    case VsxHiClkFFOffset:
    case VsxHiCaFFOffset:
    case VsxHiCtlFFOffset:
    case CompOffsetVssHiFF:
    case CkeSCompOffset:
    case CmdSCompOffset:
    case CmdRCompDrvUpOffset:
    case CmdRCompDrvDownOffset:
    case RxPerBitDeskewCal:
    case TxPerBitDeskewCal:
    case CccPerBitDeskewCal:
    case GsmIocCccPiEn:
    case GsmIocCccPiEnOverride:
    case GsmIocDataOdtStaticDis:
    case GsmIocCompOdtStaticDis:
    case GsmIocStrobeOdtStaticDis:
    case GsmIocDataODTSingleSegEn:
    case RxR:
    case RxC:
    case RxTap0:
    case RxTap1:
    case RloadDqsDn:
    case RxCben:
    case RxBiasCtl:
    case DataRxD0PiCb:
    case DataSDllPiCb:
    case VccDllRxD0PiCb:
    case VccDllSDllPiCb:
    case GsmIocDqsMaskPulseCnt:
    case GsmIocDqsPulseCnt:
    case GsmIocDqOverrideData:
    case GsmIocDqOverrideEn:
    case GsmIocRankOverrideEn:
    case GsmIocRankOverrideVal:
    case GsmIocDataCtlGear1:
    case GsmIocDataWrPreamble:
    case GsmIocDccTrainingMode:
    case GsmIocDccTrainingDone:
    case GsmIocDccDrain:
    case GsmIocDccActiveClks:
    case GsmIocDccActiveBytes:
    case GsmIocDccDcoCompEn:
    case GsmIocDccClkTrainVal:
    case GsmIocDccDataTrainDqsVal:
    case GsmIocSdllSegmentDisable:
    case GsmIocRXDeskewForceOn:
    case GsmIocDllWeakLock:
    case GsmIocDllWeakLock1:
    case GsmIocRxClkStg:
    case GsmIocDataRxBurstLen:
    case GsmIocEnDqsNRcvEn:
//    case GsmIocLeakerComp:
//    case GsmIocLongWrPreambleLp4:
//    case GsmIocRxPathBiasRcomp:
    case GsmIocVccDllRxDeskewCal:
    case GsmIocVccDllTxDeskewCal:
    case GsmIocVccDllCccDeskewCal:
    case GsmIocForceRxAmpOn:
//    case GsmIocRxTypeSelect:
    case GsmIocCompVddqOdtEn:
    case GsmIocCompVttOdtEn:
    case GsmIocVttPanicCompUpMult:
    case GsmIocVttPanicCompDnMult:
    case GsmIocRxVrefMFC:
//    case GsmIocVrefPwrDnEn:
    case GsmIocDqSlewDlyByPass:
    case GsmIocWlLongDelEn:
    case GsmIocBiasPMCtrl:
    case GsmIocDataOdtMode:
    case GsmIocDataDqOdtParkMode:
    case GsmIocTxEqDis:
    case GsmIocTxOn:
    case GsmIocRxDisable:
    case GsmIocSenseAmpMode:
    case GsmIocCaTrainingMode:
    case GsmIocReadLevelMode:
    case GsmIocWriteLevelMode:
    case GsmIocReadDqDqsMode:
    case GsmIocForceOdtOn:
    case GsmIocRxPiPwrDnDis:
    case GsmIocTxPiPwrDnDis:
    case GsmIocInternalClocksOn:
    case GsmIocDataDqsOdtParkMode:
    case GsmIocDataDqsNParkLow:
    case GsmIocTxDisable:
    case GsmIocIoReset:
    case GsmIocNoDqInterleave:
    case GsmIocScramLpMode:
    case GsmIocScramDdr4Mode:
    case GsmIocScramDdr5Mode:
    case GsmIocScramGear1:
    case GsmIocVccDllGear1:
    case GsmIocVccDllControlBypass_V:
    case GsmIocVccDllControlSelCode_V:
    case GsmIocVccDllControlTarget_V:
    case GsmIocVccDllControlOpenLoop_V:
    case GsmIocVsxHiControlSelCode_V:
    case GsmIocVsxHiControlOpenLoop_V:
    case GsmIocScramLp4Mode:
    case GsmIocScramLp5Mode:
    case GsmIocScramOvrdPeriodicToDvfsComp:
    case GsmIocLp5Wck2CkRatio:
    case GsmIocChNotPop:
    case GsmIocDisIosfSbClkGate:
    case GsmIocWlWakeCyc:
    case GsmIocWlSleepCyclesAct:
    case GsmIocWlSleepCyclesLp:
    case GsmIocDisDataIdlClkGate:
    case GsmIocDllMask:
//    case GsmIocWlLatency:
    case GsmIocConstZTxEqEn:
    case GsmIocCompClkOn:
    case GsmIocDisableQuickComp:
    case GsmIocSinStep:
    case GsmIocSinStepAdv:
    case GsmIocForceCmpUpdt:
    case GsmIocRptChRepClkOn:
    case GsmIocCmdAnlgEnGraceCnt:
    case GsmIocTxAnlgEnGraceCnt:
    case GsmIocTxDqFifoRdEnPerRankDelDis:
    case GsmIocRxVocMode:
    case GsmIocDataTrainFeedback:
    case GsmIocRxAmpOffsetEn:
    case GsmIocFFCodePiOffset:
    case GsmIocFFCodeIdleOffset:
    case GsmIocFFCodeWeakOffset:
    case GsmIocFFCodeWriteOffset:
    case GsmIocFFCodeReadOffset:
    case GsmIocFFCodePBDOffset:
    case GsmIocFFCodeCCCDistOffset:
    case GsmIocDataInvertNibble:
    case GsmIocCapCancelCodeIdle:
    case GsmIocCapCancelCodePBD:
    case GsmIocCapCancelCodeWrite:
    case GsmIocCapCancelCodeRead:
    case GsmIocCapCancelCodePi:
    case GsmIocVssHiFFCodeIdle:
    case GsmIocVssHiFFCodeWrite:
    case GsmIocVssHiFFCodeRead:
    case GsmIocVssHiFFCodePBD:
    case GsmIocVssHiFFCodePi:
    case GsmIocEnableSpineGate:
    case DqDrvVrefUp:
    case DqDrvVrefDn:
    case DqOdtVrefUp:
    case DqOdtVrefDn:
    case CmdDrvVrefUp:
    case CmdDrvVrefDn:
    case CtlDrvVrefUp:
    case CtlDrvVrefDn:
    case ClkDrvVrefUp:
    case ClkDrvVrefDn:
    case GsmMctRCD:
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
    case GsmMctCA2CS:
    case GsmMctCSL:
    case GsmMctCSH:
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
    case GsmMccEnhancedInterleave:
    case GsmMccEccMode:
    case GsmMccAddrDecodeDdrType:
    case GsmMccLChannelMap:
    case GsmMccSChannelSize:
    case GsmMccChWidth:
    case GsmMccHalfCachelineMode:
    case GsmMccLDimmSize:
    case GsmMccLDimmDramWidth:
    case GsmMccLDimmRankCnt:
    case GsmMccSDimmSize:
    case GsmMccSDimmDramWidth:
    case GsmMccSDimmRankCnt:
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
    case GsmMccBlockXarb:
    case GsmMccResetOnCmd:
    case GsmMccResetDelay:
    case GsmMccDramType:
    case GsmMccCmdStretch:
    case GsmMccCmdGapRatio:
    case GsmMccAddrMirror:
    case GsmMccCmdTriStateDis:
    case GsmMccCmdTriStateDisTrain:
    case GsmMccFreqPoint: // This aliases with ddr_probless_low_frequency.
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
    case GsmMctRFCpb:
    case GsmMccDisableCkTristate:
    case GsmMccPbrDis:
    case GsmMccPbrDisOnHot:
    case GsmMccOdtOverride:
    case GsmMccOdtOn:
    case GsmMccMprTrainDdrOn:
    case GsmMccCkeOverride:
    case GsmMccCkeOn:
    case GsmCmiHashMask:
    case GsmCmiLsbMaskBit:
    case GsmCmiHashMode:
    case GsmCmiStackedMode:
    case GsmCmiStackMsMap:
    case GsmCmiLMadSliceMap:
    case GsmCmiSMadSliceSize:
    case GsmCmiStackedMsHash:
      break;
    case GsmIocEccEn:
      if (Inputs->UlxUlt) {
        // DDRSCRAM_CR_DDRMISCCONTROL0_STRUCT.ECCPresent only exists on TGL P0
        IsSupported = FALSE;
      }
      break;
    case GsmIocCmdVrefConverge:
      if (Inputs->DtHalo) {
        // TODO: Need to handle 2 new instances of caSlowBW on TGL P0
        IsSupported = FALSE;
      }
      break;
    case GsmMccRankInterleave:
    case GsmMccStackedMode:
    case GsmMccStackChMap:
    case GsmMccStackedChHash:
      // These Get\Sets are only supported on TGL A0
      if (Inputs->A0) {
        break;
      } else {
        IsSupported = FALSE;
      }
      break;
    default:
      IsSupported = FALSE;
      break;
  }

  if (!IsSupported) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_ERROR,
      "%s GetSet Group %s(%d) is not supported!\n",
      gErrString,
      GsmGtDebugStrings[Group],
      Group
      );
    return mrcWrongInputParameter;
  }
  return mrcSuccess;
}
#endif

/**
  This function is used to determine if the GSM_GT passed in is a complex parameter.

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
      case GsmIocSenseAmpMode:
      case GsmIocReadDqDqsMode:
      case GsmIocCaTrainingMode:
      case GsmIocWriteLevelMode:
      case GsmIocReadLevelMode:
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
      case TxDqsDelay:
      case TxDqDelay:
      case ClkGrpPi:
      case TxDqsOffset:
      case RxCben:
        RetVal = TRUE;
        break;

      case GsmIocWlSleepCyclesAct:
        if (MrcData->Inputs.UlxUlt) {
          RetVal = TRUE;
        }
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

/*
  This function is used to update other Phy register in the channel based on DDR type.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      Dimm        - DIMM Number within the DDR Channel (0-based). Ignored as Rank is rank number in the channel.
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Strobe      - If Group is a CMD/CTL/CLK Index type, this is the index for that signal.  Otherwise, Dqs data group within the rank (0-based).
  @param[in]      Bit         - Bit index within the data group (0-based).
  @param[in]      FreqIndex   - Index supporting multiple operating frequencies.
  @param[in]      Level       - DDRIO level to access.
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval Nothing.
**/
void
MrcGetSetUpdatePhyChannels (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Socket,
  IN      UINT32        const   Controller,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Dimm,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      UINT32        const   FreqIndex,
  IN      GSM_LT        const   Level,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN      INT64         *const  Value
  )
{
  UINT8             Ddr4SideEffect[3] = { 1, 2, 3 };
  UINT8             Ddr5SideEffect[1] = { 1 };
  UINT8             SideEffectLoop;
  UINT32            SideEffectController;
  UINT32            SideEffectChannel;
  MrcOutput        *Outputs;
  MrcControllerOut *ControllerOut;

  Outputs = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[Controller];

  switch (Group) {
    // MCMISCS_READCFGCHx_REG
    case RxIoTclDelay:
    case RxFifoRdEnTclDelay:
    case RxDqDataValidDclkDelay:
    case RxDqDataValidQclkDelay:
      // MCMISCS_WRITECFGCHx_REG
    case TxDqFifoWrEnTcwlDelay:
    case TxDqFifoRdEnTcwlDelay:
    case GsmIocRptChRepClkOn:
    case GsmIocCmdAnlgEnGraceCnt:
    case GsmIocTxAnlgEnGraceCnt:
    case GsmIocTxDqFifoRdEnPerRankDelDis:
      // MCMISCS_READCFGCHxy_REG
    case RxFlybyDelay:
      // MCMISCS_WRITECFGCHxy_REG
    case TxDqFifoRdEnFlybyDelay:
      // MCMISCS_RXDQFIFORDENCHxy_REG
    case RxFifoRdEnFlybyDelay:
    case SCompBypassCmd:
    case SCompBypassCtl:
    case SCompBypassClk:
    case TcoCompCodeCmd:
    case TcoCompCodeCtl:
    case TcoCompCodeClk:
    case CmdTxEq:
    case CtlTxEq:
      switch (Outputs->DdrType) {
        case MRC_DDR_TYPE_DDR4:
          for (SideEffectLoop = 0; SideEffectLoop < sizeof(Ddr4SideEffect); SideEffectLoop++) {
            SideEffectController = 0;
            SideEffectChannel = Controller * MAX_CHANNEL;
            SideEffectChannel += Channel * (MAX_CHANNEL / ControllerOut->ChannelCount) + Ddr4SideEffect[SideEffectLoop];
            GetSet (MrcData, Socket, SideEffectController, SideEffectChannel, Dimm, Rank, Strobe, Bit, FreqIndex, Level, Group, Mode, Value);
          }
          break;
        case MRC_DDR_TYPE_DDR5:
          for (SideEffectLoop = 0; SideEffectLoop < sizeof(Ddr5SideEffect); SideEffectLoop++) {
            SideEffectController = 0;
            SideEffectChannel = Controller * MAX_CHANNEL;
            SideEffectChannel += Channel * (MAX_CHANNEL / ControllerOut->ChannelCount) + Ddr5SideEffect[SideEffectLoop];
            GetSet (MrcData, Socket, SideEffectController, SideEffectChannel, Dimm, Rank, Strobe, Bit, FreqIndex, Level, Group, Mode, Value);
          }
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

/*
  This function perform any side effect action required from the Group that was just set.
  It will inherit the same Mode parameter so it passed it on to the actions executed.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
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

  @retval Nothing.
**/
void
MrcGetSetSideEffect (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Socket,
  IN      UINT32        const   Controller,
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
  IN      INT64         *const  Value
  )
{
  MrcIntOutput  *MrcIntData;
  //@todo BOOLEAN   Flush;
  INT64     TxDqsValue;
  GSM_GT    WriteGroup;
  INT64     GetSetVal;
  UINT32    LocalRank;
  UINT32    LocalModeWrite;
  UINT32    LocalModeRead;
  UINT32    SearchVal;
  BOOLEAN   Gear2;

  Gear2 = MrcData->Outputs.Gear2;

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
  if (Group == GsmIocWlSleepCyclesAct) {
    MrcGetSet (MrcData, Socket, Controller, Channel, Dimm, 0, Strobe, Bit, FreqIndex, Level, GsmIocWlSleepCyclesLp, Mode, Value);
  }

  if ((Group == RecEnDelay) || (Group == TxDqsDelay) || (Group == TxDqDelay)) {
    // Find the smallest RecEnDelay/TxDqsDelay/TxDqDelay in the Byte/Channel and update the new [Rx,Tx]RankMuxDelay
    if (Group == RecEnDelay) {
      WriteGroup = RxRankMuxDelay;
    } else if (Group == TxDqDelay) {
      WriteGroup = TxRankMuxDelay;
    } else { // TxDqsDelay
      WriteGroup = TxDqsRankMuxDelay;
    }
    SearchVal = MRC_UINT32_MAX;
    for (LocalRank = 0; LocalRank < MAX_RANK_IN_CHANNEL; LocalRank++) {
      if (MrcRankExist (MrcData, Controller, Channel, LocalRank)) {
        MrcGetSet (MrcData, Socket, Controller, Channel, Dimm, LocalRank, Strobe, Bit, FreqIndex, Level, Group, LocalModeRead, &GetSetVal);
        SearchVal = MIN (SearchVal, (UINT32) GetSetVal);
      }
    }
    // Align to a QCLK (Gear1) or DCLK (Gear2)
    // Shift by an extra +1 and then multiple by 2 to round down to the nearest even number
    SearchVal = SearchVal >> (6 + Gear2 + 1);
    GetSetVal = SearchVal * 2;
    MrcGetSet (MrcData, Socket, Controller, Channel, Dimm, 0, Strobe, Bit, FreqIndex, Level, WriteGroup, LocalModeWrite, &GetSetVal);
  }

  if (Group == RxCben) {
    MrcGetSetChStrb(MrcData, Controller, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, DataRxD0PiCb, LocalModeWrite, Value);
    MrcGetSetChStrb(MrcData, Controller, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, DataSDllPiCb, LocalModeWrite, Value);
    MrcGetSetNoScope(MrcData, VccDllRxD0PiCb, LocalModeWrite, Value);
    MrcGetSetNoScope(MrcData, VccDllSDllPiCb, LocalModeWrite, Value);
  }

  // Side Effect for DCC
  if (((Mode & GSM_READ_ONLY) == 0) && ((Group == ClkGrpPi) || (Group == TxDqsDelay) || (Group == TxDqsOffset))) {
    // Only when writing to registers related to ClkGrpPi and TxDqsDelay
    MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

    // Flush only when GSM_CACHE_ONLY is not set
    //@todo Flush = ((Mode & GSM_CACHE_ONLY) == 0);

    if (MrcIntData->ClkDccInit && (Group == ClkGrpPi)) {
      // Update using CLK DCC LUT
      GetSetVal = (UINT32) *Value % MAX_DCC_CLOCK_PI;
      //@todo MrcDccUpdate (MrcData, Channel, Rank, Strobe, GsmIocDccClkTrainVal, &GetSetVal, Flush);
    }

    if (MrcIntData->DqsDccInit && ((Group == TxDqsDelay) || (Group == TxDqsOffset))) {
      // Determine the total TxDqs value w/ TxDqsDelay and TxDqsOffset (Read the other set, unless the write is w/ GSM_WRITE_OFFSET)
      MrcGetSet (MrcData, Socket, Controller, Channel, Dimm, Rank, Strobe, Bit, FreqIndex, Level, (Group == TxDqsDelay) ? TxDqsOffset : TxDqsDelay, LocalModeRead, &TxDqsValue);
      if (Mode & GSM_WRITE_OFFSET) {
        MrcGetSet (MrcData, Socket, Controller, Channel, Dimm, Rank, Strobe, Bit, FreqIndex, Level, Group, LocalModeRead, &GetSetVal);
        TxDqsValue += GetSetVal;
      } else {
        TxDqsValue += *Value;
      }
      // Update using DQS DCC LUT
      TxDqsValue = (UINT32) TxDqsValue % MAX_DCC_TX_DQS_DQ_PI;
      //@todo MrcDccUpdate (MrcData, Channel, Rank, Strobe, GsmIocDccDataTrainDqsVal, &TxDqsValue, Flush);
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
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
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
  IN      UINT32        const   Controller,
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
  MrcInput  *Inputs;
  MrcStatus Status;
  INT64     GetSetVal;
  UINT32    LocalModeWrite;

  Inputs = &MrcData->Inputs;
  // Write based on original mode. Clear offset write flag
  LocalModeWrite = Mode;
  LocalModeWrite &= ~GSM_WRITE_OFFSET;
  if ((Mode & GSM_UPDATE_CACHE) == 0) {
    // If original mode is not using the cache, the side effect write should not use it as well
    LocalModeWrite |= GSM_READ_CSR;
  }

  if (Inputs->A0 && ((Group == GsmIocSenseAmpMode) || (Group == GsmIocReadDqDqsMode) || (Group == GsmIocCaTrainingMode) || (Group == GsmIocWriteLevelMode) || (Group == GsmIocReadLevelMode))) {
    GetSetVal = (*Value) ? 1 : 0;
    MrcGetSetChStrb (MrcData, Controller, Channel, Strobe, GsmIocInternalClocksOn, LocalModeWrite, &GetSetVal);
  }

  Status  = mrcSuccess;
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
  return MrcGetSetDdrIoGroupChannel (MrcData, 0, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  Only one setting for the whole controller, so Channel, Rank, Strobe, and Bit index is dropped.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetMc (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Controller,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSet (
          MrcData,
          MRC_IGNORE_ARG,
          Controller,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          DdrLevel,
          Group,
          Mode,
          Value
          );
}

/**
  Top level function used to interact with SOC.
  This function is used to set parameters that do not have any specificity to them.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetNoScope (
  IN      MrcParameters *const  MrcData,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSet (
          MrcData,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          DdrLevel,
          Group,
          Mode,
          Value
          );
}

/**
  Top level function used to interact with SOC.
  This function ignores unused parameters in Core MRC to reduce code space.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based)
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetMcCh (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Controller,
  IN      UINT32        const   Channel,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSet (
          MrcData,
          MRC_IGNORE_ARG,
          Controller,
          Channel,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          DdrLevel,
          Group,
          Mode,
          Value
          );
}

/**
  Top level function used to interact with SOC.
  This function ignores unused parameters in Core MRC to reduce code space.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      Rank        - Rank within the DDR Channel (0-based).
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetMcChRnk (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Controller,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSet (
          MrcData,
          MRC_IGNORE_ARG,
          Controller,
          Channel,
          MRC_IGNORE_ARG,
          Rank,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          DdrLevel,
          Group,
          Mode,
          Value
          );
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
  Top level function used to interact with SOC.
  This function ignores unused parameters in Core MRC to reduce code space.
  This function is used to access indexed Command/Control/Clock groups.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      Rank        - Rank within the DDR Channel (0-based).
  @param[in]      Index       - Group index to Get/Set.
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetCcc (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Controller,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Index,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSet (
          MrcData,
          MRC_IGNORE_ARG,
          Controller,
          Channel,
          MRC_IGNORE_ARG,
          Rank,
          Index,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          DdrLevel,
          Group,
          Mode,
          Value
          );
}

/**
  Top level function used to interact with SOC.
  This function ignores unused parameters in Core MRC to reduce code space.
  This function is used to access DDRVCCDLL0 vs DDRVCCDLL1 register offsets.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Index       - Group index to Get/Set.
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetVccDll (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Index,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSet (
          MrcData,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          Index,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          DdrLevel,
          Group,
          Mode,
          Value
          );
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
  Top level function used to interact with SOC.
  This function ignores unused parameters in Core MRC to reduce code space.
  This function is for those registers that are only per Strobe per Channel granularity.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      Strobe      - Dqs data group within the rank (0-based).
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetChStrb (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Controller,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Strobe,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSet (
          MrcData,
          MRC_IGNORE_ARG,
          Controller,
          Channel,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          Strobe,
          MRC_IGNORE_ARG,
          MRC_IGNORE_ARG,
          DdrLevel,
          Group,
          Mode,
          Value
          );
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
  Top level function used to interact with SOC.
  This function ignores unused parameters in Core MRC to reduce code space.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Strobe      - Dqs data group within the rank (0-based).
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetStrobe (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Controller,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSet (
          MrcData,
          MRC_IGNORE_ARG,
          Controller,
          Channel,
          MRC_IGNORE_ARG,
          Rank,
          Strobe,
          MRC_IGNORE_ARG,
          0,
          DdrLevel,
          Group,
          Mode,
          Value
          );
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
  Top level function used to interact with SOC.
  This function ignores unused parameters in Core MRC to reduce code space.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
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
MrcGetSetBit (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Controller,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSet (
          MrcData,
          MRC_IGNORE_ARG,
          Controller,
          Channel,
          MRC_IGNORE_ARG,
          Rank,
          Strobe,
          Bit,
          MRC_IGNORE_ARG,
          DdrLevel,
          Group,
          Mode,
          Value
          );
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
  Converting controller, channel, rank, strobe number from System to IP register architecture.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Strobe      - Dqs data group within the rank or the command group (0-based).
  @param[in]      Group       - DDRIO group to access.

  @retval MrcStatus
**/
MrcStatus
MrcTranslateSystemToIp (
  IN      MrcParameters *const  MrcData,
  IN OUT  UINT32        *const  Controller,
  IN OUT  UINT32        *const  Channel,
  IN OUT  UINT32        *const  Rank,
  IN OUT  UINT32        *const  Strobe,
  IN      GSM_GT        const   Group
  )
{
  MrcOutput   *Outputs;
  MrcStatus   Status;
  UINT32      TransController;
  UINT32      TransChannel;
  UINT32      TransRank;
  UINT32      TransStrobe;
  MrcDdrType  DdrType;

  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;
  Status  = mrcSuccess;

  // Initialize the translated variables with the input. This gives us a code optimization
  // where we don't have to assign in every Group that doesn't use that scope.
  TransController = *Controller;
  TransChannel = *Channel;
  TransRank = *Rank;
  TransStrobe = *Strobe;

  switch (Group) {
    // MCMISCS_READCFGCHx_REG
    case RxIoTclDelay:
    case RxFifoRdEnTclDelay:
    case RxDqDataValidDclkDelay:
    case RxDqDataValidQclkDelay:
    // MCMISCS_WRITECFGCHx_REG
    case TxDqFifoWrEnTcwlDelay:
    case TxDqFifoRdEnTcwlDelay:
    case GsmIocRptChRepClkOn:
    case GsmIocCmdAnlgEnGraceCnt:
    case GsmIocTxAnlgEnGraceCnt:
    case GsmIocTxDqFifoRdEnPerRankDelDis:
    // MCMISCS_READCFGCHxy_REG
    case RxFlybyDelay:
    // MCMISCS_WRITECFGCHxy_REG
    case TxDqFifoRdEnFlybyDelay:
    // MCMISCS_RXDQFIFORDENCHxy_REG
    case RxFifoRdEnFlybyDelay:
    // CCC_CR_xxx_REG
    case SCompBypassCmd:
    case SCompBypassCtl:
    case SCompBypassClk:
    case CccPerBitDeskewCal:
    case CmdTxEq:
    case CtlTxEq:
    case GsmIocCccPiEn:
    case GsmIocCccPiEnOverride:
      TransChannel = (*Controller * MAX_CHANNEL);
      TransChannel += (*Channel * (MAX_CHANNEL / Outputs->MaxChannels));
      break;

    // CCC_CR_DDRCRCCCPIxxx_REG
    case CtlGrpPi:
    case ClkGrpPi:
    case CkeGrpPi:
    case CmdGrpPi:
    case WckGrpPi:
      if (DdrType == MRC_DDR_TYPE_DDR4) {
        // Controller 0 starts on CH0CCC
        // Controller 1 starts on CH4CCC
        TransChannel = (*Controller * 4);
        if (Group == CtlGrpPi) {
          // Ctrl0 - CH1CCC, Ctrl1 - CH5CCC
          TransChannel += 1;
        } else if (Group == CkeGrpPi) {
          // Ctrl0 - CH2CCC, Ctrl1 - CH6CCC
          TransChannel += 2;
        } else if (Group == ClkGrpPi) {
          // Ctrl0.R0 - CH0CCC Ctrl0.R1 - CH3CCC
          // Ctrl0.R0 - CH4CCC Ctrl0.R1 - CH7CCC
          TransChannel += (*Rank * 3);
        } else {
          // CmdGrpPi CCC Mapping
          // PiGroup  | 0 1 2 3
          // ---------|---------
          // Ctrl 0   | 0 1 2 3
          // Ctrl 1   | 4 5 6 7
          TransChannel += *Strobe;
        }
        break;
      }
      // Fall through for other DDR types
      TransChannel = (*Controller * MAX_CHANNEL);
      TransChannel += (*Channel * (MAX_CHANNEL / Outputs->MaxChannels));
      break;

    // DDRDATAxCHy_REG
    case GsmIocDqsMaskPulseCnt:
    case GsmIocDqsPulseCnt:
    case GsmIocDqOverrideData:
    case GsmIocDqOverrideEn:
    case GsmIocReadDqDqsMode:
    case GsmIocSenseAmpMode:
    case GsmIocCaTrainingMode:
    case GsmIocDataTrainFeedback:
    case GsmIocRxAmpOffsetEn:
    case GsmIocFFCodePiOffset:
    case GsmIocFFCodeIdleOffset:
    case GsmIocFFCodeWeakOffset:
    case GsmIocFFCodeWriteOffset:
    case GsmIocFFCodeReadOffset:
    case GsmIocFFCodePBDOffset:
    case GsmIocFFCodeCCCDistOffset:
    case GsmIocDataInvertNibble:
    case GsmIocWriteLevelMode:
    case GsmIocReadLevelMode:
    case GsmIocForceRxAmpOn:
    case GsmIocForceOdtOn:
    case GsmIocDataOdtStaticDis:
    case GsmIocTxPiPwrDnDis:
    case GsmIocTxDisable:
    case GsmIocInternalClocksOn:
    case GsmIocDataDqsNParkLow:
    case GsmIocTxOn:
    case GsmIocRxDisable:
    case GsmIocWlLongDelEn:
    case GsmIocBiasPMCtrl:
    case GsmIocDataOdtMode:
    case GsmIocDataDqsOdtParkMode:
    case GsmIocDataDqOdtParkMode:
    case GsmIocCompVddqOdtEn:
    case GsmIocSdllSegmentDisable:
    case GsmIocRXDeskewForceOn:
    case GsmIocRankOverrideEn:
    case GsmIocRankOverrideVal:
    case GsmIocDataCtlGear1:
    case GsmIocDataWrPreamble:
    case GsmIocDqSlewDlyByPass:
    case GsmIocRxVrefMFC:
    case GsmIocTxEqDis:
    case GsmIocConstZTxEqEn:
    case GsmIocRxClkStg:
    case GsmIocDataRxBurstLen:
    case GsmIocEnDqsNRcvEn:
    case GsmIocRxVocMode:
    case GsmIocDataODTSingleSegEn:
    case GsmIocStrobeOdtStaticDis:
    case RxDqBitDelay:
    case RxDqBitOffset:
    case TxDqBitDelay:
    case TxDqsBitDelay:
    case RxVoc:
    case RxVocUnmatched:
    case RxDqsAmpOffset:
    case RxDqsUnmatchedAmpOffset:
    case RxVref:
    case CmdVref:
    case GsmIocCmdVrefConverge:
    case RecEnDelay:
    case RxDqsPDelay:
    case RxDqsNDelay:
    case RxEq:
    case RxPerBitDeskewCal:
    case TxPerBitDeskewCal:
    case SenseAmpDelay:
    case SenseAmpDuration:
    case McOdtDelay:
    case McOdtDuration:
    case DqsOdtDelay:
    case DqsOdtDuration:
    case RxRankMuxDelay:
    case TxEq:
    case TxDqsDelay:
    case TxDqDelay:
    case SCompBypassDq:
    case RecEnOffset:
    case RxDqsOffset:
    case RxVrefOffset:
    case TxDqsOffset:
    case TxDqOffset:
    case CompOffsetAll:
    case TxTco:
    case TxDqsTco:
    case RxTap0:
    case RxTap1:
    case RxC:
    case RxR:
    case RxVrefVttDecap:
    case RxVrefVddqDecap:
    case DqsOdtCompOffset:
    case DataRxD0PiCb:
    case DataSDllPiCb:
    case RxBiasCtl:
    case CompOffsetVssHiFF:
      //ByteCount will vary based on DdrType
      TransChannel = *Controller;
      TransStrobe = (*Channel * Outputs->SdramCount);
      TransStrobe += *Strobe;
      break;

    default:
      if ((Group > EndOfIocMarker) && (Group < EndOfMccMarker)) {
        // This is to cover all MCT and MCC enums
        switch (DdrType) {
          case MRC_DDR_TYPE_LPDDR4:
          case MRC_DDR_TYPE_LPDDR5:
            if (*Channel != MRC_IGNORE_ARG) {
              // Always force writes to this register to the MC channel number for LP.
              TransChannel = *Channel / 2;
              if (*Channel % 2) {
                Status = mrcInstanceDoesNotExist;
                MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR,
                               "GetSet called with Ch of 1/3 when LPDDR, Group %s(%d), Ch%d\n",
                               GsmGtDebugStrings[Group], Group, *Channel);
              }
            }
            break;

          default:
            // DDR4/DDR5 will use System Channel Number.
            break;
        }
      }
      break;

  }

  *Controller = TransController;
  *Channel = TransChannel;
  *Rank = TransRank;
  *Strobe = TransStrobe;

  return Status;
}

/**
  Top level function that is System Level Specificity.
  The flow is as follows:
    Check Multicast/Unicast, translate from system to IP register architecture, side effect and update other PHY logic.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]      Controller  - Memory Controller Number within the processor (0-Based).
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      Dimm        - DIMM Number within the DDR Channel (0-based). Ignored as Rank is rank number in the channel.
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Strobe      - Dqs data group within the rank (0-based).
  @param[in]      Bit         - Bit index within the data group (0-based).
  @param[in]      FreqIndex   - Index supporting multiple operating frequencies.
  @param[in]      Level       - DDRIO level to access.
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSet (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Socket,
  IN      UINT32        const   Controller,
  IN      UINT32        const   Channel,
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
  MrcOutput         *Outputs;
  UINT32            SocketLoop;
  UINT32            SocketStart;
  UINT32            SocketEnd;
  UINT32            ControllerLoop;
  UINT32            ControllerStart;
  UINT32            ControllerEnd;
  UINT32            ChannelLoop;
  UINT32            ChannelStart;
  UINT32            ChannelEnd;
  UINT32            RankLoop;
  UINT32            RankStart;
  UINT32            RankEnd;
  UINT32            StrobeLoop;
  UINT32            StrobeStart;
  UINT32            StrobeEnd;
  UINT32            BitLoop;
  UINT32            BitStart;
  UINT32            BitEnd;
  BOOLEAN           ReadOnly;
  BOOLEAN           Lpddr;
  BOOLEAN           McGroup;
  BOOLEAN           MulticastAccess;
  BOOLEAN           ValidMc;
  BOOLEAN           ValidCh;
  BOOLEAN           ValidRank;
  BOOLEAN           ValidStrobe;
  UINT32            TransController;
  UINT32            TransChannel;
  UINT32            TransRank;
  UINT32            TransStrobe;
#ifdef MRC_DEBUG_PRINT
  MrcDebug      *Debug;

  Debug = &MrcData->Outputs.Debug;

  // Check that the level is supported
  switch (Level) {
    case DdrLevel:
      break;

    default:
      MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "GetSet, Level %d is not supported!\n", Level);
      return mrcWrongInputParameter;
      break;
  }

  // Check that the Group is supported
  Status = MrcCheckGroupSupported (MrcData, Group);
  if (Status != mrcSuccess) {
    return Status;
  }
#endif // MRC_DEBUG_PRINT

  Outputs = &MrcData->Outputs;
  Lpddr = Outputs->Lpddr;

  ReadOnly = (Mode & GSM_READ_ONLY) == GSM_READ_ONLY;
  Status = mrcSuccess;

  // Detect and convert all Multicast accesses into unicast.
  MulticastAccess = FALSE;
  if ((Socket != MRC_IGNORE_ARG) && (Socket >= MAX_CPU_SOCKETS)) {
    MulticastAccess = TRUE;
    SocketStart = 0;
    SocketEnd = MAX_CPU_SOCKETS - 1;
  } else {
    SocketStart = Socket;
    SocketEnd = Socket;
  }
  if ((Controller != MRC_IGNORE_ARG) && (Controller >= MAX_CONTROLLER)) {
    MulticastAccess = TRUE;
    ControllerStart = 0;
    ControllerEnd = MAX_CONTROLLER - 1;
  } else {
    ControllerStart = Controller;
    ControllerEnd = Controller;
  }
  if ((Channel != MRC_IGNORE_ARG) && (Channel >= (Outputs->MaxChannels))) {
    MulticastAccess = TRUE;
    ChannelStart = 0;
    ChannelEnd = (UINT32) (Outputs->MaxChannels) - 1;
  } else {
    ChannelStart = Channel;
    ChannelEnd = Channel;
  }
  if ((Rank != MRC_IGNORE_ARG) && (Rank >= MAX_RANK_IN_CHANNEL)) {
    MulticastAccess = TRUE;
    RankStart = 0;
    RankEnd = MAX_RANK_IN_CHANNEL - 1;
  } else {
    RankStart = Rank;
    RankEnd = Rank;
  }
  if ((Strobe != MRC_IGNORE_ARG) && (Strobe >= MAX_SDRAM_IN_DIMM)) {
    MulticastAccess = TRUE;
    StrobeStart = 0;
    StrobeEnd = MrcData->Outputs.SdramCount - 1;
  } else {
    StrobeStart = Strobe;
    StrobeEnd = Strobe;
  }
  if ((Bit != MRC_IGNORE_ARG) && (Bit >= MAX_BITS)) {
    MulticastAccess = TRUE;
    BitStart = 0;
    BitEnd = MAX_BITS - 1;
  } else {
    BitStart = Bit;
    BitEnd = Bit;
  }

  ValidMc     = (Controller != MRC_IGNORE_ARG);
  ValidCh     = (Channel != MRC_IGNORE_ARG);
  ValidRank   = (Rank != MRC_IGNORE_ARG);
  ValidStrobe = (Strobe != MRC_IGNORE_ARG);

  // Check if we are a MC Group.  If so, then we want to skip writes to channel 1/3
  if ((Group > EndOfIocMarker) && (Group < EndOfMccMarker)) {
    McGroup = TRUE;
  } else {
    McGroup = FALSE;
  }

  // Break Multicast requests into multiple unicasts if it is not GSM_READ_ONLY.
  if (MulticastAccess) {
    if (ReadOnly) {
      // Ensure no one is trying to read with multicast parameters.
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to read from a Multicast. Group: %s(%d) Controller: %u, Channel: %u, Rank: %u, Byte: %u\n",
        GsmGtDebugStrings[Group], Group, Controller, Channel, Rank, Strobe);
      return mrcWrongInputParameter;
    }
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "SocketStart: %d\tSocketEnd: %d\n", SocketStart, SocketEnd);
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "ControllerStart: %d\tControllerEnd: %d\n", ControllerStart, ControllerEnd);
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "ChannelStart: %d\tChannelEnd: %d\n", ChannelStart, ChannelEnd);
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "RankStart: %d\tRankEnd: %d\n", RankStart, RankEnd);
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "StrobeStart: %d\tStrobeEnd: %d\n", StrobeStart, StrobeEnd);
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "BitStart: %d\tBitEnd: %d\n", BitStart, BitEnd);
    for (SocketLoop = SocketStart; SocketLoop <= SocketEnd; SocketLoop++) {
      for (ControllerLoop = ControllerStart; ControllerLoop <= ControllerEnd; ControllerLoop++) {
        if (ValidMc) {
          if (!MrcControllerExist (MrcData, ControllerLoop)) {
            MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s skipped as %s %d does not exist\n", GsmGtDebugStrings[Group], gControllerStr, ControllerLoop);
            continue;
          }
        }
        for (ChannelLoop = ChannelStart; ChannelLoop <= ChannelEnd; ChannelLoop++) {
          if (ValidMc && ValidCh) {
            if (!MrcChannelExist (MrcData, ControllerLoop, ChannelLoop)) {
              MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s skipped as %s %d does not exist\n", GsmGtDebugStrings[Group], gChannelStr, ChannelLoop);
              continue;
            } else if (McGroup && (IS_MC_SUB_CH (Lpddr, ChannelLoop))) {
              // Skip calling MrcGetSet for CH 1/3 if we are LPDDR since there isn't any register associated to it.
              continue;
            }
          }
          for (RankLoop = RankStart; RankLoop <= RankEnd; RankLoop++) {
            if (ValidMc && ValidCh && ValidRank) {
              if (!MrcRankExist (MrcData, ControllerLoop, ChannelLoop, RankLoop)) {
                MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s skipped as %s %d does not exist\n", GsmGtDebugStrings[Group], gRankStr, RankLoop);
                continue;
              }
            }
            for (StrobeLoop = StrobeStart; StrobeLoop <= StrobeEnd; StrobeLoop++) {
              if (ValidMc && ValidCh && ValidRank && ValidStrobe) {
                if (!MrcByteExist (MrcData, ControllerLoop, ChannelLoop, StrobeLoop)) {
                  MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s skipped as %s %d does not exist\n", GsmGtDebugStrings[Group], gByteStr, StrobeLoop);
                  continue;
                }
              }
              for (BitLoop = BitStart; BitLoop <= BitEnd; BitLoop++) {
                CurrentStatus = MrcGetSet (
                                  MrcData,
                                  SocketLoop,
                                  ControllerLoop,
                                  ChannelLoop,
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
        } // ChannelLoop
      } // ControllerLoop
    } // SocketLoop
    // We stop here when breaking up multicasts.
    return Status;
  }

  if (MrcCheckComplexOrSideEffect (MrcData, Group, MRC_IS_COMPLEX)) {
    // Complex parameters will stop here.
    Status = MrcGetSetComplexParam (MrcData, Socket, Controller, Channel, 0, Rank, Strobe, Bit, FreqIndex, Group, Mode, Value);
    if (Status == mrcComplexParamDone) {
      return mrcSuccess;
    }
  }

  TransController = Controller;
  TransChannel = Channel;
  TransRank = Rank;
  TransStrobe = Strobe;
  Status = MrcTranslateSystemToIp (MrcData, &TransController, &TransChannel, &TransRank, &TransStrobe, Group);

  if (Status == mrcSuccess) {
    Status = GetSet (MrcData, Socket, TransController, TransChannel, Dimm, TransRank, TransStrobe, Bit, FreqIndex, Level, Group, Mode, Value);

    if (!ReadOnly) {
      // Update other Phy Channels
      MrcGetSetUpdatePhyChannels (MrcData, Socket, Controller, Channel, Dimm, Rank, Strobe, Bit, FreqIndex, Level, Group, Mode, Value);

      // Update MRC Host
      MrcGetSetUpdateHost (MrcData, TransController, TransChannel, TransRank, TransStrobe, Bit, Group, Value);

      // Check if the field written to has some side effect and resolve it.
      if (MrcCheckComplexOrSideEffect (MrcData, Group, MRC_IS_SIDE_EFFECT)) {
        MrcGetSetSideEffect (MrcData, Socket, Controller, Channel, 0, Dimm, Rank, Strobe, Bit, FreqIndex, Level, Group, Mode, Value);
      }
    }
  }

  return Status;
}

/**
Top level function used to interact with SOC.
The flow is as follows:
  Get the GSM_GT bit shift instruction, CR offset.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
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
GetSet (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Socket,
  IN      UINT32        const   Controller,
  IN      UINT32        const   Channel,
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
  MRC_RX_MODE_TYPE  RxMode;
  INT64             CurrentVal;
  INT64             UpdateVal;
  INT64             Min;
  INT64             Max;
  UINT64            RegVal;
  UINT64            NewRegVal;
  UINT32            Offset;
  UINT32            Delay;
  BOOLEAN           RegSize;
  BOOLEAN           ReadOnly;
  BOOLEAN           Unmatched;
  BOOLEAN           IsRxVocUnmatched;
  BOOLEAN           RxVocDqs;
  MRC_REGISTER_HASH_STRUCT  HashVal;
#ifdef MRC_DEBUG_PRINT
  MrcDebug      *Debug;
  INT64_STRUCT  PrintVal;
  CHAR8         Str[120];
  CHAR8         *p;

  Debug = &MrcData->Outputs.Debug;
#ifdef MRC_DISABLE_CACHING
  Mode &= ~GSM_CACHE_ONLY;
  Mode |= GSM_READ_CSR;
#endif
#endif // MRC_DEBUG_PRINT

  RxMode = MrcData->Outputs.RxMode;
  Unmatched = (RxMode == MrcRxModeUnmatchedRxWRload) || (RxMode == MrcRxModeUnmatchedRxWPpath);
  RxVocDqs  = (Group == RxDqsUnmatchedAmpOffset);
  IsRxVocUnmatched = Unmatched && ((Group == RxVoc) || (Group == RxVocUnmatched) || RxVocDqs);
  ReadOnly = (Mode & GSM_READ_ONLY) == GSM_READ_ONLY;
  Status = mrcSuccess;

  // Get CR offset and field hash value
  if (Group < EndOfPhyMarker) {
    Status = MrcGetDdrIoHash (MrcData, Group, Socket, Controller, Channel, Rank, Strobe, Bit, FreqIndex, &HashVal.Data);
  } else if (Group < EndOfIocMarker) {
    Status = MrcGetDdrIoCfgHash (MrcData, Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex, &HashVal.Data);
  } else if (Group < EndOfMctMarker) {
    Status = MrcGetMcTimingHash (MrcData, Group, Socket, Controller, Channel, FreqIndex, &HashVal.Data);
  } else if (Group < EndOfMccMarker) {
    Status = MrcGetMcConfigHash (MrcData, Group, Socket, Controller, Channel, FreqIndex, &HashVal.Data);
  } else {
    Status = MrcGetCmiHash (MrcData, Group, Socket, Channel, FreqIndex, &HashVal.Data);
  }
  if (Status != mrcSuccess) {
    return Status;
  }

  Offset = HashVal.Bits.Offset;
  RegSize = (HashVal.Bits.RegSize != 0);
#ifdef MRC_DEBUG_PRINT
  if (Offset > MRC_REGISTER_HASH_Offset_MAX) {
    p = Str;
    p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), "No Offset found for Group %s(%d)", GsmGtDebugStrings[Group], Group) - 1;
    if (Socket != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), " Socket %u,", Socket) - 1;
    }
    if (Controller != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), " Controller %u,", Controller) - 1;
    }
    if (Channel != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), " Channel %u,", Channel) - 1;
    }
    if (Rank != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), " Rank %u,", Rank) - 1;
    }
    if (Strobe != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), " Strobe %u,", Strobe) - 1;
    }
    if (Bit != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), " Bit %u,", Bit) - 1;
    }
    if (FreqIndex != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), " FreqIndex %u", FreqIndex) - 1;
    }
    MRC_DEBUG_ASSERT (Offset < MRC_REGISTER_HASH_Offset_MAX, Debug, "%s\n", Str);
  }
#endif // MRC_DEBUG_PRINT

  // Init data.
  RegVal = MrcCrCacheRead (MrcData, Offset, RegSize, Mode);

  // Get the group value
  CurrentVal = MrcHalGsmGetBitField (MrcData, HashVal, RegVal);

  // Workaround for SenseAmpOffset being non-monotonic in its sweep
  // MRC is passing its offset encoding, so we translate from CR Encoding here.
  if (IsRxVocUnmatched) {
    MrcTranslateSotOffset (CurrentVal, &CurrentVal, TRUE, RxVocDqs);
  }

  if (ReadOnly) {
    *Value = CurrentVal;
    // UpdatedVal is used for printing below due to W/A around SOT parameter
    UpdateVal = CurrentVal;
  } else {
    CurrentVal = ((Mode & GSM_WRITE_OFFSET) == GSM_WRITE_OFFSET) ? CurrentVal + *Value : *Value;

    // Check value limits.
    MrcGetSetLimits (MrcData, Group, &Min, &Max, &Delay);

    if ((CurrentVal < Min) || (CurrentVal > Max)) {
#ifdef MRC_DEBUG_PRINT
      p = Str;
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), "%s", gWarnString) - 1;
      if (Controller != MRC_IGNORE_ARG) {
        p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), "Mc%u", Controller) - 1;
      }
      if (Channel != MRC_IGNORE_ARG) {
        p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), ".C%u", Channel) - 1;
      }
      if (Rank != MRC_IGNORE_ARG) {
        p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), ".R%u", Rank) - 1;
      }
      if (Strobe != MRC_IGNORE_ARG) {
        p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), ".S%u", Strobe) - 1;
      }
      if (Bit != MRC_IGNORE_ARG) {
        p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), ".B%u,", Bit) - 1;
      }
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), " %s value %lld is out of range [%lld:%lld]. Clamping\n",
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

    // Workaround for SenseAmpOffset being non-monotonic in its sweep
    // When we write back to the CR, we need to translate back to its encoding.
    // NewRegVal is in MRC encoding at this point.
    if (IsRxVocUnmatched) {
      MrcTranslateSotOffset (CurrentVal, &UpdateVal, FALSE, RxVocDqs);
    } else {
      UpdateVal = CurrentVal;
    }

    // Update CR with new value
    NewRegVal = MrcHalGsmSetBitField (MrcData, HashVal, UpdateVal, RegVal);

    if (((Mode & GSM_FORCE_WRITE) == GSM_FORCE_WRITE) || (RegVal != NewRegVal)) {
      MrcCrCacheWrite (MrcData, Offset, RegSize, Mode, Delay, NewRegVal);
    }
  }

#ifdef MRC_DEBUG_PRINT
  if (Mode & GSM_PRINT_VAL) {
    p = Str;
    PrintVal.Data = UpdateVal;
    *p++ = (ReadOnly) ? 'R' : 'W';
    *p++ = ' ';
    if (Controller != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), "Mc%u", Controller) - 1;
    }
    if (Channel != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), ".C%u", Channel) - 1;
    }
    if (Rank != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), ".R%u", Rank) - 1;
    }
    if (Strobe != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), ".S%u", Strobe) - 1;
    }
    if (Bit != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), ".B%u", Bit) - 1;
    }
    p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), " %s: ", GsmGtDebugStrings[Group]) - 1;
    if (HashVal.Bits.BfWidth > 32) {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), "0x%llx", CurrentVal) - 1;
    } else {
      p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), "%d", PrintVal.Data32.Low) - 1;
      if ((HashVal.Bits.BfSign == 0) && (PrintVal.Data32.Low > 9)) {
        p += MrcSPrintf (MrcData, p, sizeof (Str)-(p - Str), " (0x%x)", PrintVal.Data32.Low) - 1;
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\n", Str);
  }
#endif // MRC_DEBUG_PRINT

  return Status;
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

#ifdef MRC_DISABLE_CACHING
  Mode &= ~GSM_CACHE_ONLY;
  Mode |= GSM_READ_CSR;
#endif
  Debug      = &MrcData->Outputs.Debug;

  // Check that the level is supported
  switch (Level) {
    case DdrLevel:
      break;

    default:
      MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "GetSet, Level %d is not supported!\n", Level);
      return mrcWrongInputParameter;
      break;
  }

  // Check that the Group is supported
  Status = MrcCheckGroupSupported (MrcData, Group);
  if (Status != mrcSuccess) {
    return Status;
  }
#endif // MRC_DEBUG_PRINT

  ReadOnly  = (Mode & GSM_READ_ONLY) == GSM_READ_ONLY;
  Status = mrcSuccess;

  // Detect and convert all Multicast accesses into unicast.
  MulticastAccess = FALSE;
  if ((Socket != MRC_IGNORE_ARG) && (Socket >= MAX_CPU_SOCKETS)) {
    MulticastAccess = TRUE;
    SocketStart = 0;
    SocketEnd = MAX_CPU_SOCKETS - 1;
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
        if ((!MrcChannelExist (MrcData, 0, ChannelLoop)) && (Channel != MRC_IGNORE_ARG)) {
          MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s skipped as %s %d does not exist\n", GsmGtDebugStrings[Group], gChannelStr, ChannelLoop);
          continue;
        }
        for (SubChLoop = SubChStart; SubChLoop <= SubChEnd; SubChLoop++) {
          for (RankLoop = RankStart; RankLoop <= RankEnd; RankLoop++) {
            if ((!MrcRankExist (MrcData, CONTROLLER_0, ChannelLoop, RankLoop)) && (Rank != MRC_IGNORE_ARG)) {
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
    Status = MrcGetSetComplexParam (MrcData, Socket, 0, Channel, SubChannel, Rank, Strobe, Bit, FreqIndex, Group, Mode, Value);
    if (Status == mrcComplexParamDone) {
      return mrcSuccess;
    }
  }

  // Get CR offset and field hash value
  if (Group < EndOfPhyMarker) {
    Status = MrcGetDdrIoHash (MrcData, Group, Socket, CONTROLLER_0, Channel, Rank, Strobe, Bit, FreqIndex, &HashVal.Data);
  } else if (Group < EndOfIocMarker) {
    Status = MrcGetDdrIoCfgHash (MrcData, Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex, &HashVal.Data);
  } else if (Group < EndOfMctMarker) {
    Status = MrcGetMcTimingHash (MrcData, Group, Socket, CONTROLLER_0, Channel, FreqIndex, &HashVal.Data);
  } else if (Group < EndOfMccMarker) {
    Status = MrcGetMcConfigHash (MrcData, Group, Socket, CONTROLLER_0, Channel, FreqIndex, &HashVal.Data);
  } else {
    Status = MrcGetCmiHash (MrcData, Group, Socket, Channel, FreqIndex, &HashVal.Data);
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

  // Init data.
  RegVal = MrcCrCacheRead (MrcData, Offset, RegSize, Mode);

  // Get the group value
  CurrentVal = MrcHalGsmGetBitField (MrcData, HashVal, RegVal);

  if (ReadOnly) {
    *Value = CurrentVal;
  } else {
    CurrentVal = ((Mode & GSM_WRITE_OFFSET) == GSM_WRITE_OFFSET) ? CurrentVal + *Value : *Value;

    // Check value limits.
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

    // Update CR with new value
    NewRegVal = MrcHalGsmSetBitField (MrcData, HashVal, CurrentVal, RegVal);
    if (((Mode & GSM_FORCE_WRITE) == GSM_FORCE_WRITE) || (RegVal != NewRegVal)) {
      MrcCrCacheWrite (MrcData, Offset, RegSize, Mode, Delay, NewRegVal);
    }
    // Check if the field written to has some side effect and resolve it.
    if (MrcCheckComplexOrSideEffect (MrcData, Group, MRC_IS_SIDE_EFFECT)) {
      MrcGetSetSideEffect (MrcData, Socket, 0, Channel, SubChannel, Dimm, Rank, Strobe, Bit, FreqIndex, Level, Group, Mode, &CurrentVal);
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
  BOOLEAN   Lpddr5;
  BOOLEAN   Gear2;
  BOOLEAN   Matched;
#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  MrcDebug  *Debug;
#endif
  INT64     Min;
  INT64     Max;
  UINT32    Wait;
  Outputs = &MrcData->Outputs;
#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  Debug   = &Outputs->Debug;
#endif
  Status  = mrcSuccess;
  Wait    = 0;
  Min     = MRC_INT64_MIN;
  Max     = MRC_INT64_MAX;
  Lpddr5  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5);
  Gear2   = Outputs->Gear2;
  if (((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && (Outputs->Frequency == f1067)) || (Lpddr5 && (Outputs->Frequency == f1100))) {
    Gear2 = FALSE;
  }
  Matched = (Outputs->RxMode == MrcRxModeMatchedN) || (Outputs->RxMode == MrcRxModeMatchedP);

  switch (Group) {
    case RecEnDelay:
      Min = DATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_MIN;
      Max = DATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_MAX;
      break;

    case RxDqsNDelay:
      Min = DATA0CH0_CR_RXCONTROL0RANK0_RxDqsNDelayPi_MIN;
      Max = DATA0CH0_CR_RXCONTROL0RANK0_RxDqsNDelayPi_MAX;
      break;

    case RxDqsPDelay:
      Min = DATA0CH0_CR_RXCONTROL0RANK0_RxDqsPDelayPi_MIN;
      Max = DATA0CH0_CR_RXCONTROL0RANK0_RxDqsPDelayPi_MAX;
      break;

    case RxVref:
      Min = DATA0CH0_CR_DDRCRDATACONTROL5_RxVref_MIN;
      Max = 381; // DATA0CH0_CR_DDRCRDATACONTROL5_RxVref_MAX is 511, but max valid value is 381
      break;

    case RxVoc:
      // For matched we sweep 1-31, for Unmatched we sweep 0 - 30
      Min = (Matched) ? 1 : DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset0_MIN;
      Max = (Matched) ? DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset0_MAX : 30;
      break;

    case RxVocUnmatched:
      Min = DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset1_MIN;
      Max = 30; //DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset1_MAX;
      break;

    case RxEq:
      Min = 0;  //Subfield breakout of ddrdata_cr_ddrcrdatacontrol4.RxEqRank
      Max = 15; //Subfield breakout of ddrdata_cr_ddrcrdatacontrol4.RxEqRank
      break;

    case RxR:
      Min = 0; //Subfield breakout of ddrdata_cr_ddrcrdatacontrol4.RxEqRank
      Max = 3; //Subfield breakout of ddrdata_cr_ddrcrdatacontrol4.RxEqRank
      break;

    case RxC:
      Min = 0; //Subfield breakout of ddrdata_cr_ddrcrdatacontrol4.RxEqRank
      Max = 3; //Subfield breakout of ddrdata_cr_ddrcrdatacontrol4.RxEqRank
      break;

    case RxTap0:
      Min = 0;  //Subfield breakout of ddrdata_cr_ddrcrdatacontrol4.RxEqRank
      Max = 15; //Subfield breakout of ddrdata_cr_ddrcrdatacontrol4.RxEqRank
      break;

    case RxTap1:
      Min = 0;  //Subfield breakout of ddrdata_cr_ddrcrdatacontrol4.RxEqRank
      Max = 15; //Subfield breakout of ddrdata_cr_ddrcrdatacontrol4.RxEqRank
      break;

    case RxDqBitDelay:
      Min = DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskew_MIN;
      Max = DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskew_MAX;
      break;

    case RxDqBitOffset:
      Min = DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskewOffset_MIN;
      Max = DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskewOffset_MAX;
      break;

    case RxRankMuxDelay:
      Min = DATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_MAX;
      break;

    case TxDqsDelay:
      Min = DATA0CH0_CR_TXCONTROL0RANK0_TxDqsDelay_MIN;
      Max = DATA0CH0_CR_TXCONTROL0RANK0_TxDqsDelay_MAX;
      break;

    case TxDqDelay:
      Min = DATA0CH0_CR_TXCONTROL0RANK0_TxDqDelay_MIN;
      Max = DATA0CH0_CR_TXCONTROL0RANK0_TxDqDelay_MAX;
      break;

    case TxEq:
      Min = DATA0CH0_CR_TXCONTROL0RANK0_TxEqualization_MIN;
      Max = DATA0CH0_CR_TXCONTROL0RANK0_TxEqualization_MAX;
      break;

    case CmdTxEq:
      Min = CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_MIN;
      Max = CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_MAX;
      break;

    case CtlTxEq:
      Min = CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_MIN;
      Max = CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_MAX;
      break;

    case RxVrefVttDecap:
      Min = DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_MAX;
      break;

    case RxVrefVddqDecap:
      Min = DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVddqProgMFC_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVddqProgMFC_MAX;
      break;

    case PanicVttDnLp:
      Min = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_VttPanicCompDnLpMult_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_VttPanicCompDnLpMult_MAX;
      break;

    case VttGenStatusSelCount:
      Min = DDRVTT0_CR_DDRCRVTTGENSTATUS_SelCount_MIN;
      Max = DDRVTT0_CR_DDRCRVTTGENSTATUS_SelCount_MAX;
      break;

    case VttGenStatusCount:
      Min = DDRVTT0_CR_DDRCRVTTGENSTATUS_Count_MIN;
      Max = DDRVTT0_CR_DDRCRVTTGENSTATUS_Count_MAX;
      break;

    case RloadDqsDn:
      Min = DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_RloadDqs_MIN;
      Max = DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_RloadDqs_MAX;
      break;

    case RxCben:
      Min = DLLDDRDATA0_CR_PITUNE_PiCbEn_MIN;
      Max = DLLDDRDATA0_CR_PITUNE_PiCbEn_MAX;
      break;

    case RxBiasCtl:
      Min = DATA0CH0_CR_DDRCRDATACONTROL5_BiasIrefAdj_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL5_BiasIrefAdj_MAX;
      break;

    case DataRxD0PiCb:
      Min = DATA0CH0_CR_DDRCRDATACONTROL6_rxd0picb_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL6_rxd0picb_MAX;
      break;

    case DataSDllPiCb:
      Min = DATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_MAX;
      break;

    case VccDllRxD0PiCb:
      Min = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_RxD0PiCB_MIN;
      Max = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_RxD0PiCB_MAX;
      break;

    case VccDllSDllPiCb:
      Min = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_SdllPiCB_MIN;
      Max = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_SdllPiCB_MAX;
      break;

    case DqsOdtCompOffset:
      Min = DATA0CH0_CR_DDRCRDATACONTROL5_DqsOdtCompOffset_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL5_DqsOdtCompOffset_MAX;
      break;

    case TxRankMuxDelay:
      Min = DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_MAX;
      break;

    case TxDqsRankMuxDelay:
      Min = DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_MAX;
      break;

    case TxDqBitDelay:
      Min = DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDQPerBitDeskew_MIN;
      Max = DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDQPerBitDeskew_MAX;
      break;

    case TxDqsBitDelay:
      Min = DATA0CH0_CR_DDRDATADQSRANK0_TxDQSPerBitDeskew_MIN;
      Max = DATA0CH0_CR_DDRDATADQSRANK0_TxDQSPerBitDeskew_MAX;
      break;

    case RecEnOffset:
      Min = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MIN;
      Max = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MAX;
      break;

    case RxDqsOffset:
      Min = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MIN;
      Max = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MAX;
      break;

    case RxVrefOffset:
      Min = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MIN;
      Max = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MAX;
      break;

    case TxDqsOffset:
      Min = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MIN;
      Max = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MAX;
      break;

    case TxDqOffset:
      Min = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MIN;
      Max = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MAX;
      break;

    case RoundTripDelay:
      Min = MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_MIN;
      Max = MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_MAX;
      break;

    case RxFlybyDelay:
      Min = MCMISCS_READCFGCH01_RcvEnRank0ChADel_MIN;
      Max = MCMISCS_READCFGCH01_RcvEnRank0ChADel_MAX;
      break;

    case RxIoTclDelay:
      Min = MCMISCS_READCFGCH0_tCL4RcvEn_MIN;
      Max = MCMISCS_READCFGCH0_tCL4RcvEn_MAX;
      break;

    case RxFifoRdEnFlybyDelay:
      Min = MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_MIN;
      Max = (Gear2) ? (MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_MAX - 1) / 2 : MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_MAX;
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
      Min = MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChADel_MIN;
      Max = MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChADel_MAX;
      break;

    case CmdVref:
      Min = DDRVREF_CR_DDRCRVREFADJUST1_ca0Vref_MIN;
      Max = 383;  // DDRVREF_CR_DDRCRVREFADJUST1_ca0Vref_MAX is 511, but max valid value is 383
      break;

    case SenseAmpDelay:
      Min = DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MAX;
      break;

    case SenseAmpDuration:
      Min = DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MAX;
      break;

    case McOdtDelay:
      Min = DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDelay_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDelay_MAX;
      break;

    case McOdtDuration:
      Min = DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDuration_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDuration_MAX;
      break;

    case DqsOdtDelay:
      Min = DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDelay_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDelay_MAX;
      break;

    case DqsOdtDuration:
      Min = DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDuration_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDuration_MAX;
      break;

    case RxDqsAmpOffset:
      // Smallest offset starts at 1, not 0.
      Min = 1; //DATA0CH0_CR_DDRDATADQSRANK0_RxDQSVrefOffset_MIN;
      Max = DATA0CH0_CR_DDRDATADQSRANK0_RxDQSVrefOffset_MAX;
      break;

    case RxDqsUnmatchedAmpOffset:
      Min = DATA0CH0_CR_DDRDATADQSRANK0_RxDqsUnMatVrefOffset_MIN;
      Max = 30;  //DATA0CH0_CR_DDRDATADQSRANK0_RxDqsUnMatVrefOffset_MAX

    case CtlGrpPi:
    case ClkGrpPi:
    case CmdGrpPi:
    case CkeGrpPi:
    case WckGrpPi:
      Min = CH0CCC_CR_DDRCRCCCPICODING0_PiCode0_MIN;
      Max = CH0CCC_CR_DDRCRCCCPICODING0_PiCode0_MAX / ((Gear2 && Lpddr5) ? 1 : 2);
      break;

    case TxSlewRate:
    case CmdSlewRate:
    case CtlSlewRate:
    case ClkSlewRate:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqScompCells_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqScompCells_MAX;
      break;

    case DqScompPC:
    case CmdScompPC:
    case CtlScompPC:
    case ClkScompPC:
    case SCompBypassDq:
    case SCompBypassCmd:
    case SCompBypassCtl:
    case SCompBypassClk:
      Min = 0;
      Max = 1;
      break;

    case SCompCodeDq:
    case SCompCodeClk:
      Min = DATA0CH0_CR_RCOMPDATA0_SlewRateComp_MIN;
      Max = DATA0CH0_CR_RCOMPDATA0_SlewRateComp_MAX;
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
      Min = DATA0CH0_CR_RCOMPDATA0_RcompDrvUp_MIN;
      Max = DATA0CH0_CR_RCOMPDATA0_RcompDrvUp_MAX;
      break;

    case TxTco: // This is a 2's complement register, but we set absolute values to it (the sweep thus ends up being non-monotonic)
      Min = DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_MIN;
      Max = DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_MAX;
      break;

    case TxDqsTco:
      Min = DATA0CH0_CR_DDRDATADQSRANK0_DqsPfNrTcoDelay_MIN;
      Max = DATA0CH0_CR_DDRDATADQSRANK0_DqsPfNrTcoDelay_MAX;
      break;

    // @todo: This is the Comp register.  Not the comp code.  Where is it?
    case TcoCompCodeCmd:
    case TcoCompCodeCtl:
    case TcoCompCodeClk:
      Min = DDRPHY_COMP_CR_DDRCRCACOMP_TcoComp_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCACOMP_TcoComp_MAX;
      break;

    case DqOdtVrefUp:
    case DqOdtVrefDn:
    case DqDrvVrefUp:
    case DqDrvVrefDn:
    case CmdDrvVrefUp:
    case CmdDrvVrefDn:
    case CtlDrvVrefUp:
    case CtlDrvVrefDn:
    case ClkDrvVrefUp:
    case ClkDrvVrefDn:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqOdtVrefUp_MIN;
      Max = 191;
      break;

    case CompRcompOdtUp:
    case CompRcompOdtDn:
      Min = DATA0CH0_CR_RCOMPDATA1_RcompOdtUp_MIN;
      Max = DATA0CH0_CR_RCOMPDATA1_RcompOdtUp_MAX;
      break;

    case CtlSCompOffset:
    case CmdSCompOffset:
    case ClkSCompOffset:
    //@todo: Question - case CkeSCompOffset:
      Min = CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_MIN;
      Max = CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_MAX;
      break;

    case CtlRCompDrvUpOffset:
    case CtlRCompDrvDownOffset:
    case CmdRCompDrvUpOffset:
    case CmdRCompDrvDownOffset:
    //@todo: Question - case CkeRCompDrvDownOffset:
    //@todo: Question - case CkeRCompDrvUpOffset:
    case ClkRCompDrvUpOffset:
    case ClkRCompDrvDownOffset:
      Min = CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_MIN;
      Max = CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_MAX;
      break;

    case VsxHiClkFFOffset:
    case VsxHiCaFFOffset:
    case VsxHiCtlFFOffset:
      Min = CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_MIN;
      Max = CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_MAX;
      break;

    case CompOffsetVssHiFF:
      Min = DATA0CH0_CR_DDRCRDATAOFFSETCOMP_VssHiFFCompOffset_MIN;
      Max = DATA0CH0_CR_DDRCRDATAOFFSETCOMP_VssHiFFCompOffset_MAX;
      break;

    case RxPerBitDeskewCal:
    case TxPerBitDeskewCal:
    case CccPerBitDeskewCal:
      Min = DATA0CH0_CR_DDRCRDATACONTROL2_TxPBDCalibration_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL2_TxPBDCalibration_MAX;
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
    //case GsmComplexRxBias:
    //  Min = 0;
    //  Max = DDRDATA_CR_DDRCRDATACONTROL1_RxBiasCtl_MAX;
    //break;

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
      Min = DLLDDRDATA0_CR_DLLWEAKLOCK_wl_wakecycles_MIN;
      Max = DLLDDRDATA0_CR_DLLWEAKLOCK_wl_wakecycles_MAX;
      break;

    case GsmIocWlSleepCyclesLp:
    case GsmIocWlSleepCyclesAct:
      Min = DLLDDRDATA0_CR_DLLWEAKLOCK_WL_SleepCyclesAct_MIN;
      Max = DLLDDRDATA0_CR_DLLWEAKLOCK_WL_SleepCyclesAct_MAX;
      break;

    case GsmIocChNotPop:
      Min = DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_MIN;
      Max = DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_MAX;
      break;

    case GsmIocRxClkStg:
      Min = DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX;
      break;

    case GsmIocDataRxBurstLen:
      Min = DATA0CH0_CR_DDRCRDATACONTROL2_RxBurstLen_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL2_RxBurstLen_MAX;
      break;

    case GsmIocDllMask:
      Min = DLLDDRDATA0_CR_DLLWEAKLOCK_DLLMask0_MIN;
      Max = DLLDDRDATA0_CR_DLLWEAKLOCK_DLLMask0_MAX;
      break;

    case GsmIocSdllSegmentDisable:
      Min = DATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MAX;
      break;

    case GsmIocCmdDrvVref200ohm:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL2_Cmd200VrefDn_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL2_Cmd200VrefDn_MAX;
      break;

    case GsmIocVttPanicCompUpMult:
      Min = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_VttPanicCompUp0Mult_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_VttPanicCompUp0Mult_MAX;
      break;

    case GsmIocVttPanicCompDnMult:
      Min = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_VttPanicCompDn0Mult_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_VttPanicCompDn0Mult_MAX;
      break;

    case GsmIocCmdAnlgEnGraceCnt:
      Min = MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_MIN;
      Max = MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_MAX;
      break;

    case GsmIocTxAnlgEnGraceCnt:
      Min = MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MIN;
      Max = MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MAX;
      break;

    case GsmIocDqsMaskPulseCnt:
      Min = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_MIN;
      Max = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_MAX;
      break;

    case GsmIocDqsPulseCnt:
      Min = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_MIN;
      Max = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_MAX;
      break;

    case GsmIocDqOverrideData:
      Min = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_MIN;
      Max = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_MAX;
      break;

    case GsmIocDqOverrideEn:
      Min = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_MIN;
      Max = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_MAX;
      break;
/*
    case GsmIocRxPathBiasRcomp: // @todo No TGL version found
      Min = DATA0CH0_CR_DDRCRDATACONTROL4_biasrcomp_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL4_biasrcomp_MAX;
      break;
*/
    case GsmIocRankOverrideVal:
      Min = DATA0CH0_CR_DATATRAINFEEDBACK_RankValue_MIN;
      Max = DATA0CH0_CR_DATATRAINFEEDBACK_RankValue_MAX;
      break;

    case GsmIocVccDllRxDeskewCal:
    case GsmIocVccDllTxDeskewCal:
    case GsmIocVccDllCccDeskewCal:
      Min = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_RxDeskewCal_MIN;
      Max = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_RxDeskewCal_MAX;
      break;

    case GsmIocDccActiveClks:
      //@todo Min = MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_MIN;
      //@todo Max = MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_MAX;
      break;

    case GsmIocDccActiveBytes:
      //@todo Min = MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_MIN;
      //@todo Max = MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_MAX;
      break;

    case GsmIocDccClkTrainVal:
      //@todo Min = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Clk0DccVal_MIN;
      //@todo Max = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Clk0DccVal_MAX;
      break;

    case GsmIocDccDataTrainDqsVal:
      //@todo Min = DATA0CH0_CR_DCCDATATRAINVAL1RANK0_DqsDccVal_MIN;
      //@todo Max = DATA0CH0_CR_DCCDATATRAINVAL1RANK0_DqsDccVal_MAX;
      break;

    case GsmIocRxVrefMFC:
      Min = DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_MAX;
      break;

    case GsmIocRxVocMode:
      Min = DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_MAX;
      break;

    case GsmIocDataTrainFeedback:
      Min = DATA0CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MIN;
      Max = DATA0CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MAX;
      break;

    case GsmIocRxAmpOffsetEn:
      Min = DATA0CH0_CR_DATATRAINFEEDBACK_RxAmpOffsetEn_MIN;
      Max = DATA0CH0_CR_DATATRAINFEEDBACK_RxAmpOffsetEn_MAX;
      break;

    case GsmIocDataWrPreamble:
      Min = DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_MAX;
      break;

    case GsmIocDataDqsOdtParkMode:
      Min = DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_MAX;
      break;

    case GsmIocBiasPMCtrl:
      Min = DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_MAX;
      break;

    case GsmIocDataOdtMode:
      Min = DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_MAX;
      break;

    case GsmIocFFCodePiOffset:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodePIOffset_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodePIOffset_MAX;
      break;

    case GsmIocFFCodeIdleOffset:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeIdleOffset_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeIdleOffset_MAX;
      break;

    case GsmIocFFCodeWeakOffset:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeWeakOffset_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeWeakOffset_MAX;
      break;

    case GsmIocFFCodeWriteOffset:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeWriteOffset_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeWriteOffset_MAX;
      break;

    case GsmIocFFCodeReadOffset:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeReadOffset_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeReadOffset_MAX;
      break;

    case GsmIocFFCodePBDOffset:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodePBDOffset_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodePBDOffset_MAX;
      break;

    case GsmIocFFCodeCCCDistOffset:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeCCCDistOffset_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeCCCDistOffset_MAX;
      break;

    case GsmIocVssHiFFCodeIdle:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodeIdle_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodeIdle_MAX;
      break;

    case GsmIocVssHiFFCodeWrite:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodeWrite_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodeWrite_MAX;
      break;

    case GsmIocVssHiFFCodeRead:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodeRead_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodeRead_MAX;
      break;

    case GsmIocVssHiFFCodePBD:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodePBD_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodePBD_MAX;
      break;

    case GsmIocVssHiFFCodePi:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodePi_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodePi_MAX;
      break;

    case GsmIocDataInvertNibble:
      Min = DATA0CH0_CR_DDRCRDATACONTROL5_DataInvertNibble_MIN;
      Max = DATA0CH0_CR_DDRCRDATACONTROL5_DataInvertNibble_MAX;
      break;

    case GsmIocCapCancelCodeIdle:
    case GsmIocCapCancelCodeWrite:
    case GsmIocCapCancelCodeRead:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_CapCancelCodeIdle_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_CapCancelCodeIdle_MAX;
      break;

    case GsmIocCapCancelCodePBD:
    case GsmIocCapCancelCodePi:
      Min = DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_CapCancelCodePBD_MIN;
      Max = DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_CapCancelCodePBD_MAX;
      break;

    case GsmIocEnableSpineGate:
      Min = MCMISCS_SPINEGATING_EnableSpineGate_MIN;
      Max = MCMISCS_SPINEGATING_EnableSpineGate_MAX;
      break;

    case GsmIocWriteLevelMode:
      Min = DATA0CH0_CR_DATATRAINFEEDBACK_WLTrainingMode_MIN;
      Max = DATA0CH0_CR_DATATRAINFEEDBACK_WLTrainingMode_MAX;
      break;

    case GsmIocVccDllControlTarget_V:
      Min = DDRVCCDLL0_CR_DDRCRVCCDLLCONTROL_Target_MIN;
      Max = DDRVCCDLL0_CR_DDRCRVCCDLLCONTROL_Target_MAX;
      break;

    case GsmIocCccPiEn:
      Min = CH0CCC_CR_DDRCRPINSUSED_PiEn_MIN;
      Max = CH0CCC_CR_DDRCRPINSUSED_PiEn_MAX;
      break;

      // Binary Max/Min
    case GsmIocCccPiEnOverride:
    case GsmIocIoReset:
    case GsmIocForceCmpUpdt:
    case GsmIocScramLp4Mode:
    case GsmIocScramLp5Mode:
    case GsmIocScramOvrdPeriodicToDvfsComp:
    case GsmIocLp5Wck2CkRatio:
    case GsmIocScramDdr4Mode:
    case GsmIocScramDdr5Mode:
    case GsmIocScramGear1:
    case GsmIocVccDllGear1:
    case GsmIocVccDllControlBypass_V:
    case GsmIocVccDllControlSelCode_V:
    case GsmIocVccDllControlOpenLoop_V:
    case GsmIocVsxHiControlSelCode_V:
    case GsmIocVsxHiControlOpenLoop_V:
    case GsmIocDisDataIdlClkGate:
    case GsmIocDisClkGate:
    case GsmIocDisIosfSbClkGate:
    case GsmIocEccEn:
    case GsmIocScramLpMode:
    case GsmIocNoDqInterleave:
//    case GsmIocVrefPwrDnEn:
    case GsmIocCompVddqOdtEn:
    case GsmIocCompVttOdtEn:
    case GsmIocReadDqDqsMode:
    case GsmIocSenseAmpMode:
    case GsmIocCaTrainingMode:
    case GsmIocReadLevelMode:
    case GsmIocForceOdtOn:
    case GsmIocTxOn:
    case GsmIocRxDisable:
    case GsmIocRxPiPwrDnDis:
    case GsmIocTxPiPwrDnDis:
    case GsmIocInternalClocksOn:
    case GsmIocDataDqsNParkLow:
    case GsmIocTxDisable:
    case GsmIocDataOdtStaticDis:
    case GsmIocCompOdtStaticDis:
    case GsmIocStrobeOdtStaticDis:
    case GsmIocDataODTSingleSegEn:
//    case GsmIocRxTypeSelect:
//    case GsmIocRxPathBiasSel:
    case GsmIocCmdVrefConverge:
    case GsmIocConstZTxEqEn:
    case GsmIocCompClkOn:
    case GsmIocDisableQuickComp:
    case GsmIocSinStep:
    case GsmIocSinStepAdv:
    case GsmIocDllWeakLock:
    case GsmIocDllWeakLock1:
    case GsmIocTxEqDis:
//    case GsmIocForceBiasOn:
    case GsmIocForceRxAmpOn:
    case GsmIocDqSlewDlyByPass:
    case GsmIocWlLongDelEn:
    case GsmIocTxDqFifoRdEnPerRankDelDis:
    case GsmIocRptChRepClkOn:
    case GsmIocRankOverrideEn:
    case GsmIocDataCtlGear1:
    case GsmIocDccDcoCompEn:
    case GsmIocDccTrainingMode:
    case GsmIocDccTrainingDone:
    case GsmIocDccDrain:
    case GsmIocRXDeskewForceOn:
    case GsmIocDataDqOdtParkMode:
    case GsmIocEnDqsNRcvEn:
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
  const MrcInput *Inputs;
  MrcStatus      Status;
  MrcDebug       *Debug;
  INT64          Max;
  INT64          Min;
  UINT32         Wait;

  Inputs  = &MrcData->Inputs;
  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  Wait    = 0;
  Min     = MRC_INT64_MIN;
  Max     = MRC_INT64_MAX;

  switch (Group) {
    case GsmMctRCD:
      Min = MC0_CH0_CR_TC_PRE_tRCD_MIN;
      Max = MC0_CH0_CR_TC_PRE_tRCD_MAX;
      break;

    case GsmMctRP:
      Min = MC0_CH0_CR_TC_PRE_tRP_MIN;
      Max = MC0_CH0_CR_TC_PRE_tRP_MAX;
      break;

    case GsmMctRFCpb:
      Min = MC0_CH0_CR_SC_PBR_tRFCpb_MIN;
      Max = MC0_CH0_CR_SC_PBR_tRFCpb_MAX;
      break;

    case GsmMctRPabExt:
      Min = MC0_CH0_CR_TC_PRE_tRPab_ext_MIN;
      Max = 8; //MC0_CH0_CR_TC_PRE_tRPab_ext_MAX
      break;

    case GsmMctRAS:
      Min = MC0_CH0_CR_TC_PRE_tRAS_MIN;
      Max = MC0_CH0_CR_TC_PRE_tRAS_MAX;
      break;

    case GsmMctRDPRE:
      Min = MC0_CH0_CR_TC_PRE_tRDPRE_MIN;
      Max = MC0_CH0_CR_TC_PRE_tRDPRE_MAX;
      break;

    case GsmMctPPD:
      Min = MC0_CH0_CR_TC_PRE_tPPD_MIN;
      Max = MC0_CH0_CR_TC_PRE_tPPD_MAX;
      break;

    case GsmMctWRPRE:
      Min = MC0_CH0_CR_TC_PRE_tWRPRE_MIN;
      Max = MC0_CH0_CR_TC_PRE_tWRPRE_MAX;
      break;

    case GsmMctFAW:
      Min = MC0_CH0_CR_TC_ACT_tFAW_MIN;
      Max = MC0_CH0_CR_TC_ACT_tFAW_MAX;
      break;

    case GsmMctRRDsg:
      Min = MC0_CH0_CR_TC_ACT_tRRD_sg_MIN;
      Max = MC0_CH0_CR_TC_ACT_tRRD_sg_MAX;
      break;

    case GsmMctRRDdg:
      Min = MC0_CH0_CR_TC_ACT_tRRD_dg_MIN;
      Max = MC0_CH0_CR_TC_ACT_tRRD_dg_MAX;
      break;

    case GsmMctLpDeratingExt:
      if (Inputs->UlxUlt) {
        Min = MC0_CH0_CR_TC_ACT_derating_ext_MIN;
        Max = MC0_CH0_CR_TC_ACT_derating_ext_MAX;
      } else {
        Min = MC0_CH0_CR_TC_ACT_derating_ext_P0_MIN;
        Max = MC0_CH0_CR_TC_ACT_derating_ext_P0_MAX;
      }
      break;

    case GsmMctRDRDsg:
      Min = MC0_CH0_CR_TC_RDRD_tRDRD_sg_MIN;
      Max = MC0_CH0_CR_TC_RDRD_tRDRD_sg_MAX;
      break;

    case GsmMctRDRDdg:
      Min = MC0_CH0_CR_TC_RDRD_tRDRD_dg_MIN;
      Max = MC0_CH0_CR_TC_RDRD_tRDRD_dg_MAX;
      break;

    case GsmMctRDRDdr:
      Min = MC0_CH0_CR_TC_RDRD_tRDRD_dr_MIN;
      Max = MC0_CH0_CR_TC_RDRD_tRDRD_dr_MAX;
      break;

    case GsmMctRDRDdd:
      Min = MC0_CH0_CR_TC_RDRD_tRDRD_dd_MIN;
      Max = MC0_CH0_CR_TC_RDRD_tRDRD_dd_MAX;
      break;

    case GsmMctRDWRsg:
      Min = MC0_CH0_CR_TC_RDWR_tRDWR_sg_MIN;
      Max = MC0_CH0_CR_TC_RDWR_tRDWR_sg_MAX;
      break;

    case GsmMctRDWRdg:
      Min = MC0_CH0_CR_TC_RDWR_tRDWR_dg_MIN;
      Max = MC0_CH0_CR_TC_RDWR_tRDWR_dg_MAX;
      break;

    case GsmMctRDWRdr:
      Min = MC0_CH0_CR_TC_RDWR_tRDWR_dr_MIN;
      Max = MC0_CH0_CR_TC_RDWR_tRDWR_dr_MAX;
      break;

    case GsmMctRDWRdd:
      Min = MC0_CH0_CR_TC_RDWR_tRDWR_dd_MIN;
      Max = MC0_CH0_CR_TC_RDWR_tRDWR_dd_MAX;
      break;

    case GsmMctWRRDsg:
      Min = MC0_CH0_CR_TC_WRRD_tWRRD_sg_MIN;
      Max = MC0_CH0_CR_TC_WRRD_tWRRD_sg_MAX;
      break;

    case GsmMctWRRDdg:
      Min = MC0_CH0_CR_TC_WRRD_tWRRD_dg_MIN;
      Max = MC0_CH0_CR_TC_WRRD_tWRRD_dg_MAX;
      break;

    case GsmMctWRRDdr:
      Min = MC0_CH0_CR_TC_WRRD_tWRRD_dr_MIN;
      Max = MC0_CH0_CR_TC_WRRD_tWRRD_dr_MAX;
      break;

    case GsmMctWRRDdd:
      Min = MC0_CH0_CR_TC_WRRD_tWRRD_dd_MIN;
      Max = MC0_CH0_CR_TC_WRRD_tWRRD_dd_MAX;
      break;

    case GsmMctWRWRsg:
      if (Inputs->UlxUlt) {
        Min = MC0_CH0_CR_TC_WRWR_tWRWR_sg_MIN;
        Max = MC0_CH0_CR_TC_WRWR_tWRWR_sg_MAX;
      } else {
        Min = MC0_CH0_CR_TC_WRWR_tWRWR_sg_P0_MIN;
        Max = MC0_CH0_CR_TC_WRWR_tWRWR_sg_P0_MAX;
      }
      break;

    case GsmMctWRWRdg:
      Min = MC0_CH0_CR_TC_WRWR_tWRWR_dg_MIN;
      Max = MC0_CH0_CR_TC_WRWR_tWRWR_dg_MAX;
      break;

    case GsmMctWRWRdr:
      Min = MC0_CH0_CR_TC_WRWR_tWRWR_dr_MIN;
      Max = MC0_CH0_CR_TC_WRWR_tWRWR_dr_MAX;
      break;

    case GsmMctWRWRdd:
      Min = MC0_CH0_CR_TC_WRWR_tWRWR_dd_MIN;
      Max = MC0_CH0_CR_TC_WRWR_tWRWR_dd_MAX;
      break;

    case GsmMctOdtRdDuration:
      Min = MC0_CH0_CR_TC_ODT_ODT_read_duration_MIN;
      Max = MC0_CH0_CR_TC_ODT_ODT_read_duration_MAX;
      break;

    case GsmMctOdtRdDelay:
      Min = MC0_CH0_CR_TC_ODT_ODT_Read_Delay_MIN;
      Max = MC0_CH0_CR_TC_ODT_ODT_Read_Delay_MAX;
      break;

    case GsmMctOdtWrDuration:
      Min = MC0_CH0_CR_TC_ODT_ODT_write_duration_MIN;
      Max = MC0_CH0_CR_TC_ODT_ODT_write_duration_MAX;
      break;

    case GsmMctOdtWrDelay:
      Min = MC0_CH0_CR_TC_ODT_ODT_Write_Delay_MIN;
      Max = MC0_CH0_CR_TC_ODT_ODT_Write_Delay_MAX;
      break;

    case GsmMctCL:
      Min = MC0_CH0_CR_TC_ODT_tCL_MIN;
      Max = MC0_CH0_CR_TC_ODT_tCL_MAX;
      break;

    case GsmMctCWL:
      Min = MC0_CH0_CR_TC_ODT_tCWL_MIN;
      Max = MC0_CH0_CR_TC_ODT_tCWL_MAX;
      break;

    case GsmMctAONPD:
      Min = MC0_CH0_CR_TC_ODT_tAONPD_MIN;
      Max = MC0_CH0_CR_TC_ODT_tAONPD_MAX;
      break;

    case GsmMctCKE:
      Min = MC0_CH0_CR_TC_PWRDN_tCKE_MIN;
      Max = MC0_CH0_CR_TC_PWRDN_tCKE_MAX;
      break;

    case GsmMctXP:
      Min = MC0_CH0_CR_TC_PWRDN_tXP_MIN;
      Max = MC0_CH0_CR_TC_PWRDN_tXP_MAX;
      break;

    case GsmMctXPDLL:
      Min = MC0_CH0_CR_TC_PWRDN_tXPDLL_MIN;
      Max = MC0_CH0_CR_TC_PWRDN_tXPDLL_MAX;
      break;

    case GsmMctPRPDEN:
      if (Inputs->A0) {
        Min = MC0_CH0_CR_TC_PWRDN_tPRPDEN_A0_MIN;
        Max = MC0_CH0_CR_TC_PWRDN_tPRPDEN_A0_MAX;
      } else {
        Min = MC0_CH0_CR_TC_PWRDN_tPRPDEN_MIN;
        Max = MC0_CH0_CR_TC_PWRDN_tPRPDEN_MAX;
      }
      break;

    case GsmMctRDPDEN:
      Min = MC0_CH0_CR_TC_PWRDN_tRDPDEN_MIN;
      Max = MC0_CH0_CR_TC_PWRDN_tRDPDEN_MAX;
      break;

    case GsmMctWRPDEN:
      Min = MC0_CH0_CR_TC_PWRDN_tWRPDEN_MIN;
      Max = MC0_CH0_CR_TC_PWRDN_tWRPDEN_MAX;
      break;

    case GsmMctCA2CS:
      Min = MC0_CH0_CR_TC_PWRDN_tCA2CS_MIN;
      Max = MC0_CH0_CR_TC_PWRDN_tCA2CS_MAX;
      break;

    case GsmMctCSL:
      if (Inputs->UlxUlt) {
        Min = MC0_CH0_CR_TC_PWRDN_tCSL_MIN;
        Max = MC0_CH0_CR_TC_PWRDN_tCSL_MAX;
      } else {
        Min = MC0_CH0_CR_TC_PWRDN_tCSL_P0_MIN;
        Max = MC0_CH0_CR_TC_PWRDN_tCSL_P0_MAX;
      }
      break;

    case GsmMctCSH:
      if (Inputs->UlxUlt) {
        Min = MC0_CH0_CR_TC_PWRDN_tCSH_MIN;
        Max = MC0_CH0_CR_TC_PWRDN_tCSH_MAX;
      } else {
        Min = MC0_CH0_CR_TC_PWRDN_tCSH_P0_MIN;
        Max = MC0_CH0_CR_TC_PWRDN_tCSH_P0_MAX;
      }
      break;

    case GsmMctXSDLL:
      Min = MC0_CH0_CR_TC_SRFTP_tXSDLL_MIN;
      Max = MC0_CH0_CR_TC_SRFTP_tXSDLL_MAX;
      break;

    case GsmMctXSR:
      Min = MC0_CH0_CR_TC_SREXITTP_tXSR_MIN;
      Max = MC0_CH0_CR_TC_SREXITTP_tXSR_MAX;
      break;

    case GsmMctZQOPER:
      Min = MC0_CH0_CR_TC_SRFTP_tZQOPER_MIN;
      Max = MC0_CH0_CR_TC_SRFTP_tZQOPER_MAX;
      break;

    case GsmMctMOD:
      if (Inputs->UlxUlt) {
        Min = MC0_CH0_CR_TC_SRFTP_tMOD_MIN;
        Max = MC0_CH0_CR_TC_SRFTP_tMOD_MAX;
      } else {
        Min = MC0_CH0_CR_TC_SRFTP_tMOD_P0_MIN;
        Max = MC0_CH0_CR_TC_SRFTP_tMOD_P0_MAX;
      }
      break;

    case GsmMctZQCAL:
      Min = MC0_CH0_CR_TC_ZQCAL_tZQCAL_MIN;
      Max = MC0_CH0_CR_TC_ZQCAL_tZQCAL_MAX;
      break;

    case GsmMctZQCS:
      Min = MC0_CH0_CR_TC_ZQCAL_tZQCS_MIN;
      Max = MC0_CH0_CR_TC_ZQCAL_tZQCS_MAX;
      break;

    case GsmMctZQCSPeriod:
      Min = MC0_CH0_CR_TC_ZQCAL_ZQCS_period_MIN;
      Max = MC0_CH0_CR_TC_ZQCAL_ZQCS_period_MAX;
      break;

    case GsmMctCPDED:
      if (Inputs->UlxUlt) {
        Min = MC0_CH0_CR_SC_GS_CFG_tCPDED_MIN;
        Max = MC0_CH0_CR_SC_GS_CFG_tCPDED_MAX;
      } else {
        Min = MC0_CH0_CR_SC_GS_CFG_tCPDED_P0_MIN;
        Max = MC0_CH0_CR_SC_GS_CFG_tCPDED_P0_MAX;
      }
      break;

    case GsmMctCAL:
      Min = MC0_CH0_CR_SC_GS_CFG_tCAL_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_tCAL_MAX;
      break;

    case GsmMctCKCKEH:
      if (Inputs->UlxUlt) {
        Min = MC0_CH0_CR_SC_GS_CFG_ck_to_cke_MIN;
        Max = MC0_CH0_CR_SC_GS_CFG_ck_to_cke_MAX;
      } else {
        Min = MC0_CH0_CR_SC_GS_CFG_ck_to_cke_P0_MIN;
        Max = MC0_CH0_CR_SC_GS_CFG_ck_to_cke_P0_MAX;
      }
      break;

    case GsmMctCSCKEH:
      Min = MC0_CH0_CR_SC_GS_CFG_cs_to_cke_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_cs_to_cke_MAX;
      break;

    case GsmMctSrIdle:
      Min = MC0_PM_SREF_CONFIG_Idle_timer_MIN;
      Max = MC0_PM_SREF_CONFIG_Idle_timer_MAX;
      break;

    case GsmMctREFI:
      Min = MC0_CH0_CR_TC_RFTP_tREFI_MIN;
      Max = MC0_CH0_CR_TC_RFTP_tREFI_MAX;
      break;

    case GsmMctRFC:
      Min = MC0_CH0_CR_TC_RFTP_tRFC_MIN;
      Max = MC0_CH0_CR_TC_RFTP_tRFC_MAX;
      break;

    case GsmMctOrefRi:
      Min = MC0_CH0_CR_TC_RFP_OREF_RI_MIN;
      Max = MC0_CH0_CR_TC_RFP_OREF_RI_MAX;
      break;

    case GsmMctRefreshHpWm:
      Min = MC0_CH0_CR_TC_RFP_Refresh_HP_WM_MIN;
      Max = MC0_CH0_CR_TC_RFP_Refresh_HP_WM_MAX;
      break;

    case GsmMctRefreshPanicWm:
      Min = MC0_CH0_CR_TC_RFP_Refresh_panic_wm_MIN;
      Max = MC0_CH0_CR_TC_RFP_Refresh_panic_wm_MAX;
      break;

    case GsmMctREFIx9:
      if (Inputs->UlxUlt) {
        Min = MC0_CH0_CR_TC_RFP_tREFIx9_MIN;
        Max = MC0_CH0_CR_TC_RFP_tREFIx9_MAX;
      } else {
        Min = MC0_CH0_CR_TC_RFP_tREFIx9_P0_MIN;
        Max = MC0_CH0_CR_TC_RFP_tREFIx9_P0_MAX;
      }
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
  const MrcInput *Inputs;
  MrcStatus      Status;
  MrcDebug       *Debug;
  INT64          Max;
  INT64          Min;
  UINT32         Wait;
  BOOLEAN        IsDefined;

  Inputs       = &MrcData->Inputs;
  Debug        = &MrcData->Outputs.Debug;
  Status       = mrcSuccess;
  Wait         = 0;
  Min          = MRC_INT64_MIN;
  Max          = MRC_INT64_MAX;
  IsDefined    = TRUE;

  switch (Group) {
    case GsmMccDramType:
      Min = MC0_CH0_CR_SC_GS_CFG_DRAM_technology_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_DRAM_technology_MAX;
      break;

    case GsmMccCmdStretch:
      Min = MC0_CH0_CR_SC_GS_CFG_CMD_stretch_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_CMD_stretch_MAX;
      break;

    case GsmMccCmdGapRatio:
      Min = MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_MAX;
      break;

    case GsmMccAddrMirror:
      Min = MC0_CH0_CR_SC_GS_CFG_Address_mirror_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_Address_mirror_MAX;
      break;

    case GsmMccFreqPoint:
      Min = MC0_CH0_CR_SC_GS_CFG_frequency_point_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_frequency_point_MAX;
      break;

    case GsmMccLDimmMap:
      Min = MC0_MAD_INTRA_CH0_DIMM_L_MAP_MIN;
      Max = MC0_MAD_INTRA_CH0_DIMM_L_MAP_MAX;
      break;

    case GsmMccEccMode:
      Min = MC0_MAD_INTRA_CH0_ECC_MIN;
      Max = MC0_MAD_INTRA_CH0_ECC_MAX;
      // Wait 4 usec after enabling the ECC IO, needed by HW
      Wait = 4;
      break;

    case GsmMccAddrDecodeDdrType:
      Min = MC0_MAD_INTER_CHANNEL_DDR_TYPE_MIN;
      Max = MC0_MAD_INTER_CHANNEL_DDR_TYPE_MAX;
      break;

    case GsmMccSChannelSize:
      Min = MC0_MAD_INTER_CHANNEL_CH_S_SIZE_MIN;
      Max = MC0_MAD_INTER_CHANNEL_CH_S_SIZE_MAX;
      break;

    case GsmMccStackedChHash:
      if (Inputs->A0) {
        Min = MC0_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_A0_MIN;
        Max = MC0_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_A0_MAX;
      } else {
        // MC0_MAD_INTER_CHANNEL_STRUCT.STKD_MODE_CH_BITS does not exist on
        // TGL B0 and TGL P0
        IsDefined = FALSE;
      }
      break;

    case GsmMccChWidth:
      Min = MC0_MAD_INTER_CHANNEL_CH_WIDTH_MIN;
      Max = MC0_MAD_INTER_CHANNEL_CH_WIDTH_MAX;
      break;

    case GsmMccHalfCachelineMode:
      Min = MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_MIN;
      Max = MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_MAX;
      break;

    case GsmMccLDimmSize:
      Min = MC0_MAD_DIMM_CH0_DIMM_L_SIZE_MIN;
      Max = MC0_MAD_DIMM_CH0_DIMM_L_SIZE_MAX;
      break;

    case GsmMccLDimmDramWidth:
      Min = MC0_MAD_DIMM_CH0_DLW_MIN;
      Max = MC0_MAD_DIMM_CH0_DLW_MAX;
      break;

    case GsmMccLDimmRankCnt:
      Min = MC0_MAD_DIMM_CH0_DLNOR_MIN;
      Max = MC0_MAD_DIMM_CH0_DLNOR_MAX;
      break;

    case GsmMccSDimmSize:
      Min = MC0_MAD_DIMM_CH0_DIMM_S_SIZE_MIN;
      Max = MC0_MAD_DIMM_CH0_DIMM_S_SIZE_MAX;
      break;

    case GsmMccSDimmDramWidth:
      Min = MC0_MAD_DIMM_CH0_DSW_MIN;
      Max = MC0_MAD_DIMM_CH0_DSW_MAX;
      break;

    case GsmMccSDimmRankCnt:
      Min = MC0_MAD_DIMM_CH0_DSNOR_MIN;
      Max = MC0_MAD_DIMM_CH0_DSNOR_MAX;
      break;

    case GsmMccResetOnCmd:
      Min = MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_MAX;
      break;

    case GsmMccResetDelay:
      Min = MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_MAX;
      break;

    case GsmMccRankOccupancy:
      Min = MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_MIN;
      Max = MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_MAX;
      break;

    case GsmMccRefInterval:
      Min = MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_MIN;
      Max = MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_MAX;
      break;

    case GsmMccHashMask:
      Min = MC0_CHANNEL_HASH_HASH_MASK_MIN;
      Max = MC0_CHANNEL_HASH_HASH_MASK_MAX;
      break;

    case GsmMccLsbMaskBit:
      Min = MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_MIN;
      Max = MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_MAX;
      break;

    case GsmMccX8Device:
      Min = MC0_CH0_CR_SC_GS_CFG_x8_device_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_x8_device_MAX;
      break;

    case GsmMccMr2Shadow:
      Min = MC0_CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_MIN;
      Max = MC0_CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_MAX;
      break;

    case GsmMccSrtAvail:
      Min = MC0_CH0_CR_TC_MR2_SHADDOW_SRT_avail_MIN;
      Max = MC0_CH0_CR_TC_MR2_SHADDOW_SRT_avail_MAX;
      break;

    case GsmMccDdr4OneDpc:
      Min = MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_MIN;
      Max = MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_MAX;
      break;

    case GsmMccOdtOverride:
    case GsmMccOdtOn:
      Min = MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MIN;
      Max = MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MAX;
      break;

    case GsmMccCkeOverride:
    case GsmMccCkeOn:
      Min = MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MIN;
      Max = MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MAX;
      break;

    // For boolean parameters, we will group them here as their Min/Max is always 0/1
    case GsmMccRankInterleave:
    case GsmMccStackedMode:
    case GsmMccStackChMap:
      if (Inputs->A0) {
        Min = 0;
        Max = 1;
      } else {
        // MC0_MAD_INTER_CHANNEL_STRUCT.STKD_MODE and MC0_MAD_INTER_CHANNEL_STRUCT.STKD_MODE_CH1
        // do not exist on TGL B0 and TGL P0
        IsDefined = FALSE;
      }
      break;
    case GsmMccGear2:
    case GsmMccCpgcInOrder:
    case GsmMccCadbEnable:
    case GsmMccDeselectEnable:
    case GsmMccBusRetainOnBubble:
    case GsmMccLp4FifoRdWr:
    case GsmMccIgnoreCke:
    case GsmMccMaskCs:
    case GsmMccBlockXarb:
    case GsmMccEnableOdtMatrix:
    case GsmMccCmdTriStateDis:
    case GsmMccCmdTriStateDisTrain:
    case GsmMccEnhancedInterleave:
    case GsmMccLChannelMap:
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
    case GsmMccPbrDisOnHot:
    case GsmMccMprTrainDdrOn:
      Min = 0;
      Max = 1;
      break;

    // These are unused.  Need to finish HAL if these fields are accessed.
    case GsmMccDdrReset:
    case GsmMccSafeSr:

    default:
      IsDefined = FALSE;
      break;
  }

  if (!IsDefined) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Group %s(%d) has no limits defined\n", GsmGtDebugStrings[Group], Group);
    Status = mrcWrongInputParameter;
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
  This function returns CMI register limits.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - CMI group to access.
  @param[out] MinVal    - Return pointer for Minimum Value supported.
  @param[out] MaxVal    - Return pointer for Maximum Value supported.
  @param[out] WaitTime  - Return pointer for settle time required in microseconds.

  @retval MrcStatus
**/
MrcStatus
MrcGetCmiGroupLimits (
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
  case GsmCmiHashMask:
      Min = CMI_MEMORY_SLICE_HASH_HASH_MASK_MIN;
      Max = CMI_MEMORY_SLICE_HASH_HASH_MASK_MAX;
      break;

    case GsmCmiLsbMaskBit:
      Min = CMI_MEMORY_SLICE_HASH_HASH_LSB_MASK_BIT_MIN;
      Max = CMI_MEMORY_SLICE_HASH_HASH_LSB_MASK_BIT_MAX;
      break;

    case GsmCmiSMadSliceSize:
      Min = CMI_MAD_SLICE_MS_S_SIZE_MIN;
      Max = CMI_MAD_SLICE_MS_S_SIZE_MAX;
      break;

    case GsmCmiStackedMsHash:
      Min = CMI_MAD_SLICE_STKD_MODE_MS_BITS_MIN;
      Max = CMI_MAD_SLICE_STKD_MODE_MS_BITS_MAX;
      break;

    // For boolean parameters, we will group them here as their Min/Max is always 0/1
    case GsmCmiHashMode:
    case GsmCmiStackedMode:
    case GsmCmiStackMsMap:
    case GsmCmiLMadSliceMap:
      Min = 0;
      Max = 1;
      break;

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
  @param[in]  Controller  - Memory controller in the processor socket (0-based).
  @param[in]  Channel     - DDR Channel Number within the memory controller (0-based).
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
  IN  UINT32  const   Controller,
  IN  UINT32  const   Channel,
  IN  UINT32  const   Rank,
  IN  UINT32  const   Strobe,
  IN  UINT32  const   Bit,
  IN  UINT32  const   FreqIndex,
  OUT UINT32  *const  HashVal
  )
{
#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  MrcDebug  *Debug;
#endif
  MrcInput    *Inputs;
  MrcOutput   *Outputs;
  MrcStatus   Status;
  MrcDdrType  DdrType;
  UINT32      CrOffset;
  UINT32      LogicalIndex;
  UINT32      ChMod2;
  BOOLEAN     Ddr4;
  BOOLEAN     Lpddr4;
  BOOLEAN     Lpddr5;
  BOOLEAN     Gear2;
  MRC_REGISTER_HASH_STRUCT *HashPtr;

  static const UINT32 RoundtripDelayHsh[ROUNDTRIP_DELAY_MAX] = {
    MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_HSH, MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_HSH,
    MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_HSH, MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_HSH,
    MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_HSH, MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_HSH,
    MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_HSH, MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_HSH
  };
  static const UINT32 RxFlybyDelayHsh[2][MAX_RANK_IN_CHANNEL] = {
    {MCMISCS_READCFGCH01_RcvEnRank0ChADel_HSH, MCMISCS_READCFGCH01_RcvEnRank1ChADel_HSH,
     MCMISCS_READCFGCH01_RcvEnRank2ChADel_HSH, MCMISCS_READCFGCH01_RcvEnRank3ChADel_HSH}, // Channel 0
    {MCMISCS_READCFGCH01_RcvEnRank0ChBDel_HSH, MCMISCS_READCFGCH01_RcvEnRank1ChBDel_HSH,
     MCMISCS_READCFGCH01_RcvEnRank2ChBDel_HSH, MCMISCS_READCFGCH01_RcvEnRank3ChBDel_HSH}  // Channel 1
  };
  static const UINT32 RxFifoRdyDelay[2][MAX_RANK_IN_CHANNEL] ={
    {MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_HSH, MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChADel_HSH,
     MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChADel_HSH, MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChADel_HSH}, // Channel 0
    {MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChBDel_HSH, MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChBDel_HSH,
     MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChBDel_HSH, MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChBDel_HSH}  // Channel 1
  };
  static const UINT32 TxDqFifoRdEnFlyby[2][MAX_RANK_IN_CHANNEL] = {
    {MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChADel_HSH, MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChADel_HSH,
     MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChADel_HSH, MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChADel_HSH}, // Channel 0
    {MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChBDel_HSH, MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChBDel_HSH,
     MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChBDel_HSH, MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChBDel_HSH}  // Channel 1
  };

#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  Debug     = &MrcData->Outputs.Debug;
#endif
  Status    = mrcSuccess;
  HashPtr   = (MRC_REGISTER_HASH_STRUCT *) HashVal;
  CrOffset  = MRC_UINT32_MAX;
  Inputs    = &MrcData->Inputs;
  Outputs   = &MrcData->Outputs;
  DdrType   = Outputs->DdrType;
  Lpddr4    = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5    = (DdrType == MRC_DDR_TYPE_LPDDR5);
  Ddr4      = (DdrType == MRC_DDR_TYPE_DDR4);
  ChMod2    = Channel % 2;
  Gear2     = Outputs->Gear2;
  if ((Lpddr4 && (Outputs->Frequency == f1067)) || (Lpddr5 && (Outputs->Frequency == f1100))) {
    Gear2 = FALSE;
  }

  switch (Group) {
    case RecEnDelay:
      HashPtr->Data = DATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_HSH;
      break;

    case RxDqsNDelay:
      HashPtr->Data = DATA0CH0_CR_RXCONTROL0RANK0_RxDqsNDelayPi_HSH;
      break;

    case RxDqsPDelay:
      HashPtr->Data = DATA0CH0_CR_RXCONTROL0RANK0_RxDqsPDelayPi_HSH;
      break;

    case RxVref:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL5_RxVref_HSH;
      break;

    case RxVoc:
      HashPtr->Data = DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset0_HSH; //VrefOffset1?
      break;

    case RxVocUnmatched:
      HashPtr->Data = DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset1_HSH;
      break;

    // This is a sub-bitfield within ddrdata_cr_ddrcrdatacontrol4.RxEqRank[0-3], so we had to hack the HSH values to reflect this:
    // RxTap0:
    // 100000000000000000011111000 / 40000F8 -> Bits 0 : 3 rank 0
    // 100000100000000000011111000 / 41000F8 -> Bits 0 : 3 rank 1
    // 100001000000000000011111000 / 42000F8 -> Bits 0 : 3 rank 2
    // 100001100000000000011111000 / 43000F8 -> Bits 0 : 3 rank 3
    case RxTap0:
      switch (Rank) {
      default:
        Status = mrcWrongInputParameter;
        /*FALLTHROUGH*/
      case 0:
        HashPtr->Data = 0x40000F8;
        break;

      case 1:
        HashPtr->Data = 0x41000F8;
        break;

      case 2:
        HashPtr->Data = 0x42000F8;
        break;

      case 3:
        HashPtr->Data = 0x43000F8;
        break;
      }
      break;

    // This is a signed register, but we set absolute values to it (the sweep thus ends up being non-monotonic)
    // This is a sub-bitfield within ddrdata_cr_ddrcrdatacontrol4.RxEqRank[0-3], so we had to hack the HSH values to reflect this:
    // RxTap1:
    // 100000010000000000011111000 / 40800F8 -> Bits 4 : 7 rank 0
    // 100000110000000000011111000 / 41800F8 -> Bits 4 : 7 rank 1
    // 100001010000000000011111000 / 42800F8 -> Bits 4 : 7 rank 2
    // 100001110000000000011111000 / 43800F8 -> Bits 4 : 7 rank 3
    case RxTap1:
      switch (Rank) {
      default:
        Status = mrcWrongInputParameter;
        /*FALLTHROUGH*/
      case 0:
        HashPtr->Data = 0x40800F8;
        break;

      case 1:
        HashPtr->Data = 0x41800F8;
        break;

      case 2:
        HashPtr->Data = 0x42800F8;
        break;

      case 3:
        HashPtr->Data = 0x43800F8;
        break;
      }
      break;

    // This is a sub-bitfield within ddrdata_cr_ddrcrdatacontrol4.RxEqRank[0-3], so we had to hack the HSH values to reflect this:
    // RxC:
    // 10000000000000000011111000 / 20000F8 -> Bits 0 : 1 rank 0
    // 10000100000000000011111000 / 21000F8 -> Bits 0 : 1 rank 1
    // 10001000000000000011111000 / 22000F8 -> Bits 0 : 1 rank 2
    // 10001100000000000011111000 / 23000F8 -> Bits 0 : 1 rank 3
    case RxC:
      switch (Rank) {
      default:
        Status = mrcWrongInputParameter;
        /*FALLTHROUGH*/
      case 0:
        HashPtr->Data = 0x20000F8;
        break;

      case 1:
        HashPtr->Data = 0x21000F8;
        break;

      case 2:
        HashPtr->Data = 0x22000F8;
        break;

      case 3:
        HashPtr->Data = 0x23000F8;
        break;
      }
      break;

    // This is a sub-bitfield within ddrdata_cr_ddrcrdatacontrol4.RxEqRank[0-3], so we had to hack the HSH values to reflect this:
    // RxR:
    // 10000001000000000011111000 / 20400F8 -> Bits 2 : 3 rank 0
    // 10000101000000000011111000 / 21400F8 -> Bits 2 : 3 rank 1
    // 10001001000000000011111000 / 22400F8 -> Bits 2 : 3 rank 2
    // 10001101000000000011111000 / 23400F8 -> Bits 2 : 3 rank 3
    case RxR:
      switch (Rank) {
      default:
        Status = mrcWrongInputParameter;
        /*FALLTHROUGH*/
      case 0:
        HashPtr->Data = 0x20400F8;
        break;

      case 1:
        HashPtr->Data = 0x21400F8;
        break;

      case 2:
        HashPtr->Data = 0x22400F8;
        break;

      case 3:
        HashPtr->Data = 0x23400F8;
        break;
      }
      break;

    // This is a sub-bitfield within ddrdata_cr_ddrcrdatacontrol4.RxEqRank[0-3], so we had to hack the HSH values to reflect this:
    // RxEq:
    // 100000010000000000011111000 / 40800F8 -> Bits 4 : 7 rank 0
    // 100000110000000000011111000 / 41800F8 -> Bits 4 : 7 rank 1
    // 100001010000000000011111000 / 42800F8 -> Bits 4 : 7 rank 2
    // 100001110000000000011111000 / 43800F8 -> Bits 4 : 7 rank 3
    case RxEq:
      switch (Rank) {
        default:
          Status = mrcWrongInputParameter;
          /*FALLTHROUGH*/
        case 0:
          HashPtr->Data = 0x40800F8;
          break;

        case 1:
          HashPtr->Data = 0x41800F8;
          break;

        case 2:
          HashPtr->Data = 0x42800F8;
          break;

        case 3:
          HashPtr->Data = 0x43800F8;
          break;
      }
      break;

    case RxRankMuxDelay:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_HSH;
      break;

    case RxDqBitDelay:
      HashPtr->Data = DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskew_HSH;
      break;

    case RxDqBitOffset:
      HashPtr->Data = DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskewOffset_HSH;
      break;

    case TxDqsDelay:
      HashPtr->Data = DATA0CH0_CR_TXCONTROL0RANK0_TxDqsDelay_HSH;
      break;

    case TxDqDelay:
      HashPtr->Data = DATA0CH0_CR_TXCONTROL0RANK0_TxDqDelay_HSH;
      break;

    case TxEq:
      HashPtr->Data = DATA0CH0_CR_TXCONTROL0RANK0_TxEqualization_HSH;
      break;

    case CmdTxEq:
      HashPtr->Data = CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_HSH;
      break;

    case CtlTxEq:
      HashPtr->Data = CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_HSH;
      break;

    case RxVrefVttDecap:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_HSH;
      break;

    case RxVrefVddqDecap:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVddqProgMFC_HSH;
      break;

    case PanicVttDnLp:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_VttPanicCompDnLpMult_HSH;
      break;

    case VttGenStatusSelCount:
      HashPtr->Data = DDRVTT0_CR_DDRCRVTTGENSTATUS_SelCount_HSH;
      break;

    case VttGenStatusCount:
      HashPtr->Data = DDRVTT0_CR_DDRCRVTTGENSTATUS_Count_HSH;
      break;

    case RloadDqsDn:
      HashPtr->Data = DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_RloadDqs_HSH;
      break;

    case RxCben:
      HashPtr->Data = DLLDDRDATA0_CR_PITUNE_PiCbEn_HSH;
      break;

    case RxBiasCtl:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL5_BiasIrefAdj_HSH;
      break;

    case DataRxD0PiCb:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL6_rxd0picb_HSH;
      break;

    case DataSDllPiCb:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_HSH;
      break;

    case VccDllRxD0PiCb:
      HashPtr->Data = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_RxD0PiCB_HSH;
      break;

    case VccDllSDllPiCb:
      HashPtr->Data = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_SdllPiCB_HSH;
      break;

    case DqsOdtCompOffset:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL5_DqsOdtCompOffset_HSH;
      break;

    case TxRankMuxDelay:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_HSH;
      break;

    case TxDqsRankMuxDelay:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_HSH;
      break;

    case TxDqBitDelay:
      HashPtr->Data = DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDQPerBitDeskew_HSH;
      break;

    case TxDqsBitDelay:
      HashPtr->Data = DATA0CH0_CR_DDRDATADQSRANK0_TxDQSPerBitDeskew_HSH;
      break;

    case RecEnOffset:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_HSH;
      break;

    case RxDqsOffset:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_HSH;
      break;

    case RxVrefOffset:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_HSH;
      break;

    case TxDqsOffset:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_HSH;
      break;

    case TxDqOffset:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_HSH;
      break;

    case RoundTripDelay:
      if (Lpddr4 || Lpddr5){
        LogicalIndex = (2 * (Channel % 2)) + (4 * (Rank / 2)) + (Rank % 2);
      } else {
        LogicalIndex = Rank % 4;
      }
      if (LogicalIndex < ROUNDTRIP_DELAY_MAX) {
        HashPtr->Data = RoundtripDelayHsh[LogicalIndex];
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case RxFlybyDelay:
      if ((Rank >= MAX_RANK_IN_CHANNEL) || (ChMod2 > (sizeof (RxFlybyDelayHsh) / sizeof (RxFlybyDelayHsh[0])))) {
        Status = mrcWrongInputParameter;
      } else {
        HashPtr->Data = RxFlybyDelayHsh[ChMod2][Rank];
      }
      break;

    case RxIoTclDelay:
      HashPtr->Data = MCMISCS_READCFGCH0_tCL4RcvEn_HSH;
      break;

    case RxFifoRdEnFlybyDelay:
      if ((Rank >= MAX_RANK_IN_CHANNEL) || (ChMod2 > (sizeof (RxFlybyDelayHsh) / sizeof (RxFlybyDelayHsh[0])))) {
        Status = mrcWrongInputParameter;
      } else {
        HashPtr->Data = RxFifoRdyDelay[ChMod2][Rank];
        if (Gear2) {
          // In Gear2 the value in tCK is in bits [3:1], and bit [0] should be 0
          // In Gear1 we program the value as is, it has UI resolution
          HashPtr->Bits.BfOffset += 1;
          HashPtr->Bits.BfWidth -= 1;
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
      if ((Rank >= MAX_RANK_IN_CHANNEL) || (ChMod2 > (sizeof (RxFlybyDelayHsh) / sizeof (RxFlybyDelayHsh[0])))) {
        Status = mrcWrongInputParameter;
      } else {
        HashPtr->Data = TxDqFifoRdEnFlyby[ChMod2][Rank];
      }
      break;

    case SenseAmpDelay:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_HSH;
      break;

    case SenseAmpDuration:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_HSH;
      break;

    case McOdtDelay:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDelay_HSH;
      break;

    case McOdtDuration:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDuration_HSH;
      break;

    case DqsOdtDelay:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDelay_HSH;
      break;

    case DqsOdtDuration:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDuration_HSH;
      break;

    case RxDqsAmpOffset:
      HashPtr->Data = DATA0CH0_CR_DDRDATADQSRANK0_RxDQSVrefOffset_HSH;
      break;

    case RxDqsUnmatchedAmpOffset:
      HashPtr->Data = DATA0CH0_CR_DDRDATADQSRANK0_RxDqsUnMatVrefOffset_HSH;
      break;

    case CmdVref:
      if (Channel == 0) {
        HashPtr->Data = DDRVREF_CR_DDRCRVREFADJUST1_ca0Vref_HSH;
      } else {
        HashPtr->Data = DDRVREF_CR_DDRCRVREFADJUST1_ca1Vref_HSH;
      }
      break;

    case CmdGrpPi:
      HashPtr->Data = CH0CCC_CR_DDRCRCCCPICODING0_PiCode0_HSH;
      break;

    case ClkGrpPi:
      HashPtr->Data = CH0CCC_CR_DDRCRCCCPICODING1_PiCode3_HSH;
      break;

    case CtlGrpPi:
      if (Ddr4 || Lpddr4 || (Lpddr5 && (Inputs->Lp5CccConfig & (1 << Channel)))) {
        HashPtr->Data = (Rank == 0) ? CH0CCC_CR_DDRCRCCCPICODING0_PiCode2_HSH : CH0CCC_CR_DDRCRCCCPICODING0_PiCode1_HSH;
      } else if (Lpddr5) {
        // Ascending CCC
        HashPtr->Data = (Rank == 0) ? CH0CCC_CR_DDRCRCCCPICODING0_PiCode1_HSH : CH0CCC_CR_DDRCRCCCPICODING0_PiCode2_HSH;
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case CkeGrpPi:
      if (Ddr4) {
        HashPtr->Data = (Rank == 0) ? CH0CCC_CR_DDRCRCCCPICODING0_PiCode1_HSH : CH0CCC_CR_DDRCRCCCPICODING0_PiCode2_HSH;
      } else if (Lpddr4) {
        HashPtr->Data = CH0CCC_CR_DDRCRCCCPICODING1_PiCode4_HSH;
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case WckGrpPi:
      HashPtr->Data = CH0CCC_CR_DDRCRCCCPICODING1_PiCode4_HSH;
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

    case SCompBypassDq:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_HSH;
      break;

    case SCompBypassCmd:
      if (Inputs->UlxUlt) {
        HashPtr->Data = CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_HSH;
      } else {
        HashPtr->Data = CH2CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_P0_HSH;
      }
      break;

    case SCompBypassCtl:
      if (Inputs->UlxUlt) {
        HashPtr->Data = CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_HSH;
      } else {
        HashPtr->Data = CH2CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_P0_HSH;
      }
      break;

    case SCompBypassClk:
      if (Inputs->UlxUlt) {
        HashPtr->Data = CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_HSH;
      } else {
        HashPtr->Data = CH2CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_P0_HSH;
      }
      break;

    case SCompCodeDq:
      HashPtr->Data = DATA0CH0_CR_RCOMPDATA0_SlewRateComp_HSH;
      break;

    case SCompCodeCtl: // Same CR Layout
    case SCompCodeClk: // Same CR Layout
    case SCompCodeCmd:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCACOMP_Scomp_HSH;
      break;

    case TxRonUp:
      HashPtr->Data = DATA0CH0_CR_RCOMPDATA0_RcompDrvUp_HSH;
      break;

    case WrDSCodeUpCtl: // Same CR Layout
    case WrDSCodeUpClk: // Same CR Layout
    case WrDSCodeUpCmd:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCACOMP_RcompDrvUp_HSH;
      break;

    case TxRonDn:
      HashPtr->Data = DATA0CH0_CR_RCOMPDATA0_RcompDrvDown_HSH;
      break;

    case WrDSCodeDnCtl: // Same CR layout
    case WrDSCodeDnClk: // Same CR layout
    case WrDSCodeDnCmd:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCACOMP_RcompDrvDown_HSH;
      break;

    case TxTco:
      switch (Bit) {
      default:
        Status = mrcWrongInputParameter;
        /*FALLTHROUGH*/
      case 0:
        HashPtr->Data = DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_HSH;
        break;

      case 1:
        HashPtr->Data = DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit1_HSH;
        break;

      case 2:
        HashPtr->Data = DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit2_HSH;
        break;

      case 3:
        HashPtr->Data = DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit3_HSH;
        break;

      case 4:
        HashPtr->Data = DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit4_HSH;
        break;

      case 5:
        HashPtr->Data = DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_HSH;
        break;

      case 6:
        HashPtr->Data = DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_HSH;
        break;

      case 7:
        HashPtr->Data = DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_HSH;
        break;
      }
      break;

    case TxDqsTco:
      HashPtr->Data = DATA0CH0_CR_DDRDATADQSRANK0_DqsPfNrTcoDelay_HSH;
      break;

    case TcoCompCodeCtl: // Same CR layout
    case TcoCompCodeClk: // Same CR layout
    case TcoCompCodeCmd:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCACOMP_TcoComp_HSH;
      break;

    case DqOdtVrefUp:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqOdtVrefUp_HSH;
      break;

    case DqOdtVrefDn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqOdtVrefDn_HSH;
      break;

    case DqDrvVrefUp:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL4_DqDrvVrefUp_HSH;
      break;

    case DqDrvVrefDn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL3_DqDrvVrefDn_HSH;
      break;

    case CmdDrvVrefUp:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL2_CmdDrvVrefUp_HSH;
      break;

    case CmdDrvVrefDn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL3_CmdDrvVrefDn_HSH;
      break;

    case CtlDrvVrefUp:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL2_CtlDrvVrefUp_HSH;
      break;

    case CtlDrvVrefDn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL3_CtlDrvVrefDn_HSH;
      break;

    case ClkDrvVrefUp:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL2_ClkDrvVrefUp_HSH;
      break;

    case ClkDrvVrefDn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL3_ClkDrvVrefDn_HSH;
      break;

    case CompRcompOdtUp:
      HashPtr->Data = DATA0CH0_CR_RCOMPDATA1_RcompOdtUp_HSH;
      break;

    case CompRcompOdtDn:
      HashPtr->Data = DATA0CH0_CR_RCOMPDATA1_RcompOdtDown_HSH;
      break;

    case CtlSCompOffset:
    case CkeSCompOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_HSH;
      break;

    case CompOffsetVssHiFF:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATAOFFSETCOMP_VssHiFFCompOffset_HSH;
      break;

    case CtlRCompDrvUpOffset:
    case CkeRCompDrvUpOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_HSH;
      break;

    case CtlRCompDrvDownOffset:
    case CkeRCompDrvDownOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_HSH;
      break;

    case CmdSCompOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_HSH;
      break;

    case CmdRCompDrvUpOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_HSH;
      break;

    case CmdRCompDrvDownOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_HSH;
      break;
/*
    case ClkCompOnTheFlyUpdtEn: // @todo No TGL version found
      HashPtr->Data = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ClkCompOnTheFlyUpdtEn_HSH;
      break;
*/
    case ClkRCompDrvDownOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_HSH;
      break;

    case ClkRCompDrvUpOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_HSH;
      break;

    case ClkSCompOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_HSH;
      break;

    case VsxHiClkFFOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_HSH;
      break;

    case VsxHiCaFFOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_HSH;
      break;

    case VsxHiCtlFFOffset:
      HashPtr->Data = CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_HSH;
      break;

    case RxPerBitDeskewCal:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_HSH;
      break;

    case TxPerBitDeskewCal:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_TxPBDCalibration_HSH;
      break;

    case CccPerBitDeskewCal:
      HashPtr->Data = CH0CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_HSH;
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
    CrOffset = MrcGetDdrIoRegOffset (MrcData, Group, Socket, Controller, Channel, Rank, Strobe, Bit, FreqIndex);
  }

#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  if (Status != mrcSuccess) {
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Error! Hash is undefined. Group %s(%d) Channel %u Rank %u Strobe %u: 0x%x\n",
      GsmGtDebugStrings[Group], Group, Channel, Rank, Strobe, CrOffset);
  }
#endif // MRC_HAL_DEBUG

  HashPtr->Bits.Offset = CrOffset;

  return Status;
}

/**
  This function generates the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData     - Pointer to global data.
  @param[in]  Group       - DDRIO group to access.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel     - DDR Channel Number within the memory controller (0-based).
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
  IN  UINT32          const   Rank,
  IN  UINT32          const   Strobe,
  IN  UINT32          const   Bit,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  )
{
  MrcStatus Status;
#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  MrcDebug  *Debug;
#endif
  UINT32    CrOffset;
  MRC_REGISTER_HASH_STRUCT *HashPtr;
  MrcInput  *Inputs;

#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  Debug     = &MrcData->Outputs.Debug;
#endif
  Status    = mrcSuccess;
  HashPtr   = (MRC_REGISTER_HASH_STRUCT *) HashVal;
  CrOffset  = MRC_UINT32_MAX;
  Inputs    = &MrcData->Inputs;

  switch (Group) {
    case GsmIocWlWakeCyc:
      HashPtr->Data = DLLDDRDATA0_CR_DLLWEAKLOCK_wl_wakecycles_HSH;
      break;

    case GsmIocWlSleepCyclesAct:
      HashPtr->Data = DLLDDRDATA0_CR_DLLWEAKLOCK_WL_SleepCyclesAct_HSH;
      break;

    case GsmIocWlSleepCyclesLp:
      HashPtr->Data = DLLDDRDATA0_CR_DLLWEAKLOCK_WL_SleepCyclesLP_HSH;
      break;

    case GsmIocForceCmpUpdt:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_HSH;
      break;
/*
    case GsmIocWlLatency: // @todo No TGL version found
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_HSH;
      break;
*/
    case GsmIocNoDqInterleave:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_HSH;
      break;

    case GsmIocScramLpMode:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_HSH;
      break;

    case GsmIocScramDdr4Mode:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_HSH;
      break;

    case GsmIocScramDdr5Mode:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_HSH;
      break;

    case GsmIocScramGear1:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_HSH;
      break;

    case GsmIocDisClkGate:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_HSH;
      break;

    case GsmIocDisDataIdlClkGate:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_HSH;
      break;

    case GsmIocScramLp4Mode:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_HSH;
      break;

    case GsmIocScramLp5Mode:
      if (Inputs->UlxUlt) {
        HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_HSH;
      } else {
        HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_P0_HSH;
      }
      break;

    case GsmIocScramOvrdPeriodicToDvfsComp:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_HSH;
      break;

    case GsmIocLp5Wck2CkRatio:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_HSH;
      break;

    case GsmIocChNotPop:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_HSH;
      break;

    case GsmIocDisIosfSbClkGate:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_HSH;
      break;

    case GsmIocEccEn:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_P0_HSH;
      break;

    case GsmIocVccDllGear1:
      HashPtr->Data = DDRPHY_COMP_CR_VCCDLLDQSDELAY_Gear1_HSH;
      break;

    case GsmIocVccDllControlBypass_V:
      HashPtr->Data = DDRVCCDLL0_CR_DDRCRVCCDLLCONTROL_Bypass_HSH;
      break;

    case GsmIocVccDllControlSelCode_V:
      HashPtr->Data = DDRVCCDLL0_CR_DDRCRVCCDLLCONTROL_SelCode_HSH;
      break;

    case GsmIocVccDllControlTarget_V:
      HashPtr->Data = DDRVCCDLL0_CR_DDRCRVCCDLLCONTROL_Target_HSH;
      break;

    case GsmIocVccDllControlOpenLoop_V:
      HashPtr->Data = DDRVCCDLL0_CR_DDRCRVCCDLLCONTROL_OpenLoop_HSH;
      break;

    case GsmIocVsxHiControlSelCode_V:
      HashPtr->Data = DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_SelCode_HSH;
      break;

    case GsmIocVsxHiControlOpenLoop_V:
      HashPtr->Data = DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_OpenLoop_HSH;
      break;

    case GsmIocCccPiEn:
      if (Inputs->UlxUlt) {
        HashPtr->Data = CH0CCC_CR_DDRCRPINSUSED_PiEn_HSH;
      } else {
        HashPtr->Data = CH2CCC_CR_DDRCRPINSUSED_PiEn_P0_HSH;
      }
      break;

    case GsmIocCccPiEnOverride:
      if (Inputs->UlxUlt) {
        HashPtr->Data = CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_HSH;
      } else {
        HashPtr->Data = CH2CCC_CR_DDRCRPINSUSED_PiEnOvrd_P0_HSH;
      }
      break;

    case GsmIocDataOdtStaticDis:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_HSH;
      break;

    case GsmIocStrobeOdtStaticDis:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_DisableDqsOdtStatic_HSH;
      break;

    case GsmIocDataODTSingleSegEn:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL5_ODTSingleSegEn_HSH;
      break;

    case GsmIocDqsMaskPulseCnt:
      HashPtr->Data = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_HSH;
      break;

    case GsmIocDqsPulseCnt:
      HashPtr->Data = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_HSH;
      break;

    case GsmIocDqOverrideData:
      HashPtr->Data = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_HSH;
      break;

    case GsmIocDqOverrideEn:
      HashPtr->Data = DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_HSH;
      break;

    case GsmIocRankOverrideEn:
      HashPtr->Data = DATA0CH0_CR_DATATRAINFEEDBACK_RankOvrd_HSH;
      break;

    case GsmIocRankOverrideVal:
      HashPtr->Data = DATA0CH0_CR_DATATRAINFEEDBACK_RankValue_HSH;
      break;

    case GsmIocDataCtlGear1:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_HSH;
      break;

    case GsmIocDataWrPreamble:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_HSH;
      break;

    case GsmIocTxOn:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_HSH;
      break;

    case GsmIocRxDisable:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_HSH;
      break;

    case GsmIocSenseAmpMode:
      HashPtr->Data = DATA0CH0_CR_DATATRAINFEEDBACK_SenseampTrainingMode_HSH;
      break;

    case GsmIocCaTrainingMode:
      HashPtr->Data = DATA0CH0_CR_DATATRAINFEEDBACK_CATrainingMode_HSH;
      break;

    case GsmIocDataTrainFeedback:
      HashPtr->Data = DATA0CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_HSH;
      break;

    case GsmIocRxAmpOffsetEn:
      HashPtr->Data = DATA0CH0_CR_DATATRAINFEEDBACK_RxAmpOffsetEn_HSH;
      break;

    case GsmIocReadLevelMode:
      HashPtr->Data = DATA0CH0_CR_DATATRAINFEEDBACK_RLTrainingMode_HSH;
      break;

    case GsmIocWriteLevelMode:
      HashPtr->Data = DATA0CH0_CR_DATATRAINFEEDBACK_WLTrainingMode_HSH;
      break;

    case GsmIocReadDqDqsMode:
      HashPtr->Data = DATA0CH0_CR_DATATRAINFEEDBACK_RxTrainingMode_HSH;
      break;

    case GsmIocForceOdtOn:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_HSH;
      break;

    case GsmIocRxPiPwrDnDis:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL5_RxPiOn_HSH;
      break;

    case GsmIocTxPiPwrDnDis:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_HSH;
      break;

    case GsmIocInternalClocksOn:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_HSH;
      break;

    case GsmIocDataDqsOdtParkMode:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_HSH;
      break;

    case GsmIocDataDqsNParkLow:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_HSH;
      break;

    case GsmIocTxDisable:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_HSH;
      break;

    case GsmIocDllMask:
      HashPtr->Data = DLLDDRDATA0_CR_DLLWEAKLOCK_DLLMask0_HSH;
      break;

    case GsmIocSdllSegmentDisable:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_HSH;
      break;

    case GsmIocRXDeskewForceOn:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL1_RXDeskewForceOn_HSH;
      break;

    case GsmIocCmdDrvVref200ohm:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL2_Cmd200VrefDn_HSH;
      break;

    case GsmIocDllWeakLock:
      HashPtr->Data = DLLDDRDATA0_CR_DLLWEAKLOCK_DllWeakLock0_HSH;
      break;

    case GsmIocDllWeakLock1:
      HashPtr->Data = DLLDDRDATA0_CR_DLLWEAKLOCK_DllWeakLock1_HSH;
      break;

    case GsmIocRxClkStg:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_HSH;
      break;

    case GsmIocDataRxBurstLen:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_RxBurstLen_HSH;
      break;

    case GsmIocEnDqsNRcvEn:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_EnDqsNRcvEn_HSH;
      break;

    case GsmIocRxVrefMFC:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_HSH;
      break;
/*
    case GsmIocVrefPwrDnEn: // @todo No TGL version found
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_HSH;
      break;
*/

    case GsmIocConstZTxEqEn:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_HSH;
      break;

    case GsmIocForceRxAmpOn:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_HSH;
      break;

    case GsmIocDqSlewDlyByPass:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_HSH;
      break;

    case GsmIocWlLongDelEn:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_HSH;
      break;

    case GsmIocBiasPMCtrl:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_HSH;
      break;

    case GsmIocDataOdtMode:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_HSH;
      break;

    case GsmIocFFCodeIdleOffset:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeIdleOffset_HSH;
      break;

    case GsmIocFFCodeWeakOffset:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeWeakOffset_HSH;
      break;

    case GsmIocFFCodePiOffset:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodePIOffset_HSH;
      break;

    case GsmIocFFCodeCCCDistOffset:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeCCCDistOffset_HSH;
      break;

    case GsmIocFFCodePBDOffset:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodePBDOffset_HSH;
      break;

    case GsmIocFFCodeWriteOffset:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeWriteOffset_HSH;
      break;

    case GsmIocFFCodeReadOffset:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_FFCodeReadOffset_HSH;
      break;

    case GsmIocCapCancelCodeIdle:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_CapCancelCodeIdle_HSH;
      break;

    case GsmIocCapCancelCodePBD:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_CapCancelCodePBD_HSH;
      break;

    case GsmIocCapCancelCodeWrite:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_CapCancelCodeWrite_HSH;
      break;

    case GsmIocCapCancelCodeRead:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_CapCancelCodeRead_HSH;
      break;

    case GsmIocCapCancelCodePi:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_CapCancelCodePi_HSH;
      break;

    case GsmIocVssHiFFCodeIdle:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodeIdle_HSH;
      break;

    case GsmIocVssHiFFCodeWrite:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodeWrite_HSH;
      break;

    case GsmIocVssHiFFCodeRead:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodeRead_HSH;
      break;

    case GsmIocVssHiFFCodePBD:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodePBD_HSH;
      break;

    case GsmIocVssHiFFCodePi:
      HashPtr->Data = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_VsxHiFFCodePi_HSH;
      break;

    case GsmIocDataInvertNibble:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL5_DataInvertNibble_HSH;
      break;

    case GsmIocEnableSpineGate:
      HashPtr->Data = MCMISCS_SPINEGATING_EnableSpineGate_HSH;
      break;

    case GsmIocDataDqOdtParkMode:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_HSH;
      break;

    case GsmIocTxEqDis:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL2_TxEqDis_HSH;
      break;

    case GsmIocVccDllRxDeskewCal:
      HashPtr->Data = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_RxDeskewCal_HSH;
      break;

    case GsmIocVccDllTxDeskewCal:
      HashPtr->Data = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_TxDeskewCal_HSH;
      break;

    case GsmIocVccDllCccDeskewCal:
      HashPtr->Data = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_CCCDeskewCal_HSH;
      break;
/*
    case GsmIocRxTypeSelect: // @todo No TGL version found
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL4_rxsel_HSH;
      break;
*/

    case GsmIocIoReset:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_HSH;
      break;

    case GsmIocCmdVrefConverge:
      if (Inputs->UlxUlt) {
        if (Channel == 0) {
          HashPtr->Data = DDRVREF_CR_DDRCRVREFADJUST2_ca0SlowBW_HSH;
        } else {
          HashPtr->Data = DDRVREF_CR_DDRCRVREFADJUST2_ca1SlowBW_HSH;
        }
      } else {
        //
        // TGL P0 has four instances of this register field.
        // Their usage in this GetSet will be implemented later
        //
        // DDRVREF_CR_DDRCRVREFADJUST2_ca00SlowBW_P0_HSH
        // DDRVREF_CR_DDRCRVREFADJUST2_ca01SlowBW_P0_HSH
        // DDRVREF_CR_DDRCRVREFADJUST2_ca10SlowBW_P0_HSH
        // DDRVREF_CR_DDRCRVREFADJUST2_ca11SlowBW_P0_HSH
        //
        Status = mrcWrongInputParameter;
      }
      break;

    case GsmIocCompClkOn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_CompClkOn_HSH;
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
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DisableOdtStatic_HSH;
      break;

    case GsmIocCompVddqOdtEn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL0_EnVddqOdt_HSH;
      break;

    case GsmIocCompVttOdtEn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL0_EnVttOdt_HSH;
      break;

    case GsmIocVttPanicCompUpMult:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_VttPanicCompUp0Mult_HSH;
      break;

    case GsmIocVttPanicCompDnMult:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_VttPanicCompDn0Mult_HSH;
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

    case GsmIocRxVocMode:
      HashPtr->Data = DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_HSH;
      break;

    //@todo case GsmIocDccTrainingMode:
    //@todo   HashPtr->Data = MCMISCS_DCCCONTROL0_TrainingMode_HSH;
    //@todo   break;

    //@todo case GsmIocDccTrainingDone:
    //@todo   HashPtr->Data = MCMISCS_DCCCONTROL0_TrainingDone_HSH;
    //@todo   break;

    //@todo case GsmIocDccDrain:
    //@todo   HashPtr->Data = MCMISCS_DCCCONTROL0_Drain_HSH;
    //@todo   break;

    //@todo case GsmIocDccActiveClks:
    //@todo   HashPtr->Data = MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_HSH;
    //@todo   break;

    //@todo case GsmIocDccActiveBytes:
    //@todo   HashPtr->Data = MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_HSH;
    //@todo   break;

    //@todo case GsmIocDccDcoCompEn:
    //@todo   HashPtr->Data = MCMISCS_DCCMAINFSMCONTROL0_DcoCompEn_HSH;
    //@todo   break;

    //@todo case GsmIocDccClkTrainVal:
    //@todo   // Rank is MRC_IGNORE_ARG, Strobe is the one that is valid
    //@todo   if (Strobe == 0) {
    //@todo     HashPtr->Data = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Clk0DccVal_HSH;
    //@todo   } else if (Strobe == 1) {
    //@todo     HashPtr->Data = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Clk1DccVal_HSH;
    //@todo   } else if (Strobe == 2) {
    //@todo     //@todo H/S sku code
    //@todo     Status = mrcWrongInputParameter;
    //@todo   } else {
    //@todo     //@todo H/S sku code
    //@todo     Status = mrcWrongInputParameter;
    //@todo   }
    //@todo   break;

    //@todo case GsmIocDccDataTrainDqsVal:
    //@todo   HashPtr->Data = DATA0CH0_CR_DCCDATATRAINVAL1RANK0_DqsDccVal_HSH;
    //@todo   break;

    // These are unused.  Need to finish HAL if these fields are accessed.
    default:
      Status = mrcWrongInputParameter;
      break;
  }

#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  if (Status != mrcSuccess) {
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Hash is undefined. Group %s(%d) Channel %u Rank %u Strobe %u\n",
      GsmGtDebugStrings[Group], Group, Channel, Rank, Strobe);
  }
#endif // MRC_HAL_DEBUG
  if (Status == mrcSuccess) {
    CrOffset = MrcGetDdrIoConfigOffsets (MrcData, Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex);
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
  IN  UINT32          const   Controller,
  IN  UINT32          const   Channel,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  )
{
  MrcStatus Status;
#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  MrcDebug  *Debug;
#endif
  MRC_REGISTER_HASH_STRUCT *HashPtr;
  UINT32    CrOffset;
  MrcInput  *Inputs;

#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  Debug   = &MrcData->Outputs.Debug;
#endif
  Status   = mrcSuccess;
  HashPtr  = (MRC_REGISTER_HASH_STRUCT *) HashVal;
  CrOffset = MRC_UINT32_MAX;
  Inputs   = &MrcData->Inputs;

  switch (Group) {
    case GsmMctRCD:
      HashPtr->Data = MC0_CH0_CR_TC_PRE_tRCD_HSH;
      break;

    case GsmMctRP:
      HashPtr->Data = MC0_CH0_CR_TC_PRE_tRP_HSH;
      break;

    case GsmMctRFCpb:
      HashPtr->Data = MC0_CH0_CR_SC_PBR_tRFCpb_HSH;
      break;

    case GsmMctRPabExt:
      HashPtr->Data = MC0_CH0_CR_TC_PRE_tRPab_ext_HSH;
      break;

    case GsmMctRAS:
      HashPtr->Data = MC0_CH0_CR_TC_PRE_tRAS_HSH;
      break;

    case GsmMctRDPRE:
      HashPtr->Data = MC0_CH0_CR_TC_PRE_tRDPRE_HSH;
      break;

    case GsmMctPPD:
      HashPtr->Data = MC0_CH0_CR_TC_PRE_tPPD_HSH;
      break;

    case GsmMctWRPRE:
      HashPtr->Data = MC0_CH0_CR_TC_PRE_tWRPRE_HSH;
      break;

    case GsmMctFAW:
      HashPtr->Data = MC0_CH0_CR_TC_ACT_tFAW_HSH;
      break;

    case GsmMctRRDsg:
      HashPtr->Data = MC0_CH0_CR_TC_ACT_tRRD_sg_HSH;
      break;

    case GsmMctRRDdg:
      HashPtr->Data = MC0_CH0_CR_TC_ACT_tRRD_dg_HSH;
      break;

    case GsmMctLpDeratingExt:
      if (Inputs->UlxUlt) {
        HashPtr->Data = MC0_CH0_CR_TC_ACT_derating_ext_HSH;
      } else {
        HashPtr->Data = MC0_CH0_CR_TC_ACT_derating_ext_P0_HSH;
      }
      break;

    case GsmMctRDRDsg:
      HashPtr->Data = MC0_CH0_CR_TC_RDRD_tRDRD_sg_HSH;
      break;

    case GsmMctRDRDdg:
      HashPtr->Data = MC0_CH0_CR_TC_RDRD_tRDRD_dg_HSH;
      break;

    case GsmMctRDRDdr:
      HashPtr->Data = MC0_CH0_CR_TC_RDRD_tRDRD_dr_HSH;
      break;

    case GsmMctRDRDdd:
      HashPtr->Data = MC0_CH0_CR_TC_RDRD_tRDRD_dd_HSH;
      break;

    case GsmMctRDWRsg:
      HashPtr->Data = MC0_CH0_CR_TC_RDWR_tRDWR_sg_HSH;
      break;

    case GsmMctRDWRdg:
      HashPtr->Data = MC0_CH0_CR_TC_RDWR_tRDWR_dg_HSH;
      break;

    case GsmMctRDWRdr:
      HashPtr->Data = MC0_CH0_CR_TC_RDWR_tRDWR_dr_HSH;
      break;

    case GsmMctRDWRdd:
      HashPtr->Data = MC0_CH0_CR_TC_RDWR_tRDWR_dd_HSH;
      break;

    case GsmMctWRRDsg:
      HashPtr->Data = MC0_CH0_CR_TC_WRRD_tWRRD_sg_HSH;
      break;

    case GsmMctWRRDdg:
      HashPtr->Data = MC0_CH0_CR_TC_WRRD_tWRRD_dg_HSH;
      break;

    case GsmMctWRRDdr:
      HashPtr->Data = MC0_CH0_CR_TC_WRRD_tWRRD_dr_HSH;
      break;

    case GsmMctWRRDdd:
      HashPtr->Data = MC0_CH0_CR_TC_WRRD_tWRRD_dd_HSH;
      break;

    case GsmMctWRWRsg:
      if (Inputs->UlxUlt) {
        HashPtr->Data = MC0_CH0_CR_TC_WRWR_tWRWR_sg_HSH;
      } else {
        HashPtr->Data = MC0_CH0_CR_TC_WRWR_tWRWR_sg_P0_HSH;
      }
      break;

    case GsmMctWRWRdg:
      HashPtr->Data = MC0_CH0_CR_TC_WRWR_tWRWR_dg_HSH;
      break;

    case GsmMctWRWRdr:
      HashPtr->Data = MC0_CH0_CR_TC_WRWR_tWRWR_dr_HSH;
      break;

    case GsmMctWRWRdd:
      HashPtr->Data = MC0_CH0_CR_TC_WRWR_tWRWR_dd_HSH;
      break;

    case GsmMctOdtRdDuration:
      HashPtr->Data = MC0_CH0_CR_TC_ODT_ODT_read_duration_HSH;
      break;

    case GsmMctOdtRdDelay:
      HashPtr->Data = MC0_CH0_CR_TC_ODT_ODT_Read_Delay_HSH;
      break;

    case GsmMctWrEarlyOdt:
      HashPtr->Data = MC0_CH0_CR_TC_ODT_Write_Early_ODT_HSH;
      break;

    case GsmMctOdtWrDuration:
      HashPtr->Data = MC0_CH0_CR_TC_ODT_ODT_write_duration_HSH;
      break;

    case GsmMctOdtWrDelay:
      HashPtr->Data = MC0_CH0_CR_TC_ODT_ODT_Write_Delay_HSH;
      break;

    case GsmMctCL:
      HashPtr->Data = MC0_CH0_CR_TC_ODT_tCL_HSH;
      break;

    case GsmMctCWL:
      HashPtr->Data = MC0_CH0_CR_TC_ODT_tCWL_HSH;
      break;

    case GsmMctAONPD:
      HashPtr->Data = MC0_CH0_CR_TC_ODT_tAONPD_HSH;
      break;

    case GsmMctCKE:
      HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tCKE_HSH;
      break;

    case GsmMctXP:
      HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tXP_HSH;
      break;

    case GsmMctXPDLL:
      HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tXPDLL_HSH;
      break;

    case GsmMctPRPDEN:
      if (Inputs->UlxUlt) {
        if (Inputs->A0) {
          HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tPRPDEN_A0_HSH;
        } else {
          HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tPRPDEN_HSH;
        }
      } else {
        HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tPRPDEN_P0_HSH;
      }
      break;

    case GsmMctRDPDEN:
      HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tRDPDEN_HSH;
      break;

    case GsmMctWRPDEN:
      HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tWRPDEN_HSH;
      break;

    case GsmMctCA2CS:
      if (Inputs->UlxUlt) {
        HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tCA2CS_HSH;
      } else {
        HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tCA2CS_P0_HSH;
      }
      break;

    case GsmMctCSL:
      if (Inputs->UlxUlt) {
        HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tCSL_HSH;
      } else {
        HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tCSL_P0_HSH;
      }
      break;

    case GsmMctCSH:
      if (Inputs->UlxUlt) {
        HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tCSH_HSH;
      } else {
        HashPtr->Data = MC0_CH0_CR_TC_PWRDN_tCSH_P0_HSH;
      }
      break;

    case GsmMctXSDLL:
      HashPtr->Data = MC0_CH0_CR_TC_SRFTP_tXSDLL_HSH;
      break;

    case GsmMctXSR:
      HashPtr->Data = MC0_CH0_CR_TC_SREXITTP_tXSR_HSH;
      break;

    case GsmMctZQOPER:
      if (Inputs->UlxUlt) {
        HashPtr->Data = MC0_CH0_CR_TC_SRFTP_tZQOPER_HSH;
      } else {
        HashPtr->Data = MC0_CH0_CR_TC_SRFTP_tZQOPER_P0_HSH;
      }
      break;

    case GsmMctMOD:
      if (Inputs->UlxUlt) {
        HashPtr->Data = MC0_CH0_CR_TC_SRFTP_tMOD_HSH;
      } else {
        HashPtr->Data = MC0_CH0_CR_TC_SRFTP_tMOD_P0_HSH;
      }
      break;

    case GsmMctZQCAL:
      HashPtr->Data = MC0_CH0_CR_TC_ZQCAL_tZQCAL_HSH;
      break;

    case GsmMctZQCS:
      HashPtr->Data = MC0_CH0_CR_TC_ZQCAL_tZQCS_HSH;
      break;

    case GsmMctZQCSPeriod:
      HashPtr->Data = MC0_CH0_CR_TC_ZQCAL_ZQCS_period_HSH;
      break;

    case GsmMctCPDED:
      if (Inputs->UlxUlt) {
        HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_tCPDED_HSH;
      } else {
        HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_tCPDED_P0_HSH;
      }
      break;

    case GsmMctCAL:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_tCAL_HSH;
      break;

    case GsmMctCKCKEH:
      if (Inputs->UlxUlt) {
        HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_ck_to_cke_HSH;
      } else {
        HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_ck_to_cke_P0_HSH;
      }
      break;

    case GsmMctCSCKEH:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_cs_to_cke_HSH;
      break;

    case GsmMctSrIdle:
      HashPtr->Data = MC0_PM_SREF_CONFIG_Idle_timer_HSH;
      break;

    case GsmMctREFI:
      HashPtr->Data = MC0_CH0_CR_TC_RFTP_tREFI_HSH;
      break;

    case GsmMctRFC:
      HashPtr->Data = MC0_CH0_CR_TC_RFTP_tRFC_HSH;
      break;

    case GsmMctOrefRi:
      HashPtr->Data = MC0_CH0_CR_TC_RFP_OREF_RI_HSH;
      break;

    case GsmMctRefreshHpWm:
      HashPtr->Data = MC0_CH0_CR_TC_RFP_Refresh_HP_WM_HSH;
      break;

    case GsmMctRefreshPanicWm:
      HashPtr->Data = MC0_CH0_CR_TC_RFP_Refresh_panic_wm_HSH;
      break;

    case GsmMctREFIx9:
      if (Inputs->UlxUlt) {
        HashPtr->Data = MC0_CH0_CR_TC_RFP_tREFIx9_HSH;
      } else {
        HashPtr->Data = MC0_CH0_CR_TC_RFP_tREFIx9_P0_HSH;
      }
      break;

    default:
      MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Hash undefined. Group %s(%d) Channel %u\n", GsmGtDebugStrings[Group], Group,Channel);
      HashPtr->Data = MRC_UINT32_MAX;
      Status = mrcWrongInputParameter;
      break;
  }

  if (Status == mrcSuccess) {
    CrOffset = MrcGetMcTimingRegOffset (MrcData, Group, Socket, Controller, Channel, FreqIndex);
  }

  HashPtr->Bits.Offset = CrOffset;

  return Status;
}

/**
  This function returns the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData     - Pointer to global data.
  @param[in]  Group       - MC Timing group to access.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Controller  - Controller number within the processor socket (0-based).
  @param[in]  Channel     - DDR Channel Number within the controller (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] HashVal     - Pointer to return the MMIO access instruction.

  @retval MrcStatus
**/
MrcStatus
MrcGetMcConfigHash (
  IN  MrcParameters   *const  MrcData,
  IN  GSM_GT          const   Group,
  IN  UINT32          const   Socket,
  IN  UINT32          const   Controller,
  IN  UINT32          const   Channel,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  )
{
  MrcStatus Status;
#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  MrcDebug  *Debug;
#endif
  MRC_REGISTER_HASH_STRUCT *HashPtr;
  UINT32    CrOffset;
  BOOLEAN   IsDefined;
  MrcInput  *Inputs;

#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  Debug   = &MrcData->Outputs.Debug;
#endif
  Status       = mrcSuccess;
  HashPtr      = (MRC_REGISTER_HASH_STRUCT *) HashVal;
  CrOffset     = MRC_UINT32_MAX;
  IsDefined    = TRUE;
  Inputs       = &MrcData->Inputs;

  switch (Group) {
    case GsmMccDramType:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_DRAM_technology_HSH;
      break;

    case GsmMccCmdStretch:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_CMD_stretch_HSH;
      break;

    case GsmMccCmdGapRatio:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_HSH;
      break;

    case GsmMccAddrMirror:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_Address_mirror_HSH;
      break;

    case GsmMccCmdTriStateDis:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_disable_tristate_HSH;
      break;

    case GsmMccCmdTriStateDisTrain:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_HSH;
      break;

    case GsmMccFreqPoint:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_frequency_point_HSH;
      break;

    case GsmMccEnableOdtMatrix:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_HSH;
      break;

    case GsmMccX8Device:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_x8_device_HSH;
      break;

    case GsmMccGear2:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_gear2_HSH;
      break;

    case GsmMccDdr4OneDpc:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_HSH;
      break;

    case GsmMccLDimmMap:
      HashPtr->Data = MC0_MAD_INTRA_CH0_DIMM_L_MAP_HSH;
      break;

    case GsmMccRankInterleave:
      if (Inputs->A0) {
        HashPtr->Data = MC0_MAD_INTRA_CH0_RI_A0_HSH;
      } else {
        // MC0_MAD_INTRA_CH0_STRUCT.RI
        // does not exist on TGL B0 an dTGL P0
        IsDefined = FALSE;
      }
      break;

    case GsmMccEnhancedInterleave:
      HashPtr->Data = MC0_MAD_INTRA_CH0_EIM_HSH;
      break;

    case GsmMccEccMode:
      HashPtr->Data = MC0_MAD_INTRA_CH0_ECC_HSH;
      break;

    case GsmMccAddrDecodeDdrType:
      HashPtr->Data = MC0_MAD_INTER_CHANNEL_DDR_TYPE_HSH;
      break;

    case GsmMccStackedMode:
      if (Inputs->A0) {
        HashPtr->Data = MC0_MAD_INTER_CHANNEL_STKD_MODE_A0_HSH;
      } else {
        // MC0_MAD_INTER_CHANNEL_STRUCT.STKD_MODE
        // does not exist on TGL B0 and TGL P0
        IsDefined = FALSE;
      }
      break;

    case GsmMccStackChMap:
      if (Inputs->A0) {
        HashPtr->Data = MC0_MAD_INTER_CHANNEL_STKD_MODE_CH1_A0_HSH;
      } else {
        // MC0_MAD_INTER_CHANNEL_STRUCT.STKD_MODE_CH1
        // does not exist on TGL B0 and TGL P0
        IsDefined = FALSE;
      }
      break;

    case GsmMccLChannelMap:
      HashPtr->Data = MC0_MAD_INTER_CHANNEL_CH_L_MAP_HSH;
      break;

    case GsmMccSChannelSize:
      HashPtr->Data = MC0_MAD_INTER_CHANNEL_CH_S_SIZE_HSH;
      break;

    case GsmMccStackedChHash:
      if (Inputs->A0) {
        HashPtr->Data = MC0_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_A0_HSH;
      } else {
        // MC0_MAD_INTER_CHANNEL_STRUCT.STKD_MODE_CH_BITS
        // does not exist on TGL B0 and TGL P0
        IsDefined = FALSE;
      }
      break;

    case GsmMccChWidth:
      HashPtr->Data = MC0_MAD_INTER_CHANNEL_CH_WIDTH_HSH;
      break;

    case GsmMccHalfCachelineMode:
      HashPtr->Data = MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_HSH;
      break;

    case GsmMccLDimmSize:
      HashPtr->Data = MC0_MAD_DIMM_CH0_DIMM_L_SIZE_HSH;
      break;

    case GsmMccLDimmDramWidth:
      HashPtr->Data = MC0_MAD_DIMM_CH0_DLW_HSH;
      break;

    case GsmMccLDimmRankCnt:
      HashPtr->Data = MC0_MAD_DIMM_CH0_DLNOR_HSH;
      break;

    case GsmMccSDimmSize:
      HashPtr->Data = MC0_MAD_DIMM_CH0_DIMM_S_SIZE_HSH;
      break;

    case GsmMccSDimmDramWidth:
      HashPtr->Data = MC0_MAD_DIMM_CH0_DSW_HSH;
      break;

    case GsmMccSDimmRankCnt:
      HashPtr->Data = MC0_MAD_DIMM_CH0_DSNOR_HSH;
      break;

    case GsmMccSaveFreqPoint:
      switch (FreqIndex) {
        case 0:
          HashPtr->Data = MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_HSH;
          break;

        case 1:
          HashPtr->Data = MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_HSH;
          break;

        case 2:
          HashPtr->Data = MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_HSH;
          break;

        case 3:
          HashPtr->Data = MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_HSH;
          break;

        default:
          Status = mrcWrongInputParameter;
          break;
      }
      break;

    case GsmMccEnableSr:
      HashPtr->Data = MC0_PM_SREF_CONFIG_SR_Enable_HSH;
      break;

    case GsmMccEnableRefresh:
      HashPtr->Data = MC0_MC_INIT_STATE_G_refresh_enable_HSH;
      break;

    case GsmMccMcInitDoneAck:
      HashPtr->Data = MC0_MC_INIT_STATE_G_mc_init_done_ack_HSH;
      break;

    case GsmMccMrcDone:
      HashPtr->Data = MC0_MC_INIT_STATE_G_mrc_done_HSH;
      break;

    case GsmMccEnableDclk:
      HashPtr->Data = MC0_MC_INIT_STATE_G_dclk_enable_HSH;
      break;

    case GsmMccPureSrx:
      HashPtr->Data = MC0_MC_INIT_STATE_G_pure_srx_HSH;
      break;

    case GsmMccLp4FifoRdWr:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_HSH;
      break;

    case GsmMccIgnoreCke:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_HSH;
      break;

    case GsmMccMaskCs:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_HSH;
      break;

    case GsmMccCpgcInOrder:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_HSH;
      break;

    case GsmMccCadbEnable:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_HSH;
      break;

    case GsmMccDeselectEnable:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_HSH;
      break;

    case GsmMccBusRetainOnBubble:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_HSH;
      break;

    case GsmMccBlockXarb:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_HSH;
      break;

    case GsmMccResetOnCmd:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_HSH;
      break;

    case GsmMccResetDelay:
      HashPtr->Data = MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_HSH;
      break;

    case GsmMccRankOccupancy:
      HashPtr->Data = MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_HSH;
      break;

    case GsmMccRefInterval:
      HashPtr->Data = MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_HSH;
      break;

    case GsmMccRefStaggerEn:
      HashPtr->Data = MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_HSH;
      break;

    case GsmMccRefStaggerMode:
      HashPtr->Data = MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_HSH;
      break;

    case GsmMccDisableStolenRefresh:
      HashPtr->Data = MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_HSH;
      break;

    case GsmMccEnRefTypeDisplay:
      HashPtr->Data = MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_HSH;
      break;

    case GsmMccHashMask:
      HashPtr->Data = MC0_CHANNEL_HASH_HASH_MASK_HSH;
      break;

    case GsmMccLsbMaskBit:
      HashPtr->Data = MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_HSH;
      break;

    case GsmMccHashMode:
      HashPtr->Data = MC0_CHANNEL_HASH_HASH_MODE_HSH;
      break;

    case GsmMccMr2Shadow:
      HashPtr->Data = MC0_CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_HSH;
      break;

    case GsmMccSrtAvail:
      HashPtr->Data = MC0_CH0_CR_TC_MR2_SHADDOW_SRT_avail_HSH;
      break;

    case GsmMccDisableCkTristate:
      HashPtr->Data = MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_HSH;
      break;

    case GsmMccPbrDis:
      HashPtr->Data = MC0_CH0_CR_SC_PBR_PBR_Disable_HSH;
      break;

    case GsmMccPbrDisOnHot:
      HashPtr->Data = MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_HSH;
      break;

    case GsmMccOdtOverride:
      HashPtr->Data = MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_HSH;
      break;

    case GsmMccOdtOn:
      HashPtr->Data = MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_HSH;
      break;

    case GsmMccMprTrainDdrOn:
      HashPtr->Data = MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_HSH;
      break;

    case GsmMccCkeOverride:
      HashPtr->Data = MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_HSH;
      break;

    case GsmMccCkeOn:
      HashPtr->Data = MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_HSH;
      break;

    // These are unused.  Need to finish HAL if these fields are accessed.
    case GsmMccDdrReset:
    case GsmMccSafeSr:

    default:
      IsDefined = FALSE;
      break;
  }

  if(!IsDefined) {
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Hash undefined. Group %s(%d) Channel %u\n", GsmGtDebugStrings[Group], Group, Channel);
    HashPtr->Data = MRC_UINT32_MAX;
    Status = mrcWrongInputParameter;
  }

  if (Status == mrcSuccess) {
    CrOffset = MrcGetMcConfigRegOffset (MrcData, Group, Socket, Controller, Channel, FreqIndex);
  }

  HashPtr->Bits.Offset = CrOffset;

  return Status;
}

/**
  This function returns the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData    - Pointer to global data.
  @param[in]  Group      - CMI group to access.
  @param[in]  Socket     - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel    - DDR Channel Number within the system (0-based).
  @param[in]  FreqIndex  - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] HashVal    - Pointer to return the MMIO access instruction.

  @retval MrcStatus
**/
MrcStatus
MrcGetCmiHash (
  IN  MrcParameters   *const  MrcData,
  IN  GSM_GT          const   Group,
  IN  UINT32          const   Socket,
  IN  UINT32          const   Channel,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  )
{
  MrcStatus Status;
#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  MrcDebug  *Debug;
#endif
  MRC_REGISTER_HASH_STRUCT *HashPtr;
  UINT32 CrOffset;

#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  Debug   = &MrcData->Outputs.Debug;
#endif
  Status  = mrcSuccess;
  HashPtr = (MRC_REGISTER_HASH_STRUCT *) HashVal;
  CrOffset = MRC_UINT32_MAX;

  switch (Group) {
    case GsmCmiHashMask:
      HashPtr->Data = CMI_MEMORY_SLICE_HASH_HASH_MASK_HSH;
      break;

    case GsmCmiLsbMaskBit:
      HashPtr->Data = CMI_MEMORY_SLICE_HASH_HASH_LSB_MASK_BIT_HSH;
      break;

    case GsmCmiHashMode:
      HashPtr->Data = CMI_MEMORY_SLICE_HASH_HASH_MODE_HSH;
      break;

    case GsmCmiStackedMode:
      HashPtr->Data = CMI_MAD_SLICE_STKD_MODE_HSH;
      break;

    case GsmCmiStackMsMap:
      HashPtr->Data = CMI_MAD_SLICE_STKD_MODE_MS1_HSH;
      break;

    case GsmCmiLMadSliceMap:
      HashPtr->Data = CMI_MAD_SLICE_MS_L_MAP_HSH;
      break;

    case GsmCmiSMadSliceSize:
      HashPtr->Data = CMI_MAD_SLICE_MS_S_SIZE_HSH;
      break;

    case GsmCmiStackedMsHash:
      HashPtr->Data = CMI_MAD_SLICE_STKD_MODE_MS_BITS_HSH;
      break;

    default:
      MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Hash undefined. Group %s(%d) Channel %u\n", GsmGtDebugStrings[Group], Group, Channel);
      HashPtr->Data = MRC_UINT32_MAX;
      Status = mrcWrongInputParameter;
      break;
  }

  if (Status == mrcSuccess) {
    CrOffset = MrcGetCmiRegOffset (MrcData, Group, Socket, Channel, FreqIndex);
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
  } else if (Group < EndOfCmiMarker){
    MrcGetCmiGroupLimits (MrcData, Group, MinVal, MaxVal, WaitTime);
  } else {
    MrcGetComplexGroupLimits (MrcData, Group, MinVal, MaxVal, WaitTime);
  }

  return Status;
}

#ifdef MRC_DEBUG_PRINT
/**
  This function outputs the specified group values to the debug print device.

  @param[in] MrcData   - Pointer to global data.
  @param[in] Group     - DDRIO group to access.
  @param[in] Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in] Controller- DDR Memory Controller Number within the processor socket (0-based).
  @param[in] Channel   - DDR Channel Number within the memory controller (0-based).
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
  IN UINT32  const Controller,
  IN UINT32  const Channel,
  IN UINT32  const Rank,
  IN UINT32  const Strobe,
  IN UINT32  const Bit,
  IN UINT32  const FreqIndex,
  IN GSM_GT  const Group
  )
{
  MrcOutput     *Outputs;
  MrcDebug      *Debug;
  INT64_STRUCT  Value;
  UINT32        ControllerIndex;
  UINT32        ControllerMax;
  UINT32        ControllerStart;
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

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;

  if ((Strobe >= MAX_SDRAM_IN_DIMM) && (Strobe != MRC_IGNORE_ARG)) {
    ByteMax   = Outputs->SdramCount;
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
    ChannelMax    = Outputs->MaxChannels;
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
  if ((Controller >= MAX_CONTROLLER) && (Controller != MRC_IGNORE_ARG)) {
    ControllerMax    = MAX_CONTROLLER;
    ControllerStart  = 0;
  } else {
    ControllerMax    = Controller + 1;
    ControllerStart  = Controller;
  }

  switch (Group) {
    case RecEnDelay:
      for (ControllerIndex = ControllerStart; ControllerIndex < ControllerMax; ControllerIndex++) {
        for (ChannelIndex = ChannelStart; ChannelIndex < ChannelMax; ChannelIndex++) {
          for (RankIndex = RankStart; RankIndex < RankMax; RankIndex++) {
            if (!MrcRankExist (MrcData, ControllerIndex, ChannelIndex, RankIndex)) {
              continue;
            }
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RecEnDelay Mc %u Channel %u Rank %u:\n", ControllerIndex, ChannelIndex, RankIndex);
            for (Byte = ByteStart; Byte < ByteMax; Byte++) {
              if (MrcByteExist (MrcData, ControllerIndex, ChannelIndex, Byte)) {
                MrcGetSetStrobe (MrcData, ControllerIndex, ChannelIndex, RankIndex, Byte, RecEnDelay, GSM_READ_ONLY, &Value.Data);
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " B%u: %d\n", Byte, Value.Data32.Low);
              }
            } // Byte
          } // Rank
        } // Channel
      } // Controller
      break;

    case RxDqBitDelay:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RxDqBitDelay Mc %u Channel %u Rank %u Byte %u:", Controller, Channel, Rank, Strobe);
      for (BitIndex = BitStart; BitIndex < BitMax; BitIndex++) {
        MrcGetSetBit (MrcData, Controller, Channel, Rank, Strobe, BitIndex, RxDqBitDelay, GSM_READ_ONLY, &Value.Data);
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
  Update MRC Host Data Structure when GSM_UPDATE_HOST is set
  Currently only used for RxDqBitDelay and TxDqBitDelay

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Controller  - Memory Controller Number within the processor (0-based).
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
  IN      UINT32        const   Controller,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      GSM_GT        const   Group,
  IN OUT  INT64         *const  Value
  )
{
  MrcOutput          *Outputs;
  MrcControllerOut   *ControllerOut;
  MrcChannelOut      *ChannelOut;

  Outputs = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[Controller];
  ChannelOut = &ControllerOut->Channel[Channel];

  switch (Group) {
    case RxDqBitDelay:
      ChannelOut->RxDqPb[Rank][Strobe][Bit].Center = (UINT8) *Value;
      break;

    case TxDqBitDelay:
      ChannelOut->TxDqPb[Rank][Strobe][Bit].Center = (UINT8) *Value;

    default:
      break;
  }

}

