/** @file
  GAP layer header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef GAP_H_
#define GAP_H_

#include "bt_types.h"
#include "int_interface.h"

#define GAP_DATA_FLAGS				0x01
#define GAP_DATA_16BIT_SERVICE_UUIDS_INCOMP	0x02
#define GAP_DATA_16BIT_SERVICE_UUIDS_COMP	0x03
#define GAP_DATA_32BIT_SERVICE_UUIDS_INCOMP	0x04
#define GAP_DATA_32BIT_SERVICE_UUIDS_COMP	0x05
#define GAP_DATA_128BIT_SERVICE_UUIDS_INCOMP	0x06
#define GAP_DATA_128BIT_SERVICE_UUIDS_COMP	0x07
#define GAP_DATA_SHORTENED_LOCAL_NAME		0x08
#define GAP_DATA_COMPLETE_LOCAL_NAME		0x09
#define GAP_DATA_TX_POWER_LEVEL			0x0A
#define GAP_DATA_APPEARANCE			0x19
#define GAP_DATA_LE_ROLE			0x1C

/* GAP Connection Failure Error codes mapped with HCI Error codes */
#define GAP_CONNECT_ERROR_CONNECTION_TIMEOUT					0x08
#define GAP_CONNECT_ERROR_CONNECTION_LIMIT_EXCEEDED				0x09
#define GAP_CONNECT_ERROR_ACL_CONNECTION_ALREADY_EXISTS			0x0B
#define GAP_CONNECT_ERROR_DIRECTED_ADVERTISING_TIMEOUT			0x3C

/* GAP Disconnect Failure Error codes mapped with HCI Error codes */
#define GAP_DISCONNECT_REASON_AUTHENTICATION_FAILURE			0x05
#define GAP_DISCONNECT_REASON_TERM_CONNECTION_USER				0x13
#define GAP_DISCONNECT_REASON_TERM_CONNECTION_LOCAL				0x16
#define GAP_DISCONNECT_REASON_TERM_CONNECTION_RESOURCE			0x14
#define GAP_DISCONNECT_REASON_TERM_CONNECTION_POWER				0x15
#define GAP_DISCONNECT_REASON_UNSUPPORTED_REMOTE_FEATURE		0x1A
#define GAP_DISCONNECT_REASON_UNSUPPORTED_PAIRING_KEY			0x29
#define GAP_DISCONNECT_REASON_UNSUPPORTED_CONNECTION_PARAMS		0x3B
#define GAP_DISCONNECT_REASON_CONNECTION_FAILED_TO_ESTABLISH	0x3E

#define GAP_ADDRESS_TYPE_PUBLIC			0x00
#define GAP_ADDRESS_TYPE_RANDOM			0x01
#define GAP_ADDRESS_TYPE_RPA_OR_PUBLIC	0x02
#define GAP_ADDRESS_TYPE_RPA_OR_RANDOM	0x03


#define GAP_ADV_FLAGS_BR_EDR_NOT_SUPPORTED		(1 << 2)
#define GAP_ADV_FLAGS_LE_DISCOVERABILITY_MASK	0x3

#define GAP_ADAPTER_STATE_IDLE				(0x0 << 0)
#define GAP_ADAPTER_STATE_ADV_DISABLED		(0x0 << 0)
#define GAP_ADAPTER_STATE_ADV_ENABLING		(0x1 << 0)
#define GAP_ADAPTER_STATE_ADV_DISABLING		(0x2 << 0)
#define GAP_ADAPTER_STATE_ADV_ENABLED		(0x3 << 0)
#define GAP_ADAPTER_STATE_SCN_DISABLED		(0x0 << 2)
#define GAP_ADAPTER_STATE_SCN_ENABLING		(0x1 << 2)
#define GAP_ADAPTER_STATE_SCN_DISABLING		(0x2 << 2)
#define GAP_ADAPTER_STATE_SCN_ENABLED		(0x3 << 2)
#define GAP_ADAPTER_STATE_BGSCAN_ACTIVE		(0x1 << 4)
#define GAP_ADAPTER_STATE_ADV_RESTARTING	(0x1 << 5)
#define GAP_ADAPTER_STATE_SCN_RESTARTING	(0x1 << 6)
#define GAP_ADAPTER_STATE_DISABLING			(0x1 << 7)

