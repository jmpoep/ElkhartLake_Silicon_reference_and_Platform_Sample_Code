/** @file
  This file contains the definitions common to the MRC API and other APIs.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

@par Specification
**/
#ifndef _MrcCommonTypes_h_
#define _MrcCommonTypes_h_

#ifndef INT32_MIN
#define INT32_MIN                       (0x80000000)
#endif

#ifndef INT32_MAX
#define INT32_MAX                       (0x7FFFFFFF)
#endif

#ifndef INT16_MIN
#define INT16_MIN                       (0x8000)
#endif

#ifndef INT16_MAX
#define INT16_MAX                       (0x7FFF)
#endif

///
/// System boot mode.
///
#ifndef __MRC_BOOT_MODE__
#define __MRC_BOOT_MODE__                 // The same enum is also defined in MemInfoHob.h - protect from double definition
typedef enum {
  bmCold,                                 ///< Cold boot
  bmWarm,                                 ///< Warm boot
  bmS3,                                   ///< S3 resume
  bmFast,                                 ///< Fast boot
  MrcBootModeMax,                         ///< MRC_BOOT_MODE enumeration maximum value.
  MrcBootModeDelim = INT32_MAX            ///< This value ensures the enum size is consistent on both sides of the PPI.
} MRC_BOOT_MODE;
#endif  //__MRC_BOOT_MODE__

///
/// DIMM memory package
/// This enum matches SPD Module Type - SPD byte 3, bits [3:0]
/// Note that DDR4, and LPDDR have different encoding for some module types
///
typedef enum {
  RDimmMemoryPackage          = 1,
  UDimmMemoryPackage          = 2,
  SoDimmMemoryPackage         = 3,
  LrDimmMemoryPackageDdr4     = 4,
  MiniRDimmMemoryPackage      = 5,
  MiniUDimmMemoryPackage      = 6,
  MiniCDimmMemoryPackage      = 7,
  LpDimmMemoryPackage         = 7,
  SoRDimmEccMemoryPackageDdr4 = 8,
  SoUDimmEccMemoryPackageDdr4 = 9,
  SoCDimmEccMemoryPackage     = 10,
  LrDimmMemoryPackage         = 11,
  SoDimm16bMemoryPackage      = 12,
  SoDimm32bMemoryPackage      = 13,
  NonDimmMemoryPackage        = 14,
  MemoryPackageMax,                       ///< MEMORY_PACKAGE enumeration maximum value.
  MemoryPackageDelim = INT32_MAX          ///< This value ensures the enum size is consistent on both sides of the PPI.
} MEMORY_PACKAGE;

///
/// Memory training I/O levels.
///
typedef enum {
  DdrLevel   = 0,                         ///< Refers to frontside of DIMM.
  LrbufLevel = 1,                         ///< Refers to data level at backside of LRDIMM or AEP buffer.
  RegALevel  = 2,                         ///< Refers to cmd level at backside of register - side A.
  RegBLevel  = 3,                         ///< Refers to cmd level at backside of register - side B.
  HbmLevel   = 4,                         ///< Refers to HBM bus.
  GsmLtMax,                               ///< GSM_LT enumeration maximum value.
  GsmLtDelim = INT32_MAX                  ///< This value ensures the enum size is consistent on both sides of the PPI.
} GSM_LT;

