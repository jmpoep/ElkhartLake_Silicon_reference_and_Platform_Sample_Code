/** @file
  Interface layer implementation to be used by apps.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "config_host.h"
#include "device_struct.h"
#include "hci_host.h"
#include "int_interface.h"
#include "interface.h"
#include "profile_mgr.h"
#include "device_mgr.h"
#include "service_mgr.h"
#include "smp_mgr.h"
#include "gap.h"
#include "l2cap.h"
#include "att.h"
#include "smp.h"

#define MODULE_DBG_LVL INTERFACE_DBG_LVL
#include "log.h"

// start putting variables in retention data/bss sections
RETENTION_SECTION_START
adapter_t g_local_adapter;
RETENTION_SECTION_END

app_cmd_list_t app_cmd_list[MAX_NUMBER_OF_APP];

struct pending_cleanup
{
	UINT8 smp_mgr_cleanup;
	UINT8 sm_cleanup;
	UINT8 pm_cleanup;
	UINT8 dm_cleanup;
	UINT8 att_cleanup;
	UINT8 l2cap_cleanup;
	UINT8 gap_cleanup;
	UINT8 all_done;
} pending_cleanup_flags;

static BOOLEAN stack_running = FALSE;
osa_semaphore_t stack_thread_sem;

#if (THREADLESS_STACK == FALSE)
static osa_semaphore_t msg_sem;
osa_thread_ret_t stack_main_thread_handler(osa_thread_arg_t arg);
#endif

INT8 interface_handler();

#if (GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE)

static void copy_buffer(buffer_t *dest, buffer_t* src)
{
	if (!dest || !src)
		return;
	dest->length = src->length;
	dest->offset = 0;
	memcpy(&dest->data, src->data + src->offset, src->length);
}

#endif /* GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE */


void stack_interface_signal_req()
{
#if (THREADLESS_STACK == FALSE)
	osa_semaphore_put(&msg_sem);
#endif
}

interface_req_elem_t* get_interface_req_buffer(UINT8 opcode, UINT8 conn_id, UINT16 len)
{
	interface_req_elem_t *req;
	if ((UINT32)len + sizeof(interface_req_elem_t) > (UINT32)0xFFFF)
		return NULL;
	req = (interface_req_elem_t*)alloc_queue_element(sizeof(interface_req_elem_t) + len, RETENTION_ALLOC);
	if(req == NULL)
		return NULL;
	req->req_opcode = opcode;
	req->conn_id = conn_id;
	return req;
}

#if (RX_PROCESSING_IN_TIMER_THREAD == TRUE)
static INT8 enqueue_interface_req(interface_req_elem_t *req)
{
	INT8 ret;
	ret = enqueue(&g_local_adapter.interface_req_q, (void*)req);
	return ret;
}
#endif
static INT8 enqueue_signal_interface_req(interface_req_elem_t *req)
{
	INT8 ret;
	ret = enqueue(&g_local_adapter.interface_req_q, (void*)req);
	if(ret == STATUS_SUCCESS)
		stack_interface_signal_req();
	else
		return ret;
#if (THREADLESS_STACK == TRUE)
	ret = interface_handler();
#endif
	return ret;
}

static INT8 create_timer_expire_req(osa_timeout_func_t cback, osa_timer_arg_t arg )
{
	INT8 ret;

	timer_expire_elem_t *req = (timer_expire_elem_t*)alloc_queue_element(sizeof(timer_expire_elem_t), RETENTION_ALLOC);

	if (req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	req->cback = cback;
	req->arg = arg;
	ret = enqueue(&g_local_adapter.timer_expire_q, (void*) req);

	if (ret == STATUS_SUCCESS)
	{
#if (THREADLESS_STACK == TRUE)
		ret = interface_handler();
#endif
		stack_interface_signal_req();
	}
	return ret;
}

#if (TARGET_UEFI == FALSE)
static void register_app_cmd(const char* app_prefix, const cmd_t* cmd_arr)
{
	int idx;
	if (!app_prefix)
		return;

	for (idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
	{
		if (!app_cmd_list[idx].cmd_arr)
		{
			strcpy(app_cmd_list[idx].app_prefix, app_prefix);
			app_cmd_list[idx].cmd_arr = cmd_arr;
			break;
		}
	}
}
#endif

static void show_stack_configuration()
{
	logi("\t Device name is \"%s\"", DEVICE_NAME);
	logi("\t SMP IO Capability is 0x%02x", SMP_DEFAULT_IO_CAP);
	logi("\t L2CAP COC is %s", L2CAP_COC? "ENABLED":"DISABLED");
	logi("\t LE Ping is %s", LE_PING_ENABLE? "ENABLED":"DISABLED");
	logi("\t GAP Central Role support is %s", GAP_CENTRAL_ROLE_SUPPORTED? "ENABLED":"DISABLED");
	logi("\t GAP Peripheral Role support is %s", GAP_PERIPHERAL_ROLE_SUPPORTED? "ENABLED":"DISABLED");
	logi("\t GATT Client support is %s", GATT_CLIENT_SUPPORTED? "ENABLED":"DISABLED");
	logi("\t GATT Server support is %s", GATT_SERVER_SUPPORTED? "ENABLED":"DISABLED");
	logi("\t Memory management is %s", MEM_MGMT_INTERNAL? "INTERNAL":"EXTERNAL");
	logi("\t Paranoid checks are %s", PARANOID_STACK? "ENABLED":"DISABLED");
	logi("\t Test Code is %s", TEST_CODE? "ENABLED":"DISABLED");
}

static INT8 init_layers()
{
	INT8 ret = STATUS_SUCCESS;

#if (TARGET_UEFI == FALSE)
	osa_wait_event_flag();
#endif
/*ATP uses its own memory management */
#if (MEM_MGMT_INTERNAL == TRUE)
	mem_mgr_init();
#endif

#if (THREADLESS_STACK == FALSE)
	osa_semaphore_create(&msg_sem, 0);
#endif

	if (g_local_adapter.adapter_state == ADAPTER_STATE_DISABLED
#if (TARGET_THREADX_RW == TRUE)
		|| osa_is_cold_boot_cond()
#endif
		)
	{
		if((ret = init_q(&g_local_adapter.interface_req_q)) != STATUS_SUCCESS)
			return ret;
		if((ret = init_q(&g_local_adapter.timer_expire_q)) != STATUS_SUCCESS)
			return ret;

		if (g_local_adapter.uart_port_name == NULL)
			ret = hci_host_init(BT_USERIAL_PORT_NAME, BT_USERIAL_BAUD_RATE);
		else
			ret = hci_host_init(g_local_adapter.uart_port_name, BT_USERIAL_BAUD_RATE);

		if (ret != STATUS_SUCCESS)
		{
			loge("hci_init failed with %d", ret);
			gap_cleanup_complete_cb();
		}

		ret = gap_init();

		ret = l2cap_init();

		ret = att_init();
		ret = dm_init();
		ret = pm_init();



#if (GATT_SERVER_SUPPORTED == TRUE)
		ret = sm_init();
#endif

#if (TARGET_UEFI == TRUE)
		fw_dw_finish(TRUE);
		init_log_files(0);
#else /* TARGET_UEFI == TRUE */
#if (BTSNOOPDISP_INCLUDED == TRUE)
		btsnoop_log_open(BTSNOOPDISP_LOG_FILENAME);
#endif
#if (TARGET_THREADX_RW != TRUE && THREADLESS_STACK == FALSE)
		osa_semaphore_put(&stack_thread_sem);
#endif /* TARGET_THREADX_RW != TRUE && THREADLESS_STACK == FALSE */
		dm_enable();
#endif /* TARGET_UEFI == TRUE */
	}
	else
	{
		osa_restore_connected_devices();
		hci_init_on_wakeup();
	}

	return ret;
}

static void cleanup_layers()
{
#if (BTSNOOPDISP_INCLUDED == TRUE)
	btsnoop_log_close();
#endif
	hci_cleanup();
	cleanup_q(&g_local_adapter.interface_req_q);
	cleanup_q(&g_local_adapter.timer_expire_q);
#if (MEM_MGMT_INTERNAL == TRUE)
	mem_mgr_cleanup();
#endif
#if (PROFILING ==TRUE)
	logw(" stack_max_size = %u, app_max_size = %u, l2cap_max_size = %u", stack_max_size, app_max_size, l2cap_max_size);
#endif
#if (THREADLESS_STACK == FALSE)
	osa_semaphore_delete(&msg_sem);
#endif

	/* We still need this even for THREADLESS_STACK build, since cleanup_layers is called in the
	 * context of userial read thread (GAP cleanup), and stack_thread_sem helps to synchronise
	 * this with the main (app) thread.
	 */
	osa_semaphore_put(&stack_thread_sem);
}

/*********************************************************************
 *				INTERFACE APIs
 *********************************************************************/

INT8 iLE_stack_init()
{
	stack_running = TRUE;
	osa_semaphore_create(&stack_thread_sem, 0);

	show_stack_configuration();

#if (TARGET_THREADX_RW == FALSE && THREADLESS_STACK == FALSE)
	osa_thread_create(STACK_MAIN_THREAD, stack_main_thread_handler, STACK_THREAD_PRIORITY);
#endif

#if (THREADLESS_STACK == TRUE)
	return init_layers();
#else
	return STATUS_SUCCESS;
#endif
}

void iLE_stack_cleanup()
{
	UINT8 idx;

#if (SMP_FEATURE)
	if (pending_cleanup_flags.smp_mgr_cleanup == 0)
	{
		pending_cleanup_flags.smp_mgr_cleanup = 1;
		smp_mgr_cleanup();
		return;
	}
#endif /* SMP_FEATURE */
#if (GATT_SERVER_SUPPORTED == TRUE)
	if (pending_cleanup_flags.sm_cleanup == 0)
	{
		pending_cleanup_flags.sm_cleanup = 1;
		sm_cleanup();
		return;
	}
#endif
	if (!pending_cleanup_flags.pm_cleanup)
	{
		pending_cleanup_flags.pm_cleanup = 1;
		pm_cleanup();
		return;
	}

	if (!pending_cleanup_flags.dm_cleanup)
	{
		pending_cleanup_flags.dm_cleanup = 1;
		dm_cleanup();
		return;
	}

	if (!pending_cleanup_flags.att_cleanup)
	{
		pending_cleanup_flags.att_cleanup = 1;
		att_cleanup();
		return;
	}

	if (!pending_cleanup_flags.l2cap_cleanup)
	{
		pending_cleanup_flags.l2cap_cleanup = 1;
		l2cap_cleanup();
		return;
	}

	if (!pending_cleanup_flags.gap_cleanup)
	{
		pending_cleanup_flags.gap_cleanup = 1;
		pending_cleanup_flags.all_done = 1;
		gap_cleanup();
		return;
	}

	/* Send deinitialized callback to last app and deregister it */
	for (idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
	{
		if (g_local_adapter.app_list[idx] != NULL )
			break;
	}
	if (idx != MAX_NUMBER_OF_APP)
	{
		if (g_local_adapter.app_list[idx] && g_local_adapter.app_list[idx]->app_device_control_cb)
		{
			if (g_local_adapter.app_list[idx]->app_device_control_cb->iLE_stack_initialized_cb)
			{
				g_local_adapter.app_list[idx]->app_device_control_cb->iLE_stack_initialized_cb(FALSE);
				pm_deregister_application(idx);
			}
		}
	}

	if (pending_cleanup_flags.all_done == 1)
	{
		pending_cleanup_flags.smp_mgr_cleanup = 0;
		pending_cleanup_flags.sm_cleanup = 0;
		pending_cleanup_flags.pm_cleanup = 0;
		pending_cleanup_flags.dm_cleanup = 0;
		pending_cleanup_flags.att_cleanup = 0;
		pending_cleanup_flags.l2cap_cleanup = 0;
		pending_cleanup_flags.gap_cleanup = 0;
	}

	cleanup_layers();
	memset(&g_local_adapter, 0, sizeof(g_local_adapter));
	logd("Clean up done!\n");
	return;
}

/** @brief Application calls this function to register with core stack.
 *
 * Function: iLE_register_application
 * 			 Application will receive a application handle as a result of
 * 			 successful registration. Application should save the handle
 * 			 and pass the same value to the core stack whenever calling
 * 			 core stack api in future. Application handle is valid until
 * 			 application calls de-register or application gets de-registered
 * 			 by any other means. In case of de-registration application needs
 * 			 to register again by calling this api.
 *
 * @param dev_cb - Call backs for adapter enable / disable and scan / discoverable
 * @param gatt_cb - Call backs for GATT operations
 * @param register_application_cb - this function will be called after registration
 * 										with app_handle for this application.
 * @return Error code.
 */
INT8 iLE_register_application(device_control_callbacks_t* dev_cb, gatt_callbacks_t* gatt_cb, const char *prefix, const cmd_t* cmd_arr, register_application_cb_t register_application_cb)
{
	interface_req_elem_t *req;
	pm_register_application_param_t* param;

	logi("");
	if(g_local_adapter.adapter_state == ADAPTER_STATE_DISABLED || g_local_adapter.adapter_state == ADAPTER_STATE_DISABLING)
		return STATUS_ERR_STACK_NOT_INIT;
	if (register_application_cb == NULL)
		return STATUS_ERR_INVALID_PARAM;
	req = get_interface_req_buffer(API_REQ_OPCODE_REGISTER_APPLICATION, 0, sizeof(pm_register_application_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
#if (TARGET_UEFI == FALSE)
	register_app_cmd(prefix, cmd_arr);
#endif
	param =
			(pm_register_application_param_t*)req->parameter;
	param->dev_cb = dev_cb;
	param->gatt_cb = gatt_cb;
	param->register_application_cb = register_application_cb;
	return enqueue_signal_interface_req(req);


}

/** @brief Application calls this function to de-register from core stack.
 *
 * Function: iLE_deregister_application
 * 			 Application de-registers itself from the core stack. If this application
 * 			 requested connection to any remote device previously then that device
 * 			 may be disconnected depending on if other application(s) use the same device.
 * 			 This would stop all the GATT services registered by this application if any.
 * 			 This call ends the validity of app_handle. Thus, the application should
 * 			 register again if it wants to be useful in future.
 *
 * @param app_handle - Handle of the application.
 * @return Error code.
 */
INT8 iLE_deregister_application(UINT8 app_handle)
{
	pm_deregister_application_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state == ADAPTER_STATE_DISABLED || g_local_adapter.adapter_state == ADAPTER_STATE_DISABLING)
		return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_DEREGISTER_APPLICATION, 0, sizeof(pm_deregister_application_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param =
			(pm_deregister_application_param_t*)req->parameter;

	param->app_handle = app_handle;
	return enqueue_signal_interface_req(req);


}

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

/** @brief Requests core stack to set advertisement data
 *
 * Function: iLE_set_advertisement_data
 *			 This requests the core stack to set advertisement data. Advertisement
 *			 type can be found in device_struct.h. Please refer to core spec to
 *			 set the advertisement data. This data will be broadcasted with the
 *			 advertisement packet by this device. Application is responsible to
 *			 start advertisement and advertisement wouldn't be started as a result
 *			 of this call.
 *
 * @param app_handle - Handle of the application.
 * @param length - length of the data to be set
 * @param type - Type of the advertisement data
 * @param data - data buffer of the advertisement data
 * @return Error code.
 */
INT8 iLE_set_advertisement_data(trans_id_t trans_id, UINT8 length, UINT8 type, UINT8 *data)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_SET_ADVERTISEMENT_DATA, 0, sizeof(dm_adv_scanresp_data_param_t) + length);
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	dm_adv_scanresp_data_param_t* param = (dm_adv_scanresp_data_param_t*) req->parameter;

	param->length = length;
	param->type = type;
	memcpy(param->data, data, length);
	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);

	return ret;
}

/** @brief Requests core stack to remove advertisement data
 *
 * Function: iLE_remove_advertisment_data
 *
 * @param app_handle - Handle of the application.
 * @param length - length of the data to be removed
 * @param type - Type of the advertisement data
 * @param data - data buffer of the advertisement data
 * @return Error code.
 */
INT8 iLE_remove_advertisment_data(trans_id_t trans_id, UINT8 length, UINT8 type, UINT8 *data)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_REMOVE_ADVERTISEMENT_DATA, 0, sizeof(dm_adv_scanresp_data_param_t) + length);
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	dm_adv_scanresp_data_param_t* param = (dm_adv_scanresp_data_param_t*)req->parameter;

	param->length = length;
	param->type = type;
	memcpy(param->data, data, length);

	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);

	return ret;
}

