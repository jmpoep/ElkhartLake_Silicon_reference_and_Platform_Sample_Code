/** @file
  Touch Host Controller Driver API

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

#include "ThcLibPrivate.h"
#include "ThcAbsPtr.h"

#ifdef THC_STANDALONE_DEBUG
#include <Library/PrintLib.h>
#define LINE_BUFFER        51  //To construct a line needs 51 chars.
#define END_OF_LINE_OFFSET 47
/**
  For serial debugger used, it will show the buffer message line by line to serial console.

  @param[in] Message              the address point of buffer message
  @param[in] Length               message length

**/
VOID
ShowBuffer (
  IN  UINT8                       *Message,
  IN  UINT32                      Length
  )
{
  UINT32                          Index;
  UINT32                          Offset;
  CHAR16                          Buffer [LINE_BUFFER];

  Index  = 0;
  Offset = 0;
  ZeroMem (Buffer, sizeof (Buffer));

  while (Length-- > 0) {
    //
    // Get the corresponding offset value from the index of buffer message.
    //
    Offset = ((Index & 0x0F) > 7) ? (((Index & 0x0F) * 3) + 2) : ((Index & 0x0F) * 3);

    //
    // Print "- " at the half of a line increases the readability of debug message.
    //
    if ((Index & 0x0F) == 0x08) {
      UnicodeSPrint (&Buffer [24], 3 * sizeof (CHAR16), L"- ");
    }

    //
    // Collect the data of buffer message.
    //
    UnicodeSPrint (&Buffer[Offset], 4 * sizeof (CHAR16), L"%02x ", Message [Index]);

    //
    // A line contains 16 bytes of buffer message. If a line is complete, it will be shown through DEBUG macro.
    //
    if (Offset == END_OF_LINE_OFFSET) {
      Print ( L"%02x: %s\n", (Index & 0xF0), Buffer);
    }

    Index++;
  }

  //
  // If a line isn't complete, show the remaining data.
  //
  if (Offset != END_OF_LINE_OFFSET) {
    Print (L"%02x: %s\n", (Index & 0xF0), Buffer);
  }
  return;
}
#endif

/**
  Sets Frequency based on Touch Capabilities MAX_SPI_FREQUENCY_SUPPORTED accordingly to EDS

  @param[in]  ThcDev          Context of Thc device

  @retval EFI_SUCCESS         Thc frequency set successfuly
  @retval EFI_DEVICE_ERROR    Error during frequency mapping with EDS
**/
EFI_STATUS
ThcSetFrequency (
  IN THC_DEV                *ThcDev
  )
{
  UINT32 MaxFrequency;
  UINT32 NewFrequency;

  NewFrequency = ThcFreqInvalid;
  MaxFrequency = ThcDev->DeviceRegisters.TouchCapabilities.Fields.MaxSpiFrequencySupported;

  //
  // Map Frequency to match THC and EDS
  //
  if (MaxFrequency == ThcEdsFreq7p812MHz) {
    NewFrequency = ThcFreqLow7p5MHz;
  } else if (MaxFrequency == ThcEdsFreq15p62MHz) {
    NewFrequency = ThcFreqLow15MHz;
  } else if (MaxFrequency == ThcEdsFreq17p86MHz) {
    NewFrequency = ThcFreqHigh17MHz;
  } else if (MaxFrequency == ThcEdsFreq20p83MHz) {
    NewFrequency = ThcFreqHigh20MHz;
  } else if (MaxFrequency == ThcEdsFreq25MHz) {
    NewFrequency = ThcFreqHigh24MHz;
  } else if (MaxFrequency == ThcEdsFreq31p25MHz) {
    NewFrequency = ThcFreqHigh30MHz;
  }

  if (NewFrequency == ThcFreqInvalid) {
    DEBUG ((DEBUG_ERROR, "ThcSetFrequency error Max Device Frequency does not meet EDS specification:%d\n", MaxFrequency));
    return EFI_DEVICE_ERROR;
  }

  ThcLibSetPortFrequency (ThcDev->PciBar0, N_THC_MEM_PORT_SPI_CONFIG_READ_FREQUENCY, NewFrequency);
  ThcLibSetPortFrequency (ThcDev->PciBar0, N_THC_MEM_PORT_SPI_CONFIG_WRITE_FREQUENCY, NewFrequency);

  return EFI_SUCCESS;
}

/**
  Initialize Thc according to procedure described in EDS

  @param[in]  ThcDev      Context of Thc device

  @retval EFI_SUCCESS     Thc initialized successfully
  @retval other           Error during initialization
**/
EFI_STATUS
ThcInitialize (
  IN THC_DEV                *ThcDev
  )
{
  EFI_STATUS Status;

  THC_LOCAL_DEBUG(L"ThcInitialize Start ()\n")
  Status = ThcLibIoReady (ThcDev->PciBar0, IoReadyTimeout);
  THC_LOCAL_DEBUG(L"ThcInitialize  ThcLibIoReady Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcLibIoReady error, Status %r\n", Status));
    return Status;
  }

  if (ThcLibIsQuiesceDisabled (ThcDev->PciBar0)) {
    THC_LOCAL_DEBUG(L"ThcInitialize  QuiesceDisabled \n")
    Status = ThcLibStartQuiesce (ThcDev->PciBar0, StartQuiesceTimeout);
    THC_LOCAL_DEBUG(L"ThcInitialize  ThcLibStartQuiesce Status: %r\n", Status)
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "ThcLibStartQuiesce error, Status %r\n", Status));
      return Status;
    }
  }

  //
  // Configure THC Controller to operate at 7MHz, Single I/O
  //
  THC_LOCAL_DEBUG(L"ThcInitialize  Configure THC Controller to operate at 7MHz, Single I/O\n")
  ThcLibSetPortFrequency (ThcDev->PciBar0, N_THC_MEM_PORT_SPI_CONFIG_READ_FREQUENCY, ThcFreqLow7p5MHz);
  ThcLibSetPortFrequency (ThcDev->PciBar0, N_THC_MEM_PORT_SPI_CONFIG_WRITE_FREQUENCY, ThcFreqLow7p5MHz);
  ThcLibSetSingleIoMode (ThcDev->PciBar0);

  if (USE_EDGE_INTERRUPTS) {
    ThcLibSetEdgeInterrupts (ThcDev->PciBar0);
  }

  //
  // Reset THC and clear THC_DEVINT_QUIESCE_EN
  //
  ThcLibGetOutOfReset (ThcDev->PciBar0, OutOfResetTimeout);

  Status = ThcLibEndQuiesce (ThcDev->PciBar0, EndQuiesceTimeout);
  THC_LOCAL_DEBUG(L"ThcInitialize  ThcLibEndQuiesce Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcLibEndQuiesce error, Status %r\n", Status));
    return Status;
  }

  Status = ThcLibWaitForResetOccured (ThcDev->PciBar0, WaitForResetTimeout);
  THC_LOCAL_DEBUG(L"ThcInitialize  ThcLibWaitForResetOccured Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcLibWaitForResetOccured error, Status %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Reads Touch Panels Device registers (TouchCapabilities, TouchId etc.)

  @param[in]  ThcDev      Context of Thc device

  @retval EFI_SUCCESS     Thc initialized successfully
  @retval other           Error during initialization
**/
EFI_STATUS
ThcReadConfig (
  IN THC_DEV                *ThcDev
  )
{
  EFI_STATUS Status;

  Status = ThcLibNoCyclesPending (ThcDev->PciBar0, CycleTimeout);
  THC_LOCAL_DEBUG(L"ThcReadConfig  ThcLibNoCyclesPending Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcReadConfig error, Status %r\n", Status));
    return Status;
  }

  ThcLibPrepareReadDevRegCmd (ThcDev->PciBar0);
  ThcLibGo (ThcDev->PciBar0);

  Status = ThcLibWaitCycleCompleted (ThcDev->PciBar0, CycleTimeout);
  THC_LOCAL_DEBUG(L"ThcReadConfig  ThcLibWaitCycleCompleted Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcReadConfig error, Status %r\n", Status));
    return Status;
  }

  Status = ThcLibReadDeviceRegisters (ThcDev->PciBar0, (UINT32*) &ThcDev->DeviceRegisters);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcLibReadDeviceRegisters error, Status %r\n", Status));
  }

  return Status;
}

