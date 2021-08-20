/** @file
ACPI RTD3 SSDT table.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

#define RAID_VOL_PRT0_MASK 0x01
#define RAID_VOL_PRT1_MASK 0x02
#define RAID_VOL_PRT2_MASK 0x04
#define RAID_VOL_PRT3_MASK 0x08
#define RAID_VOL_PRT4_MASK 0x10
#define RAID_VOL_PRT5_MASK 0x20
#define RAID_VOL_NVM1_MASK 0x100
#define RAID_VOL_NVM2_MASK 0x200
#define RAID_VOL_NVM3_MASK 0x400
#define RAID_CHECK (LNot(Or(Or(And(VL0M,VLPM),And(VL1M,VLPM)),And(VL2M,VLPM))))
#define RTD3_CHECK (LAnd(And(RCG1,RCGM),VR3A))

Name(VL0M, 0) //Raid Volume 0 Mask
Name(VL1M, 0) //Raid Volume 1 Mask
Name(VL2M, 0) //Raid Volume 2 Mask
Name(VR3A, 1) //Global RTD3 Allowed Flag

    // RAID - (isRaid) Method to verify if storage device is part of RAID volume.
    // IR3E - (isRtd3Enabled) Method to check if RTD3 is enabled and allowed for device.
    Scope(PRT0) {
        Name(VLPM, RAID_VOL_PRT0_MASK)
        Name(RCGM, RCG1_RTD3_PRT0_ENABLED)
        Method(RAID) { If(RAID_CHECK) { Return(0) } Return(1) }
        Method(IR3E) { If(RTD3_CHECK) { Return(1) } Return(0) }
    }

    Scope(PRT1) {
        Name(VLPM, RAID_VOL_PRT1_MASK)
        Name(RCGM, RCG1_RTD3_PRT1_ENABLED)
        Method(RAID) { If(RAID_CHECK) { Return(0) } Return(1) }
        Method(IR3E) { If(RTD3_CHECK) { Return(1) } Return(0) }
    }

    Scope(PRT2) {
        Name(VLPM, RAID_VOL_PRT2_MASK)
        Name(RCGM, RCG1_RTD3_PRT2_ENABLED)
        Method(RAID) { If(RAID_CHECK) { Return(0) } Return(1) }
        Method(IR3E) { If(RTD3_CHECK) { Return(1) } Return(0) }
    }

    Scope(PRT3) {
        Name(VLPM, RAID_VOL_PRT3_MASK)
        Name(RCGM, RCG1_RTD3_PRT3_ENABLED)
        Method(RAID) { If(RAID_CHECK) { Return(0) } Return(1) }
        Method(IR3E) { If(RTD3_CHECK) { Return(1) } Return(0) }
    }

    Scope(PRT4) {
        Name(VLPM, RAID_VOL_PRT4_MASK)
        Name(RCGM, RCG1_RTD3_PRT4_ENABLED)
        Method(RAID) { If(RAID_CHECK) { Return(0) } Return(1) }
        Method(IR3E) { If(RTD3_CHECK) { Return(1) } Return(0) }
    }

    Scope(PRT5) {
        Name(VLPM, RAID_VOL_PRT5_MASK)
        Name(RCGM, RCG1_RTD3_PRT5_ENABLED)
        Method(RAID) { If(RAID_CHECK) { Return(0) } Return(1) }
        Method(IR3E) { If(RTD3_CHECK) { Return(1) } Return(0) }
    }

    Scope(NVM1) {
        Name(VLPM, RAID_VOL_NVM1_MASK)
        Name(RCGM, RCG1_RTD3_NVM1_ENABLED)
        Method(RAID) { If(RAID_CHECK) { Return(0) } Return(1) }
        Method(IR3E) { If(RTD3_CHECK) { Return(1) } Return(0) }
    }

    Scope(NVM2) {
        Name(VLPM, RAID_VOL_NVM2_MASK)
        Name(RCGM, RCG1_RTD3_NVM2_ENABLED)
        Method(RAID) { If(RAID_CHECK) { Return(0) } Return(1) }
        Method(IR3E) { If(RTD3_CHECK) { Return(1) } Return(0) }
    }

    Scope(NVM3) {
        Name(VLPM, RAID_VOL_NVM3_MASK)
        Name(RCGM, RCG1_RTD3_NVM3_ENABLED)
        Method(RAID) { If(RAID_CHECK) { Return(0) } Return(1) }
        Method(IR3E) { If(RTD3_CHECK) { Return(1) } Return(0) }
    }

    // RSTD - _DSM method for Device RAID Volume
    // Arg0 - UUID: E03E3431-E510-4fa2-ABC0-2D7E901245FE
    // Arg1 - Revision ID: 0x01 (Integer)
    // Arg2 - Function Index: 0x01 (Integer)
    // Arg3 - Rtd3PortMask: A bit mask of SATA Ports representing each
    //        of the RAID member disk in the RAID Volume to be saved for RTD3 handling (Integer)
    //        The form of the bit mask for each RAID volume is:
    //        b-00000000000000000000000000pppppp where each p represents a SATA Controller port.
    //        If p in bit 0 is set to 1 then SATA Controller Port 0 is part of the RAID Volume.
    //        A 0 in a bit position means the port is not part of the RAID Volume.
    //        A mask with no port bits set is valid and means there are no devices that are part
    //        of the RTD3 of this RAID Volume.
    // Return - A package containing a single Integer signifying the Error value:
    //          0: Success.
    //          1: Invalid package UUID.
    //          2: Invalid package size.
    //          All Others: Reserved.
    //
    // Arg4 - PMAP Port Bitmap Status - output argument where port-per-volume bitmap will be stored
    //
    Method (RSTD, 5, Serialized,,, {BuffObj, IntObj, IntObj, PkgObj, FieldUnitObj}) {
      If (LEqual(Arg0, ToUUID ("E03E3431-E510-4fa2-ABC0-2D7E901245FE"))) {
        Switch(ToInteger(Arg2)) {
          Case (0) {
            // Standard query - A bitmask of functions supported
            // Supports function 0-3
            Name(RBUF, Buffer(1){0x00})
            CreateByteField (RBUF, 0, SFUN)
            Store (0x03, SFUN)
            Return (RBUF)
          }
          Case (1) {// Assign ports to this RAID volume - _SAVE_RTD3_PACKAGE
            Store(DeRefOf(Index(Arg3,0)), Arg4) // Assign port mapping to the volume's power resource
            Store(DeRefOf(Index(Arg3,0)), Local0) //workaround for ADBG crashing when given directly "Arg4" instead of Local0
            Return(Package(){0})
          }
          Case (2) {  // RST Driver access to turn ON a port.
            Store(DeRefOf(Index(Arg3,0)), Local0)
            \_SB.PC00.SAT0.CPON(Local0);
            Return(Package(){0})
          }
          Case (3) {  //RST Driver access to turn OFF a port.
            Store(DeRefOf(Index(Arg3,0)), Local0)
            \_SB.PC00.SAT0.CPOF(Local0);
            Return(Package(){0})
          }
          Case(4) { // RST Driver read RAID mask
            Name(GETM, Buffer(1){0x00})
            CreateByteField (GETM, 0, GMSK)
            Store (Arg4, GMSK)
            Return (GETM)
          }
          Case(5) { //Globally allow/disallow RTD3 for Raid Volumes
            Store(DeRefOf(Index(Arg3,0)), VR3A)
            Return (0)
          }
          Default {
            Return(Package(){2})
          }
        } //Switch (Arg2)
      } Else {
        Return(Buffer(){0})
      }
    } // Method (RSTD)


    Device(VOL0) {
      Name(_ADR,0x0080FFFF)  // RAID Volume 0
      Name(_PR0, Package(){V0PR})
      Name(_PR3, Package(){V0PR})

      Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj}) {
          Return(\_SB.PC00.SAT0.RSTD(Arg0,Arg1,Arg2,Arg3,RefOf(\_SB.PC00.SAT0.VL0M)))
      }
      PowerResource(V0PR, 0, 0) { // Power Resource Aggregate for RAID volume 0
          Name(_STA, 0x01)
          Method(_ON, 0) {
              Store(0x1, _STA); \_SB.PC00.SAT0.CPON(VL0M);
          }
          Method(_OFF, 0) {
              Store(0x0, _STA); \_SB.PC00.SAT0.CPOF(VL0M);
          }
      }
    }

    Device(VOL1) {
      Name(_ADR,0x0081FFFF)  // RAID Volume 1
      Name(_PR0, Package(){V1PR})
      Name(_PR3, Package(){V1PR})

      Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj}) {
        Return(\_SB.PC00.SAT0.RSTD(Arg0,Arg1,Arg2,Arg3,RefOf(\_SB.PC00.SAT0.VL1M)))
      }

      PowerResource(V1PR, 0, 0) { // Power Resource Aggregate for RAID volume 1
        Name(_STA, 0x01)
        Method(_ON, 0)  {
          Store(0x1, _STA); \_SB.PC00.SAT0.CPON(VL1M);
        }
        Method(_OFF, 0) {
          Store(0x0, _STA); \_SB.PC00.SAT0.CPOF(VL1M);
        }
      }
    }

    Device(VOL2) {
        Name(_ADR,0x0082FFFF)  // RAID Volume 2
        Name(_PR0, Package(){V2PR})
        Name(_PR3, Package(){V2PR})

        Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj}) {
          Return(\_SB.PC00.SAT0.RSTD(Arg0,Arg1,Arg2,Arg3,RefOf(\_SB.PC00.SAT0.VL2M)))
        }

        PowerResource(V2PR, 0, 0) { // Power Resource Aggregate for RAID volume 2
          Name(_STA, 0x01)
          Method(_ON, 0)  {
              Store(0x1, _STA); \_SB.PC00.SAT0.CPON(VL2M);
          }
          Method(_OFF, 0) {
              Store(0x0, _STA); \_SB.PC00.SAT0.CPOF(VL2M);
          }
        }
    }


