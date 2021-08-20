/** @file
  Interface header to be used by apps.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "device_struct.h"
#include "config_host.h"
#include "smp_mgr.h"

typedef void (handler_func)(UINT8 *arg);
typedef struct
{
	const char *cmd_str;
	handler_func *handler;
} cmd_t;

typedef struct
{
	const cmd_t* cmd_arr;
	char app_prefix[MAX_APP_PREFIX_LENGTH];
} app_cmd_list_t;

extern app_cmd_list_t app_cmd_list[MAX_NUMBER_OF_APP];

/*********************************************************************
 *				INTERFACE APIs
 *********************************************************************/

INT8 iLE_stack_init();

void iLE_stack_cleanup();

/** @brief Application calls this function to register with core stack.
 *
 * Function: iLE_register_application
 * 			 Application will receive a application handle as a result of
 * 			 successful registration. Application should save the handle
 * 			 and pass the same value to the core stack whenever calling
 * 			 core stack api in future. Application handle is valid until
 * 			 application calls de-register or application gets de-registered
 * 			 by any other means. In case of de-registration application needs
 * 			 to register again by calling this api.
 *
 * @param dev_cb - Call backs for adapter enable / disable and scan / discoverable
 * @param gatt_cb - Call backs for GATT operations
 * @param prefix - App command prefix string
 * @param cmd_arr - App command handlers
 * @param register_application_cb - this function will be called after registration
 * 										with app_handle for this application.
 * @return Error code.
 */
INT8 iLE_register_application(device_control_callbacks_t* dev_cb, gatt_callbacks_t* gatt_cb, const char *prefix, const cmd_t* cmd_arr, register_application_cb_t register_application_cb);

/** @brief Application calls this function to de-register from core stack.
 *
 * Function: iLE_deregister_application
 * 			 Application de-registers itself from the core stack. If this application
 * 			 requested connection to any remote device previously then that device
 * 			 may be disconnected depending on if other application(s) use the same device.
 * 			 This would stop all the GATT services registered by this application if any.
 * 			 This call ends the validity of app_handle. Thus, the application should
 * 			 register again if it wants to be useful in future.
 *
 * @param app_handle - Handle of the application.
 * @return Error code.
 */
INT8 iLE_deregister_application(UINT8 app_handle);

#if (GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

/** @brief Requests core stack to set advertisement data
 *
 * Function: iLE_set_advertisement_data
 *			 This requests the core stack to set advertisement data. Advertisement
 *			 type can be found in device_struct.h. Please refer to core spec to
 *			 set the advertisement data. This data will be broadcasted with the
 *			 advertisement packet by this device. Application is responsible to
 *			 start advertisement and advertisement wouldn't be started as a result
 *			 of this call.
 *
 * @param app_handle - Handle of the application.
 * @param length - length of the data to be set
 * @param type - Type of the advertisement data
 * @param data - data buffer of the advertisement data
 * @return Error code.
 */
INT8 iLE_set_advertisement_data(trans_id_t trans_id, UINT8 length, UINT8 type, UINT8 *data);

/** @brief Requests core stack to remove advertisement data
 *
 * Function: iLE_remove_advertisment_data
 *
 * @param app_handle - Handle of the application.
 * @param length - length of the data to be removed
 * @param type - Type of the advertisement data
 * @param data - data buffer of the advertisement data
 * @return Error code.
 */
INT8 iLE_remove_advertisment_data(trans_id_t trans_id, UINT8 length, UINT8 type, UINT8 *data);

/** @brief Requests core stack to set scan response data
 *
 * Function: iLE_set_scan_response_data
 *			 This requests the core stack to set advertisement data. Advertisement
 *			 type can be found in device_struct.h. Please refer to core spec to
 *			 set the advertisement data. This data will be broadcasted with the
 *			 advertisement packet by this device. Application is responsible to
 *			 start advertisement and advertisement wouldn't be started as a result
 *			 of this call.
 *
 * @param app_handle - Handle of the application.
 * @param length - length of the data to be set
 * @param type - Type of the scan response data
 * @param data - data buffer of the scan response data
 * @return Error code.
 */
INT8 iLE_set_scan_response_data(UINT8 app_handle, UINT8 length, UINT8 type, UINT8 *data);

/** @brief Requests core stack to remove scan response data
 *
 * Function: iLE_remove_scan_response_data
 *
 * @param app_handle - Handle of the application.
 * @param length - length of the data to be removed
 * @param type - Type of the scan response data
 * @param data - data buffer of the scan response data
 * @return Error code.
 */
INT8 iLE_remove_scan_response_data(UINT8 app_handle, UINT8 length, UINT8 type, UINT8 *data);

