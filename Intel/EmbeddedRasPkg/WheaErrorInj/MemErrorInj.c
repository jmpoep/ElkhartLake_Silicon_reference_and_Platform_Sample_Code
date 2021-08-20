/** @file
  This file contains the functionality for the ME Error Injection.

  @copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2019 Intel Corporation. <BR>

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary    and
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
**/

#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include "WheaErrorInj.h"

#define MMIO_IBECC0         0xDC00
#define IBECC_ACTIVATE      0x0
#define ECC_ERROR_LOG       0x0170
#define ECC_INJ_ADDR_MASK   0x0180
#define ECC_INJ_ADDR_BASE   0x0188
#define ECC_INJ_CONTROL     0x0198

UINT32                                        mInjAddrValue;
extern   WHEA_EINJ_TRIGGER_ACTION_TABLE       *mEinjAction;
extern   WHEA_EINJ_PARAM_BUFFER               *mEinjParam;
extern   UINT8                                mErrorExpected;

/**
    Write Data to error injection address to seed the error in memory.

    @param Skt - Socket Id

    @retval None

**/
VOID
EFIAPI
SeeErrorAp (
  void
  )
{
  UINT64  PhyAddr = 0;

  //
  // PhyAddr contains the error injection Address
  //
  PhyAddr = mEinjParam->EinjAddr;

  //
  // Write data to memory to seed error in memory
  //
  if (PhyAddr != 0) {
    *(UINT32 *) (UINTN) PhyAddr = mInjAddrValue;
    AsmFlushCacheLine ((VOID *) (UINTN) PhyAddr);
    //AsmCommitLine ((VOID*)(UINTN)PhyAddr, mInjAddrValue);
    AsmWbinvd ();
  }
}

