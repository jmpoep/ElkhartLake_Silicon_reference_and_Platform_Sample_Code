/** @file
  Instance of Debug Library.

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

#include <Base.h>
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugPrintErrorLevelLib.h>
#include <Library/SerialPortLib.h>
#include <Library/TraceHubDebugLib.h>
#include <FspmUpd.h>
#include <Library/FspCommonLib.h>

//
// Define the maximum debug and assert message length that this library supports
//
#define MAX_DEBUG_MESSAGE_LENGTH  0x100

//---------------------------------------------
// Serial Debug Interfaces
//---------------------------------------------
#define STATUS_CODE_USE_ISA_SERIAL BIT1
#define STATUS_CODE_USE_SERIALIO   BIT4
#define STATUS_CODE_USE_TRACEHUB   BIT5

UINT8
EFIAPI
GetDebugInterfaceFlags (
  VOID
  );

/**
  The constructor function initialize the Debug Port Library

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/
RETURN_STATUS
EFIAPI
BaseDebugLibDebugPortConstructor (
  VOID
  )
{
  FSPM_UPD        *FspmUpd;
  UINT8           StatusCodeFlags;
  FSP_GLOBAL_DATA *FspGlobalData;

  //
  // Check the initialization of FSP Global Data Pointer before using it
  // Constructor will call this first time before FSP Global Data pointer is initialized
  // skip initialization that time. It will be reinitialized by FSP, once FSP Gloabl Data pointer
  // is ready
  //
  FspGlobalData = GetFspGlobalDataPointer ();
  if ((UINTN) FspGlobalData == 0x00 || (UINTN) FspGlobalData == 0xFFFFFFFF) {
    return RETURN_SUCCESS;
  } else if (FspGlobalData->Signature != FSP_GLOBAL_DATA_SIGNATURE) {
    return RETURN_SUCCESS;
  }

  FspmUpd = FspGlobalData->MemoryInitUpdPtr;
  if (FspmUpd == NULL) {
    return RETURN_SUCCESS;
  }

  StatusCodeFlags = FspmUpd->FspmConfig.PcdDebugInterfaceFlags;

  if (StatusCodeFlags & STATUS_CODE_USE_ISA_SERIAL) {
    SerialPortInitialize ();
  }

  return RETURN_SUCCESS;
}

/**
  Prints a debug message to the debug output device if the specified error level is enabled.

  If any bit in ErrorLevel is also set in DebugPrintErrorLevelLib function
  GetDebugPrintErrorLevel (), then print the message specified by Format and the
  associated variable argument list to the debug output device.

  If Format is NULL, then ASSERT().

  @param  ErrorLevel  The error level of the debug message.
  @param  Format      Format string for the debug message to print.
  @param  ...         Variable argument list whose contents are accessed
                      based on the format string specified by Format.

**/
VOID
EFIAPI
DebugPrint (
  IN  UINTN        ErrorLevel,
  IN  CONST CHAR8  *Format,
  ...
  )
{
  CHAR8                     Buffer[MAX_DEBUG_MESSAGE_LENGTH];
  VA_LIST                   Marker;
  TRACE_HUB_SEVERITY_TYPE   TraceHubSeverityLevel;

  //
  // If Format is NULL, then ASSERT().
  //
  ASSERT (Format != NULL);

  //
  // Check driver debug mask value and global mask
  //
  if ((ErrorLevel & GetDebugPrintErrorLevel ()) == 0) {
    return;
  }

  //
  // Convert the DEBUG() message to an ASCII String
  //
  VA_START (Marker, Format);
  AsciiVSPrint (Buffer, sizeof (Buffer), Format, Marker);
  VA_END (Marker);

  //
  // Send the print string to Debug Port
  //
  if ((GetDebugInterfaceFlags() & STATUS_CODE_USE_ISA_SERIAL) || (GetDebugInterfaceFlags() & STATUS_CODE_USE_SERIALIO)) {
    SerialPortWrite ((UINT8 *)Buffer, AsciiStrLen (Buffer));
  }

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

**/
VOID
EFIAPI
DebugAssert (
  IN CONST CHAR8  *FileName,
  IN UINTN        LineNumber,
  IN CONST CHAR8  *Description
  )
{
  CHAR8           Buffer[MAX_DEBUG_MESSAGE_LENGTH];

  //
  // Generate the ASSERT() message in Ascii format
  //
  AsciiSPrint (Buffer, sizeof (Buffer), "ASSERT [%a] %a(%d): %a\n", gEfiCallerBaseName, FileName, LineNumber, Description);

  //
  // Send the print string to Debug Port
  //
  if ((GetDebugInterfaceFlags() & STATUS_CODE_USE_ISA_SERIAL) || (GetDebugInterfaceFlags() & STATUS_CODE_USE_SERIALIO)) {
    SerialPortWrite ((UINT8 *)Buffer, AsciiStrLen (Buffer));
  }

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
  if ((PcdGet8 (PcdDebugPropertyMask) & DEBUG_PROPERTY_ASSERT_BREAKPOINT_ENABLED) != 0) {
    CpuBreakpoint ();
  } else if ((PcdGet8 (PcdDebugPropertyMask) & DEBUG_PROPERTY_ASSERT_DEADLOOP_ENABLED) != 0) {
    CpuDeadLoop ();
  }
}


/**
  Fills a target buffer with PcdDebugClearMemoryValue, and returns the target buffer.

  This function fills Length bytes of Buffer with the value specified by
  PcdDebugClearMemoryValue, and returns Buffer.

  If Buffer is NULL, then ASSERT().
  If Length is greater than (MAX_ADDRESS - Buffer + 1), then ASSERT().

  @param   Buffer  Pointer to the target buffer to be filled with PcdDebugClearMemoryValue.
  @param   Length  Number of bytes in Buffer to fill with zeros PcdDebugClearMemoryValue.

  @return  Buffer  Pointer to the target buffer filled with PcdDebugClearMemoryValue.

**/
VOID *
EFIAPI
DebugClearMemory (
  OUT VOID  *Buffer,
  IN UINTN  Length
  )
{
  ASSERT (Buffer != NULL);

  return SetMem (Buffer, Length, PcdGet8 (PcdDebugClearMemoryValue));
}


/**
  Returns TRUE if ASSERT() macros are enabled.

  This function returns TRUE if the DEBUG_PROPERTY_DEBUG_ASSERT_ENABLED bit of
  PcdDebugProperyMask is set.  Otherwise FALSE is returned.

  @retval  TRUE    The DEBUG_PROPERTY_DEBUG_ASSERT_ENABLED bit of PcdDebugProperyMask is set.
  @retval  FALSE   The DEBUG_PROPERTY_DEBUG_ASSERT_ENABLED bit of PcdDebugProperyMask is clear.

**/
BOOLEAN
EFIAPI
DebugAssertEnabled (
  VOID
  )
{
  return (BOOLEAN) ((PcdGet8 (PcdDebugPropertyMask) & DEBUG_PROPERTY_DEBUG_ASSERT_ENABLED) != 0);
}


/**
  Returns TRUE if DEBUG() macros are enabled.

  This function returns TRUE if the DEBUG_PROPERTY_DEBUG_PRINT_ENABLED bit of
  PcdDebugProperyMask is set.  Otherwise FALSE is returned.

  @retval  TRUE    The DEBUG_PROPERTY_DEBUG_PRINT_ENABLED bit of PcdDebugProperyMask is set.
  @retval  FALSE   The DEBUG_PROPERTY_DEBUG_PRINT_ENABLED bit of PcdDebugProperyMask is clear.

**/
BOOLEAN
EFIAPI
DebugPrintEnabled (
  VOID
  )
{
  return (BOOLEAN) ((PcdGet8 (PcdDebugPropertyMask) & DEBUG_PROPERTY_DEBUG_PRINT_ENABLED) != 0);
}


/**
  Returns TRUE if DEBUG_CODE() macros are enabled.

  This function returns TRUE if the DEBUG_PROPERTY_DEBUG_CODE_ENABLED bit of
  PcdDebugProperyMask is set.  Otherwise FALSE is returned.

  @retval  TRUE    The DEBUG_PROPERTY_DEBUG_CODE_ENABLED bit of PcdDebugProperyMask is set.
  @retval  FALSE   The DEBUG_PROPERTY_DEBUG_CODE_ENABLED bit of PcdDebugProperyMask is clear.

**/
BOOLEAN
EFIAPI
DebugCodeEnabled (
  VOID
  )
{
  return (BOOLEAN) ((PcdGet8 (PcdDebugPropertyMask) & DEBUG_PROPERTY_DEBUG_CODE_ENABLED) != 0);
}


/**
  Returns TRUE if DEBUG_CLEAR_MEMORY() macro is enabled.

  This function returns TRUE if the DEBUG_PROPERTY_CLEAR_MEMORY_ENABLED bit of
  PcdDebugProperyMask is set.  Otherwise FALSE is returned.

  @retval  TRUE    The DEBUG_PROPERTY_CLEAR_MEMORY_ENABLED bit of PcdDebugProperyMask is set.
  @retval  FALSE   The DEBUG_PROPERTY_CLEAR_MEMORY_ENABLED bit of PcdDebugProperyMask is clear.

**/
BOOLEAN
EFIAPI
DebugClearMemoryEnabled (
  VOID
  )
{
  return (BOOLEAN) ((PcdGet8 (PcdDebugPropertyMask) & DEBUG_PROPERTY_CLEAR_MEMORY_ENABLED) != 0);
}

/**
  Returns TRUE if any one of the bit is set both in ErrorLevel and PcdFixedDebugPrintErrorLevel.

  This function compares the bit mask of ErrorLevel and PcdFixedDebugPrintErrorLevel.

  @retval  TRUE    Current ErrorLevel is supported.
  @retval  FALSE   Current ErrorLevel is not supported.

**/
BOOLEAN
EFIAPI
DebugPrintLevelEnabled (
  IN  CONST UINTN        ErrorLevel
  )
{
  return (BOOLEAN) ((ErrorLevel & PcdGet32(PcdFixedDebugPrintErrorLevel)) != 0);
}
