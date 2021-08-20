/** @file
  Implementation of PeiBoardConfigLib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/PostCodeLib.h>
#include <Library/TimerLib.h>
#include <Library/EcMiscLib.h>
#include <Library/PeiDxeBoardIdsLib.h>
#include <Library/GpioLib.h>
#include <Library/BaseMemoryLib.h>

#include <PlatformBoardType.h>
#include <PlatformBoardId.h>
#include <PlatformBoardConfig.h>

#define STALL_TIME                  1000000 // 1,000,000 microseconds = 1 second

/**
  Returns the BoardId ID of the platform from the EC for Mobile.

  @param[in]  BoardId           BoardId ID as determined through the EC.

  @retval     EFI_SUCCESS       The function completed successfully.
  @retval     EFI_DEVICE_ERROR  EC fails to respond.
**/
EFI_STATUS
EFIAPI
InternalGetBoardId (
  OUT UINT16          *BoardId
  )
{
  EFI_STATUS    Status;
  BOARD_ID_INFO EcBoardInfo;

  Status = EFI_SUCCESS;

  //
  // Return BoardIdUnknown1 in case of error.
  //
  *BoardId = BoardIdUnknown1;

  EcBoardInfo.Raw = 0;
  Status = GetBoardInfo ((UINT16 *)&EcBoardInfo);
  DEBUG ((DEBUG_INFO, "Raw Board ID from EC is 0x%x\n", EcBoardInfo.Raw));

  if (Status == EFI_SUCCESS) {
    *BoardId = (UINT16)EcBoardInfo.EhlRvpFields.BoardId;
    *BoardId &= 0x03F;
    PcdSet16S (PcdBoardId, (UINT16) (EcBoardInfo.EhlRvpFields.BoardId));
    PcdSet16S (PcdBoardBomId, (UINT8) (EcBoardInfo.EhlRvpFields.BomId));
    PcdSet16S (PcdBoardRev, (UINT8) (EcBoardInfo.EhlRvpFields.FabId));
    PcdSetBoolS (PcdSpdPresent, (BOOLEAN) (EcBoardInfo.EhlRvpFields.SpdPresent));

    DEBUG ((DEBUG_INFO, "Fields.BoardId from EC is 0x%x\n", PcdGet16 (PcdBoardId)));
    DEBUG ((DEBUG_INFO, "Fields.BomId from EC is 0x%x\n", PcdGet16 (PcdBoardBomId)));
    DEBUG ((DEBUG_INFO, "Fields.FabId from EC is 0x%x\n", PcdGet16 (PcdBoardRev)));
    DEBUG ((DEBUG_INFO, "Fields.SpdPresent from EC = %x\n", PcdGetBool (PcdSpdPresent)));
  } else {
    DEBUG ((DEBUG_ERROR, "Failed to get Board ID from EC\n"));
  }

  return Status;
}

VOID
EFIAPI
InternalUpdateRvpBoardConfig (
  IN OUT UINT16         BoardId
  )
{
  UINTN         Size;
  UINT8         BoardType;
  UINT8         PlatformType;
  UINT8         PlatformFlavor;

  if (BoardId < mSizeOfmBoardIndex) {
    Size = StrSize (mBoardIdIndex[BoardId]);
    PcdSetPtrS (PcdBoardName, &Size, mBoardIdIndex[BoardId]);
  }

  //
  // Update Board Type/Platform Type/Platform Flavor
  //
  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdEhlLp4xType3Crb:
    case BoardIdJslLp4xType4Rvp1:
    case BoardIdJslLp4xErb:
      BoardType = BoardTypeRvp;
      PlatformType = TypeUltUlx;
      PlatformFlavor = FlavorMobile;
      if (PcdSet64S (PcdAcpiDefaultOemTableId, ACPI_OEM_TABLE_ID_EHL) != EFI_SUCCESS) {
         DEBUG ((DEBUG_INFO, "Set PcdAcpiDefaultOemTableId error!!!\n"));
      }
      break;

    default:
      BoardType = BoardTypeRvp;
      PlatformType = TypeUnknown;
      PlatformFlavor = FlavorUnknown;
      break;
  }

  PcdSet8S (PcdBoardType, BoardType);
  PcdSet8S (PcdPlatformType, PlatformType);
  PcdSet8S (PcdPlatformFlavor, PlatformFlavor);

  DEBUG ((DEBUG_INFO, "PcdAcpiDefaultOemTableId is 0x%llX\n", PcdGet64 (PcdAcpiDefaultOemTableId)));
}

