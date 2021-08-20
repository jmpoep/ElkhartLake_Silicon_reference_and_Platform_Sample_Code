/** @file
  SMM State Save register.


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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include "SmmCpuFeatures.h"

//
// EFER register LMA bit
//
#define LMA BIT10

//
// SmmRegFeatureControl bit for SMM Save State in MSRs
//
#define  SMM_CPU_SAVE_EN_BIT                   BIT1

///
/// Macro used to simplfy the lookup table entries of type CPU_SMM_SAVE_STATE_LOOKUP_ENTRY
///
#define SMM_CPU_OFFSET(Field) OFFSET_OF (SOCKET_LGA_775_SMM_CPU_STATE, Field)

///
/// Macro used to simplfy the lookup table entries of type CPU_SMM_SAVE_STATE_REGISTER_RANGE
///
#define SMM_REGISTER_RANGE(Start, End) { Start, End, End - Start + 1 }

///
/// Structure used to describe a range of registers
///
typedef struct {
  EFI_SMM_SAVE_STATE_REGISTER  Start;
  EFI_SMM_SAVE_STATE_REGISTER  End;
  UINTN                        Length;
} CPU_SMM_SAVE_STATE_REGISTER_RANGE;

///
/// Structure used to build a lookup table to retrieve the widths and offsets
/// associated with each supported EFI_SMM_SAVE_STATE_REGISTER value
///

#define SMM_SAVE_STATE_REGISTER_SMMREVID_INDEX        1
#define SMM_SAVE_STATE_REGISTER_IOMISC_INDEX          2
#define SMM_SAVE_STATE_REGISTER_IOMEMADDR_INDEX       3
#define SMM_SAVE_STATE_REGISTER_MAX_INDEX             4

typedef struct {
  UINT8   Width32;
  UINT8   Width64;
  UINT16  Offset32;
  UINT16  Offset64Lo;
  UINT16  Offset64Hi;
  UINT32  MsrIndex;
  UINT8   OffsetInMsr;
  BOOLEAN Writeable;
} CPU_SMM_SAVE_STATE_LOOKUP_ENTRY;

///
/// Structure used to build a lookup table for the IOMisc width information
///
typedef struct {
  UINT8                        Width;
  EFI_SMM_SAVE_STATE_IO_WIDTH  IoWidth;
} CPU_SMM_SAVE_STATE_IO_WIDTH;

typedef struct {
  UINT32                      MsrIndex;
  UINT64                      MsrValue;
} MSR_INFO;

///
/// Table used by SmmFeatureGetRegisterIndex() to convert an EFI_SMM_SAVE_STATE_REGISTER
/// value to an index into a table of type CPU_SMM_SAVE_STATE_LOOKUP_ENTRY
///
CONST CPU_SMM_SAVE_STATE_REGISTER_RANGE mSmmFeatureCpuRegisterRanges[] = {
  SMM_REGISTER_RANGE (EFI_SMM_SAVE_STATE_REGISTER_GDTBASE, EFI_SMM_SAVE_STATE_REGISTER_LDTINFO),
  SMM_REGISTER_RANGE (EFI_SMM_SAVE_STATE_REGISTER_ES,      EFI_SMM_SAVE_STATE_REGISTER_RIP),
  SMM_REGISTER_RANGE (EFI_SMM_SAVE_STATE_REGISTER_RFLAGS,  EFI_SMM_SAVE_STATE_REGISTER_CR4),
  { (EFI_SMM_SAVE_STATE_REGISTER)0, (EFI_SMM_SAVE_STATE_REGISTER)0, 0 }
};

///
/// Lookup table used to retrieve the widths and offsets associated with each
/// supported EFI_SMM_SAVE_STATE_REGISTER value
///
CONST CPU_SMM_SAVE_STATE_LOOKUP_ENTRY mSmmFeatureCpuWidthOffset[] = {
  {0, 0, 0, 0, 0, 0, 0, FALSE},  //  Reserved

  //
  // Internally defined CPU Save State Registers. Not defined in PI SMM CPU Protocol.
  //
  {4, 4, SMM_CPU_OFFSET (x86.SMMRevId) , SMM_CPU_OFFSET (x64.SMMRevId) , 0                                 , MSR_SMM_REVID   , 0, FALSE}, // SMM_SAVE_STATE_REGISTER_SMMREVID_INDEX        = 1
  {4, 4, SMM_CPU_OFFSET (x86.IOMisc)   , SMM_CPU_OFFSET (x64.IOMisc)   , 0                                 , MSR_IO_MISC_INFO, 0, FALSE}, // SMM_SAVE_STATE_REGISTER_IOMISC_INDEX          = 2
  {4, 8, SMM_CPU_OFFSET (x86.IOMemAddr), SMM_CPU_OFFSET (x64.IOMemAddr), SMM_CPU_OFFSET (x64.IOMemAddr) + 4, MSR_IO_MEM_ADDR , 0, FALSE}, // SMM_SAVE_STATE_REGISTER_IOMEMADDR_INDEX       = 3

  //
  // CPU Save State registers defined in PI SMM CPU Protocol.
  //
  {0, 8, 0                           , SMM_CPU_OFFSET (x64.GdtBaseLoDword) , SMM_CPU_OFFSET (x64.GdtBaseHiDword), MSR_GDTR_BASE, 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_GDTBASE  = 4
  {0, 8, 0                           , SMM_CPU_OFFSET (x64.IdtBaseLoDword) , SMM_CPU_OFFSET (x64.IdtBaseHiDword), MSR_IDTR_BASE, 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_IDTBASE  = 5
  {0, 8, 0                           , SMM_CPU_OFFSET (x64.LdtBaseLoDword) , SMM_CPU_OFFSET (x64.LdtBaseHiDword), MSR_LDTR_BASE, 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_LDTBASE  = 6
  {0, 4, 0                           , SMM_CPU_OFFSET (x64.GdtLimit)       , 0                                  , 0,             0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_GDTLIMIT = 7
  {0, 4, 0                           , SMM_CPU_OFFSET (x64.IdtLimit)       , 0                                  , 0,             0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_IDTLIMIT = 8
  {0, 4, 0                           , SMM_CPU_OFFSET (x64.LdtLimit)       , 0                                  , 0,             0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_LDTLIMIT = 9
  {0, 4, 0                           , SMM_CPU_OFFSET (x64.LdtInfo)        , 0                                  , 0,             0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_LDTINFO  = 10

  {4, 4, SMM_CPU_OFFSET (x86._ES)    , SMM_CPU_OFFSET (x64._ES)    , 0                               , MSR_CS_ES  , 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_ES       = 20
  {4, 4, SMM_CPU_OFFSET (x86._CS)    , SMM_CPU_OFFSET (x64._CS)    , 0                               , MSR_CS_ES  , 4, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_CS       = 21
  {4, 4, SMM_CPU_OFFSET (x86._SS)    , SMM_CPU_OFFSET (x64._SS)    , 0                               , MSR_DS_SS  , 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_SS       = 22
  {4, 4, SMM_CPU_OFFSET (x86._DS)    , SMM_CPU_OFFSET (x64._DS)    , 0                               , MSR_DS_SS  , 4, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_DS       = 23
  {4, 4, SMM_CPU_OFFSET (x86._FS)    , SMM_CPU_OFFSET (x64._FS)    , 0                               , MSR_GS_FS  , 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_FS       = 24
  {4, 4, SMM_CPU_OFFSET (x86._GS)    , SMM_CPU_OFFSET (x64._GS)    , 0                               , MSR_GS_FS  , 4, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_GS       = 25
  {0, 4, 0                           , SMM_CPU_OFFSET (x64._LDTR)  , 0                               , MSR_TR_LDTR, 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_LDTR_SEL = 26
  {4, 4, SMM_CPU_OFFSET (x86._TR)    , SMM_CPU_OFFSET (x64._TR)    , 0                               , MSR_TR_LDTR, 4, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_TR_SEL   = 27
  {4, 8, SMM_CPU_OFFSET (x86._DR7)   , SMM_CPU_OFFSET (x64._DR7)   , SMM_CPU_OFFSET (x64._DR7)    + 4, MSR_DR7    , 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_DR7      = 28
  {4, 8, SMM_CPU_OFFSET (x86._DR6)   , SMM_CPU_OFFSET (x64._DR6)   , SMM_CPU_OFFSET (x64._DR6)    + 4, MSR_DR6    , 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_DR6      = 29
  {0, 8, 0                           , SMM_CPU_OFFSET (x64._R8)    , SMM_CPU_OFFSET (x64._R8)     + 4, MSR_R8     , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_R8       = 30
  {0, 8, 0                           , SMM_CPU_OFFSET (x64._R9)    , SMM_CPU_OFFSET (x64._R9)     + 4, MSR_R9     , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_R9       = 31
  {0, 8, 0                           , SMM_CPU_OFFSET (x64._R10)   , SMM_CPU_OFFSET (x64._R10)    + 4, MSR_R10    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_R10      = 32
  {0, 8, 0                           , SMM_CPU_OFFSET (x64._R11)   , SMM_CPU_OFFSET (x64._R11)    + 4, MSR_R11    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_R11      = 33
  {0, 8, 0                           , SMM_CPU_OFFSET (x64._R12)   , SMM_CPU_OFFSET (x64._R12)    + 4, MSR_R12    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_R12      = 34
  {0, 8, 0                           , SMM_CPU_OFFSET (x64._R13)   , SMM_CPU_OFFSET (x64._R13)    + 4, MSR_R13    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_R13      = 35
  {0, 8, 0                           , SMM_CPU_OFFSET (x64._R14)   , SMM_CPU_OFFSET (x64._R14)    + 4, MSR_R14    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_R14      = 36
  {0, 8, 0                           , SMM_CPU_OFFSET (x64._R15)   , SMM_CPU_OFFSET (x64._R15)    + 4, MSR_R15    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_R15      = 37
  {4, 8, SMM_CPU_OFFSET (x86._EAX)   , SMM_CPU_OFFSET (x64._RAX)   , SMM_CPU_OFFSET (x64._RAX)    + 4, MSR_RAX    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_RAX      = 38
  {4, 8, SMM_CPU_OFFSET (x86._EBX)   , SMM_CPU_OFFSET (x64._RBX)   , SMM_CPU_OFFSET (x64._RBX)    + 4, MSR_RBX    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_RBX      = 39
  {4, 8, SMM_CPU_OFFSET (x86._ECX)   , SMM_CPU_OFFSET (x64._RCX)   , SMM_CPU_OFFSET (x64._RCX)    + 4, MSR_RCX    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_RCX      = 40
  {4, 8, SMM_CPU_OFFSET (x86._EDX)   , SMM_CPU_OFFSET (x64._RDX)   , SMM_CPU_OFFSET (x64._RDX)    + 4, MSR_RDX    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_RDX      = 41
  {4, 8, SMM_CPU_OFFSET (x86._ESP)   , SMM_CPU_OFFSET (x64._RSP)   , SMM_CPU_OFFSET (x64._RSP)    + 4, MSR_RSP    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_RSP      = 42
  {4, 8, SMM_CPU_OFFSET (x86._EBP)   , SMM_CPU_OFFSET (x64._RBP)   , SMM_CPU_OFFSET (x64._RBP)    + 4, MSR_RBP    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_RBP      = 43
  {4, 8, SMM_CPU_OFFSET (x86._ESI)   , SMM_CPU_OFFSET (x64._RSI)   , SMM_CPU_OFFSET (x64._RSI)    + 4, MSR_RSI    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_RSI      = 44
  {4, 8, SMM_CPU_OFFSET (x86._EDI)   , SMM_CPU_OFFSET (x64._RDI)   , SMM_CPU_OFFSET (x64._RDI)    + 4, MSR_RDI    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_RDI      = 45
  {4, 8, SMM_CPU_OFFSET (x86._EIP)   , SMM_CPU_OFFSET (x64._RIP)   , SMM_CPU_OFFSET (x64._RIP)    + 4, MSR_RIP    , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_RIP      = 46

  {4, 8, SMM_CPU_OFFSET (x86._EFLAGS), SMM_CPU_OFFSET (x64._RFLAGS), SMM_CPU_OFFSET (x64._RFLAGS) + 4, MSR_EFLAGS , 0, TRUE },  //  EFI_SMM_SAVE_STATE_REGISTER_RFLAGS   = 51
  {4, 8, SMM_CPU_OFFSET (x86._CR0)   , SMM_CPU_OFFSET (x64._CR0)   , SMM_CPU_OFFSET (x64._CR0)    + 4, MSR_CR0    , 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_CR0      = 52
  {4, 8, SMM_CPU_OFFSET (x86._CR3)   , SMM_CPU_OFFSET (x64._CR3)   , SMM_CPU_OFFSET (x64._CR3)    + 4, MSR_CR3    , 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_CR3      = 53
  {0, 4, 0                           , SMM_CPU_OFFSET (x64._CR4)   , 0                               , MSR_CR4    , 0, FALSE},  //  EFI_SMM_SAVE_STATE_REGISTER_CR4      = 54
};

///
/// Lookup table for the IOMisc width information
///
CONST CPU_SMM_SAVE_STATE_IO_WIDTH mSmmFeatureCpuIoWidth[] = {
  { 0, EFI_SMM_SAVE_STATE_IO_WIDTH_UINT8  },  // Undefined           = 0
  { 1, EFI_SMM_SAVE_STATE_IO_WIDTH_UINT8  },  // SMM_IO_LENGTH_BYTE  = 1
  { 2, EFI_SMM_SAVE_STATE_IO_WIDTH_UINT16 },  // SMM_IO_LENGTH_WORD  = 2
  { 0, EFI_SMM_SAVE_STATE_IO_WIDTH_UINT8  },  // Undefined           = 3
  { 4, EFI_SMM_SAVE_STATE_IO_WIDTH_UINT32 },  // SMM_IO_LENGTH_DWORD = 4
  { 0, EFI_SMM_SAVE_STATE_IO_WIDTH_UINT8  },  // Undefined           = 5
  { 0, EFI_SMM_SAVE_STATE_IO_WIDTH_UINT8  },  // Undefined           = 6
  { 0, EFI_SMM_SAVE_STATE_IO_WIDTH_UINT8  }   // Undefined           = 7
};

///
/// Lookup table for the IOMisc type information
///
CONST EFI_SMM_SAVE_STATE_IO_TYPE mSmmFeatureCpuIoType[] = {
  EFI_SMM_SAVE_STATE_IO_TYPE_OUTPUT,     // SMM_IO_TYPE_OUT_DX        = 0
  EFI_SMM_SAVE_STATE_IO_TYPE_INPUT,      // SMM_IO_TYPE_IN_DX         = 1
  EFI_SMM_SAVE_STATE_IO_TYPE_STRING,     // SMM_IO_TYPE_OUTS          = 2
  EFI_SMM_SAVE_STATE_IO_TYPE_STRING,     // SMM_IO_TYPE_INS           = 3
  (EFI_SMM_SAVE_STATE_IO_TYPE)0,         // Undefined                 = 4
  (EFI_SMM_SAVE_STATE_IO_TYPE)0,         // Undefined                 = 5
  EFI_SMM_SAVE_STATE_IO_TYPE_REP_PREFIX, // SMM_IO_TYPE_REP_OUTS      = 6
  EFI_SMM_SAVE_STATE_IO_TYPE_REP_PREFIX, // SMM_IO_TYPE_REP_INS       = 7
  EFI_SMM_SAVE_STATE_IO_TYPE_OUTPUT,     // SMM_IO_TYPE_OUT_IMMEDIATE = 8
  EFI_SMM_SAVE_STATE_IO_TYPE_INPUT,      // SMM_IO_TYPE_OUT_IMMEDIATE = 9
  (EFI_SMM_SAVE_STATE_IO_TYPE)0,         // Undefined                 = 10
  (EFI_SMM_SAVE_STATE_IO_TYPE)0,         // Undefined                 = 11
  (EFI_SMM_SAVE_STATE_IO_TYPE)0,         // Undefined                 = 12
  (EFI_SMM_SAVE_STATE_IO_TYPE)0,         // Undefined                 = 13
  (EFI_SMM_SAVE_STATE_IO_TYPE)0,         // Undefined                 = 14
  (EFI_SMM_SAVE_STATE_IO_TYPE)0          // Undefined                 = 15
};

///
/// The mode of the CPU at the time an SMI occurs
///
UINT8  mSmmFeatureSaveStateRegisterLma;

///
/// Global spin lock used to serialize AP MSR access
///
SPIN_LOCK  *mMsrSpinLock = NULL;

/**
  Read information from the CPU save state.

  @param  Register  Specifies the CPU register to read form the save state.

  @retval 0   Register is not valid
  @retval >0  Index into mSmmFeatureCpuWidthOffset[] associated with Register

**/
UINTN
SmmFeatureGetRegisterIndex (
  IN EFI_SMM_SAVE_STATE_REGISTER  Register
  )
{
  UINTN  Index;
  UINTN  Offset;

  for (Index = 0, Offset = SMM_SAVE_STATE_REGISTER_MAX_INDEX; mSmmFeatureCpuRegisterRanges[Index].Length != 0; Index++) {
    if (Register >= mSmmFeatureCpuRegisterRanges[Index].Start && Register <= mSmmFeatureCpuRegisterRanges[Index].End) {
      return Register - mSmmFeatureCpuRegisterRanges[Index].Start + Offset;
    }
    Offset += mSmmFeatureCpuRegisterRanges[Index].Length;
  }
  return 0;
}

