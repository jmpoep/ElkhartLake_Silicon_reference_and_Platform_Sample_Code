/** @file
  This file contains the system BIOS Hybrid graphics code for
  PCH DGPU.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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

Name (IVID, 0xFFFF) //Invalid Vendor ID
Name (ELCT, 0x00000000)
Name (HVID, 0x0000)
Name (HDID, 0x0000)
Name (TCNT, 0)
Name (LDLY, 100) //100 ms
//
// Define a Memory Region that will allow access to the PCH root port 5
// Register Block.
//
OperationRegion(RPCF,SystemMemory,RPBA,0x1000)
Field(RPCF,DWordAcc,NoLock,Preserve)
{
    Offset(0),
    PVID,   16,
    PDID,   16,
    Offset(0x18),
    PRBN,   8,                      // Primary Bus Number
    SCBN,   8,                      // Secondary Bus Number
    Offset(0x50),                   // LCTL - Link Control Register of (PCI Express* -> B00:D28:F00)
    ASPN,   2,                      // 1:0, ASPM //Not referenced in code
    ,       2,
    LKDN,   1,                      // Link Disable
    Offset(0x328),                  //PCIESTS1 - PCI Express Status 1
    ,       19,
    LKSN,   4,                      //Link Status (LNKSTAT) {22:19}
}

OperationRegion (RTPN, SystemMemory, Add(\XBAS,ShiftLeft(SCBN,20)), 0xF0)
Field(RTPN, AnyAcc, Lock, Preserve)
{
    Offset(0x0),
    DVID, 16,
    Offset(0xB),
    CBCN, 8,
    Offset(0x2C),
    SVID, 16,
    SDID, 16,
}

OperationRegion(PCAN, SystemMemory, Add(Add(\XBAS,ShiftLeft(SCBN,20)),\EECP),0x14)
Field(PCAN,DWordAcc, NoLock,Preserve)
{
    Offset(0x10),
    LCTR,   16,                      // Link Control register
}

OperationRegion(PCBN, SystemMemory, Add(Add(Add(\XBAS,ShiftLeft(SCBN,20)),0x1000),\EECP),0x14)
Field(PCBN,DWordAcc, NoLock,Preserve)
{
    Offset(0x10),
    LCTZ,   16,                      // Link Control register
}

//
// Name: HGON
// Description: Function to put the Pcie Endpoint in ON state
// Return: Nothing
//
Method(HGON,0,Serialized)
{

    If (LEqual(CCHK(1), 0))
    {
      Return ()
    }

    //ACTION:
    //........................................................................................
    // As per the PCIe spec, while powering up the slot first need to enable the slot followed
    // by given ms delay to wait for slot to wake up. The Reset# should be de-asserted 100ms
    // after the power to slot is up to allow internal initialization and to issue configuration
    // requests to devices.

    //Note:
    //The 100 ms time is given for power rails and clocks to become stable.
    //........................................................................................

    //Power on the dGPU card
    HGPO(PWE0, PWG0, PWA0, 1)                  //Assert dGPU_PWR_EN# {Power on the dGPU}
    Sleep(DLPW)                                // Wait for 'given'ms for power to get stable
    HGPO(HRE0, HRG0, HRA0, 0)                  //Deassert dGPU_HOLD_RST# {Release the dGPU Reset} as per the PCIe spec
    Sleep(DLHR)                                // Wait for 'given'ms after Deassert

    //Enable x4 Link
    //This bit should already be set to 0 in the _Off method. But do it anyway.
    Store(0,LKDN)

    //Wait until link has trained to x4
    Store(0, TCNT)
    While(LLess(TCNT, LDLY))
    {
      If(LGreaterEqual(LKSN,7)) {
        Break
      }
      Sleep(16) //In some OS one tick is equal to 1/64 second (15.625ms)
      Add(TCNT, 16, TCNT)
    }

    // Re-store the DGPU SSID &
    // Re-store the Link Control register - Common Clock Control and ASPM
    Store(HVID,SVID)
    Store(HDID,SDID)
    Or(And(ELCT,0x0043),And(LCTR,0xFFBC),LCTR)
    Or(And(ELCT,0x0043),And(LCTZ,0xFFBC),LCTZ)

    Return ()
}

//
// Name: HGOF
// Description: Function to put the Pcie Endpoint in OFF state
// Return: Nothing
//
Method(HGOF,0,Serialized)
{

    If (LEqual(CCHK(0), 0))
    {
      Return ()
    }

    //ACTION:
    //........................................................................................
    //To turn off the power to the slot, all you would need to do is assert the RESET# followed
    //by 100 ms delay to allow devices to retain its initialization values as per the PCIe spec
    //and then take off the power using the power enable GPIO.
    //Once the power goes off, the clock request from the slot to the PCH is also turned off,
    //so no clocks will be going to the PCIe slot anymore.
    //........................................................................................

    // Save the Link Control register, DGPU SSID & Force disable the x4 link
    Store(LCTR,ELCT)
    Store(SVID,HVID)
    Store(SDID,HDID)
    Store(1, LKDN)

    //Wait till link is actually in disabled state
    Store(0, TCNT)
    While(LLess(TCNT, LDLY))
    {
      If(LGreaterEqual(LKSN,0)) {
        Break
      }
      Sleep(16) //In some OS one tick is equal to 1/64 second (15.625ms)
      Add(TCNT, 16, TCNT)
    }

    //Power-off the dGPU card
    HGPO(HRE0, HRG0, HRA0, 1)                   // Assert dGPU_HOLD_RST# (PERST#) {Hold the dGPU Reset}
    Sleep(DLHR)                                 // As per the PCIe spec, Wait for 'given'ms after Assert the Reset
    HGPO(PWE0, PWG0, PWA0, 0)                   // Deassert dGPU_PWR_EN#  {Power off the dGPU}

    Return ()
}

//
// Name: HGPO [SG GPIO Write]
// Description: Function to write into GPIO
// Input: Arg0 -> Expander Number
//        Arg1 -> Gpio Number
//        Arg2 -> Active Information
//        Arg3 -> Value to write
// Return: Nothing
//
Method(HGPO, 4, Serialized)
{
  // Invert if Active Low
  If (LEqual(Arg2,0))
  {
    Not(Arg3, Arg3)
    And(Arg3, 0x01, Arg3)
  }
  If (LEqual(SGGP, 0x01))
  {
   // PCH Based GPIO
    If (CondRefOf(\_SB.SGOV))
    {
      \_SB.SGOV(Arg1, Arg3)
    }
  }
} // End of Method(HGPO)

//
// Name: HGPI [PCIe GPIO Read]
// Description: Function to Read from GPIO
// Input: Arg0 -> Gpio Support
//        Arg1 -> Expander Number
//        Arg2 -> Gpio Number
//        Arg3 -> Active Information
// Return: GPIO value
//
Method(HGPI, 4, Serialized)
{
  If (LEqual(Arg0, 0x01))
  {
    //
    // PCH based GPIO
    //
    If (CondRefOf(\_SB.GGOV))
    {
      Store(\_SB.GGOV(Arg2), Local0)
    }
  }
  //
  // Invert if Active Low
  //
  If (LEqual(Arg3,0))
  {
    Not(Local0, Local0)
  }
  And(Local0, 0x01, Local0)

  Return(Local0)

} // End of Method(HGPI)

//
// Name: CCHK
// Description: Function to check whether _ON/_OFF sequence is allowed to execute for the given RP09 controller or not
// Input: Arg0 -> 0 means _OFF sequence, 1 means _ON sequence
// Return: 0 - Don't execute the flow, 1 - Execute the flow
//
Method(CCHK,1)
{

  //Check for RP09 controller presence
  If(LEqual(PVID, IVID)) {
    Return(0)
  }
  //If Endpoint is not present[already disabled] before executing _OFF then don't call the _OFF method
  //If Endpoint is present[already enabled] before executing _ON then don't call the _ON method
  If(LEqual(Arg0, 0))
  {
    //_OFF sequence condition check
    If(LEqual(HGPI(SGGP, PWE0, PWG0, PWA0), 0))
    {
      Return(0)
    }
  }
  ElseIf(LEqual(Arg0, 1))
  {
    //_ON sequence condition check
    If(LEqual(HGPI(SGGP, PWE0, PWG0, PWA0), 1))
    {
      Return(0)
    }
  }

  Return(1)
} // End of Method(CCHK,1)


