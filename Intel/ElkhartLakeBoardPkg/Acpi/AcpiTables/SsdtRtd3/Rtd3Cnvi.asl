/** @file
  Intel ACPI sample code for Connectivity devices

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

@par Specification
**/

#include <Library/PchInfoLib.h>

External(\_SB.PC00.XHCI.RHUB.HS08, DeviceObj)
External(\_SB.PC00.XHCI.RHUB.HS10, DeviceObj)
External(\_SB.PC00.XHCI.RHUB.HS14, DeviceObj)
External(\_SB.PC00.CNIP, MethodObj)
External(\_SB.PC00.SBTE, MethodObj)
External(\_SB.PC00.GBTE, MethodObj)
External(PCHS)
External(CNVI)
External(CBTC)

//
// Report BT power resource if CNVi is present and BT interface is USB.
//
If (AND (\_SB.PC00.CNIP (), LEqual (CBTC, 1))) {
  If (LEqual (PCHS, PCH_LP)) {
    Scope(\_SB.PC00.XHCI.RHUB.HS10)
    {
      //
      // Power resource object for CNVi BT
      //
      PowerResource(BTPR, 0, 0)
      {
        Method(_STA, 0)
        {
          If(LEqual (\_SB.PC00.GBTE (), 1)) {
            Return (0x01)
          } Else {
            Return (0x00)
          }
        }
        Method(_ON, 0, Serialized)
        {
          \_SB.PC00.SBTE (0x01) // Turn on BT
        }
        Method(_OFF, 0, Serialized)
        {
          \_SB.PC00.SBTE (0x00) // Turn off BT
        }
      }
    } // Scope(\_SB.PC00.XHCI.RHUB.HS10)
  } ElseIf (LEqual (PCHS, PCH_H)) {
    Scope(\_SB.PC00.XHCI.RHUB.HS14)
    {
      //
      // Power resource object for CNVi BT
      //
      PowerResource(BTPR, 0, 0)
      {
        Method(_STA, 0)
        {
          If(LEqual (\_SB.PC00.GBTE (), 1)) {
            Return (0x01)
          } Else {
            Return (0x00)
          }
        }
        Method(_ON, 0, Serialized)
        {
          \_SB.PC00.SBTE (0x01) // Turn on BT
        }
        Method(_OFF, 0, Serialized)
        {
          \_SB.PC00.SBTE (0x00) // Turn off BT
        }
      }
    } // Scope(\_SB.PC00.XHCI.RHUB.HS14)
  } ElseIf (LEqual (PCHS, PCH_N)) {
    Scope(\_SB.PC00.XHCI.RHUB.HS08)
    {
      //
      // Power resource object for CNVi BT
      //
      PowerResource(BTPR, 0, 0)
      {
        Method(_STA, 0)
        {
          If(LEqual (\_SB.PC00.GBTE (), 1)) {
            Return (0x01)
          } Else {
            Return (0x00)
          }
        }
        Method(_ON, 0, Serialized)
        {
          \_SB.PC00.SBTE (0x01) // Turn on BT
        }
        Method(_OFF, 0, Serialized)
        {
          \_SB.PC00.SBTE (0x00) // Turn off BT
        }
      }
    } // Scope(\_SB.PC00.XHCI.RHUB.HS08)
  } // If (LEqual(PCHS, PCHL))
} // If (AND (\_SB.PC00.CNIP (), LEqual (CBTC, 1)))

