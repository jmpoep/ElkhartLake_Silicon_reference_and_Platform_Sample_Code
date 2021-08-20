/** @file
  Find Me Reporter (server) implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "app_interface.h"
#include "profile_adapt.h"
#include "fmp_reporter.h"

#define MODULE_DBG_LVL FMP_SRV_APP_DBG_LVL
#include "log.h"

#if (FMP_SRV_APP == TRUE)

static fmp_srv_data_t fmp_srv_data;

static device_control_callbacks_t fmp_srv_dev_ctl_cb;
static gatt_callbacks_t fmp_srv_gatt_cb;
static void signal_req(void);

/*******************************************************************/
/********************* Exported functions to CSE *******************/
/*******************************************************************/
/** @brief Trigger the FMP reporter profile thread
 * Function: signal_req
 * 			release the Interface thread queue
 * 			and process the messages in Application thread
 * 			context
 * @return None
 */
static inline void signal_req()
{
	osa_semaphore_put(&fmp_srv_data.msg_sem);
}

/** @brief FMP reporter application registered call back
 * Function: fmp_srv_register_app_cb
 * 			The FMP server profile is registered with
 * 			GATT layer
 * @param app_handle - GATT assigned application handle
 * @param result - TRUE if registration is success.
 * 					else FALSE;
 * @return None
 */
