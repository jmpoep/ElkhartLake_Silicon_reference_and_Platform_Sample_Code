## @file
#  Board package description.
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
[Defines]
  #
  # Set platform specific package/folder name, same as passed from PREBUILD script.
  # PLATFORM_PACKAGE would be the same as PLATFORM_NAME as well as package build folder
  # DEFINE only takes effect at R9 DSC and FDF.
  #
  DEFINE      PLATFORM_PACKAGE                = MinPlatformPkg
  DEFINE      PLATFORM_FULL_PACKAGE           = ElkhartLakePlatSamplePkg
  DEFINE      PLATFORM_SI_PACKAGE             = ClientOneSiliconPkg
  DEFINE      C1S_PRODUCT_PATH                = ClientOneSiliconPkg/Product/ElkhartLake
  DEFINE      CLIENT_COMMON_PACKAGE           = ClientCommonPkg
  DEFINE      PLATFORM_FSP_BIN_PACKAGE        = ElkhartLakeFspBinPkg
  DEFINE      PLATFORM_BOARD_PACKAGE          = ElkhartLakeBoardPkg
  DEFINE      PLATFORM_OPEN_BOARD_PACKAGE     = ElkhartLakeOpenBoardPkg
  DEFINE      PLATFORM_FEATURES_PATH          = $(PLATFORM_FULL_PACKAGE)/Features

#
# Define ESRT GUIDs for Firmware Management Protocol instances
#
  DEFINE FMP_CLIENT_PLATFORM_SYSTEM_MONO                = 7FEB1D5D-33F4-48D3-BD11-C4B36B6D0E57 # gFmpDevicePlatformMonolithicGuid
  DEFINE FMP_CLIENT_PLATFORM_SYSTEM_BIOS                = 6C8E136F-D3E6-4131-AC32-4687CB4ABD27 # gFmpDevicePlatformBiosGuid
  DEFINE FMP_CLIENT_PLATFORM_SYSTEM_ME                  = 0EAB05C1-766A-4805-A039-3081DE0210C7 # gFmpDevicePlatformMeGuid
  DEFINE FMP_CLIENT_PLATFORM_SYSTEM_ISH_PDT             = 76CA0AD8-4A14-4389-B7E5-FD88791762AD # gFmpDevicePlatformIshPdtGuid
  DEFINE FMP_CLIENT_PLATFORM_SYSTEM_TSN_MAC_ADDR        = 6FEE88FF-49ED-48F1-B77B-EAD15771ABE7 # gFmpDevicePlatformTsnMacAddrGuid
  DEFINE FMP_CLIENT_PLATFORM_SYSTEM_PSE_TSN_IP_CONFIG   = 697F0EA1-B630-4B93-9B08-EAFFC5D5FC45 # gFmpDevicePlatformPseTsnIpConfigGuid
  DEFINE FMP_CLIENT_PLATFORM_SYSTEM_TSN_CONFIG          = 90C9751D-FA74-4EA6-8C4B-F44D2BE8CD4B # gFmpDevicePlatformTsnConfigGuid
  DEFINE FMP_CLIENT_PLATFORM_SYSTEM_SIIP_FW             = AAD1E926-23B8-4C3A-8B44-0C9A031664F2 # gFmpDevicePlatformSiipFwGuid
  DEFINE FMP_CLIENT_PLATFORM_SYSTEM_OOB_CONFIG          = A7EE90B1-FB4A-4478-B868-367EE9EC97E2 # gFmpDevicePlatformOobConfigGuid
  DEFINE FMP_CLIENT_PLATFORM_SYSTEM_TCC_CONFIG          = BF2AE378-01E0-4605-9E3B-2EE2FC7339DE # gFmpDevicePlatformTccConfigGuid

  #
  # Platform On/Off features are defined here
  #
  !include BoardPkgConfigDefault.dsc
  !include BoardPkgConfig.dsc

  #
  # DSC files include for different boards
  #
  !include  BoardPkgBoards.dsc

  #
  # @Todo: Need to check if the copies from ElkhartLakeSvRestrictedPkg are required or not
################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                       = $(PLATFORM_BOARD_PACKAGE)
  PLATFORM_GUID                       = EB89E595-7D9D-4422-A277-A50B5AFD3E16
  PLATFORM_VERSION                    = 0.1
  DSC_SPECIFICATION                   = 0x00010005
  OUTPUT_DIRECTORY                    = Build/$(PLATFORM_BOARD_PACKAGE)
  SUPPORTED_ARCHITECTURES             = IA32|X64
  BUILD_TARGETS                       = DEBUG|RELEASE
  SKUID_IDENTIFIER                    = ALL


  FLASH_DEFINITION                    = $(PLATFORM_BOARD_PACKAGE)/BoardPkg.fdf

  FIX_LOAD_TOP_MEMORY_ADDRESS         = 0x0
  DEFINE   TOP_MEMORY_ADDRESS         = 0x0

  #
  # Default value for BoardPkg.fdf use
  #
  DEFINE BIOS_SIZE_OPTION = SIZE_100
  DEFINE   COV_TOOLS                  = VS2008

################################################################################
#
# SKU Identification section - list of all SKU IDs supported by this
#                              Platform.
#
################################################################################
[SkuIds]
  0|DEFAULT              # The entry: 0|DEFAULT is reserved and always required.
  1|BoardIdEhlLp4xType4Erb     #@todo: SKU ID needs to be implemented right way after the code merge. use BoardId temporarily.
################################################################################
#
# Library Class section - list of all Library Classes needed by this Platform.
#
################################################################################

!include $(PLATFORM_BOARD_PACKAGE)/Include/Dsc/CoreCommonLib.dsc
!include $(PLATFORM_PACKAGE)/Include/Dsc/CorePeiLib.dsc
!include $(PLATFORM_BOARD_PACKAGE)/Include/Dsc/CoreDxeLib.dsc

[LibraryClasses.common]

  PeiLib|$(PLATFORM_PACKAGE)/Library/PeiLib/PeiLib.inf
  ReportFvLib|$(PLATFORM_BOARD_PACKAGE)/Library/PeiReportFvLib/PeiReportFvLib.inf

  PciHostBridgeLib|$(PLATFORM_PACKAGE)/Pci/Library/PciHostBridgeLibSimple/PciHostBridgeLibSimple.inf
  PciSegmentInfoLib|$(PLATFORM_PACKAGE)/Pci/Library/PciSegmentInfoLibSimple/PciSegmentInfoLibSimple.inf
  PlatformHookLib|$(PLATFORM_BOARD_PACKAGE)/Library/BasePlatformHookLib/BasePlatformHookLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf

!if gPlatformModuleTokenSpaceGuid.PcdSerialPortEnable == TRUE
  SerialPortLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseSerialPortLib/BaseSerialPortLib.inf
!else
  SerialPortLib|MdePkg/Library/BaseSerialPortLibNull/BaseSerialPortLibNull.inf
!endif

#
# Platform
#

!if gBoardModuleTokenSpaceGuid.PcdSetupEnable == TRUE
  PlatformBootManagerLib|$(PLATFORM_FULL_PACKAGE)/Library/DxePlatformBootManagerLib/DxePlatformBootManagerLib.inf
!else
  PlatformBootManagerLib|$(PLATFORM_FULL_PACKAGE)/Library/DxePlatformBootManagerLib/DxePlatformBootManagerHiiFreeLib.inf
!endif

  PlatformSecLib|$(PLATFORM_SI_PACKAGE)/Library/PlatformSecLib/PlatformSecLibEhl.inf

!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
  FspWrapperTempRamExitLib|$(PLATFORM_FULL_PACKAGE)/FspWrapper/Library/PeiFspWrapperTempRamExitLib/PeiFspWrapperTempRamExitLib.inf
!else
  FspWrapperTempRamExitLib|$(PLATFORM_FULL_PACKAGE)/FspWrapper/Library/PeiFspWrapperTempRamExitLibNull/PeiFspWrapperTempRamExitLibNull.inf
!endif
!endif

!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
  FspCommonLib|IntelFsp2Pkg/Library/BaseFspCommonLib/BaseFspCommonLib.inf
  FspWrapperApiLib|$(PLATFORM_FULL_PACKAGE)/Override/IntelFsp2WrapperPkg/Library/BaseFspWrapperApiLib/BaseFspWrapperApiLib.inf # RPPO-CNL-0087: RoyalParkOverrideContent
  FspWrapperApiTestLib|IntelFsp2WrapperPkg/Library/PeiFspWrapperApiTestLib/PeiFspWrapperApiTestLib.inf
  FspWrapperPlatformLib|$(PLATFORM_FULL_PACKAGE)/FspWrapper/Library/PeiFspWrapperPlatformLib/PeiFspWrapperPlatformLib.inf
  SiliconPolicyInitLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/SiliconPolicyInitLibNull/SiliconPolicyInitLibNull.inf
  SiliconPolicyUpdateLib|$(PLATFORM_BOARD_PACKAGE)/Library/PeiSiliconPolicyUpdateLib/PeiSiliconPolicyUpdateLibFsp.inf
  FspWrapperHobProcessLib|$(PLATFORM_FULL_PACKAGE)/FspWrapper/Library/PeiFspWrapperHobProcessLib/PeiFspWrapperHobProcessLib.inf
  FspSwitchStackLib|IntelFsp2Pkg/Library/BaseFspSwitchStackLib/BaseFspSwitchStackLib.inf
  PlatformInitLib|$(PLATFORM_FULL_PACKAGE)/Library/PlatformInitLib/PlatformInitLib.inf
  PlatformSecLib|$(PLATFORM_FULL_PACKAGE)/FspWrapper/Library/SecFspWrapperPlatformSecLib/SecFspWrapperPlatformSecLib.inf
!endif

  PeiBootModeLib|$(PLATFORM_BOARD_PACKAGE)/Library/PeiBootModeLib/PeiBootModeLib.inf

  ConfigBlockLib|ClientSiliconPkg/Library/BaseConfigBlockLib/BaseConfigBlockLib.inf
  SiliconInitLib|$(PLATFORM_BOARD_PACKAGE)/Library/SiliconInitLib/SiliconInitLib.inf
  MmioInitLib|$(PLATFORM_BOARD_PACKAGE)/Library/BaseMmioInitLib/BaseMmioInitLib.inf

  BoardInitLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/BoardInitLibNull/BoardInitLibNull.inf
  TestPointCheckLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointCheckLibNull/TestPointCheckLibNull.inf

  PciSegmentLib|$(PLATFORM_SI_PACKAGE)/Library/BasePciSegmentMultiSegLibPci/BasePciSegmentMultiSegLibPci.inf
  PciExpressLib|$(PLATFORM_SI_PACKAGE)/Library/BasePciExpressMultiSegLib/BasePciExpressMultiSegLib.inf
  PciLib|MdePkg/Library/BasePciLibPciExpress/BasePciLibPciExpress.inf
  BoardIdsLib|$(PLATFORM_BOARD_PACKAGE)/Library/PeiDxeBoardIdsLib/PeiDxeBoardIdsLib.inf
  WakeupEventLib|$(PLATFORM_BOARD_PACKAGE)/Library/WakeupEventLib/WakeupEventLib.inf
  DxeUpdatePlatformInfoLib|$(PLATFORM_BOARD_PACKAGE)/Library/DxeUpdatePlatformInfoLib/DxeUpdatePlatformInfoLib.inf

  HidI2cPlatformSupportLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeHidI2cPlatformSupportLib/DxeHidI2cPlatformSupportLib.inf
  DxeDTbtPolicyLib|$(PLATFORM_FEATURES_PATH)/Tbt/Library/DxeDTbtPolicyLib/DxeDTbtPolicyLib.inf
  DxeInstallNhltTableLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeInstallNhltTableLib/DxeInstallNhltTableLib.inf
  PlatformPasswordLib|UserInterfaceFeaturePkg/Library/PlatformPasswordLibNull/PlatformPasswordLibNull.inf
  UserPasswordLib|UserInterfaceFeaturePkg/Library/UserPasswordLib/UserPasswordLib.inf
  UserPasswordUiLib|UserInterfaceFeaturePkg/Library/UserPasswordUiLib/UserPasswordUiLib.inf
  SiMtrrLib|$(PLATFORM_SI_PACKAGE)/Library/SiMtrrLib/SiMtrrLib.inf
