/** @file
  Intel ACPI Reference Code for Dynamic Platform & Thermal Framework

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

Scope(\_SB.IETM)
{
    // KTOC (Kelvin to Celsius)
    //
    // This control method converts from 10ths of degree Kelvin to Celsius.
    //
    // Arguments: (1)
    //   Arg0 - Temperature in 10ths of degree Kelvin
    // Return Value:
    //   Temperature in Celsius
    //
    Method(KTOC,1,Serialized)
    {
      If(LGreater(Arg0,2732)) // make sure we have a temperature above zero Celcius
      {
        Return(Divide(Subtract(Arg0, 2732), 10))
      } Else {
        Return(0) // negative temperatures Celcius are changed to 0 degrees Celcius
      }
    }

    // CTOK (Celsius to Kelvin)
    //
    // This control method converts from Celsius to 10ths of degree Kelvin.
    //
    // Arguments: (1)
    //   Arg0 - Temperature in Celsius
    // Return Value:
    //   Temperature in 10ths of degree Kelvin
    //
    Method(CTOK,1,Serialized)
    {
      Return(Add(Multiply(Arg0,10),2732))
    }

    // C10K (Celsius to Kelvin)
    //
    // This control method converts from 10ths of degree Celsius (16 bit signed) to 10ths of degree Kelvin.
    // This method works only for temperatures upto absolute 0 Kelvin.
    //
    // Arguments: (1)
    //   Arg0 - Temperature in 10ths of degree Celsius (16 bit signed value)
    // Return Value:
    //   Temperature in 10ths of degree Kelvin
    //
    Method(C10K,1,Serialized)
    {
      Name(TMP1, Buffer(16) {0})
      CreateByteField(TMP1, 0x00, TMPL)
      CreateByteField(TMP1, 0x01, TMPH)

      Add(Arg0, 2732, Local0)
      Store(And(Local0,0xFF),TMPL)
      Store(ShiftRight(And(Local0,0xFF00),0x8),TMPH)

      ToInteger(TMP1, Local1)
      Return(Local1)

    }

    // K10C (Kelvin to Celsius)
    //
    // This control method converts from 10ths of degree Kelvin to 10ths of degree Celsius (16 bit signed).
    // This method works only for temperatures upto 0 degree celsius. Temperatures below 0 deg celsius are changed to 0 deg C.
    //
    // Arguments: (1)
    //   Arg0 - Temperature in 10ths of degree Kelvin
    // Return Value:
    //   Temperature in 10ths of degree Celsius (16 bit signed value)
    //
    Method(K10C,1,Serialized)
    {
      If(LGreater(Arg0,2732)) // make sure we have a temperature above zero Celcius
      {
        Return(Subtract(Arg0, 2732))
      } Else {
        Return(0) // negative temperatures Celcius are changed to 0 degrees Celcius
      }

    }
}