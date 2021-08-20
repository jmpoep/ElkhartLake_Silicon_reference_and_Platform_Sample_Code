/** @file
  This file defined status code of Beihai HAL

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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


#ifndef _BEIHAI_STATUS_HAL_H_
#define _BEIHAI_STATUS_HAL_H_

typedef enum _BH_STATUS
{
   HAL_SUCCESS                      = 0x00000000,

   HAL_TIMED_OUT                    = 0x00001001,
   HAL_FAILURE                      = 0x00001002,
   HAL_OUT_OF_RESOURCES             = 0x00001003,
   HAL_OUT_OF_MEMORY                = 0x00001004,
   HAL_BUFFER_TOO_SMALL             = 0x00001005,
   HAL_INVALID_HANDLE               = 0x00001006,
   HAL_NOT_INITIALIZED              = 0x00001007,
   HAL_INVALID_PARAMS               = 0x00001008,
   HAL_NOT_SUPPORTED                = 0x00001009,
   HAL_NO_EVENTS                    = 0x0000100A,
   HAL_NOT_READY                    = 0x0000100B,
   HAL_CONNECTION_CLOSED            = 0x0000100C,
   // ...etc

   HAL_INTERNAL_ERROR               = 0x00001100,
   HAL_ILLEGAL_FORMAT               = 0x00001101,
   HAL_LINKER_ERROR                 = 0x00001102,
   HAL_VERIFIER_ERROR               = 0x00001103,

   // User defined applet & session errors to be returned to the host (should be exposed also in the host DLL)
   HAL_FW_VERSION_MISMATCH          = 0x00002000,
   HAL_ILLEGAL_SIGNATURE            = 0x00002001,
   HAL_ILLEGAL_POLICY_SECTION       = 0x00002002,
   HAL_OUT_OF_STORAGE               = 0x00002003,
   HAL_UNSUPPORTED_PLATFORM_TYPE    = 0x00002004,
   HAL_UNSUPPORTED_CPU_TYPE         = 0x00002005,
   HAL_UNSUPPORTED_PCH_TYPE         = 0x00002006,
   HAL_UNSUPPORTED_FEATURE_SET      = 0x00002007,
   HAL_ILLEGAL_VERSION              = 0x00002008,
   HAL_ALREADY_INSTALLED            = 0x00002009,
   HAL_MISSING_POLICY               = 0x00002010,
   HAL_ILLEGAL_PLATFORM_ID          = 0x00002011,
   HAL_UNSUPPORTED_API_LEVEL        = 0x00002012,
   HAL_LIBRARY_VERSION_MISMATCH     = 0x00002013

   // ... etc

} BH_STATUS;

#endif // _BEIHAI_STATUS_HAL_H_
