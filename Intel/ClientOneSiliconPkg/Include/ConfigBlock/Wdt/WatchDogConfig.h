/** @file
  WatchDog policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#ifndef _WATCH_DOG_CONFIG_H_
#define _WATCH_DOG_CONFIG_H_

#define WATCH_DOG_PREMEM_CONFIG_REVISION 1
extern EFI_GUID gWatchDogPreMemConfigGuid;

#pragma pack (push,1)

/**
  This policy clears status bits and disable watchdog, then lock the
  WDT registers.
  while WDT is designed to be disabled and locked by Policy,
  bios should not enable WDT by WDT PPI. In such case, bios shows the
  warning message but not disable and lock WDT register to make sure
  WDT event trigger correctly.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;         ///< Config Block Header
  UINT32    DisableAndLock    :  1;     ///< <b>(Test)</b> Set 1 to clear WDT status, then disable and lock WDT registers. <b>0: Disable</b>; 1: Enable.
  UINT32    RsvdBits          : 31;
} PCH_WDT_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _WATCH_DOG_CONFIG_H_
