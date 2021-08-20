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

@echo off
set CLIENT_SILICON_PKG_NAME=ClientSiliconPkg
set FSP_PKG_NAME=ElkhartLakeFspPkg
set FSP_BIN_PKG_NAME=ElkhartLakeFspBinPkg

@REM
@REM Parse input parameters
@REM
@set FspTargetOption=
@set BuildTypeFSP=
@set CatalogOption=
:ArgParse
if /I "%1" == "" (
  goto Continue
) else if /I "%1" == "/h" (
  goto Usage
) else if /I "%1" == "/?" (
  goto Usage
) else if /I "%1" == "/clean" (
  goto Clean
) else if /I "%1" == "/r" (
  @set BuildTypeFSP=/r
) else if /I "%1" == "/tr" (
  @set BuildTypeFSP=/tr
) else if /I "%1" == "/rp" (
  @set BuildTypeFSP=/rp
) else if /I "%1" == "/d" (
  @set BuildTypeFSP=/d
) else if /I "%1" == "/catalog" (
  @set CatalogOption=/catalog
) else if /I "%1" == "IceLake" (
  @set FspTargetOption=IceLake
) else if /I "%1" == "ElkhartLakeZ0" (
  @set FspTargetOption=ElkhartLakeZ0
)
@shift
goto ArgParse

:Continue
@REM
@REM If any target option is not specified, ElkhartLake build by default
@REM
@if /I "%FspTargetOption%" == ""  set FspTargetOption=ElkhartLake

@if not exist %WORKSPACE%\Conf mkdir %WORKSPACE%\Conf
@if exist %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Override\BaseTools\Conf\tools_def.template (
  copy %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Override\BaseTools\Conf\tools_def.template %WORKSPACE%\Conf\tools_def.txt /Y
  )
@if exist %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Override\BaseTools\Conf\build_rule.template (
  copy %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Override\BaseTools\Conf\build_rule.template %WORKSPACE%\Conf\build_rule.txt /Y
  )

echo Get UTC time as build time.
set GET_TIME_COMMAND=python %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Tools\GetUtcDateTime\GetUtcDateTime.py
for /f %%a in ('%GET_TIME_COMMAND% --year') do set YYYY=%%a
for /f %%b in ('%GET_TIME_COMMAND% --date') do set MMDD=%%b
for /f %%c in ('%GET_TIME_COMMAND% --time') do set HHmm=%%c

echo %YYYY%
echo %MMDD%
echo %HHmm%
@echo off
set OUT_DIR=%WORKSPACE%\Build

pushd %WORKSPACE_SILICON%\%FSP_PKG_NAME%

@if /I "%FspTargetOption%" == "ElkhartLake" (
  @REM Default ElkhartLake build
  set FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlCpuEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlPchEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdIclCpuEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdIclPchEnable=FALSE

  @echo Target CPU is %FspTargetOption%. Build on %FSP_PKG_NAME%
  @echo Target PCH is %FspTargetOption%. Build on %FSP_PKG_NAME%
)

@if /I "%FspTargetOption%" == "ElkhartLakeZ0" (
  @REM Default ElkhartLake build
  set FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlCpuEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdEhlPchEnable=FALSE ^
--pcd gSiPkgTokenSpaceGuid.PcdIclCpuEnable=TRUE ^
--pcd gSiPkgTokenSpaceGuid.PcdIclPchEnable=TRUE

  @echo Target CPU is %FspTargetOption%. Build on %FSP_PKG_NAME%
  @echo Target PCH is %FspTargetOption%. Build on %FSP_PKG_NAME%
)
popd

