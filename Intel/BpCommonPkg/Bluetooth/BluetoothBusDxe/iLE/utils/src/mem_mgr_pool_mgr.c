/** @file
  Pool utility functions implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "bt_types.h"
#include "utils.h"
#include "osa_types.h"
#include "config_host.h"

#if (MEM_MGMT_INTERNAL == TRUE && MEM_MGMT_INTERNAL_SCHEME == MEMORY_POOL_MGMT)

#define MODULE_DBG_LVL MEM_MGR_DBG_LVL
#include "log.h"

mem_pool_header_t mem_pool_header[MEM_BUF_POOL_MAX_ID];

#define MEM_POOL_SIZE_BYTE (\
		(MEM_BUF_POOL0_LENGTH * MEM_BUF_POOL0_ELEM_SIZE) +\
		(MEM_BUF_POOL1_LENGTH * MEM_BUF_POOL1_ELEM_SIZE) +\
		(MEM_BUF_POOL2_LENGTH * MEM_BUF_POOL2_ELEM_SIZE) +\
		(MEM_BUF_POOL3_LENGTH * MEM_BUF_POOL3_ELEM_SIZE) +\
		(MEM_BUF_POOL4_LENGTH * MEM_BUF_POOL4_ELEM_SIZE) +\
		(MEM_BUF_POOL5_LENGTH * MEM_BUF_POOL5_ELEM_SIZE))

static UINT8 mem_pool[MEM_POOL_SIZE_BYTE];

static osa_mutex_t mutex;

/* Dumps a part of the bitmap. Useful in debugging */
static void mem_dump_bitmap()
{
#if ((TARGET_LINUX == TRUE || TARGET_ANDROID == TRUE) && MEM_MGR_DBG_LVL > DBG_LVL_DEBUG)
	UINT8 pool_id;
	for (pool_id = 0; pool_id < MEM_BUF_POOL_MAX_ID; pool_id ++)
	{
		printf("mem_pool_header[%d].usage_bitmap:", pool_id);
		UINT8 idx;
		for (idx = 0; idx < MEM_BUF_POOL_HEADER_BITMAP_LEN; idx ++)
		{
			UINT8 bitmap = mem_pool_header[pool_id].usage_bitmap[idx];
			UINT8 jdx;
			for (jdx = 0; jdx < 8; jdx++)
			{
				if ((bitmap & (1 << jdx)) == (1 << jdx))
					printf ("%d", 1);
				else
					printf ("%d", 0);
			}
		}
		printf("\n");
	}
#endif
}

/*
 * Select the pool by seeing which memory size fits the requested size
 */
static UINT8 mem_select_pool(UINT16 size_bytes, UINT8 min_pool_id)
{
	if (size_bytes <= MEM_BUF_POOL0_ELEM_SIZE && min_pool_id <= MEM_BUF_POOL0_ID)
	{
		logd("size_bytes:%u pool:%d waste:%u", size_bytes, MEM_BUF_POOL0_ID, MEM_BUF_POOL0_ELEM_SIZE - size_bytes);
		return MEM_BUF_POOL0_ID;
	}
	if (size_bytes <= MEM_BUF_POOL1_ELEM_SIZE && min_pool_id <= MEM_BUF_POOL1_ID)
	{
		logd("size_bytes:%u pool:%d waste:%u", size_bytes, MEM_BUF_POOL1_ID, MEM_BUF_POOL1_ELEM_SIZE - size_bytes);
		return MEM_BUF_POOL1_ID;
	}
	if (size_bytes <= MEM_BUF_POOL2_ELEM_SIZE && min_pool_id <= MEM_BUF_POOL2_ID)
	{
		logd("size_bytes:%u pool:%d waste:%u", size_bytes, MEM_BUF_POOL2_ID, MEM_BUF_POOL2_ELEM_SIZE - size_bytes);
		return MEM_BUF_POOL2_ID;
	}
	if (size_bytes <= MEM_BUF_POOL3_ELEM_SIZE && min_pool_id <= MEM_BUF_POOL3_ID)
	{
		logd("size_bytes:%u pool:%d waste:%u", size_bytes, MEM_BUF_POOL3_ID, MEM_BUF_POOL3_ELEM_SIZE - size_bytes);
		return MEM_BUF_POOL3_ID;
	}
	if (size_bytes <= MEM_BUF_POOL4_ELEM_SIZE && min_pool_id <= MEM_BUF_POOL4_ID)
	{
		logd("size_bytes:%u pool:%d waste:%u", size_bytes, MEM_BUF_POOL4_ID, MEM_BUF_POOL4_ELEM_SIZE - size_bytes);
		return MEM_BUF_POOL4_ID;
	}
	if (size_bytes <= MEM_BUF_POOL5_ELEM_SIZE && min_pool_id <= MEM_BUF_POOL5_ID)
	{
		logd("size_bytes:%u pool:%d waste:%u", size_bytes, MEM_BUF_POOL5_ID, MEM_BUF_POOL5_ELEM_SIZE - size_bytes);
		return MEM_BUF_POOL5_ID;
	}
	return MEM_BUF_POOL_MAX_ID; /* None of our pool is fit for this */
}

