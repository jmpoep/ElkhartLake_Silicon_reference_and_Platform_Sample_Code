/** @file
  ACPI uPEP Support for PCIe SSD

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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

  // Include PepPcieSsd.asl for PCIe SSD PEP support
  // Input parameters:

  Method(_DEP){
    If(LOr(PAHC(), PNVM())){ // Check if PCIe AHCI controller or NVMe
      If(LAnd(LEqual(S0ID, 1), LEqual(OSYS, 2012))) {  // If OS is Win8 and S0ix enabled, associate PCIe storage PEP with SATA PEP due to OS limitation
        If(LEqual(And(PEPC, BIT0), 1)) {  // BIT0 set means Adapter D0/F1 or D3
          Return(Package() {\_SB.PEPD})
        }
      }
      If(LAnd(LEqual(S0ID, 1),LGreaterEqual(OSYS, 2015))) {  // If OS is Win10 onward and S0ix enabled, PCIe storage PEP would be reported
        Return(Package() {\_SB.PEPD})
      }
    }
    Return(Package(){})
  }

  OperationRegion(PCCX,PCI_Config,0x09,4) // PCI Config Space Class Code
  Field(PCCX,ByteAcc, NoLock, Preserve) {
    PIXX, 8, // Programming Interface
    SCCX, 8, // Sub Class Code
    BCCX, 8, // Base Class Code
  }

  Method(PAHC, Zero, Serialized) // Check if PCIe AHCI Controller
  {
    If(LEqual(BCCX, 0x01)){ // Check Sub Class Code and Base Class Code
      If(LEqual(SCCX, 0x06)){
        If(LEqual(PIXX, 0x01)){
          Return(0x01)
        }
      }
    }
    Return(0x00)
  }

  Method(PNVM, Zero, Serialized) // Check if PCIe NVMe
  {
    If(LEqual(BCCX, 0x01)){ // Check Sub Class Code and Base Class Code
      If(LEqual(SCCX, 0x08)){
        If(LEqual(PIXX, 0x02)){
          Return(0x01)
        }
      }
    }
    Return(0x00)
  }

