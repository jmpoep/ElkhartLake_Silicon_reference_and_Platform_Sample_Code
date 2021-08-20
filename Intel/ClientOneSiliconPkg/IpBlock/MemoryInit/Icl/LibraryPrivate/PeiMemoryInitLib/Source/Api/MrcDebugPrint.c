/** @file
  Output debug messages to the debug port.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include "MrcTypes.h"
#include "MrcDebugHook.h"
#include "MrcGlobal.h"
#include "MrcDebugPrint.h"
#include "MrcMalloc.h"
#ifdef MRC_MINIBIOS_BUILD
#include "uart16550.h"
#endif //MRC_MINIBIOS_BUILD

///
/// These strings are used inside of C-code for non-debug print purposes.
///
const char *gDdrTypeStr[MAX_MRC_DDR_TYPE]  = {"DDR4", "DDR3", "LPDDR3", "LPDDR4", "WIO2", "UNKNOWN"}; // Note: Must align to MrcDdrType

#ifdef MRC_DEBUG_PRINT
///
/// Common Debug String Definition
///
const char Hex[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
const char gErrString[]             = "***ERROR***";
const char gWarnString[]            = "Warning:";
const char gNullPtrErrStr[]         = "Null Pointer Error";
const char gRdString[]              = "Read";
const char gWrString[]              = "Write";
const char gCmdString[]             = "Command";
const char gDataString[]            = "Data";
const char gSocString[]             = "SOC";
const char gDrvStr[]                = "Drive Strength";
const char gChannelStr[]            = "Channel";
const char gRankStr[]               = "Rank";
const char gByteStr[]               = "Byte";
const char gDqOdt[]                 = "DQ ODT";
const char gWrongInputParam[]       = "Wrong Input Parameter";
const char gUnsupportedTechnology[] = "Unsupported DDR Technology";
const char *gIoOdtModeStr[]         = {"Default", "Ctt", "Vtt", "Vddq", "Vss", "Max"}; // Note: must match MRC_ODT_MODE_TYPE values
const char *gFreqPointStr[MrcSaGvPointMax] = {"Low", "Mid", "High"};
const char *gResTypeStr[MAX_RESULT_TYPE] = {"RxV", "RxT", "TxV", "TxT", "RcvEna", "WrLevel", "CmdT", "CmdV"};
const char *gMrcStatusStr[mrcStatusMax] = { // Note: must match MrcStatus
  "mrcSuccess",
  "mrcFail",
  "mrcWrongInputParameter",
  "mrcCasError",
  "mrcTimingError",
  "mrcSenseAmpErr",
  "mrcReadMPRErr",
  "mrcReadLevelingError",
  "mrcWriteLevelingError",
  "mrcDataTimeCentering1DErr",
  "mrcWriteVoltage2DError",
  "mrcReadVoltage2DError",
  "mrcMiscTrainingError",
  "mrcWrError",
  "mrcDimmNotSupport",
  "mrcChannelNotSupport",
  "mrcPiSettingError",
  "mrcDqsPiSettingError",
  "mrcDeviceBusy",
  "mrcFrequencyChange",
  "mrcReutSequenceError",
  "mrcCrcError",
  "mrcFrequencyError",
  "mrcDimmNotExist",
  "mrcColdBootRequired",
  "mrcRoundTripLatencyError",
  "mrcMixedDimmSystem",
  "mrcAliasDetected",
  "mrcRetrain",
  "mrcRtpError",
  "mrcUnsupportedTechnology",
  "mrcMappingError",
  "mrcSocketNotSupported",
  "mrcControllerNotSupported",
  "mrcRankNotSupported",
  "mrcParamSaturation"
};

// This must be aligned to MRC_MarginTypes enum
const char  *gMarginTypesStr[] = {
  "RcvEna", // 0
  "RdT",
  "WrT",
  "WrDqsT",
  "RdV",
  "WrV",
  "WrL",
  "WrTBox",
  "WrTBit",
  "RdTBit",
  "RdVBit", // 10
  "RcX",
  "WrTLp4",
  "CmdT",
  "CmdV",
  "",
  "RdFan2",
  "WrFan2",
  "",
  "",
  "", // 20
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "", // 30
  "",
  "RdFan3",
  "WrFan3",
  "RdTN",
  "RdTP",
  ""
};

/**
  Convert an unsigned integer to a string.

  @param[in]  MrcCall         - Optional when value is 32-bit, required for 64-bit values.
  @param[in]  Value           - Value to work on.
  @param[in]  ValueSize       - The size of the value in bytes with valid values of 4 and 8.
  @param[out] Str             - The return string to print.
  @param[in]  Width           - The width of string to print
  @param[in]  Flags           - The flag type to print out, like '-' or '+'.
  @param[in]  Base            - Number base to work on, as in 10, or 16.

  @retval Number of characters in the resulting string.
**/
UINT32
MrcUintnToStr (
  IN  const MRC_FUNCTION *const MrcCall,
  IN  const UINT64 Value,
  IN  const UINT32 ValueSize,
  OUT char         *Str,
  IN  const UINT32 Width,
  IN  const UINT32 Flags,
  IN  const UINT32 Base
  )
{
  volatile char *Ptr;
  UINT32        Negative;
  UINT64        Int;
  UINT64        Remainder;
  UINT32        i;
  char          Prefix;
  char          c;

  Ptr = Str;
  if ((ValueSize == sizeof (UINT32)) && (Value > MRC_INT32_MAX) && (Flags & MRC_INT_SIGNED)) {
    Int       = (~Value & 0xFFFFFFFF) + 1; /* -Value */
    Negative  = 1;
  } else if ((ValueSize == sizeof (UINT64)) && (Value > MRC_INT64_MAX) && (Flags & MRC_INT_SIGNED)) {
    Int       = ~Value + 1; /* -Value */
    Negative  = 1;
  } else {
    Int       = Value;
    Negative  = 0;
  }

  i = 0;
  do {           /* Generate digits in reverse order */
    i++;
    Remainder = 0;
    if (ValueSize == sizeof (UINT64)) {
      Int = MrcCall->MrcDivU64x64 (Int, Base, &Remainder);
    } else {
      Remainder = (UINT32) Int % Base;
      Int       = (UINT32) Int / Base;
    }
    *Ptr++ = Hex[(UINT32) Remainder]; // only works right now on base 16
    if (Flags & MRC_COMMA_TYPE) {
      if (Base == 16) {
        if (i % 8 == 0) {
          *Ptr++ = '_';
        }
      } else if (Base == 10) {
        if ((i % 3) == 0) {
          *Ptr++ = ',';
        }
      }
    }
  } while (Int > 0);
  if ((*(Ptr - 1) == ',') || (*(Ptr - 1) == '_')) {
    Ptr--;
  }

  if (Negative) {
    *Ptr++ = '-';
    i++;
  } else if (Flags & MRC_PREFIX_SIGN) {
    *Ptr++ = '+';
    i++;
  }

  if (Flags & MRC_PREFIX_ZERO) {
    Prefix = '0';
  } else if (!(Flags & MRC_LEFT_JUSTIFY)) {
    Prefix = ' ';
  } else {
    Prefix = 0x00;
  }

  if (Prefix != 0x00) {
    for (i = (int) (Ptr - Str); i < Width; i++) {
      *Ptr++ = Prefix;
    }
  }

  *Ptr = '\0';

  /* Reverse string */
  while (Str < --Ptr) {
    c       = *Str;
    *Str++  = *Ptr;
    *Ptr    = c;
  }

  return i;
}

