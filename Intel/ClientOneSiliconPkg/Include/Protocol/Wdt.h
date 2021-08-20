/** @file
  Watchdog Timer protocol

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
#ifndef _DXE_WDT_H_
#define _DXE_WDT_H_

//
// Extern the GUID for protocol users.
//
extern EFI_GUID               gWdtProtocolGuid;
//
// Forward reference for ANSI C compatibility
//
typedef struct _WDT_PROTOCOL  WDT_PROTOCOL;

/**
  Reloads WDT with new timeout value and starts it. Also sets Unexpected Reset bit, which
  causes the next reset to be treated as watchdog expiration - unless AllowKnownReset()
  function was called too.

  @param[in] TimeoutValue         Time in seconds before WDT times out. Supported range = 1 - 1024.

  @retval EFI_SUCCESS             if everything's OK
  @retval EFI_INVALID_PARAMETER   if TimeoutValue parameter is wrong
**/
typedef
EFI_STATUS
(EFIAPI *WDT_RELOAD_AND_START) (
  UINT32 TimeoutValue
  );

/**
  Returns WDT failure status.

  @retval V_PCH_OC_WDT_CTL_STATUS_FAILURE   If there was WDT expiration or unexpected reset
  @retval V_PCH_OC_WDT_CTL_STATUS_OK        Otherwise
**/
typedef
UINT8
(EFIAPI *WDT_CHECK_STATUS) (
  VOID
  );

/**
  Returns information if WDT coverage for the duration of BIOS execution
  was requested by an OS application.

  @retval TRUE                    if WDT was requested
  @retval FALSE                   if WDT was not requested
**/
typedef
UINT8
(EFIAPI *IS_WDT_REQUIRED) (
  VOID
  );

/**
  Returns WDT enabled/disabled status.

  @retval TRUE                    if WDT is enabled
  @retval FALSE                   if WDT is disabled
**/
typedef
UINT8
(EFIAPI *IS_WDT_ENABLED) (
  VOID
  );

/**
  Disables WDT timer.
**/
typedef
VOID
(EFIAPI *WDT_DISABLE) (
  VOID
  );

/**
  Normally, each reboot performed while watchdog runs is considered a failure.
  This function allows platform to perform expected reboots with WDT running,
  without being interpreted as failures.
  In DXE phase, it is enough to call this function any time before reset.
  In PEI phase, between calling this function and performing reset, ReloadAndStart()
  must not be called.
**/
typedef
VOID
(EFIAPI *WDT_ALLOW_KNOWN_RESET) (
  VOID
  );

/**
  These protocols and PPI allow a platform module to perform watch dog timer operations
  through the Intel PCH LPC Host Controller Interface. The WDT protocol and WDT PPI
  implement the Intel (R) Watch Dog timer for DXE, and PEI environments, respectively.
  WDT_PROTOCOL referenced hereafter represents both WDT_PROTOCOL and WDT_PPI, as they
  share the identical data structure.
**/
struct _WDT_PROTOCOL {
  WDT_RELOAD_AND_START  ReloadAndStart;   ///< Reloads WDT with new timeout value and starts it.
  WDT_CHECK_STATUS      CheckStatus;      ///< Returns WDT failure status.
  WDT_DISABLE           Disable;          ///< Disables WDT timer.
  WDT_ALLOW_KNOWN_RESET AllowKnownReset;  ///< Perform expected reboots with WDT running, without being interpreted as failures.
  IS_WDT_REQUIRED       IsWdtRequired;    ///< Returns information if WDT coverage for the duration of BIOS execution was requested by an OS application.
  IS_WDT_ENABLED        IsWdtEnabled;     ///< Returns WDT enabled/disabled status.
};

#endif
