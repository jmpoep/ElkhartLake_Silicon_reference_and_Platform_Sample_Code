@REM @file
@REM Capsule build script.
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2016 - 2019 Intel Corporation.
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

@set CAPSULE_PREP_FLAG=c
@set BIOS_ROM_BUILD_TYPE=DEBUG
@set BUILD_MONOLITHIC_CAPSULE=TRUE
@set BUILD_BFX_CAPSULE=FALSE
@set BUILD_TENMB_CAPSULE=FALSE
@set BUILD_BIOS_CAPSULE=FALSE
@set BUILD_ME_CAPSULE=FALSE
@set BUILD_ISH_PDT_CAPSULE=FALSE
@set BIOS_MAJOR_VERSION=
@set BIOS_MINOR_VERSION=
@set BIOS_VERSION_DEC=
@set ME_BUILD_VERSION=
@set INI_TEMPLATE_FILE=BiosUpdateConfigSpi.ini

:CmdLineParse
@if "" == "%1" (
  goto Continue
)else if /I "help" == "%1" (
  goto CapsuleHelp
)else if /I "BFX" == "%1" (
  set BUILD_BFX_CAPSULE=TRUE
  set INI_TEMPLATE_FILE=BiosUpdateConfigUfs.ini
)else if /I "tenmb" == "%1" (
  set BUILD_TENMB_CAPSULE=TRUE
  set INI_TEMPLATE_FILE=BiosUpdateConfigSpi10Mb.ini
)else if /I "all" == "%1" (
  set BUILD_MONOLITHIC_CAPSULE=TRUE
  set BUILD_BIOS_CAPSULE=TRUE
  set BUILD_ME_CAPSULE=TRUE
  set BUILD_ISH_PDT_CAPSULE=TRUE
)else if /I "bios" == "%1" (
  set BUILD_MONOLITHIC_CAPSULE=FALSE
  set BUILD_BIOS_CAPSULE=TRUE
)else if /I "me" == "%1" (
  set BUILD_MONOLITHIC_CAPSULE=FALSE
  set BUILD_ME_CAPSULE=TRUE
)else if /I "ishpdt" == "%1" (
  set BUILD_MONOLITHIC_CAPSULE=FALSE
  set BUILD_ISH_PDT_CAPSULE=TRUE
)else if /I "-mever" == "%1" (
  set ME_BUILD_VERSION=%2
  SHIFT
)else (
  echo.
  echo Invalid input arguments: %1
  echo.
  goto CapsulePrepFail
)

SHIFT
goto CmdLineParse

:Continue
cd ../ElkhartLakeBoardPkg
@call prep.bat %CAPSULE_PREP_FLAG%
@If %SCRIPT_ERROR% EQU 1 goto CapsulePrepFail

@cd %WORKSPACE%


@REM
@REM Define environment variables for Capsule build usage
@REM
set CAPSULE_UPDATE_TOOL_PATH=%WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\Features\CapsuleUpdate\Tools
set CAPSULE_UPDATE_CONFIG_PATH=%WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\CapsuleUpdateConfig
set BIOS_ROM_FILE=%CAPSULE_UPDATE_CONFIG_PATH%\ClientBios.rom
set ME_BIN_FILE=%CAPSULE_UPDATE_CONFIG_PATH%\Me.bin
set PDT_BIN_FILE=%CAPSULE_UPDATE_CONFIG_PATH%\Pdt.bin
set CAPSULE_OUTPUT_PATH=%CAPSULE_UPDATE_CONFIG_PATH%\CapsuleOutput
set BIOS_ID_FILE=%CAPSULE_UPDATE_CONFIG_PATH%\biosid.env
set CAPSULE_BUILD_RESULT=%CAPSULE_OUTPUT_PATH%\result.log

@if not exist %CAPSULE_OUTPUT_PATH% mkdir %CAPSULE_OUTPUT_PATH%
@del %CAPSULE_BUILD_RESULT% 1>NUL 2>&1

@REM
@REM Check binaries before building Capsules
@REM

:CheckMeImage
@REM Skip checking ME image if it's not requested.
@if "%BUILD_ME_CAPSULE%" == "FALSE"  (
  goto CheckBiosImage
)

@if not defined ME_BUILD_VERSION (
  @echo.
  @echo !! ME build version is not assigned via -mever argument
  @goto CapsuleNotBuilt
)

