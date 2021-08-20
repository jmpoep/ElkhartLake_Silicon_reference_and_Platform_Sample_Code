/** @file
  HCI protocol implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "device_struct.h"
#include "device_mgr.h"
#include "tl.h"
#include "l2cap.h"
#include "gap.h"
#include "config_host.h"
#include "hci_host.h"
#include "profile_adapt.h"
#include "smp.h"

#define MODULE_DBG_LVL HCI_DBG_LVL
#include "log.h"

#define HCI_CMD_Q_LEN 10
#define HCI_CMD_TIMEOUT 2000 //ms

static queue_internal_t hci_cmd_tx_q;

static INT8 hci_send_msg(UINT8 type, UINT8* msg, UINT16 len);

static void hci_cmd_cmpl_handler(UINT8* buffer, UINT8 len)
{
	UINT8 event_length;
	UINT16 opcode;
	UINT8 status;
#if (TEST_CODE == TRUE)
	/* Needed for VSC HCI Passthrough*/
	UINT8 *buf = buffer - 2;
	UINT8 length = len + 2;
#endif
	STREAM_TO_UINT8(event_length, buffer);
	STREAM_TO_UINT8(g_local_adapter.hci_data.hci_credit, buffer);
#if (SIMULTANEOUS_HCI_COMMANDS == FALSE)
	if (g_local_adapter.hci_data.hci_credit > 1)
		g_local_adapter.hci_data.hci_credit = 1; /* Even if controller gives more credit, use only one. */
