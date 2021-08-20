## @file
#  Platform description.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2016 - 2020 Intel Corporation.
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
#  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
#  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
#  the terms of your license agreement with Intel or your vendor. This file may
#  be modified by the user, subject to additional terms of the license agreement.
#
# @par Specification
##

[Defines]
  #
  # Set platform specific package/folder name, same as passed from PREBUILD script.
  # PLATFORM_PACKAGE would be the same as PLATFORM_NAME as well as package build folder
  # DEFINE only takes effect at R9 DSC and FDF.
  #
  DEFINE      FSP_PACKAGE                     = ElkhartLakeFspPkg
  DEFINE      PLATFORM_SI_PACKAGE             = ClientOneSiliconPkg
  DEFINE      C1S_PRODUCT_PATH                = $(PLATFORM_SI_PACKAGE)/Product/ElkhartLake
  DEFINE      CLIENT_SILICON_PACKAGE          = ClientSiliconPkg
  DEFINE      PLATFORM_FULL_PACKAGE           = ElkhartLakePlatSamplePkg

[PcdsFixedAtBuild]
  #
  # BIOS build switches configuration
  #
  !include $(FSP_PACKAGE)/ElkhartLakeFspPkgConfig.dsc
  !include $(FSP_PACKAGE)/ElkhartLakeFspPkgConfigOverride.dsc

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = $(FSP_PACKAGE)
  PLATFORM_GUID                  = 1BEDB57A-7904-406e-8486-C89FC7FB39EE
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = $(CFG_OUTDIR)/$(FSP_PACKAGE)
  SUPPORTED_ARCHITECTURES        = IA32|X64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = $(FSP_PACKAGE)/$(FSP_PACKAGE).fdf

  #
  # UPD tool definition
  #
  FSP_T_UPD_TOOL_GUID            = 34686CA3-34F9-4901-B82A-BA630F0714C6
  FSP_M_UPD_TOOL_GUID            = 39A250DB-E465-4DD1-A2AC-E2BD3C0E2385
  FSP_S_UPD_TOOL_GUID            = CAE3605B-5B34-4C85-B3D7-27D54273C40F
  FSP_T_UPD_FFS_GUID             = 70BCF6A5-FFB1-47D8-B1AE-EFE5508E23EA
  FSP_M_UPD_FFS_GUID             = D5B86AEA-6AF7-40D4-8014-982301BC3D89
  FSP_S_UPD_FFS_GUID             = E3CD9B18-998C-4F76-B65E-98B154E5446F

  DEFINE  PCH = Ehl

################################################################################
#
# SKU Identification section - list of all SKU IDs supported by this
#                              Platform.
#
################################################################################
[SkuIds]
  0|DEFAULT              # The entry: 0|DEFAULT is reserved and always required.

################################################################################
#
# Library Class section - list of all Library Classes needed by this Platform.
#
################################################################################
[LibraryClasses.IA32]
#
# UEFI & PI
#
  PeiServicesTablePointerLib|MdePkg/Library/PeiServicesTablePointerLibIdt/PeiServicesTablePointerLibIdt.inf
  PeiServicesLib|MdePkg/Library/PeiServicesLib/PeiServicesLib.inf
  ExtractGuidedSectionLib|MdePkg/Library/PeiExtractGuidedSectionLib/PeiExtractGuidedSectionLib.inf
  PeiPolicyUpdatePreMemLib|$(FSP_PACKAGE)/Library/PeiPolicyUpdatePreMemLib/PeiPolicyUpdatePreMemLib.inf
  PeiPolicyUpdateLib|$(FSP_PACKAGE)/Library/PeiPolicyUpdateLib/PeiPolicyUpdateLib.inf
  ResetSystemLib|MdeModulePkg/Library/PeiResetSystemLib/PeiResetSystemLib.inf
  FspHelperLib|$(FSP_PACKAGE)/Library/FspHelperLib/FspHelperLib.inf
  FspSiliconCommonLib|$(FSP_PACKAGE)/Library/FspSiliconCommonLib/FspSiliconCommonLib.inf

#
# Silicon Init Pei Library
#
  PeiPcieRpLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/Library/PeiPcieRpLib/PeiPcieRpLib.inf
  SiPolicyLib|$(PLATFORM_SI_PACKAGE)/Library/PeiSiPolicyLib/PeiSiPolicyLib.inf
  SiConfigBlockLib|$(PLATFORM_SI_PACKAGE)/Library/BaseSiConfigBlockLib/BaseSiConfigBlockLib.inf
  SiFviInitLib|$(PLATFORM_SI_PACKAGE)/LibraryPrivate/PeiSiFviInitLib/PeiSiFviInitLib.inf
  PeiTraceHubLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/PeiTraceHubLib/PeiTraceHubLib.inf
  StallPpiLib|$(PLATFORM_SI_PACKAGE)/Library/PeiInstallStallPpiLib/PeiStallPpiLib.inf
  SiPolicyOverrideLib|$(PLATFORM_SI_PACKAGE)/LibraryPrivate/PeiPolicyOverrideLib/PeiSiPolicyOverrideLib.inf
  PeiSiSsidLib|$(PLATFORM_SI_PACKAGE)/LibraryPrivate/PeiSiSsidLib/PeiSiSsidLib.inf
  SiMtrrLib|$(PLATFORM_SI_PACKAGE)/Library/SiMtrrLib/SiMtrrLib.inf
  PeiTccInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcc/LibraryPrivate/PeiTccInitLib/PeiTccInitLib.inf
  PeiTccPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcc/LibraryPrivate/PeiTccPolicyLib/PeiTccPolicyLib.inf

#
# Pch
#
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  PchInitLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiPchInitLib/PeiPchInitLibFspEhl.inf
!else
  PchInitLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiPchInitLib/PeiPchInitLibFspIcl.inf
!endif
  PchPolicyLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiPchPolicyLib/PeiPchPolicyLib.inf
  SpiLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Spi/Library/PeiSpiLib/PeiSpiLib.inf
  SmbusCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Smbus/LibraryPrivate/PeiDxeSmmSmbusCommonLib/PeiDxeSmmSmbusCommonLib.inf
  SpiCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Spi/LibraryPrivate/BaseSpiCommonLib/BaseSpiCommonLib.inf
  WdtCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Wdt/LibraryPrivate/PeiDxeSmmWdtCommonLib/PeiDxeSmmWdtCommonLib.inf
  PchXhciLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiDxeSmmPchXhciLib/PeiDxeSmmPchXhciLib.inf
  PchTraceHubInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/Library/PeiDxeSmmPchTraceHubInfoLib/PeiDxeSmmPchTraceHubInfoLib.inf
  CpuTraceHubInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/Library/PeiDxeSmmCpuTraceHubInfoLib/PeiDxeSmmCpuTraceHubInfoLib.inf
!if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
  PchTraceHubLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/PeiDxeSmmPchTraceHubLib/PeiDxeSmmPchTraceHubLib.inf
  TraceHubDebugLib|$(FSP_PACKAGE)/Library/TraceHubDebugLibSvenTx/BaseTraceHubDebugLibSvenTx.inf
  TraceHubHookLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/Library/PeiDxeSmmTraceHubHookLib/PeiDxeSmmTraceHubHookLib.inf
!else
  PchTraceHubLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/BasePchTraceHubLibNull/BasePchTraceHubLibNull.inf
  TraceHubDebugLib|$(FSP_PACKAGE)/Library/TraceHubDebugLibNull/TraceHubDebugLibNull.inf
  TraceHubHookLib|$(FSP_PACKAGE)/Library/TraceHubHookLibNull/TraceHubHookLibNull.inf
!endif
  PeiCpuTraceHubPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/PeiCpuTraceHubPolicyLib/PeiCpuTraceHubPolicyLib.inf
  PeiPchTraceHubPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/PeiPchTraceHubPolicyLib/PeiPchTraceHubPolicyLib.inf
  SerialIoI2cMasterLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/I2c/Library/PeiSerialIoI2cMasterLib/PeiSerialIoI2cMasterLib.inf
  SerialIoI2cMasterCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/I2c/LibraryPrivate/PeiDxeSerialIoI2cMasterCommonLib/PeiDxeSerialIoI2cMasterCommonLib.inf
  PeiSerialIoPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/LibraryPrivate/PeiSerialIoPolicyLib/PeiSerialIoPolicyLib.inf
!if gSiPkgTokenSpaceGuid.PcdOcWdtEnable == TRUE
  OcWdtLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Wdt/Library/PeiOcWdtLib/PeiOcWdtLib.inf
!else
  OcWdtLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Wdt/Library/PeiOcWdtLibNull/PeiOcWdtLibNull.inf
!endif
  PeiSataLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sata/LibraryPrivate/PeiSataLib/PeiSataLib.inf
  PeiSataPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sata/LibraryPrivate/PeiSataPolicyLib/PeiSataPolicyLib.inf
  PeiGbeInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gbe/LibraryPrivate/PeiGbeInitLib/PeiGbeInitLib.inf
  PeiGbePolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gbe/LibraryPrivate/PeiGbePolicyLib/PeiGbePolicyLib.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  PeiTsnInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tsn/LibraryPrivate/PeiTsnInitLib/PeiTsnInitLib.inf
  PeiTsnPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tsn/LibraryPrivate/PeiTsnPolicyLib/PeiTsnPolicyLib.inf
  PeiSciInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sci/LibraryPrivate/PeiSciInitLib/PeiSciInitLib.inf
