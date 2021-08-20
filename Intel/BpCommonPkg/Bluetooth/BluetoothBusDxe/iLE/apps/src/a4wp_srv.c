/** @file
  A4WP server implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "app_interface.h"
#include "a4wp_srv.h"
#if (A4WP_APP == TRUE)

#define MODULE_DBG_LVL A4WP_DBG_LVL
#include "log.h"


/* A4WP Global variables */
static a4wp_srv_t a4wp_server;

static device_control_callbacks_t dev_ctl_cb;
static gatt_callbacks_t gatt_cb;
static void signal_req(void);

static void test_a4wp_sm_init(UINT8* arg);
static void test_a4wp_start_adv(UINT8* arg);

/**********************************************************/

/** @brief Trigger the A4WP profile thread
 * Function: signal_req
 * 			release the Interface thread queue
 * 			and process the messages in Application thread
 * 			context
 * @return None
 */
static inline void signal_req()
{
	osa_semaphore_put(&a4wp_server.msg_sem);
}

static void copy_buffer(buffer_t *dest, buffer_t* src)
{
	if (!dest || !src)
		return;
	dest->length = src->length;
	dest->offset = 0;
	memcpy(&dest->data, src->data + src->offset, src->length);
}

static void a4wp_srv_timer_expire_cb(osa_timer_arg_t arg)
{
	logd("");
}

/** @brief A4WP Application registered call back
 * Function: a4wp_register_app_cb
 * 			The A4WP profile is registered with
 * 			GATT layer
 * @param app_handle - GATT assigned application handle
 * @param result - TRUE if registration is success.
 * 					else FALSE;
 * @return None
 */
static void a4wp_register_app_cb(UINT8 app_handle, BOOLEAN result)
{
	logd("app_handle:%d", app_handle);
	if (result)
	{
		a4wp_server.app_handle = app_handle;
		a4wp_server.state = TRUE;
		a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
		if(!msg)
			return;
#endif
		msg->opcode = A4WP_APP_REGISTERED;
		msg->param = NULL;
		enqueue(&a4wp_server.req_queue,msg);
		signal_req();
	}
	else
	{	loge("A4WP App could not be registered");
		a4wp_server.state = FALSE;
		signal_req();
		cleanup_q(&a4wp_server.req_queue);
		osa_semaphore_get(&a4wp_server.thread_sem);
		osa_semaphore_delete(&a4wp_server.thread_sem);
	}

}

/** @brief Bluetooth LE stack initialized callback
 * Function: a4wp_bt_stack_initialized_cb
 * 			BT stack initialization is complete
 * 			Now A4WP service can initiate its procedures.
 * @return None
 */

static void a4wp_bt_stack_initialized_cb(BOOLEAN initialized)
{
	logd("");
	if (initialized)
	{
		a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
		if (!msg)
			return;
#endif
		msg->opcode = A4WP_BT_CORE_STACK_INIT;
		msg->param = NULL;
		enqueue(&a4wp_server.req_queue,msg);
		signal_req();
	}
}

static void a4wp_add_service()
{
	logd("");

	/* Add WPT (A4WP) Service */
	uuid_t temp_uuid;
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_STACK_SRV_PARAM_INIT_START);
#endif

	UINT8 wpt_uuid_base[] = {0x64, 0x55, 0x00, 0x00, 0xa1, 0x46, 0x11, 0xe2, 0x9e, 0x96, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x67};

	UINT16_TO_UUID(WPT_SERVICE_UUID, temp_uuid);
	iLE_add_service(a4wp_server.app_handle, &temp_uuid, ATTR_TYPE_PRIMARY_SERVICE, 0, 5, 1);

	wpt_uuid_base[3] = (UINT8)PRU_CTRL_CHARACTERISTIC_UUID;
	wpt_uuid_base[2] = (UINT8)(PRU_CTRL_CHARACTERISTIC_UUID >> 8);
	UINT128_TO_UUID(wpt_uuid_base, temp_uuid);
	iLE_add_characteristic(a4wp_server.app_handle, &temp_uuid, ATTRIBUTE_PROPERTY_WRITE_NO_RESPONSE, ATTRIBUTE_PERMISSION_WRITE);

	wpt_uuid_base[3] = (UINT8)PTU_STATIC_PARAM_CHARACTERISTIC_UUID;
	wpt_uuid_base[2] = (UINT8)(PTU_STATIC_PARAM_CHARACTERISTIC_UUID >> 8);
	UINT128_TO_UUID(wpt_uuid_base, temp_uuid);
	iLE_add_characteristic(a4wp_server.app_handle, &temp_uuid, ATTRIBUTE_PROPERTY_READ, ATTRIBUTE_PERMISSION_READ);

	wpt_uuid_base[3] = (UINT8)PRU_ALERT_PARAM_CHARACTERISTIC_UUID;
	wpt_uuid_base[2] = (UINT8)(PRU_ALERT_PARAM_CHARACTERISTIC_UUID >> 8);
	UINT128_TO_UUID(wpt_uuid_base, temp_uuid);
	iLE_add_characteristic(a4wp_server.app_handle, &temp_uuid, ATTRIBUTE_PROPERTY_READ | ATTRIBUTE_PROPERTY_NOTIFY | ATTRIBUTE_PROPERTY_INDICATE, ATTRIBUTE_PERMISSION_READ);
	UINT16_TO_UUID(CLIENT_CHAR_CONFIG_UUID, temp_uuid);
	iLE_add_descriptor(a4wp_server.app_handle, &temp_uuid, 0, ATTRIBUTE_PERMISSION_READ|ATTRIBUTE_PERMISSION_WRITE);

	wpt_uuid_base[3] = (UINT8)PRU_STATIC_PARAM_CHARACTERISTIC_UUID;
	wpt_uuid_base[2] = (UINT8)(PRU_STATIC_PARAM_CHARACTERISTIC_UUID >> 8);
	UINT128_TO_UUID(wpt_uuid_base, temp_uuid);
	iLE_add_characteristic(a4wp_server.app_handle, &temp_uuid, ATTRIBUTE_PROPERTY_READ, ATTRIBUTE_PERMISSION_READ);

	wpt_uuid_base[3] = (UINT8)PRU_DYNAMIC_PARAM_CHARACTERISTIC_UUID;
	wpt_uuid_base[2] = (UINT8)(PRU_DYNAMIC_PARAM_CHARACTERISTIC_UUID >> 8);
	UINT128_TO_UUID(wpt_uuid_base, temp_uuid);
	iLE_add_characteristic(a4wp_server.app_handle, &temp_uuid, ATTRIBUTE_PROPERTY_READ, ATTRIBUTE_PERMISSION_READ);
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_STACK_SRV_PARAM_INIT_DONE);
#endif

