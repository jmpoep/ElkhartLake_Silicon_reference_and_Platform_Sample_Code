//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
This tool generates the BIOS ID binary file using the data from the configuration file.

Copyright (c) 1999 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "GenBiosId.h"

char          InputFileName[FILE_NAME_SIZE];
char          OutputFileName[FILE_NAME_SIZE];
char          OutputBatchFileName[FILE_NAME_SIZE];

FILE          *InputFile;
FILE          *OutputFile;
FILE          *OutputBatchFile;

BIOS_ID_IMAGE BiosIdImage = {
  { '$', 'I', 'B', 'I', 'O', 'S', 'I', '$' },
  {
    { ATOU (' '), ATOU (' '), ATOU (' '), ATOU (' '), ATOU (' '), ATOU (' '), ATOU (' ') },
    ATOU (' '),
    ATOU ('.'),
    { ATOU (' '), ATOU (' '), ATOU (' ') },
    ATOU ('.'),
    { ATOU ('0'), ATOU ('0'), ATOU ('0'), ATOU ('0') },
    ATOU ('.'),
    ATOU (' '),
    { ATOU ('0'), ATOU ('0') },
    ATOU ('.'),
    { ATOU ('0'), ATOU ('0'), ATOU ('0'), ATOU ('0'), ATOU ('0'),
      ATOU ('0'), ATOU ('0'), ATOU ('0'), ATOU ('0'), ATOU ('0') },
    ATOU ('\0')
  }
};

int
main (
  IN  int   argc,
  IN  CHAR8 *argv[]
  )
/*++

Routine Description:

Arguments:

  argc  - Number of command-line arguments.

  argv  - Array of command-line arguments.

Returns:

  0   - The operation completed successfully.

  -1  - An error occurred.

--*/
{
  int Status;

  Status = 0;

  PrintBanner ();

  if ((argc != 5) && (argc != 7)) {
    PrintUsage ();
    Status = -1;
    goto Done;
  }

  if (strcmp (argv[1], "-i") == 0) {
    if (strlen (argv[2])> sizeof (InputFileName) - 1) {
      printf ("The InputFileName %s is too long \n", argv[2]);
      Status = -1;
      goto Done;
    }
    strncpy (InputFileName, argv[2], sizeof (InputFileName) - 1);
    InputFileName[sizeof (InputFileName) - 1] = 0;
  } else {
    PrintUsage ();
    Status = -1;
    goto Done;
  }

  if (strcmp (argv[3], "-o") == 0) {
    if (strlen (argv[4])> sizeof (OutputFileName) - 1) {
      printf ("OutputFileName %s is too long \n", argv[4]);
      Status = -1;
      goto Done;
    }
    strncpy (OutputFileName, argv[4], sizeof (OutputFileName) - 1);
    OutputFileName[sizeof (OutputFileName) - 1] = 0;
  } else {
    PrintUsage ();
    Status = -1;
    goto Done;
  }

  if (argc == 7) {
    if (strcmp (argv[5], "-ob") == 0) {
      if (strlen (argv[6])> sizeof (OutputBatchFileName) - 1) {
        printf ("The OutputBatchFileName %s is too long \n", argv[6]);
        Status = -1;
        goto Done;
      }
      strncpy (OutputBatchFileName, argv[6], sizeof (OutputBatchFileName) - 1);
      OutputBatchFileName[sizeof (OutputBatchFileName) - 1] = 0;
    } else {
      PrintUsage ();
      Status = -1;
      goto Done;
    }
  }

  InputFile   = NULL;
  OutputFile  = NULL;
  OutputBatchFile = NULL;

  InputFile   = fopen (InputFileName, "r");
  if (InputFile == NULL) {
    printf ("Error opening input file: %s\n", InputFileName);
    Status = -1;
    goto Done;
  }

  OutputFile  = fopen (OutputFileName, "wb");
  if (OutputFile == NULL) {
    printf ("Error creating output file: %s\n", OutputFileName);
    Status = -1;
    goto Done;
  }

  if (argc == 7) {
    OutputBatchFile = fopen (OutputBatchFileName, "wb");
    if (OutputBatchFile == NULL) {
      printf ("Error creating output batch file: %s\n", OutputBatchFileName);
      Status = -1;
      goto Done;
    }
  }

  if (ParseInputFile () != EFI_SUCCESS) {
    printf ("Invalid config file format: %s\n", InputFileName);
    Status = -1;
    goto Done;
  }

  if (WriteOutputFile () != EFI_SUCCESS) {
    printf ("Can't write output file: %s\n", OutputFileName);
    Status = -1;
    goto Done;
  }

  if (argc == 7) {
    if (WriteOutputBatchFile () != EFI_SUCCESS) {
      printf ("Can't write output batch file: %s\n", OutputBatchFileName);
      Status = -1;
      goto Done;
    }
  }

  printf ("BIOS ID created: ");
  PrintUnicodeString ((CHAR16 *)(&(BiosIdImage.BiosIdString)));
  printf ("\n");
  printf ("BIOS ID binary file created: %s\n", OutputFileName);

Done:

  if (InputFile != NULL) {
    fclose (InputFile);
  }

  if (OutputFile != NULL) {
    fclose (OutputFile);
  }

  if (OutputBatchFile != NULL) {
    fclose (OutputBatchFile);
  }

  return Status;
}

