/** @file
  GAP layer implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "device_struct.h"
#include "interface.h"
#include "profile_mgr.h"
#include "device_mgr.h"
#include "hci_host.h"
#include "l2cap.h"
#include "config_host.h"
#include "gap.h"

#define MODULE_DBG_LVL GAP_DBG_LVL
#include "log.h"

/********** Static function declaration start **********/

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static INT8 gap_start_advertise(UINT32 timeout_msec, UINT8 type, UINT8 flags, UINT8 *remote_bd_addr, UINT8 addr_type, UINT16 adv_int_min, UINT16 adv_int_max, BOOLEAN use_whitelist, BOOLEAN background);
static INT8 gap_stop_advertise();

#if 0
#if (PRIVACY_FEATURE)
static BOOLEAN gap_direct_adv_addr_needs_resolution(UINT32 timeout_msec, UINT8 type, UINT8 flags, UINT8 *remote_bd_addr, UINT8 addr_type, BOOLEAN use_whitelist, BOOLEAN background);
#endif /* PRIVACY_FEATURE */
#endif

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

static INT8 gap_start_scan(trans_id_t trans_id, UINT32 timeout_msec, BOOLEAN active, BOOLEAN limited, BOOLEAN use_whitelist, BOOLEAN background, UINT16 scan_int, UINT16 scan_win, UINT16* filter_uuids, BOOLEAN user_triggered);
static INT8 gap_stop_scan(BOOLEAN user_triggered);
static INT8 device_found();
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

#if (PRIVACY_FEATURE)

static void rpa_timeout_handler(osa_timer_arg_t arg);

#endif /* PRIVACY_FEATURE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static BOOLEAN update_connected_device(connected_device_t *device);

#endif /* (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)*/

#if (CONTROLLER_PRIVACY)

static INT8 gap_add_to_resolvinglist(UINT8 peer_addr_type, UINT8 *peer_bdaddr, UINT8 *peer_irk, UINT8 *local_irk);
static INT8 gap_remove_from_resolvinglist(UINT8 peer_addr_type, UINT8 *peer_bdaddr);
static INT8 gap_clear_resolvinglist();

#endif /* CONTROLLER_PRIVACY */

static INT8 gap_clear_whitelist();

/********** Static function declaration end **********/

/********** State handling functions start **********/

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static inline void adapter_enter_adv_state(UINT8 state)
{
	g_local_adapter.gap_data.adapter_state &= ~(GAP_ADAPTER_STATE_MASK<<GAP_ADAPTER_STATE_ADV_OFFSET);
	g_local_adapter.gap_data.adapter_state |= state;
}

static inline BOOLEAN adapter_is_in_adv_state(UINT8 state)
{
	return ((g_local_adapter.gap_data.adapter_state & (GAP_ADAPTER_STATE_MASK<<GAP_ADAPTER_STATE_ADV_OFFSET)) == state);
}

static void remove_all_adv_scanresp_data();

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

static void do_cleanup();

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

static inline void adapter_enter_scn_state(UINT8 state)
{
	g_local_adapter.gap_data.adapter_state &= ~(GAP_ADAPTER_STATE_MASK<<GAP_ADAPTER_STATE_SCN_OFFSET);
	g_local_adapter.gap_data.adapter_state |= state;
}

static inline BOOLEAN adapter_is_in_scn_state(UINT8 state)
{
	return ((g_local_adapter.gap_data.adapter_state & (GAP_ADAPTER_STATE_MASK<<GAP_ADAPTER_STATE_SCN_OFFSET)) == state);
}

static inline void adapter_enter_bgscanning_state()
{
	g_local_adapter.gap_data.adapter_state |= GAP_ADAPTER_STATE_BGSCAN_ACTIVE;
}

static inline void adapter_exit_bgscanning_state()
{
	g_local_adapter.gap_data.adapter_state &= ~GAP_ADAPTER_STATE_BGSCAN_ACTIVE;
}

static inline BOOLEAN adapter_is_bgscanning()
{
	return (g_local_adapter.gap_data.adapter_state & GAP_ADAPTER_STATE_BGSCAN_ACTIVE);
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

static inline void adapter_enter_disabling_state()
{
	g_local_adapter.gap_data.adapter_state |= GAP_ADAPTER_STATE_DISABLING;
}

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static inline BOOLEAN adapter_is_disabling()
{
	return (g_local_adapter.gap_data.adapter_state & GAP_ADAPTER_STATE_DISABLING)? TRUE:FALSE;
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

static void device_set_state(UINT8 connected_device_idx, UINT8 state)
{
	connected_device_t *device;
	if(connected_device_idx >= MAX_NUM_CONNECTED_DEVICE)
		return;

	device = g_local_adapter.connected_device[connected_device_idx];

	if (device)
		device->gap_connection_state = state;
}

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static BOOLEAN device_is_in_state(UINT8 connected_device_idx, UINT8 state)
{
	connected_device_t *device;
	if(connected_device_idx < MAX_NUM_CONNECTED_DEVICE)
	{
		device = g_local_adapter.connected_device[connected_device_idx];
		if (device && device->gap_connection_state == state)
			return TRUE;
	}
	return FALSE;
}

static UINT8 device_get_state(UINT8 connected_device_idx)
{
	connected_device_t *device = g_local_adapter.connected_device[connected_device_idx];
#if (PARANOID_STACK == TRUE)
	if (device)
#endif
		return device->gap_connection_state;
#if (PARANOID_STACK == TRUE)
	return GAP_CONNECTION_STATE_INVALID;
#endif
}

static BOOLEAN any_device_is_in_state(UINT8 state)
{
	connected_device_t *device;
	UINT8 idx;

	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		device = g_local_adapter.connected_device[idx];
		if (device && device->gap_connection_state == state)
			return TRUE;
	}

	return FALSE;
}

static UINT8 get_first_device_in_state(UINT8 state)
{
	connected_device_t *device;
	UINT8 idx;

	for (idx = 0; idx < MAX_NUM_CONNECTED_DEVICE; idx++)
	{
		device = g_local_adapter.connected_device[idx];
		if (device && device->gap_connection_state == state)
			break;
	}

	return idx;
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

static inline BOOLEAN conn_param_is_valid(UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout)
{
	/* As per HCI spec 7.8.12 */
	return (interval_min >= 0x6 && interval_min <= 0xC80
				&& interval_min <= interval_max && interval_max >= 0x6
				&& interval_max <= 0xC80 && conn_latency <= 0x1F3
				&& (sup_timeout * 10) > (125 * (interval_max/100) * (conn_latency + 1) * 2)
				&& sup_timeout >= 0xA && sup_timeout <= 0xC80
				&& (4 * sup_timeout) > ((1 + conn_latency) * interval_max));
}

static void dump_oplist()
{
#if (MODULE_DBG_LVL > DBG_LVL_DEBUG)
	hex_dump("GAP oplist: ", g_local_adapter.gap_data.operation_list, GAP_MAX_NUM_OPERATIONS);
#endif
}

static void start_operation(UINT8 operation)
{
	UINT8 idx, *oplist = &g_local_adapter.gap_data.operation_list[0];
	logi("Op = %d", operation);

	for (idx = 0; idx < GAP_MAX_NUM_OPERATIONS; idx++)
	{
		if (oplist[idx] == GAP_OPERATION_NONE)
		{
			if (operation != GAP_OPERATION_ADVERTISING)
				if (idx == 0 || (idx == 1 && oplist[0] == GAP_OPERATION_ADVERTISING))
					logi("************************* LEAVING IDLE, STARTING %d *************************", operation);
			oplist[idx] = operation;
			dump_oplist();
			return;
		}
	}
}

static void end_operation(UINT8 operation)
{
	UINT8 idx, nidx, *oplist = &g_local_adapter.gap_data.operation_list[0];
	trans_id_t trans_id;
	logi("Op = %d", operation);

	for (idx = 0; idx < GAP_MAX_NUM_OPERATIONS; idx++)
	{
		if (oplist[idx] == operation)
		{
			nidx = idx + 1;
			while ((nidx < GAP_MAX_NUM_OPERATIONS) && (oplist[nidx] != GAP_OPERATION_NONE))
			{
				oplist[nidx-1] = oplist[nidx];
				nidx++;
			}
			oplist[nidx-1] = GAP_OPERATION_NONE;

			if (operation != GAP_OPERATION_ADVERTISING)
			{
				if ((oplist[0] == GAP_OPERATION_NONE) || (oplist[0] == GAP_OPERATION_ADVERTISING && oplist[1] == GAP_OPERATION_NONE))
				{
					logi("************************* STOPPING %d, ENTERING IDLE *************************", operation);
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
					if((!is_autoconn_list_empty()) && (!adapter_is_disabling()))
					{
						g_local_adapter.gap_data.idle_scan_in_progress = TRUE;
						trans_id = INVALID_TRANS_ID;
						add_appid_to_trans_id(&trans_id, MAX_NUMBER_OF_APP);
						gap_start_scan(trans_id, 0, TRUE, FALSE, TRUE, TRUE, 0, 0, NULL, FALSE);
					}
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
				}
			}
			dump_oplist();

			if (oplist[0] == GAP_OPERATION_DISABLING && oplist[1] == GAP_OPERATION_NONE)
			{
				logi("************************* DISABLE COMPLETE *************************");
				do_cleanup();
			}

			return;
		}
	}
}

static UINT8 get_root_operation()
{
	UINT8 *oplist = &g_local_adapter.gap_data.operation_list[0];

	if (oplist[0] == GAP_OPERATION_ADVERTISING)
		return oplist[1];

	return oplist[0];
}

static void prep_whitelist_update()
{
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	BOOLEAN adv_stop = adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_ENABLED) && g_local_adapter.gap_data.adv_use_whitelist;
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	BOOLEAN scn_stop = adapter_is_in_scn_state(GAP_ADAPTER_STATE_SCN_ENABLED) && g_local_adapter.gap_data.scan_use_whitelist;
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

	start_operation(GAP_OPERATION_UPDATING_WHITELIST);

	if (
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
			adv_stop ||
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
			scn_stop ||
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
			0)
		g_local_adapter.gap_data.prev_adapter_state = g_local_adapter.gap_data.adapter_state;

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	if (adv_stop)
		gap_stop_advertise();
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	if (scn_stop)
		gap_stop_scan(FALSE);
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
}

#if (CONTROLLER_PRIVACY)

static void prep_resolvinglist_update()
{
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	BOOLEAN adv_stop = adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_ENABLED);
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	BOOLEAN scn_stop = adapter_is_in_scn_state(GAP_ADAPTER_STATE_SCN_ENABLED);
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

	start_operation(GAP_OPERATION_UPDATING_RL);

	if (
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
			adv_stop ||
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
			scn_stop ||
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
			0)
		g_local_adapter.gap_data.prev_adapter_state = g_local_adapter.gap_data.adapter_state;

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	if (adv_stop)
		gap_stop_advertise();
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	if (scn_stop)
		gap_stop_scan(FALSE);
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
}

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
//TO DO : enable direct advertisement
#if 0
static BOOLEAN is_operation_running(UINT8 operation)
{
	UINT8 idx;
	for (idx = 0; idx < GAP_MAX_NUM_OPERATIONS; idx++)
		if (g_local_adapter.gap_data.operation_list[idx] == operation)
			return TRUE;
	return FALSE;
}
#endif
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#endif /* CONTROLLER_PRIVACY */

static BOOLEAN is_only_operation(UINT8 operation)
{
	UINT8 *oplist = &g_local_adapter.gap_data.operation_list[0];

	return (oplist[0] == operation && oplist[1] == GAP_OPERATION_NONE);
}

static void clear_all_operations()
{
  UINT8 *oplist = &g_local_adapter.gap_data.operation_list[0];
  memset (oplist, GAP_OPERATION_NONE, sizeof (g_local_adapter.gap_data.operation_list));
}

/********** State handling functions end **********/

/********** Timeout handling functions start **********/

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static void adv_timeout_handler(osa_timer_arg_t arg)
{
	gap_stop_advertise();
}

static void adv_timeout_cb(osa_timer_arg_t arg)
{
	timer_expire_evt_msg(adv_timeout_handler, arg);
}

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

static void scan_timeout_handler(osa_timer_arg_t arg)
{
	gap_stop_scan(TRUE);
}

static void scan_timeout_cb(osa_timer_arg_t arg)
{
	timer_expire_evt_msg(scan_timeout_handler, arg);
}

void scan_res_timeout_handler(osa_timer_arg_t arg)
{
	device_found();
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static void finish_transac_and_process_new_req()
{
	gap_req_handler(NULL);
}
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (HOST_PRIVACY)
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static void gap_conn_comp_rpa_resolution_cb(UINT8 *remote_bd_addr, BOOLEAN local, UINT8 bonded_idx, UINT8 status)
{
	UINT8 didx;
	BOOLEAN fromremote;
	didx = get_connected_device_idx_by_bdaddr(remote_bd_addr);
	if (didx != MAX_NUM_CONNECTED_DEVICE)
	{
		connected_device_t *device = g_local_adapter.connected_device[didx];
		if(device)
		{
			if (status == STATUS_SUCCESS)
			{
				logd("Resolution success");
				hex_dump("BDADDR:",remote_bd_addr, BD_ADDR_LEN);
				logd("Index = %d", bonded_idx);
				device->is_bonded = TRUE;
				device->bonded_idx = bonded_idx;
				memcpy(device->id_addr.bdaddr, g_local_adapter.resolving_list[bonded_idx].entry.peer_id_info.id_addr, BD_ADDR_LEN);
				device->id_addr.type = g_local_adapter.resolving_list[bonded_idx].entry.peer_id_info.id_addr_type;
			}
			fromremote = update_connected_device(device);
			if (!fromremote)
			{
				finish_transac_and_process_new_req();
				end_operation(GAP_OPERATION_CONNECTING);
			}
		}
	}
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

static void gap_rpa_adv_resolution_cb(UINT8 *bd_addr, BOOLEAN local, UINT8 bonded_idx, UINT8 status)
{
	logi("");

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	//TO DO : Directed advertisement to be enabled
#if 0
	if (is_operation_running(GAP_OPERATION_RESOLVING_DIRECT_ADDR))
	{
		/* A resolution operation for directed advertisement InitA was ongoing */

		/* If resolution was successful, and CAR is supported by peer, proceed with advertisement */
		if (status == STATUS_SUCCESS)
		{
			if (g_local_adapter.bonded_device[bonded_idx]->car_supported == PEER_CAR_SUPPORT_PRESENT)
			{
				logd("Resolution successful, remote device supports CAR");
				UINT8 bdaddr[BD_ADDR_LEN];
				UINT8 *rev_bdaddr = bdaddr;
				REVERSE_ARRAY_TO_STREAM(rev_bdaddr, g_local_adapter.bonded_device[bonded_idx]->bdaddr, BD_ADDR_LEN);
				gap_start_advertise(g_local_adapter.gap_data.adv_timeout_msec, g_local_adapter.gap_data.adv_type, g_local_adapter.gap_data.adv_flags, bdaddr, g_local_adapter.bonded_device[bonded_idx]->id_addr_type+2, g_local_adapter.gap_data.adv_int_min, g_local_adapter.gap_data.adv_int_max, g_local_adapter.gap_data.adv_use_whitelist, g_local_adapter.gap_data.adv_is_background);
				return;
			}
			loge("Cannot do Directed Advertisement since remote device does not support CAR!");
			end_operation(GAP_OPERATION_RESOLVING_DIRECT_ADDR);
			return;
		}

		/* Else, fail the advertisement */
		loge("Cannot do Directed Advertisement since remote device could not be resolved!");
		end_operation(GAP_OPERATION_RESOLVING_DIRECT_ADDR);
		return;
	}
#endif
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

	if (!local)
	{
		/* RPA resolution of remote device was going on */
		if (status == STATUS_SUCCESS)
		{
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
			/* Auto-connect if required */
			UINT8 aidx = get_idx_from_autoconn_list(bd_addr);
			interface_req_elem_t *req ;
			pm_connect_param_t* param ;
			if (aidx != MAX_NUM_CONNECTED_DEVICE)
			{
				logd("Auto-connecting...");
				g_local_adapter.gap_data.autoconn_dev[aidx]->bond_idx = bonded_idx;
				req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_CONNECT, 0, sizeof(pm_connect_param_t));
				if(req == NULL)
					return;
				param = (pm_connect_param_t*)req->parameter;
				param->trans_id = INVALID_TRANS_ID;
				param->auto_reconnect = TRUE;
				param->addr_type = g_local_adapter.gap_data.autoconn_dev[aidx]->addr_type;
				memcpy(param->remote_bd_addr, bd_addr, BD_ADDR_LEN);
				param->scan_int = SCAN_CONN_INTERVAL;
				param->scan_win = SCAN_CONN_WINDOW;
				param->conn_int_min = CONNECTION_INTERVAL_MIN;
				param->conn_int_max = CONNECTION_INTERVAL_MAX;
				param->conn_lat = CONNECTION_LATENCY;
				param->sup_timeout = CONNECTION_SUP_TIMEOUT;
				gap_req_handler(req);
			}
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
		}
	}
	else
	{
		/* RPA resolution of local device was going on */
		char bdaddr_str[BD_ADDR_STR_LEN];
		BDADDR_TO_STRING(bdaddr_str, bd_addr);
		if (status == STATUS_SUCCESS)
		{
			/* If we managed to resolve the InitA, then the Directed Advertisement was indeed meant for us */
			logd("Address %s was successfully resolved as local address", bdaddr_str);
		}
		else
		{
			/* The application already got a report for this advertiser */
			/* FIXME: Let the application know somehow that the advertiser is invalid */
			logw("Address %s used by advertiser is NOT our local address!", bdaddr_str);
		}
	}
}

static interface_req_elem_t* create_req_for_rpa_adv_resolution(UINT8 *bdaddr, BOOLEAN local)
{
	interface_req_elem_t *req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_RPA_RESOLVE, 0, sizeof(smpm_rpa_resolve_param_t));
	smpm_rpa_resolve_param_t* param;
	if(req == NULL)
		return NULL;
	param = (smpm_rpa_resolve_param_t*)req->parameter;
	memcpy(param->rpa, bdaddr, BD_ADDR_LEN);
	param->local = local;
	param->cback = gap_rpa_adv_resolution_cb;
	return req;
}
#endif
#if (PRIVACY_FEATURE == TRUE)
static interface_req_elem_t* create_req_for_rpa_generation()
{
	interface_req_elem_t *req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_RPA_GENERATE, 0, 0);
	if (req == NULL )
		return NULL;
	return req;
}
#endif
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
#if (HOST_PRIVACY)
static interface_req_elem_t* create_req_for_conn_comp_rpa_resolution(UINT8 *remote_bdaddr)
{
	interface_req_elem_t *req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_RPA_RESOLVE, 0, sizeof(smpm_rpa_resolve_param_t));
	smpm_rpa_resolve_param_t* param;
	if(req == NULL)
		return NULL;
	param = (smpm_rpa_resolve_param_t*)req->parameter;
	memcpy(param->rpa, remote_bdaddr, BD_ADDR_LEN);
	param->cback = gap_conn_comp_rpa_resolution_cb;
	return req;
}
#endif /* HOST_PRIVACY */
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (PRIVACY_FEATURE == TRUE)
static void rpa_timeout_cb(osa_timer_arg_t arg)
{
	timer_expire_evt_msg(rpa_timeout_handler, arg);
}

