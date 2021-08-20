/** @file
  The common header file for SMM SPI module and SMM SPI DXE Module.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _SPI_SMM_COMMUNICATION_H_
#define _SPI_SMM_COMMUNICATION_H_

#include <Protocol/Spi.h>

#pragma pack(1)

#define SPI_FUNCTION_FLASH_READ                  1
#define SPI_FUNCTION_FLASH_WRITE                 2
#define SPI_FUNCTION_FLASH_ERASE                 3
#define SPI_FUNCTION_FLASH_READ_SFDP             4
#define SPI_FUNCTION_FLASH_READ_JEDEC_ID         5
#define SPI_FUNCTION_FLASH_WRITE_STATUS          6
#define SPI_FUNCTION_FLASH_READ_STATUS           7
#define SPI_FUNCTION_GET_REGION_ADDRESS          8
#define SPI_FUNCTION_READ_PCH_SOFTSTRAP          9
#define SPI_FUNCTION_READ_CPU_SOFTSTRAP          10

typedef struct {
  UINTN       Function;
  EFI_STATUS  ReturnStatus;
  UINT8       Data[1];
} SMM_SPI_COMMUNICATE_FUNCTION_HEADER;

//
// Size of SMM communicate header, without including the payload.
//
#define SMM_COMMUNICATE_HEADER_SIZE  (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data))

//
// Size of SMM SPI communicate function header, without including the payload.
//
#define SMM_SPI_COMMUNICATE_HEADER_SIZE  (OFFSET_OF (SMM_SPI_COMMUNICATE_FUNCTION_HEADER, Data))

typedef struct {
  FLASH_REGION_TYPE  FlashRegionType;
  UINT32             Address;
  UINT32             ByteCount;
  UINT8              *Buffer;
} SMM_SPI_FLASH_READ;

typedef struct {
  FLASH_REGION_TYPE  FlashRegionType;
  UINT32             Address;
  UINT32             ByteCount;
  UINT8              *Buffer;
} SMM_SPI_FLASH_WRITE;

typedef struct {
  FLASH_REGION_TYPE  FlashRegionType;
  UINT32             Address;
  UINT32             ByteCount;
} SMM_SPI_FLASH_ERASE;

typedef struct {
  UINT8              ComponentNumber;
  UINT32             Address;
  UINT32             ByteCount;
  UINT8              *SfdpData;
} SMM_SPI_FLASH_READ_SFDP;

typedef struct {
  UINT8              ComponentNumber;
  UINT32             ByteCount;
  UINT8              *JedecId;
} SMM_SPI_FLASH_READ_JEDEC_ID;

typedef struct {
  UINT32             ByteCount;
  UINT8              *StatusValue;
} SMM_SPI_FLASH_WRITE_STATUS;

typedef struct {
  UINT32             ByteCount;
  UINT8              *StatusValue;
} SMM_SPI_FLASH_READ_STATUS;

typedef struct {
  FLASH_REGION_TYPE  FlashRegionType;
  UINT32             *BaseAddress;
  UINT32             *RegionSize;
} SMM_SPI_GET_REGION_ADDRESS;

typedef struct {
  UINT32             SoftStrapAddr;
  UINT32             ByteCount;
  VOID               *SoftStrapValue;
} SMM_SPI_READ_PCH_SOFTSTRAP;

typedef struct {
  UINT32             SoftStrapAddr;
  UINT32             ByteCount;
  VOID               *SoftStrapValue;
} SMM_SPI_READ_CPU_SOFTSTRAP;

#pragma pack()

#endif // _SPI_SMM_COMMUNICATION_H_
