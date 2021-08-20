/** @file
  TCC Library.
  All function in this library is available for PEI, DXE, and SMM
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2020 Intel Corporation.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/PchRegsLpcEhl.h>
#include <Library/IoLib.h>
#include <TccConfigSubRegion.h>
#include <TccTuningHob.h>
#include <Library/PchPcrLib.h>
#include <Library/CpuMailboxLib.h>
#include <Library/TimerLib.h>

VOID
TuneMmio32Register (
  TCC_REGISTER* RtData
  )
{
  UINT32      Temp32;

  DEBUG((EFI_D_INFO, "RtData->TccRegPhase = %X \n", RtData->TccRegPhase));
  DEBUG((EFI_D_INFO, "RtData->TccRegType = %X \n", RtData->TccRegType));
  DEBUG((EFI_D_INFO, "RtData->Info.Mmio32.U32Base = %08X \n", RtData->Info.Mmio32.U32Base));
  DEBUG((EFI_D_INFO, "RtData->Info.Mmio32.U32Addr = %08X \n", RtData->Info.Mmio32.U32Addr));
  DEBUG((EFI_D_INFO, "RtData->Info.Mmio32.U32Mask = %08X \n", RtData->Info.Mmio32.U32Mask));
  DEBUG((EFI_D_INFO, "RtData->Info.Mmio32.U32Data = %08X \n", RtData->Info.Mmio32.U32Data));

  Temp32 = MmioRead32(RtData->Info.Mmio32.U32Base + RtData->Info.Mmio32.U32Addr);
  DEBUG((EFI_D_INFO, "Original reg value          = %08X \n", Temp32));
  Temp32 &= (~RtData->Info.Mmio32.U32Mask);
  Temp32 |= RtData->Info.Mmio32.U32Data;
  DEBUG((EFI_D_INFO, "Data to write               = %08X \n", Temp32));
  MmioWrite32((RtData->Info.Mmio32.U32Base + RtData->Info.Mmio32.U32Addr), Temp32);
  DEBUG_CODE (
    MicroSecondDelay(100);
    Temp32 = MmioRead32(RtData->Info.Mmio32.U32Base + RtData->Info.Mmio32.U32Addr);
    DEBUG((EFI_D_INFO, "Data written                = %08X \n", Temp32));
  );
}

VOID
TuneMmio64Register (
  TCC_REGISTER* RtData
  )
{
  UINT64      Temp64;

  DEBUG((EFI_D_INFO, "RtData->TccRegPhase = %X \n", RtData->TccRegPhase));
  DEBUG((EFI_D_INFO, "RtData->TccRegType = %X \n", RtData->TccRegType));
  DEBUG((EFI_D_INFO, "RtData->Info.Mmio64.Base = %X \n",  RtData->Info.Mmio64.Base.Value));
  DEBUG((EFI_D_INFO, "RtData->Info.Mmio64.Addr = %X \n",  RtData->Info.Mmio64.Addr.Value));
  DEBUG((EFI_D_INFO, "RtData->Info.Mmio64.U64Mask = %X \n", RtData->Info.Mmio64.U64Mask));
  DEBUG((EFI_D_INFO, "RtData->Info.Mmio64.U64Data = %X \n", RtData->Info.Mmio64.U64Data));

  Temp64 = MmioRead64 (RtData->Info.Mmio64.Base.Value + RtData->Info.Mmio64.Addr.Value);
  DEBUG((EFI_D_INFO, "Original reg value          = %016X \n", Temp64));
  Temp64 &= (~RtData->Info.Mmio64.U64Mask);
  Temp64 |= RtData->Info.Mmio64.U64Data;
  DEBUG((EFI_D_INFO, "Data to write               = %016X \n", Temp64));
  MmioWrite64 ((RtData->Info.Mmio64.Base.Value + RtData->Info.Mmio64.Addr.Value), Temp64);
  DEBUG_CODE (
    MicroSecondDelay(100);
    Temp64 = MmioRead64(RtData->Info.Mmio64.Base.Value + RtData->Info.Mmio64.Addr.Value);
    DEBUG((EFI_D_INFO, "Data written                = %016X \n", Temp64));
  );
}


VOID
TuneMsrRegister (
  TCC_REGISTER* RtData
  )
{
  UINT64 Temp64;

  DEBUG((EFI_D_INFO, "RtData->TccRegPhase = %X \n", RtData->TccRegPhase));
  DEBUG((EFI_D_INFO, "RtData->TccRegType = %X \n", RtData->TccRegType));
  DEBUG((EFI_D_INFO, "RtData->Info.Msr.U32Addr = %08X \n", RtData->Info.Msr.U32Addr));
  DEBUG((EFI_D_INFO, "RtData->Info.Msr.U64Mask = %L16X \n", RtData->Info.Msr.U64Mask));
  DEBUG((EFI_D_INFO, "RtData->Info.Msr.U64Data = %L16X \n", RtData->Info.Msr.U64Data));

  Temp64 = AsmReadMsr64(RtData->Info.Msr.U32Addr);
  DEBUG((EFI_D_INFO, "Original MSR value       = %L16X \n", Temp64));
  Temp64 &= (~RtData->Info.Msr.U64Mask);
  Temp64 |= RtData->Info.Msr.U64Data;
  DEBUG((EFI_D_INFO, "Data to write            = %L16X \n", Temp64));
  AsmWriteMsr64 (RtData->Info.Msr.U32Addr, Temp64);
  DEBUG_CODE (
    MicroSecondDelay(100);
    Temp64 = AsmReadMsr64(RtData->Info.Msr.U32Addr);
    DEBUG((EFI_D_INFO, "Data written             = %L16X \n", Temp64));
  );

  return;
}

VOID
TuneIosfSbRegister (
  TCC_REGISTER* RtData
  )
{
  UINT32      Temp32;

  DEBUG((EFI_D_INFO, "RtData->TccRegPhase = %X \n", RtData->TccRegPhase));
  DEBUG((EFI_D_INFO, "RtData->TccRegType = %X \n", RtData->TccRegType));
  DEBUG((EFI_D_INFO, "RtData->Info.IosfSb.Port = %02X \n", RtData->Info.IosfSb.Port));
  DEBUG((EFI_D_INFO, "RtData->Info.IosfSb.IosfSbType = %02X \n", RtData->Info.IosfSb.IosfSbType));
  DEBUG((EFI_D_INFO, "RtData->Info.IosfSb.U32Addr = %08X \n", RtData->Info.IosfSb.U32Addr));
  DEBUG((EFI_D_INFO, "RtData->Info.IosfSb.U32Mask = %08X \n", RtData->Info.IosfSb.U32Mask));
  DEBUG((EFI_D_INFO, "RtData->Info.IosfSb.U32Data = %08X \n", RtData->Info.IosfSb.U32Data));

  Temp32 = PchPcrRead32 (RtData->Info.IosfSb.Port, (UINT16) RtData->Info.IosfSb.U32Addr);
  DEBUG((EFI_D_INFO, "Original IOSFB value        = %08X \n", Temp32));
  Temp32 &= (~RtData->Info.IosfSb.U32Mask);
  Temp32 |= RtData->Info.IosfSb.U32Data;
  DEBUG((EFI_D_INFO, "Data to write               = %08X \n", Temp32));
  PchPcrWrite32 (RtData->Info.IosfSb.Port, (UINT16) RtData->Info.IosfSb.U32Addr, Temp32);
  DEBUG_CODE (
    MicroSecondDelay(100);
    Temp32 = PchPcrRead32 (RtData->Info.IosfSb.Port, (UINT16) RtData->Info.IosfSb.U32Addr);
    DEBUG((EFI_D_INFO, "Data written                = %08X \n", Temp32));
  );
}

VOID
TuneMailboxRegister (
  TCC_REGISTER* RtData
  )
{
  UINT32        Temp32;
  EFI_STATUS    Status;
  UINT32                                MailboxStatus;

  DEBUG((EFI_D_INFO, "RtData->TccRegPhase = %X \n", RtData->TccRegPhase));
  DEBUG((EFI_D_INFO, "RtData->TccRegType = %X \n", RtData->TccRegType));
  DEBUG((EFI_D_INFO, "RtData->Info.Mailbox.MailboxType = %02X \n", RtData->Info.Mailbox.MailboxType));
  DEBUG((EFI_D_INFO, "RtData->Info.Mailbox.U32Cmd = %08X \n", RtData->Info.Mailbox.U32Cmd));
  DEBUG((EFI_D_INFO, "RtData->Info.Mailbox.U32Mask = %08X \n", RtData->Info.Mailbox.U32Mask));
  DEBUG((EFI_D_INFO, "RtData->Info.Mailbox.U32Data = %08X \n", RtData->Info.Mailbox.U32Data));

  Status = MailboxRead (RtData->Info.Mailbox.MailboxType, (RtData->Info.Mailbox.U32Cmd - 1), &Temp32, &MailboxStatus);
  DEBUG((EFI_D_INFO, "MAILBOX Status = %08X \n", MailboxStatus));
  DEBUG((EFI_D_INFO, "Original MAILBOX value = %08X \n", Temp32));
  Temp32 &= (~RtData->Info.Mailbox.U32Mask);
  Temp32 |= RtData->Info.Mailbox.U32Data;
  DEBUG((EFI_D_INFO, "Data to write = %08X \n", Temp32));
  Status = MailboxWrite(RtData->Info.Mailbox.MailboxType, RtData->Info.Mailbox.U32Cmd, Temp32, &MailboxStatus);
  DEBUG_CODE (
    MicroSecondDelay(100);
    DEBUG((EFI_D_INFO, "MailboxStatus = %08X \n", MailboxStatus));
    Status = MailboxRead(RtData->Info.Mailbox.MailboxType, (RtData->Info.Mailbox.U32Cmd - 1), &Temp32, &MailboxStatus);
    DEBUG((EFI_D_INFO, "MailboxStatus = %08X \n", MailboxStatus));
    DEBUG((EFI_D_INFO, "Data written = %08X \n", Temp32));
  );
}

VOID
DumpTccBuffer (
  VOID *RtFileBuffer
  )
{

  TCC_CONFIG_SUB_REGION                 *RtSubRegion;
  TCC_BIOS_POLICY_CONFIG                *BiosConfig;
  TCC_IO_CONFIG                         *TccIoConfig;
  TCC_REG_CONFIG                        *TccRegConfig;

  RtSubRegion = (TCC_CONFIG_SUB_REGION *) RtFileBuffer;
  BiosConfig = (TCC_BIOS_POLICY_CONFIG *) &RtSubRegion->Config.BiosConfig;
  TccIoConfig = (TCC_IO_CONFIG *) &RtSubRegion->Config.TccIoConfig;
  TccRegConfig = (TCC_REG_CONFIG *) &RtSubRegion->Config.TccRegConfig;

  DEBUG ((DEBUG_INFO, "Dump TCC Buffer\n"));

  DEBUG ((DEBUG_INFO, "Bios Config\n"));
  DEBUG ((DEBUG_INFO, "Format Version %x\n", BiosConfig->FormatVersion));

  DEBUG ((DEBUG_INFO, "TCC stream buffer Config\n"));
  DEBUG ((DEBUG_INFO, "Format Version %x\n", TccIoConfig->FormatVersion));

  DEBUG ((DEBUG_INFO, "TCC Register Config\n"));
  DEBUG ((DEBUG_INFO, "Format Version %x\n", TccRegConfig->FormatVersion));
}

/**
  Reads the Real-Time register file and updates registers accordingly

**/
EFI_STATUS
TccTuning (
  UINT8   Phase,
  VOID   *RtFileBuffer,
  UINT32  FileSize
  )
{
  EFI_STATUS                            Status;
  TCC_CONFIG_SUB_REGION                 *RtSubRegion;
  TCC_REGISTER                          *RtData;
  UINT32                                Index;

  RtSubRegion = (TCC_CONFIG_SUB_REGION *) RtFileBuffer;
  RtData = (TCC_REGISTER *) RtSubRegion->Config.TccRegConfig.TccRegisters;
  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "Executing TCC Sequencing.\n"));
  DEBUG ((EFI_D_INFO, "File Size %x, Size of PTCT %x.\n", FileSize, sizeof(TCC_CONFIG_SUB_REGION)));

  if (FileSize < sizeof(TCC_CONFIG_SUB_REGION)) {
    Status = EFI_BUFFER_TOO_SMALL;
    return Status;
  }

  for (Index = 0; Index < TCC_REGISTERS_MAX; Index++) {
    if (RtData->TccRegPhase == Phase) {
      if (RtData->TccRegType == MMIO32) {
        TuneMmio32Register (RtData);
      } else if (RtData->TccRegType == MMIO64) {
        TuneMmio64Register (RtData);
      } else if (RtData->TccRegType == MSR) {
        TuneMsrRegister (RtData);
      } else if (RtData->TccRegType == IOSFSB) {
        TuneIosfSbRegister (RtData);
      } else if (RtData->TccRegType == MAILBOX) {
        TuneMailboxRegister (RtData);
      } else if (RtData->TccRegType == TCC_REG_INVALID){
        DEBUG((EFI_D_INFO, "Reached end of RT data\n"));
        break;
      } else {
        DEBUG((EFI_D_INFO, "data corrupted \n"));
        break;
      }
    }
    RtData++;
  }
  DEBUG((EFI_D_INFO, "Done\n"));

  return Status;
}