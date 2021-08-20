/**@file
  PCH Setup Routines.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2020 Intel Corporation.

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

#include <Protocol/DevicePath.h>
#include <Protocol/DiskInfo.h>
#include <Protocol/IdeControllerInit.h>
#include <SetupPrivate.h>
#include "PlatformBoardId.h"
#include <Library/SiFviLib.h>
#include "PchSetup.h"
#include "OemSetup.h"
#include <Library/GbeLib.h>
#include <Library/TsnLib.h>
#include <Library/PchInfoLib.h>
#include <Library/SataLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/SpiAccessLib.h>
#include <Protocol/Spi.h>
#include <Protocol/Smbios.h>
#include <Library/CpuPlatformLib.h>
#include <PchPcieStorageDetectHob.h>
#include <PchInfoHob.h>
#include <ChipsetInfoHob.h>
#include <PcieRegs.h>
#include <Register/PchRegs.h>
#include <Register/PchPcieRpRegs.h>
#include <PchPcieRpInfo.h>
#include <Register/FlashRegs.h>
#include <Register/PchRegsFia15.h>
#include <PseOob.h>

//
// Print primitives
//
#define LEFT_JUSTIFY  0x01
#define PREFIX_SIGN   0x02
#define PREFIX_BLANK  0x04
#define COMMA_TYPE    0x08
#define LONG_TYPE     0x10
#define PREFIX_ZERO   0x20

#define DXE_DEVICE_DISABLED                     0
#define DXE_DEVICE_ENABLED                      1

//
// Length of temp string buffer to store value string.
//
#define CHARACTER_NUMBER_FOR_VALUE              30
#define _48_BIT_ADDRESS_FEATURE_SET_SUPPORTED   0x0400
#define ATAPI_DEVICE                            0x8000

typedef enum {
  EfiCompatibility,
  EfiEnhancedMode
} EFI_SATA_MODE;

GLOBAL_REMOVE_IF_UNREFERENCED EFI_STRING_ID gSATA[6] = {
  STRING_TOKEN(STR_SATA0_NAME),
  STRING_TOKEN(STR_SATA1_NAME),
  STRING_TOKEN(STR_SATA2_NAME),
  STRING_TOKEN(STR_SATA3_NAME),
  STRING_TOKEN(STR_SATA4_NAME),
  STRING_TOKEN(STR_SATA5_NAME)
};
GLOBAL_REMOVE_IF_UNREFERENCED EFI_STRING_ID gSOFTPRES[6] = {
  STRING_TOKEN(STR_SATA0_SOFT_PRESERVE_STATUS),
  STRING_TOKEN(STR_SATA1_SOFT_PRESERVE_STATUS),
  STRING_TOKEN(STR_SATA2_SOFT_PRESERVE_STATUS),
  STRING_TOKEN(STR_SATA3_SOFT_PRESERVE_STATUS),
  STRING_TOKEN(STR_SATA4_SOFT_PRESERVE_STATUS),
  STRING_TOKEN(STR_SATA5_SOFT_PRESERVE_STATUS)
};

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN SataControllerConnected = FALSE;

VOID SwapEntries (
  IN CHAR8    *Data,
  IN UINT16   Size
  )
{
  UINT16  Index;
  CHAR8   Temp8;

  for (Index = 0; (Index+1) < Size; Index+=2) {
    Temp8           = Data[Index];
    Data[Index]     = Data[Index + 1];
    Data[Index + 1] = Temp8;
  }
}

VOID
SataDeviceCallBack (
  IN EFI_HII_HANDLE HiiHandle,
  IN UINT16         Class
  )
{
  EFI_STATUS                      Status;
  PCI_DEVICE_PATH                 *PciDevicePath;
  CHAR8                           *NewString;
  CHAR8                           *SoftPres;
  UINT8                           Index;
  UINTN                           HandleCount;
  EFI_HANDLE                      *HandleBuffer;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePathNode;
  EFI_DISK_INFO_PROTOCOL          *DiskInfo;
  UINT32                          SataPortIndex, IdeChannel;
  EFI_ATA_IDENTIFY_DATA           *IdentifyDriveInfo = NULL;
  UINT32                          BufferSize = 0;
  EFI_STRING_ID                   Token;
  EFI_STRING_ID                   SoftPresStatus;
  CHAR8                           ModelNumber[42];
  UINT64                          NumSectors = 0;
  UINT64                          DriveSizeInBytes = 0;
  UINT64                          RemainderInBytes = 0;
  UINT32                          DriveSizeInGB = 0;
  UINT32                          NumTenthsOfGB = 0;
  EFI_PCI_IO_PROTOCOL             *PciIo;
  UINTN                           Segment;
  UINTN                           Bus;
  UINTN                           Device;
  UINTN                           Function;

  //
  // If SATA controller has been connected, just return
  //
  if (SataControllerConnected) {
    return;
  }

  DEBUG ((DEBUG_INFO, "Update SATA device info\n"));

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status)) {
    HandleCount = 0;
  }

  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiPciIoProtocolGuid,
                    (VOID *) &PciIo
                    );
    ASSERT_EFI_ERROR(Status);

    PciIo->GetLocation (PciIo, &Segment, &Bus, &Device, &Function);
    if ((Bus == DEFAULT_PCI_BUS_NUMBER_PCH) &&
        (Device == SataDevNumber (0)) &&
        (Function == SataFuncNumber (0))) {
      gBS->ConnectController (HandleBuffer[Index], NULL, NULL, TRUE);
    }
  }

  if (HandleBuffer) {
    FreePool (HandleBuffer);
  }

  //
  // Indicate SATA controller has been connected
  //
  SataControllerConnected = TRUE;

  //
  // Assume no line strings is longer than 256 bytes.
  //
  NewString = AllocatePool (0x100);
  ASSERT (NewString != NULL);
  if (NewString == NULL) {
    return;
  }

  SoftPres  = AllocatePool (0x40);
  ASSERT (SoftPres != NULL);
  if (SoftPres == NULL) {
    FreePool (NewString);
    return;
  }

  PciDevicePath = NULL;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiDiskInfoProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR(Status)) HandleCount = 0;

  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiDevicePathProtocolGuid,
                    (VOID *) &DevicePath
                    );
    ASSERT_EFI_ERROR(Status);

    DevicePathNode = DevicePath;
    while (!IsDevicePathEndType (DevicePathNode)) {
      if ((DevicePathNode->Type == HARDWARE_DEVICE_PATH) &&
          (DevicePathNode->SubType == HW_PCI_DP))
      {
        PciDevicePath = (PCI_DEVICE_PATH *) DevicePathNode;
        break;
      }

      DevicePathNode = NextDevicePathNode (DevicePathNode);
    }

    if (PciDevicePath == NULL) continue;

    if ((PciDevicePath->Device == SataDevNumber (0)) &&
        (PciDevicePath->Function == SataFuncNumber (0))) {
      Status = gBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gEfiDiskInfoProtocolGuid,
                      (VOID **) &DiskInfo
                      );
      ASSERT_EFI_ERROR (Status);

      Status = DiskInfo->WhichIde (
                           DiskInfo,
                           &IdeChannel,
                           &SataPortIndex
                           );
      Token = gSATA[IdeChannel];
      SoftPresStatus = gSOFTPRES[IdeChannel];

      IdentifyDriveInfo = AllocatePool(sizeof (EFI_ATAPI_IDENTIFY_DATA));
      ASSERT (IdentifyDriveInfo != NULL);
      if (IdentifyDriveInfo == NULL) {
        return;
      }
      ZeroMem(IdentifyDriveInfo, sizeof (EFI_ATAPI_IDENTIFY_DATA));

      BufferSize = sizeof (EFI_ATAPI_IDENTIFY_DATA);
      Status = DiskInfo->Identify (
                           DiskInfo,
                           IdentifyDriveInfo,
                           &BufferSize
                           );
      ASSERT_EFI_ERROR (Status);

    } else {
      continue;
    }

    ZeroMem(ModelNumber, 42);
    CopyMem (ModelNumber, IdentifyDriveInfo->ModelName, 40);
    SwapEntries (ModelNumber, 40);
    ModelNumber[14] = '\0';           // Truncate it at 14 characters

    //
    // For HardDisk append the size. Otherwise display atapi
    //
    if (!(IdentifyDriveInfo->config & ATAPI_DEVICE)) {
      if (IdentifyDriveInfo->command_set_supported_83 & _48_BIT_ADDRESS_FEATURE_SET_SUPPORTED) {
        NumSectors = *(UINT64 *) &IdentifyDriveInfo->maximum_lba_for_48bit_addressing;
      } else {
        NumSectors = (UINT64) *(UINT32 *) &IdentifyDriveInfo->user_addressable_sectors_lo;
      }
      DriveSizeInBytes = MultU64x32 (NumSectors, 512);

      //DriveSizeInGB is DriveSizeInBytes / 1 GB (1 Decimal GB = 10^9 bytes)
      DriveSizeInGB = (UINT32) DivU64x64Remainder (DriveSizeInBytes, 1000000000, &RemainderInBytes);
      //Convert the Remainder, which is in bytes, to number of tenths of a Decimal GB.
      NumTenthsOfGB = (UINT32) DivU64x64Remainder (RemainderInBytes, 100000000, NULL);

      AsciiSPrint(NewString, 0x100, "%a (%d.%dGB)", ModelNumber, DriveSizeInGB, NumTenthsOfGB);

      if ((IdentifyDriveInfo->serial_ata_capabilities != 0xFFFF) && (IdentifyDriveInfo->serial_ata_features_supported & 0x0040))
        AsciiSPrint(SoftPres, 0x40, "SUPPORTED");
      else
        AsciiSPrint(SoftPres, 0x40, "NOT SUPPORTED");
    } else {
      AsciiSPrint(NewString, 0x100, "%a ATAPI", ModelNumber);
      AsciiSPrint(SoftPres, 0x40, "  N/A  ");
    }

    InitString(
      HiiHandle,
      Token,
      L"%a",
      NewString
      );

    InitString(
      HiiHandle,
      SoftPresStatus,
      L"%a",
      SoftPres
      );

    if (IdentifyDriveInfo) {
      FreePool (IdentifyDriveInfo);
      IdentifyDriveInfo = NULL;
    }
  }

  if (HandleBuffer)
    FreePool (HandleBuffer);

  FreePool (NewString);
  FreePool (SoftPres);
}

VOID
DisplaySpiInformation (
  EFI_HII_HANDLE HiiHandle
  )
{
  UINT32      Flcomp;
  UINT32      FlashComponents;
  UINT32      Signature;
  UINT32      Data32;
  EFI_STATUS  Status;
  UINTN       VariableSize;
  SETUP_DATA  SetupData;
  UINT32      SetupAttr;

  SetupAttr = 0;
  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  &SetupAttr,
                  &VariableSize,
                  &SetupData
                  );
  if (EFI_ERROR (Status)) {
    SetupAttr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
  }
  ASSERT_EFI_ERROR (Status);

  // Read Descriptor offset 0x10 - To get Descriptor Signature
  Signature = SpiGetDescriptorSignature ();
  DEBUG ((DEBUG_INFO, "\nSignature = 0x%.8x\n", Signature));

  // Read Descriptor offset 0x30 - To get supported features and R/W frequencies
  Flcomp = SpiGetFlashComponentDescription ();
  DEBUG ((DEBUG_INFO, "Flcomp = 0x%.8x\n", Flcomp));

  // Read Descriptor offset 0x14 - To get number of components
  FlashComponents = SpiGetFlashComponentsNumber ();
  DEBUG ((DEBUG_INFO, "FlashComponents = 0x%.8x\n\n", FlashComponents));

  //
  // Dual Output Fast Read support
  //
  if (Flcomp & B_FLASH_FLCOMP_FR_SUP) {
    InitString (HiiHandle, STRING_TOKEN (STR_SPI_DUAL_OUTPUT_FAST_READ_SUPPORT_VALUE), L"%a", "Supported");
  } else {
    InitString (HiiHandle, STRING_TOKEN (STR_SPI_DUAL_OUTPUT_FAST_READ_SUPPORT_VALUE), L"%a", "Not supported");
  }

  //
  // Read ID and Read Status Clock Frequency [27:29]
  //
  Data32 = ((Flcomp & B_FLASH_FLCOMP_RIDS_FREQ) >> N_FLASH_FLCOMP_RIDS_FREQ);

  switch (Data32) {
    case V_FLASH_FLCOMP_FREQ_48MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_READ_ID_STATUS_CLOCK_FREQUENCY_VALUE), L"%a", "48 MHz");
      break;
    case V_FLASH_FLCOMP_FREQ_30MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_READ_ID_STATUS_CLOCK_FREQUENCY_VALUE), L"%a", "30 MHz");
      break;
    case V_FLASH_FLCOMP_FREQ_17MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_READ_ID_STATUS_CLOCK_FREQUENCY_VALUE), L"%a", "17 MHz");
      break;
    default:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_READ_ID_STATUS_CLOCK_FREQUENCY_VALUE), L"%a", "Invalid Setting");
      break;
  }

  //
  // Write and Erase Clock Frequency [24:26]
  //
  Data32 = ((Flcomp & B_FLASH_FLCOMP_WE_FREQ) >> N_FLASH_FLCOMP_WE_FREQ);

  switch (Data32) {
    case V_FLASH_FLCOMP_FREQ_48MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_WRITE_ERASE_CLOCK_FREQUENCY_VALUE), L"%a", "48 MHz");
      break;
    case V_FLASH_FLCOMP_FREQ_30MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_WRITE_ERASE_CLOCK_FREQUENCY_VALUE), L"%a", "30 MHz");
      break;
    case V_FLASH_FLCOMP_FREQ_17MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_WRITE_ERASE_CLOCK_FREQUENCY_VALUE), L"%a", "17 MHz");
      break;
    default:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_WRITE_ERASE_CLOCK_FREQUENCY_VALUE), L"%a", "Invalid Setting");
      break;
  }

  //
  // Fast Read Clock Frequency [21:23]
  //
  Data32 = ((Flcomp & B_FLASH_FLCOMP_FRCF_FREQ) >> N_FLASH_FLCOMP_FRCF_FREQ);

  switch (Data32) {
    case V_FLASH_FLCOMP_FREQ_48MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_FAST_READ_CLOCK_FREQUENCY_VALUE), L"%a", "48 MHz");
      break;
    case V_FLASH_FLCOMP_FREQ_30MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_FAST_READ_CLOCK_FREQUENCY_VALUE), L"%a", "30 MHz");
      break;
    case V_FLASH_FLCOMP_FREQ_17MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_FAST_READ_CLOCK_FREQUENCY_VALUE), L"%a", "17 MHz");
      break;
    default:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_FAST_READ_CLOCK_FREQUENCY_VALUE), L"%a", "Invalid Setting");
      break;
  }

  //
  // Fast Read support [20]
  //
  if (Flcomp & B_FLASH_FLCOMP_FR_SUP) {
    InitString (HiiHandle, STRING_TOKEN (STR_SPI_FAST_READ_SUPPORT_VALUE), L"%a", "Supported");
  } else {
    InitString (HiiHandle, STRING_TOKEN (STR_SPI_FAST_READ_SUPPORT_VALUE), L"%a", "Not supported");
  }

  //
  // Read Clock Frequency [17:19]
  //
  Data32 = ((Flcomp & B_FLASH_FLCOMP_RC_FREQ) >> N_FLASH_FLCOMP_RC_FREQ);

  switch (Data32) {
    case V_FLASH_FLCOMP_FREQ_48MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_READ_CLOCK_FREQUENCY_VALUE), L"%a", "48 MHz");
      break;
    case V_FLASH_FLCOMP_FREQ_30MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_READ_CLOCK_FREQUENCY_VALUE), L"%a", "30 MHz");
      break;
    case V_FLASH_FLCOMP_FREQ_17MHZ:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_READ_CLOCK_FREQUENCY_VALUE), L"%a", "17 MHz");
      break;
    default:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_READ_CLOCK_FREQUENCY_VALUE), L"%a", "Invalid Setting");
      break;
  }

  //
  // Number of components
  //
  FlashComponents = ((FlashComponents >> N_FLASH_COMPONENTS) & B_FLASH_COMPONENTS);
  switch (FlashComponents) {
    case 0:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_NUMBER_OF_COMPONENTS_VALUE), L"%a", "1 Component");
      SetupData.TwoComponents = 0;
      break;
    case 1:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_NUMBER_OF_COMPONENTS_VALUE), L"%a", "2 Components");
      SetupData.TwoComponents = 1;
      break;
    default:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI_NUMBER_OF_COMPONENTS_VALUE), L"%a", "Reserved");
      break;
  }
  Status = gRT->SetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  SetupAttr,
                  sizeof (SETUP_DATA),
                  &SetupData
                  );
  ASSERT_EFI_ERROR (Status);
  //
  // Display SPI Component 1 Density
  //

  // Execute if there are 2 components
  if (FlashComponents == 1){
    switch (Flcomp & 0xF0) {
      case 0:
        InitString (HiiHandle, STRING_TOKEN (STR_SPI1_DENSITY_VALUE), L"%a", "512 KB");
        break;
      case 1:
        InitString (HiiHandle, STRING_TOKEN (STR_SPI1_DENSITY_VALUE), L"%a", "1 MB");
        break;
      case 2:
        InitString (HiiHandle, STRING_TOKEN (STR_SPI1_DENSITY_VALUE), L"%a", "2 MB");
        break;
      case 3:
        InitString (HiiHandle, STRING_TOKEN (STR_SPI1_DENSITY_VALUE), L"%a", "4 MB");
        break;
      case 4:
        InitString (HiiHandle, STRING_TOKEN (STR_SPI1_DENSITY_VALUE), L"%a", "8 MB");
        break;
      case 5:
        InitString (HiiHandle, STRING_TOKEN (STR_SPI1_DENSITY_VALUE), L"%a", "16 MB");
        break;
      case 6:
        InitString (HiiHandle, STRING_TOKEN (STR_SPI1_DENSITY_VALUE), L"%a", "32 MB");
        break;
      case 7:
        InitString (HiiHandle, STRING_TOKEN (STR_SPI1_DENSITY_VALUE), L"%a", "64 MB");
        break;
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
        InitString (HiiHandle, STRING_TOKEN (STR_SPI1_DENSITY_VALUE), L"%a", "Reserved");
        break;
      default:
        InitString (HiiHandle, STRING_TOKEN (STR_SPI1_DENSITY_VALUE), L"%a", "Not present");
        break;
    }
  }
  //
  // Display SPI Component 0 Density
  //
  switch (Flcomp & 0x0F) {
    case 0:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI0_DENSITY_VALUE), L"%a", "512 KB");
      break;
    case 1:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI0_DENSITY_VALUE), L"%a", "1 MB");
      break;
    case 2:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI0_DENSITY_VALUE), L"%a", "2 MB");
      break;
    case 3:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI0_DENSITY_VALUE), L"%a", "4 MB");
      break;
    case 4:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI0_DENSITY_VALUE), L"%a", "8 MB");
      break;
    case 5:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI0_DENSITY_VALUE), L"%a", "16 MB");
      break;
    case 6:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI0_DENSITY_VALUE), L"%a", "32 MB");
      break;
    case 7:
      InitString (HiiHandle, STRING_TOKEN (STR_SPI0_DENSITY_VALUE), L"%a", "64 MB");
      break;
    default:
      break;
  }
}


VOID
DisplayOobInformation (
  EFI_HII_HANDLE HiiHandle
  )
{
  VOID               *Hob;
  OOB_DATA           *OobRegion;
  PCH_SETUP          PchSetup;
  UINTN              VariableSize;
  EFI_STATUS         Status = EFI_SUCCESS;

  Hob   = NULL;
  OobRegion = NULL;

  Hob = GetFirstGuidHob (&gOobConfigSectionGuid);
  if (Hob != NULL) {
    OobRegion = (OOB_DATA *) GET_GUID_HOB_DATA (Hob);
    DEBUG ((EFI_D_INFO, "Get OOB Data from HOB successfully\n"));
  } else {
    DEBUG ((EFI_D_INFO, "Unable to obtain OOB data from HOB\n"));
    return;
  }
  DEBUG ((DEBUG_INFO, "\n\nCloudHostUrlSize: %x\n", OobRegion->CloudHostUrlSize));
  DEBUG ((DEBUG_INFO, "CloudHostUrl: \n"));
  for (UINT32 Count = 0; Count < 25; Count++) {
    DEBUG ((DEBUG_INFO, "%c", OobRegion->CloudHostUrl[Count]));
  }
  DEBUG ((DEBUG_INFO, "\nCloudPort: %x\n", OobRegion->CloudHostPort));

  VariableSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (
                L"PchSetup",
                &gPchSetupVariableGuid,
                NULL,
                &VariableSize,
                &PchSetup
                );

  /* Update OOB display information after prov state enable */
  /* otherwise keep the default value */
  if(OobRegion->ProvState == OOB_ENABLED) {
    //
    // Display Oob information
    //
    InitString (HiiHandle,
                STRING_TOKEN (STR_PSE_OOB_ENABLED_VALUE),
                L"%a",
                (OobRegion->ProvState?"ENABLED":"DISABLED"));
    InitString (HiiHandle,
                STRING_TOKEN (STR_PSE_OOB_FIRSTBOOT_VALUE),
                L"%a",
                PchSetup.PchPseOobIsFirstBootProvDone?"Done":"Not Done");
    InitString (HiiHandle,
                STRING_TOKEN (STR_PSE_OOB_DEVICEID_VALUE),
                L"%d",
                OobRegion->DeviceId);
    InitString (HiiHandle,
                STRING_TOKEN (STR_PSE_OOB_CLOUDTYPE_VALUE),
                L"%a",
                OobRegion->CloudType);
    InitString (HiiHandle,
                STRING_TOKEN (STR_PSE_OOB_CLOUDURL_VALUE),
                L"%a",
              OobRegion->CloudHostUrl);
    InitString (HiiHandle,
                STRING_TOKEN (STR_PSE_OOB_CLOUDPORT_VALUE),
                L"%d",
                OobRegion->CloudHostPort);
  }
}

