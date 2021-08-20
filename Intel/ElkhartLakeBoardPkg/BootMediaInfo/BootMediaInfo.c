/** @file
  Identify Boot Medium Information

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include "BootMediaInfo.h"

/**
  @param  ImageHandle  A handle for the image that is initializing this driver
  @param  SystemTable  A pointer to the EFI system table

  @retval EFI_SUCCESS   The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
BootMediaDriverEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                Status;
  BOOT_DEVICE_SETUP         BootDeviceInfo;
  UINTN                     VariableSize;

  VariableSize = 0;
  Status = gRT->GetVariable (
                  BOOT_DEVICE_INFO_VARIABLE_NAME,
                  &gBootDeviceInfoGuid,
                  NULL,
                  &VariableSize,
                  &BootDeviceInfo
                  );
  if (Status == RETURN_BUFFER_TOO_SMALL) {
    DEBUG ((DEBUG_INFO, "BootMediaInfo variable has already existed.\n"));
    return RETURN_SUCCESS;
  }

  if (BootMediaIsSpi ()) {
    BootDeviceInfo.Version = BOOT_DEVICE_INFO_REVISION;
    BootDeviceInfo.BootDeviceType = BootMediaSpi;
    BootDeviceInfo.Partition = 0;
  } else if (BootMediaIsUfs ()) {
    BootDeviceInfo.Version = BOOT_DEVICE_INFO_REVISION;
    BootDeviceInfo.BootDeviceType = BootMediaUfs;
    BootDeviceInfo.Partition = UFS_LUN_1;
  } else {
    DEBUG ((DEBUG_ERROR, "BootMediaLib Error: Invalid Boot Media\n"));
    return EFI_INVALID_PARAMETER;
  }

  VariableSize = sizeof (BootDeviceInfo);
  Status = gRT->SetVariable (
                  BOOT_DEVICE_INFO_VARIABLE_NAME,
                  &gBootDeviceInfoGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                  VariableSize,
                  &BootDeviceInfo
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DEBUG ((DEBUG_INFO, "BootMediaInfo set variable successfully.\n"));
  return EFI_SUCCESS;
}
