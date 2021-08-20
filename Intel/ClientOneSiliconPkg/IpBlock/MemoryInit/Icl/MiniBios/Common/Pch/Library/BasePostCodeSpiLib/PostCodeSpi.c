/** @file
  Post Code Library instance that writes post code values to SPI 7 segment display.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/
#include "MrcOemPlatform.h"
//#include <Base.h>
//#include <ConfigBlock.h>
//#include <Library/PostCodeLib.h>
//#include <Library/PcdLib.h>
//#include <Library/IoLib.h>
//#include <Library/BaseLib.h>
//#include <Uefi.h>
//#include <Library/TimerLib.h>
#include "PciSegmentLib.h"
#include <Register/PchRegs.h>
#include <Register/PchRegsSerialIo.h>
#include <Library/PchSerialIoLib.h>
//#include <IndustryStandard/Pci30.h>
//#include <Pch/IncludePrivate/Library/SerialIoPrivateLib.h>
#include <PchReservedResources.h>
#include <Library/PostCodeSpiLib.h>
//#ifdef FSP_FLAG
//#include <Library/FspCommonLib.h>
//#else
//#include <Library/DebugPropertyLib.h>
//#endif

// N_VAL = 8192, Bit [30:16] = 0x2000
// M_VAL = 9, Bit [15:1] = 0x9
#define    SPI_NVAL_MVAL_SETTING           0x00640002
#define    TIME_OUT_VALUE                  16
#define    SpiRead(r)                      (*((volatile UINT32*)(UINTN)(r)))
#define    SpiWrite(r,d)                   (*((volatile UINT32*)(UINTN)(r)) = ((UINT32)(d)))

//#define BIOS_POST_CODE_PCU_REG             0x00005824
#define B_SERIAL_IO_MEM_SSSR_BSY_TNF       (B_SERIAL_IO_MEM_SSSR_BSY | B_SERIAL_IO_MEM_SSSR_TNF)
#define B_SERIAL_IO_MEM_SSSR_BSY_RNE       (B_SERIAL_IO_MEM_SSSR_BSY | B_SERIAL_IO_MEM_SSSR_RNE)

/**
  This function does the basic init work for SPI controller.

  @param[in]  SpiBaseAddress - Base Address of SPI Controller
**/
VOID
SpiControllerBusInit (
  UINT64          SpiBaseAddress
  )
{
  UINT32 D32;
  UINT32 D32Final;
  UINT8  Count;

  //
  // Program CTRLR0.
  //
  // Transmit FIFO Under Run Interrupt Mask = Masked, Bit 23 = 0x1
  // Receive FIFO Over Run Interrupt Mask = Masked, Bit 22 = 0x1
  // Network Clock Select = determined by ECS bit, Bit 21 = 0x0
  // Extended Data Size Select = sets the DSS range from 4-16 bits, Bit 20 = 0x0
  // Serial Clock Rate = Use the M/N divider, Bit [19:8] = 0x000
  // Synchronous Serial Port Enable = SSP operation enabled, Bit7 = 0x1
  // External Clock Select = use On-chip clock, Bit6 = 0x0
  // Frame Format = Motorola SPI, Bit[5:4] = 0x0
  // Data Frame Size = 16-bit transfer (1111b)
  //
  D32 = B_SERIAL_IO_MEM_SSCR0_TIM | B_SERIAL_IO_MEM_SSCR0_RIM | B_SERIAL_IO_MEM_SSCR0_SSE | B_SERIAL_IO_MEM_SSCR0_DSS_16_32;
  SpiWrite (SpiBaseAddress + R_SERIAL_IO_MEM_SSCR0, D32);

  //
  // Program CTRLR1
  //
  // Enable FIFO Write/Read = Enhanced SSP operates in the Normal mode, Bit 14 = 0x0
  // Receive FIFO Interrupt Enable = Interrupt is masked, Bit 0 = 0x0
  //
  SpiWrite (SpiBaseAddress + R_SERIAL_IO_MEM_SSCR1, 0x0);

  //
  // Program the Baud Rate.
  //
  D32Final = SpiRead(SpiBaseAddress + R_SERIAL_IO_MEM_PPR_CLK);                                            // get current clk value
  if (D32Final != (SPI_NVAL_MVAL_SETTING | BIT0)) {                                                          // don't reset if M/N set & clk enabled
    D32 = SPI_NVAL_MVAL_SETTING;                                                                             // set clk value
    //Per LPSS architect, must make 4 separate writes to the CLOCK_PARAMS register to avoid a data race

    //Step 1
    SpiWrite (SpiBaseAddress + R_SERIAL_IO_MEM_PPR_CLK, B_SERIAL_IO_MEM_PPR_CLK_EN);                       // Enable the clock (bit 0)

    //Step 2
    D32Final = SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_PPR_CLK);
    SpiWrite (SpiBaseAddress + R_SERIAL_IO_MEM_PPR_CLK, (D32 | D32Final));                                 // Write the M/N values to the register

    //Step 3
    D32Final = SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_PPR_CLK);
    SpiWrite (SpiBaseAddress + R_SERIAL_IO_MEM_PPR_CLK, (~(B_SERIAL_IO_MEM_PPR_CLK_UPDATE) & D32Final));   // Reset the M/N values

    //Step 4
    D32Final = SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_PPR_CLK);
    SpiWrite (SpiBaseAddress + R_SERIAL_IO_MEM_PPR_CLK, ((B_SERIAL_IO_MEM_PPR_CLK_UPDATE) | D32Final));    // Update M/N values into the divider (bit31)
  }

  //
  // Forcibly clear all interrupts
  //
  SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSITR);

  //
  // Ensure there are no interrupts in progress.
  //
  Count = 0;
  while ((((SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSITR) & 0xE0) != 0) || ((SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSITR) & 0xE0) != 0)) && (Count < TIME_OUT_VALUE)) {
    Count ++;
  }
}

