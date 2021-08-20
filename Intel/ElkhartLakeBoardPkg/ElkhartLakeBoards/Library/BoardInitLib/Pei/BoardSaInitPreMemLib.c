/** @file
 Source code for the board SA configuration Pcd init functions in Pre-Memory init phase.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include "BoardSaConfigPreMem.h"
#include <Library/CpuPlatformLib.h>
#include <Pins/GpioPinsVer3.h>
#include <Pins/GpioPinsVer1N.h>
#include <PlatformBoardId.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <PlatformBoardConfig.h>
#include <Library/PcdLib.h>

/**
  MRC configuration init function for PEI pre-memory phase.

  @param[in]  VOID

  @retval VOID
**/
VOID
EhlSaMiscConfigInit (
  VOID
  )
{
  PcdSet8S (PcdSaMiscUserBd, MrcBoardTypeMobile);
  PcdSet16S (PcdSaDdrFreqLimit, 0);

  return;
}

/**
  Board Memory Init related configuration init function for PEI pre-memory phase.

  @param[in]  VOID

  @retval VOID
**/
VOID
EhlMrcConfigInit (
  VOID
  )
{
  BOOLEAN ExternalSpdPresent;
  UINT16    BoardId;
  BoardId = PcdGet16 (PcdBoardId);

  switch (BoardId) {
    case BoardIdJslLp4xType4Rvp1:
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdEhlLp4xType3Crb:
    case BoardIdJslLp4xErb:
    default:
      PcdSet8S (PcdMrcSpdAddressTable0, 0xA0);
      PcdSet8S (PcdMrcSpdAddressTable1, 0xA2);
      PcdSet8S (PcdMrcSpdAddressTable2, 0xA4);
      PcdSet8S (PcdMrcSpdAddressTable3, 0xA6);
      PcdSet8S (PcdMrcSpdAddressTable4, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable5, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable6, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable7, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable8, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable9, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable10, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable11, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable12, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable13, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable14, 0x0);
      PcdSet8S (PcdMrcSpdAddressTable15, 0x0);
      break;
  }



  // EHL uses the same RCOMP resistors for all DDR types
  PcdSet32S (PcdMrcRcompResistor, (UINTN) EhlRcompResistorZero);

  // Use default RCOMP target values for all boards
  PcdSet32S (PcdMrcRcompTarget, (UINTN) RcompTargetEhl);

  // Default is NIL
  PcdSetBoolS (PcdMrcDqPinsInterleavedControl, TRUE);
  PcdSetBoolS (PcdMrcDqPinsInterleaved, FALSE);

  // SPD is the same size for all boards
  PcdSet16S (PcdMrcSpdDataSize, sizeof (mLpddr4Ddp8Gb200bSpd));

  switch (BoardId) {
    case BoardIdJslLp4xErb:
      PcdSet16S (PcdMrcDqsMapCpu2DramSize, sizeof (DqsMapCpu2DramJslLp4xErb));
      PcdSet32S (PcdMrcDqsMapCpu2Dram, (UINTN) DqsMapCpu2DramJslLp4xErb);
      // Setting the default DQ Byte Map. It may be overriden to board specific settings below.
      PcdSet32S (PcdMrcDqByteMap, (UINT32) (VOID *) &DqByteMapJsl);
      PcdSet16S (PcdMrcDqByteMapSize, sizeof (DqByteMapJsl));
      break;
    case BoardIdJslLp4xType4Rvp1:
      PcdSet32S (PcdMrcDqsMapCpu2Dram, (UINTN) DqsMapCpu2DramJslLp4Type4Rvp);
      PcdSet16S (PcdMrcDqsMapCpu2DramSize, sizeof (DqsMapCpu2DramJslLp4Type4Rvp));
      // Setting the default DQ Byte Map. It may be overriden to board specific settings below.
      PcdSet32S (PcdMrcDqByteMap, (UINT32) (VOID *) &DqByteMapEhl);
      PcdSet16S (PcdMrcDqByteMapSize, sizeof (DqByteMapEhl));
    break;

    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlLp4xType3Crb:
    default:
      // DqsMapCpu2Dram is the same size for all boards
      PcdSet32S (PcdMrcDqsMapCpu2Dram, (UINTN) DqsMapCpu2DramEhlLp4Type4Rvp);
      PcdSet16S (PcdMrcDqsMapCpu2DramSize, sizeof (DqsMapCpu2DramEhlLp4Type4Rvp));
      // Setting the default DQ Byte Map. It may be overriden to board specific settings below.
      PcdSet32S (PcdMrcDqByteMap, (UINT32) (VOID *) &DqByteMapEhl);
      PcdSet16S (PcdMrcDqByteMapSize, sizeof (DqByteMapEhl));
      break;
  }

  // DDR4 boards have external SPD on UDIMM/SO-DIMM
  ExternalSpdPresent = FALSE;

  // Check for external SPD presence on LPDDR4x boards
  switch (BoardId) {
    case BoardIdJslLp4xErb:
      if (IsSimicsEnvironment ()) {
        ExternalSpdPresent = TRUE;
      } else {
        ExternalSpdPresent = FALSE;
        PcdSet16S (PcdMrcSpdDataSize, sizeof (mLpddr4xDdp8Gb200bSpd));
        PcdSet32S (PcdMrcSpdData, (UINT32) (VOID *) &mLpddr4xDdp8Gb200bSpd);
      }
      break;

    case BoardIdEhlLp4xType4Erb:
    case BoardIdJslLp4xType4Rvp1:
    case BoardIdEhlLp4xType4Rvp1:
      if (IsSimicsEnvironment ()) {
        ExternalSpdPresent = TRUE;
      } else {
        ExternalSpdPresent = FALSE;
        //ExternalSpdPresent = PcdGetBool(PcdSpdPresent);
      }
      break;
    case BoardIdEhlLp4xType3Crb:
      ExternalSpdPresent = FALSE;
      break;
    case BoardIdEhlDdr4Type3Rvp2:
      if (PcdGetBool(PcdSpdPresent) == TRUE) {
        ExternalSpdPresent = TRUE; // use SPD from so-dimm
      } else {
        ExternalSpdPresent = FALSE; // use hardcoded SPD for RVP2
      };
      break;
    default:
      // DDR4 boards have external SPD on UDIMM/SO-DIMM
      ExternalSpdPresent = TRUE;
      break;
  }
 // ExternalSpdPresent = PcdGetBool(PcdSpdPresent);

  // Check for external SPD presence on LPDDR4 boards

  if (!ExternalSpdPresent) {
    // Use internal SPD table if external is not present
      switch (BoardId) {
      case BoardIdJslLp4xErb:
        PcdSet32S (PcdMrcSpdData, (UINT32) (VOID *) &mLpddr4xDdp8Gb200bSpd);
        break;
      case BoardIdEhlDdr4Type3Rvp2:
        PcdSet32S (PcdMrcSpdData, (UINT32) (VOID *) &DDR4_SPD_MTA4ATF51264HZ_3G2E1);
        break;
      case BoardIdJslLp4xType4Rvp1:
      case BoardIdEhlLp4xType4Erb:
      case BoardIdEhlLp4xType4Rvp1:
      case BoardIdEhlLp4xType3Crb:
      default:
        PcdSet32S (PcdMrcSpdData, (UINT32) (VOID *) &mLpddr4xDdp8Gb200bSpd);
        break;
    }
    PcdSet8S (PcdMrcSpdAddressTable0, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable1, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable2, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable3, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable4, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable5, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable6, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable7, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable8, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable9, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable10, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable11, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable12, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable13, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable14, 0x00);
    PcdSet8S (PcdMrcSpdAddressTable15, 0x00);
  }

  //
  // CA Vref routing: board-dependent
  // 0 - VREF_CA goes to both CH_A and CH_B (LPDDR3/DDR3L)
  // 1 - VREF_CA to CH_A, VREF_DQ_A to CH_B (should not be used)
  // 2 - VREF_CA to CH_A, VREF_DQ_B to CH_B (DDR4)
  //
  // Set it to 2 for all our DDR4 boards; it is ignored for LPDDR4
  //
  PcdSet8S (PcdMrcCaVrefConfig, 2);

  return;
}

