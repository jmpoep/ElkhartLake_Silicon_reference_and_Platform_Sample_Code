/** @file
  ACPI DSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

  // General Purpose Events.  This Scope handles the Run-time and
  // Wake-time SCIs.  The specific method called will be determined by
  // the _Lxx value, where xx equals the bit location in the General
  // Purpose Event register(s).


  External(D1F0)
  External(D1F1)
  External(D1F2)
  External(D6F0)
  External(\_SB.PCI0.PEG0.HPME, MethodObj)
  External(\_SB.PCI0.PEG1.HPME, MethodObj)
  External(\_SB.PCI0.PEG2.HPME, MethodObj)
  External(\_SB.PCI0.PEG3.HPME, MethodObj)
  External(\_GPE.AL6F, MethodObj)
  External(\_GPE.P0L6, MethodObj)
  External(\_GPE.P1L6, MethodObj)
  External(\_GPE.P2L6, MethodObj)
  External(\_GPE.P3L6, MethodObj)
  External(SGGP)
  External(P1GP)
  External(P2GP)
  External(P3GP)
  External(P0WK)
  External(P1WK)
  External(P2WK)
  External(P3WK)
  External(\_SB.HWPI, IntObj) // HWP Interrupt Status
  External(\_SB.DTSI, IntObj) // DTS Interrupt Status
  External(\_SB.ITBI, IntObj) // Intel Turbo Boost Max Technology 3.0 (ITBM) Interrupt Status
  External(\_GPE.HLVT, MethodObj) // Interrupt handler for HWP
  External(\_GPE.ITBH, MethodObj) // Interrupt handler for Intel Turbo Boost Max Technology 3.0
  External(\_SB.PCI0.TRP0.VDID)
  External(\_SB.PCI0.TRP0.PDCX)
  External(\_SB.PCI0.TRP0.PDSX)
  External(\_SB.PCI0.TRP0.L0SE)
  External(\_SB.PCI0.TRP1.VDID)
  External(\_SB.PCI0.TRP1.PDCX)
  External(\_SB.PCI0.TRP1.PDSX)
  External(\_SB.PCI0.TRP1.L0SE)
  External(\_SB.PCI0.TRP2.VDID)
  External(\_SB.PCI0.TRP2.PDCX)
  External(\_SB.PCI0.TRP2.PDSX)
  External(\_SB.PCI0.TRP2.L0SE)
  External(\_SB.PCI0.TRP3.VDID)
  External(\_SB.PCI0.TRP3.PDCX)
  External(\_SB.PCI0.TRP3.PDSX)
  External(\_SB.PCI0.TRP3.L0SE)
  External(\_SB.PCI0.TRP4.VDID)
  External(\_SB.PCI0.TRP4.PDCX)
  External(\_SB.PCI0.TRP4.PDSX)
  External(\_SB.PCI0.TRP4.L0SE)
  External(\_SB.PCI0.TRP5.VDID)
  External(\_SB.PCI0.TRP5.PDCX)
  External(\_SB.PCI0.TRP5.PDSX)
  External(\_SB.PCI0.TRP5.L0SE)
  External(\_SB.PCI1.TRP0.VDID)
  External(\_SB.PCI1.TRP0.PDCX)
  External(\_SB.PCI1.TRP0.PDSX)
  External(\_SB.PCI1.TRP0.L0SE)
  External(\_SB.PCI1.TRP1.VDID)
  External(\_SB.PCI1.TRP1.PDCX)
  External(\_SB.PCI1.TRP1.PDSX)
  External(\_SB.PCI1.TRP1.L0SE)
  External(\_SB.PCI1.TRP2.VDID)
  External(\_SB.PCI1.TRP2.PDCX)
  External(\_SB.PCI1.TRP2.PDSX)
  External(\_SB.PCI1.TRP2.L0SE)
  External(\_SB.PCI1.TRP3.VDID)
  External(\_SB.PCI1.TRP3.PDCX)
  External(\_SB.PCI1.TRP3.PDSX)
  External(\_SB.PCI1.TRP3.L0SE)
  External(\_SB.PCI1.TRP4.VDID)
  External(\_SB.PCI1.TRP4.PDCX)
  External(\_SB.PCI1.TRP4.PDSX)
  External(\_SB.PCI1.TRP4.L0SE)
  External(\_SB.PCI1.TRP5.VDID)
  External(\_SB.PCI1.TRP5.PDCX)
  External(\_SB.PCI1.TRP5.PDSX)
  External(\_SB.PCI1.TRP5.L0SE)

  Scope(\_GPE)
  {
  // Note:
  // Originally, the two GPE methods below are automatically generated, but, for ASL code restructuring,
  // disabled the automatic generation and declare the ASL code here.
  //

  //
  // This PME event (PCH's GPE 69h) is received on one or more of the PCI Express* ports or
  // an assert PMEGPE message received via DMI
  //
  Method(_L69, 0, serialized) {
    \_SB.PCI0.RP01.HPME()
    \_SB.PCI0.RP02.HPME()
    \_SB.PCI0.RP03.HPME()
    \_SB.PCI0.RP04.HPME()
    \_SB.PCI0.RP05.HPME()
    \_SB.PCI0.RP06.HPME()
    \_SB.PCI0.RP07.HPME()
    \_SB.PCI0.RP08.HPME()
    \_SB.PCI0.RP09.HPME()
    \_SB.PCI0.RP10.HPME()
    \_SB.PCI0.RP11.HPME()
    \_SB.PCI0.RP12.HPME()
    \_SB.PCI0.RP13.HPME()
    \_SB.PCI0.RP14.HPME()
    \_SB.PCI0.RP15.HPME()
    \_SB.PCI0.RP16.HPME()
    \_SB.PCI0.RP17.HPME()
    \_SB.PCI0.RP18.HPME()
    \_SB.PCI0.RP19.HPME()
    \_SB.PCI0.RP20.HPME()
    \_SB.PCI0.RP21.HPME()
    \_SB.PCI0.RP22.HPME()
    \_SB.PCI0.RP23.HPME()
    \_SB.PCI0.RP24.HPME()

    If(LEqual(D1F0,1))
    {
      \_SB.PCI0.PEG0.HPME()
      Notify(\_SB.PCI0.PEG0, 0x02)
      Notify(\_SB.PCI0.PEG0.PEGP, 0x02)
    }

    If(LEqual(D1F1,1))
    {
      \_SB.PCI0.PEG1.HPME()
      Notify(\_SB.PCI0.PEG1, 0x02)
    }

    If(LEqual(D1F2,1))
    {
      \_SB.PCI0.PEG2.HPME()
      Notify(\_SB.PCI0.PEG2, 0x02)
    }

    If(LEqual(D6F0,1))
    {
      \_SB.PCI0.PEG3.HPME()
      Notify(\_SB.PCI0.PEG3, 0x02)
    }
  }

  // PCI Express Hot-Plug caused the wake event.

  Method(_L61)
  {
    Add(L01C,1,L01C)  // Increment L01 Entry Count.

    P8XH(0,0x01)      // Output information to Port 80h.
    P8XH(1,L01C)


    // Check Root Port 1 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP01.VDID,0xFFFFFFFF),\_SB.PCI0.RP01.HPSX))
    {
      If(\_SB.PCI0.RP01.PDCX)
      {
        // Clear all status bits first.

        Store(1,\_SB.PCI0.RP01.PDCX)
        Store(1,\_SB.PCI0.RP01.HPSX)

        //
        // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
        // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
        // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
        // disabled on empty slots prior booting to OS.
        //
        If(LNot(\_SB.PCI0.RP01.PDSX)) {
          // The PCI Express slot is empty, so disable L0s on hot unplug
          //
          Store(0,\_SB.PCI0.RP01.L0SE)

        }
      }
      Else
      {
        // False event.  Clear Hot-Plug Status
        // then exit.

        Store(1,\_SB.PCI0.RP01.HPSX)
      }
    }

    // Check Root Port 2 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP02.VDID,0xFFFFFFFF),\_SB.PCI0.RP02.HPSX))
    {
      If(\_SB.PCI0.RP02.PDCX)
      {
        Store(1,\_SB.PCI0.RP02.PDCX)
        Store(1,\_SB.PCI0.RP02.HPSX)

        If(LNot(\_SB.PCI0.RP02.PDSX)) {
          Store(0,\_SB.PCI0.RP02.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP02.HPSX)
      }
    }

    // Check Root Port 3 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP03.VDID,0xFFFFFFFF),\_SB.PCI0.RP03.HPSX))
    {
      If(\_SB.PCI0.RP03.PDCX)
      {
        Store(1,\_SB.PCI0.RP03.PDCX)
        Store(1,\_SB.PCI0.RP03.HPSX)

        If(LNot(\_SB.PCI0.RP03.PDSX)) {
          Store(0,\_SB.PCI0.RP03.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP03.HPSX)
      }
    }

    // Check Root Port 4 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP04.VDID,0xFFFFFFFF),\_SB.PCI0.RP04.HPSX))
    {
      If(\_SB.PCI0.RP04.PDCX)
      {
        Store(1,\_SB.PCI0.RP04.PDCX)
        Store(1,\_SB.PCI0.RP04.HPSX)

        If(LNot(\_SB.PCI0.RP04.PDSX)) {
          Store(0,\_SB.PCI0.RP04.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP04.HPSX)
      }
    }

    // Check Root Port 5 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP05.VDID,0xFFFFFFFF),\_SB.PCI0.RP05.HPSX))
    {
      If(\_SB.PCI0.RP05.PDCX)
      {
        Store(1,\_SB.PCI0.RP05.PDCX)
        Store(1,\_SB.PCI0.RP05.HPSX)

        If(LNot(\_SB.PCI0.RP05.PDSX)) {
          Store(0,\_SB.PCI0.RP05.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP05.HPSX)
      }
    }

    // Check Root Port 6 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP06.VDID,0xFFFFFFFF),\_SB.PCI0.RP06.HPSX))
    {
      If(\_SB.PCI0.RP06.PDCX)
      {
        Store(1,\_SB.PCI0.RP06.PDCX)
        Store(1,\_SB.PCI0.RP06.HPSX)

        If(LNot(\_SB.PCI0.RP06.PDSX)) {
          Store(0,\_SB.PCI0.RP06.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP06.HPSX)
      }
    }

    // Check Root Port 7 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP07.VDID,0xFFFFFFFF),\_SB.PCI0.RP07.HPSX))
    {
      If(\_SB.PCI0.RP07.PDCX)
      {
        Store(1,\_SB.PCI0.RP07.PDCX)
        Store(1,\_SB.PCI0.RP07.HPSX)

        If(LNot(\_SB.PCI0.RP07.PDSX)) {
          Store(0,\_SB.PCI0.RP07.L0SE)
        }

        If(LEqual(PFLV,FlavorDesktop))
        {
        }
        Else
        {
          If (\ECON)
          {
//@todo: Waiting for DOCK offect data
//            If(LEqual(\_SB.PCI0.LPCB.H_EC.ECRD(RefOf(\_SB.PCI0.LPCB.H_EC.DOCK)), 0))
//            { // If not docked then it's hot plug
//            }
          }
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP07.HPSX)
      }
    }

    // Check Root Port 8 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP08.VDID,0xFFFFFFFF),\_SB.PCI0.RP08.HPSX))
    {
      If(\_SB.PCI0.RP08.PDCX)
      {
        Store(1,\_SB.PCI0.RP08.PDCX)
        Store(1,\_SB.PCI0.RP08.HPSX)

        If(LNot(\_SB.PCI0.RP08.PDSX)) {
          Store(0,\_SB.PCI0.RP08.L0SE)
        }

        If(LEqual(PFLV,FlavorDesktop))
        {
        }
        Else
        {
          If (\ECON)
          {
//@todo: Waiting for DOCK offect data
//            If(LEqual(\_SB.PCI0.LPCB.H_EC.ECRD(RefOf(\_SB.PCI0.LPCB.H_EC.DOCK)), 0))
//            { // If not docked then it's hot plug
//            }
          }
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP08.HPSX)
      }
    }

    // Check Root Port 9 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP09.VDID,0xFFFFFFFF),\_SB.PCI0.RP09.HPSX))
    {
      If(\_SB.PCI0.RP09.PDCX)
      {
        Store(1,\_SB.PCI0.RP09.PDCX)
        Store(1,\_SB.PCI0.RP09.HPSX)

        If(LNot(\_SB.PCI0.RP09.PDSX)) {
          Store(0,\_SB.PCI0.RP09.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP09.HPSX)
      }
    }

    // Check Root Port 10 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP10.VDID,0xFFFFFFFF),\_SB.PCI0.RP10.HPSX))
    {
      If(\_SB.PCI0.RP10.PDCX)
      {
        Store(1,\_SB.PCI0.RP10.PDCX)
        Store(1,\_SB.PCI0.RP10.HPSX)

        If(LNot(\_SB.PCI0.RP10.PDSX)) {
          Store(0,\_SB.PCI0.RP10.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP10.HPSX)
      }
    }

    // Check Root Port 11 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP11.VDID,0xFFFFFFFF),\_SB.PCI0.RP11.HPSX))
    {
      If(\_SB.PCI0.RP11.PDCX)
      {
        Store(1,\_SB.PCI0.RP11.PDCX)
        Store(1,\_SB.PCI0.RP11.HPSX)

        If(LNot(\_SB.PCI0.RP11.PDSX)) {
          Store(0,\_SB.PCI0.RP11.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP11.HPSX)
      }
    }

    // Check Root Port 12 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP12.VDID,0xFFFFFFFF),\_SB.PCI0.RP12.HPSX))
    {
      If(\_SB.PCI0.RP12.PDCX)
      {
        Store(1,\_SB.PCI0.RP12.PDCX)
        Store(1,\_SB.PCI0.RP12.HPSX)

        If(LNot(\_SB.PCI0.RP12.PDSX)) {
          Store(0,\_SB.PCI0.RP12.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP12.HPSX)
      }
    }

    // Check Root Port 13 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP13.VDID,0xFFFFFFFF),\_SB.PCI0.RP13.HPSX))
    {
      If(\_SB.PCI0.RP13.PDCX)
      {
        Store(1,\_SB.PCI0.RP13.PDCX)
        Store(1,\_SB.PCI0.RP13.HPSX)

        If(LNot(\_SB.PCI0.RP13.PDSX)) {
          Store(0,\_SB.PCI0.RP13.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP13.HPSX)
      }
    }

    // Check Root Port 14 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP14.VDID,0xFFFFFFFF),\_SB.PCI0.RP14.HPSX))
    {
      If(\_SB.PCI0.RP14.PDCX)
      {
        Store(1,\_SB.PCI0.RP14.PDCX)
        Store(1,\_SB.PCI0.RP14.HPSX)

        If(LNot(\_SB.PCI0.RP14.PDSX)) {
          Store(0,\_SB.PCI0.RP14.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP14.HPSX)
      }
    }

    // Check Root Port 15 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP15.VDID,0xFFFFFFFF),\_SB.PCI0.RP15.HPSX))
    {
      If(\_SB.PCI0.RP15.PDCX)
      {
        Store(1,\_SB.PCI0.RP15.PDCX)
        Store(1,\_SB.PCI0.RP15.HPSX)

        If(LNot(\_SB.PCI0.RP15.PDSX)) {
          Store(0,\_SB.PCI0.RP15.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP15.HPSX)
      }
    }

    // Check Root Port 16 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP16.VDID,0xFFFFFFFF),\_SB.PCI0.RP16.HPSX))
    {
      If(\_SB.PCI0.RP16.PDCX)
      {
        Store(1,\_SB.PCI0.RP16.PDCX)
        Store(1,\_SB.PCI0.RP16.HPSX)

        If(LNot(\_SB.PCI0.RP16.PDSX)) {
          Store(0,\_SB.PCI0.RP16.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP16.HPSX)
      }
    }

    // Check Root Port 17 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP17.VDID,0xFFFFFFFF),\_SB.PCI0.RP17.HPSX))
    {
      If(\_SB.PCI0.RP17.PDCX)
      {
        Store(1,\_SB.PCI0.RP17.PDCX)
        Store(1,\_SB.PCI0.RP17.HPSX)

        If(LNot(\_SB.PCI0.RP17.PDSX)) {
          Store(0,\_SB.PCI0.RP17.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP17.HPSX)
      }
    }

    // Check Root Port 18 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP18.VDID,0xFFFFFFFF),\_SB.PCI0.RP18.HPSX))
    {
      If(\_SB.PCI0.RP18.PDCX)
      {
        Store(1,\_SB.PCI0.RP18.PDCX)
        Store(1,\_SB.PCI0.RP18.HPSX)

        If(LNot(\_SB.PCI0.RP18.PDSX)) {
          Store(0,\_SB.PCI0.RP18.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP18.HPSX)
      }
    }

    // Check Root Port 19 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP19.VDID,0xFFFFFFFF),\_SB.PCI0.RP19.HPSX))
    {
      If(\_SB.PCI0.RP19.PDCX)
      {
        Store(1,\_SB.PCI0.RP19.PDCX)
        Store(1,\_SB.PCI0.RP19.HPSX)

        If(LNot(\_SB.PCI0.RP19.PDSX)) {
          Store(0,\_SB.PCI0.RP19.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP19.HPSX)
      }
    }

    // Check Root Port 20 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP20.VDID,0xFFFFFFFF),\_SB.PCI0.RP20.HPSX))
    {
      If(\_SB.PCI0.RP20.PDCX)
      {
        Store(1,\_SB.PCI0.RP20.PDCX)
        Store(1,\_SB.PCI0.RP20.HPSX)

        If(LNot(\_SB.PCI0.RP20.PDSX)) {
          Store(0,\_SB.PCI0.RP20.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP20.HPSX)
      }
    }
    // Check Root Port 21 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP21.VDID,0xFFFFFFFF),\_SB.PCI0.RP21.HPSX))
    {
      If(\_SB.PCI0.RP21.PDCX)
      {
        Store(1,\_SB.PCI0.RP21.PDCX)
        Store(1,\_SB.PCI0.RP21.HPSX)

        If(LNot(\_SB.PCI0.RP21.PDSX)) {
          Store(0,\_SB.PCI0.RP21.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP21.HPSX)
      }
    }

    // Check Root Port 22 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP22.VDID,0xFFFFFFFF),\_SB.PCI0.RP22.HPSX))
    {
      If(\_SB.PCI0.RP22.PDCX)
      {
        Store(1,\_SB.PCI0.RP22.PDCX)
        Store(1,\_SB.PCI0.RP22.HPSX)

        If(LNot(\_SB.PCI0.RP22.PDSX)) {
          Store(0,\_SB.PCI0.RP22.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP22.HPSX)
      }
    }

    // Check Root Port 23 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP23.VDID,0xFFFFFFFF),\_SB.PCI0.RP23.HPSX))
    {
      If(\_SB.PCI0.RP23.PDCX)
      {
        Store(1,\_SB.PCI0.RP23.PDCX)
        Store(1,\_SB.PCI0.RP23.HPSX)

        If(LNot(\_SB.PCI0.RP23.PDSX)) {
          Store(0,\_SB.PCI0.RP23.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP23.HPSX)
      }
    }

    // Check Root Port 24 for a Hot Plug Event if the Port is
    // enabled.

    If(LAnd(LNotEqual(\_SB.PCI0.RP24.VDID,0xFFFFFFFF),\_SB.PCI0.RP24.HPSX))
    {
      If(\_SB.PCI0.RP24.PDCX)
      {
        Store(1,\_SB.PCI0.RP24.PDCX)
        Store(1,\_SB.PCI0.RP24.HPSX)

        If(LNot(\_SB.PCI0.RP24.PDSX)) {
          Store(0,\_SB.PCI0.RP24.L0SE)
        }
      }
      Else
      {
        Store(1,\_SB.PCI0.RP24.HPSX)
      }
    }
    //
    // The iTBT PCIe Hot-Plug event
    //
    If (CondRefOf(\_SB.PCI1)) {
      // Check iTBT PCIe Root Port 0 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI1.TRP0.VDID,0xFFFFFFFF),\_SB.PCI1.TRP0.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI1.TRP0.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI1.TRP0.PDCX)
          Store(1,\_SB.PCI1.TRP0.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI1.TRP0.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI1.TRP0.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x00)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI1.TRP0,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI1.TRP0.HPSX)
        }
      }

      // Check iTBT PCIe Root Port 1 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI1.TRP1.VDID,0xFFFFFFFF),\_SB.PCI1.TRP1.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI1.TRP1.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI1.TRP1.PDCX)
          Store(1,\_SB.PCI1.TRP1.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI1.TRP1.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI1.TRP1.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x01)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI1.TRP1,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI1.TRP1.HPSX)
        }
      }

      // Check iTBT PCIe Root Port 2 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI1.TRP2.VDID,0xFFFFFFFF),\_SB.PCI1.TRP2.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI1.TRP2.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI1.TRP2.PDCX)
          Store(1,\_SB.PCI1.TRP2.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI1.TRP2.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI1.TRP2.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x02)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI1.TRP2,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI1.TRP2.HPSX)
        }
      }

      // Check iTBT PCIe Root Port 3 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI1.TRP3.VDID,0xFFFFFFFF),\_SB.PCI1.TRP3.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI1.TRP3.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI1.TRP3.PDCX)
          Store(1,\_SB.PCI1.TRP3.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI1.TRP3.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI1.TRP3.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x03)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI1.TRP3,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI1.TRP3.HPSX)
        }
      }

      // Check iTBT PCIe Root Port 4 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI1.TRP4.VDID,0xFFFFFFFF),\_SB.PCI1.TRP4.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI1.TRP4.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI1.TRP4.PDCX)
          Store(1,\_SB.PCI1.TRP4.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI1.TRP4.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI1.TRP4.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x04)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI1.TRP4,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI1.TRP4.HPSX)
        }
      }

      // Check iTBT PCIe Root Port 5 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI1.TRP5.VDID,0xFFFFFFFF),\_SB.PCI1.TRP5.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI1.TRP5.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI1.TRP5.PDCX)
          Store(1,\_SB.PCI1.TRP5.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI1.TRP5.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI1.TRP5.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x05)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI1.TRP5,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI1.TRP5.HPSX)
        }
      }
    } Else {
      // Check iTBT PCIe Root Port 0 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI0.TRP0.VDID,0xFFFFFFFF),\_SB.PCI0.TRP0.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI0.TRP0.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI0.TRP0.PDCX)
          Store(1,\_SB.PCI0.TRP0.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI0.TRP0.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI0.TRP0.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x00)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI0.TRP0,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI0.TRP0.HPSX)
        }
      }

      // Check iTBT PCIe Root Port 1 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI0.TRP1.VDID,0xFFFFFFFF),\_SB.PCI0.TRP1.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI0.TRP1.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI0.TRP1.PDCX)
          Store(1,\_SB.PCI0.TRP1.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI0.TRP1.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI0.TRP1.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x01)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI0.TRP1,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI0.TRP1.HPSX)
        }
      }

      // Check iTBT PCIe Root Port 2 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI0.TRP2.VDID,0xFFFFFFFF),\_SB.PCI0.TRP2.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

         Sleep(100)

        If(\_SB.PCI0.TRP2.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI0.TRP2.PDCX)
          Store(1,\_SB.PCI0.TRP2.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI0.TRP2.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI0.TRP2.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x02)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI0.TRP2,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI0.TRP2.HPSX)
        }
      }

      // Check iTBT PCIe Root Port 3 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI0.TRP3.VDID,0xFFFFFFFF),\_SB.PCI0.TRP3.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI0.TRP3.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI0.TRP3.PDCX)
          Store(1,\_SB.PCI0.TRP3.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI0.TRP3.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI0.TRP3.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x03)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI0.TRP3,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI0.TRP3.HPSX)
        }
      }

      // Check iTBT PCIe Root Port 4 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI0.TRP4.VDID,0xFFFFFFFF),\_SB.PCI0.TRP4.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI0.TRP4.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI0.TRP4.PDCX)
          Store(1,\_SB.PCI0.TRP4.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI0.TRP4.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI0.TRP4.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x04)
          }
          // Perform proper notification
          // to the OS.
          Notify(\_SB.PCI0.TRP4,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI0.TRP4.HPSX)
        }
      }

      // Check iTBT PCIe Root Port 5 for a Hot Plug Event if the Port is
      // enabled.

      If(LAnd(LNotEqual(\_SB.PCI0.TRP5.VDID,0xFFFFFFFF),\_SB.PCI0.TRP5.HPSX))
      {
        // Delay for 100ms to meet the timing requirements
        // of the PCI Express Base Specification, Revision
        // 1.0A, Section 6.6 ("...software must wait at
        // least 100ms from the end of reset of one or more
        // device before it is permitted to issue
        // Configuration Requests to those devices").

        Sleep(100)

        If(\_SB.PCI0.TRP5.PDCX)
        {
          // Clear all status bits first.

          Store(1,\_SB.PCI0.TRP5.PDCX)
          Store(1,\_SB.PCI0.TRP5.HPSX)

          //
          // PCH BIOS Spec Update Rev 1.03, Section 8.9 PCI Express* Hot-Plug BIOS Support
          // In addition, BIOS should intercept Presence Detect Changed interrupt, enable L0s on
          // hot plug and disable L0s on hot unplug. BIOS should also make sure the L0s is
          // disabled on empty slots prior booting to OS.
          //
          If(LNot(\_SB.PCI0.TRP5.PDSX)) {
            // The PCI Express slot is empty, so disable L0s on hot unplug
            //
            Store(0,\_SB.PCI0.TRP5.L0SE)

          }
          // Call Handler for Bios assisted enumeration
          // Handler uses syncronization algoritham to enumerate one Root port
          // at a time
          If(LEqual(ITBS, 1))
          {
            \_GPE.ITBT(0x05)
          }
          // Perform proper notification
          // to the OS.
            Notify(\_SB.PCI0.TRP5,0)
        }
        Else
        {
          // False event.  Clear Hot-Plug Status
          // then exit.

          Store(1,\_SB.PCI0.TRP5.HPSX)
        }
      }
    }
  }

  //
  // Software GPE caused the event.
  //
  Method(_L62)
  {
    // Clear GPE status bit.
    Store(0,GPEC)

    //
    // Handle DTS Thermal SCI Event.
    //
    If(CondRefOf(\_SB.DTSE)){
      If(LGreaterEqual(\_SB.DTSE, 0x01)){
        If(LEqual(\_SB.DTSI, 1)){
          Notify(\_TZ.TZ00,0x80)
          Notify(\_TZ.TZ01,0x80)
          ///
          /// Clear HWP interrupt status
          ///
          Store(0,\_SB.DTSI)
        }
      }
    }
    ///
    /// Handle HWP SCI event
    ///
    If (LEqual(\_SB.HWPI, 1)) {
      If (CondRefOf(\_GPE.HLVT)) {
        \_GPE.HLVT()
      }
      ///
      /// Clear HWP interrupt status
      ///
      Store(0,\_SB.HWPI)
    }
    ///
    /// Handle Intel Turbo Boost Max Technology 3.0 SCI event
    ///
    If (LEqual(\_SB.ITBI, 1)) {
      If (CondRefOf(\_GPE.ITBH)) {
        \_GPE.ITBH()
      }
      ///
      /// Clear interrupt status
      ///
      Store(0,\_SB.ITBI)
    }
  }

  // IGD OpRegion SCI event (see IGD OpRegion/Software SCI BIOS SPEC).

  Method(_L66)
  {
    If(LAnd(\_SB.PCI0.GFX0.GSSE, LNot(GSMI))) // Graphics software SCI event?
    {
      \_SB.PCI0.GFX0.GSCI() // Handle the SWSCI
    }
  }

}
