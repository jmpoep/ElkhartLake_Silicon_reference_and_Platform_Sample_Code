/** @file
  Interface definition Me Platform Get Reset Type.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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
#ifndef _ME_PLATFORM_GET_RESET_TYPE_H_
#define _ME_PLATFORM_GET_RESET_TYPE_H_


#define ME_PLATFORM_GET_RESET_TYPE_PROTOCOL_REVISION 1
extern EFI_GUID gMePlatformGetResetTypeGuid;

///
/// ME_SPECIAL_RESET_TYPES must be aligned with PCH_EXTENDED_RESET_TYPES
///
typedef enum {
  PowerCycleResetReq  = 3,
  GlobalResetReq,
  GlobalResetWithEcReq,
  MaxRestReq
} ME_SPECIAL_RESET_TYPES;

/**
  Get Platform requested reset type

  @param[in] Type                 UEFI defined reset type

  @retval ME_SPEICAL_RESET_TYPES  ME reset type aligned with PCH_EXTENDED_RESET_TYPES
**/
typedef
ME_SPECIAL_RESET_TYPES
(EFIAPI *ME_GET_RESET_TYPE) (
  IN EFI_RESET_TYPE               Type
  );
/**
  Me Platform Get Reset Type Protocol
  Provide reset services cooperated with ME FW and allow platform hook prior to architecture reset service
  is called.
**/
typedef struct _ME_PLATFORM_GET_RESET_TYPE_PROTOCOL {
  UINT8                           Revision;
  ME_GET_RESET_TYPE               MeGetResetType;
} ME_PLATFORM_GET_RESET_TYPE_PROTOCOL;

#endif
