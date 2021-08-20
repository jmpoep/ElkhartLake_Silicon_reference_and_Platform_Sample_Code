/** @file
  ATP production app header definations.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef ATP_PRODUCTION_H_
#define ATP_PRODUCTION_H_

#undef DEVICE_NAME
#if defined(CFG_POWER_KPI_30)
    #if defined(CFG_ATP_ADV_1SEC_PRODUCTION) || defined(CFG_ATP_ADV_60MS_PRODUCTION)
            // Force a long name so its easier to measure the TX power
            #define DEVICE_NAME                 "ATP_ADV_KPI30_0123456789"

    #else
            #error Illegal build combination, should only build KPI-30 advertising tests!
    #endif
#else
    #if defined(CFG_ATP_ADV_1SEC_PRODUCTION) || defined(CFG_ATP_ADV_60MS_PRODUCTION)
            #define DEVICE_NAME                 "ATP_ADV"
    #else
        // defined(CFG_ATP_CONN_1SEC_PRODUCTION)) || defined(CFG_ATP_CONN_150MS_PRODUCTION)
            #define DEVICE_NAME                 "ATP_CON"
    #endif
#endif

#define ATP_BT_CORE_STACK_INIT              1
#define ATP_RES_ADAPTER_ENABLED             2
#define ATP_RES_DEVICE_CONNECTED            3

#define ATP_RES_SCAN_COMPLETED              5

#define ATP_SCAN_TIMEOUT_SEC                6

typedef struct
{
    UINT8 opcode;
    UINT8 *param;
} atp_req_elem_t;


typedef struct
{
    BOOLEAN atp_app_running;
    BOOLEAN atp_app_closing;
    BOOLEAN atp_is_connected;
    BOOLEAN is_atp_read_req_pending;
    UINT8 atp_res_code;
    UINT8 app_handle;
    UINT8 num_discovered_devices;
    UINT8 remote_bd_addr[BD_ADDR_LEN];
    UINT8 conn_id;
    queue_t atp_res_q;
    UINT8 num_of_discover_req;
    discovered_device_t discovered_list[MAX_NUM_DISCOVERED_DEVICE];
    osa_semaphore_t msg_sem;
    osa_semaphore_t thread_sem;
} atp_prod_data_t;

#endif /* ATP_PRODUCTION_H_ */
