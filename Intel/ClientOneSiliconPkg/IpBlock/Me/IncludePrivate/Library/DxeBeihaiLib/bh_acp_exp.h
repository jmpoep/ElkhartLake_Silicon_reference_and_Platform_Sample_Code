/** @file
  This file defined external data structure and api for application layer
  pload is short for "Parse and Load"
  These api are used to parse the format of the raw_data and assign each item pointer with correct address
  caller should be responsible to ensure raw_data is not released when using parsed pack struct

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

#ifndef __BH_ACP_EXP_H
#define __BH_ACP_EXP_H

#include "bh_shared_errcode.h"
#include "bh_acp_format.h"

#pragma pack(1)

typedef struct {
    ACPackHeader* head;
    ACInsSDPack cmd_pack;
    ACSig* sign;
} ACInsSDPackExt;

typedef struct {
    ACPackHeader* head;
    ACUnsSDPack cmd_pack;
    ACSig* sign;
} ACUnsSDPackExt;

typedef struct {
    ACPackHeader* head;
    ACInsJTAPack cmd_pack;
    ACSig* sign;
    char* ta_pack;
} ACInsJTAPackExt;

typedef struct {
    ACPackHeader* head;
    ACInsNTAPack cmd_pack;
    ACSig* sign;
    char* ta_pack;
} ACInsNTAPackExt;

typedef struct {
    ACPackHeader *head;
    ACUnsTAPack cmd_pack;
    ACSig* sign;
} ACUnsTAPackExt;

typedef struct {
    ACInsJTAProp cmd_pack;
    char* jeff_pack;
} ACInsJTAPropExt;

typedef struct {
    ACPackHeader* head;
    ACUpdateSVLPack cmd_pack;
    ACSig* sign;
} ACUpdateSVLPackExt;

typedef struct {
    ACProp *props;
} ACTAProps;

#pragma pack()

BH_RET ACP_pload_ins_sd(const void* raw_data, unsigned size, ACInsSDPackExt *pack);
BH_RET ACP_pload_uns_sd(const void* raw_data, unsigned size, ACUnsSDPackExt *pack);
BH_RET ACP_pload_ins_jta(const void* raw_data, unsigned size, ACInsJTAPackExt *pack);
BH_RET ACP_pload_ins_nta(const void* raw_data, unsigned size, ACInsNTAPackExt *pack);
BH_RET ACP_pload_uns_jta(const void* raw_data, unsigned size, ACUnsTAPackExt *pack);
BH_RET ACP_pload_uns_nta(const void* raw_data, unsigned size, ACUnsTAPackExt *pack);
BH_RET ACP_pload_ins_jta_prop(const void* raw_data, unsigned size, ACInsJTAPropExt *pack);
BH_RET ACP_get_cmd_id(const void* raw_data, unsigned size, int* cmd_id);
BH_RET ACP_pload_update_svl(const void *raw_data, unsigned size, ACUpdateSVLPackExt*pack);

#endif