#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
		log_time_stamp(TIME_STACK_SRV_START_START);
#endif
	iLE_start_service(a4wp_server.app_handle);

#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_STACK_SRV_START_DONE);
#endif

}

/** @brief A4WP Service is registered and started
 * Function: a4wp_on_service_started_cb
 * 			A4WP server (WPT PRU) service is started.
 * 	@param uuid - 16 bit UUID of A4WP service.
 * 	@param result - TRUE if service started successfully
 * 	@param start_handle - Service start handle.
 * @return None
 */

static void a4wp_on_service_started_cb(uuid_t *uuid, UINT8 status, UINT16 service_handle)
{
	logd("service_handle:%d", service_handle);
	uuid_t temp_uuid;
	UINT16_TO_UUID(WPT_SERVICE_UUID, temp_uuid);
	if(uuidcmp(uuid, &temp_uuid) == TRUE)
	{
		a4wp_server.a4wp_srv_handle = service_handle;
		a4wp_server.advt_data.gatt_prm_srv_hdl = a4wp_server.a4wp_srv_handle;
		a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
		if (!msg)
			return;
#endif
		msg->opcode = A4WP_SERVICE_STARTED;
		msg->param = NULL;
		enqueue(&a4wp_server.req_queue,msg);
		signal_req();
	}
	else
	{
		loge("invalid uuid for WPT service");
	}
}

static void a4wp_on_connected_cb(UINT8* remote_bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 result, BOOLEAN from_remote, UINT8 *id_bdaddr, UINT8 id_bdaddr_type)
{
	logd("");
	if (!from_remote)
		return;
#if (PARANOID_STACK == TRUE)
	if (result == STATUS_SUCCESS)
#endif
	{
		a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
		if (!msg)
			return;
#endif
		msg->opcode = A4WP_CONNECTED;
		a4wp_server.conn_id = conn_id;
		memcpy(&a4wp_server.remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
		enqueue(&a4wp_server.req_queue,msg);
		signal_req();
	}
}
/** @brief Bluetooth device is disconnected from A4WP
 * Function: a4wp_on_disconnected_cb
 * 			BT device is disconnected
 * @param conn_id - disconnected device connection id
 * @param result	- 0x00 if device is disconnected.
 * @return None
 */
static void a4wp_on_disconnected_cb(UINT8 conn_id, UINT8 result)
{
	logd("");
#if (PARANOID_STACK == TRUE)
	if (result == 0x00)
#endif
	{
		a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
		if (!msg)
			return;
#endif
		msg->opcode = A4WP_DISCONNECTED;
		msg->param = &conn_id;
		enqueue(&a4wp_server.req_queue,msg);
		signal_req();
	}
}
/** @brief Write Characteristic value request callback
 * Function: a4wp_on_characteristic_write_req_cb
 * 			write the static/dynamic PRU characteristic
 * 			values.
 * @param device - connected device data structure
 * @param characteristic - characteristic to be read
 * @param value - data buffer
 * @param len - data buffer length
 * @param offset	- offset of read location in value buffer.
 * @param need_resp - TRUE if the application need to send response.
 * @return  TRUE if data is valid.
 */
static void a4wp_on_attribute_write_req_cb(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, buffer_t* buffer)
{
	logd("");
	if (!buffer)
		return;
	buffer->length = TRUNCATE_TO_16BIT_LENGTH(buffer->length, sizeof(a4wp_attr_write_req_t));
	a4wp_attr_write_req_t *req = (a4wp_attr_write_req_t *)app_alloc(sizeof(a4wp_attr_write_req_t) + (buffer->length));
#if (PARANOID_STACK == TRUE)
	if (!req)
		return;
#endif
	a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
	if(!msg)
	{
		app_dealloc(req);
		return;
	}
#endif

	req->conn_id = conn_id;
	req->att_opcode = att_opcode;
	req->att_id = att_id;
	req->offset = offset;
	copy_buffer(&req->buffer, buffer);
	msg->opcode = A4WP_ATTR_WRITE_REQ;
	msg->param = (UINT8 *)req;
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_A4WP_ATTR_WRITE_REQ);
#endif
	enqueue(&a4wp_server.req_queue,msg);
	osa_start_timer(&(a4wp_server.timer_id),A4WP_SRV_TIMER,A4WP_SRV_MAX_RESP_TIME,a4wp_srv_timer_expire_cb,0);
	signal_req();
}

