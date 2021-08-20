/** @file
  Device structure header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef DEVICE_STRUCT_H_
#define DEVICE_STRUCT_H_

#include "osa_types.h"
#include "bt_types.h"
#include "config_host.h"
#include "utils.h"
#include "error_code.h"


#define LINK_ROLE_MASTER 0
#define LINK_ROLE_SLAVE  1

#define GAP_ADV_TYPE_CONNECTABLE_UNDIRECTED			0
#define GAP_ADV_TYPE_CONNECTABLE_DIRECTED_HIGH_DUTY	1
#define GAP_ADV_TYPE_SCANNABLE_UNDIRECTED			2
#define GAP_ADV_TYPE_NONCONNECTABLE_UNDIRECTED		3
#define GAP_ADV_TYPE_CONNECTABLE_DIRECTED_LOW_DUTY	4

#define GAP_ADV_DATA_FLAGS						0x01
#define GAP_ADV_DATA_INCOMPLETE_16BIT_UUID		0x02
#define GAP_ADV_DATA_COMPLETE_16BIT_UUID		0x03
#define GAP_ADV_DATA_INCOMPLETE_32BIT_UUID		0x04
#define GAP_ADV_DATA_COMPLETE_32BIT_UUID		0x05
#define GAP_ADV_DATA_INCOMPLETE_128BIT_UUID		0x06
#define GAP_ADV_DATA_COMPLETE_128BIT_UUID		0x07
#define GAP_ADV_DATA_SHORTENED_LOCAL_NAME		0x08
#define GAP_ADV_DATA_COMPLETE_LOCAL_NAME		0x09
#define GAP_ADV_DATA_TX_POWER					0x0A
#define GAP_ADV_DATA_DEVICE_CLASS				0x0D
#define GAP_ADV_DATA_SOLICITATION_16BIT_UUID	0x14
#define GAP_ADV_DATA_SOLICITATION_32BIT_UUID	0x1F
#define GAP_ADV_DATA_SOLICITATION_128BIT_UUID	0x15
#define GAP_ADV_DATA_SERVICE_DATA_16BIT_UUID	0x16
#define GAP_ADV_DATA_SERVICE_DATA_32BIT_UUID	0x20
#define GAP_ADV_DATA_SERVICE_DATA_128BIT_UUID	0x21
#define GAP_ADV_DATA_APPEARANCE					0x19
#define GAP_ADV_DATA_ROLE						0x1C
#define GAP_ADV_DATA_MAUFACTURER				0xFF


#define GAP_ADV_FLAGS_LE_NOT_DISCOVERABLE		0
#define GAP_ADV_FLAGS_LE_LIMITED_DISCOVERABLE	(1 << 0)
#define GAP_ADV_FLAGS_LE_GENERAL_DISCOVERABLE	(1 << 1)

#define GAP_GATT_SRV_APP_HANDLE					0

/* Attribute opcodes */
#define ATT_OPCODE_ERROR_RESP					0x01
#define ATT_OPCODE_MTU_REQ						0x02
#define ATT_OPCODE_MTU_RESP						0x03
#define ATT_OPCODE_FIND_INFO_REQ				0x04
#define ATT_OPCODE_FIND_INFO_RESP				0x05
#define ATT_OPCODE_FIND_BY_TYPE_VAL_REQ			0x06
#define ATT_OPCODE_FIND_BY_TYPE_VAL_RESP		0x07
#define ATT_OPCODE_READ_BY_TYPE_REQ				0x08
#define ATT_OPCODE_READ_BY_TYPE_RESP			0x09
#define ATT_OPCODE_READ_REQ						0x0A
#define ATT_OPCODE_READ_RESP					0x0B
#define ATT_OPCODE_READ_BLOB_REQ				0x0C
#define ATT_OPCODE_READ_BLOB_RESP				0x0D
#define ATT_OPCODE_READ_MULTI_REQ				0x0E
#define ATT_OPCODE_READ_MULTI_RESP				0x0F
#define ATT_OPCODE_READ_BY_GRP_TYPE_REQ			0x10
#define ATT_OPCODE_READ_BY_GRP_TYPE_RESP		0x11
#define ATT_OPCODE_WRITE_REQ					0x12
#define ATT_OPCODE_WRITE_RESP					0x13
#define ATT_OPCODE_WRITE_CMD					0x52
#define ATT_OPCODE_PREP_WRITE_REQ				0x16
#define ATT_OPCODE_PREP_WRITE_RESP				0x17
#define ATT_OPCODE_EXEC_WRITE_REQ				0x18
#define ATT_OPCODE_EXEC_WRITE_RESP				0x19
#define ATT_OPCODE_HANDLE_VAL_NOTIFY			0x1B
#define ATT_OPCODE_HANDLE_VAL_IND				0x1D
#define ATT_OPCODE_HANDLE_VAL_CFM				0x1E
#define ATT_OPCODE_SIGN_WRITE_CMD				0xD2

/*ATT error codes */
#define ATT_SUCCESS				                0x00
#define ATT_ERR_INVALID_HANDLE                  0x01
#define ATT_ERR_READ_NOT_PREMITTED              0x02
#define ATT_ERR_WRITE_NOT_PERMITTED             0x03
#define ATT_ERR_INVALID_PDU                     0x04
#define ATT_ERR_INSUFF_AUTHENTICATION           0x05
#define ATT_ERR_REQ_NOT_SUPPORTED               0x06
#define ATT_ERR_INVALID_OFFSET                  0x07
#define ATT_ERR_INSUFF_AUTHORIZATION            0x08
#define ATT_ERR_PREP_QUEUE_FULL                 0x09
#define ATT_ERR_ATTRIB_NOT_FOUND                0x0A
#define ATT_ERR_ATTRIB_NOT_LONG                 0x0B
#define ATT_ERR_INSUFF_ENCR_KEY_SIZE            0x0C
#define ATT_ERR_INVALID_ATTRIB_VAL_LENGTH       0x0D
#define ATT_ERR_UNLIKELY                        0x0E
#define ATT_ERR_INSUFF_ENCR                     0x0F
#define ATT_ERR_UNSUPPORTED_GRP_TYPE            0x10
#define ATT_ERR_INSUFF_RESOURCE                 0x11
/* Local errors */
#define ATT_ERR_PENDING							0x12
#define ATT_ERR_LOCAL_ERROR						0x13
#define ATT_ERR_MAX								(ATT_ERR_LOCAL_ERROR +1)

#define ATTR_UUID_PRIMARY_SERVICE 								0x2800
#define ATTR_UUID_SECONDARY_SERVICE 							0x2801
#define ATTR_UUID_INCLUDE_SERCICE	 							0x2802
#define ATTR_UUID_CHARACTERISTIC 								0x2803

#define ATTR_UUID_CHARACTERISTIC_EXTENDED_PROP_DESCRIPTOR		0x2900
#define ATTR_UUID_CHARACTERISTIC_USER_DESCRIPTION_DESCRIPTOR	0x2901
#define ATTR_UUID_CLIENT_CHARACTERISTIC_CONFIG_DESCRIPTOR		0x2902
#define ATTR_UUID_SERVER_CHARACTERISTIC_CONFIG_DESCRIPTOR		0x2903
#define ATTR_UUID_CHARACTERISTIC_FORMAT_DESCRIPTOR				0x2904
#define ATTR_UUID_CHARACTERISTIC_AGGREGATE_DESCRIPTOR			0x2905

#define ATTR_TYPE_PRIMARY_SERVICE									1
#define ATTR_TYPE_SECONDARY_SERVICE									2
#define ATTR_TYPE_INCLUDED_SERVICE									3
#define ATTR_TYPE_CHARACTERISTIC									4
#define ATTR_TYPE_DESCRIPTOR										5
#define ATTR_TYPE_CHARACTERISTIC_VALUE								6

#define ATTR_TYPE_ANY												0
#define ATTR_TYPE_INVALID											0xFF
#define ATTR_MAX_HANDLE												0xFFFF

#define ATT_EXECUTE_WRITE_FLAG_CANCEL_WRITE		0x00
#define ATT_EXECUTE_WRITE_FLAG_SUCCESS			0x01

