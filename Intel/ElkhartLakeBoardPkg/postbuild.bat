@REM @file
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

@REM #
@REM #  Module Name:
@REM #
@REM #    postbuild.bat
@REM #
@REM #  Abstract:
@REM #
@REM #    Post build script.
@REM #
@REM #--*/

echo on

@set SCRIPT_ERROR=0

@if not defined WORKSPACE (
  echo.
  echo !!! ERROR !!! WORKSPACE must be defined before executing postbuild.bat !!!
  echo.
  set SCRIPT_ERROR=1
  goto :EOF
)

@if not defined WORKSPACE_PLATFORM (
  echo.
  echo !!! ERROR !!! WORKSPACE_PLATFORM must be defined before executing postbuild.bat !!!
  echo.
  set SCRIPT_ERROR=1
  goto :EOF
)

pushd %WORKSPACE%

@if not %CD% == %WORKSPACE% (
  echo.
  echo !!! ERROR !!! postbuild.bat is not executed under %WORKSPACE%
  echo.
  set SCRIPT_ERROR=1
  goto :EOF
)

@REM 
@REM Search FV for FMMT usage
@REM 
@set FVPREMEMORY_FOUND_FLAG=FALSE

%WORKSPACE_COMMON%\%BP_COMMON_PACKAGE%\Tools\FMMT\FMMT.exe -v %BUILD_DIR%\FV\ClientBios.fd > Fvlist.txt
@findstr "ObbDigest FV" Fvlist.txt > Fvlist2.txt

@for /F "tokens=*" %%A in (Fvlist2.txt) do @call :ProcessLine %%A
@goto searchend

:ProcessLine

  @if %FVPREMEMORY_FOUND_FLAG%==TRUE exit /b 0
  @set var=%1 %2 %3
  @if NOT "%var%"=="%var:ObbDigest=%" (
    @echo Firmware volume is %FIRMWARE_VOLUME%
    @set FVPREMEMORY_FOUND_FLAG=TRUE
    @set FVPREMEMORY_FIRMWARE_VOLUME=%FIRMWARE_VOLUME%
  )
  @if NOT "%var%"=="%var:Child=%" (
    @echo "Found a child Firmware volume.: %4"
  ) else if NOT "%var%"=="%var:FV=%" (
    @echo "Found a new Firmware volume: %1"
    @set FIRMWARE_VOLUME=%1
  )

@exit /b 0
:searchend

@if exist Fvlist.txt del Fvlist.txt
@if exist Fvlist2.txt del Fvlist2.txt

@if "%FVPREMEMORY_FOUND_FLAG%" == "FALSE" (
  echo !!! ERROR !!! Could not find FVPREMEMORY
  set SCRIPT_ERROR=1
  goto :EOF
)

@echo FVPREMEMORY =  %FVPREMEMORY_FIRMWARE_VOLUME%


:SkipBiosKnobs


@REM
@REM Post-build FitGen
@REM
@set BIOS_INFO_GUID=4A4CA1C6-871C-45bb-8801-6910A7AA5807
@set STARTUP_AC_MODULE_GUID=26fdaa3d-b7ed-4714-8509-eecf1593800d

findstr %STARTUP_AC_MODULE_GUID% %BUILD_DIR%\FV\FvFwBinaries.inf > NUL
@if errorlevel 1 goto NoStartupAcm
set STARTUP_AC_PARA=-S %STARTUP_AC_MODULE_GUID%
:NoStartupAcm


@REM
@REM Run FCE tool to write default setup variable to FD image
@REM
@if %SETUP_ENABLE% EQU FALSE (
  goto NoSetup
)
copy /y %BUILD_DIR%\FV\ClientBios.fd %BUILD_DIR%\FV\ClientBios_FcePre.fd
REM Prepend FvSetupData to enable processing
copy /y /b %BUILD_DIR%\FV\FvSetupData.fv + %BUILD_DIR%\FV\ClientBios.fd %BUILD_DIR%\FV\ClientSetup_Pre.fd
@REM UQI 0006 005C 0078 0030 0034 0039 0046 is for PlatId question prompt (STR_PLATID_PROMPT) UQI string value.
@REM First 0006 is the length of string; Next six byte values are mapped to STR_PLATID_PROMPT string value (\x049F) defined in %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\Setup\UqiList.uni.
%WORKSPACE_PLATFORM%\%BP_COMMON_PACKAGE%\Tools\FCE\FCE.exe ^
read ^
-i %BUILD_DIR%\FV\ClientSetup_Pre.fd ^
0006 005C 0078 0030 0034 0039 0046 > %BUILD_DIR%\FV\ClientBios.fd.config
@if errorlevel 1 (
  set SCRIPT_ERROR=1
  goto EndPostBuild
)