/** @brief Read request callback
 * Function: a4wp_on_attribute_read_req_cb
 * 			Read GATT characteristic descriptor.
 * @param device - connected device data structure
 * @param descriptor - GATT characteristic descriptor to be read
 * @param offset	- offset of read location in value buffer.
 * @return  None.
 */
static void a4wp_on_attribute_read_req_cb(UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset)
{
	logd("");
	a4wp_attr_read_req_t *req = (a4wp_attr_read_req_t *)app_alloc(sizeof(a4wp_attr_read_req_t));
#if (PARANOID_STACK == TRUE)
	if (!req)
		return;
#endif
	a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
	if (!msg)
	{
		app_dealloc(req);
		return;
	}
#endif
	req->conn_id = conn_id;
	req->att_opcode = att_opcode;
	req->att_id = att_id;
	req->offset = offset;

	msg->opcode = A4WP_ATTR_READ_REQ;
	msg->param = (UINT8 *)req;
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_A4WP_ATTR_READ_REQ);
#endif
	enqueue(&a4wp_server.req_queue,msg);
	osa_start_timer(&(a4wp_server.timer_id),A4WP_SRV_TIMER,A4WP_SRV_MAX_RESP_TIME,0);
	signal_req();
}

void a4wp_on_indication_confirmation_cb(UINT8 conn_id, UINT16 att_id)
{
	logd("");
	a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
	if (!msg)
		return;
#endif
	msg->opcode = A4WP_IND_CFM_RECVD;
	msg->param = NULL;
	enqueue(&a4wp_server.req_queue,msg);
	signal_req();
}


static UINT8 get_att_val_elem(UINT16 att_id)
{
	UINT8 idx;
	for (idx = 0; idx < A4WP_SRV_ATT_MAX_ID; idx++)
	{
		if (a4wp_server.att_val_map[idx].att_id == att_id)
			return idx;
	}
	return A4WP_SRV_ATT_MAX_ID;
}

static buffer_t* get_buffer_from_value(UINT8 att_map_idx)
{
	if (!a4wp_server.att_val_map[att_map_idx].length)
		return NULL;
	buffer_t *buffer = (buffer_t*) app_alloc (sizeof (buffer_t) + a4wp_server.att_val_map[att_map_idx].length);
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return NULL;
#endif
	buffer->offset = 0;
	buffer->length = a4wp_server.att_val_map[att_map_idx].length;
	switch (att_map_idx)
	{
	case PRU_CTRL_CHARACTERISTIC_ID:
		memcpy(buffer->data, &a4wp_server.att_val_map[att_map_idx].value.pru_control_char_val, sizeof (pru_ctrl_char_t));
		break;
	case PTU_STATIC_PARAM_CHARACTERISTIC_ID:
		memcpy(buffer->data, &a4wp_server.att_val_map[att_map_idx].value.ptu_static_param_char_val, sizeof (ptu_static_param_char_t));
		break;
	case PRU_ALERT_PARAM_CHARACTERISTIC_ID:
		memcpy(buffer->data, &a4wp_server.att_val_map[att_map_idx].value.pru_alert_param_char_val, sizeof (pru_alert_param_char_t));
		break;
	case PRU_STATIC_PARAM_CHARACTERISTIC_ID:
		memcpy(buffer->data, &a4wp_server.att_val_map[att_map_idx].value.pru_static_param_char_val, sizeof (pru_static_param_char_t));
		break;
	case PRU_DYNAMIC_PARAM_CHARACTERISTIC_ID:
		memcpy(buffer->data, &a4wp_server.att_val_map[att_map_idx].value.pru_dynamic_param_char_val, sizeof (pru_dynamic_param_char_t));
		break;
	case CLIENT_CHAR_CONFIG_ID:
		memcpy(buffer->data, &a4wp_server.att_val_map[att_map_idx].value.pru_client_conf_desc_val, sizeof (UINT32));
		break;
	}
	return buffer;
}

