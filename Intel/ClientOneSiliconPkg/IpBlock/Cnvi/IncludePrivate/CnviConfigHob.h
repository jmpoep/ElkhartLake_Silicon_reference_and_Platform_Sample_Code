/** @file
  This file defines the CNVi CONFIG HOB

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
#ifndef _CNVI_CONFIG_HOB_H_
#define _CNVI_CONFIG_HOB_H_

#include <Base.h>

extern EFI_GUID gCnviConfigHobGuid;
#pragma pack (push,1)

/**
  This HOB is used to pass CNVi related private information to DXE phase
**/
typedef struct {
  EFI_HOB_GUID_TYPE EfiHobGuidType; ///< GUID HOB type structure for gCnviConfigHobGuid
  UINT32 Mode           :  1; ///< 0: Disabled, <b>1: Auto</b>
  UINT32 BtCore         :  1; ///< 0: Disabled, <b>1: Enabled</b>
  UINT32 BtAudioOffload :  1; ///< <b>0: Disabled</b>, 1: Enabled
  UINT32 RsvdBits0      : 29; ///< Reserved bits
} CNVI_CONFIG_HOB;
#pragma pack (pop)

#endif // _CNVI_CONFIG_HOB_H_
