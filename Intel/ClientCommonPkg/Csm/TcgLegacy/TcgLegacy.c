/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file
  SMI handler for the INT1A request.

  Caution: This module requires additional review when modified.
  This driver will have external input - TCG INT1A parameter in SMM mode.
  This external input must be validated carefully to avoid security issue like
  buffer overflow, integer overflow.

  TcgSmmDispatcher() will receive untrusted input and do basic validation.

  Each sub function TCG_MemoryOverwriteRequest
  should also do validation based on its own knowledge.

Copyright (c) 1999 - 2016, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include <PiDxe.h>
#include <IndustryStandard/Tpm12.h>
#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/PeImage.h>
#include <IndustryStandard/SmBios.h>

#include <Guid/GlobalVariable.h>
#include <Guid/SmBios.h>
#include <Guid/HobList.h>
#include <Guid/TcgEventHob.h>
#include <Guid/EventGroup.h>
#include <Guid/MemoryOverwriteControl.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/TcgService.h>
#include <Protocol/SmmVariable.h>
#include <Protocol/SmmCpu.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/TcgLegacyInt1AReady.h>

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/HobLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TpmCommLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/SmmMemLib.h>

#include "TpmComm.h"
#include "TcgLegacy.h"

EFI_SMM_VARIABLE_PROTOCOL *mSmmVariable;
EFI_SMM_CPU_PROTOCOL      *mSmmCpu;

typedef struct _TCG_SMM_DATA {
  TCG_EFI_BOOT_SERVICE_CAPABILITY   BsCap;
} TCG_SMM_DATA;

TCG_SMM_DATA                 mTcgSmmData;

#define  TCG_OK                      0
#define  TPM_RET_BASE                1
#define  TCG_GENERAL_ERROR           (TPM_RET_BASE + 0x00)  // A general unidentified error occurred.
#define  TCG_TPM_IS_LOCKED           (TPM_RET_BASE + 0x01)  // The access cannot be granted the device is open.
#define  TCG_NO_RESPONSE             (TPM_RET_BASE + 0x02)  // No response from the TPM device.
#define  TCG_INVALID_RESPONSE        (TPM_RET_BASE + 0x03)  // The response from the TPM was invalid.
#define  TCG_INVALID_ACCESS_REQUEST  (TPM_RET_BASE + 0x04)  // The access parameters for this function are invalid.
#define  TCG_FIRMWARE_ERROR          (TPM_RET_BASE + 0x05)  // Firmware error during start up.
#define  TCG_INTEGRITY_CHECK_FAILED  (TPM_RET_BASE + 0x06)  // Integrity checks of TPM parameter failed.
#define  TCG_INVALID_DEVICE_ID       (TPM_RET_BASE + 0x07)  // The device ID for the TPM is invalid.
#define  TCG_INVALID_VENDOR_ID       (TPM_RET_BASE + 0x08)  // The vendor ID for the TPM is invalid.
#define  TCG_UNABLE_TO_OPEN          (TPM_RET_BASE + 0x09)  // Unable to open a connection to the TPM device.
#define  TCG_UNABLE_TO_CLOSE         (TPM_RET_BASE + 0x0A)  // Unable to close a connection to the TPM device.
#define  TCG_RESPONSE_TIMEOUT        (TPM_RET_BASE + 0x0B)  // Time out for TPM response.
#define  TCG_INVALID_COM_REQUEST     (TPM_RET_BASE + 0x0C)  // The parameters for the communication access are invalid.
#define  TCG_INVALID_ADR_REQUEST     (TPM_RET_BASE + 0x0D)  // The address parameter for the access is invalid.
#define  TCG_WRITE_BYTE_ERROR        (TPM_RET_BASE + 0x0E)  // Bytes write error on the interface.
#define  TCG_READ_BYTE_ERROR         (TPM_RET_BASE + 0x0F)  // Bytes read error on the interface.
#define  TCG_BLOCK_WRITE_TIMEOUT     (TPM_RET_BASE + 0x10)  // Blocks write error on the interface.
#define  TCG_CHAR_WRITE_TIMEOUT      (TPM_RET_BASE + 0x11)  // Bytes write time out on the interface.
#define  TCG_CHAR_READ_TIMEOUT       (TPM_RET_BASE + 0x12)  // Bytes read time out on the interface.
#define  TCG_BLOCK_READ_TIMEOUT      (TPM_RET_BASE + 0x13)  // Blocks read error on the interface.
#define  TCG_TRANSFER_ABORT          (TPM_RET_BASE + 0x14)  // Transfer abort in communication with TPM device.
#define  TCG_INVALID_DRV_FUNCTION    (TPM_RET_BASE + 0x15)  // Function number (AL-Register) invalid for this driver.
#define  TCG_OUTPUT_BUFFER_TOO_SHORT (TPM_RET_BASE + 0x16)  // Output buffer for the TPM response to short.
#define  TCG_FATAL_COM_ERROR         (TPM_RET_BASE + 0x17)  // Fatal error in TPM communication.
#define  TCG_INVALID_INPUT_PARA      (TPM_RET_BASE + 0x18)  // Input parameter for the function invalid.
#define  TCG_TCG_COMMAND_ERROR       (TPM_RET_BASE + 0x19)  // Error during execution of a TCG command.
#define  TCG_INTERFACE_SHUTDOWN      (TPM_RET_BASE + 0x20)  // TPM BIOS interface has been shutdown using the TCG_ShutdownPreBootInterface.
#define  TCG_DRIVER_UNSUPPORTED      (TPM_RET_BASE + 0x21)  // The requested function is not supported.
#define  TCG_DRIVER_TPM_NOT_PRESENT  (TPM_RET_BASE + 0x22)  // The TPM is not installed.
#define  TCG_DRIVER_TPM_DEACTIVATED  (TPM_RET_BASE + 0x23)  // The TPM is deactivated.
#define  TCG_VENDOR_BASE_RET         0x80                   // Start point for return codes are reserved for use by TPM vendors.

