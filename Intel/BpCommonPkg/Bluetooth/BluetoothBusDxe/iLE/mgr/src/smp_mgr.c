/** @file
  SMP manager implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "smp_mgr.h"
#include "smp.h"
#include "utils.h"
#include "gap.h"
#include "device_mgr.h"
#include "hci_host.h"
#include "att.h"
#include "interface.h"
#if (INTERNAL_AES == TRUE)
#include "aes.h"
#endif /* INTERNAL_AES == TRUE */


#define MODULE_DBG_LVL SMP_MGR_DBG_LVL
#include "log.h"
/*
 * Static internal functions
 */
#if (SMP_FEATURE)

static INT8 smp_create_bond(connected_device_t *device,UINT8 auth_level_min, UINT8 key_size_min);
static INT8 smpm_remove_bond(trans_id_t trans_id, UINT8* bdaddr, UINT8 addr_type);

#if (SIGNED_WRITE)
static INT8 smp_mgr_sign_data(connected_device_t *device, UINT8 *data, UINT16 data_len);
static INT8 smp_mgr_sign_verify(connected_device_t *device, UINT8 *data, UINT16 data_len);
static INT8 smpm_sign_data(UINT8 app_handle, connected_device_t *device, UINT8 *data, UINT16 data_len, data_siging_complete_cb_t cback);
static INT8 smpm_sign_verify(UINT8 app_handle, connected_device_t *device, UINT8 *data, UINT16 data_len, sign_verify_complete_cb_t cback);
#endif /* SIGNED_WRITE */

static INT8 smpm_create_bond(trans_id_t trans_id, connected_device_t *device,UINT8 auth_level_min, UINT8 key_size_min, bonding_complete_cb_t cback);

#if (PRIVACY_FEATURE)
static INT8 smpm_rpa_generate();
static INT8 smpm_rpa_resolve(UINT8 *rpa, BOOLEAN local, rpa_complete_cb_t cback);
static void create_add_bonded_dev_to_resolving_req(smp_bonding_key_t *cur_key);
#endif /* PRIVACY_FEATURE */

#if(HOST_PRIVACY)
static UINT8 find_free_slot_in_resolving_list();
#endif /*HOST_PRIVACY */

static INT8 smpm_smp_init();

#if (HOST_PRIVACY)

static void smp_rpa_resolution_cb(UINT8 *bd_addr, BOOLEAN local, UINT8 bonded_idx, UINT8 status)
{
	char bdaddr_str[BD_ADDR_STR_LEN];
	connected_device_t *device;
	logi("");
	BDADDR_TO_STRING(bdaddr_str, bd_addr);
	device = get_connected_device_by_bdaddr(bd_addr);
	if(!device)
		return;
	if (status == STATUS_SUCCESS)
	{
		smpm_clear_key(device);
	}
	else
		loge("Could not remove bonded device %s as it was not found in database", bdaddr_str);
}

#endif /* HOST_PRIVACY*/

static INT8 smpm_enqueue_req_in_pending_queue(interface_req_elem_t *incoming_req)
{
	logd("incoming_req:%p", incoming_req);
	if (!incoming_req)
		return STATUS_ERR_INVALID_PARAM;
	return enqueue(&g_local_adapter.smp_mgr_data.pending_req_q, (void*)incoming_req);
}

static void smpm_dequeue_and_cleanup_from_pending_queue()
{
	interface_req_elem_t* req = (interface_req_elem_t*)dequeue(&g_local_adapter.smp_mgr_data.pending_req_q);
	if (req)
	{
		dealloc_queue_element(req);
	}
}

static void finish_transac_and_process_new_req()
{
	g_local_adapter.smp_mgr_data.busy = FALSE;
	smpm_req_handler(NULL);
}

static interface_req_elem_t* get_req_to_process()
{
	return (interface_req_elem_t*)pick_front(&g_local_adapter.smp_mgr_data.pending_req_q);
}

