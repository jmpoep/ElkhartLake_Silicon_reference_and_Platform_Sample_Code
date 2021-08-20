/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

#include "DTbtSmiHandler.h"
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Protocol/SmmVariable.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/PciSegmentLib.h>

extern UINTN                 gDeviceBaseAddress;
//
//US(X:0:0), DS(X+1:3:0),DS(X+1:4:0),DS(X+1:5:0),DS(X+1:6:0)
//
GLOBAL_REMOVE_IF_UNREFERENCED BRDG_CONFIG           HrConfigs[MAX_CFG_PORTS];

extern UINT8                      gCurrentDiscreteTbtRootPort;
extern UINT8                      gCurrentDiscreteTbtRootPortType;

STATIC UINT8 TbtSegment         = 0;

STATIC
VOID
InitARHRConfigs(
  IN HR_CONFIG *Hr_Config,
  IN UINT8 BusNumLimit,
  IN OUT BRDG_RES_CONFIG* HrResConf
)
{
  UINT8 i,j;

  //
  // DS port for USB device
  //
  HrConfigs[AR_DS_PORT2].DevId.Bus = HrConfigs[HR_US_PORT].DevId.Bus + 1;
  HrConfigs[AR_DS_PORT2].DevId.Dev = 2;
  HrConfigs[AR_DS_PORT2].DevId.Fun = 0;
  HrConfigs[AR_DS_PORT2].PBus = HrConfigs[AR_DS_PORT2].DevId.Bus;
  HrConfigs[AR_DS_PORT2].SBus = HrConfigs[AR_DS_PORT2].PBus + 1;
  HrConfigs[AR_DS_PORT2].SubBus = HrConfigs[AR_DS_PORT2].PBus + 1;
  //
  // CIO port
  //
  HrConfigs[AR_DS_PORT1].DevId.Bus = HrConfigs[HR_US_PORT].DevId.Bus + 1;
  HrConfigs[AR_DS_PORT1].DevId.Dev = 1;
  HrConfigs[AR_DS_PORT1].DevId.Fun = 0;
  HrConfigs[AR_DS_PORT1].PBus = HrConfigs[AR_DS_PORT1].DevId.Bus;
  HrConfigs[AR_DS_PORT1].SBus = HrConfigs[HR_DS_PORT0].SubBus + 1;
  HrConfigs[AR_DS_PORT1].SubBus = BusNumLimit;

  switch(Hr_Config->DeviceId)
  {
    //
    // HR with 1 DS and 1 USB
    //
    case AR_HR_2C:
    case AR_HR_LP:
    case AR_HR_C0_2C:
    case TR_HR_2C:
      Hr_Config->MinDSNumber = HrConfigs[AR_DS_PORT1].DevId.Dev;
      Hr_Config->MaxDSNumber = HrConfigs[AR_DS_PORT2].DevId.Dev;
      Hr_Config->BridgeLoops = 4;
      break;
    //
    // HR with 2 DS and 1 USB
    //
    case AR_HR_4C:
    case TR_HR_4C:
    case AR_HR_C0_4C:
      Hr_Config->MinDSNumber = 1;
      Hr_Config->MaxDSNumber = 4;
      Hr_Config->BridgeLoops = 6;
      for(j = 2, i = Hr_Config->MinDSNumber; j < count(HrConfigs) && i <= Hr_Config->MaxDSNumber; ++j, ++i)
      {
        HrConfigs[j].DevId.Bus = HrConfigs[HR_US_PORT].DevId.Bus + 1;
        HrConfigs[j].DevId.Dev = i;
        HrConfigs[j].DevId.Fun = 0;
        HrConfigs[j].PBus = HrConfigs[j].DevId.Bus;
        HrConfigs[j].Res.Cls = DEF_CACHE_LINE_SIZE;
      }
    break;
  }
}//InitARHRConfigs