#define GAP_ADAPTER_STATE_ADV_OFFSET	0
#define GAP_ADAPTER_STATE_SCN_OFFSET	2
#define GAP_ADAPTER_STATE_MASK			0x3

#define GAP_CONNECTION_STATE_ACL_DISCONNECTED		0
#define GAP_CONNECTION_STATE_ACL_CONNECTING			1
#define GAP_CONNECTION_STATE_ACL_CONNECTED			2
#define GAP_CONNECTION_STATE_ACL_DISCONNECTING		3
#define GAP_CONNECTION_STATE_LINK_PARAM_UPDATING	4
#define GAP_CONNECTION_STATE_INVALID				5

#define GAP_OPERATION_NONE					0
#define GAP_OPERATION_ADVERTISING			2
#define GAP_OPERATION_FG_SCANNING			3
#define GAP_OPERATION_BG_SCANNING			4
#define GAP_OPERATION_CONNECTING			5
#define GAP_OPERATION_DISCONNECTING			6
#define GAP_OPERATION_UPDATING_CONN_PARAMS	7
#define GAP_OPERATION_UPDATING_WHITELIST	8
#define GAP_OPERATION_DISABLING				9
#define GAP_OPERATION_UPDATING_RL			10
#define GAP_OPERATION_RESOLVING_DIRECT_ADDR	11


#define CM_REQ_OPCODE_START_DISCOVERABLE	API_REQ_OPCODE_START_DISCOVERABLE
#define CM_REQ_OPCODE_STOP_DISCOVERABLE		API_REQ_OPCODE_STOP_DISCOVERABLE
#define CM_REQ_OPCODE_START_SCAN			API_REQ_OPCODE_START_SCAN
#define CM_REQ_OPCODE_STOP_SCAN				API_REQ_OPCODE_STOP_SCAN

#define BLE_RESOLVE_ADDR_MSB				0x40   /*  MSB, bit7, bit6 is 01 to be resolvable random */
#define BLE_RANDSTAT_ADDR_MSB				0xC0   /*  MSB, bit7, bit6 is 01 to be resolvable random */
#define BLE_RESOLVE_ADDR_MASK				0xC0   /* bit 6, and bit7 */
#define BLE_IS_RESOLVE_BDADDR(x)			((x[0] & BLE_RESOLVE_ADDR_MASK) == BLE_RESOLVE_ADDR_MSB)
#define BLE_IS_RANDSTAT_BDADDR(x)			((x[0] & BLE_RESOLVE_ADDR_MASK) == BLE_RANDSTAT_ADDR_MSB)

#if (TARGET_UEFI == TRUE)
#define SCAN_CONN_INTERVAL			0x0030 //30ms
#define SCAN_CONN_WINDOW			0x0030 //30ms
#define CONNECTION_INTERVAL_MIN		0x0006 //7.5ms
#define CONNECTION_INTERVAL_MAX		0x0028 //50ms
#define CONNECTION_LATENCY			0x0000 //0
#define CONNECTION_SUP_TIMEOUT		0x0024 //360ms

#define ADV_FAST_INTERVAL_MIN		0x0030 //30ms
#define ADV_FAST_NC_INTERVAL_MIN	0x00A0 //100ms
#define ADV_SLOW_INTERVAL_MIN		0x0640 //1s
#define ADV_FAST_INTERVAL_MAX		0x0060 //60ms
#define ADV_FAST_NC_INTERVAL_MAX	0x00F0 //150ms
#define ADV_SLOW_INTERVAL_MAX		0x0780 //1.2s

#define SCAN_FAST_INTERVAL			0x0030 //30ms
#define SCAN_FAST_WINDOW			0x0030 //30ms
#define SCAN_SLOW_INTERVAL			0x0090 //90ms
#define SCAN_SLOW_WINDOW			0x0024 //22.5ms

#elif (TARGET_THREADX_RW != TRUE)

#define SCAN_CONN_INTERVAL			0x0030 //30ms
#define SCAN_CONN_WINDOW			0x0030 //30ms
#define CONNECTION_INTERVAL_MIN		0x0006 //7.5ms
#define CONNECTION_INTERVAL_MAX		0x0028 //50ms
#define CONNECTION_LATENCY			0x0000 //0
#define CONNECTION_SUP_TIMEOUT		0x0024 //360ms