static void rpa_timeout_handler(osa_timer_arg_t arg)
{
	smpm_req_handler(create_req_for_rpa_generation());
	osa_start_timer(&g_local_adapter.gap_data.rpa_gen_timer, GAP_RPA_GEN_TIMER, (GAP_RPA_GEN_COMMAND_TIMEOUT_SEC * 1000), rpa_timeout_cb, 0);
}
#endif

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static void remote_command_timer_stop(UINT8 connected_device_idx);

static INT8 disconnect_one_device();

static void remote_command_timeout_handler(osa_timer_arg_t arg)
{
	//UINT8 connected_device_list_idx = (UINT8) osa_get_timer_arg_val(arg);
	UINT8 connected_device_list_idx = g_local_adapter.gap_data.remote_op_device;
	connected_device_t *device = g_local_adapter.connected_device[connected_device_list_idx];
	char bdaddr_str[BD_ADDR_STR_LEN];
	g_local_adapter.gap_data.remote_op_device = MAX_NUM_CONNECTED_DEVICE;

	if (!device)
	{
		loge("Device not present in connected list!");
		return;
	}

	BDADDR_TO_STRING(bdaddr_str, device->bdaddr);
	remote_command_timer_stop(connected_device_list_idx);

	switch (device_get_state(connected_device_list_idx))
	{
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	case GAP_CONNECTION_STATE_ACL_CONNECTING:
		loge("Connection to %s timed out!", bdaddr_str);
		hci_ble_cancel_create_ll_conn();
		break;
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	case GAP_CONNECTION_STATE_ACL_DISCONNECTING:
		loge("Disconnection with %s timed out!", bdaddr_str);
		pm_disconnect_cb(device, GAP_DISCONNECT_REASON_TERM_CONNECTION_USER);
		device_set_state(connected_device_list_idx, GAP_CONNECTION_STATE_ACL_DISCONNECTED);
		delete_connected_device(connected_device_list_idx);
		end_operation(GAP_OPERATION_DISCONNECTING);
		if (adapter_is_disabling())
			disconnect_one_device();
		break;
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
	case GAP_CONNECTION_STATE_LINK_PARAM_UPDATING:
		loge("Connection parameter update for %s timed out!", bdaddr_str);
		device_set_state(connected_device_list_idx, GAP_CONNECTION_STATE_ACL_CONNECTED);
		end_operation(GAP_OPERATION_UPDATING_CONN_PARAMS);
		break;
	default:
		loge("GAP is in incorrect timeout state %u for %s!", device_get_state(connected_device_list_idx), bdaddr_str);
	}
}

static void remote_command_timeout_cb(osa_timer_arg_t arg)
{
	timer_expire_evt_msg(remote_command_timeout_handler, arg);
}

void remote_command_timer_start(UINT8 connected_device_idx)
{
	osa_timer_t *timer = &(g_local_adapter.connected_device[connected_device_idx]->gap_remote_command_timer);
	g_local_adapter.gap_data.remote_op_device = connected_device_idx;

	if (osa_create_timer(timer, GAP_REMOTE_CMD_TIMER, GAP_REMOTE_CMD_TIMER_ISR, sizeof(GAP_REMOTE_CMD_TIMER)/sizeof(osa_timer_static_t), remote_command_timeout_cb, 0) == 0)
	{
		g_local_adapter.connected_device[connected_device_idx]->remote_command_timer_created = TRUE;
		osa_start_timer(timer, GAP_REMOTE_CMD_TIMER, (GAP_REMOTE_COMMAND_TIMEOUT_SEC * 1000), remote_command_timeout_cb, 0);
	}
}

static void remote_command_timer_stop(UINT8 connected_device_idx)
{
	osa_timer_t *timer = &(g_local_adapter.connected_device[connected_device_idx]->gap_remote_command_timer);
	if (g_local_adapter.gap_data.remote_op_device == connected_device_idx)
		g_local_adapter.gap_data.remote_op_device = MAX_NUM_CONNECTED_DEVICE;

	if (g_local_adapter.connected_device[connected_device_idx]->remote_command_timer_created)
	{
		if (osa_is_timer_active(timer, GAP_REMOTE_CMD_TIMER, 0))
			osa_stop_timer(timer, GAP_REMOTE_CMD_TIMER, 0);

		osa_delete_timer(timer, GAP_REMOTE_CMD_TIMER);
		g_local_adapter.connected_device[connected_device_idx]->remote_command_timer_created = FALSE;
	}
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

/********** Timeout handling functions end **********/

/********** Utility functions start **********/

static INT8 gap_enqueue_req_in_pending_queue(interface_req_elem_t *incoming_req)
{
	logi("incoming_req:%p", incoming_req);
	if (!incoming_req)
		return STATUS_ERR_INVALID_PARAM;
	return enqueue(&g_local_adapter.gap_data.pending_req_q, (void*)incoming_req);
}

static interface_req_elem_t* gap_dequeue_req_from_pending_queue()
{
	return dequeue(&g_local_adapter.gap_data.pending_req_q);
}

static void gap_dequeue_and_cleanup_from_pending_queue()
{
	interface_req_elem_t* req = (interface_req_elem_t*)dequeue(&g_local_adapter.gap_data.pending_req_q);
	if (req)
	{
		dealloc_queue_element(req);
	}
}

static interface_req_elem_t* get_req_to_process()
{
	return (interface_req_elem_t*)pick_front(&g_local_adapter.gap_data.pending_req_q);
}

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static UINT8 get_formatted_adv_data(UINT8 *adv_data)
{
	UINT8 idx, len, total_len = 0;

	for (idx = 0; idx < MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES; idx++)
	{
		if (g_local_adapter.gap_data.adv_data[idx])
		{
			if (total_len + g_local_adapter.gap_data.adv_data[idx]->data_length + 2 > ADV_DATA_LEN)
				break;
			adv_data[0] = g_local_adapter.gap_data.adv_data[idx]->data_length + 1; //Include size of type
			adv_data[1] = g_local_adapter.gap_data.adv_data[idx]->type;
			memcpy(&adv_data[2], g_local_adapter.gap_data.adv_data[idx]->data, g_local_adapter.gap_data.adv_data[idx]->data_length);
			len = g_local_adapter.gap_data.adv_data[idx]->data_length + 2; //Include size of type, length
			total_len += len;
			adv_data += len;
		}
	}
	return total_len;
}

static UINT8 get_formatted_scanresp_data(UINT8 *scanresp_data)
{
	UINT8 idx, type, len = 0, total = 0;

	for (idx = 0; idx < MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES; idx++)
	{
		if (g_local_adapter.gap_data.scanresp_data[idx])
		{
			type = g_local_adapter.gap_data.scanresp_data[idx]->type;
			if (type == GAP_ADV_DATA_FLAGS || type == GAP_ADV_DATA_APPEARANCE) //Not allowed in scan response
				continue;
			if (total + g_local_adapter.gap_data.scanresp_data[idx]->data_length + 2 > ADV_DATA_LEN)
				break;
			scanresp_data[0] = g_local_adapter.gap_data.scanresp_data[idx]->data_length + 1; //Include size of type
			scanresp_data[1] = g_local_adapter.gap_data.scanresp_data[idx]->type;
			memcpy(&scanresp_data[2], g_local_adapter.gap_data.scanresp_data[idx]->data, g_local_adapter.gap_data.scanresp_data[idx]->data_length);
			len = g_local_adapter.gap_data.scanresp_data[idx]->data_length + 2; //Include size of type, length
			scanresp_data += len;
			total += len;
		}
	}
	return total;
}

static UINT8 add_new_adv_scanresp_data(gap_adv_scanresp_data_t **list, UINT8 length, UINT8 type, UINT8 *data)
{
	UINT8 idx = find_first_free_adv_scanresp_data_slot(list);
#if (PARANOID_STACK == TRUE)
	if (idx < MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES)
#endif
	{
		list[idx] = (gap_adv_scanresp_data_t*) alloc(sizeof(gap_adv_scanresp_data_t));
		list[idx]->data_length = length;
		list[idx]->type = type;
		list[idx]->data = (UINT8*) alloc(length);
		memcpy(list[idx]->data, data, length);
	}
	return idx;
}

static UINT8 overwrite_adv_scanresp_data(gap_adv_scanresp_data_t **list, UINT8 length, UINT8 type, UINT8 *data)
{
	UINT8 idx = find_adv_scanresp_data_idx(list, type);
#if (PARANOID_STACK == TRUE)
	if (idx < MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES)
#endif
	{
		list[idx]->data_length = length;
		list[idx]->type = type;
		dealloc(list[idx]->data);
		list[idx]->data = (UINT8*) alloc(length);
		memcpy(list[idx]->data, data, length);
	}
	return idx;
}

static void remove_all_adv_scanresp_data()
{
	UINT8 idx;

	for (idx = 0; idx < MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES; idx++)
	{
		if (g_local_adapter.gap_data.adv_data[idx])
		{
			dealloc(g_local_adapter.gap_data.adv_data[idx]->data);
			dealloc(g_local_adapter.gap_data.adv_data[idx]);
			g_local_adapter.gap_data.adv_data[idx] = NULL;
		}
		if (g_local_adapter.gap_data.scanresp_data[idx])
		{
			dealloc(g_local_adapter.gap_data.scanresp_data[idx]->data);
			dealloc(g_local_adapter.gap_data.scanresp_data[idx]);
			g_local_adapter.gap_data.scanresp_data[idx] = NULL;
		}
	}
}

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static void adapter_restore_prev_state()
{
	if (adapter_is_disabling())
	{
		g_local_adapter.gap_data.prev_adapter_state = 0;
		return;
	}

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	if (!adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_ENABLED))
		if ((g_local_adapter.gap_data.prev_adapter_state & GAP_ADAPTER_STATE_ADV_ENABLED) == GAP_ADAPTER_STATE_ADV_ENABLED)
			gap_start_advertise(g_local_adapter.gap_data.adv_timeout_msec, g_local_adapter.gap_data.adv_type, g_local_adapter.gap_data.adv_flags, g_local_adapter.gap_data.adv_remote_bd_addr, g_local_adapter.gap_data.adv_addr_type, g_local_adapter.gap_data.adv_int_min, g_local_adapter.gap_data.adv_int_max, g_local_adapter.gap_data.adv_use_whitelist, g_local_adapter.gap_data.adv_is_background);
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	if (!adapter_is_in_scn_state(GAP_ADAPTER_STATE_SCN_ENABLED))
		if ((g_local_adapter.gap_data.prev_adapter_state & GAP_ADAPTER_STATE_SCN_ENABLED) == GAP_ADAPTER_STATE_SCN_ENABLED)
			gap_start_scan(g_local_adapter.gap_data.scan_req_trans_id, g_local_adapter.gap_data.scan_timeout_msec, g_local_adapter.gap_data.scan_isactive, g_local_adapter.gap_data.scan_is_limited, g_local_adapter.gap_data.scan_use_whitelist, g_local_adapter.gap_data.scan_is_background, g_local_adapter.gap_data.scan_int, g_local_adapter.gap_data.scan_win, g_local_adapter.gap_data.scan_filter_uuids, FALSE);
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

	g_local_adapter.gap_data.prev_adapter_state = 0;
}