/* SMP events from lower layer*/
#define SMP_KEY_READY_EVT				6
#define SMP_AUTHORISATION_REQ_EVT 		31
#define SMP_PASSKEY_REQ_EVT				34
#define SMP_NUMERIC_COMPARISON_EVT		35



struct __discovered_device_t;
struct __connected_device_t;
struct __smp_bonding_key_t;

/**
 * This parameter structure unify read characteristic value, read descriptor value,
 *  read long characteristic value, read long descriptor value, read characteristic
 *  using UUID and read multiple characteristic value.
 */
typedef struct
{
	UINT8 att_opcode;
	union
	{
		struct
		{
			UINT16 att_id; /* For char read */
			UINT16 offset; /* use att_opcode for read blob req */
		} read_attr;
		struct
		{
			UINT16 start_handle;
			UINT16 end_handle;
			uuid_t uuid;
		} read_using_uuid_param;
		UINT16 multi_att_id_list[12]; /* anyway union will take 24. */
	} attr_read_param;
} gatt_attribute_read_param_t;

/** @brief Core stack calls this call back to notify completion of application
 * 			registration.
 *
 * @typedef register_application_cb_t
 * 			 Application will receive a application handle as a result of
 * 			 successful registration Through this call back function.
 * 			 Application should save the handle and pass the same value to the
 * 			 core stack whenever calling core stack api in future. Application
 * 			 handle is valid until application calls de-register or application
 * 			 gets de-registered by any other means. In case of de-registration
 * 			 application needs to register again by calling this api.
 *
 * @param app_handle handle for this application.
 * @param result result of registration status (TRUE / FALSE).
 * @return None.
 */
typedef void (*register_application_cb_t)(UINT8 app_handle, BOOLEAN result);

typedef void (*on_att_mtu_changed_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT16 mtu_size);

typedef void (*on_service_added_cb_t)(trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id);

typedef void (*on_included_service_added_cb_t)(trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id);

typedef void (*on_characteristic_added_cb_t)(trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id);

typedef void (*on_descriptor_added_cb_t)(trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id);

typedef void (*on_service_removed_cb_t)(trans_id_t trans_id, UINT8 status, UINT16 start_handle, UINT16 end_handle);

/** @brief Core stack calls this call back to notify completion of service start
 *
 * @typedef start_service_cb_t
 * 			 Application will receive a service handle as a result of
 * 			 successful service start through this call back function. The handle
 * 			 can be used during advertising for the service. If starting the
 * 			 service has failed, the handle returned will be 0.
 *
 * @param uuid UUID of the service
 * @param result Result of service start status (TRUE / FALSE).
 * @param start_handle Handle for the service.
 * @return None.
 */
typedef void (*on_service_started_cb_t)(trans_id_t trans_id, UINT8 status, uuid_t *uuid, UINT16 att_id);

/** @brief [Server call back]Core stack calls this call back when GATT server
 * 							 receives GATT characteristic read request.
 *
 * @typedef on_characteristic_read_req_cb_t
 *
 * @param device - Bluetooth device reference for remote bluetooth device [Soon
 * 					will be changed to UINT8 *remote_bd_addr].
 * @param att_id - attribute value handle
 * @param offset - Offset from which characteristic value has to be read.
 * @return None.
 */
typedef void (*on_attribute_read_req_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset);

/** @brief [Server call back]Core stack calls this call back when GATT server
 * 							 receives GATT characteristic write request.
 *
 * @typedef on_characteristic_write_req_cb_t
 *
 * @param device - Bluetooth device reference for remote bluetooth device [Soon
 * 					will be changed to UINT8 *remote_bd_addr].
 * @param att_id - attribute value handle
 * @param value - value buffer to be written to the characteristic
 * @param len - Value length in Bytes
 * @param offset - Offset in characteristic value from which this buffer should be written
 * @param need_response - FALSE for write without response. TRUE otherwise.
 * @param is_prepered_req - TRUE if this is a prepared write request. App should queue the value.
 * @param offset - if this is a prepared write request then offset notifies the value offset.
 * @return TRUE / FALSE.
 */
typedef void (*on_attribute_write_req_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, buffer_t* buffer);

/** @brief [Server call back]Core stack calls this call back when GATT server
 * 							 receives indication confirmation.
 *
 * @typedef on_indication_confirmation_cb_t
 *
 * @param device - Bluetooth device reference for remote bluetooth device [Soon
 * 					will be changed to UINT8 *remote_bd_addr].
 * @param characteristic - Reference to the GATT characteristic for which this
 * 					indication confirmation is received.
 * 					Application should never modify any of the variables in this.
 * 					If done core stack behaviour will be undefined.
 * @return None.
 */
typedef void (*on_indication_confirmation_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id);

/** @brief [Server call back]Core stack calls this call back when the handle of an
 * 							 attribute changes because of modifications to the ATT db
 *
 * @typedef on_attribute_handle_changed_cb_t
 *
 * @param old_handle - Old handle of the attribute
 * @param new_handle - New handle of the attribute
 * @return None.
 */
typedef void (*on_attribute_handle_changed_cb_t)(UINT16 old_handle, UINT16 new_handle);

/** @brief [Client call back]Core stack calls this call back when service discovery
 * 			to the remote device is done.
 *
 * @typedef on_service_discovered_cb_t
 * 			 Application will receive a reference to the service it wanted to
 * 			 discover. A GATT client is expected to register for this call back.
 *
 * @param remote_bd_addr - Bluetooth MAC address for the device for which service
 * 						 is discovered.
 * @param service - Reference to the GATT service. Application should never modify
 * 				    any of the variables in this. If done core stack behaviour
 * 				    will be undefined.
 * @return None.
 */
typedef void (*on_primary_service_discovered_cb_t)(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished);

typedef void (*on_included_service_discovered_cb_t)(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 inc_handle, UINT16 start_handle, UINT16 end_handle, uuid_t *uuid, BOOLEAN is_finished);

typedef void (*on_characteristic_discovered_cb_t)(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT8 property, UINT16 att_handle, UINT16 value_handle, uuid_t *uuid, BOOLEAN is_finished);

typedef void (*on_descriptor_discovered_cb_t)(trans_id_t trans_id, UINT8 status, UINT8 conn_id, UINT16 att_handle, uuid_t *uuid, BOOLEAN is_finished);

/** @brief [Client call back]Core stack calls this call back when GATT client
 * 							 receives response for GATT characteristic read request.
 *
 * @typedef on_characteristic_read_cb_t
 *
 * @param remote_bd_addr - Bluetooth MAC address for remote bluetooth device.
 * @param attribute - Reference to the GATT attribute being read.
 * @param value - value buffer of the characteristic
 * @param value_length - number of Bytes in the value buffer
 * @param status - Status of read.
 * @return None.
 */
typedef void (*on_attribute_read_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT8 opcode, UINT8 status, UINT16 att_id, buffer_t *buffer);

/** @brief [Client call back]Core stack calls this call back when GATT client
 * 							 receives response for GATT characteristic write request.
 *
 * @typedef on_characteristic_write_cb_t
 *
 * @param remote_bd_addr - Bluetooth MAC address for remote bluetooth device.
 * @param attribute - Reference to the GATT attribute being written.
 * @param status - Status of write.
 * @return None.
 */
typedef void (*on_attribute_write_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT8 opcode, UINT8 status, UINT16 att_id, UINT16 offset, buffer_t* buffer);

/** @brief [Client call back]Core stack calls this call back when GATT client
 * 							 receives GATT notification.
 *
 * @typedef on_notification_cb_t
 *
 * @param remote_bd_addr - Bluetooth MAC address for remote bluetooth device
 * @param characteristic - Reference to the GATT characteristic being notified / indicated.
 * 					Application should never modify any of the variables in this.
 * 					If done core stack behaviour will be undefined.
 * @param val - Value buffer for the notification / indication
 * @param len - Length in Bytes of the value buffer.
 * @param need_resp - TRUE : indication. Notification otherwise.
 * @return None.
 */
