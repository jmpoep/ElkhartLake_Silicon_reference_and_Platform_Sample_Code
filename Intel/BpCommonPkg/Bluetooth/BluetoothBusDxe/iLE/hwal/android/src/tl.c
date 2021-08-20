/** @file
  Userial layer implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "config_host.h"
#include "tl.h"
#include "error_code.h"
#include <stdint.h>
#include <poll.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "osa_types.h"
#include "hci_host.h"
#include "int_interface.h"
#include "utils.h"

#include "bt_types.h"
#include "bt_hci_lib.h"
#include "bt_hci_bdroid.h"


#define MODULE_DBG_LVL USERIAL_DBG_LVL
#include "log.h"

#define BT_EVT_MASK					0xFF00
#define BT_SUB_EVT_MASK			 	0x00FF
#define BT_EVT_TO_BTU_HCI_EVT	   	0x1000
#define BT_EVT_TO_BTU_HCI_ACL	   	0x1100
#define BT_EVT_TO_LM_HCI_CMD		0x2000
#define BT_EVT_TO_LM_HCI_ACL		0x2100
#define LOCAL_BLE_CONTROLLER_ID		(1)

typedef HC_BT_HDR BT_HDR;

static bt_hc_interface_t *bt_hc_if = NULL;
static const bt_hc_callbacks_t hc_callbacks;
static pthread_mutex_t mem_mutex = PTHREAD_MUTEX_INITIALIZER;

void android_hex_dump(char* tag, UINT8* buffer, UINT16 len)
{
	UINT16 ijk;
	char str[1024];
	memset(str, 0, 1024);
	for (ijk = 0; ijk < len; ijk++)
	{
		sprintf(&str[ijk * 3], "%02x ", buffer[ijk]);
	}
	str[len * 3] = '\0';
	ALOGD("%s %s", tag, str);
}

char *hci_alloc(int size)
{
	HC_BT_HDR *p_hdr = NULL;

	pthread_mutex_lock(&mem_mutex);
	size = size + BT_HC_BUFFER_HDR_SIZE;

	if (size <= 16)
		size = 16;
	else if (size <= 32)
		size = 32;
	else if (size <= 64)
		size = 64;
	else if (size <= 128)
		size = 128;
	else if (size <= 256)
		size = 256;
	else if (size <= 512)
		size = 512;
	else if (size <= 1024)
		size = 1024;
	else if (size <= 2048)
		size = 2048;
	else
	{
		ALOGD("Size too big to allocate");
		pthread_mutex_unlock(&mem_mutex);
		return NULL;
	}

	p_hdr = (HC_BT_HDR *) alloc (size);
	if (p_hdr == NULL)
	{
		ALOGD("malloc returns NO BUFFER!");
		pthread_mutex_unlock(&mem_mutex);
		return NULL;
	}
	else
	{
		memset(p_hdr, 0x0, size);
	}
	pthread_mutex_unlock(&mem_mutex);
	return ((char*)((uint8_t *)p_hdr + BT_HC_BUFFER_HDR_SIZE));
}

static void hci_dealloc(TRANSAC transac)
{
	HC_BT_HDR *p_hdr = NULL;

	pthread_mutex_lock(&mem_mutex);

	//logd("transac:%p", transac);
	p_hdr = (HC_BT_HDR *) (((uint8_t *)transac) - BT_HC_BUFFER_HDR_SIZE);
	if (NULL != p_hdr)
	{
		dealloc(p_hdr);
	}
	pthread_mutex_unlock(&mem_mutex);
}

static INT8 hci_enable()
{
	logd("");

	if (bt_hc_if)
	{
		unsigned char address[6] = {0x11,0x22, 0x33, 0x44, 0x55, 0x66};

		int result = bt_hc_if->init(&hc_callbacks, address);
		logd("result:%d", result);

#ifdef NEXUS
		bt_hc_if->set_power(BT_HC_CHIP_PWR_OFF);

		bt_hc_if->set_power(BT_HC_CHIP_PWR_ON);

		bt_hc_if->preload(NULL);
#else
	    unsigned long module_name = 2;/* MODULE_BT ; */
	    bt_hc_if->preload(&module_name);
#endif
	}
	return STATUS_SUCCESS;
}