static INT8 disconnect_one_device()
{
	UINT8 id;

	for (id = 0; id < MAX_NUM_CONNECTED_DEVICE; id++)
		if (g_local_adapter.connected_device[id])
			return gap_terminate_connection(id, GAP_DISCONNECT_REASON_TERM_CONNECTION_POWER);

	return STATUS_ERR_LAYER_SPECIFIC;
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

static void do_cleanup()
{
	interface_req_elem_t* req = NULL;
	logi("");
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	remove_all_adv_scanresp_data();
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

	clear_connected_device_list();

	while ((req = (interface_req_elem_t*)dequeue(&g_local_adapter.gap_data.pending_req_q)) != NULL)
	{
		dealloc_queue_element(req);
	}

	cleanup_q(&g_local_adapter.gap_data.pending_req_q);
	gap_cleanup_complete_cb();
}

/********** Utility functions end **********/

INT8 gap_req_handler(interface_req_elem_t* incoming_req)
{
	INT8 req_status = STATUS_ERR_UNKNOWN;
	interface_req_elem_t* req;
	/* enqueue this request */
	logi("");
	gap_enqueue_req_in_pending_queue(incoming_req);

	req = get_req_to_process();

	if (!req)
	{
		logi("No pending request in GAP wait queue.");
		return STATUS_SUCCESS;
	}

	if (g_local_adapter.gap_data.busy)
		return STATUS_ERR_BUSY;
	g_local_adapter.gap_data.busy = TRUE;

	switch (req->req_opcode)
	{
#if(TEST_CODE == TRUE)
#if (HOST_PRIVACY)
	case API_REQ_OPCODE_ENABLE_PRIVACY:
	{
		cm_privacy_state_param_t *param = (cm_privacy_state_param_t*)(void*)req->parameter;
		req_status = gap_enable_host_privacy(param->enable_privacy);
	}
	   break;
#endif /* HOST_PRIVACY */
#endif /* TEST_CODE == TRUE */
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

	case API_REQ_OPCODE_START_DISCOVERABLE:
	{
		cm_start_adv_param_t* param = (cm_start_adv_param_t*)(void*)req->parameter;
		/* Currently we expect that the directed adv will contain identity/public address.*/
#if 0
#if (HOST_PRIVACY)
		if (gap_direct_adv_addr_needs_resolution(param->timeout_msec, param->type, param->flags, param->remote_bd_addr, param->addr_type, param->use_whitelist, param->background))
			req_status = STATUS_SUCCESS;
		else
#endif /* HOST_PRIVACY */
#endif
			req_status = gap_start_advertise(param->timeout_msec, param->type, param->flags, param->remote_bd_addr, param->addr_type, param->adv_int_min, param->adv_int_max, param->use_whitelist, param->background);
	}
		break;
	case API_REQ_OPCODE_STOP_DISCOVERABLE:
	{
		req_status = gap_stop_advertise();
	}
		break;
#endif

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	case API_REQ_OPCODE_START_SCAN:
	{
		cm_start_scan_param_t* param = (cm_start_scan_param_t*)(void*)req->parameter;
		req_status = gap_start_scan(param->trans_id, param->timeout_msec, param->active, param->limited, param->use_whitelist, param->background, param->scan_int, param->scan_win, param->filter_uuids, TRUE);
	}
		break;
	case API_REQ_OPCODE_STOP_SCAN:
	{
		req_status = gap_stop_scan(TRUE);
	}
		break;
	case API_REQ_OPCODE_CONNECT:
	{
		pm_connect_param_t* param = (pm_connect_param_t*)(void*)req->parameter;
		req_status = pm_connect(param->trans_id, param->remote_bd_addr, param->addr_type, param->scan_int, param->scan_win, param->conn_int_min, param->conn_int_max, param->conn_lat, param->sup_timeout);
		logd("API_REQ_OPCODE_CONNECT");
	}
		break;
	case API_REQ_OPCODE_AUTO_CONNECT:
	{
		pm_auto_connect_param_t* param = (pm_auto_connect_param_t*)(void*)req->parameter;
		req_status = pm_auto_connect(param->trans_id, param->remote_bd_addr, param->addr_type, param->enable);
		logd("API_REQ_OPCODE_AUTO_CONNECT");
	}
		break;
#if (TEST_CODE == TRUE && LE_PING_ENABLE == TRUE)
	case API_REQ_OPCODE_TEST_READ_AUTHPAYLOAD_TIMEOUT:
	{
		cm_read_authpayload_timeout_t* param = (cm_read_authpayload_timeout_t*)(void*)req->parameter;
		req_status = pm_read_authpayload_timeout(param->trans_id, param->conn_id);
		logd("API_REQ_OPCODE_TEST_READ_AUTHPAYLOAD_TIMEOUT");
	}
		break;
	case API_REQ_OPCODE_TEST_WRITE_AUTHPAYLOAD_TIMEOUT:
	{
		cm_write_authpayload_timeout_t* param = (cm_write_authpayload_timeout_t*)(void*)req->parameter;
		req_status = gap_write_authpayload_timeout(param->conn_id, param->authpayload_timeout_ms);
		logd("API_REQ_OPCODE_TEST_WRITE_AUTHPAYLOAD_TIMEOUT");
	}
		break;
#endif /* TEST_CODE == TRUE && LE_PING_ENABLE == TRUE */
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
	case API_REQ_OPCODE_SET_DATA_LEN:
	{
		cm_set_data_len_t* param = (cm_set_data_len_t*)(void*)req->parameter;
		req_status = gap_set_data_len(param->conn_id, param->tx_octets);
		logd("API_REQ_OPCODE_SET_DATA_LEN");
	}
		break;
	case API_REQ_OPCODE_ADD_TO_WHITELIST:
	{
		dm_whitelist_op_param_t* param = (dm_whitelist_op_param_t*)(void*)req->parameter;
		req_status = gap_add_to_whitelist(param->addr_type, param->bdaddr);
	}
		break;
	case API_REQ_OPCODE_REMOVE_FROM_WHITELIST:
	{
		dm_whitelist_op_param_t* param = (dm_whitelist_op_param_t*)(void*)req->parameter;
		req_status = gap_remove_from_whitelist(param->addr_type, param->bdaddr);
	}
		break;
	case API_REQ_OPCODE_CLEAR_WHITELIST:
	{
		req_status = gap_clear_whitelist();
	}
		break;
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	case API_REQ_OPCODE_DISCONNECT:
	{
		pm_disconnect_param_t* param = (pm_disconnect_param_t*)(void*)req->parameter;
		req_status = pm_disconnect(param->trans_id, param->conn_id, param->reason);
		logd("API_REQ_OPCODE_DISCONNECT");
	}
		break;
	case API_REQ_OPCODE_GAP_CONN_PARAMS_UPDATE:
	{
		pm_update_conn_params_t* param = (pm_update_conn_params_t*)(void*)req->parameter;
		req_status = pm_conn_param_update_req(param->trans_id, param->conn_idx, param->interval_min,
				param->interval_max, param->conn_latency, param->sup_timeout);
	}
		break;
#if (CONTROLLER_PRIVACY)
	case API_REQ_OPCODE_ADD_TO_RESOLVINGLIST:
	{
		dm_resolving_op_param_t *param = (dm_resolving_op_param_t *)(void*)req->parameter;
		req_status = gap_add_to_resolvinglist(param->peer_addr_type, param->peer_bdaddr, param->peer_irk, param->local_irk);
	}
		break;
	case API_REQ_OPCODE_REMOVE_FROM_RESOLVINGLIST:
	{
		dm_resolving_op_param_t *param = (dm_resolving_op_param_t *)(void*)req->parameter;
		req_status = gap_remove_from_resolvinglist(param->peer_addr_type, param->peer_bdaddr);
	}
		break;
	case API_REQ_OPCODE_CLEAR_RESOLVINGLIST:
	{
		req_status = gap_clear_resolvinglist();
	}
		break;
#endif /* CONTROLLER_PRIVACY */
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
	}
	if (req_status != STATUS_ERR_BUSY && req_status != STATUS_OPERATION_FINISHED_LOCAL_SUCCESS)
		gap_dequeue_and_cleanup_from_pending_queue();

	if (req_status == STATUS_OPERATION_FINISHED_LOCAL_SUCCESS)
	{
		logd("This request has finished locally. See if there is any more req");
		gap_dequeue_req_from_pending_queue();
		g_local_adapter.gap_data.busy = FALSE;
		req_status = gap_req_handler(NULL);
		if (req_status != STATUS_SUCCESS)
		{
			dealloc_queue_element(req);
		}
		return req_status;
	}

	g_local_adapter.gap_data.busy = FALSE;
	return STATUS_PROCESS_ONGOING;
}

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

#if 0
#if (HOST_PRIVACY)

static BOOLEAN gap_direct_adv_addr_needs_resolution(UINT32 timeout_msec, UINT8 type, UINT8 flags, UINT8 *remote_bd_addr, UINT8 addr_type, BOOLEAN use_whitelist, BOOLEAN background)
{
	UINT8 bdaddr[BD_ADDR_LEN];
	UINT8 *rev_bdaddr = bdaddr;
	REVERSE_ARRAY_TO_STREAM(rev_bdaddr, remote_bd_addr, BD_ADDR_LEN);

	if (!LL_PRIVACY_IS_SUPPORTED)
		return FALSE;

	/* Directed Advertisement with RPA is only allowed if remote device has CAR support */
	if (type == GAP_ADV_TYPE_CONNECTABLE_DIRECTED_HIGH_DUTY || type == GAP_ADV_TYPE_CONNECTABLE_DIRECTED_LOW_DUTY)
	{
		/* Check if remote device supports CAR */

		/* If the supplied address is an identity address, we can directly look for it in the bonded list */
		if ((addr_type == GAP_ADDRESS_TYPE_PUBLIC || addr_type == GAP_ADDRESS_TYPE_RPA_OR_PUBLIC) || BLE_IS_RANDSTAT_BDADDR(bdaddr))
		{
			bonded_device_t* bdev = smp_mgr_db_search(bdaddr);
			if (bdev)
			{
				if (bdev->car_supported == PEER_CAR_SUPPORT_PRESENT)
				{
					logd("Resolution successful, remote device supports CAR");
				}
				else
				{
					loge("Cannot do Directed Advertisement since remote device does not support CAR!");
				}
				return FALSE;
			}
		}

		/* We need to resolve the supplied remote_bdaddr to find the corresponding entry in the bonded list */
		logd("Directed advertisement needs resolution of peer address");

		/* First, we save the advertisement parameters */
		g_local_adapter.gap_data.adv_timeout_msec = timeout_msec;
		g_local_adapter.gap_data.adv_type = type;
		g_local_adapter.gap_data.adv_flags = flags;
		memcpy(g_local_adapter.gap_data.adv_remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
		g_local_adapter.gap_data.adv_addr_type = addr_type;
		g_local_adapter.gap_data.adv_use_whitelist = use_whitelist;
		g_local_adapter.gap_data.adv_is_background = background;

		/* We start the resolution process here */
		start_operation(GAP_OPERATION_RESOLVING_DIRECT_ADDR);
		smpm_req_handler(create_req_for_rpa_adv_resolution(bdaddr, FALSE));

		return TRUE;
	}

	return FALSE;
}

#endif /* HOST_PRIVACY */
#endif

static INT8 gap_start_advertise(UINT32 timeout_msec, UINT8 type, UINT8 flags, UINT8 *remote_bd_addr, UINT8 addr_type, UINT16 adv_int_min, UINT16 adv_int_max, BOOLEAN use_whitelist, BOOLEAN background)
{
	//UINT8 direct_addr[] = {0x00,0x1b,0xdc,0x06,0x04,0xec}; /* PTS BD address */
	UINT8 adv_data_0;
	UINT8 idx = find_adv_scanresp_data_idx(g_local_adapter.gap_data.adv_data, GAP_ADV_DATA_FLAGS);
#if (PARANOID_STACK == TRUE)
	if (idx == MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES)
	{
		loge("Advertisement flags are not set!");
		return STATUS_ERR_LAYER_SPECIFIC;
	}
#endif
	logi("");

	/* If there is a Direct Advertisement InitA resolution process ongoing, we are pretty busy */
	//if (is_operation_running(GAP_OPERATION_RESOLVING_DIRECT_ADDR))
		//return STATUS_ERR_BUSY;

	if (adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_ENABLED))
	{
		/* If ongoing advertisement is infinite, restart it */
		if (!g_local_adapter.gap_data.adv_timeout_msec)
		{
			g_local_adapter.gap_data.adapter_state |= GAP_ADAPTER_STATE_ADV_RESTARTING;
			gap_stop_advertise();

			g_local_adapter.gap_data.adv_timeout_msec = timeout_msec;
			g_local_adapter.gap_data.adv_type = type;
			g_local_adapter.gap_data.adv_flags = flags;
			memcpy(g_local_adapter.gap_data.adv_remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
			g_local_adapter.gap_data.adv_addr_type = addr_type;
			g_local_adapter.gap_data.adv_use_whitelist = use_whitelist;
			g_local_adapter.gap_data.adv_int_min = adv_int_min;
			g_local_adapter.gap_data.adv_int_max = adv_int_max;
			g_local_adapter.gap_data.adv_is_background = background;

			return STATUS_SUCCESS;
		}
		/* If ongoing advertisement is finite, queue the incoming request */
		return STATUS_ERR_BUSY;
	}
	else if (adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_ENABLING) || adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_DISABLING))
		return STATUS_ERR_BUSY;

	/* Advertisement intervals and periods as per GAP spec Sec 9.3.11 */
	switch (type)
	{
	case GAP_ADV_TYPE_CONNECTABLE_UNDIRECTED:
		if (!(adv_int_min | adv_int_max))
		{
			adv_int_min = ADV_FAST_INTERVAL_MIN;
			adv_int_max = ADV_FAST_INTERVAL_MAX;
		}
		if (timeout_msec && (timeout_msec < 30000))
			timeout_msec = 30000;
		break;
	case GAP_ADV_TYPE_CONNECTABLE_DIRECTED_HIGH_DUTY:
		adv_int_min = adv_int_max = 0; //Ignored
		if (timeout_msec > 1280)
			timeout_msec = 1280;
		break;
	case GAP_ADV_TYPE_SCANNABLE_UNDIRECTED:
		if (!(adv_int_min | adv_int_max))
		{
			adv_int_min = ADV_FAST_NC_INTERVAL_MIN;
			adv_int_max = ADV_FAST_NC_INTERVAL_MAX;
		}
		if (timeout_msec && (timeout_msec < 30000))
			timeout_msec = 30000;
		break;
	case GAP_ADV_TYPE_NONCONNECTABLE_UNDIRECTED:
		if (!(adv_int_min | adv_int_max))
		{
			adv_int_min = ADV_FAST_NC_INTERVAL_MIN;
			adv_int_max = ADV_FAST_NC_INTERVAL_MAX;
		}
		if (timeout_msec && (timeout_msec < 30000))
			timeout_msec = 30000;
		break;
	case GAP_ADV_TYPE_CONNECTABLE_DIRECTED_LOW_DUTY:
		if (!(adv_int_min | adv_int_max))
		{
			adv_int_min = ADV_FAST_INTERVAL_MIN;
			adv_int_max = ADV_FAST_INTERVAL_MAX;
		}
		if (timeout_msec && (timeout_msec < 30000))
			timeout_msec = 30000;
		break;
	default:
		return STATUS_ERR_INVALID_PARAM;
	}

	if (background && type != GAP_ADV_TYPE_CONNECTABLE_DIRECTED_HIGH_DUTY)
	{
		adv_int_min = ADV_SLOW_INTERVAL_MIN;
		adv_int_max = ADV_SLOW_INTERVAL_MAX;
	}

	/* Maximum time for limited advertisement is 180s as per GAP spec Sec 9.2.3.2 */
	if ((flags == GAP_ADV_FLAGS_LE_LIMITED_DISCOVERABLE) && (timeout_msec > 180000))
		timeout_msec = 180000;

	g_local_adapter.gap_data.adv_timeout_msec = timeout_msec;
	g_local_adapter.gap_data.adv_type = type;
	g_local_adapter.gap_data.adv_flags = flags;
	memcpy(g_local_adapter.gap_data.adv_remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
	g_local_adapter.gap_data.adv_addr_type = addr_type;
	g_local_adapter.gap_data.adv_use_whitelist = use_whitelist;
	g_local_adapter.gap_data.adv_int_min = adv_int_min;
	g_local_adapter.gap_data.adv_int_max = adv_int_max;
	g_local_adapter.gap_data.adv_is_background = background;

	if (flags != 0xFF)
	{
		/* New flags passed down, otherwise we don't change the flags */
		adv_data_0 = g_local_adapter.gap_data.adv_data[idx]->data[0];
		g_local_adapter.gap_data.adv_data[idx]->data[0] &= (~GAP_ADV_FLAGS_LE_DISCOVERABILITY_MASK);
		g_local_adapter.gap_data.adv_data[idx]->data[0] |= (flags & GAP_ADV_FLAGS_LE_DISCOVERABILITY_MASK);
		if (g_local_adapter.gap_data.adv_data[idx]->data[0] != adv_data_0)
			g_local_adapter.gap_data.adv_scanresp_data_changed = TRUE; /* Flags changed */
	}

	/* Use non-connectable advertisement if we are already connected */
	if (!(g_local_adapter.ble_local_features[HCI_LE_FEATURE_CONN_PARAM_REQ_PROCEDURE_OFFSET] & HCI_LE_FEATURE_CONN_PARAM_REQ_PROCEDURE_MASK))
	{
		//LLT is not supported, use non-connectable advertisement
		if (any_device_is_in_state(GAP_CONNECTION_STATE_ACL_CONNECTED))
		{
			type = GAP_ADV_TYPE_NONCONNECTABLE_UNDIRECTED;
			adv_int_min = ADV_FAST_NC_INTERVAL_MIN;
			adv_int_max = ADV_FAST_NC_INTERVAL_MAX;
			if (timeout_msec && (timeout_msec < 30000))
				timeout_msec = 30000;
		}
	}

	start_operation(GAP_OPERATION_ADVERTISING);

	/* Just in case Direct Advertisement InitA resolution took place before this... */
	end_operation(GAP_OPERATION_RESOLVING_DIRECT_ADDR);

	if (timeout_msec)
		if (osa_create_timer(&g_local_adapter.gap_data.adv_timer, GAP_ADV_TIMER, GAP_ADV_TIMER_ISR, sizeof(GAP_ADV_TIMER)/sizeof(osa_timer_static_t), adv_timeout_cb, 0) == 0)
			osa_start_timer(&g_local_adapter.gap_data.adv_timer, GAP_ADV_TIMER, timeout_msec, adv_timeout_cb, 0);

	adapter_enter_adv_state(GAP_ADAPTER_STATE_ADV_ENABLING);

#if (BLE_USE_FWINFO_FUNC_CALL == FALSE)

	return hci_ble_write_adv_params(adv_int_min,
							adv_int_max,
							type,  /* adv type */
							g_local_adapter.addr_type,
							addr_type,  /* direct addr type */
							remote_bd_addr, /* direct address */
							0x7,	/* Adv chn map : all chan used */
							use_whitelist
							);
#else

	ble_adv_params_t adv_params;
	INT8 status = STATUS_ERR_INVALID_PARAM;
	memset(&adv_params,0x00,sizeof(ble_adv_params_t));
	adv_params.adv_int_max = adv_int_max;
	adv_params.adv_int_min = adv_int_min;
	adv_params.adv_type = type;
	adv_params.addr_type = g_local_adapter.addr_type;
	adv_params.direct_addr_type = addr_type;
	adv_params.ch_map = 0x07;
	adv_params.filter_policy = use_whitelist;
	memcpy(&adv_params.bdaddr,remote_bd_addr,BD_ADDR_LEN);
#if ((LE_STACK_PROFILING == TRUE) &&(TARGET_THREADX == TRUE))
	log_time_stamp(TIME_A4WP_WRITE_ADV_PARAMETERS);
#endif
	if (!hci_write_bt_controller_adv_params(&adv_params) )
	{
		UINT8 data_len = 0;
		UINT8 adv_data[ADV_DATA_LEN]= {0};
		data_len = get_formatted_adv_data(adv_data);
		g_local_adapter.gap_data.adv_scanresp_data_changed = FALSE;
		bt_tlv_data_t tlv_data;
		tlv_data.datalen = data_len;
		tlv_data.data = adv_data;
#if ((LE_STACK_PROFILING == TRUE) &&(TARGET_THREADX == TRUE))
	log_time_stamp(TIME_A4WP_WRITE_ADV_DATA);
#endif
		if(!hci_write_bt_controller_adv_data(&tlv_data))
		{
			UINT8 data_len = 0;
			UINT8 scan_rsp_data[ADV_DATA_LEN]= {0};
			data_len = get_formatted_scanresp_data(scan_rsp_data);
			bt_tlv_data_t tlv_data;
			tlv_data.datalen = data_len;
			tlv_data.data = scan_rsp_data;
#if ((LE_STACK_PROFILING == TRUE) &&(TARGET_THREADX == TRUE))
			log_time_stamp(TIME_A4WP_WRITE_SCAN_RESP_DATA);
#endif
			if (!hci_write_bt_controller_scan_resp_data(&tlv_data))
			{
				status = gap_handle_command_complete(HCI_CMD_LE_SET_SCAN_RESP_DATA, HCI_EVENT_STATUS_SUCCESS, NULL, 0);
			}
		}
	}
	return status;
#endif
}

static INT8 gap_stop_advertise()
{
	osa_timer_t *timer = &g_local_adapter.gap_data.adv_timer;

	if (!adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_ENABLED))
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;

	if (g_local_adapter.gap_data.adv_timeout_msec)
	{
		if (osa_is_timer_active(timer, GAP_ADV_TIMER, 0))
			osa_stop_timer(timer, GAP_ADV_TIMER, 0);
		osa_delete_timer(timer, GAP_ADV_TIMER);
	}

	adapter_enter_adv_state(GAP_ADAPTER_STATE_ADV_DISABLING);

	hci_ble_set_adv_enable(0); /* Disable adv */
	return STATUS_SUCCESS;
}