STATIC
VOID
InitCommonHRConfigs (
  IN       HR_CONFIG        *Hr_Config,
  IN       UINT8            BusNumLimit,
  IN  OUT  BRDG_RES_CONFIG  *HrResConf
  )
{
  UINT8 i;

  UINT8 j;
  for(i = 0; i < count(HrConfigs); ++i) {
    HrConfigs[i].IsDSBridge = TRUE;
  }
  //
  // US(HRBus:0:0)
  //
  HrConfigs[HR_US_PORT].DevId.Bus   = Hr_Config->HRBus;
  HrConfigs[HR_US_PORT].DevId.Dev   = 0;
  HrConfigs[HR_US_PORT].DevId.Fun   = 0;
  HrConfigs[HR_US_PORT].Res         = *HrResConf;
  HrConfigs[HR_US_PORT].Res.IoBase  = 0xF1;
  HrConfigs[HR_US_PORT].Res.IoLimit = 0x01;
  HrConfigs[HR_US_PORT].PBus        = HrConfigs[HR_US_PORT].DevId.Bus;
  HrConfigs[HR_US_PORT].SBus        = HrConfigs[HR_US_PORT].PBus + 1;
  HrConfigs[HR_US_PORT].SubBus      = BusNumLimit;
  HrConfigs[HR_US_PORT].IsDSBridge  = FALSE;

  //
  // HIA resides here
  //
  HrConfigs[HR_DS_PORT0].DevId.Bus    = HrConfigs[HR_US_PORT].DevId.Bus + 1;
  HrConfigs[HR_DS_PORT0].DevId.Dev    = 0;
  HrConfigs[HR_DS_PORT0].DevId.Fun    = 0;
  HrConfigs[HR_DS_PORT0].Res          = NOT_IN_USE_BRIDGE;
  HrConfigs[HR_DS_PORT0].Res.MemBase  = HrResConf->MemLimit;
  HrConfigs[HR_DS_PORT0].Res.MemLimit = HrResConf->MemLimit;
  HrResConf->MemLimit                -= 0x10; //This 1 MB chunk will be used by HIA
  HrConfigs[HR_DS_PORT0].Res.Cmd      = CMD_BM_MEM;
  HrConfigs[HR_DS_PORT0].Res.Cls      = DEF_CACHE_LINE_SIZE;
  HrConfigs[HR_DS_PORT0].PBus         = HrConfigs[HR_DS_PORT0].DevId.Bus;
  HrConfigs[HR_DS_PORT0].SBus         = HrConfigs[HR_DS_PORT0].PBus + 1;
  HrConfigs[HR_DS_PORT0].SubBus       = HrConfigs[HR_DS_PORT0].PBus + 1;

  switch (Hr_Config->DeviceId) {
  //
  // Alpine Ridge
  //
  case AR_HR_2C:
  case AR_HR_C0_2C:
  case AR_HR_LP:
  case AR_HR_4C:
  case AR_HR_C0_4C:
  //
  // Titan Ridge
  //
  case TR_HR_2C:
  case TR_HR_4C:
    InitARHRConfigs(Hr_Config, BusNumLimit, HrResConf);
    break;

  default:
    //
    // DS(HRBus+2:3-6:0)
    //
    Hr_Config->MinDSNumber  = 3;
    Hr_Config->MaxDSNumber  = 6;
    Hr_Config->BridgeLoops  = count (HrConfigs);

    for (j = 2, i = Hr_Config->MinDSNumber; j < count (HrConfigs) && i <= Hr_Config->MaxDSNumber; ++j, ++i) {
      HrConfigs[j].DevId.Bus  = HrConfigs[HR_US_PORT].DevId.Bus + 1;
      HrConfigs[j].DevId.Dev  = i;
      HrConfigs[j].DevId.Fun  = 0;
      HrConfigs[j].PBus       = HrConfigs[j].DevId.Bus;
      HrConfigs[j].Res.Cls    = DEF_CACHE_LINE_SIZE;
    }
  }
} // InitCommonHRConfigs

