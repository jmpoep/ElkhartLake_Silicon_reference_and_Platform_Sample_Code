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
#include "boot.h"
#include "tx_api.h"
#include <stdint.h>

#define inline __inline

#define STD_STACK_SIZE	2000
#define MAIN_STACK_SIZE	3000

/* FIXME: Packed struct is nto working */
#define _packed_struct_ _Packed struct

#define TO_STRING(x) #x
#define TO_STACK_NAME(x) x ## _STACK
#define TO_VAR_NAME(x) x ## _VAR

/// start redirecting variables to .retentionDccmData or .retentionDccmBss
#define RETENTION_SECTION_START _Pragma("push_default_section(DATA, \".retentionDccmData\")") \
 _Pragma("push_default_section(BSS, \".retentionDccmBss\")")

 /// end redirecting variables to .retentionDccmData or .retentionDccmBss.
#define RETENTION_SECTION_END _Pragma("pop_default_section(DATA)") \
 _Pragma("pop_default_section(BSS)");
typedef uint8_t		UINT8;
typedef uint16_t	UINT16;
typedef uint32_t	UINT32;
typedef uint64_t	UINT64;

typedef int8_t		INT8;
typedef int16_t 	INT16;
typedef int32_t		INT32;
typedef int64_t		INT64;

typedef uint8_t	BOOLEAN;


typedef TX_THREAD osa_thread_t;
typedef TX_MUTEX osa_mutex_t;
typedef TX_SEMAPHORE osa_semaphore_t;
typedef int osa_timer_static_t;
typedef int osa_timer_isr_list_t;
typedef uint32_t osa_timer_t;

typedef uint32_t osa_timer_arg_t;
typedef void osa_thread_ret_t;
typedef ULONG osa_thread_arg_t;


typedef struct
{
	UINT8 idx; /**< array index at which this connected device resides. */
	UINT8 addr_type; /**< address type for the remote device */
	UINT8 bdaddr[6]; /**< Bluetooth MAC address of the remote device */
	UINT8 l2cap_state; /**< l2cap state */
	UINT8 gap_connection_state;
}reten_connection_info_t;

/* ACL Handles to be saved across cold/warm boot */
typedef struct
{
	UINT16 acl_handle; /**< connection handle */
	BOOLEAN flag; /**< valid acl handle; 1: valid, 0: invalid */
}connected_dev_acl_t;


typedef void (*osa_timeout_func_t)(osa_timer_arg_t arg);


extern UINT8 STACK_MAIN_THREAD_STACK[MAIN_STACK_SIZE];
extern UINT8 USERIAL_READ_THREAD_STACK[STD_STACK_SIZE];
extern UINT8 GATT_SRV_THREAD_STACK[STD_STACK_SIZE];
extern UINT8 GAP_SRV_THREAD_STACK[STD_STACK_SIZE];
extern UINT8 A4WP_THREAD_STACK[STD_STACK_SIZE];
extern UINT8 HRP_THREAD_STACK[STD_STACK_SIZE];
extern UINT8 FMP_THREAD_STACK[STD_STACK_SIZE];
extern UINT8 FMP_SRV_THREAD_STACK[STD_STACK_SIZE];
extern UINT8 HOGP_THREAD_STACK[STD_STACK_SIZE];

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
uint8_t osa_stack_sleepAllowed(void);

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

void stack_ll_handler();
void stack_interface_handler();

#endif /* OSA_TYPES_H_ */
