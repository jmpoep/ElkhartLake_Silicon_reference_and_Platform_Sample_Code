/** @file
  This file contains the tests for the BootFirmwareMediaProtection BIT

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

#include "HstiIhvDxe.h"
#include <Library/BootMediaLib.h>
#include <Protocol/UfsDeviceConfig.h>
#include <MeState.h>

#define V_SPI_BIOS_REGION_FLASH_WRITE_ACCESS_BIOS_GBE                        0x00A00000
#define V_SPI_BIOS_REGION_FLASH_WRITE_ACCESS_BIOS_GBE_PDR                    0x01A00000
#define V_SPI_BIOS_REGION_FLASH_WRITE_ACCESS_BIOS_GBE_EC                     0x10A00000
#define V_SPI_BIOS_REGION_FLASH_WRITE_ACCESS_BIOS_GBE_PDR_EC                 0x11A00000
#define V_SPI_BIOS_REGION_FLASH_READ_ACCESS_DESCRIPTOR_BIOS_ME_GBE           0x00000F00
#define V_SPI_BIOS_REGION_FLASH_READ_ACCESS_DESCRIPTOR_BIOS_ME_GBE_PDR       0x00001F00
#define V_SPI_BIOS_REGION_FLASH_READ_ACCESS_DESCRIPTOR_BIOS_ME_GBE_EC        0x00010F00
#define V_SPI_BIOS_REGION_FLASH_READ_ACCESS_DESCRIPTOR_BIOS_ME_GBE_PDR_EC    0x00011F00
#define V_SPI_GBE_REGION_WRITE_READ_ACCESS                                   0x00800900
#define V_SPI_ME_REGION_WRITE_READ_ACCESS                                    0x00400D00
#define V_SPI_EC_REGION_WRITE_READ_ACCESS1                                   0x10010300
#define V_SPI_EC_REGION_WRITE_READ_ACCESS2                                   0x10010100

//
// UFS Boot Media LUN
//
#define UFS_LUN_1                  0x01

//
// UFS 2.0 Spec Section 14.1.6.5 - Unit Descriptor
//
typedef struct {
  UINT8  Length;
  UINT8  DescType;
  UINT8  UnitIdx;
  UINT8  LunEn;
  UINT8  BootLunId;
  UINT8  LunWriteProt;
  UINT8  LunQueueDep;
  UINT8  Rsvd1;
  UINT8  MemType;
  UINT8  DataReliability;
  UINT8  LogicBlkSize;
  UINT64 LogicBlkCount;
  UINT32 EraseBlkSize;
  UINT8  ProvisionType;
  UINT64 PhyMemResCount;
  UINT16 CtxCap;
  UINT8  LargeUnitGranularity;
} UFS_UNIT_DESC;


//
// UFS Descriptors
//
typedef enum {
  UfsDeviceDesc     = 0x00,
  UfsConfigDesc     = 0x01,
  UfsUnitDesc       = 0x02,
  UfsInterConnDesc  = 0x04,
  UfsStringDesc     = 0x05,
  UfsGeometryDesc   = 0x07,
  UfsPowerDesc      = 0x08
} UFS_DESC_IDN;


/**
  Run tests for UFS Boot Media
**/
BOOLEAN
CheckUFSMediaProtection (
  VOID
  )
{
  BOOLEAN                Result;
  EFI_STATUS             Status;
  UINT8                  Value;
  EFI_UFS_DEVICE_CONFIG_PROTOCOL   *UfsDeviceConfig;
  UFS_UNIT_DESC                     UnitDescriptor;
  UINT32                            UnitDescriptorSize;

  Result = TRUE;

  Status = gBS->LocateProtocol(&gEfiUfsDeviceConfigProtocolGuid, NULL, (VOID **)&UfsDeviceConfig);

  if (EFI_ERROR(Status)) {
    ASSERT_EFI_ERROR (Status);
    DEBUG ((DEBUG_ERROR,"  Failed to locate gEfiUfsDeviceConfigProtocolGuid Protocol\n"));
    return FALSE;
  }

  DEBUG ((DEBUG_INFO, "      UFS Boot Media LUN bLUWriteProtect Byte Test\n"));

  UnitDescriptorSize = sizeof (UFS_UNIT_DESC);
  Status = UfsDeviceConfig->RwUfsDescriptor(UfsDeviceConfig, TRUE, UfsUnitDesc, UFS_LUN_1, 0, (UINT8*)&UnitDescriptor, &UnitDescriptorSize);
  if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "        Failed to read unit descriptor, index = %X, status = %r\n", UFS_LUN_1, Status));
      ASSERT_EFI_ERROR (Status);
      return FALSE;
  }

  if (UnitDescriptor.LunWriteProt != 0x01) {
      DEBUG ((DEBUG_ERROR, "        UFS LUN %X is NOT Write Protected\n", UFS_LUN_1));
          BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_10,
      HSTI_UFS_BOOT_MEDIA_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_10
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      UFS Boot Media fPowerOnWPEn Byte Test\n"));

  Value = 0;
  Status = UfsDeviceConfig->RwUfsFlag(UfsDeviceConfig, TRUE, 3, &Value);                     // Index value of flag "fPowerOnWPEn" is 3 

  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR,"        Unable to read fPowerOnWPEn UFS flag\n"));
    ASSERT_EFI_ERROR (Status);
    return FALSE;
  }

  if (Value == 0) {
    DEBUG ((DEBUG_ERROR, "        Unexpected Status: fPowerOnWPEn is not set\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_11,
      HSTI_UFS_BOOT_MEDIA_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_11
      );
    Result = FALSE;
  }

  return Result;
}