STATIC
VOID
InitHRDSPort_Disable (
  IN       UINT8        id,
  IN  OUT  BRDG_CONFIG  *BrdgConf
  )
{
  HrConfigs[id].Res     = NOT_IN_USE_BRIDGE;
  HrConfigs[id].SBus    = BrdgConf->SBus;
  HrConfigs[id].SubBus  = BrdgConf->SBus;

  BrdgConf->SBus++;
} // InitHRDSPort_Disable

//AR only

STATIC
VOID
InitARDSPort_1Port(
  IN  OUT  BRDG_CONFIG* BrdgConf
)
{
  UINT16 MemBase    = BrdgConf->Res.MemBase & 0xFFF0;
  UINT64 PMemBase64 = BrdgConf->Res.PMemBase64 & ~0xFULL;
  UINT8  BusRange = BrdgConf->SubBus - BrdgConf->PBus - 2;

  HrConfigs[AR_DS_PORT1].Res = NOT_IN_USE_BRIDGE;
  HrConfigs[AR_DS_PORT1].Res.Cls = DEF_CACHE_LINE_SIZE;
  HrConfigs[AR_DS_PORT1].Res.Cmd = CMD_BM_MEM;
  HrConfigs[AR_DS_PORT1].Res.MemBase = MemBase;
  HrConfigs[AR_DS_PORT1].Res.MemLimit = BrdgConf->Res.MemLimit - 1;
  HrConfigs[AR_DS_PORT1].Res.PMemBase64 = PMemBase64;
  HrConfigs[AR_DS_PORT1].Res.PMemLimit64 = BrdgConf->Res.PMemLimit64;
  HrConfigs[AR_DS_PORT1].SBus = BrdgConf->SBus;
  HrConfigs[AR_DS_PORT1].SubBus = BrdgConf->SBus + BusRange;

  BrdgConf->SBus = HrConfigs[AR_DS_PORT1].SubBus + 1;

  HrConfigs[AR_DS_PORT2].Res = NOT_IN_USE_BRIDGE;
  HrConfigs[AR_DS_PORT2].Res.Cls = DEF_CACHE_LINE_SIZE;
  HrConfigs[AR_DS_PORT2].Res.Cmd = CMD_BM_MEM;
  HrConfigs[AR_DS_PORT2].Res.MemBase = BrdgConf->Res.MemLimit;
  HrConfigs[AR_DS_PORT2].Res.MemLimit = BrdgConf->Res.MemLimit;
  HrConfigs[AR_DS_PORT2].SBus = BrdgConf->SBus;
  HrConfigs[AR_DS_PORT2].SubBus = BrdgConf->SBus;

  BrdgConf->SBus = HrConfigs[AR_DS_PORT2].SubBus + 1;
}//InitARDSPort_1Port

