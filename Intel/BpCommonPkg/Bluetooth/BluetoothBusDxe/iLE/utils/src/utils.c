/** @file
  Utility function implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "osa_types.h"
#include "config_host.h"
#include "utils.h"
#include "error_code.h"

#if (TARGET_LINUX == TRUE)
#include <stdlib.h>
#endif

#if (TARGET_UEFI == TRUE)
#include "hci_host.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/Cpu.h>

STATIC UINT64 mFreq, mBaseTick;
extern EFI_GUID gEfiCpuArchProtocolGuid;
#endif

#if ((TARGET_LINUX == TRUE) && (TARGET_ANDROID == FALSE))
#include <execinfo.h>
#endif

#if (TARGET_THREADX_RW == TRUE)
#include "tx_app_define.h"
#include "os_block_pool.h"
#endif


#define MODULE_DBG_LVL UTILS_DBG_LVL
#include "log.h"

#define HCI_LE_CONNECTION_INTERVAL_MIN                              0x0006
#define HCI_LE_CONNECTION_INTERVAL_MAX                              0x0C80
#define HCI_LE_CONNECTION_LATENCY_MIN                               0x0000
#define HCI_LE_CONNECTION_LATENCY_MAX                               0x01F3
#define HCI_LE_CONNECTION_SUPERVISION_TIMEOUT_MIN                   0x000A
#define HCI_LE_CONNECTION_SUPERVISION_TIMEOUT_MAX                   0x0C80
#define HCI_LE_ADVERTISING_INTERVAL_MIN                             0x0020
#define HCI_LE_ADVERTISING_INTERVAL_MIN_NONCONN_SCANNABLE           0x00A0
#define HCI_LE_ADVERTISING_INTERVAL_MAX                             0x4000
#define HCI_LE_SCAN_INTERVAL_MIN                                    0x0004
#define HCI_LE_SCAN_INTERVAL_MAX                                    0x4000
#define HCI_LE_SCAN_WINDOW_MIN                                      0x0004
#define HCI_LE_SCAN_WINDOW_MAX                                      0x4000

#define HCI_LE_ADVERTISING_TYPE_ADV_IND			0x00
#define HCI_LE_ADVERTISING_TYPE_ADV_DIRECT_IND	0x01
#define HCI_LE_ADVERTISING_TYPE_ADV_SCAN_IND	0x02
#define HCI_LE_ADVERTISING_TYPE_ADV_NONCONN_IND	0x03

osa_timer_static_t HCI_CMD_TIMER[2];
osa_timer_isr_list_t HCI_CMD_TIMER_ISR[2];

osa_timer_static_t GAP_REMOTE_CMD_TIMER[1];
osa_timer_isr_list_t GAP_REMOTE_CMD_TIMER_ISR[1];

osa_timer_static_t GAP_ADV_TIMER[1];
osa_timer_isr_list_t GAP_ADV_TIMER_ISR[1];

osa_timer_static_t GAP_SCAN_TIMER[1];
osa_timer_isr_list_t GAP_SCAN_TIMER_ISR[1];

osa_timer_static_t GAP_RPA_GEN_TIMER[1];
osa_timer_isr_list_t GAP_RPA_GEN_TIMER_ISR[1];

osa_timer_static_t ATT_SRVR_TIMER[MAX_NUM_CONNECTED_DEVICE];
osa_timer_isr_list_t ATT_SRVR_TIMER_ISR[MAX_NUM_CONNECTED_DEVICE];

osa_timer_static_t ATT_CLNT_TIMER[MAX_NUM_CONNECTED_DEVICE];
osa_timer_isr_list_t ATT_CLNT_TIMER_ISR[MAX_NUM_CONNECTED_DEVICE];

osa_timer_static_t A4WP_SRV_TIMER[1];
osa_timer_isr_list_t A4WP_SRV_TIMER_ISR[1];

#if (TARGET_THREADX_RW == FALSE)
osa_thread_t STACK_MAIN_THREAD_VAR;
osa_thread_t USERIAL_READ_THREAD_VAR;
osa_thread_t A4WP_THREAD_VAR;
osa_thread_t HRP_THREAD_VAR;
osa_thread_t FMP_THREAD_VAR;
osa_thread_t FMP_SRV_THREAD_VAR;
osa_thread_t HOGP_THREAD_VAR;
#endif

#if (MEM_MGMT_INTERNAL == FALSE)
#if (PROFILING ==TRUE)
UINT32 stack_max_size, app_max_size, l2cap_max_size;
UINT32 stack_size, app_size, l2cap_size;
#endif
#endif

/**********************************************************
 *
 * Memory management abstraction layer
 *
 * ********************************************************/