typedef void (*on_notification_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, buffer_t *buffer, BOOLEAN is_indication);

/** @brief [Client call back]Core stack calls this call back when GATT client
 * 							notification registering / de-registering is completed.
 *
 * @typedef on_notification_registered_cb_t
 *
 * @param remote_bd_addr - Bluetooth MAC address for remote device
 * @param characteristic - Reference to the GATT characteristic for which notification
 * 						   / indication was enabled / disabled.
 * @param status - Status of enabling notification / indication.
 * @return None.
 */
typedef void (*on_notification_registered_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, UINT8 status);

/** @brief Core stack calls this call back when connection is completed to a remote device.
 *
 * @typedef on_connected_cb_t - To get the call back application should call
 * 								connect API for this remote device. Then only
 * 								application will receive the call back on completion
 * 								of connection. Connection includes profile level
 * 								connection (including LE-U, L2CAP channel open).
 *
 * @param remote_bd_addr - Bluetooth MAC address for remote device
 * @param status - Status of connection.(0x00 for success, Non zero for Error)
 * @param from_remote - TRUE if the connection is remote initiated, FALSE otherwise.
 * @param id_addr - Identity address for the remote device
 * @param id_addr_type - Identity address type for the remote device
 * @return None.
 */

typedef void (*on_connected_cb_t)(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 status, BOOLEAN from_remote, UINT8 *id_addr, UINT8 id_addr_type);

/** @brief Core stack calls this call back when disconnection is completed to a remote device.
 *
 * @typedef on_disconnected_cb_t - To get the call back application should call
 * 								disconnect API for this remote device. Then only
 * 								application will receive the call back on completion
 * 								of connection.
 *
 * @param conn_id - connection id for remote device
 * @param status - Status of disconnection.
 * @return None.
 */
typedef void (*on_disconnected_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT8 status);

/** @brief [Device call back]Core stack calls this call back when device is found.
 *
 * @typedef scan_result_cb_t -	Application should call start_scan to enable scanning.
 * 								When a device is found satisfying the discoverability
 * 								type as specified by the app, this callback will be
 * 								called with the device information as well as the raw
 * 								advertisement data.
 *
 * @param device - discovered device
 * @param adv_data - raw advertisement data
 * @param len - length of raw advertisement data
 * @return None.
 */
typedef void (*scan_result_cb_t)(trans_id_t trans_id, struct __discovered_device_t *device);

/** @brief [Device call back]Core stack calls this call back when device search
 * 							is completed.
 *
 * @typedef scan_completed_cb_t - Application should call start_scan to enable
 * 								  enable scanning. When scan is completed (based on
 * 								  the timeout value given by the application)
 * 								  this call back will be called with the list of
 * 								  discovered devices.
 *
 * @param list - list of discovered devices
 * @return None.
 */
typedef void (*scan_completed_cb_t)(trans_id_t trans_id);

/** @brief [Device call back]Core stack calls this call back when adapter is enabled.
 *
 * @typedef on_conn_param_update_cb_t -	When conn param update is completed, this callback is sent out
 * 									to all registered devices.
 *
 * @param conn_id - connection id for remote device
 * @param status - Status of connection param update.
 * @param interval - Connection interval used on this connection
 * @param latency - Slave latency for the connection in number of connection events.
 * @param timeout - Supervision timeout for this connection.
 * @return None
 */

typedef void (*on_conn_param_update_cb_t)(trans_id_t trans_id, UINT8 status, UINT8 conn_id,
								UINT16 interval, UINT16 latency, UINT16 timeout);

/** @brief [Device call back]Core stack calls this call back when adapter is enabled.
 *
 * @typedef stack_initialized_cb_t -	When stack init is completed, this callback is sent out
 * 									to all registered devices. If any device is registered
 * 									after stack init happened, it instantly gets this callback.
 *
 * @return None
 */
typedef void (*stack_initialized_cb_t)(BOOLEAN initialized);;
/** @brief [Device call back]Core stack calls this call back when the link encryption changes on a link.
 *
 * @typedef on_link_enc_changed_cb_t - when link encryption is changed, this callback is sent out to the registered
 * 									   device.
 * @param bdaddr - Bluetooth Address of the device
 *
 * @param bdaddr_type - Address type of the device
 *
 * @param conn_id - connection identifier for the device
 *
 * @param status - Status whether encryption was success or not. 0 = Success else error code
 *
 * @param sec_level - Security level that was achieved as a part of this encryption.
 *
 * @return none
 */
typedef void (*on_link_enc_changed_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT8 status, UINT8 sec_level);

/** @brief [Device call back]Core stack calls this call back when bonding procedure is completed.
 *
 * @typedef bonding_complete_cb_t -	When bonding is completed, this callback is sent out
 * 									to the registered device which initiated the bonding. If any device is registered
 * 									after stack init happened, it instantly gets this callback.
 * @param bdaddr - Bluetooth Address of the device.
 *
 * @param status - Status of the bonding procedure.
 *
 * @param id_addr - Identity address for the remote device
 *
 * @param id_addr_type - Identity address type for the remote device
 * @return None
 */
typedef void (*bonding_complete_cb_t)(trans_id_t trans_id, UINT8 *bdaddr, UINT8 bdaddr_type, UINT8 conn_id, UINT8 status, UINT8 *id_addr, UINT8 id_addr_type);

/** @brief [Device call back]Core stack calls this call back when RPA resolution is completed.
 *
 * @typedef rpa_complete_cb_t -	When resolvable private address is completed, this callback is sent out
 * 									to the GAP.
 * @param status - Status of rpa generation procedure.
 *
 *
 * @return None
 */
typedef void (*rpa_complete_cb_t)(UINT8 *bdaddr, BOOLEAN local, UINT8 bonded_idx, UINT8 status);

/** @brief [Device call back]Core stack calls this call back when data signing procedure is completed.
 *
 * @typedef data_siging_complete_cb_t -	When data signing is completed, this callback is sent out
 * 									to the registered device which requested the data signing.
 * @param conn_id - Connection id of the device.
 *
 * @param status - Status of the data signing procedure.
 *
 * @param signed_data - The signed data (MAC).
 *
 * @return None
 */
typedef void (*data_siging_complete_cb_t)(UINT8 conn_id, UINT8 status, UINT8* signed_data);

typedef void (*sign_verify_complete_cb_t)(UINT8 conn_id, UINT8 status);
#if (TEST_CODE == TRUE && LE_PING_ENABLE==TRUE)
/** @brief [Device call back]Core stack calls this call back for reading authenticated payload timeout set in controller.
 *
 * @typedef read_authpayload_timout_cb_t -	When read authenticated payload timeout is issued for an encrypted link
 * 									the value set for authenticated payload timeout in controller is returned.
 *
 * @return None
 */
typedef void (*read_authpayload_timout_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT16 authpayload_timeout_ms);

#endif //TEST_CODE && LE_PING_ENABLE
#if (TEST_CODE == TRUE)
/** @brief [Device call back]Core stack calls this call back when a command complete or command status
 *	 is received for a vendor specific command
 *
 * @typedef vsc_evt_cb_t - Buffer contains the response from the controller and len is the length of the reponse
 *
 * @return None
 */
typedef void (*vsc_evt_cb_t)(trans_id_t trans_id, UINT8 len, UINT8 *buffer);

#endif

/** @brief [Device call back]Core stack calls this call back for LE Data Length Change event.
 * Notifies the Host of a change to either the maximum Payload length or the maximum transmission time of Data Channel PDUs in either direction.
 *
 * @typedef data_len_change_evt_cb_t -	When there is change in controller value for Data length or time for Tx/Rx then this callback is invoked.
 *
 * @return None
 */
typedef void (*data_len_change_evt_cb_t)(trans_id_t trans_id, UINT8 conn_id, UINT16 max_tx_octets, UINT16 max_tx_time, UINT16 max_rx_octets, UINT16 max_rx_time);

