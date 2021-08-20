/** @file
  Implementation file for Watchdog Timer functionality

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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
#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <WatchDogConfig.h>
#include <Library/WdtCommonLib.h>
#include <Register/PmcRegs.h>
#include <Ppi/PlatformSpecificResetNotification.h>

VOID
EFIAPI
WdtResetNotificationCallback (
  IN EFI_RESET_TYPE     ResetType,
  IN EFI_STATUS         ResetStatus,
  IN UINTN              DataSize,
  IN VOID               *ResetData OPTIONAL
  );

/**
  This function register reset notify ppi with wdt in PEI

  @param[in]  PeiServices      Pointer to PEI Services Table.
  @param[in]  NotifyDescriptor Pointer to the descriptor for the Notification event that
                               caused this function to execute.
  @param[in]  Interface        Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS  The function completes successfully
  @retval     others

**/
EFI_STATUS
EFIAPI
ResetNotificationReadyCallBack (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Interface
  )
{
  EFI_STATUS                      Status;
  EFI_RESET_NOTIFICATION_PROTOCOL *ResetNotify;

  Status = PeiServicesLocatePpi (
            &gEdkiiPlatformSpecificResetNotificationPpiGuid,
            0,
            NULL,
            (VOID **) &ResetNotify
            );

  if (!EFI_ERROR(Status)) {
    ResetNotify->RegisterResetNotify (ResetNotify, WdtResetNotificationCallback);
  }
  return EFI_SUCCESS;
}

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_NOTIFY_DESCRIPTOR  mResetNotificationReady = {
  EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gEdkiiPlatformSpecificResetNotificationPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) ResetNotificationReadyCallBack
};

/**
  This runtine clears status bits and disable watchdog, then lock the
  WDT registers.
  while WDT is designed to be disabled and locked by policy,
  bios should not enable WDT by WDT PPI. In such case, bios shows the
  warning message but not disable and lock WDT register to make sure
  WDT event trigger correctly.

  @param[in] SiPreMemPolicyPpi         The Silicon PreMem Policy PPI instance
**/
VOID
WdtDisableAndLock (
  IN  SI_PREMEM_POLICY_PPI    *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                  Status;
  PCH_WDT_PREMEM_CONFIG       *WdtPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gWatchDogPreMemConfigGuid, (VOID *) &WdtPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  //
  // If WDT is enabled and DisableAndLock is set, then proceed with the lock
  //
  if (WdtPreMemConfig->DisableAndLock && IsWdtEnabled ()) {
    DEBUG ((DEBUG_INFO, "(WDT) Disable and Lock by policy request.\n"));
    //
    // clear status bits and disable watchdog, then lock the register
    //
    WdtDisable ();
    IoWrite32 (WdtGetAddress (), (B_ACPI_IO_OC_WDT_CTL_ICCSURV_STS | B_ACPI_IO_OC_WDT_CTL_NO_ICCSURV_STS));
    IoWrite32 (WdtGetAddress (), B_ACPI_IO_OC_WDT_CTL_LCK);
  }
}

/**
  Install PchResetCallback for WDT.
**/
VOID
WdtInstallResetCallback (
  VOID
  )
{
  UINT32      Readback;

  Readback = IoRead32 (WdtGetAddress ());

  DEBUG ((DEBUG_INFO, "(WDT) Readback = 0x%08x\n", Readback));

  PeiServicesNotifyPpi (&mResetNotificationReady);

}

/**
  Disable WDT when S3 resume before OS.
**/
VOID
WdtDisableBeforeS3Resume (
  VOID
  )
{
  EFI_STATUS    Status;
  EFI_BOOT_MODE BootMode;

  DEBUG ((DEBUG_INFO, "(WDT) WdtDisableBeforeS3Resume\n"));

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  //
  // We need to disable WDT on S3 resume because we cannot assume the OS WDT driver is
  // available. Also, if the system is resuming from S3, it is assumed the previous boot was stable.
  //
  if (BootMode == BOOT_ON_S3_RESUME) {
    WdtDisable ();
  }
}

/**
  WDT call back function for Reset notification.

  @param[in] ResetType            UEFI defined reset type.
  @param[in] ResetStatus          The status code for the reset.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.
**/
VOID
EFIAPI
WdtResetNotificationCallback (
  IN EFI_RESET_TYPE     ResetType,
  IN EFI_STATUS         ResetStatus,
  IN UINTN              DataSize,
  IN VOID               *ResetData OPTIONAL
  )
{
  WdtAllowKnownReset ();
}

