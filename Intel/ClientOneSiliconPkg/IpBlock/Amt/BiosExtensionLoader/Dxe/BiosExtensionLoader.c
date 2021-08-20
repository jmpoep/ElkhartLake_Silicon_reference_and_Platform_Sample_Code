/** @file
  Loads the AMT Bios Extensions and calls the module prior to boot.
  Setup options control whether the user is allowed to change the provisioning of AMT
  or not for boot speed optimization.

  Configuration and invocation of the AMT Bios Extensions is done as per
  the AMT Bios Writers Guide.

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

#include <Library/HobLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PerformanceLib.h>
#include <Library/PostCodeLib.h>
#include <MebxDataHob.h>
#include <Protocol/AmtReadyToBoot.h>
#include <Protocol/AmtSaveMebxProtocol.h>
#include <Library/DxeMeLib.h>
#include <Library/DxeAmtHeciLib.h>
#include <Library/DxeAmtPolicyLib.h>
#include <AmtConfig.h>
#include <AsfMsgs.h>
#include <MeBiosPayloadHob.h>
#include "UsbProvision.h"
#include "BiosExtensionLoader.h"

GLOBAL_REMOVE_IF_UNREFERENCED AMT_READY_TO_BOOT_PROTOCOL mAmtReadyToBoot = {
  AMT_READY_TO_BOOT_PROTOCOL_REVISION,
  MebxOnReadyToBoot
};

/**
  Print Mebx Data
**/
VOID
PrintMebxData (
  VOID
  )
{
  EFI_HOB_GUID_TYPE    *GuidHob;
  MEBX_DATA_HOB        *MebxData;

  GuidHob  = NULL;
  MebxData = NULL;

  GuidHob = GetFirstGuidHob (&gAmtMebxDataGuid);
  if (GuidHob != NULL) {
    MebxData = (MEBX_DATA_HOB *) GET_GUID_HOB_DATA (GuidHob);
  }
  if (MebxData == NULL) {
    return;
  }
  DEBUG ((DEBUG_INFO, "\n------------------------ Mebx Data Print Begin -----------------\n"));
  DEBUG ((DEBUG_INFO, " PlatformMngSel                      : 0x%x\n", MebxData->PlatformMngSel));
  DEBUG ((DEBUG_INFO, " AmtSol                              : 0x%x\n", MebxData->AmtSol));
  DEBUG ((DEBUG_INFO, " RemoteAssistanceTriggerAvailablilty : 0x%x\n", MebxData->RemoteAssistanceTriggerAvailablilty));
  DEBUG ((DEBUG_INFO, " KvmEnable                           : 0x%x\n", MebxData->KvmEnable));
  DEBUG ((DEBUG_INFO, "\n------------------------ Mebx Data Print End -------------------\n"));
  return;
}

/**
  Checks MEBx invocation reasons.

  @param[in] MebxBiosParamsBuffer MebxBiosParams Flat pointer
  @param[in] IsForceSyncUp        ForcMebxSyncUp is enabled or disabled.

  @retval TRUE                    MEBx has been invoked
  @retval FALSE                   MEBx has not been invoked
**/
BOOLEAN
IsMebxInvoked (
  IN  MEBX_BPF    *MebxBiosParams,
  IN  BOOLEAN     IsForceSyncUp
  )
{
  ///
  /// Check for Firmware invocation
  ///
  if (PciSegmentRead8 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS_2)) & INVOKE_MEBX_BIT) {
    DEBUG ((DEBUG_INFO, "InvokeMebx Reaseon = Firmware Request\n"));
    return TRUE;
  }
  ///
  /// Check for BIOS invocation
  ///
  if (MebxBiosParams->OemFlags & MEBX_USER_ENTERED_RESPONSE) {
    DEBUG ((DEBUG_INFO, "InvokeMebx Reason = MEBX_USER_ENTERED_RESPONSE\n"));
    return TRUE;
  }

  if (MebxBiosParams->OemFlags & MEBX_UNCONFIGURE) {
    DEBUG ((DEBUG_INFO, "InvokeMebx Reason = MEBX_UNCONFIGURE\n"));
    return TRUE;
  }

  if (MebxBiosParams->UsbProvisionData) {
    DEBUG ((DEBUG_INFO, "InvokeMebx Reason = USB provision requested\n"));
    return TRUE;
  }

  if (MebxBiosParams->ActiveRemoteAssistanceProcess) {
    DEBUG ((DEBUG_INFO, "InvokeMebx Reason = ActiveRemoteAssistanceProcess\n"));
    return TRUE;
  }

  if (IsForceSyncUp) {
    DEBUG ((DEBUG_INFO, "InvokeMebx Reason = forcing ME-BIOS sync-up\n"));
    return TRUE;
  }
  return FALSE;
}

