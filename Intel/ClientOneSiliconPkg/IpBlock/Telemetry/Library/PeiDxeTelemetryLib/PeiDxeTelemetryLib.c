/** @file

  Telemetry Library

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
#include <Library/TelemetryLib.h>
#include <Library/TelemetryPrivateLib.h>
#include <SaCommonDefinitions.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <IndustryStandard/Pci30.h>

/**
  Find the address of Cpu CrashLog ID

  @param[out] CrashLogDevscCap     Pointer to structure of CrashLog DEVSC Data

  @retval EFI_UNSUPPORTED          Cpu CrashLog ID not found
  @retval EFI_SUCCESS              Cpu CrashLog ID found
**/
EFI_STATUS
GetCpuCrashLogCapability (
  OUT TEL_CRASHLOG_DEVSC_CAP  *CrashLogDevscCap
  )
{
  UINT64              DeviceBase;
  UINT64              DevscCapAddress;

  DeviceBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, TEL_BUS_NUM, TEL_DEV_NUM, TEL_FUN_NUM, 0);
  if (PciSegmentRead16 (DeviceBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_ERROR, "Telemetry PCI device is disabled\n"));
    return EFI_UNSUPPORTED;
  }

  DevscCapAddress = DeviceBase + R_TEL_DVSEC_OFFSET;
  //
  // Check if it's Telemetry Aggregator Capbility
  //
  CrashLogDevscCap->CapData.Data = PciSegmentRead32 (DevscCapAddress + R_TEL_DVSEC_PCIE_CAP_ID);
  if (CrashLogDevscCap->CapData.Fields.PcieCapId != V_TELEMETRY_EXTENDED_CAP_ID) {
    DEBUG ((DEBUG_INFO, "DevscCapAddress = 0x%x\n", DevscCapAddress));

    return EFI_UNSUPPORTED;
  }
  //
  // Check if it's CrashLog entry. If not, check the next entry
  //
  CrashLogDevscCap->DevscData.Data32[1] = PciSegmentRead32 (DevscCapAddress + R_TEL_DVSEV_ID);
  while (CrashLogDevscCap->DevscData.Fields.DevscId != V_CRASHLOG_DVSEC_ID) {
    DEBUG ((DEBUG_INFO, "Next Capability Offset = 0x%x\n", CrashLogDevscCap->CapData.Fields.NextCapOffset));
    //
    // If the reading of Next Cap offset is not valid number, then return UNSUPPORTED
    //
    if (CrashLogDevscCap->CapData.Fields.NextCapOffset == 0 || CrashLogDevscCap->CapData.Fields.NextCapOffset == 0xFFF) {
      return EFI_UNSUPPORTED;
    } else {
      DevscCapAddress = DeviceBase + CrashLogDevscCap->CapData.Fields.NextCapOffset;
      DEBUG ((DEBUG_INFO, "Next Capability Address = 0x%x\n", DevscCapAddress));
    }
    CrashLogDevscCap->CapData.Data = PciSegmentRead32 (DevscCapAddress + R_TEL_DVSEC_PCIE_CAP_ID);
    CrashLogDevscCap->DevscData.Data32[1] = PciSegmentRead32 (DevscCapAddress + R_TEL_DVSEV_ID);
  }
  //
  // CrashLog DEVSC capability is found
  //
  CrashLogDevscCap->DiscoveryData.Data = PciSegmentRead32 (DevscCapAddress + R_TEL_DVSEV_DISCOVERY_TABLE_OFFSET);

  DEBUG ((DEBUG_INFO, "Discovery Buffer offset = 0x%x\n", CrashLogDevscCap->DiscoveryData.Fields.DiscoveryTableOffset));

  return EFI_SUCCESS;
}

