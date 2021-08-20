/** @file
  Device utility functions implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "bt_types.h"
#include "device_struct.h"
#include "gap.h"
#include "l2cap.h"
#include "utils.h"

#define MODULE_DBG_LVL DEVICE_UTILS_DBG_LVL
#include "log.h"

/**
 * Create connected device instance with default values
 */
connected_device_t* create_connected_device(void)
{
	connected_device_t* connected_dev = (connected_device_t*) alloc(sizeof(connected_device_t));

	if (connected_dev == NULL )
		return NULL ;

	memset(connected_dev, 0, sizeof(connected_device_t));
	return connected_dev;
}

/*static void cleanup_tx_rx_q(queue_t* q)
{
	l2cap_data_pkt_t *data_pkt;
	while ((data_pkt = dequeue(q)) != NULL )
	{
		dealloc(data_pkt->data);
		dealloc(data_pkt);
	}
	cleanup_q(q);
}*/

static void cleanup_peer_data(connected_device_t* device)
{
	if(device->pending_att_packet.in_buffer)
		dealloc(device->pending_att_packet.in_buffer);
}

void delete_connected_device(UINT8 connected_device_list_idx)
{
	logd("Connected_device_list_idx: %u", connected_device_list_idx);
	if (g_local_adapter.connected_device[connected_device_list_idx] != NULL )
	{
		cleanup_peer_data(g_local_adapter.connected_device[connected_device_list_idx]);
		osa_delete_connected_device(connected_device_list_idx);
		g_local_adapter.connected_device[connected_device_list_idx] = NULL;
	}
}

void clear_connected_device_list(void)
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
		delete_connected_device(idx);
}

/**
 * Returns index of the connected device instance in the connected_device array
 * which matches the acl handle passed
 */
UINT8 get_connected_device_idx_by_handle(UINT16 acl_handle)
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		if (g_local_adapter.connected_device[idx] != NULL )
		{
			if (g_local_adapter.connected_device[idx]->acl_handle == acl_handle)
				return idx;
		}
	}
	return MAX_NUM_CONNECTED_DEVICE;
}

/**
 * Returns index of the connected device instance in the connected_device array
 * which matches the BD address passed
 */
UINT8 get_connected_device_idx_by_bdaddr(UINT8 *bdaddr)
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		if (g_local_adapter.connected_device[idx] != NULL )
		{
			if (memcmp(g_local_adapter.connected_device[idx]->bdaddr, bdaddr, BD_ADDR_LEN) == 0)
				return idx;
		}
	}
	return MAX_NUM_CONNECTED_DEVICE;
}

connected_device_t *get_connected_device_by_bdaddr(UINT8 *bdaddr)
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		if (g_local_adapter.connected_device[idx])
		{
			if (memcmp(g_local_adapter.connected_device[idx]->bdaddr, bdaddr, BD_ADDR_LEN) == 0)
				return g_local_adapter.connected_device[idx];
		}
	}
	return NULL ;
}

connected_device_t *get_connected_device_by_id_addr(UINT8 *bdaddr)
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		if (g_local_adapter.connected_device[idx])
		{
			if (memcmp(g_local_adapter.connected_device[idx]->id_addr.bdaddr, bdaddr,
					BD_ADDR_LEN) == 0)
				return g_local_adapter.connected_device[idx];
		}
	}
	return NULL ;
}
connected_device_t *get_connected_device_by_conn_id(UINT8 conn_id)
{
	if (conn_id >= MAX_NUM_CONNECTED_DEVICE)
		return NULL;
	return g_local_adapter.connected_device[conn_id];
}

BOOLEAN is_device_connected(UINT8 *bdaddr)
{
	connected_device_t *device = get_connected_device_by_bdaddr(bdaddr);
	if ((!device) || (!device->acl_handle))
		return FALSE;
	return TRUE;
}

/**
 * Returns the index of the free location in the connected device array.
 */
UINT8 find_first_free_connected_device_slot(void)
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		if (g_local_adapter.connected_device[idx] == NULL )
			return idx;
	}
	return MAX_NUM_CONNECTED_DEVICE;
}

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

UINT8 find_adv_scanresp_data_idx(gap_adv_scanresp_data_t **list, UINT8 type)
{
	UINT8 idx;

	for (idx = 0; idx < MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES; idx++)
	{
		if (list[idx] && list[idx]->type == type)
			return idx;
	}
	return MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES;
}

UINT8 find_first_free_adv_scanresp_data_slot(gap_adv_scanresp_data_t **list)
{
	UINT8 idx;

	for (idx = 0; idx < MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES; idx++)
	{
		if (!list[idx])
			return idx;
	}
	return MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES;
}

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