/**
  Convert a string to a number.

  @param[in, out] String - String to convert.

  @retval Returns the string in number.
**/
UINT32
MrcStrToNumber (
  IN OUT char **String
  )
{
  UINT32  Sum;
  char    *Str;

  Str = *String;
  if (*Str == '0') {
    Str++;
  }

  Sum = 0;
  while (MRC_ISDIGIT (*Str)) {
    Sum = Sum * 10 + (*Str++ -'0');
  }

  *String = Str;
  return Sum;
}

/**

@brief

  This function converts a character to uppercase.

  @param[in] c - The character to convert.

  @retval Returns the converted character.

**/
unsigned char
Mrctoupper (
  const unsigned char c
  )
{
  return ((c) >= 'a') && ((c) <= 'z') ? ((c) - ('a' - 'A')) : (c);
}

/**

@brief

  This function converts a string to an unsigned long value.
  This function does not implement the full strtoul functionality.

  @param[in]  nptr   - Null-terminated string to convert.
  @param[out] endptr - Pointer to character that stops the scan.
  @param[in]  base   - Number base to use.

  @retval Returns the converted value.

**/
unsigned long
MrcStrtoul (
   const char *nptr,
   char **endptr,
   int base
)
{
  unsigned long value;
  unsigned char count;
  unsigned char hex;
  unsigned char c;
  unsigned char c1;

  value = 0;
  count = 0;
  c     = *nptr;
  c1    = Mrctoupper (*(nptr + 1));
  if ((c == '0') && (c1 == 'X')) {
    nptr += 2;
    hex = 1;
  } else {
    hex = 0;
  }
  while (count < 8) {
    c = Mrctoupper (*nptr);
    if (hex) {
      if (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F'))) {
        nptr++;
        value <<= 4;
        if ((c >= '0') && (c <= '9')) {
          value |= c - '0';
        } else {
          value |= c - 'A' + 10;
        }
      } else {
        break;
      }
    } else {
      if ((c >= '0') && (c <= '9')) {
        nptr++;
        value = (value * 10) + (c - '0');
      } else {
        break;
      }
    }
  }
  if (endptr != NULL) {
    *endptr = (char *) nptr;
  }
  return (value);
}
#endif

