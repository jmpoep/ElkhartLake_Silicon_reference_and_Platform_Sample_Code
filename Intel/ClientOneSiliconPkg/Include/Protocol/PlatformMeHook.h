/** @file
  Interface definition details for platform hook support to ME module during DXE phase.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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
#ifndef _PLATFORM_ME_HOOK_H_
#define _PLATFORM_ME_HOOK_H_

///
/// ME Hook provided by platform for DXE phase
/// This protocol provides an interface to hook reference code by OEM.
///

#define PLATFORM_ME_HOOK_PROTOCOL_REVISION  1

/**
  Platform hook before BIOS sends Global Reset Heci Message to ME


  @retval EFI Status Code
**/
typedef
EFI_STATUS
(EFIAPI *PLATFORM_ME_HOOK_PRE_GLOBAL_RESET) (
  VOID
  )
;

///
/// Platform Intel ME Hook Protocol
/// This protocol provides an interface to hook reference code by OEM before perform reset command through Heci.
///
typedef struct _PLATFORM_ME_HOOK_PROTOCOL {
  ///
  /// Function pointer for the hook called before BIOS sends Global Reset Heci Message to ME
  ///
  PLATFORM_ME_HOOK_PRE_GLOBAL_RESET PreGlobalReset;
} PLATFORM_ME_HOOK_PROTOCOL;

extern EFI_GUID gPlatformMeHookProtocolGuid;

#endif