!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
!if gPlatformModuleTokenSpaceGuid.PcdSkipFspTempRamInitAndExit == TRUE
  CacheAsRamLib|$(PLATFORM_SI_PACKAGE)/Library/BaseCacheAsRamLib/BaseCacheAsRamLib.inf
!else
  CacheAsRamLib|IntelFsp2Pkg/Library/BaseCacheAsRamLibNull/BaseCacheAsRamLibNull.inf
!endif
!endif
  BaseBfxTempRamLib|$(PLATFORM_SI_PACKAGE)/Library/BaseBfxTempRamLib/BaseBfxTempRamLib.inf

!if gBoardModuleTokenSpaceGuid.PcdEcEnable == TRUE
  EcLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcLib/BaseEcLib.inf
  EcMiscLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcMiscLib/BaseEcMiscLib.inf
  EcTcssLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcTcssLib/BaseEcTcssLib.inf
  EcHwLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcHwLib/BaseEcHwLib.inf
!else
  EcLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcLibNull/BaseEcLibNull.inf
  EcMiscLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcMiscLibNull/BaseEcMiscLibNull.inf
  EcTcssLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcTcssLibNull/BaseEcTcssLibNull.inf
!endif

!if gBoardModuleTokenSpaceGuid.PcdEcLitePseEnable == TRUE
  EcLiteLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcLiteLib/BaseEcLiteLib.inf
  EcLiteMiscLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcLiteMiscLib/BaseEcLiteMiscLib.inf
!else
  EcLiteLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcLiteLibNull/BaseEcLiteLibNull.inf
  EcLiteMiscLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseEcLiteMiscLibNull/BaseEcLiteMiscLibNull.inf
!endif

  DisplayUpdateProgressLib|MdeModulePkg/Library/DisplayUpdateProgressLibText/DisplayUpdateProgressLibText.inf
  PssLib|$(PLATFORM_FULL_PACKAGE)/Library/PssLib/PssLib.inf
  I2cAccessLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiI2cAccessLib/PeiI2cAccessLib.inf
  PlatformPostCodeMapLib|$(CLIENT_COMMON_PACKAGE)/Library/BasePlatformPostCodeMapLib/BasePlatformPostCodeMapLib.inf
  BeepLib|$(PLATFORM_FULL_PACKAGE)/Library/BeepLib/BeepLib.inf
  PlatformBeepMapLib|$(CLIENT_COMMON_PACKAGE)/Library/BasePlatformBeepMapLib/BasePlatformBeepMapLib.inf
  PlatformMiscLib|$(PLATFORM_BOARD_PACKAGE)/Library/PlatformMiscLib/PlatformMiscLib.inf

  Usb3DebugPortParameterLib|$(CLIENT_COMMON_PACKAGE)/Library/BaseUsb3DebugPortParameterLibCmos/BaseUsb3DebugPortParameterLibCmos.inf
  DebugPropertyLib|$(CLIENT_COMMON_PACKAGE)/Library/BaseDebugPropertyLibCmosPcd/BaseDebugPropertyLibCmosPcd.inf

  # TODO: This block of libraries is here because they are a dependency for ElkhartLakePlatSamplePkg/Setup/Setup.inf
  #       The Setup module needs to be refactored, these need to be refactored, and moved to ElkhartLakeBoardPkg
  #       over time.
  SerialPortParameterLib|$(CLIENT_COMMON_PACKAGE)/Library/BaseSerialPortParameterLibPcd/BaseSerialPortParameterLibPcd.inf
  SerialIoUartDebugHelperLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseSerialIoUartDebugHelperLib/BaseSerialIoUartDebugHelperLib.inf
  SerialIoUartDebugPropertyLib|$(PLATFORM_FULL_PACKAGE)/Library/SerialIoUartDebugPropertyLib/BaseSerialIoUartDebugPropertyLib.inf
  PlatformNvRamHookLib|$(PLATFORM_FEATURES_PATH)/Cmos/Library/PlatformNvRamHookLibCmos/PlatformNvRamHookLibCmos.inf
  CmosAccessLib|$(PLATFORM_FEATURES_PATH)/Cmos/Library/CmosAccessLib/CmosAccessLib.inf
  PlatformCmosAccessLib|$(PLATFORM_FEATURES_PATH)/Cmos/Library/PlatformCmosAccessLib/PlatformCmosAccessLib.inf
!if gSiPkgTokenSpaceGuid.PcdSpiPostCode == TRUE
  PostCodeLib|ClientSiliconPkg/Library/BasePostCodeSpiLib/BasePostCodeLibSpi.inf
!endif
  GpioExpanderLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseGpioExpanderLibNull/BaseGpioExpanderLibNull.inf
  DTbtCommonLib|$(PLATFORM_FEATURES_PATH)/Tbt/Library/DTbtCommonLib/DTbtCommonLib.inf
  DimmInfoLib|$(PLATFORM_FULL_PACKAGE)/Setup/DimmInfoLib.inf
  BiosIdLib|BpCommonPkg/Library/BiosIdLib/PeiBiosIdLib.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  OobRegionLib|$(PLATFORM_FULL_PACKAGE)/Library/OobRegionLib/PeiOobRegionLib.inf
!else
  OobRegionLib|$(PLATFORM_FULL_PACKAGE)/Library/OobRegionLibNull/PeiOobRegionLibNull.inf
!endif
#
# Security
#
  TpmCommLib|SecurityPkg/Library/TpmCommLib/TpmCommLib.inf

  DxeInstallOptionRomLib|$(CLIENT_COMMON_PACKAGE)/Library/DxeInstallOptionRomLibNull/DxeInstallOptionRomLibNull.inf

#
# Silicon Init Package
#
!include $(C1S_PRODUCT_PATH)/SiPkgCommonLib.dsc

#
# Features
#
!if gBoardModuleTokenSpaceGuid.PcdSetupEnable == TRUE
  !include $(PLATFORM_BOARD_PACKAGE)/Features/Setup/Include/Dsc/SetupBaseLib.dsc
!endif
!if gPlatformModuleTokenSpaceGuid.PcdRamDebugEnable == TRUE
  RamDebugLib|$(CLIENT_COMMON_PACKAGE)/Library/BaseRamDebugLib/BaseRamDebugLib.inf
!else
  RamDebugLib|$(CLIENT_COMMON_PACKAGE)/Library/BaseRamDebugLibNull/BaseRamDebugLibNull.inf
!endif
CmosAccessLib|$(PLATFORM_FEATURES_PATH)/Cmos/Library/CmosAccessLib/CmosAccessLib.inf
!if gPlatformModuleTokenSpaceGuid.PcdPlatformCmosAccessSupport == TRUE
  PlatformCmosAccessLib|$(PLATFORM_FEATURES_PATH)/Cmos/Library/PlatformCmosAccessLib/PlatformCmosAccessLib.inf
!else
  PlatformCmosAccessLibNull|$(PLATFORM_FEATURES_PATH)/Cmos/Library/PlatformCmosAccessLibNull/PlatformCmosAccessLibNull.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdAmtEnable == TRUE
  BaseAmtWrapperLib|$(PLATFORM_FEATURES_PATH)/Amt/Library/BaseAmtWrapperLib/BaseAmtWrapperLib.inf
!else
  BaseAmtWrapperLib|$(PLATFORM_FEATURES_PATH)/Amt/Library/BaseAmtWrapperLibNull/BaseAmtWrapperLibNull.inf
!endif

  ShellCommandLib|ShellPkg/Library/UefiShellCommandLib/UefiShellCommandLib.inf
  HandleParsingLib|ShellPkg/Library/UefiHandleParsingLib/UefiHandleParsingLib.inf
  BcfgCommandLib|ShellPkg/Library/UefiShellBcfgCommandLib/UefiShellBcfgCommandLib.inf

#
# S3
#
!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
  S3BootScriptLib|MdeModulePkg/Library/PiDxeS3BootScriptLib/DxeS3BootScriptLib.inf
!else
  S3BootScriptLib|MdePkg/Library/BaseS3BootScriptLibNull/BaseS3BootScriptLibNull.inf
!endif
  S3IoLib|MdePkg/Library/BaseS3IoLib/BaseS3IoLib.inf
  S3PciLib|MdePkg/Library/BaseS3PciLib/BaseS3PciLib.inf

  ThunkLib|$(CLIENT_COMMON_PACKAGE)/Library/PeiDxeSmmThunkLib/PeiDxeSmmThunkLib.inf

!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
  FwUpdateLib|$(PLATFORM_FEATURES_PATH)/CapsuleUpdate/Library/FwUpdateLib/FwUpdateLib.inf
  PlatformFlashAccessLib|$(PLATFORM_FEATURES_PATH)/CapsuleUpdate/Library/PlatformFlashAccessLib/PlatformFlashAccessLib.inf
  PlatformFvAddressLib|$(PLATFORM_FEATURES_PATH)/CapsuleUpdate/Library/PlatformFvAddressTsLib/PlatformFvAddressTsLib.inf
  SeamlessRecoverySupportLib|$(PLATFORM_FEATURES_PATH)/CapsuleUpdate/Library/SeamlessRecoverySupportLib/SeamlessRecoverySupportLib.inf
  PeiPlatformCodLib|$(PLATFORM_FEATURES_PATH)/CapsuleUpdate/Library/PeiPlatformCodLib/PeiPlatformCodLib.inf
!else
  PlatformFvAddressLib|$(PLATFORM_FULL_PACKAGE)/Library/PlatformFvAddressLib/PlatformFvAddressLib.inf
  PeiPlatformCodLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPlatformCodLibNull/PeiPlatformCodLibNull.inf
!endif
  CapsuleLib|MdeModulePkg/Library/DxeCapsuleLibNull/DxeCapsuleLibNull.inf
  FmpAuthenticationLib|MdeModulePkg/Library/FmpAuthenticationLibNull/FmpAuthenticationLibNull.inf
  Usb3DebugPortDummyLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseUsb3DebugPortDummyLib/Usb3DebugPortDummyLib.inf
  TcgStorageCoreLib|SecurityPkg/Library/TcgStorageCoreLib/TcgStorageCoreLib.inf
  TcgStorageOpalLib|SecurityPkg/Library/TcgStorageOpalLib/TcgStorageOpalLib.inf

  PeiSubRegionLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiSubRegionLib/PeiSubRegionLib.inf
  PeiSiipLib|$(PLATFORM_SI_PACKAGE)/Library/PeiSiipLib/PeiSiipLib.inf
  PeiTsnFvLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiTsnFvLib/PeiTsnFvLib.inf
  PeiSiipFvLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiSiipFvLib/PeiSiipFvLib.inf
  PeiTccFvLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiTccFvLib/PeiTccFvLib.inf
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
  PeiSciInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sci/LibraryPrivate/PeiSciInitLib/PeiSciInitLib.inf
!else
  PeiSciInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Sci/LibraryPrivate/PeiSciInitLibNull/PeiSciInitLibNull.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  UefiScsiLib|$(PLATFORM_FULL_PACKAGE)/Override/MdePkg/Library/UefiScsiLib/UefiScsiLib.inf
  VariableCacheLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiVariableCacheLib/PeiVariableCacheLib.inf
  VariableStorageSelectorLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseVariableStorageSelectorLib/BaseVariableStorageSelectorLib.inf
  NemMapLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiNemMapLib/PeiNemMapLib.inf
  BpdtLib|$(PLATFORM_FULL_PACKAGE)/Library/BpdtLib/BpdtLib.inf
  !if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
    SpmdVarSelectorLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseSpmdVarSelectorLib/BaseSpmdVarSelectorLibFsp.inf
  !else
    SpmdVarSelectorLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseSpmdVarSelectorLib/BaseSpmdVarSelectorLib.inf
  !endif
