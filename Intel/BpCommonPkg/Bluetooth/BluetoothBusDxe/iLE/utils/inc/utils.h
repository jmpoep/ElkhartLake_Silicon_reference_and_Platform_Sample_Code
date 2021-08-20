/** @file
  Utils header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef UTILS_H
#define UTILS_H

#include "bt_types.h"
#include "osa_types.h"

#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
#include "bmc_reg.h"
#endif

#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))

#define MAX_TIME_STAMP_LOG 200

typedef enum
{
   TIME_STACK_INIT_STARTED = 0,
   TIME_STACK_MEM_INIT_START,
   TIME_STACK_MEM_INIT_DONE,
   TIME_STACK_HCI_INIT_START,
   TIME_STACK_HCI_INIT_DONE,
   TIME_STACK_GAP_INIT_START,
   TIME_STACK_GAP_INIT_DONE,
   TIME_STACK_L2CAP_INIT_START,
   TIME_STACK_L2CAP_INIT_DONE,
   TIME_STACK_ATT_INIT_START,
   TIME_STACK_ATT_INIT_DONE,
   TIME_STACK_DM_INIT_START,
   TIME_STACK_DM_INIT_DONE,
   TIME_STACK_PM_INIT_START,
   TIME_STACK_PM_INIT_DONE,
   TIME_STACK_SM_INIT_START,
   TIME_STACK_SM_INIT_DONE,
   TIME_STACK_INIT_CB_START,
   TIME_STACK_INIT_CB_DONE,
   TIME_STACK_APP_REG_START,
   TIME_STACK_APP_REG_DONE,
   TIME_STACK_APP_REG_CB_START,
   TIME_STACK_APP_REG_CB_DONE,
   TIME_STACK_SRV_PARAM_INIT_START,
   TIME_STACK_SRV_PARAM_INIT_DONE,
   TIME_STACK_GAP_SRV_REG_START,
   TIME_STACK_GAP_SRV_REG_DONE,
   TIME_STACK_GATT_SRV_REG_START,
   TIME_STACK_GATT_SRV_REG_DONE,
   TIME_STACK_SRV_START_START,
   TIME_STACK_SRV_START_DONE,
   TIME_STACK_ADD_SRV_START,
   TIME_STACK_ADD_SRV_DONE,
   TIME_STACK_ADD_SRV_CB_START,
   TIME_STACK_ADD_SRV_CB_DONE,
   TIME_STACK_ADD_CHAR_START,
   TIME_STACK_ADD_CHAR_DONE,
   TIME_STACK_ADD_DESC_START,
   TIME_STACK_ADD_DESC_DONE,
   TIME_STACK_ADD_CHAR_CB_START,
   TIME_STACK_ADD_CHAR_CB_DONE,
   TIME_BLE_STACK_INIT_COMPLETED,
   TIME_HCI_RECV_DATA,
   TIME_HCI_SEND_DATA,
   TIME_ATT_RECV_DATA,
   TIME_ATT_SEND_DATA,
   TIME_HCI_CMD_SENT,
   TIME_HCI_EVT_RECVD,
   TIME_A4WP_PROFILE_INIT_STARTED,
   TIME_A4WP_PROFILE_INIT_COMPLETED,
   TIME_A4WP_ADVT_START_REQ,
   TIME_A4WP_SET_STATIC_PARAM_REQ,
   TIME_A4WP_SET_DYNAMIC_PARAM_REQ,
   TIME_A4WP_ATTR_READ_REQ,
   TIME_A4WP_ATTR_READ_RESP,
   TIME_A4WP_ATTR_WRITE_REQ,
   TIME_A4WP_ATTR_WRITE_RESP,
   TIME_A4WP_IND_CFM_REQ,
   TIME_A4WP_IND_CFM_RESP,
   TIME_APP_ALLOC_ENTRY,
   TIME_APP_ALLOC_RETURN,
   TIME_L2CAP_ALLOC_ENTRY,
   TIME_L2CAP_ALLOC_RETURN,
   TIME_STACK_ALLOC_ENTRY,
   TIME_STACK_ALLOC_RETURN,
   TIME_APP_DEALLOC_ENTRY,
   TIME_APP_DEALLOC_RETURN,
   TIME_L2CAP_DEALLOC_ENTRY,
   TIME_L2CAP_DEALLOC_RETURN,
   TIME_STACK_DEALLOC_ENTRY,
   TIME_STACK_DEALLOC_RETURN,
   TIME_STACK_PROFILING_ID_MAX,
   TIME_A4WP_FSM_LE_STACK_INIT_CALLED,
   TIME_A4WP_FSM_LE_STACK_INIT_RETURNED,
   TIME_A4WP_FSM_LE_STACK_INIT_COMPLETED,
   TIME_A4WP_FSM_LE_STACK_INIT_CB,
   TIME_A4WP_FSM_APP_REGISTERED_CB,
   TIME_A4WP_FSM_START_ADVERTISEMENT_CALLED,
   TIME_A4WP_FSM_ADVERTISEMENT_STARTED,
   TIME_A4WP_FSM_TIMEOUT_EVT_HANDLE,
   TIME_A4WP_FSM_WCDETECTED_EVT_HANDLE,
   TIME_A4WP_READ_CTRLR_INFO_CALLED,
   TIME_A4WP_WRITE_CONTROLLER_INFO_CALLED,
   TIME_A4WP_WRITE_ADV_PARAMETERS,
   TIME_A4WP_WRITE_ADV_DATA,
   TIME_A4WP_WRITE_SCAN_RESP_DATA,
}EventType;

typedef struct
{
	EventType eventId;
	//UINT32 u32BitCnt;
	//UINT32 u32SltCnt;
	UINT32 u32timeMs;
	UINT16 Opcode;
}LogTimeT;

extern void log_time_stamp(EventType event);

extern void log_time_stamp_with_opcode(EventType event, u16 Opcode);
#endif


#if (TARGET_LINUX == TRUE || TARGET_THREADX_RW == TRUE)
#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))
#endif

#define TRUNCATE_TO_16BIT_LENGTH(_len, _val) ((UINT16) MIN((UINT32)(_len) + (UINT32)(_val), (UINT32)0xFFFF) - (_val))

#define INVALID_INDEX -1

#define USE(x) (void)x


extern osa_timer_static_t HCI_CMD_TIMER[2];
extern osa_timer_isr_list_t HCI_CMD_TIMER_ISR[2];

extern osa_timer_static_t GAP_REMOTE_CMD_TIMER[1];
extern osa_timer_isr_list_t GAP_REMOTE_CMD_TIMER_ISR[1];

extern osa_timer_static_t GAP_ADV_TIMER[1];
extern osa_timer_isr_list_t GAP_ADV_TIMER_ISR[1];

extern osa_timer_static_t GAP_SCAN_TIMER[1];
extern osa_timer_isr_list_t GAP_SCAN_TIMER_ISR[1];

extern osa_timer_static_t GAP_RPA_GEN_TIMER[1];
extern osa_timer_isr_list_t GAP_RPA_GEN_TIMER_ISR[1];

extern osa_timer_static_t ATT_SRVR_TIMER[MAX_NUM_CONNECTED_DEVICE];
extern osa_timer_isr_list_t ATT_SRVR_TIMER_ISR[MAX_NUM_CONNECTED_DEVICE];

extern osa_timer_static_t ATT_CLNT_TIMER[MAX_NUM_CONNECTED_DEVICE];
extern osa_timer_isr_list_t ATT_CLNT_TIMER_ISR[MAX_NUM_CONNECTED_DEVICE];

extern osa_timer_static_t A4WP_SRV_TIMER[1];
extern osa_timer_isr_list_t A4WP_SRV_TIMER_ISR[1];

extern osa_thread_t STACK_MAIN_THREAD_VAR;
extern osa_thread_t USERIAL_READ_THREAD_VAR;
extern osa_thread_t A4WP_THREAD_VAR;
extern osa_thread_t HRP_THREAD_VAR;
extern osa_thread_t FMP_THREAD_VAR;
extern osa_thread_t FMP_SRV_THREAD_VAR;
extern osa_thread_t HOGP_THREAD_VAR;

#define RETENTION_ALLOC 	0
#define HCI_ALLOC 			1
#define L2CAP_ALLOC 		2
#define APP_ALLOC 			3

typedef struct __ll_node_t
{
	struct __ll_node_t *next;
	void *data;
} ll_node_t;

typedef struct __queue_elem_t
{
	struct __queue_elem_t *next;
	UINT32 param[0];
}queue_elem_t;

typedef struct
{
    queue_elem_t *list_head;
    BOOLEAN gaurd;
    osa_mutex_t q_mutex;
} queue_t;

typedef struct
{
	queue_elem_t *list_head;
	BOOLEAN gaurd;
} queue_internal_t;
/**********************************************************
 *
 * Logging time management
 *
 * ********************************************************/
