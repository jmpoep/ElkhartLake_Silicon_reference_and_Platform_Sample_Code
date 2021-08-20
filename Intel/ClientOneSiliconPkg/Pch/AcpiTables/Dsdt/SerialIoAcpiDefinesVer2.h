/**@file

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


//
// Definition for Pch Serial IO Controllers
//
#ifndef _SERIAL_IO_ACPI_DEFINES_VER2_
#define _SERIAL_IO_ACPI_DEFINES_VER2_

//
// TGL-PCH Serial IO BDF _ADR
//
#define SERIAL_IO_I2C0_ADR 0x00150000
#define SERIAL_IO_I2C1_ADR 0x00150001
#define SERIAL_IO_I2C2_ADR 0x00150002
#define SERIAL_IO_I2C3_ADR 0x00150003
#define SERIAL_IO_I2C4_ADR 0x00190000
#define SERIAL_IO_I2C5_ADR 0x00190001
#define SERIAL_IO_I2C6_ADR 0x00100000
#define SERIAL_IO_I2C7_ADR 0x00100001

#define SERIAL_IO_SPI0_ADR 0x001E0002
#define SERIAL_IO_SPI1_ADR 0x001E0003
#define SERIAL_IO_SPI2_ADR 0x00120006
#define SERIAL_IO_SPI3_ADR 0x00130000
#define SERIAL_IO_SPI4_ADR 0x00130001
#define SERIAL_IO_SPI5_ADR 0x00130002
#define SERIAL_IO_SPI6_ADR 0x00130003

#define SERIAL_IO_UART0_ADR 0x001E0000
#define SERIAL_IO_UART1_ADR 0x001E0001
#define SERIAL_IO_UART2_ADR 0x00190002
#define SERIAL_IO_UART3_ADR 0x00110000
#define SERIAL_IO_UART4_ADR 0x00110001
#define SERIAL_IO_UART5_ADR 0x00110002
#define SERIAL_IO_UART6_ADR 0x00110003

#endif // _SERIAL_IO_ACPI_DEFINES_VER2_
