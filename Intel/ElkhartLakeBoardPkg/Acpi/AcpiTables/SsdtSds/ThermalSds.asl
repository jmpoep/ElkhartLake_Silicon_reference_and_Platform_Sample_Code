/** @file
  ACPI DSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

//
// Defined as an SSDT to be able to dynamically load based on BIOS
// setup options
//
DefinitionBlock (
  "ThermalSds.aml",
  "SSDT",
  0x02,
  "TherSd",
  "Ther_Sds",
  0x1000
  )
{

External(\_SB.APSV)
External(\_SB.ACRT)
External(\_SB.AAC0)
External(\_SB.DTSE)
External(\_SB.PKGA)
External(\_SB.PDTS)
External(\_SB.DTS1)
External(\_SB.DTS2)
External(\_SB.DTS3)
External(\_SB.DTS4)
External(\_SB.PR00)
External(\_SB.PR01)
External(\_SB.PR02)
External(\_SB.PR03)
External(\_SB.PR04)
External(\_SB.PR05)
External(\_SB.PR06)
External(\_SB.PR07)
External(\_SB.PR08)
External(\_SB.PR09)
External(\_SB.PR10)
External(\_SB.PR11)
External(\_SB.PR12)
External(\_SB.PR13)
External(\_SB.PR14)
External(\_SB.PR15)

External(\CTYP, IntObj)
External(\TCNT, IntObj)
External(\VFN0, IntObj)
External(\VFN1, IntObj)
External(\VFN2, IntObj)
External(\VFN3, IntObj)
External(\VFN4, IntObj)
External(\ECON, IntObj)
External(\AC0F, IntObj)
External(\AC1F, IntObj)
External(\CRTT, IntObj)
External(\PSVT, IntObj)
External(\ACTT, IntObj)
External(\ACT1, IntObj)
External(\TC1V, IntObj)
External(\TC2V, IntObj)
External(\TSPV, IntObj)

#ifdef EC_SUPPORT
External(\_SB.PC00.LPCB.H_EC.ECRD, MethodObj)
External(\_SB.PC00.LPCB.H_EC.ECWT, MethodObj)
External(\_SB.PC00.LPCB.H_EC.ECMD, MethodObj)
External(\_SB.PC00.LPCB.H_EC.PENV, FieldUnitObj)
External(\_SB.PC00.LPCB.H_EC.PLMX, FieldUnitObj)
External(\_SB.PC00.LPCB.H_EC.PPSL, FieldUnitObj)
External(\_SB.PC00.LPCB.H_EC.PPSH, FieldUnitObj)
External(\_SB.PC00.LPCB.H_EC.PSTP, FieldUnitObj)
#endif

// THERMAL.ASL represents a Thermal Zone to be used for testing on the
// Customer Reference Boards.
Scope(\_TZ)
{

  // Notes:
  //   1) WIN2K strictly uses interrupt driven thermal events.
  //   2) Temperature values are stored in tenths of Kelvin to
  //      eliminate the decimal place.
  //   3) Kelvin = Celsius + 273.2.
  //   4) All temperature must be >= 289K.

  Name(ETMD, 1)

  // Temperature Threshold in Celsius, used to guard against hardware returning bad temperature readings
  Name(THLD, 120)

  //
  // WBAC --  _ACx Thermal Trip Points for Wilson Beach platform
  //
  // Matrix of Thermal Trip points & Fan Control (Wilson Beach Platform)
  //
  Name(WBAC, Package() {
   Package() { 85,  75,  65,  55}, // _ACx trip point temperature (T deg C)
   Package() { 10,  10,  10,   5}, // _ACx SW Hysteresis Delta (T deg C)
   Package() {100,  80,  60,  30}, // Corresponding Fan Speeds (% PWM)
   Package() {110, 108, 106, 104}  // DPTF Enabled Trip Point Values (T deg C)
  })

  Method(FCTL, 1, Serialized)
  {
#ifdef EC_SUPPORT
    \_SB.PC00.LPCB.H_EC.ECWT(1, RefOf(\_SB.PC00.LPCB.H_EC.PPSL))    // Fan 1
    \_SB.PC00.LPCB.H_EC.ECWT(0, RefOf(\_SB.PC00.LPCB.H_EC.PPSH))    //
    \_SB.PC00.LPCB.H_EC.ECWT(Arg0, RefOf(\_SB.PC00.LPCB.H_EC.PENV)) // percent on
    \_SB.PC00.LPCB.H_EC.ECWT(100, RefOf(\_SB.PC00.LPCB.H_EC.PSTP))  //
    \_SB.PC00.LPCB.H_EC.ECMD(0x1a)       // Command to turn the fan on
#endif
    Notify(\_TZ.TZ00, 0x81)  // Generate a Trip points change notification so that the trip points can be re-evaluated.
  }

  // Fan 0 = Package Processor Fan - Maximum speed
  PowerResource(FN00, 0, 0)
  {
    Method(_STA, 0, Serialized)
    {
        // Return Virtual Fan 0 status.
        Return(\VFN0)
    }

    Method(_ON, 0, Serialized)
    {
        // Set Virtual Fan 0 On.
        Store(1,\VFN0)

        // Turn on the CPU Fan if EC access is enabled.
#ifdef EC_SUPPORT
        If(LAnd(\ECON, ETMD))
        {
          // Turn on Fan at Speed 0
          Store(DeRefOf(Index(DeRefOf(Index(WBAC, 2)), 0)), Local1)
          \_TZ.FCTL(Local1)
        }
#endif
    }

    Method(_OFF, 0, Serialized)
    {
       // Set Virtual Fan 0 Off.
       Store(0,\VFN0)
       // Turn on the CPU Fan if EC access is enabled.
#ifdef EC_SUPPORT
       If(LAnd(\ECON, ETMD))
       {
         // Turn on Fan at Speed 1
         Store(DeRefOf(Index(DeRefOf(Index(WBAC, 2)), 1)), Local1)
         \_TZ.FCTL(Local1)
       }
#endif
    }
  }

  // Associate Virtual Fan 0 Power Resource with the FAN0 Device.
  Device(FAN0)
  {
    Name(_HID, EISAID("PNP0C0B"))
    Name(_UID,0)
    Name(_PR0, Package(1){FN00})
    Name(_FST, Package() {0, 0, 0xffffffff})
  }

  // Fan 1 = Package Processor Fan.
  PowerResource(FN01,0,0)
  {
    Method(_STA,0,Serialized)
    {
        // Return Virtual Fan 1 status.
        Return(\VFN1)
    }

    Method(_ON,0,Serialized)
    {
        // Set Virtual Fan 1 On.
        Store(1,\VFN1)
        // Turn on the CPU Fan if EC access is enabled.
#ifdef EC_SUPPORT
        If(LAnd(\ECON, ETMD))
        {
          // Turn on Fan at Speed 1
          Store(DeRefOf(Index(DeRefOf(Index(WBAC, 2)), 1)), Local1)
          \_TZ.FCTL(Local1)
        }
#endif
    }

    Method(_OFF,0,Serialized)
    {
        // Set Virtual Fan 1 Off.
        Store(0,\VFN1)

        // Turn on the CPU Fan if EC access is enabled.
#ifdef EC_SUPPORT
        If(LAnd(\ECON, ETMD))
        {
          // Turn on Fan at Speed 2
          Store(DeRefOf(Index(DeRefOf(Index(WBAC, 2)), 2)), Local1)
          \_TZ.FCTL(Local1)
        }
#endif
    }
  }

  // Associate Virtual Fan 1 Power Resource with the FAN1 Device.
  Device(FAN1)
  {
    Name(_HID, EISAID("PNP0C0B"))
    Name(_UID, 1)
    Name(_PR0, Package(1){FN01})
  }

  // Fan 2 = Package Processor Fan.
  PowerResource(FN02,0,0)
  {
    Method(_STA,0,Serialized)
    {
        // Return Virtual Fan 2 status.
        Return(\VFN2)
    }

    Method(_ON,0,Serialized)
    {
        // Set Virtual Fan 2 On.
        Store(1,\VFN2)

        // Turn on the CPU Fan if EC access is enabled.
#ifdef EC_SUPPORT
        If(LAnd(\ECON, ETMD))
        {
          // Turn on Fan at Speed 2
          Store(DeRefOf(Index(DeRefOf(Index(WBAC, 2)), 2)), Local1)
          \_TZ.FCTL(Local1)
        }
#endif
    }

    Method(_OFF,0,Serialized)
    {
        // Set Virtual Fan 2 Off.
        Store(0,\VFN2)
        // Turn on the CPU Fan if EC access is enabled.
#ifdef EC_SUPPORT
        If(LAnd(\ECON, ETMD))
        {
          // Turn on Fan at Speed 3
          Store(DeRefOf(Index(DeRefOf(Index(WBAC, 2)), 3)), Local1)
          \_TZ.FCTL(Local1)
        }
#endif
    }
  }

  // Associate Virtual Fan 2 Power Resource with the FAN0 Device.
  Device(FAN2)
  {
    Name(_HID, EISAID("PNP0C0B"))
    Name(_UID, 2)
    Name(_PR0, Package(1){FN02})
  }

  // Fan 3 = Package Processor Fan.
  PowerResource(FN03,0,0)
  {
    Method(_STA,0,Serialized)
    {
        // Return Virtual Fan 3 status.
        Return(\VFN3)
    }

    Method(_ON,0,Serialized)
    {
        // Set Virtual Fan 3 On.
        Store(1,\VFN3)
        // Turn on the CPU Fan if EC access is enabled.
#ifdef EC_SUPPORT
        If(LAnd(\ECON, ETMD))
        {
          // Turn on Fan at Speed 3
          Store(DeRefOf(Index(DeRefOf(Index(WBAC, 2)), 3)), Local1)
          \_TZ.FCTL(Local1)
        }
#endif
    }

    Method(_OFF,0,Serialized)
    {
        // Set Virtual Fan 3 Off.
        Store(0,\VFN3)
                // Turn on the CPU Fan if EC access is enabled.
#ifdef EC_SUPPORT
        If(LAnd(\ECON, ETMD))
        {
            \_TZ.FCTL(0)  // Turn Fan Off
        }
#endif
    }
  }

  // Associate Virtual Fan 3 Power Resource with the FAN0 Device.
  Device(FAN3)
  {
    Name(_HID, EISAID("PNP0C0B"))
    Name(_UID, 3)
    Name(_PR0, Package(1){FN03})
  }

  // Thermal Zone 0 = Package Thermal Zone.
  // Package Thermal Zone is used for Active and Critical Policy Control
  // Package Thermal Zone returns the maximum temperature
  // of all components within the package
  ThermalZone(TZ00)
  {
    // Temporary variable for holding the current temperature reading
    Name(PTMP,3000)

    // Notifies ASL Code the current cooling mode.
    //   0 - Active cooling
    //   1 - Passive cooling
    Method(_SCP, 1, Serialized)
    {
        Store(Arg0, CTYP)
    }

    // Return the temperature at which the OS performs Critical Shutdown
    Method(_CRT, 0, Serialized)
    {
        // Returns automatic thermal reporting temperature for CPU throttling if available and valid.
        If(CondRefOf(\_SB.ACRT))
        {
            If(LNotEqual(\_SB.ACRT,0))
            {
                Return(Add(2732, Multiply(\_SB.ACRT, 10)))
            }
        }
        Return(Add(2732, Multiply(\CRTT, 10)))
    }

    // Return the temperature(s) at which the OS initiates Active Cooling.
    Method(_AC0, 0, Serialized)
    {
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 0)), 0)), Local1)  // Store _ACx Value
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 1)), 0)), Local2)  // Store _ACx Hysteresis Delta
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 3)), 0)), Local3)  // Store _ACx Value to return when DPTF is enabled

      If (LEqual(ETMD, 0))
      {
        Store(Local3, Local4)  // Return Dummy high value if DPTF is enabled
      }
      Else
      {
        If(LEqual(\VFN0, 1))
        {
          Subtract(Local1, Local2, Local4)  // If Fan is already on, then subtract Hysteresis
        }
        Else
        {
          Store(Local1, Local4)  // If Fan is not on at this level, then return original _ACx value
        }
      }
      Return(Add(2732, Multiply(Local4, 10)))  // Return _ACx value to OSPM
    }

    Method(_AC1, 0, Serialized)
    {
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 0)), 1)), Local1)  // Store _ACx Value
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 1)), 1)), Local2)  // Store _ACx Hysteresis Delta
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 3)), 1)), Local3)  // Store _ACx Value to return when DPTF is enabled

      If (LEqual(ETMD, 0))
      {
        Store(Local3, Local4)  // Return Dummy high value if DPTF is enabled
      }
      Else
      {
        If(LEqual(\VFN1, 1))
        {
          Subtract(Local1, Local2, Local4)  // If Fan is already on, then subtract Hysteresis
        }
        Else
        {
          Store(Local1, Local4)  // If Fan is not on at this level, then return original _ACx value
        }
      }
      Return(Add(2732, Multiply(Local4, 10)))  // Return _ACx value to OSPM
    }

    Method(_AC2, 0, Serialized)
    {
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 0)), 2)), Local1)  // Store _ACx Value
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 1)), 2)), Local2)  // Store _ACx Hysteresis Delta
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 3)), 2)), Local3)  // Store _ACx Value to return when DPTF is enabled

      If (LEqual(ETMD, 0))
      {
        Store(Local3, Local4)  // Return Dummy high value if DPTF is enabled
      }
      Else
      {
        If(LEqual(\VFN2, 1))
        {
          Subtract(Local1, Local2, Local4)  // If Fan is already on, then subtract Hysteresis
        }
        Else
        {
          Store(Local1, Local4)  // If Fan is not on at this level, then return original _ACx value
        }
      }
      Return(Add(2732, Multiply(Local4, 10)))  // Return _ACx value to OSPM
    }

    Method(_AC3, 0, Serialized)
    {
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 0)), 3)), Local1)  // Store _ACx Value
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 1)), 3)), Local2)  // Store _ACx Hysteresis Delta
      Store(DeRefOf(Index(DeRefOf(Index(WBAC, 3)), 3)), Local3)  // Store _ACx Value to return when DPTF is enabled

      If (LEqual(ETMD, 0))
      {
        Store(Local3, Local4)  // Return Dummy high value if DPTF is enabled
      }
      Else
      {
        If(LEqual(\VFN3, 1))
        {
          Subtract(Local1, Local2, Local4)  // If Fan is already on, then subtract Hysteresis
        }
        Else
        {
          Store(Local1, Local4)  // If Fan is not on at this level, then return original _ACx value
        }
      }
      Return(Add(2732, Multiply(Local4, 10)))  // Return _ACx value to OSPM
    }


    // Return the device(s) to turn on when _ACx is exceeded.
    Name(_AL0, Package(1){FAN0})
    Name(_AL1, Package(1){FAN1})
    Name(_AL2, Package(1){FAN2})
    Name(_AL3, Package(1){FAN3})


    // Return the Package Temperature.
    //    Source 1: CPU DTS temperature
    //    Source 2: Max Platform temperature returned by EC
    Method(_TMP, 0, Serialized)
    {
        If(CondRefOf(\_SB.DTSE)){
          If (LEqual(\_SB.DTSE, 0x3)) //Out Of Spec Condition occurred. Return critical temperature for OS shutdown
          {
              Return(Add(2832,Multiply(\CRTT,10)))
          }
        }

        // Max Platform temperature returned by EC if EC enabled/available
#ifdef EC_SUPPORT
        If(\ECON)
        {
          // Store current reading in temporary variable
          Store(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.PLMX)), Local0) // Max Platform temperature
          Add(2732, Multiply(Local0, 10), Local0)
          Store(Local0, PTMP)
          Return(Local0)
        }
#endif
        // Return a static value if no source is available.
        Return(3010)
    }

    // Return the Processor(s) used for Passive Cooling.
    Method(_PSL, 0, Serialized)
    {
        If(LEqual(\TCNT, 16))
        {
            //  CMP - Throttling controls 16 logical CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01,\_SB.PR02,\_SB.PR03,\_SB.PR04,\_SB.PR05,\_SB.PR06,\_SB.PR07,\_SB.PR08,\_SB.PR09,\_SB.PR10,\_SB.PR11,\_SB.PR12,\_SB.PR13,\_SB.PR14,\_SB.PR15})
        }

        If(LEqual(\TCNT, 14))
        {
            //  CMP - Throttling controls 14 logical CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01,\_SB.PR02,\_SB.PR03,\_SB.PR04,\_SB.PR05,\_SB.PR06,\_SB.PR07,\_SB.PR08,\_SB.PR09,\_SB.PR10,\_SB.PR11,\_SB.PR12,\_SB.PR13})
        }

        If(LEqual(\TCNT, 12))
        {
            //  CMP - Throttling controls 12 logical CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01,\_SB.PR02,\_SB.PR03,\_SB.PR04,\_SB.PR05,\_SB.PR06,\_SB.PR07,\_SB.PR08,\_SB.PR09,\_SB.PR10,\_SB.PR11})
        }

        If(LEqual(\TCNT, 10))
        {
            //  CMP - Throttling controls 10 logical CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01,\_SB.PR02,\_SB.PR03,\_SB.PR04,\_SB.PR05,\_SB.PR06,\_SB.PR07,\_SB.PR08,\_SB.PR09})
        }


        If(LEqual(\TCNT, 8))
        {
            //  CMP - Throttling controls 8 logical CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01,\_SB.PR02,\_SB.PR03,\_SB.PR04,\_SB.PR05,\_SB.PR06,\_SB.PR07})
        }

        If(LEqual(\TCNT, 7))
        {
            //  CMP - Throttling controls 7 logical CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01,\_SB.PR02,\_SB.PR03,\_SB.PR04,\_SB.PR05,\_SB.PR06})
        }

        If(LEqual(\TCNT, 6))
        {
            //  CMP - Throttling controls 6 logical CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01,\_SB.PR02,\_SB.PR03,\_SB.PR04,\_SB.PR05})
        }

        If(LEqual(\TCNT, 5))
        {
            //  CMP - Throttling controls 5 logical CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01,\_SB.PR02,\_SB.PR03,\_SB.PR04})
        }


        If(LEqual(\TCNT, 4))
        {
            //  CMP - Throttling controls 4 logical CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01,\_SB.PR02,\_SB.PR03})
        }

        If(LEqual(\TCNT, 3))
        {
            //  CMP - Throttling controls 3 logical CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01,\_SB.PR02})
        }

        If(LEqual(\TCNT, 2))
        {
            //  CMP - Throttling controls 2 CPUs.
            Return(Package(){\_SB.PR00,\_SB.PR01})
        }

        Return(Package(){\_SB.PR00})
    }

    // Returns the temperature at which the OS initiates CPU throttling.
    Method(_PSV, 0, Serialized)
    {
        // Returns automatic thermal reporting temperature for CPU throttling if available and valid.
        If(CondRefOf(\_SB.APSV))
        {
            If(LNotEqual(\_SB.APSV,0))
            {
                Return(Add(2732, Multiply(\_SB.APSV, 10)))
            }
        }
        Return(Add(2732, Multiply(\PSVT, 10)))
    }

    // Returns TC1 value used in the passive cooling formula.
    Method(_TC1, 0, Serialized)
    {
        Return(\TC1V)
    }

    // Returns TC2 value used in the passive cooling formula.
    Method(_TC2, 0, Serialized)
    {
        Return(\TC2V)
    }

    // Returns the sampling period used in the passive cooling formula.
    Method(_TSP, 0, Serialized)
    {
        Return(\TSPV)
    }
  }
} // end Scope(\_TZ)

} // end Definition block
