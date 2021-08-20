/** @file
  SMP layer header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef SMP_H_
#define SMP_H_

#include "device_struct.h"
#include "smp_mgr.h"

/*	SMP L2cap */
#define SMP_CID 0x06	/* L2CAP fixed channel for SMP*/

/* Pairing model */

#define SMP_LEGACY_PAIRING	0
#define SMP_SECURE_PAIRING	1

/* SMP Command opcodes*/

#define SMP_PAIRING_REQ 		0x01
#define SMP_PAIRING_RSP 		0x02
#define SMP_PAIRING_CFM 		0x03
#define SMP_PAIRING_RND 		0x04
#define SMP_PAIRING_FAILED 		0x05
#define SMP_ENC_INF				0x06
#define SMP_MASTER_IDF 			0x07
#define SMP_IDENTITY_INF 		0x08
#define SMP_IDENTITY_ADD_INF	0x09
#define SMP_SIGN_INF			0x0a
#define SMP_SEC_REQ				0x0b
#define SMP_PAIRING_PUB_KEY		0x0c
#define SMP_DHKEY_CHECK			0x0d


/* SMP data length for each command */

#define SMP_PAIRING_REQ_LEN			07
#define SMP_PAIRING_RSP_LEN 		07
#define SMP_PAIRING_CFM_LEN			17
#define SMP_PAIRING_RND_LEN 		17
#define SMP_PAIRING_FAILED_LEN 		02
#define SMP_ENC_INF_LEN				17
#define SMP_MASTER_IDF_LEN			11
#define SMP_IDENTITY_INF_LEN 		17
#define SMP_IDENTITY_ADD_INF_LEN	8
#define SMP_SIGN_INF_LEN			17
#define SMP_SEC_REQ_LEN				02
#define SMP_PAIRING_PUB_KEY_LEN		65
#define SMP_DHKEY_CHECK_LEN			17

/*SMP Error code */
#define SMP_SUCCESS						0x00
#define SMP_PASS_KEY_FAILED				0x01
#define SMP_OOB_NA						0x02
#define SMP_AUTH_FAILED					0x03
#define SMP_CONFIRM_FAILED				0x04
#define SMP_PAIRING_NOT_SUPPORTED		0x05
#define SMP_INSUFF_KEY_SIZE				0x06
#define SMP_COMMAND_NOT_SUPPORTED		0x07
#define SMP_UNSPECIFIED_REASON			0x08
#define SMP_REPEATED_ATTEMPT			0x09
#define SMP_INVALID_PARAM				0x0A
#define SMP_DHKEY_CHECK_FAILED			0x0B
#define SMP_NUMERIC_COMPARISON_FAILED	0x0C /* 0x0D, 0x0E NA, 0x0F unused */
#define SMP_DEVICE_NOT_CONNECTED		0x10 /* Extended Error code defined by Stack starts from 0x10 */

#define SMP_FAILED						0xFF


#define SMP_MIN_ENC_KEY_SIZE		7
#define SMP_MAX_ENC_KEY_SIZE		16

/* Association models for TK generation*/
#define	SMP_JW  	0		/* Just works */
#define SMP_IIRD 	1		/* Initiator Inputs Responder Displays	*/
#define SMP_IDRI 	2		/* Initiator Displays Responder Inputs 	*/
#define SMP_IIRI 	3		/* Initiator Inputs Responder Inputs 	*/
#define SMP_JW_NC	4		/* Just works incase of legacy and Numeric comparison in secure connections*/
#define SMP_IIRD_NC	5		/* IIRD for legacy and NC for secure connections */
#define SMP_IDRI_NC	6		/* IDRI for legacy and NC for secure connections */
/* SMP state machine */
#define NUM_STATES 18

/* SMP State Machine States*/
#define SMP_STATE_IDLE 					0
#define SMP_STATE_WAIT_PAIR_CMD			1
#define SMP_STATE_WAIT_TK				2
#define SMP_STATE_WAIT_CNF_GEN			3
#define SMP_STATE_WAIT_CNF_CMD			4
#define SMP_STATE_WAIT_RAND_CMD			5
#define SMP_STATE_WAIT_PEER_CNF_GEN		6
#define SMP_STATE_WAIT_STK_GEN			7
#define SMP_STATE_WAIT_LTK_GEN			8
#define SMP_STATE_WAIT_ENC_CHG			9
#define SMP_STATE_WAIT_PEER_KEY_DIST	10
#define SMP_STATE_WAIT_LOCAL_KEY_DIST	11
#define SMP_STATE_WAIT_SIGN_GEN			12
#define SMP_STATE_WAIT_RPA_GEN			13
#define SMP_STATE_WAIT_RPA_RES			14
#define SMP_STATE_WAIT_INIT				15
#define SMP_STATE_WAIT_AUTHORIZATION	16
#define SMP_STATE_WAIT_PASSKEY			17
#define SMP_STATE_WAIT_NC				18


/* Secure connection state machine */
#define SMP_STATE_WAIT_SC_PUB_KEY			18
#define SMP_STATE_WAIT_SC_DHKEY				19
#define SMP_STATE_WAIT_RAND_GEN				20
#define SMP_STATE_WAIT_NUMERIC_VALUE		21
#define SMP_STATE_WAIT_DHKEY_CHECK_CMD		22
#define SMP_STATE_WAIT_DHKEY_CHECK_GEN		23
#define SMP_STATE_WAIT_PEER_DHKEY_CHECK_GEN	24


