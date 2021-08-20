/** @file
  SMP protocol implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "smp.h"
#include "l2cap.h"
#include "hci_host.h"
#include "gap.h"
#include "device_struct.h"
#include "error_code.h"
#include "int_interface.h"

#if (TARGET_UEFI == FALSE)
/* These libraries are not available on UEFI platform */
#include <unistd.h>
#endif

#if (INTERNAL_AES == TRUE)
#include "aes.h"
#endif /* INTERNAL_AES == TRUE */

#if (HOST_ECDH == TRUE)
#include "ecc.h"
#endif /* HOST_ECDH == TRUE*/

#define MODULE_DBG_LVL SMP_DBG_LVL
#include "log.h"

#if (SMP_FEATURE)

/* Static functions*/

/* Events from upper layer*/

static void smp_create_bond_evt();
static void smp_authorization_grant_evt(UINT8* data, UINT8 auth_level_min, UINT8 key_size_min);
#if (SECURE_CONNECTION)
static void smp_nc_grant_evt(UINT8* data);
#endif

static void smp_tk_gen_evt(UINT8* data);

/* Events from peer device */

static void smp_pair_cmd_evt(UINT8* data);
static void smp_sec_req_cmd_evt(UINT8* data);
static void smp_confirm_cmd_evt(UINT8* data);
static void smp_rand_cmd_evt(UINT8* data);
static void smp_enc_info_cmd_evt(UINT8* data);
static void smp_mast_id_cmd_evt(UINT8* data);

#if (PRIVACY_FEATURE)
static void smp_id_info_cmd_evt(UINT8* data);
static void smp_add_info_cmd_evt(UINT8 *data);
#endif /* PRIVACY_FEATURE */

#if (SIGNED_WRITE)
static void smp_sign_info_cmd_evt(UINT8* data);
#endif /* SIGNED_WRITE */

static void smp_pair_failed_cmd_evt(UINT8* data);

#if (SECURE_CONNECTION)
static void smp_pairing_pub_key_cmd_evt(UINT8* data);
static void smp_dhkey_check_cmd_evt(UINT8 *data);
#endif /* SECURE_CONNECTION */

/* Events from lower layers*/

static void smp_rand_gen_evt();
static void smp_confirm_gen_evt(UINT8* data);
static void smp_link_key_cal_evt();
static void smp_enc_chg_evt();
static void smp_key_dist_start_evt();
static void smp_key_dist_done_evt();

#if (SIGNED_WRITE)
static void smp_sign_gen_evt();
static void smp_aes_cmac_gen_evt();
#endif /* SIGNED_WRITE */

static void smp_l2c_disconn_evt();
static void smp_pair_failed_evt();


#if (SECURE_CONNECTION)
static void smp_dhkey_gen_evt(UINT8 *data);
static void smp_numeric_check_value_generate_evt(UINT8 *data);
static void smp_ltk_gen_evt();
static void smp_dhkey_check_gen_evt(UINT8 *data);
#endif /* SECURE_CONNECTION */


/* Commands sent to the peer device*/
static INT8 smp_send_pair_cmd();
static INT8 smp_send_security_request_cmd(UINT8 req_sec_level);
static INT8 smp_send_confirm_cmd();
static INT8 smp_send_rand_cmd();
static INT8 smp_send_enc_info_cmd();

#if (PRIVACY_FEATURE)
static INT8 smp_send_id_info_cmd();
#endif /* PRIVACY_FEATURE */

#if (SIGNED_WRITE)
static INT8 smp_send_sign_info_cmd();
#endif /* SIGNED_WRITE */

#if (SECURE_CONNECTION)
static INT8 smp_send_pub_key_cmd();
static INT8 smp_send_dhkey_check_cmd(UINT8 *data);
#endif /* SECURE_CONNECTION */

static INT8 smp_send_fail_cmd();

/* Other internal functions */
static BOOLEAN compare_auth_request();
static INT8 fetch_key(connected_device_t *device, UINT8 key_type);
static void update_enc_changed(connected_device_t *device, UINT8 status);
static void smp_decide_asso_model();
static void smp_start_pairing_phase2();
static void smp_gen_rand();
static void smp_compare_confirm(UINT8* data);

static void smp_cal_stk();
static void smp_start_enc();
static void smp_start_key_dist();
static void smp_gen_ltk();
static void smp_check_key_dist();
static void smp_hci_enc_key_reply(UINT16 conn_handle, UINT8* ltk);

#if (PRIVACY_FEATURE)
static void smp_gen_rpa();
static void smp_res_rpa(BOOLEAN local);
#endif /* PRIVACY_FEATURE */

#if (SIGNED_WRITE)
static void smp_gen_csrk();
#endif /* SIGNED_WRITE */

#if (AES_CMAC)
static void smp_shift_left(UINT8* data, UINT8 data_len, UINT8* output);
static void smp_cal_sub_keys();
static UINT8 Rb[SMP_MAX_KEY_LEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87};
#endif /* AES_CMAC */

/* Secure connection functions */
#if (SECURE_CONNECTION)
static void smp_cal_numeric_value();
static void smp_cal_dhkey();
static void smp_dhkey_compare(UINT8 *data);
static UINT8 aes_cmac_salt[] = { 0x6c, 0x88, 0x83, 0x91, 0xaa, 0xf5, 0xa5, 0x38, 0x60, 0x37, 0x0b, 0xdb, 0x5a, 0x60, 0x83, 0xbe };
static UINT8 key_id[] = { 0x62, 0x74, 0x6c, 0x65 };
#endif /* SECURE_CONNECTION */

static void smp_clean_up();


/*enc func*/
static void smp_init_enc();
static void smp_handle_enc_operations(UINT8* data);
static void smp_c1_1(UINT8* tk, UINT8* mrand, UINT8* smp_pair_req_cmd, UINT8* smp_pair_rsp_cmd, UINT8 initiating_dev_type,
			 UINT8 responding_dev_type);
static void smp_c1_2(UINT8 *tk, UINT8* p1,UINT8*intiating_dev_add, UINT8* responding_dev_add);
static void smp_aes_encrypt(UINT8* key, UINT8* plain_text);
static void smp_xor(UINT8* x, UINT8* y, int len);
static void smp_mask_key(UINT8* key, UINT8 len);

#if (AES_CMAC)
static void smp_aes_cmac(UINT8 *data, UINT16 len, UINT8 *key);
#endif
#if (SECURE_CONNECTION)
static void smp_f4(UINT8 *u, UINT8 *v, UINT8 *x, UINT8 z);
static void smp_f5(UINT8 *w, UINT8 *n1, UINT8 *n2, UINT8 *a1, UINT8 *a2);
static void smp_f6(UINT8 *w, UINT8 *n1, UINT8 *n2, UINT8 *r, UINT8 *iocap, UINT8 *a1, UINT8 *a2);
static void smp_g2(UINT8 *u, UINT8 *v, UINT8 *x, UINT8 *y);
static void smp_generate_p256_keys();
#if (HOST_ECDH)
static void smp_generate_p256_key_internal();
#if(ECDH_TESTING == TRUE)
void smp_ecc_test();
#endif /* ECDH_TESTING */
#endif /* HOST_ECDH */
#endif /* SECURE_CONNECTION */


/*Timer functions*/
static void smp_cmd_timer_expire_cb(osa_timer_arg_t arg);
static int smp_create_cmd_timer();
static int smp_destroy_cmd_timer();
static int smp_start_cmd_timer();
static int smp_stop_cmd_timer();

static void smp_app_timer_expire_cb(osa_timer_arg_t arg);
static int smp_create_app_timer();
static int smp_destroy_app_timer();
static int smp_start_app_timer();
static int smp_stop_app_timer();


RETENTION_SECTION_START
static UINT8 g_io_cap;
static UINT8 g_sec_level;
static UINT8 g_enc_key_size;
static UINT8 g_key_dist;
static const UINT8 io_cap_mapping[5][5] =
{
		/* Initiator*/
		/*Responder			Displayonly		display_yes_no		Keyboardonly	No_IO		KeyboardDisplay*/
		/*Displayonly*/		{SMP_JW,			SMP_JW,				SMP_IIRD,	SMP_JW,		SMP_IIRD},
		/*Display_yes_no*/	{SMP_JW,			SMP_JW_NC,			SMP_IIRD,	SMP_JW,		SMP_IIRD_NC},
		/*Keyboardonly*/	{SMP_IDRI,			SMP_IDRI,			SMP_IIRI,	SMP_JW,		SMP_IDRI},
		/*No_IO*/			{SMP_JW,			SMP_JW,				SMP_JW,		SMP_JW,		SMP_JW},
		/*KeyboardDisplay*/	{SMP_IDRI,			SMP_IDRI_NC,		SMP_IIRD,	SMP_JW,		SMP_IDRI_NC},
};
RETENTION_SECTION_END

static void smp_create_bond_evt()
{
	logi("");
	if(g_local_adapter.smp_data.smp_cur_cb.state != SMP_STATE_IDLE)
	{
		logw("Event Not to be processed");
		return;
	}
	g_local_adapter.smp_data.smp_cur_cb.state = SMP_STATE_WAIT_PAIR_CMD;
	if(g_local_adapter.connected_device[g_local_adapter.smp_data.smp_cur_cb.conn_id]->local_link_role)
		smp_send_security_request_cmd(g_local_adapter.smp_data.smp_cur_cb.local_auth_req);
	else
		smp_send_pair_cmd();

}

/*
 * This function is called when authorization is granted for pairing
 */
static  void smp_authorization_grant_evt(UINT8* data, UINT8 auth_level_min, UINT8 key_size_min)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	smp_stop_app_timer();
	if(cur_cb->state != SMP_STATE_WAIT_AUTHORIZATION)
	{
		logw("Event Not to be processed");
		return;
	}

	cur_cb->local_auth_req = g_sec_level;
	cur_cb->local_auth_level_min = auth_level_min;
	cur_cb->local_init_key = cur_cb->local_resp_key = g_key_dist;
	cur_cb->local_io_cap = g_io_cap;
	cur_cb->local_enc_key_size = SMP_DEFAULT_ENC_KEY_SIZE;
	cur_cb->local_enc_key_size_min = key_size_min;
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		/*
		 * We are slave. So this authorization grant event is due to a pairing
		 * request. So we will send a pairing response
		 */
		if(cur_cb->peer_enc_key_size < cur_cb->local_enc_key_size_min)
		{
			cur_cb->event = 0;
			cur_cb->status = SMP_INSUFF_KEY_SIZE;
			smp_pair_failed_evt();
			return;

		}

		if(compare_auth_request() == FALSE)
		{
			/*We dont have sufficient security
			 * Reject the pairing
			 */
			cur_cb->status = SMP_AUTH_FAILED;
			smp_pair_failed_evt();
			return;
		}

		cur_cb->local_init_key &= cur_cb->peer_init_key;
		cur_cb->local_resp_key &= cur_cb->peer_resp_key;
		cur_cb->cur_key.keys_distributed = (cur_cb->local_init_key << 4)|(cur_cb->local_resp_key);


		/* All the details to decide the pairing model (legacy / secure connections)
		 * are available.
		 */
#if ( SECURE_CONNECTION )
		if((cur_cb->local_auth_req & SMP_SC_Y) && (cur_cb->peer_auth_req & SMP_SC_Y))
		{
			/* Secure connection selected*/
			logd("Secure Pairing");
			cur_cb->state = SMP_STATE_WAIT_SC_PUB_KEY;
			smp_send_pair_cmd();
			cur_cb->local_init_key &= (SMP_ENC_N | SMP_ID_Y | SMP_SIGN_Y);
			cur_cb->local_resp_key &= (SMP_ENC_N | SMP_ID_Y | SMP_SIGN_Y);
			cur_cb->pairing_method = SMP_SECURE_PAIRING;
			smp_decide_asso_model();
			/* Since we are the slave, we need to wait for masters public key*/

		}
		else
#endif
		{
			/* Legacy pairing */
			smp_send_pair_cmd();
			smp_decide_asso_model();
			smp_start_pairing_phase2();
		}
	}
	else
	{
		/* We are master and we are responding to a security request.*/
		cur_cb->state = SMP_STATE_WAIT_PAIR_CMD;
		smp_send_pair_cmd();
	}
}

#if ( SECURE_CONNECTION )
/* This function is called when the user confirms whether the numeric comparison
 * value matches or not.
 */
static void smp_nc_grant_evt(UINT8* data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	smp_stop_app_timer();
	if(cur_cb->state != SMP_STATE_WAIT_NC && cur_cb->state != SMP_STATE_WAIT_DHKEY_CHECK_CMD)
	{
		logw("Event Not to be processed");
		return;
	}
	if(cur_cb->state == SMP_STATE_WAIT_NC)
	{
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			/* We are slave.
			 * If we are in this state, it means that the other device has
			 *  not yet sent the dhkey check.
			 */
			cur_cb->state = SMP_STATE_WAIT_DHKEY_CHECK_CMD;
		}
		else
		{
			/* We are master. We should go a head and create the LTK */
			cur_cb->state = SMP_STATE_WAIT_LTK_GEN;
			smp_gen_ltk();
		}
	}
	else
	{
		/* This means that the other device has already sent the dhkey check.
		 * We now need to generate the mackey/LTK and validate the dhkey check
		 */
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			cur_cb->state = SMP_STATE_WAIT_LTK_GEN;
			smp_gen_ltk();
		}
	}
}
#endif /* SECURE_CONNECTION */


/* This function will be called when a pass key is generated
 *  If we have to generate a passkey, then this will be called when a random
 *  number is generated from controller.
 *  If other device generates the passkey, then upper layer will input the passkey
 *  */
static void smp_tk_gen_evt(UINT8* data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8* pp = NULL;
	logi("");
	smp_stop_app_timer();
	if(cur_cb->state != SMP_STATE_WAIT_PASSKEY && cur_cb->state != SMP_STATE_WAIT_TK && cur_cb->state != SMP_STATE_WAIT_CNF_CMD)
	{
		logw("Event Not to be processed");
		return;
	}
	memset(cur_cb->tk, 0, SMP_TK_LEN);
	if(data != NULL)
	{
		pp = data;
		cur_cb->tk[12] = pp[3];
		cur_cb->tk[13] = pp[2];
		cur_cb->tk[14] = pp[1];
		cur_cb->tk[15] = pp[0];
	}
#if ( SECURE_CONNECTION )
	if(cur_cb->pairing_method == SMP_SECURE_PAIRING)
	{
		/* In case of passkey entry, we need to send confirm for each bit of passkey.
		 * This count is reset now.
		 */
		cur_cb->key_bit_sent = 0;
	}
#endif /* SECURE_CONNECTION */
	/* Irrespective of the pairing method, the action needs to be same.
	 * The sequence to be followed by
	 * 1. Master
	 * 	a) generate a random number.
	 *  b) generate confirm(commitment) value ( using smp_c1(legacy) / smp_f4(secure connections)
	 *  c) send the generated confirm(commitment) value
	 * 2. Slave
	 * 	a) wait for mconfirm(commitment) value ( This might have already happened before passkey evt
	 * 		because there are manual delay when user is entering the passkey).
	 * 	b) generate a random number
	 * 	c) generate confirm(commitment) value ( using smp_c1(legacy) / smp_f4(secure connections)
	 * 	d) send the generated confirm(commitment) value
	 */
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		/* We are slave */
		if(cur_cb->state == SMP_STATE_WAIT_CNF_CMD)
		{
			/* This state indicate that the mconfirm has already been received
			 * so we proceed with the random number generation.
			 */
			cur_cb->state = SMP_STATE_WAIT_CNF_GEN;
			smp_gen_rand();
		}
		else if(cur_cb->state == SMP_STATE_WAIT_PASSKEY || cur_cb->state == SMP_STATE_WAIT_TK)
		{
			/*
			 * This state indicate that mconfirm hasn't been received.
			 * So slave will wait for mconfirm
			 */
			cur_cb->state = SMP_STATE_WAIT_CNF_CMD;
		}
	}
	else
	{
		/* We are master. we will proceed with random number generation */
		cur_cb->state = SMP_STATE_WAIT_CNF_GEN;
		smp_gen_rand();
	}
}

/* This function is called when a pairing request or a pairing command is
 * received on the LE-U link
 */
static void smp_pair_cmd_evt(UINT8* data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8* pp = (UINT8*)data + 1;
	logi("");
	if((cur_cb->state != SMP_STATE_WAIT_PAIR_CMD) && (g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role  && cur_cb->state != SMP_STATE_IDLE))
	{
		logw("Event Not to be processed");
		return;
	}
	/* Copy the pair command details to local data base */
	STREAM_TO_UINT8(cur_cb->peer_io_cap, pp);
	STREAM_TO_UINT8(cur_cb->peer_oob_flag, pp);
	STREAM_TO_UINT8(cur_cb->peer_auth_req, pp);
	STREAM_TO_UINT8(cur_cb->peer_enc_key_size,pp);
	STREAM_TO_UINT8(cur_cb->peer_init_key,pp);
	STREAM_TO_UINT8(cur_cb->peer_resp_key,pp);
	if((cur_cb->peer_enc_key_size < SMP_MIN_ENC_KEY_SIZE) || (cur_cb->peer_enc_key_size > SMP_MAX_ENC_KEY_SIZE))
	{
		cur_cb->event = 0;
		cur_cb->status = SMP_INSUFF_KEY_SIZE;
		smp_pair_failed_evt();
		return;
	}
	if(cur_cb->peer_io_cap > SMP_MAX_IO_CAP )
	{
		cur_cb->event = 0;
		cur_cb->status = SMP_INVALID_PARAM;
		smp_pair_failed_evt();
		return;
	}
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{		//We are the slave.
		pp = cur_cb->pairing_req;
	}
	else
	{
		pp = cur_cb->pairing_rsp;
		cur_cb->local_init_key = cur_cb->peer_init_key;
		cur_cb->local_resp_key = cur_cb->peer_resp_key;
		cur_cb->cur_key.keys_distributed = (cur_cb->local_resp_key << 4)| cur_cb->local_init_key;
		if (cur_cb->peer_enc_key_size < cur_cb->local_enc_key_size_min)
		{
			cur_cb->event = 0;
			cur_cb->status = SMP_INSUFF_KEY_SIZE;
			smp_pair_failed_evt();
			return;
		}

		if(cur_cb->peer_enc_key_size < cur_cb->local_enc_key_size)
		{
			cur_cb->local_enc_key_size = cur_cb->peer_enc_key_size;
		}
	}
	REVERSE_ARRAY_TO_STREAM(pp, data, SMP_PAIRING_REQ_LEN);

	/* Do the corresponding state transition */
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		/* We are slave here*/
		if(cur_cb->state == SMP_STATE_IDLE)
		{
			/* If we are in idle state, that means this cmd is not the result of a pairing
			 * initiated by us through a security request. So we need a authorization for
			 * the same from upper layer ( if io capabilites allow us).
			 */
			cur_cb->state = SMP_STATE_WAIT_AUTHORIZATION;
			smp_start_app_timer();

			logd("Need authorisation from the upper layer");
			smp_mgr_cback(cur_cb->bdaddr, SMP_AUTHORISATION_REQ_EVT, NULL, 0);
			return;
		}
		/* Since we are not idle, we had initiated this pairing.
		 * Hence go ahead with the pairing by sending a response.
		 */
		if(compare_auth_request() == FALSE)
		{
			/*We dont have sufficient security
			 * Reject the pairing
			 */
			cur_cb->status = SMP_AUTH_FAILED;
			smp_pair_failed_evt();
			return;
		}
		cur_cb->enc_with_ltk = FALSE;
		cur_cb->local_init_key &= cur_cb->peer_init_key;
		cur_cb->local_resp_key &= cur_cb->peer_resp_key;
		cur_cb->cur_key.keys_distributed = (cur_cb->local_init_key << 4)|(cur_cb->local_resp_key);
		smp_send_pair_cmd();
	}
	else
	{
		if(compare_auth_request() == FALSE)
		{
			/*We dont have sufficient security
			 * Reject the pairing
			 */
			cur_cb->status = SMP_AUTH_FAILED;
			smp_pair_failed_evt();
			return;
		}
	}
	/* We have received all information to determine the type of pairing
	 * Now we decide whether legacy/secure connection should be used
	 */
