@REM @file
@REM Script to generate BIOS update relative images with Fault Tolerance support.
@REM
@REM This script
@REM
@REM 1. Generate ClientBios_Ft.ROM - a fault tolerance supported BIOS update image
@REM    a. Rebased FvRecovery2 and FspMT in IBB2 to generate IBB2R image.
@REM    b. Update hashed IBB info (e.g., FIT table, _IBBS_) in IBB1 to generate IBB1R image.
@REM    c. Append IBB2R and IBB1R image to input BIOS image.
@REM
@REM   +==============================================================
@REM   |  NVStorage |                                                |
@REM   +------------+                                                |
@REM   |    OBB     | <= FvMain, FvMain2, and etc.                   v
@REM   +------------+                                               Original BIOS image
@REM   |    IBB2    | <= FvRecovery2, FSP, uCode, and etc.           ^
@REM   +------------+                                                |
@REM   |    Resv    | <= Reserved for TopSwap region                 |
@REM   +------------+                                                |
@REM   |    IBB1    | <= RvRecovery                                  |
@REM   +==============================================================
@REM   |    IBB2R   | <= Rebased IBB2                                v
@REM   +------------+                                               New appended image
@REM   |    IBB1R   | <= IBB1 with updated FIT/BtG info of IBB2R     ^
@REM   +==============================================================
@REM
@REM 2. Generate BiosUpdateConfig.ini
@REM    Patch correct BaseAddress/Length/ImageOffset value in BiosUpdateConfig.ini file.
@REM 3. Generate BiosBgup.bin
@REM    Generate BGUP for each update region (e.g., IBB1, IBB2, and etc.) and merage
@REM    them to a single BiosBgup binary.
@REM    Besides, update HelperOffset/HelperLength accordingly in BiosUpdateConfig.ini to
@REM    indicate the offset/length of each BGUP within BiosBgup binary.
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

@REM Usage:
@REM GenBiosUpdateImages.bat [BIOS ROM] [Build Type] [Output Path]
@REM   BIOS ROM      : The file path to BIOS image.
@REM   Build Type    : Indicates BIOS ROM is DEBUG or RELEASE build.
@REM   Output Path   : The path where the output files will be generated at.
@REM
@set BIOS_ROM_FILE=%1
@set BIOS_ROM_BUILD_TYPE=%2
@set BIOS_UPDATE_IMAGE_OUTPUT=%3
@set INI_TEMPLATE=%4

@if not defined WORKSPACE          goto EnvironmentNotSet
@if not defined WORKSPACE_PLATFORM goto EnvironmentNotSet
@if not defined PLATFORM_PACKAGE   goto EnvironmentNotSet
@if not defined PLATFORM_FULL_PACKAGE   goto EnvironmentNotSet

@if not exist %BIOS_ROM_FILE% (
  @echo !!! Assigned BIOS ROM file %BIOS_ROM_FILE% does not exist!!!
  @goto BiosImagesNotBuilt
)

@REM
@REM Define environment variables
@REM
@set CAPSULE_UPDATE_FEATURE_PATH=%WORKSPACE_PLATFORM%\%PLATFORM_FULL_PACKAGE%\Features\CapsuleUpdate

@REM Flash map used to split BIOS into IBB1/IBB2/OBB region
@set FLASH_MAP_NAME=%WORKSPACE_PLATFORM%\ElkhartLakeBoardPkg\Include\Fdf\FlashMapInclude.fdf
@REM Flash map used to determine the offset of IBB2R
@REM @set FT_FLASH_MAP_NAME=%CAPSULE_UPDATE_FEATURE_PATH%\FaultTolerance.fdf
@REM The ini source file
@set INI_TEMPLATE_FILE=%CAPSULE_UPDATE_FEATURE_PATH%\BiosUpdateConfig\%INI_TEMPLATE%

@REM Tool path to rebase IBB2 modules, re-generate FIT and BootGuard sign data.
@set RECOVERY_GEN_TOOL_PATH=%CAPSULE_UPDATE_FEATURE_PATH%\Tools\GenBiosUpdateImages\CapsuleRecoveryGen
@REM Path to put split IBB1/IBB2/IBB1R/IBB2R/OBB binaries.
@set SPLIT_ROM_PATH=%BIOS_UPDATE_IMAGE_OUTPUT%\SplitRom
@REM Path to put tmp files during generating split binaries.
@REM @set SPLIT_ROM_WORKING_PATH=%SPLIT_ROM_PATH%\tmp

@REM
@REM Clean directories and files from the previous output
@REM
if exist %SPLIT_ROM_PATH% rmdir /q /s %SPLIT_ROM_PATH%
@REM @del %BIOS_UPDATE_IMAGE_OUTPUT%\ClientBios_Ft.rom 1>NUL 2>&1
@del %BIOS_UPDATE_IMAGE_OUTPUT%\BiosUpdateConfigSpi.ini 1>NUL 2>&1
@del %BIOS_UPDATE_IMAGE_OUTPUT%\BiosUpdateConfigSpi10Mb.ini 1>NUL 2>&1
@del %BIOS_UPDATE_IMAGE_OUTPUT%\BiosUpdateConfigUfs.ini 1>NUL 2>&1
@del %BIOS_UPDATE_IMAGE_OUTPUT%\BiosBgup.bin 1>NUL 2>&1

