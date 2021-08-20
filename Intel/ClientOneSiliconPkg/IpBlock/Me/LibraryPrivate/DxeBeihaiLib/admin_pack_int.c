/** @file
  This file implements ACP file operations.

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

#include <Library/DxeBeihaiLib/bh_shared_errcode.h>
#include <Library/DxeBeihaiLib/bh_acp_format.h>
#include <Library/DxeBeihaiLib/bh_acp_exp.h>
#include <Library/DxeBeihaiLib/bh_acp_internal.h>

#define PR_ALIGN 4
#define PR_ALIGN_MASK (PR_ALIGN - 1)
#ifndef UINT_MAX
#define UINT_MAX (UINTN)(-1)
#endif

#ifdef __GNUC__
#pragma GCC diagnostic warning "-Wunused-function"
#endif

BH_RET pr_init (const char *data, unsigned n, PackReader* out)
{
  //check integer overflow
  if ((UINTN) data > UINT_MAX - n)
    return BHE_INVALID_BPK_FILE;

  out->cur = out->head = data;
  out->total = n;
  return BH_SUCCESS;
}

static BH_RET pr_8b_align_move (PackReader* pr, UINTN n_move)
{
  unsigned offset = 0;
  UINTN new_cur = (UINTN) pr->cur + n_move;
  UINTN len_from_head = new_cur - (UINTN) pr->head;

  if ((UINTN) pr->cur > UINT_MAX - n_move || new_cur < (UINTN) pr->head)
    return BHE_INVALID_BPK_FILE;
  offset = ((8 - (len_from_head & 7)) & 7);
  if (new_cur > UINT_MAX - offset) return BHE_INVALID_BPK_FILE;
  new_cur = new_cur + offset;
  if (new_cur > (UINTN) pr->head + pr->total)
    return BHE_INVALID_BPK_FILE;
  pr->cur = (char*) new_cur;
  return BH_SUCCESS;
}

static BH_RET pr_align_move (PackReader* pr, UINTN n_move)
{
  UINTN new_cur = (UINTN) pr->cur + n_move;
  UINTN len_from_head = new_cur - (UINTN) pr->head;
  UINTN offset = 0;

  if ((UINTN) pr->cur > UINT_MAX - n_move || new_cur < (UINTN) pr->head)
    return BHE_INVALID_BPK_FILE;
  offset = ((PR_ALIGN - (len_from_head & PR_ALIGN_MASK)) & PR_ALIGN_MASK);
  if (new_cur > UINT_MAX - offset) return BHE_INVALID_BPK_FILE;
  new_cur = new_cur + offset;
  if (new_cur > (UINTN) pr->head + pr->total)
    return BHE_INVALID_BPK_FILE;
  pr->cur = (char*) new_cur;
  return BH_SUCCESS;
}

static BH_RET pr_move (PackReader* pr, UINTN n_move)
{
  UINTN new_cur = (UINTN) pr->cur + n_move;

  if ((UINTN) pr->cur > UINT_MAX - n_move ||
      new_cur > (UINTN)pr->head + pr->total)  //integer overflow or out of acp pkg size
    return BHE_INVALID_BPK_FILE;
  pr->cur = (char*) new_cur;
  return BH_SUCCESS;
}

static int pr_is_safe_to_read (const PackReader* pr, UINTN n_move)
{
  if ((UINTN)pr->cur > UINT_MAX - n_move) //integer overflow
    return BHE_INVALID_BPK_FILE;

  if ((UINTN) pr->cur + n_move > (UINTN) pr->head + pr->total)
    return BHE_INVALID_BPK_FILE;
  return BH_SUCCESS;
}

BH_RET pr_is_end (PackReader* pr)
{
  if ((UINTN) pr->cur == (UINTN) pr->head + pr->total)
    return BH_SUCCESS;
  else
  return BHE_INVALID_BPK_FILE;
}

static BH_RET ACP_load_ins_sd_head (PackReader* pr, ACInsSDHeader **head)
{
  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACInsSDHeader))) {
    *head = (ACInsSDHeader*) (pr->cur);
    return pr_align_move (pr, sizeof (ACInsSDHeader));
  }
  return BHE_INVALID_BPK_FILE;
}

static BH_RET ACP_load_ins_sd_sig (PackReader* pr, ACInsSDSigKey **sig)
{
    /*check buffer border before read the value to avoid access violation*/
  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACInsSDSigKey))) {
    *sig = (ACInsSDSigKey*) pr->cur;
    return pr_align_move (pr, sizeof (ACInsSDSigKey));
  }
  return BHE_INVALID_BPK_FILE;
}


