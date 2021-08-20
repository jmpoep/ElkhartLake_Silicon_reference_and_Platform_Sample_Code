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

#define MRC_NUM_BYTE_GROUPS   (8)
#define R64BIT                (0xFFFF)

//
// ------- IMPORTANT NOTE --------
// MRC_REGISTER_COUNT_COMMON and MRC_REGISTER_COUNT_SAGV in MrcInterface.h should match these tables.
// Update these define's whenever you add/remove registers from the tables below.

// Total Save/Restore registers = 1880 + 7896 * 3(= per sagv Point) = 33464

//
// These registers must be saved only once, they don't depend on SA GV point.
// 64 + 512 + 296 + 288 = 1160
const SaveDataControl SaveDataCommonPerByte[] = {
  // DATA[0:7]CH[0:1]  4 * 8 * 2 = 64
  {0x144, 0x144}, // 4 WRRETRAINSWIZZLECONTROL - DATA0CH0
};


// "R64BIT" indicates the 64bit field instead of the end offset used in 32 bit registers.
const SaveDataControl SaveDataCommonPerCh[] = {
   // MC[0-1] CH[0-1]  280 * 2 * 2 = 1120
  {0x4030, 0x4030},  //  4  DftMisc
  {0x4038, 0x4038},  //  4  EccDft
  {0x4044, 0x404c},  //  12 WmmReadConfig, ErrLog0, ErrLog1
  {0x4058, 0x405C},  //  8  QueueEntryDisable
  {0x4060, R64BIT},  //  8  RPQ/IPQ/WPQ
  {0x4068, R64BIT},  //  8  ScWdbwm
  {0x4084, 0x4084},  //  4  DftBlock
  {0x40BC, 0x40BC},  //  4  ScGsCfgTraining
  {0x40D0, 0x40D0},  //  4  GlobalDriverGateCfg
  {0x40D8, R64BIT},  //  8  PwmSubCh0ActCounter
  {0x40E0, R64BIT},  //  8  PwmSubCh1DclkActivateCounter
  {0x40E8, R64BIT},  //  8  PwmSubCh0DclkActivateCounter
  {0x40F0, R64BIT},  //  8  PwmSubCh1DclkActivateCounter
  {0x4120, 0x418C},  //  112 MrcFsmControl[0:27]
  {0x4210, 0x4210},  //  4  DdrMrParams
  {0x4224, 0x4228},  //  8  LpddrMr4, Ddr4Mpr Rank Temperature
  {0x4230, R64BIT},  //  8  DeswizzleLowErm
  {0x4254, 0x4258},  //  8  McInitState, WdbVisaSel
  {0x427C, 0x427C},  //  4  ReadReturnDft
  {0x4280, R64BIT},  //  8  Deswizzlelow
  {0x4298, R64BIT},  //  8  DeswizzleHighErm
  {0x42B8, R64BIT},  //  8  DeswizzleHigh
  {0x42E4, 0x42EC},  //  12 RefFsmStatus, WdbMbist0/1
  {0x42F8, 0x42F8},  //  4  RdbMbist
  {0x43E0, 0x43E4}   //  8  PL_AGENT_CFG_DTF
};

