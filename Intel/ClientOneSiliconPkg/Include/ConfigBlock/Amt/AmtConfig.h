/** @file
  AMT Config Block for PEI/DXE phase

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _AMT_CONFIG_H_
#define _AMT_CONFIG_H_

#include <Library/ConfigBlockLib.h>
#include <ConfigBlock.h>

#define AMT_PEI_CONFIG_REVISION 1
extern EFI_GUID gAmtPeiConfigGuid;

#define AMT_DXE_CONFIG_REVISION 1
extern EFI_GUID gAmtDxeConfigGuid;

///
/// AMT Error Message ID
///
typedef enum {
  MSG_ASF_BOOT_DISK_MISSING,
  MSG_KVM_TIMES_UP,
  MSG_KVM_REJECTED,
  MSG_KVM_WAIT,
  MAX_AMT_ERROR_ENUM
} AMT_ERROR_MSG_ID;

/**
  Show AMT Error message. This is to display localized message in
  the console. This is used to display message strings in local
  language. To display the message, the routine will check the
  message ID and ConOut the message strings. For example, the
  End of Post error displayed in English will be:
  gST->ConOut->OutputString (gST->ConOut, L"Error sending End Of
  Post message to ME\n"); It is recommended to clear the screen
  before displaying the error message and keep the message on
  the screen for several seconds.
  A sample is provided, see ShowAmtReportError () to retrieve
  details.

  @param[in] MsgId                AMT error message ID for displaying on screen message

**/
typedef
VOID
(*AMT_REPORT_ERROR) (
  IN AMT_ERROR_MSG_ID              MsgId
  );


#pragma pack (1)

/**
  AMT Pei Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                 ///< Config Block Header
  /**
    Enable or Disable Intel Active Management Technology feature.
    If disabled, all Intel AMT features, including Alert Standard Format features, will not be supported.
       0: Disable
    <b>1: Enable.</b>
  **/
  UINT32  AmtEnabled                      : 1;
  /**
    ME WatchDog timer feature. If disabled, below WatchDogTimerOs/WatchDogTimerBios will be irrelevant.
    See WatchDogTimerOs and WatchDogTimerBios description.
    <b>0: Disable</b>
       1: Enable ME WDT if corresponding timer value is not zero.
  **/
  UINT32  WatchDogEnabled                 : 1;
  UINT32  FwProgress                      : 1;  ///< PET Events Progress to receive PET Events. 0: Disable; <b>1: Enable</b>
  UINT32  ManageabilityMode               : 1;  ///< Manageability Mode sync with Mebx, 0: Disabled; <b>1: AMT</b>
  UINT32  AmtSolEnabled                   : 1;  ///< Serial Over Lan retrieved from Mebx. The default value depends on CSME/AMT. 0: Disable, <b>1: Enable</b>
  UINT32  RemoteAssistance                : 1;  ///< Remote Assistance is enabled if platform is provisioned.  <b>0: Disable</b>, 1: Enable
  UINT32  AmtKvmEnabled                   : 1;  ///< KVM retrieved from Mebx. The default value depends on CSME/AMT. 0: Disable, <b>1: Enable</b>
  UINT32  ForcMebxSyncUp                  : 1;  ///< <b>0: No</b>; 1: Force MEBX execution
  UINT32  RsvdBits                        : 24; ///< Reserved for future use & Config block alignment
  /**
    OS WatchDog Timer
    <b>0: Disable</b> OS WDT won't be started after stopping BIOS WDT even if WatchDogEnabled is 1.
    Non zero value - OS WDT will be started after stopping BIOS WDT if WatchDogEnabled is 1. The timer is set
    according to the value.
  **/
  UINT16  WatchDogTimerOs;
  /**
    BIOS WatchDog Timer
    <b>0: Disable</b> BIOS WDT won't be started even if WatchDogEnabled is 1.
    Non zero value - The BIOS WDT is set according to the value and started if WatchDogEnabled is 1.
  **/
  UINT16  WatchDogTimerBios;
} AMT_PEI_CONFIG;


/**
  AMT Dxe Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                 ///< Config Block Header
  UINT32  CiraRequest                     : 1;  ///< Trigger CIRA boot. <b>0: No CIRA request</b>; 1: Trigger CIRA request
  UINT32  UnConfigureMe                   : 1;  ///< OEMFlag Bit 15: Unconfigure ME with resetting MEBx password to default. <b>0: No</b>; 1: Un-configure ME without password
  UINT32  MebxDebugMsg                    : 1;  ///< OEMFlag Bit 14: Enable OEM debug menu in MEBx. <b>0: Disable</b>; 1: Enable
  UINT32  HideUnConfigureMeConfirm        : 1;  ///< OEMFlag Bit 6: Hide Unconfigure ME confirmation prompt when attempting ME unconfiguration. <b>0: Don't hide</b>; 1: Hide
  UINT32  UsbProvision                    : 1;  ///< Enable/Disable of AMT USB Provisioning. <b>0: Disable</b>; 1: Enable
  UINT32  AmtbxHotkeyPressed              : 1;  ///< OEMFlag Bit 1: Enable automatic MEBx hotkey press. <b>0: Disable</b>; 1: Enable
  /**
    OEMFlag Bit 2: Enable MEBx selection screen with 2 options:
    Press 1 to enter ME Configuration Screens
    Press 2 to initiate a remote connection
     - <b>0: Disabled</b>
     - 1: Enabled
  **/
  UINT32  AmtbxSelectionScreen            : 1;
  UINT32  RsvdBits                        : 25; ///< Reserved for future use & Config block alignment
  UINT32  CiraTimeout                     : 8;
  /**
    CPU Replacement Timeout
    <b>0: 10 seconds</b>
       1: 30 seconds
     2~5: Reserved
       6: No delay
       7: Unlimited delay
  **/
  UINT32  CpuReplacementTimeout           : 8;
  UINT32  MebxNonUiTextMode               : 4;  ///< Resolution for non-UI text mode. <b>0: Auto</b>; 1: 80x25; 2: 100x31
  UINT32  MebxUiTextMode                  : 4;  ///< Resolution for UI text mode. <b>0: Auto</b>; 1: 80x25; 2: 100x31
  UINT32  MebxGraphicsMode                : 4;  ///< Resolution for graphics mode. <b>0: Auto</b>; 1: 640x480; 2: 800x600; 3: 1024x768
  UINT32  OemResolutionSettingsRsvd       : 4;  ///< Reserved for future use & Config block alignment
  /**
    Function pointer for displaying error message on screen
  **/
  AMT_REPORT_ERROR  AmtReportError;
} AMT_DXE_CONFIG;

#pragma pack ()

#endif // _AMT_CONFIG_H_
