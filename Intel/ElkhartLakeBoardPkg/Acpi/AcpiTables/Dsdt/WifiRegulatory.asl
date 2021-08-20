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

Name (WRDX, Package()
{
  0,                      // Revision, [0-255]
  Package()               // Configuration for WiFi
  {
    0x80000000,           // DomainType, 0x7:WiFi Core
    0x8000,               // RegulatoryDomain, Country identifier as defined in ISO/IEC 3166-1 Alpha 2 code
  }
})                        // End of WRDD object

// WRDD (Wireless Regulatory Domain Description)
//
// WiFi has regulatory limitations which prohibit or allow usage of certain bands or channels as well as limiting the Tx power.
// Those settings are different per country (or groups of countries). In order to reduce the number of
// HW SKUs the direction is now to include platform level ACPI setting that determines the country.
// WiFi driver shall read the WRDD object during initialization process and shall configure uCode to apply the right regulatory limits.
//
// Arguments: (0)
//   None
// Return Value:
//
// Name (WRDD, Package()
// {
//   Revision,               // Revision, [0-255]
//   Package()               // Configuration for WiFi
//   {
//     DomainType,           // 0x7:WiFi  Core
//     RegulatoryDomain,     // Country identifier as defined in ISO/IEC 3166-1 Alpha 2 code
//   }
// })                        // End of WRDD object
//
Method(WRDD,0,Serialized)
{
  Store(\WDM1,Index (DeRefOf (Index (WRDX, 1)), 0)) // DomainType
  Store(\CID1,Index (DeRefOf (Index (WRDX, 1)), 1)) // Country identifier

  Return(WRDX)
}

Name (WRDY, Package()
{
  0,                      // Revision, DWordConst
  Package()               // Configuration for WiFi
  {
    0x07,                 // DomainType, 0x7:WiFi
    0x80,                 // WiFi SAR Enable/Disable
    0x80,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 1 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 1 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 1 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 1 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 1 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 1 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 1 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 1 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 1 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 1 Chain B
  }
})                        // End of WRDD object

// WRDS (Wireless Regulatory Domain SAR)
//
// WiFi has regulatory limitations which prohibit or allow usage of certain bands or channels as well as limiting the Tx power.
// This method is used to modify the WiFi SAR Tx Power Limit to properly control it
//
// Arguments: (0)
//   None
// Return Value:
//
// Name (WRDS, Package()
// {
//   Revision,                // DWordConst
//   Package()                // Configuration for WiFi
//   {
//     DomainType,            // 0x7:WiFi
//     WiFiSarEnable,         // Configures the source location of the WiFi SAR table to be used; 0:Device ignores BIOS configuration; 1:Device uses BIOS configuration
//     WiFiSarTxPowerLimit1,  // WiFi SAR Tx Power Limit for 2400 MHz Chain A
//     WiFiSarTxPowerLimit2,  // WiFi SAR Tx Power Limit for 5150-5350 MHz Chain A
//     WiFiSarTxPowerLimit3,  // WiFi SAR Tx Power Limit for 5350-5470 MHz Chain A
//     WiFiSarTxPowerLimit4,  // WiFi SAR Tx Power Limit for 5470-5725 MHz Chain A
//     WiFiSarTxPowerLimit5,  // WiFi SAR Tx Power Limit for 5725-5950 MHz Chain A
//     WiFiSarTxPowerLimit6,  // WiFi SAR Tx Power Limit for 2400 MHz Chain B
//     WiFiSarTxPowerLimit7,  // WiFi SAR Tx Power Limit for 5150-5350 MHz Chain B
//     WiFiSarTxPowerLimit8,  // WiFi SAR Tx Power Limit for 5350-5470 MHz Chain B
//     WiFiSarTxPowerLimit9,  // WiFi SAR Tx Power Limit for 5470-5725 MHz Chain B
//     WiFiSarTxPowerLimit10, // WiFi SAR Tx Power Limit for 5725-5950 MHz Chain B
//   }
// })                         // End of WRDS object
//

