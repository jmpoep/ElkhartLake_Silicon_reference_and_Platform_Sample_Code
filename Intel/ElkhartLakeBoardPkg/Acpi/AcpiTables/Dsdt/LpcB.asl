/** @file
  ACPI DSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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


// LPC Bridge - Device 31, Function 0
scope (\_SB.PC00.LPCB) {
#ifdef EC_SUPPORT
      Include ("EC.ASL")
#endif
      Include ("LpcDev.asl")
      Include ("NatSio.asl")
      Include ("Wpcn381USio.asl")
      Include ("H8S2113Sio.asl")
      Include ("Nct6776FSio.asl")

      // Define the KBC_COMMAND_REG-64, KBC_DATA_REG-60 Registers as an ACPI Operating
      // Region.  These registers will be used to skip kbd mouse
      // resource settings if not present.
      OperationRegion(PKBS, SystemIO, 0x60, 0x05)
      Field(PKBS, ByteAcc, Lock, Preserve)
      {
        PKBD, 8,
        , 8,
        , 8,
        , 8,
        PKBC, 8
      }
      Device(PS2K)    // PS2 Keyboard
      {
        Name(_HID,"MSFT0001")
        Name(_CID,EISAID("PNP0303"))

        Method(_STA)
        {
          If (P2MK) //Ps2 Keyboard and Mouse Enable
          {
            Return(0x000F)
          }
          Return(0x0000)
        }

        Name(_CRS,ResourceTemplate()
        {
          IO(Decode16,0x60,0x60,0x01,0x01)
          IO(Decode16,0x64,0x64,0x01,0x01)
          IRQ(Edge,ActiveHigh,Exclusive){0x01}
        })

        Name(_PRS, ResourceTemplate(){
          StartDependentFn(0, 0) {
          FixedIO(0x60,0x01)
          FixedIO(0x64,0x01)
          IRQNoFlags(){1}
          }
          EndDependentFn()
        })

      }

      Device(PS2M)    // PS/2 Mouse
      {
        Name(_HID,"MSFT0003")
        Name(_CID,EISAID("PNP0F03"))

        Method(_STA)
        {
          If (P2ME) //Ps2 Mouse Enable
          {
            If (P2MK) //Ps2 Keyboard and Mouse Enable
            {
              Return(0x000F)
            }
          }
          Return(0x0000)
        }

        Name(_CRS,ResourceTemplate()
        {
          IRQ(Edge,ActiveHigh,Exclusive){0x0C}
        })

        Name(_PRS, ResourceTemplate(){
          StartDependentFn(0, 0) {
          IRQNoFlags(){12}
          }
          EndDependentFn()
        })
      }
}
