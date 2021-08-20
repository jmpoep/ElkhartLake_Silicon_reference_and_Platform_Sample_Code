/** @file
  This file contains definitions required for One-Touch function.

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

#ifndef _TXT_ONE_TOUCH_H_
#define _TXT_ONE_TOUCH_H_

//
// Operation
//
#define ENABLE_VT                             128
#define DISABLE_VT_TXT                        129
#define ENABLE_VTD                            130
#define DISABLE_VTD_TXT                       131
#define ENABLE_ACTTPM_VT_VTD_TXT_DISABLE_STM  132
#define ENABLE_ACTTPM_VT_VTD_TXT_STM          133
#define DISABLE_STM                           134
#define DISABLE_TXT_STM                       135
#define DISABLE_SENTER_VMX                    136
#define ENABLE_VMX_SMX_ONLY                   137
#define ENABLE_VMX_OUTSIDE_SMX                138
#define ENABLE_VMX                            139
#define ENABLE_SENTER_ONLY                    140
#define ENABLE_SENTER_VMX_IN_SMX              141
#define ENABLE_SENTER_VMX_OUTSIDE_SMX         142
#define ENABLE_SENTER_VMX                     143
#define SET_NO_TXT_MAINTENANCE_FALSE          159
#define SET_NO_TXT_MAINTENANCE_TRUE           160

#endif
