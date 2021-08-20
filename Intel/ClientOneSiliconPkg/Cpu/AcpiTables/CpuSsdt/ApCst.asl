/** @file
  Intel Processor Power Management CST ACPI Code.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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

DefinitionBlock (
  "APCST.aml",
  "SSDT",
  2,
  "PmRef",
  "ApCst",
  0x3000
  )
{
External(\_SB.PR01, DeviceObj)
External(\_SB.PR02, DeviceObj)
External(\_SB.PR03, DeviceObj)
External(\_SB.PR04, DeviceObj)
External(\_SB.PR05, DeviceObj)
External(\_SB.PR06, DeviceObj)
External(\_SB.PR07, DeviceObj)
External(\_SB.PR08, DeviceObj)
External(\_SB.PR09, DeviceObj)
External(\_SB.PR10, DeviceObj)
External(\_SB.PR11, DeviceObj)
External(\_SB.PR12, DeviceObj)
External(\_SB.PR13, DeviceObj)
External(\_SB.PR14, DeviceObj)
External(\_SB.PR15, DeviceObj)
External(\_SB.PR00._CST)

  Scope(\_SB.PR01)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR02)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR03)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR04)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR05)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR06)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR07)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR08)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR09)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR10)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR11)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR12)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR13)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR14)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

  Scope(\_SB.PR15)
  {
    Method(_CST,0)
    {
      //
      // Return P0's _CST object.
      //
      Return(\_SB.PR00._CST)
    }
  }

}  // End of Definition Block
