/** @file

  Power state and boot mode save and restore data functions.

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
#include "MrcCommon.h"
#include "MrcGeneral.h"
#include "MrcGlobal.h"
#include "MrcSaveRestore.h"
#include "MrcSpdProcessing.h"
#include "MrcWriteDqDqs.h"

//
// ------- IMPORTANT NOTE --------
// MRC_REGISTER_COUNT_COMMON and MRC_REGISTER_COUNT_SAGV in MrcInterface.h should match these tables.
// Update these define's whenever you add/remove registers from the tables below.

//
// These registers must be saved only once, they don't depend on SA GV point.
// Total bytes to save = 504 + 352 + 224 + 196 + 224 + 64 = 1564
//
const SaveDataControl SaveDataCommonPerByte[] = {
  {0x0D4, 0x0E0}, // 16 DccDataControl[2:5]
  {0x100, 0x100}, // 4  DccDataTrainReplica0
  {0x140, 0x144}, // 8  DataTcoControl[0:1]
}; // 16 + 4 + 8 = 28 bytes, 9 bytes / 2 ch => 28 * 18 = 504 bytes


 const SaveDataControl SaveDataCommon[] = {
  {0x1B18, 0x1B18},  //  4   Ch0 CmdBTcoControl
  {0x1B98, 0x1B98},  //  4   Ch1 CmdBTcoControl
  {0x1D18, 0x1D18},  //  4   Ch0 CmdATcoControl
  {0x1D98, 0x1D98},  //  4   Ch1 CmdATcoControl
  {0x1E2C, 0x1E2C},  //  4   Ch0 CtlTcoControl
  {0x1E44, 0x1E50},  //  16  Ch0 DccClkTcoControl[2:5]
  {0x1E64, 0x1E64},  //  4   Ch0 DccClkTrainReplica
  {0x1E70, 0x1E70},  //  4   Ch0 ClkTcoControl
  {0x1EAC, 0x1EAC},  //  4   Ch1 CtlTcoControl
  {0x1EC4, 0x1ED0},  //  16  Ch1 DccClkTcoControl[2:5]
  {0x1EE4, 0x1EE4},  //  4   Ch1 DccClkTrainReplica
  {0x1EF0, 0x1EF0},  //  4   Ch1 ClkTcoControl
  {0x1F00, 0x1F10},  //  20  DataComp[0:1], CmdComp. CtlComp, ClkComp
  {0x1F20, 0x1F20},  //  4   CompOvr
  {0x1F2C, 0x1F38},  //  16  DataComp2, CompDebug[0:1], DigViewRcompCtl
  {0x1F40, 0x1F44},  //  8   VssIComp, DmVrefComp
  {0x1F60, 0x1F60},  //  4   DccDcoControl2
  {0x26A8, 0x26AC},  //  8   Ch0 CtlTcoControl, CmdTcoControl
  {0x2728, 0x272C},  //  8   Ch1 CtlTcoControl, CmdTcoControl
  {0x2B04, 0x2B04},  //  4   Ch0 VttTopGenControl2
  {0x2B84, 0x2B84},  //  4   Ch0 VttMidHighGenControl2
  {0x2C04, 0x2C04},  //  4   Ch0 VttMidLowGenControl2
  {0x2C84, 0x2C84},  //  4   Ch0 VttBotGenControl2
  {0x2D04, 0x2D04},  //  4   Ch1 VttTopGenControl2
  {0x2D84, 0x2D84},  //  4   Ch1 VttMidHighGenControl2
  {0x2E04, 0x2E04},  //  4   Ch1 VttMidLowGenControl2
  {0x2E84, 0x2E84},  //  4   Ch1 VttBotGenControl2
  {0x3000, 0x3004},  //  8   DdrScrambleCh[0:1]
  {0x302C, 0x3030},  //  8   DdrScrambleCh[2:3]
  {0x3034, 0x3038},  //  8   DdrMiscControl[1:2]
  {0x303C, 0x3078},  //  64  LP4 DeswizzleCh[0:3]RankPair[01:23]Dev[0:1]
  {0x30A8, 0x30B4},  //  16  LP4 DELTADQSDEVUSEMAPCHANNEL[0:3]
  {0x30DC, 0x30E0},  //  8   DdrMiscControl5, DdrMiscControl6
  {0x30F8, 0x30F8},  //  4   DCCMAINFSMCONTROL0
  {0x3104, 0x3140},  //  64  LP4 DeswizzleCh[0:3]RankPair[01:23]Dev[2:3]
                     //  Total DDRIO (without per-byte fubs): (4 * 21) + (8 * 7) + (16 * 4) + 20 + (64 * 2) = 352 bytes
  {0x4030, 0x4034},  //  8   Ch0 DftMisc, EccDft
  {0x4040, 0x4044},  //  8   Ch0 PmPdwnConfig, WmmReadConfig
  {0x4058, 0x406C},  //  24  Ch0 QueueEntryDisable RPQ/IPQ/WPQ, ScWdbwm
  {0x4084, 0x4084},  //  4   Ch0 DftBlock
  {0x419C, 0x419C},  //  4   Ch0 ScGsCfgTraining
  {0x41B0, 0x41B0},  //  4   Ch0 GlobalDriverGateCfg
  {0x4210, 0x4210},  //  4   Ch0 DdrMrParams
  {0x4230, 0x4234},  //  8   Ch0 DeswizzleLow, DeswizzleHigh
  {0x4254, 0x4258},  //  8   Ch0 McInitState, WdbVisaSel
  {0x4274, 0x4274},  //  4   Ch0 EccInjectCount
  {0x427C, 0x4284},  //  12  Ch0 ReadReturnDft, DeswizzleLowErm, DeswizzleHighErm
  {0x428C, 0x4290},  //  8   Ch0 McCpgcCmi, McCpgcMiscDft
  {0x42B0, 0x42B0},  //  4   Ch0 PmAllRanksCkeLowCount
  {0x42E4, 0x42E4},  //  4   Ch0 RefFsmStatus
  {0x43E0, 0x43E4},  //  8   Ch0 PlAgentCfgDtf, GlobalDriverGateCfg
  {0x4430, 0x4434},  //  8   Ch1 DftMisc, EccDft
  {0x4440, 0x4444},  //  8   Ch1 PmPdwnConfig, WmmReadConfig
  {0x4458, 0x446C},  //  24  Ch1 QueueEntryDisable RPQ/IPQ/WPQ, ScWdbwm
  {0x4484, 0x4484},  //  4   Ch1 DftBlock
  {0x459C, 0x459C},  //  4   Ch1 ScGsCfgTraining
  {0x45B0, 0x45B0},  //  4   Ch1 GlobalDriverGateCfg
  {0x4610, 0x4610},  //  4   Ch1 DdrMrParams
  {0x4630, 0x4634},  //  8   Ch1 DeswizzleLow, DeswizzleHigh
  {0x4654, 0x4658},  //  8   Ch1 McInitState, WdbVisaSel
  {0x4674, 0x4674},  //  4   Ch1 EccInjectCount
  {0x467C, 0x4684},  //  12  Ch1 ReadReturnDft, DeswizzleLowErm, DeswizzleHighErm
  {0x468C, 0x4690},  //  8   Ch1 McCpgcCmi, McCpgcMiscDft
  {0x46B0, 0x46B0},  //  4   Ch1 PmAllRanksCkeLowCount
  {0x46E4, 0x46E4},  //  4   Ch1 RefFsmStatus
  {0x47E0, 0x47E4},  //  8   Ch1 PlAgentCfgDtf, GlobalDriverGateCfg
                     //  Total MC Channel: ((4 * 7) + (8 * 6) + (12 * 1) + 24) * 2ch = 224 bytes
  {0x5000, 0x5010},  //  20  MadInterChannel, MadIntraCh0/1, MadDimmCh0/1
  {0x5018, 0x501C},  //  8   McdecsCbit
  {0x5024, 0x5028},  //  8   ChannelHash, ChannelEHash
  {0x5030, 0x5034},  //  8   McInitStateG, MrcRevision
  {0x5040, 0x5048},  //  12  PwmReqcount GT/IA/IO
  {0x5050, 0x505C},  //  16  PwmCount RDDATA/WRDATA/COMMAND/NON_SR
  {0x5064, 0x5068},  //  8   AtmcSts, ReadOccupancyCount
  {0x5078, 0x508C},  //  24  IpcMcArb,IpcMcDecArb, QueueCreditC, RcompTimer, EccInjAddrCompare
  {0x50FC, 0x512C},  //  52  McLock, GDXC_DDR_SYS_ADD_regs
  {0x5138, 0x5138},  //  4   McGlobalDriverGateCfg
  {0x514C, 0x514C},  //  4   PmwCountersDuration
  {0x5154, 0x515C},  //  12  McdecsSecondCbit, EccInjAddrMask
  {0x5200, 0x5210},  //  20  DdrplCfgDtf, DdrplFilterDtf, DdrplDebugDtf, DdrplVisaLanes, DdrplVisaCfgDtf
                     //  Total MCDECS: (4 * 2) + (8 * 4) + (12 * 2) + 16 + (20 * 2) + 24 + 52 = 196 bytes
  {0x5810, 0x5818},  //  12  PCU MailboxData[0:1], MailboxInterface
  {0x5820, 0x5820},  //  4   PCU PackageTherm
  {0x5880, 0x58A4},  //  40  PCU DdrPtmCtl, DdrEnergyScaleFactor, DdrRaplChannelPowerFloor, DdrThermPerDimmStatus,
                     //      DdrWarmThresholdCh[0:1], DdrHotThresholdCh[0:1], DdrThermCamarilloInterrupt, DdrVoltage

  {0x58B0, 0x58E4},  //  56  PCU DdrDimmTempeatureCh[0:1], DdrDimmHottestAbsolute, DdrDimmHottestRelative
                     //      DdrThrottleDurationCh[0:1], DdrWarmBudgetCh[0:1], DdrHotBudgetCh[0:1], DdrRaplLimit
  {0x5908, 0x5908},  //  4   PCU EdramCostEstimate
  {0x5914, 0x5914},  //  4   PCU EdramPerfEstimate
  {0x5988, 0x598C},  //  8   PCU DeviceSharedIdleDuration, DeviceDedicatedIdleDuration
  {0x5994, 0x5998},  //  8   PCU RpStateLimits, RpStateCap
  {0x59A0, 0x59AC},  //  16  PCU PackageRaplLimit, PripTurboPwrLim, SecpTurboPwrLim
  {0x59C8, 0x59C8},  //  4   PCU DeviceIdleDurationOverride
  {0x5A00, 0x5A00},  //  4   PCU ChapConfig
  {0x5A08, 0x5A18},  //  20  PCU FFFC EmiControl, RfiControl, RfiStatus, FaultStatus, RfiControl2
  {0x5B04, 0x5B04},  //  4   PCU EnergyDebug
  {0x5D10, 0x5D14},  //  8   PCU Sskpd
  {0x5D20, 0x5D24},  //  8   PCU C2C3TT, C2DdrTt
  {0x5D30, 0x5D30},  //  4   PCU PcieIltrOvrd
  {0x5DA8, 0x5DA8},  //  4   PCU BiosResetCpl
//  {0x5E00, 0x5E04},  //  8   PCU McBiosReq, McBiosData
  {0x5F00, 0x5F08},  //  12  PCU Sapmctl, PComp, MComp
  {0x5F18, 0x5F18},  //  4   PCU SapmPgStatus
                     //  Total PCU: (4 * 9) + (8 * 4) + (12 * 2) + 16 + 20 + 40 + 56 = 224 bytes
  {0x6040, 0x605C},  //  32  CCF_IDP_CHANNEL_HASH, CCF_IDP_CHANNEL_EHASH, CCF_IDP_MAD_INTER_CHANNEL, CCF_IDP_MAD_INTRA_CH0, CCF_IDP_MAD_INTRA_CH1,
                     //      CCF_IDP_MAD_DIMM_CH0, CCF_IDP_MAD_DIMM_CH1, CCF_IDP_MARS_ENABLE
  {0x6240, 0x625C},  //  32  CCF_IDP1_CHANNEL_HASH, CCF_IDP1_CHANNEL_EHASH, CCF_IDP1_MAD_INTER_CHANNEL, CCF_IDP1_MAD_INTRA_CH0, CCF_IDP1_MAD_INTRA_CH1,
                     //      CCF_IDP1_MAD_DIMM_CH0, CCF_IDP1_MAD_DIMM_CH1, CCF_IDP1_MARS_ENABLE
                     // Total CCF_IDP: 4 * 8 * 2 = 64 bytes
};

//
// These registers must be saved for each SA GV point.
// Total bytes to save = 4464 + 580 + 704 + 4 = 5752 bytes
//

 const SaveDataControl SaveDataSaGvPerByte[] = {
  {0x000, 0x03C}, // 64  RxControl[0:1]Rank[0:3], TxTrainRank[0:3], TxPerBitLowRank[0:3]
  {0x048, 0x048}, // 4   DataControl8
  {0x050, 0x05C}, // 16  RxControl2Rank[0:3]
  {0x068, 0x070}, // 12  DataOffsetComp, DataControl[1:2]
  {0x07C, 0x07C}, // 4   DataOffsetTrain
  {0x080, 0x080}, // 4   DataControl0
  {0x088, 0x098}, // 20  DataControl[3:7]
  {0x0AC, 0x0D0}, // 40  RxControl3Rank[0:3], TxPerBitHiRank[0:3], DccDataControl[0:1]
  {0x104, 0x13C}, // 60  DccDataTrainVal[0:1]Rank[0:3], DccDataDccPilut[0:6]
  {0x148, 0x15C}, // 24  DDRCRDATADFECONTROL1RANK01, DDRCRDATADFECONTROL1RANK23, DDRCRDATADFECONTROL0RANK[0:3]
}; // 64 + 4 + 16 + 12 + 4 * 2 + 20 + 40 + 60 + 24 = 248 bytes, 9 bytes / 2 ch => 248 * 18 = 4464 bytes

 const SaveDataControl SaveDataSaGv[] = {
  {0x1B04, 0x1B10},  //  16 Ch0 CMDB  CmdCompOffset, CmdPiCoding, CmdControls, CmdControls1
  {0x1B84, 0x1B90},  //  16 Ch1 CMDB  CmdCompOffset, CmdPiCoding, CmdControls, CmdControls1
  {0x1C14, 0x1C24},  //  20 Ch0 CtlClkCke   CccCompOffset0, CccPiCoding, CccControls, CccRanksUsed, CccControls1
  {0x1C30, 0x1C38},  //  12 Ch0 CtlClkCke   CccCompOffset1, Ccc4CkeControls, Ccc4CkeRanksUsed
  {0x1C40, 0x1C40},  //  4  Ch0 CtlClkCke   CccCompOffset
  {0x1C94, 0x1CA4},  //  20 Ch1 CtlClkCke   CccCompOffset0, CccPiCoding, CccControls, CccRanksUsed, CccControls1
  {0x1CB0, 0x1CB8},  //  12 Ch1 CtlClkCke   CccCompOffset1, Ccc4CkeControls, Ccc4CkeRanksUsed
  {0x1CC0, 0x1CC0},  //  4  Ch1 CtlClkCke   CccCompOffset
  {0x1D04, 0x1D10},  //  16 Ch0 CMDA  CmdCompOffset, CmdPiCoding, CmdControls, CmdControls1
  {0x1D84, 0x1D90},  //  16 Ch1 CMDA  CmdCompOffset, CmdPiCoding, CmdControls, CmdControls1
  {0x1E00, 0x1E00},  //  4  Ch0 CTL   CtlRanksUsed
  {0x1E14, 0x1E20},  //  16 Ch0 CTL   CtlCompOffset, CtlPiCoding, CtlControls, CtlControls1
  {0x1E34, 0x1E34},  //  4  Ch0 CLK   ClkCompOffset
  {0x1E3C, 0x1E40},  //  8  Ch0 CLK   DccClkControl[0:1]
  {0x1E68, 0x1E6C},  //  8  Ch0 CLK   DccClkTrainVal[0:1]
  {0x1E80, 0x1E80},  //  4  Ch1 CTL   CtlRanksUsed
  {0x1E94, 0x1EA0},  //  16 Ch1 CTL   CtlCompOffset, CtlPiCoding, CtlControls, CtlControls1
  {0x1EB4, 0x1EB4},  //  4  Ch1 CLK   ClkCompOffset
  {0x1EBC, 0x1EC0},  //  8  Ch1 CLK   DccClkControl[0:1]
  {0x1EE8, 0x1EEC},  //  8  Ch1 CLK   DccClkTrainVal[0:1]
  {0x1F00, 0x1F00},  //  4  Comp      DataComp0
  {0x1F08, 0x1F1C},  //  24 Comp      CmdComp, CtlComp, ClkComp, CompCtl[0:1], CompVssHi
  {0x1F28, 0x1F28},  //  4  Comp      CompCtl2
  {0x1F3C, 0x1F3C},  //  4  Comp      CompCtl3
  {0x1F48, 0x1F4C},  //  8  Comp      CompCtl4, CompCtl5
  {0x1F50, 0x1F54},  //  8  Comp      DcoControl[0:1]
  {0x2684, 0x2688},  //  8  Ch0 CKE   CmdCompOffset, CkeRanksUsed
  {0x2694, 0x26A0},  //  16 Ch0 CKE   CtlCompOffset, CtlPiCoding, CtlControls, CtlControls1
  {0x2704, 0x2708},  //  8  Ch1 CKE   CmdCompOffset, CkeRanksUsed
  {0x2714, 0x2720},  //  16 Ch1 CKE   CtlCompOffset, CtlPiCoding, CtlControls, CtlControls1
  {0x2800, 0x2810},  //  20 DdrVref   RcompData, VrefControl, VrefAdjust1, VrefAdjust2, VrefAdjust3
  {0x2884, 0x288C},  //  12 VssHi BotA VssHiControl, VTTFORVSSHICORNRTROL, VTTFORVSSHICOMPOFFSET
  {0x2904, 0x290C},  //  12 VssHi TopA VssHiControl, VTTFORVSSHICORNRTROL, VTTFORVSSHICOMPOFFSET
  {0x2984, 0x298C},  //  12 VssHi CentA VssHiControl, VTTFORVSSHICORNRTROL, VTTFORVSSHICOMPOFFSET
  {0x2B00, 0x2B00},  //  4  VttTop0      VttGenControl
  {0x2B80, 0x2B80},  //  4  VttMidHigh0  VttGenControl
  {0x2C00, 0x2C00},  //  4  VttMidLow0   VttGenControl
  {0x2C80, 0x2C80},  //  4  VttBot0      VttGenControl
  {0x2D00, 0x2D00},  //  4  VttTop1      VttGenControl
  {0x2D80, 0x2D80},  //  4  VttMidHigh1  VttGenControl
  {0x2E00, 0x2E00},  //  4  VttMidLow1   VttGenControl
  {0x2E80, 0x2E80},  //  4  VttBot1      VttGenControl
  {0x3008, 0x3028},  //  36 MiscControl0, WriteCfgCh[0:3], ReadCfgCh[0:3]
  {0x307C, 0x30A4},  //  44 LP4 RoCountTrainCh[0:3]Rank012Dev[0:1], RoCountTrainCh012Rank3Dev[0:1], RoCountTrainCh3Rank3Dev01
  {0x30B8, 0x30B8},  //  4  LP4 DeltaDqsCommon0
  {0x30C4, 0x30D8},  //  24 MiscControl[3:4], WriteCfgChAChB[0:1], ReadCfgChAChB[0:1]
  {0x30E4, 0x30F4},  //  20 SynAutoRdyStart, SynAutoRdyEnd, RxDqFifoRdEnChAChB[0:1], DccControl0
  {0x30FC, 0x30FC},  //  4  DccMainFsmControl1
  {0x3144, 0x316C},  //  44 LP4 RoCountTrainCh[0:3]Rank012Dev[2:3], RoCountTrainCh012Rank3Dev[2:3], RoCountTrainCh3Rank3Dev23
                     //  Total DDR IO (without per-byte fubs): (4 * 19) + (8 * 8) + (12 * 5) + (16 * 8) + (20 * 4) + (24 * 2) + 36 + (44 * 2)= 580 bytes
  {0x4000, 0x4004},  //  8  Ch0 TcPre, TcAct
  {0x400C, 0x4018},  //  16 Ch0 TcRdRd, TcRdWr, TcWrRd, TcWrWr,
  {0x4020, 0x402C},  //  16 Ch0 RoundTrip latency, SchedCbit, SchedSecondCbit
  {0x403C, 0x403C},  //  4  Ch0 ScPcit
  {0x4050, 0x4054},  //  8  Ch0 TcPowerDown
  {0x4070, 0x4078},  //  12 Ch0 TcOdt, McSchedsSpare
  {0x4080, 0x4080},  //  4  Ch0 ScOdtMatrix
  {0x4088, 0x40A0},  //  28 Ch0 ScGsCfg, ScPhThrottling[0:3], ScWpqThreshold
  {0x40A8, 0x40AC},  //  8  Ch0 ScPrCntConfig
  {0x4198, 0x4198},  //  4  Ch0 SpidLowPowerCtl
  {0x41A0, 0x41AC},  //  16 Ch0 SchedThirdCbit, DeadlockBreaker, XarbTcBubbleInj, XarbCfgBubbleInj
  {0x41B4, 0x41B4},  //  4  Ch0 ScBlockingRulesCfg
  {0x4238, 0x4250},  //  28 Ch0 TcRfp, TcRftp, TcSrftp, McRefreshStagger, TcZqcal, TcMr2Shaddow, TcMr4Shaddow
  {0x4260, 0x4270},  //  20 Ch0 PmDimmIdleEnergy, PmDimmPdEnergy, PmDimmActEnergy, PmDimmRdEnergy, PmDimmWrEnergy
  {0x4278, 0x4278},  //  4  Ch0 ScWrDelay
  {0x4288, 0x4288},  //  4  Ch0 ScPbr
  {0x4294, 0x4294},  //  4  Ch0 TcLpddr4Misc
  {0x42C4, 0x42C8},  //  8  Ch0 TcSrExitTp, Lp4DqsOscillatorParams
  {0x4330, 0x433C},  //  16 Ch0 Ddr4Mr6VrefDimm1ValuesCh[0:1]
  {0x4360, 0x439C},  //  64 Ch0 Lpddr4DiscreteMrValues[0:7]
  {0x43A0, 0x43D4},  //  56 Ch0 Ddr4Mr0Mr1Content, Ddr4Mr2Mr3Content, Ddr4Mr4Mr5Content, Ddr4Mr6Mr7Content, Ddr4Mr2RttWrValues,
                     //         Ddr4Mr2RttWrValues, Ddr4Mr6VrefValuesCh[0:1], LpddrMrContent, MrsFsmControl
  {0x43DC, 0x43DC},  //  4  Ch0 Ddr4Mr1OdicValues
  {0x43FC, 0x43FC},  //  4  Ch0 McmntsSpare
  {0x4400, 0x4404},  //  8  Ch1 TcPre, TcAct
  {0x440C, 0x4418},  //  16 Ch1 TcRdRd, TcRdWr, TcWrRd, TcWrWr,
  {0x4420, 0x442C},  //  16 Ch1 RoundTrip latency, SchedCbit, SchedSecondCbit
  {0x443C, 0x443C},  //  4  Ch1 ScPcit
  {0x4450, 0x4454},  //  8  Ch1 TcPowerDown
  {0x4470, 0x4478},  //  12 Ch1 TcOdt, McSchedsSpare
  {0x4480, 0x4480},  //  4  Ch1 ScOdtMatrix
  {0x4488, 0x44A0},  //  28 Ch1 ScGsCfg, ScPhThrottling[0:3], ScWpqThreshold
  {0x44A8, 0x44AC},  //  8  Ch1 ScPrCntConfig
  {0x4598, 0x4598},  //  4  Ch1 SpidLowPowerCtl
  {0x45A0, 0x45AC},  //  16 Ch1 SchedThirdCbit, DeadlockBreaker, XarbTcBubbleInj, XarbCfgBubbleInj
  {0x45B4, 0x45B4},  //  4  Ch1 ScBlockingRulesCfg
  {0x4638, 0x4650},  //  28 Ch1 TcRfp, TcRftp, TcSrftp, McRefreshStagger, TcZqcal, TcMr2Shaddow, TcMr4Shaddow
  {0x4660, 0x4670},  //  20 Ch1 PmDimmIdleEnergy, PmDimmPdEnergy, PmDimmActEnergy, PmDimmRdEnergy, PmDimmWrEnergy
  {0x4678, 0x4678},  //  4  Ch1 ScWrDelay
  {0x4688, 0x4688},  //  4  Ch1 ScPbr
  {0x4694, 0x4694},  //  4  Ch1 TcLpddr4Misc
  {0x46C4, 0x46C8},  //  8  Ch1 TcSrExitTp, Lp4DqsOscillatorParams
  {0x4730, 0x473C},  //  16 Ch1 Ddr4Mr6VrefDimm1ValuesCh[0:1]
  {0x4760, 0x479C},  //  64 Ch1 Lpddr4DiscreteMrValues[0:7]
  {0x47A0, 0x47D4},  //  56 Ch1 Ddr4Mr0Mr1Content, Ddr4Mr2Mr3Content, Ddr4Mr4Mr5Content, Ddr4Mr6Mr7Content, Ddr4Mr2RttWrValues,
                     //         Ddr4Mr2RttWrValues, Ddr4Mr6VrefValuesCh[0:1], LpddrMrContent, MrsFsmControl
  {0x47DC, 0x47DC},  //  4  Ch1 Ddr4Mr1OdicValues
  {0x47FC, 0x47FC},  //  4  Ch1 McmntsSpare
  {0x5060, 0x5060},  //  4  PmSrefConfig
  {0x5130, 0x5134},  //  8  ScQos
  {0x5160, 0x5168},  //  12 ScQos2, ScQos3
                     // Total MC: ((4 * 9) + (8 * 4) + 12 + (16 * 4) + 20 + (28 * 2) + 56 + 64) * 2ch + 4 + 8 + 12 = 704 bytes
  {0x59B8, 0x59B8},  //  4  PCU MrcOdtPowerSaving
                     // Total PCU: 4
};

/**
  This function verifies that neither CPU fuses or DIMMs have changed.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if fast boot is allowed, otherwise mrcColdBootRequired.
**/
MrcStatus
MrcFastBootPermitted (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput            *Inputs;
  const MRC_FUNCTION        *MrcCall;
  const MrcControllerIn     *ControllerIn;
  const MrcChannelIn        *ChannelIn;
  const MrcDimmIn           *DimmIn;
  const UINT8               *CrcStart;
  MrcOutput                 *Outputs;
  MrcDebug                  *Debug;
  MrcSaveData               *Save;
  MrcContSave               *ControllerSave;
  MrcChannelSave            *ChannelSave;
  MrcDimmOut                *DimmSave;
  MrcCapabilityId           Capid0Reg;
  UINT32                    CrcSize;
  UINT32                    Offset;
  UINT16                    DimmCrc;
  UINT8                     Controller;
  UINT8                     Channel;
  UINT8                     Dimm;

  CrcStart = NULL;
  CrcSize  = 0;
  Inputs   = &MrcData->Inputs;
  MrcCall  = Inputs->Call.Func;
  Save     = &MrcData->Save.Data;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;

  // Obtain the capabilities of the memory controller and see if they have changed.
  Offset = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_A_0_0_0_PCI_REG);
  Capid0Reg.Data32.A.Data = MrcCall->MrcMmioRead32 (Offset);
  Capid0Reg.Data32.B.Data = MrcCall->MrcMmioRead32 (Offset + 4);
  Capid0Reg.Data32.C.Data = MrcCall->MrcMmioRead32 (Offset + 8);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CAPID0_C: 0x%08X\n", Capid0Reg.Data32.C.Data);
  if (Capid0Reg.Data != Save->McCapId.Data) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Capabilities have changed, cold boot required\n '%X_%X_%X' --> '%X_%X_%X'\n",
      Save->McCapId.Data32.A.Data,
      Save->McCapId.Data32.B.Data,
      Save->McCapId.Data32.C.Data,
      Capid0Reg.Data32.A.Data,
      Capid0Reg.Data32.B.Data,
      Capid0Reg.Data32.C.Data
      );
    return mrcColdBootRequired;
  }
  // See if any of the DIMMs have changed.
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn   = &Inputs->Controller[Controller];
    ControllerSave = &Save->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn   = &ControllerIn->Channel[Channel];
      ChannelSave = &ControllerSave->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn   = &ChannelIn->Dimm[Dimm];
        DimmSave = &ChannelSave->Dimm[Dimm];
        if (DimmIn->Status == DIMM_DISABLED) {
          DimmCrc = 0;
        } else {
          CrcStart = MrcSpdCrcArea (MrcData, Controller, Channel, Dimm, &CrcSize);
          GetDimmCrc ((const UINT8 *const) CrcStart, CrcSize, &DimmCrc);
        }

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Channel %u Dimm %u DimmCrc %Xh, DimmSave->Crc %Xh\n",
          Channel,
          Dimm,
          DimmCrc,
          DimmSave->Crc
          );
        if (DimmCrc != DimmSave->Crc) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Dimm has changed, cold boot required\n");
          return mrcColdBootRequired;
        }
      }
    }
  }
  // Set RestoreMRs flag to use trained Opt Param Values for Power Savings.
  Outputs->RestoreMRs = TRUE;

  return mrcSuccess;
}

