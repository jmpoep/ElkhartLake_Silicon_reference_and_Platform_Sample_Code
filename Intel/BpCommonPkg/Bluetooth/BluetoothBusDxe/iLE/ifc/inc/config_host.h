/** @file
  Configuration header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef CONFIG_HOST_H_
#define CONFIG_HOST_H_

/* Stores configurations */

#undef FALSE
#define FALSE 0
#undef TRUE
#define TRUE  1

#define BT_USERIAL_PORT_NAME "/dev/ttyUSB0"
#define BT_USERIAL_BAUD_RATE 115200
#define BTSNOOPDISP_LOG_FILENAME "btsnoop_lestack.log"
#define BT_UHID_PORT_NAME "/dev/uhid"

/****************************
 * Stack configuration
 ***************************/

#define LOCAL_NAME "LE Stack"
#define MAX_LOCAL_NAME_LEN 248

#ifndef TEST_CODE
#define TEST_CODE FALSE
#endif

#define MAX_NUM_SCAN_FILTER_UUIDS	10

/**
 * This is the max number of device our stack can remember.
 */
#if (A4WP_ONLY_STACK == TRUE)
#define MAX_NUM_CONNECTED_DEVICE 				1
#define MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES	5
#define MAX_NUM_BONDED_DEVICE					2
#define LE_STACK_PROFILING						FALSE
#else
#define MAX_NUM_CONNECTED_DEVICE				8
#define MAX_NUM_ADV_SCANRESP_DATA_STRUCTURES	10
#define MAX_NUM_BONDED_DEVICE					8
#endif

/* Max number of simultaneous req Profile Manager can support */
#define MAX_NUMBER_OF_PM_REQ			5
#define MAX_NUM_REG_NOTIFY_CHAR			5

#if (TEST_CODE == TRUE)
#define MAX_NUM_ATTR					200
#define MAX_NUMBER_OF_APP				10
#define MAX_NUMBER_OF_AUTO_CONNECT		8
#elif (A4WP_ONLY_STACK == TRUE)
#define MAX_NUM_ATTR					25
#define MAX_NUMBER_OF_APP				3 /* A4WP, GAP-GATT, Adaptation */
#define MAX_NUMBER_OF_AUTO_CONNECT		3
#else
#define MAX_NUM_ATTR					200
#define MAX_NUMBER_OF_APP				10
#define MAX_NUMBER_OF_AUTO_CONNECT		8
#endif
#define MAX_APP_PREFIX_LENGTH			5
#define MAX_NUMBER_OF_L2CAP_COC_CHNL	5
#define MAX_NUMBER_OF_L2CAP_CHNL 		(MAX_NUMBER_OF_L2CAP_COC_CHNL + 3)

/****************************
 * Thread priority configurations
 ***************************/
/* Thread priorities (relevant for ThreadX) */
#define STACK_THREAD_PRIORITY	16
#define PROFILE_THREAD_PRIORITY	17

/****************************
 * Internal memory configurations
 ***************************/
/*	For Byte addressable internal memory memory
 *  Memory pool size in KB (for OS without dynamic allocation support) */
#define STACK_MEM_POOL_SIZE_BYTE	2560
#define APP_POOL_SIZE_BYTE			512
#define L2CAP_POOL_SIZE_BYTE		128

/* Tune these to requirement */
#define MEM_BUF_POOL0_ELEM_SIZE	8
#define MEM_BUF_POOL1_ELEM_SIZE	16
#define MEM_BUF_POOL2_ELEM_SIZE	36
#define MEM_BUF_POOL3_ELEM_SIZE	64
#define MEM_BUF_POOL4_ELEM_SIZE	128
#define MEM_BUF_POOL5_ELEM_SIZE	512

#define MEM_BUF_POOL0_ID	0
#define MEM_BUF_POOL1_ID	1
#define MEM_BUF_POOL2_ID	2
#define MEM_BUF_POOL3_ID	3
#define MEM_BUF_POOL4_ID	4
#define MEM_BUF_POOL5_ID	5
#define MEM_BUF_POOL_MAX_ID	6

