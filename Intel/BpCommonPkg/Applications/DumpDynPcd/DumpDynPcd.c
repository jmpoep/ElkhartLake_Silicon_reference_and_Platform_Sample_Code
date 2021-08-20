/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file
  Application to dump dynamic pcd information.

Copyright (c) 2013 - 2016, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include <Uefi.h>
#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ShellLib.h>

#include <Protocol/UnicodeCollation.h>
#include <Protocol/PiPcd.h>
#include <Protocol/Pcd.h>
#include <Protocol/PiPcdInfo.h>
#include <Protocol/PcdInfo.h>

//
// String token ID of help message text.
// Shell supports to find help message in the resource section of an application image if
// .MAN file is not found. This global variable is added to make build tool recognizes
// that the help string is consumed by user and then build tool will add the string into
// the resource section. Thus the application can use '-?' option to show help message in
// Shell.
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_STRING_ID mStrDumpDynPcdHelpTokenId = STRING_TOKEN (STR_DUMP_DYN_PCD_HELP_INFORMATION);

#define MAJOR_VERSION   1
#define MINOR_VERSION   0

CONST SHELL_PARAM_ITEM PcdParamList[] = {
  {L"-?", TypeFlag},
  {L"-h", TypeFlag},
  {L"-H", TypeFlag},
  {L"-v", TypeFlag},
  {L"-V", TypeFlag},
  {NULL, TypeMax}
  };

EFI_UNICODE_COLLATION_PROTOCOL  *mUnicodeCollation  = NULL;
EFI_PCD_PROTOCOL                *mPiPcd             = NULL;
PCD_PROTOCOL                    *mPcd               = NULL;
EFI_GET_PCD_INFO_PROTOCOL       *mPiPcdInfo         = NULL;
GET_PCD_INFO_PROTOCOL           *mPcdInfo           = NULL;
CHAR16                          *mTempPcdNameBuffer = NULL;
UINTN                           mTempPcdNameBufferSize = 0;
CONST CHAR8 mHex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

/**
   Display current version.
**/
VOID
ShowVersion (
  )
{
  ShellPrintEx (-1, -1, L"DumpDynPcd Version %d.%02d\n", MAJOR_VERSION, MINOR_VERSION);
}

/**
   Display Usage and Help information.
**/
VOID
ShowHelp (
  )
{
  ShellPrintEx (-1, -1, L"Dump dynamic[ex] PCD info.\n");
  ShellPrintEx (-1, -1, L"DumpDynPcd [-b] [PcdName]\n");
  ShellPrintEx (-1, -1, L"  -b         Display one screen at a time.\n");
  ShellPrintEx (-1, -1, L"  PcdName    Specifies the name of PCD.\n");
  ShellPrintEx (-1, -1, L"             A literal[or partial] name or a pattern as specified in\n");
  ShellPrintEx (-1, -1, L"             the MetaiMatch() function of the EFI_UNICODE_COLLATION2_PROCOOL.\n");
  ShellPrintEx (-1, -1, L"             If it is absent, dump all PCDs' info.\n");
  ShellPrintEx (-1, -1, L"The PCD data is printed as hexadecimal dump.\n");
}

