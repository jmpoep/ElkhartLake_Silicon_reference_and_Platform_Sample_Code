/** @file
  This file is SampleCode for SA DXE Policy initialization.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#include "SaPolicyInitDxe.h"


//
// Function implementations
//

/**
  Initialize SA DXE Policy

  @param[in] ImageHandle          Image handle of this driver.

  @retval EFI_SUCCESS             Initialization complete.
  @exception EFI_UNSUPPORTED      The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
SaPolicyInitDxe (
  IN EFI_HANDLE                   ImageHandle
  )
{
  EFI_STATUS               Status;
  SA_POLICY_PROTOCOL       *SaPolicy;

  //
  // Call CreateSaDxeConfigBlocks to create & initialize platform policy structure
  // and get all Intel default policy settings.
  //
  Status = CreateSaDxeConfigBlocks (&SaPolicy);
  DEBUG ((DEBUG_INFO, "SaPolicy->TableHeader.NumberOfBlocks = 0x%x\n ", SaPolicy->TableHeader.NumberOfBlocks));
  ASSERT_EFI_ERROR (Status);

  UpdateDxeSaPolicyBoardConfig (SaPolicy);

  if (mFirmwareConfiguration != FwConfigDefault) {

    UpdateDxeSaPolicy (SaPolicy);
    GetGopVbtData();
  }

  //
  // Install SaInstallPolicyProtocol.
  // While installed, RC assumes the Policy is ready and finalized. So please
  // update and override any setting before calling this function.
  //
  Status = SaInstallPolicyProtocol (ImageHandle, SaPolicy);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Function to register call back event to get GOP VBT data.

  @retval EFI_SUCCESS           Call back registered successfully.
  @retval EFI_UNSUPPORTED:      Call back registration fails.

**/
EFI_STATUS
GetGopVbtData (
  VOID
  )
{
  EFI_STATUS             Status;
  VOID                   *Registration;
  EFI_EVENT              Event;
  GOP_POLICY_PROTOCOL    *GopPolicy;

  Status = gBS->LocateProtocol (&gGopPolicyProtocolGuid, NULL, (VOID **) &GopPolicy);
  if (Status == EFI_NOT_FOUND) {
    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    (EFI_EVENT_NOTIFY) UpdateSaPolicyGopVbtPointer,
                    NULL,
                    &Event
                    );
    ASSERT_EFI_ERROR (Status);
    Status = gBS->RegisterProtocolNotify (
                    &gGopPolicyProtocolGuid,
                    Event,
                    &Registration
                    );
    ASSERT_EFI_ERROR (Status);
  } else {
    UpdateSaPolicyGopVbtPointer (NULL, NULL);
  }

  return EFI_SUCCESS;
}


/**
  Callback function to Update SaPolicyGopVbtPointer and Size.

  @param[in] Event    - The triggered event.
  @param[in] Context  - Context for this event.

**/
VOID
UpdateSaPolicyGopVbtPointer (
  IN  EFI_EVENT  Event,
  IN  VOID       *Context
  )
{
  EFI_STATUS                       Status;
  SA_POLICY_PROTOCOL               *SaPolicy;
  GOP_POLICY_PROTOCOL              *GopPolicy;
  EFI_PHYSICAL_ADDRESS             VbtAddress;
  UINT32                           Size;
  GRAPHICS_DXE_CONFIG              *GraphicsDxeConfig;

  Status = gBS->LocateProtocol (&gSaPolicyProtocolGuid, NULL, (VOID **) &SaPolicy);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = GetConfigBlock ((VOID *)SaPolicy, &gGraphicsDxeConfigGuid, (VOID *)&GraphicsDxeConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "Locate GopPolicy and GetVbtData\n"));
  ///
  /// Locate the GOP Policy Protocol.
  ///
  GopPolicy = NULL;
  Status = gBS->LocateProtocol (&gGopPolicyProtocolGuid, NULL, (VOID **) &GopPolicy);
  ASSERT (GopPolicy != NULL);
  if (EFI_ERROR (Status) || (GopPolicy == NULL)) {
    return;
  }

  ///
  /// Get VBT data
  ///
  VbtAddress      = 0;
  Size            = 0;
  DEBUG ((DEBUG_INFO, "GetVbtData\n"));
  Status          = GopPolicy->GetVbtData (&VbtAddress, &Size);
  ASSERT_EFI_ERROR(Status);

  GraphicsDxeConfig->VbtAddress = VbtAddress;
  GraphicsDxeConfig->Size = Size;

  return;
}