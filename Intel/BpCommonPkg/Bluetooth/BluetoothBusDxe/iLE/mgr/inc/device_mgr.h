/** @file
  Device manager header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef DEVICE_MGR_H_
#define DEVICE_MGR_H_

#include "device_struct.h"
#include "int_interface.h"

#define DM_REQ_OPCODE_SET_ADVERTISEMENT_DATA	API_REQ_OPCODE_SET_ADVERTISEMENT_DATA
#define DM_REQ_OPCODE_REMOVE_ADVERTISEMENT_DATA	API_REQ_OPCODE_REMOVE_ADVERTISEMENT_DATA
#define DM_REQ_OPCODE_SET_LOCAL_DEVICE_NAME		API_REQ_OPCODE_SET_LOCAL_DEVICE_NAME

typedef struct
{
	UINT8 app_handle;
} dm_switch_param_t;

void dm_enable();
void dm_disable();
void dm_register(UINT8 app_idx, device_control_callbacks_t *app_device_control_cb);
void dm_unregister(UINT8 app_idx);

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

void dm_add_adv_data(UINT8 length, UINT8 type, UINT8 *data);
void dm_remove_adv_data(UINT8 length, UINT8 type, UINT8 *data);
void dm_add_scanresp_data(UINT8 length, UINT8 type, UINT8 *data);
void dm_remove_scanresp_data(UINT8 length, UINT8 type, UINT8 *data);
typedef struct
{
	UINT8 length;
	UINT8 type;
	UINT8 data[0];
} dm_adv_scanresp_data_param_t;

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

UINT8 dm_get_local_device_name(UINT8* name);

void dm_set_local_device_name(UINT8* name, UINT8 len);
typedef struct
{
	UINT8 len;
	UINT8 name[0];
} dm_set_local_device_name_param_t;

INT8 dm_add_to_whitelist(UINT8 addr_type, UINT8 *bdaddr);
INT8 dm_remove_from_whitelist(UINT8 addr_type, UINT8 *bdaddr);
INT8 dm_clear_whitelist();
typedef struct
{
	UINT8 addr_type;
	UINT8 bdaddr[BD_ADDR_LEN];
} dm_whitelist_op_param_t;

/* LL_PRIVACY */
typedef struct
{
	UINT8 peer_addr_type;
	UINT8 peer_bdaddr[BD_ADDR_LEN];
	UINT8 peer_irk[16];
	UINT8 local_irk[16];
} dm_resolving_op_param_t;

/* Callback functions */
void reset_cmpl_handler();
void read_local_feat_cmpl(UINT8* evt, UINT16 len);
void write_le_host_support_cmpl();
void evt_mask_cmpl();
void evt_mask_page_2_cmpl();
void le_evt_mask_cmpl();
void le_read_buf_size_cmpl(UINT8* evt, UINT16 len);
void le_write_def_data_len_cmpl();
void le_read_max_data_len_cmpl(UINT16 opcode, UINT8 status, UINT8* evt, UINT8 len);
void read_buf_size_cmpl(UINT8* evt, UINT16 len);
void le_read_white_list_size_cmpl(UINT8* evt, UINT16 len);
#if (CONTROLLER_PRIVACY)
void le_read_resolving_list_size_cmpl(UINT8* evt, UINT16 len);
void le_set_rpa_timeout_cmpl();
#endif /* CONTROLLER_PRIVACY */
void le_read_supported_feat_cmpl(UINT8* evt, UINT16 len);
void read_bd_addr_cmpl(UINT8* evt, UINT16 len);
void stack_init_completed(INT8 status);

void manuf_cmd_cmpl();
void write_bddata_cmpl();

INT8 dm_init();
void dm_cleanup();

#endif /* DEVICE_MGR_H_ */
