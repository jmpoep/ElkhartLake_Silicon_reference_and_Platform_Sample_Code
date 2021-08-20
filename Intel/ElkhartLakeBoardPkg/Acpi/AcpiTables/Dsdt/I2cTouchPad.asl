/**@file
 Touch Pad Device of ACPI

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
// TPD Connected Device
//
#define SYNAPTICS_PRECISION_TOUCHPAD  1
#define SYNAPTICS_FORCEPAD            2
// 3,4: reserved
#define SERIAL_IO_TPD_CUSTOM_DEVICE   5 // Custom TouchPad device
#define ALPS_PRECISION_TOUCHPAD       6

//------------------------
// Touch Pads on I2C for common use
// Note: instead of adding more touch pads, parametrize this one with appropriate _HID value and GPIO numbers
//------------------------
  Device (TPD0) {
    Name (HID2,0)
    Name (SBFB, ResourceTemplate () { I2cSerialBus (0,ControllerInitiated,400000,AddressingMode7Bit,"NULL",,,I2CB) })
    Name (SBFG, ResourceTemplate () {
      GpioInt (Level, ActiveLow, ExclusiveAndWake, PullDefault, 0x0000, "\\_SB.GPI0", 0x00, ResourceConsumer, INTG) {0}
    })
    Name (SBFI, ResourceTemplate () {
      Interrupt (ResourceConsumer, Level, ActiveLow, ExclusiveAndWake,,,INTI) {0}
    })
    CreateWordField(SBFB,I2CB._ADR,BADR)
    CreateDWordField(SBFB,I2CB._SPE,SPED)
    CreateWordField (SBFG,INTG._PIN,INT1)
    CreateDWordField(SBFI,INTI._INT,INT2)
    Method(_INI) {
      If (LLess(OSYS, 2012)) { SRXO(GPDI, 1) }
      Store (GNUM(GPDI), INT1)
      Store (INUM(GPDI), INT2)
      If (LEqual(TPDM, 0)) {
        SHPO(GPDI, 1) // configure gpio pad in gpio driver mode
      }
      If (LEqual(TPDT, SYNAPTICS_PRECISION_TOUCHPAD)) {
        Store ("SYNA2393", _HID)
        Store (0x20, HID2)
        Return
      }
      If (LEqual(TPDT, SYNAPTICS_FORCEPAD)) {
        Store ("06CB2846", _HID)
        Store (0x20, HID2)
        Return
      }
      If (LEqual(TPDT, ALPS_PRECISION_TOUCHPAD)) { // ClickPad
        Store ("ALPS0000", _HID)                   // TODO - UPDATE ONCE PROVIDED
        Store (0x20, HID2)
        Store (0x2C, BADR)
        Return
      }
      If (LEqual(TPDT, SERIAL_IO_TPD_CUSTOM_DEVICE)) { // Custom TouchPad
        Store ("CUST0001", _HID)
        Store (TPDH, HID2)
        Store (TPDB, BADR)
        If (LEqual(TPDS, 0)) { Store ( 100000, SPED) }
        If (LEqual(TPDS, 1)) { Store ( 400000, SPED) }
        If (LEqual(TPDS, 2)) { Store (1000000, SPED) }
        Return
      }
    }

    Name (_HID, "XXXX0000")
    Name (_CID, "PNP0C50")
    Name (_S0W, 3)          // PTP will be in D3hot during CS, and wake capable
    Method(_DSM, 0x4, Serialized) {
      If (LEqual(Arg0,HIDG)) { Return(HIDD(Arg0,Arg1,Arg2,Arg3,HID2)) }
      If (LEqual(Arg0,TP7G)) { Return(TP7D(Arg0,Arg1,Arg2,Arg3,SBFB,SBFG)) }
      Return (Buffer(1){0})
    }

    Method (_STA, 0, NotSerialized) {
      If (LAnd(LNotEqual(TPDT,0),And( I2CN, SERIAL_IO_I2C_TOUCHPAD))) { Return (0x0F) }
      Return (0x00)
    }

    Method (_CRS, 0, NotSerialized) {
      If (LLess(OSYS, 2012)) { Return (SBFI) }
      If (LEqual(TPDM,0)) { Return (ConcatenateResTemplate(I2CM(I2CX,BADR,SPED), SBFG)) }
      Return (ConcatenateResTemplate(I2CM(I2CX,BADR,SPED), SBFI))
    }
  }  // Device (TPD0)