static void gap_restart_advertise()
{
	if (!(adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_ENABLING) || adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_ENABLED)))
		return;
	interface_req_elem_t *req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_START_DISCOVERABLE, 0, sizeof(cm_start_adv_param_t));
	if(req == NULL)
		return;
	cm_start_adv_param_t* param = (cm_start_adv_param_t*)req->parameter;
	logi("start the adv");
	param->timeout_msec = g_local_adapter.gap_data.adv_timeout_msec;
	param->type = g_local_adapter.gap_data.adv_type;
	param->flags = g_local_adapter.gap_data.adv_flags;
	param->use_whitelist =	g_local_adapter.gap_data.adv_use_whitelist;
	param->background = g_local_adapter.gap_data.adv_is_background;
	param->adv_int_min = g_local_adapter.gap_data.adv_int_min;
	param->adv_int_max = g_local_adapter.gap_data.adv_int_max;
	gap_req_handler(req);
}

UINT8 gap_add_adv_scanresp_data(gap_adv_scanresp_data_t **dlist, UINT8 length, UINT8 type, UINT8 *data)
{
	UINT8 idx = find_adv_scanresp_data_idx(dlist, type);
	UINT8 *ptr, *list;
	UINT8 i, data_length, bytes_per_entry = 2;

	if (idx == MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES)
		idx = add_new_adv_scanresp_data(dlist, length, type, data);
	else
	{
		/* Modify existing advertisement data */
		data_length = dlist[idx]->data_length;

		switch (type)
		{
		case GAP_ADV_DATA_FLAGS:
			//Overwrite existing
			dlist[idx]->data[0] = data[0];
			break;
		case GAP_ADV_DATA_INCOMPLETE_16BIT_UUID:
		case GAP_ADV_DATA_COMPLETE_16BIT_UUID:
		case GAP_ADV_DATA_SOLICITATION_16BIT_UUID:
		case GAP_ADV_DATA_INCOMPLETE_32BIT_UUID:
		case GAP_ADV_DATA_COMPLETE_32BIT_UUID:
		case GAP_ADV_DATA_SOLICITATION_32BIT_UUID:
			list = (UINT8*)(void*)dlist[idx]->data;
			if (type == GAP_ADV_DATA_INCOMPLETE_16BIT_UUID || type == GAP_ADV_DATA_COMPLETE_16BIT_UUID || type == GAP_ADV_DATA_SOLICITATION_16BIT_UUID)
				bytes_per_entry = sizeof(UINT16)/sizeof(UINT8);
			if (type == GAP_ADV_DATA_INCOMPLETE_32BIT_UUID || type == GAP_ADV_DATA_COMPLETE_32BIT_UUID || type == GAP_ADV_DATA_SOLICITATION_32BIT_UUID)
				bytes_per_entry = sizeof(UINT32)/sizeof(UINT8);
			for (i = 0; i < data_length; i += bytes_per_entry)
			{
				if (memcmp(&list[i], data, bytes_per_entry) == 0)
					break; //Already exists in list
			}
			if (i == data_length) //Not found
			{
				ptr = alloc(dlist[idx]->data_length + bytes_per_entry);
	#if (PARANOID_STACK == TRUE)
				if (!ptr)
					return idx;
	#endif
				memcpy(ptr, dlist[idx]->data, dlist[idx]->data_length);
				dealloc(dlist[idx]->data);
				dlist[idx]->data = ptr;
				dlist[idx]->data_length += bytes_per_entry; //Add new entry
				list = (UINT8*)(void*)dlist[idx]->data;
				memcpy(&list[i], data, bytes_per_entry);
			}
			break;
		case GAP_ADV_DATA_SHORTENED_LOCAL_NAME:
		case GAP_ADV_DATA_COMPLETE_LOCAL_NAME:
			if (data != (UINT8*) g_local_adapter.local_name)
			{
				memset(g_local_adapter.local_name, 0, sizeof(g_local_adapter.local_name));
				memcpy(g_local_adapter.local_name, data, length);
#if 0
#if (STORAGE_INCLUDED == TRUE)
				local_adapter_storage_t adapter_storage;
				get_local_adapter_entry(&adapter_storage);
				memcpy(adapter_storage.name, g_local_adapter.local_name, sizeof(adapter_storage.name));
				set_local_adapter_entry(&adapter_storage);
#endif /* STORAGE_INCLUDED == TRUE */
#endif
			}
		case GAP_ADV_DATA_DEVICE_CLASS:
		case GAP_ADV_DATA_APPEARANCE:
		case GAP_ADV_DATA_ROLE:
			//Overwrite
			idx = overwrite_adv_scanresp_data(dlist, length, type, data);
			break;
		case GAP_ADV_DATA_SERVICE_DATA_16BIT_UUID:
		case GAP_ADV_DATA_SERVICE_DATA_32BIT_UUID:
			if (type == GAP_ADV_DATA_SERVICE_DATA_16BIT_UUID)
				bytes_per_entry = sizeof(UINT16)/sizeof(UINT8);
			if (type == GAP_ADV_DATA_SERVICE_DATA_32BIT_UUID)
				bytes_per_entry = sizeof(UINT32)/sizeof(UINT8);
			//Check if UUID already exists, if not add
			for (idx = 0; idx < MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES; idx++)
			{
				if (dlist[idx] && dlist[idx]->type == type)
				{
					if (memcmp(dlist[idx]->data, data, bytes_per_entry) == 0)
					{
						//UUID match - replace the data
						memcpy(dlist[idx]->data, data, length);
						break;
					}
				}
			}
			if (idx == MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES) //UUID not found - add
				idx = add_new_adv_scanresp_data(dlist, length, type, data);
			break;
		}
	}
	g_local_adapter.gap_data.adv_scanresp_data_changed = TRUE;
	gap_restart_advertise();
	return idx;
}

UINT8 gap_get_local_name(gap_adv_scanresp_data_t **dlist, UINT8 *name)
{
	UINT8 idx = find_adv_scanresp_data_idx(dlist, GAP_ADV_DATA_COMPLETE_LOCAL_NAME);

	if (idx != MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES)
	{
		memcpy(name, dlist[idx]->data, dlist[idx]->data_length);
		 return dlist[idx]->data_length;
	}

	return 0;
}

void gap_remove_adv_scanresp_data(gap_adv_scanresp_data_t **dlist, UINT8 length, UINT8 type, UINT8 *data)
{
	UINT8 idx = find_adv_scanresp_data_idx(dlist, type);
	UINT8 *ptr, *list;
	UINT8 i, data_length, bytes_per_entry = 2;

	if (idx == MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES)
		return;

	data_length = dlist[idx]->data_length;

	switch (type)
	{
	case GAP_ADV_DATA_FLAGS:
		//Clear from existing
		dlist[idx]->data[0] &= (~data[0]);
		break;
	case GAP_ADV_DATA_INCOMPLETE_16BIT_UUID:
	case GAP_ADV_DATA_COMPLETE_16BIT_UUID:
	case GAP_ADV_DATA_SOLICITATION_16BIT_UUID:
	case GAP_ADV_DATA_INCOMPLETE_32BIT_UUID:
	case GAP_ADV_DATA_COMPLETE_32BIT_UUID:
	case GAP_ADV_DATA_SOLICITATION_32BIT_UUID:
	case GAP_ADV_DATA_INCOMPLETE_128BIT_UUID:
	case GAP_ADV_DATA_COMPLETE_128BIT_UUID:
	case GAP_ADV_DATA_SOLICITATION_128BIT_UUID:
		list = (UINT8*)(void*)dlist[idx]->data;
		if (type == GAP_ADV_DATA_INCOMPLETE_16BIT_UUID || type == GAP_ADV_DATA_COMPLETE_16BIT_UUID || type == GAP_ADV_DATA_SOLICITATION_16BIT_UUID)
			bytes_per_entry = sizeof(UINT16)/sizeof(UINT8);
		if (type == GAP_ADV_DATA_INCOMPLETE_32BIT_UUID || type == GAP_ADV_DATA_COMPLETE_32BIT_UUID || type == GAP_ADV_DATA_SOLICITATION_32BIT_UUID)
			bytes_per_entry = sizeof(UINT32)/sizeof(UINT8);
		if (type == GAP_ADV_DATA_INCOMPLETE_128BIT_UUID || type == GAP_ADV_DATA_COMPLETE_128BIT_UUID || type == GAP_ADV_DATA_SOLICITATION_128BIT_UUID)
			bytes_per_entry = (sizeof(UINT64) * 2)/sizeof(UINT8);
		for (i = 0; i < data_length; i += bytes_per_entry)
		{
			if (memcmp(&list[i], data, bytes_per_entry) == 0)
				break;
		}
		if (i < data_length) //Found
		{
			if (dlist[idx]->data_length == bytes_per_entry)
			{
				dealloc(dlist[idx]->data);
				dealloc(dlist[idx]);
				dlist[idx] = NULL;
			}
			else
			{
				ptr = alloc(dlist[idx]->data_length - bytes_per_entry);
#if (PARANOID_STACK == TRUE)
				if (!ptr)
					return;
#endif
				memcpy(ptr, list, i);
				memcpy(&ptr[i], &list[i + bytes_per_entry], dlist[idx]->data_length - (i + bytes_per_entry));
				dealloc(dlist[idx]->data);
				dlist[idx]->data = ptr;
				dlist[idx]->data_length -= length; //Remove old entry
			}
		}
		break;
	case GAP_ADV_DATA_SHORTENED_LOCAL_NAME:
	case GAP_ADV_DATA_COMPLETE_LOCAL_NAME:
	case GAP_ADV_DATA_DEVICE_CLASS:
	case GAP_ADV_DATA_MAUFACTURER:
	case GAP_ADV_DATA_APPEARANCE:
	case GAP_ADV_DATA_TX_POWER:
	case GAP_ADV_DATA_ROLE:
		dealloc(dlist[idx]->data);
		dealloc(dlist[idx]);
		dlist[idx] = NULL;
		break;
	case GAP_ADV_DATA_SERVICE_DATA_16BIT_UUID:
	case GAP_ADV_DATA_SERVICE_DATA_32BIT_UUID:
	case GAP_ADV_DATA_SERVICE_DATA_128BIT_UUID:
		if (type == GAP_ADV_DATA_SERVICE_DATA_16BIT_UUID)
			bytes_per_entry = sizeof(UINT16)/sizeof(UINT8);
		if (type == GAP_ADV_DATA_SERVICE_DATA_32BIT_UUID)
			bytes_per_entry = sizeof(UINT32)/sizeof(UINT8);
		if (type == GAP_ADV_DATA_SERVICE_DATA_128BIT_UUID)
			bytes_per_entry = (sizeof(UINT64) * 2)/sizeof(UINT8);
		//Check if UUID exists
		for (idx = 0; idx < MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES; idx++)
		{
			if (dlist[idx] && dlist[idx]->type == type)
			{
				if (memcmp(dlist[idx]->data, data, bytes_per_entry) == 0)
				{
					//UUID match - remove the data
					dealloc(dlist[idx]->data);
					dealloc(dlist[idx]);
					dlist[idx] = NULL;
					break;
				}
			}
		}
		break;
	}
	g_local_adapter.gap_data.adv_scanresp_data_changed = TRUE;
	gap_restart_advertise();
}

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

static INT8 gap_start_scan(trans_id_t trans_id, UINT32 timeout_msec, BOOLEAN active, BOOLEAN limited, BOOLEAN use_whitelist, BOOLEAN background, UINT16 scan_int, UINT16 scan_win, UINT16* filter_uuids, BOOLEAN user_triggered)
{
	UINT8 scan_filter = use_whitelist;
	logd("%s", background? "BG":"FG");

	if (adapter_is_in_scn_state(GAP_ADAPTER_STATE_SCN_ENABLING) || adapter_is_in_scn_state(GAP_ADAPTER_STATE_SCN_DISABLING))
		return STATUS_ERR_BUSY;

	if (user_triggered)
		g_local_adapter.gap_data.user_scan_in_progress = TRUE;

	/* Allow BG scans only if it is triggered by user or by idleness */
	/* Filter out restoring/restarting scans here */
	if (background && !(g_local_adapter.gap_data.user_scan_in_progress || g_local_adapter.gap_data.idle_scan_in_progress))
		return STATUS_ERR_LAYER_SPECIFIC;

	if (adapter_is_in_scn_state(GAP_ADAPTER_STATE_SCN_ENABLED))
	{
		/* If ongoing scan is infinite, restart it */
		if (!g_local_adapter.gap_data.scan_timeout_msec)
		{
			g_local_adapter.gap_data.adapter_state |= GAP_ADAPTER_STATE_SCN_RESTARTING;
			gap_stop_scan(FALSE);

			g_local_adapter.gap_data.scan_timeout_msec = timeout_msec;
			g_local_adapter.gap_data.scan_isactive = active;
			g_local_adapter.gap_data.scan_is_limited = limited;
			g_local_adapter.gap_data.scan_use_whitelist = use_whitelist;
			g_local_adapter.gap_data.scan_is_background = background;
			g_local_adapter.gap_data.scan_int = scan_int;
			g_local_adapter.gap_data.scan_win = scan_win;
			g_local_adapter.gap_data.scan_req_trans_id = trans_id;
			if (filter_uuids)
				memcpy(g_local_adapter.gap_data.scan_filter_uuids, filter_uuids, sizeof(g_local_adapter.gap_data.scan_filter_uuids));
			else
				memset(g_local_adapter.gap_data.scan_filter_uuids, 0, sizeof(g_local_adapter.gap_data.scan_filter_uuids));
			return STATUS_SUCCESS;
		}
		/* If ongoing scan is finite, queue the incoming request */
		return STATUS_ERR_BUSY;
	}

	g_local_adapter.gap_data.scan_timeout_msec = timeout_msec;
	g_local_adapter.gap_data.scan_isactive = active;
	g_local_adapter.gap_data.scan_is_limited = limited;
	g_local_adapter.gap_data.scan_use_whitelist = use_whitelist;
	g_local_adapter.gap_data.scan_is_background = background;
	g_local_adapter.gap_data.scan_int = scan_int;
	g_local_adapter.gap_data.scan_win = scan_win;
	g_local_adapter.gap_data.scan_req_trans_id = trans_id;
	if (filter_uuids)
		memcpy(g_local_adapter.gap_data.scan_filter_uuids, filter_uuids, sizeof(g_local_adapter.gap_data.scan_filter_uuids));
	else
		memset(g_local_adapter.gap_data.scan_filter_uuids, 0, sizeof(g_local_adapter.gap_data.scan_filter_uuids));

	/* Minimum time for general/limited discovery is 10.24s as per GAP spec Sec 9.2.5 & 9.2.6 */
	if ((timeout_msec > 0) && (timeout_msec < 10240))
		timeout_msec = 10240;

	/* As per GAP spec Sec 9.3.11 */
	if (background)
	{
		scan_int = SCAN_SLOW_INTERVAL;
		scan_win = SCAN_SLOW_WINDOW;
		start_operation(GAP_OPERATION_BG_SCANNING);
		adapter_enter_bgscanning_state();
	}
	else if ((!scan_int) || (!scan_win))
	{
		/* Use default values if either scan_int or scan_win is zero*/
		scan_int = SCAN_FAST_INTERVAL;
		scan_win = SCAN_FAST_WINDOW;
		start_operation(GAP_OPERATION_FG_SCANNING);
	}

	if (timeout_msec)
		if (osa_create_timer(&g_local_adapter.gap_data.scan_timer, GAP_SCAN_TIMER, GAP_SCAN_TIMER_ISR, sizeof(GAP_SCAN_TIMER)/sizeof(osa_timer_static_t), scan_timeout_cb, 0) == 0)
			osa_start_timer(&g_local_adapter.gap_data.scan_timer, GAP_SCAN_TIMER, timeout_msec, scan_timeout_cb, 0);
#if (CONTROLLER_PRIVACY)
	if (LL_PRIVACY_IS_SUPPORTED)
	{
		if (use_whitelist)
			scan_filter = 3;
		else
			scan_filter = 2;
	}
#endif
	adapter_enter_scn_state(GAP_ADAPTER_STATE_SCN_ENABLING);

	return hci_ble_set_scan_params(active, /* scan type */
							scan_int,
							scan_win,
							g_local_adapter.addr_type, /* own address : public */
							scan_filter
							);
}

