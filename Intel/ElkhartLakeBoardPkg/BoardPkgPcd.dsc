## @file
#  Platform description.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2017 - 2019 Intel Corporation.
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

################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################
[PcdsFeatureFlag.common]
  gEfiMdeModulePkgTokenSpaceGuid.PcdInstallAcpiSdtProtocol|TRUE
  gEfiMdeModulePkgTokenSpaceGuid.PcdPeiCoreImageLoaderSearchTeSectionFirst|FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseMemory|FALSE
!if $(TARGET) == RELEASE
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseSerial|FALSE
!else
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseSerial|TRUE
!endif

  gUefiCpuPkgTokenSpaceGuid.PcdCpuSmmEnableBspElection|FALSE
  gUefiCpuPkgTokenSpaceGuid.PcdCpuSmmProfileEnable|FALSE

!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
  gEfiMdeModulePkgTokenSpaceGuid.PcdSupportUpdateCapsuleReset|TRUE
!else
  gEfiMdeModulePkgTokenSpaceGuid.PcdSupportUpdateCapsuleReset|FALSE
!endif

  gEfiMdeModulePkgTokenSpaceGuid.PcdPciDegradeResourceForOptionRom|FALSE


[PcdsFeatureFlag.X64]
  #
  # Enabling PcdHiiOsRuntimeSupport casuses S4 failure due to
  # insuficient Runtime memory allocation
  #
  gEfiMdeModulePkgTokenSpaceGuid.PcdHiiOsRuntimeSupport|FALSE

[PcdsFixedAtBuild]
  # Change PcdBootManagerMenuFile to point to UiApp
  gEfiMdeModulePkgTokenSpaceGuid.PcdBootManagerMenuFile|{ 0x8b, 0x7d, 0x9a, 0xd8, 0x16, 0xd0, 0x26, 0x4d, 0x93, 0xe3, 0xea, 0xb6, 0xb4, 0xd3, 0xb0, 0xa2 }

  #
  # SMBIOS settings
  #

  # Disabling 64 bit Smbios Entrypoint Structure and populated tables
  # Bit0 is to enable 32 bit and Bit1 is to enable 64 bit Smbios tables
  !if gSiPkgTokenSpaceGuid.PcdSmbiosEnable == TRUE
    gEfiMdeModulePkgTokenSpaceGuid.PcdSmbiosEntryPointProvideMethod|0x01
  !endif

[PcdsFixedAtBuild.common]
!if gPlatformModuleTokenSpaceGuid.PcdPostCodeStatusCodeEnable == TRUE
  gClientCommonModuleTokenSpaceGuid.PcdStatusCodeUsePostCode|TRUE
!else
  gClientCommonModuleTokenSpaceGuid.PcdStatusCodeUsePostCode|FALSE
!endif

  gMinPlatformPkgTokenSpaceGuid.PcdFspWrapperBootMode|TRUE
!if gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable == TRUE
  gEfiMdePkgTokenSpaceGuid.PcdPerformanceLibraryPropertyMask|0x1
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxPeiPerformanceLogEntries|140
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdSmiHandlerProfileEnable == TRUE
  gEfiMdeModulePkgTokenSpaceGuid.PcdSmiHandlerProfilePropertyMask|0x1
!endif

  gMinPlatformPkgTokenSpaceGuid.PcdMaxCpuThreadCount|2
  gMinPlatformPkgTokenSpaceGuid.PcdMaxCpuCoreCount|8
  gMinPlatformPkgTokenSpaceGuid.PcdMaxCpuSocketCount|1

  gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress         | 0xC0000000
!if (gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == FALSE) || (gSiPkgTokenSpaceGuid.PcdFspModeSelection == 1)
  #
  # In EDK2 mode or FSP API mode, the PciExpressBaseAddress is not necessary DynamicEx
  #
  gSiPkgTokenSpaceGuid.PcdSiPciExpressBaseAddress|gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress
!endif

