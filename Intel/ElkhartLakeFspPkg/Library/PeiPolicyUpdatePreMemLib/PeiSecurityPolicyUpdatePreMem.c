/** @file
  This file is SampleCode of the library for Intel CPU PEI Policy initialization.

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

#include <Library/DebugLib.h>
#include <Ppi/SiPolicy.h>
#include <FspmUpd.h>
#include <Library/ConfigBlockLib.h>
#include <Library/CpuPlatformLib.h>

/**
  This function performs Security PEI Policy initialization in Pre-memory.

  @param[in] SiPreMemPolicyPpi     The SI Pre-Mem Policy PPI instance
  @param[in] FspmUpd               The pointer of FspmUpd

  @retval EFI_SUCCESS              The PPI is installed and initialized.
  @retval EFI ERRORS               The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
FspUpdatePeiSecurityPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi,
  IN      FSPM_UPD            *FspmUpd
  )
{
  EFI_STATUS                    Status;
  CPU_SECURITY_PREMEM_CONFIG    *CpuSecurityPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  ///
  ///Test RC Policies
  ///
  CpuSecurityPreMemConfig->SkipStopPbet = FspmUpd->FspmConfig.SkipStopPbet;
  ///
  ///Production Policies
  ///
  CpuSecurityPreMemConfig->BiosGuard                 = FspmUpd->FspmConfig.BiosGuard;
  CpuSecurityPreMemConfig->BiosGuardToolsInterface   = FspmUpd->FspmConfig.BiosGuardToolsInterface;
  CpuSecurityPreMemConfig->EnableSgx                 = FspmUpd->FspmConfig.EnableSgx;
#if FixedPcdGetBool(PcdTxtEnable) == 1
  CpuSecurityPreMemConfig->Txt                       = FspmUpd->FspmConfig.Txt;
#endif
  CpuSecurityPreMemConfig->PrmrrSize                 = FspmUpd->FspmConfig.PrmrrSize;

  CpuSecurityPreMemConfig->BiosSize     = FspmUpd->FspmConfig.BiosSize;
#if FixedPcdGetBool(PcdTxtEnable) == 1
  CpuSecurityPreMemConfig->TxtAcheckRequest = FspmUpd->FspmConfig.TxtAcheckRequest;

  CpuTxtPreMemConfig->SinitMemorySize   = FspmUpd->FspmConfig.SinitMemorySize;
  CpuTxtPreMemConfig->TxtHeapMemorySize = FspmUpd->FspmConfig.TxtHeapMemorySize;
  CpuTxtPreMemConfig->TxtDprMemoryBase  = FspmUpd->FspmConfig.TxtDprMemoryBase;
  CpuTxtPreMemConfig->TxtDprMemorySize  = FspmUpd->FspmConfig.TxtDprMemorySize;
  CpuTxtPreMemConfig->BiosAcmBase       = FspmUpd->FspmConfig.BiosAcmBase;
  CpuTxtPreMemConfig->BiosAcmSize       = FspmUpd->FspmConfig.BiosAcmSize;
  CpuTxtPreMemConfig->TgaSize           = FspmUpd->FspmConfig.TgaSize;
  CpuTxtPreMemConfig->TxtLcpPdBase      = FspmUpd->FspmConfig.TxtLcpPdBase;
  CpuTxtPreMemConfig->TxtLcpPdSize      = FspmUpd->FspmConfig.TxtLcpPdSize;
  CpuTxtPreMemConfig->ApStartupBase     = FspmUpd->FspmConfig.ApStartupBase;
  CpuTxtPreMemConfig->IsTPMPresence     = FspmUpd->FspmConfig.IsTPMPresence;
#endif

  return EFI_SUCCESS;
}
