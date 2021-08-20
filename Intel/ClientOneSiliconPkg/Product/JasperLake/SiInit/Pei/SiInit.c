/** @file
    Source code file for Silicon Init Post Memory module.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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

#include "SiInit.h"
#include <Library/PerformanceLib.h>
#include <Library/PeiP2sbPrivateLib.h>
#include <Library/PeiSiPolicyOverrideLib.h>
#include <Library/PostCodeLib.h>
#include <Library/IpuInitLib.h>
#include <Library/CpuTraceHubInfoLib.h>
#include <Library/PchTraceHubInfoLib.h>
#include <Library/PeiSiSsidLib.h>
#include <Library/PeiHdaInitLib.h>

#include <Register/IgdRegs.h>


#ifdef FSP_FLAG
#include <Library/FspCommonLib.h>
#endif

EFI_PEI_PPI_DESCRIPTOR mEndOfSiInit = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEndOfSiInitPpiGuid,
  NULL
};

#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_NOTIFY_DESCRIPTOR  mSiInitNotifyList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEndOfSiInitPpiGuid,
    SiInitOnEndOfPei
  }
};
#else
GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_NOTIFY_DESCRIPTOR  mSiInitNotifyList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiEndOfPeiSignalPpiGuid,
    SiInitOnEndOfPei
  }
};
#endif

static EFI_PEI_NOTIFY_DESCRIPTOR  mSiInitPostMemNotifyList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gSiPolicyReadyPpiGuid,
    SiInitPostMemOnPolicy
  }
};

/**
  Silicon Init End of PEI callback function. This is the last change before entering DXE and OS when S3 resume.

  @param[in] PeiServices   - Pointer to PEI Services Table.
  @param[in] NotifyDesc    - Pointer to the descriptor for the Notification event that
                             caused this function to execute.
  @param[in] Ppi           - Pointer to the PPI data associated with this function.

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
EFI_STATUS
SiInitOnEndOfPei (
  IN EFI_PEI_SERVICES                   **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR          *NotifyDesc,
  IN VOID                               *Ppi
  )
{
  EFI_STATUS             Status;
  SI_POLICY_PPI          *SiPolicy;
  SI_CONFIG              *SiConfig;
  CPU_CONFIG             *CpuConfig;
  EFI_BOOT_MODE          BootMode;
  SI_PREMEM_POLICY_PPI   *SiPreMemPolicy;

  //
  // Get Policy settings through the SiPolicy PPI
  //
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicy
             );
  if (Status != EFI_SUCCESS) {
    ASSERT (FALSE);
    return EFI_SUCCESS;
  }

  //
  // Get Si PreMem Policy settings through the SiPreMemPolicy PPI
  //
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicy
             );
  if (Status != EFI_SUCCESS) {
    ASSERT (FALSE);
    return EFI_SUCCESS;
  }

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSiConfigGuid, (VOID *) &SiConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock((VOID *)SiPolicy, &gCpuConfigGuid, (VOID *)&CpuConfig);
  ASSERT_EFI_ERROR(Status);

  DEBUG ((DEBUG_INFO, "SiInitOnEndOfPei - Start\n"));

  //
  // Initializes PCH after End of Pei
  //
  PchOnEndOfPei ();
  //
  // Execute before P2SB lock to ensure hiding trace hub thru PSF is valid.
  //
  ConfigureMscForCpuAndPchTraceHub (SiConfig->TraceHubMemBase, (BOOLEAN) PchGeneralConfig->PchMasterPowerGating);
  //
  // Configure P2SB at the end of EndOfPei
  // This must be done before POSTBOOT_SAI programming.
  //
  P2sbLock (SiPolicy);
  if (CpuConfig->SkipMpInit == 0) {
    //
    // Set BIOS DONE MSR on all Cores
    //
    SetBiosDone ((CONST EFI_PEI_SERVICES **) PeiServices);
  }

  //
  // Do necessary PCH configuration just after POSTBOOT_SAI switch
  //
  PchDmiConfigAfterPostBootSai ();

  CpuInitAtEndOfPei ((CONST EFI_PEI_SERVICES **) PeiServices);

  //
  // Set BIOS_RESET_CPL to indicate BIOS initialization completed
  //
  PERF_START_EX (&gPerfSaResetPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4090);
  SaResetComplete ();
  PERF_END_EX (&gPerfSaResetPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4091);

  PERF_START_EX (&gPerfHdaPostMemGuid, NULL, NULL, AsmReadTsc (), 0x40D0);
  HdAudioInitOnEndOfPei (SiPolicy, SiPreMemPolicy);
  PERF_END_EX (&gPerfHdaPostMemGuid, NULL, NULL, AsmReadTsc (), 0x40D1);

  //
  // Initialize power management after RESET_CPL at post-memory phase.
  //
  if (CpuConfig->SkipMpInit == 0) {
    PERF_START_EX (&gPerfCpuPowerMgmtGuid, NULL, NULL, AsmReadTsc (), 0x40A0);
    CpuPowerMgmtInit ((CONST EFI_PEI_SERVICES **) PeiServices);
    PERF_END_EX (&gPerfCpuPowerMgmtGuid, NULL, NULL, AsmReadTsc (), 0x40A1);
  }

  MeOnEndOfPei ();
  SaOnEndOfPei ();

  //
  // Build FVI Info HOB in normal boot
  //
  Status = PeiServicesGetBootMode (&BootMode);
  if ((Status == EFI_SUCCESS) && (BootMode != BOOT_ON_S3_RESUME)) {
    BuildFviInfoHob ();
  }

  InitializeSmbiosCpuHobs ();

  DEBUG ((DEBUG_INFO, "SiInitOnEndOfPei - End\n"));
  return EFI_SUCCESS;
}

/**
  Get HybridGraphics subsystem ID.

  @retval  HybridGraphics subsystem ID
**/
STATIC
UINT16
GetHgSsid (
  VOID
  )
{
  EFI_STATUS                    Status;
  SI_PREMEM_POLICY_PPI          *SiPreMemPolicyPpi;
  HYBRID_GRAPHICS_CONFIG        *HgGpioData;
  UINT16                        HgSubSystemId;

  SiPreMemPolicyPpi = NULL;
  HgGpioData = NULL;
  HgSubSystemId = 0;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );

  if (!EFI_ERROR (Status) && (SiPreMemPolicyPpi != NULL)) {
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHybridGraphicsConfigGuid, (VOID *) &HgGpioData);
    if (HgGpioData != NULL) {
      HgSubSystemId = HgGpioData->HgSubSystemId;
    }
  }
  return HgSubSystemId;
}

