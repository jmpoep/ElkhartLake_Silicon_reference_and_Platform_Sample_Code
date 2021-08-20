/** @file
  HID header definitions.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef UHID_HOST_H_
#define UHID_HOST_H_

#define MOUSE_DEFAULT_REPORT_ID		1
#define KEYBOARD_DEFAULT_REPORT_ID	2

int uhid_open(char* device, unsigned char *rdesc, int size);
int uhid_send(int fd, buffer_t *buffer);
void uhid_close(int fd);

#endif /* UHID_HOST_H_ */
