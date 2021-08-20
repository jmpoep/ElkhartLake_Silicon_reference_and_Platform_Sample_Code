/** @file
  The PCH Initialization Dispatcher After Memory.

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

@par Specification Reference:
**/

#include "PchInitPei.h"
#include <Library/PostCodeLib.h>
#include <Library/SerialIoI2cMasterLib.h>
#include <Library/PchDmiLib.h>
#include <Library/PchFiaLib.h>
#include <Library/PeiGbeInitLib.h>
#include <Library/PeiSciInitLib.h>
#include <Library/PeiP2sbPrivateLib.h>
#include <Library/PeiRtcLib.h>
#include <Library/PeiSataLib.h>
#include <Library/PeiEspiInitLib.h>
#include <Library/PeiIshInitLib.h>
#include <Library/PeiPseInitLib.h>
#include <Library/PeiTsnInitLib.h>
#include <Library/PeiSerialIoInitLib.h>
#include <Library/PeiHdaInitLib.h>
#include <Library/PeiSmbusLib.h>
#include <Library/PeiIehInitLib.h>
#include <Library/PeiPcieRpInitLib.h>
#include <Library/PeiPsfLib.h>
#include <Library/PeiFusaLib.h>
#include <SaPolicyCommon.h>
#include <Library/PeiSiipLib.h>
#include <SiipCommon.h>
#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
#include <Library/PchSmmControlLib.h>
#endif

/**
  The function issues reset based on SI_SCHEDULE_RESET_HOB
**/
STATIC
VOID
PchPeiReset (
  VOID
  )
{
  SA_MISC_PEI_PREMEM_CONFIG *MiscPeiPreMemConfig;
  EFI_STATUS                Status;
  SI_PREMEM_POLICY_PPI      *SiPreMemPolicyPpi;
  BOOLEAN                   ResetStatus;

  if (!SiScheduleResetIsRequired ()) {
    return;
  }

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );

  MiscPeiPreMemConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (MiscPeiPreMemConfig == NULL) {
    return;
  }

  if (MiscPeiPreMemConfig->S3DataPtr == NULL) {
    DEBUG ((DEBUG_INFO, "MRC Data not valid. Postpone reset to DXE\n"));
    return;
  }
  ResetStatus = SiScheduleResetPerformReset ();
  ASSERT (!ResetStatus);
}

