/** @file
  The PEI Library Implements OcWdt Support.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

@par Specification
**/

#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/Wdt.h>
#include <Library/WdtCommonLib.h>
#include <Library/PmcLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/IoLib.h>
#include <Register/PmcRegs.h>

static WDT_PPI mWdtPpi = {
  WdtReloadAndStart,
  WdtCheckStatus,
  WdtDisable,
  WdtAllowKnownReset,
  IsWdtRequired,
  IsWdtEnabled
};

static EFI_PEI_PPI_DESCRIPTOR  mInstallWdtPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gWdtPpiGuid,
  &mWdtPpi
};

/**
  Reads PCH registers to check if platform wakes from S3/S4

  @retval TRUE                    if platfrom wakes from S3/S4
  @retval FALSE                   otherwise
**/
BOOLEAN
IsWakeFromS3S4 (
  VOID
  )
{
  PMC_SLEEP_STATE  SleepType;

  SleepType = PmcGetSleepTypeAfterWake ();
  if ((SleepType == PmcS3SleepState) || (SleepType == PmcS4SleepState)) {
    return TRUE;
  }

  return FALSE;

}

/**
  Check for unexpected reset.
  If there was an unexpected reset, enforces WDT expiration.
**/
VOID
OcWdtResetCheck (
  VOID
  )
{
  UINT32      Readback;

  Readback = IoRead32 (WdtGetAddress ());
  DEBUG ((DEBUG_INFO, "(WDT) OcWdtResetCheck()\n"));

  ///
  /// If there was a WDT expiration, set Failure Status and clear timeout status bits
  /// Timeout status bits are cleared by writing '1'
  ///
  if (Readback & (B_ACPI_IO_OC_WDT_CTL_ICCSURV_STS | B_ACPI_IO_OC_WDT_CTL_NO_ICCSURV_STS)) {
    DEBUG ((DEBUG_ERROR, "(WDT) Expiration detected.\n", Readback));
    Readback |= B_ACPI_IO_OC_WDT_CTL_FAILURE_STS;
    Readback |= (B_ACPI_IO_OC_WDT_CTL_ICCSURV_STS | B_ACPI_IO_OC_WDT_CTL_NO_ICCSURV_STS);
    Readback &= ~(B_ACPI_IO_OC_WDT_CTL_UNXP_RESET_STS);
  } else {
    ///
    /// If there was unexpected reset but no WDT expiration and no resume from S3/S4,
    /// clear unexpected reset status and enforce expiration. This is to inform Firmware
    /// which has no access to unexpected reset status bit, that something went wrong.
    ///
    if ((Readback & B_ACPI_IO_OC_WDT_CTL_UNXP_RESET_STS) && !IsWakeFromS3S4()) {
#ifndef MDEPKG_NDEBUG
      DEBUG ((DEBUG_ERROR, "(WDT) Unexpected reset detected and ignored.\n"));
      Readback &= ~(B_ACPI_IO_OC_WDT_CTL_FAILURE_STS | B_ACPI_IO_OC_WDT_CTL_UNXP_RESET_STS);
      Readback |= (B_ACPI_IO_OC_WDT_CTL_ICCSURV_STS | B_ACPI_IO_OC_WDT_CTL_NO_ICCSURV_STS);
#else
      DEBUG ((DEBUG_ERROR, "(WDT) Unexpected reset detected. Enforcing Wdt expiration.\n"));
      WdtReloadAndStart (1);
      ///
      /// wait for reboot caused by WDT expiration
      ///
      CpuDeadLoop ();
#endif
    } else {
      ///
      /// No WDT expiration and no unexpected reset - clear Failure status
      ///
      DEBUG ((DEBUG_INFO, "(WDT) Status OK.\n", Readback));
      Readback &= ~(B_ACPI_IO_OC_WDT_CTL_FAILURE_STS);
      Readback |= (B_ACPI_IO_OC_WDT_CTL_ICCSURV_STS | B_ACPI_IO_OC_WDT_CTL_NO_ICCSURV_STS);
    }
  }

  IoWrite32 (WdtGetAddress (), Readback);

  return;
}

/**
  This function install WDT PPI

  @retval EFI_STATUS  Results of the installation of the WDT PPI
**/
EFI_STATUS
EFIAPI
OcWdtInit (
  VOID
  )
{
  EFI_STATUS  Status;
  WDT_PPI     *WdtPei;

  Status = PeiServicesLocatePpi (
             &gWdtPpiGuid,
             0,
             NULL,
             (VOID **) &WdtPei
             );
  if (EFI_ERROR (Status)) {
    Status = PeiServicesInstallPpi (&mInstallWdtPpi);
    ASSERT_EFI_ERROR (Status);
  } else {
    DEBUG ((DEBUG_INFO, "OCWDT PPI is already installed\n"));
  }

  return Status;
}