/**
 * Call this function to allocate a memory chunk dynamically from process heap.
 * After allocation this function initialises the memory with zeros
 *
 * Currently it is maximum size to allocate is bounded by 16 bit size.
 */
void* alloc(UINT16 num_of_bytes)
{
	void *p = NULL;
#if ((LE_STACK_PROFILING == TRUE) &&(LE_STACK_MEM_POOL_PROFILING == TRUE) && (TARGET_THREADX == TRUE) )
	log_time_stamp(TIME_STACK_ALLOC_ENTRY);
#endif
	if (num_of_bytes <= 0)
		return NULL ;
#if (TARGET_THREADX_RW == TRUE)
	p = os_mallocRetention(num_of_bytes);
#elif (MEM_MGMT_INTERNAL == TRUE)
	p = stack_mem_alloc(num_of_bytes);
#elif (PROFILING == TRUE)
	p = malloc(num_of_bytes + sizeof(UINT32));
#else
	p = malloc(num_of_bytes);
#endif

	if (p == NULL )
	{
		logex("FATAL ERROR. MALLOC FAILED for bytes: %d", num_of_bytes);
		return NULL ;
	}
#if (PROFILING ==TRUE)
	UINT32 *q = (UINT32*) p;
	q[0] = num_of_bytes;
	stack_size += num_of_bytes;
	q++;
	p = (void*) q;
	if (stack_max_size < stack_size)
		stack_max_size = stack_size;
#endif
	memset(p, 0, num_of_bytes);
#if ((LE_STACK_PROFILING == TRUE) &&(LE_STACK_MEM_POOL_PROFILING == TRUE)&& (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_STACK_ALLOC_RETURN);
#endif
	return p;
}

void* app_alloc(UINT16 num_of_bytes)
{
	void *p = NULL;
#if ((LE_STACK_PROFILING == TRUE) &&(LE_STACK_MEM_POOL_PROFILING == TRUE)&& (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_APP_ALLOC_ENTRY);
#endif
	if (num_of_bytes <= 0)
		return NULL ;
#if (TARGET_THREADX_RW == TRUE)
	p = os_malloc(num_of_bytes);//OS_BLE_DATA_SIZE);
#elif (MEM_MGMT_INTERNAL == TRUE)
	p = app_mem_alloc(num_of_bytes);
#elif (PROFILING == TRUE)
	p = malloc(num_of_bytes + sizeof(UINT32));
#else
	p = malloc(num_of_bytes);
#endif

	if (p == NULL )
	{
		logex("FATAL ERROR. MALLOC FAILED for bytes: %d", num_of_bytes);
		return NULL ;
	}
#if (PROFILING == TRUE)
	UINT32 *q = (UINT32*) p;
	q[0] = num_of_bytes;
	app_size += num_of_bytes;
	q++;
	p = (void*) q;
	if (app_max_size < app_size)
		app_max_size = app_size;
#endif
	memset(p, 0, num_of_bytes);
#if ((LE_STACK_PROFILING == TRUE) &&(LE_STACK_MEM_POOL_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_APP_ALLOC_RETURN);
#endif
	return p;
}

