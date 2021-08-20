/** @file
  Time Coordinated Compute register tuning

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 - 2020 Intel Corporation.

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
#include <PiDxe.h>
#include <Uefi/UefiBaseType.h>
#include <Ppi/SiPolicy.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/PchPcrLib.h>
#include <Library/CpuMailboxLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiBootManagerLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TimerLib.h>
#include <Library/HobLib.h>
#include <Library/TccLib.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/PciIo.h>
#include <Protocol/MpService.h>
#include <TccConfigSubRegion.h>
#include <TccTuningHob.h>
#include "TccTuningDxe.h"

EFI_GUID gEfiBdpTypeSystemPartGuid =  { 0xebd0a0a3, 0xb9e5, 0x4433, { 0x87, 0xc0, 0x68, 0xb6, 0xb7, 0x26, 0x99, 0xc7 }};

UINT32 mRtMsrAddr;
UINT64 mRtMsrValue;

VOID
EFIAPI
ApSetRtMsr (
  IN VOID *Buffer
  )
{
  UINT64  RtMsr;
  UINT32  Addr;

  Addr = mRtMsrAddr;
  RtMsr = mRtMsrValue;

  AsmWriteMsr64 (Addr, RtMsr);

  return;
}

/**
  Reads the Real-Time register file and updates registers accordingly

**/
EFI_STATUS
RtTuningDxe (
  UINT8  Phase,
  VOID   *RtFileBuffer,
  UINTN  FileSize
  )
{
  EFI_STATUS                            Status;
  TCC_CONFIG_SUB_REGION                 *RtSubRegion;
  TCC_REGISTER                          *RtData;
  UINT32                                Index;
  UINT64                                Temp64;
  EFI_STATUS                            MpStatus;
  EFI_MP_SERVICES_PROTOCOL              *MpService;

  RtSubRegion = (TCC_CONFIG_SUB_REGION *) RtFileBuffer;
  RtData = (TCC_REGISTER *) RtSubRegion->Config.TccRegConfig.TccRegisters;
  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "Executing TCC sequencing.\n"));
  for (Index = 0; Index < TCC_REGISTERS_MAX; Index++) {
    if (RtData->TccRegPhase == Phase) {
      if (RtData->TccRegType == MMIO32) {
        TuneMmio32Register (RtData);
      } else if (RtData->TccRegType == MMIO64) {
        TuneMmio64Register (RtData);
      } else if (RtData->TccRegType == MSR) {
        TuneMsrRegister (RtData);

        Temp64 = AsmReadMsr64(RtData->Info.Msr.U32Addr);
        Temp64 &= (~RtData->Info.Msr.U64Mask);
        Temp64 |= RtData->Info.Msr.U64Data;

        mRtMsrAddr = RtData->Info.Msr.U32Addr;
        mRtMsrValue = Temp64;

        mRtMsrAddr = RtData->Info.Msr.U32Addr;
        mRtMsrValue = Temp64;

        MpStatus = gBS->LocateProtocol (
                          &gEfiMpServiceProtocolGuid,
                          NULL,
                          (VOID **)&MpService
                          );

        if (!EFI_ERROR (MpStatus)) {
          MpStatus = MpService->StartupAllAPs (
                                    MpService,          // This
                                    ApSetRtMsr,         // Procedure
                                    TRUE,               // SingleThread
                                    NULL,               // WaitEvent
                                    0,                  // TimeoutInMicrosecsond
                                    NULL,               // ProcedureArgument
                                    NULL                // FailedCpuList
                                    );
          ASSERT (MpStatus == EFI_SUCCESS || MpStatus == EFI_NOT_STARTED);
        }
      } else if (RtData->TccRegType == IOSFSB) {
        TuneIosfSbRegister (RtData);
      } else if (RtData->TccRegType == MAILBOX) {
        TuneMailboxRegister (RtData);
      } else if (RtData->TccRegType == TCC_REG_INVALID){
        DEBUG((EFI_D_INFO, "Invalid register\n"));
      } else {
        DEBUG((EFI_D_INFO, "Found invalid register type. Exiting TCC sequencing\n"));
        break;
      }
    }
    RtData++;
  }

  DEBUG((EFI_D_INFO, "TCC sequencing complete\n"));

  return Status;
}

/**
  PCI enumeration complete event handler to configure real time registers

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context.
**/
VOID
EFIAPI
TccTuningOnPciEnumerationComplete (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS            Status;
  VOID                  *Interface;
  TCC_TUNING_HOB        *TccHob;

  Status = gBS->LocateProtocol (
                  &gEfiPciEnumerationCompleteProtocolGuid,
                  NULL,
                  &Interface
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  TccHob = (TCC_TUNING_HOB *) GetFirstGuidHob(&gTccHobGuid);

  if (TccHob != NULL) {
    Status = RtTuningDxe (TCC_LATE_INIT_PHASE, (VOID *) TccHob->TuningDataBaseAddress, TccHob->TuningDataSize);
  } else {
    DEBUG ((DEBUG_INFO, "TCC HOB not found.\n"));
  }

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to set TCC configuration\n"));
  }

  gBS->CloseEvent (Event);
}

/**
  Constructor for the Real Time Tuning Lib

  @param  ImageHandle  ImageHandle of the loaded driver.
  @param  SystemTable  Pointer to the EFI System Table.

  @retval  EFI_SUCCESS            Register successfully.
  @retval  EFI_OUT_OF_RESOURCES   No enough memory to register this handler.
**/
EFI_STATUS
EFIAPI
TccTuningDxeEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  VOID          *Registration;
  EFI_EVENT     ProtocolNotifyEvent;

  DEBUG ((DEBUG_INFO, "TccTuningDxeEntry\n"));

  ProtocolNotifyEvent = EfiCreateProtocolNotifyEvent (
    &gEfiPciEnumerationCompleteProtocolGuid,
    TPL_CALLBACK,
    TccTuningOnPciEnumerationComplete,
    NULL,
    &Registration
    );
  ASSERT (ProtocolNotifyEvent != NULL);

  DEBUG ((DEBUG_INFO, "TccTuningDxeEntry End\n"));

  return EFI_SUCCESS;
}