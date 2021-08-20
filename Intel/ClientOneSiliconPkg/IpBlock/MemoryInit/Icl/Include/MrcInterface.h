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
  mrMR11 = 11,
  mrMR12 = 12,
  mrMR13 = 13,
  mrMR14 = 14,
  mrMR22 = 22,
  mrMR23 = 23
} MrcModeRegister;

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
  mrIndexMR11,
  mrIndexMR12,
  mrIndexMR13,
  mrIndexMR14,
  mrIndexMR22,
  mrIndexMR23,
  mrIndexMax
} MrcModeRegisterIndex;

#define MAX_CPU_SOCKETS          (1)       ///< The maximum number of CPUs per system.
#define MAX_CONTROLLERS          (1)       ///< The maximum number of memory controllers per CPU socket.
#define MAX_CHANNEL              (2)       ///< The maximum number of channels per memory controller.
#define MAX_SUB_CHANNEL          (2)       ///< The maximum number of subchannels per channel.
#define MAX_PHY_CHANNEL          (MAX_SUB_CHANNEL * MAX_CHANNEL)  ///< The maximum number of channels treating each sub channels as an independent channel, per controller.
#define MAX_DIMMS_IN_CHANNEL     (2)       ///< The maximum number of DIMMs per channel.
#define MAX_RANK_IN_DIMM         (2)       ///< The maximum number of ranks per DIMM.
#define MAX_RANK_IN_CHANNEL      (MAX_DIMMS_IN_CHANNEL * MAX_RANK_IN_DIMM) ///< The maximum number of ranks per channel.
#define MAX_BANKS                (32)      ///< Max Number of Banks supported in CPGC.  This is a combination of BankGroup and Bank.
#define MAX_DDR4_x8_BANKS        (16)      ///< Max Number of Banks with x8 devices in DDR4.  This is a combination of BankGroup and Bank.
#define MAX_DDR4_x16_BANKS       (8)       ///< Max Number of Banks with x16 devices in DDR4.  This is a combination of BankGroup and Bank.
#define MAX_SDRAM_IN_DIMM        (9)       ///< The maximum number of SDRAMs per DIMM when ECC is enabled.
#define MAX_MR_IN_DIMM           (mrIndexMax)  ///< Maximum number of mode registers in a DIMM.
#define MAX_DEVICES_IN_DDR4      (8)       ///< The maximum number of SDRAMs per DDR4 DIMM.
#define MAX_BITS                 (8)       ///< BITS per byte.
#define MAX_STROBE               (18)      ///< Number of strobe groups.
#define MAX_DQ                   (72)      ///< Number of Dq bits used by the rank.
#define MAX_DQ_IN_SUB_CHANNEL    (32)      ///< Number of Dq bits within a subchannel.
#define MAX_SDRAM_IN_SUB_CHANNEL (4)
#define CHAR_BITS                (8)       ///< Number of bits in a char.
#define PSMI_SIZE_MB             (64)      ///< Define the max size of PSMI needed in MB
#define BCLK_DEFAULT             (100 * 1000 * 1000) ///< BCLK default value, in Hertz.
#define MAX_COMMAND_GROUPS       (5)       ///< CMDA (CmdPi0Code & CmdPi1Code), CMDB (CmdPi0Code & CmdPi1Code), CKECMD (CmdPi2Code)
#define MAX_DCC_CLOCK_PI         (128)     ///< CLK PI Range (0 - 127) Only used for DCC Look Up Table
#define MAX_DCC_TX_DQS_DQ_PI     (128)     ///< Tx Dqs/Dq PI Range (0 - 127) Only used for DCC Look Up Table
#define MAX_EDGES                (2)  ///< Maximum number of edges.
#define MAX_DYNAMIC_FREQ         (3)  ///< Maximum number of dynamic frequencies supported.
#define MAX_IBECC_REGIONS       (8)       ///< Maximum number of protection regions handled by IBECC

#define MRC_DEBUG_LEVEL_CMOS_ADDR     (0x4C) ///< Debug level override (32-bit value)
#define MRC_RESET_COUNT_CMOS_ADDR     (0x70) ///< 1-byte counter for reset cycling test. 0 = reset cycling disabled.

#define MRC_DEBUG_SIGN0_CMOS_ADDR     (0xD4) ///< Signature0: Enable MRC CMOS DEBUG FLOW with the special signature (sign = addr)
#define MRC_DEBUG_SIGN1_CMOS_ADDR     (0xD5) ///< Signature1: Enable MRC CMOS DEBUG FLOW with the special signature (sign = addr)
#define MRC_DEBUG_SIGN2_CMOS_ADDR     (0xD6) ///< Signature2: Enable MRC CMOS DEBUG FLOW with the special signature (sign = addr)
#define MRC_DEBUG_SIGN3_CMOS_ADDR     (0xD7) ///< Signature3: Enable MRC CMOS DEBUG FLOW with the special signature (sign = addr)
#define MRC_DEBUG_SAGV_CMOS_ADDR      (0xD8) ///< SA GV: <b>0=Disabled</b>, 1=FixedLow, 2=FixedMid, 3=FixedHigh, 4=Enabled

#define MRC_FREQ_HIGH_CMOS_ADDR       (0xD9) ///< SAGV High Frequency. This controls FreqMax regardless SaGV disabled. If this set to 0, any memory Mid/Low frequency change below will be ignored
                                             ///< [Bit7] Gear: 0=Gear1 1=Gear2
                                             ///< [Bit6:0] FrequencyValue (133.33 Based) 0=Auto 8=1067 10=1333 .. 16=2133 .. 28=3733 .. 32=4267
#define MRC_FREQ_MID_CMOS_ADDR        (0xDA) ///< SAGV Mid Frequency and Gear
                                             ///< [Bit7] Gear: 0=Gear1 1=Gear2
                                             ///< [Bit6:0] FrequencyValue (133.33 Based) 0=Auto 8=1067 10=1333 .. 16=2133 .. 28=3733 .. 32=4267
#define MRC_FREQ_LOW_CMOS_ADDR        (0xDB) ///< SAGV Low Frequency and Gear
                                             ///< [Bit7] Gear: 0=Gear1 1=Gear2
                                             ///< [Bit6:0] FrequencyValue (133.33 Based) 0=Auto 8=1067 10=1333 .. 16=2133 .. 28=3733 .. 32=4267

#define MRC_CHANNEL_DISABLE_CMOS_ADDR (0xDC) ///< [Bit7]   ForceSingleSubchannel - use SubChannel0 only (for LPDDR4): <b>0 = Disabled</b>, 1 = Enabled
                                             ///< [Bit1:0] Memory channel disable: <b>0 = both enabled</b>, 1 = channel 0 disabled, 2 = channel 1 disabled.

#define MRC_DEBUG_CONFIG0_CMOS_ADDR   (0xDD) ///< [Bit0] RmtPerTask: Rank Margin Tool Per Task. <b>0 = Disabled</b>, 1 = Enabled
#define MRC_DEBUG_CONFIG1_CMOS_ADDR   (0xDE) ///< Reserved for future MRC DEBUG Config.
#define MRC_DEBUG_CONFIG2_CMOS_ADDR   (0xDF) ///< Reserved for future MRC DEBUG Config.

