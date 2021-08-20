/** @file
  Dxe header for Overclocking

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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

#ifndef __DxeOverClock__H__
#define __DxeOverClock__H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <Protocol/IccOverClocking.h>
#include <Protocol/Wdt.h>
#include <Protocol/MemInfo.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <SetupVariable.h>
#include <PlatformBoardId.h>
#include <DxeOverClockLib.h>
#include <CpuAccess.h>

//
// Define function prototypes
//
#define AUTO            0
#define DISABLE_SUPPORT 0

#ifndef MDEPKG_NDEBUG
#define WDT_TIMEOUT_VALUE 16  // s
#else
#define WDT_TIMEOUT_VALUE 8  // s
#endif

// IGD registers definitions
#define GTT_MEM_ALIGN     22
#define GTTMMADR_SIZE_4MB 0x400000


/**

  @retval     EFI_SUCCESS
  @retval     EFI_NOT_FOUND
**/
EFI_STATUS
InitOCDefaultValues
(
  VOID
  );


/**

  @retval     EFI_SUCCESS
**/
EFI_STATUS
StoreDefaultPowerLimit2Value (
  VOID
  );


/**

  @retval     EFI_SUCCESS
**/
EFI_STATUS
RestoreDefaultHWValues (
  VOID
  );


/**
  Get current CPU BCLK settings, update setup variable and overclock BCLK.

  @retval     EFI_SUCCESS
**/
VOID
BclkSettings (
  VOID
  );


/**
  Updates memory timing setup variable with current MRC settings and then calls InitOcDefaults

  @param[in]  Event
  @param[in]  Context
**/
VOID
EFIAPI
GetCurrentMrcSettingsAndInitOcDefaults (
  IN  EFI_EVENT   Event,
  IN  VOID        *Context
  );

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