static BH_RET ACP_load_sdid (PackReader* pr, BH_SDID** pp_sdid)
{
  if (BH_SUCCESS == pr_is_safe_to_read (pr, BH_SDID_LEN)) {
    *pp_sdid = (BH_SDID*) pr->cur;
    return pr_align_move (pr, BH_SDID_LEN);
  }
  return BHE_INVALID_BPK_FILE;
}

static BH_RET ACP_load_taid (PackReader* pr, BH_TAID** pp_taid)
{
  if (BH_SUCCESS == pr_is_safe_to_read (pr, BH_TAID_LEN)) {
    *pp_taid = (BH_TAID*) pr->cur;
    return pr_align_move (pr, BH_TAID_LEN);
  }
  return BHE_INVALID_BPK_FILE;
}

static BH_RET ACP_load_metadata (PackReader* pr, ACInsMetadata **metadata)
{
  UINTN len = 0;

  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACInsMetadata))) {
    *metadata = (ACInsMetadata*) (pr->cur);
    if ((*metadata)->len > BH_MAX_ACP_NTA_METADATA_LENGTH)
      return BHE_INVALID_BPK_FILE;

    len = sizeof (ACInsMetadata) + (*metadata)->len * sizeof ((*metadata)->data[0]);

    if (BH_SUCCESS == pr_is_safe_to_read (pr, len)) {
      return pr_align_move (pr, len);
    }
  }
  return BHE_INVALID_BPK_FILE;
}

static BH_RET ACP_load_reasons (PackReader* pr, ACInsReasons **reasons)
{
  UINTN len = 0;

  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACInsReasons))) {
    *reasons = (ACInsReasons*) (pr->cur);
    if ((*reasons)->len > BH_MAX_ACP_INS_REASONS_LENGTH)
      return BHE_INVALID_BPK_FILE;
    len = sizeof (ACInsReasons) + (*reasons)->len * sizeof ((*reasons)->data[0]);
    if (BH_SUCCESS == pr_is_safe_to_read (pr, len)) {
      return pr_align_move (pr, len);
    }
  }
  return BHE_INVALID_BPK_FILE;
}

BH_RET ACP_load_taid_list (PackReader* pr, ACTAIDList **taid_list)
{
  UINTN len = 0;

  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACTAIDList))) {
    *taid_list = (ACTAIDList*) (pr->cur);
    if ((*taid_list)->num > BH_MAX_ACP_USED_SERVICES)
      return BHE_INVALID_BPK_FILE;

    len = sizeof (ACTAIDList) + (*taid_list)->num * sizeof ((*taid_list)->list[0]);

    if (BH_SUCCESS == pr_is_safe_to_read (pr, len)) {
      return pr_align_move (pr, len);
    }
  }
  return BHE_INVALID_BPK_FILE;
}

BH_RET ACP_load_svl (PackReader* pr, ACSVList **svl)
{
  UINTN len = 0;

  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACSVList))) {
    *svl = (ACSVList*) (pr->cur);
    if ((*svl)->num > BH_MAX_ACP_SVL_RECORDS)
      return BHE_INVALID_BPK_FILE;

    len = sizeof (ACSVList) + (*svl)->num * sizeof ((*svl)->data[0]);

    if (BH_SUCCESS == pr_is_safe_to_read (pr, len)) {
      return pr_align_move (pr, len);
    }
  }
  return BHE_INVALID_BPK_FILE;
}

BH_RET ACP_load_prop (PackReader* pr, ACProp **prop)
{
  UINTN len = 0;

  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACProp))) {
    *prop = (ACProp*) (pr->cur);
    if ((*prop)->len > BH_MAX_ACP_PORPS_LENGTH)
      return BHE_INVALID_BPK_FILE;

    len = sizeof (ACProp) + (*prop)->len * sizeof ((*prop)->data[0]);

    if (BH_SUCCESS == pr_is_safe_to_read (pr, len)) {
      return pr_align_move (pr, len);
    }
  }
  return BHE_INVALID_BPK_FILE;
}

