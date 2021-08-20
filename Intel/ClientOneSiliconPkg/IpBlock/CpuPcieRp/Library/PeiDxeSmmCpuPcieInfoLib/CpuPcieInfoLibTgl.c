/** @file
  CPU PCIe information library for TGL.

  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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
#include <Uefi/UefiBaseType.h>
#include <Library/CpuPlatformLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <Register/CpuPcieRegs.h>
#include <Library/CpuPcieInfoLib.h>
#include <CpuPcieInfo.h>
#include <Library/CpuPcieExpressHelpersLib.h>

/**
  PCIe controller configuration strings.
**/
GLOBAL_REMOVE_IF_UNREFERENCED CONST CHAR8* mCpuPcieControllerConfigName[] = {
  "1x16",
  "1x8-2x4",
  "2x8",
  "1x4"
};

/**
  Returns the PCIe controller configuration (1x16, 1x8-2x4, 2x8, 1x4)

  @param[in] ControllerIndex        Number of PCIe controller (0 based)

  @retval PCIe controller configuration
**/
UINT8
GetCpuPcieControllerConfig (
  IN     UINT32        ControllerIndex
  )
{
  UINT32                     Data32;
  UINT8                      Config;
  CONST CHAR8*               ControllerName;

  Config = CPU_PCIE_1x16; // set x16 as default config
  Data32 = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, SA_PEG0_FUN_NUM, R_PCIE_STRPFUSECFG));
  Config = (UINT8)((Data32 & B_PCIE_STRPFUSECFG_RPC_MASK) >> B_PCIE_STRPFUSECFG_RPC_OFFSET);
  switch (Config) {
    case CPU_PCIE_1x16 :
      ControllerName = mCpuPcieControllerConfigName[0];
      break;
    case CPU_PCIE_1x8_2x4 :
      ControllerName = mCpuPcieControllerConfigName[1];
      break;
    case CPU_PCIE_2x8 :
     ControllerName = mCpuPcieControllerConfigName[2];
     break;
    case CPU_PCIE_1x4 :
      ControllerName = mCpuPcieControllerConfigName[3];
     break;
    default:
      ControllerName = mCpuPcieControllerConfigName[3];
      break;
  }
  DEBUG((DEBUG_INFO, "CPU PCIe Furcation is %a\n", ControllerName));
  return Config;
}

/**
  Get Maximum CPU Pcie Root Port Number

  @retval Maximum CPU Pcie Root Port Number
**/
UINT8
GetMaxCpuPciePortNum (
  VOID
  )
{
  switch (GetCpuFamily()) {
    case EnumCpuTglUltUlx:
      return TIGERLAKE_ULT_ULX_MAX_ROOT_PORT;
    case EnumCpuTglDtHalo:
      return TIGERLAKE_DT_HALO_MAX_ROOT_PORT;
    default:
      return TIGERLAKE_ULT_ULX_MAX_ROOT_PORT;
  }
}

/**
  Get Maximum CPU Pcie Controller Number

  @retval Maximum CPU Pcie Controller Number
**/
UINT8
GetMaxCpuPcieControllerNum (
  VOID
  )
{
  switch (GetCpuFamily()) {
    case EnumCpuTglUltUlx:
      return TIGERLAKE_ULT_ULX_MAX_CONTROLLER;
    case EnumCpuTglDtHalo:
      return TIGERLAKE_DT_HALO_MAX_CONTROLLER;
    default:
      return TIGERLAKE_ULT_ULX_MAX_CONTROLLER;
  }
}

/**
  Get CPU Pcie Controller Number from Root Port Number

  @retval CPU Pcie Controller Number
**/
UINT8
GetCpuPcieControllerNum (
  IN     UINT32        RpIndex
  )
{
  switch (RpIndex) {
    case 0:
      return TIGERLAKE_CPU_PCIE_CONTROLLER0;
    case 1:
      return TIGERLAKE_CPU_PCIE_CONTROLLER1;
    case 2:
    case 3:
      return TIGERLAKE_CPU_PCIE_CONTROLLER2;
    default:
      return TIGERLAKE_CPU_PCIE_CONTROLLER0;
  }
}