INT8 smpm_req_handler(interface_req_elem_t* incoming_req)
{
	INT8 req_status = STATUS_ERR_UNKNOWN;
	interface_req_elem_t* req;
	logd("");
	/* enqueue this request */
	smpm_enqueue_req_in_pending_queue(incoming_req);
	req = get_req_to_process();
	if (!req)
	{
		logd("No pending request in SMP wait queue.");
		return STATUS_SUCCESS;
	}
	if(g_local_adapter.smp_mgr_data.busy == TRUE)
		return STATUS_PROCESS_ONGOING;
	g_local_adapter.smp_mgr_data.busy = TRUE;
	switch (req->req_opcode)
	{
		case API_REQ_OPCODE_INIT_SMP:
		{
			req_status = smpm_smp_init();
		}
			break;
		case API_REQ_OPCODE_CREATE_BOND:
		{
			smpm_create_bond_param_t* param = (smpm_create_bond_param_t*)(void*)req->parameter;
			connected_device_t *device = NULL;

			req_status = STATUS_ERR_INAVALID_CONNENCTION;
			device = get_connected_device_by_conn_id(param->conn_id);
			if(device)
			{
				req_status = smpm_create_bond(param->trans_id, device, param->auth_level_min, param->key_size_min, param->cb);
			}
			else
			{
				UINT8 app_handle = get_appid_from_transid(param->trans_id);
				if(param)
				{
					if(param->cb)
						param->cb(param->trans_id, NULL, 0, MAX_NUM_CONNECTED_DEVICE, SMP_DEVICE_NOT_CONNECTED, NULL, 0);
					else
						if((app_handle < MAX_NUMBER_OF_APP) && g_local_adapter.app_list[app_handle]->app_device_control_cb->iLE_bonding_completed_cb)
							g_local_adapter.app_list[app_handle]->app_device_control_cb->iLE_bonding_completed_cb(param->trans_id, NULL, 0, MAX_NUM_CONNECTED_DEVICE, SMP_DEVICE_NOT_CONNECTED, NULL, 0);
				}
			}
		}
			break;
		case API_REQ_OPCODE_REMOVE_BOND:
		{
			smpm_remove_bond_param_t* param = (smpm_remove_bond_param_t*)(void*)req->parameter;
			req_status = smpm_remove_bond(param->trans_id, param->remote_bd_addr, param->addr_type);

			/* This internally triggers an RPA resolution sequence, so SMP should remain locked */
			/* Interface will not clear this req, since SMP is still processing it */
			/* However, no cb goes to the app on completion of this req, so it can be cleared here */
			smpm_dequeue_and_cleanup_from_pending_queue();
		}
			break;
#if (SIGNED_WRITE)
		case API_REQ_OPCODE_SIGN_DATA:
		{
			smpm_sign_data_param_t* param = (smpm_sign_data_param_t*)(void*)req->parameter;
			req_status = smpm_sign_data(param->app_handle, param->device, param->data, param->data_len, param->cback);
		}
			break;
		case API_REQ_OPCODE_SIGN_VERIFY:
		{
			smpm_sign_verify_param_t* param = (smpm_sign_verify_param_t*)(void*)req->parameter;
			req_status = smpm_sign_verify(param->app_handle, param->device, param->data, param->data_len, param->cback);
		}
			break;
#endif /* SIGNED_WRITE */
#if (PRIVACY_FEATURE)
		case API_REQ_OPCODE_RPA_GENERATE:
		{
			req_status = smpm_rpa_generate();
		}
			break;
		case API_REQ_OPCODE_RPA_RESOLVE:
		{
			smpm_rpa_resolve_param_t *param = (smpm_rpa_resolve_param_t*)(void*)req->parameter;
			req_status = smpm_rpa_resolve( param->rpa, param->local, param->cback);
		}
			break;
#endif /* PRIVACY_FEATURE */
	}
	if (req_status != STATUS_ERR_BUSY)
	{
		logd("Req_status: %d", req_status);
		smpm_dequeue_and_cleanup_from_pending_queue();
		g_local_adapter.smp_mgr_data.busy = FALSE;
	}
	return STATUS_PROCESS_ONGOING;
}
/*
 * Functionalities used by the applications
 */
/** @brief Interface layer call this function to create a bond with a device.
 *
 * Function: smpm_create_bond
 * 			 This function gets called from the interface layer when an application initiates a bond creation.
 * 			 Once a bond is created, bonding_complete_cb registered by the application is called to inform the application about
 * 			 status.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param auth_level_min - Minimum Level of authentication required when a bond is created with the remote device
 * @param key_size_min - Minimum length of key used for encryption.This value has to be in the range of 7 to 16.
 * @return Error code.
 */
static INT8 smpm_create_bond(trans_id_t trans_id, connected_device_t *device,UINT8 auth_level_min, UINT8 key_size_min, bonding_complete_cb_t cback)
{
#if (PARANOID_STACK == TRUE)
	UINT8 app_handle;
	if(device == NULL)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
	app_handle = get_appid_from_transid(trans_id);
	if(app_handle == MAX_NUMBER_OF_APP)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
#endif
	if (cback)
		g_local_adapter.smp_mgr_data.smp_bonding_complete_cb = cback;

	smp_create_bond(device, auth_level_min, key_size_min);
	return STATUS_ERR_BUSY;
}

static INT8 smpm_remove_bond(trans_id_t trans_id, UINT8* bdaddr, UINT8 addr_type)
{
	connected_device_t *device;
#if (PARANOID_STACK == TRUE)
	UINT8 app_handle;
	if (!bdaddr)
		return STATUS_ERR_INVALID_PARAM;
	app_handle = get_appid_from_transid(trans_id);
	if(app_handle == MAX_NUMBER_OF_APP)
		return STATUS_ERR_INVALID_PARAM;
#endif
	device = get_connected_device_by_id_addr(bdaddr);
	if(!device)
	{
		logw("Device not connected");
		return STATUS_SUCCESS;
	}
#if (HOST_PRIVACY == TRUE)
	if (BLE_IS_RESOLVE_BDADDR(bdaddr))
		return smpm_rpa_resolve(bdaddr, FALSE, smp_rpa_resolution_cb);
#else
	smpm_clear_key(device);
#endif
	return STATUS_SUCCESS;
}

/** @brief Interface layer call this function to sign data.
 *
 * Function: smpm_sign_data
 *
 * @param app_handle - Handle of the application.
 * @param device - connected device.
 * @param data - Data to be signed
 * @param data_len - Length of data in bytes.
 * @return Error code.
 */
#if (SIGNED_WRITE)
static INT8 smpm_sign_data(UINT8 app_handle, connected_device_t *device, UINT8 *data, UINT16 data_len, data_siging_complete_cb_t cback)
{
	INT8 ret;
	logi("");
#if (PARANOID_STACK == TRUE)
	if(device == NULL)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
	if(app_handle == MAX_NUMBER_OF_APP)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
#endif
	if(g_local_adapter.smp_mgr_data.smp_sign_verify_complete_cb != NULL)
	{
		return STATUS_ERR_BUSY;
	}
	g_local_adapter.smp_mgr_data.smp_data_siging_complete_cb = cback;
	ret = smp_mgr_sign_data(device, data, data_len);
	if (ret == STATUS_SUCCESS)
		return STATUS_ERR_BUSY;
	return ret;
}

static INT8 smpm_sign_verify(UINT8 app_handle, connected_device_t *device, UINT8 *data, UINT16 data_len, sign_verify_complete_cb_t cback)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if(app_handle == MAX_NUMBER_OF_APP)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
#endif
	if(g_local_adapter.smp_mgr_data.smp_data_siging_complete_cb != NULL)
	{
		return STATUS_ERR_BUSY;
	}
	g_local_adapter.smp_mgr_data.smp_sign_verify_complete_cb = cback;
	smp_mgr_sign_verify(device, data, data_len);
	return STATUS_ERR_BUSY;
}
#endif /* SIGNED_WRITE */

