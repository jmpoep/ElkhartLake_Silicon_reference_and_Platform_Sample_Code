/** @file
  Linux implementation for OSA.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <string.h>
#include <unistd.h>
#include "osa_types.h"
#include "device_struct.h"
#include "gap.h"
#include "l2cap.h"



int osa_semaphore_create(osa_semaphore_t *sem, unsigned int value)
{
	return sem_init(sem, 0, value);
}

int osa_semaphore_delete(osa_semaphore_t *sem)
{
	return sem_destroy(sem);
}

int osa_semaphore_get(osa_semaphore_t *sem)
{
	return sem_wait(sem);
}

int osa_semaphore_put(osa_semaphore_t *sem)
{
	return sem_post(sem);
}

int osa_mutex_create(osa_mutex_t *mutex)
{
	return pthread_mutex_init(mutex, NULL);
}

int osa_mutex_delete(osa_mutex_t *mutex)
{
	return pthread_mutex_destroy(mutex);
}

int osa_mutex_get(osa_mutex_t *mutex)
{
	return pthread_mutex_lock(mutex);
}

int osa_mutex_put(osa_mutex_t *mutex)
{
	return pthread_mutex_unlock(mutex);
}

BOOLEAN osa_is_cold_boot_cond()
{
	return TRUE;
}

void * osa_create_connected_device(UINT16 conn_handle)
{
	USE(conn_handle);
	return (void *)create_connected_device();
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

int osa_create_timer(osa_timer_t *tid, osa_timer_static_t *stid, osa_timer_isr_list_t *list, int list_count, osa_timeout_func_t func, short val)
{
	struct sigevent se;
	se.sigev_notify = SIGEV_THREAD;
	se.sigev_value.sival_ptr = tid;
	se.sigev_value.sival_int = val;
	se.sigev_notify_function = func;
	se.sigev_notify_attributes = NULL;
	return timer_create(CLOCK_MONOTONIC, &se, tid);
}

int osa_start_timer(osa_timer_t *tid, osa_timer_static_t *stid, int timeout_in_ms, osa_timeout_func_t func, short val)
{
	struct itimerspec ts;
	ts.it_value.tv_sec = timeout_in_ms / 1000;
	ts.it_value.tv_nsec = 1000 * (timeout_in_ms % 1000);
	ts.it_interval.tv_sec = 0;
	ts.it_interval.tv_nsec = 0;
	return timer_settime(*tid, 0, &ts, 0);
}

int osa_stop_timer(osa_timer_t *tid, osa_timer_static_t *stid, short val)
{
	struct itimerspec ts;
	ts.it_value.tv_sec = 0;
	ts.it_value.tv_nsec = 0;
	ts.it_interval.tv_sec = 0;
	ts.it_interval.tv_nsec = 0;
	return timer_settime(*tid, 0, &ts, 0);
}

int osa_delete_timer(osa_timer_t *tid, osa_timer_static_t *stid)
{
	int res = timer_delete(*tid);
	*tid = 0;
	return res;
}

int osa_is_timer_active(osa_timer_t *tid, osa_timer_static_t *stid, short val)
{
	struct itimerspec ts;
	if (*tid == 0)
		return 0;
	timer_gettime(*tid, &ts);
	if (ts.it_value.tv_sec || ts.it_value.tv_nsec)
		return 1;
	return 0;
}

int osa_get_timer_arg_val(osa_timer_arg_t arg)
{
	return arg.sival_int;
}

int osa_sleep(int timeout_in_sec)
{
       return sleep(timeout_in_sec);
}