/**
  Dump some hexadecimal data to the screen.

  @param[in] Indent     How many spaces to indent the output.
  @param[in] Offset     The offset of the printing.
  @param[in] DataSize   The size in bytes of UserData.
  @param[in] UserData   The data to print out.
**/
VOID
DumpHex (
  IN UINTN        Indent,
  IN UINTN        Offset,
  IN UINTN        DataSize,
  IN VOID         *UserData
  )
{
  UINT8 *Data;

  CHAR8 Val[50];

  CHAR8 Str[20];

  UINT8 TempByte;
  UINTN Size;
  UINTN Index;

  Data = UserData;
  while (DataSize != 0) {
    Size = 16;
    if (Size > DataSize) {
      Size = DataSize;
    }

    for (Index = 0; Index < Size; Index += 1) {
      TempByte            = Data[Index];
      Val[Index * 3 + 0]  = mHex[TempByte >> 4];
      Val[Index * 3 + 1]  = mHex[TempByte & 0xF];
      Val[Index * 3 + 2]  = (CHAR8) ((Index == 7) ? '-' : ' ');
      Str[Index]          = (CHAR8) ((TempByte < ' ' || TempByte > 'z') ? '.' : TempByte);
    }

    Val[Index * 3]  = 0;
    Str[Index]      = 0;
    ShellPrintEx (-1, -1, L"%*a%08X: %-48a *%a*\r\n", Indent, "", Offset, Val, Str);

    Data += Size;
    Offset += Size;
    DataSize -= Size;
  }
}

/**
  Get PCD type string based on input PCD type.

  @param[in]    TokenSpace      PCD Token Space.
  @param[in]    PcdType         The input PCD type.

  @return       Pointer to PCD type string.
**/
CHAR16 *
GetPcdTypeString (
  IN CONST EFI_GUID     *TokenSpace,
  IN EFI_PCD_TYPE       PcdType
  )
{
  UINTN  BufLen;
  CHAR16 *RetString;

  BufLen      = 0;
  RetString   = NULL;

  switch (PcdType) {
    case EFI_PCD_TYPE_8:
      StrnCatGrow (&RetString, &BufLen, L"UINT8", 0);
      break;
    case EFI_PCD_TYPE_16:
      StrnCatGrow (&RetString, &BufLen, L"UINT16", 0);
      break;
    case EFI_PCD_TYPE_32:
      StrnCatGrow (&RetString, &BufLen, L"UINT32", 0);
      break;
    case EFI_PCD_TYPE_64:
      StrnCatGrow (&RetString, &BufLen, L"UINT64", 0);
      break;
    case EFI_PCD_TYPE_BOOL:
      StrnCatGrow (&RetString, &BufLen, L"BOOLEAN", 0);
      break;
    case EFI_PCD_TYPE_PTR:
      StrnCatGrow (&RetString, &BufLen, L"POINTER", 0);
      break;
    default:
      StrnCatGrow (&RetString, &BufLen, L"UNKNOWN", 0);
      break;
  }

  if (TokenSpace == NULL) {
    StrnCatGrow (&RetString, &BufLen, L":DYNAMIC", 0);
  } else {
    StrnCatGrow (&RetString, &BufLen, L":DYNAMICEX", 0);
  }

  return RetString;
}