/* Storage callback functions */
/** @brief [Storage call back]Core stack calls this call back when it requires a key of a specific type
 *
 * @typedef key_req_cb_t - when a key is required for any security purpose like encrypting a link, resolving an address or signing data.
 *
 * @param bdaddr - Bluetooth address of the device for which key is requested.
 *
 * @param bdaddr_type - Address type of the device fo rwhich key is requested.
 *
 * @param key_type - The key that is required by the stack
 * 					 Eg : LOCAL_IRK, PEER_IRK, LOCAL_LTK, PEER_LTK, LOCAL_CSRK, PEER_CSRK etc.
 *
 * @param length - length of the key requested.
 */
typedef void (*key_req_cb_t)(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 key_type);
/** @brief [Storage call back]Core stack calls this call back when a key value is updated
 *
 * @typedef key_update_cb_t - when a key value is changed due to any security action.
 *
 * @param bdaddr - Bluetooth address of the device for which key value has changed.
 *
 * @param bdaddr_type - Address type of the device fo rwhich key value has changed.
 *
 * @param key_type - The key value which got changed
 * 					 Eg : LOCAL_SIGN_COUNTER, PEER_SIGN_COUNTER, LOCAL_IRK.
 *
 * @param length - Length of the key updated.
 *
 * @param key_value - updated value
 *
 */
typedef void (*key_update_cb_t)(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 key_type,  UINT8 length, UINT8* key_value);
/** @brief [Storage call back]Core stack calls this call back when group of keys are updated due to a bonding operation
 *
 * @typedef bonding_info_t - when a group of key value is changed due to bonding operation.
 *
 * @param bdaddr - Bluetooth address of the device for which key value has changed.
 *
 * @param bdaddr_type - Address type of the device for which key value has changed.
 *
 * @param id_bdaddr - Bluetooth identity address of the device for which key value has changed.
 *
 * @param id_bdaddr_type - Identity address type of the device for which key value has changed.
 *
 * @param keys - structure containing all the keys
 *
 */
typedef void (*bonding_info_cb_t)(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8* id_bdaddr, UINT8 id_bdaddr_type, struct __smp_bonding_key_t *keys);
/** @brief [Storage call back]Core stack calls this call back when group of keys are updated due to a bonding operation
 *
 * @typedef clear_key_cb_t - clearing the stored keys.
 *
 * @param bdaddr - Bluetooth address of the device for which key value has changed.
 *
 * @param bdaddr_type - Address type of the device fo rwhich key value has changed.
 *
 */
typedef void (*clear_key_cb_t)(trans_id_t trans_id,  UINT8* bdaddr, UINT8 bdaddr_type);
/** @brief list of call back pointers to be registered by application.
 *
 * @typedef gatt_callbacks_t
 */
typedef struct
{
	on_att_mtu_changed_cb_t						iLE_on_att_mtu_changed_cb;

	/* Client related call backs */
	on_primary_service_discovered_cb_t 		iLE_on_primary_service_discovered_cb;
	on_included_service_discovered_cb_t 	iLE_on_included_service_discovered_cb;
	on_characteristic_discovered_cb_t 		iLE_on_characteristic_discovered_cb;
	on_descriptor_discovered_cb_t 			iLE_on_descriptor_discovered_cb;
	on_attribute_read_cb_t 					iLE_on_attribute_read_cb;
	on_attribute_write_cb_t 				iLE_on_attribute_write_cb;
	on_notification_cb_t		 			iLE_on_notification_cb;
	on_notification_registered_cb_t 		iLE_on_notification_registered_cb;

	/* server related call backs */
	on_service_added_cb_t					iLE_on_service_added_cb;
	on_included_service_added_cb_t			iLE_on_include_service_added_cb;
	on_service_removed_cb_t					iLE_on_service_removed_cb;
	on_characteristic_added_cb_t			iLE_on_characteristic_added_cb;
	on_descriptor_added_cb_t				iLE_on_descriptor_added_cb;
	on_service_started_cb_t 				iLE_on_service_started_cb;
	on_attribute_read_req_cb_t 				iLE_on_attribute_read_req_cb;
	on_attribute_write_req_cb_t 			iLE_on_attribute_write_req_cb;
	on_indication_confirmation_cb_t 		iLE_on_indication_confirmation_cb;
} gatt_callbacks_t;

/** @brief list of device operation call back pointers to be registered by application.
 *
 * @typedef device_control_callbacks_t
 */
typedef struct
{
	stack_initialized_cb_t 			iLE_stack_initialized_cb;
	scan_result_cb_t 				iLE_scan_result_cb;
	scan_completed_cb_t 			iLE_scan_completed_cb;
	on_connected_cb_t				iLE_on_connected_cb;
	on_link_enc_changed_cb_t 		iLE_on_link_enc_changed_cb;
	bonding_complete_cb_t 			iLE_bonding_completed_cb;
	on_disconnected_cb_t			iLE_on_disconnected_cb;
	on_conn_param_update_cb_t		iLE_on_conn_param_update_cb;
#if (TEST_CODE==TRUE)
#if (LE_PING_ENABLE==TRUE)
	read_authpayload_timout_cb_t	iLE_read_authpayload_timeout_cb;
#endif //LE_PING_ENABLE
	vsc_evt_cb_t 				iLE_vsc_cb;
#endif //TEST_CODE
	data_len_change_evt_cb_t		iLE_data_len_change_evt_cb;
} device_control_callbacks_t;

/** @brief list of storage operation call back pointers to be registered by application.
 *
 * @typedef storage_callbacks_t
 */
typedef struct
{
	key_req_cb_t key_request_cb;
	key_update_cb_t key_update_cb;
	bonding_info_cb_t bonding_info_cb;
	clear_key_cb_t clear_key_cb;
}storage_callbacks_t;

/* Key types associated with the storage callbacks*/

#define LOCAL_IRK		0
#define PEER_IRK		1
#define SEC_INFO		2
#define LOCAL_LTK		3
#define PEER_LTK		4
#define LOCAL_CSRK		5
#define PEER_CSRK		6
#define LOCAL_COUNTER	7
#define PEER_COUNTER	8
#define BOND_INFO		9
#define CLEAR_KEY		10

/* Device link encryption states */
#define LINK_ENC_STATE_NONE			0
#define LINK_ENC_STATE_UPDATING		1
#define LINK_ENC_STATE_UPDATED		2
#define LINK_ENC_STATE_ENCRYPTING	3
#define LINK_ENC_STATE_ENCRYPTED	4

#define ATTRIBUTE_PROPERTY_READ						0x02
#define ATTRIBUTE_PROPERTY_WRITE_NO_RESPONSE		0x04
#define ATTRIBUTE_PROPERTY_WRITE					0x08
#define ATTRIBUTE_PROPERTY_NOTIFY					0x10
#define ATTRIBUTE_PROPERTY_INDICATE					0x20
#define ATTRIBUTE_PROPERTY_AUTH_SIGNED_WRITE		0x40
#define ATTRIBUTE_EXTENDED_PROPERTY					0x80

#define BIT(N)              (1<<N)
#define MIN_KEY_SIZE        (0x07)
#define READ_KEY_MASK      (0x00F0)
#define WRITE_KEY_MASK     (0xF000)

#define ATTRIBUTE_PERMISSION_READ                      BIT(0)
#define ATTRIBUTE_PERMISSION_READ_ENC_NO_MITM          BIT(1)
#define ATTRIBUTE_PERMISSION_READ_ENC_MITM             BIT(2)
#define ATTRIBUTE_PERMISSION_READ_AUTHOR               BIT(3)
#define ATTRIBUTE_PERMISSION_READ_KEY_SIZE(a)          ((a - MIN_KEY_SIZE + 1) << 4) /* In BIT(4,5,6,7) Nibble, key size 7 is 1 and key size 16 is 10 */

#define ATTRIBUTE_PERMISSION_WRITE                     BIT(8)
#define ATTRIBUTE_PERMISSION_WRITE_ENC_NO_MITM         BIT(9)
#define ATTRIBUTE_PERMISSION_WRITE_ENC_MITM            BIT(10)
#define ATTRIBUTE_PERMISSION_WRITE_AUTHOR              BIT(11)
#define ATTRIBUTE_PERMISSION_WRITE_KEY_SIZE(a)         ((a - MIN_KEY_SIZE + 1) << 12) /* In BIT(12,13,14,15) Nibble, key size 7 is 1 and key size 16 is 10 */