!else
  PeiTsnInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tsn/LibraryPrivate/PeiTsnInitLibNull/PeiTsnInitLibNull.inf
  PeiTsnPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tsn/LibraryPrivate/PeiTsnPolicyLibNull/PeiTsnPolicyLibNull.inf
  PeiSciInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sci/LibraryPrivate/PeiSciInitLibNull/PeiSciInitLibNull.inf
!endif
  PeiEspiInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Espi/LibraryPrivate/PeiEspiInitLib/PeiEspiInitLib.inf
  PeiSciPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sci/LibraryPrivate/PeiSciPolicyLib/PeiSciPolicyLib.inf
  PeiHsioLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiHsioLib/PeiHsioLibTgl.inf
  PeiIshLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ish/LibraryPrivate/PeiIshLib/PeiIshLibVer3.inf
  IshInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ish/Library/IshInfoLib/IshInfoLibVer3.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  PseInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pse/Library/PseInfoLib/PseInfoLib.inf
  PeiPseLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pse/LibraryPrivate/PeiPseLib/PeiPseLibVer3.inf
  PeiPsePolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pse/LibraryPrivate/PeiPsePolicyLib/PeiPsePolicyLib.inf
  PeiIshPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ish/LibraryPrivate/PeiIshPolicyLibNull/PeiIshPolicyLibNull.inf
!else
  PseInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pse/Library/PseInfoLibNull/PseInfoLibNull.inf
  PeiPsePolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pse/LibraryPrivate/PeiPsePolicyLibNull/PeiPsePolicyLibNull.inf
  PeiPseLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pse/LibraryPrivate/PeiPseLibNull/PeiPseLibNull.inf
  PeiIshPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ish/LibraryPrivate/PeiIshPolicyLib/PeiIshPolicyLib.inf
!endif
  PeiSiipPolicyLib|$(PLATFORM_SI_PACKAGE)/Library/PeiSiipPolicyLib/PeiSiipPolicyLib.inf
  PeiP2sbPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/LibraryPrivate/PeiP2sbPolicyLib/PeiP2sbPolicyLib.inf
  PeiP2sbPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/LibraryPrivate/PeiP2sbPrivateLib/PeiP2sbPrivateLibVer1.inf
  HdaLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Hda/Library/HdaLib/HdaLib.inf
  PeiSerialIoInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/LibraryPrivate/PeiSerialIoInitLib/PeiSerialIoInitLib.inf
  PeiPchPcieClocksLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/LibraryPrivate/PeiPchPcieClocksLib/PeiPchPcieClocksLib.inf
  GpioHelpersLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/PeiGpioHelpersLib/PeiGpioHelpersLib.inf
  GpioNameBufferLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/PeiGpioNameBufferLib/PeiGpioNameBufferLib.inf
  CnviLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Cnvi/Library/PeiDxeSmmCnviLib/PeiDxeSmmCnviLib.inf
  PeiCnviPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Cnvi/LibraryPrivate/PeiCnviPolicyLib/PeiCnviPolicyLib.inf
  PeiPchDmiLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PchDmi/LibraryPrivate/PeiDxeSmmPchDmiLib/PeiPchDmiLib.inf
  PeiPchDmiPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PchDmi/LibraryPrivate/PeiPchDmiPolicyLib/PeiPchDmiPolicyLib.inf
  PeiThcPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Thc/LibraryPrivate/PeiThcPolicyLib/PeiThcPolicyLib.inf
  PeiScsPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Scs/LibraryPrivate/PeiScsPolicyLib/PeiScsPolicyLib.inf
  PeiThcInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Thc/LibraryPrivate/PeiThcInitLib/PeiThcInitLib.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  PeiPmcPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pmc/LibraryPrivate/PeiDxeSmmPmcPrivateLib/PeiPmcPrivateLibVer3.inf
  PeiItssLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Itss/LibraryPrivate/PeiItssLib/PeiItssLibVer3.inf
  PeiItssPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Itss/LibraryPrivate/PeiItssPolicyLib/PeiItssPolicyLibVer3.inf
  ScsLocationLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Scs/LibraryPrivate/BaseScsLocationLib/BaseScsLocationLibVer3.inf
  PeiScsLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Scs/LibraryPrivate/PeiScsLib/PeiScsLibVer3.inf
  PeiIshInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ish/LibraryPrivate/PeiIshInitLib/PeiIshInitLibVer3.inf
  PeiCnviLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Cnvi/LibraryPrivate/PeiCnviLib/PeiCnviLibVer2.inf
  PeiPcieRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/LibraryPrivate/PeiPcieRpInitLib/PeiPcieRpInitLibVer2.inf
  PeiPseInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pse/LibraryPrivate/PeiPseInitLib/PeiPseInitLib.inf
!else
  PeiPmcPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pmc/LibraryPrivate/PeiDxeSmmPmcPrivateLib/PeiPmcPrivateLibVer1.inf
  PeiItssLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Itss/LibraryPrivate/PeiItssLib/PeiItssLibVer1.inf
  PeiItssPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Itss/LibraryPrivate/PeiItssPolicyLib/PeiItssPolicyLibVer1.inf
  ScsLocationLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Scs/LibraryPrivate/BaseScsLocationLib/BaseScsLocationLibVer1.inf
  PeiScsLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Scs/LibraryPrivate/PeiScsLib/PeiScsLibVer1.inf
  PeiIshInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ish/LibraryPrivate/PeiIshInitLib/PeiIshInitLibVer1.inf
  PeiCnviLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Cnvi/LibraryPrivate/PeiCnviLib/PeiCnviLibVer1.inf
  PeiPcieRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/LibraryPrivate/PeiPcieRpInitLib/PeiPcieRpInitLibVer1.inf
  PeiPseInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pse/LibraryPrivate/PeiPseInitLibNull/PeiPseInitLibNull.inf
!endif
  PeiRtcLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Rtc/LibraryPrivate/PeiRtcLib/PeiRtcLib.inf
  PeiRtcPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Rtc/LibraryPrivate/PeiRtcPolicyLib/PeiRtcPolicyLib.inf
  SiScheduleResetLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/BaseSiScheduleResetLib/BaseSiScheduleResetLib.inf
  PeiDciInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Dci/LibraryPrivate/PeiDciInitLib/PeiDciInitLib.inf
  SmbusInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Smbus/Library/PeiDxeSmmSmbusInfoLib/SmbusInfoLib.inf

 
  PeiSiipLib|$(PLATFORM_SI_PACKAGE)/Library/PeiSiipLib/PeiSiipLib.inf
  PeiHdaInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Hda/LibraryPrivate/PeiHdaInitLib/PeiHdaInitLib.inf
  PeiHdaLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Hda/LibraryPrivate/PeiHdaLib/PeiHdaLib.inf
  PeiHdaPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Hda/LibraryPrivate/PeiHdaPolicyLib/PeiHdaPolicyLib.inf
  PeiIehInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ieh/LibraryPrivate/PeiIehInitLib/PeiIehInitLib.inf
  PeiIehPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ieh/LibraryPrivate/PeiIehPolicyLib/PeiIehPolicyLib.inf
  PeiCpuPcieRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLib/PeiCpuPcieRpInitLib.inf
  PeiPsfLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PeiPsfLib/PeiPsfLib.inf
  PeiPsfPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PeiPsfPolicyLib/PeiPsfPolicyLib.inf
  PeiFusaLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Fusa/LibraryPrivate/PeiFusaLibNull/PeiFusaLibNull.inf
  PeiFusaPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Fusa/LibraryPrivate/PeiFusaPolicyLibNull/PeiFusaPolicyLibNull.inf

#
# Cpu
#
  CpuInitLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiCpuInitLib/PeiCpuInitLib.inf
  CpuPowerMgmtLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiCpuPowerMgmtLib/PeiCpuPowerMgmtLib.inf
  CpuCommonLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiDxeSmmCpuCommonLib/PeiDxeSmmCpuCommonLib.inf
!if gSiPkgTokenSpaceGuid.PcdTxtEnable == TRUE
  PeiTxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiTxtLib/PeiTxtLib.inf
!else
  PeiTxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiTxtLibNull/PeiTxtLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdCpuPowerOnConfigEnable == TRUE
  CpuPowerOnConfigLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiCpuPowerOnConfigLib/PeiCpuPowerOnConfigLib.inf
!else
  CpuPowerOnConfigLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiCpuPowerOnConfigLibDisable/PeiCpuPowerOnConfigLibDisable.inf
!endif
#
#
  PeiOcPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Overclocking/LibraryPrivate/PeiOcPolicyLibNull/PeiOcPolicyLibNull.inf
!if gSiPkgTokenSpaceGuid.PcdOverclockEnable == TRUE
  PeiOcLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Overclocking/LibraryPrivate/PeiOcLib/PeiOcLib.inf
  PeiOcInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Overclocking/LibraryPrivate/PeiOcInitLib/PeiOcInitLib.inf
