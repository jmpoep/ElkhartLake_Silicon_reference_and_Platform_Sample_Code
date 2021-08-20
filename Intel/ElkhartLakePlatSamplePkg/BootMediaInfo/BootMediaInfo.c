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

BOOLEAN         mFoundBootDevice  = FALSE;
BOOT_MEDIA_TYPE mBootMedia        = BootMediaMax;

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
  BOOT_MEDIA_HOB_DATA       *BootMediaHobData;
  EFI_HOB_GUID_TYPE         *GuidHobPtr;
  BOOT_DEVICE_SETUP         BootDeviceInfo;
  UINTN                     VariableSize;
  UINT32                    BootMediaInfoAttr;
  UINTN                     DataSize;
  VOID                      *HobData;
  VOID                      *VariableData;

  HobData = NULL;
  VariableData = NULL;
  GuidHobPtr  = GetFirstGuidHob (&gBootMediaHobGuid);
  if (GuidHobPtr == NULL) {
    DEBUG ((DEBUG_ERROR, "BootMediaLib Error: Boot Media HOB does not exist!\n"));
    ASSERT (GuidHobPtr != NULL);
    return EFI_SUCCESS;
  }

  BootMediaHobData = (BOOT_MEDIA_HOB_DATA *) GET_GUID_HOB_DATA (GuidHobPtr);
  HobData = GET_GUID_HOB_DATA (GuidHobPtr);
  DataSize = GET_GUID_HOB_DATA_SIZE (GuidHobPtr);

  Status = gBS->AllocatePool(EfiBootServicesData, sizeof(BOOT_DEVICE_SETUP), (VOID **)&BootDeviceInfo);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  switch (BootMediaHobData->BootMedia) {
    case BootMediaSpi:
      BootDeviceInfo.Version = BOOT_DEVICE_INFO_REVISION;
      BootDeviceInfo.BootDeviceType = BootMediaSpi;
      BootDeviceInfo.Partition = 0;
      break;
    case BootMediaUfs:
      BootDeviceInfo.Version = BOOT_DEVICE_INFO_REVISION;
      BootDeviceInfo.BootDeviceType = BootMediaUfs;
      BootDeviceInfo.Partition = UFS_LUN_1;
      break;
    case BootMediaMax:
    default:
      DEBUG ((DEBUG_ERROR, "BootMediaLib Error: Invalid Boot Media\n"));
      return EFI_INVALID_PARAMETER;
  }

  BootMediaInfoAttr = 0;
  VariableSize = sizeof (BOOT_DEVICE_SETUP);
  Status = gRT->GetVariable (
                  BOOT_DEVICE_INFO_VARIABLE_NAME,
                  &gBootDeviceInfoGuid,
                  &BootMediaInfoAttr,
                  &VariableSize,
                  &BootDeviceInfo
                  );
  if (Status == EFI_NOT_FOUND) {
    Status = gRT->SetVariable (
                    BOOT_DEVICE_INFO_VARIABLE_NAME,
                    &gBootDeviceInfoGuid,
                    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                    sizeof (BOOT_DEVICE_SETUP),
                    &BootDeviceInfo
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else {
    VariableData = (VOID *) &BootDeviceInfo;
    if ((EFI_ERROR (Status)) || (VariableSize != DataSize) || (0 != CompareMem (HobData, VariableData, DataSize))) {
      Status = gRT->SetVariable (
                      BOOT_DEVICE_INFO_VARIABLE_NAME,
                      &gBootDeviceInfoGuid,
                      BootMediaInfoAttr,
                      VariableSize,
                      &BootDeviceInfo
                      );
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
  }

  return EFI_SUCCESS;
}