#define ADV_FAST_INTERVAL_MIN		0x0030 //30ms
#define ADV_FAST_NC_INTERVAL_MIN	0x00A0 //100ms
#define ADV_SLOW_INTERVAL_MIN		0x0640 //1s
#define ADV_FAST_INTERVAL_MAX		0x0060 //60ms
#define ADV_FAST_NC_INTERVAL_MAX	0x00F0 //150ms
#define ADV_SLOW_INTERVAL_MAX		0x0780 //1.2s

#define SCAN_FAST_INTERVAL			0x0030 //30ms
#define SCAN_FAST_WINDOW			0x0030 //30ms
#define SCAN_SLOW_INTERVAL			0x0800 //1.28s
#define SCAN_SLOW_WINDOW			0x0024 //22.5ms

#else /*(TARGET_THREADX_RW == TRUE)*/

#if (ATP_ADV_DUT || ATP_ADV_1SEC_DUT || ATP_SCAN_CONNECT_DUT)
  #include "atp_testmode_defaults.h"
#else

#define SCAN_CONN_INTERVAL			0x0640 //1s
#define SCAN_CONN_WINDOW			0x0320 //500ms
#define CONNECTION_INTERVAL_MIN		0x0010 //20ms
#define CONNECTION_INTERVAL_MAX		0x0020 //40ms
#define CONNECTION_LATENCY			0x0000 //0
#define CONNECTION_SUP_TIMEOUT		0x0018 //240ms

#define ADV_FAST_INTERVAL_MIN		0x0030 //30ms
#define ADV_FAST_NC_INTERVAL_MIN	0x00A0 //100ms
#define ADV_SLOW_INTERVAL_MIN		0x0640 //1s
#define ADV_FAST_INTERVAL_MAX		0x0060 //60ms
#define ADV_FAST_NC_INTERVAL_MAX	0x00F0 //150ms
#define ADV_SLOW_INTERVAL_MAX		0x0780 //1.2s

#define SCAN_FAST_INTERVAL			0x0030 //30ms
#define SCAN_FAST_WINDOW			0x0030 //30ms
#define SCAN_SLOW_INTERVAL			0x0800 //1.28s
#define SCAN_SLOW_WINDOW			0x0024 //22.5ms

#endif /*(ATP_ADV_1SEC_DUT || ATP_SCAN_CONNECT_DUT) */
#endif /* (TARGET_THREADX_RW != TRUE) */

#if (LE_PING_ENABLE==TRUE)
#define CONNECTION_AUTHPAYLOAD_TIMEOUT	0x0BB8 // 0x0BB8*10ms = 30s
#endif //LE_PING_ENABLE==TRUE
// NOTE: Generally DLE_MIN_TX_xx is also DEFAULT values in the controller.
// Always check with the controller implementation or by reading the default max values supported by controller before setting/updating the default values.
// Updated value should fall in the range.
// Below values are defined for 1Mbps controller LE implementation.
#define DLE_MIN_TX_OCTECTS		0x001B // From the specification, minimum TX Octets supported should be 27 decimal
#define DLE_MIN_TX_TIME			0x0148 // (( (14 byte air packet header * 8 bits) + (DLE_MIN_TX_OCTECTS bytes * 8bits)) * 1 micro seconds for 1Mbps) = 112 + 216 = 328 usec. (0x0148)
#define DLE_MAX_TX_OCTECTS		0x00FB // Spec defined Max value is 251B, controller implementation can be less than 251decimal but should >=27 decimal
#define DLE_MAX_TX_TIME			0x0848 // (( (14 byte air packet header * 8 bits) + (DLE_MAX_TX_OCTECTS bytes * 8bits)) * 1 micro seconds for 1Mbps) = 112 + 2008 = 2120  usec. (0x0848)

#define GAP_RPA_GEN_COMMAND_TIMEOUT_SEC 900
#define ADV_DATA_LEN		31
#define LE_PRIVACY_EN       TRUE
#define LE_PRIVACY_DIS      FALSE

#define PEER_CAR_SUPPORT_ABSENT		0
#define PEER_CAR_SUPPORT_PRESENT	1
#define PEER_CAR_SUPPORT_UNKNOWN	2

