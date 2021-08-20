/** @file
  Iosf2Ocp bridge helper functions.

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

#include "PeiIosf2OcpInternal.h"

/**
  Converts Iosf2Ocp controller index into PCI_CFG_CTRL register offset.

  @param[in] ControllerIndex  Index of the controller on the bridge.

  @return  UINT32  Offset of the PCI_CFG_CTRL register corresponding to Controller index
**/
STATIC
UINT32
Iosf2OcpGetPciCfgCtrlOffset (
  IN UINT8  ControllerIndex
  )
{
  return R_SCS_PCR_PCICFGCTR_BASE + (4 * ControllerIndex);
}

/**
  This function configures power and clock gating policy in Iosf2Ocp bridge
  based on value passed by the caller.

  @param[in] BridgePortId              Port ID of target bridge
  @param[in] PowerAndClockGatingValue  Value to be written to power and clock gating register
**/
VOID
Iosf2OcpConfigurePowerAndClockGating (
  IN PCH_SBI_PID  BridgePortId,
  IN UINT32       PowerAndClockGatingValue
  )
{
  PchPcrWrite32 (
    BridgePortId,
    R_SCS_PCR_PMCTL,
    (BIT5| BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
    );

  //
  // Be careful not to overwrite the UFS enable and
  // UFS dual lane enable bits while updating power
  // and clock gating registers.
  //
  PchPcrAndThenOr32 (
    BridgePortId,
    R_SCS_PCR_GPPRVRW1,
    (UINT32)~B_SCS_PCR_GPPRVRW1_PG_CG,
    PowerAndClockGatingValue & B_SCS_PCR_GPPRVRW1_PG_CG
    );
}

/**
  Enables Iosf2Ocp bridge to send snooped transactions on
  IOSF fabric.

  @param[in]  BridgePortId  Iosf2Ocp bridge sideband port id
**/
VOID
Iosf2OcpEnableSnoopedTransactions (
  IN PCH_SBI_PID  BridgePortId
  )
{
  PchPcrAndThenOr32 (
    BridgePortId,
    R_SCS_PCR_IOSFCTL,
    (UINT32) ~0,
    B_SCS_PCR_IOSFCTL_NSNPDIS
    );
}

/**
  This function enables MPHY PLL to Iosf2Ocp bridge.

  @param[in] BridgePortId  Bridge sideband port id
**/
STATIC
VOID
Iosf2OcpEnablePll (
  IN PCH_SBI_PID  BridgePortId
  )
{
  //
  // Set GPPRVRW6 31b PLL En to 1
  //
  PchPcrAndThenOr32 (
    BridgePortId,
    R_SCS_PCR_GPPRVRW6,
    (UINT32) ~0,
    BIT31
    );
}

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
  )
{
  UINT32  Data32Or;
  UINT32  Data32And;

  if (Iosf2OcpPort == NULL) {
    ASSERT (FALSE);
    return;
  }

  Data32Or = (UINT32) ((InterruptPin << N_SCS_PCR_PCICFGCTR_IPIN1) |
                       (Irq << N_SCS_PCR_PCICFGCTR_PCI_IRQ));
  Data32And = ~(UINT32) (B_SCS_PCR_PCICFGCTR_PCI_IRQ | B_SCS_PCR_PCICFGCTR_ACPI_IRQ | B_SCS_PCR_PCICFGCTR_IPIN1);

  PchPcrAndThenOr32 (
    Iosf2OcpPort->BridgePortId,
    Iosf2OcpGetPciCfgCtrlOffset (Iosf2OcpPort->ControllerIndex),
    Data32And,
    Data32Or
    );
}

/**
  This function disables BAR1 for a given controller on Iosf2Ocp brige.

  @param[in]  Iosf2OcpPort  Pointer to given controller described by IOSF2OCP_PORT structure
**/
VOID
Iosf2OcpDisableBar1 (
  IN IOSF2OCP_PORT  *Iosf2OcpPort
  )
{
  if (Iosf2OcpPort == NULL) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    Iosf2OcpPort->BridgePortId,
    Iosf2OcpGetPciCfgCtrlOffset (Iosf2OcpPort->ControllerIndex),
    (UINT32) ~0u,
    B_SCS_PCR_PCICFGCTR_BAR1DIS
    );
}

