/** @file
  EFI Charging Applet Protocol hardware interface

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include "HardwareInterface.h"
#include "DisplayIcon.h"


EFI_STATUS
EFIAPI
SetCpuVid (
  IN VOID        *Buffer
  )
{
  //
  // TODO: Code to set CPU VID
  //
/*
  MSR_REGISTER  Ia32PerfCtl;
  MSR_REGISTER  IaCoreVids;
  MSR_REGISTER  IaCoreRatios;
  UINT16        MinBusRatio;
  UINT16        MinVid;

  MinBusRatio = 0;
  MinVid      = 0;

  IaCoreRatios.Qword = AsmReadMsr64 (MSR_IACORE_RATIOS);
  MinBusRatio = IaCoreRatios.Bytes.SecondByte;

  IaCoreVids.Qword = AsmReadMsr64 (MSR_IACORE_VIDS);
  MinVid = IaCoreVids.Bytes.SecondByte;

  Ia32PerfCtl.Qword = AsmReadMsr64 (EFI_MSR_IA32_PERF_CTRL);
  Ia32PerfCtl.Qword &= ~P_STATE_TARGET_MASK;
  Ia32PerfCtl.Qword |= LShiftU64 (MinBusRatio, P_STATE_TARGET_OFFSET);
  Ia32PerfCtl.Qword |= MinVid, 0xFF;

  AsmWriteMsr64 (EFI_MSR_IA32_PERF_CTRL, Ia32PerfCtl.Qword);
*/
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
SetCpuInLfm (
  VOID
  )
{
  //
  // TODO: Code to put CPU in LFM
  //
/*
  EFI_STATUS                  Status;
  EFI_MP_SERVICES_PROTOCOL    *MpServices;
  UINTN                       NumberOfProcessors;
  UINTN                       NumberOfEnabledProcessors;
  MSR_REGISTER                Ia32PerfCtl;
  MSR_REGISTER                IaCoreVids;
  MSR_REGISTER                IaCoreRatios;
  UINT16                      MinBusRatio;
  UINT16                      MinVid;

  *MpServices = NULL;
  MinBusRatio = 0;
  MinVid      = 0;

  DEBUG ((EFI_D_INFO, "SetCpuInLfm() Start\n"));

  Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, (VOID **)&MpServices);
  if (!EFI_ERROR (Status)) {
    Status = MpServices->GetNumberOfProcessors (MpServices, &NumberOfProcessors, &NumberOfEnabledProcessors);
    if (!EFI_ERROR (Status) && (NumberOfEnabledProcessors > 2)) {
      Status = MpServices->StartupAllAPs (MpServices, SetCpuVid, TRUE, NULL, 0, NULL, NULL);
    }
  }

  IaCoreRatios.Qword = AsmReadMsr64 (MSR_IACORE_RATIOS);
  MinBusRatio = IaCoreRatios.Bytes.SecondByte;

  IaCoreVids.Qword = AsmReadMsr64 (MSR_IACORE_VIDS);
  MinVid = IaCoreVids.Bytes.SecondByte;

  Ia32PerfCtl.Qword = AsmReadMsr64 (EFI_MSR_IA32_PERF_CTRL);
  Ia32PerfCtl.Qword &= ~P_STATE_TARGET_MASK;
  Ia32PerfCtl.Qword |= LShiftU64 (MinBusRatio, P_STATE_TARGET_OFFSET);
  Ia32PerfCtl.Qword |= MinVid, 0xFF;

  AsmWriteMsr64 (EFI_MSR_IA32_PERF_CTRL, Ia32PerfCtl.Qword);

  DEBUG ((EFI_D_INFO, "SetCpuInLfm() End\n"));
*/
  return EFI_SUCCESS;
}


VOID
EFIAPI
SetFuncDisable (
  VOID
  )
{
  DEBUG ((EFI_D_INFO, "SetFuncDisable() Start\n"));

  //
  // TODO: Code function disable flow for PCH IPs
  //

  DEBUG ((EFI_D_INFO, "SetFuncDisable() End\n"));
  return;
}


