/** @file
  This is the UEFI implementation of Bhp_impl.

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
#include <Library/DxeBeihaiLib/BeihaiStatusHAL.h>
#include <Library/DxeBeihaiLib/Mei.h>


#define MAX_RETRY_COUNT   (3)

typedef BH_U64            ADDR;
typedef struct _RR_MAP_INFO {
  UINT32                  Signature;
  LIST_ENTRY              Link;
  ADDR                    seq;
  bh_response_record      *rr;
} RR_MAP_INFO;
#define RR_MAP_INFO_SIGNATURE SIGNATURE_32 ('r', 'r', 'm', 'i')

BH_RET bh_send_message (int conn_idx, void* cmd, unsigned int clen, const void* data, unsigned int dlen, BH_U64 seq);
BH_RET bh_recv_message (int conn_idx, BH_U64 *seq);
BH_RET bh_do_closeVM (int conn_idx);
BH_RET bh_do_openVM (BH_SDID sdid, int* conn_idx, int mode);
BH_RET bh_proxy_reset_svm (int conn_idx);
int HeciSendWrapper (unsigned int handle, unsigned char* buffer, unsigned int length);
int HeciRecvWrapper (unsigned int handle, unsigned char* buffer, unsigned int* length);
int HeciConnectWrapper (int heci_port, unsigned int* handle);
int HeciCloseWrapper (unsigned int handle);
void destroy_session (bh_response_record* session);
bh_response_record* session_enter (int conn_idx, BH_U64 seq, int lock_session);
void session_exit (int conn_idx, bh_response_record* session, BH_U64 seq, int unlock_session);
void session_close (int conn_idx, bh_response_record* session, BH_U64 seq, int unlock_session);
void session_kill (int conn_idx, bh_response_record* session, BH_U64 seq, int callerIsSVMRecvThread);

static volatile unsigned int init_state = DEINITED;
static BH_U32 g_seqno = 0;
static bh_connection_item connections[MAX_CONNECTIONS]; //slot 0 is reserved
static BHP_TRANSPORT bhp_tx_itf = { //transport func list, set during init
  HeciSendWrapper,    // pfnSend
  HeciRecvWrapper,    // pfnRecv
  HeciConnectWrapper, // pfnConnect
  HeciCloseWrapper    // pfnClose
};
static BHP_TRANSPORT *gpBhTransport = NULL;
ME_INFO     MeInfo;
BOOLEAN     MeInfoDone = FALSE;

static BH_SDID g_isd_uuid = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }; //the isd-id in the firmware, got during init

// Prevent handle to be 0
#define HANDLE_BASE             (1000)
#define HANDLE_TO_MEID(handle)  ((ME_CLIENT_ID)((handle) - HANDLE_BASE))
#define MEID_TO_HANDLE(meid)    ((unsigned int)((meid) + HANDLE_BASE))

int HeciSendWrapper (unsigned int handle, unsigned char* buffer, unsigned int length)
{
  EFI_STATUS    Status;
  ME_CLIENT_ID  MeId;

  MeId = handle;
  if (handle >= 1000) {
    MeId = HANDLE_TO_MEID (handle);
  }

  if (MeId >= SVM_CLIENT) {
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_ERROR, "HeciSendWrapper error, MeId overflow.\n"));
    return BPE_COMMS_ERROR;
  }
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "HeciSendWrapper (handle: %x, MeId: %x)\n", handle, MeId));

  Status = MeiSend (
             MeId,
             (UINT32 *) buffer,
             (UINT32) length
             );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_ERROR, "HeciSendWrapper error, Status: %r.\n", Status));
    return BPE_COMMS_ERROR;
  }

  return BH_SUCCESS;
}

int HeciRecvWrapper (unsigned int handle, unsigned char* buffer, unsigned int* length)
{
  EFI_STATUS    Status;
  ME_CLIENT_ID  MeId;

  MeId = handle;
  if (handle >= 1000) {
    MeId = HANDLE_TO_MEID (handle);
  }
  if (MeId >= SVM_CLIENT) {
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_ERROR, "HeciRecvWrapper error, MeId overflow.\n"));
    return BPE_COMMS_ERROR;
  }

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "HeciRecvWrapper (handle: %x, MeId: %x)\n", handle, MeId));
  Status = MeiRecv (
             MeId,
             (UINT32 *) buffer,
             (UINT32 *) length
             );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "HeciRecvWrapper, Status: %r.\n", Status));
    return BPE_COMMS_ERROR;
  }

  return BH_SUCCESS;
}

int HeciConnectWrapper (int heci_port, unsigned int* handle)
{
  EFI_STATUS    Status;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "HeciRecvWrapper (heci_port: %x)\n", heci_port));
  Status = MeiClientConnect (
             (ME_CLIENT_ID) heci_port
             );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "HeciConnectWrapper, Status: %r.\n", Status));
    return BPE_COMMS_ERROR;
  }

  *handle = (unsigned int) MEID_TO_HANDLE (heci_port);
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "HeciRecvWrapper (Meid: %x, handle: %x)\n", heci_port, *handle));
  return BH_SUCCESS;
}

int HeciCloseWrapper (unsigned int handle)
{
  EFI_STATUS    Status;
  ME_CLIENT_ID  MeId;

  MeId = handle;
  if (handle >= 1000) {
    MeId = HANDLE_TO_MEID (handle);
  }
  if (MeId >= SVM_CLIENT) {
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_ERROR, "HeciCloseWrapper error, MeId overflow.\n"));
    return BPE_COMMS_ERROR;
  }

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "HeciCloseWrapper (handle: %x, MeId: %x)\n", handle, MeId));
  Status = MeiClientDisconnect (
             //(ME_CLIENT_ID) handle
             MeId
             );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "HeciCloseWrapper, Status: %r.\n", Status));
    return BPE_COMMS_ERROR;
  }

  return BH_SUCCESS;
}


static VOID
rrmap_dump (LIST_ENTRY *rr_map_header)
{
  LIST_ENTRY            *Link;
  RR_MAP_INFO           *rrmap_info;
  UINTN                 Count;

  Count = 0;
  for (
        Link = GetFirstNode (rr_map_header);
        !IsNull (rr_map_header, Link);
        Link = GetNextNode (rr_map_header, Link)) {
    rrmap_info = CR (
                   Link,
                   RR_MAP_INFO,
                   Link,
                   RR_MAP_INFO_SIGNATURE
                   );
    if (rrmap_info) {
      DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "[%02x] seq: %x, rr: %x\n", Count, rrmap_info->seq, rrmap_info->rr));
    }
    Count++;
  }
}

static RR_MAP_INFO*
rrmap_find_by_addr (LIST_ENTRY *rr_map_header, ADDR seq)
{
  LIST_ENTRY            *Link;
  RR_MAP_INFO           *rrmap_info;

  for (
        Link = GetFirstNode (rr_map_header);
        !IsNull (rr_map_header, Link);
        Link = GetNextNode (rr_map_header, Link)) {
    rrmap_info = CR (
                   Link,
                   RR_MAP_INFO,
                   Link,
                   RR_MAP_INFO_SIGNATURE
                   );
    if (rrmap_info->seq == seq) {
      DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "rrmap_find_by_addr (seq: %x) success\n", seq));
      return rrmap_info;
    }
  }

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_ERROR, "rrmap_find_by_addr (seq: %x) fail\n", seq));
  return NULL;
}

/*
 * function inc_seqno():
 *   increase the shared variable g_seqno by 1 and wrap around if needed.
 * note: g_seqno is shared resource among all connections/threads.
 * As the JAVATA_SESSION_HANDLE/SD_SESSION_HANDLE is (void*) type,
 * it could only store 32-bit value in 32-bit machine.
 * so we define g_seqno as BH_U32, and it should be enough for usage.
 */