/** @brief Requests core stack to make this device discoverable
 *
 * Function: iLE_start_discoverable
 *			 This function will make the bluetooth controller discoverable if not
 *			 discoverable before. It will use the advertisement data as set by
 *			 set_advertisement_data api by applications. Application only has
 *			 control over advertisement data and advertisement timeout for specifying
 *			 limited disverability or general discoverability. Other configuration
 *			 values are decided by core stack module.
 *
 * @param app_handle - Handle of the application.
 * @param timeout_msec - Timeout for stopping discoverable. If passed 0 then it is
 * 						never timeout.
 * @param type - Type of the advertisement.
 * @param flags - Advertisement flags.
 * @param remote_bd_addr - Remote BD address for directed advertisement.
 * @param addr_type - Address type for directed advertisement.
 * @param use_whitelist - Set if whitelist is to be used for filtering.
 * @param background - Set if low frequency advertising is to be done (for power saving)
 * @return Error code.
 */
INT8 iLE_start_discoverable(trans_id_t trans_id, UINT32 timeout_msec, UINT8 type, UINT8 flags, UINT8 *remote_bd_addr, UINT8 addr_type, BOOLEAN use_whitelist, BOOLEAN background);

/** @brief Requests core stack to make this device discoverable
 *
 * Function: iLE_start_discoverable
 *			 This function will make the bluetooth controller discoverable if not
 *			 discoverable before. It will use the advertisement data as set by
 *			 set_advertisement_data api by applications. Application only has
 *			 control over advertisement data and advertisement timeout for specifying
 *			 limited disverability or general discoverability. Other configuration
 *			 values are decided by core stack module.
 *
 * @param app_handle - Handle of the application.
 * @param timeout_msec - Timeout for stopping discoverable. If passed 0 then it is
 * 						never timeout.
 * @param type - Type of the advertisement.
 * @param flags - Advertisement flags.
 * @param remote_bd_addr - Remote BD address for directed advertisement.
 * @param addr_type - Address type for directed advertisement.
 * @param adv_int_min - Minimum advertising interval.
 * @param adv_int_max - Maximum advertising interval.
 * @param use_whitelist - Set if whitelist is to be used for filtering.
 * @return Error code.
 */
INT8 iLE_start_discoverable_ex(trans_id_t trans_id, UINT32 timeout_msec, UINT8 type, UINT8 flags, UINT8 *remote_bd_addr, UINT8 addr_type, UINT16 adv_int_min, UINT16 adv_int_max, BOOLEAN use_whitelist);

/** @brief Requests core stack to stop this device to be discoverable
 *
 * Function: iLE_stop_discoverable
 *			 This function will stop the device from broadcasting advertisement
 *			 packets. So after this no other device can find this device in there
 *			 scan list.
 *
 * @param app_handle - Handle of the application.
 * @return Error code.
 */
INT8 iLE_stop_discoverable(trans_id_t trans_id);

#endif /* GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

/** @brief Requests core stack to change the local device name
 *
 * Function: iLE_set_local_device_name
 *			 This api allows the application to change the local name of this
 *			 device. This will update the device name field in advertisement data.
 *			 Thus the name would be reflected when this device is made discoverable
 *			 next time.
 *
 * @param app_handle - Handle of the application.
 * @param name - new name of this device.
 * @param len - length of the name in bytes. [This param will be deleted soon]
 * @return Error code.
 */
INT8 iLE_set_local_device_name(trans_id_t trans_id, UINT8 len, UINT8* name);

/** @brief Requests core stack for the local device name
 *
 * Function: iLE_get_local_device_name
 *			 This api allows the application to get the local name of this
 *			 device.
 *
 * @param app_handle - Handle of the application.
 * @param name - name of this device.
 * @return Length of the name.
 */


UINT8 iLE_get_local_device_name(trans_id_t trans_id, UINT8* name);

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

/** @brief Requests core stack to start scanning.
 *
 * Function: iLE_start_scan
 *			 This function will start scanning procedure to discover nearby
 *			 LE devices. It will set hard-coded value for scanning parameters.
 *			 Application can only set scan timeout (after this many seconds this
 *			 device will stop searching for devices.
 *			 Application which is calling this function, should register scan_completed_cb
 *			 call back in the device_control_cb. When scan is completed then
 *			 all the discovered devices details will be passed to the application
 *			 using scan_completed_cb function. Application is expected to initiate
 *			 connection to a device itself.
 *
 * @param app_handle - Handle of the application.
 * @param timeout_msec - Timeout for stopping scanning. If passed 0 then it is
 * 						never timeout.
 * @param active - Type of the scanning - active/passive.
 * @param limited - Set if limited discovery is to be used.
 * @param use_whitelist - Set if whitelist is to be used for filtering.
 * @param background - Set if low duty cycle scanning is to be done.
 * @return Error code.
 */
