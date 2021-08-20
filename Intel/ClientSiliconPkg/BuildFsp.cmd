@REM Copyright (c) 2013 - 2019, Intel Corporation. All rights reserved.
@REM This software and associated documentation (if any) is furnished
@REM under a license and may only be used or copied in accordance
@REM with the terms of the license. Except as permitted by such
@REM license, no part of this software or documentation may be
@REM reproduced, stored in a retrieval system, or transmitted in any
@REM form or by any means without the express written consent of
@REM Intel Corporation.

@echo off

if "%~1" == "/?" goto USAGE
if "%~1" == "/h" goto USAGE


setlocal enableextensions enabledelayedexpansion
set BUILD_ARGS=%*
@if not defined WORKSPACE (
  set WORKSPACE=%CD%
)
@if not defined WORKSPACE_CORE (
  set WORKSPACE_CORE=%WORKSPACE%\Edk2
)
@if not defined WORKSPACE_CORE_SILICON (
  set WORKSPACE_CORE_SILICON=%WORKSPACE%\Edk2Platforms\Silicon\Intel
)
@if not defined WORKSPACE_CORE_PLATFORM (
  set WORKSPACE_CORE_PLATFORM=%WORKSPACE%\Edk2Platforms\Platform\Intel
)
@if not defined WORKSPACE_COMMON (
  set WORKSPACE_COMMON=%WORKSPACE%\Intel
)
@if not defined WORKSPACE_SILICON (
  set WORKSPACE_SILICON=%WORKSPACE%\Intel
)
@if not defined NASM_PREFIX_EXT (
  echo NASM_PREFIX_EXT not defined, Default path set to "%WORKSPACE_COMMON%\ClientCommonPkg\Tools\nasm\Win32\"
  @set NASM_PREFIX_EXT=%WORKSPACE_COMMON%\ClientCommonPkg\Tools\nasm\Win32\
)
@set NASM_PREFIX=%NASM_PREFIX_EXT%

@if not defined PACKAGES_PATH (
  set PACKAGES_PATH=%WORKSPACE%;%WORKSPACE_COMMON%;%WORKSPACE_SILICON%;%WORKSPACE_CORE_SILICON%;%WORKSPACE_CORE_PLATFORM%;%WORKSPACE_CORE%
)
set EDK_TOOLS_PATH=%WORKSPACE_CORE%\BaseTools
set EDK_TOOLS_BIN=%WORKSPACE_CORE%\BaseTools\Bin\Win32
set PYTHON_HOME=C:\Python27

@if not exist %WORKSPACE%\Conf mkdir %WORKSPACE%\Conf

rem Perform pre-build
rem -----------------

set DEFAULT_TARGET_FILE=CurrentTarget.txt
  rem Check the first command line parameter for a package name
  rem ---------------------------------------------------------
  if not "%~1" == "" (
    set FIRSTCHAR=%1
    set FIRSTCHAR=!FIRSTCHAR:~0,1!
    if not "!FIRSTCHAR!" == "/" (
      rem First argument is a package name.
      call :UPDATE_DEFAULT_TARGET %~1
      if not !ERRORLEVEL! == 0 goto DIE
      shift
      )
    set FIRSTCHAR=
  )

  rem Check for default target file
  rem -----------------------------
  if not exist %DEFAULT_TARGET_FILE% (
    echo ERROR: Please specify a package to build.
    echo.
    call :USAGE
    goto DIE
    )

  rem Remove shifted arguments by reconstructing BUILD_ARGS
  rem -----------------------------------------------------
  set BUILD_ARGS=
  :CONSTRUCT_BUILD_ARGS_LOOP
    if "%~1"=="" goto CONSTRUCT_BUILD_ARGS_CONTINUE
    set BUILD_ARGS=%BUILD_ARGS% %1
    shift
    goto CONSTRUCT_BUILD_ARGS_LOOP
  :CONSTRUCT_BUILD_ARGS_CONTINUE

  call :PREBUILD
  if not %ERRORLEVEL% == 0 goto DIE

  rem Build package
  rem -------------
  rem Find build script.
  set /p BUILD_TARGET=<%DEFAULT_TARGET_FILE%
  set BUILD_TARGET=%WORKSPACE_SILICON%\%BUILD_TARGET%FspPkg\BuildFv.cmd
  if not exist %BUILD_TARGET% (
    echo ERROR: Unable to find '%BUILD_TARGET%'.
    goto DIE
    )
  call %BUILD_TARGET% %BUILD_ARGS%
  if not %ERRORLEVEL% == 0 goto DIE

  rem Perform post-build
  rem ------------------
  call :POSTBUILD %BUILD_ARGS%
  if not %ERRORLEVEL% == 0 goto DIE

  rem Done
  rem ----
  goto END

