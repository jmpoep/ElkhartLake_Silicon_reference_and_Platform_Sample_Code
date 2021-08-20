/** @file
  Flash decode library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2007 - 2017 Intel Corporation.

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

#include <Base.h>
#include <Library/PciSegmentLib.h>

//
// FWH_DEC_EN1-Firmware Hub Decode Enable Register (LPC I/F-D31:F0)
// ---------------------------------------------
// Offset Address: D8h-D9h   Attribute: R/W, RO
// Default Value: FFCFh       Size: 16 bits
// ---------------------------------------------
// Bit 15 : FWH_F8_EN - RO (FFF80000h - FFFFFFFFh, FFB80000h - FFBFFFFFh)
// Bit 14 : FWH_F0_EN - RW (FFF00000h - FFF7FFFFh, FFB00000h - FFB7FFFFh)
// Bit 13 : FWH_E8_EN - RW (FFE80000h - FFEFFFFFh, FFA80000h - FFAFFFFFh)
// Bit 12 : FWH_E0_EN - RW (FFE00000h - FFE7FFFFh, FFA00000h - FFA7FFFFh)
// Bit 11 : FWH_D8_EN - RW (FFD80000h - FFDFFFFFh, FF980000h - FF9FFFFFh)
// Bit 10 : FWH_D0_EN - RW (FFD00000h - FFD7FFFFh, FF900000h - FF97FFFFh)
// Bit 09 : FWH_C8_EN - RW (FFC80000h - FFCFFFFFh, FF880000h - FF8FFFFFh)
// Bit 08 : FWH_C0_EN - RW (FFC00000h - FFC7FFFFh, FF800000h - FF87FFFFh)
// Bit 07 : FWH_Legacy_F_EN - RW (F0000h - FFFFFh)
// Bit 06 : FWH_Legacy_E_EN - RW (E0000h - EFFFFh)
// Bit 05 : Reserved
// Bit 04 : Reserved
// Bit 03 : FWH_70_EN - RW (FFF70000h - FF7FFFFFh, FF300000h - FF3FFFFFh)
// Bit 02 : FWH_60_EN - RW (FFF60000h - FF6FFFFFh, FF200000h - FF2FFFFFh)
// Bit 01 : FWH_50_EN - RW (FFF50000h - FF5FFFFFh, FF100000h - FF1FFFFFh)
// Bit 00 : FWH_40_EN - RW (FFF40000h - FF4FFFFFh, FF000000h - FF0FFFFFh)
// ---------------------------------------------
// This register effects the BIOS decode regardless of whether the BIOS is resident on LPC or SPI.
//

typedef struct {
  PHYSICAL_ADDRESS   Address;
  UINT64             Length;
  UINT8              Bit;
} FLASH_DECODE_INFO;

GLOBAL_REMOVE_IF_UNREFERENCED FLASH_DECODE_INFO  mFlashDecodeInfo[] = {
  {0xFFF80000, 0x80000,  15},
  {0xFFF00000, 0x80000,  14},
  {0xFFE80000, 0x80000,  13},
  {0xFFE00000, 0x80000,  12},
  {0xFFD80000, 0x80000,  11},
  {0xFFD00000, 0x80000,  10},
  {0xFFC80000, 0x80000,  9},
  {0xFFC00000, 0x80000,  8},
  {0xFFB80000, 0x80000,  15},
  {0xFFB00000, 0x80000,  14},
  {0xFFA80000, 0x80000,  13},
  {0xFFA00000, 0x80000,  12},
  {0xFF980000, 0x80000,  11},
  {0xFF900000, 0x80000,  10},
  {0xFF880000, 0x80000,  9},
  {0xFF800000, 0x80000,  8},
  {0xFF700000, 0x100000, 3},
  {0xFF600000, 0x100000, 2},
  {0xFF500000, 0x100000, 1},
  {0xFF400000, 0x100000, 0},
  {0xFF300000, 0x100000, 3},
  {0xFF200000, 0x100000, 2},
  {0xFF100000, 0x100000, 1},
  {0xFF000000, 0x100000, 0},
  {0xF0000,    0x10000,  7},
  {0xE0000,    0x10000,  6},
};

UINT16
CalculateFlashDecodeBit (
  IN PHYSICAL_ADDRESS   Address,
  IN UINT64             Length
  )
{
  UINTN  Index;
  UINT16 Value;

  Value = 0;
  for (Index = 0; Index < sizeof(mFlashDecodeInfo)/sizeof(mFlashDecodeInfo[0]); Index++) {
    if ((Address + Length <= mFlashDecodeInfo[Index].Address) ||
        (mFlashDecodeInfo[Index].Address + mFlashDecodeInfo[Index].Length <= Address)) {
      continue;
    }
    Value = Value | (1 << mFlashDecodeInfo[Index].Bit);
  }

  return Value;
}

/**
  Enable flash decode region.

  @retval RETURN_SUCCESS              Requested flash region is enabled.
  @retval RETURN_DEVICE_ERROR         Requested flash region is not enabled.
**/
RETURN_STATUS
EFIAPI
FlashRegionEnable (
  IN PHYSICAL_ADDRESS   Address,
  IN UINT64             Length
  )
{
  UINT16  DecodeValue;

  DecodeValue = CalculateFlashDecodeBit (Address, Length);
  PciSegmentOr16 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0x1F, 0x0, 0xD8), DecodeValue);
  return RETURN_SUCCESS;
}

/**
  Disable flash decode region.

  @retval RETURN_SUCCESS              Requested flash region is enabled.
  @retval RETURN_DEVICE_ERROR         Requested flash region is not enabled.
**/
RETURN_STATUS
EFIAPI
FlashRegionDisable (
  IN PHYSICAL_ADDRESS   Address,
  IN UINT64             Length
  )
{
  UINT16  DecodeValue;

  DecodeValue = CalculateFlashDecodeBit (Address, Length);
  PciSegmentAnd16 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0x1F, 0x0, 0xD8), ~DecodeValue);
  return RETURN_SUCCESS;
}
