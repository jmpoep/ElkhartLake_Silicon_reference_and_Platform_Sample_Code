/** @file
  ACPI EcLite Device Specific method implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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

  External(\_SB.TPWR, DeviceObj)
  External(\_SB.BTY1, DeviceObj)
  External(\_SB.BTY2, DeviceObj)

  Method(_DSM, 0x4, Serialized, 0, {IntObj, BuffObj}, {BuffObj, IntObj, IntObj, PkgObj})
  {
    //
    //  Intel Proprietary EcLite Event Reporting
    //
    If (LEqual(Arg0, ToUUID("91D936A7-1F01-49C6-A6B4-72F00AD8D8A5")))
    {
      Switch (ToInteger (Arg2))            // Switch to Function Index.
      {
        //
        // Function 0, Query Function - return supported functions BitIndex.
        //
        Case (0)
        {
          // Revision 0
          If (LEqual(Arg1, Zero)) // The current revision is 0
          {
            Return(Buffer(){0x01, 0x20, 0x00, 0x00})
          }
          Else
          {
            Return(0) // Revision mismatch
          }
        }

        //
        // Power participant notifications
        //
        Case (ToInteger (ECLITE_CHARGER_CONNECT_EVENT))
        {
          // Set Global Power State = Charger Mode.
          Store(ECLITE_AC_PRESENT,PWRS)

          // Perform needed ACPI Notifications.
          If(LAnd(LEqual(DPTF,1), LEqual(PWRE,1))) {
            Notify(\_SB.TPWR, 0x81) // notify Power participant
          }

          PNOT()
          Return(0)
        }

        Case (ToInteger (ECLITE_CHARGER_DISCONNECT_EVENT))
        {
          // Set Global Power State = Battery Mode.
          Store(ECLITE_DC_PRESENT,PWRS)

          // Perform needed ACPI Notifications.
          If(LAnd(LEqual(DPTF,1), LEqual(PWRE,1))) {
            Notify(\_SB.TPWR, 0x81) // notify Power participant
          }

          PNOT()
          Return(0)
        }

        Case (ToInteger (ECLITE_BATTERY_EVENT))
        {
          If(LAnd(LEqual(DPTF,1), LEqual(PWRE,1)))
          {
            Notify(\_SB.TPWR, 0x86) // notify Power participant
          }
          PNOT()
          Return(0)
        }

        Case (ToInteger (ECLITE_PMIC_TEMP_ALERT))
        {
          If(LAnd(LEqual(DPTF,1), LEqual(S1DE,1)))
          {
            ADBG("Sensor 1")
            Notify(\_SB.SEN1, 0x90) // notify Sensor participant
          }
          Return(0)
        }

        Case (ToInteger (ECLITE_SYSTEM0_TEMP_ALERT))
        {
          If(LAnd(LEqual(DPTF,1), LEqual(S2DE,1)))
          {
            ADBG("Sensor 2")
            Notify(\_SB.SEN2, 0x90) // notify Sensor participant
          }
          Return(0)
        }

        Case (ToInteger (ECLITE_SYSTEM1_TEMP_ALERT))
        {
          If(LAnd(LEqual(DPTF,1), LEqual(S3DE,1)))
          {
            ADBG("Sensor 3")
            Notify(\_SB.SEN3, 0x90) // notify Sensor participant
          }
          Return(0)
        }

        Case (ToInteger (ECLITE_BATTERY1_TEMP_ALERT))
        {
          If(LAnd(LEqual(DPTF,1), LEqual(S4DE,1)))
          {
            ADBG("Sensor 4")
            Notify(\_SB.SEN4, 0x90) // notify Sensor participant
          }
          Return(0)
        }

        Case (ToInteger (ECLITE_BATTERY2_TEMP_ALERT))
        {
          If(LAnd(LEqual(DPTF,1), LEqual(S5DE,1)))
          {
            ADBG("Sensor 5")
            Notify(\_SB.SEN5, 0x90) // notify Sensor participant
          }
          Return(0)
        }

        Case (ECLITE_PSRC_CHANGE_EVENT)
        {
          \_SB.ECLT.ECLC(ECLITE_READ_COMMAND, ECLITE_DEFAULT_UPDATE, ECLITE_PSRC_OFFSET, ECLITE_BYTES_COUNT_2)
          Store(\_SB.ECLT.ECLR(RefOf(\_SB.ECLT.PSRC)), Local0)
          If(LNotEqual(And(ToInteger(Local0),ECLITE_PSRC_BIT_MASK),ECLITE_DC_PRESENT))
          {
            Store(ECLITE_AC_PRESENT,PWRS)
          }
          Else
          {
            Store(ECLITE_DC_PRESENT,PWRS)
          }

          // Perform needed ACPI Notifications.
          PNOT()

          If(LAnd(LEqual(DPTF,1), LEqual(PWRE,1)))
          {
            Notify(\_SB.TPWR, 0x81) // notify Power participant
          }
          Return(0)
        }

        Case (ECLITE_BATTERY_CYCLE_COUNT_EVENT)
        {
          If(LAnd(LEqual(DPTF,1), LEqual(PWRE,1)))
          {
            Notify(\_SB.TPWR, 0x82) // notify Power participant
          }
          Return(0)
        }

        Default
        {
          Return(0) // Function number mismatch but normal return.
        }
      } // End Function Index
    } // Guid Check

    If (LEqual(Arg0, ToUUID ("EEEC56B3-4442-408F-A792-4EDD4D758054")))
    {
      If (LEqual (1, ToInteger (Arg1)))        // Revision 1.
      {
        Switch (ToInteger (Arg2))            // Switch to Function Index.
        {
          //
          // Function 0, Query of supported functions.
          //
          Case (0)
          {
            Return (Buffer () {0xBF, 0x02}) // Total 6 function indices are supported including this.
          }
          //
          // Function 1, BTNL. Button Load Method. No Input/Output.
          //
          Case (1)
          {
            \_SB.HIDD.BTNL ()
          }
          //
          // Function 2, HDMM. HID Driver Mode Method.
          // Input:None
          // Output:HDMM output. See HDMM
          //
          Case (2)
          {
            Return (\_SB.HIDD.HDMM ())
          }
          //
          // Function 3, HDSM. HID Driver Status Method.
          // Input: 0 - The driver is not available. 1 - The driver is available.
          // Output: None
          //
          Case (3)
          {
            \_SB.HIDD.HDSM (DeRefOf (Index (Arg3, 0)))
          }
          //
          // Function 4, HDEM. HID Driver Event Method.
          // Input: None.
          // Output: Package contains Supported Keys (Mode 0)
          //
          Case (4)
          {
            Return (\_SB.HIDD.HDEM ())
          }
          //
          // Function 5 BTNS. Button Status Method.
          // Input: None.
          // Output: Int32 which contains a bit map of Buttons' enable/disable states
          //
          Case (5)
          {
            Return (\_SB.HIDD.BTNS ())
          }
          //
          // Function 7 HEBC. Button implemented state.
          // Input: None
          // Output: Int32 Bit map which shows what buttons are implemented on this system.
          //
          Case (7)
          {
            Return (\_SB.HIDD.HEBC ())
          }
          //
          // Function 9 H2BC. Button implemented state.
          // Input: None
          // Output: Int32 Bit map which shows what buttons are implemented on this system.
          //
          Case (9)
          {
            Return (\_SB.HIDD.H2BC ())
          }
        } // End Switch statement
      }  // End Revision check
    }  // End UUID check

    // If the code falls through to this point, just return a buffer of 0.

    Return (Buffer() {0x00})
  } // End of Method(_DSM, 0x4, Serialized, 0, {IntObj, BuffObj}, {BuffObj, IntObj, IntObj, PkgObj})