!else
  PeiOcLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Overclocking/LibraryPrivate/PeiOcLibNull/PeiOcLibNull.inf
  PeiOcInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Overclocking/LibraryPrivate/PeiOcInitLibNull/PeiOcInitLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdBiosGuardEnable == TRUE
  BiosGuardLib|$(PLATFORM_SI_PACKAGE)/IpBlock/BiosGuard/LibraryPrivate/PeiBiosGuardLib/PeiBiosGuardLib.inf
!else
  BiosGuardLib|$(PLATFORM_SI_PACKAGE)/IpBlock/BiosGuard/LibraryPrivate/PeiBiosGuardLibNull/PeiBiosGuardLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdSmbiosEnable == TRUE
  SmbiosCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiSmbiosCpuLib/PeiSmbiosCpuLib.inf
!else
  SmbiosCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiSmbiosCpuLibNull/PeiSmbiosCpuLibNull.inf
!endif
#
# Me
#
  MeInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/LibraryPrivate/PeiMeInitLib/PeiMeInitLib.inf
  PeiMeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/PeiMeLib/PeiMeLib.inf
  PeiMePolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/PeiMePolicyLib/PeiMePolicyLib.inf
  MeFwStsLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/BaseMeFwStsLib/BaseMeFwStsLib.inf
#
# Amt
#
  AsfMsgLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Amt/LibraryPrivate/PeiDxeAsfMsgLib/PeiDxeAsfMsgLib.inf
!if gSiPkgTokenSpaceGuid.PcdAmtEnable == TRUE
  PeiAmtPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Amt/Library/PeiAmtPolicyLib/PeiAmtPolicyLib.inf
  ActiveManagementLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Amt/LibraryPrivate/PeiActiveManagementLib/PeiActiveManagementLib.inf
!else
  PeiAmtPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Amt/Library/PeiAmtPolicyLibNull/PeiAmtPolicyLibNull.inf
  ActiveManagementLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Amt/LibraryPrivate/PeiActiveManagementLibNull/PeiActiveManagementLibNull.inf
!endif

#
# SA
#
!if gSiPkgTokenSpaceGuid.PcdHgEnable == TRUE
  PeiHybridGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/HybridGraphics/LibraryPrivate/PeiHybridGraphicsInitLib/PeiHybridGraphicsInitLib.inf
  PeiHybridGraphicsPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/HybridGraphics/LibraryPrivate/PeiHybridGraphicsPolicyLib/PeiHybridGraphicsPolicyLib.inf
!else
  PeiHybridGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/HybridGraphics/LibraryPrivate/PeiHybridGraphicsInitLibNull/PeiHybridGraphicsInitLibNull.inf
  PeiHybridGraphicsPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/HybridGraphics/LibraryPrivate/PeiHybridGraphicsPolicyLibNull/PeiHybridGraphicsPolicyLibNull.inf
!endif
  PeiCpuPciePreMemRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLib/PeiCpuPciePreMemRpInitLib.inf
  SaInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaInitLib/PeiSaInitLibFspEhl.inf
  CpuPcieInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/Library/PeiDxeSmmCpuPcieInfoLib/PeiDxeSmmCpuPcieInfoLibTgl.inf
  PcieInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiPcieInitLib/PeiPcieInitLib.inf

!if (gSiPkgTokenSpaceGuid.PcdPegEnable == TRUE) OR (gSiPkgTokenSpaceGuid.PcdSaDmiEnable == TRUE)
  SaPcieDmiLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaPcieDmiLib/PeiSaPcieDmiLib.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdPegEnable == TRUE
  SaPcieInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaPcieInitLib/PeiSaPcieInitLib.inf
!else
  SaPcieInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaPcieInitLib/PeiSaPcieInitLibDisableEhl.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdSaDmiEnable == TRUE
  SaDmiInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaDmiInitLib/PeiSaDmiInitLib.inf
!else
  SaDmiInitLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/LibraryPrivate/PeiSaDmiInitLibNull/PeiSaDmiInitLibNull.inf
!endif

#
#  Telemetry
#
  TelemetryLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Telemetry/Library/PeiDxeTelemetryLibNull/PeiDxeTelemetryLibNull.inf
  TelemetryPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Telemetry/LibraryPrivate/PeiDxeTelemetryPrivateLibNull/PeiDxeTelemetryPrivateLibNull.inf
  PeiTelemetryPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Telemetry/LibraryPrivate/PeiTelemetryPolicyLibNull/PeiTelemetryPolicyLibNull.inf

#
# IPU
#
  IpuLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ipu/Library/PeiDxeSmmIpuLib/IpuLib.inf
  PeiIpuPolicyPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ipu/LibraryPrivate/PeiIpuPolicyPrivateLibNull/PeiIpuPolicyPrivateLibNull.inf
  IpuInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ipu/LibraryPrivate/PeiIpuInitPrivateLibNull/PeiIpuInitLibNull.inf

#
# Graphics
#
  PeiGraphicsPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiGraphicsPolicyLibGen11/PeiGraphicsPolicyLib.inf

!if gSiPkgTokenSpaceGuid.PcdIgdEnable == TRUE
  GraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiGraphicsInitLibGen11/PeiGraphicsInitLib.inf
  DisplayInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiDisplayInitLibGen11/PeiDisplayInitLib.inf
!else
  GraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiGraphicsDisableInitLib/PeiGraphicsDisableInitLib.inf
  DisplayInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiDisplayInitLibNull/PeiDisplayInitLibNull.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdPeiDisplayEnable == TRUE
  DisplayLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiDisplayLib/PeiDisplayLib.inf
!else
  DisplayLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/PeiDisplayLibNull/PeiDisplayLibNull.inf
!endif

#
# GNA
#
GnaInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gna/Library/PeiDxeSmmGnaInfoLib/PeiDxeSmmGnaInfoLib.inf
!if gSiPkgTokenSpaceGuid.PcdGnaEnable == TRUE
  GnaInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gna/LibraryPrivate/PeiGnaInitLib/PeiGnaInitLib.inf
  PeiGnaPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gna/LibraryPrivate/PeiGnaPolicyLib/PeiGnaPolicyLib.inf
!else
  GnaInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gna/LibraryPrivate/PeiGnaInitLibNull/PeiGnaInitLibNull.inf
  PeiGnaPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gna/LibraryPrivate/PeiGnaPolicyLibNull/PeiGnaPolicyLibNull.inf
!endif

#
# VT-D
#
VtdInfoLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vtd/Library/PeiDxeSmmVtdInfoLib/PeiDxeSmmVtdInfoLib.inf
!if gSiPkgTokenSpaceGuid.PcdVtdEnable == TRUE
  PeiVtdPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vtd/LibraryPrivate/PeiVtdPolicyLib/PeiVtdPolicyLib.inf
  VtdInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vtd/LibraryPrivate/PeiVtdInitLib/PeiVtdInitLib.inf
!else
  PeiVtdPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vtd/LibraryPrivate/PeiVtdPolicyLibNull/PeiVtdPolicyLibNull.inf
  VtdInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vtd/LibraryPrivate/PeiVtdInitLibNull/PeiVtdInitLibNull.inf
!endif

#
# PSMI
#
!if gSiPkgTokenSpaceGuid.PcdPsmiEnable == TRUE
  PeiPsmiInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psmi/LibraryPrivate/PeiPsmiInitLib/PeiPsmiInitLib.inf
!else
  PeiPsmiInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psmi/LibraryPrivate/PeiPsmiInitLibNull/PeiPsmiInitLibNull.inf
!endif

  PeiPcieRpPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/LibraryPrivate/PeiPcieRpPolicyLib/PeiPcieRpPolicyLib.inf
  MemoryInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/MemoryInit/Icl/LibraryPrivate/PeiMemoryInitLib/PeiMemoryInitLibFsp.inf

  MemoryAddressEncodeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/MemoryInit/Icl/Library/PeiDxeSmmMemAddrEncodeLib/PeiDxeSmmMemAddrEncodeLib.inf
  PeiCpuTraceHubLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/PeiCpuTraceHubLib/PeiCpuTraceHubLib.inf
  PeiTcssPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/LibraryPrivate/PeiTcssPolicyLibNull/PeiTcssPolicyLibNull.inf
  TcssPmcLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/LibraryPrivate/PeiTcssPmcLibNull/PeiTcssPmcLibNull.inf

  PeiTcssInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/LibraryPrivate/PeiTcssInitLibNull/PeiTcssInitLibNull.inf


#
# Cpu
#
  CpuPolicyLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiCpuPolicyLib/PeiCpuPolicyLib.inf
#
# System Agent
#
  PeiSaPolicyLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiSaPolicyLib/PeiSaPolicyLibFsp.inf
  PeiMemPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/MemoryInit/Icl/Library/PeiMemPolicyLib/PeiMemPolicyLibFsp.inf

#
# TBT
#
  PeiITbtPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/PeiITbtPolicyLibNull/PeiITbtPolicyLibNull.inf

  TbtCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/PeiDxeSmmTbtCommonLib/TbtCommonLib.inf
  SmmTbtCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/SmmTbtCommonLib/SmmTbtCommonLib.inf
  DxeTbtDisBmeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/DxeTbtDisBmeLib/DxeTbtDisBmeLib.inf