/**
  Detect EFI MEBx support; Loading and execution.

  @param[in] IsAsfWatchDogEnabled ASF WatchDogEnabled flag
  @param[in] MebxBiosParamsBuffer MebxBiosParams Flat pointer

  @retval EFI_SUCCESS             Function executed successfully.
  @retval EFI_NOT_STARTED         MEBx not started.
**/
EFI_STATUS
AdjustAndExecuteMebxImage (
  IN BOOLEAN  IsAsfWatchDogEnabled,
  IN MEBX_BPF *MebxBiosParams
  )
{
  EFI_STATUS             Status;
  MEBX_PROTOCOL          *MebxProtocol;
  MEBX_EXIT_CODE         MebxExitCode;

  ZeroMem (&MebxExitCode, sizeof (MEBX_EXIT_CODE));

  DEBUG ((DEBUG_INFO, "Calling MEBx\n"));

  ///
  /// Whenever the user gets into setup screens like BIOS setup, MEBX, or PXE,
  /// the BIOS should stop the watchdog and restart it when user exits the setup
  /// screens, otherwise the watchdog will expire in the case where the user enters the
  /// setup screen and does not dismiss it within the watchdog timer interval.
  /// Stop ASF BIOS watchdog timer if the corresponding option policy is true with the
  /// non-zero value in the BIOS timeout setting
  ///
  if (IsAsfWatchDogEnabled == TRUE) {
    AsfStopWatchDog ();
  }

  ///
  /// Locate MEBX protocol
  ///
  Status = gBS->LocateProtocol (&gMebxProtocolGuid, NULL, (VOID **) &MebxProtocol);
  if (!EFI_ERROR (Status)) {
    DEBUG_CODE_BEGIN ();
    ///
    /// Dump MebxBiosParams before launching MEBx
    ///
    DxeMebxBiosParamsDebugDump (MebxBiosParams);
    DEBUG_CODE_END ();

    DEBUG ((DEBUG_INFO, "ME-BIOS: MEBx Core Entry.\n"));
    PostCode (0xE07);

    MebxProtocol->CoreMebxEntry (MebxBiosParams, &MebxExitCode);

    DEBUG ((DEBUG_INFO, "ME-BIOS: MEBx Core Exit - Success.\n"));
    PostCode (0xE27);
  }

  ///
  /// Re-Start ASF Watch Dog after exiting MEBx Setup
  ///
  if (IsAsfWatchDogEnabled == TRUE) {
    AsfStartWatchDog (ASF_START_BIOS_WDT);
  }

  DEBUG ((DEBUG_INFO, "MEBx return BIOS_CMD_DATA:%x, BIOS_CMD:%x\n", MebxExitCode.BiosCmdData, MebxExitCode.BiosCmd));
  DEBUG ((DEBUG_INFO, "MEBx return MEBX_STATUS_CODE:%x\n", MebxExitCode.MebxStatusCode));

  switch (MebxExitCode.BiosCmd) {
    ///
    /// mask off reserved bits 3-7 from mebx exit status code
    ///
    case MEBX_RET_ACTION_CONTINUE_TO_BOOT:
      REPORT_STATUS_CODE (EFI_PROGRESS_CODE, EFI_SOFTWARE_UNSPECIFIED | EFI_SW_DXE_MEBX_OPROM_DONE);
      break;

    case MEBX_RET_ACTION_RESET:
      REPORT_STATUS_CODE (EFI_ERROR_CODE, EFI_SOFTWARE_UNSPECIFIED | EFI_SW_DXE_MEBX_RESET_ACTION);
      DEBUG ((DEBUG_INFO, "MEBx requires Global Reset.\n"));
      HeciSendCbmResetRequest (CBM_RR_REQ_ORIGIN_MEBX, CBM_HRR_GLOBAL_RESET);
      CpuDeadLoop ();
      break;

    default:
      REPORT_STATUS_CODE (EFI_ERROR_CODE, EFI_SOFTWARE_UNSPECIFIED | EFI_SW_DXE_MEBX_OTHER_UNSPECD);
      Status = EFI_NOT_STARTED;
      break;
  }

  ///
  /// Send PET Alert Message
  ///
  /// BIOS Specific Code
  ///
  /// Indicate OS BOOT handoff so that PET/ASF Push msg can be sent out to indicate
  /// all done now booting os.
  ///
  REPORT_STATUS_CODE (EFI_PROGRESS_CODE, EFI_SOFTWARE_UNSPECIFIED | EFI_SW_DXE_BS_PC_LEGACY_BOOT_EVENT);

  return Status;
}

