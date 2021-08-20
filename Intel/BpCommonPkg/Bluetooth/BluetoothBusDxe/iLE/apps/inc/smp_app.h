/** @file
  Security manager application header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef SMP_APP_H_
#define SMP_APP_H_

typedef struct _smp_app_
{
	UINT8 app_handle;
	UINT8 remote_bdaddr[BD_ADDR_LEN];
	UINT8 remote_bdaddr_type;
}smp_app_t;

#endif /* SMP_APP_H_ */
