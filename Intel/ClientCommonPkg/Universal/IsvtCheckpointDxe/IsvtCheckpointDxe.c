/** @file
  Status Code Handler Driver which produces ISVT handler.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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


#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/ReportStatusCodeHandler.h>
#include <Guid/EventGroup.h>
#include <Library/PcdLib.h>
#include <Protocol/Smbios.h>
#include <IndustryStandard/SmBios.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>

#define ISVT_END_OF_MRC_STATE        0x10
#define ISVT_END_OF_DXE_STATE        0x20
#define ISVT_READY_TO_BOOT_STATE     0x30
#define ISVT_AFTER_OS_BOOTING        0x40

#pragma pack(1)
typedef struct {
  UINT8   Type;
  UINT8   Length;
  UINT16  Handle;
  UINT8   IsvtVersion;
  UINT16  IoPort;
  UINT8   EntryCount;
  UINT8   CheckPoint1;
  UINT8   String1;
  UINT8   CheckPoint2;
  UINT8   String2;
  UINT8   CheckPoint3;
  UINT8   String3;
} SMBIOS_TABLE_ISVT;
#pragma pack()

#define ISVT_ENTRY_COUNT  3
CHAR8 *mSmbiosIsvtStrings[] = {
  "Memory Init Complete",
  "End of DXE Phase",
  "BIOS Boot Complete"
};

CHAR8 *mSmbiosIsvtGroupNameString[] = {
  "Intel(R) Silicon View Technology"
};

EFI_RSC_HANDLER_PROTOCOL  *mRscHandlerProtocol = NULL;
EFI_SMBIOS_PROTOCOL       *mSmbios = NULL;

/**
  Intel Silicon View Technology check point interface based on IO port reading

  @param CheckPoint        Check point AH value.
                           AH = 0x10:  End of MRC State
                           AH = 0x20:  End of DXE State
                           AH = 0x30:  Read to boot before INT-19h or UEFI boot
                           AH = 0x40:  After OS booting, need a timer SMI trigger to implement (TBD)

  @param PortReading       IO port reading address used for breakpoints
**/
VOID
EFIAPI
IsvtCheckpoint (
  UINTN  CheckPoint,
  UINTN  PortReading
  );

/**
  ISVT check point event call back function

  @param[in] Event      Event handle
  @param[in] Context    Event context
**/
VOID
EFIAPI
IsvtCheckpointEvent1 (
  IN EFI_EVENT          Event,
  IN VOID              *Context
  )
{
  IsvtCheckpoint (ISVT_END_OF_DXE_STATE , PcdGet8 (PcdIsvtIoPort));
}

VOID
EFIAPI
IsvtCheckpointEvent2 (
  IN EFI_EVENT          Event,
  IN VOID              *Context
  )
{
  IsvtCheckpoint (ISVT_READY_TO_BOOT_STATE , PcdGet8 (PcdIsvtIoPort));
}

