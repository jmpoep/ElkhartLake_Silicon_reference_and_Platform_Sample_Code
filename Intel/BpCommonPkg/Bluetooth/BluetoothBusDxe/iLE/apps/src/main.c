/** @file
  Main application implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "app_interface.h"
#include "config_host.h"
#include "storage.h"
#if (STRESS_TEST_SUITE == TRUE)
#include <unistd.h>
#include <stdlib.h>
#endif

#if (HCI2ILE_ADAPT_APP == TRUE)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "bt_types.h"
#include "hci2ile_interface.h"
#include "hci2ile_internal.h"
#include "utils.h"

/* Max number of App Processors using 1 stack */
#define MAX_NUM_OF_AP       (4)
#define FREE_SLOT           (-1)
#define MAX_EVENTS          (64)

#define READ_HOST_ID(TRANS_ID)      		((TRANS_ID & ROUTE_ID_BIT_MASK) >> SIZE_OF_HLA_OP_ID_BITS)
#define READ_HLA_OP_ID(TRANS_ID)    		(TRANS_ID & HLA_OP_ID_BIT_MASK)
#define SET_HOST_ID(TRANS_ID, HOST_ID)      (TRANS_ID = ((TRANS_ID & ~(ROUTE_ID_BIT_MASK)) | ((HOST_ID & ROUTE_ID_VALUE_BITS) << SIZE_OF_HLA_OP_ID_BITS)))
static UINT8 no_of_clients;
static BOOLEAN stack_initalized;
#endif

#define ILE_STACK_INT_CMD 0xFC85

#define MODULE_DBG_LVL MAIN_APP_DBG_LVL
#include "log.h"

extern osa_semaphore_t stack_thread_sem;

void display_all_commands()
{
	int app_idx, cmd_idx;

	for (app_idx = 0; app_idx < MAX_NUMBER_OF_APP; app_idx++)
	{
		if (app_cmd_list[app_idx].cmd_arr)
		{
			for (cmd_idx = 0;; cmd_idx++)
			{
				if (strcmp(app_cmd_list[app_idx].cmd_arr[cmd_idx].cmd_str, "_end_") == 0)
					break;
				logln("%s_%s", app_cmd_list[app_idx].app_prefix, app_cmd_list[app_idx].cmd_arr[cmd_idx].cmd_str);
			}
		}
	}
#if (STRESS_TEST_SUITE == TRUE)
	logln("stress_enable_disable");
#endif
	logln("help");
	logln("quit");
}

INT8 find_and_call_handler(char *cmd)
{
	int app_idx, cmd_idx, prefix_len;

	if (!cmd)
		return STATUS_ERR_INVALID_PARAM;

	for (app_idx = 0; app_idx < MAX_NUMBER_OF_APP; app_idx++)
	{
		if (!app_cmd_list[app_idx].app_prefix)
			continue;

		prefix_len = strlen(app_cmd_list[app_idx].app_prefix);
		if (app_cmd_list[app_idx].cmd_arr && (!strncmp(cmd, app_cmd_list[app_idx].app_prefix, prefix_len)))
		{
			for (cmd_idx = 0;; cmd_idx++)
			{
				if (!strcmp(app_cmd_list[app_idx].cmd_arr[cmd_idx].cmd_str, &cmd[prefix_len+1]))
				{
					app_cmd_list[app_idx].cmd_arr[cmd_idx].handler(NULL);
					return STATUS_SUCCESS;
				}
				if (!strcmp(app_cmd_list[app_idx].cmd_arr[cmd_idx].cmd_str, "_end_"))
					return STATUS_ERR_OPERATION_NOT_SUPPORTED;
			}
		}
	}
	return STATUS_ERR_UNKNOWN;
}

INT8 lestack_init()
{
#if ((LE_STACK_PROFILING == TRUE) && (TARGET_THREADX == TRUE))
	log_time_stamp(TIME_STACK_INIT_STARTED);
#endif
	trans_id_t trans_id = 0;
	iLE_stack_init(trans_id);

	memset(app_cmd_list, 0, sizeof(app_cmd_list));

	return STATUS_SUCCESS;
}

BOOLEAN lestack_cleanup()
{
#if (A4WP_APP == TRUE)
	a4wp_cleanup(NULL);
#endif

#if (GAP_GATT_SRV_APP == TRUE)
	gap_gatt_service_cleanup(NULL);
#endif

#if (TEST_APP == TRUE)
	test_app_cleanup();
#endif

#if (HRP_APP == TRUE)
	hrp_cleanup();
#endif

#if (FMP_APP == TRUE)
	fmp_cleanup(NULL);
#endif

#if (FMP_SRV_APP == TRUE)
	fmp_srv_cleanup(NULL);
#endif

#if (SMP_APP == TRUE)
	smp_app_cleanup(NULL);
#endif

#if (L2CAP_COC_TEST_APP == TRUE)
	l2cap_coc_test_app_cleanup();
	test_app1_cleanup();
#endif

#if (HOGP_APP == TRUE)
	hogp_cleanup(NULL);
#endif

#if (ATP_AUTO_TEST_MODE == TRUE)
	atp_app_cleanup();
#endif

#if (HCI2ILE_ADAPT_APP == TRUE)
	adapt_app_cleanup();
#endif

	osa_semaphore_get(&stack_thread_sem);
	osa_semaphore_delete(&stack_thread_sem);

#if (THREADLESS_STACK == FALSE)
	osa_thread_join(STACK_MAIN_THREAD, NULL);
#else
	osa_thread_join(USERIAL_READ_THREAD, NULL);
#endif

	return TRUE;
}
#if (HCI2ILE_ADAPT_APP == TRUE)

