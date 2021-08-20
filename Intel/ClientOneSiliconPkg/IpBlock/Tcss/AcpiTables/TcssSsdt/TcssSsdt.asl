/** @file
  This file contains the TCSS SSDT Table ASL code.
  It defines a SSDT table for TCSS

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include <Register/PchPcieRpRegs.h>
#include <Register/UsbRegs.h>
#include <Register/HostDmaRegs.h>
#include <Register/ItbtPcieRegs.h>
#include <Register/CpuPcieRegs.h>
#include <Register/IomRegs.h>

//
// MAILBOX_BIOS_CMD_TCSS_DEVEN_INTERFACE
// Command code 0x15
// Description: Gateway command for handling TCSS DEVEN clear/restore.
// Field PARAM1[15:8] of the _INTERFACE register is used in this command to select from a pre-defined set of subcommands:
//
#define MAILBOX_BIOS_CMD_TCSS_DEVEN_INTERFACE     0x00000015
// Sub-Command 0
#define TCSS_DEVEN_MAILBOX_SUBCMD_GET_STATUS      0
// Sub-Command 1
#define TCSS_DEVEN_MAILBOX_SUBCMD_TCSS_CHANGE_REQ 1

#define TCSS_IOM_ACK_TIMEOUT_IN_MS      100

#define TCSS_ITBT_PCIE0_RP0             0
#define TCSS_ITBT_PCIE0_RP1             1
#define TCSS_ITBT_PCIE0_RP2             2
#define TCSS_ITBT_PCIE0_RP3             3
#define TCSS_XHCI                       4
#define TCSS_XDCI                       5
#define TCSS_DMA0                       6
#define TCSS_DMA1                       7
#define TCSS_ITBT_PCIE1_RP0             8
#define TCSS_ITBT_PCIE1_RP1             9
#define TCSS_ITBT_PCIE1_RP2             10
#define TCSS_ITBT_PCIE1_RP3             11

DefinitionBlock (
  "TcssSsdt.aml",
  "SSDT",
  2,
  "INTEL ",
  "TcssSsdt",
  0x1000
  )
{
External(\_SB.PC00, DeviceObj)
External(\_SB.PC01, DeviceObj)
External(\GPRW, MethodObj)
External(\ECR1)
External(\CPEX)
External(\ADBG, MethodObj)
External(\_SB.PC00.GMHB, MethodObj)
External(\PCIC, MethodObj)
External(\PCID, MethodObj)
External(XDAT, MethodObj)
External(SPPS, MethodObj)
External(TCDS)
External(\_SB.PC00.GPCB, MethodObj)
External(OTHC)
External(CSFR)
External(P2PS)
External(GPCB, MethodObj) // Get PCIe BAR

External(THCE) // TCSS XHCI Device Enable
External(TDCE) // TCSS XDCI Device Enable
External(DME0) // TCSS DMA 0 Device Enable
External(DME1) // TCSS DMA 1 Device Enable
External(TRE0) // TCSS ItbtPcie PCIE RP 0 Device Enable
External(TRE1) // TCSS ItbtPcie PCIE RP 1 Device Enable
External(TRE2) // TCSS ItbtPcie PCIE RP 2 Device Enable
External(TRE3) // TCSS ItbtPcie PCIE RP 3 Device Enable
External(TPA0) // TCSS ItbtPcie PCIE RP 0 Address
External(TPA1) // TCSS ItbtPcie PCIE RP 1 Address
External(TPA2) // TCSS ItbtPcie PCIE RP 2 Address
External(TPA3) // TCSS ItbtPcie PCIE RP 3 Address
External(TCIT) // TCSS xDCI Int Pin
External(TCIR) // TCSS xDCI Irq number
External(TRTD) // TCSS RTD3
External(IMRY) // IOM Ready
External(TIVS) // TCSS IOM VccSt

External(LTE0) // Latency Tolerance Reporting Mechanism.Enable/Disable
External(LTE1) // Latency Tolerance Reporting Mechanism.
External(LTE2) // Latency Tolerance Reporting Mechanism.
External(LTE3) // Latency Tolerance Reporting Mechanism.
External(PSL0) // PCIE LTR max snoop Latency 0
External(PSL1) // PCIE LTR max snoop Latency 1
External(PSL2) // PCIE LTR max snoop Latency 2
External(PSL3) // PCIE LTR max snoop Latency 3
External(PNS0) // PCIE LTR max no snoop Latency 0
External(PNS1) // PCIE LTR max no snoop Latency 1
External(PNS2) // PCIE LTR max no snoop Latency 2
External(PNS3) // PCIE LTR max no snoop Latency 3
External(\CPWE)// CPU WAKE Enable
External(\CPWS)// CPU WAKE Status
External(\PICM)

include("ITbt.asl")

Scope (\_SB) {

  Name (C2PW, 0) // Set Default value 0 to Tcss CPU to PCH WAKE Value

  // C2PM (CPU to PCH Method)
  //
  // This object is Enable/Disable GPE_CPU_WAKE_EN.
  //
  // Arguments: (4)
  //   Arg0 - An Integer containing the device wake capability
  //   Arg1 - An Integer containing the target system state
  //   Arg2 - An Integer containing the target device state
  //   Arg3 - An Integer containing the request device type
  // Return Value:
  //   return 0
  //
  Method (C2PM, 4, NotSerialized) {

    Switch (ToInteger(Arg3)) {
      Case(TCSS_ITBT_PCIE0_RP0) {
      }
      Case(TCSS_ITBT_PCIE0_RP1) {
      }
      Case(TCSS_ITBT_PCIE0_RP2) {
      }
      Case(TCSS_ITBT_PCIE0_RP3) {
      }
      Case(TCSS_XHCI) {
      }
      Case(TCSS_XDCI) {
      }
      Case(TCSS_DMA0) {
      }
      Case(TCSS_DMA1) {
      }
      Case(TCSS_ITBT_PCIE1_RP0) {
      }
      Case(TCSS_ITBT_PCIE1_RP1) {
      }
      Case(TCSS_ITBT_PCIE1_RP2) {
      }
      Case(TCSS_ITBT_PCIE1_RP3) {
      }
      Default {Return (0)}
    }

    Store ( 0, Local1)
    ShiftLeft (BIT0, ToInteger(Arg3), Local1)


    /// This method is used to enable/disable wake from Tcss Device (WKEN)
    If(LAnd(Arg0, Arg1))
    { /// If entering Sx and enabling wake, need to enable WAKE capability
      If (LEqual(CPWE,0)) { // If CPU WAKE EN is not set, Set it.
        If (CPWS) { // If CPU WAKE STATUS is set, Clear it.
          Store (1, CPWS) // Clear CPU WAKE STATUS by writing 1.
        }
        Store (1, CPWE) // Set CPU WAKE EN by writing 1.
      }
      If (LEqual (And (C2PW, Local1), 0)) {
        Or (C2PW, Local1,C2PW) // Set Corresponding Device En BIT in C2PW
      }
    } Else {  /// If Staying in S0 or Disabling Wake
      If(LOr(Arg0, Arg2)) ///- Check if Exiting D0 and arming for wake
      {
        If (LEqual(CPWE,0)) { // If CPU WAKE EN is not set, Set it.
          If (CPWS) { // If CPU WAKE STATUS is set, Clear it.
            Store (1, CPWS) // Clear CPU WAKE STATUS by writing 1.
          }
          Store (1, CPWE) // Set CPU WAKE EN by writing 1.
        }
        If (LEqual (And (C2PW, Local1), 0)) {
          Or (C2PW, Local1,C2PW) // Set Corresponding Device En BIT in C2PW
        }
      } Else { ///- Disable runtime PME, either because staying in D0 or disabling wake
        If (LNotEqual (And (C2PW, Local1), 0)) {
          And (C2PW, Not (Local1),C2PW) // Clear Corresponding Device En BIT in C2PW
        }
        If (LAnd(LNotEqual(CPWE,0), LEqual(C2PW,0))) { // If CPU WAKE EN is set, Clear it.
          Store (0, CPWE) // Clear CPU WAKE EN by writing 0.
        }
      }
    }

    Return (0)
  }
}

Scope (\_SB.PC00) {

  //
  // Operation region defined to access the IOM REGBAR
  // Get the MCHBAR in offset 0x48 in B0:D0:F0
  // REGBAR Base address is in offset 0x7110 of MCHBAR.
  //
  OperationRegion (MBAR, SystemMemory, Add(\_SB.PC00.GMHB(),0x7100), 0x1000)
  Field (MBAR, ByteAcc, NoLock, Preserve)
  {
    Offset(0x10),
    RBAR, 64       //RegBar, offset 0x7110 in MCHBAR
  }
  Field (MBAR, DWordAcc, NoLock, Preserve)
  {
    Offset(0x304), //PRIMDN_MASK1_0_0_0_MCHBAR_IMPH, offset 0x7404
    ,     31,
    TCD3, 1        // [31:31] TCSS IN D3 bit
  }

  OperationRegion (PBAR, SystemMemory, Add(\_SB.PC00.GMHB(),0x5DA0), 0x08)
  Field (PBAR, DWordAcc, NoLock, Preserve)
  {
    PMBD, 32,       // pCode MailBox Data, offset 0x5DA0 in MCHBAR
    PMBC, 8,        // pCode MailBox Command, [7:0] of offset 0x5DA4 in MCHBAR
    PSCM, 8,        // pCode MailBox Sub-Command, [15:8] of offset 0x5DA4 in MCHBAR
    ,     15,       // Reserved
    PMBR, 1         // pCode MailBox RunBit,  [31:31] of offset 0x5DA4 in MCHBAR
  }

  //
  // Poll pCode MailBox Ready
  //
  // Return 0xFF - Timeout
  //        0x00 - Ready
  //
  Method(PMBY, 0)
  {
    Store (0, Local0)
    While (LAnd (PMBR, LLess (Local0, 1000))) {
      Increment (Local0)
      Stall (1)
    }
    If (LEqual (Local0, 1000)) {
      //
      // Timeout occurred
      //
      Return (0xFF)
    }
    Return (0)
  }

  //
  // Method to send pCode MailBox command TCSS_DEVEN_MAILBOX_SUBCMD_GET_STATUS
  // Result will be updated in DATA[1:0]
  //
  // DATA[0:0] TCSS_DEVEN_CURRENT_STATE:  0 - TCSS Deven in normal state
  //                                      1 - TCSS Deven is cleared by BIOS Mailbox request
  // DATA[1:1] TCSS_DEVEN_REQUEST_STATUS: 0 - IDLE. TCSS DEVEN has reached its final requested state
  //                                      1 - In Progress. TCSS DEVEN is currently in progress of switching state according to given request (bit 0 reflects source state).
  //
  // Return 0x00 - TCSS Deven in normal state
  //        0x01 - TCSS Deven is cleared by BIOS Mailbox request
  //        0x1x - TCSS Deven is currently in progress of switching state according to given request
  //        0xFE - Command timeout
  //        0xFF - Command corrupt
  //
  Method(DSGS, 0)
  {
    If (LEqual (PMBY (), 0)) {
      Store (MAILBOX_BIOS_CMD_TCSS_DEVEN_INTERFACE, PMBC)
      Store (TCSS_DEVEN_MAILBOX_SUBCMD_GET_STATUS, PSCM)
      Store (1, PMBR)
      If (LEqual (PMBY (), 0)) {
        Store (PMBD, Local0)
        Store (PMBC, Local1)
        Stall (10)
        If (LOr (LNotEqual (Local0, PMBD), LNotEqual (Local1, PMBC))) {
          //
          // pCode MailBox is corrupt
          //
          Return (0xFF)
        }
        Return (PMBD)
      } Else {
        //
        // pCode MailBox is not ready
        //
        Return (0xFE)
      }
    } Else {
      //
      // pCode MailBox is not ready
      //
      Return (0xFE)
    }
  }

  //
  // Method to send pCode MailBox command TCSS_DEVEN_MAILBOX_SUBCMD_TCSS_CHANGE_REQ
  //
  // Arg0 : 0 - Restore to previously saved value of TCSS DEVEN
  //        1 - Save current TCSS DEVEN value and clear it
  //
  // Return 0x00 - MAILBOX_BIOS_CMD_CLEAR_TCSS_DEVEN command completed
  //        0xFD - Input argument is invalid
  //        0xFE - Command timeout
  //        0xFF - Command corrupt
  //
  Method(DSCR, 1)
  {
    If (LGreater (Arg0, 1)) {
      //
      // pCode MailBox is corrupt
      //
      Return (0xFD)
    }
    If (LEqual (PMBY (), 0)) {
      Store (MAILBOX_BIOS_CMD_TCSS_DEVEN_INTERFACE, PMBC)
      Store (TCSS_DEVEN_MAILBOX_SUBCMD_TCSS_CHANGE_REQ, PSCM)
      Store (Arg0, PMBD)
      Store (1, PMBR)
      If (LEqual (PMBY (), 0)) {
        Store (PMBD, Local0)
        Store (PMBC, Local1)
        Stall (10)
        If (LOr (LNotEqual (Local0, PMBD), LNotEqual (Local1, PMBC))) {
          //
          // pCode MailBox is corrupt
          //
          Return (0xFF)
        }
        //
        // Poll TCSS_DEVEN_REQUEST_STATUS, timeout value is 10ms
        //
        Store (0, Local0)
        While(LAnd(And(DSGS (), BIT1), LLess(Local0, 100))) {
          Stall (100)
          Increment(Local0)
        }
        If (LEqual(Local0, 100)) {
          Return (0xFE)
        } Else {
          Return (0x00)
        }
      } Else {
        //
        // pCode MailBox is not ready
        //
        Return (0xFE)
      }
    } Else {
      //
      // pCode MailBox is not ready
      //
      Return (0xFE)
    }
  }

  //
  // IOM REG BAR Base address is in offset 0x7110 in MCHBAR
  //
  Method(IOMA, 0)
  {
    Return(And(^RBAR, 0xFFFFFFFFFFFFFFFE))
  }

  // Method to dynamically assign register offset based on Port ID value based on stepping
  // Port ID for A0 = 0x7
  // Port ID for B0 = 0xC1
  Method(PIDS, 0)
  {
    return(0xC10000)
  }

  //
  // From RegBar Base, IOM_TypeC_SW_configuration_1 is in offset 0xC10040, where 0x07(in A0) is the IOM port
  // id and 0x0040 is the register offset
  //
  OperationRegion(IOMR, SystemMemory, Add(IOMA(), PIDS()), 0x100)
  Field(IOMR, DWordAcc, NoLock, Preserve)
  {
    Offset(0x40),
    ,     15,
    TD3C, 1,          // [15:15] Type C D3 cold bit
    TACK, 1,          // [16:16] IOM Acknowledge bit
    DPOF, 1,          // [17:17] Set 1 to indicate IOM, all the display is OFF, clear otherwise
    Offset(0x70),     // Pyhical addr is offset 0x70.
    IMCD, 32,         // R_SA_IOM_BIOS_MAIL_BOX_CMD
    IMDA, 32          // R_SA_IOM_BIOS_MAIL_BOX_DATA
  }

  //
  // TBT Group0 ON method
  //
  Method(TG0N, 0)
  {


    If(LNotEqual(\_SB.PC00.TDM0.VDID,0xFFFFFFFF)) {                       // DMA0 exists

      If (LEqual(\_SB.PC00.TDM0.STAT, 0)) {                               // DMA0 is in D3Cold early
        \_SB.PC00.TDM0.D3CX()                                           // RTD3 Exit
        If (CondRefOf(\_SB.PC01)) {
          \_SB.PC01.TRP0.D3CX()                                           // Then RP0 and RP1
          \_SB.PC01.TRP1.D3CX()
        } Else {
          \_SB.PC00.TRP0.D3CX()                                           // Then RP0 and RP1
          \_SB.PC00.TRP1.D3CX()
        }
      } Else {
      }
      Sleep(ITRE)
    }
  }

  //
  // TBT Group0 OFF method
  //
  Method(TG0F, 0)
  {


    If(LNotEqual(\_SB.PC00.TDM0.VDID,0xFFFFFFFF)) {                       // DMA0 exists
      If (LEqual(\_SB.PC00.TDM0.STAT, 1)) {                               // DMA0 is in not D3Cold now
        \_SB.PC00.TDM0.D3CE()                                             // Enable DMA RTD3
        If (CondRefOf(\_SB.PC01)) {
          \_SB.PC01.TRP0.D3CE()                                           // Then RP0 and RP1
          \_SB.PC01.TRP1.D3CE()
        } Else {
          \_SB.PC00.TRP0.D3CE()                                           // Then RP0 and RP1
          \_SB.PC00.TRP1.D3CE()
        }
      }
    }
  }

  //
  // TBT Group1 ON method
  //
  Method(TG1N, 0)
  {


    If(LNotEqual(\_SB.PC00.TDM1.VDID,0xFFFFFFFF)) {                       // DMA1 exists
      If (LEqual(\_SB.PC00.TDM1.STAT, 0)) {                               // DMA1 is in D3Cold early
        \_SB.PC00.TDM1.D3CX()                                             // RTD3 Exit
        If (CondRefOf(\_SB.PC01)) {
          \_SB.PC01.TRP2.D3CX()                                           // Then RP2 and RP3
          \_SB.PC01.TRP3.D3CX()
        } Else {
          \_SB.PC00.TRP2.D3CX()                                           // Then RP2 and RP3
          \_SB.PC00.TRP3.D3CX()
        }
      } Else {
      }
      Sleep(ITRE)
    }
  }

  //
  // TBT Group1 OFF method
  //
  Method(TG1F, 0)
  {


    If(LNotEqual(\_SB.PC00.TDM1.VDID,0xFFFFFFFF)) {                       // DMA1 exists

      If (LEqual(\_SB.PC00.TDM1.STAT, 1)) {                               // DMA1 is in not D3Cold now
        \_SB.PC00.TDM1.D3CE()                                           // Enable DMA RTD3
        If (CondRefOf(\_SB.PC01)) {
          \_SB.PC01.TRP2.D3CE()                                         // Then RP2 and RP3
          \_SB.PC01.TRP3.D3CE()
        } Else {
          \_SB.PC00.TRP2.D3CE()                                         // Then RP2 and RP3
          \_SB.PC00.TRP3.D3CE()
        }
      }
    }
  }
  If (ITRT) {
    // PowerResource (resourcename, systemlevel, resourceorder)
    // systemlevel - S5, the deepest system sleep level OSPM must maintain to keep this power resource
    // on following by the ordering. resourceorder - The resourceorder field in the Power Resource object
    // is a value per Power Resource that provides the system with the order in which Power Resources must
    // be enabled or disabled. Power Resource levels are enabled from low resourceorder values to high
    // values and are disabled from high resourceorder values to low values.
    PowerResource(TBT0,
                     5,
                     1)
    {
      Method(_STA, 0)
      {
        Return(\_SB.PC00.TDM0.STAT)
      }

      Method(_ON,0)
      {
        If (ITIM) {
          TG0N()
        }
      }

      Method(_OFF,0)
      {
        If (ITIM) {
          If (LEqual(\_SB.PC00.TDM0.SD3C, 0)) { // Skip D3C entry
            TG0F()
          }
        }
      }
    }

    PowerResource(TBT1,
                     5,
                     1)
    {
      Method(_STA, 0)
      {
        Return(\_SB.PC00.TDM1.STAT)
      }

      Method(_ON,0)
      {
        If (ITIM) {
          TG1N()
        }
      }

      Method(_OFF,0)
      {
        If (ITIM) {
          If (LEqual(\_SB.PC00.TDM1.SD3C, 0)) {                                              // Skip D3C entry
            TG1F()
          }
        }
      }
    }
  }
  If (TRTD) {
    Method(TCON, 0) {

      //Reset IOM D3 cold bit if it is in d3 cold now.
      If (LEqual(TD3C, 1)) // It was in D3 cold before.
      {
      //Reset IOM D3 cold bit
        Store(0, TD3C) //Request IOM for D3 cold exit sequence

        Store(0, Local0) //Time check counter variable

        // wait for ack, the maximum wait time for the ack is 100 msec. (Tune this accordingly after stable Si)
        While (LAnd(LNotEqual(TACK,0), LLess(Local0, TCSS_IOM_ACK_TIMEOUT_IN_MS)))  // Wait in this loop until TACK becomes 0 with timeout TCSS_IOM_ACK_TIMEOUT_IN_MS by default
        {
          Sleep(1) //Delay of 1ms
          Increment(Local0)
        }
        If(LEqual(Local0, TCSS_IOM_ACK_TIMEOUT_IN_MS)) // if TCSS_IOM_ACK_TIMEOUT_IN_MS timeout occurred
        {
        }
        Else
        {
          Store(0, TCD3) // Program IOP MCTP Drop (TCSS_IN_D3) after D3 cold exit and acknowledgement by IOM
            //
            // If the TCSS Deven is cleared by BIOS Mailbox request, then Restore to previously saved value of TCSS DEVEN
            //
            If (LEqual (DSGS (), 1)) {
              DSCR (0)
            }
          //
          // Set XDCI INT and IRQ
          //
          If (LAnd(LEqual(TDCE, 1), LEqual(IMRY, 1))) {
            \_SB.PC00.TXDC.SINT(TCIT,TCIR)
          }
        }
      } Else {
        //
        // Drop this method due to it is alredy exit D3 cold
        //
        Return
      }
    }
    Method(TCOF, 0) {

      If (LOr(LNotEqual(\_SB.PC00.TXHC.SD3C, 0), LOr(LNotEqual(\_SB.PC00.TDM0.SD3C, 0), LNotEqual(\_SB.PC00.TDM1.SD3C, 0))))
      {
        Return                                                            // Skip D3C entry
      }

          //
          // If the TCSS Deven in normal state, then Save current TCSS DEVEN value and clear it
          //
          If (LEqual (DSGS (), 0)) {
            DSCR (1)
          }

      Store(1, TCD3)       // Program IOP MCTP Drop (TCSS_IN_D3) in D3Cold entry beforing entering D3 cold
      Store(1, TD3C) //Request IOM  for D3 cold entry sequence
    }
    PowerResource(D3C,
                    5,
                    0)  // Turn on second, turn off second to last
    {
      Name(STAT, 0x1)  // Variable to save power state 1 - TC Cold request cleared, 0 - TC Cold request sent

      Method(_STA, 0)
      {
        Return(STAT)
      }

      Method(_ON, 0)
      {
        \_SB.PC00.TCON()
        Store(1, STAT)
      }

      Method(_OFF, 0)
      {
        \_SB.PC00.TCOF()
        Store(0, STAT)
      }
    }
  }
  //
  // TCSS xHCI device
  //
  Device(TXHC) {

    Name (_ADR, 0x000D0000)  // _ADR: Address
    Name (_DDN, "ICL North XHCI controller")  // _DDN: DOS Device Name
    Name (_STR, Unicode ("ICL North XHCI controller"))  // _STR: Description String
    Name (DCPM, TCSS_XHCI)

    Method (_STA, 0x0, NotSerialized) {
      If(LEqual(THCE, 1)) {
        Return(0x0F)
      }
      Return(0x0)
    }

    Include("TcssXhci.asl")
  } // end "TCSS xHCI device"

  //
  // TCSS xDCI device
  //
  If(LEqual(TDCE, 1)) {
    Device(TXDC) {

      Name (_ADR, 0x000D0001)  // _ADR: Address
      Name (_DDN, "ICL North XDCI controller")  // _DDN: DOS Device Name
      Name (_STR, Unicode ("ICL North XDCI controller"))  // _STR: Description String
      Name (DCPM, TCSS_XDCI)

      Method (_STA, 0x0, NotSerialized) {
        If(LEqual(TDCE, 1)) {
          Return(0x0F)
        }
        Return(0x00)
      }

      //
      // SINT -> Set XDCI INT and IRQ
      //
      // Arg0 : INT Pin number
      // Atg1 : IRQ number
      //
      Method (SINT,2,Serialized) {
        If (LEqual(IMRY, 1)) {
          ShiftLeft(Arg0, N_OTG_PCR_PCICFGCTRL_INT_PIN, Local0)
          ShiftLeft(Arg1, N_OTG_PCR_PCICFGCTRL_PCI_IRQ, Local1)
          Add(Local0, Local1, Local0)
          Store(Local0, IMDA)  // Set R_SA_IOM_BIOS_MAIL_BOX_DATA

          Store(V_SA_IOM_BIOS_CMD_TYPE_XDCI_INT, Local1) // Set R_SA_IOM_BIOS_MAIL_BOX_DATA
          ShiftLeft(Local1, 8, Local1)
          Add(Local1, V_SA_IOM_BIOS_GEM_SB_TRAN_CMD, Local1)
          Store(Local1, IMCD) // Set command register
          Or(IMCD, BIT31, IMCD)
        } Else {
          ADBG("IOM not ready")
        }
      }

      Include("TcssXdci.asl")
    } // end "TCSS xDCI device"
  }

  //
  // TCSS DMA 0 device
  //
  Device(TDM0) {

    Name (_ADR, 0x000D0002)  // _ADR: Address
    Name (_DDN, "ICL TBT DMA0 controller")  // _DDN: DOS Device Name
    Name (_STR, Unicode ("ICL TBT DMA0 controller"))  // _STR: Description String
    Name (DUID, 0) // TBT DMA number
    Name (DCPM, TCSS_DMA0)

    Method (_STA, 0x0, NotSerialized) {
      If(LEqual(DME0, 1)) {
        Return(0x0F)
      }
      Return(0x00)
    }

    Method (BASE, 0) {
      Add (GPCB(), 0x6A000, Local0)
      Return (Local0)    // Return PCIE  Base address
    }
    Include ("TcssDma.asl")
    Include ("ITbtMailBox.asl")
  } // end "TCSS DMA 0 device"

  //
  // TCSS DMA 1 device
  //
  Device(TDM1) {

    Name (_ADR, 0x000D0003)  // _ADR: Address
    Name (_DDN, "ICL TBT DMA1 controller")  // _DDN: DOS Device Name
    Name (_STR, Unicode ("ICL TBT DMA1 controller"))  // _STR: Description String
    Name (DUID, 1) // TBT DMA number
    Name (DCPM, TCSS_DMA1)

    Method (_STA, 0x0, NotSerialized) {
      If(LEqual(DME1, 1)) {
        Return(0x0F)
      }
      Return(0x00)
    }

    Method (BASE, 0) {
      Add (GPCB(), 0x6B000, Local0)
      Return (Local0)    // Return PCIE  Base address
    }
    Include ("TcssDma.asl")
    Include ("ITbtMailBox.asl")
  } // end "TCSS DMA 1 device"
}

If (CondRefOf(\_SB.PC01)) {
  Scope (\_SB.PC01) {
    //
    // TCSS iTBT PCIE Root Port #00
    //
    Device(TRP0) {
      Method (_ADR, 0) {
        If (LNotEqual(TPA0,0)) {
          Return (TPA0)
        } Else {
          Return (0x00070000)
        }
      }
      Name(TUID, 0) // TBT RP Number 0 for RP00
      Name(LTEN, 0)
      Name(LMSL, 0x88C8)
      Name(LNSL, 0x88C8)
      Name(DCPM, TCSS_ITBT_PCIE1_RP0)

      Method (_STA, 0x0, NotSerialized) {
        If(LEqual(TRE0, 1)) {
          Return(0x0F)
        }
        Return(0x00)
      }
      Method(_INI)
      {
        Store (LTE0, LTEN)
        Store (PSL0, LMSL)
        Store (PNS0, LNSL)
      }
      Include("TcssItbtPcieRp.asl")
    } // end "TCSS iTBT PCIE Root Port #00"

    //
    // TCSS iTBT PCIE Root Port #01
    //
    Device(TRP1) {
      Method (_ADR, 0) {
        If (LNotEqual(TPA1,0)) {
          Return (TPA1)
        } Else {
          Return (0x00070001)
        }
      }
      Name(TUID, 1) // TBT RP Number 1 for RP01
      Name(LTEN, 0)
      Name(LMSL, 0x88C8)
      Name(LNSL, 0x88C8)
      Name(DCPM, TCSS_ITBT_PCIE1_RP1)
      Method (_STA, 0x0, NotSerialized) {
        If(LEqual(TRE1, 1)) {
          Return(0x0F)
        }
        Return(0x00)
      }
      Method(_INI)
      {
        Store (LTE1, LTEN)
        Store (PSL1, LMSL)
        Store (PNS1, LNSL)
      }
      Include("TcssItbtPcieRp.asl")
    } // end "TCSS iTBT PCIE Root Port #01"

    //
    // TCSS iTBT PCIE Root Port #02
    //
    Device(TRP2) {
      Method (_ADR, 0) {
        If (LNotEqual(TPA2,0)) {
          Return (TPA2)
        } Else {
          Return (0x00070002)
        }
      }
      Name(TUID, 2) // TBT RP Number 2 for RP02
      Name(LTEN, 0)
      Name(LMSL, 0x88C8)
      Name(LNSL, 0x88C8)
      Name(DCPM, TCSS_ITBT_PCIE1_RP2)

      Method (_STA, 0x0, NotSerialized) {
        If(LEqual(TRE2, 1)) {
          Return(0x0F)
        }
        Return(0x00)
      }
      Method(_INI)
      {
        Store (LTE2, LTEN)
        Store (PSL2, LMSL)
        Store (PNS2, LNSL)
      }
      Include("TcssItbtPcieRp.asl")
    } // end "TCSS iTBT PCIE Root Port #02"

    //
    // TCSS iTBT PCIE Root Port #03
    //
    Device(TRP3) {
      Method (_ADR, 0) {
        If (LNotEqual(TPA3,0)) {
          Return (TPA3)
        } Else {
          Return (0x00070003)
        }
      }
      Name(TUID, 3) // TBT RP Number 3 for RP03
      Name(LTEN, 0)
      Name(LMSL, 0x88C8)
      Name(LNSL, 0x88C8)
      Name(DCPM, TCSS_ITBT_PCIE1_RP3)

      Method (_STA, 0x0, NotSerialized) {
        If(LEqual(TRE3, 1)) {
          Return(0x0F)
        }
        Return(0x00)
      }
      Method(_INI)
      {
        Store (LTE3, LTEN)
        Store (PSL3, LMSL)
        Store (PNS3, LNSL)
      }
      Include("TcssItbtPcieRp.asl")
    } // end "TCSS iTBT PCIE Root Port #03"
  }
} Else {
  Scope (\_SB.PC00) {
    //
    // TCSS iTBT PCIE Root Port #00
    //
    Device(TRP0) {
      Method (_ADR, 0) {
        If (LNotEqual(TPA0,0)) {
          Return (TPA0)
        } Else {
          Return (0x00070000)
        }
      }
      Name(TUID, 0) // TBT RP Number 0 for RP00
      Name(LTEN, 0)
      Name(LMSL, 0x88C8)
      Name(LNSL, 0x88C8)
      Name(DCPM, TCSS_ITBT_PCIE0_RP0)

      Method (_STA, 0x0, NotSerialized) {
        If(LEqual(TRE0, 1)) {
          Return(0x0F)
        }
        Return(0x0)
      }
      Method(_INI)
      {
        Store (LTE0, LTEN)
        Store (PSL0, LMSL)
        Store (PNS0, LNSL)
      }
      Include("TcssItbtPcieRp.asl")
    } // end "TCSS iTBT PCIE Root Port #00"

    //
    // TCSS iTBT PCIE Root Port #01
    //
    Device(TRP1) {
      Method (_ADR, 0) {
        If (LNotEqual(TPA1,0)) {
          Return (TPA1)
        } Else {
          Return (0x00070001)
        }
      }
      Name(TUID, 1) // TBT RP Number 1 for RP01
      Name(LTEN, 0)
      Name(LMSL, 0x88C8)
      Name(LNSL, 0x88C8)
      Name(DCPM, TCSS_ITBT_PCIE0_RP1)

      Method (_STA, 0x0, NotSerialized) {
        If(LEqual(TRE1, 1)) {
          Return(0x0F)
        }
        Return(0x00)
      }
      Method(_INI)
      {
        Store (LTE0, LTEN)
        Store (PSL0, LMSL)
        Store (PNS0, LNSL)
      }
      Include("TcssItbtPcieRp.asl")
    } // end "TCSS iTBT PCIE Root Port #01"

    //
    // TCSS iTBT PCIE Root Port #02
    //
    Device(TRP2) {
      Method (_ADR, 0) {
        If (LNotEqual(TPA2,0)) {
          Return (TPA2)
        } Else {
          Return (0x00070002)
        }
      }
      Name(TUID, 2) // TBT RP Number 2 for RP02
      Name(LTEN, 0)
      Name(LMSL, 0x88C8)
      Name(LNSL, 0x88C8)
      Name(DCPM, TCSS_ITBT_PCIE0_RP2)

      Method (_STA, 0x0, NotSerialized) {
        If(LEqual(TRE2, 1)) {
          Return(0x0F)
        }
        Return(0x00)
      }
      Method(_INI)
      {
        Store (LTE0, LTEN)
        Store (PSL0, LMSL)
        Store (PNS0, LNSL)
      }
      Include("TcssItbtPcieRp.asl")
    } // end "TCSS iTBT PCIE Root Port #02"

    //
    // TCSS iTBT PCIE Root Port #03
    //
    Device(TRP3) {
      Method (_ADR, 0) {
        If (LNotEqual(TPA3,0)) {
          Return (TPA3)
        } Else {
          Return (0x00070003)
        }
      }
      Name(TUID, 3) // TBT RP Number 3 for RP03
      Name(LTEN, 0)
      Name(LMSL, 0x88C8)
      Name(LNSL, 0x88C8)
    Name(DCPM, TCSS_ITBT_PCIE0_RP3)

      Method (_STA, 0x0, NotSerialized) {
        If(LEqual(TRE3, 1)) {
          Return(0x0F)
        }
        Return(0x00)
      }
      Method(_INI)
      {
        Store (LTE0, LTEN)
        Store (PSL0, LMSL)
        Store (PNS0, LNSL)
      }
      Include("TcssItbtPcieRp.asl")
    } // end "TCSS iTBT PCIE Root Port #03"
  }
}
  Scope(\_SB) {
    //
    // TCSS iTBT Wake notify
    //
    Method(TCWK, 1) {
      If(LOr(LEqual(Arg0,3), LEqual(Arg0,4))) {
        If (CondRefOf(\_SB.PC01)) {
          If(LNotEqual(\_SB.PC01.TRP0.VDID,0xFFFFFFFF))
          {
            Notify (\_SB.PC01.TRP0,0)
          }
          If(LNotEqual(\_SB.PC01.TRP1.VDID,0xFFFFFFFF))
          {
            Notify (\_SB.PC01.TRP1,0)
          }
          If(LNotEqual(\_SB.PC01.TRP2.VDID,0xFFFFFFFF))
          {
            Notify (\_SB.PC01.TRP2,0)
          }
          If(LNotEqual(\_SB.PC01.TRP3.VDID,0xFFFFFFFF))
          {
            Notify (\_SB.PC01.TRP3,0)
          }
        } Else {
          If(LNotEqual(\_SB.PC00.TRP0.VDID,0xFFFFFFFF))
          {
            Notify (\_SB.PC00.TRP0,0)
          }
          If(LNotEqual(\_SB.PC00.TRP1.VDID,0xFFFFFFFF))
          {
            Notify (\_SB.PC00.TRP1,0)
          }
          If(LNotEqual(\_SB.PC00.TRP2.VDID,0xFFFFFFFF))
          {
            Notify (\_SB.PC00.TRP2,0)
          }
          If(LNotEqual(\_SB.PC00.TRP3.VDID,0xFFFFFFFF))
          {
            Notify (\_SB.PC00.TRP3,0)
          }
        }
      }
    } // End of TCWK
  }
}