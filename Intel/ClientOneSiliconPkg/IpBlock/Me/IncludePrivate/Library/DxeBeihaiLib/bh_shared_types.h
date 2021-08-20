/** @file
  This file declares the shared type definition across Beihai different
  components(host and firmware), so it should be cross-platform.

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

#ifndef __BH_SHARED_TYPES_H
#define __BH_SHARED_TYPES_H

typedef INT8                  BH_I8;
typedef UINT8                 BH_U8;
typedef INT16                 BH_I16;
typedef UINT16                BH_U16;
typedef INT32                 BH_I32;
typedef UINT32                BH_U32;
typedef INT64                 BH_I64;
typedef UINT64                BH_U64;

typedef BH_U64                BH_GROUP;
#define BH_GUID_LENGTH        16
#define BH_MAX_PACK_HASH_LEN  32

typedef struct {
  BH_U8 data[BH_MAX_PACK_HASH_LEN];
} BH_PACK_HASH;

typedef struct {
  BH_U8 data[BH_GUID_LENGTH];
} BH_TAID;
#define BH_TAID_LEN sizeof(BH_TAID)

typedef struct {
  BH_U8 data[BH_GUID_LENGTH];
} BH_SDID;

#define BH_SDID_LEN sizeof(BH_SDID)

#ifdef _MSC_VER
#pragma warning (disable:4200)
#endif

/*
Firmware properties are formatted as "type\0key\0value\0"
Example: "string\0name\0Tom\0int\0Age\013\0"
*/
struct _bh_ta_install_condition_list_t { //same as BH_PROP_LIST, and needs discussion with CSG
  BH_U32 num;
  BH_U32 len;
  BH_I8 data[0];
};


#endif

