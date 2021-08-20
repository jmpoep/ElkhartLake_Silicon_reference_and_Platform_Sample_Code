/** @file
  ACPI DSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

Device(H8S2)
{
  Name(_HID,EISAID("PNP0A05"))

  Name(_UID, 5)

  Method(_STA,0,Serialized)
  {
    If(LEqual(HSIO,1))
    {
      Return(0x000F)
    }
    Return(0x0000)
  }

  Device(UAR9)  // Serial Port UART 9
  {
    Name(_HID, EISAID("PNP0501"))

    Name(_UID, 1)

    //
    // Status Method for UART 9.
    //
    Method(_STA, 0, Serialized)
    {
      If(LEqual(HSIO,1))
      {
        Return(0x000F)
      }
      Return(0x0000)
    }

    //
    // Disable Method for UART 9.
    //
    //
    // Current Resource Setting Method for UART 9.
    //
    Method(_CRS, 0, Serialized)
    {
      //
      // Create the Buffer that stores the resources to be returned.
      //
      Name(BUF0, ResourceTemplate()
      {
        IO(Decode16,0x03F8,0x03F8,0x01,0x08)
        IRQNoFlags(){4}
      })

      //
      // TO-DO: Need to implement the code updating BUF0 (I/O 0x3F8~0x3FF and IRQ 4 are the default setting)
      // according to the real resources assigned when the EC commands are available.
      //

      Return(BUF0)
    }


    //
    // Set Resource Setting Method for UART 9.
    //
    Method(_SRS,1,Serialized)
    {
      CreateByteField(Arg0, 0x02, IOLO)
      CreateByteField(Arg0, 0x03, IOHI)
      CreateWordField(Arg0, 0x09, IRQW)

      If(LEqual(IOHI, 0x03))
      {
        If(LEqual(IOLO, 0xF8))
        {
          If(LEqual(IRQW, 4))
          {

          }
        }
      }

      //
      // TO-DO: Need to implement the code setting the resources based on the arguments when the EC commands are available.
      //
    }

    //
    // D0 Method for COM Port.
    //
    Method(_PS0,0,Serialized)
    {
      //
      // TO-DO: Need to implement the code put the device on D0 state when the EC commands are available.
      //
    }

    //
    // D3 Method for COM Port.
    //
    Method(_PS3,0,Serialized)
    {
      //
      // TO-DO: Need to implement the code putting the device on D3 state when the EC commands are available.
      //
    }
  }
}