/**
  Dump PCD info.

  @param[in]    TokenSpace      PCD Token Space.
  @param[in]    TokenNumber     PCD Token Number.
  @param[in]    PcdInfo         Pointer to PCD info.
**/
VOID
DumpPcdInfo (
  IN CONST EFI_GUID     *TokenSpace,
  IN UINTN              TokenNumber,
  IN EFI_PCD_INFO       *PcdInfo
  )
{
  CHAR16                *RetString;
  UINT8                 Uint8;
  UINT16                Uint16;
  UINT32                Uint32;
  UINT64                Uint64;
  BOOLEAN               Boolean;
  VOID                  *PcdData;

  RetString = NULL;

  if (PcdInfo->PcdName != NULL) {
    ShellPrintEx (-1, -1, L"%a\n", PcdInfo->PcdName);
  } else {
    if (TokenSpace == NULL) {
      ShellPrintEx (-1, -1, L"Default Token Space\n");
    } else {
      ShellPrintEx (-1, -1, L"%g\n", TokenSpace);
    }
  }

  RetString = GetPcdTypeString (TokenSpace, PcdInfo->PcdType);

  switch (PcdInfo->PcdType) {
    case EFI_PCD_TYPE_8:
      if (TokenSpace == NULL) {
        Uint8 = mPcd->Get8 (TokenNumber);
      } else {
        Uint8 = mPiPcd->Get8 (TokenSpace, TokenNumber);
      }
      ShellPrintEx (-1, -1, L"  Token = 0x%08x - Type = %H%-17s%N - Size = 0x%x - Value = 0x%x\n", TokenNumber, RetString, PcdInfo->PcdSize, Uint8);
      break;
    case EFI_PCD_TYPE_16:
      if (TokenSpace == NULL) {
        Uint16 = mPcd->Get16 (TokenNumber);
      } else {
        Uint16 = mPiPcd->Get16 (TokenSpace, TokenNumber);
      }
      ShellPrintEx (-1, -1, L"  Token = 0x%08x - Type = %H%-17s%N - Size = 0x%x - Value = 0x%x\n", TokenNumber, RetString, PcdInfo->PcdSize, Uint16);
      break;
    case EFI_PCD_TYPE_32:
      if (TokenSpace == NULL) {
        Uint32 = mPcd->Get32 (TokenNumber);
      } else {
        Uint32 = mPiPcd->Get32 (TokenSpace, TokenNumber);
      }
      ShellPrintEx (-1, -1, L"  Token = 0x%08x - Type = %H%-17s%N - Size = 0x%x - Value = 0x%x\n", TokenNumber, RetString, PcdInfo->PcdSize, Uint32);
      break;
    case EFI_PCD_TYPE_64:
      if (TokenSpace == NULL) {
        Uint64 = mPcd->Get64 (TokenNumber);
      } else {
        Uint64 = mPiPcd->Get64 (TokenSpace, TokenNumber);
      }
      ShellPrintEx (-1, -1, L"  Token = 0x%08x - Type = %H%-17s%N - Size = 0x%x - Value = 0x%lx\n", TokenNumber, RetString, PcdInfo->PcdSize, Uint64);
      break;
    case EFI_PCD_TYPE_BOOL:
      if (TokenSpace == NULL) {
        Boolean = mPcd->GetBool (TokenNumber);
      } else {
        Boolean = mPiPcd->GetBool (TokenSpace, TokenNumber);
      }
      ShellPrintEx (-1, -1, L"  Token = 0x%08x - Type = %H%-17s%N - Size = 0x%x - Value = %a\n", TokenNumber, RetString, PcdInfo->PcdSize, Boolean ? "TRUE" : "FALSE");
      break;
    case EFI_PCD_TYPE_PTR:
      if (TokenSpace == NULL) {
        PcdData = mPcd->GetPtr (TokenNumber);
      } else {
        PcdData = mPiPcd->GetPtr (TokenSpace, TokenNumber);
      }
      ShellPrintEx (-1, -1, L"  Token = 0x%08x - Type = %H%-17s%N - Size = 0x%x\n", TokenNumber, RetString, PcdInfo->PcdSize);
      DumpHex (2, 0, PcdInfo->PcdSize, PcdData);
      break;
    default:
      return;
  }

  if (RetString != NULL) {
    FreePool (RetString);
  }
  ShellPrintEx (-1, -1, L"\n");
}