#if ( SECURE_CONNECTION )
	if((cur_cb->local_auth_req & SMP_SC_Y) && (cur_cb->peer_auth_req & SMP_SC_Y))
	{
		/*Secure connections will be used*/
		logd("Secure Pairing selected");
		cur_cb->local_init_key &= (SMP_ENC_N | SMP_ID_Y | SMP_SIGN_Y);
		cur_cb->local_resp_key &= (SMP_ENC_N | SMP_ID_Y | SMP_SIGN_Y);
		cur_cb->pairing_method = SMP_SECURE_PAIRING;
		smp_decide_asso_model();
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			/* Master will have to share his public key now*/
			cur_cb->state = SMP_STATE_WAIT_SC_PUB_KEY;
		}
		else
		{
			/* We are the master, we will send the public key and wait for the
			 * peer public key
			 */
			cur_cb->state = SMP_STATE_WAIT_SC_PUB_KEY;
			smp_send_pub_key_cmd();
		}
	}
	else
#endif /* SECURE_CONNECTION */
	{
		/* Legacy pairing selected
		 * We need to decide the association model.
		 */
		cur_cb->pairing_method = SMP_LEGACY_PAIRING;
		smp_decide_asso_model();
		smp_start_pairing_phase2();
	}
}

/* This function is called when we receive a security request command on LE-U link*/
static void smp_sec_req_cmd_evt(UINT8* data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	connected_device_t *device = g_local_adapter.connected_device[cur_cb->conn_id];
	UINT8* pp = (data+1);

	logi("");
	/* if we are the slave, then we will not receive this command.
	 * If we are not idle(a pairing is in progress),
	 * then we will not process this request
	 */
	if((device->local_link_role) ||
			(!device->local_link_role && cur_cb->state != SMP_STATE_IDLE))
	{
		logw("Event Not to be processed");
		return;
	}

	STREAM_TO_UINT8(cur_cb->peer_auth_req, pp);
	/* We need to find out whether this security request is to start a fresh pairing,
	 * or for re-encryption. For that we need to check our bonded device list for this device.
	 */
	if(device->link_enc_state.state >= LINK_ENC_STATE_UPDATED)
	{
		/* The device is already bonded. Check whether the current keys stored
		 * in our database meet the auth request.		 */
		BOOLEAN key_check = smp_check_key_level(cur_cb->peer_auth_req, device->link_enc_state.key_type);
		if(key_check)
		{
			if((device->link_enc_state.keys_distributed & SMP_LTK_RECEIVED))
			{
				cur_cb->state = SMP_STATE_WAIT_ENC_CHG;
				cur_cb->enc_with_ltk = TRUE;
				cur_cb->local_enc_key_size = device->link_enc_state.key_size;
				cur_cb->cur_key.key_type = device->link_enc_state.key_type;
				cur_cb->cur_key.key_size = device->link_enc_state.key_size;
				cur_cb->cur_key.security_level = device->link_enc_state.secuirty_level;
				device->link_enc_state.pending_act |= LINK_ENC_PENDING;
				fetch_key(device, PEER_LTK);
				return;
			}
		}
	}
	else
	{
		device->link_enc_state.pending_act |= LINK_SEC_REQ_PENDING;
		return;
	}
	cur_cb->remote_initiated = FALSE;
	cur_cb->state = SMP_STATE_WAIT_AUTHORIZATION;
	smp_start_app_timer();

	logd("Need authorisation from the upper layer");
	smp_mgr_cback(g_local_adapter.connected_device[cur_cb->conn_id]->id_addr.bdaddr, SMP_AUTHORISATION_REQ_EVT, NULL, 0);
}

void security_req_cont()
{
	UINT8 data[2];
	data[0] = SMP_SEC_REQ;
	data[1] = g_local_adapter.smp_data.smp_cur_cb.peer_auth_req;
	smp_sec_req_cmd_evt(data);
}
/* This function is called when we receive a confirm command on LE-U link*/
static void smp_confirm_cmd_evt(UINT8* data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8* pp = data;
	UINT8* confirm = cur_cb->peer_confirm;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_PASSKEY && cur_cb->state != SMP_STATE_WAIT_CNF_CMD
			&& cur_cb->state != SMP_STATE_WAIT_SC_DHKEY)
	{
		logw("Event Not to be processed");
		return;
	}
	REVERSE_ARRAY_TO_STREAM(confirm, pp, SMP_CONFIRM_LEN);
	if(cur_cb->pairing_method == SMP_LEGACY_PAIRING)
	{
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			if(cur_cb->state == SMP_STATE_WAIT_PASSKEY)
			{
				cur_cb->state = SMP_STATE_WAIT_CNF_CMD;
			}
			else if(cur_cb->state == SMP_STATE_WAIT_CNF_CMD)
			{
				cur_cb->state = SMP_STATE_WAIT_CNF_GEN;
				smp_gen_rand();
			}
		}
		else
		{
			cur_cb->state = SMP_STATE_WAIT_RAND_CMD;
			smp_send_rand_cmd();
		}
	}
#if ( SECURE_CONNECTION )
	else
	{
		/* Secure connections*/
		switch(cur_cb->asso_model)
		{
			 case SMP_JW:
			 case SMP_JW_NC:
			 case SMP_IIRD_NC:
			 case SMP_IDRI_NC:
				 if(cur_cb->state == SMP_STATE_WAIT_SC_DHKEY)
				 {
					 cur_cb->state = SMP_STATE_WAIT_CNF_CMD;
					 return;
				 }
				 if(!g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role && cur_cb->state == SMP_STATE_WAIT_CNF_CMD)
				 {
					 /* Only master will receive a confirm command in these association model*/
					 cur_cb->state = SMP_STATE_WAIT_RAND_GEN;
					 smp_gen_rand();
				 }
				 break;
			 case SMP_IIRD:
			 case SMP_IDRI:
			 case SMP_IIRI:
				 if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
				 {
					 if(cur_cb->state == SMP_STATE_WAIT_PASSKEY)
					 {
						 /* This might be the case where the slave is waiting for the passkey
						  * from upper layer
						  */
						 cur_cb->state = SMP_STATE_WAIT_CNF_CMD;
					 }
					 else if(cur_cb->state == SMP_STATE_WAIT_CNF_CMD)
					 {
						 cur_cb->state = SMP_STATE_WAIT_CNF_GEN;
						 smp_gen_rand();
					 }
				 }
				 else
				 {
					 cur_cb->state = SMP_STATE_WAIT_RAND_CMD;
					 smp_send_rand_cmd();
				 }
				 break;
		}
	}
#endif /* SECURE_CONNECTION */
}
/* This function is called when a random command is received on the LE-U link*/
static void smp_rand_cmd_evt(UINT8* data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 *pp = NULL;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_RAND_CMD)
	{
		logw("Event Not to be processed");
		return;
	}
	pp = cur_cb->peer_rand;
	REVERSE_ARRAY_TO_STREAM(pp, ((UINT8*)data + 1), 16);
	memcpy(cur_cb->cur_rand, cur_cb->peer_rand, SMP_RAND_LEN);
	if(cur_cb->pairing_method == SMP_LEGACY_PAIRING)
	{
		/* In case of legacy pairing, we need to generate the confirm on our end
		 * and compare the value before proceeding.
		 */
		cur_cb->state = SMP_STATE_WAIT_PEER_CNF_GEN;
		cur_cb->enc_stage = SMP_ENC_CONFIRM_S1;
		smp_handle_enc_operations(data);
	}
#if ( SECURE_CONNECTION )
	else
	{
		/* Secure connections */
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			/* we are slave */
			switch(cur_cb->asso_model)
			{
				case SMP_JW:
					/* Send the random number and then wait for dhkey check from master*/
					cur_cb->state = SMP_STATE_WAIT_DHKEY_CHECK_CMD;
					smp_send_rand_cmd();
					break;
				case SMP_JW_NC:
				case SMP_IIRD_NC:
				case SMP_IDRI_NC:
					/* generate and dispaly the Numeric value*/
					smp_send_rand_cmd();
					cur_cb->state = SMP_STATE_WAIT_NUMERIC_VALUE;
					smp_cal_numeric_value();
					break;
				case SMP_IIRD:
				case SMP_IDRI:
				case SMP_IIRI:
					/*Regenerate the commitment and compare*/
					cur_cb->state = SMP_STATE_WAIT_PEER_CNF_GEN;
					cur_cb->enc_stage = SMP_ENC_CONFIRM_S1;
					smp_handle_enc_operations(data);
					break;
			}
		}
		else
		{
			/* We are master*/
			/*Regenerate the commitment and compare*/
			cur_cb->state = SMP_STATE_WAIT_PEER_CNF_GEN;
			cur_cb->enc_stage = SMP_ENC_CONFIRM_S1;
			smp_handle_enc_operations(data);
		}
	}
#endif /* SECURE_CONNECTION */
}

/* This function is called when an encryption information command is received on the LE-U link*/
static void smp_enc_info_cmd_evt(UINT8* data)
{
	UINT8 *pp = g_local_adapter.smp_data.smp_cur_cb.cur_key.peer_ltk;
	UINT8* dat = data+1;
	logi("");
	if(g_local_adapter.smp_data.smp_cur_cb.state != SMP_STATE_WAIT_PEER_KEY_DIST)
	{
		logw("Event Not to be processed");
		return;
	}
	REVERSE_STREAM_TO_ARRAY(pp, dat, SMP_LTK_LEN );
	smp_start_cmd_timer();
}

/* This function is called when a master identification command is received on the LE-U link*/
static void smp_mast_id_cmd_evt(UINT8* data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 *pp = cur_cb->cur_key.peer_rand;
	UINT8* dat = (UINT8*)data + 1;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_PEER_KEY_DIST)
	{
		logw("Event Not to be processed");
		return;
	}

	STREAM_TO_UINT16(cur_cb->cur_key.peer_ediv, dat);
	REVERSE_STREAM_TO_ARRAY(pp, dat, SMP_LTK_RAND_LEN);
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		cur_cb->local_init_key = cur_cb->local_init_key^1;
		if(cur_cb->local_init_key == 0)
		{
			logd("Key sent by the peer finished");
			smp_key_dist_done_evt();
		}
		else
		{
			smp_start_cmd_timer();
		}
	}
	else
	{
		cur_cb->local_resp_key = cur_cb->local_resp_key^1;
		if(cur_cb->local_resp_key == 0)
		{
			logd("Key sent by the peer finished");
			smp_key_dist_start_evt();
		}
		else
		{
			smp_start_cmd_timer();
		}
	}
}
#if (PRIVACY_FEATURE)
/* This function is called when an identitiy information command is received on the LE-U link*/
static void smp_id_info_cmd_evt(UINT8* data)
{
	UINT8 *pp = g_local_adapter.smp_data.smp_cur_cb.cur_key.peer_irk;
	UINT8* dat = data+1;
	logi("");
	if(g_local_adapter.smp_data.smp_cur_cb.state != SMP_STATE_WAIT_PEER_KEY_DIST)
	{
		logw("Event Not to be processed");
		return;
	}
	REVERSE_STREAM_TO_ARRAY(pp, dat, SMP_IRK_LEN );
	smp_start_cmd_timer();
}

/* This function is called when an identity address information command is received on the LE-U link*/
static void smp_add_info_cmd_evt(UINT8 *data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 * dat;
	UINT8 *p;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_PEER_KEY_DIST)
	{
		logw("Event Not to be processed");
		return;
	}
	dat = data+1;
	STREAM_TO_UINT8(cur_cb->cur_key.id_addr_type, dat);
	p = cur_cb->cur_key.id_bdaddr;
	REVERSE_STREAM_TO_ARRAY(p, dat, BD_ADDR_LEN);
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		cur_cb->local_init_key = cur_cb->local_init_key^(SMP_ID_Y);
		if(cur_cb->local_init_key == 0)
		{
			logd("Key sent by the peer finished");
			smp_key_dist_done_evt();
		}
		else
		{
			smp_start_cmd_timer();
		}
	}
	else
	{
		cur_cb->local_resp_key = cur_cb->local_resp_key^(SMP_ID_Y);
		if(cur_cb->local_resp_key == 0)
		{
			logd("Key sent by the peer finished");
			smp_key_dist_start_evt();
		}
		else
		{
			smp_start_cmd_timer();
		}
	}
}
#endif /* PRIVACY_FEATURE */

#if (SIGNED_WRITE)
/* This function is called when an signing information command is received on the LE-U link*/
static void smp_sign_info_cmd_evt(UINT8* data)
{

	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 *pp = cur_cb->cur_key.peer_csrk;
	UINT8* dat = data+1;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_PEER_KEY_DIST)
	{
		logw("Event Not to be processed");
		return;
	}
	REVERSE_STREAM_TO_ARRAY(pp, dat, SMP_CSRK_LEN );
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		cur_cb->local_init_key = cur_cb->local_init_key^(SMP_SIGN_Y);
		if(cur_cb->local_init_key == 0)
		{
			logd("Key sent by the peer finished");
			smp_key_dist_done_evt();
		}
		else
		{
			smp_start_cmd_timer();
		}
	}
	else
	{
		cur_cb->local_resp_key = cur_cb->local_resp_key^(SMP_SIGN_Y);
		if(cur_cb->local_resp_key == 0)
		{
			logd("Key sent by the peer finished");
			smp_key_dist_start_evt();
		}
		else
		{
			smp_start_cmd_timer();
		}

	}
}
#endif /* SIGNED_WRITE */

/* This function is called when we receive a pairing failed command on LE-U link
 * The reason is passed on to the upper layer.
 */
static void  smp_pair_failed_cmd_evt(UINT8* data)
{
	logi("");
	if(g_local_adapter.smp_data.smp_cur_cb.state == SMP_STATE_IDLE)
	{
		logw("Event Not to be processed");
		return;
	}
	g_local_adapter.smp_data.smp_cur_cb.status = *(data+1);
	smp_stop_app_timer();
	smp_clean_up();
}

#if (SECURE_CONNECTION)
/* This function is called when a pairing public key command is received on LE-U link*/
static void smp_pairing_pub_key_cmd_evt(UINT8* data)
{
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_SC_PUB_KEY)
	{
		logw("Event not to be processes");
		return;
	}
	UINT8 *pp = cur_cb->peer_p256_key_x;
	REVERSE_STREAM_TO_ARRAY(pp, data, SMP_PUB_KEY_COORDINATE_LEN);
	pp = cur_cb->peer_p256_key_y;
	REVERSE_STREAM_TO_ARRAY(pp, data, SMP_PUB_KEY_COORDINATE_LEN);
	hex_dump("PEER PUBLIC KEY X:",cur_cb->peer_p256_key_x, SMP_PUB_KEY_COORDINATE_LEN);
	hex_dump("PEER PUBLIC KEY X:",cur_cb->peer_p256_key_y, SMP_PUB_KEY_COORDINATE_LEN);
	/* Now we will generate the dhkey*/
	g_local_adapter.smp_data.smp_cur_cb.state = SMP_STATE_WAIT_SC_DHKEY;
	smp_cal_dhkey();
}

/* This function is called when we receive a dhkey check command on LE-U link*/
static void smp_dhkey_check_cmd_evt(UINT8 *data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_DHKEY_CHECK_CMD && cur_cb->state != SMP_STATE_WAIT_NC
			&& cur_cb->state != SMP_STATE_WAIT_NUMERIC_VALUE)
	{
		logw("Event not to be processed");
		return;
	}
	/* Save the dhkey check value*/
	UINT8 *pp = cur_cb->peer_confirm;
	REVERSE_STREAM_TO_ARRAY(pp, data, SMP_MAX_KEY_LEN);
	if(cur_cb->state == SMP_STATE_WAIT_NC || cur_cb->state == SMP_STATE_WAIT_NUMERIC_VALUE)
	{
		//Still waiting for confirmation from our upper layer in case of numeric comparison;
		cur_cb->state = SMP_STATE_WAIT_DHKEY_CHECK_CMD;
	}
	else if(cur_cb->state == SMP_STATE_WAIT_DHKEY_CHECK_CMD)
	{
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			/*We are slave. We need to generate mackey and LTK and then re-compute
			 * the dhkey check sent by the master
			 */
			cur_cb->state = SMP_STATE_WAIT_LTK_GEN;
			smp_gen_ltk();
		}
		else
		{
			/* We are the master. We need to recompute the dhkey of slave
			 * and compare
			 */
			cur_cb->state = SMP_STATE_WAIT_PEER_DHKEY_CHECK_GEN;
			UINT8 iocap[3];
			iocap[0] = cur_cb->peer_auth_req;
			iocap[1] = cur_cb->peer_oob_flag;
			iocap[2] = cur_cb->peer_io_cap;
			UINT8 local_bdaddr[BD_ADDR_LEN + 1];
			UINT8 peer_bdaddr[BD_ADDR_LEN + 1];
			local_bdaddr[0] = g_local_adapter.connected_device[cur_cb->conn_id]->local_addr_type;
			peer_bdaddr[0] = g_local_adapter.connected_device[cur_cb->conn_id]->bdaddr_type;
			memcpy(local_bdaddr + 1, g_local_adapter.connected_device[cur_cb->conn_id]->local_bdaddr, BD_ADDR_LEN );
			memcpy(peer_bdaddr + 1, g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr, BD_ADDR_LEN);
			smp_f6(cur_cb->mackey, cur_cb->peer_rand, cur_cb->local_rand, cur_cb->tk, iocap,
					peer_bdaddr, local_bdaddr);
		}
	}
}
#endif /* SECURE_CONNECTION */
/* This function is called when a random number(128 bit) is generated
 *  by the controller. Typically a random number is generated and is immediately
 *  followed by confirm generation. But in case of secure connection's numerical
 *  comparison or just works, the master will not generate a confirm(commitment).
 *  It will only send a random number.
 */
static void smp_rand_gen_evt()
{
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_CNF_GEN && cur_cb->state != SMP_STATE_WAIT_RAND_GEN)
	{
		logw("Event not to be processed");
		return;
	}
	if(cur_cb->state == SMP_STATE_WAIT_CNF_GEN)
	{
		/* The random number was generated for the purpose of
		 * confirm(commitment) generation.
		 */
		cur_cb->enc_stage = SMP_ENC_CONFIRM_S1;
		smp_handle_enc_operations(NULL);
		return;
	}
	if(cur_cb->state == SMP_STATE_WAIT_RAND_GEN)
	{
		/*
		 * The random number was generated on master side in case of
		 * JW/Numeric comparison
		 */
		cur_cb->state = SMP_STATE_WAIT_RAND_CMD;
		smp_send_rand_cmd();
	}
}

/* This function is called once the confirm ( commitment ) value is calculate*/

static void smp_confirm_gen_evt(UINT8* data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8* pp;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_CNF_GEN && cur_cb->state != SMP_STATE_WAIT_PEER_CNF_GEN)
	{
		logw("Event Not to be processed");
		return;
	}
	if(cur_cb->state == SMP_STATE_WAIT_CNF_GEN)
	{
		/* This state  means that we were waiting for the local confirm value
		 * So the generated confirm is sent to the peer device
		 */
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			/* we are slave */
			cur_cb->state = SMP_STATE_WAIT_RAND_CMD;
		}
		else
		{
			/* We are master*/
			cur_cb->state = SMP_STATE_WAIT_CNF_CMD;
		}
		pp = cur_cb->local_confirm;
		REVERSE_ARRAY_TO_STREAM(pp, data, SMP_CONFIRM_LEN);
		smp_send_confirm_cmd();
	}
	else if(cur_cb->state == SMP_STATE_WAIT_PEER_CNF_GEN)
	{
		/* This state means that we were waiting for the regeneration of peer confirm
		 * Now we need to compare the regenerated confirm with the confirm received over LE-U
		 */
		cur_cb->state = SMP_STATE_WAIT_STK_GEN;// check
		smp_compare_confirm(data);
	}
}