struct epoll_event Event;
struct epoll_event event[MAX_EVENTS];

int EpollFd, serv_sockfd;

/* Client Socket FD list */
int sockfd_list[MAX_NUM_OF_AP] = {FREE_SLOT,FREE_SLOT,FREE_SLOT,FREE_SLOT};

static int get_free_sockfd_list_index()
{
    int i;
    for(i = 0; i < MAX_NUM_OF_AP; ++i)
    {
        if(sockfd_list[i] == FREE_SLOT) /* Free slot found */
        {
            return i;
        }
    }
    return MAX_NUM_OF_AP;
}

/* Returns 0 on success and negative value on error */
static int add_to_client_list(int sockfd)
{
    int index = get_free_sockfd_list_index();
    if(index < MAX_NUM_OF_AP)
    {
        printf("\nSocket Client Connected(SockID:%u, HostID:%u)\n", sockfd, index);
        sockfd_list[index] = sockfd;
        return 0;
    }

    return -1;
}

static void remove_from_client_list(int sockfd)
{
    int i;
    for(i = 0; i < MAX_NUM_OF_AP; ++i)
    {
        if(sockfd_list[i] == sockfd)
        {
            sockfd_list[i] = FREE_SLOT;
            break;
        }
    }
}

static int get_host_id(int sockfd)
{
    int i;
    for(i = 0; i < MAX_NUM_OF_AP; ++i)
    {
        if(sockfd_list[i] == sockfd)
            return i;
    }
    return -1;
}

static int get_sock_fd(int host_id)
{
    if(host_id < MAX_NUM_OF_AP)
    {
        return sockfd_list[host_id];
    }
    return -1;
}

void error(const char *msg)
	{
		perror(msg);
     		exit(1);
   	}

/* START: Code to synchronize 'Status Event' and 'Debug Event' from Stack + command logging feature*/

const char* get_curr_time()
{
	time_t current_time;
	struct tm * time_info;
	static char timeString[9];  // space for "HH:MM:SS\0"

	time(&current_time);
	time_info = localtime(&current_time);

	strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
	return timeString;
}

unsigned long get_curr_time_ms()
{
    unsigned long   ms; // Milliseconds
    struct timespec t_spec;
    clock_gettime(CLOCK_REALTIME, &t_spec);
    ms = t_spec.tv_nsec / 1000000; // Convert nanoseconds to milliseconds
    return ms;
}

/** @brief This is a utility function that can be used by an Application for logging purpose.
 *
 * Function: get_hci_command_name
 * 			 This function returns HCI Command name for the passed API ID.
 *
 * @param api_id - API ID of HCI Command passed to adaptation layer
 * 				   via hci2ile_command_dispatch_req function.
 * @return HCI Command Request Name.
 */
