/** @file
  This file implements Beihai Host Proxy (BHP) module TA management API.

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

#include <Base.h>
#include <Uefi.h>
#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>

#include <Library/DxeJhiSupportLib.h>
#include <JhiInternal.h>
#include <Library/DxeBeihaiLib/BeihaiPlugin.h>


static BH_RET bh_get_cmdtype_by_cmd_pkg (const char* cmd_pkg, unsigned int pkg_len, int* cmd_type)
{
  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;
  if (cmd_type == NULL) return BPE_INVALID_PARAMS;
  return ACP_get_cmd_id (cmd_pkg, pkg_len, cmd_type);
}

static BH_RET bh_get_tainfo_by_cmd_pkg_installjta (const char* cmd_pkg, unsigned int pkg_len, BH_TAID* ta_id, unsigned int* ta_pkg_offset)
{
  BH_RET ret = BPE_INVALID_PARAMS;
  ACInsJTAPackExt pack;

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;
  if (ta_pkg_offset == NULL) return BPE_INVALID_PARAMS;
  ret = ACP_pload_ins_jta (cmd_pkg, pkg_len, &pack);
  if (ret == BH_SUCCESS) {
    *ta_id = pack.cmd_pack.head->ta_id;
    *ta_pkg_offset = (unsigned int) (UINTN) pack.ta_pack - (unsigned int) (UINTN) cmd_pkg;
  }
  return ret;
}

static BH_RET bh_get_tainfo_by_cmd_pkg_uninstalljta (const char* cmd_pkg, unsigned int pkg_len, BH_TAID* ta_id)
{
  BH_RET ret = BPE_INVALID_PARAMS;
  ACUnsTAPackExt pack;

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;
  ret = ACP_pload_uns_jta (cmd_pkg, pkg_len, &pack);
  if (ret == BH_SUCCESS) {
    *ta_id = *pack.cmd_pack.p_taid;
  }
  return ret;
}

static BH_RET bh_do_uninstall_jta (const SD_SESSION_HANDLE handle, const char* cmd_pkg, unsigned int pkg_len)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_uninstall_javata_cmd* cmd = (bhp_uninstall_javata_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_U64 seq = (BH_U64) handle;
  BH_RET ret = BH_SUCCESS;
  BH_TAID ta_id;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (cmd_pkg == NULL || pkg_len ==0) return BPE_INVALID_PARAMS;

  ret = bh_get_tainfo_by_cmd_pkg_uninstalljta (cmd_pkg, pkg_len, &ta_id);
  if (ret != BH_SUCCESS) return ret;
  {
    //Check with VM whether the TA has live session or not
    char ta_id_string[BH_GUID_LENGTH *2 +1];
    unsigned int session_count = 0;
    JAVATA_SESSION_HANDLE* handles = NULL;

    AsciiUuid2Str ((UINT8 *)&ta_id, ta_id_string);
    ret = BHP_ListTASessions (ta_id_string, &session_count, &handles);
    if (handles) BHP_Free (handles);
    if (ret == BH_SUCCESS && session_count > 0) return BHE_EXIST_LIVE_SESSION;
  }

  //send uninstall cmd to SDM
  rr = session_enter (CONN_IDX_SDM, seq, 1);
  if (!rr) {
    return BPE_INVALID_PARAMS;
  }

  rr->buffer = NULL;
  h->id = BHP_CMD_UNINSTALL_JAVATA;

  cmd->sd_session_id = rr->addr;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_do_uninstall_jta %x\n", rr));

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), cmd_pkg, pkg_len, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_do_uninstall_jta %x ret %x\n", rr, rr->code));

  if (rr->killed) {
    ret = BHE_UNCAUGHT_EXCEPTION;
  }

  if (rr->buffer) {
    BHFREE (rr->buffer);
    rr->buffer = NULL;
  }

  session_exit (CONN_IDX_SDM, rr, seq, 1);

  return ret;
}

/*
 *
 * This function is inside sd-session-lock
 */