Method(WRDS,0,Serialized)
{
  Store(\STXE,Index (DeRefOf (Index (WRDY, 1)), 1))  // WiFi SAR Enable/Disable
  Store(\ST10,Index (DeRefOf (Index (WRDY, 1)), 2))  // WiFi SAR Tx Power Limit for 2400 MHz Set 1 Chain A
  Store(\ST11,Index (DeRefOf (Index (WRDY, 1)), 3))  // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 1 Chain A
  Store(\ST12,Index (DeRefOf (Index (WRDY, 1)), 4))  // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 1 Chain A
  Store(\ST13,Index (DeRefOf (Index (WRDY, 1)), 5))  // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 1 Chain A
  Store(\ST14,Index (DeRefOf (Index (WRDY, 1)), 6))  // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 1 Chain A
  Store(\ST15,Index (DeRefOf (Index (WRDY, 1)), 7))  // WiFi SAR Tx Power Limit for 2400 MHz Set 1 Chain B
  Store(\ST16,Index (DeRefOf (Index (WRDY, 1)), 8))  // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 1 Chain B
  Store(\ST17,Index (DeRefOf (Index (WRDY, 1)), 9))  // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 1 Chain B
  Store(\ST18,Index (DeRefOf (Index (WRDY, 1)), 10)) // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 1 Chain B
  Store(\ST19,Index (DeRefOf (Index (WRDY, 1)), 11)) // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 1 Chain B

  Return(WRDY)
}

Name (EWRY, Package()
{
  0,                      // Revision, DWordConst
  Package()               // Configuration for WiFi
  {
    0x07,                 // DomainType, 0x7:WiFi
    0x80,                 // WiFi Dynamic SAR Enable/Disable
    0x80,                 // WiFi SAR Number of Optional added SAR table sets to be used
    0x80,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 2 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 2 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 2 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 2 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 2 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 2 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 2 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 2 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 2 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 2 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 3 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 3 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 3 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 3 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 3 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 3 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 3 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 3 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 3 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 3 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 4 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 4 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 4 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 4 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 4 Chain A
    0x80,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 4 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 4 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 4 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 4 Chain B
    0x80,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 4 Chain B
  }
})                        // End of EWRY object

