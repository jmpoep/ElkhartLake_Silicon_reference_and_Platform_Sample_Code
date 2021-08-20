/** @file
  ME config block for DXE phase

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
#ifndef _ME_DXE_CONFIG_H_
#define _ME_DXE_CONFIG_H_

#define ME_DXE_CONFIG_REVISION 1
extern EFI_GUID gMeDxeConfigGuid;

#ifndef PLATFORM_POR
#define PLATFORM_POR  0
#endif
#ifndef FORCE_ENABLE
#define FORCE_ENABLE  1
#endif
#ifndef FORCE_DISABLE
#define FORCE_DISABLE 2
#endif

///
/// ME Error Message ID
///
typedef enum {
  MSG_EOP_ERROR             = 0,
  MSG_ME_FW_UPDATE_FAILED,
  MSG_HMRFPO_LOCK_FAILURE,
  MSG_HMRFPO_UNLOCK_FAILURE,
  MSG_ME_FW_UPDATE_WAIT,
  MSG_ILLEGAL_CPU_PLUGGED_IN,
  MSG_PLAT_DISABLE_WAIT,
  MAX_ME_ERROR_ENUM
} ME_ERROR_MSG_ID;

/**
  Show ME Error message. This is to display localized message in
  the console. This is used to display message strings in local
  language. To display the message, the routine will check the
  message ID and ConOut the message strings. For example, the
  End of Post error displayed in English will be:
  gST->ConOut->OutputString (gST->ConOut, L"Error sending End Of
  Post message to ME\n"); It is recommended to clear the screen
  before displaying the error message and keep the message on
  the screen for several seconds.
  A sample is provided, see ShowMeReportError () to retrieve
  details.

  @param[in] MsgId                ME error message ID for displaying on screen message

**/
typedef
VOID
(*ME_REPORT_ERROR) (
  IN ME_ERROR_MSG_ID              MsgId
  );

#pragma pack (push,1)

/**
  ME Dxe Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;              ///< Config Block Header
  UINT32 MeFwDownGrade                 : 1;  ///< <b>0: Disabled</b>; 1: Enabled - Enable/Disable ME FW downgrade
  UINT32 MeJhiSupport                  : 1;  ///< <b>0: Disabled</b>; 1: Enabled - Enable/Disable Intel DAL Host Interface Service.
  UINT32 CoreBiosDoneEnabled           : 1;  ///< 0: Disabled; <b>1: Enabled</b> - Enable/Disable Sending notification that BIOS is starting to run 3rd party code
  UINT32 ExtendMeMeasuredBoot          : 1;  ///< 0: Disabled; <b>1: Enabled</b> - Enable/Disable ME/CSME Extended Measurement to TPM-PCR
  UINT32 RsvdBits                      : 28; ///< Reserved for future use & Config block alignment

  /**
    Function pointer for displaying error message on screen
  **/
  ME_REPORT_ERROR MeReportError;
} ME_DXE_CONFIG;
#pragma pack (pop)

#endif // _ME_DXE_CONFIG_H_