UINT8 get_idx_from_autoconn_list(UINT8 *bdaddr)
{
	UINT8 idx;

	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		if (g_local_adapter.gap_data.autoconn_dev[idx])
		{
			if (memcmp(g_local_adapter.gap_data.autoconn_dev[idx]->idaddr, bdaddr, BD_ADDR_LEN) == 0)
				return idx;
		}
	}
	return MAX_NUM_CONNECTED_DEVICE;
}

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

INT8 add_trans_id_to_auto_connect_list(autoconn_dev_t *device, trans_id_t trans_id)
{
	UINT8 idx;
	if(!device|| trans_id == INVALID_TRANS_ID)
		return STATUS_ERR_INVALID_PARAM;

	for(idx = 0; idx < MAX_NUMBER_OF_AUTO_CONNECT; idx++)
	{
		if(device->notify_list[idx] == trans_id)
		{
			/* Transaction ID is already present */
			return STATUS_SUCCESS;
		}
	}

	for(idx = 0; idx < MAX_NUMBER_OF_AUTO_CONNECT; idx++)
	{
		if(device->notify_list[idx] == INVALID_TRANS_ID)
		{
			device->notify_list[idx] = trans_id;
			return STATUS_SUCCESS;
		}
	}
	return STATUS_ERR_INSUFFICIENT_RESOURCES;
}
INT8 remove_trans_id_from_auto_connect_list(autoconn_dev_t *device, trans_id_t trans_id)
{
	UINT8 idx;
	if(!device || trans_id == INVALID_TRANS_ID)
		return STATUS_ERR_INVALID_PARAM;
	for(idx = 0; idx < MAX_NUMBER_OF_AUTO_CONNECT; idx++)
	{
		if(device->notify_list[idx] == trans_id)
		{
			device->notify_list[idx] = INVALID_TRANS_ID;
			return STATUS_SUCCESS;
		}
	}
	return STATUS_ERR_INVALID_PARAM;
}
void add_to_autoconn_list(UINT8 *bdaddr, UINT8 addr_type, trans_id_t trans_id)
{
	UINT8 idx, slot = MAX_NUM_CONNECTED_DEVICE;

	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		if (g_local_adapter.gap_data.autoconn_dev[idx])
		{
			if (!memcmp(bdaddr, g_local_adapter.gap_data.autoconn_dev[idx]->idaddr, BD_ADDR_LEN))
			{
				g_local_adapter.gap_data.autoconn_dev[idx]->idaddr_type = addr_type;
				add_trans_id_to_auto_connect_list(g_local_adapter.gap_data.autoconn_dev[idx], trans_id);
				return;
			}
		}
		else if (slot == MAX_NUM_CONNECTED_DEVICE)
			slot = idx;
	}

	if (slot == MAX_NUM_CONNECTED_DEVICE)
		return;

	g_local_adapter.gap_data.autoconn_dev[slot] = (autoconn_dev_t*) alloc(sizeof(autoconn_dev_t));
	for( idx = 0; idx < MAX_NUMBER_OF_AUTO_CONNECT; idx++)
		g_local_adapter.gap_data.autoconn_dev[slot]->notify_list[idx] = INVALID_TRANS_ID;
	memcpy(g_local_adapter.gap_data.autoconn_dev[slot]->idaddr, bdaddr, BD_ADDR_LEN);
	g_local_adapter.gap_data.autoconn_dev[slot]->idaddr_type = addr_type;
	g_local_adapter.gap_data.autoconn_dev[slot]->bond_idx = MAX_NUM_BONDED_DEVICE;
	if (get_connected_device_by_id_addr(bdaddr))
		g_local_adapter.gap_data.autoconn_dev[slot]->conn_state = DEVICE_CONNECTED;
	else
		g_local_adapter.gap_data.autoconn_dev[slot]->conn_state = DEVICE_DISCONNECTED;
	add_trans_id_to_auto_connect_list(g_local_adapter.gap_data.autoconn_dev[slot], trans_id);
}

void remove_from_autoconn_list(UINT8 *bdaddr, trans_id_t trans_id)
{
	UINT8 addr[BD_ADDR_LEN], idx, aidx;
	UINT8 *rev_bdaddr = addr;
	REVERSE_ARRAY_TO_STREAM(rev_bdaddr, bdaddr, BD_ADDR_LEN);

	idx = get_idx_from_autoconn_list(bdaddr);
	if (idx != MAX_NUM_CONNECTED_DEVICE)
	{
		remove_trans_id_from_auto_connect_list(g_local_adapter.gap_data.autoconn_dev[idx], trans_id);
		for (aidx = 0; aidx < MAX_NUMBER_OF_AUTO_CONNECT; aidx++)
			if(g_local_adapter.gap_data.autoconn_dev[idx]->notify_list[aidx] != INVALID_TRANS_ID)
				return;
		//No other app is registered for auto-connect to this device
		gap_remove_from_whitelist(g_local_adapter.gap_data.autoconn_dev[idx]->idaddr_type, addr);
		dealloc(g_local_adapter.gap_data.autoconn_dev[idx]);
		g_local_adapter.gap_data.autoconn_dev[idx] = NULL;
	}
}