/**
  Board SA related GPIO configuration init function for PEI pre-memory phase.

  @param[in]  VOID

  @retval VOID
**/
VOID
EhlSaGpioConfigInit (
  VOID
  )
{
  UINT16    BoardId;
  BoardId = PcdGet16 (PcdBoardId);
  //
  // Assigning default values to PCIE RTD3 GPIOs
  //
  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdJslLp4xType4Rvp1:
      PcdSet8S (PcdRootPortIndex, 4);
      PcdSet8S (PcdPcieSlot1GpioSupport, PchGpio);
      PcdSet8S (PcdPcieSlot1HoldRstExpanderNo, 0);
      PcdSet32S (PcdPcieSlot1HoldRstGpioNo, GPIO_VER3_GPD11);
      PcdSetBoolS (PcdPcieSlot1HoldRstGpioPolarity, PIN_GPIO_ACTIVE_LOW);
      PcdSet8S (PcdPcieSlot1PwrEnableExpanderNo, 0);
      PcdSet32S (PcdPcieSlot1PwrEnableGpioNo, GPIO_VER3_GPP_E13);
      PcdSetBoolS (PcdPcieSlot1PwrEnableGpioPolarity, PIN_GPIO_ACTIVE_LOW);
      break;
    case BoardIdEhlLp4xType3Crb:
      PcdSet8S (PcdRootPortIndex, 4);
      PcdSet8S (PcdPcieSlot1GpioSupport, PchGpio);
      PcdSet8S (PcdPcieSlot1HoldRstExpanderNo, 0);
      PcdSet32S (PcdPcieSlot1HoldRstGpioNo, GPIO_VER3_GPD11);
      PcdSetBoolS (PcdPcieSlot1HoldRstGpioPolarity, PIN_GPIO_ACTIVE_HIGH);
      break;
    case BoardIdJslLp4xErb:
      PcdSet8S(PcdRootPortIndex, 4);
      PcdSet8S(PcdPcieSlot1GpioSupport, PchGpio);
      PcdSet8S(PcdPcieSlot1HoldRstExpanderNo, 0);
      PcdSet32S(PcdPcieSlot1HoldRstGpioNo, GPIO_VER1_N_GPP_C4);
      PcdSetBoolS(PcdPcieSlot1HoldRstGpioPolarity, PIN_GPIO_ACTIVE_LOW);
      PcdSet8S(PcdPcieSlot1PwrEnableExpanderNo, 0);
      PcdSet32S(PcdPcieSlot1PwrEnableGpioNo, GPIO_VER1_N_GPP_D3);
      PcdSetBoolS(PcdPcieSlot1PwrEnableGpioPolarity, PIN_GPIO_ACTIVE_LOW);
    default:
      break;
  }

  // @TODO Need to update the PEG RESET GPIOs

  //
  // PCIE RTD3 GPIO
  //

  return;
}

/**
  Board USB related configuration init function for PEI pre-memory phase.

  @param[in]  VOID

  @retval VOID
**/
VOID
EhlSaUsbConfigInit (
  VOID
  )
{
  PcdSet8S (PcdCpuUsb30PortEnable, 0x0);

  return;
}