UINT32  mTcgLegacyStatus[] = {
  TCG_PC_OK,                                           // #define EFI_SUCCESS               0
  TCG_GENERAL_ERROR,                                   // #define EFI_LOAD_ERROR            EFIERR (1)
  TCG_DRIVER_ERROR (TCG_INVALID_INPUT_PARA),           // #define EFI_INVALID_PARAMETER     EFIERR (2)
  TCG_PC_UNSUPPORTED,                                  // #define EFI_UNSUPPORTED           EFIERR (3)
  TCG_DRIVER_ERROR (TCG_INVALID_INPUT_PARA),           // #define EFI_BAD_BUFFER_SIZE       EFIERR (4)
  TCG_DRIVER_ERROR (TCG_OUTPUT_BUFFER_TOO_SHORT),      // #define EFI_BUFFER_TOO_SMALL      EFIERR (5)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_NOT_READY             EFIERR (6)
  TCG_DRIVER_ERROR (TCG_INVALID_RESPONSE),             // #define EFI_DEVICE_ERROR          EFIERR (7)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_WRITE_PROTECTED       EFIERR (8)
  TCG_PC_LOGOVERFLOW,                                  // #define EFI_OUT_OF_RESOURCES      EFIERR (9)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_VOLUME_CORRUPTED      EFIERR (10)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_VOLUME_FULL           EFIERR (11)
  TCG_DRIVER_ERROR (TCG_DRIVER_TPM_NOT_PRESENT),       // #define EFI_NO_MEDIA              EFIERR (12)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_MEDIA_CHANGED         EFIERR (13)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_NOT_FOUND             EFIERR (14)
  TCG_DRIVER_ERROR (TCG_UNABLE_TO_OPEN),               // #define EFI_ACCESS_DENIED         EFIERR (15)
  TCG_DRIVER_ERROR (TCG_NO_RESPONSE),                  // #define EFI_NO_RESPONSE           EFIERR (16)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_NO_MAPPING            EFIERR (17)
  TCG_DRIVER_ERROR (TCG_CHAR_READ_TIMEOUT),            // #define EFI_TIMEOUT               EFIERR (18)
  TCG_DRIVER_ERROR (TCG_INTERFACE_SHUTDOWN),           // #define EFI_NOT_STARTED           EFIERR (19)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_ALREADY_STARTED       EFIERR (20)
  TCG_DRIVER_ERROR (TCG_TRANSFER_ABORT),               // #define EFI_ABORTED               EFIERR (21)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_ICMP_ERROR            EFIERR (22)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_TFTP_ERROR            EFIERR (23)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_PROTOCOL_ERROR        EFIERR (24)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_INCOMPATIBLE_VERSION  EFIERR (25)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_SECURITY_VIOLATION    EFIERR (26)
  TCG_DRIVER_ERROR (TCG_GENERAL_ERROR),                // #define EFI_CRC_ERROR             EFIERR (27)
};

// INT 1Ah interface status flag
#define  IFCE_OFF        0x1
UINT8    mIfceFlags = 0;

#define LEGACY_TCG_STATUS(Status)   mTcgLegacyStatus[(Status) & ~MAX_BIT]

BOOLEAN    mTpmPresent    = FALSE;

