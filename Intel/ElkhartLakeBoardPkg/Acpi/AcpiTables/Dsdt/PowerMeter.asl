/** @file
  Power Meter Device Configuration

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

Scope(\_SB.PC00.I2C5)
{
  //
  // PA01 Device: Defines how the PAC193x is connected to the I2C Controller.
  //
  Device(PA01)
  {
    Name(_HID, "MCHP1930")
    Name(_UID, 0)

    Method(_STA, 0x0, NotSerialized)
    {
      If (POME)
      {
        Return(0xf)
      }
      Return (0x0)
    }

    //
    // Current Resources Settings
    //
    Method(_CRS, 0x0, Serialized)
    {
      Name(RBUF, ResourceTemplate()
      {
        I2CSerialBus(0x18,                  // 7-bit Slave Address
                    ControllerInitiated,    // Slave or master?
                    400000,                 // Connection Speed in hz
                    AddressingMode7Bit,     // 7-bit or 10-bit addressing?
                    "\\_SB.PC00.I2C5",      // I2C Controller to which PAC is connected
                    0,                      // Resource Index
                    ResourceConsumer)       // Consumer or Producer?
      })
      Return(RBUF)
    }

    //
    // _DSM - Device Specific Method
    //
    // This method returns configuration information that tells the driver
    // which devices each line in the PAC193x is wired to monitor.
    // Names of the monitored devices must come from the Microsoft-defined
    // power rail taxonomy.
    //
    // The UUID for the Microchip PAC193x's DSM is {033771E0-1705-47B4-9535-D1BBE14D9A09}.
    // This is unique to the device, and must match what the Windows PAC193x driver expects.
    //
    // Returns:
    //         Either: A Buffer (for Functions 0 and 2, or an error)
    //                 A Package containing EMI resources (rail/resistor pairs)
    //
    // Input Arguments (per _DSM standard):
    //
    //     Arg0: UUID - Function Identifier
    //     Arg1: Integer - Revision
    //     Arg2: Integer - Function Index
    //     Arg3: Package - Parameters (not used in our implementation)
    //
    Function(_DSM, {BuffObj, PkgObj}, {BuffObj, IntObj, IntObj, PkgObj})
    {
      //033771E0-1705-47B4-9535-D1BBE14D9A09
      //  Is our UUID being invoked?
      //
      if(LNotEqual(Arg0, ToUUID("033771E0-1705-47B4-9535-D1BBE14D9A09")))
      {
        //
        // It's NOT our UUID -- Just return a NULL for error
        //
        return(Buffer() {0x0})
      }
      //
      // Switch based on the function number requested...
      //
      switch(ToInteger(Arg2))
      {
        //
        // Function zero returns a bit-mask of supported functions
        //
        case(0)
        {
          //
          // Revision 0 is the only revision presently defined
          //
          if(LEqual(Arg1, 0x00))
          {
            //
            // Functions 0,1, and 2 are supported
            //
            return(Buffer() {0x07})
          }
          break;
        }
        //
        // Function one returns the Channel Info Package
        //
        case(1)
        {
          //
          // Revision 0 is the only revision presently defined.
          //
          If(LEqual(Arg1, 0x0))
          {
            //
            // Return channel info with alternating names and resistor values.
            //
            Name(PBUF, Package()
            {
              //
              // Power
              // Rail        Resistor
              // Name        Value
              //
              "CPU_1", 2, // Channel 1
              "CPU_2", 2, // Channel 2
              "CPU_3", 2, // Channel 3
              "SOC_DSW",2 // Channel 4
            })
            return(PBUF)
          }
          break;
        }
        //
        // Function two returns the Channel Count
        //
        case(2)
        {
          //
          // Revision 0 is the only revision presently defined.
          //
          If(LEqual(Arg1, 0x0))
          {
            //
            // Actual count of channels.
            //
            return(Buffer() {0x04})
          }
          break;
        }
      } // switch(Arg2)
      //
      // Return an error (a buffer with a value of zero)
      // if we didn't return anything else above
      //
      return(Buffer() {0x0})
    } // _DSM
  } // PowerMeter Device PA01 Scope End

  //
  // PA02 Device: Defines how the PAC193x is connected to the I2C Controller.
  //
  Device(PA02)
  {
    Name(_HID, "MCHP1930")
    Name(_UID, 1)

    Method(_STA, 0x0, NotSerialized)
    {
      If(POME)
      {
        Return(0xf)
      }
      Return (0x0)
    }

    //
    // Current Resources Settings
    //
    Method(_CRS, 0x0, Serialized)
    {
      Name(RBUF, ResourceTemplate()
      {
        I2CSerialBus(0x1E,                  // 7-bit Slave Address
                    ControllerInitiated,    // Slave or master?
                    400000,                 // Connection Speed in hz
                    AddressingMode7Bit,     // 7-bit or 10-bit addressing?
                    "\\_SB.PC00.I2C5",      // I2C Controller to which PAC is connected
                    0,                      // Resource Index
                    ResourceConsumer)       // Consumer or Producer?
      })
      Return(RBUF)
    }

    //
    // _DSM - Device Specific Method
    //
    // This method returns configuration information that tells the driver
    // which devices each line in the PAC193x is wired to monitor.
    // Names of the monitored devices must come from the Microsoft-defined
    // power rail taxonomy.
    //
    // The UUID for the Microchip PAC193x's DSM is {033771E0-1705-47B4-9535-D1BBE14D9A09}.
    // This is unique to the device, and must match what the Windows PAC193x driver expects.
    //
    // Returns:
    //         Either: A Buffer (for Functions 0 and 2, or an error)
    //                 A Package containing EMI resources (rail/resistor pairs)
    //
    // Input Arguments (per _DSM standard):
    //
    //     Arg0: UUID - Function Identifier
    //     Arg1: Integer - Revision
    //     Arg2: Integer - Function Index
    //     Arg3: Package - Parameters (not used in our implementation)
    //
    Function(_DSM, {BuffObj, PkgObj}, {BuffObj, IntObj, IntObj, PkgObj})
    {
      //033771E0-1705-47B4-9535-D1BBE14D9A09
      //  Is our UUID being invoked?
      //
      if(LNotEqual(Arg0, ToUUID("033771E0-1705-47B4-9535-D1BBE14D9A09")))
      {
        //
        // It's NOT our UUID -- Just return a NULL for error
        //
        return(Buffer() {0x0})
      }
      //
      // Switch based on the function number requested...
      //
      switch(ToInteger(Arg2))
      {
        //
        // Function zero returns a bit-mask of supported functions
        //
        case(0)
        {
          //
          // Revision 0 is the only revision presently defined
          //
          if(LEqual(Arg1, 0x00))
          {
            //
            // Functions 0,1, and 2 are supported
            //
            return(Buffer() {0x07})
          }
          break;
        }
        //
        // Function one returns the Channel Info Package
        //
        case(1)
        {
          //
          // Revision 0 is the only revision presently defined.
          //
          If(LEqual(Arg1, 0x0))
          {
            //
            // Return channel info with alternating names and resistor values.
            //
            Name(PBUF, Package()
            {
              //
              // Power
              // Rail        Resistor
              // Name        Value
              //
              "MAINMEM_CPU", 2, // Channel 1
              "MAINMEM_MEM", 2, // Channel 2
              "SOC_AUX", 2, // Channel 3
              "SOC_MCP", 5 // Channel 4
            })
          return(PBUF)
          }
          break;
        }
        //
        // Function two returns the Channel Count
        //
        case(2)
        {
          //
          // Revision 0 is the only revision presently defined.
          //
          If(LEqual(Arg1, 0x0))
          {
            //
            // Actual count of channels.
            //
            return(Buffer() {0x04})
          }
          break;
        }
      } // switch(Arg2)
      //
      // Return an error (a buffer with a value of zero)
      // if we didn't return anything else above
      //
      return(Buffer() {0x0})
    } // _DSM
  } // PowerMeter Device PA02 Scope End

  //
  // PA03 Device: Defines how the PAC193x is connected to the I2C Controller.
  //
  Device(PA03)
  {
    Name(_HID, "MCHP1930")
    Name(_UID, 2)

    Method(_STA, 0x0, NotSerialized)
    {
      If(POME)
      {
        Return(0xf)
      }
      Return (0x0)
    }

    //
    // Current Resources Settings
    //
    Method(_CRS, 0x0, Serialized)
    {
      Name(RBUF, ResourceTemplate()
      {
        I2CSerialBus(0x11,                  // 7-bit Slave Address
                    ControllerInitiated,    // Slave or master?
                    400000,                 // Connection Speed in hz
                    AddressingMode7Bit,     // 7-bit or 10-bit addressing?
                    "\\_SB.PC00.I2C5",      // I2C Controller to which PAC is connected
                    0,                      // Resource Index
                    ResourceConsumer)       // Consumer or Producer?
      })
      Return(RBUF)
    }

    //
    // _DSM - Device Specific Method
    //
    // This method returns configuration information that tells the driver
    // which devices each line in the PAC193x is wired to monitor.
    // Names of the monitored devices must come from the Microsoft-defined
    // power rail taxonomy.
    //
    // The UUID for the Microchip PAC193x's DSM is {033771E0-1705-47B4-9535-D1BBE14D9A09}.
    // This is unique to the device, and must match what the Windows PAC193x driver expects.
    //
    // Returns:
    //         Either: A Buffer (for Functions 0 and 2, or an error)
    //                 A Package containing EMI resources (rail/resistor pairs)
    //
    // Input Arguments (per _DSM standard):
    //
    //     Arg0: UUID - Function Identifier
    //     Arg1: Integer - Revision
    //     Arg2: Integer - Function Index
    //     Arg3: Package - Parameters (not used in our implementation)
    //
    Function(_DSM, {BuffObj, PkgObj}, {BuffObj, IntObj, IntObj, PkgObj})
    {
      //033771E0-1705-47B4-9535-D1BBE14D9A09
      //  Is our UUID being invoked?
      //
      if(LNotEqual(Arg0, ToUUID("033771E0-1705-47B4-9535-D1BBE14D9A09")))
      {
        //
        // It's NOT our UUID -- Just return a NULL for error
        //
        return(Buffer() {0x0})
      }
      //
      // Switch based on the function number requested...
      //
      switch(ToInteger(Arg2))
      {
        //
        // Function zero returns a bit-mask of supported functions
        //
        case(0)
        {
          //
          // Revision 0 is the only revision presently defined
          //
          if(LEqual(Arg1, 0x00))
          {
            //
            // Functions 0,1, and 2 are supported
            //
            return(Buffer() {0x07})
          }
          break;
        }
        //
        // Function one returns the Channel Info Package
        //
        case(1)
        {
          //
          // Revision 0 is the only revision presently defined.
          //
          If(LEqual(Arg1, 0x0))
          {
            //
            // Return channel info with alternating names and resistor values.
            //
            Name(PBUF, Package()
            {
              //
              // Power
              // Rail        Resistor
              // Name        Value
              //
              "STORAGE",5, // Channel 1
              "WIFI", 5, // Channel 2
              "SYSTEM_POWER", 2, // Channel 3
              "DISPLAY", 10 // Channel 4
            })
            return(PBUF)
          }
          break;
        }
        //
        // Function two returns the Channel Count
        //
        case(2)
        {
          //
          // Revision 0 is the only revision presently defined.
          //
          If(LEqual(Arg1, 0x0))
          {
            //
            // Actual count of channels.
            //
            return(Buffer() {0x04})
          }
          break;
        }
      } // switch(Arg2)
      //
      // Return an error (a buffer with a value of zero)
      // if we didn't return anything else above
      //
      return(Buffer() {0x0})
    } // _DSM
  } // PowerMeter Device PA03 Scope End
} // Scope I2C5
