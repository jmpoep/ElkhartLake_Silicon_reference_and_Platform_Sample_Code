/** @file
  ACPI DSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2020 Intel Corporation.

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


Method(PKG1, 1, Serialized) {
  Name (PKG, Package(1){0})
  Store(Arg0, Index(PKG,0))
  Return (PKG)
}

Method(PKG3, 3, Serialized) {
  Name (PKG, Package(3){0,0,0})
  Store(Arg0, Index(PKG,0))
  Store(Arg1, Index(PKG,1))
  Store(Arg2, Index(PKG,2))
  Return (PKG)
}

//
// SerialIo controllers use configurable timing parameters. It is possible but only optional to provide them through ACPI.
// If BIOS doesn't provide relevant methods, controllers' OS drivers will use default values, or in case of Windows use system registry.
// This sample code provides timing parameters optionally (based on USTP variable) and only for 3 SerialIo controllers out of 11.
//
if(USTP) {
  //
  // Standard Speed [SS] 100 kbit/s
  //  SCL L  - [SSLX] Serial Clock Line LOW  Period [DEFAULT: 640]
  //  SCL H  - [SSHX] Serial Clock Line HIGH Period [DEFAULT: 528]
  //  SDA Hold [SSDX] Serial Data  Line Hold Period [DEFAULT: 30]
  //
  // Fast Mode [FM] 400 kbit/s
  //  SCL L  - [FMLX] Serial Clock Line LOW  Period [DEFAULT: 160]
  //  SCL H  - [FMHX] Serial Clock Line HIGH Period [DEFAULT: 28]
  //  SDA Hold [FMDX] Serial Data  Line Hold Period [DEFAULT: 30]
  //
  // Fast Mode Plus [FM+] 1 Mbit/s
  //  SCL L  - [FPLX] Serial Clock Line LOW  Period [DEFAULT: 64]
  //  SCL H  - [FPHX] Serial Clock Line HIGH Period [DEFAULT: 48]
  //  SDA Hold [FPDX] Serial Data  Line Hold Period [DEFAULT: 30]
  //
  //
  // High Speed Mode [HSM] 3.4 Mbit/s
  //  SCL L  - [HSLX] Serial Clock Line LOW  Period [DEFAULT: 22]
  //  SCL H  - [HSHX] Serial Clock Line HIGH Period [DEFAULT: 11]
  //  SDA Hold [HSDX] Serial Data  Line Hold Period [DEFAULT: 8]
  //
  Scope(\_SB.PC00.I2C0) {
    Name (_DSD, Package () {
      ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
      Package () {
        Package (2) {"clock-frequency", IC0S}
      }
    })
    Method(SSCN){Return(PKG3(SSH0,SSL0,SSD0))}
    Method(FMCN){Return(PKG3(FMH0,FML0,FMD0))}
    Method(FPCN){Return(PKG3(FPH0,FPL0,FPD0))}
    Method(HSCN){Return(PKG3(HSH0,HSL0,HSD0))}
    Method(M0D3){Return(PKG1(M0C0))}
    Method(M1D3){Return(PKG1(M1C0))}
  }

  Scope(\_SB.PC00.I2C1) {
    Name (_DSD, Package () {
      ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
      Package () {
        Package (2) {"clock-frequency", IC1S}
      }
    })
    Method(SSCN){Return(PKG3(SSH1,SSL1,SSD1))}
    Method(FMCN){Return(PKG3(FMH1,FML1,FMD1))}
    Method(FPCN){Return(PKG3(FPH1,FPL1,FPD1))}
    Method(HSCN){Return(PKG3(HSH1,HSL1,HSD1))}
    Method(M0D3){Return(PKG1(M0C1))}
    Method(M1D3){Return(PKG1(M1C1))}
  }

  Scope(\_SB.PC00.I2C2) {
    Name (_DSD, Package () {
      ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
      Package () {
        Package (2) {"clock-frequency", IC2S}
      }
    })
    Method(SSCN){Return(PKG3(SSH2,SSL2,SSD2))}
    Method(FMCN){Return(PKG3(FMH2,FML2,FMD2))}
    Method(FPCN){Return(PKG3(FPH2,FPL2,FPD2))}
    Method(HSCN){Return(PKG3(HSH2,HSL2,HSD2))}
    Method(M0D3){Return(PKG1(M0C2))}
    Method(M1D3){Return(PKG1(M1C2))}
  }

  Scope(\_SB.PC00.I2C3) {
    Name (_DSD, Package () {
      ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
      Package () {
        Package (2) {"clock-frequency", IC3S}
      }
    })
    Method(SSCN){Return(PKG3(SSH3,SSL3,SSD3))}
    Method(FMCN){Return(PKG3(FMH3,FML3,FMD3))}
    Method(FPCN){Return(PKG3(FPH3,FPL3,FPD3))}
    Method(HSCN){Return(PKG3(HSH3,HSL3,HSD3))}
    Method(M0D3){Return(PKG1(M0C3))}
    Method(M1D3){Return(PKG1(M1C3))}
  }

  Scope(\_SB.PC00.I2C4) {
    Name (_DSD, Package () {
      ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
      Package () {
        Package (2) {"clock-frequency", IC4S}
      }
    })
    Method(SSCN){Return(PKG3(SSH4,SSL4,SSD4))}
    Method(FMCN){Return(PKG3(FMH4,FML4,FMD4))}
    Method(FPCN){Return(PKG3(FPH4,FPL4,FPD4))}
    Method(HSCN){Return(PKG3(HSH4,HSL4,HSD4))}
    Method(M0D3){Return(PKG1(M0C4))}
    Method(M1D3){Return(PKG1(M1C4))}
  }

  Scope(\_SB.PC00.I2C5) {
    Name (_DSD, Package () {
      ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
      Package () {
        Package (2) {"clock-frequency", IC5S}
      }
    })
    Method(SSCN){Return(PKG3(SSH5,SSL5,SSD5))}
    Method(FMCN){Return(PKG3(FMH5,FML5,FMD5))}
    Method(FPCN){Return(PKG3(FPH5,FPL5,FPD5))}
    Method(HSCN){Return(PKG3(HSH5,HSL5,HSD5))}
    Method(M0D3){Return(PKG1(M0C5))}
    Method(M1D3){Return(PKG1(M1C5))}
  }
  Scope(\_SB.PC00.I2C6) {
    Name (_DSD, Package () {
      ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
      Package () {
        Package (2) {"clock-frequency", IC6S}
      }
    })
    Method(SSCN){Return(PKG3(SSH6,SSL6,SSD6))}
    Method(FMCN){Return(PKG3(FMH6,FML6,FMD6))}
    Method(FPCN){Return(PKG3(FPH6,FPL6,FPD6))}
    Method(HSCN){Return(PKG3(HSH6,HSL6,HSD6))}
    Method(M0D3){Return(PKG1(M0CC))}
    Method(M1D3){Return(PKG1(M1CC))}
  }

  Scope(\_SB.PC00.I2C7) {
    Name (_DSD, Package () {
      ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
      Package () {
        Package (2) {"clock-frequency", IC7S}
      }
    })
    Method(SSCN){Return(PKG3(SSH7,SSL7,SSD7))}
    Method(FMCN){Return(PKG3(FMH7,FML7,FMD7))}
    Method(FPCN){Return(PKG3(FPH7,FPL7,FPD7))}
    Method(HSCN){Return(PKG3(HSH7,HSL7,HSD7))}
    Method(M0D3){Return(PKG1(M0CD))}
    Method(M1D3){Return(PKG1(M1CD))}
  }

  Scope(\_SB.PC00.SPI0) {
    Method(M0D3){Return(PKG1(M0C6))}           // the default value is 200
    Method(M1D3){Return(PKG1(M1C6))}           // the default value is 2000
  }

  Scope(\_SB.PC00.SPI1) {
    Method(M0D3){Return(PKG1(M0C7))}           // the default value is 200
    Method(M1D3){Return(PKG1(M1C7))}           // the default value is 2000
  }

  Scope(\_SB.PC00.SPI2) {
    Method(M0D3){Return(PKG1(M0C8))}           // the default value is 200
    Method(M1D3){Return(PKG1(M1C8))}           // the default value is 2000
  }

  Scope(\_SB.PC00.UA00) {
    Method(M0D3){Return(PKG1(M0C9))}           // the default value is 200
    Method(M1D3){Return(PKG1(M1C9))}           // the default value is 200
  }

  Scope(\_SB.PC00.UA01) {
    Method(M0D3){Return(PKG1(M0CA))}           // the default value is 200
    Method(M1D3){Return(PKG1(M1CA))}           // the default value is 200
  }

  Scope(\_SB.PC00.UA02) {
    Method(M0D3){Return(PKG1(M0CB))}           // the default value is 200
    Method(M1D3){Return(PKG1(M1CB))}           // the default value is 200
  }
}