#if (PRIVACY_FEATURE)
static INT8 smpm_rpa_generate()
{
	logi("");
	smp_rpa_generate();
	return STATUS_ERR_BUSY;
}
static INT8 smpm_rpa_resolve(UINT8 *rpa, BOOLEAN local, rpa_complete_cb_t cback)
{
	logi("");
	g_local_adapter.smp_mgr_data.smp_rpa_res_complete_cb = cback;
	smp_rpa_resolve(rpa, local);
	return STATUS_ERR_BUSY;
}
#endif /* PRIVACY_FEATURE */
static INT8 smpm_smp_init()
{
	smp_init();
	return STATUS_ERR_BUSY;
}

/** @brief Interface layer call this function to register for smp callbacks.
 *
 * Function: smpm_smp_register
 * 			 This function is used to register one application for SMP callbacks. SMP layer uses this call back to display passkey,
 * 			 request for authorisation and request for passkey entry. Only one application can be registered for SMP callbacks.
 *
 * @param app_handle - Handle of the application.
 * @param smp_app_cb - Callback function.
 * @return Error code.
 */

INT8 smpm_smp_register(trans_id_t trans_id, smp_app_cb_t smp_app_cb)
{
#if (PARANOID_STACK == TRUE)
	UINT8 app_handle = get_appid_from_transid(trans_id);
	logi("");
	if(app_handle == MAX_NUMBER_OF_APP)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
	if(smp_app_cb == NULL)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
#else
	logi("");
#endif
	if(g_local_adapter.smp_mgr_data.smp_app_cback != NULL)
	{
		logw("Another function already registered for callbacks");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	g_local_adapter.smp_mgr_data.smp_app_cback = smp_app_cb;
	return STATUS_SUCCESS;
}

/** @brief Interface layer call this function to send the passkey entered by the user to SMP layer.
 *
 * Function: smpm_send_passkey
 * 			 This function is used to send the passkey entered by the user to the SMP layer.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param passkey - passkey entered by the user.
 * @return Error code.
 */
INT8 smpm_send_passkey(trans_id_t trans_id, UINT8 *remote_bd_addr, UINT32 passkey)
{
	logi("");
	logd("Passkey:%d", passkey);
	smp_send_passkey(passkey);
	return STATUS_SUCCESS;
}
/** @brief Interface layer call this function to send the authorisation to SMP layer.
 *
 * Function: smpm_send_passkey
 * 			 This function is used to send the authorisation to the SMP layer.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param authorization - Authorization by the user.
 * @param auth_level_min - Minimum authentication requirement for this pairing
 * @param key_size_min - Minimum key size for this pairing
 * @return Error code.
 */
INT8 smpm_send_authorization(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 authorization, UINT8 auth_level_min, UINT8 key_size_min)
{
#if (PARANOID_STACK == TRUE)
	UINT8 app_handle = get_appid_from_transid(trans_id);
	logi("");
	if(app_handle == MAX_NUMBER_OF_APP)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
	if(remote_bd_addr == NULL)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
#else
	logi("");
#endif
	smp_send_authorization(remote_bd_addr, authorization, auth_level_min, key_size_min);
	return STATUS_SUCCESS;
}


#if (SECURE_CONNECTION)
INT8 smpm_send_nc_result(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 authorization)
{
#if (PARANOID_STACK == TRUE)
	UINT8 app_handle = get_appid_from_transid(trans_id);
	logi("");
	if(app_handle == MAX_NUMBER_OF_APP)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
	if(remote_bd_addr == NULL)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
#else
	logi("");
#endif
	smp_send_nc_result(remote_bd_addr, authorization);
	return STATUS_SUCCESS;
}
#endif /*SECURE_CONNECTION*/

/* Storage APIs*/

INT8 smpm_storage_register(trans_id_t trans_id, storage_callbacks_t *storage_cb)
{
       UINT8 app_handle;
       logi("");
       app_handle = get_appid_from_transid(trans_id);
       if(app_handle == MAX_NUMBER_OF_APP)
       {
               return STATUS_ERR_INVALID_PARAM;
       }
       if (!storage_cb)
       {
		g_local_adapter.smp_mgr_data.storage_mgr.storage_cb = NULL;
		g_local_adapter.smp_mgr_data.storage_mgr.trans_id = 0;
		g_local_adapter.smp_mgr_data.storage_mgr.registered = FALSE;
		return STATUS_SUCCESS;
       }
       if(g_local_adapter.smp_mgr_data.storage_mgr.registered)
       {
               logw("Another function already registered for storage callbacks");
               return STATUS_ERR_INSUFFICIENT_RESOURCES;
       }
       g_local_adapter.smp_mgr_data.storage_mgr.storage_cb = storage_cb;
       g_local_adapter.smp_mgr_data.storage_mgr.trans_id = trans_id;
       g_local_adapter.smp_mgr_data.storage_mgr.registered = TRUE;
       if(storage_cb != NULL)
    	   smp_storage_registered();
#if(PRIVACY_FEATURE == TRUE)
       if(storage_cb && storage_cb->key_request_cb)
       {
               UINT8 bd_addr[BD_ADDR_LEN];
               memset(bd_addr, 0, BD_ADDR_LEN);
               storage_cb->key_request_cb(trans_id, bd_addr, 0, LOCAL_IRK);
       }
       else
       {
    	   smp_generate_local_irk();
       }
#else
       smp_mgr_ext_init_cb();
#endif
       return STATUS_SUCCESS;
}

INT8 smpm_key_response(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 key_type, BOOLEAN is_valid, void* key_value)
{
	logd("");
	switch(key_type)
	{
#if (PRIVACY_FEATURE)
		case LOCAL_IRK:
		{
			logd("Local IRK update from app");
			if(is_valid == FALSE)
			{
				logd("IRK not found in DB. Generating ...");
				smp_generate_local_irk();
			}
			else
			{
				identity_info_t *local_irk;
				logd("IRK Found in DB");
				local_irk = key_value;
				memcpy(g_local_adapter.smp_data.device_irk, local_irk->irk, 16);
				hex_dump("IRK:", local_irk->irk, 16);
				if(g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_request_cb)
				{
					UINT8 dummy_bdaddr[BD_ADDR_LEN];
					memset(dummy_bdaddr, 0, BD_ADDR_LEN);
					g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_request_cb(g_local_adapter.smp_mgr_data.storage_mgr.trans_id,
																						dummy_bdaddr, 0, PEER_IRK);
				}
			}

		}
			break;
		case PEER_IRK:
		{
			resolving_list_entry_t *res_list_entry;
			logd("Peer IRK to be added to resolving list");
			if(is_valid == FALSE)
			{
				logd("All entries populated");
				smp_mgr_ext_init_cb();
				break;
			}
			res_list_entry = key_value;
#if (CONTROLLER_PRIVACY)
			if (LL_PRIVACY_IS_SUPPORTED)
			{
				UINT8 rev_bdaddr[BD_ADDR_LEN];
				UINT8 *rev_bdaddr_ptr;
				interface_req_elem_t *req;
				dm_resolving_op_param_t *param;
				memset(rev_bdaddr, 0, BD_ADDR_LEN);
				req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_ADD_TO_RESOLVINGLIST, 0, sizeof(dm_resolving_op_param_t));
				if(req == NULL)
					break;
				param = (dm_resolving_op_param_t *)req->parameter;

				rev_bdaddr_ptr = rev_bdaddr;
				REVERSE_ARRAY_TO_STREAM(rev_bdaddr_ptr, bdaddr, BD_ADDR_LEN);
				memset(param, 0, sizeof(dm_resolving_op_param_t));
				param->peer_addr_type = bdaddr_type;
				memcpy(param->peer_bdaddr, rev_bdaddr, BD_ADDR_LEN);
				memcpy(param->peer_irk , res_list_entry->peer_id_info.irk, 16);
				memcpy(param->local_irk , res_list_entry->local_irk, 16);
				gap_req_handler(req);
			}
#endif	/* CONTROLLER_PRIVACY */
#if (HOST_PRIVACY)
			{
				UINT8 idx = find_free_slot_in_resolving_list();
				if(idx < HOST_RESOLVING_LIST_SIZE)
				{
					g_local_adapter.resolving_list[idx].valid = TRUE;
					memcpy(&g_local_adapter.resolving_list[idx].entry, res_list_entry, sizeof(resolving_list_entry_t));

				}
				else
				{
					logw("Host Resolving list full");
				}
			}
#endif /* HOST_PRIVACY */
		}
				break;
#endif /* PRIVACY_FEATURE */
		case SEC_INFO:
		{
			connected_device_t *device;
			hex_dump("Security info updated for", bdaddr, BD_ADDR_LEN);
			device = get_connected_device_by_id_addr(bdaddr);
			if(!device)
			{
				logw("Device not connected");
				break;
			}
			if(is_valid)
			{
				sec_info_t *security_info = key_value;
				logd("Security_level : %d", security_info->security_level);
				logd("key_size : %02x", security_info->key_size);
				logd("keys_distributed: %02x", security_info->keys_distributed);
				logd("Key type: %02x", security_info->key_type);
				device->link_enc_state.key_size = security_info->key_size;
				device->link_enc_state.key_type = security_info->key_type;
				device->link_enc_state.keys_distributed = security_info->keys_distributed;
				device->link_enc_state.secuirty_level = security_info->security_level;
			}
			if(device->link_enc_state.state == LINK_ENC_STATE_UPDATING)
				device->link_enc_state.state = LINK_ENC_STATE_UPDATED;
			else
				break;
			if(device->link_enc_state.pending_act & LINK_ENC_PENDING)
			{
				device->link_enc_state.pending_act &= ~(LINK_ENC_PENDING);
				smp_check_key_and_encrypt(device);
			}
			if(device->link_enc_state.pending_act & LINK_PAIR_PENDING)
			{
				interface_req_elem_t* req;
				smpm_create_bond_param_t* param;

				req = get_req_to_process();
				if(req == NULL)
					break;
				param = (smpm_create_bond_param_t*)(void*)req->parameter;
				device->link_enc_state.pending_act &= ~(LINK_PAIR_PENDING);
				if(req->req_opcode == API_REQ_OPCODE_CREATE_BOND)
				{
					connected_device_t *conn_device = NULL;

					conn_device = get_connected_device_by_conn_id(param->conn_id);
					if(conn_device)
						smp_create_bond(conn_device, param->auth_level_min, param->key_size_min);
					/* TODO: what if device is not connect or got disconnect */
				}


			}
			if(device->link_enc_state.pending_act & LINK_SEC_REQ_PENDING)
			{
				device->link_enc_state.pending_act &= ~(LINK_SEC_REQ_PENDING);
				security_req_cont();
			}
			if(device->link_enc_state.pending_act & LINK_SIGN_PENDING)
			{
				interface_req_elem_t* req;
				smpm_sign_data_param_t* param;

				req = get_req_to_process();
				if(req == NULL)
					break;
				param = (smpm_sign_data_param_t*)(void*)req->parameter;
				if(req->req_opcode == API_REQ_OPCODE_SIGN_DATA)
					smp_sign_data(param->device, param->data, param->data_len);
				device->link_enc_state.pending_act &= ~(LINK_SIGN_PENDING);
			}
			if(device->link_enc_state.pending_act & LINK_VERIFY_PENDING)
			{
				interface_req_elem_t* req;
				smpm_sign_verify_param_t* param;

				req = get_req_to_process();
				if(req == NULL)
					break;
				param = (smpm_sign_verify_param_t*)(void*)req->parameter;
				if(req->req_opcode == API_REQ_OPCODE_SIGN_DATA)
					smp_mgr_sign_verify(param->device, param->data, param->data_len);
				device->link_enc_state.pending_act &= ~(LINK_VERIFY_PENDING);
			}
			if(device->link_enc_state.pending_act & LINK_ATT_PENDING)
			{
				att_process_packet(device->pending_att_packet.opcode, device->idx, device->pending_att_packet.in_buffer);
				if(device->pending_att_packet.in_buffer)
					dealloc(device->pending_att_packet.in_buffer);
				device->pending_att_packet.in_buffer = NULL;
				device->att_device.client_att_state = 0;
				device->link_enc_state.pending_act &= ~(LINK_ATT_PENDING);
			}

		}
			break;
		case PEER_LTK:
		{
			connected_device_t *device = get_connected_device_by_id_addr(bdaddr);
			if(!device)
			{
				hex_dump("Device not connected", bdaddr, BD_ADDR_LEN);
				break;
			}
			if(!(device->link_enc_state.pending_act & LINK_ENC_PENDING))
			{
				logd("Enc not pending");
				logd("Enc pending  : %02x", device->link_enc_state.pending_act);
				break;
			}
			if(is_valid)
			{
				enc_info_t *enc_info = key_value;
				hci_ble_start_encryption(device->acl_handle, enc_info->rand,
												enc_info->ediv, enc_info->ltk);
			}
			else
			{
				logw("Key not found!!!");
				break;
			}

		}
			break;
		case LOCAL_LTK:
		{
			connected_device_t *device = get_connected_device_by_id_addr(bdaddr);
			if(!device)
			{
				hex_dump("Device not connected", bdaddr, BD_ADDR_LEN);
				break;
			}
			if(!(device->link_enc_state.pending_act & LINK_ENC_PENDING))
			{
				loge("No pending enc operation");
				break;
			}
			if(is_valid)
			{
				enc_info_t *enc_info = key_value;
				hci_ble_ltk_req_reply(device->acl_handle, enc_info->ltk);
			}
			else
			{
				hci_ble_ltk_neg_reply(device->acl_handle);
			}
		}
			break;
		case LOCAL_CSRK:
		{
			connected_device_t *device = get_connected_device_by_id_addr(bdaddr);
			if(!device)
			{
				hex_dump("Device not connected", bdaddr, BD_ADDR_LEN);
				break;
			}
			if(!(device->link_enc_state.pending_act & LINK_SIGN_PENDING))
				break;
			if(is_valid)
			{
				interface_req_elem_t* req;
				smpm_sign_data_param_t* param;
				signing_info_t *local_sign_info = key_value;
				memcpy(device->local_sign_info.sign_key.csrk, local_sign_info->csrk, 16);
				device->local_sign_info.sign_key.counter = local_sign_info->counter;
				logd("Sign counter = %d", local_sign_info->counter);
				device->local_sign_info.valid = TRUE;
				req = get_req_to_process();
				if(req == NULL)
					break;
				param = (smpm_sign_data_param_t*)(void*)req->parameter;
				if(req->req_opcode == API_REQ_OPCODE_SIGN_DATA)
					smp_sign_data(param->device, param->data, param->data_len);
				break;
			}
			else
			{
				smp_mgr_data_sign_cback(device, (UINT8)STATUS_ERR_INAVALID_CONNENCTION, NULL);
			}
		}
			break;
		case PEER_CSRK:
		{
			connected_device_t *device = get_connected_device_by_id_addr(bdaddr);
			if(!device)
			{
				hex_dump("Device not connected", bdaddr, BD_ADDR_LEN);
				break;
			}
			if(!(device->link_enc_state.pending_act & LINK_VERIFY_PENDING))
				break;
			if(is_valid)
			{
				interface_req_elem_t* req;
				smpm_sign_verify_param_t* param;
				signing_info_t *peer_sign_info = key_value;
				memcpy(device->peer_sign_info.sign_key.csrk, peer_sign_info->csrk, 16);
				device->peer_sign_info.sign_key.counter = peer_sign_info->counter;
				device->peer_sign_info.valid = TRUE;
				req = get_req_to_process();
				if(req == NULL)
					break;
				param = (smpm_sign_verify_param_t*)(void*)req->parameter;
				if(req->req_opcode == API_REQ_OPCODE_SIGN_VERIFY)
					smp_sign_verify(param->device, param->data, param->data_len);
				break;
			}
			else
			{
				smp_mgr_data_verify_cback(device->idx, (UINT8)STATUS_ERR_INAVALID_CONNENCTION);
			}

		}
			break;
		default:
			logw("Unknown key type %d", key_type);
			break;
	}

	return STATUS_SUCCESS;
}

