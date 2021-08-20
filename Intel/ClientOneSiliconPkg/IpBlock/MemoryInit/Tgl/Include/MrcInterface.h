/** @file
  This file includes all the data structures that the MRC considers "global data".

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
#ifndef _MrcInterface_h_
#define _MrcInterface_h_
#include "MrcTypes.h"

///
/// DRAM Mode register numbers.
/// mrMR0 till mrMR6 can also be used as index into DimmOut->MR[],
/// for other MRs use MrcModeRegisterIndex enum.
///
typedef enum {
  mrMR0  = 0,
  mrMR1  = 1,
  mrMR2  = 2,
  mrMR3  = 3,
  mrMR4  = 4,
  mrMR5  = 5,
  mrMR6  = 6,
  mrMR10 = 10,
  mrMR11 = 11,
  mrMR12 = 12,
  mrMR13 = 13,
  mrMR14 = 14,
  mrMR15 = 15,
  mrMR16 = 16,
  mrMR17 = 17,
  mrMR18 = 18,
  mrMR20 = 20,
  mrMR21 = 21,
  mrMR22 = 22,
  mrMR23 = 23,
  mrMR25 = 25,
  mrMR28 = 28,
  mrMR30 = 30,
  mrMR37 = 37,
  mrMR40 = 40,
  mrMR41 = 41,
  mrDuplicateMrInstance = 100, ///< This is the delimiter for MR's where we have the same MR address but different values in a MR sequence.
  mrMR12b = 120 ///< This is a special case to handle ByteMode instance of Upper device for CA Vref.
} MrcModeRegister;
#define MRC_MR_DUP_SCALE  (10)

///
/// DRAM Mode register indices in DimmOut
///
typedef enum {
  mrIndexMR0,
  mrIndexMR1,
  mrIndexMR2,
  mrIndexMR3,
  mrIndexMR4,
  mrIndexMR5,
  mrIndexMR6,
  mrIndexMR10,
  mrIndexMR11,
  mrIndexMR12,
  mrIndexMR12Upper, ///< This is specific to LPDDR5 where we can configure CA Vref on each Byte with Byte-Mode devices.
  mrIndexMR13,
  mrIndexMR14,
  mrIndexMR15,
  mrIndexMR16,
  mrIndexMR17,
  mrIndexMR18,
  mrIndexMR20,
  mrIndexMR21,
  mrIndexMR22,
  mrIndexMR23,
  mrIndexMR25,
  mrIndexMR28,
  mrIndexMR30,
  mrIndexMR37,
  mrIndexMR40,
  mrIndexMR41,
  mrIndexMax
} MrcModeRegisterIndex;

#define MAX_CPU_SOCKETS         (1)       ///< The maximum number of CPUs per system.
#define MAX_CONTROLLER          (2)       ///< The maximum number of memory controllers per CPU socket.
#define MAX_CHANNEL             (4)       ///< The maximum number of channels per memory controller.
#define MAX_CHANNEL_SHARE_REGS  (2)       ///< The maximum number of channels per memory controller that share registers
#define MAX_SYS_CHANNEL         (MAX_CONTROLLER * MAX_CHANNEL)  ///< The maximum number of channels per CPU socket.
#define MAX_SUB_CHANNEL         (2)       ///< The maximum number of subchannels per channel.
#define MAX_PHY_CHANNEL         (MAX_SUB_CHANNEL * MAX_CHANNEL)  ///< The maximum number of channels treating each sub channels as an independent channel, per controller.
#define MAX_MC_CHANNEL_DDR4     (2)       ///< The maximum number of channels per memory controller for DDR4.
#define MAX_DIMMS_IN_CHANNEL    (2)       ///< The maximum number of DIMMs per channel.
#define MAX_RANK_IN_DIMM        (2)       ///< The maximum number of ranks per DIMM.
#define MAX_RANK_IN_CHANNEL     (4)       ///< The maximum number of ranks per channel.
#define MAX_BANKS               (32)      ///< Max Number of Banks supported in CPGC.  This is a combination of BankGroup and Bank.
#define MAX_DDR4_x8_BANKS       (16)      ///< Max Number of Banks with x8 devices in DDR4.  This is a combination of BankGroup and Bank.
#define MAX_DDR4_x16_BANKS      (8)       ///< Max Number of Banks with x16 devices in DDR4.  This is a combination of BankGroup and Bank.
#define MAX_SDRAM_IN_DIMM       (9)       ///< The maximum number of SDRAMs per DIMM when ECC is enabled.
#define MAX_BYTE_IN_LP_CHANNEL  (2)       ///< Max number of Bytes in a LPDDR Channel
#define MAX_CCC_PER_CHANNEL     (4)       ///< Max number of CCC blocks per Channel
#define MAX_MR_IN_DIMM          (mrIndexMax)  ///< Maximum number of mode registers in a DIMM.
#define MAX_DEVICES_IN_DDR4     (8)       ///< The maximum number of SDRAMs per DDR4 DIMM.
#define MAX_BITS                (8)       ///< BITS per byte.
#define MAX_STROBE              (18)      ///< Number of strobe groups.
#define MAX_DQ                  (72)      ///< Number of Dq bits used by the rank.
#define CHAR_BITS               (8)       ///< Number of bits in a char.
#define PSMI_SIZE_MB            (64)      ///< Define the max size of PSMI needed in MB
#define MAX_SAGV_POINTS         (4)       ///< Defines the number of frequency points supported.
#define BCLK_DEFAULT            (100 * 1000 * 1000) ///< BCLK default value, in Hertz.
#define BCLK_RFI_FREQ_CONVERSION (1000 * 1000 / 8)  ///< BCLK RFI freq conversion to 7.3 mailbox format
#define MAX_COMMAND_GROUPS      (4)       ///< 4 Command groups for DDR4 and 1 for LPDDR per controller/channel
#define MAX_DCC_CLOCK_PI        (128)     ///< CLK PI Range (0 - 127) Only used for DCC Look Up Table
#define MAX_DCC_TX_DQS_DQ_PI    (128)     ///< Tx Dqs/Dq PI Range (0 - 127) Only used for DCC Look Up Table
#define MAX_EDGES               (2)       ///< Maximum number of edges.
#define MAX_DYNAMIC_FREQ        (3)       ///< Maximum number of dynamic frequencies supported.
#define MAX_GEARS               (2)       ///< Max numbers of Gears supported by MRC.
#define MAX_SPD_PAGE_COUNT      (2)
#define MAX_SPD_PAGE_SIZE       (256)
#define MAX_SPD_SIZE            (MAX_SPD_PAGE_SIZE * MAX_SPD_PAGE_COUNT)

#define MRC_CHANNEL_DISABLE_CMOS_ADDR (0x4A) ///< Memory channel disable, 0 = both enabled, 1 = channel 0 disabled, 2 = channel 1 disabled.
#define MRC_DDR_FREQ_CMOS_ADDR        (0x4B) ///< Limit DDR speed using CMOS override
#define MRC_DEBUG_LEVEL_CMOS_ADDR     (0x4C) ///< Debug level override (32-bit value)
#define MRC_RESET_COUNT_CMOS_ADDR     (0x70) ///< 1-byte counter for reset cycling test. 0 = reset cycling disabled.

#define SPD4_MANUF_START       320         ///< The starting point for the SPD manufacturing data.
#define SPD4_MANUF_END         328         ///< The ending point for the SPD manufacturing data.
#define SPDLP_MANUF_START      320         ///< The starting point for the SPD manufacturing data.
#define SPDLP_MANUF_END        328         ///< The ending point for the SPD manufacturing data.

#include "CpuRegs.h"
#include "MrcSpdData.h"
#include "MrcRmtData.h"
#include "MrcCommonTypes.h"
#pragma pack (push, 1)


///
//////////////////////////////////////////////////////////////////////////////////////
///                           OEM platform  routines and types                      //
//////////////////////////////////////////////////////////////////////////////////////
///
/// define the oem check points the OEM can define more point and locate them in the code.
///
typedef enum {
  OemFastBootPermitted,     ///<  before fast boot.
  OemRestoreNonTraining,
  OemPrintInputParameters,  ///<  before printing input parameters.
  OemSpdProcessingRun,      ///<  before SPD processing code.
  OemSetOverridePreSpd,     ///<  before set overrides pre SPD.
  OemSetOverride,           ///<  before set overrides.
  OemMcCapability,          ///<  before MC capability.
  OemMcInitRun,             ///<  before mc init code.
  OemMcMemoryMap,           ///<  before memory map.
  OemMcResetRun,            ///<  before jedec reset.
  OemPreTraining,           ///<  before the training.
  OemMcTrainingRun,         ///<  before training code
  OemEarlyCommandTraining,  ///<  before Early Command training
  OemSenseAmpTraining,      ///<  before Sense Amp Training
  OemReadMprTraining,       ///<  before Read MPR Training
  OemReceiveEnable,         ///<  before Read Leveling
  OemJedecWriteLeveling,    ///<  before Jedec Write Leveling
  OemWriteLevelingFlyby,    ///<  before Write Leveling FlyBy
  OemWriteDqDqs,            ///<  before Write Timing Centering
  OemWriteVoltage,          ///<  before Write Voltage Centering
  OemReadVoltage,           ///<  before Read Voltage Centering
  OemEarlyWriteDqDqs2D,     ///<  before Early Write Timing Centering 2D
  OemEarlyReadDqDqs2D,      ///<  before Early Read Timing Centering 2D
  OemEarlyReadMprDqDqs2D,   ///<  before Early MPR Read Timing Centering 2D
  OemEarlyRmpr2DPostEct,    ///<  before Early MPR Read Timing Centering 2D after ECT
  OemReadDqDqs,             ///<  before Read Timing Centering
  OemPerBitDeskewCal,       ///<  before Per Bit Deskew Calibration
  OemDdr4Map,               ///<  before DDR4 PDA Mapping
  OemVddqTraining,          ///<  before Vddq Training
  OemDimmRonTraining,       ///<  before DIMM Ron Training
  OemDimmODTTraining,       ///<  before DIMM ODT Training
  OemDimmOdtCaTraining,     ///<  before DIMM ODT CA Training
  OemWriteDriveStrengthEq,  ///<  before Write Drive Strength/Equalization 2D Training
  OemWriteDriveUpDn,        ///<  before Write Drive Strength Up/Dn 2D Training
  OemWriteSlewRate,         ///<  before Write Slew Rate Training
  OemReadODTTraining,       ///<  before Read ODT algorithm.
  OemReadEQTraining,        ///<  before Read Equalization Training.
  OemReadAmplifierPower,    ///<  before Read Amplifier Power.
  OemOptimizeComp,          ///<  before Comp Optimization Training.
  OemPowerSavingMeter,      ///<  before PowerSavingMeter step.
  OemWriteDqDqs2D,          ///<  before Write Timing Centering 2D.
  OemReadDqDqs2D,           ///<  before Read Timing Centering 2D.
  OemCmdVoltCentering,      ///<  before Command Voltage Centering.
  OemWriteVoltCentering2D,  ///<  before Write Voltage Centering 2D.
  OemReadVoltCentering2D,   ///<  before Read Voltage Centering 2D.
  OemLateCommandTraining,   ///<  before Late Command training.
  OemRoundTripLatency,      ///<  before Round Trip Latency Training.
  OemTurnAroundTimes,       ///<  before Turn Around Times.
  OemRcvEnCentering1D,      ///<  before Receive Enable Centering.
  OemSaveMCValues,          ///<  before saving memory controller values.
  OemRmt,                   ///<  before RMT crosser tool.
  OemMemTest,               ///<  before Memory testing.
  OemRestoreTraining,       ///<  before Restoring Training Values.
  OemJedecResetDdr4Fast,    ///<  before JEDEC reset for DDR4 in Fast flow.
  OemTxDqTcoCompTraining,   ///<  before TxDqTCO Comp training.
  OemTxDqsTcoCompTraining,  ///<  before TxDqsTCO Comp training.
  OemClkTcoCompTraining,    ///<  before ClkTCO Comp training.
  OemCmdDriveStrengthEq,    ///<  before CMD/CTL TxEq/Drive Strength training
  OemCmdDriveUpDn,          ///<  before CMD/CTL Drive Strength training
  OemCmdSlewRate,           ///<  before CMD/CTL/CLK Slew Rate training
  OemVccDllBypassTraining,  ///<  before VccDLL Bypass training
  OemReadVrefDecapTraining, ///<  before RxVref Decap training
  OemPanicVttDnLpTraining,  ///<  before PanicVttDnLp Training
  OemSelfRefreshExit,       ///<  before Self Refresh Exit.
  OemNormalMode,            ///<  before Normal Mode on non-cold boots.
  OemThermalConfig,         ///<  after Normal Mode, set Thermal config values.
  OemTxtAliasCheck,         ///<  before TxT Alias Check Call.
  OemAliasCheck,            ///<  before alias checking on cold boots.
  OemHwMemInit,
  OemPostTraining,          ///<  after the training.
  OemForceOltm,             ///<  before MrcForceOltm
  OemMrcActivate,           ///<  before MrcActivate call.
  OemSaGvSwitch,            ///<  before SA GV switch
  OemEngPerfGain,           ///<  before Energy Performance Gain.
  OemMrcDone,               ///<  call to MrcOemCheckPoint when MRC was done.
  OemFrequencySet,          ///<  do operation before frequency set.
  OemFrequencySetDone,      ///<  do operation after frequency set.
  OemStartMemoryConfiguration,
  OemBeforeNormalMode,      ///<  call to MrcOemCheckPoint before normal mode is enabled.
  OemAfterNormalMode,       ///<  call to MrcOemCheckPoint after normal mode is enabled.
  OemMrcFillRmt,
  OemRetrainMarginCheck,
  OemSsaStopPoint,          ///< Call to SSA stop point.
  OemDdrPhyInit,            ///< before Phy Init Sequence.
  OemFllTraining,
  OemDdrScompInit,          ///< before Scomp Init Sequence.
  OemDdrCompCalPre,         ///< before Comp Calibration PreTraining
  OemOffsetCorrectionPre,   ///< before Offset Correction PreTraining
  OemWriteDqDqsReTraining,
  OemMemorySsInit,          ///< before Initializing Memory SubSystem registers.
  OemMrcSafeMode,           ///< before Safe Mode Updates to MrcInput.
  OemRmtPerBit,             ///< before Rank Margin Tool Per Bit training
  OemDccInit,               ///< before Initializing Duty Cycle Correction
  OemDccReplica,            ///< before Duty Cycle Correction Replica (Pre SAGV)
  OemDccFinal,              ///< before Finalization of Duty Cycle Correction (Post SAGV)
  OemEarlyOverrides,        ///< before Early Overrides
  OemVccDllFFTiming,        ///< before VccDllFFTiming Compensation (Pre Save-Restore)
  OemVccDllFFOffsetCorrection, ///< before VccDllFFOffsetCorrection (Pre Save-Restore)
  OemVccDllKBNCorrection,   ///< before VccDllKickBackNoise Correction (Pre Save-Restore)
  OemWckLeveling,              ///< before Write Clock Leveling for LPDDR5.
  OemVsxhiFFTuning,         ///< before VccDllVsxHiFFTuning (Pre-Save-Restore)
  ///
  ///*********************************************************************************
  ///
  OemNumOfCommands          ///<  Should always be last in the list!
} MrcOemStatusCommand;

typedef UINT8 MrcIteration; ///< MRC invocation sequence number, start with 0 and increment by one each time MRC library is called.
#define MRC_ITERATION_MAX ((1 << ((sizeof (MrcIteration) * 8) - 1)) + ((1 << ((sizeof (MrcIteration) * 8) - 1)) - 1))

#define MAX_RCOMP_TARGETS (5)


typedef struct {
  UINT32 ECT : 1;        ///< BIT0 - Early Command Training
  UINT32 SOT : 1;        ///< BIT1 - Sense Amp Offset Training
  UINT32 ERDMPRTC2D : 1; ///< BIT2 - Early ReadMPR Timing Centering 2D
  UINT32 RDMPRT : 1;     ///< BIT3 - Read MPR Training
  UINT32 RCVET : 1;      ///< BIT4 - Read Leveling Training (RcvEn)
  UINT32 JWRL : 1;       ///< BIT5 - Jedec Write Leveling
  UINT32 EWRTC2D : 1;    ///< BIT6 - Early Write Time Centering 2D
  UINT32 ERDTC2D : 1;    ///< BIT7 - Early Read Time Centering 2D
  UINT32 WRTC1D : 1;     ///< BIT8 - Write Timing Centering 1D
  UINT32 WRVC1D : 1;     ///< BIT9 - Write Voltage Centering 1D
  UINT32 RDTC1D : 1;     ///< BIT10 - Read Timing Centering 1D
  UINT32 DIMMODTT : 1;   ///< BIT11 - Dimm ODT Training
  UINT32 DIMMRONT : 1;   ///< BIT12 - Dimm Ron Training
  UINT32 WRDSEQT : 1;    ///< BIT13 - Write Drive Strength / Equalization Training 2D
  UINT32 WRSRT : 1;      ///< BIT14 - Write Slew Rate Training
  UINT32 RDODTT : 1;     ///< BIT15 - Read ODT Training
  UINT32 RDEQT : 1;      ///< BIT16 - Read Equalization Training
  UINT32 RDAPT : 1;      ///< BIT17 - Read Amplifier Power Training
  UINT32 WRTC2D : 1;     ///< BIT18 - Write Timing Centering 2D
  UINT32 RDTC2D : 1;     ///< BIT19 - Read Timing Centering 2D
  UINT32 WRVC2D : 1;     ///< BIT20 - Write Voltage Centering 2D
  UINT32 RDVC2D : 1;     ///< BIT21 - Read Voltage Centering 2D
  UINT32 CMDVC : 1;      ///< BIT22 - Command Voltage Centering
  UINT32 LCT : 1;        ///< BIT23 - Late Command Training
  UINT32 RTL : 1;        ///< BIT24 - Round Trip latency
  UINT32 TAT : 1;        ///< BIT25 - Turn Around Timing
  UINT32 RMT : 1;        ///< BIT26 - RMT Tool
  UINT32 MEMTST : 1;     ///< BIT27 - Memory Test
  UINT32 ALIASCHK: 1;    ///< BIT28 - SPD Alias Check
  UINT32 RCVENC1D: 1;    ///< BIT29 - Receive Enable Centering 1D
  UINT32 RMC : 1;        ///< BIT30 - Retrain Margin Check
  UINT32 WRDSUDT : 1;    ///< BIT31 - Write Drive Strength Up/Dn independently
} TrainingStepsEn;

typedef struct {
  UINT32 DCC      : 1;   ///< BIT0 - Duty Cycle Correction
  UINT32 RDVC1D   : 1;   ///< BIT1 - Read Voltage Centering 1D
  UINT32 TXTCO    : 1;   ///< BIT2 - Write TCO Comp Training
  UINT32 CLKTCO   : 1;   ///< BIT3 - Clock TCO Comp Training
  UINT32 CMDSR    : 1;   ///< BIT4 - CMD Slew Rate Training
  UINT32 CMDDSEQ  : 1;   ///< BIT5 - CMD Drive Strength and Tx Equalization
  UINT32 DIMMODTCA: 1;   ///< BIT6 - Dimm ODT CA Training
  UINT32 TXTCODQS : 1;   ///< BIT7- Write TCO Dqs Training
  UINT32 CMDDRUD  : 1;   ///< BIT8- CMD/CTL Drive Strength Up/Dn 2D
  UINT32 VCCDLLBP : 1;   ///< BIT9- VccDLL bypass to VccIOG training
  UINT32 PVTTDNLP : 1;   ///< BIT10- PanicVttDnLp Training
  UINT32 RDVREFDC : 1;   ///< BIT11- Read Vref Decap Training
  UINT32 VDDQT    : 1;   ///< BIT12- Vddq Training
  UINT32 RMTBIT   : 1;   ///< BIT13 - Rank Margin Tool Per Bit
  UINT32 RsvdBits   :18;
} TrainingStepsEn2;

typedef enum {
  MrcTmPower,
  MrcTmMargin,
  MrcTmMax
} TrainingModeType;

typedef enum {
  LastRxV,
  LastRxT,
  LastTxV,
  LastTxT,
  LastRcvEna,
  LastWrLevel,
  LastCmdT,
  LastCmdV,
  MAX_RESULT_TYPE
} MrcMarginResult;

typedef enum {
  MSG_LEVEL_NEVER,
  MSG_LEVEL_ERROR,
  MSG_LEVEL_WARNING,
  MSG_LEVEL_NOTE,
  MSG_LEVEL_EVENT,
  MSG_LEVEL_ALGO,
  MSG_LEVEL_HAL,
  MSG_LEVEL_MMIO,
  MSG_LEVEL_CSV,
  MSG_LEVEL_TIME,
  MSG_LEVEL_ALL = MRC_INT32_MAX
} MrcDebugMsgLevel;

/// Define the frequencies that may be possible in the memory controller.
/// Note that not all these values may be supported.
#define fNoInit     (0)
#define f533        (533)
#define f800        (800)
#define f1000       (1000)
#define f1067       (1067)
#define f1100       (1100)
#define f1200       (1200)
#define f1300       (1300)
#define f1333       (1333)
#define f1400       (1400)
#define f1467       (1467)
#define f1500       (1500)
#define f1600       (1600)
#define f1700       (1700)
#define f1733       (1733)
#define f1800       (1800)
#define f1867       (1867)
#define f1900       (1900)
#define f2000       (2000)
#define f2100       (2100)
#define f2133       (2133)
#define f2200       (2200)
#define f2267       (2267)
#define f2300       (2300)
#define f2400       (2400)
#define f2500       (2500)
#define f2533       (2533)
#define f2600       (2600)
#define f2667       (2667)
#define f2700       (2700)
#define f2750       (2750)
#define f2800       (2800)
#define f2900       (2900)
#define f2933       (2933)
#define f3000       (3000)
#define f3067       (3067)
#define f3100       (3100)
#define f3200       (3200)
#define f3300       (3300)
#define f3333       (3333)
#define f3400       (3400)
#define f3467       (3467)
#define f3500       (3500)
#define f3600       (3600)
#define f3700       (3700)
#define f3733       (3733)
#define f3800       (3800)
#define f3867       (3867)
#define f3900       (3900)
#define f4000       (4000)
#define f4100       (4100)
#define f4133       (4133)
#define f4200       (4200)
#define f4267       (4267)
#define f4300       (4300)
#define f4400       (4400)
#define f4500       (4500)
#define f4533       (4533)
#define f4600       (4600)
#define f4667       (4667)
#define f4700       (4700)
#define f4800       (4800)
#define f4900       (4900)
#define f4933       (4933)
#define f5000       (5000)
#define f5067       (5067)
#define f5100       (5100)
#define f5200       (5200)
#define f5300       (5300)
#define f5333       (5333)
#define f5400       (5400)
#define f5467       (5467)
#define f5500       (5500)
#define f5600       (5600)
#define f5700       (5700)
#define f5733       (5733)
#define f5800       (5800)
#define f5867       (5867)
#define f5900       (5900)
#define f6000       (6000)
#define f6100       (6100)
#define f6133       (6133)
#define f6200       (6200)
#define f6267       (6267)
#define f6300       (6300)
#define f6400       (6400)
#define f6500       (6500)
#define f6533       (6533)
#define f6600       (6600)
#define f6667       (6667)
#define f6700       (6700)
#define f6800       (6800)
#define f6900       (6900)
#define f6933       (6933)
#define f7000       (7000)
#define f7067       (7067)
#define f7100       (7100)
#define f7200       (7200)
#define f7300       (7300)
#define f7333       (7333)
#define f7400       (7400)
#define f7467       (7467)
#define f7500       (7500)
#define f7600       (7600)
#define f7700       (7700)
#define f7733       (7733)
#define f7800       (7800)
#define f7867       (7867)
#define f7900       (7900)
#define f8000       (8000)
#define f8100       (8100)
#define f8133       (8133)
#define f8200       (8200)
#define f8267       (8267)
#define f8400       (8400)
#define fInvalid    (0x7FFFFFFF)
typedef UINT32 MrcFrequency;

// Max supported frequency in OC mode
// RefClk133: 63*133 = 8400
// RefClk100: 84*100 = 8400
#define MAX_FREQ_OC_133   f8400
#define MAX_FREQ_OC_100   f8400

// tCK value in femtoseconds for various frequencies
// If Freq is in MHz, then tCK[fs] = 10^9 * 1/(Freq/2)
#define MRC_DDR_533_TCK_MIN      3752345
#define MRC_DDR_800_TCK_MIN      2500000
#define MRC_DDR_1000_TCK_MIN     2000000
#define MRC_DDR_1067_TCK_MIN     1875000
#define MRC_DDR_1100_TCK_MIN     1818182
#define MRC_DDR_1200_TCK_MIN     1666667
#define MRC_DDR_1300_TCK_MIN     1538462
#define MRC_DDR_1333_TCK_MIN     1500000
#define MRC_DDR_1400_TCK_MIN     1428571
#define MRC_DDR_1467_TCK_MIN     1363636
#define MRC_DDR_1500_TCK_MIN     1333333
#define MRC_DDR_1600_TCK_MIN     1250000
#define MRC_DDR_1700_TCK_MIN     1176471
#define MRC_DDR_1733_TCK_MIN     1153846
#define MRC_DDR_1800_TCK_MIN     1111111
#define MRC_DDR_1867_TCK_MIN     1071429
#define MRC_DDR_1900_TCK_MIN     1052632
#define MRC_DDR_2000_TCK_MIN     1000000
#define MRC_DDR_2100_TCK_MIN     952381
#define MRC_DDR_2133_TCK_MIN     938000
#define MRC_DDR_2200_TCK_MIN     909091
#define MRC_DDR_2267_TCK_MIN     882353
#define MRC_DDR_2300_TCK_MIN     869565
#define MRC_DDR_2400_TCK_MIN     833333
#define MRC_DDR_2500_TCK_MIN     800000
#define MRC_DDR_2533_TCK_MIN     789474
#define MRC_DDR_2600_TCK_MIN     769231
#define MRC_DDR_2667_TCK_MIN     750000
#define MRC_DDR_2700_TCK_MIN     740741
#define MRC_DDR_2750_TCK_MIN     727272
#define MRC_DDR_2800_TCK_MIN     714286
#define MRC_DDR_2900_TCK_MIN     689655
#define MRC_DDR_2933_TCK_MIN     681818
#define MRC_DDR_3000_TCK_MIN     666667
#define MRC_DDR_3067_TCK_MIN     652174
#define MRC_DDR_3100_TCK_MIN     645161
#define MRC_DDR_3200_TCK_MIN     625000
#define MRC_DDR_3300_TCK_MIN     606061
#define MRC_DDR_3333_TCK_MIN     600000
#define MRC_DDR_3400_TCK_MIN     588235
#define MRC_DDR_3467_TCK_MIN     576923
#define MRC_DDR_3500_TCK_MIN     571429
#define MRC_DDR_3600_TCK_MIN     555556
#define MRC_DDR_3700_TCK_MIN     540541
#define MRC_DDR_3733_TCK_MIN     535714
#define MRC_DDR_3800_TCK_MIN     526316
#define MRC_DDR_3867_TCK_MIN     517241
#define MRC_DDR_3900_TCK_MIN     512821
#define MRC_DDR_4000_TCK_MIN     500000
#define MRC_DDR_4100_TCK_MIN     487805
#define MRC_DDR_4133_TCK_MIN     483871
#define MRC_DDR_4200_TCK_MIN     476190
#define MRC_DDR_4267_TCK_MIN     468750
#define MRC_DDR_4300_TCK_MIN     465116
#define MRC_DDR_4400_TCK_MIN     454545
#define MRC_DDR_4500_TCK_MIN     444444
#define MRC_DDR_4533_TCK_MIN     441176
#define MRC_DDR_4600_TCK_MIN     434783
#define MRC_DDR_4667_TCK_MIN     428571
#define MRC_DDR_4700_TCK_MIN     425532
#define MRC_DDR_4800_TCK_MIN     416667
#define MRC_DDR_4900_TCK_MIN     408163
#define MRC_DDR_4933_TCK_MIN     405405
#define MRC_DDR_5000_TCK_MIN     400000
#define MRC_DDR_5067_TCK_MIN     394737
#define MRC_DDR_5100_TCK_MIN     392157
#define MRC_DDR_5200_TCK_MIN     384615
#define MRC_DDR_5300_TCK_MIN     377358
#define MRC_DDR_5333_TCK_MIN     375000
#define MRC_DDR_5400_TCK_MIN     370370
#define MRC_DDR_5467_TCK_MIN     365854
#define MRC_DDR_5500_TCK_MIN     363636
#define MRC_DDR_5600_TCK_MIN     357143
#define MRC_DDR_5700_TCK_MIN     350877
#define MRC_DDR_5733_TCK_MIN     348837
#define MRC_DDR_5800_TCK_MIN     344828
#define MRC_DDR_5867_TCK_MIN     340909
#define MRC_DDR_5900_TCK_MIN     338983
#define MRC_DDR_6000_TCK_MIN     333333
#define MRC_DDR_6100_TCK_MIN     327869
#define MRC_DDR_6133_TCK_MIN     326087
#define MRC_DDR_6200_TCK_MIN     322581
#define MRC_DDR_6267_TCK_MIN     319149
#define MRC_DDR_6300_TCK_MIN     317460
#define MRC_DDR_6400_TCK_MIN     312500
#define MRC_DDR_6500_TCK_MIN     307692
#define MRC_DDR_6533_TCK_MIN     306122
#define MRC_DDR_6600_TCK_MIN     303030
#define MRC_DDR_6667_TCK_MIN     300000
#define MRC_DDR_6700_TCK_MIN     298507
#define MRC_DDR_6800_TCK_MIN     294118
#define MRC_DDR_6900_TCK_MIN     289855
#define MRC_DDR_6933_TCK_MIN     288462
#define MRC_DDR_7000_TCK_MIN     285714
#define MRC_DDR_7067_TCK_MIN     283019
#define MRC_DDR_7100_TCK_MIN     281690
#define MRC_DDR_7200_TCK_MIN     277778
#define MRC_DDR_7300_TCK_MIN     273973
#define MRC_DDR_7333_TCK_MIN     272727
#define MRC_DDR_7400_TCK_MIN     270270
#define MRC_DDR_7467_TCK_MIN     267857
#define MRC_DDR_7500_TCK_MIN     266667
#define MRC_DDR_7600_TCK_MIN     263158
#define MRC_DDR_7700_TCK_MIN     259740
#define MRC_DDR_7733_TCK_MIN     258621
#define MRC_DDR_7800_TCK_MIN     256410
#define MRC_DDR_7867_TCK_MIN     254237
#define MRC_DDR_7900_TCK_MIN     253165
#define MRC_DDR_8000_TCK_MIN     250000
#define MRC_DDR_8100_TCK_MIN     246914
#define MRC_DDR_8133_TCK_MIN     245902
#define MRC_DDR_8200_TCK_MIN     243902
#define MRC_DDR_8267_TCK_MIN     241935
#define MRC_DDR_8400_TCK_MIN     238095

/// Define the memory nominal voltage (VDD).
/// Note that not all these values may be supported.
typedef enum {
  VDD_INVALID,
  VDD_0_40    =  400,
  VDD_0_50    =  500,
  VDD_0_60    =  600,
  VDD_0_75    =  750,
  VDD_0_80    =  800,
  VDD_0_90    =  900,
  VDD_1_00    = 1000,
  VDD_1_05    = 1050,
  VDD_1_10    = 1100,
  VDD_1_15    = 1150,
  VDD_1_20    = 1200,
  VDD_1_25    = 1250,
  VDD_1_30    = 1300,
  VDD_1_35    = 1350,
  VDD_1_40    = 1400,
  VDD_1_45    = 1450,
  VDD_1_50    = 1500,
  VDD_1_55    = 1550,
  VDD_1_60    = 1600,
  VDD_1_65    = 1650,
  VDD_1_70    = 1700,
  VDD_1_75    = 1750,
  VDD_1_80    = 1800,
  VDD_1_85    = 1850,
  VDD_1_90    = 1900,
  VDD_1_95    = 1950,
  VDD_2_00    = 2000,
  VDD_2_05    = 2050,
  VDD_2_10    = 2100,
  VDD_2_15    = 2150,
  VDD_2_20    = 2200,
  VDD_2_25    = 2250,
  VDD_2_30    = 2300,
  VDD_2_35    = 2350,
  VDD_2_40    = 2400,
  VDD_2_45    = 2450,
  VDD_2_50    = 2500,
  VDD_2_55    = 2550,
  VDD_2_60    = 2600,
  VDD_2_65    = 2650,
  VDD_2_70    = 2700,
  VDD_2_75    = 2750,
  VDD_2_80    = 2800,
  VDD_2_85    = 2850,
  VDD_2_90    = 2900,
  VDD_2_95    = 2950,
  VDD_MAXIMUM = 0x7FFFFFFF
} MrcVddSelect;

/// SA GV points
typedef enum {
  MrcSaGvPoint1,
  MrcSaGvPoint2,
  MrcSaGvPoint3,
  MrcSaGvPoint4,
  MrcSaGvPointMax
} MrcSaGvPoint;

/// SA GV modes
///  Disabled:  SA GV Disabled, run all MRC tasks
///  Fixed1:    SA GV Disabled, run only MRC tasks marked with MRC_PF_GV_1
///  Fixed2:    SA GV Disabled, run only MRC tasks marked with MRC_PF_GV_2
///  Fixed3:    SA GV Disabled, run only MRC tasks marked with MRC_PF_GV_3
///  Fixed4:    SA GV Disabled, run only MRC tasks marked with MRC_PF_GV_4
///  Enabled:   SA GV Enabled
typedef enum {
  MrcSaGvDisabled,
  MrcSaGvFixed1,
  MrcSaGvFixed2,
  MrcSaGvFixed3,
  MrcSaGvFixed4,
  MrcSaGvEnabled,
} MrcSaGv;

/// DIMM SPD Security Status
typedef enum {
  MrcSpdStatusGood,      ///< Memory is in a secure state.
  MrcSpdStatusAliased,   ///< Memory is aliased.
  MrcSpdStatusLast       ///< Must be last in the list
} MrcSpdStatus;

/// Define the board types.
typedef enum {
  btCRBMB,    ///< 0 - CRB Mobile
  btCRBDT,    ///< 1 - CRB Desktop
  btUser1,    ///< 2 - SV Karkom
  btUser2,    ///< 3 - SV desktop
  btUser3,    ///< 4 - SV miniDVP
  btUser4,    ///< 5 - Ult
  btCRBEMB,   ///< 6 - CRB Embedded
  btUpServer, ///< 7 - Up Server
  btUnknown,  ///< 8 - Unknown
  btMaximum   ///< Delimiter
} MrcBoardType;

/// Define the CPU family/model.
typedef enum {
  cmTGL_ULX_ULT   = CPUID_FULL_FAMILY_MODEL_TIGERLAKE_ULT_ULX,    ///< TigerLake ULT/ULX
  cmTGL_DT_HALO   = CPUID_FULL_FAMILY_MODEL_TIGERLAKE_DT_HALO     ///< TigerLake DT/HALO
} MrcCpuModel;

/// Define the CPU Tick/Tock.
typedef enum {
  cfTgl    = 0,   ///< TigerLake
  cfMax
} MrcCpuFamily;

/// Define the CPU stepping number.
typedef enum {
  /// TigerLake ULX/ULT
  csTglA0         = EnumTglA0,
  csTglB0         = EnumTglB0,
  csTglUlxUltLast = csTglA0,

  /// TigerLake Dt/Halo
  csTglP0         = EnumTglP0,
  csTglQ0         = EnumTglQ0,
  csTglDtHaloLast = csTglP0,
} MrcCpuStepping;

typedef enum {
  CONTROLLER_NOT_PRESENT, ///< There is no controller present in the system.
  CONTROLLER_DISABLED,    ///< There is a controller present but it is disabled.
  CONTROLLER_PRESENT,     ///< There is a controller present and it is enabled.
  MAX_CONTROLLER_STATUS   ///< Delimiter
} MrcControllerSts;

typedef enum {
  CHANNEL_NOT_PRESENT,    ///< There is no channel present on the controller.
  CHANNEL_DISABLED,       ///< There is a channel present but it is disabled.
  CHANNEL_PRESENT,        ///< There is a channel present and it is enabled.
  MAX_CHANNEL_STATUS      ///< Delimiter
} MrcChannelSts;

typedef enum {
  DIMM_ENABLED,           ///< DIMM/rank Pair is enabled, presence will be detected.
  DIMM_DISABLED,          ///< DIMM/rank Pair is disabled, regardless of presence.
  DIMM_PRESENT,           ///< There is a DIMM present in the slot/rank pair and it will be used.
  DIMM_NOT_PRESENT,       ///< There is no DIMM present in the slot/rank pair.
  MAX_DIMM_STATUS         ///< Delimiter
} MrcDimmSts;

typedef enum {
  STD_PROFILE,            ///< Standard DIMM profile select.
  USER_PROFILE,           ///< User specifies various override values.
  XMP_PROFILE1,           ///< XMP enthusiast settings select (XMP profile #1).
  XMP_PROFILE2,           ///< XMP extreme settings select (XMP profile #2).
  MAX_PROFILE             ///< Delimiter
} MrcProfile;

typedef enum {
  MRC_REF_CLOCK_133,      ///< 133MHz reference clock
  MRC_REF_CLOCK_100,      ///< 100MHz reference clock
  MRC_REF_CLOCK_66,       ///< 66MHz reference clock
  MRC_REF_CLOCK_MAXIMUM   ///< Delimiter
} MrcRefClkSelect;        ///< This value times the MrcClockRatio determines the MrcFrequency.

typedef enum {
  MRC_FREQ_INVALID       = 0,
  MRC_FREQ_133           = (MRC_BIT0 << MRC_REF_CLOCK_133), // Bit 0
  MRC_FREQ_100           = (MRC_BIT0 << MRC_REF_CLOCK_100), // Bit 1
  MRC_FREQ_MAX                                              // Delimiter
} MrcFreqFlag;

typedef UINT32 MrcBClkRef;   ///< Base clock, in Hertz, Default is 100MHz or leave at zero for default.

// This encoding matches SC_GS_CFG.DRAM_technology and MAD_INTER_CHANNEL.DDR_TYPE registers
typedef enum {
  MRC_DDR_TYPE_DDR4     = 0,
  MRC_DDR_TYPE_DDR5     = 1,
  MRC_DDR_TYPE_LPDDR5   = 2,
  MRC_DDR_TYPE_LPDDR4   = 3,
  MRC_DDR_TYPE_UNKNOWN,  ///< Delimiter
  MAX_MRC_DDR_TYPE
} MrcDdrType;

typedef enum {
  MrcIterationClock,
  MrcIterationCmd,
  MrcIterationCtl,
  MrcIterationMax
} MrcIterationType;

typedef enum {
  UpmLimit,
  PowerLimit,
  RetrainLimit,
  MarginLimitMax
} MRC_MARGIN_LIMIT_TYPE;


typedef enum {
  HardwareRhp,
  Refresh2x
} MrcRhpType;

typedef enum {
  OneIn2To1 = 1,
  OneIn2To2,
  OneIn2To3,
  OneIn2To4,
  OneIn2To5,
  OneIn2To6,
  OneIn2To7,
  OneIn2To8,
  OneIn2To9,
  OneIn2To10,
  OneIn2To11,
  OneIn2To12,
  OneIn2To13,
  OneIn2To14,
  OneIn2To15
} MrcRhProbType;

typedef enum {
  MRC_POST_CODE,
  MRC_POST_CODE_WRITE,
  MRC_POST_CODE_READ,
  MRC_POST_CODE_MAX
} MrcDebugPostCode;

/// Enumeration used to determine which test engine the product supports.
typedef enum {
  MrcTeCpgc20,
  MrcTeMax
} MRC_TE_TYPE;

/// Enumeration for ODT Mode selection via Input Parameter and current ODT Mode.
typedef enum {
  MrcOdtModeDefault,
  MrcOdtModeVtt,
  MrcOdtModeVddq,
  MrcOdtModeVss,
  MrcOdtModeMax
} MRC_ODT_MODE_TYPE;

/// Enumeration for RxMode selection.
typedef enum {
  MrcRxModeMatchedN,
  MrcRxModeMatchedP,
  MrcRxModeUnmatchedRxWRload,
  MrcRxModeUnmatchedRxWPpath,
  MrcRxModeMax
} MRC_RX_MODE_TYPE;

/// Generic enumeration interface for parameters that are Auto, Enable, Disable inputs
typedef enum {
  MrcAuto,
  MrcEnable,
  MrcDisable,
  MrcEnDisAutoMax
} MRC_EN_DIS_AUTO_TYPE;

typedef struct {
  POINTER_STRUCT MrcData;
  POINTER_STRUCT Stream;
  POINTER_STRUCT Start;
  POINTER_STRUCT End;
  POINTER_STRUCT Current;
  MrcDebugMsgLevel Level;
  UINT16 PostCode[MRC_POST_CODE_MAX];
  POINTER_STRUCT TopStackAddr;     ///< Initial stack address.
  POINTER_STRUCT LowestStackAddr;  ///< Track the lowest stack address used through MrcPrintfVaList()
} MrcDebug;

typedef UINT16 MrcPostCode;
typedef UINT8  MrcClockRatio;  ///< This value times the MrcRefClkSelect determines the MrcFrequency.
typedef UINT32 MrcGfxDataSize; ///< The size of the stolen graphics data memory, in MBytes.
typedef UINT32 MrcGfxGttSize;  ///< The size of the graphics translation table, in MBytes.


/// This data structure contains all the "DDR power saving data" values that are considered output by the MRC.
/// The following are memory controller level definitions. All channels on a controller are set to these values.
typedef struct {
  BOOLEAN    BaseFlag;      ///< Indicates if the base line of power was already calculated.
  UINT16     BaseSavingRd;  ///< Indicates the base line of power consume by the ddr on read.
  UINT16     BaseSavingWr;  ///< Indicates the base line of power consume by the ddr on write.
  UINT16     BaseSavingCmd; ///< Indicates the base line of power consume by the ddr on command.
  UINT16     MrcSavingRd;   ///< Indicates the power consume by the ddr on read at the end of MRC.
  UINT16     MrcSavingWr;   ///< Indicates the power consume by the ddr on write at the end of MRC.
  UINT16     MrcSavingCmd;  ///< Indicates the power consume by the ddr on command at the end of MRC.
} MrcOdtPowerSaving;

/// The memory controller capabilities.
typedef struct {
    UINT32 A;
    UINT32 B;
    UINT32 C;
    UINT32 E;
} MrcCapabilityId;

/// MRC version description.
typedef struct {
  UINT8  Major;  ///< Major version number
  UINT8  Minor;  ///< Minor version number
  UINT8  Rev;    ///< Revision number
  UINT8  Build;  ///< Build number
} MrcVersion;

/// Memory map configuration information.
typedef struct {
  UINT32     TomMinusMe;
  UINT32     ToludBase;
  UINT32     BdsmBase;
  UINT32     GttBase;
  UINT32     GraphicsControlRegister;
  UINT32     TsegBase;
  BOOLEAN    ReclaimEnable;
  UINT32     RemapBase;
  UINT32     RemapLimit;
  UINT32     TouudBase;
  UINT32     TotalPhysicalMemorySize;
  UINT32     NearMemorySize; // 2LM
  UINT32     PMemBase;       // 2LM
  UINT32     MeStolenBase;
  UINT32     MeStolenSize;
  UINT32     DprSize;
  UINT32     PrmrrBase;
  UINT32     LowestBase;
  UINT32     ILMem; // interleaved memory regions between controllers
} MrcMemoryMap;

/// DIMM timings
typedef struct {
  UINT32 tCK;     ///< Offset 0  Memory cycle time, in femtoseconds.
  UINT16 NMode;   ///< Offset 4  Number of tCK cycles for the channel DIMM's command rate mode.
  UINT16 tCL;     ///< Offset 6  Number of tCK cycles for the channel DIMM's CAS latency.
  UINT16 tCWL;    ///< Offset 8  Number of tCK cycles for the channel DIMM's minimum CAS write latency time.
  UINT16 tFAW;    ///< Offset 10 Number of tCK cycles for the channel DIMM's minimum four activate window delay time.
  UINT16 tRAS;    ///< Offset 12 Number of tCK cycles for the channel DIMM's minimum active to precharge delay time.
  UINT16 tRCDtRP; ///< Offset 14 Number of tCK cycles for the channel DIMM's minimum RAS# to CAS# delay time and Row Precharge delay time.
  UINT16 tREFI;   ///< Offset 16 Number of tCK cycles for the channel DIMM's minimum Average Periodic Refresh Interval.
  UINT16 tRFC;    ///< Offset 18 Number of tCK cycles for the channel DIMM's minimum refresh recovery delay time.
  UINT16 tRFCpb;  ///< Offset 20 Number of tCK cycles for the channel DIMM's minimum per bank refresh recovery delay time.
  UINT16 tRFC2;   ///< Offset 22 Number of tCK cycles for the channel DIMM's minimum refresh recovery delay time.
  UINT16 tRFC4;   ///< Offset 24 Number of tCK cycles for the channel DIMM's minimum refresh recovery delay time.
  UINT16 tRPab;   ///< Offset 26 Number of tCK cycles for the channel DIMM's minimum row precharge delay time for all banks.
  UINT16 tRRD;    ///< Offset 28 Number of tCK cycles for the channel DIMM's minimum row active to row active delay time.
  UINT16 tRRD_L;  ///< Offset 30 Number of tCK cycles for the channel DIMM's minimum row active to row active delay time for same bank groups.
  UINT16 tRRD_S;  ///< Offset 32 Number of tCK cycles for the channel DIMM's minimum row active to row active delay time for different bank groups.
  UINT16 tRTP;    ///< Offset 34 Number of tCK cycles for the channel DIMM's minimum internal read to precharge command delay time.
  UINT16 tWR;     ///< Offset 36 Number of tCK cycles for the channel DIMM's minimum write recovery time.
  UINT16 tWTR;    ///< Offset 38 Number of tCK cycles for the channel DIMM's minimum internal write to read command delay time.
  UINT16 tWTR_L;  ///< Offset 40 Number of tCK cycles for the channel DIMM's minimum internal write to read command delay time for same bank groups.
  UINT16 tWTR_S;  ///< Offset 42 Number of tCK cycles for the channel DIMM's minimum internal write to read command delay time for different bank groups.
  UINT16 tCCD_L;  ///< Offset 44 Number of tCK cycles for the channel DIMM's minimum CAS-to-CAS delay for same bank group.
} MrcTiming;

typedef struct {
  INT32 Mtb;    ///< Medium time base.
  INT32 Ftb;    ///< Fine time base.
} MrcTimeBase;

typedef struct {
  UINT8  Left;   ///< The left side of the timing eye.
  UINT8  Center; ///< The center of the timing eye.
  UINT8  Right;  ///< The right side of the timing eye.
} MrcDqTimeMargin;

typedef struct {
  UINT8  High;   ///< The high side of the Vref eye.
  UINT8  Center; ///< The center of the Vref eye.
  UINT8  Low;    ///< The low side of the Vref eye.
} MrcDqVrefMargin;

typedef struct {
  UINT8  Left;   ///< The left side of the command eye.
  UINT8  Right;  ///< The right side of the command eye.
  UINT8  High;   ///< The high side of the command eye.
  UINT8  Low;    ///< The low side of the command eye.
} MrcCommandMargin;

typedef struct {
  UINT8  Left;   ///< The left side of the receive enable eye.
  UINT8  Right;  ///< The right side of the receive enable eye.
} MrcRecvEnMargin;

typedef struct {
  UINT8  Left;   ///< The left side of the write leveling eye.
  UINT8  Right;  ///< The right side of the write leveling eye.
} MrcWrLevelMargin;

typedef struct {
  UINT8     SpdValid[sizeof (MrcSpd) / (CHAR_BITS * sizeof (UINT8))]; ///< Each valid bit maps to SPD byte.
  UINT8     MrcSpdString[3]; ///< The SPD data start marker. This must be located at the start of the SPD data structure. It includes this string plus the following flag.
  union {
    struct {
      UINT8   DimmNumber    : 4; ///< SPD zero based DIMM number.
      UINT8   ChannelNumber : 3; ///< SPD zero based channel number.
      UINT8   MdSocket      : 1; ///< 0 = memory down, 1 = socketed.
    } Bit;
    UINT8 Data;
  } Flag;
  MrcSpd Data;            ///< The SPD data for each DIMM. SPDGeneral field = 0 when absent.
} MrcSpdData;

typedef UINT8        (*MRC_IO_READ_8)               (UINT32 IoAddress);
typedef UINT16       (*MRC_IO_READ_16)              (UINT32 IoAddress);
typedef UINT32       (*MRC_IO_READ_32)              (UINT32 IoAddress);
typedef void         (*MRC_IO_WRITE_8)              (UINT32 IoAddress, UINT8 Value);
typedef void         (*MRC_IO_WRITE_16)             (UINT32 IoAddress, UINT16 Value);
typedef void         (*MRC_IO_WRITE_32)             (UINT32 IoAddress, UINT32 Value);
typedef UINT8        (*MRC_MMIO_READ_8)             (UINT32 Address);
typedef UINT16       (*MRC_MMIO_READ_16)            (UINT32 Address);
typedef UINT32       (*MRC_MMIO_READ_32)            (UINT32 Address);
typedef UINT64       (*MRC_MMIO_READ_64)            (UINT32 Address);
typedef UINT8        (*MRC_MMIO_WRITE_8)            (UINT32 Address, UINT8 Value);
typedef UINT16       (*MRC_MMIO_WRITE_16)           (UINT32 Address, UINT16 Value);
typedef UINT32       (*MRC_MMIO_WRITE_32)           (UINT32 Address, UINT32 Value);
typedef UINT64       (*MRC_MMIO_WRITE_64)           (UINT32 Address, UINT64 Value);
typedef UINT8        (*MRC_SMBUS_READ_8)            (UINT32 Address, UINT32 *Status);
typedef UINT16       (*MRC_SMBUS_READ_16)           (UINT32 Address, UINT32 *Status);
typedef UINT8        (*MRC_SMBUS_WRITE_8)           (UINT32 Address, UINT8 Value, UINT32 *Status);
typedef UINT16       (*MRC_SMBUS_WRITE_16)          (UINT32 Address, UINT16 Value, UINT32 *Status);
typedef UINT32       (*MRC_GET_PCI_DEVICE_ADDRESS)  (UINT8 Bus, UINT8 Device, UINT8 Function, UINT8 Offset);
typedef UINT32       (*MRC_GET_PCIE_DEVICE_ADDRESS) (UINT8 Bus, UINT8 Device, UINT8 Function, UINT8 Offset);
typedef void         (*MRC_GET_RTC_TIME)            (UINT8 *Second, UINT8 *Minute, UINT8 *Hour, UINT8 *Day, UINT8 *Month, UINT16 *Year);
typedef UINT64       (*MRC_GET_CPU_TIME)            (void);
typedef void *       (*MRC_MEMORY_COPY)             (UINT8 *Destination, UINT8 *Source, UINT32 NumBytes);
typedef void *       (*MRC_MEMORY_SET_BYTE)         (UINT8 *Destination, UINT32 NumBytes, UINT8 Value);
typedef void *       (*MRC_MEMORY_SET_WORD)         (UINT16 *Destination, UINT32 NumWords, UINT16 Value);
typedef void *       (*MRC_MEMORY_SET_DWORD)        (UINT32 *Destination, UINT32 NumDwords, UINT32 Value);
typedef UINT64       (*MRC_LEFT_SHIFT_64)           (UINT64 Data, UINT32 NumBits);
typedef UINT64       (*MRC_RIGHT_SHIFT_64)          (UINT64 Data, UINT32 NumBits);
typedef UINT64       (*MRC_MULT_U64_U32)            (UINT64 Multiplicand, UINT32 Multiplier);
typedef UINT64       (*MRC_DIV_U64_U64)             (UINT64 Dividend, UINT64 Divisor, UINT64 *Remainder);
typedef BOOLEAN      (*MRC_GET_SPD_DATA)            (UINT8 BootMode, UINT8 SpdAddress, UINT8 *SpdData, UINT8 *Ddr3Table, UINT32 Ddr3TableSize, UINT8 *Ddr4Table, UINT32 Ddr4TableSize, UINT8 *LpddrTable, UINT32 LpddrTableSize);
typedef BOOLEAN      (*MRC_GET_RANDOM_NUMBER)       (UINT32 *Rand);
typedef UINT32       (*MRC_CPU_MAILBOX_READ)        (UINT32 Type, UINT32 Command, UINT32 *Value, UINT32 *Status);
typedef UINT32       (*MRC_CPU_MAILBOX_WRITE)       (UINT32 Type, UINT32 Command, UINT32 Value, UINT32 *Status);
typedef UINT32       (*MRC_GET_MEMORY_VDD)          (void *MrcData, UINT32 DefaultVdd);
typedef UINT32       (*MRC_SET_MEMORY_VDD)          (void *MrcData, UINT32 DefaultVdd, UINT32 Value);
typedef UINT32       (*MRC_CHECKPOINT)              (void *MrcData, UINT32 CheckPoint, void *Status);
typedef void         (*MRC_DEBUG_HOOK)              (void *GlobalData, UINT16 DisplayDebugNumber);
#ifdef MRC_MINIBIOS_BUILD
typedef void         (*MRC_PRINT_STRING)            (void *MrcData, void *String);
#else
typedef void         (*MRC_PRINT_STRING)            (void *String);
#endif //MRC_MINIBIOS_BUILD
typedef UINT8        (*MRC_GET_RTC_CMOS)            (UINT8 Location);
typedef UINT64       (*MRC_MSR_READ_64)             (UINT32 Location);
typedef UINT64       (*MRC_MSR_WRITE_64)            (UINT32 Location, UINT64 Data);
typedef void         (*MRC_RETURN_FROM_SMC)         (void *GlobalData, UINT32 MrcStatus);
typedef void         (*MRC_DRAM_RESET)              (UINT32 PciEBaseAddress, UINT32 ResetValue);
typedef void         (*MRC_DELAY_NS)                (void *MrcData, UINT32 DelayNs);
typedef void         (*MRC_SET_LOCK_PRMRR)          (UINT64 PrmrrBase, UINT32 PrmrrSize);
typedef void         (*MRC_TME_INIT)                (UINT32 TmeEnable, UINT64 TmeExcludeBase, UINT64 TmeExcludeSize);
typedef void         (*MRC_TXT_ACHECK)              (void);
typedef void         (*MRC_SET_IA_GT_IMR_EXCLUSION)      (UINT32 ImrExcBase, UINT32 ImrExcLimit);
typedef void         (*MRC_SET_IA_GT_IMR_EXCLUSION_LOCK) (void);
typedef EFI_STATUS   (*MRC_SET_GFX_MEM_MAP)         (void);

typedef void         (*MRC_TWOLM_INIT)             (UINT32 NearMemSize, UINT32 ToludBase, UINT32 RemapBase, UINT32 RemapLimit, UINT8 MemBootMode);

/// Function calls that are called external to the MRC.
///   This structure needs to be aligned with SA_FUNCTION_CALLS.  All functions that are
///   not apart of SA_FUNCTION_CALLS need to be at the end of the structure.
typedef struct {
  MRC_IO_READ_8               MrcIoRead8;
  MRC_IO_READ_16              MrcIoRead16;
  MRC_IO_READ_32              MrcIoRead32;
  MRC_IO_WRITE_8              MrcIoWrite8;
  MRC_IO_WRITE_16             MrcIoWrite16;
  MRC_IO_WRITE_32             MrcIoWrite32;
  MRC_MMIO_READ_8             MrcMmioRead8;
  MRC_MMIO_READ_16            MrcMmioRead16;
  MRC_MMIO_READ_32            MrcMmioRead32;
  MRC_MMIO_READ_64            MrcMmioRead64;
  MRC_MMIO_WRITE_8            MrcMmioWrite8;
  MRC_MMIO_WRITE_16           MrcMmioWrite16;
  MRC_MMIO_WRITE_32           MrcMmioWrite32;
  MRC_MMIO_WRITE_64           MrcMmioWrite64;
  MRC_SMBUS_READ_8            MrcSmbusRead8;
  MRC_SMBUS_READ_16           MrcSmbusRead16;
  MRC_SMBUS_WRITE_8           MrcSmbusWrite8;
  MRC_SMBUS_WRITE_16          MrcSmbusWrite16;
  MRC_GET_PCI_DEVICE_ADDRESS  MrcGetPciDeviceAddress;
  MRC_GET_PCIE_DEVICE_ADDRESS MrcGetPcieDeviceAddress;
  MRC_GET_RTC_TIME            MrcGetRtcTime;
  MRC_GET_CPU_TIME            MrcGetCpuTime;
  MRC_MEMORY_COPY             MrcCopyMem;
  MRC_MEMORY_SET_BYTE         MrcSetMem;
  MRC_MEMORY_SET_WORD         MrcSetMemWord;
  MRC_MEMORY_SET_DWORD        MrcSetMemDword;
  MRC_LEFT_SHIFT_64           MrcLeftShift64;
  MRC_RIGHT_SHIFT_64          MrcRightShift64;
  MRC_MULT_U64_U32            MrcMultU64x32;
  MRC_DIV_U64_U64             MrcDivU64x64;
  MRC_GET_SPD_DATA            MrcGetSpdData;
  MRC_GET_RANDOM_NUMBER       MrcGetRandomNumber;
  MRC_CPU_MAILBOX_READ        MrcCpuMailboxRead;
  MRC_CPU_MAILBOX_WRITE       MrcCpuMailboxWrite;
  MRC_GET_MEMORY_VDD          MrcGetMemoryVdd;
  MRC_SET_MEMORY_VDD          MrcSetMemoryVdd;
  MRC_CHECKPOINT              MrcCheckpoint;
  MRC_DEBUG_HOOK              MrcDebugHook;
  MRC_PRINT_STRING            MrcPrintString;
  MRC_GET_RTC_CMOS            MrcRtcCmos;
  MRC_MSR_READ_64             MrcReadMsr64;
  MRC_MSR_WRITE_64            MrcWriteMsr64;
  MRC_RETURN_FROM_SMC         MrcReturnFromSmc;
  MRC_DRAM_RESET              MrcDramReset;
  MRC_DELAY_NS                MrcDelayNs;
  // End of synchronization to SA_FUNCTION_CALLS
  MRC_SET_LOCK_PRMRR          MrcSetLockPrmrr;
  MRC_TME_INIT                MrcTmeInit;
  MRC_TXT_ACHECK              MrcTxtAcheck;
  MRC_SET_IA_GT_IMR_EXCLUSION      MrcSetIaGtImrExclusion;
  MRC_SET_IA_GT_IMR_EXCLUSION_LOCK MrcSetIaGtImrExclusionLock;
  MRC_SET_GFX_MEM_MAP         MrcSetGfxMemMap;
  MRC_TWOLM_INIT              MrcTwoLmInit;
} MRC_FUNCTION;

///*****************************************
/// Output related "global data" structures.
///*****************************************
/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are SDRAM level definitions. All ranks on a rank are set to these values.

/* Commented out until needed, in order to save space.
typedef struct {
} MrcSdramOut;
*/