/* This function is called when STK generated for legacy pairing*/
static void smp_link_key_cal_evt()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_STK_GEN)
	{
		logw("Event Not to be processed");
		return;
	}
	cur_cb->state = SMP_STATE_WAIT_ENC_CHG;
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		smp_hci_enc_key_reply(g_local_adapter.connected_device[cur_cb->conn_id]->acl_handle, cur_cb->stk);
	}
	else
	{
		smp_start_enc();
	}
}

/* This function is called when the Link encryption has changed */
static void smp_enc_chg_evt()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_ENC_CHG)
	{
		logw("Event Not to be processed");
		return;
	}
	if(cur_cb->enc_with_ltk)
	{
		/* This encryption change happened due to a already bonded device(re-encryption)
		 * Hence we should end the smp activity.
		 */
		cur_cb->status = 0;
		smp_clean_up();
		return;
	}
	if((cur_cb->local_auth_req & SMP_BONDING_Y) == 0 && (cur_cb->peer_auth_req & SMP_BONDING_Y) == 0)
	{
		/* Both the parties has said no bonding. So no need distribute any keys*/
		cur_cb->status = 0;
		smp_clean_up();
		return;
	}
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		/* We are the slave. We should start distributing the keys*/
		cur_cb->state = SMP_STATE_WAIT_LOCAL_KEY_DIST;
		smp_start_key_dist();
	}
	else
	{
		/* We are the master. We should first receive the keys from the slave*/
		cur_cb->state = SMP_STATE_WAIT_PEER_KEY_DIST;
		smp_check_key_dist();
	}
}



/* This function is called to start/continue the key distribution*/
static void smp_key_dist_start_evt()
{
	logi("");
	if(g_local_adapter.smp_data.smp_cur_cb.state != SMP_STATE_WAIT_PEER_KEY_DIST &&
			g_local_adapter.smp_data.smp_cur_cb.state != SMP_STATE_WAIT_LOCAL_KEY_DIST)
	{
		logw("Event Not to be processed");
		return;
	}
	smp_start_key_dist();
}

/* This function is called when key distribution is done */
static void smp_key_dist_done_evt()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_LOCAL_KEY_DIST && cur_cb->state != SMP_STATE_WAIT_PEER_KEY_DIST)
	{
		logw("Event Not to be processed");
		return;
	}
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		/* We are slave*/
		if(cur_cb->state == SMP_STATE_WAIT_PEER_KEY_DIST)
		{
			/* If peer has finished the key distribution, then we are done with
			 * with the bonding. Save the keys and clean-up
			 */
			cur_cb->state = SMP_STATE_IDLE;
			cur_cb->status = 0;
			logd("Curent key distributed = %d", cur_cb->cur_key.keys_distributed);
			g_local_adapter.connected_device[cur_cb->conn_id]->link_enc_state.keys_distributed = cur_cb->cur_key.keys_distributed;
			smp_mgr_save_bonding_keys(g_local_adapter.connected_device[cur_cb->conn_id], &(cur_cb->cur_key));
			smp_clean_up();
		}
		else if(cur_cb->state == SMP_STATE_WAIT_LOCAL_KEY_DIST)
		{
			/* If we are done with the local key distribution, then wait for the master
			 * to distribute the keys
			 */
			cur_cb->state = SMP_STATE_WAIT_PEER_KEY_DIST;
			smp_check_key_dist();
		}
	}
	else
	{
		/* We are master*/
		if(cur_cb->state == SMP_STATE_WAIT_PEER_KEY_DIST)
		{
			/* If slave has done with the key distribution, then start key distribution*/
			cur_cb->state = SMP_STATE_WAIT_LOCAL_KEY_DIST;
			smp_start_key_dist();
		}
		else if(cur_cb->state == SMP_STATE_WAIT_LOCAL_KEY_DIST)
		{
			/* If we have distributed the keys, then we are done with the bonding.
			 * Save the keys and clean-up
			 */
			cur_cb->state = SMP_STATE_IDLE;
			cur_cb->status = 0;
			g_local_adapter.connected_device[cur_cb->conn_id]->link_enc_state.keys_distributed = cur_cb->cur_key.keys_distributed;
			smp_mgr_save_bonding_keys(g_local_adapter.connected_device[cur_cb->conn_id], &(cur_cb->cur_key));
			smp_clean_up();
		}

	}
}
#if (SIGNED_WRITE)
/* This function is called when a sign is generated.
 * The generated signature could be used for data signing or sign verification
 */
static void smp_sign_gen_evt(UINT8 *data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 *pp;
	connected_device_t *device;
	logi("");
	if(cur_cb->state != SMP_STATE_WAIT_SIGN_GEN)
	{
		logw("Event Not to be processed");
		return;
	}
	pp = data + 8;
	device = g_local_adapter.connected_device[cur_cb->conn_id];
	if(cur_cb->sign_gen)
	{
		/* The signature to be used for data signing.
		 * So give back the signature mac to the upper layer (GATT/ATT)
		 */
		UINT8 signed_data[8];
		REVERSE_STREAM_TO_ARRAY(signed_data, pp, 8);
		memset(cur_cb, 0, sizeof(smp_cb_t));
		smp_mgr_data_sign_cback(device, SMP_SUCCESS, signed_data);
	}
	else
	{
		/* The signature to be used for sign verification.
		 * Do the comparison here and give the status to upper layer (GATT/ATT).
		 */
		UINT8 signed_data[8];
		int status;
		STREAM_TO_ARRAY(signed_data, pp, 8);
		hex_dump("SIGN:", signed_data, 8);
		status = memcmp(signed_data, cur_cb->data_to_be_verified, 8);
		dealloc(cur_cb->data_to_be_verified);
		memset(cur_cb, 0, sizeof(smp_cb_t));
		smp_mgr_data_verify_cback(cur_cb->conn_id, (status == 0 ? SMP_SUCCESS:SMP_FAILED));
	}
}
#endif /* SIGNED_WRITE */

/* This function is called when we have completed a aes-mac operation
 * AES-CAM is used for the following functions/algorithms
 * 1. Data signing
 * 2. Sign Verification
 * 3. Secure connections confirm generation function f4
 * 4. Secure connections key generation function f5
 * 5. Secure connections check value generation function f6
 * 6. Secure connections Numeric comparison function g2
 */
static void smp_aes_cmac_gen_evt()
{

#if ( SECURE_CONNECTION)
	static UINT8 state = SMP_ENC_GEN_T;
#endif /*SECURE_CONNECTION*/

	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 data[SMP_MAX_KEY_LEN];
	UINT8 *pp = cur_cb->cmac_data;
	REVERSE_STREAM_TO_ARRAY(data, pp, SMP_MAX_KEY_LEN);
	dealloc(cur_cb->cmac_data);
	logi("");
	switch(cur_cb->state)
	{
		case SMP_STATE_WAIT_SIGN_GEN:
			/* Both data signing and sign verification is handled here */
			smp_sign_gen_evt(data);
			break;
#if ( SECURE_CONNECTION )
		case SMP_STATE_WAIT_CNF_GEN:
		case SMP_STATE_WAIT_PEER_CNF_GEN:
			/* Confirm generation function f4 is handled here*/
			smp_confirm_gen_evt(data);
			break;
		case SMP_STATE_WAIT_NUMERIC_VALUE:
			/* Numeric comparison generation function g2 is handled here*/
			smp_numeric_check_value_generate_evt(data);
			break;
		case SMP_STATE_WAIT_LTK_GEN:
			/* Key generation function f5 is handled here
			 * Key generation happens in three steps
			 * 1) key for 2-3 steps (T) is generated
			 * 2) Mac key is generate
			 * 3) Link key is generated
			 */
			switch(state)
			{
				case SMP_ENC_GEN_T :
					state = SMP_ENC_GEN_SC_MACKEY;
					logd("SMP_ENC_GEN_T");
					pp = data;
					REVERSE_STREAM_TO_ARRAY(cur_cb->f5_t, pp, SMP_MAX_KEY_LEN);
					smp_aes_cmac(cur_cb->f5_data, SMP_F5_DATA_LEN, cur_cb->f5_t);
					break;
				case SMP_ENC_GEN_SC_MACKEY :
					state = SMP_ENC_GEN_SC_LTK;
					pp = data;
					REVERSE_STREAM_TO_ARRAY(cur_cb->mackey, pp, SMP_MAX_KEY_LEN);
					hex_dump("Mackey:", cur_cb->mackey, SMP_MAX_KEY_LEN);
					cur_cb->f5_data[0] = 1;
					smp_aes_cmac(cur_cb->f5_data, SMP_F5_DATA_LEN, cur_cb->f5_t);
					break;
				case SMP_ENC_GEN_SC_LTK :
					pp = data;
					REVERSE_STREAM_TO_ARRAY(cur_cb->cur_key.local_ltk, pp, SMP_MAX_KEY_LEN);
					smp_mask_key(cur_cb->cur_key.local_ltk, cur_cb->local_enc_key_size);
					memcpy(cur_cb->cur_key.peer_ltk, cur_cb->cur_key.local_ltk, SMP_MAX_KEY_LEN);
					hex_dump("LTK:", cur_cb->cur_key.local_ltk, SMP_MAX_KEY_LEN);
					UINT8 local_key_dist = cur_cb->local_init_key | (SMP_ENC_Y | SMP_ID_N | SMP_SIGN_N);
					UINT8 remote_key_dist = cur_cb->local_resp_key | (SMP_ENC_Y | SMP_ID_N | SMP_SIGN_N);
					cur_cb->cur_key.keys_distributed = (local_key_dist << 4)|(remote_key_dist);
					smp_ltk_gen_evt();
					state = SMP_ENC_GEN_T;
					break;
			}
			break;
		case SMP_STATE_WAIT_DHKEY_CHECK_GEN:
		case SMP_STATE_WAIT_PEER_DHKEY_CHECK_GEN:
			/* check value generation function f6 is handled here*/
			smp_dhkey_check_gen_evt(data);
			break;
#endif /*SECURE_CONNECTION */
		default:
			logw("Event not to be processed");
			break;

	}
}

/* This function is called when the peer device has disconnected
 * We need to clean_up now
 */
static void smp_l2c_disconn_evt()
{
	logi("");
	g_local_adapter.smp_data.smp_cur_cb.status = SMP_UNSPECIFIED_REASON;
	smp_clean_up();
}

/* This function is called when a local failure happens with the bonding.
 * We send the pairing failed command on LE-U link( to the peer) and the
 * status is updated to the upper layer
 */
static void smp_pair_failed_evt()
{
	logi("");
	smp_send_fail_cmd();
	smp_clean_up();
}

#if (SECURE_CONNECTION)
/* This function is called when dhkey is generated */
static void smp_dhkey_gen_evt(UINT8 *data)
{
	logi("");
	if(g_local_adapter.smp_data.smp_cur_cb.state != SMP_STATE_WAIT_SC_DHKEY
			&& g_local_adapter.smp_data.smp_cur_cb.state != SMP_STATE_WAIT_CNF_CMD)
	{
		logd("Event not to be processed");
		return;
	}
	UINT8 *pp = g_local_adapter.smp_data.smp_cur_cb.dhkey;
	REVERSE_STREAM_TO_ARRAY(pp, data, SMP_DHKEY_LEN);
	if(g_local_adapter.connected_device[g_local_adapter.smp_data.smp_cur_cb.conn_id]->local_link_role)
	{
		/* We are slave. We will send the public key now*/
		smp_send_pub_key_cmd();
	}
	else
	{
		logd("Current state = %d", g_local_adapter.smp_data.smp_cur_cb.state);
		if(g_local_adapter.smp_data.smp_cur_cb.state == SMP_STATE_WAIT_CNF_CMD)
		{
			 /* Only master will receive a confirm command in these association model*/
			g_local_adapter.smp_data.smp_cur_cb.state = SMP_STATE_WAIT_RAND_GEN;
			smp_gen_rand();
			return;
		}
	}
	smp_start_pairing_phase2();
}

/* This function is called when the numeric comparison value (Secure connections)
 * is calculated. We need to give this value to the upper layer (smp_app) So that it can
 * be displayed to the user and get his confirmation( whether value is matching with the
 * value on the peer device).
 */
static void smp_numeric_check_value_generate_evt(UINT8 *data)
{
	UINT32 numeric_value;
	UINT8 *pp = (UINT8*)&numeric_value;
	STREAM_TO_ARRAY(pp, data, 4);
	hex_dump("NC =", (UINT8*)&numeric_value, 4);
	logd("Numeric value = %u", numeric_value);
	numeric_value = numeric_value % 1000000;
	logd("Numeric value = %d", numeric_value);
	g_local_adapter.smp_data.smp_cur_cb.state = SMP_STATE_WAIT_NC;
	smp_start_app_timer();
	smp_mgr_cback(g_local_adapter.connected_device[g_local_adapter.smp_data.smp_cur_cb.conn_id]->id_addr.bdaddr,
			SMP_NUMERIC_COMPARISON_EVT, (UINT8*)&numeric_value, sizeof(numeric_value));

}

/* This function is called when LTK for secure connection is calculated  */
static void smp_ltk_gen_evt()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 iocap[3];
	UINT8 local_bdaddr[BD_ADDR_LEN + 1];
	UINT8 peer_bdaddr[BD_ADDR_LEN + 1];
	local_bdaddr[0] = g_local_adapter.connected_device[cur_cb->conn_id]->local_addr_type;
	peer_bdaddr[0] = g_local_adapter.connected_device[cur_cb->conn_id]->bdaddr_type;
	memcpy(local_bdaddr + 1, g_local_adapter.connected_device[cur_cb->conn_id]->local_bdaddr, BD_ADDR_LEN );
	memcpy(peer_bdaddr + 1, g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr, BD_ADDR_LEN);
	hex_dump("Local bdaddr :", g_local_adapter.connected_device[cur_cb->conn_id]->local_bdaddr, BD_ADDR_LEN );
	logi("");
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		/* We are slave
		 * We need to re-calculate the dhkey check sent by the master
		 */
		cur_cb->state = SMP_STATE_WAIT_PEER_DHKEY_CHECK_GEN;
		iocap[0] = cur_cb->peer_auth_req;
		iocap[1] = cur_cb->peer_oob_flag;
		iocap[2] = cur_cb->peer_io_cap;
		smp_f6(cur_cb->mackey, cur_cb->peer_rand, cur_cb->local_rand, cur_cb->tk, iocap,
				peer_bdaddr, local_bdaddr);

	}
	else
	{
		/* We are the master.
		 * We need to generate a dhkey check now.
		 */
		cur_cb->state = SMP_STATE_WAIT_DHKEY_CHECK_GEN;
		iocap[0] = cur_cb->local_auth_req;
		iocap[1] = cur_cb->local_oob_flag;
		iocap[2] = cur_cb->local_io_cap;
		smp_f6(cur_cb->mackey, cur_cb->local_rand, cur_cb->peer_rand, cur_cb->tk, iocap,
				local_bdaddr, peer_bdaddr);
	}
}

/* This function is called when a dhkey check value is generated by f6.
 *
 */
static void smp_dhkey_check_gen_evt(UINT8 *data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->state == SMP_STATE_WAIT_DHKEY_CHECK_GEN)
	{
		/* This was a local dhkey check value. We need to send it to the peer */
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			/* We are slave. Once dhkey is re-calculated by the master, he is expected to
			 * initiate the encryption on the link with the LTK generated.
			 */
			cur_cb->state = SMP_STATE_WAIT_ENC_CHG;
		}
		else
		{
			/* We are master. The slave is expected to send his dhkey check value now*/
			cur_cb->state = SMP_STATE_WAIT_DHKEY_CHECK_CMD;
		}
		smp_send_dhkey_check_cmd(data);
	}
	else if(cur_cb->state == SMP_STATE_WAIT_PEER_DHKEY_CHECK_GEN)
	{
		/* We have re-computed the peer's dhkey. We now need to compare it with the
		 * value received on the LE-U
		 */
		smp_dhkey_compare(data);
	}
}
#endif /* SECURE_CONNECTION */



/********************************************* SMP L2CAP functions *********************************/

void smp_l2cap_connect_cb(connected_device_t *device)
{
	logi("");
}

void smp_l2cap_disconnect_cb(connected_device_t *device)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if(device == NULL)
	{
		loge("Invalid device pointer");
		return;
	}
#endif
	if(memcmp(device->bdaddr, g_local_adapter.smp_data.smp_cur_cb.bdaddr, BD_ADDR_LEN) != 0)
	{
		return;
	}
	smp_stop_cmd_timer();
	g_local_adapter.smp_data.smp_cur_cb.status = SMP_UNSPECIFIED_REASON;
	smp_l2c_disconn_evt();
}

/* This function is called by L2CAP layer when a data packet is received in SMP channel*/

INT8 smp_l2cap_recv_data_cb(connected_device_t *device, UINT8* data,
		UINT16 data_len)
{
	UINT8 cmd_opcode;
	UINT8 *pp = data;
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	if (data_len < sizeof(cmd_opcode))
		return STATUS_ERR_INVALID_PARAM;
	STREAM_TO_UINT8(cmd_opcode, pp);
	if(cmd_opcode != SMP_PAIRING_REQ && cmd_opcode != SMP_SEC_REQ)
	{
		logd("cmd_opcode = %d", cmd_opcode);
		if(memcmp(device->bdaddr, cur_cb->bdaddr, BD_ADDR_LEN) != 0)
		{
			return STATUS_SUCCESS;
		}
	}
	switch (cmd_opcode) {
		case SMP_PAIRING_REQ:
			logd("Pairing request");
			if(cur_cb->state == SMP_STATE_IDLE)
			{
				logd("Accepting the request");
				memcpy(cur_cb->bdaddr, device->bdaddr, BD_ADDR_LEN);
				cur_cb->conn_id = device->idx;
				cur_cb->operation = SMP_BONDING_OPERATION;
			}
			else
			{
				if(memcmp(device->bdaddr, cur_cb->bdaddr, BD_ADDR_LEN) != 0)
				{
					break;
				}
			}
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_PAIRING_REQ_LEN)
			{
				logd("Data length not matching with pairing request length");
				break;
			}
	#endif
			smp_pair_cmd_evt(data);
			break;
		case SMP_PAIRING_RSP:
			logd("Pairing Response");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_PAIRING_RSP_LEN)
			{
				logd("Data length not matching with pairing response length");
				break;
			}
	#endif
			smp_pair_cmd_evt(data);
			break;
		case SMP_PAIRING_CFM:
			logd("Pairing confirm");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_PAIRING_CFM_LEN)
			{
				logd("Data length not matching with pairing confirm length");
				break;
			}
	#endif
			smp_confirm_cmd_evt(data + 1);
			break;
		case SMP_PAIRING_RND:
			logd("Pairing Random");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_PAIRING_RND_LEN)
			{
				logd("Data length not matching with pairing random length");
				break;
			}
	#endif
			smp_rand_cmd_evt(data);
			break;
		case SMP_ENC_INF:
			logd("Encryption Information");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_ENC_INF_LEN)
			{
				logd("Data length not matching with encryption information length");
				break;
			}
	#endif
			smp_enc_info_cmd_evt(data);
			break;
		case SMP_MASTER_IDF:
			logd("Master Identification");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_MASTER_IDF_LEN)
			{
				logd("Data length not matching with pairing random length");
				break;
			}
	#endif
			smp_mast_id_cmd_evt(data);
			break;
		case SMP_IDENTITY_INF:
			logd("Identity Information");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_IDENTITY_INF_LEN)
			{
				logd("Data length not matching with identity information length");
				break;
			}
	#endif
#if (PRIVACY_FEATURE)
			smp_id_info_cmd_evt(data);
