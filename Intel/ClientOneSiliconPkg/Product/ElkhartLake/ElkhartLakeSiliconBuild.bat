@REM @file
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
@REM  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
@REM  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
@REM  the terms of your license agreement with Intel or your vendor. This file may
@REM  be modified by the user, subject to additional terms of the license agreement.
@REM
@REM @par Specification
@REM

set WORKSPACE=%CD%
set WORKSPACE_CORE=%WORKSPACE%\Edk2
set WORKSPACE_CORE_SILICON=%WORKSPACE%\Edk2Platforms\Silicon\Intel
set WORKSPACE_COMMON=%WORKSPACE%\Intel
set WORKSPACE_SILICON_RELATIVE=Intel
set WORKSPACE_SILICON=%WORKSPACE%\%WORKSPACE_SILICON_RELATIVE%
set WORKSPACE_PLATFORM=%WORKSPACE%\Intel
set PACKAGES_PATH=%WORKSPACE%;%WORKSPACE_CORE_SILICON%;%WORKSPACE_CORE%;%WORKSPACE_COMMON%;%WORKSPACE_SILICON%;%WORKSPACE_PLATFORM%
set EDK_TOOLS_PATH=%WORKSPACE_CORE%\BaseTools
set EDK_TOOLS_BIN=%WORKSPACE_CORE%\BaseTools\Bin\Win32
set PYTHON_HOME=C:\Python27

@if not exist %WORKSPACE%\Conf mkdir %WORKSPACE%\Conf
pushd %WORKSPACE_SILICON%\ClientOneSiliconPkg
python gen_dec.py SiPkg.dec.template ElkhartLake
popd

@if not exist %WORKSPACE_SILICON%\ClientOneSiliconPkg\SiPkg.dec (
  @echo "Error: SiPkg.dec does not exists"
  @exit /b 1
)

@call %WORKSPACE_CORE%\edksetup.bat Rebuild
@REM Below definitions are example paths to link16.exe, nasm.exe and iasl.exe build tools.
@REM Customers may define their own paths.
@if not defined WINDDK3790_PREFIX_EXT (
  @set WINDDK3790_PREFIX_EXT=%WORKSPACE_COMMON%\ClientCommonPkg\Tools\
)
@set WINDDK3790_PREFIX=%WINDDK3790_PREFIX_EXT%
@if not defined NASM_PREFIX_EXT (
  @set NASM_PREFIX_EXT=%WORKSPACE_COMMON%\ClientCommonPkg\Tools\nasm\Win32\
)
@set NASM_PREFIX=%NASM_PREFIX_EXT%
@if not defined IASL_PREFIX_EXT (
  @set IASL_PREFIX_EXT=%WORKSPACE_PLATFORM%\ElkhartLakePlatSamplePkg\Tools\Iasl\
)
@set IASL_PREFIX=%IASL_PREFIX_EXT%

@if not defined TOOL_CHAIN_TAG (
  if defined VS140COMNTOOLS (
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
)

set TARGET=RELEASE

@echo.
@echo Set build environment.
@echo.
@if not exist Build\ClientOneSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG% (
  mkdir Build\ClientOneSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%
)


@findstr /V "ACTIVE_PLATFORM TARGET TARGET_ARCH TOOL_CHAIN_TAG BUILD_RULE_CONF" %WORKSPACE%\Conf\target.txt > Build\ClientOneSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@echo ACTIVE_PLATFORM = %WORKSPACE_SILICON_RELATIVE%/ClientOneSiliconPkg/Product/ElkhartLake/ElkhartLakeSiliconPkg.dsc  >> Build\ClientOneSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@echo TARGET          = %TARGET%                                                                  >> Build\ClientOneSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@echo TARGET_ARCH     = IA32 X64                                                                  >> Build\ClientOneSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@echo TOOL_CHAIN_TAG  = %TOOL_CHAIN_TAG%                                                          >> Build\ClientOneSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@echo BUILD_RULE_CONF = %WORKSPACE%\Conf\build_rule.txt                                           >> Build\ClientOneSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@move /Y Build\ClientOneSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt %WORKSPACE%\Conf

call build