/**

@brief

  This function compares two strings, up to count characters or first null character in either string.

  @param[in] String1 - First null-terminated string to compare.
  @param[in] String2 - Second null-terminated string to compare.
  @param[in] Count   - Number of characters to compare, starting from beginning.

  @retval 0 on compare or initial Count value == 0.
  @retval < 0, string1 substring less than string2 substring.
  @retval > 0, string2 substring less than string1 substring.

**/
int
Mrcstrncmp (
  const char *String1,
  const char *String2,
  int        Count
)
{
  int Loop;

  if (Count != 0) {
    for ( Loop = 0; Loop < Count; Loop++) {
      if ((*String1 == '\0') || (*String1 != *String2)) {
        return (*((unsigned char *) String1) - *((unsigned char *) String2));
      }
      String1++;
      String2++;
    }
  }
  return (0);
}

#ifdef MRC_DEBUG_PRINT

/**
  Read line status register from the uart device.

  @param[in] MrcData     - Pointer to the MRC global data area.

  @retval Returns the read status.
**/
char
GetLineStatusRegister (
  MrcParameters *MrcData
  )
{
   UINT8        UartStatus;
   MRC_FUNCTION *MrcCall;

   MrcCall    = MrcData->Inputs.Call.Func;
   UartStatus = MrcCall->MrcIoRead8 (GLOBALCOMPORT + LINE_STATUS);
   return ((char) UartStatus);
}

/**
  Read break status from the uart device.

  @param[in] MrcData  - Pointer to the MRC global data area.

  @retval 1 = break, 0 = no break.
**/
char
GetBreak (
  MrcParameters *MrcData
)
{
  UINT8 UartStatus;

  UartStatus = GetLineStatusRegister (MrcData);
  return ((UartStatus & BREAK_INTERRUPT) ? 1 : 0);
}


/**
  Read char from the uart device.

  @param[in] MrcData  - Pointer to the MRC global data area.

  @retval Returns the read char.
**/
char
getchar (
  MrcParameters *MrcData
  )
{
  MRC_FUNCTION *MrcCall;

  MrcCall = MrcData->Inputs.Call.Func;
  return (((GetLineStatusRegister (MrcData) & DATA_READY) == DATA_READY) ? (char) MrcCall->MrcIoRead8 (GLOBALCOMPORT + RECEIVER_BUFFER) : EOF);
}

/**
  Put char in the uart device.

  @param[in] MrcData  - Pointer to the MRC global data area.
  @param[in] c        - char to put in the uart.

  @retval Returns the ouput char.
**/
int
putchar (
  MrcParameters *MrcData,
  int c
  )
{
   UINT8        UartStatus;
   MRC_FUNCTION *MrcCall;

   MrcCall = MrcData->Inputs.Call.Func;
   // Wait to uart empty
   do {
      UartStatus = MrcCall->MrcIoRead8 (GLOBALCOMPORT + LINE_STATUS);
   } while ((UartStatus & TRANS_HOLDING_REG_EMPTY) != TRANS_HOLDING_REG_EMPTY);

   // Send the char
   MrcCall->MrcIoWrite8 (GLOBALCOMPORT + TRANSMIT_HOLDING, (UINT8) c);

   return c;
}
/**
  This function outputs a string to the default device.

  @param[in] MrcData  - Pointer to the MRC global data area.
  @param[in] String   - The null terminated string to output.

  @retval Returns a nonnegative value if successful.
**/
int
MrcPuts (
  MrcParameters *MrcData,
  const char *String
  )
{
  int count = 0;
#ifdef MRC_MINIBIOS_BUILD
  UartPuts (String);
#endif //MRC_MINIBIOS_BUILD
  while (*String != '\0') {
    putchar (MrcData, *String++);
    count++;
  }
  return (count);
}