/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are rank level definitions. All ranks on a DIMM are set to these values.
typedef struct {
//MrcSdramOut Sdram[MAX_SDRAM_IN_DIMM];       ///< The following are SDRAM level definitions.
  UINT16      MR[MAX_MR_IN_DIMM];             ///< DRAM mode register values, indexed by MrcModeRegisterIndex enum.
  UINT8       Ddr4PdaMr6[MAX_SDRAM_IN_DIMM];  ///< DDR4 MR6[6:0] for per-DRAM VrefDQ (PDA)
//UINT8       Device[MAX_SDRAM_IN_DIMM];      ///< Which Bytes are tied to which Device where BIT0 set means Byte 0 - needed for PDA Mapping, not used currently
} MrcRankOut;

/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are DIMM level definitions. All ranks on a DIMM are set to these values.
typedef struct {
  MrcDimmSts     Status;                  ///< See MrcDimmSts for the definition of this field.
  MrcTiming      Timing[MAX_PROFILE];     ///< The DIMMs timing values.
  MrcVddSelect   VddVoltage[MAX_PROFILE]; ///< The voltage (VDD) setting for this DIMM, per profile.
  BOOLEAN        EccSupport;              ///< TRUE if ECC is enabled and supported on this DIMM.
  BOOLEAN        IgnoreNonEccDimm;        ///< TRUE if a DIMM without ECC capability should be ignored.
  BOOLEAN        AddressMirrored;         ///< TRUE if the DIMM is address mirrored.
  BOOLEAN        SelfRefreshTemp;         ///< TRUE if the DIMM supports self refresh extended operating temperature range (SRT).
  BOOLEAN        AutoSelfRefresh;         ///< TRUE if the DIMM supports automatic self refresh (ASR).
  BOOLEAN        PartialSelfRefresh;      ///< TRUE if the DIMM supports Partial Array Self Refresh (PASR).
  BOOLEAN        OnDieThermalSensor;      ///< TRUE if the DIMM supports On-die Thermal Sensor (ODTS) Readout.
  BOOLEAN        ExtendedTemperRange;     ///< TRUE if the DIMM supports Extended Temperature Range (ETR).
  BOOLEAN        ExtendedTemperRefresh;   ///< TRUE if the DIMM supports 1x Extended Temperature Refresh rate, FALSE = 2x.
  MrcDdrType     DdrType;                 ///< DDR type: DDR4, DDR5, LPDDR4, LPDDR5
  MEMORY_PACKAGE ModuleType;              ///< Module type: UDIMM, SO-DIMM, etc.
  UINT32         DimmCapacity;            ///< DIMM size in MBytes.
  UINT32         RowSize;                 ///< The DIMMs row address size.
  UINT16         ColumnSize;              ///< The DIMMs column address size.
  UINT16         Crc;                     ///< Calculated CRC16 of the DIMM's provided SPD. Can be used to detect DIMM change.
  UINT8          RankInDimm;              ///< The number of ranks in this DIMM.
  UINT8          Banks;                   ///< Number of banks the DIMM contains.
  UINT8          BankGroups;              ///< Number of bank groups the DIMM contains.
  UINT8          PrimaryBusWidth;         ///< DIMM primary bus width.
  UINT8          DiePerSdramPackage;      ///< Number of Die in the DRAM Package (LPDDR Only)
  UINT8          ChannelsPerSdramPackage; ///< Number of Channels in the DRAM Package (LPDDR Only)
  UINT8          NumLpSysChannel;         ///< Number of channels at PrimaryBusWidth for this DIMM's SPD (LPDDR Only)
  UINT8          SdramWidth;              ///< DIMM SDRAM width.
  UINT8          SdramWidthIndex;         ///< DIMM SDRAM width index (0 = x4, 1 = x8, 2 = x16, 3 = x32).
  UINT8          DensityIndex;            ///< Total SDRAM capacity index (0 = 256Mb, 1 = 512Mb, 2 = 1Gb, etc).
  UINT8          tMAC;                    ///< Maximum Activate Count for pTRR.
  UINT8          ReferenceRawCard;        ///< Indicates which JEDEC reference design raw card was used as the basis for the module assembly.
  UINT8          XmpSupport;              ///< Indicates if XMP profiles are supported. 0 = None, 1 = XMP1 only, 2 = XMP2 only, 3 = All.
  UINT8          XmpRevision;             ///< Indicates the XMP revision of this DIMM. 0 = None, 12h = 1.2, 13h = 1.3.
  MrcFrequency   Speed;                   ///< Max DIMM speed in the current profile - needed  for SMBIOS
  MrcRankOut     Rank[MAX_RANK_IN_DIMM];  ///< The following are rank level definitions.
} MrcDimmOut;

