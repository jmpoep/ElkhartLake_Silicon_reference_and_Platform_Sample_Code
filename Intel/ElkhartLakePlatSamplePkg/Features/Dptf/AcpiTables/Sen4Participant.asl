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

#ifdef EC_SUPPORT
Scope(\_SB.PC00.LPCB.H_EC)
#endif
#ifdef ECLITE_PSE_SUPPORT
Scope(\_SB)
#endif //ECLITE_PSE_SUPPORT
{

  Device(SEN4)
  {
#ifdef ECLITE_PSE_SUPPORT
    Name (_DEP, Package() {\_SB.ECLT})
#endif //ECLITE_PSE_SUPPORT
    Name(_HID, EISAID("INT3403"))  // Intel DPTF Temperature Sensor Device
    Name(_UID, "SEN4")

    Name(_STR, Unicode ("Thermistor Battery Charger")) // Near Battery Charger
    Name(PTYP, 0x03)
    Name(CTYP,0)  // Mode
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
      If (LEqual(\S4DE,1)) {
        Return(0x0F)
      } Else {
        Return(0x00)
      }
    }

    // _TMP (Temperature)
    //
    // This control method returns the thermal zone's current operating temperature.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   An Integer containing the current temperature of the thermal zone (in tenths of degrees Kelvin)
    //
    Method(_TMP,0,Serialized)
    {
#ifdef EC_SUPPORT
      If(\_SB.PC00.LPCB.H_EC.ECAV)
      {
        Return(\_SB.IETM.C10K(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.TSR4))))
      } Else {
        Return(3000)
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
     \_SB.ECLT.ECLC(ECLITE_READ_COMMAND, ECLITE_DEFAULT_UPDATE, ECLITE_S2T1_OFFSET, ECLITE_BYTES_COUNT_2)
     Return(\_SB.IETM.C10K(\_SB.ECLT.ECLR( RefOf (\_SB.ECLT.S2T1))))
#endif //ECLITE_PSE_SUPPORT
    }

    // Number of Aux Trips available
    Name(PATC, 2)

    // PATx (Participant Programmable Auxiliary Trip) - Sets Aux Trip Point
    //
    // The PATx objects shall take a single integer parameter, in tenths of degree Kelvin, which
    // represents the temperature at which the device should notify the participant driver of
    // an auxiliary trip event. A PATx control method returns no value.
    //
    //  Arguments: (1)
    //    Arg0 - temperature in tenths of degree Kelvin
    //  Return Value:
    //    None
    //
    Method(PAT0, 1, Serialized)
    {
#ifdef EC_SUPPORT
      If (\_SB.PC00.LPCB.H_EC.ECAV)
      {
        Store (Acquire(\_SB.PC00.LPCB.H_EC.PATM, 100),Local0)  // Save Acquire result so we can check for Mutex acquired
        If (LEqual(Local0, Zero))  // Check for Mutex acquired
        {
          Store(\_SB.IETM.K10C(Arg0),Local1)
          \_SB.PC00.LPCB.H_EC.ECWT(0x3, RefOf(\_SB.PC00.LPCB.H_EC.TSI)) // Select Thermal Sensor
          \_SB.PC00.LPCB.H_EC.ECWT(0x2, RefOf(\_SB.PC00.LPCB.H_EC.HYST)) // Thermal Sensor Hysteresis, 2 degrees
          \_SB.PC00.LPCB.H_EC.ECWT(Local1, RefOf(\_SB.PC00.LPCB.H_EC.TSLT)) // Sensor Low Trip Point
          \_SB.PC00.LPCB.H_EC.ECMD(0x4A) //Set Trip point.
          Release(\_SB.PC00.LPCB.H_EC.PATM)
        }
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
     Store(\_SB.IETM.K10C(Arg0),Local0)
     \_SB.ECLT.ECLW(Local0, RefOf(\_SB.ECLT.S2A1))
     \_SB.ECLT.ECLC(ECLITE_WRITE_COMMAND, ECLITE_THERMAL_ALERT_THERHSOLD_UPDATE, ECLITE_S2A1_OFFSET, ECLITE_BYTES_COUNT_2)
#endif //ECLITE_PSE_SUPPORT
    }

    // PATx (Participant Programmable Auxiliary Trip) - Sets Aux Trip Point
    //
    // The PATx objects shall take a single integer parameter, in tenths of degree Kelvin, which
    // represents the temperature at which the device should notify the participant driver of
    // an auxiliary trip event. A PATx control method returns no value.
    //
    //  Arguments: (1)
    //    Arg0 - temperature in tenths of degree Kelvin
    //  Return Value:
    //    None
    //
    Method(PAT1, 1, Serialized)
    {
#ifdef EC_SUPPORT
      If (\_SB.PC00.LPCB.H_EC.ECAV)
      {
        Store (Acquire(\_SB.PC00.LPCB.H_EC.PATM, 100),Local0)  // Save Acquire result so we can check for Mutex acquired
        If (LEqual(Local0, Zero))  // Check for Mutex acquired
        {
          Store(\_SB.IETM.K10C(Arg0),Local1)
          \_SB.PC00.LPCB.H_EC.ECWT(0x3, RefOf(\_SB.PC00.LPCB.H_EC.TSI)) // Select Thermal Sensor
          \_SB.PC00.LPCB.H_EC.ECWT(0x2, RefOf(\_SB.PC00.LPCB.H_EC.HYST)) // Thermal Sensor Hysteresis, 2 degrees
          \_SB.PC00.LPCB.H_EC.ECWT(Local1, RefOf(\_SB.PC00.LPCB.H_EC.TSHT)) // Sensor High Trip Point
          \_SB.PC00.LPCB.H_EC.ECMD(0x4A) // Set Trip point.
          Release(\_SB.PC00.LPCB.H_EC.PATM)
        }
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
     Store(\_SB.IETM.K10C(Arg0),Local0)
     \_SB.ECLT.ECLW(Local0, RefOf(\_SB.ECLT.S2A3))
     \_SB.ECLT.ECLC(ECLITE_WRITE_COMMAND, ECLITE_THERMAL_ALERT_THERHSOLD_UPDATE, ECLITE_S2A3_OFFSET, ECLITE_BYTES_COUNT_2)
#endif //ECLITE_PSE_SUPPORT
    }

    // Thermal Sensor Hysteresis, 2 degrees
    Name(GTSH, 20)

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
#ifdef EC_SUPPORT
      Notify(\_SB.PC00.LPCB.H_EC.SEN4, 0x91) // notify the participant of a trip point change event
#endif
#ifdef ECLITE_PSE_SUPPORT
      Notify(\_SB.SEN4, 0x91) // notify the participant of a trip point change event
#endif //ECLITE_PSE_SUPPORT
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
      Return(2782)  // 5 degree Celcius, this could be a platform policy with setup item
    }

    // _TSP (Thermal Sampling Period)
    //
    // Sets the polling interval in 10ths of seconds. A value of 0 tells the driver to use interrupts.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   An Integer containing the polling rate in tenths of seconds.
    //   A value of 0 will specify using interrupts through the ACPI notifications.
    //
    //   The granularity of the sampling period is 0.1 seconds. For example, if the sampling period is 30.0
    //   seconds, then _TSP needs to report 300; if the sampling period is 0.5 seconds, then it will report 5.
    //
    Method(_TSP,0,Serialized)
    {
      Return(\SSP4)
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
    Method(_AC0,0,Serialized)
    {
      If(CTYP)
      {
        If (LEqual(\S4PT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
        Store(\_SB.IETM.CTOK(\S4PT),Local1) // Passive Cooling Policy
      } Else {
        If (LEqual(\S4AT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
        Store(\_SB.IETM.CTOK(\S4AT),Local1) // Active Cooling Policy
      }
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
      If(CTYP)
      {
        If (LEqual(\S2PT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      } Else {
        If (LEqual(\S2AT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      }
      Return(Subtract(_AC0(), 100))
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
      If(CTYP)
      {
        If (LEqual(\S2PT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      } Else {
        If (LEqual(\S2AT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      }
      Return(Subtract(_AC1(), 100))
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
      If(CTYP)
      {
        If (LEqual(\S4AT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
        Return(\_SB.IETM.CTOK(\S4AT)) // Active Cooling Policy
      } Else {
        If (LEqual(\S4PT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
        Return(\_SB.IETM.CTOK(\S4PT)) // Passive Cooling Policy
      }
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
      If (LEqual(\S4CT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      Return(\_SB.IETM.CTOK(\S4CT))
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
      If (LEqual(\S4S3,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      Return(\_SB.IETM.CTOK(\S4S3))
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
      If (LEqual(\S4HT,0)) {Return(0xFFFFFFFF)} // Indicate DPTF driver to disable trip point
      Return(\_SB.IETM.CTOK(\S4HT))
    }

  } // End SEN4 Device
}// end Scope(\_SB.PC00.LPCB.H_EC) or Scope(\_SB)
