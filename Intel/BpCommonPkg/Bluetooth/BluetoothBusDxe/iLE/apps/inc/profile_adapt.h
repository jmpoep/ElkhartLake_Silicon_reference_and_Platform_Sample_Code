/** @file
  Profile adaptation layer header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef PROFILE_ADAPT_H_
#define PROFILE_ADAPT_H_

/* Use cases */
#define PXP_SERVER_USE_CASE							1
#define PXP_CLIENT_USE_CASE							2
#define FMP_SERVER_USE_CASE							3
#define FMP_CLIENT_USE_CASE							4
#define HRP_SERVER_USE_CASE							5
#define HRP_CLIENT_USE_CASE							6
#define A4WP_SERVER_USE_CASE						7
#define A4WP_CLIENT_USE_CASE						8

void profile_command_recvd(UINT8 *value, UINT8 value_len);

/* Profile call backs */
void profile_device_discovery_completed(UINT8 status, UINT8 use_case,
		UINT8** bd_addr_list, UINT8 num_of_results);

/* Profile APIs to use */

#if (HRP_APP == TRUE)
void hrp_start_discovery (UINT8 *arg);
void hrp_start_use_case (UINT8 *arg);
void hrp_stop_use_case (UINT8 *arg);
void hrp_data_cb(UINT8 hrp_data, UINT8 battery_level);
#endif

#if (FMP_APP == TRUE)
void fmp_start_discovery (UINT8 *arg);
void fmp_start_use_case (UINT8 *arg);
void fmp_stop_use_case (UINT8 *arg);
void fmp_write_alert_level (UINT8 *arg);
#endif

#if (FMP_SRV_APP == TRUE)
void alert_level_data_cb(UINT8 alert_level);
#endif

#endif /* PROFILE_ADAPT_H_ */