/**
  This function saves any values that need to be used during non-cold boots.

  @param[in, out] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the save occurred with no errors, otherwise returns an error code.
**/
MrcStatus
MrcSaveMCValues (
  IN OUT MrcParameters *const MrcData
  )
{
  const SaveDataControl *SaveIt;
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  MrcIntCmdTimingOut    *IntCmdTiming;
  const MrcChannelIn    *ChannelIn;
  const MrcSpd          *SpdIn;
  const MRC_FUNCTION    *MrcCall;
  MrcIntOutput          *MrcIntData;
  MrcOutput             *Outputs;
  MrcDebug              *Debug;
  MrcSaveData           *SaveData;
  MrcSaveHeader         *SaveHeader;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcContSave           *ControllerSave;
  MrcChannelSave        *ChannelSave;
  MrcProfile            Profile;
  UINT32                *McRegister;
  UINT32                *McRegisterStart;
  UINT32                Offset;
  UINT32                RegOffset;
  UINT32                Index;
  UINT32                Value;
  UINT32                Byte;
  UINT8                 *SpdBegin;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT8                 Pi;
  UINT8                 Sign;
  UINT8                 MarginLevel;
  UINT8                 Rank;
  INT8                  CmdTMargin[3];
  INT8                  WrTMargin[3];
  INT64                 GetSetVal;
  INT8                  MarginOffset;
  UINT16                TxDqsVal;

  CAPID0_A_0_0_0_PCI_STRUCT Capid0A;
  CAPID0_B_0_0_0_PCI_STRUCT Capid0B;
  CAPID0_C_0_0_0_PCI_STRUCT Capid0C;

  // Copy channel and DIMM information to the data area that will be saved.
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  SaveData    = &MrcData->Save.Data;
  SaveHeader  = &MrcData->Save.Header;
  Debug       = &Outputs->Debug;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  MrcCall->MrcSetMem ((UINT8 *) CmdTMargin, sizeof (CmdTMargin), 0);
  MrcCall->MrcSetMem ((UINT8 *) WrTMargin, sizeof (WrTMargin), 0);

  // Obtain the capabilities of the memory controller.
  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_A_0_0_0_PCI_REG);
  Capid0A.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_B_0_0_0_PCI_REG);
  Capid0B.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_C_0_0_0_PCI_REG);
  Capid0C.Data = MrcCall->MrcMmioRead32 (Offset);

  SaveData->McCapId.Data32.A.Data = Capid0A.Data;
  SaveData->McCapId.Data32.B.Data = Capid0B.Data;
  SaveData->McCapId.Data32.C.Data = Capid0C.Data;


  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn                  = &Inputs->Controller[Controller];
    ControllerOut                 = &Outputs->Controller[Controller];
    ControllerSave                = &SaveData->Controller[Controller];
    ControllerSave->ChannelCount  = ControllerOut->ChannelCount;
    ControllerSave->Status        = ControllerOut->Status;

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn   = &ControllerIn->Channel[Channel];
      ChannelOut  = &ControllerOut->Channel[Channel];
      ChannelSave                   = &ControllerSave->Channel[Channel];
      ChannelSave->DimmCount        = ChannelOut->DimmCount;
      ChannelSave->ValidRankBitMask = ChannelOut->ValidRankBitMask;
      ChannelSave->ValidSubChBitMask  = ChannelOut->ValidSubChBitMask;
      ChannelSave->ValidByteMask      = ChannelOut->ValidByteMask;
      ChannelSave->Status           = ChannelOut->Status;
      for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelSave->Timing[Profile], (UINT8 *) &ChannelOut->Timing[Profile], sizeof (MrcTiming));
      }
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelSave->Dimm[Dimm], (UINT8 *) &ChannelOut->Dimm[Dimm], sizeof (MrcDimmOut));
        SpdIn = &ChannelIn->Dimm[Dimm].Spd.Data;
        SpdBegin = (UINT8 *) &SpdIn->Ddr4.ManufactureInfo;
        ChannelSave->DimmSave[Dimm].SpdDramDeviceType = SpdIn->Ddr4.Base.DramDeviceType.Data;
        ChannelSave->DimmSave[Dimm].SpdModuleType = SpdIn->Ddr4.Base.ModuleType.Data;
        ChannelSave->DimmSave[Dimm].SpdModuleMemoryBusWidth = SpdIn->Ddr4.Base.ModuleMemoryBusWidth.Data;
        // Save just enough SPD information so it can be restored during non-cold boot.
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelSave->DimmSave[Dimm].SpdSave[0], SpdBegin, sizeof (ChannelSave->DimmSave[Dimm].SpdSave));
      } // for Dimm
    } // for Channel
  } // for Controller

  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    SaveData->VddVoltage[Profile] = Outputs->VddVoltage[Profile];
  }

  // Copy specified memory controller MMIO registers to the data area that will be saved.
  // Start with the common section.
  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint != MrcSaGvPointHigh)) {
     // If SA GV is enabled, only save the Common registers at the last point (currently High).
  } else {

    McRegister = SaveData->RegSaveCommon;

    for (Index = 0; Index < (sizeof (SaveDataCommon) / sizeof (SaveDataControl)); Index++) {
      SaveIt = &SaveDataCommon[Index];
      for (Offset = SaveIt->StartMchbarOffset; Offset <= SaveIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
        Value         = MrcReadCR (MrcData, Offset);
        *McRegister++ = Value;
      }
    }
    // Common per-byte registers
    for (Index = 0; Index < (sizeof (SaveDataCommonPerByte) / sizeof (SaveDataControl)); Index++) {
      SaveIt = &SaveDataCommonPerByte[Index];
      for (Offset = SaveIt->StartMchbarOffset; Offset <= SaveIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM; Byte++) {
            RegOffset = Offset + (DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel +
                                 (DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Byte;
            Value = MrcReadCR (MrcData, RegOffset);
            *McRegister++ = Value;
          }
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Common section: saved %d bytes\n", (McRegister - SaveData->RegSaveCommon) * 4);
    if ((UINT32) (McRegister - SaveData->RegSaveCommon) > MRC_REGISTER_COUNT_COMMON) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: RegSaveCommon overflow!\n");
      return mrcFail;
    }
  } // if SAGV and Low point

  if (MrcIntData->SaGvPoint == MrcSaGvPointHigh) {
    McRegister = SaveData->RegSaveHigh;
  } else if (MrcIntData->SaGvPoint == MrcSaGvPointMid) {
    McRegister = SaveData->RegSaveMid;
  } else {
    McRegister = SaveData->RegSaveLow;
  }
  McRegisterStart = McRegister;

  for (Index = 0; Index < (sizeof (SaveDataSaGv) / sizeof (SaveDataControl)); Index++) {
    SaveIt = &SaveDataSaGv[Index];
    for (Offset = SaveIt->StartMchbarOffset; Offset <= SaveIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
      Value         = MrcReadCR (MrcData, Offset);
      *McRegister++ = Value;
    }
  }

  // Per-byte registers
  for (Index = 0; Index < (sizeof (SaveDataSaGvPerByte) / sizeof (SaveDataControl)); Index++) {
    SaveIt = &SaveDataSaGvPerByte[Index];
    for (Offset = SaveIt->StartMchbarOffset; Offset <= SaveIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM ; Byte++) {
          RegOffset = Offset + (DDRDATA0CH1_CR_RXCONTROL0RANK0_REG - DDRDATA0CH0_CR_RXCONTROL0RANK0_REG) * Channel +
                               (DDRDATA1CH0_CR_RXCONTROL0RANK0_REG - DDRDATA0CH0_CR_RXCONTROL0RANK0_REG) * Byte;
          Value = MrcReadCR (MrcData, RegOffset);
          *McRegister++ = Value;
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SAGV section: saved %d bytes\n", (McRegister - McRegisterStart) * 4);
  if ((UINT32) (McRegister - McRegisterStart) > MRC_REGISTER_COUNT_SAGV) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: RegSaveHigh/Mid/Low overflow!\n");
    return mrcFail;
  }

  MrcVersionGet (MrcData, &SaveData->Version);
  SaveData->CpuModel               = Inputs->CpuModel;
  SaveData->CpuStepping            = Inputs->CpuStepping;
  SaveData->CpuFamily              = Inputs->CpuFamily;
  SaveData->Frequency              = Outputs->Frequency;
  SaveData->FreqMax                = Outputs->FreqMax;
  SaveData->BurstLength            = Outputs->BurstLength;
  SaveData->HighFrequency          = Outputs->HighFrequency;
  SaveData->MemoryClock            = Outputs->MemoryClock;
  SaveData->Ratio                  = Outputs->Ratio;
  SaveData->RefClk                 = Outputs->RefClk;
  SaveData->EccSupport             = Outputs->EccSupport;
  SaveData->DdrType                = Outputs->DdrType;
  SaveData->Lp4x                   = Outputs->Lp4x;
  SaveData->Lp4x8                  = Outputs->Lp4x8;
  SaveData->EnhancedChannelMode    = Outputs->EnhancedChannelMode;
  SaveData->TCRSensitiveHynixDDR4  = Outputs->TCRSensitiveHynixDDR4;
  SaveData->TCRSensitiveMicronDDR4 = Outputs->TCRSensitiveMicronDDR4;
  SaveData->XmpProfileEnable       = Outputs->XmpProfileEnable;
  SaveData->LpddrEctDone           = Outputs->LpddrEctDone;
  SaveData->Gear2Ever              = Outputs->Gear2Ever;

  if (MrcIntData->SaGvPoint == MrcSaGvPointLow) {
    SaveData->FreqSaGvLow = Outputs->Frequency;
  } else if (MrcIntData->SaGvPoint == MrcSaGvPointMid) {
    SaveData->FreqSaGvMid = Outputs->Frequency;
  }

  SaveData->MeStolenSize           = Inputs->MeStolenSize;
  SaveData->ImrAlignment           = Inputs->ImrAlignment;
#ifdef UP_SERVER_FLAG
  if(Inputs->BoardType == btUpServer) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Output UP CLTM TSOD Offset\nValue = c0d0:%xh\tcod1:%xh\tc1d0:%xh\tc1d1:%xh\n", Outputs->ThermOffset[0][0],Outputs->ThermOffset[0][1], Outputs->ThermOffset[1][0], Outputs->ThermOffset[1][1] );
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        SaveData->ThermOffset[Channel][Dimm] = Outputs->ThermOffset[Channel][Dimm];                        ///TSOD Thermal Offset
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Save UP CLTM TSOD Offset  \nValue = c0d0:%xh\tcod1:%xh\tc1d0:%xh\tc1d1:%xh\n", SaveData->ThermOffset[0][0],SaveData->ThermOffset[0][1], SaveData->ThermOffset[1][0], SaveData->ThermOffset[1][1] );
  }
#endif

  // Setup Margin tables to be used to save/restore DCC LUT for margin check
  // Note: CmdT/WrTMargin[0] should be zero.  This is to save/restore DCC LUT at current PI.
  for (Index = 0; Index < MAX_MARGIN_CHECK; Index++) {
    if (MarginCheckL1Table[Index].TimingType == CmdT) {
      CmdTMargin[MARGIN_CHECK_L1] = MarginCheckL1Table[Index].TimingMargin;
      CmdTMargin[MARGIN_CHECK_L2] = (INT8)((MarginCheckL1Table[Index].TimingMargin * Inputs->MarginLimitL2)/100);
    } else if (MarginCheckL1Table[Index].TimingType == WrT) {
      WrTMargin[MARGIN_CHECK_L1] = MarginCheckL1Table[Index].TimingMargin;
      WrTMargin[MARGIN_CHECK_L2] = (INT8)((MarginCheckL1Table[Index].TimingMargin * Inputs->MarginLimitL2)/100);
    }
  }

  // Dcc LUT needs to be restore for margin check for CmdT/WrT margining
  // To save space, we only save/restore DCC LUT that is needed for L1/L2 check which is at margin offset
  // of L1/L2 and current PI.
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    IntCmdTiming  = &MrcIntData->Controller[0].CmdTiming[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &GetSetVal);
        TxDqsVal = (UINT16) GetSetVal;

        for (MarginLevel = 0; MarginLevel < MARGIN_CHECK_BOTH; MarginLevel++) {
          for (Sign = 0; Sign < 2; Sign++) {
            // Save DqsDcc and DqsDccAipCb entries for WrT margin
            MarginOffset = WrTMargin[MarginLevel] * ((Sign* 2) - 1);
            Pi = ((UINT8) (TxDqsVal + MarginOffset) % MAX_DCC_TX_DQS_DQ_PI);
            SaveData->DqsDcc[Channel][Rank][Byte][MarginLevel][Sign] = MrcIntData->DqsDcc[Channel][Byte][Pi];
            SaveData->DqsDccAipCb[Channel][Rank][Byte][MarginLevel][Sign] = MrcIntData->DqsDccAipCb[Channel][Byte][Pi];

            if (Byte == 0) {
              // Save ClkDcc and ClkDccAipCb for CmdT margin
              MarginOffset = CmdTMargin[MarginLevel] * ((Sign* 2) - 1);
              Pi = ((UINT8) (IntCmdTiming->ClkPiCode[Rank] + MarginOffset) % MAX_DCC_CLOCK_PI);

              SaveData->ClkDcc[Channel][Rank][MarginLevel][Sign] = MrcIntData->ClkDcc[Channel][Rank][Pi];
              SaveData->ClkDccAipCb[Channel][Rank][MarginLevel][Sign] = MrcIntData->ClkDccAipCb[Channel][Rank][Pi];
            }
            if (MarginOffset == 0) {
              break;
            }
          } // Sign
        } // Margin Level
      }  // Byte
    } // Rank
  } // Channel

  SaveData->ClkDccInit = MrcIntData->ClkDccInit;
  SaveData->DqsDccInit = MrcIntData->DqsDccInit;

  SaveData->SaMemCfgCrc = MrcCalculateCrc32 ((UINT8 *) Inputs->SaMemCfgAddress.Ptr, Inputs->SaMemCfgSize);
  SaveHeader->Crc       = MrcCalculateCrc32 ((UINT8 *) SaveData, sizeof (MrcSaveData));
  MrcData->Save.Size    = sizeof (MrcSave);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saved data CRC = %xh\n", SaveHeader->Crc);

  return mrcSuccess;
}