VOID
BiosIshDataPass (
  VOID
  )
{
  static CONST CHAR8      FileName[] = "bios2ish";

  DEBUG ((DEBUG_INFO, "Sending PDT Unlock Message\n"));
  HeciPdtUnlockMsg (FileName);

}

STATIC
BOOLEAN
SetSetupVolatileDataForRstMenu (
  OUT SETUP_VOLATILE_DATA  *SetupVolatileData,
  IN OUT PCH_SETUP  *PchSetup
  )
{

  BOOLEAN                 UpdatePchSetup;
  VOID                    *Hob;
  PCIE_STORAGE_INFO_HOB   *PcieStorageInfoHob;
  UINT32                  Index;

  UpdatePchSetup = FALSE;
  Hob = NULL;
  PcieStorageInfoHob = NULL;
  Hob = GetFirstGuidHob (&gPchPcieStorageDetectHobGuid);
  if (Hob == NULL) {
    return UpdatePchSetup;
  }

  PcieStorageInfoHob = (PCIE_STORAGE_INFO_HOB *) GET_GUID_HOB_DATA (Hob);

  for (Index = 0; Index < PCH_MAX_PCIE_CONTROLLERS; Index++) {
    SetupVolatileData->CycleRouterMap[Index] = PcieStorageInfoHob->RstCycleRouterMap[Index];
    DEBUG ((DEBUG_INFO, "CycleRouterMap[%d] = %d\n", Index, SetupVolatileData->CycleRouterMap[Index]));
  }

  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
    SetupVolatileData->PcieStorageMap[Index] = PcieStorageInfoHob->PcieStorageLinkWidth[Index];
    SetupVolatileData->PcieStorageProgrammingInterface[Index] = PcieStorageInfoHob->PcieStorageProgrammingInterface[Index];
    if (PcieStorageInfoHob->PcieStorageLinkWidth[Index] == 0) {
      //
      //  Clear PCH_SETUP.RstPcieRemapEnabled for disconnected drives
      //
      PchSetup->RstPcieRemapEnabled[Index] = 0;
      UpdatePchSetup = TRUE;
    }
  }



  return UpdatePchSetup;
}

