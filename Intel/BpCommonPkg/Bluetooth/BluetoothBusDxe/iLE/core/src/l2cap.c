/** @file
  L2CAP protocol implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "device_struct.h"
#include "hci_host.h"
#include "gap.h"
#include "att.h"
#include "smp.h"
#include "config_host.h"
#include "l2cap.h"
#include "interface.h"

#define MODULE_DBG_LVL L2CAP_DBG_LVL

#include "log.h"

/* Each l2cap action function should be in this form */
typedef INT8 (*l2cap_act_t)(connected_device_t *device, UINT8* d);
typedef INT8 (*l2cap_coc_act_t)(connected_device_t *device, UINT8 ccb_idx, UINT8* d);


/****************************************************************
 * 							L2CAP Actions
 ***************************************************************/
static INT8 l2cap_act_send_data(connected_device_t *device, UINT8* d);
static INT8 l2cap_act_recv_data(connected_device_t *device, UINT8* d);
static INT8 l2cap_act_init_connect_param_update(connected_device_t *device,
		UINT8* d);
static INT8 l2cap_act_connect_param_update_done(connected_device_t *device,
		UINT8* d);
#if (L2CAP_COC == TRUE)
/* lc_act_ - stands for L2CAP CoC*/
/* Below are the event handlers or action functions to handle events */

/* L2CAP CoC connect request send to a peer device */
static INT8 lc_act_send_connect_req(connected_device_t *device, UINT8 ccb_idx, UINT8* d);
/* L2CAP CoC receive connect from a peer device, for earlier sent connect request */
static INT8 lc_act_recv_connect_res(connected_device_t *device, UINT8 ccb_idx, UINT8* d);
/* L2CAP CoC connect request for a PSM received from a peer device */
static INT8 lc_act_recv_connect_req(connected_device_t *device, UINT8 ccb_idx, UINT8* d);

/* L2CAP CoC disconnect request send to a peer device */
static INT8 lc_act_send_disconnect_req(connected_device_t *device, UINT8 ccb_idx, UINT8* d);
/* L2CAP CoC receive disconnect response from peer device, for earlier sent disconnect request */
static INT8 lc_act_recv_disconnect_res(connected_device_t *device, UINT8 ccb_idx, UINT8* d);
/* L2CAP CoC receive disconnect request from peer device */
static INT8 lc_act_recv_disconnect_req(connected_device_t *device, UINT8 ccb_idx, UINT8* d);

/* L2CAP CoC send data request to peer CoC connected device, irrespective of direction of connection */
static INT8 lc_act_send_data(connected_device_t *device, UINT8 ccb_idx, UINT8* d);
/* L2CAP CoC receive data request from peer CoC connected device, irrespective of direction of connection */
static INT8 lc_act_recv_data(connected_device_t *device, UINT8 ccb_idx, UINT8* d);
/* L2CAP CoC send flow control credits to peer CoC connected device, irrespective of direction of connection */
static INT8 lc_act_send_fc_credit(connected_device_t *device, UINT8 ccb_idx, UINT8* d);
/* L2CAP CoC receive flow control credits from peer CoC connected device, irrespective of direction of connection */
static INT8 lc_act_recv_fc_credit(connected_device_t *device, UINT8 ccb_idx, UINT8* d);
#endif // L2CAP_COC

/****************************************************************
 *					L2CAP Other static functions
 ***************************************************************/
static INT8 l2cap_send_command_reject(connected_device_t *device, UINT8 id,
		UINT16 reason);
static INT8 l2cap_signal_pkt_handler(connected_device_t *device,
		UINT8* buffer, UINT16 buffer_length);
#if(GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
static INT8 l2cap_send_command_conn_param_update_res(
		connected_device_t *device, UINT8 id, UINT16 result);
#endif

#if (L2CAP_COC == TRUE)
/* Below are the support functions for CoC */
static INT8 coc_enqueue_data_pkt(connected_device_t *device, UINT8 handle, l2cap_coc_conn_send_data_t *data_pkt);
static INT8 coc_pick_from_queue_to_send_data(connected_device_t *device, UINT8 handle);
static INT8 coc_segment_and_send_mtu_data(connected_device_t *device, UINT8* buffer, UINT16 len, UINT16 r_mps, UINT16 cid);

void l2cap_coc_connect_cb(connected_device_t *device, BOOLEAN result, UINT16 cidx);
static void remove_all_pending_l2cap_pkt(void *queue, UINT16 cid);
#endif // L2CAP_COC

/****************************************************************
 *					L2CAP TX Queue For Each Device
****************************************************************/
RETENTION_SECTION_START
static queue_internal_t l2cap_tx_q[MAX_NUM_CONNECTED_DEVICE];
RETENTION_SECTION_END

/****************************************************************
 * 						L2CAP Action Table
 ***************************************************************/
const l2cap_act_t l2cap_act[] =
{ l2cap_act_send_data, l2cap_act_recv_data, l2cap_act_init_connect_param_update,
		l2cap_act_connect_param_update_done,
	};

/****************************************************************
 * 						L2CAP State Tables
 ***************************************************************/
/* Format: <Action> <Next state> */
const UINT8 l2cap_state_closed_hdl_table[][2] =
{
/* L2CAP_EVT_SEND_DATA */
{ IGNORE, IGNORE },
/* L2CAP_EVT_RECV_DATA */
{ IGNORE, IGNORE },
/* L2CAP_EVT_INIT_CONNECT_PARAM_UPDATE */
{ IGNORE, IGNORE },
/* L2CAP_EVT_CONNECT_PARAM_UPDATE_DONE */
{ IGNORE, IGNORE },
		/* L2CAP_EVT_LINK_CONNECTED */
		{ IGNORE, L2CAP_STATE_OPEN },
		/* L2CAP_EVT_LINK_DISCONNECTED */
		{ IGNORE, IGNORE }
		};

const UINT8 l2cap_state_open_hdl_table[][2] =
{
/* L2CAP_EVT_SEND_DATA */
{ L2CAP_ACT_SEND_DATA, L2CAP_STATE_OPEN },
/* L2CAP_EVT_RECV_DATA */
{ L2CAP_ACT_RECV_DATA, L2CAP_STATE_OPEN },
/* L2CAP_EVT_INIT_CONNECT_PARAM_UPDATE */
{ L2CAP_ACT_INIT_CONNECT_PARAM_UPDATE, L2CAP_STATE_CONN_PARAM_UPDATE_CONTINUE },
/* L2CAP_EVT_CONNECT_PARAM_UPDATE_DONE */
{ L2CAP_ACT_CONNECT_PARAM_UPDATE_DONE, L2CAP_STATE_OPEN },
		/* L2CAP_EVT_LINK_CONNECTED */
		{ IGNORE, IGNORE },
		/* L2CAP_EVT_LINK_DISCONNECTED */
		{ IGNORE, L2CAP_STATE_CLOSED }
		};

const UINT8 l2cap_state_conn_param_update_continue_hdl_table[][2] =
{
/* L2CAP_EVT_SEND_DATA */
{ L2CAP_EVT_SEND_DATA, IGNORE },
/* L2CAP_EVT_RECV_DATA */
{ L2CAP_EVT_RECV_DATA, IGNORE },
/* L2CAP_EVT_INIT_CONNECT_PARAM_UPDATE */
{ IGNORE, IGNORE },
/* L2CAP_EVT_CONNECT_PARAM_UPDATE_DONE */
{ L2CAP_ACT_CONNECT_PARAM_UPDATE_DONE, L2CAP_STATE_OPEN },
		/* L2CAP_EVT_LINK_CONNECTED */
		{ IGNORE, IGNORE },
		/* L2CAP_EVT_LINK_DISCONNECTED */
		{ IGNORE, L2CAP_STATE_CLOSED }
		};

typedef const UINT8 (*state_table_ref_t)[2];
const state_table_ref_t state_table_handler_table[] =
{
		l2cap_state_closed_hdl_table,
		l2cap_state_open_hdl_table,
		l2cap_state_conn_param_update_continue_hdl_table
	};

static INT8 l2cap_csm_handler(UINT8 event, connected_device_t *device,
		UINT8* data)
{
	INT8 ret = STATUS_ERR_UNKNOWN;
	state_table_ref_t state_table;
#if (PARANOID_STACK == TRUE)
	if (device == NULL )
		return STATUS_ERR_INVALID_PARAM;
#endif
	state_table =
			state_table_handler_table[device->l2cap_state];
#if (PARANOID_STACK == TRUE)
	if (state_table == NULL )
	{
		loge("Fatal Error. Couldn't find appropriate state table.");
		return STATUS_ERR_LAYER_SPECIFIC;
	}
#endif
	if (state_table[event][0] != IGNORE)
		ret = (l2cap_act[state_table[event][0]])(device, data);
	if (state_table[event][1] != IGNORE)
		device->l2cap_state = state_table[event][1];
	return ret;
}

#if (L2CAP_COC == TRUE)
static INT8 lc_act_send_connect_req(connected_device_t *device, UINT8 ccb_idx, UINT8* d)
{
	l2cap_coc_conn_t* l2cap_coc_channel_tbl;
	buffer_t *data_pkt ;
	UINT8 *p_buf;
	INT8 ret;
	logi("");
	// Send connect request to remote device
#if (PARANOID_STACK == TRUE)
	if (!device)
		return STATUS_ERR_INAVALID_CONNENCTION;
#endif
	l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(l2cap_coc_channel_tbl->state != LCS_CLOSED)
	{
		loge("L2cap coc is not is correct state to handle the request");
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
	l2cap_coc_channel_tbl->mps = L2CAP_COC_MPS;
	l2cap_coc_channel_tbl->credits = L2CAP_COC_INITIAL_CREDITS;
	l2cap_coc_channel_tbl->cid = ccb_idx + L2CAP_COC_START_CID;

	data_pkt = (buffer_t*) get_l2cap_free_buffer(L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_CONNECT_REQ_LEN);
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	device->l2cap_cur_id = increament_l2cap_identifier(device->l2cap_cur_id);
	l2cap_coc_channel_tbl->l2cap_identifier = device->l2cap_cur_id;
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_CONNECT_REQ_LEN;
	p_buf = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(p_buf, L2CAP_COC_COMMAND_CONNECT_REQ);
	UINT8_TO_STREAM(p_buf, device->l2cap_cur_id);
	UINT16_TO_STREAM(p_buf, L2CAP_COC_COMMAND_CONNECT_REQ_LEN);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->psm);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->cid);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->mtu);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->mps);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->credits);

	ret = l2cap_data_send(device->idx, L2CAP_LE_SIGNAL_CID, data_pkt);
	if(ret != STATUS_SUCCESS)
	{
		logw("L2cap COC connection failed for psm[%u]", l2cap_coc_channel_tbl->psm);
		delete_l2cap_coc_tbl(ccb_idx);
	}
	else
	{
		l2cap_coc_channel_tbl->state = LCS_W4_CONNECT_RES;
	}
	return ret;
}