void* l2cap_alloc(UINT16 num_of_bytes)
{
	void *p = NULL;
#if ((LE_STACK_PROFILING == TRUE) &&(LE_STACK_MEM_POOL_PROFILING == TRUE))
	log_time_stamp(TIME_L2CAP_ALLOC_ENTRY);
#endif
	if (num_of_bytes <= 0)
		return NULL ;

#if (TARGET_THREADX_RW == TRUE)
		p = os_malloc(num_of_bytes);
#elif (MEM_MGMT_INTERNAL == TRUE)
	p = l2cap_mem_alloc(num_of_bytes);
#elif (PROFILING == TRUE)
	p = malloc(num_of_bytes + sizeof(UINT32));
#else
	p = malloc(num_of_bytes);
#endif

	if (p == NULL )
	{
		logex("FATAL ERROR. MALLOC FAILED for bytes: %d", num_of_bytes);
		return NULL ;
	}

#if (PROFILING == TRUE)
	UINT32 *q = (UINT32*) p;
	q[0] = num_of_bytes;
	l2cap_size += num_of_bytes;
	q++;
	p = (void*) q;
	if (l2cap_max_size < l2cap_size)
		l2cap_max_size = l2cap_size;
#endif
	memset(p, 0, num_of_bytes);
#if ((LE_STACK_PROFILING == TRUE) &&(LE_STACK_MEM_POOL_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_L2CAP_ALLOC_RETURN);
#endif
	return p;
}

void* hci_stack_alloc(UINT16 num_of_bytes)
{
	UINT8 *p = NULL;
#if (TARGET_THREADX_RW == TRUE)
	if (num_of_bytes <= 0)
		return NULL ;
	//tx_block_allocate(&block_pool_0, (VOID **) &p, TX_NO_WAIT);
	p = os_malloc(num_of_bytes);// OS_BLE_DATA_SIZE);
#else
	p = alloc(num_of_bytes);
#endif
	if (p == NULL )
	{
		logex("FATAL ERROR. MALLOC FAILED.%d", num_of_bytes);
		return NULL ;
	}

	return p;
}

void dealloc(void* buffer)
{
	if (buffer == NULL )
		return;

#if (PROFILING == TRUE)
	UINT32 *q = (UINT32*) buffer;
	q--;
	stack_size -= q[0];
	buffer = (void*) q;
#endif

#if (MEM_MGMT_INTERNAL == TRUE)
	stack_mem_mfree(buffer);
#elif (TARGET_THREADX_RW == TRUE)
	os_mfree(buffer);
#else
	free(buffer);
#endif
}

void app_dealloc(void* buffer)
{
	if (buffer == NULL )
		return;
#if (PROFILING == TRUE)
	UINT32 *q = (UINT32*) buffer;
	q--;
	app_size -= q[0];
	buffer = (void*) q;
#endif

#if (TARGET_THREADX_RW == TRUE)
	os_mfree(buffer);
#elif (MEM_MGMT_INTERNAL == TRUE)
	app_mem_free(buffer);
#else
	free(buffer);
#endif
}

void l2cap_dealloc(void* buffer)
{
	if (buffer == NULL )
		return;
#if (PROFILING == TRUE)
	UINT32 *q = (UINT32*) buffer;
	q--;
	l2cap_size -= q[0];
	buffer = (void*) q;
#endif

#if (TARGET_THREADX_RW == TRUE)
	os_mfree(buffer);
#elif (MEM_MGMT_INTERNAL == TRUE)
	l2cap_mem_free(buffer);
#else
	free(buffer);
#endif
}

/**********************************************************
 *
 * Single linked list utility
 *
 * ********************************************************/