@REM
@REM Generating SiPkg DEC
@REM
@echo Generating SiPkg DEC ....
pushd %WORKSPACE_SILICON%\ClientOneSiliconPkg
@if not exist SiPkg.dec.template (
   echo Error: SiPkg.dec Template not found. Halting build...
   goto :PreBuildFail
)
@if /I "%FspTargetOption%" == "IceLake" (
   @REM You chose IceLake build option
   python gen_dec.py SiPkg.dec.template IceLake
   @echo Switching SiPkg DEC file to IceLake
) else if /I "%FspTargetOption%" == "ElkhartLakeZ0" (
   @REM You chose ElkhartLakeZ0 build option
   python gen_dec.py SiPkg.dec.template ElkhartLakeZ0
   @echo Switching SiPkg DEC file to ElkhartLakeZ0
) else (
   @REM Default ElkhartLake build
   python gen_dec.py SiPkg.dec.template ElkhartLake
   @echo Switching SiPkg DEC file to ElkhartLake
)
@echo %WORKSPACE_SILICON%\ClientOneSiliconPkg\SiPkg.dec generation completed.
@echo .
popd

if /I "%CatalogOption%" == "/catalog"  (
  @if exist c:\python27 (
    set PYTHON_DIR=c:\python27
  ) else (
    echo.
    echo !!! ERROR !!! Catalog feature requirement issue: Python27 is not found under C:\Python27.
    echo.
    goto :PreBuildFail
  )

  @if exist %WORKSPACE_COMMON%\ClientSiliconPkg\Tools\Catalog\CatalogEncoder.py (
    set CATALOG_ENCODER=%WORKSPACE_COMMON%\ClientSiliconPkg\Tools\Catalog\CatalogEncoder.py
  ) else (
    echo.
    echo !!! ERROR !!! Catalog feature requirement issue: CatalogEncoder.py is not found.
    echo.
    goto :PreBuildFail
  )

  @if exist %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Tools\Catalog\build_rule.template_Catalog (
    copy %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Tools\Catalog\build_rule.template_Catalog %WORKSPACE%\Conf\build_rule.txt /Y
  ) else (
    echo.
    echo !!! ERROR !!! Catalog feature requirement issue: Updated Build Rule is not found.
    echo.
    goto :PreBuildFail
  )

  set NUMBER_OF_BUILD_PROCESSORS=1
)

if /I "%BuildTypeFSP%"=="/r" goto ReleaseBuild
if /I "%BuildTypeFSP%"=="/tr" goto ReleaseTypeTest
if /I "%BuildTypeFSP%"=="/rp" goto ReleaseBuildPdb
if /I "%BuildTypeFSP%"=="/d" goto DebugBuild
if /I "%BuildTypeFSP%"=="" (
  goto DebugBuild
) else (
  echo.
  echo  ERROR: %BuildTypeFSP% is not valid parameter.
  goto Usage
)


:Clean
echo Removing Build and Conf directories ...
if exist %OUT_DIR% rmdir %OUT_DIR% /s /q
if exist %WORKSPACE%\Conf  rmdir %WORKSPACE%\Conf  /s /q
if exist *.log  del *.log /q /f
set WORKSPACE=
set EDK_TOOLS_PATH=
goto End


:ReleaseTypeTest
set  BD_TARGET=RELEASE
set  BD_MACRO=-D CFG_OUTDIR=%OUT_DIR% -D TARGET=%BD_TARGET% %EXT_BUILD_FLAGS%
set  BD_ARGS=-p %WORKSPACE_SILICON%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc -b RELEASE %BD_MACRO% -a IA32 -a X64 -n %NUMBER_OF_PROCESSORS% -t %TOOL_CHAIN_TAG% -y ReportRelease.log -Y PCD -Y LIBRARY %VAR_BUILD_FLAGS%
set  FSP_BUILD_TYPE=0x0001
set  FSP_RELEASE_TYPE=0x0000
goto Build

