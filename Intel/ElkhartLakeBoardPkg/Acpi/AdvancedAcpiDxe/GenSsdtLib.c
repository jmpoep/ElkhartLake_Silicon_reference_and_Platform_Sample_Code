/** @file
  ACPI SSDT table generation library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include "AcpiByteStream.h"
#include <Base.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/HobLib.h>
#include <Guid/HobList.h>
#include <Library/UefiBootServicesTableLib.h>
#include <IndustryStandard/Acpi.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/MemoryAllocationLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtHeader [] = {
  0x53,0x53,0x44,0x54,0x08,0x01,0x00,0x00,    /* 00000000    "SSDT...." */
  0x02,0x06,0x49,0x6E,0x74,0x65,0x6C,0x20,    /* 00000008    "..Intel " */
  0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 00000010    "        " */
  0x01,0x00,0x00,0x00,0x49,0x4E,0x54,0x4C,    /* 00000018    "....INTL" */
  0x27,0x05,0x16,0x20,                        /* 00000020    "'.. " */
  0xA0,0x0F,0x00                              /* 00000024    "..." */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtExternalDualName [] = {
  0x15,0x5C,0x2E,0x5F,0x53,0x42,0x5F,0x50,    /* 00000000    ".\._SB_P" */
  0x43,0x49,0x58,0x06,0x00                    /* 00000008    "CIX.." */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtScopePkgLengthEncoding [] = {
  0x10, 0x00, 0x00, 0x00, 0x00               /* 00000000    "....." */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtScopeDualName [] = {
  0x5C,0x2E,0x5F,0x53,0x42,                   /* 00000000    "\._SB" */
  0x5F,0x50,0x43,0x49,0x58                    /* 00000008    "_PCIX" */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtDevicePkgLengthEncoding [] = {
  0x5B,0x82,0x00,0x00,0x00,0x00               /* 00000000    "......" */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtDeviceName [] = {
  0x54,0x4D,0x50,0x31                         /* 00000000    "TMP1" */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtHardwareId [] = {
  0x08,0x5F,0x48,0x49,0x44,0x0D,0x49,0x4E,    /* 00000000    "._HID.IN" */
  0x54,0x30,0x30,0x30,0x30,0x30,0x00          /* 00000008    "T0000." */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtCompatibleId [] = {
  0x08,0x5F,0x43,0x49,0x44,0x0D,0x49,0x4E,    /* 00000000    "._CID.IN" */
  0x54,0x30,0x30,0x30,0x30,0x30,0x00          /* 00000008    "T0000." */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtUniqueId [] = {
  0x08,0x5F,0x55,0x49,0x44,0x00               /* 00000000    "._UID." */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtCurrentResourceSettings [] = {
  0x08,0x5F,0x43,0x52,0x53,                   /* 00000000    "._CRS" */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtBufferPkgLengthEncoding [] = {
  0x11,0x00,0x00
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtCrsPkgLengthEncoding [] = {
  0x00,0x00, 0x00                             /* 00000000    "....." */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtGpioResource [] = {
  0x8C,0x20,0x00,0x01,0x01,0x01,0x00,0x02,    /* 00000000    ". ......" */
  0x00,0x00,0x00,0x00,0x00,0x00,0x17,0x00,    /* 00000008    "........" */
  0x00,0x19,0x00,0x23,0x00,0x00,0x00,0x03,    /* 00000010    "...#...." */
  0x00,0x5C,0x5F,0x53,0x42,0x2E,0x47,0x50,    /* 00000018    ".\_SB.GP" */
  0x49,0x30,0x00,                             /* 00000020    "I0." */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtI2cSerialBusResource [] = {
  0x8E,0x1E,0x00,0x01,0x00,0x01,0x02,0x00,    /* 00000000    "........" */
  0x00,0x01,0x06,0x00,0x80,0x1A,0x06,0x00,    /* 00000008    "........" */
  0x22,0x00,0x5C,0x5F,0x53,0x42,0x2E,0x50,    /* 00000010    "".\_SB.P" */
  0x43,0x49,0x30,0x2E,0x49,0x32,0x43,0x58,    /* 00000018    "CI0.I2CX" */
  0x00                                        /* 00000020    "." */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtStatusMethod [] = {
  0x14,0x09,0x5F,0x53,0x54,0x41,0x00,         /* 00000000    ".._STA." */
  0xA4,0x0A,0x0F                              /* 00000008    "..." */
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SsdtResourceTemplateEndTag [] = {
  0x79, 0x00
};

EFI_STATUS
GetTableSize(
  IN  UINT8   *AcpiDataBase,
  OUT UINT32  *SsdtTableSize
  )
{
  UINTN                         GpioResources;
  UINTN                         I2cResources;
  UINT32                        ResourceBufferLength;
  UINT32                        DevicePackageLength;
  UINT32                        ScopePackageLength;
  UINT32                        ResourceSize;
  UINTN                         i;
  UINTN                         ResourceOffset;
  UINT8                         ResourceType;
  UINTN                         NextResource;
  EFI_ACPI_SDT_HEADER           *SsdtTableInfo;
  SSDT_DEVICE_DATA              *SsdtDeviceInfo;
  UINT32                        Size;
  UINT8                         *PrintData;

  //
  // Get table info from HOB
  //
  SsdtTableInfo = (EFI_ACPI_SDT_HEADER *) AcpiDataBase;
  SsdtDeviceInfo = (SSDT_DEVICE_DATA *) (AcpiDataBase + sizeof(EFI_ACPI_SDT_HEADER));
  ResourceOffset = sizeof(EFI_ACPI_SDT_HEADER) + sizeof(SSDT_DEVICE_DATA) - sizeof(UINT8);
  NextResource = 0;
  GpioResources = 0;
  I2cResources = 0;
  ResourceSize = 0;

  Size = SsdtTableInfo->Length;

  DEBUG_CODE_BEGIN();
  DEBUG((DEBUG_INFO, "GenSsdt AcpiData print:\n"));
  for (PrintData = AcpiDataBase; PrintData<(AcpiDataBase + Size); PrintData++) {
    DEBUG((DEBUG_INFO, "%x ", *PrintData));
  }
  DEBUG((DEBUG_INFO, "\n"));
  DEBUG_CODE_END();

  DEBUG((DEBUG_INFO, "NumberOfResources: %x \n", SsdtDeviceInfo->NumberOfResources));

  for (i = 0; i < SsdtDeviceInfo->NumberOfResources; i++) {
    ResourceType = *(AcpiDataBase + ResourceOffset + NextResource);
    DEBUG((DEBUG_INFO, "ResourceType: %x ", ResourceType));
    switch (ResourceType) {
      case ACPI_GPIO_RESOURCE_TYPE :
      {
        ResourceSize = ResourceSize + sizeof(GPIO_RESOURCE_DATA);
        NextResource = NextResource + sizeof(GPIO_RESOURCE_DATA) - sizeof(UINT8);
        GpioResources++;
        break;
      }
      case ACPI_I2C_RESOURCE_TYPE :
      {
        ResourceSize = ResourceSize + sizeof(I2C_RESOURCE_DATA);
        NextResource = NextResource + sizeof(I2C_RESOURCE_DATA) - sizeof(UINT8);
        I2cResources++;
        break;
      }
      default :
        DEBUG ((DEBUG_INFO, "Unsupported resource type.\n"));
        break;
    }
  }
  DEBUG((DEBUG_INFO, "GenSsdt GpioResources:%d I2cResources:%d\n", GpioResources, I2cResources));
  //
  // Calculate the size of table to be generated
  //
  ResourceBufferLength = (UINT32) ((GpioResources * sizeof(SsdtGpioResource)) +
                         (I2cResources * sizeof(SsdtI2cSerialBusResource)) +
                         sizeof(SsdtResourceTemplateEndTag));
  DEBUG((DEBUG_INFO, "GenSsdt ResourceBufferLength: 0x%x\n", ResourceBufferLength));

  DevicePackageLength = (UINT32) (sizeof(SsdtDeviceName) + sizeof(SsdtHardwareId) +
                        sizeof(SsdtCompatibleId) + sizeof(SsdtUniqueId) +
                        sizeof(SsdtCurrentResourceSettings) + ResourceBufferLength +
                        sizeof(SsdtStatusMethod));
  DEBUG((DEBUG_INFO, "GenSsdt DevicePkgLength: 0x%x\n", DevicePackageLength));

  if (ResourceBufferLength < 254) {
    SsdtCrsPkgLengthEncoding[0] = ACPI_BYTE_PREFIX_OPCODE;
    SsdtCrsPkgLengthEncoding[1] = (UINT8) ResourceBufferLength;
    DevicePackageLength = DevicePackageLength + 2; //Adding Package length encoding size
    DEBUG((DEBUG_INFO, "GenSsdt CrsPkgLengthEncoding1: 0x%x\n", SsdtCrsPkgLengthEncoding[1]));
  } else if (ResourceBufferLength < 65533) {
    SsdtCrsPkgLengthEncoding[0] = ACPI_WORD_PREFIX_OPCODE;
    SsdtCrsPkgLengthEncoding[1] = (UINT8) (ResourceBufferLength & 0x00FF);
    SsdtCrsPkgLengthEncoding[2] = (UINT8) ((ResourceBufferLength & 0xFF00) >> 8);
    DevicePackageLength = DevicePackageLength + 3; //Adding Package length encoding size
    DEBUG((DEBUG_INFO, "GenSsdt CrsPkgLengthEncoding1: 0x%x\n", SsdtCrsPkgLengthEncoding[1]));
    DEBUG((DEBUG_INFO, "GenSsdt CrsPkgLengthEncoding2: 0x%x\n", SsdtCrsPkgLengthEncoding[2]));
  }

  if (ResourceBufferLength < 61) {
    SsdtBufferPkgLengthEncoding[1] = (UINT8) ResourceBufferLength + 3; //Taking CrsPackageLength encoding into account
    DevicePackageLength = DevicePackageLength + 2; //Adding Package length encoding size
    DEBUG((DEBUG_INFO, "GenSsdt BufferPkgLengthEncoding1: 0x%x\n", SsdtBufferPkgLengthEncoding[1]));
  } else if (ResourceBufferLength < 4095) {
    SsdtBufferPkgLengthEncoding[1] = 0x40 | ((UINT8)((ResourceBufferLength + 5) & 0x00F)); //Taking CrsPackageLength encoding into account
    SsdtBufferPkgLengthEncoding[2] = (UINT8) (((ResourceBufferLength + 5) & 0xFF0) >> 4); //Taking CrsPackageLength encoding into account
    DevicePackageLength = DevicePackageLength + 3; //Adding Package length encoding size
    DEBUG((DEBUG_INFO, "GenSsdt BufferPkgLengthEncoding1: 0x%x\n", SsdtBufferPkgLengthEncoding[1]));
    DEBUG((DEBUG_INFO, "GenSsdt BufferPkgLengthEncoding2: 0x%x\n", SsdtBufferPkgLengthEncoding[2]));
  }

  ScopePackageLength = 0;
  if (DevicePackageLength < 63) {
    SsdtDevicePkgLengthEncoding[2] = (UINT8) DevicePackageLength;
    ScopePackageLength = ScopePackageLength + 3;
    DEBUG((DEBUG_INFO, "GenSsdt DevicePkgLengthEncoding2: 0x%x\n", SsdtDevicePkgLengthEncoding[2]));
  } else if (DevicePackageLength < 4094) {
    SsdtDevicePkgLengthEncoding[2] = 0x40 | ((UINT8)((DevicePackageLength + 2) & 0x00F));
    SsdtDevicePkgLengthEncoding[3] = (UINT8) (((DevicePackageLength + 2) & 0xFF0) >> 4);
    ScopePackageLength = ScopePackageLength + 4;
    DEBUG((DEBUG_INFO, "GenSsdt DevicePkgLengthEncoding2: 0x%x\n", SsdtDevicePkgLengthEncoding[2]));
    DEBUG((DEBUG_INFO, "GenSsdt DevicePkgLengthEncoding3: 0x%x\n", SsdtDevicePkgLengthEncoding[3]));
  }

  ScopePackageLength = ScopePackageLength + sizeof(SsdtScopeDualName) + DevicePackageLength;
  if (ScopePackageLength < 63) {
    SsdtScopePkgLengthEncoding[1] = (UINT8) ScopePackageLength;
    DEBUG((DEBUG_INFO, "GenSsdt ScopePkgLengthEncoding1: 0x%x\n", SsdtScopePkgLengthEncoding[1]));
  } else if (ScopePackageLength < 4094) {
    ScopePackageLength = ScopePackageLength + 2;
    SsdtScopePkgLengthEncoding[1] = 0x40 | ((UINT8)(ScopePackageLength & 0x00F));
    SsdtScopePkgLengthEncoding[2] = (UINT8) ((ScopePackageLength & 0xFF0) >> 4);
    DEBUG((DEBUG_INFO, "GenSsdt ScopePkgLengthEncoding1: 0x%x\n", SsdtScopePkgLengthEncoding[1]));
    DEBUG((DEBUG_INFO, "GenSsdt ScopePkgLengthEncoding2: 0x%x\n", SsdtScopePkgLengthEncoding[2]));
  }

  *SsdtTableSize = (UINT32) (sizeof(SsdtHeader) + sizeof(SsdtExternalDualName) + ScopePackageLength + 1);

  return EFI_SUCCESS;
}

EFI_STATUS
CreateAcpiTableInMemory (
  IN  UINT8   *AcpiDataBase,
  IN  UINT32  *SsdtTableSize,
  OUT UINT8   *CurrentTable
  )
{
  UINT8                         *CurrentTablePointer;
  EFI_ACPI_SDT_HEADER           *AcpiTableHeader;
  EFI_ACPI_SDT_HEADER           *SsdtTableInfo;
  SSDT_DEVICE_DATA              *SsdtDeviceInfo;
  GPIO_RESOURCE_DATA            *GpioResourceInfo;
  I2C_RESOURCE_DATA             *I2cResourceInfo;
  GPIO_RESOURCE                 *TempGpioResource;
  I2C_SERIAL_BUS_RESOURCE       *TempI2cResource;
  UINTN                         i;
  UINTN                         ResourceOffset;
  UINT8                         ResourceType;
  UINTN                         NextResource;
  UINT32                        Size;

  SsdtTableInfo = (EFI_ACPI_SDT_HEADER *) AcpiDataBase;
  SsdtDeviceInfo = (SSDT_DEVICE_DATA *) (AcpiDataBase + sizeof(EFI_ACPI_SDT_HEADER));
  ResourceOffset = sizeof(EFI_ACPI_SDT_HEADER) + sizeof(SSDT_DEVICE_DATA) - sizeof(UINT8);
  //
  // Copy SSDT content to allocated space
  //
  CurrentTablePointer = (UINT8 *) CurrentTable;
  CopyMem(CurrentTablePointer, &SsdtHeader, sizeof(SsdtHeader));
  AcpiTableHeader = (EFI_ACPI_SDT_HEADER *) CurrentTablePointer;
  AcpiTableHeader->Length = *SsdtTableSize;
  CopyMem(AcpiTableHeader->OemId, SsdtTableInfo->OemId, 6);
  CopyMem(AcpiTableHeader->OemTableId, SsdtTableInfo->OemTableId, 8);

  CurrentTablePointer = (UINT8 *) (CurrentTable + sizeof(SsdtHeader));
  CopyMem(CurrentTablePointer, &SsdtExternalDualName, sizeof(SsdtExternalDualName));
  *(CHAR8 *) (CurrentTablePointer + ACPI_EXTERNAL_PCI_BUS_NUMBER_OFFSET) = '0'; //PCI bus 0

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + sizeof(SsdtExternalDualName));
  Size = ((SsdtScopePkgLengthEncoding[1] & 0xC0) >> 6) + 2;
  CopyMem(CurrentTablePointer, &SsdtScopePkgLengthEncoding, Size);

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + Size);
  CopyMem(CurrentTablePointer, &SsdtScopeDualName, sizeof(SsdtScopeDualName));
  *(CHAR8 *) (CurrentTablePointer + ACPI_SCOPE_PCI_BUS_NUMBER_OFFSET) = '0'; //PCI bus 0

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + sizeof(SsdtScopeDualName));
  Size = ((SsdtDevicePkgLengthEncoding[2] & 0xC0) >> 6) + 3;
  CopyMem(CurrentTablePointer, &SsdtDevicePkgLengthEncoding, Size);

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + Size);
  CopyMem(&SsdtDeviceName, SsdtDeviceInfo->DeviceName, 4);
  CopyMem(CurrentTablePointer, &SsdtDeviceName, sizeof(SsdtDeviceName));

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + sizeof(SsdtDeviceName));
  CopyMem(CurrentTablePointer, &SsdtHardwareId, sizeof(SsdtHardwareId));
  CopyMem(CurrentTablePointer + ACPI_NAME_OBJECT_STRING_OFFSET, SsdtDeviceInfo->HardwareId, 8);

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + sizeof(SsdtHardwareId));
  CopyMem(CurrentTablePointer, &SsdtCompatibleId, sizeof(SsdtCompatibleId));
  CopyMem(CurrentTablePointer + ACPI_NAME_OBJECT_STRING_OFFSET, SsdtDeviceInfo->CompatibilityId, 8);

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + sizeof(SsdtCompatibleId));
  SsdtUniqueId[ACPI_UNIQUE_ID_NUMBER_OFFSET] = (UINT8) SsdtDeviceInfo->UniqueId;
  CopyMem(CurrentTablePointer, &SsdtUniqueId, sizeof(SsdtUniqueId));

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + sizeof(SsdtUniqueId));
  CopyMem(CurrentTablePointer, &SsdtCurrentResourceSettings, sizeof(SsdtCurrentResourceSettings));

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + sizeof(SsdtCurrentResourceSettings));
  Size = ((SsdtBufferPkgLengthEncoding[1] & 0xC0) >> 6) + 2;
  CopyMem(CurrentTablePointer, &SsdtBufferPkgLengthEncoding, Size);

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + Size);
  if (SsdtCrsPkgLengthEncoding[0] == ACPI_BYTE_PREFIX_OPCODE) {
    Size = 2;
  } else if (SsdtCrsPkgLengthEncoding[0] == ACPI_WORD_PREFIX_OPCODE) {
    Size = 3;
  }
  CopyMem(CurrentTablePointer, &SsdtCrsPkgLengthEncoding, Size);

  CurrentTablePointer = (UINT8 *) (CurrentTablePointer + Size);
  NextResource = 0;
  for (i = 0; i < SsdtDeviceInfo->NumberOfResources; i++) {
    ResourceType = *(UINT8 *)(AcpiDataBase + ResourceOffset + NextResource);
    switch (ResourceType) {
      case ACPI_GPIO_RESOURCE_TYPE :
      {
        CopyMem(CurrentTablePointer, &SsdtGpioResource, sizeof(SsdtGpioResource));
        TempGpioResource = (GPIO_RESOURCE *) CurrentTablePointer;
        DEBUG((DEBUG_INFO, "TempGpioConnDesc: %x\n", TempGpioResource->GpioConnectionDescriptor));
        DEBUG((DEBUG_INFO, "TempGpioResourceNumber1 before: %x\n", TempGpioResource->PinNumber1));
        DEBUG((DEBUG_INFO, "TempGpioResourceNumber2 before: %x\n", TempGpioResource->PinNumber2));
        GpioResourceInfo = (GPIO_RESOURCE_DATA *) (AcpiDataBase + ResourceOffset + NextResource);
        if (GpioResourceInfo->GpioResourceType == ACPI_GPIO_RESOURCE_TYPE_INTERRUPT) {
          TempGpioResource->GpioConnectionType = GpioInterrupt;
          TempGpioResource->InterruptAndIoFlags1 |= 0x10;
          TempGpioResource->PinNumber1 = GpioResourceInfo->GpioNumber & 0x00FF;
          TempGpioResource->PinNumber2 = (GpioResourceInfo->GpioNumber & 0xFF00) >> 8;
        } else if (GpioResourceInfo->GpioResourceType == ACPI_GPIO_RESOURCE_TYPE_IO) {
          TempGpioResource->GpioConnectionType = GpioIo;
          TempGpioResource->InterruptAndIoFlags1 &= 0x0F;
          TempGpioResource->PinNumber1 = GpioResourceInfo->GpioNumber & 0x00FF;
          TempGpioResource->PinNumber2 = (GpioResourceInfo->GpioNumber & 0xFF00) >> 8;
        }
        DEBUG((DEBUG_INFO, "TempGpioResourceNumber1 after: %x\n", TempGpioResource->PinNumber1));
        DEBUG((DEBUG_INFO, "TempGpioResourceNumber2 after: %x\n", TempGpioResource->PinNumber2));
        NextResource = NextResource + sizeof(GPIO_RESOURCE_DATA) - sizeof(UINT8);
        CurrentTablePointer = CurrentTablePointer + sizeof(SsdtGpioResource);

        break;
      }
      case ACPI_I2C_RESOURCE_TYPE :
      {
        CopyMem(CurrentTablePointer, &SsdtI2cSerialBusResource, sizeof(SsdtI2cSerialBusResource));
        TempI2cResource = (I2C_SERIAL_BUS_RESOURCE *) CurrentTablePointer;
        I2cResourceInfo = (I2C_RESOURCE_DATA *) (AcpiDataBase + ResourceOffset + NextResource);
        TempI2cResource->SlaveAddress = (UINT16) I2cResourceInfo->I2cSlaveAddress;
        TempI2cResource->ConnectionSpeed = I2cResourceInfo->ConnectionSpeed;
        *(CurrentTablePointer + ACPI_I2C_RESOURCE_CONTROLLER_NUMBER_OFFSET) = I2cResourceInfo->I2cSliceNumber + ASCII_0_ORDINAL;
        NextResource = NextResource + sizeof(I2C_RESOURCE_DATA) - sizeof(UINT8);
        CurrentTablePointer = CurrentTablePointer + sizeof(SsdtI2cSerialBusResource);

        break;
      }
    }
  }
  CopyMem(CurrentTablePointer, &SsdtResourceTemplateEndTag, sizeof(SsdtResourceTemplateEndTag));
  CurrentTablePointer = CurrentTablePointer + sizeof(SsdtResourceTemplateEndTag);
  if (SsdtDeviceInfo->EnableStatus == TRUE) {
    SsdtStatusMethod[ACPI_STA_RETURN_VALUE_OFFSET] = ACPI_STA_RETURN_VALUE_DEVICE_ENABLED;
  } else {
    SsdtStatusMethod[ACPI_STA_RETURN_VALUE_OFFSET] = ACPI_STA_RETURN_VALUE_DEVICE_DISABLED;
  }
  CopyMem(CurrentTablePointer, &SsdtStatusMethod, sizeof(SsdtStatusMethod));

  return EFI_SUCCESS;
}

/**
  Generate SSDTs from ACPI data available in BIOS board files
  or ACPI data generated from PCT tool FVs
**/
EFI_STATUS
GenerateSsdtFromConfigFile (
  VOID
)
{
  EFI_STATUS                    Status = EFI_SUCCESS;
  UINTN                         Pages;
  UINT8                         *CurrentTable;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;
  EFI_ACPI_SDT_HEADER           *AcpiTableHeader;
  UINT32                        SsdtTableSize;
  UINT8                         *PctAcpiDataBase;
  UINTN                         i,j;
  UINT8                         *PrintData;
  UINTN                         TableHandle;
  PCT_ACPI_BLOCK_HDR            *PctAcpiDataHeader;
  UINT16                        TableCount;
  UINT8                         *AcpiDataPointer;

  DEBUG((DEBUG_INFO, "GenSsdt start\n"));
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);
  ASSERT_EFI_ERROR(Status);

  //
  // Look for ACPI data HOB from PCT
  //
  PctAcpiDataBase = (UINT8 *) PcdGetPtr(PcdBoardAcpiData);
  if (*PctAcpiDataBase != 0) {
    PctAcpiDataHeader = (PCT_ACPI_BLOCK_HDR *) PctAcpiDataBase;
    AcpiDataPointer = (UINT8 *) (PctAcpiDataBase + sizeof(PCT_ACPI_BLOCK_HDR));
    // Get number of tables to be generated
    TableCount = PctAcpiDataHeader->Count;
    for (i=0; i<TableCount; i++) {
      // Calculate table size to be created
      Status = GetTableSize(AcpiDataPointer, &SsdtTableSize);
      ASSERT_EFI_ERROR (Status);

      // Allocate memory for SSDT
      Pages = EFI_SIZE_TO_PAGES(SsdtTableSize);
      Status = (gBS->AllocatePages) (
                       AllocateMaxAddress,
                       EfiACPIMemoryNVS,
                       Pages,
                       (EFI_PHYSICAL_ADDRESS *) &CurrentTable
                       );
      ASSERT_EFI_ERROR (Status);
      ZeroMem ((VOID *) CurrentTable, SsdtTableSize);

      //Copy SSDT content to allocated space
      Status = CreateAcpiTableInMemory(AcpiDataPointer, &SsdtTableSize, CurrentTable);
      ASSERT_EFI_ERROR (Status);

      //
      // Dump table content from memory
      //
      DEBUG_CODE_BEGIN();
      PrintData = (UINT8 *)CurrentTable;
      DEBUG((DEBUG_INFO, "GenSsdt TableDump:\n"));
      for (j=0; j<SsdtTableSize; j++) {
        DEBUG((DEBUG_INFO, "%02x ", *PrintData));
        PrintData++;
      }
      DEBUG((DEBUG_INFO, "\n"));
      DEBUG_CODE_END();

      TableHandle = 0;
      AcpiTableHeader = (EFI_ACPI_SDT_HEADER *)CurrentTable;

      //
      // Install SSDT
      //
      Status = AcpiTable->InstallAcpiTable (
                              AcpiTable,
                              CurrentTable,
                              AcpiTableHeader->Length,
                              &TableHandle
                              );

      ASSERT_EFI_ERROR(Status);

      AcpiDataPointer += ((EFI_ACPI_SDT_HEADER *) AcpiDataPointer)->Length;
    }
  }
  return Status;
}