static INT8 lc_act_recv_connect_res(connected_device_t *device, UINT8 ccb_idx, UINT8* d)
{
	l2cap_coc_conn_t* l2cap_coc_channel_tbl;
	logi("");
	// Recv connect response from remote device
#if (PARANOID_STACK == TRUE)
	if (!device) return STATUS_ERR_INAVALID_CONNENCTION;
#endif
	UINT8 result;
	l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(l2cap_coc_channel_tbl->state != LCS_W4_CONNECT_RES)
	{
		loge("L2cap coc is not is correct state to handle the request");
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
	STREAM_TO_UINT16(l2cap_coc_channel_tbl->r_cid, d);
	STREAM_TO_UINT16(l2cap_coc_channel_tbl->r_mtu, d);
	STREAM_TO_UINT16(l2cap_coc_channel_tbl->r_mps, d);
	STREAM_TO_UINT16(l2cap_coc_channel_tbl->r_credits, d);
	STREAM_TO_UINT16(result, d);

	//check the max MTU that stack can support and reassign remote MTU accordingly
	if(l2cap_coc_channel_tbl->r_mtu > L2CAP_COC_MAX_MTU)
		l2cap_coc_channel_tbl->r_mtu = L2CAP_COC_MAX_MTU;

	if(l2cap_coc_channel_tbl->l2cap_coc_cb && l2cap_coc_channel_tbl->l2cap_coc_cb->connection_cmpl_cb)
	{
		l2cap_coc_channel_tbl->l2cap_coc_cb->connection_cmpl_cb(l2cap_coc_channel_tbl->owner_trans_id,
				device->idx, l2cap_coc_channel_tbl->psm, ccb_idx, l2cap_coc_channel_tbl->r_mtu, MAX_NUMBER_OF_L2CAP_COC_TX_BUFFER, result);
	}
	if(result != STATUS_SUCCESS)
	{
		logw("L2cap COC connection failed for CID[%u]",l2cap_coc_channel_tbl->cid);
		delete_l2cap_coc_tbl(ccb_idx);
		return result;
	}
	else
	{
		// For creating L2CAP Channel control block
		l2cap_coc_connect_cb(device, TRUE, l2cap_coc_channel_tbl->cid);

		l2cap_coc_channel_tbl->state = LCS_OPEN;
	}

	return STATUS_SUCCESS;
}

static INT8 lc_act_recv_connect_req(connected_device_t *device, UINT8 ccb_idx, UINT8* d)
{
	l2cap_coc_conn_t* l2cap_coc_channel_tbl;
	buffer_t *data_pkt;
	UINT8 *p_buf;
	INT8 ret;
	logi("");
	// Callback the connection receiving App's registered function.
	// App should register callback before the remote device initiates CoC conn req.
#if (PARANOID_STACK == TRUE)
	if (!device)
	  return STATUS_ERR_INAVALID_CONNENCTION;
#endif

	l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(l2cap_coc_channel_tbl->state != LCS_CLOSED)
	{
		loge("L2cap coc is not is correct state to handle the request");
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
	data_pkt = (buffer_t*) get_l2cap_free_buffer(L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_CONNECT_RES_LEN);
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_CONNECT_RES_LEN;
	p_buf = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(p_buf, L2CAP_COC_COMMAND_CONNECT_RES);
	UINT8_TO_STREAM(p_buf, device->l2cap_cur_id); // Use the same l2cap_cur_id sent by remote for the connect response.
	UINT16_TO_STREAM(p_buf, L2CAP_COC_COMMAND_CONNECT_RES_LEN);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->cid);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->mtu);
	UINT16_TO_STREAM(p_buf,	l2cap_coc_channel_tbl->mps);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->credits);
	UINT16_TO_STREAM(p_buf, L2CAP_COC_RESPONSE_CONNECTION_SUCCESSFUL);

	ret = l2cap_data_send(device->idx, L2CAP_LE_SIGNAL_CID, data_pkt);
	if(ret != STATUS_SUCCESS)
	{
		delete_l2cap_coc_tbl(ccb_idx);
		return ret;
	}

	// In order to set the l2cap_chan_ctrl_block
	l2cap_coc_connect_cb(device, TRUE, l2cap_coc_channel_tbl->cid);

	l2cap_coc_channel_tbl->state = LCS_OPEN;

	if(l2cap_coc_channel_tbl->l2cap_coc_cb && l2cap_coc_channel_tbl->l2cap_coc_cb->connection_cmpl_cb)
	{
		l2cap_coc_channel_tbl->l2cap_coc_cb->connection_cmpl_cb(l2cap_coc_channel_tbl->owner_trans_id,
				device->idx, l2cap_coc_channel_tbl->psm, ccb_idx, l2cap_coc_channel_tbl->r_mtu, MAX_NUMBER_OF_L2CAP_COC_TX_BUFFER, STATUS_SUCCESS);
	}
	return STATUS_SUCCESS;
}

static INT8 lc_act_send_disconnect_req(connected_device_t *device, UINT8 ccb_idx, UINT8* d)
{
	l2cap_coc_conn_t* l2cap_coc_channel_tbl;
	buffer_t *data_pkt;
	UINT8 *p_buf;
	INT8 ret;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!device)
	  return STATUS_ERR_INAVALID_CONNENCTION;
#endif

	l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(l2cap_coc_channel_tbl->state != LCS_OPEN &&
			l2cap_coc_channel_tbl->state != LCS_W4_CONNECT_RES)
	{
		loge("L2cap coc is not is correct state to handle the request");
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
	// Send disconnect request to remote device
	data_pkt = (buffer_t*) get_l2cap_free_buffer(L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_DISCONNECT_REQ_LEN);
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	device->l2cap_cur_id = increament_l2cap_identifier(device->l2cap_cur_id);
	l2cap_coc_channel_tbl->l2cap_identifier = device->l2cap_cur_id;
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_DISCONNECT_REQ_LEN;
	p_buf = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(p_buf, L2CAP_COC_COMMAND_DISCONNECT_REQ); //LE CREDIT BASED DISCONNECTION REQUEST (CODE 0x06)
	UINT8_TO_STREAM(p_buf, device->l2cap_cur_id);
	UINT16_TO_STREAM(p_buf, L2CAP_COC_COMMAND_DISCONNECT_REQ_LEN);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->r_cid);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->cid);
	ret = l2cap_data_send(device->idx, L2CAP_LE_SIGNAL_CID, data_pkt);
	if(ret == STATUS_SUCCESS)
		l2cap_coc_channel_tbl->state = LCS_W4_DISCONNECT_RES;
	return ret;
}

static INT8 lc_act_recv_disconnect_res(connected_device_t *device, UINT8 ccb_idx, UINT8* d)
{
	l2cap_coc_conn_t* l2cap_coc_channel_tbl;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!device)
	  return STATUS_ERR_INAVALID_CONNENCTION;
#endif

	l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(l2cap_coc_channel_tbl->state != LCS_W4_DISCONNECT_RES)
	{
		loge("L2cap coc is not is correct state to handle the request");
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
	if(l2cap_coc_channel_tbl->l2cap_coc_cb && l2cap_coc_channel_tbl->l2cap_coc_cb->disconnect_cmpl_cb)
	{
		l2cap_coc_channel_tbl->l2cap_coc_cb->disconnect_cmpl_cb(l2cap_coc_channel_tbl->owner_trans_id, device->idx, ccb_idx, STATUS_SUCCESS);
	}
	remove_all_pending_l2cap_pkt(&l2cap_tx_q[device->idx], l2cap_coc_channel_tbl->r_cid);

	delete_l2cap_coc_tbl(ccb_idx);

	return STATUS_SUCCESS;
}

static INT8 lc_act_recv_disconnect_req(connected_device_t *device, UINT8 ccb_idx, UINT8* d)
{
	l2cap_coc_conn_t* l2cap_coc_channel_tbl;
	buffer_t *data_pkt ;
	UINT8 *p_buf;
	INT8 ret;
	
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!device)
	  return STATUS_ERR_INAVALID_CONNENCTION;
#endif

	l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(l2cap_coc_channel_tbl->state != LCS_OPEN)
	{
		loge("L2cap coc is not is correct state to handle the request");
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
	data_pkt = (buffer_t*) get_l2cap_free_buffer(L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_DISCONNECT_RES_LEN);
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_DISCONNECT_RES_LEN;
	p_buf = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(p_buf, L2CAP_COC_COMMAND_DISCONNECT_RES); //DISCONNECTION RESPONSE (CODE 0x07)
	UINT8_TO_STREAM(p_buf, device->l2cap_cur_id); // Use the same l2cap_cur_id sent by remote for the connect response.
	UINT16_TO_STREAM(p_buf, L2CAP_COC_COMMAND_DISCONNECT_RES_LEN);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->cid);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->r_cid);
	ret = l2cap_data_send(device->idx, L2CAP_LE_SIGNAL_CID, data_pkt);
	if(ret!=STATUS_SUCCESS)
		return ret;
	if(l2cap_coc_channel_tbl->l2cap_coc_cb && l2cap_coc_channel_tbl->l2cap_coc_cb->disconnect_cmpl_cb)
	{
		l2cap_coc_channel_tbl->l2cap_coc_cb->disconnect_cmpl_cb(l2cap_coc_channel_tbl->owner_trans_id, device->idx, ccb_idx, STATUS_SUCCESS);
	}
	remove_all_pending_l2cap_pkt(&l2cap_tx_q[device->idx], l2cap_coc_channel_tbl->r_cid);

	delete_l2cap_coc_tbl(ccb_idx);

	return STATUS_SUCCESS;
}