#@Todo: Need to recalculate the proper size for minplatform
  !if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
    gIntelFsp2PkgTokenSpaceGuid.PcdTemporaryRamBase|0xFEF00000
    gIntelFsp2PkgTokenSpaceGuid.PcdTemporaryRamSize|0x00080000
    !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
      gUefiCpuPkgTokenSpaceGuid.PcdPeiTemporaryRamStackSize|0x10000
      !if gSiPkgTokenSpaceGuid.PcdFspModeSelection == 1
        gIntelFsp2PkgTokenSpaceGuid.PcdFspTemporaryRamSize|0x00030000
      !endif
    !else
      !if gSiPkgTokenSpaceGuid.PcdFspModeSelection == 1
        gIntelFsp2PkgTokenSpaceGuid.PcdFspTemporaryRamSize|0x00040000
      !endif
    !endif
  !else
    #Increase Temp Ram Size for EDK build to avoid HobLib Assert
    gSiPkgTokenSpaceGuid.PcdTemporaryRamBase|0xFEF00000
    gSiPkgTokenSpaceGuid.PcdTemporaryRamSize|0x00080000
    gEfiMdeModulePkgTokenSpaceGuid.PcdPeiCoreMaxPeiStackSize|0x40000
  !endif

  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxVariableSize|0x10000
  gEfiMdeModulePkgTokenSpaceGuid.PcdHwErrStorageSize|0x00000800
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxHardwareErrorVariableSize|0x400
  gEfiMdeModulePkgTokenSpaceGuid.PcdAriSupport|FALSE

  ## Specifies the number of variable MTRRs reserved for OS use. The default number of
  #  MTRRs reserved for OS use is 0.
  # @Prompt Number of reserved variable MTRRs.
  gUefiCpuPkgTokenSpaceGuid.PcdCpuNumberOfReservedVariableMtrrs|0x0
  gUefiCpuPkgTokenSpaceGuid.PcdCpuSmmApSyncTimeout|10000
!if $(TARGET) == RELEASE
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x0
  gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|0x3
!else
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x2F
  gEfiMdeModulePkgTokenSpaceGuid.PcdSerialUseHardwareFlowControl|FALSE
  gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|0x07
!endif
  gEfiMdeModulePkgTokenSpaceGuid.PcdLoadModuleAtFixAddressEnable|$(TOP_MEMORY_ADDRESS)
  gEfiMdeModulePkgTokenSpaceGuid.PcdBrowserSubtitleTextColor|0x0
  gEfiMdeModulePkgTokenSpaceGuid.PcdBrowserFieldTextColor|0x01
  gUefiCpuPkgTokenSpaceGuid.PcdCpuSmmStackSize|0x20000

  gEfiMdeModulePkgTokenSpaceGuid.PcdReclaimVariableSpaceAtEndOfDxe|TRUE

#
# 16MB TSEG in Debug build only.
#
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  gSiPkgTokenSpaceGuid.PcdTsegSize|0x1000000
!else
!if $(TARGET) == DEBUG
  gSiPkgTokenSpaceGuid.PcdTsegSize|0x1000000
!else
  gSiPkgTokenSpaceGuid.PcdTsegSize|0x800000