///
/// GetSet Group Types.
///
typedef enum {
  RecEnDelay       = 0,         ///< Linear delay (PI ticks), where the positive increment moves the RCVEN sampling window later in time relative to the RX DQS strobes.
  RxDqsDelay       = 1,         ///< Linear delay (PI ticks), where the positive increment moves the RX DQS strobe later in time relative to the RX DQ signal (i.e. toward the hold side of the eye).
  RxDqDelay        = 2,         ///< Linear delay (PI ticks), where the positive increment moves the RX DQ byte/nibble/bitlane later in time relative to the RX DQS signal (i.e.closing the gap between DQ and DQS in the setup side of the eye).
  RxDqsPDelay      = 3,         ///< Linear delay (PI ticks), where the positive increment moves the RX DQS strobe for "even" chunks later in time relative to the RX DQ signal. Even chunks are 0, 2, 4, 6 within the 0 to 7 chunks of an 8 burst length cacheline, for example.
  RxDqsNDelay      = 4,         ///< Linear delay (PI ticks), where the positive increment moves the RX DQS strobe for "odd" chunks later in time relative to the RX DQ signal. Odd chunks are 1, 3, 5, 7 within the 0 to 7 chunks of an 8 burst length cacheline, for example.
  RxVref           = 5,         ///< Linear increment (Vref ticks), where the positive increment moves the byte/nibble/bitlane RX Vref to a higher voltage.
  RxEq             = 6,         ///< RX CTLE setting indicating a set of possible resistances, capacitance, current steering, etc. values, which may be a different set of values per product. The setting combinations are indexed by integer values.
  RxDqBitDelay     = 7,         ///< Linear delay (PI ticks), where the positive increment moves the RX DQ bitlane later in time relative to the RX DQS signal (i.e.closing the gap between DQ and DQS in the setup side of the eye).
  RxVoc            = 8,         ///< Monotonic increment (Sense Amp setting), where the positive increment moves the byte/nibble/bitlane's effective switching point to a lower Vref value.
  RxOdt            = 9,         ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  RxOdtUp          = 10,        ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  RxOdtDn          = 11,        ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  DramDrvStr       = 12,        ///< Drive strength setting resistance setting within a set of possible resistances (or currents), which may be a different set of values per product. Indexed by integer values.
  McOdtDelay       = 13,        ///<
  McOdtDuration    = 14,        ///<
  SenseAmpDelay    = 15,        ///< This may be used to indicate CmdToDiffAmpEn for SoC's.
  SenseAmpDuration = 16,        ///<
  RoundTripDelay   = 17,        ///< This may be used to indicate CmdToRdDataValid for SoC's.
  RxDqsBitDelay    = 18,        ///< Linear delay (PI ticks), where the positive increment moves the RX DQS within the bitlane later in time relative to the RX DQ signal (i.e.closing the gap between DQ and DQS in the hold side of the eye).
  RxDqDqsDelay     = 19,        ///< Linear delay (PI ticks), where the positive increment moves the RX DQS per strobe later in time relative to the RX DQ signal (i.e. closing the gap between DQS and DQ in the hold side of the eye. The difference between this parameter and RxDqsDelay is that both the DQ and DQS timings may be moved in order to increase the total range of DQDQS timings.
  WrLvlDelay       = 20,        ///< Linear delay (PI ticks), where the positive increment moves both the TX DQS and TX DQ signals later in time relative to all other bus signals.
  TxDqsDelay       = 21,        ///< Linear delay (PI ticks), where the positive increment moves the TX DQS strobe later in time relative to all other bus signals.
  TxDqDelay        = 22,        ///< Linear delay (PI ticks), where the positive increment moves the TX DQ byte/nibble/bitlane later in time relative to all other bus signals.
  TxVref           = 23,        ///< Linear increment (Vref ticks), where the positive increment moves the byte/nibble/bitlane TX Vref to a higher voltage. (Assuming this will abstract away from the range specifics for DDR4, for example.)
  TxEq             = 24,        ///< TX EQ setting indicating a set of possible equalization levels, which may be a different set of values per product. The setting combinations are indexed by integer values.
  TxDqBitDelay     = 25,        ///< Linear delay (PI ticks), where the positive increment moves the TX DQ bitlane later in time relative to all other bus signals.
  TxRon            = 26,        ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  TxRonUp          = 27,        ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  TxRonDn          = 28,        ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  TxSlewRate       = 29,        ///< Monotonic increment, where the positive increment moves the byte/nibble/bitlane's effective slew rate to a higher slope.
  TxImode          = 30,        ///< TX I-Mode Boost setting indicating a set of possible current boost levels, which may be a different set of values per product. The setting combinations are indexed by integer values.
  WrOdt            = 31,        ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  NomOdt           = 32,        ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  ParkOdt          = 33,        ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  TxTco            = 34,        ///< TCO Comp Code for DQ
  TxXtalk          = 35,        ///<
  RxCtleR          = 36,        ///< Rx Equalization Resistance control.
  RxCtleC          = 37,        ///< Rx Equalization Capacitance control.
  RxDqsPBitDelay   = 38,        ///< Linear delay (PI ticks), where the positive increment moves the RX DQS bitlane timing for "even" chunks later in time relative to the RX DQ bitlane signal. Even chunks are 0, 2, 4, 6 within the 0 to 7 chunks of an 8 burst length cacheline, for example.
  RxDqsNBitDelay   = 39,        ///< Linear delay (PI ticks), where the positive increment moves the RX DQS bitlane timing for "odd" chunks later in time relative to the RX DQ bitlane signal. Odd chunks are 1, 3, 5, 7 within the 0 to 7 chunks of an 8 burst length cacheline, for example.
  CmdAll           = 40,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CMD_ALL category later in time relative to all other signals on the bus.
  CmdGrp0          = 41,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CMD_GRP0 category later in time relative to all other signals on the bus.
  CmdGrp1          = 42,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CMD_GRP1 category later in time relative to all other signals on the bus.
  CmdGrp2          = 43,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CMD_GRP2 category later in time relative to all other signals on the bus.
  CtlAll           = 44,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CTL_ALL category later in time relative to all other signals on the bus.
  CtlGrp0          = 45,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CTL_GRP0 category later in time relative to all other signals on the bus.
  CtlGrp1          = 46,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CTL_GRP1 category later in time relative to all other signals on the bus.
  CtlGrp2          = 47,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CTL_GRP2 category later in time relative to all other signals on the bus.
  CtlGrp3          = 48,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CTL_GRP3 category later in time relative to all other signals on the bus.
  CtlGrp4          = 49,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CTL_GRP4 category later in time relative to all other signals on the bus.
  CtlGrp5          = 50,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CTL_GRP5 category later in time relative to all other signals on the bus.
  CmdCtlAll        = 51,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CMD_CTL_ALL category later in time relative to all other signals on the bus.
  CkAll            = 52,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CK_ALL category later in time relative to all other signals on the bus.
  CmdVref          = 53,        ///< Linear increment (Vref ticks), where the positive increment moves the CMD Vref to a higher voltage.
  AlertVref        = 54,        ///< Linear increment (Vref ticks), where the positive increment moves the ALERT Vref to a higher voltage.
  CmdRon           = 55,        ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  CmdGrpPi         = 56,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CMD_GRPx (Specified by Strobe index) category later in time relative to all other signals on the bus.
  CtlGrpPi         = 57,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CTL_GRPx (Specified by Strobe index) category later in time relative to all other signals on the bus.
  ClkGrpPi         = 58,        ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CLK_GRPx (Specified by Strobe index) category later in time relative to all other signals on the bus.
  TxCycleDelay     = 59,        ///< Clock Cycle delay, where the positive increment increases the delay
  EridDelay        = 60,        ///< Linear delay (PI ticks), where the positive increment moves the ERID signals later in time relative to the internal sampling clock (i.e.closing the gap between ERID and internal sampling clock in the setup side of the eye). This group is applicable for DDRT DIMMs.
  EridVref         = 61,        ///< Linear increment (Vref ticks), where the positive increment moves the ERID Vref to a higher voltage. This group is applicable for DDRT DIMMs.
  ErrorVref        = 62,        ///< Linear increment (Vref ticks), where the positive increment moves the ERROR Vref to a higher voltage. This group is applicable for DDRT DIMMs.
  ReqVref          = 63,        ///< Linear increment (Vref ticks), where the positive increment moves the REQ Vref to a higher voltage. This group is applicable for DDRT DIMMs.
  RecEnOffset      = 64,        ///< Linear delay (PI ticks), where the positive increment moves the RCVEN sampling window later in time relative to the RX DQS strobes.
  RxDqsOffset      = 65,        ///< Linear delay (PI ticks), where the positive increment moves the RX DQS strobe later in time relative to the RX DQ signal (i.e. toward the hold side of the eye).
  RxVrefOffset     = 66,        ///< Linear increment (Vref ticks), where the positive increment moves the byte/nibble/bitlane RX Vref to a higher voltage.
  TxDqsOffset      = 67,        ///< Linear delay (PI ticks), where the positive increment moves the TX DQS strobe later in time relative to all other bus signals.
  TxDqOffset       = 68,        ///< Linear delay (PI ticks), where the positive increment moves the TX DQ byte/nibble/bitlane later in time relative to all other bus signals.
  CkeGrpPi,                     ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CKE_GRPx (Specified by Strobe index) category later in time relative to all other signals on the bus.
  RxBiasIComp,                  ///< Controls configuring the current compensation of the receiver.
  RxBiasRComp,                  ///< Controls configuring the resistance compensation of the receiver.
  RxBiasRCompMsb,               ///< Most Significant bit of RxBiasRComp Register Field
  RxBiasRCompLsb,               ///< Least Significant bits of RxBiasRComp Register Field.
  RxDqsAmpOffset,               ///< RX DQS Amplifier Offset Cancelation (Voltage)
  SdllPiCb,                     ///< Sdll_PiCb
  D0PiCb,                       ///< D0_PiCb
  SdllBwCtrl,                   ///< sdll_bw_ctrl
  D0BwCtrl,                     ///< d0_bw_ctrl
  RxDqAmpOffset,                ///< RX DQ Amplifier Offset Cancelation (Voltage).
  RxCben,                       ///< Extra Static Leg load in RX path.
  CompRxCben,                   ///<
  CBEnAmp1,                     ///<
  TxRankMuxDelay,               ///< Tx DQ rank mux delay to account for the I/O setting latching time vs. the drive enable
  TxDqsRankMuxDelay,            ///< Tx DQS rank mux delay to account for the I/O setting latching time vs. the drive enable
  RxRankMuxDelay,               ///< Rx rank mux delay to account for the I/O setting latching time vs. the receive enable
  RxFlybyDelay,                 ///< Per Rank, per Channel value that defines the additive delay on the Receive Enable signal.  (Number of Clocks per step vary by design)
  RxIoTclDelay,                 ///< Per Channel value that defines the additive delay on the Receive Enable signal related to the tCL of the DRAM.  (Number of Clocks per step vary by design)
  RoundTripIoComp,              ///< Per Channel offset between Receive Enable is required and when data is ready to go from DDRIO to MC.
  RxFifoRdEnFlybyDelay,         ///< Per Rank, per Channel offset between Read FIFO read enable is required and when data is ready to go from DDRIO to MC.
  RxFifoRdEnTclDelay,           ///< Per Channel offset between Read FIFO read enable is required and when data is ready to go from DDRIO to MC.
  RxDqDataValidDclkDelay,       ///< Per SubChannel, DCLK delay for DDRIO from Rx FIFO Ready.
  RxDqDataValidQclkDelay,       ///< Per SubChannel, QCLK delay for DDRIO from Rx FIFO Ready.
  TxDqFifoWrEnTcwlDelay,        ///< Per SubChannel, delay for the Write Enable of TX DQ FIFO.
  TxDqFifoRdEnTcwlDelay,        ///<
  TxDqFifoRdEnFlybyDelay,       ///<
  CmdRCompDrvDownOffset,        ///< 2s Complement Cmd offset to pull-down drive strength.
  CmdRCompDrvUpOffset,          ///< 2s Complement Cmd offset to pull-up drive strength.
  CmdSCompOffset,               ///< 2s Complement Cmd offset to slew rate. Positive # decreases slew rate and each step is ~5%
  ClkRCompDrvDownOffset,        ///< 2s Complement Clk offset to pull-down drive strength.
  ClkRCompDrvUpOffset,          ///< 2s Complement Clk offset to pull-up drive strength.
  ClkSCompOffset,               ///< 2s Complement Clk offset to slew rate. Positive # decreases slew rate and each step is ~5%
  CtlRCompDrvDownOffset,        ///< 2s Complement Ctl offset to pull-down drive strength.
  CtlRCompDrvUpOffset,          ///< 2s Complement Ctl offset to pull-up drive strength.
  CtlSCompOffset,               ///< 2s Complement Ctl offset to slew rate. Positive # decreases slew rate and each step is ~5%
  CkeRCompDrvDownOffset,        ///< 2s Complement Cke offset to pull-down drive strength.
  CkeRCompDrvUpOffset,          ///< 2s Complement Cke offset to pull-up drive strength.
  CkeSCompOffset,               ///< 2s Complement Cke offset to slew rate. Positive # decreases slew rate and each step is ~5%
  ClkCompOnTheFlyUpdtEn,        ///< Enable on-the-fly update for CLK COMP bits. if 0, comp will be update only when clk buffer is inactive. if 1, COMP will update any periodic COMP
  CompOffsetAll,                ///< Temporary holder till comps are enumerated.
  CmdSlewRate,                  ///< Monotonic increment, where the positive increment adds more delay cells in the Command delay line.
  ClkSlewRate,                  ///< Monotonic increment, where the positive increment adds more delay cells in the Clock delay line.
  ClkRon,                       ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  CtlSlewRate,                  ///< Monotonic increment, where the positive increment adds more delay cells in the Control delay line.
  CtlRon,                       ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  DqScompPC,                    ///< Phase or Cycle Lock Type for TxSlewRate
  CmdScompPC,                   ///< Phase or Cycle Lock Type for CmdSlewRate
  CtlScompPC,                   ///< Phase or Cycle Lock Type for CtlSlewRate
  ClkScompPC,                   ///< Phase or Cycle Lock Type for ClkSlewRate
  DqRcompStatLegs,              ///<
  SCompCodeDq,                  ///< Slew Comp Code for DQ
  SCompCodeCmd,                 ///< Slew Comp Code for Cmd
  SCompCodeCtl,                 ///< Slew Comp Code for Ctl
  SCompCodeClk,                 ///< Slew Comp Code for Clk
  WrDSCodeUpCmd,                ///< RcompUp Code for Write Drive Strength-Cmd
  WrDSCodeUpCtl,                ///< RcompUp Code for Write Drive Strength-Ctl
  WrDSCodeUpClk,                ///< RcompUp Code for Write Drive Strength-Clk
  WrDSCodeDnCmd,                ///< RcompDown Code for Write Drive Strength-Cmd
  WrDSCodeDnCtl,                ///< RcompDown Code for Write Drive Strength-Ctl
  WrDSCodeDnClk,                ///< RcompDown Code for Write Drive Strength-Clk
  TcoCompCodeCmd,               ///< TCO Comp Code for Cmd
  TcoCompCodeCtl,               ///< TCO Comp Code for Ctl
  TcoCompCodeClk,               ///< TCO Comp Code for Clk
  TxTcoDqsN,                    ///< TCO Comp Code for DQSN
  TxTcoDqsP,                    ///< TCO Comp Code for DQSP
  TxTcoByPass,                  ///< TCO Comp Code for ByPass
  DqOdtVref,
  DqDrvVref,
  CmdDrvVref,
  CmdTxEq,
  CtlDrvVref,
  ClkDrvVref,
  CompRcompOdtUp,               ///< The resistive value of the pull-up block of on die termination
  CompRcompOdtDn,               ///< The resistive value of the pull-dn block of on die termination
  McDqsOdtDelay,                ///< DQS ODT delay
  McDqsOdtDuration,             ///< DQS ODT duration
  DqDfeEnable,
  DqDfeDelayMode,
  DqDfeCoeff,
  DqDfeDelay,

                                ///< -----------------------------------------------------------------
  EndOfPhyMarker,               ///< Marker for end of phy groups
                                ///< -----------------------------------------------------------------
  GsmIocIoReset,                ///< Used to reset the DDR IO.
  GsmIocWlWakeCyc,              ///< Weak Lock Wake.  Specified in QCLK cycles.  Cycle mapping is project dependent.
  GsmIocWlSleepCyc,             ///< Weak Lock Sleep. Specified in QCLK cycles.  Cycle mapping is project dependent.
  GsmIocForceCmpUpdt,
  GsmIocWlLatency,              ///< Weak Lock Latency
  GsmIocLpRcvenCtrl,            ///< Should be 3 on LP4 not 2 as a default
  GsmIocNoDqInterleave,
  GsmIocScramLpMode,            ///< Set the DDRIO to LPDDR4 Mode
  GsmIocScramDdr4Mode,          ///< Set the DDRIO DDRSCRAM to DDR4 Mode
  GsmIocDdrCentric,             ///< Set the DDRIO to DDR-centric mode (DT/Halo)
  GsmIocScramGear1,             ///< Program gear in DDRSCRAM: 1 = Gear1, 0 = Gear2
  GsmIocDisClkGate,
  GsmIocDllWlEn,                ///< DLL Weak Lock Enable.
  GsmIocDisDataIdlClkGate,      ///< Data Idle Clock Gating Disable switch.
  GsmIoc4ChMode,
  GsmIocScramLp4Mode,           ///< Set the DDRIO DDRSCRAM to LPDDR4 Mode
  GsmIocChNotPop,               ///< Channel Not Populated Mask.
  GsmIocDisIosfSbClkGate,
  GsmIocEccEn,                  ///< ECC Enable/Disable for the DDRIO
  GsmIocDataOdtStaticDis,
  GsmIocCompOdtStaticDis,
  GsmIocOdtSampExtEn,
  GsmIocDqsOdtSampExtEn,
  GsmIocLpEarlyRLeak,
  GsmIocDllMask,
  GsmIocStrongWeakLeaker,
  GsmIocStrongWeakLeakerMsb,
  GsmIocRcvenFourCycleFill,
  GsmIocEnRcvenPreZeroFill,
  GsmIocLpLongOdtEn,
  GsmIocDataVddqOdtEn,
  GsmIocDataVttOdtEn,
  GsmIocCompVddqOdtEn,
  GsmIocCompVttOdtEn,
  GsmIocCmdDrvVref200ohm,
  GsmIocVttPanicCompUpMult,
  GsmIocVttPanicCompDnMult,
  GsmIocRxDeskewDis,
  GsmIocTxDeskewDis,
  GsmIocVrefPwrDnEn,
  GsmIocRxVrefMFC,              ///< RX Vref Metal Finger Cap.
  GsmIocRxStaggerCtl,
  GsmIocRxDeskewCal,
  GsmIocTxDeskewCal,
  GsmIocVssOdtEn,
  GsmIocGlobalClkEn,
  GsmIocRxTypeSelect,
  GsmIocLeakerComp,
  GsmIocLeakerWithTxAnalogEn,
  GsmIocStrong2WeakOnDqsOdt,
  GsmIocForceDqsOnQuickOdtOff,
  GsmIocLongWrPreambleLp4,      ///< 2tCK Write Preamble for LPDDR4
  GsmIocRxBiasSel,              ///< Controls if GsmIocRxBiasRcomp is used for Receiver Bias.
  GsmIocForceRxAmpOn,
  GsmIocForceBiasOn,
  GsmIocTxOn,
  GsmIocSenseAmpMode,
  GsmIocReadLevelMode,
  GsmIocXoverMinDelayCtl,
  GsmIocWriteLevelMode,
  GsmIocReadDqDqsMode,
  GsmIocDataCtlLpMode,          ///< Sets DDRIO Data to LPDDR4 Mode.
  GsmIocDataCtlLp4Mode,         ///< Sets DDRIO Data to LPDDR4 Mode.
  GsmIocDataCtlDdr4Mode,        ///< Sets DDRIO Data to DDR4 Mode.
  GsmIocRxClkStg,               ///< Number of clock cycles to keep clock on in the RX datapath from the fall of RcvEn signal.
  GsmIocRxClkStgNumMsb,         ///< Additional bit for GsmIocRxClkStg.
  GsmIocForceOdtOn,
  GsmIocRxPiPwrDnDis,
  GsmIocTxPiPwrDnDis,
  GsmIocTxDisable,              ///< Ignore Write commands for this data byte
  GsmIocTxVrefConverge,
  GsmIocCmdVrefConverge,
  GsmIocCompClkOn,
  GsmIocConstZTxEqEn,
  GsmIocCompVccddqLo,
  GsmIocDisableQuickComp,
  GsmIocSinStep,
  GsmIocSinStepAdv,
  GsmIocSdllSegmentDisable,
  GsmIocDllWeakLock,
  GsmIocTxEqDis,
  GsmIocDqSlewDlyByPass,
  GsmIocWlLongDelEn,
  GsmIocDqOdtUpDnOff,
  GsmIocFixOdtD,
  GsmIocPanicDrvUpVref,
  GsmIocOdtOverride,                ///< Override enable
  GsmIocOdtOn,                      ///< Override value
  GsmIocMprTrainDdrOn,
  GsmIocCkeOverride,                ///< Override enable
  GsmIocCkeOn,                      ///< Override value
  GsmIocRptChRepClkOn,              ///< Forces the RPTCH clock on.
  GsmIocCmdAnlgEnGraceCnt,          ///< Grace counter for extending CmdAnalogEn counter.
  GsmIocTxAnlgEnGraceCnt,           ///< Grace conter for extending the TxAnalogEn counter.
  GsmIocTxDqFifoRdEnPerRankDelDis,  ///< Disables the Per Rank delay on TxDq Fifo.
  GsmIocLowSupEnDqDqs,              ///< DQ Low Supply Enable
  GsmIocInternalClocksOn,           ///< Force on all the PI enables
  GsmIocLp4DqsMaskPulseCnt,         ///< Controls the number of masked DQS pulses sent by the DDR IO during CMD VREF update in LP4 CBT
  GsmIocLp4ForceDqsPOn,             ///< Force DQS P pulled low,  unless transmitting, receiving or in leaker mode
  GsmIocLp4ForceDqsNOn,             ///< Force DQS N pulled high, unless transmitting, receiving or in leaker mode
  GsmIocLp4ForceDqsPOnWithLeaker,   ///< Use leaker solution for DQS P Park mode
  GsmIocLp4ForceDqsNOnWithLeaker,   ///< Use leaker solution for DQS N Park mode
  GsmIocLp4DqsPulseCnt,             ///< Controls the number of unmasked DQS pulses sent by the DDR IO during CMD VREF update in LP4 CBT
  GsmIocLp4DqsPulseEn,              ///< Enables the DDR IO to toggle DQS to latch CMD VREF to the DRAM during LP4 CBT.
  GsmIocLp4DqOverrideData,          ///< DQ value override to latch CMD VREF to the DRAM during LP4 CBT.
  GsmIocLp4DqOverrideEn,            ///< Enables the DDR IO to force static DQ value to latch CMD VREF to the DRAM during LP4 CBT.
  GsmIocRankOverrideEn,             ///< Configures the DDRIO to override the delay values used for the target rank.
  GsmIocRankOverrideVal,            ///< Specified which rank to pull the delay values from.
  GsmIocDataCtlGear1,               ///< Program gear in DDRDATA: 1 = Gear1, 0 = Gear2
  GsmIocDccTrainingMode,
  GsmIocDccTrainingDone,
  GsmIocDccDrain,
  GsmIocDccActiveClks,
  GsmIocDccActiveBytes,
  GsmIocDccDcoCompEn,
  GsmIocDccPeriodicDis,
  GsmIocDccDcoLfsrDis,
  GsmIocDccClkTrainVal,
  GsmIocDccDataTrainDqsVal,
  GsmIocDccDqsReplica,
  GsmIocDccAipCb,
  GsmIocDccAipCbDqs,
                                    ///< -----------------------------------------------------------------
  EndOfIocMarker,                   ///< End of IO Config Marker
                                    ///< -----------------------------------------------------------------
  GsmMctRP,
  GsmMctRPabExt,
  GsmMctRAS,
  GsmMctRDPRE,
  GsmMctPPD,
  GsmMctWRPRE,
  GsmMctFAW,
  GsmMctRRDsg,
  GsmMctRRDdg,
  GsmMctLpDeratingExt,
  GsmMctRDRDsg,
  GsmMctRDRDdg,
  GsmMctRDRDdr,
  GsmMctRDRDdd,
  GsmMctRDWRsg,
  GsmMctRDWRdg,
  GsmMctRDWRdr,
  GsmMctRDWRdd,
  GsmMctWRRDsg,
  GsmMctWRRDdg,
  GsmMctWRRDdr,
  GsmMctWRRDdd,
  GsmMctWRWRsg,
  GsmMctWRWRdg,
  GsmMctWRWRdr,
  GsmMctWRWRdd,
  GsmMctCKE,
  GsmMctXP,
  GsmMctXPDLL,
  GsmMctPRPDEN,
  GsmMctRDPDEN,
  GsmMctWRPDEN,
  GsmMctOdtRdDuration,
  GsmMctOdtRdDelay,
  GsmMctOdtWrDuration,
  GsmMctOdtWrDelay,
  GsmMctWrEarlyOdt,
  GsmMctCL,
  GsmMctCWL,
  GsmMctAONPD,
  GsmMctCWLAdd,
  GsmMctCWLDec,
  GsmMctXSDLL,
  GsmMctXSR,                    ///< Self Refresh exit to commands not requiring a locked DLL (tXS) in DDR4(For SKL, this maps to the tXS_offset) or Self Refresh exit to next valid command delay (tXSR) in LPDDR4.
  GsmMctZQOPER,
  GsmMctMOD,                    ///< Mode Register Set command to next valid command delay.
  GsmMctSrIdle,                 ///< The number of cycles with no transactions in order to enter Self Refresh.
  GsmMctREFI,                   ///< Delay from Start of Refresh to next ACT or Refresh.
  GsmMctRFC,                    ///< Time of refresh.
  GsmMctOrefRi,                 ///< This defines how long the Rank must be idle to do a Opportunistic Refresh.
  GsmMctRefreshHpWm,            ///< tREFI count level that turns refresh priority to high.
  GsmMctRefreshPanicWm,         ///< tREFI count level for panic priority.
  GsmMctREFIx9,                 ///< Max time between refreshes per rank.
  GsmMctZQCSPeriod,
  GsmMctZQCS,
  GsmMctZQCAL,
  GsmMctCPDED,                  ///< Defines the delay required from power down before the command bus can be tri-stated.
  GsmMctCAL,                    ///<
  GsmMctCKCKEH,                 ///< Defines the number of cycles CS must be driven low before asserting CKE for power down exit.
  GsmMctCSCKEH,                 ///< Defines the number of valid clock cycles before asserting CKE for power down exit.
  GsmMctRCDwr,                  ///< Define the number of DCLKs required to wait from a Row Address (RAS) to Write (For DDR4-E).  Should be the same value as tRP (tRCD) for DDR4/LP3/LP4.
  GsmMctRFCpb,                  ///< Refresh cycle time per bank in DCLKS. How long the per bank refresh command takes to complete.
                                ///< -----------------------------------------------------------------
  EndOfMctMarker,               ///< Marks the end of the MC Timing Group.
                                ///< -----------------------------------------------------------------
  GsmMccDramType,               ///< Defines what DRAM technology is being used.
  GsmMccCmdStretch,             ///< Defines the Mode of Command Stretch.
  GsmMccCmdGapRatio,            ///< When using N:1 Command Stretch Mode, this field defines how many back-to-back commands are allowed before a gap is required
  GsmMccAddrMirror,             ///< This field is used to inform the MC which DIMMs are mirrored.
  GsmMccCmdTriStateDis,         ///< Disable Command bus tri-state
  GsmMccCmdTriStateDisTrain,    ///< Disable Command bus tri-state during CADB training
  GsmMccFreqPoint,              ///< Defines the current frequency point the MC is in during training.
  GsmMccEnableOdtMatrix,        ///< Enables custom mapping of ODT assertion on Ranks.
  GsmMccX8Device,
  GsmMccGear2,                  ///< Program gear in MC: 0 = Gear1, 1 = Gear2
  GsmMccDdr4OneDpc,             ///< ddr4_1dpc performance feature
  GsmMccLDimmMap,
  GsmMccRankInterleave,
  GsmMccEnhancedInterleave,
  GsmMccEccMode,
  GsmMccAddrDecodeDdrType,
  GsmMccEnhChannelMode,         ///< Enables Enhanced Channel Mode (32-bit channels, also called sub-channels)
  GsmMccStackedMode,
  GsmMccStackChMap,
  GsmMccLChannelMap,
  GsmMccSChannelSize,
  GsmMccStackedChHash,
  GsmMccLDimmSize,              ///< Defines the L DIMM size in mutiples of X which may vary from project to project.
  GsmMccLDimmDramWidth,         ///< This field defines the L DIMM device width: x4, x8, x16, x32, x64
  GsmMccLDimmRankCnt,
  GsmMccLDimm8Gb,               ///< This field is used to inform the Memory Controller that the L DIMM is a DDR3 using 8Gb DRAMS. (This may be depracated after CNL.)
  GsmMccSDimmSize,              ///< Defines the S DIMM size in mutiples of X which may vary from project to project.
  GsmMccSDimmDramWidth,         ///< This field defines the S DIMM device width: x4, x8, x16, x32, x64
  GsmMccSDimmRankCnt,
  GsmMccSDimm8Gb,               ///< This field is used to inform the Memory Controller that the L DIMM is a DDR3 using 8Gb DRAMS. (This may be depracated after CNL.)
  GsmMccPuMrcDone,
  GsmMccDdrReset,
  GsmMccEnableRefresh,
  GsmMccEnableSr,               ///< This field is used to enable or disable the Self Refresh feature.
  GsmMccMcInitDoneAck,
  GsmMccMrcDone,
  GsmMccSafeSr,
  GsmMccSaveFreqPoint,          ///< This field communicates with the MC to save the specified frequency point.  Used with FreqIndex in GetSet.
  GsmMccEnableDclk,
  GsmMccPureSrx,                ///< Tell MC to only exit Self Refresh.  Blocks other maintenance FSMs: ZQ, Temp, DQS Oscillator.
  GsmMccLp4FifoRdWr,
  GsmMccIgnoreCke,
  GsmMccMaskCs,
  GsmMccCpgcInOrder,
  GsmMccCadbEnable,
  GsmMccDeselectEnable,
  GsmMccBusRetainOnBubble,      ///< Set this bit to make sure that when CADB can send deselect cycles and N:1 is enabled that CA bus (and CA valid) will be frozen on a cycle where a bubble is enforced.
  GsmMccLpddr2nCsMrw,
  GsmMccBlockXarb,
  GsmMccResetOnCmd,
  GsmMccResetDelay,
  GsmMccRankOccupancy,
  GsmMccMcSrx,
  GsmMccRefInterval,            ///< Refresh Interval period in DCLKS.
  GsmMccRefStaggerEn,           ///< Enables refresh staggering.
  GsmMccRefStaggerMode,         ///< 0 = per DIMM, 1 = per channel.
  GsmMccDisableStolenRefresh,   ///< Disable stolen refresh.
  GsmMccEnRefTypeDisplay,       ///< Displays refresh type on BA address pins.
  GsmMccHashMask,               ///< Bits set for channel XOR function.
  GsmMccLsbMaskBit,             ///< MC channel interleave bit.
  GsmMccHashMode,               ///< Use A6 for channel select or other fields in this register.
  GsmMccMr2Shadow,              ///< Shadow of bits 13:0 in MR2.
  GsmMccSrtAvail,               ///< SRT mode for DDR3.  Bit 14 DIMM0, Bit 15 DIMM1.
  GsmMccDisableCkTristate,      ///< Boolean control to enable/disable Clock Tristating during CKE low.
  GsmMccPbrDis,                 ///< Boolean control for Per Bank Refresh.  1 = Disable, 0 = Enable.
                                ///< -----------------------------------------------------------------
  EndOfMccMarker,               ///< End of MC Configuration Group.
                                ///< -----------------------------------------------------------------
  GsmComplexRcvEn,
  GsmComplexRxBias,             ///< Combines the control of RxBiasRComp and RxBiasIComp into one linear field.
  GsmGtMax,                     ///< GSM_GT enumeration maximum value.
  GsmGtDelim = INT32_MAX        ///< This value ensures the enum size is consistent on both sides of the PPI.
} GSM_GT;

