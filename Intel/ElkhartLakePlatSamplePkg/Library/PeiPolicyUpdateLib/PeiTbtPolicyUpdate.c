/** @file
Do Platform Stage TBT initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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

#include <Library/PeiTbtPolicyUpdate.h>
#include <Library/HobLib.h>
#include <Platform.h>
#include <Pi/PiPeiCis.h>
#include <Core/Pei/PeiMain.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SiPolicyLib.h>
#include <Library/PeiITbtPolicyLib.h>
#include <Ppi/PeiDTbtPolicy.h>
#include <Library/PeiDTbtPolicyLib.h>
#include <Library/RngLib.h>
#if FixedPcdGetBool(PcdITbtEnable) == 1
#include <PeiITbtConfig.h>
#include <TcssDataHob.h>
#endif
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspsUpd.h>
#endif

/**
  UpdatePeiTbtPolicy performs TBT PEI Policy initialization

  @retval EFI_SUCCESS              The policy is installed and initialized.
**/
EFI_STATUS
EFIAPI
UpdatePeiTbtPolicy (
  VOID
  )
{
  EFI_STATUS                       Status;
  UINTN                            VarSize;
  SETUP_DATA                       SystemConfiguration;
  UINT8                            Index;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI  *VariableServices;
#if FixedPcdGetBool(PcdITbtEnable) == 1
  TCSS_DATA_HOB                    *TcssHob;
  PEI_ITBT_CONFIG                  *PeiITbtConfig;
#endif
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                             *FspsUpd;
#else
  SI_POLICY_PPI                    *SiPolicy;
#endif
  PEI_DTBT_POLICY                  *PeiDTbtConfig;

  DEBUG ((DEBUG_INFO, "Update PeiTbtPolicyUpdate Pos-Mem Start\n"));

#if FixedPcdGetBool(PcdITbtEnable) == 1
  TcssHob = NULL;
  PeiITbtConfig = NULL;
#endif
#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = NULL;
#else
  SiPolicy     = NULL;
  Status       = EFI_NOT_FOUND;
#endif
  PeiDTbtConfig = NULL;

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = (FSPS_UPD *) PcdGet32 (PcdFspsUpdDataAddress);
  ASSERT (FspsUpd != NULL);
#else
  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicy);
  ASSERT_EFI_ERROR(Status);
#if FixedPcdGetBool(PcdITbtEnable) == 1
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPeiITbtConfigGuid, (VOID *) &PeiITbtConfig);
  ASSERT_EFI_ERROR (Status);
#endif
#endif

  Status = PeiServicesLocatePpi (
             &gPeiDTbtPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &PeiDTbtConfig
             );

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );

  if (Status != EFI_SUCCESS) {
    return Status;
  }

  VarSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &SystemConfiguration
                               );

  if (Status != EFI_SUCCESS) {
    return Status;
  }
  //
  // Update DTBT Policy
  //
  if (PeiDTbtConfig != NULL) {
    for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
      PeiDTbtConfig->DTbtControllerConfig[Index].DTbtControllerEn  = SystemConfiguration.DTbtController[Index];
      if ((SystemConfiguration.TbtSetupDTbtPegTypeSupport) && (SystemConfiguration.DTbtControllerType[Index] == TYPE_PEG))
      {
        PeiDTbtConfig->DTbtControllerConfig[Index].Type            = (UINT8) TYPE_PEG;
        PeiDTbtConfig->DTbtControllerConfig[Index].PcieRpNumber    = 1; // PEG RP 1 (Function no. 0)
      }
    }
    PeiDTbtConfig->DTbtGenericConfig.TbtBootOn        = SystemConfiguration.TbtBootOn;
    PeiDTbtConfig->DTbtGenericConfig.TbtUsbOn         = SystemConfiguration.TbtUsbOn;
    PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwr    = SystemConfiguration.Gpio3ForcePwr;
    PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwrDly = SystemConfiguration.Gpio3ForcePwrDly;
  }

#if FixedPcdGetBool(PcdITbtEnable) == 1
  //
  // Get status of each iTBT PCIe RP is enabled or not from Tcss Hob.
  //
  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);

  //
  // Update ITBT Policy
  //
  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ITbtPcieRootPortEn[Index], PeiITbtConfig->ITbtRootPortConfig[Index].ITbtPcieRootPortEn, SystemConfiguration.ITbtRootPort[Index]);

    //
    // Set/Clear ITBT Policy for ITbtPcieRootPortEn depending upon each iTBT PCIe RP is enabled or not.
    //
    if (TcssHob != NULL) {
      AND_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ITbtPcieRootPortEn[Index], PeiITbtConfig->ITbtRootPortConfig[Index].ITbtPcieRootPortEn, TcssHob->TcssData.ItbtPcieRpEn[Index]);
    }
  }

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ITbtForcePowerOnTimeoutInMs, PeiITbtConfig->ITbtGenericConfig.ITbtForcePowerOnTimeoutInMs, SystemConfiguration.ITbtForcePowerOnTimeoutInMs);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ITbtConnectTopologyTimeoutInMs, PeiITbtConfig->ITbtGenericConfig.ITbtConnectTopologyTimeoutInMs, SystemConfiguration.ITbtConnectTopologyTimeoutInMs);
#endif

  DTbtPrintPeiPolicyConfig();

  return EFI_SUCCESS;
}
