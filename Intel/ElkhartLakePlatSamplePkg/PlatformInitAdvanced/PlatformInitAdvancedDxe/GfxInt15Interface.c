/** @file
  This is a driver to produce Int15 hook.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

//
// Module specific Includes
//
#include "PlatformInitAdvancedDxe.h"
#include <Uefi/UefiBaseType.h>
#include <Protocol/FirmwareVolume2.h>


/**
  Loads real mode file form the FV

  @param[in]  Guid
  @param[in]  Buffer
  @param[in]  BufferSize

  @retval     EFI_SUCCESS  Function has completed successfully.
**/
EFI_STATUS
LoadRealModeFile (
  EFI_GUID *Guid,
  VOID     **Buffer,
  UINTN    *BufferSize
  )
{
  EFI_FIRMWARE_VOLUME2_PROTOCOL   *Fv;
  UINT32                          Authentication;
  EFI_STATUS                      Status;
  UINTN                           NumHandles;
  EFI_HANDLE                      *HandleBuffer;
  UINTN                           Index;

  *Buffer     = NULL;
  *BufferSize = 0;
  Fv          = NULL;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolume2ProtocolGuid,
                  NULL,
                  &NumHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status)) return Status;

  for (Index = 0; Index < NumHandles; ++Index) {
    Status = gBS->HandleProtocol (HandleBuffer[Index], &gEfiFirmwareVolume2ProtocolGuid, (VOID **) &Fv);
    if (EFI_ERROR(Status)) continue;

    Status = Fv->ReadSection(Fv,
                             Guid,
                             EFI_SECTION_RAW,
                             0,              //Instance
                             Buffer,
                             BufferSize,
                             &Authentication);

    if (Status == EFI_SUCCESS) break;
  }

  (gBS->FreePool)(HandleBuffer);
  return Status;
}