/**
  This routine is run at boot time.
  1) Initialize MEBx data.
  2) Check USB provision.
  3) Build and send asset tables to ME FW.
  4) Check if MEBx is required to be launched by user.

**/
VOID
MebxNotifyEvent (
  VOID
  )
{
  EFI_STATUS                                    Status;
  MEBX_BPF                                      MebxBiosParams;
  AMT_SAVE_MEBX_PROTOCOL                        *AmtSaveMebx;
  EFI_HOB_GUID_TYPE                             *GuidHob;
  MEBX_DATA_HOB                                 MebxData;
  AMT_POLICY_PROTOCOL                           *AmtPolicy;
  AMT_DXE_CONFIG                                *AmtDxeConfig;
  AMT_PEI_CONFIG                                *AmtPeiConfig;
  BOOLEAN                                       FirstBoot;
  BOOLEAN                                       IsForceSyncUp;
  BOOLEAN                                       IsUsbProvisionEnabled;
  BOOLEAN                                       IsAmtBiosSupport;
  BOOLEAN                                       IsAsfWatchDogEnabled;
  PROVISION_RECORD_HANDLE                       ProvisionRecord;

  DEBUG ((DEBUG_INFO, "Entering BiosExtensionLoader Driver\n"));
  FirstBoot                 = FALSE;
  GuidHob                   = NULL;
  IsUsbProvisionEnabled     = FALSE;
  IsForceSyncUp             = FALSE;
  IsAmtBiosSupport          = FALSE;
  IsAsfWatchDogEnabled      = FALSE;

  GuidHob = GetFirstGuidHob (&gAmtPolicyHobGuid);
  if (GuidHob != NULL) {
    AmtPeiConfig = (AMT_PEI_CONFIG *) GET_GUID_HOB_DATA (GuidHob);
    IsForceSyncUp        = (BOOLEAN) AmtPeiConfig->ForcMebxSyncUp;
    IsAmtBiosSupport     = (BOOLEAN) AmtPeiConfig->AmtEnabled;
    IsAsfWatchDogEnabled = (BOOLEAN) AmtPeiConfig->WatchDogEnabled;
  }

  GuidHob = GetFirstGuidHob (&gAmtMebxDataGuid);
  if (GuidHob != NULL) {
    CopyMem (&MebxData, GET_GUID_HOB_DATA (GuidHob), sizeof (MEBX_DATA_HOB));
  }

  if ((GuidHob == NULL) || IsForceSyncUp) {
    DEBUG ((DEBUG_WARN, "MebxData Hob does not exist: create with default values\n"));
    ///
    /// Create the variable when it does not exist
    ///
    FirstBoot                                    = TRUE;
    MebxData.PlatformMngSel                      = MEBX_SETUP_PLATFORM_MNT_DEFAULT;
    MebxData.AmtSol                              = MEBX_SETUP_SOL_DEFAULT;
    MebxData.RemoteAssistanceTriggerAvailablilty = 0;
    MebxData.KvmEnable                           = 0;

    Status = gBS->LocateProtocol (&gAmtSaveMebxProtocolGuid, NULL, (VOID **) &AmtSaveMebx);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Platform must implement this function to save Mebx setting\n"));
      ASSERT_EFI_ERROR (Status);
    } else {
      Status = AmtSaveMebx->SaveMebx (sizeof (MEBX_DATA_HOB), (VOID *) &MebxData);
      ASSERT_EFI_ERROR (Status);
    }
  }

  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "Mebx data before calling MEBx:\n"));
  PrintMebxData ();
  DEBUG_CODE_END ();

  ZeroMem (&MebxBiosParams, sizeof (MEBX_BPF));
  MebxBiosParams.BpfVersion = MEBX_VERSION;

  Status = gBS->LocateProtocol (&gDxeAmtPolicyGuid, NULL, (VOID **) &AmtPolicy);
  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) AmtPolicy, &gAmtDxeConfigGuid, (VOID *) &AmtDxeConfig);
    ASSERT_EFI_ERROR (Status);

    MebxBiosParams.CpuReplacementTimeout                   = (UINT8)(UINTN) AmtDxeConfig->CpuReplacementTimeout;

    ///
    /// Pass OEM MEBx resolution settings through BPF
    ///
    MebxBiosParams.OemResolutionSettings.MebxGraphicsMode  = (UINT16)(UINTN) AmtDxeConfig->MebxGraphicsMode;
    MebxBiosParams.OemResolutionSettings.MebxNonUiTextMode = (UINT16)(UINTN) AmtDxeConfig->MebxNonUiTextMode;
    MebxBiosParams.OemResolutionSettings.MebxUiTextMode    = (UINT16)(UINTN) AmtDxeConfig->MebxUiTextMode;

    IsUsbProvisionEnabled                                  = IsAmtBiosSupport && AmtDxeConfig->UsbProvision;

    ///
    /// Setup CIRA data
    ///
    if (AmtDxeConfig->CiraRequest == 1) {
      MebxBiosParams.ActiveRemoteAssistanceProcess = 1;
      MebxBiosParams.CiraTimeout                   = (UINT8) AmtDxeConfig->CiraTimeout;
    }

    ///
    /// Check for OEM Flags presence
    ///
    if (AmtDxeConfig->AmtbxHotkeyPressed == 1) {
      MebxBiosParams.OemFlags |= MEBX_USER_ENTERED_RESPONSE;
    }
    if (AmtDxeConfig->AmtbxSelectionScreen == 1) {
      MebxBiosParams.OemFlags |= MEBX_RA_SELECTION_MENU;
    }
    if (AmtDxeConfig->UnConfigureMe == 1) {
      MebxBiosParams.OemFlags |= MEBX_UNCONFIGURE;
    }
    if (AmtDxeConfig->HideUnConfigureMeConfirm == 1) {
      MebxBiosParams.OemFlags |= MEBX_HIDE_UNCONFIGURE_CONF_PROMPT;
    }
    if (AmtDxeConfig->MebxDebugMsg == 1) {
      MebxBiosParams.OemFlags |= MEBX_DEBUG_MSG;
    }
  }

  if (FirstBoot == TRUE) {
    MebxBiosParams.MebxDefaultSol = 1;
  }

  if (IsUsbProvisionEnabled) {
    if (GetUsbProvisionRecord (&ProvisionRecord)) {
      MebxBiosParams.UsbProvisionData = (UINT32) (UINTN) AllocateZeroPool (sizeof (USB_PROVISION_HEADER) + ProvisionRecord.ProvisionRecordSize);
      ASSERT ((VOID*) (UINTN) MebxBiosParams.UsbProvisionData != NULL);
      CopyMem (
        (VOID *) (MebxBiosParams.UsbProvisionData + sizeof (USB_PROVISION_HEADER)),
        ProvisionRecord.ProvisionRecordBuffer,
        ProvisionRecord.ProvisionRecordSize
        );
    }
  }

  if (IsMebxInvoked (&MebxBiosParams, IsForceSyncUp)) {
    PERF_START_EX (NULL, "EventRec", NULL, AsmReadTsc (), 0x8000);
    Status = AdjustAndExecuteMebxImage (IsAsfWatchDogEnabled, &MebxBiosParams);
    PERF_END_EX (NULL, "EventRec", NULL, AsmReadTsc (), 0x8001);
  }

  //
  // We remove the provision record after MEBx invocation
  // to account for the case when MEBx didn't consume the record
  // correctly. In such a case data record won't be removed.
  // MEBx returns information about data record successfull consumption
  // by directly modyfing data record buffer passed to it in MebxBiosParams
  //
  if (IsUsbProvisionEnabled) {
    RemoveUsbProvisionRecord (&ProvisionRecord, (VOID*) (MebxBiosParams.UsbProvisionData + sizeof (USB_PROVISION_HEADER)));
  }
}

