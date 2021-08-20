/** @file
  Adaptation layer for parsing Vendor Specific HCI commands and calling respective
  APIs and generating VS HCI events

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*******
Includes
********/
#include "config_host.h"
#include "app_interface.h"

#if (TARGET_THREADX_RW == TRUE)
#include "hci_msg.h"
#include "hci_error.h"
#include "hci.h"
#include "tl.h"
#include "tx_app_define.h"
#include "qm_mailbox.h"
#include "mbox_ble.h"
#include "wdog.h"
#ifdef DBG_FRMWRK
#include "dbg_frmwrk.h"
#endif
#endif

#define MODULE_DBG_LVL HCI2ILE_ADAPT_APP_DBG_LVL
#include "log.h"

#if (HCI2ILE_ADAPT_APP == TRUE)

#include "hci2ile_internal.h"
#include "hci2ile_interface.h"

#define DBG_EVT_HEADER (sizeof(UINT32) + CB_PARAM_OFFSET + TRANS_ID_SIZE_BYTES)

RETENTION_SECTION_START
static UINT8 adapt_app_handle;
static trans_id_t smp_trans_id;
static bool panic  = 0;
RETENTION_SECTION_END

/** @brief: This function maps the existing function in the firmware to send HCI events with the function defined in hci2ile_adaptation.c
*			This ensures easy porting across platforms as this function is called from the hci layer of the platform and
*		no other change needs to be done anywhere else
*
*Function: hci2ile_Initialize:
*			This is similar to register app callback. Here the hci thread gives 2 functions which are used to send cmd cplt event
*			and debug event as defined in the platform's firmware code.
*			@param status_event_gen_func_from_fw : the function used to generate cmd cplt event in the fw code goes here.
*			@paramt debug_event_gen_func_from_fw : the function used to generate debug events in the fw code goes here.
*			the mapping of the same is done in hci2ile_adaptation.c
*/


static hci2ile_Event_Dispatch_cb_t hci2ile_Event_cb;				//function used in this file to generate debug events
static hci2ile_Status_Dispatch_cb_t hci2ile_Status_cb;				//function used in this file to generate command complete events.

void hci2ile_initialize(hci2ile_Status_Dispatch_cb_t status_event_gen_func_from_fw, hci2ile_Event_Dispatch_cb_t debug_event_gen_func_from_fw)
	{
		hci2ile_Event_cb = debug_event_gen_func_from_fw;
		hci2ile_Status_cb = status_event_gen_func_from_fw;
	}

#if (TARGET_THREADX_RW == TRUE)

/*********************************************************************

This function packs and sends command complete/status event to the host (host app)

**********************************************************************/
static void hci2ile_command_complete_event_send(trans_id_t trans_id, uint16_t opcode, UINT8 api_id, UINT8 status)
{
	UINT8 *p_buf, *p;
	logi("");
	p_buf = app_alloc(OS_BLE_DATA_SIZE);
	if(!p_buf)
	{
		return;
	}

	p = p_buf + sizeof(uint32_t);
	*p++ = HCI_EVT_MSG_TYPE;

	//pack event code
	*p++ = (uint8_t)HCI_CMD_CMPL_EVT_CODE;

	//pack command complete event parameter length
	*p++ = 7;

	//pack the number of h2c packets
	*p++ = 1;

	//pack opcode
	UINT16_TO_STREAM(p,opcode);

    //pack status
	*p++ = status;

	//pack trans_id
    TRANS_ID_TO_STREAM(p, trans_id);

	*p = api_id;

	//Post to transport thread
	tx_queue_send(&st_to_tr_msg_queue, &p_buf, TX_NO_WAIT);
	tx_event_flags_set(&tr_evnt_flags, OS_EVNT_FLG_HCI_EVNT, TX_OR);
}

/* Defined to post extended parameters in command complete packet, like local mtu size, local bd address etc */
static void hci2ile_command_complete_event_send_ext(trans_id_t trans_id, uint16_t opcode, UINT8 api_id, UINT8 status, UINT8 stream_len, UINT8 *stream)
{
	UINT8 *p_buf, *p;
	logi("");
	p_buf = app_alloc(OS_BLE_DATA_SIZE);
	if(!p_buf)
	{
		return;
	}

	p = p_buf + sizeof(uint32_t);
	*p++ = HCI_EVT_MSG_TYPE;

	//pack event code
	*p++ = (uint8_t)HCI_CMD_CMPL_EVT_CODE;

	//pack command complete event parameter length
	*p++ = 7 + stream_len;

	//pack the number of h2c packets
	*p++ = 1;

	//pack opcode
	UINT16_TO_STREAM(p,opcode);

	//pack status
	*p++ = status;

	//pack trans_id
	TRANS_ID_TO_STREAM(p, trans_id);

	//pack api id
	UINT8_TO_STREAM(p, api_id);

	//pack extended stream parameter
	memcpy(p, stream, stream_len);

	//Post to transport thread
	tx_queue_send(&st_to_tr_msg_queue, &p_buf, TX_NO_WAIT);
	tx_event_flags_set(&tr_evnt_flags, OS_EVNT_FLG_HCI_EVNT, TX_OR);
}

static void hci2ile_callback_send(trans_id_t trans_id, UINT8 len, UINT8* buff)
{
	UINT8 * p ;
	p = buff + sizeof(uint32_t);
	*p++ = HCI_EVT_MSG_TYPE;

	//pack event code
	*p++ = (uint8_t)HCI_DBG_EVT_CODE;

	//pack command complete event parameter length
	*p++ = len+1+TRANS_ID_SIZE_BYTES;
	*p++ = HCI2ILE_EVENT_ID;
	//Pack trans_id
	TRANS_ID_TO_STREAM(p, trans_id);

	//Post to transport thread
	tx_queue_send(&st_to_tr_msg_queue, &buff, TX_NO_WAIT);
	tx_event_flags_set(&tr_evnt_flags, OS_EVNT_FLG_HCI_EVNT, TX_OR);

}

#else /* TARGET_THREADX_RW == TRUE */

/*********************************************************************

This function packs and sends command complete/status event to the host (host app)

**********************************************************************/
static void hci2ile_callback_send(trans_id_t trans_id, UINT8 len, UINT8* buff)
{
    UINT8 *pbuff = buff + DBG_EVT_HEADER - (1 + TRANS_ID_SIZE_BYTES);
    UINT8 *p = pbuff;
    UINT8_TO_STREAM(p, HCI2ILE_EVENT_ID);
    TRANS_ID_TO_STREAM(p, trans_id); /* Note: App Handle within trans_id is irrelevant to upper layers */
	hci2ile_Event_cb(HCI2ILE_EVENT_CODE , len + 1 + TRANS_ID_SIZE_BYTES , pbuff);
	app_dealloc(buff);
}

static void hci2ile_command_complete_event_send(trans_id_t trans_id, UINT16 op_code, UINT8 api_id, UINT8 status)
{
	UINT8 au8CmdCptbuffer[TRANS_ID_SIZE_BYTES + 2];
	UINT8 *p = au8CmdCptbuffer;
    UINT8_TO_STREAM(p, status);
    TRANS_ID_TO_STREAM(p, trans_id);
    UINT8_TO_STREAM(p, api_id);
	hci2ile_Status_cb(op_code, TRANS_ID_SIZE_BYTES + 2 , au8CmdCptbuffer); //this function posts an HCI event to the transport thread
}

/* Defined to post extended parameters in command complete packet, like local mtu size, local bd address etc */
static void hci2ile_command_complete_event_send_ext(trans_id_t trans_id, UINT16 op_code, UINT8 api_id, UINT8 status, UINT8 stream_len, UINT8 *stream)
{
	UINT8 cmd_len = TRANS_ID_SIZE_BYTES + 2 + stream_len; /*2 bytes for status and api_id */
	UINT8* cmd_buffer = app_alloc(cmd_len);
	UINT8 *p = cmd_buffer;
	UINT8_TO_STREAM(p, status);
	TRANS_ID_TO_STREAM(p, trans_id);
	UINT8_TO_STREAM(p, api_id);
	memcpy(p, stream, stream_len);
	hci2ile_Status_cb(op_code, cmd_len , cmd_buffer); //this function posts an HCI event to the transport thread
	app_dealloc(cmd_buffer);
}

#endif /* TARGET_THREADX_RW == TRUE */

#if 0
static BOOLEAN hci2ile_command_checker(UINT8 parameter_1,UINT8 length); //defined later @line #1041
#endif

/**********************************
externs used for registering app
**********************************/

static device_control_callbacks_t dev_cb;
static gatt_callbacks_t gatt_cb;

static void HAL_register_application_cb(UINT8 app_handle, BOOLEAN result);
#if (L2CAP_COC == TRUE)
static l2cap_coc_callbacks_t l2cap_coc_cbs;
#endif
static storage_callbacks_t storage_cbs;
static void HAL_smp_cb(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 event, UINT8 length, UINT8* data);


/**********************************************************************
@brief hci2ile_Command_Dispatch_Req
This function parses the incoming HCI packet and calls the respective APIs along with
required parameters
It also calls the hci2ile_command_complete_event_send to send respective command complete events
***********************************************************************/