/**
  This function reads a null terminated string into a buffer.

  @param[in] MrcData  - Pointer to the MRC global data area.
  @param[in] Buffer   - Buffer to copy string into.
  @param[in] Count    - Size of the buffer, in characters.

  @retval Returns the converted value.

**/
char *
MrcGets (
  MrcParameters *MrcData,
  char *Buffer,
  int  Count
)
{
  char In;
  int  Index;
  char Ctl;

  Index = 0;
  do {
    In  = getchar (MrcData);
    Ctl = isprint (In);
    if ((Ctl > 0) || (In == MRC_CHAR_CR) || (In == DELETE) || (In == BACKSPACE)) {
      if (Ctl > 0) {
        putchar (MrcData, In);
        Buffer[Index++] = In;
      } else if ((In == DELETE) || (In == BACKSPACE)) {
        if (Index > 0) {
          putchar (MrcData, In);
          putchar (MrcData, ' ');
          putchar (MrcData, In);
          Index--;
        }
      } else if (In == MRC_CHAR_CR) {
        putchar (MrcData, In);
        putchar (MrcData, MRC_CHAR_LF);
      }
    }
  } while ((Index < (Count - 1)) && (In != MRC_CHAR_CR));
  Buffer[Index] = '\0';
  return (Buffer);
}