#define ATTRIBUTE_READ_PERMITTED	(ATTRIBUTE_PERMISSION_READ|ATTRIBUTE_PERMISSION_READ_ENC_NO_MITM|ATTRIBUTE_PERMISSION_READ_ENC_MITM)
#define ATTRIBUTE_WRITE_PERMITTED	(ATTRIBUTE_PERMISSION_WRITE|ATTRIBUTE_PERMISSION_WRITE_ENC_NO_MITM|ATTRIBUTE_PERMISSION_WRITE_ENC_MITM)

/* Helper MACROs to get READ/WRITE Key Size from (UINT16)permission attribute */
#define GET_READ_KEY_SIZE(PERM)		(((PERM & READ_KEY_MASK) >> 4) + MIN_KEY_SIZE - 1)
#define GET_WRITE_KEY_SIZE(PERM)	(((PERM & WRITE_KEY_MASK) >> 12) + MIN_KEY_SIZE - 1)

typedef struct
{
	UINT8 attr_type;
	UINT16 attr_handle;
	union
	{
		struct
		{
			UINT8 property;
			UINT16 permission;
		} char_desc_data;
		struct
		{
			trans_id_t owner_trans_id;
			UINT16 end_handle;
		} srv_data;
		struct
		{
			UINT16 start_handle;
			UINT16 end_handle;
		} inc_srv_data;
	} attr_data;
	uuid_t uuid;
} gatt_attribute_t;

typedef struct {
	UINT8 type;
	UINT8 data_length;
	UINT8 *data;
} gap_adv_scanresp_data_t;

typedef enum {
	DEVICE_DISCONNECTED,
	DEVICE_CONNECTING,
	DEVICE_CONNECTED
} autoconn_state_t;

typedef struct
{
	autoconn_state_t conn_state;
	UINT8 bond_idx;
	UINT8 idaddr[BD_ADDR_LEN];
	UINT8 idaddr_type;
	trans_id_t notify_list[MAX_NUMBER_OF_AUTO_CONNECT];
} autoconn_dev_t;

/** @brief Discovered Bluetooth device. */
typedef struct __discovered_device_t
{
	UINT8 addr_type; /**< address type for the remote device */
	UINT8 bdaddr[BD_ADDR_LEN]; /**< Bluetooth MAC address of the remote device */
	UINT8 direct_addr_type; /**< address type for InitA for Directed advertisement with RPA */
	UINT8 direct_addr[BD_ADDR_LEN]; /**< InitA for Directed advertisement with RPA */
	char localname[MAX_DEVICE_NAME_LEN + 1]; /**< local name of the remote device */
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
	INT8 rssi; /**< RSSI value reported in the advertisement report */
	UINT8 tx_power; /**< Tx power value reported in the advertisement report */
	UINT16 appearance; /**< appearance reported in the advertisement report */
	UINT8 role_supported; /**< Bit map of which role is supported by this remote device */
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */
	UINT8 flags; /**< Discoverability type and BREDR/LE support */
	UINT8 event_type;
	UINT8 adv_data_len; /**< Length of advertisement data */
	UINT8* adv_data; /**< Raw advertisement data */
} discovered_device_t;

typedef struct
{
	BOOLEAN adv_use_whitelist;
	BOOLEAN adv_is_background;
	BOOLEAN scan_isactive;
	BOOLEAN scan_is_limited;
	BOOLEAN scan_use_whitelist;
	BOOLEAN scan_is_background;
	BOOLEAN user_scan_in_progress;
	BOOLEAN idle_scan_in_progress;
	BOOLEAN adv_scanresp_data_changed;
	BOOLEAN busy;
	UINT8 adapter_state;
	UINT8 enable_req_app_idx;
	trans_id_t scan_req_trans_id;
	UINT8 prev_adapter_state;
	UINT8 adv_type;
	UINT8 adv_flags;
	UINT8 adv_addr_type;
	UINT8 remote_op_device;
	UINT16 adv_int_min;
	UINT16 adv_int_max;
	UINT16 scan_int;
	UINT16 scan_win;
	UINT32 scan_timeout_msec;
	UINT32 adv_timeout_msec;
	osa_timer_t adv_timer;
	osa_timer_t scan_timer;
	osa_timer_t scan_res_timer;
	osa_timer_t rpa_gen_timer;
	queue_internal_t pending_req_q;
	UINT8 adv_remote_bd_addr[BD_ADDR_LEN];
	UINT16 scan_filter_uuids[MAX_NUM_SCAN_FILTER_UUIDS];
#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
	gap_adv_scanresp_data_t *adv_data[MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES];
	gap_adv_scanresp_data_t *scanresp_data[MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES];
#endif
	UINT8 operation_list[GAP_MAX_NUM_OPERATIONS];
	autoconn_dev_t *autoconn_dev[MAX_NUM_CONNECTED_DEVICE];
#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
	discovered_device_t discovered_device;
#endif
	/* Controller supported maximum values of tx/rx data length and time */
	UINT16 max_tx_octets;
	UINT16 max_tx_time;
} gap_device_data_t;

typedef struct
{
	trans_id_t trans_id;
	UINT8 pm_operation;
	UINT8 connected_device_idx;
	void *additional_param;
} pm_transactions_elem_t;

typedef struct
{
	trans_id_t trans_id;
	UINT16 att_id;
} reg_notify_t;

typedef struct
{
	BOOLEAN init_done;
	UINT8 pm_state;
	reg_notify_t reg_notify_list[MAX_NUM_REG_NOTIFY_CHAR];
	queue_internal_t pending_req_q;
} pm_device_data_t;

typedef struct
{
	UINT16 handle;
	buffer_t* buffer;
} read_multiple_chars_value_t;

typedef struct
{
	/* GATT global data */
	/* GATT server data */
	buffer_t *saved_buffer;
	UINT8 saved_multi_read_no_of_handle;
	ll_node_t* saved_multi_read_handle_list;
	UINT16 prep_wr_att_id;
	UINT16 indication_att_id;

	/* GATT client data */
	UINT8 on_going_proc;
	UINT16 saved_handle;
	uuid_t uuid_discover;
} gatt_device_data_t;

typedef struct
{
	queue_internal_t pending_req_q;
	UINT8 prepared_wr_app_handle;
} sm_device_data_t;

/* ATT device information */
typedef struct _att_device_info_t
{
	osa_timer_t att_client_timer_id;
	osa_timer_t att_server_timer_id;
	UINT8 server_att_state;
	UINT8 client_att_state;
	UINT16 att_mtu_size;
	UINT16 att_request_mtu_size;
	BOOLEAN mtu_exchange_done;
}att_device_t;

typedef struct
{
	buffer_t *l2cap_data;
	UINT16 cid;
} l2cap_data_seg_t;

typedef struct
{
#define LINK_ENC_PENDING 		(0x01)
#define LINK_PAIR_PENDING		(0x02)
#define LINK_SEC_REQ_PENDING	(0x04)
#define LINK_SIGN_PENDING		(0x08)
#define LINK_VERIFY_PENDING		(0x10)
#define LINK_ATT_PENDING		(0x20)
	BOOLEAN valid;
	UINT8 state;
	UINT8 secuirty_level;
	UINT8 key_size;
	UINT8 key_type;
	UINT8 keys_distributed;
	UINT8 pending_act;
	UINT8 enc_state;
}smp_enc_state_t;

typedef struct
{
	UINT8 ltk[16];
	UINT8 rand[8];
	UINT16 ediv;
}enc_info_t;
typedef struct
{
	UINT8 irk[16];
	UINT8 id_addr[BD_ADDR_LEN];
	UINT8 id_addr_type;
}identity_info_t;

typedef struct
{
	UINT8 csrk[16];
	UINT32 counter;
}signing_info_t;

typedef struct
{
	UINT8 security_level;
	UINT8 keys_distributed;
	UINT8 key_size;
	UINT8 key_type;
}sec_info_t;