STATIC
BOOLEAN
InitializeSataInterfaceMode (
  IN OUT  PCH_SETUP  *PchSetup
  )
{
  UINT64   PciSataRegBase;
  UINT8    SataMode;
  UINT8    SataInterfaceMode;
  BOOLEAN  UpdatePchSetup;

  UpdatePchSetup = FALSE;

  PciSataRegBase = SataRegBase (SATA_1_CONTROLLER_INDEX);
  SataMode       = PciSegmentRead8 (PciSataRegBase + R_PCI_SCC_OFFSET);

  switch (SataMode) {
    case PCI_CLASS_MASS_STORAGE_RAID:
      SataInterfaceMode = SATA_MODE_RAID;
      break;
    case PCI_CLASS_MASS_STORAGE_SATADPA:
    default:
      SataInterfaceMode = SATA_MODE_AHCI;
      break;
  }

  if (PchSetup->SataInterfaceMode != SataInterfaceMode) {
    DEBUG ((DEBUG_INFO, "Mismatch detected between current SATA controller mode and user settings, changing PchSetup to reflect actual settings\n"));
    PchSetup->SataInterfaceMode = SataInterfaceMode;
    UpdatePchSetup = TRUE;
  }

  return UpdatePchSetup;

}

STATIC
VOID
InitializeRstModeStrings (
  IN  EFI_HII_HANDLE  HiiHandle,
  IN  RST_MODE  RstMode
  )
{

  if (RstMode != RstUnsupported) {
    if (RstMode == RstPremium) {
      InitString (HiiHandle, STRING_TOKEN (STR_SATA_RAID), L"Intel RST Premium With Intel Optane System Acceleration");
    } else {
      InitString (HiiHandle, STRING_TOKEN (STR_SATA_RAID), L"Intel RST With Intel Optane System Acceleration");
    }
  } else {
    InitString(
      HiiHandle,
      STRING_TOKEN(STR_SATA_MODE_SELECTION_HELP),
      L"Determines how SATA controller(s) operate. \nThis PCH SKU dosen't support RST feature"
      );
  }

}

