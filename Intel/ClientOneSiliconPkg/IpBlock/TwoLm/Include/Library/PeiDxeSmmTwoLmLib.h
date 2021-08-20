/** @file
  @ Header file for parser function to get 2LM module details.
    These config details are stored in a HOB, to be able to use across different boot phases.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#ifndef PEIDXESMM_TWOLM_LIB_H_
#define PEIDXESMM_TWOLM_LIB_H_

#include <Base.h>
#include <Uefi.h>
#include <Library/HobLib.h>

extern EFI_GUID gTwoLmInfoHobGuid;

//
// Enum for BIOS Memory Modes for 2LM
//
#define MEM_BOOT_MODE_1LM   0
#define MEM_BOOT_MODE_2LM   1
#define MEM_BOOT_MODE_PROVISIONING   2



//
// Enum for BIOS Region Types
//
typedef enum {
  NVMeStorage = 0,
  VolatileMemory = 1,
  IntelReservedRegionMemory = 2,
  PersistenceMemory = 3,
  Reserved
} BIOS_REGION_TYPE;


//
// Enum for Far Memory Region Attributes
//
typedef enum {
  StorageMode = 0,
  MemoryMode  = 1,
} REGION_ATTRIBUTES;


#pragma pack (1)

/**
  2LM information
  This structure is populated with the information collected from 2LM device thru mailbox interface.
  This information is used to make decisions in 2LM boot mode.
**/


//
// 2LM Info HOB
//
typedef struct {
  UINT8                  EpocBitValue;
  UINT8                  SetupOption; // From the platform policy UPD
  UINT8                  CurrentMemBootMode; // 1LM/2LM/Provisioning
  UINT32                 NearMemSize; // in MB, upto 64GB size
  UINT8                  MemoryEncryptionSupported; // For 2LM memory region
  UINT8                  PlatformRegionRequired; // Check if required for IRR?
  UINT8                  TotalNumberofRegions; // Number of valid regions provisioned, used during query region
  UINT8                  DeviceProvisioningStatus;
  UINT8                  RegionId2lm; // 0xFF indicates invalid region
  UINT8                  RegionIdPMem; // 0xFF indicates invalid region
  UINT8                  RegionIdStorage; // 0xFF indicates invalid region, BIOS will disable NVMe fun if there is no storage region.
  UINT8                  RegionIdIrr; // 0xFF indicates invalid region
  UINT32                 FarMemSize; // Far Memory Size in MB.
  UINT32                 PMemSize; // in MB
  UINT32                 StorageSize; // in MB
  UINT32                 IrrSize; //in MB
  UINT8                  FarMemFZS; // 2LM fast zero support
  UINT64                 PMemBase;   // In bytes
  UINT64                 PMemLimit;
  UINT32                 ToludBase;
  UINT32                 RemapBase;
  UINT32                 RemapLimit;
  UINT8                  Mrts; // Maximum amount of Far Memory MRd TLP outstanding supported
  UINT8                  Mwss; // Maximum amount of Far Memory Write Slice outstanding supported
  UINT8                  Mcsrts; // Maximum amount of CSR register access VDM TLP
  UINT16                 TpowerOnSupport;
  UINT16                 VendorId; // Vendor ID of 2LM module
  UINT16                 DevId; // Device ID of 2LM module
  UINT16                 RevisionId; // Chip revision id (stepping) of the ASIC
  UINT16                 Ifc; //0x301
  UINT32                 SerialNum; // Read first 4 bytes from mailbox Identify Command Serial Number
  UINT8                  MemoryModeSupported     : 1;
  UINT8                  StorageModeSupported    : 1;
  UINT8                  PMemModeSupported       : 1;
  UINT8                  DieSparingCapable       : 1;
  UINT8                  Rsvd1                   : 4;
} TWOLM_INFO;


// 2LM Info Hob

typedef struct {
  EFI_HOB_GUID_TYPE      EfiHobGuidType;
  TWOLM_INFO             TwoLmInfo;
} TWOLM_INFO_HOB;

#pragma pack ()


UINT32 TwoLmGetEpoc (
  );


VOID TwoLmSetEpoc (
  IN UINT32  EpocValue
  );
#endif /* PEIDXESMM_TWOLM_LIB_H_ */