BOOLEAN is_autoconn_list_empty()
{
	UINT8 idx;

	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		if (g_local_adapter.gap_data.autoconn_dev[idx] && (g_local_adapter.gap_data.autoconn_dev[idx]->conn_state == DEVICE_DISCONNECTED))
			return FALSE;
	}
	return TRUE;
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
#if (L2CAP_COC == TRUE)
/**
 * Create LE L2CAP connection oriented channel instance with default values
 */
l2cap_coc_conn_t* create_l2cap_coc_tbl(void)
{
	l2cap_coc_conn_t* l2cap_coc_tbl = (l2cap_coc_conn_t*) alloc(
			sizeof(l2cap_coc_conn_t));

	if (l2cap_coc_tbl == NULL )
		return NULL ;

	l2cap_coc_tbl->tx_usage_count = 0;
	l2cap_coc_tbl->state = LCS_CLOSED;
	return l2cap_coc_tbl;
}

void delete_l2cap_coc_tbl(UINT8 l2cap_coc_tbl_idx)
{
	logd("l2cap_coc_cb_idx: %u", l2cap_coc_tbl_idx);
	if (g_local_adapter.l2cap_coc_channel_tbl[l2cap_coc_tbl_idx] != NULL )
	{
		l2cap_coc_conn_send_data_t *data_pkt = dequeue(&g_local_adapter.l2cap_coc_channel_tbl[l2cap_coc_tbl_idx]->coc_data_tx_q);
		while(data_pkt)
		{
			dealloc_queue_element(data_pkt);
			data_pkt = NULL;
			data_pkt = dequeue(&g_local_adapter.l2cap_coc_channel_tbl[l2cap_coc_tbl_idx]->coc_data_tx_q);
		}
		cleanup_q(&g_local_adapter.l2cap_coc_channel_tbl[l2cap_coc_tbl_idx]->coc_data_tx_q);
		dealloc(g_local_adapter.l2cap_coc_channel_tbl[l2cap_coc_tbl_idx]);
		g_local_adapter.l2cap_coc_channel_tbl[l2cap_coc_tbl_idx] = NULL;
	}
}

void clear_l2cap_coc_tbl(void)
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUMBER_OF_L2CAP_COC_CHNL; idx++)
		delete_l2cap_coc_tbl(idx);
}

/**
 * Returns the index of the free location in the l2cap coc array.
 */
UINT8 find_first_free_l2cap_coc_tbl_slot(void)
{
	UINT8 idx = 0;
	for (idx = 0; idx < MAX_NUMBER_OF_L2CAP_COC_CHNL; idx++)
	{
		if (g_local_adapter.l2cap_coc_channel_tbl[idx] == NULL )
			break;
	}
	return idx;
}

UINT8 get_free_psm_registration_slot()
{
	UINT8 idx;
	for(idx = 0; idx < MAX_NUM_OF_REGISTERED_PSM; idx++)
	{
		if(g_local_adapter.l2cap_registered_psm_tbl[idx].psm == 0)
			break;
	}
	return idx;
}

l2cap_coc_conn_t* get_l2cap_coc_tbl_from_idx(UINT8 ccb_idx)
{
	if(ccb_idx >= MAX_NUMBER_OF_L2CAP_COC_CHNL)
	{
		return NULL;
	}

	return g_local_adapter.l2cap_coc_channel_tbl[ccb_idx];
}

UINT8 get_coc_ccb_by_l2cap_id(UINT8 conn_id,UINT8 l2cap_id)
{
	UINT8 idx;
	for(idx = 0; idx < MAX_NUMBER_OF_L2CAP_COC_CHNL; idx++)
	{
		if (g_local_adapter.l2cap_coc_channel_tbl[idx] != NULL )
			if(g_local_adapter.l2cap_coc_channel_tbl[idx]->l2cap_identifier == l2cap_id)
				break;
	}
	return idx;
}

UINT16 get_rcid_for_cid(UINT16 cid)
{
	UINT8 idx;
	for(idx = 0; idx < MAX_NUMBER_OF_L2CAP_COC_CHNL; idx++)
	{
		if (g_local_adapter.l2cap_coc_channel_tbl[idx] != NULL )
			if(g_local_adapter.l2cap_coc_channel_tbl[idx]->cid == cid)
				return g_local_adapter.l2cap_coc_channel_tbl[idx]->r_cid;
	}
	return 0;
}

