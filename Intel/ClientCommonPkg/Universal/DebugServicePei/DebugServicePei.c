/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#include <PiPei.h>
#include <Ppi/DebugService.h>
#include <Guid/StatusCodeDataTypeId.h>
#include <Guid/StatusCodeDataTypeDebug.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>
#include <Library/PcdLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/PrintLib.h>

/**
  Prints a debug message to the debug output device if the specified error level is enabled.

  If any bit in ErrorLevel is also set in DebugPrintErrorLevelLib function
  GetDebugPrintErrorLevel (), then print the message specified by Format and the
  associated variable argument list to the debug output device.

  If Format is NULL, then ASSERT().

  If the length of the message string specificed by Format is larger than the maximum allowable
  record length, then directly return and not print it.

  @param  ErrorLevel  The error level of the debug message.
  @param  Format      Format string for the debug message to print.
  @param  Marker      Variable argument list whose contents are accessed
                      based on the format string specified by Format.

**/
VOID
EFIAPI
PeiDebugPrint (
  IN  UINTN        ErrorLevel,
  IN  CONST CHAR8  *Format,
  IN  VA_LIST      VaListMarker
  )
{
  CONST EFI_PEI_SERVICES       **PeiServices;
  UINT64                       Buffer[(EFI_STATUS_CODE_DATA_MAX_SIZE / sizeof(UINT64)) + 1];
  EFI_STATUS_CODE_STRING_DATA  *StringData;
  CHAR8                        *FormatString;
  UINTN                        CharCount;
  UINTN                        StringDataMaxSize;

  StringData        = (EFI_STATUS_CODE_STRING_DATA *)Buffer;
  FormatString      = (CHAR8 *)(StringData+1);
  StringDataMaxSize = sizeof(Buffer) - sizeof(EFI_STATUS_CODE_STRING_DATA);
  //
  // Fill in EFI_STATUS_CODE_STRING_DATA
  //
  ((EFI_STATUS_CODE_STRING_DATA *) StringData)->DataHeader.HeaderSize    = (UINT16) sizeof(EFI_STATUS_CODE_STRING_DATA);
  ((EFI_STATUS_CODE_STRING_DATA *) StringData)->DataHeader.Size          = (UINT16) StringDataMaxSize;
  ((EFI_STATUS_CODE_STRING_DATA *) StringData)->DataHeader.Type          = gEfiStatusCodeDataTypeStringGuid;
  ((EFI_STATUS_CODE_STRING_DATA *) StringData)->StringType               = EfiStringAscii;
  ((EFI_STATUS_CODE_STRING_DATA *) StringData)->String.Ascii             = FormatString;
  // Transfer debug message to Ascii format
  FormatString[0] = '\0';
  CharCount = AsciiBSPrint (FormatString, StringDataMaxSize, Format, (BASE_LIST) VaListMarker);
  if (CharCount < StringDataMaxSize) {
    ((EFI_STATUS_CODE_STRING_DATA *) StringData)->DataHeader.Size        = (UINT16) CharCount;
  }

  //
  // Send the StringData record
  //
  PeiServices = GetPeiServicesTablePointer ();
  (*PeiServices)->ReportStatusCode (
                       PeiServices,
                       EFI_DEBUG_CODE,
                       EFI_SOFTWARE_PEI_MODULE,
                       (UINT32) ErrorLevel,
                       (EFI_GUID *) &gEfiStatusCodeDataTypeStringGuid,
                       (EFI_STATUS_CODE_DATA *) &(((EFI_STATUS_CODE_STRING_DATA *) StringData)->DataHeader.HeaderSize)
                       );

}