typedef struct
{
	identity_info_t peer_id_info;
	UINT8 local_irk[16];
}resolving_list_entry_t;

typedef struct
{
	resolving_list_entry_t entry;
	BOOLEAN valid;
	BOOLEAN car_supported;
}resolving_list_t;

typedef struct
{
	UINT8 bdaddr[BD_ADDR_LEN];
	UINT8 type;
}bd_addr_t;

typedef struct
{
	signing_info_t sign_key;
	BOOLEAN valid;
}signing_key_t;

#if (L2CAP_COC == TRUE)
#define MAX_NUM_OF_REGISTERED_PSM			10
#define L2CAP_COC_MIN_MTU 					23
#define L2CAP_COC_MAX_MTU 					35
#define MAX_NUMBER_OF_L2CAP_COC_TX_BUFFER 	2
#define L2CAP_COC_INITIAL_CREDITS			1

typedef struct
{
	UINT8 handle;
	UINT16 r_cid;
	UINT16 r_mtu;
	UINT16 r_mps;
	UINT16 r_initial_credits;
	INT8 result;
} l2cap_coc_conn_req_res_t;

typedef void (*on_lc_conn_complete_cb_t)(INT8 status, l2cap_coc_conn_req_res_t* p_res);
typedef void (*on_lc_disconn_complete_cb_t)(INT8 status, UINT8 handle);
typedef void (*on_lc_conn_notify_cb_t)(INT8 status, l2cap_coc_conn_req_res_t* p_res);
typedef void (*on_lc_disconn_notify_cb_t)(INT8 status, UINT8 handle);
typedef void (*on_lc_data_notify_cb_t)(INT8 status, UINT8 handle, UINT8* buffer, UINT16 buffer_len);
typedef void (*on_lc_credit_notify_cb_t)(INT8 status, UINT8 handle, UINT16 fc_credit);
typedef void (*on_lc_stack_busy_notify_cb_t)(INT8 status, UINT8 handle, BOOLEAN stack_busy);

typedef void (*lc_register_cb)(trans_id_t trans_id, UINT16 psm, INT8 status);
typedef void (*lc_authorisation_cb)(trans_id_t trans_id, UINT8 conn_id, UINT16 psm); // add coc configuration
typedef void (*lc_connection_cmpl_cb)(trans_id_t trans_id, UINT8 conn_id, UINT16 psm, UINT8 coc_handle, UINT16 r_mtu, UINT8 initial_credit, INT8 status);
typedef void (*lc_flow_control_cb)(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle, UINT8 fc_packets);
typedef void (*lc_recv_data_cb)(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle, UINT8 *buffer, UINT16 buffer_len);
typedef void (*lc_disconnection_cmpl_cb)(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle, UINT8 status);

typedef struct
{
	lc_register_cb 				register_cb;
	lc_authorisation_cb			authorisation_cb; /* TODO: Implement */
	lc_connection_cmpl_cb		connection_cmpl_cb;
	lc_flow_control_cb			flow_control_cb; /* TODO: Implement */
	lc_recv_data_cb				recv_data_cb;
	lc_disconnection_cmpl_cb	disconnect_cmpl_cb;
}l2cap_coc_callbacks_t;

typedef struct
{
	BOOLEAN connected;
	BOOLEAN auth_req;
	trans_id_t owner_trans_id;
	UINT16 psm;
	UINT16 mtu;
	l2cap_coc_callbacks_t *l2cap_coc_cb;
} l2cap_coc_app_psm_t;

typedef struct
{
	UINT8 flag_pkt_type;
	UINT16 length;
	UINT16 offset;
	UINT8 data[L2CAP_COC_MAX_MTU + 2]; //2 bytes for SDU length
} l2cap_coc_conn_recv_data_t;

typedef struct
{
	UINT16 length;
	UINT16 offset;
	UINT8 data[L2CAP_COC_MAX_MTU + 2]; //2 bytes for SDU length
}l2cap_coc_conn_send_data_t;

typedef struct
{
	UINT8 state;
	UINT8 le_conn_id;
	UINT8 l2cap_identifier;
	UINT8 tx_usage_count;
	UINT16 cid; // Other than fixed channels 4,5 & 6. Note: App refers it as handle.
	UINT16 mtu;
	UINT16 mps;
	UINT16 credits;
	UINT16 psm;
	UINT16 r_cid; // Other than fixed channels 4,5 & 6. Note: App refers it as handle. r_ means remote.
	UINT16 r_mtu;
	UINT16 r_mps;
	UINT16 r_credits;
	trans_id_t owner_trans_id;
	l2cap_coc_callbacks_t *l2cap_coc_cb;
	l2cap_coc_conn_recv_data_t coc_recv_data_pool;
	queue_internal_t coc_data_tx_q; /**< data transmission queue */
} l2cap_coc_conn_t;

#endif // L2CAP_COC
typedef struct
{
	UINT8 opcode;
	buffer_t *in_buffer;
}att_pending_packet_t;

/** @brief Connected Bluetooth device */
typedef struct __connected_device_t
{
	UINT8 idx; /**< array index at which this connected device resides. */
	//UINT8 addr_type; /**< address type for the remote device */ /* TODO: WHERE IS IT USED & REMOVE IT*/
	UINT8 bdaddr[BD_ADDR_LEN]; /**< Bluetooth MAC address of the remote device */
	UINT8 ota_bdaddr[BD_ADDR_LEN];
	UINT8 local_bdaddr[BD_ADDR_LEN];
	UINT8 bdaddr_type;
	UINT8 local_addr_type;
	bd_addr_t id_addr;
	UINT8 ble_remote_features[8]; /**< Remote used features */
	UINT16 acl_handle; /**< ACL connection handle for this device */
	UINT16 conn_interval; /**< connection interval for this connection */
	UINT16 conn_latency; /**< connection latency for this connection */
#if (GAP_EXTRA_REMOTE_DATA == TRUE)
	UINT16 sup_timeout; /**< supervision timeout for this connection */
	UINT8 clock_accuracy; /**< clock accuracy parameter for this connection */
#endif /* GAP_EXTRA_REMOTE_DATA == TRUE */
	BOOLEAN local_link_role; /**< Master:0 / Slave:1 */
	/* Internal data */
	BOOLEAN usage_map[MAX_NUMBER_OF_APP]; /**< Bitmap of applications that are communicating with this device */
	BOOLEAN l2cap_ongoing_partial_segment_rx;
	l2cap_data_seg_t data_rx_pkt;
	UINT8 l2cap_state; /**< l2cap state */
	UINT8 l2cap_cur_id; /**< current id of the control frame in l2cap */
	UINT8 num_un_acked_l2cap_pkts;
	UINT8 gap_connection_state;
	BOOLEAN is_bonded;
	UINT8 bonded_idx;
#if (CONTROLLER_PRIVACY)
	UINT8 car_supported; /* Central address resolution support */
#endif /* CONTROLLER_PRIVACY */
	osa_timer_t gap_remote_command_timer;
	BOOLEAN remote_command_timer_created;
	att_device_t att_device;
	gatt_device_data_t gatt_device_data;
	sm_device_data_t sm_device_data;
#if (SMP_FEATURE)
	smp_enc_state_t link_enc_state;
	att_pending_packet_t pending_att_packet;
	signing_key_t peer_sign_info;
	signing_key_t local_sign_info;
#endif /* SMP_FEATURE */
	/* Profile Manager per device global data */
	pm_device_data_t pm_device_data; /**< profile manager data */
} connected_device_t;
typedef connected_device_t os_retentionConnHostInfo_t;

typedef struct
{
	UINT8 idx;
	UINT8 conn_used[MAX_NUM_CONNECTED_DEVICE];
	UINT8 num_conn_used;
	gatt_callbacks_t *app_gatt_cb;
	device_control_callbacks_t *app_device_control_cb;
#if (L2CAP_COC == TRUE)
	l2cap_coc_callbacks_t *l2cap_coc_cb;
#endif
} app_data_t;

/* Structure for each element in the command store q */
typedef struct
{
	UINT16 opcode;
	osa_timer_t timer_id;
	BOOLEAN timer_created;
} hci_cmd_store_q_elem_t;

