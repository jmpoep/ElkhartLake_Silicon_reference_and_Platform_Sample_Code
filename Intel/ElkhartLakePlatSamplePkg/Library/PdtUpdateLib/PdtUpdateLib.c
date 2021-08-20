/** @file

@copyright
INTEL CONFIDENTIAL
Copyright 2017 Intel Corporation.

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

#include <Library/PdtUpdateLib.h>

#pragma pack(1)

//
// PDT file header
//
typedef struct {
  UINT32 MultiPdtId0;  // DWORD filled with all FFs
  UINT32 MultiPdtId1;  // Signature 'M' 'P' 'D' 'T'
  UINT32 PackageSize;  // Size of Multi PDT package
} PDT_HDR;

#pragma pack()

/**

  The function extracts the correct PDT binary from Multi PDT package and returns it.

  @param[in]        PlatformId    Platform ID to be matched to in MultiPDT package
  @param[in]        FileBuffer    Pointer to Multi PDT package
  @param[in]        MultiPdtPackageSize    Size of Multi PDT package
  @param[out]       DestSize      Pointer to the Size of correct PDT file
  @param[out]       ReUseSrcBuf   Pointer to point to PDT file

**/
EFI_STATUS
ExtractPdtBinary (
  IN     UINT32  PlatformId,
  IN     UINT8   *FileBuffer,
  IN     UINT32  MultiPdtPackageSize,
  OUT    UINT16  *DestSize,
  OUT    UINT8   **ReUseSrcBuf
  )
{
  EFI_STATUS              Status;
  PDT_HDR                 *PdtHeader;
  UINT32                  PdtIndex;
  UINT8                   *BufPtr;
  UINT32                  IDCount;
  UINT32                  PdtCompleteSize;
  UINT32                  PlatformIdx;

  PdtIndex        = 0;
  BufPtr          = NULL;
  PdtHeader       = (PDT_HDR*)FileBuffer;
  IDCount         = 0;
  PdtCompleteSize = 0;
  PlatformIdx     = 0;

  if (PdtHeader == NULL) {
    DEBUG ((DEBUG_ERROR, "PDT is NULL. Aborting.\n"));
    return EFI_ABORTED;
  }

  if (PdtHeader->MultiPdtId1 != SIGNATURE_32('M', 'P', 'D', 'T') || PdtHeader->PackageSize != MultiPdtPackageSize) {
    DEBUG ((DEBUG_ERROR, "Invalid PDT header. Aborting.\n"));
    return EFI_ABORTED;
  }

  PdtIndex = sizeof (PDT_HDR);
  BufPtr = FileBuffer + PdtIndex;
  //
  // Special case of single PDT file in the package with no platform ID.
  //
  if ((*(UINT32 *)BufPtr == 1) && (*(UINT32 *)(BufPtr + 4) == 0xFFFFFFFF)) {
    DEBUG ((DEBUG_INFO, "Single PDT binary.\n"));
    IDCount      = *(UINT32 *)BufPtr; // No. of Platform ID count
    *ReUseSrcBuf = BufPtr + IDCount * sizeof (UINT32) + 8; // Start of PDT binary
    *DestSize    = *(UINT16 *)(*ReUseSrcBuf + 2); //Size Read from PDT binary
    Status = EFI_SUCCESS;
    goto Exit;
  }

  Status = EFI_NOT_FOUND; // Will make it Success if valid PDT file is found
  //
  // General condition for Multi PDT binaries.
  //
  for (; PdtIndex < PdtHeader->PackageSize;) {
    PlatformIdx     = 0;
    IDCount         = 0;
    PdtCompleteSize = 0;
    *ReUseSrcBuf    = NULL;
    *DestSize       = 0;
    IDCount         = *(UINT32 *)BufPtr; // No. of Platform ID count
    PdtCompleteSize = *(UINT32 *)(BufPtr + IDCount * sizeof (UINT32) + 4); // size of Pdt binary along with 4 byte alignment
    *ReUseSrcBuf    = BufPtr + IDCount * sizeof (UINT32) + 8; // Start of PDT binary
    *DestSize      = *(UINT16 *)(*ReUseSrcBuf + 2); // Size Read from PDT binary
    for (; PlatformIdx < IDCount; PlatformIdx++) {
      if (PlatformId == *(UINT32 *)(BufPtr + PlatformIdx * sizeof (UINT32) + 4)) {
        Status = EFI_SUCCESS;
        break;
      }
    }
    if (PlatformIdx != IDCount) {
      break;
    }
    BufPtr = *ReUseSrcBuf + PdtCompleteSize; // pointing to next entry of PDT from platform ID
    PdtIndex = PdtIndex + IDCount * sizeof (UINT32) + 8 + PdtCompleteSize; // PdtIndex updated with the size scanned
  }

Exit:
  //
  // Make PDT payload size 2 bytes aligned
  //
  if (*DestSize % 2) {
    *DestSize = *DestSize + 1;
  }
  return Status;
}

/**
  API to Update new PDT file by sending it to ME

  @param[in] PlatformId     Platform ID to be matched to in MultiPDT package
  @param[in] FileBuffer     The pointer to MultiPdt file
  @param[in] MultiPdtSize   MultiPDT file size

  @retval EFI_SUCCESS       Bios2Ish file send complete.

**/

EFI_STATUS
PdtUpdate (
  IN  UINT32  PlatformId,
  IN  UINT8   *FileBuffer,
  IN  UINT32  MultiPdtSize
  )
{
  EFI_STATUS              Status;
  UINT8                   *PdtFileBuffer;
  UINT16                  PdtFileSize;
  static CONST CHAR8      FileName[] = "bios2ish";

  PdtFileBuffer = NULL;
  PdtFileSize = 0;

  DEBUG ((DEBUG_INFO, "Update ISH PDT entry...\n"));

  if (FileBuffer == NULL) {
    DEBUG ((DEBUG_ERROR, "FileBuffer is NULL. Aborting.\n"));
    return EFI_ABORTED;
  }

  Status = ExtractPdtBinary (PlatformId, FileBuffer, MultiPdtSize, &PdtFileSize, &PdtFileBuffer);
  DEBUG ((DEBUG_INFO, "Pdt Binary extracted Status = %r\n", Status));
  DEBUG ((DEBUG_INFO, "PlatformId = 0x%x, PdtFileBuffer = 0x%x, Package Size = 0x%x Binary Size = 0x%x 1st 4 byte = %x\n", PlatformId, (UINTN)PdtFileBuffer, MultiPdtSize, (UINTN)PdtFileSize, *((UINT32*)(UINTN)PdtFileBuffer)));
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = HeciPdtUpdateMsg (FileName, PdtFileBuffer, PdtFileSize);
  DEBUG ((DEBUG_INFO, "PDT Update status= %r\n", Status));

  return Status;
}