typedef enum {
  SigRasN   = 0,
  SigCasN   = 1,
  SigWeN    = 2,
  SigBa0    = 3,
  SigBa1    = 4,
  SigBa2    = 5,
  SigA0     = 6,
  SigA1     = 7,
  SigA2     = 8,
  SigA3     = 9,
  SigA4     = 10,
  SigA5     = 11,
  SigA6     = 12,
  SigA7     = 13,
  SigA8     = 14,
  SigA9     = 15,
  SigA10    = 16,
  SigA11    = 17,
  SigA12    = 18,
  SigA13    = 19,
  SigA14    = 20,
  SigA15    = 21,
  SigA16    = 22,
  SigA17    = 23,
  SigCs0N   = 24,
  SigCs1N   = 25,
  SigCs2N   = 26,
  SigCs3N   = 27,
  SigCs4N   = 28,
  SigCs5N   = 29,
  SigCs6N   = 30,
  SigCs7N   = 31,
  SigCs8N   = 32,
  SigCs9N   = 33,
  SigCke0   = 34,
  SigCke1   = 35,
  SigCke2   = 36,
  SigCke3   = 37,
  SigCke4   = 38,
  SigCke5   = 39,
  SigOdt0   = 40,     //could also be used for CA-ODT for LP4
  SigOdt1   = 41,     //could also be used for CA-ODT for LP4
  SigOdt2   = 42,
  SigOdt3   = 43,
  SigOdt4   = 44,
  SigOdt5   = 45,
  SigPar    = 46,
  SigAlertN = 47,
  SigBg0    = 48,
  SigBg1    = 49,
  SigActN   = 50,
  SigCid0   = 51,
  SigCid1   = 52,
  SigCid2   = 53,
  SigCk0    = 54,
  SigCk1    = 55,
  SigCk2    = 56,
  SigCk3    = 57,
  SigCk4    = 58,
  SigCk5    = 59,
  SigGnt0   = 60,
  SigGnt1   = 61,
  SigErid00 = 62,
  SigErid01 = 63,
  SigErid10 = 64,
  SigErid11 = 65,
  SigErr0   = 66,
  SigErr1   = 67,
  SigCa00   = 68,    // First instantiation of the CA bus for a given channel
  SigCa01   = 69,
  SigCa02   = 70,
  SigCa03   = 71,
  SigCa04   = 72,
  SigCa05   = 73,
  SigCa10   = 74,    // Second instantiation of the CA bus for a given channel
  SigCa11   = 75,
  SigCa12   = 76,
  SigCa13   = 77,
  SigCa14   = 78,
  SigCa15   = 79,
  SigCa06,
  SigCa07,
  SigCa08,
  SigCa09,
  SigCa16,
  SigCa17,
  SigCa18,
  SigCa19,
  GsmCsnMax,
  GsmCsnDelim = INT32_MAX
} GSM_CSN;
#endif // _MrcCommonTypes_h_

