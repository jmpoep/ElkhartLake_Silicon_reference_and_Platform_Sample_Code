## @file
#  Platform description.
#
# Copyright (c) 2017 - 2019, Intel Corporation. All rights reserved.<BR>
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
#
##


  #
  # Generic EDKII Driver
  #
  MdeModulePkg/Core/Dxe/DxeMain.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
  }
  MdeModulePkg/Universal/PCD/Dxe/Pcd.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  }

  MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/ReportStatusCodeRouterRuntimeDxe.inf
  MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/StatusCodeHandlerRuntimeDxe.inf

  UefiCpuPkg/CpuIo2Dxe/CpuIo2Dxe.inf
  MdeModulePkg/Universal/Metronome/Metronome.inf
  MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
  PcAtChipsetPkg/PcatRealTimeClockRuntimeDxe/PcatRealTimeClockRuntimeDxe.inf
  MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf

!if gMinPlatformPkgTokenSpaceGuid.PcdBootToShellOnly == FALSE
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteSmm.inf
    $(PLATFORM_SI_PACKAGE)/SampleCode/MdeModulePkg/Universal/Variable/RuntimeDxe/VariableSmmRuntimeDxe.inf {
      <LibraryClasses>
!if gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable == FALSE
        TpmMeasurementLib|MdeModulePkg/Library/TpmMeasurementLibNull/TpmMeasurementLibNull.inf
!endif
!if $(TARGET) == DEBUG
        DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
      <PcdsPatchableInModule>
        gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000147
!endif
    }
    $(PLATFORM_SI_PACKAGE)/SampleCode/MdeModulePkg/Universal/Variable/RuntimeDxe/VariableSmm.inf {
      <LibraryClasses>
        VarCheckLib|MdeModulePkg/Library/VarCheckLib/VarCheckLib.inf
        NULL|MdeModulePkg/Library/VarCheckUefiLib/VarCheckUefiLib.inf
        NULL|MdeModulePkg/Library/VarCheckHiiLib/VarCheckHiiLib.inf
        NULL|$(PLATFORM_FULL_PACKAGE)/Library/PlatformVarCheckLib/PlatformVarCheckLib.inf
!if gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable == TRUE
        PlatformSecureLib|$(PLATFORM_FULL_PACKAGE)/Library/PlatformSecureLibTest/PlatformSecureLibTest.inf
        AuthVariableLib|SecurityPkg/Library/AuthVariableLib/AuthVariableLib.inf
!else
        PlatformSecureLib|$(PLATFORM_FULL_PACKAGE)/Override/SecurityPkg/Library/PlatformSecureLibNull/PlatformSecureLibNull.inf
        AuthVariableLib|MdeModulePkg/Library/AuthVariableLibNull/AuthVariableLibNull.inf
!endif
    }
  !else
    MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteSmm.inf
    MdeModulePkg/Universal/Variable/RuntimeDxe/VariableSmmRuntimeDxe.inf
    MdeModulePkg/Universal/Variable/RuntimeDxe/VariableSmm.inf {
      <LibraryClasses>
        NULL|MdeModulePkg/Library/VarCheckUefiLib/VarCheckUefiLib.inf
        NULL|MdeModulePkg/Library/VarCheckHiiLib/VarCheckHiiLib.inf
        !if gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable == TRUE
          PlatformSecureLib|$(PLATFORM_FULL_PACKAGE)/Library/PlatformSecureLibTest/PlatformSecureLibTest.inf
          AuthVariableLib|SecurityPkg/Library/AuthVariableLib/AuthVariableLib.inf
        !else
          PlatformSecureLib|$(PLATFORM_FULL_PACKAGE)/Override/SecurityPkg/Library/PlatformSecureLibNull/PlatformSecureLibNull.inf
          AuthVariableLib|MdeModulePkg/Library/AuthVariableLibNull/AuthVariableLibNull.inf
        !endif
    }
  !endif
!else
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(PLATFORM_SI_PACKAGE)/SampleCode/MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf {
      <PcdsFixedAtBuild>
        gEfiMdeModulePkgTokenSpaceGuid.PcdEmuVariableNvModeEnable|TRUE
    }
  !else
    MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf {
      <LibraryClasses>
        !if gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable == TRUE
          PlatformSecureLib|$(PLATFORM_FULL_PACKAGE)/Library/PlatformSecureLibTest/PlatformSecureLibTest.inf
          AuthVariableLib|SecurityPkg/Library/AuthVariableLib/AuthVariableLib.inf
        !else
          PlatformSecureLib|$(PLATFORM_FULL_PACKAGE)/Override/SecurityPkg/Library/PlatformSecureLibNull/PlatformSecureLibNull.inf
          AuthVariableLib|MdeModulePkg/Library/AuthVariableLibNull/AuthVariableLibNull.inf
        !endif
      <PcdsFixedAtBuild>
        gEfiMdeModulePkgTokenSpaceGuid.PcdEmuVariableNvModeEnable|TRUE
    }
  !endif
!endif

  MdeModulePkg/Universal/MonotonicCounterRuntimeDxe/MonotonicCounterRuntimeDxe.inf

  MdeModulePkg/Universal/BdsDxe/BdsDxe.inf {
    <LibraryClasses>
!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
      CapsuleLib|MdeModulePkg/Library/DxeCapsuleLibFmp/DxeCapsuleLib.inf # RPPO-CNL-0080: RoyalParkOverrideContent
      NULL|$(PLATFORM_FEATURES_PATH)/CapsuleUpdate/Library/SeamlessRecoverySupportLib/SeamlessRecoveryVarLockLib.inf
!endif
}

  MdeModulePkg/Universal/DriverHealthManagerDxe/DriverHealthManagerDxe.inf
  MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf {
    <LibraryClasses>
!if gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable == TRUE
      NULL|SecurityPkg/Library/DxeImageVerificationLib/DxeImageVerificationLib.inf
!endif
!if gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable == TRUE
      NULL|SecurityPkg/Library/DxeTpm2MeasureBootLib/DxeTpm2MeasureBootLib.inf
!endif
  }

