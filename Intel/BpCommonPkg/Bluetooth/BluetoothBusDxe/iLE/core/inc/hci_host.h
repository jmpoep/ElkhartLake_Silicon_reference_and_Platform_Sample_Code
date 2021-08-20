/** @file
  HCI protocol constant and function prototype declaration.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef HCI_H
#define HCI_H

#include "config_host.h"
#include "bt_types.h"
#include "device_struct.h"

#define HCI_CMD 1
#define HCI_ACL 2
#define HCI_SCO 3
#define HCI_EVT 4

#define HCI_CON_ROLE_MASTER 0
#define HCI_CON_ROLE_SLAVE 1
#define HCI_CMD_TIMEOUT_MS	2000

INT8 hci_host_init(char* device, int ispeed);
void hci_init_on_wakeup();
void hci_cleanup();
INT8 hci_send_cmd(UINT16 opcode, UINT8* p_buf, UINT8 len);
INT8 hci_send_acl_data(UINT16 acl_handle, UINT8* buffer, UINT16 len);
INT8 hci_recv_buffer(UINT8* buffer, UINT16 len);

#define HCI_CMD_GRP_LINK_CONTROL        (0x01 << 10)            /* 0x0400 */
#define HCI_CMD_GRP_LINK_POLICY         (0x02 << 10)            /* 0x0800 */
#define HCI_CMD_GRP_HOST_CONT_BASEBAND  (0x03 << 10)            /* 0x0C00 */
#define HCI_CMD_GRP_INFORMATIONAL_PARAM (0x04 << 10)            /* 0x1000 */
#define HCI_CMD_GRP_STATUS_PARAM        (0x05 << 10)            /* 0x1400 */
#define HCI_CMD_GRP_VENDOR_SPECIFIC     (0x3F << 10)            /* 0xFC00 */
#define HCI_CMD_GRP_BLE                 (0x08 << 10)

#define HCI_CMD_RESET 					(0x03 | HCI_CMD_GRP_HOST_CONT_BASEBAND)
#define HCI_CMD_SET_EVENT_MASK              (0x01 | HCI_CMD_GRP_HOST_CONT_BASEBAND)
#define HCI_CMD_SET_EVENT_MASK_PAGE_2       (0x63 | HCI_CMD_GRP_HOST_CONT_BASEBAND)
#define HCI_CMD_WRITE_LE_HOST_SUPPORTED 	(0x6D | HCI_CMD_GRP_HOST_CONT_BASEBAND)
#define HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT	(0x7B | HCI_CMD_GRP_HOST_CONT_BASEBAND)
#define HCI_CMD_WRITE_AUTHPAYLOAD_TIMEOUT 	(0x7C | HCI_CMD_GRP_HOST_CONT_BASEBAND)

#define HCI_CMD_READ_LOCAL_VERSION_INFO (0x01 | HCI_CMD_GRP_INFORMATIONAL_PARAM)
#define HCI_CMD_READ_LOCAL_FEAT			(0x03 | HCI_CMD_GRP_INFORMATIONAL_PARAM)
#define HCI_CMD_READ_BUFFER_SIZE		(0x05 | HCI_CMD_GRP_INFORMATIONAL_PARAM)
#define HCI_CMD_READ_BD_ADDR			(0x09 | HCI_CMD_GRP_INFORMATIONAL_PARAM)

#define HCI_CMD_READ_RSSI                   (0x05 | HCI_CMD_GRP_STATUS_PARAM)
#define HCI_CMD_DISCONNECT                  (0x06 | HCI_CMD_GRP_LINK_CONTROL)