#if (A4WP_ONLY_STACK == TRUE)
#define MEM_BUF_POOL0_LENGTH	16
#define MEM_BUF_POOL1_LENGTH	20
#define MEM_BUF_POOL2_LENGTH	16
#define MEM_BUF_POOL3_LENGTH	16
#define MEM_BUF_POOL4_LENGTH	16
#define MEM_BUF_POOL5_LENGTH	5
#else
#define MEM_BUF_POOL0_LENGTH	100
#define MEM_BUF_POOL1_LENGTH	100
#define MEM_BUF_POOL2_LENGTH	100
#define MEM_BUF_POOL3_LENGTH	100
#define MEM_BUF_POOL4_LENGTH	30
#define MEM_BUF_POOL5_LENGTH	30
#endif

/* IMPORTANT: Put the maximum of pool length in this macro */
#define MEM_BUF_POOL_MAX_LENGTH MEM_BUF_POOL1_LENGTH

/****************************
 * GAP configurations
 ***************************/
/* This is the max length of remote device name our stack can store */
#define MAX_DEVICE_NAME_LEN 32

#define GAP_REMOTE_COMMAND_TIMEOUT_SEC 5
#define GAP_MAX_NUM_OPERATIONS 10

#define DLE_SET_DEF_TX_OCTECTS	0x001B // Should be between DLE_MIN_TX_OCTECTS and DLE_MAX_TX_OCTECTS

/****************************
 * SMP configurations
 ***************************/
/* Auth request */
#define SMP_MITM_Y 		(1<<2)
#define SMP_MITM_N 		(0)
#define SMP_BONDING_Y 	(1)
#define SMP_BONDING_N 	(0)
#define SMP_SC_Y		(1<<3)
#define SMP_SC_N		(0)

/* Key distribution */
#define SMP_ENC_N 	(0)
#define SMP_ENC_Y 	(1)
#define SMP_ID_N	(0<<1)
#define SMP_ID_Y	(1<<1)
#define SMP_SIGN_N	(0<<2)
#define SMP_SIGN_Y	(1<<2)
#define SMP_OOB_N	(0)
#define SMP_OOB_Y	(1)

/* IO capabilities */
#define SMP_DISPLAY_ONLY		0x00
#define SMP_DISPLAY_YN			0x01
#define SMP_KEYBOARD_ONLY		0x02
#define SMP_NO_INPUT_NO_OUTPUT 	0x03
#define SMP_KEYBOARD_DISPLAY	0x04
#define SMP_MAX_IO_CAP			0x04

#ifndef LE_PING_ENABLE
#define LE_PING_ENABLE TRUE
#endif //LE_PING_ENABLE

#define GAP_EXTRA_REMOTE_DATA FALSE

/* Default key size */
#define SMP_DEFAULT_ENC_KEY_SIZE	16

/*Out of the Band data*/
#define SMP_DEFAULT_OOB_FLAG	SMP_OOB_N


#ifndef SMP_FORCE_DISABLE_HOST_DLE
#define SMP_FORCE_DISABLE_HOST_DLE FALSE
#endif

/*
 * Feature Flags
 * The below list indicates the features that are supported by the stack.
 */

#ifndef SMP_FEATURE
#define SMP_FEATURE TRUE
#endif

/*
 * Privacy Feature has a dependency on SMP
 */
#ifndef PRIVACY_FEATURE
#if (SMP_FEATURE)
#define PRIVACY_FEATURE	TRUE
#else
#define PRIVACY_FEATURE FALSE
#endif
#endif

/*
 * Signed write has a dependency on SMP
 */
#ifndef SIGNED_WRITE
#if (SMP_FEATURE)
#define SIGNED_WRITE TRUE
#else
#define SIGNED_WRITE FLASE
#endif
#endif /* SIGNED_WRITE */

/*
 * Secure connection has a dependency on SMP
 */
#ifndef SECURE_CONNECTION
#if (SMP_FEATURE)
#define	SECURE_CONNECTION TRUE
#else
#define	SECURE_CONNECTION FALSE
#endif
#endif /* SECURE_CONNECTION */

