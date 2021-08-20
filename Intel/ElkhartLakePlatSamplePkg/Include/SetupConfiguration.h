/** @file
  Default platform setup configuration settings.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2017 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _SETUP_CONFIGURATION_H_
#define _SETUP_CONFIGURATION_H_

#define SERIAL_SETUP_OPTION  1
#define TOTAL_SIO_SERIAL_PORTS  0x4
#define TOTAL_PCI_SERIAL_PORTS  0x1
#define TOTAL_SERIAL_PORTS  0x5
#define MAX_SIO_SERIAL_PORTS  0x4
#define MAX_PCI_SERIAL_PORTS  0x4

#define DEFAULT_CONSOLE_REDIRECTION_ENABLE  1
#define DEFAULT_ACPI_SPCR_COM_PORT  0x0
#define DEFAULT_TERMINAL_TYPE  0x3
#define DEFAULT_RESOLUTION_TYPE  0x0
#define DEFAULT_ACPI_SPCR_CONSOLE_REDIRECTION_ENABLE  1
#define DEFAULT_ACPI_SPCR_TABLE_TERMINAL_TYPE  0x2
#define HARDWARE_FLOW_CONTROL_SETUP_OPTION  0x1
#define SOFTWARE_FLOW_CONTROL_SETUP_OPTION  0x2
#define TIMEOUT_FOR_DETERMINING_LONE_ESC_CHAR  0xf4240

#define DEFAULT_BOOT_TIMEOUT  0x1
#define DEFAULT_FAST_BOOT  0
#define DEFAULT_QUIET_BOOT  0
#define FORCE_USER_TO_SETUP_ON_FIRST_BOOT  0
#define SHOW_ADVANCED_FORMSET  1
#define FORCE_USER_TO_SETUP_IF_BOOT_WITH_DEFAULT  0
#define LOAD_DEFAULTS_IF_SECONDARY_NVRAM_INIT     1

#define UART_SERIAL_PORT_0_INDEX  0x0
#define UART_SERIAL_PORT_1_INDEX  0x1
#define UART_SERIAL_PORT_2_INDEX  0x2
#define UART_SERIAL_PORT_3_INDEX  0x3
#define PCI_SERIAL_PORT_0_INDEX  0x4
#define PCI_SERIAL_PORT_1_INDEX  0x5
#define PCI_SERIAL_PORT_2_INDEX  0x6
#define PCI_SERIAL_PORT_3_INDEX  0x7

#define OFFSET_0  0x0
#define OFFSET_1  0x1
#define OFFSET_2  0x2
#define OFFSET_3  0x3
#define OFFSET_4  0x4
#define OFFSET_5  0x5
#define OFFSET_6  0x6
#define OFFSET_7  0x7
#define OFFSET_8  0x8
#define OFFSET_9  0x9
#define OFFSET_10  0xa
#define OFFSET_11  0xb
#define OFFSET_12  0xc
#define OFFSET_13  0xd
#define OFFSET_14  0xe
#define OFFSET_15  0xf
#define OFFSET_16  0x10
#define OFFSET_17  0x11
#define OFFSET_18  0x12
#define OFFSET_19  0x13
#define OFFSET_20  0x14
#define OFFSET_21  0x15
#define OFFSET_22  0x16
#define OFFSET_23  0x17
#define OFFSET_24  0x18
#define OFFSET_25  0x19
#define OFFSET_26  0x1a
#define OFFSET_27  0x1b
#define OFFSET_28  0x1c
#define OFFSET_29  0x1d
#define OFFSET_30  0x1e
#define OFFSET_31  0x1f
#define OFFSET_32  0x20
#define OFFSET_33  0x21
#define OFFSET_34  0x22
#define OFFSET_35  0x23
#define OFFSET_36  0x24
#define OFFSET_37  0x25
#define OFFSET_38  0x26
#define OFFSET_39  0x27
#define ENGLISH  en-US

#endif