@REM Check if inputting ME build version is valid
echo %ME_BUILD_VERSION:~-4% | FINDSTR /R "[0-9][0-9][0-9][0-9]" 1>NUL
@if errorlevel 1 (
  @echo.
  @echo !! ME Build version is invalid.
  @goto CapsuleNotBuilt
)

@if not exist %ME_BIN_FILE% (
  @echo.
  @echo !! ME binary does not exist.
  @goto CapsuleNotBuilt
)

@REM Check ME BIN: If file exists, does not have $DUM signature
FINDSTR "$DUM" %ME_BIN_FILE% 1>NUL
@if not errorlevel 1 (
  @echo.
  @echo !! ME binary is a dummy one.
  @goto CapsuleNotBuilt
)

:CheckBiosImage
@REM Skip checking BIOS image if it's not requested.
if "%BUILD_MONOLITHIC_CAPSULE%" == "TRUE" goto GenBiosUpdateImage
if "%BUILD_BIOS_CAPSULE%" == "TRUE" goto GenBiosUpdateImage
goto SkipGenBiosUpdateImage

:GenBiosUpdateImage
@REM Check BIOS ROM: If file exists and has $IBIOSI$ signature
@if not exist %BIOS_ROM_FILE% (
  @echo.
  @echo !! BIOS ROM does not exist.
  @goto CapsuleNotBuilt
)

@REM 1. Get BIOS Major version, Minor verison and Build Target
@del %BIOS_ID_FILE% 1>NUL 2>&1
@python %CAPSULE_UPDATE_TOOL_PATH%\GetFwVersionFromBin\GetBiosIdFromBin.py %BIOS_ROM_FILE% %BIOS_ID_FILE%
@if errorlevel 1 (
  @echo.
  @echo !! Failed to get BIOS information from BIOS ROM.
  @goto CapsuleNotBuilt
)

@for /f "usebackq tokens=3" %%i in (`FINDSTR /b /c:"VERSION_MAJOR" %BIOS_ID_FILE%`) do (
   @for /f "usebackq tokens=3" %%j in (`FINDSTR /b /c:"VERSION_MINOR" %BIOS_ID_FILE%`) do (
     @for /f "usebackq tokens=3" %%k in (`FINDSTR /b /c:"BUILD_TARGET" %BIOS_ID_FILE%`) do (
      @set BIOS_MAJOR_VERSION=%%i
      @set BIOS_MINOR_VERSION=%%j
      @set BIOS_ROM_BUILD_TYPE=%%k
    )
  )
)
@del %BIOS_ID_FILE% 1>NUL 2>&1

@REM
@REM Combine major and minor version to a single BIOS FW version
@REM Format: MMMMmm (M: major version, m: minor version). e.g., 2413.01 -> 241301
@REM
set "BIOS_MINOR_VERSION=00%BIOS_MINOR_VERSION%"
set BIOS_VERSION_DEC=%BIOS_MAJOR_VERSION:~-4%%BIOS_MINOR_VERSION:~-2%

@REM 2. Generate ClientBios_Ft.rom/BiosUpdate.ini/BiosBgup.bin
@REM@if "%BUILD_BFX_CAPSULE%" == "FALSE" (
@call %CAPSULE_UPDATE_TOOL_PATH%\GenBiosUpdateImages\GenBiosUpdateImages.bat ^
                                                        %BIOS_ROM_FILE% ^
                                                        %BIOS_ROM_BUILD_TYPE% ^
                                                        %CAPSULE_UPDATE_CONFIG_PATH% ^
                                                        %INI_TEMPLATE_FILE%

@if errorlevel 1 (
  @echo.
  @echo !! Failed to generate BIOS update image from BIOS ROM.
  @goto CapsuleNotBuilt
)
@REM)

:SkipGenBiosUpdateImage

@REM
@REM Start building Capsule
@REM
@if "%BUILD_MONOLITHIC_CAPSULE%" == "TRUE" (
  @goto BuildMonolithicCapsule
) else (
  @goto BuildStandaloneCapsules
)

