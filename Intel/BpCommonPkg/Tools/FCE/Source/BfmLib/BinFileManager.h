/** @file  BinFileManager.h

 The header of BinFileManager.c.

 Copyright (c) 2011 - 2017, Intel Corporation. All rights reserved.<BR>

 This program and the accompanying materials are licensed and made available under
 the terms and conditions of the BSD License which accompanies this distribution.
 The full text of the license may be found at
 http://opensource.org/licenses/bsd-license.php

 THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef    _BIN_FILE_MANAGER_
#define    _BIN_FILE_MANAGER_

#ifdef __GNUC__
#include <unistd.h>
#else
#include <io.h>
#include <direct.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FvLib.h>
#include <Common/UefiBaseTypes.h>
#include <Common/PiFirmwareVolume.h>
#include <Common/PiFirmwareFile.h>

#include "CommonLib.h"
#include "EfiUtilityMsgs.h"
#include "ParseGuidedSectionTools.h"
#include "StringFuncs.h"
#include "Compress.h"
#include "Decompress.h"
#include "ParseInf.h"

#ifndef _MAX_PATH
#define _MAX_PATH 500
#endif

#ifdef __GNUC__
#define OS_SEP        '/'
#define OS_SEP_STR    "/"
#define COPY_STR      "cp \"%s\" \"%s\" > /dev/null"
#define RMDIR_STR     "rm -r \"%s\" > /dev/null"
#define DEL_STR       "rm \"%s\" > /dev/null"
#else
#define OS_SEP        '\\'
#define OS_SEP_STR    "\\"
#define COPY_STR      "copy \"%s\" \"%s\" > NUL"
#define RMDIR_STR     "rmdir /S /Q \"%s\" > NUL"
#define DEL_STR       "del \"%s\" > NUL"
#endif

#define TEMP_DIR_NAME              "Temp"
#define UTILITY_NAME               "Binary File Manager (BFM)"
#define UTILITY_SHORT_NAME         "BFM"
#define UTILITY_MAJOR_VERSION      0
#define UTILITY_MINOR_VERSION      1
#define MAX_BASENAME_LEN           60  // not good to HardCode, but let's be reasonable
#define EFI_SECTION_ERROR EFIERR   (100)
//
// The maximum number of Pad file guid entries.
//
#define MAX_NUMBER_OF_PAD_FILE_GUIDS    1024

//
// The maximum number of block map entries supported by the library
//
#define MAX_NUMBER_OF_FV_BLOCKS         100


//
// The maximum number of sections in an FFS file.
//
#define MAX_NUMBER_OF_SECTION_IN_FFS    100

//
// The maximum number of files in the FV supported by the library
//
#define MAX_NUMBER_OF_FILES_IN_FV       1000
#define MAX_NUMBER_OF_FILES_IN_CAP      1000



///
/// If present, this must be the first and only opcode,
/// EFI_DEP_BEFORE is only used by DXE driver.
///
#define EFI_DEP_BEFORE        0x00

///
/// If present, this must be the first and only opcode,
/// EFI_DEP_AFTER is only used by DXE driver.
///
#define EFI_DEP_AFTER         0x01

#define EFI_DEP_PUSH          0x02
#define EFI_DEP_AND           0x03
#define EFI_DEP_OR            0x04
#define EFI_DEP_NOT           0x05
#define EFI_DEP_TRUE          0x06
#define EFI_DEP_FALSE         0x07
#define EFI_DEP_END           0x08


///
/// If present, this must be the first opcode,
/// EFI_DEP_SOR is only used by DXE driver.
///
#define EFI_DEP_SOR           0x09

//
// INF file strings
//
#define OPTIONS_SECTION_STRING                "[options]"
#define ATTRIBUTES_SECTION_STRING             "[attributes]"
#define FILES_SECTION_STRING                  "[files]"
#define FV_BASE_ADDRESS_STRING                "[FV_BASE_ADDRESS]"

//
// Options section
//
#define EFI_FV_BASE_ADDRESS_STRING        "EFI_BASE_ADDRESS"
#define EFI_FV_FILE_NAME_STRING           "EFI_FILE_NAME"
#define EFI_NUM_BLOCKS_STRING             "EFI_NUM_BLOCKS"
#define EFI_BLOCK_SIZE_STRING             "EFI_BLOCK_SIZE"
#define EFI_GUID_STRING                   "EFI_GUID"
#define EFI_FV_FILESYSTEMGUID_STRING      "EFI_FV_GUID"
#define EFI_FV_NAMEGUID_STRING            "EFI_FVNAME_GUID"
#define EFI_CAPSULE_GUID_STRING           "EFI_CAPSULE_GUID"
#define EFI_CAPSULE_HEADER_SIZE_STRING    "EFI_CAPSULE_HEADER_SIZE"
#define EFI_CAPSULE_FLAGS_STRING          "EFI_CAPSULE_FLAGS"
#define EFI_CAPSULE_VERSION_STRING        "EFI_CAPSULE_VERSION"

#define EFI_FV_TOTAL_SIZE_STRING    "EFI_FV_TOTAL_SIZE"
#define EFI_FV_TAKEN_SIZE_STRING    "EFI_FV_TAKEN_SIZE"
#define EFI_FV_SPACE_SIZE_STRING    "EFI_FV_SPACE_SIZE"


typedef UINT32 BFM_ENCAP_TYPE;

#define MAX_LEVEL_IN_FV_FILE  32

//
// Types of BFM_ENCAP_TREENODE_TYPE
//
#define BFM_ENCAP_TREE_FV                    0x1
#define BFM_ENCAP_TREE_FFS                   0x2
#define BFM_ENCAP_TREE_GUIDED_SECTION        0x3
#define BFM_ENCAP_TREE_COMPRESS_SECTION      0x4
#define BFM_ENCAP_TREE_FV_SECTION            0x5

extern EFI_HANDLE mParsedGuidedSectionTools;
extern BOOLEAN     mFvGuidIsSet;
extern EFI_GUID    mFvNameGuid;

//
// Structure to keep a list of GUID-To-BaseNames
//
typedef struct _GUID_TO_BASENAME {
  struct _GUID_TO_BASENAME  *Next;
  INT8                      Guid[PRINTED_GUID_BUFFER_SIZE];
  INT8                      BaseName[MAX_BASENAME_LEN];
} GUID_TO_BASENAME;

typedef struct _GUID_SEC_TOOL_ENTRY {
  EFI_GUID   Guid;
  CHAR8*     Name;
  CHAR8*     Path;
  struct _GUID_SEC_TOOL_ENTRY *Next;
} GUID_SEC_TOOL_ENTRY;

//
// Private data types
//
//
// Component information
//
typedef struct {
  UINTN Size;
  CHAR8 ComponentName[_MAX_PATH];
} COMPONENT_INFO;

typedef struct {
  CHAR8            FfsName[_MAX_PATH];

  //
  // UI Name for this FFS file, if has.
  //
  CHAR16           UiName[_MAX_PATH];

  //
  // Total section number in this FFS.
  //
  UINT32           TotalSectionNum;

  //
  // Describe the position of the FFS file.
  //
  UINT8            Level;
  //
  // If this FFS has no encapsulate section, this flag will set to True.
  //
  BOOLEAN          IsLeaf;
  //
  // Section type for each section in FFS.
  //
  EFI_SECTION_TYPE SectionType[MAX_NUMBER_OF_SECTION_IN_FFS];

}FFS_ATTRIBUTES;


typedef struct __ENCAP_INFO_DATA{
  //
  // Now Level
  //
  UINT8                      Level;

  //
  // Encapsulate type.
  //
  BFM_ENCAP_TYPE             Type;

  //
  // Data, if it's FV, should be FV header.
  //
  VOID                       *Data;

  //
  // if FV ExtHeaderOffset not to zero, should also have FvExtHeader information
  //
  EFI_FIRMWARE_VOLUME_EXT_HEADER *FvExtHeader;


  //
  // Next node.
  //
  struct __ENCAP_INFO_DATA   *NextNode;
}ENCAP_INFO_DATA;


//
// Contain Offset and Data for PAD FFS contain reset vector or FIT data.
//
typedef struct _PATCH_DATA_PAD_FFS {
  //
  // The offset of data relative to FV start address;
  //
  UINT32                          Offset;
  //
  // Data
  //
  VOID                            *Data;
  //
  // Length of Data
  //
  UINT32                          Length;
  //
  // Next node.
  //
  struct _PATCH_DATA_PAD_FFS      *NextNode;
} PATCH_DATA_PAD_FFS;


//
// FV and capsule information holder
//
typedef struct _FV_INFOMATION{
  EFI_FIRMWARE_VOLUME_HEADER *FvHeader;
  EFI_FIRMWARE_VOLUME_EXT_HEADER *FvExtHeader;
  UINT32                     ImageAddress;
  UINT32                     FfsNumbers;
  CHAR8                      FvName[_MAX_PATH];
  EFI_FV_BLOCK_MAP_ENTRY     FvBlocks[MAX_NUMBER_OF_FV_BLOCKS];
  FFS_ATTRIBUTES             FfsAttuibutes[MAX_NUMBER_OF_FILES_IN_FV];
  EFI_FFS_FILE_HEADER2       FfsHeader[MAX_NUMBER_OF_FILES_IN_FV];
  struct _FV_INFOMATION      *FvNext;
  ENCAP_INFO_DATA            *EncapData;
  UINT8                      FvLevel;
  PATCH_DATA_PAD_FFS         *PatchData;
  BOOLEAN                    IsBfvFlag;
  BOOLEAN                    IsInputFvFlag;

} FV_INFORMATION;

typedef struct _FIRMWARE_DEVICE {
  ///
  /// Size of FD file
  ///
  UINT32                   Size;
  FV_INFORMATION           *Fv;
} FIRMWARE_DEVICE;

VOID
Usage (
  VOID
);


CHAR8 *
GenTempFile (
  VOID
);

EFI_STATUS
BfmImageView (
  IN     CHAR8*           FdInName,
  IN     CHAR8*           FvName,
  IN     BOOLEAN          ViewFlag,
  OUT    FIRMWARE_DEVICE  **FdData
);


EFI_STATUS
BfmImageAdd (
  IN     CHAR8*  FdInName,
  IN     CHAR8*  NewFile,
  IN     CHAR8*  FdOutName
);

/**
  Replace an FFS file into a specify FV.

  @param[in]   FdInName     Input FD binary/image file name;
  @param[in]   NewFile      The name of the file add in;
  @param[in]   FdOutName    Name of output fd file.

  @retval      EFI_SUCCESS
  @retval      EFI_INVALID_PARAMETER
  @retval      EFI_ABORTED

**/
EFI_STATUS
BfmImageReplace (
  IN     CHAR8*  FdInName,
  IN     CHAR8*  NewFile,
  IN     CHAR8*  FdOutName
);