/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are channel level definitions. All DIMMs on a memory channel are set to these values.
typedef struct {
  MrcChannelSts     Status;                                                       ///< Indicates whether this channel should be used.
  MrcTiming         Timing[MAX_PROFILE];                                          ///< The channel timing values.
  MrcTimeBase       TimeBase[MAX_DIMMS_IN_CHANNEL][MAX_PROFILE];                  ///< Medium and fine timebases for each DIMM in the channel and each memory profile.
  UINT32            Capacity;                                                     ///< Amount of memory in this channel, in MBytes.
  UINT32            DimmCount;                                                    ///< Number of valid DIMMs that exist in the channel.
  UINT32            DataCompOffset[MAX_SDRAM_IN_DIMM];                            ///< DataCompOffset CR
  UINT32            CmdCompOffset;                                                ///< CmdCompOffset CR
  UINT32            ClkCompOffset;                                                ///< ClkCompOffset CR
  UINT32            CtlCompOffset;                                                ///< CtrlCompOffset CR
  UINT16            WlDelay[MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];              ///< WlDelay PI Code
  MrcCommandMargin  Command[MAX_RANK_IN_CHANNEL];                                 ///< Cmd setting
  MrcDqTimeMargin   RxDqPb[MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];     ///< Rx PerBit Pi Code
  MrcDqTimeMargin   TxDqPb[MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];     ///< Tx PerBit Pi Code
  MrcDqVrefMargin   RxDqVrefPb[MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS]; ///< Rx PerBit Vref
  MrcDqVrefMargin   TxDqVrefPb[MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS]; ///< Rx PerBit Vref
  MrcRecvEnMargin   ReceiveEnable[MAX_RANK_IN_CHANNEL];                           ///< Receive enable per rank
  MrcWrLevelMargin  WriteLevel[MAX_RANK_IN_CHANNEL];                              ///< Write leveling per rank
  UINT8             ValidRankBitMask;                                             ///< Bit map of the populated ranks per channel
  UINT8             ValidSubChBitMask;                                            ///< Bit map of the populated 32-bit sub-channels per 64-bit channel (2 bits)
  UINT16            ValidByteMask;                                                ///< Bit map of the populated bytes per channel
  UINT8             ByteStart[MAX_SUB_CHANNEL];                                   ///< Defines the CPU Byte start associated with the SubChannel requested as the index to the array.
  UINT8             ByteEnd[MAX_SUB_CHANNEL];                                     ///< Defines the CPU Byte limit associated with the SubChannel requested as the index to the array.
  MrcDimmOut        Dimm[MAX_DIMMS_IN_CHANNEL];                                   ///< DIMM specific output variables.
  UINT8             CpgcChAssign;                                                 ///< Stores the CpgcSeqCfgA.Channel_Assign field
} MrcChannelOut;

