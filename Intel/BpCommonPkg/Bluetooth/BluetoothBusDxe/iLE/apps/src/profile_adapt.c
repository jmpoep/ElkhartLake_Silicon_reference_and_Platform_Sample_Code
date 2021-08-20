/** @file
  Profile adaptation layer for embedded LE stack.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "bt_types.h"
#include "utils.h"
#include "config_host.h"
#include "profile_adapt.h"
#include "interface.h"
#include "hci_host.h"

#define MODULE_DBG_LVL PROFILE_ADAPT_APP_DBG_LVL
#include "log.h"

#if (TARGET_THREADX == TRUE)

void profile_command_recvd(UINT8 *value, UINT8 value_len)
{
	UINT16 command_opcode;
	UINT8 param_len, use_case;
	STREAM_TO_UINT16(command_opcode, value);
	STREAM_TO_UINT8(param_len, value);
	STREAM_TO_UINT8(use_case, value);

	logd("command_opcode:%02x param_len:%d use_case:%d", command_opcode, param_len, use_case);
	switch (command_opcode)
	{
	case PROFILE_OPERATION_DO_DEVICE_DISCOVERY:
	{
		if (param_len != PROFILE_COMMAND_DO_DEVICE_DISCOVERY_PARAM_LEN)
			return;
		switch (use_case)
		{
		case PXP_CLIENT_USE_CASE:
		{
#if (PXP_APP == TRUE)
			pxp_start_discovery(NULL);
#endif
		}
			break;
		case FMP_CLIENT_USE_CASE:
		{
#if (FMP_APP == TRUE)
			fmp_start_discovery(NULL);
#endif
		}
			break;
		case HRP_CLIENT_USE_CASE:
		{
#if (HRP_APP == TRUE)
			logd("starting hrp discovery");
			hrp_start_discovery(NULL);
#endif
		}
			break;
		}
	}
		break;
	case PROFILE_OPERATION_DO_START_USE_CASE:
	{
		switch (use_case)
		{
		case PXP_CLIENT_USE_CASE:
		{
#if (PXP_APP == TRUE)
			pxp_start_use_case(NULL);
#endif
		}
			break;
		case FMP_CLIENT_USE_CASE:
		{
#if (FMP_APP == TRUE)
			UINT8 bdaddr[BD_ADDR_LEN];
			STREAM_TO_BDADDR(bdaddr, value);
			fmp_start_use_case(bdaddr);
#endif
		}
			break;
		case HRP_CLIENT_USE_CASE:
		{
#if (HRP_APP == TRUE)
			UINT8 bdaddr[BD_ADDR_LEN];
			STREAM_TO_BDADDR(bdaddr, value);
			hrp_start_use_case(bdaddr);
#endif
		}
			break;
		}
	}
		break;

	case PROFILE_OPERATION_DO_STOP_USE_CASE:
		{
			switch (use_case)
			{
			case PXP_CLIENT_USE_CASE:
			{
#if (PXP_APP == TRUE)
				pxp_stop_use_case(NULL);
#endif
			}
				break;
			case FMP_CLIENT_USE_CASE:
			{
#if (FMP_APP == TRUE)
				UINT8 bdaddr[BD_ADDR_LEN];
				STREAM_TO_BDADDR(bdaddr, value);
				fmp_stop_use_case(bdaddr);
#endif
			}
				break;
			case HRP_CLIENT_USE_CASE:
			{
#if (HRP_APP == TRUE)
				UINT8 bdaddr[BD_ADDR_LEN];
				STREAM_TO_BDADDR(bdaddr, value);
				hrp_stop_use_case(bdaddr);
#endif
			}
				break;
			}
		}
			break;
	case PROFILE_OPERATION_DO_WRITE_ALERT_LEVEL:
		{
			switch (use_case)
			{
				case FMP_CLIENT_USE_CASE:
				{
#if (FMP_APP == TRUE)
					UINT8 alert_level;
					STREAM_TO_UINT8(alert_level, value);
					fmp_write_alert_level(&alert_level);
#endif
				}
					break;
			}
		}
			break;
	default:
			break;
	}

}

static void send_profile_callback(UINT8 *buffer, UINT8 buffer_len)
{
	iLE_send_hci_command(PROFILE_OPERATION_ASYNC_EVENT, buffer_len, buffer);
}

/**
 * @brief This function is called when device discovery operation is
 * completed.
 *
 * @func profile_device_discovery_completed
 *
 * Parameter buffer will be:
 * -----------------------------------------
 * | status | use case | list of bd address |
 * -----------------------------------------
 *   1B			1B			6 * num_of_results B
 */
