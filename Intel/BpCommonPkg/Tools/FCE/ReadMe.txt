================================================================================
Intel(R) Firmware Configuration Editor (Intel(R) FCE) Version 0.34
Mar 16, 2018

================================================================================

===============================================================================
CONTENTS
===============================================================================
 1.  OVERVIEW
 2.  FILE LIST
 3.  SUPPORTED OPERATING SYSTEM ENVIRONMENTS
 4.  HOW TO BUILD
 5.  CHANGE LOG & FEATURES ADDED
 6.  MISC

================================================================================
1. OVERVIEW
================================================================================
Intel(R) Firmware Configuration Editor (Intel(R) FCE) enables you to retrieve and
change HII configuration ("Setup") data in Firmware Device (*.fd) files.

The "*.fd" file must be built using the BaseTools in order for the Intel(R) FCE
tool to successfully locate the HII data.  The BaseTools detect the offset of the
HII data stored as global data in the PE/COFF image at build time, and then stores
it in a newly created raw section of FFS file.

This tool only manipulates uncompressed versions of EFI_VARSTORE_IFR and
EFI_VARSTORE_IFR_EFI and it only supports the following question types: CHECKBOX,
ORDERED_LIST, ONE_OF, NUMERIC and STRING.

================================================================================
2. FILE LIST
================================================================================
1. 2018-WW13-FCE.34-Release.zip
   -- Source code and binary files for FCE tool
2. 2018-WW13-FCE.34-ReadMe.txt
   -- This file
3. Intel Firmware Configuration Editor Quick Start Guide.pdf
   -- A quick start user guide

================================================================================
3. SUPPORTED OPERATING SYSTEM ENVIRONMENTS
================================================================================
1. Microsoft Windows XP* Professional w/SP3, IA32 & X64
2. Microsoft Windows 7* 64-bit

================================================================================
4. HOW TO BUILD
================================================================================
  1. Download BaseTools from "https://github.com/tianocore/edk2.git" to your local
     machine like "C:\MyTools"

  2. Unzip "2018-WW13-FCE.34.zip" to "C:\MyTools\Source\C"

  3. Modify file "C:\MyTools\Source\C\Include\Common\BuildVersion.h" to specify a
     version number if __BUILD_VERSION is "", generally using the git revision
     of BaseTools you downloaded.

  4. Open a Visual Studio command prompt, type "set BASE_TOOLS_PATH=C:\MyTools"

  5. Type "cd C:\MyTools" and type "toolsetup.bat"

  6. Type "cd C:\MyTools\Source\C\Common" and type "nmake"

  7. Type "cd C:\MyTools\Source\C\BfmLib" and type "nmake"

  8. Type "cd C:\MyTools\Source\C\FCE" and type "nmake"

  9. The BfmLib.exe and FCE.exe are installed in "C:\MyTools\Bin\Win32",
     To run FCE correctly, this path must be set in %PATH% environment.

================================================================================
5. CHANGE LOG & FEATURES ADDED
================================================================================
1. Release 0.34 of Intel(R) FCE release (Mar 16, 2018)
   1) FCE Tool to add support for String question type.
   2) FCE Tool to read/update the setting from PcdNvStoreDefaultValueBuffer value.
   3) FCE Tool to allocate small binary range for the default setting.
   4) FCE Tool to add the missing operation for the update mode.
   5) FCE Tool fix the bug to search the config file in Linux env.
   6) FCE Tool to handle Question stored in bit field.
   7) FCE Tool to add/refine strinf buffer boundary checks.
   8) FCE Tool to fix the bug for possible NULL pointer dereference issues.
   9) FCE Tool to fix the bug about parameter format mismatch in scanf function.
   10) FCE Tool to rename some functions that conflict with BaseTools Common
   11) FCE Tool fix the bug to add check for ZeroMem operation.

2. Release 0.33 of Intel(R) FCE release (Jun 13, 2017)
   1) FCE Tool create utility under Linux.
   2) FCE Tool to support BrotliCompress tool.
   3) FCE Tool enhance performance.
   4) FCE Tool fix the bug to initialize mStringBuffer early.
   5) FCE Tool fix the bug to assign question with PlatformId and DefaultId.
   6) FCE Tool fix the bug to add FvName info into the generated leaf FFS file name.
   7) FCE Tool enhance error message when guided tool is not found or run fail.
   8) FCE Tool fix the bug for compare the version with BfmLib.
   9) FCE Tool fix some buffer overflow issues and memory leak issues.
   10)FCE Tool fix the bug that output in different editor show different content.

3. Release 0.32 of Intel(R) FCE release (April 7th, 2016)
   1) FCE Tool fix VS2015 compiler bug
   2) FCE Tool fix the bug that BIOS image has the FV image which has nothing.
   3) FCE Tool fix the bug that corrupt FIT table after update operation.

4. Release 0.31 of Intel(R) FCE release (Nov 24, 2015)
   1) Fixed the bug for FCE takes too long time to read & update for some
      specific BIOS image

5. Release 0.30 of Intel(R) FCE release (September 21, 2015)
   1) Added the new support to display additional information for questions
   2) Added the new support to set the default value for OrderList
   3) Fixed the bug for FCE to check NV attribute in EFI varstore

6. Release 0.29 of Intel(R) FCE release (February 28, 2015)
   1) Add messages that updateq can only be used in common mode.
   2) Fix a crash bug when reading some FDs.
   3) Remove consecutive backslashes in path when GuidToolDefinitionConf.ini is
      found in current working directory.

