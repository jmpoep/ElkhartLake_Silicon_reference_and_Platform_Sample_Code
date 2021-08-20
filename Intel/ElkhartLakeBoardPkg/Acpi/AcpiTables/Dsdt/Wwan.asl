/** @file
  Intel ACPI Sample Code for discrete connectivity modules (WWAN)

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

PowerResource(MRST, 5, 0)
{
  // Define the PowerResource for PCIe slot
  // PowerResource expects to have _STA, _ON and _OFF Method per ACPI Spec. Not having one of them will cause BSOD

  // Method: Dummy _STA() to comply with ACPI Spec
  Method(_STA)
  {
    ADBG("WWAN PR _STA")
    return(1)
  }

  // Method: Dummy _ON() to comply with ACPI Spec
  Method(_ON, 0)
  {
    ADBG("WWAN PR _ON")
  }

  // Method: Dummy _OFF() to comply with ACPI Spec
  Method(_OFF, 0)
  {
    ADBG("WWAN PR _OFF")
  }

  // Method: _RST()
  Method(_RST, 0, NotSerialized)
  {
    ADBG("WWAN PR _RST")

    // Drive RESET Pin low (M.2 slot reset pin)
    \_SB.SGOV(\WBBR, 0)
    // Wait 200 milliseconds
    Sleep(200)
    Notify (PCIE_ROOT_PORT.PXSX, 1)

    // De-Assert PERST
    \_SB.SGOV(\PRST, 0)

    // Drive RESET Pin high (M.2 slot reset pin)
    \_SB.SGOV(\WBBR, 1)
    // Wait 200 milliseconds
    Sleep(200)
    Notify (PCIE_ROOT_PORT.PXSX, 1)
  }
} // End MRST