#if (TARGET_LINUX == TRUE)
void record_start_time();
double gettimestamp();
#endif

#if (TARGET_UEFI == TRUE)
void record_start_time();
void gettimestamp(UINT64 *_sec, UINT64 *_msec);
#endif

void dump_stack();

/**********************************************************
 *
 * Memory management abstraction layer
 *
 * ********************************************************/
extern UINT32 stack_max_size, app_max_size, l2cap_max_size;
void* hci_stack_alloc(UINT16 num_of_bytes);
void* alloc(UINT16 num_of_bytes);
void dealloc(void* buffer);

void* app_alloc(UINT16 num_of_bytes);
void app_dealloc(void* buffer);

void* l2cap_alloc(UINT16 num_of_bytes);
void l2cap_dealloc(void* buffer);

/**********************************************************
 *
 * Queue utility to be used in stack,
 *
 * ********************************************************/
INT8 init_q(queue_t *q);
INT8 init_no_guard_q(queue_internal_t *q);
void* alloc_queue_element(UINT16 size, UINT8 type);
void dealloc_queue_element(void *queue_element);
INT8 enqueue(void *q, void* token);
void* dequeue(void *q);
void* pick_front(void *q);
void cleanup_q(void *q);

/**********************************************************
 *
 * Linked list utility to be used in stack,
 *
 * ********************************************************/
