/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#include "Uefi.h"

CHAR16 *mBoardIdIndex[] = {
//L"0123456789ABCDEF0123456789ABCDEF"       // Do not exceed 32 characters
  L"TBD",                                   // 0x00
  L"ElkhartLake LPDDR4x T4 ERB",            // 0x01
  L"ElkhartLake LPDDR4x T4 RVP",            // 0x02
  L"ElkhartLake DDR4 SODIMM T3 RVP",        // 0x03
  L"TBD",                                   // 0x04
  L"ElkhartLake LPDDR4x T3 CRB",            // 0x05
  L"TBD",                                   // 0x06
  L"TBD",                                   // 0x07
  L"TBD",                                   // 0x08
  L"TBD",                                   // 0x09
  L"TBD",                                   // 0x0A
  L"TBD",                                   // 0x0B
  L"TBD",                                   // 0x0C
  L"TBD",                                   // 0x0D
  L"TBD",                                   // 0x0E
  L"TBD",                                   // 0x0F
  L"TBD",                                   // 0x10
  L"TBD",                                   // 0x11
  L"TBD",                                   // 0x12
  L"TBD",                                   // 0x13
  L"TBD",                                   // 0x14
  L"TBD",                                   // 0x15
  L"TBD",                                   // 0x16
  L"TBD",                                   // 0x17
  L"TBD",                                   // 0x18
  L"TBD",                                   // 0x19
  L"TBD",                                   // 0x1A
  L"TBD",                                   // 0x1B
  L"TBD",                                   // 0x1C
  L"TBD",                                   // 0x1D
  L"TBD",                                   // 0x1E
  L"TBD",                                   // 0x1F
};

UINT8 mSizeOfmBoardIndex = sizeof(mBoardIdIndex)/sizeof(CHAR16*);