/* Structure for each element in the command TX q */
typedef struct
{
	UINT16 opcode;
	UINT16 buf_len;
	UINT8* p_buf;
} hci_cmd_tx_q_elem_t;

/* Credit  is decreased if a pkt is sent to controller.
 * And gets set by the num_of_packtes received with
 * command complete and command status
 */
typedef struct
{
	UINT8 hci_credit;
	UINT16 pending_opcode;
	osa_timer_t hci_cmd_timer;
	BOOLEAN timer_active;
} hci_data_t;

/* SMP control block */

/* Sig specified security levels for mode 1 */
#define SMP_SEC_LVL_1 	0
#define SMP_SEC_LVL_2	1
#define SMP_SEC_LVL_3	2
#define SMP_SEC_LVL_4	3

#define SMP_MAX_KEY_LEN 	16
#define SMP_PAIRING_CMD_LEN 7
#define SMP_PUB_KEY_LEN		64
#define SMP_PUB_KEY_COORDINATE_LEN	32
#define SMP_PRIVATE_KEY_LEN	32
#define SMP_DHKEY_LEN		32
#define SMP_CMAC_LEN		16
#define SMP_LTK_RAND_LEN	8
#define SMP_F5_DATA_LEN		53
#define SMP_F6_DATA_LEN		65
#define SMP_LTK_DISTRIBUTED  (1 << 0)
#define SMP_IRK_DISTRIBUTED  (1 << 1)
#define SMP_CSRK_DISTRIBUTED (1 << 2)
#define SMP_LTK_RECEIVED	 (1 << 4)
#define SMP_IRK_RECEIVED	 (1 << 5)
#define SMP_CSRK_RECEIVED	 (1 << 6)

typedef struct __smp_bonding_key_t
{
/* General security and key info*/
	UINT8 security_level;
	UINT8 keys_distributed;
	UINT8 key_size;
	UINT8 key_type;
/* Encryption Info */
	UINT8 peer_ltk[SMP_MAX_KEY_LEN];
	UINT8 peer_rand[SMP_LTK_RAND_LEN];
	UINT16 peer_ediv;
	UINT8 local_ltk[SMP_MAX_KEY_LEN];
	UINT8 local_rand[SMP_LTK_RAND_LEN];
	UINT16 local_ediv;
/* Identity Info*/
#if (PRIVACY_FEATURE)
	UINT8 peer_irk[SMP_MAX_KEY_LEN];
	UINT8 id_bdaddr[BD_ADDR_LEN];
	UINT8 id_addr_type;
	UINT8 local_irk[SMP_MAX_KEY_LEN];
#endif /* PRIVACY_FEATURE */
/* Signing Info*/
#if (SIGNED_WRITE)
	UINT8  peer_csrk[SMP_MAX_KEY_LEN];
	UINT8 local_csrk[SMP_MAX_KEY_LEN];
#endif /* SIGNED_WRITE */
}smp_bonding_key_t;

typedef struct{
	UINT8 bdaddr[BD_ADDR_LEN];
	UINT8 operation;
	UINT8 remote_initiated;
	UINT8 conn_id;
	UINT8 state;
	UINT8 event;
	UINT8 status;
	UINT8 local_auth_level_min;
	UINT8 local_auth_req;
	UINT8 peer_auth_req;
	UINT8 local_init_key;
	UINT8 local_resp_key;
	UINT8 peer_init_key;
	UINT8 peer_resp_key;
	UINT8 local_oob_flag;
	UINT8 peer_oob_flag;
	UINT8 local_io_cap;
	UINT8 peer_io_cap;
	UINT8 local_enc_key_size_min;
	UINT8 local_enc_key_size;
	UINT8 peer_enc_key_size;
	UINT8 asso_model;
	UINT8 pairing_method;
	UINT8 idx;
#if (PRIVACY_FEATURE)
	UINT8 rpa[BD_ADDR_LEN];
#endif /* PRIVACY_FEATURE */
	UINT8 pairing_req[SMP_PAIRING_CMD_LEN];
	UINT8 pairing_rsp[SMP_PAIRING_CMD_LEN];
	UINT8 tk[SMP_MAX_KEY_LEN];
	UINT8 peer_confirm[SMP_MAX_KEY_LEN];
	UINT8 local_confirm[SMP_MAX_KEY_LEN];
	UINT8 local_rand[SMP_MAX_KEY_LEN];
	UINT8 peer_rand[SMP_MAX_KEY_LEN];
	UINT8 cur_rand[SMP_MAX_KEY_LEN];
	UINT8 stk[SMP_MAX_KEY_LEN];
#if (AES_CMAC)
	UINT8 cmac_key[SMP_MAX_KEY_LEN];
	UINT8 k1[SMP_MAX_KEY_LEN];
	UINT8 k2[SMP_MAX_KEY_LEN];
	UINT8* cmac_data;
	UINT16 length_of_data;
	UINT8 no_of_blocks;
	UINT8 cur_block;
	BOOLEAN complete_block;
	BOOLEAN sign_gen;
#endif /* AES_CMAC */
#if (SIGNED_WRITE)
	UINT8* data_to_be_verified;
#endif /* SIGNED_WRITE*/
#if (SECURE_CONNECTION)
	UINT8 peer_p256_key_x[SMP_PUB_KEY_COORDINATE_LEN];
	UINT8 peer_p256_key_y[SMP_PUB_KEY_COORDINATE_LEN];
	UINT8 dhkey[SMP_DHKEY_LEN];
	UINT8 key_bit_sent;
	UINT8 f5_t[SMP_MAX_KEY_LEN];
	UINT8 mackey[SMP_MAX_KEY_LEN];
	UINT8 f5_data[SMP_F5_DATA_LEN];
#endif /* SECURE_CONNECTION */
	UINT8 enc_stage;
	BOOLEAN enc_with_ltk;
	smp_bonding_key_t cur_key;
}smp_cb_t;

typedef struct
{
	smp_cb_t smp_cur_cb;
	BOOLEAN sc_support;
#if (PRIVACY_FEATURE)
	UINT8 device_irk[SMP_MAX_KEY_LEN];
#endif /* PRIVACY_FEATURE */
#if (SECURE_CONNECTION)
	UINT8 local_p256_key_x[SMP_PUB_KEY_COORDINATE_LEN];
	UINT8 local_p256_key_y[SMP_PUB_KEY_COORDINATE_LEN];
	UINT8 local_p256_private_key[SMP_PRIVATE_KEY_LEN];
#endif /* SECURE_CONNECTION */
	osa_timer_t smp_cmd_timer_id;
	osa_timer_static_t SMP_CMD_TIMER[1];
	osa_timer_isr_list_t SMP_CMD_TIMER_ISR[1];
	osa_timer_t smp_app_timer_id;
	osa_timer_static_t SMP_APP_TIMER[1];
	osa_timer_isr_list_t SMP_APP_TIMER_ISR[1];

}smp_data_t;


typedef void (*smp_app_cb_t)(trans_id_t trans_id, UINT8* bdaddr, UINT8 bdaddr_type, UINT8 event,  UINT8 length, UINT8* data);

typedef struct
{
	storage_callbacks_t *storage_cb;
	trans_id_t trans_id;
	BOOLEAN registered;
}storage_mgr_t;



typedef struct
{
#define SMP_KEY_TYPE_UNAUTHENTICATED	0
#define SMP_KEY_TYPE_AUTHENTICATED		1
#define SMP_KEY_TYPE_SC_UNAUTHENTICATED	2
#define SMP_KEY_TYPE_SC_AUTHENTICATED	3

	bonding_complete_cb_t smp_bonding_complete_cb;
	smp_app_cb_t	smp_app_cback;
#if (SIGNED_WRITE)
	data_siging_complete_cb_t smp_data_siging_complete_cb;
	sign_verify_complete_cb_t smp_sign_verify_complete_cb;
#endif /* SIGNED_WRITE */
#if (PRIVACY_FEATURE)
	rpa_complete_cb_t smp_rpa_res_complete_cb;
#endif /* PRIVACY_FEATURE */
#if ( INTERNAL_AES == TRUE )
	osa_timer_t aes_timer_id;
	osa_timer_static_t AES_TIMER[1];
	osa_timer_isr_list_t AES_TIMER_ISR[1];
#endif /* INTERNAL_AES == TRUE */
	queue_internal_t pending_req_q;
	BOOLEAN busy;
/* Storage manager */
	storage_mgr_t storage_mgr;
}smp_mgr_data_t;