INT8 iLE_start_scan(trans_id_t trans_id, UINT32 timeout_msec, BOOLEAN active, BOOLEAN limited, BOOLEAN use_whitelist, BOOLEAN background, UINT8 num_filter_uuids, UINT16* filter_uuids);

/** @brief Requests core stack to start scanning.
 *
 * Function: iLE_start_scan
 *			 This function will start scanning procedure to discover nearby
 *			 LE devices. It will set hard-coded value for scanning parameters.
 *			 Application can only set scan timeout (after this many seconds this
 *			 device will stop searching for devices.
 *			 Application which is calling this function, should register scan_completed_cb
 *			 call back in the device_control_cb. When scan is completed then
 *			 all the discovered devices details will be passed to the application
 *			 using scan_completed_cb function. Application is expected to initiate
 *			 connection to a device itself.
 *
 * @param app_handle - Handle of the application.
 * @param timeout_sec - Timeout for stopping scanning. If passed 0 then it is
 * 						never timeout.
 * @param active - Set if active scanning is to be used.
 * @param use_whitelist - Set if whitelist is to be used for filtering.
 * @param scan_int - Scan interval.
 * @param scan_win - Scan window.
 * @return Error code.
 */
INT8 iLE_start_scan_ex(trans_id_t trans_id, UINT32 timeout_msec, BOOLEAN active, BOOLEAN limited, BOOLEAN use_whitelist, BOOLEAN background, UINT16 scan_int, UINT16 scan_win, UINT8 num_filter_uuids, UINT16* filter_uuids);

/** @brief Requests core stack to stop searching for nearby LE devices
 *
 * Function: stop_scan
 *			 This function stops the device searching facility. After completion
 *			 of this procedure the application will get a call back scan_completed_cb
 *			 with all the list of device found.
 *
 * @param app_handle - Handle of the application.
 * @return Error code.
 */
INT8 iLE_stop_scan(trans_id_t trans_id);

/** @brief Requests core stack to create connection to a remote device
 *
 * Function: connect
 *			 This api allows the application to connection to a remote device.
 *			 This will create a LE-U connection if it is not present. On top of
 *			 the LE-U connection this will create all necessary things.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_connect(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 addr_type);

/** @brief Requests core stack to create connection to a remote device
 *
 * Function: iLE_connect
 *			 This api allows the application to connection to a remote device.
 *			 This will create a LE-U connection if it is not present. On top of
 *			 the LE-U connection this will create all necessary things.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param addr_type - Address type of remote device.
 * @param scan_int - Scan interval.
 * @param scan_win - Scan window.
 * @param conn_int_min - Minimum connection interval.
 * @param conn_int_max - Maximum connection interval.
 * @param conn_lat - Connection latency.
 * @param sup_timeout - Supervision timeout.
 * @return Error code.
 */
INT8 iLE_connect_ex(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 addr_type, UINT16 scan_int, UINT16 scan_win, UINT16 conn_int_min, UINT16 conn_int_max, UINT16 conn_lat, UINT16 sup_timeout);

/*
** @brief Requests core stack to enable auto connection to a remote device
 *
 * Function: iLE_auto_connect
 *			 This api allows the application to enable auto connection on a remote device.
 *
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param addr_type - Address type of remote device.
 * @param enable enable = TRUE will enable auto connection
 *               enable = FALSE will disable auto connection
 * @return Error code.
 */
INT8 iLE_auto_connect(trans_id_t trans_id, UINT8 *remote_bd_addr, UINT8 addr_type, BOOLEAN enable);

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

#if (GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

/** @brief Requests core stack to terminate connection to a remote device
 *
 * Function: iLE_disconnect
 *			 This API allows the application to say to core stack that it will no
 *			 longer needs connection to this remote device. Core stack will terminate
 *			 the connection if no application needs connection to this remote
 *			 device.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_disconnect(trans_id_t trans_id, UINT8 conn_id, UINT8 reason);

#endif /* GAP_CENTRAL_ROLE_SUPPORTED == TRUE || GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (SMP_FEATURE)

/** @brief Requests core stack to initiate bonding procedure with a remote device
 *
 * Function: iLE_create_bond
 *			 Any application can use this API to create a bond with a device
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - Connection id.
 * @param auth_level_min - Minimum Level of authentication required when a bond is created with the remote device
 * @param key_size_min - Minimum length of key used for encryption.This value has to be in the range of 7 to 16.
 * @return Error code.
 */
INT8 iLE_create_bond(trans_id_t trans_id, UINT8 conn_id, UINT8 auth_level_min, UINT8 key_size_min);