/**
  Prints an assert message containing a filename, line number, and description.
  This may be followed by a breakpoint or a dead loop.

  Print a message of the form "ASSERT <FileName>(<LineNumber>): <Description>\n"
  to the debug output device.  If DEBUG_PROPERTY_ASSERT_BREAKPOINT_ENABLED bit of
  PcdDebugProperyMask is set then CpuBreakpoint() is called. Otherwise, if
  DEBUG_PROPERTY_ASSERT_DEADLOOP_ENABLED bit of PcdDebugProperyMask is set then
  CpuDeadLoop() is called.  If neither of these bits are set, then this function
  returns immediately after the message is printed to the debug output device.
  DebugAssert() must actively prevent recursion.  If DebugAssert() is called while
  processing another DebugAssert(), then DebugAssert() must return immediately.

  If FileName is NULL, then a <FileName> string of "(NULL) Filename" is printed.
  If Description is NULL, then a <Description> string of "(NULL) Description" is printed.

  @param  FileName     Pointer to the name of the source file that generated the assert condition.
  @param  LineNumber   The line number in the source file that generated the assert condition
  @param  Description  Pointer to the description of the assert condition.
  @param  DebugPropertyMask  PropertyMask to the description of the assert.

**/
VOID
EFIAPI
PeiDebugAssert (
  IN CONST CHAR8  *FileName,
  IN UINTN        LineNumber,
  IN CONST CHAR8  *Description,
  IN UINT8        DebugPropertyMask
  )
{
  UINT64                 Buffer[EFI_STATUS_CODE_DATA_MAX_SIZE / sizeof(UINT64)];
  EFI_DEBUG_ASSERT_DATA  *AssertData;
  UINTN                  HeaderSize;
  UINTN                  TotalSize;
  CHAR8                  *Temp;
  UINTN                  FileNameSize;
  UINTN                  DescriptionSize;

  //
  // Get string size
  //
  HeaderSize       = sizeof (EFI_DEBUG_ASSERT_DATA);
  FileNameSize     = AsciiStrSize (FileName);
  DescriptionSize  = AsciiStrSize (Description);

  //
  // Make sure it will all fit in the passed in buffer.
  //
  if (HeaderSize + FileNameSize + DescriptionSize > sizeof (Buffer)) {
    //
    // FileName + Description is too long to be filled into buffer.
    //
    if (HeaderSize + FileNameSize < sizeof (Buffer)) {
      //
      // Description has enough buffer to be truncated.
      //
      DescriptionSize = sizeof (Buffer) - HeaderSize - FileNameSize;
    } else {
      //
      // FileName is too long to be filled into buffer.
      // FileName will be truncated. Reserved one byte for Description NULL terminator.
      //
      DescriptionSize = 1;
      FileNameSize    = sizeof (Buffer) - HeaderSize - DescriptionSize;
    }
  }

  //
  // Fill in EFI_DEBUG_ASSERT_DATA
  //
  AssertData = (EFI_DEBUG_ASSERT_DATA *)Buffer;
  AssertData->LineNumber = (UINT32)LineNumber;
  TotalSize  = sizeof (EFI_DEBUG_ASSERT_DATA);

  //
  // Copy Ascii FileName including NULL terminator.
  //
  Temp = CopyMem (AssertData + 1, FileName, FileNameSize);
  Temp[FileNameSize - 1] = 0;
  TotalSize += FileNameSize;

  //
  // Copy Ascii Description include NULL terminator.
  //
  Temp = CopyMem (Temp + FileNameSize, Description, DescriptionSize);
  Temp[DescriptionSize - 1] = 0;
  TotalSize += DescriptionSize;

  REPORT_STATUS_CODE_EX (
    (EFI_ERROR_CODE | EFI_ERROR_UNRECOVERED),
    (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_EC_ILLEGAL_SOFTWARE_STATE),
    0,
    NULL,
    NULL,
    AssertData,
    TotalSize
    );

  //
  // Generate a Breakpoint, DeadLoop, or NOP based on PCD settings
  //
  if ((DebugPropertyMask & DEBUG_PROPERTY_ASSERT_BREAKPOINT_ENABLED) != 0) {
    CpuBreakpoint ();
  } else if ((DebugPropertyMask & DEBUG_PROPERTY_ASSERT_DEADLOOP_ENABLED) != 0) {
    CpuDeadLoop ();
  }
}

DEBUG_SERVICE_PPI mDebugServicePpi = {
  PeiDebugPrint,
  PeiDebugAssert
};

EFI_PEI_PPI_DESCRIPTOR mPpiList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gDebugServicePpiGuid,
    (VOID *) &mDebugServicePpi
  }
};

/**
  Main entry

  @param[in]  FileHandle              Handle of the file being invoked.
  @param[in]  PeiServices             Pointer to PEI Services table.

  @retval EFI_SUCCESS Install function successfully.

**/
EFI_STATUS
EFIAPI
DebugServiceEntryPoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS               Status;

  //
  // Register for a callback once memory has been initialized.
  //
  Status = PeiServicesInstallPpi (&mPpiList[0]);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}
