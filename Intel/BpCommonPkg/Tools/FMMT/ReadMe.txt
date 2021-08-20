================================================================================
Intel(R) Firmware Module Management Tool(Intel(R) FMMT) Version 0.22
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
The Intel(R) FMMT tool enables removal, addition, and replacement of ffs files
in FD image binaries.  It is a prerequisite that the ffs file must be PI 1.2
based, include a UI section, and it must have been generated from NON-XIP modules.

================================================================================
2. FILE LIST
================================================================================
1. 2018-WW13-FMMT.22-Release.zip
   --Binary and source code files of FMMT
2. 2018-WW13-FMMT.22-ReadMe.txt
   --This file
3. FMMT_User_Guide.pdf
   --User Guide

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

  2. Unzip "2018-WW13-FMMT.22-Release.zip\Source\FMMT" to "C:\MyTools\Source\C"

  3. Modify file "C:\MyTools\Source\C\Include\Common\BuildVersion.h" to specify a
     version number if __BUILD_VERSION is "", generally using the git revision
     of BaseTools you downloaded.

  4. Open a Visual Studio command prompt, type "set BASE_TOOLS_PATH=C:\MyTools"

  5. Type "cd C:\MyTools" and type "toolsetup.bat"

  6. Type "cd C:\MyTools\Source\C\Common" and type "nmake"

  7. Type "cd C:\MyTools\Source\C\FMMT" and type "nmake"

  8. The FMMT.exe are installed in "C:\MyTools\Bin\Win32",
     To run FMMT correctly, this path must be set in %PATH% environment.

================================================================================
5. CHANGE LOG & FEATURES ADDED
================================================================================
1. Release 0.23 of Intel(R) FMMT release (TBD)
   1) FMMT Tool fix the bug to run from root directory.
   2) FMMT Tool fix the bug to decode GUIDED section per PROCESS_REQUIRED filed.
   3) FMMT Tool display free space for each FV with -v option.
   4) FMMT Tool fix the bug to handle the image doesn't have VTF.
   5) FMMT Tool fix VS2010 and VS2013 compiler error.
   6) FMMT Tool add support FvNameGuid way to specify FV to be modified.
   7) FMMT Tool add support to generate FFS3 formatted FV.
   8) FMMT Tool add support to process FVs when it has a combination of sub FVs.

2. Release 0.22 of Intel(R) FMMT release (Mar 16, 2018)
   1) FMMT Tool fix the bug to search the config file in Linux env.
   2) FMMT Tool add/refine strinf buffer boundary checks.
   3) FMMT Tool fix possible NULL pointer dereference issues.
   4) FMMT Tool fix the bug to not add alignment for GUIDED_SECTION/COMPRESS_SECTION.

3. Release 0.21 of Intel(R) FMMT release (Jun 13, 2017)
   1) FMMT Tool create utility under Linux.
   2) FMMT Tool to support BrotliCompress tool.
   3) FMMT Tool enhance error message when guided tool is not found or run fail.
   4) FMMT Tool report warning when the added file doesn't have UI section.
   5) FMMT Tool fix the bug for delete files in child FV corrupts the parent.
   6) FMMT Tool fix the bug to handle PROCESSING_REQUIRED field.
   7) FMMT Tool fix the bug to add ffs file into child FV.
   8) FMMT Tool fix the bug to support multiple FV level's replace.
   9) FMMT Tool fix the bug to correct the FV alignment.
   10)FMMT Tool fix some buffer overflow issues and memory leak issues.
   11)FMMT Tool fix the bug to replace the FV type FFS.
   12)FMMT Tool fix the bug to rebase the inside FvImage.
   13)FMMT Tool fix the bug that display FV structure wrongly.

4. Release 0.20 of Intel(R) FMMT release (Mar 30, 2016)
   1) FMMT Tool fix VS2015 compiler bug
   2) FMMT Tool add multiple operation support feature
   3) FMMT Tool fix the FV alignment bug
   4) FMMT Tool fix the child FV order bug