STATIC
VOID
InitARDSPort_2Port(
  IN OUT BRDG_CONFIG* BrdgConf
)
{
  UINT16 MemBase    = BrdgConf->Res.MemBase & 0xFFF0;
  UINT64 PMemBase64 = BrdgConf->Res.PMemBase64 & ~0xFULL;
  UINT8  BusRange = BrdgConf->SubBus - BrdgConf->PBus - 3;

  // Busses are split between ports 1 and 4
  BusRange /= 2;

  HrConfigs[AR_DS_PORT1].Res = NOT_IN_USE_BRIDGE;
  HrConfigs[AR_DS_PORT1].Res.Cls = DEF_CACHE_LINE_SIZE;
  HrConfigs[AR_DS_PORT1].Res.Cmd = CMD_BM_MEM;
  HrConfigs[AR_DS_PORT1].Res.MemBase = MemBase;
  HrConfigs[AR_DS_PORT1].Res.MemLimit = MemBase + 0x17F0 - 1;
  HrConfigs[AR_DS_PORT1].Res.PMemBase64 = PMemBase64;
  HrConfigs[AR_DS_PORT1].Res.PMemLimit64 = PMemBase64 + 0x2000 - 1;
  HrConfigs[AR_DS_PORT1].SBus = BrdgConf->SBus;
  HrConfigs[AR_DS_PORT1].SubBus = BrdgConf->SBus + BusRange;

  BrdgConf->SBus = HrConfigs[AR_DS_PORT1].SubBus + 1;

  HrConfigs[AR_DS_PORT2].Res = NOT_IN_USE_BRIDGE;
  HrConfigs[AR_DS_PORT2].Res.Cls = DEF_CACHE_LINE_SIZE;
  HrConfigs[AR_DS_PORT2].Res.Cmd = CMD_BM_MEM;
  HrConfigs[AR_DS_PORT2].Res.MemBase = MemBase + 0x17F0;
  HrConfigs[AR_DS_PORT2].Res.MemLimit = MemBase + 0x1800 - 1;
  HrConfigs[AR_DS_PORT2].SBus = BrdgConf->SBus;
  HrConfigs[AR_DS_PORT2].SubBus = BrdgConf->SBus;

  BrdgConf->SBus = HrConfigs[AR_DS_PORT2].SubBus + 1;


  HrConfigs[AR_DS_PORT4].Res = NOT_IN_USE_BRIDGE;
  HrConfigs[AR_DS_PORT4].Res.Cls = DEF_CACHE_LINE_SIZE;
  HrConfigs[AR_DS_PORT4].Res.Cmd = CMD_BM_MEM;
  HrConfigs[AR_DS_PORT4].Res.MemBase = MemBase + 0x1800;
  HrConfigs[AR_DS_PORT4].Res.MemLimit = BrdgConf->Res.MemLimit;
  HrConfigs[AR_DS_PORT4].Res.PMemBase64 = PMemBase64 + 0x2000;
  HrConfigs[AR_DS_PORT4].Res.PMemLimit64 = BrdgConf->Res.PMemLimit64;
  HrConfigs[AR_DS_PORT4].SBus = BrdgConf->SBus;
  HrConfigs[AR_DS_PORT4].SubBus = BrdgConf->SubBus;

  BrdgConf->SBus = HrConfigs[AR_DS_PORT4].SubBus + 1;
}//InitARDSPort_2Port

STATIC
BOOLEAN
CheckLimits (
  IN    BOOLEAN          Is2PortDev,
  IN    BRDG_RES_CONFIG  *HrResConf,
  IN    UINT8            BusRange
  )
{
  UINT16  MemBase;
  UINT16  MemLimit;
  UINT64  PMemBase64;
  UINT64  PMemLimit64;

  MemBase     = HrResConf->MemBase & 0xFFF0;
  MemLimit    = HrResConf->MemLimit & 0xFFF0;
  PMemBase64  = HrResConf->PMemBase64 & 0xFFF0;
  PMemLimit64 = HrResConf->PMemLimit64 & 0xFFF0;
  //
  // Check memoty alignment
  //
  if (MemBase & 0x3FF) {
    DEBUG((DEBUG_INFO, "M alig\n"));
    return FALSE;
  }

  if (PMemBase64 & 0xFFF) {
    DEBUG((DEBUG_INFO, "PM alig\n"));
    return FALSE;
  }

  if (Is2PortDev) {
    //
    // Check mem size
    //
    if (MemLimit + 0x10 - MemBase < 0x2E00) {
      DEBUG((DEBUG_INFO, "M size\n"));
      return FALSE;
    }
    //
    // Check P-mem size
    //
    if (PMemLimit64 + 0x10 - PMemBase64 < 0x4A00) {
      DEBUG((DEBUG_INFO, "PM size\n"));
      return FALSE;
    }
    //
    // Check bus range
    //
    if (BusRange < 106) {
      DEBUG((DEBUG_INFO, "Bus range\n"));
      return FALSE;
    }
  } else {
    //
    // Check mem size
    //
    if (MemLimit + 0x10 - MemBase < 0x1600) {
      DEBUG((DEBUG_INFO, "M size\n"));
      return FALSE;
    }
    //
    // Check P-mem size
    //
    if (PMemLimit64 + 0x10 - PMemBase64 < 0x2200) {
      DEBUG((DEBUG_INFO, "PM size\n"));
      return FALSE;
    }
    //
    // Check bus range
    //
    if (BusRange < 56) {
      DEBUG((DEBUG_INFO, "Bus range\n"));
      return FALSE;
    }
  }

  return TRUE;
} // CheckLimits