/* Depending on the whether privacy feature is enabled or not, stack can enable controller based privacy (1.2)
 * or host based privacy(1.1).
 */
#if (PRIVACY_FEATURE == TRUE)
/*
* Controller based privacy requires support from controller.
* So enabling it here doesn't guarantee that privacy feature will be supported.
* If support from the controller is not sure, enable host based privacy flag also.
*/
#define CONTROLLER_PRIVACY TRUE
/*
 * Host based privacy requires additional memory to keep the resolving list in the stack.
 * If controller based privacy is supported, then disable this feature.
 * If enabled RESOLVING_LIST_SIZE determines the number of resolving list entries that would be
 * supported in the stack.
 */
#define HOST_PRIVACY FALSE

#if (HOST_PRIVACY == TRUE)
#define HOST_RESOLVING_LIST_SIZE 10
#endif

#define ADV_IN_PUBLIC_ADDRESS FALSE

#else
/*
 * If privacy feature is disabled, then both host based and controller based privacy should be disabled.
 */
#define CONTROLLER_PRIVACY FALSE
#define HOST_PRIVACY FALSE
#endif

/*
 * Secure connection requires ECDH algorithms to generate public & private keys and DHkeys.
 * Support for these ECDH algorithms can come from the controller through hci commands.
 * Support for these ECDH algorithms can come from the stack.
 */
#if (SECURE_CONNECTION == TRUE)
/*
 * The ECDH should either be supported from controller or from host.
 * Only one of the below should be TRUE.
 */
#define CONTROLLER_ECDH FALSE
#define HOST_ECDH TRUE
#else
#define CONTROLLER_ECDH FALSE
#define HOST_ECDH FALSE
#endif

#if (SECURE_CONNECTION == TRUE || SIGNED_WRITE == TRUE)
#define AES_CMAC TRUE
#else
#define AES_CMAC FALSE
#endif

#if (SMP_FEATURE)
#define SMP_DEFAULT_IO_CAP SMP_KEYBOARD_DISPLAY
#define INTERNAL_AES FALSE
#endif
/* Simulate short controller resolving list */
//#define SHORT_RL_SIMULATE_SIZE 5

/****************************
 * L2CAP configurations
 ***************************/
/**
 * This many number of buffers (TX / RX) are available for each l2cap
 * connections (i.e. logical link in this case)
 * */
#define L2CAP_DATA_BUFFER_NUM 2

/*Alert level values*/
#define NO_ALERT 0
#define MILD_ALERT 1
#define HIGH_ALERT 2

/****************************
 * Compilation targets
 ***************************/

#if (TARGET_OS == 1)
#define TARGET_LINUX TRUE
#else
#define TARGET_LINUX FALSE
#endif

#if (TARGET_OS == 2)
#define TARGET_THREADX TRUE
#else
#define TARGET_THREADX FALSE
#endif

#if (TARGET_OS == 4)
#define TARGET_ANDROID TRUE
#else
#define TARGET_ANDROID FALSE
#endif

/****************************
 * Rules
 ***************************/

#if (TARGET_THREADX == TRUE)
#undef TARGET_LINUX
#define TARGET_LINUX			FALSE
#define INTERNAL_ECC			FALSE
#define BTSNOOPDISP_INCLUDED	FALSE
#define LOG_ENABLED				FALSE
#define MEM_MGMT_INTERNAL		TRUE
#define STORAGE_INCLUDED		FALSE
#define TEST_APP				FALSE
#define SMP_APP					FALSE
#define PROFILING				FALSE
#define STRESS_TEST_SUITE		FALSE
#define A4WP_APP				TRUE
#define HRP_APP 				FALSE
#define FMP_APP					FALSE
#define FMP_SRV_APP 			FALSE
#define HOGP_APP 				FALSE
#define HCI2ILE_ADAPT_APP		TRUE
#endif

