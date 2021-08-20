## @file
#  Platform configuration file default values.
#
# [Note]:
#  Default PCD values from the DEC files cannot be used in conditional directives within
#  the DSC file; all PCD values used in directive statements must be defined in the DSC
#  file.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2018 - 2020 Intel Corporation.
#
#  The source code contained or described herein and all documents related to the
#  source code ("Material") are owned by Intel Corporation or its suppliers or
#  licensors. Title to the Material remains with Intel Corporation or its suppliers
#  and licensors. The Material may contain trade secrets and proprietary and
#  confidential information of Intel Corporation and its suppliers and licensors,
#  and is protected by worldwide copyright and trade secret laws and treaty
#  provisions. No part of the Material may be used, copied, reproduced, modified,
#  published, uploaded, posted, transmitted, distributed, or disclosed in any way
#  without Intel's prior express written permission.
#
#  No license under any patent, copyright, trade secret or other intellectual
#  property right is granted to or conferred upon you by disclosure or delivery
#  of the Materials, either expressly, by implication, inducement, estoppel or
#  otherwise. Any license under such intellectual property rights must be
#  express and approved by Intel in writing.
#
#  Unless otherwise agreed by Intel in writing, you may not remove or alter
#  this notice or any other notice embedded in Materials by Intel or
#  Intel's suppliers or licensors in any way.
#
#  This file contains a 'Sample Driver' and is licensed as such under the terms
#  of your license agreement with Intel or your vendor. This file may be modified
#  by the user, subject to the additional terms of the license agreement.
#
# @par Specification
##
[PcdsFixedAtBuild]
  #
  # Default BootStage is set here.
  # Stage 1 - enable debug (system deadloop after debug init)
  # Stage 2 - mem init (system deadloop after mem init)
  # Stage 3 - boot to shell only
  # Stage 4 - boot to OS
  # Stage 5 - boot to OS with security boot enabled
  # Stage 6 - boot with advanced features
  # stage 7 - tuning
  #
  gMinPlatformPkgTokenSpaceGuid.PcdBootStage|4

[PcdsFeatureFlag]

  gMinPlatformPkgTokenSpaceGuid.PcdStopAfterDebugInit|FALSE
  gMinPlatformPkgTokenSpaceGuid.PcdStopAfterMemInit|FALSE
  gMinPlatformPkgTokenSpaceGuid.PcdBootToShellOnly|FALSE
  gBoardModuleTokenSpaceGuid.PcdSecurityEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdAdvancedFeatureEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdOptimizationEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdIntelGopEnable|FALSE                  #LegacyVideoRom.bin and IntelGopDriver.efi

  gMinPlatformPkgTokenSpaceGuid.PcdSmiHandlerProfileEnable|FALSE
  gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable|FALSE

  # Build scripts override the value of this PCD, update value in scripts for the change to take effect.
  gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable|FALSE

  gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdUefiShellEnable|FALSE

[PcdsFixedAtBuild]
  gSiPkgTokenSpaceGuid.PcdAcpiEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdSmbiosEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdS3Enable|FALSE
  gSiPkgTokenSpaceGuid.PcdITbtEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdTraceHubEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdSourceDebugEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdBiosGuardEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdHgEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdBootGuardEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdTxtEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdEmbeddedEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdAmtEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdAtaEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdOverclockEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdFspWrapperEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdFspModeSelection|1
  gSiPkgTokenSpaceGuid.PcdEhlCpuEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdEhlPchEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdTglCpuEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdTglPchEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdCflCpuEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdOcWdtEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdSoftwareGuardEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdSerialIoUartEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdIpuEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdIgdEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdPeiDisplayEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdVtdEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdCpuPowerOnConfigEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdPegEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdSaDmiEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdGnaEnable|FALSE
  gSiPkgTokenSpaceGuid.Pcd2lmEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdIntegratedTouchEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdPttEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdJhiEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdSmmVariableEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdThcEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdOptimizeCompilerEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdPpmEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdSerialIoUartDebugEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdPpamEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable|FALSE

  gBoardModuleTokenSpaceGuid.PcdAcpiDebugFeatureEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdS4Enable|FALSE
  gBoardModuleTokenSpaceGuid.PcdBiosGuardBinEnable|FALSE              #BiosGuardModule.bin

  gBoardModuleTokenSpaceGuid.PcdStartupAcmProdBinEnable|FALSE         #StartupAcmProd.bin
  gBoardModuleTokenSpaceGuid.PcdGopConfigBin|FALSE
  gBoardModuleTokenSpaceGuid.PcdNhltBinEnable|FALSE                   #NhltIcl.bin
  gBoardModuleTokenSpaceGuid.PcdMebxEfiEnable|FALSE                   #Mebx.efi
  gBoardModuleTokenSpaceGuid.PcdMebxSetupBrowserEnable|FALSE          #MebxSetupBrowser.efi
  gBoardModuleTokenSpaceGuid.PcdRaidDriverEfiEnable|FALSE             #RaidDriver.efi
  gBoardModuleTokenSpaceGuid.PcdRsteDriverEfiEnable|FALSE             #SataDriverRste.efi
  gBoardModuleTokenSpaceGuid.PcdNvmeEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdIntelRaidEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdTerminalEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdElixirSpringsPatchBinEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdEcEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdEcLitePseEnable|TRUE
  gBoardModuleTokenSpaceGuid.PcdReservedFitBinEnable|FALSE

  gPlatformModuleTokenSpaceGuid.PcdPlatformCmosAccessSupport|FALSE
  gPlatformModuleTokenSpaceGuid.PcdEnableSecureErase|FALSE
  gPlatformModuleTokenSpaceGuid.PcdDTbtEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdI2cTouchDriverEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdPiI2cStackEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdUsb3SerialStatusCodeEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdUserAuthenticationEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdPciHotplugEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdUsbTypeCEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdSimpleBootFlagEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdVirtualKeyboardEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdEbcEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdHddPasswordEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdNetworkEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdGigUndiEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdMouseEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdStmBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdSinitAcmBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdAcmProdBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdGopOverrideDriverEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdScsiEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdJpgEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdBootTimeEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdSmiVariableEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdIgdIntHookEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdUsbEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdLegacyUsbBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdIgdIntHookEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdCsmLegacy16BinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdSredirBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdAhciEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdAhciOromBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdLegacySredirBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdNetworkIp6Enable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdNetworkIscsiEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdNetworkVlanEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdFatEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdCryptoEnable|FALSE    # Current Smbios implementation needs this
  gPlatformModuleTokenSpaceGuid.PcdLzmaEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdDxeCompressEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdCodeCoverageEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdVtioEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdUserIdentificationEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdDnxSupportEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdIccOverClockingBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdUsbFnEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdH8S2113Present|FALSE
  gPlatformModuleTokenSpaceGuid.PcdNat87393Present|FALSE
  gPlatformModuleTokenSpaceGuid.PcdNct677FPresent|FALSE
  gPlatformModuleTokenSpaceGuid.PcdSkipFspTempRamInitAndExit|FALSE
  gPlatformModuleTokenSpaceGuid.PcdTdsEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdOpalPasswordEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdMemoryTestEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdTpmEnable|FALSE

  # Build scripts override the value of this PCD, update value in scripts for the change to take effect.
  gBoardModuleTokenSpaceGuid.PcdSetupEnable|TRUE
  gBoardModuleTokenSpaceGuid.PcdStartupAcmBinEnable|FALSE           #StartupAcm.bin
