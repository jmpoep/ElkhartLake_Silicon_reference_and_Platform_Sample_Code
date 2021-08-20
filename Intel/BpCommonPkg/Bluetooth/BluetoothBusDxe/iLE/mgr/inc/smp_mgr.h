/** @file
  SMP manager header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef SMP_MGR_H_
#define SMP_MGR_H_

#include "bt_types.h"
#include "device_struct.h"
#include "int_interface.h"

/* SMP database security state*/
#define SMP_MGR_STATE_NONE 				0
#define SMP_MGR_STATE_AUTHORISING		1
#define SMP_MGR_STATE_AUTHORISED		2
#define SMP_MGR_STATE_UNAUTHORISED		3
#define SMP_MGR_STATE_AUTHENTICATING	4
#define SMP_MGR_STATE_AUTHENTICATED		5
#define SMP_MGR_STATE_UNAUTHENTICATED	6
#define SMP_MGR_STATE_ENCRYPTING		7
#define SMP_MGR_STATE_ENCRYPTED			8
#define SMP_MGR_STATE_ENC_PENDING		9

#define SMP_MGR_FAILURE			0xFF

#define SMP_MAC_LEN 0x0c

typedef struct
{
	UINT8 conn_id;
	UINT8 auth_level_min;
	UINT8 key_size_min;
	trans_id_t trans_id;
	bonding_complete_cb_t cb;
} smpm_create_bond_param_t;

typedef struct
{
	UINT8 remote_bd_addr[BD_ADDR_LEN];
	UINT8 addr_type;
	trans_id_t trans_id;
} smpm_remove_bond_param_t;

typedef struct
{
	UINT8 app_handle;
	UINT16 data_len;
	connected_device_t *device;
	data_siging_complete_cb_t cback;
	UINT8 data[0];
} smpm_sign_data_param_t;

typedef struct
{
	UINT8 app_handle;
	UINT16 data_len;
	connected_device_t *device;
	sign_verify_complete_cb_t cback;
	UINT8 data[0];
}smpm_sign_verify_param_t;

typedef struct
{
	UINT8 rpa[BD_ADDR_LEN];
	BOOLEAN local;
	rpa_complete_cb_t cback;
}smpm_rpa_resolve_param_t;

typedef struct
{
	UINT8 remote_bd_addr[BD_ADDR_LEN];
	trans_id_t trans_id;
	UINT32 passkey;
} smpm_send_passkey_param_t;

typedef struct
{
	UINT8 remote_bd_addr[BD_ADDR_LEN];
	UINT8 authorization;
	UINT8 auth_level_min;
	UINT8 key_size_min;
	trans_id_t trans_id;
} smpm_send_authorization_param_t;
typedef struct
{
	UINT8 remote_bd_addr[BD_ADDR_LEN];
	UINT8 authorization;
	trans_id_t trans_id;
} smpm_send_nc_result_param_t;


typedef struct
{
	smp_app_cb_t smp_mgr_cb;
	trans_id_t trans_id;
} smpm_smp_register_param_t;

typedef struct
{
       storage_callbacks_t *storage_cb;
       trans_id_t trans_id;
}smpm_storage_register_param_t;

typedef struct
{
       trans_id_t trans_id;
       UINT8 bdaddr[BD_ADDR_LEN];
       UINT8 bdaddr_type;
       UINT8 key_type;
       BOOLEAN is_valid;
       UINT32 alignment; // Required for alignment. Do not remove
       UINT8 key_value[0];
}smpm_set_key_param_t;


#if (SMP_FEATURE)
/*
 *  Functions used by lower layer (SMP)
 */
void smp_mgr_bond_status(UINT8 conn_id, UINT8 status);
void smp_mgr_data_sign_cback(connected_device_t *device, UINT8 status, UINT8* signed_data);
void smp_mgr_data_verify_cback(UINT8 conn_id, UINT8 status);
void smp_mgr_rpa_res_cb(UINT8 *remote_bd_addr, UINT8 idx, UINT8 status);
void smp_mgr_rpa_gen_cb();
void smp_mgr_init_cb();
void smp_mgr_ext_init_cb();
void smp_mgr_save_bonding_keys(connected_device_t *device, smp_bonding_key_t *cur_key);
void smpm_clear_key(connected_device_t *device);
void smp_mgr_cback(UINT8* bdaddr, UINT8 event,UINT8* data, UINT8 length);
#endif

INT8 smpm_req_handler(interface_req_elem_t* incoming_req);

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
INT8 smpm_smp_register(trans_id_t trans_id, smp_app_cb_t smp_app_cb);

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
INT8 smpm_send_passkey(trans_id_t trans_id, UINT8 *remote_bd_addr, UINT32 passkey);

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
INT8 smpm_send_authorization(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 authorization, UINT8 auth_level_min, UINT8 key_size_min);

#if (SECURE_CONNECTION)
INT8 smpm_send_nc_result(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 authorization);
#endif /* SECURE_CONNECTION*/

INT8 smpm_storage_register(trans_id_t trans_id, storage_callbacks_t *storage_cb);

INT8 smpm_key_response(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 key_type, BOOLEAN is_valid, void* key_value);
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
INT8 smp_mgr_init();

/** @brief This is called by device manger when the stack is shutdown
 *
 * Function: smp_mgr_cleanup
 * 				This function shutdown the lower layer (SMP).
  * @return Error code.
 */
INT8 smp_mgr_cleanup();

#endif /* SMP_MGR_H_ */