const SaveDataControl SaveDataCommonPerMc[] = {
// MC[0-1] : 204 * 2 = 408
  {0x5000, 0x5010},  //  20 MadInterChannel
  {0x5018, 0x501C},  //  8  McdecsMisc, McdecsCbit
  {0x5024, 0x5028},  //  8  ChannelHash, ChannelEHash
  {0x5030, 0x5034},  //  8  McInitStateG, MrcRevision
  {0x503C, 0x5040},  //  8  ProgrammableReqCountConfig, TotalReqCount
  {0x5064, 0x5064},  //  4  AtmcS
  {0x5078, 0x5080},  //  12 IpcMcArb, IpcMcDecArb, QueueCreditC
  {0x5090, R64BIT},  //  8  RemapBase, RemapLimit
  {0x5098, R64BIT},  //  8  RemapLimit
  {0x50BC, 0x50BC},  //  4  Tolud
  {0x5138, 0x5138},  //  4  Tolud
  {0x5088, R64BIT},  //  8  EccInjAddrCompare
  {0x5100, R64BIT},  //  8  SysAddFilterMask0
  {0x5108, R64BIT},  //  8  SysAddFilterMask1
  {0x5110, R64BIT},  //  8  SysAddFilterMatch0
  {0x5118, R64BIT},  //  8  SysAddFilterMatch1
  {0x5120, R64BIT},  //  8  SysAddTriggerMask
  {0x5128, R64BIT},  //  8  SysAddTriggerMatch
  {0x5154, 0x5154},  //  4  McdecsSecondCbit
  {0x5158, R64BIT},  //  8  EccInjAddrMask,
  {0x5170, 0x5174},  //  8  cpgccmi, CpgcMiscDft
  {0x51A0, R64BIT},  //  8  ParityErrLog
  {0x51A8, 0x51A8},  //  4  ParityErrInj
  {0x51B4, 0x51B4},  //  4  ParityControl
  {0x5200, 0x5210},  //  20 DdrplCfgDtf, DdrplFilterDtf, DdrplDebugDtf, DdrplVisaLanes, DdrplVisaCfgDtf
};

 const SaveDataControl SaveDataCommon[] = {
  // 288
  {0x280C, 0x280C},  //  4  DDRCRVCCDLLVOLTAGES - VCCDLL0
  {0x288C, 0x288C},  //  4  DDRCRVCCDLLVOLTAGES - VCCDLL1
  {0x2908, 0x290C},  //  8  VTTCOMPOFFSET, VTTCOMPOFFSET2  - VTT0
  {0x2988, 0x298C},  //  8  VTTCOMPOFFSET, VTTCOMPOFFSET2  - VTT1
  {0x2A08, 0x2A0C},  //  8  VTTCOMPOFFSET, VTTCOMPOFFSET2  - VTT2
  {0x2A88, 0x2A8C},  //  8  VTTCOMPOFFSET, VTTCOMPOFFSET2  - VTT3
  {0x2B00, 0x2B00},  //  4  COMPDATA
  {0x2B8C, 0x2B8C},  //  4  VSSHICOMPOFFSET
  {0x2C20, 0x2C20},  //  4  COMPOVR0
  {0x2C40, 0x2C44},  //  8  DDRCRALERT, COMPOVR1
  {0x2C84, 0x2C84},  //  4  DDRCRVIEWCTL
  {0x3504, 0x3510},  //  16 FLL_STATIC_CFG0/1, FLL_DEBUG_CFG, FLL_DYNAMIC_CFG
  {0x3520, 0x3520},  //  4  FLL_STATIC_CFG2
  {0x3E00, 0x3E1C},  //  32 DDRSCRAMBLECH[0:7]
  {0x3E28, 0x3E28},  //  4  DDRMISCCONTROL2

  {0x5810, 0x5818},  //  12  PCU MailboxData[0:1], MailboxInterface
  {0x5820, 0x5820},  //  4   PCU PackageTherm
  {0x5880, 0x5884},  //  8   PCU DdrPtmCtl, BwCtrlPcu
  {0x58A0, 0x58A4},  //  8   PCU ThermCamarilloInterrupt, Volatge
  {0x58E0, R64BIT},  //  8   PCU RaplLimit
  {0x5908, 0x5908},  //  4   PCU EdramCostEstimate
  {0x5914, 0x5914},  //  4   PCU EdramPerfEstimate
  {0x5988, 0x598C},  //  8   PCU DeviceSharedIdleDuration, DeviceDedicatedIdleDuration
  {0x5994, 0x5998},  //  8   PCU RpStateLimits, RpStateCap
  {0x59A0, R64BIT},  //  8   PCU PackageRaplLimit
  {0x59A8, 0x59AC},  //  8   PripTurboPwrLim, SecpTurboPwrLim
  {0x59B8, 0x59B8},  //  4   PCU PowerSaving
  {0x59C8, 0x59C8},  //  4   PCU DeviceIdleDurationOverride
  {0x5A00, 0x5A00},  //  4   PCU ChapConfig
  {0x5B04, 0x5B04},  //  4   PCU EnergyDebug
  {0x5D10, 0x5D14},  //  8   PCU Sskpd
  {0x5D20, 0x5D24},  //  8   PCU C2C3TT, C2DdrTt
  {0x5D30, 0x5D30},  //  4   PCU PcieIltrOvrd
  {0x5DA8, 0x5DA8},  //  4   PCU BiosResetCpl
  {0x5E00, 0x5E04},  //  8   PCU McBiosReq, McBiosData
  {0x5F00, 0x5F10},  //  24  PCU Sapmctl, PComp, MComp, FusaConfig, FusataskCompletionCounter
  {0x5F00, 0x5F08},  //  8   PCU Sapmctl, PComp, MComp
  {0x5F18, 0x5F18},  //  4   PCU SapmPgStatus
  {0x5F58, 0x5F58},  //  4   PCU OsStatus
};

//
// These registers must be saved for each SA GV point.
// Total bytes to save = 4480 + 576 + 1168 + 608 = 6820 bytes.
//
const SaveDataControl SaveDataSaGvPerByte[] = {
  // DATA[0-7]CH[0-1] : 276 * 8 * 2 = 4416
  {0x000, 0x08c}, // 144 DDRDATADQ[RANK0LANE0:RANK3LANE7] - DATA0CH0
  {0x09c, 0x0c8}, // 48 DDRDATADQS[RANK0:RANK3], RXCONTROL0RANK0/TXCONTROL0RANK0LANE0 - DATA0CH0
  {0x0E0, 0x10C}, // 32 DATAOFFSETCOMP, DATAOFFSETTRAIN, DATACONTROL[0-6], CMDBUSTRAIN, DCCFSMCONTROL, DCCCALCCONTROL - DATA0CH0
  {0x124, 0x140}, // 32 DCCPILUT[0-4], TCOCONTROL[0-1], DCCLANETARGET - DATA0CH0
  {0x148, 0x158}, // 20 WRRETRAINRANK2, WRRETRAINRANK3, WRRETRAINCONTROLSTATUS - DATA0CH0
};

const SaveDataControl SaveDataSaGvCcc[] = {
  // CH[0-7] : 80 * 8 = 640
  {0x3604, 0x3634},  //  52  CCC Regs VSSHICLKCOMPOFFSET, CTLCACOMPOFFSET, CCCPIDIVIDER, CCCPICODING0, PERBITDESKEWPRISENFALL, CCCVOLTAGEUSED, PERBITDESKEW0/1/2, DDRCRPINSUSED, CCCCLKCONTROLS - CH0
  {0x3640, 0x3648},  //  12  CCC Regs - CH0
  {0x3658, 0x3664},  //  16  CCC Regs - CH0
};

