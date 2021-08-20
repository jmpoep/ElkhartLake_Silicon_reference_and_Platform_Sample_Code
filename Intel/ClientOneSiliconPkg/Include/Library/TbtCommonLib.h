/**@file
  Header file of TBT common library

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _TBT_COMMON_LIB_H_
#define _TBT_COMMON_LIB_H_

#include <Library/BaseLib.h>
#include <Library/TimerLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci22.h>
#include <TbtMailBoxCmdDefinition.h>

#define DEFAULT_PCI_SEGMENT_NUMBER_ITBT_DMA0   0
#define DEFAULT_PCI_BUS_NUMBER_ITBT_DMA0       0
#define DEFAULT_PCI_DEVICE_NUMBER_ITBT_DMA0    0x0D
#define DEFAULT_PCI_FUNCTION_NUMBER_ITBT_DMA0  0x02

typedef struct _DEV_ID {
  UINT8 Segment;
  UINT8 Bus;
  UINT8 Dev;
  UINT8 Fun;
} DEV_ID;

#ifdef __GNUC__
#pragma GCC diagnostic warning "-Wunused-variable"
#endif

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
);

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
);

/**
  Get Segment, Bus, Device and Function Number for ITBT DMA controller by Root Port physical number

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
);

/**
  VGA Enable and VGA 16-bit decode registers of Bridge control register of Intergrated and Discrete Thunderbolt root port
  should be cleaned

  @param[in]  Segment   Segment number
  @param[in]  Bus       Bus number
  @param[in]  Device    Device number
  @param[in]  Function  Function number
**/
VOID
TbtClearVgaRegisters(
  IN  UINTN                             Segment,
  IN  UINTN                             Bus,
  IN  UINTN                             Device,
  IN  UINTN                             Function
);

#endif