/*
 * Internal functions used by upper layers
 */
/** @brief This is called by device manger once the stack initialisation is completed
 *
 * Function: smp_mgr_init
 * 				This function initialises the lower layer (SMP) and the data base required to store bonded device details.
 * note : smp_init() results in HCI commands to the controller. This function should be called only after the stack is initialised.
 * @return Error code.
 */

INT8 smp_mgr_init()
{
	interface_req_elem_t *req ;
#if (INTERNAL_AES == TRUE)
	AES128_init();
#endif /* INTERNAL_AES == TRUE*/
	g_local_adapter.smp_mgr_data.smp_bonding_complete_cb = NULL;
	g_local_adapter.smp_mgr_data.smp_app_cback = NULL;
	init_no_guard_q(&g_local_adapter.smp_mgr_data.pending_req_q);
	req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_INIT_SMP, 0, 0);
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	smpm_req_handler(req);
	return STATUS_SUCCESS;
}

/** @brief This is called by device manger when the stack is shutdown
 *
 * Function: smp_mgr_cleanup
 * 				This function shutdown the lower layer (SMP).
  * @return Error code.
 */
INT8 smp_mgr_cleanup()
{
	interface_req_elem_t* req = NULL;
#if (INTERNAL_AES == TRUE)
	AES128_cleanup();
#endif /* INTERNAL_AES == TRUE*/
	smp_shutdown();
	while ((req = (interface_req_elem_t*)dequeue(&g_local_adapter.smp_mgr_data.pending_req_q)) != NULL)
	{
		dealloc_queue_element(req);
	}

	cleanup_q(&g_local_adapter.smp_mgr_data.pending_req_q);

	iLE_stack_cleanup();
	return STATUS_SUCCESS;
}

