/** @file
  PCH Interrupts Info.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#ifndef _ITSS_LIB_INTERNAL_H_
#define _ITSS_LIB_INTERNAL_H_

#define VALID_DEV_NO    0  ///< Device does not exist
#define VALID_DEV_YES   1  ///< Device exists

#define INTERRUPT_NO    0  ///< Device doesn't generate interrupts
#define INTERRUPT_YES   1  ///< Device generates interrupts

#define USES_PIRQ_NO    0  ///< Device does not route its interrupt to PIRQ
#define USES_PIRQ_YES   1  ///< Device is under INTx->PIRQy mapping

#define INTP_NO_REQ     0  ///< There is no requirement regarding INTP programming
#define INTP_MUST_SET   1  ///< INTP is RWO and needs to be programmed
#define INTP_IS_INTA    2  ///< INTP is required to be set to INTA
#define INTP_IS_INTB    3  ///< INTP is required to be set to INTB
#define INTP_IS_INTC    4  ///< INTP is required to be set to INTC
#define INTP_IS_INTD    5  ///< INTP is required to be set to INTD

#define IRQ_UNIQUE_NO       0  ///< IRQx can be shareable for this device
#define IRQ_UNIQUE_SERIALIO 1  ///< SerialIo devices need unique IRQ
#define IRQ_UNIQUE_SCS      2  ///< SCS devices need unique IRQ
#define IRQ_UNIQUE_OTG      3  ///< OTG device need unique IRQ
#define IRQ_UNIQUE_ISH      4  ///< ISH device need unique IRQ
#define IRQ_UNIQUE_PSE      5  ///< PSE device need unique IRQ

typedef struct {
  UINT32        Device           :5;  ///< Device number
  UINT32        Function         :3;  ///< Device function
  UINT32        ValidDevice      :1;  ///< Flag which will indicate if DxFy i a PCH device
  UINT32        UsesInterrupts   :1;  ///< Flag indicating if device is using interrupts
  UINT32        UsesPirq         :1;  ///< Flag indicating that device uses INTx->PIRQ mapping
  UINT32        IntPinRequirement:3;  ///< Setting on how INTP reg should be treated
  ///
  /// 0 - IRQ can be shareable, other - for IRQ>23 it needs to be unique among all devices
  /// or if IRQ <=23 it needs to be unique only between devices with the same PortID
  ///
  UINT32        IrqUnique        :3;
  UINT32        Rsvd             :15; ///< Reserved
} PCH_DEV_INT_INFO;

/**
  Get Interrupt Info data

  @param[out] Size       Current size of the interrupt info

  @retval Pointer to Interrupt Info data on current PCH
**/
CONST PCH_DEV_INT_INFO*
GetInterruptInfoData (
  OUT UINT32  *Size
  );

//
// Structure for storing mapping between device number and PIRx register
//
typedef struct {
  UINT8   Device;
  UINT8   PirIndex;
} PCH_PIRX_REGISTER;

/**
  Get PIRx register data table

  @param[out] Size       Current size of the PIRx register table (number of PIRx registers)

  @retval Pointer to PIRx register data table
**/
CONST PCH_PIRX_REGISTER*
GetPirxRegData (
  OUT UINT32  *Size
  );

#endif