@REM
@REM ============ 1. Generate ClientBios_Ft.rom ============
@REM
@set SCRIPT_ERROR=0
mkdir %SPLIT_ROM_PATH%
mkdir %SPLIT_ROM_WORKING_PATH%

@REM
@REM ============ 1-1 Split BIOS ROM ============
@REM
@REM Split FV from bios rom into IBB1, IBB2 and OBB
@REM python %RECOVERY_GEN_TOOL_PATH%\SplitFv.py split -f %BIOS_ROM_FILE% -c all -t %BIOS_ROM_BUILD_TYPE% -m %FLASH_MAP_NAME% -o %SPLIT_ROM_WORKING_PATH%

@REM @if not exist %SPLIT_ROM_WORKING_PATH%\FspMt.rom (
@REM   @echo !!! ERROR:SplitFv Split FV failed!!!
@REM   @echo !!! ERROR:FspMt.rom not exist!!!
@REM   @goto RecoveryFileGenerateFail
@REM )

@REM @if not exist %SPLIT_ROM_WORKING_PATH%\Recovery2.rom (
@REM   @echo !!! ERROR:SplitFv Split FV failed!!!
@REM   @echo !!! ERROR:Recovery2.rom not exist!!!
@REM   @goto RecoveryFileGenerateFail
@REM )

@REM
@REM ============ 1-2 Rebase modules in IBB2 ============
@REM
@REM Rebase FspMt
@REM python %RECOVERY_GEN_TOOL_PATH%\ProcessFvRebase.py fsp %SPLIT_ROM_WORKING_PATH% FspMt.rom fspmt_new.rom %FLASH_MAP_NAME% %FT_FLASH_MAP_NAME% %BIOS_ROM_BUILD_TYPE% %RECOVERY_GEN_TOOL_PATH%\FvBinaryRebase.py
@REM @if errorlevel 1 (
@REM   @echo !!! ERROR:ProcessFvRebase FspMt failed!!!
@REM   set SCRIPT_ERROR=1
@REM   goto RecoveryFileGenerateFail
@REM )

@REM Rebase FvRecovery2
@REM python %RECOVERY_GEN_TOOL_PATH%\ProcessFvRebase.py fv %SPLIT_ROM_WORKING_PATH% Recovery2.rom Recovery2_new.rom %FLASH_MAP_NAME% %FT_FLASH_MAP_NAME% %BIOS_ROM_BUILD_TYPE% %RECOVERY_GEN_TOOL_PATH%\FvBinaryRebase.py
@REM @if errorlevel 1 (
@REM   @echo !!! ERROR:ProcessFvRebase Recovery2 failed!!!
@REM   set SCRIPT_ERROR=1
@REM   goto RecoveryFileGenerateFail
@REM )

@REM Merge rebased FV to make a new bios rom
@REM python %RECOVERY_GEN_TOOL_PATH%\SplitFv.py merge -c all -n merge.bin -a %FT_FLASH_MAP_NAME% -t %BIOS_ROM_BUILD_TYPE% -m %FLASH_MAP_NAME% -o %SPLIT_ROM_WORKING_PATH%
@REM @if not exist %SPLIT_ROM_WORKING_PATH%\merge.bin (
@REM   @echo !!! ERROR:SplitFv merge FV failed!!!
@REM   @echo !!! ERROR:merge.bin not exist!!!
@REM   @goto RecoveryFileGenerateFail
@REM )

@REM
@REM ============ 1-3 Generate new FIT and BootGuard info ============
@REM
@REM Generate new Fit table and BPM based on the new ROM.
@REM @if exist %RECOVERY_GEN_TOOL_PATH%\FitBpmGen.bat (
@REM   call %RECOVERY_GEN_TOOL_PATH%\FitBpmGen.bat
@REM )

@REM @if %SCRIPT_ERROR% NEQ 0 (
@REM   @echo !!! ERROR:FitBpmGen failed!!!
@REM   goto RecoveryFileGenerateFail
@REM )

@REM
@REM ============ 1-4 Generate IBB1/IBB2/IBB1R/IBB2R/OBB binaries ============
@REM
@REM Ibb1.bin
@REM copy /y /b %SPLIT_ROM_WORKING_PATH%\Ibb.rom %SPLIT_ROM_PATH%\Ibb1.bin
@REM Ibb1R.bin
@REM split -f %SPLIT_ROM_WORKING_PATH%\Bpm.bin -s 0x9E0000 -o %SPLIT_ROM_WORKING_PATH%\tmp2.bin -t %SPLIT_ROM_PATH%\Ibb1R.bin
@REM TsRegion.bin
@REM split -f %SPLIT_ROM_WORKING_PATH%\tmp2.bin -s 0x9C0000 -o %SPLIT_ROM_WORKING_PATH%\tmp3.bin -t %SPLIT_ROM_PATH%\TsRegion.bin
@REM del %SPLIT_ROM_WORKING_PATH%\tmp2.bin
@REM del %SPLIT_ROM_WORKING_PATH%\tmp3.bin

