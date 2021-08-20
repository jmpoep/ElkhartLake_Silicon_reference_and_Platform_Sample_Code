/** @file
  This is to publish the SMM Access Ppi instance.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/HobLib.h>
#include <Uefi/UefiBaseType.h>
#include <SmramMemoryReserve.h>

#include <Ppi/SmmAccess.h>
#include <IndustryStandard/Pci22.h>
#include <SaCommonDefinitions.h>

#define SMM_ACCESS_PRIVATE_DATA_SIGNATURE SIGNATURE_32 ('4', '5', 's', 'a')

///
/// SMM configuration register
///
typedef UINT32  SMRAM;  /// System Management RAM Control
///
/// Private data
///
typedef struct {
  UINTN                 Signature;
  EFI_HANDLE            Handle;
  PEI_SMM_ACCESS_PPI    SmmAccess;
  ///
  /// Local Data for SMM Access interface goes here
  ///
  UINTN                 NumberRegions;
  EFI_SMRAM_DESCRIPTOR  *SmramDesc;
} SMM_ACCESS_PRIVATE_DATA;

#define SMM_ACCESS_PRIVATE_DATA_FROM_THIS(a) \
        CR (a, \
          SMM_ACCESS_PRIVATE_DATA, \
          SmmAccess, \
          SMM_ACCESS_PRIVATE_DATA_SIGNATURE \
      )

/**
  This routine accepts a request to "open" a region of SMRAM.  The
  region could be legacy ABSEG, HSEG, or TSEG near top of physical memory.
  The use of "open" means that the memory is visible from all PEIM
  and SMM agents.

  @param[in] This             -  Pointer to the SMM Access Interface.
  @param[in] DescriptorIndex  -  Region of SMRAM to Open.
  @param[in] PeiServices      -  General purpose services available to every PEIM.

  @retval EFI_SUCCESS            -  The region was successfully opened.
  @retval EFI_DEVICE_ERROR       -  The region could not be opened because locked by
                            chipset.
  @retval EFI_INVALID_PARAMETER  -  The descriptor index was out of bounds.
**/
EFI_STATUS
EFIAPI
Open (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN PEI_SMM_ACCESS_PPI         *This,
  IN UINTN                      DescriptorIndex
  )
{
  SMM_ACCESS_PRIVATE_DATA *SmmAccess;

  SmmAccess = SMM_ACCESS_PRIVATE_DATA_FROM_THIS (This);
  if (DescriptorIndex >= SmmAccess->NumberRegions) {
    DEBUG ((DEBUG_WARN, "SMRAM region out of range\n"));

    return EFI_INVALID_PARAMETER;
  } else if (SmmAccess->SmramDesc[DescriptorIndex].RegionState & EFI_SMRAM_LOCKED) {
    ///
    /// Cannot open a "locked" region
    ///
    DEBUG ((DEBUG_WARN, "Cannot open a locked SMRAM region\n"));

    return EFI_DEVICE_ERROR;
  }
  SmmAccess->SmramDesc[DescriptorIndex].RegionState &= (UINT64) ~(EFI_SMRAM_CLOSED | EFI_ALLOCATED);
  SmmAccess->SmramDesc[DescriptorIndex].RegionState |= (UINT64) EFI_SMRAM_OPEN;
  SmmAccess->SmmAccess.OpenState = TRUE;
  return EFI_SUCCESS;
}

