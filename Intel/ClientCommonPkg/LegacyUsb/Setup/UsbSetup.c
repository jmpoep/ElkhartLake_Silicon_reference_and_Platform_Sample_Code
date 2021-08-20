/** @file
  USB driver setup related functions implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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

#include <SetupPrivate.h>
#include <Protocol/BlockIo.h>
#include <LegacyUsb/Protocol/UsbController.h>
#include <LegacyUsb/Protocol/UsbPolicy.h>
#include <LegacyUsb/LegacyUsbConfig.h>

#define MAX_DEVS_LINE_LENGTH      80
#define MAX_DEVICE_NUMBER_LENGTH  10
#define MAX_DEVICE_AMOUNT         127

//
// EdKII Bios Begin : Add ItoaHelper ItowEx
//
char * ItoaHelper (
  INT64   value,
  char   *string,
  int     radix,
  BOOLEAN is_int64
  )
{
  UINT32 digit;
  UINT64 v = (value>=0)
             ? (UINT64) value
             : (radix==10)
               ? (UINT64)-value
               : (is_int64)
                 ? (UINT64)value
                 : (UINT32)value;
  if (v) {
    while (v) {
      v = DivU64x32Remainder(v,radix,&digit);
      if (digit<0xa) {
        *string=(char)(digit+'0');
      } else {
        *string=(char)(digit-0xa+'a');
      }
      string++;
    }
  } else {
    *string++='0';
  }
  if (radix==10 && value<0) {
    *string++='-';
  }
  *string--=0;
  return string;
}

CHAR16 * ItowEx (
  INT64   value,
  CHAR16 *string,
  int     radix,
  BOOLEAN is_int64
  )
{
  char s[0x100];
  CHAR16 *str = string;
  char *send = ItoaHelper(value,(char*)s,radix,is_int64);
  //convert to unicode
  while(send>=s) {
    *str++ = *send--;
  }
  *str=0;
  return string;
}
//
// EdKII Bios End
//

EFI_STATUS
GetConnectedDevices(
    CHAR16                          *DevNumStr,
    CHAR16                          *ControllerNumStr,
    EFI_USB_PROTOCOL                *UsbProtocol,
    CONNECTED_USB_DEVICES_NUM       *Devs
)
/*++

Routine Description:

  This function retrieves the information about connected USB devices.

Arguments:

  DevNumStr               - GC_TODO: add argument description
  ControllerNumStr        - GC_TODO: add argument description
  UsbProtocol             - GC_TODO: add argument description
  Devs                    - GC_TODO: add argument description

Returns:

  returns TRUE if device connection status has changed since this
  function is called last time; otherwise FALSE.

 Notes: When FALSE is returned, none of the output parameters are valid.

--*/
{
    CHAR16  StrMassStorage[] = L"Drive";
    CHAR16  StrKeyboard[] = L"Keyboard";
    CHAR16  StrMouse[] = L"Mouse";
    CHAR16  StrPoint[] = L"Point";
    CHAR16  StrMice[] = L"Mice";
    CHAR16  StrHub[] = L"Hub";
    CHAR16  StrCcid[] = L"SmartCard Reader";
    CHAR16  StrUhci[] = L"UHCI";
    CHAR16  StrOhci[] = L"OHCI";
    CHAR16  StrEhci[] = L"EHCI";
    CHAR16  StrXhci[] = L"XHCI";
    CHAR16  Name[MAX_DEVS_LINE_LENGTH];
    CHAR16  *StrPtr = Name;
    CHAR16  NumberToString [MAX_DEVICE_NUMBER_LENGTH];
    UINTN   NumSize;
    CHAR16  Comma[] = L", ";
    CHAR16  Space[] = L" ";
    CHAR16  LeadingSpace[] = L"      None";
    UINT8   MassStorageNumber;
    UINT8   KeyboardNumber;
    UINT8   MouseNumber;
    UINT8   PointNumber;
    UINT8   HubNumber;
    UINT8   CcidNumber;
    UINT8   UhciNumber;
    UINT8   OhciNumber;
    UINT8   EhciNumber;
    UINT8   XhciNumber;
    BOOLEAN Is1stItem = TRUE;

    UsbProtocol->UsbReportDevices(Devs);
    MassStorageNumber = Devs->NumUsbMass;
    KeyboardNumber = Devs->NumUsbKbds;
    MouseNumber	 = Devs->NumUsbMice;
    PointNumber = Devs->NumUsbPoint;
    HubNumber = Devs->NumUsbHubs;
    CcidNumber = Devs->NumUsbCcids;
    UhciNumber = Devs->NumUhcis;
    OhciNumber = Devs->NumOhcis;
    EhciNumber = Devs->NumEhcis;
    XhciNumber = Devs->NumXhcis;

    // Form the string
    SetMem(StrPtr, MAX_DEVS_LINE_LENGTH * sizeof(CHAR16), 0);
    CopyMem(StrPtr, LeadingSpace, 10 * sizeof(CHAR16));
    StrPtr += 6;  // leave string pointer at "None"

    // Drive/Drives
    if ((MassStorageNumber) && (MassStorageNumber < MAX_DEVICE_AMOUNT)) {
        ItowEx(MassStorageNumber, NumberToString, 10, FALSE);
        NumSize = StrLen(NumberToString);

        CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        CopyMem(StrPtr, Space, 2);
        StrPtr += 1;

        CopyMem(StrPtr, StrMassStorage, 10);
        StrPtr += 5;          // L"Drive"
        if (MassStorageNumber > 1) {
          *StrPtr++ = L's';   // L"Drives"
        }
        Is1stItem = FALSE;
    }

    // Keyboard/Keyboards
    if ((KeyboardNumber) && (KeyboardNumber < MAX_DEVICE_AMOUNT)) {
        if (!Is1stItem) {
            CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;    // L" ,"
        }
        ItowEx(KeyboardNumber, NumberToString, 10, FALSE);
        NumSize = StrLen(NumberToString);

        // move pointer 1 more space then string length
        CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        CopyMem(StrPtr, Space, 2);
        StrPtr += 1;

        CopyMem(StrPtr, StrKeyboard, 16); 
        StrPtr += 8;    // L"Keyboard"
        if (KeyboardNumber > 1) {
          *StrPtr++ = L's'; // L"Keyboards"
        }
        Is1stItem = FALSE;
    }

    // Mouse/Mice
    if ((MouseNumber) && (MouseNumber < MAX_DEVICE_AMOUNT)) {
        if (!Is1stItem) {
            CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;    // L" ,"
        }
        ItowEx(MouseNumber, NumberToString, 10, FALSE);
        NumSize = StrLen(NumberToString);

        // move pointer 1 more space then string length
        CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        CopyMem(StrPtr, Space, 2);
        StrPtr += 1;

        if (MouseNumber == 1) {
            CopyMem(StrPtr, StrMouse, 10);
            StrPtr += 5;        // L"Mouse"
        } else {
            CopyMem(StrPtr, StrMice, 8);
            StrPtr += 4;        // L"Mice"
        }
        Is1stItem = FALSE;
    }

    // Point/Points
    if ((PointNumber) && (PointNumber < MAX_DEVICE_AMOUNT)) {
        if (!Is1stItem) {
            CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;    // L" ,"
        }
        ItowEx(PointNumber, NumberToString, 10, FALSE);
        NumSize = StrLen(NumberToString);
        // move pointer 1 more space then string length
        CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        CopyMem(StrPtr, Space, 2);
        StrPtr += 1;

        CopyMem(StrPtr, StrPoint, 10);
        StrPtr += 5;            // L"Point"
        if (PointNumber > 1) {
          *StrPtr++ = L's';     // L"Points"
        }
        Is1stItem = FALSE;
    }

    // Hub/Hubs
    if ((HubNumber) && (HubNumber < MAX_DEVICE_AMOUNT)) {
        if (!Is1stItem) {
            CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;    // L" ,"
        }
        ItowEx(HubNumber, NumberToString, 10, FALSE);
        NumSize = StrLen(NumberToString);

        // move pointer 1 more space then string length
        CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        CopyMem(StrPtr, Space, 2);
        StrPtr += 1;
        CopyMem(StrPtr, StrHub, 6);
        StrPtr += 3;            // L"Hub"
        if (HubNumber > 1) {
            *StrPtr++ = L's';   // L"Hubs"
        }
        Is1stItem = FALSE;
    }
    // Ccid/Ccids
    if (CcidNumber) {
        if (!Is1stItem) {
            CopyMem(StrPtr, Comma, 4);
            StrPtr += 2; // L" ,"
        }
        ItowEx(CcidNumber, NumberToString, 10, FALSE);
        NumSize = StrLen(NumberToString);

        // move pointer 1 more space then string length
        CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;

        // move pointer 1 more space
        CopyMem(StrPtr, Space, 2);
        StrPtr += 1;  // L" "

        CopyMem(StrPtr, StrCcid, 32);
        StrPtr += 16;           // L"SmartCard Reader"
        if (CcidNumber > 1) {
            *StrPtr++ = L's';   // L'SmartCard Readers'
        }
        Is1stItem = FALSE;
    }

    CopyMem(DevNumStr, Name, MAX_DEVS_LINE_LENGTH * sizeof(CHAR16));

    Is1stItem = TRUE;
    StrPtr = Name;
    // Form the string
    SetMem(StrPtr, MAX_DEVS_LINE_LENGTH * sizeof(CHAR16), 0);
    CopyMem(StrPtr, LeadingSpace, 10 * sizeof(CHAR16));
    StrPtr += 6;  // leave string pointer at "None"

    // Drive/Drives
    if (UhciNumber) {
        ItowEx(UhciNumber, NumberToString, 10, FALSE);
        NumSize = StrLen(NumberToString);

        CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        CopyMem(StrPtr, Space, 2);
        StrPtr += 1;

        CopyMem(StrPtr, StrUhci, 8);
        StrPtr += 4;   // L"UHCI"
        if (UhciNumber > 1) {
          *StrPtr++ = L's';   // L"UHCIs"
        }
        Is1stItem = FALSE;
    }

    if (OhciNumber) {
        if (!Is1stItem) {
            CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;   // L" ,"
        }
        ItowEx(OhciNumber, NumberToString, 10, FALSE);
        NumSize = StrLen(NumberToString);

        // move pointer 1 more space then string length
        CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;

        // move pointer 1 more space
        CopyMem(StrPtr, Space, 2);
        StrPtr += 1;   // L" "

        CopyMem(StrPtr, StrOhci, 8);
        StrPtr += 4;            // L"OHCI"
        if (OhciNumber > 1) {
            *StrPtr++ = L's';   // L'OHCIs'
        }
        Is1stItem = FALSE;
    }

    if (EhciNumber) {
        if (!Is1stItem) {
            CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;   // L" ,"
        }
        ItowEx(EhciNumber, NumberToString, 10, FALSE);
        NumSize = StrLen(NumberToString);

        // move pointer 1 more space then string length
        CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;

        // move pointer 1 more space
        CopyMem(StrPtr, Space, 2);
        StrPtr += 1;   // L" "

        CopyMem(StrPtr, StrEhci, 8);
        StrPtr += 4;            // L"EHCI"
        if (EhciNumber > 1) {
            *StrPtr++ = L's';   // L'EHCIs'
        }
        Is1stItem = FALSE;
    }

    if (XhciNumber) {
        if (!Is1stItem) {
            CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;   // L" ,"
        }
        ItowEx(XhciNumber, NumberToString, 10, FALSE);
        NumSize = StrLen(NumberToString);

        // move pointer 1 more space then string length
        CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;

        // move pointer 1 more space
        CopyMem(StrPtr, Space, 2);
        StrPtr += 1;	//	L" "

        CopyMem(StrPtr, StrXhci, 8);
        StrPtr += 4;            // L"XHCI"
        if (XhciNumber > 1) {
            *StrPtr++ = L's';   // L'XHCIs'
        }
        Is1stItem = FALSE;
    }

    CopyMem(ControllerNumStr, Name, MAX_DEVS_LINE_LENGTH * sizeof(CHAR16));

    return EFI_SUCCESS;

}

