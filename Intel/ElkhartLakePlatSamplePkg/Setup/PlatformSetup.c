/** @file
  Platform Setup Routines

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:

**/

#include "SetupPrivate.h"
#include <Library/PciSegmentLib.h>
#include <Guid/GlobalVariable.h>
#include <Protocol/Wdt.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/HiiString.h>

#include <Txt.h>
#include <TxtInfoHob.h>
#include <IndustryStandard/SmBios.h>
#include <Protocol/Smbios.h>
#include <PlatformBoardId.h>
#include <Protocol/I2cIo.h>
#include <Library/GpioLib.h>
#include <SystemConfigVariable.h>

#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <BootState.h>
#include <Protocol/MePlatformGetResetType.h>
#include <Protocol/UsbIo.h>
#include <IndustryStandard/Usb.h>
#include <Library/GbeLib.h>
#include <Library/SciLib.h>
#include <Library/PeiDxeBoardIdsLib.h>
#include <CpuPcieHob.h>

//
// ME/AMT Protocol
//
#include <Protocol/HeciProtocol.h>
#include "MeSetup.h"
#include <CoreBiosMsg.h>
#include "IccSetup.h"
#include <IccSetupData.h>
#include <Library/DxeMeLib.h>
#include <Register/PchRegs.h>
#include <Uefi/UefiSpec.h>
#include <Protocol/PlatformSpecificResetFilter.h>
#include <Library/UefiRuntimeLib.h>
#include <PchResetPlatformSpecific.h>

extern BOOLEAN   mMeReset;
extern BOOLEAN   gIccReset;

static const UINT16 SECONDSCREEN_VID                                   = 0x8087;
static const UINT16 SECONDSCREEN_EINK_PID                              = 0x0A06;
static const UINT8  SECONDSCREEN_EINK_IFACE                            = 0;
static const UINT8  SECONDSCREEN_FEATURE_DISPLAY_ATTRIBUTES_REPORT_ID  = 1;
static BOOLEAN      gSTMDevFwFind = FALSE;

//
// BCD to Decimal Conversion
//
#define BCD_TO_DECIMAL(A)           (((((A) >> 4) & 0xF) * 10) + ((A) & 0xF))

GLOBAL_REMOVE_IF_UNREFERENCED EFI_HII_HANDLE            gPsHiiHandle = INVALID_HII_HANDLE;

//
// LAN PHY Revision definitions
//
#define LAN_PHY_REV_TC 0xA0
#define LAN_PHY_REV_A0 0xA1
#define LAN_PHY_REV_A1 0xA2
#define LAN_PHY_REV_A2 0xA3
#define LAN_PHY_REV_A3 0xA4
#define LAN_PHY_REV_B1 0xA5
#define LAN_PHY_REV_B2 0xA6

typedef struct _LAN_PHY_INFO {
  UINT16 LanPhyRev;
  char *LanPhyString;
} LAN_PHY_INFO;

#pragma pack(push, 1)
typedef struct {
  UINT8       ReportId;
  struct
  {
    UINT16  Width;
    UINT16  Height;
  } Dimensions;
  UINT8       BitDepth;
  UINT8       Orientation : 2;
  UINT8       SupportsCS : 1;
  UINT8       : 5; // padding
  UINT8       NumberOfBuffers;
  UINT8       NumberOfButtons;
  UINT8       NumberOfFingers;
  UINT8       NumberOfFrontLights;
  UINT32      FirmwareVersion;
  UINT32      PipSizeInBytes;
} HID_FEATURE_REPORT_DISPLAY_ATTRIBUTES;
#pragma pack(pop)

LAN_PHY_INFO LanPhyInfoTable[] = {
  {LAN_PHY_REV_TC, "(TC Stepping)"},
  {LAN_PHY_REV_A0, "(A0 Stepping)"},
  {LAN_PHY_REV_A1, "(A1 Stepping)"},
  {LAN_PHY_REV_A2, "(A2 Stepping)"},
  {LAN_PHY_REV_A3, "(A3 Stepping)"},
  {LAN_PHY_REV_B1, "(B1 Stepping)"},
  {LAN_PHY_REV_B2, "(B2 Stepping)"}
};

/**
  Determine if TXT supported on a platform based on CPU and PCH TXT capability

  @retval True          if TXT  supported on the platform

**/

BOOLEAN
IsTxtSupportedOnPlatform(
  VOID
  )
{
  TXT_INFO_HOB                  *HobList;
  TXT_INFO_DATA                 *TxtInfoData;

  HobList = NULL;
  TxtInfoData = NULL;
  ///
  /// Find TXT HOB
  ///
  HobList = (TXT_INFO_HOB *) GetFirstGuidHob (&gTxtInfoHobGuid);
  if (HobList == NULL) {
    return FALSE;
  }
  TxtInfoData = &HobList->Data;
  if (TxtInfoData == NULL) {
    return FALSE;
  }
  if (TxtInfoData->ProcessorIsTxtCapable && TxtInfoData->ChipsetIsTxtCapable)
    return TRUE;
  else
    return FALSE;
}

VOID
EFIAPI
CallbackGetLanPhyRevision (
  IN  EFI_EVENT   Event,
  IN  VOID        *Context
  );

/**
  Display ICC Profile Data

  @retval   EFI_SUCCESS       - Function successfully finishes.
**/
EFI_STATUS
EFIAPI
DisplayIccProfileData (
  VOID
  )
{
  ICC_SETUP_DATA IccSetup;
  EFI_STRING     RequestString;

  //
  // Icc Setup variable will be created only if we enter into Bios Setup.
  // Expose All the Icc Setup Data to BIOS CONFIG TOOL irrespective of the variable presence
  //
  HiiGetBrowserData (&gIccGuid, ICC_SETUP_DATA_C_NAME, sizeof (ICC_SETUP_DATA), (UINT8 *)&IccSetup);
  IccSetup.AllowAdvancedOptions  = DISPLAY;
  IccSetup.ShowFrequency = DISPLAY;
  IccSetup.ShowSpread    = DISPLAY;

  gRT->SetVariable (
         ICC_SETUP_DATA_C_NAME,
         &gIccGuid,
         EFI_VARIABLE_BOOTSERVICE_ACCESS,
         sizeof (IccSetup),
         &IccSetup
         );

  RequestString = NULL;
  HiiSetBrowserData (&gIccGuid, ICC_SETUP_DATA_C_NAME, sizeof (ICC_SETUP_DATA), (UINT8 *)&IccSetup, RequestString);

  return EFI_SUCCESS;
}

