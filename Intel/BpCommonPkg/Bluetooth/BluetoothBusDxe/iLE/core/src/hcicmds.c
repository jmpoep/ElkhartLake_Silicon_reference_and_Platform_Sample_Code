/** @file
  HCI command implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "utils.h"
#include "hci_host.h"
#include "error_code.h"

#if (TARGET_THREADX == TRUE)
#include "a4wp_srv.h"
#elif (TARGET_THREADX_RW == TRUE)
#include "hci_adapter.h"
#include "tx_app_define.h"
#include "tl.h"
#include "rwble.h"
#include "hci.h"
#endif

#if (TARGET_UEFI == FALSE)
/* These libraries are not available on UEFI platform */
#include <string.h>
#endif

#define MODULE_DBG_LVL HCI_DBG_LVL
#include "log.h"

INT8 hci_reset()
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE + HCI_CMD_RESET_PARAM_LEN, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_RESET);
	UINT8_TO_STREAM(p, HCI_CMD_RESET_PARAM_LEN);
	return hci_send_cmd(HCI_CMD_RESET, p_buf, HCI_CMD_RESET_PARAM_LEN);
}

INT8 hci_read_local_feat()
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_READ_LOCAL_FEAT_PARAM_LEN, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	logi("");

	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_READ_LOCAL_FEAT);
	UINT8_TO_STREAM(p, HCI_CMD_READ_LOCAL_FEAT_PARAM_LEN);
	return hci_send_cmd(HCI_CMD_READ_LOCAL_FEAT, p_buf,
			HCI_CMD_READ_LOCAL_FEAT_PARAM_LEN);
}

INT8 hci_ble_write_host_supported(UINT8 le_host_spt, UINT8 simul_le_host_spt)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_WRITE_LE_HOST_SUPPORTED_PARAM_LEN, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	logd("");

	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_WRITE_LE_HOST_SUPPORTED);
	UINT8_TO_STREAM(p, HCI_CMD_WRITE_LE_HOST_SUPPORTED_PARAM_LEN);
	UINT8_TO_STREAM(p, le_host_spt);
	UINT8_TO_STREAM(p, simul_le_host_spt);

	return hci_send_cmd(HCI_CMD_WRITE_LE_HOST_SUPPORTED, p_buf,
			HCI_CMD_WRITE_LE_HOST_SUPPORTED_PARAM_LEN);
}

INT8 hci_set_event_mask(UINT8 *event_mask)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_SET_EVENT_MASK_PARAM_LEN, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	logd("");

	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_SET_EVENT_MASK);
	UINT8_TO_STREAM(p, HCI_CMD_SET_EVENT_MASK_PARAM_LEN);
	ARRAY8_TO_STREAM(p, event_mask);

	return hci_send_cmd(HCI_CMD_SET_EVENT_MASK, p_buf,
			HCI_CMD_SET_EVENT_MASK_PARAM_LEN);
}

INT8 hci_ble_set_event_mask_page_2(UINT8 *event_mask)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_SET_EVENT_MASK_PAGE_2_PARAM_LEN, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	logd("");
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_SET_EVENT_MASK_PAGE_2);
	UINT8_TO_STREAM(p, HCI_CMD_SET_EVENT_MASK_PAGE_2_PARAM_LEN);
	ARRAY8_TO_STREAM(p, event_mask);

	return hci_send_cmd(HCI_CMD_SET_EVENT_MASK_PAGE_2, p_buf,
			HCI_CMD_SET_EVENT_MASK_PAGE_2_PARAM_LEN);
}

INT8 hci_ble_set_event_mask(UINT8 *event_mask)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_SET_EVENT_MASK_PARAM_LEN, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	logd("");
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_EVENT_MASK);
	UINT8_TO_STREAM(p, HCI_CMD_SET_EVENT_MASK_PARAM_LEN);
	ARRAY8_TO_STREAM(p, event_mask);

	return hci_send_cmd(HCI_CMD_LE_SET_EVENT_MASK, p_buf,
			HCI_CMD_SET_EVENT_MASK_PARAM_LEN);
}

INT8 hci_read_buffer_size(void)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_READ_BUFFER_SIZE_PARAM_LEN, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	logd("");
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_READ_BUFFER_SIZE);
	UINT8_TO_STREAM(p, HCI_CMD_READ_BUFFER_SIZE_PARAM_LEN);

	return hci_send_cmd(HCI_CMD_READ_BUFFER_SIZE, p_buf,
			HCI_CMD_READ_BUFFER_SIZE_PARAM_LEN);
}

INT8 hci_ble_read_buffer_size(void)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_READ_BUFFER_SIZE_PARAM_LEN, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	logd("");
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_LE_READ_BUFFER_SIZE);
	UINT8_TO_STREAM(p, HCI_CMD_LE_READ_BUFFER_SIZE_PARAM_LEN);

	return hci_send_cmd(HCI_CMD_LE_READ_BUFFER_SIZE, p_buf,
			HCI_CMD_LE_READ_BUFFER_SIZE_PARAM_LEN);
}