BH_RET ACP_load_ta_pack (PackReader* pr, char **ta_pack)
{
  UINTN len = 0;

    /*8 byte align to obey jeff rule*/
  if (BH_SUCCESS == pr_8b_align_move (pr, 0)) {
    *ta_pack = (char*) (pr->cur);

        /*assume ta pack is the last item of one package,
           move cursor to the end directly*/
    if ((UINTN) pr->cur > (UINTN) pr->head + pr->total)
      return BHE_INVALID_BPK_FILE;
    len = (UINTN) pr->head + pr->total - (UINTN) pr->cur;
    if (BH_SUCCESS == pr_is_safe_to_read (pr, len)) {
      return pr_move (pr, len);
    }
  }
  return BHE_INVALID_BPK_FILE;
}

BH_RET ACP_load_sig (PackReader* pr, ACSig **sig)
{
  return pr_align_move (pr, 0);
}

BH_RET ACP_load_ins_sd (PackReader* pr, ACInsSDPack* pack)
{
  BH_RET ret = BHE_INVALID_BPK_FILE;
  if ((BH_SUCCESS != (ret = ACP_load_prop (pr, &(pack->ins_cond))))
      || (BH_SUCCESS != (ret = ACP_load_ins_sd_head (pr, &(pack->head))))
      || (BH_SUCCESS != (ret = ACP_load_ins_sd_sig (pr, &(pack->sig_key)))))
    return ret;
  return BH_SUCCESS;
}

BH_RET ACP_load_uns_sd (PackReader* pr, ACUnsSDPack* pack)
{
  return ACP_load_sdid (pr, &(pack->p_sdid));
}

static BH_RET ACP_load_ins_jta_prop_head (PackReader* pr, ACInsJTAPropHeader **head)
{
  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACInsJTAPropHeader))) {
    *head = (ACInsJTAPropHeader*) (pr->cur);
    return pr_align_move (pr, sizeof (ACInsJTAPropHeader));
  }
  return BHE_INVALID_BPK_FILE;
}

BH_RET ACP_load_ins_jta_prop (PackReader* pr, ACInsJTAProp* pack)
{
  BH_RET ret = BHE_INVALID_BPK_FILE;
  if ((BH_SUCCESS != (ret = ACP_load_ins_jta_prop_head (pr, &(pack->head))))
      || (BH_SUCCESS != (ret = ACP_load_reasons (pr, &(pack->post_reasons))))
      || (BH_SUCCESS != (ret = ACP_load_reasons (pr, &(pack->reg_reasons))))
      || (BH_SUCCESS != (ret = ACP_load_prop (pr, &(pack->prop)))
          || (BH_SUCCESS != (ret = ACP_load_taid_list (pr, &(pack->used_service_list)))))
      )
    return ret;
  return BH_SUCCESS;
}

static BH_RET ACP_load_ins_jta_head (PackReader* pr, ACInsJTAHeader **head)
{
  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACInsJTAHeader))) {
    *head = (ACInsJTAHeader*) (pr->cur);
    return pr_align_move (pr, sizeof (ACInsJTAHeader));
  }
  return BHE_INVALID_BPK_FILE;
}

BH_RET ACP_load_ins_jta (PackReader* pr, ACInsJTAPack* pack)
{
  BH_RET ret = BHE_INVALID_BPK_FILE;
  if ((BH_SUCCESS != (ret = ACP_load_prop (pr, &(pack->ins_cond))))
      || (BH_SUCCESS != (ret = ACP_load_ins_jta_head (pr, &(pack->head)))))
    return ret;
  return BH_SUCCESS;
}

static BH_RET ACP_load_ins_nta_head (PackReader* pr, ACInsNTAHeader **head)
{
  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACInsNTAHeader))) {
    *head = (ACInsNTAHeader*) (pr->cur);
    return pr_align_move (pr, sizeof (ACInsNTAHeader));
  }
  return BHE_INVALID_BPK_FILE;
}

BH_RET ACP_load_ins_nta (PackReader* pr, ACInsNTAPack* pack)
{
  BH_RET ret = BHE_INVALID_BPK_FILE;
  if ((BH_SUCCESS != (ret = ACP_load_prop (pr, &(pack->ins_cond))))
      || (BH_SUCCESS != (ret = ACP_load_ins_nta_head (pr, &(pack->head))))
      || (BH_SUCCESS != (ret = ACP_load_metadata (pr, &(pack->mdata)))))
    return ret;
  return BH_SUCCESS;
}

BH_RET ACP_load_uns_ta (PackReader* pr, ACUnsTAPack* pack)
{
  return ACP_load_taid (pr, &(pack->p_taid));
}

