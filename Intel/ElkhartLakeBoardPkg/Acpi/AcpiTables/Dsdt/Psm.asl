/** @file
  Intel ACPI Reference Code for Dynamic Platform & Thermal Framework

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


Device(PSM)
{
  Name(_HID, EISAID("INT3420"))
  Name(_UID, 0)
  Name(_STR, Unicode ("Power Sharing Manager"))

  // _STA (Status)
  //
  // This object returns the current status of a device.
  //
  // Arguments: (0)
  //   None
  // Return Value:
  //   An Integer containing a device status bitmap:
  //    Bit 0 - Set if the device is present.
  //    Bit 1 - Set if the device is enabled and decoding its resources.
  //    Bit 2 - Set if the device should be shown in the UI.
  //    Bit 3 - Set if the device is functioning properly (cleared if device failed its diagnostics).
  //    Bit 4 - Set if the battery is present.
  //    Bits 5-31 - Reserved (must be cleared).
  //
  Method(_STA,0)
  {
    If(LEqual(PSME,1)){
      Return(0x0F)
    } Else {
      Return(0x00)
    }
  }

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
    Store(\PDT1,Index (DeRefOf (Index (SPLX, 1)), 0)) // DomainType
    Store(\PLM1,Index (DeRefOf (Index (SPLX, 1)), 1)) // PowerLimit
    Store(\PTW1,Index (DeRefOf (Index (SPLX, 1)), 2)) // TimeWindow

    Return(SPLX)
  }

  Name (DPLX, Package()
  {
    0,                      // DWordConst
    Package()               // Power Limit Configuration 1
    {
      0x80000000,           // DomainType, 09h: Module; 07h: WiFi/WLAN; 0Fh: WWAN; 10h WiGig; 14h: RFEM
      0x80000000,           // DomainPreference, DWordConst
      Package()
      {
        0x80000000,         // PowerLimitIndex, 0 based index
        0x80000000,         // DefaultPowerLimit, mW
        0x80000000,         // DefaultTimeWindow, ms
        0x80000000,         // MinimumPowerLimit, mW
        0x80000000,         // MaximumPowerLimit, mW
        0x80000000          // MaximumTimeWindow, ms
      }
    }
  }) // End of DPLC object

  // DPLC (Dynamic Power Limit Configuration)
  //
  // The DPLC object evaluates to a package of packages that indicates to each core as well as to the
  // Power Sharing Manager the dynamic power limit capabilities to be used for runtime control,
  // including the power control range and time window range that must be used during any power
  // limiting control/usage. For PSM object, the DPLC object can have more than one package with
  // different domain types to provide power limit ranges for various combinations of cores.
  // For example, there can be two packages with each package having a DomainType value of 3 and
  // 4 respectively to provide different power limit ranges for the NGFF module and the R-FEM
  // module separately.
  //
  // Arguments: (0)
  //   None
  // Return Value:
  //
  //  Name (DPLC, Package()
  //  { // Field Name           Field Type
  //    Revision,               // DWordConst
  //    Package()               // Power Limit Configuration 1
  //    {
  //      DomainType,           // 09h: Module; 07h: WiFi/WLAN; 0Fh: WWAN; 10h WiGig; 14h: RFEM
  //      DomainPreference,     // DWordConst
  //      Package()
  //      {
  //        PowerLimitIndex,    // 0 based index
  //        DefaultPowerLimit,  // mW
  //        DefaultTimeWindow,  // ms
  //        MinimumPowerLimit,  // mW
  //        MaximumPowerLimit,  // mW
  //        MaximumTimeWindow   // ms
  //      }
  //  }) // End of DPLC object
  //
  Method(DPLC,0,Serialized)
  {
    Store(\DDT1,Index (DeRefOf (Index (DPLX, 1)), 0)) // DomainType
    Store(\DDP1,Index (DeRefOf (Index (DPLX, 1)), 1)) // DomainPreference
    Store(\DLI1,Index (DeRefOf (Index (DeRefOf (Index (DPLX, 1)), 2)),0)) // PowerLimitIndex
    Store(\DPL1,Index (DeRefOf (Index (DeRefOf (Index (DPLX, 1)), 2)),1)) // DefaultPowerLimit
    Store(\DTW1,Index (DeRefOf (Index (DeRefOf (Index (DPLX, 1)), 2)),2)) // DefaultTimeWindow
    Store(\DMI1,Index (DeRefOf (Index (DeRefOf (Index (DPLX, 1)), 2)),3)) // MinimumPowerLimit
    Store(\DMA1,Index (DeRefOf (Index (DeRefOf (Index (DPLX, 1)), 2)),4)) // MaximumPowerLimit
    Store(\DMT1,Index (DeRefOf (Index (DeRefOf (Index (DPLX, 1)), 2)),5)) // MaximumTimeWindow

    Return(DPLX)
  }
}// end Device PSM

