/** @file
  The GUID definition for SaDataHob

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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
#ifndef _SA_DATA_HOB_H_
#define _SA_DATA_HOB_H_

#include <Base.h>
#include <Register/CpuPcieRegs.h>
#include <CpuPcieInfo.h>

extern EFI_GUID gSaDataHobGuid;
#pragma pack (push,1)

///
/// System Agent Data Hob
///
typedef struct {
  EFI_HOB_GUID_TYPE        EfiHobGuidType;                       ///< GUID Hob type structure for gSaDataHobGuid
  UINT32                   IedSize;                              ///< Size of IED region in bytes: <b>0=IED Disabled(no memory occupied)</b>, 0x400000=4MB occupied by IED.
  BOOLEAN                  LegacyOnlyVgaOpRomDetected;           ///< 0=No Legacy Only VBIOS or did not scan, 1=Legacy Only VBIOS Detected

  UINT8                    EnableAbove4GBMmio;                   ///< 0=Disable above 4GB MMIO resource support, 1=Enable above 4GB MMIO resource support
  UINT8                    Rsvd1[1];                             ///< Reserved for future use
} SA_DATA_HOB;
#pragma pack (pop)
#endif