/**
  Signal an event for Amt ready to boot.
**/
VOID
EFIAPI
MebxOnReadyToBoot (
  VOID
  )
{
  static BOOLEAN       MebxLaunched = FALSE;
  EFI_HOB_GUID_TYPE    *GuidHob;
  AMT_PEI_CONFIG       *AmtPeiConfig;
  BOOLEAN              IsAsfWatchDogEnabled;

  ///
  /// only launch MEBx once during POST
  ///
  if (MebxLaunched) {
    return;
  }

  MebxLaunched         = TRUE;
  IsAsfWatchDogEnabled = FALSE;
  GuidHob = GetFirstGuidHob (&gAmtPolicyHobGuid);
  if (GuidHob != NULL) {
    AmtPeiConfig = (AMT_PEI_CONFIG *) GET_GUID_HOB_DATA (GuidHob);
    IsAsfWatchDogEnabled = (BOOLEAN) AmtPeiConfig->WatchDogEnabled;
  }

  ///
  /// Launch MEBx, do not assert on error as this may be valid case
  ///
  MebxNotifyEvent ();

  if (IsAsfWatchDogEnabled) {
    ///
    /// In the end of Ready To Boot phase (before sending End Of Post message),
    /// when BIOS is about to pass control to OS load, BIOS should stop
    /// the watchdog to avoid false watchdog expiration
    ///
    AsfStopWatchDog ();
    ///
    /// Start ASF OS watchdog timer if the corresponding option policy is true
    /// with the non-zero value in the OS timeout setting
    ///
    AsfStartWatchDog (ASF_START_OS_WDT);
  }
}

