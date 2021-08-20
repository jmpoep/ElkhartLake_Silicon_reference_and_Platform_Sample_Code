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

#ifndef MRC_INT32_MIN
#define MRC_INT32_MIN                       (0x80000000)
#endif

#ifndef MRC_INT32_MAX
#define MRC_INT32_MAX                       (0x7FFFFFFF)
#endif

#ifndef MRC_INT16_MIN
#define MRC_INT16_MIN                       (0x8000)
#endif

#ifndef MRC_INT16_MAX
#define MRC_INT16_MAX                       (0x7FFF)
#endif

#ifndef MRC_INT8_MIN
#define MRC_INT8_MIN                       (0x80)
#endif

///
/// System boot mode.
///
#ifndef __MRC_BOOT_MODE__
#define __MRC_BOOT_MODE__                 //These values are cloned to MemInfoHob.h manually
typedef enum {
  bmCold,                                 ///< Cold boot
  bmWarm,                                 ///< Warm boot
  bmS3,                                   ///< S3 resume
  bmFast,                                 ///< Fast boot
  MrcBootModeMax,                         ///< MRC_BOOT_MODE enumeration maximum value.
  MrcBootModeDelim = MRC_INT32_MAX            ///< This value ensures the enum size is consistent on both sides of the PPI.
} MRC_BOOT_MODE;
#endif  //__MRC_BOOT_MODE__

