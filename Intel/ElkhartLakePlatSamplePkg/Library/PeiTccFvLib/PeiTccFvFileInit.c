/**@file
  TCC FV Installation

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#include <TccConfigSubRegion.h>

/**
  Get TCC Config FV base address

  Base address will vary between SPI and UFS boot.

  @return FvBase associated with FvBinary FV.
**/
UINT32
GetFlashTccConfigFvBase (
  VOID
  )
{
  UINT32 FvBase;
  if (BootMediaIsUfs ()) {
    FvBase = PcdGet32 (PcdUfsFlashTccConfigFvBase);
  } else {
    FvBase = FixedPcdGet32 (PcdFlashFvTccConfigBase);
  }
  DEBUG ((DEBUG_INFO, "GetFvTccConfigBase - 0x%x  ......\n", FvBase));
  return FvBase;
}

/**
  Install Base and Size Info Ppi for TCC Config Firmware Volume.

  @retval     EFI_SUCCESS  Always returns success.

**/
EFI_STATUS
EFIAPI
InstallTccConfigFv (
  VOID
)
{
  UINT32 FlashFvBase;

  FlashFvBase = GetFlashTccConfigFvBase ();
  // Report and install FV Info Ppi to Pei Core for TCC Config FV
  PeiServicesInstallFvInfoPpi (
    NULL,
    (VOID *) FlashFvBase,
    PcdGet32 (PcdFlashFvTccConfigSize),
    NULL,
    NULL
    );
  return EFI_SUCCESS;
}

/*
  Reads TCC Config Sub region.

  Reads TCC Config sub region data from FV. Returns pointer to data.

  @param[out]  SubRegion Pointer to sub region data.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       TCC region was not found
*/
EFI_STATUS
GetTccConfigSubRegion (
  OUT TCC_CONFIG_SUB_REGION**      SubRegion,
  OUT UINT32                       *SubRegionSize
  )
{
  EFI_STATUS Status;
  VOID       *TccSubRegionStart;
  UINT32     TccSubRegionSize;

  DEBUG ((DEBUG_INFO, "GetTccConfigSubRegion() Start\n"));

  // Read Spi Flash
  Status = ReadSectionInformationFromFv (&gTccConfigSectionGuid, EFI_SECTION_RAW, &TccSubRegionStart, &TccSubRegionSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Failed to get Tcc config Sub Region FV\n"));
    return Status;
  }

  *SubRegion = (TCC_CONFIG_SUB_REGION*) TccSubRegionStart;
  *SubRegionSize = TccSubRegionSize;

  DEBUG ((DEBUG_INFO, "GetTccConfigSubRegion() End\n"));
  return Status;
}