INT8 hci_read_bd_addr(void)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_READ_BD_ADDR_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	logd("");
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_READ_BD_ADDR);
	UINT8_TO_STREAM(p, HCI_CMD_READ_BD_ADDR_PARAM_SIZE);

	return hci_send_cmd(HCI_CMD_READ_BD_ADDR, p_buf,
			HCI_CMD_READ_BD_ADDR_PARAM_SIZE);
}

INT8 hci_ble_read_local_feat(void)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_READ_LOCAL_SUPPORTED_FEAT_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif

	logd("");
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_LE_READ_LOCAL_SUPPORTED_FEAT);
	UINT8_TO_STREAM(p, HCI_CMD_LE_READ_LOCAL_SUPPORTED_FEAT_PARAM_SIZE);

	return hci_send_cmd(HCI_CMD_LE_READ_LOCAL_SUPPORTED_FEAT, p_buf,
			HCI_CMD_LE_READ_LOCAL_SUPPORTED_FEAT_PARAM_SIZE);
}

INT8 hci_ble_read_remote_feat(UINT16 handle)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_READ_REMOTE_USED_FEAT_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_LE_READ_REMOTE_USED_FEAT);
	UINT8_TO_STREAM(p, HCI_CMD_LE_READ_REMOTE_USED_FEAT_PARAM_SIZE);
	UINT16_TO_STREAM(p, handle);

	return hci_send_cmd(HCI_CMD_LE_READ_REMOTE_USED_FEAT, p_buf,
			HCI_CMD_LE_READ_REMOTE_USED_FEAT_PARAM_SIZE);
}

#if (LE_PING_ENABLE==TRUE)
INT8 hci_ble_read_authpayload_timeout(UINT16 handle)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT);
	UINT8_TO_STREAM(p, HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT_PARAM_SIZE);
	UINT16_TO_STREAM(p, handle);

	return hci_send_cmd(HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT, p_buf,
			HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT_PARAM_SIZE);
}

INT8 hci_ble_write_authpayload_timeout(UINT16 handle, UINT16 authpayload_timeout)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_WRITE_AUTHPAYLOAD_TIMEOUT_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_WRITE_AUTHPAYLOAD_TIMEOUT);
	UINT8_TO_STREAM(p, HCI_CMD_WRITE_AUTHPAYLOAD_TIMEOUT_PARAM_SIZE);
	UINT16_TO_STREAM(p, handle);
	UINT16_TO_STREAM(p, authpayload_timeout);

	return hci_send_cmd(HCI_CMD_WRITE_AUTHPAYLOAD_TIMEOUT, p_buf,
			HCI_CMD_WRITE_AUTHPAYLOAD_TIMEOUT_PARAM_SIZE);
}
#endif// LE_PING_ENABLE==TRUE
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

INT8 hci_ble_write_adv_params(UINT16 adv_int_min, UINT16 adv_int_max,
		UINT8 adv_type, UINT8 addr_type_own, UINT8 addr_type_dir,
		UINT8 *direct_bda, UINT8 channel_map, UINT8 adv_filter_policy)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_SET_ADV_PARAM_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_ADV_PARAM);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_ADV_PARAM_PARAM_SIZE);

	UINT16_TO_STREAM(p, adv_int_min);
	UINT16_TO_STREAM(p, adv_int_max);
	UINT8_TO_STREAM(p, adv_type);
	UINT8_TO_STREAM(p, addr_type_own);
	UINT8_TO_STREAM(p, addr_type_dir);
	memcpy(p, direct_bda, BD_ADDR_LEN);
	p += BD_ADDR_LEN;
	UINT8_TO_STREAM(p, channel_map);
	UINT8_TO_STREAM(p, adv_filter_policy);

	return hci_send_cmd(HCI_CMD_LE_SET_ADV_PARAM, p_buf,
			HCI_CMD_LE_SET_ADV_PARAM_PARAM_SIZE);
}

INT8 hci_ble_set_adv_data(UINT8 data_len, UINT8 *p_data)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_SET_ADV_DATA_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_ADV_DATA);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_ADV_DATA_PARAM_SIZE);

	if (p_data != NULL && data_len > 0)
	{
		if (data_len > (HCI_CMD_LE_SET_ADV_DATA_PARAM_SIZE - 1))
			data_len = HCI_CMD_LE_SET_ADV_DATA_PARAM_SIZE - 1;

		UINT8_TO_STREAM(p, data_len);
		ARRAY_TO_STREAM(p, p_data, data_len);
	}
	return hci_send_cmd(HCI_CMD_LE_SET_ADV_DATA, p_buf,
			HCI_CMD_LE_SET_ADV_DATA_PARAM_SIZE);
}

INT8 hci_ble_set_scan_rsp_data(UINT8 data_len, UINT8 *p_scan_rsp)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_SET_SCAN_RESP_DATA_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_SCAN_RESP_DATA);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_SCAN_RESP_DATA_PARAM_SIZE);

	if (p_scan_rsp != NULL && data_len > 0)
	{

		if (data_len > (HCI_CMD_LE_SET_SCAN_RESP_DATA_PARAM_SIZE - 1))
			data_len = HCI_CMD_LE_SET_SCAN_RESP_DATA_PARAM_SIZE - 1;

		UINT8_TO_STREAM(p, data_len);
		ARRAY_TO_STREAM(p, p_scan_rsp, data_len);
	}
	return hci_send_cmd(HCI_CMD_LE_SET_SCAN_RESP_DATA, p_buf,
			HCI_CMD_LE_SET_SCAN_RESP_DATA_PARAM_SIZE);
}

