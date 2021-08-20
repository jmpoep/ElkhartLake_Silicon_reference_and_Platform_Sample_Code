/** @file
  Provide TempRamInitParams data.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

@par Specification
**/

#include <Library/PcdLib.h>
#include <FsptUpd.h>

typedef struct {
  FSP_UPD_HEADER    FspUpdHeader;
  FSPT_CORE_UPD     FsptCoreUpd;
} FSPT_UPD_CORE_DATA;

GLOBAL_REMOVE_IF_UNREFERENCED CONST FSPT_UPD_CORE_DATA FsptUpdDataPtr = {
  {
    0x4450555F54505346,
    0x00,
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    }
  },
  {
#ifdef __GNUC__
    //
    // @todo to remove hard code values
    //
    0xFF800006,
    0x0009FFA0,
    0,
    0x00200000,
#else
    ((UINT32)FixedPcdGet64 (PcdCpuMicrocodePatchAddress) + FixedPcdGet32 (PcdFlashMicrocodeOffset)),
    ((UINT32)FixedPcdGet64 (PcdCpuMicrocodePatchRegionSize) - FixedPcdGet32 (PcdFlashMicrocodeOffset)),
    0,          // Set CodeRegionBase as 0, so that caching will be 4GB-(CodeRegionSize > LLCSize ? LLCSize : CodeRegionSize) will be used.
    FixedPcdGet32 (PcdFlashCodeCacheSize),
#endif
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    }
  }
};

//
// Used in Top Swap enabled case.
//
GLOBAL_REMOVE_IF_UNREFERENCED CONST FSPT_UPD_CORE_DATA FsptUpdDataPtrFt = {
  {
    0x4450555F54505346,
    0x00,
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    }
  },
  {
#ifdef __GNUC__
    //
    // @todo to remove hard code values
    //
    0xFF800006,
    0x0009FFA0,
    0,
    0x00200000,
#else
    ((UINT32)FixedPcdGet64 (PcdFtCpuMicrocodePatchAddress) + FixedPcdGet32 (PcdFlashMicrocodeOffset)),
    ((UINT32)FixedPcdGet64 (PcdCpuMicrocodePatchRegionSize) - FixedPcdGet32 (PcdFlashMicrocodeOffset)),
// @todo The set of PCDs for FlashFV has been changed in MinPlatform, the relevant code need to be redesign.
// @todo Needs to be updated with capsule feature implementation.
    //FixedPcdGet32 (PcdFtFlashFvRecovery2Base), // Set CodeRegionBase started from backup FvRecovery2
    0x00,
    FixedPcdGet32 (PcdFlashCodeCacheSize),
#endif
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    }
  }
};