:UPDATE_DEFAULT_TARGET
rem ---------------------------------------------------------------------------
rem Update the default target
rem ---------------------------------------------------------------------------
  set TARGET=%~1

  rem Store target for later
  echo Setting default target to '%TARGET%'.
  echo %TARGET%>%DEFAULT_TARGET_FILE%
  set TARGET=

  goto END

:POSTBUILD
rem ---------------------------------------------------------------------------
rem Perform post-build actions
rem ---------------------------------------------------------------------------
  rem echo Performing post-build actions.
  rem
  if /I "%1"=="/clean" goto END
  echo Copy Fsp images to RomImages\Fsp

  set FSP_FD_NAME=%TARGET%FSP.fd

  if not exist %WORKSPACE%\RomImages\Fsp @mkdir %WORKSPACE%\RomImages\Fsp
  if not exist %WORKSPACE%\RomImages\Fsp\Include @mkdir %WORKSPACE%\RomImages\Fsp\Include
  copy /y /b %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_FD_NAME% %WORKSPACE%\RomImages\Fsp\FSP.fd
  rem Do binary copy for bsf file to avoid extra characters copy, which causes issue with BCT tool
  copy /y /b %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\*.bsf %WORKSPACE%\RomImages\Fsp\FSP.bsf
  copy /y %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Docs\FspApi.chm %WORKSPACE%\RomImages\Fsp\

  echo - PostBuild Done -
  goto END

:PREBUILD
call %WORKSPACE_CORE%\edksetup.bat Rebuild

@REM
@REM Check for Python support
@REM
set PYTHON_MIN_VERSION=(2,5)
call :FIND_PYTHON
if not %ERRORLEVEL% == 0 goto DIE

@REM
@REM Setup Visual Studio environment. Order of presedence is 2015, 2013, 2012, 2010 and then 2008.
@REM
@REM NOTE: To override presedence set TOOL_CHAIN_TAG before calling.
@REM       Example: set TOOL_CHAIN_TAG=VS2008
@REM

@REM Check if tool chain has not been selected and Visual Studio 2015 is installed.
@if not defined TOOL_CHAIN_TAG (
  if defined VS140COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2015
  )
)

@REM If Visual Studio 2015 is selected by priority or by preference, setup the environment variables.
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

@REM Check if tool chain has not been selected and Visual Studio 2013 is installed.
@if not defined TOOL_CHAIN_TAG (
  if defined VS120COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2013
  )
)

@REM If Visual Studio 2013 is selected by priority or by preference, setup the environment variables.
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

@REM If no supported version of Visual Studio was detected, return an error.
@if not defined TOOL_CHAIN_TAG (
  echo.
  echo !!! ERROR !!! Visual Studio not installed correctly!!!
  echo.
  exit /b 1
)

  goto END