STATIC
BOOLEAN
InitHRResConfigs (
  IN  OUT HR_CONFIG      *Hr_Config,
  IN    UINT8            BusNumLimit,
  IN  OUT BRDG_RES_CONFIG*HrResConf
  )
{
  BRDG_CONFIG  BrdgConf;

  ZeroMem (&BrdgConf, sizeof(BRDG_CONFIG));
  InitCommonHRConfigs (Hr_Config, BusNumLimit, HrResConf);
  BrdgConf.PBus   = Hr_Config->HRBus + 2;// Take into account busses
  BrdgConf.SBus   = Hr_Config->HRBus + 3;// for US and DS of HIA
  BrdgConf.SubBus = BusNumLimit;
  BrdgConf.Res    = *HrResConf;
  while (TRUE) {
    switch (Hr_Config->DeviceId) {
    case AR_HR_4C:
    case TR_HR_4C:
    case AR_HR_C0_4C:
      //
      // 2 Port host
      //
      if (CheckLimits (TRUE, HrResConf, BusNumLimit - Hr_Config->HRBus)) {


          InitARDSPort_2Port(&BrdgConf);
          DEBUG((DEBUG_INFO, "AR2\n"));

        return TRUE;
      } else {
       return FALSE;
      }
    // AR only
  case AR_HR_2C: // 1 port host
  case AR_HR_C0_2C:
  case AR_HR_LP:
  case TR_HR_2C:
    DEBUG((DEBUG_INFO, "AR1\n"));
    InitARDSPort_1Port(&BrdgConf);
    return TRUE;

    default:
      InitHRDSPort_Disable (HR_DS_PORT3, &BrdgConf);
      InitHRDSPort_Disable (HR_DS_PORT4, &BrdgConf);
      InitHRDSPort_Disable (HR_DS_PORT5, &BrdgConf);
      InitHRDSPort_Disable (HR_DS_PORT6, &BrdgConf);
      return FALSE;
    }
  }
} // InitHRResConfigs