INT8 append_ll_node(ll_node_t** head, void* data, UINT8 max_list_len);
ll_node_t* get_next_ll_node(ll_node_t *cur_node);
void delete_list(ll_node_t **head);

/* Convert UUID to 128bit UUID in Bluetooth format */
void util_convert_uuid_to_uuid128(uuid_t *src);
/* compare two UUIDs */
BOOLEAN uuidcmp(uuid_t *compare_uuid1, uuid_t *compare_uuid2);
void get_uuid_from_stream(UINT8 *data, UINT8 data_len, uuid_t *uuid);
UINT8 get_uuid_from_stream2(UINT8 *data, uuid_t *uuid);

/**********************************************************
 *
 * Memory manager utility functions and declarations
 *
 * ********************************************************/
#define MEM_BUF_POOL_HEADER_BITMAP_LEN	((MEM_BUF_POOL_MAX_LENGTH / 8) + 1) // Length in Bytes

#ifndef MEMORY_POOL_STAT_COLLECTION
#define MEMORY_POOL_STAT_COLLECTION	TRUE
#endif

typedef struct
{
	 UINT8 num_of_elem;	/* How many element buffer in this pool*/
#if (MEMORY_POOL_STAT_COLLECTION == TRUE)
	 UINT16 cur_used;	/* current used number of elements */
	 UINT16 max_used;	/* max used number of elements */
#endif
	 UINT8 usage_bitmap[MEM_BUF_POOL_HEADER_BITMAP_LEN];
	 UINT16 elem_len;	/* Length of each element */
	 void* base_ptr;
	 void* end_ptr; 	/* End pointer of this pool */
} mem_pool_header_t;

void mem_mgr_init();
UINT8* stack_mem_alloc(UINT16 size_bytes);
void stack_mem_free(UINT8* start);
UINT8* app_mem_alloc(UINT16 size_bytes);
void app_mem_free(UINT8* start);
UINT8* l2cap_mem_alloc(UINT16 size_bytes);
void l2cap_mem_free(UINT8* start);
void mem_mgr_cleanup();

#if (TARGET_UEFI == TRUE)
CHAR16* str_duplicate (CHAR16 *src);
osa_file_handle_t open_root (EFI_HANDLE DeviceHandle);
CHAR16* append_file_name (CHAR16  *str1, CHAR16  *str2);
void init_log_files(EFI_FILE_HANDLE root_file_handle);
#endif