#define SUPPORT_DDR4              SUPPORT   ///< SUPPORT means that DDR4 is supported by the MRC.
#define SUPPORT_LPDDR4            SUPPORT   ///< SUPPORT means that LPDDR4 is supported by the MRC.
#define SPD3_MANUF_START       117         ///< The starting point for the SPD manufacturing data.
#define SPD3_MANUF_END         127         ///< The ending point for the SPD manufacturing data.
#if (SUPPORT_DDR4 == SUPPORT)
#define SPD4_MANUF_START       320         ///< The starting point for the SPD manufacturing data.
#define SPD4_MANUF_END         328         ///< The ending point for the SPD manufacturing data.
#endif
#define SPDLP_MANUF_START      320         ///< The starting point for the SPD manufacturing data.
#define SPDLP_MANUF_END        328         ///< The ending point for the SPD manufacturing data.
// SSKPD_PCU_SKPD BIT MASK
#define SSKPD_PCU_SKPD_TRAIN_DONE       0x1
#define SSKPD_PCU_SKPD_MEM_TEST_DONE    0x2

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
  OemFastBootPermitted,       ///<  before fast boot.
  OemRestoreNonTraining,
  OemPrintInputParameters,    ///<  before printing input parameters.
  OemSpdProcessingRun,        ///<  before SPD processing code.
  OemSetOverridePreSpd,       ///<  before set overrides pre SPD.
  OemSetOverride,             ///<  before set overrides.
  OemMcCapability,            ///<  before MC capability.
  OemMcInitRun,               ///<  before mc init code.
  OemMcMemoryMap,             ///<  before memory map.
  OemMcResetRun,              ///<  before jedec reset.
  OemPreTraining,             ///<  before the training.
  OemMcTrainingRun,           ///<  before training code
  OemEarlyCommandTraining,    ///<  before Early Command training
  OemEarlyCmdVoltCentering,   ///<  before Early Command Voltage Centering
  OemSenseAmpTraining,        ///<  before Sense Amp Training
  OemReadMprTraining,         ///<  before Read MPR Training
  OemReceiveEnable,           ///<  before Read Leveling
  OemJedecWriteLeveling,      ///<  before Jedec Write Leveling
  OemWriteLevelingFlyby,      ///<  before Write Leveling FlyBy
  OemWriteDqDqs,              ///<  before Write Timing Centering
  OemWriteVoltage,            ///<  before Write Voltage Centering
  OemSenseAmpCorrection,      ///<  before Sense amp offset correction
  OemReadVoltage,             ///<  before Read Voltage Centering
  OemEarlyWriteDqDqs2D,       ///<  before Early Write Timing Centering 2D
  OemEarlyReadDqDqs2D,        ///<  before Early Read Timing Centering 2D
  OemEarlyReadMprDqDqs2D,     ///<  before Early MPR Read Timing Centering 2D
  OemEarlyRmpr2DPostEct,      ///<  before Early MPR Read Timing Centering 2D after ECT
  OemReadDqDqs,               ///<  before Read Timing Centering
  OemPerBitDeskewCal,         ///<  before Per Bit Deskew Calibration
  OemDdr4Map,                 ///<  before DDR4 PDA Mapping
  OemDimmRonTraining,         ///<  before DIMM Ron Training
  OemDimmODTTraining,         ///<  before DIMM ODT Training
  OemDimmOdtCaTraining,       ///<  before DIMM ODT CA Training
  OemWriteDriveStrengthEq,    ///<  before Write Drive Strength/Equalization 2D Training
  OemWriteDriveUpDn,          ///<  before Write Drive Strength Up/Dn 2D Training
  OemWriteSlewRate,           ///<  before Write Slew Rate Training
  OemReadODTTraining,         ///<  before Read ODT algorithm.
  OemReadEQTraining,          ///<  before Read Equalization Training.
  OemReadAmplifierPower,      ///<  before Read Amplifier Power.
  OemOptimizeComp,            ///<  before Comp Optimization Training.
  OemPowerSavingMeter,        ///<  before PowerSavingMeter step.
  OemWriteDqDqs2D,            ///<  before Write Timing Centering 2D.
  OemReadDqDqs2D,             ///<  before Read Timing Centering 2D.
  OemCmdVoltCentering,        ///<  before Command Voltage Centering.
  OemCmdSlewRate,             ///<  before CMD Slew Rate
  OemCmdSlewRateOffset,       ///<  before CMD Slew Rate Offset
  OemCmdDriveStrengthEq,      ///<  before Command Drive Strength Equalization
  OemWriteVoltCentering2D,    ///<  before Write Voltage Centering 2D.
  OemReadVoltCentering2D,     ///<  before Read Voltage Centering 2D.
  OemLateCommandTraining,     ///<  before Late Command training.
  OemRoundTripLatency,        ///<  before Round Trip Latency Training.
  OemTurnAroundTimes,         ///<  before Turn Around Times.
  OemRcvEnCentering1D,        ///<  before Receive Enable Centering.
  OemSaveMCValues,            ///<  before saving memory controller values.
  OemRmt,                     ///<  before RMT crosser tool.
  OemMemTest,                 ///<  before Memory testing.
  OemRestoreTraining,         ///<  before Restoring Training Values.
  OemJedecResetDdr4Fast,      ///<  before JEDEC reset for DDR4 in Fast flow.
  OemTxTcoCompTraining,       ///<  before TxTCO Comp training.
  OemTxTcoDqsCompTraining,    ///<  before TxTCO DqsP/N/Bypass training.
  OemClkTcoCompTraining,      ///<  before ClkTCO Comp training.
  OemSelfRefreshExit,       ///<  before Self Refresh Exit.
  OemNormalMode,            ///<  before Normal Mode on non-cold boots.
  OemThermalConfig,         ///<  after Normal Mode, set Thermal config values.
  OemTxtAliasCheck,         ///<  before TxT Alias Check Call.
  OemAliasCheck,            ///<  before alias checking on cold boots.
  OemIbecc,                 ///<  ibecc enabling
  OemHwMemInit,
  OemPostTraining,          ///<  after the training.
  OemMrcActivate,           ///<  before MrcActivate call.
  OemSaGvSwitch,            ///<  before SA GV switch
  OemEngPerfGain,           ///<  before Energy Performance Gain.
  OemMrcDone,               ///<  call to MrcOemCheckPoint when MRC was done.
  OemFrequencySet,          ///<  do operation before frequency set.
  OemFrequencySetDone,      ///<  do operation after frequency set.
  OemStartMemoryConfiguration,
  OemBeforeNormalMode,      ///<  call to MrcOemCheckPoint before normal mode is enabled.
  OemAfterNormalMode,       ///<  call to MrcOemCheckPoint after normal mode is enabled.
  OemMrcFillBdat,
  OemRetrainMarginCheck,
  OemDdrPhyInit,            ///< before Phy Init Sequence.
  OemDdrScompInit,          ///< before Scomp Init Sequence.
  OemWriteDqDqsReTraining,
  OemMemorySsInit,          ///< before Initializing Memory SubSystem registers.
  OemMrcSafeMode,           ///< before Safe Mode Updates to MrcInput.
  OemRmtPerBit,
  OemDccInit,               ///< before Initializing Duty Cycle Correction
  OemDccReplica,            ///< before Duty Cycle Correction Replica (Pre SAGV)
  OemDccFinal,              ///< before Finalization of Duty Cycle Correction (Post SAGV)
  OemDqDfeTraining,         ///< before DQ DFE Training
  OemEarlyOverrides,        ///< before Early Overrides
  OemUpdateSaveMCValues,    ///< before Updating memory controller values.
  OemMarginLimitCheck,      ///< before Margin Limit Check
  OemSenseAmpRetraining,    ///< before Sense Amplifier Retraining
  ///
  ///*********************************************************************************
  ///
  OemNumOfCommands          ///<  Should always be last in the list!
} MrcOemStatusCommand;

typedef UINT8 MrcIteration; ///< MRC invocation sequence number, start with 0 and increment by one each time MRC library is called.
#define MRC_ITERATION_MAX ((1 << ((sizeof (MrcIteration) * 8) - 1)) + ((1 << ((sizeof (MrcIteration) * 8) - 1)) - 1))

#define MAX_RCOMP         (3)
#define MAX_RCOMP_TARGETS (5)

