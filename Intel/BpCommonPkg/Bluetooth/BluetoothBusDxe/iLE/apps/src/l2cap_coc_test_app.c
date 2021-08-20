/** @file
  COC test application implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "app_interface.h"
#include "l2cap_coc_test_app.h"

#define MODULE_DBG_LVL	DBG_LVL_INFO
#include "log.h"

#if (L2CAP_COC_TEST_APP == TRUE)

static l2cap_coc_test_app_data_t l2cap_coc_test_app_data;

void l2cap_coc_test_app_on_lc_register_cb(trans_id_t trans_id, UINT16 psm, INT8 status)
{
	if (status == STATUS_SUCCESS)
	{
		logd("Registered. app_id:%d PSM:%d", get_appid_from_transid(trans_id), psm);
	}
}

void l2cap_coc_test_app_on_lc_connection_cmpl_cb(trans_id_t trans_id, UINT8 conn_id, UINT16 psm, UINT8 coc_handle, UINT16 r_mtu, UINT8 initial_credit, INT8 status)
{
	l2cap_coc_test_app_data.conn_id_coc_handle[conn_id].coc_handle_idx_list[coc_handle] = TRUE;
}

void l2cap_coc_test_app_on_lc_recv_data_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle, UINT8 *buffer, UINT16 buffer_len)
{
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, l2cap_coc_test_app_data.app_handle);
	if (l2cap_coc_test_app_data.conn_id_coc_handle[conn_id].coc_handle_idx_list[coc_handle] == TRUE)
	{
		hex_dump("l2cap_coc_test_app_on_lc_recv_data_cb", buffer, buffer_len);
		iLE_l2cap_coc_send_data(new_trans_id, conn_id, coc_handle, buffer, buffer_len);
	}
	else
	{
		loge("Data from Unknown channel conn_id:%d coc_handle:%d", conn_id, coc_handle);
	}
}

void l2cap_coc_test_app_on_lc_disconnection_cmpl_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle, UINT8 status)
{
	l2cap_coc_test_app_data.conn_id_coc_handle[conn_id].coc_handle_idx_list[coc_handle] = FALSE;
}

static l2cap_coc_callbacks_t l2cap_coc_callbacks =
{
	.register_cb =			l2cap_coc_test_app_on_lc_register_cb,
	.authorisation_cb = 	NULL, /* TODO: Implement */
	.connection_cmpl_cb =	l2cap_coc_test_app_on_lc_connection_cmpl_cb,
	.flow_control_cb =		NULL, /* TODO: Implement */
	.recv_data_cb =			l2cap_coc_test_app_on_lc_recv_data_cb,
	.disconnect_cmpl_cb = 	l2cap_coc_test_app_on_lc_disconnection_cmpl_cb
};

static void l2cap_coc_test_app_register_cb(UINT8 app_handle, BOOLEAN result)
{

	if (result == TRUE)
	{
		l2cap_coc_test_app_data.app_handle = app_handle;
		logi("app_handle:%d", app_handle);
	}
}

static void l2cap_coc_test_app_stack_initalized_cb(BOOLEAN initialized)
{
	logi("");
	if (initialized)
	{
		/* Register l2cap coc PSM */
		trans_id_t new_trans_id = 0;
		add_appid_to_trans_id(&new_trans_id, l2cap_coc_test_app_data.app_handle);
		iLE_l2cap_coc_register(new_trans_id, L2CAP_COC_LE_DYNAMIC_PSM, L2CAP_COC_LE_MTU, &l2cap_coc_callbacks, FALSE);
	}
}

static void l2cap_coc_test_app_on_connected_cb(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 result, BOOLEAN from_remote, UINT8 *id_addr, UINT8 id_addr_type)
{
	if (!from_remote)
		return;

	if (result == STATUS_SUCCESS)
	{
		logd("Connected as server!");
	}
	else
	{
		logd("Connection failed!");
	}
}

static void l2cap_coc_test_app_on_disconnected_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 result)
{
	logd("");
}

static device_control_callbacks_t dev_cb =
{
	.iLE_stack_initialized_cb = 		l2cap_coc_test_app_stack_initalized_cb,
	.iLE_on_connected_cb = 				l2cap_coc_test_app_on_connected_cb,
	.iLE_on_disconnected_cb = 			l2cap_coc_test_app_on_disconnected_cb,
};

void l2cap_coc_test_app_init(char *arg)
{
	logi("");
	memset(&l2cap_coc_test_app_data, 0, sizeof (l2cap_coc_test_app_data_t));

	if (iLE_register_application(&dev_cb, NULL, NULL, NULL, l2cap_coc_test_app_register_cb))
	{
		logd("GAP service application registered");
		return;
	}
}

void l2cap_coc_test_app_cleanup(char *arg)
{
	logi("");
	iLE_deregister_application(l2cap_coc_test_app_data.app_handle);
	logd("Deregister done");
}
#endif // l2cap_coc_test_APP == TRUE