INT8 hci_ble_set_adv_enable(UINT8 adv_enable)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_SET_ADV_ENABLE_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_ADV_ENABLE);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_ADV_ENABLE_PARAM_SIZE);

	UINT8_TO_STREAM(p, adv_enable);

	return hci_send_cmd(HCI_CMD_LE_SET_ADV_ENABLE, p_buf,
			HCI_CMD_LE_SET_ADV_ENABLE_PARAM_SIZE);
}

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

INT8 hci_ble_set_scan_params(UINT8 scan_type, UINT16 scan_int,
		UINT16 scan_win, UINT8 addr_type_own, UINT8 scan_filter_policy)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_SET_SCAN_PARAM_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_SCAN_PARAM);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_SCAN_PARAM_PARAM_SIZE);

	UINT8_TO_STREAM(p, scan_type);
	UINT16_TO_STREAM(p, scan_int);
	UINT16_TO_STREAM(p, scan_win);
	UINT8_TO_STREAM(p, addr_type_own);
	UINT8_TO_STREAM(p, scan_filter_policy);

	return hci_send_cmd(HCI_CMD_LE_SET_SCAN_PARAM, p_buf,
			HCI_CMD_LE_SET_SCAN_PARAM_PARAM_SIZE);
}

INT8 hci_ble_set_scan_enable(UINT8 scan_enable, UINT8 duplicate)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_SET_SCAN_ENABLE_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_SCAN_ENABLE);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_SCAN_ENABLE_PARAM_SIZE);

	UINT8_TO_STREAM(p, scan_enable);
	UINT8_TO_STREAM(p, duplicate);

	return hci_send_cmd(HCI_CMD_LE_SET_SCAN_ENABLE, p_buf,
			HCI_CMD_LE_SET_SCAN_ENABLE_PARAM_SIZE);
}

INT8 hci_ble_create_ll_conn(UINT16 scan_int, UINT16 scan_win,
		UINT8 init_filter_policy, UINT8 addr_type_peer, UINT8* bda_peer,
		UINT8 addr_type_own, UINT16 conn_int_min, UINT16 conn_int_max,
		UINT16 conn_latency, UINT16 conn_timeout, UINT16 min_ce_len,
		UINT16 max_ce_len)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_CREATE_CONN_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_CREATE_CONN);
	UINT8_TO_STREAM(p, HCI_CMD_LE_CREATE_CONN_PARAM_SIZE);

	UINT16_TO_STREAM(p, scan_int);
	UINT16_TO_STREAM(p, scan_win);
	UINT8_TO_STREAM(p, init_filter_policy);

	UINT8_TO_STREAM(p, addr_type_peer);
	memcpy(p, bda_peer, BD_ADDR_LEN);
	p += BD_ADDR_LEN;
	UINT8_TO_STREAM(p, addr_type_own);

	UINT16_TO_STREAM(p, conn_int_min);
	UINT16_TO_STREAM(p, conn_int_max);
	UINT16_TO_STREAM(p, conn_latency);
	UINT16_TO_STREAM(p, conn_timeout);

	UINT16_TO_STREAM(p, min_ce_len);
	UINT16_TO_STREAM(p, max_ce_len);

	return hci_send_cmd(HCI_CMD_LE_CREATE_CONN, p_buf,
			HCI_CMD_LE_CREATE_CONN_PARAM_SIZE);
}

INT8 hci_ble_cancel_create_ll_conn()
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_CREATE_CONN_CANCEL_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_CREATE_CONN_CANCEL);
	UINT8_TO_STREAM(p, HCI_CMD_LE_CREATE_CONN_CANCEL_PARAM_SIZE);

	return hci_send_cmd(HCI_CMD_LE_CREATE_CONN_CANCEL, p_buf,
			HCI_CMD_LE_CREATE_CONN_CANCEL_PARAM_SIZE);
}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

INT8 hci_disconnect(UINT16 handle, UINT8 reason)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_DISCONNECT_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_DISCONNECT);
	UINT8_TO_STREAM(p, HCI_CMD_DISCONNECT_PARAM_SIZE);
	UINT16_TO_STREAM(p, handle);
	UINT8_TO_STREAM(p, reason);

	return hci_send_cmd(HCI_CMD_DISCONNECT, p_buf,
			HCI_CMD_DISCONNECT_PARAM_SIZE);
}

#if (GAP_RANDOM_ADDDRESS_SUPPORT == TRUE)
INT8 hci_ble_set_random_addr(UINT8* random_bda)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_SET_RANDOM_ADDRESS_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
	if (p == NULL )
	return STATUS_ERR_INSUFFICIENT_RESOURCES;
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_RANDOM_ADDRESS);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_RANDOM_ADDRESS_PARAM_SIZE);

	REVERSE_ARRAY_TO_STREAM(p, random_bda, BD_ADDR_LEN);

	return hci_send_cmd(HCI_CMD_LE_SET_RANDOM_ADDRESS, p_buf,
			HCI_CMD_LE_SET_RANDOM_ADDRESS_PARAM_SIZE);
}
#endif