static INT8 lc_act_send_data(connected_device_t *device, UINT8 ccb_idx, UINT8* d)
{
	l2cap_coc_conn_t* l2cap_coc_channel_tbl;
	l2cap_coc_conn_send_data_t *data_pkt ;
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!device)
	  return STATUS_ERR_INAVALID_CONNENCTION;
#endif

	l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(l2cap_coc_channel_tbl->state != LCS_OPEN)
	{
		loge("L2cap coc is not is correct state to handle the request");
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
	data_pkt = (l2cap_coc_conn_send_data_t *)(void*)d;
	if(!coc_enqueue_data_pkt(device, ccb_idx, data_pkt))
		coc_pick_from_queue_to_send_data(device, ccb_idx);
	else
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	return STATUS_SUCCESS;
}

static INT8 coc_enqueue_data_pkt(connected_device_t *device, UINT8 ccb_idx, l2cap_coc_conn_send_data_t *data_pkt)
{
	l2cap_coc_conn_t* l2cap_coc_channel_tbl;
	INT8 ret;
	logi("");
	l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	ret = enqueue(&l2cap_coc_channel_tbl->coc_data_tx_q, (void*)data_pkt);
	return ret;
}

static INT8 coc_pick_from_queue_to_send_data(connected_device_t *device, UINT8 ccb_idx)
{
	l2cap_coc_conn_t* l2cap_coc_channel_tbl;
	l2cap_coc_conn_send_data_t* data_pkt;
	
	logi("");
	l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	data_pkt = (l2cap_coc_conn_send_data_t*) pick_front(&l2cap_coc_channel_tbl->coc_data_tx_q);
	if(!data_pkt)
		return STATUS_SUCCESS;

	do
	{
		UINT16 total_len = data_pkt->length;
		UINT16 sent_len = data_pkt->offset;
		UINT8 *cur_buf_ptr = (data_pkt->data) + sent_len;
		INT8 ret = STATUS_SUCCESS;

		if((sent_len < total_len) && ((l2cap_coc_channel_tbl->r_credits) > 0))
		{
			UINT16 avl_rmt_space = ((l2cap_coc_channel_tbl->r_credits)*(l2cap_coc_channel_tbl->r_mps));
			UINT16 send_len = ((total_len-sent_len) < avl_rmt_space) ? (total_len-sent_len) : avl_rmt_space;

			ret = coc_segment_and_send_mtu_data(device, cur_buf_ptr, send_len, l2cap_coc_channel_tbl->r_mps, l2cap_coc_channel_tbl->cid);

			if(ret > 0)
			{
				sent_len += ret;
				cur_buf_ptr += ret;
				data_pkt->offset = sent_len;
				UINT16 decr_credits = (ret<(l2cap_coc_channel_tbl->r_mps))?1:
					(UINT16)(ret/(l2cap_coc_channel_tbl->r_mps));
				if((ret > (l2cap_coc_channel_tbl->r_mps)) && ret % (l2cap_coc_channel_tbl->r_mps) > 0)
					decr_credits++;
				(l2cap_coc_channel_tbl->r_credits) -= decr_credits;
			}
			else
				return ret;
		}

		if(sent_len == total_len)
		{
			dequeue(&l2cap_coc_channel_tbl->coc_data_tx_q);
			dealloc_queue_element(data_pkt);
			data_pkt = NULL;
			l2cap_coc_channel_tbl->tx_usage_count--;

			if(l2cap_coc_channel_tbl->l2cap_coc_cb && l2cap_coc_channel_tbl->l2cap_coc_cb->flow_control_cb)
			{
				l2cap_coc_channel_tbl->l2cap_coc_cb->flow_control_cb(l2cap_coc_channel_tbl->owner_trans_id, device->idx, ccb_idx, 1);
			}

			if((l2cap_coc_channel_tbl->r_credits) > 0)
			{
				data_pkt = (l2cap_coc_conn_send_data_t*) pick_front(&l2cap_coc_channel_tbl->coc_data_tx_q);
				if(!data_pkt)
					return STATUS_SUCCESS;
			}
		}
		else if((l2cap_coc_channel_tbl->r_credits) == 0)
		{
			data_pkt->offset = sent_len;
			data_pkt = NULL;
		}
	}while(data_pkt);
	return STATUS_SUCCESS;
}

static INT8 coc_segment_and_send_mtu_data(connected_device_t *device, UINT8* buffer, UINT16 len, UINT16 r_mps, UINT16 cid)
{

	UINT16 send_total_len=0;
	UINT8 *c_buf_ptr = buffer;
	UINT8 *e_buf_ptr = buffer + len;
	logi("");
	while(c_buf_ptr < e_buf_ptr)
	{
		UINT16 send_len = (e_buf_ptr - c_buf_ptr >= r_mps) ? r_mps : e_buf_ptr - c_buf_ptr;
		send_total_len += send_len;
		buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(send_len);
		if(NULL == data_pkt)
		{
			logd("L2cap packet unavailable");
			return STATUS_ERR_INSUFFICIENT_RESOURCES;
		}
		data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
		data_pkt->length = send_len;
		UINT8 *p_buf = &data_pkt->data[data_pkt->offset];
		memcpy(p_buf, c_buf_ptr, send_len);
		INT8 ret = l2cap_data_send(device->idx, cid, data_pkt);
		USE(ret);
		c_buf_ptr += send_len;
	}
	return send_total_len;
}

static INT8 lc_act_recv_data(connected_device_t *device, UINT8 ccb_idx, UINT8* d)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!device)
	  return STATUS_ERR_INAVALID_CONNENCTION;
#endif
	l2cap_coc_conn_t* l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(l2cap_coc_channel_tbl->state != LCS_OPEN)
	{
		loge("L2cap coc is not is correct state to handle the request");
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
	UINT8 handle=0;
	UINT16 sdu_len;
	l2cap_data_t *data_pkt = (l2cap_data_t *)(void*)d;
	handle=data_pkt->handle;
	l2cap_coc_conn_recv_data_t* recv_data_info = &(l2cap_coc_channel_tbl->coc_recv_data_pool);

	if((recv_data_info->flag_pkt_type == L2CAP_COC_FLAG_FIRST_PKT) && (data_pkt->length > sizeof(sdu_len)))
	{
		STREAM_TO_UINT16(sdu_len, data_pkt->data);
		logd("SDU = %d", sdu_len);

		if(sdu_len > l2cap_coc_channel_tbl->mtu)
		{
			logw("Recieved data with MTU(%u) is note than the registed MTU(%u), so disconnection the channel(%u)", sdu_len, l2cap_coc_channel_tbl->mtu, l2cap_coc_channel_tbl->cid);
			l2cap_coc_disconnect_req(l2cap_coc_channel_tbl->owner_trans_id, device, handle);
			return STATUS_ERR_INVALID_PARAM;
		}

		logd("Data received = %d bytes", data_pkt->length-2);
		hex_dump("data =",data_pkt->data, data_pkt->length -2);
		memcpy(recv_data_info->data, data_pkt->data, (data_pkt->length - 2));
		recv_data_info->offset = (data_pkt->length - 2);
		recv_data_info->length = sdu_len;
		recv_data_info->flag_pkt_type = L2CAP_COC_FLAG_CONTINUOUS_PKT;
	}
	else if(recv_data_info->flag_pkt_type == L2CAP_COC_FLAG_CONTINUOUS_PKT)
	{
		hex_dump(" Data Received:", data_pkt->data, data_pkt->length);

		if(recv_data_info->offset + data_pkt->length > recv_data_info->length)
		{
			logd("recv_data_info->received_current_len : %d ", recv_data_info->offset + data_pkt->length);
			logd("recv_data_info->sdu_len : %d ", recv_data_info->length);
			logd("received_current_len > sdu_len .. so disconnect");
			memset(&(l2cap_coc_channel_tbl->coc_recv_data_pool), 0, sizeof(l2cap_coc_channel_tbl->coc_recv_data_pool));
			l2cap_coc_disconnect_req(l2cap_coc_channel_tbl->owner_trans_id, device, handle);
			return STATUS_ERR_INSUFFICIENT_RESOURCES;
		}
		memcpy((recv_data_info->data + recv_data_info->offset), data_pkt->data, data_pkt->length);
		recv_data_info->offset += data_pkt->length;
		logd("Total data received = %u sdu = %u", recv_data_info->offset, recv_data_info->length);
	}

	if(recv_data_info->length == recv_data_info->offset)
	{
		logd("recv_data_info->received_current_len:%d",(recv_data_info->offset));

		recv_data_info->offset = 0;
		if(l2cap_coc_channel_tbl->l2cap_coc_cb && l2cap_coc_channel_tbl->l2cap_coc_cb->recv_data_cb)
		{
			l2cap_coc_channel_tbl->l2cap_coc_cb->recv_data_cb(l2cap_coc_channel_tbl->owner_trans_id, device->idx, ccb_idx, recv_data_info->data, recv_data_info->length);
		}
		memset(&(l2cap_coc_channel_tbl->coc_recv_data_pool), 0, sizeof(l2cap_coc_channel_tbl->coc_recv_data_pool));
		recv_data_info->flag_pkt_type = L2CAP_COC_FLAG_FIRST_PKT;
	}
	l2cap_coc_send_fc_credit(device, ccb_idx, 0x0001);
	return STATUS_SUCCESS;
}

static INT8 lc_act_send_fc_credit(connected_device_t *device, UINT8 ccb_idx, UINT8* d)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!device)
	  return STATUS_ERR_INAVALID_CONNENCTION;
#endif
	l2cap_coc_conn_t* l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(l2cap_coc_channel_tbl->state != LCS_OPEN)
	{
		loge("L2cap coc is not is correct state to handle the request");
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
	l2cap_credits_t *credit_pkt = (l2cap_credits_t *)(void*)d;
	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_FC_CREDIT_LEN);
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_FC_CREDIT_LEN;
	UINT8 *p_buf = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(p_buf, L2CAP_COC_COMMAND_FC_CREDIT);
	device->l2cap_cur_id = increament_l2cap_identifier(device->l2cap_cur_id);
	UINT8_TO_STREAM(p_buf, device->l2cap_cur_id);
	UINT16_TO_STREAM(p_buf, L2CAP_COC_COMMAND_FC_CREDIT_LEN);
	UINT16_TO_STREAM(p_buf, l2cap_coc_channel_tbl->cid);
	UINT16_TO_STREAM(p_buf, credit_pkt->fc_credits);
	l2cap_coc_channel_tbl->credits += credit_pkt->fc_credits;

	INT8 ret=STATUS_SUCCESS;
	USE(ret);

	ret = l2cap_data_send(device->idx, L2CAP_LE_SIGNAL_CID, data_pkt);
	return ret;
}