/**
  Prints end Device Configuration

  @param[in]  ThcDev      Context of Thc device

  @retval EFI_SUCCESS     Thc initialized successfully
  @retval other           Error during initialization
**/
VOID
ThcPrintConfig (
  IN  THC_DEV                *ThcDev
  )
{
  THC_LOCAL_DEBUG(L"ThcPrintConfig () Start\n")
  THC_LOCAL_DEBUG(L"| 0x00 | TouchIntCause        | 0x%X\n", ThcDev->DeviceRegisters.TouchIntCause)
  THC_LOCAL_DEBUG(L"| 0x04 | TouchErr             | 0x%X\n", ThcDev->DeviceRegisters.TouchErr)
  THC_LOCAL_DEBUG(L"| 0x08 | TouchDataSize        | 0x%X\n", ThcDev->DeviceRegisters.TouchDataSize.Data)
  THC_LOCAL_DEBUG(L"| 0x08 | - MAXIMUM_READ_SIZE  | %d\n",   ThcDev->DeviceRegisters.TouchDataSize.Fields.MaximumReadSize)
  THC_LOCAL_DEBUG(L"| 0x08 | - MAXIMUM_WRITE_SIZE | %d\n",   ThcDev->DeviceRegisters.TouchDataSize.Fields.MaximumWriteSize)
  THC_LOCAL_DEBUG(L"| 0x0C | TouchCfg             | 0x%X\n", ThcDev->DeviceRegisters.TouchCfg.Data)
  THC_LOCAL_DEBUG(L"| 0x0C | - TOUCH_ENABLE       | %d\n",   ThcDev->DeviceRegisters.TouchCfg.Fields.TouchEnable)
  THC_LOCAL_DEBUG(L"| 0x0C | - PROP_DATA_ENABLED  | %d\n",   ThcDev->DeviceRegisters.TouchCfg.Fields.ProprietaryDataModeEnabled)
  THC_LOCAL_DEBUG(L"| 0x0C | - HID_REPORT_ENABLED | %d\n",   ThcDev->DeviceRegisters.TouchCfg.Fields.HidReportModeEnabled)
  THC_LOCAL_DEBUG(L"| 0x0C | - POWER_STATE        | %d\n",   ThcDev->DeviceRegisters.TouchCfg.Fields.PowerState)
  THC_LOCAL_DEBUG(L"| 0x10 | TouchState           | 0x%X\n", ThcDev->DeviceRegisters.TouchState.Data)
  THC_LOCAL_DEBUG(L"| 0x10 | - TOUCH_ENABLE       | %d\n",   ThcDev->DeviceRegisters.TouchState.Fields.TouchEnable)
  THC_LOCAL_DEBUG(L"| 0x10 | - PROP_DATA_ENABLED  | %d\n",   ThcDev->DeviceRegisters.TouchState.Fields.ProprietaryDataModeEnabled)
  THC_LOCAL_DEBUG(L"| 0x10 | - HID_REPORT_ENABLED | %d\n",   ThcDev->DeviceRegisters.TouchState.Fields.HidReportModeEnabled)
  THC_LOCAL_DEBUG(L"| 0x10 | - POWER_STATE        | %d\n",   ThcDev->DeviceRegisters.TouchState.Fields.PowerState)
  THC_LOCAL_DEBUG(L"| 0x14 | TouchId              | 0x%X\n", ThcDev->DeviceRegisters.TouchId)
  THC_LOCAL_DEBUG(L"| 0x18 | TouchCapabilities    | 0x%X\n", ThcDev->DeviceRegisters.TouchCapabilities.Data)
  THC_LOCAL_DEBUG(L"| 0x18 | - PROPR_DATA_SUPPORT   | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.ProprietaryDataModeSupported)
  THC_LOCAL_DEBUG(L"| 0x18 | - MAX_SPI_FREQ_SUPPORT | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.MaxSpiFrequencySupported)
  THC_LOCAL_DEBUG(L"| 0x18 | - SINGLE_IO_SUPPORTED  | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.SingleIoSupported)
  THC_LOCAL_DEBUG(L"| 0x18 | - DUAL_IO_SUPPORTED    | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.DualIoSupported)
  THC_LOCAL_DEBUG(L"| 0x18 | - QUAD_IO_SUPPORTED    | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.QuadIoSupported)
  THC_LOCAL_DEBUG(L"| 0x18 | - MAXIMUM_TOUCH_POINTS | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.MaximumTouchPoints)
  THC_LOCAL_DEBUG(L"| 0x18 | - MINIMUM_RESET_TIME   | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.MaximumResetTime)
  THC_LOCAL_DEBUG(L"| 0x18 | - HEARTBEAT_REPORT_SUP | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.HeartBeatReportSupported)
  THC_LOCAL_DEBUG(L"| 0x18 | - PERFORMANCE_LIMIT    | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.PerformanceLimitation)
  THC_LOCAL_DEBUG(L"| 0x18 | - PREP_FOR_REGSTR_READ | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.PrepForRegisterRead)
  THC_LOCAL_DEBUG(L"| 0x1C | TouchIcHwId          | 0x%X\n", ThcDev->DeviceRegisters.TouchIcHwId)
  THC_LOCAL_DEBUG(L"| 0x20 | TouchIcHwRev         | 0x%X\n", ThcDev->DeviceRegisters.TouchIcHwRev)
  THC_LOCAL_DEBUG(L"| 0x24 | TouchIcFwRev         | 0x%X\n", ThcDev->DeviceRegisters.TouchIcFwRev)
  THC_LOCAL_DEBUG(L"| 0x28 | TouchCommand         | 0x%X\n", ThcDev->DeviceRegisters.TouchCommand)
  THC_LOCAL_DEBUG(L"| 0x30 | TouchInit            | 0x%X\n", ThcDev->DeviceRegisters.TouchInit)
  THC_LOCAL_DEBUG(L"| 0x34 | TouchCompatibilityId | 0x%X\n", ThcDev->DeviceRegisters.TouchCompatibilityId.Data)
  THC_LOCAL_DEBUG(L"| 0x34 | - EDS_MINOR_VERSION  | 0x%X\n", ThcDev->DeviceRegisters.TouchCompatibilityId.Fields.EdsMinorVersion)
  THC_LOCAL_DEBUG(L"| 0x34 | - EDS_MAJOR_VERSION  | 0x%X\n", ThcDev->DeviceRegisters.TouchCompatibilityId.Fields.EdsMajorVersion)
  THC_LOCAL_DEBUG(L"| 0x34 | - INTERFACE_REV_NUM  | 0x%X\n", ThcDev->DeviceRegisters.TouchCompatibilityId.Fields.InterfaceRevisionNumber)
  THC_LOCAL_DEBUG(L"| 0x34 | - EU_KERNEL_VERSION  | 0x%X\n", ThcDev->DeviceRegisters.TouchCompatibilityId.Fields.EuKernelCompatibilityVersion)
  THC_LOCAL_DEBUG(L"ThcPrintConfig () End\n")
  DEBUG ((DEBUG_INFO, "ThcPrintConfig () Start\n"));
  DEBUG ((DEBUG_INFO, "| 0x00 | TouchIntCause        | 0x%X\n", ThcDev->DeviceRegisters.TouchIntCause));
  DEBUG ((DEBUG_INFO, "| 0x04 | TouchErr             | 0x%X\n", ThcDev->DeviceRegisters.TouchErr));
  DEBUG ((DEBUG_INFO, "| 0x08 | TouchDataSize        | 0x%X\n", ThcDev->DeviceRegisters.TouchDataSize.Data));
  DEBUG ((DEBUG_INFO, "| 0x08 | - MAXIMUM_READ_SIZE  | %d\n",   ThcDev->DeviceRegisters.TouchDataSize.Fields.MaximumReadSize));
  DEBUG ((DEBUG_INFO, "| 0x08 | - MAXIMUM_WRITE_SIZE | %d\n",   ThcDev->DeviceRegisters.TouchDataSize.Fields.MaximumWriteSize));
  DEBUG ((DEBUG_INFO, "| 0x0C | TouchCfg             | 0x%X\n", ThcDev->DeviceRegisters.TouchCfg.Data));
  DEBUG ((DEBUG_INFO, "| 0x0C | - TOUCH_ENABLE       | %d\n",   ThcDev->DeviceRegisters.TouchCfg.Fields.TouchEnable));
  DEBUG ((DEBUG_INFO, "| 0x0C | - PROP_DATA_ENABLED  | %d\n",   ThcDev->DeviceRegisters.TouchCfg.Fields.ProprietaryDataModeEnabled));
  DEBUG ((DEBUG_INFO, "| 0x0C | - HID_REPORT_ENABLED | %d\n",   ThcDev->DeviceRegisters.TouchCfg.Fields.HidReportModeEnabled));
  DEBUG ((DEBUG_INFO, "| 0x0C | - POWER_STATE        | %d\n",   ThcDev->DeviceRegisters.TouchCfg.Fields.PowerState));
  DEBUG ((DEBUG_INFO, "| 0x10 | TouchState           | 0x%X\n", ThcDev->DeviceRegisters.TouchState.Data));
  DEBUG ((DEBUG_INFO, "| 0x10 | - TOUCH_ENABLE       | %d\n",   ThcDev->DeviceRegisters.TouchState.Fields.TouchEnable));
  DEBUG ((DEBUG_INFO, "| 0x10 | - PROP_DATA_ENABLED  | %d\n",   ThcDev->DeviceRegisters.TouchState.Fields.ProprietaryDataModeEnabled));
  DEBUG ((DEBUG_INFO, "| 0x10 | - HID_REPORT_ENABLED | %d\n",   ThcDev->DeviceRegisters.TouchState.Fields.HidReportModeEnabled));
  DEBUG ((DEBUG_INFO, "| 0x10 | - POWER_STATE        | %d\n",   ThcDev->DeviceRegisters.TouchState.Fields.PowerState));
  DEBUG ((DEBUG_INFO, "| 0x14 | TouchId              | 0x%X\n", ThcDev->DeviceRegisters.TouchId));
  DEBUG ((DEBUG_INFO, "| 0x18 | TouchCapabilities    | 0x%X\n", ThcDev->DeviceRegisters.TouchCapabilities.Data));
  DEBUG ((DEBUG_INFO, "| 0x18 | - PROPR_DATA_SUPPORT   | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.ProprietaryDataModeSupported));
  DEBUG ((DEBUG_INFO, "| 0x18 | - MAX_SPI_FREQ_SUPPORT | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.MaxSpiFrequencySupported));
  DEBUG ((DEBUG_INFO, "| 0x18 | - SINGLE_IO_SUPPORTED  | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.SingleIoSupported));
  DEBUG ((DEBUG_INFO, "| 0x18 | - DUAL_IO_SUPPORTED    | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.DualIoSupported));
  DEBUG ((DEBUG_INFO, "| 0x18 | - QUAD_IO_SUPPORTED    | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.QuadIoSupported));
  DEBUG ((DEBUG_INFO, "| 0x18 | - MAXIMUM_TOUCH_POINTS | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.MaximumTouchPoints));
  DEBUG ((DEBUG_INFO, "| 0x18 | - MINIMUM_RESET_TIME   | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.MaximumResetTime));
  DEBUG ((DEBUG_INFO, "| 0x18 | - HEARTBEAT_REPORT_SUP | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.HeartBeatReportSupported));
  DEBUG ((DEBUG_INFO, "| 0x18 | - PERFORMANCE_LIMIT    | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.PerformanceLimitation));
  DEBUG ((DEBUG_INFO, "| 0x18 | - PREP_FOR_REGSTR_READ | %d\n", ThcDev->DeviceRegisters.TouchCapabilities.Fields.PrepForRegisterRead));
  DEBUG ((DEBUG_INFO, "| 0x1C | TouchIcHwId          | 0x%X\n", ThcDev->DeviceRegisters.TouchIcHwId));
  DEBUG ((DEBUG_INFO, "| 0x20 | TouchIcHwRev         | 0x%X\n", ThcDev->DeviceRegisters.TouchIcHwRev));
  DEBUG ((DEBUG_INFO, "| 0x24 | TouchIcFwRev         | 0x%X\n", ThcDev->DeviceRegisters.TouchIcFwRev));
  DEBUG ((DEBUG_INFO, "| 0x28 | TouchCommand         | 0x%X\n", ThcDev->DeviceRegisters.TouchCommand));
  DEBUG ((DEBUG_INFO, "| 0x30 | TouchInit            | 0x%X\n", ThcDev->DeviceRegisters.TouchInit));
  DEBUG ((DEBUG_INFO, "| 0x34 | TouchCompatibilityId | 0x%X\n", ThcDev->DeviceRegisters.TouchCompatibilityId.Data));
  DEBUG ((DEBUG_INFO, "| 0x34 | - EDS_MINOR_VERSION  | 0x%X\n", ThcDev->DeviceRegisters.TouchCompatibilityId.Fields.EdsMinorVersion));
  DEBUG ((DEBUG_INFO, "| 0x34 | - EDS_MAJOR_VERSION  | 0x%X\n", ThcDev->DeviceRegisters.TouchCompatibilityId.Fields.EdsMajorVersion));
  DEBUG ((DEBUG_INFO, "| 0x34 | - INTERFACE_REV_NUM  | 0x%X\n", ThcDev->DeviceRegisters.TouchCompatibilityId.Fields.InterfaceRevisionNumber));
  DEBUG ((DEBUG_INFO, "| 0x34 | - EU_KERNEL_VERSION  | 0x%X\n", ThcDev->DeviceRegisters.TouchCompatibilityId.Fields.EuKernelCompatibilityVersion));
  DEBUG ((DEBUG_INFO, "ThcPrintConfig () End\n"));
}

/**
  Enables Touch Panel connected to the Touch Host Controller

  @param[in]  ThcDev             Context of Thc device

  @retval EFI_SUCCESS            Touch Panel Enabled
  @retval other                  Error during device enabling process
**/
EFI_STATUS
ThcEnableEndDevice (
  IN  THC_DEV              *ThcDev
  )
{
  EFI_STATUS Status;

  THC_LOCAL_DEBUG(L"ThcEnableEndDevice Start ()\n");
  ThcSetFrequency (ThcDev);

  Status = ThcLibNoCyclesPending (ThcDev->PciBar0, CycleTimeout);
  THC_LOCAL_DEBUG(L"ThcEnableEndDevice  ThcLibNoCyclesPending Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcEnableEndDevice error, Status %r\n", Status));
    return Status;
  }

  ThcLibPrepareWriteConfigCmd (ThcDev->PciBar0);
  ThcDev->DeviceRegisters.TouchCfg.Fields.PowerState = 0x3;
  ThcDev->DeviceRegisters.TouchCfg.Fields.ProprietaryDataModeEnabled = 0x0;
  ThcDev->DeviceRegisters.TouchCfg.Fields.HidReportModeEnabled = 0x1;
  ThcLibWriteSeqData1 (ThcDev->PciBar0, ThcDev->DeviceRegisters.TouchCfg.Data);
  ThcLibGo (ThcDev->PciBar0);

  Status = ThcLibWaitCycleCompleted (ThcDev->PciBar0, CycleTimeout);
  THC_LOCAL_DEBUG(L"ThcEnableEndDevice  ThcLibWaitCycleCompleted Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcEnableEndDevice error, Status %r\n", Status));
    return Status;
  }

  ThcLibPrepareWriteConfigCmd (ThcDev->PciBar0);
  ThcDev->DeviceRegisters.TouchCfg.Fields.TouchEnable = 0x1;
  ThcLibWriteSeqData1 (ThcDev->PciBar0, ThcDev->DeviceRegisters.TouchCfg.Data);
  ThcLibGo (ThcDev->PciBar0);

  Status = ThcLibWaitCycleCompleted (ThcDev->PciBar0, CycleTimeout);
  THC_LOCAL_DEBUG(L"ThcEnableEndDevice  ThcLibWaitCycleCompleted Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcEnableEndDevice error, Status %r\n", Status));
    return Status;
  }

//  Status = ThcLibWaitForConfigChange (3000 ,ThcDev->PciBar0);
//  THC_LOCAL_DEBUG(L"ThcEnableEndDevice  ThcLibWaitForConfigChange Status: %r\n", Status);
//  if (EFI_ERROR (Status)) {
//    DEBUG ((DEBUG_ERROR, "ThcEnableEndDevice error, Status %r\n", Status));
//  }

  return Status;
}

/**
  Disables Touch Panel connected to the Touch Host Controller

  @param[in]  ThcDev             Context of Thc device

  @retval EFI_SUCCESS            Touch Panel Disabled
  @retval other                  Error during device enabling process
**/
EFI_STATUS
ThcDisableEndDevice (
  IN THC_DEV                *ThcDev
  )
{
  EFI_STATUS Status;

  THC_LOCAL_DEBUG(L"ThcDisableEndDevice Start ()\n")
  ThcSetFrequency (ThcDev);

  Status = ThcLibNoCyclesPending (ThcDev->PciBar0, CycleTimeout);
  THC_LOCAL_DEBUG(L"ThcDisableEndDevice  ThcLibNoCyclesPending Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcDisableEndDevice error, Status %r\n", Status));
    return Status;
  }

  ThcLibPrepareWriteConfigCmd (ThcDev->PciBar0);
  ThcDev->DeviceRegisters.TouchCfg.Fields.PowerState = 0x0;
  ThcDev->DeviceRegisters.TouchCfg.Fields.ProprietaryDataModeEnabled = 0x0;
  ThcDev->DeviceRegisters.TouchCfg.Fields.HidReportModeEnabled = 0x1;
  ThcLibWriteSeqData1 (ThcDev->PciBar0, ThcDev->DeviceRegisters.TouchCfg.Data);
  ThcLibGo (ThcDev->PciBar0);

  Status = ThcLibWaitCycleCompleted (ThcDev->PciBar0, CycleTimeout);
  THC_LOCAL_DEBUG(L"ThcDisableEndDevice  ThcLibWaitCycleCompleted Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcDisableEndDevice error, Status %r\n", Status));
    return Status;
  }

  ThcLibPrepareWriteConfigCmd (ThcDev->PciBar0);
  ThcDev->DeviceRegisters.TouchCfg.Fields.TouchEnable = 0x0;
  ThcLibWriteSeqData1 (ThcDev->PciBar0, ThcDev->DeviceRegisters.TouchCfg.Data);
  ThcLibGo (ThcDev->PciBar0);

  Status = ThcLibWaitCycleCompleted (ThcDev->PciBar0, CycleTimeout);
  THC_LOCAL_DEBUG(L"ThcDisableEndDevice  ThcLibWaitCycleCompleted Status: %r\n", Status)
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcDisableEndDevice error, Status %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Initialize Memory for Prd used by the HW
  Only ReadRx2 and Write are supported by this driver

  @param[in]  ThcDev             Context of Thc device

  @retval EFI_SUCCESS            Thc Dma Initialized successfuly
  @retval EFI_OUT_OF_RESOURCES   Not enough memory available
**/
EFI_STATUS
ThcDmaCreatePrdCommonBuffers (
  IN  THC_DEV                *ThcDev
  )
{
  EFI_PCI_IO_PROTOCOL           *PciIo;
  UINT64                        PageCount;
  UINT64                        ByteCount;
  EFI_STATUS                    Status;

  PciIo = ThcDev->PciIo;

  PageCount = EFI_SIZE_TO_PAGES (sizeof (PRD_TABLE) * PRD_READ_TABLES_SUPPORTED);
  Status = PciIo->AllocateBuffer (
                    PciIo,
                    AllocateAnyPages,
                    EfiBootServicesData,
                    PageCount,
                    (VOID*) &ThcDev->DmaRead2.CommonPrdBuffer,
                    0
                    );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcDmaCreateCommonBuffers Read2 buffer allocateBuffer failed Status %r\n", Status));
    return EFI_OUT_OF_RESOURCES;
  }

  ByteCount = EFI_PAGES_TO_SIZE (PageCount);
  Status    = PciIo->Map (
                       PciIo,
                       EfiPciIoOperationBusMasterRead,
                       (VOID*) ThcDev->DmaRead2.CommonPrdBuffer,
                       &ByteCount,
                       &ThcDev->DmaRead2.CommonPrdBufferDevAddr,
                       &ThcDev->DmaRead2.CommonPrdBufferMapping
                       );
  if (EFI_ERROR (Status) || (ByteCount != EFI_PAGES_TO_SIZE (PageCount))) {
    DEBUG ((DEBUG_ERROR, "ThcDmaCreateCommonBuffers Read2 buffer map failed Status %r\n", Status));
    DEBUG ((DEBUG_ERROR, "ThcDmaCreateCommonBuffers Requsted ByteCount: %d Mapped Count: %d\n", EFI_PAGES_TO_SIZE (PageCount), ByteCount));
    return EFI_OUT_OF_RESOURCES;
  }

  ZeroMem ((UINT8*) ThcDev->DmaRead2.CommonPrdBuffer, ByteCount);

  PageCount = EFI_SIZE_TO_PAGES (sizeof (PRD_TABLE) * PRD_WRITE_TABLES_SUPPORTED);
  Status = PciIo->AllocateBuffer (
                    PciIo,
                    AllocateAnyPages,
                    EfiBootServicesData,
                    PageCount,
                    (VOID*) &ThcDev->DmaWrite.CommonPrdBuffer,
                    0
                    );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcDmaCreateCommonBuffers Read2 buffer allocateBuffer failed Status %r\n", Status));
    return EFI_OUT_OF_RESOURCES;
  }

  ByteCount = EFI_PAGES_TO_SIZE (PageCount);
  Status    = PciIo->Map (
                       PciIo,
                       EfiPciIoOperationBusMasterRead,
                       (VOID*) ThcDev->DmaWrite.CommonPrdBuffer,
                       &ByteCount,
                       &ThcDev->DmaWrite.CommonPrdBufferDevAddr,
                       &ThcDev->DmaWrite.CommonPrdBufferMapping
                       );
  if (EFI_ERROR (Status) || (ByteCount != EFI_PAGES_TO_SIZE (PageCount))) {
    DEBUG ((DEBUG_ERROR, "ThcDmaCreateCommonBuffers Write buffer map failed Status %r\n", Status));
    DEBUG ((DEBUG_ERROR, "ThcDmaCreateCommonBuffers Requsted ByteCount: %d Mapped Count: %d\n", EFI_PAGES_TO_SIZE (PageCount), ByteCount));
    return EFI_OUT_OF_RESOURCES;
  }

  ZeroMem ((UINT8*) ThcDev->DmaWrite.CommonPrdBuffer, ByteCount);

  return Status;
}

/**
  Fills single Prd Table with the defualt values

  @param[in]  ThcDma           Dma that stores Driver PRD table
  @param[in]  PrdTableIndex    Index of current Prd table

**/
VOID
ThcDmaFillSinglePrdTable (
  IN THC_DMA                    *ThcDma,
  IN UINT16                     PrdTableIndex
  )
{
  PRD_TABLE                     *PrdTable;
  UINT16                        CurrentEntry = 0;
  UINT32                        EntryOffset  = ThcDma->DriverPrdTable[PrdTableIndex].NumOfConfiguredEntries * PrdTableIndex;

  PrdTable =  (PRD_TABLE*) ThcDma->CommonPrdBuffer;

  for (CurrentEntry = 0; CurrentEntry < ThcDma->DriverPrdTable[PrdTableIndex].NumOfConfiguredEntries; CurrentEntry++) {
    CopyMem (
      &PrdTable->Entries[CurrentEntry + EntryOffset],
      &ThcDma->DriverPrdTable[PrdTableIndex].Entries[CurrentEntry],
      sizeof (PRD_ENTRY)
      );
  }
}

/**
  Fills every Prd Table with the defualt values

  @param[in]  ThcDma           Dma that stores Driver PRD Table

**/
VOID
ThcDmaFillPrdTables (
  THC_DMA                        *ThcDma
  )
{
  UINT16                        PrdTableIndex;

  THC_LOCAL_DEBUG(L"ThcDmaFillPrdTables Start ()\n")

  //
  // Loop through total number of Entries in Common Prd
  // Fill every entry with the corresponding data for the HW to use
  //
  for (PrdTableIndex = 0; PrdTableIndex < ThcDma->NumOfPrdTables; PrdTableIndex++) {
    ThcDmaFillSinglePrdTable (ThcDma, PrdTableIndex);
  }
}

/**
  Initialize Driver Prd Tables
  Allocates and maps every single page for each used entry
  besed on the supported BufferSize for each MAXIMUM_READ_SIZE/MAXIMUM_WRITE_SIZE

  @param[in]  ThcDev           Context of Thc device
  @param[in]  ThcDma           Dma that stores Driver PRD Table
  @param[in]  PciIoOperation   BusMasterRead or BusMasterWrite

  @retval EFI_SUCCESS            Thc Dma Initialized successfuly
  @retval EFI_OUT_OF_RESOURCES   Not enough memory available
**/
EFI_STATUS
ThcDmaCreatePrds (
  IN THC_DEV                        *ThcDev,
  IN THC_DMA                        *ThcDma,
  IN EFI_PCI_IO_PROTOCOL_OPERATION  PciIoOperation
  )
{
  EFI_STATUS                    Status;
  EFI_PCI_IO_PROTOCOL           *PciIo;
  UINTN                         PageCount;
  UINTN                         ByteCount;
  UINT16                        CurrentEntry;
  UINT64                        CurrentAddress;
  UINT16                        PrdTableIndex;
  UINTN                         BytesRemaining;

  THC_LOCAL_DEBUG(L"ThcDmaCreatePrds Start ()\n")

  PciIo = ThcDev->PciIo;

  for (PrdTableIndex = 0; PrdTableIndex < ThcDma->NumOfPrdTables; PrdTableIndex++) {

    PageCount = EFI_SIZE_TO_PAGES (ThcDma->BufferSize);
    Status    = PciIo->AllocateBuffer (
                         PciIo,
                         AllocateAnyPages,
                         EfiBootServicesData,
                         PageCount,
                         (VOID*) &ThcDma->DriverPrdTable[PrdTableIndex].Buffer,
                         0
                         );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "ThcDmaCreateReadPrds AllocateBuffer for PrdTableIndex: %d failed with Status\n", PrdTableIndex, Status));
      return EFI_OUT_OF_RESOURCES;
    }

    ByteCount = EFI_PAGES_TO_SIZE (PageCount);
    Status    = PciIo->Map (
                         PciIo,
                         PciIoOperation,
                         (VOID*) ThcDma->DriverPrdTable[PrdTableIndex].Buffer,
                         &ByteCount,
                         &ThcDma->DriverPrdTable[PrdTableIndex].DevAddr,
                         &ThcDma->DriverPrdTable[PrdTableIndex].Mapping
                         );

    if (EFI_ERROR (Status) || (ByteCount != EFI_PAGES_TO_SIZE (PageCount))) {
      DEBUG ((DEBUG_ERROR, "ThcDmaCreateReadPrds Read buffer map failed PrdTableIndex: %d Status %r\n", PrdTableIndex, Status));
      DEBUG ((DEBUG_ERROR, "ThcDmaCreateReadPrds Requsted ByteCount: %d Mapped Count: %d\n", EFI_PAGES_TO_SIZE (PageCount), ByteCount));
      return EFI_OUT_OF_RESOURCES;
    }

    ZeroMem ((UINT8*) ThcDma->DriverPrdTable[PrdTableIndex].Buffer, ByteCount);

    BytesRemaining   = ByteCount;
    CurrentEntry     = 0;
    CurrentAddress   = ThcDma->DriverPrdTable[PrdTableIndex].Buffer;
    //
    // Loop through total number of Entries
    // Each entry Max length is 4K (size of the single page), max entries is 256.
    // Max allocated total for single PRD table is 1MB
    //
    while (BytesRemaining > 0 && CurrentEntry < 256) {
      ThcDma->DriverPrdTable[PrdTableIndex].Entries[CurrentEntry].DestinationAddress = RShiftU64 (CurrentAddress, ADDRESS_SHIFT);
      ThcDma->DriverPrdTable[PrdTableIndex].Entries[CurrentEntry].EndOfPrd           = 0x0;
      ThcDma->DriverPrdTable[PrdTableIndex].Entries[CurrentEntry].Length             = EFI_PAGE_SIZE;
      if (BytesRemaining <= EFI_PAGE_SIZE) {
        ThcDma->DriverPrdTable[PrdTableIndex].Entries[CurrentEntry].Length           = BytesRemaining;
        ThcDma->DriverPrdTable[PrdTableIndex].Entries[CurrentEntry].EndOfPrd         = 0x1;
        break;
      }
      CurrentEntry++;
      CurrentAddress += EFI_PAGE_SIZE;
      BytesRemaining -= EFI_PAGE_SIZE;
    }
    ThcDma->DriverPrdTable[PrdTableIndex].NumOfConfiguredEntries = CurrentEntry + 1;
  }

  return EFI_SUCCESS;
}

/**
  Initialize Thc DMA

  @param[in]  ThcDev      Context of Thc device

  @retval EFI_SUCCESS     Thc Dma Initialized successfuly
  @retval other           error during initialization
**/
EFI_STATUS
ThcDmaInitialize (
  IN THC_DEV                *ThcDev
  )
{
  EFI_STATUS Status;

  THC_LOCAL_DEBUG(L"ThcDmaInitialize Start ()\n")

  Status = ThcDmaCreatePrdCommonBuffers (ThcDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcDmaInitialize error, failed to CreatePrdCommonBuffers Status %r\n", Status));
    return Status;
  }

  Status = ThcLibSetPrdTablesAddress (ThcDev->PciBar0, ThcDev->DmaWrite.CommonPrdBuffer, ThcDev->DmaRead2.CommonPrdBuffer);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcDmaInitialize error, failed to SetPrdTablesAddress Status %r\n", Status));
    return Status;
  }

  ThcDev->DmaRead2.BufferSize     = (ThcDev->DeviceRegisters.TouchDataSize.Fields.MaximumReadSize + 1) * SIZE_FIELD_RESOLUTION;
  ThcDev->DmaRead2.NumOfPrdTables = PRD_READ_TABLES_SUPPORTED;
  ThcDev->DmaWrite.BufferSize     = (ThcDev->DeviceRegisters.TouchDataSize.Fields.MaximumWriteSize + 1) * SIZE_FIELD_RESOLUTION;
  ThcDev->DmaWrite.NumOfPrdTables = PRD_WRITE_TABLES_SUPPORTED;

  Status = ThcDmaCreatePrds (ThcDev, &ThcDev->DmaRead2, EfiPciIoOperationBusMasterRead);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcDmaInitialize error, failed to Create Read Prds Status %r\n", Status));
    return Status;
  }

  ThcDmaFillPrdTables (&ThcDev->DmaRead2);

  Status = ThcDmaCreatePrds (ThcDev, &ThcDev->DmaWrite, EfiPciIoOperationBusMasterWrite);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcDmaInitialize error, failed to Create Write Prds Status %r\n", Status));
    return Status;
  }

  ThcDmaFillPrdTables (&ThcDev->DmaWrite);

  ThcLibSetLengthInPrd  (ThcDev->PciBar0,
                         (UINT8) ThcDev->DmaRead2.DriverPrdTable[0].NumOfConfiguredEntries,
                         PRD_READ_TABLES_SUPPORTED,
                         (UINT8) ThcDev->DmaWrite.DriverPrdTable[0].NumOfConfiguredEntries
                        );

  ThcLibSetReadRx2StartBit (ThcDev->PciBar0);

  return EFI_SUCCESS;
}

/**
  Calculates the length of the current message

  @param[in]  ThcDma             Dma that stores Driver PRD Table
  @param[in]  PrdTable           Prd Table updated by the THC HW
  @param[in]  PrdTableIndex      Index of the Prd Table
  @param[in]  EntryOffset        Entry offset

  @retval MessageLength          Size of the message
**/
UINT64
ThcDmaGetMessageLength (
  IN THC_DMA                        *ThcDma,
  IN PRD_TABLE                      *PrdTable,
  IN UINT16                         PrdTableIndex,
  IN UINT32                         EntryOffset
  )
{
  UINT32  Index;
  UINT64  MessageLength = 0;

  for (Index = 0; Index < ThcDma->DriverPrdTable[PrdTableIndex].NumOfConfiguredEntries; Index++) {
    MessageLength += PrdTable->Entries[EntryOffset + Index].Length;
    if (PrdTable->Entries[EntryOffset + Index].EndOfPrd == 1) {
      return MessageLength;
    }
  }
  return MessageLength;
}

/**
  Reads first PRD Table Entry and checks if header data type
  equals to TouchReadDataTypeHidReport
  and Report Id is equal to SINGLE_FINGER_REPORT_ID.
  If passed report data is copied to the Thc Context.

  @param[in]  ThcDev             Context of Thc device
  @param[in]  ThcDma             Dma that stores Driver PRD Table
  @param[in]  CurrentPrdTable    Index of current Prd table

  @retval EFI_SUCCESS            Data read done
  @retval EFI_BAD_BUFFER_SIZE    MessageLength is smaller then its header
  @retval EFI_BUFFER_TOO_SMALL   Allocated entry length is smaller then one present in Prd
**/
EFI_STATUS
ThcDmaReadSingleReport (
  IN THC_DEV                *ThcDev,
  IN THC_DMA                *ThcDma,
  IN UINT16                 CurrentPrdTable
  )
{
  READ_DATA_BUFF           *ReadDataBuff;
  PRD_TABLE                *PrdTable;
  UINT64                   MessageLength = 0;
  UINT64                   DataAddress   = 0;
  UINT32                   EntryOffset   = 0;
  EntryOffset = (UINT32)(ThcDma->DriverPrdTable[CurrentPrdTable].NumOfConfiguredEntries) * CurrentPrdTable;
  PrdTable    = (PRD_TABLE *) ThcDma->CommonPrdBuffer;


  THC_LOCAL_DEBUG(L"ThcDmaReadbuffer Start ()\n")
  ReadDataBuff = AllocateZeroPool (sizeof (READ_DATA_BUFF));
  if (ReadDataBuff == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  MessageLength = ThcDmaGetMessageLength (ThcDma, PrdTable, CurrentPrdTable, EntryOffset);
  THC_LOCAL_DEBUG(L"MessageLength %d \n", MessageLength)
  if (MessageLength < sizeof (RAW_DATA_HEADER)) {
    FreePool (ReadDataBuff);
    return EFI_BAD_BUFFER_SIZE;
  }
  if (ThcDma->DriverPrdTable[CurrentPrdTable].Entries[0].Length < PrdTable->Entries[EntryOffset].Length) {
    FreePool (ReadDataBuff);
    return EFI_BUFFER_TOO_SMALL;
  }

  DataAddress = LShiftU64 (PrdTable->Entries[EntryOffset].DestinationAddress, ADDRESS_SHIFT);
  CopyMem ((UINT8*) ReadDataBuff, (UINT8*) DataAddress, sizeof (READ_DATA_BUFF));

  THC_LOCAL_DEBUG(L"ReadDataBuff->Header.DataType %d\n", ReadDataBuff->Header.DataType)

  if ((ReadDataBuff->Header.DataType == TouchReadDataTypeHidReport) && (ReadDataBuff->ReadData[0] == SINGLE_FINGER_REPORT_ID)) {
    CopyMem ((UINT8*) &ThcDev->Report, (UINT8*) DataAddress + sizeof (RAW_DATA_HEADER), sizeof (SINGLE_FINGER_REPORT));
    THC_LOCAL_DEBUG(L"X:%d Y:%d Btn: %d \n",
                    (ThcDev->Report.HigherXByte << 8) + ThcDev->Report.LowerXByte,
                    (ThcDev->Report.HigherYByte << 8) + ThcDev->Report.LowerYByte,
                    ThcDev->Report.TouchSts);

    ThcDev->AbsPtrDataAvailable = TRUE;
    gBS->SignalEvent (ThcDev->AbsPtrProtocol.WaitForInput);
  } else if ((ReadDataBuff->Header.DataType == TouchReadDataTypeGetFeatures) &&
             (ThcDev->HidActive == TRUE) &&
             (ThcDev->HidBuffer != NULL)) {
    THC_LOCAL_DEBUG(L"ThcDmaReadbuffer TouchReadDataTypeGetFeatures\n")
    DEBUG ((DEBUG_ERROR, "TouchReadDataTypeGetFeatures\n"));
    CopyMem ((UINT8*) ThcDev->HidBuffer, (UINT8*) DataAddress + sizeof (RAW_DATA_HEADER), MessageLength);
    ThcDev->HidBuffer += MessageLength;
    ThcDev->HidDataAvailable = TRUE;
  } else if ((ReadDataBuff->Header.DataType == TouchReadDataTypeHidReport) &&
             (ThcDev->HidActive == TRUE) &&
             (ThcDev->HidBuffer != NULL)) {
    THC_LOCAL_DEBUG(L"ThcDmaReadSingleReport Warning! Consuming HidReport as Get/Set Feature response\n")
    DEBUG ((DEBUG_WARN, "ThcDmaReadSingleReport Warning! Consuming HidReport as Get/Set Feature response\n"));
    CopyMem ((UINT8*) ThcDev->HidBuffer, (UINT8*) DataAddress + sizeof (RAW_DATA_HEADER), MessageLength);
    ThcDev->HidBuffer += MessageLength;
    ThcDev->HidDataAvailable = TRUE;
  }

  FreePool (ReadDataBuff);

  return EFI_SUCCESS;
}

/**
  Reads data from each Read Rx2 DMA PRD Table Entry until write pointer is equal to read pointer
  Write pointer is updated after each PRD Table read is finished

  @param[in]  ThcDev                    Context of Thc device
  @param[in]  CurrentCBReadPointer      Circullar Buffer Read Pointer
  @param[in]  CurrentCBWritePointer     Circullar Buffer Write Pointer

**/
VOID
ThcDmaReadRx2 (
  IN THC_DEV                *ThcDev,
  IN UINT8                  CurrentCBWritePointer,
  IN UINT8                  CurrentCBReadPointer
  )
{
  THC_M_PRT_READ_DMA_CNTRL_2 ReadDmaCntrl2;
  EFI_STATUS                 Status;
  UINT8                      CurrentPrdTable;

  while ((CurrentCBWritePointer & POINTER_MASK) != (CurrentCBReadPointer & POINTER_MASK)) {
    CurrentPrdTable = (UINT8) (CurrentCBWritePointer & POINTER_MASK);
    THC_LOCAL_DEBUG(L"PrdTable %d CBWritePointer %d CBReadPointer %d CB 0x%X \n",
                     CurrentPrdTable,
                     CurrentCBWritePointer & POINTER_MASK,
                     CurrentCBReadPointer & POINTER_MASK,
                     CurrentCBWritePointer
                    )
    Status = ThcDmaReadSingleReport (ThcDev, &ThcDev->DmaRead2, CurrentPrdTable);
    if (EFI_ERROR (Status)) {
      THC_LOCAL_DEBUG(L"ThcDmaReadRx2 ThcDmaReadbuffer error, failed to Read Data Buffer Status %r\n", Status)
      DEBUG ((DEBUG_ERROR, "ThcDmaReadRx2 Error Read Data Buffer Status %r\n", Status));
      //no return to avoid dead loop, always change Write Pointer, even on bad data
    }

    //Return PRD table to its initial state
    ThcDmaFillSinglePrdTable (&ThcDev->DmaRead2, CurrentPrdTable);

    if ((CurrentCBWritePointer + 1) == WRAPAROUND_VALUE_16) {
      THC_LOCAL_DEBUG(L"WRAPAROUND_VALUE_16 \n")
      ThcLibSetReadRx2WritePointer (ThcDev->PciBar0, POINTER_WRAPAROUND);
    } else if ((CurrentCBWritePointer + 1) == WRAPAROUND_VALUE_0X90) {
      THC_LOCAL_DEBUG(L"WRAPAROUND_VALUE_0X90 \n")
      ThcLibSetReadRx2WritePointer (ThcDev->PciBar0, 0x0);
    } else {
      THC_LOCAL_DEBUG(L"WP +1\n")
      ThcLibSetReadRx2WritePointer (ThcDev->PciBar0, CurrentCBWritePointer + 1);
    }

    ReadDmaCntrl2.Data    = ThcLibGetReadRx2Data (ThcDev->PciBar0);
    CurrentCBWritePointer = (UINT8) ReadDmaCntrl2.Fields.ThcPrdCbWritePointer;
  }
}

/**
  Writes data to a single Tx DMA PRD Table

  @param[in]  ThcDev             Context of Thc device
  @param[in]  Buffer             Data Container that will be sent to external device
  @param[in]  DataHeader         Write Data Header

  @retval EFI_BUFFER_TOO_SMALL   THC DMA buffer is unable to fit that much data
  @retval EFI_TIMEOUT            DMA transaction did not finish in time
  @retval EFI_SUCCESS            Data sent
**/
EFI_STATUS
ThcDmaWriteTx (
  IN THC_DEV                *ThcDev,
  IN UINT8                  *Buffer,
  IN THC_WRITE_DATA_HDR     *DataHeader
  )
{
  PRD_TABLE                *PrdTable;
  UINT64                   DataAddress;
  UINT32                   PrdEntryLength;
  UINT32                   WriteLength;
  UINT16                   EntryIndex;

  DataAddress    = 0;
  PrdEntryLength = 0;
  EntryIndex     = 0;
  PrdTable       = (PRD_TABLE *) ThcDev->DmaWrite.CommonPrdBuffer;

  if ((PrdTable->Entries[0].Length * PRD_MAX_ENTRIES) < (DataHeader->WriteDataLength + sizeof (THC_WRITE_DATA_HDR))) {
    return EFI_BUFFER_TOO_SMALL;
  }

  //
  // Copy Header information, increase address and set remaining length of the first entry
  //
  DataAddress = LShiftU64 (PrdTable->Entries[EntryIndex].DestinationAddress, ADDRESS_SHIFT);
  CopyMem ((UINT8*) DataAddress, (UINT8*) DataHeader, sizeof (THC_WRITE_DATA_HDR));
  DataAddress += sizeof (THC_WRITE_DATA_HDR);
  PrdEntryLength = (UINT32) PrdTable->Entries[EntryIndex].Length - sizeof (THC_WRITE_DATA_HDR);

  do {
    PrdTable->Entries[EntryIndex].EndOfPrd = 0;
    //
    // Set write length for given Prd Entry
    //
    if (DataHeader->WriteDataLength >= PrdEntryLength) {
      WriteLength = PrdEntryLength;
    } else {
      WriteLength = DataHeader->WriteDataLength;
    }
    //
    // Put the data in the destination address
    //
    THC_LOCAL_DEBUG(L"ThcDmaWriteTx WriteLength %d\n", WriteLength)
    CopyMem ((UINT8*) DataAddress, Buffer, WriteLength);
    //
    // Substract copied data from the WriteDataLength
    //
    DataHeader->WriteDataLength = DataHeader->WriteDataLength - WriteLength;

    //
    // Store new write length along with the header in Prd entry.
    //
    if (EntryIndex == 0) {
      WriteLength += sizeof (THC_WRITE_DATA_HDR);
    }
    PrdTable->Entries[EntryIndex].Length   = WriteLength;

    if (DataHeader->WriteDataLength > 0) {
      Buffer += WriteLength;
      EntryIndex++;
      DataAddress = LShiftU64 (PrdTable->Entries[EntryIndex].DestinationAddress, ADDRESS_SHIFT);
      PrdEntryLength = (UINT32) PrdTable->Entries[EntryIndex].Length;
    } else {
      break;
    }
  } while (EntryIndex < ThcDev->DmaWrite.DriverPrdTable[0].NumOfConfiguredEntries);

  //
  // Set End on the last PRD entry used
  //
  PrdTable->Entries[EntryIndex].EndOfPrd = 1;

  //
  // Start transfer
  //
  ThcLibSetWriteStartBit (ThcDev->PciBar0);

  //
  // Poll for Dma Complete
  //
  if (EFI_ERROR (ThcLibPollDmaComplete (ThcDev->PciBar0, WritePollingTimeout))) {
    return EFI_TIMEOUT;
  }

  //
  // Reset PRD table settings
  //
  ThcDmaFillSinglePrdTable (&ThcDev->DmaWrite, 0);

  return EFI_SUCCESS;
}

/**
  Unmaps and frees Driver Prd Tables

  @param[in]  ThcDev             Context of Thc device
  @param[in]  ThcDma             Dma that stores Driver PRD Table

**/
VOID
ThcDmaFreePrds (
  IN THC_DEV                        *ThcDev,
  IN THC_DMA                        *ThcDma
  )
{
  UINT16         PrdTableIndex;

  for (PrdTableIndex = 0; PrdTableIndex < ThcDma->NumOfPrdTables; PrdTableIndex++) {
    ThcDev->PciIo->Unmap (
                        ThcDev->PciIo,
                        ThcDma->DriverPrdTable[PrdTableIndex].Mapping
                        );
    ThcDev->PciIo->FreeBuffer (
                          ThcDev->PciIo,
                          EFI_SIZE_TO_PAGES (ThcDma->BufferSize),
                          (UINT8 *) ThcDma->DriverPrdTable[PrdTableIndex].Buffer
                          );
  }
}

/**
  Stop Touch Panel, brings it back to reset state
  Freees all allocated memory and Thc device context

  @param[in]  ThcDev         Context of Thc device

**/
VOID
EFIAPI
ThcStop (
  IN THC_DEV                *ThcDev
  )
{
  if (ThcDev == NULL) {
    DEBUG ((DEBUG_ERROR, "ThcStop ThcDev is already Stopped\n"));
    return;
  }

  THC_LOCAL_DEBUG(L"ThcStop\n")

  ThcStopAbsPtr (ThcDev);
  ThcDisableEndDevice (ThcDev);
  ThcPrintConfig (ThcDev);
  ThcLibCleanUp (ThcDev->PciBar0);

  //
  // Free/Unmap Common Buffers and Prd Tables
  //
  if (ThcDev->DmaRead2.CommonPrdBuffer != 0) {
    THC_LOCAL_DEBUG(L"ThcStop Free DmaRead2.CommonPrdBuffer\n")
    ThcDev->PciIo->Unmap (
                        ThcDev->PciIo,
                        ThcDev->DmaRead2.CommonPrdBufferMapping
                        );
    ThcDev->PciIo->FreeBuffer (
                        ThcDev->PciIo,
                        EFI_SIZE_TO_PAGES (sizeof (PRD_TABLE) * PRD_READ_TABLES_SUPPORTED),
                        (UINT8 *) ThcDev->DmaRead2.CommonPrdBuffer
                        );
    ThcDmaFreePrds (ThcDev, &ThcDev->DmaRead2);
  }
  if (ThcDev->DmaWrite.CommonPrdBuffer != 0) {
    THC_LOCAL_DEBUG(L"ThcStop Free DmaWrite.CommonPrdBuffer\n")
    ThcDev->PciIo->Unmap (
                        ThcDev->PciIo,
                        ThcDev->DmaWrite.CommonPrdBufferMapping
                        );
    ThcDev->PciIo->FreeBuffer (
                        ThcDev->PciIo,
                        EFI_SIZE_TO_PAGES (sizeof (PRD_TABLE) * PRD_WRITE_TABLES_SUPPORTED),
                        (UINT8 *) ThcDev->DmaWrite.CommonPrdBuffer
                        );
    ThcDmaFreePrds (ThcDev, &ThcDev->DmaWrite);
  }

  //
  // Restore original PCI attributes
  //
  ThcDev->PciIo->Attributes (
                   ThcDev->PciIo,
                   EfiPciIoAttributeOperationSet,
                   ThcDev->PciAttributes,
                   NULL
                   );

  //
  // Close and Uninstall PCI I/O Protocol that was opened with PROTOCOL_BY_DRIVER
  //
  gBS->CloseProtocol (
         ThcDev->ControllerHandle,
         &gEfiPciIoProtocolGuid,
         &ThcDev->PciIo,
         ThcDev->ControllerHandle
         );
  gBS->UninstallMultipleProtocolInterfaces (
         ThcDev->ControllerHandle,
         &gEfiPciIoProtocolGuid,
         &ThcDev->PciIo,
         NULL
         );

  //
  // Done with the controller name table
  //
  FreeUnicodeStringTable (ThcDev->ControllerNameTable);

  //
  //  Done with the driver context
  //
  ZeroMem (ThcDev, sizeof (THC_DEV));
  FreePool (ThcDev);
}

/**
  Polls on Thc Rx2 Circullar Buffers state
  If CB Write and Read Pointer are not equal Read Rx2 Dma is trigerred

  @param[in]  Event       Polling event
  @param[in]  Context     Context of Thc device

**/
VOID
EFIAPI
ThcPolling (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  THC_DEV                    *ThcDev;
  THC_M_PRT_READ_DMA_CNTRL_2 ReadDmaCntrl2;
  UINT32                     Timeout;

  ThcDev = (THC_DEV *) Context;

  if (ThcDev == NULL) {
    DEBUG ((DEBUG_ERROR, "ThcPolling ThcDev is Null\n"));
    return;
  }
  if (ThcDev->ReadDone) {
    Timeout = PollingLoopTimeout;
    ReadDmaCntrl2.Data    = ThcLibGetReadRx2Data (ThcDev->PciBar0);
    while (((UINT8)(ReadDmaCntrl2.Fields.ThcPrdCbWritePointer  & POINTER_MASK)) != ((UINT8)(ReadDmaCntrl2.Fields.ThcPrdCbReadPointer & POINTER_MASK))) {
      ThcDev->ReadDone = FALSE;
      ThcDmaReadRx2 (ThcDev, (UINT8) ReadDmaCntrl2.Fields.ThcPrdCbWritePointer, (UINT8) ReadDmaCntrl2.Fields.ThcPrdCbReadPointer);
      ReadDmaCntrl2.Data    = ThcLibGetReadRx2Data (ThcDev->PciBar0);
      if (((UINT8)(ReadDmaCntrl2.Fields.ThcPrdCbWritePointer  & POINTER_MASK)) == ((UINT8)(ReadDmaCntrl2.Fields.ThcPrdCbReadPointer & POINTER_MASK))) {
        ThcDev->ReadDone = TRUE;
      }
      if (Timeout == 0) {
        DEBUG ((DEBUG_ERROR, "ThcPolling Timeout while reading DMA, possible interrupt storm\n"));
        ASSERT (FALSE);
        ThcDev->ReadDone = TRUE;
        return;
      }
      MicroSecondDelay (10);
      Timeout -= 10;
    }
  }
}

