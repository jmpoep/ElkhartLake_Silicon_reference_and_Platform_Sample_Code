/** @file
  Touch Host Controller Private Lib for Driver usage

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include "ThcPrivate.h"


/**
  Sets TSSGO bit to start a cycle

  @param[in]  MmioBase         Thc MMIO BAR0

**/
VOID
ThcLibGo (
  IN UINT64  MmioBase
  );

/**
  Sets Edge Interrupt mode

  @param[in]  MmioBase         Thc MMIO BAR0

**/
VOID
ThcLibSetEdgeInterrupts (
  IN UINT64  MmioBase
  );

/**
  Returns last received interrupt of THC_INTERRUPT_TYPE

  @param[in]  MmioBase     Thc MMIO BAR0

  @retval                  One of THC_INTERRUPT_TYPE
**/
UINT8
ThcLibInterruptStatus (
  IN UINT64  MmioBase
  );

/**
  Waits for SPI_IO_RDY BIT after it was moved to D0

  @param[in]  MmioBase       Thc MMIO BAR0
  @param[in]  Timeout        [MILLISECONDS] Indicates how long driver waits for device to become ready

  @retval  EFI_SUCCESS       Device is ready
  @retval  EFI_DEVICE_ERROR  Timeout reached - error during initialization
**/
EFI_STATUS
ThcLibIoReady (
  IN UINT64   MmioBase,
  IN UINT32   Timeout
  );

/**
  Start Quiesce to de-initialize THC

  @param[in]  MmioBase      Thc MMIO BAR0
  @param[in]  Timeout       [MILLISECONDS] Indicates how long driver waits for HW Sts bit to be 1

  @retval EFI_SUCCESS       Quiesce Enabled
  @retval EFI_DEVICE_ERROR  Timeout reached - error during initialization
**/
EFI_STATUS
ThcLibStartQuiesce (
  IN UINT64   MmioBase,
  IN UINT32   Timeout
  );

/**
  Ends Quiesce

  @param[in] MmioBase       Thc MMIO BAR0
  @param[in] Timeout        [MILLISECONDS] Indicates how long driver waits for HW STS response

  @retval EFI_SUCCESS       Quiesce Disabled
  @retval EFI_DEVICE_ERROR  Timeout reached - error during initialization
**/
EFI_STATUS
ThcLibEndQuiesce (
  IN UINT64   MmioBase,
  IN UINT32   Timeout
  );

/**
  Check if Quiesce is disabled

  @param[in]  MmioBase  Thc MMIO BAR0

  @retval  TRUE         Quiesce is Disabled
  @retval  FALSE        Quiesce is Enabled
**/
BOOLEAN
ThcLibIsQuiesceDisabled (
  IN UINT64   MmioBase
  );

/**
  Sets Port Frequency

  @param[in] MmioBase    Thc MMIO BAR0
  @param[in] TypeShift   Frequency shift value for read or write
  @param[in] Frequency   Frequency value

**/
VOID
ThcLibSetPortFrequency (
  IN UINT64               MmioBase,
  IN UINT32               TypeShift,
  IN THC_PORT_FREQUENCY   Frequency
  );

/**
  Sets Single IO mode for both read and write

  @param[in] MmioBase          Thc MMIO BAR0

**/
VOID
ThcLibSetSingleIoMode (
  IN UINT64   MmioBase
  );

/**
  Power down device through GPIO

  @param[in] MmioBase          Thc MMIO BAR0

**/
VOID
ThcLibReset (
  IN UINT64   MmioBase
  );

/**
  Power up device through RST GPIO

  @param[in] MmioBase       Thc MMIO BAR0
  @param[in] Timeout       [MILLISECONDS] Indicates how long driver waits for device to power up

**/
VOID
ThcLibGetOutOfReset (
  IN UINT64   MmioBase,
  IN UINT32   Timeout
  );

/**
  Waits for TOUCH_INT_CAUSE to return ResetOccurred

  @param[in]  MmioBase      Thc MMIO BAR0
  @param[in]  Timeout       [MILLISECONDS] Indicates how long driver waits for device to become ready

  @retval EFI_SUCCESS       Reset was successful
  @retval EFI_TIMEOUT       Timeout reached - might be expected
**/
EFI_STATUS
ThcLibWaitForResetOccured (
  IN UINT64   MmioBase,
  IN UINT32   Timeout
  );

/**
  Waits for TOUCH_INT_CAUSE to return ConfigChange

  @param[in]  MmioBase      Thc MMIO BAR0
  @param[in]  Timeout       [MILLISECONDS] Indicates how long driver waits for device to become ready

  @retval EFI_SUCCESS       Reset was successful
  @retval EFI_TIMEOUT       Timeout reached - might be expected
**/
EFI_STATUS
ThcLibWaitForConfigChange (
  IN UINT64   MmioBase,
  IN UINT32   Timeout
  );

/**
  Checks if any cycle is currently being served by THC

  @param[in]  MmioBase Thc MMIO BAR0

  @retval TRUE         Cycle is in progress
  @retval FALSE        No cycles running
**/
BOOLEAN
ThcLibCycleInProgress (
  IN UINT64   MmioBase
  );

