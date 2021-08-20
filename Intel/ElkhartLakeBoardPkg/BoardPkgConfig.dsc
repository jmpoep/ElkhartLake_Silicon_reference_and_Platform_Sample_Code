## @file
#  Platform configuration file.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2017 - 2020 Intel Corporation.
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
  # Please select BootStage here.
  # Stage 1 - enable debug (system deadloop after debug init)
  # Stage 2 - mem init (system deadloop after mem init)
  # Stage 3 - boot to shell only
  # Stage 4 - boot to OS
  # Stage 5 - boot to OS with security boot enabled
  # Stage 6 - boot with advanced features
  # stage 7 - tuning
  #

  gMinPlatformPkgTokenSpaceGuid.PcdBootStage|6

[PcdsFeatureFlag]

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage >= 1
  gMinPlatformPkgTokenSpaceGuid.PcdStopAfterDebugInit|TRUE
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage >= 2
  gMinPlatformPkgTokenSpaceGuid.PcdStopAfterDebugInit|FALSE
  gMinPlatformPkgTokenSpaceGuid.PcdStopAfterMemInit|TRUE
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage >= 3
  gMinPlatformPkgTokenSpaceGuid.PcdStopAfterMemInit|FALSE
  gMinPlatformPkgTokenSpaceGuid.PcdBootToShellOnly|TRUE
  gBoardModuleTokenSpaceGuid.PcdUefiShellEnable|TRUE
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage >= 4
  gMinPlatformPkgTokenSpaceGuid.PcdBootToShellOnly|FALSE
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage >= 5
  gBoardModuleTokenSpaceGuid.PcdSecurityEnable|TRUE
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage >= 6
  gBoardModuleTokenSpaceGuid.PcdAdvancedFeatureEnable|TRUE
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdBootStage == 7
  gBoardModuleTokenSpaceGuid.PcdOptimizationEnable|TRUE
!endif

[PcdsFixedAtBuild]
#
# Setting feature PCDs based on boot stages set above
#
!if gMinPlatformPkgTokenSpaceGuid.PcdBootToShellOnly == FALSE
  gSiPkgTokenSpaceGuid.PcdAcpiEnable|TRUE
  gBoardModuleTokenSpaceGuid.PcdAcpiDebugFeatureEnable|TRUE
!endif  #PcdBootToShellOnly

!if gBoardModuleTokenSpaceGuid.PcdAdvancedFeatureEnable == TRUE

  gBoardModuleTokenSpaceGuid.PcdGopConfigBin|FALSE
  gSiPkgTokenSpaceGuid.PcdPpmEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdSmbiosEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdS3Enable|TRUE
  gSiPkgTokenSpaceGuid.PcdITbtEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdBootGuardEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdTxtEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdTraceHubEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdPostCodeStatusCodeEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdTraceHubPostCodeEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdSourceDebugEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdBiosGuardEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdHgEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdS4Enable|TRUE

  gBoardModuleTokenSpaceGuid.PcdNvmeEnable|TRUE
  gBoardModuleTokenSpaceGuid.PcdIntelRaidEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdTerminalEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdOverclockEnable|FALSE

  gSiPkgTokenSpaceGuid.PcdEmbeddedEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdAmtEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdAtaEnable|TRUE

  gPlatformModuleTokenSpaceGuid.PcdIgdIntHookEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdAhciEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdDTbtEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdI2cTouchDriverEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdPiI2cStackEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdUsb3SerialStatusCodeEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdUserAuthenticationEnable|TRUE

  gPlatformModuleTokenSpaceGuid.PcdPciHotplugEnable|TRUE
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  gPlatformModuleTokenSpaceGuid.PcdUsbTypeCEnable|FALSE
!else
  gPlatformModuleTokenSpaceGuid.PcdUsbTypeCEnable|TRUE
