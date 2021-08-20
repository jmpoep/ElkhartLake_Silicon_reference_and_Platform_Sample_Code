/** @file
  Fast Boot platform setup driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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

@par Specification
**/

#include "FastBootSetupDxe.h"

GLOBAL_REMOVE_IF_UNREFERENCED SETUP_DATA           mSetupData;

/**
  Exit Boot Services Event notification handler.
  Clear boot progress bit at ExitBootServices or LegacyBoot Event.

  @param[in] Event     Event whose notification function is being invoked
  @param[in] Context   Pointer to the notification function's context

**/
VOID
EFIAPI
OnBootEvent (
  IN      EFI_EVENT                 Event,
  IN      VOID                      *Context
  )
{
  UINT8                         BootStatus;
  EFI_STATUS                    Status;
  EFI_TCG_PROTOCOL              *TcgProtocol;
  TCG_SETUP                     TcgSetup;
  UINTN                         DataSize;
  EFI_BOOT_MODE                 BootMode;
  FAST_BOOT_EXCEPTION_PROTOCOL  *FastBootExceptionProtocol;
  BOOLEAN                       ExceptionOccurred;
  BOOLEAN                       IsTcgSupported;
  VOID                          *HobList;
  EFI_HANDLE                    *Handle;
  UINTN                         Number;
  UINTN                         Index;

  //
  // Locate all handles of Fast Boot Exception protocol to find out if any exception has occurred.
  //
  ExceptionOccurred = FALSE;
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gFastBootExceptionProtocolGuid,
                  NULL,
                  &Number,
                  &Handle
                  );
  if (!EFI_ERROR (Status)) {
    for (Index = 0; Index < Number; Index++) {
      Status = gBS->HandleProtocol (
                      Handle[Index],
                      &gFastBootExceptionProtocolGuid,
                      (VOID **) &FastBootExceptionProtocol
                      );
      if (EFI_ERROR (Status)) {
        continue;
      }
      if (FastBootExceptionProtocol->FbExceptionType > NoException) {
        ExceptionOccurred = TRUE;
        break;
      }
    }
  }

  Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &HobList);
  if ((EFI_ERROR (Status)) || (HobList == NULL)) {
    return;
  }
  BootMode = ((EFI_HOB_HANDOFF_INFO_TABLE*)HobList)->BootMode;

  //
  // Clear Boot Progress bit [bit0] at OS handoff to indicate BIOS boot has successfully finished.
  // Include Boot Mode [bits 7:2] and ExceptionOccured [bit1] flag
  //
  BootStatus = 0;
  if (ExceptionOccurred) {
    BootStatus |= BIT1;
  }

  BootStatus |= (BootMode << 2);
  UpdateBootFlagStatus (BootStatus);

  //
  // TPM Exception handling
  //
  IsTcgSupported = FALSE;
  Status = gBS->LocateProtocol (&gEfiTcgProtocolGuid, NULL, (VOID **) &TcgProtocol);
  if (!EFI_ERROR (Status)) {
    IsTcgSupported = TRUE;
  }

  DataSize = sizeof (TCG_SETUP);
  Status = gRT->GetVariable (
                  TCG_SETUP_NAME,
                  &gSetupVariableGuid,
                  NULL,
                  &DataSize,
                  &TcgSetup
                  );

  if ((EFI_ERROR (Status)) || ((!IsTcgSupported) || (TcgSetup.TpmCurrentState != 2))) {
    return;
  }

  if ((ExceptionOccurred) ||
      ((BootMode != BOOT_WITH_MINIMAL_CONFIGURATION) && (BootMode != BOOT_ON_S4_RESUME))
    ) {
    gRT->ResetSystem (EfiResetWarm, EFI_SUCCESS, 0, NULL);
  }

  return;
}


/**
  Enable Tco timer

  @param[in] CpuIo

**/
VOID
EnableTcoTimer (
  IN EFI_CPU_IO2_PROTOCOL       *CpuIo
  )
{
  UINT16    Data16;
  UINT8     Data8;

  //
  // Halt TCO Timer
  //
  CpuIo->Io.Read (
              CpuIo,
              EfiCpuIoWidthUint16,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO1_CNT,
              1,
              &Data16
              );
  Data16 |= B_TCO_IO_TCO1_CNT_TMR_HLT;
  CpuIo->Io.Write (
              CpuIo,
              EfiCpuIoWidthUint16,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO1_CNT,
              1,
              &Data16
              );

  //
  // Clear the Second TCO Timeout status bit
  //
  Data8 = (B_TCO_IO_TCO2_STS_SECOND_TO | B_TCO_IO_TCO2_STS_BOOT);
  CpuIo->Io.Write (
              CpuIo,
              EfiCpuIoWidthUint8,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO2_STS,
              1,
              &Data8
              );
  //
  // Initialize TCO Timer count
  //
  Data16 = FAST_BOOT_WDT_30_SECONDS_COUNT;
  CpuIo->Io.Write (
              CpuIo,
              EfiCpuIoWidthUint16,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TMR,
              1,
              &Data16
              );
  //
  // Reload TCO Timer by writing any value to TCO_RLD register (TCO Timer Reload and Current Value Register)
  //
  Data8 = 0;
  CpuIo->Io.Write (
              CpuIo,
              EfiCpuIoWidthUint8,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_RLD,
              1,
              &Data8
              );

  //
  // Set Fast Boot flag
  //
  Data8 = FAST_BOOT_WDT_RESET_SIGNATURE;
  CpuIo->Io.Write (
              CpuIo,
              EfiCpuIoWidthUint8,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TWDS,
              1,
              &Data8
              );

  //
  // Start/Enable TCO Timer
  // AND 0x08[11]
  // Enable reseting system upon the second timeout of the TCO timer
  // AND 0x08[0]
  //
  CpuIo->Io.Read (
              CpuIo,
              EfiCpuIoWidthUint16,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO1_CNT,
              1,
              &Data16
              );
  Data16 &= ~(B_TCO_IO_TCO1_CNT_TMR_HLT | B_TCO_IO_TCO1_CNT_NR_MSUS);
  CpuIo->Io.Write (
              CpuIo,
              EfiCpuIoWidthUint16,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO1_CNT,
              1,
              &Data16
              );

  return;
}


