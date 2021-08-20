/** @file
  The implementation about Me ReadyToBootEvent for FSP support.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2020 Intel Corporation.

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

#include <Guid/EventGroup.h>
#include <Ppi/Wdt.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/PeiMeLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/HeciInitLib.h>
#include <Library/PmcPrivateLib.h>
#include "MeInit.h"
#include <PchResetPlatformSpecific.h>
#include <MeBiosPayloadHob.h>
#include <Library/BootMediaLib.h>
#include <Ppi/SiPolicy.h>

EFI_STATUS
EFIAPI
MeReadyToBootEventFsp (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  );

EFI_STATUS
EFIAPI
MeEndOfFirmwareEventFsp (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  );

STATIC EFI_PEI_NOTIFY_DESCRIPTOR  mMeReadyToBootNotifyList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK  | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiEventReadyToBootGuid,
    MeReadyToBootEventFsp
  }
};

STATIC EFI_PEI_NOTIFY_DESCRIPTOR  mMeEndOfFirmwareNotifyList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK  | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gFspEventEndOfFirmwareGuid,
    MeEndOfFirmwareEventFsp
  }
};

/**
  Send Optional Heci Command.
**/
VOID
SendOptionalHeciCommand (
  VOID
  )
{
  EFI_STATUS                Status;
  SI_POLICY_PPI             *SiPolicyPpi;
  ME_PEI_CONFIG             *MePeiConfig;
  ME_BIOS_PAYLOAD_HOB       *MbpHob;
  UINT32                    UnconfigOnRtcClear = 0;

  DEBUG ((DEBUG_INFO, "SendOptionalHeciCommand\n"));

  MbpHob      = NULL;
  SiPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Locate gSiPolicyPpiGuid fail. Status = %r\n", Status));
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gMePeiConfigGuid, (VOID *) &MePeiConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Get ME PeiConfigBlock fail, Status = %r\n", Status));
    return;
  }

  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob != NULL) {
    DEBUG ((DEBUG_INFO, "MbpHob NOT NULL\n"));

    if (MbpHob->MeBiosPayload.UnconfigOnRtcClearState.Available == 1) {
      UnconfigOnRtcClear = MbpHob->MeBiosPayload.UnconfigOnRtcClearState.UnconfigOnRtcClearData.DisUnconfigOnRtcClearState;
      if ((MePeiConfig->MeUnconfigOnRtcClear == 1) && (UnconfigOnRtcClear == DisableState)) {
        UnconfigOnRtcClear = EnableState;
        PeiHeciSetUnconfigOnRtcClearDisableMsg (UnconfigOnRtcClear);
      } else if ((MePeiConfig->MeUnconfigOnRtcClear == 0) && (UnconfigOnRtcClear == EnableState)) {
        UnconfigOnRtcClear = DisableState;
        PeiHeciSetUnconfigOnRtcClearDisableMsg (UnconfigOnRtcClear);
      }
    }
  }
}