/**
  This function saves any updates to values that need to be used during non-cold boots.

  @param[in, out] MrcData - Include all the MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcUpdateSavedMCValues (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  MrcSaveData           *SaveData;
  MrcSaveHeader         *SaveHeader;
  MrcStatus             Status;

  Inputs      = &MrcData->Inputs;
  SaveData    = &MrcData->Save.Data;
  SaveHeader  = &MrcData->Save.Header;
  Status      = mrcSuccess;

  // In Fast Boot, MeStolenSize may have changed. This should be updated within Save Data structure.
  SaveData->MeStolenSize           = Inputs->MeStolenSize;
  SaveData->ImrAlignment           = Inputs->ImrAlignment;

  SaveData->SaMemCfgCrc = MrcCalculateCrc32 ((UINT8 *) Inputs->SaMemCfgAddress.Ptr, Inputs->SaMemCfgSize);
  SaveHeader->Crc       = MrcCalculateCrc32 ((UINT8 *) SaveData, sizeof (MrcSaveData));
  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "Saved data CRC = %xh\n", SaveHeader->Crc);

  return Status;
}

/**
  This function copies the non-training information that needs to be restored
  from the 'save' data structure to the 'Output' data structure.

  @param[in, out] MrcData - include all the MRC global data.

  @retval mrcSuccess if the copy completed with no errors, otherwise returns an error code.
**/
MrcStatus
MrcRestoreNonTrainingValues (
  IN OUT MrcParameters *const MrcData
  )
{
  MRC_FUNCTION      *MrcCall;
  MrcInput          *Inputs;
  MrcControllerIn   *ControllerIn;
  MrcChannelIn      *ChannelIn;
  MrcSaveData       *SaveData;
  MrcContSave       *ControllerSave;
  MrcChannelSave    *ChannelSave;
  MrcDimmOut        *DimmSave;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  MrcIntOutput      *MrcIntData;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDimmOut        *DimmOut;
  MrcSpd            *SpdIn;
  UINT8             *SpdBegin;
  MrcProfile        Profile;
  MrcSaGvPoint      SaGvPoint;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             Dimm;

  SaveData    = &MrcData->Save.Data;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  SaGvPoint   = MrcIntData->SaGvPoint;

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn                = &Inputs->Controller[Controller];
    ControllerSave              = &SaveData->Controller[Controller];
    ControllerOut               = &Outputs->Controller[Controller];
    ControllerOut->ChannelCount = ControllerSave->ChannelCount;
    ControllerOut->Status       = ControllerSave->Status;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn                     = &ControllerIn->Channel[Channel];
      ChannelSave                   = &ControllerSave->Channel[Channel];
      ChannelOut                    = &ControllerOut->Channel[Channel];
      ChannelOut->DimmCount         = ChannelSave->DimmCount;
      ChannelOut->ValidRankBitMask  = ChannelSave->ValidRankBitMask;
      ChannelOut->Status            = ChannelSave->Status;
      ChannelOut->ValidSubChBitMask = ChannelSave->ValidSubChBitMask;
      ChannelOut->ValidByteMask     = ChannelSave->ValidByteMask;
      for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelOut->Timing[Profile], (UINT8 *) &ChannelSave->Timing[Profile], sizeof (MrcTiming));
      }
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmSave = &ChannelSave->Dimm[Dimm];
        DimmOut  = &ChannelOut->Dimm[Dimm];
        if (DimmSave->Status == DIMM_PRESENT || DimmSave->Status == DIMM_DISABLED) {
          SpdIn   = &ChannelIn->Dimm[Dimm].Spd.Data;
          MrcCall->MrcCopyMem ((UINT8 *) DimmOut, (UINT8 *) DimmSave, sizeof (MrcDimmOut));
          SpdBegin = (UINT8 *) &SpdIn->Ddr4.ManufactureInfo;
          // Restore just enough SPD information so it can be passed out in the HOB.
          // If SAGV enabled, only do this on the last pass, due to LPDDR VendorId patching.
          if ((Inputs->SaGv != MrcSaGvEnabled) || (SaGvPoint == MrcSaGvPointHigh)) {
            MrcCall->MrcCopyMem (SpdBegin, (UINT8 *) &ChannelSave->DimmSave[Dimm].SpdSave[0], sizeof (ChannelSave->DimmSave[Dimm].SpdSave));
          }
        } else {
          DimmOut->Status = DimmSave->Status;
        }
      } // for Dimm
    } // for Channel
  } // for Controller

  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    Outputs->VddVoltage[Profile] = SaveData->VddVoltage[Profile];
  }

