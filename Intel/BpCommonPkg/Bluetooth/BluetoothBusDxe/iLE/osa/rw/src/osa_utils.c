/** @file
  Implementation for OSA.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "osa_types.h"
#include "os_timer.h"
#include "device_struct.h"
#include "l2cap.h"
#include "gap.h"
#include "os_retention.h"
#include "hci.h"
#include "pmu.h"
#include "interface.h"
#include "iomux.h"
#include "wdog.h"

extern TX_EVENT_FLAGS_GROUP st_evnt_flags; //events belongs to stack thread

#include <string.h>


RETENTION_SECTION_START
connected_dev_acl_t g_connected_dev_acl_t[MAX_NUM_CONNECTED_DEVICE];
RETENTION_SECTION_END

int osa_semaphore_create(osa_semaphore_t *sem, unsigned int value)
{
	return tx_semaphore_create(sem, "", value);
}

int osa_semaphore_delete(osa_semaphore_t *sem)
{
	return tx_semaphore_delete(sem);
}

int osa_semaphore_get(osa_semaphore_t *sem)
{
	return tx_semaphore_get(sem, TX_WAIT_FOREVER);
}

int osa_semaphore_put(osa_semaphore_t *sem)
{
	return tx_semaphore_put(sem);
}

int osa_mutex_create(osa_mutex_t *mutex)
{
	return tx_mutex_create(mutex, "", TX_NO_INHERIT);
}

int osa_mutex_delete(osa_mutex_t *mutex)
{
	return tx_mutex_delete(mutex);
}

int osa_mutex_get(osa_mutex_t *mutex)
{
	return tx_mutex_get(mutex, TX_WAIT_FOREVER);
}

int osa_mutex_put(osa_mutex_t *mutex)
{
	return tx_mutex_put(mutex);
}

BOOLEAN osa_is_cold_boot_cond()
{
	BOOLEAN boot_st = TRUE;

	if (boot_state !=  BOOT_STATE_COLD_BOOT)
		boot_st = FALSE;

	return boot_st;
}

void * osa_create_connected_device(UINT16 conn_handle)
{
	connected_device_t *device = (connected_device_t*) os_retentionGetHostConnEntry(conn_handle);
	if (device == NULL)
		return NULL;
	memset(device, 0, sizeof(connected_device_t));
	return (void *)device;
}

void osa_delete_connected_device(UINT8 connected_device_list_idx)
{
	connected_device_t *device = g_local_adapter.connected_device[connected_device_list_idx];
	os_retentionFreeHostConnEntry(device->acl_handle);
	g_connected_dev_acl_t[connected_device_list_idx].acl_handle = 0;
	g_connected_dev_acl_t[connected_device_list_idx].flag = 0;
}

void osa_save_acl_handle(UINT8 connected_device_list_idx, UINT16 conn_handle)
{
	g_connected_dev_acl_t[connected_device_list_idx].acl_handle = conn_handle;
	g_connected_dev_acl_t[connected_device_list_idx].flag = 1;
}


void osa_restore_connected_devices(void)
{
	UINT8 idx = 0;
	memset(g_local_adapter.connected_device, 0, sizeof(g_local_adapter.connected_device));
	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		if (g_connected_dev_acl_t[idx].flag != 0 )
			g_local_adapter.connected_device[idx] = (connected_device_t *)os_retentionGetHostConnEntry(g_connected_dev_acl_t[idx].acl_handle);
	}
}

INT8 osa_gap_handle_command_status(UINT8 status)
{
	connected_device_t *device = NULL;
	if (status == 0)
	{
		device = (connected_device_t *)os_retentionGetHostConnEntry(OS_RETENTION_PRE_CONN_HANDLE);

		if (device == NULL)
			return STATUS_ERR_INAVALID_CONNENCTION;

		memset(device, 0, sizeof(connected_device_t));
		g_local_adapter.connected_device[g_local_adapter.reten_conn_info.idx] = device;
		device->idx = g_local_adapter.reten_conn_info.idx;
		device->bdaddr_type = g_local_adapter.reten_conn_info.addr_type;
		memcpy(device->bdaddr, g_local_adapter.reten_conn_info.bdaddr, BD_ADDR_LEN);
		device->gap_connection_state = g_local_adapter.reten_conn_info.gap_connection_state;
		osa_save_acl_handle(g_local_adapter.reten_conn_info.idx, OS_RETENTION_PRE_CONN_HANDLE);
		memset(&g_local_adapter.reten_conn_info, 0, sizeof(g_local_adapter.reten_conn_info));
		remote_command_timer_start(device->idx);
				return STATUS_SUCCESS;
	}
	else
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
}

void osa_gap_setup_connection(UINT8 idx, UINT8 *remote_bdaddr, UINT8 addr_type)
{
	g_local_adapter.reten_conn_info.idx = idx;
	memcpy(&g_local_adapter.reten_conn_info.bdaddr, remote_bdaddr, BD_ADDR_LEN);
	g_local_adapter.reten_conn_info.addr_type = addr_type;
	g_local_adapter.reten_conn_info.l2cap_state = L2CAP_STATE_CLOSED;
	g_local_adapter.reten_conn_info.gap_connection_state = GAP_CONNECTION_STATE_ACL_CONNECTING;
}

void osa_wait_event_flag(void)
{
	while(hci_msg_cfg.route == 0)
    {
        UINT32 hciOsEvntFlgs = 0;
		//return;
        /* Wait for STACK enable event from LL thread */
		tx_event_flags_get(&st_evnt_flags, \
                            OS_EVNT_FLG_ENABLE_STACK_MSG, \
                            TX_OR_CLEAR, \
                            (ULONG *)&hciOsEvntFlgs, \
                            TX_WAIT_FOREVER);
        wdog_kick();
    }
    iLE_stack_init();
}