/**
  Disables access to PCI config space for a given controller on
  Iosf2Ocp bridge.

  @param[in] Iosf2OcpPort  Pointer to given controller described by IOSF2OCP_PORT structure
**/
STATIC
VOID
Iosf2OcpDisablePciCfgSpace (
  IN IOSF2OCP_PORT  *Iosf2OcpPort
  )
{
  if (Iosf2OcpPort == NULL) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    Iosf2OcpPort->BridgePortId,
    Iosf2OcpGetPciCfgCtrlOffset (Iosf2OcpPort->ControllerIndex),
    (UINT32) ~0u,
    B_SCS_PCR_PCICFGCTR_PCI_CFG_DIS
    );
}

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
  )
{
  UINT32  Data32Or;

  if ((UfsPort == NULL) || (UsedLanesNum == 0) || (UsedLanesNum > 2)) {
    ASSERT (FALSE);
    return;
  }

  Data32Or = 0;
  switch (UfsPort->ControllerIndex) {
    case 0:
      Data32Or |= B_SCS_PCR_GPPRVRW1_UFS0_ENABLE;
      if (UsedLanesNum == 2) {
        Data32Or |= B_SCS_PCR_GPPRVRW1_UFS0_DUAL_LANE;
      }
      break;
    case 1:
      Data32Or |= B_SCS_PCR_GPPRVRW1_UFS1_ENABLE;
      if (UsedLanesNum == 2) {
        Data32Or |= B_SCS_PCR_GPPRVRW1_UFS1_DUAL_LANE;
      }
      break;
    default:
      ASSERT (FALSE);
      return;
  }

  //
  // Hardware default for dual lane is '0' which indicates that a single lane should be used.
  //
  PchPcrAndThenOr32 (
    UfsPort->BridgePortId,
    R_SCS_PCR_GPPRVRW1,
    (UINT32) ~0,
    Data32Or
    );

  //
  // PLL enable is a setting global to Iosf2Ocp bridge instance.
  // Since this has to be enabled if at least one of the UFS controllers
  // is enabled there should be no harm in calling it multiple times.
  //
  Iosf2OcpEnablePll (UfsPort->BridgePortId);
}

/**
  Sets XSOC Bit 13 of General Purpose RW Register1 on Iosf2Ocp bridge.

  @param[in] Iosf2OcpPort  Pointer to given controller described by IOSF2OCP_PORT structure
**/
VOID
Iosf2OcpUfsXSoc (
  IN IOSF2OCP_PORT  *Iosf2OcpPort
  )
{
  PchPcrAndThenOr32 (
    Iosf2OcpPort->BridgePortId,
    R_SCS_PCR_GPPRVRW1,
    (UINT32) ~0,
    B_SCS_PCR_GPPRVRW1_UFS_XSOC
    );
}

/**
  Enables in-line encryption feature for UFS controller.

  @param[in] UfsPort  Pointer to IOSF2OCP_PORT structure describing UFS controller
**/
VOID
Iosf2OcpEnableUfsInlineEncryption (
  IN IOSF2OCP_PORT  *UfsPort
  )
{
  UINT32  Data32Or;

  switch (UfsPort->ControllerIndex) {
    case 0:
      Data32Or = B_SCS_PCR_GPPRVRW1_UFS0_IES;
      break;
    case 1:
      Data32Or = B_SCS_PCR_GPPRVRW1_UFS1_IES;
      break;
    default:
      ASSERT (FALSE);
      return;
  }

  PchPcrAndThenOr32 (
    UfsPort->BridgePortId,
    R_SCS_PCR_GPPRVRW1,
    (UINT32) ~0,
    Data32Or
    );
}

/**
  Unlocks fields in eMMC DLL registers.

  @param[in] EmmcPort  Pointer to IOSF2OCP_PORT structure describing eMMC controller
**/
VOID
Iosf2OcpUnlockEmmcDll (
  IN IOSF2OCP_PORT  *EmmcPort
  )
{
  if (EmmcPort == NULL) {
    ASSERT (FALSE);
    return;
  }

  PchPcrAndThenOr32 (
    EmmcPort->BridgePortId,
    R_SCS_PCR_GPPRVRW6,
    (UINT32) ~0,
    BIT30
    );
}

