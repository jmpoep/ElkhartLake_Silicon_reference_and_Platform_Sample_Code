/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file
  ReverseThunk handler for the INT1A request.

Copyright (c) 1999 - 2017, Intel Corporation. All rights reserved.<BR>
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
#include <Protocol/LegacyBios.h>
#include <Protocol/TcgService.h>
#include <Protocol/TcgLegacyInt1AReady.h>

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/HobLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TpmCommLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseCryptLib.h>

#include "TpmComm.h"
#include "TcgLegacy.h"

#define EV_COMPACT_HASH_TCG_LEGACY             11

#pragma pack (1)
typedef struct TCG_PCR_EVENT {
  TCG_PCRINDEX                      PCRIndex;  ///< PCRIndex event extended to
  TCG_EVENTTYPE                     EventType; ///< TCG EFI event type
  TCG_DIGEST                        Digest;    ///< Value extended into PCRIndex
  UINT32                            EventSize; ///< Size of the event data
  UINT32                            EventData;  ///< The event data
} TCG_LEGACY_PCR_EVENT;
#pragma pack ()

#pragma pack (1)
typedef struct _EFI_TCG_CLIENT_ACPI_TABLE {
  EFI_ACPI_DESCRIPTION_HEADER       Header;
  UINT16                            PlatformClass;
  UINT32                            Laml;
  EFI_PHYSICAL_ADDRESS              Lasa;
} EFI_TCG_CLIENT_ACPI_TABLE;

typedef struct _EFI_TCG_SERVER_ACPI_TABLE {
  EFI_ACPI_DESCRIPTION_HEADER             Header;
  UINT16                                  PlatformClass;
  UINT16                                  Reserved0;
  UINT64                                  Laml;
  EFI_PHYSICAL_ADDRESS                    Lasa;
  UINT16                                  SpecRev;
  UINT8                                   DeviceFlags;
  UINT8                                   InterruptFlags;
  UINT8                                   Gpe;
  UINT8                                   Reserved1[3];
  UINT32                                  GlobalSysInt;
  EFI_ACPI_3_0_GENERIC_ADDRESS_STRUCTURE  BaseAddress;
  UINT32                                  Reserved2;
  EFI_ACPI_3_0_GENERIC_ADDRESS_STRUCTURE  ConfigAddress;
  UINT8                                   PciSegNum;
  UINT8                                   PciBusNum;
  UINT8                                   PciDevNum;
  UINT8                                   PciFuncNum;
} EFI_TCG_SERVER_ACPI_TABLE;

#pragma pack ()

typedef struct _TCG_REVERSE_THUNK_DATA {
  TCG_EFI_BOOT_SERVICE_CAPABILITY   BsCap;
  EFI_TCG_CLIENT_ACPI_TABLE         *TcgClientAcpiTable;
  EFI_TCG_SERVER_ACPI_TABLE         *TcgServerAcpiTable;
  UINTN                             EventLogSize;
  UINT8                             *LastEvent;
  TIS_TPM_HANDLE                    TpmHandle;
} TCG_REVERSE_THUNK_DATA;

EFI_TCG_CLIENT_ACPI_TABLE    mTcgClientAcpiTable;
EFI_TCG_SERVER_ACPI_TABLE    mTcgServerAcpiTable;

TCG_REVERSE_THUNK_DATA       mTcgReverseThunkData = {
  { 0 },
  &mTcgClientAcpiTable,
  &mTcgServerAcpiTable
};