#if (TARGET_UEFI == TRUE)
#undef GAP_CENTRAL_ROLE_SUPPORTED
#undef GAP_PERIPHERAL_ROLE_SUPPORTED
#undef GATT_CLIENT_SUPPORTED
#undef GATT_SERVER_SUPPORTED
#undef L2CAP_COC
#undef LE_PING_ENABLE
#undef SMP_SECURITY_LVL
#undef GAP_EXTRA_REMOTE_DATA
#undef CONTROLLER_ECDH
#undef HOST_ECDH
#undef SECURE_CONNECTION
#undef INTERNAL_AES
#undef SMP_DEFAULT_IO_CAP
#undef PRIVACY_FEATURE
#undef CONTROLLER_PRIVACY
#undef HOST_PRIVACY
#undef UEFI_HOGP_PTS
#define STORAGE_INCLUDED		FALSE
#define BTSNOOPDISP_INCLUDED		FALSE
#define FILE_LOGGING			FALSE
#define DEBUG_STACK             	TRUE
#define GAP_CENTRAL_ROLE_SUPPORTED	TRUE
#define GAP_PERIPHERAL_ROLE_SUPPORTED	FALSE
#define GATT_CLIENT_SUPPORTED		TRUE
#define GATT_SERVER_SUPPORTED		FALSE
#define GAP_EXTRA_REMOTE_DATA		TRUE
#define L2CAP_COC			FALSE
#define WVT_TEST_APP			FALSE
#define TEST_APP 			FALSE
#define UEFI_APP			TRUE
#define UEFI_APP_DBG_LVL		DBG_LVL_INFO
#define USERIAL_DBG_LVL			DBG_LVL_WARNING
#define ATT_DBG_LVL			DBG_LVL_WARNING
#define GATT_DBG_LVL			DBG_LVL_WARNING
#define DEVICE_MGR_DBG_LVL		DBG_LVL_WARNING
#define PROFILE_MGR_DBG_LVL		DBG_LVL_WARNING
#define SMP_MGR_DBG_LVL			DBG_LVL_WARNING
#define SMP_DBG_LVL			DBG_LVL_WARNING
#define GAP_DBG_LVL			DBG_LVL_WARNING
#define GAP_GATT_SRV_APP 		FALSE
#define A4WP_APP 			FALSE
#define FMP_SRV_APP 			FALSE
#define SMP_APP 			FALSE
#define HRP_APP 			FALSE
#define FMP_APP				FALSE
#define LE_PING_ENABLE 			FALSE
#define STRESS_TEST_SUITE 		FALSE
#define STRESS_TEST_SUITE 		FALSE
#define HOGP_APP 			FALSE
#define LE_STACK_PROFILING		FALSE
#define PROFILING			FALSE
#define INTERNAL_AES 			FALSE
#define SMP_DEFAULT_IO_CAP SMP_KEYBOARD_DISPLAY
#define THREADLESS_STACK		TRUE
#define RX_PROCESSING_IN_TIMER_THREAD	TRUE
#define SECURE_CONNECTION		FALSE
#define CONTROLLER_ECDH			FALSE
#define HOST_ECDH			FALSE
#define PRIVACY_FEATURE			TRUE
#define CONTROLLER_PRIVACY		TRUE
#define HOST_PRIVACY			FALSE
#define HOST_RESOLVING_LIST_SIZE	10
#define UEFI_HOGP_PTS		FALSE
#endif

#if (TARGET_THREADX_RW == TRUE)
#undef LOG_ENABLED
#define LOG_ENABLED             FALSE
#undef TARGET_LINUX
#define TARGET_LINUX			FALSE
#undef TARGET_THREADX
#define TARGET_THREADX			FALSE
#undef LE_PING_ENABLE
#define LE_PING_ENABLE			TRUE
#define BTSNOOPDISP_INCLUDED	FALSE
#define ATP_BT_SNOOP			FALSE
#define L2CAP_COC				TRUE
#define MEM_MGMT_INTERNAL		FALSE
#define STORAGE_INCLUDED		FALSE
#define TEST_APP				FALSE
#define INTERNAL_ECC			TRUE
#define SMP_APP					FALSE
#define STRESS_TEST_SUITE		FALSE
#define A4WP_APP 				FALSE
#define FMP_SRV_APP 			FALSE
#define GAP_GATT_SRV_APP 		TRUE
#define LE_STACK_PROFILING		FALSE
#define PROFILING				FALSE
#define HRP_APP 				FALSE
#define L2CAP_COC_TEST_APP		FALSE
#define FMP_APP					FALSE
#define HOGP_APP 				FALSE
#define DEBUG_STACK				FALSE
#define HCI2ILE_ADAPT_APP		TRUE
#define ATP_AUTO_TEST_MODE		FALSE
#undef GAP_EXTRA_REMOTE_DATA
#define GAP_EXTRA_REMOTE_DATA   TRUE
#endif