/** @brief Requests core stack to remove bonding procedure with a remote device
 *
 * Function: iLE_remove_bond
 *			 Not supported yet. Coming soon.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_remove_bond(trans_id_t trans_id, UINT8* remote_bd_addr, UINT8 addr_type);

#endif /* SMP_FEATURE */

#if (SIGNED_WRITE)

/** @brief Requests core stack to sign data
 *
 * Function: iLE_sign_data
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param data - Data to be signed
 * @param data_len - Length of data in bytes.
 * @return Error code.
 */
INT8 iLE_sign_data(UINT8 app_handle, UINT8* remote_bd_addr, UINT8 *data, UINT16 data_len);

#endif /* SIGNED_WRITE */

#if (TEST_CODE == TRUE && LE_PING_ENABLE==TRUE)
/** @brief Requests core stack to read authenticated payload timeout for an encrypted link
 *
 * Function: iLE_test_read_authenticated_payload_timeout
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_test_read_authenticated_payload_timeout(trans_id_t trans_id, UINT8 conn_id);
/** @brief Requests core stack to write authenticated payload timeout for an encrypted link
 *
 * Function: iLE_test_write_authenticated_payload_timeout
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param authpayload_timeout - Range: 10ms to 655350ms, Default: 30000ms
 *                                                default value will be used if given value is not in range (also honoring conn_interval and conn_latency).
 * @return Error code.
 */
INT8 iLE_test_write_authenticated_payload_timeout(trans_id_t trans_id, UINT8 conn_id, UINT16 authpayload_timeout);
#endif //TEST_CODE && LE_PING_ENABLE

/** @brief Requests core stack to set data len for the specified connection
 *
 * Function: iLE_set_data_len
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - Connection id.
 * @param tx_octets - Range: 27bytes to 251bytes for 1Mbps controller support(default 27 bytes)
 * @return Error code.
 */
INT8 iLE_set_data_len(trans_id_t trans_id, UINT8 conn_id, UINT16 tx_octets);

/** @brief Requests core stack to add a device to whitelist
 *
 * Function: iLE_add_to_whitelist
 *			 This API allows the application to say to core stack that it wants
 *			 to add a device to the whitelist for future operations
 *
 * @param app_handle - Handle of the application.
 * @param addr_type - Address type of the device (public/random).
 * @param bdaddr - Bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_add_to_whitelist(trans_id_t trans_id, UINT8 addr_type, UINT8 *bdaddr);

/** @brief Requests core stack to remove a device from whitelist
 *
 * Function: iLE_remove_from_whitelist
 *			 This API allows the application to say to core stack that it wants
 *			 to remove a device from the whitelist for future operations
 *
 * @param app_handle - Handle of the application.
 * @param addr_type - Address type of the device (public/random).
 * @param bdaddr - Bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_remove_from_whitelist(trans_id_t trans_id, UINT8 addr_type, UINT8 *bdaddr);

/** @brief Requests core stack to clear the whitelist
 *
 * Function: iLE_clear_whitelist
 *			 This API allows the application to say to core stack that it wants
 *			 to clear the whitelist and remove all device entries
 *
 * @param app_handle - Handle of the application.
 * @return Error code.
 */
INT8 iLE_clear_whitelist(trans_id_t trans_id);

#if (CONTROLLER_PRIVACY)

/** @brief Requests core stack to add a device to resolving list
 *
 * Function: iLE_add_to_reslovinglist
 *			 This API allows the application to say to core stack that it wants
 *			 to add a device to the resolving list for future operations
 *
 * @param app_handle - Handle of the application.
 * @param addr_type - Address type of the device (public/random).
 * @param bdaddr - Bluetooth MAC address of the remote device.
 * @param peer_irk - remote device IRK
 * @param_local_irk - local device IRK
 * @return Error code.
 */
INT8 iLE_add_to_resolvinglist(trans_id_t trans_id, UINT8 addr_type, UINT8 *bdaddr, UINT8 * peer_irk, UINT8 * local_irk);

/** @brief Requests core stack to remove a device from resolving list
 *
 * Function: iLE_remove_from_reslovinglist
 *			 This API allows the application to say to core stack that it wants
 *			 to remove a device from the resolving list for future operations
 *
 * @param app_handle - Handle of the application.
 * @param addr_type - Address type of the device (public/random).
 * @param bdaddr - Bluetooth MAC address of the remote device.
 * @return Error code.
 */
INT8 iLE_remove_from_resolvinglist(trans_id_t trans_id, UINT8 addr_type, UINT8 *bdaddr);

#endif /* CONTROLLER_PRIVACY */

