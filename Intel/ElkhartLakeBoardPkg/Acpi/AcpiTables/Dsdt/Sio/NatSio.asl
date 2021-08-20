/** @file
  ACPI DSDT table

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


Device(N393)
{
  Name(_HID,EISAID("PNP0A05"))

  Name(_UID,1)

  // Status Method for the National SIO.

  Method(_STA,0,Serialized)
  {
    // Only report resources to the OS if the SIO Device is
    // present on the Docking Board.

    If(NATP)
    {
      Return(0x000F)
    }

    Return(0x0000)
  }

  // Define the SIO Index/Data Registers as an ACPI Operating
  // Region.  These registers will be used communicate to the SIO.

  OperationRegion(N393, SystemIO, 0x02E, 0x02)
  Field(N393, ByteAcc, Lock, Preserve)
  {
    INDX, 8,
    DATA, 8
  }

  // Use ACPI Defined IndexField so consecutive Index/Data I/Os are
  // assured to be uninterrupted.

  IndexField(INDX, DATA, ByteAcc, Lock, Preserve)
  {
    Offset(0x07), // Logical Device Number.
    R07H, 8,
    Offset(0x20), // SIO Configuration and ID.
    R20H, 8,
    R21H, 8,
    R22H, 8,
    R23H, 8,
    R24H, 8,
    R25H, 8,
    R26H, 8,
    R27H, 8,
    R28H, 8,
    R29H, 8,
    R2AH, 8,
    Offset(0x30), // Logical Device Activate.
    R30H, 8,
    Offset(0x60), // I/O Space Configuration.
    R60H, 8,
    R61H, 8,
    Offset(0x70), // Interrupt Configuration.
    R70H, 8,
    R71H, 8,
    Offset(0x74), // DMA Configuration.
    R74H, 8,
    R75H, 8,
    Offset(0xF0), // Special Logical Device Configuration.
    RF0H, 8,
    RF1H, 8
  }

  Include ("NatCom.asl")
  Include ("NatLpt.asl")
}
