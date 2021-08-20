/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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

#include <PiPei.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/EcMiscLib.h>
#include <PlatformBoardType.h>
#include <Library/PeiDxeBoardIdsLib.h>
#include <PlatformBoardId.h>
#include <PlatformBoardConfig.h>
#include <Library/SmbusLib.h>
#include <Library/TimerLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Library/GpioLib.h>
#include <Pins/GpioPinsVer3.h>
#include <Library/I2cAccessLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci22.h>
#include <Library/BaseMemoryLib.h>
#include <Register/PchRegs.h>
#include <Register/PseRegs.h>

#define STALL_TIME                  1000000 // 1,000,000 microseconds = 1 second

VOID
PseI2cEnableMmio  (
  IN UINT64     PciBaseAddress,
  IN UINT32     MmioBase
  )
{
  //
  // Disable MSE
  //
  PciSegmentAnd16 (PciBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Write temp address to lower base address
  //
  PciSegmentWrite32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, MmioBase);
  //
  // Clear upper base address
  //
  PciSegmentWrite32 (PciBaseAddress + (PCI_BASE_ADDRESSREG_OFFSET + 4), 0);
  //
  // Enable MSE
  //
  PciSegmentOr16 (PciBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
}

VOID
PseI2cDisableMmio (
  IN UINT64  PciBaseAddress
  )
{
  //
  // Disable MSE
  //
  PciSegmentAnd16 (PciBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  //
  // Clear lower base address
  //
  PciSegmentWrite32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, 0);
}

/**
  Returns the BoardId ID of the platform from Smbus I/O port expander PCA9555PW.

  @param[in]  BoardId           BoardId ID as determined through the Smbus.
**/
VOID
EFIAPI
InternalGetBoardIdFromSmbus (
  OUT UINT16          *BoardId
  )
{
  UINT8                    BomId;
  SMBUS_INPUT_PORT0        SmbusInputPort0Info;
  SMBUS_INPUT_PORT1        SmbusInputPort1Info;
  EFI_STATUS               Status0;
  EFI_STATUS               Status1;
  GPIO_CONFIG              GppC0Default;
  GPIO_CONFIG              GppC1Default;
  GPIO_CONFIG              PseI2cGpioConfig;
  UINT64                   PseI2cBaseAddress;
  UINTN                    TempMmioBase;
  UINT8                    WriteBuffer0[1];
  UINT8                    WriteBuffer1[1];
  UINT8                    ReadBuffer0[1] = {0};
  UINT8                    ReadBuffer1[1] = {0};

  Status0 = EFI_DEVICE_ERROR;
  Status1 = EFI_DEVICE_ERROR;

  SmbusInputPort0Info.InputPort0Raw = SmBusReadDataByte (SMBUS_LIB_ADDRESS(SMBUS_IO_EXPANDER_SLAVE_ADDRESS, SMBUS_IO_EXPANDER_INPUT_PORT0_CMD, 0, 0), &Status0);
  SmbusInputPort1Info.InputPort1Raw = SmBusReadDataByte (SMBUS_LIB_ADDRESS(SMBUS_IO_EXPANDER_SLAVE_ADDRESS, SMBUS_IO_EXPANDER_INPUT_PORT1_CMD, 0, 0), &Status1);

  if ((Status0 == EFI_SUCCESS) && (Status1 == EFI_SUCCESS)) {
    DEBUG ((DEBUG_INFO, "Raw data from Input Port 0 is 0x%x\n", SmbusInputPort0Info.InputPort0Raw));
    DEBUG ((DEBUG_INFO, "Raw data from Input Port 1 is 0x%x\n", SmbusInputPort1Info.InputPort1Raw));

    *BoardId = (UINT16) SmbusInputPort1Info.InputPort1Fields.BoardId;
    *BoardId &= 0xF;
    if (IsSimicsEnvironment ()) {
      //Due to previous use board id 2, now change to 3, use it for simics
      *BoardId = BoardIdEhlLp4xType4Rvp1;
    }
    // For EHL A0 Power On, Board id 0x2 will treat as EHL RVP1 which is 0x3
    if((*BoardId) == BoardIdJslLp4xType4Rvp1) {
      *BoardId = BoardIdEhlLp4xType4Rvp1;
    }
    BomId = (UINT8) ((SmbusInputPort0Info.InputPort0Fields.BomId << 4) | SmbusInputPort1Info.InputPort1Fields.BomId);
    BomId &= 0x1F;

    PcdSet16S (PcdBoardId, *BoardId);
    PcdSet16S (PcdBoardBomId, BomId);
    PcdSet16S (PcdBoardRev, (UINT16) (SmbusInputPort0Info.InputPort0Fields.FabId));
    PcdSet16S (PcdMemId, SmbusInputPort0Info.InputPort0Fields.MemId);
    PcdSetBoolS (PcdSpdPresent, (BOOLEAN) (SmbusInputPort0Info.InputPort0Fields.SpdPresent));

    DEBUG ((DEBUG_INFO, "Fields.BoardId from Smbus Io expander is 0x%x\n", PcdGet16 (PcdBoardId)));
    DEBUG ((DEBUG_INFO, "Fields.BomId from Smbus Io expander is 0x%x\n", PcdGet16 (PcdBoardBomId)));
    DEBUG ((DEBUG_INFO, "Fields.FabId from Smbus Io expander is 0x%x\n", PcdGet16 (PcdBoardRev)));
    DEBUG ((DEBUG_INFO, "Fields.SpdPresent from Smbus Io expander is %x\n", PcdGetBool (PcdSpdPresent)));
  } else {
    DEBUG ((DEBUG_ERROR, "Failed to get Board ID from Smbus Io expander\n"));
    // EHL PO test
    DEBUG ((DEBUG_INFO, "EHL PO test: try to get Board ID from PSE I2C\n"));
    GpioGetPadConfig (GPIO_VER3_GPP_C0, &GppC0Default);
    GpioGetPadConfig (GPIO_VER3_GPP_C1, &GppC1Default);
    ZeroMem (&PseI2cGpioConfig, sizeof (GPIO_CONFIG));
    PseI2cGpioConfig.PadMode = GpioPadModeNative2;
    GpioSetPadConfig (GPIO_VER3_GPP_C0, &PseI2cGpioConfig); // SMB_CLK_OSE_I2C3_SCLK_SV_HDR
    GpioSetPadConfig (GPIO_VER3_GPP_C1, &PseI2cGpioConfig); // SMB_DATA_OSE_I2C3_SDAT_SV_HDR

    PseI2cBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                          DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_PSE_I2C3,
                          PCI_FUNCTION_NUMBER_PCH_PSE_I2C3,
                          0
                          );

    DEBUG ((DEBUG_INFO, "EHL PO test: PSE I2C VID and DID = 0x%x\n", PciSegmentRead32 (PseI2cBaseAddress)));
    TempMmioBase = PcdGet32 (PcdSiliconInitTempMemBaseAddr);

    PseI2cEnableMmio (PseI2cBaseAddress, TempMmioBase);

    WriteBuffer0[0] = SMBUS_IO_EXPANDER_INPUT_PORT0_CMD;
    Status0 = I2cWriteRead (
              TempMmioBase,
              SMBUS_IO_EXPANDER_SLAVE_ADDRESS,
              1,
              WriteBuffer0,
              1,
              ReadBuffer0,
              WAIT_1_SECOND
              );

    WriteBuffer1[0] = SMBUS_IO_EXPANDER_INPUT_PORT1_CMD;
    Status1 = I2cWriteRead (
                TempMmioBase,
                SMBUS_IO_EXPANDER_SLAVE_ADDRESS,
                1,
                WriteBuffer1,
                1,
                ReadBuffer1,
                WAIT_1_SECOND
                );

    if ((Status0 == EFI_SUCCESS) && (Status1 == EFI_SUCCESS)) {
      SmbusInputPort0Info.InputPort0Raw = ReadBuffer0[0];
      SmbusInputPort1Info.InputPort1Raw = ReadBuffer1[0];

      DEBUG ((DEBUG_INFO, "EHL PO test: Raw data from Input Port 0 is 0x%x\n", SmbusInputPort0Info.InputPort0Raw));
       DEBUG ((DEBUG_INFO, "EHL PO test: Raw data from Input Port 1 is 0x%x\n", SmbusInputPort1Info.InputPort1Raw));

      PseI2cDisableMmio (PseI2cBaseAddress);

      // Restore PSE I2C GPIO settings
      GpioSetPadConfig (GPIO_VER3_GPP_C0, &GppC0Default);
      GpioSetPadConfig (GPIO_VER3_GPP_C1, &GppC1Default);

      *BoardId = (UINT16) SmbusInputPort1Info.InputPort1Fields.BoardId;
      *BoardId &= 0xF;

      DEBUG ((DEBUG_INFO, "EHL PO test: BoardId is 0x%x\n", *BoardId));

      if (IsSimicsEnvironment ()) {
        //Due to previous use board id 2, now change to 3, use it for simics
        *BoardId = BoardIdEhlLp4xType4Rvp1;
      }
      // For EHL A0 Power On, Board id 0x2 will treat as EHL RVP1 which is 0x3
      if((*BoardId) == BoardIdJslLp4xType4Rvp1) {
        *BoardId = BoardIdEhlLp4xType4Rvp1;
      }
      BomId = (UINT8) ((SmbusInputPort0Info.InputPort0Fields.BomId << 4) | SmbusInputPort1Info.InputPort1Fields.BomId);
      BomId &= 0x1F;

      PcdSet16S (PcdBoardId, *BoardId);
      PcdSet16S (PcdBoardBomId, BomId);
      PcdSet16S (PcdBoardRev, (UINT16) (SmbusInputPort0Info.InputPort0Fields.FabId));
      PcdSet16S (PcdMemId, SmbusInputPort0Info.InputPort0Fields.MemId);
      PcdSetBoolS (PcdSpdPresent, (BOOLEAN) (SmbusInputPort0Info.InputPort0Fields.SpdPresent));

      DEBUG ((DEBUG_INFO, "EHL PO test: Fields.BoardId from Pse I2c Io expander is 0x%x\n", PcdGet16 (PcdBoardId)));
      DEBUG ((DEBUG_INFO, "EHL PO test: Fields.BomId from Pse I2c Io expander is 0x%x\n", PcdGet16 (PcdBoardBomId)));
      DEBUG ((DEBUG_INFO, "EHL PO test: Fields.FabId from Pse I2c Io expander is 0x%x\n", PcdGet16 (PcdBoardRev)));
      DEBUG ((DEBUG_INFO, "EHL PO test: Fields.SpdPresent from Pse I2c Io expander is %x\n", PcdGetBool (PcdSpdPresent)));
    } else {
      DEBUG ((DEBUG_ERROR, "EHL PO test: Failed to get Board ID from Pse I2c Io expander\n"));
      DEBUG ((DEBUG_ERROR, "EHL PO test: Use hard coded board Id\n"));
      // WA: hard code board id to 0x5
      *BoardId = (UINT16) BoardIdEhlLp4xType3Crb;
      PcdSet16S (PcdBoardId, *BoardId);
      PcdSet16S (PcdBoardBomId, (UINT16) (0x00));
      PcdSet16S (PcdBoardRev, (UINT16) (0x00));
      PcdSetBoolS (PcdSpdPresent, (BOOLEAN) (0x00));
    }
  }
}

