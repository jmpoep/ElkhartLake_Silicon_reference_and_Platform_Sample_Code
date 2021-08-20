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
#include "device_struct.h"
#include "gap.h"
#include "l2cap.h"
#include "os_timri.h"
#include <string.h>

#include "config_host.h"

u8 STACK_MAIN_THREAD_STACK[MAIN_STACK_SIZE];
#if (TARGET_THREADX == FALSE)
u8 USERIAL_READ_THREAD_STACK[APP_STACK_SIZE];
#endif
#if (A4WP_APP==TRUE)
u8 A4WP_THREAD_STACK[APP_STACK_SIZE];
#endif
#if (HRP_APP == TRUE)
u8 HRP_THREAD_STACK[APP_STACK_SIZE];
#endif
#if (FMP_APP == TRUE)
u8 FMP_THREAD_STACK[APP_STACK_SIZE];
#endif
#if (FMP_SRV_APP== TRUE)
u8 FMP_SRV_THREAD_STACK[APP_STACK_SIZE];
#endif
#if (HOGP_APP == TRUE)
u8 HOGP_THREAD_STACK[APP_STACK_SIZE];
#endif

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

void * osa_create_connected_device(UINT16 conn_handle)
{
	return (void *)create_connected_device();
}

BOOLEAN osa_is_cold_boot_cond()
{
	return TRUE;
}

void osa_delete_connected_device(UINT8 connected_device_list_idx)
{
	void * dev = g_local_adapter.connected_device[connected_device_list_idx];
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

int osa_create_timer(osa_timer_t *tid, osa_timer_static_t *stid, osa_timer_isr_list_t *list, int list_count, osa_timeout_func_t func, short val)
{
	UINT8 idx;
	if (stid->idNamespace)
		return TX_SUCCESS;

	for (idx = 0; idx < list_count; idx++)
		list[idx] = func;

	os_TimerCreateNamespace(list_count, list, stid);
	return TX_SUCCESS;
}

INT8 osa_gap_handle_command_status(UINT8 status)
{
	USE(status);
	UINT8 idx = 0;
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

void osa_wait_event_flag(void)
{
}

int osa_start_timer(osa_timer_t *tid, osa_timer_static_t *stid, int timeout_in_ms, short val)
{
	return os_TimerInNSStart(stid->idNamespace, val, os_MS2TICK(timeout_in_ms), LPM_WAKEUP_TRUE);
}

int osa_stop_timer(osa_timer_t *tid, osa_timer_static_t *stid, short val)
{
	os_TimerInNSCancel(stid->idNamespace, val);
	return TX_SUCCESS;
}

int osa_delete_timer(osa_timer_t *tid, osa_timer_static_t *stid)
{
	//os_TimerDeleteNamespace(stid->idNamespace);
	return TX_SUCCESS;
}

int osa_is_timer_active(osa_timer_t *tid, osa_timer_static_t *stid, short val)
{
	//BOOLEAN active;
	//tx_timer_info_get(timer_id, TX_NULL, &active, TX_NULL, TX_NULL, TX_NULL);
	//if (active == TRUE)
		//return 1;
	return os_TimerInNSIsActive(stid->idNamespace, val, NULL);
}

int osa_get_timer_arg_val(osa_timer_arg_t arg)
{
	return arg;
}

int osa_sleep(int timeout_in_sec)
{
	return tx_thread_sleep(os_MS2TICK(timeout_in_sec*1000));
}