static BH_U64 inc_seqno (
  VOID
  )
{
  BH_U32 ret = 0;

  mutex_enter (bhm_seqno);
  g_seqno++;
  //wrap around. g_seqno must not be 0, as required by Firmware VM.
  if (g_seqno == 0) {
    g_seqno = 1;
  }
  ret = g_seqno;
  mutex_exit (bhm_seqno);

  return (BH_U64) ret;
}

BH_U64 rrmap_add (int conn_idx, bh_response_record* rr)
{
  BH_U64 seq= inc_seqno ();
  RR_MAP_INFO *rrmap_info;

  mutex_enter (bhm_rrmap);
  rrmap_info = AllocateZeroPool (sizeof (RR_MAP_INFO));
  if (rrmap_info) {
    rrmap_info->Signature = RR_MAP_INFO_SIGNATURE;
    rrmap_info->seq = seq;
    rrmap_info->rr = rr;
    InsertTailList (&connections[conn_idx].rr_map_list_header, &rrmap_info->Link);
    mutex_exit (bhm_rrmap);
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "rrmap_add (rr: %x) at seq: %x\n", rr, rrmap_info->seq));
    rrmap_dump (&connections[conn_idx].rr_map_list_header);

    return rrmap_info->seq;
  }
  return (BH_U64)(-1);
}

static bh_response_record* rrmap_remove (int conn_idx, BH_U64 seq)
{
  RR_MAP_INFO *rrmap_info;
  bh_response_record* rr = NULL;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "rrmap_remove (seq: %x)\n", seq));
  mutex_enter (bhm_rrmap);
  rrmap_info = rrmap_find_by_addr (&connections[conn_idx].rr_map_list_header, seq);
  if (rrmap_info != NULL) {
    rr = rrmap_info->rr;
    if (!rr->is_session) {
      RemoveEntryList (&rrmap_info->Link);
      FreePool (rrmap_info);
    }
  }
  mutex_exit (bhm_rrmap);

  rrmap_dump (&connections[conn_idx].rr_map_list_header);
  return rr;
}