/**
  Acquire the string associated with the Index from smbios structure and return it.
  The caller is responsible for free the string buffer.

  @param    OptionalStrStart  The start position to search the string
  @param    Index             The index of the string to extract
  @param    String            The string that is extracted

  @retval   EFI_SUCCESS       The function returns EFI_SUCCESS always.
**/
EFI_STATUS
GetSmBiosStringByIndex (
  IN   CHAR8                   *OptionalStrStart,
  IN   UINT8                   Index,
  OUT  CHAR8                   **String
  )
{
  UINTN          StrSize;

  if (Index == 0) {
    *String = AllocateZeroPool (sizeof (CHAR8));
    return EFI_SUCCESS;
  }

  StrSize = 0;
  do {
    Index--;
    OptionalStrStart += StrSize;
    StrSize           = AsciiStrSize (OptionalStrStart);
  } while (OptionalStrStart[StrSize] != 0 && Index != 0);

  *String = AllocatePool (StrSize);
  ASSERT (*String != NULL);
  if (*String != NULL) {
    CopyMem (*String, OptionalStrStart, StrSize);
  }
  return EFI_SUCCESS;
}

/**
  Platform Setup Callback

  @param[in] Event         - Event based on EFI_SETUP_ENTER_GUID.
  @param[in] Context       - Pointer to the notification function's context.

**/
VOID
EFIAPI
PlatformSetupCallback (
  IN EFI_EVENT Event,
  IN VOID *Context
  )
{
  EFI_STATUS                      Status;
  UINT8                           StrIndex;
  CHAR8                           *NewString;
  UINT8                           RevisionHigh;
  UINT8                           RevisionLow;
  BOOLEAN                         BoardInfo;
  BOOLEAN                         BiosInfo;
  EFI_SMBIOS_HANDLE               SmbiosHandle;
  EFI_SMBIOS_PROTOCOL             *Smbios;
  SMBIOS_TABLE_TYPE2              *Type2Record;
  SMBIOS_TABLE_TYPE0              *Type0Record;
  EFI_SMBIOS_TABLE_HEADER         *Record;
  UINTN                           Index;
  EFI_STRING                      BoardNameString;

  gBS->CloseEvent (Event);
  BoardInfo = FALSE;
  BiosInfo = FALSE;

  Status = gBS->LocateProtocol (
                  &gEfiSmbiosProtocolGuid,
                  NULL,
                  (VOID **) &Smbios
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  do {
    Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Record, NULL);
    if (EFI_ERROR (Status)) {
      break;
    }

    if (Record->Type == EFI_SMBIOS_TYPE_BASEBOARD_INFORMATION) {
      Type2Record = (SMBIOS_TABLE_TYPE2 *) Record;
      //Update Board Name
      StrIndex = Type2Record->ProductName;
      GetSmBiosStringByIndex ((CHAR8*)((UINT8*)Type2Record + Type2Record->Hdr.Length), StrIndex, &NewString);
      InitString (gPsHiiHandle,STRING_TOKEN (STR_BOARD_NAME_VALUE),L"%a%",NewString);
      FreePool (NewString);

      BoardNameString = HiiGetString (gPsHiiHandle, STRING_TOKEN (STR_BOARD_NAME_VALUE), NULL);

      //Update Board ID
      if (BoardNameString != NULL) {
        for (Index = 0; Index < mSizeOfmBoardIndex; Index++) {
          if (StrCmp((CHAR16*)BoardNameString, mBoardIdIndex[Index]) == 0) {
            InitString (gPsHiiHandle,STRING_TOKEN (STR_BOARD_ID_VALUE),L"0x%X",Index);
            break;
          }
        }
      }

      //Update Fab ID
      StrIndex = Type2Record->Version;
      GetSmBiosStringByIndex ((CHAR8*)((UINT8*)Type2Record + Type2Record->Hdr.Length), StrIndex, &NewString);
      InitString (gPsHiiHandle,STRING_TOKEN (STR_FAB_ID_VALUE),L"%a%",NewString);
      FreePool (NewString);
      BoardInfo = TRUE;
    }
    if (Record->Type == EFI_SMBIOS_TYPE_BIOS_INFORMATION) {
      Type0Record = (SMBIOS_TABLE_TYPE0 *) Record;
      //Update EC FirmwareMajorRelease
      RevisionHigh = Type0Record->EmbeddedControllerFirmwareMajorRelease;
      //Update EC FirmwareMinorRelease
      RevisionLow = Type0Record->EmbeddedControllerFirmwareMinorRelease;
      InitString (gPsHiiHandle,STRING_TOKEN (STR_CHIP_EC_REV_VALUE),L"%02d%a%02d",RevisionHigh,".",RevisionLow);
      BiosInfo = TRUE;
    }
  } while (!(BoardInfo && BiosInfo));
}

VOID
UpdateSetUpVarRevisionString (
  EFI_HII_HANDLE HiiHandle
  )
{
  EFI_STATUS Status;
  SA_SETUP SaSetup;
  CPU_SETUP CpuSetup;
  PCH_SETUP PchSetup;
  ME_SETUP MeSetup;
  SI_SETUP SiSetup;
  SETUP_DATA SetupData;
  UINTN VarSize;

  VarSize = sizeof (ME_SETUP);
  Status = gRT->GetVariable (
                  L"MeSetup",
                  &gMeSetupVariableGuid,
                  NULL,
                  &VarSize,
                  &MeSetup
                  );

  if (!EFI_ERROR (Status)) {
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_ME_SETUP_REVISION_VALUE),
      L"%d",
      MeSetup.Revision
      );
  }

  VarSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VarSize,
                  &CpuSetup
                  );

  if (!EFI_ERROR (Status)) {
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_CPU_SETUP_REVISION_VALUE),
      L"%d",
      CpuSetup.Revision
      );
  }

  VarSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VarSize,
                  &SaSetup
                  );

  if (!EFI_ERROR (Status)) {
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_SA_SETUP_REVISION_VALUE),
      L"%d",
      SaSetup.Revision
      );
  }

  VarSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VarSize,
                  &PchSetup
                  );

  if (!EFI_ERROR (Status)) {
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_PCH_SETUP_REVISION_VALUE),
      L"%d",
      PchSetup.Revision
      );
  }

  VarSize = sizeof (SI_SETUP);
  Status = gRT->GetVariable (
                  L"SiSetup",
                  &gSiSetupVariableGuid,
                  NULL,
                  &VarSize,
                  &SiSetup
                  );

  if (!EFI_ERROR (Status)) {
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_SI_SETUP_REVISION_VALUE),
      L"%d",
      SiSetup.Revision
      );
  }

  VarSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VarSize,
                  &SetupData
                  );

  if (!EFI_ERROR (Status)) {
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_SETUP_DATA_REVISION_VALUE),
      L"%d",
      SetupData.Revision
      );
  }
}

