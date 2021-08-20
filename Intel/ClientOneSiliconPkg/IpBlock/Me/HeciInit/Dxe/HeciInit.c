/** @file
  HECI driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 2007 - 2020 Intel Corporation.

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

#include <PiDxe.h>
#include <Base.h>
#include <Uefi.h>
#include <Register/HeciRegs.h>
#include <Library/PciSegmentLib.h>
#include <Guid/EventGroup.h>
#include <Guid/EventLegacyBios.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/PerformanceLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PerformanceLib.h>
#include <Library/S3BootScriptLib.h>
#include <IndustryStandard/Pci22.h>
#include <Library/DxeMeLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/TimerLib.h>
#include <Library/HeciInitLib.h>
#include <Library/HobLib.h>
#include <MeBiosPayloadHob.h>
#include "MeInit.h"
#include "HeciInit.h"
#include <Protocol/Smbios.h>
#include <Library/PostCodeLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED HECI_INSTANCE         *mHeciContext;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN               mDisMeDevReq;

/**
  Function to set D0I3 bits for HECI devices when gBS->ExitBootServices() called or LegacyBoot event.

  @param[in]  Event                   Pointer to this event
  @param[in]  Context                 Event handler private data

**/
VOID
EFIAPI
HeciD0I3EntryPriorToBoot (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  DEBUG ((DEBUG_INFO, "HeciD0I3EntryPriorToBoot - setting D0I3 bits for HECI devices on boot time\n"));

  SetD0I3Bit (HECI1);
  SetD0I3Bit (HECI2);
  SetD0I3Bit (HECI3);
}

/**
  Function to register gBS->ExitBootServices() and LegacyBoot callbacks for setting D0I3 bits in HECI devices.
**/
VOID
RegisterD0I3EventsForHeciDevices (
  VOID
  )
{
  EFI_EVENT                   Event;
  EFI_STATUS                  Status;
  ///
  /// Don't set D0I3 if disabled by policy
  ///
  if (MeHeciD0I3Enabled () == FALSE) {
    DEBUG ((DEBUG_INFO, "RegisterD0I3EventsForHeciDevices - SKIP setting D0I3 bits for HECI devices on boot time\n"));
    return;
  }

  ///
  /// Create ExitBootServices/LegacyBootEvent for setting the HECIx D0I3 bit
  ///
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  HeciD0I3EntryPriorToBoot,
                  NULL,
                  &gEfiEventExitBootServicesGuid,
                  &Event
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  HeciD0I3EntryPriorToBoot,
                  NULL,
                  &gEfiEventLegacyBootGuid,
                  &Event
                  );
  ASSERT_EFI_ERROR (Status);
}

/**
  HECI driver entry point used to initialize support for the HECI device.

  @param[in] ImageHandle          Standard entry point parameter.
  @param[in] SystemTable          Standard entry point parameter.

  @retval EFI_SUCCESS             Always return EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
InitializeHeci (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_EVENT                       Event;
  UINT32                          MeStatus;
  UINT32                          MeMode;
  ME_BIOS_PAYLOAD_HOB             *MbpHob;
  EFI_SMBIOS_PROTOCOL             *Smbios;
  VOID                            *Registration;

  DEBUG ((DEBUG_INFO, "ME-BIOS: HECI Protocol Entry.\n"));
  PostCode (0xE04);

  MbpHob        = NULL;
  mDisMeDevReq  = FALSE;
  mHeciContext  = AllocateZeroPool (sizeof (HECI_INSTANCE));

  ///
  /// Initialize HECI protocol pointers
  ///
  if (mHeciContext == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    DEBUG ((DEBUG_ERROR, "ME-BIOS: HECI Protocol Exit - Error by lack of memory for HECI_INSTANCE.\n"));
    PostCode (0xE84);
    goto ErrExit;
  }
  mHeciContext->HeciCtlr.ResetHeci    = ResetHeciInterface;
  mHeciContext->HeciCtlr.SendwAck     = HeciSendwAck;
  mHeciContext->HeciCtlr.ReadMsg      = HeciReceive;
  mHeciContext->HeciCtlr.SendMsg      = HeciSend;
  mHeciContext->HeciCtlr.InitHeci     = HeciInitialize;
  mHeciContext->HeciCtlr.ReInitHeci   = HeciReInitialize;
  mHeciContext->HeciCtlr.MeResetWait  = MeResetWait;
  mHeciContext->HeciCtlr.GetMeStatus  = HeciGetMeStatus;
  mHeciContext->HeciCtlr.GetMeMode    = HeciGetMeMode;

  ///
  /// Initialize the HECI device
  ///
  Status = HeciInitialize (HECI1_DEVICE);
  if (EFI_ERROR (Status)) {
    ///
    /// Don't install on ERR
    ///
    DEBUG ((DEBUG_ERROR, "ME-BIOS: HECI Protocol Exit - Error by HeciInitialize fail, Status: %r\n", Status));
    PostCode (0xEA4);
    goto ErrExit;
  }
  ///
  /// Install the HECI interface
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mHeciContext->Handle,
                  &gHeciProtocolGuid,
                  &mHeciContext->HeciCtlr,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: HECI Protocol Exit - Error by install HECI protocol fail, Status: %r\n", Status));
    PostCode (0xEC4);
    goto ErrExit;
  }

  HeciGetMeStatus (&MeStatus);
  HeciGetMeMode (&MeMode);

  InitializeHeciFlow ();
  //
  // Get the MBP Data.
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob != NULL) {
    ///
    /// Dxe Mbp data is gone after ExitPmAuth, so we keep MeFwImageType for the inspection after ExitPmAuth
    ///
    mHeciContext->MeFwImageType = (UINT8) MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType;
  }

#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
  RegisterD0I3EventsForHeciDevices ();
#endif

  //
  // Register End of DXE event
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  MeEndOfDxeEvent,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &Event
                  );
  ASSERT_EFI_ERROR (Status);


  ///
  /// Create Ready to Boot events. The first event is created with higher TPL level in order to
  /// ensure that SMBIOS tables are updated before they are measured by TPM (see Extended Measurement
  /// boot for more details).
  ///
  mDisMeDevReq  = FALSE;
  Status = EfiCreateEventReadyToBootEx (
             TPL_NOTIFY,
             AddFwStsSmbiosEntry,
             (VOID *) &mDisMeDevReq,
             &Event
             );

  Status = EfiCreateEventReadyToBootEx (
             TPL_CALLBACK,
             MeReadyToBootEvent,
             NULL,
             &Event
             );

  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "ME-BIOS: HECI Protocol Exit - Success.\n"));
  PostCode (0xE24);

  //
  // Install reset handler.
  //
  RegisterMeReset ();

  return Status;

ErrExit:
  ///
  /// Install FWSTS Smbios table before disable all ME devices.
  ///
  Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **) &Smbios);

  mDisMeDevReq = TRUE;
  if (!EFI_ERROR (Status)) {
    AddFwStsSmbiosEntry (NULL, (VOID *)&mDisMeDevReq);
  } else {
    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    AddFwStsSmbiosEntry,
                    (VOID *)&mDisMeDevReq,
                    &Event
                    );
    ASSERT_EFI_ERROR (Status);

    Status = gBS->RegisterProtocolNotify (
                    &gEfiSmbiosProtocolGuid,
                    Event,
                    &Registration
                    );
    ASSERT_EFI_ERROR (Status);
  }
  return Status;
}
