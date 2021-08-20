/** @file
  Intel ACPI Reference Code for Dynamic Platform & Thermal Framework

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

Scope(\_SB)
{

  Device(BTY1)  // Battery Participant
  {
    Name(_HID, EISAID("INT3532")) //Intel DPTF Battery Participant
    Name(_UID, "BTY1")
    Name(_STR, Unicode ("Battery 1 Participant"))
    Name(PTYP, 0x0C)

    // _STA (Status)
    //
    // This object returns the current status of a device.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   An Integer containing a device status bitmap:
    //    Bit 0 - Set if the device is present.
    //    Bit 1 - Set if the device is enabled and decoding its resources.
    //    Bit 2 - Set if the device should be shown in the UI.
    //    Bit 3 - Set if the device is functioning properly (cleared if device failed its diagnostics).
    //    Bit 4 - Set if the battery is present.
    //    Bits 5-31 - Reserved (must be cleared).
    //
    Method(_STA)
    {
      If(LEqual(\PWRE,1)) {
        Return(0x0F)
      } Else {
        Return(0x00)
      }
    }

    // PMAX (Platform MAXimum)
    //
    // The PMAX object provides maximum power that can be supported by the battery in mW.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   maximum power in mW
    //
    Method(PMAX,0,Serialized)
    {
#ifdef EC_SUPPORT
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        // convert PMAX from signed to unsigned integer
        // PMAX Value = (NOT(OR(FFFF0000, ECValue))+1) * 10.
        Store(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.BMAX)),Local0)
        If(Local0){ // don't convert a zero
          Not(Or(0xFFFF0000,Local0,Local0),Local0) // make it a 32 bit value before inverting the bits
          Multiply(Add(1,Local0,Local0),10,Local0) // add 1 and multiply by 10
        }
        Return(Local0)
      } Else {
        Return(0) // EC not available
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

    // CTYP (Charger TYPe)
    //
    // The CTYP object provides charger type.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //  0x01 = Traditional
    //  0x02 = Hybrid
    //  0x03 = NVDC
    //
    Method(CTYP)
    {
#ifdef EC_SUPPORT
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.CTYP)
      } Else {
        Return(3)
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

    // PBSS (Power Battery Steady State)
    //
    // Returns max sustained power for battery.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   power in milliwatts
    //
    Method(PBSS)
    {
#ifdef EC_SUPPORT
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) {
        Store(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.PBSS)),Local0)
        Return(Local0)
      }
      Return(100)
#endif
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

    // DPSP (DPTF Power Sampling Period)
    //
    // Sets the polling interval in 10ths of seconds. A value of 0 tells the driver to use event notification for PMAX and PBSS..
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   An Integer containing the polling rate in tenths of seconds.
    //   A value of 0 will specify using interrupts through the ACPI notifications.
    //
    //   The granularity of the sampling period is 0.1 seconds. For example, if the sampling period is 30.0
    //   seconds, then report 300; if the sampling period is 0.5 seconds, then will report 5.
    //
    Method(DPSP,0,Serialized)
    {
      Return(\PPPR)
    }

    // RBHF
    //
    // The high frequency impedance value that can be obtained from battery fuel gauge.
    // The unit is 1mOhm.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Impedance Value
    //
    Method(RBHF, 0, Serialized)
    {
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

	// CMPP
    //
    // The battery discharge current capability for at least 1ms, in 1mA unit
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Battery discharge current value
    //
    Method(CMPP, 0, Serialized)
    {
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

	// VBNL
    //
    // The battery_no-load voltage that can be obtained from battery fuel gauge.
    // The unit is 1mV. DPTF reads this value during UVTH calculation.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Battery_no-load voltage value
    //
    Method(VBNL, 0, Serialized)
    {
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

  } // End Battery Participant
}// end Scope(\_SB)