static bh_response_record* addr2record (int conn_idx, BH_U64 seq)
{
  bh_response_record* rr = NULL;
  RR_MAP_INFO *rrmap_info;

  rrmap_info = rrmap_find_by_addr (&connections[conn_idx].rr_map_list_header, seq);
  if (rrmap_info != NULL) {
    rr = rrmap_info->rr;
  }

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "addr2record(seq: %x): %x\n", seq, rr));
  return rr;
}

void destroy_session (bh_response_record* session)
{
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "destroy_session %x\n", session));
  if (session->buffer != NULL ) {
    BHFREE (session->buffer);
    session->buffer = NULL;
  }
  BHFREE (session);
}

bh_response_record* session_enter (int conn_idx, BH_U64 seq, int lock_session)
{
  bh_response_record* session = NULL;
  RR_MAP_INFO *rrmap_info;

  mutex_enter (connections[conn_idx].bhm_rrmap);
  rrmap_info = rrmap_find_by_addr (&connections[conn_idx].rr_map_list_header, seq);
  if (rrmap_info) {
    if (rrmap_info->rr->is_session &&
        !rrmap_info->rr->killed) {
      session = rrmap_info->rr;
      if (session->count < MAX_SESSION_LIMIT) {
        session->count++;
      } else {
        session = NULL;
      }
    }
  }
  mutex_exit (connections[conn_idx].bhm_rrmap);

  if (session && lock_session) {
    mutex_enter (session->session_lock);
    //check whether session has been killed before session operation
    if (session->killed) {
      session_exit (conn_idx,session, seq, 1);
      session = NULL;
    }
  }
  return session;
}

void session_exit (int conn_idx, bh_response_record* session, BH_U64 seq, int unlock_session)
{
  int closeVMConn = 0;

  mutex_enter (connections[conn_idx].bhm_rrmap);
  session->count--;
  if (session->count == 0 && session->killed) {
    rrmap_remove (conn_idx, seq);
    if (unlock_session) mutex_exit (session->session_lock);
    destroy_session (session);
    if (conn_idx > CONN_IDX_IVM) closeVMConn = 1;
  } else {
    if (unlock_session) mutex_exit (session->session_lock);
  }
  mutex_exit (connections[conn_idx].bhm_rrmap);

  if (closeVMConn) {
    //remove the VM conn counter of this session:only for connected SVM
    bh_do_closeVM (conn_idx);
  }
}

void session_close (int conn_idx, bh_response_record* session, BH_U64 seq, int unlock_session)
{
  int closeVMConn = 0;

  mutex_enter (connections[conn_idx].bhm_rrmap);
  session->count--;
  if (session->count == 0) {
    rrmap_remove (conn_idx, seq);
    if (unlock_session) mutex_exit (session->session_lock);
    destroy_session (session);
    if (conn_idx > CONN_IDX_IVM) closeVMConn = 1;
  } else {
    session->killed = 1;
    if (unlock_session) mutex_exit (session->session_lock);
  }
  mutex_exit (connections[conn_idx].bhm_rrmap);

  if (closeVMConn) {
    //remove the VM conn counter of this session:only for connected SVM
    bh_do_closeVM (conn_idx);
  }
}

void session_kill (int conn_idx, bh_response_record* session, BH_U64 seq, int callerIsSVMRecvThread)
{
  int closeVMConn = 0;

  mutex_enter (connections[conn_idx].bhm_rrmap);
  session->killed = 1;
  if (session->count == 0) {
    rrmap_remove (conn_idx, seq);
    destroy_session (session);
    if (conn_idx > CONN_IDX_IVM) closeVMConn = 1;
  }
  mutex_exit (connections[conn_idx].bhm_rrmap);

  if (closeVMConn) {
    //decrease the VM conn counter of this session:only for connected SVM
    //Note: callerIsSVMRecvThread is always 1 in current impl, as caller of this func is only bh_recv_message().
    if (!callerIsSVMRecvThread) {
      bh_do_closeVM (conn_idx);
    } else {
      mutex_enter (connections[conn_idx].lock);
      if (connections[conn_idx].conn_count == 1) {
        //this is the last vm connection to be closed, so startup new thread to close svm,
        //    otherwise the recv_thread will deadlock.
      } else {
        connections[conn_idx].conn_count --;
      }
      mutex_exit (connections[conn_idx].lock);
    }
  }
}

int is_bhp_inited (void)
{
  return (init_state == INITED);
}

BH_RET
bh_transport_send (
  int conn_idx,
  void* buffer,
  UINT32 length
  )
{
  int ret;
  ret = bhp_tx_itf.pfnSend ((unsigned int) conn_idx, (unsigned char*) (buffer), (unsigned int) (length));
  return ret;
}

BH_RET
bh_transport_recv (
  int conn_idx,
  void* buffer,
  UINT32 length
  )
{
  int ret;
  UINT32 got;

  got = length;
  ret = bhp_tx_itf.pfnRecv ((unsigned int) conn_idx, (unsigned char*) (buffer), (unsigned int *) (&got));
  if (ret == BH_SUCCESS && got == length) {
    return BH_SUCCESS;
  } else {
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_transport_recv(length: %x) fail, ret: %x\n", length, ret));
    return ret;
  }
}

