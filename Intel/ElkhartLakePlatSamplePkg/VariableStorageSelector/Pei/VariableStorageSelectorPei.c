/** @file
  Variable Storage Selector PEIM

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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

@par Specification
**/

#include <Library/BaseMemoryLib.h>
#include <Library/BootMediaLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/PciSegmentLib.h>
#include <Register/HeciRegs.h>
#include <Register/MeRegs.h>
#include <Library/SecurePreMemoryDataLoadLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/VariableStorageSelectorLib.h>
#include <Ppi/VariableStorageSelectorPpi.h>

#include <Guid/CseVariableStoragePpiInstanceGuid.h>
#include <Guid/FvbVariableStoragePpiInstanceGuid.h>

//
// NOTE: Dynamic PCDs cannot be consumed in the Variable Storage
//       Selector PPI due to lock conflicts with the variable driver.
//

EFI_STATUS
EFIAPI
CseBootModeBasedVariableConfiguration (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
);

static EFI_PEI_NOTIFY_DESCRIPTOR mUfsVariableConfigurationNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMemoryDiscoveredPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT)CseBootModeBasedVariableConfiguration
};
/**
  Gets the variable storage instance ID for the variable storage instance
  that is used to store a given variable.

  @param[in]  VariableName      A pointer to a null-terminated string that is
                                the variable's name.
  @param[in]  VariableGuid      A pointer to an EFI_GUID that is the variable's
                                GUID. The combination of VariableGuid and
                                VariableName must be unique.
  @param[out] VariableStorageId The ID for the variable storage instance that
                                stores a given variable

  @retval EFI_SUCCESS           Variable storage instance id was retrieved
**/
EFI_STATUS
EFIAPI
PeiGetVariableStorageId (
  IN  CONST  CHAR16       *VariableName,
  IN  CONST  EFI_GUID     *VendorGuid,
  OUT        EFI_GUID     *VariableStorageId
  )
{
  EFI_STATUS              Status;
  VARIABLE_STORAGE_TYPE   VariableStorageType;

  Status = GetVariableStorageType (VariableName, VendorGuid, &VariableStorageType);
  if (!EFI_ERROR (Status)) {
    if (VariableStorageType == VariableStorageFvb) {
      if (!PcdGetBool (PcdEnableFvbVariableStorage) && !PcdGetBool (PcdNvVariableEmulationMode)) {
        DEBUG ((DEBUG_ERROR, "FVB variable storage is disabled with variable dependencies.\n"));
        Status = EFI_NOT_FOUND;
      } else {
        CopyMem (VariableStorageId, &gFvbVariableStoragePpiInstanceGuid, sizeof (EFI_GUID));
      }
    } else if (VariableStorageType == VariableStorageCse) {
      if (!PcdGetBool (PcdEnableCseVariableStorage) && !PcdGetBool (PcdNvVariableEmulationMode)) {
        DEBUG ((DEBUG_ERROR, "CSE variable storage is disabled with variable dependencies.\n"));
        Status = EFI_NOT_FOUND;
      } else {
        CopyMem (VariableStorageId, &gCseVariableStoragePpiInstanceGuid, sizeof (EFI_GUID));
      }
    } else {
      Status = EFI_NOT_FOUND;
    }
  }

  return Status;
}

EDKII_VARIABLE_STORAGE_SELECTOR_PPI mCseVariableStorageSelectorPpi = {
  PeiGetVariableStorageId
};

EFI_PEI_PPI_DESCRIPTOR mPpiListVariable = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEdkiiVariableStorageSelectorPpiGuid,
  &mCseVariableStorageSelectorPpi
};

