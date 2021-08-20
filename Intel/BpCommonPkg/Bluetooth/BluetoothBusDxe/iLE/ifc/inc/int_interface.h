/** @file
  Header file with constants required in interface but not exposed to apps.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#ifndef INT_INTERFACE_H_
#define INT_INTERFACE_H_

#include "bt_types.h"
#include "utils.h"
#include "osa_types.h"

#define API_REQ_OPCODE_REGISTER_APPLICATION							1
#define API_REQ_OPCODE_DEREGISTER_APPLICATION						2

#define API_REQ_OPCODE_SET_ADVERTISEMENT_DATA						5
#define API_REQ_OPCODE_REMOVE_ADVERTISEMENT_DATA					6
#define API_REQ_OPCODE_SET_SCAN_RESPONSE_DATA						7
#define API_REQ_OPCODE_REMOVE_SCAN_RESPONSE_DATA					8
#define API_REQ_OPCODE_START_DISCOVERABLE							9
#define API_REQ_OPCODE_STOP_DISCOVERABLE							10
#define API_REQ_OPCODE_START_SCAN									11
#define API_REQ_OPCODE_STOP_SCAN									12
#define API_REQ_OPCODE_SET_LOCAL_DEVICE_NAME						13
#define API_REQ_OPCODE_CONNECT										14
#define API_REQ_OPCODE_DISCONNECT									15

#define API_REQ_OPCODE_ADD_SERVICE									16
#define API_REQ_OPCODE_ADD_INCLUDED_SERVICE							17
#define API_REQ_OPCODE_ADD_CHARACTERISTIC							18
#define API_REQ_OPCODE_ADD_DESCRIPTOR								19
#define API_REQ_OPCODE_START_SERVICE								20
#define API_REQ_OPCODE_REMOVE_SERVICE								21

#define API_REQ_OPCODE_DISCOVER_PRIMARY_SERVICE						26
#define API_REQ_OPCODE_DISCOVER_INCLUDED_SERVICE					27
#define API_REQ_OPCODE_DISCOVER_CHARACTERISTIC						28
#define API_REQ_OPCODE_DISCOVER_DESCRIPTOR							29

#define API_REQ_OPCODE_READ_ATTRIBUTE_VALUE							31
#define API_REQ_OPCODE_WRITE_ATTRIBUTE_VALUE						32
#define API_REQ_OPCODE_REGISTER_NOTIFICATION						33
#define API_REQ_OPCODE_SEND_ATTRIBUTE_READ_RESPONSE					34
#define API_REQ_OPCODE_SEND_ATTRIBUTE_WRITE_RESPONSE				35
#define API_REQ_OPCODE_SEND_NOTIFICATION							36
#define API_REQ_OPCODE_SET_SERVICE_CHANGE_CONFIG					37

#define API_REQ_OPCODE_GET_ATT_MTU_SIZE								46
#define API_REQ_OPCODE_SET_ATT_MTU_SIZE								47

#define API_REQ_OPCODE_CREATE_BOND									51
#define API_REQ_OPCODE_REMOVE_BOND									52
#define API_REQ_OPCODE_SEND_PASSKEY									53
#define API_REQ_OPCODE_SEND_AUTHORIZATION							54
#define API_REQ_OPCODE_SMP_REGISTER									55
#define API_REQ_OPCODE_SET_ATTRIBUTE_VALUE							56
#define API_REQ_OPCODE_ADD_TO_WHITELIST								57
#define API_REQ_OPCODE_REMOVE_FROM_WHITELIST						58
#define API_REQ_OPCODE_CLEAR_WHITELIST								59
#define API_REQ_OPCODE_SIGN_DATA									60
#define API_REQ_OPCODE_GAP_CONN_PARAMS_UPDATE						61
#define API_REQ_OPCODE_SIGN_VERIFY									62
#define API_REQ_OPCODE_RPA_GENERATE									63
#define API_REQ_OPCODE_RPA_RESOLVE									64
#define API_REQ_OPCODE_INIT_SMP										65
#define API_REQ_OPCODE_NC_RESULT									66
#define API_REQ_OPCODE_ADD_TO_RESOLVINGLIST							67
#define API_REQ_OPCODE_REMOVE_FROM_RESOLVINGLIST					68
#define API_REQ_OPCODE_CLEAR_RESOLVINGLIST							69

#define RX_REQ_OPCODE_HCI_MSG										71
#define TX_REQ_OPCODE_HCI_MSG										72
#define TX_REQ_OPCODE_VSHCI_MSG										73
#define API_REQ_OPCODE_ENABLE_PRIVACY								74
#define API_REQ_OPCODE_AUTO_CONNECT									75

#if (L2CAP_COC==TRUE)
#define API_REQ_OPCODE_L2CAP_COC_CREATE_CONNECTION				81
#define API_REQ_OPCODE_L2CAP_COC_REGISTER						82
#define API_REQ_OPCODE_L2CAP_COC_DISCONNECT						83
#define API_REQ_OPCODE_L2CAP_COC_SEND_DATA						84
#endif // L2CAP_COC

#define API_REQ_OPCODE_SET_DATA_LEN								85

/* Storage related apis*/

#define API_REQ_OPCODE_STORAGE_REGISTER							90
#define API_REQ_OPCODE_KEY_RESPONSE									91

#if (TEST_CODE == TRUE)
#define API_REQ_OPCODE_TEST_OPCODE_SEND_LONG_READ_INVALID_OFFSET	105
#if (LE_PING_ENABLE==TRUE)
#define API_REQ_OPCODE_TEST_READ_AUTHPAYLOAD_TIMEOUT				106
#define API_REQ_OPCODE_TEST_WRITE_AUTHPAYLOAD_TIMEOUT				107
#endif //LE_PING_ENABLE
#define API_REQ_OPCODE_TEST_OPCODE_BDADDR_SET						108
#endif

/**
 * Application API mailbox element structure
 */
typedef struct
{
	UINT8 req_opcode;
	UINT8 conn_id;
	UINT32 parameter[0];
} interface_req_elem_t;

typedef struct
{
	osa_timeout_func_t cback;
	osa_timer_arg_t arg;
}timer_expire_elem_t;

typedef struct
{
	UINT8 value_len;
	UINT8 value[0];
} rx_hci_msg_param_t;

typedef struct
{
	UINT8 buffer_len;
	UINT16 opcode;
	UINT8 *buffer;
} tx_hci_send_msg_param_t;

#if (TEST_CODE == TRUE)
	/* Needed for VSC HCI passthrough*/
typedef struct
{
	UINT8 *buf;
}tx_vshci_send_msg_param_t;
#endif

typedef struct
{
	UINT8 enable_privacy;
}cm_privacy_state_param_t;

void rx_req_hci_evt_msg(UINT8* value, UINT8 value_len);
void gap_cleanup_complete_cb();
void timer_expire_evt_msg(osa_timeout_func_t cback, osa_timer_arg_t arg);
interface_req_elem_t* get_interface_req_buffer(UINT8 opcode, UINT8 conn_id, UINT16 len);
void do_app_init();
INT8 interface_handler();

#if (TARGET_UEFI == TRUE)
void fw_dw_finish(BOOLEAN status);
#endif

#endif /* INT_INTERFACE_H_ */