static BH_RET bh_proxy_installjavata (SD_SESSION_HANDLE handle, bh_response_record* rr, const char* cmd_pkg, unsigned int cmd_pkg_len)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_install_javata_cmd* cmd = (bhp_install_javata_cmd*) h->cmd;
  BH_RET ret = BH_SUCCESS;
  BH_U64 seq = (BH_U64) handle;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (cmd_pkg == NULL || cmd_pkg_len == 0) return BPE_INVALID_PARAMS;
  if (rr == NULL) return BPE_INVALID_PARAMS;

  rr->buffer = NULL;
  h->id = BHP_CMD_INSTALL_JAVATA;

  cmd->sd_session_id = rr->addr;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_installjavata %x\n", rr));

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), cmd_pkg, cmd_pkg_len, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_installjavata %x ret %x\n", rr, rr->code));

  if (rr->killed) {
    ret = BHE_UNCAUGHT_EXCEPTION;
  }
  if (rr->buffer) {
    BHFREE (rr->buffer);
    rr->buffer = NULL;
  }
  return ret;
}

/*
 *
 * This function is inside sd-session-lock
 */
static BH_RET bh_proxy_verifyjavata (int conn_idx, BH_TAID ta_id, const char* ta_pkg, unsigned int ta_pkg_len)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_verify_javata_cmd *cmd = (bhp_verify_javata_cmd*) h->cmd;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (ta_pkg == NULL || ta_pkg_len == 0) return BPE_INVALID_PARAMS;

  h->id = BHP_CMD_VERIFY_JAVATA;
  cmd->appid = ta_id;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_verifyjavata %x\n", &rr));

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), ta_pkg, ta_pkg_len, rrmap_add (conn_idx, &rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_verifyjavata %x ret %x\n", &rr, rr.code));

  if (rr.buffer) BHFREE (rr.buffer);

  return ret;
}

static BH_RET bh_do_install_jta (const SD_SESSION_HANDLE handle, const char* cmd_pkg, unsigned int pkg_len)
{
  bh_response_record* rr = NULL;
  BH_RET ret = BH_SUCCESS;
  unsigned int ta_pkg_offset = 0;
  const char* ta_pkg = NULL;
  BH_TAID ta_id;
  BH_U64 seq = (BH_U64) handle;

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;

  if (bh_get_tainfo_by_cmd_pkg_installjta (cmd_pkg,pkg_len,&ta_id,&ta_pkg_offset) != BH_SUCCESS) return BPE_INVALID_PARAMS;
  ta_pkg = (cmd_pkg +ta_pkg_offset);

  rr = session_enter (CONN_IDX_SDM, seq, 1);
  if (!rr) return BPE_INVALID_PARAMS;

  //first step: send installjta cmd to sdm
  ret = bh_proxy_installjavata (handle, rr, cmd_pkg, ta_pkg_offset);
  if (ret != BH_SUCCESS) {
    goto cleanup;
  }

  //second step: verifyjavata cmd to IVM
  ret = bh_proxy_verifyjavata (CONN_IDX_IVM, ta_id, ta_pkg, pkg_len - ta_pkg_offset);

cleanup:
  session_exit (CONN_IDX_SDM, rr, seq, 1);

  return ret;
}

#if BEIHAI_ENABLE_SVM
static BH_RET bh_do_install_sd (const SD_SESSION_HANDLE handle, const char* cmd_pkg, unsigned int pkg_len)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_install_sd_cmd *cmd = (bhp_install_sd_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_RET ret = BH_SUCCESS;
  BH_U64 seq = (BH_U64) handle;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;

  rr = session_enter (CONN_IDX_SDM, seq, 1);
  if (!rr) return BPE_INVALID_PARAMS;

  //send installsd cmd to SDM
  h->id = BHP_CMD_INSTALL_SD;
  cmd->sd_session_id = seq;
  rr->buffer = NULL;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_installsd %x\n", &rr));

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), cmd_pkg, pkg_len, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_installsd %x ret %x\n", rr, rr->code));

  if (rr->buffer) {
    BHFREE (rr->buffer);
    rr->buffer = NULL;
  }

  session_exit (CONN_IDX_SDM, rr, seq, 1);

  return ret;
}

