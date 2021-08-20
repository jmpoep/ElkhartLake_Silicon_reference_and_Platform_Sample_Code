/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#include "ITbtSmiHandler.h"
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Protocol/SmmVariable.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/ItbtPcieRpLib.h>

extern UINTN                 gDeviceBaseAddress;

extern UINT8                      gCurrentIntegratedTbtRootPort;

STATIC UINT8 TbtSegment         = 0;

BOOLEAN
InitializeITbtRootPort (
  IN UINTN   Bus,
  IN UINTN   Device,
  IN UINTN   Function
  )
{
  BRDG_RES_CONFIG HrResConf = { 0 };
  BOOLEAN         Ret;

  DEBUG((DEBUG_INFO, "InitializeITbtRootPort Start\n"));

  Ret = TRUE;

  HrResConf.Cmd          = CMD_BM_MEM;
  HrResConf.Cls          = DEF_CACHE_LINE_SIZE;
  gDeviceBaseAddress     = PCI_SEGMENT_LIB_ADDRESS ((UINT32)TbtSegment, (UINT32)Bus, (UINT32)Device, (UINT32)Function, 0);
  HrResConf.IoBase       = PciSegmentRead8 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.IoBase));
  HrResConf.IoLimit      = PciSegmentRead8 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.IoLimit));
  HrResConf.MemBase      = PciSegmentRead16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.MemoryBase));
  HrResConf.MemLimit     = PciSegmentRead16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.MemoryLimit));
  HrResConf.PMemBase64   = PciSegmentRead16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableMemoryBase));
  HrResConf.PMemLimit64  = PciSegmentRead16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableMemoryLimit));
  HrResConf.PMemBase64  |= (UINT64)(PciSegmentRead32 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableBaseUpper32))) << 16;
  HrResConf.PMemLimit64 |= (UINT64)(PciSegmentRead32 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableLimitUpper32))) << 16;

  PciSegmentWrite8 (gDeviceBaseAddress + PCI_CACHELINE_SIZE_OFFSET, HrResConf.Cls);
  HrResConf.IoBase       = 0xF1;
  HrResConf.IoLimit      = 0x01;

  PciSegmentWrite8 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.IoBase), HrResConf.IoBase);
  PciSegmentWrite8 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.IoLimit), HrResConf.IoLimit);

  DEBUG((DEBUG_INFO, "Bus = %x Dev = %x Func = %x\n", Bus, Device, Function));
  DEBUG((DEBUG_INFO, "IoBase = %x\n", HrResConf.IoBase));
  DEBUG((DEBUG_INFO, "IoLimit = %x\n", HrResConf.IoLimit));
  DEBUG((DEBUG_INFO, "MemBase = %x\n", HrResConf.MemBase));
  DEBUG((DEBUG_INFO, "MemLimit = %x\n", HrResConf.MemLimit));
  DEBUG((DEBUG_INFO, "PMemBase64 = %x\n", HrResConf.PMemBase64));
  DEBUG((DEBUG_INFO, "PMemLimit64 = %x\n", HrResConf.PMemLimit64));
  DEBUG((DEBUG_INFO, "Cache Line Size = %x\n", HrResConf.Cls));

  DEBUG((DEBUG_INFO, "InitializeITbtRootPort End\n"));

  return Ret;
} //InitializeITbtRootPort

VOID
ITbtCallback (
  VOID
  )
{
  PORT_INFO  PortInfoOrg;
  EFI_STATUS Status;
  UINTN      Segment;
  UINTN      Bus;
  UINTN      Device;
  UINTN      Function;

  //
  // Initialize variables
  //
  Segment = 0;
  Bus = 0;
  Device = 0;
  Function = 0;
  ZeroMem (&PortInfoOrg, sizeof (PORT_INFO));

  DEBUG((DEBUG_INFO, "IThunderboltCallback.Entry\n"));

  DEBUG((DEBUG_INFO, "PortInfo Initialization\n"));
  PortInfoInit (&PortInfoOrg);
    DEBUG((DEBUG_INFO, "Initialize ITBT Root Port\n"));
    if (gCurrentIntegratedTbtRootPort == 0) {
      DEBUG((DEBUG_ERROR, "Invalid RP Input\n"));
      return;
    }
    Status = GetItbtPcieRpInfo((UINTN)gCurrentIntegratedTbtRootPort - 1, &Segment, &Bus, &Device, &Function);
    if (EFI_ERROR(Status)) {
      DEBUG((DEBUG_ERROR, "RP Not enabled\n"));
      return;
    }
    TbtSegment = (UINT8) Segment;
    if (!InitializeITbtRootPort(Bus, Device, Function)) {
        return ;
    }
    //
    // Configure DS ports
    //
    DEBUG((DEBUG_INFO, "ConfigurePort\n"));
    ConfigurePort ((UINT8)Bus, (UINT8)Device,(UINT8)Function, &PortInfoOrg);

  DEBUG((DEBUG_INFO, "IThunderboltCallback.Exit\n"));
} // ThunderboltCallback

VOID
ITbtDisablePCIDevicesAndBridges (
  VOID
  )
{
  UINTN         Segment = 0;
  UINTN         Bus = 0;
  UINTN         Device;
  UINTN         Function;
  EFI_STATUS    Status;
  UINT8         MinBus;
  UINT8         MaxBus;

  MinBus = 1;
  if (gCurrentIntegratedTbtRootPort == 0) {
    return;
  }
  Status = GetItbtPcieRpInfo((UINTN)gCurrentIntegratedTbtRootPort - 1, &Segment, &Bus, &Device, &Function);
  if (EFI_ERROR(Status)) {
    return;
  }
  TbtSegment = (UINT8) Segment;
  gDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS ((UINT32)TbtSegment, (UINT32)Bus, (UINT32)Device, (UINT32)Function, 0);
  MinBus            = PciSegmentRead8 (gDeviceBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);
  MaxBus            = PciSegmentRead8 (gDeviceBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET);
  DisablePCIDevicesAndBridges(MinBus, MaxBus);
} // ITbtDisablePCIDevicesAndBridges