INT8 tl_init(char* device, int ispeed)
{
	logd("");
	if ( (bt_hc_if = (bt_hc_interface_t *) bt_hc_get_interface()) == NULL)
	{
		loge("!!! Failed to get BtHostControllerInterface !!!");
	}
	hci_enable();
	return STATUS_SUCCESS;
}

INT8 tl_write(UINT8 *buffer, UINT16 len)
{
	BT_HDR *p_msg = (BT_HDR *) hci_alloc ((UINT16) (BT_HC_HDR_SIZE + len - 1));

	if (!p_msg)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	UINT8* p = (UINT8*)(p_msg + 1);
	memcpy (p, buffer + 1, len - 1);

	p_msg->len = len - 1;

	UINT16 event = 0;
	switch (buffer[0])
	{
	case HCI_CMD:
		event = BT_EVT_TO_LM_HCI_CMD;
		break;
	case HCI_ACL:
		event = (UINT16)(BT_EVT_TO_LM_HCI_ACL | LOCAL_BLE_CONTROLLER_ID);
		break;
	}

	UINT16 sub_event = event & BT_SUB_EVT_MASK;  /* local controller ID */
	p_msg->event = event;

	if((sub_event == LOCAL_BR_EDR_CONTROLLER_ID) || \
	   (sub_event == LOCAL_BLE_CONTROLLER_ID))
	{
		android_hex_dump("tl_write:", (UINT8*)(p_msg + 1), p_msg->len);
		if (bt_hc_if)
		{
			bt_hc_if->transmit_buf((TRANSAC)p_msg, \
									   (char *) (p_msg + 1), \
										p_msg->len);
			logd("transmit_buf returned");
		}
		else
		{
			logd("bt_hc_if is NULL. dealloc p_msg.");
			hci_dealloc(p_msg);
		}
	}
	else
	{
		logd("Invalid Controller ID. Discarding message.");
		hci_dealloc(p_msg);
	}
	return STATUS_SUCCESS;
}

void tl_close()
{
	logd("");
	if (bt_hc_if)
	{
		bt_hc_if->cleanup();
	}
}

static void preload_cb(TRANSAC transac, bt_hc_preload_result_t result)
{
	logd("HC preload_cb %d [0:SUCCESS 1:FAIL]", result);

	if (result == BT_HC_PRELOAD_SUCCESS)
	{
		/* Notify controller is ready */
		logd("put");
		osa_mutex_put(&g_local_adapter.fw_init_mutex);
		osa_mutex_put(&g_local_adapter.fw_init_mutex);
	}
}

static int data_ind(TRANSAC transac, char *p_buf, int len)
{
	BT_HDR *p_msg = (BT_HDR *) transac;

	logd("len:%d", p_msg->len);

	UINT8 *buffer = (UINT8*) alloc (p_msg->len + UART_HDR_SIZE);
	if (!buffer)
		return BT_HC_STATUS_FAIL;
	switch (p_msg->event & BT_EVT_MASK)
	{
	case BT_EVT_TO_BTU_HCI_ACL:
		buffer[0] = HCI_ACL;
		break;
	case BT_EVT_TO_BTU_HCI_EVT:
		buffer[0] = HCI_EVT;
		break;
	}
	memcpy(buffer + 1, (UINT8*)(p_msg + 1), p_msg->len);

	android_hex_dump("data_ind:", buffer, p_msg->len + UART_HDR_SIZE);

	rx_req_hci_evt_msg(buffer, p_msg->len + UART_HDR_SIZE);

	dealloc(buffer);

	return BT_HC_STATUS_SUCCESS;
}

static int tx_result(TRANSAC transac, char *p_buf, \
					  bt_hc_transmit_result_t result)
{
	logd("HC tx_result %d (event=%04X)", result, ((BT_HDR *)transac)->event);
    if (result == BT_HC_TX_FRAGMENT)
    {
        logd("BT_HC_TX_FRAGMENT. Do noting.");
    }
    else
    {
		hci_dealloc(transac);
    }

	return BT_HC_STATUS_SUCCESS;
}

static const bt_hc_callbacks_t hc_callbacks = {
	sizeof(bt_hc_callbacks_t),
	.preload_cb = preload_cb,
	.postload_cb = NULL, //postload_cb,
	.lpm_cb = NULL, //lpm_cb,
	.hostwake_ind = NULL, //hostwake_ind,
	.alloc = hci_alloc,
	.dealloc = hci_dealloc,
	.data_ind = data_ind,
	.tx_result = tx_result
};
