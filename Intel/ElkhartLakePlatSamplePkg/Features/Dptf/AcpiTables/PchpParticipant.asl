/** @file
  Intel ACPI Reference Code for Dynamic Platform & Thermal Framework

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
// IPC Registers and Commands
//
#define PCH_FIVR_IPC_CMD              0xA3
#define LOGIC_WRITE_SUB_CMD           0x01
#define FUSE_WRITE_SUB_CMD            0x03
#define RFI_WBUF0                     0x00
#define EMI_WBUF0                     0x01

External(IPCS, MethodObj)  // IPC Command Send (Read/Write)

Scope(\_SB)
{
  Device(TPCH)  // PCH FIVR Participant
  {
    Name(_HID, EISAID("INT3405"))
    Name(_CID, "PNP0C02")
    Name(_UID, "TPCH")
    Name(_STR, Unicode("Intel PCH FIVR Participant"))
    Name(PTYP, 0x05)

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
    Method(_STA)
    {
      If(LEqual(\PCHE,1)) {
        Return(0x0F)
      } Else {
        Return(0x00)
      }
    }


    // SRFI (Set PCH FIVR RFI value)
    //
    // Set PCH FIVR RFI Value
    //
    // Arguments:
    //   Arg0: PCH FIVR RFI Control Setting Value.
    // Return Value:
    //   None.
    //
    Method(SRFI, 1, Serialized)
    {
      //
      // Need to perform both Logic Write (subcommand 0x01) and Fuse Write (subcommand 0x03)
      //
      IPCS(PCH_FIVR_IPC_CMD, LOGIC_WRITE_SUB_CMD, 0x8, RFI_WBUF0, Arg0, 0, 0)
      IPCS(PCH_FIVR_IPC_CMD, FUSE_WRITE_SUB_CMD, 0x8, RFI_WBUF0, Arg0, 0, 0)
    }

    // SEMI (Set PCH FIVR EMI value)
    //
    // Set PCH FIVR EMI Value
    //
    // Arguments:
    //   Arg0: PCH FIVR EMI Control Setting Value.
    // Return Value:
    //   None.
    //
    Method(SEMI, 1, Serialized)
    {
      //
      // Need to perform both Logic Write (subcommand 0x01) and Fuse Write (subcommand 0x03)
      //
      IPCS(PCH_FIVR_IPC_CMD, LOGIC_WRITE_SUB_CMD, 0x8, EMI_WBUF0, Arg0, 0, 0)
      IPCS(PCH_FIVR_IPC_CMD, FUSE_WRITE_SUB_CMD, 0x8, EMI_WBUF0, Arg0, 0, 0)
    }

  } // End TPCH device
} // End Scope (\_SB)