STATIC
BOOLEAN
SataUpdateMechanicalSwPolicy (
  OUT SETUP_VOLATILE_DATA*  SetupVolatileData,
  OUT PCH_SETUP*            PchSetup
  )
{
  BOOLEAN  UpdatePchSetup;
  UINT32   Index;

  UpdatePchSetup = FALSE;
  for (Index = 0; Index < MaxSataPortNum (SATA_1_CONTROLLER_INDEX); Index++) {
    ///
    /// Check the SATA GP pin is set to required native mode
    ///
    if (!GpioIsSataGpEnabled (SATA_1_CONTROLLER_INDEX, Index)) {
      if (PchSetup->SataMechanicalSw[Index] == 1) {

        DEBUG ((DEBUG_ERROR,
                "BIOS must set the SATA%0xGP GPIO pin to native function if Inter Lock Switch is enabled!\n",
                Index));

        PchSetup->SataMechanicalSw[Index] = 0;
        UpdatePchSetup = TRUE;
      }
      SetupVolatileData->SataMpsPresent[Index]  = 0;
    } else {
      SetupVolatileData->SataMpsPresent[Index]  = 1;
    }
  }

  return UpdatePchSetup;
}

STATIC
BOOLEAN
PchSetupSataAndRst (
  IN  EFI_HII_HANDLE  HiiHandle,
  OUT SETUP_VOLATILE_DATA  *SetupVolatileData,
  OUT PCH_SETUP            *PchSetup
  )
{
  BOOLEAN  UpdatePchSetup;
  RST_MODE  RstMode;

  UpdatePchSetup = FALSE;
  if (PciSegmentRead16 (SataRegBase (SATA_1_CONTROLLER_INDEX)) == 0xFFFF) {
    return UpdatePchSetup;
  }

  RstMode = PchGetSupportedRstMode ();
  if (RstMode != RstUnsupported) {
    SetupVolatileData->RstAvailable   = TRUE;
  }
  SetupVolatileData->RsteAvailable = IsPchServerSku ();
  InitializeRstModeStrings (HiiHandle, RstMode);

  UpdatePchSetup |= SataUpdateMechanicalSwPolicy (SetupVolatileData, PchSetup);
  UpdatePchSetup |= InitializeSataInterfaceMode (PchSetup);
  UpdatePchSetup |= SetSetupVolatileDataForRstMenu (SetupVolatileData, PchSetup);

  SataDeviceCallBack (HiiHandle, 0);

  return UpdatePchSetup;
}

