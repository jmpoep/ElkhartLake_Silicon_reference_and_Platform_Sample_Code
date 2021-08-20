/** @file
  The implementition of Tbt library shared between dTBT and iTBT.

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

#include <Register/HostDmaRegs.h>
#include <Register/ItbtPcieRegs.h>
#include <Library/DebugLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/TbtCommonLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseLib.h>

/**
  Internal function to Wait for Tbt2PcieDone Bit.to Set or clear
  @param[in]  CommandOffsetAddress      Tbt2Pcie Register Address
  @param[in]  TimeOut                   The number of 100 ms units to delay
  @param[in]  Tbt2PcieDone              Wait condition (wait for Bit to Clear/Set)
  @param[out] *Tbt2PcieValue Function   Register value
  @retval     TRUE                      If command executes succesfully
**/
BOOLEAN
InternalWaitforCommandCompletion(
  IN  UINT64                            CommandOffsetAddress,
  IN  UINT32                            TimeOut,
  IN  BOOLEAN                           Tbt2PcieDone,
  OUT UINT32                            *Tbt2PcieValue
  )
{
  BOOLEAN                               ReturnFlag;
  UINT32                                Tbt2PcieCheck;

  DEBUG ((DEBUG_INFO, "[TBT] Waiting for TBT controller to finish command\n"));
  ReturnFlag = FALSE;
  while (TimeOut-- > 0) {
    *Tbt2PcieValue = PciSegmentRead32 (CommandOffsetAddress);

    if (0xFFFFFFFF == *Tbt2PcieValue ) {
      //
      // Device is not here return now
      //
      ReturnFlag     = FALSE;
      break;
    }

    if(Tbt2PcieDone) {
      Tbt2PcieCheck  =  *Tbt2PcieValue & TBT2PCIE_DON_R;
    } else {
      Tbt2PcieCheck  = !(*Tbt2PcieValue & TBT2PCIE_DON_R);
    }

    if (Tbt2PcieCheck) {
      ReturnFlag     = TRUE;
      break;
    }

    MicroSecondDelay (TBT_MAILBOX_DELAY);
  }

  if ((TimeOut == 0) && (ReturnFlag == FALSE)) {
    DEBUG ((DEBUG_ERROR, "[TBT] Command timeout!\n"));
  }
  return ReturnFlag;
}

/**
  Execute TBT Mailbox Command without data

  1.Load PCIE2TBT register with command and set VALID bit of PCIE2TBT register to indicate a new command sent
  2.Wait for DONE bit set by LC acknowledging the command sent from the host before timeout
  3.Clear PCIE2TBT register valid bit which should be cleared by host SW after command done
  4.Wait for DONE bit cleared by LC if it is iTBT controller

  @param[in]  Command                   TBT Command
  @param[in]  Tbt2PcieOffset            TBT2PCIE Register Offset
  @param[in]  Pcie2TbtOffset            PCIE2TBT Register Offset
  @param[in]  Bus                       Bus number for HIA (ITBT) or Host Router (DTBT)
  @param[in]  Device                    Device number for HIA (ITBT) or Host Router (DTBT)
  @param[in]  Function                  Function number for HIA (ITBT) or Host Router (DTBT)
  @param[in]  Timeout                   Time out with 100 ms garnularity
  @retval     TRUE                      If command executes succesfully
**/
BOOLEAN
TbtSetPcie2TbtCommand(
  IN  UINT8                             Command,
  IN  UINT16                            Tbt2PcieOffset,
  IN  UINT16                            Pcie2TbtOffset,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Function,
  IN  UINT32                            Timeout
)
{
  UINT64                                Pcie2Tbt;
  UINT64                                Tbt2Pcie;
  UINT32                                RegisterValue;
  BOOLEAN                               ReturnFlag;

  Tbt2Pcie = PCI_SEGMENT_LIB_ADDRESS(0, Bus, Device, Function, Tbt2PcieOffset);
  Pcie2Tbt = PCI_SEGMENT_LIB_ADDRESS(0, Bus, Device, Function, Pcie2TbtOffset);

  DEBUG ((DEBUG_INFO, "[TBT] Send command %x to controller \n", Command));

  ///
  /// Load PCIE2TBT register with command and set VALID bit of PCIE2TBT register to indicate a new command sent, generates
  /// interrupt to LC and CM.
  ///
  PciSegmentWrite32 (Pcie2Tbt, Command | PCIE2TBT_VLD_B);

  ///
  /// Wait for DONE bit set by LC acknowledging the command sent from the host before timeout
  ///
  ReturnFlag = InternalWaitforCommandCompletion (Tbt2Pcie, Timeout, TRUE, &RegisterValue);

  ///
  /// Clear PCIE2TBT register valid bit which should be cleared by host SW after command done
  ///
  PciSegmentWrite32(Pcie2Tbt, 0);

  //
  /// Wait for DONE bit cleared by LC if it is iTBT controller
  ///
  if (Tbt2PcieOffset == FixedPcdGet8 (PcdITbtToPcieRegister)) {
    ReturnFlag = InternalWaitforCommandCompletion (Tbt2Pcie, Timeout, FALSE, &RegisterValue);
  }

  return ReturnFlag;
}

