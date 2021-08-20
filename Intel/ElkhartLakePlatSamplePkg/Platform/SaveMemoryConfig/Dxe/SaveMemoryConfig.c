/** @file
  This is the driver that locates the MemoryConfigurationData HOB, if it
  exists, and saves the data to NVRAM.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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

#include "SaveMemoryConfig.h"

GLOBAL_REMOVE_IF_UNREFERENCED CHAR16    mMemoryConfigVariable[] = L"MemoryConfig";

/**
  This is the standard EFI driver point that detects whether there is a
  MemoryConfigurationData HOB and, if so, saves its data to NVRAM.

  @param[in] ImageHandle    Handle for the image of this driver
  @param[in] SystemTable    Pointer to the EFI System Table

  @retval    EFI_UNSUPPORTED
**/
EFI_STATUS
EFIAPI
SaveMemoryConfigEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                          Status;
  VOID                                *HobList;
  EFI_HOB_GUID_TYPE                   *GuidHob;
  VOID                                *HobData;
  VOID                                *VariableData;
  UINTN                               DataSize;
  UINTN                               BufferSize;
  EDKII_VARIABLE_LOCK_PROTOCOL        *VariableLock;

  DataSize     = 0;
  VariableData = NULL;
  GuidHob      = NULL;
  HobList      = NULL;
  HobData      = NULL;

  //
  // Get the HOB list.  If it is not present, then ASSERT.
  //
  HobList = GetHobList ();
  ASSERT (HobList != NULL);

  //
  // Search for the Memory Configuration GUID HOB.  If it is not present, then
  // there's nothing we can do. It may not exist on the update path.
  //
  GuidHob = GetNextGuidHob (&gSiMemoryS3DataGuid, HobList);
  if (GuidHob != NULL) {
    HobData  = GET_GUID_HOB_DATA (GuidHob);
    DataSize = GET_GUID_HOB_DATA_SIZE (GuidHob);
    if (DataSize > 0) {
      //
      // Use the HOB to save Memory Configuration Data
      //
      BufferSize = DataSize;
      VariableData = AllocatePool (BufferSize);
      if (VariableData == NULL) {
        return EFI_UNSUPPORTED;
      }
      Status = gRT->GetVariable (
                      mMemoryConfigVariable,
                      &gMemoryConfigVariableGuid,
                      NULL,
                      &BufferSize,
                      VariableData
                      );

      if (Status == EFI_BUFFER_TOO_SMALL) {
        FreePool (VariableData);
        VariableData = AllocatePool (BufferSize);
        if (VariableData == NULL) {
          return EFI_UNSUPPORTED;
        }

        Status = gRT->GetVariable (
                        mMemoryConfigVariable,
                        &gMemoryConfigVariableGuid,
                        NULL,
                        &BufferSize,
                        VariableData
                        );
      }

      if ((EFI_ERROR (Status)) || (BufferSize != DataSize) || (0 != CompareMem (HobData, VariableData, DataSize))) {
        Status = gRT->SetVariable (
                        mMemoryConfigVariable,
                        &gMemoryConfigVariableGuid,
                        (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS),
                        DataSize,
                        HobData
                        );
        ASSERT_EFI_ERROR (Status);

        DEBUG ((DEBUG_INFO, "Restored Size is 0x%x\n", DataSize));
      }

      //
      // Mark MemoryConfig to read-only if the Variable Lock protocol exists
      //
      Status = gBS->LocateProtocol (&gEdkiiVariableLockProtocolGuid, NULL, (VOID **)&VariableLock);
      if (!EFI_ERROR (Status)) {
        Status = VariableLock->RequestToLock (VariableLock, L"MemoryConfig", &gMemoryConfigVariableGuid);
        ASSERT_EFI_ERROR (Status);
      }

      //
      // Set the DISB bit
      // after S3 Data is saved to NVRAM.
      //
      PmcSetDramInitScratchpad ();

      FreePool (VariableData);
    } else {
      DEBUG ((DEBUG_INFO, "Memory save size is %d\n", DataSize));
    }
  } else {
    DEBUG ((DEBUG_ERROR, "Memory S3 Data HOB was not found\n"));
  }

  //
  // This driver does not produce any protocol services, so always unload it.
  //
  return EFI_UNSUPPORTED;
}