!else
  UefiScsiLib|MdePkg/Library/UefiScsiLib/UefiScsiLib.inf
!endif

[LibraryClasses.IA32]
#
# PEI phase common
#

  ResetSystemLib|MdeModulePkg/Library/PeiResetSystemLib/PeiResetSystemLib.inf

#
# TBT
#
  PeiDTbtPolicyLib|$(PLATFORM_FEATURES_PATH)/Tbt/Library/PeiDTbtPolicyLib/PeiDTbtPolicyLib.inf
!if gPlatformModuleTokenSpaceGuid.PcdDTbtEnable == TRUE
  PeiDTbtInitLib|$(PLATFORM_FEATURES_PATH)/Tbt/Library/Private/PeiDTbtInitLib/PeiDTbtInitLib.inf
!else
  PeiDTbtInitLib|$(PLATFORM_FEATURES_PATH)/Tbt/Library/Private/PeiDTbtInitLibNull/PeiDTbtInitLibNull.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
  TraceHubDebugLib|BpCommonPkg/Library/TraceHubDebugLibSvenTx/BaseTraceHubDebugLibSvenTx.inf
!else
  TraceHubDebugLib|BpCommonPkg/Library/TraceHubDebugLibSvenTx/PeiTraceHubDebugLibSvenTx.inf
!endif
!else
  TraceHubDebugLib|BpCommonPkg/Library/TraceHubDebugLibNull/TraceHubDebugLibNull.inf
!endif

!if $(TARGET) == DEBUG
  TestPointCheckLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointCheckLib/PeiTestPointCheckLib.inf
  TestPointCheckLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointCheckLibNull/TestPointCheckLibNull.inf
!endif
  TestPointLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointLib/PeiTestPointLib.inf
  MultiBoardInitSupportLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/MultiBoardInitSupportLib/PeiMultiBoardInitSupportLib.inf
  BoardInitLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/MultiBoardInitSupportLib/PeiMultiBoardInitSupportLib.inf

  BoardConfigLib|$(PLATFORM_BOARD_PACKAGE)/Library/PeiBoardConfigLib/PeiBoardConfigLib.inf

#
# Silicon Init Package
#
!include $(C1S_PRODUCT_PATH)/SiPkgPeiLib.dsc

#
# Features
#
!if gBoardModuleTokenSpaceGuid.PcdSetupEnable == TRUE
  !include $(PLATFORM_BOARD_PACKAGE)/Features/Setup/Include/Dsc/SetupPeiLib.dsc
!endif

!if gPlatformModuleTokenSpaceGuid.PcdUsb3SerialStatusCodeEnable == TRUE
  Usb3DebugPortLib|DebugFeaturePkg/Library/Usb3DebugPortLib/Usb3DebugPortLibPei.inf
!else
  Usb3DebugPortLib|DebugFeaturePkg/Library/Usb3DebugPortLib/Usb3DebugPortLibNull.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdFspModeSelection == 1
  PeiPolicyInitLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPolicyInitLib/PeiPolicyInitLibFsp.inf
  PeiPolicyBoardConfigLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPolicyBoardConfigLib/PeiPolicyBoardConfigLibFsp.inf
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  PeiPolicyUpdateLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPolicyUpdateLib/PeiPolicyUpdateLibFspBfx.inf
!else
  PeiPolicyUpdateLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPolicyUpdateLib/PeiPolicyUpdateLibFsp.inf
!endif
  PeiPolicyDebugLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPolicyDebugLib/PeiPolicyDebugLibFsp.inf
!else
  PeiPolicyInitLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPolicyInitLib/PeiPolicyInitLib.inf
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  PeiPolicyUpdateLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPolicyUpdateLib/PeiPolicyUpdateLibBfx.inf
!else
  PeiPolicyUpdateLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPolicyUpdateLib/PeiPolicyUpdateLib.inf
!endif
  PeiPolicyBoardConfigLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPolicyBoardConfigLib/PeiPolicyBoardConfigLib.inf
  PeiPolicyDebugLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPolicyDebugLib/PeiPolicyDebugLib.inf
!endif

  ProcessorTraceMemoryAllocationLib|$(PLATFORM_SI_PACKAGE)/Library/PeiProcessorTraceMemoryAllocationLib/PeiProcessorTraceMemoryAllocationLib.inf
  PeiOverClockLib|$(PLATFORM_FEATURES_PATH)/OverClocking/OverClockInit/PeiOverClockLib.inf

#
# S3
#
  S3BootScriptLib|MdePkg/Library/BaseS3BootScriptLibNull/BaseS3BootScriptLibNull.inf

  MpInitLib|$(PLATFORM_FULL_PACKAGE)/Override/UefiCpuPkg/Library/MpInitLib/PeiMpInitLib.inf
  
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  NvStorageCopyLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiNvStorageCopyLib/PeiNvStorageCopyLib.inf
!endif

[LibraryClasses.IA32.SEC]
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  Usb3DebugPortLib|DebugFeaturePkg/Library/Usb3DebugPortLib/Usb3DebugPortLibNull.inf
  TestPointCheckLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointCheckLib/SecTestPointCheckLib.inf
  TestPointCheckLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointCheckLibNull/TestPointCheckLibNull.inf
  SecBoardInitLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/SecBoardInitLibNull/SecBoardInitLibNull.inf
  ResetSystemLib|MdeModulePkg/Library/BaseResetSystemLibNull/BaseResetSystemLibNull.inf
  SecGetFsptApiParameterLib|$(PLATFORM_SI_PACKAGE)/Library/SecGetFsptApiParameterLib/SecGetFsptApiParameterLib.inf

[LibraryClasses.IA32.PEIM]

!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
  FspSwitchStackLib|IntelFsp2Pkg/Library/BaseFspSwitchStackLib/BaseFspSwitchStackLib.inf
  FspWrapperExtractGuidedLib|$(PLATFORM_FULL_PACKAGE)/FspWrapper/Library/PeiFspWrapperExtractGuidedLib/PeiFspWrapperExtractGuidedLib.inf
!endif

!if $(TARGET) == DEBUG
  SerialIoUartDebugPropertyLib|$(PLATFORM_FULL_PACKAGE)/Library/SerialIoUartDebugPropertyLib/PeiSerialIoUartDebugPropertyLib.inf
  !if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
    !if gPlatformModuleTokenSpaceGuid.PcdSerialPortEnable == TRUE
      SerialPortLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseSerialPortLib/BaseSerialPortLib.inf
    !else
      SerialPortLib|MdePkg/Library/BaseSerialPortLibNull/BaseSerialPortLibNull.inf
    !endif
    DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
    DebugPrintErrorLevelLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiDxeSmmDebugPrintErrorLevelLib/PeiDxeSmmDebugPrintErrorLevelLib.inf
  !else
    #
    # This is for reducing NATIVE DEBUG binary size, replacing some library routines with PPI.
    #
    DebugLib|$(CLIENT_COMMON_PACKAGE)/Library/PeiDebugLibDebugService/PeiDebugLibDebugService.inf
  !endif
!endif

[LibraryClasses.X64]
  #
  # DXE phase common
  #
!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
  FspWrapperPlatformLib|$(PLATFORM_PACKAGE)/FspWrapper/Library/DxeFspWrapperPlatformLib/DxeFspWrapperPlatformLib.inf
!endif

!if gPlatformModuleTokenSpaceGuid.PcdSerialPortEnable == TRUE
  SerialPortLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseSerialPortLib/BaseSerialPortLib.inf
!else
  SerialPortLib|MdePkg/Library/BaseSerialPortLibNull/BaseSerialPortLibNull.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
  TraceHubDebugLib|BpCommonPkg/Library/TraceHubDebugLibSvenTx/DxeTraceHubDebugLibSvenTx.inf
!else
  TraceHubDebugLib|BpCommonPkg/Library/TraceHubDebugLibNull/TraceHubDebugLibNull.inf
!endif

!if $(TARGET) == DEBUG
  TestPointCheckLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointCheckLib/DxeTestPointCheckLib.inf
  TestPointCheckLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointCheckLibNull/TestPointCheckLibNull.inf
!endif
  TestPointLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointLib/DxeTestPointLib.inf
  MultiBoardInitSupportLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/MultiBoardInitSupportLib/DxeMultiBoardInitSupportLib.inf
  BoardInitLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/MultiBoardInitSupportLib/DxeMultiBoardInitSupportLib.inf
  MultiBoardAcpiSupportLib|$(PLATFORM_PACKAGE)/Acpi/Library/MultiBoardAcpiSupportLib/DxeMultiBoardAcpiSupportLib.inf
  BoardAcpiTableLib|$(PLATFORM_PACKAGE)/Acpi/Library/MultiBoardAcpiSupportLib/DxeMultiBoardAcpiSupportLib.inf
  SiliconPolicyInitLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/SiliconPolicyInitLibNull/SiliconPolicyInitLibNull.inf
  SiliconPolicyUpdateLib|$(PLATFORM_BOARD_PACKAGE)/Policy/Library/DxeSiliconPolicyUpdateLib/DxeSiliconPolicyUpdateLib.inf
  DxeAcpiGnvsInitLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeAcpiGnvsInitLib/DxeAcpiGnvsInitLib.inf

  DxeDTbtPolicyLib|$(PLATFORM_FEATURES_PATH)/Tbt/Library/DxeDTbtPolicyLib/DxeDTbtPolicyLib.inf
  DxePolicyBoardConfigLib|$(PLATFORM_FULL_PACKAGE)/Library/DxePolicyBoardConfigLib/DxePolicyBoardConfigLib.inf
  DxePolicyUpdateLib|$(PLATFORM_FULL_PACKAGE)/Library/DxePolicyUpdateLib/DxePolicyUpdateLib.inf

  BiosIdLib|BpCommonPkg/Library/BiosIdLib/DxeBiosIdLib.inf
  LogoLib|$(CLIENT_COMMON_PACKAGE)/Library/DxeLogoLib/DxeLogoLib.inf
  TcgPhysicalPresenceLib|SecurityPkg/Library/DxeTcgPhysicalPresenceLib/DxeTcgPhysicalPresenceLib.inf
  TcgPpVendorLib|SecurityPkg/Library/TcgPpVendorLibNull/TcgPpVendorLibNull.inf
  DxeSmmInternalGraphicDeviceLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeSmmInternalGraphicDeviceLib/DxeSmmInternalGraphicDeviceLib.inf

!if gSiPkgTokenSpaceGuid.PcdSmbiosEnable == TRUE
  DxeSmbiosProcessorLib|$(CLIENT_COMMON_PACKAGE)/Library/DxeSmbiosProcessorLib/DxeSmbiosProcessorLib.inf
!else
  DxeSmbiosProcessorLib|$(CLIENT_COMMON_PACKAGE)/Library/DxeSmbiosProcessorLibNull/DxeSmbiosProcessorLibNull.inf
!endif

  DxePolicyBoardConfigLib|$(PLATFORM_FULL_PACKAGE)/Library/DxePolicyBoardConfigLib/DxePolicyBoardConfigLib.inf
  DxePolicyUpdateLib|$(PLATFORM_FULL_PACKAGE)/Library/DxePolicyUpdateLib/DxePolicyUpdateLib.inf

  ResetSystemLib|MdeModulePkg/Library/BaseResetSystemLibNull/BaseResetSystemLibNull.inf


  BoardConfigLib|$(PLATFORM_BOARD_PACKAGE)/Library/DxeBoardConfigLib/DxeBoardConfigLib.inf

#
# Silicon Init Package
#
!include $(C1S_PRODUCT_PATH)/SiPkgDxeLib.dsc

!if gPlatformModuleTokenSpaceGuid.PcdUsb3SerialStatusCodeEnable == TRUE
  Usb3DebugPortLib|DebugFeaturePkg/Library/Usb3DebugPortLib/Usb3DebugPortLibDxe.inf
