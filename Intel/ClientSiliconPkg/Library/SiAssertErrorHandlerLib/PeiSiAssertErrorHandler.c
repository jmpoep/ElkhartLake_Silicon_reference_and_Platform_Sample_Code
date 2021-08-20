/** @file
  Library functions for Pei Silicon Assert Error Handler.

Copyright (c) 2018 - 2019, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiPei.h>
#include <IpStatusHob.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#ifdef FSP_FLAG
#include <Library/FspCommonLib.h>
#include <Library/FspSwitchStackLib.h>
#endif

static EFI_PEI_PPI_DESCRIPTOR  mSiInitErrorNotifyList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gSiInitErrorPpiGuid,
    NULL
  }
};

/**
  The function executes error handling. For FSP API mode, return to boot loader.
  For EDK2 or FSP non-API mode, install a PPI SiInitErrorNotify, boot loader or
  platform code can handle such errors.

  @param[in] Status      The return status.

  @retval None.
**/
VOID
ErrorHandling (
  IN  EFI_STATUS  Status
  )
{
#ifdef FSP_FLAG
  volatile BOOLEAN  LoopUntilReset;

  LoopUntilReset = TRUE;
  if (GetFspGlobalDataPointer()->FspMode == FSP_IN_API_MODE) {
    do {
      SetFspApiReturnStatus (Status);
      Pei2LoaderSwitchStack ();
    } while (LoopUntilReset);
  } else {
    PeiServicesInstallPpi (mSiInitErrorNotifyList);
  }
#else
  PeiServicesInstallPpi (mSiInitErrorNotifyList);
#endif
}

/**
  Silicon assertion error handling, creating HOB for error status and
  handling errors according to what types of mode.

  @param[in] Status      The return status.
  @param[in] HobGuid     The GUID to build a guid hob.

  @retval None.
**/
VOID
SiAssertErrorHandler (
  IN  CONST CHAR8 *FileName,
  IN  UINTN       LineNumber,
  IN  EFI_STATUS  Status,
  IN  EFI_GUID    *HobGuid
  )
{
  IP_STATUS_HOB   *IpStatusHob;

  IpStatusHob = NULL;

  if (EFI_ERROR (Status)) {
    IpStatusHob = BuildGuidHob (&gIpStatusHobGuid, sizeof (IP_STATUS_HOB));
    if (IpStatusHob != NULL) {
      IpStatusHob->Status = Status;
      CopyGuid (&IpStatusHob->Guid, HobGuid);
    }
    DEBUG ((DEBUG_ERROR, "\nENTER ERROR HANDLING: %a(%d), Status = %r\n", FileName, LineNumber, Status));
    ErrorHandling (Status);
  }
}