!if gSiPkgTokenSpaceGuid.PcdITbtEnable == TRUE
  PeiTbtTaskDispatchLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/PeiTbtTaskDispatchLib/PeiTbtTaskDispatchLib.inf
  PeiITbtInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/LibraryPrivate/PeiITbtInitLib/PeiITbtInitLib.inf
!else
  PeiTbtTaskDispatchLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/Library/PeiTbtTaskDispatchLibNull/PeiTbtTaskDispatchLibNull.inf
  PeiDTbtInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/LibraryPrivate/PeiDTbtInitLibNull/PeiDTbtInitLibNull.inf
  PeiITbtInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tbt/LibraryPrivate/PeiITbtInitLibNull/PeiITbtInitLibNull.inf
!endif

[LibraryClasses]
  #
  # Entry point
  #
  PeiCoreEntryPoint|MdePkg/Library/PeiCoreEntryPoint/PeiCoreEntryPoint.inf
  PeimEntryPoint|MdePkg/Library/PeimEntryPoint/PeimEntryPoint.inf
  #
  # Basic
  #
  DebugPrintErrorLevelLib|$(FSP_PACKAGE)/Library/DebugPrintErrorLevelLib/FspDebugPrintErrorLevelLib.inf
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
  PciExpressLib|$(PLATFORM_SI_PACKAGE)/Library/BasePciExpressMultiSegLib/BasePciExpressMultiSegLib.inf
  PciSegmentLib|$(PLATFORM_SI_PACKAGE)/Library/BasePciSegmentMultiSegLibPci/BasePciSegmentMultiSegLibPci.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLibRepStr/BaseMemoryLibRepStr.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
  CacheMaintenanceLib|MdePkg/Library/BaseCacheMaintenanceLib/BaseCacheMaintenanceLib.inf
  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf
  PeCoffExtraActionLib|MdePkg/Library/BasePeCoffExtraActionLibNull/BasePeCoffExtraActionLibNull.inf
  UefiDecompressLib|MdePkg/Library/BaseUefiDecompressLib/BaseUefiDecompressLib.inf
  SynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf
  CpuLib|MdePkg/Library/BaseCpuLib/BaseCpuLib.inf
  PreSiliconEnvDetectLib|$(PLATFORM_SI_PACKAGE)/Library/BasePreSiliconEnvDetectLib/BasePreSiliconEnvDetectLib.inf

  #
  # Generic Modules
  #
  OemHookStatusCodeLib|MdeModulePkg/Library/OemHookStatusCodeLibNull/OemHookStatusCodeLibNull.inf

  #
  # Misc
  #
  MtrrLib|UefiCpuPkg/Library/MtrrLib/MtrrLib.inf
  LocalApicLib|UefiCpuPkg/Library/BaseXApicX2ApicLib/BaseXApicX2ApicLib.inf
  ### Base on debug/release mode, choose one of the DebugLib
  ####  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
  SerialIoUartDebugPropertyPcdLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Uart/Library/SerialIoUartDebugPropertyPcdLib/SerialIoUartDebugPropertyPcdLib.inf
  FspSerialIoUartDebugHelperLib|$(FSP_PACKAGE)/Library/FspSerialIoUartDebugHelperLib/FspSerialIoUartDebugHelperLib.inf
  UefiCpuLib|UefiCpuPkg/Library/BaseUefiCpuLib/BaseUefiCpuLib.inf
  CpuExceptionHandlerLib|UefiCpuPkg/Library/CpuExceptionHandlerLib/SecPeiCpuExceptionHandlerLib.inf
  MpInitLib|$(PLATFORM_FULL_PACKAGE)/Override/UefiCpuPkg/Library/MpInitLib/PeiMpInitLib.inf
!if gElkhartLakeFspPkgTokenSpaceGuid.PcdMonoStatusCode == TRUE
  MonoStatusCodeLib|$(FSP_PACKAGE)/Library/MonoStatusCode/MonoStatusCode.inf
!else
  MonoStatusCodeLib|$(FSP_PACKAGE)/Library/MonoStatusCodeNull/MonoStatusCodeNull.inf
!endif
  UsbLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Usb/Library/PeiDxeSmmUsbLib/PeiDxeSmmUsbLib.inf

  UsbHostControllerInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Usb/LibraryPrivate/PeiUsbHostControllerInitLib/PeiUsbHostControllerInitLib.inf
  UsbDeviceControllerInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Usb/LibraryPrivate/PeiUsbDeviceControllerInitLib/PeiUsbDeviceControllerInitLib.inf
  PeiUsbPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Usb/LibraryPrivate/PeiUsbPolicyLib/PeiUsbPolicyLib.inf
  FspInfoLib|$(FSP_PACKAGE)/Library/FspInfoLib/FspInfoLib.inf
  SpiAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Spi/Library/PeiDxeSmmSpiAccessLib/PeiDxeSmmSpiAccessLib.inf
  SpiAccessPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Spi/LibraryPrivate/PeiDxeSmmSpiAccessPrivateLib/PeiDxeSmmSpiAccessPrivateLib.inf
  MmPciLib|$(PLATFORM_SI_PACKAGE)/Library/PeiDxeSmmMmPciLib/PeiDxeSmmMmPciLib.inf
  PeiCpuPsfInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PeiCpuPsfInitLibNull/PeiCpuPsfInitLibNull.inf

#
#  TwoLm IpBlock
#
  TwoLmLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/Library/PeiDxeSmmTwoLmLib/PeiDxeSmmTwoLmLib.inf
!if gSiPkgTokenSpaceGuid.Pcd2lmEnable == TRUE
  FmssMbLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/LibraryPrivate/FmssMbLib/FmssMbLib.inf
  TwoLmInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/LibraryPrivate/TwoLmInitLib/TwoLmInitLib.inf
  TwoLmPreMemPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/LibraryPrivate/TwoLmPreMemPolicyLib/TwoLmPreMemPolicyLib.inf
!else
  TwoLmInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/LibraryPrivate/TwoLmInitLibNull/TwoLmInitLibNull.inf
  TwoLmPreMemPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TwoLm/LibraryPrivate/TwoLmPreMemPolicyLibNull/TwoLmPreMemPolicyLibNull.inf
!endif

  #
  #  VMD IpBlock
  #
!if gSiPkgTokenSpaceGuid.PcdVmdEnable == TRUE
  PeiVmdInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vmd/LibraryPrivate/PeiVmdInitLib/PeiVmdInitLib.inf
  PeiVmdPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vmd/LibraryPrivate/PeiVmdPolicyLib/PeiVmdPolicyLib.inf
!else
  PeiVmdInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vmd/LibraryPrivate/PeiVmdInitLibNull/PeiVmdInitLibNull.inf
  PeiVmdPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vmd/LibraryPrivate/PeiVmdPolicyLibNull/PeiVmdPolicyLibNull.inf
!endif

  #
  # Silicon library
  #
  ConfigBlockLib|$(CLIENT_SILICON_PACKAGE)/Library/BaseConfigBlockLib/BaseConfigBlockLib.inf
  SerialPortLib|MdeModulePkg/Library/BaseSerialPortLib16550/BaseSerialPortLib16550.inf
  PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf

  #
  # Pch
  #
  GpioHelpersLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/BaseGpioHelpersLibNull/BaseGpioHelpersLibNull.inf
  GpioLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/Library/PeiDxeSmmGpioLib/PeiDxeSmmGpioLib.inf
  GpioCheckConflictLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/Library/BaseGpioCheckConflictLib/BaseGpioCheckConflictLib.inf
  DciPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Dci/LibraryPrivate/PeiDxeSmmDciPrivateLib/PeiDxeSmmDciPrivateLibVer2.inf
  SerialIoAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Library/PeiDxeSmmSerialIoAccessLib/PeiDxeSmmSerialIoAccessLib.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  GpioPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/PeiDxeSmmGpioPrivateLib/PeiDxeSmmGpioPrivateLibVer3.inf
  PchInfoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchInfoLib/PeiDxeSmmPchInfoLibEhl.inf
  SataLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sata/Library/PeiDxeSmmSataLib/PeiDxeSmmSataLibVer2.inf
  PmcPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pmc/LibraryPrivate/PeiDxeSmmPmcPrivateLib/PeiDxeSmmPmcPrivateLibVer3.inf
  PchFiaLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Fia/LibraryPrivate/PeiPchFiaLib/PeiPchFiaLibVer3.inf
  SerialIoPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/LibraryPrivate/PeiDxeSmmSerialIoPrivateLib/PeiDxeSmmSerialIoPrivateLibVer3.inf
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  PsfLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PsfLib/PeiDxeSmmPsfLibVer3Bfx.inf
!else
  PsfLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PsfLib/PeiDxeSmmPsfLibVer3.inf
!endif
!else
  GpioPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/PeiDxeSmmGpioPrivateLib/PeiDxeSmmGpioPrivateLibVer1.inf
  PchInfoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchInfoLib/PeiDxeSmmPchInfoLibJsl.inf
  SataLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sata/Library/PeiDxeSmmSataLib/PeiDxeSmmSataLibVer1.inf
  PmcPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pmc/LibraryPrivate/PeiDxeSmmPmcPrivateLib/PeiDxeSmmPmcPrivateLibVer1.inf
  PchFiaLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Fia/LibraryPrivate/PeiPchFiaLib/PeiPchFiaLibVer1.inf
  SerialIoPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/LibraryPrivate/PeiDxeSmmSerialIoPrivateLib/PeiDxeSmmSerialIoPrivateLibVer1.inf
  PsfLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PsfLib/PeiDxeSmmPsfLibVer1.inf