const char* get_hci_command_name(UINT8 api_id)
{
	switch(api_id)
	{
		case HCI2ILE_SET_ADVERTISEMENT_DATA:
		   return "Set Adv Data";
		case HCI2ILE_REMOVE_ADVERTISEMENT_DATA:
		   return "Remove Adv Data";
		case HCI2ILE_START_DISCOVERABLE:
		   return "Start Adv";
		case HCI2ILE_STOP_DISCOVERABLE:
		   return "Stop Adv";
		case HCI2ILE_SET_LOCAL_DEVICE_NAME:
		   return "Set Local Device Name";
		case HCI2ILE_START_SCAN:
		   return "Start Scan";
		case HCI2ILE_STOP_SCAN:
		   return "Stop Scan";
		case HCI2ILE_CONNECT:
		   return "Connect";
		case HCI2ILE_DISCONNECT:
		   return "Disconnect";
		case HCI2ILE_ADD_TO_WHITELIST:
		   return "Add To White List";
		case HCI2ILE_REMOVE_FROM_WHITELIST:
		   return "Remove from White List";
		case HCI2ILE_CLEAR_WHITELIST:
		   return "Clear White List";
		case HCI2ILE_CREATE_BOND:
		   return "Create Bond";
		case HCI2ILE_REMOVE_BOND:
		   return "Remove Bond";
		case HCI2ILE_SET_IO_CAPABILITIES:
			return "Set IO Capabilities";
		case HCI2ILE_SEND_PASSKEY:
		   return "Set Passkey";
		case HCI2ILE_SEND_AUTHORIZATION:
		   return "Send Auth";
		case HCI2ILE_SMP_REGISTER:
		   return "Smp Register App";
		case HCI2ILE_GET_ATTRIBUTE_MTU:
		   return "Get ATT MTU";
		case HCI2ILE_SET_ATTRIBUTE_MTU:
		   return "Set ATT MTU";
		case HCI2ILE_UPDATE_CONN_PARAMS:
		   return "Update Conn Params";
		case HCI2ILE_L2CAP_COC_REGISTER:
		   return "L2CAP COC Register App";
		case HCI2ILE_L2CAP_COC_CONNECT_REQ:
		   return "L2CAP COC Connect Req";
		case HCI2ILE_L2CAP_COC_DISCONNECT_REQ:
		   return "L2CAP COC Disconnect Req";
		case HCI2ILE_L2CAP_COC_SEND_DATA:
		   return "L2CAP COC Send Data";
		case HCI2ILE_ADD_SERICE:
		   return "GATT Add Service";
		case HCI2ILE_ADD_INCLUDED_SERVICE:
			return "GATT Add Included Service";
		case HCI2ILE_ADD_CHARACTERISTIC:
		   return "GATT Add Char";
		case HCI2ILE_ADD_DESCRIPTOR:
		   return "GATT Add Desc";
		case HCI2ILE_START_SERVICE:
		   return "GATT Start Service";
		case HCI2ILE_REMOVE_SERVICE:
		   return "GATT Remove Service";
		case HCI2ILE_SEND_ATTRIBUTE_READ_RSP:
		   return "GATT Attr Read Resp";
		case HCI2ILE_SEND_ATTRIBUTE_WRITE_RSP:
		   return "GATT Attr Write Resp";
		case HCI2ILE_SEND_NOTIFICATION:
		   return "GATT Send Notification";
		case HCI2ILE_DISCOVER_PRIMARY_SERVICE:
		   return "GATT Discover Primary Service";
		case HCI2ILE_DISCOVER_INCLUDED_SERVICE:
		   return "GATT Discover Included Service";
		case HCI2ILE_DISCOVER_CHARACTERISTIC:
		   return "GATT Discover Char";
		case HCI2ILE_DISCOVER_DESCRIPTOR:
		   return "GATT Discover Desc";
		case HCI2ILE_READ_ATTRIBUTE_VALUE:
		   return "GATT Read Attr Value";
		case HCI2ILE_WRITE_ATTRIBUTE_VALUE:
		   return "GATT Write Attr Value";
		case HCI2ILE_REGISTER_NOTIFICATION:
		   return "GATT Register Notification";
		case HCI2ILE_SEND_HCI_COMMAND:
			return "Send HCI Command";
		case HCI2ILE_TEST_ENABLE_PRIVACY:
			return "Enable Privacy";
		case HCI2ILE_TEST_READ_AUTHENTICATED_PAYLOAD_TOUT:
			return "Read Authenticated Payload Timeout";
		case HCI2ILE_TEST_WRITE_AUTHENTICATED_PAYLOAD_TOUT:
			return "Write Authenticated Payload Timeout";
		case HCI2ILE_SET_DATA_LEN:
			return "Set Data Length";
		case HCI2ILE_TEST_SET_BD_ADDRESS:
			return "Set BD Address";
		case HCI2ILE_SMP_SEND_NC_RESULT:
			return "SMP Send NC Result";
		case HCI2ILE_KEY_RESPONSE:
			return "Key Response";
		case HCI2ILE_REGISTER_STORAGE:
			return "Register storage";

	}
    printf("\nAPI ID: 0x%02X(%d)\n",api_id,api_id);
	return "Unknown API ID";
}

/** @brief This is a utility function that can be used by an Application for logging purpose.
 *
 * Function: get_hci_callback_command_name
 * 			 This function returns HCI Command response name for the passed Callback ID.
 *
 * @param callback_id - Callback ID of HCI Command received from Adaptation Layer
 * 				   		via hci2ile_Event_Dispatch_cb_t function.
 * @return HCI Command Response Name.
 */
