/** @file
 Integrated Thunderbolt MailBox ACPI methods

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#include <TbtMailBoxCmdDefinition.h>

Field(DPME, DWordAcc, NoLock, Preserve)
{
  Offset(R_SA_HOST_DMA_ITBT_NVM_FW_REVISION), // 0xC8
  ,     31,
  INFR,  1, // ITBT NVM FW Ready
  Offset(FixedPcdGet8 (PcdITbtToPcieRegister)), // 0xEC
  TB2P, 32, // TBT to PCIe
  P2TB, 32  // PCIe to TBT
}

//
// ITBT MailBox Command Method
// Arg0 : MailBox Cmd ID
// Arg1 : Timeout Value (unit is millisecond)
//
Method(ITMB, 2, Serialized) {
  Or (Arg0, PCIE2TBT_VLD_B, Local0)
  Store (Local0, P2TB)
  WFCC (Arg1, 1)
  Store (0, P2TB)
  WFCC (Arg1, 0)
}

//
// Wait For Command Completed
// Arg0    TimeOut value (unit is millisecond)
// Arg1    Wait condition: 0:wait for Bit to Clear, 1:wait for Bit to Set
//
Method(WFCC, 2, Serialized) {
  Store (Arg0, Local0) // Store the Timeout value
  While (LGreater (Local0, 0)) {
    If (Arg1) {
      //
      // Wait for Bit to Set
      //
      If (And (TB2P, TBT2PCIE_DON_R)) {
        Break
      }
    } Else {
      //
      // Wait for Bit to Clear
      //
      If (Xor (TB2P, TBT2PCIE_DON_R)) {
        Break
      }
    }
    Decrement (Local0)
    Sleep (100)
  }
}

//
// TCSS ITBT CONNECT_TOPOLOGY MailBox Command Method
//
Method(CNTP, 0, Serialized) {
  Store (0, Local0)
  //
  // Save original state if Force Power is not enabled then enable it
  //
  Store (DFPE, Local1)
  If (LEqual(DFPE, 0)) {
    Store (0x22, DMAD)
    Store (1, DFPE)
  }
  //
  // Poll the ITBT NVM FW Ready bit with timeout(default is 500ms) before send the TBT MailBox command
  //
  While (LAnd(LEqual (INFR, 0), LLess(Local0, ITFP))) {
    Sleep (1)
    Increment (Local0)
  }
  If (LNotEqual(Local0, ITFP)) {
    ITMB (PCIE2TBT_CONNECT_TOPOLOGY_COMMAND, ITCT)
  }
  //
  // Restore Force Power if original state is not enabled
  //
  If (LEqual(Local1, 0)) {
    Store (Local1, DFPE)
  }
}