/**
  Initialize Platform Strings

  @param[in] HiiHandle    HiiHandle Handle to HII database
  @param[in] Class        Indicates the setup class

**/
VOID
InitPlatformStrings (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  )
{
  EFI_STATUS            Status;
  UINTN                 VariableSize;
  EFI_BOOT_MODE         BootMode;
  ME_INFO_SETUP_DATA    MeInfoSetupData;
  UINT8                 *FwMeSku[] = {
     (UINT8 *) ME_FW_IMAGE_TYPE_CONSUMER_STRING,
     (UINT8 *) ME_FW_IMAGE_TYPE_CORPORATE_STRING,
     (UINT8 *) ME_FW_IMAGE_TYPE_UNIDENTIFIED_STRING,
  };
  UINT8                 *MeFwSkuValue;
  EFI_EVENT             SetupEnterEvent;
  VOID                  *pSetupRegistration;
  EFI_EVENT             PlatformSetupEvent;
  VOID                  *Registration;
  BOOLEAN               IsTriggeredAtSetupMenu;
  BOOLEAN               HiiDataExport;
  BOOLEAN               XmlCliEnabled;
  SA_PEG_HOB            *SaPegHob;

  ///
  /// Get SaDataHob HOB
  ///
  SaPegHob = NULL;
  SaPegHob = (SA_PEG_HOB *)GetFirstGuidHob(&gSaPegHobGuid);
  if (SaPegHob != NULL) {
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_DEKEL_FIRMWARE_VERSION_VALUE),
      L"%d",
      SaPegHob->DekelFwVersion
    );
  }


  if (Class == MAIN_FORM_SET_CLASS) {

    DEBUG ((DEBUG_INFO, "<InitPlatformStrings>"));
    HiiDataExport = FALSE;
    XmlCliEnabled = FALSE;

    //
    // Preserve HiiHandle to access Strings in callbacks
    //
    if (gPsHiiHandle == INVALID_HII_HANDLE) {
      gPsHiiHandle = HiiHandle;
    }

    VariableSize = sizeof (ME_INFO_SETUP_DATA);
    Status = gRT->GetVariable (
                    L"MeInfoSetup",
                    &gMeInfoSetupGuid,
                    NULL,
                    &VariableSize,
                    &MeInfoSetupData
                    );
    if (!EFI_ERROR (Status)) {
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_ME_FW_REV_VALUE),
        L"%d.%d.%d.%d",
        MeInfoSetupData.MeMajor,
        MeInfoSetupData.MeMinor,
        MeInfoSetupData.MeHotFix,
        MeInfoSetupData.MeBuildNo
        );
    }


    //
    // Check if InitPlatformStrings is triggered via mSetupEnterGuid
    //
    IsTriggeredAtSetupMenu = FALSE;
    VariableSize = sizeof(SETUP_DATA);
    Status = gRT->GetVariable (
                    L"Setup",
                    &gSetupVariableGuid,
                    NULL,
                    &VariableSize,
                    &mSetupData
                    );
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR (Status) && mSetupData.FastBoot) {
      BootMode = GetBootModeHob();
      if ((mSetupData.SkipHIIUpdate) &&
          ((BootMode == BOOT_WITH_MINIMAL_CONFIGURATION) ||
           (BootMode == BOOT_ON_S4_RESUME) ||
           (BootMode == BOOT_ASSUMING_NO_CONFIGURATION_CHANGES))) {
        IsTriggeredAtSetupMenu = TRUE;
      }
    }

    //
    // Call routine to calculate LAN PHY Revision when entering Setup UI
    //
    if (IsTriggeredAtSetupMenu == TRUE) {
      PlatformSetupCallback (NULL, NULL);
      CallbackGetLanPhyRevision (NULL, NULL);
    } else {
      Status = gBS->CreateEvent (
                      EVT_NOTIFY_SIGNAL,
                      TPL_CALLBACK,
                      PlatformSetupCallback,
                      NULL,
                      &PlatformSetupEvent
                      );
      ASSERT_EFI_ERROR (Status);

      Status = gBS->RegisterProtocolNotify (
                      &gSetupEnterGuid,
                      PlatformSetupEvent,
                      &Registration
                      );
      ASSERT_EFI_ERROR (Status);

      Status = gBS->CreateEvent (
                      EVT_NOTIFY_SIGNAL,
                      TPL_CALLBACK,
                      CallbackGetLanPhyRevision,
                      NULL,
                      &SetupEnterEvent
                      );
      ASSERT_EFI_ERROR(Status);

      Status = gBS->RegisterProtocolNotify (
                      &gSetupEnterGuid,
                      SetupEnterEvent,
                      &pSetupRegistration
                      );
      ASSERT_EFI_ERROR(Status);
    }

    if (mMeSetup.MeImageType == ME_IMAGE_CONSUMER_SKU_FW) {
      MeFwSkuValue = FwMeSku[0];
    } else if (mMeSetup.MeImageType == ME_IMAGE_CORPORATE_SKU_FW) {
      MeFwSkuValue = FwMeSku[1];
    } else  {
      MeFwSkuValue = FwMeSku[2];
    }
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_ME_FW_SKU_VALUE),
      L"%a",
      MeFwSkuValue
      );

    //
    // Platform/PCH TXT capability
    //
    if (IsTxtSupportedOnPlatform() == TRUE) {
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_PLATFORM_TXT_VALUE),
        L"%a",
        "Supported"
        );
    } else {
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_PLATFORM_TXT_VALUE),
        L"%a",
        "Unsupported"
        );
    }

    //
    // Production Type
    //
    if (MmioRead32(TXT_PUBLIC_BASE + 0x200) & BIT31) {
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_PRODUCTION_TYPE_VALUE),
        L"%a",
        "Production"
        );
    } else {
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_PRODUCTION_TYPE_VALUE),
        L"%a",
        "Pre-Production"
        );
    }

    //
    // if HiiExport variable is present bios will update the BoardID, FabID, KSC version and LanPhyversion without entering into setup
    //
    if (HiiDataExport || XmlCliEnabled) {
      PlatformSetupCallback (NULL, NULL);
      CallbackGetLanPhyRevision (NULL, NULL);
      DisplayIccProfileData ();
    }

    //
    // Report the SCI FW boot result
    //
    if (SciBootReady ()) {
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_PLATFORM_SCI_VALUE),
        L"%a",
        "Complete"
        );
    } else {
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_PLATFORM_SCI_VALUE),
        L"%a",
        "N/A"
        );
    }
  }

  UpdateSetUpVarRevisionString (HiiHandle);
}

