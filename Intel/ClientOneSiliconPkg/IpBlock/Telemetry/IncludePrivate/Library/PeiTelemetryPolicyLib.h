/** @file
  Header file for PeiTelemetryPolicyLib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#ifndef TELEMETRY_PEI_PRIVATE_LIB_H_
#define TELEMETRY_PEI_PRIVATE_LIB_H_

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
TelemetryLoadPeiConfigDefault (
  IN VOID   *ConfigBlockPointer
  );

/**
  Get Telemetry PEI config block table total size.

  @retval     Size of Telemetry PEI config block table
**/
UINT16
EFIAPI
TelemetryGetPeiConfigBlockTotalSize (
  VOID
  );

/**
  TelemetryAddConfigBlocks add all Telemetry PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add Ip config block

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
TelemetryAddPeiConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  );

/**
  This function prints the Telemetry PEI phase policy.

  @param[in] SiPolicyPpi - Instance of SI_POLICY_PPI
**/
VOID
EFIAPI
TelemetryPrintPeiPolicyPpi (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  );

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
TelemetryLoadPeiConfigPreMemDefault (
  IN VOID   *ConfigBlockPointer
  );

/**
  Get Telemetry PEI PreMem config block table total size.

  @retval     Size of Telemetry PEI PreMem config block table
**/
UINT16
EFIAPI
TelemetryGetPeiConfigBlockTotalSizePreMem (
  VOID
  );

/**
  TelemetryAddPeiConfigBlockPreMem add all Telemetry PreMem PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add Ip config block

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
TelemetryAddPeiConfigBlockPreMem (
  IN VOID           *ConfigBlockTableAddress
  );
/**
  This function prints the Telemetry PreMem PEI phase policy.

  @param[in] SiPreMemPolicyPpi    Pointer to a SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
TelemetryPrintPeiPolicyPpiPreMem (
  IN SI_PREMEM_POLICY_PPI     *SiPreMemPolicyPpi
  );
#endif
