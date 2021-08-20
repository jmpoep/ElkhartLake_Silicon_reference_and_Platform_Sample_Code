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
#ifndef _BOOTLOADER_SEED_PROTOCOL_H_
#define _BOOTLOADER_SEED_PROTOCOL_H_

#include <Base.h>
#include <Uefi/UefiBaseType.h>

#define BOOTLOADER_SEED_PROTOCOL_GUID \
  {0x3e764148, 0x316c, 0x41ba, { 0x9b, 0x85, 0x94, 0x3f, 0x92, 0xa3, 0xcc, 0x7f } }

typedef struct _BOOTLOADER_SEED_PROTOCOL BOOTLOADER_SEED_PROTOCOL;

extern EFI_GUID gEfiBootloaderSeedProtocolGuid;

/**
 * Tell the BIOS should end of the service of this protocol.
 *
 * Kernelflinger should call this function after call other functions.
 * Then BIOS should return EFI_ACCESS_DENIED if call the other functions again.
 */
typedef
EFI_STATUS
(EFIAPI *BLS_PROTOCOL_ENDOFSERVICE) ();


#define BOOTLOADER_SEED_LEN  64
typedef struct {
  UINT8 cse_svn;   // Always 0 for fixed seed
  UINT8 bios_svn;  // Always 0 for fixed seed.
                   // For SVN bound seed, populated in ICL, EHL and above.
  UINT8 Reserved[2];
  UINT8 seed[BOOTLOADER_SEED_LEN];
} BOOTLOADER_SEED_INFO;

#define BOOTLOADER_SEED_INFO_LIST_MAX_ENTRIES  10
typedef struct {
  UINT8                NumOfSeeds;
  BOOTLOADER_SEED_INFO SeedList[BOOTLOADER_SEED_INFO_LIST_MAX_ENTRIES];
} BOOTLOADER_SEED_INFO_LIST;

/**
 * Get the seed info list.
 *
 * Kernelflinger will prepare for the data buffer, and BIOS will copy the data to this buffer.
 */
typedef
EFI_STATUS
(EFIAPI *BLS_PROTOCOL_GET_SEED_INFO_LIST) (
  IN OUT BOOTLOADER_SEED_INFO_LIST *buf
  );


/* The max RPMB key size set to 64, and currently is 32 bytes in general, use rpmb_key[0-31]. */
#define BOOTLOADER_RPMB_MAX_KEY_SIZE  64
typedef struct {
  UINT8 rpmb_partition_no;  // This key is used for which RPMB partition, if the hardware has multi RPMB partitions.
  UINT8 rpmb_key_size;
  UINT8 rpmb_key[BOOTLOADER_RPMB_MAX_KEY_SIZE];
} BOOTLOADER_RPMB_KEY;

/**
 * Get the RPMB key.
 *
 * Kernelflinger will prepare for the data buffer, and BIOS will copy the data to this buffer.
 *
 * @num_keys  IN   the entry size of buf, in general is 6 for max RPMB partitions/keys.
 *            OUT  the final output keys number, should <= the input value.
 *
 * @buf       IN   the input array of BOOTLOADER_RPMB_KEY, has num_keys entry.
 *            OUT  the BIOS will copy data to the input buffer.
 */
typedef
EFI_STATUS
(EFIAPI *BLS_PROTOCOL_GET_RPMB_KEY) (
  IN OUT UINT8 *num_keys,
  IN OUT BOOTLOADER_RPMB_KEY *buf
  );


#define BOOTLOADER_ATTKB_ENC_KEY_LEN  32
typedef struct {
  UINT8 attkb_enc_key[BOOTLOADER_ATTKB_ENC_KEY_LEN];
} BOOTLOADER_ATTKB_ENC_KEY;

/**
 * Get the encrypt key for attkb.
 *
 * Kernelflinger will prepare for the data buffer, and the BIOS will copy the data to this buffer.
 */
typedef
EFI_STATUS
(EFIAPI *BLS_PROTOCOL_GET_ATTKB_ENC_KEY) (
  IN OUT BOOTLOADER_ATTKB_ENC_KEY *buf
  );


struct _BOOTLOADER_SEED_PROTOCOL {
  BLS_PROTOCOL_ENDOFSERVICE             EndOfService;
  BLS_PROTOCOL_GET_SEED_INFO_LIST       GetSeedInfoList;
  BLS_PROTOCOL_GET_RPMB_KEY             GetRpmbKey;
  BLS_PROTOCOL_GET_ATTKB_ENC_KEY        GetAttKBEncKey;
};

#endif /* _BOOTLOADER_SEED_PROTOCOL_H_*/
