/** @file
  This file provides services for Dci PreMem policy function

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
#include <Library/DebugLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <DciConfig.h>

/**
  Print PCH_DCI_PREMEM_CONFIG and serial out.

  @param[in] SiPreMemPolicyPpi            Pointer to a SI_PREMEM_POLICY_PPI

**/
VOID
DciPreMemPrintConfig (
  IN SI_PREMEM_POLICY_PPI     *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                Status;
  PCH_DCI_PREMEM_CONFIG     *DciPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gDciPreMemConfigGuid, (VOID *) &DciPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ DCI PreMem Config ------------------\n"));
  DEBUG ((DEBUG_INFO, "DciEn = %x\n", DciPreMemConfig->DciEn));
  DEBUG ((DEBUG_INFO, "DciDbcMode = %x\n", DciPreMemConfig->DciDbcMode));
  DEBUG ((DEBUG_INFO, "DciModphyPg = %x\n", DciPreMemConfig->DciModphyPg));
  DEBUG ((DEBUG_INFO, "DciUsb3TypecUfpDbg = %x\n", DciPreMemConfig->DciUsb3TypecUfpDbg));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
DciPreMemLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PCH_DCI_PREMEM_CONFIG  *DciPreMemConfig;
  DciPreMemConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "DciPreMemConfig->Header.GuidHob.Name = %g\n", &DciPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "DciPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", DciPreMemConfig->Header.GuidHob.Header.HobLength));

  /********************************
    DCI Configuration
  ********************************/
  DciPreMemConfig->DciDbcMode = DciDbcNoChange;
  DciPreMemConfig->DciUsb3TypecUfpDbg = Usb3TcDbgNoChange;
}

STATIC COMPONENT_BLOCK_ENTRY  mDciPreMemBlocks = {
  &gDciPreMemConfigGuid,
  sizeof (PCH_DCI_PREMEM_CONFIG),
  DCI_PREMEM_CONFIG_REVISION,
  DciPreMemLoadConfigDefault
};

/**
  Get Dci config block table size.

  @retval      Size of config block
**/
UINT16
DciPreMemGetConfigBlockTotalSize (
  VOID
  )
{
  return mDciPreMemBlocks.Size;
}

/**
  Add Dci ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
DciPreMemAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mDciPreMemBlocks, 1);
}