/**
  Show one or all PCDs' info.

  @param[in]  InputPcdName       Pointer to PCD name to show. If NULL, show all PCDs' info.

  @retval EFI_SUCCESS            Command completed successfully.
  @retval EFI_OUT_OF_RESOURCES   Not enough resources were available to run the command.
  @retval EFI_ABORTED            Aborted by user.
  @retval EFI_NOT_FOUND          The specified PCD is not found.
**/
EFI_STATUS
ProcessPcd (
  IN CHAR16     *InputPcdName
  )
{
  EFI_STATUS            Status;
  EFI_GUID              *TokenSpace;
  UINTN                 TokenNumber;
  EFI_PCD_INFO          PcdInfo;
  BOOLEAN               Found;
  UINTN                 PcdNameSize;

  PcdInfo.PcdName = NULL;
  PcdInfo.PcdSize = 0;
  PcdInfo.PcdType = 0xFF;
  Found = FALSE;

  ShellPrintEx (-1, -1, L"Current system SKU ID: 0x%x\n\n", mPiPcdInfo->GetSku ());

  TokenSpace = NULL;
  do {
    if (ShellGetExecutionBreakFlag()) {
      return EFI_ABORTED;
    }
    TokenNumber = 0;
    do {
      if (ShellGetExecutionBreakFlag()) {
        return EFI_ABORTED;
      }
      Status = mPiPcd->GetNextToken (TokenSpace, &TokenNumber);
      if (!EFI_ERROR (Status) && TokenNumber != 0) {
        if (TokenSpace == NULL) {
          //
          // PCD in default Token Space.
          //
          mPcdInfo->GetInfo (TokenNumber, &PcdInfo);
        } else {
          mPiPcdInfo->GetInfo (TokenSpace, TokenNumber, &PcdInfo);
        }
        if (InputPcdName != NULL) {
          if (PcdInfo.PcdName == NULL) {
            continue;
          }
          PcdNameSize = AsciiStrSize (PcdInfo.PcdName) * sizeof (CHAR16);
          if (mTempPcdNameBuffer == NULL) {
            mTempPcdNameBufferSize = PcdNameSize;
            mTempPcdNameBuffer = AllocatePool (mTempPcdNameBufferSize);
          } else if (mTempPcdNameBufferSize < PcdNameSize) {
            mTempPcdNameBuffer = ReallocatePool (mTempPcdNameBufferSize, PcdNameSize, mTempPcdNameBuffer);
            mTempPcdNameBufferSize = PcdNameSize;
          }
          if (mTempPcdNameBuffer == NULL) {
            return EFI_OUT_OF_RESOURCES;
          }
          AsciiStrToUnicodeStrS (PcdInfo.PcdName, mTempPcdNameBuffer, mTempPcdNameBufferSize / sizeof (CHAR16));
          //
          // Compare the input PCD name with the PCD name in PCD database.
          //
          if ((StrStr (mTempPcdNameBuffer, InputPcdName) != NULL) ||
              (mUnicodeCollation != NULL && mUnicodeCollation->MetaiMatch (mUnicodeCollation, mTempPcdNameBuffer, InputPcdName))) {
            //
            // Found matched PCD.
            //
            DumpPcdInfo (TokenSpace, TokenNumber, &PcdInfo);
            Found = TRUE;
          }
        } else {
          DumpPcdInfo (TokenSpace, TokenNumber, &PcdInfo);
        }
      }
    } while (!EFI_ERROR (Status) && TokenNumber != 0);

    Status = mPiPcd->GetNextTokenSpace ((CONST EFI_GUID **) &TokenSpace);
  } while (!EFI_ERROR (Status) && TokenSpace != NULL);

  if ((InputPcdName != NULL) && !Found) {
    //
    // The specified PCD is not found, print error.
    //
    ShellPrintEx (-1, -1, L"%EError. %NNo matching PCD found: %s.\n", InputPcdName);
    return EFI_NOT_FOUND;
  }
  return EFI_SUCCESS;
}