:ReleaseBuildPdb
set  FSP_BUILD_OPTION_PCD=%FSP_BUILD_OPTION_PCD% --pcd gElkhartLakeFspPkgTokenSpaceGuid.PcdSymbolInReleaseEnable=TRUE
set  BD_TARGET=RELEASE
set  BD_MACRO=-D CFG_OUTDIR=%OUT_DIR% -D TARGET=%BD_TARGET% %EXT_BUILD_FLAGS%
set  BD_ARGS=-p %WORKSPACE_SILICON%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc -b RELEASE %BD_MACRO% -a IA32 -a X64 -n %NUMBER_OF_PROCESSORS% -t %TOOL_CHAIN_TAG% -y ReportRelease.log -Y PCD -Y LIBRARY %VAR_BUILD_FLAGS%
set  FSP_BUILD_TYPE=0x0001
set  FSP_RELEASE_TYPE=0x0002
goto Build
:ReleaseBuild
set  BD_TARGET=RELEASE
set  BD_MACRO=-D CFG_OUTDIR=%OUT_DIR% -D TARGET=%BD_TARGET% %EXT_BUILD_FLAGS%
set  BD_ARGS=-p %WORKSPACE_SILICON%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc -b RELEASE %BD_MACRO% -a IA32 -a X64 -n %NUMBER_OF_PROCESSORS% -t %TOOL_CHAIN_TAG% -y ReportRelease.log -Y PCD -Y LIBRARY %VAR_BUILD_FLAGS%
set  FSP_BUILD_TYPE=0x0001
set  FSP_RELEASE_TYPE=0x0002
goto Build

:DebugBuild
set  BD_TARGET=DEBUG
set  BD_MACRO=-D CFG_OUTDIR=%OUT_DIR% -D TARGET=%BD_TARGET% %EXT_BUILD_FLAGS%
set  BD_ARGS=-p %WORKSPACE_SILICON%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc -b DEBUG  %BD_MACRO% -a IA32 -a X64 -n %NUMBER_OF_PROCESSORS% -t %TOOL_CHAIN_TAG% -y ReportDebug.log -Y PCD -Y LIBRARY %VAR_BUILD_FLAGS%
set  FSP_BUILD_TYPE=0x0000
set  FSP_RELEASE_TYPE=0x0000
goto Build

:Build
call build  -m %WORKSPACE_SILICON%\%FSP_PKG_NAME%\FspHeader\FspHeader.inf %BD_ARGS% %FSP_BUILD_OPTION_PCD%
if ERRORLEVEL 1 exit /b 1

call :PreBuild  CALL_RET
if "%CALL_RET%"=="1" exit /b 1
call build  %BD_ARGS% %FSP_BUILD_OPTION_PCD%
if ERRORLEVEL 1 exit /b 1
call :PostBuild
goto End

:Usage
echo. ================================================================
echo  Usage: "BuildFv.cmd [/h | /? | /r | /rp | /tr | /d | /clean | /catalog | Target Platform]"
echo
echo     Supported Target Platform :
echo     ElkhartLake
echo
echo     Note : ElkhartLake build by default if you don't put any Target Platform option.
echo     Example :
echo        - BuildFv.cmd ElkhartLake /r
echo
echo. ================================================================
exit /B 1

@REM :CopyBin
@REM @if exist %1\*.efi   xcopy %1\*.efi   %2 /D /U /Y > NUL
@REM @if exist %1\*.inf   xcopy %1\*.inf   %2 /D /U /Y > NUL
@REM @if exist %1\*.depex xcopy %1\*.depex %2 /D /U /Y > NUL
@REM goto:EOF

:PreBuild
echo Start of PreBuild ...

@if not exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include mkdir %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include

if exist %WORKSPACE_SILICON%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc attrib -r %WORKSPACE_SILICON%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc
set %~1=1
set FSP_T_UPD_GUID=34686CA3-34F9-4901-B82A-BA630F0714C6
set FSP_M_UPD_GUID=39A250DB-E465-4DD1-A2AC-E2BD3C0E2385
set FSP_S_UPD_GUID=CAE3605B-5B34-4C85-B3D7-27D54273C40F
python %WORKSPACE_CORE%\IntelFsp2Pkg\Tools\GenCfgOpt.py UPDTXT ^
     %WORKSPACE_SILICON%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc ^
     %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
     %BD_MACRO% %FSP_BUILD_OPTION_PCD%
