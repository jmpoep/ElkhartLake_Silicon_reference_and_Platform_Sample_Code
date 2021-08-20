/** @file
  This file contains the TCSS XDCI ASL code.
  It defines a Power Management for TCSS XDCI

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

  //
  // The deepest D-state supported by this device in the S0 system sleeping state where the device can wake itself,
  // "4" represents D3cold.
  //
  Method(_S0W, 0x0, NotSerialized)
  {
//     If (TRTD) {
//       Return(0x4)
//     } Else {
      Return(0x3)
//     }
  }
//  //
//  // Power Management routine for D3
//  //
//  If (TRTD) {
//    // To evaluates to a list of power resources that are dependent on this device. For OSPM to "put
//    // the device in" the D0 device state
//    Method(_PR0) {
//      Return (Package(){\_SB.PC00.D3C})
//    }
//    // To evaluates to a list of power resources upon which this device is dependent when it is in the D3hot state.
//    // The PMSS is in D3H when this method is called. For devices that support both D3hot and D3 exposed to OSPM via _PR3,
//    // device software/drivers must always assume OSPM will target D3 and must assume all device context will be lost
//    // and the device will no longer be enumerable.
//    Method(_PR3) {
//      Return (Package(){\_SB.PC00.D3C})
//    }
//  }

  Include("XdciOp.asl")

  //
  // Arg0: UUID = {732b85d5-b7a7-4a1b-9ba0-4bbd00ffd511}
  // Arg1: Revision ID = 1
  // Arg2: Function Index
  // Arg3: Argument
  // Method similar to the PCH xDCI _DSM
  //
  Method(_DSM,4,Serialized)
  {
    If(PCIC(Arg0)) { Return(PCID(Arg0,Arg1,Arg2,Arg3)) }

    If(LEqual(Arg0, ToUUID("732b85d5-b7a7-4a1b-9ba0-4bbd00ffd511"))){
      If(Lequal(Arg1, 1)){
        //
        // Set PMU Power State
        // Arg0: 0x00 PMU should enter the D0 power state.
        //       0x03 PMU should enter the D3 power state.
        // Arg1: 0x03 Enable PMU PME
        //       0x00 Clear PMU PME
        //
        Method (SPPT,2,Serialized) {

          // Local 1 is power state D0 or D3
          Store(Arg0, Local1)
          // Local 2 is Enable/Clear PMU PME
          Store(Arg1, Local2)

          If(LEqual(Local1, 0)){
            // Clear PMU PME
            // 0x10F81C BIT3: USB3 PME
            // 0x10F81C BIT4: USB2 PME
            Store(0, UXPE)
            // Wait for at least 100us, currently configured to 1000us
            Store(0, Local0)
            While(LLess(Local0, 10)){
              Stall(100)
              Increment(Local0)
            }
            // Set PMU to D0 by writing 0 to 0x10f818 Bit 1:0
            Store(0, PUPS)
            // Wait 200ms for PMU to enter D0
            // Confirm PMU being in D0 by checking 0x10f810 Bit 11:8 to be clear
            // 0x10f810 Bit 11:10 - Current power state of USB3 core
            // 0x10f810 Bit 9:8 - Current power state of USB2 core
            // both should be clear
            Store(0,Local0)
            While(LLess(Local0,2000)){
              Stall(100)
              If(LAnd(LEqual(U2CP,0),LEqual(U3CP,0))){
                break
              }
            Increment(Local0)
            }
            If(LNotEqual(U2CP, 0)){
              // Show warning message
            }
            If(LNotEqual(U3CP, 0)){
              // Show warning message
            }
            Return(0)
          }

          If(LEqual(Local1, 3)){
            // PMU should be in D0 at this point
            // 0x10f810 Bit 11:10 - current power state of USB3 core
            // 0x10f810 Bit 9:8   - current power state of USB2 core
            // both should be clear
            If(LNotEqual(U2CP, 0)){
              // Show warning message
            }
            If(LNotEqual(U3CP, 0)){
              // Show warning message
            }
            // Set PMU to D3 by writing 3 to 0x10f818 bit 1:0
            Store(3, PUPS)
            // Wait 200ms for PMU to enter D3
            // Confirm PMU being in D3 by checking 0x10f810 Bit 11:8 to be set
            // 0x10f810 Bit 11:10 - Current power state of USB3 core
            // 0x10f810 Bit 9:8 - Current power state of USB2 core
            // both should be set
            Store(0,Local0)
            While(LLess(Local0,2000)){
              Stall(100)
              If(LAnd(LEqual(U2CP,3),LEqual(U3CP,3))){
                break
              }
              Increment(Local0)
            }
            If(LNotEqual(U2CP, 3)){
              // Show warning message
            }
            If(LNotEqual(U3CP, 3)){
              // Show warning message
            }
            // Set/Clear PMU PME
            // 0x10F81C BIT3: USB3 PME
            // 0x10F81C BIT4: USB2 PME
            Store(Local2, UXPE)
            Return(0)
          }
          Return(0)
        }

      Switch(ToInteger(Arg2)) {
        Case(0){
          //
          // Function 0: return Bit map to indicate Function 0,1,4,5,6,7,8,9 supported
          //
          Return(Buffer(){0xF3, 0x03})
        }
        Case(1){
          //
          // Function 1: Attach/Detach and Port Detection Properties Method
          // This method is called by the USB function stack to set the power state of the PMU.
          // Bit 0 as 1: to indicate Platform support for Attach/detach notify
          // Bit 1 as 0:HW based charging indication
          //
          Return(0x1)
        }
        Case(4){
          //
          // Function 4: Set PMU Power State Method, clear PMU PME
          // Arg3: A package consisting of 1 ULONG value
          // 0x00 PMU should enter the D0 power state.
          // 0x03 PMU should enter the D3 power state.
          //

          //
          // Local 1 is power state D0 or D3
          //
          Store(DerefOf(Index(Arg3,0)), Local1)

          //
          // Set PMU to Dx state and clear PMU PME
          //
          SPPT(Local1, 0)
        }
        Case(5){
          //
          // Function 5: Attach Notification Enabled Method
          // This method is called by the USB function stack to indicate that it has enabled ACPI attach detach notifications.
          // In response the platform may issue an notification indicating the current attach/detach state of the controller.
          // If device is attached, notify TXDC with 0x80
          // If device is detached, notify TXDC with 0x81
          //


          If(CondRefOf(XDAT)){
            If(LEqual(XDAT(), 1)){
              Notify(\_SB.PC00.TXDC,0x80)
            }Else{
              Notify(\_SB.PC00.TXDC,0x81)
            }
          }
          Return(0)
        }
        Case(6){
          //
          // Function 6: TXDC Soft Reset Workaround
          // Return value indicate to OS softreset should be done by OS or not
          // Return value == 1: OS does softreset
          // Return value == 0: platform does softreset
          //


          If(LEqual(OTHC, 0)){
            Store(1, CSFR)
            // timeout is 100ms
            Store(0, Local0)
            While(LLess(Local0, 100)){
              If(LEqual(CSFR, 0)){
                Break
              }
            Sleep(1)
            }
          }
          Return(0)
        }
        Case(7){
          //
          // Function 7: Get PMU Power State Method
          // Return:
          // 0: PMU is in D0 state
          // 3: PMU is in D3 state
          //


          Store(PUPS, Local0)
          Return(Local0)
        }
        Case(8){
          //
          // Function 8: Get Group ID
          // Return:
          //   0: Group ID 0 is reserved
          //   Other value: A UCHAR value indicating that the controller shares connectors with one or more other controllers.
          //
          Return(1) // Both CPU and PCH are sharing connectors.
        }
        Case(9){
          //
          // Function 9: Currently, Power Down Scale is being overwritten by driver to a value of 2.
          //             BIOS saves the value initialized by HW and return the value to Driver. Driver to update the GCTL register.
          // Return:
          //   saved GCTL register value
          //
          And(TCDS, 0xFFF80000, Local1)  // Keep Bit19 - Bit31 (GCTL value only)
          ShiftRight(Local1, 19, Local1)
          return(Local1)
        }
      }
    }
  }
  Return(Buffer() {0})
  }

  //
  // XDCI Wake Support and _DSW method
  //
  Method(_PRW, 0)
  {
    Return(GPRW(0x6D, 4)) // can wakeup from S4 state
  }

  //
  // Device Sleep Wake - sets the sleep and wake transition states
  // for a device.
  //
  Method(_DSW, 3) {
    C2PM (Arg0, Arg1, Arg2, DCPM)
  }