/**
  This function returns the value of CPU CrashLog BAR.

  @param[in] CrashLogDevscCap     Structure of CrashLog DEVSC Data

  @retval BaseAddr                MMIO address of CrashLog BAR
**/
UINT32
GetCpuCrashLogBarAddress (
  IN TEL_CRASHLOG_DEVSC_CAP  CrashLogDevscCap
  )
{
  UINT64                DeviceBase;
  UINT32                BaseAddr;

  DeviceBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, TEL_BUS_NUM, TEL_DEV_NUM, TEL_FUN_NUM, 0);

  BaseAddr = 0;
  if (CrashLogDevscCap.DiscoveryData.Fields.TBir == V_TEL_DVSEC_TBIR_BAR0) {
    BaseAddr = (PciSegmentRead32 (DeviceBase + R_TEL_CFG_BAR0) & 0xFFFFFFF0);
  } else if (CrashLogDevscCap.DiscoveryData.Fields.TBir == V_TEL_DVSEC_TBIR_BAR1) {
    BaseAddr = (PciSegmentRead32 (DeviceBase + R_TEL_CFG_BAR1) & 0xFFFFFFF0);
  }

  return BaseAddr;
}

/**
  This function clears cpu crash log

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_DEVICE_ERROR        Mailbox command failed with an error
  @retval EFI_TIMEOUT             Mailbox command did not complete
**/
EFI_STATUS
CpuCrashLogClear (
  VOID
  )
{
  return CpuCrashLogMailboxCommand (V_CPU_CRASHLOG_CMD_CLEAR, 0);
}

/**
  Get CPU CrashLog Header data

  @param[in]    BaseAddr              Pci configuration space MMIO address of CrashLog BAR
  @param[out]   CrashLogHeaderBuff    Pointer to CrashLog Header Data
**/
VOID
GetCrashLogHeader (
  IN  UINT32                BaseAddr,
  OUT CPU_CRASHLOG_HEADER   *CrashLogHeaderBuff
  )
{
  UINT32                 CrashLogHeaderAddress;

  CrashLogHeaderAddress = BaseAddr + R_CRASHLOG_HEADER_ADDRESS;

  ZeroMem (&CrashLogHeaderBuff, sizeof (CPU_CRASHLOG_HEADER));
  CrashLogHeaderBuff->HeaderData = ((UINT64) MmioRead32 (CrashLogHeaderAddress) + LShiftU64((UINT64) MmioRead32 (CrashLogHeaderAddress+4), 32));
}

/**
  This function discovers CPU crashLog and gets the size of each

  @param[out] CrashLogStruct      Pointer to CrashLog Discovery Data

  @retval EFI_UNSUPPORTED         Cpu CrashLog is not supported
  @retval EFI_SUCCESS             Cpu CrashLog is supported
**/
EFI_STATUS
CpuCrashLogDiscovery (
  OUT  CPU_CRASHLOG_STRUCT    *CrashLogStruct
  )
{
  EFI_STATUS               Status;
  UINT32                   CrashLogBaseAddress;
  TEL_CRASHLOG_DEVSC_CAP   CrashLogDevscCap;
  CPU_CRASHLOG_BUFFER      CrashLogPointerBuff;

  ZeroMem (&CrashLogDevscCap, sizeof (TEL_CRASHLOG_DEVSC_CAP));
  ZeroMem (&CrashLogPointerBuff, sizeof (CPU_CRASHLOG_BUFFER));
  Status = GetCpuCrashLogCapability (&CrashLogDevscCap);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "CPU CrashLog feature is not supported\n"));
    return Status;
  }

  CrashLogBaseAddress = GetCpuCrashLogBarAddress (CrashLogDevscCap);
  Status = CpuCrashLogMainDiscovery (CrashLogBaseAddress, &CrashLogPointerBuff);
  if (!EFI_ERROR (Status)) {
    CrashLogStruct->MainBuffer.Data = CrashLogPointerBuff.Data;
  }

  Status = CpuCrashLogTelemetryDiscovery (CrashLogBaseAddress, &CrashLogPointerBuff);
  if (!EFI_ERROR (Status)) {
    CrashLogStruct->TelemetryBuffer.Data = CrashLogPointerBuff.Data;
  }

  Status = CpuCrashLogTraceDiscovery (CrashLogBaseAddress, &CrashLogPointerBuff);
  if (!EFI_ERROR (Status)) {
    CrashLogStruct->TraceBuffer.Data = CrashLogPointerBuff.Data;
  }

  return EFI_SUCCESS;
}