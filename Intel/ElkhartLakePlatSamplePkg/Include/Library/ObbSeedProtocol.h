/** @file
    This file header for the the Seed Protocol DXE.

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
#ifndef _OBB_SEED_PROTOCOL_H_
#define _OBB_SEED_PROTOCOL_H_

#include <Base.h>
#include <Uefi/UefiBaseType.h>

#define OBB_SEED_PROTOCOL_GUID \
  {0xad6c3977, 0x6f5d, 0x4578, { 0xbc, 0xcb, 0x6b, 0x8c, 0xa2, 0x37, 0x7b, 0x45 } }

typedef struct _OBB_SEED_PROTOCOL OBB_SEED_PROTOCOL;

extern EFI_GUID gEfiObbSeedProtocolGuid;

#define OBB_SEED_LEN  64
typedef struct {
  UINT8 cse_svn;   // Always 0 for fixed seed
  UINT8 bios_svn;  // Always 0 for fixed seed.
                   // For SVN bound seed, populated in ICL, EHL and above.
  UINT8 Reserved[2];
  UINT8 seed[OBB_SEED_LEN];
} OBB_SEED_INFO;

#define OBB_SEED_INFO_LIST_MAX_ENTRIES  10
typedef struct {
  UINT8                NumOfSeeds;
  OBB_SEED_INFO SeedList[OBB_SEED_INFO_LIST_MAX_ENTRIES];
} OBB_SEED_INFO_LIST;

/**
 * Get the seed info list.
 *
 * Kernelflinger will prepare for the data buffer, and BIOS will copy the data to this buffer.
 */
typedef
EFI_STATUS
(EFIAPI *OBB_SEED_PROTOCOL_GET_SEED) (
  OUT OBB_SEED_INFO_LIST *buf
  );


struct _OBB_SEED_PROTOCOL {
  OBB_SEED_PROTOCOL_GET_SEED            GetObbSeed;
};

#endif /* _OBB_SEED_PROTOCOL_H_*/