VOID
EFIAPI
PutPchIpInD3 (
  VOID
  )
{
  DEBUG ((EFI_D_INFO, "PutPchIpInD3() Start\n"));
  //
  // TODO: Put all the EHL MCC IP D3 programming here.
  //
  DEBUG ((EFI_D_INFO, "PutPchIpInD3() End\n"));
  return;
}


BOOLEAN
EFIAPI
CheckPowerButtonStatus (
  VOID
  )
/*++

Routine Description:

  High-level Interface to obtain the power button status.

Arguments:

Returns:
   TRUE     Power Button Pressed.
   FALSE    Power Button Not Pressed.
--*/
{
  BOOLEAN Status;

  Status = FALSE;

  DEBUG ((EFI_D_INFO, "[CheckPowerButtonStatus] Start\n"));

  if (mInputButtonInterface.CheckPowerButtonStatus != NULL) {
    DEBUG ((EFI_D_INFO, "[CheckPowerButtonStatus] getting status...\n"));
    Status = mInputButtonInterface.CheckPowerButtonStatus();
  }

  DEBUG ((EFI_D_INFO, "[CheckPowerButtonStatus] End\n"));
  return Status;
}


EFI_STATUS
EFIAPI
CheckWakeSource (
  UINT8  *WakeCause
  )
/*++

Routine Description:

  High-level Interface to obtain the wake source.

Arguments:
  [OUT] Source: the source that woke up the device.
        0x00: Unable to determine.
        0x01: Power Button
        0x02: USB insertion
        0x04: A/C adaptor insertion

Returns:
   EFI_SUCCESS  Wake Source successfully determined

--*/
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "[CheckWakeSource] Start\n"));

  //
  // TODO: Get wake source from platform hardware
  //
  *WakeCause = 0;

  DEBUG ((EFI_D_INFO, "[CheckWakeSource] End, Source is 0x%x\n", *WakeCause));

  return Status;
}

BOOLEAN
EFIAPI
CheckForChargerPresence (
  CHARGER_TYPE  *Type
  )
/*++

Routine Description:

  Check For Charger Presence (it can be removed anytime)

Arguments:
   [OUT] Type: Type of Charger (CHARGER_TYPE)
Returns:
   TRUE       Charger Present
   FALSE      Charger Absent
--*/
{
  BOOLEAN   ChrgPresent;

  ChrgPresent = TRUE;

  DEBUG ((EFI_D_INFO, "[CheckForChargerPresence] Start\n"));

  if (mChargerInterface.CheckForChargerPresence != NULL) {
    ChrgPresent = mChargerInterface.CheckForChargerPresence (Type);
  } else {
    DEBUG ((EFI_D_INFO, "[CheckForChargerPresence] charger functions not implemented\n"));
    ChrgPresent = FALSE;
    goto end;
   }

  DEBUG ((EFI_D_INFO, "[CheckForChargerPresence] End, Type =%d  %d\n", *Type, ChrgPresent));

end:
  return ChrgPresent;
}


BOOLEAN
EFIAPI
CheckForBatteryPresence (
  VOID
  )
/*++

Routine Description:

  Check For Battery Presence (it can be removed anytime)

Arguments:

Returns:
   TRUE       Battery PResent
   FALSE      Battery Absent
--*/
{
  BOOLEAN Status;

  Status = TRUE;

  DEBUG ((EFI_D_INFO, "[CheckForBatteryPresence] Start\n"));

  if (mChargerInterface.CheckForBatteryPresence != NULL) {
    Status = mChargerInterface.CheckForBatteryPresence();
  }

  DEBUG ((EFI_D_INFO, "[CheckForBatteryPresence] End\n"));
  return Status;
}


EFI_STATUS
EFIAPI
GetStateOfCharge (
  OUT UINT32          *CurrentCapacity,
  OUT CHARGE_STATE    *CurrentState
  )