// ------- IMPORTANT NOTE --------
// MeStolenSize should not be saved/restored (except on S3).  There is no rule stating that ME FW cannot request
// a different amount of ME UMA space from one boot to the next.  Also, if ME FW is updated/changed, the UMA
// Size requested from the previous version should not be restored.
//
  Inputs->CpuModel                = SaveData->CpuModel;
  Inputs->CpuStepping             = SaveData->CpuStepping;
  Inputs->CpuFamily               = SaveData->CpuFamily;
  Outputs->FreqMax                = SaveData->FreqMax;
  Outputs->Frequency              = SaveData->Frequency;
  Outputs->HighFrequency          = SaveData->HighFrequency;
  Outputs->MemoryClock            = SaveData->MemoryClock;
  Outputs->BurstLength            = SaveData->BurstLength;
  Outputs->Ratio                  = SaveData->Ratio;
  Outputs->RefClk                 = SaveData->RefClk;
  Outputs->EccSupport             = SaveData->EccSupport;
  Outputs->DdrType                = SaveData->DdrType;
  Outputs->EnhancedChannelMode    = SaveData->EnhancedChannelMode;
  Outputs->Lp4x                   = SaveData->Lp4x;
  Outputs->Lp4x8                  = SaveData->Lp4x8;
  Outputs->TCRSensitiveHynixDDR4  = SaveData->TCRSensitiveHynixDDR4;
  Outputs->TCRSensitiveMicronDDR4 = SaveData->TCRSensitiveMicronDDR4;
  Outputs->XmpProfileEnable       = SaveData->XmpProfileEnable;
  Outputs->LpddrEctDone           = SaveData->LpddrEctDone;
  Outputs->Gear2Ever              = SaveData->Gear2Ever;
  if (SaGvPoint == MrcSaGvPointLow) {
    Outputs->Frequency = SaveData->FreqSaGvLow;
    Outputs->HighFrequency = Outputs->Frequency;
    if (Inputs->SaGvLowGear2) {
      Outputs->Gear2 = TRUE;
    }
  } else if (SaGvPoint == MrcSaGvPointMid) {
    Outputs->Frequency = SaveData->FreqSaGvMid;
    Outputs->HighFrequency = Outputs->Frequency;
    if (Inputs->SaGvMidGear2) {
      Outputs->Gear2 = TRUE;
    }
  } else { // SAGV High or SAGV Disabled
    if (Inputs->SaGvHighGear2) {
      Outputs->Gear2 = TRUE;
    }
  }

  Outputs->MemoryClock      = ConvertFreq2Clock (MrcData, Outputs->Frequency);
  Outputs->Ratio            = MrcFrequencyToRatio (MrcData, Outputs->Frequency, Outputs->RefClk, Inputs->BClkFrequency);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "SAGV %s point: Frequency=%u, tCK=%ufs, Ratio=%u, Gear%d\n",
    gFreqPointStr[SaGvPoint],
    Outputs->Frequency,
    Outputs->MemoryClock,
    Outputs->Ratio,
    Outputs->Gear2 ? 2 : 1
    );


  if(Inputs->BootMode == bmS3) {
    Inputs->MeStolenSize      = SaveData->MeStolenSize;
    Inputs->ImrAlignment      = SaveData->ImrAlignment;
  }