#endif /* PRIVACY_FEATURE */
			break;
		case SMP_IDENTITY_ADD_INF:
			logd("Identity Address Information");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_IDENTITY_ADD_INF_LEN)
			{
				logd("Data length not matching with pairing random length");
				break;
			}
	#endif
#if (PRIVACY_FEATURE)
			smp_add_info_cmd_evt(data);
#endif /* PRIVACY_FEATURE */
			break;
		case SMP_SIGN_INF:
			logd("Signing Information");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_SIGN_INF_LEN)
			{
				logd("Data length not matching with signing information length");
				break;
			}
	#endif
#if (SIGNED_WRITE)
			smp_sign_info_cmd_evt(data);
#endif /* SIGNED_WRITE */
			break;
	case SMP_SEC_REQ:
			logd("Security Request");
			if(cur_cb->state == SMP_STATE_IDLE)
			{
				logd("Accepting the request");
				memcpy(cur_cb->bdaddr, device->bdaddr, BD_ADDR_LEN);
				cur_cb->conn_id = device->idx;
				cur_cb->operation = SMP_BONDING_OPERATION;
				cur_cb->remote_initiated = TRUE;
	#if (PARANOID_STACK == TRUE)
				if (data_len != SMP_SEC_REQ_LEN)
				{
					logd("Data length not matching with security request length");
					break;
				}
	#endif
				smp_sec_req_cmd_evt(data);
			}
			break;
		case SMP_PAIRING_PUB_KEY :
			logd("Public key");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_PAIRING_PUB_KEY_LEN)
			{
				logd("Data length not matching with public key length");
				break;
			}
	#endif
#if (SECURE_CONNECTION)
			smp_pairing_pub_key_cmd_evt(data + 1);
#endif /* SECURE_CONNECTION */
			break;
		case SMP_DHKEY_CHECK :
			logd("Dhkey");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_DHKEY_CHECK_LEN)
			{
				logd("Data length not matching with dhkey check length");
				break;
			}
	#endif
#if (SECURE_CONNECTION)
			smp_dhkey_check_cmd_evt(data + 1);
#endif /* SECURE_CONNECTION */
			break;
		case SMP_PAIRING_FAILED:
			logd("Pairing failed");
			smp_stop_cmd_timer();
	#if (PARANOID_STACK == TRUE)
			if (data_len != SMP_PAIRING_FAILED_LEN)
			{
				logd("Data length not matching with pairing failed length");
				break;
			}
	#endif
			smp_pair_failed_cmd_evt(data);
			break;
	}
	return STATUS_SUCCESS;
}


/****************************************SMP event Handler and Action functions****************************/

static INT8 smp_send_pair_cmd()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_PAIRING_REQ_LEN);
	UINT8 *cmd;
	UINT8 *pairing_cmd;
	logi("");
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_PAIRING_REQ_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	pairing_cmd = NULL;
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		UINT8_TO_STREAM(cmd, SMP_PAIRING_RSP);
		pairing_cmd = cur_cb->pairing_rsp;
		if(cur_cb->peer_enc_key_size < cur_cb->local_enc_key_size)
		{
			cur_cb->local_enc_key_size = cur_cb->peer_enc_key_size;
		}
	}
	else
	{
		UINT8_TO_STREAM(cmd, SMP_PAIRING_REQ);
		pairing_cmd = cur_cb->pairing_req;
	}
	UINT8_TO_STREAM(cmd, cur_cb->local_io_cap);
	UINT8_TO_STREAM(cmd, cur_cb->local_oob_flag);
	UINT8_TO_STREAM(cmd, cur_cb->local_auth_req);
	UINT8_TO_STREAM(cmd, cur_cb->local_enc_key_size);
	UINT8_TO_STREAM(cmd, cur_cb->local_init_key);
	UINT8_TO_STREAM(cmd, cur_cb->local_resp_key);
	cmd = &data_pkt->data[data_pkt->offset];
	REVERSE_ARRAY_TO_STREAM(pairing_cmd, cmd, SMP_PAIRING_REQ_LEN);
	smp_start_cmd_timer();
	return l2cap_data_send(cur_cb->conn_id, SMP_CID, data_pkt);
}

static INT8 smp_send_security_request_cmd(UINT8 req_sec_level)
{
	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_SEC_REQ_LEN);
	UINT8 *cmd;
	logi("");
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_SEC_REQ_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_SEC_REQ);
	UINT8_TO_STREAM(cmd, req_sec_level);
	smp_start_cmd_timer();
	return l2cap_data_send(g_local_adapter.smp_data.smp_cur_cb.conn_id, SMP_CID,data_pkt);
}

static INT8 smp_send_confirm_cmd()
{
	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_PAIRING_CFM_LEN);
	UINT8 *cmd;
	logi("");
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_PAIRING_CFM_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_PAIRING_CFM);
	REVERSE_ARRAY_TO_STREAM(cmd, g_local_adapter.smp_data.smp_cur_cb.local_confirm, SMP_CONFIRM_LEN);
	smp_start_cmd_timer();
	return l2cap_data_send(g_local_adapter.smp_data.smp_cur_cb.conn_id, SMP_CID, data_pkt);
}

static INT8 smp_send_rand_cmd()
{
	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_PAIRING_RND_LEN);
	UINT8 *cmd;
	logi("");
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_PAIRING_RND_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_PAIRING_RND);
	REVERSE_ARRAY_TO_STREAM(cmd, g_local_adapter.smp_data.smp_cur_cb.local_rand, SMP_RAND_LEN);
	smp_start_cmd_timer();
	return l2cap_data_send(g_local_adapter.smp_data.smp_cur_cb.conn_id, SMP_CID, data_pkt);
}
static INT8 smp_send_enc_info_cmd()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_ENC_INF_LEN);
	UINT8 *cmd;
	INT8 ret;
	logi("");
	hex_dump("LTK:", cur_cb->cur_key.local_ltk, SMP_LTK_LEN);
	hex_dump("Rand:", cur_cb->cur_key.local_rand, SMP_LTK_RAND_LEN);
	logd("EDIV:%x", cur_cb->cur_key.local_ediv);
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_ENC_INF_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_ENC_INF);
	REVERSE_ARRAY_TO_STREAM(cmd, cur_cb->cur_key.local_ltk, SMP_LTK_LEN);
	ret = l2cap_data_send(cur_cb->conn_id, SMP_CID, data_pkt);
	if(ret != STATUS_SUCCESS)
	{
		return ret;
	}
	data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_MASTER_IDF_LEN);
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_MASTER_IDF_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_MASTER_IDF);
	UINT16_TO_STREAM(cmd, cur_cb->cur_key.local_ediv);
	REVERSE_ARRAY_TO_STREAM(cmd, cur_cb->cur_key.local_rand, SMP_LTK_RAND_LEN);
	ret = l2cap_data_send(cur_cb->conn_id, SMP_CID, data_pkt);
	if(ret != STATUS_SUCCESS)
		return ret;
	smp_key_dist_start_evt();
	return STATUS_SUCCESS;
}

#if (PRIVACY_FEATURE)
static INT8 smp_send_id_info_cmd()
{
	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_IDENTITY_INF_LEN);
	UINT8 *cmd;
	INT8 ret;
	logi("");
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_IDENTITY_INF_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_IDENTITY_INF);
	REVERSE_ARRAY_TO_STREAM(cmd, g_local_adapter.smp_data.device_irk, SMP_IRK_LEN);
	memcpy(g_local_adapter.smp_data.smp_cur_cb.cur_key.local_irk, g_local_adapter.smp_data.device_irk, SMP_IRK_LEN);
	ret = l2cap_data_send(g_local_adapter.smp_data.smp_cur_cb.conn_id, SMP_CID, data_pkt);
	if(ret != STATUS_SUCCESS)
		return ret;
	data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_IDENTITY_ADD_INF_LEN);
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_IDENTITY_ADD_INF_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_IDENTITY_ADD_INF);
	UINT8_TO_STREAM(cmd, 0);
	REVERSE_ARRAY_TO_STREAM(cmd, g_local_adapter.static_bdaddr, BD_ADDR_LEN);
	ret = l2cap_data_send(g_local_adapter.smp_data.smp_cur_cb.conn_id, SMP_CID, data_pkt);
	if(ret == STATUS_SUCCESS)
		smp_key_dist_start_evt();
	return ret;
}
#endif /* PRIVACY_FEATURE */

#if (SIGNED_WRITE)
static INT8 smp_send_sign_info_cmd()
{
	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_SIGN_INF_LEN);
	UINT8 *cmd;
	INT8 ret;
	logi("");
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_SIGN_INF_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_SIGN_INF);
	REVERSE_ARRAY_TO_STREAM(cmd,g_local_adapter.smp_data.smp_cur_cb.cur_key.local_csrk, SMP_CSRK_LEN);
	ret = l2cap_data_send(g_local_adapter.smp_data.smp_cur_cb.conn_id, SMP_CID, data_pkt);
	if(ret == STATUS_SUCCESS)
		smp_key_dist_start_evt();
	return ret;
}
#endif /* SIGNED_WRITE */

#if (SECURE_CONNECTION)
static INT8 smp_send_pub_key_cmd()
{
	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_PAIRING_PUB_KEY_LEN);
	UINT8 *cmd;
	logi("");
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_PAIRING_PUB_KEY_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_PAIRING_PUB_KEY);
	REVERSE_ARRAY_TO_STREAM(cmd, g_local_adapter.smp_data.local_p256_key_x, SMP_PUB_KEY_COORDINATE_LEN);
	REVERSE_ARRAY_TO_STREAM(cmd, g_local_adapter.smp_data.local_p256_key_y, SMP_PUB_KEY_COORDINATE_LEN);
	smp_start_cmd_timer();
	return l2cap_data_send(g_local_adapter.smp_data.smp_cur_cb.conn_id, SMP_CID,data_pkt);
}
static INT8 smp_send_dhkey_check_cmd(UINT8 *data)
{

	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_DHKEY_CHECK_LEN);
	UINT8 *cmd ;
	logi("");
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_DHKEY_CHECK_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_DHKEY_CHECK);
	memcpy(cmd, data, SMP_MAX_KEY_LEN);
	smp_start_cmd_timer();
	return l2cap_data_send(g_local_adapter.smp_data.smp_cur_cb.conn_id, SMP_CID,data_pkt);

}
#endif /* SECURE_CONNECTION */

static INT8 smp_send_fail_cmd()
{
	buffer_t *data_pkt;
	UINT8 *cmd;
	logi("");
	if(g_local_adapter.smp_data.smp_cur_cb.status == SMP_SUCCESS)
	{
		return STATUS_SUCCESS;
	}
	data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_PAIRING_FAILED_LEN);
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = SMP_PAIRING_FAILED_LEN;
	cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, SMP_PAIRING_FAILED);
	UINT8_TO_STREAM(cmd, g_local_adapter.smp_data.smp_cur_cb.status);
	return l2cap_data_send(g_local_adapter.smp_data.smp_cur_cb.conn_id, SMP_CID, data_pkt);
}

static BOOLEAN compare_auth_request()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	if(cur_cb->local_auth_level_min & SMP_SC_Y)
	{
		if(!(cur_cb->peer_auth_req & SMP_SC_Y))
			return FALSE;
	}
	if(cur_cb->local_auth_level_min & SMP_MITM_Y)
	{
		/* We need to check the io capability */
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			cur_cb->asso_model =
					io_cap_mapping[cur_cb->local_io_cap][cur_cb->peer_io_cap];
		}
		else
		{
			cur_cb->asso_model =
					io_cap_mapping[cur_cb->peer_io_cap][cur_cb->local_io_cap];
		}
		if(cur_cb->asso_model == SMP_JW)
			return FALSE;
	}
	return TRUE;

}


/* This function is called to decide the association model to be used in the second phase
 * of pairing. This function will decide the association model and then trigger the
 * corresponding method ( either passkey generation/passkey entery).
 */
static void smp_decide_asso_model()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if((cur_cb->local_auth_req & SMP_MITM_Y) || (cur_cb->peer_auth_req & SMP_MITM_Y))
	{
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			cur_cb->asso_model =
					io_cap_mapping[cur_cb->local_io_cap][cur_cb->peer_io_cap];
		}
		else
		{
			cur_cb->asso_model =
					io_cap_mapping[cur_cb->peer_io_cap][cur_cb->local_io_cap];
		}
	}
	else
	{
		cur_cb->asso_model = SMP_JW;
	}
	logd("Associate model selected is %x", cur_cb->asso_model);
	if(cur_cb->pairing_method == SMP_LEGACY_PAIRING)
	{
		/* In case of legacy pairing, Numeric comparison is not present. So switching to basic
		 * association model.
		 */
		switch(cur_cb->asso_model)
		{
		case SMP_JW_NC :
			cur_cb->asso_model = SMP_JW;
			cur_cb->cur_key.key_type = SMP_KEY_TYPE_UNAUTHENTICATED;
			cur_cb->cur_key.security_level = SMP_SEC_LVL_2;
			break;
		case SMP_IIRD_NC :
			cur_cb->asso_model = SMP_IIRD;
			cur_cb->cur_key.key_type = SMP_KEY_TYPE_AUTHENTICATED;
			cur_cb->cur_key.security_level = SMP_SEC_LVL_3;
			break;
		case SMP_IDRI_NC :
			cur_cb->asso_model = SMP_IDRI;
			cur_cb->cur_key.key_type = SMP_KEY_TYPE_AUTHENTICATED;
			cur_cb->cur_key.security_level = SMP_SEC_LVL_3;
			break;
		case SMP_JW:
			cur_cb->cur_key.key_type = SMP_KEY_TYPE_UNAUTHENTICATED;
			cur_cb->cur_key.security_level = SMP_SEC_LVL_2;
			break;
		case SMP_IIRD:
		case SMP_IIRI:
		case SMP_IDRI:
			cur_cb->cur_key.key_type = SMP_KEY_TYPE_AUTHENTICATED;
			cur_cb->cur_key.security_level = SMP_SEC_LVL_3;
			break;
		}
	}
#if (SECURE_CONNECTION)
	else
	{
		if(cur_cb->asso_model == SMP_JW)
		{
			cur_cb->cur_key.key_type = SMP_KEY_TYPE_SC_UNAUTHENTICATED;
			cur_cb->cur_key.security_level = SMP_SEC_LVL_2;
		}
		else
		{
			cur_cb->cur_key.key_type = SMP_KEY_TYPE_SC_AUTHENTICATED;
			cur_cb->cur_key.security_level = SMP_SEC_LVL_4;
 		}
 	}
#endif /* SECURE_CONNECTION*/
}

static void smp_start_pairing_phase2()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	/* Now we will take action based on the selected
		 * association model
		 */
		switch(cur_cb->asso_model)
		{
			case SMP_JW:
				/* Just works. In case of legacy pairing we take tk as 0 and proceed with
				 * pairing.
				 */
				memset(cur_cb->tk, 0, 16);
				if(cur_cb->pairing_method == SMP_LEGACY_PAIRING)
				{
					if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
					{
						/* We are slave. We need to wait for the confirm command from master*/
						cur_cb->state = SMP_STATE_WAIT_CNF_CMD;
					}
					else
					{
						/* We are master. we need to
						 * 1. Generate a 128 bit random number.
						 * 2. Generate the confirm value.
						 * 3. Send it the slave.
						 */
						cur_cb->state = SMP_STATE_WAIT_CNF_GEN;
						smp_gen_rand();
					}
				}
#if ( SECURE_CONNECTION)
				else
				{
					/*Secure connections*/
					if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
					{
						/* We are slave. We need to
						 * * 1. Generate a 128 bit random number (nonce).
						 * 2. Generate the confirm value.
						 * 3. Send it the slave.
						 */
						cur_cb->state = SMP_STATE_WAIT_CNF_GEN;
						smp_gen_rand();
					}
					else
					{
						/* We are master. We need to wait for confirmation from slave*/
						cur_cb->state = SMP_STATE_WAIT_CNF_CMD;
					}
				}
#endif /* SECURE_CONNECTION */
				break;
			case SMP_IIRD :
				logd("Initiator Inputs Responder displays");
				if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
				{
					logd("We are responder. Need to generate a key");
					cur_cb->state = SMP_STATE_WAIT_TK;
					cur_cb->enc_stage = SMP_ENC_TK_RAND;
					hci_ble_rand();
				}
				else
				{
					cur_cb->state = SMP_STATE_WAIT_PASSKEY;
					smp_start_app_timer();
					smp_mgr_cback(g_local_adapter.connected_device[cur_cb->conn_id]->id_addr.bdaddr, SMP_PASSKEY_REQ_EVT, NULL, 0);
				}
				break;
			case SMP_IDRI :
				logd("Initiator Displays Responder Inputs");
				if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
				{
					logd("We are responder. We need to input the key");
					cur_cb->state = SMP_STATE_WAIT_PASSKEY;
					smp_start_app_timer();
					smp_mgr_cback(g_local_adapter.connected_device[cur_cb->conn_id]->id_addr.bdaddr, SMP_PASSKEY_REQ_EVT, NULL, 0);
				}
				else
				{
					logd("We are initiator . We need to generate a key");
					cur_cb->state = SMP_STATE_WAIT_TK;
					cur_cb->enc_stage = SMP_ENC_TK_RAND;
					hci_ble_rand();
				}
				break;
			case SMP_IIRI :
				logd("Initiator Inputs Responder Inputs");
				cur_cb->state = SMP_STATE_WAIT_PASSKEY;
				smp_start_app_timer();
				smp_mgr_cback(g_local_adapter.connected_device[cur_cb->conn_id]->id_addr.bdaddr, SMP_PASSKEY_REQ_EVT, NULL, 0);
				break;
#if (SECURE_CONNECTION)
			case SMP_JW_NC :
			case SMP_IIRD_NC :
			case SMP_IDRI_NC :
				/* Secure connections */
				if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
				{
					/* need to generate a confirm */
					cur_cb->state = SMP_STATE_WAIT_CNF_GEN;
					smp_gen_rand();
				}
				else
				{
					cur_cb->state = SMP_STATE_WAIT_CNF_CMD;
				}
				break;
#endif /* SECURE_CONNECTION */
			default :
				logd("Invalid association model %x", cur_cb->asso_model);
				break;
		}
}
static void smp_gen_rand()
{
	logi("");
	g_local_adapter.smp_data.smp_cur_cb.enc_stage = SMP_ENC_RAND_S1;
	hci_ble_rand();
}

static void smp_compare_confirm(UINT8* data)
{
	UINT8 cfm[16];
	UINT8* pp = cfm;
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	REVERSE_ARRAY_TO_STREAM(pp, data, SMP_CONFIRM_LEN );
	if(memcmp(cfm, cur_cb->peer_confirm, SMP_CONFIRM_LEN) == 0)
	{
		logd("Confirm matches");
		if(cur_cb->pairing_method == SMP_LEGACY_PAIRING)
		{
			if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
			{
				smp_send_rand_cmd();
			}
			else
			{
				smp_cal_stk();
			}
		}
#if ( SECURE_CONNECTION )
		else
		{
			switch(cur_cb->asso_model)
			{
				case SMP_JW:
					/* phase two done. calculate the LTK now*/
					if(!g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
					{
						/* We are the master*/
						/* Need to calculate the LTK now */
						cur_cb->state = SMP_STATE_WAIT_LTK_GEN;
						smp_gen_ltk();
					}
					break;
				case SMP_JW_NC:
				case SMP_IIRD_NC:
				case SMP_IDRI_NC:
					/* generate and dispaly the Numeric value*/
					cur_cb->state = SMP_STATE_WAIT_NUMERIC_VALUE;
					smp_cal_numeric_value();
					break;
				case SMP_IIRD:
				case SMP_IDRI:
				case SMP_IIRI:
					/*Check the iteration number and continue*/
					cur_cb->key_bit_sent++;
					if(cur_cb->key_bit_sent < 20)
					{
						if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
						{
							cur_cb->state = SMP_STATE_WAIT_CNF_CMD;
							smp_send_rand_cmd();
						}
						else
						{
							cur_cb->state = SMP_STATE_WAIT_CNF_GEN;
							smp_gen_rand();
						}
					}
					else
					{
						if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
						{
							cur_cb->state = SMP_STATE_WAIT_DHKEY_CHECK_CMD;
							smp_send_rand_cmd();
						}
						else
						{
							/* calculate ltk*/
							cur_cb->state = SMP_STATE_WAIT_LTK_GEN;
							smp_gen_ltk();
						}
					}
					break;
			}
		}
#endif /* SECURE_CONNECTION */
	}
	else
	{
		logd("Confirm failed");
		g_local_adapter.smp_data.smp_cur_cb.status = SMP_CONFIRM_FAILED;
		smp_pair_failed_evt();
	}
}
/* This function is used to calculate the STK (only used in legacy pairing)*/
static void smp_cal_stk()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 r[16];
	logi("");
	g_local_adapter.smp_data.smp_cur_cb.enc_stage = SMP_ENC_STK_S1;
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		memcpy(r, (cur_cb->local_rand + 8), 8);
		memcpy(r + 8, (cur_cb->peer_rand + 8), 8);
	}
	else
	{
		memcpy(r, (cur_cb->peer_rand+8), 8);
		memcpy(r + 8, (cur_cb->local_rand + 8), 8);
	}
	smp_aes_encrypt(cur_cb->tk, r);
}

