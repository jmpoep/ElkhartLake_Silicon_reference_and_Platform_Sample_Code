/** @file
  Register names for Telemetry
  <b>Conventions</b>:
  - Prefixes:
    - Definitions beginning with "R_" are registers
    - Definitions beginning with "B_" are bits within registers
    - Definitions beginning with "V_" are meaningful values of bits within the registers
    - Definitions beginning with "S_" are register sizes
    - Definitions beginning with "N_" are the bit position

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _REGS_TELEMETRY_H_
#define _REGS_TELEMETRY_H_

//
// Device 10 Memory Mapped IO Register Offset Equates
//
#define TEL_BUS_NUM     0x00
#define TEL_DEV_NUM     0x0A
#define TEL_FUN_NUM     0x00

//
// PCI Configuration Space Registers
//
#define R_TEL_CFG_BAR0                              0x10
#define R_TEL_CFG_BAR1                              0x14

//
// DVSEC capability Registers
//
#define R_TEL_DVSEC_OFFSET                       0x100

#define R_TEL_DVSEC_PCIE_CAP_ID                  0x0            // PCI Express Capability ID
#define R_TEL_DVSEC_NEXT_CAP                     0x2            // Next Capability Offset
#define R_TEL_DVSEV_ID                           0x8            // DVSEC_ID
#define R_TEL_DVSEV_DISCOVERY_TABLE_OFFSET       0xC            // Discovery Table Offset


#define V_TELEMETRY_EXTENDED_CAP_ID              0x23          // Indicates that this is a Telemetry Aggregator Extended Capability
#define V_CRASHLOG_DVSEC_ID                      0x04          // CrashLog DEVSC ID
#define V_TEL_DVSEC_TBIR_BAR0                    0
#define V_TEL_DVSEC_TBIR_BAR1                    1

//
// CPU CrashLog MMIO Registers
//
#define R_CRASHLOG_HEADER_ADDRESS                          0x6030

#define R_CRASHLOG_MAILBOX_INTERFACE_ADDRESS               0x6038

#define R_CRASHLOG_MAIN_POINTER_OFFSET                     0x6040
#define R_CRASHLOG_TELEMETRY_POINTER_OFFSET                0x6048
#define R_CRASHLOG_TRACE_POINTER_OFFSET                    0x6050

#define R_CRASHLOG_POINTER_BASE_ADDRESS_FIELD_OFFSET       0x00
#define R_CRASHLOG_POINTER_SIZE_FIELD_OFFSET               0x04

//
// CPU CrashLog Mailbox commands
//
#define V_CPU_CRASHLOG_CMD_DISABLE                            0
#define V_CPU_CRASHLOG_CMD_TRIGGER                            1
#define V_CPU_CRASHLOG_CMD_CLEAR                              2

#define CPU_CRASHLOG_MAILBOX_WAIT_STALL                       1
#define CPU_CRASHLOG_MAILBOX_WAIT_TIMEOUT                     1000

#endif // _SA_REGS_TELEMETRY_H_
