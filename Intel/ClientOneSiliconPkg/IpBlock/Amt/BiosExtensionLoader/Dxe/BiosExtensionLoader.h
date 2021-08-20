/** @file
  Include for AMT Bios Extentions Loader

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2019 Intel Corporation.

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
#ifndef _AMT_PTBX_H_
#define _AMT_PTBX_H_

#include <Protocol/MebxProtocol.h>

#define MEBX_RET_ACTION_CONTINUE_TO_BOOT  0x01
#define MEBX_RET_ACTION_RESET             0x04

#define MEBX_USER_ENTERED_RESPONSE        BIT1
#define MEBX_RA_SELECTION_MENU            BIT2
#define MEBX_HIDE_UNCONFIGURE_CONF_PROMPT BIT6
#define MEBX_DEBUG_MSG                    BIT14
#define MEBX_UNCONFIGURE                  BIT15

//
// MEBX Software Class DXE Subclass Progress Code definitions.
//
#define EFI_SW_DXE_MEBX_OPROM_DONE        (EFI_OEM_SPECIFIC | 0x00000000)
#define EFI_SW_DXE_MEBX_OTHER_UNSPECD     (EFI_OEM_SPECIFIC | 0x00000009)
#define EFI_SW_DXE_MEBX_RESET_ACTION      (EFI_OEM_SPECIFIC | 0x0000000a)

#define MEBX_VERSION                       0xF000      ///< for MEBx 15.0.0.0001 or later
#define MEBX_SETUP_PLATFORM_MNT_DEFAULT    MNT_OFF
#define MEBX_SETUP_SOL_DEFAULT             0

#define INVOKE_MEBX_BIT                    BIT3

/**
  Signal a event for Amt ready to boot.
**/
VOID
EFIAPI
MebxOnReadyToBoot (
  VOID
  );

/**
  Dump MEBx BIOS Params

  @param[in]   MebxBiosParams - MEBx BIOS params
**/
VOID
DxeMebxBiosParamsDebugDump (
  IN MEBX_BPF *MebxBiosParams
  );

#endif
