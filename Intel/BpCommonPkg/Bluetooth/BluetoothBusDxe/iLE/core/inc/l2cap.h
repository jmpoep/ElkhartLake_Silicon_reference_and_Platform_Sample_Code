/** @file
  L2CAP layer implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef L2CAP_H_
#define L2CAP_H_

#define IGNORE 255
/* L2CAP state machine per logical connection. */
#define L2CAP_STATE_CLOSED 						0
#define L2CAP_STATE_OPEN						1
#define L2CAP_STATE_CONN_PARAM_UPDATE_CONTINUE	2
#define L2CAP_DATA_PKT_SIZE (50)
#if (L2CAP_COC == TRUE)
#define L2CAP_COC_CONGESTION_THRESHOLD		5	/* If total available Buffer is 100*10, then at max only 5*100 bytes can stand in CoC send queues (inclusive of all apps) */
#define L2CAP_COC_AVL_BUFFER				46	/* For one CoC connection, for once the maximum SDU that can be sent */
#define L2CAP_COC_MPS						23
//Note: (L2CAP_COC_AVL_BUFFER/L2CAP_COC_MPS) should be the number of credits
//Note: Total of needed BUFFER = (send side is L2CAP_COC_AVL_BUFFER*MAX_NUMBER_OF_L2CAP_CHNL)+(recv side)

/* L2cap Channel State(LCS) machine per logical channel on logical connection. */
/* L2CAP CoC States (LCS) are valid only when LLS is set to L2CAP_STATE_OPEN */
#define LCS_CLOSED							0
#define LCS_OPEN							1
#define LCS_W4_CONNECT_RES					2
#define LCS_W4_DISCONNECT_RES				3
#endif

/**
 * L2CAP Connection state machine
 * L2CAP_STATE_CLOSED ---[L2CAP_EVT_INIT_CONNECT]--->L2CAP_STATE_W4_CONNECT_RES
 * 		|														|
 * 		|---------------[L2CAP_EVT_CONNECT_DONE]----------------|
 * 		|														|
 * 		|--Remote device sent conn req-->L2CAP_STATE_OPEN<------|
 *
 * L2CAP Connection parameter update
 * L2CAP_STATE_OPEN---[L2CAP_EVT_INIT_CONNECT_PARAM_UPDATE]-->L2CAP_STATE_CONN_PARAM_UPDATE_W4_RES
 *		|																|
 *		|																|
 *		|<-------------[L2CAP_EVT_CONNECT_PARAM_UPDATE_DONE]------------|
 *
 * L2CAP Disconnect
 * L2CAP_STATE_CONN_PARAM_UPDATE_W4_RES /
 * L2CAP_STATE_OPEN-----[L2CAP_EVT_INIT_DISCONNECT]------>L2CAP_STATE_W4_DISCONNECT_RES
 * 		|																|
 *		|---------------[L2CAP_EVT_DISCONNECT_DONE]---------------------|
 *		|																|
 *		|--Remote device sent disconnect->L2CAP_STATE_CLOSED<-----------|
 *
 */

/* L2CAP state machine events */
#define L2CAP_EVT_SEND_DATA						0
#define L2CAP_EVT_RECV_DATA						1
#define L2CAP_EVT_INIT_CONNECT_PARAM_UPDATE		2
#define L2CAP_EVT_CONNECT_PARAM_UPDATE_DONE		3
#define L2CAP_EVT_LINK_CONNECTED				4
#define L2CAP_EVT_LINK_DISCONNECTED				5
#if (L2CAP_COC == TRUE)
#define LC_EVT_SEND_CONNECT_REQ					0
#define LC_EVT_RECV_CONNECT_RES					1
#define LC_EVT_RECV_CONNECT_REQ					2
#define LC_EVT_SEND_DATA						3
#define LC_EVT_RECV_DATA						4
#define LC_EVT_SEND_DISCONNECT_REQ				5
#define LC_EVT_RECV_DISCONNECT_RES				6
#define LC_EVT_RECV_DISCONNECT_REQ				7
#define LC_EVT_SEND_FC_CREDIT					8
#define LC_EVT_RECV_FC_CREDIT					9
#endif // L2CAP_COC

/* L2CAP state machine actions */
#define L2CAP_ACT_SEND_DATA						0
#define L2CAP_ACT_RECV_DATA						1
#define L2CAP_ACT_INIT_CONNECT_PARAM_UPDATE		2
#define L2CAP_ACT_CONNECT_PARAM_UPDATE_DONE		3

