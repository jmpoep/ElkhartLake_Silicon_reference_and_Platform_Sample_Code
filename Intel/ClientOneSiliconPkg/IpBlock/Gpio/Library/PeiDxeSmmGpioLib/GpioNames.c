/** @file
  This file contains GPIO name library implementation

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include "GpioLibrary.h"
#include <Library/PrintLib.h>

/**
  Generates GPIO group name from GpioPad

  @param[in] GpioPad  GpioPad

  @retval CHAR8*  Pointer to the GPIO group name
**/
CONST
CHAR8*
GpioGetGroupName (
  IN UINT32  GroupIndex
  )
{
  CONST GPIO_GROUP_NAME_INFO*  GroupNameInfo;

  GroupNameInfo = GpioGetGroupNameInfo (GroupIndex);
  if (GroupNameInfo == NULL) {
    return NULL;
  } else {
    return GroupNameInfo->GpioGroupPrefix;
  }
}

/**
  Generates GPIO name from GpioPad

  @param[in]  GpioPad             GpioPad
  @param[out] GpioNameBuffer      Caller allocated buffer of GPIO_NAME_LENGTH_MAX size
  @param[in]  GpioNameBufferSize  Size of the buffer

  @retval CHAR8*  Pointer to the GPIO name
**/
CHAR8*
GpioGetPadName (
  IN GPIO_PAD  GpioPad,
  OUT CHAR8*   GpioNameBuffer,
  IN UINT32    GpioNameBufferSize
  )
{
  UINT32                       GroupIndex;
  UINT32                       PadNumber;
  UINT32                       FirstUniquePadNumber;
  CONST GPIO_GROUP_NAME_INFO*  GroupNameInfo;

  if (GpioNameBuffer == NULL) {
    ASSERT (FALSE);
    return NULL;
  }
  if ((GpioNameBufferSize < GPIO_NAME_LENGTH_MAX) || !GpioIsPadValid (GpioPad)) {
    ASSERT (FALSE);
    *GpioNameBuffer = 0;
    return NULL;
  }

  GroupIndex = GpioGetGroupIndexFromGpioPad (GpioPad);
  PadNumber = GpioGetPadNumberFromGpioPad (GpioPad);
  GroupNameInfo = GpioGetGroupNameInfo (GroupIndex);
  if (GroupNameInfo == NULL) {
    return NULL;
  }

  FirstUniquePadNumber = GpioGetPadNumberFromGpioPad (GroupNameInfo->FirstUniqueGpio);
  if ((PadNumber < FirstUniquePadNumber) || (GroupNameInfo->GroupUniqueNames == NULL)) {
    AsciiSPrint (GpioNameBuffer, GPIO_NAME_LENGTH_MAX, "GPIO_%a%d", GpioGetGroupName (GroupIndex), PadNumber);
  } else {
    if ((PadNumber - FirstUniquePadNumber) < GroupNameInfo->UniqueNamesTableSize) {
      AsciiSPrint (GpioNameBuffer, GPIO_NAME_LENGTH_MAX, "GPIO_%a", GroupNameInfo->GroupUniqueNames[PadNumber - FirstUniquePadNumber]);
    } else {
      AsciiSPrint (GpioNameBuffer, GPIO_NAME_LENGTH_MAX, "GPIO_%08X", GpioPad);
      ASSERT (FALSE);
    }
  }

  return GpioNameBuffer;
}