/** @brief Requests core stack to update parameters of an existing connection
 *
 * Function: iLE_update_conn_params
 *			 This api allows the application to update parameters of an existing connection.
 *			 This will automatically figure out the best possible method for the operation
 *			 and perform it.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address of the remote device.
 * @param interval_min - Minimum connection interval value
 * @param interval_max - Maximum connection interval value
 * @param conn_latency - Connection latency value
 * @param sup_timeout - Supervision timeout value
 * @return Error code.
 */
INT8 iLE_update_conn_params(trans_id_t trans_id, UINT8 conn_id, UINT16 interval_min, UINT16 interval_max, UINT16 conn_latency, UINT16 sup_timeout);

#if (GATT_SERVER_SUPPORTED == TRUE)

/** @brief Requests core stack to add a GATT service to the service database
 *
 * Function: iLE_add_service
 *			 GATT server application uses this API to add service it wants to
 *			 support.
 *			 \note {Application should call start_service to make it discoverable
 *			 		by remote device.}
 *
 * @param app_handle - Handle of the application.
 * @param uuid - UUID of the service to be added.
 * @param service_type - Primary / secondary / included
 * @return Error code.
 */
INT8 iLE_add_service(trans_id_t trans_id, uuid_t *uuid, UINT8 service_type, UINT8 num_of_incl_srv, UINT8 num_of_char, UINT8 num_of_desc);

/** @brief Requests core stack to add a GATT service to the service database
 *
 * Function: iLE_add_include_service
 *			 GATT server application uses this API to add include service it wants to
 *			 support.
 *			 \note {Application should call start_service to make it discoverable
 *			 		by remote device.}
 *
 * @param app_handle - Handle of the application.
 * @param uuid - UUID of the service to be added.
 * @param service_type - Primary / secondary / included
 * @param start_handle - Handle of service declaration of included service
 * @param end_handle - End Handle of included service definition
 * @return Error code.
 */
INT8 iLE_add_included_service(trans_id_t trans_id, uuid_t *uuid, UINT8 service_type, UINT16 start_handle, UINT16 end_handle);

/** @brief Requests core stack to add a GATT characteristic to a service
 *
 * Function: iLE_add_characteristic
 *			 GATT server application uses this API to add characteristic it wants to
 *			 support. Prior to use this procedure application shall use add_service
 *			 API to create the service.
 *
 * @param app_handle - Handle of the application.
 * @param srv_uuid - UUID of the service.
 * @param char_uuid - UUID of the characteristic
 * @param property - Property of the characteristic. Or the properties as needed.
 * @param value - Default of the characteristic. NULL otherwise.
 * @param value_len - Length in Bytes of the value being passed.
 * @return Error code.
 */
INT8 iLE_add_characteristic(trans_id_t trans_id, uuid_t *uuid, UINT8 property, UINT16 permission);

/** @brief Requests core stack to add a GATT descriptor to a characteristic
 *
 * Function: iLE_add_descriptor
 *			 GATT server application uses this API to add descriptor it wants to
 *			 support. Prior to use this procedure application shall use add_service
 *			 API to create the service and add_characterisitic to create characteristic.
 *
 * @param trans_id - Add descriptor request identifier.
 * @param uuid - UUID of the descriptor to be added
 * @param property - None(0x00) TODO: This parameter will be removed.
 * @param permission - Permission for read / write operation (valid types are ATTRIBUTE_PERMISSION_XXX)
 * 					   Ex: ATTRIBUTE_PERMISSION_READ|ATTRIBUTE_PERMISSION_WRITE etc
 * @return Error code.
 */
INT8 iLE_add_descriptor(trans_id_t trans_id, uuid_t *uuid, UINT8 property, UINT16 permission);

/** @brief Requests core stack to make a GATT service in service database discoverable
 *
 * Function: iLE_start_service
 *			 GATT server application uses this API to make a service visible to
 *			 a remote device. A remote device shall find out this new service
 *			 when a remote device would do primary service discovery procedure
 *			 after this procedure.
 *			 GATT server application shall use app_server and may use add_characteristic,
 *			 add_descriptor apis to add the service in the service database prior
 *			 to using this procedure.
 *
 * @param app_handle - Handle of the application.
 * @param uuid - 16 bit UUID of the service.
 * @return Error code.
 */
INT8 iLE_start_service(trans_id_t trans_id);

/** @brief Requests core stack to remove a GATT service
 *
 * Function: iLE_remove_service
 *			 Stops the service to be discoverable from remote device and removes
 *			 the service from the service database.
 *
 * @param app_handle - Handle of the application.
 * @param uuid - UUID of the service.
 * @return Error code.
 */
INT8 iLE_remove_service(trans_id_t trans_id, UINT16 service_handle);