!else
  Usb3DebugPortLib|DebugFeaturePkg/Library/Usb3DebugPortLib/Usb3DebugPortLibNull.inf
!endif

  DxeOverClockLib|$(PLATFORM_FEATURES_PATH)/OverClocking/OverClockInit/DxeOverClockLib.inf
  BluetoothLib|BpCommonPkg/Bluetooth/Library/BluetoothLib/BluetoothLib.inf
  HidLib|BpCommonPkg/Bluetooth/Library/HidLib/HidLib.inf

  DxeOpromPatchLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeOpromPatchLib/DxeOpromPatchLib.inf

  MpInitLib|UefiCpuPkg/Library/MpInitLib/DxeMpInitLib.inf
  SpiFlashCommonLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeSpiFlashCommonLib/DxeSpiFlashCommonLib.inf
  RasGlobalDataLib|EmbeddedRasPkg/Library/DxeRasGlobalDataLib/DxeRasGlobalDataLib.inf
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  NemMapLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeSmmNemMapLib/DxeSmmNemMapLib.inf
!endif

[LibraryClasses.X64.DXE_CORE]
!if $(TARGET) == DEBUG
  SerialIoUartDebugPropertyLib|$(PLATFORM_FULL_PACKAGE)/Library/SerialIoUartDebugPropertyLib/DxeCoreSerialIoUartDebugPropertyLib.inf
!endif
[LibraryClasses.X64.DXE_DRIVER]
  CpuExceptionHandlerLib|$(PLATFORM_FULL_PACKAGE)/Override/UefiCpuPkg/Library/CpuExceptionHandlerLib/DxeCpuExceptionHandlerLib.inf

[LibraryClasses.X64.DXE_SMM_DRIVER]
!if gSiPkgTokenSpaceGuid.PcdBiosGuardEnable == TRUE
  SpiFlashCommonLib|$(PLATFORM_FULL_PACKAGE)/Library/SmmSpiFlashCommonLib/SmmSpiFlashCommonLibBiosGuard.inf
!else
  SpiFlashCommonLib|$(PLATFORM_FULL_PACKAGE)/Library/SmmSpiFlashCommonLib/SmmSpiFlashCommonLib.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == TRUE
  MmServicesTableLib|MdePkg/Library/MmServicesTableLib/MmServicesTableLib.inf
!endif
!if $(TARGET) == DEBUG
  TestPointCheckLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointCheckLib/SmmTestPointCheckLib.inf
  TestPointCheckLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointCheckLibNull/TestPointCheckLibNull.inf
  DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
  SerialIoUartDebugPropertyLib|$(PLATFORM_FULL_PACKAGE)/Library/SerialIoUartDebugPropertyLib/DxeSmmSerialIoUartDebugPropertyLib.inf
!endif
  TestPointLib|$(PLATFORM_PACKAGE)/Test/Library/TestPointLib/SmmTestPointLib.inf
  MultiBoardAcpiSupportLib|$(PLATFORM_PACKAGE)/Acpi/Library/MultiBoardAcpiSupportLib/SmmMultiBoardAcpiSupportLib.inf
  BoardAcpiEnableLib|$(PLATFORM_PACKAGE)/Acpi/Library/MultiBoardAcpiSupportLib/SmmMultiBoardAcpiSupportLib.inf
  DxeSmmAcpiCustomLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeSmmAcpiCustomLib/DxeSmmAcpiCustomLib.inf
  DxeSmmScriptLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeSmmScriptLib/DxeSmmScriptLib.inf
  CpuPcieRpLib|$(PLATFORM_SI_PACKAGE)/IpBlock/CpuPcieRp/Library/PeiDxeSmmCpuPcieRpLib/PeiDxeSmmCpuPcieRpLib.inf
  SmmIoLib|MdePkg/Library/SmmIoLib/SmmIoLib.inf
  WheaSupportLib|EmbeddedRasPkg/Library/WheaSupportLib/WheaSupportLib.inf
  RasGlobalDataLib|EmbeddedRasPkg/Library/SmmRasGlobalDataLib/SmmRasGlobalDataLib.inf
  CpuExceptionHandlerLib|$(PLATFORM_FULL_PACKAGE)/Override/UefiCpuPkg/Library/CpuExceptionHandlerLib/SmmCpuExceptionHandlerLib.inf

[LibraryClasses.X64.DXE_RUNTIME_DRIVER]

  ReportStatusCodeLib|MdeModulePkg/Library/RuntimeDxeReportStatusCodeLib/RuntimeDxeReportStatusCodeLib.inf
  DebugPrintErrorLevelLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiDxeSmmDebugPrintErrorLevelLib/PeiDxeSmmDebugPrintErrorLevelLib.inf
  SerialPortParameterLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeSmmSerialPortParameterLib/DxeSmmSerialPortParameterLib.inf

!if $(TARGET) == DEBUG
  SerialIoUartDebugPropertyLib|$(PLATFORM_FULL_PACKAGE)/Library/SerialIoUartDebugPropertyLib/DxeSmmSerialIoUartDebugPropertyLib.inf
!endif

!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
  CapsuleLib|MdeModulePkg/Library/DxeCapsuleLibFmp/DxeRuntimeCapsuleLib.inf
!endif

ResetSystemLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/BaseResetSystemLib/BaseResetSystemLib.inf
RasGlobalDataLib|EmbeddedRasPkg/Library/DxeRasGlobalDataLib/DxeRasGlobalDataLib.inf

!include BoardPkgPcd.dsc

[LibraryClasses.X64.SMM_CORE]
!if $(TARGET) == DEBUG
  DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
  SerialIoUartDebugPropertyLib|$(PLATFORM_FULL_PACKAGE)/Library/SerialIoUartDebugPropertyLib/DxeSmmSerialIoUartDebugPropertyLib.inf
!endif

[Components.IA32]

#
# Common
#
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  $(PLATFORM_BOARD_PACKAGE)/BootMediaInfo/BootMediaInfoPei.inf
  $(PLATFORM_FULL_PACKAGE)/VariableStorageSelector/Pei/VariableStorageSelectorPei.inf {
    <LibraryClasses>
      NULL|$(PLATFORM_FULL_PACKAGE)/Library/PeiSecurePreMemoryDataLoadLib/PeiSecurePreMemoryDataLoadLib.inf
  }
  $(PLATFORM_SI_PACKAGE)/VariableStorage/Pei/FvbVariableStoragePei/FvbVariableStoragePei.inf
!endif

!include $(PLATFORM_BOARD_PACKAGE)/Include/Dsc/CorePeiInclude.dsc

  MdeModulePkg/Universal/SectionExtractionPei/SectionExtractionPei.inf {
    <LibraryClasses>
      NULL|SecurityPkg/Library/PeiRsa2048Sha256GuidedSectionExtractLib/PeiRsa2048Sha256GuidedSectionExtractLib.inf
  }

  #
  # FSP wrapper SEC Core
  #
  $(PLATFORM_FULL_PACKAGE)/Override/UefiCpuPkg/SecCore/SecCore.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/PeiPcdLib/PeiPcdLib.inf
!if $(TARGET) == DEBUG
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
!endif
  }

!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Universal/CapsulePei201905/CapsulePei.inf {
    <LibraryClasses>
!if ($(TARGET) == RELEASE) AND (gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable == TRUE)
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
!endif
  }
!else
  $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Universal/CapsulePei/CapsulePei.inf {
    <LibraryClasses>
!if ($(TARGET) == RELEASE) AND (gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable == TRUE)
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
!endif
  }
!endif
!endif


#
# CpuMp PEIM for MpService PPI
#
!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == FALSE
  UefiCpuPkg/CpuMpPei/CpuMpPei.inf
!else
!if gSiPkgTokenSpaceGuid.PcdFspModeSelection == 1
  UefiCpuPkg/CpuMpPei/CpuMpPei.inf {
    <LibraryClasses>
      NULL|$(PLATFORM_SI_PACKAGE)/Library/PeiReadyToInstallMpLib/PeiReadyToInstallMpLib.inf
  }
!endif #PcdFspModeSelection
!endif #PcdFspWrapperEnable
#
# Silicon
#
!include $(C1S_PRODUCT_PATH)/SiPkgPei.dsc

#
# This is for reducing NATIVE DEBUG binary size, replacing some library routines with PPI.
#
!if $(TARGET) == DEBUG
  $(CLIENT_COMMON_PACKAGE)/Universal/DebugServicePei/DebugServicePei.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
      DebugLib|MdeModulePkg/Library/PeiDxeDebugLibReportStatusCode/PeiDxeDebugLibReportStatusCode.inf
  }
!endif

$(CLIENT_COMMON_PACKAGE)/Universal/PlatformStatusCodeHandler/Pei/PlatformStatusCodeHandlerPei.inf {
    <LibraryClasses>
!if $(TARGET) == DEBUG
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
!else
!if gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable == TRUE
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
!endif
!endif
  }
$(PLATFORM_FEATURES_PATH)/PlatformStatusCodeHandler/Pei/PlatformStatusCodeHandlerPei.inf {
    <LibraryClasses>
!if $(TARGET) == DEBUG
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
!else
!if gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable == TRUE
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
!endif
!endif
}

#
# Platform
#
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == FALSE
  $(PLATFORM_PACKAGE)/PlatformInit/ReportFv/ReportFvPei.inf
!endif
  $(PLATFORM_FULL_PACKAGE)/Override/MinPlatformPkg/PlatformInit/PlatformInitPei/PlatformInitPreMem.inf {
    <LibraryClasses>
      NULL|$(PROJECT_EHL_BOARDS)/Library/BoardInitLib/Pei/PeiMultiBoardInitPreMemLib.inf
  }

!if gBoardModuleTokenSpaceGuid.PcdAdvancedFeatureEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/PlatformInitAdvanced/PlatformInitAdvancedPei/PlatformInitAdvancedPreMemBfx.inf {
    <LibraryClasses>
      PeiPlatformRecoveryLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPlatformRecoveryLib/PeiPlatformRecoveryLib.inf
      PeiWdtAppLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiWdtAppLib/PeiWdtAppLib.inf
      ProcessorTraceMemoryAllocationLib|$(PLATFORM_SI_PACKAGE)/Library/PeiProcessorTraceMemoryAllocationLib/PeiProcessorTraceMemoryAllocationLib.inf
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
      NULL|$(PLATFORM_FULL_PACKAGE)/Library/PeiSecPpiReinstallLib/PeiSecPpiReinstallLib.inf
!endif
  }
!else
  $(PLATFORM_FULL_PACKAGE)/PlatformInitAdvanced/PlatformInitAdvancedPei/PlatformInitAdvancedPreMem.inf {
    <LibraryClasses>
      PeiPlatformRecoveryLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiPlatformRecoveryLib/PeiPlatformRecoveryLib.inf
      PeiWdtAppLib|$(PLATFORM_FULL_PACKAGE)/Library/PeiWdtAppLib/PeiWdtAppLib.inf
      ProcessorTraceMemoryAllocationLib|$(PLATFORM_SI_PACKAGE)/Library/PeiProcessorTraceMemoryAllocationLib/PeiProcessorTraceMemoryAllocationLib.inf
  }
!endif
!endif  # PcdAdvancedFeatureEnable

  $(PLATFORM_PACKAGE)/PlatformInit/PlatformInitPei/PlatformInitPostMem.inf {
    <LibraryClasses>
      NULL|$(PROJECT_EHL_BOARDS)/Library/BoardInitLib/Pei/PeiMultiBoardInitPostMemLib.inf
  }

!if gBoardModuleTokenSpaceGuid.PcdAdvancedFeatureEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/PlatformInitAdvanced/PlatformInitAdvancedPei/PlatformInitAdvancedPostMemFsp.inf
!else
  $(PLATFORM_FULL_PACKAGE)/PlatformInitAdvanced/PlatformInitAdvancedPei/PlatformInitAdvancedPostMem.inf
