/** @file
  TSN Config policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#ifndef _TSN_CONFIG_H_
#define _TSN_CONFIG_H_

#include <ConfigBlock.h>

#define TSN_CONFIG_REVISION 1
extern EFI_GUID gTsnConfigGuid;

#define TSN_MAX_SUB_REGIONS     3

#pragma pack (push,1)

typedef struct {
  UINTN                 BaseAddress;
  UINT32                Size;
} TSN_SUB_REGION_INFO;

/**
  TSN Config settings.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                ///< Config Block Header
  TSN_SUB_REGION_INFO   TsnSubRegion[TSN_MAX_SUB_REGIONS];
  /**
    Determines if enable PCH internal TSN, 0: Disable; <b>1: Enable</b>.
  **/
  UINT8                PchTsnEnable;
  UINT8                PchTsnGbeMultiVcEnable;
  UINT8                PchTsnGbeLinkSpeed;     ///< Refer to "TSN_LINK_SPEED_OPTIONS". Default is <b> TSN_LINK_SPEED_2_5G_34MHZ</b>
  UINT8                PchTsnGbeSgmiiEnable;
  UINT8                PseTsnGbeMultiVcEnable[2];
  UINT8                PseTsnGbeLinkSpeed[2];  ///< Refer to "TSN_LINK_SPEED_OPTIONS". Default is <b> TSN_LINK_SPEED_1G_34MHZ</b>
  UINT8                PseTsnGbeSgmiiEnable[2];
  UINT8                Rsvd0[2];
} TSN_CONFIG;

#pragma pack (pop)

typedef struct {
  UINT32 RsvdBits1     : 12;                   ///< [11:0]  Reserved bits
  UINT32 Func          : 3;                    ///< [14:12] Function Id
  UINT32 Dev           : 5;                    ///< [19:15] Device Id
  UINT32 Bus           : 8;                    ///< [27:20] Bud Id
  UINT32 RsvdBits0     : 4;                    ///< [31:28] Reserved bits
} BDF;

typedef enum {
  TSN_LINK_SPEED_2_5G_24MHZ = 0,
  TSN_LINK_SPEED_1G_24MHZ,
  TSN_LINK_SPEED_2_5G_34MHZ,
  TSN_LINK_SPEED_1G_34MHZ
} TSN_LINK_SPEED_OPTIONS;

#endif // TSN_CONFIG_H_

