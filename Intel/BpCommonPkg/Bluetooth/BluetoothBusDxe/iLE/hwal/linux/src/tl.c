/** @file
  Userial layer implementation.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "config_host.h"
#include "tl.h"
#include "error_code.h"

#include <stdint.h>
#include <poll.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#include "osa_types.h"
#include "hci_host.h"
#include "int_interface.h"
#include "utils.h"

#if (USE_BLUEZ_SOCKET == TRUE)
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>
#include <getopt.h>
#include <stdbool.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdint.h>
#include <sys/epoll.h>

#include "mainloop.h"
#endif

#define MODULE_DBG_LVL USERIAL_DBG_LVL
#include "log.h"

#if (USE_BLUEZ_SOCKET == TRUE)
#define BT_H4_CMD_PKT   0x01
#define BT_H4_ACL_PKT   0x02
#define BT_H4_SCO_PKT   0x03
#define BT_H4_EVT_PKT   0x04

struct bt_hci_cmd_hdr {
	UINT16 opcode;
	UINT8  plen;
} __attribute__ ((packed));

struct bt_hci_acl_hdr {
	UINT16 handle;
	UINT16 dlen;
} __attribute__ ((packed));

struct bt_hci_sco_hdr {
	UINT16 handle;
        UINT8  dlen;
} __attribute__ ((packed));

struct bt_hci_evt_hdr {
	UINT8  evt;
	UINT8  plen;
} __attribute__ ((packed));


#define BTPROTO_HCI	1
#define HCI_CHANNEL_USER	1
struct sockaddr_hci {
	sa_family_t	hci_family;
	unsigned short	hci_dev;
	unsigned short  hci_channel;
};

static int dev_fd = -1;
static UINT8 dev_buf[4096];
static UINT16 dev_len = 0;
#else
#define POLL_TIMEOUT 100
static int userial_port = -1;
static int userial_running;
static osa_semaphore_t thread_sem;

static INT8 start_tl_read_thread();

#define USERIAL_BAUD_921600 921600
#define USERIAL_BAUD_2000000 2000000
#endif

#if (USE_BLUEZ_SOCKET == TRUE)
static bool write_packet(int fd, const void *data, size_t size)
{
	while (size > 0) {
		ssize_t written;

		written = write(fd, data, size);
		if (written < 0) {
			if (errno == EAGAIN || errno == EINTR)
				continue;
			return false;
		}

		data += written;
		size -= written;
	}
	return true;
}

static int open_channel(UINT16 index)
{
	struct sockaddr_hci addr;
	int fd;

	logd("Opening user channel for hci%u\n", index);

	fd = socket(PF_BLUETOOTH, SOCK_RAW | SOCK_CLOEXEC, BTPROTO_HCI);
	if (fd < 0) {
		loge("Failed to open Bluetooth socket");
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.hci_family = AF_BLUETOOTH;
	addr.hci_dev = index;
	addr.hci_channel = HCI_CHANNEL_USER;

	if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		close(fd);
		loge("Failed to bind Bluetooth socket");
		return -1;
	}

	return fd;
}

static void dev_read_destroy(void *user_data)
{
	logd("");
	if (dev_fd > 0)
	{
		close(dev_fd);
		dev_fd = -1;

		mainloop_remove_fd(dev_fd);
	}
}

static void dev_read_callback(int fd, UINT32 events, void *user_data)
{
	struct bt_hci_evt_hdr *evt_hdr;
	struct bt_hci_acl_hdr *acl_hdr;
	ssize_t len;
	UINT16 pktlen;

	if (events & (EPOLLERR | EPOLLHUP)) {
		loge("Error from device descriptor\n");
		mainloop_remove_fd(dev_fd);
		return;
	}

	len = read(dev_fd, dev_buf + dev_len,
				sizeof(dev_buf) - dev_len);
	if (len < 0) {
		if (errno == EAGAIN || errno == EINTR)
			return;

		loge("Read from device descriptor failed\n");
		mainloop_remove_fd(dev_fd);
		return;
	}

	dev_len += len;

process_packet:
	if (dev_len < 1)
		return;

	switch (dev_buf[0]) {
	case BT_H4_EVT_PKT:
		if (dev_len < 1 + sizeof(*evt_hdr))
			return;

		evt_hdr = (void *) (dev_buf + 1);
		pktlen = 1 + sizeof(*evt_hdr) + evt_hdr->plen;
		break;
	case BT_H4_ACL_PKT:
		if (dev_len < 1 + sizeof(*acl_hdr))
			return;

		acl_hdr = (void *) (dev_buf + 1);
		pktlen = 1 + sizeof(*acl_hdr) + acl_hdr->dlen;
		break;
	case BT_H4_SCO_PKT:
		loge("SCO packet is not expected for BLE at present");
		break;
	default:
		loge("Received unknown device packet type 0x%02x\n",
							dev_buf[0]);
		mainloop_remove_fd(dev_fd);
		return;
	}

	if (dev_len < pktlen)
		return;

	hex_dump("---> ", dev_buf, pktlen);
	rx_req_hci_evt_msg(dev_buf, pktlen);

	if (dev_len > pktlen) {
		memmove(dev_buf, dev_buf + pktlen,
						dev_len - pktlen);
		dev_len -= pktlen;
		goto process_packet;
	}

	dev_len = 0;
}

static osa_thread_ret_t tl_read_thread(osa_thread_arg_t arg)
{
	mainloop_run();
	osa_thread_exit(NULL);
}

static INT8 start_tl_read_thread()
{
	osa_thread_create(USERIAL_READ_THREAD, tl_read_thread, 0);

	return STATUS_SUCCESS;
}

static void signal_callback(int signum, void *user_data)
{
	switch (signum) {
	case SIGINT:
	case SIGTERM:
		mainloop_quit();
		break;
	}
}

INT8 tl_write(UINT8 *buffer, UINT16 len)
{
	INT8 ret = 0;
	hex_dump("<--- ", buffer, len);
	if (dev_fd != -1 && len > 0)
	{
		if ((ret = write_packet(dev_fd, buffer, len)) == FALSE)
		{
			loge("Userial write error.");
			return STATUS_ERR_LAYER_SPECIFIC;
		}
	} else
		return STATUS_ERR_LAYER_SPECIFIC;
	return STATUS_SUCCESS;
}

void tl_close()
{
	logd("");
	osa_thread_join(USERIAL_READ_THREAD, NULL);
	if (dev_fd > 0)
	{
		close(dev_fd);
		dev_fd = -1;

		mainloop_remove_fd(dev_fd);
	}
}
#else
INT8 tl_write(UINT8 *buffer, UINT16 len)
{
	INT8 ret = 0;
	hex_dump("<--- ", buffer, len);
	if (userial_port != -1 && len > 0)
	{
		if ((ret = write(userial_port, buffer, len)) <= 0)
		{
			loge("Userial write error.");
			return STATUS_ERR_LAYER_SPECIFIC;
		}
	} else
		return STATUS_ERR_LAYER_SPECIFIC;
	return STATUS_SUCCESS;
}

static INT8 tl_read_byte(UINT8* buf, size_t len)
{
	int n = 0;
	int offset = 0;
	do
	{
		n = read(userial_port, buf + offset, len);
		if (n < 0)
		{
			loge("Read failed");
			return STATUS_ERR_LAYER_SPECIFIC;
		}
		offset = offset + n;
		len = len - n;

	} while (len);

	return STATUS_SUCCESS;
}

static osa_thread_ret_t tl_read_thread(osa_thread_arg_t arg)
{
	int result;
	struct pollfd pfd;
	pfd.fd = userial_port;
	pfd.events = POLLIN;
	uint8_t hci_evt_buf[HCI_CMD_EVT_MAX_SIZE];
	uint16_t offset = 0, len = 0;
	logi("");
	osa_semaphore_put(&thread_sem);
	while (userial_running == TRUE)
	{
		offset = 0;
		result = poll(&pfd, 1, POLL_TIMEOUT);
		switch (result)
		{
		case 0:
			//logd ("timeout");
			break;
		case -1:
			logw("poll error");
			exit(1);
		default:
			if (pfd.revents & POLLIN)
			{
				/* Read uart header */
				if (tl_read_byte(hci_evt_buf + offset, 1) == STATUS_SUCCESS)
				{
					switch (hci_evt_buf[0])
					{
					case HCI_EVT:
						offset += 1;
						//bzero(hci_evt_buf+offset, HCI_CMD_EVT_MAX_SIZE - 1);
						if (tl_read_byte(hci_evt_buf + offset, 2) == STATUS_SUCCESS)
						{
							logi("hci_evt_header:0x%x param_len:0x%x", hci_evt_buf[1], hci_evt_buf[2]);
							offset += 2;
							if (tl_read_byte(hci_evt_buf + offset,
									hci_evt_buf[2]) == STATUS_SUCCESS)
							{
								hex_dump("---> ", hci_evt_buf, hci_evt_buf[2] + 3);
								rx_req_hci_evt_msg(hci_evt_buf,
										hci_evt_buf[2] + 3);
							}
						}
						break;
					case HCI_ACL:
						logi("ACL pkt Received...");
						offset += 1;
						if (tl_read_byte(hci_evt_buf + offset, 4) == STATUS_SUCCESS)
						{
							offset += 2;
							UINT8* temp = hci_evt_buf + offset;
							STREAM_TO_UINT16(len, temp);
							offset += 2;
							if (tl_read_byte(hci_evt_buf + offset,
									len) == STATUS_SUCCESS)
							{
								hex_dump("---> ", hci_evt_buf, len + HCI_ACL_PREAMBLE_SIZE + UART_HDR_SIZE);
								rx_req_hci_evt_msg(hci_evt_buf,
										len + HCI_ACL_PREAMBLE_SIZE
												+ UART_HDR_SIZE);
							}
						}
						break;
					}
				}
			}
		}
	}
