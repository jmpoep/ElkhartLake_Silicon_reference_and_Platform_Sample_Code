/** @file
  ACPI DSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

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

Scope(\_SB) {
  Name(PD00, Package(){
// WARNING: That setting should align with platform policy
// D31
    Package(){0x001FFFFF, 0, 0, 11 },
    Package(){0x001FFFFF, 1, 0, 10 },
    Package(){0x001FFFFF, 2, 0, 11 },
    Package(){0x001FFFFF, 3, 0, 11 },
// D30
    Package(){0x001EFFFF, 0, 0, 11 },
    Package(){0x001EFFFF, 1, 0, 10 },
    Package(){0x001EFFFF, 2, 0, 11 },
    Package(){0x001EFFFF, 3, 0, 11 },
// D29
    Package(){0x001DFFFF, 0, 0, 11 },
// D28
    Package(){0x001CFFFF, 0, 0, 11 },
    Package(){0x001CFFFF, 1, 0, 10 },
    Package(){0x001CFFFF, 2, 0, 11 },
    Package(){0x001CFFFF, 3, 0, 11 },
// D27
    Package(){0x001BFFFF, 0, 0, 11 },
    Package(){0x001BFFFF, 1, 0, 10 },
    Package(){0x001BFFFF, 2, 0, 11 },
    Package(){0x001BFFFF, 3, 0, 11 },
// D26
    Package(){0x001AFFFF, 0, 0, 11 },
    Package(){0x001AFFFF, 1, 0, 10 },
    Package(){0x001AFFFF, 2, 0, 11 },
    Package(){0x001AFFFF, 3, 0, 11 },
// D25
    Package(){0x0019FFFF, 0, 0, 11 },
    Package(){0x0019FFFF, 1, 0, 10 },
    Package(){0x0019FFFF, 2, 0, 11 },
    Package(){0x0019FFFF, 3, 0, 11 },
// D24
    Package(){0x0018FFFF, 0, 0, 11 },
    Package(){0x0018FFFF, 1, 0, 10 },
    Package(){0x0018FFFF, 2, 0, 11 },
    Package(){0x0018FFFF, 3, 0, 11 },
// D23
    Package(){0x0017FFFF, 0, 0, 11 },
// D22
    Package(){0x0016FFFF, 0, 0, 11 },
    Package(){0x0016FFFF, 1, 0, 10 },
    Package(){0x0016FFFF, 2, 0, 11 },
    Package(){0x0016FFFF, 3, 0, 11 },
// D20
    Package(){0x0014FFFF, 0, 0, 11 },
    Package(){0x0014FFFF, 1, 0, 10 },
    Package(){0x0014FFFF, 2, 0, 11 },
    Package(){0x0014FFFF, 3, 0, 11 },
// D19
    Package(){0x0013FFFF, 0, 0, 11 },
    Package(){0x0013FFFF, 1, 0, 10 },
    Package(){0x0013FFFF, 2, 0, 11 },
    Package(){0x0013FFFF, 3, 0, 11 },
// D18
    Package(){0x0012FFFF, 0, 0, 11 },
    Package(){0x0012FFFF, 1, 0, 10 },
    Package(){0x0012FFFF, 2, 0, 11 },
    Package(){0x0012FFFF, 3, 0, 11 },
// D17
    Package(){0x0011FFFF, 0, 0, 11 },
    Package(){0x0011FFFF, 1, 0, 10 },
    Package(){0x0011FFFF, 2, 0, 11 },
    Package(){0x0011FFFF, 3, 0, 11 },
// D16
    Package(){0x0010FFFF, 0, 0, 11 },
    Package(){0x0010FFFF, 1, 0, 10 },
    Package(){0x0010FFFF, 2, 0, 11 },
    Package(){0x0010FFFF, 3, 0, 11 },
// Host Bridge
// SA IGFX Device
    Package(){0x0002FFFF, 0, 0, 11 },
// SA GNA Device
    Package(){0x0008FFFF, 0, 0, 11 },
  })
  Name(AR00, Package(){
// PCI Bridge
// D31
    Package(){0x001FFFFF, 0, 0, 16 },
    Package(){0x001FFFFF, 1, 0, 17 },
    Package(){0x001FFFFF, 2, 0, 18 },
    Package(){0x001FFFFF, 3, 0, 19 },
// D30
    Package(){0x001EFFFF, 0, 0, 16 },
    Package(){0x001EFFFF, 1, 0, 17 },
    Package(){0x001EFFFF, 2, 0, 18 },
    Package(){0x001EFFFF, 3, 0, 19 },
// D29
    Package(){0x001DFFFF, 0, 0, 16 },
    Package(){0x001DFFFF, 1, 0, 34 },
    Package(){0x001DFFFF, 2, 0, 35 },
    Package(){0x001DFFFF, 3, 0, 36 },
// D28
    Package(){0x001CFFFF, 0, 0, 16 },
    Package(){0x001CFFFF, 1, 0, 17 },
    Package(){0x001CFFFF, 2, 0, 18 },
    Package(){0x001CFFFF, 3, 0, 19 },
// D27
    Package(){0x001BFFFF, 0, 0, 16 },
    Package(){0x001BFFFF, 1, 0, 17 },
    Package(){0x001BFFFF, 2, 0, 18 },
    Package(){0x001BFFFF, 3, 0, 19 },
// D26
    Package(){0x001AFFFF, 0, 0, 16 },
    Package(){0x001AFFFF, 1, 0, 17 },
    Package(){0x001AFFFF, 2, 0, 18 },
    Package(){0x001AFFFF, 3, 0, 19 },
// D25
    Package(){0x0019FFFF, 0, 0, 31 },
    Package(){0x0019FFFF, 1, 0, 32 },
    Package(){0x0019FFFF, 2, 0, 33 },
// D24
    Package(){0x0018FFFF, 0, 0, 16 },
    Package(){0x0018FFFF, 1, 0, 17 },
    Package(){0x0018FFFF, 2, 0, 18 },
    Package(){0x0018FFFF, 3, 0, 19 },
// D23
    Package(){0x0017FFFF, 0, 0, 16 },
// D22
    Package(){0x0016FFFF, 0, 0, 16 },
    Package(){0x0016FFFF, 1, 0, 17 },
    Package(){0x0016FFFF, 2, 0, 18 },
    Package(){0x0016FFFF, 3, 0, 19 },
// D21
    Package(){0x0015FFFF, 0, 0, 27 },
    Package(){0x0015FFFF, 1, 0, 28 },
    Package(){0x0015FFFF, 2, 0, 29 },
    Package(){0x0015FFFF, 3, 0, 30 },
// D20
    Package(){0x0014FFFF, 0, 0, 16 },
    Package(){0x0014FFFF, 1, 0, 17 },
    Package(){0x0014FFFF, 2, 0, 18 },
    Package(){0x0014FFFF, 3, 0, 19 },
// D19
    Package(){0x0013FFFF, 0, 0, 16 },
    Package(){0x0013FFFF, 1, 0, 17 },
    Package(){0x0013FFFF, 2, 0, 18 },
    Package(){0x0013FFFF, 3, 0, 19 },
// D18
    Package(){0x0012FFFF, 0, 0, 24 },
    Package(){0x0012FFFF, 1, 0, 25 },
    Package(){0x0012FFFF, 2, 0, 26 },
// D17
    Package(){0x0011FFFF, 0, 0, 16 },
    Package(){0x0011FFFF, 1, 0, 17 },
    Package(){0x0011FFFF, 2, 0, 18 },
    Package(){0x0011FFFF, 3, 0, 19 },
// D16
    Package(){0x0010FFFF, 0, 0, 16 },
    Package(){0x0010FFFF, 1, 0, 17 },
    Package(){0x0010FFFF, 2, 0, 18 },
    Package(){0x0010FFFF, 3, 0, 19 },
// Host Bridge
// SA IGFX Device
    Package(){0x0002FFFF, 0, 0, 16 },
// SA GNA Device
    Package(){0x0008FFFF, 0, 0, 16 },
  })
  Name(PD04, Package(){
    Package(){0x0000FFFF, 0, 0, 11 },
    Package(){0x0000FFFF, 1, 0, 10 },
    Package(){0x0000FFFF, 2, 0, 11 },
    Package(){0x0000FFFF, 3, 0, 11 },
  })
  Name(AR04, Package(){
    Package(){0x0000FFFF, 0, 0, 16 },
    Package(){0x0000FFFF, 1, 0, 17 },
    Package(){0x0000FFFF, 2, 0, 18 },
    Package(){0x0000FFFF, 3, 0, 19 },
  })
  Name(PD05, Package(){
    Package(){0x0000FFFF, 0, 0, 10 },
    Package(){0x0000FFFF, 1, 0, 11 },
    Package(){0x0000FFFF, 2, 0, 11 },
    Package(){0x0000FFFF, 3, 0, 11 },
  })
  Name(AR05, Package(){
    Package(){0x0000FFFF, 0, 0, 17 },
    Package(){0x0000FFFF, 1, 0, 18 },
    Package(){0x0000FFFF, 2, 0, 19 },
    Package(){0x0000FFFF, 3, 0, 16 },
  })
  Name(PD06, Package(){
    Package(){0x0000FFFF, 0, 0, 11 },
    Package(){0x0000FFFF, 1, 0, 11 },
    Package(){0x0000FFFF, 2, 0, 11 },
    Package(){0x0000FFFF, 3, 0, 10 },
  })
  Name(AR06, Package(){
    Package(){0x0000FFFF, 0, 0, 18 },
    Package(){0x0000FFFF, 1, 0, 19 },
    Package(){0x0000FFFF, 2, 0, 16 },
    Package(){0x0000FFFF, 3, 0, 17 },
  })
  Name(PD07, Package(){
    Package(){0x0000FFFF, 0, 0, 11 },
    Package(){0x0000FFFF, 1, 0, 11 },
    Package(){0x0000FFFF, 2, 0, 10 },
    Package(){0x0000FFFF, 3, 0, 11 },
  })
  Name(AR07, Package(){
    Package(){0x0000FFFF, 0, 0, 19 },
    Package(){0x0000FFFF, 1, 0, 16 },
    Package(){0x0000FFFF, 2, 0, 17 },
    Package(){0x0000FFFF, 3, 0, 18 },
  })
  Name(PD08, Package(){
    Package(){0x0000FFFF, 0, 0, 11 },
    Package(){0x0000FFFF, 1, 0, 10 },
    Package(){0x0000FFFF, 2, 0, 11 },
    Package(){0x0000FFFF, 3, 0, 11 },
  })
  Name(AR08, Package(){
    Package(){0x0000FFFF, 0, 0, 16 },
    Package(){0x0000FFFF, 1, 0, 17 },
    Package(){0x0000FFFF, 2, 0, 18 },
    Package(){0x0000FFFF, 3, 0, 19 },
  })
  Name(PD09, Package(){
    Package(){0x0000FFFF, 0, 0, 10 },
    Package(){0x0000FFFF, 1, 0, 11 },
    Package(){0x0000FFFF, 2, 0, 11 },
    Package(){0x0000FFFF, 3, 0, 11 },
  })
  Name(AR09, Package(){
    Package(){0x0000FFFF, 0, 0, 17 },
    Package(){0x0000FFFF, 1, 0, 18 },
    Package(){0x0000FFFF, 2, 0, 19 },
    Package(){0x0000FFFF, 3, 0, 16 },
  })
  Name(PD0E, Package(){
    Package(){0x0000FFFF, 0, 0, 11 },
    Package(){0x0000FFFF, 1, 0, 11 },
    Package(){0x0000FFFF, 2, 0, 11 },
    Package(){0x0000FFFF, 3, 0, 10 },
  })
  Name(AR0E, Package(){
    Package(){0x0000FFFF, 0, 0, 18 },
    Package(){0x0000FFFF, 1, 0, 19 },
    Package(){0x0000FFFF, 2, 0, 16 },
    Package(){0x0000FFFF, 3, 0, 17 },
  })
  Name(PD0F, Package(){
    Package(){0x0000FFFF, 0, 0, 11 },
    Package(){0x0000FFFF, 1, 0, 11 },
    Package(){0x0000FFFF, 2, 0, 10 },
    Package(){0x0000FFFF, 3, 0, 11 },
  })
  Name(AR0F, Package(){
    Package(){0x0000FFFF, 0, 0, 19 },
    Package(){0x0000FFFF, 1, 0, 16 },
    Package(){0x0000FFFF, 2, 0, 17 },
    Package(){0x0000FFFF, 3, 0, 18 },
  })

//---------------------------------------------------------------------------
// Begin PCI tree object scope
//---------------------------------------------------------------------------
  Device(PC00) { // PCI Bridge "Host Bridge"
    Name(_HID, EISAID("PNP0A08")) // Indicates PCI Express/PCI-X Mode2 host hierarchy
    Name(_CID, EISAID("PNP0A03")) // To support legacy OS that doesn't understand the new HID
    Name(_SEG, 0)
    Name(_ADR, 0x00000000)
    Method(^BN00, 0){ return(0x0000) }  // Returns default Bus number for Peer PCI busses. Name can be overriden with control method placed directly under Device scope
    Method(_BBN, 0){ return(BN00()) } // Bus number, optional for the Root PCI Bus
    Name(_UID, 0x0000)  // Unique Bus ID, optional
    Method(_PRT,0) {
      If(PICM) {Return(AR00)} // APIC mode
      Return (PD00) // PIC Mode
    } // end _PRT

  Device (PTCT) {
    Name (_HID, "INTC1032")  // _HID: Hardware ID
    Name (_STR, Unicode ("Intel PTCT "))  // _STR: Description String
    Name (_UID, Zero)
    Method (_DSM, 0x4, Serialized)    {
      // Check the UUID
      if(LEqual(Arg0, ToUUID("7890A6A1-1797-4FF6-9F0E-6CD85686A4A1")))   {
          If(LEqual(Arg1, Zero)) {
            //Switch statement based on the function index.
            switch(ToInteger(Arg2)) {
              case(0) {
                Return (TBAS)
              }
            }
          }
          Return(0x0)
      }
      // Unsupported UUID
      Return (Buffer (One)    { 0x00 })
    }
  }

  Include("HostBus.asl")
  } // end PC00 Bridge "Host Bridge"
} // end _SB scope
