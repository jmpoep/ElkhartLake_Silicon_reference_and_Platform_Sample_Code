/** @file
  System reset library services.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2007 - 2019 Intel Corporation.

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
#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/ResetSystemLib.h>
#include <Library/PmcLib.h>
#include <Library/BaseLib.h>
#include <Register/PchRegsLpc.h>
#include <Register/PmcRegs.h>

GLOBAL_REMOVE_IF_UNREFERENCED UINT16           mBaseResetSystemABase;

/**
  Calling this function causes a system-wide reset. This sets
  all circuitry within the system to its initial state. This type of reset
  is asynchronous to system operation and operates without regard to
  cycle boundaries.

  System reset should not return, if it returns, it means the system does
  not support cold reset.
**/
VOID
EFIAPI
ResetCold (
  VOID
  )
{
  IoWrite8 (R_PCH_IO_RST_CNT, V_PCH_IO_RST_CNT_FULLRESET);
}

/**
  Calling this function causes a system-wide initialization. The processors
  are set to their initial state, and pending cycles are not corrupted.

  System reset should not return, if it returns, it means the system does
  not support warm reset.
**/
VOID
EFIAPI
ResetWarm (
  VOID
  )
{
  IoWrite8 (R_PCH_IO_RST_CNT, V_PCH_IO_RST_CNT_HARDRESET);
}

/**
  Calling this function causes the system to enter a power state equivalent
  to the ACPI G2/S5 or G3 states.

  System shutdown should not return, if it returns, it means the system does
  not support shut down reset.
**/
VOID
EFIAPI
ResetShutdown (
  VOID
  )
{
  UINT16         ABase;
  UINT32         Data32;

  ABase = mBaseResetSystemABase;
  if (ABase == 0) {
    ABase = PmcGetAcpiBase ();
  }
  ///
  /// Firstly, GPE0_EN should be disabled to avoid any GPI waking up the system from S5
  ///
  IoWrite32 (ABase + R_ACPI_IO_GPE0_EN_127_96, 0);

  ///
  /// Secondly, PwrSts register must be cleared
  ///
  /// Write a "1" to bit[8] of power button status register at
  /// (PM_BASE + PM1_STS_OFFSET) to clear this bit
  ///
  IoWrite16 (ABase + R_ACPI_IO_PM1_STS, B_ACPI_IO_PM1_STS_PWRBTN);

  ///
  /// Finally, transform system into S5 sleep state
  ///
  Data32 = IoRead32 (ABase + R_ACPI_IO_PM1_CNT);

  Data32 = (UINT32) ((Data32 &~(B_ACPI_IO_PM1_CNT_SLP_TYP + B_ACPI_IO_PM1_CNT_SLP_EN)) | V_ACPI_IO_PM1_CNT_S5);

  IoWrite32 (ABase + R_ACPI_IO_PM1_CNT, Data32);

  Data32 = Data32 | B_ACPI_IO_PM1_CNT_SLP_EN;

  IoWrite32 (ABase + R_ACPI_IO_PM1_CNT, Data32);

  return;
}

/**
  Calling this function causes the system to enter a power state for platform specific.

  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.

**/
VOID
EFIAPI
ResetPlatformSpecific (
  IN UINTN            DataSize,
  IN VOID             *ResetData OPTIONAL
  )
{
  IoWrite8 (R_PCH_IO_RST_CNT, V_PCH_IO_RST_CNT_FULLRESET);
}

/**
  Calling this function causes the system to enter a power state for capsule update.

  Reset update should not return, if it returns, it means the system does
  not support capsule update.

**/
VOID
EFIAPI
EnterS3WithImmediateWake (
  VOID
  )
{
  //
  // In case there are pending capsules to process, need to flush the cache.
  //
  AsmWbinvd ();

  ResetWarm ();
  ASSERT (FALSE);
}

/**
  The library constructuor.

  The function does the necessary initialization work for this library instance.

  @retval     EFI_SUCCESS       The function always return EFI_SUCCESS for now.
**/
EFI_STATUS
EFIAPI
BaseResetSystemLibConstructor (
  VOID
  )
{
  mBaseResetSystemABase = PmcGetAcpiBase ();

  return EFI_SUCCESS;
}
