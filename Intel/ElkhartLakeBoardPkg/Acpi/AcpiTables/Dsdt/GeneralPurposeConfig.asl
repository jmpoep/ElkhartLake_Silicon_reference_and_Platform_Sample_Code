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

Name (GPCX, Package()
{
  0,                      // Revision, DWordConst
  Package()               // Configuration for WiFi
  {
    0x07,                 // DomainType, 0x7:WiFi
    Package()
    {
      0,                  // Type:   0 - End of TLV structure
      0,                  // Length: 0
      0,                  // Value:  0
    },
  },
  Package()               // Configuration for Bluetooth
  {
    0x12,                 // DomainType, 0x12:Bluetooth Core
    Package()
    {
      0,                  // Type:   0 - End of TLV structure
      0,                  // Length: 0
      0,                  // Value:  0
    },
  }
})

// GPC (General Purpose Configuration)
//
// The general purpose configuration method allows a general purpose configuration/communication
// between BIOS and CNV Core's drivers. It allows OEM specific & platform specific configuration
// notifications to Core's drivers.
//
// Arguments: (0)
//   None
// Return Value:
//
// Name (GPCX, Package()
// {
//   0,                      // Revision, DWordConst
//   Package()               // Configuration for WiFi or BT
//   {
//     DomainType,           // 0x7:WiFi  Core, 0x12:Bluetooth Core
//     Package()             // TLV#1
//     {
//       Type,               // The type of configuration which is defined in the structure
//       Length,             // The length of the value
//       Value,              // The value/data of the type
//     },
//     :
//     Package()             // TLV#n
//     {
//       0,                  // Type 0: End of TLV structure
//       0,
//       0,
//     },
//   },
//   Package()               // Configuration for WiFi or BT
//   {
//     DomainType,           // 0x7:WiFi  Core, 0x12:Bluetooth Core
//     Package()             // TLV#1
//     {
//       Type,               // The type of configuration which is defined in the structure
//       Length,             // The length of the value
//       Value,              // The value/data of the type
//     },
//     :
//     Package()             // TLV#n
//     {
//       0,                  // Type 0: End of TLV structure
//       0,
//       0,
//     },
//   }
// })
//
Method(GPC,0,Serialized)
{
  Return(GPCX)
}
