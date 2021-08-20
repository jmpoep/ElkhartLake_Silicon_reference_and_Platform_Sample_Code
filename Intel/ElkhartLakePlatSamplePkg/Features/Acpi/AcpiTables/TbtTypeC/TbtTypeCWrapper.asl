/** @file
  Thunderbolt (TBT) TypeC Wrapper to define Thunderbolt as ACPI device

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
  //
  // TBT DS port USB
  //
  Device(TBDU)
  {
    Name(_ADR, 0x00020000)

    Device(XHCI)
    {
      Name(_ADR, 0x00)

      Device(RHUB)
      {
        Name(_ADR, 0x00)

        //
        // Split Mode Support Status (SLMS)
        // Method to find whether TBT Port 1/2 supports Split mode
        // Arg0 : TBT Port number 1/2
        // Uses Name Space Object TURP to know the Current Root Port
        // TPXD [3:7] Root port , [1:2] Port type PCH/TBT/CPU [0] Split mode Support
        //
        Method(SLMS, 1, Serialized) { // Check split mode is supported
          // Check if TBT Port behind this root port is defined
          ShiftLeft(TURP,2, Local0)
          Or(Local0, 0x01, Local0)
          If (LAnd (LEqual(ShiftRight (TP1D,1), Local0),LEqual(Arg0, TP1T))) {
            Return (And(TP1D,0x01))
          } ElseIf(LAnd (LEqual(ShiftRight (TP2D,1), Local0),LEqual(Arg0, TP2T))) {
            Return (And(TP2D,0x01))
          } ElseIf(LAnd (LEqual(ShiftRight (TP3D,1), Local0),LEqual(Arg0, TP3T))) {
            Return (And(TP3D,0x01))
          } ElseIf(LAnd (LEqual(ShiftRight (TP4D,1), Local0),LEqual(Arg0, TP4T))) {
            Return (And(TP4D,0x01))
          } ElseIf(LAnd (LEqual(ShiftRight (TP5D,1), Local0),LEqual(Arg0, TP5T))) {
            Return (And(TP5D,0x01))
          } ElseIf(LAnd (LEqual(ShiftRight (TP6D,1), Local0),LEqual(Arg0, TP6T))) {
            Return (And(TP6D,0x01))
          } Else {
            Return (0)
          }
        }
        //
        // Find the UCM Connector and return the appropriate UPC/PLD methods
        // Idea is to define UPC/PLD Methods for all the Type C ports at one place and
        // reuse it where ever required
        // Arg0 : TBT Port number 1/2
        // Uses Name Space Object TURP to know the Current Root Port
        // Note : This should be called only if Split mode is supported for the given port
        // Same can be confirmed using SLMS method
        //
        Method(FPCP, 2, Serialized) {
          ShiftLeft(TURP,2, Local0)
          Or(Local0, 0x01, Local0)
          // Root port number
          If (LAnd (LEqual(ShiftRight (TP1D,1), Local0),LEqual(Arg0, TP1T))) {
            Return (\_SB.UBTC.RUCC(1, Arg1))
          } ElseIf(LAnd (LEqual(ShiftRight (TP2D,1), Local0),LEqual(Arg0, TP2T))) {
            Return (\_SB.UBTC.RUCC(2, Arg1))
          } ElseIf(LAnd (LEqual(ShiftRight (TP3D,1), Local0),LEqual(Arg0, TP3T))) {
            Return (\_SB.UBTC.RUCC(3, Arg1))
          } ElseIf(LAnd (LEqual(ShiftRight (TP4D,1), Local0),LEqual(Arg0, TP4T))) {
            Return (\_SB.UBTC.RUCC(4, Arg1))
          } ElseIf(LAnd (LEqual(ShiftRight (TP5D,1), Local0),LEqual(Arg0, TP5T))) {
            Return (\_SB.UBTC.RUCC(5, Arg1))
          } ElseIf(LAnd (LEqual(ShiftRight (TP6D,1), Local0),LEqual(Arg0, TP6T))) {
            Return (\_SB.UBTC.RUCC(6, Arg1))
          } Else {
            If(LEqual(Arg1, 1)) {
              Return (TUPC(0,0))
            } Else {
              Return (TPLD(0,0))
            }
          }
        }
        //
        // Find Port supported or not(FPSP)
        // Method to find Port enabled or not (we have cases where only 1 port supported)
        // Arg0 : TBT Port number 1/2
        // Uses Name Space Object TURP to know the Current Root Port
        //
        Method(FPSP, 1, Serialized) {
          // Create Propeties of the input Port to match with the Policy provided for Type C Connectors
          // Shift left and or with 0x01(TBT Controller) which will give 0:1 Controller 2:7 Root port
          // Shift right Policy by one Bit will give the same and compare both.
          ShiftLeft(TURP,2, Local0)
          Or(Local0, 0x01, Local0)
          If (LAnd (LEqual(ShiftRight (TP1D,1), Local0),LEqual(Arg0, TP1T))) {
            Return (1)
          } ElseIf(LAnd (LEqual(ShiftRight (TP2D,1), Local0),LEqual(Arg0, TP2T))) {
            Return (1)
          } ElseIf(LAnd (LEqual(ShiftRight (TP3D,1), Local0),LEqual(Arg0, TP3T))) {
            Return (1)
          } ElseIf(LAnd (LEqual(ShiftRight (TP4D,1), Local0),LEqual(Arg0, TP4T))) {
            Return (1)
          } ElseIf(LAnd (LEqual(ShiftRight (TP5D,1), Local0),LEqual(Arg0, TP5T))) {
            Return (1)
          } ElseIf(LAnd (LEqual(ShiftRight (TP6D,1), Local0),LEqual(Arg0, TP6T))) {
            Return (1)
          } Else {
            Return (0)
          }
        }

        //
        // Method for creating generic _PLD buffers
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

        //
        // Method for creating generic _UPC buffers
        // Similar to _PLD, for internal testing we only care about 1 parameter
        //
        Method(TUPC, 2, Serialized) { // For the port related with USB Type C.
          // Arg0: Connectable
          // Arg1: Type
          // Type:
          //  0x08:     Type C connector - USB2-only
          //  0x09:     Type C connector - USB2 and SS with Switch
          //  0x0A:     Type C connector - USB2 and SS without Switch
          Name(PCKG, Package(4) { 1, 0x00, 0, 0 } )
          Store(Arg0,Index(PCKG,0))
          Store(Arg1,Index(PCKG,1))
          return (PCKG)
        }
        If(LEqual(FPSP(1), 1)) {
          Device(HS01)
          {
            Name(_ADR, 0x01)
            // Type C connector - USB2 and SS with Switch
            Method(_UPC) {
              If(LEqual(SLMS(1), 0)) {
                Return (FPCP(1,1))
              } Else {
                Return (TUPC(0,0))
              }
            }
            Method(_PLD) {
              If(LEqual(SLMS(1), 0)) {
                Return (FPCP(1,2))
              } Else {
                Return (TPLD(0,0))
              }
            }
          } // End of Device(HS01)
        }
        If(LEqual(FPSP(2), 1)) {
          Device(HS02)
          {
            Name(_ADR, 0x02)
            // Type C connector - USB2 and SS with Switch
            Method(_UPC) {
              If(LEqual(SLMS(2), 0)) {
                Return (FPCP(2,1))
              } Else {
                Return (TUPC(0,0))
              }
            }
            Method(_PLD) {
              If(LEqual(SLMS(2), 0)) {
                Return (FPCP(2,2))
              } Else {
                Return (TPLD(0,0))
              }
            }
          } // End of Device(HS02)
        }
        If(LEqual(FPSP(1), 1)) {
          Device(SS01)
          {
            Name(_ADR, 0x03)
            // Type C connector - USB2 and SS with Switch
            Method(_UPC) {
              Return (FPCP(1,1))
            }
            Method(_PLD) {
              Return (FPCP(1,2))
            }
          } // End of Device(SS01)
        }
        If(LEqual(FPSP(2), 1)) {
          Device(SS02)
          {
            Name(_ADR, 0x04)
            // Type C connector - USB2 and SS with Switch
            Method(_UPC) {
              Return (FPCP(2,1))
            }
            Method(_PLD) {
              Return (FPCP(2,2))
            }
          } // End of Device(SS02)
        }
      } // End of Device(RHUB)
    } // End of Device(XHCI)
  } // End of Device(TBDU)