/**********************************************************
 *
 * Parameter validation functions
 *
 * ********************************************************/
BOOLEAN is_conn_params_valid(UINT16 scan_int, UINT16 scan_win, UINT16 conn_int_min, UINT16 conn_int_max, UINT16 conn_lat, UINT16 sup_timeout);
BOOLEAN is_scan_params_valid(UINT16 scan_int, UINT16 scan_win);
BOOLEAN is_adv_params_valid(UINT16 adv_int_min, UINT16 adv_int_max, UINT8 type);

/**********************************************************
 * Transaction ID utility MACROs and # defines
 * ********************************************************/

#if TRANS_ID_SIZE_BYTES == 4	/* 32 bits */
    #define LLA_ID_BIT_MASK         (0xFF000000)
	#define ROUTE_ID_BIT_MASK	    (0x00FF0000)
	#define HLA_OP_ID_BIT_MASK	    (0x0000FFFF)

    #define ROUTE_ID_VALUE_BITS     (0xFF)
    #define LLA_ID_VALUE_BITS       (0xFF)
    #define HLA_OP_ID_VALUE_BITS    (0xFFFF)

    #define SIZE_OF_HLA_OP_ID_BITS  (16)
    #define SIZE_OF_LLA_ID_BITS     (8)
    #define SIZE_OF_ROUTE_ID_BITS   (8)

    #define INVALID_TRANS_ID		(0xFFFFFFFF)
    #define INVALID_HLA_OP_ID       (0xFFFF)
    #define INVALID_ROUTE_ID        (0xFF)
	#define TRANS_ID_TO_STREAM(p, id)  UINT32_TO_STREAM(p, id)
	#define STREAM_TO_TRANS_ID(id, p)  STREAM_TO_UINT32(id, p)

#elif TRANS_ID_SIZE_BYTES == 2	/* 16 bits */
    #define LLA_ID_BIT_MASK         (0xF000)
	#define ROUTE_ID_BIT_MASK	    (0x0F00)
	#define HLA_OP_ID_BIT_MASK	    (0x00FF)

    #define ROUTE_ID_VALUE_BITS     (0xF)
    #define LLA_ID_VALUE_BITS       (0xF)
    #define HLA_OP_ID_VALUE_BITS    (0xFF)

    #define SIZE_OF_HLA_OP_ID_BITS  (8)
    #define SIZE_OF_LLA_ID_BITS     (4)
    #define SIZE_OF_ROUTE_ID_BITS   (4)

    #define INVALID_TRANS_ID		(0xFFFF)
	#define INVALID_HLA_OP_ID       (0xFF)
    #define INVALID_ROUTE_ID        (0xF)
	#define TRANS_ID_TO_STREAM(p, id)  UINT16_TO_STREAM(p, id)
	#define STREAM_TO_TRANS_ID(id, p)  STREAM_TO_UINT16(id, p)

#else 								/* 8 bits */
    #define LLA_ID_BIT_MASK         (0x30)
	#define ROUTE_ID_BIT_MASK	    (0x03)
	#define HLA_OP_ID_BIT_MASK	    (0x0F)

    #define ROUTE_ID_VALUE_BITS     (0x3)
    #define LLA_ID_VALUE_BITS       (0x3)
    #define HLA_OP_ID_VALUE_BITS    (0xF)

    #define SIZE_OF_HLA_OP_ID_BITS  (4)
    #define SIZE_OF_LLA_ID_BITS     (2)
    #define SIZE_OF_ROUTE_ID_BITS   (2)

    #define INVALID_TRANS_ID		(0xFF)
    #define INVALID_HLA_OP_ID       (0xF)
    #define INVALID_ROUTE_ID        (0x3)
	#define TRANS_ID_TO_STREAM(p, id)  UINT8_TO_STREAM(p, id)
	#define STREAM_TO_TRANS_ID(id, p)  STREAM_TO_UINT8(id, p)

#endif
UINT8 get_appid_from_transid(trans_id_t trans_id);
void add_appid_to_trans_id(trans_id_t *trans_id, UINT8 app_handle);
#endif