INT8 gap_req_handler(interface_req_elem_t* incoming_req);

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

typedef struct
{
	BOOLEAN use_whitelist;
	BOOLEAN background;
	UINT8 type;
	UINT8 flags;
	UINT8 addr_type;
	UINT16 adv_int_min;
	UINT16 adv_int_max;
	UINT32 timeout_msec;
	UINT8 remote_bd_addr[BD_ADDR_LEN];
} cm_start_adv_param_t;

UINT8 gap_get_local_name(gap_adv_scanresp_data_t **dlist, UINT8 *name);
UINT8 gap_add_adv_scanresp_data(gap_adv_scanresp_data_t **dlist, UINT8 length, UINT8 type, UINT8 *data);
void gap_remove_adv_scanresp_data(gap_adv_scanresp_data_t **dlist, UINT8 length, UINT8 type, UINT8 *data);

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

typedef struct
{
	BOOLEAN active;
	BOOLEAN limited;
	BOOLEAN use_whitelist;
	BOOLEAN background;
	UINT8 app_idx;
	UINT16 scan_int;
	UINT16 scan_win;
	trans_id_t trans_id;
	UINT32 timeout_msec;
	UINT16 filter_uuids[MAX_NUM_SCAN_FILTER_UUIDS];
} cm_start_scan_param_t;

INT8 gap_create_connection(UINT8 *remote_bdaddr, UINT8 addr_type, UINT16 scan_int, UINT16 scan_win, UINT16 conn_int_min, UINT16 conn_int_max, UINT16 conn_lat, UINT16 sup_timeout);

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

INT8 gap_terminate_connection(UINT8 connected_device_list_idx, UINT8 reason);
INT8 gap_enable_host_privacy(UINT8 enable);

#if (TEST_CODE == TRUE && LE_PING_ENABLE==TRUE)

INT8 gap_read_authpayload_timeout(UINT8 conn_id);
typedef struct
{
	UINT8 conn_id;
	trans_id_t trans_id;
} cm_read_authpayload_timeout_t;

INT8 gap_write_authpayload_timeout(UINT8 conn_id, UINT16 authpayload_timeout_ms);
typedef struct
{
	UINT8 conn_id;
	UINT16 authpayload_timeout_ms;
	trans_id_t trans_id;
} cm_write_authpayload_timeout_t;
#endif //LE_PING_ENABLE && TEST_CODE

typedef struct
{
	UINT8 conn_id;
	UINT16 tx_octets;
} cm_set_data_len_t;

INT8 gap_set_data_len(UINT8 conn_id, UINT16 tx_octets);

INT8 gap_req_update_conn_params(UINT8 connected_device_list_idx, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout);
INT8 gap_add_to_whitelist(UINT8 addr_type, UINT8 *bdaddr);
INT8 gap_remove_from_whitelist(UINT8 addr_type, UINT8 *bdaddr);

//Callbacks
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
INT8 gap_handle_adv_report(UINT8* buffer, UINT16 len, BOOLEAN directed);
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
INT8 gap_handle_command_complete(UINT16 opcode, UINT8 status, UINT8* evt, UINT8 len);
INT8 gap_handle_conn_complete(UINT8* buffer, UINT16 len, BOOLEAN enhanced);
INT8 gap_handle_disconn_complete(UINT8* buffer, UINT16 len);
INT8 gap_handle_conn_param_update_cmpl(UINT8* buffer, UINT16 len);
INT8 gap_handle_conn_read_remote_feat_cmpl(UINT8* buffer, UINT16 len);
INT8 gap_handle_remote_conn_param_req(UINT8* buffer, UINT16 len);
INT8 gap_update_conn_params(UINT8 connected_device_list_idx, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout);
#if (LE_PING_ENABLE==TRUE)
INT8 gap_handle_authpayload_timeout_exp_evt(UINT8* buffer, UINT16 len);
#endif// LE_PING_ENABLE==TRUE
INT8 gap_handle_data_len_change_evt(UINT8* buffer, UINT16 len);

//Init/deinit
INT8 gap_init();
void gap_cleanup();
void remote_command_timer_start(UINT8 connected_device_idx);

#endif /* GAP_H_ */