static BH_RET bh_proxy_query_sd_status (BH_SDID sd_id)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_query_sd_status_cmd *cmd = (bhp_query_sd_status_cmd*) h->cmd;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  h->id = BHP_CMD_QUERY_SD_STATUS;
  cmd->sdid = sd_id;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_query_sd_status 0x%x\n", &rr));

  ret = bh_cmd_transfer (CONN_IDX_LAUNCHER, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, rrmap_add (CONN_IDX_LAUNCHER, &rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_query_sd_status 0x%x ret %x\n", &rr, rr.code));

  if (rr.buffer) BHFREE (rr.buffer);

  return ret;
}

static BH_RET bh_get_sdinfo_by_cmd_pkg_uninstallsd (const char* cmd_pkg, unsigned int pkg_len, BH_SDID* sd_id)
{
  BH_RET ret = BPE_INVALID_PARAMS;
  ACUnsSDPackExt pack;

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;
  ret = ACP_pload_uns_sd (cmd_pkg, pkg_len, &pack);
  if (ret == BH_SUCCESS) {
    *sd_id = *pack.cmd_pack.p_sdid;
  }
  return ret;
}

static BH_RET bh_do_uninstall_sd (const SD_SESSION_HANDLE handle, const char* cmd_pkg, unsigned int pkg_len)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_uninstall_sd_cmd *cmd = (bhp_uninstall_sd_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_RET ret = BH_SUCCESS;
  BH_U64 seq = (BH_U64) handle;
  BH_SDID sd_id;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;
  if (bh_get_sdinfo_by_cmd_pkg_uninstallsd (cmd_pkg,pkg_len,&sd_id) != BH_SUCCESS) return BPE_INVALID_PARAMS;

  //step1: ask Launcher to query sd running status
  if (bh_proxy_query_sd_status (sd_id) == BH_SUCCESS) {
    //the sd's svm or nta is running, so uninstalling fails.
    return BHE_EXIST_LIVE_SESSION;
  }

  //step2: send uninstallsd cmd to SDM
  rr = session_enter (CONN_IDX_SDM, seq, 1);
  if (!rr) return BPE_INVALID_PARAMS;

  h->id = BHP_CMD_UNINSTALL_SD;
  cmd->sd_session_id = seq;
  rr->buffer = NULL;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_uninstallsd %x\n", rr));

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), cmd_pkg, pkg_len, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_uninstallsd %x ret %x\n", rr, rr->code));

  if (rr->buffer) {
    BHFREE (rr->buffer);
    rr->buffer = NULL;
  }

  session_exit (CONN_IDX_SDM, rr, seq, 1);

  return ret;
}
#endif

#if BEIHAI_ENABLE_NATIVETA
static BH_RET bh_get_tainfo_by_cmd_pkg_installnta (const char* cmd_pkg, unsigned int pkg_len, BH_TAID* ta_id, unsigned int* ta_pkg_offset)
{
  BH_RET ret = BPE_INVALID_PARAMS;
  ACInsNTAPackExt pack;

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;
  if (ta_pkg_offset == NULL) return BPE_INVALID_PARAMS;
  ret = ACP_pload_ins_nta (cmd_pkg, pkg_len, &pack);
  if (ret == BH_SUCCESS) {
    *ta_id = pack.cmd_pack.head->ta_id;
    *ta_pkg_offset = (unsigned int) (UINTN) pack.ta_pack - (unsigned int) (UINTN) cmd_pkg;
  }
  return ret;
}

static BH_RET bh_do_install_nta (const SD_SESSION_HANDLE handle, const char* cmd_pkg, unsigned int pkg_len)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_install_nativeta_cmd* cmd = (bhp_install_nativeta_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_RET ret = BH_SUCCESS;
  BH_U64 seq = (BH_U64) handle;
  unsigned int ta_pkg_offset = 0;
  BH_TAID ta_id;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;
  if (bh_get_tainfo_by_cmd_pkg_installnta (cmd_pkg,pkg_len,&ta_id,&ta_pkg_offset) != BH_SUCCESS) return BPE_INVALID_PARAMS;

  rr = session_enter (CONN_IDX_SDM, seq, 1);
  if (!rr) return BPE_INVALID_PARAMS;

  rr->buffer = NULL;
  h->id = BHP_CMD_INSTALL_NATIVETA;

  cmd->sd_session_id = seq;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_install_nativeta %x\n", rr));
  //excluding NativeTA package at install time to save lots of RAM requirement for SDM process
  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), cmd_pkg, ta_pkg_offset, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_install_nativeta %x ret %x\n", rr, rr->code));

  if (rr->buffer) {
    BHFREE (rr->buffer);
    rr->buffer = NULL;
  }

  session_exit (CONN_IDX_SDM, rr, seq, 1);

  return ret;
}
#endif

#if BEIHAI_ENABLE_NATIVETA
static BH_RET bh_get_tainfo_by_cmd_pkg_uninstallnta (const char* cmd_pkg, unsigned int pkg_len, BH_TAID* ta_id)
{
  BH_RET ret = BPE_INVALID_PARAMS;
  ACUnsTAPackExt pack;

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;
  ret = ACP_pload_uns_nta (cmd_pkg, pkg_len, &pack);
  if (ret == BH_SUCCESS) {
    *ta_id = *pack.cmd_pack.p_taid;
  }
  return ret;
}

