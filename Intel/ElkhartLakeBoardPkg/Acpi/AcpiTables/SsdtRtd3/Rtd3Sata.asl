/** @file
  ACPI RTD3 SSDT table for integrated SATA adapter

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

External(\_SB.PC00.SAT0.NVM1, DeviceObj)
External(\_SB.PC00.SAT0.NVM2, DeviceObj)
External(\_SB.PC00.SAT0.NVM3, DeviceObj)
External(\_SB.PC00.SAT0.PRT0, DeviceObj)
External(\_SB.PC00.SAT0.PRT1, DeviceObj)
External(\_SB.PC00.SAT0.PRT2, DeviceObj)
External(\_SB.PC00.SAT0.PRT3, DeviceObj)
External(\_SB.PC00.SAT0.PRT4, DeviceObj)
External(\_SB.PC00.SAT0.PRT5, DeviceObj)

Scope(\_SB.PC00.SAT0) {

  OperationRegion(SMIO,PCI_Config,0x24,4)
  Field(SMIO,AnyAcc, NoLock, Preserve) {
    MBR6, 32,     ///- SATA ABAR
  }

  OperationRegion(PCIR, PCI_Config, 0x00, 0x10)
  Field(PCIR, DWordAcc, NoLock, Preserve) {
    Offset(0x0A),
    SUBC,   8  // Link Control register
  }

  //
  // Platform indicates D3Cold support by defining PWRG objects.
  // If PWRG object is defined power resource included in Rtd3SataPort.asl
  // will be visible.
  //
  If(And(RCG1_RTD3_PRT0_ENABLED, RCG1)) {
    Scope(PRT0){
      Name(PBAR, 0x118)
      External(PWRG)
      If(CondRefOf(PWRG)){
        Include("Rtd3SataPort.asl")
      }
    }
  }

  If(And(RCG1_RTD3_PRT1_ENABLED, RCG1)) {
    Scope(PRT1){
      Name(PBAR, 0x198)
      External(PWRG)
      If(CondRefOf(PWRG)){
        Include("Rtd3SataPort.asl")
      }
    }
  }

  If(And(RCG1_RTD3_PRT2_ENABLED, RCG1)) {
    Scope(PRT2){
      Name(PBAR, 0x218)
      External(PWRG)
      If(CondRefOf(PWRG)){
        Include("Rtd3SataPort.asl")
      }
    }
  }

  If(And(RCG1_RTD3_PRT3_ENABLED, RCG1)) {
    Scope(PRT3){
      Name(PBAR, 0x298)
      External(PWRG)
      If(CondRefOf(PWRG)){
        Include("Rtd3SataPort.asl")
      }
    }
  }

  If(And(RCG1_RTD3_PRT4_ENABLED, RCG1)) {
    Scope(PRT4){
      Name(PBAR, 0x318)
      External(PWRG)
      If(CondRefOf(PWRG)){
        Include("Rtd3SataPort.asl")
      }
    }
  }

  If(And(RCG1_RTD3_PRT5_ENABLED, RCG1)) {
    Scope(PRT5){
      Name(PBAR, 0x398)
      External(PWRG)
      If(CondRefOf(PWRG)){
        Include("Rtd3SataPort.asl")
      }
    }
  }

  If(And(RCG1_RTD3_NVM1_ENABLED, RCG1)) {
    Scope(NVM1){
      Include("Rtd3RstRemap.asl")
    }
  }

  If(And(RCG1_RTD3_NVM2_ENABLED, RCG1)) {
    Scope(NVM2){
      Include("Rtd3RstRemap.asl")
    }
  }

  If(And(RCG1_RTD3_NVM3_ENABLED, RCG1)) {
    Scope(NVM3){
      Include("Rtd3RstRemap.asl")
    }
  }
}