!endif
  PchCycleDecodingLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchCycleDecodingLib/PeiDxeSmmPchCycleDecodingLib.inf
  GbeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gbe/Library/PeiDxeSmmGbeLib/PeiDxeSmmGbeLib.inf
  GbeMdiLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gbe/LibraryPrivate/PeiDxeSmmGbeMdiLib/PeiDxeSmmGbeMdiLib.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  TsnLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tsn/Library/PeiDxeSmmTsnLib/PeiDxeSmmTsnLib.inf
!else
  TsnLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tsn/Library/PeiDxeSmmTsnLibNull/PeiDxeSmmTsnLibNull.inf
!endif
  EspiLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Espi/Library/PeiDxeSmmEspiLib/PeiDxeSmmEspiLib.inf
  EspiAccessPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Espi/LibraryPrivate/PeiDxeSmmEspiAccessPrivateLib/PeiDxeSmmEspiAccessPrivateLib.inf
  PeiEspiPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Espi/LibraryPrivate/PeiEspiPolicyLib/PeiEspiPolicyLib.inf
  PchPcrLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/Library/PeiDxeSmmPchPcrLib/PeiDxeSmmPchPcrLib.inf
  PmcLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pmc/Library/PeiDxeSmmPmcLib/PeiDxeSmmPmcLib.inf
  PmcPrivateLibWithS3|$(PLATFORM_SI_PACKAGE)/IpBlock/Pmc/LibraryPrivate/PeiDxeSmmPmcPrivateLib/PeiDxeSmmPmcPrivateLibWithS3.inf
  PchSbiAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/LibraryPrivate/PeiDxeSmmPchSbiAccessLib/PeiDxeSmmPchSbiAccessLib.inf
  SerialIoUartLib|$(PLATFORM_SI_PACKAGE)/IpBlock/SerialIo/Uart/Library/PeiDxeSmmSerialIoUartLib/PeiDxeSmmSerialIoUartLib.inf
  PchDmiLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PchDmi/LibraryPrivate/PeiDxeSmmPchDmiLib/PeiDxeSmmPchDmiLib.inf
  PchDmiWithS3Lib|$(PLATFORM_SI_PACKAGE)/IpBlock/PchDmi/LibraryPrivate/PeiDxeSmmPchDmiLib/PeiDxeSmmPchDmiWithS3Lib.inf
  SmbusLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Smbus/LibraryPrivate/BaseSmbusLib/BaseSmbusLib.inf
  PchPcieRpLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/Library/PeiDxeSmmPchPcieRpLib/PeiDxeSmmPchPcieRpLib.inf
  PciExpressHelpersLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/LibraryPrivate/PciExpressHelpersLibrary/PeiDxeSmmPciExpressHelpersLib.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  SciLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sci/Library/PeiDxeSmmSciLib/PeiDxeSmmSciLib.inf
  TccLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcc/Library/PeiDxeSmmTccLib/PeiDxeSmmTccLibEhl.inf
!else
  SciLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sci/Library/PeiDxeSmmSciLibNull/PeiDxeSmmSciLibNull.inf
!endif
  Usb2PhyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Usb/LibraryPrivate/PeiUsb2PhyLib/PeiUsb2PhyLib.inf

  #
  # Me
  #
  MeTypeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/PeiDxeMeTypeLib/PeiDxeMeTypeLib.inf
  HeciInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/LibraryPrivate/PeiDxeHeciInitLib/PeiDxeHeciInitLib.inf
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  HeciContextLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/BaseHeciContextLib/BaseHeciContextLib.inf
  MeChipsetLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/PeiDxeMeChipsetLib/PeiDxeMeChipsetLibBfx.inf
!else
  MeChipsetLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/PeiDxeMeChipsetLib/PeiDxeMeChipsetLib.inf
!endif
  MeShowBufferLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/PeiDxeMeShowBufferLib/PeiDxeMeShowBufferLib.inf

  #
  # CPU
  #
  BootGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmBootGuardLib/PeiDxeSmmBootGuardLib.inf
  CpuPlatformLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmCpuPlatformLib/PeiDxeSmmCpuPlatformLib.inf
  CpuMailboxLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeSmmCpuMailboxLib/PeiDxeSmmCpuMailboxLib.inf

  #
  # SA
  #
  SaPlatformLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/PeiDxeSmmSaPlatformLib/PeiDxeSmmSaPlatformLib.inf

[LibraryClasses.IA32.SEC]
  MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
  PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
  TimerLib|$(FSP_PACKAGE)/Library/TscAcpiTimerLib/SecTscTimerLib.inf
  SecFspSiliconLib|$(FSP_PACKAGE)/Library/SecFspSiliconLib/SecFspSiliconLib.inf
  SecGetFsptApiParameterLib|$(PLATFORM_SI_PACKAGE)/Library/SecGetFsptApiParameterLib/SecGetFsptApiParameterLib.inf
!if $(TARGET) == DEBUG
  SecSerialPortLib|$(FSP_PACKAGE)/Library/SecSerialPortInitLib/SecSerialPortInitLib.inf
!else
  SecSerialPortLib|$(FSP_PACKAGE)/Library/SecSerialPortInitLib/SecSerialPortInitLibNull.inf
!endif

[LibraryClasses.IA32.SEC,LibraryClasses.IA32.PEI_CORE]
  ResetSystemLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/BaseResetSystemLib/BaseResetSystemLib.inf
!if $(TARGET) == DEBUG
  DebugLib|$(FSP_PACKAGE)/Library/BaseDebugLibDebugPort/BaseDebugLibDebugPort.inf
!else
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
!endif

[LibraryClasses.IA32.PEIM]
!if $(TARGET) == DEBUG
  DebugLib|$(FSP_PACKAGE)/Library/FspDebugLibService/FspDebugLibService.inf
!else
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
!endif
  BootMediaLib|$(PLATFORM_SI_PACKAGE)/Library/PeiDxeSmmBootMediaLib/PeiBootMediaLib.inf
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  CseVariableStorageStatusLib|$(PLATFORM_SI_PACKAGE)/VariableStorage/LibraryPrivate/PeiDxeSmmCseVariableStorageStatusLib/PeiCseVariableStorageStatusLib.inf
!endif

[LibraryClasses.IA32.PEIM,LibraryClasses.IA32.PEI_CORE]
  PciLib|MdePkg/Library/BasePciLibPciExpress/BasePciLibPciExpress.inf
  TimerLib|$(FSP_PACKAGE)/Library/TscAcpiTimerLib/PeiTscTimerLib.inf

[LibraryClasses.IA32.PEIM,LibraryClasses.IA32.PEI_CORE,LibraryClasses.IA32.SEC]
  #
  # SEC and PEI phase common
  #
  S3BootScriptLib|MdePkg/Library/BaseS3BootScriptLibNull/BaseS3BootScriptLibNull.inf
  PcdLib|MdePkg/Library/PeiPcdLib/PeiPcdLib.inf
  HobLib|MdePkg/Library/PeiHobLib/PeiHobLib.inf
  FspSwitchStackLib|IntelFsp2Pkg/Library/BaseFspSwitchStackLib/BaseFspSwitchStackLib.inf
  SecPlatformLib|$(PLATFORM_SI_PACKAGE)/Library/PlatformSecLib/FspTPlatformSecLibEhl.inf
  SecCpuLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/SecCpuLib/SecCpuLibFsp.inf
  SecPchLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/SecPchLib/SecPchLibFsp.inf
  SecSaLib|$(PLATFORM_SI_PACKAGE)/SystemAgent/Library/SecSaLib/SecSaLib.inf
  CacheAsRamLib|$(PLATFORM_SI_PACKAGE)/Library/BaseCacheAsRamLib/BaseCacheAsRamLib.inf
  FspCommonLib|IntelFsp2Pkg/Library/BaseFspCommonLib/BaseFspCommonLib.inf
  FspPlatformLib|IntelFsp2Pkg/Library/BaseFspPlatformLib/BaseFspPlatformLib.inf
  BaseBfxTempRamLib|$(PLATFORM_SI_PACKAGE)/Library/BaseBfxTempRamLib/BaseBfxTempRamLib.inf

!if $(TARGET) == DEBUG
  SerialPortLib|$(FSP_PACKAGE)/Library/SerialPortLib/SerialPortLib.inf
!else
  SerialPortLib|MdePkg/Library/BaseSerialPortLibNull/BaseSerialPortLibNull.inf
!endif

  MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
!if gSiPkgTokenSpaceGuid.PcdSpiPostCode == TRUE
  PostCodeLib|ClientSiliconPkg/Library/BasePostCodeSpiLib/BasePostCodeLibSpiFsp.inf
!else
  PostCodeLib|$(FSP_PACKAGE)/Library/BasePostCodeLibPort80Ex/BasePostCodeLibPort80Ex.inf
