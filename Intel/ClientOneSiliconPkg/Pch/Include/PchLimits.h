/** @file
  Build time limits of PCH resources.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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
/*
 * Defines povided in this file are indended to be used only where static value
 * is needed. They are set to values which allow to accomodate multiple projects
 * needs. Where runtime usage is possible please used dedicated functions from
 * PchInfoLib to retrieve accurate values
 */

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
// PCH PSF segments
//
#define PCH_MAX_PSF_SEGMENTS                8

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
// SerialIo limits
//
#define PCH_MAX_SERIALIO_CONTROLLERS         14
#define PCH_MAX_SERIALIO_I2C_CONTROLLERS      8
#define PCH_MAX_SERIALIO_SPI_CONTROLLERS      3
#define PCH_MAX_SERIALIO_SPI_CHIP_SELECTS     2
#define PCH_MAX_SERIALIO_UART_CONTROLLERS     3

//
// ISH limits
//
#define PCH_MAX_ISH_GP_PINS                   8
#define PCH_MAX_ISH_UART_CONTROLLERS          2
#define PCH_MAX_ISH_I2C_CONTROLLERS           3
#define PCH_MAX_ISH_SPI_CONTROLLERS           1
#define PCH_MAX_ISH_SPI_CS_PINS               1

// PSE limits
#define PCH_MAX_PSE_CONTROLLERS              36
#define PCH_MAX_PSE_I2S_CONTROLLERS           2
#define PCH_MAX_PSE_UART_CONTROLLERS          6
#define PCH_MAX_PSE_QEP_CONTROLLERS           4
#define PCH_MAX_PSE_I2C_CONTROLLERS           8
#define PCH_MAX_PSE_SPI_CONTROLLERS           4
#define PCH_MAX_PSE_GBE_CONTROLLERS           2
#define PCH_MAX_PSE_DMA_CONTROLLERS           3
#define PCH_MAX_PSE_SPI_CS_PINS               2
#define PCH_MAX_PSE_CAN_CONTROLLERS           2
#define PCH_MAX_PSE_PWM_CONTROLLER_PINS      16
#define PCH_MAX_PSE_ADC_CONTROLLER_PINS      16
#define PCH_MAX_PSE_TGPIO_CONTROLLERS         2
#define PCH_MAX_PSE_HSUART_PINS               4
#define PCH_MAX_PSE_TGPIO_CONTROLLER_PINS    60

//
// HDA limits
//
#define PCH_MAX_HDA_SDI                       2
#define PCH_MAX_HDA_SSP_LINK_NUM              6
#define PCH_MAX_HDA_DMIC_LINK_NUM             2
#define PCH_MAX_HDA_SNDW_LINK_NUM             4

//
// Number of eSPI slaves
//
#define PCH_MAX_ESPI_SLAVES                  2

//
// Number of UFS controllers
//
#define PCH_MAX_UFS_DEV_NUM                  2

//
// Total Number of PCH TSN GBE controllers
//
#define PCH_MAX_TSN_GBE_CONTROLLERS          3

//
// Number of FIA Connector support Orientation Muxing
//
#define PCH_MAX_FIA_ORM_CONNECTOR            16

#endif // _PCH_LIMITS_H_