/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are memory controller level definitions. All channels on a controller are set to these values.
typedef struct {
  MrcControllerSts Status;                     ///< Indicates whether this controller should be used.
  UINT16           DeviceId;                   ///< The PCI device id of this memory controller.
  UINT8            RevisionId;                 ///< The PCI revision id of this memory controller.
  UINT8            ChannelCount;               ///< Number of valid channels that exist on the controller.
  UINT8            ValidChBitMask;             ///< Bit mask of valid channels on this memory controller.
  UINT8            FirstPopCh;                 ///< First populated channel
  MrcChannelOut    Channel[MAX_CHANNEL];       ///< The following are channel level definitions.
} MrcControllerOut;

///********************************************
/// Saved data related "global data" structures.
///********************************************
/// This data structure contains all the "global data" values that are considered to be needed
/// by the MRC between power state transitions (S0->S3->S0) and also fast and warm boot modes.
/// The following are DIMM level definitions.
typedef struct {
  UINT8 SpdDramDeviceType;       ///< Save SPD DramDeviceType information needed for SMBIOS structure creation.
  UINT8 SpdModuleType;           ///< Save SPD ModuleType information needed for SMBIOS structure creation.
  UINT8 SpdModuleMemoryBusWidth; ///< Save SPD ModuleMemoryBusWidth information needed for SMBIOS structure creation.
  UINT8 SpdSave[MAX_SPD_SAVE];   ///< Save SPD Manufacturing information needed for SMBIOS structure creation.
} MrcDimmSave;

