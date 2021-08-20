/** @file
  This file is SampleCode of the library for Intel AMT PEI Platform Policy Update.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include <Ppi/SiPolicy.h>
#include <FspsUpd.h>
#include <Library/ConfigBlockLib.h>

/**
  This function performs Active Management PEI Policy update.

  @param[in, out] SiPolicyPpi   The Si Policy PPI instance
  @param[in]      FspsUpd       The pointer of FspsUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiAmtPolicy (
  IN OUT SI_POLICY_PPI    *SiPolicyPpi,
  IN     FSPS_UPD         *FspsUpd
  )
{
  EFI_STATUS              Status;
  AMT_PEI_CONFIG          *AmtPeiConfig;

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP UpdatePeiAmtPolicy\n"));

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gAmtPeiConfigGuid, (VOID *) &AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);

  AmtPeiConfig->AmtEnabled        = FspsUpd->FspsConfig.AmtEnabled;
  AmtPeiConfig->WatchDogEnabled   = FspsUpd->FspsConfig.WatchDogEnabled;
  AmtPeiConfig->FwProgress        = FspsUpd->FspsConfig.FwProgress;
  AmtPeiConfig->WatchDogTimerOs   = FspsUpd->FspsConfig.WatchDogTimerOs;
  AmtPeiConfig->WatchDogTimerBios = FspsUpd->FspsConfig.WatchDogTimerBios;
  AmtPeiConfig->ManageabilityMode = FspsUpd->FspsConfig.ManageabilityMode;
  AmtPeiConfig->AmtSolEnabled     = FspsUpd->FspsConfig.AmtSolEnabled;
  AmtPeiConfig->RemoteAssistance  = FspsUpd->FspsConfig.RemoteAssistance;
  AmtPeiConfig->AmtKvmEnabled     = FspsUpd->FspsConfig.AmtKvmEnabled;
  AmtPeiConfig->ForcMebxSyncUp    = FspsUpd->FspsConfig.ForcMebxSyncUp;

  return EFI_SUCCESS;
}