!endif
!endif

  gPcAtChipsetPkgTokenSpaceGuid.PcdAcpiIoPciBusNumber|0x0
  gPcAtChipsetPkgTokenSpaceGuid.PcdAcpiIoPciDeviceNumber|0x1F
  gPcAtChipsetPkgTokenSpaceGuid.PcdAcpiIoPciFunctionNumber|0x2
  gPcAtChipsetPkgTokenSpaceGuid.PcdAcpiIoPciEnableRegisterOffset|0x44
  gPcAtChipsetPkgTokenSpaceGuid.PcdAcpiIoBarEnableMask|0x80
  gPcAtChipsetPkgTokenSpaceGuid.PcdAcpiIoPciBarRegisterOffset|0x00
  gPcAtChipsetPkgTokenSpaceGuid.PcdAcpiIoPortBaseAddress|0x1800
  gPcAtChipsetPkgTokenSpaceGuid.PcdAcpiPm1TmrOffset|0x08
  gPcAtChipsetPkgTokenSpaceGuid.PcdAcpiIoPortBaseAddressMask|0xFFFC

  gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiAcpiReclaimMemorySize|0x79
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiAcpiNvsMemorySize|0x62
    gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiReservedMemorySize|0x224E
    gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiRtDataMemorySize|0x76
    !if $(TARGET) == RELEASE
      gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiRtCodeMemorySize|0x8E
    !else
      gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiRtCodeMemorySize|0xD0
    !endif
  !else
    gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiAcpiNvsMemorySize|0x4C
    gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiReservedMemorySize|0x226A
    gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiRtDataMemorySize|0x21
    !if $(TARGET) == RELEASE
      gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiRtCodeMemorySize|0x5D
    !else
      gMinPlatformPkgTokenSpaceGuid.PcdPlatformEfiRtCodeMemorySize|0x9C
    !endif
  !endif

  !if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
  gIntelFsp2WrapperTokenSpaceGuid.PcdFsptBaseAddress|0xFFEA0000
  gIntelFsp2WrapperTokenSpaceGuid.PcdFspmBaseAddress|0xFFD00000
  !endif

  ## Specifies timeout value in microseconds for the BSP to detect all APs for the first time.
  # @Prompt Timeout for the BSP to detect all APs for the first time.
  gUefiCpuPkgTokenSpaceGuid.PcdCpuApInitTimeOutInMicroSeconds|50000
  #
  # The PCDs are used to control the Windows SMM Security Mitigations Table - Protection Flags
  #
  # BIT0: If set, expresses that for all synchronous SMM entries,SMM will validate that input and output buffers lie entirely within the expected fixed memory regions.
  # BIT1: If set, expresses that for all synchronous SMM entries, SMM will validate that input and output pointers embedded within the fixed communication buffer only refer to address ranges \
  #       that lie entirely within the expected fixed memory regions.
  # BIT2: Firmware setting this bit is an indication that it will not allow reconfiguration of system resources via non-architectural mechanisms.
  # BIT3-31: Reserved
  #
  gMinPlatformPkgTokenSpaceGuid.PcdWsmtProtectionFlags|0x07

!if gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable == TRUE
  ## Pcd for OptionRom.
  #  Image verification policy settings:
  #  ALWAYS_EXECUTE                         0x00000000
  #  NEVER_EXECUTE                          0x00000001
  #  ALLOW_EXECUTE_ON_SECURITY_VIOLATION    0x00000002
  #  DEFER_EXECUTE_ON_SECURITY_VIOLATION    0x00000003
  #  DENY_EXECUTE_ON_SECURITY_VIOLATION     0x00000004
  #  QUERY_USER_ON_SECURITY_VIOLATION       0x00000005
  gEfiSecurityPkgTokenSpaceGuid.PcdOptionRomImageVerificationPolicy|0x00000004
  gEfiSecurityPkgTokenSpaceGuid.PcdRsa2048Sha256PublicKeyBuffer|{0x8A, 0xF3, 0x87, 0x6B, 0x0F, 0xD4, 0xA3, 0x90, 0x15, 0xD7, 0x40, 0xC5, 0x3A, 0x94, 0x9B, 0xF4, 0xE0, 0x58, 0x53, 0x58, 0x87, 0x89, 0x67, 0x84, 0x60, 0xAF, 0x8E, 0xB4, 0x16, 0x1F, 0x52, 0x51}
!endif

!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
  ## Indicates if to shadow PEIM on S3 boot path after memory is ready.<BR><BR>
  #   TRUE  - Shadow PEIM on S3 boot path after memory is ready.<BR>
  #   FALSE - Not shadow PEIM on S3 boot path after memory is ready.<BR>
  # @Prompt Shadow Peim On S3 Boot.
  gEfiMdeModulePkgTokenSpaceGuid.PcdShadowPeimOnS3Boot|TRUE

  #
  # For RS5 (1 core, 2 thread), increase page number to avoid S3 exit fail
  #
  gEfiMdeModulePkgTokenSpaceGuid.PcdS3BootScriptRuntimeTableReservePageNumber|0x4
