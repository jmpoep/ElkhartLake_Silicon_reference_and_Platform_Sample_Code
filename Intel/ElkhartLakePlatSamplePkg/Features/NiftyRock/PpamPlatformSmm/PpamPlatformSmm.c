/** @file
  PPAM platform SMM API

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/SmmReadyToLock.h>
#include <Protocol/SmmCpu.h>
#include <Protocol/SmMonitorInit.h>
#include <Library/PcdLib.h>

EFI_SM_MONITOR_INIT_PROTOCOL                *mSmMonitorInitProtocol;

/**
  Load PPAM image.

  @retval EFI_SUCCESS           STM is loaded to MSEG
  @retval EFI_BUFFER_TOO_SMALL  MSEG is too small
  @retval EFI_UNSUPPORTED       MSEG is not enabled
**/
EFI_STATUS
LoadPpamImage (
  VOID
  )
{
  EFI_STATUS  Status;
  VOID        *PpamImageBuffer;
  UINTN       PpamImageSize;

  //
  // Extract PPAM image from FV
  //
  PpamImageBuffer = NULL;
  PpamImageSize = 0;

  Status = GetSectionFromAnyFv (
             PcdGetPtr(PcdPpamBinFile),
             EFI_SECTION_RAW,
             0,
             &PpamImageBuffer,
             &PpamImageSize
             );
  ASSERT_EFI_ERROR (Status);

  Status = mSmMonitorInitProtocol->LoadMonitor ((EFI_PHYSICAL_ADDRESS)(UINTN)PpamImageBuffer, PpamImageSize);
  DEBUG ((DEBUG_INFO, "mSmMonitorInitProtocol->LoadMonitor - %r\n", Status));
  ASSERT_EFI_ERROR (Status);

  gBS->FreePool ((VOID *)((UINTN)PpamImageBuffer));

  return Status;
}

/**
  Load PPAM Manifest.

  @retval EFI_SUCCESS           STM is loaded to MSEG
  @retval EFI_BUFFER_TOO_SMALL  MSEG is too small
  @retval EFI_UNSUPPORTED       MSEG is not enabled
**/
EFI_STATUS
LoadPpamManifest (
  VOID
  )
{
  EFI_STATUS  Status;
  VOID        *PpamManifestBuffer;
  VOID        *PpamManifestRuntimeBuffer;
  UINTN       PpamManifestSize;

  //
  // Extract PPAM Manifest from FV
  //
  PpamManifestBuffer = NULL;
  PpamManifestSize = 0;

  Status = GetSectionFromAnyFv (
             PcdGetPtr(PcdPpamManifestBinFile),
             EFI_SECTION_RAW,
             0,
             &PpamManifestBuffer,
             &PpamManifestSize
             );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->AllocatePool (EfiRuntimeServicesData, PpamManifestSize, &PpamManifestRuntimeBuffer);
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_INFO, "PpamManifestRuntimeBuffer - 0x%x\n", PpamManifestRuntimeBuffer));
  CopyMem (PpamManifestRuntimeBuffer, PpamManifestBuffer, PpamManifestSize);

  Status = gBS->InstallConfigurationTable (&gPpamManifestGuid, PpamManifestRuntimeBuffer);
  ASSERT_EFI_ERROR (Status);

  gBS->FreePool ((VOID *)((UINTN)PpamManifestBuffer));

  return Status;
}

/**

  PPAM platform SMM driver entry point function.

  @param ImageHandle   image handle for this driver image
  @param SystemTable   pointer to the EFI System Table

  @retval EFI_SUCCESS

**/
EFI_STATUS
EFIAPI
InstallPpamPlatformSmm (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                    Status;

  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmMonitorInitProtocolGuid,
                    NULL,
                    (VOID **)&mSmMonitorInitProtocol
                    );
  if (EFI_ERROR(Status) || (mSmMonitorInitProtocol == NULL)) {
    return EFI_UNSUPPORTED;
  }

  Status = LoadPpamImage ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = LoadPpamManifest ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}
