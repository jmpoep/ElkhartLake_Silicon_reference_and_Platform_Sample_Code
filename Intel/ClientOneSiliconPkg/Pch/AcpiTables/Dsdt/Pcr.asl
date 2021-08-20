/**@file
  Intel ACPI Reference Code for PCR

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

Scope(\)
{
  //
  // PCR Register Access Methods
  //
  // PCR Dword Read
  // arg0: PID
  // arg1: Offset
  //
  Method (PCRR, 2, Serialized) {
    Add (ShiftLeft (arg0, 16), arg1, Local0)
    Add (SBRG, Local0, Local0)
    OperationRegion (PCR0, SystemMemory, Local0, 0x4)
    Field(PCR0,DWordAcc,Lock,Preserve) {
      Offset(0x00),
      DAT0, 32
    } // End Field PCR0
    Return (DAT0)
  } // End Method PCRR

  //
  // PCR Dword Write
  // arg0: PID
  // arg1: Offset
  // arg2: write data
  //
  Method (PCRW, 3, Serialized) {
    Add (ShiftLeft (arg0, 16), arg1, Local0)
    Add (SBRG, Local0, Local0)
    OperationRegion (PCR0, SystemMemory, Local0, 0x4)
    Field(PCR0,DWordAcc,Lock,Preserve) {
      Offset(0x00),
      DAT0, 32
    } // End Field PCR0
    Store (arg2, DAT0)
  } // End Method PCRW

  //
  // PCR Dword Or
  // arg0: PID
  // arg1: Offset
  // arg2: Or data
  //
  Method (PCRO, 3, Serialized) {
    Store(PCRR(arg0,arg1),Local0)    // Store PCR Read data in Local0
    Store(Or(Local0,arg2),Local1)    // Or data
    PCRW(arg0,arg1,Local1)           // Write data back
  }

  //
  // PCR Dword And
  // arg0: PID
  // arg1: Offset
  // arg2: And data
  //
  Method (PCRA, 3, Serialized) {
    Store(PCRR(arg0,arg1),Local0)    // Store PCR Read data in Local0
    Store(And(Local0,arg2),Local1)   // And data
    PCRW(arg0,arg1,Local1)           // Write data back
  }

  //
  // PCR Dword AndThenOr
  // arg0: PID
  // arg1: Offset
  // arg2: And data
  // arg3: Or data
  //
  Method (PCAO, 4, Serialized) {
    Store(PCRR(arg0,arg1),Local0)           // Store PCR Read data in Local0
    Store(Or(And(Local0,arg2),arg3),Local1) // AndThenOr
    PCRW(arg0,arg1,Local1)                  // Write data back
  }
}