INT8 hci_ble_read_white_list_size(void)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_READ_WHITE_LIST_SIZE_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_READ_WHITE_LIST_SIZE);
	UINT8_TO_STREAM(p, HCI_CMD_LE_READ_WHITE_LIST_SIZE_PARAM_SIZE);

	return hci_send_cmd(HCI_CMD_LE_READ_WHITE_LIST_SIZE, p_buf,
			HCI_CMD_LE_READ_WHITE_LIST_SIZE_PARAM_SIZE);
}

INT8 hci_ble_clear_white_list(void)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_CLEAR_WHITE_LIST_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_CLEAR_WHITE_LIST);
	UINT8_TO_STREAM(p, HCI_CMD_LE_CLEAR_WHITE_LIST_PARAM_SIZE);

	return hci_send_cmd(HCI_CMD_LE_CLEAR_WHITE_LIST, p_buf,
			HCI_CMD_LE_CLEAR_WHITE_LIST_PARAM_SIZE);
}

INT8 hci_ble_add_to_white_list(UINT8 addr_type, UINT8* bda)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_ADD_DEV_TO_WHITE_LIST_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_ADD_DEV_TO_WHITE_LIST);
	UINT8_TO_STREAM(p, HCI_CMD_LE_ADD_DEV_TO_WHITE_LIST_PARAM_SIZE);

	UINT8_TO_STREAM(p, addr_type);
	memcpy(p, bda, BD_ADDR_LEN);

	return hci_send_cmd(HCI_CMD_LE_ADD_DEV_TO_WHITE_LIST, p_buf,
			HCI_CMD_LE_ADD_DEV_TO_WHITE_LIST_PARAM_SIZE);
}

INT8 hci_ble_remove_from_white_list(UINT8 addr_type, UINT8* bda)
{

	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_REMOVE_DEV_FRM_WHITE_LIST_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_REMOVE_DEV_FRM_WHITE_LIST);
	UINT8_TO_STREAM(p, HCI_CMD_LE_REMOVE_DEV_FRM_WHITE_LIST_PARAM_SIZE);

	UINT8_TO_STREAM(p, addr_type);
	memcpy(p, bda, BD_ADDR_LEN);

	return hci_send_cmd(HCI_CMD_LE_REMOVE_DEV_FRM_WHITE_LIST, p_buf,
			HCI_CMD_LE_REMOVE_DEV_FRM_WHITE_LIST_PARAM_SIZE);
}

INT8 hci_ble_upd_ll_conn_params(UINT16 handle, UINT16 conn_int_min,
		UINT16 conn_int_max, UINT16 conn_latency, UINT16 conn_timeout,
		UINT16 min_ce_len, UINT16 max_ce_len)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_CONN_UPDATE_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_CONN_UPDATE);
	UINT8_TO_STREAM(p, HCI_CMD_LE_CONN_UPDATE_PARAM_SIZE);

	UINT16_TO_STREAM(p, handle);

	UINT16_TO_STREAM(p, conn_int_min);
	UINT16_TO_STREAM(p, conn_int_max);
	UINT16_TO_STREAM(p, conn_latency);
	UINT16_TO_STREAM(p, conn_timeout);
	UINT16_TO_STREAM(p, min_ce_len);
	UINT16_TO_STREAM(p, max_ce_len);

	return hci_send_cmd(HCI_CMD_LE_CONN_UPDATE, p_buf,
			HCI_CMD_LE_CONN_UPDATE_PARAM_SIZE);
}

INT8 hci_ble_set_data_len(UINT16 handle, UINT16 tx_octets,
		UINT16 tx_time)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_SET_DATA_LEN_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_DATA_LEN);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_DATA_LEN_PARAM_SIZE);

	UINT16_TO_STREAM(p, handle);
	UINT16_TO_STREAM(p, tx_octets);
	UINT16_TO_STREAM(p, tx_time);

	return hci_send_cmd(HCI_CMD_LE_SET_DATA_LEN, p_buf,
			HCI_CMD_LE_SET_DATA_LEN_PARAM_SIZE);
}

INT8 hci_ble_write_sug_def_data_len(UINT16 tx_octets, UINT16 tx_time)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_WRITE_SUG_DEF_DATA_LEN_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_WRITE_SUG_DEF_DATA_LEN);
	UINT8_TO_STREAM(p, HCI_CMD_LE_WRITE_SUG_DEF_DATA_LEN_PARAM_SIZE);

	UINT16_TO_STREAM(p, tx_octets);
	UINT16_TO_STREAM(p, tx_time);

	return hci_send_cmd(HCI_CMD_LE_WRITE_SUG_DEF_DATA_LEN, p_buf,
			HCI_CMD_LE_WRITE_SUG_DEF_DATA_LEN_PARAM_SIZE);
}

INT8 hci_ble_read_max_data_len(void)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_READ_MAX_DATA_LEN_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_READ_MAX_DATA_LEN);
	UINT8_TO_STREAM(p, HCI_CMD_LE_READ_MAX_DATA_LEN_PARAM_SIZE);

	return hci_send_cmd(HCI_CMD_LE_READ_MAX_DATA_LEN, p_buf,
			HCI_CMD_LE_READ_MAX_DATA_LEN_PARAM_SIZE);
}

