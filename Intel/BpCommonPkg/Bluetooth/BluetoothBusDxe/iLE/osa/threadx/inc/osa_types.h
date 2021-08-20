/** @file
  OSA types header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef OSA_TYPES_H_
#define OSA_TYPES_H_

#include "config_host.h"

#include "tx_api.h"
#include "ose_export.h"

#define inline __inline

#define APP_STACK_SIZE	512
#define MAIN_STACK_SIZE	1024

#define RETENTION_SECTION_START
#define RETENTION_SECTION_END
#define _packed_struct_ PACKED struct

#define TO_STRING(x) #x
#define TO_STACK_NAME(x) x ## _STACK
#define TO_VAR_NAME(x) x ## _VAR

typedef u8	UINT8;
typedef u16	UINT16;
typedef u32	UINT32;
typedef u64	UINT64;

typedef s8	INT8;
typedef s16 INT16;
typedef s32	INT32;
typedef s64	INT64;

typedef BOOL	BOOLEAN;

typedef TX_THREAD osa_thread_t;
typedef TX_MUTEX osa_mutex_t;
typedef TX_SEMAPHORE osa_semaphore_t;
typedef os_Timer_STRUCT osa_timer_static_t;
typedef TimerIsrFcn osa_timer_isr_list_t;
typedef int osa_timer_t;

typedef ULONG osa_timer_arg_t;
typedef void osa_thread_ret_t;
typedef ULONG osa_thread_arg_t;
typedef UINT8 reten_connection_info_t;

typedef void (*osa_timeout_func_t)(osa_timer_arg_t arg);

extern u8 STACK_MAIN_THREAD_STACK[MAIN_STACK_SIZE];
extern u8 USERIAL_READ_THREAD_STACK[APP_STACK_SIZE];
extern u8 A4WP_THREAD_STACK[APP_STACK_SIZE];
extern u8 HRP_THREAD_STACK[APP_STACK_SIZE];
extern u8 FMP_THREAD_STACK[APP_STACK_SIZE];
extern u8 FMP_SRV_THREAD_STACK[APP_STACK_SIZE];
extern u8 HOGP_THREAD_STACK[APP_STACK_SIZE];

#define osa_thread_create(name, handler, priority) { \
	tx_thread_create(&(TO_VAR_NAME(name)), TO_STRING(name), handler, 0, (void*) TO_STACK_NAME(name), sizeof(TO_STACK_NAME(name)), priority, priority, TX_NO_TIME_SLICE, TX_AUTO_START);	\
}

#define osa_thread_join(name, val) {}

#define osa_thread_exit(val) return

int osa_semaphore_create(osa_semaphore_t *sem, unsigned int value);
int osa_semaphore_delete(osa_semaphore_t *sem);
int osa_semaphore_get(osa_semaphore_t *sem);
int osa_semaphore_put(osa_semaphore_t *sem);

int osa_mutex_create(osa_mutex_t *mutex);
int osa_mutex_delete(osa_mutex_t *mutex);
int osa_mutex_get(osa_mutex_t *mutex);
int osa_mutex_put(osa_mutex_t *mutex);

void osa_gap_setup_connection(UINT8 idx, UINT8 *remote_bdaddr, UINT8 addr_type);
INT8 osa_gap_handle_command_status(UINT8 status);
void * osa_create_connected_device(UINT16 conn_handle);
void osa_delete_connected_device(UINT8 conn_handle);
void osa_wait_event_flag(void);

BOOLEAN osa_is_cold_boot_cond(void);
void osa_restore_connected_devices(void);
void osa_save_acl_handle(UINT8 connected_device_list_idx, UINT16 conn_handle);


int osa_create_timer(osa_timer_t *tid, osa_timer_static_t *stid, osa_timer_isr_list_t *list, int list_count, osa_timeout_func_t func, short val);
int osa_start_timer(osa_timer_t *tid, osa_timer_static_t *stid, int timeout_in_ms, osa_timeout_func_t func, short val);
int osa_stop_timer(osa_timer_t *tid, osa_timer_static_t *stid, short val);
int osa_delete_timer(osa_timer_t *tid, osa_timer_static_t *stid);
int osa_is_timer_active(osa_timer_t *tid, osa_timer_static_t *stid, short val);
int osa_get_timer_arg_val(osa_timer_arg_t arg);
int osa_sleep(int timeout_in_sec);

#endif /* OSA_TYPES_H_ */
