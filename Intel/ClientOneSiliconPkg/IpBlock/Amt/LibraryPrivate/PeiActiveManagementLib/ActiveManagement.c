/** @file
  The PEI Library Implements ActiveManagement Support.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

#include <Ppi/SiPolicy.h>
#include <MeBiosPayloadHob.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <MebxDataHob.h>
#include <AmtConfig.h>

/**
  Install Mebx Data Hob.
**/
VOID
InstallMebxDataHob (
  VOID
  )
{
  MEBX_DATA_HOB             *MebxDataHob;
  AMT_PEI_CONFIG            *AmtPeiConfig;
  EFI_STATUS                Status;
  SI_POLICY_PPI             *SiPolicyPpi;

  DEBUG ((DEBUG_INFO, "Install MEBX Data Hob\n"));

  SiPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gAmtPeiConfigGuid, (VOID *) &AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);

  MebxDataHob = BuildGuidHob (&gAmtMebxDataGuid, sizeof (MEBX_DATA_HOB));
  ASSERT (MebxDataHob != NULL);
  if (MebxDataHob == NULL) {
    return;
  }
  MebxDataHob->PlatformMngSel                      = (UINT8) AmtPeiConfig->ManageabilityMode;
  MebxDataHob->AmtSol                              = (UINT8) AmtPeiConfig->AmtSolEnabled;
  MebxDataHob->RemoteAssistanceTriggerAvailablilty = (UINT8) AmtPeiConfig->RemoteAssistance;
  MebxDataHob->KvmEnable                           = (UINT8) AmtPeiConfig->AmtKvmEnabled;

  DEBUG ((DEBUG_INFO, "PlatformMngSel   = 0x%x\n", MebxDataHob->PlatformMngSel));
  DEBUG ((DEBUG_INFO, "AmtSol           = 0x%x\n", MebxDataHob->AmtSol));
  DEBUG ((DEBUG_INFO, "RemoteAssistance = 0x%x\n", MebxDataHob->RemoteAssistanceTriggerAvailablilty));
  DEBUG ((DEBUG_INFO, "KvmEnable        = 0x%x\n", MebxDataHob->KvmEnable));

  return;
}

/**
  This function performs basic initialization for AMT in PEI phase after DID.
**/
VOID
EFIAPI
AmtPostMemInit (
  VOID
  )
{
  ME_BIOS_PAYLOAD_HOB       *MbpHob;

  DEBUG ((DEBUG_INFO, "AmtPostMemInit() - Start\n"));

  MbpHob  = (ME_BIOS_PAYLOAD_HOB *) GetFirstGuidHob (&gMeBiosPayloadHobGuid);

  DEBUG ((DEBUG_INFO, "IntelMeFwImageType = %x\n", MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType));
  if ((MbpHob != NULL) && (MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType == IntelMeCorporateFw)) {
    InstallMebxDataHob ();
  }

  DEBUG ((DEBUG_INFO, "AmtPostMemInit() - End\n"));
}