/** @brief Requests core stack to set scan response data
 *
 * Function: iLE_set_scan_response_data
 *			 This requests the core stack to set advertisement data. Advertisement
 *			 type can be found in device_struct.h. Please refer to core spec to
 *			 set the advertisement data. This data will be broadcasted with the
 *			 advertisement packet by this device. Application is responsible to
 *			 start advertisement and advertisement wouldn't be started as a result
 *			 of this call.
 *
 * @param app_handle - Handle of the application.
 * @param length - length of the data to be set
 * @param type - Type of the scan response data
 * @param data - data buffer of the scan response data
 * @return Error code.
 */
INT8 iLE_set_scan_response_data(UINT8 app_handle, UINT8 length, UINT8 type, UINT8 *data)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_SET_SCAN_RESPONSE_DATA, 0, sizeof(dm_adv_scanresp_data_param_t) + length);
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	dm_adv_scanresp_data_param_t* param = (dm_adv_scanresp_data_param_t*)req->parameter;

	param->length = length;
	param->type = type;
	memcpy(param->data, data, length);

	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);

	return ret;
}

/** @brief Requests core stack to remove scan response data
 *
 * Function: iLE_remove_scan_response_data
 *
 * @param app_handle - Handle of the application.
 * @param length - length of the data to be removed
 * @param type - Type of the scan response data
 * @param data - data buffer of the scan response data
 * @return Error code.
 */
INT8 iLE_remove_scan_response_data(UINT8 app_handle, UINT8 length, UINT8 type, UINT8 *data)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_REMOVE_SCAN_RESPONSE_DATA, 0, sizeof(dm_adv_scanresp_data_param_t) + length);
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	dm_adv_scanresp_data_param_t* param = (dm_adv_scanresp_data_param_t*)req->parameter;

	param->length = length;
	param->type = type;
	memcpy(param->data, data, length);

	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);

	return ret;
}

/** @brief Requests core stack to make this device discoverable
 *
 * Function: iLE_start_discoverable
 *			 This function will make the bluetooth controller discoverable if not
 *			 discoverable before. It will use the advertisement data as set by
 *			 set_advertisement_data api by applications. Application only has
 *			 control over advertisement data and advertisement timeout for specifying
 *			 limited disverability or general discoverability. Other configuration
 *			 values are decided by core stack module.
 *
 * @param app_handle - Handle of the application.
 * @param timeout_msec - Timeout for stopping discoverable. If passed 0 then it is
 * 						never timeout.
 * @param type - Type of the advertisement.
 * @param flags - Advertisement flags.
 * @param remote_bd_addr - Remote BD address for directed advertisement.
 * @param addr_type - Address type for directed advertisement.
 * @param use_whitelist - Set if whitelist is to be used for filtering.
 * @param background - Set if low duty cycle advertising is to be done.
 * @return Error code.
 */
