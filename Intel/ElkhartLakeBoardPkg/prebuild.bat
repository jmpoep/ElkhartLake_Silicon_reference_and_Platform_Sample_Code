@REM @file
@REM  Pre build script.
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2017 - 2019 Intel Corporation.
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

@echo on
@echo ********************************************************************
@echo *******************     PreBuild.BAT     ***************************
@echo ********************************************************************

@echo %CD%
cd ..\..\
set WORKSPACE=%CD%
@echo %CD%

@REM Set build TARGET.
@if /I "%1" == "" (
  set TARGET=DEBUG
  set TARGET_SHORT=D
  set FSP_BUILD_PARAMETER=/d
) else if /I "%1" == "DEBUG" (
  set TARGET=DEBUG
  set TARGET_SHORT=D
  set FSP_BUILD_PARAMETER=/d
) else if /I "%1" == "RELEASE" (
  set TARGET=RELEASE
  set TARGET_SHORT=R
  set FSP_BUILD_PARAMETER=/r
) else (
  echo.
  echo !!! ERROR !!! Incorrect TARGET option for prebuild.bat. !!!
  echo.
  set SCRIPT_ERROR=1
  goto :EndPreBuild
)

@echo Set build capsule flag with default being OFF
@set CAPSULE_BUILD=0

@if /I "%2" == "TRUE" (
  @set CAPSULE_BUILD=1
  goto StartCapsulePrep
)

:StartCapsulePrep

set WORKSPACE=%CD%
@REM
@REM In order to avoid dual backslash marks, remove the ending backslash mark for file path concatenation.
@REM
if %WORKSPACE:~-1%==\ (
  set WORKSPACE_ROOT=%WORKSPACE:~0,-1%
) else (
  set WORKSPACE_ROOT=%WORKSPACE%
)
@set WORKSPACE_CORE=%WORKSPACE_ROOT%\Edk2
@set WORKSPACE_CORE_PLATFORM=%WORKSPACE_ROOT%\Edk2Platforms\Platform\Intel
@set WORKSPACE_CORE_SILICON=%WORKSPACE_ROOT%\Edk2Platforms\Silicon\Intel
@set WORKSPACE_COMMON=%WORKSPACE_ROOT%\Intel
@set WORKSPACE_PLATFORM=%WORKSPACE_ROOT%\Intel
@set WORKSPACE_SILICON=%WORKSPACE_ROOT%\Intel
@set WORKSPACE_FSP_BIN=%WORKSPACE%\Intel
@set PACKAGES_PATH=%WORKSPACE%;%WORKSPACE_CORE_SILICON%;%WORKSPACE_CORE%;%WORKSPACE_CORE_PLATFORM%;%WORKSPACE_COMMON%;%WORKSPACE_PLATFORM%;%WORKSPACE_SILICON%
@set EDK_TOOLS_BIN=%WORKSPACE_CORE%\BaseTools\Bin\Win32
@set EDK_TOOLS_PATH=%WORKSPACE_CORE%\BaseTools
@set WORKSPACE_CONF=%WORKSPACE_ROOT%\Conf
@set WORKSPACE_ROM=%WORKSPACE_ROOT%\RomImages
@set FIND_PCD_CMD=%WORKSPACE_COMMON%\%CLIENT_COMMON_PACKAGE%\Tools\FindPcd\Bin\FindPCD.exe
@set FIND_PCD_DSC=%WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\PlatformPkgConfig.dsc

@if not defined WORKSPACE_ADDITIONAL_TOOLS_PATH (
  @set WORKSPACE_ADDITIONAL_TOOLS_PATH=%WORKSPACE_COMMON%\%CLIENT_COMMON_PACKAGE%\Tools\FCE;%WORKSPACE_COMMON%\%CLIENT_COMMON_PACKAGE%\Tools\FMMT;%WORKSPACE_COMMON%\%BP_COMMON_PACKAGE%\Tools\KeyEnroll;%WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\Tools\ToolScripts\SignFv;%WORKSPACE_COMMON%\%CLIENT_COMMON_PACKAGE%\Tools\Nasm
  goto SetAdditionalPath
) else (
  goto SetNormalPath
)