/**
  Call Back function for retrieves STM32 Firmware version

  @param[in] HiiHandle  Handle to HII database
  @param[in] Class      Indicates the setup class
  @param[in] SubClass   Indicates setup Subclass
  @param[in] Key        Key of Setup token

**/
VOID
GetSTM32FwVersionCallback (
  IN EFI_HII_HANDLE HiiHandle,
  IN UINT16         Class,
  IN UINT16         SubClass,
  IN UINT16         Key
  )
{
  EFI_STATUS                      Status;
  EFI_HANDLE                      *HandleArray = NULL;
  UINTN                           HandleArrayCount;
  EFI_USB_IO_PROTOCOL             *UsbIoProtocol = NULL;
  UINTN                           HandleIndex;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  EFI_USB_DEVICE_DESCRIPTOR       DeviceDescriptor;
  EFI_USB_INTERFACE_DESCRIPTOR    InterfaceDescriptor;
  EFI_USB_DEVICE_REQUEST          Request;
  UINT32                          TransferStatus;
  HID_FEATURE_REPORT_DISPLAY_ATTRIBUTES   FeatureReport;

  if (!gSTMDevFwFind) {
    if (PcdGet8 (PcdBoardType) == BoardTypeSds) {
      // Get all of the handles that support the USB IO protocol
      Status = gBS->LocateHandleBuffer (
                      ByProtocol,
                      &gEfiUsbIoProtocolGuid,
                      NULL,
                      &HandleArrayCount,
                      &HandleArray
                      );

      if (!EFI_ERROR (Status)) {
        // For each handle, we are going to see if it is the Second Screen device we want.
        for (HandleIndex = 0; HandleIndex < HandleArrayCount; ++HandleIndex) {
          DevicePath = DevicePathFromHandle (HandleArray[HandleIndex]);
          if (!DevicePath) {
            continue;
          }
          // Until we hit a device end not in the device path, look until we find
          // a USB node.  If we find a USB node, go ahead and get an open handle
          // to the protocol and get the USB device descriptor.  If the VID and PID
          // match the Second Screen VID/PID we have our device.
          while (!IsDevicePathEnd(DevicePath)) {
            if ((MESSAGING_DEVICE_PATH == DevicePathType(DevicePath)) &&
                (MSG_USB_DP == DevicePathSubType(DevicePath))) {
              // Connect to the controller
              gBS->ConnectController(HandleArray[HandleIndex], NULL, NULL, FALSE);

              // Open the USB IO protocol so we can talk to our device
              Status = gBS->OpenProtocol (
                              HandleArray[HandleIndex],
                              &gEfiUsbIoProtocolGuid,
                              (VOID **) &UsbIoProtocol,
                              NULL,
                              NULL,
                              EFI_OPEN_PROTOCOL_GET_PROTOCOL
                              );
              if (EFI_ERROR (Status)) {
                break;
              }
              // Get the device descriptor from the device
              Status = UsbIoProtocol->UsbGetDeviceDescriptor (
                                        UsbIoProtocol,
                                        &DeviceDescriptor
                                        );
              if (EFI_ERROR (Status)) {
                break;
              }

              // See if the VID and PID match our device
              if ((SECONDSCREEN_VID == DeviceDescriptor.IdVendor) &&
                  (SECONDSCREEN_EINK_PID == DeviceDescriptor.IdProduct)) {
                // Since the Second Screen device has multiple interfaces, we need to
                // make sure that we are talking to the correct one for the eInk screen.
                Status = UsbIoProtocol->UsbGetInterfaceDescriptor (
                                          UsbIoProtocol,
                                          &InterfaceDescriptor
                                          );

                if ((EFI_SUCCESS == Status) &&
                    (SECONDSCREEN_EINK_IFACE == InterfaceDescriptor.InterfaceNumber)) {
                  // Zero out the local feature report and set the report ID appropriately.
                  ZeroMem (&FeatureReport, sizeof (FeatureReport));
                  FeatureReport.ReportId = SECONDSCREEN_FEATURE_DISPLAY_ATTRIBUTES_REPORT_ID;
                  // Construct the control transfer request:
                  // HID get feature report
                  Request.RequestType   = USB_HID_CLASS_GET_REQ_TYPE;
                  Request.Request       = EFI_USB_GET_REPORT_REQUEST;
                  Request.Value         = (UINT16) ((HID_FEATURE_REPORT << 8) |
                                          SECONDSCREEN_FEATURE_DISPLAY_ATTRIBUTES_REPORT_ID);
                  Request.Index         = 0;
                  Request.Length        = (UINT16) sizeof (FeatureReport);
                  // Issue the request to get the feature report
                  Status = UsbIoProtocol->UsbControlTransfer (
                                            UsbIoProtocol,
                                            &Request,
                                            EfiUsbDataIn,
                                            3000,
                                            &FeatureReport,
                                            sizeof (FeatureReport),
                                            &TransferStatus
                                            );
                  if (EFI_ERROR (Status)) {
                    break;
                  }
                  // Here is where you will grab the firmware version from the feature report.
                  // You can also probably stop looping as we have found our device.
                  InitString (gPsHiiHandle, STRING_TOKEN (STR_CHIP_STM_REV_VALUE), L"%d", FeatureReport.FirmwareVersion);
                  gSTMDevFwFind = TRUE;
                  break;
                }
              }
            }
            DevicePath = NextDevicePathNode (DevicePath);
          }
        }
      }
      if (HandleArray != NULL) {
        FreePool (HandleArray);
      }
    }
  }
}