/**
  The notification registered as a callback to perform Me event prior to boot

  @param[in]  PeiServices         An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation
  @param[in]  NotifyDescriptor    Address of the notification descriptor data structure.
  @param[in]  Ppi                 Address of the PPI that was installed.

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    No enough buffer to allocate
**/
EFI_STATUS
EFIAPI
MeReadyToBootEventFsp (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  )
{
  EFI_STATUS                      Status;
  WDT_PPI                         *Wdt;
  UINT32                          RequestedActions;
  PCH_RESET_DATA                  ResetData;
  ME_BIOS_BOOT_PATH               MeBiosPath;
  BOOLEAN                         MeDisable;

  MeDisable = FALSE;
  MeBiosPath = CheckMeBootPath ();
  switch (MeBiosPath) {
    case SecoverJmprPath:
    case SecoverMeiMsgPath:
    case SwTempDisablePath:
      ///
      /// If ME is running in those ME-BIOS paths - hide HECI1 prior to boot
      ///
      MeDisable = TRUE;
      break;

    case NormalPath:
    case RecoveryPath:
    case ErrorPath:
      ///
      /// Send EoP message - this is crucial for platform security
      ///
      if (GetBootModeHob () == BOOT_ON_S3_RESUME) {
        break;
      }
      if (MeEndOfPostEnabled ()) {
      if (MeBiosPath == NormalPath) {
        if (BootMediaIsUfs ()) {
          SendOptionalHeciCommand ();
        }
      }
        RequestedActions = HeciEopStatusSuccess;
        Status = MeEndOfPostEvent (&RequestedActions);
        MeSetEndOfPostDone ();
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_ERROR, "MeEndOfPostEvent failed with Status = %r\n", Status));
        } else if (RequestedActions == HeciEopPerformGlobalReset) {
          ///
          /// Locate WDT PPI for access to Wdt->AllowKnownReset()
          ///
          Status = PeiServicesLocatePpi (
                     &gWdtPpiGuid,
                     0,
                     NULL,
                     (VOID **) &Wdt
                     );
          if (!EFI_ERROR (Status)) {
            Wdt->AllowKnownReset ();
          }
          DEBUG ((DEBUG_INFO, "%a - Global Reset requested by FW EOP ACK %r\n", __FUNCTION__, Status));
          CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
          StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
          (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetPlatformSpecific, EFI_SUCCESS, sizeof (PCH_RESET_DATA), &ResetData);
        }
      }
      break;
    default:
      ///
      /// In other ME-BIOS paths HECI1 has already been disabled in PEI Post Mem
      ///
      break;
  }

  ///
  /// PMIR Configuration & FDSW Lockdown
  ///
  LockConfig ();

  ///
  /// If ME policy is set to disabled, then hide MEI1 prior to boot
  ///
  if (MeDisable) {
    SetD0I3Bit (HECI1);
  }
  PmcDisableMeDevices (MeDisable);

  return EFI_SUCCESS;
}

/**
  The notification registered as a callback to perform Me EndOfFirmware event prior to boot.

  @param[in]  PeiServices         An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation
  @param[in]  NotifyDescriptor    Address of the notification descriptor data structure.
  @param[in]  Ppi                 Address of the PPI that was installed.

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
EFIAPI
MeEndOfFirmwareEventFsp (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  )
{
  UINT32 HeciBars[PCI_MAX_BAR];
  UINT8  MeDevFunction;

  ///
  /// Don't set D0I3 if disabled by policy
  ///
  if (MeHeciD0I3Enabled () == FALSE) {
    DEBUG ((DEBUG_INFO, "MeEndOfFirmwareEventFsp - SKIP setting D0I3 bits for HECI devices on boot time\n"));
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "MeEndOfFirmwareEventFsp - setting D0I3 bits for HECI devices on boot time\n"));

  //
  // 1. Save MMIO BAR addresses for all HECI devices.
  // 2. Set to default (32-bit) BAR addresses for all HECI devices.
  // 3. Set D0i3 bit
  // 4. Restore MMIO BAR addresses for all HECI devices.
  //
  for (MeDevFunction = HECI1; MeDevFunction <= HECI4; MeDevFunction++) {
    if (!IsHeciDeviceFunction (MeDevFunction)) {
      continue;
    }
    MeSaveBars (MeDevFunction, HeciBars);
    MeDeviceInit (MeDevFunction, PcdGet32 (PcdSiliconInitTempMemBaseAddr), 0);
    SetD0I3Bit (MeDevFunction);
    MeRestoreBars (MeDevFunction, HeciBars);
  }

  return EFI_SUCCESS;
}

/**
  FSP HeciInit Module Entry Point for signal ReadyToBoot FSP event

  @param[in] FileHandle           PEIM's file handle
  @param[in] PeiServices          An indirect pointer to the EFI_PEI_SERVICES table published by
                                  the PEI Foundation

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
MeInitEntryPointFsp (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO, "Fsp MeInitEntryPointFsp() Start\n"));

  Status = PeiServicesNotifyPpi (mMeReadyToBootNotifyList);
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesNotifyPpi (mMeEndOfFirmwareNotifyList);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "Fsp MeInitEntryPointFsp() End\n"));

  return Status;
}