static ll_node_t* create_new_ll_node(void* data)
{
	ll_node_t* new_node = (ll_node_t*) alloc (sizeof (ll_node_t));

	if (!new_node)
		return NULL;

	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

void* get_first_node_data(ll_node_t* head)
{
	if (head)
		return head->data;
	return NULL;
}

INT8 append_ll_node(ll_node_t** head, void* data, UINT8 max_list_len)
{
	UINT8 list_len = 1;
	ll_node_t *temp_head = *head;
	if (!*head)
	{
		*head = create_new_ll_node(data);
		return STATUS_SUCCESS;
	}
	/* Get to the last but one node */
	while (temp_head->next)
	{
		temp_head = temp_head->next;
		list_len++;
	}
	if (max_list_len == 0 || (max_list_len && list_len < max_list_len))
	{
		temp_head->next = create_new_ll_node(data);
		return STATUS_SUCCESS;
	}
	return STATUS_ERR_INSUFFICIENT_RESOURCES;
}

void* get_next_ll_node_data(ll_node_t *head, void* data)
{
	while(head)
	{
		if (head->data == data)
		{
			return ((head->next != NULL) ? head->next->data : NULL);
		}
		head = head->next;
	}
	return NULL;
}

ll_node_t* get_next_ll_node(ll_node_t *cur_node)
{
	if(cur_node != NULL)
		return cur_node->next;

	return NULL;
}

/*
 * Function returns the data of the node. The caller
 * should deallocate this as this was allocated by the
 * caller module.
 */
void* delete_first_ll_node(ll_node_t **head)
{
	ll_node_t *temp_head = *head;
	void* ret_data = NULL;
	if (!temp_head)
		return ret_data;
	if (!temp_head->next)
	{
		ret_data = temp_head->data;
		dealloc (temp_head);
		*head = NULL;
		return ret_data;
	}
	ret_data = temp_head->data;
	*head = (*head)->next;
	dealloc(temp_head);
	return ret_data;
}

/**
 * Caution this doesn't delete the data portion of the list nodes.
 */
void delete_list(ll_node_t **head)
{
	ll_node_t *temp = NULL;
	ll_node_t *t_head = *head;
	while(t_head)
	{
		temp = t_head;
		t_head = t_head->next;
		dealloc(temp);
	}
}

typedef void (*show_ll_node_func_t)(void* data);
void show_ll_nodes(ll_node_t *head, show_ll_node_func_t show_ll_node_func)
{
	while(head)
	{
		if (show_ll_node_func)
			show_ll_node_func(head->data);
		head = head->next;
	}
}

/**********************************************************
 *
 * Queue utility to be used in stack,
 *
 * ********************************************************/
#if 0
#if (UTILS_DBG_LVL >= DBG_LVL_INFO)
void display(queue_t *q)
{
	int i;
	logi("front:%d rear:%d\n", q->rear, q->front);
	logi("The queue elements are:");
	for (i = q->front; i <= q->rear; i++)
	{
		if (i != -1)
			logi("%d ", *(int*) q->array[i]);
	}
}
#endif
#endif

void* alloc_queue_element(UINT16 size, UINT8 type)
{
	queue_elem_t *elem = NULL;
	if ((UINT32)size + sizeof(queue_elem_t) > (UINT32)0xFFFF)
		return NULL;
	switch(type)
	{
		case RETENTION_ALLOC:
			elem = (queue_elem_t*)alloc(sizeof(queue_elem_t) + size);
			break;
		case HCI_ALLOC:
			elem = (queue_elem_t*)hci_stack_alloc(sizeof(queue_elem_t) + size);
			break;
		case L2CAP_ALLOC:
			elem = (queue_elem_t*)l2cap_alloc(sizeof(queue_elem_t) + size);
			break;
		case APP_ALLOC:
			elem = (queue_elem_t*)app_alloc(sizeof(queue_elem_t) + size);
			break;
	}
	if(elem == NULL)
		return NULL;
	else
		return (void*)elem->param;
}
void dealloc_queue_element(void *queue_element)
{
	dealloc(((UINT8*)queue_element - sizeof(queue_elem_t)));
}
INT8 init_q(queue_t *q)
{
	if (!q)
		return STATUS_ERR_INVALID_PARAM;
	osa_mutex_create(&q->q_mutex);
	q->gaurd = TRUE;
	q->list_head = NULL;
	return STATUS_SUCCESS;
}

INT8 init_no_guard_q(queue_internal_t *q)
{
	if (!q)
		return STATUS_ERR_INVALID_PARAM;
	q->gaurd = FALSE;
	q->list_head = NULL;
	return STATUS_SUCCESS;
}

INT8 enqueue(void *queue, void* token)
{
	queue_t *q;
	queue_elem_t *elem;
	queue_elem_t *temp_head;

	q = (queue_t*)queue;
	if (q->gaurd == TRUE)
		osa_mutex_get(&q->q_mutex);
	elem = (queue_elem_t*)((UINT8*)token - sizeof(queue_elem_t));
	elem->next = NULL;
	temp_head = q->list_head;
	if(!temp_head)
		q->list_head = elem;
	else
	{
		while(temp_head->next)temp_head = temp_head->next;
		temp_head->next = elem;
	}
	if (q->gaurd == TRUE)
		osa_mutex_put(&q->q_mutex);
	return STATUS_SUCCESS;
}

void* pick_front(void *queue)
{
	queue_t *q;
	void* data;

	if (!queue)
		return NULL;
	q = (queue_t*)queue;
	if (q->gaurd == TRUE)
		osa_mutex_get(&q->q_mutex);
	data = (q->list_head == NULL)? NULL : q->list_head->param;
	if (q->gaurd == TRUE)
		osa_mutex_put(&q->q_mutex);

	return data;
}

void* dequeue(void *queue)
{
	queue_t *q;
	void* data;

	if (!queue)
		return NULL;
	q = (queue_t*)queue;
	if (q->gaurd == TRUE)
		osa_mutex_get(&q->q_mutex);
	data = (q->list_head == NULL)? NULL : q->list_head->param;
	if(data != NULL)
		q->list_head = q->list_head->next;
	if (q->gaurd == TRUE)
		osa_mutex_put(&q->q_mutex);
	return data;
}

void cleanup_q(void *queue)
{
	queue_t *q;

	if (!queue)
		return ;
	q = (queue_t*)queue;
	if (q->gaurd == TRUE)
	{

		osa_mutex_delete(&q->q_mutex);
	}
}

/**********************************************************
 *
 * Other utility functions
 *
 * ********************************************************/
void util_convert_uuid_to_uuid128(uuid_t *src)
{
	UINT8 base_uuid_array[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
	if (src->length == UUID_128BIT_TYPE_LEN)
		return;
	if (src->length == UUID_16BIT_TYPE_LEN)
	{
		base_uuid_array[2] = (UINT8)((src->value.uuid16 & 0xFF00) >> 8);
		base_uuid_array[3] = (UINT8)((src->value.uuid16 & 0x00FF));
	}
	else if(src->length == UUID_32BIT_TYPE_LEN)
	{
		base_uuid_array[0] = (UINT8)((src->value.uuid32 & 0xFF000000) >> 24);
		base_uuid_array[1] = (UINT8)((src->value.uuid32 & 0x00FF0000) >> 16);
		base_uuid_array[2] = (UINT8)((src->value.uuid32 & 0x0000FF00) >> 8);
		base_uuid_array[3] = (UINT8)(src->value.uuid32 & 0x000000FF);
	}
	src->length = UUID_128BIT_TYPE_LEN;
	memcpy (src->value.uuid128, base_uuid_array, UUID_128BIT_TYPE_LEN);
}

BOOLEAN uuidcmp(uuid_t *compare_uuid1, uuid_t *compare_uuid2)
{
	uuid_t uuid1;
	uuid_t uuid2;

	if (compare_uuid1->length == compare_uuid2->length)
		return COMPARE_UUID(compare_uuid1, compare_uuid2);

	memcpy (&uuid1, compare_uuid1, sizeof (uuid_t));
	memcpy (&uuid2, compare_uuid2, sizeof (uuid_t));
	util_convert_uuid_to_uuid128(&uuid1);
	util_convert_uuid_to_uuid128(&uuid2);
	return COMPARE_UUID((&uuid1), (&uuid2));
}

void get_uuid_from_stream(UINT8 *data, UINT8 data_len, uuid_t *uuid)
{
	uuid->length = data_len;
	switch (data_len)
	{
	case UUID_16BIT_TYPE_LEN:
	{
		STREAM_TO_UINT16(uuid->value.uuid16, data);
	}
		break;
	case UUID_32BIT_TYPE_LEN:
	{
		STREAM_TO_UINT32(uuid->value.uuid32, data);
	}
		break;
	case UUID_128BIT_TYPE_LEN:
	{
		REVERSE_STREAM_TO_ARRAY(uuid->value.uuid128, data, UUID_128BIT_TYPE_LEN);
	}
		break;
	default:
		uuid->length = 0;
	}
}

UINT8 get_uuid_from_stream2(UINT8 *data, uuid_t *uuid)
{
	STREAM_TO_UINT8(uuid->length, data);
	switch (uuid->length)
	{
	case UUID_16BIT_TYPE_LEN:
		STREAM_TO_UINT16(uuid->value.uuid16, data);
		break;
	case UUID_32BIT_TYPE_LEN:
		STREAM_TO_UINT32(uuid->value.uuid32, data);
		break;
	case UUID_128BIT_TYPE_LEN:
		REVERSE_STREAM_TO_ARRAY(uuid->value.uuid128, data, UUID_128BIT_TYPE_LEN);
		break;
	default:
		uuid->length = 0;
	}
	return (uuid->length + sizeof(UINT8));
}

#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))

static UINT8 LogTimeIndex = 0;
LogTimeT stack_LogTime [MAX_TIME_STAMP_LOG]={0};

void log_time_stamp(EventType event)
{
  log_time_stamp_with_opcode(event,0);
}

void log_time_stamp_with_opcode (EventType evtId, u16 Opcode)
{
	UINT32 u32SltCnt, u32BitCnt;
	stack_LogTime[LogTimeIndex].eventId = evtId;
	stack_LogTime[LogTimeIndex].Opcode = Opcode;
	REG_GET_LCP_BMC(MIRRORED, NO_PRIO, Sltcnt, u32SltCnt);
	REG_GET_LCP_BMC(MIRRORED, NO_PRIO, Bitcnt, u32BitCnt);
	stack_LogTime[LogTimeIndex].u32timeMs = ((u32SltCnt)*625)+u32BitCnt;
	if(++LogTimeIndex >= MAX_TIME_STAMP_LOG)
		LogTimeIndex = 0;
}
#endif

#if (TARGET_LINUX == TRUE)

#include <sys/time.h>
long long unsigned int stack_start_time;

void record_start_time()
{
	struct timeval detail_time;
	gettimeofday(&detail_time, NULL);
	stack_start_time = (detail_time.tv_sec*(uint64_t)1000000+detail_time.tv_usec) / 1000; // in ms
}

double gettimestamp()
{
	struct timeval detail_time;
	gettimeofday(&detail_time, NULL);
	long long unsigned int cur_time = (detail_time.tv_sec*(uint64_t)1000000+detail_time.tv_usec) / 1000; // in ms
	return (double)(cur_time - stack_start_time);
}

#endif /* TARGET_LINUX == TRUE */

#if (TARGET_UEFI == TRUE)

void record_start_time()
{
	UINT64                   TimerPeriod;
	EFI_CPU_ARCH_PROTOCOL    *gCpu = NULL;

	gBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **) &gCpu);
	gCpu->GetTimerValue (gCpu, 0, &mBaseTick, &TimerPeriod);

	//
	// The timer period is in femtosecond (1 femtosecond is 1e-15 second).
	// So 1e+12 is divided by timer period to produce the freq in ticks/ms.
	//
	mFreq = DivU64x64Remainder (1000000000000ULL, TimerPeriod, NULL);
}