#define HCI_CMD_LE_SET_EVENT_MASK			(0x01 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_BUFFER_SIZE			(0x02 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_LOCAL_SUPPORTED_FEAT (0x03 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_RANDOM_ADDRESS		(0x05 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_ADV_PARAM			(0x06 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_ADV_CHN_TX_PWR		(0x07 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_ADV_DATA				(0x08 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_SCAN_RESP_DATA		(0x09 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_ADV_ENABLE			(0x0A | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_SCAN_PARAM			(0x0B | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_SCAN_ENABLE			(0x0C | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_CREATE_CONN				(0x0D | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_CREATE_CONN_CANCEL		(0x0E | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_WHITE_LIST_SIZE		(0x0F | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_CLEAR_WHITE_LIST			(0x10 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_ADD_DEV_TO_WHITE_LIST	(0x11 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_REMOVE_DEV_FRM_WHITE_LIST (0x12 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_CONN_UPDATE				(0x13 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_HOST_CHN_CLASSIFICATION (0x14 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_CHN_MAP				(0x15 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_REMOTE_USED_FEAT	(0x16 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_ENCRYPT					(0x17 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_RAND						(0x18 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_START_ENCRYPT			(0x19 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_LONG_TERM_KEY_REQ_REPLY	(0x1A | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_LONG_TERM_KEY_NEG_REPLY	(0x1B | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_SUPPORTED_STATES	(0x1C | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_REM_CONN_PARAM_REQ_REPLY	(0x20 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_REM_CONN_PARAM_REQ_REJCT	(0x21 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_DATA_LEN				(0x22 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_WRITE_SUG_DEF_DATA_LEN	(0x24 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_ADD_DEV_TO_RESOLVING_LIST (0x27 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_REMOVE_DEV_FROM_RESOLVING_LIST (0x28 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_CLEAR_RESOLVING_LIST 	(0x29 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_RESOLVING_LIST_SIZE (0x2A | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_PEER_RESOLVABLE_ADDR (0x2B | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_LOCAL_RESOLVABLE_ADDR (0x2C | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_ADDR_RESOLUTION_EN	 (0x2D | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_RESOLVABLE_PRIVATE_ADDR_TOUT	 (0x2E | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_MAX_DATA_LEN		(0x2F | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_READ_LOCAL_P256_PUBLIC_KEY		(0x25 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_GENERATE_DHKEY					(0x26 | HCI_CMD_GRP_BLE)
#define HCI_CMD_LE_SET_PRIVACY_MODE (0x4e | HCI_CMD_GRP_BLE)

#define HCI_BLE_EVENT                   				0x03E
/* ULP Event sub code */
#define HCI_BLE_CONN_COMPLETE_EVT           0x01
#define HCI_BLE_ADV_PKT_RPT_EVT             0x02
#define HCI_BLE_LL_CONN_PARAM_UPD_EVT       0x03
#define HCI_BLE_READ_REMOTE_FEAT_CMPL_EVT   0x04
#define HCI_BLE_LTK_REQ_EVT                 0x05
#define HCI_BLE_REMOTE_CONN_PARAM_REQ		0x06
#define HCI_BLE_DATA_LEN_CHANGE_EVT			0x07
#define HCI_BLE_READ_LOCAL_P256_PUBLIC_KEY_CMPL_EVT		0x08
#define HCI_BLE_GENERATE_DHKEY_EVT						0x09
#define HCI_BLE_ENHANCED_CONN_COMPLETE_EVT	0x0A
#define HCI_BLE_DIRECT_ADV_REPORT_EVT		0x0B
#define HCI_HARDWARE_ERROR					0x10
#define HCI_NUM_COMPL_DATA_PKTS_EVT         0x13

#define HCI_AUTH_PAYLOAD_TIMEOUT_EXP_EVT				0x57
#define HCI_EVENT_CMD_CMPL								0x0E
#define HCI_EVENT_CMD_STATUS							0x0F
#define HCI_EVENT_DISCON_CMPL							0x05
#define HCI_EVENT_LE_META_EVENT							0x3E
#define HCI_SUB_EVENT_LE_CONN_COMPL						0x01
#define HCI_SUB_EVENT_LE_ADV_REPORT						0x02
#define HCI_SUB_EVENT_LE_CONN_UPDATE_COMPL 				0x03
#define HCI_SUB_EVENT_LE_READ_REMOTE_USED_FEAT_COMPL 	0x04
#define HCI_SUB_EVENT_LE_LONG_TERM_KEY_REQ				0x05
#define HCI_EVENT_ENC_CHG								0x08
#define HCI_EVENT_KEY_REFRESH_COMPL						0x30