INT8 hci_ble_rem_conn_param_req_rep(UINT16 handle, UINT16 conn_int_min,
		UINT16 conn_int_max, UINT16 conn_latency, UINT16 conn_timeout,
		UINT16 min_ce_len, UINT16 max_ce_len)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_REM_CONN_PARAM_REQ_REPLY_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_REM_CONN_PARAM_REQ_REPLY);
	UINT8_TO_STREAM(p, HCI_CMD_LE_REM_CONN_PARAM_REQ_REPLY_PARAM_SIZE);

	UINT16_TO_STREAM(p, handle);

	UINT16_TO_STREAM(p, conn_int_min);
	UINT16_TO_STREAM(p, conn_int_max);
	UINT16_TO_STREAM(p, conn_latency);
	UINT16_TO_STREAM(p, conn_timeout);
	UINT16_TO_STREAM(p, min_ce_len);
	UINT16_TO_STREAM(p, max_ce_len);

	return hci_send_cmd(HCI_CMD_LE_REM_CONN_PARAM_REQ_REPLY, p_buf,
			HCI_CMD_LE_REM_CONN_PARAM_REQ_REPLY_PARAM_SIZE);
}

INT8 hci_ble_rem_conn_param_req_rej(UINT16 handle, UINT8 reason)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_REM_CONN_PARAM_REQ_REJCT_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_REM_CONN_PARAM_REQ_REJCT);
	UINT8_TO_STREAM(p, HCI_CMD_LE_REM_CONN_PARAM_REQ_REJCT_PARAM_SIZE);

	UINT16_TO_STREAM(p, handle);
	UINT8_TO_STREAM(p, reason);

	return hci_send_cmd(HCI_CMD_LE_REM_CONN_PARAM_REQ_REJCT, p_buf,
			HCI_CMD_LE_REM_CONN_PARAM_REQ_REJCT_PARAM_SIZE);
}

#if (SMP_FEATURE)

INT8 hci_ble_rand(void)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
				HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
				+ HCI_CMD_LE_RAND_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_RAND);
	UINT8_TO_STREAM(p, HCI_CMD_LE_RAND_PARAM_SIZE);

	return hci_send_cmd(HCI_CMD_LE_RAND, p_buf,
			HCI_CMD_LE_RAND_PARAM_SIZE);
}

#if (INTERNAL_AES == FALSE)
INT8 hci_ble_encrypt(UINT8* key,UINT8* plain_text)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
				HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
				+ HCI_CMD_LE_ENCRYPT_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_ENCRYPT);
	UINT8_TO_STREAM(p, HCI_CMD_LE_ENCRYPT_PARAM_SIZE);
	REVERSE_ARRAY_TO_STREAM(p, key, SMP_MAX_KEY_LEN);
	REVERSE_ARRAY_TO_STREAM(p, plain_text, SMP_MAX_KEY_LEN);

	return hci_send_cmd(HCI_CMD_LE_ENCRYPT, p_buf,
			HCI_CMD_LE_ENCRYPT_PARAM_SIZE);
}
#endif /*(INTERNAL_AES == FALSE)*/

INT8 hci_ble_ltk_req_reply(UINT16 conn_handle, UINT8* ltk)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
					HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_LONG_TERM_KEY_REQ_REPLY_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_LE_LONG_TERM_KEY_REQ_REPLY);
	UINT8_TO_STREAM(p, HCI_CMD_LE_LONG_TERM_KEY_REQ_REPLY_PARAM_SIZE);
	UINT16_TO_STREAM(p, conn_handle);
	REVERSE_ARRAY_TO_STREAM(p, ltk, SMP_MAX_KEY_LEN);

	return hci_send_cmd(HCI_CMD_LE_LONG_TERM_KEY_REQ_REPLY, p_buf,
			HCI_CMD_LE_LONG_TERM_KEY_REQ_REPLY_PARAM_SIZE);
}

INT8 hci_ble_ltk_neg_reply(UINT16 conn_handle)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
					HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
					+ HCI_CMD_LE_LONG_TERM_KEY_NEG_REPLY_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_LE_LONG_TERM_KEY_NEG_REPLY);
	UINT8_TO_STREAM(p, HCI_CMD_LE_LONG_TERM_KEY_NEG_REPLY_PARAM_SIZE);
	UINT16_TO_STREAM(p, conn_handle);

	return hci_send_cmd(HCI_CMD_LE_LONG_TERM_KEY_NEG_REPLY, p_buf,
			HCI_CMD_LE_LONG_TERM_KEY_NEG_REPLY_PARAM_SIZE);
}

INT8 hci_ble_start_encryption(UINT16 conn_handle,UINT8* random_num,UINT16 evid,UINT8* ltk)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
				HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
				+ HCI_CMD_LE_START_ENCRYPT_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_START_ENCRYPT);
	UINT8_TO_STREAM(p, HCI_CMD_LE_START_ENCRYPT_PARAM_SIZE);
	UINT16_TO_STREAM(p, conn_handle);
	REVERSE_ARRAY_TO_STREAM(p, random_num, 8);
	UINT16_TO_STREAM(p, evid);
	REVERSE_ARRAY_TO_STREAM(p, ltk, SMP_MAX_KEY_LEN);

	return hci_send_cmd(HCI_CMD_LE_START_ENCRYPT, p_buf,
			HCI_CMD_LE_START_ENCRYPT_PARAM_SIZE);
}

