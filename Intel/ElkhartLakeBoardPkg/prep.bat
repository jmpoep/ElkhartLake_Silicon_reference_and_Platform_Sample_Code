@REM @file
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2018 - 2020 Intel Corporation.
@REM
@REM  The source code contained or described herein and all documents related to the
@REM  source code ("Material") are owned by Intel Corporation or its suppliers or
@REM  licensors. Title to the Material remains with Intel Corporation or its suppliers
@REM  and licensors. The Material may contain trade secrets and proprietary and
@REM  confidential information of Intel Corporation and its suppliers and licensors,
@REM  and is protected by worldwide copyright and trade secret laws and treaty
@REM  provisions. No part of the Material may be used, copied, reproduced, modified,
@REM  published, uploaded, posted, transmitted, distributed, or disclosed in any way
@REM  without Intel's prior express written permission.
@REM
@REM  No license under any patent, copyright, trade secret or other intellectual
@REM  property right is granted to or conferred upon you by disclosure or delivery
@REM  of the Materials, either expressly, by implication, inducement, estoppel or
@REM  otherwise. Any license under such intellectual property rights must be
@REM  express and approved by Intel in writing.
@REM
@REM  Unless otherwise agreed by Intel in writing, you may not remove or alter
@REM  this notice or any other notice embedded in Materials by Intel or
@REM  Intel's suppliers or licensors in any way.
@REM
@REM  This file contains a 'Sample Driver' and is licensed as such under the terms
@REM  of your license agreement with Intel or your vendor. This file may be modified
@REM  by the user, subject to the additional terms of the license agreement.
@REM
@REM @par Specification Reference:
@REM

@echo ON

@REM TODO move these definitions to SetEdk2Env.bat and rename to WORKSPACE_*
@echo Define platform specific environment variables.
@set PLATFORM_PACKAGE=MinPlatformPkg
@set CLIENT_COMMON_PACKAGE=ClientCommonPkg
@set BP_COMMON_PACKAGE=BpCommonPkg
@set PLATFORM_BOARD_PACKAGE=ElkhartLakeBoardPkg
@set PLATFORM_FSP_PACKAGE=ElkhartLakeFspPkg
@set PLATFORM_FULL_PACKAGE=ElkhartLakePlatSamplePkg

@REM Run SetEdk2Env.bat
call SetEdk2Env.bat
@If %SCRIPT_ERROR% EQU 1 goto PrepFail

@set TIP_DIR=%CD%
cd ..\..\

@echo ********************************************************************
@echo ***********           Prep.bat is launched here          ***********
@echo ********************************************************************

@set SILENT_MODE=FALSE
@set CapsuleBuild=FALSE
@set CATALOG=FALSE
@set BFX_BUILD=FALSE
@set FSP_PDB_RELEASE=FALSE
@set PrepRELEASE=DEBUG
@set EDKBUILD=FALSE
@set SETUP_ENABLE=FALSE
@set SECURE_BOOT_ENABLE=FALSE
@set STARTUP_ACM_ENABLE=FALSE
@REM BOOT_STAGE is set to stage 6 by default
@set BOOT_STAGE=6
@rem
@rem BUILD_OPTION_PCD is used in build. It will be cleared here.
@rem EXT_BUILD_FLAGS is used by prep.bat and bld.bat. It will be cleared in the
@rem beginning of prep.bat and not cleared after bld.bat. It is not supposed
@rem to be modified by bld.bat. This will ensure bld.bat can have incremental
@rem build with all correct flags intact.
@rem
@if "%EXT_CONFIG_CLEAR%" == "" (
  @set "BUILD_OPTION_PCD="
)
@REM
@REM Set Build env variable default value
@REM
@set "FSP_BUILD_OPTION_PCD="
@set BUILD=X
@set EHL_BUILD=TRUE
@set EHL_Z0_BUILD=FALSE
@set FSP_BINARY_BUILD=TRUE
@set FSP_WRAPPER_BUILD=TRUE
@set FSP_API_BUILD=TRUE
@set PERFORMANCE_BUILD=FALSE
@set EMBEDDED_BUILD=FALSE

@set EXT_CONFIG_CLEAR=
@set EXT_BUILD_FLAGS=
@set BIOS_SIZE_OPTION=SIZE_130

:CmdLineParse