const char* get_hci_command_callback_name(UINT8 callback_id)
{
	switch(callback_id)
	{
		case HCI2ILE_CB_ID_ON_MTU_CHANGED:
		   return "MTU Changed";
		case HCI2ILE_CB_ID_ON_SERVICE_ADDED:
		   return "Service Added";
		case HCI2ILE_CB_ID_ON_INCLUDED_SERVICE_ADDED:
			return "Include Service Added";
		case HCI2ILE_CB_ID_ON_SERVICE_REMOVED:
		    return "Service Removed";
		case HCI2ILE_CB_ID_ON_CHARACTERISTIC_ADDED:
		   return "Char Added";
		case HCI2ILE_CB_ID_ON_DESCRIPTOR_ADDED:
		   return "Desc Added";
		case HCI2ILE_CB_ID_ON_SERVICE_STARTED:
		   return "Service Started";
		case HCI2ILE_CB_ID_ON_PRIMARY_SERVICE_DISCOVERED:
		   return "Primary Service Discovered";
		case HCI2ILE_CB_ID_ON_INCLUDED_SERVICE_DISCOVERED:
		   return "Included Service Discovered";
		case HCI2ILE_CB_ID_ON_CHARACTERISTIC_DISCOVERED:
		   return "Char Discovered";
		case HCI2ILE_CB_ID_ON_DESCRIPTOR_DISCOVERED:
		   return "Desc Discovered";
		case HCI2ILE_CB_ID_ON_ATTRIBUTE_READ:
		   return "Attr Read Completed";
		case HCI2ILE_CB_ID_ON_ATTRIBUTE_WRITE:
		   return "Attr Write Completed";
		case HCI2ILE_CB_ID_ON_NOTIFICATION:
		   return "Notification Received";
		case HCI2ILE_CB_ID_ON_NOTIFICATION_REGISTERED:
		   return "Notification Registered";
		case HCI2ILE_CB_ID_ON_CONNECTED:
		   return "Connection Completed";
		case HCI2ILE_CB_ID_ON_DISCONNECTED:
		   return "Disconnection Completed";
		case HCI2ILE_CB_ID_ON_ATTRIBUTE_READ_REQ: 	/* GATT Server callback */
		   return "Attr Read Req Received";
		case HCI2ILE_CB_ID_ON_ATTRIBUTE_WRITE_REQ:	/* GATT Server callback */
		   return "Attr Write Req Received";
		case HCI2ILE_CB_ID_ON_EXEC_WRITE_REQ:
		   return "Exec Write Req Received";
		case HCI2ILE_CB_ID_ON_INDICATION_CONFIRMATION:
		   return "Indication Confirmation Received";
		case HCI2ILE_CB_ID_SCAN_RESULTS_CB:
		   return "Scan Result Received";
		case HCI2ILE_CB_ID_SCAN_COMPLETED_CB:
		   return "Scan Completed";
		case HCI2ILE_CB_ID_STACK_INITIALIZED_CB:
		   return "Stack Initialized";
		case HCI2ILE_CB_ID_BONDING_COMPLETED_CB:
		   return "Bond Completed";
		case HCI2ILE_CB_ID_DATA_SIGNING_COMPLETED:
		   return "Data Signing Completed";
		case HCI2ILE_CB_ID_SMP_CB:
		   return "SMP Callback Event";
		case HCI2ILE_CB_ID_LC_REGISTER_CB:
		   return "L2CAP COC App Registered";
		case HCI2ILE_CB_ID_LC_AUTHORISATION_CB:
		   return "L2CAP COC Auth Completed";
		case HCI2ILE_CB_ID_LC_CONNECTION_CMPL_CB:
		   return "L2CAP COC Connection Completed";
		case HCI2ILE_CB_ID_LC_FLOW_CONTROL_CB:
		   return "L2CAP COC Flow Control Received";
		case HCI2ILE_CB_ID_LC_RECV_DATA_CB:
		   return "L2CAP COC Data Received";
		case HCI2ILE_CB_ID_LC_DISCONNECTION_CMPL_CB:
		   return "L2CAP COC Disonnection Completed";
		case HCI2ILE_CB_ID_ON_READ_AUTH_PAYLOAD_TIMEOUT_CB:
			return "Read Authenticated Payload Timeout";
		case HCI2ILE_CB_ID_ON_DATA_LEN_CHANGE_EVT_CB:
			return "Data Length Changed";
		case HCI2ILE_CB_ID_ON_KEY_REQ_CB:
			return "Key request";
		case HCI2ILE_CB_ID_ON_STORAGE_REGISTER_REQ_CB:
			return "storage registration request";
		case HCI2ILE_CB_ID_ON_KEY_UPDATE_CB:
			return "Key update";
		case HCI2ILE_CB_ID_ON_LINK_ENC_CHANGED_CB:
			return "link encryption changed";
	}
	return "Unknown Callback ID";
}

/* Structures and functions for retaining Debug Event data */
typedef struct _event_data_t
{
	UINT16 op_code;
	UINT8  len;
	UINT8 *hci_data;
}event_data_t;

static event_data_t status_evt, dbg_evt;
pthread_mutex_t event_mutex;
pthread_cond_t event_cond;
UINT8 event_count = 2; /*To count Status Event, Debug Event*/

static void clear_event_data()
{
	app_dealloc(status_evt.hci_data);
	memset(&status_evt,0, sizeof(event_data_t));
	app_dealloc(dbg_evt.hci_data);
	memset(&dbg_evt,0, sizeof(event_data_t));
	event_count = 2; /* Reset count */
}

/* For below set of API IDs we should wait for Status Event and Debug Event
 * to complete. Then send events to Client
 * For below commands Debug Events comes first in Linux
 * */
BOOLEAN is_wait_for_event(UINT8 api_id)
{
	switch(api_id)
	{
		case HCI2ILE_ADD_SERICE:
		case HCI2ILE_ADD_INCLUDED_SERVICE:
		case HCI2ILE_START_SERVICE:
		case HCI2ILE_ADD_CHARACTERISTIC:
		case HCI2ILE_ADD_DESCRIPTOR:
		case HCI2ILE_REGISTER_NOTIFICATION:
		{
			return TRUE;
		}
	}
	return FALSE;
}