/*++
  Format string using specified format specifier. Limited support for sizes other than
  unsigned 32-bit to save code space. Type overrides like {h | I | I64 | L}
  are not supported.

  @param[in] Format     - String containing characters to print and formatting data.
    %[flags][width]type
    [flags] '-' left align
    [flags] '+' prefix with sign (+ or -)
    [flags] '0' zero pad numbers
    [flags] ' ' prefix black in front of postive numbers
    [flags] 'l' or 'll' used with x, X, u, d, i types to indicate 64-bit value.
    [flags] ','|'_' used with x, X, u, d, i types to add comma (dec) or underscore (hex) to display value. Specify after 'l' flag when 'l' flag is used.
    [width] non negative decimal integer that specifies the width to print a value.
    [width] '*' get the width from a int argument on the stack.
    type    'd'|'i' signed decimal integer
    type    'u' unsigned integer
    type    'x'|'X' hexidecimal using "ABCDEF"
    type    'c' print character
    type    'p' print a pointer to void
    type    's' print a null terminated string
    type    '%%' prints a percent sign
  @param[in] Marker     - Variable argument marker.
  @param[in] BufferSize - Size of the buffer, in bytes.
  @param[in] Buffer     - The buffer.

  @retval Number of characters printed.
**/
int
MrcStringFormatter (
  IN const MRC_FUNCTION     *const MrcCall,
  IN const char *const      Format,
  IN MrcVaList              Marker,
  IN UINT32                 BufferSize,
  IN OUT UINT8              *Buffer
  )
{
  char        *p;
  char        *String;
  UINT64      ArgValue;
  UINT32      ArgSize;
  UINT32      Width;
  UINT32      Flags;
  UINT32      CharCount;

  CharCount = 0;
  if (Format != NULL) {
    for (p = (char *) Format; *p && (CharCount < BufferSize); p++) {
      if (*p != '%') {
        if (*p == MRC_CHAR_LF) {
          //
          // Make LF into CR LF
          //
          MRC_PUTCC (Buffer, MRC_CHAR_CR, CharCount);
        }

        MRC_PUTCC (Buffer, *p, CharCount);
      } else {
        p++;
        //
        // Check for flags
        //
        Flags = 0;
        if (*p == '-') {
          Flags |= MRC_LEFT_JUSTIFY;
        } else if (*p == '+') {
          Flags |= MRC_PREFIX_SIGN;
        } else if (*p == ' ') {
          Flags |= MRC_PREFIX_BLANK;
        }

        if (Flags != 0) {
          p++;
        }
        //
        // Check for width
        //
        if (MRC_ISDIGIT (*p)) {
          if (*p == '0') {
            Flags |= MRC_PREFIX_ZERO;
          }

          Width = MrcStrToNumber (&p);
        } else if (*p == '*') {
          Width = MRC_VA_ARG (Marker, int);
          p++;
        } else {
          Width = 0;
        }

        // Check for "long" or "long long"
        if (*p == 'l') {
          Flags |= MRC_LONG_TYPE;
          if (*(p + 1) == 'l') {  // Treat 'll' same as 'l'
            p++;
          }
          p++;
        }

        if ((*p == ',') || (*p == '_')) {
          Flags |= MRC_COMMA_TYPE;
          p++;
        }
        //
        // Get type
        //
        switch (*p) {
          case 'd':
          case 'i':
            Flags |= MRC_INT_SIGNED;
            // no break;
          case 'u':
            if (Flags & MRC_LONG_TYPE) {
              ArgSize  = sizeof (UINT64);
              ArgValue = (UINT64) MRC_VA_ARG (Marker, UINT64);
            } else {
              ArgSize  = sizeof (UINT32);
              ArgValue = (UINT64) MRC_VA_ARG (Marker, UINT32);
            }
            CharCount = CharCount + MrcUintnToStr (MrcCall, ArgValue, ArgSize, (char *) &Buffer[CharCount], Width, Flags, 10);
            break;

          case 'x':
          case 'X':
          case 'p':
            if (Flags & MRC_LONG_TYPE) {
              ArgSize  = sizeof (UINT64);
              ArgValue = (UINT64) MRC_VA_ARG (Marker, UINT64);
            } else {
              ArgSize  = sizeof (UINT32);
              ArgValue = (UINT64) MRC_VA_ARG (Marker, UINT32);
            }
            CharCount = CharCount + MrcUintnToStr (MrcCall, ArgValue, ArgSize, (char *) &Buffer[CharCount], Width, Flags, 16);
            break;

          case 'c':
            MRC_PUTCC (Buffer, (UINT8) MRC_VA_ARG (Marker, int), CharCount);
            Buffer[CharCount] = '\0';
            break;

          case 's':
            String = (char *) MRC_VA_ARG (Marker, char *);
            while (*String != '\0') {
              if (*String == MRC_CHAR_LF) {
                MRC_PUTCC (Buffer, MRC_CHAR_CR, CharCount);
              }
              MRC_PUTCC (Buffer, *String++, CharCount);
            }
            break;

          case '%':
            MRC_PUTCC (Buffer, '%', CharCount);
#ifndef MRC_MINIBIOS_BUILD
            MRC_PUTCC (Buffer, '%', CharCount); // DEBUG() will treat it as format string, so add one more %
#endif
            break;
        }
      }
    }

    if (CharCount < BufferSize) {
      MRC_PUTCC (Buffer, '\0', CharCount);
    } else {
      Buffer[BufferSize - 1] = '\0';
    }
  }

  return CharCount;
}