//
// Function in BfmLib.c file.
//
FV_INFORMATION *
LibInitializeFvStruct (
  FV_INFORMATION *Fv
);

EFI_STATUS
LibFindFvInFd (
  IN     FILE             *InputFile,
  IN OUT FIRMWARE_DEVICE  **FdData
);

/**

  TODO: Add function description

  @param[in]    Fv            - Firmware Volume to get information from

  @return       EFI_STATUS

**/
EFI_STATUS
LibGetFvInfo (
  IN     VOID                         *Fv,
  IN OUT FV_INFORMATION               *CurrentFv,
  IN     CHAR8                        *FvName,
  IN     UINT8                        Level,
  IN     UINT32                       *FfsCount,
  IN     BOOLEAN                      ViewFlag,
  IN     BOOLEAN                      IsChildFv
  );

/**

  TODO: Add function description

  FvImage       - TODO: add argument description
  FileHeader    - TODO: add argument description
  ErasePolarity - TODO: add argument description

  EFI_SUCCESS - TODO: Add description for return value
  EFI_ABORTED - TODO: Add description for return value

**/
EFI_STATUS
LibGetFileInfo (
  EFI_FIRMWARE_VOLUME_HEADER  *FvImage,
  EFI_FFS_FILE_HEADER2        *CurrentFile,
  BOOLEAN                     ErasePolarity,
  FV_INFORMATION              *CurrentFv,
  CHAR8                       *FvName,
  UINT8                       Level,
  UINT32                      *FfsCount,
  BOOLEAN                     ViewFlag
  );

