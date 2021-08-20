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
//#include "cse_adap.h"
#include "hc2app.h"
#include "tld2app.h"

#define MODULE_DBG_LVL USERIAL_DBG_LVL
#include "log.h"


#if 0
#define HCI_TX_DUMP_BUF_SIZE 2048
u8 hciTxDumpBuf[HCI_TX_DUMP_BUF_SIZE];
u32 hciTxDumpIdx = 0;
void logHciTx(u32 len, pu8 packet)
{
  u32 firstCopy = 0;
  if(hciTxDumpIdx+len > HCI_TX_DUMP_BUF_SIZE)
  {
    // fill only the part and goto zero and fill
    firstCopy = (HCI_TX_DUMP_BUF_SIZE-hciTxDumpIdx);
    memcpy(&(hciTxDumpBuf[hciTxDumpIdx]), packet, firstCopy);
    hciTxDumpIdx = 0;
    len -= firstCopy;
    memcpy(&(hciTxDumpBuf[hciTxDumpIdx]), packet, len);
  }
  else
  {
    memcpy(&(hciTxDumpBuf[hciTxDumpIdx]), packet, len);
    hciTxDumpIdx += len;
  }
}
#endif


INT8 tl_init(char* device, int ispeed)
{
	return STATUS_SUCCESS;
}

INT8 tl_write(UINT8 *buffer, UINT16 len)
{
	/* Call FW given API to send command */
#if (USERIAL_DBG == TRUE)
	hex_dump("<---", buffer, len);
#endif
#if 0
    logHciTx(len, buffer);
#endif

	switch (buffer[0])
	{
		case HCI_CMD:
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
		    UINT16 Opcode=0;
		    memcpy(&Opcode, buffer+1,2);
#endif
#if (LE_STACK_PROFILING == TRUE)
			log_time_stamp_with_opcode(TIME_HCI_CMD_SENT, Opcode);
#endif
			hcapi_IntCommand2BB(buffer + 1);
			//HC_HRP_hc2BB(buffer + 1);
			break;
		case HCI_ACL:
#if (LE_STACK_PROFILING == TRUE)
			log_time_stamp(TIME_HCI_SEND_DATA);
#endif
			tld_IntL2CAP2BB(buffer + 1);
			//HC_HRP_hcACLData2BB(buffer + 1);
			break;
	}

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
	hex_dump("--->", buffer, len);
#endif
		rx_req_hci_evt_msg(buffer, len + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE);
#if (LE_STACK_PROFILING == TRUE)
		log_time_stamp(TIME_HCI_RECV_DATA);
#endif

	}
		break;
	case HCI_EVT:
	{
		UINT8 len;
		JUMP_CUSTOM_LEN(p, UART_HDR_SIZE + 1 /* Event code */);
		STREAM_TO_UINT8(len, p);
#if (USERIAL_DBG == TRUE)
	log("---> ");
	hex_dump("", buffer, len + UART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE);
#endif
		rx_req_hci_evt_msg(buffer, len + UART_HDR_SIZE + HCI_EVT_PREAMBLE_SIZE);
	}
		break;
	case (GET_OCF(PROFILE_OPERATION_DO_DEVICE_DISCOVERY)):
	case (GET_OCF(PROFILE_OPERATION_DO_START_USE_CASE)):
	case (GET_OCF(PROFILE_OPERATION_DO_STOP_USE_CASE)):
	case (GET_OCF(PROFILE_OPERATION_DO_WRITE_ALERT_LEVEL)):
	case (GET_OCF(PROFILE_OPERATION_ASYNC_EVENT)):
	{
		UINT8 param_len, buffer_len;
		UINT8 *event_buffer;
		JUMP_CUSTOM_LEN(p, 2 /* HCI command opcode */);
		STREAM_TO_UINT8(param_len, p);
		buffer_len = param_len + UART_HDR_SIZE + HCI_CMD_PREAMBLE_SIZE;
		event_buffer = (UINT8*) alloc (buffer_len);
#if (PARANOID_STACK == TRUE)
		if (!event_buffer)
			return;
#endif
		UINT8* p_buf = event_buffer;
		UINT8_TO_STREAM(p_buf, HCI_CMD);
		memcpy(p_buf, buffer, buffer_len - UART_HDR_SIZE);
#if (USERIAL_DBG == TRUE)
	log("---> ");
	hex_dump("", event_buffer, buffer_len);
#endif
		rx_req_hci_evt_msg(event_buffer, buffer_len);
		dealloc (event_buffer);
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

