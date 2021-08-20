//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
HDD password smm driver which is used to support HDD security feature at s3 path.

Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _HDD_PASSWORD_SMM_H_
#define _HDD_PASSWORD_SMM_H_

#include <PiSmm.h>
#include <IndustryStandard/Atapi.h>

#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmSxDispatch2.h>
#include <Protocol/AtaPassThru.h>
#include <Protocol/PciIo.h>
#include <Protocol/SmmReadyToLock.h>
#include <Protocol/SmmVariable.h>
#include <Protocol/VariableLock.h>
#include <Protocol/HddPasswordNotify.h>
#include <Protocol/SmmEndOfDxe.h>

#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/PciLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/SmmIoLib.h>

#include <Guid/HddPasswordSecurityVariable.h>

#include "IdeMode.h"
#include "AhciMode.h"

//
// Time out value for ATA pass through protocol
//
#define ATA_TIMEOUT                      EFI_TIMER_PERIOD_SECONDS (3)

//
// The payload length of HDD related ATA commands
//
#define HDD_PAYLOAD                      512
//
// According to ATA spec, the max length of hdd password is 32 bytes
//
#define HDD_PASSWORD_MAX_LENGTH          32

#define ATA_SECURITY_SET_PASSWORD_CMD    0xF1
#define ATA_SECURITY_UNLOCK_CMD          0xF2
#define ATA_SECURITY_DIS_PASSWORD_CMD    0xF6

extern VOID                              *mBuffer;

typedef struct {
  UINT32                   Address;
  S3_BOOT_SCRIPT_LIB_WIDTH Width;
} HDD_HC_PCI_REGISTER_SAVE;

//
//Iterate through the doule linked list. NOT delete safe
//

#define EFI_LIST_FOR_EACH(Entry, ListHead)    \
  for (Entry = (ListHead)->ForwardLink; Entry != (ListHead); Entry = Entry->ForwardLink)


//
// Internal function declaration
//

/**
  Performs a serializing operation on all load-from-memory instructions that
  were issued prior the InternalAsmLfence function.

  Executes a LFENCE instruction. This function is only available on IA-32 and x64.

**/
VOID
EFIAPI
InternalAsmLfence (
  VOID
  );

#endif

