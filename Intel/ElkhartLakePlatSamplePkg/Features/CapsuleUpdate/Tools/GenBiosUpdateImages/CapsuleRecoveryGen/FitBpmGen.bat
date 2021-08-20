@REM @file
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2018 Intel Corporation.
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
@REM #    FitBpmGen.bat.bat
@REM #
@REM #  Abstract:
@REM #
@REM #    BpmGen script to resign FV for TopSwap case
@REM #
@REM #--*/

@set SCRIPT_ERROR=0

@set BIOS_INFO_GUID=230F6679-F703-4DC2-B2B7-41C670BCC0D1
@REM NEM_DATA_SIZE should match PcdTemporaryRamSize value
@set KM_REVOCATION=0
@set KM_ID=0x01

@set STARTUP_AC_MODULE_GUID=26fdaa3d-b7ed-4714-8509-eecf1593800d

REM *****************
REM  Do FIT gen
REM *****************

REM :StartupAcmFound
@set STARTUP_AC_PARA=-S %STARTUP_AC_MODULE_GUID%
REM :NoStartupAcm

REM Generate new Fit table---
%WORKSPACE_PLATFORM%\%BP_COMMON_PACKAGE%\Tools\FitGen\FitGen.exe -D %SPLIT_ROM_WORKING_PATH%\merge.bin %SPLIT_ROM_WORKING_PATH%\CleanFit.fd -F 0x40 -CLEAR >%SPLIT_ROM_WORKING_PATH%\cleanFIT.txt
%WORKSPACE_PLATFORM%\%BP_COMMON_PACKAGE%\Tools\FitGen\FitGen.exe -D %SPLIT_ROM_WORKING_PATH%\CleanFit.fd %SPLIT_ROM_WORKING_PATH%\NewFit.fd -F 0x40 -NA -I %BIOS_INFO_GUID% %STARTUP_AC_PARA% -O 0x0C RESERVE 0x600 -O 0x0B RESERVE 0x400 >%SPLIT_ROM_WORKING_PATH%\newFIT.txt

echo %BIOS_INFO_GUID%
echo %STARTUP_AC_MODULE_GUID%


@if errorlevel 1 (
  echo Error: NewFit not found
  set SCRIPT_ERROR=1
  goto :EOF
)


REM *****************
REM  Do BPM
REM *****************

cd %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\Tools\ToolScripts\BpmGen

echo "#### BpmGen2:  Generating KeyManifest.bin ####"
pushd .
echo %CD%
cd %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\Tools\ToolScripts\BpmGen
echo %CD%
%WORKSPACE_PLATFORM%\ClientCommonPkg\Tools\BpmGen2\BpmGen2.exe KMGEN -KEY bpm_pubkey.pem SHA384 BPM -KM %SPLIT_ROM_WORKING_PATH%\KeyManifest.bin -SIGHASHALG SHA384 -SIGNKEY oem_privkey.pem -SIGNPUBKEY oem_pubkey.pem -KMID %KM_ID% -KMKHASH SHA384 -SVN %KM_REVOCATION% -d:2 >%SPLIT_ROM_WORKING_PATH%\bpmgen2_km.txt


@if %ERRORLEVEL% NEQ 0 (
  popd
  echo "#### Error generating KM file #####"
  set SCRIPT_ERROR=1
  goto :EOF
)
echo "#### BpmGen2:  Generating Manifest.bin ####"
@if "%BFX_BUILD%" == "TRUE" (
%WORKSPACE_PLATFORM%\ClientCommonPkg\Tools\BpmGen2\BpmGen2.exe GEN %SPLIT_ROM_WORKING_PATH%\NewFit.fd bpmgen2_BFX.params -BPM %SPLIT_ROM_WORKING_PATH%\Manifest.bin -U %SPLIT_ROM_WORKING_PATH%\Bpm.bin -KM %SPLIT_ROM_WORKING_PATH%\KeyManifest.bin -block -d:2 >%SPLIT_ROM_WORKING_PATH%\bpmgen2_bpm.txt
) else (
%WORKSPACE_PLATFORM%\ClientCommonPkg\Tools\BpmGen2\BpmGen2.exe GEN %SPLIT_ROM_WORKING_PATH%\NewFit.fd bpmgen2.params -BPM %SPLIT_ROM_WORKING_PATH%\Manifest.bin -U %SPLIT_ROM_WORKING_PATH%\Bpm.bin -KM %SPLIT_ROM_WORKING_PATH%\KeyManifest.bin -d:2 >%SPLIT_ROM_WORKING_PATH%\bpmgen2_bpm.txt
)
@if %ERRORLEVEL% NEQ 0 (
  popd
  echo "#### Error generating BPM file #####"
  set SCRIPT_ERROR=1
  goto :EOF
)
popd
echo %CD%


@cd %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%

@set BIOS_INFO_GUID=
@set KM_REVOCATION=
@set KM_ID=

@set STARTUP_AC_MODULE_GUID=
@set STARTUP_AC_PARA=