/*
 * Functions used by lower layer (SMP)
 */

static INT8 smp_create_bond(connected_device_t *device, UINT8 auth_level_min, UINT8 key_size_min)
{
	BOOLEAN key_check;
	logi("");
	logd("min auth level  = %x", auth_level_min);

	if(device->link_enc_state.state >= LINK_ENC_STATE_UPDATED)
	{
		if(device->link_enc_state.key_size)
		{
			logd("Device found in database Keys distributed is %02x", device->link_enc_state.keys_distributed);
			/* Device already present in the database and hence it is already bonded*/
			/* Checking whether sufficient level of security is present for the key*/
			key_check = smp_check_key_level(auth_level_min, device->link_enc_state.key_type);

			if(key_size_min > device->link_enc_state.key_size)
				key_check = FALSE;
			if(key_check)
			{
				if(device->local_link_role)
				{
					if((device->link_enc_state.keys_distributed & SMP_LTK_DISTRIBUTED))
					{
						/* LTK present*/
						logd("LTK Present");
						return smp_start_encryption(device, auth_level_min, key_size_min);
					}
				}
				else
				{
					if((device->link_enc_state.keys_distributed & SMP_LTK_RECEIVED))
					{
						/* LTK present*/
						logd("LTK Present");
						return smp_start_encryption(device, auth_level_min, key_size_min);
					}
				}
			}
		}
	}
	else
	{
		logd("Sec info not updated waiting");
		device->link_enc_state.pending_act |= LINK_PAIR_PENDING;
		return STATUS_ERR_BUSY;
	}
	return smp_pair(device, auth_level_min, key_size_min);
}
#if (SIGNED_WRITE)
static INT8 smp_mgr_sign_data(connected_device_t *device, UINT8 *data, UINT16 data_len)
{
	INT8 ret = STATUS_ERR_LAYER_SPECIFIC;
	logi("");
#if (PARANOID_STACK == TRUE)
	if(device == NULL)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
#endif
	if(device->link_enc_state.state >= LINK_ENC_STATE_UPDATED)
	{
		if((device->link_enc_state.keys_distributed & SMP_CSRK_DISTRIBUTED) == FALSE)
			return ret;
		smp_sign_data(device, data, data_len);
	}
	else
	{
		device->link_enc_state.pending_act |= LINK_SIGN_PENDING;
	}
	return STATUS_SUCCESS;
}

