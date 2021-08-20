/** @file
  This file is SampleCode of the library for Intel AMT PEI Platform Policy Update.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2020 Intel Corporation.

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

#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <SetupVariable.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/SiPolicyLib.h>
#include <IndustryStandardAsf.h>
#include <IntelAsfExtensions.h>
#include <MebxDataHob.h>
#include <Library/ConfigBlockLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspsUpd.h>
#endif
//
// The ASF message types which will be push to PET Hob.
//
GLOBAL_REMOVE_IF_UNREFERENCED ASF_FRAMEWORK_MESSAGE_TYPE mAmtForcePushPetPolicy[] = {
  AsfMessageChassisIntrusion,
  AsfMessageUserAuthenticationInvalid,
  AsfMessageHddAuthenticationInvalid,
  AsfMessageTermination
};

/**
  Install the Active Management push PET policy
**/
VOID
InstallAmtForcePushPetPolicy (
  VOID
  )
{
  VOID        *Hob;

  //
  // Build HOB for information needed to push to PET
  //
  Hob = BuildGuidDataHob (
          &gAmtForcePushPetPolicyGuid,
          &mAmtForcePushPetPolicy,
          sizeof (mAmtForcePushPetPolicy)
          );

  //
  // Cannot Build HOB
  //
  ASSERT (Hob != NULL);

  return;
}

/**
  Install the Active Management Policy Ppi Library

  @retval EFI_SUCCESS           Initialization complete.
  @retval EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR      Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
UpdatePeiAmtPolicy (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  UINTN                           VariableSize;
  ME_SETUP                        MeSetup;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                            *FspsUpd;
#else
  SI_POLICY_PPI                   *SiPolicyPpi;
  AMT_PEI_CONFIG                  *AmtPeiConfig;
#endif
  VOID                            *MebxSavedData;

  DEBUG ((DEBUG_INFO, "Update PeiAmtPolicyUpdate Pos-Mem Start\n"));

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = NULL;
  FspsUpd = (FSPS_UPD *) PcdGet32 (PcdFspsUpdDataAddress);
  ASSERT (FspsUpd != NULL);
#else
  SiPolicyPpi  = NULL;
  AmtPeiConfig = NULL;
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gAmtPeiConfigGuid, (VOID *) &AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // Locate Variable Ppi
  //
  Status = PeiServicesLocatePpi (&gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, (VOID **) &VariableServices);

  //
  // Make sure we have a PPI, if not, just return.
  //
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }
  //
  // Get Setup Variable
  //
  VariableSize = sizeof (ME_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"MeSetup",
                               &gMeSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &MeSetup
                               );

  if (!EFI_ERROR (Status)) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.AmtEnabled,        AmtPeiConfig->AmtEnabled,        MeSetup.Amt);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.WatchDogEnabled,   AmtPeiConfig->WatchDogEnabled,   MeSetup.WatchDogEnabled);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.WatchDogTimerBios, AmtPeiConfig->WatchDogTimerBios, MeSetup.WatchDogTimerBios);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.WatchDogTimerOs,   AmtPeiConfig->WatchDogTimerOs,   MeSetup.WatchDogTimerOs);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FwProgress,        AmtPeiConfig->FwProgress,        MeSetup.FwProgress);
  }

  VariableSize  = 0;
  MebxSavedData = NULL;
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ForcMebxSyncUp, AmtPeiConfig->ForcMebxSyncUp, 1);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"MeBiosExtensionSetup",
                               &gMeBiosExtensionSetupGuid,
                               NULL,
                               &VariableSize,
                               MebxSavedData
                               );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    MebxSavedData = AllocateZeroPool (VariableSize);
    ASSERT (MebxSavedData != NULL);
    if (MebxSavedData == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    DEBUG ((DEBUG_INFO, "VariableSize is 0x%x\n", VariableSize));
    Status = VariableServices->GetVariable (
                                 VariableServices,
                                 L"MeBiosExtensionSetup",
                                 &gMeBiosExtensionSetupGuid,
                                 NULL,
                                 &VariableSize,
                                 MebxSavedData
                                 );
    if (!EFI_ERROR (Status)) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ManageabilityMode, AmtPeiConfig->ManageabilityMode, ((MEBX_DATA_HOB *)MebxSavedData)->PlatformMngSel);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.AmtSolEnabled, AmtPeiConfig->AmtSolEnabled, ((MEBX_DATA_HOB *)MebxSavedData)->AmtSol);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.RemoteAssistance, AmtPeiConfig->RemoteAssistance, ((MEBX_DATA_HOB *)MebxSavedData)->RemoteAssistanceTriggerAvailablilty);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.AmtKvmEnabled, AmtPeiConfig->AmtKvmEnabled, ((MEBX_DATA_HOB *)MebxSavedData)->KvmEnable);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ForcMebxSyncUp, AmtPeiConfig->ForcMebxSyncUp, 0);
    } else {
      DEBUG ((DEBUG_WARN, "Failed to retrieve Variable:\"MeBiosExtensionSetup\", Status = %r\n", Status));
    }
  }

#if FixedPcdGet8(PcdFspModeSelection) == 1
  if ((((FSPS_UPD *) FspsUpd)->FspsConfig.AmtEnabled == 0) || (((FSPS_UPD *) FspsUpd)->FspsConfig.ManageabilityMode == 0)) {
#else
  if ((AmtPeiConfig->AmtEnabled == 0) || (AmtPeiConfig->ManageabilityMode == 0)) {
#endif
    //
    // Disable below settings since they have dependency on AMT.
    //
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FwProgress,        AmtPeiConfig->FwProgress, 0);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.WatchDogEnabled,   AmtPeiConfig->WatchDogEnabled, 0);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.WatchDogTimerBios, AmtPeiConfig->WatchDogTimerBios, 0);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.WatchDogTimerOs,   AmtPeiConfig->WatchDogTimerOs, 0);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.AmtSolEnabled,     AmtPeiConfig->AmtSolEnabled, 0);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.AmtKvmEnabled,     AmtPeiConfig->AmtKvmEnabled, 0);
  }

  InstallAmtForcePushPetPolicy ();

  return Status;
}