/// This data structure contains all the "global data" values that are considered to be needed
/// by the MRC between power state transitions (S0->S3->S0) and also fast and warm boot modes.
/// The following are channel level definitions.
typedef struct {
  MrcChannelSts Status;                               ///< Indicates whether this channel should be used.
  UINT32        DimmCount;                            ///< Number of valid DIMMs that exist in the channel.
  UINT8         ValidRankBitMask;                     ///< Bit map of the populated ranks per channel
  UINT8         ValidSubChBitMask;                    ///< Bit map of the populated sub channels per channel.
  UINT16        ValidByteMask;                        ///< Bit map of the populated bytes per channel.
  MrcTiming     Timing[MAX_PROFILE];                  ///< The channel timing values.
  MrcDimmOut    Dimm[MAX_DIMMS_IN_CHANNEL];           ///< Save the DIMM output characteristics.
  MrcDimmSave   DimmSave[MAX_DIMMS_IN_CHANNEL];       ///< Save SPD information needed for SMBIOS structure creation.
} MrcChannelSave;

/// This data structure contains all the "global data" values that are considered to be needed
/// by the MRC between power state transitions (S0->S3->S0) and also fast and warm boot modes.
/// The following are controller level definitions.
typedef struct {
  MrcControllerSts  Status;               ///< Indicates whether this controller should be used.
  UINT8             ChannelCount;         ///< Number of valid channels that exist on the controller.
  MrcChannelSave    Channel[MAX_CHANNEL]; ///< The following are channel level definitions.
} MrcContSave;

/// This data structure contains all the "global data" values that are considered to be needed
/// by the MRC between power state transitions (S0->S3->S0) and also fast and warm boot modes.
/// The following are system level definitions.
typedef struct {
  UINT32 Crc;                  ///< The CRC-32 of the data in this structure.
} MrcSaveHeader;

// ------- IMPORTANT NOTE --------
// MRC_MC_REGISTER_COUNT in MrcInterface.h should match the table in MrcSaveRestore.c.
// Update this define whenever you add/remove registers from this table.
#define MRC_REGISTER_COUNT_COMMON (1880 / sizeof (UINT32)) ///< The number of MC registers that need to be saved (common)
#define MRC_REGISTER_COUNT_SAGV   (8186 / sizeof (UINT32)) ///< The number of MC registers that need to be saved (per SA GV point)
typedef struct {
  MrcCapabilityId McCapId;                                  ///< The memory controller's capabilities.
  UINT32          RegSaveCommon[MRC_REGISTER_COUNT_COMMON]; ///< The MC registers that are common to both SA GV points.
  UINT32          SaGvRegSave[MAX_SAGV_POINTS][MRC_REGISTER_COUNT_SAGV]; ///< The MC registers for each SA GV point.
  UINT32          MeStolenSize;                             ///< The manageability engine memory size, in Mbyte units.
  UINT32          ImrAlignment;                             ///< The Largest CSE IMR Memory Size, in Mbytes units
  MrcCpuStepping  CpuStepping;                              ///< The last cold boot happened with this CPU stepping.
  MrcCpuModel     CpuModel;                                 ///< The last cold boot happened with this CPU model.
  MrcCpuFamily    CpuFamily;                                ///< The last cold boot happened with this CPU Family.
  MrcVersion      Version;                                  ///< The last cold boot happened with this MRC version.
  UINT32          SaMemCfgCrc;                              ///< The CRC32 of the system agent memory configuration structure.
  MrcContSave     Controller[MAX_CONTROLLER];               ///< The following are controller level definitions.
  MrcFrequency    Frequency[MAX_SAGV_POINTS];               ///< The system's  memory controller frequency.
  BOOLEAN         Gear2[MAX_SAGV_POINTS];                   ///<Current memory frequency gear: 0:Gear1, 1: Gear2.
  MrcFrequency    FreqMax;                                  ///< The system's requested maximum frequency.
  MrcFrequency    HighFrequency;                            ///< High operating frequency, used for LPDDR4/5.
  UINT32          MemoryClock;                              ///< The system's common memory controller clock, in femtoseconds.
  MrcRefClkSelect RefClk;                                   ///< The memory controller is going to use this reference clock.
  MrcClockRatio   Ratio;                                    ///< Request for this memory controller to use this clock ratio.
  MrcVddSelect    VddVoltage[MAX_PROFILE];                  ///< The voltage (VDD) setting for all DIMMs in the system, per profile.
  UINT32          Vdd2Mv;                                   ///< The VR Rail tied to the DRAM.
  BOOLEAN         EccSupport;                               ///< TRUE if ECC is enabled and supported on this controller.
  MrcDdrType      DdrType;                                  ///< DDR type: DDR4, DDR5, LPDDR5, or LPDDR4.
  BOOLEAN         Lpddr;                                    ///< TRUE if Current memory type is LPDDR4 or LPDDR5
  UINT8           MaxChannels;                              ///< Maximum number of channels supported by the controller varies per technology.
  UINT8           BurstLength;                              ///< Burst length in DCLKs
  BOOLEAN         Lp4x;                                     ///< LPDDR4X part was detected.
  BOOLEAN         LpByteMode;                               ///< DRAM die width is x8 (Byte mode).
  BOOLEAN         EnhancedChannelMode;                      ///< Indicates if 64-bit channel is subdivided into two 32-bit channels.
  BOOLEAN         XmpProfileEnable;                         ///< XMP capable DIMMs detected in system (0 = no, 1 = yes).
  BOOLEAN         TCRSensitiveHynixDDR4;                    ///< TCR sensitive Hynix DDR4 in the system
  BOOLEAN         TCRSensitiveMicronDDR4;                   ///< TCR sensitive Micron DDR4 in the system
  BOOLEAN         LpddrEctDone;                             ///< Set to TRUE once Early Command Training on LPDDR is done, and we can run JEDEC Init
#ifdef UP_SERVER_FLAG
  UINT8           ThermOffset[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL]; ///< TSOD Thermal Offset
#endif
} MrcSaveData;

