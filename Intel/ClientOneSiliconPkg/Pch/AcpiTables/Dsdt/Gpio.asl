/**@file
 ACPI definition for GPIO controller

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
Include("GpioAcpiDefinesVer3.h")

Scope(\_SB) {
  //----------------------------
  //  GPIO Controller
  //----------------------------
  Device (GPI0)
  {
    Method (_HID) {
      // Return HID based on PCH Product
      Return(GPIO_VER3_ACPI_HID)
    }

    Name (LINK,"\\_SB.GPI0")

    Method (_CRS, 0x0, Serialized) {
        Name(RBFL,ResourceTemplate(){
          Interrupt (ResourceConsumer, Level, ActiveLow, Shared, , , IRQL) { 14 } //Interrupt IRQ_EN
          Memory32Fixed (ReadWrite, 0x00000000, 0x00010000, RBL0)
          Memory32Fixed (ReadWrite, 0x00000000, 0x00010000, RBL1)
          Memory32Fixed (ReadWrite, 0x00000000, 0x00010000, RBL2)
          Memory32Fixed (ReadWrite, 0x00000000, 0x00010000, RBL3)
          Memory32Fixed (ReadWrite, 0x00000000, 0x00010000, RBL4)
          Memory32Fixed (ReadWrite, 0x00000000, 0x00010000, RBL5)
        })

        CreateDWordField(RBFL,IRQL._INT,INTL)
        Store(SGIR,INTL)
        CreateDWordField(RBFL,RBL0._BAS,CML0)
        Store( Add(SBRG,PCH_GPIO_COM0), CML0)
        CreateDWordField(RBFL,RBL1._BAS,CML1)
        Store( Add(SBRG,PCH_GPIO_COM1), CML1)
        CreateDWordField(RBFL,RBL2._BAS,CML2)
        Store( Add(SBRG,PCH_GPIO_COM2), CML2)
        CreateDWordField(RBFL,RBL3._BAS,CML3)
        Store( Add(SBRG,PCH_GPIO_COM3), CML3)
        CreateDWordField(RBFL,RBL4._BAS,CML4)
        Store( Add(SBRG,PCH_GPIO_COM4), CML4)
        CreateDWordField(RBFL,RBL5._BAS,CML5)
        Store( Add(SBRG,PCH_GPIO_COM5), CML5)

        Return(RBFL)
    }

    Method (_STA, 0x0, NotSerialized) {
      If(LEqual(GPHD, 1)) { // Hide GPIO ACPI device
        Return(0x3)
      }
      Return(0xF)
    }
  } // END Device(GPIO)
} // END Scope(\_SB)

