/** @file
  This file is SampleCode for Intel PEI Platform Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2020 Intel Corporation.

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

@par Specification Reference:
**/

#include "PeiPolicyInit.h"

#include <Ppi/PeiSiDefaultPolicy.h>

/**
  To install PolicyReadyPpi to invoke Silicon initialization.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  SiPolicy PPI.

  @retval EFI_STATUS              The return status from sub function
**/
EFI_STATUS
EFIAPI
MpServicePpiCallback (
  IN  EFI_PEI_SERVICES             **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN  VOID                         *Ppi
  )
{
  EFI_STATUS  Status;
  Status = SiInstallPolicyReadyPpi ();
  ASSERT_EFI_ERROR (Status);
  return Status;
}

static EFI_PEI_NOTIFY_DESCRIPTOR  mMpServicePpiCallbackNotifyList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiMpServicesPpiGuid,
    MpServicePpiCallback
  }
};

EFI_STATUS
EFIAPI
PeiFspWrapperExtractGuidedLib (
  VOID
  );

/**
  Initialize Intel PEI Platform Policy

  @param[in] PeiServices            General purpose services available to every PEIM.
  @param[in] FirmwareConfiguration  It uses to skip specific policy init that depends
                                    on the 'FirmwareConfiguration' varaible.
**/
VOID
EFIAPI
PeiPolicyInit (
  IN CONST EFI_PEI_SERVICES      **PeiServices,
  IN UINT8                       FirmwareConfiguration
  )
{
  EFI_STATUS                     Status;
  SI_POLICY_PPI                  *SiPolicyPpi;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  FSP_INFO_HEADER                *FspsHeaderPtr;
  FSPS_UPD_COMMON                *FspsUpdDataPtr;
  UINTN                          *SourceData;
#else
  PEI_SI_DEFAULT_POLICY_INIT_PPI *PeiSiDefaultPolicyInitPpi;
#endif

  SiPolicyPpi = NULL;

#if FixedPcdGet8(PcdFspModeSelection) == 1
  //
  // Copy default FSP-S UPD data from Flash
  //
  Status = PeiFspWrapperExtractGuidedLib ();
  ASSERT_EFI_ERROR (Status);

  FspsHeaderPtr = (FSP_INFO_HEADER *) FspFindFspHeader (PcdGet32 (PcdFspsBaseAddress));
  if (FspsHeaderPtr == NULL){
    return;
  }
  DEBUG ((DEBUG_INFO, "FspsHeaderPtr - 0x%x\n", FspsHeaderPtr));
  ASSERT (FspsHeaderPtr != NULL);

  FspsUpdDataPtr = (FSPS_UPD_COMMON *) AllocateZeroPool ((UINTN)FspsHeaderPtr->CfgRegionSize);
  ASSERT (FspsUpdDataPtr != NULL);
  SourceData = (UINTN *) ((UINTN)FspsHeaderPtr->ImageBase + (UINTN)FspsHeaderPtr->CfgRegionOffset);
  CopyMem (FspsUpdDataPtr, SourceData, (UINTN)FspsHeaderPtr->CfgRegionSize);

  PcdSet32S (PcdFspsUpdDataAddress, (UINT32) FspsUpdDataPtr);
  //
  // Call SiCreateConfigBlocks to initialize Silicon Policy structure
  // and get all Intel default policy settings.
  //
  Status = SiCreateConfigBlocks (&SiPolicyPpi);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR(Status)) {
    return;
  }
#else
  PeiSiDefaultPolicyInitPpi = NULL;
  //
  // Locate Policy init PPI to install default silicon policy
  //
  Status = PeiServicesLocatePpi (
             &gSiDefaultPolicyInitPpiGuid,
             0,
             NULL,
             (VOID **) &PeiSiDefaultPolicyInitPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (PeiSiDefaultPolicyInitPpi != NULL) {
    Status = PeiSiDefaultPolicyInitPpi->PeiPolicyInit ();
    ASSERT_EFI_ERROR (Status);
    if (Status == EFI_SUCCESS) {
      Status = PeiServicesLocatePpi (
                 &gSiPolicyPpiGuid,
                 0,
                 NULL,
                 (VOID **) &SiPolicyPpi
                 );
      ASSERT_EFI_ERROR (Status);
    }
  }
#endif

  if (SiPolicyPpi == NULL) {
    DEBUG ((DEBUG_ERROR, "Fail to create default policy!\n"));
    return;
  }

  if (PcdGetBool (PcdDumpDefaultSiliconPolicy)) {
    if (SiPolicyPpi != NULL) {
      DEBUG ((DEBUG_INFO, "Dump Default Silicon Policy...\n"));
      DumpSiPolicy (SiPolicyPpi);
    }
  }

  //
  // Update policy by board configuration
  //
  UpdatePeiSiPolicyBoardConfig ();
  UpdatePeiPchPolicyBoardConfig ();
  UpdatePeiCpuPolicyBoardConfig ();
#if FixedPcdGetBool(PcdAmtEnable) == 1
  UpdatePeiAmtPolicyBoardConfig ();
#endif
  UpdatePeiMePolicyBoardConfig ();
  if (FirmwareConfiguration != FwConfigDefault) {
    //
    // Update and override all platform related and customized settings below.
    //
    UpdatePeiSiPolicy ();
    UpdatePeiPchPolicy ();
    UpdatePeiSaPolicy ();
    UpdatePeiCpuPolicy ();
#if FixedPcdGetBool(PcdAmtEnable) == 1
    UpdatePeiAmtPolicy ();
#endif
    UpdatePeiMePolicy ();
    if ((FirmwareConfiguration >= FwConfigTest) && (FirmwareConfiguration < FwConfigMax)) {
      // Update Debug Policies
      UpdatePeiPchPolicyDebug ();
      UpdatePeiCpuPolicyDebug ();
      UpdatePeiSiPolicyDebug ();
    }
  }

#if (FixedPcdGet8(PcdFspModeSelection) == 0) || (FixedPcdGetBool(PcdFspWrapperEnable) == 0)
  //
  // While installed PolicyReadyPpi, RC assumes the Policy is ready and finalized. So please
  // update and override any setting before calling this function.
  //
  Status = PeiServicesNotifyPpi (mMpServicePpiCallbackNotifyList);
  ASSERT_EFI_ERROR (Status);

#endif
}
