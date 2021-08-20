/** @file
  Header file for private PEI ITSS Lib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#ifndef _PEI_ITSS_LIB_H_
#define _PEI_ITSS_LIB_H_

typedef struct _SI_POLICY_STRUCT SI_POLICY_PPI;

/**
  Retrieve interrupt configuration for a given PCH device (DxFy)

  @param[in]  SiPolicy  Policy
  @param[in]  Device    Device number
  @param[in]  Function  Function number
  @param[out] IntPin    Interrupt pin: INTA-INTD (see PCH_INT_PIN for reference)
  @param[out] ApicIrq   APIC IRQ number
**/
VOID
ItssGetDevIntConfig (
  IN  CONST SI_POLICY_PPI  *SiPolicy,
  IN  UINT8                Device,
  IN  UINT8                Function,
  OUT UINT8                *IntPin,
  OUT UINT8                *ApicIrq
  );

/**
  Retrieve interrupt pin for a given PCH device (DxFy)

  @param[in]  SiPolicy  Policy
  @param[in]  Device    Device number
  @param[in]  Function  Function number

  @retval Interrupt pin: INTA-INTD (see PCH_INT_PIN for reference)
**/
UINT8
ItssGetDevIntPin (
  IN  CONST SI_POLICY_PPI  *SiPolicy,
  IN  UINT8                Device,
  IN  UINT8                Function
  );

/**
  Retrieve IRQ for GPIO controller

  @param[in]  SiPolicy  Policy

  @retval GpioIrq
**/
UINT8
ItssGetGpioDevIntConfig (
  IN CONST SI_POLICY_PPI  *SiPolicy
  );

/**
  Retrieve IRQ for TCO

  @param[in]  SiPolicy  Policy

  @retval TcoIrq     TCO IRQ. If 0 TCO interrupt is not to be enabled
**/
UINT8
ItssGetTcoDevIntConfig (
  IN CONST SI_POLICY_PPI  *SiPolicy
  );

/**
  Retrieve IRQ for PMC SCI

  @param[in]  SiPolicy  Policy

  @retval PmcSciIrq
**/
UINT8
ItssGetPmcSciDevIntConfig (
  IN CONST SI_POLICY_PPI  *SiPolicy
  );

/**
  Configures PCH interrupts

  @param[in] SiPolicy          Policy
**/
VOID
ItssConfigureInterrupts (
  IN CONST SI_POLICY_PPI  *SiPolicy
  );

/**
  Initialize IOAPIC according to IoApicConfig policy of the PCH
  Policy PPI

  @param[in] SiPolicyPpi          The SI Policy PPI instance

**/
VOID
ItssInitIoApic (
  IN CONST SI_POLICY_PPI  *SiPolicy
  );

/**
  Before any interrupt is enabled, set master message enable.
**/
VOID
ItssSetMasterMessageEnable (
  VOID
  );

/**
  Write to mask registers of master and slave 8259 PICs.
**/
VOID
ItssMask8259Interrupts (
  VOID
  );

#endif // _PEI_ITSS_LIB_H_