:SetAdditionalPath
@set PATH=%WORKSPACE_ADDITIONAL_TOOLS_PATH%;%PATH%
@set OPENSSL_PATH=%WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\Tools\OpenSSL

:SetNormalPath
@set EFI_SOURCE=%WORKSPACE_CORE%

@echo %WORKSPACE%
@echo %WORKSPACE_ROOT%
@echo %WORKSPACE_CORE%
@echo %WORKSPACE_COMMON%
@echo %WORKSPACE_PLATFORM%
@echo %WORKSPACE_SILICON%
@echo %PACKAGES_PATH%
@echo %EDK_TOOLS_BIN%
@echo %EDK_TOOLS_PATH%
@echo %WORKSPACE_CONF%
@echo %WORKSPACE_ROM%

@echo %WORKSPACE_PLATFORM_BIN%
@echo %WORKSPACE_SILICON_BIN%
@echo %WORKSPACE_FSP_BIN%
@echo %PLATFORM_PACKAGE%
@echo %PLATFORM_BOARD_PACKAGE%

@echo %WORKSPACE_PLATFORM%
@echo %PLATFORM_BOARD_PACKAGE%

@set SCRIPT_ERROR=0
@set CATALOG_DEBUG=0

@if not exist %WORKSPACE_CONF% mkdir %WORKSPACE_CONF%

@if %CATALOG% EQU TRUE (
  @if exist c:\python27 (
    set PYTHON_DIR=c:\python27
  ) else (
    echo.
    echo !!! ERROR !!! Catalog feature requirement issue: Python27 is not found under C:\Python27.
    echo.
    set SCRIPT_ERROR=1
    goto :EndPreBuild
  )
  @if exist %WORKSPACE_COMMON%\ClientSiliconPkg\Tools\Catalog\CatalogEncoder.py (
    set CATALOG_ENCODER=%WORKSPACE_COMMON%\ClientSiliconPkg\Tools\Catalog\CatalogEncoder.py
  ) else (
    echo.
    echo !!! ERROR !!! Catalog feature requirement issue: CatalogEncoder.py is not found.
    echo.
    set SCRIPT_ERROR=1
    goto :EndPreBuild
  )

)

@echo Set basic environment.
@echo.
@echo Prebuild:  Run edksetup.bat batch file.
@echo.
echo %CD%
@if %CATALOG_DEBUG% == 0 (
  @del %WORKSPACE%\Conf\build_rule.txt
)
echo %CD%
cd %WORKSPACE_CORE%
echo %CD%
@call edksetup.bat Rebuild
echo %CD%
cd %WORKSPACE%
echo %CD%
@set EFI_SOURCE=%WORKSPACE_CORE%

@REM
@echo Setup Visual Studio environment. Order of precedence is 2017, 2015, 2013, 2012, 2010 and then 2008.
@REM
@REM NOTE: To override precedence set TOOL_CHAIN_TAG before calling prep.bat.
@REM       Example: set TOOL_CHAIN_TAG=VS2008
@REM

@echo Check if tool chain has not been selected and Visual Studio 2017 is installed.
@if not defined TOOL_CHAIN_TAG (
  if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
    set TOOL_CHAIN_TAG=VS2017
  ) else if exist "%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe" (
    set TOOL_CHAIN_TAG=VS2017
  ) else (
    goto VS2017CheckDone
  )
)

@echo If Visual Studio 2017 is selected by priority or by preference, setup the environment variables.
@if /I "%TOOL_CHAIN_TAG%"=="VS2017" (
  echo.
  echo Prebuild:  Set the VS2017 environment.
  echo.
  if not defined VS150COMNTOOLS (
    if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
      for /f "usebackq tokens=1* delims=: " %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"`) do (
        if /i "%%i"=="installationPath" call "%%j\VC\Auxiliary\Build\vcvars32.bat"
      )
    ) else if exist "%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe" (
      for /f "usebackq tokens=1* delims=: " %%i in (`"%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe"`) do (
        if /i "%%i"=="installationPath" call "%%j\VC\Auxiliary\Build\vcvars32.bat"
      )
    )
  )
  if defined VCToolsInstallDir (
    if not defined VS2017_PREFIX (
      set "VS2017_PREFIX=%VCToolsInstallDir%"
    )
  )
)
:VS2017CheckDone

