/** @file
  This file implements Beihai Host Proxy (BHP) module TA related API.

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

static void byte_order_swapi (int* i)
{
  //reverse the byte order of the int i
  int iTmp = *i;
  char* c = (char*) i;
  char* cTmp = (char*)&iTmp;
  c[0] = cTmp[3]; c[1] = cTmp[2]; c[2] = cTmp[1]; c[3] = cTmp[0];
}

//try to session_enter for IVM, then SVM.
static bh_response_record* session_enter_vm (BH_U64 seq, int* conn_idx, int lock_session)
{
  bh_response_record* rr = NULL;

  if (conn_idx == NULL) return NULL;
  rr = session_enter (CONN_IDX_IVM, seq, lock_session);
  if (rr) {
    *conn_idx = CONN_IDX_IVM;
  } else {
#if BEIHAI_ENABLE_SVM
    rr = session_enter (CONN_IDX_SVM, seq, lock_session);
    if (rr) *conn_idx = CONN_IDX_SVM;
#endif
  }
  return rr;
}

static BH_RET bh_proxy_get_sd_by_ta (BH_TAID taid, BH_SDID* sdid)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_get_sd_by_ta_cmd* cmd = (bhp_get_sd_by_ta_cmd*) h->cmd;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_get_sd_by_ta, taid:\n"));
  DbgRawdataDump (&taid, sizeof (BH_TAID));
  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (sdid == NULL) return BPE_INVALID_PARAMS;
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai get_sd_by_ta 0x%x\n", &rr));
  h->id = BHP_CMD_GET_SD_BY_TA;
  cmd->taid = taid;

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, rrmap_add (CONN_IDX_SDM, &rr));
  if (ret == BH_SUCCESS)  ret = rr.code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai get_sd_by_ta 0x%x ret 0x%x\n", &rr, rr.code));

  if (ret != BH_SUCCESS) goto cleanup;
  if (rr.buffer && rr.length == sizeof (bhp_get_sd_by_ta_response)) {
    bhp_get_sd_by_ta_response* resp = (bhp_get_sd_by_ta_response*) rr.buffer;
    *sdid = resp->sdid;
  } else {
    ret = BPE_MESSAGE_ILLEGAL;
  }

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "sdid:\n"));
  DbgRawdataDump (sdid, sizeof (BH_SDID));

cleanup:
  if (rr.buffer) BHP_Free (rr.buffer);
  return ret;
}

static BH_RET bh_proxy_check_svl_ta_blocked_state (BH_TAID taid)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_check_svl_ta_blocked_state_cmd* cmd = (bhp_check_svl_ta_blocked_state_cmd*) h->cmd;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai check_svl_ta_blocked_state 0x%x\n", &rr));
  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  h->id = BHP_CMD_CHECK_SVL_TA_BLOCKED_STATE;
  cmd->taid = taid;
  CopyMem (&cmd->taid, &taid, sizeof (bhp_check_svl_ta_blocked_state_cmd));
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bhp_command_header:\n"));
  DbgRawdataDump (h, sizeof (sizeof (*h) + sizeof (bhp_check_svl_ta_blocked_state_cmd)));

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, rrmap_add (CONN_IDX_SDM, &rr));
  if (ret == BH_SUCCESS)  ret = rr.code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai check_svl_ta_blocked_state 0x%x ret 0x%x\n", &rr, rr.code));

  if (rr.buffer) BHP_Free (rr.buffer);
  return ret;
}

static BH_RET bh_proxy_listJTAPackages (int conn_idx, int *count, BH_TAID** appIds)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;
  bhp_list_ta_packages_response* resp;
  BH_TAID* outbuf;
  unsigned int i;

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  if (!count || !appIds) return BPE_INVALID_PARAMS;

  h->id = BHP_CMD_LIST_TA_PACKAGES;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai ListJTAPackages %x\n", &rr));

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h), NULL, 0, rrmap_add (conn_idx, &rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai ListJTAPackages %x ret %x\n", &rr, rr.code));

  *appIds = NULL;
  *count = 0;
  do {
    if (ret != BH_SUCCESS) break;
    if (rr.buffer == NULL) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }
    resp = (bhp_list_ta_packages_response*) rr.buffer;
    if (resp->count == 0) break;

    if (rr.length != sizeof (BH_TAID) * resp->count + sizeof (bhp_list_ta_packages_response)) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }
    outbuf = (BH_TAID*) BHP_Malloc (sizeof (BH_TAID) * resp->count);
    if (!outbuf) {
      ret = BPE_OUT_OF_MEMORY;
      break;
    }
    for (i = 0; i< resp->count; i++) {
      outbuf[i] = resp->appIds[i];
    }
    *appIds = outbuf;
    *count = resp->count;
  } while (0);

  if (rr.buffer) BHP_Free (rr.buffer);

  return ret;
}

static BH_RET bh_proxy_download_javata (int conn_idx, BH_TAID ta_id, const char* ta_pkg, unsigned int pkg_len)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_download_javata_cmd *cmd = (bhp_download_javata_cmd*) h->cmd;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (ta_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;

  h->id = BHP_CMD_DOWNLOAD_JAVATA;
  cmd->appid = ta_id;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_download_javata\n"));

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), ta_pkg, pkg_len, rrmap_add (conn_idx,&rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_download_javata, ret %x\n", rr.code));

  if (rr.buffer) BHP_Free (rr.buffer);

  return ret;
}

static BH_RET bh_proxy_openjtasession (int conn_idx, BH_TAID ta_id, const char* init_buffer,
                unsigned int init_len, JAVATA_SESSION_HANDLE* pHandle, int* vmConnClosed,
                const char* TA_pkg, unsigned int pkg_len)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_open_jtasession_cmd* cmd = (bhp_open_jtasession_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_U64 seq;
  BH_RET ret = BH_SUCCESS;

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (pHandle == NULL) return BPE_INVALID_PARAMS;
  if (init_buffer == NULL && init_len >0) return BPE_INVALID_PARAMS;

  rr = (bh_response_record*) BHP_Malloc (sizeof (bh_response_record));
  if (!rr) {
    return BPE_OUT_OF_MEMORY;
  }
  ZeroMem (rr, sizeof (bh_response_record));
  rr->count = 1;
  rr->is_session = 1;
  seq = rrmap_add (conn_idx, rr);

  h->id = BHP_CMD_OPEN_JTASESSION;
  cmd->appid = ta_id;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_openjtasession %x\n", rr));

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), (char*) init_buffer, init_len, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai bh_proxy_openjtasession %x ret %x\n", rr, rr->code));

  if (rr->buffer) {
    BHP_Free (rr->buffer);
    rr->buffer = NULL;
  }
  if (ret == BHE_PACKAGE_NOT_FOUND) {
    //VM might delete the TA pkg when no live session. Download the TA pkg and open session again.
    ret = bh_proxy_download_javata (conn_idx, ta_id, TA_pkg, pkg_len);
    if (ret == BH_SUCCESS) {
      ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), (char*) init_buffer, init_len, seq);
      if (ret == BH_SUCCESS) ret = rr->code;
      if (rr->buffer) {
        BHP_Free (rr->buffer);
        rr->buffer = NULL;
      }
    }
  }
  if (ret == BH_SUCCESS) {
    *pHandle = (JAVATA_SESSION_HANDLE) seq;
    session_exit (conn_idx, rr, seq, 0);
  } else {
    //bh_do_closeVM() will be called in following session_close(), as rr->count is 1.
    session_close (conn_idx, rr, seq, 0);
    *vmConnClosed = 1;
  }

  return ret;
}

BH_RET BHP_OpenTASession (JAVATA_SESSION_HANDLE* pSession, const char *pAppId,
         const char* TA_pkg, unsigned int pkg_len, const char* init_buffer, unsigned int init_len)
{
  BH_RET ret = BH_SUCCESS;
  BH_TAID ta_id;
  int conn_idx = 0;
  int vmConnClosed = 0;
  BH_SDID sdid;
  int taExisted = 0;
  int count = 0;
  BH_TAID* appIds = NULL;
  int i;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_OpenTASession <<<\n"));
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "pAppId: %a\n", pAppId));
  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  if (!pAppId || !pSession) return BPE_INVALID_PARAMS;

  if (TA_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;

  if (init_buffer == NULL && init_len != 0) return BPE_INVALID_PARAMS;

  if (!AsciiStr2Uuid (pAppId, (UINT8 *)&ta_id)) return BPE_INVALID_PARAMS;

  *pSession = NULL;

  //step 1: get vm connection idx
  //1.1: get the TA's sdid
  ret = bh_proxy_get_sd_by_ta (ta_id, &sdid);
  if (ret != BH_SUCCESS) return ret;
  ret = bh_proxy_check_svl_ta_blocked_state (ta_id);
  if (ret != BH_SUCCESS) return ret;
  //1.2: get corresponding vm conn_idx
  ret = bh_do_openVM (sdid, &conn_idx, BHP_OPEN_VM_NORMAL_MODE);
  if (ret != BH_SUCCESS) return ret;

  //step 2: send downloadJavaTA cmd to VM if needed
  //2.1: check whether the ta pkg existed in VM or not
  ret = bh_proxy_listJTAPackages (conn_idx, &count, &appIds);
  if (ret == BH_SUCCESS) {
    for (i=0;i<count; i++) {
      if (CompareMem (&ta_id, &appIds[i], sizeof (BH_TAID)) == 0) {
        taExisted = 1;
        break;
      }
    }
    if (appIds != NULL) BHP_Free (appIds);
  }
  //2.2: download ta pkg if not existed.
  if (!taExisted) {
    ret = bh_proxy_download_javata (conn_idx, ta_id, TA_pkg, pkg_len);
    if (ret != BH_SUCCESS && ret != BHE_PACKAGE_EXIST) {
      DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Download jta failed. ret=0x%x, conn_idx=%d, ta-id='%s'.\n", ret, conn_idx, pAppId));
      goto cleanup;
    }
  }

  //step 3: send opensession cmd to VM
  ret = bh_proxy_openjtasession (conn_idx, ta_id, init_buffer, init_len, pSession, &vmConnClosed, TA_pkg, pkg_len);

cleanup:
  if (ret != BH_SUCCESS && !vmConnClosed) {
    //closeVM only when this process failed and vm has not been closed inside openjtasession,
    //otherwise the session is created.
    bh_do_closeVM (conn_idx);
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_OpenTASession done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_SendAndRecv (const JAVATA_SESSION_HANDLE handle, int nCommandId, const void* input, unsigned int length,
         void** output, unsigned int* output_length, int* pResponseCode)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_snr_cmd* cmd = (bhp_snr_cmd*) h->cmd;
  BH_U64 seq = (BH_U64) handle;
  bh_response_record* rr = NULL;
  BH_RET ret = BH_SUCCESS;
  int conn_idx = 0;
  unsigned int len;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_SendAndRecv <<<\n"));
  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  if (!input && length != 0) return BPE_INVALID_PARAMS;

  if (!output_length) return BPE_INVALID_PARAMS;

  if (output) *output = NULL;

  rr = session_enter_vm (seq, &conn_idx, 1);
  if (!rr) {
    return BPE_INVALID_PARAMS;
  }

  rr->buffer = NULL;
  h->id = BHP_CMD_SENDANDRECV;

  cmd->ta_session_id = rr->addr;
  cmd->command = nCommandId;
  cmd->outlen = *output_length;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai SendAndReceive %x\n", rr));

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), (char*) input, length, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai SendAndReceive %x ret %x\n", rr, rr->code));

  if (rr->killed) {
    ret = BHE_UNCAUGHT_EXCEPTION;
  }

  if (ret == BH_SUCCESS ) {
    bhp_snr_response *resp = NULL;
    if (rr->buffer && rr->length >= sizeof (bhp_snr_response)) {
      resp = (bhp_snr_response *) rr->buffer;
      if (pResponseCode) {
        *pResponseCode = resp->response;
        byte_order_swapi (pResponseCode);
      }

      len = rr->length - sizeof (bhp_snr_response);

      if (len>0) {
        if (output && *output_length >= len) {
          *output = (char*) BHP_Malloc (len);
          if (*output) {
            CopyMem (*output, resp->buffer, len);
          } else  {
            ret = BPE_OUT_OF_MEMORY;
          }
        } else {
          ret = BHE_APPLET_SMALL_BUFFER;
        }
      }

      *output_length = len;
    } else {
      ret = BPE_MESSAGE_TOO_SHORT;
    }
  } else if (ret == BHE_APPLET_SMALL_BUFFER && rr->buffer && rr->length == sizeof (bhp_snr_bof_response)) {
    bhp_snr_bof_response* resp = (bhp_snr_bof_response *) rr->buffer;
    if (pResponseCode) {
      *pResponseCode = resp->response;
      byte_order_swapi (pResponseCode);
    }

    *output_length = resp->request_length;
    byte_order_swapi ((int*) output_length);
  }

  if (rr->buffer) {
    BHP_Free (rr->buffer);
    rr->buffer = NULL;
  }

  session_exit (conn_idx, rr, seq, 1);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_SendAndRecv done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_SendAndRecvInternal (const JAVATA_SESSION_HANDLE handle, int what, int nCommandId,
         const void* input, unsigned int length, void** output, unsigned int* output_length, int* pResponseCode)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_snr_internal_cmd* cmd = (bhp_snr_internal_cmd*) h->cmd;
  BH_U64 seq = (BH_U64) handle;
  bh_response_record* rr = NULL;
  BH_RET ret = BH_SUCCESS;
  int conn_idx = 0;
  unsigned int len;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_SendAndRecvInternal <<<\n"));

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  if (!input && length != 0) return BPE_INVALID_PARAMS;

  if (!output_length) return BPE_INVALID_PARAMS;

  if (output) *output = NULL;

  rr = session_enter_vm (seq, &conn_idx, 1);
  if (!rr) {
    return BPE_INVALID_PARAMS;
  }

  rr->buffer = NULL;
  h->id = BHP_CMD_SENDANDRECV_INTERNAL;

  cmd->ta_session_id = rr->addr;
  cmd->what = what;
  cmd->command = nCommandId;
  cmd->outlen = *output_length;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai SendAndReceive-Internal %x\n", rr));

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), (char*) input, length, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai SendAndReceive-Internal %x ret %x\n", rr, rr->code));

  if (rr->killed) {
    ret = BHE_UNCAUGHT_EXCEPTION;
  }

  if (ret == BH_SUCCESS ) {
    bhp_snr_response *resp = NULL;
    if (rr->buffer && rr->length >= sizeof (bhp_snr_response)) {
      resp = (bhp_snr_response *) rr->buffer;
      if (pResponseCode) {
        *pResponseCode = resp->response;
        byte_order_swapi (pResponseCode);
      }

      len = rr->length - sizeof (bhp_snr_response);

      if (len>0) {
        if (output && *output_length >= len) {
          *output = (char*) BHP_Malloc (len);
          if (*output) {
            CopyMem (*output, resp->buffer, len);
          } else  {
            ret = BPE_OUT_OF_MEMORY;
          }
        } else {
          ret = BHE_APPLET_SMALL_BUFFER;
        }
      }

      *output_length = len;
    } else {
      ret = BPE_MESSAGE_TOO_SHORT;
    }
  } else if (ret == BHE_APPLET_SMALL_BUFFER && rr->buffer && rr->length == sizeof (bhp_snr_bof_response)) {
    bhp_snr_bof_response* resp = (bhp_snr_bof_response *) rr->buffer;
    if (pResponseCode) {
      *pResponseCode = resp->response;
      byte_order_swapi (pResponseCode);
    }

    *output_length = resp->request_length;
    byte_order_swapi ((int*) output_length);
  }

  if (rr->buffer) {
    BHP_Free (rr->buffer);
    rr->buffer = NULL;
  }

  session_exit (conn_idx, rr, seq, 1);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_SendAndRecvInternal done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_CloseTASession (const JAVATA_SESSION_HANDLE handle)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_close_jtasession_cmd* cmd = (bhp_close_jtasession_cmd*) h->cmd;
  bh_response_record* rr = NULL;
  BH_U64 seq = (BH_U64) handle;
  BH_RET ret = BH_SUCCESS;
  int conn_idx = 0;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_CloseTASession <<<\n"));

  ZeroMem (cmdbuf, sizeof (cmdbuf));

  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  rr = session_enter_vm (seq, &conn_idx, 1);
  if (!rr) {
    return BPE_INVALID_PARAMS;
  }

  h->id = BHP_CMD_CLOSE_JTASESSION;
  cmd->ta_session_id = rr->addr;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai BHP_CloseTASession %x\n", rr));

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, seq);
  if (ret == BH_SUCCESS) ret = rr->code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai BHP_CloseTASession %x ret %x\n", rr, rr->code));

  if (rr->killed) {
    ret = BHE_UNCAUGHT_EXCEPTION;
  }

  if (ret == BHE_IAC_EXIST_INTERNAL_SESSION) {
    //internal session exists, so we should not close the hmc session.
    //It means that host app should call this API at approciate time later.
    session_exit (conn_idx, rr, seq, 1);
  } else {
    session_close (conn_idx, rr, seq, 1);
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_CloseTASession done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_ForceCloseTASession (const JAVATA_SESSION_HANDLE handle)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_forceclose_jtasession_cmd* cmd = (bhp_forceclose_jtasession_cmd*) h->cmd;
  bh_response_record rr;
  bh_response_record* session_rr = NULL;
  BH_U64 seq = (BH_U64) handle;
  BH_RET ret = BH_SUCCESS;
  int conn_idx = 0;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_ForceCloseTASession <<<\n"));

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  session_rr = session_enter_vm (seq, &conn_idx, 0);
  if (!session_rr) {
    return BPE_INVALID_PARAMS;
  }

  h->id = BHP_CMD_FORCECLOSE_JTASESSION;
  cmd->ta_session_id = session_rr->addr;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai ForceCloseTASession\n"));

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, rrmap_add (conn_idx, &rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai ForceCloseTASession ret %x\n", rr.code));

  if (rr.buffer) BHP_Free (rr.buffer);

  session_close (conn_idx, session_rr, seq, 0);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_ForceCloseTASession done, ret: %x\n\n", ret));
  return ret;
}

#if BEIHAI_ENABLE_NATIVETA
static BH_RET bh_proxy_list_downloaded_nta (BH_SDID sd_id, int *count, BH_TAID** appIds)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_list_downloaded_nta_cmd* cmd = (bhp_list_downloaded_nta_cmd*) h->cmd;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;
  bhp_list_downloaded_nta_response* resp;
  BH_TAID* outbuf;
  unsigned int i;

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  if (!count || !appIds) return BPE_INVALID_PARAMS;

  h->id = BHP_CMD_LIST_DOWNLOADED_NTA;
  cmd->sdid = sd_id;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai list_downloaded_nta %x\n", &rr));

  ret = bh_cmd_transfer (CONN_IDX_LAUNCHER, (char*) h, sizeof (*h) +sizeof (*cmd), NULL, 0, rrmap_add (CONN_IDX_LAUNCHER, &rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai list_downloaded_nta %x ret %x\n", &rr, rr.code));

  *appIds = NULL;
  *count = 0;
  do {
    if (ret != BH_SUCCESS) break;
    if (rr.buffer == NULL) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }
    resp = (bhp_list_downloaded_nta_response*) rr.buffer;
    if (resp->count == 0) break;

    if (rr.length != sizeof (BH_TAID) * resp->count + sizeof (bhp_list_downloaded_nta_response)) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }
    outbuf = (BH_TAID*) BHP_Malloc (sizeof (BH_TAID) * resp->count);
    if (!outbuf) {
      ret = BPE_OUT_OF_MEMORY;
      break;
    }
    for (i = 0; i< resp->count; i++) {
      outbuf[i] = resp->nta_ids[i];
    }
    *appIds = outbuf;
    *count = resp->count;
  } while (0);

  if (rr.buffer) BHP_Free (rr.buffer);

  return ret;
}
#endif

BH_RET BHP_ListDownloadedTAs (const char* SD_ID, unsigned int *count, char*** appIdStrs)
{
  BH_RET ret = BH_SUCCESS;
  BH_SDID sdid;
  //normallized SD_ID string, which removes all "-" characters
  char normallized_SD_ID[BH_GUID_LENGTH * 2 + 1];
  int conn_idx = 0;
  int count_jta = 0, count_nta = 0;
  BH_TAID *appIds_jta = NULL, *appIds_nta = NULL;
  int total_count = 0;
  char** outbuf = NULL;
  SD_SESSION_HANDLE sd_session = NULL;
  int i;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_ListDownloadedTAs <<<\n"));
  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  if (!SD_ID || !count || !appIdStrs) return BPE_INVALID_PARAMS;

  if (!AsciiStr2Uuid (SD_ID, (UINT8 *)&sdid))  return BPE_INVALID_PARAMS;

  AsciiUuid2Str ((UINT8 *)&sdid, normallized_SD_ID);

  *count = 0;
  *appIdStrs = NULL;

  //step1: check with SDM whether sd_id is installed or not
  do {
    unsigned int sd_count = 0;
    char** sdIdStrs = NULL;
    unsigned int idx = 0;
    int installed = 0;

    ret = BHP_OpenSDSession (SD_ID, &sd_session);
    if (ret != BH_SUCCESS) break;
    ret = BHP_ListInstalledSDs (sd_session, &sd_count, &sdIdStrs);
    if (ret != BH_SUCCESS) break;
    for (idx=0; idx<sd_count; idx++) {
      if (AsciiStriCmp (sdIdStrs[idx], normallized_SD_ID) == 0) {
        installed = 1;
      }
      BHP_Free (sdIdStrs[idx]);
      sdIdStrs[idx] = NULL;
    }
    if (sdIdStrs) BHP_Free (sdIdStrs);
    if (!installed) ret = BHE_SDM_NOT_FOUND;
  } while (0);
  if (sd_session != NULL) BHP_CloseSDSession (sd_session);
  if (ret != BH_SUCCESS) return ret;

  //step2: send ListDownloadedNTA cmd to Launcher to get downloaded native TAs
#if BEIHAI_ENABLE_NATIVETA
  ret = bh_proxy_list_downloaded_nta (sdid, &count_nta, &appIds_nta);
  if (ret != BH_SUCCESS) goto cleanup;
#endif

  //step3: openVM in query mode to know the vm conn idx
  //NOTE: openVM failure indicates sdid-VM is not launched, so We don't care
  if (bh_do_openVM (sdid, &conn_idx, BHP_OPEN_VM_QUERY_MODE) == BH_SUCCESS) {
    //step4: send ListTAPackages cmd to VM for downloaded java TA
    ret = bh_proxy_listJTAPackages (conn_idx, &count_jta, &appIds_jta);
    bh_do_closeVM (conn_idx);
    if (ret != BH_SUCCESS) goto cleanup;
  }

  //step5: convert the result to string arrays
  total_count = count_jta + count_nta;
  do {
    if (total_count == 0) break;

    outbuf = (char**) BHP_Malloc (sizeof (char*) * (total_count+1));
    if (!outbuf) {
      ret = BPE_OUT_OF_MEMORY;
      break;
    }
    ZeroMem (outbuf, sizeof (char*) * (total_count+1));
    for (i=0; i<total_count; i++) {
      outbuf[i] = (char*) BHP_Malloc (BH_GUID_LENGTH * 2 + 1);
      if (outbuf[i] == NULL) {
        ret = BPE_OUT_OF_MEMORY;
        break;
      }
    }
    if (ret != BH_SUCCESS) break;

    for (i = 0; i< count_jta; i++) {
      AsciiUuid2Str ((UINT8 *)&appIds_jta[i], outbuf[i]);
    }
    for (i = 0; i< count_nta; i++) {
      AsciiUuid2Str ((UINT8 *)&appIds_nta[i], outbuf[i+count_jta]);
    }

    *count = total_count;
    *appIdStrs = outbuf;
  } while (0);

cleanup:
  if (appIds_jta) BHP_Free (appIds_jta);
  if (appIds_nta) BHP_Free (appIds_nta);
  if (ret != BH_SUCCESS) {
    for (i = 0; i < total_count; i++) {
      if (outbuf && outbuf[i]) BHP_Free (outbuf[i]);
    }
    if (outbuf) BHP_Free (outbuf);
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_ListDownloadedTAs done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_ListTASessions (const char* appId, unsigned int* count, JAVATA_SESSION_HANDLE** pSessions)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_list_ta_sessions_cmd* cmd = (bhp_list_ta_sessions_cmd*) h->cmd;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;
  int conn_idx = 0;
  BH_SDID sdid;
  bhp_list_ta_sessions_response* resp;
  JAVATA_SESSION_HANDLE* outbuf;
  unsigned int i;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_ListTASessions <<<\n"));

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (!is_bhp_inited ())  return BPE_NOT_INIT;

  if (!appId || !count || !pSessions)  return BPE_INVALID_PARAMS;

  if (!AsciiStr2Uuid (appId, (UINT8 *)&(cmd->appid)))  return BPE_INVALID_PARAMS;

  *count = 0;
  *pSessions = NULL;

  //step 1: get the TA's sdid
  ret = bh_proxy_get_sd_by_ta (cmd->appid, &sdid);
  if (ret != BH_SUCCESS) return ret;

  //step 2: get the TA's VM conn_idx
  ret = bh_do_openVM (sdid, &conn_idx, BHP_OPEN_VM_QUERY_MODE);
  //NOTE: openvm failure means that no sdid-VM running, so return.
  if (ret != BH_SUCCESS) return ret;

  //step 3: send list-ta-session cmd to VM
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai ListJTASessions %x\n", &rr));
  h->id = BHP_CMD_LIST_JTA_SESSIONS;

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, rrmap_add (conn_idx, &rr));
  if (ret == BH_SUCCESS)  ret = rr.code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai ListJTASessions %x ret %x\n", &rr, rr.code));

  do {
    if (ret != BH_SUCCESS)  break;
    if (rr.buffer == NULL) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }

    resp = (bhp_list_ta_sessions_response*) rr.buffer;
    if (resp->count == 0)  break;

    if (rr.length != sizeof (BH_U64) * resp->count + sizeof (bhp_list_ta_sessions_response)) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }

    outbuf = (JAVATA_SESSION_HANDLE*) BHP_Malloc (sizeof (JAVATA_SESSION_HANDLE) * resp->count);
    if (!outbuf) {
      ret = BPE_OUT_OF_MEMORY;
      break;
    }
    ZeroMem (outbuf, sizeof (JAVATA_SESSION_HANDLE) * resp->count);

    for (i=0; i< resp->count; i++) {
      outbuf[i] = (JAVATA_SESSION_HANDLE) resp->addr[i];
    }

    *pSessions = outbuf;
    *count = resp->count;
  } while (0);

  if (rr.buffer) BHP_Free (rr.buffer);
  bh_do_closeVM (conn_idx);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_ListTASessions done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_ListTAProperties (const char* appId, unsigned int *count, char*** properties)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_list_ta_properties_cmd* cmd = (bhp_list_ta_properties_cmd*) h->cmd;
  bh_response_record rr;
  BH_SDID sdid;
  int conn_idx = 0;
  BH_RET ret;
  char** outbuf = NULL;
  int total_count = 0;
  char* buf;
  char* pos;
  int i;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_ListTAProperties <<<\n"));

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  if (!appId || !properties || !count)   return BPE_INVALID_PARAMS;

  if (!AsciiStr2Uuid (appId, (UINT8 *)&(cmd->appid)))   return BPE_INVALID_PARAMS;

  //step 1: get the TA's sdid
  ret = bh_proxy_get_sd_by_ta (cmd->appid, &sdid);
  if (ret != BH_SUCCESS) return ret;

  //step 2: get the TA's VM conn_idx
  ret = bh_do_openVM (sdid, &conn_idx, BHP_OPEN_VM_QUERY_MODE);
  //NOTE: openvm failure means that no sdid-VM running, so return empty list with failure.
  if (ret != BH_SUCCESS) return ret;

  //step 3: send list-ta-properties cmd to VM
  h->id = BHP_CMD_LIST_TA_PROPERTIES;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai ListTAProperties  %x\n", &rr));

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, rrmap_add (conn_idx, &rr));
  if ( ret == BH_SUCCESS )  ret = rr.code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai ListTAProperties %x ret %x\n", &rr, rr.code));

  *properties = NULL;
  *count = 0;
  do {
    if (ret != BH_SUCCESS)  break;
    if ( rr.buffer == NULL ) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }

    buf  = (char*) rr.buffer;
    if (buf[rr.length - 1] != 0) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }

    pos = (char*) rr.buffer;
    while (pos < (char*) rr.buffer + rr.length) {
      pos += AsciiStrLen (pos) + 1;
      total_count ++;
    }

    if (total_count == 0)  break;

    outbuf = (char**) BHP_Malloc ((total_count+1) * sizeof (char*));
    if (!outbuf) {
      ret = BPE_OUT_OF_MEMORY;
      break;
    }
    //the last item of output is "\0"
    ZeroMem (outbuf, (total_count+1) * sizeof (char*));

    pos = (char*) rr.buffer;
    for (i = 0; i< total_count; i++) {
      int pos_len = (int) AsciiStrLen (pos) + 1;
      outbuf[i] = (char*) BHP_Malloc (pos_len);
      if (outbuf[i] == NULL) {
        ret = BPE_OUT_OF_MEMORY;
        break;
      }

      AsciiStrCpyS (outbuf[i], ((total_count+1) * sizeof (char*)), pos);
      pos += pos_len;
    }
    if (ret != BH_SUCCESS) break;

    *properties = outbuf;
    *count = total_count;
  } while (0);

  if (ret != BH_SUCCESS) {
    for (i = 0; i< total_count; i++) {
      if (outbuf && outbuf[i]) BHP_Free (outbuf[i]);
    }
    if (outbuf) BHP_Free (outbuf);
  }

  if (rr.buffer) BHP_Free (rr.buffer);
  bh_do_closeVM (conn_idx);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_ListTAProperties done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_QueryTAProperty (const char *appId, const void* property, unsigned int length, char** output)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_query_ta_property_cmd* cmd = (bhp_query_ta_property_cmd*) h->cmd;
  bh_response_record rr;
  BH_SDID sdid;
  int conn_idx = 0;
  BH_RET ret;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_QueryTAProperty <<<\n"));

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (!is_bhp_inited ())  return BPE_NOT_INIT;

  if (!appId || !property || length == 0 || !output)  return BPE_INVALID_PARAMS;

  if (!AsciiStr2Uuid (appId, (UINT8 *)&(cmd->appid)))  return BPE_INVALID_PARAMS;
  *output = NULL;

  //step 1: get the TA's sdid
  ret = bh_proxy_get_sd_by_ta (cmd->appid, &sdid);
  if (ret != BH_SUCCESS) return ret;

  //step 2: get the TA's VM conn_idx
  ret = bh_do_openVM (sdid, &conn_idx, BHP_OPEN_VM_QUERY_MODE);
  //NOTE: openvm failure means that no sdid-VM running, so return empty list with failure.
  if (ret != BH_SUCCESS) return ret;

  //step 3: send query-ta-property cmd to VM
  h->id = BHP_CMD_QUERY_TA_PROPERTY;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai QueryTAProperty %x\n", &rr));

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h) + sizeof (*cmd), property, length, rrmap_add (conn_idx, &rr));
  if (ret == BH_SUCCESS )  ret = rr.code;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai QueryTAProperty %x ret %x\n", &rr, rr.code));

  if (ret == BH_SUCCESS) {
    if (rr.length > 0 && rr.buffer) {
      int len = rr.length;
      if (output) {
        *output = (char*) BHP_Malloc (len + 1);
        if (*output) {
          CopyMem (*output, rr.buffer, len);
          (*output) [len] = 0;
        } else {
          ret = BPE_OUT_OF_MEMORY;
        }
      }
    } else if (rr.length == 0) {
      *output = NULL;
    } else {
      ret = BPE_MESSAGE_TOO_SHORT;
    }
  }

  if (rr.buffer) BHP_Free (rr.buffer);
  bh_do_closeVM (conn_idx);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_QueryTAProperty done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_RunNativeTA (const char* pAppId, const char* TA_pkg, unsigned int pkg_len)
{
  BH_RET ret = BH_SUCCESS;
#if BEIHAI_ENABLE_NATIVETA
  BH_TAID ta_id;
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_run_nativeta_cmd* cmd = (bhp_run_nativeta_cmd*) h->cmd;
  bh_response_record rr;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_RunNativeTA <<<\n"));

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  if (TA_pkg == NULL || pkg_len == 0) return BPE_INVALID_PARAMS;

  if (!pAppId) return BPE_INVALID_PARAMS;

  if (!AsciiStr2Uuid (pAppId, (UINT8 *)&ta_id)) return BPE_INVALID_PARAMS;

  //check svl for TA blocked state first
  ret = bh_proxy_check_svl_ta_blocked_state (ta_id);
  if (ret != BH_SUCCESS) return ret;

  h->id = BHP_CMD_RUN_NATIVETA;
  cmd->appid = ta_id;

  ret = bh_cmd_transfer (CONN_IDX_LAUNCHER, (char*) h, sizeof (*h) + sizeof (*cmd), TA_pkg, pkg_len, rrmap_add (CONN_IDX_LAUNCHER,&rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  if (rr.buffer) BHP_Free (rr.buffer);

#else
  ret = BPE_NOT_IMPLEMENT;
#endif
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_RunNativeTA done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_StopNativeTA (const char* pAppId)
{
  BH_RET ret = BH_SUCCESS;
#if BEIHAI_ENABLE_NATIVETA
  BH_TAID ta_id;
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_stop_nativeta_cmd* cmd = (bhp_stop_nativeta_cmd*) h->cmd;
  bh_response_record rr;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_StopNativeTA <<<\n"));

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (rr));

  if (!is_bhp_inited ()) return BPE_NOT_INIT;

  if (!pAppId) return BPE_INVALID_PARAMS;

  if (!AsciiStr2Uuid (pAppId, (UINT8 *)&ta_id)) return BPE_INVALID_PARAMS;

  h->id = BHP_CMD_STOP_NATIVETA;
  cmd->appid = ta_id;

  ret = bh_cmd_transfer (CONN_IDX_LAUNCHER, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, rrmap_add (CONN_IDX_LAUNCHER,&rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  if (rr.buffer) BHP_Free (rr.buffer);

#else
  ret = BPE_NOT_IMPLEMENT;
#endif
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_StopNativeTA done, ret: %x\n\n", ret));
  return ret;
}
