/** @file
  Defines exported interfaces for Beihai library.

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

#ifndef __BEIHAIPLUGIN_ME11_H__
#define __BEIHAIPLUGIN_ME11_H__


#ifdef _MSC_VER
#pragma warning ( disable: 4200 ) // zero-sized array in struct/union
#endif

#include <Protocol/JhiProtocol.h>
#include "bh_shared_types.h"
#include "bhp_exp.h"     // Beihai
#include "bh_acp_exp.h"  // ACP file support
#include "bhp_heci.h"
#include "bh_shared_conf.h"

typedef struct {
  BH_RET code;          //the response code from firmware
  unsigned int length;  //length of the response buffer
  void *buffer;         //the response buffer
  BH_U64 addr;          //remote address in firmware
  int is_session;       //whether this record relates with session
  int killed;           //whether this session is killed or not, valid only for is_session is 1
  unsigned int count;   //the count of users who are using this session, valid only for is_session is 1
} bh_response_record;

typedef struct {
  volatile unsigned int handle;       //physical connection handle
  LIST_ENTRY rr_map_list_header;
  volatile unsigned int conn_count;   //VM connection counter, only valid for VM
  BH_SDID sdid;                       //the sd id it serves, only valid for VM
} bh_connection_item;

//maximum concurrent activities on one session
#define MAX_SESSION_LIMIT 20

//heci command header buffer size in bytes
#define CMDBUF_SIZE 100

typedef enum {
    CONN_IDX_START = 0,
    CONN_IDX_IVM = 0,
    CONN_IDX_SDM = 1,
    CONN_IDX_LAUNCHER = 2,
    CONN_IDX_SVM = 3,
    MAX_CONNECTIONS
} BHP_CONN_IDX_T; // redefine value (refer to ME_CLIENT_ID (Mei.h))

typedef enum {
    DEINITED = 0,
    INITED = 1,
} BHP_STATE_T;


//whether BHP is inited or not
int is_bhp_inited(void);

//Add a rr to rrmap and return a new seq number.
BH_U64 rrmap_add(int conn_idx, bh_response_record* rr);

//session enter with session handle seq
bh_response_record* session_enter(int conn_idx, BH_U64 seq, int lock_session);

//session exit
void session_exit(int conn_idx, bh_response_record* session, BH_U64 seq, int unlock_session);

//session close
void session_close(int conn_idx, bh_response_record* session, BH_U64 seq, int unlock_session);

//send one message through heci
//BH_RET bh_send_message (int conn_idx, void* cmd, unsigned int clen, const void* data, unsigned int dlen, BH_U64 seq);
BH_RET bh_cmd_transfer (int conn_idx, void* cmd, UINT32 clen, const void* data, UINT32 dlen, BH_U64 seq);

enum {
    BHP_OPEN_VM_QUERY_MODE = 0,
    BHP_OPEN_VM_NORMAL_MODE = 1
};

//open vm connection for sdid and increase vm connection counter by 1
BH_RET bh_do_openVM (BH_SDID sdid, int* conn_idx, int mode);

//decrease vm connection counter by 1
BH_RET bh_do_closeVM(int conn_idx);



void *BHP_Malloc (UINTN Size);
void BHP_Free(void * p);
#define BHMALLOC(s)     BHP_Malloc(s)
#define BHFREE(p)       BHP_Free(p)
#define mutex_enter(s)
#define mutex_exit(s)



#endif

