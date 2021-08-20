/** @file
  This file provides services for Itss policy function

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PchInfoLib.h>
#include <ConfigBlock.h>
#include <InterruptConfig.h>

typedef enum {
  PchPIRQA = 16,
  PchPIRQB, //17
  PchPIRQC, //18
  PchPIRQD, //19
  PchPIRQE, //20
  PchPIRQF, //21
  PchPIRQG, //22
  PchPIRQH  //23
} PCH_PIRQ_ROUTE;

/**
  mDevIntConfig[] table contains data on INTx and IRQ for each device.
  IRQ value for devices which use ITSS INTx->PIRQx mapping need to be set in a way
  that for each multifunctional Dxx:Fy same interrupt pins must map to the same IRQ.
  Those IRQ values will be used to update ITSS.PIRx register.
  In APIC relationship between PIRQs and IRQs is:
  PIRQA -> IRQ16
  PIRQB -> IRQ17
  PIRQC -> IRQ18
  PIRQD -> IRQ19
  PIRQE -> IRQ20
  PIRQF -> IRQ21
  PIRQG -> IRQ22
  PIRQH -> IRQ23

  Devices which use INTx->PIRQy mapping are: cAVS(in PCI mode), SMBus, GbE, TraceHub, PCIe,
  SATA, HECI, IDE-R, KT Redirection, xHCI, Thermal Subsystem, Camera IO Host Controller

  PCI Express Root Ports mapping should be programmed only with values as in below table (D27/28/29)
  otherwise _PRT methods in ACPI for RootPorts would require additional patching as
  PCIe Endpoint Device Interrupt is further subjected to INTx to PIRQy Mapping

  Configured IRQ values are not used if an OS chooses to be in PIC instead of APIC mode
**/
GLOBAL_REMOVE_IF_UNREFERENCED PCH_DEVICE_INTERRUPT_CONFIG mDevIntConfig[] = {
//  {31, 0, PchNoInt, 0}, // LPC/eSPI Interface, doesn't use interrupts
//  {31, 1, PchNoInt, 0}, // P2SB, doesn't use interrupts
//  {31, 2, PchNoInt, 0}, // PMC , doesn't use interrupts
  {31, 3, PchIntA, PchPIRQA}, // cAVS(Audio, Voice, Speach), INTA is default, programmed in PciCfgSpace 3Dh
  {31, 4, PchIntA, PchPIRQA}, // SMBus Controller, no default value, programmed in PciCfgSpace 3Dh
//  {31, 5, PchNoInt, 0}, // SPI , doesn't use interrupts
  {31, 7, PchIntA, PchPIRQA}, // NorthPeak TraceHub, INTA is default, RO register
  {30, 0, PchIntA, PchPIRQA}, // SerialIo: UART #0, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[7]
  {30, 1, PchIntB, PchPIRQB}, // SerialIo: UART #1, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[8]
  {30, 2, PchIntC, PchPIRQC}, // SerialIo: SPI #0, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[10]
  {30, 3, PchIntD, PchPIRQD}, // SerialIo: SPI #1, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[11]
  {30, 4, PchIntA, PchPIRQA}, // TSN Gbe Controller, INTx
  {29, 0, PchIntA, PchPIRQA}, // PSE LH2PSE IPC
  {29, 1, PchIntA, PchPIRQA}, // PSE TSN GBE-0
  {29, 2, PchIntA, PchPIRQA}, // PSE TSN GBE-1
  {29, 3, PchIntB, 34}, // PSE DMA-0
  {29, 4, PchIntC, 35}, // PSE DMA-1
  {29, 5, PchIntD, 36}, // PSE DMA-2
  {29, 6, PchIntA, PchPIRQA}, // PSE PWM
  {29, 7, PchIntA, PchPIRQA}, // PSE ADC
  {28, 0, PchIntA, PchPIRQA}, // PCI Express Port 1, INT is default, programmed in PciCfgSpace + FCh
  {28, 1, PchIntB, PchPIRQB}, // PCI Express Port 2, INT is default, programmed in PciCfgSpace + FCh
  {28, 2, PchIntC, PchPIRQC}, // PCI Express Port 3, INT is default, programmed in PciCfgSpace + FCh
  {28, 3, PchIntD, PchPIRQD}, // PCI Express Port 4, INT is default, programmed in PciCfgSpace + FCh
  {28, 4, PchIntA, PchPIRQA}, // PCI Express Port 5, INT is default, programmed in PciCfgSpace + FCh
  {28, 5, PchIntB, PchPIRQB}, // PCI Express Port 6, INT is default, programmed in PciCfgSpace + FCh
  {28, 6, PchIntC, PchPIRQC}, // PCI Express Port 7, INT is default, programmed in PciCfgSpace + FCh
//  {28, 7, PchIntD, PchPIRQD}, // PCI Express Port 8, INT is default, programmed in PciCfgSpace + FCh //TODO: From spec there is not PCIe Port 8, need to reconfirm
  {27, 0, PchIntA, PchPIRQA}, // PSE I2C-0
  {27, 1, PchIntB, PchPIRQB}, // PSE I2C-1
  {27, 2, PchIntC, PchPIRQC}, // PSE I2C-2
  {27, 3, PchIntD, PchPIRQD}, // PSE I2C-3
  {27, 4, PchIntA, PchPIRQA}, // PSE I2C-4
  {27, 5, PchIntB, PchPIRQB}, // PSE I2C-5
  {27, 6, PchIntC, PchPIRQC}, // PSE I2C-6
  {26, 0, PchIntA, PchPIRQA}, // SCS: eMMC
  {26, 1, PchIntB, PchPIRQB}, // SCS: SD
  {26, 2, PchIntC, PchPIRQC}, // SCS: SD1
  {26, 3, PchIntD, PchPIRQD}, // ISI
  {25, 0, PchIntA, 31}, // SerialIo I2C Controller #4, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[5]
  {25, 1, PchIntB, 32}, // SerialIo I2C Controller #5, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[6]
  {25, 2, PchIntC, 33}, // SerialIo UART Controller #2, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[9]
  {24, 0, PchIntA, PchPIRQA}, // PSE I2C-7
  {24, 1, PchIntB, PchPIRQB}, // PSE CAN-0
  {24, 2, PchIntC, PchPIRQC}, // PSE CAN-1
  {24, 3, PchIntD, PchPIRQD}, // PSE QEP-1
  {24, 4, PchIntA, PchPIRQA}, // PSE QEP-2
  {24, 5, PchIntB, PchPIRQB}, // PSE QEP-3
  {24, 6, PchIntC, PchPIRQC}, // PSE QEP-4
  {23, 0, PchIntA, PchPIRQA}, // SATA Controller, INTA is default, programmed in PciCfgSpace + 3Dh
  {22, 0, PchIntA, PchPIRQA}, // CSME: HECI #1
  {22, 1, PchIntB, PchPIRQB}, // CSME: HECI #2
  {22, 4, PchIntC, PchPIRQC}, // CSME: HECI #3
  {22, 5, PchIntD, PchPIRQD}, // CSME: HECI #4
//  {22, 7, PchIntA, PchPIRQA}, // CSME: WLAN
  {21, 0, PchIntA, 27}, // SerialIo I2C Controller #0, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[1]
  {21, 1, PchIntB, 28}, // SerialIo I2C Controller #1, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[2]
  {21, 2, PchIntC, 29}, // SerialIo I2C Controller #2, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[3]
  {21, 3, PchIntD, 30}, // SerialIo I2C Controller #3, INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[4]
//  {21, 7, PchNoInt, 0}, // NorthPeak Phantom ACPI Function
  {20, 0, PchIntA, PchPIRQA}, // USB 3.0 xHCI Controller, no default value, programmed in PciCfgSpace 3Dh
  {20, 1, PchIntB, PchPIRQB}, // USB Device Controller (OTG)
//  {20, 2, PchNoInt, 0}, // Shared SRAM, no interrupts
  {20, 3, PchIntA, PchPIRQA}, // CNVi WiFi
//  {20, 4, PchNoInt, 0}, // vTIO Phantom ACPI Function
  {19, 0, PchIntA, PchPIRQA}, // PSE SPI-0
  {19, 1, PchIntB, PchPIRQB}, // PSE SPI-1
  {19, 2, PchIntC, PchPIRQC}, // PSE SPI-2
  {19, 3, PchIntD, PchPIRQD}, // PSE SPI-3
  {19, 4, PchIntA, PchPIRQA}, // PSE GPIO-0
  {19, 5, PchIntB, PchPIRQB}, // PSE GPIO-1
  {18, 0, PchIntA, 24}, // SerialIo: SPI #2 INTA is default, programmed in PCR[SERIALIO] + PCICFGCTRL[12]
//  {18, 4, PchNoInt, PchPIRQC}, // CSME: fTPM DMA Phantom (ACPI) Function
  {18, 5, PchIntB, 25}, // SCS: UFS #0
  {18, 7, PchIntC, 26}, // SCS: UFS #1
  {17, 0, PchIntA, PchPIRQA}, // PSE UART-0
  {17, 1, PchIntB, PchPIRQB}, // PSE UART-1
  {17, 2, PchIntC, PchPIRQC}, // PSE UART-2
  {17, 3, PchIntD, PchPIRQD}, // PSE UART-3
  {17, 4, PchIntA, PchPIRQA}, // PSE UART-4
  {17, 5, PchIntB, PchPIRQB}, // PSE UART-5
  {17, 6, PchIntC, PchPIRQC}, // PSE IS2-0
  {17, 7, PchIntD, PchPIRQD}, // PSE IS2-1
  {16, 0, PchIntA, PchPIRQA}, // SerialIo: I2C #6
  {16, 1, PchIntB, PchPIRQB}, // SerialIo: I2C #7
  {16, 2, PchIntC, PchPIRQC}, // BT CNVi
//  {16, 5, PchIntB, PchPIRQB}, // IEH
  {16, 6, PchIntA, PchPIRQA}, // THC #0
  {16, 7, PchIntB, PchPIRQB}  // THC #1
};

/**
  Adds interrupt configuration for device

  @param[in/out] NumOfDevIntConfig      Point of Number of Device Interrupt Config
  @param[in/out] DevIntConfig           Array which stores PCH devices interrupts settings
**/
VOID
EFIAPI
LoadDeviceInterruptConfig (
  IN OUT UINT8                          *NumOfDevIntConfig,
  IN OUT PCH_DEVICE_INTERRUPT_CONFIG    DevIntConfig[]
  )
{
  UINT8                 IntConfigTableEntries;

  IntConfigTableEntries = ARRAY_SIZE (mDevIntConfig);
  ASSERT (IntConfigTableEntries <= PCH_MAX_DEVICE_INTERRUPT_CONFIG);
  *NumOfDevIntConfig = IntConfigTableEntries;
  CopyMem (
    DevIntConfig,
    mDevIntConfig,
    sizeof (mDevIntConfig)
    );
}