7. Release 0.28 of Intel(R) FCE release (August 15, 2014)
   1) Update FCE tool to handle the file path with space

8. Release 0.27 of Intel(R) FCE release (March 05, 2014)

   1) Added one new parameter "-a" for multi-platform mode to specify this tool set
      to choose the smaller size between two different storage formats in NV RAM.
   2) Added one new parameter "-g" for multi-platform mode to specify the FV image
      that stores the multi-platform default setting.
   3) Added new support of big FFS file that is more than 16M bytes.
   4) Fixed the bug of IFR parser.

9. Release 0.26 of Intel(R) FCE release (April 11, 2013)

   1) Enhanced the read operation of multi-platform mode to generate the current
      setting, and make the update mode list the difference based on the current
      value of BFV.
   2) Added two new parameters "--remove" and "--ignore" for multi-platform mode
      to insert variable storage into BFV of FD with variables in NVRAM.
   3) Added the variable name and GUID to error message, when more than one
      EfiVarStore variables were defined with the same name and GUID but
      different sizes.
   4) Fixed the issue that the value of 64-bit "numeric" question is truncated.
   5) Fixed the case that the case no any FFS in a FV, like SLE.
   6) Enabled the CRC32 GUIDED section parse in BfmLib.
   7) Enabled the Guided Tools config fileGuidToolDefinitionConf.ini scan rule
      by the following priority.
     a) Search the current execution path.
     b) Search the same directory with EXE.
     c) Search the %PATH% from left to right.
     d) If not existed in case above, use the build-in script.
   8) Enhanced the error message when insert the FFS to a BFV which has no much
      available space. The required size and the spare size in PAD FFS will be
      printed.
   9) Add the build revision.

10. Release 0.25 of Intel(R) FCE release (June 04, 2012)

   1) Fixed the bug that one single compressed PEIM was missing in BFV after
      executing the update in multi-platform mode.
   2) Added new support of LZMA compression with F86 converter.

11. Release 0.24 of Intel(R) FCE release (March 01, 2012)

   1) Enhanced the Intel FCE tool to support updating the existing default data in
      *.fd images, in multi-platform mode.
   2) Fixed the bug where the tool was supporting one EfiVarStore in multi-platform
      mode.
   3) Added support to parse HII data from UEFI applications, as UEFI applications
      may include HII packages and be built into the ".fd".

12.Release 0.23 of Intel(R) FCE adds the multi-platform mode support, adds new
   support for UEFI 2.31 EFI_VARSTORE_IFR_EFI, and enables the VFR disableif,
   supressif and default value conditional expression calculation.

   BACKGROUND: The multi-platform mode is used to make single BIOS image support
   all platforms and modes (normal mode and MFG mode). It offers the different
   default values for different platforms and modes. Default value which depends
   on PlatformId and DefaultId described in VFR files can be specified by VFR
   default value expression, for example:

   default value=cond(ideqval SETUP_VOLATILE_DATA.PlatId == BoardIdEcolaFalls
   ? 0x1:0x0), defaultstore = MyStandardDefault

   The Intel(r) FCE will create the binary file to store default settings at build
   time, and add all default settings into BFV as one FFS. The platform code will
   get the matched default setting when the default needs to be loaded, and launch
   the system according to the specified default values.

   For multi-platform mode, it only manipulates the uncompressed versions of
   UEFI 2.31 EFI_VARSTORE_IFR_EFI.

13.Release 0.22 of Intel(R) FCE adds a new time based variable layout support for
   UEFI 2.3.1 security boot and enhances three kinds of special cases handlings.
   The detail is listed below.

   1) Add a new time-based variable layout support. Now, three kinds of variable
      are supported, including normal variable, monotonic based authenticate
      variable and time based authenticate variable.
   2) Enhance the error handling when exists two variables with same variable name,
      guid but different size in different modules.
   3) Handle the special case that none DEFAULT attribute in ONE_OF options and
      0 is not a valid value. In this case, set the first one as the default value.
   4) Handle the special case that no DEFAULT value in NUMERIC and 0 is out of the
      range between minimum and maximum. In this case, set the minimum as the
      default value.

   A fix was only applied to the binary "FCE.exe".

14.Release 0.21 of Intel(R) FCE resolves a user access issue when the user is not
   an authorized administrator on the machine FCE is executing.

   BACKGROUND: A library component within "BfmLib.exe" is called by "FCE.exe"
   to decompress the ".fd" file and obtain all of the FFS information. An
   attempt is made to create a temporary folder in c:\ root directory. The
   attempt fails if the current user does not have authorization to create folders.

   A fix was applied to the library function within "BfmLib.exe." - no other
   changes were applied to "FCE.EXE." The "FCE.exe" 0.21 binary was updated
   from revision 0.20 to 0.21.

15.Release 0.20 of Intel(R) FCE resolves the FCE message:
   "Error. Invalid FD files." The root cause was an FCE dependency on the
   Windows API FindFirstFile()/FindNextFile() reading order of decompressed FFS
   from disk. The fix is to add additional logic to clear the return status.

* Other names and brands may be claimed as the property of others.

================================================================================
6. MISC
================================================================================
1.  Virus scanned by McAfee VirusScan Enterprise 8.8.0, Virus Definitions 8833,
    no virus detected.

[END OF README]
