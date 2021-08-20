/** @file
  Produce boot media HOB in PEI phase

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include <Library/BaseLib.h>
#include <Library/BootMediaLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <CpuRegs.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>


/**
  Reads the boot media type from hardware.

  By definition, this function is hardware-specific and implementation may vary to accommodate the method
  use to read the boot device in hardware.

  @retval BOOT_MEDIA_TYPE   The boot media type.
**/
BOOT_MEDIA_TYPE
EFIAPI
GetBootMediaTypeFromHardware (
  VOID
  )
{
  UINT32 AcmStatusPolicyData;

  //
  // Read the boot device from the upper DWORD of the 64-bit Boot Status register
  //
  AcmStatusPolicyData = MmioRead32 (TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_BOOTSTATUS + 0x4);

  if ((AcmStatusPolicyData & B_CPU_BOOT_GUARD_BOOTSTATUS_BLOCK_BOOT_ENABLED) == V_CPU_BOOT_GUARD_BOOTSTATUS_BLOCK_BOOT_ENABLED) {
    return BootMediaUfs;
  }

  return BootMediaSpi;
}

/**
  This function retrieves the NEM map layout structure on a block media boot and produces
  a boot media HOB that will be used for the remainder of the boot.

  @retval     EFI_NOT_FOUND   The boot device indicator could not be found.
  @retval     EFI_SUCCESS     The boot device indicator was found successfully.
**/
EFI_STATUS
EFIAPI
BuildBootMediaHob (
  VOID
  )
{
  BOOT_MEDIA_HOB_DATA BootMediaHobData;
  VOID                *HobPointer;

  ZeroMem (&BootMediaHobData, sizeof (BOOT_MEDIA_HOB_DATA));

  BootMediaHobData.BootMedia = GetBootMediaTypeFromHardware ();
  if (BootMediaHobData.BootMedia == BootMediaMax) {
    return EFI_NOT_FOUND;
  }
  DEBUG ((DEBUG_INFO, "BootMediaHobData.BootMedia: %d\n", BootMediaHobData.BootMedia));
  //
  // Build the BootMediaHob for consumption in BootMediaLib
  //
  HobPointer = BuildGuidDataHob (
                &gBootMediaHobGuid,
                &BootMediaHobData,
                sizeof (BOOT_MEDIA_HOB_DATA)
                );
  ASSERT (HobPointer != NULL);
  DEBUG ((DEBUG_INFO, "HobPointer: 0x%X\n", HobPointer));

  return EFI_SUCCESS;
}

/**
  Build the boot media Hob for consumption in PEI and DXE instances of BootMediaLib

  @param  FileHandle  Handle of the file being invoked.
  @param  PeiServices Describes the list of possible PEI Services.

  @retval EFI_SUCCESS   Produce the BootMedia Hob successfully.

**/
EFI_STATUS
EFIAPI
BootMediaInfoPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS  Status;

  Status = BuildBootMediaHob ();
  ASSERT_EFI_ERROR (Status);

  return Status;
}
