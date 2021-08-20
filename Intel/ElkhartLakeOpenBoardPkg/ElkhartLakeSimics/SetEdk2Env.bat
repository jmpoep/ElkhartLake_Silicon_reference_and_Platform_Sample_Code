@REM @file
@REM
@REM Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
@REM This program and the accompanying materials
@REM are licensed and made available under the terms and conditions of the BSD License
@REM which accompanies this distribution.  The full text of the license may be found at
@REM http://opensource.org/licenses/bsd-license.php
@REM
@REM THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
@REM WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
@REM

@echo off

pushd ..\..\..\

@REM Set WORKSPACE environment.
@REM %__CD__% appends a backslash to every directory, not just the root as %CD% does
@REM This allows directory concatenation when the workspace is a drive root
@set WORKSPACE=%__CD__%.
echo.
echo Set WORKSPACE as: %WORKSPACE%
echo.

@REM Create the Conf directory under WORKSPACE
if not exist %WORKSPACE%\Conf (
  mkdir Conf
)

popd

set WORKSPACE_PLATFORM=%WORKSPACE%\Intel
set WORKSPACE_SILICON=%WORKSPACE%\Intel
set WORKSPACE_COMMON=%WORKSPACE%\Intel
set WORKSPACE_PLATFORM_BIN=%WORKSPACE%\Intel
set WORKSPACE_SILICON_BIN=%WORKSPACE%\Intel
set WORKSPACE_FSP_BIN=%WORKSPACE%\Intel
set WORKSPACE_CORE=%WORKSPACE%\Edk2
set WORKSPACE_CORE_PLATFORM=%WORKSPACE%\Edk2Platforms\Platform\Intel
set EDK_TOOLS_BIN=%WORKSPACE_CORE%\BaseTools\Bin\Win32
set EDK_TOOLS_PATH=%WORKSPACE_CORE%\BaseTools
set PACKAGES_PATH=%WORKSPACE%;%WORKSPACE_CORE%;%WORKSPACE_COMMON%;%WORKSPACE_PLATFORM%;%WORKSPACE_SILICON%;%WORKSPACE_CORE_PLATFORM%

if not defined NASM_PREFIX set NASM_PREFIX=C:\nasm\
%NASM_PREFIX%\nasm.exe -v
if errorlevel 1 (
  @echo ERROR - NASM is not found at %NASM_PREFIX%
  exit \b 1
)

if not defined IASL_PREFIX set IASL_PREFIX=C:\ASL\
%IASL_PREFIX%\iasl.exe -v
if errorlevel 1 (
  @echo ERROR - IASL is not found at %IASL_PREFIX%
  exit \b 1
)

set PYTHON_HOME=C:\Python27
set Path=%PYTHON_HOME%;%PATH%
python -V
if errorlevel 1 (
  @echo ERROR - Python is not found at %PYTHON_HOME%
  exit \b 1
)

if not exist %WORKSPACE%\Conf mkdir %WORKSPACE%\Conf

@echo Compile build tools provided by BaseTools
call %WORKSPACE_PLATFORM%\ElkhartLakeOpenBoardPkg\PrepareBaseTools.cmd

@echo on