/**
Installs the Variable Storage Selector PPI.

The Variable Storage Selector PPI is consumed by the Variable PEIM. It controls
which specific Variable Storage PPI is used to store a variable.

@param[in]  PeiServices       General purpose services available to every PEIM.
@param[in]  NotifyDescriptor  Notify that this module published.
@param[in]  Ppi               PPI that was installed.

@retval     EFI_SUCCESS       The function completed successfully.
**/
EFI_STATUS
EFIAPI
CseBootModeBasedVariableConfiguration (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
)
{
  HECI_FWS_REGISTER MeHfs;

  MeHfs.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, HECI_BUS, HECI_DEV, HECI_FUN, R_ME_HFS));
  if (MeHfs.ul != 0xFFFFFFFF) {
    if(MeHfs.r.CurrentState == ME_STATE_RECOVERY) {
      DEBUG ((DEBUG_WARN, "Warning: Cse is in RecoveryMode\n"));
      PcdSetBoolS (PcdEnableVariableConfigInCseRecoveryMode, TRUE);
    }
  }
  return EFI_SUCCESS;
}
/**
  Installs the Variable Storage Selector PPI.

  The Variable Storage Selector PPI is consumed by the Variable PEIM. It controls
  which specific Variable Storage PPI is used to store a variable.

  @param      None

  @retval     EFI_SUCCESS  Variable Storage Selector services were sucessfully installed / reinstalled.
  @retval     EFI_ERROR    Variable Storage Selector services were not installed / reinstalled.
**/
EFI_STATUS
EFIAPI
PeimInstallVariableStorageSelector (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_PEI_PPI_DESCRIPTOR                *PeiPpiDescriptor;
  EDKII_VARIABLE_STORAGE_SELECTOR_PPI   *VariableStorageSelectorPpi;
  EFI_STATUS                            Status;

  PeiServicesRegisterForShadow (FileHandle);

  Status = PeiServicesLocatePpi (
             &gEdkiiVariableStorageSelectorPpiGuid,
             0,
             &PeiPpiDescriptor,
             (VOID **) &VariableStorageSelectorPpi
             );

  if (Status == EFI_SUCCESS) {
    //
    // Reinstall the Variable Storage Selector PPI
    //
    Status = PeiServicesReInstallPpi (
               PeiPpiDescriptor,
               &mPpiListVariable
               );
    if (BootMediaIsUfs ()) {
      if (PcdGetBool (PcdEnableCseVariableStorage)) {
        Status = PeiServicesLocatePpi (
                   &gEfiPeiMemoryDiscoveredPpiGuid,
                   0,
                   NULL,
                   NULL
                   );
        if (Status == EFI_SUCCESS) {
          CseBootModeBasedVariableConfiguration (NULL, NULL, NULL);
        } else {
          Status = PeiServicesNotifyPpi (&mUfsVariableConfigurationNotifyList);
          ASSERT_EFI_ERROR (Status);
        }
      }
    }
  } else if (Status == EFI_NOT_FOUND) {
    //
    // Install the Variable Storage Selector PPI
    //
    Status = PeiServicesInstallPpi (&mPpiListVariable);
    ASSERT_EFI_ERROR (Status);

    if (PcdGetBool (PcdNvVariableEmulationMode)) {
      DEBUG ((DEBUG_INFO, "UEFI variable emulation mode is enabled. Disabling other mechanisms.\n"));
      PcdSetBoolS (PcdEnableFvbVariableStorage, FALSE);
      PcdSetBoolS (PcdEnableCseVariableStorage, FALSE);
    } else if (!BootMediaIsKnown ()) {
      DEBUG ((DEBUG_ERROR, "The boot media is unknown. UEFI variables cannot be saved properly!\n"));
      ASSERT (BootMediaIsKnown ());
      CpuDeadLoop ();
    } else if (BootMediaIsSpi ()) {
      if (PcdGetBool (PcdEnableFvbVariableStorage)) {
        PcdSetBoolS (PcdEnableCseVariableStorage, FALSE);
      } else {
        DEBUG ((DEBUG_WARN, "Warning: PcdEnableFvbVariableStorage is FALSE on SPI boot. Enabling emulation mode.\n"));

        PcdSetBoolS (PcdEnableCseVariableStorage, FALSE);
        PcdSetBoolS (PcdNvVariableEmulationMode, TRUE);
      }
    } else if (BootMediaIsUfs ()) {
      if (PcdGetBool (PcdEnableCseVariableStorage)) {
        PcdSetBoolS (PcdEnableFvbVariableStorage, FALSE);

        DEBUG ((DEBUG_INFO, "Attempting to load Secure Pre-Memory Data.\n"));
        Status = LoadSecurePreMemoryData ();
      } else {
        DEBUG ((DEBUG_WARN, "Warning: PcdEnableCseVariableStorage is FALSE on UFS boot. Enabling emulation mode.\n"));

        PcdSetBoolS (PcdEnableFvbVariableStorage, FALSE);
        PcdSetBoolS (PcdNvVariableEmulationMode, TRUE);
      }
    } else {
      DEBUG ((DEBUG_ERROR, "The boot media is unknown. UEFI variables cannot be saved properly!\n"));
      CpuDeadLoop ();
    }
  }
  ASSERT_EFI_ERROR (Status);

  return Status;
}