void gettimestamp(UINT64 *_sec, UINT64 *_msec)
{
	*_msec = DivU64x64Remainder(AsmReadTsc() - mBaseTick, mFreq, NULL);
	*_sec = DivU64x64Remainder(*_msec, 1000U, _msec);

	return;
}

#endif /* TARGET_UEFI == TRUE */

#if (TARGET_UEFI == TRUE)

CHAR16* str_duplicate (CHAR16 *src)
{
  CHAR16  *dest;
  UINTN   size;

  size  = StrSize (src);
  dest  = alloc ((UINT16)size);
  ASSERT (dest != NULL);
  if (dest != NULL)
  {
    CopyMem (dest, src, size);
  }

  return dest;
}

osa_file_handle_t open_root (EFI_HANDLE DeviceHandle)
{
  EFI_STATUS status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *volume;
  osa_file_handle_t file;

  file = NULL;

  status = gBS->HandleProtocol ( DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID *) &volume);
  if (!EFI_ERROR (status))
  {
    status = volume->OpenVolume ( volume, &file);
  }

  return EFI_ERROR (status) ? NULL : file;
}

CHAR16* append_file_name (CHAR16  *str1, CHAR16  *str2)
{
  UINTN   size1;
  UINTN   size2;
  UINTN   buffer_size;
  CHAR16  *str;
  CHAR16  *tmp_str;
  CHAR16  *ptr;
  CHAR16  *last_slash;

  size1 = StrSize (str1);
  size2 = StrSize (str2);
  buffer_size = size1 + size2 + sizeof (CHAR16);
  str   = alloc((UINT16)buffer_size);
  if (!str) {
	loge("Alloc failed for %d bytes", (UINT16)buffer_size);
	return str;
  }

  tmp_str = alloc ((UINT16)buffer_size);
  ASSERT (tmp_str != NULL);

  StrCatS (str, buffer_size / sizeof (CHAR16), str1);

  if (!((*str == '\\') && (*(str + 1) == 0)))
  {
    StrCatS (str, buffer_size / sizeof (CHAR16), L"\\");
  }

  StrCatS (str, buffer_size / sizeof (CHAR16), str2);

  ptr       = str;
  last_slash = str;
  while (*ptr != 0)
  {
    if (*ptr == '\\' && *(ptr + 1) == '.' && *(ptr + 2) == '.' && *(ptr + 3) == L'\\')
    {
      //
      // Convert "\Name\..\" to "\"
      // DO NOT convert the .. if it is at the end of the string. This will
      // break the .. behavior in changing directories.
      //

      //
      // Use TmpStr as a backup, as StrCpyS in BaseLib does not handle copy of two strings
      // that overlap.
      //
      StrCpyS (tmp_str, buffer_size / sizeof (CHAR16), ptr + 3);
      StrCpyS (last_slash, buffer_size / sizeof (CHAR16), tmp_str);
      ptr = last_slash;
    }
    else if (*ptr == '\\' && *(ptr + 1) == '.' && *(ptr + 2) == '\\')
    {
      //
      // Convert a "\.\" to a "\"
      //

      //
      // Use TmpStr as a backup, as StrCpyS in BaseLib does not handle copy of two strings
      // that overlap.
      //
      StrCpyS (tmp_str, buffer_size / sizeof (CHAR16), ptr + 2);
      StrCpyS (ptr, buffer_size / sizeof (CHAR16), tmp_str);
      ptr = last_slash;
    }
    else if (*ptr == '\\')
    {
    	last_slash = ptr;
    }

    ptr++;
  }

  dealloc(tmp_str);

  return str;
}