/**

  Parses EFI Sections

  @param[in]    SectionBuffer - Buffer containing the section to parse.
  @param[in]    BufferLength  - Length of SectionBuffer

  @retval       EFI_SECTION_ERROR - Problem with section parsing.
                      (a) compression errors
                      (b) unrecognized section
  @retval       EFI_UNSUPPORTED - Do not know how to parse the section.
  @retval       EFI_SUCCESS - Section successfully parsed.
  @retval       EFI_OUT_OF_RESOURCES - Memory allocation failed.

--*/
EFI_STATUS
LibParseSection (
  UINT8                  *SectionBuffer,
  UINT32                 BufferLength,
  FV_INFORMATION         *CurrentFv,
  CHAR8                  *FvName,
  EFI_FFS_FILE_HEADER2   *CurrentFile,
  UINT8                  Level,
  UINT32                 *FfsCount,
  BOOLEAN                ViewFlag,
  BOOLEAN                ErasePolarity,
  BOOLEAN                FfsGeneratedFlag
  );

/*
  Get size info from FV file.

  @param[in]
  @param[out]

  @retval

*/
EFI_STATUS
LibGetFvSize (
  IN   FILE                       *InputFile,
  OUT  UINT32                     *FvSize
  );

/*
  Generate the leaf FFS files.

*/
EFI_STATUS
LibGenFfsFile (
  EFI_FFS_FILE_HEADER2   *CurrentFile,
  FV_INFORMATION         *CurrentFv,
  CHAR8                  *FvName,
  UINT8                  Level,
  UINT32                 *FfsCount,
  BOOLEAN                ErasePolarity
  );

 /**

  This function returns the next larger size that meets the alignment
  requirement specified.

  @param[in]      ActualSize      The size.
  @param[in]      Alignment       The desired alignment.

  @retval         EFI_SUCCESS     Function completed successfully.
  @retval         EFI_ABORTED     The function encountered an error.

**/
UINT32
GetOccupiedSize (
  IN UINT32  ActualSize,
  IN UINT32  Alignment
  );