#ifdef UP_SERVER_FLAG
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Save UP CLTM TSOD Offset  \nValue = c0d0:%xh\tcod1:%xh\tc1d0:%xh\tc1d1:%xh\n", SaveData->ThermOffset[0][0],SaveData->ThermOffset[0][1], SaveData->ThermOffset[1][0], SaveData->ThermOffset[1][1] );
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      Outputs->ThermOffset[Channel][Dimm] = SaveData->ThermOffset[Channel][Dimm];                        ///TSOD Thermal Offset
    }
  }
MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Output UP CLTM TSOD Offset\nValue = c0d0:%xh\tcod1:%xh\tc1d0:%xh\tc1d1:%xh\n", Outputs->ThermOffset[0][0],Outputs->ThermOffset[0][1], Outputs->ThermOffset[1][0], Outputs->ThermOffset[1][1] );
#endif

  return mrcSuccess;
}

/**
  This function writes the previously determined training values back to the memory controller,
  for the SAGV section

  @param[in] MrcData    - Include all the MRC global data.
  @param[in] McRegister - Data array to restore the values from.

  @retval mrcSuccess if the memory controller write back completed with no errors, otherwise returns an error code.
**/
MrcStatus
MrcRestoreTrainingSaGv (
  IN MrcParameters *const MrcData,
  IN UINT32               *McRegister
  )
{
  const SaveDataControl *RestoreIt;
  MrcDebug              *Debug;
  UINT32                *McRegisterStart;
  UINT32                Offset;
  UINT32                RegOffset;
  UINT32                Index;
  UINT32                Value;
  UINT32                Channel;
  UINT32                Byte;

  Debug    = &MrcData->Outputs.Debug;

  McRegisterStart = McRegister;

  for (Index = 0; Index < (sizeof (SaveDataSaGv) / sizeof (SaveDataControl)); Index++) {
    RestoreIt = &SaveDataSaGv[Index];
    for (Offset = RestoreIt->StartMchbarOffset; Offset <= RestoreIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
      Value = *McRegister++;
      MrcWriteCR (MrcData, Offset, Value);
    }
  }
  // Per-byte registers
  for (Index = 0; Index < (sizeof (SaveDataSaGvPerByte) / sizeof (SaveDataControl)); Index++) {
    RestoreIt = &SaveDataSaGvPerByte[Index];
    for (Offset = RestoreIt->StartMchbarOffset; Offset <= RestoreIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM; Byte++) {
          RegOffset = Offset + (DDRDATA0CH1_CR_RXCONTROL0RANK0_REG - DDRDATA0CH0_CR_RXCONTROL0RANK0_REG) * Channel +
                               (DDRDATA1CH0_CR_RXCONTROL0RANK0_REG - DDRDATA0CH0_CR_RXCONTROL0RANK0_REG) * Byte;
          Value = *McRegister++;
          MrcWriteCR (MrcData, RegOffset, Value);
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SAGV section: Restored %d bytes\n", (McRegister - McRegisterStart) * 4);
  if ((UINT32) (McRegister - McRegisterStart) > MRC_REGISTER_COUNT_SAGV) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: RegSaveHigh/Mid/Low overflow!\n");
    return mrcFail;
  }

  return mrcSuccess;
}

/**
  This function writes the previously determined training values back to the memory controller.
  We also have SAGV flow for S3/Warm/Fast boot here.

  @param[in] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the memory controller write back completed with no errors, otherwise returns an error code.
**/
MrcStatus
MrcRestoreTrainingValues (
  IN     MrcParameters *const MrcData
  )
{
  const SaveDataControl *RestoreIt;
  const MrcInput        *Inputs;
  const MRC_FUNCTION    *MrcCall;
  MrcDebug              *Debug;
  MrcIntOutput          *MrcIntData;
  MrcOutput             *Outputs;
  MrcSaveData           *SaveData;
  MrcIntCmdTimingOut    *IntCmdTiming;
  MrcStatus             Status;
  INT64                 GetSetVal;
  UINT32                *McRegister;
  UINT32                Offset;
  UINT32                RegOffset;
  UINT32                Index;
  UINT32                Value;
  UINT32                Channel;
  UINT32                Byte;
  UINT32                Rank;
  UINT8                 Pi;
  UINT8                 Sign;
  UINT8                 MarginLevel;
  INT8                  CmdTMargin[3];
  INT8                  WrTMargin[3];
  INT8                  MarginOffset;
  UINT16                TxDqsVal;


  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  SaveData = &MrcData->Save.Data;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  MrcCall = Inputs->Call.Func;

  MrcCall->MrcSetMem ((UINT8 *) CmdTMargin, sizeof (CmdTMargin), 0);
  MrcCall->MrcSetMem ((UINT8 *) WrTMargin, sizeof (WrTMargin), 0);

  // Wait on RCOMP Done.  Needed to ensure Rcomp completes on warm reset/S3 before restoring dclk_enable.
  // dclk_enable gets restored with the training registers
  Status = CheckFirstRcompDone (MrcData);
  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "RComp did not complete before the timeout in McFrequencySet\n");
    return Status;
  }

  // First restore the Common section
  McRegister = SaveData->RegSaveCommon;
  for (Index = 0; Index < (sizeof (SaveDataCommon) / sizeof (SaveDataControl)); Index++) {
    RestoreIt = &SaveDataCommon[Index];
    for (Offset = RestoreIt->StartMchbarOffset; Offset <= RestoreIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
      Value = *McRegister++;
      MrcWriteCR (MrcData, Offset, Value);
    }
  }

  // Common per-byte registers
  for (Index = 0; Index < (sizeof (SaveDataCommonPerByte) / sizeof (SaveDataControl)); Index++) {
    RestoreIt = &SaveDataCommonPerByte[Index];
    for (Offset = RestoreIt->StartMchbarOffset; Offset <= RestoreIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM; Byte++) {
          RegOffset = Offset + (DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel +
                               (DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Byte;
          Value = *McRegister++;
          MrcWriteCR (MrcData, RegOffset, Value);
        }
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Common section: Restored %d bytes\n", (McRegister - SaveData->RegSaveCommon) * 4);
  if ((UINT32) (McRegister - SaveData->RegSaveCommon) > MRC_REGISTER_COUNT_COMMON) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: RegSaveCommon overflow!\n");
    return mrcFail;
  }

  // Now restore the SAGV section, RegSaveHigh is used when SAGV is disabled
  if (MrcIntData->SaGvPoint == MrcSaGvPointHigh) {
    McRegister = SaveData->RegSaveHigh;
  } else if (MrcIntData->SaGvPoint == MrcSaGvPointMid) {
      McRegister = SaveData->RegSaveMid;
  } else {
    McRegister = SaveData->RegSaveLow;
  }

  Status = MrcRestoreTrainingSaGv (MrcData, McRegister);
  if (Status != mrcSuccess) {
    return Status;
  }

  // Restore Host structure data for ClkPiCode and update cache for RcvEn, TxDqs, TxDq
  // This is need to do CmdT margining in RMT on Fast Flow
  // Also bring SC_GS_CFG register to the CR cache, by reading one of its fields (GsmMccGear2)
  // This is needed because we use ReadFromCache for GsmMccDdr4OneDpc (in JEDEC Reset) and GsmMccCmdTriStateDis (in RunIOTest)
  // And in Fast flow when we lock MC PLL we cache SC_GS_CFG before it's restored from MrcSave.
  if ((Inputs->BootMode == bmFast) || (Inputs->BootMode == bmWarm)) {

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      IntCmdTiming  = &MrcIntData->Controller[0].CmdTiming[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        // Restore ClkPiCode host data, we shift CmdT for Margin check
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Rank, ClkGrpPi, ReadCached, &GetSetVal);
        IntCmdTiming->ClkPiCode[Rank] = (UINT8) GetSetVal;

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          // Bring RcvEn,TxDqs,TxDq  to CR cache, we shift CmdT for Margin check
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, ReadCached, &GetSetVal);
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, ReadCached, &GetSetVal);
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay,  ReadCached, &GetSetVal);
        } // Byte
      } // for Rank

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        // Bring DataControl6 register to the CR cache, we program Lp4ForceDqsNOn in DdrioInit, before it's restored from MrcSave, and later program Gear in this register
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLp4ForceDqsNOn,  ReadCached, &GetSetVal);
      }
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccGear2, ReadCached, &GetSetVal);
    } // for Channel

    // Bring DdrMiscControl0 register to the CR cache, we set DataClkGateDisAtIdle to 1 in DdrioInit, before it's restored from MrcSave, and later program Gear in this register
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDisDataIdlClkGate, ReadCached, &GetSetVal);

    // Setup Margin tables to be used to save/restore DCC LUT for margin check
    // Note: CmdT/WrTMargin[0] should be zero.  This is to save/restore DCC LUT at current PI.
    for (Index = 0; Index < MAX_MARGIN_CHECK; Index++) {
      if (MarginCheckL1Table[Index].TimingType == CmdT) {
        CmdTMargin[MARGIN_CHECK_L1] = MarginCheckL1Table[Index].TimingMargin;
        CmdTMargin[MARGIN_CHECK_L2] = (INT8)((MarginCheckL1Table[Index].TimingMargin * Inputs->MarginLimitL2)/100);
      } else if (MarginCheckL1Table[Index].TimingType == WrT) {
        WrTMargin[MARGIN_CHECK_L1] = MarginCheckL1Table[Index].TimingMargin;
        WrTMargin[MARGIN_CHECK_L2] = (INT8)((MarginCheckL1Table[Index].TimingMargin * Inputs->MarginLimitL2)/100);
      }
    }

    // Dcc LUT needs to be restore for margin check for CmdT/WrT margining
    // To save space, we only save/restore DCC LUT that is needed for L1/L2 check which is at margin offset
    // of L1/L2 and current PI.
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      IntCmdTiming  = &MrcIntData->Controller[0].CmdTiming[Channel];
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &GetSetVal);
          TxDqsVal = (UINT16) GetSetVal;

          for (MarginLevel = 0; MarginLevel < MARGIN_CHECK_BOTH; MarginLevel++) {
            for (Sign = 0; Sign < 2; Sign++) {
              // Restore DqsDcc and DqsDccAipCb entries for WrT margin
              MarginOffset = WrTMargin[MarginLevel] * ((Sign* 2) - 1);
              Pi = ((UINT8) (TxDqsVal + MarginOffset) % MAX_DCC_TX_DQS_DQ_PI);

              MrcIntData->DqsDcc[Channel][Byte][Pi] = SaveData->DqsDcc[Channel][Rank][Byte][MarginLevel][Sign];
              MrcIntData->DqsDccAipCb[Channel][Byte][Pi] = SaveData->DqsDccAipCb[Channel][Rank][Byte][MarginLevel][Sign];

              if (Byte == 0) {
                // Restore ClkDcc and ClkDccAipCb for CmdT margin
                MarginOffset = CmdTMargin[MarginLevel] * ((Sign* 2) - 1);
                Pi = ((UINT8) (IntCmdTiming->ClkPiCode[Rank] + MarginOffset) % MAX_DCC_CLOCK_PI);

                MrcIntData->ClkDcc[Channel][Rank][Pi] = SaveData->ClkDcc[Channel][Rank][MarginLevel][Sign];
                MrcIntData->ClkDccAipCb[Channel][Rank][Pi] = SaveData->ClkDccAipCb[Channel][Rank][MarginLevel][Sign];
              }

              if (MarginOffset == 0) {
                break;
              }
            } // Sign
          } // Margin Level
        }  // Byte
      } // Rank
    } // Channel

    MrcIntData->ClkDccInit = SaveData->ClkDccInit;
    MrcIntData->DqsDccInit = SaveData->DqsDccInit;
  }

  ForceRcomp (MrcData);