void init_log_files(EFI_FILE_HANDLE root_file_handle)
{
#if ((FILE_LOGGING == TRUE) || (BTSNOOPDISP_INCLUDED == TRUE))
	logd("Creating log files...");
	CHAR16 *file_path = str_duplicate (L"\\");
	EFI_HANDLE *simple_fs_handle = 0;
	UINTN no_handles;
	EFI_HANDLE *blk_io_handle;

	if (!root_file_handle)
	{
		gBS->LocateHandleBuffer(ByProtocol, &gEfiBlockIoProtocolGuid, NULL, &no_handles, &blk_io_handle);
		FreePool (blk_io_handle);
		gBS->LocateHandleBuffer(ByProtocol, &gEfiSimpleFileSystemProtocolGuid, NULL, &no_handles, &simple_fs_handle);
        	root_file_handle = open_root(simple_fs_handle[0]);
		ASSERT(root_file_handle != NULL);
	}

#if (FILE_LOGGING == TRUE)
	CHAR16 log_file_name[10];
	AsciiStrToUnicodeStrS("log.txt", log_file_name, sizeof(log_file_name) / sizeof(CHAR16));
	CHAR16 *final_log_file_name = append_file_name(file_path, log_file_name);
	if (!final_log_file_name)
	{
		loge("Failed to append Log File!");
		return;
	}
	root_file_handle->Open(root_file_handle, &log_file, final_log_file_name, EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0);
#endif

#if (BTSNOOPDISP_INCLUDED == TRUE)
	CHAR16 snoop_file_name[20];
	AsciiStrToUnicodeStrS("btsnoop.log", snoop_file_name, sizeof(snoop_file_name) / sizeof(CHAR16));
	CHAR16 *final_snoop_file_name = append_file_name(file_path, snoop_file_name);
	if (!final_snoop_file_name)
	{
		loge("Failed to append snoop File!");
		return;
	}
	root_file_handle->Open(root_file_handle, &snoop_file, final_snoop_file_name, EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0);
	btsnoop_log_open(BTSNOOPDISP_LOG_FILENAME);
#endif

	logd("Log file opened %d %p %p", status, log_file, snoop_file);

	if (simple_fs_handle)
		FreePool(simple_fs_handle);
#endif /* (FILE_LOGGING == TRUE) || (BTSNOOPDISP_INCLUDED == TRUE) */
}

