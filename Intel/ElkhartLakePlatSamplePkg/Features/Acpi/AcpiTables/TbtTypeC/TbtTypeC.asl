/** @file
  Thunderbolt (TBT) TypeC ports information

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
  "TbtTypeC.aml",
  "SSDT",
  2,
  "Intel",
  "TbtTypeC",
  0x0
  )
{
  External(\_SB.PC00.RP01.PXSX, DeviceObj)
  External(\_SB.PC00.RP05.PXSX, DeviceObj)
  External(\_SB.PC00.RP09.PXSX, DeviceObj)
  External(\_SB.UBTC.CR01._UPC, MethodObj)
  External(\_SB.UBTC.CR01._PLD, MethodObj)
  External(\_SB.UBTC.CR02._UPC, MethodObj)
  External(\_SB.UBTC.CR02._PLD, MethodObj)
  External(\_SB.UBTC.CR03._UPC, MethodObj)
  External(\_SB.UBTC.CR03._PLD, MethodObj)
  External(\_SB.UBTC.CR04._UPC, MethodObj)
  External(\_SB.UBTC.CR04._PLD, MethodObj)
  External(\_SB.UBTC.CR05._UPC, MethodObj)
  External(\_SB.UBTC.CR05._PLD, MethodObj)
  External(\_SB.UBTC.CR06._UPC, MethodObj)
  External(\_SB.UBTC.CR06._PLD, MethodObj)
  External(\_SB.UBTC.RUCC, MethodObj)
  External(\TBTS, IntObj)
  External(\TBSE, IntObj)
  External(\RPS0, IntObj)
  External(\RPS1, IntObj)
  External(\NDUS, IntObj)
  External(\DPM1, IntObj)
  External(\DPM2, IntObj)
  External(\DPM3, IntObj)
  External(\NTUS, IntObj)
  External(\TP1T, IntObj)
  External(\TP1P, IntObj)
  External(\TP1D, IntObj)
  External(\TP2T, IntObj)
  External(\TP2P, IntObj)
  External(\TP2D, IntObj)
  External(\TP3T, IntObj)
  External(\TP3P, IntObj)
  External(\TP3D, IntObj)
  External(\TP4T, IntObj)
  External(\TP4P, IntObj)
  External(\TP4D, IntObj)
  External(\TP5T, IntObj)
  External(\TP5P, IntObj)
  External(\TP5D, IntObj)
  External(\TP6T, IntObj)
  External(\TP6P, IntObj)
  External(\TP6D, IntObj)

  If(LAnd(LEqual(TBTS, 0x01),LOr(LEqual(RPS0,0x1),LEqual(RPS1,0x1))))
  {
    Scope(\_SB.PC00.RP01.PXSX)
    {
       Name(TURP, 1)
       Include ("TbtTypeCWrapper.asl")
    } // End of Scope(\_SB.PC00.RP01.PXSX)
  }

  If(LAnd(LEqual(TBTS, 0x01),LOr(LEqual(RPS0,0x5),LEqual(RPS1,0x5))))
  {
    Scope(\_SB.PC00.RP05.PXSX)
    {
       Name(TURP, 5)
       Include ("TbtTypeCWrapper.asl")
    } // End of Scope(\_SB.PC00.RP05.PXSX)
  }

  If(LAnd(LEqual(TBTS, 0x01),LOr(LEqual(RPS0,0x9),LEqual(RPS1,0x9))))
  {
    Scope(\_SB.PC00.RP09.PXSX)
    {
       Name(TURP, 9)
       Include ("TbtTypeCWrapper.asl")
    } // End of Scope(\_SB.PC00.RP09.PXSX)
  }
} // DefinitionBlock
