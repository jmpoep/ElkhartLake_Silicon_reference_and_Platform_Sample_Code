/**@file

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <PcieRegs.h>
#include <Register/CnviRegs.h>

Scope (\_SB.PC00) {
  Device(CNVW)
  {
    Name(_ADR, 0x00140003)

    //
    // Define a Memory Region that will allow access to the CNVi WiFi PCI Configuration Space
    //
    OperationRegion(CWAR, PCI_Config, 0x00, 0x100)
    Field(CWAR, WordAcc, NoLock, Preserve) {
      VDID, 32, // 0x00, VID DID
          ,  1,
      WMSE,  1, // MSE
      WBME,  1, // BME
      Offset(R_PCI_BAR0_OFFSET),
      WBR0, 64, // BAR0
      Offset(R_CNVI_CFG_WIFI_GIO_DEV_CAP),
          , 28,
      WFLR,  1, // Function Level Reset Capable
      Offset(R_CNVI_CFG_WIFI_GIO_DEV_CTRL),
          , 15,
      WIFR,  1, // Init Function Level Reset
      Offset(R_CNVI_CFG_WIFI_PMCSR),
      WPMS, 32,
    }
    Method(_S0W, 0x0, NotSerialized)
    {
      Return (0x3)
    }
    Method(_PRW, 0)
    {
      Return (GPRW(0x6D, 4)) // can wakeup from S4 state
    }

    Method(_DSW, 3) {}

    // Define Platform-level device reset power resource
    PowerResource(WRST, 5, 0)
    {
      // Define the PowerResource for CNVi WiFi
      // PowerResource expects to have _STA, _ON and _OFF Method per ACPI Spec. Not having one of them will cause BSOD

      // Method: Dummy _STA() to comply with ACPI Spec
      Method(_STA)
      {
        Return (0x01)
      }

      // Method: Dummy _ON() to comply with ACPI Spec
      Method(_ON, 0)
      {
      }

      // Method: Dummy _OFF() to comply with ACPI Spec
      Method(_OFF, 0)
      {
      }

      Method(_RST, 0, NotSerialized)
      {
        If(LEqual (WFLR, 1))
        {
          Store (0, WBR0)
          Store (0, WPMS)
          Store (0, WBME)
          Store (0, WMSE)
          Store (1, WIFR)
        }
      }
    } // End WRST

    Name(_PRR, Package(){WRST})
  }

  //
  // CNVi is present
  //
  Method(CNIP)
  {
    If (LNotEqual (\_SB.PC00.CNVW.VDID, 0xFFFFFFFF)){
      Return (0x01)
    } Else {
      Return (0x00)
    }
  }

  //
  // Set BT_EN
  //
  Method(SBTE, 0x1, Serialized)
  {
    //
    // Arg0 - Value to BT_EN
    //
    If (LEqual (PCHS, PCHL)) { // PCH-LP
      Store (GPIO_VER3_VGPIO0, Local0)
    }
    \_SB.SGOV (Local0, Arg0)
  }

  //
  // Get BT_EN value
  //
  Method(GBTE, 0)
  {
    If (LEqual (PCHS, PCHL)) { // PCH-LP
      Store (GPIO_VER3_VGPIO0, Local0)
    }
    Return (\_SB.GGOV (Local0))
  }

  //
  // Update BT Audio Offload setting
  //
  Method (AOLX, 0, Serialized)
  {
    // BT Audio Offload data structure
    Name (AODS, Package () {
      0,    // Revision
      0x12, // DomainType, 0x12:Bluetooth Core
      0     // Audio Offload selection, 0: Disabled, 1:Enabled
      })

    If (LEqual (CBTA, 1)) {
      Store(1, Index (AODS, 2))
    }
    Return (AODS)
  }
}

//
// AOLD (Audio Offload)
//   Arguments:
//     None
//   Return Value:
//     Revision
//     DomainType
//     Audio Offload selection, default value is Disabled
//
If (AND (\_SB.PC00.CNIP (), LEqual (CBTC, 1))) {
  If (LEqual (PCHS, PCH_LP)) {
    Scope(\_SB.PC00.XHCI.RHUB.HS10)
    {
      Method(AOLD)
      {
        Return (AOLX ())
      }
    } // Scope(\_SB.PC00.XHCI.RHUB.HS10)
  } ElseIf (LEqual (PCHS, PCH_H)) {
    Scope(\_SB.PC00.XHCI.RHUB.HS14)
    {
      Method(AOLD)
      {
        Return (AOLX ())
      }
    } // Scope(\_SB.PC00.XHCI.RHUB.HS14)
  } ElseIf (LEqual (PCHS, PCH_N)) {
    Scope(\_SB.PC00.XHCI.RHUB.HS08)
    {
      Method(AOLD)
      {
        Return (AOLX ())
      }
    } // Scope(\_SB.PC00.XHCI.RHUB.HS08)
  } // If (LEqual(PCHS, PCHL))
} // If (AND (\_SB.PC00.CNIP (), LEqual (CBTC, 1)))