typedef struct {
  UINT32              Size;                        ///< The size of this structure, in bytes. Must be the first entry in this structure.
  MrcDebug            Debug;                       ///< MRC debug related variables used for serial output and debugging purposes.
  MrcVersion          Version;                     ///< The memory reference code version.
  MrcFrequency        FreqMax;                     ///< The requested maximum valid frequency.
  MrcFrequency        Frequency;                   ///< The system's common memory controller frequency based on inputs, SPD, and capabilities.
  MrcFrequency        HighFrequency;               ///< High operating frequency, used for LPDDR4.
  UINT32              MemoryClockMax;              ///< The system's common memory controller maximum clock, in femtoseconds.
  UINT32              MemoryClock;                 ///< The system's common memory controller clock, in femtoseconds.
  MrcRefClkSelect     RefClk;                      ///< The memory controller is going to use this reference clock.
  MrcClockRatio       Ratio;                       ///< Request for this memory controller to use this clock ratio.
  BOOLEAN             Gear2;                       ///< Current memory frequency gear: 0=Gear1, 1=Gear2
  MrcMemoryMap        MemoryMapData;               ///< The system's memory map data.
  MrcGfxDataSize      GraphicsStolenSize;          ///< Graphics Data Stolen Memory size in MB
  MrcGfxGttSize       GraphicsGttSize;             ///< GTT graphics stolen memory size in MB
  UINT32              GtPsmiRegionSize;            ///< PSMI region size in MB
  MrcVddSelect        VddVoltage[MAX_PROFILE];     ///< The currently running voltage (VDD) setting for all DIMMs in the system, per profile.
  MrcVddSelect        VccddqVoltage;               ///< DDR transmitter FIVR voltage rail per technology and per datarate. @todo : Does it need
  UINT16              VccddqLimit;                 ///< Vccddq FIVR upper limit.
                                                   ///< user defined inputs for overclocking?
  BOOLEAN             VddVoltageDone;              ///< To determine if VddVoltageDone update has been done already
  UINT32              Vdd2Mv;                      ///< The VR Rail tied to the DRAM.
  BOOLEAN             EccSupport;                  ///< TRUE if ECC is enabled and supported on this controller.
  BOOLEAN             RestoreMRs;                  ///< Enable/Disable restoring
  BOOLEAN             LpddrEctDone;                ///< Set to TRUE once Early Command Training on LPDDR is done, and we can run JEDEC Init
  BOOLEAN             JedecInitDone;               ///< Set to TRUE once JEDEC Init on LPDDR/DDR4 is done
  BOOLEAN             XmpProfileEnable;            ///< XMP capable DIMMs detected in system (0 = no, 1 = yes).
  BOOLEAN             Capable100;                  ///< The MC is capable of 100 reference clock (0 = no, 1 = yes).
  BOOLEAN             AutoSelfRefresh;             ///< Indicates ASR is supported for all the DIMMS for 2xRefresh
  MrcDdrType          DdrType;                     ///< Current memory type: DDR4, DDR5, LPDDR4, or LPDDR5
  BOOLEAN             Lpddr;                       ///< TRUE if Current memory type is LPDDR4 or LPDDR5
  MrcSpdStatus        SpdSecurityStatus;           ///< Status variable to inform BIOS that memory contains an alias.
  UINT32              MrcTotalChannelLimit;        ///< The maximum allowed memory size per channel, in MBytes.
  UINT8               SdramCount;                  ///< The number of SDRAM components on a DIMM.
  UINT16              Qclkps;                      ///< QCLK period in pS, this is internal MC/DDRIO clock which is impacted by Gear1/2
  UINT16              Dclkps;                      ///< DCLK period in pS, this is internal MC/DDRIO clock which is impacted by Gear1/2
  UINT16              tCKps;                       ///< Memory clock period in pS (external bus clock)
  UINT16              Wckps;                       ///< Write clock period in pS
  UINT16              UIps;                        ///< Data Unit Interval period in pS (half of external bus clock)
  UINT8               DQPat;                       ///< Global Variable storing the current DQPat REUT Test.
  INT8                DQPatLC;                     ///< Global Variable storing the current DQPat Loopcount.
  UINT8               ReutStopType;                ///< Global Variable storing the current test stop type.
  UINT8               ValidRankMask;               ///< Rank bit map.  Includes both channels across memory controllers.
  UINT8               ValidChBitMask;              ///< Channel bit map of the populated channels
  UINT8               ValidMcBitMask;              ///< Memory Controller population bit mask.
  UINT8               ValidSubChMask;              ///< Sub Channel bit map.  Includes both Channels. @todo: Depracate
  BOOLEAN             UpmPwrRetrainFlag;           ///< A flag that indicates if training with higher UPM/PWR limits.
  UINT16              MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES]; ///< Stores last margin measurement.
  MrcOdtPowerSaving   OdtPowerSavingData;          ///< ODT power savings data.
  BOOLEAN             TxDIMMVref[MAX_CHANNEL];     ///< Whether Write DIMM Vref is enabled based on Channel
  UINT32              MchBarWriteCount;            ///< The number of MMIO writes performed during MRC execution.
  UINT32              MchBarReadCount;             ///< The number of MMIO reads performed during MRC execution.
  UINT8               tMAC;                        ///< Maximum Activate Count for pTRR.
  BOOLEAN             Ddr4PdaEnable;               ///< Current status of PDA - if true all the Mr6 operations need to use PDA mode.
  UINT8               SubChCount;                  ///< Number of valid SubChannels that exist.  This is symmetrical per Channel.
  UINT8               MaxChannels;                 ///< Maximum number of channels supported by the controller varies per technology.
  UINT8               BurstLength;                 ///< Burst length in tCK.
  BOOLEAN             EnhancedChannelMode;         ///< Indicates the controller's smallest channel size is bifurcated
  MrcControllerOut    Controller[MAX_CONTROLLER]; ///< The following are controller level definitions.
  BOOLEAN             TCRSensitiveHynixDDR4;       ///< TCR sensitive Hynix DDR4 in the system
  BOOLEAN             TCRSensitiveMicronDDR4;      ///< TCR sensitive Micron DDR4 in the system
  MRC_ODT_MODE_TYPE   OdtMode;                     ///< Specifies the current ODT Mode the DDRIO is set to.
  MRC_RX_MODE_TYPE    RxMode;                      ///< Specifies the receiver to use in the DDRIO.
  BOOLEAN             DramDqOdtEn;                 ///< Specifies if the DRAM DQ ODT is enabled.
  BOOLEAN             Lp4x;                        ///< LPDDR4X part was detected.
  BOOLEAN             LpByteMode;                  ///< DRAM die width is x8 (Byte mode).
  BOOLEAN             Gear2Ever;                   ///< If any SAGV point was Gear2, then this is TRUE otherwise FALSE.
  UINT8               McChBitMask;                 ///< Flat Bit Mask of which CPGC/CADB engines to setup based on MaxChannels per technology.
                                                   ///<     DDR4: Bit 0 - Bit 1 = Mc0Ch0, Mc1Ch0
                                                   ///<      LP4: Bit 0 - Bit 7 = Mc0Ch0, Mc0Ch1, Mc0Ch2, Mc0Ch3, Mc1Ch0, Mc1Ch1, Mc1Ch2, Mc1Ch3
#ifdef BDAT_SUPPORT
  union {
    MRC_BDAT_SCHEMA_LIST_HOB *Pointer;             ///< Pointer to the BDAT schema list.
    UINT64                   Data;
  } BdatSchemasHob;
  union {
    BDAT_MEMORY_DATA_HOB *Pointer;                 ///< Pointer to the BDAT memory data HOB.
    UINT64               Data;
  } BdatMemoryHob[MAX_SCHEMA_LIST_LENGTH];
#endif

#ifdef UP_SERVER_FLAG
  UINT8               ThermOffset[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];                        ///< TSOD Thermal Offset
#endif
} MrcOutput;

///****************************************
/// Input related "global data" structures.
///****************************************

/// This data structure contains all the "global data" values that are considered input by the MRC.
/// The following are DIMM level definitions. All ranks on a DIMM are set to these values.
typedef struct {
  MrcDimmSts  Status;     ///< Indicates whether this DIMM should be used.
  MrcSpdData  Spd;        ///< The SPD data for each DIMM. SPDGeneral field = 0 when absent.
  MrcTiming   Timing;     ///< The DIMMs requested timing overrides.
  UINT8       SpdAddress; ///< The SMBus address for the DIMM's SPD data.
} MrcDimmIn;

/// This data structure contains all the "global data" values that are considered input by the MRC.
/// The following are channel level definitions. All DIMMs on a memory channel are set to these values.
typedef struct {
  MrcChannelSts Status;                                           ///< Indicates whether this channel should be used.
  UINT32        DimmCount;                                        ///< The maximum number of DIMMs on this channel.
  MrcDimmIn     Dimm[MAX_DIMMS_IN_CHANNEL];                       ///< The following are DIMM level definitions.
  UINT8         DqsMapCpu2Dram[MAX_BYTE_IN_LP_CHANNEL];           ///< Mapping from CPU DQS pins to SDRAM DQS pins
  UINT8         DqMapCpu2Dram[MAX_BYTE_IN_LP_CHANNEL][MAX_BITS];  ///< Mapping from CPU DQ pins to SDRAM DQ pins
} MrcChannelIn;

/// This data structure contains all the "global data" values that are considered input by the MRC.
/// The following are memory controller level definitions. All channels on a controller are set to these values.
typedef struct {
  MrcControllerSts  Status;               ///< Indicates whether this controller should be used.
  UINT8             ChannelCount;         ///< Number of valid channels that are requested on the controller.
  MrcChannelIn      Channel[MAX_CHANNEL]; ///< The following are channel level definitions.
} MrcControllerIn;