/**
  This function send specific command to SPI current slave.

  @param[in]  SpiBaseAddress - Base Address of SPI Controller
              Command - The command need to issue to the current Slave chosen
              WaitForData - The need to wait for slave feedback or not. TRUE, yes wait for slave data; FALSE, return instantly

  @retval     The data returned for the command
**/
UINT32
SpiSlaveCmd (
  IN UINT64 SpiBaseAddress,
  IN UINT32 Command,
  IN BOOLEAN WaitForData
  )
{
  UINT8    Count;

  //
  // Issue the command
  //
  SpiWrite (SpiBaseAddress + R_SERIAL_IO_MEM_SSDR, Command);

  //
  // Wait for the command to complete when the SPI Host Controller is not busy,
  // and the transmit FIFO is empty meaning the command was sent, and the receive
  // FIFO is not empty meaning a value was returned from the sent command.
  //
  //   BSY (SSI Busy Flag)                  [BIT4] == 0
  //   RNE (Receive FIFO Not Empty)         [BIT3] == 0
  //   TNF (Transmit FIFO Not Full)         [BIT2] == 1
  //
  Count = 0;
  while (((SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSSR) & B_SERIAL_IO_MEM_SSSR_BSY_TNF) != B_SERIAL_IO_MEM_SSSR_TNF) && (Count < TIME_OUT_VALUE)) {
    Count ++;
  }

  //
  // Wait for the FIFO to be ready. (RFNE)
  //
  if (WaitForData == TRUE) {
    while (SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SIRF) == 0);
  }

  //
  // This delay of 10 Microsecs is required because it helps to successfully
  // process the commands at Max6950/MAX6951 device end. Although from Controller(master)
  // side BSY bit is cleared, and TNF Bit is Set, still from the device(slave) end it
  // needs specific amount of delay to process all the Single Digit based commands.
  //
  //MicroSecondDelay (10);
  for (UINTN i=0;i<9999999;i++);

  //
  // Return the data
  //
  return SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSDR);
}