#endif /* SMP_FEATURE */

#if (CONTROLLER_PRIVACY)

INT8 hci_ble_set_privacy_mode(UINT8 addr_type, UINT8* bda, UINT8 privacy_mode)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_SET_PRIVACY_MODE_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_PRIVACY_MODE);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_PRIVACY_MODE_SIZE);

	UINT8_TO_STREAM(p, addr_type);
	memcpy(p, bda, BD_ADDR_LEN);

	p += BD_ADDR_LEN;

	*p = privacy_mode;

	return hci_send_cmd(HCI_CMD_LE_SET_PRIVACY_MODE, p_buf,
			HCI_CMD_LE_SET_PRIVACY_MODE_SIZE);
}

INT8 hci_ble_add_device_to_resolving_list(UINT8 addr_type, UINT8* bda, UINT8* peer_irk, UINT8* local_irk)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_ADD_DEV_TO_RESOLVING_LIST_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_ADD_DEV_TO_RESOLVING_LIST);
	UINT8_TO_STREAM(p, HCI_CMD_LE_ADD_DEV_TO_RESOLVING_LIST_PARAM_SIZE);

	UINT8_TO_STREAM(p, addr_type);
	memcpy(p, bda, BD_ADDR_LEN);
	p += BD_ADDR_LEN;
	REVERSE_ARRAY_TO_STREAM(p, peer_irk, SMP_MAX_KEY_LEN);
	REVERSE_ARRAY_TO_STREAM(p, local_irk, SMP_MAX_KEY_LEN);

	return hci_send_cmd(HCI_CMD_LE_ADD_DEV_TO_RESOLVING_LIST, p_buf,
			HCI_CMD_LE_ADD_DEV_TO_RESOLVING_LIST_PARAM_SIZE);
}

INT8 hci_ble_remove_device_from_resolving_list(UINT8 addr_type, UINT8* bda)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_REMOVE_DEV_FROM_RESOLVING_LIST_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_REMOVE_DEV_FROM_RESOLVING_LIST);
	UINT8_TO_STREAM(p, HCI_CMD_LE_REMOVE_DEV_FROM_RESOLVING_LIST_PARAM_SIZE);

	UINT8_TO_STREAM(p, addr_type);
	memcpy(p, bda, BD_ADDR_LEN);
	p += BD_ADDR_LEN;

	return hci_send_cmd(HCI_CMD_LE_REMOVE_DEV_FROM_RESOLVING_LIST, p_buf,
			HCI_CMD_LE_REMOVE_DEV_FROM_RESOLVING_LIST_PARAM_SIZE);
}

INT8 hci_ble_clear_resolving_list(void)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_CLEAR_RESOLVING_LIST_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_CLEAR_RESOLVING_LIST);
	UINT8_TO_STREAM(p, HCI_CMD_LE_CLEAR_RESOLVING_LIST_PARAM_SIZE);

	return hci_send_cmd(HCI_CMD_LE_CLEAR_RESOLVING_LIST, p_buf,
			HCI_CMD_LE_CLEAR_RESOLVING_LIST_PARAM_SIZE);
}

INT8 hci_ble_read_resolving_list_size(void)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_READ_RESOLVING_LIST_SIZE_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_READ_RESOLVING_LIST_SIZE);
	UINT8_TO_STREAM(p, HCI_CMD_LE_READ_RESOLVING_LIST_SIZE_PARAM_SIZE);

	return hci_send_cmd(HCI_CMD_LE_READ_RESOLVING_LIST_SIZE, p_buf,
			HCI_CMD_LE_READ_RESOLVING_LIST_SIZE_PARAM_SIZE);
}

INT8 hci_ble_read_peer_resolvable_addr(UINT8 addr_type, UINT8* bda)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_READ_PEER_RESOLVABLE_ADDR_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_READ_PEER_RESOLVABLE_ADDR);
	UINT8_TO_STREAM(p, HCI_CMD_LE_READ_PEER_RESOLVABLE_ADDR_PARAM_SIZE);

	UINT8_TO_STREAM(p, addr_type);
	memcpy(p, bda, BD_ADDR_LEN);
	p += BD_ADDR_LEN;

	return hci_send_cmd(HCI_CMD_LE_READ_PEER_RESOLVABLE_ADDR, p_buf,
			HCI_CMD_LE_READ_PEER_RESOLVABLE_ADDR_PARAM_SIZE);
}

INT8 hci_ble_read_local_resolvable_addr(UINT8 addr_type, UINT8* bda)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_READ_LOCAL_RESOLVABLE_ADDR_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_READ_LOCAL_RESOLVABLE_ADDR);
	UINT8_TO_STREAM(p, HCI_CMD_LE_READ_LOCAL_RESOLVABLE_ADDR_PARAM_SIZE);

	UINT8_TO_STREAM(p, addr_type);
	memcpy(p, bda, BD_ADDR_LEN);
	p += BD_ADDR_LEN;

	return hci_send_cmd(HCI_CMD_LE_READ_LOCAL_RESOLVABLE_ADDR, p_buf,
			HCI_CMD_LE_READ_LOCAL_RESOLVABLE_ADDR_PARAM_SIZE);
}