#endif

void dump_stack()
{
#if (TARGET_THREADX == FALSE && TARGET_ANDROID == FALSE && TARGET_THREADX_RW == FALSE && TARGET_UEFI == FALSE)
	int j, nptrs;
#define SIZE 100
	void *buffer[SIZE];
	char **strings;

	nptrs = backtrace(buffer, SIZE);

	strings = backtrace_symbols(buffer, nptrs);
	if (strings == NULL)
		return;

	printf("******************** < STACK TRACE BEGIN > ********************\n");
	for (j = 1; j < nptrs; j++)
		printf("%s\n", strings[j]);
	printf("******************** <  STACK TRACE END  > ********************\n");

	free(strings);
#endif
}

BOOLEAN is_conn_params_valid(UINT16 scan_int, UINT16 scan_win, UINT16 conn_int_min, UINT16 conn_int_max, UINT16 conn_lat, UINT16 sup_timeout)
{
	if (scan_int < HCI_LE_SCAN_INTERVAL_MIN || scan_int > HCI_LE_SCAN_INTERVAL_MAX)
		return FALSE;
	if (scan_win < HCI_LE_SCAN_WINDOW_MIN || scan_win > HCI_LE_SCAN_WINDOW_MAX)
		return FALSE;
	if (scan_win > scan_int)
		return FALSE;
	if (conn_int_min < HCI_LE_CONNECTION_INTERVAL_MIN || conn_int_min > HCI_LE_CONNECTION_INTERVAL_MAX)
		return FALSE;
	if (conn_int_max < HCI_LE_CONNECTION_INTERVAL_MIN || conn_int_max > HCI_LE_CONNECTION_INTERVAL_MAX)
		return FALSE;
	if (conn_int_min > conn_int_max)
		return FALSE;
	if (conn_lat > HCI_LE_CONNECTION_LATENCY_MAX)
		return FALSE;
	if (sup_timeout < HCI_LE_CONNECTION_SUPERVISION_TIMEOUT_MIN || sup_timeout > HCI_LE_CONNECTION_SUPERVISION_TIMEOUT_MAX)
		return FALSE;
	if ((10 * sup_timeout <= (((125 * conn_int_max) / 100) * (conn_lat + 1) * 2)))
		return FALSE;
	return TRUE;
}