UINT16 get_cid_for_rcid(UINT16 rcid, UINT8 le_conn_id)
{
	UINT8 idx;
	for(idx = 0; idx < MAX_NUMBER_OF_L2CAP_COC_CHNL; idx++)
	{
		if (g_local_adapter.l2cap_coc_channel_tbl[idx] != NULL )
			if(g_local_adapter.l2cap_coc_channel_tbl[idx]->r_cid == rcid && g_local_adapter.l2cap_coc_channel_tbl[idx]->le_conn_id == le_conn_id )
				return g_local_adapter.l2cap_coc_channel_tbl[idx]->cid;
	}
	return 0;
}

UINT8 get_psm_registration_idx(UINT16 psm)
{
	logi("");
	UINT8 idx = 0;
	for(idx = 0; idx < MAX_NUM_OF_REGISTERED_PSM; idx++)
		if(g_local_adapter.l2cap_registered_psm_tbl[idx].psm == psm)
			break;
	return idx;
}

UINT8 check_psm_already_in_use(UINT16 psm, UINT8 conn_id)
{
	logi("");
	UINT8 ccb_idx;
	for(ccb_idx = 0; ccb_idx < MAX_NUMBER_OF_L2CAP_COC_CHNL; ccb_idx++)
	{
		if(g_local_adapter.l2cap_coc_channel_tbl[ccb_idx] != NULL)
		{
			if((g_local_adapter.l2cap_coc_channel_tbl[ccb_idx]->psm == psm) &&
					(g_local_adapter.l2cap_coc_channel_tbl[ccb_idx]->le_conn_id == conn_id))
				break;
		}
	}
	return ccb_idx;
}

UINT8 get_handle_from_coc_table_for_cid(UINT16 cid)
{
	logi("");
	UINT8 ccb_idx;
	for(ccb_idx = 0; ccb_idx < MAX_NUMBER_OF_L2CAP_COC_CHNL; ccb_idx++)
		if(g_local_adapter.l2cap_coc_channel_tbl[ccb_idx] != NULL)
			if(g_local_adapter.l2cap_coc_channel_tbl[ccb_idx]->cid == cid)
				break;
	return ccb_idx;
}

UINT8 get_handle_from_coc_table_for_cids(UINT16 cid, UINT16 r_cid)
{
	logi("");
	UINT8 ccb_idx;
	for(ccb_idx = 0; ccb_idx < MAX_NUMBER_OF_L2CAP_COC_CHNL; ccb_idx++)
		if(g_local_adapter.l2cap_coc_channel_tbl[ccb_idx] != NULL)
			if(g_local_adapter.l2cap_coc_channel_tbl[ccb_idx]->cid == cid
					&& g_local_adapter.l2cap_coc_channel_tbl[ccb_idx]->r_cid == r_cid)
				break;
	return ccb_idx;
}

l2cap_coc_conn_send_data_t* get_free_coc_tx_data_pool(UINT8 ccb_idx)
{
	logi("");
	l2cap_coc_conn_t* l2cap_coc_channel_tbl = get_l2cap_coc_tbl_from_idx(ccb_idx);
	if(l2cap_coc_channel_tbl == NULL)
	{
		loge("Invalid le l2cap coc connection id");
		return NULL;
	}
	if(l2cap_coc_channel_tbl->tx_usage_count < MAX_NUMBER_OF_L2CAP_COC_TX_BUFFER)
	{
		return (l2cap_coc_conn_send_data_t*)alloc_queue_element(sizeof(l2cap_coc_conn_send_data_t), L2CAP_ALLOC);
	}
	return NULL;
}

BOOLEAN is_psm_valid(UINT16 psm)
{
	logi("");
	/*
	PSMs shall be in the range of 0x0001 to 0x00FF
	*/
	logd("psm:%04x",psm);
	if( (psm < 0x0001) || (psm > 0x00FF))
		return FALSE;
	return TRUE;
}

#if 0
INT8 coc_unregister_psm(connected_device_t *device, UINT8 app_id, UINT16 psm)
{
	UINT8 idx=0;
	for(idx=0; idx<MAX_NUM_OF_PSM_PER_DEV; idx++)
		if(device->l2cap_coc_app_psm_map[idx].app_id == app_id && device->l2cap_coc_app_psm_map[idx].psm == psm)
		{
			device->l2cap_coc_app_psm_map[idx].app_id = 0;
			device->l2cap_coc_app_psm_map[idx].psm = 0;
			device->l2cap_coc_app_psm_map[idx].connected = FALSE;
			return STATUS_SUCCESS;
		}
	return STATUS_ERR_INVALID_PARAM;
}
#endif
#endif //L2CAP_COC

UINT8 increament_l2cap_identifier(UINT8 identifier)
{
	if(identifier == 255)
		identifier = 1;
	else
		identifier++;

	return identifier;
}
/**********************************************************
 *
 * Utility functions for enqueue and dequeue in pending queue
 *
 * ********************************************************/


