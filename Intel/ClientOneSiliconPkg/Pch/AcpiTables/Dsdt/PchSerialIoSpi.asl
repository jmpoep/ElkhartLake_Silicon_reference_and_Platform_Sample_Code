/**@file

  Serial IO SPI Controllers ACPI definitions

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

#define SERIAL_IO_SPI_DISABLED 0
#define SERIAL_IO_SPI_PCI      1
#define SERIAL_IO_SPI_HIDDEN   2

Scope(\_SB.PC00) {
  //
  //  SPI Hidden Resource allocation
  //  Returns resource buffer with memory ranges used but not explicitely claimed by the device
  //
  //  @param[in]  Arg0      Pci Config Base
  //
  //  @retval               Resource buffer with memory ranges
  //
  Method (SPIH, 1, Serialized) {
    OperationRegion (ICB1, SystemMemory, Arg0, Add(R_SERIAL_IO_CFG_BAR0_LOW, 16))
    Field (ICB1, AnyAcc, NoLock, Preserve) {
      Offset(R_SERIAL_IO_CFG_BAR0_LOW),
      BAR0, 64,
      BAR1, 64
    }
    Name (BUF0, ResourceTemplate () { Memory32Fixed (ReadWrite, 0, 0x1000, BFR0) })
    Name (BUF1, ResourceTemplate () { Memory32Fixed (ReadWrite, 0, 0x1000, BFR1) })
    CreateDWordField (BUF0, BFR0._BAS, ADR0)
    CreateDWordField (BUF1, BFR1._BAS, ADR1)
    Store (And (BAR0, 0xFFFFFFFFFFFFF000), ADR0) // BAR0
    Store (And (BAR1, 0xFFFFFFFFFFFFF000), ADR1) // BAR1 - PCI CFG SPACE
    ConcatenateResTemplate (BUF0, BUF1, Local0)
    Return (Local0)
  } // End SPIH

//-------------------------------------------
//  Serial IO SPI Controller 0 Configuration
//-------------------------------------------
  Device (SPI0) {
    If(LEqual(SPI0_MODE, SERIAL_IO_SPI_HIDDEN)) {
      Name (_HID, "PNP0C02")
      Method (_CRS) { Return (SPIH (SPI0_PCIE_BASE)) }
      Name (_STA, 0x3)
    }
    If(LEqual(SPI0_MODE, SERIAL_IO_SPI_PCI)) {
      Method (_DSM,4,Serialized){if(PCIC(Arg0)) { Return(PCID(Arg0,Arg1,Arg2,Arg3)) }; Return (Buffer(){0})}
      Method (_PS3) { SOD3 (SPI0_PCIE_BASE, SERIAL_IO_D3, SERIAL_IO_BAR_RESET) }
      Method (_PS0) {  }
    }
    If (LOr (LEqual (SPI0_MODE, SERIAL_IO_SPI_PCI), LEqual (SPI0_MODE, SERIAL_IO_SPI_DISABLED))) {
      Method (_ADR) { Return (SERIAL_IO_SPI0_ADR) }
    }
  }
//------------------------------------------
//  Serial IO SPI Controller 1 Configuration
//------------------------------------------
  Device (SPI1) {
    If (LEqual(SPI1_MODE, SERIAL_IO_SPI_HIDDEN)) {
      Name (_HID, "PNP0C02")
      Method (_CRS) { Return (SPIH (SPI1_PCIE_BASE)) }
      Name (_STA, 0x3)
      Method (_INI, 0, Serialized) {
        //
        //  Since for Hidden mode, OSPM wont call _PS3, hence we use this method inside _INI
        //  so that this gets called initially while OS boot up and put the SPI hidden device
        //  in D3 state. If someone brings the device to D0 after this, in runtime (Eg. SPI1
        //  PostCodes), its their responsibility to Set back to D3 again. So, that S0ix works.
        //
        Name(STMP, 0)            // scratch variable that does not cause compiler warnings as writes to Localx variables do.
        OperationRegion (SPCF, SystemMemory, SPI1_PCIE_BASE, Add (R_SERIAL_IO_CFG_PME_CTRL_STS, 4))
        Field (SPCF, ByteAcc, NoLock, Preserve) {
          Offset(R_SERIAL_IO_CFG_PME_CTRL_STS),
          PMCS, 8
        }
        Store (0x3, PMCS)
        Store (PMCS, STMP) // perform a read to avoid ordering and noncoherency problems
      }
    }
    If (LEqual(SPI1_MODE, SERIAL_IO_SPI_PCI)) {
      Method (_DSM,4,Serialized){if(PCIC(Arg0)) { Return(PCID(Arg0,Arg1,Arg2,Arg3)) }; Return (Buffer(){0})}
      Method (_PS3) { SOD3 (SPI1_PCIE_BASE, SERIAL_IO_D3, SERIAL_IO_BAR_RESET) }
      Method (_PS0) {  }
    }
    If (LOr (LEqual (SPI1_MODE, SERIAL_IO_SPI_PCI), LEqual (SPI1_MODE, SERIAL_IO_SPI_DISABLED))) {
      Method (_ADR) { Return (SERIAL_IO_SPI1_ADR) }
    }
  }
//------------------------------------------
//  Serial IO SPI Controller 2 Configuration
//------------------------------------------
  Device (SPI2) {
    If (LEqual (SPI2_MODE, SERIAL_IO_SPI_HIDDEN)) {
      Name (_HID, "PNP0C02")
      Method (_CRS) { Return (SPIH (SPI2_PCIE_BASE)) }
      Name(_STA, 0x3)
    }
    If (LEqual (SPI2_MODE, SERIAL_IO_SPI_PCI)) {
      Method (_DSM,4,Serialized){if(PCIC(Arg0)) { Return(PCID(Arg0,Arg1,Arg2,Arg3)) }; Return(Buffer(){0})}
      Method (_PS3) { SOD3 (SPI2_PCIE_BASE, SERIAL_IO_D3, SERIAL_IO_BAR_RESET) }
      Method (_PS0) {  }
    }
    If (LOr (LEqual (SPI2_MODE, SERIAL_IO_SPI_PCI), LEqual (SPI2_MODE, SERIAL_IO_SPI_DISABLED))) {
      Method (_ADR) {

         Return (SERIAL_IO_SPI2_ADR)
      }
    }
  }
} //End Scope(\_SB.PC00)

