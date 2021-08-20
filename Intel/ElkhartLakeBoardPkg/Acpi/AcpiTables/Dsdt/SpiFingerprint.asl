/**@file
 Finger Print Device of ACPI

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

//
// FPNT Connected Device
//
#define FPC1011           1
#define FPC1020           2
#define VFSI6101          3
#define VFSI7500          4
#define EGIS0300          5
#define FPC1021           6

//------------------------
// Finger Print on SPI for common use
// Note: instead of adding more touch panels, parametrize this one with appropriate _HID value and GPIO numbers
//------------------------
  Device(FPNT) {
    Method(_HID) {
      // Return FPS HID based on BIOS Setup
      If (LEqual(FPTT,FPC1011)){ Return("FPC1011") }
      If (LEqual(FPTT,FPC1020)){ Return("FPC1020") }
      If (LEqual(FPTT,VFSI6101)){ Return("VFSI6101") }
      If (LEqual(FPTT,VFSI7500)){ Return("VFSI7500") }
      If (LEqual(FPTT,EGIS0300)){ Return("EGIS0300") }
      If (LEqual(FPTT,FPC1021)){ Return("FPC1021") }
      Return("FPNT_DIS")
    }
    Method(_INI) {
      SHPO(GFPI,1) // configure gpio pad in gpio driver mode
      SHPO(GFPS,1) // configure gpio pad in gpio driver mode
    }
    Method(_STA) {
      // Is SerialIo SPI1 FPS enabled in BIOS Setup?
      If(LAnd(LNotEqual(FPTT, 0), LEqual(SPIP, SERIAL_IO_SPI_FINGERPRINT))) {
        Return(0x0F)
      }
      Return(0x00)
    }
    Method(_CRS, 0x0, Serialized) {
      Name (BBUF,ResourceTemplate () {
        GpioIo(Exclusive, PullDefault, 0, 0, IoRestrictionOutputOnly, "\\_SB.GPI0",,,GSLP) {8}
      })
      Name (IBUF,ResourceTemplate () {
        Interrupt(ResourceConsumer, Level, ActiveLow, ExclusiveAndWake,,,IINT) {0}
      })
      Name (GBUF, ResourceTemplate () {
        GpioInt (Level, ActiveLow, ExclusiveAndWake, PullDefault, 0x0000, "\\_SB.GPI0", 0x00, ResourceConsumer,GINT ) { 0 }
      })
      Name (UBUF,ResourceTemplate () {
        GpioIo(Exclusive, PullDefault, 0, 0, IoRestrictionInputOnly, "\\_SB.GPI0",,,GIRQ) {0}
      })

      CreateWordField(BBUF,GSLP._PIN,SPIN)
      CreateWordField(GBUF,GINT._PIN,GPIN)
      CreateDWordField(IBUF,IINT._INT,IPIN)
      CreateWordField(UBUF,GIRQ._PIN,UPIN)
      CreateBitField(IBUF,IINT._LL,ILVL)
      CreateBitField(IBUF,IINT._HE,ITRG)
      CreateField(GBUF,GINT._POL,2,GLVL)
      CreateBitField(GBUF,GINT._MOD,GTRG)

      Store (GNUM(GFPS),SPIN)
      Store (GNUM(GFPI),GPIN)
      Store (INUM(GFPI),IPIN)
      Store (GNUM(GFPI),UPIN)
      If (LOr(LEqual(FPTT,FPC1020), LEqual(FPTT,FPC1021))) { //FPC1020/FPC1021 has rising-edge interrupts, instead of the default level-low
        Store (0,ILVL) // interrupt active high
        Store (1,ITRG) // interrupt edge triggered
        Store (0,GLVL) // gpioint active high
        Store (1,GTRG) // gpioint edge triggered
      }
      If (LEqual(FPTT,VFSI7500)) { //VFSI7500 has rising-edge interrupts, instead of the default level-low
        Store (0,ILVL) // interrupt active high
        Store (1,ITRG) // interrupt edge triggered
      }
      //Store(? , Local3) // (_DPL) update chipselect polarity per fingerprint's version, once we receive information which FPS requires which polarity

      // Update SPI interface settings based on BIOS Setup
      Switch(ToInteger(FPTT)) {
        Case (FPC1011) {
          Store (10000000, Local1) // Connection Speed
          Store (0, Local0) // First Phase
        }
        Case (FPC1020) {
          Store (3000000, Local1) // Connection Speed 0x2Dc6C0
          Store (0, Local0) // First Phase
        }
        Case (VFSI6101) {
          Store (8000000, Local1) // Connection Speed 0x7A1200
          Store (1, Local0) // Second Phase
        }
        Case (VFSI7500) {
          Store (8000000, Local1) // Connection Speed 0x7A1200
          Store (0, Local0) // First Phase
        }
        Case (EGIS0300) {
          Store (16000000, Local1) // Connection Speed 0xF42400
          Store (0, Local0) // First Phase
        }
        Case (FPC1021) {
          Store (3000000, Local1) // Connection Speed 0x2Dc6C0
          Store (0, Local0) // First Phase
        }
        Default {
        }
      }

      If (LEqual(FPTT,FPC1011)) { Return (ConcatenateResTemplate(SPIM(SPIX,Local0,Local1),BBUF)) } // FPC1011 doesn't use interrupts
      If (LAnd(LEqual(FPTT,VFSI7500), LEqual(FPTM,0))) {  Return (ConcatenateResTemplate(ConcatenateResTemplate(SPIM(SPIX,Local0,Local1),BBUF), ConcatenateResTemplate(UBUF, GBUF))) } // VFSI7500, GpioInt
      If (LAnd(LEqual(FPTT,VFSI7500), LNotEqual(FPTM,0))) { Return (ConcatenateResTemplate(ConcatenateResTemplate(SPIM(SPIX,Local0,Local1),BBUF), ConcatenateResTemplate(UBUF, IBUF))) } // VFSI7500, Interrupt
      If (LEqual(FPTM,0)) { Return (ConcatenateResTemplate(ConcatenateResTemplate(SPIM(SPIX,Local0,Local1),BBUF), GBUF)) } // GpioInt
      Return (ConcatenateResTemplate(ConcatenateResTemplate(SPIM(SPIX,Local0,Local1),BBUF), IBUF))  //Interrupt
    }
  } // Device (FPNT)
