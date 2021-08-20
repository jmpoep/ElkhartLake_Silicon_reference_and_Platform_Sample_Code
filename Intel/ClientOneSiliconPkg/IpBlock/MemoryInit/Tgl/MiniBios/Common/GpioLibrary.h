/** @file
  Header file for GPIO Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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
#ifndef _GPIO_LIBRARY_H_
#define _GPIO_LIBRARY_H_

#include "MrcOemPlatform.h"
#include "PchAccess.h"
#include "GpioLib.h"
#include "GpioNativeLib.h"
#include "GpioPrivateLib.h"
#include "PchInfoLib.h"

// BIT15-0  - pad number
// BIT31-16 - group info
//   BIT23- 16 - group index
//   BIT31- 24 - chipset ID
#define PAD_INFO_MASK          0x0000FFFF
#define GROUP_INFO_POSITION    16
#define GROUP_INFO_MASK        0xFFFF0000
#define GROUP_INDEX_MASK       0x00FF0000
#define UNIQUE_ID_MASK         0xFF000000
#define UNIQUE_ID_POSITION     24

#define GPIO_PAD_DEF(Group,Pad)               (UINT32)(((Group) << 16) + (Pad))
#define GPIO_GROUP_DEF(Index,ChipsetId)       ((Index) | ((ChipsetId) << 8))
#define GPIO_GET_GROUP_INDEX(Group)           ((Group) & 0xFF)
#define GPIO_GET_GROUP_FROM_PAD(Pad)          ((Pad) >> 16)
#define GPIO_GET_GROUP_INDEX_FROM_PAD(Pad)    GPIO_GET_GROUP_INDEX (((Pad) >> 16))
#define GPIO_GET_PAD_NUMBER(Pad)              ((Pad) & 0xFFFF)
#define GPIO_GET_CHIPSET_ID(Pad)              ((Pad) >> 24)

#define GPIO_GET_PAD_POSITION(PadNumber)      ((PadNumber) % 32)
#define GPIO_GET_DW_NUM(PadNumber)            ((PadNumber) / 32u)

//
// Number of PADCFG_DW registers
//
#define GPIO_PADCFG_DW_REG_NUMBER  4

/**
  This internal procedure will calculate GPIO_RESET_CONFIG value  (new type)
  based on provided PadRstCfg for a specific GPIO Pad.

  @param[in]  GpioPad               GPIO Pad
  @param[in]  PadRstCfg             GPIO PadRstCfg value

  @retval GpioResetConfig           GPIO Reset configuration (new type)
**/
GPIO_RESET_CONFIG
GpioResetConfigFromPadRstCfg (
  IN  GPIO_PAD           GpioPad,
  IN  UINT32             PadRstCfg
  );

/**
  This internal procedure will calculate PadRstCfg register value based
  on provided GPIO Reset configuration for a certain pad.

  @param[in]  GpioPad                   GPIO Pad
  @param[in]  GpioResetConfig           GPIO Reset configuration
  @param[out] PadRstCfg                 GPIO PadRstCfg value

  @retval EFI_SUCCESS                   The function completed successfully
  @retval EFI_INVALID_PARAMETER         Invalid configuration
**/
EFI_STATUS
GpioPadRstCfgFromResetConfig (
  IN  GPIO_PAD           GpioPad,
  IN  GPIO_RESET_CONFIG  GpioResetConfig,
  OUT UINT32             *PadRstCfg
  );

/**
  This procedure will calculate PADCFG register value based on GpioConfig data

  @param[in]  GpioPad                   GPIO Pad
  @param[in]  GpioConfig                GPIO Configuration data
  @param[out] PadCfgDwReg               PADCFG DWx register value
  @param[out] PadCfgDwRegMask           Mask with PADCFG DWx register bits to be modified

  @retval Status
**/
EFI_STATUS
GpioPadCfgRegValueFromGpioConfig (
  IN  GPIO_PAD           GpioPad,
  IN  CONST GPIO_CONFIG  *GpioConfig,
  OUT UINT32             *PadCfgDwReg,
  OUT UINT32             *PadCfgDwRegMask
  );

/**
  Generates GPIO group name from GroupIndex

  @param[in] GroupIndex  Gpio GroupIndex

  @retval CHAR8*  Pointer to the GPIO group name
**/
CONST
CHAR8*
GpioGetGroupName (
  IN UINT32  GroupIndex
  );

#endif // _GPIO_LIBRARY_H_