!endif
!endif  # PcdAdvancedFeatureEnable

  $(PLATFORM_BOARD_PACKAGE)/BiosInfo/BiosInfo.inf

!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/BiosInfoRecovery/BiosInfoRecovery.inf
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/Platform/BiosInfoChecker/BiosInfoChecker.inf
!endif
  $(PLATFORM_PACKAGE)/Services/StallServicePei/StallServicePei.inf

!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
 $(PLATFORM_FULL_PACKAGE)/Override/IntelFsp2WrapperPkg/FspmWrapperPeim/FspmWrapperPeim.inf {
    <LibraryClasses>
      SiliconPolicyInitLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/SiliconPolicyInitLibNull/SiliconPolicyInitLibNull.inf
      SiliconPolicyUpdateLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/SiliconPolicyUpdateLibNull/SiliconPolicyUpdateLibNull.inf
  }
 $(PLATFORM_FULL_PACKAGE)/Override/IntelFsp2WrapperPkg/FspsWrapperPeim/FspsWrapperPeim.inf {
    <LibraryClasses>
      SiliconPolicyInitLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/SiliconPolicyInitLibNull/SiliconPolicyInitLibNull.inf
      SiliconPolicyUpdateLib|$(PLATFORM_PACKAGE)/PlatformInit/Library/SiliconPolicyUpdateLibNull/SiliconPolicyUpdateLibNull.inf
  }
  $(PLATFORM_FULL_PACKAGE)/FspWrapper/FspWrapperPeim/FspWrapperPeim.inf
!endif

#
# S3
#
!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
  UefiCpuPkg/Universal/Acpi/S3Resume2Pei/S3Resume2Pei.inf
  UefiCpuPkg/PiSmmCommunication/PiSmmCommunicationPei.inf
!if gPlatformModuleTokenSpaceGuid.PcdOpalPasswordEnable == TRUE
  SecurityPkg/Tcg/Opal/OpalPassword/OpalPasswordPei.inf
!endif
!endif

#
# Security
#
!if gPlatformModuleTokenSpaceGuid.PcdTpmEnable == TRUE
  SecurityPkg/Tcg/PhysicalPresencePei/PhysicalPresencePei.inf

!if gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable == TRUE
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(CLIENT_COMMON_PACKAGE)/Override/SecurityPkg/Tcg/Tcg2Config/Tcg2ConfigPei.inf {
      <Defines>
        FILE_GUID = 5FA8B78C-1BE8-4478-8396-57AB35B02232
      <LibraryClasses>
        Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2DeviceLibDTpm.inf
        Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
        Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterPei.inf
        NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
        NULL|$(PLATFORM_FULL_PACKAGE)/Library/PeiBootGuardEventLogLib/PeiBootGuardEventLogLibBfx.inf
        NULL|SecurityPkg/Library/HashInstanceLibSha1/HashInstanceLibSha1.inf
        NULL|SecurityPkg/Library/HashInstanceLibSha256/HashInstanceLibSha256.inf
    }
    !if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == FALSE
      $(PLATFORM_FULL_PACKAGE)/Override/SecurityPkg/Tcg/Tcg2Pei/Tcg2Pei.inf {
        <Defines>
          FILE_GUID = 5CA8EC13-18DE-48E6-B037-67A2772F3EBB
        <LibraryClasses>
          Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
          Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterPei.inf
          NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
          NULL|SecurityPkg/Library/HashInstanceLibSha1/HashInstanceLibSha1.inf
          NULL|SecurityPkg/Library/HashInstanceLibSha256/HashInstanceLibSha256.inf
      }
    !else
      $(PLATFORM_FULL_PACKAGE)/Override/SecurityPkg/Tcg/Tcg2Pei/Tcg2Pei201905.inf {
        <Defines>
          FILE_GUID = 5CA8EC13-18DE-48E6-B037-67A2772F3EBB
        <LibraryClasses>
          Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
          Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterPei.inf
          NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
          NULL|SecurityPkg/Library/HashInstanceLibSha1/HashInstanceLibSha1.inf
          NULL|SecurityPkg/Library/HashInstanceLibSha256/HashInstanceLibSha256.inf
      }
    !endif
  !else
    $(CLIENT_COMMON_PACKAGE)/Universal/Tcg/Tcg2Config/Tcg2ConfigPei.inf {
      <Defines>
        FILE_GUID = 5FA8B78C-1BE8-4478-8396-57AB35B02232
      <LibraryClasses>
        Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2DeviceLibDTpm.inf
        Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
        Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterPei.inf
        NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
        NULL|$(PLATFORM_FULL_PACKAGE)/Library/PeiBootGuardEventLogLib/PeiBootGuardEventLogLib.inf
        NULL|SecurityPkg/Library/HashInstanceLibSha1/HashInstanceLibSha1.inf
        NULL|SecurityPkg/Library/HashInstanceLibSha256/HashInstanceLibSha256.inf
    }
    SecurityPkg/Tcg/Tcg2Pei/Tcg2Pei.inf {
      <Defines>
        FILE_GUID = 5CA8EC13-18DE-48E6-B037-67A2772F3EBB
      <LibraryClasses>
        Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
        Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterPei.inf
        NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
        NULL|SecurityPkg/Library/HashInstanceLibSha1/HashInstanceLibSha1.inf
        NULL|SecurityPkg/Library/HashInstanceLibSha256/HashInstanceLibSha256.inf
    }
  !endif

  $(CLIENT_COMMON_PACKAGE)/Universal/Tcg2PlatformPei/Tcg2PlatformPei.inf  {
    <LibraryClasses>
      Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
      Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterPei.inf
      NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
  }
!endif

  SecurityPkg/Tcg/TcgPei/TcgPei.inf
!endif # gPlatformModuleTokenSpaceGuid.PcdTpmEnable



#
# Features
#
!if gBoardModuleTokenSpaceGuid.PcdSetupEnable == TRUE
  !include $(PLATFORM_BOARD_PACKAGE)/Features/Setup/Include/Dsc/SetupPei.dsc
!endif

 MdeModulePkg/Universal/ResetSystemPei/ResetSystemPei.inf {
   <LibraryClasses>
     ResetSystemLib|$(PLATFORM_SI_PACKAGE)/Pch/Library/BaseResetSystemLib/BaseResetSystemLib.inf
 }

#
# VTd Iommu Security for Pei
#
  $(PLATFORM_FEATURES_PATH)/VTd/PlatformVTdInfoSamplePei/PlatformVTdInfoSamplePei.inf
  $(PLATFORM_FEATURES_PATH)/VTd/IntelVTdPmrPei/IntelVTdPmrPei.inf

!if gSiPkgTokenSpaceGuid.PcdAmtEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/Amt/AmtStatusCodePei/AmtStatusCodePei.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdOverclockEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/OverClocking/OverClockInit/PeiOverClock.inf
!endif

!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
  # Recovery module
!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == FALSE
  $(PLATFORM_FULL_PACKAGE)/Override/FatPkg/FatPei/FatPei.inf # RPPO-CNL-0087: RoyalParkOverrideContent
!else
  FatPkg/FatPei/FatPei.inf
!endif
  $(PLATFORM_FEATURES_PATH)/Sata/AtaDeviceDriverPei/AtaDeviceDriverPei.inf
  $(PLATFORM_FEATURES_PATH)/Nvme/NvmExpressHcPlatformPei/NvmePciHcPei.inf
  $(PLATFORM_FEATURES_PATH)/Nvme/NvmExpressPei/NvmExpressPei.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdPeiDisplayEnable == TRUE
!if gBoardModuleTokenSpaceGuid.PcdGopConfigBin == FALSE
!endif # PcdGopConfigBin
!endif # PcdSleEnable

!if gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable == TRUE
  MdeModulePkg/Universal/Acpi/FirmwarePerformanceDataTablePei/FirmwarePerformancePei.inf {
    <LibraryClasses>
      TimerLib|PcAtChipsetPkg/Library/AcpiTimerLib/BaseAcpiTimerLib.inf
  }
!endif

!if gSiPkgTokenSpaceGuid.PcdPpamEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/NiftyRock/MsegSmramPei/MsegSmramPei.inf
!endif

!if gBoardModuleTokenSpaceGuid.PcdUfsEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Bus/Pci/UfsPciHcPei/UfsPciHcPei.inf
  $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Bus/Ufs/UfsBlockIoPei/UfsBlockIoPei.inf
!endif
!endif

[Components.X64]

#
# Common
#
#
# Board specific instance of CoreDxeInclude.dsc from MinPlatformPkg
#
!include $(PLATFORM_BOARD_PACKAGE)/Include/Dsc/CoreDxeInclude.dsc

!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/Platform/PlatformHmacShaSmm/PlatformHmacShaSmm.inf
  $(PLATFORM_FULL_PACKAGE)/VariableStorageSelector/Dxe/VariableStorageSelectorRuntimeDxe.inf
  $(PLATFORM_SI_PACKAGE)/VariableStorage/Dxe/FvbVariableStorageSmmRuntimeDxe/FvbVariableStorageRuntimeDxe.inf
  $(PLATFORM_FULL_PACKAGE)/VariableStorageSelector/Smm/VariableStorageSelectorSmm.inf
  $(PLATFORM_SI_PACKAGE)/VariableStorage/Dxe/FvbVariableStorageSmmRuntimeDxe/FvbVariableStorageSmm.inf
  $(PLATFORM_SI_PACKAGE)/VariableStorage/Smm/CseVariableStorageSmm/CseVariableStorageSmm.inf {
    <LibraryClasses>
      NULL|$(PLATFORM_FULL_PACKAGE)/Library/BaseSecurePreMemoryDataInitLib/BaseSecurePreMemoryDataInitLib.inf
  }
  $(PLATFORM_SI_PACKAGE)/VariableStorage/Dxe/CseCommandQueueRuntimeDxe/CseCommandQueueRuntimeDxe.inf
!endif

  UefiCpuPkg/CpuDxe/CpuDxe.inf
#
# S3
#
  UefiCpuPkg/CpuS3DataDxe/CpuS3DataDxe.inf

  MdeModulePkg/Bus/Pci/PciHostBridgeDxe/PciHostBridgeDxe.inf

  MdeModulePkg/Bus/Pci/SataControllerDxe/SataControllerDxe.inf
  MdeModulePkg/Bus/Ata/AtaBusDxe/AtaBusDxe.inf
  MdeModulePkg/Bus/Ata/AtaAtapiPassThru/AtaAtapiPassThru.inf
!if gBoardModuleTokenSpaceGuid.PcdUfsEnable == TRUE
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(PLATFORM_FEATURES_PATH)/Ufs/UfsEarlyInitDxe/UfsEarlyInitDxe.inf {
       <LibraryClasses>
!if $(TARGET) == DEBUG
         DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
       <PcdsPatchableInModule>
         gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000147
!endif
    }
    $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Bus/Pci/UfsPciHcDxe/UfsPciHcDxe.inf {
       <LibraryClasses>
!if $(TARGET) == DEBUG
         DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
       <PcdsPatchableInModule>
         gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000147
!endif
    }
    $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Bus/Ufs/UfsPassThruDxe/UfsPassThruDxe.inf {
       <LibraryClasses>
!if $(TARGET) == DEBUG
         DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
       <PcdsPatchableInModule>
         gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000147
!endif
    }
  !else
    MdeModulePkg/Bus/Pci/UfsPciHcDxe/UfsPciHcDxe.inf
    $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Bus/Ufs/UfsPassThruDxe/UfsPassThruDxe.inf
  !endif
!endif
  $(PLATFORM_FEATURES_PATH)/EmmcSoftwareTuningStorage/EmmcSoftwareTuningStorage.inf
!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Bus/Pci/SdMmcPciHcDxe201905/SdMmcPciHcDxe.inf
!else
  $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Bus/Pci/SdMmcPciHcDxe/SdMmcPciHcDxe.inf
!endif
  MdeModulePkg/Bus/Sd/EmmcDxe/EmmcDxe.inf
  MdeModulePkg/Bus/Sd/SdDxe/SdDxe.inf
  MdeModulePkg/Universal/Console/GraphicsOutputDxe/GraphicsOutputDxe.inf