!endif

!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdPeiCoreMaxFvSupported   | 26
  gEfiMdeModulePkgTokenSpaceGuid.PcdPeiCoreMaxPpiSupported  | 160
!endif

!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == FALSE
  gPlatformModuleTokenSpaceGuid.PcdBiosInfoEntryCount|24
!endif

!if gSiPkgTokenSpaceGuid.PcdPpamEnable == TRUE
  gUefiCpuPkgTokenSpaceGuid.PcdCpuMsegSize|0x80000
!endif


gPlatformModuleTokenSpaceGuid.PcdGmAdrAddress|(gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress - 0x10000000) # 0xB0000000
gPlatformModuleTokenSpaceGuid.PcdGttMmAddress|(gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress - 0x11000000) # 0xAF000000

#
# PlatformTemporaryMmioAssignmentBegin
#
# When gEfiPeiBootInRecoveryModePpiGuid is installed, below MMIO resource would be
# temporarily assigned to NVME/AHCI host controller after FspSiInitDone and be released at EndOfPei.
# Please take care of platform resource assignment to avoid conflicts.
#
gPlatformModuleTokenSpaceGuid.PcdNvmePciHostControllerMmioBase |(gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress - 0x20000000)              # 0xA0000000
gPlatformModuleTokenSpaceGuid.PcdNvmePciHostControllerMmioLimit|(gPlatformModuleTokenSpaceGuid.PcdNvmePciHostControllerMmioBase + 0x1000000) # 0xA1000000
gPlatformModuleTokenSpaceGuid.PcdSataPciHostControllerMmioBase |(gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress - 0x30000000)             # 0x90000000
#
# PlatformTemporaryMmioAssignmentEnd
#

#
# PlatformTemporaryPciBusAssignmentBegin
#
# When gEfiPeiBootInRecoveryModePpiGuid is installed, below PciBus would be
# temporarily assigned to NVME host controller after FspSiInitDone and be released at EndOfPei.
# Please take care of platform resource assignment to avoid conflicts.
gPlatformModuleTokenSpaceGuid.PcdNvmePciHostControllerPciBusMin|0x10
gPlatformModuleTokenSpaceGuid.PcdNvmePciHostControllerPciBusMax|0x17
#
# PlatformTemporaryPciBusAssignmentEnd
#
!if gBoardModuleTokenSpaceGuid.PcdUfsEnable == TRUE
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  gEfiMdeModulePkgTokenSpaceGuid.PcdUfsPciHostControllerMmioBase|0xD0000000
  gBoardModuleTokenSpaceGuid.PcdUfsPciHostControllerBus|0
  gBoardModuleTokenSpaceGuid.PcdUfsPciHostControllerDevice|18
!endif
!endif