/**

    Inject Memory Related errors. i.e. Patrol Scrub, Corrected or UC errors.

    @param ErrorToInject - BIT3 - Memory Correctable (ECC correctable)
                                 - BIT4  - Memory UC non-fatal (i.e. Patrol Scrub)
                                 - BIT5 - Memory UC Fatal - (ECC uncorrectable error)
                                 - BIT12 - Memory uncorrectable error (Core consumption IFU/DCU errors, software is expected to consume the line to trigger errors)

    @retval None

**/
VOID
EFIAPI
InjectMemoryError (
  UINT32   ErrorToInject
  )
{
  UINT64        PhyAddr;
  UINT64        AddrMask;
  UINT32        Data;
  UINT64        Data64;
  UINT64        MchBar;

  PhyAddr = mEinjParam->EinjAddr;
  AddrMask = mEinjParam->AddrMask;

  MchBar = PcdGet64 (PcdMchBaseAddress);
  DEBUG((DEBUG_INFO, " InjectMemoryError - MchBar = 0x%lx\n", (UINT64) MchBar));

  Data = MmioRead32 (MchBar + MMIO_IBECC0 + IBECC_ACTIVATE);
  DEBUG((DEBUG_INFO, " InjectMemoryError - IBECC_ACTIVATE  = 0x%x\n", Data));

  //
  // Invalidate the line in memory
  //
  mInjAddrValue = *(volatile UINT32 *) (UINTN) (PhyAddr);
  *(volatile  UINT32 *) (UINTN) (PhyAddr) = 0x12345678;
  AsmFlushCacheLine ((VOID*) (UINTN) PhyAddr);

  if (mErrorExpected == WHEA_MEM_COR_ERROR) {
      mEinjAction->Trigger0.InjectionAction                  = WHEA_EINJ_TRIGGER_ERROR_ACTION;
      mEinjAction->Trigger0.Instruction                      = EFI_ACPI_6_0_EINJ_WRITE_REGISTER_VALUE;
      mEinjAction->Trigger0.Flags                            = 0;
      mEinjAction->Trigger0.Reserved0                        = 00;
      mEinjAction->Trigger0.RegisterRegion.AddressSpaceId    = EFI_ACPI_3_0_SYSTEM_MEMORY;
      mEinjAction->Trigger0.RegisterRegion.RegisterBitWidth  = 0x20;
      mEinjAction->Trigger0.RegisterRegion.RegisterBitOffset = 0x00;
      mEinjAction->Trigger0.RegisterRegion.AccessSize        = EFI_ACPI_3_0_DWORD;
      mEinjAction->Trigger0.RegisterRegion.Address           = PhyAddr;
      mEinjAction->Trigger0.Value                            = mInjAddrValue;
      mEinjAction->Trigger0.Mask                             = 0xffffffffffffffff;
  }

  //
  // Setup Error Injection registers
  //
  // clear ECC_ERROR_LOG
  Data64 = MmioRead64 (MchBar + MMIO_IBECC0 + ECC_ERROR_LOG);
  MmioWrite64 (MchBar + MMIO_IBECC0 + ECC_ERROR_LOG, Data64);

  // clear ECC_INJ_CONTROL
  Data = 0;
  MmioWrite32 (MchBar + MMIO_IBECC0 + ECC_INJ_CONTROL, Data);

  DEBUG((DEBUG_INFO, " InjectMemoryError - PhyAddr  = 0x%lx\n", (UINT64) PhyAddr));
  MmioWrite64 (MchBar + MMIO_IBECC0 + ECC_INJ_ADDR_BASE, (UINT64) PhyAddr);
  Data64 = MmioRead64 (MchBar + MMIO_IBECC0 + ECC_INJ_ADDR_BASE);
  DEBUG((DEBUG_INFO, " InjectMemoryError - ECC_INJ_ADDR_BASE = 0x%lx\n", Data64));

  DEBUG((DEBUG_INFO, " InjectMemoryError - AddrMask = 0x%lx\n", (UINT64) AddrMask));
  MmioWrite64 (MchBar + MMIO_IBECC0 + ECC_INJ_ADDR_MASK, (UINT64) AddrMask);
  Data64 = MmioRead64 (MchBar + MMIO_IBECC0 + ECC_INJ_ADDR_MASK);
  DEBUG((DEBUG_INFO, " InjectMemoryError - ECC_INJ_ADDR_MASK = 0x%lx\n", Data64));

  if (ErrorToInject == EFI_ACPI_6_0_EINJ_ERROR_MEMORY_CORRECTABLE) {
    //Data = MmioRead32 (MchBar + MMIO_IBECC0 + ECC_INJ_CONTROL);
    //Data &= 0xFFFFFFF8;
    //Data |= 0x1; // Set bits 2:0, 001b: Inject a correctable ECC error on the ECC_INJ_ADDR_COMPARE register match
    Data = 0x1;
    MmioWrite32 (MchBar + MMIO_IBECC0 + ECC_INJ_CONTROL, Data);
    Data = MmioRead32 (MchBar + MMIO_IBECC0 + ECC_INJ_CONTROL);
    DEBUG((DEBUG_INFO, " InjectMemoryError - CE : ECC_INJ_CONTROL = 0x%x\n", Data));
  }

  if (ErrorToInject == EFI_ACPI_6_0_EINJ_ERROR_MEMORY_UNCORRECTABLE_FATAL) {
    //Data = MmioRead32 (MchBar + MMIO_IBECC0 + ECC_INJ_CONTROL);
    //Data &= 0xFFFFFFF8;
    //Data |= 0x5; // Set bits 2:0, 101b: Inject a non-recoverable ECC error on the ECC_INJ_ADDR_COMPARE register match
    Data = 0x5;
    MmioWrite32 (MchBar + MMIO_IBECC0 + ECC_INJ_CONTROL, Data);
    Data = MmioRead32 (MchBar + MMIO_IBECC0 + ECC_INJ_CONTROL);
    DEBUG((DEBUG_INFO, " InjectMemoryError - UE : ECC_INJ_CONTROL = 0x%x\n", Data));
  }

  SeeErrorAp ();
  AsmWbinvd ();

  // doing a read back should cause an ECC error
  mInjAddrValue = *(volatile UINT32 *) (UINTN) (PhyAddr);

  Data64 = MmioRead64 (MchBar + MMIO_IBECC0 + ECC_ERROR_LOG);
  DEBUG((DEBUG_INFO, " InjectMemoryError - ECC_ERROR_LOG = 0x%lx\n", Data64));

  // ibecc should then generate a NMI which will be intercepted by Linux EDAC driver.
  // EDAC : Error Detection and Correction Driver.
}