///
/// DIMM memory package
/// This enum matches SPD Module Type - SPD byte 3, bits [3:0]
/// Note that DDR3, DDR4, and LPDDR have different encoding for some module types
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
  MemoryPackageDelim = MRC_INT32_MAX          ///< This value ensures the enum size is consistent on both sides of the PPI.
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
  GsmLtDelim = MRC_INT32_MAX                  ///< This value ensures the enum size is consistent on both sides of the PPI.
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
  McOdtDelay       = 13,        ///< Dq Odt Control
  McOdtDuration    = 14,        ///< Dq Odt Control
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
  RxDqBitOffset    = 69,        ///< Linear delay (PI ticks), read timing offset between Strobe P/N per lane t for bit[x] of the DQ byte
  CkeGrpPi,                     ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the CKE_GRPx (Specified by Strobe index) category later in time relative to all other signals on the bus.
  WckGrpPi,                     ///< Linear delay (PI ticks), where the positive increment moves all signals assigned to the WCK_GRPx (Specified by Strobe index) category later in time relative to all other signals on the bus.
  DqsOdtDelay,                  ///< Dqs ODT Control
  DqsOdtDuration,               ///< Dqs ODT Control
  RxBiasCtl,                    ///< Control Bias current DAC which determines 1st and 2nd stage amp current.  Iref = 14% * BiasIrefAdj[3:0] where default is (0xA, 0x7) for NPath & PPath.
  RxDqsAmpOffset,               ///< RX DQS Amplifier Offset Cancellation (Voltage)
  RxDqsUnmatchedAmpOffset,      ///< RX DQS Amplifier Offset Cancellation for the unmatched path (Voltage)
  RxCben,                       ///< PI CB enable settings
  TxRankMuxDelay,               ///< Tx rank mux delay to account for the I/O setting latching time vs. the drive enable
  TxDqsRankMuxDelay,            ///< Tx rank mux delay for DQS to account for the I/O setting latching time vs. the drive enable
  RxRankMuxDelay,               ///< Rx rank mux delay to account for the I/O setting latching time vs. the receive enable
  RxFlybyDelay,                 ///< Per Rank, per Channel value that defines the additive delay on the Receive Enable signal.  (Number of Clocks per step vary by design)
  RxIoTclDelay,                 ///< Per Channel value that defines the additive delay on the Receive Enable signal related to the tCL of the DRAM.  (Number of Clocks per step vary by design) ?CH_SUB
  RoundTripIoComp,              ///< Per Channel offset between Receive Enable is required and when data is ready to go from DDRIO to MC.
  RxFifoRdEnFlybyDelay,         ///< Per Rank, per Channel offset between Read FIFO read enable is required and when data is ready to go from DDRIO to MC. ?CH_SUB
  RxFifoRdEnTclDelay,           ///< Per Channel offset between Read FIFO read enable is required and when data is ready to go from DDRIO to MC. ?CH_SUB
  RxDqDataValidDclkDelay,       ///< Per SubChannel, DCLK delay for DDRIO from Rx FIFO Ready. ?CH_SUB
  RxDqDataValidQclkDelay,       ///< Per SubChannel, QCLK delay for DDRIO from Rx FIFO Ready. ?CH_SUB
  TxDqFifoWrEnTcwlDelay,        ///< Per SubChannel, delay for the Write Enable of TX DQ FIFO. ?CH_SUB
  TxDqFifoRdEnTcwlDelay,        ///< ?CH_SUB
  TxDqFifoRdEnFlybyDelay,       ///< ?CH_SUB
  TxDqsTco,                     ///< Provides an unsigned delay control to DqsP-Fall / DqsN-Rise TcoDelay.  Lower values slows down rise delay and higher values slow down fall delay.
  CmdTxEq,                      ///< CA Equalization codes: {4} Controls ConstantZ (1) vs. NonConstantZ (0), {3:0}={0: 0 Static Legs / 12 Eq Legs, ... 12: 12 Static Legs / 0 Eq Legs, 13-15: rsvd}
  CtlTxEq,                      ///< CTL Equalization codes: {4} Controls ConstantZ (1) vs. NonConstantZ (0), {3:0}={0: 0 Static Legs / 12 Eq Legs, ... 12: 12 Static Legs / 0 Eq Legs, 13-15: rsvd}
  RxVrefVttDecap,               ///< Control Rx Vref coupling to VTT.  0: No cap to VTT  1-7 is cap control with 12.5% step size. Remaining cap will be to VSS
  RxVrefVddqDecap,              ///< Control Rx Vref coupling to Vddq.  0: No cap to Vddq  1-7 is cap control with 12.5% step size. Remaining cap will be to VSS
  PanicVttDnLp,                 ///< Multiplier to the Vtt Panic Comp Dn Level LPDDR Read code to expand to 8 bits with resolution of 0.5 LSB. Range 0 to 7.5. Final output is 1x LSB
  VttGenStatusSelCount,         ///< Select which comparator is counted. 0:panichi0 1:panichi1 2:paniclo0 3:paniclo1 4:spare 5:(panichi0-paniclo0 6-7:rsvd
  VttGenStatusCount,            ///< 16 bit signed, saturating counter that counts the comparator output. Do not used when the comp FSM is active.
  RxR,                          ///< Matched : 3:2 CTRE Res Control
  RxC,                          ///< Matched : 1:0 CTLE Cap control
  RxTap0,                       ///< Unmatched : 3:0 Tap 0 Coeffecient control(unsigned voltage with step size ~5mv),
  RxTap1,                       ///< Unmatched : 7:4 Tap 1 Coeffecient Control(signed with step size ~5mv)
  RloadDqsDn,                   ///< Sets the strength of the Rload pulldown for the RxDqs P-Path umatched receiver and RxBias Current generation
  DataRxD0PiCb,                 ///< PICB control for slave rxdqd0 block.  Can match SDLLPICb or use 0 for best bandwidth.
  DataSDllPiCb,                 ///< PICB control for slave DLL. Higher value means more cap/slower slopes into PI.  Should match value in CBTune1.
  VccDllRxD0PiCb,               ///< PICB control for slave rxdqd0 block.  Can match SDLLPICb or use 0 for best bandwidth
  VccDllSDllPiCb,               ///< PICB control for slave DLL.  Higher value means more cap/slower slopes into PI.  Should match value in CBTune1.
  DqsOdtCompOffset,             ///< Offset for DQS OdtUp & OdtDn, decoupled from DQ ODT values for better power control in the system
  CmdRCompDrvDownOffset,        ///< 2s Complement Cmd offset to pull-down drive strength. ?CH_SUB
  CmdRCompDrvUpOffset,          ///< 2s Complement Cmd offset to pull-up drive strength. ?CH_SUB
  CmdSCompOffset,               ///< 2s Complement Cmd offset to slew rate. Positive # decreases slew rate and each step is ~5% ?CH_SUB
  ClkRCompDrvDownOffset,        ///< 2s Complement Clk offset to pull-down drive strength. ?CH_SUB
  ClkRCompDrvUpOffset,          ///< 2s Complement Clk offset to pull-up drive strength. ?CH_SUB
  ClkSCompOffset,               ///< 2s Complement Clk offset to slew rate. Positive # decreases slew rate and each step is ~5% ?CH_SUB
  CtlRCompDrvDownOffset,        ///< 2s Complement Ctl offset to pull-down drive strength. ?CH_SUB
  CtlRCompDrvUpOffset,          ///< 2s Complement Ctl offset to pull-up drive strength. ?CH_SUB
  CtlSCompOffset,               ///< 2s Complement Ctl offset to slew rate. Positive # decreases slew rate and each step is ~5% ?CH_SUB
  CkeRCompDrvDownOffset,        ///< 2s Complement Cke offset to pull-down drive strength. ?CH_SUB
  CkeRCompDrvUpOffset,          ///< 2s Complement Cke offset to pull-up drive strength. ?CH_SUB
  CkeSCompOffset,               ///< 2s Complement Cke offset to slew rate. Positive # decreases slew rate and each step is ~5% ?CH_SUB
  CompOffsetVssHiFF,            ///< 2s Complement VssHi Feedforward Comp Offset
  CompOffsetAll,                ///< Temporary holder till comps are enumerated.
  VsxHiClkFFOffset,             ///< 2s Complement VsxHi Clk FeedForward Offset
  VsxHiCaFFOffset,              ///< 2s Complement VsxHi Ca FeedForward Offset
  VsxHiCtlFFOffset,             ///< 2s Complement VsxHi Ctl FeedForward Offset
  CmdSlewRate,                  ///< Monotonic increment, where the positive increment adds more delay cells in the Command delay line.
  ClkSlewRate,                  ///< Monotonic increment, where the positive increment adds more delay cells in the Clock delay line.
  ClkRon,                       ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  CtlSlewRate,                  ///< Monotonic increment, where the positive increment adds more delay cells in the Control delay line.
  CtlRon,                       ///< Resistance setting within a set of possible resistances, which may be a different set of values per product. Indexed by integer values.
  DqScompPC,                     ///< Phase or Cycle Lock Type for TxSlewRate
  CmdScompPC,                   ///< Phase or Cycle Lock Type for CmdSlewRate
  CtlScompPC,                   ///< Phase or Cycle Lock Type for CtlSlewRate
  ClkScompPC,                   ///< Phase or Cycle Lock Type for ClkSlewRate
  SCompCodeDq,                  ///< Slew Comp Code for DQ
  SCompCodeCmd,                 ///< Slew Comp Code for Cmd
  SCompCodeCtl,                 ///< Slew Comp Code for Ctl
  SCompCodeClk,                 ///< Slew Comp Code for Clk
  SCompBypassDq,                ///< Bypass DQ Slew delay
  SCompBypassCmd,               ///< Bypass CA Slew delay
  SCompBypassCtl,               ///< Bypass Ctl Slew delay
  SCompBypassClk,               ///< Bypass Clk Slew delay
  WrDSCodeUpCmd,                ///< RcompUp Code for Write Drive Strength-Cmd
  WrDSCodeUpCtl,                ///< RcompUp Code for Write Drive Strength-Ctl
  WrDSCodeUpClk,                ///< RcompUp Code for Write Drive Strength-Clk
  WrDSCodeDnCmd,                ///< RcompDown Code for Write Drive Strength-Cmd
  WrDSCodeDnCtl,                ///< RcompDown Code for Write Drive Strength-Ctl
  WrDSCodeDnClk,                ///< RcompDown Code for Write Drive Strength-Clk
  TcoCompCodeCmd,               ///< TCO Comp Code for Cmd
  TcoCompCodeCtl,               ///< TCO Comp Code for Ctl
  TcoCompCodeClk,               ///< TCO Comp Code for Clk
  DqOdtVrefUp,
  DqOdtVrefDn,
  DqDrvVrefUp,
  DqDrvVrefDn,
  CmdDrvVrefUp,
  CmdDrvVrefDn,
  CtlDrvVrefUp,
  CtlDrvVrefDn,
  ClkDrvVrefUp,
  ClkDrvVrefDn,
  CompRcompOdtUp,               ///< The resistive value of the pull-up block of on die termination
  CompRcompOdtDn,               ///< The resistive value of the pull-dn block of on die termination
  TxDqsBitDelay,                ///< Linear delay (PI ticks), where the positive increment moves the TX DQS bitlane later in time relative to all other bus signals.
  RxVocUnmatched,
  RxPerBitDeskewCal,            ///< Step size of RxPerBit (Byte granularity)
  TxPerBitDeskewCal,            ///< Step size of TxPerBit (Byte granularity)
  CccPerBitDeskewCal,           ///< Step size of CCCPerBit (Byte granularity)
  EndOfPhyMarker,               ///< Marker for end of phy groups.
  GsmIocIoReset,                ///< Used to reset the DDR IO.
  GsmIocWlWakeCyc,              ///< Weak Lock Wake.  Specified in QCLK cycles.  Cycle mapping is project dependent.
  GsmIocWlSleepCyclesAct,       ///< Weak Lock Sleep. Specified in QCLK cycles.  Cycle mapping is project dependent.
  GsmIocWlSleepCyclesLp,        ///< Weak Lock Sleep. Specified in QCLK cycles.  Cycle mapping is project dependent.
  GsmIocForceCmpUpdt,
  GsmIocNoDqInterleave,
  GsmIocScramLpMode,            ///< Set the DDRIO DDRSCRAM to LPDDR4 Mode
  GsmIocScramDdr4Mode,          ///< Set the DDRIO DDRSCRAM to DDR4 Mode
  GsmIocScramDdr5Mode,          ///< Set the DDRIO DDRSCRAM to DDR5 Mode
  GsmIocScramGear1,             ///< Program gear in DDRSCRAM: 1 = Gear1, 0 = Gear2
  GsmIocVccDllGear1,            ///< Program gear in VccDllDqsDelay.Gear1
  GsmIocVccDllControlBypass_V,           ///< Disable VccDll[0/1] regulator and short the output to VccIoG
  GsmIocVccDllControlSelCode_V,
  GsmIocVccDllControlTarget_V,
  GsmIocVccDllControlOpenLoop_V,
  GsmIocVsxHiControlSelCode_V,
  GsmIocVsxHiControlOpenLoop_V,
  GsmIocCccPiEn,
  GsmIocCccPiEnOverride,
  GsmIocDisClkGate,
  GsmIocDisDataIdlClkGate,      ///< Data Idle Clock Gating Disable switch.
  GsmIocScramLp4Mode,           ///< Set the DDRIO DDRSCRAM to LPDDR4 Mode
  GsmIocScramLp5Mode,           ///< Set the DDRIO DDRSCRAM to LPDDR5 Mode
  GsmIocScramOvrdPeriodicToDvfsComp, ///<Converts PM8 Comp requests to PM9 DFVS Comp
  GsmIocLp5Wck2CkRatio,
  GsmIocChNotPop,               ///< Channel Not Populated Mask.
  GsmIocDisIosfSbClkGate,
  GsmIocEccEn,                  ///< ECC Enable/Disable for the DDRIO ?
  GsmIocDataOdtStaticDis,
  GsmIocCompOdtStaticDis,
  GsmIocStrobeOdtStaticDis,     ///< 2 bits to control ddrxover cell for mindelay margin improvment [0]: q2q0_sel - controls margin from Qclk to Q0clk[1]: q02pi_sel - controls margin from Q0clk to PIclk
  GsmIocDataODTSingleSegEn,     ///< ODT enables (0: 2 segment, 1: 1 segment) of the 2 DQ Driver segments.  CR is independent of Control0.OdtMode.
  GsmIocDllMask,
  GsmIocDataOdtMode,
  GsmIocDataDqOdtParkMode,
  GsmIocCompVttOdtEn,
  GsmIocCmdDrvVref200ohm,
  GsmIocVttPanicCompUpMult,
  GsmIocVttPanicCompDnMult,
  GsmIocRxVrefMFC,              ///< RX Vref Metal Finger Cap. ?Vtt vs Vddq
  GsmIocVccDllRxDeskewCal,      ///< Step size of overall Rx instances
  GsmIocVccDllTxDeskewCal,      ///< Step size of overall Tx instances
  GsmIocVccDllCccDeskewCal,     ///< Step size of overall CCC instances
  GsmIocForceRxAmpOn,
  GsmIocTxOn,
  GsmIocRxDisable,
  GsmIocSenseAmpMode,
  GsmIocCaTrainingMode,
  GsmIocReadLevelMode,
  GsmIocWriteLevelMode,
  GsmIocReadDqDqsMode,
  GsmIocRxClkStg,               ///< Number of clock cycles to keep clock on in the RX datapath from the fall of RcvEn signal.
  GsmIocDataRxBurstLen,         ///< Configures the burst length of Read at the data partition.
  GsmIocEnDqsNRcvEn,
  GsmIocForceOdtOn,
  GsmIocRxPiPwrDnDis,
  GsmIocTxPiPwrDnDis,
  GsmIocTxDisable,              ///< Ignore Write commands for this data byte
  GsmIocCmdVrefConverge,
  GsmIocCompClkOn,
  GsmIocConstZTxEqEn,
  GsmIocDisableQuickComp,
  GsmIocSinStep,
  GsmIocSinStepAdv,
  GsmIocSdllSegmentDisable,
  GsmIocRXDeskewForceOn,                  ///< Disable all power down modes in Rx Per Bit Deskew
  GsmIocDllWeakLock,
  GsmIocDllWeakLock1,
  GsmIocTxEqDis,
  GsmIocDqSlewDlyByPass,
  GsmIocWlLongDelEn,
  GsmIocCompVddqOdtEn,              ///< Byte ODT mode: 0 Vss, 1:Vddq, 2:Vtt
  GsmIocRptChRepClkOn,              ///< Forces the RPTCH clock on.
  GsmIocCmdAnlgEnGraceCnt,          ///< Grace counter for extending CmdAnalogEn counter.
  GsmIocTxAnlgEnGraceCnt,           ///< Grace conter for extending the TxAnalogEn counter.
  GsmIocTxDqFifoRdEnPerRankDelDis,  ///< Disables the Per Rank delay on TxDq Fifo.
  GsmIocInternalClocksOn,           ///< Force on all the PI enables
  GsmIocDqsMaskPulseCnt,            ///< Controls the number of masked DQS pulses sent by the DDR IO during CMD VREF update in LP4 CBT
  GsmIocDqsPulseCnt,                ///< Controls the number of unmasked DQS pulses sent by the DDR IO during CMD VREF update in LP4 CBT
  GsmIocDqOverrideData,             ///< DQ value override to latch CMD VREF to the DRAM during LP4 CBT. This field is used to drive DQ7 High during LP5 ECT.
  GsmIocDqOverrideEn,               ///< Enables the DDR IO to force static DQ value to latch CMD VREF to the DRAM during LP4 CBT. This field is used to drive DQ7 High during LP5 ECT.
  GsmIocRankOverrideEn,             ///< Configures the DDRIO to override the delay values used for the target rank.
  GsmIocRankOverrideVal,            ///< Specified which rank to pull the delay values from.
  GsmIocDataCtlGear1,               ///< Program gear in DDRDATA: 1 = Gear1, 0 = Gear2
  GsmIocDataWrPreamble,             ///< The number of Write Preambles to send to the DRAM.  Should match MR encoding.
  GsmIocDccTrainingMode,
  GsmIocDccTrainingDone,
  GsmIocDccDrain,
  GsmIocDccActiveClks,
  GsmIocDccActiveBytes,
  GsmIocDccDcoCompEn,
  GsmIocDccClkTrainVal,
  GsmIocDccDataTrainDqsVal,
  GsmIocRxVocMode,                  ///< Controls the Sense Amp mode
  GsmIocDataTrainFeedback,          ///< DataTrainFeedback
  GsmIocDataDqsOdtParkMode,
  GsmIocDataDqsNParkLow,
  GsmIocRxAmpOffsetEn,
  GsmIocBiasPMCtrl,
  GsmIocFFCodePiOffset,
  GsmIocFFCodeIdleOffset,
  GsmIocFFCodeWeakOffset,
  GsmIocFFCodeWriteOffset,
  GsmIocFFCodeReadOffset,
  GsmIocFFCodePBDOffset,
  GsmIocFFCodeCCCDistOffset,
  GsmIocDataInvertNibble,
  GsmIocCapCancelCodeIdle,
  GsmIocCapCancelCodePBD,
  GsmIocCapCancelCodeWrite,
  GsmIocCapCancelCodeRead,
  GsmIocCapCancelCodePi,
  GsmIocVssHiFFCodeIdle,
  GsmIocVssHiFFCodeWrite,
  GsmIocVssHiFFCodeRead,
  GsmIocVssHiFFCodePBD,
  GsmIocVssHiFFCodePi,
  GsmIocEnableSpineGate,
  EndOfIocMarker,                   ///< IO Config Marker
  GsmMctRCD,
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
  GsmMctCA2CS,
  GsmMctCSL,
  GsmMctCSH,
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
  GsmMctXSR,                    ///< Self Refresh exit to commands not requiring a locked DLL (tXS) in DDR3/4(For SKL, this maps to the tXS_offset) or Self Refresh exit to next valid command delay (tXSR) in LPDDR3/4.
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
  GsmMctRFCpb,                  ///< Refresh cycle time per bank in DCLKS. How long the per bank refresh command takes to complete.
  EndOfMctMarker,               ///< Marks the end of the MC Timing Group.
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
  GsmMccStackedMode,
  GsmMccStackChMap,
  GsmMccLChannelMap,
  GsmMccSChannelSize,
  GsmMccStackedChHash,
  GsmMccChWidth,
  GsmMccHalfCachelineMode,
  GsmMccLDimmSize,              ///< Defines the L DIMM size in mutiples of X which may vary from project to project.
  GsmMccLDimmDramWidth,         ///< This field defines the L DIMM device width: x4, x8, x16, x32, x64
  GsmMccLDimmRankCnt,
  GsmMccSDimmSize,              ///< Defines the S DIMM size in mutiples of X which may vary from project to project.
  GsmMccSDimmDramWidth,         ///< This field defines the S DIMM device width: x4, x8, x16, x32, x64
  GsmMccSDimmRankCnt,
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
  GsmMccPbrDisOnHot,
  GsmMccOdtOverride,            ///< Override enable
  GsmMccOdtOn,                  ///< Override value
  GsmMccMprTrainDdrOn,
  GsmMccCkeOverride,            ///< Override enable
  GsmMccCkeOn,                  ///< Override value
  EndOfMccMarker,               ///< End of MC Configuration Group.
  GsmCmiHashMask,
  GsmCmiLsbMaskBit,
  GsmCmiHashMode,
  GsmCmiStackedMode,
  GsmCmiStackMsMap,
  GsmCmiLMadSliceMap,
  GsmCmiSMadSliceSize,
  GsmCmiStackedMsHash,
  EndOfCmiMarker,               ///< End of CMI Group.
  GsmComplexRcvEn,
  GsmComplexRxBias,             ///< Combines the control of RxBiasRComp and RxBiasIComp into one linear field.
  GsmGtMax,                     ///< GSM_GT enumeration maximum value.
  GsmDebugStringMax,            ///< Used to control Debug string array size.
  GsmGtDelim = MRC_INT32_MAX        ///< This value ensures the enum size is consistent on both sides of the PPI.
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
  SigCa06,      ///< LPDDR3 has 10 CA pins per bus.
  SigCa07,
  SigCa08,
  SigCa09,
  SigCa16,
  SigCa17,
  SigCa18,
  SigCa19,
  GsmCsnMax,
  GsmCsnDelim = MRC_INT32_MAX
} GSM_CSN;
#endif // _MrcCommonTypes_h_