@echo Check if tool chain has not been selected and Visual Studio 2015 is installed.
@if not defined TOOL_CHAIN_TAG (
  if defined VS140COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2015
  )
)

@echo If Visual Studio 2015 is selected by priority or by preference, setup the environment variables.
@if /I "%TOOL_CHAIN_TAG%"=="VS2015" (
  echo.
  echo Prebuild:  Set the VS2015 environment.
  echo.
  if not defined VSINSTALLDIR call "%VS140COMNTOOLS%\vsvars32.bat"
  if /I "%VS140COMNTOOLS%" == "C:\Program Files\Microsoft Visual Studio 14.0\Common7\Tools\" (
    set TOOL_CHAIN_TAG=VS2015
  ) else (
    set TOOL_CHAIN_TAG=VS2015x86
  )
)

@echo Check if tool chain has not been selected and Visual Studio 2013 is installed.
@if not defined TOOL_CHAIN_TAG (
  if defined VS120COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2013
  )
)

@echo If Visual Studio 2013 is selected by priority or by preference, setup the environment variables.
@if /I "%TOOL_CHAIN_TAG%"=="VS2013" (
  echo.
  echo Prebuild:  Set the VS2013 environment.
  echo.
  if not defined VSINSTALLDIR call "%VS120COMNTOOLS%\vsvars32.bat"
  if /I "%VS120COMNTOOLS%" == "C:\Program Files\Microsoft Visual Studio 12.0\Common7\Tools\" (
    set TOOL_CHAIN_TAG=VS2013
  ) else (
    set TOOL_CHAIN_TAG=VS2013x86
  )
)

@REM Check if tool chain has not been selected and Visual Studio 2012 is installed.
@if not defined TOOL_CHAIN_TAG (
  if defined VS110COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2012
  )
)

@REM If Visual Studio 2012 is selected by priority or by preference, setup the environment variables.
@if /I "%TOOL_CHAIN_TAG%"=="VS2012" (
  echo.
  echo Prebuild:  Set the VS2012 environment.
  echo.
  if not defined VSINSTALLDIR call "%VS110COMNTOOLS%\vsvars32.bat"
  if /I "%VS110COMNTOOLS%" == "C:\Program Files\Microsoft Visual Studio 11.0\Common7\Tools\" (
    set TOOL_CHAIN_TAG=VS2012
  ) else (
    set TOOL_CHAIN_TAG=VS2012x86
  )
)

@REM Check if tool chain has not been selected and Visual Studio 2010 is installed.
@if not defined TOOL_CHAIN_TAG (
  if defined VS100COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2010
  )
)

@REM If Visual Studio 2010 is selected by priority or by preference, setup the environment variables.
@if /I "%TOOL_CHAIN_TAG%"=="VS2010" (
  echo.
  echo Prebuild:  Set the VS2010 environment.
  echo.
  if not defined VSINSTALLDIR call "%VS100COMNTOOLS%\vsvars32.bat"
  if /I "%VS100COMNTOOLS%" == "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\" (
    set TOOL_CHAIN_TAG=VS2010
  ) else (
    set TOOL_CHAIN_TAG=VS2010x86
  )
)

@REM Check if tool chain has not been selected and Visual Studio 2008 is installed.
@if not defined TOOL_CHAIN_TAG (
  if defined VS90COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2008
  )
)

@REM If Visual Studio 2008 is selected by priority or by preference, setup the environment variables.
@if /I "%TOOL_CHAIN_TAG%"=="VS2008" (
  echo.
  echo Prebuild:  Set the VS2008 environment.
  echo.
  if not defined VSINSTALLDIR call "%VS90COMNTOOLS%\vsvars32.bat"
  if /I "%VS90COMNTOOLS%" == "C:\Program Files\Microsoft Visual Studio 9.0\Common7\Tools\" (
    set TOOL_CHAIN_TAG=VS2008
  ) else (
    set TOOL_CHAIN_TAG=VS2008x86
  )
)