/* Encryption stages */
#define	SMP_ENC_IDLE			0
#define SMP_ENC_IRK_GEN_S1		1
#define SMP_ENC_IRK_GEN_S2		2
#define SMP_ENC_TK_RAND			3
#define SMP_ENC_RAND_S1			4
#define SMP_ENC_RAND_S2			5
#define SMP_ENC_CONFIRM_S1		6
#define SMP_ENC_CONFIRM_S2		7
#define SMP_ENC_CONFIRM_S3		8
#define SMP_ENC_STK_S1			9
#define SMP_ENC_IRK				10
#define SMP_ENC_LTK_RAND_GEN	11
#define SMP_ENC_LTK_EDIV_GEN	12
#define SMP_ENC_LTK_GEN_S1		13
#define SMP_ENC_LTK_GEN_S2		14
#define SMP_ENC_CSRK_GEN_S1		15
#define SMP_ENC_CSRK_GEN_S2		16
#define SMP_ENC_SUB_KEY			17
#define SMP_ENC_AES_CMAC		18
#define SMP_ENC_RPA_GEN_S1		19
#define SMP_ENC_RPA_GEN_S2		20
#define SMP_ENC_RPA_RES			21
#define SMP_ENC_PUB_KEY			22
#define SMP_ENC_GEN_T			23
#define SMP_ENC_GEN_SC_MACKEY	24
#define SMP_ENC_GEN_SC_LTK		25
#define SMP_ENC_LOCAL_RPA_RES	26
#define SMP_ENC_RAND_P256_1		27
#define SMP_ENC_RAND_P256_2		28
#define SMP_ENC_RAND_P256_3		29
#define SMP_ENC_RAND_P256_4		30


#define SMP_CONFIRM_LEN 16
#define SMP_RAND_LEN 16
#define SMP_STK_LEN 16
#define SMP_LTK_LEN 16
#define SMP_DHK_LEN 16
#define SMP_IRK_LEN 16
#define SMP_CSRK_LEN 16
#define SMP_TK_LEN	16

#define SMP_CMD_TIMEOUT_MS	30000
#define SMP_APP_TIMEOUT_MS	25000

#define SMP_NO_OPERATION		0
#define SMP_BONDING_OPERATION 	1
#define SMP_SIGN_VERIFICATION	2
#define SMP_SIGN_GENERATION		3
#define SMP_RPA_GENERATION		4
#define SMP_RPA_RESOLUTION		5

/* General function type for smp actions */

typedef void (*tSMP_FUN)(smp_cb_t* cur_cb, UINT8 event, UINT8* data);

/* Call back methods from L2CAP */
/**
 * This method will be called from the l2cap layer when a connection to
 * a remote device is completed.
 */
void smp_l2cap_connect_cb(connected_device_t *device);
void smp_l2cap_disconnect_cb(connected_device_t *device);
INT8 smp_l2cap_recv_data_cb(connected_device_t *device, UINT8* data, UINT16 data_len);

/* SMP API's*/
INT8 smp_set_io_capabilities(UINT8 io_capabilities);
BOOLEAN smp_check_key_level(UINT8 auth_level, UINT8 key_type);
INT8 smp_pair(connected_device_t *device,UINT8 auth_level_min, UINT8 key_size_min);
INT8 smp_start_encryption(connected_device_t *device, UINT8 auth_level_min, UINT8 key_size_min);
INT8 smp_init();
INT8 smp_generate_local_irk();
void smp_send_authorization(UINT8 *remote_bd_addr, UINT8 authorization, UINT8 auth_level_min, UINT8 key_size_min);
void smp_send_passkey(UINT32 passkey);
void smp_check_key_and_encrypt(connected_device_t *device);
void security_req_cont();


#if (SECURE_CONNECTION)
void smp_send_nc_result(UINT8 *remote_bd_addr, UINT8 authorization);
#endif /* SECURE_CONNECTION */

#if (PRIVACY_FEATURE)
INT8 smp_rpa_generate();
INT8 smp_rpa_resolve(UINT8* rpa, BOOLEAN local);
#endif /* PRIVACY_FEATURE */

#if (SIGNED_WRITE)
INT8 smp_sign_data(connected_device_t *device, UINT8 *data, UINT16 data_len);
INT8 smp_sign_verify(connected_device_t *device,  UINT8 *data, UINT16 data_len);
#endif /* SIGNED_WRITE */

void smp_storage_registered();
INT8 smp_shutdown();




/* Call back methods from HCI*/
void smp_proc_hci_rand(UINT8 *buffer, UINT8 event_length);
void smp_proc_hci_le_encrypt(UINT8* buffer,UINT8 event_length);
void smp_enc_chg_cback(UINT8* buffer, UINT16 len);
void smp_proc_ltk_req(UINT8* buffer,UINT8 len);

#if (SECURE_CONNECTION)
void smp_proc_p256_public_key(UINT8* buffer, UINT8 len);
void smp_proc_dhkey(UINT8* buffer, UINT8 len);
#endif /* SECURE_CONNECTION */

#endif /* SMP_H_ */