#endif
	STREAM_TO_UINT16(opcode, buffer);
	if (g_local_adapter.hci_data.timer_active != TRUE)
	{
		loge("Critical error: Command complete received (0x%04x) without stored command.", opcode);
		return;
	}
	if (g_local_adapter.hci_data.pending_opcode != opcode)
	{
		loge("ERROR: Unaligned Command Complete Pkt! Something is terribly wrong! Stored = %x, Rcvd = %x", g_local_adapter.hci_data.pending_opcode, opcode);
		return;
	}
	if (g_local_adapter.hci_data.timer_active == TRUE)
	{
		g_local_adapter.hci_data.timer_active = FALSE;
		osa_stop_timer(&(g_local_adapter.hci_data.hci_cmd_timer), HCI_CMD_TIMER, 0);
	}
	STREAM_TO_UINT8(status, buffer);
	if (status != HCI_EVENT_STATUS_SUCCESS)
	{
		switch (status)
		{
		case HCI_EVENT_STATUS_COMMAND_DISALLOWED:
			loge("Command 0x%04x disallowed", opcode);
			break;
		default:
			logw("Event status: %d", status);
		}
	}
	event_length -= 4;
	switch (opcode)
	{
	case HCI_CMD_RESET:
		reset_cmpl_handler();
		break;
	case HCI_CMD_READ_LOCAL_FEAT:
		read_local_feat_cmpl(buffer, event_length);
		break;
	case HCI_CMD_LE_READ_LOCAL_SUPPORTED_FEAT:
		le_read_supported_feat_cmpl(buffer, event_length);
		break;
	case HCI_CMD_SET_EVENT_MASK:
		evt_mask_cmpl();
		break;
	case HCI_CMD_SET_EVENT_MASK_PAGE_2:
		evt_mask_page_2_cmpl();
		break;
#if (LE_PING_ENABLE==TRUE)
	case HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT:
	case HCI_CMD_WRITE_AUTHPAYLOAD_TIMEOUT:
		gap_handle_command_complete(opcode, status, buffer, event_length);
		break;
#endif //LE_PING_ENABLE==TRUE
	case HCI_CMD_LE_SET_EVENT_MASK:
		le_evt_mask_cmpl();
		break;
	case HCI_CMD_WRITE_LE_HOST_SUPPORTED:
		write_le_host_support_cmpl();
		break;
	case HCI_CMD_READ_LOCAL_VERSION_INFO:
		break;
	case HCI_CMD_READ_BUFFER_SIZE:
		read_buf_size_cmpl(buffer, event_length);
		break;
	case HCI_CMD_LE_READ_BUFFER_SIZE:
		le_read_buf_size_cmpl(buffer, event_length);
		break;
	case HCI_CMD_READ_BD_ADDR:
		read_bd_addr_cmpl(buffer, event_length);
		break;
	case HCI_CMD_READ_RSSI:
		break;
	case HCI_CMD_LE_READ_WHITE_LIST_SIZE:
		le_read_white_list_size_cmpl(buffer, event_length);
		break;
	case HCI_CMD_LE_RAND:
#if (SMP_FEATURE)
		smp_proc_hci_rand(buffer, event_length);
#endif /* SMP_FEATURE */
		break;
	case HCI_CMD_LE_ENCRYPT:
#if (SMP_FEATURE)
		smp_proc_hci_le_encrypt(buffer, event_length);
#endif /* SMP_FEATURE */
		break;
	//FIXME: Remove this
#if (TARGET_THREADX == TRUE)
	case HCI_CMD_VS_MANUF_MODE:
		manuf_cmd_cmpl();
		break;
#endif
	case HCI_CMD_LE_SET_DATA_LEN:
	{
		if (status == HCI_EVENT_STATUS_SUCCESS)
		{
			UINT16 connHandle=0;
			STREAM_TO_UINT16(connHandle, buffer);
			logd("HCI_CMD_LE_SET_DATA_LEN status=HCI_EVENT_STATUS_SUCCESS");
			logd("HCI_CMD_LE_SET_DATA_LEN connHandle=%x", connHandle);
		}
		else
			logd("HCI_CMD_LE_SET_DATA_LEN failed, status=%d", status);
	}
	break;
	case HCI_CMD_LE_WRITE_SUG_DEF_DATA_LEN:
	{
		logd("HCI_CMD_LE_WRITE_SUG_DEF_DATA_LEN status=%d", status);
		if (status == HCI_EVENT_STATUS_SUCCESS)
			le_write_def_data_len_cmpl();
	}
	break;
	case HCI_CMD_LE_READ_MAX_DATA_LEN:
	{
		logd("HCI_CMD_LE_READ_MAX_DATA_LEN status=%d", status);
		le_read_max_data_len_cmpl(opcode, status, buffer, event_length);
	}
	break;
	case HCI_CMD_LE_SET_ADV_PARAM:
	case HCI_CMD_LE_SET_ADV_DATA:
	case HCI_CMD_LE_SET_SCAN_RESP_DATA:
	case HCI_CMD_LE_SET_ADV_ENABLE:
	case HCI_CMD_LE_SET_SCAN_PARAM:
	case HCI_CMD_LE_SET_SCAN_ENABLE:
	case HCI_CMD_LE_ADD_DEV_TO_WHITE_LIST:
	case HCI_CMD_LE_REMOVE_DEV_FRM_WHITE_LIST:
	case HCI_CMD_LE_CLEAR_WHITE_LIST:
	case HCI_CMD_LE_CREATE_CONN_CANCEL:
#if (PRIVACY_FEATURE == TRUE)
	case HCI_CMD_LE_SET_RANDOM_ADDRESS:
#endif
#if (CONTROLLER_PRIVACY == TRUE)
	case HCI_CMD_LE_ADD_DEV_TO_RESOLVING_LIST:
	case HCI_CMD_LE_REMOVE_DEV_FROM_RESOLVING_LIST:
	case HCI_CMD_LE_CLEAR_RESOLVING_LIST:
#endif /* CONTROLLER_PRIVACY */
		gap_handle_command_complete(opcode, status, buffer, event_length);
		break;
#if (CONTROLLER_PRIVACY)
	case HCI_CMD_LE_READ_RESOLVING_LIST_SIZE:
		le_read_resolving_list_size_cmpl(buffer, event_length);
		break;
	case HCI_CMD_LE_READ_PEER_RESOLVABLE_ADDR:
	case HCI_CMD_LE_READ_LOCAL_RESOLVABLE_ADDR:
	case HCI_CMD_LE_SET_ADDR_RESOLUTION_EN:
		break;
	case HCI_CMD_LE_SET_RESOLVABLE_PRIVATE_ADDR_TOUT:
		le_set_rpa_timeout_cmpl();
		break;
#endif /* CONTROLLER_PRIVACY */
#if (TARGET_THREADX == TRUE)
	case PROFILE_OPERATION_ASYNC_EVENT:
		logd("Profile async event sent.");
		break;
#endif
	default:
#if (TEST_CODE == TRUE)
	/* Needed for VSC HCI passthrough*/
		if ((opcode & 0XFF00) == 0xFC00)
		{
			UINT8 idx;
			logd("Vendor specific command");

			for( idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
			{
				if(g_local_adapter.app_list[idx] && g_local_adapter.app_list[idx]->app_device_control_cb
					&& g_local_adapter.app_list[idx]->app_device_control_cb->iLE_vsc_cb)
				{
					g_local_adapter.app_list[idx]->app_device_control_cb->iLE_vsc_cb(INVALID_TRANS_ID,
						length, buf);
				}
			}

		}
		else
#endif /*TEST_CODE == TRUE*/
			logw("Unknown cmd cmpl event");
	}
}

