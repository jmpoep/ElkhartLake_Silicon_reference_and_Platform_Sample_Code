/** @file
  This file is SampleCode of the library for Intel PCH PEI Debug Policy initialization.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#include <Library/PeiPchPolicyUpdate.h>
#include <PiPei.h>
#include <SetupVariable.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PchInfoLib.h>
#include <Library/SiPolicyLib.h>
#include <Library/CpuPlatformLib.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspsUpd.h>
#endif

/**
  Update PCIE Root Port debug policies

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
  @param[in] PchSetup  Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdatePcieRpDebugPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN VOID           *FspsUpd,
  IN PCH_SETUP      *PchSetup
  )
{
  UINT8             Index;
  PCH_PCIE_CONFIG   *PcieRpConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PcieRpConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEnablePort8xhDecode,                            PcieRpConfig->EnablePort8xhDecode,                               PchSetup->PcieRootPort8xhDecode);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPciePort8xhDecodePortIndex,                      PcieRpConfig->PchPciePort8xhDecodePortIndex,                     PchSetup->Pcie8xhDecodePortIndex);

  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
    if (IsPchLp ()) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrMaxSnoopLatency[Index],                PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxSnoopLatency,                0x1003);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrMaxNoSnoopLatency[Index],              PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxNoSnoopLatency,              0x1003);
    }
    if (IsPchH ()) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrMaxSnoopLatency[Index],                PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxSnoopLatency,                0x0846);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrMaxNoSnoopLatency[Index],              PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxNoSnoopLatency,              0x0846);
    }
    if (PchSetup->PchPcieLtrEnable[Index]) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrMaxSnoopLatency[Index],                PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxSnoopLatency,                0x1003);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrMaxNoSnoopLatency[Index],              PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxNoSnoopLatency,              0x1003);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpSnoopLatencyOverrideMode[Index],          PcieRpConfig->RootPort[Index].PcieRpLtrConfig.SnoopLatencyOverrideMode,          PchSetup->PchPcieSnoopLatencyOverrideMode[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpSnoopLatencyOverrideMultiplier[Index],    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.SnoopLatencyOverrideMultiplier,    PchSetup->PchPcieSnoopLatencyOverrideMultiplier[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpNonSnoopLatencyOverrideMode[Index],       PcieRpConfig->RootPort[Index].PcieRpLtrConfig.NonSnoopLatencyOverrideMode,       PchSetup->PchPcieNonSnoopLatencyOverrideMode[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpNonSnoopLatencyOverrideMultiplier[Index], PcieRpConfig->RootPort[Index].PcieRpLtrConfig.NonSnoopLatencyOverrideMultiplier, PchSetup->PchPcieNonSnoopLatencyOverrideMultiplier[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpSnoopLatencyOverrideValue[Index],         PcieRpConfig->RootPort[Index].PcieRpLtrConfig.SnoopLatencyOverrideValue,         PchSetup->PchPcieSnoopLatencyOverrideValue[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpNonSnoopLatencyOverrideValue[Index],      PcieRpConfig->RootPort[Index].PcieRpLtrConfig.NonSnoopLatencyOverrideValue,      PchSetup->PchPcieNonSnoopLatencyOverrideValue[Index]);
    }
  }
}

/**
  Update PCH DMI debug policies.

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdatePchDmiDebugPolicy (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  UINT8                        Index;
  PCH_DMI_CONFIG               *PchDmiConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchDmiConfigGuid, (VOID *) &PchDmiConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PchDmiConfig = NULL;
#endif

  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
    if (PchSetup->PchPcieLtrEnable[Index] == TRUE) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPwrOptEnable, PchDmiConfig->PwrOptEnable, TRUE);
      return;
    }
  }
}

/**
  Update SATA debug policies.

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateSataDebugPolicy (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  SATA_CONFIG                  *SataConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSataConfigGuid, (VOID *) &SataConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  SataConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataTestMode, SataConfig->TestMode, PchSetup->SataTestMode);
}

/**
  Update USB debug policies.

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateUsbDebugPolicy (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  USB_CONFIG                   *UsbConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsbConfigGuid, (VOID *) &UsbConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  UsbConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchXhciOcLock, UsbConfig->XhciOcLock, PchSetup->PchXhciOcLock);
}

/**
  Update Power Management debug policies.

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdatePmDebugPolicy (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  PCH_PM_CONFIG                *PmConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PmConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmDisableEnergyReport, PmConfig->DisableEnergyReport, (PchSetup->PchEnergyReport == 1)? 0 : 1);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmcLpmS0ixSubStateEnableMask, PmConfig->LpmS0ixSubStateEnable.Val,  ((PchSetup->PmcLpmS0i2p0En << 0) |
                                                                                                                             (PchSetup->PmcLpmS0i2p1En << 1) |
                                                                                                                             (PchSetup->PmcLpmS0i2p2En << 2) |
                                                                                                                             (PchSetup->PmcLpmS0i3p0En << 3) |
                                                                                                                             (PchSetup->PmcLpmS0i3p1En << 4) |
                                                                                                                             (PchSetup->PmcLpmS0i3p2En << 5) |
                                                                                                                             (PchSetup->PmcLpmS0i3p3En << 6) |
                                                                                                                             (PchSetup->PmcLpmS0i3p4En << 7)));
}

/**
  Update P2sb debug policies.

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateP2sbDebugPolicy (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  PCH_P2SB_CONFIG                 *P2sbConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gP2sbConfigGuid, (VOID *) &P2sbConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  P2sbConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchSbAccessUnlock, P2sbConfig->SbAccessUnlock, PchSetup->PchSidebandLock ? 0 : 1);
}

/**
  This function performs PCH PEI Debug Policy initialization.

  @retval EFI_SUCCESS        The PPI is installed and initialized.
  @retval EFI ERRORS         The PPI is not successfully installed.
**/
EFI_STATUS
EFIAPI
UpdatePeiPchPolicyDebug (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  UINTN                           VariableSize;
  PCH_SETUP                       PchSetup;
  SI_POLICY_PPI                   *SiPolicy;
  VOID                            *FspsUpd;

  DEBUG ((DEBUG_INFO, "Update PeiPchPolicyDebug Pos-Mem Start\n"));

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = (FSPS_UPD *) PcdGet32 (PcdFspsUpdDataAddress);
  ASSERT (FspsUpd != NULL);
  SiPolicy     = NULL;
#else
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicy);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  FspsUpd = NULL;
#endif
  //
  // Retrieve Setup variable
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid, // GUID
             0,                                // INSTANCE
             NULL,                             // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices       // PPI
             );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &PchSetup
                               );
  ASSERT_EFI_ERROR (Status);

  UpdatePcieRpDebugPolicy (SiPolicy, FspsUpd, &PchSetup);
  UpdatePchDmiDebugPolicy (SiPolicy, FspsUpd, &PchSetup);
  UpdateSataDebugPolicy (SiPolicy, FspsUpd, &PchSetup);
  UpdateUsbDebugPolicy (SiPolicy, FspsUpd, &PchSetup);
  UpdatePmDebugPolicy (SiPolicy, FspsUpd, &PchSetup);
  UpdateP2sbDebugPolicy (SiPolicy, FspsUpd, &PchSetup);

  return Status;
}
