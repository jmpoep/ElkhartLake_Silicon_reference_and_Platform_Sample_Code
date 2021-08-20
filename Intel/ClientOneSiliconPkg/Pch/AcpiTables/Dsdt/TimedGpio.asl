/**@file
  ACPI definition for Timed GPIO controller

  @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.
**/
  //----------------------------
  //  Timed GPIO
  //----------------------------
#include <Register/PmcRegs.h>

Scope(\_SB) {

  If (LEqual(TGEA,1)) {
    Device (TGIA){
      Name(_HID, "INTC1021")
      Name(_STR, Unicode ("Timed GPIO 1"))
      Method (_STA, 0x0, NotSerialized) {
          Return (0xF)
      }
      Method (_CRS, 0x0, Serialized) {
        Name(TGRA,ResourceTemplate() {
          Memory32Fixed (ReadWrite, 0x0,0x38, TGA1)
        })
        CreateDWordField(TGRA,TGA1._BAS,TMH1)
        Store( Add(PWRM,R_PMC_PWRM_TIMED_GPIO_CONTROL_0), TMH1)
        Return(TGRA)
      }
    } // END Device(TGIA)
  } // end if TGEA

  If (LEqual(TGEB,1)) {
    Device (TGIB){
      Name(_HID, "INTC1022")
      Name(_STR, Unicode ("Timed GPIO 2"))
      Method (_STA, 0x0, NotSerialized) {
          Return (0xF)
      }
      Method (_CRS, 0x0, Serialized) {
        Name(TGRB,ResourceTemplate() {
          Memory32Fixed (ReadWrite, 0x0,0x38, TGA2)
        })
        CreateDWordField(TGRB,TGA2._BAS,TMH2)
        Store( Add(PWRM,R_PMC_PWRM_TIMED_GPIO_CONTROL_1), TMH2)
        Return(TGRB)
      }
    } // END Device(TGIB)
  } // end if TGEB
} // END Scope
