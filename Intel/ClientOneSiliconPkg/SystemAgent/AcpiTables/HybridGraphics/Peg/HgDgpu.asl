/** @file
  This file contains the system BIOS Hybrid graphics code for
  PEG DGPU.

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

External(\_SB.PC00.PEG0.PEGP, DeviceObj)
External(\_SB.PC00.PGON, MethodObj)
External(\_SB.PC00.PGOF, MethodObj)
External(\_SB.SGOV, MethodObj)
External(\GBAS)
External(\SGGP)

Scope(\_SB.PC00.PEG0.PEGP)
{
  Method(_ON,0,Serialized)
  {
    \_SB.PC00.PGON(0)
    //
    //Ask OS to do a PnP rescan
    //
    Notify(\_SB.PC00.PEG0,0)
  }

  Method(_OFF,0,Serialized)
  {
    \_SB.PC00.PGOF(0)
    //
    //Ask OS to do a PnP rescan
    //
    Notify(\_SB.PC00.PEG0,0)
  }

  //
  // Name: SGPO [SG GPIO Write]
  // Description: Function to write into GPIO
  // Input: Arg0 -> Expander Number
  //        Arg1 -> Gpio Number
  //        Arg2 -> Active Information
  //        Arg3 -> Value to write
  // Return: Nothing
  //
  Method(SGPO, 4, Serialized)
  {
    //
    // Invert if Active Low
    //
    If (LEqual(Arg2,0))
    {
      Not(Arg3, Arg3)
      And(Arg3, 0x01, Arg3)
    }
    If (LEqual(SGGP, 0x01))
    {
      //
      // PCH based GPIO
      //
      If (CondRefOf(\_SB.SGOV))
      {
        \_SB.SGOV(Arg1, Arg3)
      }
    }
  } // End of Method(SGPO)
} // End of Scope(\_SB.PC00.PEG0.PEGP)
