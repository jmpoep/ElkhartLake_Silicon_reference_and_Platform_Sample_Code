/** @file
  A4WP server header definitions.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef A4WP_SRV_H_
#define A4WP_SRV_H_

#if (TARGET_THREADX == TRUE)
#include "..\app\a4wp\loc_exp\a4wp_main.h"
#endif

/* A4WP Request queue size */
#define A4WP_REQ_QUEUE_LEN 						0x10
/* A4WP Notification  timeout in msec*/
#define A4WP_SRV_NOTIFY_TIMEOUT					1000

/* Wireless power Transfer (A4WP) service */
#define WPT_SERVICE_UUID						0xFFFE
#define PRU_CTRL_CHARACTERISTIC_UUID			0xE670
#define PTU_STATIC_PARAM_CHARACTERISTIC_UUID	(PRU_CTRL_CHARACTERISTIC_UUID + 1)
#define PRU_ALERT_PARAM_CHARACTERISTIC_UUID		(PRU_CTRL_CHARACTERISTIC_UUID + 2)
#define PRU_STATIC_PARAM_CHARACTERISTIC_UUID	(PRU_CTRL_CHARACTERISTIC_UUID + 3)
#define PRU_DYNAMIC_PARAM_CHARACTERISTIC_UUID	(PRU_CTRL_CHARACTERISTIC_UUID + 4)
#define CLIENT_CHAR_CONFIG_UUID					0x2902

/* att id value index */
#define PRU_CTRL_CHARACTERISTIC_ID					0
#define PTU_STATIC_PARAM_CHARACTERISTIC_ID			1
#define PRU_ALERT_PARAM_CHARACTERISTIC_ID			2
#define PRU_STATIC_PARAM_CHARACTERISTIC_ID			3
#define PRU_DYNAMIC_PARAM_CHARACTERISTIC_ID			4
#define CLIENT_CHAR_CONFIG_ID						5
#define A4WP_SRV_ATT_MAX_ID							6

/* A4WP Service parameters length */
#define PRU_CTRL_CHAR_LEN						0x05
#define PTU_STATIC_PARAM_CHAR_LEN				0x11
#define PRU_ALERT_CHAR_LEN						0x01
#define PRU_STATIC_PARAM_CHAR_LEN				0x14
#define PRU_DYNAMIC_PARAM_CHAR_LEN				0x14

/*A4WP Message opcodes */
#define A4WP_APP_REGISTERED						0x00
#define A4WP_BT_CORE_STACK_INIT					0x01
#define A4WP_SERVICE_STARTED					0x02
#define A4WP_CONNECTED							0x03
#define A4WP_DISCONNECTED						0x04
#define A4WP_ATTR_READ_REQ						0x05
#define A4WP_ATTR_WRITE_REQ						0x06
#define A4WP_NOTIFY_REQ							0x07
#define A4WP_IND_REQ							0x08
#define A4WP_IND_CFM_RECVD						0x09
#define A4WP_START_ADV_REQ						0x0A
#define A4WP_STOP_ADV_REQ						0x0B
#define A4WP_UPDATE_DYN_PARAM_REQ				0x0C
#define A4WP_DISCONNECT_REQ						0x0D

#define A4WP_SRV_NOTIFICATION_FLAG				0x01
#define A4WP_SRV_INDICATION_FLAG				0x02

/* Maximum profile response time in msec */
#define A4WP_SRV_MAX_RESP_TIME					50

typedef struct
{
	UINT8 opcode;
	UINT8 *param;
}a4wp_msg_t;

typedef struct
{
	UINT8 conn_id;
	UINT8 att_opcode;
	UINT16 att_id;
	UINT16 offset;
}a4wp_attr_read_req_t;

typedef struct
{
	UINT8 conn_id;
	UINT8 att_opcode;
	UINT16 att_id;
	UINT16 offset;
	buffer_t buffer;
}a4wp_attr_write_req_t;

typedef struct
{
	//gatt_characteristic_t *characteristic;
	UINT8 remote_bd_addr[BD_ADDR_LEN];
}a4wp_ind_cfm_t;

/* PRU control characteristic structure */
typedef _packed_struct_
{
	UINT8 enables;
	UINT8 permissions;
	UINT8 time_set;
	UINT8 rserved[2];
}pru_ctrl_char_t;

