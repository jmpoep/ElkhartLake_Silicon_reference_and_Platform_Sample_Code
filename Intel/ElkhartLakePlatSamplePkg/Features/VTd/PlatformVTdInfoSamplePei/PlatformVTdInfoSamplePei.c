/** @file
  Platform VTd Info Sample PEI driver.

  Copyright (c) 2018 - 2019, Intel Corporation.

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

**/

#include <PiPei.h>

#include <Ppi/VtdInfo.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/PeiServicesLib.h>
#include <Library/DebugLib.h>
#include <Library/PciLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/PciSegmentLib.h>
#include <SetupVariable.h>
#include <SaCommonDefinitions.h>
#include <Register/VtdRegs.h>

typedef struct {
  EFI_ACPI_DMAR_HEADER                         DmarHeader;
  //
  // VTd engine - IOP
  //
  EFI_ACPI_DMAR_DRHD_HEADER                    IopDrhd;
} PLATFORM_VTD_INFO_IOP_PPI;

PLATFORM_VTD_INFO_IOP_PPI mPlatformIopVTdSample = {
  { // DmarHeader
    { // Header
      EFI_ACPI_4_0_DMA_REMAPPING_TABLE_SIGNATURE,
      sizeof(PLATFORM_VTD_INFO_IOP_PPI),
      EFI_ACPI_DMAR_REVISION,
    },
    0x26, // HostAddressWidth -- TO BE PATCHED
  },
  { // IopDrhd
    { // Header
      EFI_ACPI_DMAR_TYPE_DRHD,
      sizeof(EFI_ACPI_DMAR_DRHD_HEADER)
    },
    EFI_ACPI_DMAR_DRHD_FLAGS_INCLUDE_PCI_ALL, // Flags
    0, // Reserved
    0, // SegmentNumber
    /*
       IOP RegisterBaseAddress -- TO BE PATCHED:
       This address should match to the value in Silicon Policy
       In the preMem phase, we will only use one VTd hardware unit for PMR
    */
    0xFED91000
  },
};

EFI_PEI_PPI_DESCRIPTOR mPlatformIopVTdInfoSampleDesc = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEdkiiVTdInfoPpiGuid,
  &mPlatformIopVTdSample
};

/**
  Initialize VTd register.
**/
VOID
InitDmar (
  VOID
  )
{
  UINT32              McD0BaseAddress;
  UINT32              MchBar;

  DEBUG ((DEBUG_INFO, "InitDmar\n"));

  McD0BaseAddress  = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  MchBar = PciSegmentRead32 (McD0BaseAddress + R_SA_MCHBAR) & ~B_SA_MCHBAR_MCHBAREN_MASK;
  DEBUG ((DEBUG_INFO, "MchBar - %x\n", MchBar));

  MmioWrite32 (MchBar + R_MCHBAR_VTD3_OFFSET, (UINT32)mPlatformIopVTdSample.IopDrhd.RegisterBaseAddress | BIT0);
  DEBUG ((DEBUG_INFO, "IOP VTd - %x\n", (MmioRead32 (MchBar + R_MCHBAR_VTD3_OFFSET))));

}

/**
  The callback function for MemoryInitializedPpi.
  It installs PLATFORM_VTD_INFO_IOP_PPI.

  @param[in]  PeiServices            General purpose services available to every PEIM.
  @param[in]  NotifyDescriptor       Notify that this module published.
  @param[in]  Ppi                    PPI that was installed.

  @retval     EFI_SUCCESS            The function completed successfully.
**/
EFI_STATUS
EFIAPI
MemoryInitializedPpiNotifyCallback (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS               Status;
  Status                   = EFI_UNSUPPORTED;

  DEBUG ((DEBUG_INFO, "MemoryInitializedPpiNotifyCallback for iommu\n"));

  Status = PeiServicesInstallPpi (&mPlatformIopVTdInfoSampleDesc);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR , "Failed to install a ppi - %r\n", Status));
  }

  return Status;
}

EFI_PEI_NOTIFY_DESCRIPTOR mMemoryInitializedNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMemoryDiscoveredPpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) MemoryInitializedPpiNotifyCallback
};