EFI_STATUS
LibDeleteAndRenameFfs(
  IN CHAR8*    DeleteFile,
  IN CHAR8*    NewFile
);

/**
  Converts ASCII characters to Unicode.
  Assumes that the Unicode characters are only these defined in the ASCII set.

  String      - Pointer to string that is written to FILE.
  UniString   - Pointer to unicode string

  The address to the ASCII string - same as AsciiStr.

**/
VOID
LibAscii2Unicode (
  IN   CHAR8          *String,
  OUT  CHAR16         *UniString
  );

EFI_STATUS
LibCreateGuidedSectionOriginalData(
  IN CHAR8*    FileIn,
  IN CHAR8*    ToolName,
  IN CHAR8*    FileOut
);

/**

   This function convert the FV header's attribute to a string. The converted string
   will be put into an INF file as the input of GenFV.

   @param[in]      Attr       FV header's attribute.
   @param[out]     InfFile    InfFile contain FV header attribute information.

   @retval         EFI_SUCCESS.
   @retval         EFI_INVLID_PARAMETER
   @retval         EFI_OUT_OF_RESOURCES

**/
EFI_STATUS
LibFvHeaderAttributeToStr (
  IN     EFI_FVB_ATTRIBUTES_2     Attr,
  IN     FILE*                  InfFile
);


/**
   This function fill the FV inf files option field.

   @param[in]      BlockMap       FV header's attribute.
   @param[out]     InfFile    InfFile contain FV header attribute information.

   @retval         EFI_SUCCESS.
   @retval         EFI_INVLID_PARAMETER

**/
EFI_STATUS
LibFvHeaderOptionToStr (
  IN     EFI_FV_BLOCK_MAP_ENTRY  *BlockMap,
  IN     FILE*                   InfFile,
  IN     BOOLEAN                 IsRootFv
);

