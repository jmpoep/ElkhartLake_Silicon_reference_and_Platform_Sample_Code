/** @file
  Disable Cache As Ram

@copyright
  Copyright (c) 2014 - 2019, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/CacheAsRamLib.h>
#include <Register/Msr.h>
#include <CpuRegs.h>
#include <Library/DebugLib.h>
#include <Library/CpuCommonLib.h>

VOID
CacheInvd (
  VOID
  );

/**
  Disable NEM (No Eviction Mode).

  @param[in] DisableCar       TRUE means use Cache INVD, FALSE means use WBINVD
**/
VOID
EFIAPI
DisableCacheAsRam (
  IN BOOLEAN DisableCar
  )
{
  UINT64 CacheAsRamMsr;
  UINT32 Index;
  UINT32 McEnd;
  UINT32 McMaxBank;
  UINT8 Cbo0Index;
  MSR_IA32_MCG_CAP_REGISTER MsrMcgCap;

  CacheAsRamMsr = AsmReadMsr64 (NO_EVICT_MODE);

  //
  // Disable No-Eviction Mode Run State by clearing NO_EVICT_MODE MSR 2E0h bit [1] = 0
  //
  CacheAsRamMsr &= ~((UINT64)B_NO_EVICT_MODE_RUN);
  AsmWriteMsr64 (NO_EVICT_MODE, CacheAsRamMsr);

  //
  // Can't combine this MSR write with previous MSR write.
  // Disable No-Eviction Mode Setup State by clearing NO_EVICT_MODE MSR 2E0h bit [0] = 0
  //
  CacheAsRamMsr &= ~((UINT64)B_NO_EVICT_MODE_SETUP);
  AsmWriteMsr64 (NO_EVICT_MODE, CacheAsRamMsr);

  if (DisableCar) {
    CacheInvd ();
  } else {
    AsmWbinvd();
  }

  //
  // After NEM is disabled, BIOS must clear any Machine Check Bank errors that may
  // have occurred as the result of ... MLC to to LLC Evictions.
  //

  //
  // Get number of max number of banks.
  //
  MsrMcgCap.Uint64 = AsmReadMsr64 (MSR_IA32_MCG_CAP);
  McMaxBank = (UINT32) MsrMcgCap.Bits.Count;

  //
  // Safety check - make sure don't clear above last bank from capabilities.
  //
  McEnd = ((AsmReadMsr64 (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_EDRAM_ENABLE_MASK) != 0) ? McMaxBank - 1 : McMaxBank;
  DEBUG ((DEBUG_INFO, "McBank End Index 0x%x \n", McEnd));

  //
  // Get CBO0 Bank Index.
  //
  Cbo0Index = GetCbo0BankIndex ();

  for (Index = Cbo0Index; Index < McEnd; Index++) {
    AsmWriteMsr64 (MSR_IA32_MC0_STATUS + Index * 4, 0);
  }
}
