/** @file
  Driver for BIOS Info support.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

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

#include <PiPei.h>
#include <BiosInfo.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <IndustryStandard/FirmwareInterfaceTable.h>

#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
#define BIOS_INFO_STRUCT_SIZE 18
#else
#define BIOS_INFO_STRUCT_SIZE 15
#endif


//
// Internal
//
#pragma pack (1)

typedef struct {
  BIOS_INFO_HEADER  Header;
  BIOS_INFO_STRUCT  Entry[BIOS_INFO_STRUCT_SIZE];
} BIOS_INFO;
#pragma pack ()

GLOBAL_REMOVE_IF_UNREFERENCED BIOS_INFO  mBiosInfo = {
  {
    BIOS_INFO_SIGNATURE,
    BIOS_INFO_STRUCT_SIZE,
    0,
  },
  {
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_GENERAL_EXCLUDE_FROM_FIT,
      0x0100,
      FixedPcdGet32 (PcdFlashNvStorageVariableSize) + FixedPcdGet32 (PcdFlashNvStorageFtwWorkingSize) + FixedPcdGet32 (PcdFlashNvStorageFtwSpareSize),
      FixedPcdGet32 (PcdFlashNvStorageVariableBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_GENERAL_EXCLUDE_FROM_FIT,
      0x0100,
      FixedPcdGet32 (PcdFlashFvFirmwareBinariesSize),
      FixedPcdGet32 (PcdFlashFvFirmwareBinariesBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_POST_IBB,
      0x0100,
      FixedPcdGet32 (PcdFlashFvAdvancedSize),
      FixedPcdGet32 (PcdFlashFvAdvancedBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_POST_IBB,
      0x0100,
      FixedPcdGet32 (PcdFlashFvSecuritySize),
      FixedPcdGet32 (PcdFlashFvSecurityBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_POST_IBB,
      0x0100,
      FixedPcdGet32 (PcdFlashFvOsBootSize),
      FixedPcdGet32 (PcdFlashFvOsBootBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_POST_IBB,
      0x0100,
      FixedPcdGet32 (PcdFlashFvUefiBootSize),
      FixedPcdGet32 (PcdFlashFvUefiBootBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_POST_IBB,
      0x0100,
      FixedPcdGet32 (PcdFlashFvPostMemorySize),
      FixedPcdGet32 (PcdFlashFvPostMemoryBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_GENERAL_EXCLUDE_FROM_FIT,
      0x0100,
      FixedPcdGet32 (PcdFlashMicrocodeFvSize),
      FixedPcdGet32 (PcdFlashMicrocodeFvBase)
    },
#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_POST_IBB,
      0x0100,
      FixedPcdGet32 (PcdFlashFvFspSSize),
      FixedPcdGet32 (PcdFlashFvFspSBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      0x00,
      0x0100,
      FixedPcdGet32 (PcdFlashFvFspMSize),
      FixedPcdGet32 (PcdFlashFvFspMBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      0x00,
      0x0100,
      FixedPcdGet32 (PcdFlashFvFspTSize),
      FixedPcdGet32 (PcdFlashFvFspTBase)
    },
#endif
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      0x00,
      0x0100,
      FixedPcdGet32 (PcdFlashFvPreMemorySize),
      FixedPcdGet32 (PcdFlashFvPreMemoryBase)
    },
    {
      FIT_TYPE_01_MICROCODE,
      BIOS_INFO_STRUCT_ATTRIBUTE_MICROCODE_WHOLE_REGION,
      0x0100,
      FixedPcdGet32 (PcdFlashMicrocodeFvSize),
      FixedPcdGet32 (PcdFlashMicrocodeFvBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_GENERAL_EXCLUDE_FROM_FIT,
      0x0100,
      FixedPcdGet32 (PcdFlashFvSiipFwSize),
      FixedPcdGet32 (PcdFlashFvSiipFwBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_GENERAL_EXCLUDE_FROM_FIT,
      0x0100,
      FixedPcdGet32 (PcdFlashFvTsnMacAddressSize),
      FixedPcdGet32 (PcdFlashFvTsnMacAddressBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_GENERAL_EXCLUDE_FROM_FIT,
      0x0100,
      FixedPcdGet32 (PcdFlashFvPseTsnIpConfigSize),
      FixedPcdGet32 (PcdFlashFvPseTsnIpConfigBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_GENERAL_EXCLUDE_FROM_FIT,
      0x0100,
      FixedPcdGet32 (PcdFlashFvTsnConfigSize),
      FixedPcdGet32 (PcdFlashFvTsnConfigBase)
    },
    {
      FIT_TYPE_07_BIOS_STARTUP_MODULE,
      BIOS_INFO_STRUCT_ATTRIBUTE_GENERAL_EXCLUDE_FROM_FIT,
      0x0100,
      FixedPcdGet32 (PcdFlashFvTccConfigSize),
      FixedPcdGet32 (PcdFlashFvTccConfigBase)
    },
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_PPI_DESCRIPTOR  mBiosInfoPpiList = {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gBiosInfoGuid,
  &mBiosInfo
};

/**
  Installs BiosInfo Ppi.

  @param  FileHandle  Handle of the file being invoked.
  @param  PeiServices Describes the list of possible PEI Services.

  @retval EFI_SUCCESS   Install the BiosInfo Ppi successfully.

**/
EFI_STATUS
EFIAPI
BiosInfoEntryPoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS  Status;
  VOID        *HobData;

  //
  // Install PPI, so that other PEI module can add dependency.
  //
  Status = PeiServicesInstallPpi (&mBiosInfoPpiList);
  ASSERT_EFI_ERROR (Status);

  //
  // Build hob, so that DXE module can also get the data.
  //
  HobData = BuildGuidHob (&gBiosInfoGuid, sizeof (mBiosInfo));
  ASSERT (HobData != NULL);
  if (HobData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem (HobData, &mBiosInfo, sizeof (mBiosInfo));

  return EFI_SUCCESS;
}