STATIC
BOOLEAN
InitializeHostRouter (
  OUT  HR_CONFIG  *Hr_Config,
  IN   UINTN      RpSegment,
  IN   UINTN      RpBus,
  IN   UINTN      RpDevice,
  IN   UINTN      RpFunction
  )
{
  UINT8           BusNumLimit;
  BRDG_RES_CONFIG HrResConf;
  UINT8           i;
  BOOLEAN         Ret;

  ZeroMem (&HrResConf, sizeof(BRDG_RES_CONFIG));
  Ret = TRUE;

  gDeviceBaseAddress   = PCI_SEGMENT_LIB_ADDRESS (RpSegment, RpBus, RpDevice, RpFunction, 0);
  Hr_Config->HRBus    = PciSegmentRead8 (gDeviceBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);
  gDeviceBaseAddress   = PCI_SEGMENT_LIB_ADDRESS (RpSegment, Hr_Config->HRBus, 0x00, 0x00, 0);
  Hr_Config->DeviceId = PciSegmentRead16 (gDeviceBaseAddress + PCI_DEVICE_ID_OFFSET);
  if (!(IsTbtHostRouter (Hr_Config->DeviceId))) {
    return FALSE;
  }
  TbtSegment = (UINT8)RpSegment;

  HrResConf.Cmd          = CMD_BM_MEM;
  HrResConf.Cls          = DEF_CACHE_LINE_SIZE;
  gDeviceBaseAddress      = PCI_SEGMENT_LIB_ADDRESS (RpSegment, RpBus, RpDevice, RpFunction, 0);
  HrResConf.IoBase       = PciSegmentRead8 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.IoBase));
  HrResConf.IoLimit      = PciSegmentRead8 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.IoLimit));
  HrResConf.MemBase      = PciSegmentRead16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.MemoryBase));
  HrResConf.MemLimit     = PciSegmentRead16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.MemoryLimit));
  HrResConf.PMemBase64   = PciSegmentRead16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableMemoryBase));
  HrResConf.PMemLimit64  = PciSegmentRead16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableMemoryLimit));
  HrResConf.PMemBase64  |= (UINT64)(PciSegmentRead32 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableBaseUpper32))) << 16;
  HrResConf.PMemLimit64 |= (UINT64)(PciSegmentRead32 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableLimitUpper32))) << 16;
  BusNumLimit = PciSegmentRead8 (gDeviceBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET);

  Ret         = InitHRResConfigs (Hr_Config, BusNumLimit, &HrResConf);

  for (i = 0; i < Hr_Config->BridgeLoops; ++i) {
    UINT8 Bus;
    UINT8 Dev;
    UINT8 Fun;
    Bus               = HrConfigs[i].DevId.Bus;
    Dev               = HrConfigs[i].DevId.Dev;
    Fun               = HrConfigs[i].DevId.Fun;
    gDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (TbtSegment,Bus, Dev, Fun, 0);

    PciSegmentWrite8 (gDeviceBaseAddress + PCI_CACHELINE_SIZE_OFFSET, HrConfigs[i].Res.Cls);
    PciSegmentWrite8 (gDeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, HrConfigs[i].PBus);
    PciSegmentWrite8 (gDeviceBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET, HrConfigs[i].SBus);
    PciSegmentWrite8 (gDeviceBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET, HrConfigs[i].SubBus);
    PciSegmentWrite16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.MemoryBase), HrConfigs[i].Res.MemBase);
    PciSegmentWrite16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.MemoryLimit), HrConfigs[i].Res.MemLimit);
    PciSegmentWrite16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableMemoryBase), (UINT16) (HrConfigs[i].Res.PMemBase64 & 0xFFFF));
    PciSegmentWrite16 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableMemoryLimit), (UINT16) (HrConfigs[i].Res.PMemLimit64 & 0xFFFF));
    PciSegmentWrite32 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableBaseUpper32), (UINT32) (HrConfigs[i].Res.PMemBase64 >> 16));
    PciSegmentWrite32 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.PrefetchableLimitUpper32), (UINT32) (HrConfigs[i].Res.PMemLimit64 >> 16));
    PciSegmentWrite8 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.IoBase), HrConfigs[i].Res.IoBase);
    PciSegmentWrite8 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.IoLimit), HrConfigs[i].Res.IoLimit);
    PciSegmentWrite32 (gDeviceBaseAddress + OFFSET_OF (PCI_TYPE01, Bridge.IoBaseUpper16), 0x00000000);
    PciSegmentWrite8 (gDeviceBaseAddress + PCI_COMMAND_OFFSET, HrConfigs[i].Res.Cmd);
  }
  if (Hr_Config->DeviceId == AR_HR_2C || Hr_Config->DeviceId == AR_HR_4C || Hr_Config->DeviceId == AR_HR_LP) {
    for (i = 0; i < Hr_Config->BridgeLoops; ++i) {
      if(HrConfigs[i].IsDSBridge) {
        UnsetVesc(HrConfigs[i].DevId.Bus, HrConfigs[i].DevId.Dev, HrConfigs[i].DevId.Fun);
      }
    }
  }

  gDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (TbtSegment,(Hr_Config->HRBus + 2), 0x00, 0x00, 0);
  PciSegmentWrite32 (gDeviceBaseAddress + PCI_BASE_ADDRESSREG_OFFSET + (PCI_BAR_IDX0 * 4), HrConfigs[HR_DS_PORT0].Res.MemLimit << 16);
  PciSegmentWrite32 (gDeviceBaseAddress + PCI_BASE_ADDRESSREG_OFFSET + (PCI_BAR_IDX1 * 4), (HrConfigs[HR_DS_PORT0].Res.MemLimit + 0x4) << 16);
  PciSegmentWrite8 (gDeviceBaseAddress + PCI_CACHELINE_SIZE_OFFSET, DEF_CACHE_LINE_SIZE);
  PciSegmentWrite8 (gDeviceBaseAddress + PCI_COMMAND_OFFSET, CMD_BM_MEM);
  return Ret;
} // InitializeHostRouter