static INT8 lc_act_recv_fc_credit(connected_device_t *device, UINT8 ccb_idx, UINT8* d)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if (!device)
	  return STATUS_ERR_INAVALID_CONNENCTION;
#endif
	l2cap_coc_conn_t* l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(l2cap_coc_channel_tbl->state != LCS_OPEN)
	{
		loge("L2cap coc is not is correct state to handle the request");
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
	l2cap_credits_t *credit_pkt = (l2cap_credits_t *)(void*)d;

	if(((credit_pkt->fc_credits) + (l2cap_coc_channel_tbl->r_credits)) >= (65536))
	{
		// disconnect the CoC
		l2cap_coc_disconnect_req(l2cap_coc_channel_tbl->owner_trans_id, device, credit_pkt->handle);
	}
	l2cap_coc_channel_tbl->r_credits += (credit_pkt->fc_credits);
	coc_pick_from_queue_to_send_data(device, ccb_idx);
	return STATUS_SUCCESS;
}
#endif // L2CAP_COC
/**
 * This function is called when data is to be sent to the remote device
 *
 * This function enqueues data in the data tx q. and if controller buffer is
 * free then sends to the hci layer.
 * On reception of num of hci pkts event it is called with d = NULL. Then
 * we send whatever is remaining in the buffer.
 *
 * This function not yet take care of data > controller data buffer size
 * Now it simply fails and reports the failure to the client.
 *
 * Struct of d: [UINT16 CID,  UINT16 LEN, UINT8* DATA_BUFFER]
 */
static INT8 l2cap_act_send_data(connected_device_t *device, UINT8* d)
{
	INT8 ret = STATUS_SUCCESS;
	UINT8 count = 0;
	UINT8 cur_device_idx;
	BOOLEAN fragmented_pkt;
	if (d != NULL )
	{
		buffer_t *data_pkt;
		UINT16 cid;
		UINT8 *p;
#if (PARANOID_STACK == TRUE)
		if (!device)
			return STATUS_ERR_INVALID_PARAM;
#endif
		data_pkt = (buffer_t*)(void*)d;
		p = &data_pkt->data[data_pkt->offset + sizeof(UINT16)];
		STREAM_TO_UINT16(cid, p);
#if (L2CAP_COC == TRUE)
		if(cid >= L2CAP_COC_START_CID)
		{
			UINT8 *ptr = &data_pkt->data[data_pkt->offset + sizeof(UINT16)];
			UINT16_TO_STREAM(ptr, get_rcid_for_cid(cid)); // For Coc dynamic channels cid and rcid could be different
		}
#endif
		enqueue(&l2cap_tx_q[device->idx], (void*)data_pkt);
	}
	/* If there is room in the controller buffer we send data */
	cur_device_idx = g_local_adapter.l2cap_next_device_idx;
	logd("data_window:%d", g_local_adapter.data_window);
	while (g_local_adapter.data_window > 0)
	{
		fragmented_pkt = FALSE;
		if(g_local_adapter.connected_device[cur_device_idx])
		{
			connected_device_t *cur_device = g_local_adapter.connected_device[cur_device_idx];
			buffer_t* data_pkt = (buffer_t*) pick_front(&l2cap_tx_q[cur_device->idx]);
			if (data_pkt != NULL )
			{
				UINT8 pb_flag;
				UINT16 l2cap_send_payload_len;
				count = 0;
				logd("data_pkt->offset = %d", data_pkt->offset);
				pb_flag = data_pkt->offset == (UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE) ? L2CAP_PB_FLAG_FIRST_NON_FLUSHABLE_PKT : L2CAP_PB_FLAG_CONTINUOUS_PKT;

				l2cap_send_payload_len = data_pkt->length - (data_pkt->offset - (UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE)); /* Length of the L2CAP packet (with header). */
				if (l2cap_send_payload_len > g_local_adapter.buffer_size)
				{
					/* Packet to be fragmented. */
					fragmented_pkt = TRUE;
					g_local_adapter.l2cap_next_device_idx = cur_device->idx;
					l2cap_send_payload_len = g_local_adapter.buffer_size;
				}
				else
				{
					/* Everything can be sent in one go. */
					dequeue(&l2cap_tx_q[cur_device->idx]);
				}
				ret = hci_send_data(cur_device, pb_flag,(UINT8*)data_pkt, l2cap_send_payload_len);
				if (ret != STATUS_SUCCESS)
				{
					if (data_pkt)
					{
						free_l2cap_buffer((void*)data_pkt);
					}
					loge("HCI send data failed");
					break;
				}
				else
				{
					g_local_adapter.data_window --;
					cur_device->num_un_acked_l2cap_pkts ++;
					if(fragmented_pkt)
						data_pkt->offset += l2cap_send_payload_len;
					else
						free_l2cap_buffer((void*)data_pkt);
				}
			}
			if(!fragmented_pkt)
			{
				cur_device_idx = (cur_device_idx + 1) % MAX_NUM_CONNECTED_DEVICE;
				g_local_adapter.l2cap_next_device_idx = cur_device_idx;
				count ++;
				if(count >= MAX_NUM_CONNECTED_DEVICE)
				{
					/* We have checked all the devices*/
					break;
				}
			}

		}
		else
		{
			/* No more data to be sent on this device*/
			cur_device_idx = (cur_device_idx + 1) % MAX_NUM_CONNECTED_DEVICE;
			g_local_adapter.l2cap_next_device_idx = cur_device_idx;
			count ++;
			if(count >= MAX_NUM_CONNECTED_DEVICE)
			{
				/* We have checked all the devices*/
				break;
			}
		}
	}
	return ret;
}

/**
 * This function is called when we receive data.
 * Call data receive call backs of the clients.
 */
static INT8 l2cap_act_recv_data(connected_device_t *device, UINT8* data)
{
	l2cap_recv_data_pkt_t *data_pkt = (l2cap_recv_data_pkt_t*)(void*)data;
	UINT16 cid;
	UINT16 l2cap_payload_length_total;
	UINT16 l2cap_payload_length_this_pkt = data_pkt->data_length;
	INT8 ret;
	logi("");

	if(!device)
		return STATUS_ERR_INVALID_PARAM;

	logd("pb_flag:0x%x", data_pkt->pb_flag);
	if (data_pkt->pb_flag == L2CAP_PB_FLAG_FIRST_FLUSHABLE_PKT) /* This is the first frame. This packet has the headers */
	{
		if(device->l2cap_ongoing_partial_segment_rx == TRUE)
		{
			loge("New L2CAP packet received when a partial segment was pending!!");
			logw("Discarding the old packet and processing the new packet");
			if(device->data_rx_pkt.l2cap_data)
			{
				dealloc(device->data_rx_pkt.l2cap_data);
				device->data_rx_pkt.l2cap_data = NULL;
			}
		}
		logd("fresh pkt.");
		STREAM_TO_UINT16(l2cap_payload_length_total, data_pkt->data);
		STREAM_TO_UINT16(cid, data_pkt->data);
		logd("length:%d cid:%d", l2cap_payload_length_total, cid);
		l2cap_payload_length_total = TRUNCATE_TO_16BIT_LENGTH(l2cap_payload_length_total, sizeof(buffer_t));
		device->data_rx_pkt.l2cap_data = (buffer_t*)alloc(l2cap_payload_length_total + sizeof(buffer_t));
		if(!device->data_rx_pkt.l2cap_data)
			return STATUS_ERR_INSUFFICIENT_RESOURCES;
		device->data_rx_pkt.l2cap_data->length = l2cap_payload_length_total;
		device->data_rx_pkt.l2cap_data->offset = 0;
		device->data_rx_pkt.cid = cid;
		l2cap_payload_length_this_pkt -= L2CAP_HDR_SIZE;
	}
	else if(data_pkt->pb_flag == L2CAP_PB_FLAG_CONTINUOUS_PKT)
	{
		if(device->l2cap_ongoing_partial_segment_rx == FALSE)
		{
			loge("Partial L2CAP segment received when a new packet was expected!!");
			logw("Discarding this continuation packet");
			return STATUS_ERR_LAYER_SPECIFIC;
		}

		if(!device->data_rx_pkt.l2cap_data)
			return  STATUS_ERR_INSUFFICIENT_RESOURCES;

		if((UINT32)device->data_rx_pkt.l2cap_data->offset + (UINT32)l2cap_payload_length_this_pkt > (UINT32)device->data_rx_pkt.l2cap_data->length)
		{
			loge("More Data present in the partial segment than expected!!");
			logw("Discarding the all the pending packets");
			if(device->data_rx_pkt.l2cap_data)
			{
				dealloc(device->data_rx_pkt.l2cap_data);
				device->data_rx_pkt.l2cap_data = NULL;
			}
			return STATUS_ERR_LAYER_SPECIFIC;
		}
	}
	else
	{
		loge("Unknown PB flag:%d", data_pkt->pb_flag);
		return STATUS_ERR_LAYER_SPECIFIC;
	}

	memcpy (device->data_rx_pkt.l2cap_data->data + device->data_rx_pkt.l2cap_data->offset, data_pkt->data, l2cap_payload_length_this_pkt);
	device->data_rx_pkt.l2cap_data->offset += l2cap_payload_length_this_pkt;
	if(device->data_rx_pkt.l2cap_data->offset < device->data_rx_pkt.l2cap_data->length)
	{
		logd("This packet is not yet complete. Waiting for more partial fragments");
		device->l2cap_ongoing_partial_segment_rx = TRUE;
		return STATUS_SUCCESS;
	}
	device->l2cap_ongoing_partial_segment_rx = FALSE;
	logd("Process the data now.");
	device->data_rx_pkt.l2cap_data->offset = 0;
	hex_dump("", device->data_rx_pkt.l2cap_data->data, device->data_rx_pkt.l2cap_data->length);
	ret = STATUS_ERR_UNKNOWN;
	switch (device->data_rx_pkt.cid)
	{
		case L2CAP_ATT_CID:
		{
			ret = att_l2cap_recv_data_cb(device->idx, device->data_rx_pkt.l2cap_data);
		}
			break;
		case L2CAP_LE_SIGNAL_CID:
		{
			ret = l2cap_signal_pkt_handler(device, device->data_rx_pkt.l2cap_data->data, device->data_rx_pkt.l2cap_data->length);
		}
			break;
		case L2CAP_SMP_CID:
		{
			ret = smp_l2cap_recv_data_cb(device, device->data_rx_pkt.l2cap_data->data, device->data_rx_pkt.l2cap_data->length);
		}
			break;
		default:
		{
#if (L2CAP_COC == TRUE)
			if (!device || !device->data_rx_pkt.l2cap_data) return STATUS_ERR_INVALID_PARAM;
			if(device && device->l2cap_state != L2CAP_STATE_OPEN) return STATUS_ERR_INAVALID_CONNENCTION;
			UINT8 ccb_idx = get_handle_from_coc_table_for_cid(device->data_rx_pkt.cid);
			if(ccb_idx == MAX_NUMBER_OF_L2CAP_COC_CHNL)
			{
				logw("Invalid CID(%u): Ignoring the packet !!!", cid);
				dealloc(device->data_rx_pkt.l2cap_data);
				device->data_rx_pkt.l2cap_data = NULL;
				return STATUS_ERR_INAVALID_CONNENCTION;
			}

			l2cap_coc_conn_t* l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
			if(l2cap_coc_channel_tbl == NULL)
			{
				loge("Invalid le l2cap coc connection id");
				dealloc(device->data_rx_pkt.l2cap_data);
				device->data_rx_pkt.l2cap_data = NULL;
				return STATUS_ERR_INVALID_PARAM;
			}
			if(device->data_rx_pkt.l2cap_data->length > l2cap_coc_channel_tbl->mps)
			{
				logw("Invalid PDU size. Disconnect the channel");
				dealloc(device->data_rx_pkt.l2cap_data);
				device->data_rx_pkt.l2cap_data = NULL;
				l2cap_coc_disconnect_req(l2cap_coc_channel_tbl->owner_trans_id, device, ccb_idx);
				return STATUS_ERR_INVALID_PARAM;
			}
			l2cap_data_t data_pkt;

			data_pkt.handle = ccb_idx;
			data_pkt.length = device->data_rx_pkt.l2cap_data->length;
			data_pkt.data = device->data_rx_pkt.l2cap_data->data;
			ret = lc_act_recv_data(device, ccb_idx, (UINT8 *)&data_pkt);
#endif // L2CAP_COC
			}
			break;
			}
			if (device->data_rx_pkt.l2cap_data)
			{
				dealloc (device->data_rx_pkt.l2cap_data);
				device->data_rx_pkt.l2cap_data = NULL;
				device->data_rx_pkt.cid = 0;
			}
			return ret;
}

