/** @file
  Include file for PCI and Media device inventory.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2019 Intel Corporation.

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
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <Library/DxeMeLib.h>

#define MEDIA_DEVICE_SERIAL_NO_MAX_LENGTH  20
#define MEDIA_DEVICE_VERSION_NO_MAX_LENGTH 8
#define MEDIA_DEVICE_MODEL_NO_MAX_LENGTH   40

#define HWA_MEDIA_IN_ATA                 0x0000
#define HWA_MEDIA_IN_ATAPI               0x0001
#define HWA_MEDIA_IN_SATA                0x0002
#define HWA_MEDIA_IN_PCIE                0x0003

#define HWA_MEDIA_DT_HDD                 0x0000
#define HWA_MEDIA_DT_CDROM               0x0001
#define HWA_MEDIA_DT_DVD                 0x0002
#define HWA_MEDIA_DT_FDD                 0x0003
#define HWA_MEDIA_DT_MO                  0x0004

#define HWA_FRU_TYPE_PCI                  1

#pragma pack(1)

typedef struct {
  UINT8  SmbiosType;
  UINT8  Length;
  UINT16 SmbiosHandle;
  UINT32 FruType;
  UINT16 VendorId;
  UINT16 DeviceId;
  UINT16 RevisionId;
  UINT16 SubsystemVendorId;
  UINT16 SubsystemDeviceId;
  UINT32 ClassCode;
  UINT16 BusDevFunc;
} HWA_PCI_FRU_DATA;

typedef struct {
  UINT16            TableByteCount;
  UINT16            StructureCount;
  HWA_PCI_FRU_DATA  Data[0];
} HWA_FRU_TABLE;

typedef struct {
  UINT16 StructSize;
  UINT8  Interface;
  UINT8  DevType;
  UINT8  Rsvd[40];
  UINT8  SerialNo[MEDIA_DEVICE_SERIAL_NO_MAX_LENGTH];
  UINT8  VersionNo[MEDIA_DEVICE_VERSION_NO_MAX_LENGTH];
  UINT8  ModelNo[MEDIA_DEVICE_MODEL_NO_MAX_LENGTH];
  UINT64 MaxMediaSize;
  UINT16 SupportedCmdSets[3];
} HWA_FRU_MEDIA_DEVICES;

typedef struct {
  UINT8                  SmbiosType;
  UINT8                  Length;
  UINT16                 SmbiosHandle;
  HWA_FRU_MEDIA_DEVICES  MediaData;
} HWA_MEDIA_ENTRY;

typedef struct {
  UINT16          TableByteCount;
  UINT16          StructureCount;
  HWA_MEDIA_ENTRY Data[0];
} HWA_MEDIA_TABLE;

#pragma pack()

///
/// NVME definition
///
#define NVME_GENERIC_TIMEOUT            EFI_TIMER_PERIOD_SECONDS (5)
#define NVME_CONTROLLER_ID              0

#define NVME_ALL_NAMESPACES             0xFFFFFFFF

#define NVME_IDENTIFY_NAMESPACE_STRUCT  0
#define NVME_IDENTIFY_CONTROLLER_STRUCT 1

/**
  Constructs each of the lower level asset tables

  @param[in]  AssetTablesData           Buffer of all Asset tables to send to FW
  @param[in]  IsMediaTablePushRequested Determines if CSME has requested Media Table in this boot

  @return     TableSize                 Total Size of the HWA Table
**/
UINT16
BuildHwaTable (
  IN  HWA_TABLE           *AssetTableData,
  IN  BOOLEAN             IsMediaTablePushRequested
  );

#endif // _INVENTORY_H_