#if BEIHAI_ENABLE_SVM
static BH_RET bh_proxy_launch_vm (BH_SDID sdid, int* heci_port)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_launch_vm_cmd* cmd = (bhp_launch_vm_cmd*) h->cmd;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;

  if (heci_port == NULL) return BPE_INVALID_PARAMS;

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (bh_response_record));

  h->id = BHP_CMD_LAUNCH_VM;
  cmd->sdid = sdid;

  ret = bh_cmd_transfer (CONN_IDX_LAUNCHER, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, rrmap_add (CONN_IDX_LAUNCHER,&rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  if (ret == BH_SUCCESS) {
    if (rr.buffer != NULL && rr.length == sizeof (bhp_launch_vm_response)) {
      bhp_launch_vm_response* resp = (bhp_launch_vm_response*) rr.buffer;
      *heci_port = resp->heci_port;
    } else {
      ret = BPE_MESSAGE_ILLEGAL;
    }
  }
  if (rr.buffer) BHFREE (rr.buffer);

  return ret;
}
#endif

BH_RET bh_do_openVM (BH_SDID sdid, int* conn_idx, int mode)
{
#if (BEIHAI_ENABLE_SVM)
    BH_RET ret = BPE_SERVICE_UNAVAILABLE;
  int heci_port = 0;
#endif

  if (conn_idx == NULL) return BPE_INVALID_PARAMS;
  if (CompareMem (&sdid, &g_isd_uuid,sizeof (BH_SDID)) == 0) {
    *conn_idx = CONN_IDX_IVM;
    return BH_SUCCESS;
  }
#if (!BEIHAI_ENABLE_SVM)
    return BPE_INVALID_PARAMS;
#else
  mutex_enter (connections[CONN_IDX_SVM].lock);
  if (connections[CONN_IDX_SVM].handle > 0
      && CompareMem (&connections[CONN_IDX_SVM].sdid, &sdid, sizeof (BH_SDID)) == 0) {
    unsigned int val = (++connections[CONN_IDX_SVM].conn_count);
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "svm conn_count inc = %d\n", val));
    ret = BH_SUCCESS;
  }
  if (mode == BHP_OPEN_VM_QUERY_MODE || ret == BH_SUCCESS) {
    //simply query vm conn status or sd-id match
    goto cleanup;
  }
  do {
    //sd-id has checked and not match
    if (connections[CONN_IDX_SVM].handle > 0) {
      if (connections[CONN_IDX_SVM].conn_count > 0) {
        ret = BPE_OUT_OF_RESOURCE;
        break;
      }
      //should not happen
      ret = BPE_INTERNAL_ERROR;
      break;
    }
    //need launch vm and connect
    //1: launch vm
    ret = bh_proxy_launch_vm (sdid, &heci_port);
    if (ret != BH_SUCCESS) {
      DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "BHP-open-vm lauchVM failed, ret=0x%x.\n", ret));
      ret = BPE_OUT_OF_RESOURCE;
      break;
    }
    //2: connect to the heci-port
    ret = bh_do_connect (CONN_IDX_SVM, heci_port);
    if (ret != BH_SUCCESS) {
      //NOTE: this should not happen. If it happens, host record will
      //be inconsistent with fw status.
      //TODO: Should we ask Launcher to terminate SVM?
      DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "BHP-open-vm connectSVM failed, ret=0x%x, heci_port=%d.\n", ret, heci_port));
      break;
    }
    //3: update bhp record
    connections[CONN_IDX_SVM].sdid = sdid;
    connections[CONN_IDX_SVM].conn_count = 1;
    ret = BH_SUCCESS;
  } while (0);

cleanup:
  mutex_exit (connections[CONN_IDX_SVM].lock);
  if (ret == BH_SUCCESS) *conn_idx = CONN_IDX_SVM;

  return ret;
#endif
}

BH_RET bh_do_closeVM (int conn_idx)
{
  BH_RET ret = BH_SUCCESS;
  unsigned int count = 0;

  //only close connected SVM
  if (conn_idx <= CONN_IDX_IVM || connections[conn_idx].handle == 0) return ret;

  mutex_enter (connections[conn_idx].lock);
  if (connections[conn_idx].conn_count == 0) {
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "[BHP]FATAL: svm conn_idx %d, closeVM called when conn_count is already 0 \n", conn_idx));
  }
  count = (--connections[conn_idx].conn_count);
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "svm conn_idx %d, conn_count dec = %d \n", conn_idx, count));
  if (count == 0) {
    ret = bh_proxy_reset_svm (conn_idx);
  }
  mutex_exit (connections[conn_idx].lock);

  return ret;
}

