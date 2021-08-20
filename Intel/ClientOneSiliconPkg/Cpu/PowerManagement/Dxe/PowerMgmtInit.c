/** @file
  Processor Power Management initialization code. This code determines current
  user configuration and modifies and loads ASL as well as initializing chipset
  and processor features to enable the proper power management.

  Acronyms:
  - PPM:  Processor Power Management
  - TM:   Thermal Monitor
  - IST:  Intel(R) Speedstep technology
  - HT:   Hyper-Threading Technology
  - ITBM: Intel(R) Turbo Boost Max Technology 3.0

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

#include "PowerMgmtInit.h"
#include <Protocol/CpuInfo.h>

//
// Global variables
//

GLOBAL_REMOVE_IF_UNREFERENCED CPU_NVS_AREA_PROTOCOL *gCpuNvsAreaProtocol = NULL;  ///< CPU GlobalNvs Protocol

//
// FVID Table Information
// Default FVID table
// One header field plus states
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT16     mNumberOfStates            = 0;
GLOBAL_REMOVE_IF_UNREFERENCED FVID_TABLE *mFvidPointer              = NULL;

//
// Globals to support updating ACPI Tables
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_TABLE_PROTOCOL     *mAcpiTable                = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mCpu0IstTable             = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mApIstTable               = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mCpu0CstTable             = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mApCstTable               = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mCpuSsdtTable             = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mCpu0TstTable             = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mApTstTable               = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mCpu0HwpTable             = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mApHwpTable               = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mItbmTable                = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mItbmSciTable             = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mCpu0PsdTable             = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_DESCRIPTION_HEADER *mApPsdTable               = NULL;

GLOBAL_REMOVE_IF_UNREFERENCED CPU_INIT_DATA_HOB           *mCpuInitDataHob            = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_CONFIG_DATA             *mCpuConfigData             = NULL;
/**
  Initialize the power management support.
  This function will do boot time configuration:
    Detect HW capabilities and SW configuration
    Initialize HW and software state (primarily MSR and ACPI tables)

  @param[in] ImageHandle  Pointer to the loaded image protocol for this driver
  @param[in] SystemTable  Pointer to the EFI System Table

  @retval EFI_SUCCESS     The driver installes/initialized correctly.
  @retval Driver will ASSERT in debug builds on error.  PPM functionality is considered critical for mobile systems.
**/
EFI_STATUS
EFIAPI
InitPowerManagement (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS                       Status;
  VOID                             *Hob;

  ///
  /// Get CPU Init Data Hob
  ///
  Hob = GetFirstGuidHob (&gCpuInitDataHobGuid);
  if (Hob == NULL) {
    DEBUG ((DEBUG_ERROR, "CPU Data HOB not available\n"));
    return EFI_NOT_FOUND;
  }
  mCpuInitDataHob   = (CPU_INIT_DATA_HOB *) ((UINTN) Hob + sizeof (EFI_HOB_GUID_TYPE));
  mCpuConfigData    = (CPU_CONFIG_DATA *) (UINTN) mCpuInitDataHob->CpuConfigData;
  ///
  /// Initialize the Global pointer for VID Table
  ///
  mFvidPointer         = (FVID_TABLE *)(UINTN)mCpuInitDataHob->FvidTable;

  ///
  /// Initialize Power management Global variables
  ///
  InitPowerManagementGlobalVariables ();

  /// Initialize CPU Power management code (Patch and install CPU ACPI tables, save S3 boot script info)
  ///
  Status = InitPpmDxe ();
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Initializes the platform power management global variable.
  This must be called prior to any of the functions being used.
**/
VOID
InitPowerManagementGlobalVariables (
  VOID
  )
{
  EFI_STATUS   Status;


  ///
  /// Locate CPU Nvs Protocol.
  ///
  Status = gBS->LocateProtocol (
                  &gCpuNvsAreaProtocolGuid,
                  NULL,
                  (VOID **) &gCpuNvsAreaProtocol
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "CPU GloableNvs protocol not found"));
  }
  ASSERT_EFI_ERROR (Status);
  if (gCpuNvsAreaProtocol != NULL) {
    gCpuNvsAreaProtocol->Area->Cpuid = GetCpuFamily () | GetCpuStepping ();
  }

  ///
  /// Locate ACPI table protocol
  ///
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &mAcpiTable);
  ASSERT_EFI_ERROR (Status);
  return;
}

/**
  Initialize the processor power management based on hardware capabilities
  and user configuration settings.

  @retval EFI_SUCCESS - on success
  @retval Appropiate failure code on error
**/
EFI_STATUS
InitPpmDxe (
  VOID
  )
{
  EFI_STATUS   Status;

  Status      = EFI_SUCCESS;

  ///
  /// Initialize PAIR Configuration
  ///
  InitPpmIrmConfiguration ();

  Status = InitCpuAcpiTable ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ///
  /// Initialise Miscellaneous features
  ///
  InitMiscFeatures ();

  return Status;
}
