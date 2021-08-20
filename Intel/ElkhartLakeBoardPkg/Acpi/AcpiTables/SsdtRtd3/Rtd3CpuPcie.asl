/** @file
  ACPI RTD3 SSDT table for CPU PCIe(DEKEL PHY)

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

/// @details
/// Code in this file uses following variables:
/// SCLK: ICC Clock number - optional
/// WAKG: WAKE GPIO pad - optional
/// Below objects should be defined according to the format described in PinDriverLib.asl
/// RSTG: reset pin definition - mandatory
/// PWRG: power GPIO pad - optional
/// WAKP: Flag to indicate that power gating must not be performed if WAKE is enabled - optional
/// @defgroup pcie_scope PCIe Root Port Scope **/

//
// AcpiPinDriverLib imports(from DSDT in platform)
//
External(\PIN.STA, MethodObj)
External(\PIN.ON, MethodObj)
External(\PIN.OFF, MethodObj)
//
// GpioLib imports(DSDT)
//
External(\_SB.SHPO, MethodObj)

//
// External decalarations for optional objects.
// Defined by board specific code.
//
External(WAKG)
External(PWRG)
External(SCLK)
External(WAKP)

// WAKE enable on PCIe device.
Name(WKEN, 0)

Name(_S0W, 3)

Method(_DSW, 3)
{
/// This method is used to enable/disable wake from PCIe (WKEN)
  If(Arg1)
  { /// If entering Sx, need to disable WAKE# from generating runtime PME
    Store(0, WKEN)
  } Else {  /// If Staying in S0
    If(LAnd(Arg0, Arg2)) ///- Check if Exiting D0 and arming for wake
    { ///- Set PME
      Store(1, WKEN)
    } Else { ///- Disable runtime PME, either because staying in D0 or disabling wake
      Store(0, WKEN)
    }
  }

/** @defgroup pcie_dsw PCIE _DSW **/
} // End _DSW

//
// PCIe slot power resource definition
//
PowerResource(PXP, 0, 0) {
  Method(_STA, 0) {
    If (LEqual (VDID, 0xFFFFFFFF)) {
      Return(0)
    }
    Return(PSTA())
  }

  Method(_ON) {
    If (LEqual (VDID, 0xFFFFFFFF)) {
      Return()
    }

    //
    // Turn on slot power
    //
    PON()

    //
    // Trigger L2/L3 ready exit flow in rootport - transition link to Detect
    //
    L23D()
  }

  Method(_OFF) {
    If (LEqual (VDID, 0xFFFFFFFF)) {
      Return()
    }

    //
    // Trigger L2/L3 ready entry flow in rootport
    //
    DL23()

    //
    // Turn off slot power
    //
    POFF()
  }
}

// Returns the status of PCIe slot core power
Method(PSTA, 0) {
  //
  // RESET# assertion is mandatory for PCIe RTD3
  // So if RESET# is asserted the whole slot is off
  //
  If(\PIN.STA(RSTG)) {
    Return(0)
  } Else {
    Return (1)
  }
}

// Turn on power to PCIe Slot
// Since this method is also used by the remapped devices to turn on power to the slot
// this method should not make any access to the PCie config space.
Method(PON) {

  // Turn ON Power for PCIe Slot
  If(CondRefOf(PWRG)) {
    \PIN.ON(PWRG)
    Sleep(PEP0)
  }

  If(CondRefOf(SCLK)) {
    SPCO(SCLK, 1)
  }

  // De-Assert Reset Pin
  \PIN.OFF(RSTG)
}

// Turn off power to PCIe Slot
// Since this method is also used by the remapped devices to turn off power to the slot
// this method should not make any access to the PCIe config space.
Method(POFF) {

  // Assert Reset Pin
  // Reset pin is mandatory for correct PCIe RTD3 flow
  \PIN.ON(RSTG)

  //
  // On RTD3 entry, BIOS will instruct the PMC to disable source clocks.
  // This is done through sending a PMC IPC command.
  //
  If(CondRefOf(SCLK)) {
    SPCO(SCLK, 0)
  }

  // Power OFF for Slot
  If(CondRefOf(PWRG)) {
    // If WAKP has not been defined we can safely disable power.
    // If WAKP is defined this slot does not supply device with auxilary power and we have to keep primary power
    // to allow for WAKE. If WAKP is not equal to 0 and WKEN has been enabled do not disable the power.
    If(CondRefOf (WAKP)) {
      If(LOr(LEqual(WAKP, 0), LNot(WKEN))) {
        \PIN.OFF(PWRG)
      }
    } Else {
      \PIN.OFF(PWRG)
    }
  }

  // enable WAKE
  If(CondRefOf (WAKG)) {
    If(LAnd(LNotEqual(WAKG, 0), WKEN)) {
      \_SB.SHPO(WAKG, 0)
    }
  }
}

Method(_PR0) {
  Return(Package(){PXP})
}

