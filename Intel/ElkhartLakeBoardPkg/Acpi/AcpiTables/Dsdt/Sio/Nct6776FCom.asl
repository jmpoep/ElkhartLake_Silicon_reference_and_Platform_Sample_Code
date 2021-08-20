/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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


// This ASL file will support the NCT6776F UARTs.

Device(UARA)  // Serial Port A
{
  Name(_HID, EISAID("PNP0501"))
  Name(_UID,10)

  // Status Method for COM A.

  Method(_STA,0,Serialized)
  {
    // Only report resources to the OS if the SIO Device is present.

    //
    // Steps: 1) If board does not support NCT6776F return 0x0000 (no device).
    //        2) If bit set (NCT6776F present) aquire mutex and set the SIO
    //           to COM A.
    //        3) Read enable register to Local0.
    //        4) Release mutex and exit config mode.
    //        5) If Local0 set return 0x000f (device present and active).
    //        6) Else return 0x000d (device present, inactive).
    //
    If(LEqual(NCTC,1))
    {
      ENFG(0x02)
      Store(R30H, Local0)
      EXFG()
      If(Local0)
      {
        Return(0x000F)
      }

      Return(0x000D)
    }

    Return(0x0000)
  }

  // Disable Method for COM A.

  Method(_DIS,0,Serialized)
  {
    //
    // Steps: 1) Aquire mutex and set the SIO to COM A.
    //        2) Store 0 to enable register.
    //        3) release mutex and exit config mode.
    //
    ENFG(0x02)
    Store(0,R30H)
    EXFG()
  }

  // Current Resource Setting Method for COM A.

  Method(_CRS,0,Serialized)
  {
    //
    // Steps: 1) Create the buffer that stores the Resources to be returned.
    //        2) Aquire mutex and set the SIO to COM A.
    //        3) Create pointers to specific bytes.
    //        4) Read appropriate registers and copy them into buffer.
    //        5) Release mutex and exit config mode.
    //        6) Return the buffer with final values.
    //
    Name(BUF0,ResourceTemplate()
    {
      IO(Decode16,0x03F8,0x03F8,0x01,0x08)
      IRQNoFlags(){4}
    })

    ENFG(0x02)

    // Create pointers to the specific byte.

    CreateByteField(BUF0,0x02,IOL0)
    CreateByteField(BUF0,0x03,IOH0)
    CreateByteField(BUF0,0x04,IOL1)
    CreateByteField(BUF0,0x05,IOH1)
    CreateByteField(BUF0,0x07,LEN0)
    CreateWordField(BUF0,0x09,IRQW)

    // Write IO and Length values into the Buffer.

    Store(R60H,IOH0)
    Store(R61H,IOL0)
    Store(R60H,IOH1)
    Store(R61H,IOL1)
    Store(8,LEN0)

    // Convert the IRQ value to bit and write it into the Buffer.

    And(R70H,0x0F,Local0)
    If(Local0)
    {
      ShiftLeft(One,Local0,IRQW)
    }
    Else
    {
      Store(Zero,IRQW)
    }

    EXFG()
    Return(BUF0)
  }

  // Possible Resource Setting Method for COM A.

    // Build a Buffer with all valid COM Port Resources. A Method is not
    // required when using _PRS.

    Name(_PRS,ResourceTemplate()
    {
      StartDependentFn(0,2)
      {
        IO(Decode16,0x3F8,0x3F8,0x01,0x08)
        IRQNoFlags(){4}
      }

      StartDependentFn(0,2)
      {
        IO(Decode16,0x2F8,0x2F8,0x01,0x08)
        IRQNoFlags(){3}
      }

      StartDependentFn(0,2)
      {
        IO(Decode16,0x3E8,0x3E8,0x01,0x08)
        IRQNoFlags(){4}
      }

      StartDependentFn(0,2)
      {
        IO(Decode16,0x2E8,0x2E8,0x01,0x08)
        IRQNoFlags(){3}
      }

      EndDependentFn()
    })


  // Set Resource Setting Method for COM A.

  Method(_SRS,1,Serialized)
  {
    //
    // Steps: 1) Point to the specific information in the passed in Buffer.
    //        2) Aquire mutex and set the SIO to COM A.
    //        3) Disable the device by writting 0 to the enable register.
    //        4) Set the Base IO Address and IRQ.
    //        5) Set the LPC decode range.
    //        6)
    //
    CreateByteField(Arg0,0x02,IOLO)
    CreateByteField(Arg0,0x03,IOHI)
    CreateWordField(Arg0,0x09,IRQW)

    ENFG(0x02)
    Store(0,R30H)

    // Set the Base IO Address.

            Store(IOLO,R61H)
            Store(IOHI,R60H)

    // Set the IRQ.

    FindSetRightBit(IRQW,Local0)
    If(LNotEqual(IRQW,Zero))
    {
      Decrement(Local0)
    }
    Store(Local0,R70H)

    // Set the Decode Range so COM A works on ICH7 and future platforms.

    AND(IOD0,0xF8,IOD0)     // Clear all bits.

    If(LEqual(IOHI,0x03))     // Address = 0x3xx
    {
      If(LEqual(IOLO,0xF8))   // Address = 0x3F8
      {
        Or(IOD0,0x00,IOD0)
      }
      Else        // Address = 0x3E8
      {
        Or(IOD0,0x07,IOD0)
      }
    }
    Else          // Address = 0x2xx
    {
      If(LEqual(IOLO,0xF8))   // Address = 0x2F8
      {
        Or(IOD0,0x01,IOD0)
      }
      Else        // Address = 0x2E8
      {
        Or(IOD0,0x05,IOD0)
      }
    }

    // Enable the device.

    Store(1,R30H)
    EXFG()                // release mutex and exit config mode.
  }

  // D0 Method for COM Port.

  Method(_PS0,0,Serialized)
  {
    //
    // Steps: 1) Aquire mutex and set the SIO to COM A.
    //        2) Store 1 to enable register.
    //        3) release mutex and exit config mode.
    //
    ENFG(0x02)            // Aquire mutex and set the SIO to COM A.
    Store(1,R30H)
    EXFG()                // release mutex and exit config mode.
  }

  // D3 Method for COM Port.

  Method(_PS3,0,Serialized)
  {
    //
    // Steps: 1) Aquire mutex and set the SIO to COM A.
    //        2) Store 0 to enable register.
    //        3) release mutex and exit config mode.
    //
    ENFG(0x02)            // Aquire mutex and set the SIO to COM A.
    Store(0,R30H)
    EXFG()                // release mutex and exit config mode.
  }
}