BH_RET bh_send_message (int conn_idx, void* cmd, unsigned int clen, const void* data, unsigned int dlen, BH_U64 seq)
{
  BH_RET ret = BH_SUCCESS;
  bh_response_record *rr = addr2record (conn_idx, seq);
  bhp_command_header *h = NULL;

  if (!rr) {
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "[BHP] FATAL: rr record NULL with seq=%d.\n", (BH_U32) seq));
    return BPE_INTERNAL_ERROR;
  }
  mutex_enter (connections[conn_idx].bhm_send);
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "enter bh_send_message %x %d\n", rr, clen+dlen));

  if (clen < sizeof (bhp_command_header) || !cmd || !rr) return BPE_INVALID_PARAMS;

  rr->buffer = NULL;
  rr->length = 0;
  CopyMem (cmd, BHP_MSG_CMD_MAGIC, BHP_MSG_MAGIC_LENGTH);

  h = (bhp_command_header*) cmd;
  h->h.length = clen + dlen;
  h->seq = seq;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "bh_message_header\n"));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " magic:  %08x\n", *((UINT32 *) h->h.magic)));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " length: %08x\n", h->h.length));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " seq:    %x (size: %x)\n", h->seq, sizeof (BH_U64)));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " id:     %x (size: %x)\n", h->id, sizeof (bhp_command_id)));

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "bh_send_message, send cmd (clen: %x)\n", clen));
  ret = bh_transport_send (conn_idx, (void *) cmd, clen);
  if (ret == BH_SUCCESS && dlen>0) {
    DEBUG_BEIHAI_LIB ((DEBUG_INFO, "bh_send_message, send data (dlen: %x)\n", dlen));
    ret = bh_transport_send (conn_idx, (void *) data, dlen);
  }

  if (ret != BH_SUCCESS)  {
    rrmap_remove (conn_idx, seq);
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "done bh_send_message %x %d\n", rr, clen+dlen));

  if (ret == BH_SUCCESS) {
    mutex_exit (connections[conn_idx].bhm_send);
  } else {
    mutex_exit (connections[conn_idx].bhm_send);
  }
  return ret;
}

BH_RET bh_recv_message (int conn_idx, BH_U64 *seq)
{
  bhp_response_header headbuf;
  bhp_response_header *head = &headbuf;
  char* data = NULL;
  unsigned int dlen = 0;
  BH_RET ret = BH_SUCCESS;
  bh_response_record* rr = NULL;
  int sessionKilled;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "bh_recv_message(%x)\n", conn_idx));

  ret = bh_transport_recv (connections[conn_idx].handle, (char*) head, sizeof (bhp_response_header));
  if (ret != BH_SUCCESS) return ret;

    /* check magic */
  if (CompareMem (BHP_MSG_RESPONSE_MAGIC, head->h.magic, BHP_MSG_MAGIC_LENGTH) != 0) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "magic header fail\n"));
    return BPE_MESSAGE_ILLEGAL;
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "bh_response_header\n"));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " magic:  %08x\n", *((UINT32 *) head->h.magic)));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " length: %08x\n", head->h.length));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " seq:    %x (size: %x)\n", head->seq, sizeof (BH_U64)));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " addr:   %x (size: %x)\n", head->addr, sizeof (BH_U64)));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " code:   %x (size: %x)\n", head->code, sizeof (BH_RET)));

  // verify rr
  rr = rrmap_remove (conn_idx, head->seq);
  if (!rr) {
    DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Beihai RECV invalid rr idx-%d 0x%I64x\n", conn_idx, head->seq));
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "enter bh_recv_message 0x%x 0x%I64x %d\n", rr, head->seq, head->code));

  if (head->h.length > sizeof (bhp_response_header)) {
    dlen = head->h.length - sizeof (bhp_response_header);
    data = (char*) BHP_Malloc (dlen);
    ret = bh_transport_recv (connections[conn_idx].handle, data, dlen);
    if (ret == BH_SUCCESS && data == NULL) ret = BPE_OUT_OF_MEMORY;
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "exit bh_recv_message %x %I64x %d\n", rr, head->seq, ret));

  if (rr) {
    rr->buffer = data;
    rr->length = dlen;

    if (ret == BH_SUCCESS) rr->code = (BH_RET) head->code;
    else rr->code = ret;

    if (head->addr) rr->addr = head->addr;

    sessionKilled = (rr->is_session &&
                     (rr->code == BHE_WD_TIMEOUT
                      || rr->code == BHE_UNCAUGHT_EXCEPTION
                      || rr->code == BHE_APPLET_CRASHED));
    if (sessionKilled) rr->killed = 1; //set killed flag before wake up send_wait thread.
    if (sessionKilled) {
      //VM instance abnormal exit, and no corresponding send_wait thread.
      session_kill (conn_idx, rr, head->seq, 1);
    }
  } else {
    if (data) BHP_Free (data);
  }

  if (seq) {
    *seq = head->seq;
  }

  return ret;
}

