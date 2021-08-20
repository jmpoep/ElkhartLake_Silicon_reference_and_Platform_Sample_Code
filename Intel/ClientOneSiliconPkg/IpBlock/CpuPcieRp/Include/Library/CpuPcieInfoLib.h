/** @file
  Header file for CpuPcieInfoLib.

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
#ifndef _CPU_PCIE_INFO_LIB_H_
#define _CPU_PCIE_INFO_LIB_H_

#define CPU_PCIE_MAX_ROOT_PORTS       4
#define CPU_PCIE_MAX_CONTROLLERS      3

#define CPU_PCIE_CLKREQMSGTXVLMDESTID  0xBB
#define CPU_PCIE_CLKREQMSGRXVLMI       0x2B
#define CPU_PCIE_CLKREQMSGTXVLMI1      0x27
#define CPU_PCIE_CLKREQMSGTXVLMI0      0x26
#define CPU_PCIE_GDR_LDVWMIDX          0x40

#define TIGERLAKE_ULT_ULX_MAX_ROOT_PORT     1
#define TIGERLAKE_DT_HALO_MAX_ROOT_PORT     4
#define TIGERLAKE_ULT_ULX_MAX_CONTROLLER    1
#define TIGERLAKE_DT_HALO_MAX_CONTROLLER    3

#define TIGERLAKE_CPU_PCIE_CONTROLLER0      0
#define TIGERLAKE_CPU_PCIE_CONTROLLER1      1
#define TIGERLAKE_CPU_PCIE_CONTROLLER2      2

#define TIGERLAKE_CPU_PCIE_x4_MAX_LANES     4
#define TIGERLAKE_CPU_PCIE_x16_MAX_LANES    16

#define LANE_MULTIPLIER                     0x1000

/**
  Get CPU Maximum Pcie Root Port Number

  @retval PcieMaxRootPort         Pch Maximum Pcie Root Port Number
**/
UINT8
GetMaxCpuPciePortNum (
  VOID
  );

/**
  Get CPU Maximum Pcie Controller Number

  @retval Pch Maximum Pcie Controller Number
**/
UINT8
GetMaxCpuPcieControllerNum (
  VOID
  );

/**
  Get CPU Maximum Pcie Clock Number

  @retval Pch Maximum Pcie Clock Number
**/
UINT8
GetMaxCpuPcieClockNum (
  VOID
  );

/**
  Get CPU Pcie Controller Number from Root Port Number

  @retval Sa Pcie Controller Number
**/
UINT8
GetCpuPcieControllerNum (
  IN     UINT32        RpIndex
  );

/**
  Returns the PCIe controller configuration (1x16, 1x8-2x4, 2x8, 1x4)

  @param[in] ControllerIndex        Number of PCIe controller (0 based)

  @retval PCIe controller configuration
**/
UINT8
GetCpuPcieControllerConfig (
  IN     UINT32        ControllerIndex
  );

/**
  Get Maximum CPU Pcie Root Port Number

  @retval Maximum CPU Pcie Root Port Number
**/
UINT8
GetMaxCpuPciePortNum (
  VOID
  );

#endif // _CPU_PCIE_INFO_LIB_H_
