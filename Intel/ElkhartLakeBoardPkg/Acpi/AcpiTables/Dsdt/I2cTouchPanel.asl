/**@file
 Touch Panel Device of ACPI

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
// TPL Connected Device
//
#define ATMEL3432_PANEL               1
#define ATMEL2952_PANEL               2
#define ELAN2097_PANEL                3
#define NTRIG_SAMSUNG_PANEL           4
#define NTRIG_SHARP_PANEL             5
#define WACOM_PANEL                   6
#define SERIAL_IO_TPL_CUSTOM_DEVICE   7 // Custom TouchPanel device

//------------------------
// Touch Panels on I2C for common use
// Note: instead of adding more touch panels, parametrize this one with appropriate _HID value and GPIO numbers
//------------------------
  Device (TPL1) {
    Name (HID2,0)
    Name (SBFB, ResourceTemplate () { I2cSerialBus (0,ControllerInitiated,400000,AddressingMode7Bit,"NULL",,,I2CB) })
    Name (SBFG, ResourceTemplate () {
      GpioInt (Level, ActiveLow, Exclusive, PullDefault, 0x0000, "\\_SB.GPI0", 0x00, ResourceConsumer,INTG ) { 0 }
    })
    Name (SBFI, ResourceTemplate () {
      Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive,,,INTI) {0}
    })
    CreateWordField(SBFB,I2CB._ADR,BADR)
    CreateDWordField(SBFB,I2CB._SPE,SPED)
    CreateWordField (SBFG,INTG._PIN,INT1)
    CreateDWordField(SBFI,INTI._INT,INT2)
    Method(_INI) {
      If (LLess(OSYS,2012)) { SRXO(GPLI,1) }
      Store (GNUM(GPLI),INT1)
      Store (INUM(GPLI),INT2)
      If (LEqual(TPLM,0)) {
        SHPO(GPLI,1) // configure gpio pad in gpio driver mode
      }
      If (LEqual(TPLT, ATMEL3432_PANEL)) {
        Store ("ATML3432",_HID)
        Store (0,HID2)
        Store (0x4C,BADR)
        Store (400000,SPED)
        Return
      }
      If (LEqual(TPLT, ATMEL2952_PANEL)) {
        Store ("ATML2952",_HID)
        Store (0,HID2)
        Store (0x4A,BADR)
        Store (400000,SPED)
        Return
      }
      If (LEqual(TPLT, ELAN2097_PANEL)) {
        Store ("ELAN2097",_HID)
        Store (1,HID2)
        Store (0x10,BADR)
        Store (400000,SPED)
        Return
      }
      If (LEqual(TPLT, NTRIG_SAMSUNG_PANEL)) {
        Store ("NTRG0001",_HID)
        Store (1,HID2)
        Store (0x07,BADR)
        Store (400000,SPED)
        Return
      }
      If (LEqual(TPLT, NTRIG_SHARP_PANEL)) {
        Store ("NTRG0002",_HID)
        Store (1,HID2)
        Store (0x64,BADR)
        Store (400000,SPED)
        Return
      }
      If(LEqual(TPLT, WACOM_PANEL)) {
        Store("WCOM508E",_HID)
        Store(1,HID2)
        Store(0x0A,BADR)
        If (LEqual(TPLS,0)) { Store( 400000,SPED) } // Fast mode
        If (LEqual(TPLS,1)) { Store( 400000,SPED) } // Fast mode
        If (LEqual(TPLS,2)) { Store(1000000,SPED) } // Fast mode
        Return
      }
      If(LEqual(TPLT, SERIAL_IO_TPL_CUSTOM_DEVICE)) { // Custom TouchPanel
        Store("CUST0000",_HID)
        Store(TPLH,HID2)
        Store(TPLB,BADR)
        If (LEqual(TPLS,0)) { Store( 100000,SPED) }
        If (LEqual(TPLS,1)) { Store( 400000,SPED) }
        If (LEqual(TPLS,2)) { Store(1000000,SPED) }
        Return
      }
    }

    Name (_HID, "XXXX0000")
    Name (_CID, "PNP0C50")
    Name (_S0W, 4)
    Method(_DSM, 0x4, Serialized) {
      If (LEqual(Arg0,HIDG)) { Return(HIDD(Arg0,Arg1,Arg2,Arg3,HID2)) }
      If (LEqual(Arg0,TP7G)) { Return(TP7D(Arg0,Arg1,Arg2,Arg3,SBFB,SBFG)) }
      Return (Buffer(1){0})
    }

    Method (_STA, 0, NotSerialized) {
      If (LAnd(LNotEqual(TPLT,0),And( I2CN, SERIAL_IO_I2C_TOUCHPANEL))) { Return (0x0F) }
      Return (0x00)
    }

    Method (_CRS, 0, NotSerialized) {
      If (LLess(OSYS, 2012)) { Return (SBFI) } // For Windows 7 only report Interrupt; it doesn't support ACPI5.0 and wouldn't understand GpioInt nor I2cBus
      If (LEqual(TPLM,0)) { Return (ConcatenateResTemplate(I2CM(I2CX,BADR,SPED), SBFG)) }
      Return (ConcatenateResTemplate(I2CM(I2CX,BADR,SPED), SBFI))
    }
  } // Device (TPL0)

