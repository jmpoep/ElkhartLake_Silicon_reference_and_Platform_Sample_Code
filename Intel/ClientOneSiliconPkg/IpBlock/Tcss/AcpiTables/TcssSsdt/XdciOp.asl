/** @file
  This file contains the TCSS XDCI ASL Operation Region code.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
    OperationRegion (XDCS, PCI_Config, 0x0, 0x100)
    Field (XDCS, DWordAcc, NoLock, Preserve)
    {
      Offset(0x0),
      DVID, 16,
      Offset(0x10),
      XDCB, 64
    }
    //
    // Byte access for PMCS field to avoid race condition on device D-state
    //
    Field (XDCS, ByteAcc, NoLock, Preserve)
    {
      Offset(R_XDCI_CFG_PMCSR),                 // 0x84, PM_CS - Power Management Control/Status
      D0I3, 2,                                  // PM_CS[1:0] PowerState
    }

    Method(XDBA, 0)
    {
      Return(And(^XDCB, 0xFFFFFFFFFFFFFF00))
    }

    OperationRegion(XDMM, SystemMemory, XDBA(), 0x110000)
    Field(XDMM, WordAcc, NoLock, Preserve)
    {
      Offset(R_XDCI_MEM_GCTL),                  // 0xC110
      GCTL, 32,                                 // Power Down Scale Value [31:19]
      Offset(R_XDCI_MEM_APBFC_U3PMU_CFG2),      // 0x10F810
          ,  8,
      U2CP,  2,                                 // USB2 core power state
      U3CP,  2,                                 // USB3 core power state
      Offset(R_XDCI_MEM_APBFC_U3PMU_CFG4),      // 0x10F818
      PUPS,  2,                                 // PMU power state
          ,  1,
      PURC,  1,                                 // Reset PMU core
          , 12,
      Offset(R_XDCI_MEM_APBFC_U3PMU_CFG5),      // 0x10F81C
          ,  3,
      UXPE,  2,                                 // U2 PME EN / U3 PME EN
          , 11,
    }


