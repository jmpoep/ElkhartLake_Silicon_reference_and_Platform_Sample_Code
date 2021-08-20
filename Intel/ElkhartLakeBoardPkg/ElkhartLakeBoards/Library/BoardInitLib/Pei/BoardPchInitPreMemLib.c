/** @file
 Source code for the board PCH configuration Pcd init functions for Pre-Mmeory Init phase.

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

#include <PiPei.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/BoardConfigLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Include/PlatformBoardId.h>
#include <GpioTableEhlPreMem.h>
#include <GpioTableEhlPostMem.h>
#include <Setup.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/PeiServicesLib.h>
#include <Register/PchRegsFia15.h>
#include <Register/PchPcrRegs.h>
#include <Library/PchPcrLib.h>

/**
  Board Root Port Clock Info configuration init function for PEI pre-memory phase.

  @retval EFI_SUCCESS   The function completed successfully.
**/
EFI_STATUS
EhlRootPortClkInfoInit (
  VOID
  )
{
  PCD64_BLOB Clock[PCH_MAX_PCIE_CLOCKS];
  UINT32     Index;
  UINT16     BoardId;
  UINT32     FiaLos1;

  BoardId = PcdGet16 (PcdBoardId);

  //
  // The default clock assignment will be FREE_RUNNING, which corresponds to PchClockUsageUnspecified
  // This is safe but power-consuming setting. If Platform code doesn't contain port-clock map for a given board,
  // the clocks will keep on running anyway, allowing PCIe devices to operate. Downside is that clocks will
  // continue to draw power. To prevent this, remember to provide port-clock map for every board.
  //
  for (Index = 0; Index < PCH_MAX_PCIE_CLOCKS; Index++) {
    Clock[Index].PcieClock.ClkReqSupported = TRUE;
    Clock[Index].PcieClock.ClockUsage = FREE_RUNNING;
  }

  //
  // Query the FIA Lane for LOSL4 as this could be single/multi vc
  //
  FiaLos1 = (0x000F0000 & PchPcrRead32(PID_FIA, R_PCH_FIA_15_PCR_LOS1_REG_BASE)) >> 16;

  ///
  /// Assign ClkReq signal to root port. (Base 0)
  /// For EHL, Set 0 - 5
  /// Note that if GbE is enabled, ClkReq assigned to GbE will not be available for Root Port.
  ///
  switch (BoardId) {
    case BoardIdJslLp4xType4Rvp1:
      Clock[0].PcieClock.ClockUsage = PCIE_PCH + 2;
      Clock[1].PcieClock.ClockUsage = NOT_USED;
      Clock[2].PcieClock.ClockUsage = PCIE_PCH + 9;
      Clock[3].PcieClock.ClockUsage = PCIE_PCH + 4;
      Clock[4].PcieClock.ClockUsage = NOT_USED;
      Clock[5].PcieClock.ClockUsage = NOT_USED;
      break;

    case BoardIdEhlLp4xType3Crb:
      if (FiaLos1 != 0xC) {  // Not PCIe Multi VC Lane
        Clock[0].PcieClock.ClockUsage = PCIE_PCH;       // x4 PCIE Slot 1 (Single VC RP)
      }
      else {
        Clock[0].PcieClock.ClockUsage = PCIE_PCH + 5;   // x4 PCIE Slot 1 (Multi VC RP)
      }
      Clock[1].PcieClock.ClockUsage = PCIE_PCH + 6;  // PCIE M.2 WLAN
      Clock[2].PcieClock.ClockUsage = PCIE_PCH + 4;  // PCIE M.2 NVME
      Clock[3].PcieClock.ClockUsage = NOT_USED;
      Clock[4].PcieClock.ClockUsage = NOT_USED;
      Clock[5].PcieClock.ClockUsage = NOT_USED;
      break;

    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    default:
      if (FiaLos1 != 0xC) {  // Not PCIe Multi VC Lane
        Clock[0].PcieClock.ClockUsage = PCIE_PCH;       // x4 PCIE Slot 1 (Single VC RP)
      }
      else {
        Clock[0].PcieClock.ClockUsage = PCIE_PCH + 5;   // x4 PCIE Slot 1 (Multi VC RP)
      }
      Clock[1].PcieClock.ClockUsage = NOT_USED;     // PCIE_PCH + 6 for Wifi bluetooth
      Clock[2].PcieClock.ClockUsage = PCIE_PCH + 4; // PCIE M.2 NVME
      Clock[3].PcieClock.ClockUsage = PCIE_PCH + 6; // x4 PCIE Slot 2
      Clock[4].PcieClock.ClockUsage = NOT_USED;
      Clock[5].PcieClock.ClockUsage = NOT_USED;
      break;
  }

  PcdSet64S (PcdPcieClock0,  Clock[ 0].Blob); // @todo Those individual PCDs should probably be replaced with something like a VOID* that can be iterated over
  PcdSet64S (PcdPcieClock1,  Clock[ 1].Blob); // @todo Those individual PCDs should probably be replaced with something like a VOID* that can be iterated over
  PcdSet64S (PcdPcieClock2,  Clock[ 2].Blob); // @todo Those individual PCDs should probably be replaced with something like a VOID* that can be iterated over
  PcdSet64S (PcdPcieClock3,  Clock[ 3].Blob); // @todo Those individual PCDs should probably be replaced with something like a VOID* that can be iterated over
  PcdSet64S (PcdPcieClock4,  Clock[ 4].Blob); // @todo Those individual PCDs should probably be replaced with something like a VOID* that can be iterated over
  PcdSet64S (PcdPcieClock5,  Clock[ 5].Blob); // @todo Those individual PCDs should probably be replaced with something like a VOID* that can be iterated over

  return EFI_SUCCESS;
}