!if $(TARGET) == DEBUG
    !if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
      !if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
        gEfiBpCommonPkgTokenSpaceGuid.PcdStatusCodeUseTraceHub|TRUE
        gEfiBpCommonPkgTokenSpaceGuid.PcdTraceHubDebugLibMaster|0x48
        gEfiBpCommonPkgTokenSpaceGuid.PcdTraceHubDebugLibChannel|0xE
        !if gSiPkgTokenSpaceGuid.PcdSerialIoUartEnable == TRUE
          gPlatformModuleTokenSpaceGuid.PcdStatusCodeUseSerialIoUart|TRUE
          gClientCommonModuleTokenSpaceGuid.PcdStatusCodeFlags|0xB2
        !else
          gPlatformModuleTokenSpaceGuid.PcdStatusCodeUseSerialIoUart|FALSE
          gClientCommonModuleTokenSpaceGuid.PcdStatusCodeFlags|0xA2
        !endif
      !else
        gEfiBpCommonPkgTokenSpaceGuid.PcdStatusCodeUseTraceHub|FALSE
        !if gSiPkgTokenSpaceGuid.PcdSerialIoUartEnable == TRUE
          gPlatformModuleTokenSpaceGuid.PcdStatusCodeUseSerialIoUart|TRUE
          gClientCommonModuleTokenSpaceGuid.PcdStatusCodeFlags|0x92
        !else
          gPlatformModuleTokenSpaceGuid.PcdStatusCodeUseSerialIoUart|FALSE
          gClientCommonModuleTokenSpaceGuid.PcdStatusCodeFlags|0x82
        !endif
      !endif
    !else
      gEfiBpCommonPkgTokenSpaceGuid.PcdStatusCodeUseTraceHub|FALSE
      !if gSiPkgTokenSpaceGuid.PcdSerialIoUartEnable == TRUE
        gPlatformModuleTokenSpaceGuid.PcdStatusCodeUseSerialIoUart|TRUE
        gClientCommonModuleTokenSpaceGuid.PcdStatusCodeFlags|0x92
      !else
        gPlatformModuleTokenSpaceGuid.PcdStatusCodeUseSerialIoUart|FALSE
        gClientCommonModuleTokenSpaceGuid.PcdStatusCodeFlags|0x82
      !endif
    !endif
!else
#
# RELEASE Build
#
  !if gSiPkgTokenSpaceGuid.PcdTraceHubEnable == TRUE
    gClientCommonModuleTokenSpaceGuid.PcdStatusCodeFlags|0x20
    gEfiBpCommonPkgTokenSpaceGuid.PcdStatusCodeUseTraceHub|TRUE
    gEfiBpCommonPkgTokenSpaceGuid.PcdTraceHubDebugLibMaster|0x48
    gEfiBpCommonPkgTokenSpaceGuid.PcdTraceHubDebugLibChannel|0xE
  !endif
!endif

!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
#
# RPPO-LKF-0033: RoyalParkOverrideBegin
#
!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  gBoardModuleTokenSpaceGuid.PcdUpdateCapsuleOnColdReset|TRUE
!else
  gBoardModuleTokenSpaceGuid.PcdUpdateCapsuleOnColdReset|FALSE
!endif
#
# RPPO-LKF-0033: RoyalParkOverrideEnd
#
  gBoardModuleTokenSpaceGuid.PcdUfsTopSwapSize|0x400000      # 4MB
!endif

[PcdsFixedAtBuild.IA32]
  gEfiMdeModulePkgTokenSpaceGuid.PcdVpdBaseAddress|0x0
  gMinPlatformPkgTokenSpaceGuid.PcdPeiPhaseStackTop|0xA0000
  !if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
    gIntelFsp2PkgTokenSpaceGuid.PcdGlobalDataPointerAddress|0xFED00148
    !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
      gIntelFsp2WrapperTokenSpaceGuid.PcdPeiMinMemSize|0x5000000
    !else
      gIntelFsp2WrapperTokenSpaceGuid.PcdPeiMinMemSize|0x3800000
    !endif
  !endif

[PcdsFixedAtBuild.X64]

  # Default platform supported RFC 4646 languages: (American) English
  gEfiMdePkgTokenSpaceGuid.PcdUefiVariableDefaultPlatformLangCodes|"en-US"

!if gSiPkgTokenSpaceGuid.PcdS3Enable == TRUE
# @todo the size needs to be optimized.
!if $(TARGET) == DEBUG
  gPlatformModuleTokenSpaceGuid.PcdS3AcpiReservedMemorySize|0x1B00000
!else
  gPlatformModuleTokenSpaceGuid.PcdS3AcpiReservedMemorySize|0x1B00000
!endif
!endif

!if gPlatformModuleTokenSpaceGuid.PcdNetworkEnable == TRUE
  gEfiNetworkPkgTokenSpaceGuid.PcdAllowHttpConnections|TRUE