/**
  Get Segment, Bus, Device and Function Number for TBT DMA controller by Root Port physical number

  @param[in]  Controller                Controller number. (0-based)
  @param[out] Segment                   Return corresponding Tbt HIA Segment number.
  @param[out] Bus                       Return corresponding Tbt HIA Bus number.
  @param[out] Device                    Return corresponding Tbt HIA device number.
  @param[out] Function                  Return corresponding Tbt HIA function number.

  @retval     EFI_SUCCESS               Root port device and function is retrieved
**/
EFI_STATUS
EFIAPI
GetITbtDmaDevFun(
  IN  UINT8                             Controller,
  OUT UINTN                             *Segment,
  OUT UINTN                             *Bus,
  OUT UINTN                             *Device,
  OUT UINTN                             *Function
)
{
  if (Controller >= (MAX_ITBT_PCIE_PORT / 2)) {
    *Segment  = 0xFF;
    *Bus      = 0xFF;
    *Device   = 0xFF;
    *Function = 0xFF;
    return EFI_NOT_FOUND;
  } else {
    *Segment  = 0;
    *Bus      = SA_HOST_DMA_BUS_NUM;
    *Device   = SA_HOST_DMA_DEV_NUM;
    *Function = SA_HOST_DMA0_FUN_NUM + (UINTN) Controller;
    return EFI_SUCCESS;
  }
}

/**
  VGA Enable and VGA 16-bit decode registers of Bridge control register of Intergrated and Discrete Thunderbolt root port
  should be cleaned

  @param[in]  Segment                   Segment number
  @param[in]  Bus                       Bus number
  @param[in]  Device                    Device number
  @param[in]  Function                  Function number
**/
VOID
TbtClearVgaRegisters(
  IN  UINTN                             Segment,
  IN  UINTN                             Bus,
  IN  UINTN                             Device,
  IN  UINTN                             Function
)
{
  UINT64                                BridngeBaseAddress;
  UINT16                                Data16;

  //
  // Get the TBT Root Port Base Address
  //
  BridngeBaseAddress = PCI_SEGMENT_LIB_ADDRESS (Segment, Bus, (UINT32)Device, (UINT32)Function, 0);
  Data16 = PciSegmentRead16 (BridngeBaseAddress + PCI_BRIDGE_CONTROL_REGISTER_OFFSET);
  Data16 &= (~(EFI_PCI_BRIDGE_CONTROL_VGA | EFI_PCI_BRIDGE_CONTROL_VGA_16));
  PciSegmentWrite16 (BridngeBaseAddress + PCI_BRIDGE_CONTROL_REGISTER_OFFSET, Data16);
}