/** @file
  COC test application header definitions.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef L2CAP_COC_TEST_APP_H_
#define L2CAP_COC_TEST_APP_H_

#define L2CAP_COC_LE_DYNAMIC_PSM	0x0080
#define L2CAP_COC_LE_MTU			46 /* To be tuned as per use cases */

typedef struct
{
	/* True if coc_handle is open otherwise false */
	BOOLEAN coc_handle_idx_list [MAX_NUMBER_OF_L2CAP_COC_CHNL];
} conn_id_coc_handle_t;

typedef struct
{
	UINT8 app_handle;
	conn_id_coc_handle_t conn_id_coc_handle[MAX_NUM_CONNECTED_DEVICE];
} l2cap_coc_test_app_data_t;

#endif /* L2CAP_COC_TEST_APP_H_ */
