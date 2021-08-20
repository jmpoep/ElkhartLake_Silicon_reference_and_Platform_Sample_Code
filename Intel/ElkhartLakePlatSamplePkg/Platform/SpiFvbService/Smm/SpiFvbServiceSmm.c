/** @file
  Common driver source for several Serial Flash devices
  which are compliant with the Intel(R) Serial Flash Interface Compatibility Specification.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

#include "SpiFvbServiceCommon.h"
#include <Library/SmmServicesTableLib.h>
#include <Protocol/SmmFirmwareVolumeBlock.h>
#include <Library/PciSegmentLib.h>
#include <Library/SpiAccessLib.h>

/**
  The function installs EFI_FIRMWARE_VOLUME_BLOCK protocol
  for each FV in the system.

  @param[in]  FvbInstance   The pointer to a FW volume instance structure,
                            which contains the information about one FV.

  @retval     VOID

**/
VOID
InstallFvbProtocol (
  IN  EFI_FVB_INSTANCE               *FvbInstance
  )
{
  EFI_FIRMWARE_VOLUME_HEADER            *FvHeader;
  EFI_STATUS                            Status;
  EFI_HANDLE                            FvbHandle;

  ASSERT (FvbInstance != NULL);
  if (FvbInstance == NULL) {
    return;
  }

  CopyMem (&FvbInstance->FvbProtocol, &mFvbProtocolTemplate, sizeof (EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL));

  FvHeader = &FvbInstance->FvHeader;
  if (FvHeader == NULL) {
    return;
  }

  //
  // Set up the devicepath
  //
  DEBUG ((DEBUG_INFO, "FwBlockService.c: Setting up DevicePath for 0x%lx:\n", FvbInstance->FvBase));
  if (FvHeader->ExtHeaderOffset == 0) {
    //
    // FV does not contains extension header, then produce MEMMAP_DEVICE_PATH
    //
    FvbInstance->DevicePath = (EFI_DEVICE_PATH_PROTOCOL *) AllocateRuntimeCopyPool (sizeof (FV_MEMMAP_DEVICE_PATH), &mFvMemmapDevicePathTemplate);
    if (FvbInstance->DevicePath == NULL) {
      DEBUG ((DEBUG_INFO, "SpiFvbServiceSmm.c: Memory allocation for MEMMAP_DEVICE_PATH failed\n"));
      return;
    }
    ((FV_MEMMAP_DEVICE_PATH *) FvbInstance->DevicePath)->MemMapDevPath.StartingAddress = FvbInstance->FvBase;
    ((FV_MEMMAP_DEVICE_PATH *) FvbInstance->DevicePath)->MemMapDevPath.EndingAddress   = FvbInstance->FvBase + FvHeader->FvLength - 1;
  } else {
    FvbInstance->DevicePath = (EFI_DEVICE_PATH_PROTOCOL *) AllocateRuntimeCopyPool (sizeof (FV_PIWG_DEVICE_PATH), &mFvPIWGDevicePathTemplate);
    if (FvbInstance->DevicePath == NULL) {
      DEBUG ((DEBUG_INFO, "SpiFvbServiceSmm.c: Memory allocation for FV_PIWG_DEVICE_PATH failed\n"));
      return;
    }
    CopyGuid (
      &((FV_PIWG_DEVICE_PATH *)FvbInstance->DevicePath)->FvDevPath.FvName,
      (GUID *)(UINTN)(FvbInstance->FvBase + FvHeader->ExtHeaderOffset)
      );
  }

  //
  // LocateDevicePath fails so install a new interface and device path
  //
  FvbHandle = NULL;

  Status = gSmst->SmmInstallProtocolInterface (
                    &FvbHandle,
                    &gEfiSmmFirmwareVolumeBlockProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &(FvbInstance->FvbProtocol)
                    );
  ASSERT_EFI_ERROR (Status);

  Status = gSmst->SmmInstallProtocolInterface (
                    &FvbHandle,
                    &gEfiDevicePathProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &(FvbInstance->DevicePath)
                    );
  ASSERT_EFI_ERROR (Status);
}

