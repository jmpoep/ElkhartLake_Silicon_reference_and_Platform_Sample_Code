/**@file
 Byte stream structures for ACPI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#ifndef _ACPI_BYTE_STREAM_H_
#define _ACPI_BYTE_STREAM_H_

#include <IndustryStandard/Acpi.h>

// @todo: Push these macros to Acpi.h file in Edk2 core.

//
// Definition block ecoding
//
#define ACPI_DEFINITION_BLOCK_LEADBYTE_OFFSET 0x24
#define ACPI_DEFINITION_BLOCK_PACKAGE_LENGTH_OFFSET 0x25

//
// External byte stream values and offsets
//
#define ACPI_EXTERNAL_OPCODE 0x15
#define ACPI_HEADER_EXTERNAL_OFFSET  0x24
#define ACPI_EXTERNAL_PCI_BUS_NUMBER_OFFSET 0xA
#define ACPI_EXTERNAL_NAME_TYPE_PREFIX_OFFSET 0x2
#define ACPI_EXTERNAL_NAME_OBJECT_COUNT_OFFSET 0x3

#define ACPI_DUAL_NAME_PREFIX 0x2E
#define ACPI_MULTI_NAME_PREFIX 0x2F

#define ACPI_SCOPE_OPCODE 0x10
#define ACPI_SCOPE_PACKAGE_LENGTH_OFFSET 0x1
#define ACPI_SCOPE_PCI_BUS_NUMBER_OFFSET 0x9

#define ACPI_PACKAGE_LENGTH_BYTEDATA_COUNT_MASK 0x3F

#define ACPI_DEVICE_PACKAGE_LENGTH_OFFSET 0X2

#define ACPI_NAME_OBJECT_STRING_OFFSET 0x6

#define ACPI_METHOD_NAME_OFFSET 0x1

#define ACPI_UNIQUE_ID_NUMBER_OFFSET 0x5

#define ACPI_CRS_BUFFER_LENGTH_PREFIX 0x8
#define ACPI_CRS_BUFFER_LENGTH_OFFSET 0x9

#define ACPI_BYTE_PREFIX_OPCODE 0x0A
#define ACPI_WORD_PREFIX_OPCODE 0x0B
#define ACPI_DWORD_PREFIX_OPCODE 0x0C
#define ACPI_STRING_PREFIX_OPCODE 0x0D
#define ACPI_QWORD_PREFIX_OPCODE 0x0E

#define ACPI_I2C_RESOURCE_CONTROLLER_NUMBER_OFFSET 0x1F

#define ACPI_STA_RETURN_VALUE_OFFSET 0x9
#define ACPI_STA_RETURN_VALUE_DEVICE_ENABLED 0xF
#define ACPI_STA_RETURN_VALUE_DEVICE_DISABLED 0x0

#define ACPI_GPIO_RESOURCE_TYPE 0x1
#define ACPI_GPIO_RESOURCE_TYPE_INTERRUPT 0x1
#define ACPI_GPIO_RESOURCE_TYPE_IO 0x2

#define ACPI_I2C_RESOURCE_TYPE 0x2

#define ASCII_0_ORDINAL ((UINT32) '0')

typedef struct {
  UINT8 GpioConnectionDescriptor; // 0x8C
  UINT8 Length1;
  UINT8 Length2;
  UINT8 RevisionId;
  UINT8 GpioConnectionType; // 0x0 - Interrupt, 0x01 - IO Connection, 0x02-0xFF reserved
  UINT8 GeneralFlags1;
  UINT8 GeneralFlags2;
  UINT8 InterruptAndIoFlags1;
  UINT8 InterruptAndIoFlags2;
  UINT8 PinConfiguration;
  UINT8 OutputDriveStrength1;
  UINT8 OutputDriveStrength2;
  UINT8 DebounceTimeOut1;
  UINT8 DebounceTimeOut2;
  UINT8 PinTableOffset1;
  UINT8 PinTableOffset2;
  UINT8 ResourceSourceIndex;
  UINT8 ResourceSourceNameOffset1;
  UINT8 ResourceSourceNameOffset2;
  UINT8 VendorDataOffset1;
  UINT8 VendorDataOffset2;
  UINT8 VendorDataLength1;
  UINT8 VendorDataLength2;
  UINT8 PinNumber1;
  UINT8 PinNumber2;
  CHAR8 ResourceSource[15];
} GPIO_RESOURCE;

typedef enum {
  GpioInterrupt,
  GpioIo
} GPIO_CONNECTION_TYPE;

typedef struct {
  UINT8 I2cBusConnectionDescriptor; // 0x8E
  UINT8 Length1;
  UINT8 Length2;
  UINT8 RevisionId;
  UINT8 ResourceSourceIndex;
  UINT8 SerialBusType; // 0x1 for I2C
  UINT8 GeneralFlags;
  UINT8 TypeSpecificFlags1;
  UINT8 TypeSpecificFlags2;
  UINT8 TypeSpecificRevisionId; // 0x1 for I2C
  UINT8 TypeDataLength1; // minimum value 0x6
  UINT8 TypeDataLength2; // minimum value 0x0
  UINT32 ConnectionSpeed;
  UINT16 SlaveAddress;
  CHAR8 ResourceSource[15];
} I2C_SERIAL_BUS_RESOURCE;

typedef struct {
  UINT8    ResourceType;
  UINT16   GpioNumber;
  UINT8    GpioResourceType;
  BOOLEAN  Shared;
} GPIO_RESOURCE_DATA;

typedef struct {
  UINT8    ResourceType;
  UINT32   I2cSlaveAddress;
  UINT32   ConnectionSpeed;
  UINT8    I2cSliceNumber;
} I2C_RESOURCE_DATA;

typedef struct {
  CHAR8     DeviceName[4];
  CHAR8     HardwareId[8];
  CHAR8     CompatibilityId[8];
  UINT32    UniqueId;
  UINT8     Address;
  CHAR8     DosDeviceName[32];
  UINT8     EnableStatus;
  UINT8     NumberOfResources;
} SSDT_DEVICE_DATA;

typedef struct {
  EFI_GUID  Guid;
  UINT8     Revision;
  UINT16    Count;
  UINT8     Rsvd[5];
} PCT_ACPI_BLOCK_HDR;

#endif
