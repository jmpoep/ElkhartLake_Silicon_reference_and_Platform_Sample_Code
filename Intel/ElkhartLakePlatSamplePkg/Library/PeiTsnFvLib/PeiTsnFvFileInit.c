/**@file
  TSN FV Installation

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
#include <Library/PeiTsnMacAddrFvLib.h>
#include <Library/PeiPseTsnIpConfigFvLib.h>
#include <Library/PeiTsnConfigFvLib.h>
#include <Library/PeiSubRegionLib.h>

/**
  Get TSN MAC Config FV base address

  Base address will vary between SPI and UFS boot.

  @return FvBase associated with FvBinary FV.
**/
UINT32
GetFlashTsnMacAddrFvBase (
  VOID
  )
{
  UINT32 FvBase;
  if (BootMediaIsUfs ()) {
    FvBase = PcdGet32 (PcdUfsFlashTsnMacAddressFvBase);
  } else {
    FvBase = FixedPcdGet32 (PcdFlashFvTsnMacAddressBase);
  }
  DEBUG ((DEBUG_INFO, "GetFvTsnMacAddressBase - 0x%x  ......\n", FvBase));
  return FvBase;
}

/**
  Get TSN IP Config FV base address

  Base address will vary between SPI and UFS boot.

  @return FvBase associated with FvBinary FV.
**/
UINT32
GetFlashPseTsnIpConfigFvBase (
  VOID
  )
{
  UINT32 FvBase;
  if (BootMediaIsUfs ()) {
    FvBase = PcdGet32 (PcdUfsFlashPseTsnIpConfigFvBase);
  } else {
    FvBase = FixedPcdGet32 (PcdFlashFvPseTsnIpConfigBase);
  }
  DEBUG ((DEBUG_INFO, "GetFvPseTsnIpConfigBase - 0x%x  ......\n", FvBase));
  return FvBase;
}

/**
  Get TSN Config FV base address

  Base address will vary between SPI and UFS boot.

  @return FvBase associated with FvBinary FV.
**/
UINT32
GetFlashTsnConfigFvBase (
  VOID
  )
{
  UINT32 FvBase;
  if (BootMediaIsUfs ()) {
    FvBase = PcdGet32 (PcdUfsFlashTsnConfigFvBase);
  } else {
    FvBase = FixedPcdGet32 (PcdFlashFvTsnConfigBase);
  }
  DEBUG ((DEBUG_INFO, "GetFvTsnConfigBase - 0x%x  ......\n", FvBase));
  return FvBase;
}

/**
  Install Base and Size Info Ppi for TSN MAC address Firmware Volume.

  @retval     EFI_SUCCESS  Always returns success.

**/
EFI_STATUS
EFIAPI
InstallTsnMacAddrFv (
  VOID
)
{
  UINT32 FlashFvBase;

  FlashFvBase = GetFlashTsnMacAddrFvBase ();
  // Report and install FV Info Ppi to Pei Core for TSN MAC FV
  PeiServicesInstallFvInfoPpi (
    NULL,
    (VOID *) FlashFvBase,
    PcdGet32 (PcdFlashFvTsnMacAddressSize),
    NULL,
    NULL
    );
  return EFI_SUCCESS;
}

/**
  Install Base and Size Info Ppi for PSE TSN IP config Firmware Volume.

  @retval     EFI_SUCCESS  Always returns success.

**/
EFI_STATUS
EFIAPI
InstallPseTsnIpConfigFv (
  VOID
)
{
  UINT32 FlashFvBase;

  FlashFvBase = GetFlashPseTsnIpConfigFvBase ();
  // Report and install FV Info Ppi to Pei Core for PSE TSN IP config FV
  PeiServicesInstallFvInfoPpi (
    NULL,
    (VOID *) FlashFvBase,
    PcdGet32 (PcdFlashFvPseTsnIpConfigSize),
    NULL,
    NULL
    );
  return EFI_SUCCESS;
}