UINT8 get_api_id_by_callback_id(UINT8 callback_id)
{
	switch(callback_id)
	{
		case HCI2ILE_CB_ID_ON_SERVICE_ADDED:
			return HCI2ILE_ADD_SERICE;

		case HCI2ILE_CB_ID_ON_INCLUDED_SERVICE_ADDED:
			return HCI2ILE_ADD_INCLUDED_SERVICE;

		case HCI2ILE_CB_ID_ON_SERVICE_STARTED:
			return HCI2ILE_START_SERVICE;

		case HCI2ILE_CB_ID_ON_CHARACTERISTIC_ADDED:
			return HCI2ILE_ADD_CHARACTERISTIC;

		case HCI2ILE_CB_ID_ON_DESCRIPTOR_ADDED:
			return HCI2ILE_ADD_DESCRIPTOR;

		case HCI2ILE_CB_ID_ON_NOTIFICATION_REGISTERED:
			return HCI2ILE_REGISTER_NOTIFICATION;
	}

	return 0xFF;/* Callback ID Not found */
}

/* Returns TRUE if the function was waiting for command complete */
BOOLEAN wait_for_cmd_complete(UINT8 api_id)
{
	BOOLEAN status = FALSE;
	if(is_wait_for_event(api_id) == TRUE)
	{
		status = TRUE;
		while(event_count != 0)
			pthread_cond_wait(&event_cond, &event_mutex);
	}
	return status;
}

static void decrement_event_count()
{
	--event_count;
	if(event_count == 0){
		pthread_cond_signal(&event_cond);
	}
}

static void copy_status_event(UINT16 op_code, UINT8 len, UINT8 *hci_data)
{
	//printf("\ncopy_status_event\n");
	status_evt.op_code  = op_code;
	status_evt.len	 = len;
	status_evt.hci_data = app_alloc(len);
	memcpy(status_evt.hci_data, hci_data, len);
	decrement_event_count();
}

static void copy_debug_event(UINT16 op_code, UINT8 len, UINT8 *hci_data)
{
	//printf("\ncopy_debug_event\n");
	dbg_evt.op_code  = op_code;
	dbg_evt.len	 = len;
	dbg_evt.hci_data = app_alloc(len);
	memcpy(dbg_evt.hci_data, hci_data, len);
	decrement_event_count();
}

static ssize_t write_to_client(UINT8 host_id, const char *buf, size_t buf_len)
{
    ssize_t n = 0;
    /* Extract host_id from buffer */
    int sockfd = -1, i;
    if(host_id == INVALID_ROUTE_ID) /* Broadcast to All existing APs */
    {
        printf("\nBroadcast\n");
        for(i = 0; i < MAX_NUM_OF_AP; ++i)
        {
            if(sockfd_list[i] != FREE_SLOT)
                n = write(sockfd_list[i], buf, buf_len);
        }
    }
    else
    {
        sockfd = get_sock_fd(host_id);
        if(sockfd > 0)
        {
            n = write(sockfd, buf, buf_len);
        }
        else
            printf("Invalid host_id:%u received from Stack !!!\n",host_id);
    }

    return n;
}

/* Helper function */
static void send_status_event(UINT16 op_code, UINT8 len, UINT8 * u8HCIdata)
{
    /* u8HCIdata from Stack
     * ----------------------------------------------------------------------
     * | Status (1 Byte) | Trans_id (TRANS_ID_SIZE_BYTES) | API-ID (1 Byte) |
     * ----------------------------------------------------------------------
     * */
	char buffer[256] = { 0x01, 0x00, 0x00, 0x00, 0x04, 0x0E, len + 3, 0x01, 0x80, 0xFC };
	UINT8 i, host_id, *p = (u8HCIdata + 1); /* Point to trans id */
	int n = 0;
    trans_id_t trans_id;

    /* Read Host Id from Status Event Packet */
    //printf("Trans_ID Stream:0x%02X 0x%02X\n", p[0], p[1]);
    STREAM_TO_TRANS_ID(trans_id, p);
    host_id = READ_HOST_ID(trans_id); /* Note: host_id is irrelevant to upper layer */

    printf("\n\n <----(HostID:%u(%d), OpID:%u) Status Event: %s\n", host_id, get_sock_fd(host_id),
            READ_HLA_OP_ID(trans_id), get_hci_command_name(p[0]/*api_id*/));

	for (i = 0; i < len; i++)
		buffer[i + 10] = u8HCIdata[i];

	/* Print the Status Event */
	for (i = 0; i <= (len + 9); i++)
		printf("%02x:", (UINT8) buffer[i]);
	printf("\n");

	n = write_to_client(host_id, buffer, len + 10);
	if (n < 0)
		error("ERROR writing to socket");
	bzero(buffer, 256);
}