BOOLEAN
IsPciePortShadowed (
  UINT32       Index,
  PCH_INFO_HOB *PchInfoHob
  )
{
  UINT32 Controller;
  UINT32 Port;

  Controller = GetControllerIndex (Index);
  Port = GetControllerRpIndex (Index);

  if ((Port == 1) && (PchInfoHob->PcieControllerCfg[Controller] != V_PCH_PCIE_CFG_STRPFUSECFG_RPC_1_1_1_1)) {
    return TRUE;
  } else if ((Port == 2) && (PchInfoHob->PcieControllerCfg[Controller] == V_PCH_PCIE_CFG_STRPFUSECFG_RPC_4)) {
    return TRUE;
  } else if ((Port == 3) && ((PchInfoHob->PcieControllerCfg[Controller] == V_PCH_PCIE_CFG_STRPFUSECFG_RPC_4) ||
                             (PchInfoHob->PcieControllerCfg[Controller] == V_PCH_PCIE_CFG_STRPFUSECFG_RPC_2_2))) {
    return TRUE;
  }
  return FALSE;
}

STATIC
VOID
PchSetupHdAudio (
  OUT SETUP_VOLATILE_DATA*  SetupVolatileData
  )
{
  UINT32 Index;

  SetupVolatileData->AudioHdaLinkSupported = IsAudioInterfaceSupported (HdaLink, 0);

  for (Index = 0; Index < GetPchHdaMaxDmicLinkNum (); Index++) {
    SetupVolatileData->AudioDmicLinkSupported[Index] = IsAudioInterfaceSupported (HdaDmic, Index);
  }

  for (Index = 0; Index < GetPchHdaMaxSspLinkNum (); Index++) {
    SetupVolatileData->AudioSspLinkSupported[Index] = IsAudioInterfaceSupported (HdaSsp, Index);
  }

  for (Index = 0; Index < GetPchHdaMaxSndwLinkNum (); Index++) {
    SetupVolatileData->AudioSndwLinkSupported[Index] = IsAudioInterfaceSupported (HdaSndw, Index);
  }
}