static void smp_start_enc()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 rand[8];
	logi("");
	memset(rand, 0, SMP_LTK_RAND_LEN);
	smp_start_cmd_timer();
	hci_ble_start_encryption(g_local_adapter.connected_device[cur_cb->conn_id]->acl_handle, rand, 0, cur_cb->stk);
}

/* This function is called to start/continue the key distribution*/
static void smp_start_key_dist()
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	int i = 0;
	logi("");
	/* We will check whether any key is pending to be distributed*/
	while(i < 3)
	{
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			if(cur_cb->local_resp_key & 1 << i)
			{
				cur_cb->local_resp_key &= ~(1<<i);
				break;
			}
		}
		else
		{
			if(cur_cb->local_init_key & 1 << i)
			{
				cur_cb->local_init_key &= ~(1<<i);
				break;
			}
		}
		i++;
	}
	if(i == 0)
	{
		/* Indicates LTK is pending( only happens in case of legacy pairing).
		 * We will now generate LTK and send it across.
		 */
		smp_gen_ltk();
	}
	if(i == 1)
	{
		/* Indicates IRK is pending*/
#if (PRIVACY_FEATURE)
		logd("Send IRK");
		smp_send_id_info_cmd();
#endif /* PRIVACY_FEATURE */
	}
	if(i == 2)
	{
		/*Indicates CSRK is pending*/
#if (SIGNED_WRITE)
		logd("Send Data signing key");
		smp_gen_csrk();
#endif /* SIGNED_WRITE */
	}
	if(i == 3)
	{
		logd("Key distribution done");
		smp_key_dist_done_evt();
	}
}

/* This function is used to generate the LTK*/
static void smp_gen_ltk()
{
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->pairing_method == SMP_LEGACY_PAIRING)
	{
		/* Incase of legacy pairing LTK is generated as
		 * 1. A Random number (rand) of 64 bit is generated.
		 * 2. Y = dm(DHK, rand) is calculated.
		 * 3. random number DIV is generated
		 * 4. EDIV is calculated as Y xor DIV
		 * 5. LTK = d1(ER, DIV, 0)
		 * 6. LTK, EDIV and rand are distributed to the peer device
		 */
		cur_cb->enc_stage = SMP_ENC_LTK_RAND_GEN;
		hci_ble_rand();
	}
#if ( SECURE_CONNECTION )
	else
	{
		/* Secure connections
		 * LTK and mackey are calculated using smp_f5().
		 */
		UINT8 local_bdaddr[BD_ADDR_LEN + 1];
		UINT8 peer_bdaddr[BD_ADDR_LEN + 1];
		local_bdaddr[0] = g_local_adapter.connected_device[cur_cb->conn_id]->local_addr_type;
		peer_bdaddr[0] = g_local_adapter.connected_device[cur_cb->conn_id]->bdaddr_type;
		memcpy(local_bdaddr + 1, g_local_adapter.connected_device[cur_cb->conn_id]->local_bdaddr, BD_ADDR_LEN );
		memcpy(peer_bdaddr + 1, g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr, BD_ADDR_LEN);
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			smp_f5(cur_cb->dhkey, cur_cb->peer_rand, cur_cb->local_rand,
					peer_bdaddr, local_bdaddr);
		}
		else
		{
			smp_f5(cur_cb->dhkey, cur_cb->local_rand, cur_cb->peer_rand,
					local_bdaddr, peer_bdaddr);
		}
	}
#endif /* SECURE_CONNECTION */
}

#if ( SIGNED_WRITE )
static void smp_gen_csrk()
{
	g_local_adapter.smp_data.smp_cur_cb.enc_stage = SMP_ENC_CSRK_GEN_S1;
	hci_ble_rand();

}
#endif /* SIGNED_WRITE */
/* This function is called to check whether key distribution has been completed by peer or not*/
static void smp_check_key_dist()
{
	logi("");
	if(g_local_adapter.connected_device[g_local_adapter.smp_data.smp_cur_cb.conn_id]->local_link_role)
	{
		if(g_local_adapter.smp_data.smp_cur_cb.local_init_key == 0)
		{
			smp_key_dist_done_evt();
		}
		else
		{
			smp_start_cmd_timer();
		}
	}
	else
	{
		if(g_local_adapter.smp_data.smp_cur_cb.local_resp_key == 0)
		{
			smp_key_dist_done_evt();
		}
		else
		{
			smp_start_cmd_timer();
		}
	}
}

static void smp_hci_enc_key_reply(UINT16 conn_handle, UINT8* ltk)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if(ltk != NULL)
#endif
	{
		hci_ble_ltk_req_reply(conn_handle, ltk);
	}
}

#if (PRIVACY_FEATURE)

static void smp_gen_rpa()
{
	g_local_adapter.smp_data.smp_cur_cb.enc_stage = SMP_ENC_RPA_GEN_S1;
	hci_ble_rand();
}

static void smp_res_rpa(BOOLEAN local)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 pp[16];
	memset(pp, 0, 16);
	logd("");
#if (HOST_PRIVACY)
	if (!local)
	{
		for(;cur_cb->idx < HOST_RESOLVING_LIST_SIZE; cur_cb->idx++)
		{
			if(g_local_adapter.resolving_list[cur_cb->idx].valid)
			{
				break;
			}
		}
		if(cur_cb->idx >= HOST_RESOLVING_LIST_SIZE)
		{
			UINT8 idx;
			UINT8 rpa[BD_ADDR_LEN];
			cur_cb->idx = 0;
			cur_cb->state = SMP_STATE_IDLE;
			logd("Resolution failed");
			memcpy(rpa, cur_cb->rpa, BD_ADDR_LEN);
			idx = cur_cb->idx;
			memset(cur_cb, 0, sizeof(smp_cb_t));
			smp_mgr_rpa_res_cb(rpa, idx, SMP_FAILED);
			return;
		}
		memcpy(pp + 13, cur_cb->rpa, 3);
		cur_cb->enc_stage = SMP_ENC_RPA_RES;
		smp_aes_encrypt(g_local_adapter.resolving_list[cur_cb->idx].entry.peer_id_info.irk, pp);
	}
	else
#endif /* HOST_PRIVACY */
	{
		memcpy(pp + 13, cur_cb->rpa, 3);
		cur_cb->enc_stage = SMP_ENC_LOCAL_RPA_RES;
		smp_aes_encrypt(g_local_adapter.smp_data.device_irk, pp);
	}
}
#endif /* PRIVACY_FEATURE */



#if (AES_CMAC)

static void smp_cal_sub_keys()
{
	UINT8 c[16] = {0};
	g_local_adapter.smp_data.smp_cur_cb.enc_stage = SMP_ENC_SUB_KEY;
	hci_ble_encrypt(g_local_adapter.smp_data.smp_cur_cb.cmac_key, c);
}

static void smp_shift_left(UINT8* data, UINT8 data_len, UINT8* output)
{
	INT8 i, pre_overflow = 0, cur_overflow = 0;
	for( i = data_len - 1; i >= 0; i--)
	{
		cur_overflow = data[i] & 0x80 ? 1 : 0;
		output[i] = (data[i] << 1)| pre_overflow;
		pre_overflow = cur_overflow;
	}
}
#endif /* AES_CMAC */

#if (SECURE_CONNECTION)
static void smp_cal_numeric_value()
{
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		smp_g2(cur_cb->peer_p256_key_x, g_local_adapter.smp_data.local_p256_key_x, cur_cb->peer_rand, cur_cb->local_rand);
	else
		smp_g2(g_local_adapter.smp_data.local_p256_key_x, cur_cb->peer_p256_key_x, cur_cb->local_rand, cur_cb->peer_rand);
}
#if(HOST_ECDH)
static void smp_cal_dhkey_internal()
{
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	cal_dhkey(g_local_adapter.smp_data.local_p256_private_key, cur_cb->peer_p256_key_x,
				cur_cb->peer_p256_key_y, cur_cb->dhkey);
	hex_dump("DHKEY :", cur_cb->dhkey, 32);
	if(!g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		if(cur_cb->asso_model == SMP_JW || cur_cb->asso_model == SMP_JW_NC || cur_cb->asso_model == SMP_IIRD_NC ||
		   cur_cb->asso_model == SMP_IDRI_NC)
			cur_cb->state = SMP_STATE_WAIT_CNF_CMD;
		else
			smp_start_pairing_phase2();
	}
	else
	{
		smp_send_pub_key_cmd();
		smp_start_pairing_phase2();
	}
}
#endif /* HOST_ECDH */
static void smp_cal_dhkey()
{
	logi("");
#if(CONTROLLER_ECDH)
	hci_ble_generate_dhkey(g_local_adapter.smp_data.smp_cur_cb.peer_p256_key_x,
			g_local_adapter.smp_data.smp_cur_cb.peer_p256_key_y, SMP_PUB_KEY_COORDINATE_LEN);
#else
	smp_cal_dhkey_internal();
#endif /* CONTROLLER_ECDH */
}

/* This function is used to compare the dhkey check re-computed locally and the dhkey check
 * sent by the peer.
 */
static void smp_dhkey_compare(UINT8 *data)
{
	logi("");
	UINT8 cfm[16];
	UINT8* pp = cfm;
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	REVERSE_ARRAY_TO_STREAM(pp, data, SMP_CONFIRM_LEN );
	if(memcmp(cfm, cur_cb->peer_confirm, SMP_CONFIRM_LEN) == 0)
	{
		logd("dhkey matches");
		if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
		{
			/*We are the slave. Now we need to generate our local dhkey check and
			 * send to the master.
			 */
			cur_cb->state = SMP_STATE_WAIT_DHKEY_CHECK_GEN;
			UINT8 iocap[3];
			iocap[0] = cur_cb->local_auth_req;
			iocap[1] = cur_cb->local_oob_flag;
			iocap[2] = cur_cb->local_io_cap;
			UINT8 local_bdaddr[BD_ADDR_LEN + 1];
			UINT8 peer_bdaddr[BD_ADDR_LEN + 1];
			local_bdaddr[0] = g_local_adapter.connected_device[cur_cb->conn_id]->local_addr_type;
			peer_bdaddr[0] = g_local_adapter.connected_device[cur_cb->conn_id]->bdaddr_type;
			memcpy(local_bdaddr + 1, g_local_adapter.connected_device[cur_cb->conn_id]->local_bdaddr, BD_ADDR_LEN );
			memcpy(peer_bdaddr + 1, g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr, BD_ADDR_LEN);
			hex_dump("Local Bdaddr :", g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr, BD_ADDR_LEN);
			smp_f6(cur_cb->mackey, cur_cb->local_rand, cur_cb->peer_rand, cur_cb->tk, iocap,
					local_bdaddr, peer_bdaddr);
		}
		else
		{
			/* We are the master. We will start the encryption now*/
			UINT8 rand[8];
			memset(rand, 0, 8);
			cur_cb->state = SMP_STATE_WAIT_ENC_CHG;
			hci_ble_start_encryption(g_local_adapter.connected_device[cur_cb->conn_id]->acl_handle, rand, 0, cur_cb->cur_key.peer_ltk);
		}
	}
	else
	{
		logw("Dhkey compare failed");
		cur_cb->status = SMP_DHKEY_CHECK_FAILED;
		smp_pair_failed_evt();
	}
}
#endif /* SECURE_CONNECTION */

static void smp_clean_up()
{
	UINT8 conn_id = g_local_adapter.smp_data.smp_cur_cb.conn_id;
	UINT8 status = g_local_adapter.smp_data.smp_cur_cb.status;
	UINT8 operation = g_local_adapter.smp_data.smp_cur_cb.operation;
	UINT8 remote_initiated = g_local_adapter.smp_data.smp_cur_cb.remote_initiated;
	logi("");
	memset(&g_local_adapter.smp_data.smp_cur_cb, 0, sizeof(smp_cb_t));
	if(operation == SMP_BONDING_OPERATION && !remote_initiated)
		smp_mgr_bond_status(conn_id, status);
}



/************************************HCI callback functions*****************************/

/* This function is called by hci layer when the controller
 * is done with a random number generation.
 */
void smp_proc_hci_rand(UINT8 *buffer, UINT8 event_length)
{
	logi("");
	smp_handle_enc_operations(buffer);
}

/* This function is called by hci layer when the controller
 * is done with aes-128 encryption.
 */
void smp_proc_hci_le_encrypt(UINT8* buffer,UINT8 event_length)
{
	logi("");
#if (PARANOID_STACK == TRUE)
	if(event_length != 16)
	{
		logd("Error in length");
		return;
	}
#endif
	smp_handle_enc_operations(buffer);
}

/* This function is called by hci layer when it receives a link encryption change
 * Incase of legacy pairing this event might have happened because of an encryption with
 * 1. STK
 * 2. LTK
 *
 */
void smp_enc_chg_cback(UINT8* buffer, UINT16 len)
{
	UINT8* pp = buffer;
	UINT8 data[5];
	UINT8 status;
	UINT16 conn_handle;
	UINT8 ll_enc;
	UINT8 idx;
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	connected_device_t *device;

	logi("");
	smp_stop_cmd_timer();
	len = MIN(len, sizeof(data));
	memcpy(data, buffer, len);
	STREAM_TO_UINT8(status, pp);
	STREAM_TO_UINT16(conn_handle, pp);
	if(len >= 4)
	{
		STREAM_TO_UINT8(ll_enc, pp);
		logd("ll_enc:%d", ll_enc);
	}
	else
	{
		ll_enc = 1;
		memcpy(data + len, &ll_enc, 1);
	}
	logd("Status:%d", status);
	logd("Connection handle:%d", conn_handle);
	idx = get_connected_device_idx_by_handle(conn_handle);

	if (idx >= MAX_NUM_CONNECTED_DEVICE)
		return;

	device = g_local_adapter.connected_device[idx];

	if(memcmp(cur_cb->bdaddr, g_local_adapter.connected_device[idx]->bdaddr, BD_ADDR_LEN) == 0)
	{
		if(status == SMP_SUCCESS && ll_enc == 1)
		{
			cur_cb->cur_key.key_size = cur_cb->local_enc_key_size;
			device->link_enc_state.secuirty_level = cur_cb->cur_key.security_level;
			device->link_enc_state.state = LINK_ENC_STATE_ENCRYPTED;
			device->link_enc_state.key_size = cur_cb->local_enc_key_size;
			device->link_enc_state.key_type = cur_cb->cur_key.key_type;
			update_enc_changed(device, status);
			smp_enc_chg_evt();
		}
		else
		{
			update_enc_changed(device, status);
			if(cur_cb->enc_with_ltk)
			{
				/* Re-encryption with the current key failed. Clear the keys */
				smpm_clear_key(device);
			}
			cur_cb->status = SMP_UNSPECIFIED_REASON;
			smp_pair_failed_evt();
		}
	}
	else
	{
		/* Re-encrytpion triggered by remote*/
		if(status == SMP_SUCCESS && ll_enc == 1)
		{
			device->link_enc_state.state = LINK_ENC_STATE_ENCRYPTED;
		}
		else
		{
			smpm_clear_key(device);
		}
		update_enc_changed(device, status);
	}
}
static void update_enc_changed(connected_device_t *device, UINT8 status)
{
	UINT8 idx;
	for(idx = 0; idx < MAX_NUMBER_OF_APP; idx++)
	{
		if(g_local_adapter.app_list[idx] && g_local_adapter.app_list[idx]->app_device_control_cb->iLE_on_link_enc_changed_cb)
		{
			g_local_adapter.app_list[idx]->app_device_control_cb->iLE_on_link_enc_changed_cb(INVALID_TRANS_ID, device->idx, status, device->link_enc_state.secuirty_level);
		}
	}
}
static INT8 fetch_key(connected_device_t *device, UINT8 key_type)
{
	if(!device)
		return STATUS_ERR_INVALID_PARAM;
	logd("Fetching key type %d", key_type);
	if(g_local_adapter.smp_mgr_data.storage_mgr.storage_cb && g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_request_cb)
	{
		g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_request_cb(g_local_adapter.smp_mgr_data.storage_mgr.trans_id, device->id_addr.bdaddr, device->id_addr.type, key_type);
		return STATUS_SUCCESS;
	}
	else
		return STATUS_ERR_OPERATION_NOT_SUPPORTED;
}
/* This function is called when a key request comes from the controller*/
void smp_proc_ltk_req(UINT8* buffer,UINT8 len)
{
	UINT16 conn_handle;
	UINT8 idx;
	UINT8* pp = buffer;
	UINT8 stk_required = 0;
	UINT8 rand[8];
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT16 ediv = 0;
	connected_device_t *device;

	logi("");
	memset(rand, 0, SMP_LTK_RAND_LEN);
	STREAM_TO_UINT16(conn_handle, pp);
	if(memcmp(rand, pp, SMP_LTK_RAND_LEN) == 0)
	{
		/* Rand is all zeros. In legacy pairing this means we need to use STK.*/
		stk_required = 1;
	}
	REVERSE_STREAM_TO_ARRAY(rand, pp, SMP_LTK_RAND_LEN);
	STREAM_TO_UINT16(ediv, pp);
	idx = get_connected_device_idx_by_handle(conn_handle);

	if( idx == MAX_NUM_CONNECTED_DEVICE)
	{
		logd("Unknown connection handle");
		return;
	}

	device = g_local_adapter.connected_device[idx];
	logd("g_local_adapter.connected_device[%d]:%p", idx, g_local_adapter.connected_device[idx]);
	hex_dump("BDADDR:", g_local_adapter.connected_device[idx]->bdaddr,BD_ADDR_LEN);

	if(memcmp(device->bdaddr, g_local_adapter.smp_data.smp_cur_cb.bdaddr, BD_ADDR_LEN) == 0)
	{
		/* The request is from the same device.
		 * This means we had initiated this change (either while pairing or re-encrypting)
		 */
		smp_stop_cmd_timer();
		if(cur_cb->pairing_method == SMP_LEGACY_PAIRING)
		{
			/* Legacy mode*/
			if(stk_required == 1)
			{
				/* We need to generate the STK now and then encrypt the link*/
				cur_cb->state = SMP_STATE_WAIT_STK_GEN;
				smp_cal_stk();
				return;
			}
			else
			{
				/* This is for re-encryption*/
				if(device->link_enc_state.keys_distributed & SMP_LTK_DISTRIBUTED)
				{
					device->link_enc_state.pending_act |= LINK_ENC_PENDING;
					cur_cb->state = SMP_STATE_WAIT_ENC_CHG;
					fetch_key(device, LOCAL_LTK);
				}
				else
				{
					logd("No LTK found for the device");
					hci_ble_ltk_neg_reply(conn_handle);
					return;
				}
			}
		}
#if ( SECURE_CONNECTION )
		else
		{
			/* Secure connection mode*/
			if(cur_cb->enc_with_ltk == TRUE)
			{
				device->link_enc_state.pending_act |= LINK_ENC_PENDING;
				cur_cb->state = SMP_STATE_WAIT_ENC_CHG;
				fetch_key(device, LOCAL_LTK);
			}
			else
			{
				cur_cb->state = SMP_STATE_WAIT_ENC_CHG;
				hci_ble_ltk_req_reply(conn_handle, cur_cb->cur_key.local_ltk);
			}

		}
#endif /* SECURE_CONNECTION */
	}
	else
	{
		/* This request was not initiated by us*/
		if(device->link_enc_state.state < LINK_ENC_STATE_UPDATED)
		{
			device->link_enc_state.pending_act |= LINK_ENC_PENDING;
		}
		else
		{
			smp_check_key_and_encrypt(device);
		}
	}
}
void smp_check_key_and_encrypt(connected_device_t *device)
{
	if(!device)
		return;
	if(!(device->link_enc_state.key_type == SMP_KEY_TYPE_SC_AUTHENTICATED) && !(device->link_enc_state.key_type == SMP_KEY_TYPE_SC_UNAUTHENTICATED))
	{
		/* Legacy mode */
		if(!(device->link_enc_state.keys_distributed & SMP_LTK_DISTRIBUTED))
		{
			hci_ble_ltk_neg_reply(device->acl_handle);
			return;
		}
	}
	device->link_enc_state.pending_act |= LINK_ENC_PENDING;
	fetch_key(device, LOCAL_LTK);
}

