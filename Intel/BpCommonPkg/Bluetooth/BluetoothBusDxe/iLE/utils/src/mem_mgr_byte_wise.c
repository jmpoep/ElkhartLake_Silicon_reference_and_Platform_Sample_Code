/** @file
  Byte utility functions implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "bt_types.h"
#include "osa_types.h"
#include "config_host.h"
#include "utils.h"

#if (MEM_MGMT_INTERNAL == TRUE && MEM_MGMT_INTERNAL_SCHEME == MEMORY_BYTE_ADDR_MGMT)

#define MODULE_DBG_LVL MEM_MGR_DBG_LVL
#include "log.h"

/*
 * Memory allocation scheme...
 *
 * Pool:
 * ______________________________________________________________________________
 * |          |          |          |          |          |          |          |
 * |  BYTE 0  |  BYTE 1  |  BYTE 2  |  BYTE 3  |  BYTE 4  |  BYTE 5  |  BYTE 6  |
 * |__________|__________|__________|__________|__________|__________|__________|
 *
 * Bitmap:
 *    bit 0      bit 1      bit 2      bit 3      bit 4      bit 5      bit 6
 *
 *
 * Strategy:
 *
 * For free byte in pool, corresponding bit in bitmap is '0'
 * For allocated byte in pool, corresponding bit in bitmap is '1'
 *
 * One free guard byte at the end of every allocation to mark the end of allocation
 * This is used to identify end of allocated region while deallocating
 *
 */

#define SET_FROM(x)			(0xFF<<(x))
#define SET_TILL(x)			(0xFF>>(8-(x+1)))

static UINT8 stack_mem_pool[STACK_MEM_POOL_SIZE_BYTE];
static UINT8 stack_mem_pool_bitmap[STACK_MEM_POOL_SIZE_BYTE / 8];

static UINT8 app_mem_pool[APP_POOL_SIZE_BYTE];
static UINT8 app_mem_pool_bitmap[APP_POOL_SIZE_BYTE / 8];

static UINT8 l2cap_mem_pool[L2CAP_POOL_SIZE_BYTE];
static UINT8 l2cap_mem_pool_bitmap[L2CAP_POOL_SIZE_BYTE / 8];

static osa_mutex_t mutex;

UINT32 stack_max_size, app_max_size, l2cap_max_size;

/* Marks a memory region as busy in bitmap, starting from
 * 'start', and up to 'size_bytes' bytes
 */
static void mem_mark_busy(UINT8* pool_bitmap, UINT16 start, UINT16 size_bytes)
{
	UINT16 idx, start_block = start/8, end_block = (start+size_bytes-1)/8;
	UINT8 start_offset = start%8, end_offset = (start+size_bytes-1)%8;

	if (start_block == end_block)
	{
		pool_bitmap[start_block] |= (SET_FROM(start_offset) & SET_TILL(end_offset));
		return;
	}

	pool_bitmap[start_block] |= SET_FROM(start_offset);

	for (idx = start_block+1; idx < end_block; idx++)
		pool_bitmap[idx] = 0xFF;

	pool_bitmap[end_block] |= SET_TILL(end_offset);
}

/* Finds a free (unallocated) memory region from bitmap, of
 * up to 'size_bytes' bytes. The starting offset is returned
 * and 'result' is populated with either TRUE or FALSE, based
 * on whether or not the search succeeded
 */
static UINT16 mem_find_free(UINT8* pool_bitmap, UINT16 pool_bitmap_size, UINT16 size_bytes, BOOLEAN *result)
{
	UINT16 idx, start_block = 0, count = 0;
	UINT8 bit_idx, start_offset = 0;
	BOOLEAN first_free = TRUE;

	for (idx = 0; idx < pool_bitmap_size; idx++)
	{
		for (bit_idx = 0; bit_idx < 8; bit_idx ++)
		{
			//Found a free byte
			if (!(pool_bitmap[idx] & (1<<bit_idx)))
			{
				if (first_free)
				{
					//Ignore the first bit (gap bit)
					first_free = FALSE;
					continue;
				}
				if (count == 0)
				{
					//First real free byte
					start_block = idx;
					start_offset = bit_idx;
				}
				count++;
				if (count == size_bytes)
				{
					*result = TRUE;
					return (start_block*8 + start_offset);
				}
			}
			else
			{
				first_free = TRUE;
				count = 0;
			}
		}
	}
	logex("********** MEMORY FULL **********");
	dump_stack();
	*result = FALSE;
	return 0;
}

/* Marks a previously allocated memory region as free in the bitmap.
 * The starting offset is 'start', and the end is determined by the
 * free guard byte.
 */
static void mem_mark_free(UINT8* pool_bitmap, UINT16 start)
{
	UINT16 idx, start_block = start/8;
	UINT8 bit_idx, start_offset = start%8;

	for (bit_idx = start_offset; bit_idx < 8; bit_idx ++)
	{
		//Found a free byte - end of allocation - return
		if (!(pool_bitmap[start_block] & (1<<bit_idx)))
			return;
		//Otherwise, clear the byte
		pool_bitmap[start_block] &= ~(1<<bit_idx);
	}
	for (idx = start_block+1;; idx++)
	{
		for (bit_idx = 0; bit_idx < 8; bit_idx ++)
		{
			if (!(pool_bitmap[idx] & (1<<bit_idx)))
				return;
			pool_bitmap[idx] &= ~(1<<bit_idx);
		}
	}
}

