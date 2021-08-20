/** @file
  This file contains the TCSS XHCI ASL code.
  It defines a Power Management for TCSS XHCI

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
    Add (GPCB(), Local2, Local3)
    Return (Local3)
  }

  Method(_PS0,0,Serialized)
  {
    If (LEqual(\_SB.PC00.TXHC.PMEE, 1)) {
      Store(0, \_SB.PC00.TXHC.PMEE)
    }
  }

  Method(_PS3,0,Serialized)
  {
    If (LEqual(\_SB.PC00.TXHC.PMEE, 0)) {
      Store(1, \_SB.PC00.TXHC.PMEE)
    }
  }

  //
  // The deepest D-state supported by this device in the S0 system sleeping state where the device can wake itself,
  // "4" represents D3cold.
  //
  Method(_S0W, 0x0, NotSerialized)
  {
    If (TRTD) {
      Return(0x4)
    } Else {
      Return(0x3)
    }
  }
  //
  // Variable to skip TCSS/TBT D3 cold; 1+: Skip D3CE, 0 - Enable D3CE
  // TCSS D3 Cold and TBT RTD3 is only available when system power state is in S0.
  //
  Name(SD3C, 0)
  //
  // Power Management routine for D3
  //
  If (TRTD) {
    // To evaluates to a list of power resources that are dependent on this device. For OSPM to "put
    // the device in" the D0 device state
    Method(_PR0) {
      Return (Package(){\_SB.PC00.D3C})
    }
    // To evaluates to a list of power resources upon which this device is dependent when it is in the D3hot state.
    // The PMSS is in D3H when this method is called. For devices that support both D3hot and D3 exposed to OSPM via _PR3,
    // device software/drivers must always assume OSPM will target D3 and must assume all device context will be lost
    // and the device will no longer be enumerable.
    Method(_PR3) {
      Return (Package(){\_SB.PC00.D3C})
    }
  }

  OperationRegion(XPRT,SystemMemory,BASE(),0x100)
  //
  // Byte access for PMCS field to avoid race condition on device D-state
  //
  Field(XPRT,ByteAcc,NoLock,Preserve)
  {
    Offset(R_XHCI_CFG_PWR_CNTL_STS), // 0x74
    D0D3,  2,  // 0x74 BIT[1:0]
        ,  6,
    PMEE,  1,  // PME Enable
        ,  6,
    PMES,  1,  // PME Status
  }

  //
  // Variable to store the maximum D state supported in S0.
  //
  Name (XFLT, 0)

  //
  // XHCI controller _DSM method
  //
  Method(_DSM,4,serialized)
  {
    ADBG("XHCI _DSM")

    If(PCIC(Arg0)) { return(PCID(Arg0,Arg1,Arg2,Arg3)) }

    Return(Buffer() {0})
  }


  //
  // _SXD and _SXW methods
  //
  Method(_S3D, 0, NotSerialized)
  {
    Return(3)
  }
  Method(_S4D, 0, NotSerialized)
  {
    Return(3)
  }
  Method(_S3W, 0, NotSerialized)
  {
    Return(3)
  }
  Method(_S4W, 0, NotSerialized)
  {
    Return(3)
  }

  //
  // Additionally if the device is capable of waking up
  // the platform from a low power System state (S3 or S4), there is a _S0W and _PRW
  // associated with the device as well.
  //
  Method(_PRW, 0)
  {
    Return(GPRW(0x6D, 4)) // can wakeup from S4 state
  }

  Method(_DSW, 3)
  {
    ADBG("TCSS XHCI _DSW")
    C2PM (Arg0, Arg1, Arg2, DCPM)
    Store(Arg1, SD3C)                                 // If entering Sx (Arg1 > 1), need to skip TCSS D3Cold & TBT RTD3/D3Cold.
  }

  //
  // xHCI Root Hub Device
  //
  Device(RHUB)
  {
    Name(_ADR, Zero)

    //
    // Method for creating Type C _PLD buffers
    // _PLD contains lots of data, but for purpose of internal validation we care only about
    // ports visibility and pairing (this requires group position)
    // so these are the only 2 configurable parameters
    //
    Method(TPLD, 2, Serialized) { // For the port related with USB Type C.
      // Arg0:  Visible
      // Arg1:  Group position
      Name(PCKG, Package() { Buffer(0x10) {} } )
      CreateField(DerefOf(Index(PCKG,0)), 0, 7, REV)
      Store(1,REV)
      CreateField(DerefOf(Index(PCKG,0)), 64, 1, VISI)
      Store(Arg0, VISI)
      CreateField(DerefOf(Index(PCKG,0)), 87, 8, GPOS)
      Store(Arg1, GPOS)
      // For USB type C, Standerd values
      CreateField(DerefOf(Index(PCKG,0)), 74, 4, SHAP)  // Shape set to Oval
      Store(1, SHAP)
      CreateField(DerefOf(Index(PCKG,0)), 32, 16, WID)  // Width of the connector, 8.34mm
      Store(8, WID)
      CreateField(DerefOf(Index(PCKG,0)), 48, 16, HGT)  // Height of the connector, 2.56mm
      Store(3, HGT)
      return (PCKG)
    }

    //
    // Method for creating Type C _UPC buffers
    // Similar to _PLD, for internal testing we only care about 1 parameter
    //
    Method(TUPC, 2, Serialized) { // For the port related with USB Type C.
      // Arg0: Connectable
      // Arg1: Type
      // Type:
      //  0x08:     Type C connector - USB2-only
      //  0x09:     Type C connector - USB2 and SS with Switch
      //  0x0A:     Type C connector - USB2 and SS without Switch
      Name(PCKG, Package(4) { 1, 0x00, 0, 0 } )
      Store(Arg0,Index(PCKG,0))
      Store(Arg1,Index(PCKG,1))
      return (PCKG)
    }

    //
    // High Speed Ports
    //
    Device(HS01)
    {
      Name(_ADR, 0x01)
      // TODO: Check what to do about _UPC & _PLD
    }

    //
    // Super Speed Ports
    //
    Device(SS01)
    {
      Name(_ADR, 0x02)
    }

    Device(SS02)
    {
      Name(_ADR, 0x03)
    }

    Device(SS03)
    {
      Name(_ADR, 0x04)
    }

    Device(SS04)
    {
      Name(_ADR, 0x05)
    }

    Method(_PS0,0,Serialized)
    {
    }

    Method(_PS2,0,Serialized)
    {
    }

    Method(_PS3,0,Serialized)
    {
    }

  } // End of Device(RHUB)