/**@file
 I2S Audio Codec ACPI

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

// HD Audio I2S codecs
#define HDAC_I2S_DISABLED 0
#define HDAC_I2S_ALC274   1
#define HDAC_I2S_ALC5660  2

///
/// I2S HW Audio Codec ACPI definition body
///
//-----------------------------------
//  HD Audio I2S Codec device
//  Disabled               (I2SC = 0)
//  Realtek ALC274         (I2SC = 1)
//  Realtek ALC5660I       (I2SC = 2)
//-----------------------------------
Device (HDAC)
{
  Name (_HID, "INT00000")
  Name (_CID, "INT00000")
  Name (_DDN, "Intel(R) Smart Sound Technology Audio Codec")
  Name (_UID, 1)
  Name (CADR, 0) // Codec I2C address
  Name (CDIS, 0) // Codec Disabled state

  Method(_INI) {
    If (LEqual(I2SC, HDAC_I2S_ALC274)) { // ALC274
      Store ("INT34C2", _HID)
      Store ("INT34C2", _CID)
      Store (0x1C, CADR)
      Return
    }
    If (LEqual(I2SC, HDAC_I2S_ALC5660)) { // ALC5660
      Store ("INTC1027", _HID)
      Store ("INTC1027", _CID)
      Store (0x1C, CADR)
      Return
    }
  }

  Method (_CRS, 0, NotSerialized) {

    // IICB: Method generates 'I2cSerialBus' descriptor buffer
    // CADR: Device variable with codec address (set in _INI based on codec model)
    // I2SB: NVS variable with I2C controller connection
    // INTB: Method generates 'Interrupt' descriptor buffer
    // I2SI: NVS variable with codec jack detection pin
    If (LEqual(I2SC, HDAC_I2S_ALC5660)) {
      Return (ConcatenateResTemplate(IICB(CADR, I2SB), INTB(I2SI, INT_EDGE_TRIG, INT_ACTIVE_HIGH)))
    } Else {
      Return (ConcatenateResTemplate(IICB(CADR, I2SB), INTB(I2SI, INT_LEVEL_TRIG, INT_ACTIVE_LOW)))
    }
  }

  Method (_STA, 0, NotSerialized) {
    If (LAnd(LNotEqual(I2SC, HDAC_I2S_DISABLED), LNotEqual(CDIS, 1))) {
      Return (0xF)  // I2S Codec Enabled
    }

    If (LEqual (CDIS, 1)) {
      Return (0xD)  // Disabled from _DIS 1101b - Present/Disabled (via Device Manager)
    }

    Return (0x0)  // I2S Codec Dialed (via BIOS Policy/Setup)
  }

  Method (_SRS, 0x1, Serialized) {
    Store (0, CDIS) // Clear Disabled bit
  }

  Method (_DIS, 0x0, NotSerialized) {
    Store (1, CDIS) // Set Disabled bit
  }
}  // Device (HDAC)