BH_RET ACP_load_update_svl (PackReader* pr, ACUpdateSVLPack* pack)
{
  BH_RET ret = BHE_INVALID_BPK_FILE;
  if ((BH_SUCCESS != (ret = ACP_load_prop (pr, &(pack->ins_cond))))
      || (BH_SUCCESS != (ret = ACP_load_svl (pr, &(pack->sv_list)))))
    return ret;
  return BH_SUCCESS;
}

/*
  static BH_RET ACP_load_pack_sig(PackReader* pr, ACSig **sig)
  {
  *sig = (ACSig*)pr->cur;
  if ((*sig)->sig_alg >= SIG_ALG_NUM)
  return BHE_BAD_PARAMETER;
  pr_align_move(pr, sizeof(ACSig) + SIG_KEY_LEN[(*sig)->sig_alg]);
  return BH_SUCCESS;
  }
*/

/*
  static BH_RET ACP_load_pack_data(PackReader* pr, BH_U32 cmd_id,
  char **data)
  {
  switch(cmd_id) {
  case AC_INSTALL_SD:
  *data = (char*)malloc(sizeof(ACInsSDPack));
  ACP_load_ins_sd(pr, (ACInsSDPack*)(*data));
  break;
  case AC_UNINSTALL_SD:
  *data = (char*)malloc(sizeof(ACUnsSDPack));
  ACP_load_uns_sd(pr, (ACUnsSDPack*)(*data));
  break;
  case AC_INSTALL_JTA:
  *data = (char*)malloc(sizeof(ACInsJTAPack));
  ACP_load_ins_jta(pr, (ACInsJTAPack*)(*data));
  break;
  case AC_INSTALL_NTA:
  *data = (char*)malloc(sizeof(ACInsNTAPack));
  ACP_load_ins_nta(pr, (ACInsNTAPack*)(*data));
  break;
  case AC_UNINSTALL_TA:
  *data = (char*)malloc(sizeof(ACUnsTAPack));
  ACP_load_uns_ta(pr, (ACUnsTAPack*)(*data));
  break;
  default:
  return BHE_BAD_PARAMETER;
  }
  return BH_SUCCESS;
  }
*/

BH_RET ACP_load_pack_head (PackReader* pr, ACPackHeader **head)
{
  if (BH_SUCCESS == pr_is_safe_to_read (pr, sizeof (ACPackHeader))) {
    *head = (ACPackHeader*) (pr->cur);
    return pr_align_move (pr, sizeof (ACPackHeader));
  }
  return BHE_INVALID_BPK_FILE;
}

/*
  static BH_RET ACP_load_pack_enc(PackReader* pr, ACEncryption **enc)
  {
  *enc = (ACEncryption*)(pr->cur);
  pr_align_move(pr, sizeof(ACEncryption) + (*enc)->len);
  return BH_SUCCESS;
  }
*/
#ifdef BPKT_UNIT_TEST
/*for debugging purpose*/

BH_RET ACP_load_pack (char *raw_pack,  unsigned size, int cmd_id, ACPack *pack);
void dump_pack (ACPack *pack);