#if (SECURE_CONNECTION)
void smp_proc_p256_public_key(UINT8* buffer, UINT8 len)
{
	logi("");
	smp_handle_enc_operations( buffer + 1);
}

void smp_proc_dhkey(UINT8* buffer, UINT8 len)
{
	UINT8 status = buffer[0];

	logi("");

	if ( status != STATUS_SUCCESS)
	{
		g_local_adapter.smp_data.smp_cur_cb.status = SMP_DHKEY_CHECK_FAILED;
		smp_pair_failed_evt();
		return;
	}
	smp_dhkey_gen_evt(buffer + 1);
}
#endif /* SECURE_CONNECTION */
/*****************************************ENC Handling Functions************************************/

static void smp_init_enc()
{
	logi("");
#if (SECURE_CONNECTION == TRUE)
	/* Need to generate public key */
	g_local_adapter.smp_data.smp_cur_cb.state = SMP_STATE_WAIT_INIT;
	g_local_adapter.smp_data.smp_cur_cb.enc_stage = SMP_ENC_PUB_KEY;
	smp_generate_p256_keys();
#if(ECC_TESTING == TRUE)
		smp_ecc_test();
#endif
#endif
}
static void smp_handle_enc_operations(UINT8* data)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 *pp = (UINT8*)data;
	UINT8 p1[16];
#if (PRIVACY_FEATURE == TRUE)
	UINT8 rpa[BD_ADDR_LEN];
#endif /* PRIVACY_FEATURE == TRUE */

	logi("");
	memset(p1, 0, 16);

	/* Generating cfm is a three step process
	 * Step 1 : generate a 8byte rand number with the help of controller
	 * Step 2 : Generate a 8byte random number with the help of controller and combine the
	 * 			random number generated in step 1 to form mrand ( 128 bit random number)
	 * Step 3 : Generate confirm  using Mconfirm = c1(tk, mrand, pairing_req_cmd,initiating_device_address_type,
	 * 												  initiating device address, pairing_req_rsp,
	 * 												  responding_device_address_type,responding_device_address)
	 */
	switch(cur_cb->enc_stage)
	{
#if (PRIVACY_FEATURE == TRUE)
		case SMP_ENC_IRK_GEN_S1:
		{
			cur_cb->enc_stage = SMP_ENC_IRK_GEN_S2;
			memcpy(g_local_adapter.smp_data.device_irk, data, 8);
			hci_ble_rand();
		}
			break;
		case SMP_ENC_IRK_GEN_S2:
		{
			UINT8 dummy_bdaddr[BD_ADDR_LEN];
			cur_cb->enc_stage = SMP_ENC_IRK_GEN_S2;
			memcpy(g_local_adapter.smp_data.device_irk + 8, data, 8);
			memset(dummy_bdaddr, 0, BD_ADDR_LEN);
			if(g_local_adapter.smp_mgr_data.storage_mgr.storage_cb)
			{
				if(g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_update_cb)
				{
					g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_update_cb(g_local_adapter.smp_mgr_data.storage_mgr.trans_id,
																						dummy_bdaddr, 0, LOCAL_IRK,
																						16, g_local_adapter.smp_data.device_irk);
				}
				if(g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_request_cb)
				{
					g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_request_cb(g_local_adapter.smp_mgr_data.storage_mgr.trans_id,
																						dummy_bdaddr, 0, PEER_IRK);
				}
			}
			else
			{
				smp_mgr_ext_init_cb();
			}
		}
			break;
#endif /* PRIVACY_FEATURE == TRUE */
		case SMP_ENC_TK_RAND :
			{
				UINT32 temp_tk;
				cur_cb->enc_stage = SMP_ENC_IDLE;
				STREAM_TO_UINT32(temp_tk, data);
				temp_tk = temp_tk % 1000000;
				logd("Tk:%u", temp_tk);
				smp_mgr_cback(g_local_adapter.connected_device[cur_cb->conn_id]->id_addr.bdaddr, SMP_KEY_READY_EVT, (UINT8*)(void*)&temp_tk, sizeof(temp_tk));
				smp_tk_gen_evt((UINT8*)(void*)&temp_tk);
			}
			break;
		case SMP_ENC_RAND_S1 :
			cur_cb->enc_stage = SMP_ENC_RAND_S2;
			memcpy(cur_cb->local_rand, pp, 8);
			hci_ble_rand();
			break;
		case SMP_ENC_RAND_S2 :
			cur_cb->enc_stage = SMP_ENC_IDLE;
			memcpy(cur_cb->local_rand+8, pp, 8);
			memcpy(cur_cb->cur_rand, cur_cb->local_rand, SMP_RAND_LEN);
			smp_rand_gen_evt();
			break;
			/*fall through */
		case SMP_ENC_CONFIRM_S1 :

			if(cur_cb->pairing_method == SMP_LEGACY_PAIRING)
			{
				cur_cb->enc_stage =SMP_ENC_CONFIRM_S2;
				if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
				{
					logi("local addr: %x  peer: %x",g_local_adapter.connected_device[cur_cb->conn_id]->local_addr_type, g_local_adapter.connected_device[cur_cb->conn_id]->bdaddr_type);
					logi("addrty: %d", g_local_adapter.connected_device[cur_cb->conn_id]->local_addr_type);
					smp_c1_1(cur_cb->tk, cur_cb->cur_rand, cur_cb->pairing_req, cur_cb->pairing_rsp, g_local_adapter.connected_device[cur_cb->conn_id]->bdaddr_type,
							g_local_adapter.connected_device[cur_cb->conn_id]->local_addr_type);
				}
				else
				{
					logi("local addr: %x  peer: %x",g_local_adapter.connected_device[cur_cb->conn_id]->local_addr_type, g_local_adapter.connected_device[cur_cb->conn_id]->bdaddr_type);
					smp_c1_1(cur_cb->tk, cur_cb->cur_rand, cur_cb->pairing_req, cur_cb->pairing_rsp, g_local_adapter.connected_device[cur_cb->conn_id]->local_addr_type,
							g_local_adapter.connected_device[cur_cb->conn_id]->bdaddr_type);
				}
			}
#if ( SECURE_CONNECTION )
			else
			{
				cur_cb->enc_stage = SMP_ENC_IDLE;
				if(cur_cb->state == SMP_STATE_WAIT_CNF_GEN)
				{
					/* Confirm value needs to be generated */
					if(cur_cb->asso_model == SMP_JW || cur_cb->asso_model > SMP_IIRI)
						smp_f4(g_local_adapter.smp_data.local_p256_key_x, cur_cb->peer_p256_key_x, cur_cb->cur_rand, 0);
					else
					{
						UINT32 key = 0;
						UINT8 *pp1 = (UINT8*) &key;
						UINT8 *p = cur_cb->tk + 12;
						REVERSE_STREAM_TO_ARRAY(pp1, p , 4);
						UINT8 z = (0x80 | ((key & (1 << cur_cb->key_bit_sent))?1:0));
						smp_f4(g_local_adapter.smp_data.local_p256_key_x, cur_cb->peer_p256_key_x, cur_cb->cur_rand, z);
					}
				}
				else
				{
					if(cur_cb->asso_model == SMP_JW || cur_cb->asso_model > SMP_IIRI)
						smp_f4(cur_cb->peer_p256_key_x, g_local_adapter.smp_data.local_p256_key_x, cur_cb->cur_rand, 0);
					else
					{
						UINT32 key = 0;
						UINT8 *pp1 = (UINT8*) &key;
						UINT8 *p = cur_cb->tk + 12;
						REVERSE_STREAM_TO_ARRAY(pp1, p , 4);
						UINT8 z = (0x80 | ((key & (1 << cur_cb->key_bit_sent))?1:0));
						smp_f4(cur_cb->peer_p256_key_x, g_local_adapter.smp_data.local_p256_key_x, cur_cb->cur_rand, z);
					}
				}
			}
#endif /* SECURE_CONNECTION */
			break;
		case SMP_ENC_CONFIRM_S2 :
			cur_cb->enc_stage = SMP_ENC_CONFIRM_S3;
			pp = p1;
			REVERSE_ARRAY_TO_STREAM(pp,data,16);
			hex_dump("C1:", p1, 16);
			if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
			{
				log("peer bdaddr: to [%02x:%02x:%02x:%02x:%02x:%02x]\n", g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[0], g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[1], g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[2],
						g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[3], g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[4], g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[5]);
				logi("addrty: %d", g_local_adapter.connected_device[cur_cb->conn_id]->local_addr_type);
				smp_c1_2(cur_cb->tk, p1,g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr, g_local_adapter.connected_device[cur_cb->conn_id]->local_bdaddr);
			}
			else
			{
				log("peer bdaadr: to [%02x:%02x:%02x:%02x:%02x:%02x]\n", g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[0], g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[1], g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[2],
									g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[3], g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[4], g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr[5]);
				smp_c1_2(cur_cb->tk, p1,g_local_adapter.connected_device[cur_cb->conn_id]->local_bdaddr, g_local_adapter.connected_device[cur_cb->conn_id]->ota_bdaddr);
			}
			break;
		case SMP_ENC_CONFIRM_S3 :
			cur_cb->enc_stage = SMP_ENC_IDLE;
			hex_dump("Confirm:", data, 16);
			smp_confirm_gen_evt(data);
			break;
		case SMP_ENC_STK_S1 :
			cur_cb->enc_stage = SMP_ENC_IDLE;
			pp = cur_cb->stk;
			REVERSE_ARRAY_TO_STREAM(pp, data, SMP_STK_LEN);
			hex_dump("STK:", cur_cb->stk, SMP_STK_LEN);
			smp_mask_key(cur_cb->stk, cur_cb->local_enc_key_size);
			smp_link_key_cal_evt();
			break;
		case SMP_ENC_LTK_RAND_GEN :
			cur_cb->enc_stage = SMP_ENC_LTK_EDIV_GEN;
			memcpy(cur_cb->cur_key.local_rand, data, 8);
			hci_ble_rand();
			break;
		case SMP_ENC_LTK_EDIV_GEN :
			cur_cb->enc_stage = SMP_ENC_LTK_GEN_S1;
			memcpy(&cur_cb->cur_key.local_ediv, data, 2);
			hci_ble_rand();
			break;
		case SMP_ENC_LTK_GEN_S1:
			cur_cb->enc_stage = SMP_ENC_LTK_GEN_S2;
			memcpy(cur_cb->cur_key.local_ltk, data, 8);
			hci_ble_rand();
			break;
		case SMP_ENC_LTK_GEN_S2:
			cur_cb->enc_stage = SMP_ENC_IDLE;
			memcpy(cur_cb->cur_key.local_ltk + 8, data, 8);
			smp_mask_key(cur_cb->cur_key.local_ltk, cur_cb->local_enc_key_size);
			smp_send_enc_info_cmd();
			break;
#if ( SIGNED_WRITE )
		case SMP_ENC_CSRK_GEN_S1:
			cur_cb->enc_stage = SMP_ENC_CSRK_GEN_S2;
			memcpy(cur_cb->cur_key.local_csrk, data, 8);
			hci_ble_rand();
			break;
		case SMP_ENC_CSRK_GEN_S2:
			cur_cb->enc_stage = SMP_ENC_IDLE;
			memcpy(cur_cb->cur_key.local_csrk + 8, data, 8);
			smp_send_sign_info_cmd();
			break;
#endif /* SIGNED_WRITE */
#if (SECURE_CONNECTION)
		case SMP_ENC_PUB_KEY :
			pp = g_local_adapter.smp_data.local_p256_key_x;
			REVERSE_STREAM_TO_ARRAY(pp, data, SMP_PUB_KEY_COORDINATE_LEN);
			hex_dump("PUB KEY X:", g_local_adapter.smp_data.local_p256_key_x, SMP_PUB_KEY_COORDINATE_LEN);
			pp = g_local_adapter.smp_data.local_p256_key_y;
			REVERSE_STREAM_TO_ARRAY(pp, data, SMP_PUB_KEY_COORDINATE_LEN);
			hex_dump("PUB KEY Y:", g_local_adapter.smp_data.local_p256_key_y, SMP_PUB_KEY_COORDINATE_LEN);
			cur_cb->state = SMP_STATE_IDLE;
			cur_cb->enc_stage = SMP_ENC_IDLE;
			g_local_adapter.smp_data.sc_support = TRUE;
			smp_mgr_init_cb();
			break;
#endif /* SECURE_CONNECTION */
#if (AES_CMAC)
		case SMP_ENC_SUB_KEY :
			logd("SMP_ENC_SUB_KEY");
			cur_cb->enc_stage = SMP_ENC_AES_CMAC;
			pp = p1;
			REVERSE_ARRAY_TO_STREAM(pp, data, 16);
			if((p1[0] & 0x80) == 0)
			{
				smp_shift_left(p1, SMP_MAX_KEY_LEN, cur_cb->k1);
			}
			else
			{
				smp_shift_left(p1, SMP_MAX_KEY_LEN, cur_cb->k1);
				smp_xor(cur_cb->k1, Rb, SMP_MAX_KEY_LEN);
			}
			pp = cur_cb->k1;
			if((pp[0] & 0x80) == 0)
			{
				smp_shift_left(pp, SMP_MAX_KEY_LEN, cur_cb->k2);
			}
			else
			{
				smp_shift_left(pp, SMP_MAX_KEY_LEN, cur_cb->k2);
				smp_xor(cur_cb->k2, Rb, SMP_MAX_KEY_LEN);
			}
			memset(p1, 0, SMP_MAX_KEY_LEN);
			cur_cb->cur_block = 0;
			if(cur_cb->no_of_blocks == 1)
			{
				if(cur_cb->complete_block == TRUE)
				{
					smp_xor(p1, cur_cb->k1,SMP_MAX_KEY_LEN );
				}
				else
				{
					smp_xor(p1, cur_cb->k2,SMP_MAX_KEY_LEN );
				}
			}
			hex_dump("DATA:", cur_cb->cmac_data, SMP_MAX_KEY_LEN);
			smp_xor(p1, cur_cb->cmac_data,SMP_MAX_KEY_LEN );
			cur_cb->cur_block++;
			hci_ble_encrypt(cur_cb->cmac_key, p1);
			break;
		case SMP_ENC_AES_CMAC:
			logd("SMP_ENC_DATA_SIGNING");
			pp = p1;
			REVERSE_ARRAY_TO_STREAM(pp, data, SMP_MAX_KEY_LEN);
			pp = cur_cb->cmac_data + cur_cb->cur_block*SMP_MAX_KEY_LEN;
			if(cur_cb->cur_block == cur_cb->no_of_blocks-1)
			{
				if(cur_cb->complete_block == TRUE)
				{
					smp_xor(p1, cur_cb->k1,SMP_MAX_KEY_LEN );
				}
				else
				{
					smp_xor(p1, cur_cb->k2, SMP_MAX_KEY_LEN );
				}
			}
			else if(cur_cb->cur_block == cur_cb->no_of_blocks)
			{
				//data signing done
				logd("Data signing done");
				hex_dump("MAC:", p1, SMP_MAX_KEY_LEN);
				cur_cb->enc_stage = SMP_ENC_IDLE;
				memcpy(cur_cb->cmac_data, p1, SMP_MAX_KEY_LEN);
				//smp_sign_gen_evt();
				smp_aes_cmac_gen_evt();
				break;
			}
			smp_xor(p1, pp, SMP_MAX_KEY_LEN);
			cur_cb->cur_block++;
			hci_ble_encrypt(cur_cb->cmac_key, p1);
			break;
#endif /* AES_CMAC */
#if (PRIVACY_FEATURE)
		case SMP_ENC_RPA_GEN_S1 :
			cur_cb->enc_stage = SMP_ENC_RPA_GEN_S2;
			pp = (UINT8*)p1;
			pp = pp + 13;
			REVERSE_STREAM_TO_ARRAY(pp, data, 3);
			pp = (UINT8*)p1;
			pp[13] = ((pp[13] & 0x7F) | 0x40);
			memcpy(cur_cb->rpa, pp + 13, 3);
			smp_aes_encrypt(g_local_adapter.smp_data.device_irk, pp);
			break;
		case SMP_ENC_RPA_GEN_S2 :
			cur_cb->enc_stage = SMP_ENC_IDLE;
			pp = (UINT8*)p1;
			REVERSE_STREAM_TO_ARRAY(pp, data, 16);
			hex_dump("ENCTXT:",pp,16);
			pp = (UINT8*)p1;
			memcpy(cur_cb->rpa + 3, pp + 13, 3);
			hex_dump("RPA:", cur_cb->rpa, 6);
#if (GAP_RANDOM_ADDDRESS_SUPPORT == TRUE)
			hci_ble_set_random_addr(cur_cb->rpa);
#endif
			log("BDADRR Changed to [%02x:%02x:%02x:%02x:%02x:%02x]\n", cur_cb->rpa[0], cur_cb->rpa[1], cur_cb->rpa[2],
					cur_cb->rpa[3], cur_cb->rpa[4], cur_cb->rpa[5]);
			memcpy(g_local_adapter.bdaddr, cur_cb->rpa, BD_ADDR_LEN);
			cur_cb->state = SMP_STATE_IDLE;
			smp_mgr_rpa_gen_cb();
			break;
		case SMP_ENC_RPA_RES :
			cur_cb->enc_stage = SMP_ENC_IDLE;
			pp = (UINT8*)p1;
			REVERSE_STREAM_TO_ARRAY(pp, data, 16);
			pp = (UINT8*)p1;
			if(memcmp(pp + 13, cur_cb->rpa + 3, 3) == 0)
			{
				UINT8 idx;
				logd("Resolution success");
				cur_cb->state = SMP_STATE_IDLE;
				idx = cur_cb->idx;
				memcpy(rpa, cur_cb->rpa, BD_ADDR_LEN);
				memset(cur_cb, 0, sizeof(smp_cb_t));
				smp_mgr_rpa_res_cb(rpa, idx, STATUS_SUCCESS);
			}
			else
			{
				cur_cb->idx++;
				smp_res_rpa(FALSE);
			}
			break;
		case SMP_ENC_LOCAL_RPA_RES :
			cur_cb->enc_stage = SMP_ENC_IDLE;
			pp = (UINT8*)p1;
			REVERSE_STREAM_TO_ARRAY(pp, data, 16);
			pp = (UINT8*)p1;
			cur_cb->state = SMP_STATE_IDLE;
			memcpy(rpa, cur_cb->rpa, BD_ADDR_LEN);
			if(memcmp(pp + 13, cur_cb->rpa + 3, 3) == 0)
			{
				UINT8 idx;
				logd("Resolution success");
				idx = cur_cb->idx;
				memset(cur_cb, 0, sizeof(smp_cb_t));
				smp_mgr_rpa_res_cb(rpa, idx, STATUS_SUCCESS);
			}
			else
			{
				UINT8 idx;
				logd("Resolution failed");
				idx = 0;
				memset(cur_cb, 0, sizeof(smp_cb_t));
				smp_mgr_rpa_res_cb(rpa, idx, SMP_FAILED);
			}
			break;
#endif /* PRIVACY_FEATURE */
#if (SECURE_CONNECTION)
#if (HOST_ECDH)
		case SMP_ENC_RAND_P256_1:
			cur_cb->enc_stage = SMP_ENC_RAND_P256_2;
			pp = (UINT8*)g_local_adapter.smp_data.local_p256_private_key;
			REVERSE_STREAM_TO_ARRAY(pp, data, 8);
			hci_ble_rand();
			break;
		case SMP_ENC_RAND_P256_2:
			cur_cb->enc_stage = SMP_ENC_RAND_P256_3;
			pp = (UINT8*)g_local_adapter.smp_data.local_p256_private_key + 8;
			REVERSE_STREAM_TO_ARRAY(pp, data, 8);
			hci_ble_rand();
			break;
		case SMP_ENC_RAND_P256_3:
			cur_cb->enc_stage = SMP_ENC_RAND_P256_4;
			pp = (UINT8*)g_local_adapter.smp_data.local_p256_private_key + 16;
			REVERSE_STREAM_TO_ARRAY(pp, data, 8);
			hci_ble_rand();
			break;
		case SMP_ENC_RAND_P256_4:
			cur_cb->enc_stage = SMP_ENC_IDLE;
			pp = (UINT8*)g_local_adapter.smp_data.local_p256_private_key + 24;
			REVERSE_STREAM_TO_ARRAY(pp, data, 8);
			if(gen_public_private_key_pair(g_local_adapter.smp_data.local_p256_private_key, g_local_adapter.smp_data.local_p256_private_key,
					g_local_adapter.smp_data.local_p256_key_x, g_local_adapter.smp_data.local_p256_key_y) == STATUS_SUCCESS)
			{
				logd("Public key generated");
				hex_dump("Public key [x]:", g_local_adapter.smp_data.local_p256_key_x, SMP_PUB_KEY_COORDINATE_LEN);
				hex_dump("Public key [x]:", g_local_adapter.smp_data.local_p256_key_y, SMP_PUB_KEY_COORDINATE_LEN);
				hex_dump("Private key:", g_local_adapter.smp_data.local_p256_private_key, SMP_PRIVATE_KEY_LEN);
				g_local_adapter.smp_data.sc_support = TRUE;
			}
			else
			{
				loge("Generating of public keys failed");
				g_local_adapter.smp_data.sc_support = FALSE;
			}
			g_local_adapter.smp_data.smp_cur_cb.state = SMP_STATE_IDLE;
			smp_mgr_init_cb();
			break;
#endif /* HOST_ECDH */
#endif /* SECURE_CONNECTION */
	}
}

