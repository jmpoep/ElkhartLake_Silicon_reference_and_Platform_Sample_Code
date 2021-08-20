/** @file
  ACPI functions that drive pin states

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

#define PIN_GPIO_PAD_INDEX  0
#define PIN_GPIO_POLARITY_INDEX  1

//
// This library provides functions that configure pin states.
//
// GPIO package definition:
// Package() {
//   GpioPad : IntObj
//   GpioActiveStatePolarity : IntObj
//   }
//

//
// GPIO library imports
//

Scope(\) {

  //
  // Note this is not a real power resource we simply use this to declare new named scope
  //
  PowerResource(PIN, 0, 0) {
    //
    // Check pin status function
    // @param[in]  Arg0  Pin descriptor package
    //
    // @return GPIO pin status relative to GpioActiveStatePolarity value
    //
    Method(STA, 1, Serialized) {
      If(LEqual(\_SB.GGOV(DeRefOf(Index(Arg0, PIN_GPIO_PAD_INDEX))), DeRefOf(Index(Arg0, PIN_GPIO_POLARITY_INDEX)))) {
        Return(1)
      } Else {
        Return(0)
      }
    }

    //
    // Drive pin to active state function.
    // @param[in]  Arg0  Pin descriptor package
    //
    Method(ON, 1, Serialized) {
      ADBG(Concatenate("PINH GPIO=", ToHexString(DeRefOf(Index(Arg0, PIN_GPIO_PAD_INDEX)))))
      \_SB.SGOV(DeRefOf(Index(Arg0, PIN_GPIO_PAD_INDEX)), DeRefOf(Index(Arg0, PIN_GPIO_POLARITY_INDEX)))
    }

    //
    // Drive pin to inactive state.
    // @param[in]  Arg0  Pin descriptor package
    //
    Method(OFF, 1, Serialized) {
      ADBG(Concatenate("PINL GPIO=", ToHexString(DeRefOf(Index(Arg0, PIN_GPIO_PAD_INDEX)))))
      \_SB.SGOV(DeRefOf(Index(Arg0, PIN_GPIO_PAD_INDEX)), Not(DeRefOf(Index(Arg0, PIN_GPIO_POLARITY_INDEX))))
    }

    // Dummy standard methods for OSPM.
    // PowerResource is required to implement those.
    Method(_STA) {Return(0)}
    Method(_ON) {}
    Method(_OFF) {}
  }
}

