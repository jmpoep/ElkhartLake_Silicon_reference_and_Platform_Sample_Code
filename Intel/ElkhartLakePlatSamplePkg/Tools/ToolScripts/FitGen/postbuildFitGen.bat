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
@REM #    postbuildFitGen.bat
@REM #
@REM #  Abstract:
@REM #
@REM #    Post build FitGen script.
@REM #
@REM #--*/

@set SCRIPT_ERROR=0

@set BIOS_INFO_GUID=4A4CA1C6-871C-45bb-8801-6910A7AA5807
@set STARTUP_AC_MODULE_GUID=26fdaa3d-b7ed-4714-8509-eecf1593800d

@findstr %STARTUP_AC_MODULE_GUID% %BUILD_DIR%\FV\FvFwBinaries.inf > NUL

if errorlevel 1 goto NoStartupAcm
@set STARTUP_AC_PARA=-S %STARTUP_AC_MODULE_GUID%
:NoStartupAcm

copy %BUILD_DIR%\FV\ClientBios.fd %BUILD_DIR%\FV\ClientBios_ORG.fd /Y

%WORKSPACE_PLATFORM%\%BP_COMMON_PACKAGE%\Tools\FitGen\FitGen.exe -D %BUILD_DIR%\FV\ClientBios.fd %BUILD_DIR%\FV\ClientBios_FIT.fd -F 0x40 -NA -I %BIOS_INFO_GUID% %STARTUP_AC_PARA% -O 0x0C RESERVE 0x600 -O 0x0B RESERVE 0x400
@if errorlevel 1 (
  echo Error: ClientBios_FIT not found
  set SCRIPT_ERROR=1
  goto :EOF
)

@if not errorlevel 1 (
  @REM Work around to incorporate Bootguard ACM since fit gen does not support new header structure
  @if "%TargetOption%" == "" (
    @echo TargetOption is not found!
    @set SCRIPT_ERROR=1
    goto :EOF
  ) else (
    @if not /I "%TargetOption%" == "ehl" (
      echo Using KBL ACM
      copy %BUILD_DIR%\FV\ClientBios_FIT.fd %BUILD_DIR%\FV\CLIENTBIOS.fd /Y
    ) else (
      echo Using PO ACM
      %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\InternalOnly\Tools\BootGuard\anc_bios_gen.exe -b %BUILD_DIR%\FV\ClientBios_FIT.fd -a  %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\Binaries\BootGuard\ACM\StartupAcm.bin -o %BUILD_DIR%\FV\ClientBios_FIT_PO.fd
      copy %BUILD_DIR%\FV\ClientBios_FIT_PO.fd %BUILD_DIR%\FV\ClientBios_FIT.fd /Y
    )
  )
)


@set STARTUP_AC_MODULE_GUID=
@set BIOS_INFO_GUID=
@set STARTUP_AC_PARA=