/**
  Run tests for SPI Boot Media
**/
BOOLEAN
CheckSPIMediaProtection (
  VOID
  )
{
  BOOLEAN         Result;
  UINT32          Cpptv;
  UINT32          Data32;
  BOOLEAN         SpiBild;

  Result = TRUE;

  DEBUG ((DEBUG_INFO, "  SPI Flash and BIOS Security Configuration\n"));
  DEBUG ((DEBUG_INFO, "      BIOS write-protection Test\n"));

  if (SpiIsWriteProtectionEnabled () == FALSE) {
    DEBUG((DEBUG_INFO, "        Unexpected Status: One or more bits misconfigured for BIOS Write-Protection\n"));
    DEBUG((DEBUG_INFO, "        Values expected: LE = 1; WPD = 0; EISS = 1\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_1,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_1
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      SPI flash descriptor security override pin-strap Test\n"));
  if (SpiIsFlashDescriptorOverrideEnabled () == FALSE) {
    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_2,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_2
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      SPI controller configuration is locked Test\n"));

  if (SpiIsFlashConfigurationLockDownEnabled () == FALSE) {
    DEBUG((DEBUG_INFO, "        Unexpected Status: SPI controller configuration Registers Unlocked\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_3,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_3
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      BIOS Interface Lock Test\n"));

  SpiBild = SpiIsBiosInterfaceLockdownEnabled ();
  if (SpiBild == FALSE) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: BILD[7] = %x is not set\n", SpiBild));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_4,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_4
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      BIOS Top Swap Mode Test\n"));

  if (SpiIsTopSwapEnabled () == TRUE) {
    DEBUG((DEBUG_INFO, "        Unexpected Status: BIOS Top Swap Mode Enabled\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_5,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_5
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      Component Property Parameter Table Valid Test\n"));

  SpiGetComponentPropertyParameterTable (0, &Cpptv);
  if (SpiIsCppValidBitSet (Cpptv) == FALSE) {
    DEBUG((DEBUG_INFO, "        Unexpected Status: Component Property Parameter Table Invalid.\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_6,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_6
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      Component Property Parameter Table Valid, Secondary Flash Part Test\n"));

  //
  // If Second part is present the verify Vscc is set, otherwise if not present verify that it's clear
  //
  if (SpiGetComponentPropertyParameterTable (1, &Cpptv) == TRUE) {
    if (SpiIsCppValidBitSet (Cpptv) == FALSE) {
      DEBUG((DEBUG_INFO, "        Unexpected Status: Secondary SPI Flash part is not cleared\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_6,
        HSTI_SPI_FLASH_CONFIGURATION,
        HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_6
        );
      Result = FALSE;
    }
  } else {
    if (SpiIsCppValidBitSet (Cpptv) == TRUE) {
      DEBUG((DEBUG_INFO, "        Unexpected Status: SPI Vendor Specific Component Capabilities Unlocked\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_6,
        HSTI_SPI_FLASH_CONFIGURATION,
        HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_6
        );
      Result = FALSE;
    }
  }

  DEBUG ((DEBUG_INFO, "      BIOS Flash Descriptor Valid Test\n"));

  if (SpiIsFlashDescriptorValid () == FALSE) {
    DEBUG((DEBUG_INFO, "        Unexpected Status: BIOS Flash Descriptor Invalid\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_9,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_9
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      BIOS Region Flash Write Access Test\n"));
  ///
  /// Descriptor Master Access Read:  BIT 8
  /// Bios Master Access Read:        BIT 9
  /// CSE Master Access Read:         BIT 10
  /// GBE Master Access Read:         BIT 11
  /// PDR Master Access Read:         BIT 12
  /// EC  Master Access Read:         BIT 16
  /// Descriptor Master Access Write: BIT 20
  /// Bios Master Access Write:       BIT 21
  /// CSE Master Access Write:        BIT 22
  /// GBE Master Access Write:        BIT 23
  /// PDR Master Access Write:        BIT 24
  /// EC Master Access Write:         BIT 28
  /// Recommended Flash Region Read/Write access permissions as per SPI Programming Guide.
  ///
  Data32 = SpiGetBiosRegionFlashWriteAccess ();

  if ((Data32 != V_SPI_BIOS_REGION_FLASH_WRITE_ACCESS_BIOS_GBE) &&
      (Data32 != V_SPI_BIOS_REGION_FLASH_WRITE_ACCESS_BIOS_GBE_PDR) &&
      (Data32 != V_SPI_BIOS_REGION_FLASH_WRITE_ACCESS_BIOS_GBE_EC) &&
      (Data32 != V_SPI_BIOS_REGION_FLASH_WRITE_ACCESS_BIOS_GBE_PDR_EC)) {

    DEBUG ((DEBUG_INFO, "        Unexpected Status: Bios Region Master Write Access Invalid Production Permissions\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_A,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_A
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      BIOS Region Flash Read Access Test\n"));
  Data32 = SpiGetBiosRegionFlashReadAccess ();

  if ((Data32 != V_SPI_BIOS_REGION_FLASH_READ_ACCESS_DESCRIPTOR_BIOS_ME_GBE) &&
      (Data32 != V_SPI_BIOS_REGION_FLASH_READ_ACCESS_DESCRIPTOR_BIOS_ME_GBE_PDR) &&
      (Data32 != V_SPI_BIOS_REGION_FLASH_READ_ACCESS_DESCRIPTOR_BIOS_ME_GBE_EC) &&
      (Data32 != V_SPI_BIOS_REGION_FLASH_READ_ACCESS_DESCRIPTOR_BIOS_ME_GBE_PDR_EC)) {

    DEBUG ((DEBUG_INFO, "        Unexpected Status: Bios Region Master Read Access Invalid Production Permissions\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_A,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_A
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      BIOS Master Read Access Test\n"));

  if (SpiGetMasterReadAccess () != 0) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: BMRAG Not Equal To 0x00\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_A,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_A
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      BIOS Master Write Access Test\n"));

  if (SpiGetMasterWriteAccess () != 0) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: BMWAG Not Equal To 0x00\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_A,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_A
      );
    Result = FALSE;
  }

  if (SpiIsGbeRegionValid () == TRUE) {
    DEBUG ((DEBUG_INFO, "      GbE Region Access Test\n"));
    Data32 = SpiGetGbeRegionAccess ();
    if (Data32 != V_SPI_GBE_REGION_WRITE_READ_ACCESS) {
      DEBUG ((DEBUG_INFO, "        Unexpected Status: Gbe Region Access Flash Descriptor\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_A,
        HSTI_SPI_FLASH_CONFIGURATION,
        HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_A
        );
      Result = FALSE;
    }
  }

  DEBUG ((DEBUG_INFO, "      ME Region Access Test\n"));

  Data32 = SpiGetCsmeRegionAccess ();
  if (Data32 != V_SPI_ME_REGION_WRITE_READ_ACCESS) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: ME Region Access Flash Descriptor\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_A,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_A
      );
    Result = FALSE;
  }
  DEBUG ((DEBUG_INFO, "      EC Region Access Test\n"));

  Data32 = SpiGetEcRegionAccess ();

  if ((Data32 != V_SPI_EC_REGION_WRITE_READ_ACCESS1) &&
      (Data32 != V_SPI_EC_REGION_WRITE_READ_ACCESS2)) {
      DEBUG((DEBUG_INFO, "        Unexpected Status: EC Region Access Flash Descriptor\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_A,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_A
      );
    Result = FALSE;
  }

  DEBUG((DEBUG_INFO, "      Disallow WriteStatus SPI OPCODE Test\n"));

  if (SpiIsWriteStatusDisable () == FALSE) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: WriteStatus SPI OPCODE is Allowed\n"));

    BuildAndAppendHstiStatusString(
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_F,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_F
      );
    Result = FALSE;
  }

  return Result;
}


/**
  Run tests for BootFirmwareMediaProtection bit
**/
VOID
CheckBootFirmwareMediaProtection (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOLEAN         Result;
  BOOLEAN         PcrDmi;
  HECI_PROTOCOL   *Heci;
  UINT32          MeStatus;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION) == 0) {
    return;
  }

  if (BootMediaIsUfs ()) {
    Result = CheckUFSMediaProtection();
  } else if (BootMediaIsSpi ()) {
    Result = CheckSPIMediaProtection();
  } else {
    DEBUG ((DEBUG_INFO, "      Unknown BootMedia detected\n"));
    Result = FALSE;
  }


  DEBUG ((DEBUG_INFO, "      Pch DMI BIOS Interface Lock Test\n"));

  PcrDmi = PchDmiIsBiosInterfaceLock ();
  if (PcrDmi == FALSE) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: PcrDmi = %x are not set\n", PcrDmi));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_4,
      HSTI_SPI_FLASH_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_4
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      ME Firmware Normal Working Status Test\n"));

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "        Unable to Locate HECI Protocol\n"));
  } else {
    Heci->GetMeStatus (&MeStatus);

    if (ME_STATUS_ME_STATE_ONLY (MeStatus) != ME_READY)  {
      DEBUG((DEBUG_INFO, "        Unexpected Status: ME Firmware not in Normal Working Status = %x\n", (ME_STATUS_ME_STATE_ONLY (MeStatus))));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_8,
        HSTI_SPI_FLASH_CONFIGURATION,
        HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_8
        );
      Result = FALSE;
    }
  }
  //
  // ALL PASS
  //
  if (Result) {
    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               0,
               HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION
               );
    CheckStatusForHstiLibSet (Status);
  }

  return;
}