/** @file
  This is the driver that produce MsegSmram hob

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include <PiPei.h>
#include <SmramMemoryReserve.h>

#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PcdLib.h>

/**
  Retrieves the data structure associated witht he GUIDed HOB of type gEfiSmmPeiSmramMemoryReserveGuid

  @retval NULL   A HOB of type gEfiSmmPeiSmramMemoryReserveGuid could not be found.
  @retval !NULL  A pointer to the GUID data from a HIB of type gEfiSmmPeiSmramMemoryReserveGuid

**/
EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *
GetSrmamHobData (
  VOID
  )
{
  VOID  *GuidHob;

  //
  // Search SmramMemoryReserve HOB that describes SMRAM region
  //
  GuidHob = GetFirstGuidHob (&gEfiSmmPeiSmramMemoryReserveGuid);
  if (GuidHob == NULL) {
    return NULL;
  }
  return (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *)GET_GUID_HOB_DATA (GuidHob);
}

/**
  This routine will split SmramReserve hob to reserve Mseg page for SMRAM content.

  @retval EFI_SUCCESS           The gEfiSmmPeiSmramMemoryReserveGuid is splited successfully.
  @retval EFI_NOT_FOUND         The gEfiSmmPeiSmramMemoryReserveGuid is not found.

**/
EFI_STATUS
EFIAPI
SplitSmramReserveHob (
  VOID
  )
{
  EFI_HOB_GUID_TYPE                *GuidHob;
  EFI_PEI_HOB_POINTERS             Hob;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK   *DescriptorBlock;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK   *NewDescriptorBlock;
  UINTN                            BufferSize;
  UINTN                            SmramRanges;
  UINT32                           MsegSize;
  UINT32                           MsegBase;

  MsegSize = PcdGet32 (PcdCpuMsegSize);

  //
  // Retrieve the GUID HOB data that contains the set of SMRAM descriptyors
  //
  GuidHob = GetFirstGuidHob (&gEfiSmmPeiSmramMemoryReserveGuid);
  if (GuidHob == NULL) {
    DEBUG ((EFI_D_INFO, "Smram HOB not found\n"));
    return EFI_NOT_FOUND;
  }

  DescriptorBlock = (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *)GET_GUID_HOB_DATA (GuidHob);

  //
  // Allocate one extra EFI_SMRAM_DESCRIPTOR to describe a page of SMRAM memory that contains a pointer
  // to the SMM Services Table that is required on the S3 resume path
  //
  SmramRanges = DescriptorBlock->NumberOfSmmReservedRegions;
  BufferSize = sizeof (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK) + (SmramRanges * sizeof (EFI_SMRAM_DESCRIPTOR));

  Hob.Raw = BuildGuidHob (
              &gEfiSmmPeiSmramMemoryReserveGuid,
              BufferSize
              );
  ASSERT (Hob.Raw);
  NewDescriptorBlock = (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *)Hob.Raw;

  //
  // Copy old EFI_SMRAM_HOB_DESCRIPTOR_BLOCK to new allocated region
  //
  CopyMem ((VOID *)Hob.Raw, DescriptorBlock, BufferSize - sizeof(EFI_SMRAM_DESCRIPTOR));

  //
  // Increase the number of SMRAM descriptors by 1 to make room for the ALLOCATED descriptor of size EFI_PAGE_SIZE
  //
  NewDescriptorBlock->NumberOfSmmReservedRegions = (UINT32)(SmramRanges + 1);

  ASSERT (SmramRanges >= 1);
  //
  // Copy last entry to the end - we assume TSEG is last entry, which is same assumption as R8 CPU/SMM driver
  //
  CopyMem (&NewDescriptorBlock->Descriptor[SmramRanges], &NewDescriptorBlock->Descriptor[SmramRanges - 1], sizeof(EFI_SMRAM_DESCRIPTOR));

  //
  // Reduce the size of the last entry with MsegSize.
  //
  ASSERT (NewDescriptorBlock->Descriptor[SmramRanges].PhysicalSize > MsegSize);
  NewDescriptorBlock->Descriptor[SmramRanges].PhysicalSize   -= MsegSize;

  //
  // Add the last but 1 entry with size of MsegSize and put into the ALLOCATED state
  //
  MsegBase = (UINT32)(NewDescriptorBlock->Descriptor[SmramRanges].CpuStart + NewDescriptorBlock->Descriptor[SmramRanges].PhysicalSize);
  NewDescriptorBlock->Descriptor[SmramRanges - 1].PhysicalStart  = MsegBase;
  NewDescriptorBlock->Descriptor[SmramRanges - 1].CpuStart       = MsegBase;
  NewDescriptorBlock->Descriptor[SmramRanges - 1].PhysicalSize   = MsegSize;
  NewDescriptorBlock->Descriptor[SmramRanges - 1].RegionState   |= EFI_ALLOCATED;

  //
  // Last step, we can scrub old one
  //
  ZeroMem (&GuidHob->Name, sizeof(GuidHob->Name));

  return EFI_SUCCESS;
}

/**
  This routine will create MsegSmram hob to hold MsegSmramInfo.

  @retval EFI_SUCCESS           The MsegSmramHob is created successfully.
  @retval EFI_NOT_FOUND         The gEfiSmmPeiSmramMemoryReserveGuid is not found.

**/
EFI_STATUS
EFIAPI
CreateMsegSmramHob (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS             Hob;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK   *DescriptorBlock;
  UINTN                            SmramRanges;

  //
  // Retrieve the GUID HOB data that contains the set of SMRAM descriptyors
  //
  DescriptorBlock = GetSrmamHobData ();
  if (DescriptorBlock == NULL) {
    return EFI_NOT_FOUND;
  }

  Hob.Raw = BuildGuidHob (
              &gMsegSmramGuid,
              sizeof (EFI_SMRAM_DESCRIPTOR)
              );
  ASSERT (Hob.Raw);

  //
  // It should be already patch, so just copy last but 1 region directly.
  //
  SmramRanges = DescriptorBlock->NumberOfSmmReservedRegions;
  ASSERT (SmramRanges >= 2);
  if (SmramRanges >= 2) {
    CopyMem ((VOID *)Hob.Raw, &DescriptorBlock->Descriptor[SmramRanges - 2], sizeof (EFI_SMRAM_DESCRIPTOR));
  }

  return EFI_SUCCESS;
}

/**
  Driver Entry for MsegSmram PEIM

  @param   FileHandle       Handle of the file being invoked.
  @param   PeiServices      Describes the list of possible PEI Services.

  @retval EFI_SUCCESS      Success create gMsegSmramGuid and
                           split gEfiSmmPeiSmramMemoryReserveGuid.
  @retval EFI_NOT_FOUND    Can not get gEfiSmmPeiSmramMemoryReserveGuid hob

**/
EFI_STATUS
EFIAPI
MsegSmramHobEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS              Status;

  if (PcdGet32 (PcdCpuMsegSize) == 0) {
    DEBUG ((EFI_D_INFO, "PcdCpuMsegSize is 0\n"));
    return EFI_SUCCESS;
  }

  //
  // Split SmramReserve hob.
  //
  Status = SplitSmramReserveHob ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Create MsegSmram hob.
  //
  Status = CreateMsegSmramHob ();
  DEBUG ((EFI_D_INFO, "Successfully created Mseg Smram HOB\n"));

  return Status;
}