/**
  Retrieves LAN PHY Revision

  @param[in] Event         - Event based on EFI_SETUP_ENTER_GUID.
  @param[in] Context       - Pointer to the notification function's context.

**/
VOID
EFIAPI
CallbackGetLanPhyRevision (
  IN  EFI_EVENT   Event,
  IN  VOID        *Context
  )
{
  EFI_STATUS      Status;
  UINT16          LanPhyRev;
  UINTN           Index;
  BOOLEAN         LanPhyRevisionUpdated;

  LanPhyRev = 0;
  LanPhyRevisionUpdated = FALSE;

  //
  // Get Phy Version
  //
  Status = GbeGetLanPhyRevision (&LanPhyRev);
  if (Status == EFI_NOT_FOUND) {
    return;
  }
  //
  // Close event, so it will not be invoked again.
  //
  gBS->CloseEvent (Event);

  if (EFI_ERROR (Status)) {
    return;
  }

  //
  // LAN PHY Revision
  //
  if (LanPhyRev) {
    for (Index = 0; Index < (sizeof (LanPhyInfoTable) / sizeof (LAN_PHY_INFO)); Index++) {
      if ((UINT8) LanPhyRev == LanPhyInfoTable[Index].LanPhyRev) {
        InitString (
          gPsHiiHandle,
          STRING_TOKEN (STR_LAN_PHY_REV_VALUE),
          L"%02x %a",
          (UINT8) LanPhyRev,
          LanPhyInfoTable[Index].LanPhyString
          );
        LanPhyRevisionUpdated = TRUE;
        break;
      }
    }

    if (LanPhyRevisionUpdated == FALSE) {
      InitString (
        gPsHiiHandle,
        STRING_TOKEN (STR_LAN_PHY_REV_VALUE),
        L"%02x",
        (UINT8) LanPhyRev
        );
    }
  }

  return;
}

/**
  Determines if Full Sku ME is present.

  @retval TRUE     if fullSku ME is present

**/
BOOLEAN
IsFullSkuMePresent (
  VOID
  )
{
  EFI_STATUS        Status;
  HECI_PROTOCOL     *Heci;
  UINT32            MeMode;
  BOOLEAN           RetVal;

  RetVal = FALSE;
  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (!EFI_ERROR (Status)) {
    Status = Heci->GetMeMode (&MeMode);
    //
    // ASSERT_EFI_ERROR (Status);
    //
    if (!EFI_ERROR (Status)) {
      if (MeMode == ME_MODE_NORMAL) {
        RetVal = TRUE;
      }
    }
  }

  return RetVal;
}

/**
  Determines if SusPwrDnAck needs to be set.
  For IbexPeak Platform with EC support, SusPwrDnAck should be to set.

  @retval TRUE        if SusPwrDnAck needs to be set

**/
BOOLEAN
CheckIfSetSusPwrDnAck (
  VOID
  )
{
  EFI_STATUS          Status;
  UINTN               VariableSize;
  SETUP_VOLATILE_DATA SetupVolatileData;
  BOOLEAN             SusPwrDnAck;

  SusPwrDnAck  = FALSE;

  VariableSize = sizeof (SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupVolatileData
                  );
  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR (Status)) {
    if ((SetupVolatileData.PlatformFlavor == FlavorMobile) ||
        (SetupVolatileData.PlatformFlavor == FlavorEmbedded)) {
      SusPwrDnAck = TRUE;
    }
  }

  return SusPwrDnAck;
}