static void set_value_from_buffer(UINT8 att_map_idx, buffer_t *buffer)
{
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return;
#endif
	switch (att_map_idx)
	{
	case PRU_CTRL_CHARACTERISTIC_ID:
		memcpy(&a4wp_server.att_val_map[att_map_idx].value.pru_control_char_val, buffer->data + buffer->offset, sizeof (pru_ctrl_char_t));
		break;
	case PTU_STATIC_PARAM_CHARACTERISTIC_ID:
		memcpy(&a4wp_server.att_val_map[att_map_idx].value.ptu_static_param_char_val, buffer->data + buffer->offset, sizeof (ptu_static_param_char_t));
		break;
	case PRU_ALERT_PARAM_CHARACTERISTIC_ID:
		memcpy(&a4wp_server.att_val_map[att_map_idx].value.pru_alert_param_char_val, buffer->data + buffer->offset, sizeof (pru_alert_param_char_t));
		break;
	case PRU_STATIC_PARAM_CHARACTERISTIC_ID:
		memcpy(&a4wp_server.att_val_map[att_map_idx].value.pru_static_param_char_val, buffer->data + buffer->offset, sizeof (pru_static_param_char_t));
		break;
	case PRU_DYNAMIC_PARAM_CHARACTERISTIC_ID:
		memcpy(&a4wp_server.att_val_map[att_map_idx].value.pru_dynamic_param_char_val, buffer->data + buffer->offset, sizeof (pru_dynamic_param_char_t));
		break;
	case CLIENT_CHAR_CONFIG_ID:
	{
		UINT8 *p = buffer->data + buffer->offset;
		STREAM_TO_UINT16(a4wp_server.att_val_map[att_map_idx].value.pru_client_conf_desc_val, p);
	}
		break;
	}
}
/** @brief A4WP Profile Thread handler
 * Function: a4wp_main_thread_handler
 * 			Process the GATT Requests and
 * 			send responses.
 * @return  Always NULL.
 */