/**
  Disables eMMC controller on Iosf2Ocp bridge.

  @param[in] EmmcPort  Structure describing eMMC controller location on Iosf2Ocp bridge
**/
VOID
Iosf2OcpDisableEmmc (
  IN IOSF2OCP_PORT  *EmmcPort
  )
{
  if (EmmcPort == NULL) {
    ASSERT (FALSE);
    return;
  }
  Iosf2OcpDisablePciCfgSpace (EmmcPort);
  PchPcrAndThenOr32 (
    EmmcPort->BridgePortId,
    R_SCS_PCR_GPPRVRW2,
    (UINT32) ~0,
    BIT1
    );
}

/**
  Configures 1p8 voltage related registers in Iosf2Ocp bridge.

  @param[in] SdCardPort             Pointer to IOSf2OCP_PORT structure describing SdCard controller
  @param[in] PowerEnableActiveHigh  Flag to indicate if POWER_ENABLE# should be active high
**/
VOID
Iosf2OcpSdCard1p8Enable (
  IN IOSF2OCP_PORT  *SdCardPort,
  IN BOOLEAN        PowerEnableActiveHigh
  )
{
  if (SdCardPort == NULL) {
    ASSERT (FALSE);
    return;
  }
  //
  // Set Rcomp delay from 1p8mode to 10ms
  // Set offset 614h bit[7:0] = 0x7F
  //
  PchPcrAndThenOr32 (
    SdCardPort->BridgePortId,
    R_SCS_PCR_GPPRVRW6,
    (UINT32) ~B_SCS_PCR_GPPRVRW6_1P8_SEL_DELAY,
    V_SCS_PCR_GPPRVRW6_1P8_SEL_DELAY
    );

  if (PowerEnableActiveHigh) {
    //
    // Set VDD1_Invert to 1 to make SD Card VDD1_POWER_ENABLE active HIGH.
    // Default is active LOW.
    // offset 604h [16] = 1b
    //
    PchPcrAndThenOr32 (
      SdCardPort->BridgePortId,
      R_SCS_PCR_GPPRVRW2,
      (UINT32) ~0,
      B_SCS_PCR_GPPRVRW2_VDD1_INVERT
      );
  }
}

/**
  Disables SdCard controller on Iosf2Ocp bridge.

  @param[in] SdCardPort  Structure describing SdCard location on Iosf2Ocp bridge
**/
VOID
Iosf2OcpDisableSdCard (
  IN IOSF2OCP_PORT  *SdCardPort
  )
{
  if (SdCardPort == NULL) {
    ASSERT (FALSE);
    return;
  }
  Iosf2OcpDisablePciCfgSpace (SdCardPort);
  PchPcrAndThenOr32 (
    SdCardPort->BridgePortId,
    R_SCS_PCR_GPPRVRW2,
    (UINT32) ~0,
    BIT3
    );
}

/**
  Disables UFS controller on Iosf2Ocp bridge.

  @param[in] UfsPort  Structure describing UFS controller location on Iosf2Ocp bridge.
**/
VOID
Iosf2OcpDisableUfs (
  IN IOSF2OCP_PORT  *UfsPort
  )
{
  if (UfsPort == NULL) {
    ASSERT (FALSE);
    return;
  }

  switch (UfsPort->ControllerIndex) {
    case 0:
      Iosf2OcpDisablePciCfgSpace (UfsPort);
      PchPcrAndThenOr32 (
        UfsPort->BridgePortId,
        R_SCS_PCR_GPPRVRW2,
        (UINT32) ~0,
        BIT0
        );
      break;
    case 1:
      Iosf2OcpDisablePciCfgSpace (UfsPort);
      PchPcrAndThenOr32 (
        UfsPort->BridgePortId,
        R_SCS_PCR_GPPRVRW2,
        (UINT32) ~0,
        BIT1
        );
      break;
    default:
      ASSERT (FALSE);
  }
}