/*++

Routine Description:

  High level interface to get the state of charge.

Arguments:

Returns:
   StateOfCharge: in %.

--*/
{
  EFI_STATUS   Status;

  Status = EFI_DEVICE_ERROR;
  DEBUG ((EFI_D_INFO, "[GetStateOfCharge] Start\n"));

  if (mChargerInterface.GetStateOfCharge != NULL) {
    Status = mChargerInterface.GetStateOfCharge (CurrentCapacity, CurrentState);
    DEBUG ((EFI_D_INFO, "[GetStateOfCharge] CurrentCapacity = %d\n", *CurrentCapacity));
    DEBUG ((EFI_D_INFO, "[GetStateOfCharge] CurrentState = %d\n", *CurrentState));
  }

  DEBUG ((EFI_D_INFO, "[GetStateOfCharge] End\n"));

  return Status;
}

EFI_STATUS
EFIAPI
SetRateOfCharge (
  IN UINT32  ChargeRate
  )
/*++

Routine Description:

  High level interface to get the state of charge.

Arguments:
  ChargeRate: charging rate in mA.

Returns:

  Does not return if the reset takes place.
  EFI_UNSUPPORTED   If ResetType is invalid.

--*/
{
  EFI_STATUS Status;

  Status = EFI_UNSUPPORTED;

  DEBUG ((EFI_D_INFO, "[SetChargeRate] Start\n"));

  if (mChargerInterface.SetChargeRate != NULL) {
    Status = mChargerInterface.SetChargeRate (ChargeRate);
    DEBUG ((EFI_D_INFO, "[SetChargeRate] Charge rate Status = %x\n", Status));
  }

  DEBUG ((EFI_D_INFO, "[SetChargeRate] End\n"));
  return Status;
}


EFI_STATUS
EFIAPI
StartCharging (
  VOID
  )
/*++

Routine Description:

  High level interface to start charging.

Arguments:

Returns:
   EFI_SUCCESS Successfully started charging
   EFI_UNSUPPORTED Device does not support

--*/
{
  EFI_STATUS Status;

  Status = EFI_UNSUPPORTED;
  DEBUG ((EFI_D_INFO, "[StartCharging] Start\n"));

  if (mChargerInterface.StartCharging != NULL) {
    Status = mChargerInterface.StartCharging ();
    DEBUG ((EFI_D_INFO, "[StartCharging] Charging Status = %x\n",Status));
  }
  DEBUG ((EFI_D_INFO, "[StartCharging] End\n"));
  return Status;
}


VOID
InitializeHardwareInterfaces (
  CHARGER_ID      Id
  )
/*++

Routine Description:
   Initialize Charger Hardware Interface

Arguments:
   Id  : Charger Id

Returns:

--*/
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "[InitializeHardwareInterfaces] Start, ChargerId = %x\n", Id));

  //
  // Display Interface initialization
  //
  mDisplayInterface.ClockTicks = 0;
  mDisplayInterface.DisplayChargingIndication = DisplayIcon;
  mMaxDisplayClockTicks = (UINTN)(ICON_DISPLAY_TIME_CONFIG / CHARGING_TIMER_INTERVAL);

  //
  // Charger combination initializations
  //
  switch ((CHARGER_ID) Id) {
  case ECLITE:
    mChargerInterface.GetStateOfCharge        = EcLite_GetStateOfCharge;
    mChargerInterface.StartCharging           = EcLite_StartCharging;
    mChargerInterface.CheckForChargerPresence = EcLite_CheckForChargerPresence;
    mChargerInterface.SetChargeRate           = EcLite_SetChargeCurrent;
    mChargerInterface.GetBatteryInfo          = EcLite_GetBatteryInfo;
    break;

  default:
    mChargerInterface.GetStateOfCharge        = Dummy_GetStateOfCharge;
    mChargerInterface.StartCharging           = Dummy_StartCharging;
    mChargerInterface.CheckForChargerPresence = Dummy_CheckForChargerPresence;
    mChargerInterface.SetChargeRate           = Dummy_SetChargeCurrent;
    mChargerInterface.GetBatteryInfo          = Dummy_GetBatteryInfo;
    break;
  }

  //
  // Input Button Initialization
  //
  Status = InitializeInputButtonInterface ();
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_INFO, "[InitializeHardwareInterfaces] Initialize Input button interface failed\n"));
  }

  DEBUG ((EFI_D_INFO, "[InitializeHardwareInterfaces] End\n"));
  return;
}