static BH_RET bh_transport_init (const BHP_TRANSPORT* context, BHP_INFO *info)
{
  BH_RET ret = BH_SUCCESS;
  EFI_STATUS  Status;

  gpBhTransport = (BHP_TRANSPORT *) context;
  if (gpBhTransport == NULL) {
    Status = MeiInit ();
    if (EFI_ERROR (Status)) {
      DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "JhisInit fail, MeiInit error: %r.\n", Status));
      return BPE_INTERNAL_ERROR;
    }

    if (MeInfoDone == FALSE) {
      Status = MeiGetInfo (&MeInfo);
      if (EFI_ERROR (Status)) {
        DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "JhisInit fail, MeiGetInfo error: %r.\n", Status));
        return BPE_INTERNAL_ERROR;
      }
      MeInfoDone = TRUE;
    }

    if (info != NULL) {
      info->Major = MeInfo.Major;
      info->Minor = MeInfo.Minor;
      info->Hotfix = MeInfo.Hotfix;
      info->Build = MeInfo.Build;
      info->PluginType = MeInfo.MeFwType;
    }
  } else {
    CopyMem (&bhp_tx_itf, context, sizeof (BHP_TRANSPORT));
  }

  if (bhp_tx_itf.pfnConnect == NULL
      || bhp_tx_itf.pfnClose == NULL
      || bhp_tx_itf.pfnSend == NULL
      || bhp_tx_itf.pfnRecv == NULL) {
    DEBUG_BEIHAI_LIB ((DEBUG_INFO, "FATAL error: Invalid transport function.\n"));
    ret = BPE_INVALID_PARAMS;
  }

  return ret;
}

static BH_RET bh_transport_exit (
  VOID
  )
{
  BH_RET ret = BH_SUCCESS;
  EFI_STATUS  Status;

  if (gpBhTransport == NULL) {
    Status = MeiDeinit ();
    if (EFI_ERROR (Status)) {
      DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "JhisDeInit fail, MeiDeinit error: %r.\n", Status));
      ret = BPE_INTERNAL_ERROR;
    }
  }
  gpBhTransport = NULL;

  return ret;
}

static BH_RET bh_do_connect (int conn_idx)
{
  BH_RET ret = BH_SUCCESS;
  int temp_ret =0;
  unsigned int handle = 0;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_do_connect(%x)\n", conn_idx));
  connections[conn_idx].handle = 0;
  connections[conn_idx].conn_count = 0;
  InitializeListHead (&connections[conn_idx].rr_map_list_header);

  ZeroMem (&connections[conn_idx].sdid, sizeof (BH_SDID));

  temp_ret = bhp_tx_itf.pfnConnect (conn_idx, &handle);
  if (temp_ret != 0) {
    ret = BPE_CONNECT_FAILED;
    DEBUG_BEIHAI_LIB ((DEBUG_INFO, "bh_do_connect() failed: idx=%d\n", conn_idx));
    goto cleanup;
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "bh_do_connect, conn_idx: %x, handle: %x\n", conn_idx, handle));
  connections[conn_idx].handle = handle;
cleanup:
  if (ret != BH_SUCCESS) {
    if (connections[conn_idx].handle != 0) {
      bhp_tx_itf.pfnClose (connections[conn_idx].handle);
      connections[conn_idx].handle = 0;
      //here: recv_thread creation must be failed, and don't need to terminate it.
    }
  }

  return ret;
}

static BH_RET bh_do_disconnect (int conn_idx)
{
  BH_RET ret = BH_SUCCESS;
  RR_MAP_INFO           *rrmap_info;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_do_disconnect(%x) handle: %x\n", conn_idx, connections[conn_idx].handle));
  if (connections[conn_idx].handle != 0) {
    bhp_tx_itf.pfnClose (connections[conn_idx].handle);
  }
  connections[conn_idx].conn_count = 0;
  connections[conn_idx].handle = 0;

  while (!IsListEmpty (&connections[conn_idx].rr_map_list_header)) {
    rrmap_info = CR (
                   connections[conn_idx].rr_map_list_header.ForwardLink,
                   RR_MAP_INFO,
                   Link,
                   RR_MAP_INFO_SIGNATURE
                   );
    RemoveEntryList (&rrmap_info->Link);
    FreePool (rrmap_info);
  }

  InitializeListHead (&connections[conn_idx].rr_map_list_header);
  ZeroMem (&connections[conn_idx].sdid,sizeof (BH_SDID));

  return ret;
}

static BH_RET bh_connections_init (void)
{
  BH_RET ret = BH_SUCCESS;
  int i = 0;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_connections_init\n"));

  for (i=CONN_IDX_START;i<MAX_CONNECTIONS;i++) {
    connections[i].conn_count = 0;
    connections[i].handle = 0;
    InitializeListHead (&connections[i].rr_map_list_header);
  }

  for (i=CONN_IDX_START; i<CONN_IDX_SVM; i++) {
    //connect to predefined heci ports, except SVM
    ret = bh_do_connect (i);
    if (ret != BH_SUCCESS) break;
  }

  if (ret != BH_SUCCESS) {
    for (i=CONN_IDX_START; i<CONN_IDX_SVM; i++) {
      if (connections[i].handle != 0) {
        bhp_tx_itf.pfnClose (connections[i].handle);
      }
    }
  }

  return ret;
}