/**
  Platform Reset function

  @param[in] PlatformResetType          Reset type aligned with EFI_RESET_TYPE

  @retval EFI_RESET_TYPE                final reset type aligned with EFI_RESET_TYPE

**/
EFI_RESET_TYPE
PlatformReset (
  IN  EFI_RESET_TYPE       PlatformResetType
  )
{
  EFI_STATUS               Status;
  UINTN                    VariableSize;

  //
  // Reset Flag
  //
  BOOLEAN                  GlobalResetRequired = FALSE;
  BOOLEAN                  PowerCycleResetRequired = FALSE;

  SETUP_DATA               CurrentData;
  SETUP_DATA               SetupData;
  SA_SETUP                 SaCurrentData;
  SA_SETUP                 SaSetup;
  CPU_SETUP                CpuCurrentData;
  CPU_SETUP                CpuSetup;
  PCH_SETUP                PchCurrentData;
  PCH_SETUP                PchSetup;
  SI_SETUP                 SiSetup;
  SI_SETUP                 SiCurrentData;
  EFI_HANDLE               Handle;

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupData
                  );
  //
  // ASSERT_EFI_ERROR (Status);
  //
  if (EFI_ERROR (Status)) {
    return PlatformResetType;
  }

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SaSetup
                  );
  if (EFI_ERROR (Status)) {
    return PlatformResetType;
  }

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &CpuSetup
                  );
  if (EFI_ERROR (Status)) {
    return PlatformResetType;
  }

  VariableSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &PchSetup
                  );
  if (EFI_ERROR (Status)) {
    return PlatformResetType;
  }


  VariableSize = sizeof (SI_SETUP);
  Status = gRT->GetVariable(
                  L"SiSetup",
                  &gSiSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SiSetup
                  );
  if (EFI_ERROR(Status)) {
    return PlatformResetType;
  }

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"ColdReset",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &CurrentData
                  );
  if (EFI_ERROR (Status)) {
    return PlatformResetType;
  }

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaColdReset",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SaCurrentData
                  );
  if (EFI_ERROR (Status)) {
    return PlatformResetType;
  }

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuColdReset",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &CpuCurrentData
                  );
  if (EFI_ERROR (Status)) {
    return PlatformResetType;
  }

  VariableSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (
                  L"PchColdReset",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &PchCurrentData
                  );
  if (EFI_ERROR (Status)) {
    return PlatformResetType;
  }


  VariableSize = sizeof (SI_SETUP);
  Status = gRT->GetVariable(
                  L"SiColdReset",
                  &gSiSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SiCurrentData
                  );
  if (EFI_ERROR(Status)) {
    return PlatformResetType;
  }

  //
  // Checks if silicon setup variables has been modified
  //
  if (CompareMem(&PchSetup, &PchCurrentData, sizeof(PchSetup)) != 0 ||
      CompareMem(&CpuSetup, &CpuCurrentData, sizeof(CpuSetup)) != 0 ||
      CompareMem(&SaSetup, &SaCurrentData, sizeof(SaSetup)) != 0 ||
      CompareMem(&SiSetup, &SiCurrentData, sizeof(SiSetup)) != 0
     ) {
    //
    // Install gPlatformConfigChangeProtocolGuid
    //
    Handle = NULL;
    gBS->InstallProtocolInterface(
      &Handle,
      &gPlatformConfigChangeProtocolGuid,
      EFI_NATIVE_INTERFACE,
      NULL
      );
  }

  //
  // Change boot mode for critical setup questions.
  //
  if ((PchSetup.SataInterfaceMode != PchCurrentData.SataInterfaceMode) ||
      (SetupData.PxeRom != CurrentData.PxeRom) ||
      (SetupData.EfiNetworkSupport != CurrentData.EfiNetworkSupport)
     ) {
    //
    // Delete BootState variable to force next boot is FullConfiguration boot
    // Boot option enumeration only happens in FullConfiguration boot
    //
    gRT->SetVariable (
           BOOT_STATE_VARIABLE_NAME,
           &gBootStateGuid,
           0,
           0,
           NULL
           );
  }

  if ((SaSetup.EnableVtd != SaCurrentData.EnableVtd) ||
      (PchSetup.PchHdAudio != PchCurrentData.PchHdAudio) ||
      (CpuSetup.Txt != CpuCurrentData.Txt) ||
      (SaSetup.GTTSize != SaCurrentData.GTTSize) ||
      (SaSetup.IgdDvmt50PreAlloc != SaCurrentData.IgdDvmt50PreAlloc) ||
      (SaSetup.MaxTolud != SaCurrentData.MaxTolud) ||
      (SaSetup.InternalGraphics != SaCurrentData.InternalGraphics) ||
      (SaSetup.PrimaryDisplay != SaCurrentData.PrimaryDisplay) ||
      (SaSetup.SpdProfileSelected != SaCurrentData.SpdProfileSelected) ||
      (CpuSetup.BiosGuard != CpuCurrentData.BiosGuard) ||
      (CpuSetup.BiosGuardToolsInterface != CpuCurrentData.BiosGuardToolsInterface)
      ) {
    PowerCycleResetRequired = TRUE;
  }

  if (mMeReset
    ) {
    GlobalResetRequired = TRUE;
  }

  if (gIccReset) {
    PowerCycleResetRequired = TRUE;
  }

  if ((CpuSetup.ConfigTdpLevel != CpuCurrentData.ConfigTdpLevel) ||
     (CpuSetup.ConfigTdpLock != CpuCurrentData.ConfigTdpLock) ||
     (CpuSetup.Custom1TurboActivationRatio != CpuCurrentData.Custom1TurboActivationRatio) ||
     (CpuSetup.Custom2TurboActivationRatio != CpuCurrentData.Custom2TurboActivationRatio) ||
     (CpuSetup.Custom3TurboActivationRatio != CpuCurrentData.Custom3TurboActivationRatio)
    ) {
    PowerCycleResetRequired = TRUE;
  }

  if (CpuSetup.EnableSgx != CpuCurrentData.EnableSgx) {
    PowerCycleResetRequired = TRUE;
  }

  //
  // CrashLog variable set in PMC needs a G3 or global reset to clear it up.
  //
  if ((SetupData.EnableCrashLog != CurrentData.EnableCrashLog) ||
      (SetupData.CrashLogOnAllReset != CurrentData.CrashLogOnAllReset)) {
    GlobalResetRequired = TRUE;
  }

  //
  // Doesn't need to do platform special reset
  //
  if (GlobalResetRequired) {
    return EfiResetPlatformSpecific;
  } else if (PowerCycleResetRequired) {
    return EfiResetCold;
  }

  return PlatformResetType;
}



VOID
InitBoardStrings (
  EFI_HII_HANDLE  HiiHandle,
  UINT16          Class
  )
{
  return;
}

/**
  ThermalFunctionCallback() is called when we enter Thermal Configuration Form
  When "Enable All Thermal Functions" setup option value is changed then it updated
  as below:
   "Enable All Thermal Functions" is enabled it enables:
     1. Memory Thermal Management
     2. Active Trip Points
     3. Critical Trip Points
   "Enable All Thermal Functions" option is disabled then "Memory Thermal Management",
   Active ,Critical Trip Points option is disabled
**/

EFI_STATUS
EFIAPI
ThermalFunctionCallback (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  SA_SETUP    *SaSetup;
  SETUP_DATA  SetupData;
  UINTN       VarSize;
  EFI_STATUS  Status;
  EFI_STRING  RequestString;

  RequestString = NULL;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  VarSize = sizeof (SA_SETUP);
  SaSetup = AllocatePool (VarSize);
  ASSERT (SaSetup != NULL);
  if (SaSetup == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //   "Enable All Thermal Functions" option is enabled then "Memory Thermal Management" option is enabled
  //   "Enable All Thermal Functions" option is disabled then "Memory Thermal Management" option is disabled
  //
  Status = HiiGetBrowserData (&gSaSetupVariableGuid, L"SaSetup", VarSize, (UINT8 *) SaSetup);
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    if(!(SaSetup->MemoryThermalManagement == Value->u8) ) {
      SaSetup->MemoryThermalManagement = Value->u8;
      RequestString = NULL;
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, MemoryThermalManagement),sizeof(SaSetup->MemoryThermalManagement));

      if (RequestString != NULL) {
        Status = HiiSetBrowserData (&gSaSetupVariableGuid, L"SaSetup", VarSize, (UINT8 *) SaSetup, RequestString);
        ASSERT_EFI_ERROR (Status);
        FreePool (RequestString);
      }
    }
  }

  VarSize = sizeof(SETUP_DATA);
  Status = HiiGetBrowserData(&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) &SetupData);
  ASSERT_EFI_ERROR(Status);

  //
  //   "Enable All Thermal Functions" option is enabled  then  "Active Trip Points", "Critical Trip Points"  option is enabled
  //   "Enable All Thermal Functions" option is disabled then  "Active Trip Points", "Critical Trip Points" option is disabled
  //
  if (!EFI_ERROR (Status)) {
    if(!(SetupData.DisableActiveTripPoints == Value->u8) ) {
      SetupData.DisableActiveTripPoints = Value->u8;
      RequestString = NULL;
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DisableActiveTripPoints),sizeof(SetupData.DisableActiveTripPoints));

      if (RequestString != NULL) {
        Status = HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) &SetupData, RequestString);
        ASSERT_EFI_ERROR (Status);
        FreePool (RequestString);
      }
    }

    if(!(SetupData.DisableCriticalTripPoints == Value->u8) ) {
      SetupData.DisableCriticalTripPoints = Value->u8;
      RequestString = NULL;
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DisableCriticalTripPoints),sizeof(SetupData.DisableCriticalTripPoints));
    }
    if (RequestString != NULL) {
      Status = HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) &SetupData, RequestString);
      ASSERT_EFI_ERROR (Status);
      FreePool (RequestString);
    }
  }
  FreePool (SaSetup);
  return Status;
}