STATIC
VOID
PchSetupCrid (
  OUT SETUP_VOLATILE_DATA*  SetupVolatileData
  )
{
  VOID          *HobPtr;
  PCH_INFO_HOB  *PchInfoHob;

  HobPtr = GetFirstGuidHob (&gPchInfoHobGuid);
  if (HobPtr == NULL) {
    ASSERT (FALSE);
    return;
  }
  PchInfoHob = (PCH_INFO_HOB*) GET_GUID_HOB_DATA (HobPtr);
  if (PchInfoHob == NULL) {
    ASSERT (FALSE);
    return;
  }
  SetupVolatileData->PchCridSupport = (UINT8) PchInfoHob->CridSupport;
}

STATIC
VOID
PchSetupFia (
  OUT SETUP_VOLATILE_DATA  *SetupVolatileData
  )
{
  UINT8 Index;

  for (Index = 0; Index < ARRAY_SIZE (SetupVolatileData->FiaConnectorOrmSupported); Index ++) {
    SetupVolatileData->FiaConnectorOrmSupported[Index] = PCH_FIA_ORM_NOT_SUPPORTED;
  }

  for (Index = 0; Index < PCH_FIA_15_MAX_ORM_CONNECTOR; Index ++) {
    SetupVolatileData->FiaConnectorOrmSupported[Index] = PCH_FIA_ORM_SUPPORTED;
  }
}