static INT8 smp_mgr_sign_verify(connected_device_t *device, UINT8 *data, UINT16 data_len)
{
	INT8 ret = STATUS_ERR_LAYER_SPECIFIC;
	logi("");
#if (PARANOID_STACK == TRUE)
	if(device == NULL)
	{
		return STATUS_ERR_INVALID_PARAM;
	}
#endif

	if(device->link_enc_state.state >= LINK_ENC_STATE_UPDATED)
	{	/* Device already in data base*/
		if((device->link_enc_state.keys_distributed & SMP_CSRK_RECEIVED) == FALSE)
					return ret;
		smp_sign_verify(device, data, data_len);
	}
	else
	{
		device->link_enc_state.pending_act |= LINK_VERIFY_PENDING;
	}
	return STATUS_SUCCESS;
}
#endif /* SIGNED_WRITE */


void smp_mgr_cback(UINT8* bdaddr, UINT8 event, UINT8* data, UINT8 length)
{
	trans_id_t trans_id;
	interface_req_elem_t *req = get_req_to_process();
	if(req == NULL)
	{
		trans_id = INVALID_TRANS_ID;
	}
	else
	{
	smpm_create_bond_param_t* param = (smpm_create_bond_param_t*)(void*)req->parameter;
	trans_id = param->trans_id;
	}
	if(g_local_adapter.smp_mgr_data.smp_app_cback != NULL)
	{
		connected_device_t *device = get_connected_device_by_id_addr(bdaddr);
		if(!device)
		{
			loge("Device not found in the connected device list!!!");
			return;
		}
		g_local_adapter.smp_mgr_data.smp_app_cback(trans_id, bdaddr, device->id_addr.type, event, length, data);
	}
	else
	{
		logw("No application registered for smp callbacks");
	}
}