/**
  Override HG SVID and SSID

  @param[in]      PciDevNum       Pci device number
  @param[in]      PciFuncNum      Pci function number
  @param[in,out]  Svid            Svid value
  @param[in,out]  Ssid            Ssid value

  @retval         TRUE            Silicon overrides the SSID
  @retval         FALSE           Silicon doesn't override the SSID
**/
STATIC
BOOLEAN
HgSsidOverride (
  UINT32                 PciDevNum,
  UINT32                 PciFuncNum,
  UINT16                 *Svid,
  UINT16                 *Ssid
  )
{
  UINT16    HgSsid;

  if ((PciDevNum == SA_IGD_DEV) && (PciFuncNum == SA_IGD_FUN_0)) {
    HgSsid = GetHgSsid ();
    if (HgSsid != 0) {
      *Ssid = HgSsid;
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Slicon Initializes after PostMem phase Policy PPI produced,
  All required polices must be installed before the callback

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  SiPolicy PPI.

  @retval EFI_SUCCESS             Succeeds.
  @retval EFI_UNSUPPORTED         The function failed to locate SiPolicy
**/
EFI_STATUS
EFIAPI
SiInitPostMemOnPolicy (
  IN  EFI_PEI_SERVICES             **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN  VOID                         *Ppi
  )
{
  SI_POLICY_PPI             *SiPolicy;
  SI_PREMEM_POLICY_PPI      *SiPreMemPolicyPpi;
  VOID                      *HobPtr;
  EFI_STATUS                Status;
  CPU_CONFIG                *CpuConfig;
  SI_CONFIG                 *SiConfig;
  DEBUG ((DEBUG_INFO, "SiInit () - Start\n"));

  SiPreMemPolicyPpi       = NULL;
  SiPolicy                = NULL;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPolicy
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gCpuConfigGuid, (VOID *) &CpuConfig);
  ASSERT_EFI_ERROR(Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSiConfigGuid, (VOID *) &SiConfig);
  ASSERT_EFI_ERROR(Status);

  //
  // Cross IP Policy override for specific feature enabling
  //
  PeiSiPolicyOverride (SiPreMemPolicyPpi, SiPolicy);

  HobPtr = BuildGuidDataHob (&gSiConfigHobGuid, SiConfig, sizeof (SI_CONFIG));
  ASSERT (HobPtr != 0);

  ///
  /// SubsystemID programming on Internal Devices.
  ///
  DEBUG ((DEBUG_INFO, "SubsystemID programming on Internal Devices\n"));
  SiProgramSsid (SiPolicy, HgSsidOverride);

  //
  // Perform ME post mem init
  // Call before PchInit to have MbpHob data ready.
  //
  PERF_START_EX (&gPerfMePostMemGuid, NULL, NULL, AsmReadTsc (), 0x40B0);
  MePostMemInit (SiPolicy);
  PERF_END_EX (&gPerfMePostMemGuid, NULL, NULL, AsmReadTsc (), 0x40B1);

  //
  // Initializes PCH after memory services initialized
  //
  PERF_START_EX (&gPerfPchPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4020);
  PchInit (SiPolicy);
  PERF_END_EX (&gPerfPchPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4021);

  //
  // SA Post Mem initialization
  //
  PERF_START_EX (&gPerfSaPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4030);
  SaInit ();
  PERF_END_EX (&gPerfSaPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4031);

  //
  //  IPU Initilization
  //
  DEBUG ((DEBUG_INFO, "Initializing IPU device\n"));
  PostCode (0xA14);
  IpuInit();


  //
  // Initialize processor features, performance and power management features,
  // BIOS GUARD, and overclocking etc features before RESET_CPL at post-memory phase.
  //
  PERF_START_EX (&gPerfCpuPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4080);
  CpuInit ((CONST EFI_PEI_SERVICES **) PeiServices, SiPolicy);
  PERF_END_EX (&gPerfCpuPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4081);

  //
  // Perform AMT post mem init
  //
  PERF_START_EX (&gPerfAmtPostMemGuid, NULL, NULL, AsmReadTsc (), 0x40C0);
  AmtPostMemInit ();
  PERF_END_EX (&gPerfAmtPostMemGuid, NULL, NULL, AsmReadTsc (), 0x40C1);

  //
  // SA Security Lock down after all initialization done
  //
  PERF_START_EX (&gPerfSaSecLockPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4050);
  SaSecurityLock ();
  PERF_END_EX (&gPerfSaSecLockPostMemGuid, NULL, NULL, AsmReadTsc (), 0x4051);


  //
  // Install EndOfPei callback function.
  //
#ifdef FSP_FLAG
  if (GetFspGlobalDataPointer()->FspMode == FSP_IN_DISPATCH_MODE) {
    CopyGuid (mSiInitNotifyList->Guid, &gEfiEndOfPeiSignal2PpiGuid);
  }
#endif

  Status = PeiServicesNotifyPpi (mSiInitNotifyList);
  ASSERT_EFI_ERROR (Status);

  //
  // End of SiInit notification event
  //
#ifndef FSP_FLAG
  Status = PeiServicesInstallPpi (&mEndOfSiInit);
  ASSERT_EFI_ERROR (Status);
#else
  if (GetFspGlobalDataPointer()->FspMode == FSP_IN_DISPATCH_MODE) {
    Status = PeiServicesInstallPpi (&mEndOfSiInit);
    ASSERT_EFI_ERROR (Status);
  }
#endif

  DEBUG ((DEBUG_INFO, "SiInit () - End\n"));

  return EFI_SUCCESS;
}

/**
  Silicon Initializes after memory services initialized

  @param[in] FileHandle           The file handle of the file, Not used.
  @param[in] PeiServices          General purpose services available to every PEIM.

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
EFIAPI
SiInit (
  IN  EFI_PEI_FILE_HANDLE               FileHandle,
  IN CONST EFI_PEI_SERVICES             **PeiServices
  )
{
  EFI_STATUS                Status;

  //
  // Install PostMem phase OnPolicyInstalled callback function.
  //
  Status = PeiServicesNotifyPpi (mSiInitPostMemNotifyList);
  ASSERT_EFI_ERROR (Status);

  return Status;
}
