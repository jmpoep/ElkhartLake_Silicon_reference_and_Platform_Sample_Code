/** @file
  ACPI DSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

External(UPBT, MethodObj)

  Method (HIDW, 4, Serialized)
  {
    //--------------------------------------------
    //  Intel Proprietary Wake up Event solution
    //
    //  Method(_DSM, 0x4, Serialized, 0, {IntObj, BuffObj}, {BuffObj, IntObj, IntObj, PkgObj})
    //
    //--------------------------------------------
    // DSM UUID for Intel Proprietary Wake up Event solution. Do Not change.
    If (LEqual(Arg0, ToUUID("1730E71D-E5DD-4A34-BE57-4D76B6A2FE37")))
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
        Switch(ToInteger(DeRefOf(Index(Arg3, 0))))
        {
          Case (0) // Send HID Event/Wake Notification
          {
            If (CondRefOf(\_SB.HIDD.HPEM))
            {
#ifdef EC_SUPPORT
              \_SB.HIDD.HPEM(27)
#endif
              P8XH(0,0x5C)
            }
          }
          Case (1) // Send Sleep button Notification. Put the system to Sleep
          {
            If (CondRefOf(\_SB.SLPB))
            {
              Notify(\_SB.SLPB, 0x80)
              P8XH(0,0x5D)
            }
          }
          Case (2) // Send Dock Event
          {
#ifdef EC_SUPPORT
            If (CondRefOf(\_SB.PC00.LPCB.H_EC.UPBT))
            {
              \_SB.PC00.LPCB.H_EC.UPBT(0x80, One) // Arg0:Bit7 - Dock Indicator change request, Arg1:One - Set the target bit.
            }
#endif
          }
          Case (3) // Send Undock Event
          {
#ifdef EC_SUPPORT
            If (CondRefOf(\_SB.PC00.LPCB.H_EC.UPBT))
            {
              \_SB.PC00.LPCB.H_EC.UPBT(0x80, Zero) // Arg0:Bit7 - Dock Indicator change request, Arg1:Zero - Clear the target bit.
            }
#endif
          }
        }
        Return(0)
      }
      Else
      {
        Return(0) // Function number mismatch but normal return.
      }
    }
    Else
    {
      Return(Buffer(One) { 0x00 }) // Guid mismatch
    }
  } // End Method (HIDW)

  Method (HIWC, 1) // HID WAKE CHECK
  {
    If (LEqual(Arg0, ToUUID("1730E71D-E5DD-4A34-BE57-4D76B6A2FE37")))
    {
      Return (1)
    }
    Return (0)
  } // End Method (HIWC)