static INT8 gap_stop_scan(BOOLEAN user_triggered)
{
	osa_timer_t *timer = &g_local_adapter.gap_data.scan_timer;
	logi("");

	if (!adapter_is_in_scn_state(GAP_ADAPTER_STATE_SCN_ENABLED))
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;

	if (user_triggered)
		g_local_adapter.gap_data.user_scan_in_progress = FALSE;

	g_local_adapter.gap_data.idle_scan_in_progress = FALSE;

	if (g_local_adapter.gap_data.scan_timeout_msec)
	{
		if (osa_is_timer_active(timer, GAP_SCAN_TIMER, 0))
			osa_stop_timer(timer, GAP_SCAN_TIMER, 0);
		osa_delete_timer(timer, GAP_SCAN_TIMER);
	}

	adapter_enter_scn_state(GAP_ADAPTER_STATE_SCN_DISABLING);

	/* Disable scan */
	if (hci_ble_set_scan_enable(0, 0) != STATUS_SUCCESS)
	{
		loge("LE Disable Scan Failed");
		gap_handle_command_complete(HCI_CMD_LE_SET_SCAN_ENABLE, HCI_EVENT_STATUS_SUCCESS, 0, 0);
	}

	return STATUS_SUCCESS;
}

static INT8 device_found()
{
	discovered_device_t *device = &g_local_adapter.gap_data.discovered_device;
	UINT8 app_idx = get_appid_from_transid(g_local_adapter.gap_data.scan_req_trans_id);
	UINT8 idx = 0, pos, elem_len;
	BOOLEAN found = FALSE;

	/* Filter by service UUID */

	if (!g_local_adapter.gap_data.scan_filter_uuids[0])
		found = TRUE;

	if (device->adv_data_len)
	{
		while ((idx < MAX_NUM_SCAN_FILTER_UUIDS) && g_local_adapter.gap_data.scan_filter_uuids[idx] && (!found))
		{
			pos = 0;
			while ((pos < (device->adv_data_len - 1)) && (!found))
			{
				elem_len = device->adv_data[pos++];
				elem_len--; //Except the Type field
				switch (device->adv_data[pos++])
				{
				case GAP_DATA_16BIT_SERVICE_UUIDS_INCOMP:
				case GAP_DATA_16BIT_SERVICE_UUIDS_COMP:
					if (*((UINT16*)(device->adv_data + pos)) == g_local_adapter.gap_data.scan_filter_uuids[idx])
						found = TRUE;
					pos += elem_len;
					break;
				default:
					pos += elem_len;
				}
			}
			idx++;
		}
	}

	/* Send data to app */
	if ((app_idx < MAX_NUMBER_OF_APP) && g_local_adapter.app_list[app_idx] && found)
	{
		if (g_local_adapter.app_list[app_idx]->app_device_control_cb->iLE_scan_result_cb)
			g_local_adapter.app_list[app_idx]->app_device_control_cb->iLE_scan_result_cb(g_local_adapter.gap_data.scan_req_trans_id, device);
	}

#if (HOST_PRIVACY)
	if (!is_autoconn_list_empty() && (LE_PRIVACY_EN == g_local_adapter.privacy_enabled) && device->addr_type && BLE_IS_RESOLVE_BDADDR(device->bdaddr))
		smpm_req_handler(create_req_for_rpa_adv_resolution(device->bdaddr, FALSE));
	else if (!is_autoconn_list_empty() && device->direct_addr_type && BLE_IS_RESOLVE_BDADDR(device->direct_addr))
		smpm_req_handler(create_req_for_rpa_adv_resolution(device->direct_addr, TRUE));
	else
#endif /* HOST_PRIVACY */
	{
		UINT8 auto_idx = get_idx_from_autoconn_list(device->bdaddr);
		if (auto_idx != MAX_NUM_CONNECTED_DEVICE)
		{
			if (g_local_adapter.gap_data.autoconn_dev[auto_idx]->conn_state == DEVICE_DISCONNECTED)
			{
				interface_req_elem_t *req = (interface_req_elem_t *)get_interface_req_buffer(API_REQ_OPCODE_CONNECT, 0, sizeof(pm_connect_param_t));
				pm_connect_param_t* param;
				if(req == NULL)
					return STATUS_ERR_INSUFFICIENT_RESOURCES;
				param = (pm_connect_param_t*)req->parameter;
				logd("Auto-connectable device found! Connecting...");
				g_local_adapter.gap_data.autoconn_dev[auto_idx]->conn_state = DEVICE_CONNECTING;
				// We are putting invalid trans_id here to indicate that it is an autoconnect so that it is handled correctly
				//in the connection compete.
				gap_stop_scan(FALSE);//TODO : To check whether to stop the scan or not
				param->trans_id = INVALID_TRANS_ID;
				param->addr_type = device->addr_type;
				memcpy(param->remote_bd_addr, device->bdaddr, BD_ADDR_LEN);
				param->scan_int = SCAN_CONN_INTERVAL;
				param->scan_win = SCAN_CONN_WINDOW;
				param->conn_int_min = CONNECTION_INTERVAL_MIN;
				param->conn_int_max = CONNECTION_INTERVAL_MAX;
				param->conn_lat = CONNECTION_LATENCY;
				param->sup_timeout = CONNECTION_SUP_TIMEOUT;
				gap_req_handler(req);
			}
		}
	}
	if (device->adv_data_len)
		dealloc(device->adv_data);
	memset(device, 0, sizeof(discovered_device_t));
	return STATUS_SUCCESS;
}

INT8 gap_create_connection(UINT8 *remote_bdaddr, UINT8 addr_type, UINT16 scan_int, UINT16 scan_win, UINT16 conn_int_min, UINT16 conn_int_max, UINT16 conn_lat, UINT16 sup_timeout)
{
	UINT8 bdaddr[BD_ADDR_LEN], idx;
	char bdaddr_str[BD_ADDR_STR_LEN];
	UINT8 *rev_bdaddr = bdaddr;
	INT8 ret;
	REVERSE_ARRAY_TO_STREAM(rev_bdaddr, remote_bdaddr, BD_ADDR_LEN);
	BDADDR_TO_STRING(bdaddr_str, remote_bdaddr);

	logi("");

	idx = get_connected_device_idx_by_bdaddr(remote_bdaddr);

	if (idx != MAX_NUM_CONNECTED_DEVICE)
	{
		logd("Device %s is already connected at %u!", bdaddr_str, idx);
		/* L2CAP is already setup. Don't call l2cap connect again. */
		pm_connect_cb(g_local_adapter.connected_device[idx], STATUS_SUCCESS);
		return STATUS_OPERATION_FINISHED_LOCAL_SUCCESS;
	}

	if (any_device_is_in_state(GAP_CONNECTION_STATE_ACL_CONNECTING) || any_device_is_in_state(GAP_CONNECTION_STATE_ACL_DISCONNECTING) || any_device_is_in_state(GAP_CONNECTION_STATE_LINK_PARAM_UPDATING))
	{
		logw("At least one remote device is already in connect/disconnect/update state, cannot start new connection!");
		return STATUS_ERR_BUSY;
	}

	if (
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
			adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_ENABLING) ||
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
			adapter_is_in_scn_state(GAP_ADAPTER_STATE_SCN_ENABLING))
	{
		logw("In the middle of enabling advertisement/scan, cannot start new connection!");
		return STATUS_ERR_BUSY;
	}

	idx = find_first_free_connected_device_slot();
	if (idx == MAX_NUM_CONNECTED_DEVICE)
	{
		loge("Already reached the limit of %u connected devices!", MAX_NUM_CONNECTED_DEVICE);
		pm_connect_error_cb(remote_bdaddr, addr_type, GAP_CONNECT_ERROR_CONNECTION_LIMIT_EXCEEDED);
		return STATUS_OPERATION_FINISHED_LOCAL_SUCCESS;
	}

	osa_gap_setup_connection(idx, remote_bdaddr, addr_type);

	g_local_adapter.gap_data.prev_adapter_state = g_local_adapter.gap_data.adapter_state;

	start_operation(GAP_OPERATION_CONNECTING);

	logd("Trying to create connection with %s (%u)", bdaddr_str, idx);

	ret = hci_ble_create_ll_conn(scan_int,
						scan_win,
						0x0,	//initiator filter policy
						addr_type,	//Peer address type
						bdaddr,
						g_local_adapter.addr_type, //Own address type
						conn_int_min,
						conn_int_max,
						conn_lat,
						sup_timeout,
						0x0000, //Min CE length
						0x0000); //Max CE length

#if (PARANOID_STACK == TRUE)
	if (ret != STATUS_SUCCESS)
		return ret;
#else
	USE(ret);
#endif

	return STATUS_SUCCESS;
}