static BH_RET bh_proxy_query_nta_status (BH_TAID ta_id)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_query_nativeta_status_cmd *cmd = (bhp_query_nativeta_status_cmd*) h->cmd;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  h->id = BHP_CMD_QUERY_NATIVETA_STATUS;
  cmd->taid = ta_id;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_query_nta_status 0x%x\n", &rr));

  ret = bh_cmd_transfer (CONN_IDX_LAUNCHER, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, rrmap_add (CONN_IDX_LAUNCHER, &rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_query_nta_status 0x%x ret %x\n", &rr, rr.code));

  if (rr.buffer) BHFREE (rr.buffer);

  return ret;
}

static BH_RET bh_do_uninstall_nta (const SD_SESSION_HANDLE handle, const char* cmd_pkg, unsigned int pkg_len)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_uninstall_nativeta_cmd* cmd = (bhp_uninstall_nativeta_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_RET ret = BH_SUCCESS;
  BH_TAID ta_id;
  BH_U64 seq = (BH_U64) handle;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;

  if (bh_get_tainfo_by_cmd_pkg_uninstallnta (cmd_pkg,pkg_len,&ta_id) != BH_SUCCESS) return BPE_INVALID_PARAMS;

  //step1: ask Launcher to query nativeta running status
  if (bh_proxy_query_nta_status (ta_id) == BH_SUCCESS) {
    //the nta is running, so uninstalling fails.
    return BHE_EXIST_LIVE_SESSION;
  }

  //step2: send UninstallNTA cmd to SDM
  rr = session_enter (CONN_IDX_SDM, seq, 1);
  if (!rr) return BPE_INVALID_PARAMS;

  rr->buffer = NULL;
  h->id = BHP_CMD_UNINSTALL_NATIVETA;

  cmd->sd_session_id = seq;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_uninstall_nativeta %x\n", rr));

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), cmd_pkg, pkg_len, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_uninstall_nativeta %x ret %x\n", rr, rr->code));

  if (rr->buffer) {
    BHFREE (rr->buffer);
    rr->buffer = NULL;
  }

  session_exit (CONN_IDX_SDM, rr, seq, 1);

  return ret;
}
#endif

static BH_RET bh_do_update_svl (const SD_SESSION_HANDLE handle, const char* cmd_pkg, unsigned int pkg_len)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_update_svl_cmd *cmd = (bhp_update_svl_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_RET ret = BH_SUCCESS;
  BH_U64 seq = (BH_U64) handle;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (cmd_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;

  rr = session_enter (CONN_IDX_SDM, seq, 1);
  if (!rr) return BPE_INVALID_PARAMS;

  //send updatesvl cmd to SDM
  h->id = BHP_CMD_UPDATE_SVL;
  cmd->sd_session_id = seq;
  rr->buffer = NULL;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_do_update_svl %x\n", &rr));

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), cmd_pkg, pkg_len, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_do_update_svl %x ret %x\n", rr, rr->code));

  if (rr->buffer) {
    BHFREE (rr->buffer);
    rr->buffer = NULL;
  }

  session_exit (CONN_IDX_SDM, rr, seq, 1);

  return ret;
}

