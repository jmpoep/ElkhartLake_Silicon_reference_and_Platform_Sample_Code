/** @file
  This file implements firmware version information.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:

**/

#include <PiDxe.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Guid/EventGroup.h>

#include <Protocol/Smbios.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/IccOverClocking.h>
#include <Protocol/GopComponentName2.h>

#include <PlatformInfo.h>
#include <Library/PciSegmentLib.h>
#include <Library/SiFviLib.h>
#include <PlatformBoardConfig.h>
#include <Library/BoardConfigLib.h>
#include <Library/DxeFirmwareVersionInfoLib.h>
#include <Library/GbeLib.h>

#include <Register/PchRegs.h>

#include <IndustryStandard/Pci30.h>

GLOBAL_REMOVE_IF_UNREFERENCED CONST CHAR8 StrEnabled[] = PLATFORM_FVI_STATUS_ENABLED;

GLOBAL_REMOVE_IF_UNREFERENCED FVI_DATA mPlatformFviData[] = {
  FVI_VERSION (LAN_PHY_VERSION),
  FVI_VERSION (SENSOR_FW_VERSION),
  FVI_VERSION (DEBUG_MODE_VERSION),
  FVI_VERSION (PERFORMANCE_MODE_VERSION),
  FVI_VERSION (DEBUG_USE_USB_VERSION),
  FVI_VERSION (ICC_OVERLOCKING_VERSION),
  FVI_VERSION (UNDI_VERSION),
  FVI_VERSION (EC_VERSION),
  FVI_VERSION (GOP_VERSION),
  FVI_VERSION (ROYALPARK_VERSION),
  FVI_VERSION (PLATFORM_VERSION),
  FVI_VERSION (CLIENT_SILICON_VERSION),
};

GLOBAL_REMOVE_IF_UNREFERENCED FVI_HEADER mPlatformFviHeader = DEFAULT_FVI_HEADER_DATA(mPlatformFviData);

GLOBAL_REMOVE_IF_UNREFERENCED FVI_STRINGS mPlatformFviStrings[] = {
  { LAN_PHY_FVI_STRING,          NULL, },
  { SENSOR_FW_FVI_STRING,        NULL, },
  { DEBUG_MODE_STATUS,           PLATFORM_FVI_STATUS_DISABLED, },
  { PERFORMANCE_MODE_STATUS,     PLATFORM_FVI_STATUS_DISABLED, },
  { DEBUG_USE_USB_STATUS,        PLATFORM_FVI_STATUS_DISABLED, },
  { ICC_OVERLOCKING_FVI_STRING,  NULL, },
  { UNDI_FVI_STRING,             NULL, },
  { EC_FVI_STRING,               NULL, },
  { GOP_FVI_STRING,              NULL, },
  { ROYALPARK_FVI_STRING,        NULL, },
  { PLATFORM_FVI_STRING,         NULL, },
  { CLIENT_SILICON_FVI_STRING,   NULL, },
};

/**
  Get EC Version
**/
VOID
GetEcVersion(
  VOID
  )
{
  EFI_STATUS              Status;
  EFI_SMBIOS_HANDLE       SmbiosHandle;
  EFI_SMBIOS_PROTOCOL     *mSmbios;
  SMBIOS_TABLE_TYPE0      *Type0Record;
  EFI_SMBIOS_TABLE_HEADER *Record;

  Status = gBS->LocateProtocol (
                  &gEfiSmbiosProtocolGuid,
                  NULL,
                  (VOID **)&mSmbios
                  );
  if (!EFI_ERROR (Status)) {
    SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
    do {
      Status = mSmbios->GetNext (mSmbios, &SmbiosHandle, NULL, &Record, NULL);
      if (EFI_ERROR(Status)) {
        break;
      }
      if (Record->Type == EFI_SMBIOS_TYPE_BIOS_INFORMATION) {
        Type0Record = (SMBIOS_TABLE_TYPE0 *) Record;
        mPlatformFviData[EC_VER].Version.MajorVersion = Type0Record->EmbeddedControllerFirmwareMajorRelease;
        mPlatformFviData[EC_VER].Version.MinorVersion = Type0Record->EmbeddedControllerFirmwareMinorRelease;
        mPlatformFviData[EC_VER].Version.Revision     = 0;
        mPlatformFviData[EC_VER].Version.BuildNum     = 0;
        break;
      }
    } while (Record->Type != EFI_SMBIOS_TYPE_BIOS_INFORMATION);
  }
}