/**
  Install Base and Size Info Ppi for TSN config Firmware Volume.

  @retval     EFI_SUCCESS  Always returns success.

**/
EFI_STATUS
EFIAPI
InstallTsnConfigFv (
  VOID
)
{
  UINT32 FlashFvBase;

  FlashFvBase = GetFlashTsnConfigFvBase ();
  // Report and install FV Info Ppi to Pei Core for TSN config FV
  PeiServicesInstallFvInfoPpi (
    NULL,
    (VOID *) FlashFvBase,
    PcdGet32 (PcdFlashFvTsnConfigSize),
    NULL,
    NULL
    );
  return EFI_SUCCESS;
}

/*
  Reads TSN MAC Address Sub region.

  Reads TSN MAC Address sub region data from FV. Returns pointer to data.

  @param[out]  SubRegion Pointer to sub region data.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       TSN region was not found
*/
EFI_STATUS
GetTsnMacAddrSubRegion (
  OUT TSN_MAC_ADDR_SUB_REGION**        SubRegion,
  OUT UINT32                           *SubRegionSize
  )
{
  EFI_STATUS Status;
  VOID       *TsnSubRegionStart;
  UINT32     TsnSubRegionSize;

  DEBUG ((DEBUG_INFO, "GetTsnMacAddressSubRegion() Start\n"));

  // Read Spi Flash
  Status = ReadSectionInformationFromFv (&gTsnMacAddrSectionGuid, EFI_SECTION_RAW, &TsnSubRegionStart, &TsnSubRegionSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Failed to get TSN MAC Address Sub Region FV\n"));
    return Status;
  }

  *SubRegion = (TSN_MAC_ADDR_SUB_REGION*) TsnSubRegionStart;
  *SubRegionSize = TsnSubRegionSize;

  DEBUG ((DEBUG_INFO, "GetTsnMacAddressSubRegion() End\n"));
  return Status;
}

/*
  Reads PSE TSN IP Config Sub region.

  Reads PSE TSN IP Config sub region data from FV. Returns pointer to data.

  @param[out]  SubRegion Pointer to sub region data.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       TSN region was not found
*/
EFI_STATUS
GetPseTsnIpConfigSubRegion (
  OUT PSE_IP_CONFIG_SUB_REGION**       SubRegion,
  OUT UINT32                           *SubRegionSize
  )
{
  EFI_STATUS Status;
  VOID       *TsnSubRegionStart;
  UINT32     TsnSubRegionSize;

  DEBUG ((DEBUG_INFO, "GetPseTsnIpConfigSubRegion() Start\n"));

  // Read Spi Flash
  Status = ReadSectionInformationFromFv (&gPseTsnIpConfigSectionGuid, EFI_SECTION_RAW, &TsnSubRegionStart, &TsnSubRegionSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Failed to get TSN IP config Sub Region FV\n"));
    return Status;
  }

  *SubRegion = (PSE_IP_CONFIG_SUB_REGION*) TsnSubRegionStart;
  *SubRegionSize = TsnSubRegionSize;

  DEBUG ((DEBUG_INFO, "GetPseTsnIpConfigSubRegion() End\n"));
  return Status;
}

/*
  Reads TSN Config Sub region.

  Reads TSN Config sub region data from FV. Returns pointer to data.

  @param[out]  SubRegion Pointer to sub region data.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       TSN region was not found
*/
EFI_STATUS
GetTsnConfigSubRegion (
  OUT PSE_TSN_CONFIG_SUB_REGION**      SubRegion,
  OUT UINT32                           *SubRegionSize
  )
{
  EFI_STATUS Status;
  VOID       *TsnSubRegionStart;
  UINT32     TsnSubRegionSize;

  DEBUG ((DEBUG_INFO, "GetTsnConfigSubRegion() Start\n"));

  // Read Spi Flash
  Status = ReadSectionInformationFromFv (&gTsnConfigSectionGuid, EFI_SECTION_RAW, &TsnSubRegionStart, &TsnSubRegionSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Failed to get TSN config Sub Region FV\n"));
    return Status;
  }

  *SubRegion = (PSE_TSN_CONFIG_SUB_REGION*) TsnSubRegionStart;
  *SubRegionSize = TsnSubRegionSize;

  DEBUG ((DEBUG_INFO, "GetTsnConfigSubRegion() End\n"));
  return Status;
}
