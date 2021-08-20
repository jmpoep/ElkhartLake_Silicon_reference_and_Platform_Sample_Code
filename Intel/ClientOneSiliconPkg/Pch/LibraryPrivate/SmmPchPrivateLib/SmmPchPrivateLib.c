/** @file
  PCH SMM private lib.

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

#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/CpuPlatformLib.h>
#include <CpuRegs.h>

STATIC UINT32 mBiosGuardEnabled = ~0u;

/**
  Set InSmm.Sts bit
**/
VOID
PchSetInSmmSts (
  VOID
  )
{
  UINT32      Data32;

  //
  // When BIOS GUARD is enabled, the MSR 1FEh is invalid.
  //
  if (mBiosGuardEnabled != 0) {
    if (mBiosGuardEnabled == 1) {
      return;
    }
    mBiosGuardEnabled = IsBiosGuardEnabled () ? 1 : 0;
    if (mBiosGuardEnabled == 1) {
      return;
    }
  }

  ///
  /// Read memory location FED30880h OR with 00000001h, place the result in EAX,
  /// and write data to lower 32 bits of MSR 1FEh (sample code available)
  ///
  Data32 = MmioRead32 (0xFED30880);
  AsmWriteMsr32 (MSR_SPCL_CHIPSET_USAGE, Data32 | BIT0);
  ///
  /// Read FED30880h back to ensure the setting went through.
  ///
  Data32 = MmioRead32 (0xFED30880);
}

/**
  Clear InSmm.Sts bit
**/
VOID
PchClearInSmmSts (
  VOID
  )
{
  UINT32      Data32;

  //
  // When BIOS GUARD is enabled, the MSR 1FEh is invalid.
  //
  if (mBiosGuardEnabled != 0) {
    if (mBiosGuardEnabled == 1) {
      return;
    }
    mBiosGuardEnabled = IsBiosGuardEnabled () ? 1 : 0;
    if (mBiosGuardEnabled == 1) {
      return;
    }
  }

  ///
  /// Read memory location FED30880h AND with FFFFFFFEh, place the result in EAX,
  /// and write data to lower 32 bits of MSR 1FEh (sample code available)
  ///
  Data32 = MmioRead32 (0xFED30880);
  AsmWriteMsr32 (MSR_SPCL_CHIPSET_USAGE, Data32 & (UINT32) (~BIT0));
  ///
  /// Read FED30880h back to ensure the setting went through.
  ///
  Data32 = MmioRead32 (0xFED30880);
}