/**
  setup reset call back function

  @param[in] ResetType            UEFI defined reset type.
  @param[in] ResetStatus          The status code for the reset.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.
**/
VOID
EFIAPI
PlatformSetupResetCallback (
  IN EFI_RESET_TYPE           ResetType,
  IN EFI_STATUS               ResetStatus,
  IN UINTN                    DataSize,
  IN VOID                     *ResetData OPTIONAL
  )
{
  static BOOLEAN              IsExecuted;
  EFI_RESET_TYPE              OrgResetType;
  PCH_RESET_DATA              NewResetData;


  if (IsExecuted) return;
  IsExecuted = TRUE;

  DEBUG ((DEBUG_INFO,"PlatformSetupResetCallback() Executed\n"));


  OrgResetType = ResetType;
  ResetType = PlatformReset (ResetType);
  if(OrgResetType == ResetType) return;

  DEBUG((DEBUG_INFO,"new ResetType is %d\n",ResetType));

  if(ResetType != EfiResetPlatformSpecific) {
    gRT->ResetSystem (ResetType, EFI_SUCCESS, 0, NULL);
  } else {
    DataSize = sizeof (PCH_RESET_DATA);
    CopyMem (&NewResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
    StrCpyS (NewResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
    gRT->ResetSystem (EfiResetPlatformSpecific, EFI_SUCCESS, DataSize, &NewResetData);
  }
}

/**
  Hook the system reset to properly reset function for platform setup reset

  @param[in]  Event     Event whose notification function is being invoked
  @param[in]  Context   Pointer to the notification function's context
**/
VOID
EFIAPI
OnResetFilterInstall (
  IN EFI_EVENT                      Event,
  IN VOID                           *Context
  )
{
  EFI_STATUS                      Status;
  EFI_RESET_NOTIFICATION_PROTOCOL *ResetNotify;

  Status = gBS->LocateProtocol (&gEdkiiPlatformSpecificResetFilterProtocolGuid, NULL, (VOID **) &ResetNotify);
  if (!EFI_ERROR (Status)) {
    Status = ResetNotify->RegisterResetNotify (ResetNotify, PlatformSetupResetCallback);
    if (Event) gBS->CloseEvent (Event);
  }

}

/**
  add a reset filter protocol call back for setup exit funciton

**/
VOID
InstallPlatfromReset (
  VOID
  )
{
  VOID   *Registration;

  EfiCreateProtocolNotifyEvent (
    &gEdkiiPlatformSpecificResetFilterProtocolGuid,
    TPL_CALLBACK,
    OnResetFilterInstall,
    NULL,
    &Registration
    );
}

/**
  Initializes xHCI ACPI Path Name and String Length

  @retval EFI_SUCCESS            Successfully completed updates.
  @retval EFI_NOT_FOUND          Setup data not found.
  @retval EFI_OUT_OF_RESOURCES   Allocation failure for Setup data.
**/
EFI_STATUS
SdevXhciAcpiPathNameUpdate (
  VOID
  )
{
  SETUP_DATA              *CurrentUserSetupData;
  UINTN                   VarSize;
  EFI_STATUS              Status;
  EFI_STRING              RequestString             = NULL;
  UINT16                  Device1AcpiPathName[]     = L"\\_SB.PC00.XHCI.RHUB.HS00.CRGB";
  UINT16                  Device2AcpiPathName[]     = L"\\_SB.PC00.XHCI.RHUB.HS01.CIR";

  VarSize              = sizeof (SETUP_DATA);
  CurrentUserSetupData = AllocatePool (VarSize);
  ASSERT (CurrentUserSetupData != NULL);

  if (CurrentUserSetupData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = HiiGetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) CurrentUserSetupData);
  ASSERT_EFI_ERROR (Status);
  if (Status != TRUE) {
    FreePool (CurrentUserSetupData);
    return EFI_NOT_FOUND;
  }

  ///
  /// Populate xHCI Device 1 ACPI Path Name and Length with default value
  ///
  if (CurrentUserSetupData->SdevXhciAcpiPathNameDevice1[0] == 0x0) {
    ZeroMem (CurrentUserSetupData->SdevXhciAcpiPathNameDevice1, sizeof (CurrentUserSetupData->SdevXhciAcpiPathNameDevice1));
    CurrentUserSetupData->SdevXhciAcpiPathStringLength[0] = (UINT16) (StrLen (Device1AcpiPathName) + 1);
    CopyMem (CurrentUserSetupData->SdevXhciAcpiPathNameDevice1, Device1AcpiPathName, StrSize (Device2AcpiPathName));
  }

  ///
  /// Populate xHCI Device 2 ACPI Path Name and Length with default value
  ///
  if (CurrentUserSetupData->SdevXhciAcpiPathNameDevice2[0] == 0x0) {
    ZeroMem (CurrentUserSetupData->SdevXhciAcpiPathNameDevice2, sizeof (CurrentUserSetupData->SdevXhciAcpiPathNameDevice2));
    CurrentUserSetupData->SdevXhciAcpiPathStringLength[1] = (UINT16) (StrLen (Device2AcpiPathName) + 1);
    CopyMem (CurrentUserSetupData->SdevXhciAcpiPathNameDevice2, Device2AcpiPathName, StrSize (Device2AcpiPathName));
  }

  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, SdevXhciAcpiPathNameDevice1), sizeof (CurrentUserSetupData->SdevXhciAcpiPathNameDevice1));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, SdevXhciAcpiPathNameDevice2), sizeof (CurrentUserSetupData->SdevXhciAcpiPathNameDevice2));
  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, SdevXhciAcpiPathStringLength), sizeof (CurrentUserSetupData->SdevXhciAcpiPathStringLength));

  if (RequestString != NULL) {
    VarSize = sizeof (SETUP_DATA);
    Status = HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) CurrentUserSetupData, RequestString);
    ASSERT_EFI_ERROR (Status);
    FreePool (RequestString);
    if (Status != TRUE) {
      return EFI_NOT_FOUND;
    }
  }

  FreePool (CurrentUserSetupData);

  return EFI_SUCCESS;
}