// EWRD (Extended Wireless Regulatory Domain SAR)
//
// WiFi has regulatory limitations which prohibit or allow usage of certain bands or channels as well as limiting the Tx power.
// This method is used to modify the WiFi SAR Tx Power Limit to properly control it
// This adds Three more Sets in addition to the Set defined in WRDS
//
// Arguments: (0)
//   None
// Return Value:
//
//Name (EWRY, Package()
//{
//  Revision,                                       // Revision, DWordConst
//  Package()                                       // Configuration for WiFi
//  {
//    DomainType,                                   // DomainType, 0x7:WiFi
//    EwrdWiFiDynamicSarEnable,                     // WiFi Dynamic SAR Enable/Disable
//    EwrdWiFiDynamicSarRangeSets,                  // WiFi SAR Number of Optional added SAR table sets to be used
//    EwrdWiFiSarTxPowerSet2Limit1,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 2 Chain A
//    EwrdWiFiSarTxPowerSet2Limit2,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 2 Chain A
//    EwrdWiFiSarTxPowerSet2Limit3,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 2 Chain A
//    EwrdWiFiSarTxPowerSet2Limit4,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 2 Chain A
//    EwrdWiFiSarTxPowerSet2Limit5,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 2 Chain A
//    EwrdWiFiSarTxPowerSet2Limit6,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 2 Chain B
//    EwrdWiFiSarTxPowerSet2Limit7,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 2 Chain B
//    EwrdWiFiSarTxPowerSet2Limit8,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 2 Chain B
//    EwrdWiFiSarTxPowerSet2Limit9,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 2 Chain B
//    EwrdWiFiSarTxPowerSet2Limit10,                // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 2 Chain B
//    EwrdWiFiSarTxPowerSet3Limit1,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 3 Chain A
//    EwrdWiFiSarTxPowerSet3Limit2,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 3 Chain A
//    EwrdWiFiSarTxPowerSet3Limit3,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 3 Chain A
//    EwrdWiFiSarTxPowerSet3Limit4,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 3 Chain A
//    EwrdWiFiSarTxPowerSet3Limit5,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 3 Chain A
//    EwrdWiFiSarTxPowerSet3Limit6,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 3 Chain B
//    EwrdWiFiSarTxPowerSet3Limit7,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 3 Chain B
//    EwrdWiFiSarTxPowerSet3Limit8,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 3 Chain B
//    EwrdWiFiSarTxPowerSet3Limit9,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 3 Chain B
//    EwrdWiFiSarTxPowerSet3Limit10,                // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 3 Chain B
//    EwrdWiFiSarTxPowerSet4Limit1,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 4 Chain A
//    EwrdWiFiSarTxPowerSet4Limit2,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 4 Chain A
//    EwrdWiFiSarTxPowerSet4Limit3,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 4 Chain A
//    EwrdWiFiSarTxPowerSet4Limit4,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 4 Chain A
//    EwrdWiFiSarTxPowerSet4Limit5,                 // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 4 Chain A
//    EwrdWiFiSarTxPowerSet4Limit6,                 // WiFi SAR Tx Power Limit for 2400 MHz Set 4 Chain B
//    EwrdWiFiSarTxPowerSet4Limit7,                 // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 4 Chain B
//    EwrdWiFiSarTxPowerSet4Limit8,                 // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 4 Chain B
//    EwrdWiFiSarTxPowerSet4Limit9,                 // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 4 Chain B
//    EwrdWiFiSarTxPowerSet4Limit10,                // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 4 Chain B
//  }
//})                        // End of EWRD object
//
Method(EWRD,0,Serialized)
{
  Store(\STDE,Index (DeRefOf (Index (EWRY, 1)), 1))  // WiFi Dynamic SAR Enable/Disable
  Store(\STRS,Index (DeRefOf (Index (EWRY, 1)), 2))  // WiFi SAR Number of Optional added SAR table sets to be used
  Store(\ST20,Index (DeRefOf (Index (EWRY, 1)), 3))  // WiFi SAR Tx Power Limit for 2400 MHz Set 2 Chain A
  Store(\ST21,Index (DeRefOf (Index (EWRY, 1)), 4))  // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 2 Chain A
  Store(\ST22,Index (DeRefOf (Index (EWRY, 1)), 5))  // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 2 Chain A
  Store(\ST23,Index (DeRefOf (Index (EWRY, 1)), 6))  // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 2 Chain A
  Store(\ST24,Index (DeRefOf (Index (EWRY, 1)), 7))  // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 2 Chain A
  Store(\ST25,Index (DeRefOf (Index (EWRY, 1)), 8))  // WiFi SAR Tx Power Limit for 2400 MHz Set 2 Chain B
  Store(\ST26,Index (DeRefOf (Index (EWRY, 1)), 9))  // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 2 Chain B
  Store(\ST27,Index (DeRefOf (Index (EWRY, 1)), 10)) // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 2 Chain B
  Store(\ST28,Index (DeRefOf (Index (EWRY, 1)), 11)) // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 2 Chain B
  Store(\ST29,Index (DeRefOf (Index (EWRY, 1)), 12)) // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 2 Chain B

  Store(\ST30,Index (DeRefOf (Index (EWRY, 1)), 13)) // WiFi SAR Tx Power Limit for 2400 MHz Set 3 Chain A
  Store(\ST31,Index (DeRefOf (Index (EWRY, 1)), 14)) // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 3 Chain A
  Store(\ST32,Index (DeRefOf (Index (EWRY, 1)), 15)) // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 3 Chain A
  Store(\ST33,Index (DeRefOf (Index (EWRY, 1)), 16)) // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 3 Chain A
  Store(\ST34,Index (DeRefOf (Index (EWRY, 1)), 17)) // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 3 Chain A
  Store(\ST35,Index (DeRefOf (Index (EWRY, 1)), 18)) // WiFi SAR Tx Power Limit for 2400 MHz Set 3 Chain B
  Store(\ST36,Index (DeRefOf (Index (EWRY, 1)), 19)) // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 3 Chain B
  Store(\ST37,Index (DeRefOf (Index (EWRY, 1)), 20)) // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 3 Chain B
  Store(\ST38,Index (DeRefOf (Index (EWRY, 1)), 21)) // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 3 Chain B
  Store(\ST39,Index (DeRefOf (Index (EWRY, 1)), 22)) // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 3 Chain B

  Store(\ST40,Index (DeRefOf (Index (EWRY, 1)), 23)) // WiFi SAR Tx Power Limit for 2400 MHz Set 4 Chain A
  Store(\ST41,Index (DeRefOf (Index (EWRY, 1)), 24)) // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 4 Chain A
  Store(\ST42,Index (DeRefOf (Index (EWRY, 1)), 25)) // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 4 Chain A
  Store(\ST43,Index (DeRefOf (Index (EWRY, 1)), 26)) // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 4 Chain A
  Store(\ST44,Index (DeRefOf (Index (EWRY, 1)), 27)) // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 4 Chain A
  Store(\ST45,Index (DeRefOf (Index (EWRY, 1)), 28)) // WiFi SAR Tx Power Limit for 2400 MHz Set 4 Chain B
  Store(\ST46,Index (DeRefOf (Index (EWRY, 1)), 29)) // WiFi SAR Tx Power Limit for 5150-5350 MHz Set 4 Chain B
  Store(\ST47,Index (DeRefOf (Index (EWRY, 1)), 30)) // WiFi SAR Tx Power Limit for 5350-5470 MHz Set 4 Chain B
  Store(\ST48,Index (DeRefOf (Index (EWRY, 1)), 31)) // WiFi SAR Tx Power Limit for 5470-5725 MHz Set 4 Chain B
  Store(\ST49,Index (DeRefOf (Index (EWRY, 1)), 32)) // WiFi SAR Tx Power Limit for 5725-5950 MHz Set 4 Chain B

  Return(EWRY)
}

