/** @file
  This file contains GpioMemLib implementation for PEI phase

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

#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/GpioNameBufferLib.h>

STATIC CONST EFI_GUID mGpioNamesPrivateHobGuid = {0x9AE3138D, 0x4EBF, 0x4E90, {0x87, 0x96, 0x11, 0xD3, 0x10, 0x04, 0x60, 0x0A}};

STATIC volatile BOOLEAN mGlobalMemoryWorking = FALSE;

STATIC CHAR8 mGpioNameBuffer[GPIO_NAME_LENGTH_MAX];

/**
  Returns pointer to the buffer taken from GpioLib private HOB

  @retval CHAR8*  Pointer to the buffer
**/
STATIC
CHAR8*
GetBufferFromHob (
  VOID
  )
{
  VOID  *Hob;
  CHAR8 *GpioNameBuffer;

  Hob = NULL;
  GpioNameBuffer = NULL;

  Hob = GetFirstGuidHob (&mGpioNamesPrivateHobGuid);
  if (Hob != NULL){
    GpioNameBuffer = (CHAR8*) GET_GUID_HOB_DATA (Hob);
  } else {
    GpioNameBuffer = (CHAR8*) BuildGuidHob (&mGpioNamesPrivateHobGuid, GPIO_NAME_LENGTH_MAX);
    if (GpioNameBuffer == NULL){
      DEBUG ((DEBUG_ERROR, "Failed to setup HOB for GPIO names lib\n"));
      ASSERT (FALSE);
    }
  }
  return GpioNameBuffer;
}

/**
  Returns pointer to the global buffer to be used by GpioNamesLib

  @retval CHAR8*  Pointer to the buffer
**/
CHAR8*
GpioGetStaticNameBuffer (
  VOID
  )
{
  mGlobalMemoryWorking = TRUE;

  if (mGlobalMemoryWorking) {
    return mGpioNameBuffer;
  } else {
    return GetBufferFromHob ();
  }
}

