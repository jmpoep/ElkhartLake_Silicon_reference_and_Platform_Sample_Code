/** @file
  SA PCIe Initialization Private Low Level functions for Skylake DT/HALO

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

@par Specification
**/

#include "SaPegLowLevel.h"
#include <Library/SaPlatformLib.h>
#include <Register/PchRegsHsio.h>
#include <Library/CpuMailboxLib.h>
#include <Register/SaRegsHostBridge.h>
/**
  Reads, modifies and writes to PCODE mail box as per the input.

  @param[in]  CrOffset                    - Config Register Offset
  @param[in]  Data32And                   - Data to Clear
  @param[in]  Data32Or                    - Data to Set
**/
EFI_STATUS
PcodeMailboxReadThenWrite(
  IN  UINT32           CrOffset,
  IN  UINT32           Data32And,
  IN  UINT32           Data32Or,
  IN  CONTROLLER_TYPE  ControllerType
  )
{
  EFI_STATUS  Status;
  UINT32      LibStatus;
  UINT32      Data32;
  UINT32      TargetBlock;

  TargetBlock = 0;
  //
  // Target IO block 0 for DMI or 1 for PCI (Bit 24 in Mailbox Command)
  //
  if (ControllerType == PEG_PORT) {
    TargetBlock = 0x1 << N_MAILBOX_TARGET_IO_BLOCK_OFFSET;
  } else {
    TargetBlock = 0x0 << N_MAILBOX_TARGET_IO_BLOCK_OFFSET;
  }
  MailboxRead (MAILBOX_TYPE_PCODE, (READ_PEG_CRIO_CR | TargetBlock | CrOffset),&Data32,&LibStatus);
  if(LibStatus != PCODE_MAILBOX_CC_SUCCESS){
    DEBUG ((DEBUG_INFO, "PEG_CRIO_CR() - MailboxRead Error = %r\n", LibStatus));
  }
  Data32 &= Data32And;
  Data32 |= Data32Or;
  Status = MailboxWrite (MAILBOX_TYPE_PCODE, (WRITE_PEG_CRIO_CR | TargetBlock | CrOffset),Data32,&LibStatus);
  if((Status != EFI_SUCCESS)||(LibStatus != PCODE_MAILBOX_CC_SUCCESS)){
    DEBUG ((DEBUG_INFO, "PEG_CRIO_CR() - MailboxWrite Error = %r\n", LibStatus));
  }
  return Status;
}
