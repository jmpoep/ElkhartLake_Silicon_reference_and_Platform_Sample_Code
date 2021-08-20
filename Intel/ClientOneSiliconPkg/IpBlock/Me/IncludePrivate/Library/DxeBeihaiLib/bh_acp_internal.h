/** @file
  admin cmd pkg internal functions.

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

#ifndef _BH_ACP_INTERNAL_H
#define _BH_ACP_INTERNAL_H

#include "bh_shared_types.h"
#include "bh_shared_errcode.h"
#include "bh_acp_format.h"

// Intel CSS Header + CSS Cypto Block which prefixes each signed ACP pkg
#define BH_ACP_CSS_HEADER_LENGTH    (128 + 520) // CSS Header + CSS Crypto Block

/*PackReader hold a reference of raw pack and read items with alignment support*/
typedef struct {
    const char *cur;
    const char *head;
    unsigned total;
} PackReader;

BH_RET pr_init(const char *data, unsigned n, PackReader* out);
/*whether pack reader reaches the end of buffer, alignment considered*/
BH_RET pr_is_end(PackReader *pr);
BH_RET ACP_load_pack_head(PackReader *pr, ACPackHeader** head);
BH_RET ACP_load_prop(PackReader *pr, ACProp** props);
BH_RET ACP_load_ins_sd(PackReader *pr, ACInsSDPack* pack);
BH_RET ACP_load_uns_sd(PackReader *pr, ACUnsSDPack* pack);
BH_RET ACP_load_ins_jta(PackReader *pr, ACInsJTAPack* pack);
BH_RET ACP_load_ins_nta(PackReader *pr, ACInsNTAPack* pack);
BH_RET ACP_load_uns_ta(PackReader *pr, ACUnsTAPack* pack);
BH_RET ACP_load_sig(PackReader *pr, ACSig** sig);
BH_RET ACP_load_ta_pack(PackReader *pr, char** ta_pack);
BH_RET ACP_load_ins_jta_prop(PackReader *pr, ACInsJTAProp* pack);
BH_RET ACP_load_update_svl(PackReader* pr, ACUpdateSVLPack* pack);

#endif