UINT8
GetMassDeviceName(
    UINT8               *DevName,
    UINT8               DevAddr,
    EFI_USB_PROTOCOL    *UsbProtocol
)
/*++

Routine Description:

  This function retrieves the USB mass storage device ASCII name.

Arguments:

  DevName        - GC_TODO: add argument description
  DevAddr        - GC_TODO: add argument description
  UsbProtocol    - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
{
    CHAR8   Data[MAX_DEVS_LINE_LENGTH];
    CHAR16  AsciiCodeData[MAX_DEVS_LINE_LENGTH];
    UINT8   NextDev;
    UINT8   i;

    // Get the name using USBMassAPIGetDeviceInformation
    NextDev = UsbProtocol->UsbGetNextMassDeviceName((UINT8 *) Data, sizeof(Data), DevAddr);
    
    if (NextDev != 0xFF) {
      //
      // Transfer CHAR8 to CHAR16
      //
      for (i = 0; i < MAX_DEVS_LINE_LENGTH; i++) {
        AsciiCodeData[i] = (UINT16) Data[i];
      }
      //
      // Save as Unicode String
      //
      AsciiSPrint((char*)DevName, MAX_DEVS_LINE_LENGTH, "%s", AsciiCodeData);
    }

    return NextDev;
}

VOID
InitUsbStrings(
    EFI_HII_HANDLE HiiHandle,
    UINT16         Class
)
/*++

Routine Description:

  This function is eLink'ed with the chain executed right before the Setup.

Arguments:

  HiiHandle - GC_TODO: add argument description
  Class     - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
{
    CHAR16  DevNumStr[MAX_DEVS_LINE_LENGTH];
    CHAR16  ControllerNumStr[MAX_DEVS_LINE_LENGTH];
    CHAR8   MassStr[MAX_DEVS_LINE_LENGTH];
    UINT8   NextDev;
    UINT16  MassDev[16] = {
        STRING_TOKEN(STR_USB_MASS_DEVICE1),
        STRING_TOKEN(STR_USB_MASS_DEVICE2),
        STRING_TOKEN(STR_USB_MASS_DEVICE3),
        STRING_TOKEN(STR_USB_MASS_DEVICE4),
        STRING_TOKEN(STR_USB_MASS_DEVICE5),
        STRING_TOKEN(STR_USB_MASS_DEVICE6),
        STRING_TOKEN(STR_USB_MASS_DEVICE7),
        STRING_TOKEN(STR_USB_MASS_DEVICE8),
        STRING_TOKEN(STR_USB_MASS_DEVICE9),
        STRING_TOKEN(STR_USB_MASS_DEVICE10),
        STRING_TOKEN(STR_USB_MASS_DEVICE11),
        STRING_TOKEN(STR_USB_MASS_DEVICE12),
        STRING_TOKEN(STR_USB_MASS_DEVICE13),
        STRING_TOKEN(STR_USB_MASS_DEVICE14),
        STRING_TOKEN(STR_USB_MASS_DEVICE15),
        STRING_TOKEN(STR_USB_MASS_DEVICE16)

    };
    UINT8               MassDevValid[16];
    UINT8               i;
    UINTN               VariableSize;
    USB_MASS_DEV_NUM    SetupData;
    EFI_STATUS          Status;
    EFI_USB_PROTOCOL    *UsbProtocol;
//    EFI_GUID            UsbProtocolGuid = EFI_USB_PROTOCOL_GUID;
	CONNECTED_USB_DEVICES_NUM       DevNum;
    UINT32              VariableAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    USB_CONTROLLER_NUM  UsbControllerNum;

#if USB_SETUP_VARIABLE_RUNTIME_ACCESS
    VariableAttributes |= EFI_VARIABLE_RUNTIME_ACCESS;
#endif


    if (Class!=ADVANCED_FORM_SET_CLASS) {
        return;
    }
    InitString(HiiHandle, STRING_TOKEN(STR_USB_MODULE_VER), L"%02d", USB_DRIVER_MAJOR_VER);

    Status = gBS->LocateProtocol(&gLegacyUsbProtocolGuid, NULL, (VOID **) &UsbProtocol);
//####  ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return;
    }

    // Number of connected devices
    GetConnectedDevices(DevNumStr, ControllerNumStr, UsbProtocol, &DevNum);

    DEBUG((DEBUG_INFO, "Devices total: %d KBDs, %d HUBs, %d MICE, %d POINT %d MASS %d CCID\n",
        DevNum.NumUsbKbds, DevNum.NumUsbHubs, DevNum.NumUsbMice,
        DevNum.NumUsbPoint, DevNum.NumUsbMass, DevNum.NumUsbCcids));

    InitString(HiiHandle, STRING_TOKEN(STR_USB_DEVICES_ENABLED_LIST), L"%s", DevNumStr);
    InitString(HiiHandle, STRING_TOKEN(STR_USB_CONTROLLERS_ENABLED_LIST), L"%s", ControllerNumStr);

    // Mass storage device names
    for (i = 0, NextDev = 0; i < 16; i++) {
        NextDev = GetMassDeviceName( (UINT8 *) MassStr, NextDev, UsbProtocol);
        if (NextDev == 0xFF) {
            break;    // No more devices
        }
        InitString(HiiHandle, MassDev[i], L"%s", MassStr);
        if (NextDev & 0x80) {
            break;     // Last device
        }
    }

    for (i = 0; i < 16; i++) {
        if (i < DevNum.NumUsbMass) {
            MassDevValid[i] = 1;
        } else {
            MassDevValid[i] = 0;
        }
    }

    VariableSize = sizeof(USB_MASS_DEV_VALID);

    Status = gRT->SetVariable(L"UsbMassDevValid",
        &gSetupVariableGuid,
        VariableAttributes,
        VariableSize,
        &MassDevValid);

    VariableSize = sizeof(SetupData);
    Status = gRT->GetVariable(L"UsbMassDevNum",
        &gSetupVariableGuid,
        NULL,
        &VariableSize,
        &SetupData);

    if (EFI_ERROR(Status)) {
        return;
    }

    SetupData.IsInteractionAllowed = 0;
    SetupData.UsbMassDevNum = DevNum.NumUsbMass;

    Status = gRT->SetVariable(L"UsbMassDevNum",
        &gSetupVariableGuid,
        VariableAttributes,
        VariableSize,
        &SetupData);

    VariableSize = sizeof(UsbControllerNum);
    Status = gRT->GetVariable(L"UsbControllerNum",
        &gSetupVariableGuid,
        NULL,
        &VariableSize,
        &UsbControllerNum);

    if (EFI_ERROR(Status)) {
        return;
    }

    UsbControllerNum.UhciNum = DevNum.NumUhcis;
    UsbControllerNum.OhciNum = DevNum.NumOhcis;
    UsbControllerNum.EhciNum = DevNum.NumEhcis;
    UsbControllerNum.XhciNum = DevNum.NumXhcis;

    Status = gRT->SetVariable(L"UsbControllerNum",
        &gSetupVariableGuid,
        VariableAttributes,
        VariableSize,
        &UsbControllerNum);

}