VOID
DTbtCallback (
  VOID
  )
{
  PORT_INFO                     PortInfoOrg;
  HR_CONFIG                     HrConfig;
  UINT8                         i;
  UINTN                         Segment = 0;
  UINTN                         Bus = 0;
  UINTN                         Device;
  UINTN                         Function;

  ZeroMem (&PortInfoOrg, sizeof(PORT_INFO));
  ZeroMem (&HrConfig, sizeof(HR_CONFIG));

  DEBUG((DEBUG_INFO, "DThunderboltCallback.Entry\n"));

  DEBUG((DEBUG_INFO, "PortInfo Initialization\n"));
  PortInfoInit (&PortInfoOrg);
  if (gCurrentDiscreteTbtRootPort == 0) {
    DEBUG((DEBUG_ERROR, "Invalid RP Input\n"));
    return;
  }
  GetDTbtRpDevFun(gCurrentDiscreteTbtRootPortType, gCurrentDiscreteTbtRootPort - 1, &Device, &Function);
  DEBUG((DEBUG_INFO, "InitializeHostRouter. \n"));
  if (!InitializeHostRouter (&HrConfig, Segment, Bus, Device, Function)) {
    return ;
  }
  //
  // Configure DS ports
  //
  for (i = HrConfig.MinDSNumber; i <= HrConfig.MaxDSNumber; ++i) {
    DEBUG((DEBUG_INFO, "ConfigurePort. \n"));
    ConfigurePort (HrConfig.HRBus + 1, i,0, &PortInfoOrg);
  }

  DEBUG((DEBUG_INFO, "EndOfThunderboltCallback.\n"));
  EndOfThunderboltCallback (Segment, Bus, Device, Function);

  DEBUG((DEBUG_INFO, "DThunderboltCallback.Exit\n"));
} // ThunderboltCallback

VOID
DTbtDisablePCIDevicesAndBridges (
  VOID
  )
{
  UINTN         Segment = 0;
  UINTN         Bus = 0;
  UINTN         Device;
  UINTN         Function;
  UINT8         MinBus;
  UINT8         MaxBus;
  UINT16        DeviceId;

  MinBus = 1;
  //
  // for(Dev = 0; Dev < 8; ++Dev)
  // {
  // PciOr8(PCI_LIB_ADDRESS(2, Dev, 0, PCI_BRIDGE_CONTROL_REGISTER_OFFSET), 0x40);
  // gBS->Stall(2000);      // 2msec
  // PciAnd8(PCI_LIB_ADDRESS(2, Dev, 0, PCI_BRIDGE_CONTROL_REGISTER_OFFSET), 0xBF);
  // }
  // gBS->Stall(200 * 1000);        // 200 msec
  //
  if (gCurrentDiscreteTbtRootPort == 0) {
    DEBUG((DEBUG_ERROR, "Invalid RP Input\n"));
    return;
  }
  GetDTbtRpDevFun(gCurrentDiscreteTbtRootPortType, gCurrentDiscreteTbtRootPort - 1, &Device, &Function);
  gDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (Segment, Bus, Device, Function, 0);
  MinBus            = PciSegmentRead8 (gDeviceBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);
  MaxBus            = PciSegmentRead8 (gDeviceBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET);
  gDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (Segment, MinBus, 0x00, 0x00, 0);
  DeviceId          = PciSegmentRead16 (gDeviceBaseAddress + PCI_DEVICE_ID_OFFSET);
  if (!(IsTbtHostRouter (DeviceId))) {
    return;
  }
  TbtSegment = (UINT8)Segment;
  MinBus++;
  //
  // @todo : Move this out when we dont have Loop for ITBT
  //
  DisablePCIDevicesAndBridges(MinBus, MaxBus);

} // DTbtDisablePCIDevicesAndBridges