/* PTU Static Parameters structure */
typedef _packed_struct_
{
	UINT8 optional_validity;
	UINT8 ptu_power;
	UINT8 ptu_max_src_impedence;
	UINT8 ptu_max_load_resistance;
	UINT8 reserved1[2];
	UINT8 ptu_class;
	UINT8 hw_revision;
	UINT8 fw_revision;
	UINT8 protocol_revision;
	UINT8 ptu_num_devices_supported;
	UINT8 reserved2[6];
}ptu_static_param_char_t;

#if (TARGET_THREADX == FALSE)

/* PRU static parameters structure */
typedef _packed_struct_
{
	UINT8 optional_validity;
	UINT8 protocol_revision;
	UINT8 reserved1[1];
	UINT8 pru_category;
	UINT8 pru_info;
	UINT8 hw_revision;
	UINT8 fw_revision;
	UINT8 p_rect_max;
	UINT16 v_rect_min_static;
	UINT16 v_rect_high_static;
	UINT16 v_rect_set;
	UINT16 delta_r1_val;
	UINT8 reserved2[4];
}pru_static_param_char_t;

/* PRU Dynamic parameters structure */

typedef _packed_struct_
{
	UINT8 optional_validity;
	UINT16 v_rect;
	UINT16 i_rect;
	UINT16 v_out;
	UINT16 i_out;
    UINT8 temperature;
	UINT16 v_rect_min_dynamic;
	UINT16 v_rect_set_dynamic;
	UINT16 v_rect_high_dynamic;
	UINT8 pru_alert;
	UINT8 reserved[3];
}pru_dynamic_param_char_t;

#endif /* TARGET_THREADX == FALSE */

/* PRU Alert Characteristic structure */
typedef _packed_struct_
{
	UINT8 pru_alert;
	UINT8 dev_address[6];
}pru_alert_param_char_t;

/* PRU advertisement data */
typedef _packed_struct_
{
    UINT16 wpt_service_UUID;
    UINT16 gatt_prm_srv_hdl;
    UINT8 pru_rssi_param;
    UINT8 adv_flags;
}pru_adv_data_t;


typedef struct
{
	UINT16 att_id;
	UINT16 length;
	union
	{
		pru_ctrl_char_t pru_control_char_val;
		ptu_static_param_char_t ptu_static_param_char_val;
		pru_alert_param_char_t pru_alert_param_char_val;
		pru_static_param_char_t pru_static_param_char_val;
		pru_dynamic_param_char_t pru_dynamic_param_char_val;
		UINT32 pru_client_conf_desc_val;
	} value;
} att_val_elem_t;

#if (TARGET_THREADX == FALSE)

typedef enum
{
	A4WP_APP_REGISTERED_CB,
	A4WP_CONNECTION_COMPLETE_CB,
	A4WP_DISCONNECTION_COMPLETE_CB,
	A4WP_PRU_CONTROL_MESSAGE_RCVD_CB,
	A4WP_PTU_STATIC_PARAMS_RCVD_CB,
	A4WP_INDICATION_CONFIRMATION_RCVD_CB
}a4wp_sm_opcodes_t;

#endif /* TARGET_THREADX == FALSE */

typedef void (*cb_handler_t)(a4wp_sm_opcodes_t opcode,void *param);

typedef struct _a4wp_app_
{
	BOOLEAN state;
	BOOLEAN isconnected;
	BOOLEAN configure_for_notify;
	BOOLEAN configure_for_indication;

	UINT8 app_handle;
	UINT8 remote_bd_addr[BD_ADDR_LEN];
	UINT8 conn_id;
	UINT16 a4wp_srv_handle;
	cb_handler_t a4wp_sm_handler; /* A4WP state machine cb function handler */
	queue_t req_queue;
	pru_adv_data_t advt_data;
	osa_semaphore_t msg_sem;
	osa_semaphore_t thread_sem;
	osa_timer_t timer_id;
	att_val_elem_t att_val_map[A4WP_SRV_ATT_MAX_ID]; /* Note: Adjust this number with number of char and desc */
}a4wp_srv_t;

extern UINT8 a4wp_register_sm_cb(cb_handler_t sm_handler);
extern UINT8 a4wp_write_adv_parameters(UINT8 rssi, UINT8 adv_flags);
extern UINT8 a4wp_write_static_parameters(pru_static_param_char_t *param);
extern UINT8 a4wp_write_dynamic_parameters(pru_dynamic_param_char_t *param);
extern BOOLEAN a4wp_start_advertisement(void);
extern BOOLEAN a4wp_stop_advertisement(void);
extern BOOLEAN a4wp_send_alert_notification(UINT8 flag,BOOLEAN is_indication);
extern UINT8 a4wp_disconnect(UINT8 reason);
#endif /* A4WP_SRV_H_ */