static osa_thread_ret_t a4wp_main_thread_handler(osa_thread_arg_t arg)
{
	logd("");
	osa_semaphore_create(&a4wp_server.msg_sem, 0);
	osa_semaphore_put(&a4wp_server.thread_sem);
	while (a4wp_server.state)
	{
		a4wp_msg_t *msg = (a4wp_msg_t *)dequeue(&a4wp_server.req_queue);
		if (msg == NULL)
		{
			osa_semaphore_get(&a4wp_server.msg_sem);
		}
		else
		{
			/* check for the Message and process */
			switch (msg->opcode)
			{
				case A4WP_APP_REGISTERED:
				{
					logd("A4WP_APP_REGISTERED");
					osa_create_timer(&(a4wp_server.timer_id), A4WP_SRV_TIMER, A4WP_SRV_TIMER_ISR, sizeof(A4WP_SRV_TIMER)/sizeof(osa_timer_static_t), a4wp_srv_timer_expire_cb, 0);
				}
				break;
				case A4WP_BT_CORE_STACK_INIT:
				{
					logd("A4WP_CORE_BT_STACK_INIT");
					/* device name set to "WPT PRU" */
					UINT8 wpt_dev_name[] = { 0x57, 0x50, 0x54, 0x20, 0x50, 0x52, 0x55 };
					iLE_set_local_device_name(a4wp_server.app_handle,sizeof(wpt_dev_name), wpt_dev_name);
#if (TARGET_THREADX == TRUE)

#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
					log_time_stamp(TIME_STACK_INIT_CB_START);
#endif

					A4wp_le_stack_init_CallbackHandler(TRUE);
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
					log_time_stamp(TIME_STACK_INIT_CB_DONE);
#endif

#endif

#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
										  log_time_stamp(TIME_STACK_APP_REG_CB_START);
#endif
					if(a4wp_server.a4wp_sm_handler)
						a4wp_server.a4wp_sm_handler(A4WP_APP_REGISTERED_CB,NULL);
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
					log_time_stamp(TIME_STACK_APP_REG_CB_DONE);
#endif

				}
				break;
				case A4WP_SERVICE_STARTED:
				{
					logd("A4WP_SERVICE_STARTED");
					a4wp_server.att_val_map[PRU_CTRL_CHARACTERISTIC_ID].att_id = a4wp_server.a4wp_srv_handle + 2;
					a4wp_server.att_val_map[PTU_STATIC_PARAM_CHARACTERISTIC_ID].att_id = a4wp_server.a4wp_srv_handle + 4;
					a4wp_server.att_val_map[PRU_ALERT_PARAM_CHARACTERISTIC_ID].att_id = a4wp_server.a4wp_srv_handle + 6;
					a4wp_server.att_val_map[CLIENT_CHAR_CONFIG_ID].att_id = a4wp_server.a4wp_srv_handle + 7;
					a4wp_server.att_val_map[PRU_STATIC_PARAM_CHARACTERISTIC_ID].att_id = a4wp_server.a4wp_srv_handle + 9;
					a4wp_server.att_val_map[PRU_DYNAMIC_PARAM_CHARACTERISTIC_ID].att_id = a4wp_server.a4wp_srv_handle + 11;

					if (iLE_set_advertisement_data(a4wp_server.app_handle, sizeof(pru_adv_data_t),
							GAP_ADV_DATA_SERVICE_DATA_16BIT_UUID, (UINT8 *)&a4wp_server.advt_data) != STATUS_SUCCESS)
					{
					    loge("A4WP_SERVICE Advertisement data set fail");
					}
				}
				break;
				case A4WP_CONNECTED:
				{
					logd("A4WP_CONNECTED");
					a4wp_server.isconnected = TRUE;
					a4wp_server.configure_for_notify = FALSE;
					a4wp_server.configure_for_indication = FALSE;
					if(a4wp_server.a4wp_sm_handler)
						a4wp_server.a4wp_sm_handler(A4WP_CONNECTION_COMPLETE_CB, &a4wp_server.remote_bd_addr);
				}
				break;
				case A4WP_DISCONNECTED:
				{
					logd("A4WP_DISCONNECTED");
					a4wp_server.isconnected = FALSE;
					if(a4wp_server.a4wp_sm_handler)
						a4wp_server.a4wp_sm_handler(A4WP_DISCONNECTION_COMPLETE_CB, &a4wp_server.remote_bd_addr);
					memset(&a4wp_server.remote_bd_addr,0x00,BD_ADDR_LEN);
				}
				break;
				case A4WP_ATTR_READ_REQ:
				{
					logd("A4WP_ATTR_READ_REQ");
					a4wp_attr_read_req_t *req = (a4wp_attr_read_req_t *)(void *)msg->param;
					if(a4wp_server.isconnected != TRUE)
					{
						loge("This is not the intended device.");
						break;
					}
					UINT8 map_id = get_att_val_elem(req->att_id);
#if (PARANOID_STACK == TRUE)
					if (map_id == A4WP_SRV_ATT_MAX_ID)
					{
						iLE_send_attribute_read_rsp(a4wp_server.app_handle, req->conn_id, req->att_opcode, req->att_id,  ATT_ERR_ATTRIB_NOT_FOUND, NULL);
					}
					else
#endif
					{
						logd("map_id:%d", map_id);
						buffer_t *buffer = get_buffer_from_value(map_id);
						if (!buffer)
						{
							iLE_send_attribute_read_rsp(a4wp_server.app_handle, req->conn_id, req->att_opcode, req->att_id, ATT_ERR_UNLIKELY, NULL);
						}
						else
						{
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
							log_time_stamp(TIME_A4WP_ATTR_READ_RESP);
#endif
							iLE_send_attribute_read_rsp(a4wp_server.app_handle, req->conn_id, req->att_opcode, req->att_id,  ATT_SUCCESS, buffer);
							app_dealloc (buffer);
						}
					}
					app_dealloc(req);
					osa_stop_timer(&(a4wp_server.timer_id),A4WP_SRV_TIMER,0);
				}
				break;
				case A4WP_ATTR_WRITE_REQ:
				{
					logd("A4WP_CHAR_WRITE_REQ");
					a4wp_attr_write_req_t *req = (a4wp_attr_write_req_t *)(void *)msg->param;
					UINT8 map_id = get_att_val_elem(req->att_id);
#if (PARANOID_STACK == TRUE)
					if (map_id == A4WP_SRV_ATT_MAX_ID || !req->buffer.length)
					{
						if (req->att_opcode == ATT_OPCODE_WRITE_REQ)
							iLE_send_attribute_write_rsp(a4wp_server.app_handle, req->conn_id, req->att_opcode, req->att_id, 0, ATT_ERR_INVALID_PDU, NULL);
					}
					else
#endif
					{
						set_value_from_buffer(map_id, &req->buffer);
						if (req->att_opcode == ATT_OPCODE_WRITE_REQ)
						{
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
							log_time_stamp(TIME_A4WP_ATTR_READ_RESP);
#endif
							iLE_send_attribute_write_rsp(a4wp_server.app_handle, req->conn_id, req->att_opcode, req->att_id, 0, ATT_SUCCESS, NULL);
						}
						logd("a4wp_server.att_val_map[map_id].value.pru_client_conf_desc_val:%d", a4wp_server.att_val_map[map_id].value.pru_client_conf_desc_val);
						if (map_id == CLIENT_CHAR_CONFIG_ID)
						{
							if ((a4wp_server.att_val_map[map_id].value.pru_client_conf_desc_val & 0x01) == 0x01)
							{
								logd("Notification: TRUE");
								a4wp_server.configure_for_notify = TRUE;
							}
							if ((a4wp_server.att_val_map[map_id].value.pru_client_conf_desc_val & 0x02) == 0x02)
							{
								logd("Indication: TRUE");
								a4wp_server.configure_for_indication = TRUE;
							}
							if (a4wp_server.att_val_map[map_id].value.pru_client_conf_desc_val == 0x00)
							{
								a4wp_server.configure_for_notify = FALSE;
								a4wp_server.configure_for_indication = FALSE;
							}
						}
						app_dealloc(req);
					}
					osa_stop_timer(&(a4wp_server.timer_id),A4WP_SRV_TIMER,0);

					if(map_id == PRU_CTRL_CHARACTERISTIC_ID)
					{
						if(a4wp_server.a4wp_sm_handler)
							a4wp_server.a4wp_sm_handler(A4WP_PRU_CONTROL_MESSAGE_RCVD_CB, &a4wp_server.att_val_map[map_id].value.pru_control_char_val);
					}
				}
				break;
				case A4WP_NOTIFY_REQ:
				{
					logd("A4WP_NOTIFY_REQ");
					buffer_t* buffer = (buffer_t*)(void *)msg->param;
					memcpy (buffer->data, &a4wp_server.att_val_map[PRU_ALERT_PARAM_CHARACTERISTIC_ID].value.pru_alert_param_char_val, sizeof (pru_alert_param_char_t));
					iLE_send_notification(a4wp_server.app_handle, a4wp_server.conn_id, a4wp_server.att_val_map[PRU_ALERT_PARAM_CHARACTERISTIC_ID].att_id, buffer, FALSE);
					app_dealloc (buffer);
				}
				break;
				case A4WP_IND_REQ:
				{
					logd("A4WP_IND_REQ");
					buffer_t* buffer = (buffer_t*)(void *)msg->param;
					memcpy (buffer->data, &a4wp_server.att_val_map[PRU_ALERT_PARAM_CHARACTERISTIC_ID].value.pru_alert_param_char_val, sizeof (pru_alert_param_char_t));
					iLE_send_notification(a4wp_server.app_handle, a4wp_server.conn_id, a4wp_server.att_val_map[PRU_ALERT_PARAM_CHARACTERISTIC_ID].att_id, buffer, TRUE);
					app_dealloc (buffer);
				}
				break;
				case A4WP_IND_CFM_RECVD:
				{
					logd("A4WP_IND_CFM_RECVD");
					if(a4wp_server.a4wp_sm_handler)
						a4wp_server.a4wp_sm_handler(A4WP_INDICATION_CONFIRMATION_RCVD_CB, NULL);
				}
					break;
				case A4WP_START_ADV_REQ:
				{
					logd("A4WP_START_ADV_REQ");
					iLE_start_discoverable(a4wp_server.app_handle,0,
							GAP_ADV_TYPE_CONNECTABLE_UNDIRECTED, GAP_ADV_FLAGS_LE_LIMITED_DISCOVERABLE, NULL, 0, FALSE, FALSE);
				}
				break;
				case A4WP_STOP_ADV_REQ:
				{
					logd("A4WP_STOP_ADV_REQ");
					iLE_stop_discoverable(a4wp_server.app_handle);
				}
				break;
				case A4WP_DISCONNECT_REQ:
				{
					logd("A4WP_DISCONNECT_REQ");
					iLE_disconnect(a4wp_server.app_handle, a4wp_server.conn_id);
				}
				break;
				default:
				{
					logd("A4WP: Invalid opcode");
				}
				break;
			}
			app_dealloc(msg);
		}
	}
	osa_semaphore_delete(&a4wp_server.msg_sem);
	osa_semaphore_put(&a4wp_server.thread_sem);
	osa_thread_exit(NULL);
}