#define HCI_EVENT_STATUS_SUCCESS							0
#define HCI_EVENT_STATUS_CONNECTION_LIMIT_EXCEEDED			9
#define HCI_EVENT_STATUS_CONTROLLER_BUSY					58
#define HCI_EVENT_STATUS_COMMAND_DISALLOWED					12
#define HCI_EVENT_CMPL_STATUS_BIT_OFFSET					5
#define HCI_EVENT_STATUS_STATUS_BIT_OFFSET					2
#define HCI_SUB_EVENT_LE_CONN_COMPL_STATUS_BIT_OFFSET		3

/* HCI Command parameter length values */
#define HCI_CMD_RESET_PARAM_LEN			  				0
#define HCI_CMD_READ_LOCAL_FEAT_PARAM_LEN 				0
#define HCI_CMD_WRITE_LE_HOST_SUPPORTED_PARAM_LEN 		2
#define HCI_CMD_SET_EVENT_MASK_PARAM_LEN				8
#define HCI_CMD_SET_EVENT_MASK_PAGE_2_PARAM_LEN			8
#define HCI_CMD_READ_BUFFER_SIZE_PARAM_LEN  			0
#define HCI_CMD_LE_READ_BUFFER_SIZE_PARAM_LEN			0
#define HCI_CMD_READ_BD_ADDR_PARAM_SIZE	 				0
#define HCI_CMD_LE_READ_LOCAL_SUPPORTED_FEAT_PARAM_SIZE 0
#define HCI_CMD_LE_READ_REMOTE_USED_FEAT_PARAM_SIZE		2
#define HCI_CMD_READ_AUTHPAYLOAD_TIMEOUT_PARAM_SIZE		2 // size of connection_handle
#define HCI_CMD_WRITE_AUTHPAYLOAD_TIMEOUT_PARAM_SIZE	4 // size of connection_handle + authenticated_payload_timeout
#define HCI_CMD_LE_SET_ADV_PARAM_PARAM_SIZE 			15
#define HCI_CMD_LE_SET_ADV_DATA_PARAM_SIZE 				32
#define HCI_CMD_LE_SET_SCAN_RESP_DATA_PARAM_SIZE		32
#define HCI_CMD_LE_SET_ADV_ENABLE_PARAM_SIZE			1
#define HCI_CMD_LE_SET_SCAN_PARAM_PARAM_SIZE			7
#define HCI_CMD_LE_SET_SCAN_ENABLE_PARAM_SIZE			2
#define HCI_CMD_LE_CREATE_CONN_PARAM_SIZE				25
#define HCI_CMD_LE_CREATE_CONN_CANCEL_PARAM_SIZE		0
#define HCI_CMD_DISCONNECT_PARAM_SIZE					3
#define HCI_CMD_LE_SET_RANDOM_ADDRESS_PARAM_SIZE		6
#define HCI_CMD_LE_READ_WHITE_LIST_SIZE_PARAM_SIZE		0
#define HCI_CMD_LE_CLEAR_WHITE_LIST_PARAM_SIZE			0
#define HCI_CMD_LE_ADD_DEV_TO_WHITE_LIST_PARAM_SIZE		7
#define HCI_CMD_LE_REMOVE_DEV_FRM_WHITE_LIST_PARAM_SIZE	7
#define HCI_CMD_LE_CONN_UPDATE_PARAM_SIZE				14
#define HCI_CMD_LE_REM_CONN_PARAM_REQ_REPLY_PARAM_SIZE	14
#define HCI_CMD_LE_REM_CONN_PARAM_REQ_REJCT_PARAM_SIZE	3
#define HCI_CMD_LE_RAND_PARAM_SIZE						0
#define HCI_CMD_LE_START_ENCRYPT_PARAM_SIZE				28
#define HCI_CMD_LE_ENCRYPT_PARAM_SIZE					32
#define HCI_CMD_LE_LONG_TERM_KEY_REQ_REPLY_PARAM_SIZE	18
#define HCI_CMD_LE_LONG_TERM_KEY_NEG_REPLY_PARAM_SIZE	2
#define HCI_CMD_LE_ADD_DEV_TO_RESOLVING_LIST_PARAM_SIZE	39
#define HCI_CMD_LE_REMOVE_DEV_FROM_RESOLVING_LIST_PARAM_SIZE	7
#define HCI_CMD_LE_CLEAR_RESOLVING_LIST_PARAM_SIZE		0
#define HCI_CMD_LE_READ_RESOLVING_LIST_SIZE_PARAM_SIZE	0
#define HCI_CMD_LE_READ_PEER_RESOLVABLE_ADDR_PARAM_SIZE	7
#define HCI_CMD_LE_READ_LOCAL_RESOLVABLE_ADDR_PARAM_SIZE	7
#define HCI_CMD_LE_SET_ADDR_RESOLUTION_EN_PARAM_SIZE	1
#define HCI_CMD_LE_SET_RESOLVABLE_PRIVATE_ADDR_TOUT_PARAM_SIZE	2
#define HCI_CMD_LE_SET_DATA_LEN_PARAM_SIZE				6
#define HCI_CMD_LE_WRITE_SUG_DEF_DATA_LEN_PARAM_SIZE	4
#define HCI_CMD_LE_READ_MAX_DATA_LEN_PARAM_SIZE			0
#define HCI_CMD_LE_READ_LOCAL_P256_PUBLIC_KEY_PARAM_SIZE	0
#define HCI_CMD_LE_GENERATE_DHKEY_PARAM_SIZE				64
#define HCI_EVT_LE_CONN_PARAM_UPDATE_PARAM_SIZE			9
#define HCI_CMD_VS_WRITE_BDADDR_PARAM_SIZE				9
#define HCI_LE_HOST_SUPPORTED 1
#define HCI_LE_SIMUL_HOST_SUPPORTED 0
#define HCI_CMD_LE_SET_PRIVACY_MODE_SIZE	8

