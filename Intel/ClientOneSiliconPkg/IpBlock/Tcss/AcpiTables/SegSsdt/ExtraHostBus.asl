/** @file
  This file contains the SystemAgent PCI Configuration space
  definition.
  It produce all resources in the Extra Host Bus.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

External(\M64B, IntObj)
External(\M64L, IntObj)
External(\M32B, IntObj)
External(\M32L, IntObj)
External(\OSCC, IntObj)
External(\NEXP, IntObj)
External(\ITSP, IntObj)
External(\NHPG, MethodObj)
External(\NPME, MethodObj)

//
// Define a buffer that will store all the bus, memory, and IO information
// relating to the Host Bus.  This buffer will be dynamically altered in
// the _CRS and passed back to the OS.
//
Name(BUF0,ResourceTemplate()
{
  //
  // Bus Number Allocation: Bus 0 to 0xFF
  //
  WORDBusNumber(ResourceProducer,MinFixed,MaxFixed,PosDecode,0x00,
    0x0000,0x00FF,0x00,0x0100,,,PB00)

  //
  // I/O Region Allocation 0 ( 0x0000 - 0x0CF7 )
  //
  DWordIo(ResourceProducer,MinFixed,MaxFixed,PosDecode,EntireRange,
    0x00,0x0000,0x0CF7,0x00,0x0CF8,,,PI00)

  //
  // I/O Region Allocation 1 ( 0x0D00 - 0xFFFF )
  //
  DWordIo(ResourceProducer,MinFixed,MaxFixed,PosDecode,EntireRange,
    0x00,0x0D00,0xFFFF,0x00,0xF300,,,PI01)

  //
  // PCI Memory Region ( TOLUD - 0xDFFFFFFF )
  //
  DWordMemory(ResourceProducer,PosDecode,MinFixed,MaxFixed,NonCacheable,
    ReadWrite,0x00,0x00000000,0xDFFFFFFF,0x00,0xE0000000,,,PM01)

  //
  // PCI Memory Region ( TOUUD - (TOUUD + ABOVE_4G_MMIO_SIZE) )
  // (This is dummy range for OS compatibility, will patch it in _CRS)
  //
  QWordMemory(ResourceProducer,PosDecode,MinFixed,MaxFixed,NonCacheable,
    ReadWrite,0x00,0x10000,0x1FFFF,0x00,0x10000,,,PM02)
})

Method(_CRS,0,Serialized)
{
  //
  // Create pointers to Memory Sizing values.
  //
  CreateDwordField(BUF0, ^PM01._MIN,M1MN)
  CreateDwordField(BUF0, ^PM01._MAX,M1MX)
  CreateDwordField(BUF0, ^PM01._LEN,M1LN)

  //
  // Set Memory Size Values. TLUD represents bits 31:20 of phyical
  // TOM, so shift these bits into the correct position and fix up
  // the Memory Region available to PCI.
  //
  Store (M32L, M1LN)
  Store (M32B, M1MN)
  Subtract (Add (M1MN, M1LN), 1, M1MX)

  //
  // Create pointers to Memory Sizing values.
  // Patch PM02 range basing on memory size and OS type
  //
  If (LEqual(M64L, 0)) {
    CreateQwordField(BUF0, ^PM02._LEN,MSLN)
    //
    // Set resource length to 0
    //
    Store (0, MSLN)
  }
  Else {
    CreateQwordField(BUF0, ^PM02._LEN,M2LN)
    CreateQwordField(BUF0, ^PM02._MIN,M2MN)
    CreateQwordField(BUF0, ^PM02._MAX,M2MX)
    //
    // Set 64bit MMIO resource Base and Length
    //
    Store (M64L, M2LN)
    Store (M64B, M2MN)
    Subtract (Add (M2MN, M2LN), 1, M2MX)
  }

  Return(BUF0)
}

//
//Name(GUID,UUID("33DB4D5B-1FF7-401C-9657-7441C03DD766"))
//
Name(GUID,Buffer(){0x5b, 0x4d, 0xdb, 0x33,
          0xf7, 0x1f,
          0x1c, 0x40,
          0x96, 0x57,
          0x74, 0x41, 0xc0, 0x3d, 0xd7, 0x66})


Name(SUPP,0)  // PCI _OSC Support Field value
Name(CTRL,0)  // PCI _OSC Control Field value
Name(XCNT, 0) // Variable used in _OSC for counting

Method(_OSC,4,Serialized)
{
  //
  // Check for proper UUID
  // Save the capabilities buffer
  //
  Store(Arg3,Local0)

  //
  // Create DWord-adressable fields from the Capabilties Buffer
  //
  CreateDWordField(Local0,0,CDW1)
  CreateDWordField(Local0,4,CDW2)
  CreateDWordField(Local0,8,CDW3)

  //
  // Check for proper UUID
  //
  If(LEqual(Arg0,GUID))
  {
    // Save Capabilities DWord2 & 3
    Store(CDW2,SUPP)
    Store(CDW3,CTRL)

    //
    // You can clear bits in CTRL here if you don't want OS to take
    // control
    //
    If(LNot(NEXP))
    {
      And(CTRL, 0xFFFFFFF8, CTRL)       // disable Native hot plug, PME
    }

    If(LEqual(ITSP, 1))
    {
      // \_OSC disallow only Advanced Error Reporting control
      And(CTRL, 0xFFFFFFF7, CTRL)
    }

    If(Not(And(CDW1,1)))  // Query flag clear?
    { // Disable GPEs for features granted native control.
      If(And(CTRL,0x01))
      {
        NHPG()
      }
      If(And(CTRL,0x04))  // PME control granted?
      {
        NPME()
      }
    }

    If(LNotEqual(Arg1,One))
    {
      //
      // Unknown revision
      //
      Or(CDW1,0x08,CDW1)
    }

    If(LNotEqual(CDW3,CTRL))
    {
      //
      // Capabilities bits were masked
      //
      Or(CDW1,0x10,CDW1)
    }
    //
    // Update DWORD3 in the buffer
    //
    Store(CTRL,CDW3)
    Store(CTRL,OSCC)
    Return(Local0)
  } Else {
    Or(CDW1,4,CDW1)   // Unrecognized UUID
    Return(Local0)
  }
} // End _OSC