BH_RET BHP_OpenSDSession (const char* SD_ID, SD_SESSION_HANDLE* pSession)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_open_sdsession_cmd* cmd = (bhp_open_sdsession_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_U64 seq;
  BH_RET ret = BH_SUCCESS;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_OpenSDSession <<<\n"));
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "SD_ID: %a\n", SD_ID));

  if (!is_bhp_inited ()) return BPE_NOT_INIT;
  if (SD_ID == NULL || pSession == NULL) return BPE_INVALID_PARAMS;

  if (!AsciiStr2Uuid (SD_ID,(UINT8 *)&cmd->sdid)) return BPE_INVALID_PARAMS;

  rr = (bh_response_record*) BHMALLOC (sizeof (bh_response_record));
  if (!rr) {
    return BPE_OUT_OF_MEMORY;
  }
  ZeroMem (rr, sizeof (bh_response_record));

  rr->count = 1;
  rr->is_session = 1;
  seq = rrmap_add (CONN_IDX_SDM, rr);

  h->id = BHP_CMD_OPEN_SDSESSION;

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) +sizeof (*cmd), NULL, 0, seq);
  if ( ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai BHP_OpenSDSession %x ret %x\n", rr, rr->code));

  if (rr->buffer) {
    BHFREE (rr->buffer);
    rr->buffer = NULL;
  }
  if (ret == BH_SUCCESS) {
    *pSession = (SD_SESSION_HANDLE)  seq;
    session_exit (CONN_IDX_SDM, rr, seq, 0);
  } else {
    session_close (CONN_IDX_SDM, rr, seq, 0);
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_OpenSDSession done, ret: %x\n\n", ret));
  return ret;
}


BH_RET BHP_CloseSDSession (const SD_SESSION_HANDLE handle)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_close_sdsession_cmd* cmd = (bhp_close_sdsession_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_U64 seq = (BH_U64) handle;
  BH_RET ret = BH_SUCCESS;
  int conn_idx = CONN_IDX_SDM;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_CloseSDSession <<<\n"));
  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  rr = session_enter (conn_idx, seq, 1);
  if (!rr) {
    return BPE_INVALID_PARAMS;
  }

  rr->buffer = NULL;

  h->id = BHP_CMD_CLOSE_SDSESSION;
  cmd->sd_session_id = rr->addr;

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai CloseSDSession %x ret %x\n", rr, rr->code));
  if (rr->killed) ret = BHE_UNCAUGHT_EXCEPTION;

  session_close (conn_idx, rr, seq, 1);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_CloseSDSession done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_SendAdminCmdPkg (const SD_SESSION_HANDLE handle, const char* cmd_pkg, unsigned int pkg_len)
{
  BH_RET ret = BPE_INVALID_PARAMS;
  int cmd_type = 0;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_SendAdminCmdPkg <<<\n"));
  if (!is_bhp_inited ()) return BPE_NOT_INIT;
  if (cmd_pkg == NULL || pkg_len == 0) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "cmd_pkg: %x, pkg_len: %x\n", cmd_pkg, pkg_len));
    return BPE_INVALID_PARAMS;
  }

  if (bh_get_cmdtype_by_cmd_pkg (cmd_pkg, pkg_len, &cmd_type) != BH_SUCCESS) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "bh_get_cmdtype_by_cmd_pkg fail\n"));
    return BPE_INVALID_PARAMS;
  }

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "cmd_type: %x\n", cmd_type));
  switch (cmd_type) {
#if BEIHAI_ENABLE_SVM
    case AC_INSTALL_SD:
      ret = bh_do_install_sd (handle, cmd_pkg, pkg_len);
      break;
    case AC_UNINSTALL_SD:
      ret = bh_do_uninstall_sd (handle, cmd_pkg, pkg_len);
      break;
#endif
#if BEIHAI_ENABLE_NATIVETA
    case AC_INSTALL_NTA:
      ret = bh_do_install_nta (handle, cmd_pkg, pkg_len);
      break;
    case AC_UNINSTALL_NTA:
      ret = bh_do_uninstall_nta (handle, cmd_pkg, pkg_len);
      break;
#endif
    case AC_INSTALL_JTA:
      ret = bh_do_install_jta (handle, cmd_pkg, pkg_len);
      break;
    case AC_UNINSTALL_JTA:
      ret = bh_do_uninstall_jta (handle, cmd_pkg, pkg_len);
      break;
    case AC_UPDATE_SVL:
      ret = bh_do_update_svl (handle, cmd_pkg, pkg_len);
      break;
    default:
      ret = BPE_INVALID_PARAMS;
      break;
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_SendAdminCmdPkg done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_ListInstalledSDs (const SD_SESSION_HANDLE handle, unsigned int* count, char*** sdIdStrs)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_list_sd_cmd *cmd = (bhp_list_sd_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_RET ret = BH_SUCCESS;
  BH_U64 seq = (BH_U64) handle;
  char** outbuf = NULL;
  int total_count = 0;
  bhp_list_sd_response* resp;
  int i;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_ListInstalledSDs <<<\n"));
  if (!is_bhp_inited ()) return BPE_NOT_INIT;
  if (count == NULL || sdIdStrs == NULL) return BPE_INVALID_PARAMS;

  rr = session_enter (CONN_IDX_SDM, seq, 1);
  if (!rr) return BPE_INVALID_PARAMS;

  //send listSD cmd to SDM
  h->id = BHP_CMD_LIST_SD;
  cmd->sd_session_id = seq;
  rr->buffer = NULL;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai List SD %x\n", rr));

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai List SD %x ret %x\n", rr, rr->code));

  *count = 0;
  *sdIdStrs = NULL;
  do {
    if (ret != BH_SUCCESS)  break;
    if (rr->buffer == NULL) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }

    resp = (bhp_list_sd_response*) rr->buffer;
    total_count = resp->count;
    if (total_count == 0)  break;

    if (rr->length != sizeof (BH_SDID) * total_count + sizeof (bhp_list_sd_response)) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }
    outbuf = (char**) BHMALLOC (sizeof (char*) * (total_count+1));
    if (!outbuf) {
      ret = BPE_OUT_OF_MEMORY;
      break;
    }
    ZeroMem (outbuf, sizeof (char*) * (total_count+1));

    for (i=0; i< total_count; i++) {
      outbuf[i] = (char*) BHMALLOC (BH_GUID_LENGTH *2 +1);
      if (outbuf[i] == NULL) {
        ret = BPE_OUT_OF_MEMORY;
        break;
      }
      AsciiUuid2Str ((UINT8 *)&resp->sd_ids[i], outbuf[i]);
    }
    if (ret != BH_SUCCESS) break;

    *count  = total_count;
    *sdIdStrs = outbuf;
  } while (0);

  if (ret != BH_SUCCESS) {
    for (i=0; i<total_count; i++) {
      if (outbuf && outbuf[i]) BHFREE (outbuf[i]);
    }
    if (outbuf) BHFREE (outbuf);
  }
  if (rr->buffer) {
    BHFREE (rr->buffer);
    rr->buffer = NULL;
  }

  session_exit (CONN_IDX_SDM, rr, seq, 1);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_ListInstalledSDs done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_ListInstalledTAs (const SD_SESSION_HANDLE handle, const char* SD_ID, unsigned int * count, char*** appIdStrs)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_list_ta_cmd *cmd = (bhp_list_ta_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_RET ret = BH_SUCCESS;
  BH_U64 seq = (BH_U64) handle;
  BH_SDID sdid;
  char** outbuf = NULL;
  int total_count = 0;
  int i;
  bhp_list_ta_response* resp;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_ListInstalledTAs <<<\n"));
  if (!is_bhp_inited ()) return BPE_NOT_INIT;
  if (SD_ID == NULL || count == NULL || appIdStrs == NULL) return BPE_INVALID_PARAMS;
  if (!AsciiStr2Uuid (SD_ID, (UINT8 *)&sdid)) return BPE_INVALID_PARAMS;

  rr = session_enter (CONN_IDX_SDM, seq, 1);
  if (!rr) return BPE_INVALID_PARAMS;

  //send listTA cmd to SDM
  h->id = BHP_CMD_LIST_TA;
  cmd->sd_session_id = seq;
  cmd->sdid = sdid;
  rr->buffer = NULL;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai List TA %x\n", rr));

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai List TA %x ret %x\n", rr, rr->code));

  *count = 0;
  *appIdStrs = NULL;
  do {
    if (ret != BH_SUCCESS)  break;
    if (rr->buffer == NULL) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }

    resp = (bhp_list_ta_response*) rr->buffer;
    total_count = resp->count;
    if (total_count == 0)  break;

    if (rr->length != sizeof (BH_TAID) * total_count + sizeof (bhp_list_ta_response)) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }
    outbuf = (char**) BHMALLOC (sizeof (char*) * (total_count+1));
    if (!outbuf) {
      ret = BPE_OUT_OF_MEMORY;
      break;
    }
    ZeroMem (outbuf, sizeof (char*) * (total_count+1));

    for (i=0; i< total_count; i++) {
      outbuf[i] = (char*) BHMALLOC (BH_GUID_LENGTH *2 +1);
      if (outbuf[i] == NULL) {
        ret = BPE_OUT_OF_MEMORY;
        break;
      }
      AsciiUuid2Str ((UINT8 *)&resp->ta_ids[i], outbuf[i]);
    }
    if (ret != BH_SUCCESS) break;

    *count  = total_count;
    *appIdStrs = outbuf;
  } while (0);

  if (ret != BH_SUCCESS) {
    for (i=0; i<total_count; i++) {
      if (outbuf && outbuf[i]) BHFREE (outbuf[i]);
    }
    if (outbuf) BHFREE (outbuf);
  }
  if (rr->buffer) {
    BHFREE (rr->buffer);
    rr->buffer = NULL;
  }

  session_exit (CONN_IDX_SDM, rr, seq, 1);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_ListInstalledTAs done, ret: %x\n\n", ret));
  return ret;
}
