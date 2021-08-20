******************************
      FindPCD v0.1.0.0
******************************
Description:
  1. Search through provided dsc files for given PCD name:
      return errorlevel 0 if the PCD is found and defined FALSE.
      return errorlevel 1 if the PCD is found and definde TRUE.
      return errorlevel 2 if the PCD is not found.
  2. The multiple dsc files input must be placed in override priority order correctly.

System Requirement:
  python 3.x

Supported File Types:
  dsc

Usage: FindPCD.exe -F FILE_PATH_NAME... -PCD PCD_NAME_TO_SEARCH

Optional arguments:
  -h, --help            show this help message and exit
  -F FILES [FILES ...], --files FILES [FILES ...]
                        Space separated list of files in current folder to be
                        processed.
  -PCD PCD_NAME, --pcd_name PCD_NAME
                        PCD name to be searched in dsc files.
  -V, --version         show program's version number and exit

Examples:
  1. FindPcd.exe -F PlatformPkgConfigOverride.dsc PlatformPkgExtConfig.dsc PlatformPkgConfig.dsc -PCD     gBoardModuleTokenSpaceGuid.PcdTestMenuEnable
  2. Usage in batch file:
    @set WORKSPACE=C:\Code\2017_CannonLake
    @set WORKSPACE_PLATFORM=%WORKSPACE%\Intel
    @set PLATFORM_PACKAGE=CannonLakePlatSamplePkg
    @set CONFIG_DSC=%WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\PlatformPkgConfigOverride.dsc %WORKSPACE_PLATFORM%\    %PLATFORM_PACKAGE%\PlatformPkgExtConfig.dsc %WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\PlatformPkgConfig.dsc

    FindPcd.exe -F %CONFIG_DSC% -PCD gPlatformModuleTokenSpaceGuid.PcdDcttFlagEnable

