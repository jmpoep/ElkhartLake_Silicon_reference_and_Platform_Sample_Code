/**@file

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification
**/

#define EHL_PCH_LP_SERIAL_IO_CFG_SPI1_DEVICE_ID       0x4B2B

  Name(SSIN,0x0)
  Name(SIN,0x0)

If (LEqual(SPI1_MODE, SERIAL_IO_SPI_HIDDEN)) {
  OperationRegion(SPI1, SystemMemory, 0xFE032000, 0x228) //Address equals to SPI1 fixed MMIO address for hidden mode (PCH_SERIAL_IO_BASE_ADDRESS + 0x12000)
  Field(SPI1, DWordAcc, NoLock, Preserve) {
    Offset(R_SERIAL_IO_MEM_SSCR0),          SCR0, 32,  //SSP Control Register 0
    Offset(R_SERIAL_IO_MEM_SSCR1),          SCR1, 32,  //SSP Control Register 1 (SSCR1)
    Offset(R_SERIAL_IO_MEM_SSSR),           SSSR, 32,  //SSP Status Register (SSSR)
    Offset(R_SERIAL_IO_MEM_SSITR),          SITR, 32,  //SSP Interrupt Test Register (SSITR)
    Offset(R_SERIAL_IO_MEM_SSDR),           SSDR, 32,  //SSP Data (SSDR)
    Offset(R_SERIAL_IO_MEM_SIRF),           SIRF, 32,  //SPI Receive FIFO (SIRF)
    Offset(R_SERIAL_IO_MEM_PPR_CLK),        CPAR, 32,  //CLOCK_PARAMS
    Offset(R_SERIAL_IO_MEM_SPI_CS_CONTROL), SCSC, 32,  //SPI_CS_CONTROL
  }
}
  //
  // There are only 1 public functions that may be called by external code:
  // ASPC(POSTCODE)     - Display post code.
  // Everything else inside ASPC is internal implementation, not to be called from outside
  //

  // ASPC - Display ACPI post code.
  // Arg0= PostCode to display.
  Mutex(MUTX, 0)
  Method(ASPC, 1, Serialized) {
    OperationRegion (SPCF, SystemMemory, SPI1_PCIE_BASE, Add (R_SERIAL_IO_CFG_PME_CTRL_STS, 1))
      Field (SPCF, AnyAcc, NoLock, Preserve) {
        Offset(PCI_DEVICE_ID_OFFSET),
        VDID, 16,
        Offset(R_SERIAL_IO_CFG_PME_CTRL_STS),
        PMCS,2
      }
    If (LEqual(VDID, EHL_PCH_LP_SERIAL_IO_CFG_SPI1_DEVICE_ID)) {
      Name(STMP,0) // scratch variable that doesn't cause compiler warnings as writes to Localx variables does.
      Store(Acquire(MUTX, 0x1000), Local0) // Save Acquire result so we can check for Mutexacquired
      If (LEqual(Local0, Zero)) { // Check for Mutexacquired
        Store(0x0,PMCS) // Putting device into D0 state
        Store(PMCS, STMP) // perform a read back to avoid ordering and noncoherency problems
        SPPC(Arg0)
        Store(0x3,PMCS) // Putting device into D3 state
        Store(PMCS, STMP) // perform a read back to avoid ordering and noncoherency problems
        Release(MUTX)
      }
    }
  } // End of ASPC

  //
  //Initialize SPI controller
  //

  Method(INSP,0,Serialized) {

    //Program CTRLR0.
    //SCR0[BIT23] : 0 = Transmit FIFO Under Run(TUR) events will generate an SSP interrupt, 1 = TUR events will be masked
    //SCR0[BIT22] : 0 = receive FIFO Over Run(ROR) events will generate an SSP interrupt, 1 - ROR events will be masked
    //SCR0[BIT7]  : 0 = SSP operation disabled, 1 = SSP operation enabled
    Store(Or(Or(BIT23,BIT22),Or(BIT7,0x0F)),SCR0)

    //Program CTRLR1.
    Store(0,SCR1)
    Store(SCR1,Local0)

   //Program the Baud Rate.
    Store(CPAR,Local0)

    if(LNotEqual(Local0,Or(0x00640002,BIT0))) {  // Don't reset if M/N set & clk enabled

      // Step 1
      Store(BIT0,CPAR)                           // Enable the clock (Bit 0)

      // Step 2
      Store(CPAR,Local0)
      Store(Or(0x00640002,Local0),CPAR)          // Write the M/N values to the register

      // Step 3
      Store(CPAR,Local0)
      Store(And((Not(BIT31)),Local0),CPAR)       // Reset the M/N values

      // Step 4
      Store(CPAR,Local0)
      Store(Or(BIT31,Local0),CPAR)               // Update M/N values into the divider (bit31)
    }

    //Ensure there are no interrupts in progress.
    Store(SITR, Local0)

    //Wait until SITR[BIT7] = 0 - No receive FIFO overrun service request
    //           SITR[BIT6] = 0 - No receive FIFO service request
    //           SITR[BIT5] = 0 - No transmit FIFO service request pending
    while(LNotEqual(And(Local0,0xE0),0)) {
      Store(SITR, Local0)
    }
  } //End of INSP

  //
  //This function send specific command to SPI current slave.
  //
  //Arg0 - Command, Arg1 - Wait for Data (TRUE/FALSE)
  Method(SCMD,2,Serialized) {

    // Issue the command
    Store(Arg0,SSDR)

    //
    // Wait for the command to complete when the SPI Host Controller is not busy,
    // and the transmit FIFO is empty meaning the command was sent, and the receive
    // FIFO is not empty meaning a value was returned from the sent command.
    //
    //   BSY (SSI Busy Flag)                  [BIT4] == 0
    //   RNE (Receive FIFO Not Empty)         [BIT3] == 0
    //   TNF (Transmit FIFO Not Full)         [BIT2] == 1
    //
    Store(SSSR,Local0)
    while(LNotEqual(And(Local0,Or(BIT4,BIT2)),BIT2)) {
      Store(SSSR,Local0)
    }

    // Wait for the FIFO to be ready. (RFNE)
    if(LEqual(Arg1,1)) {
      Store(SIRF,Local0)
      while(LEqual(Local0,0)) {
        Store(SIRF,Local0)
      }
    }
    Stall(50)
  } //End of SCMD

  //
  // SPIPostCodeWrite Arg0 - Value to disaplay is post code.
  //

  Method(SPPC,1,Serialized) {
    //
    // Use clk to determine if already init
    //
    Store(CPAR,Local0)
    if(LNotEqual(Local0,Or(0x00640002,BIT0))) {
      //CPAR[BIT0] : 1 =  Clock Enabled
      Store(BIT0,CPAR)
      //Set CPAR[30:16] = 6400 (Denominator value N for M/N logic)
      //Set CPAR[15:1]  = 2    (Numerator value M for M/N logic)
      Store(CPAR,Local0)
      Store(Or(0x00640002,Local0),CPAR)
      // Reset the M/N values
      Store(CPAR,Local0)
      Store(And((Not(BIT31)),Local0),CPAR)
      // Update M/N values into the divider (bit31)
      Store(CPAR,Local0)
      Store(Or(BIT31,Local0),CPAR)
    }Else {
       Store(0x1,SSIN) //Controller already Initialized
       Store(0x1,SIN)  //Max6950 is already Initialized
    }

    //Initialize SPI controller
    if(LEqual(SSIN,0x0)) {
      INSP()
      Store(0x1,SSIN)
    }

    //
    //Select UART device
    //

    //Wait for SPI port to be Idle
    Store(SSSR,Local0)
    //
    // SSP Status Register (SSSR) - SSSR[BIT4] == 0 - SSP is idle or disabled, 1 - SSP currently transmitting or receiving a frame
    //
    while(LEqual(And(Local0,BIT4),BIT4)) {  //Wait until BSY bit is clear
      Store(SSSR,Local0)
    }

    //Select the appropriate slave device
    Store(SCSC,Local0)
    And(Local0,0xFFFFFFFE,Local0) // Set the mode to HW Mode
    Store(Local0,SCSC)
    Store(SCSC,Local0)

    //
    // Control Polarity Register SPI_CS_CONTROL
    // SPI_CS_CONTROL[BIT8 : BIT9] : 00 = SPI CS0
    //
    //
    if(LNotEqual(And(Local0,Or(BIT8,BIT9)),0x00))
    {
      // It  is the responsibility of the SW Driver to quiescence the current SPI transactions before
      // switching to another SPI_CS output/connect device.

      // Reset SPI controller by writing SSP Control Register 0[BIT31 - BIT0] = 0
      Store(0,SCR0)
      Stall(10)

      // Initialize SPI controller
      INSP()
      Store(SCSC,Local0)

      //Clear SPI CS Output Select[BIT9,BIT8]
      Store(And(Local0,Not(Or(BIT8,BIT9))),Local0)

      Store(Or(Local0,0x00),Local0)

      //Write updated value into SPI_CS_CONTROL
      Store(Local0,SCSC)

      Store(SCSC,Local0)
      //Wait till SPI_CS_CONTROL[BIT8 : BIT9] is 00
      while(LNotEqual(And(Local0,Or(BIT8,BIT9)),0x00))
      {
      }
    }

    // Wait for the controller to be not BUSY and the TX FIFO to be clear
    //SSSR[BIT4] : 1 - Busy, 0 - Idle
    //SSSR[BIT2] : 1 - Transmit FIFO is not full, 0 - Transmit FIFO is full
    Store(SSSR,Local0)
    while(LNotEqual(And(Local0,Or(BIT4,BIT2)),BIT2)) {
      Store(SCSC,Local0)
      Store(SSSR,Local0)
    }

    // While there is anything that happens to be IN the FIFO, read it out.
    Store(0,Local1)

    Store(SIRF,Local0)
    //Wait till SPI Receive FIFO (SIRF) > 0
    while(LAnd(LGreater(Local0,0),LLess(Local1,16))) {
      //Read Data in SSP Data (SSDR) register.
      Store(SSDR,Local0)
      Store(SIRF,Local0)
      ADD(Local1,1,Local1)
    }

    if(LGreater(Local1,16)) {
      return(0xFF);
    }

    //
    //Initialize Max6950
    //

    if(LEqual(SIN,0x0)) {
      // Wait for SPI port to be Idle
      Store(SSSR,Local0)

      //SSSR[BIT4] : 1 - Busy, 0 - Idle
      while(LEqual(And(Local0,BIT4),BIT4)) {
        Store(SSSR,Local0)
      }

      //
      // This is the meat of the Maxim part initialization.
      //
      // Set the display_test register fromat command 0x07 to indicate normal operation
      SCMD(0x0700,0)


      // Digit data for both planes P0 and P1 are cleared on the rising edge of /CS
      SCMD(0x0420,0)

      //
      // Set config regsiter format command 0x04 to indicate normal operation, slow
      // blink rate, global blinking function is disabled, global blink timing synch
      // which blink timing counters are unaffected, global clear digit data which
      // cause both plane P0 and P1 are unaffected.
      //
      SCMD(0x0401,0)

      //
      // Set the scan limit register format command 0x03 to indicate display for digits 7-0
      //
      SCMD(0x0307,0)

      //
      // Set the intensity register format command 0x02 to indicate duty cycle of 15/16 (max on)
      //
      SCMD(0x020E,0)

      //
      // Set the decode mode register format command 0x01 to indicate hex decode for digit 7-0
      //
      SCMD(0x01FF,0)

      //
      // Wait for SPI port to be Idle and the Xmit FIFO to be clear.
      //
      Store(SSSR,Local0)
      //SSSR[BIT4] : 1 - Busy, 0 - Idle
      //SSSR[BIT3] : 1 - Receive FIFO is not empty, 0 - Receive FIFO is empty
      while(LAnd(LEqual(And(Local0,BIT4),BIT4),LEqual(And(Local0,BIT3),BIT3))) {
        Store(SSSR,Local0)
      }
      Store(0x1,SIN)
    }//End of Initialize Max6950

    //
    //Wait for SPI port to be Idle
    //
    Store(SSSR,Local0)
    //SSSR[BIT4] : 1 - Busy, 0 - Idle
    while(LEqual(And(Local0,BIT4),BIT4)) {
      Store(SSSR,Local0)
    }

    //
    //Write all the digits.
    //
    // --------------------------------------------------------------------
    // |0 | 1 | 2 | 3| 4 | 5 | 6 | 7 |8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
    // |------------------------------------------------------------------|
    // |           Address           | MSB           DATA             LSB |
    // |                             |                                    |
    // --------------------------------------------------------------------
    // Address 0x60  - Digit 0 plane P0 and plane P1 (with same data)
    // Address 0x61  - Digit 1 plane P0 and plane P1 (with same data)
    // Address 0x62  - Digit 2 plane P0 and plane P1 (with same data)
    // Address 0x63  - Digit 3 plane P0 and plane P1 (with same data)
    //
    Store(0,Local1)
    Store(0,Local2)
    while(LLess(Local1,4)) {
      ShiftLeft(ADD(Local1,0x60,Local0),8,Local0)
      Multiply(Local1,4,Local2)
      ADD(Local0, And(ShiftRight(Arg0,Local2),0x0F),Local0)
      ADD(Local1,1,Local1)
      SCMD(Local0,0)
    }

    //
    // Wait for SPI port to be Idle and the Xmit FIFO to be clear.
    //
    Store(SSSR,Local0)
    //SSSR[BIT4] : 1 - Busy, 0 - Idle
    //SSSR[BIT3] : 1 - Receive FIFO is not empty, 0 - Receive FIFO is empty
    while(LAnd(LEqual(And(Local0,BIT4),BIT4),LEqual(And(Local0,BIT3),BIT3))) {
      Store(SSSR,Local0)
    }
    return (Local0)
  }// End of SPPC