void hci2ile_command_dispatch_req(UINT16 opcode, UINT8 len, UINT8 * hcidata)
{
	UINT8 ret;
	UINT16 op_code = opcode;
	trans_id_t trans_id;
	UINT8 api_id = hcidata[0];
	BOOLEAN status = TRUE;	   // hci2ile_command_checker(api_id,len);
	UINT8 *payl = &(hcidata[1]);
	if(status == TRUE)
		{
			switch(api_id)
				{
					case HCI2ILE_SET_ADVERTISEMENT_DATA:
						{
							UINT8 length, type;
							UINT8 *data;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(length, payl);
							STREAM_TO_UINT8(type, payl);
							data = payl;
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret= iLE_set_advertisement_data(trans_id, length, type, data);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SET_ADVERTISEMENT_DATA,ret);
							break;
						}
					case HCI2ILE_REMOVE_ADVERTISEMENT_DATA:
						{
							UINT8 length,type;
							UINT8 *data;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(length,payl);
							STREAM_TO_UINT8(type,payl);
							data = payl;
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret= iLE_remove_advertisment_data(trans_id, length, type, data);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_REMOVE_ADVERTISEMENT_DATA,ret);
							break;
						}
					case HCI2ILE_SET_SCAN_RESPONSE_DATA:
						{
							UINT8 length, type;
							UINT8 *data;
							// UINT8 app_handle;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(length, payl);
							STREAM_TO_UINT8(type, payl);
							data = payl;
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret= iLE_set_scan_response_data(trans_id, length, type, data);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SET_SCAN_RESPONSE_DATA,ret);
							break;
						}
					case HCI2ILE_REMOVE_SCAN_RESPONSE_DATA:
						{
							UINT8 length,type;
							UINT8 *data;
							// UINT8 app_handle;
							STREAM_TO_TRANS_ID(trans_id,payl);
							STREAM_TO_UINT8(length,payl);
							STREAM_TO_UINT8(type,payl);
							data = payl;
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret= iLE_remove_scan_response_data(trans_id, length, type, data);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_REMOVE_SCAN_RESPONSE_DATA,ret);
							break;
						}
					case HCI2ILE_START_DISCOVERABLE:
						{
							UINT32 timeout_msec;
							UINT8 type,flags;
							UINT8 * bd_addr;
							UINT8 addr_type;
							BOOLEAN use_whitelist, background;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT32(timeout_msec,payl);
							STREAM_TO_UINT8(type,payl);
							STREAM_TO_UINT8(flags,payl);
							bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(addr_type, payl);
							STREAM_TO_UINT8(use_whitelist,payl);
							STREAM_TO_UINT8(background,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret= iLE_start_discoverable(trans_id, timeout_msec, type, flags, bd_addr,addr_type, use_whitelist, background);
							hci2ile_command_complete_event_send(trans_id, op_code ,HCI2ILE_START_DISCOVERABLE,ret);
							break;
						}
					case HCI2ILE_START_DISCOVERABLE_EX:
						{
							// UINT8 app_handle;
							UINT32 timeout_msec;
							UINT8 type,flags;
							UINT8 * bd_addr;
							UINT8 addr_type;
							UINT16 adv_int_min, adv_int_max;
							BOOLEAN use_whitelist;
							STREAM_TO_TRANS_ID(trans_id,payl);
							STREAM_TO_UINT32(timeout_msec,payl);
							STREAM_TO_UINT8(type,payl);
							STREAM_TO_UINT8(flags,payl);
							bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(addr_type, payl);
							STREAM_TO_UINT16(adv_int_min, payl);
							STREAM_TO_UINT16(adv_int_max, payl);
							STREAM_TO_UINT8(use_whitelist,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret= iLE_start_discoverable_ex(trans_id, timeout_msec, type, flags, bd_addr,addr_type, adv_int_min, adv_int_max, use_whitelist);
							hci2ile_command_complete_event_send(trans_id, op_code ,HCI2ILE_START_DISCOVERABLE_EX,ret);
							break;
						}
					case HCI2ILE_STOP_DISCOVERABLE:
						{
							STREAM_TO_TRANS_ID(trans_id, payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret= iLE_stop_discoverable(trans_id);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_STOP_DISCOVERABLE,ret);
							break;
						}
					case HCI2ILE_SET_LOCAL_DEVICE_NAME:
						{
							UINT8* name;
							UINT8 len;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(len,payl);
							name = payl;
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret= iLE_set_local_device_name(trans_id, len, name);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SET_LOCAL_DEVICE_NAME,ret);
							break;
						}
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
					case HCI2ILE_START_SCAN:
						{
							UINT32 timeout_msec;
							BOOLEAN active;
							BOOLEAN limited;
							BOOLEAN use_whitelist;
							BOOLEAN background;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT32(timeout_msec, payl);
							STREAM_TO_UINT8(active, payl);
							STREAM_TO_UINT8(limited, payl);
							STREAM_TO_UINT8(use_whitelist, payl);
							STREAM_TO_UINT8(background, payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret= iLE_start_scan(trans_id, timeout_msec, active, limited, use_whitelist, background);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_START_SCAN,ret);
							break;
						}
					case HCI2ILE_START_SCAN_EX:
						{
							UINT32 timeout_msec;
							// UINT8 app_handle;
							BOOLEAN active;
							BOOLEAN limited;
							BOOLEAN use_whitelist;
							UINT16 scan_int, scan_win;
							STREAM_TO_TRANS_ID(trans_id,payl);
							STREAM_TO_UINT32(timeout_msec,payl);
							STREAM_TO_UINT8(active,payl);
							STREAM_TO_UINT8(limited,payl);
							STREAM_TO_UINT8(use_whitelist,payl);
							STREAM_TO_UINT16(scan_int, payl);
							STREAM_TO_UINT16(scan_win, payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret= iLE_start_scan_ex(trans_id, timeout_msec, active, limited, use_whitelist, scan_int, scan_win);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_START_SCAN_EX,ret);
							break;
						}
					case HCI2ILE_STOP_SCAN:
						{
							STREAM_TO_TRANS_ID(trans_id, payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_stop_scan(trans_id);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_STOP_SCAN,ret);
							break;
						}
					case HCI2ILE_CONNECT:
						{
							UINT8* remote_bd_addr;
							UINT8 addr_type;
							BOOLEAN auto_reconnect;
							STREAM_TO_TRANS_ID(trans_id, payl);
							remote_bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(addr_type,payl);
							STREAM_TO_UINT8(auto_reconnect,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_connect(trans_id, remote_bd_addr,addr_type);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_CONNECT,ret);
							break;
						}
					case HCI2ILE_CONNECT_EX:
						{
							UINT8* remote_bd_addr;
							UINT8 addr_type;
							// UINT8 app_handle;
							BOOLEAN auto_reconnect;
							UINT16 scan_int, scan_win, conn_int_min, conn_int_max, conn_lat, sup_timeout;
							STREAM_TO_TRANS_ID(trans_id,payl);
							remote_bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(addr_type,payl);
							STREAM_TO_UINT16(scan_int, payl);
							STREAM_TO_UINT16(scan_win, payl);
							STREAM_TO_UINT16(conn_int_min, payl);
							STREAM_TO_UINT16(conn_int_max, payl);
							STREAM_TO_UINT16(conn_lat, payl);
							STREAM_TO_UINT16(sup_timeout, payl);
							STREAM_TO_UINT8(auto_reconnect,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_connect_ex(trans_id, remote_bd_addr,addr_type, scan_int, scan_win, conn_int_min, conn_int_max, conn_lat, sup_timeout);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_CONNECT_EX,ret);
							break;
						}
#endif
					case HCI2ILE_DISCONNECT:
						{
							UINT8 conn_id;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_disconnect(trans_id , conn_id);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_DISCONNECT,ret);
							break;
						}

					case HCI2ILE_ADD_TO_WHITELIST:
						{
							UINT8 addr_type;
							UINT8 *bdaddr;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(addr_type,payl);
							bdaddr = payl;
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_add_to_whitelist(trans_id, addr_type, bdaddr);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_ADD_TO_WHITELIST,ret);
							break;
						}

					case HCI2ILE_REMOVE_FROM_WHITELIST:
						{
							UINT8 addr_type;
							UINT8 *bdaddr;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(addr_type,payl);
							bdaddr = payl;
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_remove_from_whitelist(trans_id, addr_type, bdaddr);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_REMOVE_FROM_WHITELIST,ret);
							break;
						}

					case HCI2ILE_CLEAR_WHITELIST:
						{
							STREAM_TO_TRANS_ID(trans_id, payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_clear_whitelist(trans_id);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_CLEAR_WHITELIST,ret);
							break;
						}
					case HCI2ILE_CREATE_BOND:
						{
							UINT8 addr_type;
							UINT8 auth_level;
							UINT8 key_size_min;
							UINT8 key_size_max;
							UINT8 io_cap;
							UINT8 * remote_bd_addr;
							UINT8 oob_flag;
							STREAM_TO_TRANS_ID(trans_id, payl);
							remote_bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(addr_type,payl);
							STREAM_TO_UINT8(auth_level,payl);
							STREAM_TO_UINT8(key_size_min,payl);
							STREAM_TO_UINT8(key_size_max,payl);
							STREAM_TO_UINT8(io_cap,payl);
							STREAM_TO_UINT8(oob_flag,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_create_bond(trans_id, remote_bd_addr,addr_type, auth_level, key_size_min);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_CREATE_BOND,ret);
							break;
						}
					case HCI2ILE_CREATE_BOND_EX:
						{
							// UINT8 app_handle;
							UINT8 addr_type;
							UINT8 auth_level;
							UINT8 key_size_min;
							UINT8 key_size_max;
							UINT8 io_cap;
							UINT8 * remote_bd_addr;
							UINT8 oob_flag;
							UINT16 scan_int, scan_win, conn_int_min, conn_int_max, conn_lat, sup_timeout;
							STREAM_TO_TRANS_ID(trans_id,payl);
							remote_bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(addr_type,payl);
							STREAM_TO_UINT16(scan_int, payl);
							STREAM_TO_UINT16(scan_win, payl);
							STREAM_TO_UINT16(conn_int_min, payl);
							STREAM_TO_UINT16(conn_int_max, payl);
							STREAM_TO_UINT16(conn_lat, payl);
							STREAM_TO_UINT16(sup_timeout, payl);
							STREAM_TO_UINT8(auth_level,payl);
							STREAM_TO_UINT8(key_size_min,payl);
							STREAM_TO_UINT8(key_size_max,payl);
							STREAM_TO_UINT8(io_cap,payl);
							STREAM_TO_UINT8(oob_flag,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_create_bond_ex(trans_id, remote_bd_addr,addr_type, scan_int, scan_win, conn_int_min, conn_int_max,
													 conn_lat, sup_timeout, auth_level, key_size_min);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_CREATE_BOND_EX,ret);
							break;
						}
					case HCI2ILE_REMOVE_BOND:
						{
							UINT8 *remote_bd_addr;
							UINT8 addr_type;
							STREAM_TO_TRANS_ID(trans_id,payl);
							remote_bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(addr_type,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_remove_bond(trans_id, remote_bd_addr, addr_type);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_REMOVE_BOND,ret);
							break;
						}
					case HCI2ILE_SET_DATA_LEN:
						{
							UINT8 conn_id, tx_octets;
							STREAM_TO_TRANS_ID(trans_id,payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT8(tx_octets,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_set_data_len(trans_id, conn_id, tx_octets);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SET_DATA_LEN,ret);
							break;
						}
					case HCI2ILE_SMP_REGISTER:
						{
							STREAM_TO_TRANS_ID(trans_id, payl);
							ret = STATUS_ERR_INSUFFICIENT_RESOURCES;			
							if (!smp_trans_id)
							{
								add_appid_to_trans_id(&trans_id, adapt_app_handle);
								smp_trans_id = trans_id;
								ret = iLE_smp_register(trans_id, HAL_smp_cb);
 
							}
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SMP_REGISTER,ret);
							break;
						}
					case HCI2ILE_SET_IO_CAPABILITIES:
						{
							UINT8 io_cap;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(io_cap, payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_smp_set_io_capabilities(trans_id,io_cap);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SET_IO_CAPABILITIES,ret);
							break;
						}
					case HCI2ILE_SEND_PASSKEY:
						{
							UINT8 * remote_bd_addr;
							UINT8 bdaddr_type;
							UINT32 passkey;
							STREAM_TO_TRANS_ID(trans_id, payl);
							remote_bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(bdaddr_type,payl);
							STREAM_TO_UINT32(passkey,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_send_passkey(trans_id, remote_bd_addr, bdaddr_type, passkey);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SEND_PASSKEY,ret);
							break;
						}
					case HCI2ILE_SEND_AUTHORIZATION:
						{
							UINT8 * remote_bd_addr;
							UINT8 bdaddr_type;
							UINT8 authorization, auth_req, key_size_min, key_size_max, io_cap, oob_flag;
							STREAM_TO_TRANS_ID(trans_id, payl);
							remote_bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(bdaddr_type,payl);
							STREAM_TO_UINT8(authorization,payl);
							STREAM_TO_UINT8(auth_req,payl);
							STREAM_TO_UINT8(key_size_min,payl);
							STREAM_TO_UINT8(key_size_max, payl);
							STREAM_TO_UINT8(io_cap,payl);
							STREAM_TO_UINT8(oob_flag,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_send_authorization(trans_id, remote_bd_addr, bdaddr_type, authorization,
														auth_req, key_size_min);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SEND_AUTHORIZATION,ret);
							break;
						}
