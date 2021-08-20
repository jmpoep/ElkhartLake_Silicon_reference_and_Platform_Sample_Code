/** @file
  This file is SampleCode of the library for Intel PCH PEI Debug Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2020 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#include <Library/PeiPchPolicyUpdate.h>
#include <Library/SiPolicyLib.h>
#include <PiPei.h>
#include <SetupVariable.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PchInfoLib.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspmUpd.h>
#endif

/**
  Update Smbus Debug Pre Mem Policy.

  @param[in] SiPreMemPolicy       Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm              Pointer to FspsUpm structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateSmbusDebugPreMemPolicy (
  IN SI_PREMEM_POLICY_PPI      *SiPreMemPolicy,
  IN VOID                      *FspmUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  PCH_SMBUS_PREMEM_CONFIG         *SmbusPreMemConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gSmbusPreMemConfigGuid, (VOID *) &SmbusPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  SmbusPreMemConfig = NULL;
#endif

  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SmbusSpdWriteDisable, SmbusPreMemConfig->SpdWriteDisable, PchSetup->SmbusSpdWriteDisable);
}

/**
  This function performs PCH PEI Debug Policy initialization.

  @retval EFI_SUCCESS        The PPI is installed and initialized.
  @retval EFI ERRORS         The PPI is not successfully installed.
**/
EFI_STATUS
EFIAPI
UpdatePeiPchPolicyDebugPreMem (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  UINTN                           VariableSize;
  PCH_SETUP                       PchSetup;
  VOID                            *FspmUpd;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicy;

  DEBUG ((DEBUG_INFO, "Update PeiPchPolicyDebug Pre-Mem Start\n"));

  FspmUpd = NULL;
  SiPreMemPolicy = NULL;

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = (FSPM_UPD *) PcdGet32 (PcdFspmUpdDataAddress);
  ASSERT (FspmUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }
#endif

  //
  // Retrieve Setup variable
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid, // GUID
             0,                                // INSTANCE
             NULL,                             // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices       // PPI
             );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &PchSetup
                               );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  UpdateSmbusDebugPreMemPolicy (SiPreMemPolicy, FspmUpd, &PchSetup);

  return EFI_SUCCESS;
}