const SaveDataControl SaveDataSaGvMc[] = {
  // MC[0-1]CH{0-1] : 504 * 2 * 2 = 2016
  {0x4000, R64BIT},  //  8  TcPre(64bit)
  {0x4008, 0x4018},  //  20 TcAct, TcRdRd, TcRdWr, TcWrRd, TcWrWr
  {0x4020, R64BIT},  //  8 RoundTrip latency(64bit)
  {0x4028, 0x402C},  //  8 SchedCbit, SchedSecondCbit
  {0x4034, 0x4034},  //  4  ScPcit
  {0x4040, 0x4040},  //  4  PmPdwnCfg
  {0x4050, R64BIT},  //  8  TcPwrdn
  {0x4060, R64BIT},  //  8  QueueEntryDisableWpq
  {0x4070, R64BIT},  //  8  TcOdt
  {0x4078, 0x4078},  //  4  McSchedsSpare
  {0x4080, 0x4080},  //  4  ScOdtMatrix
  {0x4088, R64BIT},  //  8  ScGsCfg
  {0x4090, 0x40A0},  //  20 ScPhThrottling[0:3], ScWpqThreshold
  {0x40A8, R64BIT},  //  8  ScPrCntCfg
  {0x40B8, 0x40B8},  //  4  SpidLowPowerCtl
  {0x40C0, 0x40CC},  //  16 SchedThirdCbit, DeadLockBreaker, TcBubbleInj, CfgBubbleInj
  {0x40D4, 0x40D4},  //  4  ScBlockingRulesCfg
  {0x40F8, R64BIT},  //  8  WckConfig
  {0x4190, 0x41D8},  //  76 MrsFsmPerRank[0:11], MrsFsmShadowValues[0:6]
  {0x41E0, 0x41E0},  //  4  MrsFsmTimingStorage
  {0x4238, 0x4250},  //  28 TcRfp, TcRftp, TcSrftp, McRefreshStagger, TcZqcal, TcMr2Shaddow, TcMr4Shaddow
  {0x4260, 0x4270},  //  20 PmDimmIdleEnergy, PmDimmPdEnergy, PmDimmActEnergy, PmDimmRdEnergy, PmDimmWrEnergy
  {0x4278, 0x4278},  //  4  ScWrDelay
  {0x4288, 0x4288},  //  4  ScPbr
  {0x4294, 0x4294},  //  4  TcLpddr4Misc
  {0x42C0, R64BIT},  //  8  TcSrExitTp
  {0x42C8, 0x42C8},  //  4  Lp4DqsOscillatorParams
  {0X4320, R64BIT},  //  8  Mr1RttNomDimm1Values
  {0X4328, R64BIT},  //  8  Mr2RttNomDimm1Values
  {0X4330, R64BIT},  //  8  Mr6VrefDimm1Values0
  {0X4338, R64BIT},  //  8  Mr6VrefDimm1Values1
  {0X4344, 0X4344},  //  4  Mr1OdicDimm1Values
  {0X4348, R64BIT},  //  8  Mr5RttParkValues
  {0X4350, R64BIT},  //  8  Mr5RttParkDimm1Values
  {0X4358, R64BIT},  //  8  Mr5RttNonValues
  {0X4360, R64BIT},  //  8  DiscreteMrValues0
  {0X4368, R64BIT},  //  8  DiscreteMrValues1
  {0X4370, R64BIT},  //  8  DiscreteMrValues2
  {0X4378, R64BIT},  //  8  DiscreteMrValues3
  {0X4380, R64BIT},  //  8  DiscreteMrValues4
  {0X4388, R64BIT},  //  8  DiscreteMrValues5
  {0X4390, R64BIT},  //  8  DiscreteMrValues6
  {0X4398, R64BIT},  //  8  DiscreteMrValues7
  {0x43A0, 0x43AC},  //  16 Ddr4Mr0Mr1Content, Ddr4Mr2Mr3Content, Ddr4Mr4Mr5Content, Ddr4Mr6Mr7Content
  {0X43B0, R64BIT},  //  8  Mr2RttWrValues
  {0X43B8, R64BIT},  //  8  Mr6VrefValues0
  {0X43C0, R64BIT},  //  8  Mr6VrefValues1
  {0x43C8, R64BIT},  //  8  MpddrMrContent
  {0x43D0, R64BIT},  //  8  MrsFsmControl
  {0x43DC, 0x43DC},  //  4  Mr1OdicValue
  {0x43E8, R64BIT},  //  4  EccDevice
  {0x43F0, R64BIT},  //  8  EccDeviceDimm1
  {0x43FC, 0x43FC},  //  4  McMntsspare
};

 const SaveDataControl SaveDataSaGv[] = {
  // 824
  {0x2800, 0x2808},  //  12 VCCDLLCONTROL, VCCDLLCOMPDLL, VCCDLLSAMPLER - VCC DLL0
  {0x2880, 0x2888},  //  12 VCCDLLCONTROL, VCCDLLCOMPDLL, VCCDLLSAMPLER - VCC DLL1
  {0x2900, 0x2900},  //  4 VTTGENCONTROL - VTT0
  {0x2980, 0x2980},  //  4 VTTGENCONTROL - VTT1
  {0x2A00, 0x2A00},  //  4 VTTGENCONTROL - VTT2
  {0x2A80, 0x2A80},  //  4 VTTGENCONTROL - VTT3
  {0x2B04, 0x2B0C},  //  12 VREFCONTROL, VREFADJUST1, VREFADJUST2
  {0x2B80, 0x2B88},  //  12 DDRRCOMPDATA, DDRCRVSSHICONTROL, DDRCRVSSHISAMPLER
  {0x2C00, 0x2C1C},  //  32  DDRCRDATACOMP1, CACOMP, DDRCRCLKCOMP, COMPCTL[0-2]
  {0x2C24, 0x2C3C},  //  28 COMPCTL3, COMPTEM, DDRCOMPDATA, COMPCTL4, VSSHITARGET
  {0x2C48, 0x2C74},  //  48 VCCDLL TARGET, REPLICACTR[0-2], COMPDLL, COMPDATACCC,
                     //     DQSDELAY, COMPREF[0-1], COMPDVFSRLOAD, VSSHIPANIC, COMPVTTPANIC
  {0x2C80, 0x2C8C},  //  16 COMPVTTPANIC, FLLWIRED, COMPDVFSRCOMP
  {0x2D24, 0x2D44},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -DATA0
  {0x2DA4, 0x2DC4},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -DATA1
  {0x2E24, 0x2E44},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -DATA2
  {0x2EA4, 0x2EC4},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -DATA3
  {0x2F24, 0x2F44},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -DATA4
  {0x2FA4, 0x2FC4},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -DATA5
  {0x3024, 0x3044},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -DATA6
  {0x30A4, 0x30C4},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -DATA7
  {0x3124, 0x3144},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -CMD0
  {0x31A4, 0x31C4},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -CMD1
  {0x3224, 0x3244},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -CTL0
  {0x32A4, 0x32C4},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -CTL1
  {0x3324, 0x3344},  //  36 VCCDLLWEAKLOCK, VCCDLLFFCONTROL, FFNBIAS, DDRCRVCCDLLCOMPDLL, DDRCRVCCDLLCOMPDATACCC, DDRCRVCCDLLCOMPOFFSET, VCCDLLVSXHIFF, VCCDLLCOUPLINGCAP, PITUNE -COMP

  {0x3500, 0x3500},  //  4  FLL_CMD_CFG
  {0x3E20, 0x3E24},  //  8  DDRMISCCONTROL0, DDRMISCCONTROL1
  {0x3E2C, 0x3E74},  //  76 WRITECFGCH[0:7], READCFGCH[0:7], DDRMISCCONTROL7
  {0x3E80, 0x3EB4},  //  56 WRITECFGCH01:67, READCFGCH01:67, RXDQFIFORDENCH01:67, SPINEGATING, DDRWCKCONTROL

  {0x5060, 0x5060},  //  4  PmSrefConfig
  {0x5130, R64BIT},  //  8  ScQos
  {0x5160, R64BIT},  //  8  ScQos2
  {0x5168, 0x5168},  //  4  ScQos3
};

 typedef enum {
   SaveReg,
   RestoreReg
 } SaveRestore;

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
  MrcCall = Inputs->Call.Func;
  Save     = &MrcData->Save.Data;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;

  // Obtain the capabilities of the memory controller and see if they have changed.
  Offset = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_A_0_0_0_PCI_REG);
  Capid0Reg.A = MrcCall->MrcMmioRead32 (Offset);
  Offset = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_B_0_0_0_PCI_REG);
  Capid0Reg.B = MrcCall->MrcMmioRead32 (Offset);
  Offset = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_C_0_0_0_PCI_REG);
  Capid0Reg.C = MrcCall->MrcMmioRead32 (Offset);
  Offset = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_E_0_0_0_PCI_REG);
  Capid0Reg.E = MrcCall->MrcMmioRead32 (Offset);
  if ((Capid0Reg.A != Save->McCapId.A) ||
      (Capid0Reg.B != Save->McCapId.B) ||
      (Capid0Reg.C != Save->McCapId.C) ||
      (Capid0Reg.E != Save->McCapId.E)) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Capabilities have changed, cold boot required\n '%X_%X_%X_%X' --> '%X_%X_%X_%X'\n",
      Save->McCapId.A,
      Save->McCapId.B,
      Save->McCapId.C,
      Save->McCapId.E,
      Capid0Reg.A,
      Capid0Reg.B,
      Capid0Reg.C,
      Capid0Reg.E
      );
    return mrcColdBootRequired;
  }
  // See if any of the DIMMs have changed.
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
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
  This function saves or restores register values based on the SaveRestore flag.

  @param[in, out] MrcData         - Include all the MRC global data.
  @param[in]      SaveRestoreDataCtrlPtr
                                  - Registers data group to be saved or restored.
  @param[in]      SizeoOfData     - Total size of the register group.
  @param[in]      RegOffset       - Register offset increment of the register group.
  @param[in, out] McRegister      - Save or Restore registers value in mrc save data.
  @param[in]      SaveRestore     - Control flag to save registers or to restore registers.
  @param[in]      SkipPrint       - Debug prints control flag.

  @retval         LocalRegLoopCnt - Returns number of registers saved/restored.
