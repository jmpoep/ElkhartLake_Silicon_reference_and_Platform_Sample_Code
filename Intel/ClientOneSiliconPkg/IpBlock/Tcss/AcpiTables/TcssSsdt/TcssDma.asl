/** @file
  This file contains the TCSS DMA ASL code.
  It defines a Power Management for TCSS DMA

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
  // For devices that support both D3hot and D3 exposed to OSPM via _PR3, device software/drivers
  // must always assume OSPM will target D3 and must assume all device context will be lost and the
  // device will no longer be enumerable. The possible way to access an OpRegion could be when the
  // access type configured as SystemMemory.
  //
  OperationRegion(DPME, SystemMemory, BASE(), 0x100)
  Field(DPME,AnyAcc,NoLock,Preserve)
  {
    Offset(0),
    VDID, 32,
    Offset(R_SA_HOST_DMA_CFG_PM_CAP_1),    // 0x84
    PMST, 2,       // 1:0, PM_STATE
    , 6,
    PMEE, 1,       // 8, PME_EN
    , 6,
    PMES, 1,       // 15, PME_STATUS
    Offset(R_SA_HOST_DMA_RTD3_FORCEPOWER), // 0xFC
    DD3E, 1,       // 0:0 DMA RTD3 Enable
    DFPE, 1,       // 1:1 DMA Force Power
    , 22,
    DMAD, 8        // 31:24 DMA Active Delay
  }

  Name(STAT, 0x1)  // Variable to save power state 1 - D0, 0 - D3C
  Name(ALCT, 0x0)  // Connect-Topology cmd can be sent or not 1 - yes, 0 - no

  //
  // This Control Method is used to put the specific device into its D0 state. The PMSS is not yet
  // changed (staying in previous state, could be D0 or D3H) when this method is called.
  //
  Method(_PS0,0,Serialized)
  {
    //
    // Need to send Connect-Topology command when TBT host controller back to D0 from D3
    //
    If (LEqual(ALCT, 1)) {
      CNTP()            // Send Connect-Topology command
      Store(0, ALCT)    // Disallow to send Connect-Topology cmd
    }
  }

  //
  // This control method is used to put the specific device into its D3 state. The PMSS is in D3H typically
  // when this method is called, so this control method can only access Operation Regions that are either always
  // available while in the system working state (S0) or that are available when the Power Resources referenced
  // by the _PR0, _PR1 and PR2 objects are all ON. For devices that support both D3hot and D3 exposed to OSPM via
  // _PR3, device software/drivers must always assume OSPM will target D3 and must assume all device context will
  // be lost and the device will no longer be enumerable. The possible way to access an OpRegion could be when the
  // access type configured as SystemMemory.
  //
  Method(_PS3,0,Serialized)
  {
  }

  //
  // The deepest D-state supported by this device in the S0 system sleeping state where the device can wake itself,
  // "4" represents D3cold.
  //
  Method(_S0W, 0x0)
  {
    ADBG("TDMA S0W")
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
        If (LEqual (DUID, 0)) {
          Return (Package(){\_SB.PC00.D3C, \_SB.PC00.TBT0})
        } Else {
          Return (Package(){\_SB.PC00.D3C, \_SB.PC00.TBT1})
        }
      }
      If (LEqual (DUID, 0)) {
          Return (Package(){\_SB.PC00.TBT0})
      }
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
        If (LEqual (DUID, 0)) {
          Return (Package(){\_SB.PC00.D3C, \_SB.PC00.TBT0})
        } Else {
          Return (Package(){\_SB.PC00.D3C, \_SB.PC00.TBT1})
        }
      }
      If (LEqual (DUID, 0)) {
          Return (Package(){\_SB.PC00.TBT0})
      }
      Return (Package(){\_SB.PC00.TBT1})
    }
  }
  //
  // RTD3 Exit Method to bring TBT controller out of RTD3 mode.
  //
  Method(D3CX, 0, Serialized)  // RTD3 Exit
  {
    Store(0, DD3E)                                 // Disable DMA RTD3
    Store(0x1, STAT)
  }

  //
  // RTD3 Entry method to enable TBT controller RTD3 mode.
  //
  Method(D3CE, 0, Serialized)  // RTD3 Entry
  {
    Store(1, DD3E)                                 // Enable DMA RTD3
    Store(0x0, STAT)
    Store(0x1, ALCT)                               // Allow to send Connect-Topology cmd
  }

  //
  // Variable to skip TCSS/TBT D3 cold; 1+: Skip D3CE, 0 - Enable D3CE
  // TCSS D3 Cold and TBT RTD3 is only available when system power state is in S0.
  //
  Name(SD3C, 0)

  Method(_DSW, 3) {
    Store(Arg1, SD3C)                                 // If entering Sx (Arg1 > 1), need to skip TCSS D3Cold & TBT RTD3/D3Cold.
  }

  //
  // Additionally if the device is capable of waking up
  // the platform from a low power System state (S3 or S4), there is a _S0W and _PRW
  // associated with the device as well.
  //
  Method(_PRW, 0) {
    Return(GPRW(0x6D, 4)) // can wakeup from S4 state
  }

  Method (_DSD, 0) {
    If (ITIM) {
      If (TIVS) {
        Return (
          Package ()
          {
            ToUUID("C44D002F-69F9-4E7D-A904-A7BAABDF43F7"),
            Package ()
            {
              Package (2) {"IMR_VALID", 1}
            },
            ToUUID("6C501103-C189-4296-BA72-9BF5A26EBE5D"),
            Package ()
            {
              Package (2) {"WAKE_SUPPORTED", 1}
            }
          }
        ) // End of Return ()
      } Else {
        Return (
          Package ()
          {
            ToUUID("C44D002F-69F9-4E7D-A904-A7BAABDF43F7"),
            Package ()
            {
              Package (2) {"IMR_VALID", 1}
            },
            ToUUID("6C501103-C189-4296-BA72-9BF5A26EBE5D"),
            Package ()
            {
              Package (2) {"WAKE_SUPPORTED", 0}
            }
          }
        ) // End of Return ()
      }
    } Else {
      If (TIVS) {
        Return (
          Package ()
          {
            ToUUID("C44D002F-69F9-4E7D-A904-A7BAABDF43F7"),
            Package ()
            {
              Package (2) {"IMR_VALID", 0}
            },
            ToUUID("6C501103-C189-4296-BA72-9BF5A26EBE5D"),
            Package ()
            {
              Package (2) {"WAKE_SUPPORTED", 1}
            }
          }
        ) // End of Return ()
      } Else {
        Return (
          Package ()
          {
            ToUUID("C44D002F-69F9-4E7D-A904-A7BAABDF43F7"),
            Package ()
            {
              Package (2) {"IMR_VALID", 0}
            },
            ToUUID("6C501103-C189-4296-BA72-9BF5A26EBE5D"),
            Package ()
            {
              Package (2) {"WAKE_SUPPORTED", 0}
            }
          }
        ) // End of Return ()
      }
    }
  }

  Method (_DSM, 4, Serialized) {  // _DSM: Device-Specific Method
    //
    // _DSM Definition for TBT DMA functions
    // Arguments:
    // Arg0: UUID: 197DB5E0-F095-4F33-B915-71DD70833E55
    // Arg1: Revision ID: 1
    // Arg2: Function Index: 0, 1
    // Arg3: Additional Inputs Bits[31:0] Arg3 {Byte0, Byte1, Byte2, Byte3}
    //
    // Switch by function index
    //
      If (LEqual (Arg0,ToUUID("197DB5E0-F095-4F33-B915-71DD70833E55"))) { // TBT DMA
        If (LEqual (Arg2, 0)) {
        //
        // Function Index: 0
        // Standard query - A bitmask of functions supported
        //
        // Return: A bitmask of functions supported
        //
          If (LEqual (Arg1, 1)) {
            Return (Buffer() {0x03})  // Functions 1 supported for revision 1
          }
          Else { Return (Buffer() {0x01}) } // revisions higher than 1 are not supported
        }
        If (LEqual (Arg2, 1)) {
          //
          // Function Index: 1
          // Standard query - A bitmask of ITBT PCIe RootPort supported
          //
          // Return: A bitmask of ITBT PCIe RootPort supported
          //         below is the PCIe RP map
          //         00b: both ports disabled
          //         01b: first port is enable
          //         10b: second port is enabled
          //         11b: both ports enabled.
          Name(PCPN, Buffer(1){0})
          CreateBitField(PCPN, 0, PCP0)
          CreateBitField(PCPN, 1, PCP1)
          If (LEqual (DUID, 0)) {
            If(LEqual(TRE0, 1)) {
              Store (1, PCP0)
            }
            If(LEqual(TRE1, 1)) {
              Store (1, PCP1)
            }
          } Else {
            If(LEqual(TRE2, 1)) {
              Store (1, PCP0)
            }
            If(LEqual(TRE3, 1)) {
              Store (1, PCP1)
            }
          }

          Return (PCPN)
        }
      }
      Return (Buffer() {0})
    }