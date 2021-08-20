/** @file
 OEM Specific Setup Variables and Structures

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

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

#ifndef _OEMSETUP_H_
#define _OEMSETUP_H_

#include <PchLimits.h>
#include <Register/CpuPcieRegs.h>
#include <CpuPcieInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

// OS profile
#define OS_PROFILE_GUID \
 { 0xE59376D7, 0x2DD9, 0x42A3, { 0x9E, 0xC8, 0x1D, 0x71, 0xD5, 0xE3, 0xC1, 0xEC }}

// Currently enumerated OSes
#define OsNone                   0x00
#define OsAndroid                0x01
#define OsWinCs                  0x02
#define OsWinNonCs               0x03
#define OsMax                    0x04

//
// From PchInfoLib.h
//
#define SKL_PCH                 1
#define KBL_PCH                 2
#define CNL_PCH                 3
#define ICL_PCH                 4
#define PCH_UNKNOWN_GENERATION  0xFF

#define PCH_MOBILE_SKU          0
#define PCH_DESKTOP_SKU         1
#define PCH_SERVER_SKU          2

#define PCH_RP_AVAILABLE       0
#define PCH_RP_FUSED_OFF       1
#define PCH_RP_MERGED          2
#define PCH_RP_DIFFERENT_BUS   3
#define PCH_RP_ETHERNET        4
#define PCH_RP_NOT_IMPLEMENTED 5

#define CPU_PCIE_RP_AVAILABLE       0
#define CPU_PCIE_RP_FUSED_OFF       1
#define CPU_PCIE_RP_NOT_IMPLEMENTED 3

#define PCH_FIA_ORM_NOT_SUPPORTED   0
#define PCH_FIA_ORM_SUPPORTED       1

#define PCH_PSE_TSN_GBE0_COM1_FIALANE  7
#define PCH_PSE_TSN_GBE1_COM1_FIALANE  9
#define PCH_PSE_TSN_GBE1_COM3_FIALANE  11
#define PCH_TSN_GBE_COM1_FIALANE       8
#define PCH_TSN_GBE_COM3_FIALANE       10

#pragma pack(1)

/**
 Making any setup structure change after code frozen
 will need to maintain backward compatibility, bump up
 structure revision and update below history table\n
     Revision 1:      - Initial version.
  <b>Revision 2</b>:  - Remove Item EnableDebugSerialIoUartNumber
**/

#define SETUP_VOLATILE_DATA_REVISION 2

typedef struct _SETUP_VOLATILE_DATA
{
  UINT16 FabId;
  UINT16 BoardBomId;
  UINT16 PlatId;
  UINT8  PlatformFlavor;
  UINT8  PlatformType;
  UINT8  BoardType;
  UINT8  VTdAvailable;
  UINT8  PchGeneration;
  UINT8  GbeSupportByPch;            // Gbe is supported on current PCH
  UINT8  GbeAvailable;               // Gbe is configured and usable
  UINT8  ThcSupported;
  UINT8  ThcAvailable;
  UINT8  DimmPresent[4];
  UINT8  PciePortCfg[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8  PchUsb2PortCount;
  UINT8  PchUsb3PortCount;
  UINT8  CpuPciePortCfg[CPU_PCIE_MAX_ROOT_PORTS];
  UINT8  EmmcSupported;
  UINT8  SdCardSupported;
  UINT8  UfsSupported[PCH_MAX_UFS_DEV_NUM];
  UINT32 AcpiDebugAddress;
  UINT8  PegPresent[4];
  UINT8  RstAvailable;
  UINT8  RsteAvailable;
  UINT8  SataMpsPresent[8];
  UINT8  DockAttached;
  UINT8  PcieStorageMap[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8  PcieStorageProgrammingInterface[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8  CycleRouterMap[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8  AudioHdaLinkSupported;
  UINT8  AudioDmicLinkSupported[PCH_MAX_HDA_DMIC_LINK_NUM];
  UINT8  AudioSspLinkSupported[PCH_MAX_HDA_SSP_LINK_NUM];
  UINT8  AudioSndwLinkSupported[PCH_MAX_HDA_SNDW_LINK_NUM];
  UINT8  PchCridSupport;
  UINT8  IpuSupport;
  UINT8  TbtVtdBaseSecurityGrayOut;
  UINT8  CdClockSelector;
  UINT8  TsnSupportByPch;
  UINT8  TsnAvailable;
  UINT8  TsnGbeLaneEnabled[PCH_MAX_TSN_GBE_CONTROLLERS]; // See TSN_GBE_HSIO_LANE_INDEX
  UINT8  TsnGbeLaneNum[PCH_MAX_TSN_GBE_CONTROLLERS];     // See TSN_GBE_HSIO_LANE_INDEX
  UINT8  FiaConnectorOrmSupported[PCH_MAX_FIA_ORM_CONNECTOR];
} SETUP_VOLATILE_DATA;

/**
 Making any setup structure change after code frozen
 will need to maintain backward compatibility, bump up
 structure revision and update below history table\n
  <b>Revision 1</b>:  - Initial version.
**/

#define SETUP_CPU_FEATURES_REVISION 1

//This structure is used for setup.
typedef struct {
  UINT8 XDBitAvailable;
  UINT8 TurboModeAvailable;
  UINT8 XETdcTdpLimitAvailable;
  UINT8 CoreRatioLimitAvailable;
  UINT8 HTAvailable;
  UINT8 MultiCoreAvailable;
  UINT8 VTAvailable;
  UINT8 AESAvailable;
  UINT8 TXTAvailable;
  UINT8 CxAvailable;
  UINT8 C1Available;
  UINT8 C1EAvailable;
  UINT8 C3Available;
  UINT8 C6Available;
  UINT8 C7Available;
  UINT8 C8Available;
  UINT8 C9Available;
  UINT8 C10Available;
  UINT8 EISTAvailable;
  UINT8 HwpAvailable;
  UINT8 ItbmAvailable;
  UINT8 NumCores;
  UINT8 MultiSocketAvailable;
  UINT8 MultiSocketPopulated;
  UINT8 LocalX2ApicAvailable;
  UINT8 EnergyEfficientTurboAvailable;
  UINT8 SgxSupported;
  UINT8 C6DramSupported;
  UINT8 ApicIdFlag;
  UINT8 ConfigTdpAvailable;
  UINT8 PpinFeatureAvailable;
  UINT8 LpmAvailable;
  UINT8 TimedMwaitSupported;
  UINT8 DebugInterfaceSupported;
  UINT8 ProcTraceSupported;
  UINT8 SmmEnhancementSupported;
  UINT8 SmmTargetedSmiAvailable;
  UINT8 SmmCpuSvrstrAvailable;
  UINT8 SmmLongFlowAvailable;
  UINT8 HdcSupported;
  UINT8 HwpInterruptSupported;
  UINT8 CtdpDownSupported;
  UINT8 CtdpUpSupported;
  UINT8 FivrSupported;
  UINT8 FclkSupported;
} SETUP_CPU_FEATURES;

typedef struct {
  UINT8   OsProfile;
  UINT8   PrevOs;
} OS_PROFILE;

#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
