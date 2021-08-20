/** @file
  The PEI TCC Init Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 - 2020 Intel Corporation.

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

#include <Library/PeiServicesLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiTccInitLib.h>
#include <TccTuningHob.h>
#include <TccConfig.h>
#include <Library/TccLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED TCC_CONFIG               *mTccConfig = NULL;

/**
  Installs TCC Data Hob

  @retval EFI_SUCCESS           The HOB was successfully created.
  @retval EFI_OUT_OF_RESOURCES  There is no additional space for HOB creation.
**/
EFI_STATUS
InstallTccDataHob (
  VOID
  )
{

  EFI_STATUS                  Status;
  TCC_TUNING_HOB              *TccHob;

  ///
  /// Create HOB for TCC Tuning Data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (TCC_TUNING_HOB),
             (VOID **) &TccHob
             );
  ASSERT_EFI_ERROR (Status);
  ///
  /// Initialize default HOB data
  ///
  TccHob->EfiHobGuidType.Name = gTccHobGuid;
  DEBUG ((DEBUG_INFO, "TccHob->EfiHobGuidType.Name: %g\n", &TccHob->EfiHobGuidType.Name));
  ZeroMem (&(TccHob->TuningDataBaseAddress), (sizeof (TCC_TUNING_HOB) - sizeof (EFI_HOB_GUID_TYPE)));

  DEBUG ((DEBUG_INFO, "TccHob @ %X\n", TccHob));
  DEBUG ((DEBUG_INFO, "TccHob - HobHeader: %X\n", sizeof (TCC_TUNING_HOB) - sizeof (EFI_HOB_GUID_TYPE)));

  return Status;
}

/**
  This function updates the location of the TCC register structure

**/
VOID
UpdateTccBaseHob (
  UINTN  BaseAddress,
  UINT32 BaseSize
  )
{
  TCC_TUNING_HOB               *TccHob;

  DEBUG ((DEBUG_INFO, "[TCC] UpdateTccBaseHob Entry\n"));

  TccHob = NULL;
  TccHob = (TCC_TUNING_HOB *) GetFirstGuidHob (&gTccHobGuid);
  if (TccHob == NULL) {
    ASSERT (FALSE);
    return;
  }

  TccHob->TuningDataBaseAddress = (UINT64) BaseAddress;
  TccHob->TuningDataSize = BaseSize;

  DEBUG ((DEBUG_INFO, "[TCC] UpdateTccBaseHob End\n"));

  return;
}

/**
  Initialize TCC configuration for TCC performance

  @param[in] SiPolicyPpi          The SI Policy PPI instance
**/
VOID
EFIAPI
TccInit (
  IN  SI_POLICY_PPI           *SiPolicyPpi
  )
{
  EFI_STATUS                  Status;

  //
  // Performing TCC initialization from here.
  //
  DEBUG ((DEBUG_INFO, "[TCC] TccInit() - Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gTccConfigGuid, (VOID *) &mTccConfig);

  if (mTccConfig->TccTuningEnable) {
    TccTuning (TCC_POST_MEM_PHASE, (VOID*) mTccConfig->TccSubRegion.BaseAddress, mTccConfig->TccSubRegion.Size);
    DEBUG ((DEBUG_INFO, "Tcc Tuning Enabled. Creating TCC HOB\n"));
    Status = InstallTccDataHob ();
    if (!EFI_ERROR (Status)) {
      UpdateTccBaseHob (mTccConfig->TccSubRegion.BaseAddress, mTccConfig->TccSubRegion.Size);
    }
  }

  DEBUG ((DEBUG_INFO, "[TCC] TccInit() - End\n"));
}