!endif

[PcdsPatchableInModule.common]
  gEfiMdeModulePkgTokenSpaceGuid.PcdSmbiosVersion|0x0208

  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000046

!if $(TARGET) == DEBUG
!if gSiPkgTokenSpaceGuid.PcdSerialIoUartEnable == TRUE
  gSiPkgTokenSpaceGuid.PcdSerialIoUartDebugEnable|1
!endif
!endif

  gPlatformModuleTokenSpaceGuid.PcdSystemFirmwareFmpSupportedMode|0xFF

[PcdsDynamicHii.common.DEFAULT]
  gClientCommonModuleTokenSpaceGuid.PcdPlatformMemoryCheck|L"MemoryCheck"|gClientCommonModuleTokenSpaceGuid|0x0|0
  gClientCommonModuleTokenSpaceGuid.PcdComPortAttributes0IsEnabled|L"ComAttributes"|gSetupVariableGuid|0x16|0
  gEfiMdePkgTokenSpaceGuid.PcdDefaultTerminalType|L"ComAttributes"|gSetupVariableGuid|0x13|0
  gEfiSecurityPkgTokenSpaceGuid.PcdTpm2AcpiTableRev|L"TCG2_VERSION"|gTcg2ConfigFormSetGuid|0x8|4|NV,BS
  gClientCommonModuleTokenSpaceGuid.PcdFastBootEnable|L"Setup"|gSetupVariableGuid|0x0|0

[PcdsDynamicHii.X64.DEFAULT]
  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut|L"Timeout"|gEfiGlobalVariableGuid|0x0|5 # Variable: L"Timeout"
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|L"ConOutConfig"|gClientCommonModuleTokenSpaceGuid|0x0|100
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|L"ConOutConfig"|gClientCommonModuleTokenSpaceGuid|0x4|31
  gEfiMdePkgTokenSpaceGuid.PcdHardwareErrorRecordLevel|L"HwErrRecSupport"|gEfiGlobalVariableGuid|0x0|1 # Variable: L"HwErrRecSupport"
  gSiPkgTokenSpaceGuid.PcdCpuSmmMsrSaveStateEnable|L"CpuSmm"|gCpuSmmGuid|0x0|0
  gSiPkgTokenSpaceGuid.PcdCpuSmmUseDelayIndication|L"CpuSmm"|gCpuSmmGuid|0x2|1
  gSiPkgTokenSpaceGuid.PcdCpuSmmUseBlockIndication|L"CpuSmm"|gCpuSmmGuid|0x3|1
  gSiPkgTokenSpaceGuid.PcdCpuSmmUseSmmEnableIndication|L"CpuSmm"|gCpuSmmGuid|0x4|1

!if gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable == TRUE
  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut|L"Timeout"|gEfiGlobalVariableGuid|0x0|1 # Variable: L"Timeout"
!endif

[PcdsDynamicDefault]
!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
  gIntelFsp2WrapperTokenSpaceGuid.PcdFspsBaseAddress|0xFFC00000
  gIntelFsp2WrapperTokenSpaceGuid.PcdFspmUpdDataAddress|0x00000000
  gIntelFsp2WrapperTokenSpaceGuid.PcdFspsUpdDataAddress|0x00000000
!endif
  gEfiSecurityPkgTokenSpaceGuid.PcdCRBIdleByPass|0xFF
  gEfiMdeModulePkgTokenSpaceGuid.PcdSrIovSupport|FALSE

[PcdsDynamicDefault.common.DEFAULT]
  gMinPlatformPkgTokenSpaceGuid.PcdPciReservedMemBase |0x80000000
  gMinPlatformPkgTokenSpaceGuid.PcdPciReservedMemLimit|0xC0000000
  gMinPlatformPkgTokenSpaceGuid.PcdPciReservedMemAbove4GBBase  |0xFFFFFFFFFFFFFFFF
  gMinPlatformPkgTokenSpaceGuid.PcdPciReservedMemAbove4GBLimit |0x0000000000000000
  gMinPlatformPkgTokenSpaceGuid.PcdPciSegmentCount|0x1