@echo If no supported version of Visual Studio was detected, return an error.
@if not defined TOOL_CHAIN_TAG (
  echo.
  echo !!! ERROR !!! Visual Studio not installed correctly!!!
  echo.
  set SCRIPT_ERROR=1
  goto :EndPreBuild
)

@set BUILD_DIR=Build\%PLATFORM_BOARD_PACKAGE%\%TARGET%_%TOOL_CHAIN_TAG%
@set BUILD_FSP_DIR=Build\%PLATFORM_FSP_PACKAGE%\%TARGET%_%TOOL_CHAIN_TAG%
@set BUILD_DIR_PATH=%WORKSPACE%\%BUILD_DIR%
@set BUILD_X64=%BUILD_DIR_PATH%\X64
@set BUILD_IA32=%BUILD_DIR_PATH%\IA32


@echo.
@echo Prebuild:  Set build environment.
@echo.
@echo BUILD_IA32 = %BUILD_IA32%
@echo BUILD_X64 = %BUILD_X64%
@if not exist %BUILD_DIR_PATH% (
  mkdir %BUILD_DIR_PATH%
)
@if not exist %BUILD_IA32% (
  mkdir %BUILD_IA32%
)
@if not exist %BUILD_X64% (
  mkdir %BUILD_X64%
)

@findstr /V "ACTIVE_PLATFORM TARGET TARGET_ARCH TOOL_CHAIN_TAG BUILD_RULE_CONF" %WORKSPACE%\Conf\target.txt > %BUILD_DIR_PATH%\target.txt
@echo ACTIVE_PLATFORM = %WORKSPACE_PLATFORM%/%PLATFORM_BOARD_PACKAGE%/BoardPkg.dsc        >> %BUILD_DIR_PATH%\target.txt
@echo TARGET          = %TARGET%                                  >> %BUILD_DIR_PATH%\target.txt
@echo TARGET_ARCH     = IA32 X64                                  >> %BUILD_DIR_PATH%\target.txt
@echo TOOL_CHAIN_TAG  = %TOOL_CHAIN_TAG%                          >> %BUILD_DIR_PATH%\target.txt
@echo BUILD_RULE_CONF = Conf/build_rule.txt                       >> %BUILD_DIR_PATH%\target.txt
@move /Y %BUILD_DIR_PATH%\target.txt Conf

@REM
@REM   SiPkg DEC file generation
@REM
@echo Build SiPkg.dec from SiPkg.dec.template file.
@pushd %WORKSPACE_SILICON%\ClientOneSiliconPkg
if exist %WORKSPACE_SILICON%\ClientOneSiliconPkg\SiPkg.dec @del /Q %WORKSPACE_SILICON%\ClientOneSiliconPkg\SiPkg.dec

@python gen_dec.py SiPkg.dec.template ElkhartLake
@echo SiPkg DEC generated for ElkhartLake

@popd

@echo Current Directory = %CD%
@echo WORKSPACE_FSP_BIN = %WORKSPACE_FSP_BIN%

@if %BOOT_STAGE% EQU 5 (
  set SECUREBOOT_ENABLE=TRUE
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD% --pcd gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable=TRUE
)

@if %BOOT_STAGE% EQU 6 (
  set BUILD_OPTION_PCD=%BUILD_OPTION_PCD%^
  --pcd gBoardModuleTokenSpaceGuid.PcdSetupEnable=TRUE^
  --pcd gMinPlatformPkgTokenSpaceGuid.PcdUefiSecureBootEnable=TRUE^
  --pcd gBoardModuleTokenSpaceGuid.PcdStartupAcmBinEnable=TRUE

  set SETUP_ENABLE=TRUE
  set SECURE_BOOT_ENABLE=TRUE
  set STARTUP_ACM_ENABLE=TRUE
)

@REM
@if /I "%EHL_BUILD%" == "TRUE" (
  @echo EHL_BUILD = %EHL_BUILD%
  @set FspTarget = ElkhartLake
)

@REM
@REM
@REM Check %FSP_BINARY_BUILD% and set %FSP_TEST_RELEASE%
@REM
@set FSP_TEST_RELEASE=FALSE
@if %FSP_BINARY_BUILD% EQU TRUE (
  if /I "%1" == "TEST_RELEASE" (
    set FSP_TEST_RELEASE=TRUE
  )
)
@echo FSP_BINARY_BUILD (%FSP_BINARY_BUILD%)
@echo FSP_TEST_RELEASE (%FSP_TEST_RELEASE%)