Name (WGDY, Package()
{
  0,                      // Revision, DWordConst
  Package()               // Configuration for WiFi
  {
    0x07,                 // DomainType, 0x7:WiFi
    0x80,                 // WiFi output power delta for Group 1 FCC 2400 MHZ Max Allowed
    0x80,                 // WiFi output power delta for Group 1 FCC 2400 Chain A Offset
    0x80,                 // WiFi output power delta for Group 1 FCC 2400 Chain B Offset
    0x80,                 // WiFi output power delta for Group 1 FCC 5200 MHZ Max Allowed
    0x80,                 // WiFi output power delta for Group 1 FCC 5200 Chain A Offset
    0x80,                 // WiFi output power delta for Group 1 FCC 5200 Chain B Offset
    0x80,                 // WiFi output power delta for Group 2 EC Japan 2400 MHZ Max Allowed
    0x80,                 // WiFi output power delta for Group 2 EC Japan 2400 Chain A Offset
    0x80,                 // WiFi output power delta for Group 2 EC Japan 2400 Chain B Offset
    0x80,                 // WiFi output power delta for Group 2 EC Japan 5200 MHZ Max Allowed
    0x80,                 // WiFi output power delta for Group 2 EC Japan 5200 Chain A Offset
    0x80,                 // WiFi output power delta for Group 2 EC Japan 5200 Chain B Offset
    0x80,                 // WiFi output power delta for Group 3 ROW 2400 MHZ Max Allowed
    0x80,                 // WiFi output power delta for Group 3 ROW 2400 Chain A Offset
    0x80,                 // WiFi output power delta for Group 3 ROW 2400 Chain B Offset
    0x80,                 // WiFi output power delta for Group 3 ROW 5200 MHZ Max Allowed
    0x80,                 // WiFi output power delta for Group 3 ROW 5200 Chain A Offset
    0x80,                 // WiFi output power delta for Group 3 ROW 5200 Chain B Offset
  }
})                        // End of WGDY object