/**
 * buffer contains L2CAP payload only.
 */
static INT8 l2cap_signal_pkt_handler(connected_device_t *device, UINT8* buffer, UINT16 buffer_length)
{
	UINT8 l2cap_command;
	UINT8 id;
	UINT16 length;

	if ((device == NULL) || (buffer_length < sizeof(l2cap_command) + sizeof(id)))
		return STATUS_ERR_INVALID_PARAM;

	STREAM_TO_UINT8(l2cap_command, buffer);
	STREAM_TO_UINT8(id, buffer);
	buffer_length -= (sizeof(l2cap_command) + sizeof(id));
	/* Store the id for future use */
	if(id == 0) //TODO: match identifier for reponse pkt and for command pkt check if identifier is not same as last pkt
	{
		logw("Received wrong Identifier(%u) from remote device(%u) so discarding it", id, device->idx);
		return STATUS_ERR_INVALID_PARAM;
	}
	device->l2cap_cur_id = id;

	if (buffer_length < sizeof(length))
		return STATUS_ERR_INVALID_PARAM;

	STREAM_TO_UINT16(length, buffer);
	buffer_length -= sizeof(length);

	if (length != buffer_length)
	{
		logw("Received invalid length packet from remote device(%u), stated = %d, actual = %d", device->idx, length, buffer_length);
		return STATUS_ERR_INVALID_PARAM;
	}

	if (length > L2CAP_SIGNALLING_MTU_SIZE)
		return l2cap_send_command_reject(device, id, L2CAP_SIGNALLING_MTU_EXEEDED);

	switch (l2cap_command)
	{
	case L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_REQ:
	{
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
		if (device->local_link_role == LINK_ROLE_MASTER)
		{
			UINT16 interval_min;
			UINT16 interval_max;
			UINT16 slave_latency;
			UINT16 timeout_mul;

			if (buffer_length < sizeof(interval_min) + sizeof(interval_max) + sizeof(slave_latency) + sizeof(timeout_mul))
				return STATUS_ERR_INVALID_PARAM;

			STREAM_TO_UINT16(interval_min, buffer);
			STREAM_TO_UINT16(interval_max, buffer);
			STREAM_TO_UINT16(slave_latency, buffer);
			STREAM_TO_UINT16(timeout_mul, buffer);
			buffer_length -= (sizeof(interval_min) + sizeof(interval_max) + sizeof(slave_latency) + sizeof(timeout_mul));
			if (gap_update_conn_params(device->idx, interval_min, interval_max, slave_latency, timeout_mul) == STATUS_SUCCESS)
			{
				/* Change the state to update continue */
				return l2cap_csm_handler(L2CAP_EVT_INIT_CONNECT_PARAM_UPDATE,
							device, NULL );
			} else
			{
				/* Bad parameter req */
				return l2cap_send_command_conn_param_update_res(device, id, L2CAP_CONN_PARAM_REJECTED);
			}
		} else
#endif
		{
			/* Slave cannot receive this. Reject this */
			return l2cap_send_command_reject(device, id, L2CAP_COMMAND_NOT_UNDERSTOOD);
		}
	}
	case L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_RES:
	{		
			if (device->local_link_role != LINK_ROLE_MASTER)
			{
				UINT8 result;
				if (buffer_length < sizeof(result))
					return STATUS_ERR_INVALID_PARAM;

				STREAM_TO_UINT8(result, buffer);
				buffer_length -= sizeof(result);
				if (result == L2CAP_CONN_PARAM_REJECTED)
				{
					/* Sending dummy event to GAP with status Unsupported LL Parameter */
					UINT8 dummy_command[9];
					UINT8 *p = dummy_command;
					UINT8_TO_STREAM(p,0x20);
					UINT16_TO_STREAM(p,device->acl_handle);
					gap_handle_conn_param_update_cmpl(dummy_command, sizeof(dummy_command));
				}
				return l2cap_csm_handler(L2CAP_EVT_CONNECT_PARAM_UPDATE_DONE, device,
					 NULL);
			}
	}
	case L2CAP_COMMAND_REJECT:
	{
#if (L2CAP_COC == TRUE)
		if(device && device->l2cap_state == L2CAP_STATE_OPEN)
		{
			UINT8 idx;
			for(idx = 0; idx < MAX_NUMBER_OF_L2CAP_COC_CHNL; idx++)
			{
				if(g_local_adapter.l2cap_coc_channel_tbl[idx] != NULL)
				{
					if(g_local_adapter.l2cap_coc_channel_tbl[idx]->state == LCS_W4_CONNECT_RES)
					{
						l2cap_coc_conn_t *l2cap_coc_channel_tbl = g_local_adapter.l2cap_coc_channel_tbl[idx];
						logw("Recevied command reject from peer device for le psm: %d", g_local_adapter.l2cap_coc_channel_tbl[idx]->psm);
						if(l2cap_coc_channel_tbl->l2cap_coc_cb && l2cap_coc_channel_tbl->l2cap_coc_cb->connection_cmpl_cb)
						{
							l2cap_coc_channel_tbl->l2cap_coc_cb->connection_cmpl_cb(l2cap_coc_channel_tbl->owner_trans_id,
									device->idx, l2cap_coc_channel_tbl->psm, idx, l2cap_coc_channel_tbl->r_mtu, MAX_NUMBER_OF_L2CAP_COC_TX_BUFFER, STATUS_ERR_UNKNOWN);
						}

						delete_l2cap_coc_tbl(idx);
						return STATUS_ERR_INAVALID_CONNENCTION;
					}
				}
			}
		}
#endif //L2CAP_COC
		return 	STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}
#if (L2CAP_COC == TRUE)
	case L2CAP_COC_COMMAND_CONNECT_RES: // Received from remote device
	{
		if((length != L2CAP_COC_COMMAND_CONNECT_RES_LEN) || (buffer_length < L2CAP_COC_COMMAND_CONNECT_RES_LEN))
			return STATUS_ERR_INVALID_PARAM;
		UINT8 idx = get_coc_ccb_by_l2cap_id(device->idx, id);
		if(idx == MAX_NUMBER_OF_L2CAP_COC_CHNL)
			return STATUS_ERR_INAVALID_CONNENCTION;
		INT8 ret = lc_act_recv_connect_res(device, idx, (UINT8 *)buffer);
		return ret;
	}
	case L2CAP_COC_COMMAND_CONNECT_REQ: // Received from remote device
	{
		if(length != L2CAP_COC_COMMAND_CONNECT_REQ_LEN) return STATUS_ERR_INVALID_PARAM;
		if(device && device->l2cap_state != L2CAP_STATE_OPEN) return STATUS_ERR_INAVALID_CONNENCTION;
		UINT16 psm;
		if (buffer_length < sizeof(psm))
			return STATUS_ERR_INVALID_PARAM;
		STREAM_TO_UINT16(psm, buffer);
		buffer_length -= sizeof(psm);
		UINT8 idx = get_psm_registration_idx(psm);
		if((idx == MAX_NUM_OF_REGISTERED_PSM) || (check_psm_already_in_use(psm, device->idx) < MAX_NUMBER_OF_L2CAP_COC_CHNL))
		{
			/* THis PSM was not registered by any app. or connection is already exists with psm and remote device, So reject the connection*/
			logw("Unable to find any registered app for PSM(%u). or Connection is already exists with psm and remote device, so COC connection rejected!!! ", psm);
			buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_CONNECT_RES_LEN);
			if(NULL == data_pkt)
			{
				logd("L2cap packet unavailable");
				return STATUS_ERR_INSUFFICIENT_RESOURCES;
			}
			data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
			data_pkt->length = L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_CONNECT_RES_LEN;
			UINT8 *p_buf = &data_pkt->data[data_pkt->offset];
			UINT8_TO_STREAM(p_buf, L2CAP_COC_COMMAND_CONNECT_RES);
			UINT8_TO_STREAM(p_buf, device->l2cap_cur_id); // Use the same l2cap_cur_id sent by remote for the connect response.
			UINT16_TO_STREAM(p_buf, L2CAP_COC_COMMAND_CONNECT_RES_LEN);
			UINT16_TO_STREAM(p_buf, 40);
			UINT16_TO_STREAM(p_buf, 40);
			UINT16_TO_STREAM(p_buf, 20);
			UINT16_TO_STREAM(p_buf, 100);
			UINT16_TO_STREAM(p_buf, L2CAP_COC_RESPONSE_LE_PSM_NOT_SUPPORTED);
			INT8 ret = l2cap_data_send(device->idx, L2CAP_LE_SIGNAL_CID, data_pkt);
			return ret;
		}
		UINT8 ccb_idx = find_first_free_l2cap_coc_tbl_slot();
		if(ccb_idx == MAX_NUMBER_OF_L2CAP_COC_CHNL)
		{
			/* No free coc channel available for this device. Reject the connection */
			logw("No free COC channel available for this device(conn_id:%u). COC connection rejected", device->idx);
			buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_CONNECT_RES_LEN);
			if(NULL == data_pkt)
			{
				logd("L2cap packet unavailable");
				return STATUS_ERR_INSUFFICIENT_RESOURCES;
			}
			data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
			data_pkt->length = L2CAP_COMMAND_HDR_LEN + L2CAP_COC_COMMAND_CONNECT_RES_LEN;
			UINT8 *p_buf = &data_pkt->data[data_pkt->offset];
			UINT8_TO_STREAM(p_buf, L2CAP_COC_COMMAND_CONNECT_RES);
			UINT8_TO_STREAM(p_buf, device->l2cap_cur_id); // Use the same l2cap_cur_id sent by remote for the connect response.
			UINT16_TO_STREAM(p_buf, L2CAP_COC_COMMAND_CONNECT_RES_LEN);
			UINT16_TO_STREAM(p_buf, 40);
			UINT16_TO_STREAM(p_buf, 40);
			UINT16_TO_STREAM(p_buf, 20);
			UINT16_TO_STREAM(p_buf, 100);
			UINT16_TO_STREAM(p_buf, L2CAP_COC_RESPONSE_NO_RESOURCES_AVAILABLE);
			INT8 ret = l2cap_data_send(device->idx, L2CAP_LE_SIGNAL_CID, data_pkt);
			return ret;
		}
		g_local_adapter.l2cap_coc_channel_tbl[ccb_idx] = create_l2cap_coc_tbl();
		l2cap_coc_conn_t* l2cap_coc_channel_tbl = g_local_adapter.l2cap_coc_channel_tbl[ccb_idx];

		l2cap_coc_channel_tbl->psm = psm;

		if (buffer_length < sizeof(l2cap_coc_channel_tbl->r_cid) + sizeof(l2cap_coc_channel_tbl->r_cid) + sizeof(l2cap_coc_channel_tbl->r_mps) + sizeof(l2cap_coc_channel_tbl->r_credits))
			return STATUS_ERR_INVALID_PARAM;

		STREAM_TO_UINT16(l2cap_coc_channel_tbl->r_cid, buffer); // here s_cid is remote device channel id.
		STREAM_TO_UINT16(l2cap_coc_channel_tbl->r_mtu, buffer);

		//check the max MTU that stack can support and reassign remote MTU accordingly
		if(l2cap_coc_channel_tbl->r_mtu > L2CAP_COC_MAX_MTU)
			l2cap_coc_channel_tbl->r_mtu = L2CAP_COC_MAX_MTU;

		STREAM_TO_UINT16(l2cap_coc_channel_tbl->r_mps, buffer);
		STREAM_TO_UINT16(l2cap_coc_channel_tbl->r_credits, buffer);
		buffer_length -= (sizeof(l2cap_coc_channel_tbl->r_cid) + sizeof(l2cap_coc_channel_tbl->r_cid) + sizeof(l2cap_coc_channel_tbl->r_mps) + sizeof(l2cap_coc_channel_tbl->r_credits));
		l2cap_coc_channel_tbl->le_conn_id = device->idx;
		l2cap_coc_channel_tbl->mps = L2CAP_COC_MPS;
		l2cap_coc_channel_tbl->credits = L2CAP_COC_INITIAL_CREDITS;
		l2cap_coc_channel_tbl->cid = ccb_idx + L2CAP_COC_START_CID;
		l2cap_coc_channel_tbl->mtu = g_local_adapter.l2cap_registered_psm_tbl[idx].mtu;
		l2cap_coc_channel_tbl->owner_trans_id = g_local_adapter.l2cap_registered_psm_tbl[idx].owner_trans_id;
		init_no_guard_q(&l2cap_coc_channel_tbl->coc_data_tx_q);
		l2cap_coc_channel_tbl->l2cap_coc_cb = g_local_adapter.l2cap_registered_psm_tbl[idx].l2cap_coc_cb;

		INT8 ret = lc_act_recv_connect_req(device, ccb_idx, NULL);
		return ret;
	}
	case L2CAP_COC_COMMAND_DISCONNECT_RES: // Received from remote device
	{
		if(length != 4) return STATUS_ERR_INVALID_PARAM;
		if(device && device->l2cap_state != L2CAP_STATE_OPEN) return STATUS_ERR_INAVALID_CONNENCTION;

		UINT16 cid=0, r_cid=0;
		if (buffer_length < sizeof(r_cid) + sizeof(cid))
			return STATUS_ERR_INVALID_PARAM;

		STREAM_TO_UINT16(r_cid, buffer);
		STREAM_TO_UINT16(cid, buffer);
		buffer_length-= (sizeof(r_cid) + sizeof(cid));
		UINT8 handle = get_handle_from_coc_table_for_cids(cid, r_cid);
		if(handle == MAX_NUMBER_OF_L2CAP_COC_CHNL)
		{
			logw("Disconnect received from unknown CID(%u). Ignoring the packet", cid);
			return STATUS_ERR_INAVALID_CONNENCTION;
		}
		INT8 ret = lc_act_recv_disconnect_res(device, handle, NULL);
		return ret;
	}
	case L2CAP_COC_COMMAND_DISCONNECT_REQ:
	{
		if(length != 4) return STATUS_ERR_INVALID_PARAM;
		if(device && device->l2cap_state != L2CAP_STATE_OPEN) return STATUS_ERR_INAVALID_CONNENCTION;

		UINT16 cid=0, r_cid=0;
		if (buffer_length < sizeof(r_cid) + sizeof(cid))
			return STATUS_ERR_INVALID_PARAM;

		STREAM_TO_UINT16(cid, buffer);
		STREAM_TO_UINT16(r_cid, buffer);
		buffer_length-= (sizeof(r_cid) + sizeof(cid));
		UINT8 handle = get_handle_from_coc_table_for_cids(cid, r_cid);
		if(handle == MAX_NUMBER_OF_L2CAP_COC_CHNL)
		{
			logw("Disconnect response for unknown CID(%u). Ignoring the packet!!", cid);
			return STATUS_ERR_INAVALID_CONNENCTION;
		}
		INT8 ret = lc_act_recv_disconnect_req(device, handle, NULL);
		return ret;
	}
	case L2CAP_COC_COMMAND_FC_CREDIT:
	{
		if(length != 4) return STATUS_ERR_INVALID_PARAM;
		if(device && device->l2cap_state != L2CAP_STATE_OPEN) return STATUS_ERR_INAVALID_CONNENCTION;

		l2cap_credits_t *credit_pkt = (l2cap_credits_t *) alloc(sizeof(l2cap_credits_t));

		if (!credit_pkt)
			return STATUS_ERR_INSUFFICIENT_RESOURCES;

		UINT16 r_cid=0;
		if (buffer_length < sizeof(r_cid) + sizeof(credit_pkt->fc_credits))
			return STATUS_ERR_INVALID_PARAM;

		STREAM_TO_UINT16(r_cid, buffer);
		STREAM_TO_UINT16(credit_pkt->fc_credits, buffer);
		buffer_length-= (sizeof(r_cid) + sizeof(credit_pkt->fc_credits));
		credit_pkt->handle = get_handle_from_coc_table_for_cid(get_cid_for_rcid(r_cid, device->idx));
		INT8 ret = lc_act_recv_fc_credit(device, credit_pkt->handle,(UINT8*)credit_pkt);
		dealloc (credit_pkt);
		return ret;
	}
