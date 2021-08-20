/** @file
  UEFI implementation for OSA.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "osa_types.h"
#include "device_struct.h"
#include "gap.h"
#include "l2cap.h"

#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

#define MODULE_DBG_LVL DBG_LVL_INFO
#include "log.h"

#define MAX_NUM_SIMULTANEOUS_TIMERS 10

EFI_FILE_HANDLE log_file = NULL;
EFI_FILE_HANDLE snoop_file = NULL;
UINT8 logbuf_count = 0;

typedef struct
{
	osa_timer_t tid;
	osa_timeout_func_t func;
	short val;
} timer_list_t;

static timer_list_t timer_list[MAX_NUM_SIMULTANEOUS_TIMERS];

// Note : Semophore function not yet implemented
int osa_semaphore_create(osa_semaphore_t *sem, unsigned int value)
{
	return 0;
}

int osa_semaphore_delete(osa_semaphore_t *sem)
{
	return 0;
}

int osa_semaphore_get(osa_semaphore_t *sem)
{
	return 0;
}

int osa_semaphore_put(osa_semaphore_t *sem)
{
	return 0;
}

int osa_mutex_create(osa_mutex_t *mutex)
{
	return 0;
}

int osa_mutex_delete(osa_mutex_t *mutex)
{
	return 0;
}

int osa_mutex_get(osa_mutex_t *mutex)
{
	*mutex = gBS->RaiseTPL(TPL_NOTIFY);
	return 0;
}

int osa_mutex_put(osa_mutex_t *mutex)
{
	gBS->RestoreTPL(*mutex);
	return 0;
}

BOOLEAN osa_is_cold_boot_cond()
{
	return TRUE;
}

void EFIAPI timer_expire_cb(osa_timer_t tid, void *context)
{
	UINT8 idx;
	for (idx = 0; idx < MAX_NUM_SIMULTANEOUS_TIMERS; idx++)
	{
		if (timer_list[idx].tid == tid)
		{
			timer_list[idx].tid = 0;
			timer_list[idx].func(timer_list[idx].val);
			timer_list[idx].val = 0;
			timer_list[idx].func = 0;
			break;
		}
	}
}

int osa_create_timer(osa_timer_t *tid, osa_timer_static_t *stid, osa_timer_isr_list_t *list, int list_count, osa_timeout_func_t func, short val)
{
	return (int)gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK, timer_expire_cb, NULL, tid);
}

int osa_start_timer(osa_timer_t *tid, osa_timer_static_t *stid, UINT64 timeout_in_ms, osa_timeout_func_t func, short val)
{
	UINT8 idx;
	for (idx = 0; idx < MAX_NUM_SIMULTANEOUS_TIMERS; idx++)
	{
		if (!timer_list[idx].func)
		{
			timer_list[idx].tid = *tid;
			timer_list[idx].val = val;
			timer_list[idx].func = func;
			gBS->SetTimer(*tid, TimerRelative, EFI_TIMER_PERIOD_MILLISECONDS(timeout_in_ms));
			break;
		}
	}
    return 0;
}

int osa_stop_timer(osa_timer_t *tid, osa_timer_static_t *stid, short val)
{
	UINT8 idx;
	for (idx = 0; idx < MAX_NUM_SIMULTANEOUS_TIMERS; idx++)
	{
		if (timer_list[idx].tid == *tid)
		{
			timer_list[idx].tid = 0;
			timer_list[idx].val = 0;
			timer_list[idx].func = 0;
			gBS->SetTimer(*tid, TimerCancel, 0);
			break;
		}
	}
	return 0;
}

int osa_delete_timer(osa_timer_t *tid, osa_timer_static_t *stid)
{
	return (int)gBS->CloseEvent(*tid);
}

int osa_is_timer_active(osa_timer_t *tid, osa_timer_static_t *stid, short val)
{
	UINT8 idx;
	for (idx = 0; idx < MAX_NUM_SIMULTANEOUS_TIMERS; idx++)
	{
		if (timer_list[idx].tid == *tid)
			return 1;
	}
	return 0;
}

int osa_get_timer_arg_val(osa_timer_arg_t arg)
{
	return arg;
}

int osa_sleep(int timeout_in_sec)
{
	gBS->Stall((UINTN)EFI_TIMER_PERIOD_SECONDS(timeout_in_sec));
	return 0;
}
void * osa_create_connected_device(UINT16 conn_handle)
{
	USE(conn_handle);
	return (void *)create_connected_device();
}
void osa_gap_setup_connection(UINT8 idx, UINT8 *remote_bdaddr, UINT8 addr_type)
{
	connected_device_t *device = NULL;
	g_local_adapter.connected_device[idx] = create_connected_device();
	device = g_local_adapter.connected_device[idx];
	device->idx = idx;
	memcpy(&device->bdaddr, remote_bdaddr, BD_ADDR_LEN);
	device->bdaddr_type = addr_type;
	device->l2cap_state = L2CAP_STATE_CLOSED;
	device->gap_connection_state = GAP_CONNECTION_STATE_ACL_CONNECTING;
}

void osa_delete_connected_device(UINT8 connected_device_list_idx)
{
	void *dev = g_local_adapter.connected_device[connected_device_list_idx];
	dealloc(dev);
}

void osa_restore_connected_devices(void)
{
}

void osa_save_acl_handle(UINT8 connected_device_list_idx, UINT16 conn_handle)
{
	USE(connected_device_list_idx);
	USE(conn_handle);
}

INT8 osa_gap_handle_command_status(UINT8 status)
{
	UINT8 idx = 0;

	USE(status);
	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		if (g_local_adapter.connected_device[idx] != NULL )
			if (g_local_adapter.connected_device[idx]->gap_connection_state == GAP_CONNECTION_STATE_ACL_CONNECTING)
			{
				remote_command_timer_start(g_local_adapter.connected_device[idx]->idx);
				return 0;
			}
	}
	return 0;
}

int read_file(osa_file_handle_t file_handle, osa_length_t *length, void *buffer)
{
	int ret = 0;
	file_handle->Read(file_handle, length, buffer);
	ret = (int)*length;
	return ret;
}

int close_file(osa_file_handle_t file_handle)
{
	return (int)file_handle->Close(file_handle);
}