/**
   This function fill the FV inf files option field.

   @param[in]      FfsName    Ffs file path/name.
   @param[out]     InfFile    InfFile contain FV header attribute information
   @param[in]      FirstIn    Is the first time call this function? If yes, should create [files] section.

   @retval         EFI_SUCCESS.
   @retval         EFI_INVLID_PARAMETER

**/
EFI_STATUS
LibAddFfsFileToFvInf (
  IN     CHAR8                   *FfsName,
  IN     FILE*                   InfFile,
  IN     BOOLEAN                 FirstIn
);

/**
  Convert EFI file to PE or TE section

  @param[in]   InputFilePath   .efi file, it's optional unless process PE/TE section.
  @param[in]   Type            PE or TE and UI/Version
  @param[in]   OutputFilePath  .te or .pe file
  @param[in]   UiString        String for generate UI section usage, this parameter is optional
                               unless Type is EFI_SECTION_USER_INTERFACE.
  @param[in]   VerString       String for generate Version section usage, this parameter is optional
                               unless Type is EFI_SECTION_VERSION.

  @retval EFI_SUCCESS

**/
EFI_STATUS
LibCreateFfsSection (
  IN CHAR8*     InputFilePath,      OPTIONAL
  IN CHAR8*     Sections,           OPTIONAL
  IN UINT8      Type,
  IN CHAR8*     OutputFilePath,
  IN CHAR8*     UiString,           OPTIONAL
  IN CHAR8*     VerString,          OPTIONAL
  IN CHAR8*     GuidToolGuid,       OPTIONAL
  IN CHAR8*     CompressType        OPTIONAL
  );

/**
  Encapsulate FFSs to FV

  @param[in]   InputFilePath   Section file will be read into this FFS file. This option is required.
  @param[in]   OutputFilePath  The created PI firmware file name. This option is required.
  @param[in]   BlockSize       BlockSize is one HEX or DEC format value required by FV image.
  @param[in]   FileTakeSize

  @retval EFI_SUCCESS

**/
EFI_STATUS
LibEncapsulateFfsToFv (
  IN CHAR8*     InfFilePath,
  IN CHAR8*     InputFFSs,
  IN CHAR8*     OutputFilePath,
  IN CHAR8*     FvGuidName
  );


/**
  Encapsulate an FFS section file to an FFS file.

  @param[in]   Type            Type is one FV file type defined in PI spec, which is one type of EFI_FV_FILETYPE_RAW, EFI_FV_FILETYPE_FREEFORM,
                               EFI_FV_FILETYPE_SECURITY_CORE, EFI_FV_FILETYPE_PEIM, EFI_FV_FILETYPE_PEI_CORE, EFI_FV_FILETYPE_DXE_CORE,
                               EFI_FV_FILETYPE_DRIVER, EFI_FV_FILETYPE_APPLICATION, EFI_FV_FILETYPE_COMBINED_PEIM_DRIVER,
                               EFI_FV_FILETYPE_FIRMWARE_VOLUME_IMAGE. This option is required.
  @param[in]   InputFilePath   Section file will be read into this FFS file. This option is required.
  @param[in]   OutputFilePath  The created PI firmware file name. This option is required.
  @param[in]   FileGuid        FileGuid is the unique identifier for this FFS file. This option is required.
  @param[in]   Fixed           Set fixed attribute in FFS file header to indicate that the file may not be moved from its present location.
  @param[in]   SectionAlign    FileAlign specifies FFS file alignment, which only support the following alignment: 8,16,128,512,1K,4K,32K,64K.

  @retval EFI_SUCCESS

**/
EFI_STATUS
LibEncapSectionFileToFFS (
  IN UINT8      Type,
  IN CHAR8*     InputFilePath,
  IN CHAR8*     OutputFilePath,
  IN EFI_GUID   FileGuid,
  IN BOOLEAN    Fixed,
  IN UINT32     SectionAlign
  );

EFI_STATUS
LibCreateNewFdCopy(
  IN CHAR8*    OldFd,
  IN CHAR8*    NewFd
  );