/// This data structure contains all the "global data" values that are considered input by the MRC.
/// The following are system level definitions. All memory controllers in the system are set to these values.
typedef struct {
  // Start of synchronization to the SA MEMORY_CONFIGURATION structure.
  // Alignment of this block must be maintained and field offsets must match.
  UINT8   Header[28];             ///< Offset 0-27 Config Block Header
  UINT16  Size;                   ///< Offset 28 The size of this structure, in bytes. Must be the first entry in this structure.
  UINT8   HobBufferSize;          ///< Offset 30 Size of HOB buffer for MRC

  UINT8  MemoryProfile;           ///< Offset 31 SPD XMP profile selection - for XMP supported DIMM: <b>0=Default DIMM profile</b>, 1=Customized profile, 2=XMP profile 1, 3=XMP profile 2.

  // The following parameters are used only when SpdProfileSelected is UserDefined (CUSTOM PROFILE)
  UINT16  tCL;                    ///< Offset 32 User defined Memory Timing tCL value,   valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, 31=Maximum.
  UINT16  tRCDtRP;                ///< Offset 34 User defined Memory Timing tRCD value (same as tRP), valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, 63=Maximum
  UINT16  tRAS;                   ///< Offset 36 User defined Memory Timing tRAS value,  valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, 64=Maximum.
  UINT16  tWR;                    ///< Offset 38 User defined Memory Timing tWR value,   valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, legal values: 5, 6, 7, 8, 10, 12, 14, 16, 18, 20, 24.
  UINT16  tRFC;                   ///< Offset 40 User defined Memory Timing tRFC value,  valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, 1023=Maximum.
  UINT16  tRRD;                   ///< Offset 42 User defined Memory Timing tRRD value,  valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, 15=Maximum.
  UINT16  tWTR;                   ///< Offset 44 User defined Memory Timing tWTR value,  valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, 28=Maximum.
  UINT16  tRTP;                   ///< Offset 46 User defined Memory Timing tRTP value,  valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, 15=Maximum. DDR4 legal values: 5, 6, 7, 8, 9, 10, 12
  UINT16  tFAW;                   ///< Offset 48 User defined Memory Timing tFAW value,  valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, 63=Maximum.
  UINT16  tCWL;                   ///< Offset 50 User defined Memory Timing tCWL value,  valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, 20=Maximum.
  UINT16  tREFI;                  ///< Offset 52 User defined Memory Timing tREFI value, valid when SpdProfileSelected is CUSTOM_PROFILE: <b>0=AUTO</b>, 65535=Maximum.
  UINT16  PciIndex;               ///< Offset 54 Pci index register address: <b>0xCF8=Default</b>
  UINT16  PciData;                ///< Offset 56 Pci data register address: <b>0xCFC=Default</b>
  UINT16  VddVoltage;             ///< Offset 58 DRAM voltage (Vdd) in millivolts: <b>0=Platform Default (no override)</b>, 1200=1.2V, 1350=1.35V etc.
  UINT16  Idd3n;                  ///< Offset 60 EPG Active standby current (Idd3N) in milliamps from DIMM datasheet.
  UINT16  Idd3p;                  ///< Offset 62 EPG Active power-down current (Idd3P) in milliamps from DIMM datasheet.

  UINT32  EccSupport:1;              ///< Offset 64 Bit 0  - DIMM Ecc Support option - for Desktop only: 0=Disable, <b>1=Enable</b>
  UINT32  MrcSafeConfig:1;           ///<           Bit 1  - MRC Safe Mode: <b>0=Disable</b>, 1=Enable
  UINT32  RemapEnable:1;             ///<           Bit 2  - This option is used to control whether to enable/disable memory remap above 4GB: 0=Disable, <b>1=Enable</b>.
  UINT32  ScramblerSupport:1;        ///<           Bit 3  - Memory scrambler support: 0=Disable, <b>1=Enable</b>
  UINT32  Vc1ReadMeter:1;            ///<           Bit 4  - VC1 Read Metering Enable: 0=Disable, <b>1=Enable</b>
  UINT32  ForceSingleSubchannel:1;   ///<           Bit 5  - TRUE means use SubChannel0 only (for LPDDR4): <b>0=Disable</b>, 1=Enable
  UINT32  SimicsFlag:1;              ///<           Bit 6  - Option to Enable SIMICS: 0=Disable, <b>1=Enable</b>
  UINT32  Ddr4DdpSharedClock:1;      ///<           Bit 7  - Select if CLK0 is shared between Rank0 and Rank1 in DDR4 DDP package. <b>0=Not shared</b>, 1=Shared
  UINT32  SharedZqPin:1;             ///<           Bit 8  - Select if the ZQ resistor is shared between Ranks in DDR4/LPDDR4 DRAM Packages <b>0=Not Shared</b>, 1=Shared
  UINT32  LpDqsOscEn:1;              ///<           Bit 9  - LPDDR Write DQ/DQS Retraining: 0=Disable, <b>1=Enable</b>
  UINT32  RmtPerTask:1;              ///<           Bit 10 - Rank Margin Tool Per Task. <b>0 = Disabled</b>, 1 = Enabled
  UINT32  TrainTrace:1;              ///<           Bit 11 - Trained state tracing debug. <b>0 = Disabled</b>, 1 = Enabled
  UINT32  SafeMode:1;                ///<           Bit 12 - Define if safe mode is enabled for MC/IO
  UINT32  MsHashEnable:1;            ///<           Bit 13 - Controller Hash Enable: 0=Disable, <b>1=Enable</b>
  UINT32  DisPgCloseIdleTimeout:1;   ///<           Bit 14 - Disable Page Close Idle Timeout: 0=Enable, <b>1=Disable</b>
  UINT32  RsvdO64B15t31:17;          ///<           Bits 15:31 reserved
  /**
   Disables a DIMM slot in the channel even if a DIMM is present\n
   Array index represents the channel number (0 = channel 0, 1 = channel 1)\n
     <b>0x0 = DIMM 0 and DIMM 1 enabled</b>\n
     0x1 = DIMM 0 disabled, DIMM 1 enabled\n
     0x2 = DIMM 0 enabled, DIMM 1 disabled\n
     0x3 = DIMM 0 and DIMM 1 disabled (will disable the whole channel)\n
  **/
  UINT8   DisableDimmChannel[MAX_CONTROLLER][MAX_CHANNEL]; ///< Offset 68-75
  UINT8   Ratio;                  ///< Offset 76 DDR Frequency ratio, to multiply by 133 or 100 MHz depending on RefClk. <b>0 = Auto</b>
  UINT8   ProbelessTrace;         ///< Offset 77 Probeless Trace: <b>0=Disabled</b>, <b>1=Enabled</b>
  /**
    Channel Hash Enable.\n
    NOTE: BIT7 will interleave the channels at a 2 cache-line granularity, BIT8 at 4 and BIT9 at 8\n
    0=BIT6, <B>1=BIT7</B>, 2=BIT8, 3=BIT9
  **/
  UINT8   ChHashInterleaveBit;    ///< Offset 78 Option to select interleave Address bit. Valid values are 0 - 3 for BITS 6 - 9 (Valid values for BDW are 0-7 for BITS 6 - 13)
  UINT8   SmramMask;              ///< Offset 79 Reserved memory ranges for SMRAM
  UINT32  BClkFrequency;          ///< Offset 80 Base reference clock value, in Hertz: <b>100000000 = 100Hz</b>, 125000000=125Hz, 167000000=167Hz, 250000000=250Hz
  // Training Algorithms
  TrainingStepsEn  TrainingEnables;   ///< Offset 84 Options to Enable individual training steps
  TrainingStepsEn2 TrainingEnables2;  ///< Offset 88 Options to Enable individual training steps

  UINT32  MrcTimeMeasure:1;         ///< Offset 92 Bit 0  - Enables serial debug level to display the MRC execution times only: <b>0=Disable</b>, 1=Enable
  UINT32  MrcFastBoot:1;            ///<           Bit 1  - Enables the MRC fast boot path for faster cold boot execution: 0=Disable, <b>1=Enable</b>
  UINT32  DqPinsInterleaved:1;      ///<           Bit 2  - Interleaving mode of DQ/DQS pins which depends on board routing: <b>0=Disable</b>, 1=Enable
  UINT32  RankInterleave:1;         ///<           Bit 3  - Rank Interleave Mode: 0=Disable, <b>1=Enable</b>
  UINT32  EnhancedInterleave:1;     ///<           Bit 4  - Enhanced Interleave Mode: 0=Disable, <b>1=Enable</b>
  UINT32  WeaklockEn:1;             ///<           Bit 5  - Weak Lock Enable: 0=Disable, <b>1=Enable</b>
  UINT32  ChHashEnable:1;           ///<           Bit 6  - Channel Hash Enable: 0=Disable, <b>1=Enable</b>
  UINT32  EnablePwrDn:1;            ///<           Bit 7  - Enable Power Down control for DDR: 0=PCODE control, <b>1=BIOS control</b>
  UINT32  EnablePwrDnLpddr:1;       ///<           Bit 8  - Enable Power Down for LPDDR: 0=PCODE control, <b>1=BIOS control</b>
  UINT32  SrefCfgEna:1;             ///<           Bit 9  - Enable Self Refresh: 0=Disable, <b>1=Enable</b>
  UINT32  ThrtCkeMinDefeatLpddr:1;  ///<           Bit 10 - Throttler CKE min defeature for LPDDR: 0=Disable, <b>1=Enable</b>
  UINT32  ThrtCkeMinDefeat:1;       ///<           Bit 11 - Throttler CKE min defeature: <b>0=Disable</b>, 1=Enable
  UINT32  AutoSelfRefreshSupport:1; ///<           Bit 12 - FALSE = No auto self refresh support, <b>TRUE = auto self refresh support</b>
  UINT32  ExtTemperatureSupport:1;  ///<           Bit 13 - FALSE = No extended temperature support, <b>TRUE = extended temperature support</b>
  UINT32  MobilePlatform:1;         ///<           Bit 14 - Memory controller device id indicates: <b>TRUE if mobile</b>, FALSE if not. Note: This will be auto-detected and updated.
  UINT32  Force1Dpc:1;              ///<           Bit 15 - TRUE means force one DIMM per channel, <b>FALSE means no limit</b>
  UINT32  ForceSingleRank:1;        ///<           Bit 16 - TRUE means use Rank0 only (in each DIMM): <b>0=Disable</b>, 1=Enable
  UINT32  VttTermination:1;         ///<           Bit 17 - Vtt Termination for Data ODT: <b>0=Disable</b>, 1=Enable
  UINT32  VttCompForVsshi:1;        ///<           Bit 18 - Enable/Disable Vtt Comparator For Vsshi: <b>0=Disable</b>, 1=Enable
  UINT32  ExitOnFailure:1;          ///<           Bit 19 - MRC option for exit on failure or continue on failure: 0=Disable, <b>1=Enable</b>
  UINT32  RsvdO92B27t31:12;         ///<           Bit 20-31: Rsvd
  UINT32  VddSettleWaitTime;      ///< Offset 96 Amount of time in microseconds to wait for Vdd to settle on top of 200us required by JEDEC spec: <b>Default=0</b>
  UINT16  SrefCfgIdleTmr;         ///< Offset 100 Self Refresh idle timer: <b>512=Minimal</b>, 65535=Maximum
  UINT16  ChHashMask;             ///< Offset 102 Channel Hash Mask: 0x0001=BIT6 set(Minimal), 0x3FFF=BIT[19:6] set(Maximum), <b>0x30CE= BIT[19:18, 13:12 ,9:7] set</b>
  UINT16  DdrFreqLimit;           ///< Offset 104 Memory Frequency setting: 3=1067, 5=1333, 7=1600, 9=1867, 11=2133, 13=2400, <b>15=2667</b>, 17=2933, 19=3200, 21=3467, 23=3600, 25=3733, 27=4000, 29=4200, 31=4267, 33=4400, 35=4600, 37=4800, 39=5000, 41=5200, 43=5400, 45=5600, 47=6400.
  UINT8   MaxRttWr;               ///< Offset 106 Maximum DIMM RTT_WR to use in power training: <b>0=ODT Off</b>, 1 = 120 ohms
  UINT8   ThrtCkeMinTmr;          ///< Offset 107 Throttler CKE min timer: 0=Minimal, 0xFF=Maximum, <b>0x30=Default</b>
  UINT8   ThrtCkeMinTmrLpddr;     ///< Offset 108 Throttler CKE min timer for LPDDR: 0=Minimal, 0xFF=Maximum, <b>0x40=Default</b>
  BOOLEAN PerBankRefresh;         ///< Offset 109 Enables and Disables the per bank refresh.  This only impacts memory technologies that support PBR: LPDDR3, LPDDR4.  FALSE=Disabled, <b>TRUE=Enabled</b>
  UINT8   SaGv;                   ///< Offset 110 SA GV: <b>0=Disabled</b>, 1=Point1, 2=Point2, 3=Point3, 4=Point4, 5=Enabled
  UINT8   NModeSupport;           ///< Offset 111 Memory N Mode Support - Enable user to select Auto, 1N or 2N: <b>0=AUTO</b>, 1=1N, 2=2N.
  UINT8   RefClk;                 ///< Offset 112 Selects the DDR base reference clock. 0x01 = 100MHz, <b>0x00 = 133MHz</b>
  UINT8   EnCmdRate;              ///< Offset 113 CMD Rate Enable: 0=Disable, 5=2 CMDs, <b>7=3 CMDs</b>, 9=4 CMDs, 11=5 CMDs, 13=6 CMDs, 15=7 CMDs
  UINT8   Refresh2X;              ///< Offset 114 Refresh 2x: <b>0=Disable</b>, 1=Enable for WARM or HOT, 2=Enable for HOT only
  UINT8   EpgEnable;              ///< Offset 115 Enable Energy Performance Gain.
  UINT8   UserThresholdEnable;    ///< Offset 116 Flag to manually select the DIMM CLTM Thermal Threshold, 0=Disable,  1=Enable, <b>0=Default</b>
  UINT8   UserBudgetEnable;       ///< Offset 117 Flag to manually select the Budget Registers for CLTM Memory Dimms , 0=Disable,  1=Enable, <b>0=Default</b>
  UINT8   RetrainOnFastFail;      ///< Offset 118 Restart MRC in Cold mode if SW MemTest fails during Fast flow. 0 = Disabled, <b>1 = Enabled</b>
  UINT8   PowerDownMode;          ///< Offset 119 CKE Power Down Mode: <b>0xFF=AUTO</b>, 0=No Power Down, 1= APD mode, 6=PPD-DLL Off mode
  UINT8   PwdwnIdleCounter;       ///< Offset 120 CKE Power Down Mode Idle Counter: 0=Minimal, 255=Maximum, <b>0x80=0x80 DCLK</b>
  UINT8   CmdRanksTerminated;     ///< Offset 121 LPDDR: Bitmask of ranks that have CA bus terminated. <b>0x01=Default, Rank0 is terminating and Rank1 is non-terminating</b>
  UINT16  MsHashMask;             ///< Offset 122 Controller Hash Mask: 0x0001=BIT6 set(Minimal), 0x3FFF=BIT[19:6] set(Maximum), <b>0x30CE= BIT[19:18, 13:12 ,9:7] set</b>
  UINT32  Lp5CccConfig;           ///< Offset 124 BitMask where bits [3:0] are controller 0 Channel [3:0] and [7:4] are Controller 1 Channel [3:0].  0 selects Ascending mapping and 1 selects Descending mapping.
  UINT8   RMTLoopCount;           ///< Offset 128 Indicates the Loop Count to be used for Rank Margin Tool Testing: 1=Minimal, 32=Maximum, 0=AUTO, <b>0=Default</b>
  UINT8   MsHashInterleaveBit;    ///< Offset 129 Option to select interleave Address bit. Valid values are 0 - 3 for BITS 6 - 9
  UINT8   GearRatio;              ///< Offset 130 This input control's the current gear expressed as an integer when SAGV is disabled: <b>0=Default</b>, 1, 2.
  UINT8   RsvdO131;               ///< Offset 131
  UINT32  BclkRfiFreq[MAX_SAGV_POINTS]; ///< Offset 132 Bclk RFI Frequency for each SAGV point in Hz units. 98000000Hz = 98MHz <b>0 - No RFI Tuning</b>. Range is 98Mhz-100Mhz.
  UINT16  SaGvFreq[MAX_SAGV_POINTS];    ///< Offset 148 Frequency per SAGV point.  0 is Auto, otherwise holds the frequency value expressed as an integer: <b>0=Default</b>, 1067, 1333, 1600, 1800, 1867, etc.
  UINT8   SaGvGear[MAX_SAGV_POINTS];    ///< Offset 156 Gear ratio per SAGV point.  0 is Auto, otherwise holds the Gear ratio expressed as an integer: <b>0=Default</b>, 1, 2.
  // End of synchronization to the SA MEMORY_CONFIGURATION structure.
  UINT64          TscTimeBase;                 ///< CPU TSC timebase in [us] : (BCLK * Ratio / 1000 / 1000)
  MrcFrequency    FreqMax;                     ///< The requested maximum valid frequency.
  MrcBoardType    BoardType;                   ///< define the board type (CRBMB,CRBDT,User1,User2). the OEM can add more boards.
  MrcCpuStepping  CpuStepping;                 ///< define the CPU stepping.
  UINT8           MemBootMode;                 ///< Boot mode in 1LM/2LM/Provisioning     // 2LM
  UINT32          FarMemorySize;               ///< Far Memory size in units of MB        // 2LM
  UINT32          PMemSize;                    ///< Persistent Memory Size in units of MB // 2LM
  MrcCpuModel     CpuModel;                    ///< define the CPU model.
  MrcCpuFamily    CpuFamily;                   ///< define the CPU Family
  MrcGfxDataSize  GraphicsStolenSize;          ///< Graphics Data Stolen Memory size in MB
  MrcGfxGttSize   GraphicsGttSize;             ///< GTT graphics stolen memory size in MB
  UINT32          GtPsmiRegionSize;            ///< PSMI region size in MB
  MrcIteration    Iteration;                   ///< Number of iterations thru the MRC core call table.
  MRC_BOOT_MODE   BootMode;                    ///< The requested memory controller boot mode.
  BOOLEAN         TxtFlag;                     ///< Trusted eXecution Technology flag.
  BOOLEAN         GfxIsVersatileAcceleration;  ///< iGFX engines are in Versatile Acceleration
  BOOLEAN         DDR4MAP;                     ///< DDR4 PDA Mapping training control.
  POINTER_STRUCT  SaMemCfgAddress;             ///< Starting address of the input parameters to CRC.
  UINT32          SaMemCfgSize;                ///< The size of the input parameters to CRC.
  UINT32          PciEBaseAddress;             ///< define the PciE base address.
  UINT32          MchBarBaseAddress;           ///< define the MCH bar base address.
  UINT32          SmbusBaseAddress;            ///< This field defines the smbus base address.
  UINT32          MeStolenSize;                ///< Define the size that the ME need in MB.
  UINT32          ImrAlignment;                ///< Define the largest size of IMR that the ME need in MB.
  UINT32          MmioSize;                    ///< define the MMIO size in MB.
  UINT32          TsegSize;                    ///< TSEG size that require by the system in MB.
  UINT32          IedSize;                     ///< IED size that require by the system in MB.
  UINT32          DprSize;                     ///< DPR size required by system in MB.
  UINT32          PrmrrSize;                   ///< Prmrr size required by the system in MB.
  UINT32          TmeEnable;                   ///< TME policy enable <b>0: Disable </b>; 1: Enable
  UINT64          TmeExcludeBase;              ///< Base physical address to be excluded for TME encryption.
  UINT64          TmeExcludeSize;              ///< Size of range to be excluded from TME encryption.
  POINTER_STRUCT  SerialBuffer;                ///< Pointer to the start of the serial buffer.
  UINT32          SerialBufferSize;            ///< The size of the serial buffer, in bytes.
  UINT32          DebugStream;                 ///< The debug port pointer.
  INT32           DebugLevel;                  ///< Indicates the level of debug messaging.
  UINT16          VccIomV;                     ///< VccIO logic voltage in mV.
  MrcControllerIn Controller[MAX_CONTROLLER];  ///< The following are controller level definitions.
#ifdef SSA_FLAG
  UINT32          SsaCallbackPpi;
#endif // SSA_FLAG
  POINTER_STRUCT    HeapBase;                     ///< Starting address of the heap space.
  UINT32            HeapSize;                     ///< Size of the heap space, in bytes.
  POINTER_STRUCT    MrcStackTop;                  ///< Top of the stack at the beginning of MRC, for stack usage calculations.
  BOOLEAN           RmtBdatEnable;                ///< Option to enable output of training results into BDAT.
  UINT8             DramDqOdt;                    ///< Controls the usage of the DRAM DQ ODT. 0 - Auto, 1 - Enable, 2 - Disable. See MRC_EN_DIS_AUTO_TYPE.
  BOOLEAN           EnableVrefPwrDn;              ///< Setting this limits VrefGen to be off only during CKEPowerDown
  BOOLEAN           TxEqDis;                      ///< Disable TX Equalization
  UINT32            CpuidModel;                   ///< Unique CPU identifier.
  UINT8             CpuidStepping;                ///< Revision of the CPU.
  UINT32            SiPreMemPolicyPpi;
  TrainingModeType  PowerTrainingMode;              ///< 0 - Power Training. 1 - Margin Training.
  UINT16            RcompResistor;                  ///< Reference RCOMP resistor on motherboard ~ 100 ohms
  UINT16            RcompTarget[MAX_RCOMP_TARGETS]; ///< RCOMP target values for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  BOOLEAN           SeparateCkeDelayDdr4;           ///< Boolean switch to control sharing of CKE delays for DDR4 Ranks 0 & 1. @todo: Comment improvement to relate to PDG CKE design.
  MRC_TE_TYPE       TestEngine;                     ///< Defines which hardware test engine is used by this product.
  UINT8             RxMode;                         ///< Override RxMode setting of DataControl0 register
  BOOLEAN           LpFreqSwitch;                   ///< Boolean variable to enable or disable frequency switching for supported LPDDR devices.
  BOOLEAN           LowSupplyEnData;                ///< Used to enable Low Supply for LPDDR4 Data.
  BOOLEAN           LowSupplyEnCcc;                 ///< Used to enable Low Supply for LPDDR4 Clock/Command/Control.
  BOOLEAN           RdTPbdDis;                      ///< Controls if Read Timing Per-Bit Deskew is disabled.
  BOOLEAN           WrTPbdDis;                      ///< Controls if Write Timing Per-Bit Deskew is disabled.
  BOOLEAN           Mars;                           ///< Controls MARS feature
  UINT8             Ddr4OneDpc;                     ///< DDR4 1DPC performance feature: 0 - Disabled; 1 - Enabled on DIMM0 only, 2 - Enabled on DIMM1 only; 3 - Enabled on both DIMMs. (bit [0] - DIMM0, bit [1] - DIMM1)
  BOOLEAN           DqBitDccRerunInWrTPbd;          ///< Controls if DQ Bit DCC is re-run during Write Timing Per-Bit Deskew.  Only applicable if Write Timing Per-Bit Deskew is enabled.
  UINT8             ScompBypass[4];
  UINT32            CleanMemory:1;                  ///< TRUE to request a memory clean
  UINT32            RsvdBits1:31;
  BOOLEAN           DtHalo;                         ///< Identifies that the current CPU SKU is Desktop / Halo
  BOOLEAN           UlxUlt;                         ///< Identifies that the current CPU SKU is ULX / ULT
  BOOLEAN           A0;                             ///< Identifies that the current CPU stepping is A0
  BOOLEAN           B0;                             ///< Identifies that the current CPU stepping is B0
  BOOLEAN           NonTargetOdtEn;                 ///< Enables Non-Target ODT for LPDDR5
  /**
   Sets the serial debug message level\n
     0x00 = Disabled\n
     0x01 = Errors only\n
     0x02 = Errors and Warnings\n
     <b>0x03 = Errors, Warnings, and Info</b>\n
     0x04 = Errors, Warnings, Info, and Events\n
     0x05 = Displays Memory Init Execution Time Summary only\n
  **/
  UINT8 SerialDebugLevel;
  union {
    MRC_FUNCTION    *Func;  ///< External to MRC function pointers
    UINT64          Data;
  } Call;
} MrcInput;