/// Thermal Options
typedef struct {
  UINT8  RaplLim2WindX;                                    ///< Power Limit 2 Time Window X value: 0=Minimal, 3=Maximum, <b>1=Default</b>
  UINT8  RaplLim2WindY;                                    ///< Power Limit 2 Time Window Y value: 0=Minimal, 3=Maximum, <b>1=Default</b>
  UINT8  RaplLim1WindX;                                    ///< Power Limit 1 Time Window X value: <b>0=Minimal</b>, 3=Maximum
  UINT8  RaplLim1WindY;                                    ///< Power Limit 1 Time Window Y value: <b>0=Minimal</b>, 31=Maximum
  UINT16 RaplLim2Pwr;                                      ///< Power Limit 2: 0=Minimal, 16383=Maximum, <b>222=Default</b>
  UINT16 RaplLim1Pwr;                                      ///< Power Limit 1: <b>0=Minimal</b>, 16383=Maximum
  UINT8  WarmThreshold[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL]; ///< Warm Threshold (Channel 0, Dimm 0): 0=Minimal, <b>255=Maximum</b>
  UINT8  HotThreshold[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];  ///< Hot Threshold (Channel 0, Dimm 0): 0=Minimal, <b>255=Maximum</b>
  UINT8  WarmBudget[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];    ///< Warm Budget (Channel 0, Dimm 0): 0=Minimal, <b>255=Maximum</b>
  UINT8  HotBudget[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];     ///< Hot Budget (Channel 0, Dimm 0): 0=Minimal, <b>255=Maximum</b>
  UINT8  IdleEnergy[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT8  PdEnergy[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT8  ActEnergy[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT8  RdEnergy[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT8  WrEnergy[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
} ThermalMngmtEn;


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
  UINT32 CMDSR        : 1;   ///< BIT0  - CMD Slew Rate Training
  UINT32 CMDDSEQ      : 1;   ///< BIT1  - CMD Drive Strength and Tx Equalization
  UINT32 CMDNORM      : 1;   ///< BIT2  - CMD Normalization
  UINT32 EWRDSEQ      : 1;   ///< BIT3  - Early DQ Write Drive Strength and Equalization Training
  UINT32 RDVC1D       : 1;   ///< BIT4  - Read Voltage Centering 1D
  UINT32 TXTCO        : 1;   ///< BIT5  - Write TCO Comp Training
  UINT32 CLKTCO       : 1;   ///< BIT6  - Clock TCO Comp Training
  UINT32 DIMMODTCA    : 1;   ///< BIT7  - Dimm ODT CA Training
  UINT32 TXTCODQS     : 1;   ///< BIT8  - Write TCO Dqs Training
  UINT32 DCC          : 1;   ///< BIT9  - Duty Cycle Correction
  UINT32 DQDFE        : 1;   ///< BIT10 - DQ DFE Training
  UINT32 SOTC         : 1;   ///< BIT11 - Sense amp offset correction
  UINT32 PERIODICDCC  : 1;   ///< BIT12 - Periodic DCC Enable
  UINT32 RMTBIT       : 1;   ///< BIT13 - Rank Margin Tool Per Bit
  UINT32 RsvdBits     :18;
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
  VDD_0_60    =  600,
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
  MrcSaGvPointLow,
  MrcSaGvPointMid,
  MrcSaGvPointHigh,
  MrcSaGvPointMax
} MrcSaGvPoint;

/// SA GV modes
///  Disabled:  SA GV Disabled, run all MRC tasks
///  FixedLow:  SA GV Disabled, run only MRC tasks marked with MRC_PF_GV_LOW
///  FixedMid:  SA GV Disabled, run only MRC tasks marked with MRC_PF_GV_MID
///  FixedHigh: SA GV Disabled, run only MRC tasks marked with MRC_PF_GV_HIGH
///  Enabled:   SA GV Enabled
typedef enum {
  MrcSaGvDisabled,
  MrcSaGvFixedLow,
  MrcSaGvFixedMid,
  MrcSaGvFixedHigh,
  MrcSaGvEnabled,
} MrcSaGv;

/// DIMM SPD Security Status
typedef enum {
  MrcSpdStatusGood,      ///< Memory is in a secure state.
  MrcSpdStatusAliased,   ///< Memory is aliased.
  MrcSpdStatusLast       ///< Must be last in the list
} MrcSpdStatus;

/// Define the virtual channel.
typedef enum {
  vcL,  ///< Virtual channel L
  vcS,  ///< Virtual channel S
} MrcVirtualChannel;

/// Define the board types.
typedef enum {
  btMobile              = 0,  ///< Mobile: Y/U/YN/UN (default)
  btMobileLp4Limit3200  = 1,  ///< Mobile: Y/U/YN/UN, with LP4/x limited to 3200
  btDesktop             = 2,  ///< Desktop: DT/Halo with DDR4 2DPC
  btUpServer            = 3,  ///< UP Server
} MrcBoardType;

/// Define the CPU family/model.
typedef enum {
  cmICL_ULX_ULT   = CPUID_FULL_FAMILY_MODEL_ICELAKE_ULT_ULX,    ///< IceLake ULT/ULX
  cmICL_DT_HALO   = CPUID_FULL_FAMILY_MODEL_ICELAKE_DT_HALO,    ///< IceLake DT/HALO
  cmICL_DT_HALO_R = CPUID_FULL_FAMILY_MODEL_ICELAKE_DT_HALO_R,  ///< IceLake DT/HALO Refresh
  cmEHL           = CPUID_FULL_FAMILY_MODEL_ELKHARTLAKE,        ///< ELKHARTLAKE
  cmJSL           = CPUID_FULL_FAMILY_MODEL_JASPERLAKE,         ///< JASPERLAKE
} MrcCpuModel;

/// Define the CPU Tick/Tock.
typedef enum {
  cfCnl    = 0,   ///< Cannonlake
  cfIcl,          ///< Icelake
  cfMax
} MrcCpuFamily;

/// Define the CPU stepping number.
typedef enum {
  /// Icelake ULX/ULT
  csIclA0         = EnumIclA0,
  csIclB0         = EnumIclB0,
  csIclB4         = EnumIclB4,
  csIclC0         = EnumIclC0,
  csIclD0         = EnumIclD0,
  csIclD1         = EnumIclD1,
  csIclUlxUltLast = csIclD1,

  /// Icelake Dt/Halo
  csIclP0         = EnumIclP0,
  csIclQ0         = EnumIclQ0,
  csIclDtHaloLast = csIclQ0,

  /// Icelake Dt/Halo Refresh
  csIclG0         = EnumIclG0,
  csIclH0         = EnumIclH0,
  csIclDtHaloRLast = csIclH0,
  /// Elkhartlake
  csEhlA0         = EnumEhlA0,
  csEhlB0         = EnumEhlB0,

  /// Jasperlake
  csJslA0         = EnumJslA0,
///
///
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
  MRC_DDR_TYPE_DDR3     = 1,
  MRC_DDR_TYPE_LPDDR3   = 2,
  MRC_DDR_TYPE_LPDDR4   = 3,
  MRC_DDR_TYPE_WIO2     = 4,
  MRC_DDR_TYPE_UNKNOWN,
  MAX_MRC_DDR_TYPE        ///< Delimiter
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
  MrcTeCpgc10,
  MrcTeCpgc15,
  MrcTeCpgc20,
  MrcTeMax
} MRC_TE_TYPE;

/// Enumeration for ODT Mode selection via Input Parameter and current ODT Mode.
typedef enum {
  MrcOdtModeDefault,
  MrcOdtModeCtt,
  MrcOdtModeVtt,
  MrcOdtModeVddq,
  MrcOdtModeVss,
  MrcOdtModeMax
} MRC_ODT_MODE_TYPE;

/// Generic enumeration interface for parameters that are Auto, Enable, Disable inputs
typedef enum {
  MrcAuto,
  MrcEnable,
  MrcDisable,
  MrcEnDisAutoMax
} MRC_EN_DIS_AUTO_TYPE;

// Enumeration Margin Limit Check mode
typedef enum {
  MARGIN_CHECK_DISABLE   = 0,
  MARGIN_CHECK_L1        = 1,
  MARGIN_CHECK_L2        = 2,
  MARGIN_CHECK_BOTH      = 3
} MarginCheckMode;

typedef struct {
  POINTER_STRUCT MrcData;
  POINTER_STRUCT Stream;
  POINTER_STRUCT Start;
  POINTER_STRUCT End;
  POINTER_STRUCT Current;
  int Level;
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
typedef union {
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MrcCapabilityIdA;

typedef union {
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MrcCapabilityIdB;

typedef union {
  UINT32  Data;
  UINT16  Data16[2];
  UINT8   Data8[4];
} MrcCapabilityIdC;

typedef union {
  UINT64 Data;
  struct {
    MrcCapabilityIdA A;
    MrcCapabilityIdB B;
    MrcCapabilityIdC C;
  } Data32;
} MrcCapabilityId;

/// MRC version description.
typedef struct {
  UINT8  Major;  ///< Major version number
  UINT8  Minor;  ///< Minor version number
  UINT8  Rev;    ///< Revision number
  UINT8  Build;  ///< Build number
} MrcVersion;

// This is used to locate MRC version in a binary BIOS file
typedef struct {
  UINT64     Signature;
  MrcVersion Version;
} MrcVersionWithSignature;

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
  UINT32     MeStolenBase;
  UINT32     MeStolenSize;
  UINT32     DprSize;
  UINT32     PrmrrBase;
  UINT32     PramBase;
  UINT32     LowestBase;
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
typedef UINT64       (*MRC_GET_CPU_TIME)            (void *MrcData);
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
// Full bios doesn't use the MrcCall table provided Io read and write functions. Mini bios uses them.
typedef void         (*MRC_PRINT_STRING)            (void *MrcData, void *String);
#else
typedef void         (*MRC_PRINT_STRING)            (void *String);
#endif
typedef UINT8        (*MRC_GET_RTC_CMOS)            (UINT8 Location);
typedef UINT64       (*MRC_MSR_READ_64)             (UINT32 Location);
typedef UINT64       (*MRC_MSR_WRITE_64)            (UINT32 Location, UINT64 Data);
typedef void         (*MRC_RETURN_FROM_SMC)         (void *GlobalData, UINT32 MrcStatus);
typedef void         (*MRC_DRAM_RESET)              (UINT32 PciEBaseAddress, UINT32 ResetValue);
typedef void         (*MRC_DELAY_NS)                (void *MrcData, UINT32 DelayNs);
typedef void         (*MRC_SET_LOCK_PRMRR)          (UINT64 PrmrrBase, UINT32 PrmrrSize);
typedef void         (*MRC_TXT_ACHECK)              (void);
typedef void         (*MRC_TXT_CLEAR_SECRETS_BIT)      (void);
typedef void         (*MRC_TXT_SET_POWER_DOWN_REQUEST) (void);
typedef EFI_STATUS   (*MRC_SET_GFX_MEM_MAP)         (void);

/// Function calls that are called external to the MRC.
///   This structure needs to be aligned with SA_FUNCTION_CALLS.  All functions that are
///   not part of SA_FUNCTION_CALLS need to be at the end of the structure.
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
  MRC_TXT_ACHECK              MrcTxtAcheck;
  MRC_TXT_CLEAR_SECRETS_BIT   MrcClearSecretsBit;
  MRC_TXT_SET_POWER_DOWN_REQUEST  MrcSetPowerDownRequest;
  MRC_SET_GFX_MEM_MAP         MrcSetGfxMemMap;
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
  MrcDdrType     DdrType;                 ///< DDR type: DDR3, DDR4, LPDDR3, LPDDR4, or WIO2
  MEMORY_PACKAGE ModuleType;              ///< Module type: UDIMM, SO-DIMM, etc.
  UINT32         SdramCount;              ///< The number of SDRAM components on a DIMM.
  UINT32         DimmCapacity;            ///< DIMM size in MBytes.
  UINT32         RowSize;                 ///< The DIMMs row address size.
  UINT16         ColumnSize;              ///< The DIMMs column address size.
  UINT16         Crc;                     ///< Calculated CRC16 of the DIMM's provided SPD. Can be used to detect DIMM change.
  UINT8          RankInDimm;              ///< The number of ranks in this DIMM.
  UINT8          Banks;                   ///< Number of banks the DIMM contains.
  UINT8          BankGroups;              ///< Number of bank groups the DIMM contains.
  UINT8          PrimaryBusWidth;         ///< DIMM primary bus width (Includes both subchannels in ECH mode).
  UINT8          DiePerSdramPackage;      ///< Number of Die in the DRAM Package (LPDDR Only)
  UINT8          ChannelsPerDie;          ///< Number of Channels per Die (LPDDR4 Only)
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
  MrcVirtualChannel VirtualChannel;                                               ///< Define the virtual channel type A or B.
  MrcTiming         Timing[MAX_PROFILE];                                          ///< The channel timing values.
  MrcTimeBase       TimeBase[MAX_DIMMS_IN_CHANNEL][MAX_PROFILE];                  ///< Medium and fine timebases for each DIMM in the channel and each memory profile.
  UINT32            Capacity;                                                     ///< Amount of memory in this channel, in MBytes.
  UINT32            DimmCount;                                                    ///< Number of valid DIMMs that exist in the channel.
  UINT32            DataCompOffset[MAX_SDRAM_IN_DIMM];                            ///< DataCompOffset CR
  MrcCommandMargin  Command[MAX_RANK_IN_CHANNEL][MAX_SUB_CHANNEL];                ///< Cmd setting
  MrcDqTimeMargin   RxDqPb[MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];     ///< Rx PerBit Pi Code
  MrcDqTimeMargin   TxDqPb[MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];     ///< Tx PerBit Pi Code
  MrcDqVrefMargin   RxDqVrefPb[MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS]; ///< Rx PerBit Vref
  MrcDqVrefMargin   TxDqVrefPb[MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS]; ///< Rx PerBit Vref
  MrcRecvEnMargin   ReceiveEnable[MAX_RANK_IN_CHANNEL][MAX_SUB_CHANNEL];          ///< Receive enable per rank
  MrcWrLevelMargin  WriteLevel[MAX_RANK_IN_CHANNEL][MAX_SUB_CHANNEL];             ///< Write leveling per rank
  UINT8             ValidRankBitMask;                                             ///< Bit map of the populated ranks per channel
  UINT8             ValidSubChBitMask;                                            ///< Bit map of the populated 32-bit sub-channels per 64-bit channel (2 bits)
  UINT16            ValidByteMask;                                                ///< Bit map of the populated bytes per channel
  UINT8             ValidCkeBitMask;                                              ///< Bit map of the used CKE pins per channel
  UINT8             ByteStart[MAX_SUB_CHANNEL];                                   ///< Defines the CPU Byte start associated with the SubChannel requested as the index to the array.
  UINT8             ByteEnd[MAX_SUB_CHANNEL];                                     ///< Defines the CPU Byte limit associated with the SubChannel requested as the index to the array.
  MrcDimmOut        Dimm[MAX_DIMMS_IN_CHANNEL];                                   ///< DIMM specific output variables.
} MrcChannelOut;

/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are memory controller level definitions. All channels on a controller are set to these values.
typedef struct {
  MrcControllerSts Status;                ///< Indicates whether this controller should be used.
  UINT16           DeviceId;              ///< The PCI device id of this memory controller.
  UINT8            RevisionId;            ///< The PCI revision id of this memory controller.
  UINT8            ChannelCount;          ///< Number of valid channels that exist on the controller.
  MrcChannelOut    Channel[MAX_CHANNEL];  ///< The following are channel level definitions.
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
#define MRC_REGISTER_COUNT_COMMON (1564 / sizeof (UINT32)) ///< The number of MC registers that need to be saved (common)
#define MRC_REGISTER_COUNT_SAGV   (5752 / sizeof (UINT32)) ///< The number of MC registers that need to be saved (per SA GV point)
typedef struct {
  MrcCapabilityId McCapId;                                  ///< The memory controller's capabilities.
  UINT32          RegSaveCommon[MRC_REGISTER_COUNT_COMMON]; ///< The MC registers that are common to both SA GV points.
  UINT32          RegSaveLow[MRC_REGISTER_COUNT_SAGV];      ///< The MC registers for the Low SA GV point.
  UINT32          RegSaveMid[MRC_REGISTER_COUNT_SAGV];      ///< The MC registers for the Middle SA GV point.
  UINT32          RegSaveHigh[MRC_REGISTER_COUNT_SAGV];     ///< The MC registers for the High SA GV point, or for SA GV Disabled case.
  UINT32          MeStolenSize;                             ///< The manageability engine memory size, in Mbyte units.
  UINT32          ImrAlignment;                             ///< The Largest CSE IMR Memory Size, in Mbytes units
  MrcCpuStepping  CpuStepping;                              ///< The last cold boot happened with this CPU stepping.
  MrcCpuModel     CpuModel;                                 ///< The last cold boot happened with this CPU model.
  MrcCpuFamily    CpuFamily;                                ///< The last cold boot happened with this CPU Family.
  MrcVersion      Version;                                  ///< The last cold boot happened with this MRC version.
  UINT32          SaMemCfgCrc;                              ///< The CRC32 of the system agent memory configuration structure.
  MrcContSave     Controller[MAX_CONTROLLERS];              ///< The following are controller level definitions.
  MrcFrequency    FreqMax;                                  ///< The system's requested maximum frequency.
  MrcFrequency    Frequency;                                ///< The system's common memory controller frequency.
  MrcFrequency    HighFrequency;                            ///< High operating frequency, used for LPDDR4.
  MrcFrequency    FreqSaGvLow;                              ///< Final resolved SAGV Low frequency - based on inputs, SPD, and capabilities
  MrcFrequency    FreqSaGvMid;                              ///< Final resolved SAGV Mid frequency - based on inputs, SPD, and capabilities
  UINT32          MemoryClock;                              ///< The system's common memory controller clock, in femtoseconds.
  MrcRefClkSelect RefClk;                                   ///< The memory controller is going to use this reference clock.
  MrcClockRatio   Ratio;                                    ///< Request for this memory controller to use this clock ratio.
  MrcVddSelect    VddVoltage[MAX_PROFILE];                  ///< The voltage (VDD) setting for all DIMMs in the system, per profile.
  BOOLEAN         EccSupport;                               ///< TRUE if ECC is enabled and supported on this controller.
  MrcDdrType      DdrType;                                  ///< DDR type: DDR4, LPDDR3, or LPDDR4.
  UINT8           BurstLength;                              ///< Burst length in DCLKs
  BOOLEAN         Lp4x;                                     ///< LPDDR4X part was detected.
  BOOLEAN         Lp4x8;                                    ///< DRAM die width is x8 (Byte mode).
  BOOLEAN         EnhancedChannelMode;                      ///< Indicates if 64-bit channel is subdivided into two 32-bit channels.
  BOOLEAN         XmpProfileEnable;                         ///< XMP capable DIMMs detected in system (0 = no, 1 = yes).
  BOOLEAN         TCRSensitiveHynixDDR4;                    ///< TCR sensitive Hynix DDR4 in the system
  BOOLEAN         TCRSensitiveMicronDDR4;                   ///< TCR sensitive Micron DDR4 in the system
  BOOLEAN         LpddrEctDone;                             ///< Set to TRUE once Early Command Training on LPDDR is done, and we can run JEDEC Init
  UINT8           ClkDcc[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MARGIN_CHECK_BOTH][MAX_EDGES];      ///< Look Up Table for CLK DCC per CLK PI setting (only for margin check L1 & L2)
  UINT8           ClkDccAipCb[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MARGIN_CHECK_BOTH][MAX_EDGES]; ///< Look Up Table for DccAipCb per CLK PI setting (only for margin check L1 & L2)
  UINT8           DqsDcc[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MARGIN_CHECK_BOTH][MAX_EDGES];      ///< Look Up Table for DQS DCC per DQS PI setting (only for margin check L1 & L2)
  UINT8           DqsDccAipCb[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MARGIN_CHECK_BOTH][MAX_EDGES]; ///< Look Up Table for DqsDccAipCb per DQS PI setting (only for margin check L1 & L2)
  BOOLEAN         ClkDccInit;                               ///< Whether the Look Up Table for CLK DCC is populated with correct data
  BOOLEAN         DqsDccInit;                               ///< Whether the Look Up Table for DQS DCC is populated with correct data
  BOOLEAN         Gear2Ever;                                ///< If any SAGV point was Gear2, then this is TRUE otherwise FALSE.
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
  BOOLEAN             VddVoltageDone;              ///< To determine if VddVoltageDone update has been done already
  BOOLEAN             EccSupport;                  ///< TRUE if ECC is enabled and supported on this controller.
  BOOLEAN             RestoreMRs;                  ///< Enable/Disable restoring
  BOOLEAN             LpddrEctDone;                ///< Set to TRUE once Early Command Training on LPDDR is done, and we can run JEDEC Init
  BOOLEAN             JedecInitDone;               ///< Set to TRUE once JEDEC Init on LPDDR/DDR4 is done
  BOOLEAN             XmpProfileEnable;            ///< XMP capable DIMMs detected in system (0 = no, 1 = yes).
  BOOLEAN             Capable100;                  ///< The MC is capable of 100 reference clock (0 = no, 1 = yes).
  BOOLEAN             AutoSelfRefresh;             ///< Indicates ASR is supported for all the DIMMS for 2xRefresh
  MrcDdrType          DdrType;                     ///< Current memory type: DDR3, DDR4, LPDDR3, LPDDR4, or WIO2
  MrcSpdStatus        SpdSecurityStatus;           ///< Status variable to inform BIOS that memory contains an alias.
  UINT32              MrcTotalChannelLimit;        ///< The maximum allowed memory size per channel, in MBytes.
  UINT8               SdramCount;                  ///< The number of SDRAM components on a DIMM.
  UINT16              Qclkps;                      ///< QCLK period in pS, this is internal MC/DDRIO clock which is impacted by Gear1/2
  UINT16              Dclkps;                      ///< DCLK period in pS, this is internal MC/DDRIO clock which is impacted by Gear1/2
  UINT16              tCKps;                       ///< Memory clock period in pS (external bus clock)
  UINT16              UIps;                        ///< Data Unit Interval period in pS (half of external bus clock)
  UINT8               DQPat;                       ///< Global Variable storing the current DQPat REUT Test.
  INT8                DQPatLC;                     ///< Global Variable storing the current DQPat Loopcount.
  UINT16              NumCL;                       ///< Global Variables storing the current number of Cachelines
  UINT8               ReutStopType;                ///< Global Variable storing the current test stop type.
  UINT8               ValidRankMask;               ///< Rank bit map.  Includes both channels
  UINT8               ValidChBitMask;              ///< Channel bit map of the populated channels
  UINT8               ValidSubChMask;              ///< Sub Channel bit map.  Includes both Channels.
  BOOLEAN             UpmPwrRetrainFlag;           ///< A flag that indicates if training with higher UPM/PWR limits.
  UINT32              MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES]; ///< Stores last margin measurement.
  MrcOdtPowerSaving   OdtPowerSavingData;          ///< ODT power savings data.
  BOOLEAN             TxDIMMVref[MAX_CHANNEL];     ///< Whether Write DIMM Vref is enabled based on Channel
  UINT32              MchBarWriteCount;            ///< The number of MMIO writes performed during MRC execution.
  UINT32              MchBarReadCount;             ///< The number of MMIO reads performed during MRC execution.
  UINT8               tMAC;                        ///< Maximum Activate Count for pTRR.
  BOOLEAN             Ddr4PdaEnable;               ///< Current status of PDA - if true all the Mr6 operations need to use PDA mode.
  UINT8               SubChCount;                  ///< Number of valid SubChannels that exist.  This is symmetrical per Channel.
  UINT8               BurstLength;                 ///< Burst length in DCLKs
  BOOLEAN             EnhancedChannelMode;         ///< Indicates if 64-bit channel is subdivided into two 32-bit channels.
  MrcControllerOut    Controller[MAX_CONTROLLERS]; ///< The following are controller level definitions.
  BOOLEAN             TCRSensitiveHynixDDR4;       ///< TCR sensitive Hynix DDR4 in the system
  BOOLEAN             TCRSensitiveMicronDDR4;      ///< TCR sensitive Micron DDR4 in the system
  MRC_ODT_MODE_TYPE   OdtMode;                     ///< Specifies the current ODT Mode the DDRIO is set to.
  BOOLEAN             DramDqOdtEn;                 ///< Specifies if the DRAM DQ ODT is enabled.
  BOOLEAN             Lp4x;                        ///< LPDDR4X part was detected.
  BOOLEAN             Lp4x8;                       ///< DRAM die width is x8 (Byte mode).
  BOOLEAN             Gear2Ever;                   ///< If any SAGV point was Gear2, then this is TRUE otherwise FALSE.
  UINT32              DccRatio;                    ///< DCC Ratio
  BOOLEAN             SenseAmpRetrain;             ///< Set to TRUE if sense amp retraining needed after - CTLE, ICOMP/RCOMP, etc.
  BOOLEAN             UseExistingStress;           ///< If TRUE, then DQTimeCentering1D will skip SetupIOTest() and use existing CPGC setup
#ifdef BDAT_SUPPORT
  union {
    MRC_BDAT_SCHEMA_LIST_HOB *Pointer;             ///< Pointer to the BDAT schema list.
    UINT64                   Data;
  } BdatSchemasHob;
  union {
    BDAT_MEMORY_DATA_HOB *Pointer;                 ///< Pointer to the BDAT memory data HOB.
    UINT64               Data;
  } BdatMemoryHob[MAX_SCHEMA_LIST_LENGTH];
  UINT8               Margin2DResult[MAX_2D_EYE_TYPE][MAX_RANK_IN_CHANNEL][MAX_PHY_CHANNEL][MAX_2D_EYE_OFFSETS][MAX_EDGES]; ///< Stores the 2D Eye Margin
#endif

#ifdef UP_SERVER_FLAG
  UINT8               ThermOffset[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];                        ///< TSOD Thermal Offset
#endif
  UINT32              IbeccEdsrSize;
} MrcOutput;

///****************************************
/// Input related "global data" structures.
///****************************************

/// This data structure contains all the "global data" values that are considered input by the MRC.
/// The following are DIMM level definitions. All ranks on a DIMM are set to these values.
typedef struct {
  MrcDimmSts  Status;                 ///< Indicates whether this DIMM should be used.
  MrcSpdData  Spd;                    ///< The SPD data for each DIMM. SPDGeneral field = 0 when absent.
  MrcTiming   Timing;                 ///< The DIMMs requested timing overrides.
  UINT8       SpdAddress;             ///< The SMBus address for the DIMM's SPD data.
} MrcDimmIn;

/// This data structure contains all the "global data" values that are considered input by the MRC.
/// The following are channel level definitions. All DIMMs on a memory channel are set to these values.
typedef struct {
  MrcChannelSts Status;                        ///< Indicates whether this channel should be used.
  UINT32        DimmCount;                     ///< The maximum number of DIMMs on this channel.
  MrcDimmIn     Dimm[MAX_DIMMS_IN_CHANNEL];    ///< The following are DIMM level definitions.
  UINT8         DqsMapCpu2Dram[8];             ///< Mapping from CPU DQS pins to SDRAM DQS pins
  UINT8         DqMapCpu2Dram[8][MAX_BITS];    ///< Mapping from CPU DQ pins to SDRAM DQ pins
  UINT8         DQByteMap[MrcIterationMax][2]; ///< Maps which PI clocks are used by what LPDDR DQ Bytes (from CPU side), per group
                                               ///< DQByteMap[0] - ClkDQByteMap:
                                               ///<   If clock is per rank, program to [0xFF, 0xFF]
                                               ///<   If clock is shared by 2 ranks, program to [0xFF, 0] or [0, 0xFF]
                                               ///<   If clock is shared by 2 ranks but does not go to all bytes,
                                               ///<           Entry[i] defines which DQ bytes Group i services
                                               ///< DQByteMap[1] - CmdDQByteMap: Entry[0] is CAA and Entry[1] is CAB
                                               ///< DQByteMap[2] - CtlDQByteMap : Always program to [0xFF, 0] since we have 1 CTL / rank
                                               ///<                               Variable only exists to make the code easier to use
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

  UINT32  EccSupport:1;              ///< Offset 64 Bit 0: DIMM Ecc Support option - for Desktop only: 0=Disable, <b>1=Enable</b>
  UINT32  MrcSafeConfig:1;           ///<  Bit 1 - MRC Safe Mode: <b>0=Disable</b>, 1=Enable
  UINT32  RemapEnable:1;             ///<  Bit 2 - This option is used to control whether to enable/disable memory remap above 4GB: 0=Disable, <b>1=Enable</b>.
  UINT32  ScramblerSupport:1;        ///<  Bit 3 - Memory scrambler support: 0=Disable, <b>1=Enable</b>
  UINT32  Off64Bit4Rsvd:1;           ///<  Bit 4 - reserved
  UINT32  DdrThermalSensor:1;        ///<  Bit 5 - Ddr Thermal Sensor: 0=Disable, <b>1=Enable</b>
  UINT32  ForceSingleSubchannel:1;   ///<  Bit 6 - TRUE means use SubChannel0 only (for LPDDR4): <b>0=Disable</b>, 1=Enable
  UINT32  Off64Bits7to8Rsvd:2;       ///<  Bit 7:8 reserved
  UINT32  SimicsFlag:1;              ///<  Bit 9 - Option to Enable SIMICS: 0=Disable, <b>1=Enable</b>
  UINT32  Ddr4DdpSharedClock:1;      ///<  Bit 10 - Select if CLK0 is shared between Rank0 and Rank1 in DDR4 DDP package. <b>0=Not shared</b>, 1=Shared
  UINT32  SharedZqPin:1;             ///<  Bit 11 - Select if the ZQ resistor is shared between Ranks in DDR4/LPDDR4 DRAM Packages <b>0=Not Shared</b>, 1=Shared
  UINT32  Off64Bits12to16Rsvd:5;     ///<  Bit 12:16 - 5 Bits reserved for Thermal Management
  UINT32  Lp4DqsOscEn:1;             ///<  Bit 17 - LPDDR4 Write DQ/DQS Retraining: 0=Disable, <b>1=Enable</b>
  UINT32  SaGvLowGear2:1;            ///<  Bit 18 - Gear mode for SAGV Low point:  <b>0=Gear1</b>, 1=Gear2
  UINT32  SaGvMidGear2:1;            ///<  Bit 19 - Gear mode for SAGV Mid point:  <b>0=Gear1</b>, 1=Gear2
  UINT32  SaGvHighGear2:1;           ///<  Bit 20 - Gear mode for SAGV High point: <b>0=Gear1</b>, 1=Gear2
  UINT32  DdrSpeedControl:1;         ///<  Bit 21 - DDR Frequency and Gear control for all SAGV points: <b>0=Automatic</b>, 1=Manual.
  UINT32  Lp4ClockMirror:1;          ///<  Bit 22 - Select if LPDDR4 CLK Mirroring is used on the board <b>0=Disabled</b>, 1=Enabled
  UINT32  ReservedBits1:9;           ///<  Bits 23:31 reserved
  /**
   Disables a DIMM slot in the channel even if a DIMM is present\n
   Array index represents the channel number (0 = channel 0, 1 = channel 1)\n
     <b>0x0 = DIMM 0 and DIMM 1 enabled</b>\n
     0x1 = DIMM 0 disabled, DIMM 1 enabled\n
     0x2 = DIMM 0 enabled, DIMM 1 disabled\n
     0x3 = DIMM 0 and DIMM 1 disabled (will disable the whole channel)\n
  **/
  UINT8   DisableDimmChannel[MAX_CHANNEL];///< Offset 68
  UINT8   Ratio;                  ///< Offset 70 DDR Frequency ratio, to multiply by 133 or 100 MHz depending on RefClk. <b>0 = Auto</b>
  UINT8   ProbelessTrace;         ///< Offset 71 Probeless Trace: <b>0=Disabled</b>, <b>1=Enabled</b>
  UINT32  BClkFrequency;          ///< Offset 72 Base reference clock value, in Hertz: <b>100000000 = 100Hz</b>, 125000000=125Hz, 167000000=167Hz, 250000000=250Hz
  /**
     - Channel Hash Enable.\n
    NOTE: BIT7 will interleave the channels at a 2 cache-line granularity, BIT8 at 4 and BIT9 at 8\n
    0=BIT6, <B>1=BIT7</B>, 2=BIT8, 3=BIT9
  **/
  UINT8   ChHashInterleaveBit;    ///< Offset 76 Option to select interleave Address bit. Valid values are 0 - 3 for BITS 6 - 9 (Valid values for BDW are 0-7 for BITS 6 - 13)
  UINT8   EnergyScaleFact;        ///< Offset 77 Energy Scale Factor. 0=Minimal, 7=Maximum, <b>4=Default</b>
  BOOLEAN PerBankRefresh;         ///< Offset 78 Enables and Disables the per bank refresh.  This only impacts memory technologies that support PBR: LPDDR4.  FALSE=Disabled, <b>TRUE=Enabled</b>
  UINT8   Ddr4OneDpc;             ///< Offset 79 DDR4 1DPC performance feature: 0 - Disabled; 1 - Enabled on DIMM0 only, 2 - Enabled on DIMM1 only; 3 - Enabled on both DIMMs. (bit [0] - DIMM0, bit [1] - DIMM1)
  // Training Algorithms
  TrainingStepsEn  TrainingEnables;   ///< Offset 80 Options to Enable individual training steps
  TrainingStepsEn2 TrainingEnables2;  ///< Offset 84 Options to Enable individual training steps

  UINT32  MrcTrainOnWarm:1;           ///<  Bit 0 Offset 88 - Enables MRC training on warm boot : <b>0=Disable</b>, 1=Enable
  UINT32  MrcTimeMeasure:1;           ///<  Bit 1  - Enables serial debug level to display the MRC execution times only: <b>0=Disable</b>, 1=Enable
  UINT32  MrcFastBoot:1;              ///<  Bit 2  - Enables the MRC fast boot path for faster cold boot execution: 0=Disable, <b>1=Enable</b>
  UINT32  DqPinsInterleaved:1;        ///<  Bit 3  - Interleaving mode of DQ/DQS pins which depends on board routing: <b>0=Disable</b>, 1=Enable
  UINT32  RankInterleave:1;           ///<  Bit 4  - Rank Interleave Mode: 0=Disable, <b>1=Enable</b>
  UINT32  EnhancedInterleave:1;       ///<  Bit 5  - Enhanced Interleave Mode: 0=Disable, <b>1=Enable</b>
  UINT32  WeaklockEn:1;               ///<  Bit 6  - Weak Lock Enable: 0=Disable, <b>1=Enable</b>
  UINT32  ExtendedBankHashing:1;      ///<  Bit 7  - Enable EBH Extended Bank Hashing: <b>0=Disable</b>, 1=Enable
  UINT32  MemoryTrace:1;              ///<  Bit 8  - Memory Trace to second DDR channel using Stacked Mode: <b>0=Disable</b>, 1=Enable
  UINT32  ChHashEnable:1;             ///<  Bit 9  - Channel Hash Enable: 0=Disable, <b>1=Enable</b>
  UINT32  EnableExtts:1;              ///<  Bit 10 - Enable Extts: <b>0=Disable</b>, 1=Enable
  UINT32  EnableCltm:1;               ///<  Bit 11 - Enable Closed Loop Thermal Management: <b>0=Disable</b>, 1=Enable
  UINT32  EnableOltm:1;               ///<  Bit 12 - Enable Open Loop Thermal Management: <b>0=Disable</b>, 1=Enable
  UINT32  EnablePwrDn:1;              ///<  Bit 13 - Enable Power Down control for DDR: 0=PCODE control, <b>1=BIOS control</b>
  UINT32  EnablePwrDnLpddr:1;         ///<  Bit 14 - Enable Power Down for LPDDR: 0=PCODE control, <b>1=BIOS control</b>
  UINT32  LockPTMregs:1;              ///<  Bit 15 - Lock PCU Thermal Management registers: 0=Disable, <b>1=Enable</b>
  UINT32  UserPowerWeightsEn:1;       ///<  Bit 16 - Allows user to explicitly set power weight, scale factor, and channel power floor values: <b>0=Disable</b>, 1=Enable
  UINT32  RaplLim2Lock:1;             ///<  Bit 17 - Lock DDR_RAPL_LIMIT register: <b>0=Disable</b>, 1=Enable
  UINT32  RaplLim2Ena:1;              ///<  Bit 18 - Enable Power Limit 2: <b>0=Disable</b>, 1=Enable
  UINT32  RaplLim1Ena:1;              ///<  Bit 19 - Enable Power Limit 1: <b>0=Disable</b>, 1=Enable
  UINT32  SrefCfgEna:1;               ///<  Bit 20 - Enable Self Refresh: 0=Disable, <b>1=Enable</b>
  UINT32  ThrtCkeMinDefeatLpddr:1;    ///<  Bit 21 - Throttler CKE min defeature for LPDDR: 0=Disable, <b>1=Enable</b>
  UINT32  ThrtCkeMinDefeat:1;         ///<  Bit 22 - Throttler CKE min defeature: <b>0=Disable</b>, 1=Enable
  UINT32  AutoSelfRefreshSupport:1;   ///<  Bit 23 - FALSE = No auto self refresh support, <b>TRUE = auto self refresh support</b>
  UINT32  ExtTemperatureSupport:1;    ///<  Bit 24 - FALSE = No extended temperature support, <b>TRUE = extended temperature support</b>
  UINT32  MobilePlatform:1;           ///<  Bit 25 - Memory controller device id indicates: <b>TRUE if mobile</b>, FALSE if not. Note: This will be auto-detected and updated.
  UINT32  Force1Dpc:1;                ///<  Bit 26 - TRUE means force one DIMM per channel, <b>FALSE means no limit</b>
  UINT32  ForceSingleRank:1;          ///<  Bit 27 - TRUE means use Rank0 only (in each DIMM): <b>0=Disable</b>, 1=Enable
  UINT32  RhPrevention:1;             ///<  Bit 28 - RH Prevention Enable/Disable: 0=Disable, <b>1=Enable</b>
  UINT32  VttTermination:1;           ///<  Bit 29 - Vtt Termination for Data ODT: <b>0=Disable</b>, 1=Enable
  UINT32  VttCompForVsshi:1;          ///<  Bit 30 - Enable/Disable Vtt Comparator For Vsshi: <b>0=Disable</b>, 1=Enable
  UINT32  ExitOnFailure:1;            ///<  Bit 31 - MRC option for exit on failure or continue on failure: 0=Disable, <b>1=Enable</b>

  UINT32  VddSettleWaitTime;      ///< Offset 92 Amount of time in microseconds to wait for Vdd to settle on top of 200us required by JEDEC spec: <b>Default=0</b>
  UINT16  FreqSaGvLow;            ///< Offset 96 SA GV: 0 is Auto/default, otherwise holds the frequency value: <b>0=Default</b>, 1067, 1200, 1333, 1400, 1600, 1800, 1867.
  UINT16  SrefCfgIdleTmr;         ///< Offset 98 Self Refresh idle timer: <b>512=Minimal</b>, 65535=Maximum
  UINT8   RhActProbability;       ///< Offset 100 Activation probability for Hardware RHP
  UINT8   SmramMask;              ///< Offset 101 Reserved memory ranges for SMRAM
  UINT8   Reserved102[38];        ///< Offset 102 - 139 Reserved
  UINT16  ChHashMask;             ///< Offset 140 Channel Hash Mask: 0x0001=BIT6 set(Minimal), 0x3FFF=BIT[19:6] set(Maximum), <b>0x30CE= BIT[19:18, 13:12 ,9:7] set</b>
  UINT16  DdrFreqLimit;           ///< Offset 142 Memory Frequency setting: 3=1067, 5=1333, 7=1600, 9=1867, 11=2133, 13=2400, <b>15=2667</b>
  ThermalMngmtEn  ThermalEnables; ///< Offset 144 - 187

  UINT8   MaxRttWr;               ///< Offset 188 Maximum DIMM RTT_WR to use in power training: <b>0=ODT Off</b>, 1 = 120 ohms
  UINT8   ThrtCkeMinTmr;          ///< Offset 189 Throttler CKE min timer: 0=Minimal, 0xFF=Maximum, <b>0x30=Default</b>
  UINT8   ThrtCkeMinTmrLpddr;     ///< Offset 190 Throttler CKE min timer for LPDDR: 0=Minimal, 0xFF=Maximum, <b>0x40=Default</b>
  UINT8   Reserved191;            ///< Offset 191 Reserved
  UINT8   CkeRankMapping;         ///< Offset 192 Bits [7:4] - Channel 1, bits [3:0] - Channel 0. <b>0xAA=Default</b> Bit [i] specifies which rank CKE[i] goes to.
  UINT8   Reserved193;            ///< Offset 193 Reserved
  UINT8   CaVrefConfig;           ///< Offset 194 0=VREF_CA goes to both CH_A and CH_B, 1=VREF_CA to CH_A, VREF_DQ_A to CH_B, <b>2=VREF_CA to CH_A, VREF_DQ_B to CH_B</b>
  UINT8   SaGv;                   ///< Offset 195 SA GV: <b>0=Disabled</b>, 1=FixedLow, 2=FixedMid, 3=FixedHigh, 4=Enabled
  UINT8   RaplPwrFlCh1;           ///< Offset 196 Power Channel 1 Floor value: <b>0=Minimal</b>, 255=Maximum
  UINT8   RaplPwrFlCh0;           ///< Offset 197 Power Channel 0 Floor value: <b>0=Minimal</b>, 255=Maximum
  UINT8   NModeSupport;           ///< Offset 198 Memory N Mode Support - Enable user to select Auto, 1N or 2N: <b>0=AUTO</b>, 1=1N, 2=2N.
  UINT8   RefClk;                 ///< Offset 199 Selects the DDR base reference clock. 0x01 = 100MHz, <b>0x00 = 133MHz</b>
  UINT8   EnCmdRate;              ///< Offset 200 CMD Rate Enable: 0=Disable, 1=1 CMD, 2=2 CMDs, <b>3=3 CMDs</b>, 4=4 CMDs, 5=5 CMDs, 6=6 CMDs, 7=7 CMDs
  UINT8   Refresh2X;              ///< Offset 201 Refresh 2x: <b>0=Disable</b>, 1=Enable for WARM or HOT, 2=Enable for HOT only
  UINT8   EpgEnable;              ///< Offset 202 Enable Energy Performance Gain.
  UINT8   RhSolution;             ///< Offset 203 Type of solution to be used for RHP - 0/1 = HardwareRhp/Refresh2x
  UINT8   UserThresholdEnable;    ///< Offset 204 Flag to manually select the DIMM CLTM Thermal Threshold, 0=Disable,  1=Enable, <b>0=Default</b>
  UINT8   UserBudgetEnable;       ///< Offset 205 Flag to manually select the Budget Registers for CLTM Memory Dimms , 0=Disable,  1=Enable, <b>0=Default</b>
  UINT8   TsodTcritMax;           ///< Offset 206 TSOD Tcrit Maximum Value  to be Configure , 0=Minimal, 128=Maximum, , <b>105=Default</b>

  UINT8   TsodEventMode;          ///< Offset 207 Flag to Enable Event Mode Interruption in TSOD Configuration Register, 0=Disable,  1=Enable, <b>1=Default</b>
  UINT8   TsodEventPolarity;      ///< Offset 208 Event Signal Polarity in TSOD Configuration Register, 0=Low,  1=High, <b>0=Default</b>
  UINT8   TsodCriticalEventOnly;  ///< Offset 209 Critical Trigger Only in TSOD Configuration Register,0=Disable,  1=Enable, <b>1=Default</b>
  UINT8   TsodEventOutputControl; ///< Offset 210 Event Output Control in TSOD Configuration Register,0=Disable,  1=Enable, <b>1=Default</b>
  UINT8   TsodAlarmwindowLockBit; ///< Offset 211 Alarm Windows Lock Bit in TSOD Configuration Register,0=Unlock,  1=Lock, <b>0=Default</b>
  UINT8   TsodCriticaltripLockBit;///< Offset 212 Critical Trip Lock Bit in TSOD Configuration Register,0=Unlock,  1=Lock, <b>0=Default</b>
  UINT8   TsodShutdownMode;       ///< Offset 213 Shutdown Mode TSOD Configuration Register,0=Enable,  1=Disable, <b>0=Default</b>
  UINT8   TsodThigMax;            ///< Offset 214 Thigh Max Value In the  for CLTM Memory Dimms , 0=Disable,  1=Enable, <b>0=Default</b>
  UINT8   TsodManualEnable;       ///< Offset 215 Flag to manually select the TSOD Register Values , 0=Disable,  1=Enable, <b>0=Default</b>
  UINT8   DllBwEn0;               ///< Offset 216 DllBwEn value for 1067
  UINT8   DllBwEn1;               ///< Offset 217 DllBwEn value for 1333
  UINT8   DllBwEn2;               ///< Offset 218 DllBwEn value for 1600
  UINT8   DllBwEn3;               ///< Offset 219 DllBwEn value for 1867 and up
  UINT8   RetrainOnFastFail;      ///< Offset 220 Restart MRC in Cold mode if SW MemTest fails during Fast flow. 0 = Disabled, <b>1 = Enabled</b>
  UINT8   ForceOltmOrRefresh2x;   ///< Offset 221 Force OLTM or 2X Refresh when needed. <b>0 = Force OLTM</b>, 1 = Force 2x Refresh
  UINT8   PowerDownMode;          ///< Offset 222 CKE Power Down Mode: <b>0xFF=AUTO</b>, 0=No Power Down, 1= APD mode, 6=PPD-DLL Off mode
  UINT8   PwdwnIdleCounter;       ///< Offset 223 CKE Power Down Mode Idle Counter: 0=Minimal, 255=Maximum, <b>0x80=0x80 DCLK</b>
  UINT8   IsvtIoPort;             ///< Offset 224 ISVT IO Port Address: 0=Minimal, 0xFF=Maximum, <b>0x99=Default</b>
  UINT8   CmdRanksTerminated;     ///< Offset 225 LPDDR4: Bitmask of ranks that have CA bus terminated. <b>0x01=Default, Rank0 is terminating and Rank1 is non-terminating</b>
  UINT8   RMTLoopCount;           ///< Offset 226 Indicates the Loop Count to be used for Rank Margin Tool Testing: 1=Minimal, 32=Maximum, 0=AUTO, <b>0=Default</b>
  UINT8   MarginLimitCheck;       ///< Offset 227 Margin limit check
  UINT16  MarginLimitL2;          ///< Offset 228 Margin limit check L2 threshold
  UINT16  FreqSaGvMid;            ///< Offset 230 SA GV: 0 is Auto/default, otherwise holds the frequency value expressed as an integer: <b>0=Default</b>, 1600, 1800, 1867, 2000, 2133, etc.
  UINT32  RmtPerTask:1;           ///< Offset 232 Bit 0: Rank Margin Tool Per Task. <b>0 = Disabled</b>, 1 = Enabled
  UINT32  TrainTrace:1;           ///< Offset 232 Bit 1: Trained state tracing debug. <b>0 = Disabled</b>, 1 = Enabled
  UINT32  SafeMode:1;             ///< Offset 232 Bit 2: Define if safe mode is enabled for MC/IO
  UINT32  LowSupplyEnData:1;      ///< Offset 232 Bit 3: Option to enable Low Supply for LPDDR4 Data. <b>0 = Disabled</b>, 1 = Enabled
  UINT32  LowSupplyEnCcc:1;       ///< Offset 232 Bit 4: Option to enable Low Supply for LPDDR4 Clock/Command/Control. <b>0 = Disabled</b>, 1 = Enabled
  UINT32  Ibecc:1;                ///<            Bit 5 - Inband ECC - for LPDDR4 and LPDDR5 only: 0=Disable, <b>1=Disable</b>
  UINT32  IbeccParity:1;          ///<            Bit 6 - Inband ECC Parity Control - for LPDDR4 and LPDDR5 only: 0=Disable, <b>1=Disable</b>
  UINT32  IbeccOperationMode:2;   ///<            Bits 7:8 - Inband ECC Operation Mode: 0=Functional Mode protects requests based on the address range, <b>1=Makes all requests non protected and ignore range checks</b>, 2=Makes all requests protected and ignore range checks
  UINT32  DisPgCloseIdleTimeout:1;///< Offset 232 Bit 9: Disable Page Close Idle Timeout: 0=Enable, <b>1=Disable</b>
  UINT32  Off232RsvdBits:22;      ///< Offset 232 Bit 10-31: Reserved
  UINT8   IbeccProtectedRegionEnable[MAX_IBECC_REGIONS];
  UINT16  IbeccProtectedRegionBase[MAX_IBECC_REGIONS];
  UINT16  IbeccProtectedRegionMask[MAX_IBECC_REGIONS];
  // End of synchronization to the SA MEMORY_CONFIGURATION structure.

  UINT64          TscTimeBase;                 ///< CPU TSC timebase in [us] : (BCLK * Ratio / 1000 / 1000)
  MrcFrequency    FreqMax;                     ///< The requested maximum valid frequency.
  MrcBoardType    BoardType;                   ///< define the board type (Mobile, Desktop, UP server etc.). OEM can add more boards.
  MrcCpuStepping  CpuStepping;                 ///< define the CPU stepping.
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
  UINT32          DprSize;                     ///< DPR size required by system in MB.
  UINT32          PrmrrSize;                   ///< Prmrr size required by the system in MB.
  UINT8           PramSize;                    ///< Pram size required by system in MB

  POINTER_STRUCT  SerialBuffer;                ///< Pointer to the start of the serial buffer.
  UINT32          SerialBufferSize;            ///< The size of the serial buffer, in bytes.
  UINT32          DebugStream;                 ///< The debug port pointer.
  INT32           DebugLevel;                  ///< Indicates the level of debug messaging.
  UINT16          VccIomV;                     ///< VccIO logic voltage in mV.
  MrcControllerIn Controller[MAX_CONTROLLERS]; ///< The following are controller level definitions.
  POINTER_STRUCT    HeapBase;                     ///< Starting address of the heap space.
  UINT32            HeapSize;                     ///< Size of the heap space, in bytes.
  POINTER_STRUCT    MrcStackTop;                  ///< Top of the stack at the beginning of MRC, for stack usage calculations.
  BOOLEAN           BdatEnable;                   ///< Option to enable output of training results into BDAT.
  UINT8             BdatTestType;                 ///< When BdatEnable is set to TRUE, this option selects the type of training results data which will be populated into BDAT: 0 - RMT, 1 - RMT Per Bit, 2 - Margin 2D.
  UINT8             DramDqOdt;                    ///< Controls the usage of the DRAM DQ ODT. 0 - Auto, 1 - Enable, 2 - Disable. See MRC_EN_DIS_AUTO_TYPE.
  BOOLEAN           EnableVrefPwrDn;              ///< Setting this limits VrefGen to be off only during CKEPowerDown
  BOOLEAN           TxEqDis;                      ///< Disable TX Equalization
  UINT32            CpuidModel;                   ///< Unique CPU identifier.
  UINT32            CpuidModelActual;             ///< Actual Unique CPU identifier
  UINT8             CpuidStepping;                ///< Revision of the CPU.
  UINT32            SiPreMemPolicyPpi;
  TrainingModeType  PowerTrainingMode;              ///< 0 - Power Training. 1 - Margin Training.
  UINT16            RcompResistor[MAX_RCOMP];       ///< Reference RCOMP resistors on motherboard
  UINT16            RcompTarget[MAX_RCOMP_TARGETS]; ///< RCOMP target values for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  BOOLEAN           SeparateCkeDelayDdr4;           ///< Boolean switch to control sharing of CKE delays for DDR4 Ranks 0 & 1. @todo: Comment improvement to relate to PDG CKE design.
  MRC_TE_TYPE       TestEngine;                     ///< Defines which hardware test engine is used by this product.
  BOOLEAN           Lp4Npath;                       ///< TRUE if we use LP4 with N-path
  BOOLEAN           LpFreqSwitch;                   ///< Boolean variable to enable or disable frequency switching for supported LPDDR devices.
  BOOLEAN           RdTPbdDis;                      ///< Controls if Read Timing Per-Bit Deskew is disabled.
  BOOLEAN           WrTPbdDis;                      ///< Controls if Write Timing Per-Bit Deskew is disabled.
  BOOLEAN           Mars;                           ///< Controls MARS feature
  BOOLEAN           DqBitDccRerunInWrTPbd;          ///< Controls if DQ Bit DCC is re-run during Write Timing Per-Bit Deskew.  Only applicable if Write Timing Per-Bit Deskew is enabled.
  BOOLEAN           IclA0;                          ///< TRUE for ICL-U/Y A0 stepping
  BOOLEAN           TxtClean;                       ///< TRUE if we require to perform TxtClean
  UINT8             TatDelta;                       ///< Used to increase Turnaround values in Safe mode
  BOOLEAN           LoopBackTest;                   ///< CPGC Loopback test mode
  BOOLEAN           IgnoreCheckPoint;               ///< Ignore OEM checkpoint in MRC call table
  union {
    MRC_FUNCTION    *Func;                          ///< External to MRC function pointers
    UINT64          Data;
  } Call;
  UINT8             CleanMemory;                    ///< TRUE to request a memory clean
  /**
   Sets the serial debug message level\n
     0x00 = Disabled\n
     0x01 = Errors only\n
     0x02 = Errors and Warnings\n
     <b>0x03 = Errors, Warnings, and Info</b>\n
     0x04 = Errors, Warnings, Info, and Events\n
     0x05 = Displays Memory Init Execution Time Summary only\n
  **/
  UINT8           SerialDebugLevel;

  UINT8           PchStepping;

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
Enables IBECC if supported

@param[in] *MrcData - Pointer to the MRC Debug structure.

@retval Returns mrcSuccess if the Ibecc is enabled
**/
MrcStatus
MrcIbecc(
  IN MrcParameters *MrcData
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
  Prepare MRC structures for next MRC Iteraion (SAGV or margin retrain).

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Retrain - Turn on/off UpmPwrRetrainFlag

**/
extern
void
MrcPrepareNextMrcIteration (
  IN OUT MrcParameters *const MrcData,
  IN BOOLEAN                  Retrain
  );

/**
  Initializes the memory controller and DIMMs.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Select  - The post code of the call table entry to execute.
  @param[in, out] CurrentSaGvPoint  - The SaGV point that we want to execute the Select post code  entry or to continue from (relevan if SaGV enabled).
  @param[in]      ExecuteFromSelectPoint  - Execute Memory configuration from (Select,CurrentSaGvPoint) to the end

  @retval mrcSuccess if the initialization succeeded, otherwise an error status indicating the failure.
**/
extern
MrcStatus
MrcStartMemoryConfiguration (
  IN OUT MrcParameters *const MrcData,
  IN     MrcPostCode          Select,
  IN OUT MrcSaGvPoint  *const CurrentSaGvPoint,
  IN BOOLEAN                  ExecuteFromSelectPoint
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

  @retval The current value of the sticky scratchpad register.

  **/
extern
UINT64
MrcWmRegGet (
  IN     MrcParameters *const MrcData
  );

/**
This function Set a newvalue of the sticky scratchpad register by set new givin Bit(s)

@param[in] MrcData  - include all the MRC data.
@param[in] SskpdBit - Bit(s) Need to Set

@retval The current value of the sticky scratchpad register.

**/
void
MrcWmRegSetBits (
  IN    MrcParameters *const MrcData,
  IN    UINT64        SskpdBits
);

/**
This function Set a newvalue of the sticky scratchpad register by clear givin Bit(s)

@param[in] MrcData - include all the MRC data.
@param[in] SskpdBit - Bit(s) Need to Clear

@retval The current value of the sticky scratchpad register.

**/
void
MrcWmRegClrBits (
  IN     MrcParameters *const MrcData,
  IN     UINT64        SskpdBits
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