/**
  Read a CPU Save State MSR on an AP to the buffer.

  @param[in,out] Buffer  Pointer to private data buffer.
**/
VOID
EFIAPI
ReadSaveStateMsrOnAp (
  IN OUT VOID  *Buffer
  )
{
  MSR_INFO *MsrInfo;

  MsrInfo = (MSR_INFO *)Buffer;
  MsrInfo->MsrValue = AsmReadMsr64 (MsrInfo->MsrIndex);

  //
  // Release the MSR spin lock.
  //
  ReleaseSpinLock (mMsrSpinLock);
}

/**
  Read a CPU Save State MSR on the target processor.

  If the target processor is the BSP, directly read the MSR. Otherwise, call blocking SmmStartupThisAp()
  to read the MSR on the target processor.

  @param[in]     CpuIndex  Specifies the zero-based index of the CPU save state.
  @param[in,out] MsrInfo   Pointer to a MSR_INFO data structure holding the index and value of a MSR.
**/
VOID
ReadSaveStateMsr (
  IN     UINTN     CpuIndex,
  IN OUT MSR_INFO  *MsrInfo
  )
{
  EFI_STATUS Status;

  if (CpuIndex == gSmst->CurrentlyExecutingCpu) {
    MsrInfo->MsrValue = AsmReadMsr64 (MsrInfo->MsrIndex);
  } else {
    //
    // Acquire MSR spin lock.  The AP will release the
    // spin lock when it is done executing ReadSaveStateMsrOnAp().
    //
    AcquireSpinLock (mMsrSpinLock);

    //
    // Call SmmStartupThisAp() to read MSR on AP.
    //
    Status = gSmst->SmmStartupThisAp (ReadSaveStateMsrOnAp, CpuIndex, MsrInfo);
    ASSERT_EFI_ERROR (Status);

    //
    // Wait for the AP to release the MSR spin lock.
    //
    while (!AcquireSpinLockOrFail (mMsrSpinLock)) {
      CpuPause ();
    }

    //
    // Release the MSR spin lock.
    //
    ReleaseSpinLock (mMsrSpinLock);
  }
}