/**
  This function reads 32bit register value from SMM Save State.

  @param Register  Save State register index.
  @param CpuIndex  Cpu Index.

  @return register value
**/
UINT32
ReadRegister32 (
  EFI_SMM_SAVE_STATE_REGISTER  Register,
  UINTN                        CpuIndex
  )
{
  EFI_STATUS                   Status;
  UINT32                       Uint32;

  Status = mSmmCpu->ReadSaveState (
                      mSmmCpu,
                      sizeof (Uint32),
                      Register,
                      CpuIndex,
                      &Uint32
                      );
  ASSERT_EFI_ERROR (Status);

  return Uint32;
}

/**
  This function reads 16bit register value from SMM Save State.

  @param Register  Save State register index.
  @param CpuIndex  Cpu Index.

  @return register value
**/
UINT16
ReadRegister16 (
  EFI_SMM_SAVE_STATE_REGISTER  Register,
  UINTN                        CpuIndex
  )
{
  EFI_STATUS                   Status;
  UINT16                       Uint16;

  Status = mSmmCpu->ReadSaveState (
                      mSmmCpu,
                      sizeof (Uint16),
                      Register,
                      CpuIndex,
                      &Uint16
                      );
  ASSERT_EFI_ERROR (Status);

  return Uint16;
}

/**
  This function writes 32bit register value to SMM Save State.

  @param Register  Save State register index.
  @param CpuIndex  Cpu Index.
  @param Uint32    32bit value.
**/
VOID
WriteRegister32 (
  EFI_SMM_SAVE_STATE_REGISTER  Register,
  UINTN                        CpuIndex,
  UINT32                       Uint32
  )
{
  EFI_STATUS                   Status;

  Status = mSmmCpu->WriteSaveState (
                        mSmmCpu,
                        sizeof (Uint32),
                        Register,
                        CpuIndex,
                        &Uint32
                        );
  ASSERT_EFI_ERROR (Status);
}


/**
  Software SMI handler to handle the INT1A request from CSM16.

  Caution: This function may receive untrusted input.
  TCG INT1A parameter is external input, so this function will do basic validation.
  Each sub function TCG_HashLogExtendEvent, TCG_PassThroughToTPM, TCG_ShutdownPreBootInterface,
  TCG_HashLogEvent, TCG_HashAll, TCG_CompactHashLogExtendEvent, TCG_MemoryOverwriteRequest
  should also do validation based on its own knowledge.
  The basic rule is that the function need make sure the input and outout buffer will not
  override the SMRAM.

  @param DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param Context         Points to an optional handler context which was specified when the
                         handler was registered.
  @param SwContext       A pointer to a collection of data in memory that will
                         be conveyed from a non-SMM environment into an SMM environment.
  @param CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS    The INT1A request is served successfully.

**/
EFI_STATUS
EFIAPI
TcgSmmDispatcher (
  IN EFI_HANDLE                        DispatchHandle,
  IN CONST EFI_SMM_SW_REGISTER_CONTEXT *Context,
  IN OUT EFI_SMM_SW_CONTEXT            *SwContext,
  IN OUT UINTN                         *CommBufferSize
  )
{
  EFI_STATUS                      Status;
  UINT8                           FunctionId;

  Status = EFI_SUCCESS;
  //
  // Get the function ID from AH register
  //
  FunctionId = (UINT8)(ReadRegister16 (EFI_SMM_SAVE_STATE_REGISTER_RAX, SwContext->SwSmiCpuIndex) >> 8);

  if (!mTpmPresent) {
    Status = EFI_NO_MEDIA;
    goto lExit;
  }

  if (FunctionId == TCG_StatusCheck) {
    //
    // It is handled in ReverseThunk
    //
    Status = EFI_UNSUPPORTED;
    goto lExit;
  }

  //
  // The rest of the functions need to look at the TPM state and Interface Off flag
  // (interface off takes precedence over TPM state)
  //
  if ((mIfceFlags & IFCE_OFF) != 0) {
    Status = EFI_NOT_STARTED;
    goto lExit;
  }

  switch (FunctionId) {

  case TCG_HashLogExtendEvent:
  case TCG_PassThroughToTPM:
  case TCG_ShutdownPreBootInterface:
  case TCG_HashLogEvent:
  case TCG_HashAll:
  case TCG_CompactHashLogExtendEvent:
    //
    // It is handled in ReverseThunk
    //
    Status = EFI_UNSUPPORTED;
    break;

  case TCG_MemoryOverwriteRequest:
    {
      IPB_MOR      *Ipb;

      Ipb    = (IPB_MOR *) (UINTN) ReadRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RDI, SwContext->SwSmiCpuIndex);
      if (!SmmIsBufferOutsideSmmValid ((UINTN)Ipb, sizeof (*Ipb))) {
        Status = EFI_INVALID_PARAMETER;
        break;
      }
      Status = mSmmVariable->SmmSetVariable (
                               MEMORY_OVERWRITE_REQUEST_VARIABLE_NAME,
                               &gEfiMemoryOverwriteControlDataGuid,
                               EFI_VARIABLE_NON_VOLATILE |
                                 EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                 EFI_VARIABLE_RUNTIME_ACCESS,
                               sizeof (UINT8),
                               &Ipb->MORBitValue
                               );
      break;
    }
  default:
    {
      FunctionId = TCG_StatusCheck;
      Status = EFI_UNSUPPORTED;
      break;
    }
  }