#if (SECURE_CONNECTION)
					case HCI2ILE_SMP_SEND_NC_RESULT:
						{
							UINT8 * remote_bd_addr;
							UINT8 bdaddr_type;
							UINT8 authorization;
							STREAM_TO_TRANS_ID(trans_id, payl);
							remote_bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(bdaddr_type,payl);
							STREAM_TO_UINT8(authorization,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_smp_send_nc_result(trans_id, remote_bd_addr, bdaddr_type, authorization);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SMP_SEND_NC_RESULT,ret);
							break;
						}
#endif /* SECURE_CONNECTION */
					case HCI2ILE_GET_ATTRIBUTE_MTU:
						{
							UINT8 conn_id;
							UINT16 mtu_size;
							UINT8 mtu_stream[sizeof(mtu_size)];
							UINT8 *p = mtu_stream;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id, payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							mtu_size = iLE_get_att_mtu(trans_id, conn_id);
							UINT16_TO_STREAM(p, mtu_size);
							hci2ile_command_complete_event_send_ext(trans_id, op_code, HCI2ILE_GET_ATTRIBUTE_MTU, STATUS_SUCCESS,\
																	(UINT8)sizeof(mtu_stream), (UINT8*)mtu_stream);
							break;
						}
					case HCI2ILE_SET_ATTRIBUTE_MTU:
						{
							UINT8 conn_id;
							UINT16 mtu_size;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT16(mtu_size,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_set_att_mtu( trans_id, conn_id, mtu_size);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SET_ATTRIBUTE_MTU, ret);
							break;
						}
					case HCI2ILE_UPDATE_CONN_PARAMS:
						{
							UINT8 conn_id;
							UINT16 interval_min;
							UINT16 interval_max;
							UINT16 conn_latency;
							UINT16 sup_timeout;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT16(interval_min,payl);
							STREAM_TO_UINT16(interval_max,payl);
							STREAM_TO_UINT16(conn_latency,payl);
							STREAM_TO_UINT16(sup_timeout,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_update_conn_params(trans_id,conn_id, interval_min, interval_max, conn_latency, sup_timeout);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_UPDATE_CONN_PARAMS, ret);
							break;

						}
#if (L2CAP_COC == TRUE)

					case HCI2ILE_L2CAP_COC_REGISTER:
						{
							UINT16 psm;
							UINT16 mtu;
							BOOLEAN auth_req;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT16(psm,payl);
							STREAM_TO_UINT16(mtu,payl);
							STREAM_TO_UINT8(auth_req,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_l2cap_coc_register(trans_id,psm,mtu,&l2cap_coc_cbs,auth_req);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_L2CAP_COC_REGISTER, ret);
							break;
						}
					case HCI2ILE_L2CAP_COC_CONNECT_REQ:
						{
							UINT8 conn_id;
							UINT16 psm;
							UINT16 mtu;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT16(psm,payl);
							STREAM_TO_UINT16(mtu,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_l2cap_coc_connect_req(trans_id,conn_id,psm,mtu,&l2cap_coc_cbs);
							hci2ile_command_complete_event_send(trans_id, op_code,HCI2ILE_L2CAP_COC_CONNECT_REQ,ret);
							break;
						}

					case HCI2ILE_L2CAP_COC_DISCONNECT_REQ:
						{
							UINT8 conn_id;
							UINT8 coc_handle;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT8(coc_handle,payl);
							ret = iLE_l2cap_coc_disconnect_req(trans_id,conn_id,coc_handle);
							hci2ile_command_complete_event_send(trans_id, op_code,HCI2ILE_L2CAP_COC_DISCONNECT_REQ,ret);
							break;
						}
					case HCI2ILE_L2CAP_COC_SEND_DATA:
						{
							UINT8 conn_id;
							UINT8 coc_handle;
							UINT16 buffer_len;
							UINT8 * buffer;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT8(coc_handle,payl);
							STREAM_TO_UINT16(buffer_len, payl);
							buffer = payl;
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_l2cap_coc_send_data(trans_id,conn_id,coc_handle,buffer,buffer_len);
							hci2ile_command_complete_event_send(trans_id, op_code,HCI2ILE_L2CAP_COC_SEND_DATA,ret);
							break;
						}

#endif
#if (TEST_CODE == TRUE)
					case HCI2ILE_TEST_READ_AUTHENTICATED_PAYLOAD_TOUT:
						{
							UINT8 conn_id;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_test_read_authenticated_payload_timeout(trans_id,conn_id);
							hci2ile_command_complete_event_send(trans_id, op_code,HCI2ILE_TEST_READ_AUTHENTICATED_PAYLOAD_TOUT,ret);
							break;
						}

					case HCI2ILE_TEST_WRITE_AUTHENTICATED_PAYLOAD_TOUT:
						{
							UINT8 conn_id;
							UINT16 timeout;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT16(timeout,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_test_write_authenticated_payload_timeout(trans_id,conn_id,timeout);
							hci2ile_command_complete_event_send(trans_id, op_code,HCI2ILE_TEST_WRITE_AUTHENTICATED_PAYLOAD_TOUT,ret);
							break;
						}

					case HCI2ILE_TEST_ENABLE_PRIVACY:
						{
							UINT8 enable_privacy;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(enable_privacy,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_test_enable_privacy(trans_id, enable_privacy);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_TEST_ENABLE_PRIVACY, ret);
							break;
						}
					case HCI2ILE_GET_BDADDR:
						{
							UINT8 addr_type;
							UINT8 bdaddr[BD_ADDR_LEN];
							UINT8 bdaddr_stream[BD_ADDR_LEN + 1];
							UINT8 *p = bdaddr_stream;
							STREAM_TO_TRANS_ID(trans_id, payl);
						    add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_get_bdaddr(trans_id, &addr_type, bdaddr);
							ARRAY_TO_STREAM(p,bdaddr,HCI2ILE_SIZE_OF_BD_ADDR);
							UINT8_TO_STREAM(p,addr_type);
							hci2ile_command_complete_event_send_ext(trans_id, op_code, HCI2ILE_GET_BDADDR, ret, \
																(UINT8)sizeof(bdaddr_stream), (UINT8*)bdaddr_stream);
							break;
						}
					case HCI2ILE_TEST_SET_BD_ADDRESS:
						{
							UINT8 bd_addr[BD_ADDR_LEN];
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_ARRAY(bd_addr,payl,BD_ADDR_LEN);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_test_set_public_bdaddr(trans_id, bd_addr);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_TEST_SET_BD_ADDRESS, ret);
							break;
						}

#endif // (TEST_CODE == TRUE)
					case HCI2ILE_ADD_SERICE:
						{
							UINT8 service_type;
							UINT8 number_of_inc_services;
							UINT8 number_of_char;
							UINT8 number_of_desc;
							uuid_t uuid;
							STREAM_TO_TRANS_ID(trans_id, payl);
							//STREAM_TO_UINT8(uuid.length,payl);
							//uuid = get_uuid_from_stream(payl,uuid.length);
							JUMP_CUSTOM_LEN(payl, get_uuid_from_stream2(payl, &uuid));
							STREAM_TO_UINT8(service_type,payl);
							STREAM_TO_UINT8(number_of_inc_services,payl);
							STREAM_TO_UINT8(number_of_char,payl);
							STREAM_TO_UINT8(number_of_desc,payl);
							//logd("service_type = %u", service_type);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_add_service(trans_id, &uuid, service_type, number_of_inc_services, number_of_char, number_of_desc);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_ADD_SERICE, ret);
							break;
						}
					case HCI2ILE_ADD_INCLUDED_SERVICE:
						{
							UINT8 service_type;
							UINT16 start_handle;
							UINT16 end_handle;
							uuid_t uuid;
							STREAM_TO_TRANS_ID(trans_id,payl);
							JUMP_CUSTOM_LEN(payl, get_uuid_from_stream2(payl, &uuid));
							STREAM_TO_UINT8(service_type,payl);
							STREAM_TO_UINT16(start_handle,payl);
							STREAM_TO_UINT16(end_handle,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_add_included_service(trans_id, &uuid, service_type, start_handle, end_handle);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_ADD_INCLUDED_SERVICE, ret);
							break;
						}
					case HCI2ILE_ADD_CHARACTERISTIC:
						{
							uuid_t uuid;
							UINT8 property;
							UINT16 permission;
							STREAM_TO_TRANS_ID(trans_id, payl);
							//STREAM_TO_UINT8(uuid.length,payl);
							//uuid = get_uuid_from_stream(payl,uuid.length);
							JUMP_CUSTOM_LEN(payl, get_uuid_from_stream2(payl, &uuid));
							STREAM_TO_UINT8(property,payl);
							STREAM_TO_UINT16(permission,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_add_characteristic(trans_id, &uuid, property, permission);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_ADD_CHARACTERISTIC, ret);
							break;
						}

					case HCI2ILE_ADD_DESCRIPTOR:
						{
							uuid_t uuid;
							UINT8 property;
							UINT16 permission;
							STREAM_TO_TRANS_ID(trans_id, payl);
							//STREAM_TO_UINT8(uuid.length,payl);
							//uuid = get_uuid_from_stream(payl,uuid.length);
							JUMP_CUSTOM_LEN(payl, get_uuid_from_stream2(payl, &uuid));
							STREAM_TO_UINT8(property,payl); /* TODO: This command parameter will be removed */
							STREAM_TO_UINT16(permission,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_add_descriptor(trans_id, &uuid, property, permission);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_ADD_DESCRIPTOR, ret);
							break;
						}

					case HCI2ILE_START_SERVICE:
						{
							STREAM_TO_TRANS_ID(trans_id, payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_start_service(trans_id);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_START_SERVICE, ret);
							break;
						}
					case HCI2ILE_REMOVE_SERVICE:
						{
							UINT16 service_handle;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT16(service_handle,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_remove_service( trans_id, service_handle);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_REMOVE_SERVICE, ret);
							break;
						}

					case HCI2ILE_SEND_ATTRIBUTE_READ_RSP:
						{
							UINT8 conn_id;
							UINT8 att_opcode;
							UINT16 att_id;
							UINT8 status;
							buffer_t * buffer;
							UINT16 buffer_len;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT8(att_opcode,payl);
							STREAM_TO_UINT16(att_id,payl);
							STREAM_TO_UINT8(status,payl);
							STREAM_TO_UINT16(buffer_len,payl);

							if (buffer_len) {
								buffer_len = TRUNCATE_TO_16BIT_LENGTH(buffer_len, sizeof(buffer_t));
								buffer = (buffer_t *)app_alloc((sizeof(buffer_t) + buffer_len));
								buffer->length = buffer_len;
								STREAM_TO_UINT16(buffer->offset,payl);
								memcpy (buffer->data, payl, buffer->length);
							}else{
								buffer = NULL;
							}
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_send_attribute_read_rsp( trans_id, conn_id, att_opcode, att_id, status, buffer);
							app_dealloc(buffer);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SEND_ATTRIBUTE_READ_RSP, ret);
							break;
						}

					case HCI2ILE_SEND_ATTRIBUTE_WRITE_RSP:
						{
							UINT8 conn_id;
							UINT8 att_opcode;
							UINT16 att_id;
							UINT8 status;
							UINT16 offset;
							buffer_t * buffer;
							UINT16 buffer_len;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT8(att_opcode,payl);
							STREAM_TO_UINT16(att_id,payl);
							STREAM_TO_UINT16(offset,payl);
							STREAM_TO_UINT8(status,payl);
							STREAM_TO_UINT16(buffer_len,payl);

							if (buffer_len) {
								buffer_len = TRUNCATE_TO_16BIT_LENGTH(buffer_len, sizeof(buffer_t));
								buffer = (buffer_t *)app_alloc((sizeof(buffer_t) + buffer_len));
								buffer->length = buffer_len;
								STREAM_TO_UINT16(buffer->offset,payl);
								memcpy (buffer->data, payl, buffer->length);
							}else{
								buffer = NULL;
							}
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_send_attribute_write_rsp( trans_id, conn_id, att_opcode, att_id,offset, status, buffer);
							app_dealloc(buffer);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SEND_ATTRIBUTE_WRITE_RSP, ret);
							break;
						}

					case HCI2ILE_SEND_NOTIFICATION:
						{
							buffer_t * buffer;
							UINT16 buffer_len;
							UINT8 conn_id;
							UINT16 att_id;
							BOOLEAN need_response;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT16(att_id,payl);
							STREAM_TO_UINT8(need_response,payl);
							STREAM_TO_UINT16(buffer_len,payl);

							if (buffer_len) {
								buffer_len = TRUNCATE_TO_16BIT_LENGTH(buffer_len, sizeof(buffer_t));
								buffer = (buffer_t *)app_alloc((sizeof(buffer_t) + buffer_len));
								buffer->length = buffer_len;
								STREAM_TO_UINT16(buffer->offset,payl);
								memcpy (buffer->data, payl, buffer->length);
							}else{
								buffer = NULL;
							}
							JUMP_CUSTOM_LEN(payl,buffer->length);

							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_send_notification(trans_id,conn_id, att_id, buffer , need_response);
							app_dealloc(buffer);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SEND_NOTIFICATION, ret);
							break;
						}
