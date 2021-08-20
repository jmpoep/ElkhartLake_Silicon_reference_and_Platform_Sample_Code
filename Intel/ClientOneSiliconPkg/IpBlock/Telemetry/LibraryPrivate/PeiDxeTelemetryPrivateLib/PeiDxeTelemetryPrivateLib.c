/** @file

  Telemetry Private Library

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

#include <Uefi.h>
#include <Base.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Register/TelemetryRegs.h>
#include <Register/SaRegsHostBridge.h>
#include <Library/TelemetryLib.h>
#include <Library/TelemetryPrivateLib.h>
#include <Library/CpuPlatformLib.h>
#include <SaCommonDefinitions.h>
#include <CpuRegs.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <IndustryStandard/Pci30.h>

/**
  Poll the run/busy bit of the mailbox until available or timeout expires.

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_DEVICE_ERROR        Mailbox command failed with an error
  @retval EFI_TIMEOUT             Mailbox command did not complete
**/
EFI_STATUS
CpuCrashLogPollMailboxReady (
  IN UINT32                  CrashLogMailboxAddress
  )
{
  CPU_CRASHLOG_MAILBOX       CrashLogMailboxInterface;
  UINT16                     StallCount;

  StallCount = 0;

  do {
    CrashLogMailboxInterface.InterfaceData = MmioRead32 (CrashLogMailboxAddress);

    MicroSecondDelay (CPU_CRASHLOG_MAILBOX_WAIT_STALL);
    StallCount++;
  } while ((CrashLogMailboxInterface.Fields.Busy == 1) && (StallCount < CPU_CRASHLOG_MAILBOX_WAIT_TIMEOUT));

  if ((CrashLogMailboxInterface.Fields.Busy == 1) && (StallCount >= CPU_CRASHLOG_MAILBOX_WAIT_TIMEOUT)) {
    DEBUG ((DEBUG_ERROR, "CPU CrashLog Mailbox timed out.\n"));
    return EFI_TIMEOUT;
  }
  return EFI_SUCCESS;
}

/**
  Send CPU CrashLog Mailbox command

  @param[in]  Command             Command request for CrashLog management.
  @param[in]  Param               Parameter associated with the requested command.

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_DEVICE_ERROR        Mailbox command failed with an error
  @retval EFI_TIMEOUT             Mailbox command did not complete
**/
EFI_STATUS
CpuCrashLogMailboxCommand (
  IN  UINT8                Command,
  IN  UINT8                Param
  )
{
  EFI_STATUS               Status;
  CPU_CRASHLOG_MAILBOX     CrashLogMailboxInterface;
  UINT32                   CrashLogBaseAddress;
  TEL_CRASHLOG_DEVSC_CAP   CrashLogDevscCap;

  Status = EFI_SUCCESS;
  DEBUG ((DEBUG_INFO, "CpuCrashLogMailboxCommand(): COMMAND=0x%02X, PARAM=0x%02X\n", Command, Param));

  ZeroMem (&CrashLogDevscCap, sizeof (TEL_CRASHLOG_DEVSC_CAP));
  Status = GetCpuCrashLogCapability (&CrashLogDevscCap);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "CPU CrashLog feature is not supported\n"));
    return Status;
  }
  CrashLogBaseAddress = GetCpuCrashLogBarAddress (CrashLogDevscCap);
  CrashLogMailboxInterface.Fields.Command = Command;
  CrashLogMailboxInterface.Fields.Param = Param;
  CrashLogMailboxInterface.Fields.Busy = 1;

  MmioWrite32 (CrashLogBaseAddress + R_CRASHLOG_MAILBOX_INTERFACE_ADDRESS, CrashLogMailboxInterface.InterfaceData);

  CpuCrashLogPollMailboxReady (CrashLogBaseAddress + R_CRASHLOG_MAILBOX_INTERFACE_ADDRESS);
  return Status;
}