/*
 * Given a pool it sees the first free unallocated element in the pool and
 * returns the location to it. Sets the busy bit in the usage mask array.
 */
static void* mem_find_free(UINT8 pool_id)
{
	UINT8 idx;
	UINT8 offset = 0;

	if (pool_id >= MEM_BUF_POOL_MAX_ID)
		return NULL;

	for (idx = 0; idx < mem_pool_header[pool_id].num_of_elem; idx++)
	{
		if (mem_pool_header[pool_id].usage_bitmap[idx] != 0xFF) /* This one has a free space */
		{
			UINT8 max_bit_offset = mem_pool_header[pool_id].num_of_elem - (idx * 8);
			logd("max_bit_offset:%d", max_bit_offset);
			for (offset = 0; offset < max_bit_offset; offset ++)
			{
				if (((~mem_pool_header[pool_id].usage_bitmap[idx]) & (1 << offset)) == (1 << offset))
				{
					logd("Got a free space. bit offset: %d mem_pool_header[%d].usage_bitmap[idx]:%x",
							offset, pool_id, mem_pool_header[pool_id].usage_bitmap[idx]);
					mem_pool_header[pool_id].usage_bitmap[idx] |= (1 << offset);
					break;
				}
			}
			if (offset >= max_bit_offset)
			{
				logw("No free memory found in pool:%d", pool_id);
				return NULL;
			}
			mem_dump_bitmap();
#if (MEMORY_POOL_STAT_COLLECTION == TRUE)
			mem_pool_header[pool_id].cur_used += mem_pool_header[pool_id].elem_len;
			mem_pool_header[pool_id].max_used = MAX(mem_pool_header[pool_id].cur_used, mem_pool_header[pool_id].max_used);
			logd("mem_pool_header[%d].max_used:%u", pool_id, mem_pool_header[pool_id].max_used);
#endif
			void * ret_buf = mem_pool_header[pool_id].base_ptr + (idx * 8 * mem_pool_header[pool_id].elem_len) + mem_pool_header[pool_id].elem_len * offset;
			memset(ret_buf, 0, mem_pool_header[pool_id].elem_len);
#if (MEM_MGR_DBG_LVL > DBG_LVL_DEBUG)
			if (pool_id >= MEM_BUF_POOL4_ID)
			{
				dump_stack();
			}
#endif
			return ret_buf;
		}
	}
	logw("No free memory found in pool:%d", pool_id);
	return NULL;
}

/* Allocates memory of 'size_bytes' bytes in the pool,
 * and returns the start pointer
 * Note: Use 32bit aligned allocation for ThreadX
 */
UINT8* mem_alloc(UINT16 size_bytes)
{
	UINT8 min_pool_id = 0;
	void *ret_ptr = NULL;

	osa_mutex_get(&mutex);

	logd("size_bytes:%u", size_bytes);
	for (min_pool_id = 0; min_pool_id < MEM_BUF_POOL_MAX_ID; min_pool_id ++)
	{
		min_pool_id = mem_select_pool(size_bytes, min_pool_id);
		if ((ret_ptr = mem_find_free(min_pool_id)) != NULL)
		{
			logd("allocation success: %p", ret_ptr);
			break;
		}
		logd("retry with bigger pool");
	}

	if (min_pool_id == MEM_BUF_POOL_MAX_ID)
	{
		logex("************Memory Full*************");
		dump_stack();
	}

	osa_mutex_put(&mutex);
	return ret_ptr;
}