#if (GATT_CLIENT_SUPPORTED == TRUE)
					case HCI2ILE_DISCOVER_PRIMARY_SERVICE:
						{
							UINT8 conn_id;
							uuid_t service_uuid;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							//STREAM_TO_UINT8(service_uuid.length,payl);
							//service_uuid = get_uuid_from_stream(payl,service_uuid.length);
							JUMP_CUSTOM_LEN(payl, get_uuid_from_stream2(payl, &service_uuid));
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_discover_primary_service(trans_id, conn_id, &service_uuid);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_DISCOVER_PRIMARY_SERVICE, ret);
							break;
						}
					case HCI2ILE_DISCOVER_INCLUDED_SERVICE:
						{
							UINT8 conn_id;
							UINT16 start_handle;
							UINT16 end_handle;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT16(start_handle,payl);
							STREAM_TO_UINT16(end_handle,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_discover_included_service(trans_id, conn_id, start_handle, end_handle);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_DISCOVER_INCLUDED_SERVICE, ret);
							break;
						}

					case HCI2ILE_DISCOVER_CHARACTERISTIC:
						{
							UINT8 conn_id;
							UINT16 start_handle;
							UINT16 end_handle;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT16(start_handle,payl);
							STREAM_TO_UINT16(end_handle,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_discover_characteristic(trans_id, conn_id, start_handle, end_handle);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_DISCOVER_CHARACTERISTIC, ret);
							break;
						}
					case HCI2ILE_DISCOVER_DESCRIPTOR:
						{
							UINT8 conn_id;
							UINT16 start_handle;
							UINT16 end_handle;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT16(start_handle,payl);
							STREAM_TO_UINT16(end_handle,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_discover_descriptor(trans_id, conn_id, start_handle, end_handle);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_DISCOVER_DESCRIPTOR, ret);
							break;
						}
					case HCI2ILE_READ_ATTRIBUTE_VALUE:
						{
							UINT8 conn_id;
							gatt_attribute_read_param_t read_param;
							memset(&read_param, 0, sizeof(gatt_attribute_read_param_t));
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT8(read_param.att_opcode,payl);
							switch(read_param.att_opcode)
								{
									case ATT_OPCODE_READ_REQ:
										{
											STREAM_TO_UINT16(read_param.attr_read_param.read_attr.att_id, payl);
											break;
										}
									case ATT_OPCODE_READ_BLOB_REQ:
										{
											STREAM_TO_UINT16(read_param.attr_read_param.read_attr.att_id, payl);
											STREAM_TO_UINT16(read_param.attr_read_param.read_attr.offset,payl);
											break;
										}
									case ATT_OPCODE_READ_BY_TYPE_REQ:
										{
											STREAM_TO_UINT16(read_param.attr_read_param.read_using_uuid_param.start_handle, payl);
											STREAM_TO_UINT16(read_param.attr_read_param.read_using_uuid_param.end_handle, payl);
											JUMP_CUSTOM_LEN(payl, get_uuid_from_stream2(payl, &read_param.attr_read_param.read_using_uuid_param.uuid));
											//STREAM_TO_UINT8(read_param.attr_read_param.read_using_uuid_param.uuid.length, payl);
											//STREAM_TO_ARRAY(((UINT8*)(&(read_param.attr_read_param.read_using_uuid_param.uuid.value))),payl, read_param.attr_read_param.read_using_uuid_param.uuid.length);
											break;
										}
									case ATT_OPCODE_READ_MULTI_REQ:
										{
											UINT8 i;
											UINT8 num_of_att = (len - (TRANS_ID_SIZE_BYTES + 2)) / 2;
											if(num_of_att > 12)
											{
												loge("Num of attributes exceeds the limit");
												break;
											}
											for(i=0; i < num_of_att; i++)
												STREAM_TO_UINT16(read_param.attr_read_param.multi_att_id_list[i], payl);
											break;
										}
								}
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_read_attribute_value(trans_id, conn_id, &read_param);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_READ_ATTRIBUTE_VALUE, ret);
							break;
						}
					case HCI2ILE_WRITE_ATTRIBUTE_VALUE:
						{
							UINT8 conn_id;
							UINT8 att_opcode;
							UINT16 att_id;
							UINT16 offset;
							buffer_t * buffer;
							UINT16 buffer_len;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT8(att_opcode,payl);
							STREAM_TO_UINT16(att_id,payl);
							STREAM_TO_UINT16(offset,payl);
							STREAM_TO_UINT16(buffer_len,payl);

							if (buffer_len) {
								buffer_len = TRUNCATE_TO_16BIT_LENGTH(buffer_len, sizeof(buffer_t));
								buffer = (buffer_t *)app_alloc((sizeof(buffer_t) + buffer_len));
								buffer->length = buffer_len;
								STREAM_TO_UINT16(buffer->offset,payl);
								memcpy (buffer->data, payl, buffer->length);
							}else{
								buffer = NULL;
							}
							JUMP_CUSTOM_LEN(payl,buffer->length);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_write_attribute_value(trans_id, conn_id , att_opcode, att_id ,offset, buffer);
							app_dealloc(buffer);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_WRITE_ATTRIBUTE_VALUE, ret);
							break;
						}
					case HCI2ILE_REGISTER_NOTIFICATION:
						{
							UINT8 conn_id;
							UINT16 att_id;
							BOOLEAN is_register;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(conn_id,payl);
							STREAM_TO_UINT16(att_id,payl);
							STREAM_TO_UINT8(is_register,payl);
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_register_notification(trans_id, conn_id, att_id, is_register);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_REGISTER_NOTIFICATION,ret);
							break;
						}
#endif
					case HCI2ILE_SEND_HCI_COMMAND:
						{
							UINT16 opcode;
							UINT8 buffer_len;
							UINT8* command_buffer;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT16(opcode, payl);
							STREAM_TO_UINT8(buffer_len,payl);
							command_buffer = payl;
							add_appid_to_trans_id(&trans_id, adapt_app_handle);
							ret = iLE_send_hci_command(trans_id, opcode, buffer_len,command_buffer);
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SEND_HCI_COMMAND,ret);
							break;
						}
                    case HCI2ILE_TEST_TRIGER_PANIC: 
                       { 
							panic = 1;
							hci2ile_command_complete_event_send(0, op_code, HCI2ILE_TEST_TRIGER_PANIC, 0);

							ASSERT_ERR(0); 
                            break; 
                       } 
					case HCI2ILE_REGISTER_STORAGE:
						{
							UINT8 storage_support;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(storage_support, payl);
							if(storage_support)
							{
								ret = iLE_storage_register(trans_id, &storage_cbs);
							}
							else
							{
								ret = iLE_storage_register(trans_id, NULL);
							}
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_REGISTER_STORAGE,ret);

							break;
						}
					case HCI2ILE_KEY_RESPONSE:
						{
							UINT8 bdaddr_type;
							UINT8* bd_addr;
							UINT8 key_type;
							UINT8 key_length;
							STREAM_TO_TRANS_ID(trans_id, payl);
							STREAM_TO_UINT8(bdaddr_type, payl);
							bd_addr = payl;
							JUMP_BDADDR(payl);
							STREAM_TO_UINT8(key_type, payl);
							STREAM_TO_UINT8(key_length, payl);
							switch(key_type)
							{
#if (PRIVACY_FEATURE == TRUE)
								case LOCAL_IRK:
									{
										if(key_length == 0)
										{
											logd("IRK not found in DB");
											ret = iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, NULL);
										}
										else if(key_length != 16)
										{
											ret = STATUS_ERR_INVALID_PARAM;
										}
										else
										{
											identity_info_t local_irk;
											UINT8 *pp = local_irk.irk;
											STREAM_TO_ARRAY(pp, payl, 16);
											ret = iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, &local_irk);
										}
										break;
									}
								case PEER_IRK:
									{
										if(key_length == 0)
										{
											ret = iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, NULL);
										}
										else if(key_length != 32)
										{
											ret = STATUS_ERR_INVALID_PARAM;
										}
										else
										{
											resolving_list_entry_t peer_irk ;
											UINT8 *pp = peer_irk.peer_id_info.irk;
											memcpy(peer_irk.peer_id_info.id_addr, bd_addr, BD_ADDR_LEN);
											peer_irk.peer_id_info.id_addr_type = bdaddr_type;
											STREAM_TO_ARRAY(pp, payl, 16);
											payl += 16;
											pp = peer_irk.local_irk;
											STREAM_TO_ARRAY(pp, payl, 16);
											ret = iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, &peer_irk);
										}
										break;
									}
