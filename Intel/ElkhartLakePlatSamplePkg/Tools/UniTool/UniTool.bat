@REM @file
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2016 - 2018 Intel Corporation.
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

rem UniTool v1.8
rem Syntax: UniTool.exe [-b] [-u] [-l] [-x] 'rootDirectory' 'uqiFile' ['excludedDirectory1'] ['excludedDirectory2']
rem
rem Function will sync up UQI definitions with unicode files in the tree.
rem
rem Required Arguments:
rem   'rootdirectory'       path to root directory (EFI_SOURCE)
rem   'uqiFileDirectory'    path to UQI file
rem
rem Options:
rem   -h                    Show this help
rem   -b                    Build option prints an error if a UQI duplicated or if a new UQI needs assigning
rem   -u                    Update UQI values to setup strings based on vfi/vfrs
rem                         NOTE: 'uqiFile' cannot be readonly!
rem   -l                    Language deletion option (keeps only eng and uqi) moves all UQIs to 'uqiFile'
rem                         NOTE: Unicode files cannot be readonly!
rem   -x                    Excludes 'rootDirectory''excludedDirectory1' & 'rootDirectory''excludedDirectory2' from UQI list build.
rem                         NOTE: Cannot be the same as rootDirectory
rem                         NOTE: Defaults to 'rootDirectory'\Restricted if unspecified
rem
rem Options must be specified before path

@echo on

@rem
@rem  - Non-restricted items: %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\Setup\UqiList.uni
@rem
@rem  Scan non-restricted items using "%WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%" as root.
@rem
@if exist %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\Setup\UqiList.uni attrib -r %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\Setup\UqiList.uni
%WORKSPACE_COMMON%\BpCommonPkg\Tools\UniTool\UniTool.exe -b -u %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE% %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\Setup\UqiList.uni
@if not %errorlevel%==0 goto Error


goto Done

:Error
set NMAKE_ERROR=1
exit /b 1

:Done
