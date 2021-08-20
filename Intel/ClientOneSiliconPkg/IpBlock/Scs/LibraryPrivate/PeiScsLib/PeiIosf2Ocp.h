/** @file
  Iosf2Ocp header.

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

#ifndef _PEI_IOSF2OCP_H_
#define _PEI_IOSF2OCP_H_

typedef struct {
  PCH_SBI_PID  BridgePortId;
  UINT8        ControllerIndex;
} IOSF2OCP_PORT;

/**
  Initializes Iosf2Ocp bridges.
**/
VOID
Iosf2OcpInitializeBridges (
  VOID
  );

/**
  This function disables BAR1 for a given controller on Iosf2Ocp brige.

  @param[in]  Iosf2OcpPort  Pointer to given controller described by IOSF2OCP_PORT structure
**/
VOID
Iosf2OcpDisableBar1 (
  IN IOSF2OCP_PORT  *Iosf2OcpPort
  );

/**
  Configures interrupts in the Iosf2Ocp bridge.

  @param[in] Iosf2OcpPort  Pointer to given controller described by IOSF2OCP_PORT structure
  @param[in] InterruptPin  Interrupt pin number
  @param[in] Irq           IRQ number
**/
VOID
Iosf2OcpConfigureInterrupts (
  IN IOSF2OCP_PORT  *Iosf2OcpPort,
  IN UINT8          InterruptPin,
  IN UINT8          Irq
  );

/**
  This function enables UFS on Iosf2Ocp bridge.
  It supports up to 2 UFS HC on a single bridge.

  @param[in] UfsPort       Pointer to IOSF2OCP_PORT structure describing UFS controller
  @param[in] UsedLanesNum  Number of lanes used by UFS controller
**/
VOID
Iosf2OcpEnableUfs (
  IN IOSF2OCP_PORT  *UfsPort,
  IN UINT32         UsedLanesNum
  );

/**
  Disables UFS controller on Iosf2Ocp bridge.

  @param[in] UfsPort  Structure describing UFS controller location on Iosf2Ocp bridge.
**/
VOID
Iosf2OcpDisableUfs (
  IN IOSF2OCP_PORT  *UfsPort
  );

/**
  Sets XSOC Bit 13 of General Purpose RW Register1 on Iosf2Ocp bridge.

  @param[in] Iosf2OcpPort  Pointer to given controller described by IOSF2OCP_PORT structure
**/
VOID
Iosf2OcpUfsXSoc (
  IN IOSF2OCP_PORT  *Iosf2OcpPort
  );

/**
  Enables in-line encryption feature for UFS controller.

  @param[in] UfsPort  Pointer to IOSF2OCP_PORT structure describing UFS controller
**/
VOID
Iosf2OcpEnableUfsInlineEncryption (
  IN IOSF2OCP_PORT  *UfsPort
  );

/**
  Unlocks fields in eMMC DLL registers.

  @param[in] EmmcPort  Pointer to IOSF2OCP_PORT structure describing eMMC controller
**/
VOID
Iosf2OcpUnlockEmmcDll (
  IN IOSF2OCP_PORT  *EmmcPort
  );

/**
  Disables eMMC controller on Iosf2Ocp bridge.

  @param[in] EmmcPort  Structure describing eMMC controller location on Iosf2Ocp bridge
**/
VOID
Iosf2OcpDisableEmmc (
  IN IOSF2OCP_PORT  *EmmcPort
  );

/**
  Configures 1p8 voltage related registers in Iosf2Ocp bridge.

  @param[in] SdCardPort             Pointer to IOSf2OCP_PORT structure describing SdCard controller
  @param[in] PowerEnableActiveHigh  Flag to indicate if POWER_ENABLE# should be active high
**/
VOID
Iosf2OcpSdCard1p8Enable (
  IN IOSF2OCP_PORT  *SdCardPort,
  IN BOOLEAN        PowerEnableActiveHigh
  );

/**
  Disables SdCard controller on Iosf2Ocp bridge.

  @param[in] SdCardPort  Structure describing SdCard location on Iosf2Ocp bridge
**/
VOID
Iosf2OcpDisableSdCard (
  IN IOSF2OCP_PORT  *SdCardPort
  );

/**
  Get UFS controller location on Iosf2Ocp bridge.

  @param[in] UfsIndex  Global index identifying UFS controller instance

  @return IOSF2OCP_PORT  Structure describing UFS controller location on Iosf2Ocp bridge
**/
IOSF2OCP_PORT*
Iosf2OcpGetUfsPort (
  IN UINT8  UfsIndex
  );

/**
  Get SdCard controller port on Iosf2Ocp bridge.

  @return IOSF2OCP_PORT  Structure describing SdCard controller location on Iosf2Ocp bridge
**/
IOSF2OCP_PORT*
Iosf2OcpGetSdCardPort (
  VOID
  );

/**
  Get eMMC controller location on Iosf2Ocp bridge.

  @return  IOSF2OCP_PORT  Structure describing eMMC controller location on Iosf2Ocp bridge
**/
IOSF2OCP_PORT*
Iosf2OcpGetEmmcPort (
  VOID
  );

#endif

