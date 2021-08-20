/** @file
  The GUID definition for SaConfigHob

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#ifndef _SA_CONFIG_HOB_H_
#define _SA_CONFIG_HOB_H_

#include <SaCommonDefinitions.h>
#include <Base.h>
#include "HybridGraphicsInfo.h"
#include "CpuPcieInfo.h"

extern EFI_GUID gSaConfigHobGuid;

#pragma pack (push,1)
///
/// DPR Directory Types
///
typedef enum {
  EnumDprDirectoryTxt   = 0,
  EnumDprDirectoryBiosGuard
} DPR_DIRECTORY_ELEMENT;

#define DPR_DIRECTORY_TYPE_TXT          0x01      ///< DPR directory type - TXT
#define DPR_DIRECTORY_TYPE_BIOSGUARD    0x02      ///< DPR directory type - BIOS Guard
#define DPR_DIRECTORY_MAX               2         ///< DPR Maximum Size

///
/// DPR directory entry definition
///
typedef struct {
  UINT8   Type;          ///< DPR Directory Type
  UINT8   Size;          ///< DPR Size in MB
  UINT32  PhysBase;      ///< Must be 4K aligned (bits 11..0 must be clear)
  UINT16  Reserved;      ///< Must be 0
} DPR_DIRECTORY_ENTRY;

///
/// System Agent Config Hob
///
typedef struct {
  EFI_HOB_GUID_TYPE        EfiHobGuidType;                           ///< GUID Hob type structure for gSaConfigHobGuid
  DPR_DIRECTORY_ENTRY      DprDirectory[DPR_DIRECTORY_MAX];          ///< DPR directory entry definition
  UINT8                    ApertureSize;                             ///< Aperture size value
  BOOLEAN                  CridEnable;                               ///< This field inidicates if CRID is enabled or disabled (to support Intel(R) SIPP)
  BOOLEAN                  SkipPamLock;                              ///< 0=All PAM registers will be locked in System Agent code, 1=Do not lock PAM registers in System Agent code.
} SA_CONFIG_HOB;
#pragma pack (pop)
#endif
