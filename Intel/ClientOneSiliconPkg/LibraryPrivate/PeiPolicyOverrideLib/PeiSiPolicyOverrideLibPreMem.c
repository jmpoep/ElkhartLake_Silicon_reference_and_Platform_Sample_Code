/** @file
  Provide polciy override functions in PreMem to enable specific silicon feature.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PeiSiPolicyOverrideLib.h>
#include <Library/PsmiInitLib.h>

/**
  Override policies relevant to PlatformDebugConsent to enable debug in PreMem.

  @param[in] SiPreMemPolicyPpi         The Silicon PreMem Policy PPI instance
**/
STATIC
VOID
PlatformDebugConsentEnablePreMem (
  IN  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                           Status;
  SI_PREMEM_CONFIG                     *SiPreMemConfig;
  PCH_DCI_PREMEM_CONFIG                *DciPreMemConfig;
  CPU_TRACE_HUB_PREMEM_CONFIG          *CpuTraceHubPreMemConfig;
  PCH_TRACE_HUB_PREMEM_CONFIG          *PchTraceHubPreMemConfig;

  SiPreMemConfig                     = NULL;
  DciPreMemConfig                    = NULL;
  CpuTraceHubPreMemConfig            = NULL;
  PchTraceHubPreMemConfig            = NULL;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSiPreMemConfigGuid, (VOID *) &SiPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gDciPreMemConfigGuid, (VOID *) &DciPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuTraceHubPreMemConfigGuid, (VOID *) &CpuTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPchTraceHubPreMemConfigGuid, (VOID *) &PchTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  //
  // skip policy override for manual
  //
  if (SiPreMemConfig->PlatformDebugConsent == ProbeTypeManual) {
    DEBUG ((DEBUG_INFO, "PlatformDeugConsent is Manual, DO NOT override policy!!!\n"));
    return;
  }
  //
  // Common settings for PDC enabled/disabled
  //
  CpuTraceHubPreMemConfig->TraceHub.MemReg0Size = TraceBuffer8M;
  CpuTraceHubPreMemConfig->TraceHub.MemReg1Size = TraceBuffer8M;
  PchTraceHubPreMemConfig->TraceHub.MemReg0Size = TraceBuffer8M;
  PchTraceHubPreMemConfig->TraceHub.MemReg1Size = TraceBuffer8M;
  //
  // Common settings for PDC enabled
  //
  DciPreMemConfig->DciEn                             = TRUE;
  DciPreMemConfig->DciModphyPg                       = TRUE;
  DciPreMemConfig->DciDbcMode                        = DciDbcNoChange;
  CpuTraceHubPreMemConfig->TraceHub.EnableMode       = TraceHubModeHostDebugger;
  PchTraceHubPreMemConfig->TraceHub.EnableMode       = TraceHubModeHostDebugger;

  switch (SiPreMemConfig->PlatformDebugConsent) {
    case ProbeTypeDisabled:
      DciPreMemConfig->DciEn                         = FALSE;
      CpuTraceHubPreMemConfig->TraceHub.EnableMode   = TraceHubModeDisabled;
      PchTraceHubPreMemConfig->TraceHub.EnableMode   = TraceHubModeDisabled;
      break;

    case ProbeTypeUsb2Dbc:
      DciPreMemConfig->DciDbcMode                    = DciDbcBoth;
      break;

    case ProbeTypeUsb3Dbc:
      DciPreMemConfig->DciDbcMode                    = DciDbcUsb3;
      break;

    case ProbeType2WireDciOob:
      CpuTraceHubPreMemConfig->TraceHub.EnableMode   = TraceHubModeDisabled;
      PchTraceHubPreMemConfig->TraceHub.EnableMode   = TraceHubModeDisabled;
      break;

    case ProbeTypeDciOob:
      DciPreMemConfig->DciModphyPg                   = FALSE;
      break;

    default:
      break;
  }
  DEBUG ((DEBUG_INFO, "SiPreMemConfig->PlatformDebugConsent = %x\n", SiPreMemConfig->PlatformDebugConsent));
  DEBUG ((DEBUG_INFO, "DciPreMemConfig->DciEn = %x\n", DciPreMemConfig->DciEn));
  DEBUG ((DEBUG_INFO, "DciPreMemConfig->DciModphyPg = %x\n", DciPreMemConfig->DciModphyPg));
  DEBUG ((DEBUG_INFO, "DciPreMemConfig->DciDbcMode = %x\n", DciPreMemConfig->DciDbcMode));
  DEBUG ((DEBUG_INFO, "CpuTraceHubPreMemConfig->TraceHub.EnableMode = %x\n",  CpuTraceHubPreMemConfig->TraceHub.EnableMode));
  DEBUG ((DEBUG_INFO, "CpuTraceHubPreMemConfig->TraceHub.MemReg0Size = %x\n", CpuTraceHubPreMemConfig->TraceHub.MemReg0Size));
  DEBUG ((DEBUG_INFO, "CpuTraceHubPreMemConfig->TraceHub.MemReg1Size = %x\n", CpuTraceHubPreMemConfig->TraceHub.MemReg1Size));
  DEBUG ((DEBUG_INFO, "PchTraceHubPreMemConfig->TraceHub.EnableMode = %x\n",  PchTraceHubPreMemConfig->TraceHub.EnableMode));
  DEBUG ((DEBUG_INFO, "PchTraceHubPreMemConfig->TraceHub.MemReg0Size = %x\n", PchTraceHubPreMemConfig->TraceHub.MemReg0Size));
  DEBUG ((DEBUG_INFO, "PchTraceHubPreMemConfig->TraceHub.MemReg1Size = %x\n", PchTraceHubPreMemConfig->TraceHub.MemReg1Size));
}


/**
  Policy override in PreMem phase

  @param[in] SiPreMemPolicyPpi         The Silicon PreMem Policy PPI instance
**/
VOID
PeiSiPolicyOverridePreMem (
  IN  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi
  )
{
  DEBUG ((DEBUG_INFO, "PeiSiPolicyOverridePreMem ()\n"));
  PlatformDebugConsentEnablePreMem (SiPreMemPolicyPpi);
  PsmiTraceHubPolicyOverride (SiPreMemPolicyPpi);
}