/**
  Board GPIO Group Tier configuration init function for PEI pre-memory phase.
**/
VOID
EhlGpioGroupTierInit (
  VOID
  )
{
  //
  // GPIO Group Tier
  //
  PcdSet32S (PcdGpioGroupToGpeDw0, GPIO_VER3_GROUP_GPP_T); // Dummy
  PcdSet32S (PcdGpioGroupToGpeDw1, GPIO_VER3_GROUP_GPP_E); // For Home Button and Volume Up Button GPE
  PcdSet32S (PcdGpioGroupToGpeDw2, GPIO_VER3_GROUP_GPP_C); // For Volume Down Button GPE

  return;
}

/**
  GPIO init function for PEI pre-memory phase.

  @param[in]  BoardId   An unsigned integrer represent the board id.

  @retval EFI_SUCCESS   The function completed successfully.
**/
EFI_STATUS
EhlGpioTablePreMemInit (
  VOID
  )
{
  UINT16             GpioCount;
  UINTN              Size;
  EFI_STATUS         Status;
  GPIO_INIT_CONFIG  *GpioTable;
  UINT16             BoardId;

  BoardId = PcdGet16 (PcdBoardId);

  //
  // GPIO Table Init.
  //
  Status = EFI_SUCCESS;
  GpioCount = 0;
  Size = 0;
  GpioTable = NULL;


  switch(BoardId) {
    case BoardIdJslLp4xType4Rvp1:
       PcdSet32S (PcdBoardGpioTableWwanOnEarlyPreMem, (UINTN) mGpioTableJslEhlRvpWwanOnEarlyPreMem);
       PcdSet16S (PcdBoardGpioTableWwanOnEarlyPreMemSize, sizeof (mGpioTableJslEhlRvpWwanOnEarlyPreMem) / sizeof (GPIO_INIT_CONFIG));
       PcdSet32S (PcdBoardGpioTableWwanOffEarlyPreMem, (UINTN) mGpioTableJslEhlRvpWwanOffEarlyPreMem);
       PcdSet16S (PcdBoardGpioTableWwanOffEarlyPreMemSize, sizeof (mGpioTableJslEhlRvpWwanOffEarlyPreMem) / sizeof (GPIO_INIT_CONFIG));
       GpioTable = mGpioTablePreMemJsl;
    break;

    case BoardIdJslLp4xErb:
       PcdSet32S (PcdBoardGpioTableWwanOnEarlyPreMem, (UINTN) mGpioTableJslWwanOnEarlyPreMem);
       PcdSet16S (PcdBoardGpioTableWwanOnEarlyPreMemSize, sizeof (mGpioTableJslWwanOnEarlyPreMem) / sizeof (GPIO_INIT_CONFIG));
       PcdSet32S (PcdBoardGpioTableWwanOffEarlyPreMem, (UINTN) mGpioTableJslWwanOffEarlyPreMem);
       PcdSet16S (PcdBoardGpioTableWwanOffEarlyPreMemSize, sizeof (mGpioTableJslWwanOffEarlyPreMem) / sizeof (GPIO_INIT_CONFIG));
       GpioTable = mGpioTablePreMemJsl;
    break;

    case BoardIdEhlLp4xType3Crb:
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    default:
      if (IsSimicsEnvironment ()) {
        DEBUG ((DEBUG_INFO, "Simics Environment : GpioTablePreMemEhlDdr4Simics Update\n"));
        GpioTable = mGpioTablePreMemEhlSimics;
      } else {
        PcdSet32S (PcdBoardGpioTableWwanOnEarlyPreMem, (UINTN) mGpioTableEhlWwanOnEarlyPreMem);
        PcdSet16S (PcdBoardGpioTableWwanOnEarlyPreMemSize, sizeof (mGpioTableEhlWwanOnEarlyPreMem) / sizeof (GPIO_INIT_CONFIG));
        PcdSet32S (PcdBoardGpioTableWwanOffEarlyPreMem, (UINTN) mGpioTableEhlWwanOffEarlyPreMem);
        PcdSet16S (PcdBoardGpioTableWwanOffEarlyPreMemSize, sizeof (mGpioTableEhlWwanOffEarlyPreMem) / sizeof (GPIO_INIT_CONFIG));
        GpioTable = mGpioTablePreMemEhl;
      }
      break;
  }

  if (GpioTable != NULL) {
    GetGpioTableSize (GpioTable, &GpioCount);
    //
    // Increase GpioCount for the zero terminator.
    //
    GpioCount ++;
    Size = (UINTN) (GpioCount * sizeof (GPIO_INIT_CONFIG));
    Status = PcdSetPtrS (PcdBoardGpioTablePreMem, &Size, GpioTable);
    ASSERT_EFI_ERROR (Status);
  } else {
    DEBUG ((DEBUG_ERROR, "Can not find proper BoardId result in GpioTable = NULL, Assert!\n"));
    ASSERT(FALSE);
  }

  return Status;
}