#if (THREADLESS_STACK == TRUE)
	osa_semaphore_delete(&thread_sem);
	osa_thread_join(USERIAL_READ_THREAD, NULL);
	if (userial_port > 0)
	{
		close(userial_port);
		userial_port = -1;
	}
#else
	osa_semaphore_put(&thread_sem);
#endif
	osa_thread_exit(NULL);
}

static INT8 start_tl_read_thread()
{
	userial_running = TRUE;
	osa_semaphore_create(&thread_sem, 0);

	osa_thread_create(USERIAL_READ_THREAD, tl_read_thread, 0);

	osa_semaphore_get(&thread_sem);
	return STATUS_SUCCESS;
}

void tl_close()
{
	userial_running = FALSE;
	logi("");
#if (THREADLESS_STACK == FALSE)
	osa_semaphore_get(&thread_sem);
	osa_semaphore_delete(&thread_sem);
	osa_thread_join(USERIAL_READ_THREAD, NULL);
	if (userial_port > 0)
	{
		close(userial_port);
		userial_port = -1;
	}
#endif
}
#endif

#if (USE_BLUEZ_EMULATOR == TRUE)
INT8 tl_init(char* device, int ispeed)
{
	struct sockaddr_un server;
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0)
	{
		loge("error opening stream socket");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}

	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, device);
	if (connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) < 0)
	{
		close(sock);
		loge("error connecting stream socket");
		return STATUS_ERR_INSUFFICIENT_RESOURCES;
	}

	userial_port = sock;

	start_tl_read_thread();

	return sock;
}
#elif (USE_BLUEZ_SOCKET == TRUE)
INT8 tl_init(char* device, int ispeed)
{
	const char *str;
	sigset_t mask;

	if (strlen(device) > 3 && !strncmp(device, "hci", 3))
		str = device + 3;
	else
		str = device;
	if (!isdigit(*str)) {
		loge("Invalid index value");
		return -1;
	}

	mainloop_init();

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGTERM);

	mainloop_set_signal(&mask, signal_callback, NULL, NULL);

	dev_fd = open_channel(atoi(str));
	logd("dev_fd: %d\n", dev_fd);

	mainloop_add_fd(dev_fd, EPOLLIN | EPOLLRDHUP,
			dev_read_callback, NULL, dev_read_destroy);

	start_tl_read_thread();

	return dev_fd;
}
#else
INT8 tl_init(char* device, int ispeed)
{
	struct termios g_initialAtt, newAtt;
	int baud = B115200;
	userial_port = open(device, O_RDWR);
	if (userial_port == -1)
		return STATUS_ERR_INSUFFICIENT_RESOURCES;

	tcflush(userial_port, TCIOFLUSH);
	memset(&g_initialAtt, 0, sizeof(g_initialAtt));
	tcgetattr(userial_port, &g_initialAtt); // save this to restore later
	newAtt = g_initialAtt;

	if (ispeed == USERIAL_BAUD_921600)
		g_initialAtt.c_cflag = B921600 | CS8 | CLOCAL | CRTSCTS; // Enable RTS CTS flow control
	else if (ispeed == USERIAL_BAUD_2000000)
		g_initialAtt.c_cflag = B2000000 | CS8 | CLOCAL | CRTSCTS; // Enable RTS CTS flow control
	else
		//default rate: 115200
		g_initialAtt.c_cflag = B115200 | CS8 | CLOCAL | CRTSCTS; // Enable RTS CTS flow control

	cfsetospeed(&g_initialAtt, baud);
	cfsetispeed(&g_initialAtt, baud);

	cfmakeraw(&newAtt);
	tcsetattr(userial_port, TCSANOW, &newAtt);
	tcflush(userial_port, TCIOFLUSH);

	logd(" device:%s success. port:%d", device, userial_port);

	start_tl_read_thread();

	return userial_port;
}
#endif
