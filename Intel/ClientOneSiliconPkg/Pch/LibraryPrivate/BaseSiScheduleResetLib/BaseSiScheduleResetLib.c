/** @file
  Reset scheduling library services

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include <Library/DebugLib.h>
#include <Library/ResetSystemLib.h>
#include <Uefi/UefiBaseType.h>
#include <Uefi.h>
#include <Pi/PiMultiPhase.h>
#include <Library/HobLib.h>
#include <PchResetPlatformSpecific.h>
#include <Library/SiScheduleResetLib.h>
#include <SiScheduleResetHob.h>

/**
  This function returns SiScheduleResetHob for library use
**/
STATIC
SI_SCHEDULE_RESET_HOB *
SiScheduleGetResetData (
  VOID
  )
{
  STATIC SI_SCHEDULE_RESET_HOB *SiScheduleResetHob = NULL;
  SI_SCHEDULE_RESET_HOB        *SiScheduleResetHobTemp;
  VOID                         *HobPtr;

  if (SiScheduleResetHob != NULL) {
    return SiScheduleResetHob;
  }

  HobPtr = GetFirstGuidHob (&gSiScheduleResetHobGuid);
  if (HobPtr == NULL) {
    SiScheduleResetHobTemp = BuildGuidHob (&gSiScheduleResetHobGuid, sizeof (SI_SCHEDULE_RESET_HOB));
    if (SiScheduleResetHobTemp == NULL) {
      ASSERT (FALSE);
      return SiScheduleResetHobTemp;
    }
    SiScheduleResetHobTemp->ResetType = 0xFF;
    DEBUG ((DEBUG_INFO, "SiScheduleResetSetType : Init SiScheduleResetHob\n"));
  } else {
    SiScheduleResetHobTemp = (SI_SCHEDULE_RESET_HOB*) GET_GUID_HOB_DATA (HobPtr);
  }
  SiScheduleResetHob = SiScheduleResetHobTemp;
  return SiScheduleResetHobTemp;
}

/**
  This function updates the reset information in SiScheduleResetHob
  @param[in] ResetType        UEFI defined reset type.
  @param[in] ResetData        Optional element used to introduce a platform specific reset.
                               The exact type of the reset is defined by the EFI_GUID that follows
                               the Null-terminated Unicode string.
**/
VOID
SiScheduleResetSetType (
  IN EFI_RESET_TYPE     ResetType,
  IN PCH_RESET_DATA     *ResetData OPTIONAL
  )
{
  SI_SCHEDULE_RESET_HOB *SiScheduleResetHob;
  if (ResetType > EfiResetPlatformSpecific) {
    DEBUG ((DEBUG_INFO, "Unsupported Reset Type Requested\n"));
    return;
  }
  SiScheduleResetHob = SiScheduleGetResetData ();
  if (SiScheduleResetHob == NULL) {
    return;
  }
  DEBUG ((DEBUG_INFO, "SiScheduleResetSetType : Current Reset Type = 0x%x\n", SiScheduleResetHob->ResetType));
  if (SiScheduleResetHob->ResetType == ResetType) {
    DEBUG ((DEBUG_INFO, "Current Reset Type is same as requested Reset Type\n"));
    return;
  }
  if (SiScheduleResetHob->ResetType == 0xFF) {
    // Init Reset Type to lowest ResetType
    SiScheduleResetHob->ResetType = EfiResetWarm;
  }
  //
  // ResetType Priority set as : ResetPlatformSpecific(3) > ResetShutdown(2) > ResetCold(0) > ResetWarm(1)
  //
  switch (ResetType) {
    case EfiResetWarm:
      break;

    case EfiResetCold:
      if (SiScheduleResetHob->ResetType == EfiResetWarm) {
        SiScheduleResetHob->ResetType = ResetType;
      }
      break;

    case EfiResetShutdown:
      if (SiScheduleResetHob->ResetType < ResetType)
      SiScheduleResetHob->ResetType = ResetType;
      break;

    case EfiResetPlatformSpecific:
      SiScheduleResetHob->ResetType = ResetType;
      SiScheduleResetHob->ResetData = *ResetData;
      break;
  }
  DEBUG ((DEBUG_INFO, "SiScheduleResetSetType : New Reset Type = 0x%x\n", SiScheduleResetHob->ResetType));
}

/**
  This function returns TRUE or FALSE depending on whether a reset is required based on SiScheduleResetHob

  @retval     BOOLEAN       The function returns FALSE if no reset is required
**/
BOOLEAN
SiScheduleResetIsRequired (
  VOID
  )
{
  VOID                  *HobPtr;

  HobPtr = NULL;
  HobPtr = GetFirstGuidHob (&gSiScheduleResetHobGuid);
  if (HobPtr == NULL) {
    return FALSE;
  }
  return TRUE;
}

/**
  This function performs reset based on SiScheduleResetHob

  @retval     BOOLEAN       The function returns FALSE if no reset is required
**/
BOOLEAN
SiScheduleResetPerformReset (
  VOID
  )
{
  UINTN                 DataSize;
  SI_SCHEDULE_RESET_HOB *SiScheduleResetHob;

  if (!SiScheduleResetIsRequired ()) {
    return FALSE;
  }
  SiScheduleResetHob = SiScheduleGetResetData ();

  if (SiScheduleResetHob == NULL) {
    return TRUE;
  }

  DEBUG ((DEBUG_INFO, "SiScheduleResetPerformReset : Reset Type = 0x%x\n", SiScheduleResetHob->ResetType));
  switch (SiScheduleResetHob->ResetType) {
  case EfiResetWarm:
    ResetWarm ();
    break;

  case EfiResetCold:
    ResetCold ();
    break;

  case EfiResetShutdown:
    ResetShutdown ();
    break;

  case EfiResetPlatformSpecific:
    DataSize = sizeof (PCH_RESET_DATA);
    ResetPlatformSpecific (DataSize, &SiScheduleResetHob->ResetData);
    break;
  }
  // Code should never reach here
  ASSERT (FALSE);
  return TRUE;
}
