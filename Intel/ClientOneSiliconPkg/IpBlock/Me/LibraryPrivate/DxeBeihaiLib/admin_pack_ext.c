/** @file
  This file implements package file operations.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

#include <Library/DxeBeihaiLib/bh_acp_exp.h>
#include <Library/DxeBeihaiLib/bh_acp_internal.h>

#define BREAKIF(ret)  {if (ret != BH_SUCCESS) break;}

BH_RET ACP_load_pack (const char *raw_pack,  unsigned size, int cmd_id, ACPack *pack)
{
  BH_RET ret = BHE_FAILED;
  PackReader pr = {0};

  if (BH_SUCCESS != pr_init (raw_pack, size, &pr))
    return BHE_INVALID_BPK_FILE;

  if ((cmd_id != AC_INSTALL_JTA_PROP) &&
      BH_SUCCESS != (ret = ACP_load_pack_head (&pr, &(pack->head))))
    return ret;

  if ((cmd_id != AC_INSTALL_JTA_PROP) && ((UINT32) cmd_id != pack->head->cmd_id))
    return BHE_BAD_PARAMETER;

  switch (cmd_id) {
    case AC_INSTALL_SD:
      ret = ACP_load_ins_sd (&pr, &(((ACInsSDPackExt*) pack)->cmd_pack));
      BREAKIF (ret);
      ret = ACP_load_sig (&pr, &(((ACInsSDPackExt*) pack)->sign));
      break;
    case AC_UNINSTALL_SD:
      ret = ACP_load_uns_sd (&pr, &(((ACUnsSDPackExt*) pack)->cmd_pack));
      BREAKIF (ret);
      ret = ACP_load_sig (&pr, &(((ACUnsSDPackExt*) pack)->sign));
      break;
    case AC_INSTALL_JTA:
      ret = ACP_load_ins_jta (&pr, &(((ACInsJTAPackExt*) pack)->cmd_pack));
      BREAKIF (ret);
      ret = ACP_load_sig (&pr, &(((ACInsJTAPackExt*) pack)->sign));
      BREAKIF (ret);
      ret = ACP_load_ta_pack (&pr, &(((ACInsJTAPackExt*) pack)->ta_pack));
      break;
    case AC_INSTALL_NTA:
      ret = ACP_load_ins_nta (&pr, &(((ACInsNTAPackExt*) pack)->cmd_pack));
      BREAKIF (ret);
      ret = ACP_load_sig (&pr, &(((ACInsNTAPackExt*) pack)->sign));
      BREAKIF (ret);
      ret = ACP_load_ta_pack (&pr, &(((ACInsNTAPackExt*) pack)->ta_pack));
      break;
    case AC_UNINSTALL_JTA:
    case AC_UNINSTALL_NTA:
      ret = ACP_load_uns_ta (&pr, &(((ACUnsTAPackExt*) pack)->cmd_pack));
      BREAKIF (ret);
      ret = ACP_load_sig (&pr, &(((ACUnsTAPackExt*) pack)->sign));
      break;
    case AC_INSTALL_JTA_PROP:
      ret = ACP_load_ins_jta_prop (&pr, &(((ACInsJTAPropExt*) pack)->cmd_pack));
      BREAKIF (ret);
      //Note: the next section is JEFF file, and not ta_pack(JTA_properties+JEFF file),
      //  but we could reuse the ACP_load_ta_pack() here.
      ret = ACP_load_ta_pack (&pr, &(((ACInsJTAPropExt*) pack)->jeff_pack));
      break;
    case AC_UPDATE_SVL:
      ret = ACP_load_update_svl (&pr, &(((ACUpdateSVLPackExt*) pack)->cmd_pack));
      BREAKIF (ret);
      ret = ACP_load_sig (&pr, &(((ACUpdateSVLPackExt*) pack)->sign));
      break;
    default:
      return BHE_BAD_PARAMETER;
  }
  if (BH_SUCCESS != pr_is_end (&pr))
    return BHE_INVALID_BPK_FILE;
  return ret;
}

BH_RET ACP_pload_ins_sd (const void *raw_data, unsigned size, ACInsSDPackExt *pack)
{
  if (NULL == raw_data || size <= BH_ACP_CSS_HEADER_LENGTH || NULL == pack)
    return BHE_BAD_PARAMETER;
  return ACP_load_pack ((char*) raw_data + BH_ACP_CSS_HEADER_LENGTH,
           size - BH_ACP_CSS_HEADER_LENGTH, AC_INSTALL_SD, (ACPack*) pack);
}

BH_RET ACP_pload_uns_sd (const void *raw_data, unsigned size, ACUnsSDPackExt *pack)
{
  if (NULL == raw_data || size <= BH_ACP_CSS_HEADER_LENGTH || NULL == pack)
    return BHE_BAD_PARAMETER;
  return ACP_load_pack ((char*) raw_data + BH_ACP_CSS_HEADER_LENGTH,
           size - BH_ACP_CSS_HEADER_LENGTH, AC_UNINSTALL_SD, (ACPack*) pack);
}

BH_RET ACP_pload_ins_jta (const void *raw_data, unsigned size, ACInsJTAPackExt *pack)
{
  if (NULL == raw_data || size <= BH_ACP_CSS_HEADER_LENGTH || NULL == pack)
    return BHE_BAD_PARAMETER;
  return ACP_load_pack ((char*) raw_data + BH_ACP_CSS_HEADER_LENGTH,
           size - BH_ACP_CSS_HEADER_LENGTH, AC_INSTALL_JTA, (ACPack*) pack);
}

BH_RET ACP_pload_ins_nta (const void *raw_data, unsigned size, ACInsNTAPackExt *pack)
{
  if (NULL == raw_data || size <= BH_ACP_CSS_HEADER_LENGTH || NULL == pack)
    return BHE_BAD_PARAMETER;
  return ACP_load_pack ((char*) raw_data + BH_ACP_CSS_HEADER_LENGTH,
           size - BH_ACP_CSS_HEADER_LENGTH, AC_INSTALL_NTA, (ACPack*) pack);
}

BH_RET ACP_pload_uns_jta (const void *raw_data, unsigned size, ACUnsTAPackExt *pack)
{
  if (NULL == raw_data || size <= BH_ACP_CSS_HEADER_LENGTH || NULL == pack)
    return BHE_BAD_PARAMETER;
  return ACP_load_pack ((char*) raw_data + BH_ACP_CSS_HEADER_LENGTH,
           size - BH_ACP_CSS_HEADER_LENGTH, AC_UNINSTALL_JTA, (ACPack*) pack);
}

BH_RET ACP_pload_uns_nta (const void *raw_data, unsigned size, ACUnsTAPackExt *pack)
{
  if (NULL == raw_data || size <= BH_ACP_CSS_HEADER_LENGTH || NULL == pack)
    return BHE_BAD_PARAMETER;
  return ACP_load_pack ((char*) raw_data + BH_ACP_CSS_HEADER_LENGTH,
           size - BH_ACP_CSS_HEADER_LENGTH, AC_UNINSTALL_NTA, (ACPack*) pack);
}

BH_RET ACP_pload_ins_jta_prop (const void *raw_data, unsigned size, ACInsJTAPropExt *pack)
{
  if (NULL == raw_data || NULL == pack)
    return BHE_BAD_PARAMETER;
  return ACP_load_pack ((char*) raw_data, size, AC_INSTALL_JTA_PROP, (ACPack*) pack);
}

BH_RET ACP_pload_update_svl (const void *raw_data, unsigned size, ACUpdateSVLPackExt *pack)
{
  if (NULL == raw_data || size <= BH_ACP_CSS_HEADER_LENGTH || NULL == pack)
    return BHE_BAD_PARAMETER;
  return ACP_load_pack ((char*) raw_data + BH_ACP_CSS_HEADER_LENGTH,
           size - BH_ACP_CSS_HEADER_LENGTH, AC_UPDATE_SVL, (ACPack*) pack);
}

BH_RET ACP_get_cmd_id (const void *raw_data, unsigned size, int* cmd_id)
{
  BH_RET ret = BH_SUCCESS;
    PackReader pr = {0};
  ACPackHeader *ph = 0;

  if (NULL == raw_data || size <= BH_ACP_CSS_HEADER_LENGTH || NULL == cmd_id)
    return BHE_BAD_PARAMETER;

  *cmd_id = AC_CMD_INVALID;
  if (BH_SUCCESS != pr_init ((char*) raw_data+BH_ACP_CSS_HEADER_LENGTH, size-BH_ACP_CSS_HEADER_LENGTH, &pr))
    return BHE_INVALID_BPK_FILE;
  if (BH_SUCCESS != (ret = ACP_load_pack_head (&pr, &ph)))
    return ret;
  *cmd_id = (*ph).cmd_id;
  return BH_SUCCESS;
}
