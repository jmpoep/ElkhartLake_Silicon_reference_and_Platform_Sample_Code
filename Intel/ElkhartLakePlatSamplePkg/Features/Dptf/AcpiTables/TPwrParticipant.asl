/** @file
  Intel ACPI Reference Code for Dynamic Platform & Thermal Framework

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
External (\_SB.PC00.LPCB.H_EC.PBOK, FieldUnitObj)
#endif

Scope(\_SB)
{

  Device(TPWR)  // Power participant
  {
    Name(_HID, EISAID("INT3407")) //Intel DPTF platform power device
    Name(_UID, "TPWR")
    Name(_STR, Unicode ("Platform Power"))
    Name(PTYP, 0x11)
    // PFLG
    //   0 - Default, participant is on the main board
    //   1 - Participant device is on the docking station
    //   2 - Participant device is on the detachable base
    //   3 - Participant device is an external device (such as a USB device, DPTF does not support this type of device today)
    Name(PFLG, 0)
#ifdef ECLITE_PSE_SUPPORT
     //
     // Power participant device should be loaded only after EcLite driver/device is available
     //
     Name (_DEP, Package() {\_SB.ECLT})

#endif //ECLITE_PSE_SUPPORT

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
      If(LEqual(\PWRE,1)) {
        Return(0x0F)
      } Else {
        Return(0x00)
      }
    }

    // _BST (Battery Status)
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   A Package containing the battery status in the format below:
    //   Package {
    //      Battery State
    //      Battery Present Rate
    //      Battery Remaining Capacity
    //      Battery Present Voltage
    //   }
    //
    Method(_BST,,,,PkgObj)
    {
#ifdef EC_SUPPORT
      If(CondRefOf(\_SB.PC00.LPCB.H_EC.BAT1._BST))
      {
        Return(\_SB.PC00.LPCB.H_EC.BAT1._BST())
      } Else {
        Return(Package(){0,0,0,0})
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
     // @todo [EcLite] DPTF relies on OS to provide battery level. Confirm whether it is needed or not
     If(CondRefOf(\_SB.BAT1._BST))
      {
        Return(\_SB.BAT1._BST())
      } Else {
        Return(Package(){0,0,0,0})
      }
#endif ECLITE_PSE_SUPPORT
    }

    // _BIX (Battery Information Extended)
    //
    // The _BIX object returns the static portion of the Control Method Battery information.
    // This information remains constant until the battery is changed.
    // The _BIX object returns all information available via the _BIF object plus additional battery information.
    // The _BIF object is deprecated in lieu of _BIX in ACPI 4.0.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   A Package containing the battery information as described below
    //   Package {
    //      Revision
    //      Power Unit
    //      Design Capacity
    //      Last Full Charge Capacity
    //      Battery Technology
    //      Design Voltage
    //      Design Capacity of Warning
    //      Design Capacity of Low
    //      Cycle Count
    //      Measurement Accuracy
    //      Max Sampling Time
    //      Min Sampling Time
    //      Max Averaging Interval
    //      Min Averaging Interval
    //      Battery Capacity Granularity 1
    //      Battery Capacity Granularity 2
    //      Model Number
    //      Serial Number
    //      Battery Type
    //      OEM Information
    //   }
    //
    Method(_BIX,,,,PkgObj)
    {
#ifdef EC_SUPPORT
      If(CondRefOf(\_SB.PC00.LPCB.H_EC.BAT1._BIX))
      {
        Return(\_SB.PC00.LPCB.H_EC.BAT1._BIX())
      } Else {
        Return(Package(){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"0","0","0","0",0})
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      // @todo [EcLite] DPTF relies on OS to provide battery level. Confirm whether it is needed or not
      If(CondRefOf(\_SB.BAT1._BIX))
      {
        Return(\_SB.BAT1._BIX())
      } Else {
        Return(Package(){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"0","0","0","0",0})
      }
#endif //ECLITE_PSE_SUPPORT
    }

#ifdef EC_SUPPORT
    // PSOC (Platform State of Charge)
    //
    // This object evaluates to the remaining battery state of charge in %.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   remaining battery charge in %
    //
    Method(PSOC)
    {
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,0)) // check EC opregion available
      {
        Return (0) // EC not available
      }
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.B1FC)),0)) // prevent divide by zero
      {
        Return (0) // Full charge cannot be 0, indicate malfunction in battery
      }
      If(LGreater(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.B1RC)),\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.B1FC)))) // remaining charge > full charge
      {
        Return(0) // Remaining Charge cannot be greater than Full Charge, this illegal value indicates the battery is malfunctioning
      }
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.B1RC)),\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.B1FC)))) // remaining charge == full charge
      {
        Return(100) // indicate battery is fully charged
      }
      If(LLess(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.B1RC)),\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.B1FC)))) // (RC*100)/FC=percent
      {
        Multiply(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.B1RC)),100,Local0) // RC*100
        Divide(Local0,\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.B1FC)),Local2,Local1) // divide by FC
        Divide(Local2,100,,Local2) // account for the remainder in percent
        Divide(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.B1FC)),200,,Local3) // what number is 0.5%?
        If(LGreaterEqual(Local2,Local3)){ // round up if the remainder is equal or above .5
          Add(Local1,1,Local1)
        }
        Return(Local1) // current charge in percent
      } Else {
        Return (0) // avoid compiler warning
      }
    }
#endif

#ifdef EC_SUPPORT
    // NPWR (N PoWeR)
    //
    // True Platform Power: Could be AC supplied+Battery Pack supplied power or AC supplied.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Power required to charge battery in mW.
    //
    Method(NPWR)
    {
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.NPWR)
      } Else {
       Return(20000) // 20 watts
      }
    }
#endif //EC_SUPPORT

    // PSRC (Power SouRCe)
    //
    // The PSRC object provides power source type.
    //
    // Arguments: (0)
    //   None
    // Return Value:(enumeration which DPTF driver expects)
    //   Bit[3:0] = Power Resource Type
    //   0x00 = DC
    //   0x01 = AC
    //   0x02 = USB
    //   Bit[7:4] = Power Delivery State Change Sequence Number
    //
    // Notes: (Bitmap from EC)
    // PwrSrcType Bit[0] = 0 <DC>, Bit[0] = 1 <AC>, Bit[1] = 1 <USB-PD>, Bit[2] = 1 <Wireless Charging>
    // Bit[7:4]  = Power Delivery State Change Sequence Number

    Method (PSRC, 0, Serialized)
    {
     ADBG ("PSRC")
     Store(0, Local0)
     Store(0, Local1)
#ifdef EC_SUPPORT
     If (LEqual(\_SB.PC00.LPCB.H_EC.ECAV,0))
      {
        ADBG ("ECAV 0")
        Return(0) // EC not available, default to battery
      } Else {
        Store (\_SB.PC00.LPCB.H_EC.ECRD (RefOf(\_SB.PC00.LPCB.H_EC.PWRT)),Local0)
        And (Local0, 0xF0, Local1) // Keep Bit[7:4], clear Bit[3:0] in Local1
      }

        Switch (ToInteger(And(ToInteger(Local0),0x07))) // Switch Power Source Type Bits [3:0]
        {
          Case (0x0) { // Power source is DC
            ADBG ("DC")
            Or (Local1, 0x00, Local1)
          }
          Case (0x1) { // Power source is AC
            ADBG ( "AC")
            Or (Local1, 0x01, Local1)
          }
          Case (0x2) { // Power source is USB-PD
            ADBG ("PD")
            Or (Local1, 0x02, Local1)
          }
          Default {
            ADBG ("Default DC")
            Or (Local1, 0x00, Local1) //default to battery
          }
        } // end of switch case check
#endif
#ifdef ECLITE_PSE_SUPPORT
      // @todo [EcLite] Check with ISH FW team on the values for different power sources [LKF supports only Type C charger and Battery]
      \_SB.ECLT.ECLC(ECLITE_READ_COMMAND, ECLITE_DEFAULT_UPDATE, ECLITE_PSRC_OFFSET, ECLITE_BYTES_COUNT_1)
      Store(\_SB.ECLT.ECLR(RefOf(\_SB.ECLT.PSRC)), Local0)
      And (Local0, 0xF0, Local1) // Keep Bit[7:4], clear Bit[3:0] in Local1
      Switch(ToInteger(And(ToInteger(Local0),0x07)))
      {
        Case(0x0)
        { // Power source is DC
          ADBG("DC")
          Or (Local1, 0x00, Local1)
        }
        Case(0x1)
        { // Power source is AC
          ADBG("AC")
          Or (Local1, 0x01, Local1)
        }
        Case(0x2)
        { // Power source is USB-PD
          ADBG("PD")
          Or (Local1, 0x02, Local1)
        }
        Default
        {
          ADBG("Default")
          Or (Local1, 0x00, Local1) //default to battery
        }
      }
#endif //ECLITE_PSE_SUPPORT
      Return(Local1)
    }

    // ARTG (Adapter RaTinG)
    //
    // The ARTG object provides AC adapter rating in mW.
    // ARTG should return 0 if PSRC is DC (0).
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   AC adapter rating in mW
    //
    Method(ARTG)
    {
      If(LEqual(PSRC(),1))
      {
#ifdef EC_SUPPORT
        If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
        {
          Return(\_SB.PC00.LPCB.H_EC.ARTG)
        } Else {
          Return(90000) // 90 watts
        }
#endif

#ifdef ECLITE_PSE_SUPPORT
        Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
      } Else {
        Return(0)
      }
    }

#ifdef EC_SUPPORT
    // LSOC (Long term SoC)
    //
    // Long term battery charge is based on c/20 SoC. Every vendor has a different terminology.
    // This is the value predicted by the FG based on light/no load, in %.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Long term battery charge in %.
    //
    Method(LSOC)
    {
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.LSOC)
      } Else {
        Return(50) // 50%
      }
    }
#endif //EC_SUPPORT

    // PROP (Platform Rest Of worst case Power)
    //
    // This object provides maximum worst case platform rest of power.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   power in milliwatts
    //
    Method(PROP)
    {
#ifdef EC_SUPPORT
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.PROP)
      } Else {
       Return(25000) // 25 watts
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

#ifdef EC_SUPPORT
    // APKP (Ac PeaK Power)
    //
    // This object provides maximum adapter power output.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   power in milliwatts
    //
    Method(APKP)
    {
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.APKP)
      } Else {
        Return(90000) // 90 watts
      }
    }

    // APKT (Ac PeaK Time)
    //
    // This object provides the maximum time the adapter can maintain peak power.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   time in milliseconds
    //
    Method(APKT)
    {
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.APKT)
      } Else {
        Return(10) // 10 milliseconds
      }
    }
#endif //EC_SUPPORT

    // AVOL
    //
    // Returns the AC source nominal voltage
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Returns the AC source nominal voltage in milliVolts.
    //
    Method(AVOL,0,Serialized)
    {
#ifdef EC_SUPPORT
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.AVOL)
      } Else {
        Return(0) // EC Unavailable
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

    // ACUR
    //
    // Returns the AC source operational current
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Returns the AC source operational current in milliAmperes.
    //
    Method(ACUR,0,Serialized)
    {
#ifdef EC_SUPPORT
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.ACUR)
      } Else {
        Return(0) // EC Unavailable
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

    // AP01
    //
    // Returns AC source 1ms period percentage overload in 1% unit.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Returns AC source 1ms period percentage overload in 1% unit.
    //
    Method(AP01,0,Serialized)
    {
#ifdef EC_SUPPORT
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.AP01)
      } Else {
        Return(0) // EC Unavailable
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

    // AP02
    //
    // Returns AC source 2ms period percentage overload in 1% unit.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Returns AC source 2ms period percentage overload in 1% unit.
    //
    Method(AP02,0,Serialized)
    {
#ifdef EC_SUPPORT
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.AP02)
      } Else {
        Return(0) // EC Unavailable
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

    // AP10
    //
    // Returns AC source 10ms period percentage overload in 1% unit.
    //
    // Arguments: (0)
    //   None
    // Return Value:
    //   Returns AC source 10ms period percentage overload in 1% unit.
    //
    Method(AP10,0,Serialized)
    {
#ifdef EC_SUPPORT
      If(LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Return(\_SB.PC00.LPCB.H_EC.AP10)
      } Else {
        Return(0) // EC Unavailable
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      Return(0) // EC not available
#endif //ECLITE_PSE_SUPPORT
    }

    // PBOK
    //
    // PBOK is a command which BIOS sends to EC.
    // It will have a parameter which is the sequence number.
    //
    // Arguments: (1)
    //   Arg0 should be sent by DPTF driver which will be corresponding to Power delivery state change sequence number.
    //   Bit[3:0] = Power Delivery State Change Sequence number
    // Return Value:
    //   None
    //
    Method(PBOK,1,Serialized)
    {
#ifdef EC_SUPPORT
      If (LEqual(\_SB.PC00.LPCB.H_EC.ECAV,1)) // Check If EC opregion is available
      {
        Store (And(Arg0, 0x000F), Local0)
        \_SB.PC00.LPCB.H_EC.ECWT (Local0, RefOf(\_SB.PC00.LPCB.H_EC.PBOK)) // Store sequence number
        \_SB.PC00.LPCB.H_EC.ECMD (0x15)
      }
#endif
#ifdef ECLITE_PSE_SUPPORT
      // Do Nothing!!! EC not available
#endif //ECLITE_PSE_SUPPORT
    }

  } // End TPWR Device
}// end Scope(\_SB)