/** @brief Requests core stack to send response for characteristic read request
 *
 * Function: iLE_send_attribute_read_rsp
 *			 GATT server application uses this API to send out response to a
 *			 characteristic read request from a remote device.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param att_id - attribute handle value
 * @param offset - For characteristic long read this represents the value offset
 * @param value_length - Length in Bytes of the value
 * @param value - Buffer containing the whole / part of characteristic value
 * @param status - Status of the response
 * @return Error code.
 */
INT8 iLE_send_attribute_read_rsp(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT8 status, buffer_t* buffer);

/** @brief Requests core stack to send response for characteristic / descriptor write request
 *
 * Function: iLE_send_attribute_write_rsp
 *			 GATT server application uses this API to send out response to a
 *			 characteristic / descriptor write request from a remote device.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param att_id - attribute handle value
 * @param status - status of the write req. ATT error to be embedded by application for errors.
 * 					Otherwise ATT_SUCCESS
 * @param value - value to be sent for the prepared write response
 * @param value_length - length of the value to be sent in the prepared write response
 * @param offset - offset of the value to be written
 * @param is_execute_resp - if this is the resposne for the execute write
 * @return Error code.
 */
INT8 iLE_send_attribute_write_rsp(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, UINT8 status, buffer_t* buffer);

/** @brief Requests core stack to send notification / indication
 *
 * Function: iLE_send_notification
 *			 GATT server application uses this API to send notification / indication.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param att_id - Characteristic handle value
 * @param value - value buffer of the value to be notified / indicated.
 * @param value_len - Length in Bytes in of the value to be written
 * @param need_response - TRUE to send indication. FALSE for notification.
 * @return Error code.
 */
INT8 iLE_send_notification(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, buffer_t *buffer, BOOLEAN need_response);

/** @brief Requests core stack to store the indication setting for service change characteristic in NVM
 *
 * Function: iLE_set_service_change_config
 *			 GATT server application uses this API to store the indication setting for service change characteristic in NVM.
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - connection id of remote device
 * @param is_notify - TRUE to send indication. FALSE for disable indication for service change characteristic.
 * @return Error code.
 */
INT8 iLE_set_service_change_config(trans_id_t trans_id, UINT8 conn_id, BOOLEAN is_notify);

/** @brief Get the stored indication setting for service change characteristic from core stack
 *
 * Function: iLE_get_service_change_config
 *			 GATT server application uses this API to get the stored indication setting for service change characteristic in NVM
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - connection id of remote device
 * @return - TRUE if indication is set. FALSE if indication is disabled.
 */
BOOLEAN iLE_get_service_change_config(trans_id_t trans_id, UINT8 conn_id);

#endif /* GATT_SERVER_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE)

/** @brief Requests core stack to discover primary service offered by a remote
 * 			device having uuid as specified
 *
 * Function: iLE_discover_primary_service
 *			 GATT client application uses this API to discover primary service
 *			 having UUID as specified in the argument. Core stack shall discover
 *			 all the characteristics and their descriptors as a part of this
 *			 API. on_service_discovered_cb call back will be called to the
 *			 application with reference to the service being discovered. Client
 *			 can use the characteristic / descriptor operation after this operation.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param service_uuid - 16 bit UUID of the service to be discovered
 * @return Error code.
 */
INT8 iLE_discover_primary_service(trans_id_t trans_id, UINT8 conn_id, uuid_t *filter_uuid);

INT8 iLE_discover_included_service(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle);

INT8 iLE_discover_characteristic(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle, uuid_t *filter_uuid);

INT8 iLE_discover_descriptor(trans_id_t trans_id, UINT8 conn_id, UINT16 start_handle, UINT16 end_handle);

/** @brief Requests core stack to read a characteristic value
 *
 * Function: iLE_read_characteristic_value
 *			 GATT client application uses this API to read characteristic value.
 *			 Prior to use this API the application should have performed Primary
 *			 service discovery procedure.
 *			 Characteristic value will be passed to the application using on_characteristic_read_cb
 *			 call back on successful completion of the procedure. If error response
 *			 is sent by the remote device it will not be passed to the application.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param characteristic - reference to gatt characteristic. This reference should be
 * 							the same reference which is passed from the service
 * 							discovery callback.
 * @return Error code.
 */
INT8 iLE_read_attribute_value(trans_id_t trans_id, UINT8 conn_id, gatt_attribute_read_param_t *read_param);

/** @brief Requests core stack to write a characteristic value
 *
 * Function: iLE_write_attribute_value
 *			 GATT client application uses this API to write attribute value.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param gatt_write_type - Type of the write
 * @param attribute - reference to gatt attribute.
 * @param value - value buffer of the value to be written to this characteristic.
 * 				  Depending on the value length core stack uses long write.
 * @param value_len - Length in Bytes in of the value to be written
 * @return Error code.
 */
