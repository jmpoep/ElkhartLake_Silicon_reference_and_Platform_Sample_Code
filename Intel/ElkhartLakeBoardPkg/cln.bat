@REM @file
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2017 - 2018 Intel Corporation.
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

@echo off
echo.
echo Run build cleanall...
echo.

set "BUILD_OPTION_PCD="
set "FSP_BUILD_OPTION_PCD="

pushd ..\..\

if not defined WORKSPACE set WORKSPACE=%CD%
@REM
@REM In order to avoid dual backslash marks, remove the ending backslash mark for file path concatenation.
@REM
if %WORKSPACE:~-1%==\ (
  set WORKSPACE_ROOT=%WORKSPACE:~0,-1%
) else (
  set WORKSPACE_ROOT=%WORKSPACE%
)
if not defined WORKSPACE_CORE set WORKSPACE_CORE=%WORKSPACE_ROOT%\Edk2
if not defined WORKSPACE_COMMON set WORKSPACE_COMMON=%WORKSPACE_ROOT%\Intel
if not defined WORKSPACE_PLATFORM set WORKSPACE_PLATFORM=%WORKSPACE_ROOT%\Intel
if not defined WORKSPACE_SILICON set WORKSPACE_SILICON=%WORKSPACE_ROOT%\Intel

REM build cleanall

echo.
echo Directories to clean...
echo.

if exist %WORKSPACE%\Build rmdir /q /s %WORKSPACE%\Build
if exist %WORKSPACE%\Conf\.cache rmdir /q /s %WORKSPACE%\Conf\.cache
if exist %WORKSPACE%\RomImages rmdir /q /s %WORKSPACE%\RomImages
if exist %WORKSPACE%\BaseToolsTmp rmdir /q /s %WORKSPACE%\BaseToolsTmp

echo.
echo Files to clean...
echo.

if exist %WORKSPACE_ROOT%\edk2.log del %WORKSPACE_ROOT%\edk2.log
if exist %WORKSPACE_ROOT%\Conf\build_rule.txt del %WORKSPACE_ROOT%\Conf\build_rule.txt
if exist %WORKSPACE_ROOT%\Conf\FrameworkDatabase.db del %WORKSPACE_ROOT%\Conf\FrameworkDatabase.db
if exist %WORKSPACE_ROOT%\Conf\target.txt del %WORKSPACE_ROOT%\Conf\target.txt
if exist %WORKSPACE_ROOT%\Conf\tools_def.txt del %WORKSPACE_ROOT%\Conf\tools_def.txt
if exist %WORKSPACE_SILICON%\ClientOneSiliconPkg\SiPkg.dec del %WORKSPACE_SILICON%\ClientOneSiliconPkg\SiPkg.dec
@REM
@REM *.c.c is generated by Catalog Debug feature across code tree.
@REM
del /s *.c.c > nul 2>&1

popd

del /f /q Prep.log > nul 2>&1
del /f /q ..\Build.log > nul 2>&1
del /f /q ..\AslAnalyze*.log > nul 2>&1
del /f /q %WORKSPACE%\*.log > nul 2>&1

echo.
echo All done...
echo.
@echo on