#define HCI_LOCAL_FEATURE_MASK_CONTROLLER_LE_SUPPORTED_OFFSET 4
#define HCI_LOCAL_FEATURE_MASK_CONTROLLER_LE_SUPPORTED_MASK 0x40
#define HCI_LE_FEATURE_CONN_PARAM_REQ_PROCEDURE_OFFSET		0
#define HCI_LE_FEATURE_CONN_PARAM_REQ_PROCEDURE_MASK		0x02
#define HCI_LE_FEATURE_SLAVE_INIT_FEAT_EXCHANGE_OFFSET		0
#define HCI_LE_FEATURE_SLAVE_INIT_FEAT_EXCHANGE_MASK		0x08
#define HCI_LE_FEATURE_LL_PRIVACY_OFFSET					0
#define HCI_LE_FEATURE_LL_PRIVACY_MASK						0x40
#define HCI_LE_FEATURE_DATA_PKT_LEN_EXTN_OFFSET				0
#define HCI_LE_FEATURE_DATA_PKT_LEN_EXTN_MASK				0x20

#define LE_NETWORK_PRIVACY_MODE	0
#define LE_DEVICE_PRIVACY_MODE	1

#define LL_PRIVACY_IS_SUPPORTED (g_local_adapter.ble_local_features[HCI_LE_FEATURE_LL_PRIVACY_OFFSET] & HCI_LE_FEATURE_LL_PRIVACY_MASK)

#define HCI_CMD_VS_WRITE_BDADDR		(0x8B | HCI_CMD_GRP_VENDOR_SPECIFIC)

#if (TARGET_THREADX == TRUE)
#define GET_OCF(x) ((x & 0x00FF))
#define PROFILE_OPERATION_DO_DEVICE_DISCOVERY			(0x7B | HCI_CMD_GRP_VENDOR_SPECIFIC)
#define PROFILE_OPERATION_DO_START_USE_CASE				(0x7C | HCI_CMD_GRP_VENDOR_SPECIFIC)
#define PROFILE_OPERATION_DO_STOP_USE_CASE				(0x7D | HCI_CMD_GRP_VENDOR_SPECIFIC)
#define PROFILE_OPERATION_ASYNC_EVENT					(0x7E | HCI_CMD_GRP_VENDOR_SPECIFIC)
#define PROFILE_OPERATION_DO_WRITE_ALERT_LEVEL			(0x81 | HCI_CMD_GRP_VENDOR_SPECIFIC)