/** @brief Stores local adapter information */
typedef struct
{
	osa_mutex_t fw_init_mutex;
	char *uart_port_name; /**< port name for the tty */
	/* States */
	UINT8 adapter_state;
#define ADAPTER_STATE_DISABLED	0
#define ADAPTER_STATE_ENABLING	1
#define ADAPTER_STATE_ENABLED	2
#define ADAPTER_STATE_DISABLING	3

	/* Informational parameters */
	UINT8 static_bdaddr[BD_ADDR_LEN]; /* Public */
	UINT8 bdaddr[BD_ADDR_LEN]; /* Random */
	UINT8 local_features[8];
	UINT8 ble_local_features[8];
	UINT16 buffer_size;
	UINT16 timer_id;
	UINT8 num_of_buffer;
	UINT8 whitelist_size;
	UINT8 num_whitelist_entries;
#if (PRIVACY_FEATURE == TRUE)
	UINT8 privacy_enabled;
#endif
#if (CONTROLLER_PRIVACY)
	UINT8 resolvinglist_size;
	UINT8 num_resolvinglist_entries;
	UINT8 cur_rpa_list_size;
#endif /* CONTROLLER_PRIVACY */
#if (HOST_PRIVACY)
	resolving_list_t resolving_list[HOST_RESOLVING_LIST_SIZE];
#endif /* HOST_PRIVACY */
	UINT8 local_name[MAX_LOCAL_NAME_LEN];
	UINT16 data_window;
	UINT8 addr_type;
	UINT16 local_att_mtu_size;
	gap_device_data_t gap_data;
	UINT8 l2cap_next_device_idx;
	connected_device_t *connected_device[MAX_NUM_CONNECTED_DEVICE];
#if (L2CAP_COC == TRUE)
	l2cap_coc_conn_t *l2cap_coc_channel_tbl[MAX_NUMBER_OF_L2CAP_COC_CHNL];
#endif // L2CAP_COC
	gatt_attribute_t attribute_list[MAX_NUM_ATTR];
	UINT16 next_free_handle, last_attr_idx, last_srv_end_handle;

	pm_transactions_elem_t *pm_transac_list[MAX_NUMBER_OF_PM_REQ];
	UINT8 pm_device_idx_to_execute;
	UINT8 sm_device_idx_to_execute;

	app_data_t* app_list[MAX_NUMBER_OF_APP];
	queue_t interface_req_q;
	queue_t timer_expire_q;
	hci_data_t hci_data;
#if (SMP_FEATURE)
	smp_data_t smp_data;
	smp_mgr_data_t smp_mgr_data;
#endif /* SMP_FEATURE */
#if (L2CAP_COC == TRUE)
	l2cap_coc_app_psm_t l2cap_registered_psm_tbl[MAX_NUM_OF_REGISTERED_PSM];
#endif // L2CAP_COC
#if (TARGET_UEFI == TRUE)
    BOOLEAN thread_busy;
    BOOLEAN is_sync_event;
#endif
	reten_connection_info_t reten_conn_info;
/* Add more fields to store data about local adapter */
} adapter_t;

extern adapter_t g_local_adapter;

#if (BLE_USE_FWINFO_FUNC_CALL == TRUE)

typedef struct
{
	UINT8 bdaddr[BD_ADDR_LEN];
	UINT8 local_features[8];
	UINT8 ble_local_features[8];
	UINT16 le_buffer_size;
	UINT8 num_of_buffer;
	UINT8 le_whitelist_size;
}ble_controller_info_t;

typedef struct
{
	UINT8 event_mask[8];
	UINT8 ble_event_mask[8];
}ble_controller_event_mask_t;

typedef struct
{
	UINT8 bdaddr[BD_ADDR_LEN];
	UINT8 addr_type;
	UINT8 direct_addr_type;
	UINT8 adv_type;
	UINT8 ch_map;
	UINT8 filter_policy;
	UINT16 adv_int_min;
	UINT16 adv_int_max;
}ble_adv_params_t;


typedef struct
{
	UINT8 datalen;
	UINT8 *data;
}bt_tlv_data_t;

extern UINT8 hci_read_bt_controller_info(ble_controller_info_t *controller_info);
extern UINT8 hci_write_bt_controller_info(ble_controller_event_mask_t *event_mask);
extern UINT8 hci_write_bt_controller_adv_params( ble_adv_params_t *adv_params);
extern UINT8 hci_write_bt_controller_adv_data(bt_tlv_data_t *tlv_data);
extern UINT8 hci_write_bt_controller_scan_resp_data(bt_tlv_data_t *tlv_data);


#endif //BLE_USE_FWINFO_FUNC_CALL

/* Device Utility functions */

connected_device_t* create_connected_device(void);
void delete_connected_device(UINT8 connected_device_list_idx);
void clear_connected_device_list(void);
UINT8 get_connected_device_idx_by_handle(UINT16 acl_handle);
UINT8 get_connected_device_idx_by_bdaddr(UINT8 *bdaddr);
connected_device_t *get_connected_device_by_bdaddr(UINT8 *bdaddr);
connected_device_t *get_connected_device_by_id_addr(UINT8 *bdaddr);
connected_device_t *get_connected_device_by_conn_id(UINT8 conn_id);
BOOLEAN is_device_connected(UINT8 *bdaddr);
UINT8 find_first_free_connected_device_slot(void);

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)
UINT8 find_adv_scanresp_data_idx(gap_adv_scanresp_data_t **list, UINT8 type);
UINT8 find_first_free_adv_scanresp_data_slot(gap_adv_scanresp_data_t **list);
#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

UINT8 get_idx_from_autoconn_list(UINT8 *bdaddr);

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)
INT8 add_trans_id_to_auto_connect_list(autoconn_dev_t *device, trans_id_t trans_id);
INT8 remove_trans_id_from_auto_connect_list(autoconn_dev_t *device, trans_id_t trans_id);
void add_to_autoconn_list(UINT8 *bdaddr, UINT8 addr_type, trans_id_t trans_id);
void update_autoconn_list(UINT8 *bdaddr, UINT8 app_handle);
BOOLEAN is_in_autoconn_list(UINT8 *bdaddr);
void remove_from_autoconn_list(UINT8 *bdaddr, trans_id_t trans_id);
BOOLEAN is_autoconn_list_empty();
#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */
#if (L2CAP_COC == TRUE)
l2cap_coc_conn_t* create_l2cap_coc_tbl(void);
void delete_l2cap_coc_tbl(UINT8 l2cap_coc_tbl_idx);
void clear_l2cap_coc_tbl(void);
UINT8 find_first_free_l2cap_coc_tbl_slot(void);
UINT8 get_free_psm_registration_slot();
l2cap_coc_conn_t* get_l2cap_coc_tbl_from_idx(UINT8 ccb_idx);
UINT8 get_coc_ccb_by_l2cap_id(UINT8 conn_id,UINT8 l2cap_id);
UINT16 get_rcid_for_cid(UINT16 cid);
UINT16 get_cid_for_rcid(UINT16 rcid, UINT8 le_conn_id);
UINT8 get_psm_registration_idx(UINT16 psm);
UINT8 check_psm_already_in_use(UINT16 psm, UINT8 conn_id);
UINT8 get_handle_from_coc_table_for_cid(UINT16 cid);
UINT8 get_handle_from_coc_table_for_cids(UINT16 cid, UINT16 r_cid);
l2cap_coc_conn_send_data_t* get_free_coc_tx_data_pool(UINT8 ccb_idx);
BOOLEAN is_psm_valid(UINT16 psm);
#endif
UINT8 increament_l2cap_identifier(UINT8 identifier);

#endif /* DEVICE_STRUCT_H_ */