BOOLEAN
IsEhlBoard (
  OUT UINT16          *BoardId
  )
{
#if FixedPcdGetBool(PcdEcEnable) == 1
  RETURN_STATUS   Status;
  BOARD_ID_INFO   EcBoardInfo;
  UINT8           DataBuffer[2];
  UINT8           Retry;
#endif
  InternalGetBoardIdFromSmbus (BoardId);
  if ((*BoardId == BoardIdEhlLp4xType4Erb)  ||
      (*BoardId == BoardIdJslLp4xType4Rvp1) ||
      (*BoardId == BoardIdEhlLp4xType4Rvp1) ||
      (*BoardId == BoardIdEhlDdr4Type3Rvp2) ||
      (*BoardId == BoardIdEhlLp4xType3Crb)) {
    DEBUG ((DEBUG_INFO, "Elkhartlake Board detected\n"));
    return TRUE;
  }
#if FixedPcdGetBool(PcdEcEnable) == 1
  else {
    //
    // Detect EC Revision
    //
    Retry = 5;
    do {
      Status = DetectEcRevision ((UINT8 *)DataBuffer);
      Retry--;
      if ((RETURN_ERROR (Status)) && (Retry != 0)) {
        MicroSecondDelay (STALL_TIME);
      }
    } while ((RETURN_ERROR (Status)) && (Retry != 0));
    if (RETURN_ERROR (Status)) {
      PcdSetBoolS (PcdEcPresent, FALSE);
    } else {
      PcdSetBoolS (PcdEcPresent, TRUE);
      PcdSet8S (PcdEcMajorRevision, DataBuffer[0]);
      PcdSet8S (PcdEcMinorRevision, DataBuffer[1]);
    }

    if (PcdGetBool (PcdEcPresent)) {
      Status = GetBoardInfo ((UINT16 *) &EcBoardInfo);
      if (RETURN_ERROR (Status)) {
        return FALSE;
      }
      if (EcBoardInfo.EhlRvpFields.BoardId == 0x3) {
        DEBUG ((DEBUG_INFO, "Jasperlake Board detected\n"));
        *BoardId = BoardIdJslLp4xErb;
        return TRUE;
      }
    }
  }
#endif
  return FALSE;
}