if "%ERRORLEVEL%"=="256" (
  REM  DSC is not changed, no need to recreate MAP and BIN file
) else (
  if ERRORLEVEL 1 goto:PreBuildFail
  echo UPD TXT file was generated successfully !

  echo Generate VPD Header File ...
  del /Q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_T_UPD_GUID%.bin ^
            %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_T_UPD_GUID%.map 2>nul

  del /Q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_M_UPD_GUID%.bin ^
            %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_M_UPD_GUID%.map 2>nul

  del /Q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_S_UPD_GUID%.bin ^
            %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_S_UPD_GUID%.map 2>nul

  call BPDG ^
       %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_T_UPD_GUID%.txt ^
       -o %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_T_UPD_GUID%.bin ^
       -m %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_T_UPD_GUID%.map
  if ERRORLEVEL 1 goto:PreBuildFail

  call BPDG ^
       %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_M_UPD_GUID%.txt ^
       -o %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_M_UPD_GUID%.bin ^
       -m %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_M_UPD_GUID%.map
  if ERRORLEVEL 1 goto:PreBuildFail

  call BPDG ^
       %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_S_UPD_GUID%.txt ^
       -o %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_S_UPD_GUID%.bin ^
       -m %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_S_UPD_GUID%.map
  if ERRORLEVEL 1 goto:PreBuildFail
)

python %WORKSPACE_CORE%\IntelFsp2Pkg\Tools\GenCfgOpt.py HEADER ^
         %WORKSPACE_SILICON%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc ^
         %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
         %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\BootLoaderPlatformData.h ^
         %BD_MACRO% %FSP_BUILD_OPTION_PCD%
if "%ERRORLEVEL%"=="256" (
    REM  No need to recreate header file
) else (
    if ERRORLEVEL 1 goto:PreBuildFail
    echo Vpd header file was generated successfully !

    echo Generate BSF File ...

    if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Fsp.bsf attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Fsp.bsf
    python %WORKSPACE_CORE%\IntelFsp2Pkg\Tools\GenCfgOpt.py GENBSF ^
         %WORKSPACE_SILICON%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc ^
         %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
         %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Fsp.bsf ^
         %BD_MACRO% %FSP_BUILD_OPTION_PCD%

    if ERRORLEVEL 1 goto:PreBuildFail
    echo BSF file was generated successfully !
    if exist %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FspUpd.h attrib -r %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FspUpd.h
    if exist "%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspUpd.h" (
      copy /y %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspUpd.h %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FspUpd.h
      )
    if exist %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FsptUpd.h attrib -r %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FsptUpd.h
    if exist "%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FsptUpd.h" (
      copy /y %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FsptUpd.h %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FsptUpd.h
      )
    if exist %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FspmUpd.h attrib -r %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FspmUpd.h
    if exist "%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspmUpd.h" (
      copy /y %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspmUpd.h %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FspmUpd.h
      )
    if exist "%WORKSPACE_SILICON%\ClientOneSiliconPkg\SystemAgent\Include\MemInfoHob.h" (
      copy /y %WORKSPACE_SILICON%\ClientOneSiliconPkg\SystemAgent\Include\MemInfoHob.h %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\MemInfoHob.h
      )
    if exist %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FspsUpd.h attrib -r %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FspsUpd.h
    if exist "%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspsUpd.h" (
      copy /y %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspsUpd.h %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\FspsUpd.h
      )
)

:PreBuildRet
set %~1=0
echo End of PreBuild ...
echo.
goto:EOF

:PreBuildFail
del /q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspUpd.h
del /q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FsptUpd.h
del /q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspmUpd.h
del /q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspsUpd.h
echo.
(goto) 2>nul & endlocal & exit /b 1
goto:EOF

:PostBuild
echo Start of PostBuild ...