!endif
  ReportStatusCodeLib|MdeModulePkg/Library/PeiReportStatusCodeLib/PeiReportStatusCodeLib.inf
  PerformanceLib|MdeModulePkg/Library/PeiPerformanceLib/PeiPerformanceLib.inf

  #
  # Silicon initialization library
  #
  BasePcieHelperLib|$(PLATFORM_SI_PACKAGE)/IpBlock/PcieRp/Library/BasePcieHelperLib/BasePcieHelperLib.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  PeiRstPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Rst/LibraryPrivate/PeiRstPolicyLib/PeiRstPolicyLibNull.inf
  RstCrLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Rst/Library/PeiDxeSmmRstCrLib/PeiDxeSmmRstCrLibVer2.inf
!else
  PeiRstPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Rst/LibraryPrivate/PeiRstPolicyLib/PeiRstPolicyLibVer1.inf
  PeiRstPrivateLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Rst/LibraryPrivate/PeiRstPrivateLib/PeiRstPrivateLib.inf
  RstCrLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Rst/Library/PeiDxeSmmRstCrLib/PeiDxeSmmRstCrLibVer1.inf
!endif
  CpuPcieInitCommonLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/Library/PeiDxeSmmCpuPcieInitCommonLib/PeiDxeSmmCpuPcieInitCommonLib.inf
  PeiDciPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Dci/LibraryPrivate/PeiDciPolicyLib/PeiDciPolicyLib.inf
  ThcLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Thc/Library/PeiDxeSmmThcLib/PeiDxeSmmThcLib.inf
  CpuPcieRpLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/Library/PeiDxeSmmCpuPcieRpLib/PeiDxeSmmCpuPcieRpLib.inf
  PeiPmcPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Pmc/LibraryPrivate/PeiPmcPolicyLib/PeiPmcPolicyLib.inf
  CpuSbiAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/Library/PeiDxeSmmCpuSbiAccessLib/PeiDxeSmmCpuSbiAccessLib.inf


  ItbtPcieRpLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/DxeItbtPcieRpLibNull/DxeItbtPcieRpLibNull.inf
  DxeTcssInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/LibraryPrivate/DxeTcssInitLib/DxeTcssInitLib.inf

  #
  #  CPU PCIe IpBlock
  #
!if gSiPkgTokenSpaceGuid.PcdCpuPcieEnable == TRUE
  PeiCpuPciePreMemRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLib/PeiCpuPciePreMemRpInitLib.inf
  PeiCpuPcieRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLib/PeiCpuPcieRpInitLib.inf
  DekelInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieDekelInitLib/PeiCpuPcieDekelInitLib.inf
  PeiCpuPciePolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPciePolicyLib/PeiCpuPciePolicyLib.inf
!else
  PeiCpuPciePreMemRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLibNull/PeiCpuPciePreMemRpInitLibNull.inf
  PeiCpuPcieRpInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieRpInitLibNull/PeiCpuPcieRpInitLibNull.inf
  DekelInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPcieDekelInitLibNull/PeiCpuPcieDekelInitLibNull.inf
  PeiCpuPciePolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/LibraryPrivate/PeiCpuPciePolicyLibNull/PeiCpuPciePolicyLibNull.inf
!endif

  PchPseIoLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/PeiDxeSmmPchPseIoLib/PeiDxeSmmPchPseIoLibEhl.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  PsfLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PsfLib/PeiDxeSmmPsfLibVer3Bfx.inf
!else
  PsfLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PsfLib/PeiDxeSmmPsfLibVer3.inf
!endif
!else
  PsfLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Psf/LibraryPrivate/PsfLib/PeiDxeSmmPsfLibVer1.inf
!endif
  PeiThermalLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Thermal/LibraryPrivate/PeiThermalLib/PeiThermalLib.inf
  PeiThermalPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Thermal/LibraryPrivate/PeiThermalPolicyLib/PeiThermalPolicyLib.inf

  PeiSmbusLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Smbus/LibraryPrivate/PeiSmbusLib/PeiSmbusLib.inf
  PeiSmbusPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Smbus/LibraryPrivate/PeiSmbusPolicyLib/PeiSmbusPolicyLib.inf
  PeiWdtLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Wdt/LibraryPrivate/PeiWdtLib/PeiWdtLib.inf
  PeiWdtPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Wdt/LibraryPrivate/PeiWdtPolicyLib/PeiWdtPolicyLib.inf
  PeiLpcLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/PeiLpcLib/PeiLpcLib.inf

  SoftwareGuardLib|$(PLATFORM_SI_PACKAGE)/Cpu/LibraryPrivate/PeiDxeSoftwareGuardLib/PeiDxeSoftwareGuardLib.inf
  TxtLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiDxeTxtLib/PeiDxeTxtLib.inf
  RngLib|MdePkg/Library/BaseRngLib/BaseRngLib.inf
  CpuRegbarAccessLib|$(PLATFORM_SI_PACKAGE)/IpBlock/P2sb/Library/PeiDxeSmmCpuRegbarAccessLib/PeiDxeSmmCpuRegbarAccessLib.inf

[LibraryClasses.X64]
  #
  # DXE phase common
  #
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
  PciLib|MdePkg/Library/BasePciLibPciExpress/BasePciLibPciExpress.inf
  TimerLib|$(FSP_PACKAGE)/Library/TscAcpiTimerLib/DxeTscTimerLib.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  DxeServicesTableLib|MdePkg/Library/DxeServicesTableLib/DxeServicesTableLib.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  LockBoxLib|MdeModulePkg/Library/SmmLockBoxLib/SmmLockBoxDxeLib.inf
!if gElkhartLakeFspPkgTokenSpaceGuid.PcdFspPerformanceEnable == TRUE
  PerformanceLib|MdeModulePkg/Library/DxePerformanceLib/DxePerformanceLib.inf
!else
  PerformanceLib|MdePkg/Library/BasePerformanceLibNull/BasePerformanceLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdSpiPostCode == TRUE
  PostCodeLib|ClientSiliconPkg/Library/BasePostCodeSpiLib/BasePostCodeLibSpi.inf
!else
  PostCodeLib|MdePkg/Library/BasePostCodeLibPort80/BasePostCodeLibPort80.inf
!endif
  #
  # UEFI & PI
  #
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  #
  # Framework
  #
  S3BootScriptLib|MdeModulePkg/Library/PiDxeS3BootScriptLib/DxeS3BootScriptLib.inf
  #
  # Silicon initialization library
  #
  DxeMeLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Me/Library/DxeMeLib/DxeMeLib.inf
  PciExpressLib|$(PLATFORM_SI_PACKAGE)/Library/FspPciExpressMultiSegLib/FspPciExpressMultiSegLib.inf
  GpioNameBufferLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Gpio/LibraryPrivate/DxeGpioNameBufferLib/DxeGpioNameBufferLib.inf
  ResetSystemLib|MdeModulePkg/Library/DxeResetSystemLib/DxeResetSystemLib.inf
  SiScheduleResetLib|$(PLATFORM_SI_PACKAGE)/Pch/LibraryPrivate/BaseSiScheduleResetLib/BaseSiScheduleResetLib.inf

################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################
[PcdsFeatureFlag.common]

[PcdsFixedAtBuild]
!if $(TARGET) == DEBUG
  gElkhartLakeFspPkgTokenSpaceGuid.PcdMrcDebugMsg           | 0x02
!else
  gElkhartLakeFspPkgTokenSpaceGuid.PcdMrcDebugMsg           | 0x00
!endif

  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask             | 0x27

  gIntelFsp2PkgTokenSpaceGuid.PcdTemporaryRamBase           | 0xFEF00000
  gIntelFsp2PkgTokenSpaceGuid.PcdTemporaryRamSize           | 0x00080000

!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  gIntelFsp2PkgTokenSpaceGuid.PcdFspReservedMemoryLength    | 0x00500000
  gIntelFsp2PkgTokenSpaceGuid.PcdFspTemporaryRamSize        | 0x00030000
!else
  gIntelFsp2PkgTokenSpaceGuid.PcdFspReservedMemoryLength    | 0x003B0000
  gIntelFsp2PkgTokenSpaceGuid.PcdFspTemporaryRamSize        | 0x00040000
!endif
  gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress         | 0xC0000000

  gElkhartLakeFspPkgTokenSpaceGuid.PcdStatusCodeFlags       | 0x32

!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == FALSE
## EDK2 master has removed these PCDs.
  gEfiMdeModulePkgTokenSpaceGuid.PcdPeiCoreMaxPeimPerFv     | 64
  gEfiMdeModulePkgTokenSpaceGuid.PcdPeiCoreMaxFvSupported   | 50
  gEfiMdeModulePkgTokenSpaceGuid.PcdPeiCoreMaxPpiSupported  | 255
!endif

  # This defines how much space will be used for heap in FSP temporary memory
  # x % of FSP temporary memory will be used for heap
  # (100 - x) % of FSP temporary memory will be used for stack
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  gIntelFsp2PkgTokenSpaceGuid.PcdFspHeapSizePercentage      | 50
!else
  gIntelFsp2PkgTokenSpaceGuid.PcdFspHeapSizePercentage      | 0
