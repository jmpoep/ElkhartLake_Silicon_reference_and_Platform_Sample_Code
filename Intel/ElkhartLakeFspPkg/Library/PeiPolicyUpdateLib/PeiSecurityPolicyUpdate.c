/** @file
  This file is SampleCode of the library for Intel Security PEI Policy initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2018 Intel Corporation.

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

#include <PiPei.h>
#include <Ppi/SiPolicy.h>
#include <Library/FspCommonLib.h>
#include <FspsUpd.h>
#include <Library/DebugLib.h>
#include <Library/CpuPlatformLib.h>
#include <CpuRegs.h>
#include <Library/ConfigBlockLib.h>


/**
  This function performs Security PEI Policy initialization.

  @param[in] SiPolicyPpi           The SI Policy PPI instance
  @param[in] FspsUpd               The pointer of FspsUpd

  @retval EFI_SUCCESS              The PPI is installed and initialized.
  @retval EFI ERRORS               The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES     Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
FspUpdatePeiSecurityPolicy (
  IN OUT SI_POLICY_PPI        *SiPolicyPpi,
  IN FSPS_UPD                 *FspsUpd
  )
{
  EFI_STATUS                       Status;
  CPU_SGX_CONFIG                   *CpuSgxConfig;
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuSgxConfigGuid, (VOID *) &CpuSgxConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Production RC Policies
  ///
  CpuSgxConfig->SgxEpoch0 = FspsUpd->FspsConfig.SgxEpoch0;
  CpuSgxConfig->SgxEpoch1 = FspsUpd->FspsConfig.SgxEpoch1;
  CpuSgxConfig->SgxSinitNvsData = FspsUpd->FspsConfig.SgxSinitNvsData;
  CpuSgxConfig->SgxLCP             = FspsUpd->FspsConfig.SgxLCP;
  CpuSgxConfig->SgxLEPubKeyHash0   = FspsUpd->FspsConfig.SgxLEPubKeyHash0;
  CpuSgxConfig->SgxLEPubKeyHash1   = FspsUpd->FspsConfig.SgxLEPubKeyHash1;
  CpuSgxConfig->SgxLEPubKeyHash2   = FspsUpd->FspsConfig.SgxLEPubKeyHash2;
  CpuSgxConfig->SgxLEPubKeyHash3   = FspsUpd->FspsConfig.SgxLEPubKeyHash3;

  ///
  /// Test RC Policies
  ///
  CpuSgxConfig->SgxSinitDataFromTpm = FspsUpd->FspsConfig.SgxSinitDataFromTpm;

  ///
  ///

  return EFI_SUCCESS;
}