/**
  Disable Tco timer

  @param[in] CpuIo

**/
VOID
DisableTcoTimer (
  IN EFI_CPU_IO2_PROTOCOL       *CpuIo
  )
{
  UINT16    Data16;
  UINT8     Data8;

  //
  // Halt TCO Timer
  // Disable reseting system upon the second timeout of the TCO timer.
  //
  CpuIo->Io.Read (
              CpuIo,
              EfiCpuIoWidthUint16,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO1_CNT,
              1,
              &Data16
              );
  Data16 |= (B_TCO_IO_TCO1_CNT_TMR_HLT | B_TCO_IO_TCO1_CNT_NR_MSUS);
  CpuIo->Io.Write (
              CpuIo,
              EfiCpuIoWidthUint16,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO1_CNT,
              1,
              &Data16
              );

  //
  // Clear the Second TCO Timeout status bit
  //
  Data8 = (B_TCO_IO_TCO2_STS_SECOND_TO | B_TCO_IO_TCO2_STS_BOOT);
  CpuIo->Io.Write (
              CpuIo,
              EfiCpuIoWidthUint8,
              PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO2_STS,
              1,
              &Data8
              );

  //
  // Clear Fast Boot flag
  //
  Data8 = 0;
  CpuIo->Io.Write (
            CpuIo,
            EfiCpuIoWidthUint8,
            PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TWDS,
            1,
            &Data8
            );

  return;
}


/**
  Register callbacks to disable WDT

  @param[in] NotifyFunction

  @retval    EFI_SUCCESS
  @retval    others
**/
EFI_STATUS
RegisterCallbacksToDisableWdt (
  EFI_EVENT_NOTIFY   NotifyFunction
  )
{
  EFI_STATUS      Status;
  EFI_EVENT       SetupEnteringEvent;
  EFI_EVENT       ReadyToBootEvent;
  EFI_EVENT       ExitBootServiceEvent;
  VOID            *Registration;

  Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    NotifyFunction,
                    NULL,
                    &SetupEnteringEvent);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  Status = gBS->RegisterProtocolNotify (
                    &gSetupEnterGuid,
                    SetupEnteringEvent,
                    &Registration);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  NotifyFunction,
                  NULL,
                  &gEfiEventReadyToBootGuid,
                  &ReadyToBootEvent
                  );
  if (EFI_ERROR(Status)) {
    gBS->CloseEvent (SetupEnteringEvent);
    return Status;
  }

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  NotifyFunction,
                  NULL,
                  &gEfiEventExitBootServicesGuid,
                  &ExitBootServiceEvent
                  );
  if (EFI_ERROR(Status)) {
    gBS->CloseEvent (SetupEnteringEvent);
    gBS->CloseEvent (ReadyToBootEvent);
    return Status;
  }

  return EFI_SUCCESS;
}


/**
  Callback for Fast Boot Disable

  @param[in] Event
  @param[in] Context
  **/
VOID
EFIAPI
FastBootDisableWdtCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS              Status;
  EFI_CPU_IO2_PROTOCOL    *CpuIo;

  Status = gBS->LocateProtocol(
                  &gEfiCpuIo2ProtocolGuid,
                  NULL,
                  (VOID **) &CpuIo);
  if (!EFI_ERROR (Status)) {
    DisableTcoTimer (CpuIo);
  }

  gBS->CloseEvent (Event);
}


/**
  Callback for Fast Boot Enable

  @param[in] Event
  @param[in] Context
  **/
VOID
EFIAPI
FastBootEnableWdtCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS              Status;
  EFI_CPU_IO2_PROTOCOL    *CpuIo;

  Status = gBS->LocateProtocol (
                  &gEfiCpuIo2ProtocolGuid,
                  NULL,
                  (VOID **) &CpuIo);
  if (!EFI_ERROR (Status)) {
    Status = RegisterCallbacksToDisableWdt (FastBootDisableWdtCallback);
    if (!EFI_ERROR (Status)) {
      EnableTcoTimer (CpuIo);
    }
  }

  gBS->CloseEvent (Event);
}