/**
  Get CPU CrashLog Main pointer data

  @param[in]    BaseAddr          Pci configuration space MMIO address of CrashLog BAR
  @param[out]   *CrashDataBuff    Pointer to CrashLog Main data buffer
**/
EFI_STATUS
CpuCrashLogMainDiscovery (
  IN   UINT32                 BaseAddr,
  OUT  CPU_CRASHLOG_BUFFER    *CrashDataBuff
  )
{
  CrashDataBuff->Data = ((UINT64) MmioRead32 (BaseAddr + R_CRASHLOG_MAIN_POINTER_OFFSET) + \
                          LShiftU64((UINT64) MmioRead32 (BaseAddr + R_CRASHLOG_MAIN_POINTER_OFFSET + 4), 32));

  if (MmioRead32 (CrashDataBuff->Fields.DataBuffAddress) == 0) {
    DEBUG ((DEBUG_INFO, "CPU CrashLog: No Main CrashLog\n"));
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
  Get CPU CrashLog Telemetry pointer data

  @param[in]    BaseAddr          Pci configuration space MMIO address of CrashLog BAR
  @param[out]   *CrashDataBuff    Pointer to CrashLog Telemetry data buffer
**/
EFI_STATUS
CpuCrashLogTelemetryDiscovery (
  IN   UINT32                 BaseAddr,
  OUT  CPU_CRASHLOG_BUFFER    *CrashDataBuff
  )
{
  CrashDataBuff->Data = ((UINT64) MmioRead32 (BaseAddr + R_CRASHLOG_TELEMETRY_POINTER_OFFSET) + \
                          LShiftU64((UINT64) MmioRead32 (BaseAddr + R_CRASHLOG_TELEMETRY_POINTER_OFFSET + 4), 32));

  if (CrashDataBuff->Fields.DataBuffAddress == 0x0) {
    DEBUG ((DEBUG_INFO, "CPU CrashLog: No Telemetry CrashLog\n"));
    return EFI_UNSUPPORTED;
  }
  return EFI_SUCCESS;
}

/**
  Get CPU CrashLog Trace pointer data

  @param[in]    BaseAddr          Pci configuration space MMIO address of CrashLog BAR
  @param[out]   *CrashDataBuff    Pointer to CrashLog Trace data buffer
**/
EFI_STATUS
CpuCrashLogTraceDiscovery (
  IN   UINT32                 BaseAddr,
  OUT  CPU_CRASHLOG_BUFFER    *CrashDataBuff
  )
{
  CrashDataBuff->Data = MmioRead64 (BaseAddr + R_CRASHLOG_TRACE_POINTER_OFFSET);
  CrashDataBuff->Data = ((UINT64) MmioRead32 (BaseAddr + R_CRASHLOG_TRACE_POINTER_OFFSET) + \
                          LShiftU64((UINT64) MmioRead32 (BaseAddr + R_CRASHLOG_TRACE_POINTER_OFFSET + 4), 32));

  if (CrashDataBuff->Fields.DataBuffAddress == 0x0) {
    DEBUG ((DEBUG_INFO, "CPU CrashLog: No Trace CrashLog\n"));
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
  This function disables cpu crash log

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_DEVICE_ERROR        Mailbox command failed with an error
  @retval EFI_TIMEOUT             Mailbox command did not complete
**/
EFI_STATUS
CpuCrashLogDisable (
  VOID
  )
{
  return CpuCrashLogMailboxCommand (V_CPU_CRASHLOG_CMD_DISABLE, 0);
}

/**
  This function configures the DEVEN for CrashLog Device

  @param[in]    CpuCrashLogDevice    Enable/Disable the CrashLog Device
**/
VOID
ConfigureCrashLogDevEn (
  BOOLEAN                 CpuCrashLogDevice
)
{
  UINT64                  McD0BaseAddress;
  UINT32                  DevEn;
  CPU_FAMILY              CpuFamily;
  CPU_STEPPING            CpuSteppingId;
  UINT32                  DeviceBase;

  DeviceBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, TEL_BUS_NUM, TEL_DEV_NUM, TEL_FUN_NUM, 0);
  if (PciSegmentRead16 (DeviceBase + PCI_VENDOR_ID_OFFSET) == V_SA_DEVICE_ID_INVALID) {
    DEBUG ((DEBUG_ERROR, "Telemetry PCI device is disabled\n"));
    return;
  }
  CpuFamily     = GetCpuFamily ();
  CpuSteppingId = GetCpuStepping ();

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  DevEn = PciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN);

  if (CpuFamily == EnumCpuTglUltUlx && CpuSteppingId == EnumTglA0) {
    DEBUG ((DEBUG_INFO, "Telemetry CPU CrashLog Device: Skipping DevEn update. DEVEN=0x%X\n",DevEn));
    return;
  }
  ///
  /// Enable/Disable CrashLog device (B0,D10,F0).
  ///
  if ( CpuCrashLogDevice ) {
    DevEn |= B_SA_DEVEN_D10F0EN_MASK;
  } else {
    DevEn &= ~(B_SA_DEVEN_D10F0EN_MASK);
  }

  DEBUG ((DEBUG_INFO, "Configuring Telemetry CPU CrashLog Device with DEVEN 0x%x \n",DevEn));
  PciSegmentWrite32 (McD0BaseAddress + R_SA_DEVEN, DevEn);
}

/**
  This function enable Telemetry's MSE after PciEnumerationComplete
**/
VOID
TelemetryMseEn (
  VOID
)
{
  UINT32  DeviceBase;

  DeviceBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, TEL_BUS_NUM, TEL_DEV_NUM, TEL_FUN_NUM, 0);

  if (PciSegmentRead16 (DeviceBase + PCI_VENDOR_ID_OFFSET) == V_SA_DEVICE_ID_INVALID) {
    DEBUG ((DEBUG_ERROR, "Telemetry PCI device is disabled\n"));
    return;
  }

  DEBUG ((DEBUG_INFO, "Enable MSE of Telemetry\n"));
  PciSegmentOr8 (DeviceBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
}
