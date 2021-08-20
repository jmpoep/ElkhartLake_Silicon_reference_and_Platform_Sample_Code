/** @file
  Storage implementation header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef STORAGE_H_

#include "bt_types.h"
#include "device_struct.h"

typedef struct
{
	UINT8 name[MAX_LOCAL_NAME_LEN];
	UINT8 bd_addr[BD_ADDR_LEN];
	UINT8 key_ir[16];
	UINT8 key_irk[16];
	UINT8 key_dhk[16];
	UINT8 key_er[16];
} local_adapter_storage_t;

typedef struct
{
	UINT8 bd_addr[BD_ADDR_LEN];
	UINT8 addr_type;
	UINT8 name[255];
	UINT8 car_supported;
/* General security and key info*/
	UINT8 security_level;
	UINT8 keys_distributed;
	UINT8 key_size;
	UINT8 key_type;
/* Encryption Info */
	UINT8 peer_ltk[SMP_MAX_KEY_LEN];
	UINT8 peer_rand[SMP_LTK_RAND_LEN];
	UINT16 peer_ediv;
	UINT8 local_ltk[SMP_MAX_KEY_LEN];
	UINT8 local_rand[SMP_LTK_RAND_LEN];
	UINT16 local_ediv;
/* Identity Info*/
#if (PRIVACY_FEATURE)
	UINT8 peer_irk[SMP_MAX_KEY_LEN];
	UINT8 id_bdaddr[BD_ADDR_LEN];
	UINT8 id_addr_type;
	UINT8 local_irk[SMP_MAX_KEY_LEN];
#endif /*PRIVACY_FEATURE */
/* Signing Info*/
#if (SIGNED_WRITE)
	UINT8  peer_csrk[SMP_MAX_KEY_LEN];
	UINT8 local_csrk[SMP_MAX_KEY_LEN];
	UINT32 local_sign_counter;
	UINT32 peer_sign_counter;
#endif /* SIGNED_WRITE */
#if (GAP_GATT_SRV_APP == TRUE)
	BOOLEAN is_notify_for_service_change;
#endif
} remote_device_storage_t;


INT8 open_storage_file(char *filename);
void close_storage_file();

void set_local_adapter_entry(local_adapter_storage_t *local_adapter_storage);
void get_local_adapter_entry(local_adapter_storage_t *adapter_storage);

void get_remote_device_entry(UINT8 *bdaddr, remote_device_storage_t *device_storage);
void set_remote_device_entry(remote_device_storage_t *device_entry);

void delete_one_remote_device_entry(UINT8 *bdaddr);
void delete_all_remote_device_entry();
UINT16 get_number_of_stored_devices(UINT8 key_type);
#if (PRIVACY_FEATURE == TRUE)
void get_stored_irk_info(resolving_list_entry_t *list_of_irk, UINT16 count);
#endif

#endif //#ifndef STORAGE_H_