/**
  Retrieves LAN PHY Revision by reading register at the first boot time
  after flashing FW image or updating capsule and set into NV variable.
  Then get the revision from NV varialbe during POST at the other time.
**/
VOID
GetLanPhyVersion(
  VOID
  )
{
  EFI_STATUS         Status;
  UINT16             LanPhyRev;
  PLATFORM_FVI_SETUP PlatformFviSetup = {0};
  UINTN              VariableSize;

  LanPhyRev = 0;

  VariableSize = sizeof (PLATFORM_FVI_SETUP);
  Status = gRT->GetVariable (
                  PLATFORM_FVI_SETUP_NAME,
                  &gPlatformFviSetupGuid,
                  NULL,
                  &VariableSize,
                  &PlatformFviSetup
                  );

  if (!EFI_ERROR(Status) && (PlatformFviSetup.LanPhyVersion != 0)) {
    //
    // The other time, to get Lan Phy revision from NV.
    //
     LanPhyRev = (UINT16) PlatformFviSetup.LanPhyVersion;
  } else if (Status == EFI_NOT_FOUND) {

    Status = GbeGetLanPhyRevision (&LanPhyRev);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "GetLanPhyVersion failed to obtain Phy Revision. Status: %r\n", Status));
      LanPhyRev = 0;
    }

    PlatformFviSetup.LanPhyVersion = (UINT8) LanPhyRev;
    gRT->SetVariable (
           PLATFORM_FVI_SETUP_NAME,
           &gPlatformFviSetupGuid,
           EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
           sizeof(PLATFORM_FVI_SETUP),
           &PlatformFviSetup
           );
  }

  //
  // LAN PHY Revision
  //
  mPlatformFviData[LAN_PHY_VER].Version.MajorVersion = 0;
  mPlatformFviData[LAN_PHY_VER].Version.MinorVersion = 0;
  mPlatformFviData[LAN_PHY_VER].Version.BuildNum = LanPhyRev;
  mPlatformFviData[LAN_PHY_VER].Version.Revision = 0;

  return;
}


/**
  Update the Debug Mode Status, Performance Mode Status and Debug Use USB Status.

**/
VOID
UpdateDebugInformation(
  VOID
  )
{
  //
  // Default debug mode is disabled and update when MDEPKG_NDEBUG is False
  //
  DEBUG_CODE(mPlatformFviStrings[DEBUG_MODE_VER].VersionString = (CHAR8 *) &StrEnabled;);

  //
  // Default Performance mode is disabled and update it when PcdPerformanceEnable is TRUE.
  //
#if FixedPcdGetBool(PcdPerformanceEnable) == 1
  mPlatformFviStrings[PERFORMANCE_MODE_VER].VersionString = (CHAR8 *) &StrEnabled;
#endif

  //
  // Default Debug usage is Serial port and update it when PcdSourceDebugUseUsb is TRUE.
  //
#if FixedPcdGetBool(PcdSourceDebugUseUsb) == 1
  mPlatformFviStrings[DEBUB_USE_USB_VER].VersionString = (CHAR8 *) &StrEnabled;
#endif
}

/**
  Get Icc Overclock version from the ICC_OVERCLOCKING_PROTOCOL
**/
VOID
GetIccOverclockingVersion (
  VOID
  )
{
  EFI_STATUS                Status;
  ICC_LIB_VERSION           Version = {0};
  PLATFORM_FVI_SETUP        PlatformFviSetup = {0};
  UINTN                     VariableSize;

  VariableSize = sizeof (PLATFORM_FVI_SETUP);
  Status = gRT->GetVariable (
                  PLATFORM_FVI_SETUP_NAME,
                  &gPlatformFviSetupGuid,
                  NULL,
                  &VariableSize,
                  &PlatformFviSetup
                  );
  if ((!EFI_ERROR(Status)) && (PlatformFviSetup.IccMajorVersion != 0)) {
    Version.Major = PlatformFviSetup.IccMajorVersion;
    Version.Minor = PlatformFviSetup.IccMinorVersion;
    Version.Hotfix= PlatformFviSetup.IccHotfixVersion;
    Version.Build = PlatformFviSetup.IccBuildVersion;
  } else {
    DEBUG ((DEBUG_INFO, "FirmwareVersionInfo: ICC librar version uninitialized.\n"));
  }

  mPlatformFviData[ICC_OVERLOCKING_VER].Version.MajorVersion = (UINT8) Version.Major;
  mPlatformFviData[ICC_OVERLOCKING_VER].Version.MinorVersion = (UINT8) Version.Minor;
  mPlatformFviData[ICC_OVERLOCKING_VER].Version.Revision     = (UINT8) Version.Hotfix;
  mPlatformFviData[ICC_OVERLOCKING_VER].Version.BuildNum     = Version.Build;
}


