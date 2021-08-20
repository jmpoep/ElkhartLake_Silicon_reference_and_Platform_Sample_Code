//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file

Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _HDD_PASSWORD_DXE_H_
#define _HDD_PASSWORD_DXE_H_

#include <Uefi.h>

#include <IndustryStandard/Atapi.h>
#include <Protocol/AtaPassThru.h>
#include <Protocol/PciIo.h>
#include <Protocol/SmmCommunication.h>
#include <Protocol/HiiConfigAccess.h>

#include <Guid/MdeModuleHii.h>
#include <Guid/PiSmmCommunicationRegionTable.h>

#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiHiiServicesLib.h>
#include <Library/HiiLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseCryptLib.h>

#include <Guid/HddPasswordSecurityVariable.h>
#include <Protocol/HddPasswordNotify.h>

#include "HddPasswordNVDataStruc.h"

//
// This is the generated IFR binary data for each formset defined in VFR.
// This data array is ready to be used as input of HiiAddPackages() to
// create a packagelist (which contains Form packages, String packages, etc).
//
extern UINT8  HddPasswordBin[];

//
// This is the generated String package data for all .UNI files.
// This data array is ready to be used as input of HiiAddPackages() to
// create a packagelist (which contains Form packages, String packages, etc).
//
extern UINT8  HddPasswordDxeStrings[];

#define HDD_PASSWORD_DXE_PRIVATE_SIGNATURE SIGNATURE_32 ('H', 'D', 'D', 'P')

typedef struct _HDD_PASSWORD_CONFIG_FORM_ENTRY {
  LIST_ENTRY                    Link;
  EFI_HANDLE                    Controller;
  UINTN                         Bus;
  UINTN                         Device;
  UINTN                         Function;
  UINT16                        Port;
  UINT16                        PortMultiplierPort;
  CHAR16                        HddString[64];
  EFI_STRING_ID                 TitleToken;
  EFI_STRING_ID                 TitleHelpToken;
  UINT8                         PasswordState;

  HDD_PASSWORD_CONFIG           IfrData;
} HDD_PASSWORD_CONFIG_FORM_ENTRY;

typedef struct _HDD_PASSWORD_DXE_PRIVATE_DATA {
  UINTN                            Signature;
  EFI_HANDLE                       DriverHandle;
  EFI_HII_HANDLE                   HiiHandle;
  EFI_HII_CONFIG_ACCESS_PROTOCOL   ConfigAccess;
  HDD_PASSWORD_CONFIG_FORM_ENTRY   *Current;
} HDD_PASSWORD_DXE_PRIVATE_DATA;

#define HDD_PASSWORD_DXE_PRIVATE_FROM_THIS(a)  CR (a, HDD_PASSWORD_DXE_PRIVATE_DATA, ConfigAccess, HDD_PASSWORD_DXE_PRIVATE_SIGNATURE)

//
//Iterate through the doule linked list. NOT delete safe
//
#define EFI_LIST_FOR_EACH(Entry, ListHead)    \
  for (Entry = (ListHead)->ForwardLink; Entry != (ListHead); Entry = Entry->ForwardLink)

#pragma pack(1)

///
/// HII specific Vendor Device Path definition.
///
typedef struct {
  VENDOR_DEVICE_PATH           VendorDevicePath;
  EFI_DEVICE_PATH_PROTOCOL     End;
} HII_VENDOR_DEVICE_PATH;

#pragma pack()

//
// Time out value for ATA pass through protocol
//
#define ATA_TIMEOUT        EFI_TIMER_PERIOD_SECONDS (3)

//
// The payload length of HDD related ATA commands
//
#define HDD_PAYLOAD                  512

//
// The max retry count specified in ATA 8 spec.
//
#define MAX_HDD_PASSWORD_RETRY_COUNT 5

#endif
