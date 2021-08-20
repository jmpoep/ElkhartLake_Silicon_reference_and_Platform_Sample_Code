/** @file
  This file is DxeITbtPolicy library.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include <DxeITbtPolicyLibrary.h>
#include <ITbtInfoHob.h>
#include <Protocol/ITbtPolicy.h>
#include <DxeITbtConfig.h>
#include <Guid/HobList.h>
#include <Library/HobLib.h>

/**
  Print DXE ITBT Policy

  @param[in]  ITbtPolicy                The pointer to get iTBT DXE Protocol instance
**/
VOID
ITbtPrintDxePolicyConfig (
  IN  ITBT_POLICY_PROTOCOL              *ITbtPolicy
  )
{
  return;
}

EFI_STATUS
EFIAPI
LoadITbtDxeDefault (
  IN VOID                               *ConfigBlockPointer
  )
{
  return EFI_SUCCESS;
}


/**
  LoadITbtDxeConfigBlockDefault - Initialize default settings for each ITBT Config block

  @param[in] ConfigBlockPointer         The buffer pointer that will be initialized as specific config block
  @param[in] BlockId                    Request to initialize defaults of specified config block by given Block ID

  @retval EFI_SUCCESS                   The given buffer has contained the defaults of requested config block
  @retval EFI_NOT_FOUND                 Block ID is not defined so no default Config block will be initialized
**/
EFI_STATUS
EFIAPI
LoadITbtDxeConfigBlockDefault (
  IN  VOID                              *ConfigBlockPointer,
  IN  EFI_GUID                          BlockGuid
  )
{
  return EFI_SUCCESS;
}

/**
  CreateITbtDxeConfigBlocks generates the config blocksg of iTBT DXE Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[out] ITbtPolicy                The pointer to get iTBT DXE Protocol instance

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
CreateITbtDxeConfigBlocks (
  IN OUT  ITBT_POLICY_PROTOCOL          **ITbtPolicy
  )
{
  return EFI_SUCCESS;
}

/**
  ITbtInstallPolicyProtocol installs iTBT Policy.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] ImageHandle                Image handle of this driver.
  @param[in] ITbtPolicy                 The pointer to TBT Policy Protocol instance

  @retval EFI_SUCCESS                   The policy is installed.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
ITbtInstallPolicyProtocol (
  IN  EFI_HANDLE                        ImageHandle,
  IN  ITBT_POLICY_PROTOCOL              *ITbtPolicy
  )
{
  return EFI_SUCCESS;
}