/**
  Parse the event log buffer to get the last event address.
**/
VOID
UpdateLastEventAddress (
  VOID
  )
{
  TCG_PCR_EVENT_HDR     *EventHdr;
  VOID                  *LastEvent;
  EFI_PHYSICAL_ADDRESS   Lasa;

  if (PcdGet8 (PcdTpmPlatformClass) == TCG_PLATFORM_TYPE_CLIENT) {
    Lasa = mTcgReverseThunkData.TcgClientAcpiTable->Lasa;
  }
  else {
    Lasa = mTcgReverseThunkData.TcgServerAcpiTable->Lasa;
  }

  if (Lasa == 0) {
    return;
  }

  LastEvent = NULL;
  for (
    EventHdr = (TCG_PCR_EVENT_HDR *) (UINTN) Lasa;
    EventHdr->PCRIndex != (TCG_PCRINDEX) -1;
    EventHdr = (TCG_PCR_EVENT_HDR *) ((UINT8 *) EventHdr + sizeof (TCG_PCR_EVENT_HDR) + EventHdr->EventSize)
    ) {
    LastEvent = EventHdr;
  }

  ASSERT (LastEvent >= (VOID *) mTcgReverseThunkData.LastEvent);
  mTcgReverseThunkData.LastEvent     = LastEvent;
  mTcgReverseThunkData.EventLogSize  = (UINTN) EventHdr - (UINTN) Lasa;
}

/**
  This service provides EFI protocol capability information, state information
  about the TPM, and Event Log state information.

  @param  ProtocolCapability     The callee allocates memory for a TCG_BOOT_SERVICE_CAPABILITY
                                 structure and fills in the fields with the EFI protocol
                                 capability information and the current TPM state information.
  @param  TCGFeatureFlags        This is a pointer to the feature flags. No feature
                                 flags are currently defined so this parameter
                                 MUST be set to 0. However, in the future,
                                 feature flags may be defined that, for example,
                                 enable hash algorithm agility.
  @param  EventLogLocation       This is a pointer to the address of the event log in memory.
  @param  EventLogLastEntry      If the Event Log contains more than one entry,
                                 this is a pointer to the address of the start of
                                 the last entry in the event log in memory.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_INVALID_PARAMETER  ProtocolCapability does not match TCG capability.
**/
EFI_STATUS
TcgReverseThunkStatusCheck (
  OUT     TCG_EFI_BOOT_SERVICE_CAPABILITY
                                    *ProtocolCapability,
  OUT     UINT32                    *TCGFeatureFlags,
  OUT     EFI_PHYSICAL_ADDRESS      *EventLogLocation,
  OUT     EFI_PHYSICAL_ADDRESS      *EventLogLastEntry
  )
{
  TCG_REVERSE_THUNK_DATA                      *TcgData;

  TcgData = &mTcgReverseThunkData;

  if (ProtocolCapability != NULL) {
    *ProtocolCapability = TcgData->BsCap;
  }

  if (TCGFeatureFlags != NULL) {
    *TCGFeatureFlags = 0;
  }

  if (EventLogLocation != NULL) {
    if (PcdGet8 (PcdTpmPlatformClass) == TCG_PLATFORM_TYPE_CLIENT) {
      *EventLogLocation = TcgData->TcgClientAcpiTable->Lasa;
    } else {
      *EventLogLocation = TcgData->TcgServerAcpiTable->Lasa;
    }
  }

  if (EventLogLastEntry != NULL) {
    if (TcgData->BsCap.TPMDeactivatedFlag) {
      *EventLogLastEntry = (EFI_PHYSICAL_ADDRESS)(UINTN)0;
    } else {
      *EventLogLastEntry = (EFI_PHYSICAL_ADDRESS)(UINTN)TcgData->LastEvent;
    }
  }

  return EFI_SUCCESS;
}