#endif /* PRIVACY_FEATURE */
								case SEC_INFO:
									{
										if(key_length == 0)
										{
											ret = iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, NULL);
										}
										else if(key_length != 4)
										{
											ret = STATUS_ERR_INVALID_PARAM;
										}
										else
										{
											sec_info_t security_info;
											STREAM_TO_UINT8(security_info.security_level, payl);
											STREAM_TO_UINT8(security_info.keys_distributed, payl);
											STREAM_TO_UINT8(security_info.key_size, payl);
											STREAM_TO_UINT8(security_info.key_type, payl);
											ret = iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, &security_info);
										}
										break;
									}
								case PEER_LTK:
									{
										if(key_length == 0)
										{
											ret = iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, NULL);
										}
										else if (key_length != 26)
										{
											ret = STATUS_ERR_INVALID_PARAM;
										}
										else
										{
											enc_info_t peer_ltk;
											UINT8 *pp = peer_ltk.ltk;
											STREAM_TO_ARRAY(pp, payl, 16);
											payl += 16;
											pp = peer_ltk.rand;
											STREAM_TO_ARRAY(pp, payl, 8);
											payl += 8;
											STREAM_TO_UINT16(peer_ltk.ediv, payl);
											ret = iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, &peer_ltk);

										}
										break;
									}
								case LOCAL_LTK:
									{
										if(key_length == 0)
										{
											ret =iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, NULL);
										}
										else if (key_length != 26)
										{
											ret = STATUS_ERR_INVALID_PARAM;
										}
										else
										{
											enc_info_t local_ltk;
											UINT8 *pp = local_ltk.ltk;
											STREAM_TO_ARRAY(pp, payl, 16);
											payl += 16;
											pp = local_ltk.rand;
											STREAM_TO_ARRAY(pp, payl, 8);
											payl += 8;
											STREAM_TO_UINT16(local_ltk.ediv, payl);
											ret = iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, &local_ltk);
										}
										break;
									}
								case PEER_CSRK:
									{
										if(key_length == 0)
										{
											ret =iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, NULL);
										}
										else if (key_length != 20)
										{
											ret = STATUS_ERR_INVALID_PARAM;
										}
										else
										{
											signing_info_t peer_csrk;
											UINT8 *pp = peer_csrk.csrk;
											STREAM_TO_ARRAY(pp, payl, 16);
											payl += 16;
											STREAM_TO_UINT32(peer_csrk.counter, payl);
											ret =iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, &peer_csrk);
										}
										break;
									}
								case LOCAL_CSRK:
									{
										if(key_length == 0)
										{
											ret =iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, NULL);
										}
										else if (key_length != 20)
										{
											ret = STATUS_ERR_INVALID_PARAM;
										}
										else
										{
											signing_info_t local_csrk;
											UINT8 *pp = local_csrk.csrk;
											STREAM_TO_ARRAY(pp, payl, 16);
											payl += 16;
											STREAM_TO_UINT32(local_csrk.counter, payl);											
											ret =iLE_key_response(trans_id, bd_addr, bdaddr_type, key_type, &local_csrk);
										}
										break;
									}
								default:
									{
										logd("Unknown key_type %d", key_type);
										ret = STATUS_ERR_INVALID_PARAM;
										break;
									}
							}
							hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_KEY_RESPONSE, ret);
							break;
						}
#if (TEST_CODE == TRUE)
	/* Needed for VSC HCI passthrough*/	
					case HCI2ILE_SEND_VSHCI_COMMAND:
					{	
						UINT8 buffer_len = len - 3;
						UINT8* command_buffer;
						STREAM_TO_TRANS_ID(trans_id, payl);
						command_buffer = payl;
						add_appid_to_trans_id(&trans_id, adapt_app_handle);
						ret = iLE_send_vshci_command(trans_id, buffer_len, command_buffer);
						hci2ile_command_complete_event_send(trans_id, op_code, HCI2ILE_SEND_VSHCI_COMMAND, ret);
						break;
					}
#endif /*TEST_CODE == TRUE*/
               		default: 
                       { /* Should never hit this */ 
                           ASSERT_ERR(0); 
                       } 

				}
		}
}

/*******************************************
Callback Functions and callback event packaging
*******************************************/
void HAL_register_application_cb(UINT8 app_handle, BOOLEAN result)
	{
		panic = 0;
        logd("");
    	UINT8 * cb_buffer;
    	UINT8 length;
   		UINT8* p_buf; UINT8* p;
        if (result == TRUE)
        {
        /* First send command complete for ile stack enable command*/
#if(TARGET_THREADX_RW == TRUE)
			p_buf = app_alloc(14);
			if(!p_buf)
			{
				return;
			}
		
			p = p_buf + sizeof(uint32_t);
			*p++ = HCI_EVT_MSG_TYPE;
		
			//pack event code
			*p++ = (uint8_t)HCI_CMD_CMPL_EVT_CODE;
		
			//pack command complete event parameter length
			*p++ = 4;
		
			//pack the number of h2c packets
			*p++ = 1;
		
			//pack opcode
			UINT16_TO_STREAM(p,0xFC85);
		
			//pack status
			*p++ = 0;

			//Post to transport thread
	tx_queue_send(&st_to_tr_msg_queue, &p_buf, TX_NO_WAIT);
	tx_event_flags_set(&tr_evnt_flags, OS_EVNT_FLG_HCI_EVNT, TX_OR);
#endif
		
            logd("app_handle:%d", app_handle);
            adapt_app_handle = app_handle;
        /* Request for storage registration */
            p_buf = app_alloc(HCI2ILE_LENGTH_STORAGE_REG_REQUEST_CB);
    		if(!p_buf)
    		{
    			return;
    		}
    		cb_buffer = (p_buf + DBG_EVT_HEADER);
    		p = cb_buffer;
    		UINT8_TO_STREAM(p, HCI2ILE_CB_ID_ON_STORAGE_REGISTER_REQ_CB);
    		length = p - cb_buffer;
    		hci2ile_callback_send(INVALID_TRANS_ID, length, p_buf);
        }
	}


void HAL_on_connected_cb(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 result, BOOLEAN from_remote,
						 UINT8 *id_bdaddr, UINT8 id_bdaddr_type)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_CONNECT_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER);
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_CONNECTED);
		UINT8_TO_STREAM(p,result);
		ARRAY_TO_STREAM(p,remote_bd_addr,HCI2ILE_SIZE_OF_BD_ADDR);
		UINT8_TO_STREAM(p,bdaddr_type);
		UINT8_TO_STREAM(p,conn_id);
		if (from_remote)
		{
			UINT8_TO_STREAM(p,CONNECTED_AS_SERVER);
		}
		else
		{
			UINT8_TO_STREAM(p,CONNECTED_AS_CLIENT);
		}
		ARRAY_TO_STREAM(p, id_bdaddr, HCI2ILE_SIZE_OF_BD_ADDR);
		UINT8_TO_STREAM(p,id_bdaddr_type);
		length = p - cb_buffer;
		hci2ile_callback_send(trans_id, length, p_buf);
	}

void HAL_on_disconnected_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 result)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_DISCONNECT_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER);
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_DISCONNECTED);
		UINT8_TO_STREAM(p, result);
		UINT8_TO_STREAM(p, conn_id);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length, p_buf);
	}

void HAL_on_conn_param_update(trans_id_t trans_id, UINT8 status, UINT8 conn_id,
								UINT16 interval, UINT16 latency, UINT16 timeout)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_ON_CONN_PARAM_CHANGED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER);
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_CONN_PARAM_CHANGED_CB);
		UINT8_TO_STREAM(p, status);
		UINT8_TO_STREAM(p, conn_id);
		UINT16_TO_STREAM(p, interval);
		UINT16_TO_STREAM(p, latency);
		UINT16_TO_STREAM(p, timeout);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length, p_buf);

	}
	
void HAL_app_scan_result_cb(trans_id_t trans_id, discovered_device_t * device)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_SCAN_RESULT_CB + device->adv_data_len);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER);
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_SCAN_RESULTS_CB);
		UINT8_TO_STREAM(p,device->addr_type);
		ARRAY_TO_STREAM(p, device->bdaddr,HCI2ILE_SIZE_OF_BD_ADDR);
		ARRAY_TO_STREAM(p, device->localname, HCI2ILE_SIZE_OF_LOCAL_NAME);
		#if(GAP_EXTRA_REMOTE_DATA == TRUE)
		UINT8_TO_STREAM(p,device->rssi);
		UINT8_TO_STREAM(p,device->tx_power);
		UINT16_TO_STREAM(p,device->appearance);
		UINT8_TO_STREAM(p,device->role_supported);
		#else
		UINT8_TO_STREAM(p,0);
		UINT8_TO_STREAM(p,0);
		UINT16_TO_STREAM(p,0);
		UINT8_TO_STREAM(p,0);
		#endif
		UINT8_TO_STREAM(p,device->flags);
		UINT8_TO_STREAM(p,device->event_type);
		UINT8_TO_STREAM(p,device->adv_data_len);
		ARRAY_TO_STREAM(p,device->adv_data, device->adv_data_len);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length, p_buf);
	}

void HAL_app_scan_completed_cb(trans_id_t trans_id)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		UINT8 scan_completed = 0x01;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_SCAN_COMPLETED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_SCAN_COMPLETED_CB);
		UINT8_TO_STREAM(p,scan_completed);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length, p_buf);
	}

void HAL_smp_cb (trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 event, UINT8 length, UINT8 *data)
	{
		UINT8 * cb_buffer;
		UINT8 length_cb;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(length && data)
			p_buf = app_alloc(HCI2ILE_LENGTH_SMP_CB + length);
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_SMP_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_SMP_CB);
		ARRAY_TO_STREAM(p, bdaddr,HCI2ILE_SIZE_OF_BD_ADDR);
		UINT8_TO_STREAM(p,bdaddr_type);
		UINT8_TO_STREAM(p,event);
		UINT8_TO_STREAM(p,length);
		if(length && data)
			ARRAY_TO_STREAM(p, data, length);
		length_cb = p-cb_buffer;
		hci2ile_callback_send(trans_id, length_cb, p_buf);
	}

void HAL_app_on_primary_service_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(uuid)
			p_buf = app_alloc(HCI2ILE_LENGTH_PRIMARY_SERVICE_DIS_CB + uuid->length);
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_PRIMARY_SERVICE_DIS_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_PRIMARY_SERVICE_DISCOVERED);
		UINT8_TO_STREAM(p,status);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p,start_handle);
		UINT16_TO_STREAM(p,end_handle);
		UINT8_TO_STREAM(p,(UINT8)is_finished);
		if (uuid != NULL)
		{
			UINT8_TO_STREAM(p,uuid->length);
			UUID_TO_STREAM(p,uuid);
		}
		else //no more primary services left: Sending a dummy UUID of size 0 to indicate that
		{
			UINT8_TO_STREAM(p,0);
		}
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length, p_buf);
	}

void HAL_app_on_included_service_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 inc_handle, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(uuid)
			p_buf = app_alloc(HCI2ILE_LENGTH_INCLUDED_SERVICE_DIS_CB + uuid->length);
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_INCLUDED_SERVICE_DIS_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_INCLUDED_SERVICE_DISCOVERED);
		UINT8_TO_STREAM(p,status);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p, inc_handle);
		UINT16_TO_STREAM(p,start_handle);
		UINT16_TO_STREAM(p,end_handle);
		UINT8_TO_STREAM(p,(UINT8)is_finished);
		if (uuid != NULL)
		{
			UINT8_TO_STREAM(p,uuid->length);
			UUID_TO_STREAM(p,uuid);
		}
		else //no more primary services left: Sending a dummy UUID of size 0 to indicate that
		{
			UINT8_TO_STREAM(p,0);
		}
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length, p_buf);

	}

void HAL_app_on_characteristic_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT8 property, UINT16 att_handle, UINT16 value_handle, uuid_t *uuid, BOOLEAN is_finished)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(uuid)
			p_buf = app_alloc(HCI2ILE_LENGTH_CHAR_DISCOVERY_CB + uuid->length);
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_CHAR_DISCOVERY_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_CHARACTERISTIC_DISCOVERED);
		UINT8_TO_STREAM(p,status);
		UINT8_TO_STREAM(p,conn_id);
		UINT8_TO_STREAM(p, property);
		UINT16_TO_STREAM(p,att_handle);
		UINT16_TO_STREAM(p,value_handle);
		UINT8_TO_STREAM(p,is_finished);
		if (uuid != NULL)
		{
			UINT8_TO_STREAM(p,uuid->length);
			UUID_TO_STREAM(p,uuid);
		}
		else //no more primary services left: Sending a dummy UUID of size 0 to indicate that
		{
			UINT8_TO_STREAM(p,0);
		}
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length, p_buf);
	}

