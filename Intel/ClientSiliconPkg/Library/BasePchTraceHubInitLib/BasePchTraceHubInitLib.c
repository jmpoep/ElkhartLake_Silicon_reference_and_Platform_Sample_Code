/** @file
  Base Pch TraceHub Init Lib.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
  Intel Trace Hub (Intel(R) TH) Developer's Manual Revision 2.1.1 December 2016
**/
#include <Base.h>
#include <Uefi.h>
#include <IndustryStandard/Pci.h>
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/DebugLib.h>

#define PCH_TRACE_HUB_PCI_CFG_MTB_LBAR_OFFSET 0x10
#define PCH_TRACE_HUB_PCI_CFG_MTB_UBAR_OFFSET 0x14
#define PCH_TRACE_HUB_PCI_CFG_SW_LBAR_OFFSET 0x18
#define PCH_TRACE_HUB_PCI_CFG_SW_UBAR_OFFSET 0x1C
#define PCH_TRACE_HUB_PCI_CFG_FW_LBAR_OFFSET 0x70
#define PCH_TRACE_HUB_PCI_CFG_FW_UBAR_OFFSET 0x74

/**
  This function performs basic PCI initialization for PchTraceHub.

  @retval EFI_SUCCESS                Trace Hub is initialized successfully.
  @retval EFI_DEVICE_ERROR           Trace Hub is not present.
**/
RETURN_STATUS
EFIAPI
PchTraceHubInitialize (
  VOID
  )
{
  UINT64  TraceHubBaseAddress;

  //
  // Check if Trace Hub Device is present
  //
  TraceHubBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                          PcdGet16 (PcdPchTraceHubPciSeg),
                          PcdGet8 (PcdPchTraceHubPciBus),
                          PcdGet8 (PcdPchTraceHubPciDev),
                          PcdGet8 (PcdPchTraceHubPciFun),
                          0);
  DEBUG ((DEBUG_INFO, "TraceHubBaseAddress = 0x%x\n", TraceHubBaseAddress));
  if (PciSegmentRead16 (TraceHubBaseAddress) == 0xFFFF) {
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Program the MTB Base Address Register fixed BAR
  ///
  PciSegmentWrite32 (TraceHubBaseAddress + PCH_TRACE_HUB_PCI_CFG_MTB_LBAR_OFFSET, (UINT32)PcdGet64 (PcdPchTraceHubMtbBaseAddr));
  PciSegmentWrite32 (TraceHubBaseAddress + PCH_TRACE_HUB_PCI_CFG_MTB_UBAR_OFFSET, (UINT32)(PcdGet64 (PcdPchTraceHubMtbBaseAddr) >> 32));

  ///
  /// Program the SW Base Address Register with fixed BAR
  ///
  PciSegmentWrite32 (TraceHubBaseAddress + PCH_TRACE_HUB_PCI_CFG_SW_LBAR_OFFSET, (UINT32)PcdGet64 (PcdPchTraceHubSwBaseAddr));
  PciSegmentWrite32 (TraceHubBaseAddress + PCH_TRACE_HUB_PCI_CFG_SW_UBAR_OFFSET, (UINT32)(PcdGet64 (PcdPchTraceHubSwBaseAddr) >> 32));

  ///
  /// Program the FW Base Address Register with fixed BAR
  ///
  PciSegmentWrite32 (TraceHubBaseAddress + PCH_TRACE_HUB_PCI_CFG_FW_LBAR_OFFSET, (UINT32)PcdGet64 (PcdPchTraceHubFwBaseAddr));
  PciSegmentWrite32 (TraceHubBaseAddress + PCH_TRACE_HUB_PCI_CFG_FW_UBAR_OFFSET, (UINT32)(PcdGet64 (PcdPchTraceHubFwBaseAddr) >> 32));

  ///
  /// Enable MSE and BME
  ///
  PciSegmentOr8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER);

  return EFI_SUCCESS;
}
