/** @file
  Intel ACPI Reference Code for Dynamic Platform & Thermal Framework

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#ifdef EC_SUPPORT
Scope(\_SB.PC00.LPCB.H_EC)
#endif
#ifdef ECLITE_PSE_SUPPORT
Scope(\_SB)
#endif
{

  Device(CHRG)  // Charger participant
  {
#ifdef ECLITE_PSE_SUPPORT
    Name (_DEP, Package() {\_SB.ECLT})
#endif //ECLITE_PSE_SUPPORT
    Name(_HID, EISAID("INT3403"))
    Name(_UID, "CHRG")
    Name(_STR, Unicode ("Charger"))
    Name(PTYP, 0x0B)

    // PFLG
    //   0 - Default, participant is on the main board
    //   1 - Participant device is on the docking station
    //   2 - Participant device is on the detachable base
    //   3 - Participant device is an external device (such as a USB device, DPTF does not support this type of device today)
    Name(PFLG, 0)

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
      If (LEqual(\CHGE,1)) {
        Return(0x0F)
      } Else {
        Return(0x00)
      }
    }

    Name(PSSS, 0) // Participant Performance Supported States (PPSS) packge size

    // PPSS (Participant Performance Supported States)
    //
    // This object evaluates to a packaged list of information about available power performance states.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Package of packages
    //
    Name (PPS1, Package()
    {
      Package ()     // Zeroth Power/Performance State
      {
        100,         // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        0,           // DWordConst: Control
        3500,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        85,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        1,           // DWordConst: Control
        3000,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        71,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        2,           // DWordConst: Control
        2500,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        57,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        3,           // DWordConst: Control
        2000,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        42,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        4,           // DWordConst: Control
        1500,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        28,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        5,           // DWordConst: Control
        1000,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        14,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        6,           // DWordConst: Control
        500,         // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Last Power/Performance State
      {
        0,           // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        7,           // DWordConst: Control
        0,           // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      }
    })

    Name (PPS2, Package()  // Fast Charging Enabled.
    {
      Package ()     // Zeroth Power/Performance State
      {
        100,         // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        0,           // DWordConst: Control
        4500,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        88,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        1,           // DWordConst: Control
        4000,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        77,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        2,           // DWordConst: Control
        3500,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        66,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        3,           // DWordConst: Control
        3000,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        55,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        4,           // DWordConst: Control
        2500,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        44,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        5,           // DWordConst: Control
        2000,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Power/Performance State
      {
        33,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        6,           // DWordConst: Control
        1500,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Last Power/Performance State
      {
        22,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        7,           // DWordConst: Control
        1000,        // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
#ifdef EC_SUPPORT
      Package ()     // Last Power/Performance State
      {
        11,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        8,           // DWordConst: Control
        500,         // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Last Power/Performance State
      {
        0,           // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        9,           // DWordConst: Control
        0,           // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      Package ()     // Last Power/Performance State
      {
        11,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        7,           // DWordConst: Control
        500,         // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      },
      Package ()     // Last Power/Performance State
      {
        0,           // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        7,           // DWordConst: Control
        0,           // DWordConst: RawPerformance
        "MilliAmps", // String: RawUnit
        0            // DWordConst: Reserved1
      }
#endif //ECLITE_PSE_SUPPORT
    })

    Method(PPSS, 0, Serialized, ,PkgObj)
    {
#ifdef EC_SUPPORT
      If (LEqual(ECRD(RefOf(FCHG)), 1)) { // Check Fast Charging is Enabled
        Return (PPS2)
      } Else {
        Return (PPS1)
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      Return (PPS1)
#endif //ECLITE_PSE_SUPPORT
    }

    // PCAL
    //
    // Calculate the size of the PPSS package object and updates the global object that stores it.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   None
    Method(PCAL, 0, Serialized)
    {
#ifdef EC_SUPPORT
      If (LEqual(ECRD(RefOf(FCHG)), 1)) { // Check Fast Charging is Enabled
        Store(SizeOf(PPS2), PSSS)
      } Else {
#endif
        Store(SizeOf(PPS1), PSSS)
#ifdef EC_SUPPORT
      }
#endif
    }

    // PPPC (Participant Performance Present Capabilities)
    //
    // PPPC evaluates to an integer that will indicate the maximum allowable P-State for OSPM
    // to use at any given time.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   P states
    //
    Method(PPPC, 0)
    {
      PCAL() // Calculate the size of the relevant PPSS package.
      If (\PWRS) { // return 0 for AC, Pn for DC
        Return(0)
      } Else {
        Return(Subtract(PSSS,1))
      }
    }

    // SPPC (Set Participant Performance Capability)
    //
    // SPPC is a control method object that takes one integer parameter that will indicate the maximum
    // allowable P-State for OSPM to use at any given time.
    //
    // Arguments: (1)
    //   Arg0 - integer
    // Return Value:
    //   None
    //
    Method(SPPC,1,Serialized)
    {
      PCAL() // Calculate the size of the relevant PPSS package.

      // BIOS translates P-state to charge amps and writes CMD/DATA to EC
      If (LLessEqual(ToInteger(Arg0), Subtract(PSSS, 1))) { // bounds check requested P-state
#ifdef EC_SUPPORT
        If (LEqual(ECRD(RefOf(FCHG)), 1)) { // Check Fast Charging is Enabled
          Store(DeRefOf(Index(DeRefOf(Index(PPS2,Arg0)),5)),Local1) // get Charge Rate amp value
        } Else {
          Store(DeRefOf(Index(DeRefOf(Index(PPS1,Arg0)),5)),Local1) // get Charge Rate amp value
        }
        \_SB.PC00.LPCB.H_EC.ECWT(Local1, RefOf(\_SB.PC00.LPCB.H_EC.CHGR)) // write amp value to EC
        \_SB.PC00.LPCB.H_EC.ECMD(0x37) // Set Charge Rate
#endif
#ifdef ECLITE_PSE_SUPPORT
       Store(DeRefOf(Index(DeRefOf(Index(PPS1,Arg0)),5)),Local0) // get Charge Rate amp value
       \_SB.ECLT.ECLW(Local0, RefOf(\_SB.ECLT.C1IN ))
       \_SB.ECLT.ECLC(ECLITE_WRITE_COMMAND, ECLITE_CHARGER_UPDATE, ECLITE_C1IN_OFFSET, ECLITE_BYTES_COUNT_2)
#endif //ECLITE_PSE_SUPPORT
      }
    }

    // PPDL (Participant P-state Depth Limit)
    //
    // Indicates dynamically a lower limit on the number of control states currently supported.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   An Integer containing the P-state Depth Limit _PSS entry number:
    //   0 - P0 is the only P-state available for OSPM use
    //   1 - state 1 is the lowest power P-state available
    //   2 - state 2 is the lowest power P-state available
    //   n - state n is the lowest power P-state available
    //
    Method(PPDL, 0)
    {
      PCAL() // Calculate the size of the relevant PPSS package.
      Return(Subtract(PSSS,1))
    }

  } // End CHRG Device
}// end Scope(\_SB.PC00.LPCB.H_EC) or Scope(\_SB)

