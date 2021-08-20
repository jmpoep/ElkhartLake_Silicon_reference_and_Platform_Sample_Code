/** @file
  Driver for Decompressing FVMAIN2 when CSM mode is enabled.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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
#include <BootState.h>
#include <SetupVariable.h>
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
#include <Guid/SysFwUpdateProgress.h>
#include <Library/HobLib.h>
#endif

EFI_STATUS
EFIAPI
DecompressFvMain2EntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  UINTN                   VarSize;
  EFI_STATUS              Status;
  EFI_HANDLE              FwVolHandle;
  VOID                    *BootState;
  CPU_SETUP               CpuSetup;
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
  EFI_HOB_GUID_TYPE       *GuidHob;

  GuidHob = NULL;
#endif
  GetVariable2 (L"BootState", &gBootStateGuid, &BootState, NULL);

  if (BootState == NULL) {
    DEBUG((DEBUG_INFO, "[FVMAIN2] FVMAIN2 will be processed by SpiFvbService driver\n"));
    return EFI_SUCCESS;
  }

  VarSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VarSize,
                  &CpuSetup
                  );
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_ERROR, "[FVMAIN2] Fail to get CPU Setup variable\n"));
    return Status;
  }
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
  GuidHob = GetFirstGuidHob (&gSysFwUpdateProgressGuid);
  if ((GuidHob != NULL) && \
      (((SYSTEM_FIRMWARE_UPDATE_PROGRESS *) GET_GUID_HOB_DATA (GuidHob))->Component == UpdatingBios)) {
    return EFI_SUCCESS;
  }
#endif
    if ((CpuSetup.OverclockingSupport)) {
      DEBUG((DEBUG_INFO, "[FVMAIN2] Over-clocking is enabled, Decompressing FVMAIN2.\n"));
      gDS->ProcessFirmwareVolume (
        (VOID *) (UINTN)PcdGet32(PcdFlashFvMain2Base),
        PcdGet32(PcdFlashFvMain2Size),
        &FwVolHandle
        );

      gDS->Dispatch ();
    }

  return EFI_SUCCESS;
}
