/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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
#ifndef _ATA_SECURE_ERASE_H_
#define _ATA_SECURE_ERASE_H_

#include <Protocol/AtaPassThru.h>
#include <IndustryStandard/Atapi.h>
#include <Library/DxeAmtHeciLib.h>

#define IS_FLAG_SET(vector,flag) (((vector)&(flag)) != 0 )

///
/// Ata IDENTIFY DEVICE data, word 128, security related flags
///
#define ATA_DATA_SECURITY_LEVEL                            ((UINT16)BIT8)
#define ATA_DATA_SECURE_ERASE_BIT                          ((UINT16)BIT5)
#define ATA_DATA_SECURITY_COUNT_EXPIRED_BIT                ((UINT16)BIT4)
#define ATA_DATA_SECURITY_FROZEN_BIT                       ((UINT16)BIT3)
#define ATA_DATA_SECURITY_LOCKED_BIT                       ((UINT16)BIT2)
#define ATA_DATA_SECURITY_ENABLED_BIT                      ((UINT16)BIT1)
#define ATA_DATA_SECURITY_FEATURE_SET_BIT                  ((UINT16)BIT0)

#define ATA_PASSWORD_MAX_LENGTH                            32
///
/// Ata commands
///
#define ATA_SECURITY_SET_PASSWORD_CMD                         0xF1
#define ATA_SECURITY_UNLOCK_CMD                               0xF2
#define ATA_SECURITY_ERASE_PREPARE_CMD                        0xF3
#define ATA_SECURITY_ERASE_UNIT_CMD                           0xF4
#define ATA_SECURITY_DIS_PASSWORD_CMD                         0xF6

#define ATA_SECURITY_ERASE_UNIT_COMPARE_ADMIN_PASSWORD        0x0001
#define ATA_SECURITY_DISABLE_PASSWORD_COMPARE_ADMIN_PASSWORD  0x0001
#define ATA_SECURITY_ERASE_UNIT_COMPARE_USER_PASSWORD         0x0000
#define ATA_SECURITY_ERASE_UNIT_NORMAL_MODE                   0x0000
#define ATA_SECURITY_ERASE_UNIT_ENHANCED_MODE                 0x0002

#define ATA_SECURITY_SET_MASTER_PASSWORD                      0x0001
#define ATA_SECURITY_SET_MAXIMUM_SECURITY                     0x0100

#pragma pack(push,1)
typedef struct {
  UINT16                               EraseControldata;
  CHAR8                                Password[ATA_PASSWORD_MAX_LENGTH];
  UINT16                               Reserved[256 - 1 - (ATA_PASSWORD_MAX_LENGTH/2)];
} ATA_SECURE_ERASE_DATA_BLOCK;

typedef struct {
  UINT16                               ControlData;
  CHAR8                                Password[ATA_PASSWORD_MAX_LENGTH];
  UINT16                               MasterPasswordRevisionCode;
  UINT16                               Reserved[256 - 2 - (ATA_PASSWORD_MAX_LENGTH/2)];
} ATA_SET_PASSWORD_COMMAND_BLOCK;

typedef struct {
  UINT16                               ControlData;
  CHAR8                                Password[ATA_PASSWORD_MAX_LENGTH];
  UINT16                               Reserved[256 - 1 - (ATA_PASSWORD_MAX_LENGTH/2)];
} ATA_DISABLE_PASSWORD_COMMAND_BLOCK;

typedef struct {
  UINT16                               ControlData;
  CHAR8                                Password[ATA_PASSWORD_MAX_LENGTH];
  UINT16                               Reserved[256 - 1 - (ATA_PASSWORD_MAX_LENGTH/2)];
} ATA_UNLOCK_COMMAND_BLOCK;

#pragma pack(pop)

/**
  Searches device handles for EfiAtaPassThru protocol. If the protocol is found the function
  will cycle through all of the valid Ports and Port Multiplier Ports and erase the devices.

  @retval          EFI_SUCCESS         Nvme Device was erased successfully
  @retval          EFI_NOT_FOUND       No NvmExpressPassThru protocol found
  @retval          Others              An error occurred during Secure Erase operation
**/
EFI_STATUS
EraseAtaDevice (
  VOID
  );

#endif
