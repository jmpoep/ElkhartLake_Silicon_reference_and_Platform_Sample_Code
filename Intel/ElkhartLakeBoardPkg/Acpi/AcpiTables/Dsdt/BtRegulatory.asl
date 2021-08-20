/** @file
  Intel ACPI Reference Code for connectivity modules

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

Name (BRDY, Package()
{
  0,                      // Revision, DWordConst
  Package()               // Configuration for Bluetooth
  {
    0x12,                 // DomainType, 0x12:Bluetooth Core
    0x80,                 // Bluetooth SAR Enable/Disable
    0x80,                 // Bluetooth SAR BR Modulation
    0x80,                 // Bluetooth SAR EDR2 Modulation
    0x80,                 // Bluetooth SAR EDR3 Modulation
    0x80,                 // Bluetooth SAR LE Modulation
    0x80,                 // Bluetooth SAR LE 2Mhz Modulation
    0x80,                 // Bluetooth SAR LE LR Modulation
  }
})                        // End of BRDY object

// BRDS (Bluetooth wireless Regulatory Domain SAR)
//
// Bluetooth has regulatory limitations which prohibit or allow usage of certain bands or channels as well as limiting the Tx power.
// This method is used to modify the Bluetooth SAR Tx Power Limit to properly control it
//
// Arguments: (0)
//   None
// Return Value:
//
// Name (BRDS, Package()
// {
//   Revision,                        // DWordConst
//   Package()                        // Configuration for Bluetooth
//   {
//     DomainType,                    // DomainType, 0x12:Bluetooth Core
//     BluetoothSar,                  // Define the mode of SAR control to be used.0: Tx power shall be mandated by device NVM; 1: Tx power shall be the minimum between BIOS SAR table and BT Device NVM (either Module or Platform)
//     BluetoothSarBrModulation,      // Bluetooth SAR BR Modulation
//     BluetoothSarEdr2Modulation,    // Bluetooth SAR EDR2 Modulation
//     BluetoothSarEdr3Modulation,    // Bluetooth SAR EDR3 Modulation
//     BluetoothSarLeModulation,      // Bluetooth SAR LE Modulation
//     BluetoothSarLe2MhzModulation,  // Bluetooth SAR LE 2Mhz Modulation
//     BluetoothSarLeLrModulation,    // Bluetooth SAR LE LR Modulation
//   }
// })                                 // End of BRDS object
//

Method(BRDS,0,Serialized)
{
  Store(\BTSE,Index (DeRefOf (Index (BRDY, 1)), 1))  // Bluetooth SAR Enable/Disable
  Store(\BTBR,Index (DeRefOf (Index (BRDY, 1)), 2))  // Bluetooth SAR BR Modulation
  Store(\BED2,Index (DeRefOf (Index (BRDY, 1)), 3))  // Bluetooth SAR EDR2 Modulation
  Store(\BED3,Index (DeRefOf (Index (BRDY, 1)), 4))  // Bluetooth SAR EDR3 Modulation
  Store(\BTLE,Index (DeRefOf (Index (BRDY, 1)), 5))  // Bluetooth SAR LE Modulation
  Store(\BTL2,Index (DeRefOf (Index (BRDY, 1)), 6))  // Bluetooth SAR LE 2Mhz Modulation
  Store(\BTLL,Index (DeRefOf (Index (BRDY, 1)), 7))  // Bluetooth SAR LE LR Modulation

  Return(BRDY)
}