void HAL_app_on_descriptor_discovered_cb(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 att_handle,uuid_t *uuid, BOOLEAN is_finished)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(uuid)
			p_buf = app_alloc(HCI2ILE_LENGTH_DESC_DISCOVERY_CB + uuid->length);
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_DESC_DISCOVERY_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_DESCRIPTOR_DISCOVERED);
		UINT8_TO_STREAM(p,status);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p,att_handle);
		UINT8_TO_STREAM(p,is_finished);
		if (uuid != NULL)
		{
			UINT8_TO_STREAM(p,uuid->length);
			UUID_TO_STREAM(p,uuid);
		}
		else //no more primary services left: Sending a dummy UUID of size 0 to indicate that
		{
			UINT8_TO_STREAM(p,0);
		}
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length, p_buf);
	}

void HAL_app_on_attribute_write_req_cb(trans_id_t trans_id, UINT8 conn_id,UINT8 att_opcode,UINT16 att_id, UINT16 offset, buffer_t * buffer)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(buffer)
		{
			buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, HCI2ILE_LENGTH_ATTRIBUTE_WRITE_REQ_CB + sizeof(UINT16) + sizeof(UINT16));
			p_buf = app_alloc(HCI2ILE_LENGTH_ATTRIBUTE_WRITE_REQ_CB + HCI2ILE_SIZE_OF_BUFFER(buffer->length));
		}
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_ATTRIBUTE_WRITE_REQ_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_ATTRIBUTE_WRITE_REQ);
		UINT8_TO_STREAM(p,conn_id);
		UINT8_TO_STREAM(p,att_opcode);
		UINT16_TO_STREAM(p,att_id);
		UINT16_TO_STREAM(p,offset);

		if(buffer)
		{
			UINT16_TO_STREAM(p,buffer->length);
			UINT16_TO_STREAM(p,0); // Offset would always be 0 since we are copying data from the offset into new buffer_t
			memcpy (p, buffer->data+buffer->offset, buffer->length);

			length = (p - cb_buffer) + buffer->length; // Pointer difference should be the length of encoded params, excluding buffer data
		}
		else
			length = (p - cb_buffer); // Pointer difference should be the length of encoded params

		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_app_on_attribute_read_req_cb(trans_id_t trans_id, UINT8 conn_id,UINT8 att_opcode,UINT16 att_id,UINT16 offset)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_ATTRIBUTE_READ_REQ_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_ATTRIBUTE_READ_REQ);
		UINT8_TO_STREAM(p,conn_id);
		UINT8_TO_STREAM(p,att_opcode);
		UINT16_TO_STREAM(p,att_id);
		UINT16_TO_STREAM(p,offset);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_app_on_attribute_write_cb(trans_id_t trans_id, UINT8 conn_id,UINT8 att_opcode, UINT8 status, UINT16 att_id,UINT16 offset, buffer_t * buffer)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(buffer)
		{
			buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, HCI2ILE_LENGTH_ATTRIBUTE_WRITE_CB + sizeof(UINT16) + sizeof(UINT16));
			p_buf = app_alloc(HCI2ILE_LENGTH_ATTRIBUTE_WRITE_CB + HCI2ILE_SIZE_OF_BUFFER(buffer->length));
		}
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_ATTRIBUTE_WRITE_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_ATTRIBUTE_WRITE);
		UINT8_TO_STREAM(p,status);
		UINT8_TO_STREAM(p,conn_id);
		UINT8_TO_STREAM(p,att_opcode);
		UINT16_TO_STREAM(p,att_id);
		UINT16_TO_STREAM(p,offset);

		if(buffer)
		{
			UINT16_TO_STREAM(p,buffer->length);
			UINT16_TO_STREAM(p,0); // Offset would always be 0 since we are copying data from the offset into new buffer_t
			memcpy (p, buffer->data+buffer->offset, buffer->length);

			length = (p - cb_buffer) + buffer->length; // Pointer difference should be the length of encoded params, excluding buffer data
		}
		else
			length = (p - cb_buffer); // Pointer difference should be the length of encoded params

		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_app_on_attribute_read_cb(trans_id_t trans_id, UINT8 conn_id,UINT8 att_opcode, UINT8 status, UINT16 att_id, buffer_t * buffer)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(buffer)
		{
			buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, HCI2ILE_LENGTH_ATTRIBUTE_READ_CB + sizeof(UINT16) + sizeof(UINT16));
			p_buf = app_alloc(HCI2ILE_LENGTH_ATTRIBUTE_READ_CB + HCI2ILE_SIZE_OF_BUFFER(buffer->length));
		}
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_ATTRIBUTE_READ_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_ATTRIBUTE_READ);
		UINT8_TO_STREAM(p,status);
		UINT8_TO_STREAM(p,conn_id);
		UINT8_TO_STREAM(p,att_opcode);
		UINT16_TO_STREAM(p,att_id);

		if(buffer)
		{
			UINT16_TO_STREAM(p,buffer->length);
			UINT16_TO_STREAM(p,0); // Offset would always be 0 since we are copying data from the offset into new buffer_t
			memcpy (p, buffer->data+buffer->offset, buffer->length);

			length = (p - cb_buffer) + buffer->length; // Pointer difference should be the length of encoded params, excluding buffer data
		}
		else
			length = (p - cb_buffer); // Pointer difference should be the length of encoded params

		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_app_on_notification_registered_cb(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, UINT8 status)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_NOTIFICATION_REGISTERED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_NOTIFICATION_REGISTERED);
		UINT8_TO_STREAM(p,status);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p,att_id);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length , p_buf);
	}

void HAL_app_on_att_mtu_changed_cb(trans_id_t trans_id, UINT8 conn_id, UINT16 mtu_size)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_ATT_MTU_CHANGED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_MTU_CHANGED);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p,mtu_size);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length , p_buf);
	}

void HAL_app_on_service_added_cb (trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(uuid)
			p_buf = app_alloc(HCI2ILE_LENGTH_SERVICE_ADDED_CB + uuid->length);
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_SERVICE_ADDED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_SERVICE_ADDED);
		UINT8_TO_STREAM(p,status);
		UINT16_TO_STREAM(p,att_id);
		if (uuid != NULL)
		{
			UINT8_TO_STREAM(p,uuid->length);
			UUID_TO_STREAM(p,uuid);
		}
		else //no more primary services left: Sending a dummy UUID of size 0 to indicate that
		{
			UINT8_TO_STREAM(p,0);
		}
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length , p_buf);
	}

void HAL_app_on_include_service_added_cb(trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(uuid)
			p_buf = app_alloc(HCI2ILE_LENGTH_INCLUDED_SERVICE_ADDED_CB + uuid->length);
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_INCLUDED_SERVICE_ADDED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER);
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_INCLUDED_SERVICE_ADDED);
		UINT8_TO_STREAM(p,status);
		UINT16_TO_STREAM(p,att_id);
		if (uuid != NULL)
		{
			UINT8_TO_STREAM(p,uuid->length);
			UUID_TO_STREAM(p,uuid);
		}
		else //no more services left: Sending a dummy UUID of size 0 to indicate that
		{
			UINT8_TO_STREAM(p,0);
		}
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length , p_buf);
	}

void HAL_app_on_service_removed_cb(trans_id_t trans_id, UINT8 status, UINT16 start_handle, UINT16 end_handle)
    {
        UINT8 * cb_buffer;
        UINT8 length;
        logi("");
        UINT8* p_buf; UINT8* p;
        p_buf = app_alloc(HCI2ILE_LENGTH_SERVICE_REMOVED_CB);
        if(!p_buf)
        {
            return;
        }
        cb_buffer = (p_buf + DBG_EVT_HEADER);
        p = cb_buffer;
        UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_SERVICE_REMOVED);
        UINT8_TO_STREAM(p,status);
        UINT16_TO_STREAM(p,start_handle);
        UINT16_TO_STREAM(p,end_handle);
        length = p-cb_buffer;
        hci2ile_callback_send(trans_id, length , p_buf);
    }

void HAL_app_on_characteristic_added_cb (trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(uuid)
			p_buf = app_alloc(HCI2ILE_LENGTH_CHAR_ADDED_CB + uuid->length);
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_CHAR_ADDED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_CHARACTERISTIC_ADDED);
		UINT8_TO_STREAM(p,status);
		UINT16_TO_STREAM(p,att_id);
		if (uuid != NULL)
		{
			UINT8_TO_STREAM(p,uuid->length);
			UUID_TO_STREAM(p,uuid);
		}
		else //no more primary services left: Sending a dummy UUID of size 0 to indicate that
		{
			UINT8_TO_STREAM(p,0);
		}
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length , p_buf);
	}

void HAL_app_on_descriptor_added_cb (trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(uuid)
			p_buf = app_alloc(HCI2ILE_LENGTH_DESC_ADDED_CB + uuid->length);
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_DESC_ADDED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_DESCRIPTOR_ADDED);
		UINT8_TO_STREAM(p,status);
		UINT16_TO_STREAM(p,att_id);
		if (uuid != NULL)
		{
			UINT8_TO_STREAM(p,uuid->length);
			UUID_TO_STREAM(p,uuid);
		}
		else //no more primary services left: Sending a dummy UUID of size 0 to indicate that
		{
			UINT8_TO_STREAM(p,0);
		}
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length , p_buf);
	}

void HAL_app_on_service_started_cb (trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(uuid)
			p_buf = app_alloc(HCI2ILE_LENGTH_SERVICE_STARTED_CB + uuid->length);
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_SERVICE_STARTED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_SERVICE_STARTED);
		UINT8_TO_STREAM(p,status);
		UINT16_TO_STREAM(p,att_id);
		if (uuid != NULL)
		{
			UINT8_TO_STREAM(p,uuid->length);
			UUID_TO_STREAM(p,uuid);
		}
		else //no more primary services left: Sending a dummy UUID of size 0 to indicate that
		{
			UINT8_TO_STREAM(p,0);
		}
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length , p_buf);
	}

void HAL_app_on_notification_cb(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, buffer_t * buffer, BOOLEAN is_indication)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		if(buffer)
		{
			buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, HCI2ILE_LENGTH_NOTIFICATION_CB + sizeof(UINT16) + sizeof(UINT16));
			p_buf = app_alloc(HCI2ILE_LENGTH_NOTIFICATION_CB + HCI2ILE_SIZE_OF_BUFFER(buffer->length));
		}
		else
			p_buf = app_alloc(HCI2ILE_LENGTH_NOTIFICATION_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_NOTIFICATION);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p,att_id);
		UINT8_TO_STREAM(p, is_indication);
		if(buffer)
		{
			UINT16_TO_STREAM(p,buffer->length);
			UINT16_TO_STREAM(p,0); // Offset would always be 0 since we are copying data from the offset into new buffer_t
			memcpy (p, buffer->data+buffer->offset, buffer->length);
			length = (p - cb_buffer) + buffer->length; // Pointer difference should be the length of encoded params, excluding buffer data
		}
		else
		{
			length = (p - cb_buffer); // Pointer difference should be the length of encoded params
		}

		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_app_on_indication_confirmation_cb(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_INDICATION_CONFIRMATION_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_INDICATION_CONFIRMATION);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p,att_id);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_app_bonding_completed_cb(trans_id_t trans_id, UINT8* bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 status, UINT8 *id_bdaddr, UINT8 id_bdaddr_type)
	{

		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_BONDING_COMPLETED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_BONDING_COMPLETED_CB);
		UINT8_TO_STREAM(p,status);
		ARRAY_TO_STREAM(p,bd_addr,HCI2ILE_SIZE_OF_BD_ADDR);  // Should we have a BDADDR_TO_STREAM
		UINT8_TO_STREAM(p,bdaddr_type);
		UINT8_TO_STREAM(p,conn_id);
		ARRAY_TO_STREAM(p,id_bdaddr,HCI2ILE_SIZE_OF_BD_ADDR);
		UINT8_TO_STREAM(p,id_bdaddr_type);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id,  length , p_buf);
	}
	