/* Helper function */
static void send_debug_event(UINT16 op_code, UINT8 len, UINT8 * u8HCIdata)
{
    /* u8HCIdata from Stack
     * ---------------------------------------------------------------------------------------------
     * | Event ID (1 Byte) | Trans_id (TRANS_ID_SIZE_BYTES) | Callback ID (1 Byte) | Callback params
     * ---------------------------------------------------------------------------------------------
     * */

	UINT8 i, *p, host_id;
	int n;
	char buffer[256] = { 0x01, 0x00, 0x00, 0x00, 0x04, 0xFF, len };
    trans_id_t trans_id;

    p = u8HCIdata + 1; /* Skip Event ID */
	STREAM_TO_TRANS_ID(trans_id, p);
	host_id = READ_HOST_ID(trans_id);  /* Note: host_id is irrelevant to upper layer */

	printf("\n\n <----(HostID:%u(%d), OpID:%u) Debug Event: %s\n", host_id, get_sock_fd(host_id),
	        READ_HLA_OP_ID(trans_id), get_hci_command_callback_name(p[0]/*callback_id*/));

	for (i = 0; i < len; i++)
		buffer[i + 7] = u8HCIdata[i];

	/* Print the Debug Event */
	for (i = 0; i < (len + 7); i++)
		printf("%02x:", (UINT8) buffer[i]);
	printf("\n");

	n = write_to_client(host_id, buffer, len + 7);
	if (n < 0)
		error("ERROR writing to socket");

	usleep(20000); /* Delay back to back debug event for 3vt/py_test_main to read it properly */
}

/* END: Code to synchronize 'Status Event' and 'Debug Event' from Stack + command logging feature*/

void ile2socket_status_event(UINT16 op_code, UINT8 len, UINT8 * u8HCIdata)
{
	/* u8HCIdata from Stack
	 * ----------------------------------------------------------------------
	 * | Trans_id (TRANS_ID_SIZE_BYTES) | Status (1 Byte) | API-ID (1 Byte) |
	 * ----------------------------------------------------------------------
	 * */
    UINT8 api_id = u8HCIdata[TRANS_ID_SIZE_BYTES + 1];
	if (is_wait_for_event(api_id) == TRUE)
	{
		copy_status_event(op_code, len, u8HCIdata);
		return;
	}
	send_status_event(op_code, len, u8HCIdata);
}

void ile2socket_debug_event(UINT16 op_code, UINT8 len, UINT8 * u8HCIdata)
{
	/* u8HCIdata from Stack
	 * ---------------------------------------------------------------------------------------------
	 * | Event ID (1 Byte) | Trans_id (TRANS_ID_SIZE_BYTES) | Callback ID (1 Byte) | Callback params
	 * ---------------------------------------------------------------------------------------------
	 * */
	UINT8 callback_id = u8HCIdata[1 + TRANS_ID_SIZE_BYTES];
	UINT8 api_id = 0xFF; /* 0xFF - Invalid API ID */
	api_id = get_api_id_by_callback_id(callback_id);
	if (is_wait_for_event(api_id) == TRUE)
	{
		copy_debug_event(op_code, len, u8HCIdata);
		return;
	}
	send_debug_event(op_code, len, u8HCIdata);
}

void print_command(UINT8 *buffer, UINT8 buffer_len)
{
	int i = 0;
	for (; i < buffer_len; i++)
		printf("%02x:", (UINT8) buffer[i]);
	printf("\n");
}

/* creates server socket, bind it to IN_ADDRY ANY and returns socket fd */
static int create_and_bind(int serv_port)
{
    struct sockaddr_in serv_addr;
    int serv_sockfd;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(serv_port);

    serv_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(serv_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))
            < 0) {
        error("ERROR on binding");
        close(serv_sockfd);
        serv_sockfd = -1;
    }

    return serv_sockfd;
}

static int make_non_blocking(int sockfd)
{
    int flags, s;
    flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl(sockfd, F_SETFL, flags);
    if (s == -1) {
        perror("fcntl");
        return -1;
    }

    return 0;
}

/* Returns socket fd of new connected client */
static void handle_new_connection()
{
    int sockfd = -1;
    struct sockaddr in_addr;
    socklen_t in_len;
    in_len = sizeof(in_addr);
    sockfd = accept(serv_sockfd, &in_addr, &in_len);
    if ((sockfd == -1) && (errno != EAGAIN) && (errno != EWOULDBLOCK))
    {
        perror("accept");
        return;
    }

    /* Make the incoming socket non-blocking */
    make_non_blocking(sockfd);

    Event.data.fd = sockfd;
    Event.events = EPOLLIN;
    if(epoll_ctl(EpollFd, EPOLL_CTL_ADD, sockfd, &Event) < 0)
    {
        perror("epoll_ctl");
        return;
    }

    /* Add new client socket connection to client list */
    add_to_client_list(sockfd);
}