INT8 hci_ble_set_addr_resolution_enable(UINT8 enable)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_SET_ADDR_RESOLUTION_EN_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_ADDR_RESOLUTION_EN);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_ADDR_RESOLUTION_EN_PARAM_SIZE);

	UINT8_TO_STREAM(p, enable);

	return hci_send_cmd(HCI_CMD_LE_SET_ADDR_RESOLUTION_EN, p_buf,
			HCI_CMD_LE_SET_ADDR_RESOLUTION_EN_PARAM_SIZE);
}

INT8 hci_ble_set_rpa_tout(UINT16 rpa_tout)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
			HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
			+ HCI_CMD_LE_SET_RESOLVABLE_PRIVATE_ADDR_TOUT_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_SET_RESOLVABLE_PRIVATE_ADDR_TOUT);
	UINT8_TO_STREAM(p, HCI_CMD_LE_SET_RESOLVABLE_PRIVATE_ADDR_TOUT_PARAM_SIZE);

	UINT16_TO_STREAM(p, rpa_tout);

	return hci_send_cmd(HCI_CMD_LE_SET_RESOLVABLE_PRIVATE_ADDR_TOUT, p_buf,
			HCI_CMD_LE_SET_RESOLVABLE_PRIVATE_ADDR_TOUT_PARAM_SIZE);
}

#endif /* CONTROLLER_PRIVACY */

#if (CONTROLLER_ECDH)
INT8 hci_ble_read_local_p256_public_key()
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
				HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
				+ HCI_CMD_LE_READ_LOCAL_P256_PUBLIC_KEY_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_READ_LOCAL_P256_PUBLIC_KEY);
	UINT8_TO_STREAM(p, HCI_CMD_LE_READ_LOCAL_P256_PUBLIC_KEY_PARAM_SIZE);

	return hci_send_cmd(HCI_CMD_LE_READ_LOCAL_P256_PUBLIC_KEY, p_buf,
			HCI_CMD_LE_READ_LOCAL_P256_PUBLIC_KEY_PARAM_SIZE);
}

INT8 hci_ble_generate_dhkey(UINT8 *pub_key_x,UINT8 *pub_key_y, UINT8 len)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(
				HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE
				+ HCI_CMD_LE_GENERATE_DHKEY_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_LE_GENERATE_DHKEY);
	UINT8_TO_STREAM(p, HCI_CMD_LE_GENERATE_DHKEY_PARAM_SIZE);
	REVERSE_ARRAY_TO_STREAM(p, pub_key_x, len);
	REVERSE_ARRAY_TO_STREAM(p, pub_key_y, len);

	return hci_send_cmd(HCI_CMD_LE_GENERATE_DHKEY, p_buf,
			HCI_CMD_LE_GENERATE_DHKEY_PARAM_SIZE);
}
#endif /* CONTROLLER_ECDH */

INT8 hci_ble_set_bdaddr(UINT8 *bda)
{
	UINT8 *p_buf = (UINT8*) alloc_queue_element(HCI_CMD_PREAMBLE_SIZE + UART_HDR_SIZE + HCI_CMD_VS_WRITE_BDADDR_PARAM_SIZE, HCI_ALLOC);
	UINT8 *p = p_buf;
	UINT8 cmd[] = { 0x08, 0x22, 0x01 };
#if (PARANOID_STACK == TRUE)
	if (!p)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	JUMP_UART_HEADER(p);

	UINT16_TO_STREAM(p, HCI_CMD_VS_WRITE_BDADDR);
	UINT8_TO_STREAM(p, HCI_CMD_VS_WRITE_BDADDR_PARAM_SIZE);

	ARRAY_TO_STREAM(p, cmd, sizeof(cmd));
	memcpy(p, bda, BD_ADDR_LEN);
	p += BD_ADDR_LEN;

	return hci_send_cmd(HCI_CMD_VS_WRITE_BDADDR, p_buf, HCI_CMD_VS_WRITE_BDADDR_PARAM_SIZE);
}

#if ((TARGET_THREADX == TRUE) || (TARGET_THREADX_RW == TRUE))
/**
 * @brief This function is called when embedded stack init is completed.
 *
 * @func hci_stack_init_completed
 *
 * Parameter buffer will be:
 * ----------
 * | status |
 * ----------
 *   1B
 */
INT8 hci_stack_init_completed(UINT8 status)
{

#if (A4WP_APP == TRUE)
	return 0;
#else
#if ((TARGET_THREADX == TRUE) || (TARGET_THREADX_TEST == TRUE))

	UINT8 *buffer = (UINT8*) alloc_queue_element(PROFILE_EVENT_STACK_INIT_COMPLETED_PARAM_LEN + UART_HDR_SIZE + HCI_CMD_PREAMBLE_SIZE, HCI_ALLOC);
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	UINT8 *p = buffer;
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, PROFILE_OPERATION_ASYNC_EVENT);
	UINT8_TO_STREAM(p, PROFILE_EVENT_STACK_INIT_COMPLETED_PARAM_LEN);
	UINT8_TO_STREAM(p, PROFILE_EVENT_STACK_INIT_COMPLETED);
	UINT8_TO_STREAM(p, status);
	return hci_send_cmd(PROFILE_OPERATION_ASYNC_EVENT, buffer,
			PROFILE_EVENT_STACK_INIT_COMPLETED_PARAM_LEN);