/**
  Read a CPU Save State register on the target processor.

  This function abstracts the differences that whether the CPU Save State register is in the
  IA32 Cpu Save State Map or x64 Cpu Save State Map or a CPU Save State MSR.

  This function supports reading a CPU Save State register in SMBase relocation handler.

  @param[in]  CpuIndex       Specifies the zero-based index of the CPU save state.
  @param[in]  RegisterIndex  Index into mSmmFeatureCpuWidthOffset[] look up table.
  @param[in]  Width          The number of bytes to read from the CPU save state.
  @param[out] Buffer         Upon return, this holds the CPU register value read from the save state.

  @retval EFI_SUCCESS           The register was read from Save State.
  @retval EFI_NOT_FOUND         The register is not defined for the Save State of Processor.
  @retval EFI_INVALID_PARAMTER  This or Buffer is NULL.
  @retval EFI_UNSUPPORTED       The register has no corresponding MSR.

**/
EFI_STATUS
SmmReadSaveStateRegisterByIndex (
  IN UINTN   CpuIndex,
  IN UINTN   RegisterIndex,
  IN UINTN   Width,
  OUT VOID   *Buffer
  )
{
  SMRAM_SAVE_STATE_MAP  *CpuSaveState;
  MSR_INFO              MsrInfo;

  if (RegisterIndex == 0) {
    return EFI_NOT_FOUND;
  }

  CpuSaveState = gSmst->CpuSaveState[CpuIndex];

  if (mSmmFeatureSaveStateRegisterLma == EFI_SMM_SAVE_STATE_REGISTER_LMA_32BIT) {
    //
    // If 32-bit mode width is zero, then the specified register can not be accessed
    //
    if (mSmmFeatureCpuWidthOffset[RegisterIndex].Width32 == 0) {
      return EFI_NOT_FOUND;
    }

    //
    // If Width is bigger than the 32-bit mode width, then the specified register can not be accessed
    //
    if (Width > mSmmFeatureCpuWidthOffset[RegisterIndex].Width32) {
      return EFI_INVALID_PARAMETER;
    }

    //
    // Write return buffer
    //
    ASSERT(CpuSaveState != NULL);
    CopyMem(Buffer, (UINT8 *)CpuSaveState + mSmmFeatureCpuWidthOffset[RegisterIndex].Offset32, Width);
  } else {
    //
    // If 64-bit mode width is zero, then the specified register can not be accessed
    //
    if (mSmmFeatureCpuWidthOffset[RegisterIndex].Width64 == 0) {
      return EFI_NOT_FOUND;
    }

    //
    // If Width is bigger than the 64-bit mode width, then the specified register can not be accessed
    //
    if (Width > mSmmFeatureCpuWidthOffset[RegisterIndex].Width64) {
      return EFI_INVALID_PARAMETER;
    }

    if (mSaveStateInMsr) {

      MsrInfo.MsrIndex = mSmmFeatureCpuWidthOffset[RegisterIndex].MsrIndex;
      if (MsrInfo.MsrIndex == 0) {
        //
        // If no corresponding MSR
        //
        return EFI_UNSUPPORTED;
      }
      ReadSaveStateMsr(CpuIndex, &MsrInfo);

      CopyMem(Buffer, (UINT8 *)&MsrInfo.MsrValue + mSmmFeatureCpuWidthOffset[RegisterIndex].OffsetInMsr, Width);
    } else {
      //
      // Write lower 32-bits of return buffer
      //
      CopyMem(Buffer, (UINT8 *)CpuSaveState + mSmmFeatureCpuWidthOffset[RegisterIndex].Offset64Lo, MIN(4, Width));
      if (Width >= 4) {
        //
        // Write upper 32-bits of return buffer
        //
        CopyMem((UINT8 *)Buffer + 4, (UINT8 *)CpuSaveState + mSmmFeatureCpuWidthOffset[RegisterIndex].Offset64Hi, Width - 4);
      }
    }
  }
  return EFI_SUCCESS;
}