static void smp_c1_1(UINT8* tk, UINT8* mrand, UINT8* smp_pair_req_cmd, UINT8* smp_pair_rsp_cmd, UINT8 initiating_dev_type,
		UINT8 responding_dev_type)
{
	UINT8 p1[16];
	logi("");
	memcpy(p1, smp_pair_rsp_cmd, 7);
	memcpy(p1+7, smp_pair_req_cmd, 7);
	p1[14] = responding_dev_type;
	p1[15] = initiating_dev_type;
	hex_dump("P1:", p1, 16);
	smp_xor(p1, mrand, 16);
	hex_dump("P1':", p1, 16);
	/* e( k, mrand XOR p1)*/
	smp_aes_encrypt(tk, p1);
}

static void smp_c1_2(UINT8 *tk, UINT8* p1,UINT8*intiating_dev_add, UINT8* responding_dev_add)
{
	UINT8 p2[16];
	logi("");
	/* p2 = padding|ia|ra*/
	memset(p2, 0, 16);
	memcpy(p2+4, intiating_dev_add, 6);
	memcpy(p2+10, responding_dev_add, 6);
	hex_dump("P2:", p2, 16);
	/*p1 XOR p2*/
	smp_xor(p2, p1, 16);
	hex_dump("P2':", p2, 16);
	smp_aes_encrypt(tk, p2);
}
static void smp_aes_encrypt(UINT8* key,UINT8* plain_text)
{
	logi("");
	hex_dump("PTXT:", plain_text, 16);
	hex_dump("KEY:", key, 16);
	hci_ble_encrypt(key, plain_text);
}

static void smp_xor(UINT8* x, UINT8* y, int len)
{
	for (len = len -1; len >= 0; len--)
	{
		x[len] = x[len] ^ y[len];
	}
}

static void smp_mask_key(UINT8* key, UINT8 len)
{
	memset(key, 0, SMP_MAX_ENC_KEY_SIZE - len);
}

#if (AES_CMAC)
static void smp_aes_cmac(UINT8 *data, UINT16 len, UINT8 *key)
{
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	cur_cb->cmac_data = data;
	memcpy(cur_cb->cmac_key, key, SMP_MAX_KEY_LEN);
	cur_cb->no_of_blocks = ((UINT8)len + SMP_CMAC_LEN - 1) / SMP_CMAC_LEN;
	cur_cb->cmac_data = (UINT8*)alloc(cur_cb->no_of_blocks * SMP_CMAC_LEN);

	if(!cur_cb->cmac_data)
		return;

	memcpy(cur_cb->cmac_data, data, len);
	hex_dump("DATA:", cur_cb->cmac_data, len);
	if(len % SMP_CMAC_LEN != 0)
	{
			logd("Not a complete block");
			cur_cb->complete_block = FALSE;
			cur_cb->cmac_data[len] = 0x80;
			memset(&cur_cb->cmac_data[len + 1], 0, ((cur_cb->no_of_blocks * SMP_CMAC_LEN) - len - 1));
	}
	else
	{
		cur_cb->complete_block = TRUE;
	}

	smp_cal_sub_keys();
}
#endif /* AES_CMAC */

#if (SECURE_CONNECTION)
static void smp_f4(UINT8 *u, UINT8 *v, UINT8 *x, UINT8 z)
{
	UINT8 data[SMP_PUB_KEY_COORDINATE_LEN *2 + 1];
	UINT8 *pp = data;
	logi("z = 0x%x", z);
	ARRAY_TO_STREAM(pp, u, SMP_PUB_KEY_COORDINATE_LEN);
	ARRAY_TO_STREAM(pp, v, SMP_PUB_KEY_COORDINATE_LEN);
	UINT8_TO_STREAM(pp, z);
	smp_aes_cmac(data, SMP_PUB_KEY_COORDINATE_LEN *2 + 1, x);
}
static void smp_f5(UINT8 *w, UINT8 *n1, UINT8 *n2, UINT8 *a1, UINT8 *a2)
{
	/* start with creation of key T*/
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT8 *pp = cur_cb->f5_data;
	UINT16 length = 256;
	logd("");
	UINT8_TO_STREAM(pp, 0);
	ARRAY_TO_STREAM(pp, key_id, sizeof(key_id));
	ARRAY_TO_STREAM(pp, n1, SMP_MAX_KEY_LEN);
	ARRAY_TO_STREAM(pp, n2, SMP_MAX_KEY_LEN);
	ARRAY_TO_STREAM(pp, a1, BD_ADDR_LEN + 1);
	ARRAY_TO_STREAM(pp, a2, BD_ADDR_LEN + 1);
	UINT8 *p = (UINT8*)&length;
	REVERSE_ARRAY_TO_STREAM(pp, p, sizeof(length));
	smp_aes_cmac(w, SMP_DHKEY_LEN, aes_cmac_salt);
}
static void smp_f6(UINT8 *w, UINT8 *n1, UINT8 *n2, UINT8 *r, UINT8 *iocap, UINT8 *a1, UINT8 *a2)
{
	UINT8 data[SMP_F6_DATA_LEN];
	UINT8 *pp = data;
	logi("");
	ARRAY_TO_STREAM(pp, n1, SMP_MAX_KEY_LEN);
	ARRAY_TO_STREAM(pp, n2, SMP_MAX_KEY_LEN);
	ARRAY_TO_STREAM(pp, r, SMP_MAX_KEY_LEN);
	ARRAY_TO_STREAM(pp, iocap, 3);
	ARRAY_TO_STREAM(pp, a1, BD_ADDR_LEN + 1);
	ARRAY_TO_STREAM(pp, a2, BD_ADDR_LEN + 1);
	smp_aes_cmac(data, SMP_F6_DATA_LEN, w);

}
static void smp_g2(UINT8 *u, UINT8 *v, UINT8 *x, UINT8 *y)
{
	UINT8 data[SMP_PUB_KEY_COORDINATE_LEN *2 + SMP_MAX_KEY_LEN];
	UINT8 *pp = data;
	logi("");
	hex_dump("U:", u , SMP_PUB_KEY_COORDINATE_LEN);
	hex_dump("v:", v , SMP_PUB_KEY_COORDINATE_LEN);
	hex_dump("x:", x , SMP_MAX_KEY_LEN);
	hex_dump("y:", y , SMP_MAX_KEY_LEN);
	ARRAY_TO_STREAM(pp, u, SMP_PUB_KEY_COORDINATE_LEN);
	ARRAY_TO_STREAM(pp, v, SMP_PUB_KEY_COORDINATE_LEN);
	ARRAY_TO_STREAM(pp, y, SMP_MAX_KEY_LEN);
	hex_dump("DATA:", data, SMP_PUB_KEY_COORDINATE_LEN *2 + SMP_MAX_KEY_LEN);
	smp_aes_cmac(data, SMP_PUB_KEY_COORDINATE_LEN *2 + SMP_MAX_KEY_LEN, x);
}
#if (HOST_ECDH == TRUE)
static void smp_generate_p256_key_internal()
{
	/* Need to generate the random seed for private key first*/
	g_local_adapter.smp_data.smp_cur_cb.enc_stage = SMP_ENC_RAND_P256_1;
	hci_ble_rand();
}
#endif /* HOST_ECDH */

static void smp_generate_p256_keys()
{
#if (CONTROLLER_ECDH == TRUE)
	hci_ble_read_local_p256_public_key();
#elif (HOST_ECDH == TRUE)
	smp_generate_p256_key_internal();
#endif /* CONTROLLER_ECDH */
}

#if(ECC_TESTING == TRUE)
	void smp_ecc_test()
	{
		UINT8 public_key_Ax1[32], public_key_Ay1[32], private_key_A1[32];
		logd("*******************************************ECC TESTING *********************************");
		UINT8 private_key_A[32] = { 0x3f, 0x49, 0xf6, 0xd4, 0xa3, 0xc5, 0x5f, 0x38, 0x74, 0xc9, 0xb3, 0xe3,
				0xd2, 0x10, 0x3f, 0x50, 0x4a, 0xff, 0x60, 0x7b, 0xeb, 0x40, 0xb7, 0x99, 0x58, 0x99, 0xb8,
				0xa6, 0xcd, 0x3c, 0x1a, 0xbd };
		UINT8 public_key_Ax[32] = { 0x20, 0xb0, 0x03, 0xd2, 0xf2, 0x97, 0xbe, 0x2c, 0x5e, 0x2c, 0x83, 0xa7,
						0xe9, 0xf9, 0xa5, 0xb9, 0xef, 0xf4, 0x91, 0x11, 0xac, 0xf4, 0xfd, 0xdb, 0xcc, 0x03,
						0x01, 0x48, 0x0e, 0x35, 0x9d, 0xe6 };
		UINT8 public_key_Ay[32] = { 0xdc, 0x80, 0x9c, 0x49, 0x65, 0x2a, 0xeb, 0x6d, 0x63, 0x32, 0x9a, 0xbf,
								0x5a, 0x52, 0x15, 0x5c, 0x76, 0x63, 0x45, 0xc2, 0x8f, 0xed, 0x30, 0x24,
								0x74, 0x1c, 0x8e, 0xd0, 0x15, 0x89, 0xd2, 0x8b };
		gen_public_private_key_pair(private_key_A, private_key_A1, public_key_Ax1, public_key_Ay1);
		hex_dump("ECC generated public_x:", public_key_Ax1, 32);
		hex_dump("SIG specified public_x:", public_key_Ax, 32);
		if(memcmp(public_key_Ax1, public_key_Ax, 32) != 0)
		{
			loge("Key generation failed");
			return;
		}
		hex_dump("ECC generated public_y:", public_key_Ay1, 32);
		hex_dump("SIG specified public_y", public_key_Ay, 32);
		if(memcmp(public_key_Ay1, public_key_Ay, 32) != 0)
		{
			loge("Key generation failed");
			return;
		}
		hex_dump("ECC generated private_key:", private_key_A1, 32);
		hex_dump("SIG specified private_key:", private_key_A, 32);
		if(memcmp(private_key_A1, private_key_A, 32) != 0)
		{
			loge("Key generation failed");
			return;
		}
		UINT8 private_key_B[32] = { 0x55, 0x18, 0x8b, 0x3d, 0x32, 0xf6, 0xbb, 0x9a, 0x90, 0x0a, 0xfc, 0xfb, 0xee, 0xd4, 0xe7, 0x2a,
				0x59, 0xcb, 0x9a, 0xc2, 0xf1, 0x9d, 0x7c, 0xfb, 0x6b, 0x4f, 0xdd, 0x49, 0xf4, 0x7f, 0xc5, 0xfd };
		UINT8 public_key_Bx[32] = { 0x1e, 0xa1, 0xf0, 0xf0, 0x1f, 0xaf, 0x1d, 0x96, 0x09, 0x59, 0x22, 0x84, 0xf1, 0x9e, 0x4c, 0x00,
				0x47, 0xb5, 0x8a, 0xfd, 0x86, 0x15, 0xa6, 0x9f, 0x55, 0x90, 0x77, 0xb2, 0x2f, 0xaa, 0xa1, 0x90 };
		UINT8 public_key_By[32] = { 0x4c, 0x55, 0xf3, 0x3e, 0x42, 0x9d, 0xad, 0x37, 0x73, 0x56, 0x70, 0x3a, 0x9a, 0xb8, 0x51, 0x60,
				0x47, 0x2d, 0x11, 0x30, 0xe2, 0x8e, 0x36, 0x76, 0x5f, 0x89, 0xaf, 0xf9, 0x15, 0xb1, 0x21, 0x4a };
		UINT8 public_key_Bx1[32], public_key_By1[32], private_key_B1[32];
		gen_public_private_key_pair(private_key_B, private_key_B1, public_key_Bx1, public_key_By1);
		hex_dump("ECC generated public_x:", public_key_Bx1, 32);
		hex_dump("SIG specified public_x:", public_key_Bx, 32);
		if(memcmp(public_key_Bx1, public_key_Bx, 32) != 0)
		{
			loge("Key generation failed");
			return;
		}
		hex_dump("ECC generated public_y:", public_key_By1, 32);
		hex_dump("SIG specified public_y", public_key_By, 32);
		if(memcmp(public_key_By1, public_key_By, 32) != 0)
		{
			loge("Key generation failed");
			return;
		}
		hex_dump("ECC generated private_key:", private_key_B1, 32);
		hex_dump("SIG specified private_key:", private_key_B, 32);
		if(memcmp(private_key_B1, private_key_B, 32) != 0)
		{
			loge("Key generation failed");
			return;
		}
		UINT8 dhkey[32] = { 0xec, 0x02, 0x34, 0xa3, 0x57, 0xc8, 0xad, 0x05,  0x34, 0x10, 0x10, 0xa6, 0x0a, 0x39, 0x7d, 0x9b,
				0x99, 0x79, 0x6b, 0x13, 0xb4, 0xf8, 0x66, 0xf1, 0x86, 0x8d, 0x34, 0xf3, 0x73, 0xbf, 0xa6, 0x98};
		UINT8 dhkey1[32];
		cal_dhkey(private_key_B1, public_key_Ax1, public_key_Ay1, dhkey1);
		hex_dump("ECC generated dhkey_key:", dhkey1, 32);
		hex_dump("SIG specified dhkey_key:", dhkey, 32);
		if(memcmp(dhkey1, dhkey, 32) != 0)
		{
			loge("Dhkey failed");
			return;
		}
		cal_dhkey(private_key_A1, public_key_Bx1, public_key_By1, dhkey1);
		hex_dump("ECC generated dhkey_key:", dhkey1, 32);
		hex_dump("SIG specified dhkey_key:", dhkey, 32);
		if(memcmp(dhkey1, dhkey, 32) != 0)
		{
			loge("Dhkey failed");
			return;
		}
		logd("One set of SIG specified values have been tested");
		logd("***************************************ECC TEST CASE PASSED **************************************");
	}
#endif
#endif /* SECURE_CONNECTION */

/********************************************** Timer functions *********************************/

static int smp_create_cmd_timer()
{
	return osa_create_timer(&(g_local_adapter.smp_data.smp_cmd_timer_id), g_local_adapter.smp_data.SMP_CMD_TIMER,
			g_local_adapter.smp_data.SMP_CMD_TIMER_ISR,sizeof(g_local_adapter.smp_data.SMP_CMD_TIMER)/sizeof(osa_timer_static_t),
			smp_cmd_timer_expire_cb, 0);
}

static int smp_destroy_cmd_timer()
{
	return osa_delete_timer(&(g_local_adapter.smp_data.smp_cmd_timer_id),g_local_adapter.smp_data.SMP_CMD_TIMER);
}

static void smp_cmd_timer_expire_handler(osa_timer_arg_t arg)
{
	 smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	 logi("");
	 cur_cb->status = SMP_UNSPECIFIED_REASON;
	 smp_clean_up();
}

static void smp_cmd_timer_expire_cb(osa_timer_arg_t arg)
{
	logi("");
	timer_expire_evt_msg(smp_cmd_timer_expire_handler, arg);
}

static int smp_start_cmd_timer()
{
	logi("");
	return osa_start_timer(&(g_local_adapter.smp_data.smp_cmd_timer_id), g_local_adapter.smp_data.SMP_CMD_TIMER,
			SMP_CMD_TIMEOUT_MS, smp_cmd_timer_expire_cb, 0);

}

static int smp_stop_cmd_timer()
{
	logi("");
	if(osa_is_timer_active(&(g_local_adapter.smp_data.smp_cmd_timer_id),g_local_adapter.smp_data.SMP_CMD_TIMER, 0))
		return osa_stop_timer(&(g_local_adapter.smp_data.smp_cmd_timer_id), g_local_adapter.smp_data.SMP_CMD_TIMER, 0);
	else
	{
		logd("Command timer not active");
		return 1;
	}
}

static int smp_create_app_timer()
{
	return osa_create_timer(&(g_local_adapter.smp_data.smp_app_timer_id), g_local_adapter.smp_data.SMP_APP_TIMER,
			g_local_adapter.smp_data.SMP_APP_TIMER_ISR, sizeof(g_local_adapter.smp_data.SMP_APP_TIMER)/sizeof(osa_timer_static_t),
			smp_app_timer_expire_cb, 0);
}

static int smp_destroy_app_timer()
{
	return osa_delete_timer(&(g_local_adapter.smp_data.smp_app_timer_id),g_local_adapter.smp_data.SMP_APP_TIMER);
}

static void smp_app_timer_expire_handler(osa_timer_arg_t arg)
{
	 smp_cb_t *cur_cb;
	 logi("");
	 cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	 if(cur_cb->state == SMP_STATE_WAIT_AUTHORIZATION)
		 cur_cb->status = SMP_UNSPECIFIED_REASON;
	 else if(cur_cb->state == SMP_STATE_WAIT_PASSKEY || cur_cb->state == SMP_STATE_WAIT_CNF_CMD)
		 cur_cb->status = SMP_PASS_KEY_FAILED;
	 else if(cur_cb->state == SMP_STATE_WAIT_NC || cur_cb->state == SMP_STATE_WAIT_DHKEY_CHECK_CMD)
		 cur_cb->status = SMP_NUMERIC_COMPARISON_FAILED;
	 else
		 cur_cb->status = SMP_UNSPECIFIED_REASON;
	 smp_pair_failed_evt();
}

