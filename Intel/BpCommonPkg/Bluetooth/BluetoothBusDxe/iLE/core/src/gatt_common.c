/** @file
  GATT server and client common functionality implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "att.h"
#include "profile_mgr.h"
#include "service_mgr.h"
#include "smp_mgr.h"
#include "config_host.h"
#include "utils.h"
#include "gatt.h"
#include "interface.h"

#define MODULE_DBG_LVL GATT_DBG_LVL
#include "log.h"

/****************************************************************
 *		GATT static utility functions
 ***************************************************************/

/****************************************************************
 * 	GATT Static functions
 ***************************************************************/

#if ((GATT_CLIENT_SUPPORTED == TRUE) || (GATT_SERVER_SUPPORTED == TRUE))

INT8 gatt_init()
{
	return STATUS_SUCCESS;
}

void gatt_cleanup()
{
	iLE_stack_cleanup();
}

#if (GATT_SERVER_SUPPORTED == TRUE)

void gatt_mtu_exchange_req_cb(UINT8 conn_id, buffer_t* in_buffer)
{
#if (PARANOID_STACK == TRUE)
	if(!in_buffer || (in_buffer && in_buffer->length < 2))
		return;
#endif
	UINT16 remote_mtu;
	UINT8* p_input = in_buffer->data + in_buffer->offset;
	STREAM_TO_UINT16(remote_mtu, p_input);

	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return;

	/* TODO: if MTU exchange is already done, send error response */

	/*
	 * MTU negotiation strategy: Even if a remote device asks for a MTU < MIN_MTU
	 * then don't change the MTU. Make the MTU value which is minimum between
	 * local MTU and remote MTU. Remote device will do the same calculation and
	 * we both will arrive at the same value.
	 */
	remote_mtu = (remote_mtu < ATT_MIN_MTU_LEN) ? ATT_MIN_MTU_LEN : remote_mtu;
	device->att_device.att_mtu_size = (ATT_MAX_MTU_LEN < remote_mtu) ? ATT_MAX_MTU_LEN : remote_mtu;

	/* FIXME: if we cannot send the reply then MTU shouldn't be changed. Check it.*/
	device->att_device.mtu_exchange_done = TRUE;
	att_send_mtu_xchange_rsp(device->idx, device->att_device.att_mtu_size);

	pm_att_mtu_changed_cb(conn_id, device->att_device.att_mtu_size);
}

#endif /* GATT_SERVER_SUPPORTED == TRUE */

UINT16 get_device_mtu(UINT8 conn_id)
{
	connected_device_t *device = get_connected_device_by_conn_id(conn_id);

	if (!device)
		return 0;

	/* FIXME: Potential memory bloat??? Always allocate mtu? */
	return device->att_device.att_mtu_size;
}

void gatt_connect_cb(connected_device_t* device)
{
#if (GATT_CLIENT_SUPPORTED == TRUE)
	gatt_client_connect_cb(device);
#endif
#if (GATT_SERVER_SUPPORTED == TRUE)
	gatt_server_connect_cb(device->idx);
#endif
	//gatt_request_mtu(device);
}

void gatt_disconnect_cb(connected_device_t* device)
{
#if (GATT_CLIENT_SUPPORTED == TRUE)
	gatt_client_disconnect_cb(device);
#endif
#if (GATT_SERVER_SUPPORTED == TRUE)
	gatt_server_disconnect_cb(device->idx);
#endif
}

#endif /* (GATT_CLIENT_SUPPORTED == TRUE) || (GATT_SERVER_SUPPORTED == TRUE) */