!endif
  gPlatformModuleTokenSpaceGuid.PcdSimpleBootFlagEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdVirtualKeyboardEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdEbcEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdHddPasswordEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdNetworkEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdGigUndiEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdMouseEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdStmBinEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdSinitAcmBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdAcmProdBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdGopOverrideDriverEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdScsiEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdJpgEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdBootTimeEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdSmiVariableEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdIgdIntHookEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdUsbEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdLegacyUsbBinEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdDnxSupportEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdPlatformCmosAccessSupport|TRUE
  gPlatformModuleTokenSpaceGuid.PcdEnableSecureErase|TRUE
  gPlatformModuleTokenSpaceGuid.PcdUnitoolEnable|TRUE

  #
  # Build Switch for bin files.
  #
  !if gSiPkgTokenSpaceGuid.PcdBiosGuardEnable == TRUE
    gBoardModuleTokenSpaceGuid.PcdBiosGuardBinEnable|TRUE              #BiosGuardModule.bin # @todo: Needs to check if it's necessary to exist
  !else
    gBoardModuleTokenSpaceGuid.PcdBiosGuardBinEnable|FALSE
  !endif
  gBoardModuleTokenSpaceGuid.PcdStartupAcmProdBinEnable|FALSE        #StartupAcmProd.bin
  gBoardModuleTokenSpaceGuid.PcdNhltBinEnable|TRUE                   #NhltIcl.bin
  gBoardModuleTokenSpaceGuid.PcdElixirSpringsPatchBinEnable|FALSE    #Elixir Springs Patch # @todo: Use existing binary when available.
  gBoardModuleTokenSpaceGuid.PcdReservedFitBinEnable|TRUE            #ReservedFIT.bin
  gPlatformModuleTokenSpaceGuid.PcdAhciOromBinEnable|FALSE           #AHCIOR.BIN
  gPlatformModuleTokenSpaceGuid.PcdCsmLegacy16BinEnable|FALSE        #AmiLegacy16.bin
  gPlatformModuleTokenSpaceGuid.PcdSredirBinEnable|FALSE             #Sredir.bin
  gPlatformModuleTokenSpaceGuid.PcdSinitAcmBinEnable|FALSE           #SinitAc.bin
  gPlatformModuleTokenSpaceGuid.PcdH8S2113Present|FALSE
  gPlatformModuleTokenSpaceGuid.PcdNat87393Present|FALSE
  gPlatformModuleTokenSpaceGuid.PcdNct677FPresent|FALSE

  #
  # Build Switch for efi files.
  #
  gBoardModuleTokenSpaceGuid.PcdMebxEfiEnable|FALSE                   #Mebx.efi
  gBoardModuleTokenSpaceGuid.PcdMebxSetupBrowserEnable|FALSE          #MebxSetupBrowser.efi
  gBoardModuleTokenSpaceGuid.PcdRaidDriverEfiEnable|TRUE             #RaidDriver.efi
  gBoardModuleTokenSpaceGuid.PcdRsteDriverEfiEnable|TRUE             #SataDriverRste.efi
  gPlatformModuleTokenSpaceGuid.PcdLegacySredirBinEnable|FALSE       #LegacySredir.efi
  gPlatformModuleTokenSpaceGuid.PcdIccOverClockingBinEnable|TRUE    #IccOverClocking.efi

  gPlatformModuleTokenSpaceGuid.PcdNetworkIp6Enable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdNetworkIscsiEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdNetworkVlanEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdFatEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdCryptoEnable|TRUE    # Current Smbios implementation needs this
  gPlatformModuleTokenSpaceGuid.PcdLzmaEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdDxeCompressEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdVtioEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdUserIdentificationEnable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdTdsEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdOpalPasswordEnable|TRUE
  gPlatformModuleTokenSpaceGuid.PcdMemoryTestEnable|TRUE

  gSiPkgTokenSpaceGuid.PcdOcWdtEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdSoftwareGuardEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdSerialIoUartEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdIpuEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdIgdEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdPeiDisplayEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdVtdEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdCpuPowerOnConfigEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdPegEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdSaDmiEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdGnaEnable|TRUE
  gSiPkgTokenSpaceGuid.Pcd2lmEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdVmdEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdCpuPcieEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdIntegratedTouchEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdPttEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdJhiEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdSmmVariableEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdThcEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdTbtLegacyModeSupport|FALSE
  gSiPkgTokenSpaceGuid.PcdOptimizeCompilerEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdPpmEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdPsmiEnable|TRUE
!endif  #PcdAdvancedFeatureEnable

  gSiPkgTokenSpaceGuid.PcdITbtEnable|FALSE

  #
  # Silicon feature settings
  #
  !if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == FALSE
    gSiPkgTokenSpaceGuid.PcdFspModeSelection|0x00
  !endif
  gSiPkgTokenSpaceGuid.PcdBdatEnable|FALSE


  #
  # LiteBios related PCDs must be moved to LiteBios board package when it is  created
  #

  gBoardModuleTokenSpaceGuid.PcdMicrocodeBinEnable|TRUE       #Microcode
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  gBoardModuleTokenSpaceGuid.PcdEcEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdEcLitePseEnable|TRUE
!else
  gBoardModuleTokenSpaceGuid.PcdEcEnable|TRUE
  gBoardModuleTokenSpaceGuid.PcdEcLitePseEnable|FALSE
!endif

  gPlatformModuleTokenSpaceGuid.PcdRamDebugEnable|TRUE
  gBoardModuleTokenSpaceGuid.PcdSipkgBinaryEnable|FALSE

  #
  # BIOS build switches configuration
  #
  gPlatformModuleTokenSpaceGuid.PcdDeprecatedFunctionRemove|FALSE
  gPlatformModuleTokenSpaceGuid.PcdSerialPortEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdBfxEnable|FALSE
  gSiPkgTokenSpaceGuid.PcdBfxHfpgaWorkAroundEnable|FALSE
  gBoardModuleTokenSpaceGuid.PcdS5ChargingEnable|TRUE
  gSiPkgTokenSpaceGuid.PcdSpiPostCode|TRUE
  gBoardModuleTokenSpaceGuid.PcdUfsEnable|TRUE

  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVendor|L"Intel"

  !if gBoardModuleTokenSpaceGuid.PcdSecurityEnable == TRUE
    gPlatformModuleTokenSpaceGuid.PcdTpmEnable|TRUE
  !endif


  gPlatformModuleTokenSpaceGuid.PcdUsbFnEnable|TRUE

[PcdsFeatureFlag]
!if gBoardModuleTokenSpaceGuid.PcdSecurityEnable == TRUE
  gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable|TRUE
  !if $(TARGET) == DEBUG
    gMinPlatformPkgTokenSpaceGuid.PcdSmiHandlerProfileEnable|TRUE
  !endif
!endif  #PcdSecurityEnable

!if gBoardModuleTokenSpaceGuid.PcdOptimizationEnable == TRUE
  gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable|TRUE
!endif  #PcdOptimizationEnable

  gBoardModuleTokenSpaceGuid.PcdIntelGopEnable|TRUE                  #LegacyVideoRom.bin and IntelGopDriver.efi
