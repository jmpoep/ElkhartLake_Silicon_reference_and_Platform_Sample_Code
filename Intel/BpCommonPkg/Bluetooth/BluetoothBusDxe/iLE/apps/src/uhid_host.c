/** @file
  HID Host application.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "config_host.h"
#include "error_code.h"
#include "bt_types.h"
#include "app_interface.h"
#include "uhid_host.h"

#define MODULE_DBG_LVL UHID_HOST_DBG_LVL
#include "log.h"

#if (HOGP_APP == TRUE)

#if (TARGET_LINUX == TRUE)

#include <fcntl.h>
#include <unistd.h>
#include <linux/uhid.h>

static int uhid_write(int fd, const struct uhid_event *ev);

static unsigned char rdesc_default[] = {
	0x05, 0x01,	/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x02,	/* USAGE (Mouse) */
	0xa1, 0x01,	/* COLLECTION (Application) */
	0x09, 0x01,		/* USAGE (Pointer) */
	0xa1, 0x00,		/* COLLECTION (Physical) */
	0x85, 0x01,			/* REPORT_ID (1) */
	0x05, 0x09,			/* USAGE_PAGE (Button) */
	0x19, 0x01,			/* USAGE_MINIMUM (Button 1) */
	0x29, 0x03,			/* USAGE_MAXIMUM (Button 3) */
	0x15, 0x00,			/* LOGICAL_MINIMUM (0) */
	0x25, 0x01,			/* LOGICAL_MAXIMUM (1) */
	0x95, 0x03,			/* REPORT_COUNT (3) */
	0x75, 0x01,			/* REPORT_SIZE (1) */
	0x81, 0x02,			/* INPUT (Data,Var,Abs) */
	0x95, 0x01,			/* REPORT_COUNT (1) */
	0x75, 0x05,			/* REPORT_SIZE (5) */
	0x81, 0x01,			/* INPUT (Cnst,Var,Abs) */
	0x05, 0x01,			/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x30,			/* USAGE (X) */
	0x09, 0x31,			/* USAGE (Y) */
	0x09, 0x38,			/* USAGE (WHEEL) */
	0x15, 0x81,			/* LOGICAL_MINIMUM (-127) */
	0x25, 0x7f,			/* LOGICAL_MAXIMUM (127) */
	0x75, 0x08,			/* REPORT_SIZE (8) */
	0x95, 0x03,			/* REPORT_COUNT (3) */
	0x81, 0x06,			/* INPUT (Data,Var,Rel) */
	0xc0,			/* END_COLLECTION */
	0xc0,		/* END_COLLECTION */
	0x05, 0x01,	/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x06,	/* USAGE (Keyboard) */
	0xa1, 0x01,	/* COLLECTION (Application) */
	0x85, 0x02,	/* REPORT_ID (2) */
	0x05, 0x07, 	/* Usage Page (Key Codes) */
	0x19, 0xe0, 		/* Usage Minimum (224) */
	0x29, 0xe7, 		/* Usage Maximum (231) */
	0x15, 0x00, 		/* Logical Minimum (0) */
	0x25, 0x01, 		/* Logical Maximum (1) */
	0x75, 0x01, 		/* Report Size (1) */
	0x95, 0x08, 			/* Report Count (8) */
	0x81, 0x02, 			/* Input (Data, Variable, Absolute) */
	0x95, 0x05, 		/* Report Count (5) */
	0x75, 0x01, 			/* Report Size (1) */
	0x05, 0x08, 	/* Usage Page (LEDs) */
	0x19, 0x01, 		/* Usage Minimum (1) */
	0x29, 0x05, 		/* Usage Maximum (5) */
	0x91, 0x02, 		/* Output (Data, Variable, Absolute), Led report */
	0x95, 0x01, 		/* Report Count (1) */
	0x75, 0x03, 			/* Report Size (3) */
	0x91, 0x03, 			/* Output (Data, Variable, Absolute), Led report padding */
	0x95, 0x07, 		/* Report Count (7) */
	0x75, 0x08, 			/* Report Size (8) */
	0x16, 0x00, 0x00, 		/* Logical Minimum (0) */
	0x26, 0xff, 0x00, 		/* Logical Maximum (65280) */
	0x05, 0x07, 	/* Usage Page (Key Codes) */
	0x19, 0x00, 		/* Usage Minimum (0) */
	0x2a, 0x91, 0x00, 	/* Usage Maximum (37120) */
	0x81, 0x00,			/* Input */
	0xc0,		/* END_COLLECTION */
};

int uhid_open(char* device, unsigned char *rdesc, int size)
{
	logi("");

	int uhid_port = open(device, O_RDWR | O_CLOEXEC);

	if (uhid_port == -1)
	{
		perror("Failed to open UHID port, please check permissions!");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}

	struct uhid_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.type = UHID_CREATE2;
	strcpy((char*)ev.u.create2.name, "test-uhid-device");
	if (!rdesc)
	{
		memcpy(ev.u.create2.rd_data, rdesc_default, sizeof(rdesc_default));
		ev.u.create2.rd_size = sizeof(rdesc_default);
	}
	else
	{
		memcpy(ev.u.create2.rd_data, rdesc, size);
		ev.u.create2.rd_size = size;
	}
	ev.u.create2.bus = BUS_USB;
	ev.u.create2.vendor = 0x15d9;
	ev.u.create2.product = 0x0a37;
	ev.u.create2.version = 0;
	ev.u.create2.country = 0;
	uhid_write(uhid_port, &ev);

	return uhid_port;
}

static int uhid_write(int fd, const struct uhid_event *ev)
{
	logi("");
	ssize_t ret;
	ret = write(fd, ev, sizeof(*ev));

	if (ret < 0)
	{
		logw("Cannot write to uhid: %d", fd);
		return -1;
	}
	else if (ret != sizeof(*ev))
	{
		logw("Wrong size written to uhid: %d", fd);
		return -1;
	}

	return ret;
}

int uhid_send(int fd, buffer_t *buffer)
{
    struct uhid_event ev;
    logd("fd = %d, buffer->length = %d", fd, buffer->length);

    memset(&ev, 0, sizeof(ev));
    ev.type = UHID_INPUT2;
    ev.u.input2.size = buffer->length;
    if (buffer->length > sizeof(ev.u.input2.data))
    {
        logw("Report size greater than allowed size");
        return -1;
    }

    memcpy(ev.u.input2.data, buffer->data + buffer->offset, buffer->length);
    hex_dump("UHID write", buffer->data, buffer->length);

    return uhid_write(fd, &ev);
}

void uhid_close(int fd)
{
	struct uhid_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.type = UHID_DESTROY;
	uhid_write(fd, &ev);
	close(fd);
}

#else /* TARGET_LINUX == TRUE */

int uhid_open(char* device, unsigned char *rdesc, int size) { return 0; }
int uhid_send(int fd, buffer_t *buffer) { return 0; }
void uhid_close(int fd) {}

#endif /* TARGET_LINUX == TRUE */

#endif /* HOGP_APP == TRUE */
