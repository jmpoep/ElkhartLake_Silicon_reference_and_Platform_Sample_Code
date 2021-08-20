/** @file
  Intel ACPI Reference Code for Dynamic Platform & Thermal Framework

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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

Scope(\_SB)
{

  Device(VIR2)
  {
    Name(_HID, EISAID("INT3409"))  // Intel DPTF Virtual Sensor Participant Device
    Name(_UID, "VIR2")
    Name(PTYP, 0x15) // TypeVirtualSensor
    Name(_STR, Unicode ("Virtual Sensor 2"))
    // PFLG
    //   0 - Default, participant is on the main board
    //   1 - Participant device is on the docking station
    //   2 - Participant device is on the detachable base
    //   3 - Participant device is an external device (such as a USB device, DPTF does not support this type of device today)
    Name(PFLG, 0)

    // _STA (Status)
    //
    // This object returns the current status of a device.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   An Integer containing a device status bitmap:
    //    Bit 0 - Set if the device is present.
    //    Bit 1 - Set if the device is enabled and decoding its resources.
    //    Bit 2 - Set if the device should be shown in the UI.
    //    Bit 3 - Set if the device is functioning properly (cleared if device failed its diagnostics).
    //    Bit 4 - Set if the battery is present.
    //    Bits 5-31 - Reserved (must be cleared).
    //
    Method(_STA)
    {
      If (LEqual(VSP2,1)){
        Return(0x0F)
      } Else {
        Return(0x00)
      }
    }

    // Returns Number of Aux Trips available
    Name(PATC, 0)

    Name(LSTM,0)  // Last temperature reported

    // _DTI (Device Temperature Indication)
    //
    // Conveys the temperature of a device's internal temperature sensor to the platform when a temperature trip point
    // is crossed or when a meaningful temperature change occurs.
    //
    // Arguments: (1)
    //   Arg0 - An Integer containing the current value of the temperature sensor (in tenths Kelvin)
    // Return Value:
    //   None
    //
    Method(_DTI, 1)
    {
      Store(Arg0,LSTM)
      Notify(\_SB.VIR2, 0x91) // notify the participant of a trip point change event
    }

    // _NTT (Notification Temperature Threshold)
    //
    // Returns the temperature change threshold for devices containing native temperature sensors to cause
    // evaluation of the _DTI object
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   An Integer containing the temperature threshold in tenths of degrees Kelvin.
    //
    Method(_NTT, 0)
    {
      Return(2782)  // 5 degree Celcius
    }

    // VSCT (Virtual Sensor Calibration Table)
    //
    // Provides parameters for virtual temperature sensor calculation.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Package of VSCT packages
    //
    // Name (VSCT, Package())
    // {
    //   Revision,           // DWordConst
    //   Package ()
    //   {
    //     target,          // DeviceReference,
    //     domain,          // DwordConst,  Enumerated domain type.
    //     coefficientType, // DwordConst,  Enumerated co-efficient type, 0=TEMPERATURE, 1=POWER, 2=CONSTANT
    //     coefficient      // DwordConst,  Co-efficient to be used by virtual temperature sensor policy.
    //     operation        // DwordConst,  Enumerated operation, 0 = Addition (+), 1 = Subtraction (-)
    //     alpha,           // DwordConst,  Gain in .01 increments so 1 would be represented by 100.
    //     triggerPoint     // DwordConst,  Indicates what temperature VTS calculation should be performed. Unit is .1 Kelvin.
    //   }
    // }) // End of VSCT object
    //
    Name (VSCT, Package()
    {
      1,
      Package()
      {
#ifdef EC_SUPPORT
        Package () {\_SB.PC00.LPCB.H_EC.SEN3,14,0,500,0,200,2932},
        Package () {\_SB.PC00.LPCB.H_EC.SEN4,14,0,500,0,300,2932}
#endif
#ifdef ECLITE_PSE_SUPPORT
        Package () {\_SB.SEN3,14,0,500,0,200,2932},
        Package () {\_SB.SEN4,14,0,500,0,300,2932}
#endif //ECLITE_PSE_SUPPORT
      }
    })

    // VSPT (Virtual Sensor Polling Table)
    //
    // Used to provide polling intervals for target temperature.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Package of VSPT packages
    //
    // Name (VSPT, Package()
    // {
    //   Revision,           // DWordConst
    //   Package ()
    //   {
    //     virtualTemp,      // DwordConst, Virtual Temperature in .1 Kelvin.
    //     pollingPeriod     // DwordConst, Period of polling period in .1 Second.
    //   }
    // }) // End of VSPT object
    //
    Name (VSPT, Package()
    {
      1,
      Package()
      {
        Package () {3031,300},
        Package () {3131,100},
        Package () {3231,10}
      }
    })

    // _ACx (Active Cooling)
    //
    // This optional object, if present under a thermal zone, returns the
    //  temperature trip point at which OSPM must start or stop Active cooling,
    //  where x is a value between 0 and 9 that designates multiple active cooling levels of the thermal zone.
    //
    //  Arguments: (0)
    //    None
    //  Return Value:
    //    An Integer containing the active cooling temperature threshold in tenths of degrees Kelvin
    //
    Method(_AC0,0,Serialized)
    {
      If (LEqual(\V2AT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      Store(\_SB.IETM.CTOK(\V2AT),Local1)
      If(LGreaterEqual(LSTM,Local1))
      {
        Return(Subtract(Local1,20)) // subtract 2 degrees which is the Hysteresis
      }
      Else
      {
        Return(Local1)
      }
    }

    // _ACx (Active Cooling)
    //
    // This optional object, if present under a thermal zone, returns the
    //  temperature trip point at which OSPM must start or stop Active cooling,
    //  where x is a value between 0 and 9 that designates multiple active cooling levels of the thermal zone.
    //
    //  Arguments: (0)
    //    None
    //  Return Value:
    //    An Integer containing the active cooling temperature threshold in tenths of degrees Kelvin
    //
    Method(_AC1,0,Serialized)
    {
      If (LEqual(\V1AT,0)) {Return(0xFFFFFFFF)} // Indicate Intel(R) Dynamic Tuning driver to disable trip point
      Return(Subtract(_AC0(), 30))
    }

    // _ACx (Active Cooling)
    //
    // This optional object, if present under a thermal zone, returns the
    //  temperature trip point at which OSPM must start or stop Active cooling,
    //  where x is a value between 0 and 9 that designates multiple active cooling levels of the thermal zone.
    //
    //  Arguments: (0)
    //    None
    //  Return Value:
    //    An Integer containing the active cooling temperature threshold in tenths of degrees Kelvin
    //
    Method(_AC2,0,Serialized)
    {
      If (LEqual(\V1AT,0)) {Return(0xFFFFFFFF)} // Indicate Intel(R) Dynamic Tuning driver to disable trip point
      Return(Subtract(_AC1(), 30))
    }

    // _PSV (Passive)
    //
    // This optional object, if present under a thermal zone, evaluates to the temperature
    //  at which OSPM must activate passive cooling policy.
    //
    //  Arguments: (0)
    //    None
    //  Return Value:
    //    An Integer containing the passive cooling temperature threshold in tenths of degrees Kelvin
    //
    Method(_PSV,0,Serialized)
    {
      If (LEqual(\V2PV,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      Return(\_SB.IETM.CTOK(\V2PV))
    }

    // _CRT (Critical Temperature)
    //
    // This object, when defined under a thermal zone, returns the critical temperature at which OSPM must shutdown the system.
    //
    //  Arguments: (0)
    //    None
    //  Return Value:
    //    An Integer containing the critical temperature threshold in tenths of degrees Kelvin
    //
    Method(_CRT,0,Serialized)
    {
      If (LEqual(\V2CR,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      Return(\_SB.IETM.CTOK(\V2CR))
    }

    // _CR3 (Critical Temperature for S3/CS)
    //
    // This object, when defined under a thermal zone, returns the critical temperature at which OSPM
    // must transition to Standby or Connected Standy.
    //
    //  Arguments: (0)
    //    None
    //  Return Value:
    //    An Integer containing the critical temperature threshold in tenths of degrees Kelvin
    //
    Method(_CR3,0,Serialized)
    {
      If (LEqual(\V2C3,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      Return(\_SB.IETM.CTOK(\V2C3))
    }

    // _HOT (Hot Temperature)
    //
    // This optional object, when defined under a thermal zone, returns the critical temperature
    //  at which OSPM may choose to transition the system into the S4 sleeping state.
    //
    //  Arguments: (0)
    //    None
    //  Return Value:
    //    The return value is an integer that represents the critical sleep threshold tenths of degrees Kelvin.
    //
    Method(_HOT,0,Serialized)
    {
      If (LEqual(\V2HT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      Return(\_SB.IETM.CTOK(\V2HT))
    }

  } // End VIR2 Device
}// end Scope(\_SB)