void HAL_app_on_link_enc_changed_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 status, UINT8 sec_level)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_LINK_ENC_CHANGE_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_LINK_ENC_CHANGED_CB);
		UINT8_TO_STREAM(p,status);
		UINT8_TO_STREAM(p,conn_id);
		UINT8_TO_STREAM(p, sec_level);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_on_read_authpayload_timeout_cb(trans_id_t trans_id, UINT8 conn_id, UINT16 authpayload_timeout_ms)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_READ_AUTHPAYLOAD_TIMEDOUT_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_READ_AUTH_PAYLOAD_TIMEOUT_CB);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p,authpayload_timeout_ms);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id,  length , p_buf);
	}
	
#if (TEST_CODE == TRUE)
	/* Needed for VSC HCI passthrough*/	
void HAL_on_vsc_cb(trans_id_t trans_id, UINT8 len, UINT8 *buffer)
{
			UINT8 * cb_buffer;
			UINT8 length;
			logi("");
			UINT8* p_buf; UINT8* p;
			p_buf = app_alloc(HCI2ILE_LENGTH_VSC_CB + len);
			if(!p_buf)
			{
				return;
			}
			cb_buffer = (p_buf + DBG_EVT_HEADER );
			p = cb_buffer;
			UINT8_TO_STREAM(p, HCI2ILE_CB_ID_ON_VSC_CB);
			memcpy(p, buffer, len);
			p += len;
			length = p-cb_buffer;
			hci2ile_callback_send(trans_id, length, p_buf);
}
#endif /*TEST_CODE == TRUE*/

void HAL_app_data_len_change_evt_cb(trans_id_t trans_id, UINT8 conn_id, UINT16 max_tx_octets, UINT16 max_tx_time, UINT16 max_rx_octets, UINT16 max_rx_time)
	{
		logi("");
		UINT8 * cb_buffer;
		UINT8 length;
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_DATA_LEN_CHANGE_EVT_CB);
		if(!p_buf)
		{
			return;
		}

		cb_buffer = (p_buf + DBG_EVT_HEADER);
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_ON_DATA_LEN_CHANGE_EVT_CB);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p,max_tx_octets);
		UINT16_TO_STREAM(p,max_tx_time);
		UINT16_TO_STREAM(p,max_rx_octets);
		UINT16_TO_STREAM(p,max_tx_time);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id, length, p_buf);
	}

void HAL_app_stack_initialized_cb()
{
	logd("");
#if (TARGET_THREADX_RW == TRUE)
	UINT8 *p_buf = (UINT8*) alloc_queue_element(7, HCI_ALLOC);
#if (PARANOID_STACK == TRUE)
	if (!p_buf)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
		UINT8* p = p_buf;

		UINT8_TO_STREAM(p, HCI_EVT);
		UINT8_TO_STREAM(p, HCI_EVENT_CMD_CMPL);
		UINT8_TO_STREAM(p, 4);
		UINT8_TO_STREAM(p,0x0b); //pack the number of h2c packets

		//pack opcode
		*p++ = 0;
		*p++ = 0;

		//pack status
		*p = 0;
		UINT8 *buff = p_buf - sizeof(uint32_t);
		tx_queue_send(&st_to_tr_msg_queue, &buff, TX_NO_WAIT);
		tx_event_flags_set(&tr_evnt_flags, OS_EVNT_FLG_HCI_EVNT, TX_OR);
#endif /* TARGET_THREADX_RW == TRUE */
}

static void HAL_key_request_cb(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 key_type)
{
	logi("");
	UINT8 * cb_buffer;
	UINT8 length;
	UINT8* p_buf; UINT8* p;
	p_buf = app_alloc(HCI2ILE_LENGTH_KEY_REQUEST_CB);
	if(!p_buf)
	{
		return;
	}
	cb_buffer = (p_buf + DBG_EVT_HEADER );
	p = cb_buffer;
	UINT8_TO_STREAM(p, HCI2ILE_CB_ID_ON_KEY_REQ_CB);
	UINT8_TO_STREAM(p, bdaddr_type);
	ARRAY_TO_STREAM(p, bdaddr, BD_ADDR_LEN);
	UINT8_TO_STREAM(p, key_type);
	length = p - cb_buffer;
	hci2ile_callback_send(trans_id,  length , p_buf);
}

static void HAL_key_update_cb(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 key_type,  UINT8 key_length, UINT8* key_value)
{
	logi("");
	UINT8 * cb_buffer;
	UINT8 length;
	UINT8* p_buf; UINT8* p;
	p_buf = app_alloc(HCI2ILE_LENGTH_KEY_UPDATE_CB + key_length);
	if(!p_buf)
	{
		return;
	}
	cb_buffer = (p_buf + DBG_EVT_HEADER );
	p = cb_buffer;
	UINT8_TO_STREAM(p, HCI2ILE_CB_ID_ON_KEY_UPDATE_CB);
	UINT8_TO_STREAM(p, bdaddr_type);
	ARRAY_TO_STREAM(p, bdaddr, BD_ADDR_LEN);
	UINT8_TO_STREAM(p, key_type);
	UINT8_TO_STREAM(p, key_length);
	ARRAY_TO_STREAM(p, key_value, key_length);
	length = p - cb_buffer;
	hci2ile_callback_send(trans_id,  length , p_buf);
}
static void HAL_bonding_info_cb(trans_id_t trans_id,  UINT8* bdaddr, UINT8 bdaddr_type, smp_bonding_key_t *keys)
{
	logi("");
	UINT8 * cb_buffer;
	UINT8 length;
	UINT8* p_buf; UINT8* p;
	p_buf = app_alloc(HCI2ILE_LENGTH_BONDING_INFO_CB);
	if(!p_buf)
	{
		return;
	}
	cb_buffer = (p_buf + DBG_EVT_HEADER );
	p = cb_buffer;
	UINT8_TO_STREAM(p, HCI2ILE_CB_ID_ON_KEY_UPDATE_CB);
	UINT8_TO_STREAM(p, bdaddr_type);
	ARRAY_TO_STREAM(p, bdaddr, BD_ADDR_LEN);
	UINT8_TO_STREAM(p, BOND_INFO);
	UINT8_TO_STREAM(p, HCI2ILE_BOND_INFO_LEN);
	UINT8_TO_STREAM(p, keys->security_level);
	UINT8_TO_STREAM(p, keys->keys_distributed);
	UINT8_TO_STREAM(p, keys->key_size);
	UINT8_TO_STREAM(p, keys->key_type);
	ARRAY_TO_STREAM(p, keys->peer_ltk, 16);
	ARRAY_TO_STREAM(p, keys->peer_rand, 8);
	UINT16_TO_STREAM(p, keys->peer_ediv);
	ARRAY_TO_STREAM(p, keys->local_ltk, 16);
	ARRAY_TO_STREAM(p, keys->local_rand, 8);
	UINT16_TO_STREAM(p, keys->local_ediv);
#if (PRIVACY_FEATURE == TRUE)
	ARRAY_TO_STREAM(p, keys->peer_irk, 16);
	ARRAY_TO_STREAM(p, keys->local_irk, 16);
#else
	{
		UINT8 dummy_irk[16];
		memset(dummy_irk, 0, 16);
		ARRAY_TO_STREAM(p, dummy_irk, 16);
		ARRAY_TO_STREAM(p, dummy_irk, 16);

	}
#endif
#if (SIGNED_WRITE == TRUE)
	ARRAY_TO_STREAM(p, keys->peer_csrk, 16);
	ARRAY_TO_STREAM(p, keys->local_csrk, 16);
#else
	{
		UINT8 dummy_csrk[16];
		memset(dummy_csrk, 0, 16);
		ARRAY_TO_STREAM(p, dummy_csrk, 16);
		ARRAY_TO_STREAM(p, dummy_csrk, 16);
	}
#endif

	length = p - cb_buffer;
	hci2ile_callback_send(trans_id,  length , p_buf);
}
static void HAL_clear_key_cb(trans_id_t trans_id,  UINT8* bdaddr, UINT8 bdaddr_type)
{
	logi("");
	UINT8 * cb_buffer;
	UINT8 length;
	UINT8* p_buf; UINT8* p;
	p_buf = app_alloc(HCI2ILE_LENGTH_CLEAR_KEY_CB);
	if(!p_buf)
	{
		return;
	}
	cb_buffer = (p_buf + DBG_EVT_HEADER );
	p = cb_buffer;
	UINT8_TO_STREAM(p, HCI2ILE_CB_ID_ON_KEY_UPDATE_CB);
	UINT8_TO_STREAM(p, bdaddr_type);
	ARRAY_TO_STREAM(p, bdaddr, BD_ADDR_LEN);
	UINT8_TO_STREAM(p, CLEAR_KEY);
	UINT8_TO_STREAM(p, 0);
	length = p - cb_buffer;
	hci2ile_callback_send(trans_id,  length , p_buf);
}

#if (L2CAP_COC == TRUE)

void HAL_app_lc_register_cb (trans_id_t trans_id, UINT16 psm, INT8 status)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_LC_REGISTER_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_LC_REGISTER_CB);
		UINT8_TO_STREAM(p,status);
		UINT16_TO_STREAM(p,psm);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_app_lc_authorisation_cb (trans_id_t trans_id, UINT8 conn_id, UINT16 psm)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_LC_AUTH_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_LC_AUTHORISATION_CB);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p,psm);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_app_lc_connection_cmpl_cb (trans_id_t trans_id, UINT8 conn_id, UINT16 psm, UINT8 handle, UINT16 r_mtu, UINT8 initial_credit, INT8 status)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_LC_CONNECTION_COMPLETED_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_LC_CONNECTION_CMPL_CB);
		UINT8_TO_STREAM(p,(UINT8)status);
		UINT8_TO_STREAM(p,conn_id);
		UINT16_TO_STREAM(p,psm);
		UINT8_TO_STREAM(p,handle);
		UINT16_TO_STREAM(p,r_mtu);
		UINT8_TO_STREAM(p,initial_credit);
		//loge("status = %d\n",status);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id,  length , p_buf);

	}

void HAL_app_lc_flow_control_cb (trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle, UINT8 fc_packets)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_LC_FLOW_CONTROL_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_LC_FLOW_CONTROL_CB);
		UINT8_TO_STREAM(p,conn_id);
		UINT8_TO_STREAM(p,coc_handle);
		UINT8_TO_STREAM(p,fc_packets);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_app_lc_recv_data_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle, UINT8 * buffer, UINT16 buffer_len)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		buffer_len = TRUNCATE_TO_16BIT_LENGTH(buffer_len, HCI2ILE_LENGTH_LC_RECV_DATA_CB);
		p_buf = app_alloc(HCI2ILE_LENGTH_LC_RECV_DATA_CB + buffer_len);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_LC_RECV_DATA_CB);
		UINT8_TO_STREAM(p,conn_id);
		UINT8_TO_STREAM(p,coc_handle);
		UINT16_TO_STREAM(p,buffer_len);
		memcpy(p,buffer, buffer_len);
		length = (p-cb_buffer) + buffer_len;
		hci2ile_callback_send(trans_id,  length , p_buf);
	}

