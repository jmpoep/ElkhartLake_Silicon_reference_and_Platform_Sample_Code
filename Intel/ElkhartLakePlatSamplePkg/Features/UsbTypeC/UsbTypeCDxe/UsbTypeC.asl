/** @file
  ACPI DSDT table for USB Type C

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

DefinitionBlock (
  "UsbC.aml",
  "SSDT",
  2,
  "Intel_",
  "UsbCTabl",
  0x1000
  )
{
#ifdef EC_SUPPORT
  External(\_SB.PC00.LPCB.H_EC.MGI0, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGI1, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGI2, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGI3, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGI4, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGI5, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGI6, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGI7, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGI8, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGI9, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGIA, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGIB, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGIC, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGID, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGIE, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGIF, IntObj)

  External(\_SB.PC00.LPCB.H_EC.CTL0, IntObj)
  External(\_SB.PC00.LPCB.H_EC.CTL1, IntObj)
  External(\_SB.PC00.LPCB.H_EC.CTL2, IntObj)
  External(\_SB.PC00.LPCB.H_EC.CTL3, IntObj)
  External(\_SB.PC00.LPCB.H_EC.CTL4, IntObj)
  External(\_SB.PC00.LPCB.H_EC.CTL5, IntObj)
  External(\_SB.PC00.LPCB.H_EC.CTL6, IntObj)
  External(\_SB.PC00.LPCB.H_EC.CTL7, IntObj)

  External(\_SB.PC00.LPCB.H_EC.MGO0, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGO1, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGO2, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGO3, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGO4, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGO5, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGO6, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGO7, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGO8, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGO9, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGOA, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGOB, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGOC, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGOD, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGOE, IntObj)
  External(\_SB.PC00.LPCB.H_EC.MGOF, IntObj)

  External(\_SB.PC00.LPCB.H_EC.CCI0, IntObj)
  External(\_SB.PC00.LPCB.H_EC.CCI1, IntObj)
  External(\_SB.PC00.LPCB.H_EC.CCI2, IntObj)
  External(\_SB.PC00.LPCB.H_EC.CCI3, IntObj)

  External(\_SB.PC00.LPCB.H_EC.ECMD, MethodObj)
  External(\_SB.PC00.LPCB.H_EC.ECRD, MethodObj)  // EC Read Method
  External(\_SB.PC00.LPCB.H_EC.ECWT, MethodObj)  // EC Write Method
#endif
  External(UBCB)
  External(XDCE)
  External(USTC)
  External(UCMS)
  External(TBTS)
  External(TTUP)
  External(TP1T)
  External(TP1P)
  External(TP1D)
  External(TP2T)
  External(TP2P)
  External(TP2D)
  External(TP3T)
  External(TP3P)
  External(TP3D)
  External(TP4T)
  External(TP4P)
  External(TP4D)
  External(TP5T)
  External(TP5P)
  External(TP5D)
  External(TP6T)
  External(TP6P)
  External(TP6D)
  External(P8XH, MethodObj)
  External(\_SB.PC00.XHCI.RHUB, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.TPLD, MethodObj)

  Scope (\_SB)
  {
    Device(UBTC)  // USB type C device
    {
      Name (_HID, EISAID("USBC000"))
      Name (_CID, EISAID("PNP0CA0"))
      Name (_UID, 0)
      Name (_DDN, "USB Type C")
      Name (_ADR, 0x0)

      Name (CRS, ResourceTemplate () {
        Memory32Fixed (ReadWrite, 0x00000000, 0x1000, USBR)
      })

      Method(_CRS,0, Serialized)
      {
        CreateDWordField (CRS, \_SB.UBTC.USBR._BAS, CBAS)
        Store (UBCB, CBAS)
        Return(CRS)
      }

      Method(_STA,0)
      {
        If (LEqual(USTC,1)) //Check if USB Type C is supported
        {
          If (LEqual(UCMS,1)) //Check if UCSI is supported
          {
            Return(0x000F)
          }
        }
        Return(0x0000)
      }

      //
      // Return USB Type C Connector (RUCC ) Properties
      // Arg0 : Connector number
      // Arg1 : 1 - UPC, 2 - PLD
      // Uses Name Space Object TURP to know the Current Root Port
      // TPXD [3:7] Root port , [1:2] Port type PCH/TBT/CPU [0] Split mode Support
      //
      Method(RUCC, 2, Serialized) { //
        Switch(ToInteger(Arg0)) // Connector
        {
          Case (1)
          {
            If(LEqual(Arg1, 1)) {
              Return (\_SB.UBTC.CR01._UPC)
            } Else {
              Return (\_SB.UBTC.CR01._PLD)
            }
          }
          Case (2)
          {
            If(LEqual(Arg1, 1)) {
              Return (\_SB.UBTC.CR02._UPC)
            } Else {
              Return (\_SB.UBTC.CR02._PLD)
            }
          }
          Case (3)
          {
            If(LEqual(Arg1, 1)) {
              Return (\_SB.UBTC.CR03._UPC)
            } Else {
              Return (\_SB.UBTC.CR03._PLD)
            }
          }
          Case (4)
          {
            If(LEqual(Arg1, 1)) {
              Return (\_SB.UBTC.CR04._UPC)
            } Else {
              Return (\_SB.UBTC.CR04._PLD)
            }
          }
          Case (5)
          {
            If(LEqual(Arg1, 1)) {
              Return (\_SB.UBTC.CR05._UPC)
            } Else {
              Return (\_SB.UBTC.CR05._PLD)
            }
          }
          Case (6)
          {
            If(LEqual(Arg1, 1)) {
              Return (\_SB.UBTC.CR06._UPC)
            } Else {
              Return (\_SB.UBTC.CR06._PLD)
            }
          }
          Default
          {
            If(LEqual(Arg1, 1)) {
              Return (TUPC(0))
            } Else {
              Return (TPLD(0,0))
            }
          }
        }
      }
      //
      // Find Port Mapping Group number (FPMN)
      // Arg0 : Connector number
      // Uses Name Space Object TURP to know the Current Root Port
      // TPXD [3:7] Root port , [1:2] Port type PCH/TBT/CPU [0] Split mode Support
      //
      Method(FPMN, 1, Serialized)
      {
        Switch(ToInteger(Arg0)) // UCM Connector
        {
          Case (1)
          {
            //
            // Bit 1:2 will give the Controller from which this is exposed (PCH/TBT/CPU)
            //
            ShiftRight (TP1D, 1, Local0)
            And(Local0, 0x03, Local0)
            // Bit 0 is for Split mode support status
            And(TP1D, 0x01, Local1)
            // Port mapping on PCH controller if Split mode support
            Store (TP1P, Local2)
            // Port mapping on Respective Controller
            Store (TP1T, Local3)
          }
          Case (2)
          {
            ShiftRight (TP2D, 1, Local0)
            And(Local0, 0x03, Local0)
            And(TP2D, 0x01, Local1)
            Store (TP2P, Local2)
            Store (TP2T, Local3)
          }
          Case (3)
          {
            ShiftRight (TP3D, 1, Local0)
            And(Local0, 0x03, Local0)
            And(TP3D, 0x01, Local1)
            Store (TP3P, Local2)
            Store (TP3T, Local3)
          }
          Case (4)
          {
            ShiftRight (TP4D, 1, Local0)
            And(Local0, 0x03, Local0)
            And(TP4D, 0x01, Local1)
            Store (TP4P, Local2)
            Store (TP4T, Local3)
          }
          Case (5)
          {
            ShiftRight (TP5D, 1, Local0)
            And(Local0, 0x03, Local0)
            And(TP5D, 0x01, Local1)
            Store (TP5P, Local2)
            Store (TP5T, Local3)
          }
          Case (6)
          {
            ShiftRight (TP6D, 1, Local0)
            And(Local0, 0x03, Local0)
            And(TP6D, 0x01, Local1)
            Store (TP6P, Local2)
            Store (TP6T, Local3)
          }
          Default
          {
            Store (0xFF, Local0)
            Store (0, Local1)
            Store (0, Local2)
            Store (0, Local3)
          }
        }

        If(LEqual(Local0, 0x00)) { // PCH Type C
          Return(Local2)
        } ElseIf (Lor(LEqual(Local0, 0x01), LEqual(Local0, 0x02))) { // TBT or CPU Type C
          If (LEqual(Local1, 0x01)) { // Split mode supported
            Return(Local2) // Return PCH XHCI Port number
          } Else {
            Return(Local3) // Return PCH/TBT/CPU XHCI Port number
          }
        } Else  {
          Return(0)
        }
      }
      //
      // Method for creating Type C _PLD buffers
      // _PLD contains lots of data, but for purpose of internal validation we care only about
      // ports visibility and pairing (this requires group position)
      // so these are the only 2 configurable parameters
      //
      Method(TPLD, 2, Serialized) { // For the port related with USB Type C.
        // Arg0:  Visible
        // Arg1:  Group position
        Name(PCKG, Package() { Buffer(0x10) {} } )
        CreateField(DerefOf(Index(PCKG,0)), 0, 7, REV)
        Store(1,REV)
        CreateField(DerefOf(Index(PCKG,0)), 64, 1, VISI)
        Store(Arg0, VISI)
        CreateField(DerefOf(Index(PCKG,0)), 87, 8, GPOS)
        Store(Arg1, GPOS)
        // For USB type C, Standerd values
        CreateField(DerefOf(Index(PCKG,0)), 74, 4, SHAP)  // Shape set to Oval
        Store(1, SHAP)
        CreateField(DerefOf(Index(PCKG,0)), 32, 16, WID)  // Width of the connector, 8.34mm
        Store(8, WID)
        CreateField(DerefOf(Index(PCKG,0)), 48, 16, HGT)  // Height of the connector, 2.56mm
        Store(3, HGT)
        return (PCKG)
      }
      Method(TUPC, 1, Serialized) { // For the port related with USB Type C. copied and modified from GUPC
        // Arg0: Type
        // Type:
        //  0x08:     Type-C connector - USB2-only
        //  0x09:     Type-C connector - USB2 and SS with Switch
        //  0x0A:     Type-C connector - USB2 and SS without Switch
        Name(PCKG, Package(4) { 1, 0x00, 0, 0 } )
        Store(Arg0,Index(PCKG,1))
        return (PCKG)
      }

      //
      // Expose connector based on Total supported Connectors
      //
      If (LGreaterEqual(TTUP,1)) {
        Device (CR01) { // USB Type C Connector
          Name (_ADR, 0x0)
          Method (_PLD) {
            Return (TPLD(1,FPMN(1)))
          }
          Method (_UPC) {
            Return (TUPC(9))
          }
        }
      }
      If (LGreaterEqual(TTUP,2)) {
        Device (CR02) { // USB Type C Connector
          Name (_ADR, 0x0)
          Method (_PLD) {
            Return (TPLD(1,FPMN(2)))
          }
          Method (_UPC) {
            Return (TUPC(9))
          }
        }
      }
      If (LGreaterEqual(TTUP,3)) {
        Device (CR03) { // USB Type C Connector
          Name (_ADR, 0x0)
          Method (_PLD) {
            Return (TPLD(1,FPMN(3)))
          }
          Method (_UPC) {
            Return (TUPC(9))
          }
        }
      }
      If (LGreaterEqual(TTUP,4)) {
        Device (CR04) { // USB Type C Connector
          Name (_ADR, 0x0)
          Method (_PLD) {
            Return (TPLD(1,FPMN(4)))
          }
          Method (_UPC) {
            Return (TUPC(9))
          }
        }
      }
      If (LGreaterEqual(TTUP,5)) {
        Device (CR05) { // USB Type C Connector
          Name (_ADR, 0x0)
          Method (_PLD) {
            Return (TPLD(1,FPMN(5)))
          }
          Method (_UPC) {
            Return (TUPC(9))
          }
        }
      }
      If (LGreaterEqual(TTUP,6)) {
        Device (CR06) { // USB Type C Connector
          Name (_ADR, 0x0)
          Method (_PLD) {
            Return (TPLD(1,FPMN(6)))
          }
          Method (_UPC) {
            Return (TUPC(9))
          }
        }
      }

      OperationRegion (USBC, SystemMemory, UBCB, 0x38)  // 56 bytes Opm Buffer
      Field(USBC,ByteAcc,Lock,Preserve)
      {
        VER1, 8,
        VER2, 8,
        RSV1, 8,
        RSV2, 8,
        Offset(4),
        CCI0, 8,  //  PPM->OPM CCI indicator
        CCI1, 8,
        CCI2, 8,
        CCI3, 8,

        CTL0, 8,  //  OPM->PPM Control message
        CTL1, 8,
        CTL2, 8,
        CTL3, 8,
        CTL4, 8,
        CTL5, 8,
        CTL6, 8,
        CTL7, 8,

        // USB Type C Mailbox Interface
        MGI0, 8,  //  PPM->OPM Message In
        MGI1, 8,
        MGI2, 8,
        MGI3, 8,
        MGI4, 8,
        MGI5, 8,
        MGI6, 8,
        MGI7, 8,
        MGI8, 8,
        MGI9, 8,
        MGIA, 8,
        MGIB, 8,
        MGIC, 8,
        MGID, 8,
        MGIE, 8,
        MGIF, 8,

        MGO0, 8,  //  OPM->PPM Message Out
        MGO1, 8,
        MGO2, 8,
        MGO3, 8,
        MGO4, 8,
        MGO5, 8,
        MGO6, 8,
        MGO7, 8,
        MGO8, 8,
        MGO9, 8,
        MGOA, 8,
        MGOB, 8,
        MGOC, 8,
        MGOD, 8,
        MGOE, 8,
        MGOF, 8,

      }  // end of Field

      Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj} )
      {
        // Compare passed in UUID with supported UUID.
        If (LEqual(Arg0, ToUUID ("6f8398c2-7ca4-11e4-ad36-631042b5008f")))  // UUID for USB type C
        {
          Switch (ToInteger(Arg2))  // Arg2:  0 for query, 1 for write and 2 for read
          {
            Case (0)
            {
              Return (Buffer() {0x0F}) // 2 functions defined other than Query.
            }

            Case (1)  // OPM write to EC
            {
#ifdef EC_SUPPORT
              \_SB.PC00.LPCB.H_EC.ECWT( MGO0, RefOf(  \_SB.PC00.LPCB.H_EC.MGO0 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGO1, RefOf(  \_SB.PC00.LPCB.H_EC.MGO1 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGO2, RefOf(  \_SB.PC00.LPCB.H_EC.MGO2 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGO3, RefOf(  \_SB.PC00.LPCB.H_EC.MGO3 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGO4, RefOf(  \_SB.PC00.LPCB.H_EC.MGO4 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGO5, RefOf(  \_SB.PC00.LPCB.H_EC.MGO5 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGO6, RefOf(  \_SB.PC00.LPCB.H_EC.MGO6 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGO7, RefOf(  \_SB.PC00.LPCB.H_EC.MGO7 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGO8, RefOf(  \_SB.PC00.LPCB.H_EC.MGO8 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGO9, RefOf(  \_SB.PC00.LPCB.H_EC.MGO9 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGOA, RefOf(  \_SB.PC00.LPCB.H_EC.MGOA ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGOB, RefOf(  \_SB.PC00.LPCB.H_EC.MGOB ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGOC, RefOf(  \_SB.PC00.LPCB.H_EC.MGOC ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGOD, RefOf(  \_SB.PC00.LPCB.H_EC.MGOD ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGOE, RefOf(  \_SB.PC00.LPCB.H_EC.MGOE ) )
              \_SB.PC00.LPCB.H_EC.ECWT( MGOF, RefOf(  \_SB.PC00.LPCB.H_EC.MGOF ) )

              \_SB.PC00.LPCB.H_EC.ECWT( CTL0, RefOf(  \_SB.PC00.LPCB.H_EC.CTL0 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( CTL1, RefOf(  \_SB.PC00.LPCB.H_EC.CTL1 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( CTL2, RefOf(  \_SB.PC00.LPCB.H_EC.CTL2 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( CTL3, RefOf(  \_SB.PC00.LPCB.H_EC.CTL3 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( CTL4, RefOf(  \_SB.PC00.LPCB.H_EC.CTL4 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( CTL5, RefOf(  \_SB.PC00.LPCB.H_EC.CTL5 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( CTL6, RefOf(  \_SB.PC00.LPCB.H_EC.CTL6 ) )
              \_SB.PC00.LPCB.H_EC.ECWT( CTL7, RefOf(  \_SB.PC00.LPCB.H_EC.CTL7 ) )

              \_SB.PC00.LPCB.H_EC.ECMD (0xE0)
#endif
              P8XH(0,0xE0)
            }

            Case (2)  // OPM read from EC
            {
#ifdef EC_SUPPORT
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGI0) ), MGI0 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGI1) ), MGI1 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGI2) ), MGI2 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGI3) ), MGI3 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGI4) ), MGI4 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGI5) ), MGI5 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGI6) ), MGI6 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGI7) ), MGI7 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGI8) ), MGI8 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGI9) ), MGI9 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGIA) ), MGIA )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGIB) ), MGIB )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGIC) ), MGIC )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGID) ), MGID )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGIE) ), MGIE )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.MGIF) ), MGIF )

              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.CCI0) ), CCI0 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.CCI1) ), CCI1 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.CCI2) ), CCI2 )
              Store(  \_SB.PC00.LPCB.H_EC.ECRD( RefOf (\_SB.PC00.LPCB.H_EC.CCI3) ), CCI3 )
#endif
            }

            Case (3) //xDCI FN EN/DIS Status
            {
              Return(XDCE) // 0: Disable 1: Enable
            }
          }  // End switch
        }   // End UUID check
        Return (Buffer() {0})
      }  // End _DSM Method
    }  // end of Device
  } // end \_SB scope
} // end SSDT