#elif (TARGET_THREADX_RW == TRUE)


	logd("");

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
	tl_write(p_buf, 7);
#endif
#endif /* A4WP_APP == TRUE */
	return STATUS_SUCCESS;
}
#else
INT8 hci_stack_init_completed(UINT8 status)
{
	return STATUS_ERR_OPERATION_NOT_SUPPORTED;
}
#endif

#if (TARGET_THREADX == TRUE)
INT8 hci_manuf_mode(UINT8 status)
{
	UINT8 *buffer = (UINT8*) alloc_queue_element(HCI_CMD_VS_MANUF_MODE_PARAM_LEN + UART_HDR_SIZE + HCI_CMD_PREAMBLE_SIZE, HCI_ALLOC);
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	UINT8 *p = buffer;
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_VS_MANUF_MODE);
	UINT8_TO_STREAM(p, HCI_CMD_VS_MANUF_MODE_PARAM_LEN);
	UINT8_TO_STREAM(p, status); /* status: 1 to enable manuf on. status 0 to disable.*/
	UINT8_TO_STREAM(p, 0);
	return hci_send_cmd(HCI_CMD_VS_MANUF_MODE, buffer, HCI_CMD_VS_MANUF_MODE_PARAM_LEN);
}

INT8 hci_write_bd_data()
{
	UINT8 *buffer = (UINT8*) alloc_queue_element(HCI_CMD_VS_WRITE_BD_DATA_PARAM_LEN+ UART_HDR_SIZE + HCI_CMD_PREAMBLE_SIZE, HCI_ALLOC);
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#endif
	UINT8 *p = buffer;
	//UINT8 cmd_buffer[] = {0x11,0x22,0x33,0x44,0x55,0x66,0x00,0x00,0x00,0xF0,0x49,0x02,0xFF,0xFE,0x0F,0xF8,0x5B,0x1E,0x7B,0x87,0x01,0x00,0xFA,0x1A,0x20,0x0A,0x08,0x08,0x08,0x05,0x07,0x07,0x07,0x0A,0x08,0x08,0x04,0x06,0x0A,0xA4,0x09,0xB8,0xCC,0x0A,0x04,0x00,0x01,0xC0,0x0B,0x14,0x08,0x00,0x40,0x00,0x1E,0x00,0xB8,0x0B,0x64,0x19,0xC8,0xAF,0xA8,0x61,0xD0,0x07,0x04,0x00,0x0B,0x5A,0x86,0x86,0x04,0x43,0xB3,0x7C,0x02,0x00,0x00,0x00};

/*	UINT8 cmd_buffer[] = {0x66,0x55,0x44,0x33,0x22,0x11,0x00,0x00,0x00,0xF0,0x49 \
							,0x02,0xFF,0xFE,0x0F,0xFE,0xDB,0xFF,0x7B,0x87,0x01 \
							,0x00,0xFA,0x1A,0x20,0x08,0x02,0xFF,0x08,0x05,0x07 \
							,0x07,0x07,0x08,0x02,0xFF,0x04,0x06,0x08,0xA4,0x08 \
							,0xB8,0xCC,0x0A,0x04,0x00,0x01,0xC0,0x0B,0x14,0x0C \
							,0x00,0x00,0x00,0x1E,0x00,0xB8,0x0B,0x64,0x19,0xC8 \
							,0xAF,0xA8,0x61,0xD0,0x07,0x04,0x00,0x0B,0x5A,0x86 \
							,0x86,0x04,0x43,0xB3,0x7C,0x02,0x00,0x00,0x00};
							*/
	UINT8 cmd_buffer[] = {0x66,0x55,0x44,0x33,0x22,0x11,0x00,0x00,0x00,0xF0,\
						  0x49,0x02,0xFF,0xFE,0x0F,0xF8,0x5B,0x1E,0x7B,0x87,\
						  0x01,0x00,0xFA,0x1A,0x20,0x0A,0x08,0x08,0x08,0x05,\
						  0x07,0x07,0x07,0x0A,0x08,0x08,0x04,0x06,0x0A,0xA4,\
						  0x09,0xB8,0xCC,0x0A,0x04,0x00,0x01,0xC0,0x0B,0x14,\
						  0x08,0x00,0x40,0x00,0x1E,0x00,0xB8,0x0B,0x64,0x19,\
						  0xC8,0xAF,0xA8,0x61,0xD0,0x07,0x04,0x00,0x0B,0x5A,\
						  0x86,0x86,0x04,0x43,0xB3,0x7C,0x02,0x00,0x00,0x00};
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, HCI_CMD_VS_WRITE_BD_DATA);
	UINT8_TO_STREAM(p, HCI_CMD_VS_WRITE_BD_DATA_PARAM_LEN);
	memcpy (p, cmd_buffer, HCI_CMD_VS_WRITE_BD_DATA_PARAM_LEN);

	return hci_send_cmd(HCI_CMD_VS_WRITE_BD_DATA, buffer,
			HCI_CMD_VS_WRITE_BD_DATA_PARAM_LEN);
}
#endif