STATIC
VOID
PchSetupScs (
  OUT SETUP_VOLATILE_DATA*  SetupVolatileData
  )
{
  UINT8  UfsIndex;

  if (IsPchEmmcSupported ()) {
    SetupVolatileData->EmmcSupported = TRUE;
  }
  if (IsPchSdCardSupported ()) {
    SetupVolatileData->SdCardSupported = TRUE;
  }

  for (UfsIndex = 0; UfsIndex < PchGetMaxUfsNum (); UfsIndex++) {
    SetupVolatileData->UfsSupported[UfsIndex] = TRUE;
  }
}

STATIC
VOID
PchSetupPcie (
  IN  EFI_HII_HANDLE        HiiHandle,
  OUT SETUP_VOLATILE_DATA*  SetupVolatileData
  )
{
  UINT32        Index;
  VOID          *HobPtr;
  PCH_INFO_HOB  *PchInfoHob;

  HobPtr = GetFirstGuidHob (&gPchInfoHobGuid);
  ASSERT (HobPtr != NULL);
  if (HobPtr == NULL) {
    return;
  }
  PchInfoHob = (PCH_INFO_HOB*) GET_GUID_HOB_DATA (HobPtr);
  ASSERT (PchInfoHob != NULL);
  if (PchInfoHob == NULL) {
    return;
  }

  for (Index = 0; Index < GetPchMaxPciePortNum (); Index ++) {
    if (PchInfoHob->PciePortFuses & (BIT0 << Index)) {
      SetupVolatileData->PciePortCfg[Index] = PCH_RP_FUSED_OFF;
    } else if (Index + 1 == PchInfoHob->GbePciePortNumber) {
      SetupVolatileData->PciePortCfg[Index] = PCH_RP_ETHERNET;
    } else if ((PchInfoHob->PciePortLaneEnabled & (BIT0 << Index)) == 0) {
      SetupVolatileData->PciePortCfg[Index] = PCH_RP_DIFFERENT_BUS;
    } else if (IsPciePortShadowed (Index, PchInfoHob)) {
      SetupVolatileData->PciePortCfg[Index] = PCH_RP_MERGED;
    } else {
      SetupVolatileData->PciePortCfg[Index] = PCH_RP_AVAILABLE;
    }
  }
  for (Index = GetPchMaxPciePortNum (); Index < ARRAY_SIZE (SetupVolatileData->PciePortCfg); Index ++) {
    SetupVolatileData->PciePortCfg[Index] = PCH_RP_NOT_IMPLEMENTED;
  }
  for (Index = 0; Index < ARRAY_SIZE (SetupVolatileData->PciePortCfg); Index ++) {
    DEBUG ((DEBUG_INFO, "VolatileData.PciePortCfg[%d] = %d\n", Index, SetupVolatileData->PciePortCfg[Index]));
  }

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_PCIE_LAN_VALUE),
    (PchInfoHob->GbePciePortNumber != 0) ? L"%d" : L"Disabled",
    PchInfoHob->GbePciePortNumber
    );

}

/*
  Update SETUP_VOLATILE_DATA PCH USB related data
*/
STATIC
VOID
PchSetupUsb (
  OUT SETUP_VOLATILE_DATA  *SetupVolatileData
  )
{
  //
  // USB Ports Count update
  //
  SetupVolatileData->PchUsb2PortCount = GetPchUsb2MaxPhysicalPortNum ();
  SetupVolatileData->PchUsb3PortCount = GetPchXhciMaxUsb3PortNum ();
}

STATIC
VOID
PchSetupGbe (
  OUT SETUP_VOLATILE_DATA  *SetupVolatileData
  )
{
  SetupVolatileData->GbeSupportByPch = PchIsGbeSupported ();
  SetupVolatileData->GbeAvailable = IsGbePresent ();
}

STATIC
VOID
PchSetupTsn (
  OUT SETUP_VOLATILE_DATA  *SetupVolatileData
  )
{
  UINT8         Index;
  VOID          *HobPtr;
  PCH_INFO_HOB  *PchInfoHob;

  HobPtr = GetFirstGuidHob (&gPchInfoHobGuid);
  ASSERT (HobPtr != NULL);
  if (HobPtr == NULL) {
    return;
  }
  PchInfoHob = (PCH_INFO_HOB*) GET_GUID_HOB_DATA (HobPtr);
  ASSERT (PchInfoHob != NULL);
  if (PchInfoHob == NULL) {
    return;
  }

  for (Index = 0; Index < GetNumTsnPorts (); Index ++) {
    SetupVolatileData->TsnGbeLaneEnabled[Index] = PchInfoHob->TsnPortLaneEnabled[Index];
    SetupVolatileData->TsnGbeLaneNum[Index]     = PchInfoHob->TsnPortLaneNum[Index];
  }

  SetupVolatileData->TsnSupportByPch = PchIsTsnSupported ();
  SetupVolatileData->TsnAvailable = IsTsnPresent ();
}

STATIC
VOID
PchSetupThc (
  OUT SETUP_VOLATILE_DATA  *SetupVolatileData
  )
{
  VOID          *HobPtr;
  PCH_INFO_HOB  *PchInfoHob;

  HobPtr = GetFirstGuidHob (&gPchInfoHobGuid);
  ASSERT (HobPtr != NULL);
  if (HobPtr == NULL) {
    return;
  }
  PchInfoHob = (PCH_INFO_HOB*) GET_GUID_HOB_DATA (HobPtr);
  ASSERT (PchInfoHob != NULL);
  if (PchInfoHob == NULL) {
    return;
  }
  SetupVolatileData->ThcSupported = IsPchThcSupported ();
  SetupVolatileData->ThcAvailable = PchInfoHob->Thc0Strap;
}

