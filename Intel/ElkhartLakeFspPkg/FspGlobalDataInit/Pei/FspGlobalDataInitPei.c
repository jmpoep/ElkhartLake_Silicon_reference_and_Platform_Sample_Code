/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#include <PiPei.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/PeimEntryPoint.h>
#include <FspGlobalData.h>
#include <Library/FspCommonLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/MemoryAllocationLib.h>

/**
  This interface gets FspInfoHeader pointer

  @return   FSP binary base address.
**/
UINT32
EFIAPI
AsmGetFspInfoHeader (
  VOID
  );

/**
  This function is called after PEI core discover memory and finish migration.

  @param[in] PeiServices    Pointer to PEI Services Table.
  @param[in] NotifyDesc     Pointer to the descriptor for the Notification event that
                            caused this function to execute.
  @param[in] Ppi            Pointer to the PPI data associated with this function.

  @retval EFI_STATUS        Always return EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
PeiMemoryDiscoveredNotify (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

EFI_PEI_NOTIFY_DESCRIPTOR mPeiMemoryDiscoveredNotifyDesc = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMemoryDiscoveredPpiGuid,
  PeiMemoryDiscoveredNotify
};

/**
  Main entry

  @param[in] FileHandle        Handle of the file being invoked.
  @param[in] PeiServices       Pointer to PEI Services table.

  @retval EFI_SUCCESS          Install function successfully.
  @retval EFI_OUT_OF_RESOURCES Insufficient resources to create buffer.

**/
EFI_STATUS
EFIAPI
FspGlobalDataInitEntryPoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS              Status;
  FSP_GLOBAL_DATA         *FspData;
  EFI_PEI_PPI_DESCRIPTOR  *PpiDescriptor;

  Status = EFI_SUCCESS;
  FspData = GetFspGlobalDataPointer ();

  if ((UINTN)FspData == 0x00 || (UINTN)FspData == 0xFFFFFFFF) {
    //
    // Re-initialize Global Data as it was not present/initialized earlier.
    //
    FspData = NULL;
    FspData = (FSP_GLOBAL_DATA *) AllocateZeroPool (sizeof (FSP_GLOBAL_DATA));
    if (FspData == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    if (FspData != NULL) {
      FspData->Signature      = FSP_GLOBAL_DATA_SIGNATURE;
      FspData->Version        = 0;
      FspData->PerfIdx        = 2;
      FspData->PerfSig        = FSP_PERFORMANCE_DATA_SIGNATURE;
      //
      // In API mode FspGlobalData must have be initialized in FspSecCore, so here must be DISPATCH mode.
      //
      FspData->FspMode = FSP_IN_DISPATCH_MODE;
      FspData->FspInfoHeader  = (FSP_INFO_HEADER *) AsmGetFspInfoHeader ();

      SetFspGlobalDataPointer (FspData);
      //
      // Ensure the golbal data pointer is valid
      //
      ASSERT (GetFspGlobalDataPointer () == FspData);
    }
  }

  if (FspData->FspMode == FSP_IN_DISPATCH_MODE) {
    PpiDescriptor = AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
    if (PpiDescriptor == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    if (PpiDescriptor != NULL) {
      PpiDescriptor->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
      PpiDescriptor->Ppi   = (VOID *) FspData;
      PpiDescriptor->Guid  = &gFspGlobalDataInitPpiGuid;

      Status = PeiServicesInstallPpi (PpiDescriptor);
      ASSERT_EFI_ERROR (Status);
    }

    Status = PeiServicesNotifyPpi (&mPeiMemoryDiscoveredNotifyDesc);
    ASSERT_EFI_ERROR (Status);
  }
  DEBUG ((DEBUG_INFO, " FspData: Signature     - 0x%x\n", FspData->Signature));
  DEBUG ((DEBUG_INFO, " FspData: Version       - 0x%x\n", FspData->Version));
  DEBUG ((DEBUG_INFO, " FspData: PerfIdx       - 0x%x\n", FspData->PerfIdx));
  DEBUG ((DEBUG_INFO, " FspData: PerfSig       - 0x%x\n", FspData->PerfSig));
  DEBUG ((DEBUG_INFO, " FspData: FspMode       - %s\n",   FspData->FspMode ? L"DISPATCH" : L"API"));
  DEBUG ((DEBUG_INFO, " FspData: FspInfoHeader - 0x%x\n", FspData->FspInfoHeader));
  return Status;
}

/**
  This function is called after PEI core discover memory and finish migration.

  @param[in] PeiServices    Pointer to PEI Services Table.
  @param[in] NotifyDesc     Pointer to the descriptor for the Notification event that
                            caused this function to execute.
  @param[in] Ppi            Pointer to the PPI data associated with this function.

  @retval EFI_STATUS        Always return EFI_SUCCESS
**/
EFI_STATUS
PeiMemoryDiscoveredNotify (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS              Status;
  VOID                    *FspGlobalDataInitPpi;
  FSP_GLOBAL_DATA         *FspData;

  DEBUG ((DEBUG_INFO, "PeiMemoryDiscoveredNotify enter\n"));

  Status = PeiServicesLocatePpi (
             &gFspGlobalDataInitPpiGuid,
             0,
             NULL,
             (VOID **) &FspGlobalDataInitPpi
             );
  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR (Status)) {
    FspData = (FSP_GLOBAL_DATA *) FspGlobalDataInitPpi;
    SetFspGlobalDataPointer (FspData);
    DEBUG ((DEBUG_INFO, " FspData: Signature     - 0x%x\n", FspData->Signature));
    DEBUG ((DEBUG_INFO, " FspData: Version       - 0x%x\n", FspData->Version));
    DEBUG ((DEBUG_INFO, " FspData: PerfIdx       - 0x%x\n", FspData->PerfIdx));
    DEBUG ((DEBUG_INFO, " FspData: PerfSig       - 0x%x\n", FspData->PerfSig));
    DEBUG ((DEBUG_INFO, " FspData: FspMode       - %s\n",   FspData->FspMode ? L"DISPATCH" : L"API"));
    DEBUG ((DEBUG_INFO, " FspData: FspInfoHeader - 0x%x\n", FspData->FspInfoHeader));
  }

  return EFI_SUCCESS;
}