#if (TARGET_ANDROID == TRUE)
#undef TARGET_LINUX
#define TARGET_LINUX TRUE
#define INTERNAL_ECC			FALSE
#define UTILS_DBG_LVL DBG_LVL_INFO
#define HCI_DBG_LVL DBG_LVL_INFO
#define L2CAP_DBG_LVL DBG_LVL_INFO
#define GAP_DBG_LVL DBG_LVL_INFO
#define USERIAL_DBG_LVL DBG_LVL_INFO
#define GATT_DBG_LVL DBG_LVL_INFO
#define ATT_DBG_LVL DBG_LVL_INFO
#define SMP_DBG_LVL DBG_LVL_INFO
#define SERVICE_MGR_DBG_LVL DBG_LVL_INFO
#define DEVICE_MGR_DBG_LVL DBG_LVL_INFO
#define PROFILE_MGR_DBG_LVL DBG_LVL_INFO
#define SMP_MGR_DBG_LVL DBG_LVL_INFO
#define INTERFACE_DBG_LVL DBG_LVL_INFO
#undef BTSNOOPDISP_LOG_FILENAME
#define BTSNOOPDISP_LOG_FILENAME "/data/btsnoop_lestack.log"
#define SMP_APP FALSE /* In android HAL handles bonding procedure */
#undef GAP_EXTRA_REMOTE_DATA
#define GAP_EXTRA_REMOTE_DATA 		TRUE
#undef MEM_MGMT_INTERNAL
#define MEM_MGMT_INTERNAL 			FALSE
#define A4WP_APP 					FALSE
#define FMP_SRV_APP 				FALSE
#define PROFILING					FALSE
#define HRP_APP 					FALSE
#define FMP_APP 					FALSE
#define L2CAP_COC_TEST_APP 			FALSE
#define TEST_APP 					FALSE
#define HCI2ILE_ADAPT_APP			FALSE
#define HOGP_APP 					FALSE
#define HOGP_APP FALSE
#endif


#if (TARGET_THREADX == TRUE && A4WP_ONLY_STACK == TRUE)
#define BLE_USE_FWINFO_FUNC_CALL			TRUE
#else
#define BLE_USE_FWINFO_FUNC_CALL			FALSE
#endif

#if (TARGET_LINUX == TRUE)
#define PROFILING FALSE
#define HCI2ILE_ADAPT_APP	FALSE
#define AES_INTERNAL TRUE
#endif

#if (ATP_AUTO_TEST_MODE)
#if defined(CFG_ATP_ADV_PRODUCTION)
#define ATP_ADV_DUT				TRUE
#endif
#if defined(CFG_ATP_ADV_1SEC_PRODUCTION)
#define ATP_ADV_1SEC_DUT				TRUE
#endif
#if defined(CFG_ATP_CONN_1SEC_PRODUCTION)
#define	ATP_SCAN_CONNECT_DUT	TRUE
#endif
#endif

#if (TARGET_THREADX_RW != TRUE)
#define RETENTION_SECTION_START
#define RETENTION_SECTION_END
#endif /* (TARGET_THREADX_RW != TRUE) */

/****************************
 * A4WP specific stack feature configuration
 ***************************/
