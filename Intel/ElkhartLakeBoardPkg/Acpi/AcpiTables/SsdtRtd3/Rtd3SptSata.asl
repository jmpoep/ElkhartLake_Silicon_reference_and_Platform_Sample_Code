/** @file
  ACPI RTD3 SSDT table for SATA

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

/// @details
/// The following namespace(variable) must be initialized
/// when including this file under SATA scope:
/// PORT: SATA PORT number
/// PBAR: SATA command port base address
/// PWRG: power GPIO pin {enable, group, pad, "on" polarity}
//    sample:Name(PWRG, Package() {
//                   0, // 0-disable, 1-enable GPIO, 2-enable IOEX(IO Expander)
//                   0, // GPIO group #/IOEX #
//                   0, // GPIO pad #/IOEX pin #
//                   0  // power on polarity
//                 })
/// @defgroup SATA port Scope **/

/// Define _PR0, _PR3 PowerResource Package
// command port = ABAR + PBAR
// power pin = PWRG

  Method(_PR0) {
      If (CondRefOf(SPPR)) {
        Return(Package(){SPPR})
      }
    Return(Package() {})
  }
  Method(_PR3) {
      If (CondRefOf(SPPR)) {
        Return(Package(){SPPR})
      }
    Return(Package() {})
  }

  PowerResource(SPPR, 0, 0)
  {
    Method(_STA)
    {
        Return(SPSA())
    }

    Method(_ON) {
        //If RTD3 is disabled exit.
        If(LNotEqual(IR3E(),0)) {
          // If device is NOT part of RAID than allow to change state.
            If(LEqual(RAID(),0)) {
              SPON()            // _ON Method
              Sleep(16)       // Delay for power ramp.
            }
        }
    }

    Method(_OFF) {
      //If RTD3 is disabled exit.
      If(LNotEqual(IR3E(),0)) {
          // If device is NOT part of RAID than allow to change state.
          If(LEqual(RAID(),0)) {
            SPOF()
          }
      }
    }

  } // end SPPR

  Name(OFTM, Zero) /// OFTM: Time returned by Timer() when the Power resource was turned OFF

  Method(SPSA) {
      Return (PSTA(PWRG))
  } /// @defgroup sata_prt1_sta     SATA Port 1 PowerResource _STA Method

  Method(SPON, 0) {
      PON(PWRG)
  }

  Method(SPOF, 0, Serialized) {
    Add(\_SB.PC00.SAT0.MBR6, PBAR, Local0)
    /// if S0Ix enabled
    If(LEqual(S0ID, 1)) {
      OperationRegion(PSTS, SystemMemory, Local0, 0x18)
      Field(PSTS, DWordAcc, NoLock, Preserve)
      {
        Offset(0x0),
        CMST, 1,  //PxCMD.ST
        CSUD, 1,  //PxCMD.SUD
        , 2,
        CFRE, 1,  //PxCMD.FRE
        Offset(0x10),
        SDET, 4,  //PxSSTS.DET
        Offset(0x14),
        CDET, 4   //PxSCTL.DET
      }

      // WA for RST driver creating volume failed.
      // In order to fix the error caused by reigster change during creating volume of RST driver, skip to disable phy in RAID mode.
      If(LAnd(LEqual(\_SB.PC00.SAT0.SUBC, 0x06),LOr(LEqual(SDET, 1), LEqual(SDET, 3))))  { /// Execute offline flow only if Device detected and Phy not offline
        ///- Clear ST (PxCMD.ST)
        Store(0, CMST)                   // PBAR[0]
        ///- Clear FRE
        Store(0, CFRE)                   // PBAR[4]
        ///- Clear SUD (PxCMD.SUD)
        Store(0, CSUD)                   // PBAR[1]
        ///- Set DET to 4 (PxSCTL.DET)
        Store(4, CDET)                   // PBAR+0x14[3:0]
        Sleep(16)
        ///- Wait until PxSSTS.DET == 4
        While(LNotEqual(SDET, 4)){
          Sleep(16)
        }
      }
    } // if S0Ix enabled
    // drive power pin "OFF"
    POFF(PWRG)
    Store(Timer(), ^OFTM) /// Store time when Disk turned OFF(non-zero OFTM indicate minimum 50ms requirement does apply when _ON called next time)
  } // end SOPF
