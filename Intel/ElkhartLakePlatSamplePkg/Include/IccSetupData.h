/** @file

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _ICC_SETUP_DATA_H_
#define _ICC_SETUP_DATA_H_

#define MAX_UI_CLOCKS    2

#define CLOCK1 1

#define INTEL_ICC_GUID \
{0x64192dca, 0xd034, 0x49d2, { 0xa6, 0xde, 0x65, 0xa8, 0x29, 0xeb, 0x4c, 0x74 }}

#define DONT_DISPLAY    0
#define DISPLAY         1

#define OPTION_DISABLED           0
#define OPTION_ENABLED            1

#define OPTION_LOCK_DEFAULT       0
#define OPTION_LOCK_ALL           1
#define OPTION_UNLOCK_ALL         2

#define ICC_SSC_NONE        0
#define ICC_SSC_UP          1
#define ICC_SSC_CENTER      2
#define ICC_SSC_DOWN        4

#define ICC_BCLK_REAL_TIME      0
#define ICC_BCLK_PERM_NO_WR     1

#define ICC_SETUP_DATA_C_NAME  L"IccAdvancedSetupDataVar"

//
// Ensure proper structure formats
//
#pragma pack(1)

typedef struct _ICC_SETUP_DATA {
  UINT16 Frequency;
  UINT8  Spread;
  UINT8  ShowFrequency;
  UINT8  ShowSpread;
  UINT8  ShowProfile;
  UINT8  Profile;
  UINT8  AllowAdvancedOptions;
} ICC_SETUP_DATA;

#pragma pack()

#endif
