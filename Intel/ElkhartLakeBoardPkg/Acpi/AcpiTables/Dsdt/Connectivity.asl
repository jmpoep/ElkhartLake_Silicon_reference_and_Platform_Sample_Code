/** @file
  Intel ACPI Sample Code for connectivity modules

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

Scope(\_SB)
{

  //
  // Set M.2 BT RF-Kill(W_DISABLE2#) pin
  //
  Method (BTRK, 0x1, Serialized)
  {
    //
    // Arg0 - Value to W_DISABLE2#
    //

    \_SB.SGOV (GBTK, Arg0)
  }

  //
  // Get value of M.2 BT RF-Kill(W_DISABLE2#) pin
  //
  Method (GBTR, 0)
  {
    Return (\_SB.GGOV (GBTK))
  }
}

//
// Report thermal & regulatory methods if CNVi WiFi is present
//
If (\_SB.PC00.CNIP ()) {
  Scope (\_SB.PC00.CNVW) {
    Include("WifiThermal.asl")
    Include("WifiRegulatory.asl")
    Include("AntennaDiversity.asl")
    Include("GeneralPurposeConfig.asl")
  }
  If (LEqual (PCHS, PCH_LP)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS10) {
      Include("AntennaDiversity.asl")
      Include("BtRegulatory.asl")
      Include("GeneralPurposeConfig.asl")
    }
  } ElseIf (LEqual (PCHS, PCH_N)) {
    Scope (\_SB.PC00.XHCI.RHUB.HS08) {
      Include("AntennaDiversity.asl")
      Include("BtRegulatory.asl")
      Include("GeneralPurposeConfig.asl")
    }
  } Else {
    // for PCH_H
    Scope (\_SB.PC00.XHCI.RHUB.HS14) {
      Include("AntennaDiversity.asl")
      Include("BtRegulatory.asl")
      Include("GeneralPurposeConfig.asl")
    }
  }
}

Scope(\_SB.PC00.UA00)
{
  //
  // Bluetooth controller using serial interface
  //
  Device(BTH0){

    Method(_HID) {
      Return("INT33E1")  // TODO: HID is open EHL Discrete BT and can be udpated once it is avaialbe
    }

    Method(_INI) {
      SHPO(GBTI,1) // configure gpio pad in gpio driver mode; Bluetooth Interrupt
      SHPO(GBTK,1) // configure gpio pad in gpio driver mode; Bluetooth RF-Kill
    }

    Method(_CRS, 0x0, Serialized){
      Name(SBFG, ResourceTemplate (){
        UARTSerialBus(115200,,,0xc0,,,FlowControlHardware,32,32,"\\_SB.PC00.UA00" )
        GpioIo(Exclusive, PullDefault, 0, 0, IoRestrictionOutputOnly, "\\_SB.GPI0",,,KIL1 ) {0}
        GpioInt (Edge, ActiveLow, ExclusiveAndWake, PullDefault, 0x0000, "\\_SB.GPI0", 0x00, ResourceConsumer, INT1) { 0 }
      })
      CreateWordField(SBFG,INT1._PIN,INT3)
      CreateWordField(SBFG,KIL1._PIN,KIL3)
      Store(GNUM(GBTI),INT3)
      Store(GNUM(GBTK),KIL3)

      Name(SBFI, ResourceTemplate (){
        UARTSerialBus(115200,,,0xc0,,,FlowControlHardware,32,32,"\\_SB.PC00.UA00" )
        GpioIo(Exclusive, PullDefault, 0, 0, IoRestrictionOutputOnly, "\\_SB.GPI0",,,KIL2 ) {0}
        Interrupt(ResourceConsumer, Edge, ActiveLow, ExclusiveAndWake,,,INT2 ) {0}
      })
      CreateDWordField(SBFI,INT2._INT,INT4)
      CreateWordField(SBFI,KIL2._PIN,KIL4)
      Store(INUM(GBTI),INT4)
      Store(GNUM(GBTK),KIL4)

      If(LEqual(SDM9,0)) {
        Return (SBFG)
      } Else {
        Return (SBFI)
      }
    }

    Method (_STA, 0x0, NotSerialized){
      If(LNotEqual(SDS9,2)) { // Check Discrete BT Over UART is enabled
        Return (0x0)
      }
      Return (0x0F)
    }
    Name (_S0W, 2)                            // Required to put the device to D2 during S0 idle
  } // Device BTH0
  Include("BtRegulatory.asl")
  Include("GeneralPurposeConfig.asl")
}  // End of Scope(\_SB.PC00.UART0)
