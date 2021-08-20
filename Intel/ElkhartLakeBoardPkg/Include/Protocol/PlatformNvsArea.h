/** @file
  This file defines the Platform NVS Area Protocol.

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

#ifndef _PLATFORM_NVS_AREA_H_
#define _PLATFORM_NVS_AREA_H_

//
// Platform NVS Area definition
//
#include <PlatformNvsAreaDef.h>

//
// Includes
//
#define PLATFORM_NVS_DEVICE_ENABLE 1
#define PLATFORM_NVS_DEVICE_DISABLE 0

//
// Forward reference for pure ANSI compatibility
//
typedef struct _PLATFORM_NVS_AREA_PROTOCOL PLATFORM_NVS_AREA_PROTOCOL;

//
// Platform NVS Area Protocol GUID
//
#define PLATFORM_NVS_AREA_PROTOCOL_GUID \
{ 0xc77ae556,0x40a3, 0x41c0, 0xac, 0xe6, 0x71, 0x43, 0x8c, 0x60, 0xf8, 0x71 }

#define PLATFORM_NVS_AREA_REVISION_1       1

//
// Platform NVS Area Protocol
//
typedef struct _PLATFORM_NVS_AREA_PROTOCOL {
  PLATFORM_NVS_AREA     *Area;
} PLATFORM_NVS_AREA_PROTOCOL;

#endif // _PLATFORM_NVS_AREA_H_
