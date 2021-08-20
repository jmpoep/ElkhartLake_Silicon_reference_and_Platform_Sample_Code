/** @file
  ACPI SSDT table

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
  External(\_SB.PC00.XHCI.RHUB.HS01, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS02, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS03, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS04, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS05, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS06, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS07, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS08, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS09, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS10, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS11, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS12, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS13, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.HS14, DeviceObj)

  External(\_SB.PC00.XHCI.RHUB.SS01, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS02, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS03, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS04, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS05, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS06, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS07, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS08, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS09, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.SS10, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.USR1, DeviceObj)
  External(\_SB.PC00.XHCI.RHUB.USR2, DeviceObj)

  External(\_SB.UBTC.CR01._UPC, MethodObj)
  External(\_SB.UBTC.CR01._PLD, MethodObj)
  External(\_SB.UBTC.CR02._UPC, MethodObj)
  External(\_SB.UBTC.CR02._PLD, MethodObj)
  External(\_SB.UBTC.CR03._UPC, MethodObj)
  External(\_SB.UBTC.CR03._PLD, MethodObj)
  External(\_SB.UBTC.CR04._UPC, MethodObj)
  External(\_SB.UBTC.CR04._PLD, MethodObj)
  External(\_SB.UBTC.RUCC, MethodObj)

  External(\_SB.PC00.RP01.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP02.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP03.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP04.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP05.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP06.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP07.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP08.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP09.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP10.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP11.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP12.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP13.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP14.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP15.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP16.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP17.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP18.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP19.PXSX.WIST, MethodObj)
  External(\_SB.PC00.RP20.PXSX.WIST, MethodObj)

  External(ATDV)
  External(BTSE)
  External(BTBR)
  External(BED2)
  External(BED3)
  External(BTLE)
  External(BTL2)
  External(BTLL)

  //
  // CNVd is present
  //
  Method(CNDP)
  {
    If (\_SB.PC00.RP01.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP02.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP03.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP04.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP05.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP06.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP07.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP08.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP09.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP10.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP11.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP12.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP13.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP14.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP15.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP16.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP17.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP18.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP19.PXSX.WIST()) {
      Return (0x01)
    }
    If (\_SB.PC00.RP20.PXSX.WIST()) {
      Return (0x01)
    }
    Return (0x00)
  }

  If (LGreaterEqual(NHSP,1)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS01) {
      Method(_UPC) {
        If(LEqual(H1TC,0)) {
          Return (GUPC(H1CN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(H1CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(H1TC,0)) {
          Return (GPLD(H1VS,1))
        } Else {
          Return (\_SB.UBTC.RUCC(H1CR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,1), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,2)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS02) {
      Method(_UPC) {
        If(LEqual(H2TC,0)) {
          Return (GUPC(H2CN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(H2CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(H2TC,0)) {
          Return (GPLD(H2VS,2))
        } Else {
          Return (\_SB.UBTC.RUCC(H2CR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,2), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,3)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS03) {
      Method(_UPC) {
        If(LEqual(H3TC,0)) {
          Return (GUPC(H3CN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(H3CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(H3TC,0)) {
          Return (GPLD(H3VS,3))
        } Else {
          Return (\_SB.UBTC.RUCC(H3CR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,3), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,4)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS04) {
      Method(_UPC) {
        If(LEqual(H4TC,0)) {
          Return (GUPC(H4CN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(H4CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(H4TC,0)) {
          Return (GPLD(H4VS,4))
        } Else {
          Return (\_SB.UBTC.RUCC(H4CR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,4), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,5)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS05) {
      Method(_UPC) {
        If(LEqual(H5TC,0)) {
          Return (GUPC(H5CN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(H5CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(H5TC,0)) {
          Return (GPLD(H5VS,5))
        } Else {
          Return (\_SB.UBTC.RUCC(H5CR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,5), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,6)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS06) {
      Method(_UPC) {
        If(LEqual(H6TC,0)) {
          Return (GUPC(H6CN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(H6CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(H6TC,0)) {
          Return (GPLD(H6VS,6))
        } Else {
          Return (\_SB.UBTC.RUCC(H6CR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,6), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,7)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS07) {
      Method(_UPC) {
        If(LEqual(H7TC,0)) {
          Return (GUPC(H7CN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(H7CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(H2TC,0)) {
          Return (GPLD(H7VS,7))
        } Else {
          Return (\_SB.UBTC.RUCC(H7CR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,7), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,8)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS08) {
      Method(_UPC) {
        If(LEqual(H8TC,0)) {
          Return (GUPC(H8CN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(H8CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(H2TC,0)) {
          Return (GPLD(H8VS,8))
        } Else {
          Return (\_SB.UBTC.RUCC(H8CR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,8), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,9)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS09) {
      Method(_UPC) {
        If(LEqual(H9TC,0)) {
          Return (GUPC(H9CN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(H9CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(H9TC,0)) {
          Return (GPLD(H9VS,9))
        } Else {
          Return (\_SB.UBTC.RUCC(H9CR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,9), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,10)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS10) {
      Method(_UPC) {
        If(LEqual(HATC,0)) {
          Return (GUPC(HACN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(HACR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(HATC,0)) {
          Return (GPLD(HAVS,10))
        } Else {
          Return (\_SB.UBTC.RUCC(HACR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,10), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,11)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS11) {
      Method(_UPC) {
        If(LEqual(HBTC,0)) {
          Return (GUPC(HBCN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(HBCR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(HBTC,0)) {
          Return (GPLD(HBVS,11))
        } Else {
          Return (\_SB.UBTC.RUCC(HBCR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,11), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,12)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS12) {
      Method(_UPC) {
        If(LEqual(HCTC,0)) {
          Return (GUPC(HCCN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(HCCR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(HCTC,0)) {
          Return (GPLD(HCVS,12))
        } Else {
          Return (\_SB.UBTC.RUCC(HCCR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,12), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }
  If (LGreaterEqual(NHSP,13)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS13) {
      Method(_UPC) {
        If(LEqual(HDTC,0)) {
          Return (GUPC(HDCN))
        } Else { // Type C
          Return (\_SB.UBTC.RUCC(HDCR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(HDTC,0)) {
          Return (GPLD(HDVS,13))
        } Else {
          Return (\_SB.UBTC.RUCC(HDCR,2))
        }
      }
      If (CondRefOf(DBPN)) {
        If (LAnd(LEqual(DBPN,13), CNDP())) {
          Include("AntennaDiversity.asl")
          Include("BtRegulatory.asl")
          Include("GeneralPurposeConfig.asl")
        }
      }
    }
  }

  Scope (\_SB.PC00.XHCI.RHUB.USR1) {
    Method(_UPC) { Return (GUPC(0)) }
    Method(_PLD) { Return (GPLD(0,0)) }
  }

  Scope (\_SB.PC00.XHCI.RHUB.USR2) {
    Method(_UPC) { Return (GUPC(0)) }
    Method(_PLD) { Return (GPLD(0,0)) }
  }
  If (LGreaterEqual(NSSP,1)) {
    Scope (\_SB.PC00.XHCI.RHUB.SS01) {
      Method(_UPC) {
        If(LEqual(S1TC,0)) {
          Return (GUPC(S1CN))
        } Else {
          Return (\_SB.UBTC.RUCC(S1CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(S1TC,0)) {
          Return (GPLD(S1VS,S1CP))
        } Else {
          Return (\_SB.UBTC.RUCC(S1CR,2))
        }
      }
    }
  }
  If (LGreaterEqual(NSSP,2)) {
    Scope (\_SB.PC00.XHCI.RHUB.SS02) {
      Method(_UPC) {
        If(LEqual(S2TC,0)) {
          Return (GUPC(S2CN))
        } Else {
          Return (\_SB.UBTC.RUCC(S2CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(S2TC,0)) {
          Return (GPLD(S2VS,S2CP))
        } Else {
          Return (\_SB.UBTC.RUCC(S2CR,2))
        }
      }
    }
  }
  If (LGreaterEqual(NSSP,3)) {
    Scope (\_SB.PC00.XHCI.RHUB.SS03) {
      Method(_UPC) {
        If(LEqual(S3TC,0)) {
          Return (GUPC(S3CN))
        } Else {
          Return (\_SB.UBTC.RUCC(S3CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(S3TC,0)) {
          Return (GPLD(S3VS,S3CP))
        } Else {
          Return (\_SB.UBTC.RUCC(S3CR,2))
        }
      }
    }
  }
  If (LGreaterEqual(NSSP,4)) {
    Scope (\_SB.PC00.XHCI.RHUB.SS04) {
      Method(_UPC) {
        If(LEqual(S4TC,0)) {
          Return (GUPC(S4CN))
        } Else {
          Return (\_SB.UBTC.RUCC(S4CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(S4TC,0)) {
          Return (GPLD(S4VS,S4CP))
        } Else {
          Return (\_SB.UBTC.RUCC(S4CR,2))
        }
      }
    }
  }
  If (LGreaterEqual(NSSP,5)) {
    Scope (\_SB.PC00.XHCI.RHUB.SS05) {
      Method(_UPC) {
        If(LEqual(S5TC,0)) {
          Return (GUPC(S5CN))
        } Else {
          Return (\_SB.UBTC.RUCC(S5CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(S5TC,0)) {
          Return (GPLD(S5VS,S5CP))
        } Else {
          Return (\_SB.UBTC.RUCC(S5CR,2))
        }
      }
    }
  }
  If (LGreaterEqual(NSSP,6)) {
    Scope (\_SB.PC00.XHCI.RHUB.SS06) {
      Method(_UPC) {
        If(LEqual(S6TC,0)) {
          Return (GUPC(S6CN))
        } Else {
          Return (\_SB.UBTC.RUCC(S6CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(S6TC,0)) {
          Return (GPLD(S6VS,S6CP))
        } Else {
          Return (\_SB.UBTC.RUCC(S6CR,2))
        }
      }
    }
  }
  If (LGreaterEqual(NSSP,7)) {
    Scope (\_SB.PC00.XHCI.RHUB.SS07) {
      Method(_UPC) {
        If(LEqual(S7TC,0)) {
          Return (GUPC(S7CN))
        } Else {
          Return (\_SB.UBTC.RUCC(S7CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(S7TC,0)) {
          Return (GPLD(S7VS,S7CP))
        } Else {
          Return (\_SB.UBTC.RUCC(S7CR,2))
        }
      }
    }
  }
  If (LGreaterEqual(NSSP,8)) {
    Scope (\_SB.PC00.XHCI.RHUB.SS08) {
      Method(_UPC) {
        If(LEqual(S8TC,0)) {
          Return (GUPC(S8CN))
        } Else {
          Return (\_SB.UBTC.RUCC(S8CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(S8TC,0)) {
          Return (GPLD(S8VS,S8CP))
        } Else {
          Return (\_SB.UBTC.RUCC(S8CR,2))
        }
      }
    }
  }
 If (LGreaterEqual(NSSP,9)) {
    Scope (\_SB.PC00.XHCI.RHUB.SS09) {
      Method(_UPC) {
        If(LEqual(S9TC,0)) {
          Return (GUPC(S9CN))
        } Else {
          Return (\_SB.UBTC.RUCC(S9CR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(S9TC,0)) {
          Return (GPLD(S9VS,S9CP))
        } Else {
          Return (\_SB.UBTC.RUCC(S9CR,2))
        }
      }
    }
  }
  If (LGreaterEqual(NSSP,10)) {
    Scope (\_SB.PC00.XHCI.RHUB.SS10) {
      Method(_UPC) {
        If(LEqual(SATC,0)) {
          Return (GUPC(SACN))
        } Else {
          Return (\_SB.UBTC.RUCC(SACR,1))
        }
      }
      Method(_PLD) {
        If(LEqual(S1TC,0)) {
          Return (GPLD(SAVS,SACP))
        } Else {
          Return (\_SB.UBTC.RUCC(SACR,2))
        }
      }
    }
  }