VOID
PrintBanner (
  VOID
  )
/*++

Routine Description:

Arguments:

Returns:

--*/
{
  printf ("\n");
  printf ("GenBiosId utility, version: v2.0c 03/01/2018   \n");
  printf ("Copyright (c) 2005 - 2018, Intel Corporation. All rights reserved.   \n");
  printf ("\n");
}

VOID
PrintUsage (
  VOID
  )
/*++

Routine Description:

Arguments:

Returns:

--*/
{
  printf ("Usage:\n");
  printf ("GenBiosId -i ConfigFile -o OutputFile [-ob OutputBatchFile] \n");
  printf ("\n");
}

EFI_STATUS
ParseInputFile (
  VOID
  )
/*++

Routine Description:

  Parse the BIOS ID definition file and fill the BIOS ID structure, including timestamp.

Arguments:

Returns:

  EFI_SUCCESS           - The input file was parsed successfully.

  EFI_INVALID_PARAMETER - The input file has incorrect format.

--*/
{
  CHAR8   StrLine[MAX_LINE_SIZE];
  CHAR8   StrFieldName[MAX_LINE_SIZE];
  CHAR8   StrFieldValue[MAX_LINE_SIZE];
  CHAR8   *Str;
  UINT16  FieldsSet;
  CHAR8   FormatString[MAX_FORMAT_STRING_SIZE];

  FieldsSet = 0;
  Str       = NULL;

  //
  // Generate the format string for sscanf() function.
  //
  sprintf (FormatString, "%%%us = %%%us", (unsigned int) sizeof (StrFieldName) - 1, (unsigned int) sizeof (StrFieldValue) - 1);

  while (fgets (StrLine, sizeof (StrLine) - 1, InputFile) != NULL) {
    Str = StripLeadingWhiteSpace (StrLine);

    //
    // Check for whitespace string.
    //
    if (Str == NULL) {
      continue;
    }

    //
    // Check for comment string.
    //
    if (*Str == '#') {
      continue;
    }

    if (sscanf (Str, FormatString, StrFieldName, StrFieldValue) != 2) {
      continue;
    }

    if (strcmp (StrFieldName, NAME_BOARD_ID) == 0) {
      if (strlen (StrFieldValue) == CHARS_BOARD_ID) {
        ConvertToUnicode (StrFieldValue, BiosIdImage.BiosIdString.BoardId);
        FieldsSet |= FIELD_BOARD_ID;
      } else {
        printf ("Error: value of %s should have exactly %d chars\n", NAME_BOARD_ID, CHARS_BOARD_ID);
        return EFI_INVALID_PARAMETER;
      }
    }

    if (strcmp (StrFieldName, NAME_BOARD_REV) == 0) {
      if (strlen (StrFieldValue) == CHARS_BOARD_REV) {
        ConvertToUnicode (StrFieldValue, &(BiosIdImage.BiosIdString.BoardRev));
        FieldsSet |= FIELD_BOARD_REV;
      } else {
        printf ("Error: value of %s should have exactly %d chars\n", NAME_BOARD_REV, CHARS_BOARD_REV);
        return EFI_INVALID_PARAMETER;
      }
    }

    if (strcmp (StrFieldName, NAME_BOARD_EXT) == 0) {
      if (strlen (StrFieldValue) == CHARS_BOARD_EXT) {
        ConvertToUnicode (StrFieldValue, BiosIdImage.BiosIdString.BoardExt);
        FieldsSet |= FIELD_BOARD_EXT;
      } else {
        printf ("Error: value of %s should have exactly %d chars\n", NAME_BOARD_EXT, CHARS_BOARD_EXT);
        return EFI_INVALID_PARAMETER;
      }
    }

    if (strcmp (StrFieldName, NAME_BUILD_TYPE) == 0) {
      if (strlen (StrFieldValue) == CHARS_BUILD_TYPE) {
        if ((strcmp (StrFieldValue, "D") == 0) ||
            (strcmp (StrFieldValue, "A") == 0) ||
            (strcmp (StrFieldValue, "B") == 0) ||
            (strcmp (StrFieldValue, "P") == 0)) {
          ConvertToUnicode (StrFieldValue, &(BiosIdImage.BiosIdString.BuildType));
          FieldsSet |= FIELD_BUILD_TYPE;
        } else {
          printf ("Error: value of %s should be one of %s, %s, %s or %s\n", NAME_BUILD_TYPE, "D", "A", "B", "P");
          return EFI_INVALID_PARAMETER;
        }
      } else {
        printf ("Error: value of %s should have exactly %d chars\n", NAME_BUILD_TYPE, CHARS_BUILD_TYPE);
        return EFI_INVALID_PARAMETER;
      }
    }

    if (strcmp (StrFieldName, NAME_VERSION_MAJOR) == 0) {
      if (strlen (StrFieldValue) == CHARS_VERSION_MAJOR) {
        ConvertToUnicode (StrFieldValue, BiosIdImage.BiosIdString.VersionMajor);
        FieldsSet |= FIELD_VERSION_MAJOR;
      } else {
        printf ("Error: value of %s should have exactly %d chars\n", NAME_VERSION_MAJOR, CHARS_VERSION_MAJOR);
        return EFI_INVALID_PARAMETER;
      }
    }

    if (strcmp (StrFieldName, NAME_VERSION_MINOR) == 0) {
      if (strlen (StrFieldValue) == CHARS_VERSION_MINOR) {
        ConvertToUnicode (StrFieldValue, BiosIdImage.BiosIdString.VersionMinor);
        FieldsSet |= FIELD_VERSION_MINOR;
      } else {
        printf ("Error: value of %s should have exactly %d chars\n", NAME_VERSION_MINOR, CHARS_VERSION_MINOR);
        return EFI_INVALID_PARAMETER;
      }
    }

    if (strcmp (StrFieldName, NAME_DATE) == 0) {
      if (strlen (StrFieldValue) == CHARS_DATE) {
        ConvertToUnicode (StrFieldValue, BiosIdImage.BiosIdString.TimeStamp);
        FieldsSet |= FIELD_DATE;
      } else {
        printf ("Error: value of %s should have exactly %d chars\n", NAME_DATE, CHARS_DATE);
        return EFI_INVALID_PARAMETER;
      }
    }

    if (strcmp (StrFieldName, NAME_TIME) == 0) {
      if (strlen (StrFieldValue) == CHARS_TIME) {
        ConvertToUnicode (StrFieldValue, &(BiosIdImage.BiosIdString.TimeStamp[CHARS_DATE]));
        FieldsSet |= FIELD_TIME;
      } else {
        printf ("Error: value of %s should have exactly %d chars\n", NAME_TIME, CHARS_TIME);
        return EFI_INVALID_PARAMETER;
      }
    }

  }

  if ((FieldsSet & (FIELD_DATE | FIELD_TIME)) != (FIELD_DATE | FIELD_TIME)) {
    //
    // Fill the timestamp.
    //
    FillTimeStamp (BiosIdImage.BiosIdString.TimeStamp);
    FieldsSet |= (FIELD_DATE | FIELD_TIME);
  }

  //
  // Exit if not all fields were supplied.
  //
  if ((FieldsSet & FIELD_ALL) != FIELD_ALL) {
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
WriteOutputFile (
  VOID
  )
/*++

Routine Description:

  Write the BIOS ID structure to the output file.

Arguments:

Returns:

  EFI_SUCCESS       - The output file was created successfully.

  EFI_DEVICE_ERROR  - There was a file write error.

--*/
{
  if (fwrite (&BiosIdImage, sizeof (BIOS_ID_IMAGE), 1, OutputFile) != 1) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
WriteOutputBatchFile (
  VOID
  )
/*++

Routine Description:

  Write "SET BIOS_ID=" and BIOS ID string to the batch file.

Arguments:

Returns:

  EFI_SUCCESS       - The output batch file was created successfully.

  EFI_DEVICE_ERROR  - There was a file write error.

--*/
{
#ifndef __GNUC__
  CHAR8 BatchFileContent[MAX_LINE_SIZE] = "SET BIOS_ID=";
#else
  CHAR8 BatchFileContent[MAX_LINE_SIZE] = "export BIOS_ID=";
#endif

  CHAR8 BiosIdString[sizeof (BIOS_ID_STRING)];

  ConvertToAscii ((CHAR16 *) (&(BiosIdImage.BiosIdString)), BiosIdString);
  strcat (BatchFileContent, BiosIdString);

  if (fwrite (BatchFileContent, strlen (BatchFileContent), 1, OutputBatchFile) != 1) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

CHAR8 *
StripLeadingWhiteSpace (
  IN CHAR8 *StrInput
  )
/*++

Routine Description:

  Strip the leading whitespoace off the given ASCII string.

Arguments:

  StrInput  - the ASCII string that should be processed.

Returns:

  A pointer to the first non-whitespace character in the given string,
  or NULL if the string was all whitespace.

--*/
{
  if (StrInput == NULL) {
    return NULL;
  }

  while (*StrInput != 0) {
    if ((*StrInput == ' ') || (*StrInput == '\t') || (*StrInput == '\n')) {
      ++StrInput;
    } else {
      return StrInput;
    }
  }

  return NULL;
}

VOID
ConvertToUnicode (
  IN  CHAR8  *StrAscii,
  OUT CHAR16 *StrUnicode
  )
/*++

Routine Description:

  Convert the given ASCII string to Unicode without appending terminating 0x0000.

Arguments:

  StrAscii    - the source ASCII string, null-terminated.

  StrUnicode  - the resulted Unicode string will be put here, without the terminating 0x0000.

Returns:

--*/
{
  if ((StrAscii == NULL) || (StrUnicode == NULL)) {
    return;
  }

  while (*StrAscii != 0) {
    *StrUnicode = ATOU (*StrAscii);
    ++StrAscii;
    ++StrUnicode;
  }
}

VOID
ConvertToAscii (
  IN  CHAR16 *StrUnicode,
  OUT CHAR8  *StrAscii
  )
/*++

Routine Description:

  Convert the given Unicode string to ASCII with appending terminating 0x00.

Arguments:

  StrUnicode  - the source Unicode string, null-terminated.

  StrAscii    - the resulted ASCII string will be put here, with the terminating 0x00.

Returns:

--*/
{
  if ((StrUnicode == NULL) || (StrAscii == NULL)) {
    return;
  }

  while (*StrUnicode != 0) {
    *StrAscii = UTOA (*StrUnicode);
    ++StrUnicode;
    ++StrAscii;
  }
  *StrAscii = 0;
}

VOID
PrintUnicodeString (
  IN CHAR16 *StrUnicode
  )
/*++

Routine Description:

  Print the given Unicode string.

Arguments:

  StrUnicode  - the null-terminated Unicode string to print.

Returns:

--*/
{
  if (StrUnicode == NULL) {
    return;
  }

  while (*StrUnicode != 0) {
    putchar ((CHAR8)(*StrUnicode));
    ++StrUnicode;
  }
}

VOID
FillTimeStamp (
  OUT CHAR16  *StrTimeStampUnicode
  )
/*++

Routine Description:
  The function generates the current timestamp in "YYMMDDHHMM" format
  and puts it into the Unicode string supplied, without the null-terminator.

Arguments:

  StrTimeStampUnicode - The Unicode string which is filled on return with the current timestamp.

Returns:

--*/
{
  struct tm *Time;
  time_t    CurTime;
  CHAR8     StrTime[11];

  //
  // Fetch the current time based on UTC timezone
  //
  time (&CurTime);
  Time = gmtime (&CurTime);

  if (NULL == Time) {
    return;
  }

  snprintf (
    StrTime,
    sizeof (StrTime),
    "%02d%02d%02d%02d%02d",
    (Time->tm_year + 1900) % 100, // Year is 1900-based, need only 2 digits.
    Time->tm_mon + 1,             // Month is zero based.
    Time->tm_mday,
    Time->tm_hour,
    Time->tm_min
    );

  ConvertToUnicode (StrTime, StrTimeStampUnicode);
}