/* Frees up a memory region previously allocated at 'start' */
void mem_free(UINT8* start)
{
	osa_mutex_get(&mutex);
	logd("address:%p", start);

	/* Find the pool to which it belongs to. Match the address range. */
	UINT8 pool_id;
	for (pool_id = 0; pool_id < MEM_BUF_POOL_MAX_ID; pool_id ++)
	{
		if (((void*)start) >= mem_pool_header[pool_id].base_ptr &&  ((void*)start) < mem_pool_header[pool_id].end_ptr)
			break;
	}
	logd("pool_id:%d mem_pool_header[pool_id].base_ptr:%p", pool_id, mem_pool_header[pool_id].base_ptr);
	if (pool_id != MEM_BUF_POOL_MAX_ID)
	{
		UINT16 offset = (void*)start - mem_pool_header[pool_id].base_ptr;
		UINT8 idx_in_usage_mask = offset / (mem_pool_header[pool_id].elem_len * 8);
		UINT8 bit_offset = (offset - (mem_pool_header[pool_id].elem_len * idx_in_usage_mask * 8)) / mem_pool_header[pool_id].elem_len;
		logd("offset:%u idx_in_usage_mask:%d bit_offset:%d", offset, idx_in_usage_mask, bit_offset);
		mem_pool_header[pool_id].usage_bitmap[idx_in_usage_mask] &= ~(1 << bit_offset);
		mem_dump_bitmap();
#if (MEMORY_POOL_STAT_COLLECTION == TRUE)
		mem_pool_header[pool_id].cur_used -= mem_pool_header[pool_id].elem_len;
#endif
		/* Clear memory */
		memset(start, 0, mem_pool_header[pool_id].elem_len);
	}
	else
	{
		loge("Could not locate this memory. Its a same for us...");
	}

	osa_mutex_put(&mutex);
}

