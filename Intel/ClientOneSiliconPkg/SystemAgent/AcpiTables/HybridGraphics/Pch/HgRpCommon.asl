/** @file
  This file contains the system BIOS Hybrid graphics code for
  ULT.

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


//-----------------------------------------
// Runtime Device Power Management - Begin
//-----------------------------------------
//
// Name: PCRP
// Description: Declare a PowerResource object.
//
PowerResource(PCRP, 0, 0) {
  Name(_STA, One)
  Method(_ON, 0, Serialized) {
    If(LNotEqual(OSYS,2009)) {
      \_SB.PC00.HGON()
      Store(One, _STA)
    }
  }
  Method(_OFF, 0, Serialized) {
    If(LNotEqual(OSYS,2009)) {
      \_SB.PC00.HGOF()
      Store(Zero, _STA)
    }
  }
} //End of PowerResource(PCRP, 0, 0)

Name(_PR0,Package(){PCRP})
Name(_PR2,Package(){PCRP})
Name(_PR3,Package(){PCRP})

Method(_S0W, 0) { Return(4) } //D3cold is supported

//-----------------------------------------
// Runtime Device Power Management - End
//-----------------------------------------

Device(PEGP) {
  Name(_ADR, 0x00000000)
  Method(_PRW, 0) { Return(GPRW(0x69, 4)) } // can wakeup from S4 state
}

Device(PEGA) {
  Name(_ADR, 0x00000001)
  Method(_PRW, 0) { Return(GPRW(0x69, 4)) } // can wakeup from S4 state
}





