/** @file
Header file for CpuPcieInitCommonLib.

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
#ifndef _CPU_PCIE_INIT_COMMON_H_
#define _CPU_PCIE_INIT_COMMON_H_

#include <Library/CpuRegbarAccessLib.h>

/**
  This function returns PID according to PCIe controller index

  @param[in] ControllerIndex     PCIe controller index

  @retval CPU_SB_DEVICE_PID    Returns PID for SBI Access
**/
CPU_SB_DEVICE_PID
GetCpuPcieControllerSbiPid (
  IN  UINT32  ControllerIndex
  );

/**
  This function returns PID according to Root Port Number

  @param[in] RpIndex     Root Port Index (0-based)

  @retval CPU_SB_DEVICE_PID    Returns PID for SBI Access
**/
CPU_SB_DEVICE_PID
GetCpuPcieRpSbiPid (
  IN  UINTN  RpIndex
  );

/**
  This function reads PCI Config register via SBI Access or through IOM mailbox

  @param[in]  RpIndex             Root Port Index (0-based)
  @param[in]  Offset              Offset of Config register
  @param[out] *Data32             Value of Config register

  @retval EFI_SUCCESS             SBI Read successful.
**/
EFI_STATUS
CpuPcieRpSbiRead32 (
  IN    UINT32  RpIndex,
  IN    UINT32  Offset,
  OUT   UINT32  *Data32
  );

/**
  This function And then Or Pci Config register via SBI Access

  @param[in]  RpIndex             Root Port Index (0-based)
  @param[in]  Offset              Offset of Config register
  @param[in]  Data32And           Value of Config register to be And-ed
  @param[in]  Data32AOr           Value of Config register to be Or-ed

  @retval EFI_SUCCESS             SBI Read and Write successful.
**/
EFI_STATUS
CpuPcieRpSbiAndThenOr32 (
  IN  UINT32  RpIndex,
  IN  UINT32  Offset,
  IN  UINT32  Data32And,
  IN  UINT32  Data32Or
  );

/**
  Print registers value

  @param[in] PrintMmioBase       Mmio base address
  @param[in] PrintSize           Number of registers
  @param[in] OffsetFromBase      Offset from mmio base address

  @retval None
**/
VOID
SaPrintRegisters (
  IN  UINTN        PrintMmioBase,
  IN  UINT32       PrintSize,
  IN  UINT32       OffsetFromBase
  );

/**
  Print registers value

  @param[in] PrintPciSegmentBase Pci segment base address
  @param[in] PrintSize           Number of registers
  @param[in] OffsetFromBase      Offset from mmio base address

  @retval None
**/
VOID
SaPrintPciRegisters (
  IN  UINT64       PrintPciSegmentBase,
  IN  UINT32       PrintSize,
  IN  UINT32       OffsetFromBase
  );

#endif // _CPU_PCIE_INIT_COMMON_H_