echo Patch FSP-T Image ...
@REM
@REM @todo Change FSP.fd to Fsp.fd
@REM
python %WORKSPACE_CORE%\IntelFsp2Pkg\Tools\PatchFv.py ^
     %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
     FSP-T:FSP  ^
     "0x0000,            _BASE_FSP-T_,                                                                                       @Temporary Base" ^
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-T Size" ^
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-T Base" ^
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-T Image Attribute" ^
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x1000 | %FSP_BUILD_TYPE% | %FSP_RELEASE_TYPE%,                @FSP-T Component Attribute" ^
     "<[0x0000]>+0x00B8, 70BCF6A5-FFB1-47D8-B1AE-EFE5508E23EA:0x1C - <[0x0000]>,                                             @FSP-T CFG Offset" ^
     "<[0x0000]>+0x00BC, [70BCF6A5-FFB1-47D8-B1AE-EFE5508E23EA:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-T CFG Size" ^
     "<[0x0000]>+0x00C4, FspSecCoreT:_TempRamInitApi - [0x0000],                                                             @TempRamInit API" ^
     "<[0x0000]>+0x00FC, 0x%YYYY%,                                                                                           @BuildTimeStamp" ^
     "<[0x0000]>+0x0100, 0x%MMDD%,                                                                                           @BuildTimeStamp" ^
     "<[0x0000]>+0x0104, 0x%HHmm%,                                                                                           @BuildTimeStamp" ^
     "0x0000,            0x00000000,                                                                                         @Restore the value" ^
     "FspSecCoreT:_FspInfoHeaderRelativeOff, FspSecCoreT:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-T Header Offset"^
     "FspSecCoreT:_SiFspInfoHeaderRelativeOff, FspSecCoreT:_SiAsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-T Header Offset"
if ERRORLEVEL 1 goto:PreBuildFail

echo Patch FSP-M Image ...
@REM
@REM @todo Change FSP.fd to Fsp.fd
@REM
python %WORKSPACE_CORE%\IntelFsp2Pkg\Tools\PatchFv.py ^
     %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
     FSP-M:FSP  ^
     "0x0000,            _BASE_FSP-M_,                                                                                       @Temporary Base" ^
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-M Size" ^
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-M Base" ^
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-M Image Attribute" ^
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x2000 | %FSP_BUILD_TYPE% | %FSP_RELEASE_TYPE%,                @FSP-M Component Attribute" ^
     "<[0x0000]>+0x00B8, D5B86AEA-6AF7-40D4-8014-982301BC3D89:0x1C - <[0x0000]>,                                             @FSP-M CFG Offset" ^
     "<[0x0000]>+0x00BC, [D5B86AEA-6AF7-40D4-8014-982301BC3D89:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-M CFG Size" ^
     "<[0x0000]>+0x00D0, FspSecCoreM:_FspMemoryInitApi - [0x0000],                                                           @MemoryInitApi API" ^
     "<[0x0000]>+0x00D4, FspSecCoreM:_TempRamExitApi - [0x0000],                                                             @TempRamExit API" ^
     "<[0x0000]>+0x00FC, 0x%YYYY%,                                                                                           @BuildTimeStamp" ^
     "<[0x0000]>+0x0100, 0x%MMDD%,                                                                                           @BuildTimeStamp" ^
     "<[0x0000]>+0x0104, 0x%HHmm%,                                                                                           @BuildTimeStamp" ^
     "FspSecCoreM:_FspPeiCoreEntryOff, PeiCore:__ModuleEntryPoint - [0x0000],                                                @PeiCore Entry" ^
     "0x0000,            0x00000000,                                                                                         @Restore the value" ^
     "FspSecCoreM:_FspInfoHeaderRelativeOff, FspSecCoreM:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-M Header Offset" ^
     "FspGlobalDataInitPei:_FspInfoHeaderRelativeOff, FspGlobalDataInitPei:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-M Header Offset"
if ERRORLEVEL 1 goto:PreBuildFail