@if "" == "%1" (
  goto Continue
) else if /i "d" == "%1" (
  echo "d"
  set PrepRELEASE=DEBUG
) else if /i "r" == "%1" (
  echo "r"
  set PrepRELEASE=RELEASE
) else if /i "tr" == "%1" (
  echo "tr"
  set PrepRELEASE=TEST_RELEASE
) else if /i "rp" == "%1" (
  echo "rp"
  set PrepRELEASE=RELEASE
  echo gPlatformModuleTokenSpaceGuid.PcdSymbolInReleaseEnable ^|TRUE
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gPlatformModuleTokenSpaceGuid.PcdSymbolInReleaseEnable=TRUE
  set FSP_PDB_RELEASE=TRUE
) else if /i "s" == "%1" (
  set SILENT_MODE=TRUE
) else if /i "c" == "%1" (
  set CapsuleBuild=TRUE
) else if /i "rc" == "%1" (
  echo "rc"
  set PrepRELEASE=RELEASE
  set CapsuleBuild=TRUE
) else if /i "embedded" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gSiPkgTokenSpaceGuid.PcdEmbeddedEnable=0x1
  set FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% --pcd gSiPkgTokenSpaceGuid.PcdEmbeddedEnable=0x1
  set EMBEDDED_BUILD=TRUE

) else if /i "cov" == "%1" (
  @echo Code Coverage build is not supported
  goto PrepHelp
  @REM  echo gPlatformModuleTokenSpaceGuid.PcdCodeCoverageEnable^|TRUE
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gPlatformModuleTokenSpaceGuid.PcdCodeCoverageEnable=TRUE
  set BUILD=C
) else if /i "edk" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdFspBinaryEnable=FALSE ^
--pcd gSiPkgTokenSpaceGuid.PcdFspWrapperEnable=FALSE ^
--pcd gSiPkgTokenSpaceGuid.PcdFspModeSelection=0

  set FSP_BINARY_BUILD=FALSE
  set FSP_WRAPPER_BUILD=FALSE
  set FSP_API_BUILD=FALSE

  @set EDKBUILD=TRUE
) else if /i "fspb" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdFspBinaryEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdFspWrapperEnable=FALSE

  set FSP_BINARY_BUILD=TRUE
  set FSP_WRAPPER_BUILD=FALSE
) else if /i "fspw" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdFspBinaryEnable=FALSE ^
--pcd gSiPkgTokenSpaceGuid.PcdFspWrapperEnable=TRUE

  set FSP_BINARY_BUILD=FALSE
  set FSP_WRAPPER_BUILD=TRUE
) else if /i "fspnoapi" == "%1" (
  set FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdFspModeSelection=0 ^
--pcd gSiPkgTokenSpaceGuid.PcdFspWrapperEnable=TRUE
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdFspModeSelection=0 ^
--pcd gSiPkgTokenSpaceGuid.PcdFspWrapperEnable=TRUE
  set FSP_API_BUILD=FALSE
  set FSP_BINARY_BUILD=TRUE
  set FSP_WRAPPER_BUILD=TRUE
) else if /i "pacm" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gSiPkgTokenSpaceGuid.PcdFspWrapperEnable=TRUE
  set FSP_WRAPPER_BUILD=TRUE
) else if /i "perf" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gPlatformModuleTokenSpaceGuid.PcdPerformanceEnable=TRUE
  set PERFORMANCE_BUILD=TRUE
  set BUILD=P
) else if /i "ehlz0" == "%1" (
  set EHL_Z0_BUILD=TRUE
  set EHL_BUILD=FALSE
  set BIOS_SIZE_OPTION=SIZE_100
) else if /i "ehl" == "%1" (
  set EHL_BUILD=TRUE
) else if "catalog" == "%1" (
  @echo Catalog build is not supported
  goto PrepHelp
@REM  @set CATALOG=TRUE
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable=TRUE
  set FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% --pcd gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable=TRUE
) else if /i "bfx" == "%1" (
  set BFX_BUILD=TRUE
) else if /i "tenmb" == "%1" (
  set BIOS_SIZE_OPTION=SIZE_100
) else if /i "exclfw" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% ^
--pcd gPlatformModuleTokenSpaceGuid.PcdVbtBinEnable=FALSE ^
--pcd gPlatformModuleTokenSpaceGuid.PcdRaidDriverEfiEnable=FALSE ^
--pcd gPlatformModuleTokenSpaceGuid.PcdNvmeEnable=FALSE ^
--pcd gPlatformModuleTokenSpaceGuid.PcdRsteDriverEfiEnable=FALSE ^
--pcd gPlatformModuleTokenSpaceGuid.PcdIntelGopEnable=FALSE ^
--pcd gBoardModuleTokenSpaceGuid.PcdStartupAcmBinEnable=FALSE ^
--pcd gBoardModuleTokenSpaceGuid.PcdMicrocodeBinEnable=FALSE ^
--pcd gBoardModuleTokenSpaceGuid.PcdBiosGuardBinEnable=FALSE ^
--pcd gSiPkgTokenSpaceGuid.PcdBiosGuardEnable=FALSE
) else if /i "exclfwall" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% ^
--pcd gPlatformModuleTokenSpaceGuid.PcdVbtBinEnable=FALSE ^
--pcd gPlatformModuleTokenSpaceGuid.PcdRaidDriverEfiEnable=FALSE ^
--pcd gPlatformModuleTokenSpaceGuid.PcdNvmeEnable=FALSE ^
--pcd gPlatformModuleTokenSpaceGuid.PcdRsteDriverEfiEnable=FALSE ^
--pcd gPlatformModuleTokenSpaceGuid.PcdMebxEfiEnable=FALSE ^
--pcd gPlatformModuleTokenSpaceGuid.PcdMebxSetupBrowserEnable=FALSE ^
--pcd gPlatformModuleTokenSpaceGuid.PcdIntelGopEnable=FALSE ^
--pcd gBoardModuleTokenSpaceGuid.PcdStartupAcmBinEnable=FALSE ^
--pcd gBoardModuleTokenSpaceGuid.PcdMicrocodeBinEnable=FALSE ^
--pcd gBoardModuleTokenSpaceGuid.PcdBiosGuardBinEnable=FALSE ^
--pcd gSiPkgTokenSpaceGuid.PcdBiosGuardEnable=FALSE

) else if /i "stage1" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gMinPlatformPkgTokenSpaceGuid.PcdBootStage=1
  set BOOT_STAGE=1
) else if /i "stage2" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gMinPlatformPkgTokenSpaceGuid.PcdBootStage=2
  set BOOT_STAGE=2
) else if /i "stage3" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gMinPlatformPkgTokenSpaceGuid.PcdBootStage=3
  set BOOT_STAGE=3
) else if /i "stage4" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gMinPlatformPkgTokenSpaceGuid.PcdBootStage=4
  set BOOT_STAGE=4
) else if /i "stage5" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gMinPlatformPkgTokenSpaceGuid.PcdBootStage=5
  set BOOT_STAGE=5
) else if /i "stage6" == "%1" (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gMinPlatformPkgTokenSpaceGuid.PcdBootStage=6
  set BOOT_STAGE=6
) else if /i "help" == "%1" (
  goto PrepHelp
) else (
  echo Invalid input arguments: %1
  echo.
  goto PrepHelp
)
SHIFT
goto CmdLineParse

