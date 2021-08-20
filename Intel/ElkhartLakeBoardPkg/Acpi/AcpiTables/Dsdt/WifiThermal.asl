/** @file
  Intel ACPI Sample Code for connectivity modules

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

Name (SPLX, Package()
{
  0,                      // Revision
  Package()
  {
   0x80000000,            // DomainType,         09h: Module; 07h: WiFi/WLAN; 0Fh: WWAN; 10h WiGig; 14h: RFEM
   0x80000000,            // DefaultPowerLimit,  mW
   0x80000000             // DefaultTimeWindow,  ms
  }
}) // End of SPLC object

// SPLC (Static Power Limit Configuration)
//
// The SPLC object evaluates to a package of packages that indicates to each core as well as to
// the Power Sharing Manager the static power limit capabilities to be used as default when
// no dynamic power limit controls are available. For PSM object, the SPLC object can have more
// than package with different domain types to provide default values for various combinations
// of cores. For example, there can be two packages with each package having a DomainType
// value of 1 and 8 respectively to provide different power limit values for the NGFF module and
// the R-FEM module separately.
//
// Arguments: (0)
//   None
// Return Value:
//
// Name (SPLC, Package()
// { // Field Name           Field Type
//   Revision,               // DWordConst
//   Package()               // Default Configuration 1
//   {
//     DomainType,           // 09h: Module; 07h: WiFi/WLAN; 0Fh: WWAN; 10h WiGig; 14h: RFEM
//     DefaultPowerLimit,    // mW
//     DefaultTimeWindow     // ms
//   }
//  }) // End of SPLC object
//
Method(SPLC,0,Serialized)
{
  Store(\DOM1,Index (DeRefOf (Index (SPLX, 1)), 0)) // DomainType
  Store(\LIM1,Index (DeRefOf (Index (SPLX, 1)), 1)) // PowerLimit
  Store(\TIM1,Index (DeRefOf (Index (SPLX, 1)), 2)) // TimeWindow

  Return(SPLX)
}

Name (WANX, Package()
{
  0,                      // Revision, DWordConst
  Package()               // Default Configuration 1
  {
    0x80000000,           // AntennaID, 0:Antenna A, 1:Antenna B
    0x80000000,           // TxRx Delay, possible values 1-100 in 0.1ns resolution (0.1 to 10ns)
    0x80000000            // Antenna CableLength, in 1cm resolution, possible values 1-100
  },
  Package()               // Default Configuration 1
  {
    0x80000000,           // AntennaID, 0:Antenna A, 1:Antenna B
    0x80000000,           // TxRx Delay, possible values 1-100 in 0.1ns resolution (0.1 to 10ns)
    0x80000000            // Antenna CableLength, in 1cm resolution, possible values 1-100
  }
}) // End of WAND object

// WAND (Wireless Antenna Diversity)
//
// Description of the WiFi antennas on the module
//
// Arguments: (0)
//   None
// Return Value:
//
// Name (WAND, Package()
// { // Field Name           Field Type
//   Revision,               // DWordConst
//   Package()               // Default Configuration 1
//   {
//     AntennaID,            // 0:Antenna A, 1:Antenna B
//     TRxDelay,             // nSecDelay, possible values 1-100 in 0.1ns resolution (0.1 to 10ns).
//     TRxCableLength        // cm ; possible values 1-100cm in 1cm resolution.
//   },
//   Package()               // Default Configuration 1
//   {
//     AntennaID,            // 0:Antenna A, 1:Antenna B
//     TRxDelay,             // nSecDelay, possible values 1-100 in 0.1ns resolution (0.1 to 10ns).
//     TRxCableLength        // cm ; possible values 1-100cm in 1cm resolution.
//   }
// }) // End of WAND object
//
Method(WAND,0,Serialized)
{
  Store(0,Index (DeRefOf (Index (WANX, 1)), 0)) // AntennaID 0
  Store(\TRD0,Index (DeRefOf (Index (WANX, 1)), 1)) // TRxDelay 0
  Store(\TRL0,Index (DeRefOf (Index (WANX, 1)), 2))  // TRxCableLength 0

  Store(1,Index (DeRefOf (Index (WANX, 2)), 0)) // AntennaID 1
  Store(\TRD1,Index (DeRefOf (Index (WANX, 2)), 1)) // TRxDelay 1
  Store(\TRL1,Index (DeRefOf (Index (WANX, 2)), 2))  // TRxCableLength 1

  Return(WANX)
}