/** @file
  ATP Production application implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <stdlib.h>
#include "app_interface.h"
#include "profile_adapt.h"

#define MODULE_DBG_LVL HRP_APP_DBG_LVL
#include "log.h"

#if (ATP_AUTO_TEST_MODE == TRUE)

#include "atp_production_app.h"
#include "rwble.h"

RETENTION_SECTION_START
atp_prod_data_t atp_prod_data;
RETENTION_SECTION_END

osa_thread_ret_t atp_app_main_thread(osa_thread_arg_t arg);
static void atp_stack_initialized_cb(void);

static inline void signal_req()
{
    osa_semaphore_put(&atp_prod_data.msg_sem);
}


/******************************************************
 * Callback functions
 ******************************************************/
static void atp_register_application_cb(UINT8 app_handle, BOOLEAN result)
{
    trans_id_t new_trans_id = 0;

    logi("");
    if (result == TRUE)
    {
        atp_prod_data.app_handle = app_handle;
        logi("app_handle:%d", app_handle);
    }

    add_appid_to_trans_id(&new_trans_id, atp_prod_data.app_handle);
    iLE_storage_register(new_trans_id, NULL);
    osa_semaphore_put(&atp_prod_data.thread_sem);
}

static void atp_on_connected_cb(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 status, BOOLEAN from_remote,
								UINT8 *id_bdaddr, UINT8 id_bdaddr_type)
{
    if (memcmp(remote_bd_addr, atp_prod_data.remote_bd_addr, BD_ADDR_LEN)
            == 0 && status == 0)
    {
        atp_prod_data.is_atp_read_req_pending = FALSE;
        atp_prod_data.conn_id = conn_id;
        atp_req_elem_t *res_code = (atp_req_elem_t*) alloc_queue_element(sizeof(atp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
        if (res_code == NULL )
            return;
#endif
        res_code->opcode = ATP_RES_DEVICE_CONNECTED;
        enqueue(&atp_prod_data.atp_res_q, res_code);
        signal_req();
    }
}

static void atp_on_disconnected_cb(trans_id_t trans_id, UINT8 conn_id, UINT8 result)
{
    logi("");
    atp_prod_data.atp_is_connected = FALSE;
    atp_prod_data.is_atp_read_req_pending = FALSE;
    memset(atp_prod_data.remote_bd_addr, 0, BD_ADDR_LEN);

    atp_stack_initialized_cb();

    if (atp_prod_data.atp_app_closing)
    {
        iLE_deregister_application(atp_prod_data.app_handle);
        cleanup_q(&atp_prod_data.atp_res_q);
        atp_prod_data.atp_app_running = FALSE;
        signal_req();
        osa_semaphore_get(&atp_prod_data.thread_sem);
        osa_semaphore_delete(&atp_prod_data.thread_sem);
        osa_thread_join(ATP_THREAD, NULL);
    }
}

static void atp_scan_result_cb(trans_id_t trans_id, discovered_device_t *device)
{
    char bdaddr_str[BD_ADDR_STR_LEN];
    BDADDR_TO_STRING(bdaddr_str, device->bdaddr);
    logi("Found Device %s %s", bdaddr_str, device->localname);

    memcpy(&atp_prod_data.discovered_list[atp_prod_data.num_discovered_devices], device, sizeof(discovered_device_t));
    if (device->adv_data && device->adv_data_len)
    {
        atp_prod_data.discovered_list[atp_prod_data.num_discovered_devices].adv_data = (UINT8*) app_alloc(device->adv_data_len);
#if (PARANOID_STACK == TRUE)
        if (!atp_prod_data.discovered_list[atp_prod_data.num_discovered_devices].adv_data)
            return;
#endif
        memcpy(atp_prod_data.discovered_list[atp_prod_data.num_discovered_devices].adv_data, device->adv_data, device->adv_data_len);
    }
    atp_prod_data.num_discovered_devices++;
}

static void atp_scan_completed_cb(trans_id_t trans_id)
{
    atp_req_elem_t *res_code = (atp_req_elem_t*) alloc_queue_element(sizeof(atp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
    if (res_code == NULL )
        return;
#endif
    res_code->opcode = ATP_RES_SCAN_COMPLETED;
    enqueue(&atp_prod_data.atp_res_q, res_code);
    signal_req();
}

static void atp_stack_initialized_cb()
{
    logi("");
    atp_req_elem_t *msg = (atp_req_elem_t *)alloc_queue_element(sizeof(atp_req_elem_t), APP_ALLOC);
#if (PARANOID_STACK == TRUE)
    if (!msg)
        return;
#endif
    msg->opcode = ATP_BT_CORE_STACK_INIT;
    msg->param = NULL;
    enqueue(&atp_prod_data.atp_res_q, msg);
    signal_req();
}


static gatt_callbacks_t atp_gatt_cb =
{
    .iLE_on_primary_service_discovered_cb = NULL,
    .iLE_on_characteristic_discovered_cb = NULL,
    .iLE_on_descriptor_discovered_cb = NULL,
    .iLE_on_attribute_read_cb = NULL,
    .iLE_on_notification_cb = NULL,
};

static device_control_callbacks_t atp_dev_cb =
{
    .iLE_stack_initialized_cb   = atp_stack_initialized_cb,
    .iLE_scan_result_cb = atp_scan_result_cb,
    .iLE_scan_completed_cb = atp_scan_completed_cb,
    .iLE_on_connected_cb = atp_on_connected_cb,
    .iLE_on_disconnected_cb = atp_on_disconnected_cb
};



void atp_start_discovery (void)
{
    UINT8 idx;
    for (idx = 0; idx < atp_prod_data.num_discovered_devices; idx++)
        app_dealloc(atp_prod_data.discovered_list[idx].adv_data);
    atp_prod_data.num_discovered_devices = 0;
    trans_id_t new_trans_id = 0;
    add_appid_to_trans_id(&new_trans_id, atp_prod_data.app_handle);

    iLE_start_scan(new_trans_id, ATP_SCAN_TIMEOUT_SEC, TRUE, FALSE, FALSE, FALSE);
}

void atp_start_connect_usecase (void)
{
    UINT8 idx = 0;
    char bdaddr_str[BD_ADDR_STR_LEN];
    UINT8 useAddrIndex = 0;

    if (!atp_prod_data.num_discovered_devices)
    {
        loge("First do atp_start_discovery operation.");
        atp_stack_initialized_cb();
        return;
    }
    for (idx = 0; idx < atp_prod_data.num_discovered_devices; idx++)
    {
        // Search for expected device, find index
        if (atp_prod_data.discovered_list[idx].bdaddr[0] == atp_ble_config.bd_addr.addr[5] &&
            atp_prod_data.discovered_list[idx].bdaddr[1] == atp_ble_config.bd_addr.addr[4] &&
            atp_prod_data.discovered_list[idx].bdaddr[2] == atp_ble_config.bd_addr.addr[3] &&
            atp_prod_data.discovered_list[idx].bdaddr[3] == atp_ble_config.bd_addr.addr[2] &&
            atp_prod_data.discovered_list[idx].bdaddr[4] == atp_ble_config.bd_addr.addr[1])
        {
            useAddrIndex = idx;

            BDADDR_TO_STRING(bdaddr_str, atp_prod_data.discovered_list[idx].bdaddr);
            logln("Device %d> %s - %s", idx, bdaddr_str, atp_prod_data.discovered_list[idx].localname);
            break;
        }
    }

    trans_id_t new_trans_id = 0;
    add_appid_to_trans_id(&new_trans_id, atp_prod_data.app_handle);

    if (idx < atp_prod_data.num_discovered_devices)
    {
        memcpy(atp_prod_data.remote_bd_addr, atp_prod_data.discovered_list[useAddrIndex].bdaddr, BD_ADDR_LEN);
        iLE_connect(new_trans_id, atp_prod_data.discovered_list[useAddrIndex].bdaddr, atp_prod_data.discovered_list[useAddrIndex].addr_type);
    }
}

static BOOLEAN atp_set_adv_data()
{
    logi("");
    trans_id_t new_trans_id = 0;
    add_appid_to_trans_id(&new_trans_id, atp_prod_data.app_handle);
    if (!iLE_set_local_device_name(new_trans_id, sizeof(DEVICE_NAME), (UINT8*) DEVICE_NAME))
        return FALSE;

    return TRUE;
}


/**
 * Stops the use case by only disconnecting the remote device.
 */
void atp_stop_use_case (UINT8 *bdaddr)
{
    trans_id_t new_trans_id = 0;
    add_appid_to_trans_id(&new_trans_id, atp_prod_data.app_handle);
    if (atp_prod_data.atp_is_connected == FALSE)
        atp_on_disconnected_cb(new_trans_id, atp_prod_data.conn_id, 0x00);
    else
        iLE_disconnect(new_trans_id, atp_prod_data.conn_id);
}


osa_thread_ret_t atp_app_main_thread(osa_thread_arg_t arg)
{
    osa_semaphore_create(&atp_prod_data.thread_sem, 0);
    if (atp_prod_data.atp_app_running == FALSE)
        osa_semaphore_get(&atp_prod_data.thread_sem);

    osa_semaphore_create(&atp_prod_data.msg_sem, 0);
    trans_id_t new_trans_id = 0;
    add_appid_to_trans_id(&new_trans_id, atp_prod_data.app_handle);

    while (atp_prod_data.atp_app_running == TRUE)
    {
        atp_req_elem_t* res_elem = (atp_req_elem_t*) dequeue(
                &atp_prod_data.atp_res_q);
        if (res_elem == NULL )
        {
            osa_semaphore_get(&atp_prod_data.msg_sem);
            continue;
        }
        UINT8 opcode = res_elem->opcode;
        switch (opcode)
        {

            case ATP_BT_CORE_STACK_INIT:
            {
#if (ATP_ADV_DUT || ATP_ADV_1SEC_DUT)
                logi("ATP ADV STARTED");
                atp_set_adv_data();
                iLE_start_discoverable(new_trans_id, 0, GAP_ADV_TYPE_CONNECTABLE_UNDIRECTED, GAP_ADV_FLAGS_LE_GENERAL_DISCOVERABLE, NULL, 0, FALSE, FALSE);
#endif
#if (ATP_SCAN_CONNECT_DUT)
                atp_start_discovery();
#endif
            }
                break;
            case ATP_RES_SCAN_COMPLETED:
            {
                logd("ATP_RES_SCAN_COMPLETED");
                atp_start_connect_usecase();
            }
                break;
            case ATP_RES_DEVICE_CONNECTED:
            {
                logd("HRP_RES_DEVICE_CONNECTED");
                atp_prod_data.atp_is_connected = TRUE;
                iLE_stop_discoverable(new_trans_id);
            }
                break;
            default:
                break;
        }
        dealloc_queue_element(res_elem);
    }
    osa_semaphore_delete(&atp_prod_data.msg_sem);
    osa_semaphore_put(&atp_prod_data.thread_sem);
}

void atp_app_init()
{
    /* Register ATP application. */
    iLE_register_application(&atp_dev_cb, &atp_gatt_cb, "atp_production", NULL, atp_register_application_cb);
    init_q(&atp_prod_data.atp_res_q);
    atp_prod_data.atp_app_running = TRUE;
    atp_prod_data.atp_app_closing = FALSE;
    atp_prod_data.atp_is_connected = FALSE;
}

void atp_app_cleanup()
{
    logi("");
    UINT8 idx;
    trans_id_t new_trans_id = 0;
    add_appid_to_trans_id(&new_trans_id, atp_prod_data.app_handle);
    for (idx = 0; idx < atp_prod_data.num_discovered_devices; idx++)
        app_dealloc(atp_prod_data.discovered_list[idx].adv_data);
    atp_prod_data.num_discovered_devices = 0;
    atp_prod_data.atp_app_closing = TRUE;
    if (atp_prod_data.atp_is_connected == FALSE)
        atp_on_disconnected_cb(new_trans_id, atp_prod_data.conn_id, 0x00);
    else
        iLE_disconnect(new_trans_id, atp_prod_data.conn_id);
}

#endif
