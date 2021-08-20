/** @file
  File to support address decoding and encoding
  Entry Point for the AddrDecodeEncode EFI application

@copyright
 Copyright (c) 1999 - 2018 Intel Corporation. All rights reserved
 This software and associated documentation (if any) is furnished
 under a license and may only be used or copied in accordance
 with the terms of the license. Except as permitted by the
 license, no part of this software or documentation may be
 reproduced, stored in a retrieval system, or transmitted in any
 form or by any means without the express written consent of
 Intel Corporation.
 This file contains an 'Intel Peripheral Driver' and is uniquely
 identified as "Intel Reference Module" and is licensed for Intel
 CPUs and chipsets under the terms of your license agreement with
 Intel or your vendor. This file may be modified by the user, subject
 to additional terms of the license agreement.

@par Specification Reference:
**/
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/ShellLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/MemoryAddressEncodeDecode.h>

#define MAJOR_VERSION   1
#define MINOR_VERSION   0

STATIC CONST SHELL_PARAM_ITEM DecodeParamList[] = {
  {L"-h", TypeFlag},
  {L"-H", TypeFlag},
  {L"-v", TypeFlag},
  {L"-V", TypeFlag},
  {L"-e", TypeFlag},
  {L"-E", TypeFlag},
  {L"-d", TypeFlag},
  {L"-D", TypeFlag},
  {NULL, TypeMax}
  };

/**
   Display current version.
**/
VOID
ShowVersion (
  )
{
  ShellPrintEx (-1, -1, L"AddrDecodeEncode: Version %d.%02d\n", MAJOR_VERSION, MINOR_VERSION);
}

/**
   Display Usage and Help information.
**/
VOID
ShowHelp (
  )
{
  ShellPrintEx (-1, -1, L"AddrDecodeEncode [-e] [Channel] [Dimm] [Rank] [BankGroup] [Bank] [CAS] [RAS]\n");
  ShellPrintEx (-1, -1, L"  -e         Specifies input of a Dram Address to be Encoded.\n");
  ShellPrintEx (-1, -1, L"  Controller  Specifies the Controller {0}\n");
  ShellPrintEx (-1, -1, L"  Channel     Specifies the Channel    {0..1}\n");
  ShellPrintEx (-1, -1, L"  Dimm        Specifies the Dimm       {0..1}\n");
  ShellPrintEx (-1, -1, L"  Rank        Specifies the Rank       {0..1}\n");
  ShellPrintEx (-1, -1, L"  BankGroup   Specifies the BankGroup  {0..3}\n");
  ShellPrintEx (-1, -1, L"  Bank        Specifies the Bank       {0..7}\n");
  ShellPrintEx (-1, -1, L"  CAS         Specifies the CAS        {0..2^10-1}\n");
  ShellPrintEx (-1, -1, L"  RAS         Specifies the RAS        {0..2^14-1}\n");
  ShellPrintEx (-1, -1, L"  The output of this command will be the System Address associated with the Dram Address\n\n");
  ShellPrintEx (-1, -1, L"AddrDecodeEncode [-d] [System Address]\n");
  ShellPrintEx (-1, -1, L"  -d            Specifies input of a System Address to be Decoded.\n");
  ShellPrintEx (-1, -1, L"  SystemAddress  Specifies the System Address.\n");
  ShellPrintEx (-1, -1, L"  The output of this command will be the Dram Address associated with the System Address\n");
}