/**
  This routine accepts a request to "close" a region of SMRAM.  This is valid for
  compatible SMRAM region.

  @param[in] PeiServices      -  General purpose services available to every PEIM.
  @param[in] This             -  Pointer to the SMM Access Interface.
  @param[in] DescriptorIndex  -  Region of SMRAM to Close.

  @retval EFI_SUCCESS            -  The region was successfully closed.
  @retval EFI_DEVICE_ERROR       -  The region could not be closed because locked by
                            chipset.
  @retval EFI_INVALID_PARAMETER  -  The descriptor index was out of bounds.
**/
EFI_STATUS
EFIAPI
Close (
  IN EFI_PEI_SERVICES        **PeiServices,
  IN PEI_SMM_ACCESS_PPI      *This,
  IN UINTN                   DescriptorIndex
  )
{
  SMM_ACCESS_PRIVATE_DATA *SmmAccess;
  BOOLEAN                 OpenState;
  UINT8                   Index;

  SmmAccess = SMM_ACCESS_PRIVATE_DATA_FROM_THIS (This);
  if (DescriptorIndex >= SmmAccess->NumberRegions) {
    DEBUG ((DEBUG_WARN, "SMRAM region out of range\n"));

    return EFI_INVALID_PARAMETER;
  } else if (SmmAccess->SmramDesc[DescriptorIndex].RegionState & EFI_SMRAM_LOCKED) {
    ///
    /// Cannot close a "locked" region
    ///
    DEBUG ((DEBUG_WARN, "Cannot close a locked SMRAM region\n"));

    return EFI_DEVICE_ERROR;
  }

  if (SmmAccess->SmramDesc[DescriptorIndex].RegionState & EFI_SMRAM_CLOSED) {
    return EFI_DEVICE_ERROR;
  }
  SmmAccess->SmramDesc[DescriptorIndex].RegionState &= (UINT64) ~EFI_SMRAM_OPEN;
  SmmAccess->SmramDesc[DescriptorIndex].RegionState |= (UINT64) (EFI_SMRAM_CLOSED | EFI_ALLOCATED);

  ///
  /// Find out if any regions are still open
  ///
  OpenState = FALSE;
  for (Index = 0; Index < SmmAccess->NumberRegions; Index++) {
    if ((SmmAccess->SmramDesc[Index].RegionState & EFI_SMRAM_OPEN) == EFI_SMRAM_OPEN) {
      OpenState = TRUE;
    }
  }

  SmmAccess->SmmAccess.OpenState = OpenState;
  return EFI_SUCCESS;
}

/**
  This routine accepts a request to "lock" SMRAM.  The
  region could be legacy AB or TSEG near top of physical memory.
  The use of "lock" means that the memory can no longer be opened
  to PEIM.

  @param[in] PeiServices      - General purpose services available to every PEIM.
  @param[in] This             -  Pointer to the SMM Access Interface.
  @param[in] DescriptorIndex  -  Region of SMRAM to Lock.

  @retval EFI_SUCCESS            -  The region was successfully locked.
  @retval EFI_DEVICE_ERROR       -  The region could not be locked because at least
                            one range is still open.
  @retval EFI_INVALID_PARAMETER  -  The descriptor index was out of bounds.
**/
EFI_STATUS
EFIAPI
Lock (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN PEI_SMM_ACCESS_PPI        *This,
  IN UINTN                     DescriptorIndex
  )
{
  SMM_ACCESS_PRIVATE_DATA *SmmAccess;

  SmmAccess = SMM_ACCESS_PRIVATE_DATA_FROM_THIS (This);
  if (DescriptorIndex >= SmmAccess->NumberRegions) {
    DEBUG ((DEBUG_WARN, "SMRAM region out of range\n"));

    return EFI_INVALID_PARAMETER;
  } else if (SmmAccess->SmmAccess.OpenState) {
    DEBUG ((DEBUG_WARN, "Cannot lock SMRAM when SMRAM regions are still open\n"));

    return EFI_DEVICE_ERROR;
  }

  SmmAccess->SmramDesc[DescriptorIndex].RegionState |= (UINT64) EFI_SMRAM_LOCKED;
  SmmAccess->SmmAccess.LockState = TRUE;
  return EFI_SUCCESS;
}

/**
  This routine services a user request to discover the SMRAM
  capabilities of this platform.  This will report the possible
  ranges that are possible for SMRAM access, based upon the
  memory controller capabilities.

  @param[in] PeiServices   - General purpose services available to every PEIM.
  @param[in] This          -  Pointer to the SMRAM Access Interface.
  @param[in] SmramMapSize  -  Pointer to the variable containing size of the
                   buffer to contain the description information.
  @param[in] SmramMap      -  Buffer containing the data describing the Smram
                   region descriptors.

  @retval EFI_BUFFER_TOO_SMALL  -  The user did not provide a sufficient buffer.
  @retval EFI_SUCCESS           -  The user provided a sufficiently-sized buffer.
**/
EFI_STATUS
EFIAPI
GetCapabilities (
  IN EFI_PEI_SERVICES                **PeiServices,
  IN PEI_SMM_ACCESS_PPI              *This,
  IN OUT UINTN                       *SmramMapSize,
  IN OUT EFI_SMRAM_DESCRIPTOR        *SmramMap
  )
{
  EFI_STATUS              Status;
  SMM_ACCESS_PRIVATE_DATA *SmmAccess;
  UINTN                   NecessaryBufferSize;

  SmmAccess           = SMM_ACCESS_PRIVATE_DATA_FROM_THIS (This);
  NecessaryBufferSize = SmmAccess->NumberRegions * sizeof (EFI_SMRAM_DESCRIPTOR);
  if (*SmramMapSize < NecessaryBufferSize) {
    DEBUG ((DEBUG_WARN, "SMRAM Map Buffer too small\n"));

    Status = EFI_BUFFER_TOO_SMALL;
  } else {
    CopyMem (SmramMap, SmmAccess->SmramDesc, NecessaryBufferSize);
    Status = EFI_SUCCESS;
  }

  *SmramMapSize = NecessaryBufferSize;
  return Status;
}

