## @file
#  Component description file for the ElkhartLake SiPkg DSC file.
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
#@par Specification Reference:
#
##

[PcdsFixedAtBuild]
gSiPkgTokenSpaceGuid.PcdTraceHubEnable               |FALSE
gSiPkgTokenSpaceGuid.PcdSmmVariableEnable            |TRUE
gSiPkgTokenSpaceGuid.PcdAtaEnable                    |FALSE
gSiPkgTokenSpaceGuid.PcdHgEnable                     |FALSE
gSiPkgTokenSpaceGuid.PcdAcpiEnable                   |FALSE
gSiPkgTokenSpaceGuid.PcdSourceDebugEnable            |FALSE
gSiPkgTokenSpaceGuid.PcdPpmEnable                    |TRUE
gSiPkgTokenSpaceGuid.PcdTxtEnable                    |FALSE
gSiPkgTokenSpaceGuid.PcdIntegratedTouchEnable        |FALSE
gSiPkgTokenSpaceGuid.PcdAmtEnable                    |FALSE
gSiPkgTokenSpaceGuid.PcdPttEnable                    |FALSE
gSiPkgTokenSpaceGuid.PcdJhiEnable                    |FALSE
gSiPkgTokenSpaceGuid.PcdSoftwareGuardEnable          |FALSE
gSiPkgTokenSpaceGuid.PcdSmbiosEnable                 |TRUE
gSiPkgTokenSpaceGuid.PcdS3Enable                     |TRUE
gSiPkgTokenSpaceGuid.PcdOverclockEnable              |FALSE
gSiPkgTokenSpaceGuid.PcdCpuPowerOnConfigEnable       |FALSE
gSiPkgTokenSpaceGuid.PcdBdatEnable                   |TRUE
gSiPkgTokenSpaceGuid.PcdIgdEnable                    |TRUE
gSiPkgTokenSpaceGuid.PcdPegEnable                    |FALSE
gSiPkgTokenSpaceGuid.PcdSaDmiEnable                  |TRUE
gSiPkgTokenSpaceGuid.PcdIpuEnable                    |FALSE
gSiPkgTokenSpaceGuid.PcdGnaEnable                    |TRUE
gSiPkgTokenSpaceGuid.PcdVtdEnable                    |TRUE
gSiPkgTokenSpaceGuid.PcdBiosGuardEnable              |FALSE  #BiosGuardModule.bin
gSiPkgTokenSpaceGuid.PcdOptimizeCompilerEnable       |TRUE
gSiPkgTokenSpaceGuid.PcdPeiDisplayEnable             |TRUE
gSiPkgTokenSpaceGuid.PcdCflCpuEnable                 |FALSE
gSiPkgTokenSpaceGuid.PcdEhlCpuEnable                 |TRUE
gSiPkgTokenSpaceGuid.PcdEhlPchEnable                 |TRUE
gSiPkgTokenSpaceGuid.PcdTglCpuEnable                 |FALSE
gSiPkgTokenSpaceGuid.PcdTglPchEnable                 |TRUE
gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable         |FALSE
gSiPkgTokenSpaceGuid.PcdOcWdtEnable                  |FALSE
gSiPkgTokenSpaceGuid.PcdBootGuardEnable              |TRUE
gSiPkgTokenSpaceGuid.PcdCflSimicsEnable              |FALSE
gSiPkgTokenSpaceGuid.PcdSerialIoUartEnable           |TRUE

gSiPkgTokenSpaceGuid.PcdITbtEnable                   |FALSE
gSiPkgTokenSpaceGuid.PcdThcEnable                    |FALSE
gSiPkgTokenSpaceGuid.Pcd2lmEnable                    |FALSE
gSiPkgTokenSpaceGuid.PcdFspModeSelection             |1
gSiPkgTokenSpaceGuid.PcdPpamEnable                   |TRUE
gSiPkgTokenSpaceGuid.PcdVmdEnable                    |FALSE
gSiPkgTokenSpaceGuid.PcdPsmiEnable                   |TRUE
gSiPkgTokenSpaceGuid.PcdCpuPcieEnable                |FALSE