INT8 iLE_write_attribute_value(trans_id_t trans_id, UINT8 conn_id, UINT8 att_opcode, UINT16 att_id, UINT16 offset, buffer_t *buffer);

/** @brief Requests core stack to enable / disable notification / indication of a characteristic
 *
 * Function: iLE_register_notification
 *			 GATT client application uses this API to enable / disable characteristic
 *			 notification / indication.
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device
 * @param characteristic - reference to gatt characteristic. This reference should be
 * 							the same reference which is passed from the service
 * 							discovery callback.
 * @param is_register - TRUE to register for notification / indication. FALSE to de-register.
 * @return Error code.
 */
INT8 iLE_register_notification(trans_id_t trans_id, UINT8 conn_id, UINT16 att_id, BOOLEAN is_register);

#endif /* GATT_CLIENT_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE)

UINT16 iLE_get_att_mtu(trans_id_t trans_id, UINT8 conn_id);

#endif /* GATT_CLIENT_SUPPORTED == TRUE || GATT_SERVER_SUPPORTED == TRUE */

INT8 iLE_set_att_mtu(trans_id_t trans_id, UINT8 conn_id, UINT16 mtu_size);

#if (SMP_FEATURE)
/** @brief Send the passkey input from the user to the SMP manager
 *
 * Function: iLE_send_passkey
 *			 SMP application uses this interface to send the passkey input from the user to the SMP manager
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device.
 * @param passkey - passkey input from the user.
 * @return Error code.
 */
INT8 iLE_send_passkey(trans_id_t trans_id, UINT8 *remote_bd_addr, UINT8 bdaddr_type, UINT32 passkey);

/** @brief Send the authorization input from the user to the SMP manager
 *
 * Function: iLE_send_authorization
 *			 SMP application uses this interface to send the authorization input from the user to the SMP manager
 *
 * @param app_handle - Handle of the application.
 * @param remote_bd_addr - bluetooth MAC address for remote device.
 * @param authorization - authorization input from the user.
 * @param auth_level_min - Minimum authentication requirement for this pairing
 * @param key_size_min - Minimum key size for this pairing
 * @return Error code.
 */
INT8 iLE_send_authorization(trans_id_t trans_id, UINT8 *remote_bd_addr, UINT8 bdaddr_type, UINT8 authorization, UINT8 auth_level_min, UINT8 key_size_min);

/** @brief Register to the SMP manager for callbacks
 *
 * Function: iLE_smp_register
 *			 SMP application uses this interface to register to the SMP manager callbacks.
 *
 * @param app_handle - Handle of the application.
 * @param smp_cb	- SMP manger callback function.
 * @return Error code.
 */
INT8 iLE_smp_register(trans_id_t trans_id, smp_app_cb_t smp_cb);

/** @brief Sets IO Capabilities of SMP
 *
 * Function: iLE_smp_set_io_capabilities
 *			 Application uses this interface to change the IO Capabilities of SMP Manager.
 *
 * @param trans_id - Unique identifier of the request.
 * @param io_capabilities - IO Capabilities to set, Valid values are as follows
 * 							SMP_DISPLAY_ONLY(0x00)
 *							SMP_DISPLAY_YN(0x01)
 *							SMP_KEYBOARD_ONLY(0x02)
 *							SMP_NO_INPUT_NO_OUTPUT(0x03) - Default
 *							SMP_KEYBOARD_DISPLAY(0x04)
 * @return Error code - Returns SUCCESS(0x00) if command is successful else returns the proper error code.
 */
INT8 iLE_smp_set_io_capabilities(trans_id_t trans_id, UINT8 io_capabilities);
#endif /* SMP_FEATURE */

#if (SECURE_CONNECTION)
INT8 iLE_smp_send_nc_result(trans_id_t trans_id, UINT8 *remote_bd_addr,
		UINT8 bdaddr_type, UINT8 authorization);
#endif /* SECURE_CONNECTION */


/** @brief Check if controller supports central address resolution
 *
 * Function: iLE_is_controller_privacy_supported
 *			 This is meant to be used by the GATT-GAP service profile to determine if the controller
 *			 supports central address resolution. Since this profile is supposed to reside in the
 *			 controller for embedded deployments, no HCI command code is required for this. Instead,
 *			 this would be a direct function call, which would return synchronously with the value.
 *
 * @return TRUE if controller supports central address resolution, FALSE otherwise
 */
BOOLEAN iLE_is_controller_privacy_supported(trans_id_t trans_id);

