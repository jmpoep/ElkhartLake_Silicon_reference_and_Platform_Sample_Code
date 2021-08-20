/** @file
  Interrupt policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#ifndef _INTERRUPT_CONFIG_H_
#define _INTERRUPT_CONFIG_H_

#define INTERRUPT_CONFIG_REVISION 1
extern EFI_GUID gInterruptConfigGuid;

#pragma pack (push,1)

//
// --------------------- Interrupts Config ------------------------------
//
typedef enum {
  PchNoInt,        ///< No Interrupt Pin
  PchIntA,
  PchIntB,
  PchIntC,
  PchIntD
} PCH_INT_PIN;

///
/// The PCH_DEVICE_INTERRUPT_CONFIG block describes interrupt pin, IRQ and interrupt mode for PCH device.
///
typedef struct {
  UINT8        Device;                  ///< Device number
  UINT8        Function;                ///< Device function
  UINT8        IntX;                    ///< Interrupt pin: INTA-INTD (see PCH_INT_PIN)
  UINT8        Irq;                     ///< IRQ to be set for device.
} PCH_DEVICE_INTERRUPT_CONFIG;

#define PCH_MAX_DEVICE_INTERRUPT_CONFIG 128       ///< Number of all PCH devices
#define PCH_MAX_PXRC_CONFIG               8       ///< Number of PXRC registers in ITSS
#define PCH_MAX_ITSS_IPC_REGS             4       ///< Number of IPC registers in ITSS
#define PCH_MAX_ITSS_IRQ_NUM            120       ///< Maximum number of IRQs


///
/// The PCH_INTERRUPT_CONFIG block describes interrupt settings for PCH.
///
typedef struct {
  CONFIG_BLOCK_HEADER          Header;                                          ///< Config Block Header
  UINT8                        NumOfDevIntConfig;                               ///< Number of entries in DevIntConfig table
  UINT8                        Rsvd0[3];                                        ///< Reserved bytes, align to multiple 4.
  PCH_DEVICE_INTERRUPT_CONFIG  DevIntConfig[PCH_MAX_DEVICE_INTERRUPT_CONFIG];   ///< Array which stores PCH devices interrupts settings
  UINT8                        GpioIrqRoute;                                    ///< Interrupt routing for GPIO. Default is <b>14</b>.
  UINT8                        SciIrqSelect;                                    ///< Interrupt select for SCI. Default is <b>9</b>.
  UINT8                        TcoIrqSelect;                                    ///< Interrupt select for TCO. Default is <b>9</b>.
  UINT8                        TcoIrqEnable;                                    ///< Enable IRQ generation for TCO. <b>0: Disable</b>; 1: Enable.
} PCH_INTERRUPT_CONFIG;

#pragma pack (pop)

#endif // _INTERRUPT_CONFIG_H_