INT8 iLE_start_discoverable(trans_id_t trans_id, UINT32 timeout_msec, UINT8 type, UINT8 flags, UINT8 *remote_bd_addr, UINT8 addr_type, BOOLEAN use_whitelist, BOOLEAN background)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_START_DISCOVERABLE, 0, sizeof(cm_start_adv_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	UINT8 null_addr[] = {0,0,0,0,0,0};
	cm_start_adv_param_t* param = (cm_start_adv_param_t*)req->parameter;

	param->timeout_msec = timeout_msec;
	param->type = type;
	param->flags = flags;
	if (remote_bd_addr)
		memcpy(param->remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
	else
		memcpy(param->remote_bd_addr, null_addr, BD_ADDR_LEN);
	param->addr_type = addr_type;
	param->use_whitelist = use_whitelist;
	param->background = background;

	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to make this device discoverable
 *
 * Function: iLE_start_discoverable
 *			 This function will make the bluetooth controller discoverable if not
 *			 discoverable before. It will use the advertisement data as set by
 *			 set_advertisement_data api by applications. Application only has
 *			 control over advertisement data and advertisement timeout for specifying
 *			 limited disverability or general discoverability. Other configuration
 *			 values are decided by core stack module.
 *
 * @param app_handle - Handle of the application.
 * @param timeout_msec - Timeout for stopping discoverable. If passed 0 then it is
 * 						never timeout.
 * @param type - Type of the advertisement.
 * @param flags - Advertisement flags.
 * @param remote_bd_addr - Remote BD address for directed advertisement.
 * @param addr_type - Address type for directed advertisement.
 * @param adv_int_min - Minimum advertising interval.
 * @param adv_int_max - Maximum advertising interval.
 * @param use_whitelist - Set if whitelist is to be used for filtering.
 * @return Error code.
 */
INT8 iLE_start_discoverable_ex(trans_id_t trans_id, UINT32 timeout_msec, UINT8 type, UINT8 flags, UINT8 *remote_bd_addr, UINT8 addr_type, UINT16 adv_int_min, UINT16 adv_int_max, BOOLEAN use_whitelist)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if (!is_adv_params_valid(adv_int_min, adv_int_max, type))
		return STATUS_ERR_INVALID_PARAM;
	UINT8 null_addr[] = {0,0,0,0,0,0};
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_START_DISCOVERABLE, 0, sizeof(cm_start_adv_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	cm_start_adv_param_t* param = (cm_start_adv_param_t*)req->parameter;

	param->timeout_msec = timeout_msec;
	param->type = type;
	param->flags = flags;
	if (remote_bd_addr)
		memcpy(param->remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
	else
		memcpy(param->remote_bd_addr, null_addr, BD_ADDR_LEN);
	param->addr_type = addr_type;
	param->use_whitelist = use_whitelist;
	param->adv_int_min = adv_int_min;
	param->adv_int_max = adv_int_max;

	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to stop this device to be discoverable
 *
 * Function: iLE_stop_discoverable
 *			 This function will stop the device from broadcasting advertisement
 *			 packets. So after this no other device can find this device in there
 *			 scan list.
 *
 * @param app_handle - Handle of the application.
 * @return Error code.
 */
INT8 iLE_stop_discoverable(trans_id_t trans_id)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_STOP_DISCOVERABLE, 0, 0);
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

/** @brief Requests core stack to change the local device name
 *
 * Function: iLE_set_local_device_name
 *			 This api allows the application to change the local name of this
 *			 device. This will update the device name field in advertisement data.
 *			 Thus the name would be reflected when this device is made discoverable
 *			 next time.
 *
 * @param app_handle - Handle of the application.
 * @param name - new name of this device.
 * @param len - length of the name in bytes. [This param will be deleted soon]
 * @return Error code.
 */
INT8 iLE_set_local_device_name(trans_id_t trans_id, UINT8 len, UINT8* name)
{
	dm_set_local_device_name_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_SET_LOCAL_DEVICE_NAME, 0, sizeof(dm_set_local_device_name_param_t) + len);
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param =
			(dm_set_local_device_name_param_t*)req->parameter;

	memcpy(param->name, name, len);
	param->len = len;

	return enqueue_signal_interface_req(req);;


}

/** @brief Requests core stack for the local device name
 *
 * Function: iLE_get_local_device_name
 *			 This api allows the application to get the local name of this
 *			 device.
 *
 * @param app_handle - Handle of the application.
 * @param name - name of this device.
 * @return Length of the name.
 */
UINT8 iLE_get_local_device_name(trans_id_t trans_id, UINT8* name)
{
	logi("");

	return dm_get_local_device_name(name);
}

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

/** @brief Requests core stack to start scanning.
 *
 * Function: iLE_start_scan
 *			 This function will start scanning procedure to discover nearby
 *			 LE devices. It will set hard-coded value for scanning parameters.
 *			 Application can only set scan timeout (after this many seconds this
 *			 device will stop searching for devices.
 *			 Application which is calling this function, should register scan_completed_cb
 *			 call back in the device_control_cb. When scan is completed then
 *			 all the discovered devices details will be passed to the application
 *			 using scan_completed_cb function. Application is expected to initiate
 *			 connection to a device itself.
 *
 * @param app_handle - Handle of the application.
 * @param timeout_sec - Timeout for stopping scanning. If passed 0 then it is
 * 						never timeout.
 * @param active - Set if active scanning is to be used.
 * @param use_whitelist - Set if whitelist is to be used for filtering.
 * @param background - Set if low duty cycle scanning is to be done.
 * @return Error code.
 */
INT8 iLE_start_scan(trans_id_t trans_id, UINT32 timeout_msec, BOOLEAN active, BOOLEAN limited, BOOLEAN use_whitelist, BOOLEAN background, UINT8 num_filter_uuids, UINT16* filter_uuids)
{
	cm_start_scan_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_START_SCAN, 0, sizeof(cm_start_scan_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (cm_start_scan_param_t*)req->parameter;

	param->trans_id = trans_id;
	param->timeout_msec = timeout_msec;
	param->active = active;
	param->limited = limited;
	param->use_whitelist = use_whitelist;
	param->background = background;

	if (num_filter_uuids)
		memcpy(param->filter_uuids, filter_uuids, num_filter_uuids * sizeof(UINT16));

	return enqueue_signal_interface_req(req);


}

/** @brief Requests core stack to start scanning.
 *
 * Function: iLE_start_scan
 *			 This function will start scanning procedure to discover nearby
 *			 LE devices. It will set hard-coded value for scanning parameters.
 *			 Application can only set scan timeout (after this many seconds this
 *			 device will stop searching for devices.
 *			 Application which is calling this function, should register scan_completed_cb
 *			 call back in the device_control_cb. When scan is completed then
 *			 all the discovered devices details will be passed to the application
 *			 using scan_completed_cb function. Application is expected to initiate
 *			 connection to a device itself.
 *
 * @param app_handle - Handle of the application.
 * @param timeout_sec - Timeout for stopping scanning. If passed 0 then it is
 * 						never timeout.
 * @param active - Set if active scanning is to be used.
 * @param use_whitelist - Set if whitelist is to be used for filtering.
 * @param scan_int - Scan interval.
 * @param scan_win - Scan window.
 * @return Error code.
 */
INT8 iLE_start_scan_ex(trans_id_t trans_id, UINT32 timeout_msec, BOOLEAN active, BOOLEAN limited, BOOLEAN use_whitelist, BOOLEAN background, UINT16 scan_int, UINT16 scan_win, UINT8 num_filter_uuids, UINT16* filter_uuids)
{
	cm_start_scan_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_START_SCAN, 0, sizeof(cm_start_scan_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	if (!is_scan_params_valid(scan_int, scan_win))
		return STATUS_ERR_INVALID_PARAM;
	param = (cm_start_scan_param_t*)req->parameter;

	param->trans_id = trans_id;
	param->timeout_msec = timeout_msec;
	param->active = active;
	param->limited = limited;
	param->use_whitelist = use_whitelist;
	param->background = background;
	param->scan_int = scan_int;
	param->scan_win = scan_win;

	if (num_filter_uuids)
		memcpy(param->filter_uuids, filter_uuids, num_filter_uuids * sizeof(UINT16));

	return enqueue_signal_interface_req(req);

}

/** @brief Requests core stack to stop searching for nearby LE devices
 *
 * Function: iLE_stop_scan
 *			 This function stops the device searching facility. After completion
 *			 of this procedure the application will get a call back scan_completed_cb
 *			 with all the list of device found.
 *
 * @param app_handle - Handle of the application.
 * @return Error code.
 */
INT8 iLE_stop_scan(trans_id_t trans_id)
{
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_STOP_SCAN, 0, 0);
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	return enqueue_signal_interface_req(req);

}

/** @brief Requests core stack to create connection to a remote device
 *
 * Function: iLE_connect
 *			 This api allows the application to connection to a remote device.
 *			 This will create a LE-U connection if it is not present. On top of
 *			 the LE-U connection this will create all necessary things.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param addr_type - Address type of remote device.
 * @return Error code.
 */
INT8 iLE_connect(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 addr_type)
{
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	return iLE_connect_ex(trans_id, remote_bd_addr, addr_type, SCAN_CONN_INTERVAL, SCAN_CONN_WINDOW, CONNECTION_INTERVAL_MIN, CONNECTION_INTERVAL_MAX, CONNECTION_LATENCY, CONNECTION_SUP_TIMEOUT);
}

/** @brief Requests core stack to create connection to a remote device
 *
 * Function: iLE_connect
 *			 This api allows the application to connection to a remote device.
 *			 This will create a LE-U connection if it is not present. On top of
 *			 the LE-U connection this will create all necessary things.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param addr_type - Address type of remote device.
 * @param scan_int - Scan interval.
 * @param scan_win - Scan window.
 * @param conn_int_min - Minimum connection interval.
 * @param conn_int_max - Maximum connection interval.
 * @param conn_lat - Connection latency.
 * @param sup_timeout - Supervision timeout.
 * @return Error code.
 */
INT8 iLE_connect_ex(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 addr_type, UINT16 scan_int, UINT16 scan_win, UINT16 conn_int_min, UINT16 conn_int_max, UINT16 conn_lat, UINT16 sup_timeout)
{
	pm_connect_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if (!remote_bd_addr)
		return STATUS_ERR_INVALID_PARAM;
	if (!is_conn_params_valid(scan_int, scan_win, conn_int_min, conn_int_max, conn_lat, sup_timeout))
		return STATUS_ERR_INVALID_PARAM;
	req = get_interface_req_buffer(API_REQ_OPCODE_CONNECT, 0, sizeof(pm_connect_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (pm_connect_param_t*)req->parameter;

	param->trans_id = trans_id;
	memcpy(param->remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
	param->addr_type = addr_type;
	param->scan_int = scan_int;
	param->scan_win = scan_win;
	param->conn_int_min = conn_int_min;
	param->conn_int_max = conn_int_max;
	param->conn_lat = conn_lat;
	param->sup_timeout = sup_timeout;
	return enqueue_signal_interface_req(req);
}
INT8 iLE_auto_connect(trans_id_t trans_id, UINT8 *remote_bd_addr, UINT8 addr_type, BOOLEAN enable)
{
	pm_auto_connect_param_t* param;
	interface_req_elem_t *req;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if (!remote_bd_addr)
			return STATUS_ERR_INVALID_PARAM;
		logi("");
		req = get_interface_req_buffer(API_REQ_OPCODE_AUTO_CONNECT, 0, sizeof(pm_auto_connect_param_t));
		if(req == NULL)
			return STATUS_ERR_INSUFFICIENT_RESOURCES;
		param = (pm_auto_connect_param_t*) req->parameter;

		param->trans_id = trans_id;
		param->enable = enable;
		memcpy(param->remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
		param->addr_type = addr_type;
		return enqueue_signal_interface_req(req);

}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

/** @brief Requests core stack to terminate connection to a remote device
 *
 * Function: iLE_disconnect
 *			 This API allows the application to say to core stack that it will no
 *			 longer needs connection to this remote device. Core stack will terminate
 *			 the connection if no application needs connection to this remote
 *			 device.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_disconnect(trans_id_t trans_id, UINT8 conn_id, UINT8 reason)
{
	interface_req_elem_t *req;
	pm_disconnect_param_t* param;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if (conn_id >= MAX_NUM_CONNECTED_DEVICE)
		return STATUS_ERR_INVALID_PARAM;
	logi("");
	req = get_interface_req_buffer(API_REQ_OPCODE_DISCONNECT, conn_id, sizeof(pm_disconnect_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (pm_disconnect_param_t*)req->parameter;

	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->reason = reason;

	return enqueue_signal_interface_req(req);

}

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

/** @brief Requests core stack to add a device to whitelist
 *
 * Function: iLE_add_to_whitelist
 *			 This API allows the application to say to core stack that it wants
 *			 to add a device to the whitelist for future operations
 *
 * @param app_handle - Handle of the application.
 * @param addr_type - Address type of the device (public/random).
 * @param bdaddr - Bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_add_to_whitelist(trans_id_t trans_id, UINT8 addr_type, UINT8 *bdaddr)
{
	dm_whitelist_op_param_t* param;
	interface_req_elem_t *req;
	UINT8 bd_addr[BD_ADDR_LEN];
	UINT8 *rev_bdaddr = bd_addr;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_ADD_TO_WHITELIST, 0, sizeof(dm_whitelist_op_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (dm_whitelist_op_param_t*)req->parameter;

	param->addr_type = addr_type;
	REVERSE_ARRAY_TO_STREAM(rev_bdaddr, bdaddr, BD_ADDR_LEN);
	memcpy(param->bdaddr, &bd_addr, BD_ADDR_LEN);

	return enqueue_signal_interface_req(req);

}

/** @brief Requests core stack to remove a device from whitelist
 *
 * Function: iLE_remove_from_whitelist
 *			 This API allows the application to say to core stack that it wants
 *			 to remove a device from the whitelist for future operations
 *
 * @param app_handle - Handle of the application.
 * @param addr_type - Address type of the device (public/random).
 * @param bdaddr - Bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_remove_from_whitelist(trans_id_t trans_id, UINT8 addr_type, UINT8 *bdaddr)
{
	dm_whitelist_op_param_t* param;
	interface_req_elem_t *req;
	UINT8 bd_addr[BD_ADDR_LEN];
	UINT8 *rev_bdaddr = bd_addr;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_REMOVE_FROM_WHITELIST, 0, sizeof(dm_whitelist_op_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (dm_whitelist_op_param_t*)req->parameter;

	param->addr_type = addr_type;
	REVERSE_ARRAY_TO_STREAM(rev_bdaddr, bdaddr, BD_ADDR_LEN);
	memcpy(param->bdaddr, &bd_addr, BD_ADDR_LEN);

	return enqueue_signal_interface_req(req);

}

/** @brief Requests core stack to clear the whitelist
 *
 * Function: iLE_clear_whitelist
 *			 This API allows the application to say to core stack that it wants
 *			 to clear the whitelist and remove all device entries
 *
 * @param app_handle - Handle of the application.
 * @return Error code.
 */
INT8 iLE_clear_whitelist(trans_id_t trans_id)
{
	interface_req_elem_t *req;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_CLEAR_WHITELIST, 0, 0);
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	return enqueue_signal_interface_req(req);

}

#if (CONTROLLER_PRIVACY)

/** @brief Requests core stack to add a device to resolving list
 *
 * Function: iLE_add_to_reslovinglist
 *			 This API allows the application to say to core stack that it wants
 *			 to add a device to the resolving list for future operations
 *
 * @param app_handle - Handle of the application.
 * @param addr_type - Address type of the device (public/random).
 * @param bdaddr - Bluetooth MAC address of the remote device.
 * @param peer_irk - remote device IRK
 * @param_local_irk - local device IRK
 * @return Error code.
 */
INT8 iLE_add_to_resolvinglist(trans_id_t trans_id, UINT8 addr_type, UINT8 *bdaddr, UINT8 * peer_irk, UINT8 * local_irk)
{
	dm_resolving_op_param_t* param ;
	interface_req_elem_t *req;
	UINT8 bd_addr[BD_ADDR_LEN];
	UINT8 *rev_bdaddr = bd_addr;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_ADD_TO_RESOLVINGLIST, 0, sizeof(dm_resolving_op_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (dm_resolving_op_param_t*)req->parameter;

	param->peer_addr_type = addr_type;
	REVERSE_ARRAY_TO_STREAM(rev_bdaddr, bdaddr, BD_ADDR_LEN);
	memcpy(param->peer_bdaddr, &bd_addr, BD_ADDR_LEN);
	memcpy(param->peer_irk , peer_irk, 16);
	memcpy(param->local_irk , local_irk, 16);

	return enqueue_signal_interface_req(req);

}

/** @brief Requests core stack to remove a device from resolving list
 *
 * Function: iLE_remove_from_reslovinglist
 *			 This API allows the application to say to core stack that it wants
 *			 to remove a device from the resolving list for future operations
 *
 * @param app_handle - Handle of the application.
 * @param addr_type - Address type of the device (public/random).
 * @param bdaddr - Bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_remove_from_resolvinglist(trans_id_t trans_id, UINT8 addr_type, UINT8 *bdaddr)
{
	dm_resolving_op_param_t* param;
	interface_req_elem_t *req;
	UINT8 bd_addr[BD_ADDR_LEN];
	UINT8 *rev_bdaddr = bd_addr;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_REMOVE_FROM_RESOLVINGLIST, 0, sizeof(dm_resolving_op_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (dm_resolving_op_param_t*)req->parameter;

	param->peer_addr_type = addr_type;
	REVERSE_ARRAY_TO_STREAM(rev_bdaddr, bdaddr, BD_ADDR_LEN);
	memcpy(param->peer_bdaddr, &bd_addr, BD_ADDR_LEN);

	return enqueue_signal_interface_req(req);

}

#endif /* CONTROLLER_PRIVACY */

#if (GATT_SERVER_SUPPORTED == TRUE)

/** @brief Requests core stack to add a GATT service to the service database
 *
 * Function: iLE_add_service
 *			 GATT server application uses this API to add service it wants to
 *			 support.
 *			 \note {Application should call start_service to make it discoverable
 *			 		by remote device.}
 *
 * @param app_handle - Handle of the application.
 * @param uuid - UUID of the service to be added.
 * @param is_primary - TRUE if this service is primary. FALSE for included service
 * @return Error code.
 */
INT8 iLE_add_service(trans_id_t trans_id, uuid_t *uuid, UINT8 service_type, UINT8 num_of_incl_srv, UINT8 num_of_char, UINT8 num_of_desc)
{
	sm_add_service_param_t* param ;
	INT8 ret;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_ADD_SERVICE, 0, sizeof(sm_add_service_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (sm_add_service_param_t*)req->parameter;

	param->trans_id = trans_id;
	param->uuid = *uuid;
	param->service_type = service_type;
	param->num_of_incl_srv = num_of_incl_srv;
	param->num_of_char = num_of_char;
	param->num_of_desc = num_of_desc;
	ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to add a GATT service to the service database
 *
 * Function: iLE_add_included_service
 *			 GATT server application uses this API to add include service it wants to
 *			 support.
 *			 \note {Application should call start_service to make it discoverable
 *			 		by remote device.}
 *
 * @param app_handle - Handle of the application.
 * @param uuid - UUID of the service to be added.
 * @param service_type - Primary / secondary / included
 * @param start_handle - Handle of service declaration of included service
 * @param end_handle - End Handle of included service definition
 * @return Error code.
 */
INT8 iLE_add_included_service(trans_id_t trans_id, uuid_t *uuid, UINT8 service_type, UINT16 start_handle, UINT16 end_handle)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_ADD_INCLUDED_SERVICE, 0, sizeof(sm_add_include_service_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	sm_add_include_service_param_t* param = (sm_add_include_service_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->uuid = *uuid;
	param->service_type = service_type;
	param->start_handle = start_handle;
	param->end_handle = end_handle;

	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to add a GATT characteristic to a service
 *
 * Function: iLE_add_characteristic
 *			 GATT server application uses this API to add characteristic it wants to
 *			 support. Prior to use this procedure application shall use add_service
 *			 API to create the service.
 *
 * @param app_handle - Handle of the application.
 * @param srv_uuid - UUID of the service.
 * @param char_uuid - UUID of the characteristic to be added to the service
 * @param property - Property of the characteristic. Or the properties as needed.
 * @param value - Default of the characteristic. NULL otherwise.
 * @param value_len - Length in Bytes of the value being passed.
 * @return Error code.
 */
INT8 iLE_add_characteristic(trans_id_t trans_id, uuid_t *uuid, UINT8 property, UINT16 permission)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_ADD_CHARACTERISTIC, 0, sizeof(sm_add_characteristic_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	sm_add_characteristic_param_t* param =
			(sm_add_characteristic_param_t*) req->parameter;

	param->trans_id = trans_id;
	param->uuid = *uuid;
	param->property = property;
	param->permission = permission;
	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to add a GATT descriptor to a characteristic
 *
 * Function: iLE_add_descriptor
 *			 GATT server application uses this API to add descriptor it wants to
 *			 support. Prior to use this procedure application shall use add_service
 *			 API to create the service and add_characterisitic to create characteristic.
 *
 * @param trans_id - Add descriptor request identifier.
 * @param uuid - UUID of the descriptor to be added
 * @param property - None(0x00) TODO: This parameter will be removed.
 * @param permission - Permission for read / write operation (valid types are ATTRIBUTE_PERMISSION_XXX)
 * 					   Ex: ATTRIBUTE_PERMISSION_READ|ATTRIBUTE_PERMISSION_WRITE etc
 * @return Error code.
 */
INT8 iLE_add_descriptor(trans_id_t trans_id, uuid_t *uuid, UINT8 property, UINT16 permission)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_ADD_DESCRIPTOR, 0, sizeof(sm_add_descriptor_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	sm_add_descriptor_param_t* param = (sm_add_descriptor_param_t*)req->parameter;

	param->trans_id = trans_id;
	param->uuid = *uuid;
	param->permission = permission;
	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to make a GATT service in service database discoverable
 *
 * Function: iLE_start_service
 *			 GATT server application uses this API to make a service visible to
 *			 a remote device. A remote device shall find out this new service
 *			 when a remote device would do primary service discovery procedure
 *			 after this procedure.
 *			 GATT server application shall use app_server and may use add_characteristic,
 *			 add_descriptor apis to add the service in the service database prior
 *			 to using this procedure.
 *
 * @param app_handle - Handle of the application.
 * @param uuid - UUID of the service.
 * @return Error code.
 */
INT8 iLE_start_service(trans_id_t trans_id)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_START_SERVICE, 0, sizeof(sm_start_service_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	sm_start_service_param_t* param = (sm_start_service_param_t*)req->parameter;

	param->trans_id = trans_id;
	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to remove a GATT service
 *
 * Function: iLE_remove_service
 *			 Stops the service to be discoverable from remote device and removes
 *			 the service from the service database.
 *
 * @param app_handle - Handle of the application.
 * @param uuid - UUID of the service.
 * @return Error code.
 */
INT8 iLE_remove_service(trans_id_t trans_id, UINT16 service_handle)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_REMOVE_SERVICE, 0, sizeof(sm_remove_service_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	sm_remove_service_param_t* param = (sm_remove_service_param_t*)req->parameter;

	param->trans_id = trans_id;
	param->service_handle = service_handle;
	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to send response for characteristic read request
 *
 * Function: iLE_send_attribute_read_rsp
 *			 GATT server application uses this API to send out response to a
 *			 characteristic read request from a remote device.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param att_id - Attribute handle value
 * @param offset - For characteristic long read this represents the value offset
 * @param value_length - Length in Bytes of the value
 * @param value - Buffer containing the whole / part of characteristic value
 * @param status - Status of the response
 * @return Error code.
 */
INT8 iLE_send_attribute_read_rsp(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT8 status, buffer_t* buffer)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_SEND_ATTRIBUTE_READ_RESPONSE, conn_id, sizeof(sm_send_attribute_read_rsp_param_t) + (buffer == NULL ? 0 : buffer->length));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	sm_send_attribute_read_rsp_param_t* param = (sm_send_attribute_read_rsp_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->att_opcode = att_opcode;
	param->att_id = att_id;
	copy_buffer(&param->buffer, buffer);
	param->status = status;
	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to send response for characteristic / descriptor write request
 *
 * Function: iLE_send_attribute_write_rsp
 *			 GATT server application uses this API to send out response to a
 *			 characteristic / descriptor write request from a remote device.
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - conn id for the device
 * @param att_id - attribute handle value
 * @param status - status of the write req. ATT error to be embedded by application for errors.
 * 					Otherwise ATT_SUCCESS
 * @param value - value to be sent for the prepared write response
 * @param len - length of the value to be sent in the prepared write response
 * @param offset - offset of the value to be written
 * @param is_execute_resp - if this is the resposne for the execute write
 * @return Error code.
 */
INT8 iLE_send_attribute_write_rsp(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, UINT8 status, buffer_t* buffer)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_SEND_ATTRIBUTE_WRITE_RESPONSE, conn_id, sizeof(sm_send_attribute_write_rsp_param_t) + ((buffer == NULL) ? 0 : buffer->length));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	sm_send_attribute_write_rsp_param_t* param = (sm_send_attribute_write_rsp_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->att_opcode = att_opcode;
	param->status = status;
	param->att_id = att_id;
	param->status = status;
	param->offset = offset;
	copy_buffer(&param->buffer, buffer);
	logd("Sending response");

	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to send notification / indication
 *
 * Function: iLE_send_notification
 *			 GATT server application uses this API to send notification / indication.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param characteristic - reference to gatt characteristic. This reference should be
 * 							the same reference which is passed from the service
 * 							discovery callback.
 * @param value - value buffer of the value to be notified / indicated.
 * @param value_len - Length in Bytes in of the value to be written
 * @param need_response - TRUE to send indication. FALSE for notification.
 * @return Error code.
 */
INT8 iLE_send_notification(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, buffer_t *buffer, BOOLEAN need_response)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if (!buffer)
		return STATUS_ERR_INVALID_PARAM;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_SEND_NOTIFICATION, conn_id, sizeof(sm_send_notification_param_t) + ((buffer == NULL) ? 0 : buffer->length));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	sm_send_notification_param_t* param = (sm_send_notification_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->att_id = att_id;
	copy_buffer(&param->buffer, buffer);
	param->need_resp = need_response;
	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to store the indication setting for service change characteristic in NVM
 *
 * Function: iLE_set_service_change_config
 *			 GATT server application uses this API to store the indication setting for service change characteristic in NVM.
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - connection id of remote device
 * @param is_notify - TRUE to send indication. FALSE for disable indication for service change characteristic.
 * @return Error code.
 */
INT8 iLE_set_service_change_config(trans_id_t trans_id, UINT8 conn_id, BOOLEAN is_notify)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_SET_SERVICE_CHANGE_CONFIG, conn_id, sizeof(sm_set_service_change_config_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	sm_set_service_change_config_param_t* param = (sm_set_service_change_config_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->is_notify = is_notify;

	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;

}

/** @brief Get the stored indication setting for service change characteristic from core stack
 *
 * Function: iLE_get_service_change_config
 *			 GATT server application uses this API to get the stored indication setting for service change characteristic in NVM
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - connection id of remote device
 * @return - TRUE if indication is set. FALSE if indication is disabled.
 */
BOOLEAN iLE_get_service_change_config(trans_id_t trans_id, UINT8 conn_id)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	return sm_get_service_change_config(conn_id);
}

#endif /* GATT_SERVER_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE)

/** @brief Requests core stack to discover primary service offered by a remote
 * 			device having uuid as specified
 *
 * Function: iLE_discover_primary_service
 *			 GATT client application uses this API to discover primary service
 *			 having UUID as specified in the argument. Core stack shall discover
 *			 all the characteristics and their descriptors as a part of this
 *			 API. on_service_discovered_cb call back will be called to the
 *			 application with reference to the service being discovered. Client
 *			 can use the characteristic / descriptor operation after this operation.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param service_uuid - 16 bit UUID of the service to be discovered
 * @return Error code.
 */
INT8 iLE_discover_primary_service(trans_id_t trans_id, UINT8 conn_id, uuid_t *filter_uuid)
{
	pm_discover_primary_service_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_DISCOVER_PRIMARY_SERVICE, conn_id, sizeof(pm_discover_primary_service_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (pm_discover_primary_service_param_t*)req->parameter;

	param->trans_id = trans_id;
	param->conn_id = conn_id;
	if (filter_uuid)
		memcpy (&param->filter_uuid, filter_uuid, sizeof (uuid_t));
	else
		param->filter_uuid.length = UUID_NULL_LEN;

	return enqueue_signal_interface_req(req);

}

INT8 iLE_discover_included_service(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	pm_discover_included_service_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_DISCOVER_INCLUDED_SERVICE, conn_id, sizeof(pm_discover_included_service_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (pm_discover_included_service_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->start_handle = start_handle;
	param->end_handle = end_handle;

	return enqueue_signal_interface_req(req);

}

INT8 iLE_discover_characteristic(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *filter_uuid)
{
	pm_discover_characteristic_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_DISCOVER_CHARACTERISTIC, conn_id, sizeof(pm_discover_characteristic_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	param = (pm_discover_characteristic_param_t*)req->parameter;

	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->start_handle = start_handle;
	param->end_handle = end_handle;
	if (filter_uuid)
		memcpy (&param->filter_uuid, filter_uuid, sizeof (uuid_t));
	else
		param->filter_uuid.length = UUID_NULL_LEN;

	return enqueue_signal_interface_req(req);

}

INT8 iLE_discover_descriptor(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle)
{
	pm_discover_descriptor_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_DISCOVER_DESCRIPTOR, conn_id, sizeof(pm_discover_descriptor_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (pm_discover_descriptor_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->start_handle = start_handle;
	param->end_handle = end_handle;
	return enqueue_signal_interface_req(req);

}

/** @brief Requests core stack to read a characteristic value
 *
 * Function: iLE_read_attribute_value
 *			 GATT client application uses this API to read characteristic
 *			 / dsecriptor value.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param read_param - Parameter of the read
 * @return Error code.
 */
INT8 iLE_read_attribute_value(trans_id_t trans_id, UINT8 conn_id, gatt_attribute_read_param_t *read_param)
{
	pm_read_attribute_value_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_READ_ATTRIBUTE_VALUE, conn_id, sizeof(pm_read_attribute_value_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (pm_read_attribute_value_param_t*)req->parameter;

	param->trans_id = trans_id;
	param->conn_id = conn_id;
	memcpy (&param->read_param, read_param, sizeof (gatt_attribute_read_param_t));
	return enqueue_signal_interface_req(req);

}

/** @brief Requests core stack to write a characteristic value
 *
 * Function: iLE_write_attribute_value
 *			 GATT client application uses this API to write attribute value.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param gatt_write_type - Type of the write
 * @param attribute - reference to gatt attribute.
 * @param value - value buffer of the value to be written to this characteristic.
 * 				  Depending on the value length core stack uses long write.
 * @param value_len - Length in Bytes in of the value to be written
 * @return Error code.
 */
INT8 iLE_write_attribute_value(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, buffer_t *buffer)
{
	pm_write_attribute_value_param_t* param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_WRITE_ATTRIBUTE_VALUE, conn_id, sizeof(pm_write_attribute_value_param_t)+ ((buffer == NULL) ? 0 : buffer->length));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param =(pm_write_attribute_value_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->att_opcode = att_opcode;
	param->att_id = att_id;
	param->offset = offset;
	copy_buffer(&param->buffer, buffer);
	return enqueue_signal_interface_req(req);

}

/** @brief Requests core stack to enable / disable notification / indication of a characteristic
 *
 * Function: iLE_register_notification
 *			 GATT client application uses this API to enable / disable characteristic
 *			 notification / indication.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param characteristic - reference to gatt characteristic. This reference should be
 * 							the same reference which is passed from the service
 * 							discovery callback.
 * @param is_register - TRUE to register for notification / indication. FALSE to de-register.
 * @return Error code.
 */
INT8 iLE_register_notification(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, BOOLEAN is_register)
{
	pm_register_notification_param_t * param;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_REGISTER_NOTIFICATION, conn_id, sizeof(pm_register_notification_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (pm_register_notification_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->att_id = att_id;
	param->is_register = is_register;
	return enqueue_signal_interface_req(req);

}

#endif /* GATT_CLIENT_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE)

UINT16 iLE_get_att_mtu(trans_id_t trans_id, UINT8 conn_id)
{
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return 0;
	return pm_get_att_mtu(conn_id);
}

#endif /* GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE */

INT8 iLE_set_att_mtu(trans_id_t trans_id, UINT8 conn_id, UINT16 mtu_size)
{
	pm_set_att_mtu_param_t* param;
	interface_req_elem_t *req;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
		return STATUS_ERR_STACK_NOT_INIT;

	if(mtu_size < ATT_MIN_MTU_LEN || mtu_size > ATT_MAX_MTU_LEN)
		return STATUS_ERR_INVALID_PARAM;

	req = get_interface_req_buffer(API_REQ_OPCODE_SET_ATT_MTU_SIZE, conn_id, sizeof(pm_set_att_mtu_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (pm_set_att_mtu_param_t*)req->parameter;

	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->mtu_size = mtu_size;
	return enqueue_signal_interface_req(req);

}

#if (SMP_FEATURE)

/** @brief Requests core stack to initiate bonding procedure with a remote device
 *
 * Function: iLE_create_bond
 *			 Any application can use this API to create a bond with a device
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - Connection id.
 * @param auth_level_min - Minimum Level of authentication required when a bond is created with the remote device
 * @param key_size_min - Minimum length of key used for encryption.This value has to be in the range of 7 to 16.
 * @return Error code.
 */
INT8 iLE_create_bond(trans_id_t trans_id, UINT8 conn_id, UINT8 auth_level_min, UINT8 key_size_min)
{
	interface_req_elem_t *req;
	smpm_create_bond_param_t* param;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;

	req = get_interface_req_buffer(API_REQ_OPCODE_CREATE_BOND, 0, sizeof(smpm_create_bond_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (smpm_create_bond_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->auth_level_min = auth_level_min;
	param->key_size_min = key_size_min;
	param->cb = NULL;
	return enqueue_signal_interface_req(req);
}

/** @brief Requests core stack to remove bonding procedure with a remote device
 *
 * Function: iLE_remove_bond
 *			 Not supported yet. Coming soon.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_remove_bond(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 addr_type)
{
	interface_req_elem_t *req;
	smpm_remove_bond_param_t* param;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if (!remote_bd_addr)
		return STATUS_ERR_INVALID_PARAM;
	req = get_interface_req_buffer(API_REQ_OPCODE_REMOVE_BOND, 0, sizeof(smpm_remove_bond_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (smpm_remove_bond_param_t*)req->parameter;

	param->trans_id = trans_id;
	memcpy(param->remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
	param->addr_type = addr_type;
	return enqueue_signal_interface_req(req);

}


/** @brief Send the passkey input from the user to the SMP manager
 *
 * Function: iLE_send_passkey
 *			 SMP application uses this interface to send the passkey input from the user to the SMP manager
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device.
 * @param passkey - passkey input from the user.
 * @return Error code.
 */
INT8 iLE_send_passkey(trans_id_t trans_id, UINT8 *remote_bd_addr, UINT8 bdaddr_type, UINT32 passkey)
{
	interface_req_elem_t *req ;
	smpm_send_passkey_param_t * param;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if (!remote_bd_addr)
		return STATUS_ERR_INVALID_PARAM;
	req = get_interface_req_buffer(API_REQ_OPCODE_SEND_PASSKEY, 0, sizeof(smpm_send_passkey_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (smpm_send_passkey_param_t*)req->parameter;
	param->trans_id = trans_id;
	memcpy(param->remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
	param->passkey = passkey;
	return enqueue_signal_interface_req(req);

}

/** @brief Send the authorization input from the user to the SMP manager
 *
 * Function: iLE_send_authorization
 *			 SMP application uses this interface to send the authorization input from the user to the SMP manager
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device.
 * @param bdaddr_type - bluetooth address type for remote device.
 * @param authorization - authorization input from the user.
 * @param auth_level_min - Minimum authentication requirement for this pairing
 * @param key_size_min - Minimum key size for this pairing
 * @return Error code.
 */
INT8 iLE_send_authorization(trans_id_t trans_id, UINT8 *remote_bd_addr, UINT8 bdaddr_type, UINT8 authorization, UINT8 auth_level_min, UINT8 key_size_min)
{
	interface_req_elem_t *req;
	smpm_send_authorization_param_t * param;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if (!remote_bd_addr)
		return STATUS_ERR_INVALID_PARAM;
	req = get_interface_req_buffer(API_REQ_OPCODE_SEND_AUTHORIZATION, 0, sizeof(smpm_send_authorization_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (smpm_send_authorization_param_t*)req->parameter;
	param->trans_id = trans_id;
	memcpy(param->remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
	param->authorization = authorization;
	param->auth_level_min = auth_level_min;
	param->key_size_min = key_size_min;
	return enqueue_signal_interface_req(req);

}
/** @brief Register to the SMP manager for callbacks
 *
 * Function: iLE_smp_register
 *			 SMP application uses this interface to register to the SMP manager callbacks.
 *
 * @param app_handle - Handle of the application.
 * @param smp_cb	- SMP manger callback function.
 * @return Error code.
 */
INT8 iLE_smp_register(trans_id_t trans_id, smp_app_cb_t smp_cb)
{
	interface_req_elem_t *req;
	smpm_smp_register_param_t * param;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_SMP_REGISTER, 0, sizeof(smpm_smp_register_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (smpm_smp_register_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->smp_mgr_cb = smp_cb;
	return enqueue_signal_interface_req(req);

}

/** @brief Sets IO Capabilities of SMP
 *
 * Function: iLE_smp_set_io_capabilities
 *			 Application uses this interface to change the IO Capabilities of SMP Manager.
 *
 * @param trans_id - Unique identifier of the request.
 * @param io_capabilities - IO Capabilities to set, Valid values are as follows
 * 							SMP_DISPLAY_ONLY(0x00)
 *							SMP_DISPLAY_YN(0x01)
 *							SMP_KEYBOARD_ONLY(0x02)
 *							SMP_NO_INPUT_NO_OUTPUT(0x03) - Default
 *							SMP_KEYBOARD_DISPLAY(0x04)
 * @return Error code - Returns SUCCESS(0x00) if command is successful else returns the proper error code.
 */
INT8 iLE_smp_set_io_capabilities(trans_id_t trans_id, UINT8 io_capabilities)
{
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	return smp_set_io_capabilities(io_capabilities);
}

#endif /* SMP_FEATURE */

#if (SECURE_CONNECTION)
/** @brief Send the numeric comparison result input from the user to the SMP manager
 *
 * Function: iLE_smp_send_nc_result
 *			 SMP application uses this interface to send the numeric comparison result input from
 *			 the user to the SMP manager
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device.
 * @param bdaddr_type - bluetooth address type for remote device.
 * @param authorization - authorization input from the user.
 * @return Error code.
 */
INT8 iLE_smp_send_nc_result(trans_id_t trans_id, UINT8 *remote_bd_addr, UINT8 bdaddr_type, UINT8 authorization)
{
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if (!remote_bd_addr)
		return STATUS_ERR_INVALID_PARAM;
	interface_req_elem_t *req = get_interface_req_buffer(API_REQ_OPCODE_NC_RESULT, 0, sizeof(smpm_send_nc_result_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	smpm_send_nc_result_param_t * param = (smpm_send_nc_result_param_t*)req->parameter;
	param->trans_id = trans_id;
	memcpy(param->remote_bd_addr, remote_bd_addr, BD_ADDR_LEN);
	param->authorization = authorization;
	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}
#endif /* SECURE_CONNECTION */

/** @brief Check if controller supports central address resolution
 *
 * Function: iLE_is_controller_privacy_supported
 *			 This is meant to be used by the GATT-GAP service profile to determine if the controller
 *			 supports central address resolution. Since this profile is supposed to reside in the
 *			 controller for embedded deployments, no HCI command code is required for this. Instead,
 *			 this would be a direct function call, which would return synchronously with the value.
 *
 * @return TRUE if controller supports central address resolution, FALSE otherwise
 */
BOOLEAN iLE_is_controller_privacy_supported(trans_id_t trans_id)
{
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return FALSE;
	return (LL_PRIVACY_IS_SUPPORTED? TRUE : FALSE);
}

void rx_req_hci_evt_msg(UINT8* value, UINT8 value_len)
{
	rx_hci_msg_param_t* param ;

	interface_req_elem_t *req = get_interface_req_buffer(RX_REQ_OPCODE_HCI_MSG, 0, sizeof(rx_hci_msg_param_t) + value_len);
	if(req == NULL)
		return;
	param = (rx_hci_msg_param_t*)req->parameter;

	memcpy(param->value, value, value_len);
	param->value_len = value_len;

#if (RX_PROCESSING_IN_TIMER_THREAD == TRUE)
	enqueue_interface_req(req);
#else
	enqueue_signal_interface_req(req);
#endif
	return;
}

INT8 iLE_update_conn_params(trans_id_t trans_id, UINT8 conn_id, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout)
{
	pm_update_conn_params_t* param;
	interface_req_elem_t *req;

	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_GAP_CONN_PARAMS_UPDATE, conn_id, sizeof(pm_update_conn_params_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (pm_update_conn_params_t*)req->parameter;

	param->trans_id = trans_id;
	param->conn_idx = conn_id;
	param->interval_min = interval_min;
	param->interval_max = interval_max;
	param->conn_latency = conn_latency;
	param->sup_timeout = sup_timeout;
	return enqueue_signal_interface_req(req);

}

void timer_expire_evt_msg(osa_timeout_func_t cback, osa_timer_arg_t arg)
{
	create_timer_expire_req(cback, arg);
}

#if (TEST_CODE == TRUE)

#if (LE_PING_ENABLE==TRUE)
/** @brief Requests core stack to read authenticated payload timeout for an encrypted link
 *
 * Function: iLE_test_read_authenticated_payload_timeout
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - Connection id.
 * @return Error code.
 */
INT8 iLE_test_read_authenticated_payload_timeout(trans_id_t trans_id, UINT8 conn_id)
{
	cm_read_authpayload_timeout_t* param ;
	INT8 ret;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_TEST_READ_AUTHPAYLOAD_TIMEOUT, conn_id, sizeof(cm_read_authpayload_timeout_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (cm_read_authpayload_timeout_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to write authenticated payload timeout for an encrypted link
 *
 * Function: iLE_test_write_authenticated_payload_timeout
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param authpayload_timeout - Range: 10ms to 655350ms, Default: 30000ms
 *                                                default value will be used if given value is not in range (also honoring conn_interval and conn_latency).
 * @return Error code.
 */
INT8 iLE_test_write_authenticated_payload_timeout(trans_id_t trans_id, UINT8 conn_id, UINT16 authpayload_timeout_ms)
{
	cm_write_authpayload_timeout_t* param;
	INT8 ret;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_TEST_WRITE_AUTHPAYLOAD_TIMEOUT, conn_id, sizeof(cm_write_authpayload_timeout_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (cm_write_authpayload_timeout_t*)req->parameter;

	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->authpayload_timeout_ms = authpayload_timeout_ms;
	ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);

	return ret;
}

#endif //LE_PING_ENABLE

/** @brief Requests core stack to stop this device to be discoverable
 *
 * Function: iLE_enable_privacy
 *			 This function will enable privacy
 *
 * @param app_handle - Handle of the application.
 *        enable_privacy - Set true if privacy has to be enabled yes false.
 * @return Error code.
 */
INT8 iLE_test_enable_privacy(trans_id_t trans_id, UINT8 enable_privacy)
{
	cm_privacy_state_param_t* param;
	INT8 ret ;
	interface_req_elem_t *req;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_ENABLE_PRIVACY, 0, sizeof(cm_privacy_state_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (cm_privacy_state_param_t*)req->parameter;

	param->enable_privacy = enable_privacy;
	ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}
#endif

UINT8 iLE_get_bdaddr(trans_id_t trans_id, UINT8 *bdaddr)
{
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return 0;
	memcpy(bdaddr, g_local_adapter.bdaddr, BD_ADDR_LEN);
	return g_local_adapter.addr_type;
}

INT8 iLE_test_set_public_bdaddr(trans_id_t trans_id, UINT8* bdaddr)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	return hci_ble_set_bdaddr(bdaddr);
}

/** @brief Requests core stack to set data len for the specified connection
 *
 * Function: iLE_set_data_len
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - Connection id.
 * @param tx_octets - Range: 27bytes to 251bytes for 1Mbps controller support(default 27 bytes. Maximum value varies based on controller data rate)
 * @return Error code.
 */
INT8 iLE_set_data_len(trans_id_t trans_id, UINT8 conn_id, UINT16 tx_octets)
{
	interface_req_elem_t *req;
	cm_set_data_len_t* param;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if(!(g_local_adapter.ble_local_features[HCI_LE_FEATURE_DATA_PKT_LEN_EXTN_OFFSET] & HCI_LE_FEATURE_DATA_PKT_LEN_EXTN_MASK))
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
	req = get_interface_req_buffer(API_REQ_OPCODE_SET_DATA_LEN, conn_id, sizeof(cm_set_data_len_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (cm_set_data_len_t*)req->parameter;

	param->conn_id = conn_id;
	param->tx_octets = tx_octets;
	return enqueue_signal_interface_req(req);

}

INT8 iLE_send_hci_command(trans_id_t trans_id, UINT16 opcode, UINT8 buffer_len, UINT8* command_buffer)
{
	interface_req_elem_t *req;
	tx_hci_send_msg_param_t* param;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(TX_REQ_OPCODE_HCI_MSG, 0, sizeof(tx_hci_send_msg_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (tx_hci_send_msg_param_t*)req->parameter;

	param->opcode = opcode;
	param->buffer = alloc_queue_element(buffer_len, HCI_ALLOC);
	memcpy(param->buffer, command_buffer, buffer_len);
	param->buffer_len = buffer_len;

	return enqueue_signal_interface_req(req);

}
#if (TEST_CODE == TRUE)
	/* Needed for VSC HCI passthrough*/
INT8 iLE_send_vshci_command(trans_id_t trans_id, UINT8 buffer_len, UINT8* command_buffer)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	if (buffer_len == 0 || !command_buffer)
		return STATUS_ERR_INVALID_PARAM;
	interface_req_elem_t *req = get_interface_req_buffer(TX_REQ_OPCODE_VSHCI_MSG, 0, sizeof(tx_vshci_send_msg_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	tx_vshci_send_msg_param_t* param = (tx_vshci_send_msg_param_t*)req->parameter;

	param->buf = (UINT8*)alloc_queue_element(buffer_len, HCI_ALLOC);
	if(!param->buf)
	{
		dealloc_queue_element((void*) req);
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	memcpy(param->buf, command_buffer, buffer_len);

	INT8 ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}
#endif /*TEST_CODE == TRUE*/

void gap_cleanup_complete_cb()
{
	logi("");
	stack_running = FALSE;
	stack_interface_signal_req();

	iLE_stack_cleanup();
}

#if (L2CAP_COC == TRUE)
/** @brief Requests core stack to create an L2CAP connection oriented channel
 *
* Function: iLE_l2cap_coc_connect_req
*
* @param app_handle - Handle of the application.
* @param conn_id - connection id of remote device.
* @param psm - Protocol Service Multiplexer value of the protocol used on this CoC.
* @param mtu - Maximum transmission unit value that the local device can accept
* @param l2cap_coc_cbs - callback functions for L2CAP CoC
*
* @return Error code.
*/
INT8 iLE_l2cap_coc_connect_req(trans_id_t trans_id, UINT8 conn_id, UINT16 psm, UINT16 mtu, l2cap_coc_callbacks_t *l2cap_coc_cbs)
{
	interface_req_elem_t *req;
	l2cap_coc_api_conn_t * param;
	INT8 ret;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_L2CAP_COC_CREATE_CONNECTION, conn_id, sizeof(l2cap_coc_api_conn_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (l2cap_coc_api_conn_t*)req->parameter;

	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->psm = psm;
	param->mtu = mtu;
	param->l2cap_coc_cbs = l2cap_coc_cbs;
	ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;
}

/** @brief Requests core stack to register for an psm. An incoming CoC create is accepted if an App has registered for the psm.
 *
 * Function: iLE_l2cap_coc_register_cb_for_conn_req
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - connection id of remote device.
 * @param psm - Protocol Service Multiplexer registered by the app.
 * @param mtu - Maximum transmission unit value that the local device can accept
 * @param l2cap_coc_cbs - callback functions for L2CAP CoC
 * @parma auth_req - whether application needs any authorisation callbacks before a connection is made using this psm
 *
 * @return Error code.
 */
INT8 iLE_l2cap_coc_register(trans_id_t trans_id, UINT16 psm, UINT16 mtu, l2cap_coc_callbacks_t *l2cap_coc_cbs, BOOLEAN auth_req)
{
	interface_req_elem_t *req;
	l2cap_coc_register_coc_param_t *param;
	INT8 ret;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_L2CAP_COC_REGISTER, 0, sizeof(l2cap_coc_register_coc_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (l2cap_coc_register_coc_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->psm = psm;
	param->mtu = mtu;
	param->l2cap_coc_cbs = l2cap_coc_cbs;
	param->auth_req = auth_req;
	ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;

}

/** @brief Request to get maximum MTU size supported by stack for l2cap CoC.
 *
 * Function: iLE_l2cap_coc_get_max_mtu_size
 *
 * @param app_handle - Handle of the application.
 *
 * @return Maximum MTU size supported by stack for l2cap CoC.
 */
UINT16 iLE_l2cap_coc_get_max_mtu_size(trans_id_t trans_id)
{
	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	return 	l2cap_coc_get_max_mtu_size();
}

/** @brief Request to disconnect a L2CAP CoC channel
 *
 * Function: iLE_l2cap_coc_disconnect_req
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - connection id of remote device.
 * @param coc_handle - Handle of the L2CAP CoC to be disconnected
 *
 * @return Error code.
 */
INT8 iLE_l2cap_coc_disconnect_req(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle)
{
	interface_req_elem_t *req;
	l2cap_coc_api_disconnect_t * param;
	INT8 ret;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_L2CAP_COC_DISCONNECT, conn_id, sizeof(l2cap_coc_api_disconnect_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (l2cap_coc_api_disconnect_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->coc_handle = coc_handle;
	ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;

}

/** @brief Request to send data over an L2CAP CoC channel
 *
 * Function: iLE_l2cap_coc_send_data
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - connection id of remote device.
 * @param coc_handle - Handle of the L2CAP CoC
 * @param buffer - buffer to be send to remote device
 * @param buffer_len - length to the buffer to be send to remote device
 *
 * @return Error code.
 */
INT8 iLE_l2cap_coc_send_data(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle, UINT8* buffer, UINT16 buffer_len)
{
	interface_req_elem_t *req;
	l2cap_coc_api_data_t * param;
	INT8 ret;

	logi("");
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
			return STATUS_ERR_STACK_NOT_INIT;
	req = get_interface_req_buffer(API_REQ_OPCODE_L2CAP_COC_SEND_DATA, conn_id, sizeof(l2cap_coc_api_data_t) + buffer_len);
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (l2cap_coc_api_data_t*)req->parameter;
	param->trans_id = trans_id;
	param->conn_id = conn_id;
	param->coc_handle = coc_handle;
	memcpy(param->buffer, buffer, buffer_len);
	param->buffer_len = buffer_len;
	ret = enqueue_signal_interface_req(req);

	if (ret != STATUS_SUCCESS)
		dealloc_queue_element((void*)req);
	return ret;

}
#endif //L2CAP_COC

/* Storage related APIs */

INT8 iLE_storage_register(trans_id_t trans_id, storage_callbacks_t *storage_cb)
{
	interface_req_elem_t *req;
	smpm_storage_register_param_t *param;

	if(g_local_adapter.adapter_state == ADAPTER_STATE_DISABLED || g_local_adapter.adapter_state == ADAPTER_STATE_DISABLING)
		return STATUS_ERR_STACK_NOT_INIT;
	if(g_local_adapter.adapter_state != ADAPTER_STATE_ENABLING)
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;

	req = get_interface_req_buffer(API_REQ_OPCODE_STORAGE_REGISTER, 0, sizeof(smpm_storage_register_param_t));
	if(req == NULL)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	param = (smpm_storage_register_param_t*)req->parameter;
	param->trans_id = trans_id;
	param->storage_cb = storage_cb;
	return enqueue_signal_interface_req(req);

}
INT8 iLE_key_response(trans_id_t trans_id, UINT8 *bdaddr, UINT8 bdaddr_type, UINT8 key_type, void* key_value)
{
	UINT8 length;
	interface_req_elem_t *req;
	smpm_set_key_param_t *param;

	if(g_local_adapter.adapter_state == ADAPTER_STATE_DISABLED || g_local_adapter.adapter_state == ADAPTER_STATE_DISABLING)
		return STATUS_ERR_STACK_NOT_INIT;

	length = 0;
	if(key_value)
	{
		switch(key_type)
		{
			case LOCAL_LTK:
			case PEER_LTK:
				length = sizeof(enc_info_t);
				break;
			case LOCAL_IRK:
				length = sizeof(identity_info_t);
				break;
			case PEER_IRK:
				length = sizeof(resolving_list_entry_t);
				break;
			case LOCAL_CSRK:
			case PEER_CSRK:
				length = sizeof(signing_info_t);
				break;
			case SEC_INFO:
				length = sizeof(sec_info_t);
				break;
			default:
				logw("Unknown key type");
				return STATUS_ERR_INVALID_PARAM;
		}
	}
	req = get_interface_req_buffer(API_REQ_OPCODE_KEY_RESPONSE, 0, sizeof(smpm_set_key_param_t) + length);
	if(req == NULL)
				return STATUS_ERR_INSUFFICIENT_RESOURCES;
	param = (smpm_set_key_param_t*)req->parameter;
	param->trans_id = trans_id;
	memcpy(param->bdaddr, bdaddr, BD_ADDR_LEN);
	param->bdaddr_type = bdaddr_type;
	param->key_type = key_type;
	if(key_value)
	{
		param->is_valid = TRUE;
		memcpy(param->key_value, key_value, length);
	}
	return enqueue_signal_interface_req(req);

}

INT8 interface_handler()
{
	INT8 ret = STATUS_SUCCESS;
	timer_expire_elem_t* timer_req;
	interface_req_elem_t* req;
	UINT8 idx;

#if (TARGET_UEFI == TRUE)
	if(g_local_adapter.thread_busy == TRUE)
		return STATUS_SUCCESS;
	g_local_adapter.thread_busy = TRUE;
#endif

	while (stack_running == TRUE)
	{
#if (TARGET_THREADX_RW == TRUE)
		stack_ll_handler();
		stack_interface_handler();
#endif

		timer_req = dequeue(&g_local_adapter.timer_expire_q);
		if (timer_req)
		{
			if(timer_req->cback)
				timer_req->cback(timer_req->arg);
			dealloc_queue_element(timer_req);
			continue;
		}

		req = dequeue(&g_local_adapter.interface_req_q);
		if (!req)
		{
#if (THREADLESS_STACK == TRUE)
			break;
#else
			/* There is no req in the list. Wait for one */
			osa_semaphore_get(&msg_sem);
			continue;
#endif
		}
		if (req)
		{
			INT8 req_status = STATUS_SUCCESS;
			logd("+process req->req_opcode:%d", req->req_opcode);
			switch (req->req_opcode)
			{
			case API_REQ_OPCODE_REGISTER_APPLICATION:
			{
				pm_register_application_param_t* param =
						(pm_register_application_param_t*)(void*)req->parameter;
				pm_register_application(param->dev_cb, param->gatt_cb,
						param->register_application_cb);
			}
				break;
			case API_REQ_OPCODE_DEREGISTER_APPLICATION:
			{
				pm_deregister_application_param_t* param = (pm_deregister_application_param_t*)(void*)req->parameter;
				logd("API_REQ_OPCODE_DEREGISTER_APPLICATION: param->app_handle:%d", param->app_handle);
#if (GATT_SERVER_SUPPORTED == TRUE)
				sm_remove_app_all_services(param->app_handle);
#endif
				/* If this is the latest app running, we don't deregister it yet */
				/* Instead, we clean up the stack, give stack deinitialized callback to the app, and then deregister it */
				for (idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
				{
					if (idx == param->app_handle)
						continue;
					if (g_local_adapter.app_list[idx] != NULL )
						break;
				}
				logd("idx:%d", idx);
				if (idx == MAX_NUMBER_OF_APP)
				{
					dm_disable();
					iLE_stack_cleanup();
				}
				else
					pm_deregister_application(param->app_handle);
			}
				break;
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
			case API_REQ_OPCODE_SET_ADVERTISEMENT_DATA:
			{
				dm_adv_scanresp_data_param_t* param =
						(dm_adv_scanresp_data_param_t*)(void*)req->parameter;
				dm_add_adv_data(param->length, param->type, param->data);
				logd("API_REQ_OPCODE_SET_ADVERTISEMENT_DATA param->data:%p", param->data);
			}
				break;
			case API_REQ_OPCODE_REMOVE_ADVERTISEMENT_DATA:
			{
				dm_adv_scanresp_data_param_t* param =
						(dm_adv_scanresp_data_param_t*)(void*)req->parameter;
				dm_remove_adv_data(param->length, param->type, param->data);
				logd("API_REQ_OPCODE_REMOVE_ADVERTISEMENT_DATA param->data:%p", param->data);
			}
				break;
			case API_REQ_OPCODE_SET_SCAN_RESPONSE_DATA:
			{
				dm_adv_scanresp_data_param_t* param =
						(dm_adv_scanresp_data_param_t*)(void*)req->parameter;
				dm_add_scanresp_data(param->length, param->type, param->data);
				logd("API_REQ_OPCODE_SET_SCAN_RESPONSE_DATA param->data:%p", param->data);
			}
				break;
			case API_REQ_OPCODE_REMOVE_SCAN_RESPONSE_DATA:
			{
				dm_adv_scanresp_data_param_t* param =
						(dm_adv_scanresp_data_param_t*)(void*)req->parameter;
				dm_remove_scanresp_data(param->length, param->type, param->data);
				logd("API_REQ_OPCODE_REMOVE_SCAN_RESPONSE_DATA param->data:%p", param->data);
			}
				break;
			case API_REQ_OPCODE_START_DISCOVERABLE:
			case API_REQ_OPCODE_STOP_DISCOVERABLE:
				req_status = gap_req_handler(req);
				break;

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
			case API_REQ_OPCODE_SET_LOCAL_DEVICE_NAME:
			{
				dm_set_local_device_name_param_t* param =
						(dm_set_local_device_name_param_t*)(void*)req->parameter;
				dm_set_local_device_name(param->name, param->len);
			}
				break;
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
			case API_REQ_OPCODE_START_SCAN:
			case API_REQ_OPCODE_STOP_SCAN:
			case API_REQ_OPCODE_CONNECT:
			case API_REQ_OPCODE_AUTO_CONNECT:
			case API_REQ_OPCODE_ADD_TO_WHITELIST:
			case API_REQ_OPCODE_REMOVE_FROM_WHITELIST:
			case API_REQ_OPCODE_CLEAR_WHITELIST:
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
#if (CONTROLLER_PRIVACY)
			case API_REQ_OPCODE_ADD_TO_RESOLVINGLIST:
			case API_REQ_OPCODE_REMOVE_FROM_RESOLVINGLIST:
			case API_REQ_OPCODE_CLEAR_RESOLVINGLIST:
#endif /* CONTROLLER_PRIVACY */
			case API_REQ_OPCODE_DISCONNECT:
			case API_REQ_OPCODE_GAP_CONN_PARAMS_UPDATE:
#if (TEST_CODE == TRUE && LE_PING_ENABLE == TRUE)
			case API_REQ_OPCODE_TEST_READ_AUTHPAYLOAD_TIMEOUT:
			case API_REQ_OPCODE_TEST_WRITE_AUTHPAYLOAD_TIMEOUT:
#endif //TEST_CODE && LE_PING_ENABLE
			case API_REQ_OPCODE_SET_DATA_LEN:
				req_status = gap_req_handler(req);
				break;
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
#if (SMP_FEATURE)
			case API_REQ_OPCODE_CREATE_BOND:
			case API_REQ_OPCODE_REMOVE_BOND:
				req_status = smpm_req_handler(req);
				break;
#if (TEST_CODE == TRUE)
			case API_REQ_OPCODE_SIGN_DATA:
				req_status = smpm_req_handler(req);
				break;
#endif /*TEST_CODE == TRUE*/
#endif /* SMP_FEATURE */
#if (GATT_SERVER_SUPPORTED == TRUE)
			case API_REQ_OPCODE_ADD_SERVICE:
			case API_REQ_OPCODE_ADD_INCLUDED_SERVICE:
			case API_REQ_OPCODE_ADD_CHARACTERISTIC:
			case API_REQ_OPCODE_ADD_DESCRIPTOR:
			case API_REQ_OPCODE_START_SERVICE:
			case API_REQ_OPCODE_REMOVE_SERVICE:
				req_status = sm_service_add_req_handler(req);
				break;
			case API_REQ_OPCODE_SEND_ATTRIBUTE_READ_RESPONSE:
			case API_REQ_OPCODE_SEND_ATTRIBUTE_WRITE_RESPONSE:
			case API_REQ_OPCODE_SEND_NOTIFICATION:
			case API_REQ_OPCODE_SET_SERVICE_CHANGE_CONFIG:
				req_status = sm_req_handler(req);
				break;
#endif
#if (GATT_CLIENT_SUPPORTED == TRUE)
			case API_REQ_OPCODE_SET_ATT_MTU_SIZE:
			case API_REQ_OPCODE_DISCOVER_PRIMARY_SERVICE:
			case API_REQ_OPCODE_DISCOVER_INCLUDED_SERVICE:
			case API_REQ_OPCODE_DISCOVER_CHARACTERISTIC:
			case API_REQ_OPCODE_DISCOVER_DESCRIPTOR:
			case API_REQ_OPCODE_READ_ATTRIBUTE_VALUE:
			case API_REQ_OPCODE_WRITE_ATTRIBUTE_VALUE:
				req_status = pm_req_handler(req);
				break;
			case API_REQ_OPCODE_REGISTER_NOTIFICATION:
			{
				pm_register_notification_param_t* param = (pm_register_notification_param_t*)(void*)req->parameter;
				req_status = pm_register_notification(param->trans_id, param->conn_id, param->att_id, param->is_register);
			}
				break;
#endif
			case API_REQ_OPCODE_SEND_PASSKEY:
			{
				smpm_send_passkey_param_t* param =
						(smpm_send_passkey_param_t *)(void*)req->parameter;
				smpm_send_passkey(param->trans_id, param->remote_bd_addr, param->passkey);
			}
				break;
			case API_REQ_OPCODE_SEND_AUTHORIZATION:
			{
				smpm_send_authorization_param_t* param =
							(smpm_send_authorization_param_t *)(void*)req->parameter;
				smpm_send_authorization(param->trans_id, param->remote_bd_addr, param->authorization, param->auth_level_min, param->key_size_min);
			}
				break;
			case API_REQ_OPCODE_NC_RESULT:
			{
#if (SECURE_CONNECTION)
				smpm_send_nc_result_param_t* param =
							(smpm_send_nc_result_param_t *)(void*)req->parameter;
				smpm_send_nc_result(param->trans_id, param->remote_bd_addr, param->authorization);
#endif /* SECURE_CONNECTION */
				break;
			}
			case API_REQ_OPCODE_SMP_REGISTER:
			{
				smpm_smp_register_param_t* param =
						(smpm_smp_register_param_t *)(void*)req->parameter;
				smpm_smp_register(param->trans_id, param->smp_mgr_cb);
			}
				break;
			case RX_REQ_OPCODE_HCI_MSG:
			{
				rx_hci_msg_param_t* param = (rx_hci_msg_param_t*)(void*)req->parameter;
				req_status = hci_recv_buffer(param->value, param->value_len);

#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
				UINT16 Opcode=0;
				memcpy(&Opcode, (UINT8 *)(param->value)+4,2);
				log_time_stamp_with_opcode(TIME_HCI_EVT_RECVD,Opcode);
#endif
			}
				break;
#if (TEST_CODE == TRUE)
			case API_REQ_OPCODE_ENABLE_PRIVACY:
#if (HOST_PRIVACY)
				req_status = gap_req_handler(req);
#endif /* HOST_PRIVACY */
			break;
#endif /* TEST_CODE == TRUE */
#if (L2CAP_COC == TRUE)
			case API_REQ_OPCODE_L2CAP_COC_CREATE_CONNECTION:
			{
				l2cap_coc_api_conn_t* param = (l2cap_coc_api_conn_t *)(void*)req->parameter;
#if (PARANOID_STACK == TRUE)
				if (param->mtu <= 0)
				{
					req_status = STATUS_ERR_INVALID_PARAM;
					break;
				}
				if (!g_local_adapter.connected_device[param->conn_id])
				{
					loge("Invalid connection id");
					req_status = STATUS_ERR_INAVALID_CONNENCTION;
					break;
				}
				UINT8 app_handle = get_appid_from_transid(param->trans_id);
				app_data_t* app_data = g_local_adapter.app_list[app_handle];
				if (!app_data)
				{
					req_status = STATUS_ERR_INVALID_APP_HANDLE;
					break;
				}
				if(!is_conn_used(app_data, g_local_adapter.connected_device[param->conn_id]))
				{
					logd("(!is_conn_used(app_data, device))");
					req_status = STATUS_ERR_INVALID_APP_HANDLE;
					break;
				}
#endif
				l2cap_coc_connect_req(param->trans_id, param->conn_id, param->psm, param->mtu, param->l2cap_coc_cbs);
			}
				break;
			case API_REQ_OPCODE_L2CAP_COC_REGISTER:
			{
				l2cap_coc_register_coc_param_t* param = (l2cap_coc_register_coc_param_t *)(void*)req->parameter;
#if (PARANOID_STACK == TRUE)
				if (param->mtu <= 0 )
				{
					req_status = STATUS_ERR_INVALID_PARAM;
					break;
				}
#endif
				l2cap_coc_register_cb_for_conn_req(param->trans_id, param->psm, param->mtu, param->auth_req, param->l2cap_coc_cbs);
			}
				break;
			case API_REQ_OPCODE_L2CAP_COC_DISCONNECT:
			{
				l2cap_coc_api_disconnect_t* param = (l2cap_coc_api_disconnect_t *)(void*)req->parameter;
#if (PARANOID_STACK == TRUE)
				if (param->trans_id <= 0)
				{
					req_status = STATUS_ERR_INVALID_PARAM;
					break;
				}
				if (!g_local_adapter.connected_device[param->conn_id])
				{
					loge("Invalid connection id");
					req_status = STATUS_ERR_INAVALID_CONNENCTION;
					break;
				}
				UINT8 app_handle = get_appid_from_transid(param->trans_id);
				app_data_t* app_data = g_local_adapter.app_list[app_handle];
				if (!app_data)
				{
					req_status = STATUS_ERR_INVALID_APP_HANDLE;
					break;
				}
				if(!is_conn_used(app_data, g_local_adapter.connected_device[param->conn_id]))
				{
					logd("(!is_conn_used(app_data, device))");
					req_status = STATUS_ERR_INVALID_APP_HANDLE;
					break;
				}
#endif
				connected_device_t *device = g_local_adapter.connected_device[param->conn_id];
				l2cap_coc_disconnect_req(param->trans_id, device, param->coc_handle);
			}
				break;
			case API_REQ_OPCODE_L2CAP_COC_SEND_DATA:
			{
				l2cap_coc_api_data_t* param = (l2cap_coc_api_data_t *)(void*)req->parameter;
#if (PARANOID_STACK == TRUE)
				if (!g_local_adapter.connected_device[param->conn_id])
				{
					loge("Invalid connection id");
					req_status = STATUS_ERR_INAVALID_CONNENCTION;
					break;
				}
				UINT8 app_handle = get_appid_from_transid(param->trans_id);
				app_data_t* app_data = g_local_adapter.app_list[app_handle];
				if (!app_data)
				{
					req_status = STATUS_ERR_INVALID_APP_HANDLE;
					break;
				}
				if(!is_conn_used(app_data, g_local_adapter.connected_device[param->conn_id]))
				{
					logd("(!is_conn_used(app_data, device))");
					req_status = STATUS_ERR_INVALID_APP_HANDLE;
					break;
				}
#endif
				connected_device_t *device = g_local_adapter.connected_device[param->conn_id];
				l2cap_coc_send_data(device, param->coc_handle, param->buffer, param->buffer_len);
			}
				break;
#endif // L2CAP_COC
			case TX_REQ_OPCODE_HCI_MSG:
			{
				tx_hci_send_msg_param_t *param = (tx_hci_send_msg_param_t*)(void*)req->parameter;
				if ((req_status = hci_send_cmd(param->opcode, param->buffer, param->buffer_len - UART_HDR_SIZE - HCI_CMD_PREAMBLE_SIZE)) == STATUS_ERR_BUSY)
				{
					ret = enqueue(&g_local_adapter.interface_req_q, (void*) req);

					if (ret == STATUS_SUCCESS)
						break;
				}
			}
				break;
#if (TEST_CODE == TRUE)
	/* Needed for VSC HCI passthrough*/
			case TX_REQ_OPCODE_VSHCI_MSG:
			{
				UINT16 opcode;
				UINT8 len;
				tx_vshci_send_msg_param_t *param = (tx_vshci_send_msg_param_t*)(void*)req->parameter;
				UINT8 *p = param->buf;
				JUMP_UART_HEADER(p);
				STREAM_TO_UINT16(opcode, p);
				STREAM_TO_UINT8(len, p);
				if ((req_status = hci_send_cmd(opcode, param->buf, len)) == STATUS_ERR_BUSY)
				{
					ret = enqueue(&g_local_adapter.interface_req_q, (void*) req);

					if (ret == STATUS_SUCCESS)
						break;
				}
			}
				break;
#endif /*TEST_CODE == TRUE*/
			case API_REQ_OPCODE_STORAGE_REGISTER:
			{
				smpm_storage_register_param_t* param =
					 (smpm_storage_register_param_t *)(void*)req->parameter;
				smpm_storage_register(param->trans_id, param->storage_cb);
			}
				break;
			 case API_REQ_OPCODE_KEY_RESPONSE:
			 {
				 smpm_set_key_param_t* param =
						 (smpm_set_key_param_t *)(void*)req->parameter;
				 smpm_key_response(param->trans_id, param->bdaddr, param->bdaddr_type, param->key_type, param->is_valid, param->key_value);
			 }
			 	 break;

			}
			if (req_status != STATUS_ERR_BUSY && req_status != STATUS_PROCESS_ONGOING)
			{
				logd("-process req->req_opcode:%d", req->req_opcode);
				dealloc_queue_element(req);
			}
			else
			{
				logd("Req resubmitted / being processed by lower layers.");
			}
		}
	}
#if (TARGET_UEFI == TRUE)
	g_local_adapter.thread_busy = FALSE;
#endif
	return ret;
}

#if (THREADLESS_STACK == FALSE)
osa_thread_ret_t stack_main_thread_handler(osa_thread_arg_t arg)
{
	if (init_layers() == STATUS_SUCCESS)
		interface_handler();

	osa_thread_exit(NULL);
}
#endif

#if (TARGET_UEFI == TRUE)
void fw_dw_finish(BOOLEAN status)
{
	logd("firmware download done. Status = %d", status);
	logd("Stack HCI init starting");
	dm_enable();
}
#endif