/**
  Waits until cycle is completed

  @param[in]  MmioBase         Thc MMIO BAR0
  @param[in]  Timeout          [MILLISECONDS] Indicates how long driver waits for device to become ready

  @retval EFI_SUCCESS          Cycle completed
  @retval EFI_DEVICE_ERROR     TSSDONE not set or ERR set
  @retval EFI_TIMEOUT          Timeout
**/
EFI_STATUS
ThcLibWaitCycleCompleted (
  IN UINT64   MmioBase,
  IN UINT32   Timeout
  );

/**
  Checks if no cycles are pending

  @param[in]  MmioBase          Thc MMIO BAR0
  @param[in]  Timeout          [MILLISECONDS] Indicates how long driver waits for device to become ready

  @retval EFI_SUCCESS          No Cycles running
  @retval EFI_TIMEOUT          Timeout
**/
EFI_STATUS
ThcLibNoCyclesPending (
  IN UINT64   MmioBase,
  IN UINT32   Timeout
  );

/**
  Prepares THC to return its configuration

  @param[in]  MmioBase          Thc MMIO BAR0

**/
VOID
ThcLibPrepareReadDevRegCmd (
  IN UINT64   MmioBase
  );

/**
  Prepares THC to change Touch Panels TOUCH_CONFIG fields

  @param[in]  MmioBase          Thc MMIO BAR0

**/
VOID
ThcLibPrepareWriteConfigCmd (
  IN UINT64   MmioBase
  );

/**
  Reads THC device registers

  @param[in]      MmioBase         Thc MMIO BAR0
  @param[in/out]  DeviceRegisters  Pointer to the device registers

  @retval EFI_SUCCESS              Cycle completed
  @retval EFI_DEVICE_ERROR         Returned Byte Count is too big or empty
**/
EFI_STATUS
ThcLibReadDeviceRegisters (
  IN     UINT64  MmioBase,
  IN OUT UINT32  *DeviceRegisters
  );

/**
  Write to sequencing Data 1

  @param[in]  MmioBase         Thc MMIO BAR0
  @param[in]  Data             Data

**/
VOID
ThcLibWriteSeqData1 (
  IN UINT64  MmioBase,
  IN UINT32  Data
  );

/**
  Sets Prd Tables Adddress in THC MMIO

  @param[in]  MmioBase            Thc MMIO BAR0
  @param[in]  WriteAddr           Write Prd Address
  @param[in]  Read2Addr           Read2 Prd Address

  @retval EFI_SUCCESS             Cycle completed
  @retval EFI_INVALID_PARAMETER   Returned Byte Count is too big or empty
**/
EFI_STATUS
ThcLibSetPrdTablesAddress (
  IN UINT64  MmioBase,
  IN UINT64  WriteAddr,
  IN UINT64  Read2Addr
  );

/**
  Sets PrdTable/CircullarBuffer length

  @param[in]  MmioBase        Thc MMIO BAR0
  @param[in]  ReadEntryCount  Number Of Read Entries
  @param[in]  ReadCBDepth     Read Circullar Buffer Depth
  @param[in]  WriteEntryCount Number of Write Entries

**/
VOID
ThcLibSetLengthInPrd (
  IN UINT64  MmioBase,
  IN UINT8   ReadEntryCount,
  IN UINT8   ReadCBDepth,
  IN UINT8   WriteEntryCount
  );

/**
  Sets Write DMA start bit

  @param[in]  MmioBase           Thc MMIO BAR0

**/
VOID
ThcLibSetWriteStartBit (
  IN UINT64  MmioBase
  );

/**
  Polls until DMA Complete bit is set

  @param[in]  MmioBase       Thc MMIO BAR0
  @param[in]  Timeout        [MILLISECONDS] Indicates how long polling lasts

  @retval  EFI_SUCCESS       DMA transfer is complete
  @retval  EFI_TIMEOUT       Timeout reached
**/
EFI_STATUS
ThcLibPollDmaComplete (
  IN UINT64  MmioBase,
  IN UINT32  Timeout
  );

/**
  Sets Read Rx2 DMA start bit

  @param[in]  MmioBase           Thc MMIO BAR0

**/
VOID
ThcLibSetReadRx2StartBit (
  IN UINT64  MmioBase
  );

/**
  Sets Read Rx2 DMA write pointer

  @param[in]  MmioBase       Thc MMIO BAR0
  @param[in]  WritePointer   PRD CB Write Pointer

**/
VOID
ThcLibSetReadRx2WritePointer (
  IN UINT64  MmioBase,
  IN UINT8   WritePointer
  );

/**
  Sets Read Rx2 DMA write pointer

  @param[in]  MmioBase           Thc MMIO BAR0

  @retval     Contents of Dma Control 2 register
**/
UINT32
ThcLibGetReadRx2Data (
  IN UINT64  MmioBase
  );

/**
  Prepares Touch Panel and THC for OS hand off

  @param[in]  MmioBase           Thc MMIO BAR0

**/
VOID
ThcLibCleanUp (
  IN UINT64  MmioBase
  );

/**
  Read Int Cause Register in PIO mode.

  @param[in]  MmioBase          Thc MMIO BAR0

**/
VOID
ThcLibPioReadIntCause (
  IN UINT64   MmioBase
  );