/**
  Check Iommu Ability base on Vtd Policy.
**/
VOID
PeiCheckIommuSupport (
  VOID
  )
{
  EFI_STATUS                      Status;
  SA_SETUP                        *SaSetup;
  SETUP_DATA                      *SetupData;
  UINTN                           VarSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;

  SetupData                       = NULL;
  SaSetup                         = NULL;
  VarSize                         = 0;
  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "PeiServicesLocatePpi failed\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  VarSize = sizeof (SETUP_DATA);
  SetupData = AllocateZeroPool (VarSize);
  if (SetupData == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to allocate SetupData size\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VarSize,
                               SetupData
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "GetVariable (SetupData) failed, Status:%r\n", Status));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  //
  // Locate SaSetup variables
  //
  VarSize = sizeof (SA_SETUP);
  SaSetup = AllocateZeroPool (VarSize);
  if (SaSetup == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to allocate SaSetup size\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"SaSetup",
                               &gSaSetupVariableGuid,
                               NULL,
                               &VarSize,
                               SaSetup
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "GetVariable (SaSetup) failed, Status:%r\n", Status));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  if (SaSetup->EnableVtd == 0x00) {
    //
    // Set PcdVTdPolicyPropertyMask to 0 when VTd disable
    //
    PcdSet8S (PcdVTdPolicyPropertyMask, 0x00);
  } else {

    //
    // This Control Iommu setup option is mainly for debug purpose.
    // It might be removed when feature is stable
    //
    if (SetupData->ControlIommu != 0x00) {
      PcdSet8S (PcdVTdPolicyPropertyMask, 0x01);
    } else {
      PcdSet8S (PcdVTdPolicyPropertyMask, 0x00);
    }
  }

Exit:
  DEBUG ((DEBUG_INFO, "PcdVTdPolicyPropertyMask value: %x\n", PcdGet8(PcdVTdPolicyPropertyMask)));

  if (SetupData != NULL) {
    FreePool (SetupData);
  }

  if (SaSetup != NULL) {
    FreePool (SaSetup);
  }

}

/**
  Platform VTd Info sample driver.

  @param[in] FileHandle         Handle of the file being invoked.
  @param[in] PeiServices        Describes the list of possible PEI Services.

  @retval EFI_SUCCESS           The function completed successfully.
  @retval EFI_UNSUPPORTED       Iommu is unsupported.
**/
EFI_STATUS
EFIAPI
PlatformVTdInfoSampleInitialize (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                      Status;
  VOID                            *MemoryDiscovered;
  BOOLEAN                         MemoryInitialized;

  Status = EFI_UNSUPPORTED;
  MemoryDiscovered = NULL;
  MemoryInitialized = FALSE;

  DEBUG ((DEBUG_INFO, "PlatformVTdInfoSampleInitialize START\n"));

  //
  // check if we should enable Iommu
  //
  PeiCheckIommuSupport ();

  if ((PcdGet8(PcdVTdPolicyPropertyMask) & BIT0) == 0) {
    DEBUG ((DEBUG_INFO, "Iommu is unsupported\n"));
    goto Exit;
  }

  //
  // Check if memory is initialized.
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiMemoryDiscoveredPpiGuid,
             0,
             NULL,
             &MemoryDiscovered
             );
  if (!EFI_ERROR(Status)) {
    MemoryInitialized = TRUE;
  }

  DEBUG ((DEBUG_INFO, "MemoryInitialized - %x\n", MemoryInitialized));

  if (!MemoryInitialized) {
    //
    // If the memory is not initialized, register a notification
    //
    Status = PeiServicesNotifyPpi (&mMemoryInitializedNotifyList);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR , "Failed to register a notification - %r\n", Status));
    }

    InitDmar ();

    Status = PeiServicesInstallPpi (&mPlatformIopVTdInfoSampleDesc);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR , "Failed to install a ppi - %r\n", Status));
    }
  } else {
    //
    // If customer only wants to enable PMR in PostMem
    //
    Status = PeiServicesInstallPpi (&mPlatformIopVTdInfoSampleDesc);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR , "Failed to install a ppi - %r\n", Status));
    }
  }
Exit:
  DEBUG ((DEBUG_INFO, "PlatformVTdInfoSampleInitialize END\n"));
  return Status;
}