#ifdef UP_SERVER_FLAG
  if (Inputs->BoardType == btUpServer) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Restoring CLTM TSOD Values.\n");
    CltmTsodConfiguration (MrcData);
#ifdef MRC_DEBUG_PRINT
    MrcCltmPrintMchRegisters (MrcData);
#endif //MRC_DEBUG_PRINT
  }
#endif

  return mrcSuccess;
}

/**
  Calculates a CRC-32 of the specified data buffer.

  @param[in] Data     - Pointer to the data buffer.
  @param[in] DataSize - Size of the data buffer, in bytes.

  @retval The CRC-32 value.
**/
UINT32
MrcCalculateCrc32 (
  IN     const UINT8       *const Data,
  IN     const UINT32      DataSize
  )
{
  UINT32 i;
  UINT32 j;
  UINT32 crc;
  UINT32 CrcTable[256];

  crc = (UINT32) (-1);

  // Initialize the CRC base table.
  for (i = 0; i < 256; i++) {
    CrcTable[i] = i;
    for (j = 8; j > 0; j--) {
      CrcTable[i] = (CrcTable[i] & 1) ? (CrcTable[i] >> 1) ^ 0xEDB88320 : CrcTable[i] >> 1;
    }
  }
  // Calculate the CRC.
  for (i = 0; i < DataSize; i++) {
    crc = (crc >> 8) ^ CrcTable[(UINT8) crc ^ (Data)[i]];
  }

  return ~crc;
}


