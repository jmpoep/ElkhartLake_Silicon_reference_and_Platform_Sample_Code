/**@file

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
#ifndef _NVME_SECURE_ERASE_H_
#define _NVME_SECURE_ERASE_H_

#include <Protocol/NvmExpressPassthru.h>
#include <Protocol/PciIo.h>
#include <IndustryStandard/Pci22.h>
#include <IndustryStandard/Nvme.h>

#define NVME_GENERIC_TIMEOUT           EFI_TIMER_PERIOD_SECONDS (5)
#define NVME_FORMAT_NVM_CMD_TIMEOUT    EFI_TIMER_PERIOD_SECONDS (3600)

#define NVME_CONTROLLER_ID             0
#define NVME_ALL_NAMESPACES            0xFFFFFFFF

#define STONY_BEACH_V1_DEVICE_ID       0x2522
#define INTEL_VENDOR_ID                0x8086
#define STONY_BEACH_V1_MIN_SSID        0x3806
#define STONY_BEACH_V1_MAX_SSID        0x3807

//
// Format NVM Attributes
//
#define CRYPTOGRAPHIC_ERASE_SUPPORTED  BIT2

//
// NvmExpress Admin Format NVM Command
//
#define FORMAT_NVM_USER_DATA_ERASE     BIT0
#define FORMAT_NVM_CRYPTOGRAPHIC_ERASE BIT1

typedef enum {
  NoEraseMode,
  UserDataEraseMode,
  FullEraseMode
} SECURE_ERASE_MODE;

/**
  Searches device handles for NvmExpressPassThru protocol and erases devices
  which have this protocol installed.

  @retval          EFI_SUCCESS         Nvme Device was erased successfully
  @retval          EFI_NOT_FOUND       No NvmExpressPassThru protocol found
  @retval          Others              An error occurred during Secure Erase operataion
**/
EFI_STATUS
EraseNvmeDevice (
  VOID
  );

#endif