!if (gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == FALSE) || (gSiPkgTokenSpaceGuid.PcdFspModeSelection == 1)
  ## Specifies max supported number of Logical Processors.
  # @Prompt Configure max supported number of Logical Processorss
  gUefiCpuPkgTokenSpaceGuid.PcdCpuMaxLogicalProcessorNumber|16

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

  gSiPkgTokenSpaceGuid.PcdPciExpressRegionLength|0x10000000
!endif
  gUefiCpuPkgTokenSpaceGuid.PcdCpuSmmStaticPageTable|FALSE
  gPlatformModuleTokenSpaceGuid.PcdTopSwapEnableSwSmi |0xFF
  gPlatformModuleTokenSpaceGuid.PcdTopSwapDisableSwSmi|0xFF

  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|0x0
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|0x0
  gEfiMdeModulePkgTokenSpaceGuid.PcdAtaSmartEnable|TRUE
  gEfiMdeModulePkgTokenSpaceGuid.PcdConInConnectOnDemand|FALSE
  #
  #  Set video to native resolution as Windows 8 WHCK requirement.
  #
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|0x0
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|0x0

  gEfiMdeModulePkgTokenSpaceGuid.PcdS3BootScriptTablePrivateDataPtr|0x0

!if gBoardModuleTokenSpaceGuid.PcdS4Enable == FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdResetOnMemoryTypeInformationChange|FALSE
!else
  gEfiMdeModulePkgTokenSpaceGuid.PcdResetOnMemoryTypeInformationChange|TRUE
!endif
!if gBoardModuleTokenSpaceGuid.PcdAcpiDebugFeatureEnable == TRUE
  gEfiBpCommonPkgTokenSpaceGuid.PcdAcpiDebugEnable|TRUE
!else
  gEfiBpCommonPkgTokenSpaceGuid.PcdAcpiDebugEnable|FALSE
!endif

  ## This is recover file name in PEI phase.
  #  The file must be in the root directory.
  #  The file name must be the 8.3 format.
  #  The PCD data must be in UNICODE format.
  # @Prompt Recover file name in PEI phase
  gEfiMdeModulePkgTokenSpaceGuid.PcdRecoveryFileName|L"Capsule.cap"|VOID*|0x20

  ## The mask is used to control VTd behavior.<BR><BR>
  #  BIT0: Enable IOMMU during boot (If DMAR table is installed in DXE. If VTD_INFO_PPI is installed in PEI.)
  #  BIT1: Enable IOMMU when transfer control to OS (ExitBootService in normal boot. EndOfPEI in S3)
  # @Prompt The policy for VTd driver behavior.
  gIntelSiliconPkgTokenSpaceGuid.PcdVTdPolicyPropertyMask|0x00000000

!if gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable == TRUE
  gEfiSecurityPkgTokenSpaceGuid.PcdTpmInstanceGuid|{0x5a, 0xf2, 0x6b, 0x28, 0xc3, 0xc2, 0x8c, 0x40, 0xb3, 0xb4, 0x25, 0xe6, 0x75, 0x8b, 0x73, 0x17}

  gEfiSecurityPkgTokenSpaceGuid.PcdTcg2HashAlgorithmBitmap|0xFFFFFFFF
  gEfiSecurityPkgTokenSpaceGuid.PcdTpm2HashMask|0x0000001F

  gClientCommonModuleTokenSpaceGuid.PcdTpm2HierarchyChangeAuthPlatform|1
  gClientCommonModuleTokenSpaceGuid.PcdTpm2HierarchyControlPlatform|1
  gClientCommonModuleTokenSpaceGuid.PcdTpm2HierarchyControlEndorsement|1
  gClientCommonModuleTokenSpaceGuid.PcdTpm2HierarchyControlOwner|1
  gClientCommonModuleTokenSpaceGuid.PcdTpm2ChangeEps|0
  gClientCommonModuleTokenSpaceGuid.PcdTpm2ChangePps|0
  gClientCommonModuleTokenSpaceGuid.PcdTpm2Clear|0

  gEfiSecurityPkgTokenSpaceGuid.PcdTpm2InitializationPolicy|1
  gEfiSecurityPkgTokenSpaceGuid.PcdTpm2SelfTestPolicy|0
  gEfiSecurityPkgTokenSpaceGuid.PcdTpm2ScrtmPolicy|1
