/** @file
 Thunderbolt ACPI methods

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
#define DTBT_TYPE_PCH                     0x01
#define DTBT_TYPE_PEG                     0x02

#ifndef  BIT29
#define  BIT29    0x20000000
#endif

Name (DTNB, 0xFFFF0000)  // DTBT NVS Base address
Name (DTNL, 0xAA55)      // DTBT NVS Length
Include ("DTbtNvs.asl")

External(\_SB.PC00.RP02.L23D, MethodObj)
External(\_SB.PC00.RP03.L23D, MethodObj)
External(\_SB.PC00.RP04.L23D, MethodObj)
External(\_SB.PC00.RP05.L23D, MethodObj)
External(\_SB.PC00.RP06.L23D, MethodObj)
External(\_SB.PC00.RP07.L23D, MethodObj)
External(\_SB.PC00.RP08.L23D, MethodObj)
External(\_SB.PC00.RP09.L23D, MethodObj)
External(\_SB.PC00.RP10.L23D, MethodObj)
External(\_SB.PC00.RP11.L23D, MethodObj)
External(\_SB.PC00.RP12.L23D, MethodObj)
External(\_SB.PC00.RP13.L23D, MethodObj)
External(\_SB.PC00.RP14.L23D, MethodObj)
External(\_SB.PC00.RP15.L23D, MethodObj)
External(\_SB.PC00.RP16.L23D, MethodObj)
External(\_SB.PC00.RP17.L23D, MethodObj)
External(\_SB.PC00.RP18.L23D, MethodObj)
External(\_SB.PC00.RP19.L23D, MethodObj)
External(\_SB.PC00.RP20.L23D, MethodObj)
External(\_SB.PC00.RP21.L23D, MethodObj)
External(\_SB.PC00.RP22.L23D, MethodObj)
External(\_SB.PC00.RP23.L23D, MethodObj)
External(\_SB.PC00.RP24.L23D, MethodObj)

External(\_SB.PC00.RP01.DL23, MethodObj)
External(\_SB.PC00.RP02.DL23, MethodObj)
External(\_SB.PC00.RP03.DL23, MethodObj)
External(\_SB.PC00.RP04.DL23, MethodObj)
External(\_SB.PC00.RP05.DL23, MethodObj)
External(\_SB.PC00.RP06.DL23, MethodObj)
External(\_SB.PC00.RP07.DL23, MethodObj)
External(\_SB.PC00.RP08.DL23, MethodObj)
External(\_SB.PC00.RP09.DL23, MethodObj)
External(\_SB.PC00.RP10.DL23, MethodObj)
External(\_SB.PC00.RP11.DL23, MethodObj)
External(\_SB.PC00.RP12.DL23, MethodObj)
External(\_SB.PC00.RP13.DL23, MethodObj)
External(\_SB.PC00.RP14.DL23, MethodObj)
External(\_SB.PC00.RP15.DL23, MethodObj)
External(\_SB.PC00.RP16.DL23, MethodObj)
External(\_SB.PC00.RP17.DL23, MethodObj)
External(\_SB.PC00.RP18.DL23, MethodObj)
External(\_SB.PC00.RP19.DL23, MethodObj)
External(\_SB.PC00.RP20.DL23, MethodObj)
External(\_SB.PC00.RP21.DL23, MethodObj)
External(\_SB.PC00.RP22.DL23, MethodObj)
External(\_SB.PC00.RP23.DL23, MethodObj)
External(\_SB.PC00.RP24.DL23, MethodObj)

External(\_SB.PC00.RTEN, MethodObj)
External(\_SB.PC00.RTDS, MethodObj)

  //
  // Name: TBTD
  // Description: Function to return the TBT RP# device no
  // Input: Arg0 -> Tbt Root Port value from Tbt NVS
  // Input: Arg1 -> Tbt port type value from Tbt NVS
  // Return: TBT RP# device no
  //
  Method(TBTD, 2, Serialized)
  {
    ADBG("TBTD")
    If (LEqual(Arg1, DTBT_TYPE_PCH)) {
      Switch(ToInteger(Arg0))
      {
        Case (Package () {1, 2, 3, 4, 5, 6, 7, 8})
        {
          Store(0x1C, Local0) //Device28-Function0...Function7 = 11100.000...111
        }
        Case (Package () {9, 10, 11, 12, 13, 14, 15, 16})
        {
          Store(0x1D, Local0) //Device29-Function0...Function7 = 11101.000...111
        }
        Case (Package () {17, 18, 19, 20, 21, 22, 23, 24})
        {
          Store(0x1B, Local0) //Device27-Function0...Function3 = 11011.000...011
        }
      }
    } ElseIf (LEqual(Arg1, DTBT_TYPE_PEG)) {
      Switch(ToInteger(Arg0))
      {
        Case (Package () {1, 2, 3})
        {
          Store(0x1, Local0) //Device1-Function0...Function2 = 00001.000...010
        }
        Case (Package () {4})
        {
          Store(0x6, Local0) //Device6-Function0 = 00110.000
        }
      }
    } Else {
      Store(0xFF, Local0)
    }

    ADBG("Device no")
    ADBG(Local0)

    Return(Local0)
  } // End of Method(TBTD, 2, Serialized)

  //
  // Name: TBTF
  // Description: Function to return the TBT RP# function no
  // Input: Arg0 -> Tbt Root Port value from Tbt NVS
  // Input: Arg1 -> Tbt port type value from Tbt NVS
  // Return: TBT RP# function no
  //
  Method(TBTF, 2, Serialized)
  {
    ADBG("TBTF")
    If (LEqual(Arg1, DTBT_TYPE_PCH)) {
      Switch(ToInteger(Arg0))
      {
        Case (1)
        {
          Store(And(\RPA1,0xF), Local0) //Device28-Function0 = 11100.000
        }
        Case (2)
        {
          Store(And(\RPA2,0xF), Local0) //Device28-Function1 = 11100.001
        }
        Case (3)
        {
          Store(And(\RPA3,0xF), Local0) //Device28-Function2 = 11100.010
        }
        Case (4)
        {
          Store(And(\RPA4,0xF), Local0) //Device28-Function3 = 11100.011
        }
        Case (5)
        {
          Store(And(\RPA5,0xF), Local0) //Device28-Function4 = 11100.100
        }
        Case (6)
        {
          Store(And(\RPA6,0xF), Local0) //Device28-Function5 = 11100.101
        }
        Case (7)
        {
          Store(And(\RPA7,0xF), Local0) //Device28-Function6 = 11100.110
        }
        Case (8)
        {
          Store(And(\RPA8,0xF), Local0) //Device28-Function7 = 11100.111
        }
        Case (9)
        {
          Store(And(\RPA9,0xF), Local0) //Device29-Function0 = 11101.000
        }
        Case (10)
        {
          Store(And(\RPAA,0xF), Local0) //Device29-Function1 = 11101.001
        }
        Case (11)
        {
          Store(And(\RPAB,0xF), Local0) //Device29-Function2 = 11101.010
        }
        Case (12)
        {
          Store(And(\RPAC,0xF), Local0) //Device29-Function3 = 11101.011
        }
        Case (13)
        {
          Store(And(\RPAD,0xF), Local0) //Device29-Function4 = 11101.100
        }
        Case (14)
        {
          Store(And(\RPAE,0xF), Local0) //Device29-Function5 = 11101.101
        }
        Case (15)
        {
          Store(And(\RPAF,0xF), Local0) //Device29-Function6 = 11101.110
        }
        Case (16)
        {
          Store(And(\RPAG,0xF), Local0) //Device29-Function7 = 11101.111
        }
        Case (17)
        {
          Store(And(\RPAH,0xF), Local0) //Device27-Function0 = 11011.000
        }
        Case (18)
        {
          Store(And(\RPAI,0xF), Local0) //Device27-Function1 = 11011.001
        }
        Case (19)
        {
          Store(And(\RPAJ,0xF), Local0) //Device27-Function2 = 11011.010
        }
        Case (20)
        {
          Store(And(\RPAK,0xF), Local0) //Device27-Function3 = 11011.011
        }
        Case (21)
        {
          Store(And(\RPAL,0xF), Local0) //Device27-Function4 = 11011.100
        }
        Case (22)
        {
          Store(And(\RPAM,0xF), Local0) //Device27-Function5 = 11011.101
        }
        Case (23)
        {
          Store(And(\RPAN,0xF), Local0) //Device27-Function6 = 11011.110
        }
        Case (24)
        {
          Store(And(\RPAO,0xF), Local0) //Device27-Function7 = 11011.111
        }
      }
    } ElseIf (LEqual(Arg1, DTBT_TYPE_PEG)) {
      Switch(ToInteger(Arg0))
      {
        Case (1)
        {
          Store(0x0, Local0) //Device1-Function0 = 00001.000
        }
        Case (2)
        {
          Store(0x1, Local0) //Device1-Function1 = 00001.001
        }
        Case (3)
        {
          Store(0x2, Local0) //Device1-Function2 = 00001.010
        }
        Case (4)
        {
          Store(0x0, Local0) //Device6-Function0 = 00110.000
        }
      }
    } Else {
      Store(0xFF, Local0)
    }

    ADBG("Function no")
    ADBG(Local0)

    Return(Local0)
  } // End of Method(TBTF, 2, Serialized)

  //
  // Name: MMRP
  // Description: Function to return the Pci base address of TBT rootport
  // Input: Arg0 -> Tbt Root Port value from Tbt NVS
  // Input: Arg1 -> Tbt port type value from Tbt NVS
  //

  Method(MMRP, 2, Serialized)
  {
    Store(\_SB.PC00.GPCB(), Local0) // MMIO Base address
    Add(Local0, ShiftLeft(TBTD(Arg0, Arg1), 15), Local0) // Device no
    Add(Local0, ShiftLeft(TBTF(Arg0, Arg1), 12), Local0) // Function no

    Return(Local0)
  } // End of Method(MMRP)

  //
  // Name: MMTB
  // Description: Function to return the Pci base address of TBT Up stream port
  // Input: Arg0 -> Tbt Root Port value from Tbt NVS
  // Input: Arg1 -> Tbt port type value from Tbt NVS
  //
  Method(MMTB, 2, Serialized)
  {
    ADBG("MMTB")

    Store(\_SB.PC00.GPCB(), Local0) // MMIO Base address

    Add(Local0, ShiftLeft(TBTD(Arg0, Arg1), 15), Local0) // Device no
    Add(Local0, ShiftLeft(TBTF(Arg0, Arg1), 12), Local0) // Function no

    OperationRegion (MMMM, SystemMemory, Local0, 0x1A)
    Field (MMMM, AnyAcc, NoLock, Preserve)
    {
      Offset(0x19),
      SBUS, 8
    }
    Store(SBUS, Local2)
    Store(\_SB.PC00.GPCB(), Local0)
    Multiply(Local2, 0x100000, Local2)
    Add(Local2, Local0, Local0) // TBT HR US port

    ADBG("TBT-US-ADR")
    ADBG(Local0)

    Return(Local0)
  } // End of Method(MMTB, 1, Serialized)
  //
  // Name: FFTB
  // Description: Function to  Check for FFFF in TBT PCIe
  // Input: Arg0 -> Tbt Root Port value from Tbt NVS
  // Input: Arg1 -> Tbt port type value from Tbt NVS
  // Return: 1 if TBT PCIe space has value FFFF, 0 if not
  //
  Method(FFTB, 2, Serialized)
  {
    ADBG("FFTB")

    Add(MMTB(Arg0, Arg1), 0x548, Local0)
    OperationRegion(PXVD,SystemMemory,Local0,0x08)
    Field(PXVD,DWordAcc, NoLock, Preserve)
    {
      TB2P, 32,
      P2TB, 32
    }

    Store(TB2P, Local1)

    If(LEqual(Local1, 0xFFFFFFFF))
    {
      ADBG("FFTb 1")
      Return (1)
    }
    Else
    {
      ADBG("FFTb 0")
      Return (0)
    }
  } // End of Method(FFTB)

Scope(\_GPE)
{
  //
  //
  //OS up Mail Box command execution to host router upstream port each time
  //exiting from Sx State .Avoids intermediate
  //PCIe Scan by OS during resorce allocation
  // Arg0 : PCIe Base address
  //Developer notes: Called twice
  // 1. During OS INIT (booting to OS from S3-S5/Reboot)
  // 2. Up on Hot plug
  //
  Method(DTOU, 1, Serialized)
  {
    ADBG("DTOU")

    Add(Arg0, 0x540, Local0)
    OperationRegion(PXVD,SystemMemory,Local0,0x10)
    Field(PXVD,DWordAcc, NoLock, Preserve)
    {
      Offset(0x08),
      DT2P, 32,
      DP2T, 32
    }

    Store(100, Local1)
    Store(0x0D, DP2T) // Write OS_Up to PCIe2TBT
    While(LGreater(Local1, 0))
    {
      Store(Subtract(Local1, 1), Local1)
      Store(DT2P, Local2)
      //Store(TB2P, Local2)
      If(LEqual(Local2, 0xFFFFFFFF))// Device gone
      {
        ADBG("Dev gone")
        Return(2)
      }
      If(And(Local2, 1)) // Done
      {
        ADBG("Cmd acknowledged")
        break
      }
      Sleep(50)
    }
    //Store(0x00, P2TB) // Write 0 to PCIe2TBT

    ADBG("End-of-DTOU")

    Return(1)
  } // End of Method(DTOU, 1, Serialized)

  //
  // Check for FFFF in TBT
  // Input: Arg0 -> Tbt Root Port value from Tbt NVS
  // Input: Arg1 -> Tbt port type value from Tbt NVS
  //

  Method(TBFF, 2, Serialized)
  {
    ADBG("TBFF")

    Store(MMTB(Arg0, Arg1), Local0)
    OperationRegion(PXVD,SystemMemory,Local0,0x4)
    Field(PXVD,DWordAcc, NoLock, Preserve)
    {
      VEDI, 32 // Vendor/Device ID
    }
    Store(VEDI, Local1)

    If(LEqual(Local1, 0xFFFFFFFF))
    {
      Return (DTOU(Local0))
    }
    Else
    {
      ADBG("Dev Present")
      Return (0)
    }
  } // End of Method(TBFF, 1, Serialized)

  //
  // Secondary bus of TBT RP
  // Input: Arg0 -> Tbt Root Port value from Tbt NVS
  // Input: Arg1 -> Tbt port type value from Tbt NVS
  //

  Method(TSUB, 2, Serialized)
  {
    ADBG("TSUB")

    Store(\_SB.PC00.GPCB(), Local0) // MMIO Base address

    Add(Local0, ShiftLeft(TBTD(Arg0, Arg1), 15), Local0) // Device no
    Add(Local0, ShiftLeft(TBTF(Arg0, Arg1), 12), Local0) // Function no

    ADBG("ADR")
    ADBG(Local0)

    OperationRegion (MMMM, SystemMemory, Local0, 0x1A)
    Field (MMMM, AnyAcc, NoLock, Preserve)
    {
      Offset(0x19),
      SBUS, 8
    }

    ADBG("Sec Bus")
    ADBG(SBUS)

    Return(SBUS)
  } // End of Method(TSUB, 0, Serialized)

  //
  // Pmem of TBT RP
  // Input: Arg0 -> Tbt Root Port value from Tbt NVS
  // Input: Arg1 -> Tbt port type value from Tbt NVS
  //

  Method(TSUP, 2, Serialized)
  {
    ADBG("TSUP")

    Store(\_SB.PC00.GPCB(), Local0) // MMIO Base address

    Add(Local0, ShiftLeft(TBTD(Arg0, Arg1), 15), Local0) // Device no
    Add(Local0, ShiftLeft(TBTF(Arg0, Arg1), 12), Local0) // Function no

    ADBG("ADR:")
    ADBG(Local0)

    OperationRegion (MMMM, SystemMemory, Local0, 0x30)
    Field (MMMM, AnyAcc, NoLock, Preserve)
    {
      CMDS, 32,
      Offset(0x19),
      SBUS, 8,
      SBU5, 8,
      Offset(0x1C),
      SEIO, 32,
      MMBL, 32,
      PMBL, 32,

    }

    ADBG("Pmem of TBT RP:")
    ADBG(PMBL)

    Return(PMBL)
  } // End of Method(TSUP, 0, Serialized)

  //
  // Wait for secondary bus in TBT RP
  // Input: Arg0 -> Tbt Root Port value from Tbt NVS
  // Input: Arg1 -> Tbt port type value from Tbt NVS
  //

  Method(WSUB, 2, Serialized)
  {
    ADBG(Concatenate("WSUB=", ToHexString(Arg0)))
    ADBG(ToHexString(Timer))

    Store(0, Local0)
    Store(0, Local1)
    While(1)
    {
      Store(TSUP(Arg0, Arg1), Local1)
      If(LGreater(Local1, 0x1FFF1))
      {
        ADBG("WSUB-Finished")
        Break
      }
      Else
      {
        Add(Local0, 1, Local0)
        If(LGreater(Local0, 1000))
        {
          Sleep(1000)
          ADBG("WSUB-Deadlock")
        }
        Else
        {
          Sleep(16)
        }
      }
    }
     ADBG(Concatenate("WSUb=", ToHexString(Local1)))
  } // End of Method(WSUB)

  // Wait for _WAK finished
  Method(WWAK)
  {
    ADBG("WWAK")

    Wait(WFEV, 0xFFFF)
    Signal(WFEV) // Set it, to enter on next HP
  } // End of Method(WWAK)

  Method(NTFY, 2, Serialized)
  {
    ADBG("NTFY")

    If(LEqual(DTHN,1))
    {
      If (LEqual(Arg1, DTBT_TYPE_PCH)) {
        Switch(ToInteger(Arg0)) // TBT Selector
        {
          Case (1)
          {
            ADBG("Notify RP01")
            Notify(\_SB.PC00.RP01,0)
          }
          Case (2)
          {
            ADBG("Notify RP02")
            Notify(\_SB.PC00.RP02,0)
          }
          Case (3)
          {
            ADBG("Notify RP03")
            Notify(\_SB.PC00.RP03,0)
          }
          Case (4)
          {
            ADBG("Notify RP04")
            Notify(\_SB.PC00.RP04,0)
          }
          Case (5)
          {
            ADBG("Notify RP05")
            Notify(\_SB.PC00.RP05,0)
          }
          Case (6)
          {
            ADBG("Notify RP06")
            Notify(\_SB.PC00.RP06,0)
          }
          Case (7)
          {
            ADBG("Notify RP07")
            Notify(\_SB.PC00.RP07,0)
          }
          Case (8)
          {
            ADBG("Notify RP08")
            Notify(\_SB.PC00.RP08,0)
          }
          Case (9)
          {
            ADBG("Notify RP09")
            Notify(\_SB.PC00.RP09,0)
          }
          Case (10)
          {
            ADBG("Notify RP10")
            Notify(\_SB.PC00.RP10,0)
          }
          Case (11)
          {
            ADBG("Notify RP11")
            Notify(\_SB.PC00.RP11,0)
          }
          Case (12)
          {
            ADBG("Notify RP12")
            Notify(\_SB.PC00.RP12,0)
          }
          Case (13)
          {
            ADBG("Notify RP13")
            Notify(\_SB.PC00.RP13,0)
          }
          Case (14)
          {
            ADBG("Notify RP14")
            Notify(\_SB.PC00.RP14,0)
          }
          Case (15)
          {
            ADBG("Notify RP15")
            Notify(\_SB.PC00.RP15,0)
          }
          Case (16)
          {
            ADBG("Notify RP16")
            Notify(\_SB.PC00.RP16,0)
          }
          Case (17)
          {
            ADBG("Notify RP17")
            Notify(\_SB.PC00.RP17,0)
          }
          Case (18)
          {
            ADBG("Notify RP18")
            Notify(\_SB.PC00.RP18,0)
          }
          Case (19)
          {
            ADBG("Notify RP19")
            Notify(\_SB.PC00.RP19,0)
          }
          Case (20)
          {
            ADBG("Notify RP20")
            Notify(\_SB.PC00.RP20,0)
          }
          Case (21)
          {
            ADBG("Notify RP21")
            Notify(\_SB.PC00.RP21,0)
          }
          Case (22)
          {
            ADBG("Notify RP22")
            Notify(\_SB.PC00.RP22,0)
          }
          Case (23)
          {
            ADBG("Notify RP23")
            Notify(\_SB.PC00.RP23,0)
          }
          Case (24)
          {
            ADBG("Notify RP24")
            Notify(\_SB.PC00.RP24,0)
          }
        }//Switch(ToInteger(TBSS)) // TBT Selector
      } ElseIf (LEqual(Arg1, DTBT_TYPE_PEG)) {
        Switch(ToInteger(Arg0))
        {
          Case (1)
          {
            ADBG("Notify PEG0")
            Notify(\_SB.PC00.PEG0,0)
          }
          Case (2)
          {
            ADBG("Notify PEG1")
            Notify(\_SB.PC00.PEG1,0)
          }
          Case (3)
          {
            ADBG("Notify PEG2")
            Notify(\_SB.PC00.PEG2,0)
          }
          Case (4)
          {
            ADBG("Notify PEG3")
            Notify(\_SB.PC00.PEG3,0)
          }
        }
      }//Switch(ToInteger(TBSS)) // TBT Selector
    }//If(NOHP())
    P8XH(0,0xC2)
    P8XH(1,0xC2)
  }// End of Method(NTFY)

//
//  TBT BIOS, GPIO 5 filtering,
//  Hot plug of 12V USB devices, into TBT host router, cause electrical noise on PCH GPIOs,
//  This noise cause false hot-plug events, and negatively influence BIOS assisted hot-plug.
//  PCH GPIO does not implement Glitch Filter logic (refer to GPIO HAS) on any GPIO pad. Native functions have to implement their own digital glitch-filter logic
//  if needed. As HW filter was not implemented on PCH, because of that SW workaround should be implemented in BIOS.
//  Register 0x544(Bios mailbox) bit 0 definition:
//  if BIOS reads bit as 1, BIOS will clear the bit and continue normal flow, if bit is 0 BIOS will exit from method
//

  Method(GNIS,2, Serialized)
  {

    ADBG("GNIS")
    If(LEqual(GP5F, 0))
    {
      ADBG("GNIS_Dis=0")
      Return(0)
    }
    //
    // BIOS mailbox command for GPIO filter
    //
    Add(MMTB(Arg0, Arg1), 0x544, Local0)
    OperationRegion(PXVD,SystemMemory,Local0,0x08)

    Field(PXVD,DWordAcc, NoLock, Preserve)
    {
      HPFI, 1,
      Offset(0x4),
      TB2P, 32
    }
    Store(TB2P, Local1)
    ADBG(Concatenate("TB2P=", ToHexString(Local1)))
    If(LEqual(Local1, 0xFFFFFFFF)) // Disconnect?
    {
      ADBG("GNIS=0")
      Return(0)
    }
    Store(HPFI, Local2)
    ADBG(Concatenate("HPFI=", ToHexString(Local2)))
    If(LEqual(Local2, 0x01))
    {
      Store(0x00, HPFI)
      ADBG("GNIS=0")
      Return(0)
    }
    // Any other values treated as a GPIO noise
    ADBG("GNIS=1")
    Return(1)
  }

  Method(CHKP,2, Serialized)
  {
    Add(MMTB(Arg0, Arg1), 0x544, Local0)
    OperationRegion(PXVE,SystemMemory,Local0,0x08)

    Field(PXVE,DWordAcc, NoLock, Preserve)
    {
      HPFI, 1,
      Offset(0x4),
      TB2P, 32
    }
    Store(TB2P, Local1)
    And(Local1,BIT29,Local1)
    ADBG(Concatenate("Local1=", ToHexString(Local1)))
    //ADBG(Concatenate("BIT29=", ToHexString(LAnd(Local1,BIT29))))
    If(LEqual(Local1, BIT29))
    {
      Return(1)
    }
    Else
    {
      Return(0)
    }
  }

  //
  // Method to Handle enumerate PCIe structure through
  // SMI for Thunderbolt(TM) devices
  //
  Method(XTBT,2, Serialized)
  {
    ADBG("XTBT")
    ADBG("RP :")
    ADBG(Arg0)
    Store(Arg0, DTCP) // Root port to enumerate
    Store(Arg1, DTPT)   // Root port Type
    If(LNotEqual(Arg0, RPS0) && LNotEqual(Arg0, RPS1)) {
      Return ()
    }

    WWAK()
    WSUB(Arg0, Arg1)
    If(GNIS(Arg0, Arg1))
    {
      Return()
    }

    OperationRegion(SPRT,SystemIO, 0xB2,2)
    Field (SPRT, ByteAcc, Lock, Preserve)
    {
      SSMP, 8
    }

    ADBG("TBT-HP-Handler")

    Acquire(OSUM, 0xFFFF)
    Store(TBFF(Arg0, Arg1), Local1)
    If(LEqual(Local1, 1))// Only HR
    {
      Sleep(16)
      Release(OSUM)
      ADBG("OS_Up_Received")
      Return ()
    }
    If(LEqual(Local1, 2)) // Disconnect
    {
      NTFY(Arg0, Arg1)
      Sleep(16)
      Release(OSUM)
      ADBG("Disconnect")
      Return ()
    }

    // HR and EP
    If(LEqual(DTHS, 1))
    {
      // Trigger SMI to enumerate PCIe Structure
      ADBG("TBT SW SMI")
      Store(21, DTBF)
      Store(FixedPcdGet8(PcdSwSmiDTbtEnumerate), SSMP)
    }
    NTFY(Arg0, Arg1)
    Sleep(16)
    Release(OSUM)

    ADBG("End-of-XTBT")
  } // End of Method(XTBT)

  //
  // Calling Method to Handle enumerate PCIe structure through
  // SMI for Thunderbolt(TM) devices for Tier 1 GPIOs
  // Used in Two ways ,
  // If CIO GPIO(1 Tier) is Different for the Controllers, this will be used as 1 Tier GPIO Handler for 1st controller
  // If CIO GPIO(1 Tier) is Same for all the controllers, this will be used as 1 Tier GPIO Handler for All the controllers
  //
  Method(ATBT)
  {
    ADBG("ATBT")
    //
    // Calling Method to Handle enumerate PCIe structure through
    //
    If(LEqual(CGST,0)) { // If GPIO is Different for each controller
      If(LEqual(RPN0,1))
      {
        XTBT(RPS0, RPT0)
      }
    } Else {
      If(LEqual(RPN0,1))
      {
        XTBT(RPS0, RPT0)
      }
      ElseIf(LEqual(RPN1,1))
      {
        XTBT(RPS1, RPT1)
      }
    }
    ADBG("End-of-ATBT")
  } // End of Method(ATBT)

  Method(BTBT)
  {
    ADBG("BTBT")
    //
    // Calling Method to Handle enumerate PCIe structure through
    //
    If(LEqual(CGST,0)) { // If GPIO is Different for each controller
      If(LEqual(RPN1,1))
      {
        XTBT(RPS1, RPT1)
      }
    }
    ADBG("End-of-BTBT")
  } // End of Method(BTBT)

  //
  // Method to call OSPU Mail box command
  // Arg0 : TBT RP Selector / DMA
  // Arg1 : TBT Type (PCH or PEG)
  //
  Method(DINI, 2, Serialized)
  {
    ADBG("DINI")
    Store(MMRP(Arg0, Arg1), Local0)
    OperationRegion(RP_X,SystemMemory,Local0,0x20)
    Field(RP_X,DWordAcc, NoLock, Preserve)
    {
      REG0, 32,
      REG1, 32,
      REG2, 32,
      REG3, 32,
      REG4, 32,
      REG5, 32,
      REG6, 32,
      REG7, 32
    }
    Store(REG6, Local1)
    Store(0x00F0F000, REG6)
    Store(MMTB(Arg0, Arg1), Local2)
    DTOU(Local2)
    Store(Local1, REG6)
    ADBG("End-of-DINI")
  }

} // End of Scope (\_GPE)

Scope (\_SB)
{
  //
  // The code needs to be executed for TBT Hotplug Handler event (2-tier GPI GPE event architecture) is presented here
  //
  Method(THDR, 3, Serialized)
  {
    ADBG("THDR")
    \_SB.CAGS(Arg0)
    \_GPE.XTBT(Arg1, Arg2)
  } // End of Method(THDR, 3, Serialized)
} // End of Scope(\_SB)

Scope (\_SB)
{
  //
  // Name: CGWR [Combined GPIO Write]
  // Description: Function to write into GPIO
  // Input: Arg0 -> GpioPad / Expander pin
  //        Arg1 -> Value
  // Return: Nothing
  //
  Method(CGWR, 2, Serialized)
  {
    // PCH
    If (CondRefOf(\_SB.SGOV))
    {
      \_SB.SGOV(Arg0, Arg1)
    }
  } // End of Method(CGWR, 4, Serialized)

  //
  // Name: CGRD [Combined GPIO Read]
  // Description: Function to read from GPIO
  // Input: Arg0 -> GpioPad / Expander pin
  //        Arg1 -> 0: GPO [GPIO TX State]
  //                1: GPI [GPIO RX State]
  // Return: Value
  //
  Method(CGRD, 2, Serialized)
  {
    Store(1, Local0)
    // PCH
    If (LEqual(Arg1, 0))
    {
      // GPIO TX State
      If (CondRefOf(\_SB.GGOV))
      {
        Store(\_SB.GGOV(Arg0), Local0)
      }
    }
    ElseIf (LEqual(Arg1, 1))
    {
      // GPIO RX State
      If (CondRefOf(\_SB.GGIV))
      {
        Store(\_SB.GGIV(Arg0), Local0)
      }
    }
    Return(Local0)
  } // End of Method(CGRD, 4, Serialized)
  //
  // Name: WRGP [GPIO Write]
  // Description: Function to write into GPIO
  // Input: Arg0 -> COMMON_GPIO_CONFIG GpioInfo
  //        Arg1 -> Value
  // Return: Nothing
  //
  Method(WRGP, 2, Serialized)
  {
    Store(Arg0, Local0)
    Store(Arg0, Local1)
    And(Local0, 0xFFFFFFFF, Local0) // Low  32 bits (31:00)
    ShiftRight(Local1, 32, Local1)  // High 32 bits (63:32)
    If (LEqual(And(Local0, 0xFF), 1))
    {
      // PCH
      \_SB.CGWR(Local1, Arg1)
    }
  } // End of Method(WRGP, 2, Serialized)

  //
  // Name: RDGP [GPIO Read]
  // Description: Function to write into GPIO
  // Input: Arg0 -> COMMON_GPIO_CONFIG GpioInfo
  //        Arg1 -> In case of PCH Gpio Read {GPIO TX(0)/RX(1) State indicator}
  // Return: Value
  //
  Method(RDGP, 2, Serialized)
  {
    Store(1, Local7)
    Store(Arg0, Local0)
    Store(Arg0, Local1)
    And(Local0, 0xFFFFFFFF, Local0) // Low  32 bits (31:00)
    ShiftRight(Local1, 32, Local1)  // High 32 bits (63:32)
    If (LEqual(And(Local0, 0xFF), 1))
    {
      // PCH
      Store(\_SB.CGRD(Local1, Arg1), Local7)
    }
    Return(Local7)
  } // End of Method(RDGP, 2, Serialized)

} // End of Scope(\_SB)

Scope(\_SB)
{
  // Asserts/De-asserts TBT force power
  Method(TBFP, 2)
  {
    If(Arg0)
    {
      // Implementation dependent way to assert TBT force power
      If(LEqual(Arg1, 1)) {
        CGWR(FPG0, FP0L)
      }
      Else {
        CGWR(FPG1, FP1L)
      }
    }
    Else
    {
      // Implementation dependent way to de-assert TBT force power
      If(LEqual(Arg1, 1)) {
        CGWR(FPG0, LNot(FP0L))
      }
      Else {
        CGWR(FPG1, LNot(FP1L))
      }
    }
  }

  // WMI ACPI device to control TBT force power
  Device(WMTF)
  {
    // pnp0c14 is pnp id assigned to WMI mapper
    Name(_HID, "PNP0C14")
    Name(_UID, "TBFP")

    Name(_WDG, Buffer() {
      // {86CCFD48-205E-4A77-9C48-2021CBEDE341}
      0x48, 0xFD, 0xCC, 0x86,
      0x5E, 0x20,
      0x77, 0x4A,
      0x9C, 0x48,
      0x20, 0x21, 0xCB, 0xED, 0xE3, 0x41,
      84, 70,    // Object Id (TF)
      1,         // Instance Count
      0x02       // Flags (WMIACPI_REGFLAG_METHOD)
    })

    // Set TBT force power
    // Arg2 is force power value
    Method(WMTF, 3)
    {
      CreateByteField(Arg2,0,FP)

      If(FP)
      {
        TBFP(1, 1)
      }
      Else
      {
        TBFP(0, 1)
      }
    }
  }
} // End of Scope(\_SB)


If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 1),LEqual(RPS1, 1))))
{
  Scope(\_SB.PC00.RP01)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP01)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 2),LEqual(RPS1, 2))))
{
  Scope(\_SB.PC00.RP02)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP02)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 3),LEqual(RPS1, 3))))
{
  Scope(\_SB.PC00.RP03)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP03)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 4),LEqual(RPS1, 4))))
{
  Scope(\_SB.PC00.RP04)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP04)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 5),LEqual(RPS1, 5))))
{
  Scope(\_SB.PC00.RP05)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP05)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 6),LEqual(RPS1, 6))))
{
  Scope(\_SB.PC00.RP06)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP06)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 7),LEqual(RPS1, 7))))
{
  Scope(\_SB.PC00.RP07)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP07)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 8),LEqual(RPS1, 8))))
{
  Scope(\_SB.PC00.RP08)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP08)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 9),LEqual(RPS1, 9))))
{
  Scope(\_SB.PC00.RP09)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP09)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 10),LEqual(RPS1, 10))))
{
  Scope(\_SB.PC00.RP10)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP10)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 11),LEqual(RPS1, 11))))
{
  Scope(\_SB.PC00.RP11)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP11)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 12),LEqual(RPS1, 12))))
{
  Scope(\_SB.PC00.RP12)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP12)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 13),LEqual(RPS1, 13))))
{
  Scope(\_SB.PC00.RP13)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP13)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 14),LEqual(RPS1, 14))))
{
  Scope(\_SB.PC00.RP14)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP14)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 15),LEqual(RPS1, 15))))
{
  Scope(\_SB.PC00.RP15)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP15)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 16),LEqual(RPS1, 16))))
{
  Scope(\_SB.PC00.RP16)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP16)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 17),LEqual(RPS1, 17))))
{
  Scope(\_SB.PC00.RP17)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP17)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 18),LEqual(RPS1, 18))))
{
  Scope(\_SB.PC00.RP18)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP18)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 19),LEqual(RPS1, 19))))
{
  Scope(\_SB.PC00.RP19)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP19)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 20),LEqual(RPS1, 20))))
{
  Scope(\_SB.PC00.RP20)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.RP20)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 21),LEqual(RPS1, 21))))
{
  Scope(\_SB.PC00.PEG0)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.PEG0)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 22),LEqual(RPS1, 22))))
{
  Scope(\_SB.PC00.PEG1)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.PEG1)
}

If(LAnd(LEqual(TBTS, 1),LOr(LEqual(RPS0, 23),LEqual(RPS1, 23))))
{
  Scope(\_SB.PC00.PEG2)
  {
    Device(HRUS)// Host router Upstream port
    {
      Name(_ADR, 0x00000000)

      Method(_RMV)
      {
        Return(DTAR)
      } // end _RMV
    }
  }//End of Scope(\_SB.PC00.PEG2)
}
