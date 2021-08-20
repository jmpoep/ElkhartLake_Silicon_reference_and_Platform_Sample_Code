/** @file
  GPIO Expander APIs.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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
#include <Library/GpioExpanderLib.h>

/**
  Set the Output value for the given Expander Gpio pin.

  This function is to Set the Output value for the GPIO
  Pin within the giving Expander.

  @param[in]  Expander    Expander Value with in the Contoller
  @param[in]  Pin         Pin with in the Expnader Value
  @param[in]  Value       none

**/
VOID
GpioExpSetOutput (
  IN UINT8 Expander,
  IN UINT8 Pin,
  IN UINT8 Value
  )
{

}
/**
  Set the Direction value for the given Expander Gpio pin.

  This function is to Set the direction value for the GPIO
  Pin within the giving Expander.

  @param[in]  Expander    Expander Value with in the Contoller
  @param[in]  Pin         Pin with in the Expnader Value
  @param[in]  Value       none
**/
VOID
GpioExpSetDirection (
  IN UINT8 Expander,
  IN UINT8 Pin,
  IN UINT8 Value
  )
{

}
/**
  Set the input value for the given Expander Gpio pin.

  This function is to get the input value for the GPIO
  Pin within the giving Expander.

  @param[in]  Expander    Expander Value with in the Contoller
  @param[in]  Pin         Pin with in the Expnader Value
  @param[in]  Value       none

**/
VOID
GpioExpSetPolarity (
  IN UINT8 Expander,
  IN UINT8 Pin,
  IN UINT8 Value
  )
{

}
/**
  Get the input value for the given Expander Gpio pin.

  This function is to get the input value for the GPIO
  Pin within the giving Expander.

  @param[in]  Expander    Expander Value with in the Contoller
  @param[in]  Pin         Pin with in the Expnader Value

  @retval     UINT8       Final Value returned from the register
**/
UINT8
GpioExpGetInput (
  IN UINT8 Expander,
  IN UINT8 Pin
  )
{
  return (0xFF);
}

/**
  Configures all registers of a single IO Expander in one go.

  @param[in]  Expander    Expander number (0/1)
  @param[in]  Direction   Bit-encoded direction values. BIT0 is for pin0, etc. 0=output, 1=input
  @param[in]  Polarity    Bit-encoded input inversion values. BIT0 is for pin0, etc. 0=normal, 1=inversion
  @param[in]  Output      Bit-encoded output state, ignores polarity, only applicable if direction=INPUT. BIT0 is for pin0, etc. 0=low, 1=high

**/
VOID
GpioExpBulkConfig (
  IN UINT8  Expander,
  IN UINT32 Direction,
  IN UINT32 Polarity,
  IN UINT32 Output
  )
{

}