INT8 gap_handle_adv_report(UINT8* buffer, UINT16 len, BOOLEAN directed)
{
	UINT8 num_reports, event_type = 0, address_type, length_data = 0, direct_addr_type = 0;
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
	INT8 rssi = 0;
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */
	UINT8 bdaddr[BD_ADDR_LEN], direct_addr[BD_ADDR_LEN];
	UINT8* data = 0;
	UINT8* ptr;
	UINT8 pos = 0, elem_len;
	BOOLEAN skip = FALSE;
	char bdaddr_str[BD_ADDR_STR_LEN], direct_addr_str[BD_ADDR_STR_LEN];
	UINT8 zero_addr[] = { 0, 0, 0, 0, 0, 0 };
	discovered_device_t *device = &g_local_adapter.gap_data.discovered_device;

	memcpy(direct_addr, zero_addr, BD_ADDR_LEN);
	STREAM_TO_UINT8(num_reports, buffer);
	logd("Got adv report, num_reports = %u", num_reports);

	while (num_reports)
	{
		STREAM_TO_UINT8(event_type, buffer);
		STREAM_TO_UINT8(address_type, buffer);
		STREAM_TO_BDADDR(bdaddr, buffer);

		if (directed)
		{
			STREAM_TO_UINT8(direct_addr_type, buffer);
			STREAM_TO_BDADDR(direct_addr, buffer);
		}
		else
		{
			STREAM_TO_UINT8(length_data, buffer);
			if (length_data > 0)
			{
				data = (UINT8*) alloc(length_data);

				if (!data)
					return STATUS_ERR_INSUFFICIENT_RESOURCES;

				STREAM_TO_ARRAY(data, buffer, length_data);
			}
			buffer += length_data;
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
			STREAM_TO_INT8(rssi, buffer);
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */
		}

		device->addr_type = address_type;
		memcpy(device->bdaddr, bdaddr, BD_ADDR_LEN);
		device->direct_addr_type = direct_addr_type;
		memcpy(device->direct_addr, direct_addr, BD_ADDR_LEN);
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
		device->rssi = rssi;
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */

		BDADDR_TO_STRING(bdaddr_str, bdaddr);

		if (directed)
		{
			BDADDR_TO_STRING(direct_addr_str, direct_addr);
			logd("event_type=%u, address_type=%u, bdaddr_str=%s, direct_addr_str=%s", event_type, address_type, bdaddr_str, direct_addr_str);
		}
		else
			logd("event_type=%u, address_type=%u, bdaddr_str=%s, length_data=%u", event_type, address_type, bdaddr_str, length_data);

		if (length_data > 0)
		{
			while (pos < (length_data - 1))
			{
				elem_len = data[pos++];
				elem_len--; //Except the Type field
				switch (data[pos++])
				{
				case GAP_DATA_SHORTENED_LOCAL_NAME:
				case GAP_DATA_COMPLETE_LOCAL_NAME:
					ptr = &data[pos];
					pos += elem_len;
					ARRAY_TO_STRING(device->localname, ptr, MIN(elem_len, MAX_DEVICE_NAME_LEN));
					logd("devname=%s", device->localname);
					break;
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
				case GAP_DATA_TX_POWER_LEVEL:
					device->tx_power = data[pos++];
					logd("tx_power=%u", device->tx_power);
					break;
				case GAP_DATA_APPEARANCE:
					device->appearance = ((UINT16)data[pos])+(((UINT16)data[pos+1])<<8);
					pos += 2;
					logd("appearance=%u", device->appearance);
					break;
				case GAP_DATA_LE_ROLE:
					device->role_supported = data[pos++];
					logd("role_supported=%u", device->role_supported);
					break;
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */
				case GAP_DATA_FLAGS:
					device->flags = data[pos++];
					logd("flags=%u", device->flags);
					break;
				default:
					pos += elem_len;
				}
			}
		}

		num_reports--;

		device->event_type = event_type;

#if (GAP_DISCOVER_ALL_DEVICES == FALSE)
		/* If device is not discoverable, reject it */
		if (!(device->flags & GAP_ADV_FLAGS_LE_DISCOVERABILITY_MASK))
		{
			logd("Remote device is not discoverable! Ignoring...");
			memset(device->bdaddr, 0, BD_ADDR_LEN);
			skip = TRUE;
		}
#endif

		/* If we are doing limited discovery, and the device doesn't have limited discovery flag set, reject it */
		if (g_local_adapter.gap_data.scan_is_limited && !(device->flags & GAP_ADV_FLAGS_LE_LIMITED_DISCOVERABLE))
		{
			logd("Doing limited discovery, but remote device is general discoverable! Ignoring...");
			memset(device->bdaddr, 0, BD_ADDR_LEN);
			skip = TRUE;
		}

		if (!skip)
		{
			if (device->adv_data)
				dealloc(device->adv_data);
			device->adv_data = NULL;
			device->adv_data_len = 0;
			if (length_data)
			{
				device->adv_data = (UINT8*) alloc(length_data);
				if (device->adv_data)
				{
					memcpy(device->adv_data, data, length_data);
					device->adv_data_len = length_data;
				}
			}
			device_found();
		}
	}

	if (length_data)
		dealloc(data);

	return STATUS_SUCCESS;
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

INT8 gap_add_to_whitelist(UINT8 addr_type, UINT8 *peer_bdaddr)
{

#if (PARANOID_STACK == TRUE)
	if (g_local_adapter.num_whitelist_entries >= g_local_adapter.whitelist_size)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	prep_whitelist_update();

	return hci_ble_add_to_white_list(addr_type, peer_bdaddr);
}

INT8 gap_remove_from_whitelist(UINT8 addr_type, UINT8 *peer_bdaddr)
{

#if (PARANOID_STACK == TRUE)
	if (g_local_adapter.num_whitelist_entries == 0)
		return STATUS_ERR_INVALID_PARAM;
#endif

	prep_whitelist_update();

	return hci_ble_remove_from_white_list(addr_type, peer_bdaddr);
}

static INT8 gap_clear_whitelist()
{
	prep_whitelist_update();

	return hci_ble_clear_white_list();
}

#if (CONTROLLER_PRIVACY)

INT8 gap_add_to_resolvinglist(UINT8 peer_addr_type, UINT8 *peer_bdaddr, UINT8 *peer_irk, UINT8 *local_irk)
{
	INT8 status;

#if (PARANOID_STACK == TRUE)
	if (g_local_adapter.num_resolvinglist_entries >= g_local_adapter.resolvinglist_size)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	if (any_device_is_in_state(GAP_CONNECTION_STATE_ACL_CONNECTING))
	{
		logw("At least one remote device is already in connect state, cannot start new update!");
			return STATUS_ERR_BUSY;
	}

	prep_resolvinglist_update();

	status = hci_ble_add_device_to_resolving_list(peer_addr_type, peer_bdaddr, peer_irk, local_irk);

#if (TARGET_UEFI == TRUE)
	/* WORKAROUND: Changing Privacy mode to Device Privacy mode for any peer device,
				   remove this after 5.0 Privacy changes */
	status = hci_ble_set_privacy_mode(peer_addr_type, peer_bdaddr, LE_DEVICE_PRIVACY_MODE);
#endif

	return status;
}

INT8 gap_remove_from_resolvinglist(UINT8 peer_addr_type, UINT8 *peer_bdaddr)
{

#if (PARANOID_STACK == TRUE)
	if (g_local_adapter.num_resolvinglist_entries == 0)
		return STATUS_ERR_INVALID_PARAM;
#endif

	if (any_device_is_in_state(GAP_CONNECTION_STATE_ACL_CONNECTING))
	{
		logw("At least one remote device is already in connect state, cannot start new update!");
		return STATUS_ERR_BUSY;
	}

	prep_resolvinglist_update();

	return hci_ble_remove_device_from_resolving_list(peer_addr_type, peer_bdaddr);
}

INT8 gap_clear_resolvinglist()
{
	if (any_device_is_in_state(GAP_CONNECTION_STATE_ACL_CONNECTING))
	{
			logw("At least one remote device is already in connect state, cannot start new update!");
				return STATUS_ERR_BUSY;
	}

	prep_resolvinglist_update();

	return hci_ble_clear_resolving_list();
}

#endif /* CONTROLLER_PRIVACY */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

INT8 controller_error_cleanup(connected_device_t *device)
{
	UINT8 idx;

	/* Clear all the pending operations */
	clear_all_operations();
	idx = get_connected_device_idx_by_handle(device->acl_handle);

	if (idx == MAX_NUM_CONNECTED_DEVICE)
	{
		loge("ACL handle 0x%x does not exist in connection list!", device->acl_handle);
		pm_disconnect_cb(NULL, FALSE);
		return STATUS_ERR_INAVALID_CONNENCTION;
	}

	if (device_is_in_state(idx, GAP_CONNECTION_STATE_ACL_DISCONNECTED))
	{
		loge("Remote device is already in GAP state DISCONNECTED!");
		pm_disconnect_cb(device, FALSE);
		delete_connected_device(idx);
		end_operation(GAP_OPERATION_DISCONNECTING);
		return STATUS_SUCCESS;
	}
	if (device_is_in_state(idx, GAP_CONNECTION_STATE_ACL_DISCONNECTING))
	{
		//Disconnect was issued from here... l2cap is already disconnected
		device_set_state(idx, GAP_CONNECTION_STATE_ACL_DISCONNECTED);
		remote_command_timer_stop(idx);
	}

	pm_disconnect_cb(device, FALSE);

	delete_connected_device(idx);
	finish_transac_and_process_new_req();

	return STATUS_SUCCESS;
}

INT8 gap_terminate_connection(UINT8 connected_device_list_idx, UINT8 reason)
{
	connected_device_t *device;
	UINT8 bdaddr[BD_ADDR_LEN];
	INT8 ret;
	char bdaddr_str[BD_ADDR_STR_LEN];
	UINT8 *rev_bdaddr = bdaddr;

	if (any_device_is_in_state(GAP_CONNECTION_STATE_ACL_CONNECTING) || any_device_is_in_state(GAP_CONNECTION_STATE_ACL_DISCONNECTING) || any_device_is_in_state(GAP_CONNECTION_STATE_LINK_PARAM_UPDATING))
	{
		logw("At least one remote device is already in connect/disconnect/update state, cannot start new disconnection!");
		return STATUS_ERR_BUSY;
	}


	if (connected_device_list_idx >= MAX_NUM_CONNECTED_DEVICE)
		return STATUS_ERR_INAVALID_CONNENCTION;


	device = g_local_adapter.connected_device[connected_device_list_idx];

	if (!device)
		return STATUS_ERR_INAVALID_CONNENCTION;

	REVERSE_ARRAY_TO_STREAM(rev_bdaddr, device->bdaddr, BD_ADDR_LEN);
	BDADDR_TO_STRING(bdaddr_str, device->bdaddr);

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	if (device_is_in_state(connected_device_list_idx, GAP_CONNECTION_STATE_ACL_CONNECTING))
	{
		logd("Remote device %s is in connecting state, disconnecting!", bdaddr_str);
		pm_disconnect_cb(device, FALSE);
		remote_command_timer_stop(connected_device_list_idx);
		hci_ble_cancel_create_ll_conn();
		return STATUS_SUCCESS;
	}
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

	if (!(device_is_in_state(connected_device_list_idx, GAP_CONNECTION_STATE_ACL_CONNECTED) || device_is_in_state(connected_device_list_idx, GAP_CONNECTION_STATE_LINK_PARAM_UPDATING)))
	{
		loge("Remote device %s is in GAP state %u, cannot start disconnection!", bdaddr_str, device_get_state(connected_device_list_idx));
		pm_disconnect_cb(device, FALSE);
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	}

	logd("Trying to disconnect from %s", bdaddr_str);

	l2cap_disconnect_req(device);

	device_set_state(connected_device_list_idx, GAP_CONNECTION_STATE_ACL_DISCONNECTING);

	start_operation(GAP_OPERATION_DISCONNECTING);

	ret = hci_disconnect(device->acl_handle, reason);
	if (ret == STATUS_ERR_DEVICE_ERROR) {
		/* Controller not available or controller is disconnected; cleanup the stack */
		controller_error_cleanup(device);
		return STATUS_SUCCESS;
	}
#if (PARANOID_STACK == TRUE)
	if (ret != STATUS_SUCCESS)
		return ret;
#else
	USE(ret);
#endif

	remote_command_timer_start(connected_device_list_idx);

	return STATUS_SUCCESS;
}

/* Function to be exposed to interface for requesting
 * connection parameter update from local host
 */
INT8 gap_req_update_conn_params(UINT8 connected_device_list_idx, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout)
{
	UINT8 local_feat, remote_feat;
	connected_device_t *device;
	if(connected_device_list_idx == MAX_NUM_CONNECTED_DEVICE)
		return STATUS_ERR_INVALID_PARAM;

	device = g_local_adapter.connected_device[connected_device_list_idx];

	if (!device)
		return STATUS_OPERATION_FINISHED_LOCAL_SUCCESS;

	if (any_device_is_in_state(GAP_CONNECTION_STATE_ACL_CONNECTING) || any_device_is_in_state(GAP_CONNECTION_STATE_ACL_DISCONNECTING) || any_device_is_in_state(GAP_CONNECTION_STATE_LINK_PARAM_UPDATING))
	{
		logw("At least one remote device is already in connect/disconnect/update state, cannot start new update!");
		return STATUS_ERR_BUSY;
	}

	if (!conn_param_is_valid(interval_min, interval_max, conn_latency, sup_timeout))
		return STATUS_ERR_INVALID_PARAM;

	device_set_state(device->idx, GAP_CONNECTION_STATE_LINK_PARAM_UPDATING);
	start_operation(GAP_OPERATION_UPDATING_CONN_PARAMS);

	local_feat = g_local_adapter.ble_local_features[HCI_LE_FEATURE_CONN_PARAM_REQ_PROCEDURE_OFFSET];
	remote_feat = device->ble_remote_features[HCI_LE_FEATURE_CONN_PARAM_REQ_PROCEDURE_OFFSET];
	remote_command_timer_start(device->idx);
	if (!(local_feat & remote_feat & HCI_LE_FEATURE_CONN_PARAM_REQ_PROCEDURE_MASK))
	{
		//We don't support the Connection Parameter Request Procedure

		//Do LL connection update request if device is master
		if (device->local_link_role == LINK_ROLE_MASTER)
			return hci_ble_upd_ll_conn_params(device->acl_handle, interval_min, interval_max, conn_latency, sup_timeout, 0x00, 0x00);

		//Do L2CAP connection parameter update request if device is slave
		return l2cap_send_conn_param_update_req(device, interval_min, interval_max, conn_latency, sup_timeout);
	}
	else
		return hci_ble_upd_ll_conn_params(device->acl_handle, interval_min, interval_max, conn_latency, sup_timeout, 0x00, 0x00);
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (TEST_CODE == TRUE && LE_PING_ENABLE == TRUE)
/* Function to be exposed to interface for writing
 * authenticated payload timeout
 */
INT8 gap_read_authpayload_timeout(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return STATUS_ERR_INAVALID_CONNENCTION;

	return hci_ble_read_authpayload_timeout(device->acl_handle);
}

/* Function to be exposed to interface for writing
 * authenticated payload timeout
 */
INT8 gap_write_authpayload_timeout(UINT8 conn_id, UINT16 authpayload_timeout_ms)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return STATUS_ERR_INAVALID_CONNENCTION;

	UINT16 authpayload_timeout = authpayload_timeout_ms/10;

	if (authpayload_timeout<0x0001) // Range defined in HCI BT 4.1 spec for hci_ble_write_authpayload_timeout
		authpayload_timeout=0x0BB8;
	if(authpayload_timeout < ((device->conn_interval)*(1+device->conn_latency)))
		authpayload_timeout = ((device->conn_interval)*(1+device->conn_latency)); // Condition defined in HCI BT 4.1 spec for hci_ble_write_authpayload_timeout

	return hci_ble_write_authpayload_timeout(device->acl_handle, authpayload_timeout);
}
#endif /* TEST_CODE == TRUE && LE_PING_ENABLE == TRUE */

INT8 gap_set_data_len(UINT8 conn_id, UINT16 tx_octets)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);
	UINT16 tx_time;

	if (!device)
		return STATUS_ERR_INAVALID_CONNENCTION;

	// tx_octet range for comparison defined in HCI BT 4.2 spec
	if(tx_octets<DLE_MIN_TX_OCTECTS || tx_octets>DLE_MAX_TX_OCTECTS)
		return STATUS_ERR_INVALID_PARAM;
	if(tx_octets>g_local_adapter.gap_data.max_tx_octets)
		return STATUS_ERR_INVALID_PARAM;
	tx_time = ((14 /*byte air packet header*/ * 8 /*bits*/) + (tx_octets * 8 /*bits*/ ));
	if(tx_time>g_local_adapter.gap_data.max_tx_time)
		return STATUS_ERR_INVALID_PARAM;
	if(tx_time<DLE_MIN_TX_TIME || tx_time>DLE_MAX_TX_TIME)
		return STATUS_ERR_INVALID_PARAM;
	return hci_ble_set_data_len(device->acl_handle, tx_octets, tx_time);
}

/* Function called from L2CAP upon receiving an L2CAP
 * connection parameter update request from remote host
 */
INT8 gap_update_conn_params(UINT8 connected_device_list_idx, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout)
{
	connected_device_t *device;
	UINT8 dummy_pkt[HCI_EVT_LE_CONN_PARAM_UPDATE_PARAM_SIZE], *d_pkt;

	if(connected_device_list_idx >= MAX_NUM_CONNECTED_DEVICE)
		return STATUS_ERR_INVALID_PARAM;

	device = g_local_adapter.connected_device[connected_device_list_idx];
	d_pkt = &dummy_pkt[0];

	if (!device)
		return STATUS_ERR_INAVALID_CONNENCTION;

	logi("");
	if (conn_param_is_valid(interval_min, interval_max, conn_latency, sup_timeout))
	{
		/* Values are valid */
		logd("interval_min %d, interval_max %d, conn_latency %d, sup_timeout %d", interval_min, interval_max, conn_latency, sup_timeout);
		device_set_state(connected_device_list_idx, GAP_CONNECTION_STATE_LINK_PARAM_UPDATING);
		start_operation(GAP_OPERATION_UPDATING_CONN_PARAMS);
		UINT8_TO_STREAM(d_pkt, 0); //Status
		UINT16_TO_STREAM(d_pkt, device->acl_handle); //ACL handle
		l2cap_recv_conn_param_update_evt(dummy_pkt, HCI_EVT_LE_CONN_PARAM_UPDATE_PARAM_SIZE); //Send accept pkt
		hci_ble_upd_ll_conn_params(device->acl_handle, interval_min, interval_max, conn_latency, sup_timeout, 0x00, 0x00);
	}
	else
	{
		UINT8_TO_STREAM(d_pkt, 1); //Status
		UINT16_TO_STREAM(d_pkt, device->acl_handle); //ACL handle
		l2cap_recv_conn_param_update_evt(dummy_pkt, HCI_EVT_LE_CONN_PARAM_UPDATE_PARAM_SIZE); //Send reject pkt
	}

	return STATUS_SUCCESS;
}

