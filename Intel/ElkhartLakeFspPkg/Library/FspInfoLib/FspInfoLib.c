/** @file
  FSP Information Library.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PcdLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/FspCommonLib.h>
#include <Library/HobLib.h>
#include <FspEas.h>
#include <Library/FspInfoLib.h>

//
// FSP Header Data structure from FspHeader driver.
//
#pragma pack(1)
///
/// FSP Producer Data Subtype - 1
///
typedef struct {
  ///
  /// Byte 0x00: Length of this FSP producer data type record.
  ///
  UINT16  Length;
  ///
  /// Byte 0x02: FSP producer data type.
  ///
  UINT8   Type;
  ///
  /// Byte 0x03: Revision of this FSP producer data type.
  ///
  UINT8   Revision;
  ///
  /// Byte 0x04: 4 byte field of RC version which is used to build this FSP image.
  ///
  UINT32  RcVersion;
  ///
  /// Byte 0x08: Represents the build time stamp "YYYYMMDDHHMM".
  ///
  UINT8  BuildTimeStamp[12];
} FSP_PRODUCER_DATA_TYPE1;

typedef struct {
  FSP_INFO_HEADER          FspInfoHeader;
  FSP_INFO_EXTENDED_HEADER FspInfoExtendedHeader;
  FSP_PRODUCER_DATA_TYPE1  FspProduceDataType1;
  FSP_PATCH_TABLE          FspPatchTable;
} TABLES;

#pragma pack()

/**
  Dump FSP Information.

  @param[in]  None

  @retval     None.

**/
VOID
EFIAPI
DumpFspInfo (
  IN FSP_INFO_HOB *FspInfo
  )
{

  DEBUG ((DEBUG_INFO, "=====================================\n"));

  if (FspInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "FSP Information pointer is NULL\n"));
    return;
  }

  DEBUG ((DEBUG_INFO,
          "FSP Version : %02x.%02x.%02x.%02x\n",
          FspInfo->SiliconInitVersionMajor,
          FspInfo->SiliconInitVersionMinor,
          FspInfo->FspVersionRevision,
          FspInfo->FspVersionBuild
          ));

  DEBUG ((DEBUG_INFO,
          "RC Version  : %02x.%02x.%02x.%02x\n",
          FspInfo->SiliconInitVersionMajor,
          FspInfo->SiliconInitVersionMinor,
          FspInfo->SiliconInitVersionRevision,
          FspInfo->SiliconInitVersionBuild
          ));

  DEBUG ((DEBUG_INFO, "Build Date  : %.12a\n", FspInfo->TimeStamp));

  DEBUG ((DEBUG_INFO, "=====================================\n"));
}

/**
  Get FSP Information

  @param[in out]  FspInfo     Pointer to FSP INFO buffer to store the data of FSP information.

  @retval EFI_SUCCESS    Get the FSP information successfully.
          EFI_NOT_FOUND  Can't find FSP header to get FSP information.
          EFI_INVALID_PARAMETER  FspInfo pointer is NULL.

**/
EFI_STATUS
EFIAPI
GetFspInfo (
  IN OUT FSP_INFO_HOB *FspInfo
  )
{
  TABLES           *FsptTable;
  FSP_GLOBAL_DATA  *FspData;

  FsptTable = NULL;

  if (FspInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  FspData = GetFspGlobalDataPointer ();
  if (FspData->FspMode == FSP_IN_API_MODE) {
    FsptTable = (TABLES *) GetFspInfoHeaderFromApiContext ();
  } else {
    FsptTable = (TABLES *) FspData->FspInfoHeader;
  }
  if (FsptTable == NULL) {
    return EFI_NOT_FOUND;
  }

  FspInfo->SiliconInitVersionMajor = PcdGet8 (PcdSiliconInitVersionMajor);
  FspInfo->SiliconInitVersionMinor = PcdGet8 (PcdSiliconInitVersionMinor);
  FspInfo->SiliconInitVersionRevision = PcdGet8 (PcdSiliconInitVersionRevision);
  FspInfo->SiliconInitVersionBuild = PcdGet8 (PcdSiliconInitVersionBuild);
  FspInfo->FspVersionRevision = PcdGet8 (PcdFspVersionRevision);
  FspInfo->FspVersionBuild = PcdGet8 (PcdFspVersionBuild);

  CopyMem (FspInfo->TimeStamp, FsptTable->FspProduceDataType1.BuildTimeStamp, 12);

  return EFI_SUCCESS;
}