/**
  Read an SMM Save State register on the target processor.  If this function
  returns EFI_UNSUPPORTED, then the caller is responsible for reading the
  SMM Save Sate register.

  @param[in]  CpuIndex  The index of the CPU to read the SMM Save State.  The
                        value must be between 0 and the NumberOfCpus field in
                        the System Management System Table (SMST).
  @param[in]  Register  The SMM Save State register to read.
  @param[in]  Width     The number of bytes to read from the CPU save state.
  @param[out] Buffer    Upon return, this holds the CPU register value read
                        from the save state.

  @retval EFI_SUCCESS           The register was read from Save State.
  @retval EFI_INVALID_PARAMTER  Buffer is NULL.
  @retval EFI_UNSUPPORTED       This function does not support reading Register.
  @retval EFI_NOT_FOUND         The register is not defined for the Save State of Processor.

**/
EFI_STATUS
EFIAPI
SmmCpuFeaturesReadSaveStateRegister (
  IN  UINTN                        CpuIndex,
  IN  EFI_SMM_SAVE_STATE_REGISTER  Register,
  IN  UINTN                        Width,
  OUT VOID                         *Buffer
  )
{
  UINT32                      SmmRevId;
  SMRAM_SAVE_STATE_IOMISC     IoMisc;
  EFI_SMM_SAVE_STATE_IO_INFO  *IoInfo;

  //
  // Check for special EFI_SMM_SAVE_STATE_REGISTER_LMA
  //
  if (Register == EFI_SMM_SAVE_STATE_REGISTER_LMA) {
    //
    // Only byte access is supported for this register
    //
    if (Width != 1) {
      return EFI_INVALID_PARAMETER;
    }

    *(UINT8 *)Buffer = mSmmFeatureSaveStateRegisterLma;

    return EFI_SUCCESS;
  }

  //
  // Check for special EFI_SMM_SAVE_STATE_REGISTER_IO
  //
  if (Register == EFI_SMM_SAVE_STATE_REGISTER_IO) {
    //
    // Get SMM Revision ID
    //
    SmmReadSaveStateRegisterByIndex (CpuIndex, SMM_SAVE_STATE_REGISTER_SMMREVID_INDEX, sizeof(SmmRevId), &SmmRevId);

    //
    // See if the CPU supports the IOMisc register in the save state
    //
    if (SmmRevId < SMRAM_SAVE_STATE_MIN_REV_ID_IOMISC) {
      return EFI_NOT_FOUND;
    }

    //
    // Get the IOMisc register value
    //
    SmmReadSaveStateRegisterByIndex (CpuIndex, SMM_SAVE_STATE_REGISTER_IOMISC_INDEX, sizeof(IoMisc.Uint32), &IoMisc.Uint32);

    //
    // Check for the SMI_FLAG in IOMisc
    //
    if (IoMisc.Bits.SmiFlag == 0) {
      return EFI_NOT_FOUND;
    }

    //
    // Only support IN/OUT, but not INS/OUTS/REP INS/REP OUTS.
    //
    if ((mSmmFeatureCpuIoType[IoMisc.Bits.Type] != EFI_SMM_SAVE_STATE_IO_TYPE_INPUT) &&
        (mSmmFeatureCpuIoType[IoMisc.Bits.Type] != EFI_SMM_SAVE_STATE_IO_TYPE_OUTPUT)) {
      return EFI_UNSUPPORTED;
    }

    //
    // Compute index for the I/O Length and I/O Type lookup tables
    //
    if (mSmmFeatureCpuIoWidth[IoMisc.Bits.Length].Width == 0 || mSmmFeatureCpuIoType[IoMisc.Bits.Type] == 0) {
      return EFI_NOT_FOUND;
    }

    //
    // Zero the IoInfo structure that will be returned in Buffer
    //
    IoInfo = (EFI_SMM_SAVE_STATE_IO_INFO *)Buffer;
    ZeroMem (IoInfo, sizeof(EFI_SMM_SAVE_STATE_IO_INFO));

    //
    // Use lookup tables to help fill in all the fields of the IoInfo structure
    //
    IoInfo->IoPort = (UINT16)IoMisc.Bits.Port;
    IoInfo->IoWidth = mSmmFeatureCpuIoWidth[IoMisc.Bits.Length].IoWidth;
    IoInfo->IoType = mSmmFeatureCpuIoType[IoMisc.Bits.Type];
    SmmCpuFeaturesReadSaveStateRegister (CpuIndex, EFI_SMM_SAVE_STATE_REGISTER_RAX, mSmmFeatureCpuIoWidth[IoMisc.Bits.Length].Width, &IoInfo->IoData);
    return EFI_SUCCESS;
  }

  //
  // Convert Register to a register lookup table index
  //
  return SmmReadSaveStateRegisterByIndex (CpuIndex, SmmFeatureGetRegisterIndex (Register), Width, Buffer);
}

