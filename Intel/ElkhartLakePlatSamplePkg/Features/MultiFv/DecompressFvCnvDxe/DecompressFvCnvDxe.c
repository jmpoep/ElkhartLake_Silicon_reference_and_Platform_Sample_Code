/** @file
  Driver for Decompressing FVCNV when WiFi Http Boot is enabled.

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

#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <SetupVariable.h>
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
#include <Guid/SysFwUpdateProgress.h>
#include <Library/HobLib.h>
#endif

#define EFI_NETWORK_ALL    1
#define EFI_NETWORK_WIFI   2


/**
  Entry point for Decompress FvCnv Driver.

  @param[in] ImageHandle   - Pointer to the loaded image protocol for this driver
  @param[in] SystemTable   - Pointer to the EFI System Table

  @retval EFI_SUCCESS      - Decompress FvCnv successfully.
**/
EFI_STATUS
EFIAPI
DecompressFvCnvEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  UINTN                   VarSize;
  UINT32                  VarAttr;
  EFI_STATUS              Status;
  EFI_HANDLE              FwVolHandle;
  SETUP_DATA              SetupData;
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
  EFI_HOB_GUID_TYPE       *GuidHob;

  GuidHob = NULL;
#endif
  VarSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                    L"Setup",
                    &gSetupVariableGuid,
                    &VarAttr,
                    &VarSize,
                    &SetupData
                    );
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_ERROR, "[FVCNV] Fail to get Setup variable\n"));
    return Status;
  }
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
  GuidHob = GetFirstGuidHob (&gSysFwUpdateProgressGuid);
  if ((GuidHob != NULL) && \
      (((SYSTEM_FIRMWARE_UPDATE_PROGRESS *) GET_GUID_HOB_DATA (GuidHob))->Component == UpdatingBios)) {
    return EFI_SUCCESS;
  }
#endif
  if ((SetupData.EfiNetworkSupport == EFI_NETWORK_ALL) ||
      (SetupData.EfiNetworkSupport == EFI_NETWORK_WIFI) ||
      (SetupData.PrebootBleEnable == 1)) {
    DEBUG((DEBUG_INFO, "[FVCNV] Preboot WiFi/BLE is enabled, Decompressing FVCNV.\n"));
    gDS->ProcessFirmwareVolume (
      (VOID *) (UINTN)PcdGet32(PcdFlashFvCnvBase),
      PcdGet32(PcdFlashFvCnvSize),
      &FwVolHandle
      );

    gDS->Dispatch ();
  }

  return EFI_SUCCESS;
}