void profile_device_discovery_completed(UINT8 status, UINT8 use_case,
		UINT8** bd_addr_list, UINT8 num_of_results)
{
	UINT8 i;
	UINT8 size = (num_of_results * BD_ADDR_LEN) + 3 + UART_HDR_SIZE + HCI_CMD_PREAMBLE_SIZE;
	UINT8 param_size = size - UART_HDR_SIZE - HCI_CMD_PREAMBLE_SIZE;
	UINT8 *buffer = (UINT8*) app_alloc(
			sizeof(UINT8) * size);
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return;
#endif
	UINT8 *p = buffer;
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, PROFILE_OPERATION_ASYNC_EVENT);
	UINT8_TO_STREAM(p, param_size);
	UINT8_TO_STREAM(p, PROFILE_EVENT_DEVICE_DISCOVERY_COMPLETED);
	UINT8_TO_STREAM(p, status);
	UINT8_TO_STREAM(p, use_case);
	for (i = 0; i < num_of_results; i++)
	{
		//memcpy(p, bd_addr_list[i], BD_ADDR_LEN);
		REVERSE_ARRAY_TO_STREAM(p, bd_addr_list[i], BD_ADDR_LEN);
		//p += BD_ADDR_LEN;
	}
	logd("- size:%d", size);
	hex_dump("", buffer, size);
	send_profile_callback(buffer, size);
	app_dealloc(buffer);
}

/**
 * @brief This function is called when hrp sensor data is available.
 *
 * @func hrp_data_cb
 *
 * Parameter buffer will be:
 * ----------------------------
 * | hrp data | battery level |
 * ---------------------------
 *   1B
 */
void hrp_data_cb(UINT8 hrp_data, UINT8 battery_level)
{
	UINT8 size = PROFILE_EVENT_HRP_DATA_PARAM_LEN + UART_HDR_SIZE + HCI_CMD_PREAMBLE_SIZE;
	UINT8 *buffer = (UINT8*) app_alloc(size * sizeof (UINT8));
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return;
#endif
	UINT8 *p = buffer;
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, PROFILE_OPERATION_ASYNC_EVENT);
	UINT8_TO_STREAM(p, PROFILE_EVENT_HRP_DATA_PARAM_LEN);
	UINT8_TO_STREAM(p, PROFILE_EVENT_HRP_DATA);
	UINT8_TO_STREAM(p, hrp_data);
	UINT8_TO_STREAM(p, battery_level);
	send_profile_callback(buffer, size);
	app_dealloc(buffer);
}

/**
 * @brief This function is called when embedded stack init is completed.
 *
 * @func alert_level_data_cb
 *
 * Parameter buffer will be:
 * --------------
 * | alert level |
 * --------------
 *   1B
 */
void alert_level_data_cb(UINT8 alert_level)
{
	UINT8 size = PROFILE_EVENT_ALERT_LEVEL_DATA_PARAM_LEN + UART_HDR_SIZE + HCI_CMD_PREAMBLE_SIZE;
	UINT8 *buffer = (UINT8*) app_alloc(size * sizeof (UINT8));
#if (PARANOID_STACK == TRUE)
	if (!buffer)
		return;
#endif
	UINT8 *p = buffer;
	JUMP_UART_HEADER(p);
	UINT16_TO_STREAM(p, PROFILE_OPERATION_ASYNC_EVENT);
	UINT8_TO_STREAM(p, PROFILE_EVENT_ALERT_LEVEL_DATA_PARAM_LEN);
	UINT8_TO_STREAM(p, PROFILE_EVENT_ALERT_LEVEL_DATA);
	UINT8_TO_STREAM(p, alert_level);
	send_profile_callback(buffer, size);
	app_dealloc(buffer);
}
#else
void profile_command_recvd(UINT8 *value, UINT8 value_len){}
void profile_device_discovery_completed(UINT8 status, UINT8 use_case,
		UINT8* bd_addr_list[BD_ADDR_LEN], UINT8 num_of_results){}
void hrp_data_cb(UINT8 hrp_data, UINT8 battery_level){}
void alert_level_data_cb(UINT8 alert_level){}

#endif /* (TARGET_THREADX == TRUE) */
