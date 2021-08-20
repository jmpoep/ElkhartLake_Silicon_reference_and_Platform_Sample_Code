/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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

#include <PiDxe.h>
#include <SetupVariable.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/HeciProtocol.h>
#include <Protocol/AmtPolicy.h>
#include <AmtConfig.h>

#define AMT_MSG_DELAY                 2000000  ///< Show warning msg and stay for 2 seconds.

/**
  This is to display localized message in the console. This is
  used to display message strings in local language. To display
  the message, the routine will check the message ID and ConOut
  the message strings.

  @param[in] MsgId                Amt error message ID for displaying on screen message

**/
VOID
ShowAmtReportError (
  IN AMT_ERROR_MSG_ID              MsgId
  )
{
  gST->ConOut->ClearScreen (gST->ConOut);

  switch (MsgId) {
    case MSG_ASF_BOOT_DISK_MISSING:
      gST->ConOut->OutputString (gST->ConOut, L"Boot disk missing, please insert boot disk and press ENTER\r\n");
      break;

    case MSG_KVM_TIMES_UP:
      gST->ConOut->OutputString (gST->ConOut, L"Error!! Times up and the KVM session was cancelled!!");
      break;

    case MSG_KVM_REJECTED:
      gST->ConOut->OutputString (gST->ConOut, L"Error!! The request has rejected and the KVM session was cancelled!!");
      break;

    case MSG_KVM_WAIT:
      gST->ConOut->OutputString (gST->ConOut, L"Waiting Up to 8 Minutes For KVM FW.....");
      break;

    default:
      DEBUG ((DEBUG_ERROR, "This Message Id hasn't been defined yet, MsgId = %x\n", MsgId));
      break;
  }

  gBS->Stall (AMT_MSG_DELAY);
}

/**
  Install DxeAmtPolicy with setup values

  @param[in, out] DxeAmtPolicy  DXE Amt Policy

  @retval EFI_SUCCESS             Initialization complete.
  @retval EFI_UNSUPPORTED         The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
UpdateDxeAmtPolicy (
  IN OUT  AMT_POLICY_PROTOCOL   *DxeAmtPolicy
  )
{
  EFI_STATUS     Status;
  AMT_DXE_CONFIG *AmtDxeConfig;
  ME_SETUP       MeSetup;
  UINTN          Size;

  DEBUG ((DEBUG_INFO, "%a\n", __FUNCTION__));

  //
  // Get Amt configuration from Me Setup
  //
  Size = sizeof (ME_SETUP);
  Status = gRT->GetVariable (L"MeSetup", &gMeSetupVariableGuid, NULL, &Size, &MeSetup);

  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) DxeAmtPolicy, &gAmtDxeConfigGuid, (VOID *) &AmtDxeConfig);
    ASSERT_EFI_ERROR (Status);

    AmtDxeConfig->CiraRequest               = MeSetup.AmtCiraRequest;
    AmtDxeConfig->CiraTimeout               = MeSetup.AmtCiraTimeout;
    AmtDxeConfig->UnConfigureMe             = MeSetup.UnConfigureMe;
    AmtDxeConfig->HideUnConfigureMeConfirm  = MeSetup.HideUnConfigureMeConfirm;
    AmtDxeConfig->MebxDebugMsg              = MeSetup.MebxDebugMsg;
    AmtDxeConfig->UsbProvision              = MeSetup.UsbProvision;
    AmtDxeConfig->AmtbxSelectionScreen      = MeSetup.AmtbxSelectionScreen;
    AmtDxeConfig->AmtbxHotkeyPressed        = MeSetup.AmtbxHotKeyPressed;
    AmtDxeConfig->MebxNonUiTextMode         = MeSetup.MebxNonUiTextMode;
    AmtDxeConfig->MebxUiTextMode            = MeSetup.MebxUiTextMode;
    AmtDxeConfig->MebxGraphicsMode          = MeSetup.MebxGraphicsMode;

    AmtDxeConfig->AmtReportError            = ShowAmtReportError;
  }

  DEBUG ((DEBUG_INFO, "%a done\n", __FUNCTION__));
  return Status;
}