!if gSiPkgTokenSpaceGuid.PcdSerialIoUartEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/SerialIoDxe/SerialIoDxe.inf
!endif
  MdeModulePkg/Bus/Pci/PciSioSerialDxe/PciSioSerialDxe.inf
  MdeModulePkg/Bus/Pci/NvmExpressDxe/NvmExpressDxe.inf
  $(CLIENT_COMMON_PACKAGE)/Sio/NationalPC8374LDxe/NationalPC8374L.inf
  $(CLIENT_COMMON_PACKAGE)/Sio/SmscLpc100xDxe/LpcSmsc100x.inf
  $(CLIENT_COMMON_PACKAGE)/Sio/HitachiH8s2113Dxe/HitachiH8s2113Dxe.inf
  $(CLIENT_COMMON_PACKAGE)/Sio/WinbondWpcn381uDxe/WinbondWpcn381u.inf

!if (gSiPkgTokenSpaceGuid.PcdAtaEnable == TRUE) OR (gBoardModuleTokenSpaceGuid.PcdNvmeEnable == TRUE)
!if gPlatformModuleTokenSpaceGuid.PcdOpalPasswordEnable == TRUE
  SecurityPkg/Tcg/Opal/OpalPassword/OpalPasswordDxe.inf
!endif
!endif

!if gBoardModuleTokenSpaceGuid.PcdTerminalEnable == TRUE
  MdeModulePkg/Universal/Console/TerminalDxe/TerminalDxe.inf
!endif

#
#UEFI Shell
#
  ShellPkg/Application/Shell/Shell.inf {
    <LibraryClasses>
      NULL|ShellPkg/Library/UefiShellLevel2CommandsLib/UefiShellLevel2CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellLevel1CommandsLib/UefiShellLevel1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellLevel3CommandsLib/UefiShellLevel3CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellDriver1CommandsLib/UefiShellDriver1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellInstall1CommandsLib/UefiShellInstall1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellDebug1CommandsLib/UefiShellDebug1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellNetwork1CommandsLib/UefiShellNetwork1CommandsLib.inf

    <PcdsFixedAtBuild>
      gEfiShellPkgTokenSpaceGuid.PcdShellLibAutoInitialize|FALSE
  }

!if gPlatformModuleTokenSpaceGuid.PcdFatEnable == TRUE
  MdeModulePkg/Universal/Disk/RamDiskDxe/RamDiskDxe.inf
!endif

!if gPlatformModuleTokenSpaceGuid.PcdCryptoEnable == TRUE
  SecurityPkg/RandomNumberGenerator/RngDxe/RngDxe.inf {
    <LibraryClasses>
      RngLib|MdePkg/Library/BaseRngLib/BaseRngLib.inf
  }
!endif

!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
  MdeModulePkg/Universal/CapsulePei/CapsuleX64.inf {
    <LibraryClasses>
      TimerLib|PcAtChipsetPkg/Library/AcpiTimerLib/BaseAcpiTimerLib.inf
      HobLib|MdePkg/Library/PeiHobLib/PeiHobLib.inf
      MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
        Usb3DebugPortLib|BpCommonPkg/Library/Usb3DebugPortLib/Usb3DebugPortLibPei.inf
      !if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
        TraceHubDebugLib|BpCommonPkg/Library/TraceHubDebugLibSvenTx/PeiTraceHubDebugLibSvenTx.inf
      !endif
      !if gSiPkgTokenSpaceGuid.PcdSourceDebugEnable == TRUE
        PeiMeLib|$(PLATFORM_SI_PACKAGE)/Me/Library/PeiMeLib/PeiMeLib.inf
      !endif
  }
!endif

#
# I2C Stack:Start
#
!if gPlatformModuleTokenSpaceGuid.PcdPiI2cStackEnable == TRUE
  MdeModulePkg/Bus/I2c/I2cDxe/I2cDxe.inf
  $(PLATFORM_FEATURES_PATH)/I2c/I2cPlatformDxe/I2cPlatformDxe.inf
!endif

!if gPlatformModuleTokenSpaceGuid.PcdI2cTouchDriverEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/I2c/I2cTouchPanelDxe/I2cTouchPanelDxe.inf
!endif
#
# I2C Stack:End
#

!if gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable == TRUE
# @todo SecureBootConfigDxe is not successfully overridden by this change. Due to this secure boot BIOS setup page goes to TPV page instead of Boot Maintenance menu.
  SecurityPkg/VariableAuthenticated/SecureBootConfigDxe/SecureBootConfigDxe.inf {
    <Defines>
    FILE_GUID = 84095540-92C0-433B-9B37-AD2FF7CF8E6A
    <LibraryClasses>
      PlatformSecureLib|$(PLATFORM_FULL_PACKAGE)/Library/PlatformSecureLibTest/PlatformSecureLibTest.inf
      FileExplorerLib|MdeModulePkg/Library/FileExplorerLib/FileExplorerLib.inf
    <BuildOptions>
      #
      # Specify GUID gEfiIfrBootMaintenanceGuid, to install Secure Boot Configuration menu
      # into Boot Maintenance Manager menu
      #
      *_*_*_VFR_FLAGS   = -g b2dedc91-d59f-48d2-898a-12490c74a4e0
  }
!endif


!if gBoardModuleTokenSpaceGuid.PcdAdvancedFeatureEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/PlatformInitAdvanced/PlatformInitAdvancedSmm/PlatformInitAdvancedSmmBfx.inf {
     <BuildOptions>
       *_*_X64_CC_FLAGS      = -DDOCK_ENABLE
  }
!else
  $(PLATFORM_FULL_PACKAGE)/PlatformInitAdvanced/PlatformInitAdvancedSmm/PlatformInitAdvancedSmm.inf {
     <BuildOptions>
       *_*_X64_CC_FLAGS      = -DDOCK_ENABLE
  }
!endif
!endif
!endif


#
# Silicon
#
!include $(C1S_PRODUCT_PATH)/SiPkgDxe.dsc

#
# Network
#
$(PLATFORM_FEATURES_PATH)/Cnv/CnvUefiVariables/CnvUefiVariables.inf
!if gPlatformModuleTokenSpaceGuid.PcdNetworkEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == TRUE
!include NetworkPkg/NetworkComponents.dsc.inc
!else
!if gPlatformModuleTokenSpaceGuid.PcdNetworkIscsiEnable == TRUE
  NetworkPkg/IScsiDxe/IScsiDxe.inf
!endif
!if gPlatformModuleTokenSpaceGuid.PcdNetworkVlanEnable == TRUE
  MdeModulePkg/Universal/Network/VlanConfigDxe/VlanConfigDxe.inf
!endif
  #
  # UEFI network modules
  #
  MdeModulePkg/Universal/Network/SnpDxe/SnpDxe.inf
  MdeModulePkg/Universal/Network/DpcDxe/DpcDxe.inf
  MdeModulePkg/Universal/Network/MnpDxe/MnpDxe.inf
  MdeModulePkg/Universal/Network/ArpDxe/ArpDxe.inf
  MdeModulePkg/Universal/Network/Dhcp4Dxe/Dhcp4Dxe.inf
  MdeModulePkg/Universal/Network/Ip4Dxe/Ip4Dxe.inf
  MdeModulePkg/Universal/Network/Mtftp4Dxe/Mtftp4Dxe.inf
  NetworkPkg/TcpDxe/TcpDxe.inf
  MdeModulePkg/Universal/Network/Udp4Dxe/Udp4Dxe.inf
  NetworkPkg/DnsDxe/DnsDxe.inf
  NetworkPkg/HttpDxe/HttpDxe.inf
  NetworkPkg/HttpUtilitiesDxe/HttpUtilitiesDxe.inf
  NetworkPkg/HttpBootDxe/HttpBootDxe.inf
!if gPlatformModuleTokenSpaceGuid.PcdNetworkIp6Enable == TRUE
  NetworkPkg/Ip6Dxe/Ip6Dxe.inf
  NetworkPkg/Dhcp6Dxe/Dhcp6Dxe.inf
  NetworkPkg/IpSecDxe/IpSecDxe.inf
  NetworkPkg/Udp6Dxe/Udp6Dxe.inf
  NetworkPkg/Mtftp6Dxe/Mtftp6Dxe.inf
!endif
  NetworkPkg/UefiPxeBcDxe/UefiPxeBcDxe.inf
!endif
# Temporary workaround for GCC and Xcode build due to these drivers causes system hang.
!if ("MSFT" in $(FAMILY))
  $(PLATFORM_FEATURES_PATH)/WifiConnectionManagerDxe/WifiConnectionManagerDxe.inf
  BpCommonPkg/Bluetooth/BluetoothConnectionManagerDxe/BluetoothConnectionManagerDxe.inf
!endif
  BpCommonPkg/Bluetooth/UsbBtHciDxe/UsbBtHciDxe.inf
  BpCommonPkg/Bluetooth/BluetoothBusDxe/BluetoothBusDxe.inf
  BpCommonPkg/Bluetooth/BluetoothHidDxe/BluetoothHidDxe.inf
  BpCommonPkg/Bluetooth/HidKbDxe/HidKbDxe.inf
  BpCommonPkg/Bluetooth/HidMouseDxe/HidMouseDxe.inf
!endif # gPlatformModuleTokenSpaceGuid.PcdNetworkEnable

!if ("MSFT" in $(FAMILY))
!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
  # capsule related drivers and Application.
  MdeModulePkg/Universal/EsrtFmpDxe/EsrtFmpDxe.inf
  MdeModulePkg/Application/CapsuleApp/CapsuleApp.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
  }
  !include $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/FmpPlatformMonolithic.dsc
  !include $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/FmpPlatformBios.dsc
  !include $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/FmpPlatformMe.dsc
  !include $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/FmpPlatformIshPdt.dsc
  !include $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/FmpPlatformTsnMacAddr.dsc
  !include $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/FmpPlatformPseTsnIpConfig.dsc
  !include $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/FmpPlatformTsnConfig.dsc
  !include $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/FmpPlatformSiipFw.dsc
  !include $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/FmpPlatformOobConfig.dsc
  !include $(PLATFORM_FEATURES_PATH)/CapsuleUpdate/FmpPlatformTccConfig.dsc

!endif
!endif

#
# SMBIOS
#
!if gSiPkgTokenSpaceGuid.PcdSmbiosEnable == TRUE
  MdeModulePkg/Universal/SmbiosDxe/SmbiosDxe.inf
  $(PLATFORM_FULL_PACKAGE)/Platform/SmbiosPlatformInfo/SmbiosPlatformInfo.inf
  $(PLATFORM_FEATURES_PATH)/Smbios/SmbiosMiscDxe/SmbiosMiscDxe.inf
  $(PLATFORM_FEATURES_PATH)/Me/MeSmbiosDxe/MeSmbiosDxe.inf
!endif


#
# AcpiTables
#
!if gPlatformModuleTokenSpaceGuid.PcdDTbtEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/Tbt/TbtInit/Smm/DTbtSmm.inf
  $(PLATFORM_FEATURES_PATH)/Tbt/TbtInit/Dxe/DTbtDxe.inf
!endif

#
# VTd Iommu Security
#
  $(PLATFORM_FEATURES_PATH)/VTd/PlatformVTdSampleDxe/PlatformVTdSampleDxe.inf
  IntelSiliconPkg/Feature/VTd/IntelVTdDxe/IntelVTdDxe.inf

