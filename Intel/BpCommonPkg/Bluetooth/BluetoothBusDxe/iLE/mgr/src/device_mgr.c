/** @file
  Device manager implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "hci_host.h"
#include "gap.h"
#include "utils.h"
#include "device_mgr.h"
#include "app_interface.h"

#if (TARGET_UEFI != TRUE)
/* These libraries are not available on UEFI platform */
#include <string.h>
#endif

#if (TARGET_UEFI == TRUE)
#include <tl.h>
#endif

#define MODULE_DBG_LVL DEVICE_MGR_DBG_LVL
#include "log.h"

#define MANUF_STATE_NONE 0
#define MANUF_STATE_ON   1
#define MANUF_STATE_OFF  2

UINT8 manuf_state;

#if (TARGET_ANDROID == TRUE)
osa_semaphore_t android_hal_init_sem;
#endif

static UINT8 get_name_length(UINT8* name)
{
	UINT8 idx;

	for (idx = 0; idx < MAX_LOCAL_NAME_LEN; idx++)
		if (!name[idx])
			return idx + 1;

	return 0;
}

void read_bd_addr_cmpl(UINT8* evt, UINT16 len)
{
	char bdaddr_str[BD_ADDR_STR_LEN];
	if (g_local_adapter.adapter_state == ADAPTER_STATE_ENABLED)
		return;

	//FIXME: Restructure the code here without altering the init sequence
#if (BLE_USE_FWINFO_FUNC_CALL == FALSE)
	STREAM_TO_BDADDR(g_local_adapter.bdaddr, evt);
#endif

	BDADDR_TO_STRING(bdaddr_str, g_local_adapter.bdaddr);
	memcpy(g_local_adapter.static_bdaddr, g_local_adapter.bdaddr, BD_ADDR_LEN);
	logd("BD address = %s", bdaddr_str);

#if (CONTROLLER_PRIVACY)
	if (LL_PRIVACY_IS_SUPPORTED)
		g_local_adapter.addr_type = GAP_ADDRESS_TYPE_RPA_OR_PUBLIC;
	else
#endif /* CONTROLLER_PRIVACY */
	g_local_adapter.addr_type = GAP_ADDRESS_TYPE_PUBLIC;

	dm_set_local_device_name(NULL, 0);

	/********** All layers whose init depends on controller features go here **********/

#if (SMP_FEATURE)
	smp_mgr_init();
#else
	do_app_init();
#endif /* SMP_FEATURE */

}

void do_app_init()
{
	/* Bluetooth is enabled. Lets start the profiles. */
#if (GAP_GATT_SRV_APP == TRUE)
	gap_gatt_service_init(NULL);
#endif

#if (HRP_APP == TRUE)
	hrp_init();
#endif

#if ((TEST_APP == TRUE) && (TARGET_ANDROID == FALSE))
	test_app_init();
#endif

#if (A4WP_APP == TRUE)
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_A4WP_PROFILE_INIT_STARTED);
#endif
	a4wp_init(NULL);
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_A4WP_PROFILE_INIT_COMPLETED);
#endif
#endif

#if (FMP_APP == TRUE)
	fmp_init(NULL);
#endif

#if (FMP_SRV_APP == TRUE)
	fmp_srv_init(NULL);
#endif

#if (SMP_APP == TRUE)
	smp_app_init(NULL);
#endif

#if (L2CAP_COC_TEST_APP == TRUE)
	l2cap_coc_test_app_init();
	test_app1_init();
#endif

#if (HOGP_APP == TRUE)
	hogp_init();
#endif

#if (UEFI_APP == TRUE)
	uefi_app_init();
#endif

#if (ATP_AUTO_TEST_MODE == TRUE)
	atp_app_init();
#endif

#if (HCI2ILE_ADAPT_APP == TRUE)
	adapt_app_init();
#endif

#if (TARGET_ANDROID == TRUE)
	osa_semaphore_put(&android_hal_init_sem);
#endif
}