void smp_mgr_bond_status(UINT8 conn_id, UINT8 status)
{
	UINT8 idx;
	trans_id_t trans_id;
	interface_req_elem_t *req = get_req_to_process();
	logi("");
	if(req == NULL)
	{
		trans_id = INVALID_TRANS_ID;
	}
	else
	{
	smpm_create_bond_param_t* param = (smpm_create_bond_param_t*)(void*)req->parameter;
	trans_id = param->trans_id;
	}
	smpm_dequeue_and_cleanup_from_pending_queue();
	logd("device bond status = %d", status);
#if (PARANOID_STACK == TRUE)
	if(conn_id >= MAX_NUM_CONNECTED_DEVICE)
		return;
#endif
	for (idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
	{
		if (g_local_adapter.app_list[idx])
			if (g_local_adapter.app_list[idx]->app_device_control_cb)
				if(g_local_adapter.app_list[idx]->app_device_control_cb->iLE_bonding_completed_cb)
					g_local_adapter.app_list[idx]->app_device_control_cb->iLE_bonding_completed_cb(trans_id, g_local_adapter.connected_device[conn_id]->bdaddr,
							g_local_adapter.connected_device[conn_id]->bdaddr_type, conn_id, status,
							g_local_adapter.connected_device[conn_id]->id_addr.bdaddr, g_local_adapter.connected_device[conn_id]->id_addr.type);
	}
	if(g_local_adapter.smp_mgr_data.smp_bonding_complete_cb)
	{
		g_local_adapter.smp_mgr_data.smp_bonding_complete_cb(trans_id, g_local_adapter.connected_device[conn_id]->bdaddr, g_local_adapter.connected_device[conn_id]->bdaddr_type, conn_id, status,
			g_local_adapter.connected_device[conn_id]->id_addr.bdaddr, g_local_adapter.connected_device[conn_id]->id_addr.type);
	}
	finish_transac_and_process_new_req();
}
#if (SIGNED_WRITE)
void smp_mgr_data_sign_cback(connected_device_t *device, UINT8 status, UINT8* signed_data)
{
	logi("");
	smpm_dequeue_and_cleanup_from_pending_queue();
	logd("Data sign status = %d", status);
#if (PARANOID_STACK == TRUE)
	if(device == NULL)
	{
		return;
	}
#endif
	if(g_local_adapter.smp_mgr_data.smp_data_siging_complete_cb != NULL)
	{
		UINT8* pp;
		UINT8 *mac = (UINT8*) alloc(SMP_MAC_LEN);
		logd("Calling call back");

		if (!mac)
			return;

		if(status == STATUS_SUCCESS)
		{
			pp = mac + sizeof(UINT32);
			memcpy(mac, &device->local_sign_info.sign_key.counter, sizeof(UINT32));
			REVERSE_ARRAY_TO_STREAM(pp, signed_data, 8);
			hex_dump("Mac", mac,SMP_MAC_LEN);
			g_local_adapter.smp_mgr_data.smp_data_siging_complete_cb(device->idx, status, mac);
			device->local_sign_info.sign_key.counter++;
			if(g_local_adapter.smp_mgr_data.storage_mgr.storage_cb && g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_update_cb)
			{
				UINT8 sc[4];
				UINT8 *pp1 = sc;
				UINT32_TO_STREAM(pp1, device->local_sign_info.sign_key.counter);
				g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_update_cb
								(g_local_adapter.smp_mgr_data.storage_mgr.trans_id, device->id_addr.bdaddr, device->id_addr.type, LOCAL_COUNTER, 4, sc);
			}
			dealloc(mac);
		}
		else
		{
			g_local_adapter.smp_mgr_data.smp_data_siging_complete_cb(device->idx, status, NULL);
		}
		g_local_adapter.smp_mgr_data.smp_data_siging_complete_cb = NULL;
	}
	else
	{
		logw("No callback");
	}
	finish_transac_and_process_new_req();
}
void smp_mgr_data_verify_cback(UINT8 conn_id, UINT8 status)
{
	logi("");
	smpm_dequeue_and_cleanup_from_pending_queue();
	logi("Data verify status = %d", status);
	if(g_local_adapter.smp_mgr_data.smp_sign_verify_complete_cb)
	{
		g_local_adapter.smp_mgr_data.smp_sign_verify_complete_cb(conn_id, status);
	}
	finish_transac_and_process_new_req();
}
#endif /* SIGNED_WRITE */

#if (PRIVACY_FEATURE)
void smp_mgr_rpa_gen_cb()
{
	logi("");
	smpm_dequeue_and_cleanup_from_pending_queue();
	finish_transac_and_process_new_req();
}
void smp_mgr_rpa_res_cb(UINT8 *remote_bd_addr, UINT8 idx, UINT8 status)
{
	smpm_dequeue_and_cleanup_from_pending_queue();
	g_local_adapter.smp_mgr_data.smp_rpa_res_complete_cb(remote_bd_addr, FALSE, idx, status);
	finish_transac_and_process_new_req();
}
#endif /* PRIVACY_FEATURE */
void smp_mgr_init_cb()
{
	logi("");
	do_app_init();
}
void smp_mgr_ext_init_cb()
{
	logi("");
	smpm_dequeue_and_cleanup_from_pending_queue();
	finish_transac_and_process_new_req();
	stack_init_completed(STATUS_SUCCESS);
}

#if (PRIVACY_FEATURE)

void create_clear_resolving_req(void)
{
#if (CONTROLLER_PRIVACY)
	interface_req_elem_t *req;
#endif /*CONTROLLER_PRIVACY */

	logd("");
#if (CONTROLLER_PRIVACY)
	if (LL_PRIVACY_IS_SUPPORTED)
	{
		req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_CLEAR_RESOLVINGLIST, 0, 0);
		if(req)
			gap_req_handler(req);
	}
#endif /*CONTROLLER_PRIVACY */
#if (HOST_PRIVACY)
	{
		memset(g_local_adapter.resolving_list, 0, sizeof(resolving_list_entry_t) * HOST_RESOLVING_LIST_SIZE);
	}
#endif /* HOST_PRIVACY */
}

static void create_add_bonded_dev_to_resolving_req(smp_bonding_key_t *cur_key)
{
#if (CONTROLLER_PRIVACY)
	if (LL_PRIVACY_IS_SUPPORTED)
	{
		interface_req_elem_t    *req;
		dm_resolving_op_param_t *param;
		UINT8 rev_bdaddr[BD_ADDR_LEN];
		UINT8 *rev_bdaddr_ptr;

		req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_ADD_TO_RESOLVINGLIST, 0, sizeof(dm_resolving_op_param_t));
		if(req == NULL)
			return;
		param = (dm_resolving_op_param_t *)req->parameter;

		rev_bdaddr_ptr = rev_bdaddr;
		REVERSE_ARRAY_TO_STREAM(rev_bdaddr_ptr, cur_key->id_bdaddr, BD_ADDR_LEN);
		memset(param, 0, sizeof(dm_resolving_op_param_t));
		param->peer_addr_type = cur_key->id_addr_type;
		memcpy(param->peer_bdaddr, rev_bdaddr, BD_ADDR_LEN);
		if (!(cur_key->keys_distributed & SMP_IRK_RECEIVED))
		{
			logd("We have not received Peer IRK");
		}
		else
			memcpy(param->peer_irk , cur_key->peer_irk, SMP_LTK_LEN);
		memcpy(param->local_irk , cur_key->local_irk, SMP_LTK_LEN);
		gap_req_handler(req);
	}
