/** @file
  This file is the library for PCH DXE Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

#include <PiDxe.h>
#include <SetupVariable.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PchInfoLib.h>
#include <Protocol/PchPolicy.h>
#include <HdAudioConfig.h>
#include <ScsConfig.h>
#include <Protocol/EmmcDriverStrengthProtocol.h>
#include <ScsEmmcSoftwareTuningVariable.h>

#define PCI_CLASS_NETWORK             0x02
#define PCI_CLASS_NETWORK_ETHERNET    0x00
#define PCI_CLASS_NETWORK_OTHER       0x80

GLOBAL_REMOVE_IF_UNREFERENCED PCH_PCIE_DEVICE_OVERRIDE mPcieDeviceUpdateTable[] = {
  //
  // Intel PRO/Wireless
  //
  { 0x8086, 0x422b, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x422c, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x4238, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x4239, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel WiMAX/WiFi Link
  //
  { 0x8086, 0x0082, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0085, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0083, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0084, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0086, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0087, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0088, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0089, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x008F, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0090, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel Crane Peak WLAN NIC
  //
  { 0x8086, 0x08AE, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x08AF, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel Crane Peak w/BT WLAN NIC
  //
  { 0x8086, 0x0896, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0897, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel Kelsey Peak WiFi, WiMax
  //
  { 0x8086, 0x0885, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0886, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel Centrino Wireless-N 105
  //
  { 0x8086, 0x0894, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0895, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel Centrino Wireless-N 135
  //
  { 0x8086, 0x0892, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0893, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel Centrino Wireless-N 2200
  //
  { 0x8086, 0x0890, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0891, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel Centrino Wireless-N 2230
  //
  { 0x8086, 0x0887, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x0888, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel Centrino Wireless-N 6235
  //
  { 0x8086, 0x088E, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x088F, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel CampPeak 2 Wifi
  //
  { 0x8086, 0x08B5, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  { 0x8086, 0x08B6, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },
  //
  // Intel WilkinsPeak 1 Wifi
  //
  { 0x8086, 0x08B3, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2AndL1SubstatesOverride, 0x0158, 0x0000000F, 0, 0, 0, 0, 0 },
  { 0x8086, 0x08B4, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2AndL1SubstatesOverride, 0x0158, 0x0000000F, 0, 0, 0, 0, 0 },
  //
  // Intel Wilkins Peak 2 Wifi
  //
  { 0x8086, 0x08B1, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2AndL1SubstatesOverride, 0x0158, 0x0000000F, 0, 0, 0, 0, 0 },
  { 0x8086, 0x08B2, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2AndL1SubstatesOverride, 0x0158, 0x0000000F, 0, 0, 0, 0, 0 },
  //
  // Intel Wilkins Peak PF Wifi
  //
  { 0x8086, 0x08B0, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1, PchPcieL1L2Override, 0, 0, 0, 0, 0, 0, 0 },

  //
  // End of Table
  //
  { 0 }
};

GLOBAL_REMOVE_IF_UNREFERENCED EMMC_DRIVER_STRENGTH_PROTOCOL  gEmmcDriverStrengthProtocol;

/**
  Update Emmc software tuning configuration with previous tuning results.

  @param[out] EmmcDxeConfig  Pointer to eMMC DXE config.
**/
STATIC
VOID
EmmcUpdatePreviousTuningResults (
  OUT SCS_EMMC_DXE_CONFIG  *EmmcDxeConfig
  )
{
  SCS_EMMC_SOFTWARE_TUNING_VARIABLE  ScsEmmcTuningVariable;
  EFI_STATUS                         Status;
  UINTN                              VariableSize;

  VariableSize = sizeof (SCS_EMMC_SOFTWARE_TUNING_VARIABLE);
  Status = gRT->GetVariable (
                  SCS_EMMC_SOFTWARE_TUNING_VARIABLE_NAME,
                  &gScsEmmcSoftwareTuningVariableGuid,
                  NULL,
                  &VariableSize,
                  &ScsEmmcTuningVariable
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  if (GetBootModeHob () != BOOT_WITH_DEFAULT_SETTINGS) {
    CopyMem (&EmmcDxeConfig->PreviousTuningResults, &ScsEmmcTuningVariable.TuningResults, sizeof (SCS_EMMC_SOFTWARE_TUNING_RESULTS));
  }
}

/**
  Update eMMC DXE policies

  @param[in] PchPolicy  Pointer to PCH_POLICY_PROTOCOL
  @param[in] PchSetup   Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateEmmcDxePolicy (
  IN PCH_POLICY_PROTOCOL  *PchPolicy,
  IN PCH_SETUP            *PchSetup
  )
{
  EFI_STATUS                 Status;
  SCS_EMMC_DXE_CONFIG        *EmmcDxeConfig;
  EFI_HANDLE                 ProtocolHandle;

  Status = GetConfigBlock ((VOID*) PchPolicy, &gEmmcDxeConfigGuid, (VOID*) &EmmcDxeConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  EmmcDxeConfig->DriverStrength = PchSetup->PchScsEmmcHs400DriverStrength;

  if (PchSetup->PchScsEmmcHs400SoftwareTuning) {
    EmmcDxeConfig->EnableSoftwareHs400Tuning = TRUE;
    EmmcDxeConfig->TuningLba = 0x2000000;
    EmmcUpdatePreviousTuningResults (EmmcDxeConfig);
  }

  //
  // EMMC_DRIVER_STRENGTH_PROTOCOL is consumed by eMMC driver
  //
  switch (PchSetup->PchScsEmmcHs400DriverStrength) {
    case DriverStrength33Ohm:
      gEmmcDriverStrengthProtocol.EmmcDriverStrength = DriverStrengthType1;
      break;
    case DriverStrength50Ohm:
      gEmmcDriverStrengthProtocol.EmmcDriverStrength = DriverStrengthType0;
      break;
    case DriverStrength40Ohm:
    default:
      gEmmcDriverStrengthProtocol.EmmcDriverStrength = DriverStrengthType4;
  }

  ProtocolHandle = NULL;
  Status = gBS->InstallProtocolInterface (
                  &ProtocolHandle,
                  &gEmmcDriverStrengthProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  (VOID*)&gEmmcDriverStrengthProtocol
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to install driver strength protocol\n"));
  }
}

/**
  Update HD Audio DXE policies.

  @param[in] PchPolicy  Pointer to PCH_POLICY_PROTOCOL
  @param[in] PchSetup   Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateHdAudioDxePolicy (
  IN PCH_POLICY_PROTOCOL  *PchPolicy,
  IN PCH_SETUP            *PchSetup
  )
{
  EFI_STATUS              Status;
  UINT32                  Index;
  HDAUDIO_DXE_CONFIG      *HdAudioDxeConfig;

  Status = GetConfigBlock ((VOID *)PchPolicy, &gHdAudioDxeConfigGuid, (VOID *)&HdAudioDxeConfig);
  ASSERT_EFI_ERROR (Status);

  for (Index = 0; Index < PCH_MAX_HDA_SNDW_LINK_NUM; Index++) {
    HdAudioDxeConfig->SndwConfig[Index].AutonomousClockStop        = PchSetup->PchHdaAutonomousClockStopSndw[Index];
    HdAudioDxeConfig->SndwConfig[Index].DataOnActiveIntervalSelect = PchSetup->PchHdaDataOnActiveIntervalSelectSndw[Index];
    HdAudioDxeConfig->SndwConfig[Index].DataOnDelaySelect          = PchSetup->PchHdaDataOnDelaySelectSndw[Index];
  }

  for (Index = 0; Index < HDAUDIO_FEATURES; Index++) {
    HdAudioDxeConfig->DspFeatureMask |= (UINT32)(PchSetup->PchHdAudioFeature[Index] ? (1 << Index) : 0);
  }

}

/**
  Update PCIE Rp DXE policies

  @param[in] PchPolicy  Pointer to PCH_POLICY_PROTOCOL
**/
STATIC
VOID
UpdatePchPcieRpDxePolicy (
  IN PCH_POLICY_PROTOCOL  *PchPolicy
  )
{
  EFI_STATUS                 Status;
  PCIE_RP_DXE_CONFIG         *PchPcieRpDxeConfig;

  Status = GetConfigBlock ((VOID*) PchPolicy, &gPchPcieRpDxeConfigGuid, (VOID*) &PchPcieRpDxeConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  PchPcieRpDxeConfig->PcieDeviceOverrideTablePtr = mPcieDeviceUpdateTable;
}

/**
  Get data for PCH policy from setup options.

  @param[in] PchPolicy                 The pointer to get PCH Policy protocol instance

  @retval EFI_SUCCESS                  Operation success.

**/
EFI_STATUS
UpdateDxePchPolicy (
  IN OUT  PCH_POLICY_PROTOCOL    *PchPolicy
  )
{
  EFI_STATUS              Status;
  UINTN                   VariableSize;
  PCH_SETUP               PchSetup;

  VariableSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (
                   L"PchSetup",
                   &gPchSetupVariableGuid,
                   NULL,
                   &VariableSize,
                   &PchSetup
                   );
  ASSERT_EFI_ERROR (Status);

  UpdateEmmcDxePolicy (PchPolicy, &PchSetup);
  UpdateHdAudioDxePolicy (PchPolicy, &PchSetup);
  UpdatePchPcieRpDxePolicy (PchPolicy);

  return EFI_SUCCESS;
}