#if (A4WP_ONLY_STACK == TRUE)
#undef GAP_CENTRAL_ROLE_SUPPORTED
#undef GAP_PERIPHERAL_ROLE_SUPPORTED
#undef L2CAP_COC
#undef GATT_CLIENT_SUPPORTED
#undef GATT_SERVER_SUPPORTED
#define GAP_CENTRAL_ROLE_SUPPORTED		FALSE
#define GAP_PERIPHERAL_ROLE_SUPPORTED	TRUE
#define L2CAP_COC						FALSE
#define GATT_CLIENT_SUPPORTED			FALSE
#define INTERNAL_ECC					FALSE
#define GATT_SERVER_SUPPORTED			TRUE
#undef MEM_MGMT_INTERNAL
#define MEM_MGMT_INTERNAL				TRUE
#undef SMP_SECURITY_LVL
#define TEST_APP FALSE
#define GAP_GATT_SRV_APP TRUE
#define A4WP_APP TRUE
#define FMP_SRV_APP FALSE
#define SMP_APP FALSE
#undef LE_PING_ENABLE
#define LE_PING_ENABLE FALSE
#define HCI2ILE_ADAPT_APP				FALSE
#define STRESS_TEST_SUITE 				FALSE
#define STRESS_TEST_SUITE 				FALSE
#endif
/****************************
 * Stack features
 ***************************/
#ifndef MEM_MGMT_INTERNAL
#define MEM_MGMT_INTERNAL FALSE
#endif

#define MEMORY_POOL_MGMT		1
#define MEMORY_BYTE_ADDR_MGMT	2

#if (MEM_MGMT_INTERNAL == TRUE)
#ifndef MEM_MGMT_INTERNAL_SCHEME
#define MEM_MGMT_INTERNAL_SCHEME	MEMORY_BYTE_ADDR_MGMT
#endif
#endif

/* TRUE: store the bonded device data and adapter data in NVM */
#if (TARGET_THREADX == FALSE)
#ifndef STORAGE_INCLUDED
#define STORAGE_INCLUDED TRUE
#else
#define STORAGE_INCLUDED FALSE
#endif

#if (STORAGE_INCLUDED == TRUE)
#define LOCAL_STORAGE_FILE_LOCATION "lestack_config_file"
#endif
#endif

#ifndef STRESS_TEST_SUITE
#define STRESS_TEST_SUITE FALSE
#endif

#ifndef THREADLESS_STACK
/* EXPERIMENTAL: Enable to eliminate stack main thread
 * All stack processing (downward flow) happens in the app thread context
 * All callbacks (upward flow) happen in the userial read thread context
 */
#define THREADLESS_STACK FALSE
#endif

#if (THREADLESS_STACK == TRUE)
/* If set to TRUE, all RX data will be processed in a timer thread context
 * Otherwise, all RX data will be processed in the RX thread context
 */
#ifndef RX_PROCESSING_IN_TIMER_THREAD
#define RX_PROCESSING_IN_TIMER_THREAD FALSE
#endif
#endif

/****************************
 * GAP features
 ***************************/
#ifndef GAP_CENTRAL_ROLE_SUPPORTED
#define GAP_CENTRAL_ROLE_SUPPORTED TRUE
#endif

#ifndef GAP_PERIPHERAL_ROLE_SUPPORTED
#define GAP_PERIPHERAL_ROLE_SUPPORTED TRUE
#endif

#ifndef GAP_RANDOM_ADDDRESS_SUPPORT
#define GAP_RANDOM_ADDDRESS_SUPPORT TRUE
#endif

#ifndef GAP_DISCOVER_ALL_DEVICES
#define GAP_DISCOVER_ALL_DEVICES TRUE
#endif

/****************************
 * L2CAP features
 ***************************/
#ifndef L2CAP_COC
#define L2CAP_COC TRUE
#define L2CAP_COC_PTS FALSE // Should be TRUE only when L2CAP_COC is TRUE
#endif

/****************************
 * GATT features
 ***************************/
#ifndef GATT_CLIENT_SUPPORTED
#define GATT_CLIENT_SUPPORTED TRUE
#endif

#ifndef GATT_SERVER_SUPPORTED
#define GATT_SERVER_SUPPORTED TRUE
#endif

/****************************
 * HCI features
 ***************************/
#ifndef SIMULTANEOUS_HCI_COMMANDS
#define SIMULTANEOUS_HCI_COMMANDS FALSE
#endif