@if "FSP_BINARY_BUILD"=="TRUE" (
  @if %FSP_WRAPPER_BUILD% EQU FALSE goto :EndPreBuild
)
@echo FSP_BINARY_BUILD = %FSP_BINARY_BUILD%
@echo FSP_TEST_RELEASE = %FSP_TEST_RELEASE%
@echo FSP_WRAPPER_BUILD = %FSP_WRAPPER_BUILD%



@REM
@REM Printing the build type
@REM
@echo.
@echo Printing the build type ([U]nified, [N]on-Restricted, [I]nternal, E[x]ternal, [P]erformance, SL[E], Code-[C]overage)
@echo Build type (%BUILD%)
@echo.
:BiosIdBuild
set BIOS_ID_FILE=%BUILD_DIR%\BiosId.env
copy %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%\BiosId.env %BIOS_ID_FILE% /Y
set BUILD=I
set PCH_TYPE=S
@if %FSP_WRAPPER_BUILD% EQU FALSE (
  echo BOARD_ID      = EHL%PCH_TYPE%E2%BUILD%>> %BIOS_ID_FILE%
) else (
  echo BOARD_ID      = EHL%PCH_TYPE%FW%BUILD%>> %BIOS_ID_FILE%
)
echo BOARD_EXT     = %TARGET_SHORT%00>> %BIOS_ID_FILE%

%WORKSPACE_COMMON%\%BP_COMMON_PACKAGE%\Tools\GenBiosId\GenBiosId.exe ^
-i %BIOS_ID_FILE% ^
-o %BUILD_IA32%\BiosId.bin

@REM
@REM @Todo: Need to check if the copies from ElkhartLakeSvRestrictedPkg are required or not
@REM

@if %CAPSULE_BUILD% == 1 (
  goto EndCapsulePrep
)

@REM
@echo Skip BIOS_SIZE_OPTION if it is predefined
@REM
@if NOT "%BIOS_SIZE_OPTION%" == "" goto BiosSizeDone

@set BIOS_SIZE_OPTION=

@REM default size option is 13M
@set BIOS_SIZE_OPTION=-DBIOS_SIZE_OPTION=SIZE_130

:BiosSizeDone
@echo BIOS_SIZE_OPTION=%BIOS_SIZE_OPTION%


:EndCapsulePrep
@echo.
@echo   Prebuild is complete.
@echo   Current Directory    = %CD%
@echo   EFI_SOURCE           = %EFI_SOURCE%
@echo   TARGET               = %TARGET%
@echo   TARGET_ARCH          = IA32 X64
@echo   TOOL_CHAIN_TAG       = %TOOL_CHAIN_TAG%
@echo   WORKSPACE            = %WORKSPACE%
@echo   WORKSPACE_CORE       = %WORKSPACE_CORE%
@echo   EXT_BUILD_FLAGS      = %EXT_BUILD_FLAGS%
@echo   WORKSPACE_PLATFORM   = %WORKSPACE_PLATFORM%
@echo.
:EndPreBuild
cd %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%

@echo BFX_BUILD           = %BFX_BUILD%
@echo BIOS_SIZE_OPTION    = %BIOS_SIZE_OPTION%
@echo EDK2_MASTER_BUILD   = %EDK2_MASTER_BUILD%
@echo TARGET              = %TARGET%
@echo FSP_BUILD_PARAMETER = %FSP_BUILD_PARAMETER%
@echo FSP_BINARY_BUILD    = %FSP_BINARY_BUILD%
@echo FSP_TEST_RELEASE    = %FSP_TEST_RELEASE%
@echo BUILD_X64           = %BUILD_X64%
@echo EHL_BUILD           = %EHL_BUILD%
@echo EHL_Z0_BUILD        = %EHL_Z0_BUILD%
@echo PERFORMANCE_BUILD   = %PERFORMANCE_BUILD%
@echo BUILD_OPTION_PCD    = %BUILD_OPTION_PCD%

