/** @file
  FrontPage routines to handle the callbacks and browser calls

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification
**/


//**/
#ifndef _FORMSET_GUID_H_
#define _FORMSET_GUID_H_

#include "BootMaint/FormGuid.h"

#define FRONT_PAGE_FORMSET_GUID  { 0x9e0c30bc, 0x3f06, 0x4ba6, 0x82, 0x88, 0x9, 0x17, 0x9b, 0x85, 0x5d, 0xbe }

// Used by Boot manager form
#define BOOT_MANAGER_FORMSET_GUID  { 0x847bc3fe, 0xb974, 0x446d, 0x94, 0x49, 0x5a, 0xd5, 0x41, 0x2e, 0x99, 0x3b }

#define BOOT_MANAGER_FORM_ID     0x1000


// Used by Device manager form.
#define DEVICE_MANAGER_FORMSET_GUID  { 0x3ebfa8e6, 0x511d, 0x4b5b, 0xa9, 0x5f, 0xfb, 0x38, 0x26, 0xf, 0x1c, 0x27 }


#define DEVICE_KEY_OFFSET                  0x2000
#define NETWORK_DEVICE_LIST_KEY_OFFSET     0x2100
#define MAX_KEY_SECTION_LEN                0x0100

#define QUESTION_NETWORK_DEVICE_ID         0x2FFF

#define LABEL_END                          0xffff
#define LABEL_FORM_ID_OFFSET               0x0100
#define LABEL_VBIOS                        0x0040


#endif