:Continue

@echo TIP_DIR             =  %TIP_DIR%
@echo PrepRELEASE         =  %PrepRELEASE%
@echo FSP_PDB_RELEASE     =  %FSP_PDB_RELEASE%
@echo SILENT_MODE         =  %SILENT_MODE%
@echo CapsuleBuild        =  %CapsuleBuild%
@echo CATALOG             =  %CATALOG%
@echo Current Directory   =  %CD%
@echo WORKSPACE           =  %WORKSPACE%
@echo WORKSPACE_CORE      =  %WORKSPACE_CORE%
@echo WORKSPACE_COMMON    =  %WORKSPACE_COMMON%
@echo WORKSPACE_PLATFORM  =  %WORKSPACE_PLATFORM%
@echo WORKSPACE_SILICON   =  %WORKSPACE_SILICON%

goto SkipHelp

:PrepHelp
cd %TIP_DIR%
@echo Preparation for BIOS build.
@echo.
@echo prep [r][rp][s][c][rc][tr][edk][pacm][perf][catalog][bfx][tenmb]][help]
@echo.
@echo   r         To do release build. Default is debug build. See note 1
@echo   rp        To do release build with Symbols - For source level debugging. See note 1
@echo   s         To build in silent mode. . See note 1
@echo   c         To build with CapsuleBuild=TRUE (Debug build). See note 1
@echo   rc        To build with CapsuleBuild=TRUE (Release build). See note 1
@echo   ehl       To set gSiPkgTokenSpaceGuid.PcdEhlCpuEnable^|TRUE and gSiPkgTokenSpaceGuid.PcdEhlPchEnable^|TRUE. See note 1
@echo   cov       To set gPlatformModuleTokenSpaceGuid.PcdCodeCoverageEnable^|TRUE. See note 1
@echo   edk       To build EDK build (Default is Debug build). See note 1
@echo   bfx       To set gSiPkgTokenSpaceGuid.PcdBfxEnable^|TRUE.
@echo   tenmb     To build 10MB BIOS and set gBoardModuleTokenSpaceGuid.PcdBiosSizeMbOption=10
@echo   hfpga     To set gSiPkgTokenSpaceGuid.PcdBfxHfpgaWorkAroundEnable^|TRUE. See note 1
@echo   fspb      To build *Only* FSP Binary (Default is Debug build, adding r for Release build). See note 1
@echo   fspw      To build *Only* FSP Wrapper         (Default is Debug build, adding r for Release build). See note 1
@echo   fspnoapi  To build FSP Wrapper Dispatch Mode  (Default is Debug build, adding r for Release build). See note 1
@echo   pacm      To set gBoardModuleTokenSpaceGuid.PcdStartupAcmProdBinEnable^|TRUE. See note 1
@echo   perf      To set gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable^|TRUE. See note 1
@echo   catalog   To set CATALOG=TRUE for Catalog build.
@echo   exclfw    To exclude Non-BIOS payloads (with MEBx). See note 1
@echo   exclfwall To exclude Non-BIOS payloads (without MEBx). See note 1
@echo.
@echo 1) Re-running prep without these arguments cannot be used for
@echo    incremental build. Hence, these inputs must be supplied each time
@echo    prep are desired to be re-run.
@echo   stage1      To set gMinPlatformPkgTokenSpaceGuid.PcdBootStage^|1. Stage 1 build
@echo   stage2      To set gMinPlatformPkgTokenSpaceGuid.PcdBootStage^|2. Stage 2 build
@echo   stage3      To set gMinPlatformPkgTokenSpaceGuid.PcdBootStage^|3. Stage 3 build
@echo   stage4      To set gMinPlatformPkgTokenSpaceGuid.PcdBootStage^|4. Stage 4 build
@echo   stage5      To set gMinPlatformPkgTokenSpaceGuid.PcdBootStage^|5. Stage 5 build
@echo   stage6      To set gMinPlatformPkgTokenSpaceGuid.PcdBootStage^|6. Stage 6 build
goto PrepDone

