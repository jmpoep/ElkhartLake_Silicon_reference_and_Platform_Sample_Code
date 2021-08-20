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

@echo off

pushd ..\..\

@REM Set WORKSPACE environment.
@REM %__CD__% appends a backslash to every directory, not just the root as %CD% does
@REM This allows directory concatenation when the workspace is a drive root
@set WORKSPACE=%__CD__%
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
set WORKSPACE_CORE_SILICON=%WORKSPACE%\Edk2Platforms\Silicon\Intel
set EDK_TOOLS_BIN=%WORKSPACE_CORE%\BaseTools\Bin\Win32
set EDK_TOOLS_PATH=%WORKSPACE_CORE%\BaseTools
set PACKAGES_PATH=%WORKSPACE%;%WORKSPACE_CORE_SILICON%;%WORKSPACE_CORE%;%WORKSPACE_COMMON%;%WORKSPACE_PLATFORM%;%WORKSPACE_SILICON%;%WORKSPACE_CORE_PLATFORM%
set COMMON_TOOLS_PATH=%WORKSPACE%\Intel\ClientCommonPkg\Tools
set SCRIPT_ERROR=0

set NASM_PREFIX=%COMMON_TOOLS_PATH%\nasm\Win32\
%NASM_PREFIX%\nasm.exe -v
if errorlevel 1 (
  @echo ERROR - NASM is not found at %NASM_PREFIX%
  set SCRIPT_ERROR=1
)

set IASL_PREFIX=%WORKSPACE_PLATFORM%\ElkhartLakePlatSamplePkg\Tools\Iasl\
%IASL_PREFIX%\iasl.exe -v
if errorlevel 1 (
  @echo ERROR - IASL is not found at %IASL_PREFIX%
  set SCRIPT_ERROR=1
)

set PYTHON_HOME=C:\Python27
set Path=%PYTHON_HOME%;%PATH%
python -V
if errorlevel 1 (
  @echo ERROR - Python is not found at %PYTHON_HOME%
  set SCRIPT_ERROR=1
)

@echo on