REM Place FFS file in FvPreMemory
%WORKSPACE_PLATFORM%\%BP_COMMON_PACKAGE%\Tools\FCE\FCE.exe ^
update ^
-i %BUILD_DIR%\FV\ClientSetup_Pre.fd ^
-s %BUILD_DIR%\FV\ClientBios.fd.config ^
-o %BUILD_DIR%\FV\ClientSetup.fd ^
-g FC8FE6B5-CD9B-411E-BD8F-31824D0CDE3D ^
-a
@if errorlevel 1 (
  set SCRIPT_ERROR=1
  goto EndPostBuild
)
REM Strip FvSetupData back out of the image
split -f %BUILD_DIR%\FV\ClientSetup.fd -s 0x100000
@if errorlevel 1 (
  set SCRIPT_ERROR=1
  goto EndPostBuild
)
del %BUILD_DIR%\FV\ClientSetup.fd1
move /y %BUILD_DIR%\FV\ClientSetup.fd2 %BUILD_DIR%\FV\ClientBios_FcePost.fd

copy /y %BUILD_DIR%\FV\ClientBios_FcePost.fd %BUILD_DIR%\FV\ClientBios.fd

:NoSetup


@rem
@rem Calculate OBB HASH using SHA256 and store it in Bios ROM
@rem
@if %FSP_WRAPPER_BUILD% EQU TRUE (
  copy /y /b %WORKSPACE%\%BUILD_DIR%\FV\FVADVANCED.Fv + %WORKSPACE%\%BUILD_DIR%\FV\FVPOSTMEMORY.Fv + %WORKSPACE%\%BUILD_DIR%\FV\FVFSPS.Fv %WORKSPACE%\%BUILD_DIR%\FV\OBB.Fv
) else (
  copy /y /b %WORKSPACE%\%BUILD_DIR%\FV\FVADVANCED.Fv + %WORKSPACE%\%BUILD_DIR%\FV\FVPOSTMEMORY.Fv %WORKSPACE%\%BUILD_DIR%\FV\OBB.Fv
)
@set OBB_HASH_FILE_GUID=F57757FC-2603-404F-AAE2-34C6232388E8
@rem
@rem Calculate OBB.Fv SHA256 digest and replace DummySha256Digest.bin with it.
@rem
@call %OPENSSL_PATH%\openssl.exe dgst -binary -sha256 %WORKSPACE%\%BUILD_DIR%\FV\OBB.Fv > %WORKSPACE%\%BUILD_DIR%\FV\ObbDigest.bin
@rem
@rem Prepare ObbDigest.ffs
@rem
%EDK_TOOLS_BIN%\GenSec.exe -s EFI_SECTION_USER_INTERFACE -n "ObbDigest" -o %WORKSPACE%\%BUILD_DIR%\FV\ObbDigest.sec
%EDK_TOOLS_BIN%\GenSec.exe -s EFI_SECTION_RAW %WORKSPACE%\%BUILD_DIR%\FV\ObbDigest.bin -o %WORKSPACE%\%BUILD_DIR%\FV\ObbDigest.raw
%EDK_TOOLS_BIN%\GenFfs.exe -t EFI_FV_FILETYPE_FREEFORM -g %OBB_HASH_FILE_GUID% -o %WORKSPACE%\%BUILD_DIR%\FV\ObbDigest.ffs -i %WORKSPACE%\%BUILD_DIR%\FV\ObbDigest.raw -i %WORKSPACE%\%BUILD_DIR%\FV\ObbDigest.sec
@rem
@rem Replace ObbDigest.ffs in FvRecovery with the actual one
@rem

