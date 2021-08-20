@REM @file
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2016 Intel Corporation.
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
@REM #    Rsa2048Sha256SignPlatform.bat
@REM #
@REM #  Abstract:
@REM #
@REM #    Rsa2048Sha256SignPlatform script.
@REM #
@REM #--*/

@echo off
@setlocal

@echo %1
@echo %2
@echo %3
@echo %4

@if "%1"=="" goto End

@if exist %WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\Tools\ToolScripts\SignFv\privkey.pem (
  set PRIVATE_KEY_PATH=%WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\Tools\ToolScripts\SignFv\privkey.pem
) else (
  set OPENSSL_PATH=%CD%
  set PRIVATE_KEY_PATH=%CD%\privkey.pem
)

Rsa2048Sha256Sign %1 %2 %3 %4 --private-key %PRIVATE_KEY_PATH%
@if errorlevel 1 (
  @exit /b 1
)

@echo on
:End
