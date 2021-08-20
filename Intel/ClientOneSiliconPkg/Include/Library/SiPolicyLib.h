/** @file
  Prototype of the SiPolicyLib library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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
#ifndef _SI_POLICY_LIB_H_
#define _SI_POLICY_LIB_H_

#include <Ppi/SiPolicy.h>

#if FixedPcdGet8(PcdFspModeSelection) == 1
//
// MACROS for platform code use
//
#define UPDATE_POLICY(UpdField, ConfigField, Value)  UpdField = Value;
#define COPY_POLICY(UpdField, ConfigField, Value, Size)  CopyMem (UpdField, Value, Size);
#define GET_POLICY(UpdField, ConfigField, Value)  Value = UpdField;
#define AND_POLICY(UpdField, ConfigField, Value)  UpdField &= Value;
#define OR_POLICY(UpdField, ConfigField, Value)  UpdField |= Value;
#else
#define UPDATE_POLICY(UpdField, ConfigField, Value)  ConfigField = Value;
#define COPY_POLICY(UpdField, ConfigField, Value, Size)  CopyMem (ConfigField, Value, Size);
#define GET_POLICY(UpdField, ConfigField, Value)  Value = ConfigField;
#define AND_POLICY(UpdField, ConfigField, Value)  ConfigField &= Value;
#define OR_POLICY(UpdField, ConfigField, Value)  ConfigField |= Value;
#endif

/**
  Print whole SI_PREMEM_POLICY_PPI and serial out.

  @param[in] SiPreMemPolicyPpi          The RC PREMEM Policy PPI instance
**/
VOID
EFIAPI
SiPreMemPrintPolicyPpi (
  IN  SI_PREMEM_POLICY_PPI          *SiPreMemPolicyPpi
  );

/**
  Print whole SI_POLICY_PPI and serial out.

  @param[in] SiPolicyPpi          The RC Policy PPI instance
**/
VOID
EFIAPI
SiPrintPolicyPpi (
  IN  SI_POLICY_PPI          *SiPolicyPpi
  );

/**
  SiCreatePreMemConfigBlocks creates the config blocksg of Silicon Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[out] SiPreMemPolicyPpi   The pointer to get Silicon PREMEM Policy PPI instance

  @retval EFI_SUCCESS             The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiCreatePreMemConfigBlocks (
  OUT  SI_PREMEM_POLICY_PPI         **SiPreMemPolicyPpi
  );

/**
  SiCreateConfigBlocks creates the config blocksg of Silicon Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[out] SiPolicyPpi         The pointer to get Silicon Policy PPI instance

  @retval EFI_SUCCESS             The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiCreateConfigBlocks (
  OUT  SI_POLICY_PPI         **SiPolicyPpi
  );

/**
  SiPreMemInstallPolicyPpi installs SiPreMemPolicyPpi.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] SiPreMemPolicyPpi   The pointer to Silicon PREMEM Policy PPI instance

  @retval EFI_SUCCESS            The policy is installed.
  @retval EFI_OUT_OF_RESOURCES   Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiPreMemInstallPolicyPpi (
  IN  SI_PREMEM_POLICY_PPI          *SiPreMemPolicyPpi
  );

/**
  SiPreMemInstallPolicyReadyPpi installs SiPreMemPolicyReadyPpi.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @retval EFI_SUCCESS            The policy is installed.
  @retval EFI_OUT_OF_RESOURCES   Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiPreMemInstallPolicyReadyPpi (
  VOID
  );

/**
  SiInstallPolicyPpi installs SiPolicyPpi.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] SiPolicyPpi         The pointer to Silicon Policy PPI instance

  @retval EFI_SUCCESS            The policy is installed.
  @retval EFI_OUT_OF_RESOURCES   Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiInstallPolicyPpi (
  IN  SI_POLICY_PPI          *SiPolicyPpi
  );

/**
  SiInstallPolicyReadyPpi installs SiPolicyReadyPpi.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @retval EFI_SUCCESS            The policy is installed.
  @retval EFI_OUT_OF_RESOURCES   Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SiInstallPolicyReadyPpi (
  VOID
  );

/**
  Print out all silicon policy information.

  @param[in] SiPolicyPpi         The pointer to Silicon Policy PPI instance

  @retval none
**/
VOID
DumpSiPolicy (
  IN  SI_POLICY_PPI *SiPolicyPpi
  );

/**
  Calculate total trace buffer size and make it power of two, eliminate the total size within 512MB
  Please ensure CPU and PCH trace hub policies are configured before calling.

  @param[in] PlatformDebugConsent            Platform Debug Consent
  @param[in] CpuTraceHubMode                 CPU Trace Hub Mode
  @param[in] CpuTraceHubMemReg0Size          CPU Trace Hub Memory Region 0
  @param[in] CpuTraceHubMemReg1Size          CPU Trace Hub Memory Region 1
  @param[in] PchTraceHubMode                 PCH Trace Hub Mode
  @param[in] PchTraceHubMemReg0Size          PCH Trace Hub Memory Region 0
  @param[in] PchTraceHubMemReg1Size          PCH Trace Hub Memory Region 1

  @retval UINT32                             Total size of trace buffers
**/
UINT32
EFIAPI
TraceHubCalculateTotalBufferSize (
  IN UINT8         PlatformDebugConsent,
  IN UINT8         CpuTraceHubMode,
  IN UINT8         CpuTraceHubMemReg0Size,
  IN UINT8         CpuTraceHubMemReg1Size,
  IN UINT8         PchTraceHubMode,
  IN UINT8         PchTraceHubMemReg0Size,
  IN UINT8         PchTraceHubMemReg1Size
  );
#endif // _SI_POLICY_LIB_H_
