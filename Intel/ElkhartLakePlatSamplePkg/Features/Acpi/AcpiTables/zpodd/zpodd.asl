/** @file

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


DefinitionBlock (
  "zpodd.aml",
  "SSDT",
  2,
  "AcpiRf",
  "zpodd",
  0x1000
  )
{
  External(\_SB.PC00.SAT0.PRT1, DeviceObj)
  External(\_SB.PC00.SAT0.PRT3, DeviceObj)
  External(RCG0, IntObj)                   // RTD3 Config Setting(BIT0:ZPODD,BIT1:USB Camera Port4, BIT2/3:SATA Port3)
  External(\ZPOD)

  // GPIO methods
  External(\_SB.GGIV, MethodObj)
  External(\_SB.SGOV, MethodObj)
  External(\_SB.GGII, MethodObj)
  External(\_SB.SGII, MethodObj)

  If (LAnd(And(RCG0,1), 1)) {
    Scope(\_SB.PC00.SAT0.PRT1) {
      //
      // _DSM Device Specific Method supporting SATA ZPODD function
      //
      // Arg0: UUID Unique function identifier
      // Arg1: Integer Revision Level
      // Arg2: Integer Function Index
      // Arg3: Package Parameters
      //
      Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj}) {
        If (LEqual(Arg0, ToUUID ("bdfaef30-aebb-11de-8a39-0800200c9a66"))) {
          //
          // Switch by function index
          //
          Switch (ToInteger(Arg2)) {
            //
            // Standard query - A bitmask of functions supported
            // Supports function 0-3
            //
            Case (0) {
              Switch(ToInteger(Arg1)) {
                Case(1) {
                  Switch (ToInteger (ZPOD)) {
                    Case ( Package () {1,2,3}) {
                      Return (Buffer () {0xF})
                    }
                    Default {
                      Return (Buffer () {0})
                    }
                  }
                }
                Default {
                  Return (Buffer () {0})
                }
              }
            }

            //
            // Enable ZPODD feature
            //
            Case (1) {
              //
              // Enable Power ON/OFF
              //
              Return (1)
            }

            //
            // Power Off Device
            //
            Case (2) {
              Switch (ToInteger (ZPOD)) {
                Case ( Package () {1}) {
                }

                Case ( Package () {2,3}) {
                  //
                  // Drive GPP_G_1_FAN_TACH_1 to low to power off device.
                  //
                }

              }
              Return (1)
            }

            //
            // Power ON Device
            //
            Case (3) {
              Switch (ToInteger (ZPOD)) {
                Case ( Package () {1}) {

                }

                Case ( Package () {2}) {
                  //
                  // Drive GPP_G_1_FAN_TACH_1 to high to power on device,
                  // only when ODD is detected
                  //
                }

                Case ( Package () {3}) {
                  //
                  // Drive GPP_G_1_FAN_TACH_1 to high to power on device,
                  // only when ODD is detected
                  //
                }

              }
              Sleep(10)
              Return (1)
            }

            Default {
              Return (0)
            }
          }
        } Else {
          Return (Buffer() {0})
        }
      }  // _DSM()
    } // \_SB.PC00.SAT0.PRT1

    Scope(\_SB.PC00.SAT0.PRT3) {
      //
      // _DSM Device Specific Method supporting SATA ZPODD function
      //
      // Arg0: UUID Unique function identifier
      // Arg1: Integer Revision Level
      // Arg2: Integer Function Index
      // Arg3: Package Parameters
      //
      Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj}) {
        If (LEqual(Arg0, ToUUID ("bdfaef30-aebb-11de-8a39-0800200c9a66"))) {
          //
          // Switch by function index
          //
          Switch (ToInteger(Arg2)) {
            //
            // Standard query - A bitmask of functions supported
            // Supports function 0-3
            //
            Case (0) {
              Switch(ToInteger(Arg1)) {
                Case(1) {
                  Switch (ToInteger (ZPOD)) {
                    Case ( Package () {1,2,3}) {
                      Return (Buffer () {0xF})
                    }

                    Default {
                      Return (Buffer () {0})
                    }
                  }
                }
                Default {
                  Return (Buffer () {0})
                }
              }
            }

            //
            // Enable ZPODD feature
            //
            Case (1) {
              //
              // Enable Power ON/OFF
              //
              Return (1)
            }

            //
            // Power Off Device
            //
            Case (2) {
              Switch (ToInteger (ZPOD)) {
                Case ( Package () {1}) {
                }

                Case ( Package () {2,3}) {
                  //
                  // Drive GPP_G_1_FAN_TACH_1 to low to power off device.
                  //
                }

              }
              Return (1)
            }

            //
            // Power ON Device
            //
            Case (3) {
              Switch (ToInteger (ZPOD)) {
                Case ( Package () {1}) {
                }

                Case ( Package () {2}) {
                  //
                  // Drive GPP_G_1_FAN_TACH_1 to high to power on device,
                  // only when ODD is detected
                  //
                }

                Case ( Package () {3}) {
                  //
                  // Drive GPP_G_1_FAN_TACH_1 to high to power on device,
                  // only when ODD is detected
                  //
                }

              }
              Sleep(10)
              Return (1)
            }

            Default {
              Return (0)
            }
          }
        } Else {
          Return (Buffer() {0})
        }
      }  // _DSM()
    } // \_SB.PC00.SAT0.PRT3
  }
}