/**
  This service abstracts the capability to do a hash operation on a data buffer.

  @param  HashData               Pointer to the data buffer to be hashed
  @param  HashDataLen            Length of the data buffer to be hashed
  @param  AlgorithmId            Identification of the Algorithm to use for the hashing operation
  @param  HashedDataLen          Resultant length of the hashed data
  @param  HashedDataResult       Resultant buffer of the hashed data

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_INVALID_PARAMETER  HashDataLen is NULL.
  @retval EFI_INVALID_PARAMETER  HashDataLenResult is NULL.
  @retval EFI_OUT_OF_RESOURCES   Cannot allocate buffer of size *HashedDataLen.
  @retval EFI_UNSUPPORTED        AlgorithmId not supported.
  @retval EFI_BUFFER_TOO_SMALL   *HashedDataLen < sizeof (TCG_DIGEST).
**/
EFI_STATUS
EFIAPI
TcgReverseThunkHashAll (
  IN      UINT8                     *HashData,
  IN      UINT64                    HashDataLen,
  IN      TCG_ALGORITHM_ID          AlgorithmId,
  IN OUT  UINT64                    *HashedDataLen,
  IN OUT  UINT8                     **HashedDataResult
  )
{
  BOOLEAN    HashResult;

  if (HashedDataLen == NULL || HashedDataResult == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  switch (AlgorithmId) {
    case TPM_ALG_SHA:
      if (*HashedDataLen < sizeof (TPM_DIGEST)) {
        *HashedDataLen = sizeof (TPM_DIGEST);
        return EFI_BUFFER_TOO_SMALL;
      }
      *HashedDataLen = sizeof (TPM_DIGEST);

      HashResult = Sha1HashAll (
                     HashData,
                     (UINTN) HashDataLen,
                     *HashedDataResult
                     );
      ASSERT (HashResult);
      return EFI_SUCCESS;

    default:
      return EFI_UNSUPPORTED;
  }
}

/**
  Add a new entry to the Event Log.

  @param[in] TcgData       TCG_DXE_DATA structure.
  @param[in] NewEventHdr   Pointer to a TCG_PCR_EVENT_HDR data structure.
  @param[in] NewEventData  Pointer to the new event data.

  @retval EFI_SUCCESS           The new event log entry was added.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.

**/
EFI_STATUS
EFIAPI
TcgReverseThunkLogEventI (
  IN      TCG_REVERSE_THUNK_DATA              *TcgData,
  IN      TCG_PCR_EVENT_HDR         *NewEventHdr,
  IN      UINT8                     *NewEventData
  )
{
  if (PcdGet8 (PcdTpmPlatformClass) == TCG_PLATFORM_TYPE_CLIENT) {
    TcgData->LastEvent = (UINT8*)(UINTN)TcgData->TcgClientAcpiTable->Lasa;
    return TpmCommLogEvent (
             &TcgData->LastEvent,
             &TcgData->EventLogSize,
             (UINTN)TcgData->TcgClientAcpiTable->Laml,
             NewEventHdr,
             NewEventData
             );
  } else {
    TcgData->LastEvent = (UINT8*)(UINTN)TcgData->TcgServerAcpiTable->Lasa;
    return TpmCommLogEvent (
             &TcgData->LastEvent,
             &TcgData->EventLogSize,
             (UINTN)TcgData->TcgServerAcpiTable->Laml,
             NewEventHdr,
             NewEventData
             );
  }
}

/**
  This service abstracts the capability to add an entry to the Event Log.

  @param  This                   Indicates the calling context
  @param  TCGLogData             Pointer to the start of the data buffer containing
                                 the TCG_PCR_EVENT data structure. All fields in
                                 this structure are properly filled by the caller.
  @param  EventNumber            The event number of the event just logged
  @param  Flags                  Indicate additional flags. Only one flag has been
                                 defined at this time, which is 0x01 and means the
                                 extend operation should not be performed. All
                                 other bits are reserved.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_OUT_OF_RESOURCES   Insufficient memory in the event log to complete this action.
**/
EFI_STATUS
EFIAPI
TcgReverseThunkLogEvent (
  IN      EFI_TCG_PROTOCOL          *This,
  IN      TCG_PCR_EVENT             *TCGLogData,
  IN OUT  UINT32                    *EventNumber,
  IN      UINT32                    Flags
  )
{
  TCG_REVERSE_THUNK_DATA  *TcgData;

  TcgData = &mTcgReverseThunkData;

  if (TcgData->BsCap.TPMDeactivatedFlag) {
    return EFI_DEVICE_ERROR;
  }
  return TcgReverseThunkLogEventI (
           TcgData,
           (TCG_PCR_EVENT_HDR*)TCGLogData,
           TCGLogData->Event
           );
}

/**
  This service is a proxy for commands to the TPM.

  @param  TpmInputParameterBlockSize  Size of the TPM input parameter block
  @param  TpmInputParameterBlock      Pointer to the TPM input parameter block
  @param  TpmOutputParameterBlockSize Size of the TPM output parameter block
  @param  TpmOutputParameterBlock     Pointer to the TPM output parameter block

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_INVALID_PARAMETER  Invalid ordinal.
  @retval EFI_UNSUPPORTED        Current Task Priority Level  >= EFI_TPL_CALLBACK.
  @retval EFI_TIMEOUT            The TIS timed-out.
**/
EFI_STATUS
EFIAPI
TcgReverseThunkPassThroughToTpm (
  IN      UINT32                    TpmInputParameterBlockSize,
  IN      UINT8                     *TpmInputParameterBlock,
  IN      UINT32                    TpmOutputParameterBlockSize,
  IN      UINT8                     *TpmOutputParameterBlock
  )
{
  TCG_REVERSE_THUNK_DATA                      *TcgData;

  TcgData = &mTcgReverseThunkData;

  return TisPcExecute (
           TcgData->TpmHandle,
           "%r%/%r",
           TpmInputParameterBlock,
           (UINTN) TpmInputParameterBlockSize,
           TpmOutputParameterBlock,
           (UINTN) TpmOutputParameterBlockSize
           );
}

/**
  Do a hash operation on a data buffer, extend a specific TPM PCR with the hash result,
  and add an entry to the Event Log.

  @param[in]      TcgData       TCG_DXE_DATA structure.
  @param[in]      HashData      Physical address of the start of the data buffer
                                to be hashed, extended, and logged.
  @param[in]      HashDataLen   The length, in bytes, of the buffer referenced by HashData
  @param[in, out] NewEventHdr   Pointer to a TCG_PCR_EVENT_HDR data structure.
  @param[in]      NewEventData  Pointer to the new event data.

  @retval EFI_SUCCESS           Operation completed successfully.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.

**/
EFI_STATUS
EFIAPI
TcgReverseThunkHashLogExtendEventI (
  IN      TCG_REVERSE_THUNK_DATA              *TcgData,
  IN      UINT8                     *HashData,
  IN      UINT64                    HashDataLen,
  IN OUT  TCG_PCR_EVENT_HDR         *NewEventHdr,
  IN      UINT8                     *NewEventData
  )
{
  BOOLEAN                           HashResult;
  EFI_STATUS                        Status;

  if (HashDataLen > 0) {
    HashResult = Sha1HashAll (
                   HashData,
                   (UINTN) HashDataLen,
                   (UINT8 *) &NewEventHdr->Digest
                   );
    ASSERT (HashResult);
  }

  Status = TpmCommExtend (
             TcgData->TpmHandle,
             &NewEventHdr->Digest,
             NewEventHdr->PCRIndex,
             NULL
             );
  if (!EFI_ERROR (Status)) {
    Status = TcgReverseThunkLogEventI (TcgData, NewEventHdr, NewEventData);
  }

  return Status;
}

/**
  This service abstracts the capability to do a hash operation on a data buffer,
  extend a specific TPM PCR with the hash result, and add an entry to the Event Log

  @param  HashData               Physical address of the start of the data buffer
                                 to be hashed, extended, and logged.
  @param  HashDataLen            The length, in bytes, of the buffer referenced by HashData
  @param  AlgorithmId            Identification of the Algorithm to use for the hashing operation
  @param  TCGLogData             The physical address of the start of the data
                                 buffer containing the TCG_PCR_EVENT data structure.
  @param  EventNumber            The event number of the event just logged.
  @param  EventLogLastEntry      Physical address of the first byte of the entry
                                 just placed in the Event Log. If the Event Log was
                                 empty when this function was called then this physical
                                 address will be the same as the physical address of
                                 the start of the Event Log.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_UNSUPPORTED        AlgorithmId != TPM_ALG_SHA.
  @retval EFI_UNSUPPORTED        Current TPL >= EFI_TPL_CALLBACK.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
TcgReverseThunkHashLogExtendEvent (
  IN      EFI_PHYSICAL_ADDRESS      HashData,
  IN      UINT64                    HashDataLen,
  IN      TPM_ALGORITHM_ID          AlgorithmId,
  IN OUT  TCG_PCR_EVENT             *TCGLogData,
  IN OUT  UINT32                    *EventNumber,
     OUT  EFI_PHYSICAL_ADDRESS      *EventLogLastEntry
  )
{
  TCG_REVERSE_THUNK_DATA  *TcgData;

  TcgData = &mTcgReverseThunkData;

  if (TcgData->BsCap.TPMDeactivatedFlag) {
    return EFI_DEVICE_ERROR;
  }

  if (AlgorithmId != TPM_ALG_SHA) {
    return EFI_UNSUPPORTED;
  }

  return TcgReverseThunkHashLogExtendEventI (
           TcgData,
           (UINT8 *) (UINTN) HashData,
           HashDataLen,
           (TCG_PCR_EVENT_HDR*)TCGLogData,
           TCGLogData->Event
           );
}

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
BOOLEAN    mOpbNeedSet[] = {
  FALSE,  // TCG_StatusCheck
  TRUE,   // TCG_HashLogExtendEvent
  TRUE,   // TCG_PassThroughToTPM
  FALSE,  // TCG_ShutdownPreBootInterface
  TRUE,   // TCG_HashLogEvent
  FALSE,  // TCG_HashAll
  FALSE,  // TCG_Tss
  FALSE,  // TCG_CompactHashLogExtendEvent
  FALSE,  // TCG_MemoryOverwriteRequest
};

/**
  Handler to handle the INT1A request from CSM16.

  @param RegSet  Register set context for TCG INT1A services.

  @retval EFI_SUCCESS    The INT1A request is served successfully.

**/
EFI_STATUS
EFIAPI
TcgReverseThunkDispatcher (
  IN OUT EFI_IA32_REGISTER_SET *RegSet
  )
{
  EFI_STATUS                      Status;
  TCG_EFI_BOOT_SERVICE_CAPABILITY Capability;
  EFI_PHYSICAL_ADDRESS            EventLogLocation;
  EFI_PHYSICAL_ADDRESS            EventLogLastEntry;
  UINT32                          FeatureFlags;
  UINT8                           *DigestPointer;
  UINT8                           FunctionId;
  OPB_PASS_THRU                   *OpbStructure;
  UINT32                          EventNumber;
  UINT64                          HashedDataLen;

  Status = EFI_SUCCESS;
  EventNumber = 0;
  //
  // Get the function ID from AH register
  //
  FunctionId = (UINT8)RegSet->H.AH;

  if (FunctionId >= (sizeof (mOpbNeedSet) / sizeof(BOOLEAN))) {
    //
    // Invalid FunctionId is passed, return error.
    //
    FunctionId = TCG_StatusCheck;
    Status = EFI_UNSUPPORTED;
    goto lExit;
  }

  if (!mTpmPresent) {
    Status = EFI_NO_MEDIA;
    goto lExit;
  }

  UpdateLastEventAddress ();

  if (FunctionId == TCG_StatusCheck) {
    Status = TcgReverseThunkStatusCheck (&Capability, &FeatureFlags, &EventLogLocation, &EventLogLastEntry);

    RegSet->E.EBX = SIGNATURE_32 ('T', 'C', 'P', 'A'); // 41504354h
    RegSet->X.CX  = ((UINT16) Capability.ProtocolSpecVersion.Major) << 8 | Capability.ProtocolSpecVersion.Minor;
    RegSet->E.EDX = FeatureFlags;
    RegSet->E.ESI = (UINT32) EventLogLocation;
    RegSet->E.EDI = (UINT32) EventLogLastEntry;

    if ((mIfceFlags & IFCE_OFF) != 0) {
      Status = EFI_NOT_STARTED;
    }
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
    {
      IPB_HASH_LOG_EXTEND_EVENT *Ipb;
      OPB_HASH_LOG_EXTEND_EVENT *Opb;

      Ipb = (IPB_HASH_LOG_EXTEND_EVENT *) (UINTN) RegSet->E.EDI;
      Opb = (OPB_HASH_LOG_EXTEND_EVENT *) (UINTN) RegSet->E.ESI;

      if ((Ipb->Log.LongLog.LogDataLen < OFFSET_OF (TCG_PC_CLIENT_PCR_EVENT, Event)) ||
          (Ipb->Log.LongLog.LogDataLen !=
          ((TCG_PC_CLIENT_PCR_EVENT *) (UINTN) Ipb->Log.LongLog.LogDataPtr)->EventDataSize + OFFSET_OF (TCG_PC_CLIENT_PCR_EVENT, Event))) {
        Status = EFI_INVALID_PARAMETER;
        break;
      }
      if (((TCG_PC_CLIENT_PCR_EVENT *) (UINTN) Ipb->Log.LongLog.LogDataPtr)->PCRIndex != Ipb->PCRIndex) {
        Status = EFI_INVALID_PARAMETER;
        break;
      }

      Status = TcgReverseThunkHashLogExtendEvent (
                 (EFI_PHYSICAL_ADDRESS) (UINTN) Ipb->HashDataPtr,
                 Ipb->HashDataLen,
                 TPM_ALG_SHA,
                 (TCG_PCR_EVENT *) (UINTN) Ipb->Log.LongLog.LogDataPtr,
                 &EventNumber,
                 &EventLogLastEntry
                 );
      if (!EFI_ERROR (Status)) {
        Opb->EventNumber = EventNumber;
        Opb->OPBLength   = sizeof (OPB_HASH_LOG_EXTEND_EVENT);
        CopyMem (Opb->HashValue, ((TCG_PC_CLIENT_PCR_EVENT *) (UINTN)Ipb->Log.LongLog.LogDataPtr)->Digest, sizeof (Opb->HashValue));
      }

      break;
    }

  case TCG_PassThroughToTPM:
    {
      IPB_PASS_THRU        *Ipb;
      OPB_PASS_THRU        *Opb;

      Ipb = (IPB_PASS_THRU *) (UINTN) RegSet->E.EDI;
      Opb = (OPB_PASS_THRU *) (UINTN) RegSet->E.ESI;

      if ((Ipb->IPBLength <= 8) ||
          (Ipb->IPBLength != 8 + (UINT16) SwapBytes32 (((TPM_RQU_COMMAND_HDR *) &Ipb->TPMOperandIn)->paramSize))) {
        Status = EFI_INVALID_PARAMETER;
        break;
      }
      if (Ipb->OPBLength <= 4) {
        Status = EFI_INVALID_PARAMETER;
        break;
      }

      Status = TcgReverseThunkPassThroughToTpm (
                                      Ipb->IPBLength - 8,
                                      &Ipb->TPMOperandIn,
                                      Ipb->OPBLength - 4,
                                      &Opb->TPMOperandOut
                                      );
      if (!EFI_ERROR (Status)) {
        Opb->OPBLength = 4 + (UINT16) SwapBytes32 (((TPM_RSP_COMMAND_HDR *) &Opb->TPMOperandOut)->paramSize);
        //
        // Update output length if what caller gives to me is shorter than we want to receive from TPM
        //
        if (Ipb->OPBLength > Opb->OPBLength) {
          Opb->OPBLength = Ipb->OPBLength;
        }
      }
      break;
    }

  case TCG_ShutdownPreBootInterface:
    {
      mIfceFlags |= IFCE_OFF;
      Status = EFI_SUCCESS;
      break;
    }

  case TCG_HashLogEvent:
    {
      IPB_HASH_LOG_EVENT *Ipb;
      OPB_HASH_LOG_EVENT *Opb;

      Ipb = (IPB_HASH_LOG_EVENT *) (UINTN) RegSet->E.EDI;
      Opb = (OPB_HASH_LOG_EVENT *) (UINTN) RegSet->E.ESI;

      if ((Ipb->LogDataLen < OFFSET_OF (TCG_PC_CLIENT_PCR_EVENT, Event)) ||
          (Ipb->LogDataLen !=
              ((TCG_PC_CLIENT_PCR_EVENT *) (UINTN) Ipb->LogDataPtr)->EventDataSize + OFFSET_OF (TCG_PC_CLIENT_PCR_EVENT, Event))) {
        Status = EFI_INVALID_PARAMETER;
        break;
      }
      if (Ipb->PCRIndex != ((TCG_PC_CLIENT_PCR_EVENT *) (UINTN) Ipb->LogDataPtr)->PCRIndex) {
        Status = EFI_INVALID_PARAMETER;
        break;
      }
      if (Ipb->LogEventType != ((TCG_PC_CLIENT_PCR_EVENT *) (UINTN) Ipb->LogDataPtr)->EventType) {
        Status = EFI_INVALID_PARAMETER;
        break;
      }

      // If either the hash data length or hash data pointer is null we do not need
      // to hash the data since the digest is already included in the event structure.
      //
      if ((Ipb->HashDataLen != 0) && ((UINT8 *) (UINTN) Ipb->HashDataPtr != NULL)) {
        HashedDataLen = sizeof (((TCG_PC_CLIENT_PCR_EVENT *) (UINTN) Ipb->LogDataPtr)->Digest);
        DigestPointer = (UINT8 *) ((TCG_PC_CLIENT_PCR_EVENT *) (UINTN) Ipb->LogDataPtr)->Digest;
        Status = TcgReverseThunkHashAll (
                               (UINT8 *) (UINTN) Ipb->HashDataPtr,
                               Ipb->HashDataLen,
                               TPM_ALG_SHA,
                               &HashedDataLen,
                               &DigestPointer
                               );
        if (EFI_ERROR (Status)) {
          break;
        }
      }
      Status = TcgReverseThunkLogEvent (
                              NULL,
                              (TCG_PCR_EVENT *) (UINTN) Ipb->LogDataPtr,
                              &EventNumber,
                              0x01
                              );
      if (!EFI_ERROR (Status)) {
        Opb->EventNumber = EventNumber;
        Opb->OPBLength   = sizeof (OPB_HASH_LOG_EVENT);
        Opb->Reserved   = 0;
      }

      break;
    }

  case TCG_HashAll:
    {
      IPB_HASH_ALL       *Ipb;
      UINT8              *Digest;

      Ipb    = (IPB_HASH_ALL *) (UINTN) RegSet->E.EDI;
      Digest = (UINT8 *)        (UINTN) RegSet->E.ESI;

      HashedDataLen = 20;
      Status = TcgReverseThunkHashAll (
                 (UINT8 *) (UINTN) Ipb->HashDataPtr,
                 Ipb->HashDataLen,
                 Ipb->AlgorithmID,
                 &HashedDataLen,
                 (UINT8 **) &Digest
                 );
      break;
    }
  case TCG_CompactHashLogExtendEvent:
    {
      UINT8                *HashData;
      TCG_LEGACY_PCR_EVENT Event;
      UINT32               EventData;
      UINT64               HashDataLen;

      HashData    = (UINT8 *) (UINTN) RegSet->E.EDI;
      EventData   =                   RegSet->E.ESI;
      HashDataLen = (UINT64)          RegSet->E.ECX;

      Event.PCRIndex  = RegSet->E.EDX;
      Event.EventType = EV_COMPACT_HASH_TCG_LEGACY;
      Event.EventSize = sizeof (EventData);
      Event.EventData = EventData;

      Status = TcgReverseThunkHashLogExtendEvent (
                 (EFI_PHYSICAL_ADDRESS) (UINTN) HashData,
                 HashDataLen,
                 TPM_ALG_SHA,
                 (TCG_PCR_EVENT *)&Event,
                 &EventNumber,
                 &EventLogLastEntry
                 );
      if (!EFI_ERROR (Status)) {
        RegSet->E.EDX = EventNumber;
        //
        // Work-around for tcgbios check
        //
        RegSet->E.EDX = 1;
      }
      break;
    }
  case TCG_MemoryOverwriteRequest:
    // should use SOFTSMI
    ASSERT(FALSE);
    break;

  default:
    {
      FunctionId = TCG_StatusCheck; // Avoid changing OpbStructure below becauase mOpbNeedSet[TCG_StatusCheck] is FALSE
      Status = EFI_UNSUPPORTED;
      break;
    }
  }

lExit:
  if (EFI_ERROR (Status) && mOpbNeedSet[FunctionId]) {
    OpbStructure = (OPB_PASS_THRU *) (UINTN) RegSet->E.ESI;
    OpbStructure->OPBLength = 4;
    OpbStructure->Reserved  = 0;
  }
  RegSet->E.EAX = LEGACY_TCG_STATUS (Status);

  return EFI_SUCCESS;
}

/**
  Get the TCG related status and save it locally.

  @param  Event   The Event this notify function registered to.
  @param  Context Pointer to the context data.
**/
VOID
EFIAPI
TcgHandlerInit (
  IN  EFI_EVENT       Event,
  IN  VOID            *Context
  )
{
  EFI_STATUS                        Status;
  UINT32                            FeatureFlags;
  EFI_TCG_PROTOCOL                  *Tcg;
  EFI_PHYSICAL_ADDRESS              EventLogLocation;
  EFI_PHYSICAL_ADDRESS              EventLogLastEntry;
  TPM_PERMANENT_FLAGS               PFlags;


  Status = gBS->LocateProtocol (&gEfiTcgProtocolGuid, NULL, (VOID **) &Tcg);
  if (EFI_ERROR (Status)) {
    return;
  }

  mTpmPresent = TRUE;
  Status = Tcg->StatusCheck (
                  Tcg,
                  &mTcgReverseThunkData.BsCap,
                  &FeatureFlags,
                  &EventLogLocation,
                  &EventLogLastEntry
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Also get disable state from TPM hardware
  //
  Status = TpmCommGetFlags (
              (TIS_TPM_HANDLE) (UINTN) TPM_BASE_ADDRESS,
              TPM_CAP_FLAG_PERMANENT,
              &PFlags,
              sizeof (PFlags)
              );

  if (EFI_ERROR (Status) || mTcgReverseThunkData.BsCap.TPMDeactivatedFlag || PFlags.disable) {
    mIfceFlags |= IFCE_OFF;
  } else {
    mTcgReverseThunkData.TpmHandle          = (TIS_TPM_HANDLE)(UINTN)TPM_BASE_ADDRESS;
    if (PcdGet8 (PcdTpmPlatformClass) == TCG_PLATFORM_TYPE_CLIENT){
      mTcgReverseThunkData.TcgClientAcpiTable->Lasa = (UINT64) EventLogLocation;
      mTcgReverseThunkData.TcgClientAcpiTable->Laml = (UINT32) 0x10000; // LAML is 64KB
    }
    else{
      mTcgReverseThunkData.TcgServerAcpiTable->Lasa = (UINT64) EventLogLocation;
      mTcgReverseThunkData.TcgServerAcpiTable->Laml = (UINT32) 0x10000; // LAML is 64KB
    }
    mTcgReverseThunkData.LastEvent          = (UINT8 *) (UINTN) EventLogLastEntry;
    mTcgReverseThunkData.EventLogSize       = (UINT32) (EventLogLastEntry
                                                - EventLogLocation
                                                + sizeof (TCG_PCR_EVENT_HDR)
                                                + ((TCG_PCR_EVENT_HDR *) (UINTN) EventLogLastEntry)->EventSize
                                                );
  }
}