@REM ===================================================
@REM =             Build Monolithic Capsule            =
@REM ===================================================
:BuildMonolithicCapsule
@REM Clean directories and files from the previous output
@if exist %WORKSPACE%\Conf\.cache rmdir /q /s %WORKSPACE%\Conf\.cache
@if exist %WORKSPACE%\%BUILD_DIR%\FV rmdir /q /s %WORKSPACE%\%BUILD_DIR%\FV

@REM 1. Build Monolithic FMP FV Payload
call genfds ^
       -f %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\CapsulePkg.fdf ^
       -p %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\CapsulePkg.dsc ^
       -i CapsulePayloadMonolithic ^
       -D BFX_CAPSULE=%BUILD_BFX_CAPSULE% ^
       -D TENMB_CAPSULE=%BUILD_TENMB_CAPSULE%

@if errorlevel 1 (
  @echo.
  @echo !! Error when generating Monolithic FMP FV Payload
  goto CapsuleNotBuilt
)

@REM 2. Generate Monolithic FMP Capsule
@cd %CAPSULE_UPDATE_TOOL_PATH%\GenerateCapsule
@call GenCapsuleSysFwMonolithic.bat ^
        %WORKSPACE%\%BUILD_DIR%\FV\CAPSULEPAYLOADMONOLITHIC.Fv ^
        %BIOS_VERSION_DEC% ^
        %CAPSULE_OUTPUT_PATH%

@if errorlevel 1 (
  @echo.
  @echo !! Error when generating Monolithic capsule
  goto CapsuleNotBuilt
)

@REM Write to build result
set CAPSULE_OUTPUT_NAME=EhlSystemFwMono_%BIOS_VERSION_DEC%.Cap
if exist %CAPSULE_OUTPUT_PATH%\%CAPSULE_OUTPUT_NAME% (
  @echo Monolithic Capsule %CAPSULE_OUTPUT_NAME% is generated in >> %CAPSULE_BUILD_RESULT%
  @echo   %CAPSULE_OUTPUT_PATH% >> %CAPSULE_BUILD_RESULT%
  @echo. >> %CAPSULE_BUILD_RESULT%
)

:BuildStandaloneCapsules
@REM
@REM Build Standalone Capsules
@REM
:BuildBiosCapsule
@REM ===================================================
@REM =            Build BIOS Capsule                   =
@REM ===================================================
@REM Skip building standalone BIOS Capsule if it's not requested.
@if "%BUILD_BIOS_CAPSULE%" == "FALSE"  (
  goto BuildMeCapsule
)

@REM Clean directories and files from the previous output
if exist %WORKSPACE%\Conf\.cache rmdir /q /s %WORKSPACE%\Conf\.cache
if exist %WORKSPACE%\%BUILD_DIR%\FV rmdir /q /s %WORKSPACE%\%BUILD_DIR%\FV

@REM 1. Build BIOS FMP FV Payload
call genfds ^
       -f %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\CapsulePkg.fdf ^
       -p %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\CapsulePkg.dsc ^
       -i CapsulePayloadBios ^
       -D BFX_CAPSULE=%BUILD_BFX_CAPSULE% ^
       -D TENMB_CAPSULE=%BUILD_TENMB_CAPSULE%

@if errorlevel 1 (
  @echo.
  @echo !! Error when generating BIOS FMP FV Payload
  goto CapsuleNotBuilt
)

@REM 2. Generate BIOS FMP Capsule
@cd %CAPSULE_UPDATE_TOOL_PATH%\GenerateCapsule
@call GenCapsuleSysFwBios.bat ^
        %WORKSPACE%\%BUILD_DIR%\FV\CAPSULEPAYLOADBIOS.Fv ^
        %BIOS_VERSION_DEC% ^
        %CAPSULE_OUTPUT_PATH%

@if errorlevel 1 (
  @echo.
  @echo !! Error when generating BIOS capsule
  goto CapsuleNotBuilt
)

@REM Write to build result
set CAPSULE_OUTPUT_NAME=EhlSystemFwBios_%BIOS_VERSION_DEC%.Cap
if exist %CAPSULE_OUTPUT_PATH%\%CAPSULE_OUTPUT_NAME% (
  @echo Standalone BIOS Capsule %CAPSULE_OUTPUT_NAME% is generated in >> %CAPSULE_BUILD_RESULT%
  @echo   %CAPSULE_OUTPUT_PATH% >> %CAPSULE_BUILD_RESULT%
  @echo. >> %CAPSULE_BUILD_RESULT%
)