/****************************
 * Log levels
 ***************************/
#define DBG_LVL_INFO		5
#define DBG_LVL_DEBUG		4
#define DBG_LVL_WARNING		3
#define DBG_LVL_ERROR		2
#define DBG_LVL_EXCEPTION	1

/****************************
 * Debug settings
 ***************************/
#ifndef BTSNOOPDISP_INCLUDED
#define BTSNOOPDISP_INCLUDED TRUE
#endif

#ifndef LOG_ENABLED
#define LOG_ENABLED	TRUE
#endif

#ifndef PARANOID_STACK
#define PARANOID_STACK	TRUE
#endif

#ifndef HCI_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define HCI_DBG_LVL				DBG_LVL_WARNING
#else
#define HCI_DBG_LVL				DBG_LVL_WARNING
#endif
#endif

#ifndef L2CAP_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define L2CAP_DBG_LVL			DBG_LVL_WARNING
#else
#define L2CAP_DBG_LVL			DBG_LVL_WARNING
#endif
#endif

#ifndef GAP_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define GAP_DBG_LVL				DBG_LVL_INFO
#else
#define GAP_DBG_LVL				DBG_LVL_WARNING
#endif
#endif

#ifndef UTILS_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define UTILS_DBG_LVL			DBG_LVL_WARNING
#else
#define UTILS_DBG_LVL			DBG_LVL_WARNING
#endif
#endif

#ifndef DEVICE_UTILS_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define DEVICE_UTILS_DBG_LVL	DBG_LVL_WARNING
#else
#define DEVICE_UTILS_DBG_LVL	DBG_LVL_WARNING
#endif
#endif

#ifndef USERIAL_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define USERIAL_DBG_LVL			DBG_LVL_INFO
#else
#define USERIAL_DBG_LVL			DBG_LVL_WARNING
#endif
#endif

#ifndef GATT_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define GATT_DBG_LVL			DBG_LVL_INFO
#else
#define GATT_DBG_LVL			DBG_LVL_WARNING
#endif
#endif

#ifndef ATT_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define ATT_DBG_LVL				DBG_LVL_INFO
#else
#define ATT_DBG_LVL				DBG_LVL_WARNING
#endif
#endif

#ifndef SMP_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define SMP_DBG_LVL				DBG_LVL_INFO
#else
#define SMP_DBG_LVL				DBG_LVL_WARNING
#endif
#endif

#ifndef SERVICE_MGR_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define SERVICE_MGR_DBG_LVL		DBG_LVL_INFO
#else
#define SERVICE_MGR_DBG_LVL		DBG_LVL_WARNING
#endif
#endif

#ifndef DEVICE_MGR_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define DEVICE_MGR_DBG_LVL		DBG_LVL_INFO
#else
#define DEVICE_MGR_DBG_LVL		DBG_LVL_WARNING
#endif
#endif

#ifndef PROFILE_MGR_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define PROFILE_MGR_DBG_LVL		DBG_LVL_INFO
#else
#define PROFILE_MGR_DBG_LVL		DBG_LVL_WARNING
#endif
#endif

#ifndef SMP_MGR_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define SMP_MGR_DBG_LVL			DBG_LVL_INFO
#else
#define SMP_MGR_DBG_LVL			DBG_LVL_WARNING
#endif
#endif

#ifndef INTERFACE_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define INTERFACE_DBG_LVL		DBG_LVL_WARNING
#else
#define INTERFACE_DBG_LVL		DBG_LVL_WARNING
#endif
#endif

#ifndef STORAGE_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define STORAGE_DBG_LVL			DBG_LVL_WARNING
#else
#define STORAGE_DBG_LVL			DBG_LVL_WARNING
#endif
#endif

#ifndef MEM_MGR_DBG_LVL
#if (DEBUG_STACK == TRUE)
#define MEM_MGR_DBG_LVL			DBG_LVL_INFO
#else
#define MEM_MGR_DBG_LVL			DBG_LVL_WARNING
#endif
#endif

/************************************************
 * Choose application to run and set debug levels
 ************************************************/