static INT8 check_initialize_stack(int sockfd, char buffer[])
{
	UINT8 *p = (UINT8*)&buffer[13];
	UINT16 op_code;
	STREAM_TO_UINT16(op_code,p);
	if(op_code != ILE_STACK_INT_CMD)
		 return STATUS_ERR_INVALID_PARAM;
	if (lestack_init() != STATUS_SUCCESS)
	{
		if(g_local_adapter.uart_port_name)
			app_dealloc(g_local_adapter.uart_port_name);
		return -(STATUS_ERR_STACK_NOT_INIT);
	}
	stack_initalized = TRUE;
	return STATUS_SUCCESS;
}

/* Extracts the command packet from buffer and dispatches it to Adaptation Layer */
static void dispatch_cmd(int sockfd, char buffer[])
{
    UINT8 *p = (UINT8*)&buffer[13], *cmd;
    UINT8 cmd_len;
    UINT16 op_code;
    trans_id_t trans_id = 0;
    int host_id = get_host_id(sockfd);

   STREAM_TO_UINT16(op_code,p);
    /* p points to below buffer
     * ------------------------------------------------------------
     * | Cmd Length (1 Byte) | API ID (1 Byte) | Trans ID(2 Bytes)|
     * ------------------------------------------------------------
     * */
   cmd_len = p[0];
   cmd = p + 1;
   p += 2; /* Point to trans_id stream */

    if(cmd_len != 0)
    {
        /* Read trans_id data from stream, set host_id in it and set it back to stream */
        //printf("Trans_ID Stream:0x%02X 0x%02X\n", p[0], p[1]);
        STREAM_TO_TRANS_ID(trans_id, p);
        SET_HOST_ID(trans_id, host_id);
        p -= TRANS_ID_SIZE_BYTES;
        TRANS_ID_TO_STREAM(p, trans_id);

        printf("\n\n ---->(HostID:%u(%d), OpID:%u) HCI Command: %s\n",
                host_id, sockfd, READ_HLA_OP_ID(trans_id), get_hci_command_name(cmd[0]/*api_id*/));
        print_command(cmd, cmd_len);
        hci2ile_command_dispatch_req(op_code, cmd_len , cmd);

        /* To avoid the inconsistent order of events(Status,Debug Event) received
         * for local api calls, we need the logic below.
         * Below code will be executed only for those API calls for that
         * both Status Event & Debug Event is expected
         * Status Event and Debug Event is Queued first
         * then sent sequentially
         * */
        if(wait_for_cmd_complete(cmd[0]/*api_id*/) == TRUE)
        {
            send_status_event(status_evt.op_code, status_evt.len,status_evt.hci_data);
            usleep(10000);/*in micro seconds (1 sec = 1,000,000 millisec), sleeps 0.1 sec (100 millisec) */
            send_debug_event(dbg_evt.op_code, dbg_evt.len,dbg_evt.hci_data);
            clear_event_data();
        }
    }
}
#endif

#if (TARGET_LINUX == TRUE)
#if (HCI2ILE_ADAPT_APP != TRUE)
int main(int argc, char *argv[])
{
#if ((TARGET_LINUX == TRUE) && (TARGET_ANDROID == FALSE))
	record_start_time();
#endif
	char cmd[128];
	char *ret;

	logd("MAIN \n");

#if (STORAGE_INCLUDED == TRUE)
	open_storage_file(LOCAL_STORAGE_FILE_LOCATION);
#endif

	g_local_adapter.uart_port_name = NULL;
	if (argc > 1)
	{
		logd("%s",argv[1]);
		if ((g_local_adapter.uart_port_name = (char*) app_alloc (strlen(argv[1]) + 1)) == NULL)
			return -1;
		strcpy(g_local_adapter.uart_port_name, argv[1]);
	}

	if (lestack_init() != STATUS_SUCCESS)
	{
		if(g_local_adapter.uart_port_name)
			app_dealloc(g_local_adapter.uart_port_name);
		return -(STATUS_ERR_STACK_NOT_INIT);
	}

	while (1)
	{
		log("$ ");
		ret = fgets(cmd, sizeof(cmd), stdin);
		USE(ret);
		cmd[strlen(cmd) - 1] = '\0';

		if (!strcmp(cmd, "quit"))
			break;

#if (STRESS_TEST_SUITE == TRUE)
		if (!strcmp(cmd, "stress_enable_disable"))
			break;
#endif

		if (!strcmp(cmd, "help"))
		{
			display_all_commands();
			continue;
		}

		if (find_and_call_handler(cmd) != STATUS_SUCCESS)
		{
			logd("No matching command found");
			display_all_commands();
		}
	}

	lestack_cleanup();

#if (STRESS_TEST_SUITE == TRUE)
	if (!strcmp(cmd, "stress_enable_disable"))
	{
		UINT8 i, num = 0;
		log("Number of cycles to execute: ");
		ret = fgets(cmd, sizeof(cmd), stdin);
		USE(ret);
		cmd[strlen(cmd) - 1] = '\0';
		num = (UINT8) atoi(cmd);
		for (i = 0; i < num; i++)
		{
			osa_sleep(1);
			lestack_init();
			osa_sleep(1);
			lestack_cleanup();
		}
	}
#endif

	app_dealloc(g_local_adapter.uart_port_name);

	logd("Stack thread done.");

#if (STORAGE_INCLUDED == TRUE)
	close_storage_file();
#endif

	return STATUS_SUCCESS;
}

