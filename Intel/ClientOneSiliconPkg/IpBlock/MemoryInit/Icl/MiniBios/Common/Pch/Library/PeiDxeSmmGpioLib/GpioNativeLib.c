/** @file
  This file contains routines for GPIO native and chipset specific usage

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#include "MrcOemPlatform.h"
#include "GpioLibrary.h"

/**
  This procedure will get number of pads for certain GPIO group

  @param[in] Group            GPIO group number

  @retval Value               Pad number for group
                              If illegal group number then return 0
**/
UINT32
GpioGetPadPerGroup (
  IN GPIO_GROUP      Group
  )
{
  CONST GPIO_GROUP_INFO  *GpioGroupInfo;
  UINT32                 GpioGroupInfoLength;
  UINT32                 GroupIndex;
  //
  // Check if group argument exceeds GPIO GROUP INFO array
  //
  GpioGroupInfo = GpioGetGroupInfoTable (&GpioGroupInfoLength);
  GroupIndex = GpioGetGroupIndexFromGroup (Group);

  if ((UINTN) GroupIndex >= GpioGroupInfoLength) {
    return 0;
  } else {
    return GpioGroupInfo[GroupIndex].PadPerGroup;
  }
}

/**
  This procedure will get number of groups

  @param[in] none

  @retval Value               Group number
**/
UINT32
GpioGetNumberOfGroups (
  VOID
  )
{
  UINT32                 GpioGroupInfoLength;

  GpioGetGroupInfoTable (&GpioGroupInfoLength);
  return GpioGroupInfoLength;
}
/**
  This procedure will get lowest group

  @param[in] none

  @retval Value               Lowest Group
**/
GPIO_GROUP
GpioGetLowestGroup (
  VOID
  )
{
  return GpioGetGroupFromGroupIndex (0);
}
/**
  This procedure will get highest group

  @param[in] none

  @retval Value               Highest Group
**/
GPIO_GROUP
GpioGetHighestGroup (
  VOID
  )
{
  return GpioGetGroupFromGroupIndex (GpioGetNumberOfGroups () - 1);
}

/**
  This procedure will get group number

  @param[in] GpioPad          Gpio Pad

  @retval Value               Group number
**/
GPIO_GROUP
GpioGetGroupFromGpioPad (
  IN GPIO_PAD         GpioPad
  )
{
  return GPIO_GET_GROUP_FROM_PAD (GpioPad);
}

/**
  This procedure will get group index (0 based)

  @param[in] GpioPad          Gpio Pad

  @retval Value               Group Index
**/
UINT32
GpioGetGroupIndexFromGpioPad (
  IN GPIO_PAD        GpioPad
  )
{
  return (UINT32) GPIO_GET_GROUP_INDEX_FROM_PAD (GpioPad);
}

/**
  This procedure will get group index (0 based) from group

  @param[in] GpioGroup        Gpio Group

  @retval Value               Group Index
**/
UINT32
GpioGetGroupIndexFromGroup (
  IN GPIO_GROUP        GpioGroup
  )
{
  return (UINT32) GPIO_GET_GROUP_INDEX (GpioGroup);
}

/**
  This procedure will get group from group index (0 based)

  @param[in] GroupIndex        Group Index

  @retval GpioGroup            Gpio Group
**/
GPIO_GROUP
GpioGetGroupFromGroupIndex (
  IN UINT32        GroupIndex
  )
{
  return GPIO_GROUP_DEF (GroupIndex, GpioGetThisChipsetId ());
}

/**
  This procedure will get pad number (0 based) from Gpio Pad

  @param[in] GpioPad          Gpio Pad

  @retval Value               Pad Number
**/
UINT32
GpioGetPadNumberFromGpioPad (
  IN GPIO_PAD        GpioPad
  )
{
  return (UINT32) GPIO_GET_PAD_NUMBER (GpioPad);
}
/**
  This procedure will return GpioPad from Group and PadNumber

  @param[in] Group              GPIO group
  @param[in] PadNumber          GPIO PadNumber

  @retval GpioPad               GpioPad
**/
GPIO_PAD
GpioGetGpioPadFromGroupAndPadNumber (
  IN GPIO_GROUP      Group,
  IN UINT32          PadNumber
  )
{
  if (IsPchLp ()) {
    return GPIO_PAD_DEF (Group,PadNumber);
  } else {
    return GPIO_PAD_DEF (Group,PadNumber);
  }
}

/**
  This procedure will return GpioPad from GroupIndex and PadNumber

  @param[in] GroupIndex         GPIO GroupIndex
  @param[in] PadNumber          GPIO PadNumber

  @retval GpioPad               GpioPad
**/
GPIO_PAD
GpioGetGpioPadFromGroupIndexAndPadNumber (
  IN UINT32          GroupIndex,
  IN UINT32          PadNumber
  )
{
  GPIO_GROUP Group;

  Group = GPIO_GROUP_DEF (GroupIndex, GpioGetThisChipsetId ());
  return GPIO_PAD_DEF (Group, PadNumber);
}

#ifndef MRC_MINIBIOS_BUILD
/**
  This function checks if SATA GP pin is enabled

  @param[in]  SataCtrlIndex       SATA controller index
  @param[in]  SataPort            SATA port number

  @retval TRUE                    SATA GPx is enabled (pad is in required native mode)
          FALSE                   SATA GPx is not enabled
**/
BOOLEAN
GpioIsSataGpEnabled (
  IN  UINT32          SataCtrlIndex,
  IN  UINTN           SataPort
  )
{
  EFI_STATUS                Status;
  GPIO_PAD_NATIVE_FUNCTION  SataGpGpio;
  GPIO_PAD_MODE             GpioMode;

  ASSERT (SataCtrlIndex < GetPchMaxSataControllerNum ());

  GpioGetSataGpPin (
    SataCtrlIndex,
    SataPort,
    &SataGpGpio
    );

  Status =  GpioGetPadMode (SataGpGpio.Pad, &GpioMode);
  if ((EFI_ERROR (Status)) || (GpioMode != SataGpGpio.Mode)) {
    return FALSE;
  } else {
    return TRUE;
  }
}
#endif // MRC_MINIBIOS_BUILD

