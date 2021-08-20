/** @file
  Intel ACPI Sample Code for connectivity modules

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

Name (SADX, Package()
{
  0,            // Revision, [0-255]
  Package()     // Configuration for WiFi or BT
  {
    0x07,       // DomainType, 0x7:WiFi Core
    0x80000000, // Switched Antenna Diversity Selection, 0:Antenna1, 1:Antenna2, 2:Diversity, 3:Diversity_Antenna1, 4:Diversity_Antenna2
  },
  Package()
  {
    0x12,       // DomainType, 0x12:Bluetooth Core
    0x80000000, // Switched Antenna Diversity Selection, 0:Antenna1, 1:Antenna2, 2:Diversity, 3:Diversity_Antenna1, 4:Diversity_Antenna2
  }
})

// SADS (Switched Antenna Diversity Selection)
//
// Some WiFi modules have one antenna that mux both BT and Wi-Fi. Antenna diversity allows these devices
// to use one of the 2 possible antennas with the following options:
//   1.Antenna1:
//       Wi-Fi and BT are always connected to antenna #1 and switched antenna diversity is disabled.
//   2.Antenna2:
//       Wi-Fi and BT are always connected to antenna #2 and switched antenna diversity is disabled.
//   3.Diversity:
//       Wi-Fi and BT are connected to either antenna #1 or antenna #2, according to Wi-Fi algorithm
//       decision, and switched antenna diversity is enabled.
//   4.Diversity_Antenna1:
//       Wi-Fi and BT are connected to either antenna #1 or antenna #2, according to Wi-Fi algorithm
//       decision, when initially it is connected to antenna #1 and switched antenna diversity is enabled.
//   5.Diversity_Antenna2:
//       Wi-Fi and BT are connected to either antenna #1 or antenna #2, according to Wi-Fi algorithm
//       decision, when initially it is connected to antenna #2 and switched antenna diversity is enabled.
//
// Arguments: (0)
//   None
// Return Value:
//
// Name (SADX, Package()
// {
//   Revision,                            // Revision, [0-255]
//   Package()                            // Configuration for WiFi or BT
//   {
//     DomainType,                        // 0x7:WiFi Core, 0x12:Bluetooth Core
//     SwitchedAntennaDiversitySelection, // 0:Antenna1, 1:Antenna2, 2:Diversity, 3:Diversity_Antenna1, 4:Diversity_Antenna2
//   },
//   Package()                            // Configuration for WiFi or BT
//   {
//     DomainType,                        // 0x7:WiFi Core, 0x12:Bluetooth Core
//     SwitchedAntennaDiversitySelection, // 0:Antenna1, 1:Antenna2, 2:Diversity, 3:Diversity_Antenna1, 4:Diversity_Antenna2
//   }
// })                                     // End of SADX object
//
Method(SADS,0,Serialized)
{
  Store(\ATDV,Index (DeRefOf (Index (SADX, 1)), 1)) // Switched Antenna Diversity Selection
  Store(\ATDV,Index (DeRefOf (Index (SADX, 2)), 1)) // Switched Antenna Diversity Selection

  Return(SADX)
}
