/** @file
  Build time limits of PCH resources.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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
#ifndef _PCH_LIMITS_H_
#define _PCH_LIMITS_H_

//
// PCIe limits
//
#define PCH_MAX_PCIE_ROOT_PORTS             24
#define PCH_MAX_PCIE_CONTROLLERS            6

//
// PCIe clocks limits
//
#define PCH_MAX_PCIE_CLOCKS                 16

//
// DMI lanes
//
#define PCH_MAX_DMI_LANES                   8

//
// RST PCIe Storage Cycle Router limits
//
#define PCH_MAX_RST_PCIE_STORAGE_CR         3

//
// SATA limits
//
#define PCH_MAX_SATA_CONTROLLERS            3
#define PCH_MAX_SATA_PORTS                  8

//
// USB limits
//
#define PCH_MAX_USB2_PORTS                  16
#define PCH_MAX_USB3_PORTS                  10

//
// SerialIo limits
//
#define PCH_MAX_SERIALIO_CONTROLLERS         12
#define PCH_MAX_SERIALIO_I2C_CONTROLLERS      6
#define PCH_MAX_SERIALIO_SPI_CONTROLLERS      3
#define PCH_MAX_SERIALIO_UART_CONTROLLERS     3

//
// Number of eSPI slaves
//
#define PCH_MAX_ESPI_SLAVES                  2

#endif // _PCH_LIMITS_H_

