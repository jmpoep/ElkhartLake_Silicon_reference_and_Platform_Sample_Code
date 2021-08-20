/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2017 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Protocol/Cpu.h>
#include <BootTime.h>

//-----------------------------------------------------------------------------
// Data & Header Define
//-----------------------------------------------------------------------------
BOOTTIME_TABLE         BoottimeLogs;
EFI_CPU_ARCH_PROTOCOL  *gCpu = NULL;

//-----------------------------------------------------------------------------
// Code
//-----------------------------------------------------------------------------


/**
  Get total boot time in milliseconds format

  @retval    MilliSecond  It returns total boot time in milliseconds format
**/
UINT32
GetTscTime (
  VOID
  )
{
  UINT32     MilliSecond;
  UINT64     TimerPeriod;
  UINT64     CurrentTick;
  UINT32     CpuFreq;

  gCpu->GetTimerValue (gCpu, 0, &CurrentTick, &TimerPeriod);

  DEBUG((DEBUG_ERROR, "<TSC=0x%lx>", CurrentTick));

  CpuFreq = (UINT32)DivU64x64Remainder (1000000000, TimerPeriod, NULL);
  MilliSecond = (UINT32)DivU64x64Remainder (CurrentTick, CpuFreq * 1000, NULL);
  DEBUG((DEBUG_ERROR, "<ms=%d>", MilliSecond)); 

  return MilliSecond;
}


/**
  Log Record

  @param[in] timer_flags
  @param[in] ms
  @param[in] quiet_boot
  @param[in] fast_boot
  @param[in] os_flags
**/
VOID
LogRecord (
  IN UINT32 timer_flags,
  IN UINT32 ms,
  IN BOOLEAN quiet_boot,
  IN BOOLEAN fast_boot,
  IN UINT32 os_flags
  )
{
  BOOTTIME_ENTRY  n, c;
  UINTN           Count;
  UINTN           i;

  Count = sizeof (BoottimeLogs.Buffer) / sizeof (BoottimeLogs.Buffer[0]);
  n.Time = ms;
  n.Flags = timer_flags | os_flags;
  if (quiet_boot)
    n.Flags |= QUIET_BOOT;
  if (fast_boot)
    n.Flags |= FAST_BOOT;

  i = 0;
  do {
    gBS->CopyMem (&c, &BoottimeLogs.Buffer[i], sizeof (c));
    gBS->CopyMem (&BoottimeLogs.Buffer[i], &n, sizeof (n));
    gBS->CopyMem (&n, &c, sizeof (c));
    i++;
  } while (i < Count);

  if (BoottimeLogs.Length < Count)
    BoottimeLogs.Length++;
}


/**
  Save boot time to BootTimeLog variable

  @param[in] OS_Mode
**/
VOID
SaveBootTime (
  IN UINT32  OS_Mode
  )
{
  UINT32          tsc_ms;
  EFI_STATUS      Status;
  UINTN           VariableSize;

  tsc_ms = GetTscTime ();

  VariableSize = sizeof (BOOTTIME_TABLE);
  Status = gRT->GetVariable(
                  L"BootTimeLog",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &BoottimeLogs
                  );
  if (EFI_ERROR(Status)) {
    BoottimeLogs.Length = 0;
  }

  LogRecord (TSC_TIMER, tsc_ms, 0, 0, OS_Mode);

  Status = gRT->SetVariable(
                  L"BootTimeLog",
                  &gSetupVariableGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  VariableSize,
                  &BoottimeLogs
                  );
  ASSERT_EFI_ERROR (Status);

//    UpdateGlobalNVS();
}


/**
  Event for boot time with leagcy boot

  @param[in] Event
  @param[in] ParentImageHandle
**/
VOID
EFIAPI
BootTimeLegacyBootEvent (
  IN EFI_EVENT  Event,
  IN VOID       *ParentImageHandle
  )
{
  gBS->CloseEvent(Event);

  DEBUG ((DEBUG_ERROR, "<BootTimeLegacyBoot>"));
  SaveBootTime (LEGACY_BOOT);
}


/**
  Event for boot time with EFI boot

  @param[in] Event
  @param[in] ParentImageHandle
**/
VOID
EFIAPI
BootTimeEfiBootEvent (
  IN EFI_EVENT  Event,
  IN VOID       *ParentImageHandle
  )
{
  gBS->CloseEvent(Event);

  DEBUG ((DEBUG_ERROR, "<BootTimeEfiBoot>"));
  SaveBootTime (EFI_BOOT);
}


/**
  Entry point for the driver

  @param[in] ImageHandle
  @param[in] SystemTable

  @retval    EFI_SUCCESS
  @retval    Others       The required operation failed.
**/
EFI_STATUS
EFIAPI
BootTimeEntry (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS     Status = EFI_SUCCESS;
  EFI_EVENT      eBootTimeEfiBootEvent;
  EFI_EVENT      LegacyBootEvent;
  UINTN          VariableSize;

  DEBUG ((DEBUG_ERROR, "<BootTimeEntry>"));

  Status = gBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **) &gCpu);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Status = %r", Status));
    return Status;
  }

  if (PcdGetBool(PcdBootTime)) {
    Status = gBS->CreateEvent (
                    EVT_SIGNAL_EXIT_BOOT_SERVICES,
                    TPL_NOTIFY,
                    BootTimeEfiBootEvent,
                    (VOID *) &ImageHandle,
                    &eBootTimeEfiBootEvent
                    );
    ASSERT_EFI_ERROR (Status);

    Status = EfiCreateEventLegacyBootEx (
               TPL_NOTIFY,
               BootTimeLegacyBootEvent,
               (VOID *) &ImageHandle,
               &LegacyBootEvent
               );
    ASSERT_EFI_ERROR (Status);
  } else {
    //
    // "Enable BootTime Log" is disabled, get BootTimeLog Variable, if it is exist, delete it.
    //
    VariableSize = sizeof (BOOTTIME_TABLE);
    Status = gRT->GetVariable (
                    L"BootTimeLog",
                    &gSetupVariableGuid,
                    NULL,
                    &VariableSize,
                    &BoottimeLogs
                    );

    if (!EFI_ERROR (Status)) {
      VariableSize = 0;
      Status = gRT->SetVariable (
                      L"BootTimeLog",
                      &gSetupVariableGuid,
                      EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                      VariableSize,
                      &BoottimeLogs
                      );
      ASSERT_EFI_ERROR (Status);
    }
  }

  return EFI_SUCCESS;
}
