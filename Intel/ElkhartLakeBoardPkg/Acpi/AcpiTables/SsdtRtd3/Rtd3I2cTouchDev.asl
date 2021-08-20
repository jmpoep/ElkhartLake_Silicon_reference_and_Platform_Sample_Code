/** @file
  ACPI RTD3 I2C Touch Device SSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

  /// Include Rtd3I2cTouchDev.asl under Touch Device scope for RTD3 support \n
  /// Input parameters: \n
  ///- TD_T - Touch Device type
  ///- TD_P - Touch Device Power Package
  ///- TD_D - Touch Device power on delay
  ///- TD_C - Touch Device I2C controller power on timestamp

  ///@addtogroup i2c1_touchdev_scope

  /// PS0X Method
  Method(PS0X,0,Serialized)
  {

    If(LEqual(TD_C,Zero))               /// Check if I2C controller is powered on
    {
      Return()
    }

    ///
    /// Make sure "D0 delay" (TD_D) delay is elapsed before returning _PS0 \n
    /// Variables:
    ///- Local0: Elapse time since the _ON method \n
    ///- VRRD: VR Rampup Delay \n
    ///- TD_D: Time required for device to be ready after power on \n
    ///- Local1 = TD_D + VRRD: Need to incorporate VRRD since the _ON method no longer has VR Rampup Delay \n
    ///- So only need sleep for (Local1 - Local0), the amount of time remaining since the _ON method \n
    ///
    Divide(Subtract(Timer(), TD_C), 10000, , Local0) /// Store Elapsed time in ms, ignore remainder \n
    Add(TD_D, VRRD, Local1)             /// Incorporate VR Rampup Delay \n
    If(LLess(Local0, Local1))           /// Do not sleep if already past the delay requirement (TD_D + VRRD) for Touch Device \n
    {
      ///- Else, delay for power ramp
      Sleep(Subtract(Local1, Local0))   ///- Sleep (TD_D + VRRD - time elapsed)
    }

  ///@defgroup i2c1_touchdev_ps0    I2C1 Touch Device _PS0 Method
  }

  Method(PS3X,0,Serialized)
  {
  ///@defgroup i2c1_touchdev_ps3        I2C1 Touch Device _PS3 Method
  }

  Method(_PR0, Zero, NotSerialized, 0, PkgObj)    /// _PR0 Method
  {
    If(LEqual(_STA(),0xF))              /// Check if Touch Device is enabled
    {
      Return(TD_P)                      ///- Return Device Specific Power Package (TD_P) if enabled
    } Else {
      Return(Package() {})              ///- Return NULL Power Package if disabled
    }

  ///@defgroup i2c1_touchdev_pr0        I2C1 Touch Device _PR0 Method
  }

  Method(_PR3, Zero, NotSerialized, 0, PkgObj)    /// _PR3 Method
  {
    If(LEqual(_STA(),0xF))              /// Check if Touch Device is enabled
    {
      Return(TD_P)                      ///- Return Device Specific Power Package (TD_P) if enabled
    } Else {
      Return(Package() {})              ///- Return NULL Power Package if disabled
    }

  ///@defgroup i2c1_touchdev_pr3        I2C1 Touch Device _PR3 Method
  }
///@defgroup i2c1_touchdev_scope        I2C1 Touch Device Common Library