void mem_mgr_init()
{
	logi("pool managed internal memory");
#if (TARGET_THREADX == TRUE || TARGET_THREADX_RW == TRUE)
	//Make sure first allocation is 32bit aligned
	mem_pool_bitmap[0] = 7;
#endif
	/* Initialize the header of the pools */
	memset(mem_pool, 0, MEM_POOL_SIZE_BYTE);
	memset(mem_pool_header, 0, sizeof (mem_pool_header_t) * MEM_BUF_POOL_MAX_ID);
	mem_pool_header[MEM_BUF_POOL0_ID].base_ptr = &mem_pool[0];
	mem_pool_header[MEM_BUF_POOL1_ID].base_ptr = mem_pool_header[MEM_BUF_POOL0_ID].base_ptr + (MEM_BUF_POOL0_LENGTH * MEM_BUF_POOL0_ELEM_SIZE);
	mem_pool_header[MEM_BUF_POOL2_ID].base_ptr = mem_pool_header[MEM_BUF_POOL1_ID].base_ptr + (MEM_BUF_POOL1_LENGTH * MEM_BUF_POOL1_ELEM_SIZE);
	mem_pool_header[MEM_BUF_POOL3_ID].base_ptr = mem_pool_header[MEM_BUF_POOL2_ID].base_ptr + (MEM_BUF_POOL2_LENGTH * MEM_BUF_POOL2_ELEM_SIZE);
	mem_pool_header[MEM_BUF_POOL4_ID].base_ptr = mem_pool_header[MEM_BUF_POOL3_ID].base_ptr + (MEM_BUF_POOL3_LENGTH * MEM_BUF_POOL3_ELEM_SIZE);
	mem_pool_header[MEM_BUF_POOL5_ID].base_ptr = mem_pool_header[MEM_BUF_POOL4_ID].base_ptr + (MEM_BUF_POOL4_LENGTH * MEM_BUF_POOL4_ELEM_SIZE);

	mem_pool_header[MEM_BUF_POOL0_ID].elem_len = MEM_BUF_POOL0_ELEM_SIZE;
	mem_pool_header[MEM_BUF_POOL1_ID].elem_len = MEM_BUF_POOL1_ELEM_SIZE;
	mem_pool_header[MEM_BUF_POOL2_ID].elem_len = MEM_BUF_POOL2_ELEM_SIZE;
	mem_pool_header[MEM_BUF_POOL3_ID].elem_len = MEM_BUF_POOL3_ELEM_SIZE;
	mem_pool_header[MEM_BUF_POOL4_ID].elem_len = MEM_BUF_POOL4_ELEM_SIZE;
	mem_pool_header[MEM_BUF_POOL5_ID].elem_len = MEM_BUF_POOL5_ELEM_SIZE;

	mem_pool_header[MEM_BUF_POOL0_ID].num_of_elem = MEM_BUF_POOL0_LENGTH;
	mem_pool_header[MEM_BUF_POOL1_ID].num_of_elem = MEM_BUF_POOL1_LENGTH;
	mem_pool_header[MEM_BUF_POOL2_ID].num_of_elem = MEM_BUF_POOL2_LENGTH;
	mem_pool_header[MEM_BUF_POOL3_ID].num_of_elem = MEM_BUF_POOL3_LENGTH;
	mem_pool_header[MEM_BUF_POOL4_ID].num_of_elem = MEM_BUF_POOL4_LENGTH;
	mem_pool_header[MEM_BUF_POOL5_ID].num_of_elem = MEM_BUF_POOL5_LENGTH;

	mem_pool_header[MEM_BUF_POOL0_ID].end_ptr = mem_pool_header[MEM_BUF_POOL0_ID].base_ptr + (MEM_BUF_POOL0_ELEM_SIZE * MEM_BUF_POOL0_LENGTH);
	mem_pool_header[MEM_BUF_POOL1_ID].end_ptr = mem_pool_header[MEM_BUF_POOL1_ID].base_ptr + (MEM_BUF_POOL1_ELEM_SIZE * MEM_BUF_POOL1_LENGTH);
	mem_pool_header[MEM_BUF_POOL2_ID].end_ptr = mem_pool_header[MEM_BUF_POOL2_ID].base_ptr + (MEM_BUF_POOL2_ELEM_SIZE * MEM_BUF_POOL2_LENGTH);
	mem_pool_header[MEM_BUF_POOL3_ID].end_ptr = mem_pool_header[MEM_BUF_POOL3_ID].base_ptr + (MEM_BUF_POOL3_ELEM_SIZE * MEM_BUF_POOL3_LENGTH);
	mem_pool_header[MEM_BUF_POOL4_ID].end_ptr = mem_pool_header[MEM_BUF_POOL4_ID].base_ptr + (MEM_BUF_POOL4_ELEM_SIZE * MEM_BUF_POOL4_LENGTH);
	mem_pool_header[MEM_BUF_POOL5_ID].end_ptr = mem_pool_header[MEM_BUF_POOL5_ID].base_ptr + (MEM_BUF_POOL5_ELEM_SIZE * MEM_BUF_POOL5_LENGTH);

	osa_mutex_create(&mutex);
	UINT8 pool_id;
	for (pool_id = 0; pool_id < MEM_BUF_POOL_MAX_ID; pool_id ++)
	{
		logd("mem_pool_header[%d].base_ptr:%p, mem_pool_header[%d].end_ptr:%p mem_pool_header[%d].elem_len:%u",
				pool_id, mem_pool_header[pool_id].base_ptr,
				pool_id, mem_pool_header[pool_id].end_ptr,
				pool_id, mem_pool_header[pool_id].elem_len);
	}
}

void mem_mgr_cleanup()
{
	osa_mutex_get(&mutex);
#if (MEMORY_POOL_STAT_COLLECTION == TRUE)
	UINT8 idx;
	UINT16 total_max_used = 0;
	for (idx = 0; idx < MEM_BUF_POOL_MAX_ID; idx++)
	{
		logln("POOL [%d] max_used:%d Bytes. Length:%d", idx, mem_pool_header[idx].max_used,  mem_pool_header[idx].max_used / mem_pool_header[idx].elem_len);
		total_max_used += mem_pool_header[idx].max_used;
	}
	logln("Memory pool size:%zu bookeeping size:%lu total_max_used:%u", sizeof (mem_pool), sizeof (mem_pool_header), total_max_used);
#endif
	memset (mem_pool, 0, MEM_POOL_SIZE_BYTE);
	memset (mem_pool_header, 0, sizeof (mem_pool_header_t) * MEM_BUF_POOL_MAX_ID);

	osa_mutex_put(&mutex);

	osa_mutex_delete(&mutex);

}

#endif /* MEM_MGMT_INTERNAL == TRUE && MEM_MGMT_INTERNAL_SCHEME == MEMORY_POOL_STAT_COLLECTION */
