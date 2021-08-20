/** @file
  This file provides the ACPI interface for Intel Ready Mode Technology(IRMT)

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

DefinitionBlock (
  "IrmtAcpi.aml",
  "SSDT",
  2,
  "Intel_",
  "IrmtTabl",
  0x1000
  )

{
  External(IRMC) // Irmt Configuration
  External(\_SB.PC00.GFX0.TCHE)                 // Technology enabled indicator
  External(\_SB.PC00.GFX0.STAT)                 // State Indicator


  Scope (\_SB) {
    Device (AOAA) {
      Name (_HID, "INT3398")

      Name (NSMD, 0x00)  // Used to store mode settings:
      /**
        Bits        Description
        - (1:0)     00: Leave Never Sleep Mode;
                    01: Enter Never Sleep Mode.
                    10: Power Reduction Mode
                    11: Enter Do Not Disturb mode.
        - (7:2)     Reserved: Set to 0.
      **/

      Method (_STA, 0)
      {
        //
        //The Intel RMT ACPI device is a hidden device and
        //listed under system devices on Device Manager.
        //
        Return (0x0B)
      }

      /**
        GNSC - Get Never Sleep Configuration
        Input:   None
        Return:
        Bits    Description
        - 0      State(Never Sleep Enabling Status in BIOS): 0 = Disabled, 1 = Enabled
        - 1      Notification(Hardware notification enabling status): 0 = Unsupported, 1 = Supported
        - (7:2)  Reserved: Set to 0.
      **/
      Method (GNSC, 0, NotSerialized, 0, IntObj) {
        Return (IRMC)
      }

      /**
        GNSM - Get Never Sleep Mode
        Input:   None
        Return:
        Bits        Description
        - (1:0)     00: Leave Never Sleep Mode;
                    01: Enter Never Sleep Mode.
                    10: Power Reduction Mode
                    11: Enter Do Not Disturb mode.
        - (7:2)     Reserved: Set to 0.
      **/
      Method (GNSM, 0, NotSerialized, 0, IntObj) {
        Return (NSMD)
      }

      /**
        SNSM - Set Never Sleep Mode
        Input:
        Bits        Description
        - (1:0)     00: Leave Never Sleep Mode;
                    01: Enter Never Sleep Mode.
                    10: Power Reduction Mode
                    11: Enter Do Not Disturb mode.
        - (7:2)     Reserved: Set to 0.
        Return:
      **/
      Method (SNSM, 1, NotSerialized, 0, UnknownObj, IntObj) {
        And(Arg0, 0x3, NSMD)
      }

    } // Device (AOAA)
  } // Scope (\_SB)
} // End SSDT