void HAL_app_lc_disconnection_cmpl_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle, UINT8 status)
	{
		UINT8 * cb_buffer;
		UINT8 length;
		logi("");
		UINT8* p_buf; UINT8* p;
		p_buf = app_alloc(HCI2ILE_LENGTH_LC_DISCONNECTION_COMPLETE_CB);
		if(!p_buf)
		{
			return;
		}
		cb_buffer = (p_buf + DBG_EVT_HEADER );
		p = cb_buffer;
		UINT8_TO_STREAM(p,HCI2ILE_CB_ID_LC_DISCONNECTION_CMPL_CB);
		UINT8_TO_STREAM(p,status);
		UINT8_TO_STREAM(p,conn_id);
		UINT8_TO_STREAM(p,coc_handle);
		length = p-cb_buffer;
		hci2ile_callback_send(trans_id,  length , p_buf);

	}

#endif
/*******************************************

command checker

******************************************/
#if 0
BOOLEAN hci2ile_command_checker ( UINT8 parameter_1, UINT8 length)
{
	BOOLEAN status;
	switch(parameter_1)
		{

			case HCI2ILE_STACK_INIT:
					{
						if(length > 0x05)

							status=FALSE;
						else
							status=TRUE;
					}

			case HCI2ILE_REGISTER_APPLICATION:
					{
						if(length > 0x02)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_DEREGISTER_APPLICATION:
					{
						if(length > 0x03)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_SET_ADVERTISEMENT_DATA:
					{
						if(length > 0x24)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_remove_advertisement_data:
					{
						if(length > 0x24)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_START_DISCOVERABLE:
					{
						if(length > 0x11)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_STOP_DISCOVERABLE:
					{
						if(length > 0x03)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_SET_LOCAL_DEVICE_NAME:
					{
						if(length > 0x22)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_START_SCAN:
					{
						if(length > 0x0B)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_STOP_SCAN:
					{
						if(length > 0x03)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_CONNECT:
					{
						if(length > 0x0B)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_DISCONNECT:
					{
						if(length > 0x09)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_ADD_TO_WHITELIST:
					{
						if(length > 0x0A)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_REMOVE_FROM_WHITELIST:
					{
						if(length > 0x0A)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_CLEAR_WHITELIST:
					{
						if(length > 0x03)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_CREATE_BOND:
					{
						if(length > 0x0B)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_SEND_PASSKEY:
					{
						if(length > 0x0C)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_SEND_AUTHORIZATION:
					{
						if(length > 0x0A)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_SMP_REGISTER:
					{
						if(length > 0x0A)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_SIGN_DATA:
					{
						if(length > 0x00)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_GET_ATTRIBUTE_MTU:
					{
						if(length > 0x04)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_SET_ATTRIBUTE_MTU:
					{
						if(length > 0x06)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_UPDATE_CONN_PARAMS:
					{
						if(length > 0x11)

							status = FALSE;
						else
							status = TRUE;
						break;
					}

			case HCI2ILE_ADD_SERICE:
					{
						if(length > 0x0D)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_ADD_CHARACTERISTIC:
					{
						if(length > 0x0F)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_ADD_DESCRIPTOR:
					{
						if(length > 0x0F)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_START_SERVICE:
					{
						if(length > 0x03)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_REMOVE_SERVICE:
					{
						if(length > 0x05)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_SEND_ATTRIBUTE_READ_RSP:
					{
						if(length > 0xFF)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_SEND_ATTRIBUTE_WRITE_RSP:
					{
						if(length > 0xFF)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_SEND_NOTIFICATION:
					{
						if(length > 0xFF)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_DISCOVER_PRIMARY_SERVICE:
					{
						if(length > 0x0D)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_DISCOVER_INCLUDED_SERVICE:
					{
						if(length > 0x08)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_DISCOVER_CHARACTERISTIC:
					{
						if(length > 0x08)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_READ_ATTRIBUTE_VALUE:
					{
						if(length > 0x34)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_WRITE_ATTRIBUTE_VALUE:
					{
						if(length > 0xFF)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
			case HCI2ILE_REGISTER_NOTIFICATION:
					{
						if(length > 0x07)

							status = FALSE;
						else
							status = TRUE;
						break;
					}
	}
	return status;
}
#endif

#if (TARGET_THREADX_RW == TRUE)


void stack_interface_handler()
{
	UINT32 sts;
	UINT8 *pHciMsg;

	sts = tx_queue_receive(&tr_to_st_msg_queue, &pHciMsg, TX_NO_WAIT);
    
    wdog_kick();
    
	if(sts == TX_SUCCESS)
	{
		/*>>> STACK code entry for command or data msg received
			  from Host:
		Pointer 'pHciMsg' pointing to link pointer (of size 4bytes)
		+ HCI command msg or data msg:
		Memory structure for HCI command msg:
		Byte index	  Data
		0~3			 Link pointer
		4			   Type = 1 for HCI commands
		5			   Lower 8bits of OCF
		6			   Bit1~0 <- upper 2bits of OCF
						Bit7~2 <- OGF 6bits
		7			   Parmeter length
		8			   parameter0
		...			 ...				 ...

		*/
		UINT8 ocf, ogf;
		UINT8 *ptr = pHciMsg + 4;

		ocf = *(ptr+1);
		ogf = *(ptr+2);
		//printf ("stack_interface_handler dispatch\n");
		hex_dump("from 3vt:", ptr, ptr[3]+4);

#ifdef DBG_FRMWRK
        // log message to debug framework if logging is enabled for this message type
        dbg_frmwrk_enqueue_prepare(pHciMsg + 4, DBG_FRMWRK_TR_TO_ST);
#endif

		if (0xfc == ogf)
		{
			hci2ile_command_dispatch_req((ogf<<8|ocf), ptr[3], &(ptr[4]));
		}

#if SHARED_MEM_VALID
	if (!panic)
        mbox_send_ctrl_msg(MBOX_LOCAL_ILE_CTRL_CHANNEL_OUT,MBOX_MSG_TYPE_FREE_MEMORY,(uint32_t)pHciMsg);
#else
		dealloc(pHciMsg);
#endif
	}
}

void stack_ll_handler()
{
	UINT32 sts;
	UINT8 *pHciMsg;

	sts = tx_queue_receive(&ll_to_st_msg_queue, &pHciMsg, TX_NO_WAIT);
    
    wdog_kick();
    
	if(sts == TX_SUCCESS)
	{
		/*>>> STACK code entry for event or data msg received from
			  controller >>>
		Pointer 'pHciMsg' pointing to link pointer (of size 4bytes)
		+ HCI event msg or data msg:
		Memory structure for HCI event msg:
		Byte index		Data
		0~3 			Link pointer
		4				Type = 4 for HCI events
		5				Event code = 0x3E
		6				Parmeter length
		7				parameter0
		... 			... 				...

		Memory structure for HCI data msg:
		Byte index		Data
		0~3 			Link pointer
		4				Type = 2 for HCI data
		5				Lower 8bits of Handle
		6				Bit3~0 <- upper 4bits of Handle
						Bit5~4 <- PBFlag
						Bit7~6 <- BCFlag
		7				Lower 8bits of Length
		8				Upper 8bits of Length
		6				data0
		... 			... 				...


		*/

#ifdef DBG_FRMWRK
        // log message to debug framework if logging is enabled for this message type
        dbg_frmwrk_enqueue_prepare(pHciMsg + 4, DBG_FRMWRK_LL_TO_ST);
#endif
		tl_recv_msg(pHciMsg+4);
		//After msg is processed, the allocated memory block should be released.
		dealloc(pHciMsg);
	}
}

#endif /* TARGET_THREADX_RW == TRUE */

/*************************
structures
**************************/
static gatt_callbacks_t gatt_cb =
{
		.iLE_on_att_mtu_changed_cb = HAL_app_on_att_mtu_changed_cb,
		.iLE_on_primary_service_discovered_cb = HAL_app_on_primary_service_discovered_cb,
		.iLE_on_included_service_discovered_cb = HAL_app_on_included_service_discovered_cb,
		.iLE_on_characteristic_discovered_cb = HAL_app_on_characteristic_discovered_cb,
		.iLE_on_descriptor_discovered_cb = HAL_app_on_descriptor_discovered_cb,
		.iLE_on_attribute_read_cb = HAL_app_on_attribute_read_cb,
		.iLE_on_attribute_write_cb = HAL_app_on_attribute_write_cb,
		.iLE_on_service_added_cb = HAL_app_on_service_added_cb,
		.iLE_on_include_service_added_cb = HAL_app_on_include_service_added_cb,
		.iLE_on_service_removed_cb = HAL_app_on_service_removed_cb,
		.iLE_on_characteristic_added_cb = HAL_app_on_characteristic_added_cb,
		.iLE_on_descriptor_added_cb = HAL_app_on_descriptor_added_cb,
		.iLE_on_notification_cb = HAL_app_on_notification_cb,
		.iLE_on_notification_registered_cb = HAL_app_on_notification_registered_cb,
		.iLE_on_indication_confirmation_cb = HAL_app_on_indication_confirmation_cb,
		.iLE_on_attribute_read_req_cb = HAL_app_on_attribute_read_req_cb,
		.iLE_on_attribute_write_req_cb = HAL_app_on_attribute_write_req_cb,
		.iLE_on_service_started_cb = HAL_app_on_service_started_cb,
};

static device_control_callbacks_t dev_cb =
{ 	
	.iLE_stack_initialized_cb = HAL_app_stack_initialized_cb,
	.iLE_scan_result_cb = HAL_app_scan_result_cb,
	.iLE_scan_completed_cb = HAL_app_scan_completed_cb,
	.iLE_on_link_enc_changed_cb = HAL_app_on_link_enc_changed_cb,
	.iLE_bonding_completed_cb = HAL_app_bonding_completed_cb,
	.iLE_on_connected_cb = HAL_on_connected_cb,
	.iLE_on_disconnected_cb = HAL_on_disconnected_cb,
	.iLE_on_conn_param_update_cb = HAL_on_conn_param_update,
#if (TEST_CODE==TRUE)
#if (LE_PING_ENABLE==TRUE)
	.iLE_read_authpayload_timeout_cb = HAL_on_read_authpayload_timeout_cb,

#endif
	.iLE_vsc_cb = HAL_on_vsc_cb,
#endif
	.iLE_data_len_change_evt_cb = HAL_app_data_len_change_evt_cb,
};
#if (L2CAP_COC == TRUE)

static l2cap_coc_callbacks_t l2cap_coc_cbs =
{
	.register_cb = HAL_app_lc_register_cb,
	.authorisation_cb = HAL_app_lc_authorisation_cb,
	.connection_cmpl_cb = HAL_app_lc_connection_cmpl_cb,
	.flow_control_cb = HAL_app_lc_flow_control_cb ,
	.recv_data_cb = HAL_app_lc_recv_data_cb ,
	.disconnect_cmpl_cb = HAL_app_lc_disconnection_cmpl_cb ,
};

static storage_callbacks_t storage_cbs =
{
		.key_request_cb = HAL_key_request_cb,
		.key_update_cb = HAL_key_update_cb,
		.bonding_info_cb = HAL_bonding_info_cb,
		.clear_key_cb = HAL_clear_key_cb,
};
#endif

void adapt_app_init()
{
    logd("Starting Adaptation Layer App");
    iLE_register_application(&dev_cb, &gatt_cb, NULL, NULL, HAL_register_application_cb);
}

void adapt_app_cleanup()
{
    logd("");
    iLE_deregister_application(adapt_app_handle);
}

/* ------ End of file ------ */

#endif /* HCI2ILE_ADAPT_APP == TRUE */
