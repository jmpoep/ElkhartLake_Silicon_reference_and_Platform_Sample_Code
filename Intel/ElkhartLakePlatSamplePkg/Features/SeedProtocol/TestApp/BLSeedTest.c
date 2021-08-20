/** @file
UEFI BLSeedTest application.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018-19 Intel Corporation.

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

@par Specification

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BootloaderSeedProtocol.h>

/**

  This function dump raw data.

  @param  Data  raw data
  @param  Size  raw data size

**/
VOID
InternalDumpData (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN  Index;
  for (Index = 0; Index < Size; Index++) {
    Print (L"%02x", (UINTN)Data[Index]);
  }
}

/**

  This function dump raw data with colume format.

  @param  Data  raw data
  @param  Size  raw data size

**/
VOID
InternalDumpHex (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN   Index;
  UINTN   Count;
  UINTN   Left;

#define COLUME_SIZE  (16 * 2)

  Count = Size / COLUME_SIZE;
  Left  = Size % COLUME_SIZE;
  for (Index = 0; Index < Count; Index++) {
    Print (L"%04x: ", Index * COLUME_SIZE);
    InternalDumpData (Data + Index * COLUME_SIZE, COLUME_SIZE);
    Print (L"\n");
  }

  if (Left != 0) {
    Print (L"%04x: ", Index * COLUME_SIZE);
    InternalDumpData (Data + Index * COLUME_SIZE, Left);
    Print (L"\n");
  }
}

VOID
PrintBLSeedList (
  IN BOOTLOADER_SEED_INFO_LIST *BlSeedList
  )
{
  int i = 0;

  if (BlSeedList) {
    Print (L"NumSeeds = %d\n", BlSeedList->NumOfSeeds);

    for (; i < BlSeedList->NumOfSeeds; i++) {
      Print (L"CseSvn = %d\n", BlSeedList->SeedList[i].cse_svn);
      Print (L"BiosSvn = %d\n", BlSeedList->SeedList[i].bios_svn);
      Print (L"Seed : \n");
      InternalDumpHex (BlSeedList->SeedList[i].seed, BOOTLOADER_SEED_LEN);
    }
  }
}


EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                  Status;
  BOOTLOADER_SEED_PROTOCOL    *Bls;

  Status    = EFI_SUCCESS;

  Print (L" -- Locate UEFI BLS Protocol : ");
  Status = gBS->LocateProtocol (&gEfiBootloaderSeedProtocolGuid, NULL, (VOID **)&Bls);
  if (EFI_ERROR (Status)) {
    Print (L"[Fail - Status = %r]\n", Status);
    return Status;
  } else {
    Print (L"[Pass]\n");
  }

  if (Bls && Bls->GetSeedInfoList) {

    BOOTLOADER_SEED_INFO_LIST BlSeedList;

    ZeroMem (&BlSeedList, sizeof (BOOTLOADER_SEED_INFO_LIST));
    Status = Bls->GetSeedInfoList (&BlSeedList);
    if (Status != EFI_SUCCESS) {
      Print (L"[Fail - Status = %r]\n", Status);
    } else {
      PrintBLSeedList (&BlSeedList);
    }

    // Do cleanup of memory which contains sensitive data
    ZeroMem (&BlSeedList, sizeof(BlSeedList));
  }

  if (Bls && Bls->EndOfService) {
    Status = Bls->EndOfService ();
    Print (L"Invoked EndofService on BLS Seed Protocol. Repeat calls to retrieve seed will NOT succeed.\n");
  }

  return Status;
}
