/** @file
  GUID used for Platform Info Data entries in the HOB list.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#ifndef _PLATFORM_INFO_H_
#define _PLATFORM_INFO_H_

#include <PlatformBoardType.h>

#pragma pack(1)

///
/// PCH_GPIO_PAD is equivalent to GPIO_PAD which is defined in GpioConfig.h
///
typedef UINT32 PCH_GPIO_PAD; //Copied from GpioConfig.h (need to change it based on include)

typedef struct {
UINT8    Expander;
UINT8    Pin;
UINT16   Reserved; // Reserved for future use
} IO_EXPANDER_PAD;

typedef union {
PCH_GPIO_PAD       PchGpio;
IO_EXPANDER_PAD    IoExpGpio;
} GPIO_PAD_CONFIG;

typedef struct {
UINT8                GpioType;    // 0: Disabled (no GPIO support), 1: PCH, 2: I/O Expander
UINT8                Reserved[3]; // Reserved for future use
GPIO_PAD_CONFIG      GpioData;
} PACKED_GPIO_CONFIG;

typedef union {
PACKED_GPIO_CONFIG    PackedGpio;
UINT64                Data64;
} COMMON_GPIO_CONFIG;

#pragma pack()

#endif
