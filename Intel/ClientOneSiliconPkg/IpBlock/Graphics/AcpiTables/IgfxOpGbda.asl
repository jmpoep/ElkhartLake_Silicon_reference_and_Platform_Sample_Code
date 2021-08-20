/** @file
  IGD OpRegion/Software SCI Reference Code.
  This file contains Get BIOS Data Area funciton support for
  the Integrated Graphics Device (IGD) OpRegion/Software SCI mechanism

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
Method (GBDA, 0, Serialized)
{
  //
  // Supported calls: Sub-function 0
  //
  If (LEqual(GESF, 0))
  {
    //
    //<NOTE> Reference code is set to Intel's validated implementation.
    //
    Store(0x0000659, PARM)
    Store(Zero, GESF) // Clear the exit parameter
    Return(SUCC) // Success
  }
  //
  // Requested callbacks: Sub-function 1
  //
  If (LEqual(GESF, 1))
  {
    //
    //<NOTE> Call back functions are where the driver calls the
    // system BIOS at function indicated event.
    //
    Store(0x300482, PARM)
    If(LEqual(S0ID, One)){
      Or(PARM, 0x100, PARM) //Request Fn 8 callback in CS systems
    }
    Store(Zero, GESF) // Clear the exit parameter
    Return(SUCC) // Success
  }
  //
  // Get Boot display Preferences: Sub-function 4
  //
  If (LEqual(GESF, 4))
  {
    //
    //<NOTE> Get Boot Display Preferences function.
    //
    And(PARM, 0xEFFF0000, PARM) // PARM[30:16] = Boot device ports
    And(PARM, ShiftLeft(DeRefOf(Index(DBTB, IBTT)), 16), PARM)
    Or(IBTT, PARM, PARM) // PARM[7:0] = Boot device type
    Store(Zero, GESF) // Clear the exit parameter
    Return(SUCC) // Success
  }
  //
  // Panel details: Sub-function 5
  //
  If (LEqual(GESF, 5))
  {
    //
    //<NOTE> Get Panel Details function.
    //
    Store(IPSC, PARM) // Report the scaling setting
    Or(PARM, ShiftLeft(IPAT, 8), PARM)
    Add(PARM, 0x100, PARM) // Adjust panel type, 0 = VBT default
    Or(PARM, ShiftLeft(LIDS, 16), PARM) // Report the lid state
    Add(PARM, 0x10000, PARM) // Adjust the lid state, 0 = Unknown
    Or(PARM, ShiftLeft(IBIA, 20), PARM) // Report the BIA setting
    Store(Zero, GESF)
    Return(SUCC)
  }
  //
  // Internal graphics: Sub-function 7
  //
  If (LEqual(GESF, 7))
  {
    Store(GIVD, PARM) // PARM[0]      - VGA mode(1=VGA)
    Xor(PARM, 1, PARM) // Invert the VGA mode polarity
    Or(PARM, ShiftLeft(GMFN, 1), PARM) // PARM[1]   - # IGD PCI functions-1
                                       // PARM[3:2]    - Reserved
                                       // PARM[4]      - IGD D3 support(0=cold)
                                       // PARM[10:5]   - Reserved
    Or(PARM, ShiftLeft(3, 11), PARM) // PARM[12:11] - DVMT mode(11b = 5.0)

    //
    // Report DVMT 5.0 Total Graphics memory size.
    //
    Or(PARM, ShiftLeft(IDMS, 17), PARM) // Bits 20:17 are for Gfx total memory size
    //
    // If the "Set Internal Graphics" call is supported, the modified
    // settings flag must be programmed per the specification.  This means
    // that the flag must be set to indicate that system BIOS requests
    // these settings.  Once "Set Internal Graphics" is called, the
    //  modified settings flag must be cleared on all subsequent calls to
    // this function.
    // Report the graphics frequency based on B0:D2:F0:RF0h[12].  Must
    // take into account the current VCO.
    //
    Or(ShiftLeft(Derefof(Index(Derefof(Index(CDCT, HVCO)), CDVL)), 21),PARM, PARM)
    Store(1, GESF) // Set the modified settings flag
    Return(SUCC)
  }
  //
  // Spread spectrum clocks: Sub-function 10
  //
  If (LEqual(GESF, 10))
  {
    Store(0, PARM) // Assume SSC is disabled
    If(ISSC)
    {
      Or(PARM, 3, PARM) // If SSC enabled, return SSC1+Enabled
    }
    Store(0, GESF) // Set the modified settings flag
    Return(SUCC) // Success
  }

  If (LEqual(GESF, 11))
  {
    Store(KSV0, PARM) // First four bytes of AKSV
    Store(KSV1, GESF) // Fifth byte of AKSV

    Return(SUCC) // Success
  }
  //
  // A call to a reserved "Get BIOS data" function was received.
  //
  Store(Zero, GESF) // Clear the exit parameter
  Return(CRIT) // Reserved, "Critical failure"
}