/**
 * main entry of module
 *
 * @param ImageHandle
 * @param SystemTable
 *
 * @return EFI_STATUS EFIAPI
 */
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  DRAM_ADDRESS   DramAddress;
  UINT64         SystemAddress;
  EFI_STATUS     Status;
  LIST_ENTRY     *ParamPackage;
  CHAR16         *StringValue;
  UINT64         Value;
  MEMORY_ADDRESS_ENCODE_DECODE_PROTOCOL *MemEncodeDecodeProtocol;

  ParamPackage  = NULL;
  StringValue = NULL;

  //
  // initialize the shell lib (we must be in non-auto-init...)
  //
  Status = ShellInitialize ();
  ASSERT_EFI_ERROR (Status);

  Status = gBS->LocateProtocol (&gMemoryAddressEncodeDecodeProtocolGuid, NULL, (VOID **) &MemEncodeDecodeProtocol);
  ASSERT_EFI_ERROR (Status);

  //
  // parse the command line
  //
  Status = ShellCommandLineParse (DecodeParamList, &ParamPackage, NULL, TRUE);
  if (EFI_ERROR (Status)) {
    Status = EFI_INVALID_PARAMETER;
  } else {
    //
    // check for "-?" help information, and for "-v" for version inforamtion.
    //
    if (ShellCommandLineGetFlag (ParamPackage, L"-h")  ||
        ShellCommandLineGetFlag (ParamPackage, L"-H")) {
      ShowHelp ();
      goto Done;
    } else if (ShellCommandLineGetFlag (ParamPackage, L"-v") ||
               ShellCommandLineGetFlag (ParamPackage, L"-V")) {
      ShowVersion ();
      goto Done;
    } else if (ShellCommandLineGetFlag (ParamPackage, L"-e") ||
               ShellCommandLineGetFlag (ParamPackage, L"-E")) {

      StringValue = (CHAR16 *) ShellCommandLineGetRawValue (ParamPackage, 1);
      ShellConvertStringToUint64 (StringValue, &Value, FALSE, FALSE);
      DramAddress.Controller = (UINT8) Value;

      StringValue = (CHAR16 *) ShellCommandLineGetRawValue (ParamPackage, 2);
      ShellConvertStringToUint64 (StringValue, &Value, FALSE, FALSE);
      DramAddress.ChannelNumber = (UINT8) Value;

      StringValue = (CHAR16 *) ShellCommandLineGetRawValue (ParamPackage, 3);
      ShellConvertStringToUint64 (StringValue, &Value, FALSE, FALSE);
      DramAddress.DimmNumber = (UINT8) Value;

      StringValue = (CHAR16 *) ShellCommandLineGetRawValue (ParamPackage, 4);
      ShellConvertStringToUint64 (StringValue, &Value, FALSE, FALSE);
      DramAddress.Rank = (UINT8) Value;

      StringValue = (CHAR16 *) ShellCommandLineGetRawValue (ParamPackage, 5);
      ShellConvertStringToUint64 (StringValue, &Value, FALSE, FALSE);
      DramAddress.BankGroup = (UINT8) Value;

      StringValue = (CHAR16 *) ShellCommandLineGetRawValue (ParamPackage, 6);
      ShellConvertStringToUint64 (StringValue, &Value, FALSE, FALSE);
      DramAddress.Bank = (UINT8) Value;

      StringValue = (CHAR16 *) ShellCommandLineGetRawValue (ParamPackage, 7);
      ShellConvertStringToUint64 (StringValue, &Value, FALSE, FALSE);
      DramAddress.Cas = (UINT16) Value;

      StringValue = (CHAR16 *) ShellCommandLineGetRawValue (ParamPackage, 8);
      ShellConvertStringToUint64 (StringValue, &Value, FALSE, FALSE);
      DramAddress.Ras = (UINT32) Value;

      ShellPrintEx (
        -1,
        -1,
        L"Controller %d Ch %d Dimm %d Rank %d BankGroup %d Bank %d CAS 0x%X RAS 0x%X\n",
        DramAddress.Controller,
        DramAddress.ChannelNumber,
        DramAddress.DimmNumber,
        DramAddress.Rank,
        DramAddress.BankGroup,
        DramAddress.Bank,
        DramAddress.Cas,
        DramAddress.Ras
        );

      DEBUG ((
        DEBUG_INFO,
        "Controller %d Ch %d Dimm %d Rank %d BankGroup %d Bank %d CAS 0x%X RAS 0x%X\n",
        DramAddress.Controller,
        DramAddress.ChannelNumber,
        DramAddress.DimmNumber,
        DramAddress.Rank,
        DramAddress.BankGroup,
        DramAddress.Bank,
        DramAddress.Cas,
        DramAddress.Ras
      ));

        MemEncodeDecodeProtocol->MemoryAddressEncode (&DramAddress, &SystemAddress);

      ShellPrintEx (
        -1,
        -1,
        L"\nSystemAddress = 0x%llX\n",
        SystemAddress
        );

      DEBUG ((
        DEBUG_INFO,
        " - System Address = 0x%llX\n",
        SystemAddress
      ));

    } else if (ShellCommandLineGetFlag (ParamPackage, L"-d") ||
               ShellCommandLineGetFlag (ParamPackage, L"-D")) {
      StringValue = (CHAR16 *) ShellCommandLineGetRawValue (ParamPackage, 1);
      ShellConvertStringToUint64 (StringValue, &Value, FALSE, FALSE);
      SystemAddress = Value;

      ShellPrintEx (
        -1,
        -1,
        L"\nSystemAddress = 0x%llX\n",
        SystemAddress
        );

      DEBUG ((
        DEBUG_INFO,
        " - System Address = 0x%llX\n",
        SystemAddress
        ));

      MemEncodeDecodeProtocol->MemoryAddressDecode (SystemAddress, &DramAddress);

      ShellPrintEx (
        -1,
        -1,
        L"Controller %d Ch %d Dimm %d Rank %d BankGroup %d Bank %d CAS 0x%X RAS 0x%X\n",
        DramAddress.Controller,
        DramAddress.ChannelNumber,
        DramAddress.DimmNumber,
        DramAddress.Rank,
        DramAddress.BankGroup,
        DramAddress.Bank,
        DramAddress.Cas,
        DramAddress.Ras
        );
      DEBUG ((
        DEBUG_INFO,
        "Controller %d Ch %d Dimm %d Rank %d BankGroup %d Bank %d CAS 0x%X RAS 0x%X\n",
        DramAddress.Controller,
        DramAddress.ChannelNumber,
        DramAddress.DimmNumber,
        DramAddress.Rank,
        DramAddress.BankGroup,
        DramAddress.Bank,
        DramAddress.Cas,
        DramAddress.Ras
      ));

    }

    //
    // free the command line package
    // map to ShellCommandLineParse
    //
    ShellCommandLineFreeVarList (ParamPackage);
    ParamPackage = NULL;
  }

  //
  // Additional check for the input parameter.
  //
  if (EFI_ERROR(Status)) {
    goto Done;
  }

Done:

  return EFI_SUCCESS;
}
