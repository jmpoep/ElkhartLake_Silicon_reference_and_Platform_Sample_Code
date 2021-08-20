/** @file
  This file contains the UART 16550 related definitions

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _uart16550_h_
#define _uart16550_h_

#include "MrcCommon.h"
#include "MrcOemPlatform.h"

#define RECEIVER_BUFFER             (0x00)
#define TRANSMIT_HOLDING            (0x00)
#define DIVISOR_LATCH_LOW           (0x00)    // 0/1 - 16-bit

#define DIVISOR_LATCH_HIGH          (0x01)
#define INTERRUPT_ENABLE            (0x01)
#define DISABLE_INTERRUPTS          (0x00)

#define INTERRUPT_IDENTIFICATION    (0x02)
#define FIFO_CONTROL                (0x02)
#define FIFO_DISABLE_MASK           (0xFE)

#define LINE_CONTROL                (0x03)
#define DIVISOR_LATCH_ACCESS        (0x80)
#define STOP_BITS                   (0x04)
#define NO_PARITY                   (0x00)
#define BITS8                       (0x03) // 3 = 8

#define DLAB_BIT                    (0x01)
#define STOP_BIT                    (0x01)
#define DATA_BITS                   (0x03)

#define EOF                         (0xFF)

#define LINE_STATUS                 (0x05)
#define TRANS_HOLDING_REG_EMPTY     (0x20)
#define BREAK_INTERRUPT             (0x10)
#define DATA_READY                  (0x01)

#define INDEX_PORT0                 (0x02E)
#define DATA_PORT0                  (INDEX_PORT0 + 1)
//
// Global register in NSPC87427
//

#define ICH_LPC_EN                  (0x400F8080)     // D31:F0:R80h

#define PCI_FUNCTION_NUMBER_ICH_LPC (0)
#define PCI_DEVICE_NUMBER_ICH_LPC   (31)

#define ICH_LPC_CF8_ADDR(Offset)    GetPciDeviceAddress (0, PCI_DEVICE_NUMBER_ICH_LPC, PCI_FUNCTION_NUMBER_ICH_LPC, Offset)
#define ICH_LPC_IO_DEC              (0x80)
#define ICH_LPC_IO_ENABLE           (0x82)
#define ICH_LPC_GEN1_DEC            (0x84)
#define ICH_LPC_GEN2_DEC            (0x88)

#define BAUD_RATE_DIVISOR           (115200)

// Com port options
#define MRC_COM1_BASE               (0x3f8)
#define MRC_COM2_BASE               (0x2f8)
#define MRC_COM3_BASE               (0x3e8)
#define MRC_COM4_BASE               (0x2e8)

// Select the platform com port address
#define GLOBALCOMPORT               (MRC_COM1_BASE)     // 0x3F8-0x3FF

#define PILOT3_CONFIG_INDEX       0x4E
#define PILOT3_CONFIG_DATA        0x4F
#define PILOT3_ENTERCFG_VALUE     0x5A
#define PILOT3_DEV_ID_REG         0x20
#define PILOT3_DEV_ID             0x03
#define PILOT3_EXITCFG_VALUE      0xA5

extern
char
UartGetChar (
  void
);

extern
int
UartPutChar (
  int c
  );

extern
char
UartGetLineStatusRegister (
  void
  );

extern
char
UartGetBreak (
  void
  );

extern
int
UartPuts (
  const char *String
);

extern
void
Init16550Uart (
  void
  );

#endif // _uart16550_h_