/*******************************************************************/
/********************* Exported functions to CSE *******************/
/*******************************************************************/

UINT8 a4wp_write_adv_parameters(UINT8 rssi, UINT8 adv_flags)
{
	logd("");
	a4wp_server.advt_data.wpt_service_UUID = WPT_SERVICE_UUID;
	a4wp_server.advt_data.pru_rssi_param = rssi;
	a4wp_server.advt_data.adv_flags = adv_flags;
	return TRUE;
}

BOOLEAN a4wp_start_advertisement(void)
{
	logd("");
	a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
	if(!msg)
		return FALSE;
#endif
	msg->opcode = A4WP_START_ADV_REQ;
	msg->param = NULL;
	enqueue(&a4wp_server.req_queue,msg);
	signal_req();
	return TRUE;
}

BOOLEAN a4wp_stop_advertisement(void)
{
	logd("");
	a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
	if(!msg)
		return FALSE;
#endif
	msg->opcode = A4WP_STOP_ADV_REQ;
	msg->param = NULL;
	enqueue(&a4wp_server.req_queue,msg);
	signal_req();
	return TRUE;
}

BOOLEAN a4wp_send_alert_notification(UINT8 flag,BOOLEAN is_indication)
{
	logd("");
	buffer_t* buffer = NULL;
	a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
	if (!msg)
		return FALSE;
#endif

	if(is_indication)
	{
		if(a4wp_server.configure_for_indication == TRUE)
			msg->opcode = A4WP_IND_REQ;
		else
			{
				logd("PTU not subscribed Indication");
				app_dealloc(msg);
				return FALSE;
			}
	}
	else
	{
		if(a4wp_server.configure_for_notify == TRUE)
			msg->opcode = A4WP_NOTIFY_REQ;
		else
		{
			logd("PTU not subscribed Indication");
			app_dealloc(msg);
			return FALSE;
		}
	}
	buffer = (buffer_t*) app_alloc (sizeof (buffer_t) + sizeof (pru_alert_param_char_t));
#if (PARANOID_STACK == TRUE)
	if (!buffer)
	{
		app_dealloc(msg);
		return FALSE;
	}
#endif
	buffer->length = sizeof (pru_alert_param_char_t);
	buffer->offset = 0;
	UINT8 *p = buffer->data;
	UINT8_TO_STREAM(p, flag);
	memcpy ((void *)p, (void *)&a4wp_server.remote_bd_addr, BD_ADDR_LEN);
	memcpy (&a4wp_server.att_val_map[PRU_ALERT_PARAM_CHARACTERISTIC_ID].value.pru_alert_param_char_val, buffer->data, sizeof (pru_alert_param_char_t));
	msg->param = (UINT8 *)buffer;
	enqueue(&a4wp_server.req_queue,msg);
	signal_req();
	return TRUE;
}

