/** @file
  Proximity monitor (client) implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "app_interface.h"

#if (PXP_APP == TRUE)

#ifndef PXP_APP_DBG
#define PXP_APP_DBG TRUE
#endif

#if (PXP_APP_DBG == FALSE)
#undef logd
#define logd(param, ...) {}
#endif

#define LINK_LOSS_UUID		 	0x1803
#define ALERT_LEVEL_UUID 		0x2A06

static BOOLEAN pxp_app_running = FALSE;
static UINT8 appindex;
static UINT8 alert_level = MILD_ALERT;
static UINT8 connected_device_idx = 0;
static UINT8 bdaddr[6] =
{ 0 };
static UINT16 char_handle = 0;

void app_quit(char* arg);
typedef void (handler_func)(char *arg);
typedef struct
{
	const char *cmd_str;
	handler_func *handler;
	const char *help_text;
} cmd_t;

static void app_writeCharacterstic(UINT8* remote_device_address,
		UINT16 char_handle, UINT8 val_len, UINT8 *val_buf,
		BOOLEAN is_response_required)
{
	Gatt_Write_Req(appindex, remote_device_address, char_handle, val_len,
			val_buf, is_response_required);
}

#if 0
UINT8 get_immediate_altert_options()
{

	char *ret;
	char cmd[5];
	UINT8 option;

	logln("Enter the Alter Level");
	logln(" 0 ---- NO ALERT");
	logln(" 1 ---- MILD ALERT");
	logln(" 2 ---- HIGH ALERT");
	logln(" 3 ---- quit");

	ret = fgets(cmd, sizeof(cmd), stdin);
	USE(ret);
	cmd[strlen(cmd) - 1] = '\0';
	option = (UINT8) atoi(cmd);
	return option;

}
#endif
/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void onConnectionStateChanged(UINT8 app_index, UINT8 *remote_bdaddr,
		UINT8 connection_result)
{
//	int option = 0;
	if (connection_result == GATT_CONNECTED)
	{
		//call the function to discover the immediate alert service
		Gatt_Discover_Primary_Service(app_index, remote_bdaddr, LINK_LOSS_UUID);
	} else if (connection_result == GATT_DISCONNECTED)
	{
		/*option = get_immediate_altert_options();
		 if (option == 3) {
		 //Deregister Gatt and quit the app
		 app_quit(NULL);
		 } else {
		 Gatt_Connect_req(appindex,
		 g_local_adapter.discovered_device[connected_device_idx]->bdaddr);
		 }*/

	}
}

/**********************************************************************
 * Function: onServiceDiscovered
 * input parameters:
 *     - remote_device_address    - BD address of the connected device
 *     - service - response buffer length
 *
 * output parameters: void
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void onServiceDiscovered(UINT8* remote_device_address, gatt_service_t** service, UINT16 service_uuid)
{
	//check  if the link loss service is supported by server or not
	UINT8 service_slot = get_service_idx_by_uuid(
			get_connected_device_idx_by_bdaddr(remote_device_address),
			LINK_LOSS_UUID);
	/* Service not found */
	if (service_slot == MAX_NUMBER_OF_SERV_PER_DEV)
		return;
	logd(" pxp_monitor_main service[0]->uuid:%2x", service[0]->uuid);
	Gatt_Discover_all_chars(appindex, remote_device_address, LINK_LOSS_UUID);
}

