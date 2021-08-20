/** @file
  This file contains function definitions that can determine
  the TXT resource of a platform during SMM and perform
  certain specific platform tasks that are required for TXT
  during SMM.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
#ifndef _SMM_TXT_RESOURCE_PROTOCOL_H_
#define _SMM_TXT_RESOURCE_PROTOCOL_H_

///
/// Resource database header
///
#pragma pack(push, 1)
typedef union _RESOURCE       RESOURCE;

typedef struct _RESOURCE_AREA RESOURCE_AREA;

struct _RESOURCE_AREA {
  EFI_PHYSICAL_ADDRESS  AreaAddress;
  UINT32                AreaSize;
  UINT32                FreeSize;
  EFI_PHYSICAL_ADDRESS  EndOfRscAddress;
  EFI_PHYSICAL_ADDRESS  FreeSpaceAddress;
};

#define MAX_AREAS   4
#define AREA_SIZE   0x1000
#define APPEND      0
#define START_OVER  !0

typedef struct _STM_RESOURCE_HEADER STM_RESOURCE_HEADER;

struct _STM_RESOURCE_HEADER {
  UINT32        NumAreas;
  RESOURCE_AREA Area[MAX_AREAS];
};

///
/// Resource definitions
///
#define END_OF_RESOURCES      0
#define MEM_RANGE             1
#define IO_RANGE              2
#define MMIO_RANGE            3
#define MACHINE_SPECIFIC_REG  4
#define PCI_CFG_RANGE         5
#define TRAPPED_IO_RANGE      6
#define MAX_DESC_TYPE         6

#define RD_ACCS               1
#define WR_ACCS               2
#define EX_ACCS               4
#define RDWR_ACCS             3
#define FULL_ACCS             7

typedef struct {
  UINT32  RscType;
  UINT16  Length;
  UINT16  ReturnStatus : 1;
  UINT16  Res : 14;
  UINT16  IgnoreResource : 1;
} STM_RSC_DESC_HEADER;

typedef struct {
  STM_RSC_DESC_HEADER Hdr;
  UINT64              ResourceListContinuation;
} STM_RSC_END;

typedef struct {
  STM_RSC_DESC_HEADER Hdr;
  UINT64              Base;
  UINT64              Length;
  UINT32              RWXAttributes;
  UINT32              Reserved;   /// must be 0
} STM_RSC_MEM_DESC;

typedef struct {
  STM_RSC_DESC_HEADER Hdr;
  UINT16              Base;
  UINT16              Length;
  UINT32              Reserved;   /// must be 0
} STM_RSC_IO_DESC;

typedef struct {
  STM_RSC_DESC_HEADER Hdr;
  UINT64              Base;
  UINT64              Length;
  UINT32              RWXAttributes;
  UINT32              Reserved;   /// must be 0
} STM_RSC_MMIO_DESC;

#define MASK0     0
#define MASK64    0xFFFFFFFFFFFFFFFF
#define TABLE_END 0xFFFFFFFFFFFFFFFF

typedef struct {
  STM_RSC_DESC_HEADER Hdr;
  UINT64              MsrIndex;
  UINT64              ReadMask;
  UINT64              WriteMask;
} STM_RSC_MSR_DESC;

typedef struct {
  UINT8 PciFunction;
  UINT8 PciDevice;
} STM_PCI_DEVICE_PATH_NODE;

typedef struct {
  STM_RSC_DESC_HEADER       Hdr;
  UINT16                    RWAttributes;
  UINT16                    Base;
  UINT16                    Length;
  UINT8                     OriginatingBusNumber;
  UINT8                     LastNodeIndex;
  UINT8                     Reserved;
  STM_PCI_DEVICE_PATH_NODE  PciDevicePath[1];
} STM_RSC_PCI_CFG_DESC;

typedef struct {
  STM_RSC_DESC_HEADER Hdr;
  UINT16              Base;
  UINT16              Length;
  UINT16              In : 1;
  UINT16              Out : 1;
  UINT16              Api : 1;
  UINT16              Reserved1 : 13;
  UINT16              Reserved2;  /// must be 0
} STM_RSC_TRAPPED_IO_DESC;

union _RESOURCE {
  STM_RSC_DESC_HEADER     hdr;
  STM_RSC_MEM_DESC        mem;
  STM_RSC_IO_DESC         io;
  STM_RSC_MMIO_DESC       mmio;
  STM_RSC_MSR_DESC        msr;
  STM_RSC_PCI_CFG_DESC    pci;
  STM_RSC_TRAPPED_IO_DESC trapio;
  STM_RSC_END             eor;
};

#pragma pack(pop)

typedef struct _SMM_TXT_RESOURCE_PROTOCOL           SMM_TXT_RESOURCE_PROTOCOL;
typedef struct _STM_MAP_ADDRESS_RANGE_DESCRIPTOR    STM_MAP_ADDRESS_RANGE_DESCRIPTOR;
typedef struct _STM_UNMAP_ADDRESS_RANGE_DESCRIPTOR  STM_UNMAP_ADDRESS_RANGE_DESCRIPTOR;
typedef struct _STM_API_ADDRESS_LOOKUP_DESCRIPTOR   STM_API_ADDRESS_LOOKUP_DESCRIPTOR;

///
/// Member functions
///
typedef
EFI_STATUS
(EFIAPI *STM_MAP_ADDRESS_RANGE) (
  STM_MAP_ADDRESS_RANGE_DESCRIPTOR * Buf
  );

typedef
EFI_STATUS
(EFIAPI *STM_UNMAP_ADDRESS_RANGE) (
  STM_UNMAP_ADDRESS_RANGE_DESCRIPTOR * Buf
  );

typedef
EFI_STATUS
(EFIAPI *STM_API_ADDRESS_LOOKUP) (
  STM_API_ADDRESS_LOOKUP_DESCRIPTOR * Buf
  );

struct _SMM_TXT_RESOURCE_PROTOCOL {
  STM_MAP_ADDRESS_RANGE   StmMapAddressRange;
  STM_UNMAP_ADDRESS_RANGE StmUnmapAddressRange;
  STM_API_ADDRESS_LOOKUP  StmApiAddressLookup;
};
#endif