[PcdsFixedAtBuild.common]
gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress       |0xC0000000
gSiPkgTokenSpaceGuid.PcdSiPciExpressBaseAddress         |gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress
gSiPkgTokenSpaceGuid.PcdTemporaryPciExpressRegionLength |0x10000000

[PcdsDynamicDefault.common]
gSiPkgTokenSpaceGuid.PcdPciExpressRegionLength          |0x10000000
## Specifies the AP wait loop state during POST phase.
#  The value is defined as below.
#  1: Place AP in the Hlt-Loop state.
#  2: Place AP in the Mwait-Loop state.
#  3: Place AP in the Run-Loop state.
# @Prompt The AP wait loop state.
gUefiCpuPkgTokenSpaceGuid.PcdCpuApLoopMode|2
## Specifies the AP target C-state for Mwait during POST phase.
#  The default value 0 means C1 state.
#  The value is defined as below.<BR><BR>
# @Prompt The specified AP target C-state for Mwait.
gUefiCpuPkgTokenSpaceGuid.PcdCpuApTargetCstate|0

[Defines]
  PLATFORM_NAME = ClientOneSiliconPkg
  PLATFORM_GUID = CCD38CA7-61D3-4185-9CDA-A9FDF209CB31
  PLATFORM_VERSION = 0.4
  DSC_SPECIFICATION = 0x00010005
  OUTPUT_DIRECTORY = Build/ClientOneSiliconPkg
  SUPPORTED_ARCHITECTURES = IA32|X64
  BUILD_TARGETS = DEBUG|RELEASE
  SKUID_IDENTIFIER = DEFAULT

  DEFINE   PLATFORM_SI_PACKAGE        = ClientOneSiliconPkg
  DEFINE   C1S_PRODUCT_PATH           = ClientOneSiliconPkg/Product/ElkhartLake
  #
  # Definition for Build Flag
  #
  !include $(C1S_PRODUCT_PATH)/SiPkgBuildOption.dsc

[PcdsDynamicExDefault]
gSiPkgTokenSpaceGuid.PcdSiPciExpressBaseAddress|gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress

[LibraryClasses.common]
  #
  # Entry point
  #
  PeiCoreEntryPoint|MdePkg/Library/PeiCoreEntryPoint/PeiCoreEntryPoint.inf
  PeimEntryPoint|MdePkg/Library/PeimEntryPoint/PeimEntryPoint.inf
  DxeCoreEntryPoint|MdePkg/Library/DxeCoreEntryPoint/DxeCoreEntryPoint.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  PeCoffExtraActionLib|MdePkg/Library/BasePeCoffExtraActionLibNull/BasePeCoffExtraActionLibNull.inf

  #
  # Basic
  #
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLibRepStr/BaseMemoryLibRepStr.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  CpuLib|MdePkg/Library/BaseCpuLib/BaseCpuLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  PciSegmentLib|$(PLATFORM_SI_PACKAGE)/Library/BasePciSegmentMultiSegLibPci/BasePciSegmentMultiSegLibPci.inf
  PciLib|MdePkg/Library/BasePciLibPciExpress/BasePciLibPciExpress.inf
  PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
  PciExpressLib|$(PLATFORM_SI_PACKAGE)/Library/BasePciExpressMultiSegLib/BasePciExpressMultiSegLib.inf
  CacheMaintenanceLib|MdePkg/Library/BaseCacheMaintenanceLib/BaseCacheMaintenanceLib.inf
  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf
  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
  #
  # UEFI & PI
  #
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  UefiRuntimeLib|MdePkg/Library/UefiRuntimeLib/UefiRuntimeLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  PeiServicesTablePointerLib|MdePkg/Library/PeiServicesTablePointerLibIdt/PeiServicesTablePointerLibIdt.inf
  PeiServicesLib|MdePkg/Library/PeiServicesLib/PeiServicesLib.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
  DxeServicesTableLib|MdePkg/Library/DxeServicesTableLib/DxeServicesTableLib.inf

  S3BootScriptLib|MdePkg/Library/BaseS3BootScriptLibNull/BaseS3BootScriptLibNull.inf
  S3IoLib|MdePkg/Library/BaseS3IoLib/BaseS3IoLib.inf
  S3PciLib|MdePkg/Library/BaseS3PciLib/BaseS3PciLib.inf

  UefiUsbLib|MdePkg/Library/UefiUsbLib/UefiUsbLib.inf
  UefiScsiLib|MdePkg/Library/UefiScsiLib/UefiScsiLib.inf
  SynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf

  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf

  #
  # Misc
  #
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  PerformanceLib|MdePkg/Library/BasePerformanceLibNull/BasePerformanceLibNull.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  TimerLib|MdePkg/Library/BaseTimerLibNullTemplate/BaseTimerLibNullTemplate.inf
!if gSiPkgTokenSpaceGuid.PcdSpiPostCode == TRUE
  PostCodeLib|ClientSiliconPkg/Library/BasePostCodeSpiLib/BasePostCodeLibSpi.inf
