/** @file
  ACPI DSDT table

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2017 Intel Corporation.

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



// Use this information when determining the Possible IRQs that can be
// used in a given system.
//
// The following IRQs are always in use by legacy devices:
//    0  = System Timer
//    2  = 8259 PIC
//    8  = RTC
//    9  = SCI Interrupt (It may be used, we choose not to)
//    13 = Co-processor Error
//
// The following may be in use by legacy devices:
//    1  = If using PS/2 Keyboard
//    3  = If COMx Port Enabled and IRQ = 3
//    4  = If COMx Port Enabled and IRQ = 4
//    5  = If LPT Port Enabled and IRQ = 5
//    6  = If FDC Enabled
//    7  = If LPT Port Enabled and IRQ = 7
//    12 = If using PS/2 Mouse
//    14 = Primary IDE (If populated and in Compatibility Mode)
//    15 = Secondary IDE (If populated and in Compatibility Mode)
//
// The following will never be in use by legacy devices:
//    10 = Assign to PARC, PCRC, PERC, PGRC
//    11 = Assign to PBRC, PDRC, PFRC, PHRC

Device(LNKA)        // PARC Routing Resource
{
  Name(_HID,EISAID("PNP0C0F"))  // PCI Interrupt Link Device

  Name(_UID,1)      // Unique to other Link Devices

  // Current IRQ Resource Setting.
  Method(_CRS,0,Serialized)
  {
    Name(RTLA,ResourceTemplate()
    {
      IRQ(Level,ActiveLow,Shared) {11}
    })

    CreateWordField(RTLA,1,IRQ0)
    Store (PIRA, IRQ0)

    Return(RTLA)
  }

  // PCI IRQ Status.
  Method(_STA,0,Serialized)
  {
    Return(0x000B)
  }
}

Device(LNKB)        // PBRC Routing Resource
{
  Name(_HID,EISAID("PNP0C0F"))

  Name(_UID,2)

  // Current IRQ Resource Setting.
  Method(_CRS,0,Serialized)
  {
    Name(RTLB,ResourceTemplate()
    {
      IRQ(Level,ActiveLow,Shared) {10}
    })

    CreateWordField(RTLB,1,IRQ0)
    Store (PIRB, IRQ0)

    Return(RTLB)
  }

  // PCI IRQ Status.
  Method(_STA,0,Serialized)
  {
    Return(0x000B)
  }
}

Device(LNKC)        // PCRC Routing Resource
{
  Name(_HID,EISAID("PNP0C0F"))

  Name(_UID,3)

  // Current IRQ Resource Setting.
  Method(_CRS,0,Serialized)
  {
    Name(RTLC,ResourceTemplate()
    {
      IRQ(Level,ActiveLow,Shared) {11}
    })

    CreateWordField(RTLC,1,IRQ0)
    Store (PIRC, IRQ0)

    Return(RTLC)
  }

  // PCI IRQ Status.
  Method(_STA,0,Serialized)
  {
    Return(0x000B)
  }
}

Device(LNKD)        // PDRC Routing Resource
{
  Name(_HID,EISAID("PNP0C0F"))

  Name(_UID,4)

  // Current IRQ Resource Setting.
  Method(_CRS,0,Serialized)
  {
    Name(RTLD,ResourceTemplate()
    {
      IRQ(Level,ActiveLow,Shared) {11}
    })

    CreateWordField(RTLD,1,IRQ0)
    Store (PIRD, IRQ0)

    Return(RTLD)
  }


  // PCI IRQ Status.
  Method(_STA,0,Serialized)
  {
    Return(0x000B)
  }
}

Device(LNKE)        // PERC Routing Resource
{
  Name(_HID,EISAID("PNP0C0F"))

  Name(_UID,5)

  // Current IRQ Resource Setting.
  Method(_CRS,0,Serialized)
  {
    Name(RTLE,ResourceTemplate()
    {
      IRQ(Level,ActiveLow,Shared) {11}
    })

    CreateWordField(RTLE,1,IRQ0)
    Store (PIRE, IRQ0)

    Return(RTLE)
  }

  // PCI IRQ Status.
  Method(_STA,0,Serialized)
  {
    Return(0x000B)
  }
}

Device(LNKF)        // PFRC Routing Resource
{
  Name(_HID,EISAID("PNP0C0F"))

  Name(_UID,6)

  // Current IRQ Resource Setting.
  Method(_CRS,0,Serialized)
  {
    Name(RTLF,ResourceTemplate()
    {
      IRQ(Level,ActiveLow,Shared) {11}
    })

    CreateWordField(RTLF,1,IRQ0)
    Store (PIRF, IRQ0)

    Return(RTLF)
  }

  // PCI IRQ Status.
  Method(_STA,0,Serialized)
  {
    Return(0x000B)
  }
}

Device(LNKG)        // PGRC Routing Resource
{
  Name(_HID,EISAID("PNP0C0F"))

  Name(_UID,7)

  // Current IRQ Resource Setting.
  Method(_CRS,0,Serialized)
  {
    Name(RTLG,ResourceTemplate()
    {
      IRQ(Level,ActiveLow,Shared) {11}
    })

    CreateWordField(RTLG,1,IRQ0)
    Store (PIRG, IRQ0)

    Return(RTLG)
  }

  // PCI IRQ Status.
  Method(_STA,0,Serialized)
  {
    Return(0x000B)
  }
}

Device(LNKH)        // PHRC Routing Resource
{
  Name(_HID,EISAID("PNP0C0F"))

  Name(_UID,8)

  // Current IRQ Resource Setting.
  Method(_CRS,0,Serialized)
  {
    Name(RTLH,ResourceTemplate()
    {
      IRQ(Level,ActiveLow,Shared) {11}
    })

    CreateWordField(RTLH,1,IRQ0)
    Store (PIRH, IRQ0)

    Return(RTLH)
  }

  // PCI IRQ Status.
  Method(_STA,0,Serialized)
  {
    Return(0x000B)
  }
}