static void smp_app_timer_expire_cb(osa_timer_arg_t arg)
{
	logi("");
	timer_expire_evt_msg(smp_app_timer_expire_handler, arg);
}

static int smp_start_app_timer()
{
	logi("");
	return osa_start_timer(&(g_local_adapter.smp_data.smp_app_timer_id), g_local_adapter.smp_data.SMP_APP_TIMER,
			SMP_APP_TIMEOUT_MS, smp_app_timer_expire_cb, 0);

}

static int smp_stop_app_timer()
{
	logi("");
	if(osa_is_timer_active(&(g_local_adapter.smp_data.smp_app_timer_id),g_local_adapter.smp_data.SMP_APP_TIMER, 0))
		return osa_stop_timer(&(g_local_adapter.smp_data.smp_app_timer_id), g_local_adapter.smp_data.SMP_APP_TIMER, 0);
	else
	{
		logd("Application timer not active");
		return 1;
	}
}


/********************************************SMP API's***************************************/
/* SMP APIs used by SMP Manager*/

/** @brief This is called by smp manager to initialise SMP
 *
 * Function: smp_init
 * 				Initialises the SMP by resetting the control block and initialising the cmd timer. It also initialises the encryption operations
 * 				by creating a DHK and IRK.
 * @return Error code.
 * */
INT8 smp_init()
{
	logi("");
	memset(&(g_local_adapter.smp_data), 0, sizeof(smp_data_t));
	g_io_cap = SMP_DEFAULT_IO_CAP;
	g_sec_level = 0x00;
	g_enc_key_size = SMP_DEFAULT_ENC_KEY_SIZE;
	g_key_dist = 0x00;

	if (g_io_cap != SMP_NO_INPUT_NO_OUTPUT)
		g_sec_level |= SMP_MITM_Y;
#if ( SECURE_CONNECTION )
	g_sec_level |= SMP_SC_Y;
#endif
	smp_init_enc();
	if(smp_create_cmd_timer())
	{
		loge("Create timer failed");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	if(smp_create_app_timer())
	{
		loge("Application timer failed");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	if(g_local_adapter.smp_data.smp_cur_cb.state == SMP_STATE_IDLE)
		smp_mgr_init_cb();
	return STATUS_SUCCESS;
}

#if (PRIVACY_FEATURE == TRUE)
INT8 smp_generate_local_irk()
{
	logi("");
	if(g_local_adapter.smp_data.smp_cur_cb.state != SMP_STATE_IDLE || g_local_adapter.smp_data.smp_cur_cb.enc_stage != SMP_ENC_IDLE)
	{
		logd("SMP busy state = %d", g_local_adapter.smp_data.smp_cur_cb.state);
		logd("Enc state = %d", g_local_adapter.smp_data.smp_cur_cb.enc_stage);
		return STATUS_ERR_BUSY;
	}
	g_local_adapter.smp_data.smp_cur_cb.enc_stage = SMP_ENC_IRK_GEN_S1;
	return hci_ble_rand();
}
#endif

INT8 smp_set_io_capabilities(UINT8 io_capabilities)
{
	INT8 ret = STATUS_SUCCESS;
	if (io_capabilities <= SMP_MAX_IO_CAP)
	{
		if(io_capabilities != SMP_NO_INPUT_NO_OUTPUT && !g_local_adapter.smp_mgr_data.smp_app_cback)
			return STATUS_ERR_OPERATION_NOT_SUPPORTED;
		g_io_cap = io_capabilities;
	}
	else
		ret = STATUS_ERR_INVALID_PARAM;
	if(g_io_cap != SMP_NO_INPUT_NO_OUTPUT)
		g_sec_level |= SMP_MITM_Y;
	else
		g_sec_level &= ~(SMP_MITM_Y);
	return ret;
}

BOOLEAN smp_check_key_level(UINT8 auth_level, UINT8 key_type)
{
	if(auth_level & SMP_SC_Y)
	{
		if(key_type != SMP_KEY_TYPE_SC_AUTHENTICATED && key_type != SMP_KEY_TYPE_SC_UNAUTHENTICATED)
			return FALSE;
	}
	if(auth_level & SMP_MITM_Y)
	{
		if(key_type != SMP_KEY_TYPE_AUTHENTICATED && key_type != SMP_KEY_TYPE_SC_AUTHENTICATED)
			return FALSE;
	}
	return TRUE;
}

UINT8 check_device_config(UINT8 auth_level, UINT8 enc_key_size)
{
	if(g_enc_key_size < enc_key_size)
		return 0;
	if((auth_level & SMP_SC_Y) && !(g_sec_level & SMP_SC_Y))
		return 0;
	if((auth_level & SMP_MITM_Y) && !(g_sec_level & SMP_MITM_Y))
		return 0;
	return 1;
}

INT8 smp_pair(connected_device_t *device,UINT8 auth_level_min, UINT8 key_size_min)
{
	smp_cb_t* cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->state != SMP_STATE_IDLE)
		return STATUS_ERR_BUSY;

	g_local_adapter.smp_data.smp_cur_cb.operation = SMP_BONDING_OPERATION;
	if (check_device_config(auth_level_min, key_size_min) == 0)
	{
		cur_cb->status = SMP_AUTH_FAILED;
		smp_clean_up();
		return STATUS_SUCCESS;
	}
	memcpy(cur_cb->bdaddr, device->bdaddr, BD_ADDR_LEN);
	cur_cb->conn_id = device->idx;
	cur_cb->local_init_key = cur_cb->local_resp_key = g_key_dist;
	cur_cb->local_auth_req = cur_cb->peer_auth_req = g_sec_level;
	cur_cb->local_auth_level_min = auth_level_min;
	cur_cb->local_enc_key_size = g_enc_key_size;
	cur_cb->local_enc_key_size_min = key_size_min;
	cur_cb->local_io_cap = g_io_cap;

	smp_create_bond_evt();
	return STATUS_SUCCESS;
}

INT8 smp_start_encryption(connected_device_t *device, UINT8 auth_level_min, UINT8 key_size_min)
{
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->state != SMP_STATE_IDLE)
		return STATUS_ERR_BUSY;
	memcpy(cur_cb->bdaddr, device->bdaddr, BD_ADDR_LEN);
	cur_cb->conn_id = device->idx;
	g_local_adapter.smp_data.smp_cur_cb.operation = SMP_BONDING_OPERATION;
	if(g_local_adapter.connected_device[cur_cb->conn_id]->local_link_role)
	{
		/*Slave... send security request*/
		UINT8 sec_level = 0;
		switch(device->link_enc_state.key_type)
		{
			case SMP_KEY_TYPE_AUTHENTICATED:
				sec_level = (SMP_MITM_Y | SMP_BONDING_Y);
				cur_cb->pairing_method = SMP_LEGACY_PAIRING;
				break;
			case SMP_KEY_TYPE_UNAUTHENTICATED:
				sec_level = (SMP_MITM_N | SMP_BONDING_Y);
				cur_cb->pairing_method = SMP_LEGACY_PAIRING;
				break;
			case SMP_KEY_TYPE_SC_AUTHENTICATED:
				sec_level = (SMP_SC_Y | SMP_MITM_Y | SMP_BONDING_Y);
				cur_cb->pairing_method = SMP_SECURE_PAIRING;
				break;
			case SMP_KEY_TYPE_SC_UNAUTHENTICATED:
				sec_level = (SMP_SC_Y | SMP_MITM_N | SMP_BONDING_Y);
				cur_cb->pairing_method = SMP_SECURE_PAIRING;
				break;
		}
		cur_cb->state = SMP_STATE_WAIT_PAIR_CMD;
		cur_cb->local_auth_req = g_sec_level;
		cur_cb->local_auth_level_min = auth_level_min;
		cur_cb->local_init_key = cur_cb->local_resp_key = g_key_dist;
		cur_cb->local_io_cap = g_io_cap;
		cur_cb->enc_with_ltk = TRUE;
		cur_cb->local_enc_key_size = device->link_enc_state.key_size;
		cur_cb->local_enc_key_size_min = key_size_min;
		cur_cb->cur_key.key_type = device->link_enc_state.key_type;
		cur_cb->cur_key.key_size = device->link_enc_state.key_size;
		cur_cb->cur_key.security_level = device->link_enc_state.secuirty_level;
		smp_send_security_request_cmd(sec_level);
	}
	else
	{
		cur_cb->state = SMP_STATE_WAIT_ENC_CHG;
		cur_cb->enc_with_ltk = TRUE;
		cur_cb->local_enc_key_size = device->link_enc_state.key_size;
		cur_cb->cur_key.key_type = device->link_enc_state.key_type;
		cur_cb->cur_key.key_size = device->link_enc_state.key_size;
		cur_cb->cur_key.security_level = device->link_enc_state.secuirty_level;
		if(device->link_enc_state.key_type == SMP_KEY_TYPE_SC_AUTHENTICATED || device->link_enc_state.key_type == SMP_KEY_TYPE_SC_UNAUTHENTICATED)
		{
			cur_cb->pairing_method = SMP_SECURE_PAIRING;
		}
		device->link_enc_state.pending_act |= LINK_ENC_PENDING;
		logd("Enc pending set : %02x", device->link_enc_state.pending_act);
		fetch_key(device, PEER_LTK);
	}
	return STATUS_SUCCESS;
}

void smp_send_authorization(UINT8 *remote_bd_addr, UINT8 authorization, UINT8 auth_level_min, UINT8 key_size_min)
{
	connected_device_t *device;
#if (PARANOID_STACK == TRUE)
	if(remote_bd_addr == NULL)
	{
		return;
	}
#endif
	logi("");
	device = get_connected_device_by_id_addr(remote_bd_addr);
	if( device && device->idx == g_local_adapter.smp_data.smp_cur_cb.conn_id)
	{
		if(authorization == 1)
		{
			smp_authorization_grant_evt(&authorization, auth_level_min, key_size_min);
		}
		else
		{
			if ( g_local_adapter.smp_data.smp_cur_cb.operation == SMP_BONDING_OPERATION)
			{
				g_local_adapter.smp_data.smp_cur_cb.status = SMP_UNSPECIFIED_REASON;
				smp_pair_failed_evt();
			}
		}
	}
#if (PARANOID_STACK == TRUE)
	else
	{
		loge("Authorization event for unknown BD addres");
		hex_dump("BDADDR:", remote_bd_addr, BD_ADDR_LEN);
	}
#endif
}

void smp_send_passkey(UINT32 passkey)
{
	logi("");
	smp_tk_gen_evt((UINT8*)(void*)&passkey);
}

#if (SECURE_CONNECTION)
void smp_send_nc_result(UINT8 *remote_bd_addr, UINT8 authorization)
{
	connected_device_t *device;
#if (PARANOID_STACK == TRUE)
	if(remote_bd_addr == NULL)
	{
		return;
	}
#endif
	logi("");
	device  = get_connected_device_by_id_addr(remote_bd_addr);
	if( device && device->idx == g_local_adapter.smp_data.smp_cur_cb.conn_id)
	{
		if(authorization == 1)
		{
			smp_nc_grant_evt(&authorization);
		}
		else
		{
			g_local_adapter.smp_data.smp_cur_cb.status = SMP_NUMERIC_COMPARISON_FAILED;
			smp_pair_failed_evt();
		}
	}
#if (PARANOID_STACK == TRUE)
	else
	{
		loge("Authorization event for unknown BD addres");
		hex_dump("BDADDR:", remote_bd_addr, BD_ADDR_LEN);
	}
#endif
}
#endif /* SECURE_CONNECTION */

#if (PRIVACY_FEATURE)
INT8 smp_rpa_generate()
{
	logi("");
	if(g_local_adapter.smp_data.smp_cur_cb.state != SMP_STATE_IDLE)
			return STATUS_ERR_BUSY;
	g_local_adapter.smp_data.smp_cur_cb.state = SMP_STATE_WAIT_RPA_GEN;
	g_local_adapter.smp_data.smp_cur_cb.operation = SMP_RPA_GENERATION;
	smp_gen_rpa();
	return STATUS_SUCCESS;
}

INT8 smp_rpa_resolve(UINT8* rpa, BOOLEAN local)
{
	logi("");
	if(g_local_adapter.smp_data.smp_cur_cb.state != SMP_STATE_IDLE)
			return STATUS_ERR_BUSY;
	g_local_adapter.smp_data.smp_cur_cb.state = SMP_STATE_WAIT_RPA_RES;
	g_local_adapter.smp_data.smp_cur_cb.operation = SMP_RPA_RESOLUTION;
	memcpy(g_local_adapter.smp_data.smp_cur_cb.rpa, rpa, BD_ADDR_LEN);
	g_local_adapter.smp_data.smp_cur_cb.idx = 0;
	smp_res_rpa(local);
	return STATUS_SUCCESS;
}
#endif /* PRIVACY_FEATURE */

#if (SIGNED_WRITE)

INT8 smp_sign_data(connected_device_t *device, UINT8 *data, UINT16 data_len)
{
	UINT8 *pp = NULL;
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT16 total_len;
	UINT8 *cmac_data;
	UINT8 *p;
	logi("");
	if(cur_cb->state != SMP_STATE_IDLE)
		return STATUS_ERR_BUSY;
	cur_cb->sign_gen = TRUE;
	memcpy(cur_cb->bdaddr, device->bdaddr, BD_ADDR_LEN);
	cur_cb->conn_id = device->idx;
	if(!device->local_sign_info.valid)
	{
		device->link_enc_state.pending_act |= LINK_SIGN_PENDING;
		fetch_key(device, LOCAL_CSRK);
		return STATUS_SUCCESS;
	}
	total_len = data_len + sizeof(device->local_sign_info.sign_key.counter);
	cmac_data = (UINT8*)alloc(total_len);
	if(!cmac_data)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	pp = cmac_data;
	p = (UINT8*)(void*)&device->local_sign_info.sign_key.counter;
	pp[0] = p[3];
	pp[1] = p[2];
	pp[2] = p[1];
	pp[3] = p[0];
	JUMP_CUSTOM_LEN(pp, sizeof(device->local_sign_info.sign_key.counter));
	REVERSE_ARRAY_TO_STREAM(pp, data, data_len);
	g_local_adapter.smp_data.smp_cur_cb.state = SMP_STATE_WAIT_SIGN_GEN;
	g_local_adapter.smp_data.smp_cur_cb.operation = SMP_SIGN_GENERATION;
	smp_aes_cmac(cmac_data, total_len, device->local_sign_info.sign_key.csrk);
	dealloc(cmac_data);
	return STATUS_SUCCESS;
}

INT8 smp_sign_verify(connected_device_t *device,  UINT8 *data, UINT16 data_len)
{
	UINT8 *pp = NULL;
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	UINT16 total_len ;
	UINT8 *cmac_data;
	UINT8 *p;
	UINT32 sign_counter;

	logi("");
	hex_dump("Data to be verified:", data, data_len);
	if(cur_cb->state != SMP_STATE_IDLE)
			return STATUS_ERR_BUSY;

	memcpy(cur_cb->bdaddr, device->bdaddr, BD_ADDR_LEN);
	cur_cb->conn_id = device->idx;
	if(!device->peer_sign_info.valid)
	{
		device->link_enc_state.pending_act |= LINK_VERIFY_PENDING;
		fetch_key(device, PEER_CSRK);
		return STATUS_SUCCESS;
	}
	cur_cb->sign_gen = FALSE;
	total_len = data_len - 8;
	cur_cb->data_to_be_verified = (UINT8*)alloc(sizeof(UINT8)*8);

	if (!cur_cb->data_to_be_verified)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	memcpy(cur_cb->data_to_be_verified, data + total_len, 8);
	p = data + (data_len - SMP_MAC_LEN);
	STREAM_TO_UINT32(sign_counter, p);
	logi("Counter value = %d", sign_counter);
	if(sign_counter < device->peer_sign_info.sign_key.counter)
	{
		loge("Sign counter less than the required value");
		return STATUS_ERR_LAYER_SPECIFIC;
	}
	sign_counter++;
	cmac_data = (UINT8*)alloc(total_len * sizeof(UINT8));
	if(!cmac_data)
	{
		dealloc(cur_cb->data_to_be_verified);
		return STATUS_ERR_LAYER_SPECIFIC;
	}
	pp = cmac_data;
	REVERSE_STREAM_TO_ARRAY(pp, data, total_len);
	if(g_local_adapter.smp_mgr_data.storage_mgr.storage_cb && g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_update_cb)
	{
		UINT8 sc[4];
		pp = sc;
		UINT32_TO_STREAM(pp, sign_counter);
		g_local_adapter.smp_mgr_data.storage_mgr.storage_cb->key_update_cb
		(g_local_adapter.smp_mgr_data.storage_mgr.trans_id, device->id_addr.bdaddr, device->id_addr.type, PEER_COUNTER, 4, sc);
	}
	device->peer_sign_info.sign_key.counter = sign_counter;
	g_local_adapter.smp_data.smp_cur_cb.state = SMP_STATE_WAIT_SIGN_GEN;
	g_local_adapter.smp_data.smp_cur_cb.operation = SMP_SIGN_VERIFICATION;
	smp_aes_cmac(cmac_data, total_len, device->peer_sign_info.sign_key.csrk);
	dealloc(cmac_data);
	return STATUS_SUCCESS;
}
#endif /* SIGNED_WRITE */

void smp_storage_registered()
{
	g_sec_level |= SMP_BONDING_Y;
	g_key_dist |= SMP_ENC_Y;
#if (SIGNED_WRITE == TRUE)
	g_key_dist |= SMP_SIGN_Y;
#endif
#if	(PRIVACY_FEATURE == TRUE)
	g_key_dist |= SMP_ID_Y;
#endif
}

INT8 smp_shutdown()
{
	smp_cb_t *cur_cb = &g_local_adapter.smp_data.smp_cur_cb;
	logi("");
	if(cur_cb->state != SMP_STATE_IDLE && cur_cb->state != SMP_STATE_WAIT_RPA_GEN
			&& cur_cb->state != SMP_STATE_WAIT_RPA_RES && cur_cb->state != SMP_STATE_WAIT_SIGN_GEN)
	{
		cur_cb->status = SMP_UNSPECIFIED_REASON;
		smp_pair_failed_evt();
	}

	if(smp_destroy_cmd_timer())
	{
		if(smp_destroy_app_timer() == 0)
			return STATUS_SUCCESS;
		return STATUS_ERR_LAYER_SPECIFIC;
	}
	else
	{
		smp_destroy_app_timer();
		return STATUS_ERR_LAYER_SPECIFIC;
	}
}

#else

void smp_l2cap_connect_cb(connected_device_t *device)
{
	logi("");
}

void smp_l2cap_disconnect_cb(connected_device_t *device)
{
	logi("");
}

INT8 smp_l2cap_recv_data_cb(connected_device_t *device, UINT8* data,
		UINT16 data_len)
{
	buffer_t *data_pkt = (buffer_t*) get_l2cap_free_buffer(SMP_PAIRING_FAILED_LEN);
	if(NULL == data_pkt)
	{
		logd("L2cap packet unavailable");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}
	data_pkt->offset = L2CAP_HDR_SIZE + UART_HDR_SIZE + HCI_ACL_PREAMBLE_SIZE;
	data_pkt->length = 02;
	UINT8 *cmd = &data_pkt->data[data_pkt->offset];
	UINT8_TO_STREAM(cmd, 05);
	UINT8_TO_STREAM(cmd, 05);
	return l2cap_data_send(device->idx, SMP_CID, data_pkt);
}
#endif /* SMP_FEATURE */