#
# Platform
#
  $(PLATFORM_PACKAGE)/PlatformInit/SiliconPolicyDxe/SiliconPolicyDxe.inf
  $(PLATFORM_PACKAGE)/PlatformInit/PlatformInitDxe/PlatformInitDxe.inf {
    <LibraryClasses>
    NULL|$(PROJECT_EHL_BOARDS)/Library/BoardInitLib/Dxe/DxeMultiBoardInitlib.inf
  }
  $(PLATFORM_FULL_PACKAGE)/PlatformInitAdvanced/PlatformInitAdvancedDxe/PlatformInitAdvancedDxe.inf {
    <LibraryClasses>
      BootGuardRevocationLib|$(PLATFORM_FULL_PACKAGE)/Library/BootGuardRevocationLib/BootGuardRevocationLib.inf
      DxeFirmwareVersionInfoLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeFirmwareVersionInfoLib/DxeFirmwareVersionInfoLib.inf
      DxeSmbiosDataHobLib|IntelSiliconPkg/Library/DxeSmbiosDataHobLib/DxeSmbiosDataHobLib.inf
      DxeSmbiosFirmwareVersionInfoLib|$(CLIENT_COMMON_PACKAGE)/Library/DxeSmbiosFirmwareVersionInfoLib/DxeSmbiosFirmwareVersionInfoLib.inf
  }

!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdFspModeSelection == 1
  IntelFsp2WrapperPkg/FspWrapperNotifyDxe/FspWrapperNotifyDxe.inf
!endif
!endif
  $(PLATFORM_FULL_PACKAGE)/Platform/SaveMemoryConfig/Dxe/SaveMemoryConfig.inf
# @todo Re-evaluate use case for the MultiFv modules and update for the flash map.
#  $(PLATFORM_FEATURES_PATH)/MultiFv/DecompressFvMain2Dxe/DecompressFvMain2Dxe.inf
#!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
#!if gSiPkgTokenSpaceGuid.PcdFspModeSelection == 0
#  $(PLATFORM_FEATURES_PATH)/MultiFv/DecompressFspsDxe/DecompressFspsDxe.inf
#!endif
#!endif
#  $(PLATFORM_FEATURES_PATH)/MultiFv/DecompressFvCnvDxe/DecompressFvCnvDxe.inf

  $(PLATFORM_PACKAGE)/Test/TestPointStubDxe/TestPointStubDxe.inf
  $(PLATFORM_PACKAGE)/Test/TestPointDumpApp/TestPointDumpApp.inf

!if gBoardModuleTokenSpaceGuid.PcdSetupEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/UiApp/UiApp.inf {
  <Defines>
  FILE_GUID = D89A7D8B-D016-4D26-93E3-EAB6B4D3B0A2
  }
!endif #PcdSetupEnable == TRUE

!if gBoardModuleTokenSpaceGuid.PcdSetupEnable == TRUE
  !include $(PLATFORM_BOARD_PACKAGE)/Features/Setup/Include/Dsc/SetupDxe.dsc

!if gPlatformModuleTokenSpaceGuid.PcdUserAuthenticationEnable == TRUE
  UserInterfaceFeaturePkg/UserAuthentication/UserAuthentication2Dxe.inf {
    <LibraryClasses>
      PlatformPasswordLib|UserInterfaceFeaturePkg/Library/PlatformPasswordLibNull/PlatformPasswordLibNull.inf
    }
  UserInterfaceFeaturePkg/UserAuthentication/UserAuthenticationSmm.inf {
    <LibraryClasses>
      PlatformPasswordLib|UserInterfaceFeaturePkg/Library/PlatformPasswordLibNull/PlatformPasswordLibNull.inf
    }
!endif
!endif
#  $(PLATFORM_BOARD_PACKAGE)/BootMediaInfo/BootMediaInfo.inf

!if gMinPlatformPkgTokenSpaceGuid.PcdStopAfterMemInit == FALSE
  $(PLATFORM_FULL_PACKAGE)/Override/UefiCpuPkg/PiSmmCpuDxeSmm/PiSmmCpuDxeSmm.inf {
  <LibraryClasses>
      SmmCpuFeaturesLib|$(PLATFORM_SI_PACKAGE)/Cpu/Library/SmmCpuFeaturesLib/SmmCpuFeaturesLib.inf
  }
!endif #PcdStopAfterMemInit

  $(PLATFORM_FEATURES_PATH)/Icc/IccPlatformDxe/IccPlatformDxe.inf

#
# OS Boot
#
!if gMinPlatformPkgTokenSpaceGuid.PcdBootToShellOnly == FALSE
!if gBoardModuleTokenSpaceGuid.PcdAdvancedFeatureEnable == TRUE
  $(PLATFORM_BOARD_PACKAGE)/Acpi/AdvancedAcpiDxe/AdvancedAcpiDxe.inf
  $(PLATFORM_FEATURES_PATH)/Acpi/AcpiTables/AcpiFeatures.inf
  $(PLATFORM_BOARD_PACKAGE)/Acpi/AcpiTables/AcpiTables.inf
  $(PLATFORM_FEATURES_PATH)/Dptf/AcpiTables/DptfAcpiTables.inf
  $(PLATFORM_FEATURES_PATH)/Dptf/AcpiTables/Sds/DptfAcpiTablesSds.inf
  $(PLATFORM_FEATURES_PATH)/Dptf/Dxe/Dptf.inf
!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/Pep/Smm/PepBccdSmm.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdPpamEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/NiftyRock/PpamPlatformSmm/PpamPlatformSmm.inf
!endif
!if gSiPkgTokenSpaceGuid.PcdOverclockEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/OverClocking/OverClockInit/DxeOverClock.inf
  $(PLATFORM_FEATURES_PATH)/OverClocking/OverclockInterface/OverclockInterface.inf
  $(PLATFORM_FEATURES_PATH)/OverClocking/OverclockInterface/OverclockInterfaceACPI.inf
  $(PLATFORM_FEATURES_PATH)/OverClocking/OverclockInterface/OverClockSmiHandler.inf
!endif #PcdOverclockEnable
!else
  $(PLATFORM_PACKAGE)/Acpi/AcpiTables/AcpiPlatform.inf {
    <LibraryClasses>
      NULL|$(PROJECT_EHL_BOARDS)/Library/BoardAcpiLib/BaseMultiBoardAcpiSupportLib.inf
  }
  $(PLATFORM_BOARD_PACKAGE)/Acpi/BoardAcpiDxe/BoardAcpiDxe.inf {
    <LibraryClasses>
      NULL|$(PROJECT_EHL_BOARDS)/Library/BoardAcpiLib/BaseMultiBoardAcpiSupportLib.inf
  }
  $(PLATFORM_PACKAGE)/PlatformInit/PlatformInitSmm/PlatformInitSmm.inf
  $(PLATFORM_PACKAGE)/Acpi/AcpiSmm/AcpiSmm.inf {
    <LibraryClasses>
      NULL|$(PLATFORM_BOARD_PACKAGE)/SmmMultiBoardAcpiSupportLib/SmmMultiBoardAcpiSupportLib.inf
  }
!endif #PcdAdvancedFeatureEnable

  $(PLATFORM_FULL_PACKAGE)/Platform/SpiFvbService/SpiFvbServiceDxe.inf
!if gSiPkgTokenSpaceGuid.PcdSmmVariableEnable == TRUE
  $(PLATFORM_PACKAGE)/Flash/SpiFvbService/SpiFvbServiceSmm.inf
!endif # gSiPkgTokenSpaceGuid.PcdSmmVariableEnable

!if gSiPkgTokenSpaceGuid.PcdSmmVariableEnable == TRUE
  !if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
    !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
      $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf
    !else
      MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf
    !endif
  !endif
!else
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf
  !else
    MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf
  !endif
!endif
!if gPlatformModuleTokenSpaceGuid.PcdUsbEnable == TRUE
  MdeModulePkg/Bus/Usb/UsbMouseDxe/UsbMouseDxe.inf
!endif

  $(PLATFORM_FEATURES_PATH)/Me/MeUlvCheckDxe/MeUlvCheckDxe.inf

!endif #PcdBootToShellOnly

#
# S3
#
!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
  MdeModulePkg/Universal/LockBox/SmmLockBox/SmmLockBox.inf
  UefiCpuPkg/PiSmmCommunication/PiSmmCommunicationSmm.inf
  MdeModulePkg/Universal/Acpi/S3SaveStateDxe/S3SaveStateDxe.inf
  MdeModulePkg/Universal/Acpi/SmmS3SaveState/SmmS3SaveState.inf
  MdeModulePkg/Universal/Acpi/BootScriptExecutorDxe/BootScriptExecutorDxe.inf {
    <LibraryClasses>
!if $(TARGET) == DEBUG
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
      TraceHubDebugLib|BpCommonPkg/Library/TraceHubDebugLibSvenTx/BaseTraceHubDebugLibSvenTx.inf
!endif
  }
!endif # gSiPkgTokenSpaceGuid.PcdS3Enable

#
# Trusty Seed
#
!if gSiPkgTokenSpaceGuid.PcdEhlPchEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == FALSE
$(PLATFORM_FEATURES_PATH)/SeedProtocol/RuntimeDxe/SeedProtocolDxe.inf
!endif

#
# Trusty Seed Test
#
$(PLATFORM_FEATURES_PATH)/SeedProtocol/TestApp/BLSeedTest.inf
!endif

#
# Security
#

!if gPlatformModuleTokenSpaceGuid.PcdTpmEnable == TRUE
  SecurityPkg/Tcg/TcgConfigDxe/TcgConfigDxe.inf {
    <BuildOptions>
      #
      # specify GUID gEfiIfrNotInTPVPageGuid, this page will not
      # be showed in TPV page.
      #
      *_*_*_VFR_FLAGS   = -g 1947c034-062f-44c0-bcc4-19927afe9ea4
  }

!if gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable == TRUE
  SecurityPkg/Tcg/Tcg2Dxe/Tcg2Dxe.inf {
    <Defines>
    FILE_GUID = EFCB058E-8BDC-4062-8DAE-8262886C512B
    <LibraryClasses>
      Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
      Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterDxe.inf
      NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha1/HashInstanceLibSha1.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha256/HashInstanceLibSha256.inf
!if $(TARGET) == DEBUG
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
      SerialPortParameterLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeSmmSerialPortParameterLib/DxeSmmSerialPortParameterLib.inf
      SerialIoUartDebugPropertyLib|$(PLATFORM_FULL_PACKAGE)/Library/SerialIoUartDebugPropertyLib/DxeSmmSerialIoUartDebugPropertyLib.inf
!endif
  }
# use Client Common Tcg2ConfigDxe when porting
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  $(CLIENT_COMMON_PACKAGE)/Override/SecurityPkg/Tcg/Tcg2Config/Tcg2ConfigDxe.inf {
    <Defines>
      FILE_GUID = 7C81E7E9-5348-41EF-BBCE-10733F6B4595
    <LibraryClasses>
      Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
      Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterDxe.inf
      NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
    <BuildOptions>
      #
      # specify GUID gEfiIfrNotInTPVPageGuid, this page will not
      # be showed in TPV page.
      #
      *_*_*_VFR_FLAGS   = -g 1947c034-062f-44c0-bcc4-19927afe9ea4
  }
!else
  $(CLIENT_COMMON_PACKAGE)/Universal/Tcg/Tcg2Config/Tcg2ConfigDxe.inf {
    <Defines>
      FILE_GUID = 7C81E7E9-5348-41EF-BBCE-10733F6B4595
    <LibraryClasses>
      Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
      Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterDxe.inf
      NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
    <BuildOptions>
      #
      # specify GUID gEfiIfrNotInTPVPageGuid, this page will not
      # be showed in TPV page.
      #
      *_*_*_VFR_FLAGS   = -g 1947c034-062f-44c0-bcc4-19927afe9ea4
  }
!endif
  $(CLIENT_COMMON_PACKAGE)/Universal/Tcg2PlatformDxe/Tcg2PlatformDxe.inf {
    <LibraryClasses>
      Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
      PlatformSecureLib|$(PLATFORM_FULL_PACKAGE)/Library/PlatformSecureLibTest/PlatformSecureLibTest.inf
      NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
  }
  SecurityPkg/Tcg/TcgDxe/TcgDxe.inf {
    <LibraryClasses>
!if $(TARGET) == DEBUG
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
      SerialPortParameterLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeSmmSerialPortParameterLib/DxeSmmSerialPortParameterLib.inf
      SerialIoUartDebugPropertyLib|$(PLATFORM_FULL_PACKAGE)/Library/SerialIoUartDebugPropertyLib/DxeSmmSerialIoUartDebugPropertyLib.inf
!endif
  }
