/** @file
  Wpcn381U driver Sio interface.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/
#ifndef _REGISTER_H
#define _REGISTER_H

//
// Define some fixed platform device location information
//
#define LPC_SIO_CONFIG_DEFAULT_PORT 0x2E
#define LPC_SIO_INDEX_DEFAULT_PORT  0x2E
#define LPC_SIO_DATA_DEFAULT_PORT   0x2F

//
// Port address for LPC
//
#define SIO_CONFIG_PORT    LPC_SIO_CONFIG_DEFAULT_PORT
#define SIO_INDEX_PORT     LPC_SIO_INDEX_DEFAULT_PORT
#define SIO_DATA_PORT      LPC_SIO_DATA_DEFAULT_PORT

//
// Logical Device in Winbond WPCN381U
//
#define SIO_PARA_LDN      0x1
#define SIO_COM2_LDN      0x2
#define SIO_COM1_LDN      0x3
#define SIO_GPIO_LDN      0x7
#define SIO_INVALID_LDN   0xFF

//
// Global Registers in Winbond WPCN381U
//
#define REG_CONFIG_CONTROL              0x02
#define R_SIO_LOGICAL_DEVICE            0x07
#define R_DEVICE_ID                     0x20
#define R_SIO_CFG_1                     0x21
#define R_SIO_CFG_2                     0x22
#define R_SIO_CFG_6                     0x26
#define R_REVISION_ID                   0x27
#define R_SIO_CLK_CFG                   0x29
#define R_SIO_CFG_C                     0x2C
#define R_SIO_ACTIVATE                  0x30
#define R_SIO_BASE_ADDRESS_HIGH         0x60
#define R_SIO_BASE_ADDRESS_LOW          0x61
#define R_SIO_BASE_ADDRESS_HIGH2        0x62
#define R_SIO_BASE_ADDRESS_LOW2         0x63
#define R_SIO_PRIMARY_INTERRUPT_SELECT  0x70
#define R_SIO_SECOND_INTERRUPT_SELECT   0x72
#define R_SIO_DMA_CHANNEL_SELECT        0x74

#endif