/**
  Entry point for the driver

  @param[in] ImageHandle         Image Handle.
  @param[in] SystemTable         EFI System Table.

  @retval    EFI_SUCCESS         Function has completed successfully.
  @retval    others              All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
EFIAPI
FastBootSetupInit (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                    Status;
  BOOLEAN                       IsFastBootEnabled;
  VOID                          *HobStart;
  EFI_PEI_HOB_POINTERS          Hob;
  FAST_BOOT_EXCEPTION_INFO_HOB  *FastBootExceptionInfoHob;
  FAST_BOOT_EXCEPTION_PROTOCOL  *FastBootExceptionProtocol;
  EFI_HANDLE                    Handle;
  EFI_CPU_IO2_PROTOCOL          *CpuIo;
  EFI_EVENT                     FastBootPlatformSetupEvent;
  VOID                          *Registration;
  EFI_EVENT                     OsHandoffEvent;
  UINTN                         VariableSize;

  Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &HobStart);
  ASSERT_EFI_ERROR (Status);

  IsFastBootEnabled = FALSE;
  for (Hob.Raw = HobStart; !END_OF_HOB_LIST(Hob); Hob.Raw = GET_NEXT_HOB(Hob)) {
    if ((GET_HOB_TYPE (Hob) == EFI_HOB_TYPE_GUID_EXTENSION) && (CompareGuid(&Hob.Guid->Name, &gFastBootFunctionEnabledHobGuid))) {
      IsFastBootEnabled = TRUE;
      break;
    }
  }

  if (IsFastBootEnabled) {
    //
    // Collecting all Fast Boot Exception HOB and instll Fast Boot Exception protocol(s) for them.
    //
    for (Hob.Raw = HobStart; !END_OF_HOB_LIST(Hob); Hob.Raw = GET_NEXT_HOB(Hob)) {
      if ((GET_HOB_TYPE (Hob) == EFI_HOB_TYPE_GUID_EXTENSION) && (CompareGuid(&Hob.Guid->Name, &gFastBootExceptionInfoHobGuid))) {
        FastBootExceptionInfoHob = (FAST_BOOT_EXCEPTION_INFO_HOB *) Hob.Guid;
        Status = gBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof (FAST_BOOT_EXCEPTION_PROTOCOL),
                        (VOID **) &FastBootExceptionProtocol
                        );
        if (EFI_ERROR(Status)) {
          break;
        }
        //
        // Get Fast Boot Exception Information from the HOB data, fill up the protocol
        //
        FastBootExceptionProtocol->FbExceptionType = FastBootExceptionInfoHob->FbExceptionType;
        FastBootExceptionProtocol->FbExceptionCategory = FastBootExceptionInfoHob->FbExceptionCategory;

        //
        // Install the Fast Boot Exception Protocol.
        //
        Handle = NULL;
        Status = gBS->InstallProtocolInterface (
                        &Handle,
                        &gFastBootExceptionProtocolGuid,
                        EFI_NATIVE_INTERFACE,
                        FastBootExceptionProtocol
                        );
      }
    }

    VariableSize = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (
                    L"Setup",
                    &gSetupVariableGuid,
                    NULL,
                    &VariableSize,
                    &mSetupData
                    );

    if (!EFI_ERROR (Status) && (mSetupData.FastBootWdt != 0)) {
      //
      // Intialize TCO Timer with timeout of 30 seconds as a WDT at early DXE. If expires before ExitBootService(),
      // it will reset the platform. After reset, log the event and BIOS will automatically fallback to full-boot.
      //
      Status = gBS->LocateProtocol (
                      &gEfiCpuIo2ProtocolGuid,
                      NULL,
                      (VOID**)&CpuIo
                      );
      if (EFI_ERROR (Status)) {
        Status = gBS->CreateEvent (
                        EVT_NOTIFY_SIGNAL,
                        TPL_CALLBACK,
                        FastBootEnableWdtCallback,
                        NULL,
                        &FastBootPlatformSetupEvent
                        );
        if (!EFI_ERROR (Status)) {
          Status = gBS->RegisterProtocolNotify (
                          &gEfiCpuIo2ProtocolGuid,
                          FastBootPlatformSetupEvent,
                          &Registration
                          );
        }
      } else {
        Status = RegisterCallbacksToDisableWdt (FastBootDisableWdtCallback);
        if (!EFI_ERROR (Status)) {
          EnableTcoTimer (CpuIo);
        }
      }
    }

    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    OnBootEvent,
                    NULL,
                    &gEfiEventExitBootServicesGuid,
                    &OsHandoffEvent
                    );
    Status = EfiCreateEventLegacyBootEx (
               TPL_CALLBACK,
               OnBootEvent,
               NULL,
               &OsHandoffEvent
               );
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}