:FIND_PYTHON
rem ---------------------------------------------------------------------------
rem Looks for Python installed on the system.
rem ---------------------------------------------------------------------------
  set PYTHON_DEF_EXE=python.exe
  set PYTHON_EXE=
  set PYTHON_DIR=
  set PYTHON_FOUND_IN_PATH=0

  rem Check the standard installation location for Python 2.7
  if exist C:\Python27\%PYTHON_DEF_EXE% (
    set PYTHON_EXE=C:\Python27\%PYTHON_DEF_EXE%
    )
  if defined PYTHON_EXE goto FIND_PYTHON_FOUND

  rem Check the standard installation location for Python 2.6
  if exist C:\Python26\%PYTHON_DEF_EXE% (
    set PYTHON_EXE=C:\Python26\%PYTHON_DEF_EXE%
    )
  if defined PYTHON_EXE goto FIND_PYTHON_FOUND

  rem Check the standard installation location for Python 2.5
  if exist C:\Python25\%PYTHON_DEF_EXE% (
    set PYTHON_EXE=C:\Python25\%PYTHON_DEF_EXE%
    )
  if defined PYTHON_EXE goto FIND_PYTHON_FOUND

  rem Check the PATH environment variable
  for %%X in (%PYTHON_DEF_EXE%) do (set PYTHON_EXE=%%~$PATH:X)
  if defined PYTHON_EXE (
    set PYTHON_FOUND_IN_PATH=1
    goto FIND_PYTHON_FOUND
    )

  rem Python not found
  echo Error: %PYTHON_DEF_EXE% could not be located on this system. If^
  Python has been installed to a nonstandard location (the typical installation^
  location is C:\Python25\%PYTHON_DEF_EXE%), ensure that the directory^
  containing the Python executable has been added to the PATH environment^
  variable.
   call :FIND_PYTHON_CLEANUP
  goto DIE

  :FIND_PYTHON_FOUND
  echo Python was found at '%PYTHON_EXE%'.
  call :PYTHON_VERSION_TEST "%PYTHON_EXE%" "%PYTHON_MIN_VERSION%"
  if not %ERRORLEVEL% == 0 (
  echo Error: The version of Python installed on this system at^
  '%PYTHON_EXE%' is too old to run necessary scripts. Please upgrade^
  your Python installation to version !PYTHON_MIN_VERSION! or newer.
    call :FIND_PYTHON_CLEANUP
    goto DIE
    )

  rem Add Python to the PATH if necessary
  if not %PYTHON_FOUND_IN_PATH% == 0 goto FIND_PYHTON_CLEANUP
  for %%X in (%PYTHON_EXE%) do set PYTHON_DIR=%%~pdX
  set PATH=%PATH%;%PYTHON_DIR%

  :FIND_PYTHON_CLEANUP
  set PYTHON_DEF_EXE=
  set PYTHON_DEF_DIR=
  set PYTHON_EXE=
  set PYTHON_DIR=
  set PYTHON_FOUND_IN_PATH=

  goto END

:PYTHON_VERSION_TEST
rem ---------------------------------------------------------------------------
rem Test the Python executable %1 for version >= %2.
rem ---------------------------------------------------------------------------
  %1 -c "import sys; sys.exit(sys.version_info<%~2)"
  if not %ERRORLEVEL% == 0 goto DIE
  goto END

:USAGE
rem ---------------------------------------------------------------------------
rem Print usage and exit
rem ---------------------------------------------------------------------------
  echo.
  echo ========================================================================
  echo = For backward compatibility following usage will still be supported   =
  echo = Usage: BuildFsp [package name]                                       =
  echo =                 [platform name (optional)]                           =
  echo =                 [/h or /? or /r or /d or /mr or /md or /clean]       =
  echo =                                                                      =
  echo =     Example build CoffeeLake form CannonLakeFspPkg:                  =
  echo =       .\Intel\ClientSiliconPkg\BuildFsp.cmd CannonLake CoffeeLake /d =
  echo =                                                                      =
  echo =     Example build CannonLake form CannonLakeFspPkg:                  =
  echo =       .\Intel\ClientSiliconPkg\BuildFsp.cmd CannonLake /d            =
  echo ========================================================================
  echo = By default BuildFsp assumes below paths when executing:            =
  echo =   \Edk2\                 : FSP required open source packages       =
  echo =   \Intel\                : Rest of the FSP required packages       =
  echo =   C:\Python27\python.exe : For supporting FSP build scripts        =
  echo =   nasm.exe               : Should be under NASM_PREFIX_EXT path    =
  echo ======================================================================
  goto END

:DIE
rem ---------------------------------------------------------------------------
rem Exit returning a failure error code
rem ---------------------------------------------------------------------------
  exit /B 1

:END
rem ---------------------------------------------------------------------------
rem Exit returning a success error code
rem ---------------------------------------------------------------------------
  exit /B 0