/**********************************************************************
 * Function: onServiceDiscovered
 * input parameters:
 *     - remote_device_address    - BD address of the connected device
 *     - service - response buffer length
 *
 * output parameters: void
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void onCharacteristicDiscovered(UINT8* remote_device_address,
		gatt_service_t** service, UINT8 gatt_service_idx)
{
	UINT8 i;
	UINT8 service_slot = get_service_idx_by_uuid(
			get_connected_device_idx_by_bdaddr(remote_device_address),
			LINK_LOSS_UUID);
	/* Service not found */
	if (service_slot == MAX_NUMBER_OF_SERV_PER_DEV)
		return;
	for (i = 0; i < MAX_NUMBER_OF_CHAR_PER_SERV; i++)
	{
		if (service[service_slot] == NULL )
			continue;
		if (service[service_slot]->charcteristic[i] == NULL )
			continue;
		if (service[service_slot]->charcteristic[i]->uuid == ALERT_LEVEL_UUID)
		{
			logi("Read char value. Val handle:%d",
					service[service_slot]->charcteristic[i]->value_handle);
			memcpy(bdaddr, remote_device_address, 6);
			char_handle = service[service_slot]->charcteristic[i]->value_handle;
			Gatt_Read_Characteristic_value(appindex, remote_device_address,
					service[service_slot]->charcteristic[i]->value_handle);
		}
	}
}
/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void onCharacteristicRead(UINT8* remote_device_address,
		UINT16 characteristic_handle, UINT8* data, UINT8 len)
{
	logd("Characteristic read:%x characteristic_handle:%2x char_handle:%2x",
			*data, characteristic_handle, char_handle);
	if (characteristic_handle == char_handle)
		app_writeCharacterstic(remote_device_address, char_handle,
				sizeof(alert_level), &alert_level, TRUE);
}
/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void onCharacteristicWrite(UINT8* remote_device_address,
		UINT16 characteristic_handle, UINT8* data, UINT8 len)
{
	//Gatt_Disconnect_req(appindex, remote_device_address);

}
/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_gatt_register()
{
	if (g_local_adapter.adapter_state == INTERFACE_ADAPTER_STATE_OFF)
	{
		loge("Adapter disabled! Please enable first...");
		return;
	}

	gatt_app_info_t *pxp_app_info = (gatt_app_info_t*) alloc(
			sizeof(gatt_app_info_t));

	pxp_app_info->onConnectionStateChanged = onConnectionStateChanged;
	pxp_app_info->onServiceDiscovered = onServiceDiscovered;
	pxp_app_info->onCharacteristicDiscovered = onCharacteristicDiscovered;
	pxp_app_info->onCharacteristicRead = onCharacteristicRead;
	pxp_app_info->onCharacteristicWrite = onCharacteristicWrite;
	//register the application with GATT to get the callbacks
	Gatt_Register(&appindex, pxp_app_info);
}

/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_gatt_deregister()
{
	if (g_local_adapter.adapter_state == INTERFACE_ADAPTER_STATE_OFF)
	{
		loge("Adapter disabled! Please enable first...");
		return;
	}
	//deregister the application with GATT
	Gatt_DeRegister(appindex);
}
/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_bt_on()
{
	if (g_local_adapter.adapter_state == INTERFACE_ADAPTER_STATE_ON)
	{
		loge("Already enabled!");
		return;
	}
	init_stack("/dev/ttyUSB0", 115200);
	g_local_adapter.adapter_state = INTERFACE_ADAPTER_STATE_ON;

}
/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_bt_off(char* arg)
{
	UINT8 i;
	if (g_local_adapter.adapter_state == INTERFACE_ADAPTER_STATE_ON)
	{
		for (i = 0; i < MAX_NUM_CONNECTED_DEVICE; i++)
			if (g_local_adapter.connected_device[i])
				Gatt_Disconnect_req(appindex,
						g_local_adapter.connected_device[i]->bdaddr);
		app_gatt_deregister();
		cleanup_stack();
		g_local_adapter.adapter_state = INTERFACE_ADAPTER_STATE_OFF;
	}
}

/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_connect()
{
	UINT8 id;
	char cmd[5];
	char *ret;
	if (g_local_adapter.adapter_state == INTERFACE_ADAPTER_STATE_OFF)
	{
		loge("Adapter disabled! Please enable first...");
		return;
	}
	display_discovered_device_list();
	log("Enter device ID to connect (enter > 8 to cancel): ");
	ret = fgets(cmd, sizeof(cmd), stdin);
	USE(ret);
	cmd[strlen(cmd) - 1] = '\0';
	id = (UINT8) atoi(cmd);
	if (id > 8)
		return;
	connected_device_idx = id;
	if (g_local_adapter.discovered_device[id])
		Gatt_Connect_req(appindex, g_local_adapter.discovered_device[id]->bdaddr);
}
/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_disconnect(char* arg)
{
	UINT8 id;
	char cmd[5];
	char *ret;
	if (g_local_adapter.adapter_state == INTERFACE_ADAPTER_STATE_OFF)
	{
		loge("Adapter disabled! Please enable first...");
		return;
	}

	display_connected_device_list();
	log("Enter device ID to disconnect (enter > 8 to cancel): ");
	ret = fgets(cmd, sizeof(cmd), stdin);
	USE(ret);
	cmd[strlen(cmd) - 1] = '\0';
	id = (UINT8) atoi(cmd);
	if (id > 8)
		return;
	if (g_local_adapter.connected_device[id])
		Gatt_Disconnect_req(appindex, g_local_adapter.connected_device[id]->bdaddr);
}

/******************************************************
 * Callback functions
 ******************************************************/
void adapter_state_cb(UINT8 result, UINT8 state)
{
	if (result == FALSE)
	{
		loge("Operation NOT successful.");
		return;
	}
	if (state == INTERFACE_ADAPTER_STATE_ON)
	{
		logd("INTERFACE_ADAPTER_STATE_ON");
		app_gatt_register();
	} else if (state == INTERFACE_ADAPTER_STATE_TURNNING_ON)
	{
		logd("INTERFACE_ADAPTER_STATE_TURNNING_ON");
	} else if (state == INTERFACE_ADAPTER_STATE_OFF)
	{
		logd("INTERFACE_ADAPTER_STATE_OFF");
	}
}