BOOLEAN is_scan_params_valid(UINT16 scan_int, UINT16 scan_win)
{
	if (scan_int && (scan_int < HCI_LE_SCAN_INTERVAL_MIN || scan_int > HCI_LE_SCAN_INTERVAL_MAX))
		return FALSE;
	if (scan_win && (scan_win < HCI_LE_SCAN_WINDOW_MIN || scan_win > HCI_LE_SCAN_WINDOW_MAX))
		return FALSE;
	if (scan_int && (scan_win > scan_int))
		return FALSE;
	return TRUE;
}

BOOLEAN is_adv_params_valid(UINT16 adv_int_min, UINT16 adv_int_max, UINT8 type)
{
	UINT16 int_min = HCI_LE_ADVERTISING_INTERVAL_MIN;

	if (type == HCI_LE_ADVERTISING_TYPE_ADV_SCAN_IND || type == HCI_LE_ADVERTISING_TYPE_ADV_NONCONN_IND)
		int_min = HCI_LE_ADVERTISING_INTERVAL_MIN_NONCONN_SCANNABLE;
	if ((type != HCI_LE_ADVERTISING_TYPE_ADV_DIRECT_IND) && (adv_int_min < int_min || adv_int_max > HCI_LE_ADVERTISING_INTERVAL_MAX || adv_int_min > adv_int_max))
		return FALSE;
	return TRUE;
}

UINT8 get_appid_from_transid(trans_id_t trans_id)
{
	UINT8 app_id = ((trans_id & LLA_ID_BIT_MASK) >> (SIZE_OF_HLA_OP_ID_BITS + SIZE_OF_ROUTE_ID_BITS));
	return (app_id < MAX_NUMBER_OF_APP ? app_id : MAX_NUMBER_OF_APP);

}
void add_appid_to_trans_id(trans_id_t *trans_id, UINT8 app_handle)
{
	*trans_id = (*(trans_id) & ~(LLA_ID_BIT_MASK)) | ((app_handle & LLA_ID_VALUE_BITS) << (SIZE_OF_HLA_OP_ID_BITS + SIZE_OF_ROUTE_ID_BITS));
}


