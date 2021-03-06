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

@echo on

:CmdLineParse
if "" == "%1" (
  goto Continue
)else if "/r" == "%1" (
  set RELEASE=/r
) else (
  echo Invalid input arguments: %1
  echo.
)
SHIFT
goto CmdLineParse
:Continue

echo.
echo Run build cleanall...
echo.

pushd ..\..\..\

if not defined WORKSPACE set WORKSPACE=%__CD__%.
@REM if not defined WORKSPACE_ROOT set WORKSPACE_ROOT=%WORKSPACE%\..\..\..\
@echo Workspace: %WORKSPACE%
@REM @echo Workspace_Root: %WORKSPACE_ROOT%

REM build cleanall

echo.
echo Directories to clean...
echo.

if exist %WORKSPACE%\Build rmdir /q /s %WORKSPACE%\Build
if exist %WORKSPACE%\Conf\.cache rmdir /q /s %WORKSPACE%\Conf\.cache
if exist %WORKSPACE%\RomImages rmdir /q /s %WORKSPACE%\RomImages

echo.
echo Files to clean...
echo.

if exist %WORKSPACE%\edk2.log del %WORKSPACE%\edk2.log
if exist %WORKSPACE%\Conf\build_rule.txt del %WORKSPACE%\Conf\build_rule.txt
if exist %WORKSPACE%\Conf\FrameworkDatabase.db del %WORKSPACE%\Conf\FrameworkDatabase.db
if exist %WORKSPACE%\Conf\target.txt del %WORKSPACE%\Conf\target.txt
if exist %WORKSPACE%\Conf\tools_def.txt del %WORKSPACE%\Conf\tools_def.txt
@REM *.c.c is generated by Catalog Debug feature across code tree.
@REM
del /s *.c.c > nul 2>&1

popd

del /f /q Prep.log > nul 2>&1
del /f /q ..\Build.log > nul 2>&1

@REM !!!!!!!!!!!!!!!!!!!!!!
pushd ..\..\..\

@REM Copy IASL and NASM exe to Root Directory
if not exist C:\NASM (
  mkdir C:\NASM
  copy %WORKSPACE%\Intel\ClientCommonPkg\Tools\nasm\Win32\nasm.exe C:\NASM\ /y
)
if not exist C:\ASL (
  mkdir C:\ASL
  copy %WORKSPACE%\Intel\BpCommonPkg\Tools\Iasl\iasl.exe C:\ASL\ /y
)

@REM Copy and Run PrepareMinTree.bat
copy %WORKSPACE%\Intel\ElkhartLakeOpenBoardPkg\PackageToolInternalOnly\PrepareMinTree.bat %WORKSPACE% /y
call PrepareMinTree.bat %RELEASE%
popd

@REM !!!!!!!!!!!!!!!!!!!!!!

echo.
echo All done...
echo.
@echo on