/**
  Updates xHCI ACPI Path Name and String Length

  @param[IN]       EFI_FORM_CALLBACK_PROTOCOL   *This
  @param[IN]       EFI_BROWSER_ACTION           Action,
  @param[IN]       EFI_QUESTION_ID              KeyValue
  @param[IN]       UINT8                        Type,
  @param[IN]       EFI_IFR_TYPE_VALUE           *Value,
  @param[IN]       EFI_BROWSER_ACTION_REQUEST   *ActionRequest

  @retval EFI_SUCCESS            Successfully completed updates.
  @retval EFI_NOT_FOUND          Setup data not found.
  @retval EFI_UNSUPPORTED        Unsupported browser action.
  @retval EFI_OUT_OF_RESOURCES   Allocation failure for Setup data.
**/
EFI_STATUS
EFIAPI
VtioFormCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  SETUP_DATA              *CurrentUserSetupData;
  UINTN                   VarSize;
  EFI_STATUS              Status;
  EFI_STRING              RequestString = NULL;
  UINT8                   Index = 0;

  ///
  /// No action to perform on Action Changing
  ///
  if (Action == EFI_BROWSER_ACTION_CHANGING) {
    return EFI_SUCCESS;
  }

  ///
  /// Initializations on form open
  ///
  if (Action == EFI_BROWSER_ACTION_FORM_OPEN) {
    return SdevXhciAcpiPathNameUpdate ();
  }

  ///
  /// No action to perform on Action Changed
  ///
  if (Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  VarSize               = sizeof (SETUP_DATA);
  CurrentUserSetupData  = AllocatePool (VarSize);
  ASSERT (CurrentUserSetupData != NULL);

  if (CurrentUserSetupData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  ///
  /// GetBrowserData by VarStore Name (Setup)
  ///
  Status = HiiGetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) CurrentUserSetupData);
  ASSERT_EFI_ERROR (Status);
  if (Status != TRUE) {
    FreePool (CurrentUserSetupData);
    return EFI_NOT_FOUND;
  }

  switch (KeyValue) {
    case KEY_SdevXhciAcpiPathNameDevice1:
      ///
      /// Update xHCI ACPI Path Name
      /// Ensure last entry is NULL terminator
      ///
      CurrentUserSetupData->SdevXhciAcpiPathNameDevice1[48] = 0x00;

      ///
      /// Update xHCI ACPI Path String Length
      ///
      if (CurrentUserSetupData->SdevXhciAcpiPathNameDevice1[0] == 0x0) {
        CurrentUserSetupData->SdevXhciAcpiPathStringLength[0] = 0;
      } else {
        Index = 0;
        while (CurrentUserSetupData->SdevXhciAcpiPathNameDevice1[Index] != 0x0) {
          Index++;
        }
        CurrentUserSetupData->SdevXhciAcpiPathStringLength[0] = Index + 1;
      }

      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, SdevXhciAcpiPathStringLength), sizeof (CurrentUserSetupData->SdevXhciAcpiPathStringLength));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, SdevXhciAcpiPathNameDevice1), sizeof (CurrentUserSetupData->SdevXhciAcpiPathNameDevice1));
      if (RequestString != NULL) {
        VarSize = sizeof (SETUP_DATA);
        Status = HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) CurrentUserSetupData, RequestString);
        ASSERT_EFI_ERROR (Status);
        FreePool (RequestString);
        if (Status != TRUE) {
          FreePool (CurrentUserSetupData);
          Status = EFI_NOT_FOUND;
        }
      }
      Status = EFI_SUCCESS;
      break;

    case KEY_SdevXhciAcpiPathNameDevice2:
      ///
      /// Update xHCI ACPI Path Name
      /// Ensure last entry is NULL terminator
      ///
      CurrentUserSetupData->SdevXhciAcpiPathNameDevice2[48] = 0x00;

      ///
      /// Update xHCI ACPI Path String Length
      ///
      if (CurrentUserSetupData->SdevXhciAcpiPathNameDevice2[0] == 0x0) {
        CurrentUserSetupData->SdevXhciAcpiPathStringLength[1] = 0;
      } else {
        Index = 0;
        while (CurrentUserSetupData->SdevXhciAcpiPathNameDevice2[Index] != 0x0) {
          Index++;
        }
        CurrentUserSetupData->SdevXhciAcpiPathStringLength[1] = Index + 1;
      }

      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, SdevXhciAcpiPathStringLength), sizeof (CurrentUserSetupData->SdevXhciAcpiPathStringLength));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, SdevXhciAcpiPathNameDevice2), sizeof (CurrentUserSetupData->SdevXhciAcpiPathNameDevice2));
      if (RequestString != NULL) {
        VarSize = sizeof (SETUP_DATA);
        Status = HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) CurrentUserSetupData, RequestString);
        ASSERT_EFI_ERROR (Status);
        FreePool (RequestString);
        if (Status != TRUE) {
          FreePool (CurrentUserSetupData);
          Status = EFI_NOT_FOUND;
        }
      }
      Status = EFI_SUCCESS;
      break;
  default:
    Status = EFI_UNSUPPORTED;
  }

  FreePool (CurrentUserSetupData);

  return Status;
}