!endif

  # This is a platform specific global pointer used by FSP
  gIntelFsp2PkgTokenSpaceGuid.PcdGlobalDataPointerAddress   | 0xFED00148

  # Override PcdFspMaxPatchEntry to match FspHeader.aslc
  gIntelFsp2PkgTokenSpaceGuid.PcdFspMaxPatchEntry           | 0x02

  ## Indicates if to shadow PEIM on S3 boot path after memory is ready.<BR><BR>
  #   TRUE  - Shadow PEIM on S3 boot path after memory is ready.<BR>
  #   FALSE - Not shadow PEIM on S3 boot path after memory is ready.<BR>
  # @Prompt Shadow Peim On S3 Boot.
  gEfiMdeModulePkgTokenSpaceGuid.PcdShadowPeimOnS3Boot|TRUE

  # Temp solution to avoid halt in PeiVariable->GetVariable (PeiGetVariable)
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase               |0xFFF80000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableSize               |0x10000

  ## Specifies the number of variable MTRRs reserved for OS use. The default number of
  #  MTRRs reserved for OS use is 0.
  # @Prompt Number of reserved variable MTRRs.
  gUefiCpuPkgTokenSpaceGuid.PcdCpuNumberOfReservedVariableMtrrs|0x0

  ## Specifies timeout value in microseconds for the BSP to detect all APs for the first time.
  # @Prompt Timeout for the BSP to detect all APs for the first time.
  gUefiCpuPkgTokenSpaceGuid.PcdCpuApInitTimeOutInMicroSeconds|10000

!if gElkhartLakeFspPkgTokenSpaceGuid.PcdFspPerformanceEnable == TRUE
  gEfiMdePkgTokenSpaceGuid.PcdPerformanceLibraryPropertyMask|0x1
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxPeiPerformanceLogEntries|140
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxPeiPerformanceLogEntriesPerHob|60
!endif

!if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
  gElkhartLakeFspPkgTokenSpaceGuid.PcdTraceHubDebugLibMaster |0x48
  gElkhartLakeFspPkgTokenSpaceGuid.PcdTraceHubDebugLibChannel|0xE
!endif

  # Use to override gEfiMdeModulePkgTokenSpaceGuid.PcdPeiCoreMaxPeiStackSize
  gEfiMdeModulePkgTokenSpaceGuid.PcdPeiCoreMaxPeiStackSize|0x40000
!if $(TARGET) == RELEASE
  gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|3
!else
  gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|7
!endif

[PcdsPatchableInModule]
!if $(TARGET) == DEBUG
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel         | 0x80000042
!else
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel         | 0x00000001
!endif
  gSiPkgTokenSpaceGuid.PcdRegBarBaseAddress                | 0xFB000000
  #
  # This entry will be patched during the build process
  #
  gEfiMdeModulePkgTokenSpaceGuid.PcdVpdBaseAddress         | 0x12345678

[PcdsDynamicDefault]
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  gSiPkgTokenSpaceGuid.PcdEnableCseVariableStorage|TRUE
  gSiPkgTokenSpaceGuid.PcdEnableFvbVariableStorage|FALSE
!else
  gSiPkgTokenSpaceGuid.PcdEnableCseVariableStorage|FALSE
  gSiPkgTokenSpaceGuid.PcdEnableFvbVariableStorage|TRUE
!endif

[PcdsDynamicExDefault]
  #
  # Include FSP PCD settings.
  #
  !include $(FSP_PACKAGE)/ElkhartLakeFspPcds.dsc

  gEfiMdeModulePkgTokenSpaceGuid.PcdS3BootScriptTablePrivateDataPtr|0x0
  gEfiMdeModulePkgTokenSpaceGuid.PcdS3BootScriptTablePrivateSmmDataPtr|0x0


!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  gSiPkgTokenSpaceGuid.PcdEnableCseVariableStorage|TRUE
  gSiPkgTokenSpaceGuid.PcdEnableFvbVariableStorage|FALSE
!endif
  gSiPkgTokenSpaceGuid.PcdNvVariableEmulationMode|FALSE

[PcdsDynamicVpd.Upd]
  #
  # This section is not used by the normal build process
  # Howerver, FSP will use dedicated tool to handle it and generate a
  # VPD simliar binary block (User Configuration Data). This block will
  # be accessed through a generated data structure directly rather than
  # PCD services. This is for size consideration.
  # Format:
  #   gPlatformFspPkgTokenSpaceGuid.Updxxxxxxxxxxxxn        | OFFSET | LENGTH | VALUE
  # Only simple data type is supported
  #

  # offset 0000 ~ 00B0
  !include $(FSP_PACKAGE)/Upd/FsptUpd.dsc

  # offset 0000 ~ 06AE
  !include $(FSP_PACKAGE)/Upd/FspmUpd.dsc

  # offset 0000 ~ 0D10
  !include $(FSP_PACKAGE)/Upd/FspsUpd.dsc

###################################################################################################
#
# Components Section - list of the modules and components that will be processed by compilation
#                      tools and the EDK II tools to generate PE32/PE32+/Coff image files.
#
# Note: The EDK II DSC file is not used to specify how compiled binary images get placed
#       into firmware volume images. This section is just a list of modules to compile from
#       source into UEFI-compliant binaries.
#       It is the FDF file that contains information on combining binary files into firmware
#       volume images, whose concept is beyond UEFI and is described in PI specification.
#       Binary modules do not need to be listed in this section, as they should be
#       specified in the FDF file. For example: Shell binary (Shell_Full.efi), FAT binary (Fat.efi),
#       Logo (Logo.bmp), and etc.
#       There may also be modules listed in this section that are not required in the FDF file,
#       When a module listed here is excluded from FDF file, then UEFI-compliant binary will be
#       generated for it, but the binary will not be put into any firmware volume.
#
###################################################################################################

[Components.IA32]
  #
  # SEC
  #
  $(FSP_PACKAGE)/Override/IntelFsp2Pkg/FspSecCore/FspSecCoreT.inf { # FSPO-0009
    <LibraryClasses>
      MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
      PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
      FspSecPlatformLib|$(PLATFORM_SI_PACKAGE)/Library/PlatformSecLib/FspTPlatformSecLibEhl.inf
  }
!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == FALSE
  $(FSP_PACKAGE)/Override/IntelFsp2Pkg/FspSecCore/FspSecCoreM.inf { # FSPO-0009
    <LibraryClasses>
      MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
      PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
      FspSecPlatformLib|$(PLATFORM_SI_PACKAGE)/Library/PlatformSecLib/FspMPlatformSecLibEhl.inf
  }
!else
  IntelFsp2Pkg/FspSecCore/FspSecCoreM.inf {
    <LibraryClasses>
      MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
      PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
      FspSecPlatformLib|$(PLATFORM_SI_PACKAGE)/Library/PlatformSecLib/FspMPlatformSecLib.inf
  }
!endif
  $(FSP_PACKAGE)/Override/IntelFsp2Pkg/FspSecCore/FspSecCoreS.inf { # FSPO-0009
    <LibraryClasses>
      MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
      PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
      FspSecPlatformLib|$(PLATFORM_SI_PACKAGE)/Library/PlatformSecLib/FspSPlatformSecLibEhl.inf
  }

  #
  # PEI Core
  #
!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == TRUE
  #
  # EDK2 master has removed PcdPeiCoreMaxPeimPerFv, PcdPeiCoreMaxFvSupported
  # and PcdPeiCoreMaxPpiSupported.
  # The override PeiMain is still using these PCDs, there will be build failure
  # if it is used for edk2 master build. So here is to use non-override PeiMain
  # for edk2 master build.
  #
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(FSP_PACKAGE)/Override/MdeModulePkg/Core/Pei201903/PeiMain.inf {
      <LibraryClasses>
        !if $(TARGET) == DEBUG
          DebugLib|$(FSP_PACKAGE)/Library/BaseDebugLibDebugPort/BaseDebugLibDebugPort.inf
        !endif
        MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
        PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
      <PcdsFixedAtBuild>
        gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x27
    }
  !else
    MdeModulePkg/Core/Pei/PeiMain.inf {
      <LibraryClasses>
        !if $(TARGET) == DEBUG
          DebugLib|$(FSP_PACKAGE)/Library/BaseDebugLibDebugPort/BaseDebugLibDebugPort.inf
        !endif
        MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
        PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
      <PcdsFixedAtBuild>
        gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x27
    }
  !endif
!else
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(FSP_PACKAGE)/Override/MdeModulePkg/Core/Pei/PeiMain.inf {
      <LibraryClasses>
        !if $(TARGET) == DEBUG
          DebugLib|$(FSP_PACKAGE)/Library/BaseDebugLibDebugPort/BaseDebugLibDebugPort.inf
        !endif
        MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
        PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
      <PcdsFixedAtBuild>
        gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x27
    }
  !else
    MdeModulePkg/Core/Pei/PeiMain.inf {
      <LibraryClasses>
        !if $(TARGET) == DEBUG
          DebugLib|$(FSP_PACKAGE)/Library/BaseDebugLibDebugPort/BaseDebugLibDebugPort.inf
        !endif
        MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
        PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
      <PcdsFixedAtBuild>
        gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x27
    }
  !endif
!endif

  #
  # PCD
  #
  MdeModulePkg/Universal/PCD/Pei/Pcd.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
      DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
      NULL|$(FSP_PACKAGE)/Library/FspEmptyLib/FspEmptyLib.inf
  }
  #
  # FSP Binary Components
  #
  $(FSP_PACKAGE)/FspGlobalDataInit/Pei/FspGlobalDataInitPei.inf {
    <LibraryClasses>
      MmPciLib|$(FSP_PACKAGE)/Library/MmPciCf8Lib/MmPciCf8Lib.inf
      PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
      DebugLib|$(FSP_PACKAGE)/Library/BaseDebugLibDebugPort/BaseDebugLibDebugPort.inf
      SerialPortLib|$(FSP_PACKAGE)/Library/SerialPortLib/SerialPortLib.inf
  }

