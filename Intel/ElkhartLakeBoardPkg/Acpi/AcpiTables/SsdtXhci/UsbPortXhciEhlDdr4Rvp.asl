/**@file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

DefinitionBlock (
    "UsbPortXhciEhlDdr4Rvp.aml",
    "SSDT",
    0x02, // SHAD revision.
        // A Revision field value greater than or equal to 2 signifies that integers
        // declared within the Definition Block are to be evaluated as 64-bit values
    "INTEL", // OEM ID (6 byte string)
    "xh_tudd4", // OEM table ID  (8 byte string) BoardIdEhlLp4xType4Rvp
    0x0 // OEM version of DSDT table (4 byte Integer)
    )
{
  External(\_SB.PC00.XHCI.RHUB.HS01, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS02, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS03, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS04, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS05, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS06, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS07, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS08, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS09, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS10, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS01, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS02, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS03, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS04, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS05, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS06, DeviceObj)
  External(\_SB.UBTC.RUCC, MethodObj)
  External(\_SB.PC00.CNIP, MethodObj)
  External(\_SB.PC00.RP03.PXSX.WIST, MethodObj)

  External(SXI1,IntObj) // SdevXhciInterfaceNumber1
  External(SXI2,IntObj) // SdevXhciInterfaceNumber2
  External(SXP1,IntObj) // SdevXhciRootPortNumber1
  External(SXP2,IntObj) // SdevXhciRootPortNumber2

  External(ATDV)
  External(BTSE)
  External(BTBR)
  External(BED2)
  External(BED3)
  External(BTLE)
  External(BTL2)
  External(BTLL)

  Method(GPLD, 2, Serialized) {
    //
    // Arg0:  Visible
    // Arg1:  Group position
    //
    Name(PCKG, Package() { Buffer(0x10) {} })
    CreateField(DerefOf(Index(PCKG,0)), 0, 7, REV)
    Store(2,REV)
    CreateField(DerefOf(Index(PCKG,0)), 7, 1, RGB)
    Store(1,RGB)
    CreateField(DerefOf(Index(PCKG,0)), 64, 1, VISI) // Arg 0
    Store(Arg0, VISI)
    CreateField(DerefOf(Index(PCKG,0)), 87, 8, GPOS) // Arg 1
    Store(Arg1, GPOS)
    return (PCKG)
  }

  Method(GUPC, 2, Serialized) {
    /*
    Arg0: Connectable
    Non-Zero value: Connectable

    Arg1: Type
    0x00: Type A connector
    0x01: Mini-AB connector
    0x02: ExpressCard
    0x03: USB 3 Standard-A connector
    0x04: USB 3 Standard-B connector
    0x05: USB 3 Micro-B connector
    0x06: USB 3 Micro-AB connector
    0x07: USB 3 Power-B connector
    0x08: Type C connector - USB2-only
    0x09: Type C connector - USB2 and SS with Switch
    0x0A: Type C connector - USB2 and SS without Switch
    0x0B - 0xFE: Reserved
    0xFF: Proprietary connector
    */
    Name(PCKG, Package(4) { 0xFF, 0xFF, 0, 0 } )
    Store(Arg0,Index(PCKG,0))
    Store(Arg1,Index(PCKG,1))
    return (PCKG)
  }
  //
  // PCH XHCI Ports
  //
  Scope (\_SB.PC00.XHCI.RHUB.HS01) {
    // Maps to Type C connector 1
    Method(_UPC) {
      Return (GUPC(1, 0x0A))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x02))
    }
    If (LAnd(CondRefOf(SXI1),CondRefOf(SXP1))) {
      If(LAnd(LGreater(SXI1,0),LEqual(SXP1,1))) {
        Device (CIR) {
          ///
          /// Address is Port + Interface number
          ///
          Method (_ADR, 0) {
            Return (Add(1,SXI1))
          }
        }
      }
    }
    If (LAnd(CondRefOf(SXI2),CondRefOf(SXP2))) {
      If(LAnd(LGreater(SXI2,0),LEqual(SXP2,1))) {
        Device (CIR2) {
          ///
          /// Address is Port + Interface number
          ///
          Method (_ADR, 0) {
            Return (Add(1,SXI2))
          }
        }
      }
    }
  }
  Scope (\_SB.PC00.XHCI.RHUB.HS02) {
    // Maps to USB3/2 Type A connector
    Method(_UPC) {
      Return (GUPC(1, 0x00))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x03))
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.HS03) {
    // Maps to USB3/2 Type A connector
    Method(_UPC) {
      Return (GUPC(1, 0x00))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x04))
    }
  }

  If (\_SB.PC00.RP03.PXSX.WIST()) {
    Scope (\_SB.PC00.XHCI.RHUB.HS03) {
      Include("AntennaDiversity.asl")
      Include("BtRegulatory.asl")
      Include("GeneralPurposeConfig.asl")
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.HS04) {
    // Maps to USB3/2 Type A connector
    Method(_UPC) {
      Return (GUPC(1, 0x00))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x05))
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.HS05) {
    // Maps to M2
    Method(_UPC) {
      Return (GUPC(0, 0xFF))
    }
    Method(_PLD) {
      Return (GPLD(0x00, 0x00))
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.HS06) {
    // Maps to USB3/2 Type A connector
    Method(_UPC) {
      Return (GUPC(1, 0x00))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x06))
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.HS07) {
    // Maps to USB3/2 Type A connector
    Method(_UPC) {
      Return (GUPC(1, 0x00))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x07))
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.HS08) {
    // Maps to USB3/2 Type A connector
    Method(_UPC) {
      Return (GUPC(1, 0x00))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x08))
    }
    If (LAnd(CondRefOf(SXI1),CondRefOf(SXP1))) {
      If(LAnd(LGreater(SXI1,0),LEqual(SXP1,8))) {
        Device (CIR) {
          ///
          /// Address is Port + Interface number
          ///
          Method (_ADR, 0) {
            Return (Add(8,SXI1))
          }
        }
      }
    }
    If (LAnd(CondRefOf(SXI2),CondRefOf(SXP2))) {
      If(LAnd(LGreater(SXI2,0),LEqual(SXP2,8))) {
        Device (CIR2) {
          ///
          /// Address is Port + Interface number
          ///
          Method (_ADR, 0) {
            Return (Add(8,SXI2))
          }
        }
      }
    }
  }
  Scope (\_SB.PC00.XHCI.RHUB.HS09) {
    // Maps to USB2 Type A connector
    Method(_UPC) {
      Return (GUPC(1, 0x00))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x09))
    }
    If (LAnd(CondRefOf(SXI1),CondRefOf(SXP1))) {
      If(LAnd(LGreater(SXI1,0),LEqual(SXP1,9))) {
        Device (CIR) {
          ///
          /// Address is Port + Interface number
          ///
          Method (_ADR, 0) {
            Return (Add(9,SXI1))
          }
        }
      }
    }
    If (LAnd(CondRefOf(SXI2),CondRefOf(SXP2))) {
      If(LAnd(LGreater(SXI2,0),LEqual(SXP2,9))) {
        Device (CIR2) {
          ///
          /// Address is Port + Interface number
          ///
          Method (_ADR, 0) {
            Return (Add(9,SXI2))
          }
        }
      }
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.HS10) {
    // Maps to M2
    Method(_UPC) {
      Return (GUPC(0, 0xFF))
    }
    Method(_PLD) {
      Return (GPLD(0x00, 0x00))
    }
    If (LAnd(CondRefOf(SXI1),CondRefOf(SXP1))) {
      If(LAnd(LGreater(SXI1,0),LEqual(SXP1,10))) {
        Device (CIR) {
          ///
          /// Address is Port + Interface number
          ///
          Method (_ADR, 0) {
            Return (Add(10,SXI1))
          }
        }
      }
    }
    If (LAnd(CondRefOf(SXI2),CondRefOf(SXP2))) {
      If(LAnd(LGreater(SXI2,0),LEqual(SXP2,10))) {
        Device (CIR2) {
          ///
          /// Address is Port + Interface number
          ///
          Method (_ADR, 0) {
            Return (Add(10,SXI2))
          }
        }
      }
    }
  }
  Scope (\_SB.PC00.XHCI.RHUB.SS01) {
    // Maps to Type C connector 1
    Method(_UPC) {
      Return (GUPC(1, 0x0A))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x02))
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.SS02) {
    // Maps to USB3/2 Type A connector
    Method(_UPC) {
      Return (GUPC(1,0x0))
    }
    Method(_PLD) {
      Return (GPLD(1,0x03))
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.SS03) {
    // Maps to USB3/2 Type A connector
    Method(_UPC) {
      Return (GUPC(1, 0x00))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x04))
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.SS04) {
    // Maps to USB3/2 Type A connector
    Method(_UPC) {
      Return (GUPC(1, 0x00))
    }
    Method(_PLD) {
      Return (GPLD(1, 0x05))
    }
}
}