static UINT8 a4wp_write_ptu_static_parameters(ptu_static_param_char_t *param)
{
#if (PARANOID_STACK == TRUE)
	if(param == NULL)
		return FALSE;
#endif
	memcpy((void *)&a4wp_server.att_val_map[PTU_STATIC_PARAM_CHARACTERISTIC_ID].value.ptu_static_param_char_val,
			(void *)param, sizeof(ptu_static_param_char_t));
	a4wp_server.att_val_map[PTU_STATIC_PARAM_CHARACTERISTIC_ID].length = sizeof(pru_static_param_char_t);
	return TRUE;
}

static UINT8 a4wp_write_pru_alert_char(pru_alert_param_char_t *param)
{
#if (PARANOID_STACK == TRUE)
	if(param == NULL)
		return FALSE;
#endif
	memcpy((void *)&a4wp_server.att_val_map[PRU_ALERT_PARAM_CHARACTERISTIC_ID].value.pru_alert_param_char_val,
			(void *)param, sizeof(pru_alert_param_char_t));
	a4wp_server.att_val_map[PRU_ALERT_PARAM_CHARACTERISTIC_ID].length = sizeof(pru_alert_param_char_t);
	return TRUE;
}

UINT8 a4wp_write_static_parameters(pru_static_param_char_t *param)
{
#if (PARANOID_STACK == TRUE)
	if(param == NULL)
		return FALSE;
#endif

#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_A4WP_SET_STATIC_PARAM_REQ);
#endif

	memcpy((void *)&a4wp_server.att_val_map[PRU_STATIC_PARAM_CHARACTERISTIC_ID].value.pru_static_param_char_val,
			(void *)param, sizeof(pru_static_param_char_t));
	a4wp_server.att_val_map[PRU_STATIC_PARAM_CHARACTERISTIC_ID].length = sizeof(pru_static_param_char_t);
	return TRUE;
}

UINT8 a4wp_write_dynamic_parameters(pru_dynamic_param_char_t *param)
{
	logd("");
#if (PARANOID_STACK == TRUE)
	if(param == NULL)
		return FALSE;
#endif
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
		log_time_stamp(TIME_A4WP_SET_DYNAMIC_PARAM_REQ);
#endif
	memcpy(&a4wp_server.att_val_map[PRU_DYNAMIC_PARAM_CHARACTERISTIC_ID].value.pru_dynamic_param_char_val, param,
			sizeof(pru_dynamic_param_char_t));
	a4wp_server.att_val_map[PRU_DYNAMIC_PARAM_CHARACTERISTIC_ID].length = sizeof(pru_dynamic_param_char_t);
	return TRUE;
}

UINT8 a4wp_disconnect(UINT8 reason)
{
	a4wp_msg_t *msg = (a4wp_msg_t *)app_alloc(sizeof(a4wp_msg_t));
#if (PARANOID_STACK == TRUE)
	if(!msg)
		return FALSE;
#endif
	msg->opcode = A4WP_DISCONNECT_REQ;
	msg->param = &reason;
	enqueue(&a4wp_server.req_queue,msg);
	signal_req();
	return TRUE;
}

static void test_a4wp_start_adv(UINT8* arg)
{
	a4wp_start_advertisement();
}

static void test_a4wp_stop_adv(UINT8* arg)
{
	a4wp_stop_advertisement();
}

static void dummy_a4wp_sm_handler(a4wp_sm_opcodes_t opcode,void *param)
{
#if (MODULE_DBG_LVL < DBG_LVL_DEBUG)
	char *sm_opcode_str[] =
	{
			"A4wP_APP_REGISTERED_CB",
			"A4WP_CONNECTION_COMPLETE_CB",
			"A4WP_DISCONNECTION_COMPLETE_CB"
			"A4WP_PRU_CONTROL_MESSAGE_RCVD_CB",
			"A4WP_PTU_STATIC_PARAMS_RCVD_CB",
	};

	logd("opcode:%s", sm_opcode_str[opcode]);
#endif
}

