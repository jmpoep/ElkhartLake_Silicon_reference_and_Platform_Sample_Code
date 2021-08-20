/** @file
  ACPI DSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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

@par Specification
**/

External(\DEPC)
//
// Camera LYRY
//
Device(CLRY) {
  Method(_STA, 0, Serialized)
  {
    If(LEqual(DEPC,1))
    {
      Return(0x0F)
    }
    Return(0x00)
  }

  Method(_ADR, 0, Serialized)
  {
    If(LEqual(DEPC,1))
    {
       Return(0xF)
    }
    Return(0x00)
  }

   Method(_UPC, 0, Serialized) {
    Name(UPCP, Package() { 0xFF,0xFF,0x00,0x00 }) // Proprietary connector
    Return(UPCP)
  }

  Method(_PLD, 0, Serialized)
  {
    Name(PLDR, Package() { //For RVP3 Platform
    Buffer(0x14)
      {
        0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Revision 2
        0x28, 0x01, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, // Not visible, Back Panel, Upper, Center,1st, 2nd, 3rd & 4th In Group
        0xA0, 0x00, 0x6E, 0x00 //Optional
      }
    })
    If(LEqual(DEPC,1))
    {
      Return(PLDR)
    }
    Return(Package() {})
  }
} // Device(CLRY)

//
// Camera Depth
//
Device(CDPT) {
  Method(_STA, 0, Serialized)
  {
    If(LEqual(DEPC,1))
    {
      Return(0x0F)
    }
    Return(0x00)
  }

  Method(_ADR, 0, Serialized)
  {
    If(LEqual(DEPC,1))
    {
      Return(0x11)
    }
    Return(0x00)
  }

   Method(_UPC, 0, Serialized) {
    Name(UPCP, Package() { 0xFF,0xFF,0x00,0x00 }) // Proprietary connector
    Return(UPCP)
  }

  Method(_PLD, 0, Serialized) {
    Name(PLDR, Package() { //For RVP3 Platform
    Buffer(0x14)
      {
        0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Revision 2
        0x28, 0x01, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, // Not visible, Back Panel, Upper, Center,1st, 2nd, 3rd & 4th In Group
        0xA0, 0x00, 0x5A, 0x00 //Optional
      }
    })
    If(LEqual(DEPC,1))
    {
      Return(PLDR)
    }
    Return(Package() {})
  }
} // Device(CDPT)


//
// Camera RGB
//
Device(CRGB) {
  Method(_STA, 0, Serialized)
  {
    If(LEqual(DEPC,1))
    {
      Return(0x0F)
    }
    Return(0x00)
  }

  Method(_ADR, 0, Serialized)
  {
    If(LEqual(DEPC,1))
    {
      Return(0x13)
    }
    Return(0x00)
  }

   Method(_UPC, 0, Serialized) {
    Name(UPCP, Package() { 0xFF,0xFF,0x00,0x00 }) // Proprietary connector
    Return(UPCP)
  }

  Method(_PLD, 0, Serialized) {
    Name(PLDR, Package() { //For RVP3 Platform
    Buffer(0x14)
      {
        0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Revision 2
        0x28, 0x01, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, // Not visible, Back Panel, Upper, Center,1st, 2nd, 3rd & 4th In Group
        0xA0, 0x00, 0x61, 0x00 //Optional
      }
    })
    If(LEqual(DEPC,1))
    {
      Return(PLDR)
    }
    Return(Package() {})
   }
} // Device(CRGB)