static void fmp_srv_register_app_cb(UINT8 app_handle, BOOLEAN result)
{
	logi("app_handle:%d", app_handle);
	if (result)
	{
		fmp_srv_data.app_handle = app_handle;
		fmp_srv_data.state = TRUE;
		fmp_srv_msg_t *msg = (fmp_srv_msg_t *)alloc_queue_element(sizeof(fmp_srv_msg_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
		if(!msg)
			return;
#endif
		msg->opcode = FMP_SRV_APP_REGISTERED;
		msg->param = NULL;
		enqueue(&fmp_srv_data.req_queue,msg);
		signal_req();
	}
	else
	{	loge("FMP_SRV App could not be registered");
		fmp_srv_data.state = FALSE;
		signal_req();
		cleanup_q(&fmp_srv_data.req_queue);
		osa_semaphore_get(&fmp_srv_data.thread_sem);
		osa_semaphore_delete(&fmp_srv_data.thread_sem);
		osa_thread_join(FMP_SRV_THREAD, NULL);
	}

}

/** @brief Bluetooth LE stack initialized callback
 * Function: fmp_srv_bt_stack_initialized_cb
 *
 * @return None
 */

static void fmp_srv_bt_stack_initialized_cb(BOOLEAN initialized)
{
	logi("");
	if (initialized)
	{
		fmp_srv_msg_t *msg = (fmp_srv_msg_t *)alloc_queue_element(sizeof(fmp_srv_msg_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
		if (!msg)
			return;
#endif
		msg->opcode = FMP_SRV_BT_CORE_STACK_INIT;
		msg->param = NULL;
		enqueue(&fmp_srv_data.req_queue, msg);
		signal_req();
	}
}

/** @brief FMP Service is registered and started
 * Function: fmp_srv_on_service_started_cb
 * 			FMP server service is started.
 * 	@param uuid - 16 bit UUID of Immidiate alert service.
 * 	@param result - TRUE if service started successfully
 * 	@param service - Service pointer.
 * @return None
 */

static void fmp_srv_on_service_started_cb(trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 service_handle)
{
	logi("");
	fmp_srv_data.service_handle = service_handle;
	fmp_srv_msg_t *msg = (fmp_srv_msg_t *)alloc_queue_element(sizeof(fmp_srv_msg_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
		if (!msg)
			return;
#endif
		msg->opcode = FMP_SRV_SERVICE_STARTED;
		msg->param = NULL;
		enqueue(&fmp_srv_data.req_queue, msg);
		signal_req();
}

/** @brief Read Characteristic value request callback
 * Function: fmp_srv_on_characteristic_read_req_cb
 *
 * @param device - connected device data structure
 * @param characteristic - characteristic to be read
 * @param offset	- offset of read location in value buffer.
 * @return None
 */
static void fmp_srv_on_attribute_read_req_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset)
{
	logi("");
	fmp_srv_attr_read_req_param_t *req = (fmp_srv_attr_read_req_param_t *)alloc_queue_element(sizeof(fmp_srv_attr_read_req_param_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
	if (!req)
		return;
#endif
	fmp_srv_msg_t *msg = (fmp_srv_msg_t *)alloc_queue_element(sizeof(fmp_srv_msg_t), APP_ALLOC);
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
	msg->opcode = FMP_SRV_CHAR_READ_REQ;
	msg->param = (UINT8 *)req;
	enqueue(&fmp_srv_data.req_queue, msg);
	signal_req();
}

/** @brief Write Characteristic value request callback
 * Function: fmp_srv_on_characteristic_write_req_cb
 * 			 callback function will be called when a remote device will write
 * 			 the attribute this application has registered.
 */
static void fmp_srv_on_attribute_write_req_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, buffer_t* buffer)
{
	fmp_srv_data.alert_level = buffer->data[buffer->offset + 0];
	logw("fmp_srv_data.alert_level:%d", fmp_srv_data.alert_level);
	fmp_srv_attr_write_req_param_t *req = (fmp_srv_attr_write_req_param_t *)app_alloc(sizeof(fmp_srv_attr_write_req_param_t));
#if (PARANOID_STACK == TRUE)
	if (!req)
		return;
#endif
	fmp_srv_msg_t *msg = (fmp_srv_msg_t *)alloc_queue_element(sizeof(fmp_srv_msg_t), APP_ALLOC);
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
	msg->opcode = FMP_SRV_CHAR_WRITE_REQ;
	msg->param = (UINT8 *)req;
	enqueue(&fmp_srv_data.req_queue, msg);
	signal_req();
}

/** @brief Register FMP services
 * Function: fmp_srv_register_services
 * 			Register Immidiate alert services
 * 			with GATT/Service Manager
 * @return  Always TRUE.
 */
static BOOLEAN fmp_srv_register_services()
{
	logi("");
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_srv_data.app_handle);
	UINT16_TO_UUID(IMMEDIATE_ALERT_SERVICE_UUID, fmp_srv_data.service_uuid);
	iLE_add_service(new_trans_id, &fmp_srv_data.service_uuid, ATTR_TYPE_PRIMARY_SERVICE, 0, 1, 0);
	uuid_t char_uuid;
	UINT16_TO_UUID(ALERT_LEVEL_CHAR_UUID, char_uuid);
	iLE_add_characteristic(new_trans_id, &char_uuid, ATTRIBUTE_PROPERTY_READ | ATTRIBUTE_PROPERTY_WRITE_NO_RESPONSE, ATTRIBUTE_PERMISSION_READ | ATTRIBUTE_PERMISSION_WRITE);
	iLE_start_service(new_trans_id);
	return TRUE;
}

/** @brief Set Advertisement data
 * Function: fmp_set_adv_data
 *
 * @return  TRUE if Advertisement data is set.
 */
static BOOLEAN fmp_set_adv_data()
{
	logi("");
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_srv_data.app_handle);
	if (!iLE_set_local_device_name(new_trans_id, sizeof(DEVICE_NAME), (UINT8*) DEVICE_NAME))
		return FALSE;

	return TRUE;
}

/** @brief FMP server Profile Thread handler
 * Function: fmp_srv_main_thread_handler
 * 			Process the GATT Requests and
 * 			send responses.
 * @return  Always NULL.
 */
static osa_thread_ret_t fmp_srv_main_thread_handler(osa_thread_arg_t arg)
{
	logi("");
	osa_semaphore_create(&fmp_srv_data.msg_sem, 0);
	osa_semaphore_put(&fmp_srv_data.thread_sem);
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_srv_data.app_handle);
	while (fmp_srv_data.state)
	{
		fmp_srv_msg_t *msg = (fmp_srv_msg_t *)dequeue(&fmp_srv_data.req_queue);
		if (msg == NULL)
			osa_semaphore_get(&fmp_srv_data.msg_sem);
		else
		{ /* check for the Message and process */
			switch (msg->opcode)
			{
				case FMP_SRV_APP_REGISTERED:
				{
					logi("FMP_SRV_APP_REGISTERED");
				}
				break;
				case FMP_SRV_BT_CORE_STACK_INIT:
				{
					logi("FMP_SRV_BT_CORE_STACK_INIT");
					fmp_srv_register_services();
				}
				break;
				case FMP_SRV_SERVICE_STARTED:
				{
					logi("FMP_SRV_SERVICE_STARTED");
					fmp_srv_data.alert_level = 0;
					fmp_set_adv_data();
					iLE_start_discoverable(new_trans_id, 0, GAP_ADV_TYPE_CONNECTABLE_UNDIRECTED, GAP_ADV_FLAGS_LE_GENERAL_DISCOVERABLE, NULL, 0, FALSE, FALSE);
				}
				break;
				case FMP_SRV_DISCONNECTED:
				{
					logd("FMP_SRV_DISCONNECTED");
					fmp_srv_data.isconnected = FALSE;
					iLE_start_discoverable(new_trans_id, 0, GAP_ADV_TYPE_CONNECTABLE_UNDIRECTED, GAP_ADV_FLAGS_LE_GENERAL_DISCOVERABLE, NULL, 0, FALSE, FALSE);
				}
				break;
				case FMP_SRV_CHAR_READ_REQ:
				{
					logd("FMP_SRV_CHAR_READ_REQ");
					fmp_srv_attr_read_req_param_t *req = (fmp_srv_attr_read_req_param_t *)(void *)msg->param;
					buffer_t *buffer = (buffer_t*) app_alloc (sizeof (buffer_t) + sizeof (UINT8));
					if (!buffer)
					{
						app_dealloc(req);
						continue;
					}
					logd("fmp_srv_data.alert_level:%d", fmp_srv_data.alert_level);
					buffer->length = 1;
					*buffer->data = fmp_srv_data.alert_level;
					iLE_send_attribute_read_rsp(new_trans_id, req->conn_id, req->att_opcode, req->att_id, ATT_SUCCESS, buffer);
					app_dealloc(buffer);
					app_dealloc(req);
				}
				break;
				case FMP_SRV_CHAR_WRITE_REQ:
				{
					logd("FMP_SRV_CHAR_WRITE_REQ");
					fmp_srv_attr_write_req_param_t *req = (fmp_srv_attr_write_req_param_t *)(void *)msg->param;
					if (req->att_opcode == ATT_OPCODE_WRITE_REQ)
					{
						iLE_send_attribute_write_rsp(new_trans_id, req->conn_id, req->att_opcode, req->att_id, 0, ATT_SUCCESS, NULL);
					}
					app_dealloc(req);
#if (TARGET_THREADX == TRUE)
						alert_level_data_cb(fmp_srv_data.alert_level);
#endif
				}
				break;
				case FMP_SRV_START_ADV_REQ:
				{
					logd("FMP_SRV_START_ADV_REQ");
					iLE_start_discoverable(new_trans_id, 0,
							GAP_ADV_TYPE_CONNECTABLE_UNDIRECTED, GAP_ADV_FLAGS_LE_GENERAL_DISCOVERABLE, NULL, 0, FALSE, FALSE);
				}
				break;
				case FMP_SRV_STOP_ADV_REQ:
				{
					logd("FMP_SRV_STOP_ADV_REQ");
					iLE_stop_discoverable(new_trans_id);
				}
				break;
				default:
				{
					logw("FMP: Invalid opcode");
				}
				break;
			}
			dealloc_queue_element(msg);
		}

	}
	osa_semaphore_delete(&fmp_srv_data.msg_sem);
	osa_semaphore_put(&fmp_srv_data.thread_sem);
	osa_thread_exit(NULL);
}

/** @brief Initialise FMP reporter profile
 * Function: fmp_srv_init
 * 			Initialise FMP reporter profile and register
 * 			the required call back functions and Profile
 * 			Message Queue.
 * @return  NONE.
 */
void fmp_srv_init(char *arg)
{
	logi("");
	INT8 ret = init_q(&fmp_srv_data.req_queue);
#if (PARANOID_STACK == TRUE)
	if (ret != STATUS_SUCCESS)
		return;
#endif
	fmp_srv_data.state = TRUE;
	osa_semaphore_create(&fmp_srv_data.thread_sem, 0);

	osa_thread_create(FMP_SRV_THREAD, fmp_srv_main_thread_handler, PROFILE_THREAD_PRIORITY);

	osa_semaphore_get(&fmp_srv_data.thread_sem);

	fmp_srv_dev_ctl_cb.iLE_scan_completed_cb = NULL;
	fmp_srv_dev_ctl_cb.iLE_stack_initialized_cb = fmp_srv_bt_stack_initialized_cb;

	/* we don't need any client related callback */
	fmp_srv_gatt_cb.iLE_on_attribute_read_cb = NULL;
	fmp_srv_gatt_cb.iLE_on_attribute_write_cb = NULL;
	fmp_srv_gatt_cb.iLE_on_primary_service_discovered_cb = NULL;
	fmp_srv_gatt_cb.iLE_on_included_service_discovered_cb = NULL;
	fmp_srv_gatt_cb.iLE_on_characteristic_discovered_cb = NULL;
	fmp_srv_gatt_cb.iLE_on_descriptor_discovered_cb = NULL;
	fmp_srv_gatt_cb.iLE_on_notification_cb = NULL;
	fmp_srv_gatt_cb.iLE_on_notification_registered_cb = NULL;

	/* register server related callback */

	fmp_srv_gatt_cb.iLE_on_attribute_read_req_cb = fmp_srv_on_attribute_read_req_cb;
	fmp_srv_gatt_cb.iLE_on_attribute_write_req_cb = fmp_srv_on_attribute_write_req_cb;
	fmp_srv_gatt_cb.iLE_on_indication_confirmation_cb = NULL;

	fmp_srv_gatt_cb.iLE_on_service_started_cb = fmp_srv_on_service_started_cb;

	if (iLE_register_application(&fmp_srv_dev_ctl_cb,&fmp_srv_gatt_cb,NULL,NULL,fmp_srv_register_app_cb))
	{
		logi("FMP Server App registered");
		return;
	}
}

/** @brief De-Initialise FMP reporter Profile
 * Function: fmp_srv_cleanup
 * 			De-Initialise FMP reporter profile and Unregister
 * 			the GATT and GAP services. Also destroy the
 * 			Profile Message queue.
 * @return  NONE.
 */
void fmp_srv_cleanup(char *arg)
{
	logi("");
	trans_id_t new_trans_id = 0;
	add_appid_to_trans_id(&new_trans_id, fmp_srv_data.app_handle);
	iLE_stop_discoverable(new_trans_id);
	iLE_remove_service(new_trans_id, fmp_srv_data.service_handle);
	iLE_deregister_application(fmp_srv_data.app_handle);
	fmp_srv_data.state = FALSE;
	signal_req();
	cleanup_q(&fmp_srv_data.req_queue);
	osa_semaphore_get(&fmp_srv_data.thread_sem);
	osa_semaphore_delete(&fmp_srv_data.thread_sem);
	osa_thread_join(FMP_SRV_THREAD, NULL);
}

#endif /* FMP_SRV_APP == TRUE */