#endif /* CONTROLLER_PRIVACY */

#if (HOST_PRIVACY)
	{
		UINT8 idx = find_free_slot_in_resolving_list();
		if(idx < HOST_RESOLVING_LIST_SIZE)
		{
			memcpy(g_local_adapter.resolving_list[idx].entry.local_irk, cur_key->local_irk, SMP_IRK_LEN);
			if (!(cur_key->keys_distributed & SMP_IRK_RECEIVED))
			{
				logd("We have not received Peer IRK");
			}
			else
			{
				memcpy(g_local_adapter.resolving_list[idx].entry.peer_id_info.irk, cur_key->peer_irk, SMP_IRK_LEN);
				memcpy(g_local_adapter.resolving_list[idx].entry.peer_id_info.id_addr, cur_key->id_bdaddr, BD_ADDR_LEN);
				g_local_adapter.resolving_list[idx].entry.peer_id_info.id_addr_type = cur_key->id_addr_type;
				g_local_adapter.resolving_list[idx].valid = TRUE;
			}
		}
		else
		{
			logw("Host resolving list full");
		}
	}
#endif /* HOST_PRIVACY */
}
static void remove_device_from_resolving_list(connected_device_t *device)
{
#if (CONTROLLER_PRIVACY)
	if (LL_PRIVACY_IS_SUPPORTED)
	{
		interface_req_elem_t *req;
		dm_resolving_op_param_t *param;
		UINT8 rev_bdaddr[BD_ADDR_LEN];
		UINT8 *rev_bdaddr_ptr;
		req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_REMOVE_FROM_RESOLVINGLIST, 0, sizeof(dm_resolving_op_param_t));
		if(req == NULL)
			return;
		param = (dm_resolving_op_param_t *)req->parameter;

		rev_bdaddr_ptr = rev_bdaddr;
		REVERSE_ARRAY_TO_STREAM(rev_bdaddr_ptr, device->id_addr.bdaddr, BD_ADDR_LEN);
		memset(param, 0, sizeof(dm_resolving_op_param_t));
		param->peer_addr_type = device->id_addr.type;
		memcpy(param->peer_bdaddr, rev_bdaddr, BD_ADDR_LEN);
		gap_req_handler(req);
	}
#endif
#if (HOST_PRIVACY)
	if(device->is_bonded)
	{
		memset(&g_local_adapter.resolving_list[device->bonded_idx], 0, sizeof(resolving_list_t));
	}
#endif

}
#endif /* PRIVACY_FEATURE */

void smp_mgr_save_bonding_keys(connected_device_t *device, smp_bonding_key_t *cur_key)
{
	if(g_local_adapter.smp_mgr_data.storage_mgr.storage_cb && g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->bonding_info_cb)
	{
#if (PRIVACY_FEATURE == TRUE)
		if(cur_key->keys_distributed & SMP_IRK_RECEIVED)
			g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->bonding_info_cb(g_local_adapter.smp_mgr_data.storage_mgr.trans_id, device->bdaddr,
					device->bdaddr_type, cur_key->id_bdaddr, cur_key->id_addr_type, cur_key);
		else
#endif
		{
			g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->bonding_info_cb(g_local_adapter.smp_mgr_data.storage_mgr.trans_id, device->bdaddr,
					device->bdaddr_type, device->bdaddr, device->bdaddr_type, cur_key);
		}
	}
#if (PRIVACY_FEATURE == TRUE)
	if(!(cur_key->keys_distributed & SMP_IRK_RECEIVED) && !(cur_key->keys_distributed & SMP_IRK_DISTRIBUTED))
	{
		logd("IRK was not exchanged during this bonding. Not adding to resolving list");
	}
	else
	{
		logd("Adding the device to resolving list");
		create_add_bonded_dev_to_resolving_req(cur_key);
	}
	if(cur_key->keys_distributed & SMP_IRK_RECEIVED)
	{
		memcpy(device->id_addr.bdaddr, cur_key->id_bdaddr, BD_ADDR_LEN);
		device->id_addr.type = cur_key->id_addr_type;
	}
#endif
}
void smpm_clear_key(connected_device_t *device)
{
#if (PRIVACY_FEATURE == TRUE)
	if((device->link_enc_state.keys_distributed & SMP_IRK_RECEIVED) || (device->link_enc_state.keys_distributed & SMP_IRK_DISTRIBUTED))
	{
		/* Remove the device from resolving list */
		remove_device_from_resolving_list(device);
	}
#endif
	device->link_enc_state.key_size = 0;
	device->link_enc_state.keys_distributed = 0;
	device->link_enc_state.key_type = 0;
	if(g_local_adapter.smp_mgr_data.storage_mgr.storage_cb && g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->clear_key_cb)
	{
		g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->clear_key_cb(g_local_adapter.smp_mgr_data.storage_mgr.trans_id, device->id_addr.bdaddr, device->id_addr.type);
	}
}
#if (HOST_PRIVACY)
static UINT8 find_free_slot_in_resolving_list()
{
	UINT8 idx;
	for(idx = 0; idx < HOST_RESOLVING_LIST_SIZE; idx++)
	{
		if(!g_local_adapter.resolving_list[idx].valid)
		{
			break;
		}
	}
	return idx;
}
#endif /* HOST_PRIVACY */
#endif /* SMP_FEATURE */