**/
UINT32
SaveRestoreRegisters (
  IN OUT  MrcParameters   *const MrcData,
  IN      SaveDataControl const *SaveRestoreDataCtrlPtr,
  IN      UINT32  SizeoOfData,
  IN      UINT32  RegOffset,
  IN OUT  UINT32  **McRegister,
  IN      UINT8   SaveRestore,
  IN      BOOLEAN SkipPrint
)
{
  UINT32                Offset;
  UINT32                Index;
  UINT32                Value;
  UINT64                Value64;
  UINT32                LocalRegLoopCnt;
  MrcDebug              *Debug;
  MrcDebugMsgLevel      DebugLevel;

  Debug = &MrcData->Outputs.Debug;
  DebugLevel = SkipPrint ? MSG_LEVEL_NEVER : MSG_LEVEL_NOTE;
  Value64 = 0;
  Value = 0;

  LocalRegLoopCnt = 0;
  for (Index = 0; Index < SizeoOfData / sizeof (SaveDataControl); Index++) {
    for (Offset = SaveRestoreDataCtrlPtr->StartMchbarOffset; Offset <= SaveRestoreDataCtrlPtr->EndMchbarOffset; Offset += sizeof (UINT32)) {
      LocalRegLoopCnt++;
      if (SaveRestore == SaveReg) {
        if (SaveRestoreDataCtrlPtr->EndMchbarOffset == R64BIT) {
          Value64 = MrcReadCR64 (MrcData, RegOffset + Offset);
          MRC_DEBUG_MSG (Debug, DebugLevel, "\n Index: %02d, StartMchbarOffset: %08x, Value: 0x%016llx,  ", Index, Offset + RegOffset, Value64);
          *(UINT64 *)(*McRegister)++ = Value64;
          (*McRegister)++;
          break;
        } else {
          Value = MrcReadCR (MrcData, RegOffset + Offset);
          MRC_DEBUG_MSG (Debug, DebugLevel, "\n Index: %02d, StartMchbarOffset: %08x, Value0x: %08x, ", Index, Offset + RegOffset, Value);
          *(*McRegister)++ = Value;
        }
      } else {
        if (SaveRestoreDataCtrlPtr->EndMchbarOffset == R64BIT) {
          Value64 = *(UINT64 *)(*McRegister)++;
          MrcWriteCR64 (MrcData, RegOffset + Offset, Value64);
          MRC_DEBUG_MSG (Debug, DebugLevel, "\n Index: %02d, StartMchbarOffset: %08x, Value0x: %016llx,  ", Index, Offset + RegOffset, Value64);
          (*McRegister)++;
          break;
        } else {
          Value = *(*McRegister)++;
          MrcWriteCR (MrcData, RegOffset + Offset, Value);
          MRC_DEBUG_MSG (Debug, DebugLevel, "\n Index: %02d, StartMchbarOffset: %08x, Value0x: %08x, ", Index, Offset + RegOffset, Value);
        }
      }
    }
    SaveRestoreDataCtrlPtr++;
  }
  return LocalRegLoopCnt;
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
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
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
  UINT32                RegOffset;
  UINT32                Byte;
  UINT8                 *SpdBegin;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT8                 SaveRestore;  // @todo used for future simplification of single save/restore function call.
  UINT32                LocalRegLoopCnt;
  UINT32                TotalRegCnt;
  BOOLEAN               SkipPrint;


  // Copy channel and DIMM information to the data area that will be saved.
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  SaveData    = &MrcData->Save.Data;
  SaveHeader  = &MrcData->Save.Header;
  Debug       = &Outputs->Debug;
  SaveRestore = SaveReg; // @todo used for future simplification of single save/restore function call. Filled from input parameter.
  SkipPrint   = TRUE;

  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  TotalRegCnt = 0;
  LocalRegLoopCnt = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
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
      ChannelSave->ValidSubChBitMask= ChannelOut->ValidSubChBitMask;
      ChannelSave->ValidByteMask    = ChannelOut->ValidByteMask;
      ChannelSave->Status           = ChannelOut->Status;
      for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelSave->Timing[Profile], (UINT8 *) &ChannelOut->Timing[Profile], sizeof (MrcTiming));
      }
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelSave->Dimm[Dimm], (UINT8 *) &ChannelOut->Dimm[Dimm], sizeof (MrcDimmOut));
        SpdIn = &ChannelIn->Dimm[Dimm].Spd.Data;
        if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
          SpdBegin = (UINT8 *) &SpdIn->Ddr4.ManufactureInfo;
          ChannelSave->DimmSave [Dimm].SpdDramDeviceType = SpdIn->Ddr4.Base.DramDeviceType.Data;
          ChannelSave->DimmSave [Dimm].SpdModuleType = SpdIn->Ddr4.Base.ModuleType.Data;
          ChannelSave->DimmSave [Dimm].SpdModuleMemoryBusWidth = SpdIn->Ddr4.Base.ModuleMemoryBusWidth.Data;
        } else {
          //@todo Add DDR5
          SpdBegin = (UINT8 *) &SpdIn->Ddr4.ManufactureInfo;
          ChannelSave->DimmSave [Dimm].SpdDramDeviceType = SpdIn->Ddr4.Base.DramDeviceType.Data;
          ChannelSave->DimmSave [Dimm].SpdModuleType = SpdIn->Ddr4.Base.ModuleType.Data;
          ChannelSave->DimmSave [Dimm].SpdModuleMemoryBusWidth = SpdIn->Ddr4.Base.ModuleMemoryBusWidth.Data;
        }
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
  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint != MrcSaGvPoint4)) {
     // If SA GV is enabled, only save the Common registers at the last point (currently High).
  } else {

    McRegister = SaveData->RegSaveCommon;
    RegOffset  = 0;
    LocalRegLoopCnt = SaveRestoreRegisters (MrcData, SaveDataCommon, sizeof (SaveDataCommon), RegOffset, (void *)&McRegister, SaveRestore, SkipPrint);
    TotalRegCnt += LocalRegLoopCnt;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\tSaveDataCommon RegCnt : %04d, TotalRegCnt : %04d,", LocalRegLoopCnt, TotalRegCnt);
    LocalRegLoopCnt = 0;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n Controller : %d", Controller);
      // Common per-Mc registers
      RegOffset = INC_OFFSET_CALC_CH (MC0_MAD_INTER_CHANNEL_REG, MC1_MAD_INTER_CHANNEL_REG, Controller);
      LocalRegLoopCnt = SaveRestoreRegisters (MrcData, SaveDataCommonPerMc, sizeof (SaveDataCommonPerMc), RegOffset, (void *)&McRegister, SaveRestore, SkipPrint);
      TotalRegCnt += LocalRegLoopCnt;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\tSaveDataCommonPerMc RegCnt : %04d, TotalRegCnt : %04d",LocalRegLoopCnt, TotalRegCnt);
      LocalRegLoopCnt = 0;
      // Common per-Ch registers
      for (Channel = 0; Channel < MAX_CHANNEL / 2; Channel++) {
        RegOffset = INC_OFFSET_CALC_MC_CH (MC0_CH0_CR_WMM_READ_CONFIG_REG, MC1_CH0_CR_WMM_READ_CONFIG_REG, Controller, MC0_CH1_CR_WMM_READ_CONFIG_REG, Channel);
        LocalRegLoopCnt = SaveRestoreRegisters (MrcData, SaveDataCommonPerCh, sizeof (SaveDataCommonPerCh), RegOffset, (void *)&McRegister, SaveRestore, SkipPrint);
      }
      TotalRegCnt += LocalRegLoopCnt;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\tSaveDataCommonPerCh RegCnt : %04d, TotalRegCnt : %04d", LocalRegLoopCnt, TotalRegCnt);
      LocalRegLoopCnt = 0;
      // Common per-byte registers
      for (Byte = 0; Byte < MRC_NUM_BYTE_GROUPS; Byte++) {
        RegOffset = INC_OFFSET_CALC_MC_CH (DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG, DATA0CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG, Controller, DATA1CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG, Byte);
        LocalRegLoopCnt = SaveRestoreRegisters (MrcData, SaveDataCommonPerByte, sizeof (SaveDataCommonPerByte), RegOffset, (void *)&McRegister, SaveRestore, SkipPrint);
      }
      TotalRegCnt += LocalRegLoopCnt;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\tSaveDataCommonPerByte RegCnt : %04d, TotalRegCnt : %04d", LocalRegLoopCnt, TotalRegCnt);
    }

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n Common section: saved %d bytes\n", (McRegister - SaveData->RegSaveCommon) * 4);
    if ((UINT32) (McRegister - SaveData->RegSaveCommon) > MRC_REGISTER_COUNT_COMMON) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n\tERROR: RegSaveCommon overflow!\n");
      return mrcFail;
    }
  } // if SAGV and Low point
  // Sagv save registers total count
  TotalRegCnt = 0;
  McRegister = SaveData->SaGvRegSave[MrcIntData->SaGvPoint];
  McRegisterStart = McRegister;

  // Each Sagv Save register count
  LocalRegLoopCnt = 0;
  RegOffset       = 0;
  LocalRegLoopCnt = SaveRestoreRegisters (MrcData, SaveDataSaGv, sizeof (SaveDataSaGv), RegOffset, (void *)&McRegister, SaveRestore, SkipPrint);

  TotalRegCnt += LocalRegLoopCnt;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\tSaveDataSaGv RegCnt : %04d, TotalRegCnt : %04d", LocalRegLoopCnt, TotalRegCnt);
  LocalRegLoopCnt = 0;
  // Sagv Mc registers
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n Controller : %d", Controller);
    for (Channel = 0; Channel < MAX_CHANNEL / 2; Channel++) {
      RegOffset = INC_OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_PRE_REG, MC1_CH0_CR_TC_PRE_REG, Controller, MC0_CH1_CR_TC_PRE_REG, Channel);
      LocalRegLoopCnt = SaveRestoreRegisters (MrcData, SaveDataSaGvMc, sizeof (SaveDataSaGvMc), RegOffset, (void *)&McRegister, SaveRestore, SkipPrint);
    }
    TotalRegCnt += LocalRegLoopCnt;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\t SaveDataSaGvMc RegCnt : %04d, TotalRegCnt : %04d", LocalRegLoopCnt, TotalRegCnt);
  }
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    LocalRegLoopCnt = 0;
    // Per-byte registers
    for (Byte = 0; Byte < MRC_NUM_BYTE_GROUPS; Byte++) {
      RegOffset = INC_OFFSET_CALC_MC_CH (DATA0CH0_CR_DDRDATADQRANK0LANE0_REG, DATA0CH1_CR_DDRDATADQRANK0LANE0_REG, Controller, DATA1CH0_CR_DDRDATADQRANK0LANE0_REG, Byte);
      LocalRegLoopCnt = SaveRestoreRegisters (MrcData, SaveDataSaGvPerByte, sizeof (SaveDataSaGvPerByte), RegOffset, (void *)&McRegister, SaveRestore, SkipPrint);
    }
    TotalRegCnt += LocalRegLoopCnt;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\t SaveDataSaGvPerByte RegCnt : %04d, TotalRegCnt : %04d", LocalRegLoopCnt, TotalRegCnt);
  }
  LocalRegLoopCnt = 0;
  // Common per-CCC registers
  for (Channel = 0; Channel < (MAX_CONTROLLER * MAX_CCC_PER_CHANNEL); Channel++) {
    RegOffset = INC_OFFSET_CALC_CH (CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG, CH1CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG, Channel);
    LocalRegLoopCnt = SaveRestoreRegisters (MrcData, SaveDataSaGvCcc, sizeof (SaveDataSaGvCcc), RegOffset, (void *)&McRegister, SaveRestore, SkipPrint);
  }
  TotalRegCnt += LocalRegLoopCnt;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\tSaveDataSaGvCcc RegCnt : %04d, TotalRegCnt : %04d\n", LocalRegLoopCnt, TotalRegCnt);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " SAGV section: saved %d bytes\n", (McRegister - McRegisterStart) * 4);
  if ((UINT32) (McRegister - McRegisterStart) > MRC_REGISTER_COUNT_SAGV) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nERROR: RegSaveHigh/Mid/Low overflow!\n");
    return mrcFail;
  }

  MrcVersionGet (MrcData, &SaveData->Version);
  SaveData->CpuModel               = Inputs->CpuModel;
  SaveData->CpuStepping            = Inputs->CpuStepping;
  SaveData->CpuFamily              = Inputs->CpuFamily;
  SaveData->Frequency[MrcIntData->SaGvPoint] = Outputs->Frequency;
  SaveData->BurstLength            = Outputs->BurstLength;
  SaveData->HighFrequency          = Outputs->HighFrequency;
  SaveData->MemoryClock            = Outputs->MemoryClock;
  SaveData->Ratio                  = Outputs->Ratio;
  SaveData->RefClk                 = Outputs->RefClk;
  SaveData->EccSupport             = Outputs->EccSupport;
  SaveData->DdrType                = Outputs->DdrType;
  SaveData->Lpddr                  = Outputs->Lpddr;
  SaveData->Lp4x                   = Outputs->Lp4x;
  SaveData->LpByteMode             = Outputs->LpByteMode;
  SaveData->EnhancedChannelMode    = Outputs->EnhancedChannelMode;
  SaveData->TCRSensitiveHynixDDR4  = Outputs->TCRSensitiveHynixDDR4;
  SaveData->TCRSensitiveMicronDDR4 = Outputs->TCRSensitiveMicronDDR4;
  SaveData->XmpProfileEnable       = Outputs->XmpProfileEnable;
  SaveData->LpddrEctDone           = Outputs->LpddrEctDone;
  SaveData->MaxChannels            = Outputs->MaxChannels;
  SaveData->Vdd2Mv                 = Outputs->Vdd2Mv;
  SaveData->MeStolenSize           = Inputs->MeStolenSize;
  SaveData->ImrAlignment           = Inputs->ImrAlignment;
  SaveData->Gear2[MrcIntData->SaGvPoint] = Outputs->Gear2;
  SaveData->FreqMax                = Outputs->FreqMax;
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

  SaveData->SaMemCfgCrc = MrcCalculateCrc32 ((UINT8 *) Inputs->SaMemCfgAddress.Ptr, Inputs->SaMemCfgSize);
  SaveHeader->Crc       = MrcCalculateCrc32 ((UINT8 *) SaveData, sizeof (MrcSaveData));
  MrcData->Save.Size    = sizeof (MrcSave);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saved data CRC = %xh\n", SaveHeader->Crc);

  return mrcSuccess;
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

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
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
          if (SaveData->DdrType == MRC_DDR_TYPE_DDR4) {
            SpdBegin = (UINT8 *) &SpdIn->Ddr4.ManufactureInfo;
            SpdIn->Ddr4.Base.DramDeviceType.Data = ChannelSave->DimmSave[Dimm].SpdDramDeviceType;
            SpdIn->Ddr4.Base.ModuleType.Data     = ChannelSave->DimmSave[Dimm].SpdModuleType;
            SpdIn->Ddr4.Base.ModuleMemoryBusWidth.Data = ChannelSave->DimmSave[Dimm].SpdModuleMemoryBusWidth;
          } else {
            //@todo Add DDR5
            SpdBegin = (UINT8 *) &SpdIn->Ddr4.ManufactureInfo;
          }
          // Restore just enough SPD information so it can be passed out in the HOB.
          // If SAGV enabled, only do this on the last pass, due to LPDDR VendorId patching.
          if ((Inputs->SaGv != MrcSaGvEnabled) || (SaGvPoint == MrcSaGvPoint4)) {
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
  Outputs->HighFrequency          = SaveData->HighFrequency;
  Outputs->MemoryClock            = SaveData->MemoryClock;
  Outputs->BurstLength            = SaveData->BurstLength;
  Outputs->Ratio                  = SaveData->Ratio;
  Outputs->RefClk                 = SaveData->RefClk;
  Outputs->EccSupport             = SaveData->EccSupport;
  Outputs->DdrType                = SaveData->DdrType;
  Outputs->Lpddr                  = SaveData->Lpddr;
  Outputs->EnhancedChannelMode    = SaveData->EnhancedChannelMode;
  Outputs->Lp4x                   = SaveData->Lp4x;
  Outputs->LpByteMode             = SaveData->LpByteMode;
  Outputs->TCRSensitiveHynixDDR4  = SaveData->TCRSensitiveHynixDDR4;
  Outputs->TCRSensitiveMicronDDR4 = SaveData->TCRSensitiveMicronDDR4;
  Outputs->XmpProfileEnable       = SaveData->XmpProfileEnable;
  Outputs->MaxChannels            = SaveData->MaxChannels;
  Outputs->Vdd2Mv                 = SaveData->Vdd2Mv;
  Outputs->Gear2 = SaveData->Gear2[SaGvPoint];
  Outputs->Frequency = SaveData->Frequency[SaGvPoint];
  if (Outputs->Gear2 == 1) {
    Outputs->Gear2Ever = 1;
  }

  Outputs->MemoryClock      = ConvertFreq2Clock (MrcData, Outputs->Frequency);
  Outputs->Ratio            = MrcFrequencyToRatio (MrcData, Outputs->Frequency, Outputs->RefClk, Inputs->BClkFrequency);
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "SAGV point %u: Frequency=%u, tCK=%ufs, Ratio=%u, Gear%d, Inputs->BClkFrequency=%x,Outputs->RefClk=%d\n",
    SaGvPoint,
    Outputs->Frequency,
    Outputs->MemoryClock,
    Outputs->Ratio,
    Outputs->Gear2 ? 2 : 1,
    Inputs->BClkFrequency,
    Outputs->RefClk
  );

  Outputs->LpddrEctDone     = SaveData->LpddrEctDone;

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
  MrcDebug              *Debug;
  UINT32                *McRegisterStart;
  UINT32                RegOffset;
  UINT32                Controller;
  UINT32                Channel;
  UINT32                Byte;
  BOOLEAN               SkipPrint;

  Debug     = &MrcData->Outputs.Debug;
  SkipPrint = TRUE;
  McRegisterStart = McRegister;

  RegOffset = 0;
  SaveRestoreRegisters (MrcData, SaveDataSaGv, sizeof (SaveDataSaGv), RegOffset, (void *)&McRegister, RestoreReg, SkipPrint);

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    // per channel registers
    for (Channel = 0; Channel < MAX_CHANNEL / 2; Channel++) {
      RegOffset = INC_OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_PRE_REG, MC1_CH0_CR_TC_PRE_REG, Controller, MC0_CH1_CR_TC_PRE_REG, Channel);
      SaveRestoreRegisters (MrcData, SaveDataSaGvMc, sizeof (SaveDataSaGvMc), RegOffset, (void *)&McRegister, RestoreReg, SkipPrint);
    }
  }
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    // Per-byte registers
    for (Byte = 0; Byte < MRC_NUM_BYTE_GROUPS; Byte++) {
      RegOffset = INC_OFFSET_CALC_MC_CH (DATA0CH0_CR_DDRDATADQRANK0LANE0_REG, DATA0CH1_CR_DDRDATADQRANK0LANE0_REG, Controller, DATA1CH0_CR_DDRDATADQRANK0LANE0_REG, Byte);
      SaveRestoreRegisters (MrcData, SaveDataSaGvPerByte, sizeof (SaveDataSaGvPerByte), RegOffset, (void *)&McRegister, RestoreReg, SkipPrint);
    }
  }
  // Common per-CCC registers
  for (Channel = 0; Channel < (MAX_CONTROLLER * MAX_CCC_PER_CHANNEL); Channel++) {
    RegOffset = INC_OFFSET_CALC_CH (CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG, CH1CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG, Channel);
    SaveRestoreRegisters (MrcData, SaveDataSaGvCcc, sizeof (SaveDataSaGvCcc), RegOffset, (void *)&McRegister, RestoreReg, SkipPrint);
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
#ifdef UP_SERVER_FLAG
  const MrcInput        *Inputs;
#endif
  MrcDebug              *Debug;
  MrcIntOutput          *MrcIntData;
  MrcOutput             *Outputs;
  MrcSaveData           *SaveData;
  MrcStatus             Status;
  UINT32                *McRegister;
  UINT32                RegOffset;
  UINT32                Controller;
  UINT32                Channel;
  UINT32                Byte;
  BOOLEAN               SkipPrint;

#ifdef UP_SERVER_FLAG
  Inputs   = &MrcData->Inputs;
#endif
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  SaveData = &MrcData->Save.Data;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  SkipPrint = TRUE;

  // @todo - RCOMP must be executed by MRC first.

  // First restore the Common section
  McRegister = SaveData->RegSaveCommon;
  RegOffset   = 0;
  SaveRestoreRegisters (MrcData, SaveDataCommon, sizeof (SaveDataCommon), RegOffset, (void *)&McRegister, RestoreReg, SkipPrint);

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    // Common per-Mc registers
    RegOffset = INC_OFFSET_CALC_CH (MC0_MAD_INTER_CHANNEL_REG, MC1_MAD_INTER_CHANNEL_REG, Controller);
    SaveRestoreRegisters (MrcData, SaveDataCommonPerMc, sizeof (SaveDataCommonPerMc), RegOffset, (void *)&McRegister, RestoreReg, SkipPrint);

    // Common per-Ch registers
    for (Channel = 0; Channel < MAX_CHANNEL / 2; Channel++) {
      RegOffset = INC_OFFSET_CALC_MC_CH (MC0_CH0_CR_WMM_READ_CONFIG_REG, MC1_CH0_CR_WMM_READ_CONFIG_REG, Controller, MC0_CH1_CR_WMM_READ_CONFIG_REG, Channel);
      SaveRestoreRegisters (MrcData, SaveDataCommonPerCh, sizeof (SaveDataCommonPerCh), RegOffset, (void *)&McRegister, RestoreReg, SkipPrint);
    }

    // Common per-byte registers
    for (Byte = 0; Byte < MRC_NUM_BYTE_GROUPS; Byte++) {
      RegOffset = INC_OFFSET_CALC_MC_CH (DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG, DATA0CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG, Controller, DATA1CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG, Byte);
      SaveRestoreRegisters (MrcData, SaveDataCommonPerByte, sizeof (SaveDataCommonPerByte), RegOffset, (void *)&McRegister, RestoreReg, SkipPrint);
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\tCommon section: Restored %d bytes\n", (McRegister - SaveData->RegSaveCommon) * 4);
  if ((UINT32) (McRegister - SaveData->RegSaveCommon) > MRC_REGISTER_COUNT_COMMON) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nERROR: RegSaveCommon overflow!\n");
    return mrcFail;
  }

  // Now restore the SAGV section, RegSaveHigh is used when SAGV is disabled
  McRegister = SaveData->SaGvRegSave[MrcIntData->SaGvPoint];

  Status = MrcRestoreTrainingSaGv (MrcData, McRegister);
  if (Status != mrcSuccess) {
    return Status;
  }

  // Must be the last register written for basic init (Must be after MC Init).
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRLASTCR_REG, 1);
  ForceRcomp (MrcData);

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