/**
  Add ISVT Smbios table

  @param[in] Event      Event handle
  @param[in] Context    Event context
**/
VOID
EFIAPI
AddIsvtSmbiosTable (
  IN EFI_EVENT          Event,
  IN VOID              *Context
  )
{

  EFI_SMBIOS_HANDLE     SmbiosHandle;
  SMBIOS_TABLE_ISVT     *IsvtRecord;
  SMBIOS_TABLE_TYPE14   *IsvtSmbiosType14;
  CHAR8                 *StringPtr;
  UINTN                 StringSize;
  UINT8                 i;

  //
  // count string size before allocate memory
  //
  StringSize = 0;
  for (i = 0; i < (ISVT_ENTRY_COUNT); i++) {
    StringSize += AsciiStrSize (mSmbiosIsvtStrings[i]);
  }

  IsvtRecord = (SMBIOS_TABLE_ISVT *) AllocateZeroPool(sizeof(SMBIOS_TABLE_ISVT) + StringSize + ISVT_ENTRY_COUNT + 1);
  if (IsvtRecord == NULL) {
    return;
  }

  //
  // fill table values
  //
  IsvtRecord->Type        = PcdGet8 (PcdIsvtSmbiosType);
  IsvtRecord->Length      = sizeof(SMBIOS_TABLE_ISVT);
  IsvtRecord->IsvtVersion = 1;
  IsvtRecord->IoPort      = PcdGet8 (PcdIsvtIoPort);
  IsvtRecord->EntryCount  = ISVT_ENTRY_COUNT;
  IsvtRecord->CheckPoint1 = ISVT_END_OF_MRC_STATE;
  IsvtRecord->String1     = 1;
  IsvtRecord->CheckPoint2 = ISVT_END_OF_DXE_STATE;
  IsvtRecord->String2     = 2;
  IsvtRecord->CheckPoint3 = ISVT_READY_TO_BOOT_STATE;
  IsvtRecord->String3     = 3;

  //
  // append strings to the tail of table
  //
  StringPtr = ((CHAR8 *)IsvtRecord) + IsvtRecord->Length;
  for (i = 0; i < (ISVT_ENTRY_COUNT); i++) {
    AsciiStrCpyS (StringPtr, AsciiStrSize (mSmbiosIsvtStrings[i]), mSmbiosIsvtStrings[i]);
    StringPtr += AsciiStrSize (mSmbiosIsvtStrings[i]);
  }

  //
  // add Smbios table
  //
  if (mSmbios == NULL){
    gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **)&mSmbios);
  }
  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  mSmbios->Add (mSmbios, NULL, &SmbiosHandle, (EFI_SMBIOS_TABLE_HEADER *)IsvtRecord);

  //
  // prepare Isvt smbios type14 table
  //
  //
  // count string size before allocate memory
  //
  StringSize = 0;
  StringSize += AsciiStrSize (mSmbiosIsvtGroupNameString[0]);

  IsvtSmbiosType14 = (SMBIOS_TABLE_TYPE14 *) AllocateZeroPool(sizeof(SMBIOS_TABLE_TYPE14) + StringSize + 1);
  if (IsvtSmbiosType14 == NULL) {
    return;
  }
  //
  // fill table values
  //
  IsvtSmbiosType14->Hdr.Type            = 14;
  IsvtSmbiosType14->Hdr.Length          = sizeof(SMBIOS_TABLE_TYPE14);
  IsvtSmbiosType14->GroupName           = 1;
  IsvtSmbiosType14->Group[0].ItemType   = PcdGet8 (PcdIsvtSmbiosType);
  IsvtSmbiosType14->Group[0].ItemHandle = SmbiosHandle;

  //
  // append strings to the tail of table
  //
  StringPtr = ((CHAR8 *)IsvtSmbiosType14) + IsvtSmbiosType14->Hdr.Length;
  AsciiStrCpyS (StringPtr, AsciiStrSize (mSmbiosIsvtGroupNameString[0]), mSmbiosIsvtGroupNameString[0]);

  //
  // add Smbios table
  //
  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  mSmbios->Add (mSmbios, NULL, &SmbiosHandle, (EFI_SMBIOS_TABLE_HEADER *)IsvtSmbiosType14);

}

/**
  Entry point of DXE Status Code Driver.

  This function is the entry point of this DXE Status Code Driver.
  It initializes registers status code handlers.

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
InitializeIsvtCheckpoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                Status;
  EFI_EVENT                 EventHandle;
  EFI_EVENT                 IsvtSmbiosEvent;
  VOID                      *IsvtSmbiosEventRegistration;

  Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **)&mSmbios);
  if (Status == EFI_NOT_FOUND) {
    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    AddIsvtSmbiosTable,
                    NULL,
                    &IsvtSmbiosEvent
                    );
    ASSERT_EFI_ERROR (Status);

    Status = gBS->RegisterProtocolNotify (
                    &gEfiSmbiosProtocolGuid,
                    IsvtSmbiosEvent,
                    &IsvtSmbiosEventRegistration
                    );
    ASSERT_EFI_ERROR (Status);
  } else {
    AddIsvtSmbiosTable (NULL, NULL);
  }

  //
  // create event for check point "0x20 - End of DXE Phase"
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  IsvtCheckpointEvent1,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EventHandle
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // create event for check point "0x30 - BIOS Boot Complete"
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  IsvtCheckpointEvent2,
                  NULL,
                  &gEfiEventReadyToBootGuid,
                  &EventHandle
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