/* LE L2CAP CID */
#define L2CAP_ATT_CID							4
#define L2CAP_LE_SIGNAL_CID						5
#define L2CAP_SMP_CID							6
#if (L2CAP_COC == TRUE)
#define L2CAP_COC_START_CID						0x40 /* From specification */
#endif //L2CAP_COC

#define L2CAP_ATT_PSM							4
#define L2CAP_SMP_PSM							6

/* L2CAP OPCODES */
#define L2CAP_COMMAND_REJECT						0x01
#define L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_REQ	0X12
#define L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_RES	0X13

#define L2CAP_SIGNALLING_MTU_SIZE						23 /* TODO: Verify */
#define L2CAP_COMMAND_REJECT_LEN						2
#define L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_REQ_LEN	8
#define L2CAP_COMMAND_HDR_LEN							4
#define L2CAP_COMMAND_CONNECTION_PARAM_UPDATE_RES_LEN	2

#if (L2CAP_COC == TRUE)
/* opcodes */
#define L2CAP_COC_COMMAND_CONNECT_REQ						0x14
#define L2CAP_COC_COMMAND_CONNECT_RES						0x15
#define L2CAP_COC_COMMAND_DISCONNECT_REQ					0x06
#define L2CAP_COC_COMMAND_DISCONNECT_RES					0x07
#define L2CAP_COC_COMMAND_FC_CREDIT							0x16

/* command lengths */
#define L2CAP_COC_COMMAND_CONNECT_REQ_LEN					10 /* From specification */
#define L2CAP_COC_COMMAND_CONNECT_RES_LEN					10 /* From specification */
#define L2CAP_COC_COMMAND_DISCONNECT_REQ_LEN				4  /* From specification */
#define L2CAP_COC_COMMAND_DISCONNECT_RES_LEN				4  /* From specification */
#define L2CAP_COC_COMMAND_FC_CREDIT_LEN						4  /* From specification */

/* L2CAP Response Reason Codes */
#define L2CAP_COC_RESPONSE_CONNECTION_SUCCESSFUL			0X0000
#define L2CAP_COC_RESPONSE_LE_PSM_NOT_SUPPORTED				0X0002
#define L2CAP_COC_RESPONSE_NO_RESOURCES_AVAILABLE			0X0004
#define L2CAP_COC_RESPONSE_INSUFFICIENT_AUTHENTICATION		0X0005
#define L2CAP_COC_RESPONSE_INSUFFICIENT_AUTHORIZATION		0X0006
#define L2CAP_COC_RESPONSE_INSUFFICIENT_ENC_KEY_SIZE		0X0007
#define L2CAP_COC_RESPONSE_INSUFFICIENT_ENCRYPTION			0X0008
#define L2CAP_COC_RESPONSE_INVALID_SOURCE_CID				0X0009
#define L2CAP_COC_RESPONSE_SOURCE_CID_ALREADY_ALLOCATED		0X000A
#endif //L2CAP_COC

/* L2CAP REASON CODES */
#define L2CAP_COMMAND_NOT_UNDERSTOOD				0
#define L2CAP_SIGNALLING_MTU_EXEEDED				1
#define L2CAP_INVALID_CID							2

#define L2CAP_CONN_PARAM_ACCEPTED					0
#define L2CAP_CONN_PARAM_REJECTED					1

#define L2CAP_PB_FLAG_FIRST_NON_FLUSHABLE_PKT		0x00
#define L2CAP_PB_FLAG_CONTINUOUS_PKT				0x01
#define L2CAP_PB_FLAG_FIRST_FLUSHABLE_PKT			0x02

typedef struct
{
	UINT16 cid;
	UINT16 len;
	UINT8* data;
} l2cap_data_pkt_t;

typedef struct
{
	UINT8 pb_flag;
	UINT16 data_length;
	UINT8* data;
} l2cap_recv_data_pkt_t;

typedef struct
{
	UINT16 interval_min;
	UINT16 interval_max;
	UINT16 conn_latency;
	UINT16 sup_timeout;
} l2cap_param_updt_pkt_t;

#if (L2CAP_COC == TRUE)
#define L2CAP_COC_FLAG_FIRST_PKT					0x00
#define L2CAP_COC_FLAG_CONTINUOUS_PKT				0x01

/* Used while data send/receive by API or by peer, also used for queueing data */
typedef struct
{
	UINT8 handle;
	UINT16 length;
	UINT8* data;
} l2cap_data_t;

/* Used for credit send/receive */
typedef struct
{
	UINT8 handle;
	UINT16 fc_credits;
} l2cap_credits_t;