/**
  Write the value in the buffer into a CPU Save State MSR on an AP.

  @param[in,out] Buffer  Pointer to private data buffer.
**/
VOID
EFIAPI
WriteSaveStateMsrOnAp (
  IN OUT VOID  *Buffer
  )
{
  MSR_INFO *MsrInfo;

  MsrInfo = (MSR_INFO *)Buffer;
  AsmWriteMsr64 (MsrInfo->MsrIndex, MsrInfo->MsrValue);

  //
  // Release the MSR spin lock.
  //
  ReleaseSpinLock (mMsrSpinLock);
}

/**
  Write value to a CPU Save State MSR on the target processor.

  If the target processor is the BSP, directly write the MSR. Otherwise, call blocking SmmStartupThisAp()
  to write the MSR on the target processor.

  @param[in] CpuIndex  Specifies the zero-based index of the CPU save state.
  @param[in] MsrInfo   Pointer to a MSR_INFO data structure holding the index and value of a MSR.
**/
VOID
WriteSaveStateMsr (
  IN UINTN     CpuIndex,
  IN MSR_INFO  *MsrInfo
  )
{
  EFI_STATUS Status;

  //
  // For MSR_EFLAGS, we can NOT write BIT1, which is reserved field.
  // Even though its reserve value is "1", writing "1" to BIT1 of MSR_EFLAGS will cause #GP.
  //
  if (MsrInfo->MsrIndex == MSR_EFLAGS) {
    MsrInfo->MsrValue &= ~((UINT64)BIT1);
  }

  if (CpuIndex == gSmst->CurrentlyExecutingCpu) {
     AsmWriteMsr64 (MsrInfo->MsrIndex, MsrInfo->MsrValue);
  } else {
    //
    // Acquire MSR spin lock.  The AP will release the
    // spin lock when it is done executing ReadSaveStateMsrOnAp().
    //
    AcquireSpinLock (mMsrSpinLock);

    //
    // Call SmmStartupThisAp() to write MSR on AP.
    //
    Status = gSmst->SmmStartupThisAp (WriteSaveStateMsrOnAp, CpuIndex, MsrInfo);
    ASSERT_EFI_ERROR (Status);

    //
    // Wait for the AP to release the MSR spin lock.
    //
    while (!AcquireSpinLockOrFail (mMsrSpinLock)) {
      CpuPause ();
    }

    //
    // Release the MSR spin lock.
    //
    ReleaseSpinLock (mMsrSpinLock);
  }
}