/**

  The function does the necessary initialization work for
  Firmware Volume Block Driver.

  @param[in]  ImageHandle       The firmware allocated handle for the UEFI image.
  @param[in]  SystemTable       A pointer to the EFI system table.

  @retval     EFI_SUCCESS       This funtion always return EFI_SUCCESS.
                                It will ASSERT on errors.

**/
EFI_STATUS
EFIAPI
FvbInitialize (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_FVB_INSTANCE                      *FvbInstance;
  EFI_FIRMWARE_VOLUME_HEADER            *FvHeader;
  EFI_FV_BLOCK_MAP_ENTRY                *PtrBlockMapEntry;
  EFI_PHYSICAL_ADDRESS                  BaseAddress;
  EFI_STATUS                            Status;
  UINTN                                 BufferSize;
  UINTN                                 Idx;
  UINT32                                MaxLbaSize;
  UINT32                                BytesWritten;
  UINTN                                 BytesErased;

  //
  // Return if the boot media is not SPI
  //
  if (!BootMediaIsSpi () || !PcdGetBool (PcdEnableFvbVariableStorage)) {
    return EFI_SUCCESS;
  }
  //
  // We will only continue with FVB installation if the
  // SPI is the active BIOS state
  //
  if (!SpiIsBiosBootFromSpi ()) {
    return EFI_UNSUPPORTED;
  }

  //
  // Make sure all FVB are valid and/or fix if possible
  //
  for (Idx = 0; Idx < mPlatformFvBaseAddressCount; Idx++) {
    BaseAddress = mPlatformFvBaseAddress[Idx].FvBase;
    FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) BaseAddress;

    if (!IsFvHeaderValid (BaseAddress, FvHeader)) {
      BytesWritten = 0;
      BytesErased = 0;
      DEBUG ((DEBUG_ERROR, "ERROR - The FV in 0x%x is invalid!\n", FvHeader));
      Status = GetFvbInfo (BaseAddress, &FvHeader);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "ERROR - Can't recovery FV header at 0x%x.  GetFvbInfo Status %r\n", BaseAddress, Status));
        continue;
      }
      DEBUG ((DEBUG_INFO, "Rewriting FV header at 0x%X with static data\n", BaseAddress));
      //
      // Spi erase
      //
      BytesErased = (UINTN) FvHeader->BlockMap->Length;
      Status = SpiFlashBlockErase( (UINTN) BaseAddress, &BytesErased);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "ERROR - SpiFlashBlockErase Error  %r\n", Status));
        continue;
      }
      if (BytesErased != FvHeader->BlockMap->Length) {
        DEBUG ((DEBUG_ERROR, "ERROR - BytesErased != FvHeader->BlockMap->Length\n"));
        DEBUG ((DEBUG_ERROR, " BytesErased = 0x%X\n Length = 0x%X\n", BytesErased, FvHeader->BlockMap->Length));
        continue;
      }
      BytesWritten = FvHeader->HeaderLength;
      Status = SpiFlashWrite (BaseAddress, &BytesWritten, (UINT8*)FvHeader);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "ERROR - SpiFlashWrite Error  %r\n", Status));
        continue;
      }
      if (BytesWritten != FvHeader->HeaderLength) {
        DEBUG ((DEBUG_ERROR, "ERROR - BytesWritten != HeaderLength\n"));
        DEBUG ((DEBUG_ERROR, " BytesWritten = 0x%X\n HeaderLength = 0x%X\n", BytesWritten, FvHeader->HeaderLength));
        continue;
      }
      Status = SpiFlashLock ();
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "ERROR - SpiFlashLock Error  %r\n", Status));
        continue;
      }
      DEBUG ((DEBUG_INFO, "FV Header @ 0x%X restored with static data\n", BaseAddress));
      //
      // Clear cache for this range.
      //
      WriteBackInvalidateDataCacheRange ( (VOID *) (UINTN) BaseAddress, FvHeader->BlockMap->Length);
    }
  }

  //
  // Calculate the total size for all firmware volume block instances
  //
  BufferSize = 0;
  for (Idx = 0; Idx < mPlatformFvBaseAddressCount; Idx++) {
    BaseAddress = mPlatformFvBaseAddress[Idx].FvBase;
    FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) BaseAddress;

    if (!IsFvHeaderValid (BaseAddress, FvHeader)) {
      DEBUG ((DEBUG_ERROR, "ERROR - The FV in 0x%x is invalid!\n", FvHeader));
      continue;
    }

    BufferSize += (FvHeader->HeaderLength +
                  sizeof (EFI_FVB_INSTANCE) -
                  sizeof (EFI_FIRMWARE_VOLUME_HEADER)
                  );
  }

  mFvbModuleGlobal.FvbInstance =  (EFI_FVB_INSTANCE *) AllocateRuntimeZeroPool (BufferSize);
  if (mFvbModuleGlobal.FvbInstance == NULL) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }

  MaxLbaSize      = 0;
  FvbInstance     = mFvbModuleGlobal.FvbInstance;
  mFvbModuleGlobal.NumFv   = 0;

  for (Idx = 0; Idx < mPlatformFvBaseAddressCount; Idx++) {
    BaseAddress = mPlatformFvBaseAddress[Idx].FvBase;
    FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) BaseAddress;

    if (!IsFvHeaderValid (BaseAddress, FvHeader)) {
      DEBUG ((DEBUG_ERROR, "ERROR - The FV in 0x%x is invalid!\n", FvHeader));
      continue;
    }

    FvbInstance->Signature = FVB_INSTANCE_SIGNATURE;
    CopyMem (&(FvbInstance->FvHeader), FvHeader, FvHeader->HeaderLength);

    FvHeader = &(FvbInstance->FvHeader);
    FvbInstance->FvBase = (UINTN)BaseAddress;

    //
    // Process the block map for each FV
    //
    FvbInstance->NumOfBlocks   = 0;
    for (PtrBlockMapEntry = FvHeader->BlockMap;
         PtrBlockMapEntry->NumBlocks != 0;
         PtrBlockMapEntry++) {
      //
      // Get the maximum size of a block.
      //
      if (MaxLbaSize < PtrBlockMapEntry->Length) {
        MaxLbaSize  = PtrBlockMapEntry->Length;
      }
      FvbInstance->NumOfBlocks += PtrBlockMapEntry->NumBlocks;
    }

    //
    // Add a FVB Protocol Instance
    //
    InstallFvbProtocol (FvbInstance);
    mFvbModuleGlobal.NumFv++;

    //
    // Move on to the next FvbInstance
    //
    FvbInstance = (EFI_FVB_INSTANCE *) ((UINTN)((UINT8 *)FvbInstance) +
                                          FvHeader->HeaderLength +
                                          (sizeof (EFI_FVB_INSTANCE) - sizeof (EFI_FIRMWARE_VOLUME_HEADER)));

  }

  return EFI_SUCCESS;
}
