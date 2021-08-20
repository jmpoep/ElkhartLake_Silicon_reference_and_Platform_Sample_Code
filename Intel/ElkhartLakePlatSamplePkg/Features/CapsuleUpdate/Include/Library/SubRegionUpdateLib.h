/** @file
  Sub Region update header file.

  Copyright (c) 2018 - 2019, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _SUB_REGION_UPDATE_LIB_H_
#define _SUB_REGION_UPDATE_LIB_H_

#include <PiDxe.h>

#include <Guid/SystemResourceTable.h>

#include <Protocol/FirmwareManagement.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/DevicePathLib.h>
#include <Library/HobLib.h>
#include <Library/PlatformFlashAccessLib.h>

#define B_FMP_HIGH_32BIT_MASK    0xFFFFFFFF00000000

typedef enum {
  TSN_MAC_ADDRESS_SUB_REGION_TYPE = 0,
  OOB_CONFIG_SUB_REGION_TYPE,
  TCC_CONFIG_SUB_REGION_TYPE,
  SIIP_FW_SUB_REGION_TYPE,
  PSE_TSN_IP_CONFIG_SUB_REGION_TYPE,
  TSN_CONFIG_SUB_REGION_TYPE
} SUB_REGION_TYPES;

//
// PSE FW FMP private data structure.
//
typedef struct {
  UINT32 LastAttemptVersion;
  UINT32 LastAttemptStatus;
} SUB_REGION_FMP_LAST_ATTEMPT_VARIABLE;

typedef struct {
  EFI_GUID  *ImageTypeId;
  UINTN     Offset;
  UINT32    FvSize;
} FLASH_SUB_REGION_INFO;

/**
  Write Sub Region. Sub region identified by the Guid in the Sub region FMP private data.

  @param[in]   Image               The SubRegion image buffer.
  @param[in]   ImageSize           The size of SubRegion image buffer in bytes.
  @param[out]  LastAttemptVersion  The last attempt version, which will be recorded in ESRT and FMP EFI_FIRMWARE_IMAGE_DESCRIPTOR.
  @param[out]  LastAttemptStatus   The last attempt status, which will be recorded in ESRT and FMP EFI_FIRMWARE_IMAGE_DESCRIPTOR.
  @param[out]  AbortReason         A pointer to a pointer to a null-terminated string providing more
                                   details for the aborted operation. The buffer is allocated by this function
                                   with AllocatePool(), and it is the caller's responsibility to free it with a
                                   call to FreePool().

  @retval EFI_SUCCESS               The SubRegion image is written.
  @retval EFI_VOLUME_CORRUPTED      The SubRegion image is corrupt.
  @retval EFI_INCOMPATIBLE_VERSION  The SubRegion image version is incorrect.
  @retval EFI_SECURITY_VIOLATION    The SubRegion image fails to load.
  @retval EFI_WRITE_PROTECTED       The flash device is read only.
**/
EFI_STATUS
SubRegionWrite (
  IN  VOID                              *Image,
  IN  UINTN                             ImageSize,
  IN  UINT32                            SubRegionSignature,
  IN  FLASH_SUB_REGION_INFO             *FlashSubRegionInfo,
  OUT CHAR16                            **AbortReason
  );

/*
BOOLEAN
IsImageForSubRegion (
  IN VOID*  Image,
  IN UINT64 ImageSize,
  IN UINT8  RegionType
  );
*/
#endif

