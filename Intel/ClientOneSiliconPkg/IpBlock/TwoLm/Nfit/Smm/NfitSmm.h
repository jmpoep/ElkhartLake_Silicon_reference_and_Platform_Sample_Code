/** @file

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

#ifndef __NFIT_SMM_H__
#define __NFIT_SMM_H__

#include <PiDxe.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/SmmVariable.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/IoLib.h>
#include <Library/PrintLib.h>
#include <Library/PcdLib.h>
#include <Library/FmssMbLib.h>
#include <Library/PeiDxeSmmTwoLmLib.h>
#include <Library/HobLib.h>

#pragma pack(1)
typedef struct {
  UINT8                  FisSwSmiNumber;
  UINT8                  FisFuntionNumber;
  UINT32                 Data1;
  UINT32                 Data2;
  UINT32                 Data3;
  UINT32                 Buffer[128];
} NVDIMM_NVS;

typedef struct {
  UINT8                  OpRegionOp;
  UINT32                 NameString;
  UINT8                  RegionSpace;
  UINT8                  DWordPrefix;
  UINT32                 RegionOffset;
  UINT8                  BytePrefix;
  UINT8                  RegionLen;
} AML_OP_REGION_32_8;

typedef struct {
  UINT8  Enable;
  UINT8  RegionId;
  UINT16 Rsvd;
  UINT64 DpaStartAddr;
  UINT64 DpaEndAddr;
  UINT64 DpaCurrAddr;
} ARS_OUTPUT_DATA;

typedef struct {
  UINT16        PacketNo;
  UINT32        PacketLength;
  UINT32        PacketData[128];
} UpdateFwPacket;

#pragma pack()
#endif  // __NFIT_SMM_H__