void load_and_dump (const char *fname)
{
  FILE *fp = fopen (fname, "rb");
  unsigned n_read;
  long sz;
  char *buf;
  ACInsSDPackExt p1;
  ACUnsSDPackExt p2;
  ACInsJTAPackExt p3;
  ACUnsTAPackExt p4;
  ACInsNTAPackExt p5;
  ACUnsTAPackExt p6;
  ACInsJTAPropExt p7;
  ACUpdateSVLPackExt p8;
  BH_RET ret;
  int cmd_id = fname[0] - '0';

  fseek (fp, 0L, SEEK_END);
  sz = ftell (fp);
  fseek (fp, 0L, SEEK_SET);
  buf = malloc (sz);
  n_read = fread (buf, 1, sz, fp);
  switch (cmd_id) {
    case AC_INSTALL_SD: {
        ret = ACP_pload_ins_sd (buf, n_read, &p1);
        dump_pack ((ACPack*)&p1);
        break;
      }
    case AC_UNINSTALL_SD: {
        ret = ACP_pload_uns_sd (buf, n_read, &p2);
        dump_pack ((ACPack*)&p2);
        break;
      }
    case AC_INSTALL_JTA: {
        ret = ACP_pload_ins_jta (buf, n_read, &p3);
        dump_pack ((ACPack*)&p3);
        break;
      }
    case AC_UNINSTALL_JTA: {
        ret = ACP_pload_uns_jta (buf, n_read, &p4);
        dump_pack ((ACPack*)&p4);
        break;
      }
    case AC_INSTALL_NTA: {
        ret = ACP_pload_ins_nta (buf, n_read, &p5);
        dump_pack ((ACPack*)&p5);
        break;
      }
    case AC_UNINSTALL_NTA: {
        ret = ACP_pload_uns_nta (buf, n_read, &p6);
        dump_pack ((ACPack*)&p6);
        break;
      }
    case AC_INSTALL_JTA_PROP: {
        ret = ACP_pload_ins_jta_prop (buf, n_read, &p7);
        printf ("---------------------------\n");
        dump_ins_jta_prop (&(p7.cmd_pack));
        dump_binary ("jeff_binary", 4, p7.jeff_pack);
        break;
      }
    case AC_UPDATE_SVL: {
        ret = ACP_pload_update_svl (buf, n_read, &p8);
        printf ("---------------------------\n");
        dump_pack ((ACPack*) &p8);
        break;
      }
    default: {
        printf ("illegal cmd id %d\n", cmd_id);
        ret = BHE_BAD_PARAMETER;
        break;
      }
  }
  fclose (fp);
  if (ret != BH_SUCCESS)
    abort ();
}
#ifdef BH_TEST
int main (int argc, const char *argv[])
{
  char ch;

  system ("del 1.out 2.out 3.out 4.out 5.out 6.out 7.out 8.out");
  system ("bpkt_exe.exe 1 TEMPLATE_AC_INSTALL_SD.xml 1.out 00000000-0000-0000-0000-000000000001");
  system ("bpkt_exe.exe 2 TEMPLATE_AC_UNINSTALL_SD.xml 2.out 00000000-0000-0000-0000-000000000002");
  system ("bpkt_exe.exe 4 TEMPLATE_AC_UNINSTALL_JTA.xml 4.out 00000000-0000-0000-0000-000000000003");
  system ("bpkt_exe.exe 5 TEMPLATE_AC_INSTALL_NTA.xml  5.out 00000000-0000-0000-0000-000000000003 a.out a.met");
  system ("bpkt_exe.exe 6 TEMPLATE_AC_UNINSTALL_NTA.xml 6.out 00000000-0000-0000-0000-000000000003");
  system ("bpkt_exe.exe 8 TEMPLATE_AC_INSTALL_JTA_PROP.xml 8.out a.jeff");
  system ("bpkt_exe.exe 3 TEMPLATE_AC_INSTALL_JTA.xml 3.out 00000000-0000-0000-0000-000000000004 8.out");
  system ("bpkt_exe.exe 7 TEMPLATE_AC_UPDATE_SVL.xml 7.out 00000000-0000-0000-0000-000000000003");

  load_and_dump ("1.out");
  load_and_dump ("2.out");
  load_and_dump ("3.out");
  load_and_dump ("4.out");
  load_and_dump ("5.out");
  load_and_dump ("6.out");
  load_and_dump ("7.out");
  load_and_dump ("8.out");
  printf ("-------------\nSucc\n");

  scanf ("%c", &ch);
  return 0;
}
#else
int main (int argc, const char *argv[])
{
  char ch;
  system ("del 1.out 2.out 3.out 4.out 5.out 6.out 7.out 8.out");
  system ("bpkt_exe.exe 1 TEMPLATE_AC_INSTALL_SD.xml 1.out");
  system ("bpkt_exe.exe 2 TEMPLATE_AC_UNINSTALL_SD.xml 2.out");
  system ("bpkt_exe.exe 4 TEMPLATE_AC_UNINSTALL_JTA.xml 4.out");
  system ("bpkt_exe.exe 5 TEMPLATE_AC_INSTALL_NTA.xml  5.out a.met");
  system ("bpkt_exe.exe 6 TEMPLATE_AC_UNINSTALL_NTA.xml 6.out");
  system ("bpkt_exe.exe 8 TEMPLATE_AC_INSTALL_JTA_PROP.xml 8.out");
  system ("bpkt_exe.exe 7 TEMPLATE_AC_UPDATE_SVL.xml 7.out");
  system ("bpkt_exe.exe 3 TEMPLATE_AC_INSTALL_JTA.xml 3.out");

  load_and_dump ("1.out");
  load_and_dump ("2.out");
  load_and_dump ("3.out");
  load_and_dump ("4.out");
  load_and_dump ("5.out");
  load_and_dump ("6.out");
  load_and_dump ("7.out");
  load_and_dump ("8.out");
  printf ("-------------\nSucc\n");

  scanf ("%c", &ch);
  return 0;
}
#endif

#endif
