/** @file
  ACPI uPEP Support

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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

External(\_SB.PC00.DPOF)

If(LOr(LEqual(S0ID, 1),LGreaterEqual(OSYS, 2015))){
  Scope(\_SB.PC00.GFX0) {
    Method(_DEP) {
      Return(Package() {\_SB.PEPD})
    }
  }
  If(LNotEqual(And(PEPC, 0x03), 0)) {
    Scope(\_SB.PC00.SAT0) {
      Method(_DEP) {
      Return(Package() {\_SB.PEPD})
      }
    }
  }
  Scope(\_SB.PC00.I2C0) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.I2C1) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.I2C2) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.I2C3) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.I2C4) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.I2C5) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.SPI0) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.SPI1) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.SPI2) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.UA00) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.UA01) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.UA02) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PC00.HECI) { Name(_DEP, Package(){\_SB.PEPD}) }

  If (LNotEqual(GBES,0)) {
    Scope(\_SB.PC00.GLAN) { Name(_DEP, Package(){\_SB.PEPD}) }
  }

  Scope(\_SB.PC00.XHCI) {
    Method(_DEP) {
      Return(Package() {\_SB.PEPD})
    }
  }
  Scope(\_SB.PC00.HDAS) {
    Method(_DEP) {
      Return(Package() {\_SB.PEPD})
    }
  }
}

Scope (\_SB.PC00.RP01.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP02.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP03.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP04.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP05.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP06.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP07.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP08.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP09.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP10.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP11.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP12.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP13.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP14.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP15.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP16.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP17.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP18.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP19.PXSX)
{
  include("PepPcieSsd.asl")
}

Scope (\_SB.PC00.RP20.PXSX)
{
  include("PepPcieSsd.asl")
}

If(LOr(LEqual(S0ID, 1),LGreaterEqual(OSYS, 2015))){
  Scope(\_SB.PR00) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PR01) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PR02) { Name(_DEP, Package(){\_SB.PEPD}) }
  Scope(\_SB.PR03) { Name(_DEP, Package(){\_SB.PEPD}) }
}

Scope(\_SB)
{
  Device (PEPD)
  {
    Name (_HID, "INT33A1")
    Name (_CID, EISAID ("PNP0D80"))
    Name (_UID, 0x1)

    Name(PPD0, Package() {"\\_SB.PC00.SAT0",               0x0, Package() {0, Package() {0xFF, 0, 0x81}}})
    Name(PPD3, Package() {"\\_SB.PC00.SAT0",               0x0, Package() {0, Package() {0xFF, 3}}})
    Name(WWD3, Package() {"\\_SB.PC00.RP04",               0x0, Package() {0, Package() {0xFF, 3}}})
    Name(DEVY, Package() // uPEP Device List
    {
      //
      // 1: ACPI Device Descriptor: Fully Qualified name-string
      // 2: Enabled/Disabled Field
      //      0 = This device is disabled and applies no constraints
      //     1+ = This device is enabled and applies constraints
      // 3: Constraint Package: entry per LPI state in LPIT
      //     a. Associated LPI State UID
      //         ID == 0xFF: same constraints apply to all states in LPIT
      //     b: minimum Dx state as pre-condition
      //     c: (optional) OEM specific OEM may provide an additional encoding
      //         which further defines the D-state Constraint
      //            0x0-0x7F - Reserved
      //            0x80-0xFF - OEM defined
      //
      Package() {"\\_SB.PR00",                    0x0, Package() {0, Package() {0xFF, 0}}},                   //  0 - SB.PR00
      Package() {"\\_SB.PR01",                    0x0, Package() {0, Package() {0xFF, 0}}},                   //  1 - SB.PR01
      Package() {"\\_SB.PR02",                    0x0, Package() {0, Package() {0xFF, 0}}},                   //  2 - SB.PR02
      Package() {"\\_SB.PR03",                    0x0, Package() {0, Package() {0xFF, 0}}},                   //  3 - SB.PR03
      Package() {"\\_SB.PR04",                    0x0, Package() {0, Package() {0xFF, 0}}},                   //  4 - SB.PR04
      Package() {"\\_SB.PR05",                    0x0, Package() {0, Package() {0xFF, 0}}},                   //  5 - SB.PR05
      Package() {"\\_SB.PR06",                    0x0, Package() {0, Package() {0xFF, 0}}},                   //  6 - SB.PR06
      Package() {"\\_SB.PR07",                    0x0, Package() {0, Package() {0xFF, 0}}},                   //  7 - SB.PR07
      Package() {"\\_SB.PC00.GFX0",               0x1, Package() {0, Package() {0xFF, 3}}},                   //  8 - Gfx
      Package() {"\\_SB.PC00.SAT0",               0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             //  9 - SATA
      Package() {"\\_SB.PC00.UA00",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 10 - UART0
      Package() {"\\_SB.PC00.UA01",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 11 - UART1
      Package() {"\\_SB.PC00.I2C0",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 12 - I2C0
      Package() {"\\_SB.PC00.I2C1",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 13 - I2C1
      Package() {"\\_SB.PC00.XHCI",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 14 - XHCI
      Package() {"\\_SB.PC00.HDAS",               0x1, Package() {0, Package() {0xFF, 0, 0x81}}},             // 15 - cAVS (HDAudio)
      Package() {"\\_SB.PC00.PEMC",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 16 - EMMC
      Package() {"\\_SB.PC00.PSDC",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 17 - SCS SD Card (PCI Mode)
      Package() {"\\_SB.PC00.I2C2",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 18 - I2C2
      Package() {"\\_SB.PC00.I2C3",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 19 - I2C3
      Package() {"\\_SB.PC00.I2C4",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 20 - I2C4
      Package() {"\\_SB.PC00.I2C5",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 21 - I2C5
      Package() {"\\_SB.PC00.UA02",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 22 - UART2
      Package() {"\\_SB.PC00.SPI0",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 23 - SPI0
      Package() {"\\_SB.PC00.SPI1",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 24 - SPI1
      Package() {"\\_SB.PC00.RP01.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 25 - RP01
      Package() {"\\_SB.PC00.RP02.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 26 - RP02
      Package() {"\\_SB.PC00.RP03.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 27 - RP03
      Package() {"\\_SB.PC00.RP04.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 28 - RP04
      Package() {"\\_SB.PC00.RP05.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 29 - RP05
      Package() {"\\_SB.PC00.RP06.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 30 - RP06
      Package() {"\\_SB.PC00.RP07.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 31 - RP07
      Package() {"\\_SB.PC00.RP08.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 32 - RP08
      Package() {"\\_SB.PC00.RP09.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 33 - RP09
      Package() {"\\_SB.PC00.RP10.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 34 - RP10
      Package() {"\\_SB.PC00.RP11.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 35 - RP11
      Package() {"\\_SB.PC00.RP12.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 36 - RP12
      Package() {"\\_SB.PC00.RP13.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 37 - RP13
      Package() {"\\_SB.PC00.RP14.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 38 - RP14
      Package() {"\\_SB.PC00.RP15.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 39 - RP15
      Package() {"\\_SB.PC00.RP16.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 40 - RP16
      Package() {"\\_SB.PC00.RP17.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 41 - RP17
      Package() {"\\_SB.PC00.RP18.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 42 - RP18
      Package() {"\\_SB.PC00.RP19.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 43 - RP19
      Package() {"\\_SB.PC00.RP20.PXSX",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 44 - RP20
      Package() {"\\_SB.PC00.SAT0.VOL0",          0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 45 - RAID
      Package() {"\\_SB.PR08",                    0x0, Package() {0, Package() {0xFF, 0}}},                   // 46 - SB.PR08
      Package() {"\\_SB.PR09",                    0x0, Package() {0, Package() {0xFF, 0}}},                   // 47 - SB.PR09
      Package() {"\\_SB.PR10",                    0x0, Package() {0, Package() {0xFF, 0}}},                   // 48 - SB.PR10
      Package() {"\\_SB.PR11",                    0x0, Package() {0, Package() {0xFF, 0}}},                   // 49 - SB.PR11
      Package() {"\\_SB.PR12",                    0x0, Package() {0, Package() {0xFF, 0}}},                   // 50 - SB.PR12
      Package() {"\\_SB.PR13",                    0x0, Package() {0, Package() {0xFF, 0}}},                   // 51 - SB.PR13
      Package() {"\\_SB.PR14",                    0x0, Package() {0, Package() {0xFF, 0}}},                   // 52 - SB.PR14
      Package() {"\\_SB.PR15",                    0x0, Package() {0, Package() {0xFF, 0}}},                   // 53 - SB.PR15
      Package() {"\\_SB.PC00.SPI2",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 54 - SPI2
      Package() {"\\_SB.PC00.CNVW",               0x0, Package() {0, Package() {0xFF, 0, 0x81}}},             // 55 - CNVi WiFi
      Package() {"\\_SB.PC00.IPU0",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 56 - IPU0
      Package() {"\\_SB.PC00.HECI",               0x1, Package() {0, Package() {0xFF, 0, 0x81}}},             // 57 - CSME
      Package() {"\\_SB.PC00.GLAN",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 58 - LAN(GBE)
      Package() {"\\_SB.PC00.PEG0.PEGP",          0x0, Package() {0, Package() {0xFF, 3}}},                   // 59 - PEG0
      Package() {"\\_SB.PC00.THC0",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 60 - THC0
      Package() {"\\_SB.PC00.THC1",               0x1, Package() {0, Package() {0xFF, 3}}},                   // 61 - THC1
      Package() {"\\_SB.PC00.HDAS.IDA",           0x1, Package() {0, Package() {0xFF, 3}}},                   // 62 - IDA
      Package() {"USB\\VID_8087&PID_0AC9&MI*",    0x0, Package() {0, Package() {0xFF, 2}}},                   // 63 - CDC MBIM
      Package() {"\\_SB.PC00.RP04",               0x0, Package() {0, Package() {0xFF, 3}}},                   // 64 - RP04 WWAN D3
    })

    Name(BCCD, Package() // Bugcheck Critical Device(s)
    {
      //
      // 1: ACPI Device Descriptor: Fully Qualified name string
      // 2: Package of packages: 1 or more specific commands to power up critical device
      //  2a: Package: GAS-structure describing location of PEP accessible power control
      //    Refer to ACPI 5.0 spec section 5.2.3.1 for details
      //    a: Address Space ID (0 = System Memory)
      //       NOTE: A GAS Address Space of 0x7F (FFH) indicates remaining package
      //             elements are Intel defined
      //    b: Register bit width (32 = DWORD)
      //    c: Register bit offset
      //    d: Access size (3 = DWORD Access)
      //    e: Address (for System Memory = 64-bit physical address)
      //  2b: Package containing:
      //    a: AND mask !V not applicable for all Trigger Types
      //    b: Value (bits required to power up the critical device)
      //    c: Trigger Type:
      //         0 = Read
      //         1 = Write
      //         2 = Write followed by Read
      //         3 = Read Modify Write
      //         4 = Read Modify Write followed by Read
      //  2c: Power up delay: Time delay before next operation in uSec
      //
      Package() {"\\_SB.PC00.SAT0", Package() {
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   16000}                        // Power up delay = 16ms
        }
      },
      Package() {"\\_SB.PC00.SAT0.PRT0", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   16000}                        // Power up delay = 16ms
        }
      },
      Package() {"\\_SB.PC00.SAT0.PRT1", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   16000}                        // Power up delay = 16ms
        }
      },
      Package() {"\\_SB.PC00.SAT0.PRT2", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   16000}                        // Power up delay = 16ms
        }
      },
      Package() {"\\_SB.PC00.SAT0.PRT3", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   16000}                        // Power up delay = 16ms
        }
      },
      Package() {"\\_SB.PC00.RP01.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP02.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP03.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP04.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP05.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP06.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP07.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP08.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP09.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP10.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP11.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP12.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP13.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP14.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP15.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP16.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP17.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP18.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP19.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
      Package() {"\\_SB.PC00.RP20.PXSX", Package(){
        Package() {Package() {1, 8, 0, 1, 0xB2}, // GAS Structure 8-bit IO Port
                   Package() {0x0, 0xCD, 0x1},   // Write 0xCD
                   100000}                       // Power up delay = 100ms
        }
      },
    })

    Method(_STA, 0x0, NotSerialized)
    {
      If(LOr(LGreaterEqual(OSYS,2015), LAnd(LGreaterEqual(OSYS,2012),LEqual(S0ID, 1))))
      {
        Return(0xf)
      }
      Return(0)
    }

    Method(_DSM, 0x4, Serialized)
    {
      ADBG(Concatenate("PEPC = ", ToHexString(PEPC)))

      If(LEqual(Arg0,ToUUID("c4eb40a0-6cd2-11e2-bcfd-0800200c9a66")))
      {
        // Number of Functions (including this one)
        If(LEqual(Arg2, Zero))
        {
          Return(Buffer(One){0x7F})
        }
        // Device Constraints Enumeration
        If(LEqual(Arg2, One))
        {
          If (LEqual(S0ID, 0)) {
            Return(Package() {})
          }

          // Update uPEP device list based on PEPC (Low Power S0 Constraint)
          // Bit[1:0] - Storage (0:None, 1:Storage Controller, 2:Raid)
          // Bit[2]   - En/Dis UART0
          // Bit[3]   - En/Dis UART1
          // Bit[4]   - En/Dis PCIe NVMe/AHCI
          // Bit[5]   - En/Dis I2C0
          // Bit[6]   - En/Dis I2C1
          // Bit[7]   - En/Dis XHCI
          // Bit[8]   - En/Dis HD Audio (includes ADSP)
          // Bit[9]   - En/Dis Gfx
          // Bit[10]  - En/Dis PR0
          // Bit[11]  - En/Dis EMMC
          // Bit[12]  - En/Dis SDXC
          // Bit[13]  - En/Dis I2C2
          // Bit[14]  - En/Dis I2C3
          // Bit[15]  - En/Dis I2C4
          // Bit[16]  - En/Dis I2C5
          // Bit[17]  - En/Dis UART2
          // Bit[18]  - En/Dis SPI0
          // Bit[19]  - En/Dis SPI1
          // Bit[20]  - En/Dis SPI2
          // Bit[21]  - En/Dis IDA
          // Bit[22]  - En/Dis CSME
          // Bit[23]  - En/Dis I2C6
          // Bit[24]  - En/Dis I2C7
          // Bit[25]  - En/Dis THC0
          // Bit[26]  - En/Dis THC1


          If(LEqual(And(PEPC, BIT0), 1)) // PEPC Bit[1:0] - Storage (1:Adapter D0/F1 or 3:Adapter D3)
          {
            // Constraint for SATA Controller (SAT0)
            If(LEqual(And(PEPC, Or(BIT1, BIT0)), 1)) // PEPC Bit[1:0] - Storage (1:Adapter D0/F1)
            {
              Store (PPD0, Index (DEVY, 9)) // 9 - SATA Adapter D0
            } ElseIf(LEqual(And(PEPC, Or(BIT1, BIT0)), 3)) // PEPC Bit[1:0] - Storage (3:Adapter D3)
            {
              Store (PPD3, Index (DEVY, 9)) // 9 - SATA Adapter D3
            }
            Store (0x01, Index (DeRefOf(Index (DEVY, 9)), 1)) // Set PEP enabled
          } ElseIf(LEqual(And(PEPC, Or(BIT1, BIT0)), 2)) // PEPC Bit[1:0] - Storage (0:None, 1:Adapter D0/F1, 2:Raid, 3:Adapter D3)
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 45)), 1)) // 45 - RAID
          }

          If(LEqual(And(PEPC, BIT4), BIT4)) // PEPC Bit[4] - En/Dis PCIe NVMe/AHCI
          {
            //
            // Only enable PCIe Root Port for PEP if AHCI Controller or NVMe Class Code is connected. _DEP for PCIe would be reported based on OS
            //
            If(LOr(\_SB.PC00.RP01.PXSX.PAHC(), \_SB.PC00.RP01.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 25)), 1)) // 25 - RP01
            }
            If(LOr(\_SB.PC00.RP02.PXSX.PAHC(), \_SB.PC00.RP02.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 26)), 1)) // 26 - RP02
            }
            If(LOr(\_SB.PC00.RP03.PXSX.PAHC(), \_SB.PC00.RP03.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 27)), 1)) // 27 - RP03
            }
            If(LOr(\_SB.PC00.RP04.PXSX.PAHC(), \_SB.PC00.RP04.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 28)), 1)) // 28 - RP04
            }
            If(LOr(\_SB.PC00.RP05.PXSX.PAHC(), \_SB.PC00.RP05.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 29)), 1)) // 29 - RP05
            }
            If(LOr(\_SB.PC00.RP06.PXSX.PAHC(), \_SB.PC00.RP06.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 30)), 1)) // 30 - RP06
            }
            If(LOr(\_SB.PC00.RP07.PXSX.PAHC(), \_SB.PC00.RP07.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 31)), 1)) // 31 - RP07
            }
            If(LOr(\_SB.PC00.RP08.PXSX.PAHC(), \_SB.PC00.RP08.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 32)), 1)) // 32 - RP08
            }
            If(LOr(\_SB.PC00.RP09.PXSX.PAHC(), \_SB.PC00.RP09.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 33)), 1)) // 33 - RP09
            }
            If(LOr(\_SB.PC00.RP10.PXSX.PAHC(), \_SB.PC00.RP10.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 34)), 1)) // 34 - RP10
            }
            If(LOr(\_SB.PC00.RP11.PXSX.PAHC(), \_SB.PC00.RP11.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 35)), 1)) // 35 - RP11
            }
            If(LOr(\_SB.PC00.RP12.PXSX.PAHC(), \_SB.PC00.RP12.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 36)), 1)) // 36 - RP12
            }
            If(LOr(\_SB.PC00.RP13.PXSX.PAHC(), \_SB.PC00.RP13.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 37)), 1)) // 37 - RP13
            }
            If(LOr(\_SB.PC00.RP14.PXSX.PAHC(), \_SB.PC00.RP14.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 38)), 1)) // 38 - RP14
            }
            If(LOr(\_SB.PC00.RP15.PXSX.PAHC(), \_SB.PC00.RP15.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 39)), 1)) // 39 - RP15
            }
            If(LOr(\_SB.PC00.RP16.PXSX.PAHC(), \_SB.PC00.RP16.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 40)), 1)) // 40 - RP16
            }
            If(LOr(\_SB.PC00.RP17.PXSX.PAHC(), \_SB.PC00.RP17.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 41)), 1)) // 41 - RP17
            }
            If(LOr(\_SB.PC00.RP18.PXSX.PAHC(), \_SB.PC00.RP18.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 42)), 1)) // 42 - RP18
            }
            If(LOr(\_SB.PC00.RP19.PXSX.PAHC(), \_SB.PC00.RP19.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 43)), 1)) // 43 - RP19
            }
            If(LOr(\_SB.PC00.RP20.PXSX.PAHC(), \_SB.PC00.RP20.PXSX.PNVM())){
              Store (0x01, Index (DeRefOf(Index (DEVY, 44)), 1)) // 44 - RP20
            }
          }

          If(LAnd(LGreaterEqual(OSYS, 2015), LNotEqual(WRTO, 0))) {
            //
            // WRTO - WWAN RTD3 Option
            //   3: D3/L2
            //   1: D0/L1.2
            //   0: Disabled
            //
            If(\_SB.PC00.RP04.PXSX.WWST()) {
              If(LEqual(WRTO, 3)) {
                // Put D3 constraint on RP
                Store ("\\_SB.PC00.RP04", Index (WWD3, 0))
                Store (WWD3, Index (DEVY, 64))                     // 64 - RP04 D3
                Store (0x01, Index (DeRefOf(Index (DEVY, 64)), 1)) // 64 - RP04 WWAN
              }
              If(LEqual(WRTO, 1)) {
                // Put D2 constraint on CDC MBIM
                Store (0x1, Index (DeRefOf(Index (DEVY, 63)), 1)) // 63 - CDC MBIM
              }
            }
          }

          If(LEqual(And(PEPC, BIT2), 0)) // PEPC Bit[2] - En/Dis UART0
          {
            // Disabled UA00
            Store (0x00, Index (DeRefOf(Index (DEVY, 10)), 1)) // 10 - UART0
          }

          If(LEqual(And(PEPC, BIT3), 0)) // PEPC Bit[3] - En/Dis UART1
          {
            // Disabled UA01
            Store (0x00, Index (DeRefOf(Index (DEVY, 11)), 1)) // 11 - UART1
          }

          If(LEqual(And(PEPC, BIT4), 0)) // PEPC Bit[4] - Unused
          {

          }

          If(LEqual(And(PEPC, BIT5), 0)) // PEPC Bit[5] - En/Dis I2C0
          {
            // Disabled I2C0
            Store (0x00, Index (DeRefOf(Index (DEVY, 12)), 1)) // 12 - I2C0
          }

          If(LEqual(And(PEPC, BIT6), 0))  // PEPC Bit[6] - En/Dis I2C1
          {
            // Disabled I2C1
            Store (0x00, Index (DeRefOf(Index (DEVY, 13)), 1)) // 13 - I2C1
          }

          If(LEqual(And(PEPC, BIT7), 0))  // PEPC Bit[7] - En/Dis XHCI
          {
            // Disabled XHCI
            Store (0x00, Index (DeRefOf(Index (DEVY, 14)), 1)) // 14 - XHCI
          }

          If(LEqual(And(PEPC, BIT8), 0)) // PEPC Bit[8] - En/Dis Azalia
          {
            // Disabled Azalia
            Store (0x00, Index (DeRefOf(Index (DEVY, 15)), 1)) // 15 - HD Audio (includes ADSP)
          }

          If(LEqual(And(PEPC, BIT9), 0)) // PEPC Bit[9] - En/Dis Gfx
          {
            // Disabled Gfx
            Store (0x00, Index (DeRefOf(Index (DEVY, 8)), 1)) // 8 - Gfx
          }

          // Apply PEP constraints for CPU,
          // Based on number of threads
          If (LGreaterEqual(TCNT, 1))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 0)), 1))  // 0 - PR00
          }
          If (LGreaterEqual(TCNT, 2))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 1)), 1))  // 1 - PR01
          }
          If (LGreaterEqual(TCNT, 3))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 2)), 1))  // 2 - PR02
          }
          If (LGreaterEqual(TCNT, 4))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 3)), 1))  // 3 - PR03
          }
          If (LGreaterEqual(TCNT, 5))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 4)), 1))  // 4 - PR04
          }
          If (LGreaterEqual(TCNT, 6))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 5)), 1))  // 5 - PR05
          }
          If (LGreaterEqual(TCNT, 7))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 6)), 1))  // 6 - PR06
          }
          If (LGreaterEqual(TCNT, 8))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 7)), 1))  // 7 - PR07
          }
          If (LGreaterEqual(TCNT, 9))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 46)), 1))  // 46 - PR08
          }
          If (LGreaterEqual(TCNT, 10))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 47)), 1))  // 47 - PR09
          }
          If (LGreaterEqual(TCNT, 11))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 48)), 1))  // 48 - PR10
          }
          If (LGreaterEqual(TCNT, 12))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 49)), 1))  // 49 - PR11
          }
          If (LGreaterEqual(TCNT, 13))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 50)), 1))  // 50 - PR12
          }
          If (LGreaterEqual(TCNT, 14))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 51)), 1))  // 51 - PR13
          }
          If (LGreaterEqual(TCNT, 15))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 52)), 1))  // 52 - PR14
          }
          If (LGreaterEqual(TCNT, 16))
          {
            Store (0x01, Index (DeRefOf(Index (DEVY, 53)), 1))  // 53 - PR15
          }

          If(LEqual(And(PEPC, BIT10), 0)) // PEPC Bit[10] - En/Dis CPU
          {
            // Disabled PEP PR0
            Store (0x00, Index (DeRefOf(Index (DEVY, 0)), 1))   // 0 -  PR00
            Store (0x00, Index (DeRefOf(Index (DEVY, 1)), 1))   // 1 -  PR01
            Store (0x00, Index (DeRefOf(Index (DEVY, 2)), 1))   // 2 -  PR02
            Store (0x00, Index (DeRefOf(Index (DEVY, 3)), 1))   // 3 -  PR03
            Store (0x00, Index (DeRefOf(Index (DEVY, 4)), 1))   // 4 -  PR04
            Store (0x00, Index (DeRefOf(Index (DEVY, 5)), 1))   // 5 -  PR05
            Store (0x00, Index (DeRefOf(Index (DEVY, 6)), 1))   // 6 -  PR06
            Store (0x00, Index (DeRefOf(Index (DEVY, 7)), 1))   // 7 -  PR07
            Store (0x00, Index (DeRefOf(Index (DEVY, 46)), 1))  // 46 - PR08
            Store (0x00, Index (DeRefOf(Index (DEVY, 47)), 1))  // 47 - PR09
            Store (0x00, Index (DeRefOf(Index (DEVY, 48)), 1))  // 48 - PR10
            Store (0x00, Index (DeRefOf(Index (DEVY, 49)), 1))  // 49 - PR11
            Store (0x00, Index (DeRefOf(Index (DEVY, 50)), 1))  // 50 - PR12
            Store (0x00, Index (DeRefOf(Index (DEVY, 51)), 1))  // 51 - PR13
            Store (0x00, Index (DeRefOf(Index (DEVY, 52)), 1))  // 52 - PR14
            Store (0x00, Index (DeRefOf(Index (DEVY, 53)), 1))  // 53 - PR15
          }

          If(LOr(LEqual(And(PEPC, BIT11), 0), LEqual(EMCE,0))) // PEPC Bit[11] - En/Dis eMMC
          {
            // Disabled eMMC
            Store (0x00, Index (DeRefOf(Index (DEVY, 16)), 1)) // 16 - EMMC
          }

          If(LOr(LEqual(And(PEPC, BIT12), 0), LEqual(SDCE,0))) // PEPC Bit[12] - En/Dis SDXC
          {
            // Disabled SDXC
            Store (0x00, Index (DeRefOf(Index (DEVY, 17)), 1)) // 17 - SCS SD Card (PCI Mode)
          }

          If(LEqual(And(PEPC, BIT13), 0)) { // PEPC Bit[13] - En/Dis I2C2
            Store (0x00, Index (DeRefOf(Index (DEVY, 18)), 1)) // 18 - I2C2
          }

          If(LEqual(And(PEPC, BIT14),0)) { // PEPC Bit[14] - En/Dis I2C3
            Store (0x00, Index (DeRefOf(Index (DEVY, 19)), 1)) // 19 - I2C3
          }

          If(LEqual(And(PEPC, BIT15), 0)) { // PEPC Bit[15] - En/Dis I2C4
            Store (0x00, Index (DeRefOf(Index (DEVY, 20)), 1)) // 20 - I2C4
          }

          If(LEqual(And(PEPC, BIT16), 0)) { // PEPC Bit[16] - En/Dis I2C5
            Store (0x00, Index (DeRefOf(Index (DEVY, 21)), 1)) // 21 - I2C5
          }

          If(LEqual(And(PEPC, BIT17), 0)) { // PEPC Bit[17] - En/Dis UART2
            Store (0x00, Index (DeRefOf(Index (DEVY, 22)), 1)) // 22 - UART2
          }

          If(LEqual(And(PEPC, BIT18), 0)) { // PEPC Bit[18] - En/Dis SPI0
            Store (0x00, Index (DeRefOf(Index (DEVY, 23)), 1)) // 23 - SPI0
          }

          If(LEqual(And(PEPC, BIT19), 0)) { // PEPC Bit[19] - En/Dis SPI1
            Store (0x00, Index (DeRefOf(Index (DEVY, 24)), 1)) // 24 - SPI1
          }

          If(LEqual(And(PEPC, BIT20), 0)) { // PEPC Bit[20] - En/Dis SPI2
            Store (0x00, Index (DeRefOf(Index (DEVY, 54)), 1)) // 54 - SPI2
          }

          //If(LEqual(And(PEPC, BIT21), 0)) { // PEPC Bit[21] - En/Dis IDA
            Store (0x00, Index (DeRefOf(Index (DEVY, 62)), 1)) // 62 - IDA
          //}

          If(LEqual(And(PEPC, BIT22), 0)) { // PEPC Bit[22] - En/Dis CSME
            Store (0x00, Index (DeRefOf(Index (DEVY, 57)), 1)) // 57 - CSME
          }

          If(LEqual(And(PEPC, BIT23), 0)) { // PEPC Bit[23] - Unused

          }

          If(LEqual(And(PEPC, BIT24), 0)) { // PEPC Bit[24] - Unused

          }

          If(LEqual(And(PEPC, BIT25), 0)) { // PEPC Bit[25] - En/Dis THC0
            Store (0x00, Index (DeRefOf(Index (DEVY, 60)), 1)) // 60 - THC0
          }

          If(LEqual(And(PEPC, BIT26), 0)) { // PEPC Bit[26] - En/Dis THC1
            Store (0x00, Index (DeRefOf(Index (DEVY, 61)), 1)) // 61 - THC1
          }

          If(LGreaterEqual(OSYS,2015)){ // Add D3 uPEP constraint for PCIe-based WIFI on Win. Threshold
            If(\_SB.PC00.RP01.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 25)), 2)), 1)), 1)) // 25 - RP01
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 25)), 2)), 1)), 2)) // 25 - RP01
              Store (0x01, Index (DeRefOf(Index (DEVY, 25)), 1)) // 25 - RP01
            }
            If(\_SB.PC00.RP02.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 26)), 2)), 1)), 1)) // 26 - RP02
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 26)), 2)), 1)), 2)) // 26 - RP02
              Store (0x01, Index (DeRefOf(Index (DEVY, 26)), 1)) // 26 - RP02
            }
            If(\_SB.PC00.RP03.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 27)), 2)), 1)), 1)) // 27 - RP03
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 27)), 2)), 1)), 2)) // 27 - RP03
              Store (0x01, Index (DeRefOf(Index (DEVY, 27)), 1)) // 27 - RP03
            }
            If(\_SB.PC00.RP04.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 28)), 2)), 1)), 1)) // 28 - RP04
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 28)), 2)), 1)), 2)) // 28 - RP04
              Store (0x01, Index (DeRefOf(Index (DEVY, 28)), 1)) // 28 - RP04
            }
            If(\_SB.PC00.RP05.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 29)), 2)), 1)), 1)) // 29 - RP05
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 29)), 2)), 1)), 2)) // 29 - RP05
              Store (0x01, Index (DeRefOf(Index (DEVY, 29)), 1)) // 29 - RP05
            }
            If(\_SB.PC00.RP06.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 30)), 2)), 1)), 1)) // 30 - RP06
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 30)), 2)), 1)), 2)) // 30 - RP06
              Store (0x01, Index (DeRefOf(Index (DEVY, 30)), 1)) // 30 - RP06
            }
            If(\_SB.PC00.RP07.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 31)), 2)), 1)), 1)) // 31 - RP07
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 31)), 2)), 1)), 2)) // 31 - RP07
              Store (0x01, Index (DeRefOf(Index (DEVY, 31)), 1)) // 31 - RP07
            }
            If(\_SB.PC00.RP08.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 32)), 2)), 1)), 1)) // 32 - RP08
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 32)), 2)), 1)), 2)) // 32 - RP08
              Store (0x01, Index (DeRefOf(Index (DEVY, 32)), 1)) // 32 - RP08
            }
            If(\_SB.PC00.RP09.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 33)), 2)), 1)), 1)) // 33 - RP09
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 33)), 2)), 1)), 2)) // 33 - RP09
              Store (0x01, Index (DeRefOf(Index (DEVY, 33)), 1)) // 33 - RP09
            }
            If(\_SB.PC00.RP10.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 34)), 2)), 1)), 1)) // 34 - RP10
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 34)), 2)), 1)), 2)) // 34 - RP10
              Store (0x01, Index (DeRefOf(Index (DEVY, 34)), 1)) // 34 - RP10
            }
            If(\_SB.PC00.RP11.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 35)), 2)), 1)), 1)) // 35 - RP11
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 35)), 2)), 1)), 2)) // 35 - RP11
              Store (0x01, Index (DeRefOf(Index (DEVY, 35)), 1)) // 35 - RP11
            }
            If(\_SB.PC00.RP12.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 36)), 2)), 1)), 1)) // 36 - RP12
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 36)), 2)), 1)), 2)) // 36 - RP12
              Store (0x01, Index (DeRefOf(Index (DEVY, 36)), 1)) // 36 - RP12
            }
            If(\_SB.PC00.RP13.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 37)), 2)), 1)), 1)) // 37 - RP13
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 37)), 2)), 1)), 2)) // 37 - RP13
              Store (0x01, Index (DeRefOf(Index (DEVY, 37)), 1)) // 33 - RP13
            }
            If(\_SB.PC00.RP14.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 38)), 2)), 1)), 1)) // 38 - RP14
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 38)), 2)), 1)), 2)) // 38 - RP14
              Store (0x01, Index (DeRefOf(Index (DEVY, 38)), 1)) // 34 - RP14
            }
            If(\_SB.PC00.RP15.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 39)), 2)), 1)), 1)) // 39 - RP15
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 39)), 2)), 1)), 2)) // 39 - RP15
              Store (0x01, Index (DeRefOf(Index (DEVY, 39)), 1)) // 39 - RP15
            }
            If(\_SB.PC00.RP16.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 40)), 2)), 1)), 1)) // 40 - RP16
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 40)), 2)), 1)), 2)) // 40 - RP16
              Store (0x01, Index (DeRefOf(Index (DEVY, 40)), 1)) // 40 - RP16
            }
            If(\_SB.PC00.RP17.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 41)), 2)), 1)), 1)) // 41 - RP17
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 41)), 2)), 1)), 2)) // 41 - RP17
              Store (0x01, Index (DeRefOf(Index (DEVY, 41)), 1)) // 41 - RP17
            }
            If(\_SB.PC00.RP18.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 42)), 2)), 1)), 1)) // 42 - RP18
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 42)), 2)), 1)), 2)) // 42 - RP18
              Store (0x01, Index (DeRefOf(Index (DEVY, 42)), 1)) // 42 - RP18
            }
            If(\_SB.PC00.RP19.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 43)), 2)), 1)), 1)) // 43 - RP19
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 43)), 2)), 1)), 2)) // 43 - RP19
              Store (0x01, Index (DeRefOf(Index (DEVY, 43)), 1)) // 43 - RP19
            }
            If(\_SB.PC00.RP20.PXSX.WIST()){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 44)), 2)), 1)), 1)) // 44 - RP20
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 44)), 2)), 1)), 2)) // 44 - RP20
              Store (0x01, Index (DeRefOf(Index (DEVY, 44)), 1)) // 44 - RP20
            }
            If(LNotEqual(\_SB.PC00.CNVW.VDID, 0xFFFFFFFF)){
              Store (3, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 55)), 2)), 1)), 1)) // 55 - CNVi- WiFI
              Store (0, Index(DeRefOf(Index(DeRefOf(Index (DeRefOf(Index (DEVY, 55)), 2)), 1)), 2)) // 55 - CNVi- WiFI
              Store (0x01, Index (DeRefOf(Index (DEVY, 55)), 1)) // 55 - CNVi- WiFI
            }
          }

          Return(DEVY)
        }

        // BCCD
        If(LEqual(Arg2, 2))
        {
          Return(BCCD)
        }

        // Screen off notification
        If(LEqual(Arg2, 0x3))
        {
          // no action for screen off
          If(LEqual(S0ID, 1)) { //S0ID: >=1: CS 0: non-CS
            D8XH (0, 0xC5)
            D8XH (1, 0)
          }
        }

        // Screen on notification
        If(LEqual(Arg2, 0x4))
        {
          // no action for screen on
          If(LEqual(S0ID, 1)) { //S0ID: >=1: CS 0: non-CS
            D8XH (0, 0xC5)
            D8XH (1, 0xAB)
          }
        }

        // resiliency phase entry (deep standby entry)
        If(LEqual(Arg2, 0x5))
        {
          If(LEqual(S0ID, 1)) { //S0ID: >=1: CS 0: non-CS
            // call method specific to CS platforms when the system is in a
            // standby state with very limited SW activities
            \GUAM(1) // 0x01 - Power State Standby (CS Resiliency Entry)
          }
#ifdef EC_SUPPORT
          \_SB.PC00.LPCB.H_EC.ECNT(1) // 0x01 - Call method to notify EC of Idle Resiliency entry
#endif
        }

        // resiliency phase exit (deep standby exit)
        If(LEqual(Arg2, 0x6))
        {
          If(LEqual(S0ID, 1)) { //S0ID: >=1: CS 0: non-CS
            // call method specific to CS platforms when the system is in a
            // standby state with very limited SW activities
            \GUAM(0) // 0x00 - Power State On (CS Resiliency Exit)
          }
#ifdef EC_SUPPORT
          \_SB.PC00.LPCB.H_EC.ECNT(0) // 0x00 - Call method to notify EC of Idle Resiliency exit
#endif
        }
      }// If(LEqual(Arg0,ToUUID("c4eb40a0-6cd2-11e2-bcfd-0800200c9a66")))
      Return (Buffer() {0})
    } // Method(_DSM)
  } //device (PEPD)
} // End Scope(\_SB)
