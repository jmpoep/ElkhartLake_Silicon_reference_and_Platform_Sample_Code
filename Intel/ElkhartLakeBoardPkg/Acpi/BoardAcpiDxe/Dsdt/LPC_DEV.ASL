/** @file
  ACPI DSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include <Register/PmcRegs.h>

Device(HPET)  // High Performance Event Timer
{
  Name(_HID,EISAID("PNP0103"))
  Name(_UID, 0)

  Name(BUF0,ResourceTemplate()
  {
    Memory32Fixed(ReadWrite,0xFED00000,0x400,FED0)
  })

  Method(_STA,0)
  {
    // Show this Device only if the OS is WINXP or beyond.
    If(HPTE)
    {
      Return(0x000F)  // Enabled, do Display.
    }

    Return(0x0000)      // Return Nothing.
  }

  Method(_CRS,0,Serialized)
  {
    If(HPTE)
    {
      // Check if HPETimer Base should be modified.
      CreateDwordField(BUF0,^FED0._BAS,HPT0)
      Store(HPTB,HPT0)
    }

    Return(BUF0)
  }
}

Device(IPIC)  // 8259 PIC
{
  Name(_HID,EISAID("PNP0000"))

  Name(_CRS,ResourceTemplate()
  {
    IO(Decode16,0x20,0x20,0x01,0x02)
    IO(Decode16,0x24,0x24,0x01,0x02)
    IO(Decode16,0x28,0x28,0x01,0x02)
    IO(Decode16,0x2C,0x2C,0x01,0x02)
    IO(Decode16,0x30,0x30,0x01,0x02)
    IO(Decode16,0x34,0x34,0x01,0x02)
    IO(Decode16,0x38,0x38,0x01,0x02)
    IO(Decode16,0x3C,0x3C,0x01,0x02)
    IO(Decode16,0xA0,0xA0,0x01,0x02)
    IO(Decode16,0xA4,0xA4,0x01,0x02)
    IO(Decode16,0xA8,0xA8,0x01,0x02)
    IO(Decode16,0xAC,0xAC,0x01,0x02)
    IO(Decode16,0xB0,0xB0,0x01,0x02)
    IO(Decode16,0xB4,0xB4,0x01,0x02)
    IO(Decode16,0xB8,0xB8,0x01,0x02)
    IO(Decode16,0xBC,0xBC,0x01,0x02)
    IO(Decode16,0x4D0,0x4D0,0x01,0x02)
    IRQNoFlags() {2}
  })
}


Device(MATH)  // Math Co-Processor
{
  Name(_HID,EISAID("PNP0C04"))

  Name(_CRS,ResourceTemplate()
  {
    IO(Decode16,0xF0,0xF0,0x01,0x01)
    IRQNoFlags() {13}
  })

  //
  // Report device present for LPT-H.
  //
  Method (_STA, 0x0, NotSerialized)
  {
    If(LEqual(PCHS, PCHH)) {
      Return(0x1F)
    } else {
      Return(0x0)
    }
  }
}


Device(LDRC)  // LPC Device Resource Consumption
{
  Name(_HID,EISAID("PNP0C02"))

  Name(_UID,2)

  Name(_CRS,ResourceTemplate()                      // This is for Cougar Point
  {
    IO(Decode16,0x2E,0x2E,0x1,0x02)             // SIO Access.
    IO(Decode16,0x4E,0x4E,0x1,0x02)             // LPC Slot Access.
    IO(Decode16,0x61,0x61,0x1,0x1)               // NMI Status.
    IO(Decode16,0x63,0x63,0x1,0x1)               // Processor I/F.
    IO(Decode16,0x65,0x65,0x1,0x1)               // Processor I/F.
    IO(Decode16,0x67,0x67,0x1,0x1)               // Processor I/F.
    IO(Decode16,0x70,0x70,0x1,0x1)               // NMI Enable.
    IO(Decode16,0x80,0x80,0x1,0x1)               // Port 80h.
    IO(Decode16,0x92,0x92,0x1,0x1)               // Processor I/F.
    IO(Decode16,0xB2,0xB2,0x01,0x02)           // Software SMI.
    IO(Decode16,0x680,0x680,0x1,0x20)        // 32 Byte I/O.
    IO(Decode16,0x164e,0x164e,0x1,0x02)    // 16 Byte I/O.
  })
}

Device(RTC) // RTC
{
  Name(_HID,EISAID("PNP0B00"))

  Name(_CRS,ResourceTemplate()
  {
    IO(Decode16,0x70,0x70,0x01,0x08)
    IRQNoFlags() {8}
  })
}

Device(TIMR)  // 8254 Timer
{
  Name(_HID,EISAID("PNP0100"))

  Name(_CRS,ResourceTemplate()
  {
    IO(Decode16,0x40,0x40,0x01,0x04)
    IO(Decode16,0x50,0x50,0x10,0x04)
    IRQNoFlags() {0}
  })
}

Device(CWDT)
{
  Name(_HID,EISAID("INT3F0D"))
  Name(_CID,EISAID("PNP0C02"))

  Method(_STA,0,Serialized)
  {
    Return(0x0F)
  }

  Method (_CRS, 0x0, NotSerialized) {
    Name (RBUF, ResourceTemplate () {
      IO(Decode16, 0, 0, 0x4, 0x4,OCWD)  // ACPIBASE + OcWdtCtl offset
    })

    CreateWordField(RBUF,OCWD._MIN,OMIN)
    CreateWordField(RBUF,OCWD._MAX,OMAX)

    Add(PMBS,R_ACPI_IO_OC_WDT_CTL,OMIN)
    Add(PMBS,R_ACPI_IO_OC_WDT_CTL,OMAX)

    Return (RBUF)
  }
}