!else
  PostCodeLib|MdePkg/Library/BasePostCodeLibDebug/BasePostCodeLibDebug.inf
!endif
  ReportStatusCodeLib|MdePkg/Library/BaseReportStatusCodeLibNull/BaseReportStatusCodeLibNull.inf
  MtrrLib|UefiCpuPkg/Library/MtrrLib/MtrrLib.inf
  RngLib|MdePkg/Library/BaseRngLib/BaseRngLib.inf

#####################################################################################################

#
# Silicon Init Common Library
#
!include $(C1S_PRODUCT_PATH)/SiPkgCommonLib.dsc
ConfigBlockLib|ClientSiliconPkg/Library/BaseConfigBlockLib/BaseConfigBlockLib.inf

[LibraryClasses.IA32]
#
# PEI phase common
#
  PcdLib|MdePkg/Library/PeiPcdLib/PeiPcdLib.inf
  HobLib|MdePkg/Library/PeiHobLib/PeiHobLib.inf
  MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
  ExtractGuidedSectionLib|MdePkg/Library/PeiExtractGuidedSectionLib/PeiExtractGuidedSectionLib.inf

#####################################################################################################################################

#
# Silicon Init Pei Library
#
!include $(C1S_PRODUCT_PATH)/SiPkgPeiLib.dsc

[LibraryClasses.IA32.SEC]

[LibraryClasses.X64]
 #
 # DXE phase common
 #
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  ExtractGuidedSectionLib|MdePkg/Library/DxeExtractGuidedSectionLib/DxeExtractGuidedSectionLib.inf

#
# Hsti
#
  HstiLib|MdePkg/Library/DxeHstiLib/DxeHstiLib.inf

###################################################################################################
#
# Silicon Init Dxe Library
#
!include $(C1S_PRODUCT_PATH)/SiPkgDxeLib.dsc

[LibraryClasses.X64.PEIM]

[LibraryClasses.X64.DXE_CORE]
  HobLib|MdePkg/Library/DxeCoreHobLib/DxeCoreHobLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf

[LibraryClasses.X64.DXE_SMM_DRIVER]
  SmmServicesTableLib|MdePkg/Library/SmmServicesTableLib/SmmServicesTableLib.inf
  MemoryAllocationLib|MdePkg/Library/SmmMemoryAllocationLib/SmmMemoryAllocationLib.inf
  SmmIoLib|MdePkg/Library/SmmIoLib/SmmIoLib.inf
  SmmMemLib|MdePkg/Library/SmmMemLib/SmmMemLib.inf

[LibraryClasses.X64.SMM_CORE]

[LibraryClasses.X64.UEFI_DRIVER]
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf

[LibraryClasses.X64.UEFI_APPLICATION]
  PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf

[Components.IA32]
!include $(C1S_PRODUCT_PATH)/SiPkgPei.dsc

[Components.X64]
!include $(C1S_PRODUCT_PATH)/SiPkgDxe.dsc
#
# AcpiTables
#
$(PLATFORM_SI_PACKAGE)/Pch/AcpiTables/Dsdt/PchAcpiTablesSelfTest.inf