/**
  Procedure to detect current board HW configuration.

**/
VOID
GetBoardConfig ( //@todo Decouple GetBoard Config
  VOID           //      All board are using same function
  )
{
  UINT16          BoardId;
  RETURN_STATUS   Status;
  UINT8           DataBuffer[2];
  UINT8           Retry;
  UINT8           EcData;

  //
  // Get Platform Info and fill the Hob
  //
  EcData    = 0;
  BoardId   = BoardIdUnknown1;
  ZeroMem (&DataBuffer, sizeof (DataBuffer));
  PcdSet8S (PcdBoardType, BoardTypeMax);
  PcdSetBoolS (PcdEcPresent, FALSE);

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

  //
  // get RVP board ID
  //
  if (PcdGetBool (PcdEcPresent)) {
    // get board ID from EC
    DEBUG ((DEBUG_INFO, "Reading Board ID from EC ...\n"));
    do {
      Status = InternalGetBoardId (&BoardId);
    } while (Status != EFI_SUCCESS);
    DEBUG ((DEBUG_INFO, "Got Board ID from EC: 0x%x  \n", BoardId));
    if(BoardId == 0x3) {
      BoardId = BoardIdJslLp4xErb;
    }
  } else {
    // todo: get board ID on an EC less board. hard code 0 for temp use
    BoardId = 0;
  }

  //
  // update RVP board config
  //
  InternalUpdateRvpBoardConfig (BoardId);
  //
  // check dock status if support
  //
  if ((PcdGetBool (PcdEcPresent)) && (PcdGet8 (PcdPlatformFlavor) == FlavorMobile)) {
    Status = GetPcieDockStatus (&EcData);
    if ((Status == EFI_SUCCESS) && (EcData & EC_B_DOCK_STATUS_ATTACH)) {
      PcdSetBoolS (PcdDockAttached, TRUE);
    }
  }

  DEBUG ((DEBUG_INFO, "Platform Information:\nPlatformType: %x\nBoardName: %s\n", PcdGet8 (PcdPlatformType), PcdGetPtr (PcdBoardName)));
  DEBUG ((DEBUG_INFO, "PlatformFlavor: %x\nBoardID: 0x%x\n", PcdGet8 (PcdPlatformFlavor), BoardId));
  DEBUG ((DEBUG_INFO, "BoardRev: %x\nBoardBomId: %x\nBoardType: %x\n", PcdGet16 (PcdBoardRev), PcdGet16 (PcdBoardBomId), PcdGet8 (PcdBoardType)));
  DEBUG ((DEBUG_INFO, "PlatformGeneration: %x\nEcPresent: %d\nSpdPresent: %d\n", PcdGet8 (PcdPlatformGeneration), PcdGetBool (PcdEcPresent), PcdGetBool (PcdSpdPresent)));

  //
  // Halt the system if BoardID unknown
  //
  if (BoardId == BoardIdUnknown1) {
    UINT32 code = 0;

    switch (PcdGet8 (PcdBoardType)) {
      case BoardTypeRvp:
        code = 0xBD10;
        break;
      case BoardTypeSv:
        code = 0xBD20;
        break;
      default:
        code = 0xBD30;
        break;
    }
    DEBUG ((DEBUG_ERROR, "Platform BoardID unknown, set PostCode=0x%x and halt the system !\n", code));

    PostCode (code);
    CpuDeadLoop ();
  }

}

/**
  Count the number of GPIO settings in the Table.

  @param[in]  GpioTable   The pointer of GPIO config table
  @param[out] GpioCount   The number of GPIO config entries
**/
VOID
GetGpioTableSize (
  GPIO_INIT_CONFIG   *GpioTable,
  OUT UINT16         *GpioCount
  )
{
  *GpioCount = 0;
  while (GpioTable[*GpioCount].GpioPad != 0 && *GpioCount < MAX_GPIO_PINS) {
    DEBUG ((DEBUG_INFO, "GpioTable[%d]->GpioPad = %x\n", *GpioCount, GpioTable[*GpioCount].GpioPad));
    (*GpioCount) ++;
  }
}

/**
  Configures GPIO

  @param[in]  GpioTable       Point to Platform Gpio table
  @param[in]  GpioTableCount  Number of Gpio table entries
**/
STATIC
VOID
ConfigureGpio (
  IN GPIO_INIT_CONFIG                 *GpioTable,
  IN UINT16                           GpioTableCount
  )
{
  EFI_STATUS          Status;

  DEBUG ((DEBUG_INFO, "ConfigureGpio() Start\n"));

  Status = GpioConfigurePads (GpioTableCount, GpioTable);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "ConfigureGpio() End\n"));
}

/**
  Configure GPIO Before Memory is initialized.

  @param[in]  GpioTable  Pointer to Gpio table
**/
VOID
GpioInit (
  IN GPIO_INIT_CONFIG *GpioTable
  )
{
  UINT16             GpioCount;

  if (GpioTable != 0) {
    GpioCount = 0;
    GetGpioTableSize (GpioTable, &GpioCount);
    if (GpioCount != 0) {
      ConfigureGpio ((VOID *) GpioTable, GpioCount);
    }
  }
}

/**
  Configure GPIO group GPE tier.

**/
VOID
GpioGroupTierInit (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "GpioGroupTierInit Start\n"));

  if (PcdGet32 (PcdGpioGroupToGpeDw0)) {
    GpioSetGroupToGpeDwX (PcdGet32 (PcdGpioGroupToGpeDw0),
                          PcdGet32 (PcdGpioGroupToGpeDw1),
                          PcdGet32 (PcdGpioGroupToGpeDw2));
  }
  DEBUG ((DEBUG_INFO, "GpioGroupTierInit End\n"));
}