INT8 gap_handle_command_complete(UINT16 opcode, UINT8 status, UINT8* evt, UINT8 len)
{
	BOOLEAN bgscan;
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	UINT8 adv_data[ADV_DATA_LEN], scanresp_data[ADV_DATA_LEN];
	UINT8 data_len;
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

	switch (opcode)
	{
#if (LE_PING_ENABLE == TRUE)
	case HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT:
		if (status == HCI_EVENT_STATUS_SUCCESS)
		{
			UINT16 conn_handle=0, auth_payload_timeout=0;
			STREAM_TO_UINT16(conn_handle, evt);
			STREAM_TO_UINT16(auth_payload_timeout, evt);
			logd("[LE_PING]HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT succeeded conn_handle:%x, auth_payload_timeout=%x", conn_handle, auth_payload_timeout);
#if (TEST_CODE == TRUE)
			UINT8 dev_idx=get_connected_device_idx_by_handle(conn_handle);
			pm_read_authpayload_timeout_cb(dev_idx, auth_payload_timeout);
#endif //TEST_CODE
		}
		else
			logd("[LE_PING]HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT failed");
		break;
	case HCI_CMD_WRITE_AUTHPAYLOAD_TIMEOUT:
		if (status == HCI_EVENT_STATUS_SUCCESS)
		{
			UINT16 conn_handle=0;
			STREAM_TO_UINT16(conn_handle, evt);
			logd("[LE_PING]HCI_CMD_LE_WRITE_AUTHPAYLOAD_TIMEOUT succeeded conn_handle:%x", conn_handle);
		}
		else
			logd("[LE_PING]HCI_CMD_LE_WRITE_AUTHPAYLOAD_TIMEOUT failed");
		break;
#endif /* LE_PING_ENABLE == TRUE */
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	case HCI_CMD_LE_SET_ADV_PARAM:
		if (g_local_adapter.gap_data.adv_scanresp_data_changed)
		{
			data_len = get_formatted_adv_data(adv_data);
			hci_ble_set_adv_data(data_len, adv_data);
		}
		else
			hci_ble_set_adv_enable(1); /* Enable adv */
		break;
	case HCI_CMD_LE_SET_ADV_DATA:
		data_len = get_formatted_scanresp_data(scanresp_data);
		g_local_adapter.gap_data.adv_scanresp_data_changed = FALSE;
		if (!data_len) /* If no scan response data added, mirror adv data */
			data_len = get_formatted_adv_data(scanresp_data);
		hci_ble_set_scan_rsp_data(data_len, scanresp_data);
		break;
	case HCI_CMD_LE_SET_SCAN_RESP_DATA:
		hci_ble_set_adv_enable(1); /* Enable adv */
		break;
	case HCI_CMD_LE_SET_ADV_ENABLE:
		if (adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_DISABLING))
		{
			logd("Advertisement stopped");
			adapter_enter_adv_state(GAP_ADAPTER_STATE_ADV_DISABLED);

			if (g_local_adapter.gap_data.adapter_state & GAP_ADAPTER_STATE_ADV_RESTARTING)
			{
				g_local_adapter.gap_data.adapter_state &= ~GAP_ADAPTER_STATE_ADV_RESTARTING;
				UINT32 timeout_msec = g_local_adapter.gap_data.adv_timeout_msec;
				UINT8 type = g_local_adapter.gap_data.adv_type;
				UINT8 flags = g_local_adapter.gap_data.adv_flags;
				UINT8 *remote_bd_addr = g_local_adapter.gap_data.adv_remote_bd_addr;
				UINT8 addr_type = g_local_adapter.gap_data.adv_addr_type;
				UINT16 adv_int_min = g_local_adapter.gap_data.adv_int_min;
				UINT16 adv_int_max = g_local_adapter.gap_data.adv_int_max;
				BOOLEAN use_whitelist = g_local_adapter.gap_data.adv_use_whitelist;
				BOOLEAN background = g_local_adapter.gap_data.adv_is_background;
				gap_start_advertise(timeout_msec, type, flags, remote_bd_addr, addr_type, adv_int_min, adv_int_max, use_whitelist, background);
				end_operation(GAP_OPERATION_ADVERTISING);
			}
			else
			{
				end_operation(GAP_OPERATION_ADVERTISING);
				finish_transac_and_process_new_req();
			}
		}
		else
		{
			logd("Advertisement started");
			adapter_enter_adv_state(GAP_ADAPTER_STATE_ADV_ENABLED);
			if (adapter_is_disabling())
				gap_stop_advertise();
			else
				finish_transac_and_process_new_req();
		}
		break;
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	case HCI_CMD_LE_SET_SCAN_PARAM:
		hci_ble_set_scan_enable(1, 1); /* Enable scan, filter duplicates */
		break;
	case HCI_CMD_LE_SET_SCAN_ENABLE:
		if (adapter_is_in_scn_state(GAP_ADAPTER_STATE_SCN_DISABLING))
		{
			logd("Scan stopped");
			adapter_enter_scn_state(GAP_ADAPTER_STATE_SCN_DISABLED);

			if (g_local_adapter.gap_data.adapter_state & GAP_ADAPTER_STATE_SCN_RESTARTING)
			{
				UINT32 timeout_msec = g_local_adapter.gap_data.scan_timeout_msec;
				BOOLEAN active = g_local_adapter.gap_data.scan_isactive;
				BOOLEAN limited = g_local_adapter.gap_data.scan_is_limited;
				BOOLEAN use_whitelist = g_local_adapter.gap_data.scan_use_whitelist;
				BOOLEAN background = g_local_adapter.gap_data.scan_is_background;
				UINT16 scan_int = g_local_adapter.gap_data.scan_int;
				UINT16 scan_win = g_local_adapter.gap_data.scan_win;
				UINT16 *filter_uuids = g_local_adapter.gap_data.scan_filter_uuids;
				g_local_adapter.gap_data.adapter_state &= ~GAP_ADAPTER_STATE_SCN_RESTARTING;
				bgscan = adapter_is_bgscanning();
				if (bgscan)
					adapter_exit_bgscanning_state();
				gap_start_scan(g_local_adapter.gap_data.scan_req_trans_id, timeout_msec, active, limited, use_whitelist, background, scan_int, scan_win, filter_uuids, FALSE);
				if (bgscan)
					end_operation(GAP_OPERATION_BG_SCANNING);
				else
					end_operation(GAP_OPERATION_FG_SCANNING);
			}
			else
			{
				if (!adapter_is_disabling())
				{
					UINT8 app_idx = get_appid_from_transid(g_local_adapter.gap_data.scan_req_trans_id);
					if ((app_idx < MAX_NUMBER_OF_APP) && g_local_adapter.app_list[app_idx]
						&& g_local_adapter.app_list[app_idx]->app_device_control_cb && g_local_adapter.app_list[app_idx]->app_device_control_cb->iLE_scan_completed_cb)
						g_local_adapter.app_list[app_idx]->app_device_control_cb->iLE_scan_completed_cb(g_local_adapter.gap_data.scan_req_trans_id);
				}
				g_local_adapter.gap_data.scan_req_trans_id = INVALID_TRANS_ID;

				if (adapter_is_bgscanning())
				{
					adapter_exit_bgscanning_state();
					end_operation(GAP_OPERATION_BG_SCANNING);
				}
				else
					end_operation(GAP_OPERATION_FG_SCANNING);
				finish_transac_and_process_new_req();
			}
		}
		else
		{
			logd("Scan started");
			adapter_enter_scn_state(GAP_ADAPTER_STATE_SCN_ENABLED);
			if (!adapter_is_bgscanning())
				memset(g_local_adapter.gap_data.discovered_device.bdaddr, 0, BD_ADDR_LEN);
			if (adapter_is_disabling())
				gap_stop_scan(FALSE);
			else
				finish_transac_and_process_new_req();
		}
		break;
	case HCI_CMD_LE_CREATE_CONN_CANCEL:
		adapter_restore_prev_state();
		finish_transac_and_process_new_req();
		end_operation(GAP_OPERATION_CONNECTING);
		break;
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
	case HCI_CMD_LE_ADD_DEV_TO_WHITE_LIST:
		if (status == HCI_EVENT_STATUS_SUCCESS)
			g_local_adapter.num_whitelist_entries++;
		if (get_root_operation() == GAP_OPERATION_UPDATING_WHITELIST)
			adapter_restore_prev_state();
		finish_transac_and_process_new_req();
		end_operation(GAP_OPERATION_UPDATING_WHITELIST);
		break;
	case HCI_CMD_LE_REMOVE_DEV_FRM_WHITE_LIST:
		if (status == HCI_EVENT_STATUS_SUCCESS)
			g_local_adapter.num_whitelist_entries--;
		if (get_root_operation() == GAP_OPERATION_UPDATING_WHITELIST)
			adapter_restore_prev_state();
		finish_transac_and_process_new_req();
		end_operation(GAP_OPERATION_UPDATING_WHITELIST);
		break;
	case HCI_CMD_LE_CLEAR_WHITE_LIST:
		if (status == HCI_EVENT_STATUS_SUCCESS)
			g_local_adapter.num_whitelist_entries = 0;
		if (get_root_operation() == GAP_OPERATION_UPDATING_WHITELIST)
			adapter_restore_prev_state();
		finish_transac_and_process_new_req();
		end_operation(GAP_OPERATION_UPDATING_WHITELIST);
		break;
#if (PRIVACY_FEATURE == TRUE)
	case HCI_CMD_LE_SET_RANDOM_ADDRESS:
		if(status == HCI_EVENT_STATUS_SUCCESS)
		{
			if (LL_PRIVACY_IS_SUPPORTED)
				g_local_adapter.addr_type = GAP_ADDRESS_TYPE_RPA_OR_RANDOM;
			else
				g_local_adapter.addr_type = GAP_ADDRESS_TYPE_RANDOM;
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
			gap_restart_advertise();
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
		}
		break;
#endif
#if (CONTROLLER_PRIVACY)
	case HCI_CMD_LE_ADD_DEV_TO_RESOLVING_LIST:
		if (status == HCI_EVENT_STATUS_SUCCESS)
			g_local_adapter.num_resolvinglist_entries++;

		/* The controller currently generates RPAs once every timeout. hence
		 * newly added entries will have local RPA field unpopulated till the
		 * next timeout cycle. Work around it by toggling address resolution
		 * which would cause the timer to fire and all RPAs get (re)genrated
		 */
		//FIXME: Remove when FW implements immediate local RPA generation
		hci_ble_set_addr_resolution_enable(0);
		hci_ble_set_addr_resolution_enable(1);

		if (get_root_operation() == GAP_OPERATION_UPDATING_RL)
			adapter_restore_prev_state();
		finish_transac_and_process_new_req();
		end_operation(GAP_OPERATION_UPDATING_RL);
		break;
	case HCI_CMD_LE_REMOVE_DEV_FROM_RESOLVING_LIST:
		if (status == HCI_EVENT_STATUS_SUCCESS)
			g_local_adapter.num_resolvinglist_entries--;
		if (get_root_operation() == GAP_OPERATION_UPDATING_RL)
			adapter_restore_prev_state();
		finish_transac_and_process_new_req();
		end_operation(GAP_OPERATION_UPDATING_RL);
		break;
	case HCI_CMD_LE_CLEAR_RESOLVING_LIST:
		if (status == HCI_EVENT_STATUS_SUCCESS)
			g_local_adapter.num_resolvinglist_entries = 0;
		if (get_root_operation() == GAP_OPERATION_UPDATING_RL)
			adapter_restore_prev_state();
		finish_transac_and_process_new_req();
		end_operation(GAP_OPERATION_UPDATING_RL);
		break;
#endif /* CONTROLLER_PRIVACY */
	}

	return STATUS_SUCCESS;
}

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

static BOOLEAN update_connected_device(connected_device_t *device)
{
	BOOLEAN fromremote = FALSE;
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	UINT8 aidx = get_idx_from_autoconn_list(device->id_addr.bdaddr);
	if (aidx != MAX_NUM_CONNECTED_DEVICE)
		g_local_adapter.gap_data.autoconn_dev[aidx]->conn_state = DEVICE_CONNECTED;
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

	//Check if we initiated the connection
	if (device_is_in_state(device->idx, GAP_CONNECTION_STATE_ACL_CONNECTING))
		device_set_state(device->idx, GAP_CONNECTION_STATE_ACL_CONNECTED);
	else
	{
		//Connection was initiated from remote device
		fromremote = TRUE;
		g_local_adapter.gap_data.prev_adapter_state = g_local_adapter.gap_data.adapter_state;
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
		adapter_enter_adv_state(GAP_ADAPTER_STATE_ADV_DISABLED);
		end_operation(GAP_OPERATION_ADVERTISING);
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
		device_set_state(device->idx, GAP_CONNECTION_STATE_ACL_CONNECTED);
	}

	adapter_restore_prev_state();
	l2cap_connect_req(device, L2CAP_ATT_PSM);
	pm_connect_cb(device, STATUS_SUCCESS);

#if (LE_PING_ENABLE == TRUE)
	//Write Authenticated payload timeout to controller which will be used for LL_PING if the link is encrypted
	logd("[LE_PING]GAP hci_ble_write_authpayload_timeout acl_handle:%x", device->acl_handle);

	UINT16 authpayload_timeout = CONNECTION_AUTHPAYLOAD_TIMEOUT;
	if (authpayload_timeout < (device->conn_interval * (1 + device->conn_latency)))
		authpayload_timeout = (device->conn_interval * (1 + device->conn_latency));

	hci_ble_write_authpayload_timeout(device->acl_handle, authpayload_timeout);
#endif /* LE_PING_ENABLE == TRUE */

	//Try to find out the remote device's features before completing the connection procedure
	if (g_local_adapter.ble_local_features[HCI_LE_FEATURE_SLAVE_INIT_FEAT_EXCHANGE_OFFSET] & HCI_LE_FEATURE_SLAVE_INIT_FEAT_EXCHANGE_MASK)
		hci_ble_read_remote_feat(device->acl_handle);
	return fromremote;
}

INT8 gap_handle_conn_complete(UINT8* buffer, UINT16 len, BOOLEAN enhanced)
{
	UINT8 status, role, bdaddr_type;
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
	UINT8 clock_accuracy;
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */
	UINT16 conn_handle, conn_interval, con_latency, sup_timeout;
	UINT8 dummy_bdaddr[BD_ADDR_LEN] = {0,0,0,0,0,0};
	UINT8 peer_addr[BD_ADDR_LEN], peer_rpa[BD_ADDR_LEN] = {0,0,0,0,0,0}, local_rpa[BD_ADDR_LEN] = {0,0,0,0,0,0};
	char bdaddr_str[BD_ADDR_STR_LEN];
	UINT8 idx;
	connected_device_t *device;
	BOOLEAN fromremote = FALSE, resolving = FALSE;
	logi("");


	STREAM_TO_UINT8(status, buffer);
	STREAM_TO_UINT16(conn_handle, buffer);
	STREAM_TO_UINT8(role, buffer);
	STREAM_TO_UINT8(bdaddr_type, buffer);
	STREAM_TO_BDADDR(peer_addr, buffer);
	if (enhanced)
	{
		STREAM_TO_BDADDR(local_rpa, buffer);
		STREAM_TO_BDADDR(peer_rpa, buffer);
	}
	STREAM_TO_UINT16(conn_interval, buffer);
	STREAM_TO_UINT16(con_latency, buffer);
	STREAM_TO_UINT16(sup_timeout, buffer);
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
	STREAM_TO_UINT8(clock_accuracy, buffer);
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */

	idx = get_connected_device_idx_by_bdaddr(peer_addr);

	if ((idx == MAX_NUM_CONNECTED_DEVICE) && enhanced)
		idx = get_connected_device_idx_by_bdaddr(peer_rpa);

	if (status == 0)
	{
		BDADDR_TO_STRING(bdaddr_str, peer_addr);

		if (idx == MAX_NUM_CONNECTED_DEVICE)
		{
			logd("Device %s doesn't exist in connection list! Creating...", bdaddr_str);
			idx = find_first_free_connected_device_slot();
			if (idx == MAX_NUM_CONNECTED_DEVICE)
			{
				loge("Already reached the limit of %u connected devices!", MAX_NUM_CONNECTED_DEVICE);
				hci_disconnect(conn_handle, GAP_DISCONNECT_REASON_TERM_CONNECTION_RESOURCE);
				end_operation(GAP_OPERATION_CONNECTING);
				return STATUS_ERR_INSUFFICIENT_RESOURCES;
			}

			g_local_adapter.connected_device[idx] = (connected_device_t *)osa_create_connected_device(conn_handle);
		}
		else
		{
			remote_command_timer_stop(idx);
			if (device_is_in_state(idx, GAP_CONNECTION_STATE_ACL_CONNECTED) || device_is_in_state(idx, GAP_CONNECTION_STATE_ACL_DISCONNECTING))
			{
				loge("Remote device %s is in GAP state %u, cannot process new connection!", bdaddr_str, device_get_state(idx));
				pm_connect_cb(g_local_adapter.connected_device[idx], GAP_CONNECT_ERROR_ACL_CONNECTION_ALREADY_EXISTS);
				end_operation(GAP_OPERATION_CONNECTING);
				return STATUS_ERR_BUSY;
			}
		}

		log("Connection to %s completed successfully!\n", bdaddr_str);
		device = g_local_adapter.connected_device[idx];

		device->l2cap_state = L2CAP_STATE_CLOSED;
		device->pm_device_data.init_done = FALSE;
#if (SMP_FEATURE == TRUE)
		/* Update the links encryption state.
		 * Set it to security level 0 - no encryption
		 */
		/*
		device->link_enc_state.secuirty_level = SMP_SEC_LVL_1;
		device->link_enc_state.key_size = 0;
		device->link_enc_state.key_type = SMP_MGR_SEC_NONE;
		device->link_enc_state.valid = FALSE;
		*/
		memset(&device->link_enc_state, 0, sizeof(device->link_enc_state));
#endif /* SMP_FEATURE */
#if (CONTROLLER_PRIVACY == TRUE)
		device->car_supported = PEER_CAR_SUPPORT_UNKNOWN;
#endif /* CONTROLLER_PRIVACY */
		device->acl_handle = conn_handle;
		osa_save_acl_handle(idx, conn_handle);
		memcpy(&device->bdaddr, &peer_addr, BD_ADDR_LEN);
		if (memcmp(peer_rpa, dummy_bdaddr, BD_ADDR_LEN) != 0)
		{
			memcpy(device->ota_bdaddr, &peer_rpa, BD_ADDR_LEN);
			device->bdaddr_type = GAP_ADDRESS_TYPE_RANDOM;
		}
		else
		{
			memcpy(device->ota_bdaddr, &peer_addr, BD_ADDR_LEN);
			device->bdaddr_type = bdaddr_type;
		}

		if (memcmp(local_rpa, dummy_bdaddr, BD_ADDR_LEN) == 0)
		{
			if(LL_PRIVACY_IS_SUPPORTED)
			{
				memcpy(device->local_bdaddr, g_local_adapter.bdaddr, BD_ADDR_LEN);
				device->local_addr_type = GAP_ADDRESS_TYPE_RANDOM;
			}
			else
			{
				memcpy(device->local_bdaddr, g_local_adapter.bdaddr, BD_ADDR_LEN);
				device->local_addr_type = g_local_adapter.addr_type;
			}
		}
		else
		{
			memcpy(device->local_bdaddr, local_rpa, BD_ADDR_LEN);
			device->local_addr_type = GAP_ADDRESS_TYPE_RANDOM;
		}
		switch(bdaddr_type)
		{
			case GAP_ADDRESS_TYPE_PUBLIC:
			case GAP_ADDRESS_TYPE_RPA_OR_PUBLIC:
			{
				memcpy(device->id_addr.bdaddr, peer_addr, BD_ADDR_LEN);
				device->id_addr.type = GAP_ADDRESS_TYPE_PUBLIC;
			}
				break;
			case GAP_ADDRESS_TYPE_RANDOM:
			case GAP_ADDRESS_TYPE_RPA_OR_RANDOM:
			{
				memcpy(device->id_addr.bdaddr, peer_addr, BD_ADDR_LEN);
				device->id_addr.type = GAP_ADDRESS_TYPE_RANDOM;
			}
				break;
			default:
				logw("Unknown address type %02x", bdaddr_type);
				break;
		}
		logi("perr_adr set: %d got: %d", device->bdaddr_type, bdaddr_type);
		logi("peer bdaddr:  [%02x:%02x:%02x:%02x:%02x:%02x]", g_local_adapter.connected_device[idx]->ota_bdaddr[0], g_local_adapter.connected_device[idx]->ota_bdaddr[1], g_local_adapter.connected_device[idx]->ota_bdaddr[2], g_local_adapter.connected_device[idx]->ota_bdaddr[3], g_local_adapter.connected_device[idx]->ota_bdaddr[4], g_local_adapter.connected_device[idx]->ota_bdaddr[5]);
		device->local_link_role = role;
		device->conn_interval = conn_interval;
		device->conn_latency = con_latency;
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
		device->sup_timeout = sup_timeout;
		device->clock_accuracy = clock_accuracy;
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */
		device->l2cap_state = L2CAP_STATE_CLOSED;
		device->idx = idx;

		logd("conn_handle=0x%x, role=%u, bdaddr_type=%u, peer_addr=%s (%u), conn_interval=%u, con_latency=%u, sup_timeout=%u", conn_handle, role, bdaddr_type, bdaddr_str, idx, conn_interval, con_latency, sup_timeout);

		/* Check and resolve if necessary */
#if (HOST_PRIVACY)
		if ((g_local_adapter.privacy_enabled == LE_PRIVACY_EN) && (BLE_IS_RESOLVE_BDADDR(device->bdaddr)))
		{
			smpm_req_handler(create_req_for_conn_comp_rpa_resolution(device->bdaddr));
			resolving = TRUE;
		}
#endif /* HOST_PRIVACY */

		/* Do book-keeping and state changes */
		if (!resolving)
			fromremote = update_connected_device(device);
	}
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	else if (status == GAP_CONNECT_ERROR_DIRECTED_ADVERTISING_TIMEOUT) /* Direct advertising timeout */
	{
		logw("Directed Advertising timed out!");
		adapter_enter_adv_state(GAP_ADAPTER_STATE_ADV_DISABLED);
		end_operation(GAP_OPERATION_ADVERTISING);
		return STATUS_SUCCESS;
	}
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
	else /* Connection failed */
	{
		if (idx == MAX_NUM_CONNECTED_DEVICE)
			idx = get_first_device_in_state(GAP_CONNECTION_STATE_ACL_CONNECTING);
		if (idx != MAX_NUM_CONNECTED_DEVICE)
		{
			remote_command_timer_stop(idx);
			l2cap_connect_cb(g_local_adapter.connected_device[idx], FALSE);
			pm_connect_cb(g_local_adapter.connected_device[idx], status);
			device_set_state(idx, GAP_CONNECTION_STATE_ACL_DISCONNECTED);
			delete_connected_device(idx);
		}
		else
		{
			/* Do nothing */
		}

		loge("Connection failed : 0x%x", status);
		adapter_restore_prev_state();
	}

	if (!resolving)
	{
		if (!fromremote)
		{
			finish_transac_and_process_new_req();
			end_operation(GAP_OPERATION_CONNECTING);
		}
	}

	return STATUS_SUCCESS;
}