!endif # gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable

  # module to update variable according to TPM HW state, the code could be in TcgDxe driver but better to be separated
  $(PLATFORM_FEATURES_PATH)/Tcg/TcgSetupDxe/TcgSetupDxe.inf
!endif # gPlatformModuleTokenSpaceGuid.PcdTpmEnable

!if gSiPkgTokenSpaceGuid.PcdAmtEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/Amt/AmtSaveMebxConfigDxe/AmtSaveMebxConfigDxe.inf
  $(PLATFORM_FEATURES_PATH)/Amt/AmtPetAlertDxe/AmtPetAlertDxe.inf
  $(PLATFORM_FEATURES_PATH)/Amt/AsfTable/AsfTable.inf
  $(PLATFORM_FEATURES_PATH)/Amt/AmtWrapperDxe/AmtWrapperDxe.inf
!if gPlatformModuleTokenSpaceGuid.PcdEnableSecureErase == TRUE
  $(PLATFORM_FEATURES_PATH)/Amt/SecureEraseDxe/SecureEraseDxe.inf
!endif
!endif
  $(PLATFORM_FULL_PACKAGE)/Features/Me/MeExtMeasurement/Dxe/MeExtMeasurement.inf
  $(PLATFORM_FULL_PACKAGE)/Features/TrustedDeviceSetup/TrustedDeviceSetup.inf

#
# UsbDeviceMode XDCI
#
!if gPlatformModuleTokenSpaceGuid.PcdUsbFnEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/Usb/UsbDeviceDxe/UsbDeviceDxe.inf
  SecurityPkg/Hash2DxeCrypto/Hash2DxeCrypto.inf
!endif



#
# Crash Log Support
#
$(PLATFORM_FEATURES_PATH)/CrashLogDxe/CrashLogDxe.inf

!if gPlatformModuleTokenSpaceGuid.PcdDnxSupportEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/Dnx/DnxDxe/DnxDxe.inf
!endif

$(PLATFORM_FEATURES_PATH)/FastBoot/FastBootHandlerDxe/FastBootHandlerDxe.inf
$(PLATFORM_FEATURES_PATH)/FastBoot/FastBootSetupDxe/FastBootSetupDxe.inf

  $(PLATFORM_FEATURES_PATH)/Hsti/HstiResultDxe/HstiResultDxe.inf

#
# Hsti
#
$(PLATFORM_FEATURES_PATH)/Hsti/HstiIhvDxe/HstiIhvDxe.inf {
  <LibraryClasses>
    HstiLib|MdePkg/Library/DxeHstiLib/DxeHstiLib.inf
    Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
}

  $(PLATFORM_FEATURES_PATH)/Hsti/HstiIhvSmm/HstiIhvSmm.inf

!if gBoardModuleTokenSpaceGuid.PcdAdvancedFeatureEnable == TRUE
!if gBoardModuleTokenSpaceGuid.PcdSetupEnable == TRUE
!endif

$(PLATFORM_FULL_PACKAGE)/Platform/PciPlatform/Dxe/PciPlatform.inf {
  <LibraryClasses>
    DxeOpromPatchLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeOpromPatchLib/DxeOpromPatchLib.inf
}

!if gPlatformModuleTokenSpaceGuid.PcdPciHotplugEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/Platform/PciHotPlug/PciHotPlug.inf
!endif

!if gPlatformModuleTokenSpaceGuid.PcdUsbTypeCEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/UsbTypeC/UsbTypeCDxe/UsbTypeCDxe.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdAcpiEnable == TRUE
!if gBoardModuleTokenSpaceGuid.PcdAcpiDebugFeatureEnable == TRUE
  DebugFeaturePkg/AcpiDebug/AcpiDebugDxe.inf
!endif
!endif

!if gPlatformModuleTokenSpaceGuid.PcdSimpleBootFlagEnable == TRUE
  $(CLIENT_COMMON_PACKAGE)/Universal/SimpleBootFlagDxe/SimpleBootFlag.inf
!endif

!if gPlatformModuleTokenSpaceGuid.PcdVirtualKeyboardEnable == TRUE
  $(CLIENT_COMMON_PACKAGE)/Universal/VirtualKeyboardDxe/VirtualKeyboardDxe.inf
!endif

!if gPlatformModuleTokenSpaceGuid.PcdEbcEnable == TRUE
  MdeModulePkg/Universal/EbcDxe/EbcDxe.inf
!endif

!if gSiPkgTokenSpaceGuid.PcdAtaEnable == TRUE
!if gPlatformModuleTokenSpaceGuid.PcdHddPasswordEnable == TRUE
  ClientCommonPkg/Universal/HddPassword/Dxe/HddPasswordDxe.inf {
    <BuildOptions>
      #
      # Specify GUID gEfiIfrBootMaintenanceGuid, to install HddPassword Configuration menu
      # into Boot Maintenance Manager menu
      #
      *_*_*_VFR_FLAGS   = -g b2dedc91-d59f-48d2-898a-12490c74a4e0
  }
  ClientCommonPkg/Universal/HddPassword/Smm/HddPasswordSmm.inf {
   <LibraryClasses>
      SmmIoLib|MdePkg/Library/SmmIoLib/SmmIoLib.inf
  }
!endif
!endif

!if gSiPkgTokenSpaceGuid.PcdAtaEnable == TRUE
!if gBoardModuleTokenSpaceGuid.PcdIntelRaidEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/Sata/IntelUefiRaidDiskInfo/IntelUefiRaidDiskInfo.inf
!endif
!endif

$(CLIENT_COMMON_PACKAGE)/Universal/SetTimerPeriodDxe/SetTimerPeriodDxe.inf
  MdeModulePkg/Bus/Isa/Ps2KeyboardDxe/Ps2KeyboardDxe.inf
  !if gPlatformModuleTokenSpaceGuid.PcdMouseEnable == TRUE
    MdeModulePkg/Bus/Isa/Ps2MouseDxe/Ps2MouseDxe.inf
  !endif



#PSDS Table
#
$(PLATFORM_FEATURES_PATH)/PsdsAcpiDxe/PsdsAcpiDxe.inf

!if gPlatformModuleTokenSpaceGuid.PcdGopOverrideDriverEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/Gop/GopOverrideDriver/GopOverrideDriver.inf
!endif

!if gPlatformModuleTokenSpaceGuid.PcdScsiEnable == TRUE
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Bus/Scsi/ScsiBusDxe/ScsiBusDxe.inf
    $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Bus/Scsi/ScsiDiskDxe/ScsiDiskDxe.inf
  !else
    MdeModulePkg/Bus/Scsi/ScsiBusDxe/ScsiBusDxe.inf
    MdeModulePkg/Bus/Scsi/ScsiDiskDxe/ScsiDiskDxe.inf
  !endif
!endif

!if gSiPkgTokenSpaceGuid.PcdAtaEnable == TRUE
  $(PLATFORM_FEATURES_PATH)/Sata/SataController/SataController.inf
!endif

!if gPlatformModuleTokenSpaceGuid.PcdBootTimeEnable == TRUE
  $(CLIENT_COMMON_PACKAGE)/Responsiveness/BootTime/BootTimeDxe.inf
!endif

  $(PLATFORM_FEATURES_PATH)/Wdt/WdtAppDxe/WdtAppDxe.inf

!if gSiPkgTokenSpaceGuid.PcdEmbeddedEnable == TRUE
  $(CLIENT_COMMON_PACKAGE)/Sio/NuvotonNct6776fDxe/NuvotonNct6776f.inf
  $(CLIENT_COMMON_PACKAGE)/Sio/Nct6776fHwMonDxe/Nct6776fHwMon.inf
  $(PLATFORM_FEATURES_PATH)/LifeCycleState/LifeCycleState.inf
!endif

!endif  #PcdAdvancedFeatureEnable

!if gBoardModuleTokenSpaceGuid.PcdEcEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/EC/EC.inf
!endif

!if gBoardModuleTokenSpaceGuid.PcdIntelGopEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/Features/Gop/GopDebugDxe/GopDebugDxe.inf
!endif



!if gPlatformModuleTokenSpaceGuid.PcdVtioEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/Vtio/Dxe/VtioDxe.inf
!endif

  $(CLIENT_COMMON_PACKAGE)/Universal/PlatformStatusCodeHandler/Smm/PlatformStatusCodeHandlerSmm.inf
  $(PLATFORM_FEATURES_PATH)/PlatformStatusCodeHandler/Smm/PlatformStatusCodeHandlerSmm.inf

 $(CLIENT_COMMON_PACKAGE)/Universal/IsvtCheckpointDxe/IsvtCheckpointDxe.inf

!if gBoardModuleTokenSpaceGuid.PcdTerminalEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdSourceDebugEnable == FALSE
  $(CLIENT_COMMON_PACKAGE)/Universal/SpcrAcpiDxe/SpcrAcpiDxe.inf
!endif
!endif

!if gPlatformModuleTokenSpaceGuid.PcdUserIdentificationEnable == TRUE
  SecurityPkg/UserIdentification/UserIdentifyManagerDxe/UserIdentifyManagerDxe.inf
  SecurityPkg/UserIdentification/UserProfileManagerDxe/UserProfileManagerDxe.inf
  SecurityPkg/UserIdentification/PwdCredentialProviderDxe/PwdCredentialProviderDxe.inf
  SecurityPkg/UserIdentification/UsbCredentialProviderDxe/UsbCredentialProviderDxe.inf
!endif

$(PLATFORM_FEATURES_PATH)/Acpi/AcpiTables/SsdtIrmt/IrmtAcpiTables.inf

$(CLIENT_COMMON_PACKAGE)/Universal/PlatformStatusCodeHandler/RuntimeDxe/PlatformStatusCodeHandlerRuntimeDxe.inf {
    <LibraryClasses>
!if $(TARGET) == DEBUG
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
      SerialPortParameterLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeSmmSerialPortParameterLib/DxeSmmSerialPortParameterLib.inf
      SerialIoUartDebugPropertyLib|$(PLATFORM_FULL_PACKAGE)/Library/SerialIoUartDebugPropertyLib/DxeSmmSerialIoUartDebugPropertyLib.inf
!else
!if gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable == TRUE
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
!endif
!endif
}
$(PLATFORM_FEATURES_PATH)/PlatformStatusCodeHandler/RuntimeDxe/PlatformStatusCodeHandlerRuntimeDxe.inf {
    <LibraryClasses>
!if $(TARGET) == DEBUG
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
      SerialPortParameterLib|$(PLATFORM_FULL_PACKAGE)/Library/DxeSmmSerialPortParameterLib/DxeSmmSerialPortParameterLib.inf
      SerialIoUartDebugPropertyLib|$(PLATFORM_FULL_PACKAGE)/Library/SerialIoUartDebugPropertyLib/DxeSmmSerialIoUartDebugPropertyLib.inf
!else
!if gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable == TRUE
      DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
!endif
!endif
}

  EmbeddedRasPkg/WheaErrorInj/WheaErrorInj.inf
  EmbeddedRasPkg/Library/DxeRasGlobalDataLib/DxeRasGlobalDataLib.inf
  $(PLATFORM_FEATURES_PATH)/Pse/OobInit/OobInit.inf

!if (gBoardModuleTokenSpaceGuid.PcdS5ChargingEnable == TRUE)
  $(PLATFORM_FEATURES_PATH)/S5Charging/S5Charging.inf
!endif

  $(PLATFORM_FEATURES_PATH)/PlatformTcoReset/PlatformTcoReset.inf

#
# Build Options
#
!include $(C1S_PRODUCT_PATH)/SiPkgBuildOption.dsc
!include BoardPkgBuildOption.dsc

