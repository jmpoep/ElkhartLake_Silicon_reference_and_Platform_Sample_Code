/** @file
  Storage implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "storage.h"
#include "utils.h"
#include "error_code.h"
#include "device_struct.h"

#define MODULE_DBG_LVL STORAGE_DBG_LVL
#include "log.h"

#if (STORAGE_INCLUDED == TRUE)

#include <stdio.h>

typedef struct
{
	FILE *file_ptr;
	char file_name[255];
} storage_file_t;

static storage_file_t storage_file;

static void dump_local_adapter_entry(local_adapter_storage_t *adapter_storage)
{
#if (STORAGE_DBG_LVL == DBG_LVL_DEBUG)
	//hex_dump("", adapter_storage.name, sizeof (adapter_storage.name));
	logd("name: %s", adapter_storage->name);
	hex_dump("", adapter_storage->bd_addr, sizeof (adapter_storage->bd_addr));
	hex_dump("", adapter_storage->key_ir, sizeof (adapter_storage->key_ir));
	hex_dump("", adapter_storage->key_ir, sizeof (adapter_storage->key_irk));
	hex_dump("", adapter_storage->key_ir, sizeof (adapter_storage->key_dhk));
	hex_dump("", adapter_storage->key_ir, sizeof (adapter_storage->key_er));
#endif
}

static INT8 create_file_if_not_exists(char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (!fp)
	{
		logd("Couldn't open the previously saved file. Create an empty file");
		fp = fopen(filename, "w+");
		if (!fp)
			return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	fclose(fp);
	return STATUS_SUCCESS;
}

static UINT32 get_sizeof_file(FILE *fp)
{
	UINT32 size = 0;
	if (!fp)
		return size;
	UINT32 saved_cur = ftell(fp);
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, saved_cur, SEEK_SET);

	return size;
}

INT8 open_storage_file(char *filename)
{
	logd("");
	if (!filename)
		return STATUS_ERR_INVALID_PARAM;
	if (create_file_if_not_exists(filename) != STATUS_SUCCESS)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	storage_file.file_ptr = fopen(filename, "r+");
	if (!storage_file.file_ptr)
	{
		loge("Cannot open storage file");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	fseek (storage_file.file_ptr, 0, SEEK_SET);
	strcpy(storage_file.file_name, filename);

	return STATUS_SUCCESS;
}

void close_storage_file()
{
	logd("");
	if (storage_file.file_ptr)
		fclose(storage_file.file_ptr);
}

void set_local_adapter_entry(local_adapter_storage_t *local_adapter_storage)
{
	logd("");
	if (!storage_file.file_ptr)
		return;
	dump_local_adapter_entry(local_adapter_storage);
	/* This is the first entry */
	fseek (storage_file.file_ptr, 0, SEEK_SET);
	logd("file ptr:%ld", ftell(storage_file.file_ptr));
	size_t written_elem = fwrite(local_adapter_storage, sizeof(local_adapter_storage_t), 1, storage_file.file_ptr);
	if (written_elem != 1)
	{
		loge("Nothing written");
	}
}

/* NOTE: Deallocation responsibility is on the caller function. */
void get_local_adapter_entry(local_adapter_storage_t *adapter_storage)
{
	logd("");
	memset (adapter_storage, 0, sizeof(local_adapter_storage_t));
	if (storage_file.file_ptr)
	{
		logd("getting local adapter data");
		fseek (storage_file.file_ptr, 0, SEEK_SET);
		logd("file ptr:%ld", ftell(storage_file.file_ptr));
		size_t size = fread(adapter_storage, sizeof (local_adapter_storage_t), 1, storage_file.file_ptr);
		logd("fread return:%zu", size);
		if (size != 1)
		{
			logd("Nothing retrieved");
			dump_local_adapter_entry(adapter_storage);
			return;
		}
		dump_local_adapter_entry(adapter_storage);
	}
	return;
}

void set_remote_device_entry(remote_device_storage_t *device_entry)
{
	logd("");
	if (!storage_file.file_ptr)
		return;
	/* Find out if this device entry is new or modification. */
	remote_device_storage_t device_storage;
	get_remote_device_entry(device_entry->bd_addr, &device_storage);

	/* File pointer is at the end of file (if this is new entry)
	 * 			 	or its at the beginning of the entry (if found)
	 */
	logd("Writing the element in offset:%ld", ftell(storage_file.file_ptr));
	size_t written_elem = fwrite(device_entry, sizeof(remote_device_storage_t), 1, storage_file.file_ptr);
	if (written_elem != 1)
		loge("Nothing written");
}

/* Find the device entry from the storage for this bd address */
void get_remote_device_entry(UINT8 *bdaddr, remote_device_storage_t *device_storage)
{
	long int first_zerod_offset = get_sizeof_file(storage_file.file_ptr);
	memset (device_storage, 0, sizeof (remote_device_storage_t));

	if (storage_file.file_ptr)
	{
		fseek(storage_file.file_ptr, sizeof (local_adapter_storage_t), SEEK_SET);
		while (TRUE)
		{
			remote_device_storage_t temp_storage;
			logd("file ptr:%ld", ftell(storage_file.file_ptr));
			size_t size = fread(&temp_storage, sizeof (remote_device_storage_t), 1, storage_file.file_ptr);
			if (size != 1)
			{
				/**
				 * We didn't find the entry. Set the file offset to the point where
				 * we found the first empty slot / to the end of file (if no empty slot found)
				 */
				logd("didn't find the entry. first_zerod_offset: %ld", first_zerod_offset);
				fseek(storage_file.file_ptr, first_zerod_offset, SEEK_SET);
				break;
			}
			if (memcmp(device_storage, &temp_storage, sizeof (temp_storage)) == 0)
			{
				/* Take a note of the first 0'd (empty) slot.
				 * If we don't find an entry for this bd address we'll save the
				 * storage_file.file_ptr offset to this. So that if this routine is called
				 * from set_remote_device_entry then it'll just write the data where
				 * this offset points to.
				 */
				first_zerod_offset = ftell(storage_file.file_ptr) - sizeof (remote_device_storage_t);
				logd("first_zerod_offset: %ld", first_zerod_offset);
			}
			if (memcmp (temp_storage.bd_addr, bdaddr, BD_ADDR_LEN) == 0)
			{
				/* File pointer is at the beginning of the found entry */
				*device_storage = temp_storage;
				logd("device storage found.");
				/* Align file pointer. */
				fseek(storage_file.file_ptr, -sizeof(remote_device_storage_t), SEEK_CUR);
				break;
			}
		}
	}
}