#ifdef UP_SERVER_FLAG
#ifdef MRC_DEBUG_PRINT
/**
  This function Print the CLTM related registers.

  @param MrcData - Include all the MRC global data.

  @retval None.
**/
void
MrcCltmPrintMchRegisters (
  MrcParameters          *MrcData
  )
{
  MrcOutput               *Outputs;
  MrcDebug                *Debug;

  Outputs                 = &MrcData->Outputs;
  Debug                   = &Outputs->Debug;

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UP Power weight Energy registers...\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_ENERGY_SCALEFACTOR %Xh: %Xh \n", PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG));

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Power budget registers ...\n");

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_BUDGET_CH0 %Xh: %Xh \n", PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_BUDGET_CH1 %Xh: %Xh \n", PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_BUDGET_CH0 %Xh: %Xh \n", PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_BUDGET_CH1 %Xh: %Xh \n", PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG));


    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Thresholds registers...\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_THRESHOLD_CH0 %Xh: %Xh \n", PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_THRESHOLD_CH1 %Xh: %Xh \n", PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_THRESHOLD_CH0 %Xh: %Xh \n", PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_THRESHOLD_CH1 %Xh: %Xh \n", PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG));

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM Configuration registers...\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_PTM_CTL %Xh: %Xh \n", PCU_CR_DDR_PTM_CTL_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG));
}
#endif //MRC_DEBUG_PRINT
#endif