static void hci_cmd_status_handler(UINT8* buffer, UINT8 len)
{
	UINT16 opcode;
	UINT8 status;
	UINT8 dummy_buffer[20];
#if (TEST_CODE == TRUE)
	/* Needed for VSC HCI passthrough*/
	UINT8 *buf = buffer - 2;
	UINT8 length = len + 2;
#endif
	JUMP_CUSTOM_LEN(buffer, 1);
	STREAM_TO_UINT8(status, buffer);
	STREAM_TO_UINT8(g_local_adapter.hci_data.hci_credit, buffer);
#if (SIMULTANEOUS_HCI_COMMANDS == FALSE)
	if (g_local_adapter.hci_data.hci_credit > 1)
		g_local_adapter.hci_data.hci_credit = 1; /* Even if controller gives more credit, use only one. */
#endif
	STREAM_TO_UINT16(opcode, buffer);
	if (g_local_adapter.hci_data.timer_active != TRUE)
	{
		loge("Critical error: Command status received (0x%04x) without stored command.", opcode);
		return;
	}
	if (g_local_adapter.hci_data.pending_opcode != opcode)
	{
		loge("ERROR: Unaligned Command Status Pkt! Something is terribly wrong");
		return;
	}

	if (g_local_adapter.hci_data.timer_active == TRUE)
	{
		osa_stop_timer(&(g_local_adapter.hci_data.hci_cmd_timer), HCI_CMD_TIMER, 0);
		g_local_adapter.hci_data.timer_active = FALSE;
	}
	logd(" status:%02x hci_credit:%02x opcode:%04x", status, g_local_adapter.hci_data.hci_credit, opcode);
	if (status == HCI_EVENT_STATUS_SUCCESS)
	{
		switch (opcode)
		{
		case HCI_CMD_LE_CREATE_CONN:
			osa_gap_handle_command_status(status);
			logd("Create connection process is going on.");
			break;
		//FIXME: Remove this
#if (TARGET_THREADX == TRUE)
		case HCI_CMD_VS_WRITE_BD_DATA:
			write_bddata_cmpl();
			break;
#endif
#if (TEST_CODE == TRUE)
	/* Needed for VSC HCI passthrough*/
		default:
		{
			if ((opcode & 0XFF00) == 0xFC00)
			{
				UINT8 idx;
				logd("Vendor specific command");
				for( idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
				{
					if(g_local_adapter.app_list[idx] && g_local_adapter.app_list[idx]->app_device_control_cb
						&& g_local_adapter.app_list[idx]->app_device_control_cb->iLE_vsc_cb)
					{
						g_local_adapter.app_list[idx]->app_device_control_cb->iLE_vsc_cb(INVALID_TRANS_ID,
							length, buf);
					}
				}
			}
			break;
		}
#endif
		}
	}
	else
	{
		switch (status)
		{
		case HCI_EVENT_STATUS_CONNECTION_LIMIT_EXCEEDED:
		{
			loge("Connection limit exceeded");
			memset(&dummy_buffer, 0, sizeof(dummy_buffer));
			dummy_buffer[0] = status;
			gap_handle_conn_complete(dummy_buffer, 0, FALSE);
			//TODO: Workaround for K0 FW?
			//hci_ble_cancel_create_ll_conn();
		}
			break;
		case HCI_EVENT_STATUS_CONTROLLER_BUSY:
		{
			loge("Controller busy");
			if (opcode == HCI_CMD_LE_CONN_UPDATE)
			{
				memset(&dummy_buffer, 0, sizeof(dummy_buffer));
				dummy_buffer[0] = status;
				gap_handle_conn_param_update_cmpl(dummy_buffer, sizeof(dummy_buffer));
			}
		}
			break;
		default:
			logw(" Command Failed. Status:%02x", status);
		}
	}
}

/**
 * Manages the HCI Data flow control.
 */
static void hci_num_cmpl_data_pkts_evt_cmpl(UINT8* buffer, UINT16 len)
{
	UINT8 num_of_handles;
	UINT16 num_of_pkts_sent, handle;
	UINT8 it;
	UINT8 conn_idx ;
	JUMP_CUSTOM_LEN(buffer, 1); /* Skip event length */
	STREAM_TO_UINT8(num_of_handles, buffer);
	for (it = 0; it < num_of_handles; it++)
	{
		STREAM_TO_UINT16(handle, buffer);
		STREAM_TO_UINT16(num_of_pkts_sent, buffer);
		g_local_adapter.data_window += num_of_pkts_sent;
		conn_idx = get_connected_device_idx_by_handle(handle);
		if (conn_idx != MAX_NUM_CONNECTED_DEVICE)
			g_local_adapter.connected_device[conn_idx]->num_un_acked_l2cap_pkts -= (UINT8) num_of_pkts_sent;
	}
	/* Check if anything we can send now */
	l2cap_data_send(MAX_NUM_CONNECTED_DEVICE, 0, NULL);
}

static void hci_process_evt(UINT8* buffer, UINT8 len)
{
	UINT8 event_code, ble_sub_code;
	UINT8 event_length;
	if (len < HCI_EVT_PREAMBLE_SIZE)
		return;
	STREAM_TO_UINT8(event_code, buffer);
	switch (event_code)
	{
	case HCI_EVENT_CMD_CMPL:
		hci_cmd_cmpl_handler(buffer, len);
		hci_send_cmd(0, NULL, 0);
		break;
	case HCI_EVENT_CMD_STATUS:
		hci_cmd_status_handler(buffer, len);
		hci_send_cmd(0, NULL, 0);
		break;
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	case HCI_EVENT_DISCON_CMPL:
		STREAM_TO_UINT8(event_length, buffer);
		gap_handle_disconn_complete(buffer, len);
		break;
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
	case HCI_EVENT_ENC_CHG:
#if (SMP_FEATURE)
		STREAM_TO_UINT8(event_length, buffer);
		smp_enc_chg_cback(buffer, event_length);
#endif /* SMP_FEATURE */
		break;
	case HCI_EVENT_KEY_REFRESH_COMPL:
#if (SMP_FEATURE)
		STREAM_TO_UINT8(event_length, buffer);
		smp_enc_chg_cback(buffer, event_length);
#endif /* SMP_FEATURE */
		break;
	case HCI_BLE_EVENT:
		STREAM_TO_UINT8(event_length, buffer);
		USE(event_length);
		STREAM_TO_UINT8(ble_sub_code, buffer);
		switch (ble_sub_code)
		{
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
		case HCI_BLE_ADV_PKT_RPT_EVT: /* result of inquiry */
			gap_handle_adv_report(buffer, event_length - 1, FALSE);
			break;
		case HCI_BLE_DIRECT_ADV_REPORT_EVT:
			gap_handle_adv_report(buffer, event_length - 1, TRUE);
			break;
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
		case HCI_BLE_CONN_COMPLETE_EVT:
			gap_handle_conn_complete(buffer, event_length - 1, FALSE);
			break;
		case HCI_BLE_LL_CONN_PARAM_UPD_EVT:
			gap_handle_conn_param_update_cmpl(buffer, event_length - 1);
			break;
#if (CONTROLLER_PRIVACY)
		case HCI_BLE_ENHANCED_CONN_COMPLETE_EVT:
			gap_handle_conn_complete(buffer, event_length - 1, TRUE);
			break;
#endif /* CONTROLLER_PRIVACY */
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
		case HCI_BLE_READ_REMOTE_FEAT_CMPL_EVT:
			gap_handle_conn_read_remote_feat_cmpl(buffer, event_length - 1);
			break;
		case HCI_BLE_REMOTE_CONN_PARAM_REQ:
			gap_handle_remote_conn_param_req(buffer, event_length - 1);
			break;
		case HCI_BLE_LTK_REQ_EVT: /* received only at slave device */
#if (SMP_FEATURE)
			smp_proc_ltk_req(buffer, event_length - 1);
#endif /* SMP_FEATURE */
			break;
		case HCI_BLE_READ_LOCAL_P256_PUBLIC_KEY_CMPL_EVT:
#if (CONTROLLER_ECDH)
			smp_proc_p256_public_key(buffer, event_length - 1);
#endif /* Controller_ECDH */
			break;
		case HCI_BLE_GENERATE_DHKEY_EVT:
#if (CONTROLLER_ECDH)
			smp_proc_dhkey(buffer, event_length - 1);
#endif /* CONTROLLER_ECDH */
			break;
		case HCI_BLE_DATA_LEN_CHANGE_EVT:
			gap_handle_data_len_change_evt(buffer, event_length - 1);
			break;
		}
		break;
	case HCI_HARDWARE_ERROR:
			loge("Received Hardware Error code 0x%x", buffer[1]);
			break;
	case HCI_NUM_COMPL_DATA_PKTS_EVT:
		hci_num_cmpl_data_pkts_evt_cmpl(buffer, len);
		break;
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
#if (LE_PING_ENABLE == TRUE)
	case HCI_AUTH_PAYLOAD_TIMEOUT_EXP_EVT:
		gap_handle_authpayload_timeout_exp_evt(buffer, len);
		break;
#endif /*LE_PING_ENABLE == TRUE */
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
	default:
		break;
	}
}

INT8 hci_recv_buffer(UINT8* buffer, UINT16 len)
{
	UINT8 type;
#if (PARANOID_STACK == TRUE)
	if (buffer == NULL || len < UART_HDR_SIZE)
		return STATUS_ERR_INVALID_PARAM;
#endif
	STREAM_TO_UINT8(type, buffer);
	switch (type)
	{
	case HCI_EVT:
#if (BTSNOOPDISP_INCLUDED == TRUE)
		btsnoop_hci_evt(buffer);
#endif
		hci_process_evt(buffer, (UINT8)len - UART_HDR_SIZE);
		break;
	case HCI_ACL:
	{
		UINT16 acl_handle;
		UINT8 pb_flag;
		UINT8 connected_device_list_idx;
		UINT16 buffer_length;
		connected_device_t *device;
#if (BTSNOOPDISP_INCLUDED == TRUE)
		btsnoop_acl_data(buffer, TRUE);
#endif
		if (len < (UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE))
		{
			loge("Invalid ACL buffer length: %d", len);
			return STATUS_SUCCESS;
		}
		STREAM_TO_UINT16(acl_handle, buffer);
		pb_flag = (acl_handle >> 12) & 0x03;
		acl_handle = acl_handle & 0x0FFF;
		logd("ACL Data: acl handle:0x%02x pb_flag:0x%x", acl_handle, pb_flag);
		/* Find the device from the acl handle */
		connected_device_list_idx = get_connected_device_idx_by_handle(acl_handle);
		if (connected_device_list_idx == MAX_NUM_CONNECTED_DEVICE)
		{
			loge("Unknown acl handle. handle:0x%02x", acl_handle);
			return STATUS_SUCCESS;
		}
		STREAM_TO_UINT16(buffer_length, buffer);
		if ((buffer_length + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE) != len)
		{
			loge("Received ACL buffer length 0x%02x does not match actual packet length 0x%02x", len, buffer_length + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE);
			return STATUS_SUCCESS;
		}
		device = g_local_adapter.connected_device[connected_device_list_idx];
		l2cap_recv_data(device, pb_flag, buffer, buffer_length);
	}
		break;
#if (TARGET_THREADX == TRUE)
	case HCI_CMD:
	{
		profile_command_recvd(buffer, len - UART_HDR_SIZE);
	}
		break;
#endif
	default:
		loge("Unknown type. Drop.");
	}
	return STATUS_SUCCESS;
}

static void hci_cmd_timeout_handler(osa_timer_arg_t arg)
{
	logi("");
	loge("CMD TIMEOUT opcode:0x%04x", g_local_adapter.hci_data.pending_opcode);
	if(g_local_adapter.hci_data.timer_active == TRUE)
		g_local_adapter.hci_data.timer_active = FALSE;
	g_local_adapter.hci_data.hci_credit++;
#if (SIMULTANEOUS_HCI_COMMANDS == FALSE)
	if (g_local_adapter.hci_data.hci_credit > 1)
		g_local_adapter.hci_data.hci_credit = 1; /* Even if controller gives more credit, use only one. */
#endif
	hci_send_cmd(0, NULL, 0);
}

static void hci_cmd_timeout_cb(osa_timer_arg_t arg)
{
	timer_expire_evt_msg(hci_cmd_timeout_handler, arg);
}

/**
 * This function is called from hcicmds.c file functions to send hci command
 *
 * opcode: opcode of the command to be sent (ocf + ogf)
 * p_buf: pointer to the buffer to be sent
 * len: length of the buffer (includes hci payload length [cmd length])
 *
 * Total buffer length to be sent is : len + uart header length + hci preamble length
 *
 * 	---------------------------------------------------------------------------
 * 	| UART HDR(left blank here) | HCI PREAMBLE(in p_buf) | HCI PAYLOAD (p_buf)|
 * 	---------------------------------------------------------------------------
 * 													     |<------ len-------->|
 */
INT8 hci_send_cmd(UINT16 opcode, UINT8* p_buf, UINT8 len)
{
	INT8 ret = STATUS_SUCCESS;
	if(p_buf)
		enqueue(&hci_cmd_tx_q, (void*)p_buf);
	if(g_local_adapter.hci_data.hci_credit > 0)
	{
		p_buf = (UINT8*)dequeue(&hci_cmd_tx_q);
		if(p_buf)
		{
			UINT8 *p = p_buf;
			JUMP_UART_HEADER(p);
			STREAM_TO_UINT16(opcode, p);
			STREAM_TO_UINT8(len, p);
			if ((ret = hci_send_msg(HCI_CMD, p_buf, len + UART_HDR_SIZE + HCI_CMD_PREAMBLE_SIZE)) == STATUS_SUCCESS)
			{
				g_local_adapter.hci_data.hci_credit--;
				if(g_local_adapter.hci_data.timer_active == TRUE)
					loge("Previous hci cmd timer still active!!!");
				g_local_adapter.hci_data.pending_opcode = opcode;
				osa_start_timer(&(g_local_adapter.hci_data.hci_cmd_timer), HCI_CMD_TIMER, HCI_CMD_TIMEOUT, hci_cmd_timeout_cb, 0);
				g_local_adapter.hci_data.timer_active = TRUE;

#if (TARGET_UEFI == TRUE)
				// synchronously receive the event when is_sync_event is set
				if(g_local_adapter.is_sync_event)
				{
					UINT8 *buffer = (UINT8*)alloc(HCI_CMD_EVT_MAX_SIZE);
					if (buffer)
					{
						logd("Waiting for sync event");

						tl_recv_msg(buffer);
						dealloc(buffer);
					}
				}
#endif
			}
#if (TARGET_THREADX_RW != TRUE)
			dealloc_queue_element(p_buf);
#endif

		}
	}
	return ret;
}

/**
 *	@brief This function is called from the L2CAP layer to send a L2CAP frame
 *
 *	acl_handle: denotes to which link the packet has to be sent
 *	buffer: pointer to the data buffer to send
 *	len: length of the l2cap payload. Add L2CAP header size for HCI ACL pkt length
 *
 *	Total buffer length to be sent is : len + uart header length + acl preamble length
 *
 * 	-------------------------------------------------------------------------------------
 * 	| UART HDR(left blank here) | HCI PREAMBLE(acl hdl, flags, len) | HCI PAYLOAD (p_buf)|
 * 	-------------------------------------------------------------------------------------
 * 													                |<------ len-------->|
 *
 */
INT8 hci_send_data(connected_device_t *device, UINT8 pb_flag, UINT8* data_buffer, UINT16 data_length)
{
	UINT16 hci_data_len;
	UINT16 acl_handle;
	buffer_t *data_pkt;
	UINT8 *p_buf;
	UINT8 *p;
	INT8 ret;
#if (PARANOID_STACK == TRUE)
	if (!device)
		return STATUS_ERR_INVALID_PARAM;
	if (device->acl_handle > 0xEFF) /* ACL handlel range 0 - 0xeff */
		return STATUS_ERR_INAVALID_CONNENCTION;
#endif
	hci_data_len = data_length + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	acl_handle = (pb_flag == L2CAP_PB_FLAG_CONTINUOUS_PKT) ? (device->acl_handle & 0xCFFF) | 0x1000 : device->acl_handle;

	data_pkt = (buffer_t*)(void*)data_buffer;
#if (PARANOID_STACK == TRUE)
	if (!data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	p_buf = NULL;
	p = &data_pkt->data[data_pkt->offset];

#if (TARGET_THREADX_RW == TRUE)
	p_buf = (UINT8*)alloc_queue_element(hci_data_len, HCI_ALLOC);
#if (PARANOID_STACK == TRUE)
		if (!p_buf)
			return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	memcpy(p_buf + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE, p, data_length);
	p = p_buf;
#elif (TARGET_THREADX_RW != TRUE)
	p = p -(UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE);
	p_buf = p;
#endif
	UINT8_TO_STREAM(p_buf, HCI_ACL);
	UINT16_TO_STREAM(p_buf, acl_handle);
	UINT16_TO_STREAM(p_buf, data_length);
#if (BTSNOOPDISP_INCLUDED == TRUE)
	btsnoop_acl_data(p + UART_HDR_SIZE, FALSE);
#endif
	ret = tl_write(p, hci_data_len);
	return ret;
}

/***********************************************
 * Function  : hci_send_msg
 * Description: Sends hci pkt to userial_write
 ***********************************************/
static INT8 hci_send_msg(UINT8 type, UINT8* msg, UINT16 len)
{
	UINT8* buf;
#if (PARANOID_STACK == TRUE)
	if (!msg)
		return STATUS_ERR_INVALID_PARAM;
#endif

	buf = (UINT8*) msg;
	buf[0] = type;
#if (BTSNOOPDISP_INCLUDED == TRUE)
	btsnoop_hci_cmd(buf + UART_HDR_SIZE);
#endif
	return tl_write(buf, len);
}

INT8 hci_host_init(char* device, int ispeed)
{
	init_no_guard_q(&hci_cmd_tx_q);
	g_local_adapter.hci_data.hci_credit = 1;

#if (TARGET_UEFI == TRUE)
	if (tl_init(device, ispeed) != STATUS_SUCCESS)
#else
	if (tl_init(device, ispeed) == -1)
#endif
	{
		logex("Cannot open ttyport %s", device);
		/* Cannot do anything */
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	logd("tty port open success");
	if (osa_create_timer(&(g_local_adapter.hci_data.hci_cmd_timer), HCI_CMD_TIMER, HCI_CMD_TIMER_ISR, sizeof(HCI_CMD_TIMER)/sizeof(osa_timer_static_t), hci_cmd_timeout_cb, 0) != 0)
	{
		logex("Hci command timer creating failed");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	return STATUS_SUCCESS;
}

void hci_init_on_wakeup()
{
	init_no_guard_q(&hci_cmd_tx_q);
}

void hci_cleanup(void)
{
	logi("");
	osa_delete_timer(&(g_local_adapter.hci_data.hci_cmd_timer), HCI_CMD_TIMER);
	cleanup_q(&hci_cmd_tx_q);
	tl_close();
}