!if $(TARGET) == DEBUG
  $(FSP_PACKAGE)/FspDebugInit/Pei/FspDebugServicePei.inf {
    # library for display FSP information
    <LibraryClasses>
      DebugLib|$(FSP_PACKAGE)/Library/BaseDebugLibDebugPort/BaseDebugLibDebugPort.inf
      SerialPortLib|$(FSP_PACKAGE)/Library/SerialPortLib/SerialPortLib.inf
    <PcdsFixedAtBuild>
      gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x2F
    <PcdsPatchableInModule>
      gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80080046
  }
!endif
  $(FSP_PACKAGE)/FspHeader/FspHeader.inf
  $(C1S_PRODUCT_PATH)/SiInit/Pei/SiInitPreMemFsp.inf
  MdeModulePkg/Universal/PcatSingleSegmentPciCfg2Pei/PcatSingleSegmentPciCfg2Pei.inf {
    <LibraryClasses>
      NULL|$(FSP_PACKAGE)/Library/FspEmptyLib/FspEmptyLib.inf
  }
    $(PLATFORM_SI_PACKAGE)/Fru/EhlCpu/Graphics/IntelGraphicsPeim/Binaries/IntelGraphicsPeim.inf

  #
  # CpuMp PEIM for MpService PPI
  # In Dispatch mode: if MpServicePpi already installed by boot loader
  #                   this will be skipped.
  # In API mode     : If external MpService stack passed by UPD, this will
  #                   be skipped
  #
  # If not skipped, this module must be dispatched earlier than PostMem
  # silicon policy PPI installed, for PostMem silicon initialization to
  # consume MpService PPI.
  #
  UefiCpuPkg/CpuMpPei/CpuMpPei.inf {
    <LibraryClasses>
      NULL|$(PLATFORM_SI_PACKAGE)/Library/PeiReadyToInstallMpLib/PeiReadyToInstallMpLib.inf
  }
  $(C1S_PRODUCT_PATH)/SiInit/Pei/SiInitFsp.inf

  MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf {
    <LibraryClasses>
      DebugAgentLib|MdeModulePkg/Library/DebugAgentLibNull/DebugAgentLibNull.inf
      ResetSystemLib|MdeModulePkg/Library/BaseResetSystemLibNull/BaseResetSystemLibNull.inf
      NULL|$(FSP_PACKAGE)/Library/FspEmptyLib/FspEmptyLib.inf
  }

  MdeModulePkg/Universal/ResetSystemPei/ResetSystemPei.inf {
    <LibraryClasses>
      ResetSystemLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/BaseResetSystemLib/BaseResetSystemLib.inf
      NULL|$(FSP_PACKAGE)/Library/FspEmptyLib/FspEmptyLib.inf
  }
  $(FSP_PACKAGE)/FspInit/Pei/FspInitPreMem.inf
  $(FSP_PACKAGE)/FspPcdInit/Pei/FspPcdInit.inf
  $(FSP_PACKAGE)/FspInit/Pei/FspInit.inf {
    <LibraryClasses>
      CpuPolicyLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/PeiCpuPolicyLib/PeiCpuPolicyLib.inf
  }

  #
  # Silicon policy should be dependency on all of Notify phase code for dispatching later than
  # SiInit done.
  #
  $(PLATFORM_SI_PACKAGE)/SystemAgent/SaInit/Dxe/SaInitFsp.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/Pch/PchInit/Dxe/PchInitDxeFspEhl.inf
!else
  $(PLATFORM_SI_PACKAGE)/Pch/PchInit/Dxe/PchInitDxeFspIcl.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/HeciInit/Dxe/HeciInitFspBfx.inf
!else
  $(PLATFORM_SI_PACKAGE)/IpBlock/Me/HeciInit/Dxe/HeciInitFsp.inf
!endif

  IntelFsp2Pkg/FspNotifyPhase/FspNotifyPhasePeim.inf {
    <LibraryClasses>
      NULL|$(PLATFORM_SI_PACKAGE)/Library/PeiSiliconPolicyInitLibDependency/PeiPostMemSiliconPolicyInitLibDependency.inf
  }

  $(FSP_PACKAGE)/FspInit/Pei/FspS3Notify.inf
  $(FSP_PACKAGE)/FspEndOfPei2/FspEndOfPei2Peim.inf

[Components.X64]
  $(PLATFORM_SI_PACKAGE)/Pch/PchInit/Dxe/PchInitDxeFsp.inf
  #$(PLATFORM_SI_PACKAGE)/IpBlock/Me/HeciInit/Dxe/HeciInitDxeFsp.inf
  $(PLATFORM_SI_PACKAGE)/SystemAgent/SaInit/Dxe/SaInitDxeFsp.inf

!include $(C1S_PRODUCT_PATH)/SiPkgBuildOption.dsc
!include $(FSP_PACKAGE)/FspPkgBuildOption.dsc

###################################################################################################
#
# BuildOptions Section - Define the module specific tool chain flags that should be used as
#                        the default flags for a module. These flags are appended to any
#                        standard flags that are defined by the build process. They can be
#                        applied for any modules or only those modules with the specific
#                        module style (EDK or EDKII) specified in [Components] section.
#
###################################################################################################
[BuildOptions]
# Append build options for EDK and EDKII drivers (= is Append, == is Replace)

[BuildOptions.Common.EDKII]

!if gElkhartLakeFspPkgTokenSpaceGuid.PcdMiniBiosEnable == TRUE
  DEFINE EDKII_DSC_MINIBIOS_BUILD_OPTIONS = -DMRC_MINIBIOS_BUILD
!else
  DEFINE EDKII_DSC_MINIBIOS_BUILD_OPTIONS =
!endif

!if gSiPkgTokenSpaceGuid.PcdSsaFlagEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdEvLoaderEnable == TRUE
  DEFINE EV_LOADER_BUILD_OPTIONS = -DSSA_FLAG=1
!else
  DEFINE EV_LOADER_BUILD_OPTIONS =
!endif
!else
  DEFINE EV_LOADER_BUILD_OPTIONS =
!endif
  DEFINE EDKII_DSC_FEATURE_BUILD_OPTIONS = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(EDKII_DSC_MINIBIOS_BUILD_OPTIONS) -DFSP_FLAG
  DEFINE EDKII_DSC_ALL_BUILD_OPTIONS = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)

!if ("GCC49" in $(TOOL_CHAIN_TAG)) OR ("GCC5" in $(TOOL_CHAIN_TAG))
GCC:   *_*_IA32_ASM_FLAGS   = $(EDKII_DSC_FEATURE_BUILD_OPTIONS) -Wa,--defsym,FSP_FLAG=1
  *_*_IA32_PP_FLAGS = $(EDKII_DSC_ALL_BUILD_OPTIONS)
!else
GCC:   *_*_IA32_ASM_FLAGS   = $(EDKII_DSC_FEATURE_BUILD_OPTIONS) -DFSP_FLAG=1
GCC:   *_*_IA32_PP_FLAGS = $(EDKII_DSC_ALL_BUILD_OPTIONS)
!endif
MSFT:  *_*_IA32_ASM_FLAGS   = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_IA32_NASM_FLAGS  = $(EDKII_DSC_FEATURE_BUILD_OPTIONS) -DFSP_FLAG=1
  *_*_IA32_CC_FLAGS    = $(EDKII_DSC_ALL_BUILD_OPTIONS) -DFSP_FLAG
  *_*_IA32_VFRPP_FLAGS = $(EDKII_DSC_ALL_BUILD_OPTIONS)
  *_*_IA32_APP_FLAGS   = $(EDKII_DSC_ALL_BUILD_OPTIONS)
  *_*_IA32_PP_FLAGS    = -DFSP_FLAG=1

!if ("GCC49" in $(TOOL_CHAIN_TAG)) OR ("GCC5" in $(TOOL_CHAIN_TAG))
GCC:   *_*_X64_ASM_FLAGS   = $(EDKII_DSC_FEATURE_BUILD_OPTIONS) -Wa,--defsym,FSP_FLAG=1
!else
GCC:   *_*_X64_ASM_FLAGS   = $(EDKII_DSC_FEATURE_BUILD_OPTIONS) -DFSP_FLAG=1
!endif
MSFT:  *_*_X64_ASM_FLAGS   = $(EDKII_DSC_FEATURE_BUILD_OPTIONS)
  *_*_X64_NASM_FLAGS  = $(EDKII_DSC_FEATURE_BUILD_OPTIONS) -DFSP_FLAG=1
  *_*_X64_CC_FLAGS    = $(EDKII_DSC_ALL_BUILD_OPTIONS) -DFSP_FLAG
  *_*_X64_VFRPP_FLAGS = $(EDKII_DSC_ALL_BUILD_OPTIONS)
  *_*_X64_APP_FLAGS   = $(EDKII_DSC_ALL_BUILD_OPTIONS)
  *_*_X64_PP_FLAGS    = -DFSP_FLAG=1