@REM Ibb2.bin
@REM copy /y /b %SPLIT_ROM_WORKING_PATH%\Ibb2.rom + %SPLIT_ROM_WORKING_PATH%\Recovery2.rom + %SPLIT_ROM_WORKING_PATH%\FspMt.rom %SPLIT_ROM_PATH%\Ibb2.bin
@REM Ibb2R.bin
@REM copy /y /b %SPLIT_ROM_WORKING_PATH%\Ibb2.rom + %SPLIT_ROM_WORKING_PATH%\Recovery2_new.rom + %SPLIT_ROM_WORKING_PATH%\fspmt_new.rom %SPLIT_ROM_PATH%\Ibb2R.bin

@REM Obb.bin
@REM copy /y /b %SPLIT_ROM_WORKING_PATH%\Obb.rom %SPLIT_ROM_PATH%\Obb.bin

@REM
@REM ============ 1-5 Generate ClientBios_Ft.rom ============
@REM
@REM Generate the final image ClientBios_Ft.rom used for Capsule udpate.
@REM copy /y /b %BIOS_ROM_FILE% + %SPLIT_ROM_PATH%\Ibb2R.bin + %SPLIT_ROM_PATH%\Ibb1R.bin %BIOS_UPDATE_IMAGE_OUTPUT%\ClientBios_Ft.rom
@REM copy /y /b %BIOS_ROM_FILE% %BIOS_UPDATE_IMAGE_OUTPUT%\ClientBios_Ft.rom

@REM @%FIND_PCD_CMD% -F %FIND_PCD_DSC% -PCD gPlatformModuleTokenSpaceGuid.PcdResiliencyEnable
@REM @if errorlevel 2 (
@REM   @echo gPlatformModuleTokenSpaceGuid.PcdResiliencyEnable is not found
@REM   @goto RecoveryFileGenerateFail
@REM ) else (
@REM   @if errorlevel 1 (
@REM     split -f %BIOS_ROM_FILE% -s 0xA50000 -t %SPLIT_ROM_PATH%\IBB.bin -o %SPLIT_ROM_PATH%\IBBR_OBB.bin
@REM     split -f %SPLIT_ROM_PATH%\IBBR_OBB.bin -s 0xA00000 -t %SPLIT_ROM_PATH%\Dummy.bin -o %SPLIT_ROM_PATH%\REMAINING.bin
@REM     split -f %SPLIT_ROM_PATH%\REMAINING.bin -s 0x650000 -t %SPLIT_ROM_PATH%\IBBR.bin -o %SPLIT_ROM_PATH%\REMAINING1.bin
@REM     split -f %SPLIT_ROM_PATH%\REMAINING1.bin -s 0x60000 -t %SPLIT_ROM_PATH%\OBB.bin -o %SPLIT_ROM_PATH%\NVS.bin
@REM   ) else (
@REM     split -f %BIOS_ROM_FILE% -s 0xA50000 -t %SPLIT_ROM_PATH%\IBB.bin -o %SPLIT_ROM_PATH%\IBBR_OBB.bin
@REM     split -f %SPLIT_ROM_PATH%\IBBR_OBB.bin -s 0x60000 -t %SPLIT_ROM_PATH%\OBB.bin -o %SPLIT_ROM_PATH%\NVS.bin
@REM     copy /b /y %SPLIT_ROM_PATH%\IBB.bin %SPLIT_ROM_PATH%\IBBR.bin
@REM   )
@REM )
@REM
@REM ============ 2. Generate BiosUpdateConfig.ini ============
@REM
@REM Update address/length information in configini file
@REM python %RECOVERY_GEN_TOOL_PATH%\SplitFv.py updateconfig -i %INI_TEMPLATE_FILE% -t %BIOS_ROM_BUILD_TYPE% -m %FLASH_MAP_NAME% -o %BIOS_UPDATE_IMAGE_OUTPUT%
copy %INI_TEMPLATE_FILE% %BIOS_UPDATE_IMAGE_OUTPUT%


rmdir /q /s %SPLIT_ROM_PATH%

@echo.
@echo  GenBiosUpdateImages completed.
@echo.
@goto GenBiosUpdateImagesDone

:RecoveryFileGenerateFail
@echo.
@echo !! Preparation for recovery failed!
@echo.

:BiosImagesNotBuilt
@echo.
@echo !! GenBiosUpdateImages failed.
@echo.
@exit /b 1

:EnvironmentNotSet
@echo.
@echo !! GenBiosUpdateImages failed. Needed environment variables are not defined.
@echo.
@exit /b 1

:GenBiosUpdateImagesDone