#
# RPPO-LKF-0033: RoyalParkOverrideEnd
#
  $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf {
    <LibraryClasses>
!if gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable == TRUE
      CapsuleLib|$(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Library/DxeCapsuleLibFmp/DxeRuntimeCapsuleLib.inf
!endif
  }
#
# RPPO-LKF-0033: RoyalParkOverrideEnd
#

  #UefiCpuPkg/CpuDxe/CpuDxe.inf

  MdeModulePkg/Universal/ResetSystemRuntimeDxe/ResetSystemRuntimeDxe.inf
  PcAtChipsetPkg/HpetTimerDxe/HpetTimerDxe.inf

  #MdeModulePkg/Bus/Pci/PciHostBridgeDxe/PciHostBridgeDxe.inf
  MdeModulePkg/Bus/Pci/PciBusDxe/PciBusDxe.inf

  #MdeModulePkg/Bus/Pci/SataControllerDxe/SataControllerDxe.inf
  #MdeModulePkg/Bus/Ata/AtaBusDxe/AtaBusDxe.inf
  #MdeModulePkg/Bus/Ata/AtaAtapiPassThru/AtaAtapiPassThru.inf
  MdeModulePkg/Bus/Pci/XhciDxe/XhciDxe.inf
  MdeModulePkg/Bus/Pci/EhciDxe/EhciDxe.inf
  MdeModulePkg/Bus/Pci/UhciDxe/UhciDxe.inf
  MdeModulePkg/Bus/Usb/UsbBusDxe/UsbBusDxe.inf
  MdeModulePkg/Bus/Usb/UsbMassStorageDxe/UsbMassStorageDxe.inf
  MdeModulePkg/Bus/Usb/UsbKbDxe/UsbKbDxe.inf

  MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
  FatPkg/EnhancedFatDxe/Fat.inf

  #MdeModulePkg/Universal/Console/GraphicsOutputDxe/GraphicsOutputDxe.inf
  MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf

  MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf

  MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf

!if gPlatformModuleTokenSpaceGuid.PcdMemoryTestEnable == TRUE
  MdeModulePkg/Universal/MemoryTest/GenericMemoryTestDxe/GenericMemoryTestDxe.inf
!else
  MdeModulePkg/Universal/MemoryTest/NullMemoryTestDxe/NullMemoryTestDxe.inf
!endif

  MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
  MdeModulePkg/Universal/SetupBrowserDxe/SetupBrowserDxe.inf

  MdeModulePkg/Universal/DisplayEngineDxe/DisplayEngineDxe.inf

  MdeModulePkg/Application/UiApp/UiApp.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
      NULL|MdeModulePkg/Library/DeviceManagerUiLib/DeviceManagerUiLib.inf
      NULL|MdeModulePkg/Library/BootManagerUiLib/BootManagerUiLib.inf
      NULL|MdeModulePkg/Library/BootMaintenanceManagerUiLib/BootMaintenanceManagerUiLib.inf
  }
  MdeModulePkg/Application/BootManagerMenuApp/BootManagerMenuApp.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
  }

!if gMinPlatformPkgTokenSpaceGuid.PcdBootToShellOnly == FALSE
  MdeModulePkg/Core/PiSmmCore/PiSmmIpl.inf
  MdeModulePkg/Core/PiSmmCore/PiSmmCore.inf

  MdeModulePkg/Universal/ReportStatusCodeRouter/Smm/ReportStatusCodeRouterSmm.inf
  MdeModulePkg/Universal/StatusCodeHandler/Smm/StatusCodeHandlerSmm.inf

  #UefiCpuPkg/PiSmmCpuDxeSmm/PiSmmCpuDxeSmm.inf

  UefiCpuPkg/CpuIo2Smm/CpuIo2Smm.inf
  MdeModulePkg/Universal/SmmCommunicationBufferDxe/SmmCommunicationBufferDxe.inf
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdBootToShellOnly == FALSE
  MdeModulePkg/Universal/Acpi/AcpiTableDxe/AcpiTableDxe.inf
  MdeModulePkg/Universal/Acpi/FirmwarePerformanceDataTableDxe/FirmwarePerformanceDxe.inf
  MdeModulePkg/Universal/Acpi/FirmwarePerformanceDataTableSmm/FirmwarePerformanceSmm.inf
  MdeModulePkg/Universal/Acpi/BootGraphicsResourceTableDxe/BootGraphicsResourceTableDxe.inf
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable == TRUE
  SecurityPkg/VariableAuthenticated/SecureBootConfigDxe/SecureBootConfigDxe.inf
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable == TRUE
  SecurityPkg/Tcg/MemoryOverwriteControl/TcgMor.inf
  SecurityPkg/Tcg/Tcg2Dxe/Tcg2Dxe.inf {
    <LibraryClasses>
      Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterDxe.inf
      NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha256/HashInstanceLibSha256.inf
  }
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(PLATFORM_FULL_PACKAGE)/Override/SecurityPkg/Tcg/Tcg2Smm/Tcg2Smm.inf
  !else
    SecurityPkg/Tcg/Tcg2Smm/Tcg2Smm.inf {
      <LibraryClasses>
        Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibTcg2/Tpm2DeviceLibTcg2.inf
    }
  !endif
  SecurityPkg/Tcg/Tcg2Config/Tcg2ConfigDxe.inf
!endif

!if gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable == TRUE
  ShellPkg/DynamicCommand/DpDynamicCommand/DpDynamicCommand.inf
!endif
