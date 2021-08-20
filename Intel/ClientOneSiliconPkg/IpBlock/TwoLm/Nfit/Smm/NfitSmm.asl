/** @file
  NV DIMM Root and child device support.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

DefinitionBlock (
  "NvDimm.aml",
  "SSDT",
  2,
  "INTEL ",
  "NvdmTabl",
  0x1000
  )
{
  Scope (\_SB)
  {
    External(\ADBG, MethodObj)

    //
    // This file contains the definition of Device(NFIT) which would allow the NFIT
    // SCM Bus driver to load.
    //
    Device(NVDR){
      Name (_HID, "ACPI0012")

      Method (_STA){
        ADBG ("NVDR STA")
        Return (0x0F)
      }

      //
      // Operational region for communication between ASL and SMM handler
      // Region Offset 0xFFFF0000 and Length 0x300 will be fixed in C code.
      //
      OperationRegion (NVDM, SystemMemory, 0xFFFF0000, 0x300)
      Field (NVDM, AnyAcc, NoLock, Preserve)
      {
        FISS,   8,  //   Software SMI for Firmware Interface Command interface
        FISF,   8,  //   Function number for Firmware Interface Command
        FIS1,   32, //   dword1
        FIS2,   32, //   dword2
        FIS3,   32, //   dword3
        BUFF,   4096 //  buffer
      }

      //
      // Operational region for Smi port access
      //
      OperationRegion (SMIP, SystemIO, 0xB2, 1)
      Field (SMIP, ByteAcc, NoLock, Preserve)
      {
        IOB2, 8
      }

      Method (CLAR, 1)
      {
        OperationRegion (BUF0, SystemMemory, Arg0, 1)
        Field (BUF0, ByteAcc, NoLock, Preserve)
        {
          DATA, 8
        }
        Store (0, DATA)
      }

      Method (BITS, 1)
      {
        Return (Multiply (Arg0, 8))
      }

      // Root device _DSMs
      Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj})
      {
        ADBG ("NVDR DSM")
        ADBG(ToHexString(Arg2))
        If(LNotEqual(Arg0, ToUUID ("2f10e7a4-9e91-11e4-89d3-123b93f75cba")))
        {
          ADBG ("Guid mismatch")
          Return (Package () {0x03})
        }
        Name (INDX, 0)
        Switch(ToInteger(Arg2)) {
          Case(0)
          {
            ADBG ("Query Command")
            Return(Buffer(){0x1F})  //0 to 4 functuons are supported
          }
          Case(1)
          {
            ADBG ("Query ARS Capabilities")
            Store(21, FISF)
            ToBuffer (DeRefOf (Index (Arg3, 0)), Local6)
            ADBG ("Arg3 Input:")
            ADBG (ToHexString(Local6))
            // read input payload of size 16 bytes from Arg3
            ToBuffer (DeRefOf (Index (Arg3, 0)), BUFF)
            Mid (BUFF, 0,  16, Local0) //Local0 has read buffer
            Store (0, INDX)
            ADBG("Input ")
            While(LLess(INDX, 16)) {
              Store(DeRefOf(Index(Local0,INDX)), Local7)
              Increment(INDX)
              ADBG(ToHexString(Local7))
            }
            //
            // Triggle the SMI interrupt
            //
            Store (FISS, IOB2)
            //CreateField (FIS1, 0, BITS (2), RSTS)
            if (LEqual ((FIS1 & 0xFF), 0)) {
              ADBG ("Query ARS Capabilities Success")
              //copy data from Buff starting at 0 and of length 12 bytes to Local0
              Mid (BUFF, 0, 12, Local0) //Local0 has read buffer
              //create Local1 of size (4 + 12)
              Store (Buffer (Add (4, 12)) {}, Local1)
              //In Local1, define DW field RS21 from offset 0
              CreateDWordField (Local1, 0, RS21)
              Store(FIS1, RS21)
              //create field RD21 in Local1 from offset 32bits and size 12
              CreateField (Local1, BITS (4), BITS (12), RD21)
              Store(Local0, RD21)

              Store (0, INDX)
              ADBG("Buffer ")
              While(LLess(INDX, 16)) {
                Store(DeRefOf(Index(Local1,INDX)), Local7)
                Increment(INDX)
                ADBG(ToHexString(Local7))
              }
              Store(Local1, Debug)
              Return(Local1)
            }
            Else
            {
              ADBG ("Query ARS Cap Failure")
              //Return (Buffer (16) {FIS1, 0})
              //Return (Buffer () {4, 0, 0, 0})
              Store (Buffer (Add (4, 12)) {}, Local4)
              //In Local2, define DW field RS21 from offset 0
              CreateDWordField (Local4, 0, RSTS)
              Store(FIS1, RSTS)
              //create field RD21 in Local1 from offset 32bits and size 12
              CreateField (Local4, BITS (4), BITS (12), RDTQ)
              Store(0, RDTQ)
              Return(Local4)
            }
          }
          Case(2) {
            ADBG ("Start ARS")
            Store(22, FISF)
            // read input payload of size 24 bytes from Arg3
            ToBuffer(DeRefOf(Index(Arg3, 0)), BUFF)
            Mid (BUFF, 0,  24, Local0) //Local0 has read buffer
            ToBuffer (DeRefOf (Index (Arg3, 0)), Local6)
            ADBG ("Arg3 Input:")
            ADBG (ToHexString(Local6))
            Store (0, INDX)
            ADBG("Input ")
            While(LLess(INDX, 24)) {
              Store(DeRefOf(Index(Local0,INDX)), Local7)
              Increment(INDX)
              ADBG(ToHexString(Local7))
            }
            //
            // Triggle the SMI interrupt
            //
            Store (FISS, IOB2)
            if (LEqual (FIS1, 0)) {
              ADBG ("Start ARS Success")
              Store(FIS2, Local0) //store estimated time in Local0
              ADBG ("Estimated time is")
              ADBG(ToHexString(Local0))
              //create Local1 of size (4 + 4)
              Store (Buffer (Add (4, 4)) {}, Local1)
              //In Local1, define DW field RS22 from offset 0
              CreateDWordField (Local1, 0, RS22)
              Store(0, RS22)
              //create field RD22 in Local1 from offset 32bits and size 4 bytes
              CreateField (Local1, BITS (4), BITS (4), RD22)
              Store(Local0, RD22)

              Store (0, INDX)
              Store(8, Local6)
              ADBG("Buffer ")
              While(LLess(INDX, Local6)) {
                Store(DeRefOf(Index(Local1,INDX)), Local7)
                Increment(INDX)
                ADBG(ToHexString(Local7))
              }
              Return(Local1)
            }
            Else
            {
              ADBG ("Start ARS Failure")
              Return (FIS1)
            }
          }
          Case(3) {
            ADBG ("Query ARS Status")
            Store(23, FISF)
            Store (FISS, IOB2)
            if (LEqual ((FIS1 & 0xFF), 0)) {
              ADBG ("Query ARS Status Success")
              ADBG ("Return status")
              ADBG(ToHexString(FIS1))
              Store(FIS2, Local3) //store return length in Local3
              ADBG(ToHexString(Local3))
              //copy data from Buff starting at 0 and of length Local3 to Local0
              Mid (BUFF, 0,  Local3, Local0) //Local0 has read buffer
              //create Local1 of size (Local3 + 4) = (124+4)
              Store (Buffer (Add (Local3, 4)) {}, Local1)
              //In Local1, define DW field RSTS from offset 0
              CreateDWordField (Local1, 0, RS23)
              Store(FIS1, RS23)
              //create field RDTA in Local1 from offset 32bits and size Local3
              CreateField (Local1, BITS (4), BITS (Local3), RDTA)
              Store(Local0, RDTA)

              Store(0, INDX)
              Store(Add (FIS2, 4), Local6)
              ADBG(ToHexString(Local6))
              ADBG("Buffer ")
              While(LLess(INDX, Local6)) {
                Store(DeRefOf(Index(Local1,INDX)), Local7)
                Increment(INDX)
                ADBG(ToHexString(Local7))
              }
              Store(Local1, Debug)
              Return(Local1)
            }
            Else
            {
              ADBG ("Query ARS Status Failure")
              Store(FIS2, Local3) //store return length in Local3
              //create Local4 of size (Local3 + 4) = (124+4)
              Store (Buffer (Add (Local3, 4)) {}, Local4)
              //In Local4, define DW field RSTS from offset 0
              CreateDWordField (Local4, 0, FS23)
              Store(FIS1, FS23)
              //create field RDTA in Local1 from offset 32bits and size Local3
              CreateField (Local4, BITS (4), BITS (Local3), FD23)
              Store(0, FD23)
              Return(Local4)
            }
          }
          Case(4) {
            ADBG ("Clear Uncorrectable Error")
            Store(24, FISF)
            ToBuffer(DeRefOf(Index(Arg3, 0)), BUFF)
            Mid (BUFF, 0,  16, Local0) //Local0 has read buffer
            ADBG("Input")
            ADBG(ToHexString(Local0))
            //
            // Triggle the SMI interrupt
            //
            Store (FISS, IOB2)
            if (LEqual (FIS1, 0)) {
              ADBG ("Input is valid")
              Mid (BUFF, 0, 16, Local0) //Local0 has input
              CreateQWordField (Local0, 0, ADDR)
              CreateQWordField (Local0, 8, LENG)
              ADBG ("Start Addr")
              ADBG(ToHexString(ADDR))
              ADBG ("Length")
              ADBG(ToHexString(LENG))
              // Clear addr rang to 0
              Store(0, INDX)
              While(LLess(INDX, LENG)) {
                CLAR(ADDR)
                Increment(ADDR)
                Increment(INDX)
              }
              ADBG ("Cleared Errors upto addr")
              ADBG(ToHexString(ADDR))
              Store (Buffer (16) {}, Local4)
              CreateDWordField (Local4, 0, RS24)
              Store(0, RS24)
              CreateDWordField (Local4, 4, RSVD)
              Store(0, RSVD)
              CreateQWordField (Local4, 8, RD24)
              Store(LENG, RD24)
              Return(Local4)
            }
            Else
            {
              ADBG ("Input Failure")
              Return (0x02) //Invalid input
            }
          } //end of case
        }// end of switch
      } //end of DSM

      Device(NVD1) {
        // _ADR
        Name(_ADR, 0x1)

        Method (_STA) {
          ADBG ("NVD1 STA")
          Return (0x0F)
        }

        Method (_LSI, 0)
        {
          ADBG ("NVD1 _LSI")
          Store(31, FISF)  // Store LSI function number which has corresponding function in NfitSmm.c
          //
          // Triggle the SMI interrupt
          //
          Store (FISS, IOB2)

          if (LEqual (FIS1, 0)) {
            ADBG ("_LSI Success")
            ADBG(Concatenate("Status ",ToHexString(FIS1)))
            ADBG(Concatenate("Size ",ToHexString(FIS2)))
            ADBG(Concatenate("Max Transfer Length ",ToHexString(FIS3)))

            Store (Package () {0, 0, 0}, Local2)
            Store (ToInteger (FIS1), Index (Local2, 0))
            Store (ToInteger (FIS2), Index (Local2, 1))
            Store (ToInteger (FIS3), Index (Local2, 2))
            Return (Local2)
          }
          Else
          {
            ADBG ("_LSI Failure")
            Return (Package () {0x01, 0x00, 0x00})
          }
        }

        Method (_LSR, 2)
        {
          ADBG ("NVD1 _LSR")
          Store(32, FISF) // Store LSR function number which has corresponding function in NfitSmm.c
          Store(Arg0, FIS1) // Offset in bytes
          Store(Arg1, FIS2) // Length in bytes
          //
          // Triggle the SMI interrupt
          //
          Store (FISS, IOB2)
          // After coming back from SMI, FIS1 will have status. 0 is success.
          // BUFF will be filled with data read from device of size in FIS2.
          if (LEqual (FIS1, 0)) {
            ADBG ("_LSR Success")
            Store (Buffer (Add (Arg1, 4)) {}, Local1)
            CreateDWordField (Local1, 0, RSTS)
            Store(0, RSTS)
            CreateField (Local1, BITS (4), BITS (Arg1), RDTA)
            Mid (BUFF, 0,  Arg1, Local0) //Local0 has read buffer
            Store(Local0, RDTA)
            ADBG("Offset ")
            ADBG(ToHexString(Arg0))
            ADBG("Length ")
            ADBG(ToHexString(Arg1))
            Name (INDX, 4)
            Store(Arg1, Local6)
            ADBG("Buffer ")
            While(LLess(INDX, Local6)) {
              Store(DeRefOf(Index(Local1,INDX)), Local7)
              Increment(INDX)
              ADBG(ToHexString(Local7))
            }
            return (Local1)
          }
          Else
          {
            ADBG ("_LSR Failure")
            Return (Package () {0x01, Buffer () {0}})
          }
        }

        Method (_LSW, 3, Serialized)
        {
          ADBG ("NVD1 _LSW")
          Mid (Arg2, 0,  Arg1, BUFF)
          Store(33, FISF) // Store LSW function number which has corresponding function in NfitSmm.c
          Store(Arg0, FIS1)  // offset
          Store(Arg1, FIS2)  // Length in bytes
          ADBG("Offset ")
          ADBG(ToHexString(Arg0))
          ADBG("Length ")
          ADBG(ToHexString(Arg1))
          Name (INDX, 0)
          Store(Arg1, Local6)
          ADBG("Buffer ")
          Store (Buffer (Arg1) {}, Local5)
          Mid (BUFF, 0,  Arg1, Local5) //Local0 has read buffer
          While(LLess(INDX, Local6)) {
            Store(DeRefOf(Index(Local5,INDX)), Local7)
            Increment(INDX)
            ADBG(ToHexString(Local7))
          }
          //
          // Triggle the SMI interrupt
          //
          Store (FISS, IOB2)
          if (LEqual (FIS1, 0)) {
            ADBG ("_LSW Success")
            Return (0x00)
          }
          Else
          {
            ADBG ("_LSW Failure")
            Return (0x01)
          }
        }
    // _DSM
    Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj})
    {
      ADBG ("NVD1 DSM")
          ADBG(ToHexString(Arg2))
          If(LNotEqual(Arg0, ToUUID ("4309AC30-0D11-11E4-9191-0800200C9A66")))
          {
            ADBG ("Guid mismatch")
            Return (Package () {0x03})
          }
          Name (INDX, 0)
          Switch(ToInteger(Arg2)) {
            Case(0) {
              ADBG ("Get Supported Functions")
              Return(Buffer(){0x87, 0x1F,0x2})
            }
            Case(1) { // Get SMART and Health Info (Function Index 1)
              ADBG ("NVD1 Get Smart and Health info")
              Store(1, FISF)
              Store (FISS, IOB2)
              if (LEqual (FIS1, 0)) {
                ADBG ("NVD1 Get Smart and Health info Success")
                Store(FIS2, Local3) //store return length in Local3
                //copy data from Buff starting at 0 and of length Local3 to Local0
                Mid (BUFF, 0,  Local3, Local0) //Local0 has read buffer
                //create Local1 of size (Local3 + 4) = (128+4)
                Store (Buffer (Add (Local3, 4)) {}, Local1)
                //In Local1, define DW field RSTS from offset 0
                CreateDWordField (Local1, 0, RSTS)
                Store(0, RSTS)
                //create field RDTA in Local1 from offset 32bits and size Local3
                CreateField (Local1, BITS (4), BITS (Local3), RDTA)
                Store(Local0, RDTA)
                Store (0, INDX)
                Store(FIS2, Local6)
                ADBG("Buffer ")
                While(LLess(INDX, Local6)) {
                  Store(DeRefOf(Index(Local1,INDX)), Local7)
                  Increment(INDX)
                  ADBG(ToHexString(Local7))
                }
                Return(Local1)
              }
              Else
              {
                ADBG ("Failure")
                Return (Buffer () {4, 0, 0, 0})
              }
            }
            Case(2) { // Get SMART Threshold (Function Index 2)
              ADBG ("NVD1 Get Smart Threshold")
              Store(2, FISF)
              Store (FISS, IOB2)
              if (LEqual (FIS1, 0)) {
                ADBG ("Get SMART Threshold Success")
                Store(FIS2, Local3) //store return length in Local3
                //copy data from Buff starting at 0 and of length Local3 to Local0
                Mid (BUFF, 0,  Local3, Local0) //Local0 has read buffer
                //create Local1 of size (Local3 + 4) = (8+4)
                Store (Buffer (Add (Local3, 4)) {}, Local1)
                //In Local1, define DW field RST2 from offset 0
                CreateDWordField (Local1, 0, RST2)
                Store(0, RST2)
                //create field RDTA in Local1 from offset 32bits and size Local3
                CreateField (Local1, BITS (4), BITS (Local3), RDT2)
                Store(Local0, RDT2)

                Store (0, INDX)
                Store(12, Local6)
                ADBG("Buffer ")
                While(LLess(INDX, Local6)) {
                  Store(DeRefOf(Index(Local1,INDX)), Local7)
                  Increment(INDX)
                  ADBG(ToHexString(Local7))
                }
                Return(Local1)
              }
              Else
              {
                ADBG ("Get SMART Threshold Failure")
                Return (Buffer () {4, 0, 0, 0})
              }
            }
            Case(7) {
              // Get Command Effect Log Info (Function Index 7)
              ADBG ("NVD1 Get Command Effect Log Info")
              Store(7, FISF)
              Store (FISS, IOB2)
              if (LEqual (FIS1, 0)) {
                ADBG ("Get Command Effect Log Info Success")
                //copy data from Buff starting at 0 and of length 4 bytes to Local0
                Mid (BUFF, 0,  4, Local0) //Local0 has read buffer
                //create Local1 of size (4 + 4)
                Store (Buffer (Add (4, 4)) {}, Local1)
                //In Local1, define DW field RST7 from offset 0
                CreateDWordField (Local1, 0, RST7)
                Store (0, RST7)
                //create field RDT7 in Local1 from offset 32bits and size 4
                CreateField (Local1, BITS (4), BITS (4), RDT7)
                Store (Local0, RDT7)

                Store (0, INDX)
                Store (8, Local6)
                ADBG("Buffer ")
                While(LLess(INDX, Local6)) {
                  Store(DeRefOf(Index(Local1,INDX)), Local7)
                  Increment(INDX)
                  ADBG(ToHexString(Local7))
                }
                Return(Local1)
              }
              Else
              {
                ADBG ("Failure")
                Return (Buffer () {4, 0, 0, 0})
              }
            }
            Case(8) {
              // Get Command Effect Log (Function Index 8)
              ADBG ("NVD1 Get Command Effect Log")
              Store(8, FISF)
              Store (FISS, IOB2)
              if (LEqual (FIS1, 0)) {
                ADBG ("Get Command Effect Log Success")
                Store(FIS2, Local3) //store return length in Local3
                Store(FIS3, Local4) //store opcode count in Local4
                ADBG ("FIS2: length")
                ADBG (ToHexString(Local3))
                ADBG ("FIS3: count")
                ADBG (ToHexString(Local4))
                //copy data from Buff starting at 0 and of length Local3 to Local0
                Mid (BUFF, 0,  Local3, Local0) //Local0 has read buffer
                //create Local1 of size (Local3 + 4 + 4 )
                Store (Buffer (Add (Local3, 8)) {}, Local1)
                //In Local1, define DW field RST8 from offset 0
                CreateDWordField (Local1, 0, RST8)
                Store(0, RST8)
                //now copy and return opcode cnt
                CreateDWordField (Local1, 4, RCNT)
                Store(Local4, RCNT)
                //create field RDT8 in Local1 from offset 32bits and size Local3
                CreateField (Local1, BITS (8), BITS (Local3), RDT8)
                Store(Local0, RDT8)

                Store (0, INDX)
                Store(Add (Local3, 8), Local6)
                ADBG("Buffer ")
                While(LLess(INDX, Local6)) {
                  Store(DeRefOf(Index(Local1,INDX)), Local7)
                  Increment(INDX)
                  ADBG(ToHexString(Local7))
                }
                Return(Local1)
              }
              Else
              {
                ADBG ("Failure")
                Return (Buffer () {4, 0, 0, 0})
              }
            }
            Case(9) {
              // Pass-Through Command (Function Index 9)
              ADBG ("NVD1 Pass-Through Command")
              Store(9, FISF)
              ADBG("Line1")
              ToBuffer (DeRefOf (Index (Arg3, 0)), Local0)// Local0 has input
              ADBG ("ARG3 Input:")
              ADBG(ToHexString(Local0))

              ADBG("Line2")
              Mid (Local0, 0, 4, FIS1) // Opcode
              ADBG("Line3")
              Mid (Local0, 4, 4, FIS2) // Input data length
              ADBG("Line4")
              Mid (Local0, 8, FIS2, BUFF) //BUFF has input payload
              ADBG("Line5")
              ADBG("Opcode ")
              ADBG(ToHexString(FIS1))
              ADBG("Input length ")
              ADBG(ToHexString(FIS2))

              Store (0, INDX)
              Store (FIS2, Local6)
              ADBG ("Input Buffer ")
              Store (Buffer (FIS2) {}, Local5)
              Mid (BUFF, 0,  FIS2, Local5) //Local5 has read buffer
              While(LLess(INDX, Local6)) {
                Store(DeRefOf(Index(Local5,INDX)), Local7)
                Increment(INDX)
                ADBG(ToHexString(Local7))
              }
              //
              // Triggle the SMI interrupt
              //
              Store (FISS, IOB2)
              if (LEqual (FIS1, 0)) {
                ADBG ("Pass-Through Success")
                //copy data from Buff starting at 0 and of length 4 bytes to Local0
                Mid (BUFF, 0, 512, Local0) //Local0 has read buffer
                //create Local1 of size (512 + 4 + 4)
                Store (Buffer (Add (512, 8)) {}, Local1)
                //In Local1, define DW field RST9 from offset 0
                CreateDWordField (Local1, 0, RST9)
                Store(0, RST9)
                //In Local1, define DW field RDL9 from offset 4
                CreateDWordField (Local1, 4, RDL9)
                Store(512, RDL9)
                //create field RDT9 in Local1 from offset 8bytes and size 512
                CreateField (Local1, BITS (8), BITS (512), RDT9)
                Store(Local0, RDT9)

                Store (0, INDX)
                ADBG("Buffer ")
                While(LLess(INDX, 520)) {
                  Store(DeRefOf(Index(Local1,INDX)), Local7)
                  Increment(INDX)
                  ADBG(ToHexString(Local7))
                }
                Return(Local1)
              }
              Else
              {
                ADBG ("Pass thru Failure")
                Return (Buffer () {4, 0, 0, 0})
              }
            }
            Case(10) {
              // Enable Latch System Shutdown Status
              ADBG ("NVD1 Enable Latch System Shutdown Status")
              Store(10, FISF)
              ToBuffer(DeRefOf(Index(Arg3, 0)), Local0)// Local0 has input
              ADBG ("ARG3 Input:")
              ADBG(ToHexString(Local0))
              Mid (Local0, 0, 1, BUFF) //BUFF has input payload
              //
              // Triggle the SMI interrupt
              //
              Store (FISS, IOB2)

              if (LEqual (FIS1, 0)) {
                ADBG ("Enable Latch System Shutdown Status Success")
                Return (Buffer () {0, 0, 0, 0})
              }
              Else
              {
                ADBG ("Failure")
                Return (Buffer () {4, 0, 0, 0})
              }
            }
            Case(11) {
              // Get Supported Modes (Function Index 11)
              ADBG ("NVD1 Get Supported Modes")
              Store(11, FISF)
              Store (FISS, IOB2)
              if (LEqual (FIS1, 0)) {
                ADBG ("Get Supported Modes Success")
                //copy data from Buff starting at 0 and of length 2 bytes to Local0
                Mid (BUFF, 0,  2, Local0) //Local0 has read buffer
                //create Local1 of size (4 + 2)
                Store (Buffer (Add (4, 2)) {}, Local1)
                //In Local1, define DW field RS11 from offset 0
                CreateDWordField (Local1, 0, RS11)
                Store(0, RS11)
                //create field RD11 in Local1 from offset 32bits and size 2
                CreateField (Local1, BITS (4), BITS (2), RD11)
                Store(Local0, RD11)

                Store (0, INDX)
                ADBG("Buffer ")
                While(LLess(INDX, 2)) {
                  Store(DeRefOf(Index(Local1,INDX)), Local7)
                  Increment(INDX)
                  ADBG(ToHexString(Local7))
                }
                Return(Local1)
              }
              Else
              {
                ADBG ("Failure")
                Return (Buffer () {4, 0, 0, 0})
              }
            }
            Case(12) {
              // Get FW Info (Function Index 12)
              ADBG ("NVD1 Get FW Info")
              Store(12, FISF)
              Store (FISS, IOB2)
              if (LEqual (FIS1, 0)) {
                ADBG ("Get FW Info Success")
                Store(FIS2, Local3) //store return length in Local3
                ADBG(ToHexString(Local3))
                //copy data from Buff starting at 0 and of length Local3 to Local0
                Mid (BUFF, 0, Local3, Local0) //Local0 has read buffer
                //create Local1 of size (Local3 + 4)
                Store (Buffer (Add (Local3, 4)) {}, Local1)
                //In Local1, define DW field RS12 from offset 0
                CreateDWordField (Local1, 0, RS12)
                Store(0, RS12)
                //create field RD12 in Local1 from offset 32bits and size Local3
                CreateField (Local1, BITS (4), BITS (Local3), RD12)
                Store(Local0, RD12)

                Store("Local6", Debug)
                Store (0, INDX)
                ADBG("Buffer ")
                While(LLess(INDX, 44)) {
                  Store(DeRefOf(Index(Local1,INDX)), Local7)
                  Increment(INDX)
                  ADBG(ToHexString(Local7))
                  }
                Store(Local1, Debug)
                Return(Local1)
              }
              Else
              {
                ADBG ("Failure")
                Return (Buffer (44) {4, 0})
              }
            }
            Case(17) {
              // Set SMART Threshold (Function Index 17)
              ADBG ("NVD1 Set SMART Threshold")
              Store(17, FISF)
              // read input payload of size 7 bytes from Arg3
              ToBuffer(DeRefOf(Index(Arg3, 0)), BUFF)
              Mid (BUFF, 0,  7, Local0) //Local0 has read buffer
              Store (0, INDX)
              ADBG("Input ")
              While(LLess(INDX, 7)) {
                Store(DeRefOf(Index(Local0,INDX)), Local7)
                Increment(INDX)
                ADBG(ToHexString(Local7))
              }
              ToBuffer (DeRefOf (Index (Arg3, 0)), Local6)
              ADBG ("CR17 ARG3 Input:")
              ADBG(ToHexString(Local6))
              //
              // Triggle the SMI interrupt
              //
              Store (FISS, IOB2)
              if (LEqual (FIS1, 0)) {
                ADBG ("Set SMART Threshold Success")
                Return (0x00)
              }
              Else
              {
                //03 Invalid Input Parameters Returned If any threshold value requested to be enabled is invalid.
               ADBG ("Failure")
               Return (0x03)
              }
            } //end of case17
            Default {
              ADBG ("NVD1 Default")
              Return (Buffer () {0, 0, 0, 0})
            }
          } //end of switch
        } //end of NVD1 DSM
      } // end of NVD1
    } // end of namespace
  }
}