#if (LE_PING_ENABLE == TRUE)
INT8 gap_handle_authpayload_timeout_exp_evt(UINT8* buffer, UINT16 len)
{
	UINT16 conn_handle;
	JUMP_CUSTOM_LEN(buffer, 1); /* Skip event length */
	STREAM_TO_UINT16(conn_handle, buffer);
	logd("[LE_PING]conn_handle:0x%x", conn_handle);
	return STATUS_SUCCESS;
}
#endif /* LE_PING_ENABLE == TRUE */

INT8 gap_handle_data_len_change_evt(UINT8* buffer, UINT16 len)
{

	UINT16 conn_handle, max_tx_octets, max_tx_time, max_rx_octets, max_rx_time;
	BOOLEAN conn_used;
	UINT8 conn_id;
	UINT8 idx = 0;
	trans_id_t trans_id = INVALID_TRANS_ID;
	app_data_t* app_data=NULL;
	connected_device_t* device;
	logi("");
	STREAM_TO_UINT16(conn_handle, buffer);
	STREAM_TO_UINT16(max_tx_octets, buffer);
	STREAM_TO_UINT16(max_tx_time, buffer);
	STREAM_TO_UINT16(max_rx_octets, buffer);
	STREAM_TO_UINT16(max_rx_time, buffer);
	logd("conn_handle:0x%x max_tx_octets:%x, max_tx_time:%x, max_rx_octets:%x, max_rx_time:%x",
		conn_handle, max_tx_octets, max_tx_time, max_rx_octets, max_rx_time);
	conn_id = get_connected_device_idx_by_handle(conn_handle);
	device = get_connected_device_by_conn_id(conn_id);
	if (!device)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	for (idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
	{
		app_data = g_local_adapter.app_list[idx];
		if(app_data != NULL)
		{
			conn_used = is_conn_used(app_data, device);
 			if(conn_used && g_local_adapter.app_list[idx] && g_local_adapter.app_list[idx]->app_device_control_cb && g_local_adapter.app_list[idx]->app_device_control_cb->iLE_data_len_change_evt_cb)
				g_local_adapter.app_list[idx]->app_device_control_cb->iLE_data_len_change_evt_cb(trans_id, conn_id, max_tx_octets, max_tx_time, max_rx_octets, max_rx_time);
		}
	}
	return STATUS_SUCCESS;
}

INT8 gap_handle_disconn_complete(UINT8* buffer, UINT16 len)
{
	UINT8 status, reason;
	UINT16 conn_handle;
	UINT8 idx;
	UINT8 bdaddr[BD_ADDR_LEN];
	char bdaddr_str[BD_ADDR_STR_LEN];
	connected_device_t *device;
	UINT8 *rev_bdaddr = bdaddr;
	UINT8 aidx ;

	STREAM_TO_UINT8(status, buffer);
	STREAM_TO_UINT16(conn_handle, buffer);
	STREAM_TO_UINT8(reason, buffer);


	idx = get_connected_device_idx_by_handle(conn_handle);

	if (idx == MAX_NUM_CONNECTED_DEVICE)
	{
		loge("ACL handle 0x%x does not exist in connection list!", conn_handle);
		pm_disconnect_cb(NULL, FALSE);
		return STATUS_ERR_INAVALID_CONNENCTION;
	}

	device = g_local_adapter.connected_device[idx];

#if (PARANOID_STACK == TRUE)
	if (status == 0)
	{
#endif
		BDADDR_TO_STRING(bdaddr_str, device->bdaddr);
		REVERSE_ARRAY_TO_STREAM(rev_bdaddr, device->bdaddr, BD_ADDR_LEN);

#if (PARANOID_STACK == TRUE)
		if (device_is_in_state(idx, GAP_CONNECTION_STATE_ACL_DISCONNECTED))
		{
			loge("Remote device %s is already in GAP state DISCONNECTED!", bdaddr_str);
			pm_disconnect_cb(device, FALSE);
			delete_connected_device(idx);
			end_operation(GAP_OPERATION_DISCONNECTING);
			return STATUS_SUCCESS;
		}
#endif

		logw("Device %s disconnected due to 0x%x!", bdaddr_str, reason);

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
		aidx = get_idx_from_autoconn_list(device->id_addr.bdaddr);
		if (aidx != MAX_NUM_CONNECTED_DEVICE)
			g_local_adapter.gap_data.autoconn_dev[aidx]->conn_state = DEVICE_DISCONNECTED;
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

		if (device_is_in_state(idx, GAP_CONNECTION_STATE_ACL_DISCONNECTING))
		{
			//Disconnect was issued from here... l2cap is already disconnected
			device_set_state(idx, GAP_CONNECTION_STATE_ACL_DISCONNECTED);
			remote_command_timer_stop(idx);
		}
		else
		{
			//Disconnect came from remote end... disconnect l2cap
			start_operation(GAP_OPERATION_DISCONNECTING);
			if (device_is_in_state(idx, GAP_CONNECTION_STATE_LINK_PARAM_UPDATING))
				end_operation(GAP_OPERATION_UPDATING_CONN_PARAMS);
			if (device_is_in_state(idx, GAP_CONNECTION_STATE_ACL_CONNECTING))
				end_operation(GAP_OPERATION_CONNECTING);
			device_set_state(idx, GAP_CONNECTION_STATE_ACL_DISCONNECTED);
			l2cap_disconnect_cb(device, TRUE);
			remote_command_timer_stop(idx);
		}

		pm_disconnect_cb(device, reason);

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
		if (!adapter_is_disabling())
		{
			//Start connectable adv now if we had moved to non-connectable adv during connection (LLT not supported)
			if (!(g_local_adapter.ble_local_features[HCI_LE_FEATURE_CONN_PARAM_REQ_PROCEDURE_OFFSET] & HCI_LE_FEATURE_CONN_PARAM_REQ_PROCEDURE_MASK))
				if (adapter_is_in_adv_state(GAP_ADAPTER_STATE_ADV_ENABLED))
					gap_start_advertise(g_local_adapter.gap_data.adv_timeout_msec, g_local_adapter.gap_data.adv_type, g_local_adapter.gap_data.adv_flags, g_local_adapter.gap_data.adv_remote_bd_addr, g_local_adapter.gap_data.adv_addr_type, g_local_adapter.gap_data.adv_int_min, g_local_adapter.gap_data.adv_int_max, g_local_adapter.gap_data.adv_use_whitelist, g_local_adapter.gap_data.adv_is_background);
		}
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */


		delete_connected_device(idx);

#if (PARANOID_STACK == TRUE)
	}
	else
	{
		loge("Disconnection failed : 0x%x", status);
		pm_disconnect_cb(device, FALSE);
	}
#else
	USE(status);
#endif

	USE(reason);

	if (adapter_is_disabling())
		disconnect_one_device();

	finish_transac_and_process_new_req();
	end_operation(GAP_OPERATION_DISCONNECTING);

	return STATUS_SUCCESS;
}

/* Callback for connection parameter update complete event */
INT8 gap_handle_conn_param_update_cmpl(UINT8* buffer, UINT16 len)
{
	UINT16 acl_handle;
	UINT8* p_buf = buffer;
	UINT8 idx, status;
	UINT16 conn_interval = 0, conn_latency = 0, sup_timeout = 0;
	connected_device_t *device;
	logi("");

	STREAM_TO_UINT8(status, p_buf);

	if (status == HCI_EVENT_STATUS_CONTROLLER_BUSY)
	{
		idx = get_first_device_in_state(GAP_CONNECTION_STATE_LINK_PARAM_UPDATING);
		loge("Connection parameter update for device %u failed with %02x", idx, status);
	}
	else
	{
		STREAM_TO_UINT16(acl_handle, p_buf);
		idx = get_connected_device_idx_by_handle(acl_handle);
	}

	if (idx >= MAX_NUM_CONNECTED_DEVICE)
			return STATUS_ERR_INAVALID_CONNENCTION; /* TODO: check the return consequence*/

	device = g_local_adapter.connected_device[idx];

	if (!status)
	{
		STREAM_TO_UINT16(conn_interval, p_buf);
		STREAM_TO_UINT16(conn_latency, p_buf);
		STREAM_TO_UINT16(sup_timeout, p_buf);

		device->conn_interval = conn_interval;
		device->conn_latency = conn_latency;
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
		device->sup_timeout = sup_timeout;
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */
	}

	device_set_state(idx, GAP_CONNECTION_STATE_ACL_CONNECTED);

	pm_conn_param_update_cb(status, device->idx, conn_interval, conn_latency, sup_timeout);

	end_operation(GAP_OPERATION_UPDATING_CONN_PARAMS);
	remote_command_timer_stop(idx);

	return STATUS_SUCCESS;
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (PRIVACY_FEATURE == TRUE)
INT8 gap_enable_host_privacy(UINT8 enable)
{
	logi("");
	if (g_local_adapter.privacy_enabled == enable)
		return STATUS_OPERATION_FINISHED_LOCAL_SUCCESS;
	g_local_adapter.privacy_enabled = enable;
#if (ADV_IN_PUBLIC_ADDRESS != TRUE)
	if (LE_PRIVACY_EN == enable)
	{
		smpm_req_handler(create_req_for_rpa_generation());
		if (osa_create_timer(&g_local_adapter.gap_data.rpa_gen_timer, GAP_RPA_GEN_TIMER, GAP_RPA_GEN_TIMER_ISR, sizeof(GAP_RPA_GEN_TIMER)/sizeof(osa_timer_static_t), rpa_timeout_cb, 0) == 0)
			osa_start_timer(&g_local_adapter.gap_data.rpa_gen_timer, GAP_RPA_GEN_TIMER, (GAP_RPA_GEN_COMMAND_TIMEOUT_SEC * 1000), rpa_timeout_cb, 0);
	}
	else
	{
		if (osa_is_timer_active(&g_local_adapter.gap_data.rpa_gen_timer, GAP_RPA_GEN_TIMER, 0))
		{
			osa_stop_timer(&g_local_adapter.gap_data.rpa_gen_timer, GAP_RPA_GEN_TIMER, 0);
			osa_delete_timer(&g_local_adapter.gap_data.rpa_gen_timer, GAP_RPA_GEN_TIMER);
		}
		g_local_adapter.addr_type = GAP_ADDRESS_TYPE_PUBLIC;
		memcpy(g_local_adapter.bdaddr, g_local_adapter.static_bdaddr, BD_ADDR_LEN);
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
		if (!adapter_is_disabling())
			gap_restart_advertise();
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
	}
#endif /* ADV_IN_PUBLIC_ADDRESS == FALSE */
	return STATUS_OPERATION_FINISHED_LOCAL_SUCCESS;
}
#endif /* PRIVACY_FEATURE */

/* Callback for read remote features request
 * Connection parameter update from local host
 * is triggered from here
 */
INT8 gap_handle_conn_read_remote_feat_cmpl(UINT8* buffer, UINT16 len)
{
	UINT16 acl_handle;
	UINT8 *p_buf = buffer;
	UINT8 status, idx;
	connected_device_t *device;

	STREAM_TO_UINT8(status, p_buf);
	STREAM_TO_UINT16(acl_handle, p_buf);

	idx = get_connected_device_idx_by_handle(acl_handle);

	if (idx == MAX_NUM_CONNECTED_DEVICE)
		return STATUS_ERR_INAVALID_CONNENCTION;

	device = g_local_adapter.connected_device[idx];


	if (status == 0)
		memcpy(device->ble_remote_features, p_buf, 8);

	return STATUS_SUCCESS;
}

/* Callback for remote connection parameter request */
INT8 gap_handle_remote_conn_param_req(UINT8* buffer, UINT16 len)
{
	UINT16 acl_handle;
	UINT8* p_buf = buffer;
	UINT16 interval_min, interval_max, conn_latency, sup_timeout;

	STREAM_TO_UINT16(acl_handle, p_buf);
	STREAM_TO_UINT16(interval_min, p_buf);
	STREAM_TO_UINT16(interval_max, p_buf);
	STREAM_TO_UINT16(conn_latency, p_buf);
	STREAM_TO_UINT16(sup_timeout, p_buf);

	if (conn_param_is_valid(interval_min, interval_max, conn_latency, sup_timeout))
	{
		/* Values are valid */
		UINT8 connected_device_idx = get_connected_device_idx_by_handle(acl_handle);

#if (PARANOID_STACK == TRUE)
		if (connected_device_idx == MAX_NUM_CONNECTED_DEVICE)
			return STATUS_ERR_INAVALID_CONNENCTION;
#endif

		device_set_state(connected_device_idx, GAP_CONNECTION_STATE_LINK_PARAM_UPDATING);
		end_operation(GAP_OPERATION_UPDATING_CONN_PARAMS);
		remote_command_timer_start(connected_device_idx);
		return hci_ble_rem_conn_param_req_rep(acl_handle, interval_min, interval_max, conn_latency, sup_timeout, 0x00, 0x00);
	}
	else
		return hci_ble_rem_conn_param_req_rej(acl_handle, 0x3B);
}

INT8 gap_init()
{
	logi("");
	g_local_adapter.gap_data.adapter_state = GAP_ADAPTER_STATE_IDLE;
	init_no_guard_q(&g_local_adapter.gap_data.pending_req_q);
	g_local_adapter.gap_data.adv_scanresp_data_changed = TRUE;
	g_local_adapter.gap_data.busy = FALSE;
	clear_all_operations();
	g_local_adapter.gap_data.remote_op_device = MAX_NUM_CONNECTED_DEVICE;
	return STATUS_SUCCESS;
}

void gap_cleanup()
{
	logi("");
	adapter_enter_disabling_state();

	start_operation(GAP_OPERATION_DISABLING);
#if (HOST_PRIVACY)
	gap_enable_host_privacy(LE_PRIVACY_DIS);
#endif /* HOST_PRIVACY */
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	gap_stop_advertise();
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	gap_stop_scan(FALSE);
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	disconnect_one_device();
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

	if (is_only_operation(GAP_OPERATION_DISABLING))
	{
		logd("Do CLeanup");
		do_cleanup();
	}
}