/**
  This function does the basic init work for Max6950.

  @param[in]  SpiBaseAddress - Base Address of SPI Controller
**/
VOID
MaxLedInit (
  IN UINT64 SpiBaseAddress
  )
{
  UINT8     Count;

  //
  // Wait for SPI port to be Idle
  //
  Count = 0;
  while (((SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSSR) & B_SERIAL_IO_MEM_SSSR_BSY) == B_SERIAL_IO_MEM_SSSR_BSY) && (Count < TIME_OUT_VALUE)) {
    Count ++;
  }

  //
  // This is the meat of the Maxim part initialization.
  //
  // Set the display_test register fromat command 0x07 to indicate normal operation
  SpiSlaveCmd (SpiBaseAddress, 0x0700, FALSE);

  //
  // Set config regsiter format command 0x04 to indicate normal operation, slow
  // blink rate, global blinking function is disabled, global blink timing synch
  // which blink timing counters are unaffected, global clear digit data which
  // cause both plane P0 and P1 are unaffected.
  //
  SpiSlaveCmd (SpiBaseAddress, 0x0401, FALSE);

  //
  // Set the scan limit register format command 0x03 to indicate display for digits 7-0
  //
  SpiSlaveCmd (SpiBaseAddress, 0x0307, FALSE);

  //
  // Set the intensity register format command 0x02 to indicate duty cycle of 15/16 (max on)
  //
  SpiSlaveCmd (SpiBaseAddress, 0x020E, FALSE);

  //
  // Set the decode mode register format command 0x01 to indicate hex decode for digit 7-0
  //
  SpiSlaveCmd (SpiBaseAddress, 0x01FF, FALSE);

  //
  // Wait for SPI port to be Idle and the Xmit FIFO to be clear.
  //
  Count = 0;
  while (((SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSSR) & B_SERIAL_IO_MEM_SSSR_BSY_RNE) == B_SERIAL_IO_MEM_SSSR_BSY_RNE) && (Count < TIME_OUT_VALUE)) {
    Count ++;
  }
}

/**
  Does SPI Controller Init and MaxLed Init
**/
VOID
EFIAPI
SpiControllerAndMaxLedInit (
  VOID
  )
{
  UINT64 SpiBaseAddress = 0;
  UINT8 Count;

  //
  // Get Fixed Mmio Address since SPI1 was Configured as Hidden in SEC phase
  //
  SpiBaseAddress = GetSerialIoSpiFixedMmioAddress (SERIAL_IO_SPI_POSTCODE_NUMBER);
  if ((SpiBaseAddress == 0) || (SpiBaseAddress == 0xFFFFFFFF))
    return;

  SpiControllerBusInit (SpiBaseAddress);

  //
  // Wait for SPI port to be Idle
  //
  Count = 0;
  while (((SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSSR) & B_SERIAL_IO_MEM_SSSR_BSY) == B_SERIAL_IO_MEM_SSSR_BSY) && (Count < TIME_OUT_VALUE)) { 
    Count ++;
  }

  //
  // Wait for the controller to be not BUSY and the TX FIFO to be clear */
  //
  Count = 0;
  while (((SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSSR) & B_SERIAL_IO_MEM_SSSR_BSY_TNF) != B_SERIAL_IO_MEM_SSSR_TNF) && (Count < TIME_OUT_VALUE)) { 
    Count ++;
  }

  //
  // While there is anything that happens to be IN the FIFO, read it out.
  //
  Count = 0;
  while ((SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SIRF) > 0) && (Count < TIME_OUT_VALUE)) {
    SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SIRF);
    Count++;
  }

  MaxLedInit (SpiBaseAddress);

  //
  // Wait for SPI port to be Idle
  //
  Count = 0;
  while (((SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSSR) & B_SERIAL_IO_MEM_SSSR_BSY) == B_SERIAL_IO_MEM_SSSR_BSY) && (Count < TIME_OUT_VALUE)) { 
    Count ++;
  }
}

