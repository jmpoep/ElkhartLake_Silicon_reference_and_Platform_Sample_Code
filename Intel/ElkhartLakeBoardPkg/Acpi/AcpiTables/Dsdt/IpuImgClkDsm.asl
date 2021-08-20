/** @file
  ACPI DSDT table

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

//----------------------------------------------------------------------------------------
//  Intel Proprietary IMGCLK Enabling DSM Method
//
//  Method(_DSM, 0x4, Serialized, 0, {IntObj, BuffObj}, {BuffObj, IntObj, IntObj, PkgObj})
//  Arguments:
// Arg0: UUID Unique function identifier
// Arg1: Integer Revision Level
// Arg2: Integer Function Index
// Arg3: Package Parameters -
//       Index 0 - Clock source select (0: IMGCLKOUT_0, 1: IMGCLKOUT_1, 2: IMGCLKOUT_2, 3: IMGCLKOUT_3, 4: IMGCLKOUT_4)
//       Index 1 - Clock Enable / Disable (0: Disable, 1: Enable)
//       Index 2 - Select 24MHz / 19.2 MHz (0: 24MHz, 1: 19.2MHz)
//-----------------------------------------------------------------------------------------
// DSM UUID for IMGCLK Enabling. Do Not change.
If (LEqual(Arg0, ToUUID("82C0D13A-78C5-4244-9BB1-EB8B539A8D11")))
{
  // Function 0 : Query Function
  If (LEqual(Arg2, Zero))
  {
    // Revision 0
    If (LEqual(Arg1, Zero)) // The current revision is 0
    {
      Return(Buffer(One) { 0x03 }) // There are 1 function defined other than Query.
    }
    Else
    {
      Return(0) // Revision mismatch
    }
  }
  // Function 1 :
  If(LEqual(Arg2, One))
  {
    CLKC(ToInteger(DeRefOf(Index(Arg3, 0))), ToInteger(DeRefOf(Index(Arg3, 1))))
    CLKF(ToInteger(DeRefOf(Index(Arg3, 0))), ToInteger(DeRefOf(Index(Arg3, 2))))
  }
  Else
  {
    Return(0) // Function number mismatch but normal return.
  }
}