#define HCI_CMD_VS_MANUF_MODE							(0x11 | HCI_CMD_GRP_VENDOR_SPECIFIC)
#define HCI_CMD_VS_WRITE_BD_DATA						(0x2F | HCI_CMD_GRP_VENDOR_SPECIFIC)


#define PROFILE_COMMAND_DO_DEVICE_DISCOVERY_PARAM_LEN	1
#define PROFILE_COMMAND_DO_START_USE_CASE_PARAM_LEN		7
#define PROFILE_COMMAND_DO_STOP_USE_CASE_PARAM_LEN		7

#define PROFILE_EVENT_DEVICE_DISCOVERY_COMPLETED		0x01
#define PROFILE_EVENT_HRP_DATA							0x02
#define PROFILE_EVENT_HRP_DATA_PARAM_LEN				3
#define PROFILE_EVENT_ALERT_LEVEL_DATA					0x03
#define PROFILE_EVENT_ALERT_LEVEL_DATA_PARAM_LEN		2
#define PROFILE_EVENT_STACK_INIT_COMPLETED				0x04
#define PROFILE_EVENT_STACK_INIT_COMPLETED_PARAM_LEN	2
#define HCI_CMD_VS_MANUF_MODE_PARAM_LEN					2
#define HCI_CMD_VS_WRITE_BD_DATA_PARAM_LEN				0X50


#endif /* (TARGET_THREADX == TRUE) */

/**************************************************************
 * Function declarations for BTSNOOP
 **************************************************************/
#if (BTSNOOPDISP_INCLUDED == TRUE)
INT8 btsnoop_log_open(char *btsnoop_logfile);
INT8 btsnoop_log_close(void);
void btsnoop_hci_cmd(UINT8 *p);
void btsnoop_hci_evt(UINT8 *p);
void btsnoop_acl_data(UINT8 *p, UINT8 is_rcvd);
#endif
void btsnoop_log(const char* p);

/**************************************************************
 * Function declarations for sending HCI commands
 **************************************************************/
INT8 hci_send_data(connected_device_t *device, UINT8 pb_flag, UINT8* data_buffer, UINT16 data_length);

INT8 hci_set_event_mask(UINT8 *event_mask);
INT8 hci_ble_set_event_mask_page_2(UINT8 *event_mask);
INT8 hci_ble_set_event_mask(UINT8 *event_mask);
INT8 hci_read_buffer_size(void);
INT8 hci_ble_read_buffer_size(void);
INT8 hci_read_bd_addr(void);
INT8 hci_ble_read_local_feat(void);
INT8 hci_ble_read_white_list_size(void);
INT8 hci_ble_read_remote_feat(UINT16 handle);
INT8 hci_ble_write_host_supported(UINT8 le_host_spt, UINT8 simul_le_host_spt);
#if (LE_PING_ENABLE==TRUE)
INT8 hci_ble_read_authpayload_timeout(UINT16 handle);
INT8 hci_ble_write_authpayload_timeout(UINT16 handle, UINT16 authpayload_timeout);
#endif //LE_PING_ENABLE==TRUE

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
INT8 hci_ble_write_adv_params(UINT16 adv_int_min, UINT16 adv_int_max,
		UINT8 adv_type, UINT8 addr_type_own, UINT8 addr_type_dir,
		UINT8 *direct_bda, UINT8 channel_map, UINT8 adv_filter_policy);
INT8 hci_ble_set_adv_data(UINT8 data_len, UINT8 *p_data);
INT8 hci_ble_set_scan_rsp_data(UINT8 data_len, UINT8 *p_scan_rsp);
INT8 hci_ble_set_adv_enable(UINT8 adv_enable);
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
INT8 hci_ble_set_scan_params(UINT8 scan_type, UINT16 scan_int,
		UINT16 scan_win, UINT8 addr_type_own, UINT8 scan_filter_policy);