/**
  Send 4 digit PostCode commands to Max6950 device

  @param[in]  PostCodeValue - 4 digit PostCode value to be displayed
**/
VOID
EFIAPI
DisplayPostCode (
  IN UINT32 PostCodeValue
  )
{
  UINT64 SpiBaseAddress = 0;
  UINT16 SetDigitCommand;
  UINT16 SingleDigit;
  UINT8 Count;
  UINT8 i;

  //
  // Get Fixed Mmio Address since SPI1 was Configured as Hidden in SEC phase
  //
  SpiBaseAddress = GetSerialIoSpiFixedMmioAddress (SERIAL_IO_SPI_POSTCODE_NUMBER);
  if ((SpiBaseAddress == 0) || (SpiBaseAddress == 0xFFFFFFFF))
    return;

  //
  // Wait for SPI port to be Idle
  //
  Count = 0;
  while (((SpiRead (SpiBaseAddress + R_SERIAL_IO_MEM_SSSR) & B_SERIAL_IO_MEM_SSSR_BSY) == B_SERIAL_IO_MEM_SSSR_BSY) && (Count < TIME_OUT_VALUE)) { 
    Count ++;
  }

  //
  // Write all the digits.
  //
  for (i = 0; i < 4; i++) {
    SingleDigit = (PostCodeValue >> (4 * i)) & 0xF;
    SetDigitCommand = (UINT16)(((0x60 + i) << 8) + SingleDigit);
    SpiSlaveCmd (SpiBaseAddress, SetDigitCommand, FALSE);
  }
}

/**
  Write the Postcode's Phase Status code value into a scratchpad register

  @param[in]  PhaseCode - The PhaseCode value to save to scratchpad register
**/
VOID
SetPhaseStatusCodeToScratchpadReg (
  UINT32 PhaseCode
  )
{
  UINT32     MchBar;
  UINT32     OrValue;

  MchBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0, 0, 0x48)) &~BIT0;
  OrValue = (UINT32)(PhaseCode << 16);
  MmioAndThenOr32 ((MchBar + BIOS_POST_CODE_PCU_REG), 0x0FFFFFFF, OrValue);
}

/**
  Read the Phase Status code value from the scratch pad register

  @param[in]  None

  @retval     The phase status code value from the scratchpad register
**/
UINT32
GetPhaseStatusCodeFromScratchpadReg (void)
{
  UINT32     MchBar;
  UINT32     PhaseCode;

  MchBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0, 0, 0x48)) & ~BIT0;
  PhaseCode = ((MmioRead32 ((MchBar + BIOS_POST_CODE_PCU_REG)) & 0xF0000000) >> 16);
  return PhaseCode;
}

/**
  The PostCode function prints a postcode to the SPI device MaxLed6950

  @param[in]  Value - PostCode Value

  @retval     Complete PostCode Value with Phase Status Code.
**/
UINT32
EFIAPI
PostCode (
  IN UINT32  Value
  )
{
#ifdef FSP_FLAG
  Value |= GetPhaseStatusCode ();
#else
//  DebugPropertyAction (Value);
//  Value |= GetPhaseStatusCodeFromScratchpadReg ();
#endif
  DisplayPostCode (Value);
  // Temporary add back port 80 post code display in case SPI post code not working properly
  IoWrite16 (0x80, (UINT16) Value);
  return Value;
}

/**
  The constructor function initialize the SpiPostCode Library

  @param[in]  None

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.
**/
RETURN_STATUS
EFIAPI
SpiPostCodeLibConstructor (
  VOID
  )
{
  SpiControllerAndMaxLedInit ();
  return RETURN_SUCCESS;
}