void scan_completed_cb(void)
{
	//app_connect();
}

/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_scan_enable(char* arg)
{
	if (g_local_adapter.adapter_state == INTERFACE_ADAPTER_STATE_OFF)
	{
		//app_bt_on();
		//loge("Adapter disabled! Please enable first...");
		return;
	} else
	{
		gap_start_scan(0, TRUE);
	}
	//gap_start_scan(0, 1);
	//app_connect();
}
/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_scan_disable(char* arg)
{
	if (g_local_adapter.adapter_state == INTERFACE_ADAPTER_STATE_OFF)
	{
		loge("Adapter disabled! Please enable first...");
		return;
	}
	gap_stop_scan();
}

void app_adv_enable(char* arg)
{
	if (g_local_adapter.adapter_state == INTERFACE_ADAPTER_STATE_OFF)
	{
		loge("Adapter disabled! Please enable first...");
		return;
	}
	gap_start_advertise(0, GAP_ADV_TYPE_CONNECTABLE_UNDIRECTED);
}

void app_adv_disable(char* arg)
{
	if (g_local_adapter.adapter_state == INTERFACE_ADAPTER_STATE_OFF)
	{
		loge("Adapter disabled! Please enable first...");
		return;
	}
	gap_stop_advertise();
}

/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_send_alert(char* arg)
{
	UINT8 option = 0; //get_immediate_altert_options();
	char *ret;
	char cmd[5];

	logi(" 0 ----> NO ALERT");
	logi(" 1 ----> MILD ALERT");
	logi(" 2 ----> HIGH ALERT");
	log("Enter the Alert Level: ");
	ret = fgets(cmd, sizeof(cmd), stdin);
	USE(ret);
	cmd[strlen(cmd) - 1] = '\0';
	option = (UINT8) atoi(cmd);
	alert_level = option;

	app_writeCharacterstic(bdaddr, char_handle, sizeof(alert_level),
			&alert_level, TRUE);
}

/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_quit(char* arg)
{
	app_bt_off(NULL );
	pxp_app_running = FALSE;
}

void app_help(char* arg);
const cmd_t cmd_arr[] =
{
{ "e", app_bt_on, "Turn on BT" },
/*
{ "x", app_bt_off, "Turn off BT" },
*/
{ "s", app_scan_enable, "Start Scan" },
/*
{ "n", app_scan_disable, "Stop Scan" },
{ "v", app_adv_enable, "Start Advertise" },
{ "b", app_adv_disable, "Stop Advertise" },
*/
{ "c", app_connect, "Connect to a device" },
{ "d", app_disconnect, "Disconnect from a device" },
{ "a", app_send_alert, "Change alert level" },
{ "q", app_quit, "Quit the application" },
{ "h", app_help, "Display this menu" },
{ "_end_", NULL } };

/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
void app_help(char* arg)
{
	UINT8 i;
	for (i = 0;; i++)
	{
		if (strcmp(cmd_arr[i].cmd_str, "_end_") == 0)
			break;
		logln("%s - %s", cmd_arr[i].cmd_str, cmd_arr[i].help_text);
	}
}

/**********************************************************************
 * Function: onConnectionStateChanged
 * input parameters:
 *     - app_index    - connected device index
 *     - connected_device_idx - connected device index
 *     - connection_result - connected or disconnected
 * output parameters: Always TRUE
 * Description: Decode the error response received and
 *              provide to the upper layer.
 *
 *********************************************************************/
int main(int argc, char *argv[])
{
	char cmd[128];
	int i = 0;
	int reached_end = FALSE;
	char *ret;
	g_local_adapter.adapter_state = INTERFACE_ADAPTER_STATE_OFF;
	pxp_app_running = TRUE;
	logln(">>>>> PROXIMITY MONITOR <<<<<");
	while (pxp_app_running)
	{
		app_help(NULL );
		log("$ ");
		ret = fgets(cmd, sizeof(cmd), stdin);
		USE(ret);
		cmd[strlen(cmd) - 1] = '\0';
		if (strlen(cmd) != 0)
		{
			reached_end = FALSE;
			for (i = 0;; i++)
			{
				if (strcmp(cmd_arr[i].cmd_str, "_end_") == 0)
				{
					reached_end = TRUE;
					break;
				}
				if (strcmp(cmd_arr[i].cmd_str, cmd) == 0)
				{
					cmd_arr[i].handler(NULL );
					break;
				}
			}
			if (reached_end == TRUE)
			{
				logd("No matching command found");
				app_help(NULL );
			}
		}
	}
	return 0;
}
#endif