/*++

  Print to output stream/device. Limited support for sizes other than
  unsigned 32-bit to save code space. Type overrides like {h | I | I64 | L}
  are not supported.

  @param[in] Debug  - Location to store debug message print information for future use.
  @param[in] Level  - The debug level.
  @param[in] Format - String containing characters to print and formatting data.
    %[flags][width]type
    [flags] '-' left align
    [flags] '+' prefix with sign (+ or -)
    [flags] '0' zero pad numbers
    [flags] ' ' prefix black in front of postive numbers
    [flags] 'l' used with x, X, u, d, i types to indicate 64-bit value.
    [flags] ','|'_' used with x, X, u, d, i types to add comma (dec) or underscore (hex) to display value. Specify after 'l' flag when 'l' flag is used.
    [width] non negative decimal integer that specifies the width to print a value.
    [width] '*' get the width from a int argument on the stack.
    type    'd'|'i' signed decimal integer
    type    'u' unsigned integer
    type    'x'|'X' hexidecimal using "ABCDEF"
    type    'c' print character
    type    'p' print a pointer to void
    type    's' print a null terminated string
    type    '%%' prints a percent sign
  @param[in] Marker - Variable argument marker

  @retval Number of characters printed.
**/
int
MrcPrintfVaList (
  IN MrcDebug *const    Debug,
  IN MrcDebugMsgLevel   Level,
  IN const char *const  Format,
  IN MrcVaList          Marker
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;
  MrcDebug           *Dbg;
  UINT8              *String;
  UINT32             CharCount;
  UINT8              Buffer[MAX_STRING_LENGTH];

  Inputs    = (const MrcInput *) &((MrcParameters *)(Debug->MrcData.Ptr))->Inputs;
  MrcCall   = Inputs->Call.Func;
  CharCount = 0;
  if (Debug->LowestStackAddr.DataN >= (UINTN) Buffer) {
    Debug->LowestStackAddr.DataN = (UINTN) Buffer;
  }
  if ((Format != NULL) && (Level != MSG_LEVEL_NEVER)) {
    if ((Level == MSG_LEVEL_ALL) ||
       ((Debug->Level == MSG_LEVEL_TIME) && (Level == MSG_LEVEL_TIME)) ||
       ((Debug->Level != MSG_LEVEL_TIME) && (Level <= Debug->Level))) {
      CharCount = MrcStringFormatter (MrcCall, Format, Marker, sizeof (Buffer), Buffer);

      //
      // Write the string to the serial log buffer.
      //
      if (Debug->Current.DataN > 0) {
        Dbg    = (MrcDebug *) Debug;
        String = Buffer;
        while (*String != '\0') {
          if (Dbg->Current.DataN >= Dbg->End.DataN) {
            Dbg->Current.DataN = Dbg->Start.DataN;
          }
          *((UINT8 *) (Dbg->Current.Ptr)) = *String++;
          Dbg->Current.DataN += sizeof (char);
        }
        //
        // Write a "end of text" marker to the buffer but don't increment the current pointer.
        //
        if (Dbg->Current.DataN >= Dbg->End.DataN) {
          Dbg->Current.DataN = Dbg->Start.DataN;
        }
        *((UINT8 *) (Dbg->Current.Ptr)) = ASCII_ETX;
      }

      if (Debug->Stream.DataN > 0) {
#ifdef MRC_MINIBIOS_BUILD
        MrcCall->MrcPrintString (Debug->MrcData.Ptr, Buffer);
#else
        MrcCall->MrcPrintString (Buffer);
#endif
      }
    }
  }
  return CharCount;
}

/**
  Function used to get a serial debug print buffer

  @param[in, out] MrcData - The MRC global data area.
**/
void
MrcSerialBufferMalloc (
  MrcParameters *const MrcData
  )
{
  MrcInput *Inputs;

  Inputs = &MrcData->Inputs;
  for (Inputs->SerialBufferSize = Inputs->HeapSize / 2; (Inputs->SerialBufferSize > 0); Inputs->SerialBufferSize /= 2) {
    Inputs->SerialBuffer.Ptr = MrcHeapMalloc (MrcData, Inputs->SerialBufferSize);
    if (Inputs->SerialBuffer.Ptr != 0) {
      break;
    }
  }
}
#endif // MRC_DEBUG_PRINT

/**
  Write formatted data to a string.
  Uses same format specifiers as MrcPrintf().

  @param[in] MrcData  - Pointer to the MRC global data area.
  @param[in] String   - The string buffer to use. Max size is MAX_STRING_LENGTH.
  @param[in] Size     - Buffer size.
  @param[in] Format   - String containing characters to print and formatting data.
  @param[in] ...      - Variable number of arguments to print

  @retval Number of characters printed, including the terminating NULL character.
**/
int
MrcSPrintf (
  IN const MrcParameters * const  MrcData,
  IN OUT char                     *String,
  IN UINT32                       Size,
  IN const char *const            Format,
  ...
  )
{
#ifdef MRC_DEBUG_PRINT
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  MrcVaList           Marker;

  MRC_VA_START (Marker, Format);
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  return MrcStringFormatter (MrcCall, Format, Marker, Size, (UINT8 *) String);
#else
  return 0;
#endif // MRC_DEBUG_PRINT
}

