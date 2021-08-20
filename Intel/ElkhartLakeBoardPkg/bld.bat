@REM @file
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2018 - 2019 Intel Corporation.
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

:: Useage: bld [/s] [/f <FEATURE_PCD_NAME> <FALSE or TRUE>] [/r]
::
:: For a given build command, 3 options may be passed into this batch file via command prompt:
:: 1) /s = Redirects all output to a file called EDK2.log(Prep.log must be existed), which will be located at the root.
:: 2) /f = Defines the passing in of a single override to a feature PCD that is used in the platform
::    DSC file.  If this parameter is used, it is to be followed immediately after by both the feature
::    pcd name and value. FeaturePcd is the full PCD name, like gMinPlatformPkgTokenSpaceGuid.PcdOptimizeCompilerEnable
:: 3) /r = Useful for faster rebuilds when no changes have been made to .inf files. Passes -u to
::    build.exe to skip the generation of makefiles.
:: 4) rom = Build Bios.rom only and building SPIs will be skipped.
::

@echo on
@echo ********************************************************************
@echo ******************    BLD.BAT    ***********************************
@echo ********************************************************************

@rem cd %WORKSPACE%
@echo %CD%

@SET SILENT_MODE=FALSE
@SET REBUILD_MODE=
@SET BUILD_ROM_ONLY=

:: Loop through arguements until all are processed
:BUILD_FLAGS_LOOP
@if "%~1" == "" goto BUILD_FLAGS_LOOP_DONE

@if "%~1" == "/f" (
  shift
  goto BUILD_FLAGS_LOOP
)
@if "%~1" == "/s" (
  SET SILENT_MODE=TRUE
  @if exist %WORKSPACE%\Build.log del %WORKSPACE%\Build.log
  shift
  goto BUILD_FLAGS_LOOP
)
@if "%~1" == "/r" (
  SET REBUILD_MODE=-u
  shift
  goto BUILD_FLAGS_LOOP
)
@if "%~1" == "rom" (
  SET BUILD_ROM_ONLY=rom
  shift
  goto BUILD_FLAGS_LOOP
)
:: Unknown build flag.
shift
goto BUILD_FLAGS_LOOP
:BUILD_FLAGS_LOOP_DONE

:: Output the build variables the user has selected.
@echo.
@echo  User Selected build options:
@echo    SILENT_MODE = %SILENT_MODE%
@echo    REBUILD_MODE = %REBUILD_MODE%
@echo    BUILD_ROM_ONLY = %BUILD_ROM_ONLY%
@echo.

:: Start the FSP build process
@echo FSP_BINARY_BUILD=%FSP_BINARY_BUILD%
@REM
@echo Build FSP Binary
@REM
@if not defined FSP_BINARY_BUILD goto :SkipFspBinaryBuild
@if %FSP_BINARY_BUILD% EQU FALSE goto :SkipFspBinaryBuild
@set FSP_BUILD_PARAMETER=/d
@set FSP_PKG_NAME=ElkhartLakeFspPkg
@if /I "%TARGET%" == "RELEASE" (
  @if "%FSP_TEST_RELEASE%"=="TRUE" (
    set FSP_BUILD_PARAMETER=/tr
  ) else (
    set FSP_BUILD_PARAMETER=/r
  )
  @if "%FSP_PDB_RELEASE%"=="TRUE" (
    set FSP_BUILD_PARAMETER=/rp
  )
)
set WORKSPACE_FSP_BIN=%WORKSPACE%\Intel

@echo %CD%
@rem
@rem  By Default Build for EHL
@rem
@set FspTargetOption=ElkhartLake
if %EHL_Z0_BUILD% EQU TRUE (
@set FspTargetOption=ElkhartLakeZ0
)

@if not "%FspTargetOption%" == "" (
  @echo FSP build target is %FspTargetOption%
) else (
  @echo FSP build target is not specified.
  @goto :BldFail
)

@if %SILENT_MODE% EQU TRUE goto FspSilent

call %WORKSPACE_COMMON%\ClientSiliconPkg\BuildFsp.cmd ElkhartLake %FspTargetOption% %FSP_BUILD_PARAMETER%
@goto FspBuildEnd

:FspSilent
call %WORKSPACE_COMMON%\ClientSiliconPkg\BuildFsp.cmd ElkhartLake %FspTargetOption% %FSP_BUILD_PARAMETER% 1>> %WORKSPACE%\Build.log 2>&1

:FspBuildEnd
@if %ERRORLEVEL% NEQ 0 (
  @echo !!! ERROR:Build Fail !!!
  @echo %WORKSPACE_COMMON%\ClientSiliconPkg\BuildFsp.cmd ElkhartLake %FspTargetOption% %FSP_BUILD_PARAMETER%
  set SCRIPT_ERROR=1
  goto :BldFail
) else (
  @echo FSP build has succeeded
  @echo FSP build has succeeded >> %WORKSPACE%\Build.log 2>&1
)

@if %FSP_WRAPPER_BUILD% EQU FALSE goto :BldEnd

:SkipFspBinaryBuild
@if %FSP_WRAPPER_BUILD% EQU FALSE goto :SkipPatchFspBinFvsBaseAddress
del /f %WORKSPACE_SILICON%\%PLATFORM_FSP_BIN_PACKAGE%\Fsp_Rebased*.fd

cd %WORKSPACE%
@echo %CD%
@echo ********************* BLD.BAT *****************************

