/** @file
  This file is SampleCode of the library for Intel Me PEI
  Platform Policy Update.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#include <Library/FspCommonLib.h>
#include <FspmUpd.h>
#include <Library/ConfigBlockLib.h>

/**
  This function performs Me PEI Policy update in pre-memory.

  @param[in out] SiPreMemPolicy    SI_PREMEM_POLICY_PPI
  @param[in]     FspmUpd           The pointer of FspmUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiMePolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI   *SiPreMemPolicy,
  IN     FSPM_UPD               *FspmUpd
  )
{
  EFI_STATUS                      Status;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FspUpdatePeiMePolicyPreMem\n"));

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  MePeiPreMemConfig->HeciTimeouts               = FspmUpd->FspmConfig.HeciTimeouts;

  // <Test policies>
  MePeiPreMemConfig->DidInitStat                = FspmUpd->FspmConfig.DidInitStat;
  MePeiPreMemConfig->DisableCpuReplacedPolling  = FspmUpd->FspmConfig.DisableCpuReplacedPolling;
  MePeiPreMemConfig->SendDidMsg                 = FspmUpd->FspmConfig.SendDidMsg;
  MePeiPreMemConfig->DisableMessageCheck        = FspmUpd->FspmConfig.DisableMessageCheck;
  MePeiPreMemConfig->SkipMbpHob                 = FspmUpd->FspmConfig.SkipMbpHob;

  MePeiPreMemConfig->HeciCommunication2         = FspmUpd->FspmConfig.HeciCommunication2;
  MePeiPreMemConfig->KtDeviceEnable             = FspmUpd->FspmConfig.KtDeviceEnable;

  MePeiPreMemConfig->Heci1BarAddress            = FspmUpd->FspmConfig.Heci1BarAddress;
  MePeiPreMemConfig->Heci2BarAddress            = FspmUpd->FspmConfig.Heci2BarAddress;
  MePeiPreMemConfig->Heci3BarAddress            = FspmUpd->FspmConfig.Heci3BarAddress;

  return EFI_SUCCESS;
}

