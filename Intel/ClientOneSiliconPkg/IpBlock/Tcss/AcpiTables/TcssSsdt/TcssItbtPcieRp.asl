/** @file
  This file contains the TCSS PCIe Root Port configuration

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
  Method (BASE, 0) {
    Store (And(_ADR, 0x7), Local0) // Function Number
    Store (And(ShiftRight(_ADR, 16), 0x1F), Local1) // Device Number
    Add (ShiftLeft(Local0, 12), ShiftLeft(Local1, 15), Local2)
    If (CondRefOf(\_SB.PC01)) {
      // One segment occupied 256MB, so the PCIE base address of next segment is "PCI Segment0 address + 256MB"
      Add (GPCB(), 0x10000000, Local3)
      Add (Local2, Local3, Local3)
    } Else {
      Add (GPCB(), Local2, Local3)
    }
    Return (Local3)
  }

  OperationRegion(PXCS,SystemMemory, BASE(), 0x800)
  Field(PXCS,AnyAcc, NoLock, Preserve)
  {
    Offset(0),
    VDID, 32,
    Offset(0x50), // LCTL - Link Control Register
    L0SE, 1,      // 0, L0s Entry Enabled
    , 3,
    LDIS, 1,
    , 3,
    Offset(0x52), // LSTS - Link Status Register
    , 13,
    LASX, 1,      // 0, Link Active Status
    Offset(0x5A), // SLSTS[7:0] - Slot Status Register
    ABPX, 1,      // 0, Attention Button Pressed
    , 2,
    PDCX, 1,      // 3, Presence Detect Changed
    , 2,
    PDSX, 1,      // 6, Presence Detect State
    , 1,
    Offset(0x60), // RSTS - Root Status Register
    , 16,
    PSPX, 1,      // 16,  PME Status
    Offset(0xA4),
    D3HT, 2,      // Power State
    Offset(R_PCIE_MPC), // 0xD8, MPC - Miscellaneous Port Configuration Register
    , 30,
    HPEX, 1,      // 30,  Hot Plug SCI Enable
    PMEX, 1,      // 31,  Power Management SCI Enable
    Offset(R_PCIE_RPPGEN), // 0xE2, RPPGEN - Root Port Power Gating Enable
    , 2,
    L23E, 1,      // 2,   L23_Rdy Entry Request (L23ER)
    L23R, 1,      // 3,   L23_Rdy to Detect Transition (L23R2DT)
    Offset(R_PCIE_PCIEPMECTL), // 0x420, PCIEPMECTL (PCIe PM Extension Control)
    , 30,
    DPGE, 1,       // PCIEPMECTL[30]: Disabled, Detect and L23_Rdy State PHY Lane Power Gating Enable (DLSULPPGE):
    Offset(R_PCIE_ADVMCTRL), // 0x5BC
    , 3,
    RPER, 1,      //  RTD3PERST[3]
    RPFE, 1,      //  RTD3PFETDIS[4]
  }
  Field(PXCS,AnyAcc, NoLock, WriteAsZeros)
  {
    Offset(R_PCH_PCIE_CFG_SMSCS), // 0xDC, SMSCS - SMI/SCI Status Register
    , 30,
    HPSX, 1,      // 30,  Hot Plug SCI Status
    PMSX, 1       // 31,  Power Management SCI Status
  }

  Name(LTRV, Package(){0,0,0,0})

  //
  // _DSM Device Specific Method
  //
  // Arg0: UUID Unique function identifier
  // Arg1: Integer Revision Level
  // Arg2: Integer Function Index (0 = Return Supported Functions)
  // Arg3: Package Parameters
  Method(_DSM, 4, Serialized) {
    //
    // Switch based on which unique function identifier was passed in
    //
    If (LEqual(Arg0, ToUUID ("E5C937D0-3553-4d7a-9117-EA4D19C3434D"))) {
      //
      // _DSM Definitions for Latency Tolerance Reporting
      //
      // Arguments:
      // Arg0: UUID: E5C937D0-3553-4d7a-9117-EA4D19C3434D
      // Arg1: Revision ID: 3
      // Arg2: Function Index: 0, 5, 8, 9
      // Arg3: Empty Package
      //
      // Switch by function index
      //
      Switch(ToInteger(Arg2)) {
        //
        // Function Index:0
        // Standard query - A bitmask of functions supported
        //
        Case (0) {
          Name(OPTS,Buffer(2){0,0})
          CreateBitField(OPTS,0,FUN0)
          CreateBitField(OPTS,5,FUN5)
          CreateBitField(OPTS,6,FUN6)
          CreateBitField(OPTS,8,FUN8)
          CreateBitField(OPTS,9,FUN9)

          Store(1,FUN0)
          Store (IORB, FUN5)
          if(LEqual(LTEN,1)) {
            Store(1,Fun6)
          }

          If (LGreaterEqual(Arg1, 2)){ // test Arg1 for Revision ID: 2
            If(CondRefOf(ECR1)) {
              if(LEqual(ECR1,1)){
                if (LGreaterEqual(Arg1, 3)){ // test Arg1 for Revision ID: 3
                  Store(1,Fun8)
                  Store(1,Fun9)
                }
              }
            }
          }
          Return (OPTS)
        }

        //
        // Function Index: 5
        // Ignore PCI Boot Configuration
        //
        Case(5) {
          If (LGreaterEqual(Arg1, 1)) { // test Arg1 for Revision ID: 1
            Return(1)
          }
        }

        //
        // Function Index: 6
        // LTR Extended Capability Structure
        //
        Case(6) {
          if (LGreaterEqual(Arg1, 2)){ // test Arg1 for Revision ID: 2
            Store(And(ShiftRight(LMSL,10),7), Index(LTRV, 0))
            Store(And(LMSL,0x3FF), Index(LTRV, 1))
            Store(And(ShiftRight(LNSL,10),7), Index(LTRV, 2))
            Store(And(LNSL,0x3FF), Index(LTRV, 3))
            Return (LTRV)
          }
        }

        Case(8) { //ECR ACPI additions for FW latency optimizations, DSM for Avoiding Power-On Reset Delay Duplication on Sx Resume
          If(CondRefOf(ECR1)) {
            if(LEqual(ECR1,1)){
              if (LGreaterEqual(Arg1, 3)) { // test Arg1 for Revision ID: 3
                return (1)
              }
            }
          }
        }
        Case(9) { //ECR ACPI additions for FW latency optimizations, DSM for Specifying Device Readiness Durations
          If(CondRefOf(ECR1)) {
            if(LEqual(ECR1,1)){
              if (LGreaterEqual(Arg1, 3)) { // test Arg1 for Revision ID: 3
                return(Package(5){50000,Ones,Ones,50000,Ones})
              }
            }
          }
        }
      } // End of switch(Arg2)
    } // End of if
    return (Buffer() {0x00})
  } // End of _DSM

  Device(PXSX)
  {
    Name(_ADR, 0x00000000)

    // NOTE:  Any PCIE Hot-Plug dependency for this port is
    // specific to the CRB.  Please modify the code based on
    // your platform requirements.

    Method(_PRW, 0) {
      Return(GPRW(0x69, 4)) // can wakeup from S4 state
    }
  }

  Method(_DSW, 3) {
    Store(Arg1, \_SB.PC00.TDM0.SD3C)                  // If entering Sx (Arg1 > 1), need to skip TCSS D3Cold & TBT RTD3/D3Cold.
    Store(Arg1, \_SB.PC00.TDM1.SD3C)                  // If entering Sx (Arg1 > 1), need to skip TCSS D3Cold & TBT RTD3/D3Cold.
    C2PM (Arg0, Arg1, Arg2, DCPM)
  }

  //
  // Additionally if the device is capable of waking up
  // the platform from a low power System state (S3 or S4), there is a _S0W and _PRW
  // associated with the device as well.
  //
  Method(_PRW, 0) {
    Return(GPRW(0x69, 4)) // can wakeup from S4 state
  }
  //
  // Sub-Method of _L61 Hot-Plug event
  // _L61 event handler should invoke this method to support HotPlug wake event from TBT RP
  //
  Method(HPEV,0,Serialized) {
    If(LAnd(LNotEqual(VDID,0xFFFFFFFF), HPSX)) {
      If(PDCX) {
        // Clear all status bits first.
        Store(1, PDCX)
        Store(1, HPSX)

        //
        // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
        // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
        // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
        // disabled on empty slots prior booting to OS.
        //
        If(LNot(PDSX)) {
          // The PCI Express slot is empty, so disable L0s on hot unplug
          //
          Store(0, L0SE)
        }
        // Perform proper notification to the OS.
        Notify(^,0)
      } Else {
        // False event.  Clear Hot-Plug Status
        // then exit.
        Store(1, HPSX)
      }
    }
  }

  //
  // Power Management routine for D3
  //
  Name(STAT, 0x1)  // Variable to save power state 1 - D0, 0 - D3C

  //
  // RTD3 Exit Method to bring TBT controller out of RTD3 mode.
  //
  Method(D3CX, 0, Serialized) {
    if(LEqual(STAT,0x1)) {
      Return
    }

    //
    // Set RTD3PFETDIS = 0
    //
    Store(0, RPFE)

    //
    // Set RTD3PERST = 0
    //
    Store(0, RPER)

    //
    // Set  L23r2dt = 1
    //
    Store(1, L23R)

    //
    // Poll for L23r2dt == 0. Wait for transition to Detect
    //
    Store(0, Local0)
    Store(L23R, Local1)
    While(Local1) {
      If(Lgreater(Local0, 20))
      {
        Break
      }
      Sleep(5)
      Increment(Local0)
      Store(L23R, Local1)
    }
    Store(0x1, STAT)

    //
    // Wait for LA = 1
    //
    Store(0, Local0)
    Store(LASX, Local1)
    While(LEqual(Local1,0)) {
      If(Lgreater(Local0, 20))
      {
        Break
      }
      Sleep(5)
      Increment(Local0)
      Store(LASX, Local1)
    }
  }

  //
  // RTD3 Entry method to enable TBT controller RTD3 mode.
  //
  Method(D3CE, 0, Serialized)      // D3Cold Entry
  {

    if(LEqual(STAT,0x0)) {
      Return
    }

    //
    // Set  L23er = 1
    //
    Store(1, L23E)

    //
    // Poll until L23er == 0
    //
    Store(0, Local0)
    Store(L23E, Local1)
    While(Local1) {
      If(Lgreater(Local0, 20))
      {
        Break
      }
      Sleep(5)
      Increment(Local0)
      Store(L23E, Local1)
    }


    Store(0, STAT) // D3Cold

    //
    // Set RTD3PFETDIS = 1
    //
    Store(1, RPFE)

    //
    // Set RTD3PERST = 1
    //
    Store(1, RPER)

  }

  Method(_PS0,0,Serialized)
  {
    If (LEqual(HPEX, 1)) {
      Store(0, HPEX) // Disable Hot Plug SCI
      Store(1, HPSX) // Clear Hot Plug SCI status
    }
    If (LEqual (PMEX, 1)) {
      Store(0, PMEX) // Disable Power Management SCI
      Store(1, PMSX) // Clear Power Management SCI status
    }
    Sleep(100) // Wait for 100ms before return to OS starts any DS activities
  }

  Method(_PS3,0,Serialized)
  {
    If (LEqual (HPEX, 0)) {
      Store(1, HPEX) // Enable Hot Plug SCI
      Store(1, HPSX) // Clear Hot Plug SCI status
    }
    If (LEqual(PMEX, 0)) {
      Store(1, PMEX) // Enable Power Management SCI
      Store(1, PMSX) // Clear Power Management SCI status
    }
  }

  Method (_DSD, 0) {
    Return (
      Package () {
        ToUUID("6211E2C0-58A3-4AF3-90E1-927A4E0C55A4"),
        Package () {
          Package (2) {"HotPlugSupportInD3", 1},
        },

        ToUUID("EFCC06CC-73AC-4BC3-BFF0-76143807C389"),
        Package () {
          Package (2) {"ExternalFacingPort", 1}, // Property 1: This is a TBT/CIO port
          Package (2) {"UID", TUID}, // Property 2: UID of the TBT RP on platform, range is: 0, 1, ..., NumOfTBTRP - 1
        }
      }
    ) // End of Return ()
  }
  //
  // Control the HotPlug and PME SCI
  // Agr0 : 0 - Disable the HotPlug and PME SCI
  //        1 - Enable the HotPlug and PME SCI
  //
  Method(CHPI, 1) {
    If (LEqual(Arg0, 0)) {
      If (LEqual(HPEX, 1)) {
        Store(0, HPEX) // Disable Hot Plug SCI
        Store(1, HPSX) // Clear Hot Plug SCI status
      }
      If (LEqual (PMEX, 1)) {
        Store(0, PMEX) // Disable Power Management SCI
        Store(1, PMSX) // Clear Power Management SCI status
      }
    } Else {
      If (LEqual (HPEX, 0)) {
        Store(1, HPEX) // Enable Hot Plug SCI
        Store(1, HPSX) // Clear Hot Plug SCI status
      }
      If (LEqual(PMEX, 0)) {
        Store(1, PMEX) // Enable Power Management SCI
        Store(1, PMSX) // Clear Power Management SCI status
      }
    }
  }

  //
  // The deepest D-state supported by this device in the S0 system sleeping state where the device can wake itself,
  // "4" represents D3cold.
  //
  Method(_S0W, 0x0, NotSerialized)
  {
    If (ITRT) {
      Return(0x4)
    } Else {
      Return(0x3)
    }
  }

  If (ITRT) {
    //
    // To evaluates to a list of power resources that are dependent on this device. For OSPM to "put
    // the device in" the D0 device state
    //
    Method(_PR0) {
      If (TRTD) {
        If (LOr(LEqual(TUID,0),LEqual(TUID,1))) {
          Return (Package(){\_SB.PC00.D3C, \_SB.PC00.TBT0})
        } Else { //ElseIf (LOr(LEqual(TUID,2),LEqual(TUID,3))) {
          Return (Package(){\_SB.PC00.D3C, \_SB.PC00.TBT1})
        }
      }
      If (LOr(LEqual(TUID,0),LEqual(TUID,1))) {
        Return (Package(){\_SB.PC00.TBT0})
      } //ElseIf (LOr(LEqual(TUID,2),LEqual(TUID,3))) {
      Return (Package(){\_SB.PC00.TBT1})
    }
    //
    // To evaluates to a list of power resources upon which this device is dependent when it is in the D3hot state.
    // The PMSS is in D3H when this method is called. For devices that support both D3hot and D3 exposed to OSPM via _PR3,
    // device software/drivers must always assume OSPM will target D3 and must assume all device context will be lost
    // and the device will no longer be enumerable.
    //
    Method(_PR3) {
      If (TRTD) {
        If (LOr(LEqual(TUID,0),LEqual(TUID,1))) {
          Return (Package(){\_SB.PC00.D3C, \_SB.PC00.TBT0})
        } Else {//ElseIf (LOr(LEqual(TUID,2),LEqual(TUID,3))) {
          Return (Package(){\_SB.PC00.D3C, \_SB.PC00.TBT1})
        }
      }
      If (LOr(LEqual(TUID,0),LEqual(TUID,1))) {
        Return (Package(){\_SB.PC00.TBT0})
      } //ElseIf (LOr(LEqual(TUID,2),LEqual(TUID,3))) {
      Return (Package(){\_SB.PC00.TBT1})
    }
  }

  //
  // PCI_EXP_STS Handler for PCIE Root Port
  //
  Method(HPME,0,Serialized) {
    If(LAnd(LNotEqual(VDID,0xFFFFFFFF), LEqual(PMSX,1))) { //if port exists and has PME SCI Status set...
      Notify (PXSX, 0x2) //notify child device; this will cause its driver to clear PME_Status from device
      Store(1,PMSX) // clear rootport's PME SCI status
      Store(1,PSPX) // consume one pending PME notification to prevent it from blocking the queue
      Return(0x01)
    }
    Return(0x00)
  }
  Name(PD01, Package(){
    Package(){0x0000FFFF, 0, 0, 11 },
    Package(){0x0000FFFF, 1, 0, 10 },
    Package(){0x0000FFFF, 2, 0, 11 },
    Package(){0x0000FFFF, 3, 0, 11 },
  })
  Name(AR01, Package(){
    Package(){0x0000FFFF, 0, 0, 16 },
    Package(){0x0000FFFF, 1, 0, 17 },
    Package(){0x0000FFFF, 2, 0, 18 },
    Package(){0x0000FFFF, 3, 0, 19 },
  })
  Method(_PRT,0) {
    If(CondRefOf(PICM)) {
      If(PICM) {Return(AR01)} // APIC mode
    }
    Return (PD01) // PIC Mode
  } // end _PRT
