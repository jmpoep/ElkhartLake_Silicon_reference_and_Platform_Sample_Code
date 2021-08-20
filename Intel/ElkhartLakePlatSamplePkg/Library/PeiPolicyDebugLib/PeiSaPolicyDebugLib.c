/** @file
  This file is SampleCode of the library for Intel SA PEI Debug Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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

#include "PeiPolicyDebug.h"
#include <Library/PeiSaPolicyLib.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Guid/AcpiVariable.h>
#include <Guid/MemoryTypeInformation.h>
#include <Library/HobLib.h>
#include <Platform.h>
#include <Library/PchInfoLib.h>

/**
  This function performs SA PEI Debug PreMem Policy initialization.

  @retval EFI_SUCCESS             The PPI is installed and initialized.
  @retval EFI ERRORS              The PPI is not successfully installed.
**/
EFI_STATUS
EFIAPI
UpdatePeiSaPolicyDebugPreMem (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  SA_SETUP                        SaSetup;
  UINTN                           VarSize;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                            *FspmUpd;
#else
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig;
  SA_MISC_PEI_PREMEM_CONFIG       *MiscPeiPreMemConfig;
#endif

  DEBUG ((DEBUG_INFO, "Update PeiSaPolicyDebug Pre-Mem Start\n"));

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = NULL;
#else
  SiPreMemPolicyPpi   = NULL;
  GtPreMemConfig      = NULL;
  MiscPeiPreMemConfig = NULL;
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = (FSPM_UPD *) PcdGet32 (PcdFspmUpdDataAddress);
  ASSERT (FspmUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // Locate system configuration variable
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid, // GUID
             0,                                // INSTANCE
             NULL,                             // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices       // PPI
             );
  ASSERT_EFI_ERROR ( Status);

  //
  // Get Setup SA variables
  //
  VarSize = sizeof (SA_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"SaSetup",
                               &gSaSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &SaSetup
                               );

  if (!EFI_ERROR (Status)) {
    //
    // Initialize the Graphics configuration
    //
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PanelPowerEnable, GtPreMemConfig->PanelPowerEnable, SaSetup.PanelPowerEnable);

    //
    // Initialize Misc SA Configuration
    //
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.LockPTMregs,  MiscPeiPreMemConfig->LockPTMregs,  SaSetup.LockPTMregs);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.BdatEnable,   MiscPeiPreMemConfig->BdatEnable,   SaSetup.BdatEnable);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.BdatTestType,   MiscPeiPreMemConfig->BdatTestType,   SaSetup.BdatTestType);
  }

  return Status;
}