#else

int main(int argc, char *argv[])
{
#if ((TARGET_LINUX == TRUE) && (TARGET_ANDROID == FALSE))
	record_start_time();
#endif

	logd("MAIN \n");

#if (STORAGE_INCLUDED == TRUE)
	open_storage_file(LOCAL_STORAGE_FILE_LOCATION);
#endif

	g_local_adapter.uart_port_name = NULL;
	if (argc > 2)
	{
		logd("%s",argv[1]);
		if ((g_local_adapter.uart_port_name = (char*) app_alloc (strlen(argv[1]) + 1)) == NULL)
		return -1;
		strcpy(g_local_adapter.uart_port_name, argv[1]);
	}
	else
	{
		fprintf(stderr,"ERROR, no port provided\n");
		fprintf(stdout,"USAGE: %s [/dev/ttyUSBX] [serv port]\n", argv[0]);
		exit(1);
	}
	no_of_clients = 0;
	stack_initalized = FALSE;
	serv_sockfd = create_and_bind(atoi(argv[2]));
	if (serv_sockfd < 0)
		return -1;

	/* Make server socket non blocking to accept new client connections on the fly */
	make_non_blocking(serv_sockfd);

	if (listen(serv_sockfd, 5) == -1)
	{
		perror("listen");
		return -1;
    }

	EpollFd = epoll_create1(0);
	if (EpollFd == -1)
	{
		perror ("epoll_create");
		return -1;
    }

	hci2ile_initialize(ile2socket_status_event, ile2socket_debug_event);

	/* Monitor server socket fd to listen and accept new connections */
	Event.events = EPOLLIN;
	Event.data.fd = serv_sockfd;
	if (epoll_ctl(EpollFd, EPOLL_CTL_ADD, serv_sockfd, &Event) < 0)
	{
		printf("Error epoll_ctl, adding server socket %d\n", serv_sockfd);
		return -1;
    }

	/* Event loop of epoll */
	while(1)
	{
		int n,i;
		n = epoll_wait(EpollFd, event, MAX_EVENTS, -1); /* Read multiple events */
		for (i = 0; i < n; ++i)
		{
			if ((event[i].events & EPOLLERR) || (event[i].events & EPOLLHUP)
					|| (!(event[i].events & EPOLLIN)))
            {
				/* An error has occured on this fd */
				//fprintf(stderr, "epoll error\n");
				printf("Closed connection on Sock Fd %d\n", event[i].data.fd);
				remove_from_client_list(event[i].data.fd);
				close(event[i].data.fd);
				no_of_clients--;
				if(!no_of_clients)
				{
					break;
                }
				continue;
            }
			else if (event[i].data.fd == serv_sockfd) /* Notification for incoming connection */
			{
				handle_new_connection();
				if(no_of_clients == 0)
				{
#if 0
					if (lestack_init() != STATUS_SUCCESS)
					{
						if(g_local_adapter.uart_port_name)
							app_dealloc(g_local_adapter.uart_port_name);
                    	return -(STATUS_ERR_STACK_NOT_INIT);
                    }
#endif
                }
				no_of_clients++;
            }
			else /* We have data on fds waiting to be read */
			{
				int done = FALSE;
				while (1)
				{
					ssize_t count;
					char buffer[256] = {0};

					count = read(event[i].data.fd, buffer, sizeof(buffer));
					if (count == -1)
					{
						/* If errno == EAGAIN, that means we have read all
                             data. So go back to Event loop of epoll. */
                        if (errno != EAGAIN)
                        {
                        	perror("read");
                        	done = TRUE;
                        }
                        break;
					}
					else if(count == 0)
					{
						/* End of file. The remote has closed the
                             connection. */
						done = TRUE;
						break;
					}
					if(stack_initalized == TRUE)
						dispatch_cmd(event[i].data.fd, buffer);
					else
					{
						check_initialize_stack(event[i].data.fd, buffer);
					}

				}
				if (done)
				{
					printf("Closed connection on Sock Fd %d\n", event[i].data.fd);

					/* Closing the descriptor will make epoll remove it
                         from the set of descriptors which are monitored. */
					remove_from_client_list(event[i].data.fd);
					close(event[i].data.fd);
					no_of_clients--;
					if(!no_of_clients)
					{
						break;
					}
				}
			}
		}
		if(i < n)
			break;
	}
	close(serv_sockfd);
	lestack_cleanup();

	app_dealloc(g_local_adapter.uart_port_name);

	logd("Stack thread done.");

#if (STORAGE_INCLUDED == TRUE)
	close_storage_file();
#endif

	return STATUS_SUCCESS;
}
#endif
#endif /* TARGET_LINUX == TRUE */

#if (TARGET_THREADX == TRUE)
int threadx_main()
{
	lestack_init();
	lestack_cleanup();
	return 0;
}
#endif /* TARGET_THREADX */