@echo WORKSPACE_PLATFORM     = %WORKSPACE_PLATFORM%
@echo WORKSPACE_SILICON      = %WORKSPACE_SILICON%
@echo PROJECT                = %PROJECT%
@echo PLATFORM_PACKAGE       = %PLATFORM_PACKAGE%
@echo PLATFORM_BOARD_PACKAGE = %PLATFORM_BOARD_PACKAGE%
@echo WORKSPACE_FSP_BIN      = %WORKSPACE_FSP_BIN%

@if exist %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%\BoardPkgPcd.dsc attrib -r %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%\BoardPkgPcd.dsc
@echo .
@if %BIOS_SIZE_OPTION% EQU SIZE_100 (
  @call python %WORKSPACE_CORE_PLATFORM%\%PLATFORM_PACKAGE%\Tools\Fsp\RebaseAndPatchFspBinBaseAddress.py %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%\Include\Fdf\FlashMapTenMbInclude.fdf %WORKSPACE_FSP_BIN%\ElkhartLakeFspBinPkg Fsp.fd %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%\BoardPkgPcd.dsc 0x0
) else (
  @call python %WORKSPACE_CORE_PLATFORM%\%PLATFORM_PACKAGE%\Tools\Fsp\RebaseAndPatchFspBinBaseAddress.py %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%\Include\Fdf\FlashMapInclude.fdf %WORKSPACE_FSP_BIN%\ElkhartLakeFspBinPkg Fsp.fd %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%\BoardPkgPcd.dsc 0x0
)
@echo .
@if %ERRORLEVEL% NEQ 0 (
  @echo !!! ERROR:RebaseAndPatchFspBinBaseAddress failed!!!
  set SCRIPT_ERROR=1
  goto :BldFail
)

cd %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%

copy /y /b %WORKSPACE_SILICON%\%PLATFORM_FSP_BIN_PACKAGE%\Fsp_Rebased_S.fd+%WORKSPACE_SILICON%\%PLATFORM_FSP_BIN_PACKAGE%\Fsp_Rebased_M.fd+%WORKSPACE_SILICON%\%PLATFORM_FSP_BIN_PACKAGE%\Fsp_Rebased_T.fd %WORKSPACE_SILICON%\%PLATFORM_FSP_BIN_PACKAGE%\Fsp_Rebased.fd
:SkipPatchFspBinFvsBaseAddress

@if %SETUP_ENABLE% EQU FALSE (
    goto SkipUniTool
)
call %WORKSPACE_PLATFORM%\ElkhartLakePlatSamplePkg\Tools\UniTool\UniTool.bat
@if %ERRORLEVEL% NEQ 0 goto BldFail

:SkipUniTool

@echo Current Directory = %CD%
@echo ********************* BLD.BAT *****************************
@echo SILENT_MODE          = %SILENT_MODE%
@echo NUMBER_OF_PROCESSORS = %NUMBER_OF_PROCESSORS%
@echo REBUILD_MODE         = %REBUILD_MODE%
@echo EXT_BUILD_FLAGS      = %EXT_BUILD_FLAGS%


@if %SILENT_MODE% EQU TRUE goto BldSilent
call build %BUILD_OPTION_PCD% -n %NUMBER_OF_PROCESSORS% %REBUILD_MODE% %EXT_BUILD_FLAGS%

@echo %CD%
@echo ********************* BLD.BAT *****************************
@echo ERRORLEVEL=%ERRORLEVEL%

@if %ERRORLEVEL% NEQ 0 goto BldFail
@echo.
@echo Running postbuild.bat to complete the build process.
@echo.
call %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%\postbuild.bat %BUILD_ROM_ONLY%
@if %SCRIPT_ERROR% EQU 1 goto BldFail
@goto BldSuccess

:BldSilent
@echo.
@echo ********************************************************************
@echo ***********            Build is launched here             **********
@echo ********************************************************************
@echo.
call build %BUILD_OPTION_PCD% -n %NUMBER_OF_PROCESSORS% %REBUILD_MODE% %EXT_BUILD_FLAGS% 1>>%WORKSPACE%\Build.log 2>&1
@echo ERRORLEVEL=%ERRORLEVEL% 1>>%WORKSPACE%\Build.log 2>&1

@if %ERRORLEVEL% NEQ 0 goto BldFail
@echo. >>%WORKSPACE%\Build.log
@echo Running postbuild.bat to complete the build process. >> %WORKSPACE%\Build.log
@echo. >>%WORKSPACE%\Build.log
call %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%\postbuild.bat %BUILD_ROM_ONLY% 1>>%WORKSPACE%\Build.log 2>&1
@If %SCRIPT_ERROR% EQU 1 goto BldFail

:BldSuccess
@echo.
@echo BFX_BUILD:            %BFX_BUILD%
@echo BIOS_SIZE_OPTION:     %BIOS_SIZE_OPTION%
@echo EDK2_MASTER_BUILD:    %EDK2_MASTER_BUILD%
@echo TARGET:               %TARGET%
@echo TOOL_CHAIN_TAG:       %TOOL_CHAIN_TAG%
@echo BIOS location:        %BUILD_DIR%\FV
@echo ROM Images location:  %WORKSPACE%\RomImages
@echo.
@echo The BIOS build has successfully completed!
@echo.
@REM

@goto BldEnd

:BldFail
cd %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%
@echo.
@echo The BIOS Build has failed!
@echo.
@exit /b 1

:BldEnd
@if %SILENT_MODE% EQU TRUE (
  @if exist EDK2.log del EDK2.log
  @if exist Prep.log if exist Build.log copy Prep.log+Build.log EDK2.log
)

cd %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%