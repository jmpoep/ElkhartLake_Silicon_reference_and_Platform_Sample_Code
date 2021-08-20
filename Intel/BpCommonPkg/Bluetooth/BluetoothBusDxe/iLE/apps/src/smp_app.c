/** @file
  Security Manager application source.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <stdlib.h>
#include "app_interface.h"
#include "smp_app.h"

#define MODULE_DBG_LVL SMP_APP_DBG_LVL
#include "log.h"

#if (SMP_APP == TRUE)

static smp_app_t smp_app_cb;

#if (TARGET_LINUX == TRUE)
UINT16 get_int_input_smp(char *display_prompt)
{
	UINT16 id;
	char *ret;
	char cmd[40];
	log("%s", display_prompt);
	fflush(stdin);
	ret = fgets(cmd, sizeof(cmd), stdin);
	USE(ret);
	cmd[strlen(cmd) - 1] = '\0';
	id = (UINT16) atoi(cmd);
	fflush(stdin);
	return id;
}
UINT16 get_hex_input_smp(char *display_str)
{
	char handle_str[10];
	log("%s", display_str);
	char *ret = fgets(handle_str, sizeof(handle_str), stdin);
	if (handle_str[strlen(handle_str) -1] == '\n')
		handle_str[strlen(handle_str) -1] = '\0';
	USE(ret);
	return strtol(handle_str, NULL, 16);
}
#endif
/*********************************************************************
 * 					Call Back functions
 *********************************************************************/
void smp_app_cback(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 event, UINT8 length, UINT8* data)
{
	logd("%s", __func__);
	logd("Event = %d", event);
	UINT32 passkey;
	switch(event)
	{
	case SMP_AUTHORISATION_REQ_EVT:
		log("**************************************************************************************************\
				\n			Pairing Request from the device\n");
		log("%x:%x:%x:%x:%x:%x\n", bdaddr[0], bdaddr[1], bdaddr[2], bdaddr[3], bdaddr[4], bdaddr[5]);
		memcpy(smp_app_cb.remote_bdaddr, bdaddr, BD_ADDR_LEN);
		smp_app_cb.remote_bdaddr_type = bdaddr_type;
		log("Please use smp_approve_bonding command to approve/reject this connection\n");
		break;
	case SMP_KEY_READY_EVT:
		memcpy(&passkey, data, length);
		log("***************************************************************************************************\
				\n		Pass Key Generated is\n %06d\n",passkey);
		log("Please key in this pass key in the other device\n");
		break;
	case SMP_PASSKEY_REQ_EVT:
		memcpy(smp_app_cb.remote_bdaddr, bdaddr, BD_ADDR_LEN);
		smp_app_cb.remote_bdaddr_type = bdaddr_type;
		log("***************************************************************************************************\
				\n		Please Input the passkey displayed on other device\n");
		log("Please use smp_input_passkey command to input the passkey\n");
		break;
#if (SECURE_CONNECTION)
	case SMP_NUMERIC_COMPARISON_EVT:
		memcpy(smp_app_cb.remote_bdaddr, bdaddr, BD_ADDR_LEN);
		smp_app_cb.remote_bdaddr_type = bdaddr_type;
		memcpy(&passkey, data, length);
		log("***************************************************************************************************\
				\n		Numeric comparison Generated is\n %06d\n",passkey);
		log("Use smp_nc_approve to confirm whether the number is same on the other device\n");
		break;
#endif /* SECURE_CONNECTION */
	}
}
void smp_app_register_application_cb(UINT8 app_handle, BOOLEAN result)
{
	logd("");
	if (result == TRUE)
	{
		logd("app_handle:%d", app_handle);
		smp_app_cb.app_handle = app_handle;
	}
}
void smp_stack_initialized_cb(BOOLEAN initialized)
{
	logi("");
	if (initialized)
	{
		trans_id_t new_trans_id;
		add_appid_to_trans_id(&new_trans_id, smp_app_cb.app_handle);
		iLE_smp_register(new_trans_id, &smp_app_cback);
	}
}

void smp_input_passkey(UINT8* arg)
{
	UINT32 passkey;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, smp_app_cb.app_handle);
#if (TARGET_LINUX == TRUE)
	char *ret;
	char cmd[10];
	log("Enter the passkey:");
	ret = fgets(cmd, sizeof(cmd), stdin);
	USE(ret);
	passkey = (UINT32) atoi(cmd);
#else
	passkey = 0;
#endif
	iLE_send_passkey(new_trans_id, smp_app_cb.remote_bdaddr, smp_app_cb.remote_bdaddr_type, passkey);
}

void smp_approve_bonding(UINT8* arg)
{
	UINT8 id;
	trans_id_t new_trans_id = 0;
	UINT8 auth_level_min = 0x00;
	UINT8 key_size_min = 7;

	add_appid_to_trans_id(&new_trans_id, smp_app_cb.app_handle);
#if (TARGET_LINUX == TRUE)
	char *ret;
	char cmd[5];
	log("Enter 1(to approve the pairing) 0(cancel the pairing)\n");
	ret = fgets(cmd, sizeof(cmd), stdin);
	USE(ret);
	cmd[strlen(cmd) - 1] = '\0';
	id = (UINT8) atoi(cmd);
	log("Enter the minimum authentication requirement\n");
	log("0x00 - Legacy pairing, no mitm\n");
	log("0x04 - Legacy pairing, with mitm\n");
	log("0x08 - Secure pairing, no mitm\n");
	log("0x0C - Secure pairing, with mitm\n");
	auth_level_min = get_hex_input_smp("Enter min auth level(in hex):");
	log("Please input the minimum encryption key size required for this pairing (in the range 7 - 16)\n");
	key_size_min = get_int_input_smp("Enter the desired min key_size:");
#else
	id = 0;
#endif
	iLE_send_authorization(new_trans_id,smp_app_cb.remote_bdaddr, smp_app_cb.remote_bdaddr_type, id, auth_level_min, key_size_min);
}

#if ( SECURE_CONNECTION )
void smp_nc_approve(UINT8* arg)
{
	UINT8 id;
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, smp_app_cb.app_handle);
#if (TARGET_LINUX == TRUE)
	char *ret;
	char cmd[5];
	log("Enter 1(to confirm same value) 0(cancel the pairing)");
	ret = fgets(cmd, sizeof(cmd), stdin);
	USE(ret);
	cmd[strlen(cmd) - 1] = '\0';
	id = (UINT8) atoi(cmd);
#else
		id = 0;
#endif
		iLE_smp_send_nc_result(new_trans_id,smp_app_cb.remote_bdaddr, smp_app_cb.remote_bdaddr_type, id);
}
#endif /* SECURE_CONNECTION */

const cmd_t smp_cmd_arr[] = {
{ "approve_bonding", smp_approve_bonding },
{ "input_passkey", smp_input_passkey },
#if ( SECURE_CONNECTION )
{ "nc_approve", smp_nc_approve },
#endif /* SECURE_CONNECTION */
{ "_end_", NULL }
};
device_control_callbacks_t smp_dev_cb =
{
	.iLE_stack_initialized_cb = smp_stack_initialized_cb,
	.iLE_scan_completed_cb = NULL
};

void smp_app_init()
{
	logd("Starting SMP App");
	iLE_register_application(&smp_dev_cb, NULL, "smp", smp_cmd_arr, smp_app_register_application_cb);
}

void smp_app_cleanup()
{
	logd("%s", __func__);
	iLE_deregister_application(smp_app_cb.app_handle);
}

#endif //#if (SMP_APP == TRUE)
