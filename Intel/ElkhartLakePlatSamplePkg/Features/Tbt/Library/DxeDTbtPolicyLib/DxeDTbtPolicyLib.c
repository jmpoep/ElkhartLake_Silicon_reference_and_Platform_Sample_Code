/** @file
  This file is DxeDTbtPolicyLib library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

@par Specification
**/
#include <DxeDTbtPolicyLibrary.h>
#include <Protocol/DxeDTbtPolicy.h>

/**
  Print DXE DTBT Policy
**/
VOID
DTbtPrintDxePolicyConfig (
  VOID
  )
{
  EFI_STATUS                       Status;
  UINT8                            Index;
  DXE_DTBT_POLICY_PROTOCOL         *DxeDTbtConfig;

  DEBUG ((DEBUG_INFO, "DTbtPrintDxePolicyConfig Start\n"));

  DxeDTbtConfig = NULL;
  Status = EFI_NOT_FOUND;
  Status = gBS->LocateProtocol (
                &gDxeDTbtPolicyProtocolGuid,
                NULL,
                (VOID **) &DxeDTbtConfig
                );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, " gDxeDTbtPolicyProtocolGuid Not installed!!!\n"));
    return;
  }
  //
  // Print DTBT Policy
  //
  DEBUG ((DEBUG_ERROR, " ========================= DXE DTBT POLICY ========================= \n"));
  if (DxeDTbtConfig != NULL) {
    for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
      DEBUG ((DEBUG_INFO, "DxeDTbtConfig->DTbtResourceConfig[%x].DTbtPcieExtraBusRsvd = %x\n", Index, DxeDTbtConfig->DTbtResourceConfig[Index].TbtPcieExtraBusRsvd));
      DEBUG ((DEBUG_INFO, "DxeDTbtConfig->DTbtResourceConfig[%x].DTbtPcieMemRsvd = %x\n", Index, DxeDTbtConfig->DTbtResourceConfig[Index].TbtPcieMemRsvd));
      DEBUG ((DEBUG_INFO, "DxeDTbtConfig->DTbtResourceConfig[%x].DTbtPcieMemAddrRngMax = %x\n", Index, DxeDTbtConfig->DTbtResourceConfig[Index].TbtPcieMemAddrRngMax));
      DEBUG ((DEBUG_INFO, "DxeDTbtConfig->DTbtResourceConfig[%x].DTbtPciePMemRsvd = %x\n", Index, DxeDTbtConfig->DTbtResourceConfig[Index].TbtPciePMemRsvd));
      DEBUG ((DEBUG_INFO, "DxeDTbtConfig->DTbtResourceConfig[%x].DTbtPciePMemAddrRngMax = %x\n", Index, DxeDTbtConfig->DTbtResourceConfig[Index].TbtPciePMemAddrRngMax));
    }
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->TbtCommonConfig.TbtAspm = %x\n", DxeDTbtConfig->TbtCommonConfig.TbtAspm));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->TbtCommonConfig.TbtL1SubStates = %x\n", DxeDTbtConfig->TbtCommonConfig.TbtL1SubStates));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->TbtCommonConfig.TbtHotNotify = %x\n", DxeDTbtConfig->TbtCommonConfig.TbtHotNotify));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->TbtCommonConfig.TbtHotSMI = %x\n", DxeDTbtConfig->TbtCommonConfig.TbtHotSMI));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->TbtCommonConfig.TbtLtr = %x\n", DxeDTbtConfig->TbtCommonConfig.TbtLtr));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->TbtCommonConfig.TbtPtm = %x\n", DxeDTbtConfig->TbtCommonConfig.TbtPtm));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->TbtCommonConfig.TbtSetClkReq = %x\n", DxeDTbtConfig->TbtCommonConfig.TbtSetClkReq));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->TbtCommonConfig.TbtVtdBaseSecurity = %x\n", DxeDTbtConfig->TbtCommonConfig.TbtVtdBaseSecurity));
    DEBUG((DEBUG_INFO, "DxeDTbtConfig->DTbtGenericConfig.TbtWakeupSupport = %x\n", DxeDTbtConfig->DTbtGenericConfig.TbtWakeupSupport));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->DTbtGenericConfig.SecurityMode = %x\n", DxeDTbtConfig->DTbtGenericConfig.SecurityMode));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->DTbtGenericConfig.Gpio5Filter = %x\n", DxeDTbtConfig->DTbtGenericConfig.Gpio5Filter));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->DTbtGenericConfig.TrA0OsupWa = %x\n", DxeDTbtConfig->DTbtGenericConfig.TrA0OsupWa));
    DEBUG ((DEBUG_INFO, "DxeDTbtConfig->DTbtGenericConfig.TbtAcDcSwitch = %x\n", DxeDTbtConfig->DTbtGenericConfig.TbtAcDcSwitch));
  }
  return;
}

/**
  DTbtInstallPolicyProtocol installs DTBT Policy.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] ImageHandle                Image handle of this driver.

  @retval EFI_SUCCESS                   The policy is installed.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
DTbtInstallPolicyProtocol (
  IN  EFI_HANDLE                  ImageHandle
  )
{
  EFI_STATUS                    Status;
  DXE_DTBT_POLICY_PROTOCOL      *DxeTbtPolicy;

  DEBUG ((DEBUG_INFO, "Install DXE DTBT Policy\n"));

  DxeTbtPolicy = NULL;
  //Alloc memory for DxeTbtPolicy
  DxeTbtPolicy = (DXE_DTBT_POLICY_PROTOCOL *) AllocateZeroPool (sizeof (DXE_DTBT_POLICY_PROTOCOL));
  if (DxeTbtPolicy == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gDxeDTbtPolicyProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  DxeTbtPolicy
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Install DXE DTBT Policy failed\n"));
  }
  return Status;
}