/**
  This function will assemble the filename, directory and extend and return the combined string.
  Like FileName = file1, Dir = c:\temp extend = txt, the output string will be:
  c:\temp\file1.txt.

  @param[in]
  @param[in]
  @param[in]

  @retrun     A string contain all the input information.

**/
CHAR8 *
LibFilenameStrExtended (
  IN CHAR8      *FileName,
  IN CHAR8      *Dir,
  IN CHAR8      *Extend
  );

/**
  Delete a directory and files in it.

  @param[in]   DirName   Name of the directory need to be deleted.

  @return EFI_INVALID_PARAMETER
  @return EFI_SUCCESS
**/
EFI_STATUS
LibRmDir (
  IN  CHAR8*  DirName
  );

/*
  Construct a set of blank chars based on the number.

  @param[in]   Count The number of blank chars.

  @return      A string contained the blank chars.

*/
CHAR8 *
LibConstructBlankChar (
  IN UINT8    Count
  );

/**
  Delete a file.

  @param[in]   FileName   Name of the file need to be deleted.

  @return EFI_INVALID_PARAMETER
  @return EFI_SUCCESS
**/
EFI_STATUS
LibBfmDeleteFile(
  IN   CHAR8    *FileName
);

/**

  Convert a GUID to a string.


  @param[in]   Guid       - Pointer to GUID to print.


  @return The string after convert.

**/
CHAR8 *
LibBfmGuidToStr (
  IN  EFI_GUID  *Guid
);


/**

  Free the whole Fd data structure.

  @param[in]  Fd  The pointer point to the Fd data structure.

**/
VOID
LibBfmFreeFd (
  FIRMWARE_DEVICE *Fd
);

/**
  Generate the compressed section with specific type.
  Type could be EFI_STANDARD_COMPRESSION or EFI_NOT_COMPRESSED

  @param[in]  InputFileName    File name of the raw data.
  @param[in]  OutPutFileName   File name of the sectioned data.
  @param[in]  CompressionType  The compression type.

  @return  EFI_INVALID_PARAMETER
  @return  EFI_ABORTED
  @return  EFI_OUT_OF_RESOURCES
  @return  EFI_SUCCESS

**/
EFI_STATUS
LibGenCompressedSection (
  CHAR8         *InputFileName,
  CHAR8         *OutPutFileName,
  UINT8         CompressionType
);

EFI_HANDLE
LibPreDefinedGuidedTools (
  VOID
);

EFI_STATUS
LibLocateFvViaFvId (
  IN     FIRMWARE_DEVICE     *FdData,
  IN     CHAR8               *FvId,
  IN OUT FV_INFORMATION      **FvInFd
);

EFI_STATUS
LibEncapNewFvFile(
  IN     FV_INFORMATION              *FvInFd,
  IN     CHAR8                       *TemDir,
  OUT    CHAR8                       **OutputFile
);

EFI_STATUS
LibLocateBfv(
  IN     FIRMWARE_DEVICE             *FdData,
  IN OUT CHAR8                       **FvId,
  IN OUT FV_INFORMATION              **FvInFd
);

BOOLEAN
LibCheckPadFfsNotNull (
  IN     EFI_FFS_FILE_HEADER2       *CurrentFile
);

BOOLEAN
LibCheckPadFfsContainFvNameGuid (
  IN     FV_INFORMATION            *CurrentFv,
  IN     EFI_FFS_FILE_HEADER2      *CurrentFile
);

EFI_STATUS
LibFindResetVectorAndFitTableData(
  IN     EFI_FIRMWARE_VOLUME_HEADER  *FvImage,
  IN     EFI_FFS_FILE_HEADER2        *CurrentFile,
  IN OUT FV_INFORMATION              *CurrentFv
);

EFI_STATUS
LibPatchResetVectorAndFitTableData (
IN CHAR8                      *OutputFileName,
IN PATCH_DATA_PAD_FFS         *PatchData
);

/**

  Get the length of a file.

  @param[in]      FileName      The name of a file.

  @retval         The length of file.

**/
UINT64
GetFileSize (
  IN  CHAR8    *FileName
);

/**

  Get the length of BFV PAD file.

  @retval         The length of PAD file.

**/
UINT32
GetBfvPadSize (
  VOID
);
#endif