#if (TEST_CODE == TRUE)
INT8 iLE_test_enable_privacy(trans_id_t trans_id, UINT8 enable_privacy);
#endif

UINT8 iLE_get_bdaddr(trans_id_t trans_id, UINT8 *bdaddr);

INT8 iLE_test_set_public_bdaddr(trans_id_t trans_id, UINT8* bdaddr);

INT8 iLE_send_hci_command(trans_id_t trans_id, UINT16 opcode, UINT8 buffer_len, UINT8* command_buffer);

#if (TEST_CODE == TRUE)
	/* Needed for VSC HCI passthrough*/
INT8 iLE_send_vshci_command(trans_id_t trans_id, UINT8 buffer_len, UINT8* command_buffer);

#endif

#if (L2CAP_COC == TRUE)
/** @brief Requests core stack to create an L2CAP connection oriented channel
 *
* Function: iLE_l2cap_coc_connect_req
*
* @param app_handle - Handle of the application.
* @param conn_id - connection id of remote device.
* @param psm - Protocol Service Multiplexer value of the protocol used on this CoC.
* @param mtu - Maximum transmission unit value that the local device can accept
* @param l2cap_coc_cbs - callback functions for L2CAP CoC
*
* @return Error code.
*/
INT8 iLE_l2cap_coc_connect_req(trans_id_t trans_id, UINT8 conn_id, UINT16 psm, UINT16 mtu, l2cap_coc_callbacks_t *l2cap_coc_cbs);

/** @brief Requests core stack to register for an psm. An incoming CoC create is accepted if an App has registered for the psm.
 *
 * Function: iLE_l2cap_coc_register_cb_for_conn_req
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - connection id of remote device.
 * @param psm - Protocol Service Multiplexer registered by the app.
 * @param mtu - Maximum transmission unit value that the local device can accept
 * @param l2cap_coc_cbs - callback functions for L2CAP CoC
 * @parma auth_req - whether application needs any authorisation callbacks before a connection is made using this psm
 *
 * @return Error code.
 */
INT8 iLE_l2cap_coc_register(trans_id_t trans_id, UINT16 psm, UINT16 mtu, l2cap_coc_callbacks_t *l2cap_coc_cbs, BOOLEAN auth_req);

/** @brief Request to get maximum MTU size supported by stack for l2cap CoC.
 *
 * Function: iLE_l2cap_coc_get_max_mtu_size
 *
 * @param app_handle - Handle of the application.
 *
 * @return Maximum MTU size supported by stack for l2cap CoC.
 */
UINT16 iLE_l2cap_coc_get_max_mtu_size(trans_id_t trans_id);

/** @brief Request to disconnect a L2CAP CoC channel
 *
 * Function: iLE_l2cap_coc_disconnect_req
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - connection id of remote device.
 * @param coc_handle - Handle of the L2CAP CoC to be disconnected
 *
 * @return Error code.
 */
INT8 iLE_l2cap_coc_disconnect_req(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle);

/** @brief Request to send data over an L2CAP CoC channel
 *
 * Function: iLE_l2cap_coc_send_data
 *
 * @param app_handle - Handle of the application.
 * @param conn_id - connection id of remote device.
 * @param coc_handle - Handle of the L2CAP CoC
 * @param buffer - buffer to be send to remote device
 * @param buffer_len - length to the buffer to be send to remote device
 *
 * @return Error code.
 */
INT8 iLE_l2cap_coc_send_data(trans_id_t trans_id, UINT8 conn_id, UINT8 coc_handle, UINT8* buffer, UINT16 buffer_len);
#endif // L2CAP_COC

/* Storage APIs */

/** @brief Register for storage related callbacks
 *
 * Function : iLE_storage_register
 *
 * @param trans_id - transaction id related to registration.
 *
 * @param storage_cb - collection of all the storage callbacks
 */
INT8 iLE_storage_register(trans_id_t trans_id, storage_callbacks_t *storage_cb);
/** @brief Set a particular security key.
 *
 * Function : iLE_key_response
 *
 * @param trans_id - transaction id
 *
 * @param bdaddr - Bluetooth address for the device for which the keys are being set
 *
 * @param bdaddr_type - address type
 *
 * @param key_type - describes the key that is being set
 * 					 eg : LOCAL_LTK, PEER_LTK, LOCAL_IRK, PEER_IRK etc.
 * @param is_valid -
 *
 * @param key_value - value of the key
 * 					- non-NULL indicate that the key was found.
 * 				   	- NULL indicate that the key was not found.
 */

INT8 iLE_key_response(trans_id_t trans_id, UINT8 *bdaddr, UINT8 bdaddr_type, UINT8 key_type, void *key_value);

#endif