void stack_init_completed(INT8 status)
{
	UINT8 idx;

	/* Enable host privacy only if controller privacy is not supported */
#if (PRIVACY_FEATURE)
	gap_enable_host_privacy(TRUE);
#endif /*PRIVACY_FEATURE*/

	g_local_adapter.adapter_state = ADAPTER_STATE_ENABLED;
	for (idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
		if (g_local_adapter.app_list[idx] && g_local_adapter.app_list[idx]->app_device_control_cb && g_local_adapter.app_list[idx]->app_device_control_cb->iLE_stack_initialized_cb)
			g_local_adapter.app_list[idx]->app_device_control_cb->iLE_stack_initialized_cb(TRUE);
}

void le_write_def_data_len_cmpl()
{
	logi("");
	/* If LL privacy is supported, BD address will be read after setting RPA timeout */
#if(PRIVACY_FEATURE)
	if (!LL_PRIVACY_IS_SUPPORTED)
#endif
		hci_read_bd_addr();
}

void le_read_max_data_len_cmpl(UINT16 opcode, UINT8 status, UINT8* evt, UINT8 len)
{
	logi("");
	if(status != STATUS_SUCCESS)
	{
		logd("Error in reading max DLE in CT");
		return;
	}
	STREAM_TO_UINT16(g_local_adapter.gap_data.max_tx_octets, evt);
	STREAM_TO_UINT16(g_local_adapter.gap_data.max_tx_time, evt);
	logd("le_read_max_data_len_cmpl max_tx_octets=%x, max_tx_time=%x", g_local_adapter.gap_data.max_tx_octets, g_local_adapter.gap_data.max_tx_time);
	logd("send hci_read_bdaddr");

	hci_read_bd_addr();
}

void le_read_supported_feat_cmpl(UINT8* evt, UINT16 len)
{
	BOOLEAN special_feat_supp = FALSE;
	memcpy(g_local_adapter.ble_local_features, evt, 8);

#if (SMP_FORCE_DISABLE_HOST_DLE == TRUE)
	g_local_adapter.ble_local_features[HCI_LE_FEATURE_DATA_PKT_LEN_EXTN_OFFSET] &= (~HCI_LE_FEATURE_DATA_PKT_LEN_EXTN_MASK);
#endif
	if (g_local_adapter.ble_local_features[HCI_LE_FEATURE_DATA_PKT_LEN_EXTN_OFFSET] & HCI_LE_FEATURE_DATA_PKT_LEN_EXTN_MASK)
	{
		hci_ble_read_max_data_len();
		special_feat_supp = TRUE;
	}

#if (CONTROLLER_PRIVACY == FALSE)
	/* If controller privacy is not enabled, mask the feature from the local_features*/
	g_local_adapter.ble_local_features[HCI_LE_FEATURE_LL_PRIVACY_OFFSET] &= (~HCI_LE_FEATURE_LL_PRIVACY_MASK);
#endif
#if (CONTROLLER_PRIVACY)
	if (LL_PRIVACY_IS_SUPPORTED)
	{
		hci_ble_read_resolving_list_size();
		special_feat_supp = TRUE;
	}
#endif

	if (!special_feat_supp)
		hci_read_bd_addr();
}

void read_buf_size_cmpl(UINT8* evt, UINT16 len)
{
	STREAM_TO_UINT16(g_local_adapter.buffer_size, evt);
	JUMP_CUSTOM_LEN(evt, 1); /* Jump sco pkt len param*/
	STREAM_TO_UINT8(g_local_adapter.num_of_buffer, evt);
	g_local_adapter.data_window = g_local_adapter.num_of_buffer;
	logd("data_window:%d", g_local_adapter.data_window);
	logd("send hci_ble_read_local_feat");
	hci_ble_read_local_feat();
}

void le_read_white_list_size_cmpl(UINT8* evt, UINT16 len)
{
	STREAM_TO_UINT8(g_local_adapter.whitelist_size, evt);
	hci_ble_read_buffer_size();
}

#if (CONTROLLER_PRIVACY)

void le_read_resolving_list_size_cmpl(UINT8* evt, UINT16 len)
{
	STREAM_TO_UINT8(g_local_adapter.resolvinglist_size, evt);
#ifdef SHORT_RL_SIMULATE_SIZE
	g_local_adapter.resolvinglist_size = SHORT_RL_SIMULATE_SIZE;
#endif
	hci_ble_set_rpa_tout(0x0384); //15min
}

void le_set_rpa_timeout_cmpl()
{
	hci_read_bd_addr();
}

#endif /* CONTROLLER_PRIVACY */

void le_read_buf_size_cmpl(UINT8* evt, UINT16 len)
{
	STREAM_TO_UINT16(g_local_adapter.buffer_size, evt);
	if (g_local_adapter.buffer_size == 0)
	{
		logd(" send hci_cmd_read_buffer_size");
		hci_read_buffer_size();
	} else
	{
		STREAM_TO_UINT8(g_local_adapter.num_of_buffer, evt);
		g_local_adapter.data_window = g_local_adapter.num_of_buffer;
		logd("data_window:%d", g_local_adapter.data_window);
		logd(" send hci_ble_read_local_feat");
		hci_ble_read_local_feat();
	}
}

void le_evt_mask_cmpl()
{
	logd(" send le_evt_mask_cmpl");
	hci_ble_read_white_list_size();
}

void evt_mask_page_2_cmpl()
{
	UINT8 mask[] = { 0, 0, 0, 0, 0, 0, 0, 0x3F };

#if (CONTROLLER_PRIVACY)
	mask[6] |= 0x06;
#endif

#if (CONTROLLER_ECDH)
	mask[6] |= 0x01;
	mask[7] |= 0x80;
#endif

#if (SMP_FORCE_DISABLE_HOST_DLE != TRUE)
	mask[7] |= 0x40;
#endif

	logd("send hci_ble_set_event_mask");
	hci_ble_set_event_mask(mask);
}

void evt_mask_cmpl()
{
#if (LE_PING_ENABLE == TRUE)
	UINT8 mask[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 00, 00}; // LE Ping: Authenticated Payload Timeout Expired Event = 0x0000000000800000
	logd("send hci_ble_set_event_mask_page_2");
	hci_ble_set_event_mask_page_2(mask);
#else
	evt_mask_page_2_cmpl();
#endif
}

void write_le_host_support_cmpl()
{
	UINT8 event_mask[] =
	{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	logd(" send hci_ble_set_event_mask");
	hci_set_event_mask(event_mask);
}

void read_local_feat_cmpl(UINT8* evt, UINT16 len)
{
	memcpy(g_local_adapter.local_features, evt, 8);
	if (g_local_adapter.local_features[HCI_LOCAL_FEATURE_MASK_CONTROLLER_LE_SUPPORTED_OFFSET] & HCI_LOCAL_FEATURE_MASK_CONTROLLER_LE_SUPPORTED_MASK)
	{
		UINT8 event_mask[] =
		{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
		logd(" send hci_set_event_mask");
		hci_set_event_mask(event_mask);
/*		logd(" Send LE Host supported");
		hci_ble_write_host_supported(HCI_LE_HOST_SUPPORTED,
				HCI_LE_SIMUL_HOST_SUPPORTED);*/
	}/* else
	{
		loge(" Controller doesn't support LE.");
		g_local_adapter.adapter_state = ADAPTER_STATE_DISABLED;
	}*/
}

void reset_cmpl_handler()
{
	logd(" send hci_read_local_feat");
#if (CONTROLLER_ECDH)
	/* This is a workaround for LNP.
	 * We try to generate DH public keys in the smp_init sequence
	 * But the controller is unable to generate a correct public key in such a short time after
	 * hci reset.( LNP controller needs 2.5s to generate public key after issuing a
	 * hci reset. This work around will be removed once public key generation is moved form the
	 * init sequence
	 */
	logw("Stack initializing. Please wait...");
	osa_sleep(3);
#endif /*CONTROLLER_ECDH*/

#if (BLE_USE_FWINFO_FUNC_CALL == FALSE)
	hci_read_local_feat();
#else
	UINT8 status = 0;
	ble_controller_info_t bt_controller_info;
	status = hci_read_bt_controller_info(&bt_controller_info);
	if(!status)
	{
		memcpy(g_local_adapter.local_features, bt_controller_info.local_features, 8);
		memcpy(g_local_adapter.ble_local_features,bt_controller_info.ble_local_features,8);
		UINT8 *evt = &bt_controller_info.bdaddr[0];
		STREAM_TO_BDADDR(g_local_adapter.bdaddr, evt);
		g_local_adapter.whitelist_size = bt_controller_info.le_whitelist_size;
		g_local_adapter.buffer_size = bt_controller_info.le_buffer_size;
		g_local_adapter.num_of_buffer = bt_controller_info.num_of_buffer;
		g_local_adapter.data_window = g_local_adapter.num_of_buffer;

		if (g_local_adapter.local_features[HCI_LOCAL_FEATURE_MASK_CONTROLLER_LE_SUPPORTED_OFFSET] & HCI_LOCAL_FEATURE_MASK_CONTROLLER_LE_SUPPORTED_MASK)
		{
			ble_controller_event_mask_t stmask = { {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
													{0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
			status = hci_write_bt_controller_info(&stmask);
		}
		if(!status)
		{
			read_bd_addr_cmpl(NULL,0);
		}
		else
		{
			loge(" could not set event mask");
		}
	}
	else
	{
		loge(" Could not read BLE controller info");
	}
#endif
}

#if (TARGET_THREADX == TRUE)
static void manuf_mode_on()
{
	hci_manuf_mode(TRUE);
}

void write_bddata()
{
	hci_write_bd_data();
}

static void manuf_mode_off()
{
	hci_manuf_mode(FALSE);
}

void write_bddata_cmpl()
{
	manuf_state = MANUF_STATE_OFF;
	manuf_mode_off();
}

void manuf_cmd_cmpl()
{
	switch(manuf_state)
	{
		case MANUF_STATE_NONE:
			manuf_state = MANUF_STATE_ON;
			write_bddata();
			break;
		case MANUF_STATE_ON:
			break;
		case MANUF_STATE_OFF:
			manuf_state = MANUF_STATE_NONE;
			reset_cmpl_handler();
			break;
	}
}

#endif

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

void dm_add_adv_data(UINT8 length, UINT8 type, UINT8 *data)
{
	gap_add_adv_scanresp_data(g_local_adapter.gap_data.adv_data, length, type, data);
}

void dm_remove_adv_data(UINT8 length, UINT8 type, UINT8 *data)
{
	gap_remove_adv_scanresp_data(g_local_adapter.gap_data.adv_data, length, type, data);
}

void dm_add_scanresp_data(UINT8 length, UINT8 type, UINT8 *data)
{
	gap_add_adv_scanresp_data(g_local_adapter.gap_data.scanresp_data, length, type, data);
}

void dm_remove_scanresp_data(UINT8 length, UINT8 type, UINT8 *data)
{
	gap_remove_adv_scanresp_data(g_local_adapter.gap_data.scanresp_data, length, type, data);
}

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

void dm_set_local_device_name(UINT8* name, UINT8 len)
{

	memset(g_local_adapter.local_name, 0, sizeof(g_local_adapter.local_name));

	if (!name)
	{
		/* Set default name */
			memcpy(g_local_adapter.local_name, LOCAL_NAME, sizeof(g_local_adapter.local_name));
	}
	else
		memcpy(g_local_adapter.local_name, name, len);

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	gap_add_adv_scanresp_data(g_local_adapter.gap_data.adv_data, get_name_length(g_local_adapter.local_name), GAP_ADV_DATA_COMPLETE_LOCAL_NAME, (UINT8*) g_local_adapter.local_name);
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
}

UINT8 dm_get_local_device_name(UINT8* name)
{
	memcpy(name, g_local_adapter.local_name, sizeof(g_local_adapter.local_name));
	return get_name_length(g_local_adapter.local_name);
}

void dm_enable()
{
	logi("");
	if (g_local_adapter.adapter_state != ADAPTER_STATE_DISABLED)
	{
		logw("Adapter is in state %u", g_local_adapter.adapter_state);
		return;
	}

#if (TARGET_ANDROID == TRUE)
	/* wait for controller to be initialized. */
	logd("wait for fw to download");
	osa_mutex_get(&g_local_adapter.fw_init_mutex);
	osa_mutex_get(&g_local_adapter.fw_init_mutex);
#endif
	logd("proceed to stack init.");

	g_local_adapter.adapter_state = ADAPTER_STATE_ENABLING;
#if (TARGET_THREADX == TRUE || TARGET_THREADX_RW == TRUE)
	logd("call reset_cmpl_handler");
	reset_cmpl_handler();
	//manuf_state = MANUF_STATE_NONE;
	//manuf_mode_on();
#else
	hci_reset();
#endif
}

void dm_disable()
{
	logi("");
	if (g_local_adapter.adapter_state != ADAPTER_STATE_ENABLED)
	{
		logw("Adapter is in state %u", g_local_adapter.adapter_state);
		return;
	}

	g_local_adapter.adapter_state = ADAPTER_STATE_DISABLED;
}

void dm_register(UINT8 app_idx, device_control_callbacks_t *app_device_control_cb)
{
	if (g_local_adapter.app_list[app_idx])
		g_local_adapter.app_list[app_idx]->app_device_control_cb = app_device_control_cb;
}

void dm_unregister(UINT8 app_idx)
{
	if (g_local_adapter.app_list[app_idx])
		g_local_adapter.app_list[app_idx]->app_device_control_cb = NULL;
}

INT8 dm_init()
{
	logi("");
	osa_mutex_create(&g_local_adapter.fw_init_mutex);

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	/* Set default flags and device name */
	UINT8 flags = GAP_ADV_FLAGS_LE_GENERAL_DISCOVERABLE | GAP_ADV_FLAGS_BR_EDR_NOT_SUPPORTED;
	dm_add_adv_data(0x01, GAP_ADV_DATA_FLAGS, &flags);
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */
	return STATUS_SUCCESS;
}

void dm_cleanup()
{
	logi("");
	osa_mutex_delete(&g_local_adapter.fw_init_mutex);
	iLE_stack_cleanup();
}
