/** @file
  PCH preserved MMIO resource definitions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#ifndef _PCH_PRESERVED_RESOURCES_H_
#define _PCH_PRESERVED_RESOURCES_H_

/**

  Detailed recommended static allocation
  +-------------------------------------------------------------------------+
  | For CNL PCH                                                             |
  | PCH preserved MMIO range, 32 MB, from 0xFC800000 to 0xFE7FFFFF          |
  +-------------------------------------------------------------------------+
  | Size        | Start       | End         | Usage                         |
  | 8 MB        | 0xFC800000  | 0xFCFFFFFF  | TraceHub SW BAR               |
  | 16 MB       | 0xFD000000  | 0xFDFFFFFF  | SBREG                         |
  | 64 KB       | 0xFE000000  | 0xFE00FFFF  | PMC MBAR                      |
  | 4 KB        | 0xFE010000  | 0xFE010FFF  | SPI BAR0                      |
  | 176 KB      | 0xFE020000  | 0xFE04BFFF  | SerialIo BAR in ACPI mode     |
  | 16 KB       | 0xFE050000  | 0xFE053FFF  | PSE DMA1 BAR                  |
  | 16 KB       | 0xFE060000  | 0xFE063FFF  | PSE DMA2 BAR                  |
  | 400 KB      | 0xFE064000  | 0xFE0AFFFF  | Unused                        |
  | 64 KB       | 0xFE0B0000  | 0xFE0BFFFF  | eSPI LGMR BAR                 |
  | 64 KB       | 0xFE0C0000  | 0xFE0CFFFF  | eSPI2 SEGMR BAR               |
  | 192 KB      | 0xFE0D0000  | 0xFE0FFFFF  | Unused                        |
  | 1 MB        | 0xFE100000  | 0xFE1FFFFF  | TraceHub MTB BAR              |
  | 2 MB        | 0xFE200000  | 0xFE3FFFFF  | TraceHub FW BAR               |
  | 2 MB        | 0xFE400000  | 0xFE5FFFFF  | PSE MBAR                      |
  | 2 MB        | 0xFE600000  | 0xFE7FFFFF  | Temp address                  |
  +-------------------------------------------------------------------------+
**/
#define PCH_PRESERVED_BASE_ADDRESS      0xFC800000     ///< Pch preserved MMIO base address
#define PCH_PRESERVED_MMIO_SIZE         0x02000000     ///< 28MB
#define PCH_TRACE_HUB_SW_BASE_ADDRESS   0xFC800000     ///< TraceHub SW MMIO base address
#define PCH_TRACE_HUB_SW_MMIO_SIZE      0x00800000     ///< 8MB
#define PCH_PCR_BASE_ADDRESS            0xFD000000     ///< SBREG MMIO base address
#define PCH_PCR_MMIO_SIZE               0x01000000     ///< 16MB
#define PCH_PWRM_BASE_ADDRESS           0xFE000000     ///< PMC MBAR MMIO base address
#define PCH_PWRM_MMIO_SIZE              0x00010000     ///< 64KB
#define PCH_SPI_BASE_ADDRESS            0xFE010000     ///< SPI BAR0 MMIO base address
#define PCH_SPI_MMIO_SIZE               0x00001000     ///< 4KB
#define PCH_SERIAL_IO_BASE_ADDRESS      0xFE020000     ///< SerialIo MMIO base address
#define PCH_SERIAL_IO_MMIO_SIZE         0x0002C000     ///< 176KB
#define PCH_PSE_DMA1_BASE_ADDRESS       0xFE050000     ///< PSE DMA1 MMIO base address
#define PCH_PSE_DMA1_MMIO_SIZE          0x00004000     ///< 16KB
#define PCH_PSE_DMA2_BASE_ADDRESS       0xFE060000     ///< PSE DMA2 MMIO base address
#define PCH_PSE_DMA2_MMIO_SIZE          0x00004000     ///< 16KB
#define PCH_ESPI_LGMR_BASE_ADDRESS      0xFE0B0000     ///< eSPI LGMR MMIO base address
#define PCH_ESPI_LGMR_MMIO_SIZE         0x00010000     ///< 64KB
#define PCH_ESPI_SEGMR_BASE_ADDRESS     0xFE0C0000     ///< Second eSPI GMR MMIO base address
#define PCH_ESPI_SEGMR_MMIO_SIZE        0x00010000     ///< 64KB
#define PCH_TRACE_HUB_MTB_BASE_ADDRESS  0xFE100000     ///< TraceHub MTB MMIO base address
#define PCH_TRACE_HUB_MTB_MMIO_SIZE     0x00100000     ///< 1MB
#define PCH_TRACE_HUB_FW_BASE_ADDRESS   0xFE200000     ///< TraceHub FW MMIO base address
#define PCH_TRACE_HUB_FW_MMIO_SIZE      0x00200000     ///< 2MB
#define PCH_PSE_BASE_ADDRESS            0xFE400000     ///< PSE MMIO base address
#define PCH_PSE_MMIO_SIZE               0x00200000     ///< 2MB
#define PCH_TEMP_BASE_ADDRESS           0xFE600000     ///< preserved temp address for misc usage,
#define PCH_TEMP_MMIO_SIZE              0x00200000     ///< 2MB

#endif // _PCH_PRESERVED_RESOURCES_H_