/**
  Get UNDI version.

  @param[in] Event    The Event this notify function registered to.
  @param[in] Context  Pointer to the context data registered to the Event.
**/
VOID
EFIAPI
GetUndiVersion (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS                  Status;
  UINTN                       Index;
  UINTN                       DriverImageHandleCount;
  EFI_HANDLE                  *DriverImageHandleBuffer;
  EFI_LOADED_IMAGE_PROTOCOL   *LoadedImage;
  EFI_GUID                    *NameGuid;
  EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL    *LastDeviceNode;
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding;
  UINT32                      RetVal;
  VOID                        *ProtocolPointer;

  RetVal = (UINT32)-1;
  DriverImageHandleCount = 0;

  Status = gBS->LocateProtocol (&gEfiPxeBaseCodeProtocolGuid, NULL, (VOID **) &ProtocolPointer);
  if (EFI_SUCCESS != Status) {
    return;
  }

  //
  // Close event, so it will not be invoked again.
  //
  gBS->CloseEvent (Event);

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiLoadedImageProtocolGuid,
                  NULL,
                  &DriverImageHandleCount,
                  &DriverImageHandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);

  for (Index = 0; Index < DriverImageHandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    DriverImageHandleBuffer[Index],
                    &gEfiLoadedImageProtocolGuid,
                    (VOID *) &LoadedImage
                    );
    if (LoadedImage->FilePath == NULL) {
      continue;
    }

    TempDevicePath = LoadedImage->FilePath;
    LastDeviceNode = TempDevicePath;
    while (!IsDevicePathEnd (TempDevicePath)) {
      LastDeviceNode = TempDevicePath;
      TempDevicePath = NextDevicePathNode (TempDevicePath);
    }
    NameGuid = EfiGetNameGuidFromFwVolDevicePathNode (
                 (MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *) LastDeviceNode
                 );
    if ((NameGuid != NULL) && (CompareGuid (NameGuid, &gUndiDriverImageGuid))) {
      Status = gBS->HandleProtocol(
                      DriverImageHandleBuffer[Index],
                      &gEfiDriverBindingProtocolGuid,
                      (VOID*)&DriverBinding
                      );
      if (!EFI_ERROR(Status)) {
        RetVal = DriverBinding->Version;
        break;
      }
    }
  }

  mPlatformFviData[UNDI_VER].Version.MajorVersion = (RetVal >> 24) & 0x000000FF;
  mPlatformFviData[UNDI_VER].Version.MinorVersion = (RetVal >> 16) & 0x000000FF;
  mPlatformFviData[UNDI_VER].Version.Revision     = (RetVal >>  8) & 0x000000FF;
  mPlatformFviData[UNDI_VER].Version.BuildNum     = RetVal & 0x000000FF;
}


/**
  Get GOP Version - To get the GOP version depends on the
  GOP_COMPONENT_NAME2_PROTOCOL_GUID and transfer the Revision the CHAR16 to UINT.

  @param[in] Event    The Event this notify function registered to.
  @param[in] Context  Pointer to the context data registered to the Event.
**/
VOID
EFIAPI
GetGopVersion (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS                    Status;
  UINT32                        Version[3] = {0};
  UINT32                        Index = 0;
  UINT32                        VersionIndex = 0;
  CHAR16                        TempStr;
  CHAR16                        *DriverVersion;
  GOP_COMPONENT_NAME2_PROTOCOL  *GopComponentName2Protocol = NULL;
  VOID                          *ProtocolPointer;

  Status = gBS->LocateProtocol (&gGopComponentName2ProtocolGuid, NULL, (VOID **) &ProtocolPointer);
  if (EFI_SUCCESS != Status) {
    return;
  }

  gBS->CloseEvent (Event);

  Status = gBS->LocateProtocol (&gGopComponentName2ProtocolGuid, NULL, (VOID **) &GopComponentName2Protocol);
  if (!EFI_ERROR (Status)) {
    Status = GopComponentName2Protocol->GetDriverVersion (
                                          GopComponentName2Protocol,
                                          "en-US",
                                          &DriverVersion
                                          );
    if (!EFI_ERROR (Status)) {
      for (Index = 0; Index <= StrSize(DriverVersion); Index++) {
        TempStr = DriverVersion[Index];
        if (TempStr == '.') {
          VersionIndex++;
        } else if ((TempStr <= '9') && (TempStr >= '0')) {
          Version[VersionIndex] *= 0x10;
          Version[VersionIndex] += ((UINT32)(TempStr) - '0');
        }
      }

      mPlatformFviData[GOP_VER].Version.MajorVersion = 0;
      mPlatformFviData[GOP_VER].Version.MinorVersion = (UINT8) Version[0];
      mPlatformFviData[GOP_VER].Version.Revision     = (UINT8) Version[1];
      mPlatformFviData[GOP_VER].Version.BuildNum     = (UINT16)Version[2];
    }
  }
}