#ifndef MAIN_APP_DBG_LVL
#define MAIN_APP_DBG_LVL		DBG_LVL_WARNING
#endif

#ifndef TEST_APP_DBG_LVL
#define TEST_APP_DBG_LVL		DBG_LVL_DEBUG
#endif

#ifndef PROFILE_ADAPT_APP_DBG_LVL
#define PROFILE_ADAPT_APP_DBG_LVL	DBG_LVL_WARNING
#endif

#if (L2CAP_COC == TRUE)
#ifndef L2CAP_COC_TEST_APP
#define L2CAP_COC_TEST_APP TRUE
#endif
#endif

#ifndef TEST_APP
#if (HCI2ILE_ADAPT_APP == FALSE)
#define TEST_APP TRUE
#define SMP_APP	 TRUE
#else
#define TEST_APP FALSE
#define SMP_APP  FALSE
#endif
#endif

#if (GATT_SERVER_SUPPORTED == TRUE && GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE)

#ifndef GAP_GATT_SRV_APP
#define GAP_GATT_SRV_APP TRUE
#endif
#if (DEBUG_STACK == TRUE)
#define GAP_GATT_SRV_DBG_LVL 	DBG_LVL_INFO
#else
#define GAP_GATT_SRV_DBG_LVL 	DBG_LVL_WARNING
#endif

#ifndef A4WP_APP
#define A4WP_APP FALSE
#endif
#define A4WP_DBG_LVL			DBG_LVL_DEBUG

#ifndef FMP_SRV_APP
#define FMP_SRV_APP FALSE
#endif
#define FMP_SRV_APP_DBG_LVL		DBG_LVL_DEBUG

#endif /* GATT_SERVER_SUPPORTED == TRUE && GAP_PERIPHERAL_ROLE_SUPPORTED == TRUE */

#if (GATT_CLIENT_SUPPORTED == TRUE && GAP_CENTRAL_ROLE_SUPPORTED == TRUE)

#ifndef FMP_APP
#define FMP_APP FALSE
#define FMP_APP_DBG_LVL			DBG_LVL_DEBUG
#endif

#ifndef PXP_APP
#define PXP_APP FALSE
#define PXP_APP_DBG_LVL			DBG_LVL_DEBUG
#endif

#ifndef HRP_APP
#define HRP_APP FALSE
#define HRP_APP_DBG_LVL			DBG_LVL_DEBUG
#endif

#ifndef HOGP_APP
#define HOGP_APP FALSE
#define HOGP_APP_DBG_LVL		DBG_LVL_WARNING
#define UHID_HOST_DBG_LVL		DBG_LVL_WARNING
#endif

#ifndef INTERNAL_ECC
#define INTERNAL_ECC FALSE
#endif

#endif /* GATT_CLIENT_SUPPORTED == TRUE && GAP_CENTRAL_ROLE_SUPPORTED == TRUE */

#ifndef HCI2ILE_ADAPT_APP_DBG_LVL
#define HCI2ILE_ADAPT_APP_DBG_LVL			DBG_LVL_INFO
#endif

#ifndef FW_DW_DBG_LVL
#define FW_DW_DBG_LVL           DBG_LVL_WARNING
#endif

#if (SMP_FEATURE)
#ifndef SMP_APP
#define SMP_APP TRUE
#endif
#else
#ifndef SMP_APP
#define SMP_APP FALSE
#endif
#endif /* SMP_FEATURE */
#if (SMP_APP == TRUE)
#define SMP_APP_DBG_LVL			DBG_LVL_WARNING
#endif

#ifndef AES_INTERNAL
#define AES_INTERNAL FALSE
#endif

#ifndef USE_BLUEZ_SOCKET
#define USE_BLUEZ_SOCKET FALSE
#endif

/* Defines SIZE of Transaction ID in bytes that will be used to represent
 * Combination of Route ID, High Level App ID/Handle, Low Level App ID/Handle
 * */
#ifndef TRANS_ID_SIZE_BYTES
	#define TRANS_ID_SIZE_BYTES (2)
#endif

#endif /* CONFIG_H_ */
