/**@file
  PSE FV Installation

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification
**/

#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/BootMediaLib.h>
#include <Library/PeiSubRegionLib.h>
#include <Library/PeiSiipFvLib.h>

/**
  Install Base and Size Info Ppi for Siip Firmware Volume.

  @retval     EFI_SUCCESS  Always returns success.

**/
EFI_STATUS
EFIAPI
InstallSiipFv (
  VOID
)
{
  if (BootMediaIsSpi ()) {
    PeiServicesInstallFvInfoPpi (
      NULL,
      (VOID *) PcdGet32 (PcdFlashFvSiipFwBase),
      PcdGet32 (PcdFlashFvSiipFwSize),
      NULL,
      NULL
      );
  } else {
    PeiServicesInstallFvInfoPpi (
      NULL,
      (VOID *) PcdGet32 (PcdUfsFvSiipFwBase),
      PcdGet32 (PcdUfsFvSiipFwSize),
      NULL,
      NULL
      );
  }
  return EFI_SUCCESS;
}

/*
  Reads SIIP Sub region.

  Reads SIIP address and size from FV. Returns pointer to data.

  @param[out]  SubRegion Pointer to sub region data.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       SIIP firmware was not found
*/
EFI_STATUS
GetSiipFvInfo (
  OUT SIIP_FV_INFO  *SiipFvInfo
  )
{
  EFI_STATUS    Status;
  VOID          *FwBuffer;
  UINTN         FwSize;
  VOID          *ManifestBuffer;
  UINTN         ManifestSize;

  Status = ReadSectionInformationFromFv (&gSiipPseFirmwareCodeBlob0Guid, EFI_SECTION_RAW, &FwBuffer, &FwSize);
  DEBUG_CODE_BEGIN ();
    DEBUG ((DEBUG_INFO, "Raw read, PSE FwBuffer : %x FwSize : %x\n", FwBuffer, FwSize));
    for (UINT32 fw_i = 0; fw_i < 20; fw_i++) {
      if ((fw_i % 10) == 0){
        DEBUG ((EFI_D_INFO, "\n"));
      }
      DEBUG ((EFI_D_INFO, "0x%08x ",*((UINT32 *)FwBuffer + fw_i)));
    }
  DEBUG_CODE_END ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Failed to get SIIP firmware\n"));
    // return Status;
  } else {
    Status = ReadSectionInformationFromFv (&gSiipPseFirmwareBlobManifestGuid, EFI_SECTION_RAW, &ManifestBuffer, &ManifestSize);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "Failed to get SIIP manifest\n"));
      // return Status;
    } else {
      Status = VerifyManifest(ManifestBuffer, ManifestSize);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_INFO, "Failed to verify SIIP manifest\n"));
      }
      Status = VerifyFirmware(ManifestBuffer, ManifestSize, FwBuffer, FwSize);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_INFO, "Failed to verify SIIP firmware\n"));
        DEBUG ((DEBUG_INFO, "FwBuffer : %x FwSize : %x\n", 0, 0));
        SiipFvInfo->Address = 0;
        SiipFvInfo->Size    = 0;
      } else {
        DEBUG ((DEBUG_INFO, "FwBuffer : %x FwSize : %x\n", FwBuffer, FwSize));
        SiipFvInfo->Address = (UINTN) FwBuffer;
        SiipFvInfo->Size    = (UINTN) FwSize;
        Status = EFI_SUCCESS;
      }
    }
  }
  return Status;
}