/**
  Writes an SMM Save State register on the target processor.  If this function
  returns EFI_UNSUPPORTED, then the caller is responsible for writing the
  SMM Save Sate register.

  @param[in] CpuIndex  The index of the CPU to write the SMM Save State.  The
                       value must be between 0 and the NumberOfCpus field in
                       the System Management System Table (SMST).
  @param[in] Register  The SMM Save State register to write.
  @param[in] Width     The number of bytes to write to the CPU save state.
  @param[in] Buffer    Upon entry, this holds the new CPU register value.

  @retval EFI_SUCCESS           The register was written to Save State.
  @retval EFI_INVALID_PARAMTER  Buffer is NULL.
  @retval EFI_UNSUPPORTED       This function does not support writing Register.
**/
EFI_STATUS
EFIAPI
SmmCpuFeaturesWriteSaveStateRegister (
  IN UINTN                        CpuIndex,
  IN EFI_SMM_SAVE_STATE_REGISTER  Register,
  IN UINTN                        Width,
  IN CONST VOID                   *Buffer
  )
{
  UINTN                 RegisterIndex;
  SMRAM_SAVE_STATE_MAP  *CpuSaveState;
  MSR_INFO              MsrInfo;

  //
  // Writes to EFI_SMM_SAVE_STATE_REGISTER_LMA are ignored
  //
  if (Register == EFI_SMM_SAVE_STATE_REGISTER_LMA) {
    return EFI_SUCCESS;
  }

  //
  // Writes to EFI_SMM_SAVE_STATE_REGISTER_IO are not supported
  //
  if (Register == EFI_SMM_SAVE_STATE_REGISTER_IO) {
    return EFI_NOT_FOUND;
  }

  //
  // Convert Register to a register lookup table index
  //
  RegisterIndex = SmmFeatureGetRegisterIndex (Register);
  if (RegisterIndex == 0) {
    return EFI_NOT_FOUND;
  }

  CpuSaveState = gSmst->CpuSaveState[CpuIndex];

  //
  // Do not write non-writeable SaveState, because in MsrSaveState it will cause exception.
  //
  if (!mSmmFeatureCpuWidthOffset[RegisterIndex].Writeable) {
    return EFI_UNSUPPORTED;
  }

  //
  // Check CPU mode
  //
  if (mSmmFeatureSaveStateRegisterLma == EFI_SMM_SAVE_STATE_REGISTER_LMA_32BIT) {
    //
    // If 32-bit mode width is zero, then the specified register can not be accessed
    //
    if (mSmmFeatureCpuWidthOffset[RegisterIndex].Width32 == 0) {
      return EFI_NOT_FOUND;
    }

    //
    // If Width is bigger than the 32-bit mode width, then the specified register can not be accessed
    //
    if (Width > mSmmFeatureCpuWidthOffset[RegisterIndex].Width32) {
      return EFI_INVALID_PARAMETER;
    }
    //
    // Write SMM State register
    //
    ASSERT (CpuSaveState != NULL);
    CopyMem((UINT8 *)CpuSaveState + mSmmFeatureCpuWidthOffset[RegisterIndex].Offset32, Buffer, Width);
  } else {
    //
    // If 64-bit mode width is zero, then the specified register can not be accessed
    //
    if (mSmmFeatureCpuWidthOffset[RegisterIndex].Width64 == 0) {
      return EFI_NOT_FOUND;
    }

    //
    // If Width is bigger than the 64-bit mode width, then the specified register can not be accessed
    //
    if (Width > mSmmFeatureCpuWidthOffset[RegisterIndex].Width64) {
      return EFI_INVALID_PARAMETER;
    }

    if (mSaveStateInMsr) {

      MsrInfo.MsrIndex = mSmmFeatureCpuWidthOffset[RegisterIndex].MsrIndex;
      if (MsrInfo.MsrIndex == 0) {
        //
        // If no corresponding MSR
        //
        return EFI_UNSUPPORTED;
      }
      //
      // If the CPU Save State register is to be partially modified, read the current value to keep the un-modified part intact.
      //
      if ((mSmmFeatureCpuWidthOffset[RegisterIndex].Width64 != sizeof (UINT64)) ||
          (mSmmFeatureCpuWidthOffset[RegisterIndex].Width64 != Width)) {
        ReadSaveStateMsr (CpuIndex, &MsrInfo);
      }

      CopyMem((UINT8 *)&MsrInfo.MsrValue + mSmmFeatureCpuWidthOffset[RegisterIndex].OffsetInMsr, Buffer, Width);
      WriteSaveStateMsr (CpuIndex, &MsrInfo);
    } else {
      //
      // Write lower 32-bits of SMM State register
      //
      CopyMem((UINT8 *)CpuSaveState + mSmmFeatureCpuWidthOffset[RegisterIndex].Offset64Lo, Buffer, MIN (4, Width));
      if (Width >= 4) {
        //
        // Write upper 32-bits of SMM State register
        //
        CopyMem((UINT8 *)CpuSaveState + mSmmFeatureCpuWidthOffset[RegisterIndex].Offset64Hi, (UINT8 *)Buffer + 4, Width - 4);
      }
    }
  }
  return EFI_SUCCESS;
}

