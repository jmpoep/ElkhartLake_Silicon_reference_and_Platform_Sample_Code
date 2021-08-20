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


Device(WPCN)
{
  Name(_HID,EISAID("PNP0A05"))

  Name(_UID,3)

  // Status Method for the National SIO.

  Method(_STA,0,Serialized)
  {
    // Only report resources to the OS if the SIO Device is
    // present on the Docking Board.

    If(W381)
    {
      Return(0x000F)
    }

    Return(0x0000)
  }

  // Define the SIO Index/Data Registers as an ACPI Operating
  // Region.  These registers will be used communicate to the SIO.

  OperationRegion(WPCN, SystemIO, 0x02E, 0x02)
  Field(WPCN, ByteAcc, Lock, Preserve)
  {
    INDX, 8,
    DATA, 8
  }

  // Use ACPI Defined IndexField so consecutive Index/Data I/Os are
  // assured to be uninterrupted.

  IndexField(INDX, DATA, ByteAcc, Lock, Preserve)
  {
    Offset(0x07), // Logical Device Number.
    WR07, 8,
    Offset(0x20), // SIO Configuration and ID.
    WR20, 8,
    WR21, 8,
    WR22, 8,
    WR23, 8,
    WR24, 8,
    WR25, 8,
    WR26, 8,
    WR27, 8,
    WR28, 8,
    WR29, 8,
    WR2A, 8,
    Offset(0x30), // Logical Device Activate.
    WR30, 8,
    Offset(0x60), // I/O Space Configuration.
    WR60, 8,
    WR61, 8,
    WR62, 8,
    WR63, 8,
    Offset(0x70), // Interrupt Configuration.
    WR70, 8,
    WR71, 8,
    Offset(0x74), // DMA Configuration.
    WR74, 8,
    WR75, 8,
    Offset(0xF0), // Special Logical Device Configuration.
    WRF0, 8,
    WRF1, 8
  }

    Include ("Wpcn381UCom.asl")
    Include ("Wpcn381ULpt.asl")
}
