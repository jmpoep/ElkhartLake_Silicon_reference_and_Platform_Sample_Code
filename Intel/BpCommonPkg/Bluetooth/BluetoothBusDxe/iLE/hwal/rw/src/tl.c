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
#include <string.h>
#include "tl.h"
#include "utils.h"
#include "hci_host.h"
#include "bt_types.h"
#include "int_interface.h"

#include "hci_adapter.h"
#include "tx_app_define.h"
#include "rwble.h"
#include "hci.h"
#define USERIAL_DBG TRUE


#define MODULE_DBG_LVL USERIAL_DBG_LVL
#include "log.h"

extern TX_QUEUE                queue_0;
extern TX_EVENT_FLAGS_GROUP	event_flags_0;
extern TX_BLOCK_POOL           block_pool_0;
void hci_cmd_timeout_handler(osa_timer_arg_t arg);
#define HCI_CMD_TIMEOUT 2000 //ms

INT8 tl_init(char* device, int ispeed)
{
	return STATUS_SUCCESS;
}

static UINT8 hci_post_msg_to_fw(UINT8 **p_msg)
{
	UINT8 status;
	//Post in threadx Q and signal rwble thread
	status = tx_queue_send(&st_to_ll_msg_queue, p_msg, TX_NO_WAIT);
	if(TX_SUCCESS != status)
	{
		// Q full, what do we do?
		loge("In hci_post_msg_to_fw - Release block : %x \n", (UINT8)*p_msg);
		dealloc(*p_msg);
	}
	//Send an event to LL thread
	tx_event_flags_set(&ll_evnt_flags, OS_EVNT_FLG_HCI_MSG, TX_OR);
	return status;
}

UINT8 hci_post_evt_msg_to_tl(UINT8 **p_msg)
{
	UINT8 status;
	//Post in threadx Q and signal rwble thread
	status = tx_queue_send(&st_to_tr_msg_queue, p_msg, TX_NO_WAIT);
	if(TX_SUCCESS != status)
	{
		// Q full, what do we do?
		loge("In hci_post_msg_to_fw - Release block : %x \n", (UINT8)*p_msg);
		dealloc(*p_msg);
	}
	//Let transport know that there is a evnt msg
	tx_event_flags_set(&tr_evnt_flags, OS_EVNT_FLG_HCI_EVNT, TX_OR);
	return status;

}

INT8 tl_write(UINT8 *buffer, UINT16 len)
{
	UINT8* buf = buffer - sizeof(UINT32);

	/* Call FW given API to send command */
#if (USERIAL_DBG == TRUE)
	hex_dump("<--- ", buffer, len);
#endif
#if (TARGET_THREADX_RW == TRUE)
	if (buffer[0] == HCI_EVT)
		hci_post_evt_msg_to_tl(&buf);
	else
		{
#if (ATP_BT_SNOOP == TRUE)
		UINT8	*p_buf, *p1_buf, *vs_buf = NULL;
		UINT8 len1, len2;
		len2 = len + UART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE + 1/*eventid*//*3*/;

		p_buf = alloc_queue_element(len2/*opcode +nbcomplpkt*/, HCI_ALLOC);
		if (p_buf !=NULL)
		{
			vs_buf = p_buf;
			len1 = len + 1 /*evt idUART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE */;
			UINT8_TO_STREAM(vs_buf, HCI_EVT_MSG_TYPE);
			UINT8_TO_STREAM(vs_buf, HCI_DBG_EVT_CODE);
			UINT8_TO_STREAM(vs_buf,len1);
			UINT8_TO_STREAM(vs_buf,0x2E);
			memcpy(vs_buf, buffer, len);
			p1_buf = p_buf - sizeof(UINT32);
			hci_post_evt_msg_to_tl(&p1_buf);
		}
#endif
		hci_post_msg_to_fw(&buf);


		}
#endif
	return STATUS_SUCCESS;
}

void tl_recv_msg(UINT8 *buffer)
{
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return;
#endif
	UINT8* p = buffer;
	switch (buffer[0])
	{
	case HCI_ACL:
	{
		UINT16 len;
		JUMP_CUSTOM_LEN(p, 2 /* ACL HANDLE size */ + UART_HDR_SIZE);
		STREAM_TO_UINT16(len, p);
#if (USERIAL_DBG == TRUE)
	hex_dump("---> ", buffer, len);
#endif
#if (ATP_BT_SNOOP == TRUE)
		UINT8 *p_buf;
		UINT8 	*p1_buf, *vs_buf;;
		UINT8 len1 = len + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + UART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE + UART_HDR_SIZE;/*Evt Id*/
		UINT8 acl_len = MIN(len1,255);
		p_buf =	alloc_queue_element(acl_len, HCI_ALLOC);
		if (p_buf !=NULL)
		{
			vs_buf = p_buf;
			UINT8 len2 = MIN(len,249) + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE + 1;/*eventid*/ /*3*/
			UINT8_TO_STREAM(vs_buf, HCI_EVT_MSG_TYPE);
			UINT8_TO_STREAM(vs_buf,HCI_DBG_EVT_CODE);
			UINT8_TO_STREAM(vs_buf,len2);
			UINT8_TO_STREAM(vs_buf,0x2E);
			len1 = len + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
			acl_len = MIN(249,len1);
			memcpy(vs_buf, buffer, acl_len);
			p1_buf = p_buf - sizeof(UINT32);

			hci_post_evt_msg_to_tl(&p1_buf);
		}
#endif
		hci_recv_buffer(buffer, len + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE);
	}
		break;
	case HCI_EVT:
	{
		UINT8 len;
		JUMP_CUSTOM_LEN(p, UART_HDR_SIZE + 1 /* Event code */);
		STREAM_TO_UINT8(len, p);
#if (USERIAL_DBG == TRUE)
	hex_dump("---> ", buffer, len + UART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE);
#endif
#if (ATP_BT_SNOOP == TRUE)
		UINT8 *p_buf;
		UINT8 	*p1_buf, *vs_buf;

		UINT8 len1 = len + UART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE + UART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE + UART_HDR_SIZE/*Evt Id*//* + HCI_EVT_PREAMBLE_SIZE*/;
		/* H4 + H4 header(EVENT TYPE + LEN(2bytes) + H4 + H4 header(EVENT TYPE + LEN(2bytes) + eventid*/
		p_buf =	alloc_queue_element(len1, HCI_ALLOC);
		if (p_buf !=NULL)
		{
			vs_buf = p_buf;
			UINT8 len2 = len + UART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE + 1;/*eventid*/ /*3*/
			UINT8_TO_STREAM(vs_buf, HCI_EVT_MSG_TYPE);
			UINT8_TO_STREAM(vs_buf,HCI_DBG_EVT_CODE);
			UINT8_TO_STREAM(vs_buf,len2);
			UINT8_TO_STREAM(vs_buf,0x2E);
			len1 = len + UART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE;
			memcpy(vs_buf, buffer, len1);
			p1_buf = p_buf - sizeof(UINT32);
			hci_post_evt_msg_to_tl(&p1_buf);
		}
#endif
		hci_recv_buffer(buffer, len + UART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE);
	}
		break;
	default:
		logd("Unknown HCI msg");
		break;

	}
}

void tl_close()
{
}