/**
  Pch init after memory PEI module

  @param[in] SiPolicy     The Silicon Policy PPI instance

  @retval None
**/
VOID
PchInit (
  IN  SI_POLICY_PPI  *SiPolicy
  )
{
  UINT32             SataCtrlIndex;

  PostCode (0xB00); // PCH API Entry
  DEBUG ((DEBUG_INFO, "PchInit - Start\n"));

#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
  //
  // Install PEI SMM Control PPI
  //
  PchSmmControlInit ();
#endif

  //
  // HSIO programming
  //
  PchHsioMiscBiosProg (SiPolicy);
  //
  // FIA Lane Orientation Muxing Configuration
  //
  PchFiaConfigureOrientationMuxing (SiPolicy);

  //
  // Program PSF grant counts for SATA
  // Call this before SATA ports are accessed for enumeration
  //
  PsfConfigureSataGrantCounts ();

  //
  // Configure PCH SATA
  //
  for (SataCtrlIndex = 0; SataCtrlIndex < MaxSataControllerNum (); SataCtrlIndex++) {
    ConfigureSata (SiPolicy, SataCtrlIndex);
  }

  PchConfigureClkreqMapping ();

  //
  // Configure GbE LAN
  //
  if (PchIsGbeSupported ()) {
    GbeInit (SiPolicy);
  }

  //
  // PchInfo HOB must be created before PCIe root port initialization, because
  // afterwards it cannot be determined which ports were fused off
  //
  BuildPchInfoHob ();

  //
  // Build and Update PCH configuration HOB
  //
  BuildPchConfigHob (SiPolicy);

  //
  // Configure PCH PCIe Root Ports
  //
  PcieRpInit (SiPolicy);

  DisableUnusedPcieClocks ();

  //
  // Handle PCH PSF Disable
  //
  PchPsfDisableP2pDecoding ();

  //
  // Configure PCH USB controllers
  //
  PchUsbConfigure (SiPolicy);

  //
  // Configure DMI
  //
  PostCode (0xB0A);
  if (IsPchH ()) {
    PchDmi15Init (SiPolicy);
  } else {
    PchDmi14Init (SiPolicy);
  }

  //
  // Configure P2SB
  //
  PostCode (0xB0B);
  P2sbConfigure (SiPolicy);

  //
  // Configure PSTH
  //
  PchPsthConfigure (SiPolicy);

  //
  // Configure IOAPIC
  //
  PostCode (0xB0C);
  ItssInitIoApic (SiPolicy);

  //
  // Configure interrupts.
  //
  PostCode (0xB0D);
  ItssConfigureInterrupts (SiPolicy);

  //
  // Configure CNVi devices
  //
  CnviInit (SiPolicy);

  //
  // Touch Host Controller
  //
  ThcInit (SiPolicy);

  //
  // Configure SCS devices
  //
  PostCode (0xB13);
  ScsInit (SiPolicy);


  //
  // Configure Integrated Sensor Hub (ISH)
  //
  PostCode (0xB14);

  //
  // Configure Serial IO
  //
  SerialIoInit (SiPolicy);

  //
  // Configure Programmable Service Engine (PSE)
  //
  PseInit (SiPolicy);

  //
  // Configure TSN
  //
  if (PchIsTsnSupported ()) {
    TsnInit (SiPolicy);
  }

  SiipFwLoading (SiPolicy, PSE_IP);

  PsfHidePseDmaDevices ();
  //
  // Configure GPIO PM and interrupt settings
  //
  GpioConfigurePm (SiPolicy);
  GpioSetIrq (ItssGetGpioDevIntConfig (SiPolicy));

  //
  // Perform initial DFx (Jtag) related configurations
  //
  GpioConfigureDFx ();

  //
  // Configure Time Sync Gpio
  //
  TimeSyncInit (SiPolicy);

  //
  // Configure Fusa configuration for Psf
  //
  PsfFusaOverrideProgramming (SiPolicy);
  //
  // Configure PSF PM settings
  //
  PsfConfigurePowerManagement (SiPolicy);

  //
  // Configure RTC
  //
  PchRtcConfigure (SiPolicy);

  //
  // Configure SMBUS
  //
  PostCode (0xB15);
  SmbusConfigure (SiPolicy);

  //
  // Configure ICLK
  //
  PchIClkConfigure ();

  //
  // Configure FIVR
  //
  PmcPchFivrInit (SiPolicy);


  //
  // Configure LPC PM
  //
  LpcConfigurePm ();

  //
  // Hide PMC PciCfgSpace
  //
  PsfHidePmcDevice ();

  //
  // Install I2C protocol for PEI use.
  //
  InstallI2cMasterPpi (0);

  //
  // Configure eSPI after memory
  //
  EspiInit (SiPolicy);

  //
  // Configure IEH
  //
  IehInit (SiPolicy);
  //
  // Configure SCI
  //
  SciInit (SiPolicy);

  if (IsPchLp ()) {
    //
    // Disable D3:F0 in PSF
    //
    PsfDisableD3F0 ();
  }


  //
  // Configure root port function number mapping
  // This has to be done before PCI enumeration and after RST remapping
  //
  PcieRpConfigureRpfnMapping ();

  //
  // Configure PSF PCIe Grant Counts after PCIe Root Ports are initialized
  // and unused ports are disabled
  //
  PcieRpConfigureGrantCounts ();

  //
  // Configure Serial IO Function 0
  // This has to happen late here after all other PCH devices (non serial) are configured because non serial devices
  // may share device number with func0 serial Io
  //
  SerialIoFunction0Disable (SiPolicy);

  //
  // Check if ME has the right HSIO Settings and sync with ME if required.
  // Has to be done before PMC Init to ensure the USB2PHY and ModPHY Power Gating
  // settings are turned on after CSME has the correct SUS tables.
  //
#if FixedPcdGetBool(PcdBfxEnable) == 0
  //
  // Temporary disabled for UFS boot as HECI is giving error
  //
  // Temporary disable for Power On due to CSE Production is not stable.
  ChipsetInitSync ();
#endif

  //
  // Configure PMC settings
  //
  PmcInit (SiPolicy);

  //
  // Lock FIVR Configuration
  //
  PmcLockFivrConfig ();

  //
  // Issue Reset based on SiScheduleResetHob
  //
  PchPeiReset ();

  PostCode (0xB7F);  // PCH API Exit
  DEBUG ((DEBUG_INFO, "PchInit - End\n"));
}
