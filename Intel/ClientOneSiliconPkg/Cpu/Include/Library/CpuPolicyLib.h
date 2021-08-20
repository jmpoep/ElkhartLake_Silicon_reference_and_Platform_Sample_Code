/** @file
  Prototype of the CpuPolicy library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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

@par Specification
**/
#ifndef _CPU_POLICY_LIB_H_
#define _CPU_POLICY_LIB_H_

#include <Ppi/SiPolicy.h>

#pragma pack(push,1)

typedef struct {
  UINT8       *VrConfigEnable;
  UINT8       *TdcEnable;
  UINT8       *TdcTimeWindow;
  UINT16      *TdcCurrentLimit;
  UINT16      *AcLoadline;
  UINT16      *DcLoadline;
  UINT16      *Psi1Threshold;
  UINT16      *Psi2Threshold;
  UINT16      *Psi3Threshold;
  UINT8       *Psi3Enable;
  UINT8       *Psi4Enable;
  UINT16      *IccMax;
} CPU_POWER_MGMT_VR_DATA;

typedef struct {
  EFI_GUID                     Name;
  UINT16                       HobLength;
  CPU_POWER_MGMT_VR_DATA       *CpuPowerMgmtVrData;
} CPU_POWER_MGMT_VR_CONFIG_EX;

#pragma pack(pop)

/**
  External call for loading Config block default

  @param[in/out] CpuPowerMgmtVrConfigEx   Pointer to CPU_POWER_MGMT_VR_CONFIG_EX array.

  @retval EFI_SUCCESS                     The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES            Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
LoadCpuPowerMgmtVrConfigDefaultEx (
  IN OUT  CPU_POWER_MGMT_VR_CONFIG_EX     *CpuPowerMgmtVrConfigEx
  );

/**
  Print whole CPU related config blocks of SI_PREMEM_POLICY_PPI and serial out.

  @param[in] SiPreMemPolicyPpi             The Si PreMem Policy PPI instance
**/
VOID
CpuPreMemPrintPolicy (
  IN  SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi
  );

/**
  Get CPU PREMEM config block table total size.

  @retval Size of CPU PREMEM config block table
**/
UINT16
EFIAPI
CpuGetPreMemConfigBlockTotalSize (
  VOID
  );

/**
  CpuAddPreMemConfigBlocks add all CPU PREMEM config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add CPU PREMEM config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
CpuAddPreMemConfigBlocks (
  IN     VOID      *ConfigBlockTableAddress
  );

/**
  Print whole CPU config blocks of SiPolicyPpi and serial out.

  @param[in] SiPolicyPpi             The SI Policy PPI instance
**/
VOID
CpuPrintPolicy (
  IN  SI_POLICY_PPI                 *SiPolicyPpi
  );

/**
  Get CPU config block table total size.

  @retval Size of CPU config block table
**/
UINT16
EFIAPI
CpuGetConfigBlockTotalSize (
  VOID
  );

/**
  CpuAddConfigBlocks add all Cpu config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add CPU config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
CpuAddConfigBlocks (
  IN     VOID      *ConfigBlockTableAddress
  );

#endif // _PEI_CPU_POLICY_LIB_H_
