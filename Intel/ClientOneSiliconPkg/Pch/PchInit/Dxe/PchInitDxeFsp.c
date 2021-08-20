/** @file
  This is the Uefi driver that initializes the Intel PCH.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include "PchInit.h"

/**
  This is the callback function for PCI ENUMERATION COMPLETE.
**/
VOID
EFIAPI
PchOnPciEnumComplete (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS          Status;
  VOID                *ProtocolPointer;

  ///
  /// Check if this is first time called by EfiCreateProtocolNotifyEvent() or not,
  /// if it is, we will skip it until real event is triggered
  ///
  Status = gBS->LocateProtocol (&gEfiPciEnumerationCompleteProtocolGuid, NULL, (VOID **) &ProtocolPointer);
  if (EFI_SUCCESS != Status) {
    return;
  }
  gBS->CloseEvent (Event);

  PchOnPciEnumCompleteCommon ();
}
/**
  <b>PchInit DXE Module Entry Point</b>\n
  - <b>Introduction</b>\n
      The PchInit module is a DXE driver that initializes the Intel Platform Controller Hub
      following the PCH BIOS specification and EDS requirements and recommendations. It consumes
      the PCH_POLICY_HOB SI_POLICY_HOB for expected configurations per policy.
      This is the standard EFI driver point that detects whether there is an supported PCH in
      the system and if so, initializes the chipset.

  - <b>Details</b>\n
    This module is required for initializing the Intel Platform Controller Hub to
    follow the PCH BIOS specification and EDS.
    This includes some initialization sequences, enabling and disabling PCH devices,
    configuring clock gating, RST PCIe Storage Remapping, SATA controller, ASPM of PCIE devices. Right before end of DXE,
    it's responsible to lock down registers for security requirement.

  - @pre
    - PCH PCR base address configured
    - EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL
      - This is to ensure that PCI MMIO and IO resource has been prepared and available for this driver to allocate.

  - @result
    - Publishes the @link _PCH_INFO_PROTOCOL PCH_INFO_PROTOCOL @endlink
    - Publishes the @link _PCH_EMMC_TUNING_PROTOCOL PCH_EMMC_TUNING_PROTOCOL @endlink

  - <b>References</b>\n
    - @link _PCH_POLICY PCH_POLICY_HOB @endlink.
    - @link _SI_POLICY_STRUCT SI_POLICY_HOB @endlink.

  - <b>Integration Checklists</b>\n
    - Verify prerequisites are met. Porting Recommendations.
    - No modification of this module should be necessary
    - Any modification of this module should follow the PCH BIOS Specification and EDS

  @param[in] ImageHandle          Handle for the image of this driver
  @param[in] SystemTable          Pointer to the EFI System Table

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
PchInitEntryPointDxeFsp (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  VOID        *Registration;

  DEBUG ((DEBUG_INFO, "PchInitEntryPointDxeFsp() Start\n"));

  PchInitEntryPointCommon ();
  ///
  /// Create PCI Enumeration Completed callback for PCH
  ///
  EfiCreateProtocolNotifyEvent (
    &gEfiPciEnumerationCompleteProtocolGuid,
    TPL_CALLBACK,
    PchOnPciEnumComplete,
    NULL,
    &Registration
    );
  DEBUG ((DEBUG_INFO, "PchInitEntryPointDxeFsp() End\n"));

  return EFI_SUCCESS;
}