/* Timer ID is 24bit. MS 8bit is value (ignoring MSB for retention). LS 16bit is incremental timer ID */
int osa_create_timer(osa_timer_t *tid, osa_timer_static_t *stid, osa_timer_isr_list_t *list, int list_count, osa_timeout_func_t func, short val)
{

	if (!*tid)
	{
		g_local_adapter.timer_id++;
		*tid = val;
		*tid <<= 16;
		*tid |= g_local_adapter.timer_id;
	}
	if (!g_local_adapter.timer_id)
		return TX_TIMER_ERROR;
	return TX_SUCCESS;
}

int osa_start_timer(osa_timer_t *tid, osa_timer_static_t *stid, int timeout_in_ms, osa_timeout_func_t func, short val)
{
	if (!*tid)
		return TX_TIMER_ERROR;
	os_timerStart(*tid, timeout_in_ms/10, func);
	return TX_SUCCESS;
}

int osa_stop_timer(osa_timer_t *tid, osa_timer_static_t *stid, short val)
{
	if (!*tid)
		return TX_TIMER_ERROR;
	return os_timerStop(*tid);
}

int osa_delete_timer(osa_timer_t *tid, osa_timer_static_t *stid)
{
	if (!*tid)
		return TX_TIMER_ERROR;
	*tid = 0;
	return TX_SUCCESS;
}

int osa_is_timer_active(osa_timer_t *tid, osa_timer_static_t *stid, short val)
{
	if (!*tid)
		return TX_TIMER_ERROR;
	return os_timerActive(*tid);
}

int osa_get_timer_arg_val(osa_timer_arg_t arg)
{
	return (arg >> 16) & 0xff;
}

int osa_sleep(int timeout_in_sec)
{
	return 0;//tx_thread_sleep(timeout_in_sec*1000);
}

BOOLEAN osa_is_stack_sleepAllowed(void)
{
    BOOLEAN sleepStatus = PMU_SLEEP_ALLOWED;

    return (sleepStatus);
}

