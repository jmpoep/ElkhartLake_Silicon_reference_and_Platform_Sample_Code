/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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
// Defined as an SSDT to be able to dynamically load based on BIOS
// setup options
//
DefinitionBlock (
  "OverclockInterfaceAcpi.aml",
  "SSDT",
  0x02,
  "Intel",
  "PerfTune",
  0x1000
  )

{
  Scope(\_SB)
  {
    // External References to the actual data locations that stores
    // various temperature and Fan Speed values from EC.
    //

    // externs for TSDD
    External(\_SB.PC00.LPCB.H_EC.DIM0)    // DIMM0 Temperature
    External(\_SB.PC00.LPCB.H_EC.DIM1)    // DIMM1 Temperature
    External(\_TZ.TZ01._TMP, MethodObj)

    // externs for FSDD
    External(\_SB.PC00.LPCB.H_EC.CFSP)    // CPU Fan speed

    External(\_SB.PC00.LPCB.H_EC.ECRD, MethodObj)    // EC Read Method
    External(\_SB.PC00.LPCB.H_EC.ECWT, MethodObj)    // EC Write Method
    // Embedded Controller Availability Flag.
    External(\TSOD, IntObj)
    External(\ECON, IntObj)
    External(XTUB)
    External(XTUS)
    External(XMPB)
    External(DDRF)
    External(\ADBG, MethodObj)

    Device(PTMD)
    {
      Name(_HID, EISAID("INT3394"))
      Name(_CID, EISAID("PNP0C02"))
      Name(IVER, 0x00010000)
      Name(SIZE,0x55C)

      Method(GACI, 0x0, NotSerialized, 0, PkgObj)
      {
       Name(RPKG, Package(0x2){}) // Return Package

       Store(0x00, Index(RPKG, 0)) // Error Code

        If (LNotEqual(XTUB, Zero))
        {
         ADBG("XTUB")
         ADBG(XTUB)
         ADBG("XTUS")
         ADBG(XTUS)
         OperationRegion (XNVS, SystemMemory, XTUB, SIZE)
           Field (XNVS, ByteAcc, NoLock, Preserve) {
            XBUF, 0x2AE0              // Total Controls * 28 * 8, BitLength.
           }
         Name(TEMP, Buffer(XTUS){})
         Store(XBUF,TEMP)
         Store( TEMP, Index(RPKG, 1)) // Data buffer
       }
       Else
       {
        ADBG("XTUB ZERO")
        Store( 0, Index(RPKG, 1)) // Data buffer
       }
       Return(RPKG)
      }


      Method(GDSV, 0x1, Serialized, 0, PkgObj, IntObj)
      {
        If(LEqual(Arg0, 5))
        {
          Return(Package(0x2)
          {
            0x0, // Error code
            Buffer()
            {
              0, 0, 0, 0,    // Data value for auto
              0, 0, 0, 0,    // Display value
              1, 0, 0, 0,    // Data value
              0xb0, 4, 0, 0, // Display value
              2, 0, 0, 0,    // Data value
              0xe2, 4, 0, 0, // Display value
              3, 0, 0, 0,    // Data value
              0x14, 5, 0, 0, // Display value
              4, 0, 0, 0,    // Data value
              0x46, 5, 0, 0, // Display value
              5, 0, 0, 0,    // Data value
              0x78, 5, 0, 0, // Display value
              6, 0, 0, 0,    // Data value
              0xaa, 5, 0, 0, // Display value
              7, 0, 0, 0,    // Data value
              0xdc, 5, 0, 0, // Display value
              8, 0, 0, 0,    // Data value
              0x0e, 6, 0, 0, // Display value
              9, 0, 0, 0,    // Data value
              0x40, 6, 0, 0, // Display value
              10, 0, 0, 0,   // Data value
              0x72, 6, 0, 0, // Display value
            }
          })
        }

        If(LEqual(Arg0, 19))
        {
          ADBG("DDR MULT")
          If(LEqual(DDRF,1))
          {
            ADBG("DDR 1")
            Return (Package(0x2)
            {
              0x0, //Error code
              Buffer()
              {
                0, 0, 0, 0,      // Data value for auto
                0, 0, 0, 0,      // Display value
                4, 0, 0, 0,      // Data value
                0x2b, 4, 0, 0,   // Display value
                5, 0, 0, 0,      // Data value
                53, 5, 0, 0,     // Display value
                6, 0, 0, 0,      // Data value
                0x40, 6, 0, 0,   // Display value
                7, 0, 0, 0,      // Data value
                0x4b, 7, 0, 0,   // Display value
                8, 0, 0, 0,      // Data value
                0x55, 8, 0, 0,   // Display value
                9, 0, 0, 0,      // Data value
                0x60, 9, 0, 0,   // Display value
                10, 0, 0, 0,     // Data value
                0x6b, 0xa, 0, 0, // Display value
                11, 0, 0, 0,     // Data value
                0x75, 0xb, 0, 0, // Display value
                12, 0, 0, 0,     // Data value
                0x80, 0xc, 0, 0, // Display value
              }
            })
          }
          Else
          {
            ADBG("DDR ELSE")
            Return(Package(0x2)
            {
              0x0, // Error code
              Buffer()
              {
                0, 0, 0, 0,      // Data value for auto
                0, 0, 0, 0,      // Display value
                5, 0, 0, 0,      // Data value
                0x2b, 4, 0, 0,   // Display value
                6, 0, 0, 0,      // Data value
                0xb0, 4, 0, 0,   // Display value
                7, 0, 0, 0,      // Data value
                0x78, 5, 0, 0,   // Display value
                8, 0, 0, 0,      // Data value
                0x40, 6, 0, 0,   // Display value
                9, 0, 0, 0,      // Data value
                0x08, 7, 0, 0,   // Display vlaue
                10, 0, 0, 0,     // Data value
                0xd0, 7, 0, 0,   // Display value
                11, 0, 0, 0,     // Data value
                0x98, 8, 0, 0,   // Display value
                12, 0, 0, 0,     // Data value
                0x60, 9, 0, 0,   // Display value
                13, 0, 0, 0,     // Data value
                0x28, 0xa, 0, 0, // Display value
                14, 0, 0, 0,     // Data value
                0xf0, 0xa, 0, 0, // Display value
                15, 0, 0, 0,     // Data value
                0xb8, 0xb, 0, 0, // Display value
                16, 0, 0, 0,     // Data value
                0x80, 0xc, 0, 0, // Display value
              }
            })
          }
          ADBG("DDR EXIT")
        }

        If(LEqual(Arg0,11))
        {
          Return(Package(0x2)
          {
            0x0, // Error code
            Buffer()
            {
              0, 0, 0, 0,  // Data value for auto
              0, 0, 0, 0,  // Display value
              5, 0, 0, 0,  // Data value
              5, 0, 0, 0,  // Display value
              6, 0, 0, 0,  // Data value
              6, 0, 0, 0,  // Display value
              7, 0, 0, 0,  // Data value
              7, 0, 0, 0,  // Display value
              8, 0, 0, 0,  // Data value
              8, 0, 0, 0,  // Display value
              10, 0, 0, 0, // Data value
              0xA,0, 0, 0, // Display value
              12, 0, 0, 0, // Data value
              0xC,0, 0, 0, // Display value
              14, 0, 0, 0, // Data Value
              0xE,0, 0,0,  // Display Value
              16, 0, 0, 0, // Data Value
              0x10,0,0,0,  // Display Value
              18, 0, 0, 0, // Data Value
              0x12,0,0,0,  // Display Value
              20, 0, 0, 0, // Data Value
              0x14,0,0,0,  // Display Value
              24, 0, 0, 0, // Data Value
              0x18,0,0,0,  // Display Value
            }
          })
        }

        If(LEqual(Arg0,73))
        {
          Return(Package(0x2)
          {
            0x0, // Error code
            Buffer()
            {
              0, 0, 0, 0,    // Data value for auto
              0, 0, 0, 0,    // Display value
              1, 0, 0, 0,    // Data value
              0x85, 0, 0, 0, // Display value
              2, 0, 0, 0,    // Data value
              0x64, 0, 0, 0, // Display value
            }
          })
        }

        Return(Package(0x1)
        {
        0x01 // Error code for continuous settings
        })
      }

      Method(GXDV, 0x1, Serialized, 0, PkgObj, IntObj)
      {
        If (LNotEqual(XMPB, Zero))
        {
          OperationRegion (XMPN, SystemMemory, XMPB, SIZE)
          Field (XMPN, ByteAcc, NoLock, Preserve) {
              XMP1, 0x240,              // Total Controls * 8 * 8, BitLength.
              XMP2, 0x240,              // Total Controls * 8 * 8, BitLength.
          }

          If(LEqual(Arg0, 1))
          {
            Name(XP_1, Package(0x2){}) // Return Package
            Store(0x00, Index(XP_1, 0)) // Error Code
            Store(XMP1, Index(XP_1, 1)) // Data buffer
            Return(XP_1)
          }
          If(LEqual(Arg0, 2))
          {
            Name(XP_2, Package(0x2){}) // Return Package
            Store(0x00, Index(XP_2, 0)) // Error Code
            Store(XMP2, Index(XP_2, 1)) // Data buffer
            Return(XP_2)
          }
        }
        Return(Package(0x1)
        {
          1 // Invalid profile type
        })
      }

      Method(GSCV, 0x0, NotSerialized, 0, PkgObj)
      {
      Return(Package(0x1)
      {
      0x72
      })
      }

      Method(CDRD, 0x1, Serialized, 0, PkgObj, IntObj)
      {
      Return(Package(0x1)
      {
      0x01 // Non real time device read requested
      })
      }

      Method(CDWR, 0x2, Serialized, 0, PkgObj, {IntObj, IntObj})
      {
      Return(0x01) // Write to non real time device
      }

      Name(RPMV, Package()
      {
       //UsageId     //DeviceId       //Value     //Reserved
          0x01,         0x0007,          0,          0        //Cpu Fan Speed
      })

      Name(TMP1, Package()
      {
      //UsageId     //DeviceId      //Value     //Reserved
         0x01,         0x0002,         0,          0,       //Core Temprature
         0x05,         0x0004,         0,          0,       //CPU VR Temperature
         0x06,         0x0005,         0,          0,       // TS-on-DIMM Temperature
      })
      Name(TMP2, Package()
      {
       //UsageId     //DeviceId      //Value     //Reserved
          0x01,         0x0002,         0,          0,       //Core Temprature
          0x05,         0x0004,         0,          0,       //CPU VR Temperature
      })
      Name(TMP3, Package()
      {
       //UsageId     //DeviceId      //Value     //Reserved
          0x01,         0x0002,         0,          0,       //Core Temprature
      })
      Method(TSDD)
      {
        If(LEqual(XTUS, 0))
        {
          Return (0)
        }
        If (\ECON)
        {
          If(\TSOD)
          {
            Store(\_TZ.TZ01._TMP, Index(TMP1, 2))
            Return(TMP1)
          }
          Else
          {
            Store(\_TZ.TZ01._TMP, Index(TMP2, 2))
            Return(TMP2)
          }//End of TSDD If
        }
        Else
        {
          Store(\_TZ.TZ01._TMP, Index(TMP3, 2))
          Return(TMP3)
        }//End of ECON If
      }//End of TSDD Method

      Method(FSDD)
      {
        If(LEqual(XTUS, 0))
        {
          Return (0)
        }
        If (\ECON)
        {
          Store(\_SB.PC00.LPCB.H_EC.ECRD(RefOf(\_SB.PC00.LPCB.H_EC.CFSP)), Index(RPMV, 2))
        }
        Return(RPMV)
      }

      Method (SDSP)
      {
        Return(10)      // Sampling period .
      }


    }// end of PTMD Device

  } // end \_SB scope
} // end SSDT
