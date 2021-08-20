@REM Copyright (c) 2017, Intel Corporation. All rights reserved.
@REM This software and associated documentation (if any) is furnished
@REM under a license and may only be used or copied in accordance
@REM with the terms of the license. Except as permitted by such
@REM license, no part of this software or documentation may be
@REM reproduced, stored in a retrieval system, or transmitted in any
@REM form or by any means without the express written consent of
@REM Intel Corporation.

@echo off

REM ---------------------------------------------------------------------------
REM Prepare Tools provided from Python script
REM ---------------------------------------------------------------------------

set PYTHON_HOME=C:\Python27

REM ---------------------------------------------------------------------------
REM Prepare workspace environment.
REM ---------------------------------------------------------------------------

setlocal EnableDelayedExpansion EnableExtensions

if defined WORKSPACE goto :WorkSpaceDefined
set LocationOfThisFile=%~dp0
set WORKSPACE=%LocationOfThisFile%..\..\

:WorkSpaceDefined
set WORKSPACE_CORE=%WORKSPACE%\Edk2
set WORKSPACE_COMMON=%WORKSPACE%\Intel
set WORKSPACE_PLATFORM=%WORKSPACE%\Intel
set WORKSPACE_SILICON=%WORKSPACE%\Intel
set BASE_TOOLS_PATH=%WORKSPACE_CORE%\BaseTools
set EDK_TOOLS_PATH=%WORKSPACE_CORE%\BaseTools
set EDK_TOOLS_BIN=%WORKSPACE_CORE%\BaseTools\Bin\Win32
set PATH=%EDK_TOOLS_BIN%;%PATH%

REM ---------------------------------------------------------------------------
REM Setup Visual Studio environment. Order of precedence is 2012, 2013, 2010 and then 2008.
REM
REM NOTE: To override precedence set TOOL_CHAIN_TAG before calling PrepareBaseTools.bat.
REM       Example: set TOOL_CHAIN_TAG=VS2008
REM ---------------------------------------------------------------------------

REM Check if tool chain has not been selected and Visual Studio 2014 is installed.
if not defined TOOL_CHAIN_TAG (
  if defined VS140COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2015
  )
)

REM If Visual Studio 2014 is selected by priority or by preference, setup the environment variables.
if /I "%TOOL_CHAIN_TAG%"=="VS2015" (
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

REM Check if tool chain has not been selected and Visual Studio 2013 is installed.
if not defined TOOL_CHAIN_TAG (
  if defined VS120COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2013
  )
)

REM If Visual Studio 2013 is selected by priority or by preference, setup the environment variables.
if /I "%TOOL_CHAIN_TAG%"=="VS2013" (
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

REM Check if tool chain has not been selected and Visual Studio 2012 is installed.
if not defined TOOL_CHAIN_TAG (
  if defined VS110COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2012
  )
)

REM If Visual Studio 2012 is selected by priority or by preference, setup the environment variables.
if /I "%TOOL_CHAIN_TAG%"=="VS2012" (
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

REM Check if tool chain has not been selected and Visual Studio 2010 is installed.
if not defined TOOL_CHAIN_TAG (
  if defined VS100COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2010
  )
)

REM If Visual Studio 2010 is selected by priority or by preference, setup the environment variables.
if /I "%TOOL_CHAIN_TAG%"=="VS2010" (
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

REM Check if tool chain has not been selected and Visual Studio 2008 is installed.
if not defined TOOL_CHAIN_TAG (
  if defined VS90COMNTOOLS (
    set TOOL_CHAIN_TAG=VS2008
  )
)

REM If Visual Studio 2008 is selected by priority or by preference, setup the environment variables.
if /I "%TOOL_CHAIN_TAG%"=="VS2008" (
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

REM If no supported version of Visual Studio was detected, return an error.
if not defined TOOL_CHAIN_TAG (
  echo.
  echo !!! ERROR !!! Visual Studio not installed correctly!!!
  echo.
  set SCRIPT_ERROR=1
  goto :End
)

echo Show CL revision
cl

REM ---------------------------------------------------------------------------
REM Building Tools from C source code, will take around 30 seconds.
REM ---------------------------------------------------------------------------

if not exist %EDK_TOOLS_BIN% (
  mkdir %EDK_TOOLS_BIN%
)

pushd .
cd %EDK_TOOLS_PATH%
nmake -f Makefile c
popd

:END
endlocal