/**
  Main entrypoint for DumpDynPcd shell application.

  @param[in]  ImageHandle     The image handle.
  @param[in]  SystemTable     The system table.

  @retval EFI_SUCCESS            Command completed successfully.
  @retval EFI_INVALID_PARAMETER  Command usage error.
  @retval EFI_OUT_OF_RESOURCES   Not enough resources were available to run the command.
  @retval EFI_ABORTED            Aborted by user.
  @retval EFI_NOT_FOUND          The specified PCD is not found.
  @retval Others                 Error status returned from gBS->LocateProtocol.
**/
EFI_STATUS
EFIAPI
DumpDynPcdMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS    Status;
  LIST_ENTRY    *ParamPackage;
  CHAR16        *ParamProblem;
  CHAR16        *InputPcdName;

  ParamPackage  = NULL;
  InputPcdName  = NULL;

  //
  // initialize the shell lib (we must be in non-auto-init...)
  //
  Status = ShellInitialize ();
  ASSERT_EFI_ERROR (Status);

  Status = gBS->LocateProtocol(&gEfiUnicodeCollation2ProtocolGuid, NULL, (VOID **) &mUnicodeCollation);
  if (EFI_ERROR (Status)) {
    mUnicodeCollation = NULL;
  }

  Status = gBS->LocateProtocol (&gEfiPcdProtocolGuid, NULL, (VOID **) &mPiPcd);
  if (EFI_ERROR (Status)) {
    ShellPrintEx (-1, -1, L"DumpDynPcd: %EError. %NPI PCD protocol is not present.\n");
    return Status;
  }

  Status = gBS->LocateProtocol (&gEfiGetPcdInfoProtocolGuid, NULL, (VOID **) &mPiPcdInfo);
  if (EFI_ERROR (Status)) {
    ShellPrintEx (-1, -1, L"DumpDynPcd: %EError. %NPI PCD info protocol is not present.\n");
    return Status;
  }

  Status = gBS->LocateProtocol (&gPcdProtocolGuid, NULL, (VOID **) &mPcd);
  if (EFI_ERROR (Status)) {
    ShellPrintEx (-1, -1, L"DumpDynPcd: %EError. %NPCD protocol is not present.\n");
    return Status;
  }

  Status = gBS->LocateProtocol (&gGetPcdInfoProtocolGuid, NULL, (VOID **) &mPcdInfo);
  if (EFI_ERROR (Status)) {
    ShellPrintEx (-1, -1, L"DumpDynPcd: %EError. %NPCD info protocol is not present.\n");
    return Status;
  }

  //
  // parse the command line
  //
  Status = ShellCommandLineParse (PcdParamList, &ParamPackage, &ParamProblem, TRUE);
  if (EFI_ERROR (Status)) {
    if (ParamProblem != NULL) {
      ShellPrintEx (-1, -1, L"DumpDynPcd: %EError. %NThe argument '%B%s%N' is invalid.\n", ParamProblem);
      FreePool (ParamProblem);
    } else {
      ShellPrintEx (-1, -1, L"DumpDynPcd: %EError. %NThe input parameters are not recognized.\n");
    }
    Status = EFI_INVALID_PARAMETER;
  } else {
    //
    // check for "-?" help information, and for "-v" for version inforamtion.
    //
    if (ShellCommandLineGetFlag (ParamPackage, L"-?")  ||
        ShellCommandLineGetFlag (ParamPackage, L"-h")  ||
        ShellCommandLineGetFlag (ParamPackage, L"-H")) {
      ShowHelp ();
      goto Done;
    } else if (ShellCommandLineGetFlag (ParamPackage, L"-v") ||
               ShellCommandLineGetFlag (ParamPackage, L"-V")) {
      ShowVersion ();
      goto Done;
    } else {
      if (ShellCommandLineGetRawValue (ParamPackage, 2) != NULL) {
        ShellPrintEx (-1, -1, L"DumpDynPcd: %EError. %NToo many arguments specified.\n");
        Status = EFI_INVALID_PARAMETER;
      } else {
        //
        // Only support single parameter as the input PCD name.
        //
        InputPcdName = (CHAR16 *) ShellCommandLineGetRawValue (ParamPackage, 1);
      }
    }
  }

  //
  // Additional check for the input parameter.
  //
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  Status = ProcessPcd (InputPcdName);

Done:
  //
  // Free the command line package map to ShellCommandLineParse.
  //
  if (ParamPackage != NULL) {
    ShellCommandLineFreeVarList (ParamPackage);
  }

  if (mTempPcdNameBuffer != NULL) {
    FreePool (mTempPcdNameBuffer);
  }

  return Status;
}