// WGDS (Wireless Geo Delta Settings)
//
// Defines the output power delta of the current SAR set, this value will allow an increased Tx power
// compared to the default (Canada) BIOS SAR settings in case DRS mechanism
// has detected country that is compatible with Europe regulations
//
//
// Arguments: (0)
//   None
// Return Value:
//
// Name (WGDY, Package()
// {
//  Revision,                                      // Revision, DWordConst
//  Package()                                      // Configuration for WiFi
//  {
//    DomainType,                                  // DomainType, 0x7:WiFi
//    WgdsWiFiSarDeltaGroup1PowerMax1,             // WiFi output power delta for Group 1 FCC 2400 MHZ Max Allowed
//    WgdsWiFiSarDeltaGroup1PowerChainA1,          // WiFi output power delta for Group 1 FCC 2400 Chain A Offset
//    WgdsWiFiSarDeltaGroup1PowerChainB1,          // WiFi output power delta for Group 1 FCC 2400 Chain B Offset
//    WgdsWiFiSarDeltaGroup1PowerMax2,             // WiFi output power delta for Group 1 FCC 5200 MHZ Max Allowed
//    WgdsWiFiSarDeltaGroup1PowerChainA2,          // WiFi output power delta for Group 1 FCC 5200 Chain A Offset
//    WgdsWiFiSarDeltaGroup1PowerChainB2,          // WiFi output power delta for Group 1 FCC 5200 Chain B Offset
//    WgdsWiFiSarDeltaGroup2PowerMax1,             // WiFi output power delta for Group 2 EC Japan 2400 MHZ Max Allowed
//    WgdsWiFiSarDeltaGroup2PowerChainA1,          // WiFi output power delta for Group 2 EC Japan 2400 Chain A Offset
//    WgdsWiFiSarDeltaGroup2PowerChainB1,          // WiFi output power delta for Group 2 EC Japan 2400 Chain B Offset
//    WgdsWiFiSarDeltaGroup2PowerMax2,             // WiFi output power delta for Group 2 EC Japan 5200 MHZ Max Allowed
//    WgdsWiFiSarDeltaGroup2PowerChainA2,          // WiFi output power delta for Group 2 EC Japan 5200 Chain A Offset
//    WgdsWiFiSarDeltaGroup2PowerChainB2,          // WiFi output power delta for Group 2 EC Japan 5200 Chain B Offset
//    WgdsWiFiSarDeltaGroup3PowerMax1,             // WiFi output power delta for Group 3 ROW 2400 MHZ Max Allowed
//    WgdsWiFiSarDeltaGroup3PowerChainA1,          // WiFi output power delta for Group 3 ROW 2400 Chain A Offset
//    WgdsWiFiSarDeltaGroup3PowerChainB1,          // WiFi output power delta for Group 3 ROW 2400 Chain B Offset
//    WgdsWiFiSarDeltaGroup3PowerMax2,             // WiFi output power delta for Group 3 ROW 5200 MHZ Max Allowed
//    WgdsWiFiSarDeltaGroup3PowerChainA2,          // WiFi output power delta for Group 3 ROW 5200 Chain A Offset
//    WgdsWiFiSarDeltaGroup3PowerChainB2,          // WiFi output power delta for Group 3 ROW 5200 Chain B Offset
//  }
//})                        // End of WGDS object
//
Method(WGDS,0,Serialized)
{
  Store(\SD11,Index (DeRefOf (Index (WGDY, 1)), 1)) // WiFi output power delta for Group 1 FCC 2400 MHZ Max Allowed
  Store(\SD12,Index (DeRefOf (Index (WGDY, 1)), 2)) // WiFi output power delta for Group 1 FCC 2400 Chain A Offset
  Store(\SD13,Index (DeRefOf (Index (WGDY, 1)), 3)) // WiFi output power delta for Group 1 FCC 2400 Chain B Offset
  Store(\SD14,Index (DeRefOf (Index (WGDY, 1)), 4)) // WiFi output power delta for Group 1 FCC 5200 MHZ Max Allowed
  Store(\SD15,Index (DeRefOf (Index (WGDY, 1)), 5)) // WiFi output power delta for Group 1 FCC 5200 Chain A Offset
  Store(\SD16,Index (DeRefOf (Index (WGDY, 1)), 6)) // WiFi output power delta for Group 1 FCC 5200 Chain B Offset
  Store(\SD21,Index (DeRefOf (Index (WGDY, 1)), 7)) // WiFi output power delta for Group 2 EC Japan 2400 MHZ Max Allowed
  Store(\SD22,Index (DeRefOf (Index (WGDY, 1)), 8)) // WiFi output power delta for Group 2 EC Japan 2400 Chain A Offset
  Store(\SD23,Index (DeRefOf (Index (WGDY, 1)), 9)) // WiFi output power delta for Group 2 EC Japan 2400 Chain B Offset
  Store(\SD24,Index (DeRefOf (Index (WGDY, 1)), 10)) // WiFi output power delta for Group 2 EC Japan 5200 MHZ Max Allowed
  Store(\SD25,Index (DeRefOf (Index (WGDY, 1)), 11)) // WiFi output power delta for Group 2 EC Japan 5200 Chain A Offset
  Store(\SD26,Index (DeRefOf (Index (WGDY, 1)), 12)) // WiFi output power delta for Group 2 EC Japan 5200 Chain B Offset
  Store(\SD31,Index (DeRefOf (Index (WGDY, 1)), 13)) // WiFi output power delta for Group 3 ROW 2400 MHZ Max Allowed
  Store(\SD32,Index (DeRefOf (Index (WGDY, 1)), 14)) // WiFi output power delta for Group 3 ROW 2400 Chain A Offset
  Store(\SD33,Index (DeRefOf (Index (WGDY, 1)), 15)) // WiFi output power delta for Group 3 ROW 2400 Chain B Offset
  Store(\SD34,Index (DeRefOf (Index (WGDY, 1)), 16)) // WiFi output power delta for Group 3 ROW 5200 MHZ Max Allowed
  Store(\SD35,Index (DeRefOf (Index (WGDY, 1)), 17)) // WiFi output power delta for Group 3 ROW 5200 Chain A Offset
  Store(\SD36,Index (DeRefOf (Index (WGDY, 1)), 18)) /// WiFi output power delta for Group 3 ROW 5200 Chain B Offset

  Return(WGDY)
}
