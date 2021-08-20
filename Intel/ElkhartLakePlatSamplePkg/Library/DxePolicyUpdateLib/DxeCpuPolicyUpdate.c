/** @file
  This file is the library for CPU DXE Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

#include <Library/DxeCpuPolicyUpdateLib.h>

/**
  This function prints the CPU DXE phase policy.

  @param[in] DxeCpuPolicy - CPU DXE Policy protocol
**/
VOID
CpuDxePrintPolicyProtocol (
  IN  DXE_CPU_POLICY_PROTOCOL  *DxeCpuPolicy
  )
{
  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "\n------------------------ CPU Policy (DXE) print BEGIN -----------------\n"));
  DEBUG ((DEBUG_INFO, "Revision : %x\n", DxeCpuPolicy->Revision));
  ASSERT (DxeCpuPolicy->Revision == DXE_CPU_POLICY_PROTOCOL_REVISION);
  DEBUG ((DEBUG_INFO, "\n------------------------ CPU_DXE_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, "EnableDts : %x\n", DxeCpuPolicy->EnableDts));
  DEBUG ((DEBUG_INFO, "\n------------------------ CPU Policy (DXE) print END -----------------\n"));
  DEBUG_CODE_END ();
}

/**
  Get data for CPU policy from setup options.

  @param[in] DxeCpuPolicy              The pointer to get CPU Policy protocol instance

  @retval EFI_SUCCESS                  Operation success.

**/
EFI_STATUS
EFIAPI
UpdateDxeSiCpuPolicy (
  IN OUT  DXE_CPU_POLICY_PROTOCOL  *DxeCpuPolicy
  )
{
  UINTN                     VariableSize;
  CPU_SETUP                 CpuSetup;
  EFI_STATUS                Status;

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &CpuSetup
                  );
  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR(Status)) {
    DxeCpuPolicy->EnableDts = CpuSetup.EnableDigitalThermalSensor;
  }

  return EFI_SUCCESS;
}

/**
  CpuInstallPolicyProtocol installs CPU Policy.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] ImageHandle                Image handle of this driver.
  @param[in] DxeCpuPolicy               The pointer to CPU Policy Protocol instance

  @retval EFI_SUCCESS                   The policy is installed.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
CpuInstallPolicyProtocol (
  IN  EFI_HANDLE                  ImageHandle,
  IN  DXE_CPU_POLICY_PROTOCOL     *DxeCpuPolicy
  )
{
  EFI_STATUS            Status;

  ///
  /// Print CPU DXE Policy
  ///
  CpuDxePrintPolicyProtocol(DxeCpuPolicy);

  ///
  /// Install the DXE_CPU_POLICY_PROTOCOL interface
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gDxeCpuPolicyProtocolGuid,
                  DxeCpuPolicy,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

