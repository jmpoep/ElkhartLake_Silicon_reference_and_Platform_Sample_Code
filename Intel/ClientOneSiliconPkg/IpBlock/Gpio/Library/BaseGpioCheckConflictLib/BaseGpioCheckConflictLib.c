/** @file
  Implementation of BaseGpioCheckConflictLib.

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

@par Specification Reference:
**/

#include <Library/GpioCheckConflictLib.h>
#include <Uefi/UefiMultiPhase.h>
#include <Pi/PiBootMode.h>
#include <Pi/PiHob.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/GpioPrivateLib.h>

/**
  Check Gpio PadMode conflict and report it.

  @retval     none.
**/
VOID
GpioCheckConflict (
  VOID
  )
{
  EFI_HOB_GUID_TYPE              *GpioCheckConflictHob;
  GPIO_PAD_MODE_INFO             *GpioCheckConflictHobData;
  UINT32                          HobDataSize;
  UINT32                          GpioCount;
  UINT32                          GpioIndex;
  GPIO_CONFIG                     GpioActualConfig;

  GpioCheckConflictHob = NULL;
  GpioCheckConflictHobData = NULL;

  DEBUG ((DEBUG_INFO, "GpioCheckConflict Start..\n"));

  //
  // Use Guid to find HOB.
  //
  GpioCheckConflictHob = (EFI_HOB_GUID_TYPE *) GetFirstGuidHob (&gGpioCheckConflictHobGuid);
  if (GpioCheckConflictHob == NULL) {
    DEBUG ((DEBUG_INFO, "[GPIO Conflict Check] No GPIO HOB found.\n"));
  } else {
    while (GpioCheckConflictHob != NULL) {
      //
      // Find the Data area pointer and Data size from the Hob
      //
      GpioCheckConflictHobData = (GPIO_PAD_MODE_INFO *) GET_GUID_HOB_DATA (GpioCheckConflictHob);
      HobDataSize = GET_GUID_HOB_DATA_SIZE (GpioCheckConflictHob);

      GpioCount = HobDataSize / sizeof (GPIO_PAD_MODE_INFO);
      DEBUG ((DEBUG_INFO, "[GPIO Conflict Check] Hob : GpioCount =  %d\n", GpioCount));

      //
      // Probe Gpio entries in Hob and compare which are conflicted
      //
      for (GpioIndex = 0; GpioIndex < GpioCount ; GpioIndex++) {
        GpioGetPadConfig (GpioCheckConflictHobData[GpioIndex].GpioPad, &GpioActualConfig);
        if (GpioCheckConflictHobData[GpioIndex].GpioPadMode != GpioActualConfig.PadMode) {
          DEBUG ((DEBUG_ERROR, "[GPIO Conflict Check] Identified conflict on pad %a (actual: 0x%X, expected: 0x%X)\n",
                  GpioName (GpioCheckConflictHobData[GpioIndex].GpioPad),
                  GpioActualConfig.PadMode,
                  GpioCheckConflictHobData[GpioIndex].GpioPadMode));
        }
      }
      //
      // Find next Hob and return the Hob pointer by the specific Hob Guid
      //
      GpioCheckConflictHob = GET_NEXT_HOB (GpioCheckConflictHob);
      GpioCheckConflictHob = GetNextGuidHob (&gGpioCheckConflictHobGuid, GpioCheckConflictHob);
    }

    DEBUG ((DEBUG_INFO, "GpioCheckConflict End.\n"));
  }

  return;
}

/**
  This libaray will create one Hob for each Gpio config table
  without PadMode is GpioHardwareDefault

  @param[in]  GpioDefinition    Point to Platform Gpio table
  @param[in]  GpioTableCount    Number of Gpio table entries

  @retval     none.
**/
VOID
CreateGpioCheckConflictHob (
  IN GPIO_INIT_CONFIG          *GpioDefinition,
  IN UINT32                    GpioTableCount
  )
{

  UINT32                   Index;
  UINT32                   GpioIndex;
  GPIO_PAD_MODE_INFO       *GpioCheckConflictHobData;
  UINT16                   GpioCount;

  GpioCount = 0;
  GpioIndex = 0;

  DEBUG ((DEBUG_INFO, "CreateGpioCheckConflictHob Start \n"));

  for (Index = 0; Index < GpioTableCount ; Index++) {
    if (GpioDefinition[Index].GpioConfig.PadMode == GpioHardwareDefault) {
      continue;
    } else {
      //
      // Calculate non-default GPIO number
      //
      GpioCount++;
    }
  }

  //
  // Build a HOB tagged with a GUID for identification and returns
  // the start address of GUID HOB data.
  //
  GpioCheckConflictHobData = (GPIO_PAD_MODE_INFO *) BuildGuidHob (&gGpioCheckConflictHobGuid , GpioCount * sizeof (GPIO_PAD_MODE_INFO));

  //
  // Record Non Default Gpio entries to the Hob
  //
  for (Index = 0; Index < GpioTableCount; Index++) {
    if (GpioDefinition[Index].GpioConfig.PadMode == GpioHardwareDefault) {
      continue;
    } else {
      GpioCheckConflictHobData[GpioIndex].GpioPad = GpioDefinition[Index].GpioPad;
      GpioCheckConflictHobData[GpioIndex].GpioPadMode = GpioDefinition[Index].GpioConfig.PadMode;
      GpioIndex++;
    }
  }

  DEBUG ((DEBUG_INFO, "CreateGpioCheckConflictHob End \n"));
  return;
}