#if 0
/* Dumps a part of the bitmap. Useful in debugging */
static void mem_dump_bitmap(UINT8* pool_bitmap, UINT16 pool_bitmap_size)
{
	UINT16 idx;
	UINT8 bit_idx;

	logi("");

	for(idx = 0; idx < pool_bitmap_size; idx++)
	{
		for (bit_idx = 0; bit_idx < 8; bit_idx++)
		{
			if ((pool_bitmap[idx] & (1<<bit_idx)))
			{
				log("1");
			}
			else
			{
				log("0");
			}
		}
	}
	logln("\n");
}
#endif

/* Allocates memory of 'size_bytes' bytes in the pool,
 * and returns the start pointer
 * Note: Use 32bit aligned allocation for ThreadX
 */
UINT8* stack_mem_alloc(UINT16 size_bytes)
{
	UINT16 offset;
	UINT16 aligned_size_bytes = (size_bytes/4 + 1) * 4;
	BOOLEAN result;

	osa_mutex_get(&mutex);

	//Request for an additional guard byte
	offset = mem_find_free(stack_mem_pool_bitmap, sizeof (stack_mem_pool_bitmap), aligned_size_bytes, &result);

	//Mark bytes as busy
	mem_mark_busy(stack_mem_pool_bitmap, offset, aligned_size_bytes - 1);
	if (aligned_size_bytes > 80)
		dump_stack();
	if (stack_max_size < (offset + aligned_size_bytes))
	{
		//logd("stack_max_size:%d", stack_max_size);
		//dump_stack();
		stack_max_size = offset + aligned_size_bytes;
	}

	osa_mutex_put(&mutex);

	if (result)
		return &stack_mem_pool[offset];

	return NULL;
}

/* Frees up a memory region previously allocated at 'start' */
void stack_mem_free(UINT8* start)
{
	UINT16 offset = start - &stack_mem_pool[0];

	osa_mutex_get(&mutex);

	mem_mark_free(stack_mem_pool_bitmap, offset);

	osa_mutex_put(&mutex);
}

UINT8* app_mem_alloc(UINT16 size_bytes)
{
	UINT16 offset;
	UINT16 aligned_size_bytes = (size_bytes/4 + 1) * 4;
	BOOLEAN result;

	osa_mutex_get(&mutex);

	//Request for an additional guard byte
	offset = mem_find_free(app_mem_pool_bitmap, sizeof (app_mem_pool_bitmap), aligned_size_bytes, &result);

	//Mark bytes as busy
	mem_mark_busy(app_mem_pool_bitmap, offset, aligned_size_bytes - 1);
	if (aligned_size_bytes > 80)
		dump_stack();
	if (app_max_size < (offset + aligned_size_bytes))
		app_max_size = offset + aligned_size_bytes;

	osa_mutex_put(&mutex);

	if (result)
		return &app_mem_pool[offset];

	return NULL;
}

/* Frees up a memory region previously allocated at 'start' */
void app_mem_free(UINT8* start)
{
	UINT16 offset = start - &app_mem_pool[0];

	osa_mutex_get(&mutex);

	mem_mark_free(app_mem_pool_bitmap, offset);

	osa_mutex_put(&mutex);
}

UINT8* l2cap_mem_alloc(UINT16 size_bytes)
{
	UINT16 offset;
	UINT16 aligned_size_bytes = (size_bytes/4 + 1) * 4;
	BOOLEAN result;

	osa_mutex_get(&mutex);

	//Request for an additional guard byte
	offset = mem_find_free(l2cap_mem_pool_bitmap, sizeof (l2cap_mem_pool_bitmap), aligned_size_bytes, &result);

	//Mark bytes as busy
	mem_mark_busy(l2cap_mem_pool_bitmap, offset, aligned_size_bytes - 1);
	if (aligned_size_bytes > 80)
		dump_stack();
	if (l2cap_max_size < (offset + aligned_size_bytes))
		l2cap_max_size = offset + aligned_size_bytes;

	osa_mutex_put(&mutex);

	if (result)
		return &l2cap_mem_pool[offset];

	return NULL;
}

/* Frees up a memory region previously allocated at 'start' */
void l2cap_mem_free(UINT8* start)
{
	UINT16 offset = start - &l2cap_mem_pool[0];

	osa_mutex_get(&mutex);

	mem_mark_free(l2cap_mem_pool_bitmap, offset);

	osa_mutex_put(&mutex);
}

void mem_mgr_init()
{
	logi("Byte addressing internal memory");
#if (TARGET_THREADX == TRUE || TARGET_THREADX_RW == TRUE)
	//Make sure first allocation is 32bit aligned
	stack_mem_pool_bitmap[0] = 7;
	app_mem_pool_bitmap[0] = 7;
	l2cap_mem_pool_bitmap[0] = 7;
#endif
	osa_mutex_create(&mutex);
}

void mem_mgr_cleanup()
{
	osa_mutex_delete(&mutex);
	//mem_dump_bitmap();
}

#endif /* #if (MEM_MGMT_INTERNAL == TRUE && MEM_MGMT_INTERNAL_SCHEME == MEMORY_BYTE_ADDR_MGMT) */
