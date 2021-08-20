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

Device (\_SB.PC00.DOCK)
{

  Name(_HID, "ABCD0000")
  Name(_CID, EISAID("PNP0C15"))
  Name(_UID,"SADDLESTRING")

  If(LEqual(\S0ID,0)) {
    Method(_EJ0, 1) {
      P8XH(0,0xED)
      //
      // @todo: Add necessary Power/Hot removal procedure here.
      //
      Return ()
    }
  }

  Method(_STA, 0) {
    ADBG("Method _STA")
#ifdef EC_SUPPORT
    If(LEqual(ECON,0))
    {
      Return(0x0)
    }
#endif
    If(\DSTS) {
      ADBG("Dock Exist")
      Return(0x0F)
    } Else {
      ADBG("Dock not Exist")
      Return(0x0)
    }
  }


 If(LEqual(\S0ID,0)) {
   Method(_DCK, 1) {
     ADBG("Method _DCK")
     If (Arg0) {
       Return (1)
     } Else {
       Store(0, \DSTS)
       Return (1)
     }
   }
 }

  Name(_EDL, Package( ) {   // DOCK1 has several dependent devices
    \_SB.PC00.RP07.PXSX,
    \_SB.PC00.RP08.PXSX,
    \_SB.PC00.SAT0,
    })

}
