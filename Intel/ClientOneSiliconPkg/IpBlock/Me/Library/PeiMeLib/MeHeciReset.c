/** @file
  ME HECI reset PEI lib.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include <Uefi.h>
#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ResetSystemLib.h>
#include <Ppi/PlatformSpecificResetHandler.h>
#include <Library/BaseMemoryLib.h>
#include <CoreBiosMsg.h>
#include <Library/PmcLib.h>
#include <Library/PeiMeLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/HobLib.h>

/**
  Print reset message for debug build readability
**/
VOID
EFIAPI
PrintResetMessage (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "******************************\n"));
  DEBUG ((DEBUG_INFO, "**    SYSTEM REBOOT !!!     **\n"));
  DEBUG ((DEBUG_INFO, "******************************\n"));
}

/**
  Sent HECI command to ME for GlobalReset

  @param[in] ResetType            Warm or cold
  @param[in] ResetStatus          Possible cause of reset
  @param[in] DataSize             Size of ResetData in bytes
  @param[in] ResetData            Optional Unicode string

**/
VOID
EFIAPI
PeiMeResetHandlerCallback (
  IN EFI_RESET_TYPE           ResetType,
  IN EFI_STATUS               ResetStatus,
  IN UINTN                    DataSize,
  IN VOID                     *ResetData OPTIONAL
  )
{
  EFI_STATUS       Status;
  EFI_GUID         *GuidPtr;
  VOID             *Hob;

  PrintResetMessage ();
  if (ResetType != EfiResetPlatformSpecific) {
    return;
  }
  if (ResetData == NULL) {
    return;
  }

  GuidPtr = (EFI_GUID *) ((UINT8 *) ResetData + DataSize - sizeof (EFI_GUID));
  if (!CompareGuid (GuidPtr, &gPchGlobalResetGuid)) return;

  //
  // PCH BIOS Spec Section 4.6 GPIO Reset Requirement
  //
  DEBUG ((DEBUG_INFO, "Enable CF9 Global Reset - PEI\n"));
  PmcEnableCf9GlobalReset ();

  Hob = GetFirstGuidHob (&gMeDataHobGuid);
  if (Hob == NULL) {
    Status = EFI_NOT_FOUND;
  } else {
    Status = EFI_SUCCESS;
  }
  if (Status == EFI_SUCCESS) {
    //
    // After sending DRAM Init Done to ME FW, please do the global reset through HECI.
    //
    DEBUG ((DEBUG_INFO,"Send HECI command CBM_HRR_GLOBAL_RESET\n"));
    PeiHeciSendCbmResetRequest (CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
  }

}


/**
  This function register reset handler ppi for ME in PEI

  @param[in]  PeiServices      Pointer to PEI Services Table.
  @param[in]  NotifyDescriptor Pointer to the descriptor for the Notification event that
                               caused this function to execute.
  @param[in]  Interface        Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS  The function completes successfully
  @retval     others

**/
EFI_STATUS
EFIAPI
MeResetHandlerCallback (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Interface
  )
{
  EFI_STATUS                                Status;
  EDKII_PLATFORM_SPECIFIC_RESET_HANDLER_PPI *ResetHandlerPpi;

  DEBUG ((DEBUG_INFO,"MeResetHandlerCallback() START\n"));

  Status = (*PeiServices)->LocatePpi (
                PeiServices,
                &gEdkiiPlatformSpecificResetHandlerPpiGuid,
                0,
                NULL,
                (VOID **) &ResetHandlerPpi
                );

  if (!EFI_ERROR (Status)) {
    ResetHandlerPpi->RegisterResetNotify (ResetHandlerPpi, PeiMeResetHandlerCallback);
  }

  return EFI_SUCCESS;
}


GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_NOTIFY_DESCRIPTOR  mResetHandlerReady = {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEdkiiPlatformSpecificResetHandlerPpiGuid,
    (EFI_PEIM_NOTIFY_ENTRY_POINT) MeResetHandlerCallback
};

/**
  Install ME call back function for rest2 ppi.

**/
VOID
RegisterMeReset (
  VOID
  )
{
  PeiServicesNotifyPpi (&mResetHandlerReady);
}

