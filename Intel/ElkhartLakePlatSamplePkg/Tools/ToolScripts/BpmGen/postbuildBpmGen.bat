@REM @file
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2010 - 2019 Intel Corporation.
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
@REM #    postbuildBpmGen.bat
@REM #
@REM #  Abstract:
@REM #
@REM #    Post build BpmGen script.
@REM #
@REM #--*/

@set SCRIPT_ERROR=0

@set BIOS_INFO_GUID=4A4CA1C6-871C-45bb-8801-6910A7AA5807
@REM NEM_DATA_SIZE should match PcdTemporaryRamSize value
@set KM_REVOCATION=0
@set KM_ID=0x01


echo "#### BpmGen2:  Generating KeyManifest.bin ####"
pushd .
echo %CD%
cd %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\Tools\ToolScripts\BpmGen
echo %CD%
%WORKSPACE_PLATFORM%\ClientCommonPkg\Tools\BpmGen2\BpmGen2.exe KMGEN -KEY bpm_pubkey.pem SHA384 BPM -KM %WORKSPACE%\%BUILD_DIR%\FV\KeyManifest.bin -SIGHASHALG SHA384 -SIGNKEY oem_privkey.pem -SIGNPUBKEY oem_pubkey.pem -KMID %KM_ID% -KMKHASH SHA384 -SVN %KM_REVOCATION% -d:2 >bpmgen2_km.txt
@if %ERRORLEVEL% NEQ 0 (
  popd
  echo "#### Error generating KM file #####"
  set SCRIPT_ERROR=1
  goto :EOF
)
echo "#### BpmGen2:  Generating Manifest.bin ####"
@if "%BFX_BUILD%" == "TRUE" (
%WORKSPACE_PLATFORM%\ClientCommonPkg\Tools\BpmGen2\BpmGen2.exe GEN %WORKSPACE%\%BUILD_DIR%\FV\%1.fd bpmgen2_BFX.params -BPM %WORKSPACE%\%BUILD_DIR%\FV\Manifest.bin -U %WORKSPACE%\%BUILD_DIR%\FV\%1_MBIOS.fd -KM %WORKSPACE%\%BUILD_DIR%\FV\KeyManifest.bin -block -d:2 >bpmgen2_bpm.txt
) else (
%WORKSPACE_PLATFORM%\ClientCommonPkg\Tools\BpmGen2\BpmGen2.exe GEN %WORKSPACE%\%BUILD_DIR%\FV\%1.fd bpmgen2.params -BPM %WORKSPACE%\%BUILD_DIR%\FV\Manifest.bin -U %WORKSPACE%\%BUILD_DIR%\FV\%1_MBIOS.fd -KM %WORKSPACE%\%BUILD_DIR%\FV\KeyManifest.bin -d:2 >bpmgen2_bpm.txt
)
@if %ERRORLEVEL% NEQ 0 (
  popd
  echo "#### Error generating BPM file #####"
  set SCRIPT_ERROR=1
  goto :EOF
)
popd
echo %CD%


copy %BUILD_DIR%\FV\%1_MBIOS.fd %BUILD_DIR%\FV\%2.fd /Y

@set BIOS_INFO_GUID=
@set KM_REVOCATION=
@set KM_ID=