/**
  Get RoyalPark Version
**/
VOID
GetRoyalParkVersion (
  VOID
  )
{
  mPlatformFviData[ROYALPARK_VER].Version.MajorVersion = PcdGet8 (PcdClientCommonVersionMajor);
  mPlatformFviData[ROYALPARK_VER].Version.MinorVersion = PcdGet8 (PcdClientCommonVersionMinor);
  mPlatformFviData[ROYALPARK_VER].Version.Revision     = PcdGet8 (PcdClientCommonVersionRevision);
  mPlatformFviData[ROYALPARK_VER].Version.BuildNum     = PcdGet8 (PcdClientCommonVersionBuild);

  mPlatformFviStrings[ROYALPARK_VER].VersionString     = (CHAR8 *)PcdGetPtr (PcdClientCommonVersionString);
}

/**
  Get Platform Version
**/
VOID
GetPlatformVersion (
  VOID
  )
{
  mPlatformFviData[PLATFORM_VER].Version.MajorVersion = (UINT8)  PcdGet8 (PcdPlatformVersionMajor);
  mPlatformFviData[PLATFORM_VER].Version.MinorVersion = (UINT8)  PcdGet8 (PcdPlatformVersionMinor);
  mPlatformFviData[PLATFORM_VER].Version.Revision     = (UINT8)  PcdGet8 (PcdPlatformVersionRevision);
  mPlatformFviData[PLATFORM_VER].Version.BuildNum     = (UINT16) PcdGet8 (PcdPlatformVersionBuild);
}

/**
  Get Client Silicon Version
**/
VOID
GetClientSiliconVersion (
  VOID
  )
{
  mPlatformFviData[CLIENT_SILICON_VER].Version.MajorVersion = PcdGet8 (PcdClientSiliconVersionMajor);
  mPlatformFviData[CLIENT_SILICON_VER].Version.MinorVersion = PcdGet8 (PcdClientSiliconVersionMinor);
  mPlatformFviData[CLIENT_SILICON_VER].Version.Revision     = PcdGet8 (PcdClientSiliconVersionRevision);
  mPlatformFviData[CLIENT_SILICON_VER].Version.BuildNum     = PcdGet8 (PcdClientSiliconVersionBuild);
}

/**
  Create SMBIOS Table type

  @param[in] Event    The Event this notify function registered to.
  @param[in] Context  Pointer to the context data registered to the Event.
**/
VOID
EFIAPI
InitializeFviDataCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS Status;
  VOID       *ProtocolPointer;

  Status = gBS->LocateProtocol (&gBdsAllDriversConnectedProtocolGuid, NULL, (VOID **) &ProtocolPointer);
  if (EFI_SUCCESS != Status) {
    return;
  }

  gBS->CloseEvent (Event);

  //
  // Initialize and report Platform FVI information to Smbios
  //
  mPlatformFviHeader.SmbiosHeader.Type = PcdGet8(PcdSmbiosOemTypeFirmwareVersionInfo);

  GetEcVersion();
  if (IsGbePresent ()) {
    GetLanPhyVersion ();
  }
  UpdateDebugInformation ();
  GetIccOverclockingVersion ();

  GetRoyalParkVersion ();
  GetPlatformVersion ();
  GetClientSiliconVersion ();

  Status = AddFviEntry (mPlatformFviHeader, mPlatformFviData, mPlatformFviStrings);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "AddFviEntry failed. Status = %r\n", Status));
  }
  return;
}


/**
  This is driver entry point to register the notification event.

  @param[in] ImageHandle  A handle for the image that is initializing this driver
  @param[in] SystemTable  A pointer to the EFI system table

  @retval    EFI_SUCCESS  The initialization finished successfully.
**/
EFI_STATUS
EFIAPI
DxeFirmwareVersionInfoLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  VOID               *Registration1;
  VOID               *Registration2;
  VOID               *Registration3;

  //
  // Register InitializeFviDataCallback
  //
  EfiCreateProtocolNotifyEvent (
          &gBdsAllDriversConnectedProtocolGuid,
          TPL_CALLBACK,
          InitializeFviDataCallback,
          NULL,
          &Registration1
          );

  //
  // Get the UNDI driver version.
  //
  EfiCreateProtocolNotifyEvent (
          &gEfiPxeBaseCodeProtocolGuid,
          TPL_CALLBACK,
          GetUndiVersion,
          NULL,
          &Registration2
          );

  //
  // Get the GOP driver version.
  //
  EfiCreateProtocolNotifyEvent (
          &gGopComponentName2ProtocolGuid,
          TPL_CALLBACK,
          GetGopVersion,
          NULL,
          &Registration3
          );

  return EFI_SUCCESS;
}