%WORKSPACE_COMMON%\%BP_COMMON_PACKAGE%\Tools\FMMT\FMMT.exe -r %WORKSPACE%\%BUILD_DIR%\FV\ClientBios.fd %FVPREMEMORY_FIRMWARE_VOLUME% ObbDigest %WORKSPACE%\%BUILD_DIR%\FV\ObbDigest.ffs %WORKSPACE%\%BUILD_DIR%\FV\ClientBiosObb.fd

@if not exist "%WORKSPACE%\%BUILD_DIR%\FV\ClientBiosObb.fd" (
  @echo !!! ERROR:Build Fail !!
  @echo *** %WORKSPACE%\%BUILD_DIR%\FV\ClientBios1.fd does not exist. ***
  @echo -- FMMT insertion process may have failed, please check logs above --
  @set SCRIPT_ERROR=1
  @goto :EOF
)
move /y %WORKSPACE%\%BUILD_DIR%\FV\ClientBiosObb.fd %WORKSPACE%\%BUILD_DIR%\FV\ClientBios.fd


@REM
@REM Run FitGen tool to generate FIT
@REM
copy %BUILD_DIR%\FV\ClientBios.fd %BUILD_DIR%\FV\ClientBios_FitPre.fd /Y

%WORKSPACE_PLATFORM%\%BP_COMMON_PACKAGE%\Tools\FitGen\FitGen.exe ^
-D ^
%BUILD_DIR%\FV\ClientBios.fd ^
%BUILD_DIR%\FV\ClientBios.fd ^
-F 0x40 ^
-NA ^
-I %BIOS_INFO_GUID% ^
%STARTUP_AC_PARA% ^
-O 0x0C RESERVE 0x600 ^
-O 0x0B RESERVE 0x400

@ if errorlevel 1 (
  echo Error: FitGen failure
  set SCRIPT_ERROR=1
  goto EndPostBuild
)

:SkipGenFitTable

@if exist %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\InternalOnly\ToolScripts\KeyEnroll\MsEnrollRestricted.bat (
  call %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\InternalOnly\ToolScripts\KeyEnroll\MsEnrollRestricted.bat %WORKSPACE_ROOT%\%BUILD_DIR%
)


@REM
REM Remove MinPlatformPkg module instances that are overridden in ElkhartLakeBoardPkg
@REM
copy %BUILD_DIR%\FV\ClientBios.fd %BUILD_DIR%\FV\ClientBios_FmmtPre.fd /Y

@set MODULE_REMOVER_CMD=py -3 %WORKSPACE_PLATFORM%\%PLATFORM_BOARD_PACKAGE%\module_remover.py
@set FMMT_PATH=%WORKSPACE_COMMON%\%BP_COMMON_PACKAGE%\Tools\FMMT\FMMT.exe

@set MODULE_LIST=Tcg2ConfigPei Tcg2Pei

%MODULE_REMOVER_CMD% %FMMT_PATH% %BUILD_DIR%\FV\ClientBios.fd %MODULE_LIST%
@if %errorlevel% NEQ 0 (
  @echo Failure in running FMMT by module remover.
  set SCRIPT_ERROR=1
  goto EndPostBuild
)



@REM
@echo Build Production BIOS
@REM
@if %STARTUP_ACM_ENABLE% EQU FALSE (
  goto :NoAcm
)

@rem
@rem Re-sign again with above output ClientBios_acn_pre.fd
@rem
if exist %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\Tools\ToolScripts\BpmGen\postbuildBpmGen.bat (
  call %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\Tools\ToolScripts\BpmGen\postbuildBpmGen.bat ClientBios ClientBios
  if %SCRIPT_ERROR% NEQ 0 goto :NoAcm
)

:NoAcm


@echo ---Create ROM and Simics images---
call %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\Tools\RomImage\SetupRomDirs.bat

@echo Copy FSP header to RomImages
@if %FSP_WRAPPER_BUILD% EQU TRUE (
  copy /y /b %WORKSPACE%\%BUILD_FSP_DIR%\FV\*.h %WORKSPACE%\RomImages\Fsp\Include
)



:EndPostBuild
@set STARTUP_AC_MODULE_GUID=
@set BIOS_INFO_GUID=
@set STARTUP_AC_PARA=
@popd
