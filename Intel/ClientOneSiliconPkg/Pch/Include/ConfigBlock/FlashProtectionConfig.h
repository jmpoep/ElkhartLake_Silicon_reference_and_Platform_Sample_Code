/** @file
  FlashProtection policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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
#ifndef _FLASH_PROTECTION_CONFIG_H_
#define _FLASH_PROTECTION_CONFIG_H_

#define FLASH_PROTECTION_CONFIG_REVISION 1
extern EFI_GUID gFlashProtectionConfigGuid;

#pragma pack (push,1)

//
// Flash Protection Range Register
//
#define PCH_FLASH_PROTECTED_RANGES         5

/**
  The PCH provides a method for blocking writes and reads to specific ranges
  in the SPI flash when the Protected Ranges are enabled.
  PROTECTED_RANGE is used to specify if flash protection are enabled,
  the write protection enable bit and the read protection enable bit,
  and to specify the upper limit and lower base for each register
  Platform code is responsible to get the range base by PchGetSpiRegionAddresses routine,
  and set the limit and base accordingly.
**/
typedef struct {
  UINT32                WriteProtectionEnable     :  1;     ///< Write or erase is blocked by hardware. <b>0: Disable</b>; 1: Enable.
  UINT32                ReadProtectionEnable      :  1;     ///< Read is blocked by hardware. <b>0: Disable</b>; 1: Enable.
  UINT32                RsvdBits                  :  30;    ///< Reserved
  /**
    The address of the upper limit of protection
    This is a left shifted address by 12 bits with address bits 11:0 are assumed to be FFFh for limit comparison
  **/
  UINT16                ProtectedRangeLimit;
  /**
    The address of the upper limit of protection
    This is a left shifted address by 12 bits with address bits 11:0 are assumed to be 0
  **/
  UINT16                ProtectedRangeBase;
} PROTECTED_RANGE;

typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  PROTECTED_RANGE       ProtectRange[PCH_FLASH_PROTECTED_RANGES];
} PCH_FLASH_PROTECTION_CONFIG;

#pragma pack (pop)

#endif // _FLASH_PROTECTION_CONFIG_H_