INT8 hci_ble_set_scan_enable(UINT8 scan_enable, UINT8 duplicate);
INT8 hci_ble_create_ll_conn(UINT16 scan_int, UINT16 scan_win,
		UINT8 init_filter_policy, UINT8 addr_type_peer, UINT8* bda_peer,
		UINT8 addr_type_own, UINT16 conn_int_min, UINT16 conn_int_max,
		UINT16 conn_latency, UINT16 conn_timeout, UINT16 min_ce_len,
		UINT16 max_ce_len);
INT8 hci_ble_cancel_create_ll_conn();
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

INT8 hci_read_local_feat();
INT8 hci_reset();
INT8 hci_disconnect(UINT16 handle, UINT8 reason);
#if (GAP_RANDOM_ADDDRESS_SUPPORT == TRUE)
INT8 hci_ble_set_random_addr(UINT8* random_bda);
#endif
INT8 hci_ble_read_white_list_size(void);
INT8 hci_ble_clear_white_list(void);
INT8 hci_ble_add_to_white_list(UINT8 addr_type, UINT8* bda);
INT8 hci_ble_remove_from_white_list(UINT8 addr_type, UINT8* bda);
INT8 hci_ble_upd_ll_conn_params(UINT16 handle, UINT16 conn_int_min,
		UINT16 conn_int_max, UINT16 conn_latency, UINT16 conn_timeout,
		UINT16 min_ce_len, UINT16 max_ce_len);
INT8 hci_ble_rem_conn_param_req_rep(UINT16 handle, UINT16 conn_int_min,
		UINT16 conn_int_max, UINT16 conn_latency, UINT16 conn_timeout,
		UINT16 min_ce_len, UINT16 max_ce_len);
INT8 hci_ble_rem_conn_param_req_rej(UINT16 handle, UINT8 reason);
INT8 hci_ble_rand(void);
#if (INTERNAL_AES == FALSE)
INT8 hci_ble_encrypt(UINT8* key,UINT8* plain_text);
#endif
INT8 hci_ble_ltk_req_reply(UINT16 conn_handle, UINT8* ltk);
INT8 hci_ble_ltk_neg_reply(UINT16 conn_handle);
INT8 hci_ble_start_encryption(UINT16 conn_handle,UINT8* random_num,UINT16 evid,UINT8* ltk);
#if (CONTROLLER_ECDH == TRUE)
INT8 hci_ble_read_local_p256_public_key();
INT8 hci_ble_generate_dhkey(UINT8 *pub_key_x,UINT8 *pub_key_y, UINT8 len);
#endif /* CONTROLLER_ECDH */
INT8 hci_stack_init_completed(UINT8 status);
INT8 hci_manuf_mode(UINT8 status);
INT8 hci_write_bd_data();
#if (CONTROLLER_PRIVACY == TRUE)
INT8 hci_ble_set_privacy_mode(UINT8 addr_type, UINT8* bda, UINT8 privacy_mode);
INT8 hci_ble_add_device_to_resolving_list(UINT8 addr_type, UINT8* bda, UINT8* peer_irk, UINT8* local_irk);
INT8 hci_ble_remove_device_from_resolving_list(UINT8 addr_type, UINT8* bda);
INT8 hci_ble_clear_resolving_list(void);
INT8 hci_ble_read_resolving_list_size(void);
INT8 hci_ble_read_peer_resolvable_addr(UINT8 addr_type, UINT8* bda);
INT8 hci_ble_read_local_resolvable_addr(UINT8 addr_type, UINT8* bda);
INT8 hci_ble_set_addr_resolution_enable(UINT8 enable);
INT8 hci_ble_set_rpa_tout(UINT16 rpa_tout);
#endif /* CONTROLLER_PRIVACY */
INT8 hci_ble_set_data_len(UINT16 handle, UINT16 tx_octets, UINT16 tx_time);
INT8 hci_ble_write_sug_def_data_len(UINT16 tx_octets, UINT16 tx_time);
INT8 hci_ble_read_max_data_len(void);
INT8 hci_ble_set_bdaddr(UINT8 *bda);

#endif //#ifndef HCI_H