/**
  This function updates the SMRAM save state on the currently executing CPU
  to resume execution at a specific address after an RSM instruction.  This
  function must evaluate the SMRAM save state to determine the execution mode
  the RSM instruction resumes and update the resume execution address with
  either NewInstructionPointer32 or NewInstructionPoint.  The auto HALT restart
  flag in the SMRAM save state must always be cleared.  This function returns
  the value of the instruction pointer from the SMRAM save state that was
  replaced.  If this function returns 0, then the SMRAM save state was not
  modified.

  This function is called during the very first SMI on each CPU after
  SmmCpuFeaturesInitializeProcessor() to set a flag in normal execution mode
  to signal that the SMBASE of each CPU has been updated before the default
  SMBASE address is used for the first SMI to the next CPU.

  @param[in] CpuIndex                 The index of the CPU to hook.  The value
                                      must be between 0 and the NumberOfCpus
                                      field in the System Management System Table
                                      (SMST).
  @param[in] CpuState                 Pointer to SMRAM Save State Map for the
                                      currently executing CPU.
  @param[in] NewInstructionPointer32  Instruction pointer to use if resuming to
                                      32-bit execution mode from 64-bit SMM.
  @param[in] NewInstructionPointer    Instruction pointer to use if resuming to
                                      same execution mode as SMM.

  @retval 0    This function did modify the SMRAM save state.
  @retval > 0  The original instruction pointer value from the SMRAM save state
               before it was replaced.
**/
UINT64
EFIAPI
SmmCpuFeaturesHookReturnFromSmm (
  IN UINTN                 CpuIndex,
  IN SMRAM_SAVE_STATE_MAP  *CpuState,
  IN UINT64                NewInstructionPointer32,
  IN UINT64                NewInstructionPointer
  )
{
  UINT64  OriginalInstructionPointer;

  if (mSmmFeatureSaveStateRegisterLma == EFI_SMM_SAVE_STATE_REGISTER_LMA_64BIT) {
    //
    // Check to see if the currently executing CPU enters into SMM with save state
    // in MSRs enabled. If the processor enters into SMM with save state in MSRs
    // disabled, it should not access save state through MSRs even it may set
    // SMM_CPU_SAVE_EN_BIT at this SMM entry.
    //
    if (mSmmInitSaveStateInMsr) {
      OriginalInstructionPointer = AsmReadMsr64 (MSR_RIP);
      if ((AsmReadMsr64 (MSR_EFER) & LMA) == 0) {
        AsmWriteMsr64 (MSR_RIP, NewInstructionPointer32);
      } else {
        AsmWriteMsr64 (MSR_RIP, NewInstructionPointer);
      }
      //
      // Clear the auto HALT restart flag so the RSM instruction returns
      // program control to the instruction following the HLT instruction.
      //
      if ((AsmReadMsr64 (MSR_EVENT_CTL_HLT_IO) & BIT16) != 0) {
        AsmMsrBitFieldAnd64 (MSR_EVENT_CTL_HLT_IO, 16, 16, 0);
      }
      return OriginalInstructionPointer;
    }
  }
  return 0;
}