/* Below structs are L2CAP interface parameter structures */
/* Used by L2CAP CoC API create connection */
typedef struct
{
	UINT8 conn_id;
	UINT16 psm;
	UINT16 mtu;
	trans_id_t trans_id;
	l2cap_coc_callbacks_t *l2cap_coc_cbs;
} l2cap_coc_api_conn_t;

typedef struct
{
	BOOLEAN auth_req;
	trans_id_t trans_id;
	UINT16 psm;
	UINT16 mtu;
	l2cap_coc_callbacks_t *l2cap_coc_cbs;
}l2cap_coc_register_coc_param_t;

/* Used by L2CAP CoC API for disconnect request */
typedef struct
{
	UINT8 conn_id;
	UINT8 coc_handle;
	trans_id_t trans_id;
} l2cap_coc_api_disconnect_t;

/* Used by L2CAP CoC API for data send request */
typedef struct
{
	UINT8 conn_id;
	UINT8 coc_handle;
	trans_id_t trans_id;
	UINT16 buffer_len;
	UINT8 buffer[0];
} l2cap_coc_api_data_t;
#endif // L2CAP_COC

/*********************************************************************
 * 						L2CAP APIs
 ********************************************************************/
INT8 l2cap_init(void);
void l2cap_cleanup(void);
void* get_l2cap_free_buffer(UINT16 size);
void free_l2cap_buffer(void *buffer);
/**
 * Connect request. This will send out ll connection request.
 * This will call gap procedure to establish connection.
 */
INT8 l2cap_connect_req(connected_device_t *device, UINT16 psm);
INT8 l2cap_data_send(UINT8 conn_id, UINT16 cid, buffer_t* buffer);
INT8 l2cap_disconnect_req(connected_device_t *device);
INT8 l2cap_send_conn_param_update_req(connected_device_t *device, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout);
INT8 l2cap_connect_cancel_req(UINT8* remote_bd_addr);

#if (L2CAP_COC == TRUE)
/** Note: All CoC operations can happen only when base L2CAP state is OPEN alone */
/**
 * CoC Connect request to send out logical CoC connection request.
 * Pre-condition L2CAP connection should exist between two devices in order to establish L2CAP CoC.
 */
INT8 l2cap_coc_connect_req(trans_id_t trans_id, UINT8 conn_id, UINT16 psm, UINT16 mtu, l2cap_coc_callbacks_t *l2cap_coc_cbs);
/**
 * Application can register for supported PSM with other parameters.
 * Note: At any point of time only one application can register for a PSM, there cannot be multiple applications registering for same PSM.
 * Other parameters include application call back functions to be called in order to notify connection complete, FC credit receive and data receive events.
 * app_id is the same app_handle received by application during app registration. Unique coc_handle will be generated for a unique combination of app_id+psm and
 * returned in connection_complete or connection_complete_notify callback. This unique coc_handle should be reference along with app_handle for any further CoC transactions.
 * mps cannot be greater than mtu.
 * initial_credits can range from 0 to (2^16 -1). The FC credits received should be positive value, and used for incrementing available credits, and also notified to the app.
 */
INT8 l2cap_coc_register_cb_for_conn_req(trans_id_t trans_id, UINT16 psm, UINT16 mtu, BOOLEAN auth_req, l2cap_coc_callbacks_t *l2cap_coc_cbs);
/**
 * CoC Get the maximum MTU size supported by stack for LE CoC.
 */
UINT16 l2cap_coc_get_max_mtu_size();
/**
 * CoC Disconnect request is to send logical CoC disconnection request to peer.
 */
INT8 l2cap_coc_disconnect_req(trans_id_t trans_id, connected_device_t *device, UINT8 handle);

/**
 * CoC fc credit request is to send flow control credits to peer. Credit value will be based on available free memory for the app.
 */
INT8 l2cap_coc_send_fc_credit(connected_device_t *device, UINT8 handle, UINT16 fc_credits);

/**
 * CoC send data request is to send data to peer.
 */
INT8 l2cap_coc_send_data(connected_device_t *device, UINT8 handle, UINT8* buffer, UINT16 buffer_len);
#endif // L2CAP_COC

/*********************************************************************
 * 						L2CAP Call Backs
 ********************************************************************/
void l2cap_connect_cb(connected_device_t *device, BOOLEAN result);
void l2cap_disconnect_cb(connected_device_t *device, BOOLEAN result);
void l2cap_recv_data(connected_device_t *device, UINT8 pb_flag, UINT8* data, UINT16 data_length);
void l2cap_recv_conn_param_update_evt(UINT8* buffer, UINT8 len);

#endif /* L2CAP_H_ */