void delete_one_remote_device_entry(UINT8 *bdaddr)
{
	if (!storage_file.file_ptr)
		return;
	remote_device_storage_t device_storage;
	get_remote_device_entry(bdaddr, &device_storage);

	if (memcmp(device_storage.bd_addr, bdaddr, BD_ADDR_LEN) == 0)
	{
		/* Entry to be deleted is found in the file. */
		remote_device_storage_t temp_storage;
		memset (&temp_storage, 0, sizeof (remote_device_storage_t));
		fwrite(&temp_storage, sizeof(remote_device_storage_t), 1, storage_file.file_ptr);
	}
	else
	{
		logd("Entry to be deleted is not found.");
	}
}

void delete_all_remote_device_entry()
{
	if (!storage_file.file_ptr)
		return;
	/* get local adapter entry */
	local_adapter_storage_t adapter_entry;
	get_local_adapter_entry(&adapter_entry);

	fclose (storage_file.file_ptr);
	remove(storage_file.file_name);

	open_storage_file(storage_file.file_name);

	set_local_adapter_entry(&adapter_entry);
}
UINT16 get_number_of_stored_devices(UINT8 key_type)
{
	if (!storage_file.file_ptr)
		return 0;
	remote_device_storage_t device_storage;
	UINT16 count = 0;
	memset (&device_storage, 0, sizeof (remote_device_storage_t));
	fseek(storage_file.file_ptr, sizeof (local_adapter_storage_t), SEEK_SET);
	while (TRUE)
	{
		remote_device_storage_t temp_storage;
		logd("file ptr:%ld", ftell(storage_file.file_ptr));
		size_t size = fread(&temp_storage, sizeof (remote_device_storage_t), 1, storage_file.file_ptr);
		if (size != 1)
		{
			break;
		}
		if (memcmp(&device_storage, &temp_storage, sizeof (temp_storage)) == 0)
			continue;
		else
		{
			switch(key_type)
			{
				case PEER_IRK:
				{
					logd("Checking peer irk");
					if((temp_storage.keys_distributed & SMP_IRK_RECEIVED) || (temp_storage.keys_distributed & SMP_IRK_DISTRIBUTED))
						count++;
				}
					break;
				default:
					break;
			}
		}
	}
	return count;
}
#if (PRIVACY_FEATURE == TRUE)
void get_stored_irk_info(resolving_list_entry_t *list_of_irk, UINT16 count)
{
       if (!storage_file.file_ptr || count == 0 )
    	   return;
       remote_device_storage_t device_storage;
       UINT16 idx = 0;
       memset (&device_storage, 0, sizeof (remote_device_storage_t));
       fseek(storage_file.file_ptr, sizeof (local_adapter_storage_t), SEEK_SET);
       while (TRUE)
       {
               remote_device_storage_t temp_storage;
               logd("file ptr:%ld", ftell(storage_file.file_ptr));
               size_t size = fread(&temp_storage, sizeof (remote_device_storage_t), 1, storage_file.file_ptr);
               if (size != 1)
               {
                       break;
               }
               if (memcmp(&device_storage, &temp_storage, sizeof (temp_storage)) == 0)
                       continue;
               else
               {
                       if((temp_storage.keys_distributed & SMP_IRK_RECEIVED) || (temp_storage.keys_distributed & SMP_IRK_DISTRIBUTED))
                       {
                               memcpy(list_of_irk[idx].peer_id_info.id_addr, temp_storage.bd_addr, BD_ADDR_LEN);
                               list_of_irk[idx].peer_id_info.id_addr_type = temp_storage.addr_type;
                               memcpy(list_of_irk[idx].local_irk, temp_storage.local_irk, 16);
                               memcpy(list_of_irk[idx].peer_id_info.irk, temp_storage.peer_irk, 16);
                               idx++;
                               if(idx == count)
                               {
                            	   break;
                               }
                       }
               }
       }
       if(count != idx)
               logw("Error in the count");
}
#endif
#else

INT8 open_storage_file(char *filename)
{
	return STATUS_ERR_OPERATION_NOT_SUPPORTED;
}

void close_storage_file(){ }

void set_local_adapter_entry(local_adapter_storage_t *local_adapter_storage){}
void get_local_adapter_entry(local_adapter_storage_t *adapter_storage){}

void get_remote_device_entry(UINT8 *bdaddr, remote_device_storage_t *device_storage){}
void set_remote_device_entry(remote_device_storage_t *device_entry){}

void delete_one_remote_device_entry(UINT8 *bdaddr) {}

void delete_all_remote_device_entry() {}
UINT16 get_number_of_stored_devices(UINT8 key_type)	{ return 0; }
void get_stored_irk_info(resolving_list_entry_t *list_of_irk, UINT16 count) {}

#endif // #if (STORAGE_INCLUDED == TRUE)