lExit:
  WriteRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RAX, SwContext->SwSmiCpuIndex, LEGACY_TCG_STATUS (Status));

  return EFI_SUCCESS;
}

/**
  Get the TCG related status and save it locally.

  @param  Event   The Event this notify function registered to.
  @param  Context Pointer to the context data.
**/
VOID
EFIAPI
TcgHandler (
  IN  EFI_EVENT       Event,
  IN  VOID            *Context
  )
{
  EFI_STATUS                        Status;
  UINT32                            FeatureFlags;
  EFI_TCG_PROTOCOL                  *Tcg;
  EFI_PHYSICAL_ADDRESS              EventLogLocation;
  EFI_PHYSICAL_ADDRESS              EventLogLastEntry;

  Status = gBS->LocateProtocol (&gEfiTcgProtocolGuid, NULL, (VOID **) &Tcg);
  if (EFI_ERROR (Status)) {
    return;
  }

  mTpmPresent = TRUE;
  Status = Tcg->StatusCheck (
                  Tcg,
                  &mTcgSmmData.BsCap,
                  &FeatureFlags,
                  &EventLogLocation,
                  &EventLogLastEntry
                  );
  ASSERT_EFI_ERROR (Status);

  if (mTcgSmmData.BsCap.TPMDeactivatedFlag) {
    mIfceFlags |= IFCE_OFF;
  }
}

/**
  Initialize TcgLegacy.

  @param ImageHandle   Pointer to the loaded image protocol for this driver
  @param SystemTable   Pointer to the EFI System Table

  @retval EFI_SUCCESS  The driver initializes correctly.

**/
EFI_STATUS
EFIAPI
InitializeTcgLegacy (
  IN    EFI_HANDLE                  ImageHandle,
  IN    EFI_SYSTEM_TABLE            *SystemTable
  )
{
  EFI_STATUS                        Status;
  EFI_SMM_SW_DISPATCH2_PROTOCOL     *SwDispatch;
  EFI_SMM_SW_REGISTER_CONTEXT       SwContext;
  EFI_HANDLE                        SwHandle;
  EFI_HANDLE                        Handle;
  TCG_LEGACY_INT1A_READY_PROTOCOL   *Int1AReady;

  //
  //  Get the Sw dispatch protocol
  //
  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmSwDispatch2ProtocolGuid,
                    NULL,
                    (VOID**) &SwDispatch
                    );
  ASSERT_EFI_ERROR (Status);
  SwContext.SwSmiInputValue = (UINTN) -1;
  Status = SwDispatch->Register (SwDispatch, (EFI_SMM_HANDLER_ENTRY_POINT2) TcgSmmDispatcher, &SwContext, &SwHandle);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Install the Int1AReady protocol so that the TcgSmmInstallInt1A module can get dispatched.
  // We also pass the SwSmiInputValue to TcgSmmInstallInt1A module.
  //
  Status = gBS->AllocatePool (EfiBootServicesData, sizeof (*Int1AReady), (VOID **) &Int1AReady);
  ASSERT_EFI_ERROR (Status);
  Handle = NULL;
  Int1AReady->SwSmiInputValue = (UINT8) SwContext.SwSmiInputValue;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gTcgLegacyInt1AReadyProtocolGuid, Int1AReady,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Get SMM CPU protocol
  //
  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmCpuProtocolGuid,
                    NULL,
                    (VOID **)&mSmmCpu
                    );
  ASSERT_EFI_ERROR (Status);

  //
  // Locate SmmVariableProtocol
  //
  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmVariableProtocolGuid,
                    NULL,
                    (VOID**)&mSmmVariable
                    );
  ASSERT_EFI_ERROR (Status);

  //
  // Even TCG Protocol is not installed (TPM not present), we still need to handle INT1A
  // Assuming TCG Protocol is installed before SMRAM is closed
  //
  /* Causing Invalid OP CODE exception because the callback is running in a different context (non-SMM mode).
  EfiCreateProtocolNotifyEvent (
    &gEfiTcgProtocolGuid,
    TPL_CALLBACK,
    TcgHandler,
    NULL,
    &mRegisteration
    );
  */
  //
  // Assuming TCG Protocol has been installed.
  //
  TcgHandler (NULL, NULL);

  return EFI_SUCCESS;
}