static void bh_connections_deinit (
  VOID
  )
{
  int i=0;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_connections_deinit\n"));

  for (i=CONN_IDX_START; i<MAX_CONNECTIONS; i++) {
    bh_do_disconnect (i);
  }
}

static BH_RET bh_proxy_reset (int conn_idx)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_proxy_reset\n"));

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (bh_response_record));

  h->id = BHP_CMD_RESET;

  ret = bh_cmd_transfer (conn_idx, (char*) h, sizeof (*h), NULL, 0, rrmap_add (conn_idx, &rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  if (rr.buffer) BHFREE (rr.buffer);

  return ret;
}

static BH_RET bh_proxy_reset_launcher (unsigned int* count, int** ports)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;
  bhp_reset_launcher_response* resp;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_proxy_reset_launcher\n"));

  if (count == NULL || ports == NULL) return BPE_INVALID_PARAMS;

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (bh_response_record));

  h->id = BHP_CMD_RESET;

  ret = bh_cmd_transfer (CONN_IDX_LAUNCHER,(char*) h, sizeof (*h), NULL, 0, rrmap_add (CONN_IDX_LAUNCHER, &rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  resp = NULL;
  *ports = NULL;
  *count = 0;
  do {
    if (ret != BH_SUCCESS) break;
    if (rr.buffer == NULL
        || rr.length < sizeof (bhp_reset_launcher_response)) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }
    resp = (bhp_reset_launcher_response*) rr.buffer;
    if (resp->count == 0) break;

    if (rr.length != sizeof (int) * resp->count + sizeof (bhp_reset_launcher_response)) {
      ret = BPE_MESSAGE_ILLEGAL;
      break;
    }
    *ports = (int*) BHP_Malloc (sizeof (int) * resp->count);
    if (*ports == NULL) {
      ret = BPE_OUT_OF_MEMORY;
      break;
    }
    CopyMem ((void*)*ports, resp->vm_heci_port_list, resp->count * sizeof (int));
    *count = resp->count;

    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_proxy_reset_launcher, dump port info, count: %x\n", *count));
    DbgRawdataDump (*ports, *count * sizeof (int));
  } while (0);

  if (rr.buffer) BHP_Free (rr.buffer);

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_proxy_reset_launcher done, ret: %x, count: %x\n", ret, *count));
  return ret;
}

static BH_RET bh_proxy_close_vm (BH_SDID sdid)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bhp_close_vm_cmd* cmd = (bhp_close_vm_cmd*) h->cmd;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (bh_response_record));

  h->id = BHP_CMD_CLOSE_VM;
  cmd->sdid = sdid;

  ret = bh_cmd_transfer (CONN_IDX_LAUNCHER, (char*) h, sizeof (*h) + sizeof (*cmd), NULL, 0, rrmap_add (CONN_IDX_LAUNCHER,&rr));
  if (ret == BH_SUCCESS) ret = rr.code;

  if (rr.buffer) BHFREE (rr.buffer);

  return ret;
}

BH_RET bh_proxy_reset_svm (int conn_idx)
{
  BH_RET ret = BPE_INVALID_PARAMS;
    BH_SDID sdid = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

  if (conn_idx <= CONN_IDX_IVM || connections[conn_idx].handle == 0) return ret;
  sdid = connections[conn_idx].sdid;
  //send RESET cmd to VM
  ret = bh_proxy_reset (conn_idx);
  if (ret == BH_SUCCESS) {
    ret = bh_proxy_close_vm (sdid);
  }
  return ret;
}

/*
 * function: bh_proxy_get_isd()
 *   get isd uuid from SDM in Firmware side.
 */
static BH_RET bh_proxy_get_isd (void)
{
  char cmdbuf[CMDBUF_SIZE];
  bhp_command_header* h = (bhp_command_header*) cmdbuf;
  bh_response_record rr;
  BH_RET ret = BH_SUCCESS;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai get_isd 0x%x\n", &rr));

  ZeroMem (cmdbuf, sizeof (cmdbuf));
  ZeroMem (&rr, sizeof (bh_response_record));

  h->id = BHP_CMD_GET_ISD;

  ret = bh_cmd_transfer (CONN_IDX_SDM, (char*) h, sizeof (*h), NULL, 0, rrmap_add (CONN_IDX_SDM, &rr));
  if (ret == BH_SUCCESS)  ret = rr.code;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Beihai get_isd 0x%x ret 0x%x\n", &rr, rr.code));

  if (ret == BH_SUCCESS) {
    if (rr.buffer && rr.length == sizeof (bhp_get_isd_response)) {
      bhp_get_isd_response* resp = (bhp_get_isd_response*) rr.buffer;
      g_isd_uuid = resp->sdid;
    } else {
      ret = BPE_MESSAGE_ILLEGAL;
    }
  }

  if (rr.buffer) BHP_Free (rr.buffer);
  return ret;
}