5. Release 0.19 of Intel(R) FMMT release (Nov 24, 2015)
   1) FMMT Tool to generate FFS3 FV system guid for FV image that includes the
      big file

6. Release 0.18 of Intel(R) FMMT release (September 21, 2015)
   1) Added the new support to handle the file path with space
   2) Added the new support to handle FV image with sub FvImage and FFS files
   3) Fixed the bug to support the file path ".\\"
   4) Fixed the bug that always assume the FV EXT header is always sizeof(EFI_FIRMWARE_VOLUME_EXT_HEADER)
   5) Added the new support for PEIM add, delete and replace
   6) Added the new support to check duplicated FFS name
   7) Added the new support to delete entire root FV
   8) Fixed the bug to skip FV EXT header if ext header existed to parse FV
   9) Follow PI spec to update ExtendedSize in EFI_FFS_FILE_HEADER2

7. Release 0.17 of Intel(R) FMMT release (Nov 05, 2014)
   1) Update FMMT tool to handle the file path with space.

8. Release 0.16 of Intel(R) FMMT release (March 05, 2014)
   1) Added new support of big FFS file that is more than 16M bytes.
   2) Fixed the bug of return value.
   3) Enhance the error message while parsing FFS file.
   4) Fixed the bug of failing to add a module to no-nested FV.

9. Release 0.15 of Intel(R) FMMT release (April 11, 2013)

   1) Enabled the Guided Tools config file FmmtConf.ini scan rule by the
      following priority.
     a) Search the current execution path.
     b) Search the same directory with EXE.
     c) Search the %PATH% from left to right.
     d) If it does not exist, use the build-in script.
   2) Enabled the CRC32 GUIDed section parse and supported GUIDed with attribute
      and data offset.
   3) Updated the algorithm to find FV images from the input FD image.
   4) Added the support for the nest encapsulation sections.
   5) Fixed the case that the case no any FFS in a FV, like SLE.
   6) Corrected SectionBuffer and Length on CRC32 section parsing.

10. Release 0.14 of Intel(R) FMMT release (September 25, 2012)

   1) Enhanced the FV structure initialization and the encapsule logic algorithm.
   2) Updated FmmtConf.ini to support LzmaF86Compress.
   3) Fixed a failure decoding with Lzmacompress compressed sections.
   4) Supported the operate on FD image in network shared directory.

11. Release 0.13 of Intel(R) FMMT release (December 14, 2011)

   1) Enabled to add FFS file into FVMAIN_COMPACT image and delete a module in
      a FD.
   2) Supported more than 255 FFS files in FV.
   3) Fixed the section parser to get section information of FFS file, while
      there is a FREE_FROM or SEC_CORE type FFS in FV.

12. Release 0.12 of Intel(R) FMMT release (October 28, 2011)

   1) Fixed the issue that FvNameGuid in Sub_FV was missed after the replace,
      delete or add operation.
   2) Renamed the temorary file as "FmmtTemp" and removed it finally.
   3) Disabled to display some internal message to user while do add, replace
      and delete operation.
   4) Fix an issue that an invalid FV name caused crash.
   5) Fix a bug of free un-allocated memory.
   6) Added Fv Extend Header information while generating FV. If the original
      FV file have this information, after add, delete or replace operate, the
      GUID of Fv Name should still exist.
   7) Added the support for RAW, FREEFORM andSEC type file in FV.

13. Release 0.11 of Intel(R) FMMT release (March 03, 2011)

   Resolved an user access issue when the user is not an authorized administrator
   on the machine FMMT is executing.

   BACKGROUND: While "FMMT.exe" decompress the ".fd" file and gets all FFS
   information. The "FMMT.exe" attempts to create a temporary folder in c:\
   root directory and will fail if the current user does not have authorization
   to create folders.

* Other names and brands may be claimed as the property of others.

================================================================================
6. MISC
================================================================================
1.  Virus scanned by McAfee VirusScan Enterprise 8.8.0, Virus Definitions 8833,
    no virus detected.

[END OF README]
