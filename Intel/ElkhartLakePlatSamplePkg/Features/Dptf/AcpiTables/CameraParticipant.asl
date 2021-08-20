/** @file
  Intel ACPI Reference Code for Dynamic Platform & Thermal Framework

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

  Device(CAM1)  // 2D Camera participant
  {
    Name(_HID, EISAID("INT340B"))
    Name(_UID, "CAM1")
    Name(_STR, Unicode ("2D Camera"))
    Name(PTYP, 0x1B)

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
      If (LEqual(\CA2D,1)) {
        Return(0x0F)
      } Else {
        Return(0x00)
      }
    }

    // PPSS (Participant Performance Supported States)
    //
    // This object evaluates to a packaged list of information about available power performance states.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Package of packages
    //
    Name (PPSS, Package()
    {
      Package ()     // Zeroth Power/Performance State
      {
        100,         // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        100,         // DWordConst: Control
        30,          // DWordConst: RawPerformance
        "FPS",       // String: RawUnit Frames Per Second
        0            // DWordConst: Reserved1
      },

      Package ()     // Power/Performance State
      {
        80,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        80,          // DWordConst: Control
        24,          // DWordConst: RawPerformance
        "FPS",       // String: RawUnit Frames Per Second
        0            // DWordConst: Reserved1
      },

      Package ()     // Power/Performance State
      {
        60,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        60,          // DWordConst: Control
        18,          // DWordConst: RawPerformance
        "FPS",       // String: RawUnit Frames Per Second
        0            // DWordConst: Reserved1
      },

      Package ()     // Power/Performance State
      {
        40,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        40,          // DWordConst: Control
        12,          // DWordConst: RawPerformance
        "FPS",       // String: RawUnit Frames Per Second
        0            // DWordConst: Reserved1
      },

      Package ()     // Power/Performance State
      {
        20,          // DWordConst: Performance
        0,           // DWordConst: Power
        0,           // DWordConst: TransitionLatency
        0,           // Boolean DWordConst : Linear
        20,          // DWordConst: Control
        6,           // DWordConst: RawPerformance
        "FPS",       // String: RawUnit Frames Per Second
        0            // DWordConst: Reserved1
      }
    })

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
        Return(0)
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
      Return(100)
    }

  } // End 2D Camera participant
}// end Scope(\_SB)

