/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file
  LegacyInterruptHook Driver.

Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/
#include <PiDxe.h>
#include <Pi/PiDxeCis.h>

#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/LegacyInterruptHandler.h>

VOID                      *mRegisteration;
EFI_LEGACY_BIOS_PROTOCOL  *mLegacyBios;

//
// Legacy BIOS needs to access memory in page 0 (0-4095), which is disabled if
// NULL pointer detection feature is enabled. Following macro can be used to
// enable/disable page 0 before/after accessing it.
//
#if !defined (ACCESS_PAGE0_CODE)
#define ACCESS_PAGE0_CODE(statements)                           \
  do {                                                          \
    EFI_STATUS                            Status_;              \
    EFI_GCD_MEMORY_SPACE_DESCRIPTOR       Desc_;                \
                                                                \
    Desc_.Attributes = 0;                                       \
    Status_ = gDS->GetMemorySpaceDescriptor (0, &Desc_);        \
    ASSERT_EFI_ERROR (Status_);                                 \
    if ((Desc_.Attributes & EFI_MEMORY_RP) != 0) {              \
      Status_ = gDS->SetMemorySpaceAttributes (                 \
                      0,                                        \
                      EFI_PAGES_TO_SIZE(1),                     \
                      Desc_.Attributes & ~(UINT64)EFI_MEMORY_RP \
                      );                                        \
      ASSERT_EFI_ERROR (Status_);                               \
    }                                                           \
                                                                \
    {                                                           \
      statements;                                               \
    }                                                           \
                                                                \
    if ((Desc_.Attributes & EFI_MEMORY_RP) != 0) {              \
      Status_ = gDS->SetMemorySpaceAttributes (                 \
                      0,                                        \
                      EFI_PAGES_TO_SIZE(1),                     \
                      Desc_.Attributes                          \
                      );                                        \
      ASSERT_EFI_ERROR (Status_);                               \
    }                                                           \
  } while (FALSE)
#endif

/**
  Callback for the Legacy Interrupt Handler protocol installation.

  @param Event     Event handle.
  @param Context   Callback context.
**/
VOID
EFIAPI
NewLegacyInterruptHandler (
  IN  EFI_EVENT       Event,
  IN  VOID            *Context
  )
{
  EFI_STATUS                            Status;
  UINTN                                 BufferSize;
  EFI_HANDLE                            Handle;
  EFI_LEGACY_INTERRUPT_HANDLER_PROTOCOL *LegacyInterrupt;
  INTERRUPT_HANDLER                     *NewHandler;
  LEGACY_VECTOR                         *Vector;


  while (TRUE) {
    BufferSize = sizeof (Handle);
    Status = gBS->LocateHandle (
                    ByRegisterNotify,
                    NULL,
                    mRegisteration,
                    &BufferSize,
                    &Handle
                    );
    if (EFI_ERROR (Status)) {
      //
      // Exit Path of While Loop....
      //
      break;
    }

    Status = gBS->HandleProtocol (Handle, &gEfiLegacyInterruptHandlerProtocolGuid, (VOID **) &LegacyInterrupt);
    ASSERT_EFI_ERROR (Status);
    ASSERT (LegacyInterrupt->Number < 0x20);
    ASSERT (LegacyInterrupt->Handler != NULL);
    ASSERT (LegacyInterrupt->Length < 0x20000);

    Vector = (LEGACY_VECTOR *) (UINTN) (LegacyInterrupt->Number * sizeof (LEGACY_VECTOR));
    //
    // Save the original interrupt handler
    //
    ACCESS_PAGE0_CODE (
      LegacyInterrupt->Handler->NextSegment = Vector->Segment;
      LegacyInterrupt->Handler->NextOffset  = Vector->Offset;
    );

    DEBUG ((EFI_D_ERROR, "GetLegacyRegion...\n"));
    Status = mLegacyBios->GetLegacyRegion (
                            mLegacyBios,
                            LegacyInterrupt->Length,
                            0,    // E or F segment
                            0x10, // 16-byte aligned
                            (VOID **) &NewHandler
                            );
    ASSERT_EFI_ERROR (Status);
    //
    // The Address should be 16-byte aligned
    //
    ASSERT (((UINTN) NewHandler & 0xF) == 0);

    DEBUG ((EFI_D_ERROR, "CopyLegacyRegion...\n"));
    Status = mLegacyBios->CopyLegacyRegion (
                            mLegacyBios,
                            LegacyInterrupt->Length,
                            NewHandler,
                            LegacyInterrupt->Handler
                            );
    ASSERT_EFI_ERROR (Status);


    //
    // Set the current interrupt handler
    //
    ACCESS_PAGE0_CODE (
      Vector->Segment = (UINT16) ((UINTN) &NewHandler->Code >> 4);
      Vector->Offset  = (UINT16) ((UINTN) &NewHandler->Code & 0xF);
      DEBUG ((DEBUG_INFO, "Install Interrupt[%02x] - %04x:%04x l=%04x\n",
              (UINTN) LegacyInterrupt->Number, (UINTN) Vector->Segment, (UINTN) Vector->Offset, LegacyInterrupt->Length
             ));
    );
  }
}

/**
  The driver entry point for LegacyInterruptHook Driver.

  The function does the necessary initialization work.

  @param[in]  ImageHandle       The firmware allocated handle for the UEFI image.
  @param[in]  SystemTable       A pointer to the EFI system table.

  @retval     EFI_SUCCESS       This funtion always return EFI_SUCCESS.
                                It will ASSERT on errors.

**/
EFI_STATUS
EFIAPI
InitializeLegacyInterruptHook (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS            Status;

  Status = gBS->LocateProtocol (
                  &gEfiLegacyBiosProtocolGuid,
                  NULL,
                  (VOID **) &mLegacyBios
                  );
  ASSERT_EFI_ERROR (Status);

  EfiCreateProtocolNotifyEvent(
    &gEfiLegacyInterruptHandlerProtocolGuid,
    TPL_CALLBACK,
    NewLegacyInterruptHandler,
    NULL,
    &mRegisteration
    );

  return EFI_SUCCESS;
}