STATIC
VOID
UpdateChipsetInitInfo (
  IN EFI_HII_HANDLE  HiiHandle
  )
{
  VOID               *HobPtr;
  CHAR8              BaseVersion[3];
  CHAR8              OemVersion[3];
  CHIPSET_INIT_INFO  *ChipsetInitHob;

  HobPtr = GetFirstGuidHob (&gChipsetInitHobGuid);
  if (HobPtr != NULL) {
    ChipsetInitHob = (CHIPSET_INIT_INFO*) GET_GUID_HOB_DATA (HobPtr);
  } else {
    return;
  }

  AsciiSPrint (BaseVersion, sizeof (BaseVersion), "%x", ChipsetInitHob->BaseVersion);
  AsciiSPrint (OemVersion, sizeof (OemVersion), "%x", ChipsetInitHob->OemVersion);

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_CHIP_HSIO_BASE_REV_VALUE),
    L"%a",
    BaseVersion
    );
  InitString (
    HiiHandle,
    STRING_TOKEN (STR_CHIP_HSIO_OEM_REV_VALUE),
    L"%a",
    OemVersion
    );
}

STATIC
VOID
UpdateChipsetInfo (
  IN EFI_HII_HANDLE  HiiHandle
  )
{
  CHAR8   Buffer[PCH_STEPPING_STR_LENGTH_MAX];

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_CHIP_SB_VALUE),
    L"%a",
    PchGetSeriesStr ()
    );

  PchGetSteppingStr (Buffer, sizeof (Buffer));
  InitString (
    HiiHandle,
    STRING_TOKEN(STR_CHIP_SB_REV_VALUE),
    L"%a",
    Buffer
    );

  InitString (
    HiiHandle,
    STRING_TOKEN(STR_CHIP_SB_SKU_VALUE),
    L"%a",
    PchGetSkuStr ()
    );
}

VOID
InitSBStrings (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  )
{
  EFI_STATUS           Status;
  UINTN                VariableSize;
  UINT32               PchSetupAttr;
  PCH_SETUP            PchSetup;
  SETUP_VOLATILE_DATA  VolatileData;
  UINT32               SetupVolVarAttr;
  BOOLEAN              UpdatePchSetup;

  if (Class == ADVANCED_FORM_SET_CLASS) {
    DEBUG ((DEBUG_INFO, "<InitSBStrings>"));

    UpdatePchSetup = FALSE;

    VariableSize = sizeof (SETUP_VOLATILE_DATA);
    Status = gRT->GetVariable (
                    L"SetupVolatileData",
                    &gSetupVariableGuid,
                    &SetupVolVarAttr,
                    &VariableSize,
                    &VolatileData
                    );
    ASSERT_EFI_ERROR (Status);

    VariableSize = sizeof (PCH_SETUP);
    Status = gRT->GetVariable (
                    L"PchSetup",
                    &gPchSetupVariableGuid,
                    &PchSetupAttr,
                    &VariableSize,
                    &PchSetup
                    );
    ASSERT_EFI_ERROR (Status);

    //
    // Update SetupVolatileData and PchSetup
    //
    PchSetupPcie (HiiHandle, &VolatileData);
    UpdatePchSetup |= PchSetupSataAndRst (HiiHandle, &VolatileData, &PchSetup);
    PchSetupUsb (&VolatileData);
    PchSetupGbe (&VolatileData);
    PchSetupTsn (&VolatileData);
    PchSetupScs (&VolatileData);
    PchSetupHdAudio (&VolatileData);
    PchSetupThc (&VolatileData);
    PchSetupCrid (&VolatileData);
    PchSetupFia (&VolatileData);

    //
    // Update PchSetup if needed
    //
    if (UpdatePchSetup == TRUE) {
      Status = gRT->SetVariable (
                      L"PchSetup",
                      &gPchSetupVariableGuid,
                      PchSetupAttr,
                      sizeof (PCH_SETUP),
                      &PchSetup
                      );
      ASSERT_EFI_ERROR (Status);
    }

    Status = gRT->SetVariable (
                    L"SetupVolatileData",
                    &gSetupVariableGuid,
                    SetupVolVarAttr,
                    sizeof (SETUP_VOLATILE_DATA),
                    &VolatileData
                    );
    ASSERT_EFI_ERROR (Status);

  } // ADVANCED_FORM_SET_CLASS

  if (Class == MAIN_FORM_SET_CLASS) {
    DEBUG ((DEBUG_INFO, "<InitSBStrings>"));

    UpdateChipsetInfo (HiiHandle);
    UpdateChipsetInitInfo (HiiHandle);

    InitString (
      HiiHandle,
      STRING_TOKEN (STR_CHIP_SB_PACKAGE_VALUE),
      L"%a",
      "Not Implemented Yet"
      );

    //
    // PSE OOB information
    //
    DisplayOobInformation (HiiHandle);
    //
    // SPI controller information
    //
#if FixedPcdGetBool(PcdBfxEnable) == 0
    DisplaySpiInformation (HiiHandle);
#endif
  } // MAIN_FORM_SET_CLASS
}