/**
    This is to install an SMM Access PPI

    @retval EFI_SUCCESS           - Protocol successfully started and installed.
    @exception EFI_UNSUPPORTED    - Protocol can't be started.
    @retval EFI_NOT_FOUND         - Protocol can't be found.
    @retval EFI_OUT_OF_RESOURCES  - Protocol does not have enough resources to initialize the driver.
**/
EFI_STATUS
EFIAPI
PeiInstallSmmAccessPpi (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINTN                           Index;
  EFI_PEI_PPI_DESCRIPTOR          *PpiList;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK  *DescriptorBlock;
  SMM_ACCESS_PRIVATE_DATA         *SmmAccessPrivate;
  VOID                            *HobList;
  EFI_BOOT_MODE                   BootMode;

  Status = PeiServicesGetBootMode (&BootMode);
  if (EFI_ERROR (Status)) {
    ///
    /// If not in S3 boot path. do nothing
    ///
    return EFI_SUCCESS;
  }

  if (BootMode != BOOT_ON_S3_RESUME) {
    return EFI_SUCCESS;
  }
  ///
  /// Initialize private data
  ///
  SmmAccessPrivate  = AllocateZeroPool (sizeof (*SmmAccessPrivate));
  ASSERT (SmmAccessPrivate != NULL);
  if (SmmAccessPrivate == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  PpiList           = AllocateZeroPool (sizeof (*PpiList));
  ASSERT (PpiList != NULL);
  if (PpiList == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SmmAccessPrivate->Signature = SMM_ACCESS_PRIVATE_DATA_SIGNATURE;
  SmmAccessPrivate->Handle    = NULL;

  ///
  /// Get Hob list
  ///
  HobList = GetFirstGuidHob (&gEfiSmmPeiSmramMemoryReserveGuid);
  if (HobList == NULL) {
    DEBUG ((DEBUG_WARN, "SmramMemoryReserve HOB not found\n"));
    return EFI_NOT_FOUND;
  }

  DescriptorBlock = (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *) ((UINT8 *) HobList + sizeof (EFI_HOB_GUID_TYPE));

  ///
  /// Alloc space for SmmAccessPrivate->SmramDesc
  ///
  SmmAccessPrivate->SmramDesc = AllocateZeroPool ((DescriptorBlock->NumberOfSmmReservedRegions) * sizeof (EFI_SMRAM_DESCRIPTOR));
  if (SmmAccessPrivate->SmramDesc == NULL) {
    DEBUG ((DEBUG_WARN, "Alloc SmmAccessPrivate->SmramDesc fail.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  DEBUG ((DEBUG_INFO, "Alloc SmmAccessPrivate->SmramDesc success.\n"));

  ///
  /// use the hob to publish SMRAM capabilities
  ///
  for (Index = 0; Index < DescriptorBlock->NumberOfSmmReservedRegions; Index++) {
    SmmAccessPrivate->SmramDesc[Index].PhysicalStart  = DescriptorBlock->Descriptor[Index].PhysicalStart;
    SmmAccessPrivate->SmramDesc[Index].CpuStart       = DescriptorBlock->Descriptor[Index].CpuStart;
    SmmAccessPrivate->SmramDesc[Index].PhysicalSize   = DescriptorBlock->Descriptor[Index].PhysicalSize;
    SmmAccessPrivate->SmramDesc[Index].RegionState    = DescriptorBlock->Descriptor[Index].RegionState;
  }

  SmmAccessPrivate->NumberRegions             = Index;
  SmmAccessPrivate->SmmAccess.Open            = Open;
  SmmAccessPrivate->SmmAccess.Close           = Close;
  SmmAccessPrivate->SmmAccess.Lock            = Lock;
  SmmAccessPrivate->SmmAccess.GetCapabilities = GetCapabilities;
  SmmAccessPrivate->SmmAccess.LockState       = FALSE;
  SmmAccessPrivate->SmmAccess.OpenState       = FALSE;

  ///
  /// Install PPI
  ///
  PpiList->Flags  = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  PpiList->Guid   = &gPeiSmmAccessPpiGuid;
  PpiList->Ppi    = &SmmAccessPrivate->SmmAccess;

  Status          = PeiServicesInstallPpi (PpiList);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}
