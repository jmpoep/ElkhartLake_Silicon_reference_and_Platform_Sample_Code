@echo off

echo %0: Generating ElkhartLakeSimicsLP image

@REM Set Simics Rom Generation Tool Path and Simics Rom Output Path
if not defined WORKSPACE echo ERROR - WORKSPACE is not defined
if not defined WORKSPACE_PLATFORM echo ERROR - WORKSPACE_PLATFORM is not defined && exit /b 1
if not defined PROJECT echo ERROR - PROJECT is not defined && exit /b 1
if not defined EHL_SIMICS_TOOL_PATH set EHL_SIMICS_TOOL_PATH=%WORKSPACE_PLATFORM%\%PROJECT%\Tools\RomImage\ElkhartLakeSimicsLP
if not defined SIMICS_ROM_LOCATION set SIMICS_ROM_LOCATION=%WORKSPACE%\RomImages\MinPlatform\ElkhartLakeSimicsLP

@REM Copy BIOS to Simics Rom Generation Tool
if not defined BUILD_DIR_PATH echo ERROR - BUILD_DIR_PATH is not defined && exit /b 1
if not defined BOARD echo ERROR - BOARD is not defined && exit /b 1
if not exist "%EHL_SIMICS_TOOL_PATH%\fit\bin\" mkdir %EHL_SIMICS_TOOL_PATH%\fit\bin
copy %BUILD_DIR_PATH%\Fv\%BOARD%.fd %EHL_SIMICS_TOOL_PATH%\fit\bin\bios.bin /Y

@echo on
