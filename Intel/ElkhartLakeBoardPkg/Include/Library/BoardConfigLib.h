/** @file
  Function prototype of BoardConfigLib.

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

#ifndef _BOARD_CONFIG_LIB_H_
#define _BOARD_CONFIG_LIB_H_

#include <Library/GpioLib.h>
#include <Library/SetupInitLib.h>
#include <HdAudioConfig.h>
#include <PlatformBoardConfig.h>

#define SIZE_OF_FIELD(TYPE, Field) (sizeof (((TYPE *)0)->Field))

#define SIZE_OF_TABLE(TABLE, TYPE) (sizeof (TABLE) / sizeof (TYPE))

//
// @todo Define BOARD_CONFIG
//
#define BOARD_CONFIG PLATFORM_INFO

/**
  Procedure to detect current board HW configuration.

**/
VOID
EFIAPI
GetBoardConfig (
  VOID
  );

EFI_STATUS
PatchConfigurationDataInit (
  IN CONFIG_PATCH_STRUCTURE  *ConfigPatchStruct,
  IN UINTN                   ConfigPatchStructSize
  );

/**
  Count the number of GPIO settings in the Table.

  @param[in]  GpioTable   The pointer of GPIO config table
  @param[out] GpioCount   The number of GPIO config entries
**/
VOID
GetGpioTableSize (
  GPIO_INIT_CONFIG   *GpioTable,
  OUT UINT16         *GpioCount
  );

/**
  Configure GPIO pads in PEI phase.

  @param[in]  GpioTable  Pointer to Gpio table
**/
VOID
GpioInit (
  IN GPIO_INIT_CONFIG *GpioTable
  );

/**
  Configure GPIO group GPE tier.

**/
VOID
GpioGroupTierInit (
  VOID
  );

/**
  Update board configure patch table.

  @param[in, out]  TargetPatchTable      Target patch table you want to be updated.
  @param[in, out]  TargetPatchTableSize  Target patch table size that you want to be updated.
  @param[in]       SourcePatchTable      Source patch table.
  @param[in]       SourcePatchTableSize  Source patch table size.

**/
VOID
UpdatePatchTable (
  IN OUT CONFIG_PATCH_STRUCTURE **TargetPatchTable,
  IN OUT UINTN                  *TargetPatchTableSize,
  IN     CONFIG_PATCH_STRUCTURE *SourcePatchTable,
  IN     UINTN                  SourcePatchTableSize
  );

/**
  Free unused patch table.

  @param[in, out]  PatchTable             Patch table you want to free memory.
  @param[in, out]  PatchTableSize         Patch table size that you want to free memory.

**/
VOID
FreePatchTable (
  IN OUT CONFIG_PATCH_STRUCTURE **PatchTable,
  IN OUT UINTN                  *PatchTableSize
  );

/**
  Check if given rootport has device connected and enable wake capability

  @param[in]  RpNum           An unsigned integer represent the root port number.

  @retval                     TRUE if endpoint was connected
  @retval                     FALSE if no endpoint was detected
**/
BOOLEAN
IsPcieEndPointPresent (
  IN UINT8 RpNum
  );

extern HDAUDIO_VERB_TABLE HdaVerbTableDisplayAudio;
extern HDAUDIO_VERB_TABLE HdaVerbTableAlc286S;
extern HDAUDIO_VERB_TABLE HdaVerbTableAlc298;
extern HDAUDIO_VERB_TABLE HdaVerbTableAlc700;
extern HDAUDIO_VERB_TABLE HdaVerbTableAlc701;
extern HDAUDIO_VERB_TABLE HdaVerbTableAlc274;
extern HDAUDIO_VERB_TABLE HdaVerbTableAlc711;

// LPDDR4 200b 8Gb die, DDP, 2 channels per die, x16
// Samsung K4F6E304Hx-MGCJ
// or Hynix H9HCNNNBUUxLHR-NMx
// or Micron MT53B512M32D2NP-053
// 3733, 32-34-34-79
// 2 ranks per channel, 2 SDRAMs per channel, 2x2x8Gb = 4GB total per channel
extern const UINT8 mLpddr4Ddp8Gb200bSpd;

// LPDDR4X 432b 16Gb die, QDP 2x16
// Samsung K3UH7H70MM-JGCJ
// 3733, 32-34-34-79
// 2 ranks per channel, 1 SDRAMs per rank, 4x16Gb = 8GB total per channel
extern const UINT8 mLpddr4xQdp16Gb432bSpd;

// LPDDR4X 556b 8Gb die, ODP, 1 channel per die, x16
// Micron MT53D1G64D8SQ-046
// 4266
// 2 ranks per channel, 2 SDRAMs per channel, 2x4x8Gb = 8GB total per channel
extern const UINT8 mLpddr4xOdp8Gb556bSpd;

// LPDDR4X 556b 4Gb die, QDP, 1 channel per die, x16
// Micron MT53D512M64D4RQ-046 WT:E
// 4266
// 2 ranks per channel, 2 SDRAMs per channel, 2x4x8Gb = 4GB total per channel
extern const UINT8 mLpddr4xQdp4Gb556bSpd;

extern const UINT8 mLpddr4Ddp16Gb200b1rSpd;

// LPDDR5 496b 12Gb die, QDP 1x16
// Samsung K3LK2K20BM-BGCN
// 5500, ??-??-??-??
// 16 Banks, 4 bank groups, 12Gb SDRAM density
// 16 Row bits, 10 Column bits
// Non-Monolithic DRAM Device, 4 dies, 4 Channels per die,
extern const UINT8 mLpddr5xQdp12Gb496bSpd;

// LPDDR4X 200b 16Gb die, DDP, 2 channel per die, 2x8
// Samsung  K4U6E3S4AA-MGCL
// 4267, 36-39-39-90
// 1 rank per channel, 2 SDRAMs per channel, 2x8GB = 16GB total per channel
extern const UINT8 mLpddr4xDdp16Gb200bSpd;


// LPDDR4X 200b 8Gb die, DDP, 1 channel per die, x16
// Hynix H9HCNNNBKMMLHR-NEE
// Micron MT53D512M32D2NP-046
// 4267, 36-39-39-90
// 1 rank per channel, 2 SDRAMs per channel, 2x2x8Gb = 4GB total per channel
extern const UINT8 mLpddr4xDdp8Gb200bSpd;

extern USB2_PHY_TABLE mUsb2PhyTuningTable;
// Default USB2 OC mapping
extern USB_OC_MAP_TABLE mUsb2OverCurrentMappingTable;
// Default USB3 OC mapping
extern USB_OC_MAP_TABLE mUsb3OverCurrentMappingTable;

extern const UINT8 DDR4_SPD_MTA4ATF51264HZ_3G2E1;
#endif // _BOARD_CONFIG_LIB_H_
