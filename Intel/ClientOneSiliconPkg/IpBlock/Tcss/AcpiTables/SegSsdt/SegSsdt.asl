/** @file
  This file contains the Segment SSDT Table ASL code.
  It defines a SSDT table for extra Segment

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
  "SegSsdt.aml",
  "SSDT",
  2,
  "INTEL ",
  "SegSsdt",
  0x1000
  )
{
External(\PICM, IntObj)

Scope(\_SB) {

  Name(PD00, Package(){
// SEG1. PCIe Root Port D7F0
    Package(){0x0007FFFF, 0, 0, 11 },
    Package(){0x0007FFFF, 1, 0, 10 },
    Package(){0x0007FFFF, 2, 0, 11 },
    Package(){0x0007FFFF, 3, 0, 11 },
// SEG1. PCIe Root Port D7F1
  })
  Name(AR00, Package(){
// SEG1. PCIe Root Port D7F0
    Package(){0x0007FFFF, 0, 0, 16 },
    Package(){0x0007FFFF, 1, 0, 17 },
    Package(){0x0007FFFF, 2, 0, 18 },
    Package(){0x0007FFFF, 3, 0, 19 },
// SEG1. PCIe Root Port D7F1
  })

  Device(PC01) { // PCI Bridge "Host Bridge"
    Name(_HID, EISAID("PNP0A08")) // Indicates PCI Express/PCI-X Mode2 host hierarchy
    Name(_CID, EISAID("PNP0A03")) // To support legacy OS that doesn't understand the new HID
    Name(_SEG, 1)
    Name(_ADR, 0x00000000)
    Method(_BBN, 0){ return(0) } // Bus number, optional for the Root PCI Bus
    Name(_UID, 0x0001)  // Unique Bus ID, optional
    Method(_PRT,0) {
      If(PICM) {Return(AR00)} // APIC mode
      Return (PD00) // PIC Mode
    } // end _PRT

    Include("ExtraHostBus.asl")
  } // end PC01 Bridge "Host Bridge"
}
}