BH_RET bh_cmd_transfer (int conn_idx, void* cmd, UINT32 clen, const void* data, UINT32 dlen, BH_U64 seq)
{
  BH_RET ret;
  UINTN       RetryCount;
  BH_U64 SeqResponse;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_cmd_transfer\n"));

  ret = bh_send_message (conn_idx, cmd, clen, data, dlen, seq);
  if (ret == BH_SUCCESS) {
    RetryCount = 0;
    do {
      ret = bh_recv_message (conn_idx, &SeqResponse);
      if (ret == BH_SUCCESS) {
        DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_cmd_transfer, SeqResponse: %x\n", SeqResponse));

        if (SeqResponse == seq) {
          DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "bh_cmd_transfer success at RetryCount=%x\n", RetryCount));
          break;
        }
      }
      RetryCount++;
    } while (RetryCount < MAX_RETRY_COUNT);

    if (RetryCount == MAX_RETRY_COUNT) {
      DEBUG_BEIHAI_LIB ((DEBUG_INFO, "bh_cmd_transfer fail, max retry achieve\n"));
      ret = HAL_TIMED_OUT;
    }
  }

  return ret;
}


void *BHP_Malloc (UINTN Size)
{
  if (Size != 0) {
    return AllocateZeroPool (Size);
  }
  return NULL;
}

void BHP_Free (void * p)
{
  if (p != NULL) {
    FreePool (p);
  }
}


BH_RET BHP_Init (const BHP_TRANSPORT* transport, BHP_INFO *info)
{
  BH_RET ret = BH_SUCCESS;
  unsigned int count_svm = 0;
  int* ports_svm = NULL;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_Init <<<\n"));

  if (init_state == INITED) {
    ret = BPE_INITIALIZED_ALREADY;
    goto cleanup;
  }

  //step 1: init connections to each process
  ret = bh_transport_init (transport, info);
  if (ret == BH_SUCCESS) ret = bh_connections_init ();
  if (ret != BH_SUCCESS) {
    goto cleanup;
  }

  //step 2: send reset cmd to each process in correct order
  ret = bh_proxy_reset (CONN_IDX_SDM);

  if (ret == BH_SUCCESS) ret = bh_proxy_reset_launcher (&count_svm, &ports_svm);
  if (ret == BH_SUCCESS && count_svm > 0) {
    //we have at most 1 svm
    ret = bh_do_connect (CONN_IDX_SVM);
    if (ret == BH_SUCCESS) {
      ret = bh_proxy_reset_svm (CONN_IDX_SVM);
    }
  }
  if (ports_svm) BHFREE (ports_svm);
  if (ret == BH_SUCCESS) ret = bh_proxy_reset (CONN_IDX_IVM);

  //step 3: get isd-uuid from SDM
  if (ret == BH_SUCCESS) {
    ret = bh_proxy_get_isd ();
  }

  if (ret != BH_SUCCESS) {
    bh_connections_deinit ();
  } else {
    //this assignment is atomic operation
    init_state = INITED;
  }

cleanup:
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_Init done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_Deinit (void)
{
  BH_RET ret = BH_SUCCESS;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_Deinit <<<\n"));
  if (!is_bhp_inited ()) return BPE_NOT_INIT;
  mutex_enter (bhm_gInit);
  if (init_state == INITED) {
    BHP_Reset(); //reset fw and let SVM(if any) exit
    bh_connections_deinit ();
    init_state = DEINITED;
    ret = bh_transport_exit ();
  } else {
    ret = BPE_NOT_INIT;
  }
  mutex_exit (bhm_gInit);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_Deinit done, ret: %x\n\n", ret));
  return ret;
}

BH_RET BHP_Reset (void)
{
  BH_RET ret = BH_SUCCESS;
  BH_RET ret_tmp = BH_SUCCESS;
  unsigned int count_svm = 0;
  int* ports_svm = NULL;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> BHP_Reset <<<\n"));
  if (!is_bhp_inited ()) return BPE_NOT_INIT;
  mutex_enter (bhm_gInit);

  //disconnect svm and unblock all user threads to avoid the recursive reset_svm() below
  bh_do_disconnect (CONN_IDX_SVM);
  //send reset cmd to each process in correct order
  ret_tmp = bh_proxy_reset (CONN_IDX_SDM);
  if (ret_tmp != BH_SUCCESS) ret = ret_tmp;

  ret_tmp = bh_proxy_reset_launcher (&count_svm, &ports_svm);
  if (ret_tmp == BH_SUCCESS && count_svm > 0) {
    //we have at most 1 svm
    // int port = ports_svm[0];
    ret_tmp = bh_do_connect(CONN_IDX_SVM);//, port);
    if (ret_tmp == BH_SUCCESS) {
      ret_tmp = bh_proxy_reset_svm (CONN_IDX_SVM);
    }
  }
  if (ports_svm) BHFREE (ports_svm);
  if (ret_tmp != BH_SUCCESS) ret = ret_tmp;

  ret_tmp = bh_proxy_reset (CONN_IDX_IVM);
  if (ret_tmp != BH_SUCCESS) ret = ret_tmp;

  mutex_exit (bhm_gInit);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "BHP_Reset done, ret: %x\n\n", ret));
  return ret;
}