:SkipHelp

if %BIOS_SIZE_OPTION% EQU SIZE_100 (
  set BFX_BUILD=FALSE
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gBoardModuleTokenSpaceGuid.PcdBiosSizeMbOption=10
) else (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gBoardModuleTokenSpaceGuid.PcdBiosSizeMbOption=13
)

if %BFX_BUILD% EQU TRUE (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gSiPkgTokenSpaceGuid.PcdBfxEnable=TRUE
  set FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% --pcd gSiPkgTokenSpaceGuid.PcdBfxEnable=TRUE
) else (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gSiPkgTokenSpaceGuid.PcdBfxEnable=FALSE
  set FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% --pcd gSiPkgTokenSpaceGuid.PcdBfxEnable=FALSE
)

if %FSP_API_BUILD% EQU TRUE (
  echo FSP API build is enabled by default
  set FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdFspModeSelection=1 ^
--pcd gSiPkgTokenSpaceGuid.PcdFspWrapperEnable=TRUE
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdFspModeSelection=1 ^
--pcd gSiPkgTokenSpaceGuid.PcdFspWrapperEnable=TRUE
)

if %EHL_BUILD% EQU TRUE (
set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlCpuEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlPchEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdIclPchEnable=FALSE

set FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlCpuEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlPchEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdIclPchEnable=FALSE
)

if %EHL_Z0_BUILD% EQU TRUE (
set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlCpuEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlPchEnable=FALSE ^
--pcd gSiPkgTokenSpaceGuid.PcdIclPchEnable=TRUE

  set FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlCpuEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlPchEnable=FALSE ^
--pcd gSiPkgTokenSpaceGuid.PcdIclPchEnable=TRUE
)

if exist %WORKSPACE%\Prep.log del %WORKSPACE%\Prep.log

:PrepReleaseCheck

@echo ********************************************************************
@echo ***********        Prebuild.bat is launched here       *************
@echo ********************************************************************
cd %TIP_DIR%
@echo Current Directory   =  %CD%
@echo WORKSPACE           =  %WORKSPACE%
@echo WORKSPACE_CORE      =  %WORKSPACE_CORE%
@echo WORKSPACE_COMMON    =  %WORKSPACE_COMMON%
@echo WORKSPACE_PLATFORM  =  %WORKSPACE_PLATFORM%
@echo WORKSPACE_SILICON   =  %WORKSPACE_SILICON%
@echo PrepRelease         =  %PrepRelease%
@echo CapsuleBuild        =  %CapsuleBuild%

@if %SILENT_MODE% EQU TRUE goto BldSilent

call prebuild.bat %PrepRelease% %CapsuleBuild%
goto PrePrepDone

:BldSilent
cd %TIP_DIR%
call prebuild.bat %PrepRelease% %CapsuleBuild% 1>>%WORKSPACE%\Prep.log 2>&1

:PrePrepDone
@If %SCRIPT_ERROR% EQU 1 goto PrepFail
@goto PrepDone

:PrepFail
@echo.
@echo !! The EDKII BIOS build has failed in prep!
@echo.
@exit /b 1

:PrepDone
@echo.
@echo Bios Prep succeeded
@echo.