!endif
  gEfiSecurityPkgTokenSpaceGuid.PcdTpm2CurrentIrqNum|0x00

!if gPlatformModuleTokenSpaceGuid.PcdTpmEnable == TRUE
  gEfiSecurityPkgTokenSpaceGuid.PcdTpmInitializationPolicy|1
  gEfiSecurityPkgTokenSpaceGuid.PcdTpmScrtmPolicy|1
!endif

  gClientCommonModuleTokenSpaceGuid.PcdPostIbbVerificationEnable|TRUE

  ## Default OEM Table ID for ACPI table creation, it is "EDK2    ".
  #  According to ACPI specification, this field is particularly useful when
  #  defining a definition block to distinguish definition block functions.
  #  The OEM assigns each dissimilar table a new OEM Table ID.
  #  This PCD is ignored for definition block.
  # @Prompt Default OEM Table ID for ACPI table creation.
  # default set to "EHL     ", will be patched by AcpiPlatform per CPU family
  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultOemTableId|0x20202020204C4845
  gSiPkgTokenSpaceGuid.PcdAcpiDefaultOemTableId|0x20202020204C4845

  gEfiSecurityPkgTokenSpaceGuid.PcdFirmwareDebuggerInitialized|FALSE

[PcdsDynamicExDefault.common.DEFAULT]
  gEfiMdeModulePkgTokenSpaceGuid.PcdS3BootScriptTablePrivateDataPtr|0x0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFastPS2Detection|FALSE
  gMinPlatformPkgTokenSpaceGuid.PcdPciExpressRegionLength|0x10000000

!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
  gEfiMdeModulePkgTokenSpaceGuid.PcdSystemFmpCapsuleImageTypeIdGuid|{GUID(gFmpDevicePlatformMonolithicGuid), GUID(gFmpDevicePlatformBiosGuid), GUID(gFmpDevicePlatformMeGuid)}
!endif

!if gSiPkgTokenSpaceGuid.PcdFspModeSelection == 0
  #
  # Include FSP PCD settings.
  #
  !include $(PLATFORM_FSP_BIN_PACKAGE)/ElkhartLakeFspPcds.dsc
!endif

  #
  # Some of the PCD consumed by both FSP and bootloader should be defined
  # here for bootloader to consume.
  #

!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  gSiPkgTokenSpaceGuid.PcdEnableCseVariableStorage|TRUE
  gSiPkgTokenSpaceGuid.PcdEnableFvbVariableStorage|FALSE
!else
  gSiPkgTokenSpaceGuid.PcdEnableCseVariableStorage|FALSE
  gSiPkgTokenSpaceGuid.PcdEnableFvbVariableStorage|TRUE
!endif
  gSiPkgTokenSpaceGuid.PcdNvVariableEmulationMode|FALSE

  !include $(PLATFORM_BOARD_PACKAGE)/DefaultConfigStructures.dsc
!if gSiPkgTokenSpaceGuid.PcdFspWrapperEnable == TRUE
  gIntelFsp2WrapperTokenSpaceGuid.PcdFspsBaseAddress|0xFFC00000
  #
  # RPPO-CNL-0087: RoyalParkOverrideBegin
  #
  gPlatformModuleTokenSpaceGuid.PcdFspmBaseAddress|0xFFD00000
  #
  # RPPO-CNL-0087: RoyalParkOverrideEnd
  #
!endif

