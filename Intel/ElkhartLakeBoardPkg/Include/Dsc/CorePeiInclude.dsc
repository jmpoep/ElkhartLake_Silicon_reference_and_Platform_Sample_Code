## @file
#  Platform description.
#
# Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

  #
  # Generic EDKII Driver
  #
!if gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable == TRUE
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Core/Pei201903/PeiMain.inf {
      <LibraryClasses>
        DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
    }
  !else
    MdeModulePkg/Core/Pei/PeiMain.inf {
      <LibraryClasses>
        DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
    }
  !endif
!else
  !if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
    $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Core/Pei/PeiMain.inf {
      <LibraryClasses>
        DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
    }
  !else
    MdeModulePkg/Core/Pei/PeiMain.inf {
      <LibraryClasses>
        DebugLib|$(PLATFORM_FULL_PACKAGE)/Library/BaseDebugLibAllDebugPort/BaseDebugLibAllDebugPort.inf
    }
  !endif
!endif

  MdeModulePkg/Universal/PCD/Pei/Pcd.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  }
  MdeModulePkg/Universal/ReportStatusCodeRouter/Pei/ReportStatusCodeRouterPei.inf
  MdeModulePkg/Universal/StatusCodeHandler/Pei/StatusCodeHandlerPei.inf

  UefiCpuPkg/CpuIoPei/CpuIoPei.inf


!if gSiPkgTokenSpaceGuid.PcdBfxEnable == TRUE
  $(PLATFORM_FULL_PACKAGE)/Override/MdeModulePkg/Universal/FaultTolerantWritePei/FaultTolerantWritePei.inf
  $(PLATFORM_SI_PACKAGE)/SampleCode/MdeModulePkg/Universal/Variable/Pei/VariablePei.inf
!else
  MdeModulePkg/Universal/FaultTolerantWritePei/FaultTolerantWritePei.inf
  MdeModulePkg/Universal/Variable/Pei/VariablePei.inf
!endif

  MdeModulePkg/Universal/PcatSingleSegmentPciCfg2Pei/PcatSingleSegmentPciCfg2Pei.inf

  MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
  }
  
!if gMinPlatformPkgTokenSpaceGuid.PcdTpm2Enable == TRUE
  SecurityPkg/Tcg/Tcg2Config/Tcg2ConfigPei.inf
  SecurityPkg/Tcg/Tcg2Pei/Tcg2Pei.inf {
    <LibraryClasses>
      NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha256/HashInstanceLibSha256.inf
  }
!endif
