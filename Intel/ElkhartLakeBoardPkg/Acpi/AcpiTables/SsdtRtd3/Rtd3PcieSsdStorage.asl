/** @file
  ACPI RTD3 SSDT table functions for M.2 SSD support

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
// This code should be included in the scope of the PCIe root port that is connected to the M.2 slot
//

  External(PAHC, MethodObj) // Checks if the connected device is AHCI drive
  External(PNVM, MethodObj) // Checks if the connected device is NVME drive

  Name(_S0W,0x04)

  //
  // PCIe D3Cold support hacks ACPI specification in order to work around bug in Windows PCIe driver.
  // For storage we want to return power resources from root port's _PR0 so that we won't get unexpected D3Cold entry.
  //
  If(LOr(PAHC(), PNVM())){
    Method(_PR0, Zero, NotSerialized, 0, PkgObj){
      Return(^^_PR0())
    }
    Method(_PR3, Zero, NotSerialized, 0, PkgObj){
      Return(^^_PR0())
    }
  }

  Method(_PS0,0,Serialized){
  }

  Method(_PS3,0,Serialized){
  }

  Device(MINI){
    Method(_STA,0,Serialized){
      If(PAHC()){
        Return(0x0F)
      }Else {
        Return(0x00)
      }
    }

    //
    // Declare MINI device as a SATA drive connected to the port 0 of the SATA controller
    //
    Name(_ADR,0x0000FFFF)
    Name(_S0W,0x04)

    Method(_PS0,0,Serialized){
    }

    Method(_PS3,0,Serialized){
    }

    //
    // PCIe D3Cold support hacks ACPI specification in order to work around bug in Windows PCIe driver.
    // For storage we want to return power resources from root port's _PR0 so that we won't get unexpected D3Cold entry.
    //
    If(PAHC()){
      Method(_PR0, Zero, NotSerialized, 0, PkgObj){
        Return(^^^_PR0())
      }
      Method(_PR3, Zero, NotSerialized, 0, PkgObj){
        Return(^^^_PR0())
      }
    }
  }