:BuildMeCapsule
@REM ===================================================
@REM =            Build ME Capsule                     =
@REM ===================================================
@REM Skip building standalone ME Capsule if it's not requested.
@if "%BUILD_ME_CAPSULE%" == "FALSE"  (
  goto EndOfBuildingCapsule
)

@REM Generate ME FMP Capsule
@cd %CAPSULE_UPDATE_TOOL_PATH%\GenerateCapsule
@call GenCapsuleSysFwMe.bat ^
        %ME_BIN_FILE% ^
        %ME_BUILD_VERSION:~-4% ^
        %CAPSULE_OUTPUT_PATH%

@if errorlevel 1 (
  @echo.
  @echo !! Error when generating ME capsule
  goto CapsuleNotBuilt
)

@REM Write to build result
set CAPSULE_OUTPUT_NAME=EhlSystemFwMe_%ME_BUILD_VERSION:~-4%.Cap
if exist %CAPSULE_OUTPUT_PATH%\%CAPSULE_OUTPUT_NAME% (
  @echo Standalone ME Capsule %CAPSULE_OUTPUT_NAME% is generated in >> %CAPSULE_BUILD_RESULT%
  @echo   %CAPSULE_OUTPUT_PATH% >> %CAPSULE_BUILD_RESULT%
  @echo. >> %CAPSULE_BUILD_RESULT%
)

:EndOfBuildingCapsule
@echo.
@echo.
@echo.
if exist %CAPSULE_BUILD_RESULT% (
  type %CAPSULE_BUILD_RESULT%
  @del %CAPSULE_BUILD_RESULT% 1>NUL 2>&1
)
@echo.
@echo Capsule build is completed.
@echo.
goto CapsuleBuildDone

@REM
@REM ============ Error handle ============
@REM
:CapsulePrepFail
@echo.
@echo !! The Capsule build has failed in prep phase!
@echo.
@goto CapsuleHelp

:CapsuleNotBuilt
@echo.
@echo !! CapsuleBuild failed.
@echo.

:CapsuleHelp
@echo.
@echo Build Capsules based on the binaries in CapsuleUpdateConfig
@echo Find more details in CapsuleUpdateConfig\ReadMe.txt
@echo.
@echo capsulebuild [BIOS type:SPI/BFX][target:all/bios/me][-mever ^<ME Build Version^>][help]
@echo.
@echo   BIOS type   BIOS type to build capsule: SPI/BFX.
@echo.
@echo               default: If BIOS type is NOT assigned, BIOS rom file is SPI rom.
@echo                        Buid SPI capsule.
@echo               BFX    : BIOS rom file is BFX rom. Buid BFX capsule.
@echo.
@echo   target   Assign Capsule build target: all/bios/me
@echo.
@echo            default: If target is NOT assigned, build Monolithic Capsule
@echo                     (A single capsule covers BIOS+ME+...)
@echo            all    : Build Monolithic Capsule + all standalone Capsules
@echo            bios   : Build Standalone BIOS Capsule
@echo            me     : Build Standalone ME Capsule
@echo.
@echo   -mever   To indicate ME Build version of CapsuleUpdateConfig\Me.bin.
@echo            It's mandatory if building capsules with [all] or [me] target
@echo            e.g., "capsulebuild.bat me -mever 1033"
@echo.
@echo   Note: As of now we dont have the knowledge to parse ME version from
@echo         a given ME FW image.
@echo         So ME version needs to be provided manually by the user.
@echo.
@echo   Examples:
@echo      a. capsulebuild.bat
@echo           Build a Monolithic capsule. (default build)
@echo           EhlSystemFwMono_xxxx.cap would be observed in CapsuleOutput directory.
@echo      b. capsulebuild.bat bios me -mever 1033
@echo           Build both standalone ME capsule and BIOS capsule.
@echo           1033 indicates ME build verion of Me.bin
@echo           EhlSystemFwMe_1033.cap and EhlSystemFwBios_xxxx.cap would be observed
@echo           in CapsuleOutput directory.
@echo.
@goto CapsuleBuildDone

:CapsuleBuildDone
@if defined WORKSPACE_PLATFORM (
  if defined PLATFORM_FULL_PACKAGE (
    @cd %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%
  )
)
