/** @file
  This file is BaseBfxTempRamLib library is used to obtain Temp Ram parameters

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BfxTempRamLib.h>
#include <CpuRegs.h>

#define NEM_TEMPORARY_RAM_BASE                       0x28
#define NEM_TEMPORARY_RAM_SIZE                       0x2C

/**
  Obtain Temporary RAM Base for BFX

  @retval Temporary RAM Base address
**/
UINT32
BfxGetTempRamBase (
  VOID
  )
{
  UINT32   Data32;
  UINT32   TempRamBase;

  Data32      = 0;
  TempRamBase = 0;

  Data32 = MmioRead32 ((UINTN) (TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_BOOTSTATUS + 0x04));
  if (Data32 != 0xFFFFFFFF) {
    if ((Data32 & B_CPU_BOOT_GUARD_BOOTSTATUS_BLOCK_BOOT_ENABLED) == V_CPU_BOOT_GUARD_BOOTSTATUS_BLOCK_BOOT_ENABLED) {
      Data32 = MmioRead32 ((UINTN) (TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_NEM_MAP_STRUCTURE_ADDRESS));
      Data32 = MmioRead32 ((UINTN) (Data32 + NEM_TEMPORARY_RAM_BASE));
      if (Data32 != 0x00000000) {
        TempRamBase = Data32;
      }
    }
  }
  if (TempRamBase == 0) {
    ASSERT (FALSE);
  }
  return TempRamBase;
}

/**
  Obtain Temporary RAM Size for BFX

  @retval Temporary RAM Size
**/
UINT32
BfxGetTempRamSize (
  VOID
  )
{
  UINT32   Data32;
  UINT32   TempRamSize;

  Data32      = 0;
  TempRamSize = 0;

  Data32 = MmioRead32 ((UINTN) (TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_BOOTSTATUS + 0x04));
  if (Data32 != 0xFFFFFFFF) {
    if ((Data32 & B_CPU_BOOT_GUARD_BOOTSTATUS_BLOCK_BOOT_ENABLED) == V_CPU_BOOT_GUARD_BOOTSTATUS_BLOCK_BOOT_ENABLED) {
      Data32 = MmioRead32 ((UINTN) (TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_NEM_MAP_STRUCTURE_ADDRESS));
      Data32 = MmioRead32 ((UINTN) (Data32 + NEM_TEMPORARY_RAM_SIZE));
      if (Data32 != 0x00000000) {
        TempRamSize = Data32;
      }
    }
  }
  if (TempRamSize == 0) {
    ASSERT (FALSE);
  }
  return TempRamSize;
}