echo Patch FSP-S Image ...
@REM
@REM @todo Change FSP.fd to Fsp.fd
@REM
python %WORKSPACE_CORE%\IntelFsp2Pkg\Tools\PatchFv.py ^
     %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
     FSP-S:FSP  ^
     "0x0000,            _BASE_FSP-S_,                                                                                       @Temporary Base" ^
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-S Size" ^
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-S Base" ^
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-S Image Attribute" ^
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x3000 | %FSP_BUILD_TYPE% | %FSP_RELEASE_TYPE%,                @FSP-S Component Attribute" ^
     "<[0x0000]>+0x00B8, E3CD9B18-998C-4F76-B65E-98B154E5446F:0x1C - <[0x0000]>,                                             @FSP-S CFG Offset" ^
     "<[0x0000]>+0x00BC, [E3CD9B18-998C-4F76-B65E-98B154E5446F:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-S CFG Size" ^
     "<[0x0000]>+0x00D8, FspSecCoreS:_FspSiliconInitApi - [0x0000],                                                          @SiliconInit API" ^
     "<[0x0000]>+0x00CC, FspSecCoreS:_NotifyPhaseApi - [0x0000],                                                             @NotifyPhase API" ^
     "<[0x0000]>+0x00FC, 0x%YYYY%,                                                                                           @BuildTimeStamp" ^
     "<[0x0000]>+0x0100, 0x%MMDD%,                                                                                           @BuildTimeStamp" ^
     "<[0x0000]>+0x0104, 0x%HHmm%,                                                                                           @BuildTimeStamp" ^
     "0x0000,            0x00000000,                                                                                         @Restore the value" ^
     "FspSecCoreS:_FspInfoHeaderRelativeOff, FspSecCoreS:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-S Header Offset"
if ERRORLEVEL 1 goto:PreBuildFail

@REM Copy FSP binary to ElkhartLakeFspBinPkg
echo on
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Fsp.bsf attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Fsp.bsf
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Fsp.fd attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Fsp.fd
copy /y %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FSP.fd %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Fsp.fd
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\FspUpd.h attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\FspUpd.h
if exist "%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspUpd.h" (
  copy /y %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspUpd.h %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\FsptUpd.h attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\FsptUpd.h
if exist "%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FsptUpd.h" (
  copy /y %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FsptUpd.h %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\FspmUpd.h attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\FspmUpd.h
if exist "%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspmUpd.h" (
  copy /y %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspmUpd.h %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\FspsUpd.h attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\FspsUpd.h
if exist "%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspsUpd.h" (
  copy /y %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspsUpd.h %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\MemInfoHob.h attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\MemInfoHob.h
if exist "%WORKSPACE_SILICON%\ClientOneSiliconPkg\SystemAgent\Include\MemInfoHob.h" (
  copy /y %WORKSPACE_SILICON%\ClientOneSiliconPkg\SystemAgent\Include\MemInfoHob.h %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\SmbiosCacheInfoHob.h attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\SmbiosCacheInfoHob.h
if exist "%WORKSPACE_COMMON%\ClientSiliconPkg\Include\SmbiosCacheInfoHob.h" (
  copy /y %WORKSPACE_COMMON%\ClientSiliconPkg\Include\SmbiosCacheInfoHob.h %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\SmbiosProcessorInfoHob.h attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\SmbiosProcessorInfoHob.h
if exist "%WORKSPACE_COMMON%\ClientSiliconPkg\Include\SmbiosProcessorInfoHob.h" (
  copy /y %WORKSPACE_COMMON%\ClientSiliconPkg\Include\SmbiosProcessorInfoHob.h %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\FirmwareVersionInfoHob.h attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\FirmwareVersionInfoHob.h
if exist "%WORKSPACE_COMMON%\ClientSiliconPkg\Include\FirmwareVersionInfoHob.h" (
  copy /y %WORKSPACE_COMMON%\ClientSiliconPkg\Include\FirmwareVersionInfoHob.h %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\HobUsageDataHob.h attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\HobUsageDataHob.h
if exist %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\HobUsageDataHob.h (
  copy /y %WORKSPACE_SILICON%\%FSP_PKG_NAME%\Include\HobUsageDataHob.h %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\CatalogDataBase.txt (
  copy /y %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\CatalogDataBase.txt %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\
  )
if exist %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\ElkhartLakeFspPcds.dsc attrib -r %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\ElkhartLakeFspPcds.dsc
if exist %WORKSPACE_SILICON%\%FSP_PKG_NAME%\ElkhartLakeFspPcds.dsc (
  copy /y %WORKSPACE_SILICON%\%FSP_PKG_NAME%\ElkhartLakeFspPcds.dsc %WORKSPACE_SILICON%\%FSP_BIN_PKG_NAME%\
  )

echo off

echo Patch is DONE

goto:EOF

:End
echo.