/**
  The driver entry point - MEBx Driver main body.

  @param[in] ImageHandle          Handle for this drivers loaded image protocol.
  @param[in] SystemTable          EFI system table.

  @retval EFI_SUCCESS             The driver installed without error.
  @retval EFI_UNSUPPORTED         The chipset is unsupported by this driver.
**/
EFI_STATUS
EFIAPI
MebxDriverEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS            Status;
  HECI_PROTOCOL         *Heci;
  UINT32                MeMode;
  EFI_HANDLE            Handle;
  ME_BIOS_PAYLOAD_HOB   *MbpHob;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Heci->GetMeMode (&MeMode);
  if (MeMode != ME_MODE_NORMAL) {
    return EFI_UNSUPPORTED;
  }

  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob == NULL) {
    DEBUG ((DEBUG_ERROR, "No MBP Data Protocol available\n"));
    return EFI_UNSUPPORTED;
  }

  if (MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType != IntelMeCorporateFw) {
    return EFI_UNSUPPORTED;
  }

  ///
  /// If it is corporate SKU, BIOS must stop ASF BIOS watchdog timer when normal POST after DID message.
  /// The reason is because BIOS doesn't know what the state of ASF BIOS watchdog timer was in the previous boot.
  /// Start BIOS Watchdog only if Watchdog Timer is enabled.
  ///
  AsfStopWatchDog ();

  ///
  /// Install an Amt ready to boot protocol.
  ///
  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gAmtReadyToBootProtocolGuid,
                  &mAmtReadyToBoot,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
