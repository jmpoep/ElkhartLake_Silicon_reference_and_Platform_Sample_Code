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

#include <Protocol/SimpleFileSystem.h>

#define __func__ __FUNCTION__
#define inline __inline

typedef UINT8 osa_thread_t;
typedef UINT8 osa_semaphore_t;
typedef EFI_TPL osa_mutex_t;
typedef EFI_EVENT osa_timer_t;
typedef UINT8 osa_timer_static_t;
typedef UINT8 osa_timer_isr_list_t;
typedef short osa_timer_arg_t;
typedef void* osa_thread_ret_t;
typedef void* osa_thread_arg_t;
typedef EFI_FILE_HANDLE osa_file_handle_t;
typedef UINTN osa_length_t;
typedef UINT8 reten_connection_info_t;

extern EFI_FILE_HANDLE log_file;
extern EFI_FILE_HANDLE snoop_file;
extern UINT8 logbuf_count;
#define LOGBUF_SIZE 200
#define LOGFLUSH_GAP 10

#define RETENTION_SECTION_START
#define RETENTION_SECTION_END

#define malloc(size) AllocateZeroPool((UINTN)size)
#define free(ptr) FreePool(ptr)
#define memset(buffer, value, size) SetMem(buffer, size, value)
#define memcpy(destination, source, size) CopyMem(destination, source, size)
#define memcmp(buffer1, buffer2, size) (int)CompareMem(buffer1, buffer2, size)

typedef void (*osa_timeout_func_t)(osa_timer_arg_t arg);

#define osa_thread_create(name, handler, priority) USE(handler)

#define osa_thread_join(name, val) USE(val)

#define osa_thread_exit(val) return val

int osa_semaphore_create(osa_semaphore_t *sem, unsigned int value);
int osa_semaphore_delete(osa_semaphore_t *sem);
int osa_semaphore_get(osa_semaphore_t *sem);
int osa_semaphore_put(osa_semaphore_t *sem);

int osa_mutex_create(osa_mutex_t *mutex);
int osa_mutex_delete(osa_mutex_t *mutex);
int osa_mutex_get(osa_mutex_t *mutex);
int osa_mutex_put(osa_mutex_t *mutex);


int osa_create_timer(osa_timer_t *tid, osa_timer_static_t *stid, osa_timer_isr_list_t *list, int list_count, osa_timeout_func_t func, short val);
int osa_start_timer(osa_timer_t *tid, osa_timer_static_t *stid, UINT64 timeout_in_ms, osa_timeout_func_t func, short val);
int osa_stop_timer(osa_timer_t *tid, osa_timer_static_t *stid, short val);
int osa_delete_timer(osa_timer_t *tid, osa_timer_static_t *stid);
int osa_is_timer_active(osa_timer_t *tid, osa_timer_static_t *stid, short val);
int osa_get_timer_arg_val(osa_timer_arg_t arg);
int osa_sleep(int timeout_in_sec);
void * osa_create_connected_device(UINT16 conn_handle);
void osa_gap_setup_connection(UINT8 idx, UINT8 *remote_bdaddr, UINT8 addr_type);
void osa_delete_connected_device(UINT8 conn_handle);
INT8 osa_gap_handle_command_status(UINT8 status);
BOOLEAN osa_is_cold_boot_cond(void);
void osa_restore_connected_devices(void);
void osa_save_acl_handle(UINT8 connected_device_list_idx, UINT16 conn_handle);

int read_file(osa_file_handle_t file_handle, osa_length_t *length, void *buffer);
int close_file(osa_file_handle_t file_handle);

#endif /* OSA_TYPES_H_ */