static void test_a4wp_sm_init(UINT8* arg)
{
	ptu_static_param_char_t param1;
	memset (&param1, 0x05, sizeof(ptu_static_param_char_t));
	a4wp_write_ptu_static_parameters(&param1);

	pru_alert_param_char_t param2;
	memset (&param2, 0x06, sizeof(pru_alert_param_char_t));
	a4wp_write_pru_alert_char(&param2);

	/* Set PRU static param. */
	pru_static_param_char_t param3;
	UINT8 arr[20] = {0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x01, 0x37, 0xcc, 0x10, 0x84, 0x35, 0x88, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	memcpy(&param3, arr, sizeof(pru_static_param_char_t));
	a4wp_write_static_parameters(&param3);

	pru_dynamic_param_char_t param4;
	memset(&param4, 0x00, sizeof (pru_dynamic_param_char_t));
	param4.optional_validity = 0xC0;
	param4.v_rect = 0x0A;
	param4.i_rect = 0x0F;
	a4wp_write_dynamic_parameters(&param4);

	a4wp_register_sm_cb(dummy_a4wp_sm_handler);

	a4wp_write_adv_parameters(0x10, 0x20);
}

static void test_a4wp_send_alert_notification(UINT8 *arg)
{
	a4wp_send_alert_notification(0x03,FALSE);

	a4wp_send_alert_notification(0x04, TRUE);

	a4wp_send_alert_notification(0x00, FALSE);
}

static void test_a4wp_disconnect(UINT8* arg)
{
	a4wp_disconnect(0x04);
}

static const cmd_t cmd_arr[] = {
{"init",					test_a4wp_sm_init},
{"send_alert_notify", 		test_a4wp_send_alert_notification},
{"start_adv",				test_a4wp_start_adv},
{"stop_adv",				test_a4wp_stop_adv},
{"disconnect", 				test_a4wp_disconnect},
{ "_end_", 					NULL }};

void a4wp_init()
{
	 INT8 ret = init_q(&a4wp_server.req_queue);
#if (PARANOID_STACK == TRUE)
	if (ret != STATUS_SUCCESS)
		return;
#endif
	a4wp_server.state = TRUE;
	osa_semaphore_create(&a4wp_server.thread_sem, 0);

	osa_thread_create(A4WP_THREAD, a4wp_main_thread_handler, PROFILE_THREAD_PRIORITY);

	osa_semaphore_get(&a4wp_server.thread_sem);

	dev_ctl_cb.iLE_scan_result_cb = NULL;
	dev_ctl_cb.iLE_bonding_completed_cb = NULL;
	dev_ctl_cb.iLE_stack_initialized_cb = a4wp_bt_stack_initialized_cb;
	dev_ctl_cb.iLE_scan_completed_cb = NULL;
	dev_ctl_cb.iLE_on_connected_cb = a4wp_on_connected_cb;
	dev_ctl_cb.iLE_on_disconnected_cb = a4wp_on_disconnected_cb;

	gatt_cb.iLE_on_attribute_read_cb = NULL;
	gatt_cb.iLE_on_attribute_write_cb = NULL;
	gatt_cb.iLE_on_primary_service_discovered_cb = NULL;
	gatt_cb.iLE_on_included_service_discovered_cb = NULL;
	gatt_cb.iLE_on_characteristic_discovered_cb = NULL;
	gatt_cb.iLE_on_descriptor_discovered_cb = NULL;
	gatt_cb.iLE_on_notification_cb = NULL;
	gatt_cb.iLE_on_notification_registered_cb = NULL;

	gatt_cb.iLE_on_service_started_cb = a4wp_on_service_started_cb;
	gatt_cb.iLE_on_characteristic_added_cb = NULL;
	gatt_cb.iLE_on_descriptor_added_cb = NULL;
	gatt_cb.iLE_on_attribute_read_req_cb = a4wp_on_attribute_read_req_cb;
	gatt_cb.iLE_on_attribute_write_req_cb = a4wp_on_attribute_write_req_cb;
	gatt_cb.iLE_on_indication_confirmation_cb = a4wp_on_indication_confirmation_cb;

	if (iLE_register_application(&dev_ctl_cb,&gatt_cb,"pru",cmd_arr, a4wp_register_app_cb))
	{
		logd("A4WP App registered");
	}
}

/** @brief Initialize A4WP Profile
 * Function: a4wp_init
 * 			Initialize A4WP profile and register
 * 			the required call back functions and Profile
 * 			Message Queue.
 * @return  TRUE if A4WP profile is initialized else
 * 			FALSE.
 */
UINT8 a4wp_register_sm_cb(cb_handler_t sm_handler)
{
	logd("");
	a4wp_server.a4wp_sm_handler = sm_handler;
	a4wp_add_service();
	return TRUE;
}
/** @brief De-Initialize A4WP Profile
 * Function: a4wp_deinit
 * 			De-Initialize A4WP profile and Unregister
 * 			the GATT and GAP services. Also destroy the
 * 			Profile Message queue.
 * @return  Always TRUE.
 */
void a4wp_cleanup(char *arg)
{
	logd("");
	iLE_stop_discoverable(a4wp_server.app_handle);
	if (a4wp_server.a4wp_srv_handle)
		iLE_remove_service(a4wp_server.app_handle, a4wp_server.a4wp_srv_handle);
	iLE_deregister_application(a4wp_server.app_handle);
	a4wp_server.state = FALSE;
	signal_req();
	cleanup_q(&a4wp_server.req_queue);
	osa_delete_timer(&a4wp_server.timer_id, A4WP_SRV_TIMER);
	osa_semaphore_get(&a4wp_server.thread_sem);
	osa_semaphore_delete(&a4wp_server.thread_sem);
	osa_thread_join(A4WP_THREAD, NULL);
	a4wp_server.a4wp_sm_handler = NULL;
}
#endif
