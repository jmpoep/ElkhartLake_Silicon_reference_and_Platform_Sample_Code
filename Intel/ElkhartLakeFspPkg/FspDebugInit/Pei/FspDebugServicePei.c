/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>
#include <Library/PrintLib.h>
#include <Library/SerialPortLib.h>
#include <Library/DebugPrintErrorLevelLib.h>
#include <Library/FspDebugLibService/FspDebugLibService.h>
#include <Library/FspInfoLib.h>
#include <Library/TraceHubDebugLib.h>

#define STATUS_CODE_USE_TRACEHUB   BIT5

UINT8
EFIAPI
GetDebugInterfaceFlags (
  VOID
  );

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
FspDebugPrint (
  IN  UINTN        ErrorLevel,
  IN  CONST CHAR8  *Format,
  IN  VA_LIST      VaListMarker
  )
{
  CHAR8                     Buffer[MAX_DEBUG_MESSAGE_LENGTH];
  TRACE_HUB_SEVERITY_TYPE   TraceHubSeverityLevel;

  //
  // If Format is NULL, then ASSERT().
  //
  ASSERT (Format != NULL);

  //
  // Convert the DEBUG() message to an ASCII String
  //
  AsciiVSPrint (Buffer, sizeof (Buffer), Format, VaListMarker);

  //
  // Send the print string to a Serial Port
  //
  SerialPortWrite ((UINT8 *)Buffer, AsciiStrLen (Buffer));

  //
  // Send the print string to Trace Hub
  //
  if ((GetDebugInterfaceFlags() & STATUS_CODE_USE_TRACEHUB) &&
      (FeaturePcdGet (PcdTraceHubEnable) == TRUE)) {
    //
    // EDK ErrorLevel to TraceHub Severity Mapping
    //
    TraceHubSeverityLevel = SeverityNormal;
    if (ErrorLevel & EFI_D_ERROR) {
      TraceHubSeverityLevel = SeverityError;
    } else if (ErrorLevel & EFI_D_WARN) {
      TraceHubSeverityLevel = SeverityWarning;
    }

    TraceHubDebugWrite (TraceHubSeverityLevel, (UINT8 *)Buffer, AsciiStrLen (Buffer));
  }
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
FspDebugAssert (
  IN CONST CHAR8  *FileName,
  IN UINTN        LineNumber,
  IN CONST CHAR8  *Description,
  IN UINT8        DebugPropertyMask
  )
{
  CHAR8  Buffer[MAX_DEBUG_MESSAGE_LENGTH];

  //
  // Generate the ASSERT() message in Ascii format
  //
  AsciiSPrint (Buffer, sizeof (Buffer), "ASSERT %a(%d): %a\n", FileName, LineNumber, Description);

  //
  // Send the print string to the Console Output device
  //
  SerialPortWrite ((UINT8 *)Buffer, AsciiStrLen (Buffer));

   //
   // Send the print string to Trace Hub
   //
   if ((GetDebugInterfaceFlags() & STATUS_CODE_USE_TRACEHUB) &&
       (FeaturePcdGet (PcdTraceHubEnable) == TRUE)) {
     TraceHubDebugWrite (SeverityError, (UINT8 *)Buffer, AsciiStrLen (Buffer));
   }

  //
  // Generate a Breakpoint, DeadLoop, or NOP based on PCD settings
  //
  if ((DebugPropertyMask & DEBUG_PROPERTY_ASSERT_BREAKPOINT_ENABLED) != 0) {
    CpuBreakpoint ();
  } else if ((DebugPropertyMask & DEBUG_PROPERTY_ASSERT_DEADLOOP_ENABLED) != 0) {
    CpuDeadLoop ();
  }
}

DEBUG_SERVICE_PPI mFspDebugServicePpi = {
  FspDebugPrint,
  FspDebugAssert
};

EFI_PEI_PPI_DESCRIPTOR mPpiList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gFspDebugServicePpiGuid,
    (VOID *) &mFspDebugServicePpi
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
  FSP_INFO_HOB             FspInfo;

  //
  // Dump FSP Information
  //
  Status = GetFspInfo (&FspInfo);
  if (! EFI_ERROR (Status)) {
    DumpFspInfo (&FspInfo);
  }
  //
  // Register for a callback once memory has been initialized.
  //
  Status = SerialPortInitialize ();
  ASSERT_EFI_ERROR (Status);
  Status = PeiServicesInstallPpi (&mPpiList[0]);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}