/**
  Print to output stream/device.  Gets the start Marker for the variable arguments
  and calls MrcPrintfVaList().

  @param[in] Debug  - Location to store debug message print information for future use.
  @param[in] Level  - The debug level.
  @param[in] Format - String containing characters to print and formatting data.
    %[flags][width]type
    [flags] '-' left align
    [flags] '+' prefix with sign (+ or -)
    [flags] '0' zero pad numbers
    [flags] ' ' prefix black in front of postive numbers
    [flags] 'l' used with x, X, u, d, i types to indicate 64-bit value.
    [flags] ','|'_' used with x, X, u, d, i types to add comma (dec) or underscore (hex) to display value. Specify after 'l' flag when 'l' flag is used.
    [width] non negative decimal integer that specifies the width to print a value.
    [width] '*' get the width from a int argument on the stack.
    type    'd'|'i' signed decimal integer
    type    'u' unsigned integer
    type    'x'|'X' hexidecimal using "ABCDEF"
    type    'c' print character
    type    'p' print a pointer to void
    type    's' print a null terminated string
    type    '%%' prints a percent sign
  @param[in] ...    - Variable number of arguments to print

  @retval Number of characters printed.
**/
int
MrcPrintf (
  IN MrcDebug *const    Debug,
  IN MrcDebugMsgLevel   Level,
  IN const char *const  Format,
  ...
  )
{
#ifdef MRC_DEBUG_PRINT
  MrcVaList Marker;

  MRC_VA_START (Marker, Format);

  return (Debug != NULL) ? MrcPrintfVaList (Debug, Level, Format, Marker) : 0;
#else
  return 0;
#endif // MRC_DEBUG_PRINT
}

#ifdef MRC_DEBUG_PRINT
/**
  Save the output stream/device. This function must be called prior to debug
  string output.

  @param[in out] Global - Pointer to the MRC global data structure.
  @param[in]     Level  - The debug level to set. Messages at or above this level are printed.
  @param[in]     Stream - Pointer to the stream/device to use.
  @param[in]     Buffer - Pointer to the buffer that will be used to 'tee' the data to.
  @param[in]     Size   - Size of the 'tee' buffer.

  @retval Nothing.
**/
void
MrcFopen (
  IN OUT void *const    Global,
  IN  MrcDebugMsgLevel  Level,
  IN  UINT32            Stream,
  IN  UINTN             Buffer,
  IN  UINT32            Size
  )
{
  static const UINT8 StringBegin[] = "ISV>";
  static const UINT8 StringEnd[]   = "<ISV";
  MrcParameters      *MrcData;
  MrcDebug           *Debug;
  MrcInput           *Inputs;
  const MRC_FUNCTION *MrcCall;

  MrcData             = (MrcParameters *) Global;
  Inputs              = &MrcData->Inputs;
  MrcCall             = Inputs->Call.Func;
  Debug               = &MrcData->Outputs.Debug;
  Debug->MrcData.Ptr  = MrcData;
  Debug->Level        = Level;
  Debug->Stream.DataN = (UINTN) Stream;
  Debug->TopStackAddr.DataN     = Inputs->MrcStackTop.DataN;
  Debug->LowestStackAddr.DataN  = Inputs->MrcStackTop.DataN;
  MrcCall->MrcSetMem ((UINT8 *) &Debug->PostCode[0], sizeof (Debug->PostCode), 0);
  if ((Buffer > 0) && (Size > (sizeof (StringBegin) + sizeof (StringEnd)))) {
    Debug->Start.DataN    = Buffer + (sizeof (StringBegin) - 1);
    Debug->End.DataN      = Buffer + Size - (sizeof (StringEnd) - 1);
    Debug->Current.Data64 = Debug->Start.Data64;
    MrcCall->MrcSetMem ((UINT8 *) Debug->Start.Ptr, Size - (sizeof (StringBegin) + sizeof (StringEnd) - 2), ' ');
    MrcCall->MrcCopyMem ((UINT8 *) Buffer, (UINT8 *) StringBegin, sizeof (StringBegin) - 1);
    MrcCall->MrcCopyMem ((UINT8 *) Debug->End.Ptr, (UINT8 *) StringEnd, sizeof (StringEnd) - 1);
  } else {
    Debug->Start.DataN   = 0;
    Debug->End.DataN     = 0;
    Debug->Current.DataN = 0;
  }

  return;
}

#endif // MRC_DEBUG_PRINT

