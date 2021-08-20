/** @file
  HOB definition to be used by DTBT.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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
#ifndef _DTBT_INFO_GUID_H_
#define _DTBT_INFO_GUID_H_
#include <PeiDTbtGenericStructure.h>
#include <DTbtDefinition.h>

#pragma pack(1)
//
// DTBT Info HOB
//
typedef struct _DTBT_INFO_HOB {
  EFI_HOB_GUID_TYPE      EfiHobGuidType;
  DTBT_GENERIC_CONFIG    DTbtGenericConfig;                                 ///< dTbt Geneirc Configuration
  DTBT_CONTROLLER_CONFIG DTbtControllerConfig [MAX_DTBT_CONTROLLER_NUMBER]; ///< dTbt Controller Configuration
} DTBT_INFO_HOB;
#pragma pack()

#endif