#endif //L2CAP_COC
	default:
	{
		return l2cap_send_command_reject(device, id, L2CAP_COMMAND_NOT_UNDERSTOOD);
	}
	}
}

static INT8 l2cap_send_command_reject(connected_device_t *device, UINT8 id,
		UINT16 reason)
{
	UINT16 buf_len = L2CAP_COMMAND_HDR_LEN + L2CAP_COMMAND_REJECT_LEN;
	buffer_t *data_pkt = get_l2cap_free_buffer(buf_len);
	UINT8 *p;
	INT8 ret;
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = buf_len;
	p =  &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(p, L2CAP_COMMAND_REJECT);
	UINT8_TO_STREAM(p, id);
	UINT16_TO_STREAM(p, sizeof (reason));
	UINT16_TO_STREAM(p, reason);
	ret = l2cap_data_send(device->idx, L2CAP_LE_SIGNAL_CID, data_pkt);
	return ret;
}

#if(GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
static INT8 l2cap_send_command_conn_param_update_res(
		connected_device_t *device, UINT8 id, UINT16 result)
{
	buffer_t *data_pkt = get_l2cap_free_buffer(L2CAP_COMMAND_HDR_LEN + L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_RES_LEN);
	UINT8 *p;
	INT8 ret;
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = L2CAP_COMMAND_HDR_LEN + L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_RES_LEN;
	p =  &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(p, L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_RES);
	UINT8_TO_STREAM(p, device->l2cap_cur_id);
	UINT16_TO_STREAM(p, L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_RES_LEN);
	UINT16_TO_STREAM(p, result);
	hex_dump("", &data_pkt->data[data_pkt->offset], data_pkt->length);

	ret = l2cap_data_send(device->idx, L2CAP_LE_SIGNAL_CID, data_pkt);
	return ret;
}
#endif

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
static INT8 l2cap_send_command_conn_param_update_req(connected_device_t *device, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout)
{
	buffer_t *data_pkt = get_l2cap_free_buffer(L2CAP_COMMAND_HDR_LEN + L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_REQ_LEN);
	UINT8 *p;
	INT8 ret;
	if (NULL == data_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	data_pkt->offset = UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + L2CAP_HDR_SIZE;
	data_pkt->length = L2CAP_COMMAND_HDR_LEN + L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_REQ_LEN;
	p =  &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(p, L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_REQ);
	device->l2cap_cur_id = increament_l2cap_identifier(device->l2cap_cur_id);
	UINT8_TO_STREAM(p, device->l2cap_cur_id);
	UINT16_TO_STREAM(p, L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_REQ_LEN);
	UINT16_TO_STREAM(p, interval_min);
	UINT16_TO_STREAM(p, interval_max);
	UINT16_TO_STREAM(p, conn_latency);
	UINT16_TO_STREAM(p, sup_timeout);
	hex_dump("", &data_pkt->data[data_pkt->offset], data_pkt->length);

	ret = l2cap_data_send(device->idx, L2CAP_LE_SIGNAL_CID, data_pkt);
	return ret;
}
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

static INT8 l2cap_act_init_connect_param_update(connected_device_t *device,
		UINT8* d)
{
#if (PARANOID_STACK == TRUE)
	if (device == NULL)
		return STATUS_ERR_INAVALID_CONNENCTION;
#endif
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	if (device->local_link_role == LINK_ROLE_MASTER)
	{
		/* Nothing to do for master */
		return STATUS_SUCCESS;
	}
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	l2cap_param_updt_pkt_t *cmd_pkt;
	cmd_pkt = (l2cap_param_updt_pkt_t *)(void*)d;
	return l2cap_send_command_conn_param_update_req(device, cmd_pkt->interval_min, cmd_pkt->interval_max, cmd_pkt->conn_latency, cmd_pkt->sup_timeout);
#else
	return STATUS_SUCCESS;
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
}
static INT8 l2cap_act_connect_param_update_done(connected_device_t *device,
		UINT8* d)
{
#if (PARANOID_STACK == TRUE)
	if (device == NULL)
		return STATUS_ERR_INAVALID_CONNENCTION;
#endif
#if(GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	if (device->local_link_role == LINK_ROLE_MASTER)
	{
		UINT8 status;
		UINT8 result = L2CAP_CONN_PARAM_REJECTED;
		STREAM_TO_UINT8(status, d);
		if (status == HCI_EVENT_STATUS_SUCCESS)
		{
			JUMP_CUSTOM_LEN(d, 2); /* Skip connection handle */
			STREAM_TO_UINT16(device->conn_interval, d);
			STREAM_TO_UINT16(device->conn_latency, d);
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
			STREAM_TO_UINT16(device->sup_timeout, d);
#else
			UINT16 dummy;
			STREAM_TO_UINT16(dummy, d);
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */
			/* Send l2cap conn param update accepted. */
			result = L2CAP_CONN_PARAM_ACCEPTED;
		}
		return l2cap_send_command_conn_param_update_res(device, device->l2cap_cur_id,
				result);
	}
#endif
	return STATUS_SUCCESS;
}

/*********************************************************************
 * 						L2CAP APIs
 ********************************************************************/
INT8 l2cap_init(void)
{
	UINT8 idx;
	g_local_adapter.l2cap_next_device_idx = 0;
	for( idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
		init_no_guard_q(&l2cap_tx_q[idx]);
	return STATUS_SUCCESS;
}

void l2cap_cleanup(void)
{
#if (L2CAP_COC == TRUE)
	clear_l2cap_coc_tbl();
#endif // L2CAP_COC
	iLE_stack_cleanup();
}
/**
 * Connect request. This creates the fixed channel control blocks.
 */
INT8 l2cap_connect_req(connected_device_t *device, UINT16 psm)
{
#if (PARANOID_STACK == TRUE)
	if (!device)
		return STATUS_ERR_INVALID_PARAM;
#endif

	if (psm != L2CAP_ATT_PSM && psm != L2CAP_SMP_PSM)
	{
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	} else
	{
		l2cap_connect_cb(device, TRUE);
		return STATUS_SUCCESS;
	}
}

INT8 l2cap_data_send(UINT8 conn_id, UINT16 cid, buffer_t* buffer)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	UINT8* p;
	INT8 ret;
	/* This is to check if anything is pending in tx data queue */
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	if(cid == L2CAP_ATT_CID)
		log_time_stamp(TIME_ATT_SEND_DATA);
#endif
	if (device == NULL)
	{
		logd("Sending pending data.");
		return l2cap_act_send_data(NULL, NULL);
	}
	logd("cid:%d buffer_len:%d", cid, buffer->length);
	buffer->offset -= L2CAP_HDR_SIZE;
	p = &buffer->data[buffer->offset];
	UINT16_TO_STREAM(p, buffer->length);
	UINT16_TO_STREAM(p, cid);
	buffer->length += L2CAP_HDR_SIZE;
	ret = l2cap_csm_handler(L2CAP_EVT_SEND_DATA, device, (UINT8*) buffer);
	return ret;
}

INT8 l2cap_send_conn_param_update_req(connected_device_t *device, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout)
{
	l2cap_param_updt_pkt_t cmd_pkt;

	cmd_pkt.interval_min = interval_min;
	cmd_pkt.interval_max = interval_max;
	cmd_pkt.conn_latency = conn_latency;
	cmd_pkt.sup_timeout = sup_timeout;
	return l2cap_csm_handler(L2CAP_EVT_INIT_CONNECT_PARAM_UPDATE, device,(UINT8*)&cmd_pkt);

}

INT8 l2cap_disconnect_req(connected_device_t *device)
{
#if (PARANOID_STACK == TRUE)
	if (!device)
		return STATUS_ERR_INVALID_PARAM;
#endif
	l2cap_disconnect_cb(device, TRUE);
	return STATUS_SUCCESS;
}

INT8 l2cap_connect_cancel_req(UINT8 *remote_bd_addr)
{
	/* Call Gap to cancel the connection establishment */
	return STATUS_ERR_OPERATION_NOT_SUPPORTED;
}

#if (L2CAP_COC == TRUE)
INT8 l2cap_coc_connect_req(trans_id_t trans_id, UINT8 conn_id, UINT16 psm, UINT16 mtu, l2cap_coc_callbacks_t *l2cap_coc_cbs)
{
	logi("");
	INT8 ret = STATUS_ERR_OPERATION_NOT_SUPPORTED;
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return STATUS_ERR_INVALID_PARAM;

	// L2CAP should be connected and should be in L2CAP_STATE_OPEN state in order to initiate CoC_connect
	if(device->l2cap_state != L2CAP_STATE_OPEN)
	{
		if(l2cap_coc_cbs->connection_cmpl_cb)
			l2cap_coc_cbs->connection_cmpl_cb(trans_id, conn_id, psm,
					0xFF, 0xFFFF, 0, STATUS_ERR_INAVALID_CONNENCTION);
		return STATUS_ERR_INAVALID_CONNENCTION;
	}
	if((check_psm_already_in_use(psm, conn_id) < MAX_NUMBER_OF_L2CAP_COC_CHNL) || !is_psm_valid(psm) || mtu > L2CAP_COC_MAX_MTU || mtu < L2CAP_COC_MIN_MTU)
	{
		if(l2cap_coc_cbs->connection_cmpl_cb)
			l2cap_coc_cbs->connection_cmpl_cb(trans_id, conn_id, psm,
					0xFF, 0xFFFF, 0, STATUS_ERR_INVALID_PARAM);
		return STATUS_ERR_INVALID_PARAM; // 'psm' is already in use with remote device or psm' is invalid or mtu is bigger than supported mtu
	}
	UINT8 ccb_idx = find_first_free_l2cap_coc_tbl_slot();
	if(ccb_idx == MAX_NUMBER_OF_L2CAP_COC_CHNL)
	{	if(l2cap_coc_cbs->connection_cmpl_cb)
		l2cap_coc_cbs->connection_cmpl_cb(trans_id, conn_id, psm,
				0xFF, 0xFFFF, 0, STATUS_ERR_INSUFFICIENT_RESOURCES);
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}

	g_local_adapter.l2cap_coc_channel_tbl[ccb_idx] = create_l2cap_coc_tbl();
	l2cap_coc_conn_t* l2cap_coc_channel_tbl = g_local_adapter.l2cap_coc_channel_tbl[ccb_idx];

	l2cap_coc_channel_tbl->owner_trans_id = trans_id;
	l2cap_coc_channel_tbl->le_conn_id = device->idx;
	l2cap_coc_channel_tbl->mtu = mtu;
	l2cap_coc_channel_tbl->psm = psm;
	l2cap_coc_channel_tbl->l2cap_coc_cb = l2cap_coc_cbs;
	l2cap_coc_channel_tbl->state = LCS_CLOSED;
	init_no_guard_q(&l2cap_coc_channel_tbl->coc_data_tx_q);
	ret = lc_act_send_connect_req(device, ccb_idx, NULL);
	return ret;
}

/** Irrespective of the states, any application can register an PSM at any time. Therefore this function does not invoke state machine operations */
INT8 l2cap_coc_register_cb_for_conn_req(trans_id_t trans_id, UINT16 psm, UINT16 mtu, BOOLEAN auth_req, l2cap_coc_callbacks_t *l2cap_coc_cbs)
{
	logi("");
	UINT8 idx;
	if((get_psm_registration_idx(psm) < MAX_NUM_OF_REGISTERED_PSM) || !is_psm_valid(psm) || mtu > L2CAP_COC_MAX_MTU || mtu < L2CAP_COC_MIN_MTU)
	{
		if(l2cap_coc_cbs->register_cb)
			l2cap_coc_cbs->register_cb(trans_id, psm, STATUS_ERR_INVALID_PARAM);
		return STATUS_ERR_INVALID_PARAM; // already an application has registered for 'psm' or 'psm' is invalid or mtu is bigger than supported mtu
	}
	idx = get_free_psm_registration_slot();
	if(idx == MAX_NUM_OF_REGISTERED_PSM)
	{
		logd("No free slots available. PSM not registered!!!");
		if(l2cap_coc_cbs->register_cb)
			l2cap_coc_cbs->register_cb(trans_id, psm, STATUS_ERR_INSUFFICIENT_RESOURCES);
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	g_local_adapter.l2cap_registered_psm_tbl[idx].owner_trans_id = trans_id;
	g_local_adapter.l2cap_registered_psm_tbl[idx].auth_req = auth_req;
	g_local_adapter.l2cap_registered_psm_tbl[idx].psm = psm;
	g_local_adapter.l2cap_registered_psm_tbl[idx].mtu = mtu;
	g_local_adapter.l2cap_registered_psm_tbl[idx].l2cap_coc_cb = l2cap_coc_cbs;
	if(l2cap_coc_cbs->register_cb)
	{
		l2cap_coc_cbs->register_cb(trans_id, psm, STATUS_SUCCESS);
	}
	return STATUS_SUCCESS;
}

UINT16 l2cap_coc_get_max_mtu_size()
{
	logi("");
	return L2CAP_COC_MAX_MTU;
}

INT8 l2cap_coc_disconnect_req(trans_id_t trans_id, connected_device_t *device, UINT8 handle)
{
	logi("");

	if (!device)
		return STATUS_ERR_INVALID_PARAM;

	// L2CAP should be connected and should be in L2CAP_STATE_OPEN state in order to initiate CoC operation
	if(device && device->l2cap_state != L2CAP_STATE_OPEN) return STATUS_ERR_INAVALID_CONNENCTION;

	INT8 ret = STATUS_ERR_OPERATION_NOT_SUPPORTED;
	ret = lc_act_send_disconnect_req(device, handle, NULL);
	return ret;
}

INT8 l2cap_coc_send_fc_credit(connected_device_t *device, UINT8 handle, UINT16 fc_credits)
{
	logi("");

	if (!device)
		return STATUS_ERR_INVALID_PARAM;

	if(device && device->l2cap_state != L2CAP_STATE_OPEN) return STATUS_ERR_INAVALID_CONNENCTION;
	if(!fc_credits) return STATUS_ERR_INVALID_PARAM;

	INT8 ret = STATUS_ERR_OPERATION_NOT_SUPPORTED;
	l2cap_credits_t *credit_pkt = (l2cap_credits_t *) alloc(sizeof(l2cap_credits_t));

	if (!credit_pkt)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	credit_pkt->handle = handle;
	credit_pkt->fc_credits = fc_credits;
	ret = lc_act_send_fc_credit(device, handle, (UINT8*) credit_pkt);
	dealloc (credit_pkt);
	return ret;
}

INT8 l2cap_coc_send_data(connected_device_t *device, UINT8 ccb_idx, UINT8* buffer, UINT16 buffer_len)
{
	logi("");
	hex_dump("DATA:", buffer, buffer_len);

	if (!device)
		return STATUS_ERR_INVALID_PARAM;

	l2cap_coc_conn_t* l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return STATUS_ERR_INVALID_PARAM;
	}

	if(device && device->l2cap_state != L2CAP_STATE_OPEN) return STATUS_ERR_INAVALID_CONNENCTION;
	if((buffer == NULL) || (buffer_len > l2cap_coc_channel_tbl->r_mtu)) return STATUS_ERR_INVALID_PARAM;

	INT8 ret = STATUS_ERR_OPERATION_NOT_SUPPORTED;
	l2cap_coc_conn_send_data_t *data_pkt = get_free_coc_tx_data_pool(ccb_idx);

	if (!data_pkt)
	{
		logw("Coc channel is congested - App should send the pkt upon receiving the credits from stack");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	l2cap_coc_channel_tbl->tx_usage_count++;
	data_pkt->offset = 0;
	data_pkt->length = buffer_len + 2;

	UINT8* p_buf = data_pkt->data;
	UINT16_TO_STREAM(p_buf, buffer_len);
	memcpy(p_buf, buffer, buffer_len);

	ret = lc_act_send_data(device, ccb_idx, (UINT8*) data_pkt);
	return ret;
}
#endif //L2CAP_COC

/*********************************************************************
 * 						L2CAP Call Backs
 ********************************************************************/

void l2cap_connect_cb(connected_device_t *device, BOOLEAN result)
{
	logi("");
	if (result == TRUE)
	{
		init_no_guard_q(&l2cap_tx_q[device->idx]);
		device->data_rx_pkt.l2cap_data = NULL;
	}
	l2cap_csm_handler(L2CAP_EVT_LINK_CONNECTED, device, NULL);
}

#if (L2CAP_COC == TRUE)
void l2cap_coc_connect_cb(connected_device_t *device, BOOLEAN result, UINT16 cidx)
{
	logi("");
}
#endif //#if (L2CAP_COC == TRUE)

void l2cap_disconnect_cb(connected_device_t *device, BOOLEAN result)
{
	buffer_t *data_pkt;
	logi("");
	att_l2cap_disconnect_cb(device);
#if (L2CAP_COC == TRUE)
	UINT8 ccb_idx;
	for( ccb_idx = 0; ccb_idx < MAX_NUMBER_OF_L2CAP_COC_CHNL; ccb_idx ++)
	{
		if(g_local_adapter.l2cap_coc_channel_tbl[ccb_idx] != NULL)
		{
			if(g_local_adapter.l2cap_coc_channel_tbl[ccb_idx]->le_conn_id == device->idx)
			{
				l2cap_coc_conn_t* l2cap_coc_channel_tbl = g_local_adapter.l2cap_coc_channel_tbl[ccb_idx];
				if(l2cap_coc_channel_tbl->l2cap_coc_cb && l2cap_coc_channel_tbl->l2cap_coc_cb->disconnect_cmpl_cb)
				{
					l2cap_coc_channel_tbl->l2cap_coc_cb->disconnect_cmpl_cb(l2cap_coc_channel_tbl->owner_trans_id, device->idx, ccb_idx, STATUS_SUCCESS);
				}

				delete_l2cap_coc_tbl(ccb_idx);
			}
		}
	}
#endif
	data_pkt = (buffer_t*) dequeue(&l2cap_tx_q[device->idx]);
	while (data_pkt)
	{
		free_l2cap_buffer(data_pkt);
		data_pkt = (buffer_t*) dequeue(&l2cap_tx_q[device->idx]);
	}
	/* Clean up the queue and ccb */
	cleanup_q(&l2cap_tx_q[device->idx]);
	g_local_adapter.data_window += device->num_un_acked_l2cap_pkts;
	device->num_un_acked_l2cap_pkts = 0;
	if (result == TRUE)
		l2cap_csm_handler(L2CAP_EVT_LINK_DISCONNECTED, device, NULL);
}

/**
 * HCI layer calls this when a acl data is received for this device.
 */
void l2cap_recv_data(connected_device_t *device, UINT8 pb_flag, UINT8* data, UINT16 data_length)
{
	l2cap_recv_data_pkt_t data_pkt;
	data_pkt.pb_flag = pb_flag;
	data_pkt.data = data;
	data_pkt.data_length = data_length;
	logi("");
	logd(">>l2cap_recv_data:%p",data_pkt.data);
	l2cap_csm_handler(L2CAP_EVT_RECV_DATA, device, (UINT8*)&data_pkt);
}

void l2cap_recv_conn_param_update_evt(UINT8* buffer, UINT8 len)
{
	UINT16 acl_handle;
	UINT8* p_buf;
	UINT8 idx;
	connected_device_t *device;
	if (len != HCI_EVT_LE_CONN_PARAM_UPDATE_PARAM_SIZE)
	{
		/* Bad packet. We are in trouble. TODO: What next? */
		return;
	}
	p_buf = buffer;
	JUMP_CUSTOM_LEN(buffer, 1); /* Jump status */
	STREAM_TO_UINT16(acl_handle, buffer);
	idx = get_connected_device_idx_by_handle(acl_handle);

	if (idx == MAX_NUM_CONNECTED_DEVICE)
		return;

	device = g_local_adapter.connected_device[idx];
#if (PARANOID_STACK == TRUE)
	if (device == NULL)
		return;
#endif
	l2cap_csm_handler(L2CAP_EVT_CONNECT_PARAM_UPDATE_DONE, device, p_buf);
}

void* get_l2cap_free_buffer(UINT16 size)
{
	if (sizeof(buffer_t) + (UINT32)size + L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE > (UINT32)0xFFFF)
		return NULL;
	return alloc_queue_element(sizeof(buffer_t) + size + L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE, L2CAP_ALLOC);
}

void free_l2cap_buffer(void *buffer)
{
	dealloc_queue_element(buffer);
}

#if (L2CAP_COC == TRUE)

static void remove_all_pending_l2cap_pkt(void *queue, UINT16 cid)
{
	if (!queue)
		return ;
	queue_t *q = (queue_t*)queue;
	if (q->gaurd == TRUE)
		osa_mutex_get(&q->q_mutex);
	queue_elem_t *cur_node = q->list_head, *prev_node = NULL;
	UINT16 cur_cid;
/* Delete all the elements present in the front until
 *  we find an element with a different cid
 */
	while(cur_node != NULL)
	{
		buffer_t *data_pkt = (buffer_t*)cur_node->param;
		UINT8 *ptr = &data_pkt->data[data_pkt->offset + sizeof(UINT16)];
		STREAM_TO_UINT16(cur_cid, ptr);
		if(cur_cid == cid)
		{
			q->list_head = cur_node->next;
			dealloc(cur_node);
			cur_node = q->list_head;
		}
		else
			break;
	}
/* Search until we find an element with the matching cid
 *  then un-link it from the linked list and delete it
 */
	while(cur_node != NULL)
	{
		while(cur_node != NULL)
		{
			buffer_t *data_pkt = (buffer_t*)cur_node->param;
			UINT8 *ptr = &data_pkt->data[data_pkt->offset + sizeof(UINT16)];
			STREAM_TO_UINT16(cur_cid, ptr);
			if(cur_cid != cid)
			{
				prev_node = cur_node;
				cur_node = cur_node->next;
			}
			else
				break;
		}
		if(cur_node == NULL) return;
		if(prev_node == NULL) return;

	prev_node->next = cur_node->next;
	dealloc(cur_node);
	cur_node = prev_node->next;
	}
}

#endif /* L2CAP_COC == TRUE */