EFI_STATUS
EFIAPI
EhlBoardDetect (
  VOID
  )
{
  UINT16          BoardId;
  UINTN           Size;
  UINT16          SkuId;
  BOOLEAN         IsEhlBoardExist;
#if FixedPcdGetBool(PcdEcEnable) == 1
  RETURN_STATUS   Status;
  UINT8           EcData;
#endif
  BoardId         = 0;
  SkuId           = 0;
  IsEhlBoardExist = FALSE;

  if (LibPcdGetSku () != 0) {
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "Elkhartlake Board Detection Callback\n"));

  IsEhlBoardExist = IsEhlBoard (&BoardId);
  if (IsEhlBoardExist) {
    SkuId = BoardIdEhlLp4xType4Erb;  // TODO: SKU ID needs to be implemented right way after the code merge. use BoardId temporarily.
    LibPcdSetSku (SkuId);
    //
    // To find out Board Name
    //
#if FixedPcdGetBool(PcdEcEnable) == 1
  if (PcdGetBool (PcdEcPresent)) {
    //
    // Check dock status if support
    //
    Status = GetPcieDockStatus (&EcData);
      if ((Status == EFI_SUCCESS) && (EcData & EC_B_DOCK_STATUS_ATTACH)) {
        PcdSetBoolS (PcdDockAttached, TRUE);
      }
    }
#endif
    PcdSet16 (PcdBoardId, BoardId);
    Size = StrSize (mBoardIdIndex[BoardId]);
    PcdSetPtrS (PcdBoardName, &Size, mBoardIdIndex[BoardId]);
    PcdSet8S (PcdBoardType, BoardTypeRvp);
    PcdSet8S (PcdPlatformType, TypeUltUlx);
    PcdSet8S (PcdPlatformFlavor, FlavorMobile);
    if (PcdSet64S (PcdAcpiDefaultOemTableId, ACPI_OEM_TABLE_ID_EHL) != EFI_SUCCESS) {
      DEBUG ((DEBUG_INFO, "Set PcdAcpiDefaultOemTableId error!!!\n"));
    }

    DEBUG ((DEBUG_INFO, "BoardId is 0x%x\n", PcdGet16 (PcdBoardId)));
    DEBUG ((DEBUG_INFO, "BomId is 0x%x\n", PcdGet16 (PcdBoardBomId)));
    DEBUG ((DEBUG_INFO, "FabId is 0x%x\n", PcdGet16 (PcdBoardRev)));

    DEBUG ((DEBUG_INFO, "Platform Information:\nPlatformType: %x\nBoardName: %s\n", PcdGet8 (PcdPlatformType), PcdGetPtr (PcdBoardName)));
    DEBUG ((DEBUG_INFO, "PlatformFlavor: %x\n", PcdGet8 (PcdPlatformFlavor)));
    DEBUG ((DEBUG_INFO, "BoardType: %x\n", PcdGet8 (PcdBoardType)));
    DEBUG ((DEBUG_INFO, "EcPresent: %d\nSpdPresent: %d\n", PcdGetBool (PcdEcPresent), PcdGetBool (PcdSpdPresent)));
    DEBUG ((DEBUG_INFO, "PcdAcpiDefaultOemTableId: 0x%lx\n", PcdGet64 (PcdAcpiDefaultOemTableId)));
    DEBUG ((DEBUG_INFO, "SKU_ID: 0x%x\n", LibPcdGetSku()));
  }
  return EFI_SUCCESS;
}