typedef struct {
  UINT32        Size;   ///< The size of this structure, in bytes. Must be the first entry in this structure.
  MrcSaveHeader Header; ///< The header portion of the MRC saved data.
  MrcSaveData   Data;   ///< The data portion of the MRC saved data.
} MrcSave;

typedef struct {
  // Global variables that will be copied to the HOB follow.
  UINT8        MrcDataString[4]; ///< Beginning of global data marker, starts with "MRC". Must be the first entry in this structure.
  UINT32       MrcDataSize;      ///< The size of the MRC global data area, in bytes. Must be the second entry in this structure.
  MrcSave      Save;             ///< System specific save variables.
  MrcInput     Inputs;           ///< System specific input variables.
  MrcOutput    Outputs;          ///< System specific output variables.

  // Global variables that will remain internal to the MRC library follow.
  union {
    void   *Internal; ///< System specific output variables that remain internal to the library.
    UINT64 Data;
  } IntOutputs;
} MrcParameters;

/**
  This function returns the recommended MRC boot mode.

  @param[in]  MrcData - include all the MRC general data.

  @retval bmWarm if we are in self refresh and the DISB bit is set, otherwise returns bmCold.
**/
extern
MRC_BOOT_MODE
MrcGetBootMode (
  IN MrcParameters * const MrcData
  );

/**
  This function return the MRC version.

  @param[in]  MrcData - include all the MRC general data.
  @param[out] Version - Location to store the MRC version.
**/
extern
void
MrcVersionGet (
     IN  const MrcParameters *const MrcData,
     OUT MrcVersion *const Version
  );

/**
  Print the MRC version to the MRC output device.

  @param[in] *MrcData - Pointer to the MRC Debug structure.
  @param[in] Version  - The MRC version.
**/
extern
void
MrcVersionPrint (
  IN MrcParameters     *MrcData,
  IN const MrcVersion  *Version
  );

/**
  Calculates a CRC-32 of the specified data buffer.

  @param[in] Data     - Pointer to the data buffer.
  @param[in] DataSize - Size of the data buffer, in bytes.

  @retval The CRC-32 value.
**/
extern
UINT32
MrcCalculateCrc32 (
  IN     const UINT8  *const Data,
  IN     const UINT32 DataSize
  );

/**
  This function resets the DISB bit in General PM Configuration 2 B:D:F 0,31,0 offset 0xA2.

  @param[in]  MrcData - include all the MRC general data.
**/
extern
void
MrcResetDISB (
  IN MrcParameters * const MrcData
  );

/**
  Initializes the memory controller and DIMMs.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Select  - The post code of the call table entry to execute.

  @retval mrcSuccess if the initialization succeeded, otherwise an error status indicating the failure.
**/
extern
MrcStatus
MrcStartMemoryConfiguration (
  IN OUT MrcParameters *const MrcData,
  IN     MrcPostCode          Select
  );

/**
  Retrieve the current memory frequency and clock from the memory controller.

  @param[in]      MrcData      - Include all MRC global data.
  @param[in, out] MemoryClock  - The current memory clock.
  @param[in, out] Ratio        - The current memory ratio setting.
  @param[in, out] RefClk       - The current memory reference clock.

  @retval: The current memory frequency.
**/
MrcFrequency
MrcGetCurrentMemoryFrequency (
  MrcParameters * const   MrcData,
  UINT32 * const          MemoryClock,
  MrcClockRatio * const   Ratio,
  MrcRefClkSelect * const RefClk
  );

/**
  This function get the current value of the sticky scratchpad register.

  @param[in] MrcData - include all the MRC data.

  @retval The current value of the sticky scratchpad register
**/
extern
UINT64
MrcWmRegGet (
  IN     MrcParameters *const MrcData
  );


/**
  Gets pointers to functions inside of core.

  @param[in]  MrcData                     - All the MRC global data.
  @param[out] CallChannelExist            - Pointer to the function MrcChannelExist
  @param[out] CallPrintf                  - Pointer to the function MrcPrintf
  @param[out] CallChangeMargin            - Pointer to the function ChangeMargin
  @param[out] CallSignExtend              - Pointer to the function MrcSignExtend
  @param[out] CallShiftPIforCmdTraining   - Pointer to the function ShiftPIforCmdTraining
  @param[out] CallMrcUpdateVref           - Pointer to the function MrcUpdateVref

  @retval Returns mrcSuccess if the function succeeds.
**/
extern
MrcStatus
MrcGetCoreFunction (
  IN const MrcParameters *const MrcData,
  OUT UINTN              *CallChannelExist,
  OUT UINTN              *CallPrintf,
  OUT UINTN              *CallChangeMargin,
  OUT UINTN              *CallSignExtend,
  OUT UINTN              *CallShiftPIforCmdTraining,
  OUT UINTN              *CallMrcUpdateVref
  );

#ifdef UP_SERVER_FLAG
#define WarmThreshold_1X_MAX_TEMP       83
#define WarmThreshold_1X_MAX_TEMP_DECIMAL        0      //Resolution 0.5 format 7.1
#define WarmThreshold_2X_MAX_TEMP       85
#define WarmThreshold_2X_MAX_TEMP_DECIMAL       0      //Resolution 0.5 format 7.1
#define HotThreshold_1X_MAX_TEMP        83
#define HotThreshold_1X_MAX_TEMP_DECIMAL       0      //Resolution 0.5 format 7.1
#define HotThreshold_2X_MAX_TEMP        92
#define HotThreshold_2X_MAX_TEMP_DECIMAL       0      //Resolution 0.5 format 7.1
#define CRITICAL_TEMP                    105
#define THOT_2X_MAX_TEMP                 93
#define THOT_1X_MAX_TEMP                 83
#define DISABLE_REFRESH2X                0
//Power Weight Table Defines
#define WARM_BUDGET_POSITION             6
// CLTM Process Status Defines
#define PROCESS_NOT_INITIALIZED          0x0000
#define PROCESS_FAILED                   0xFFFF
#define CONTROLLER_NOT_LOADED            0xFF
#define CLTM_DISABLE                     0
//TSE2002 Thermal Sensor Defines
#define MTS_CAPABILITIES                 0
#define MTS_CFG                          1
#define MTS_THIGH                        2
#define MTS_TLOW                         3
#define MTS_TCRIT                        4
#define TEMPERATURE_REGISTER             5
#define MTS_MFGID                        6
#define MTS_DID                          7
#define THERMAL_MODULE_MASK              0x30
#define CLTM_THERMAL_LOOKUPTABLE_SIZE    40
//TSOD definitions
#define HYST_DISABLE                      0

typedef union {
  struct {
    UINT16 EventMode                               :  1;  // Bits 0:0
    UINT16 EventPolarity                           :  1;  // Bits 1:1
    UINT16 CriticalEventOnly                       :  1;  // Bits 2:2
    UINT16 EventOutputControl                      :  1;  // Bits 3:3
    UINT16 EventStatus                             :  1;  // Bits 4:4
    UINT16 ClearEvent                              :  1;  // Bits 5:5
    UINT16 AlarmWindowLock                         :  1;  // Bits 6:6
    UINT16 CriticalLock                            :  1;  // Bits 7:7
    UINT16 ShutdownMode                            :  1;  // Bits 8:8
    UINT16 HystEnable                              :  1;  // Bits 10:9
    UINT16 Reserved                                :  4;  // Bits 15:11
  } Bits;
  UINT16 Data;
} TSOD_CONF_REGISTER_STRUCT;

typedef union {
  struct {
    UINT32 Dimm0Thigh                          :  16;  // Bits 15:0
    UINT32 Dimm1Thigh                          :  16;  // Bits 31:16
    } Bits;
  UINT16 Data16[2];
  UINT32 Data;
} TSOD_THIGH_STRUCT;

typedef union {
  struct {
    UINT32 Dimm0Tcrit                         :  16;  // Bits 15:0
    UINT32 Dimm1Tcrit                         :  16;  // Bits 31:16
    } Bits;
  UINT16  Data16[2];
  UINT32 Data;
} TSOD_TCRIT_STRUCT;
#endif

#pragma pack (pop)
#endif

