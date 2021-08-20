/** @file
  Userial layer header.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef TL_H_
#define TL_H_

#include "bt_types.h"

INT8 tl_init(char* device, int ispeed);
INT8 tl_write(UINT8 *buffer, UINT16 len);
void tl_recv_msg(UINT8 *buffer);
void tl_close();

#endif /* TL_H_ */
