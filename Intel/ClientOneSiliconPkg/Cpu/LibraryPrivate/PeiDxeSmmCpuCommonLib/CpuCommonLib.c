/** @file
  CPU Common Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/CpuLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TimerLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/CpuMailboxLib.h>
#include <Library/BootGuardLib.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuAccess.h>
#include <Register/LocalApic.h>
#include <Library/CpuCommonLib.h>

#define INTERRUPT_VECTOR_NUMBER 256
#define END_OF_TIMETABLE        0x3FF

///
/// Table to convert Seconds into equivalent MSR values
/// This table is used for PL1, Pl2 and RATL TDP Time Window programming
///
GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mSecondsToMsrValueMapTable[][2] = {
  ///
  ///  Seconds,    MSR Value
  ///
  {        1,         0x0A     },
  {        2,         0x0B     },
  {        3,         0x4B     },
  {        4,         0x0C     },
  {        5,         0x2C     },
  {        6,         0x4C     },
  {        7,         0x6C     },
  {        8,         0x0D     },
  {       10,         0x2D     },
  {       12,         0x4D     },
  {       14,         0x6D     },
  {       16,         0x0E     },
  {       20,         0x2E     },
  {       24,         0x4E     },
  {       28,         0x6E     },
  {       32,         0x0F     },
  {       40,         0x2F     },
  {       48,         0x4F     },
  {       56,         0x6F     },
  {       64,         0x10     },
  {       80,         0x30     },
  {       96,         0x50     },
  {      112,         0x70     },
  {      128,         0x11     },
  {      160,         0x31     },
  {      192,         0x51     },
  {      224,         0x71     },
  {      256,         0x12     },
  {      320,         0x32     },
  {      384,         0x52     },
  {      448,         0x72     },
  { END_OF_TIMETABLE, END_OF_TIMETABLE }
};

///
/// Table to convert Milli Seconds into equivalent MSR values
/// This table is used for Pl3 and RATL TDP Time Window programming
///
GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mMilliSecondsToMsrValueMapTable[][2] = {
  ///
  ///  MilliSeconds,  MSR Value
  ///
  {        3,         0x41     },
  {        4,         0x02     },
  {        5,         0x22     },
  {        6,         0x42     },
  {        7,         0x62     },
  {        8,         0x03     },
  {       10,         0x23     },
  {       12,         0x43     },
  {       14,         0x63     },
  {       16,         0x04     },
  {       20,         0x24     },
  {       24,         0x44     },
  {       28,         0x64     },
  {       32,         0x05     },
  {       40,         0x25     },
  {       48,         0x45     },
  {       55,         0x65     },
  {       56,         0x65     },
  {       64,         0x06     },
  {      156,         0x27     },
  {      375,         0x48     },
  {      500,         0x09     },
  {      750,         0x49     },
  { END_OF_TIMETABLE, END_OF_TIMETABLE }
};

/**
  Initialize prefetcher settings

  @param[in] MlcStreamerprefecterEnabled - Enable/Disable MLC streamer prefetcher
  @param[in] MlcSpatialPrefetcherEnabled - Enable/Disable MLC spatial prefetcher
**/
VOID
ProcessorsPrefetcherInitialization (
  IN UINTN MlcStreamerprefecterEnabled,
  IN UINTN MlcSpatialPrefetcherEnabled
  )
{
  UINT64 MsrValue;
  MsrValue = AsmReadMsr64 (MSR_MISC_FEATURE_CONTROL);

  if (MlcStreamerprefecterEnabled == 0) {
    MsrValue |= B_MSR_MISC_FEATURE_CONTROL_MLC_STREAMER_PREFETCH_DISABLE_MASK;
  }

  if (MlcSpatialPrefetcherEnabled == 0) {
    MsrValue |= B_MSR_MISC_FEATURE_CONTROL_MLC_SPATIAL_PREFETCH_DISABLE_MASK;
  }

  if ((MsrValue & (B_MSR_MISC_FEATURE_CONTROL_MLC_STREAMER_PREFETCH_DISABLE_MASK | B_MSR_MISC_FEATURE_CONTROL_MLC_SPATIAL_PREFETCH_DISABLE_MASK)) != 0) {
    AsmWriteMsr64 (MSR_MISC_FEATURE_CONTROL, MsrValue);
  }

  return;
}

/**
  Set up flags in CR4 for XMM instruction enabling
**/
VOID
EFIAPI
XmmInit (
  VOID
  )
{
  EFI_CPUID_REGISTER Cpuid;
  UINTN              Cr0;
  UINTN              Cr4;

  ///
  /// Read the CPUID information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);

  ///
  /// Check whether SSE2 is supported
  ///
  if (Cpuid.RegEdx & BIT26) {
    ///
    /// Enable XMM
    ///
    Cr0 = AsmReadCr0 ();
    Cr0 |= BIT1;
    AsmWriteCr0 (Cr0);

    Cr4 = AsmReadCr4 ();
    Cr4 |= (UINTN) (BIT9 | BIT10);
    AsmWriteCr4 (Cr4);
  }
}

/**
  Enable "Machine Check Enable" bit in Cr4
**/
VOID
EFIAPI
EnableMce (
  VOID
  )
{
  UINTN Cr4;

  ///
  /// Enable MCE
  ///
  Cr4 = AsmReadCr4 ();
  Cr4 |= BIT6;
  AsmWriteCr4 (Cr4);
}

/**
  Mtrr Synch Up Entry
**/
UINTN
EFIAPI
MpMtrrSynchUpEntry (
  VOID
  )
{
  EFI_CPUID_REGISTER Cpuid;
  UINT64 MsrData;
  UINTN  Cr0;
  UINTN  Cr4;

  ///
  /// Read the CPUID and MSR 1Bh information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  MsrData = AsmReadMsr64 (MSR_IA32_APIC_BASE);

  ///
  /// Set CD(Bit30) bit and clear NW(Bit29) bit of CR0 followed by a WBINVD.
  ///
  if (!(Cpuid.RegEdx & BIT24) || (MsrData & BIT8)) {
    AsmDisableCache ();
  } else {
    ///
    /// We could bypass the wbinvd by
    /// checking MSR 1Bh(MSR_IA32_APIC_BASE) Bit8 (1 = BSP, 0 = AP) to see if we're the BSP?
    /// and checking CPUID if the processor support self-snooping.
    ///
    Cr0 = AsmReadCr0 ();
    Cr0 &= (UINTN) ~BIT29;
    Cr0 |= BIT30;
    AsmWriteCr0 (Cr0);
  }

  ///
  /// Clear PGE flag Bit 7
  ///
  Cr4 = AsmReadCr4 ();
  Cr4 &= (UINTN) ~BIT7;
  AsmWriteCr4 (Cr4);

  ///
  /// Flush all TLBs
  ///
  CpuFlushTlb ();

  return Cr4;
}

/**
  Mtrr Synch Up Exit
**/
VOID
EFIAPI
MpMtrrSynchUpExit (
  UINTN Cr4
  )
{
  UINTN  Cr0;

  ///
  /// Flush all TLBs the second time
  ///
  CpuFlushTlb ();

  ///
  /// Clear both the CD and NW bits of CR0.
  ///
  Cr0 = AsmReadCr0 ();
  Cr0 &= (UINTN) ~(BIT29 | BIT30);
  AsmWriteCr0 (Cr0);

  ///
  /// Set PGE Flag in CR4 if set
  ///
  AsmWriteCr4 (Cr4);
}

/**
  This procedure sends an IPI to the designated processor in
  the requested delivery mode with the requested vector.

  @param[in] ApicID          - APIC ID of processor.
  @param[in] VectorNumber    - Vector number.
  @param[in] DeliveryMode    - I/O APIC Interrupt Deliver Modes

  @retval EFI_INVALID_PARAMETER - Input paramters were not correct.
  @retval EFI_NOT_READY         - There was a pending interrupt
  @retval EFI_SUCCESS           - Interrupt sent successfully
**/
EFI_STATUS
EFIAPI
CpuSendIpi (
  IN UINT32            ApicID,
  IN UINTN             VectorNumber,
  IN UINTN             DeliveryMode
  )
{
  MSR_IA32_APIC_BASE_REGISTER Msr;
  EFI_PHYSICAL_ADDRESS        ApicBase;
  UINT32                      IcrLow;
  UINT32                      IcrHigh;
  BOOLEAN                     XapicEnabled;
  UINT32                      TriggerMode;

  ///
  /// Check for valid input parameters.
  ///
  if (VectorNumber >= INTERRUPT_VECTOR_NUMBER) {
    return EFI_INVALID_PARAMETER;
  }

  if (DeliveryMode >= LOCAL_APIC_DELIVERY_MODE_EXTINT) {
    return EFI_INVALID_PARAMETER;
  }

  ///
  /// Fix the vector number for special interrupts like SMI and INIT.
  ///
  if (DeliveryMode == LOCAL_APIC_DELIVERY_MODE_SMI || DeliveryMode == LOCAL_APIC_DELIVERY_MODE_INIT) {
    VectorNumber = 0x0;
  }

  ///
  /// Initialze ICR high dword, since P6 family processor needs
  /// the destination field to be 0x0F when it is a broadcast
  ///
  IcrHigh = 0x0f000000;
  IcrLow  = (UINT32) (VectorNumber | (LShiftU64 (DeliveryMode, 8)));

  TriggerMode = TRIGGER_MODE_EDGE;

  ///
  /// Interrupt trigger mode
  ///
  if (TriggerMode == TRIGGER_MODE_LEVEL) {
    IcrLow |= 0x8000;
  }

  ///
  /// Interrupt pin polarity
  ///
  IcrLow |= 0x4000;

  ///
  /// xAPIC Enabled
  ///
  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_APIC_BASE);
  XapicEnabled = (BOOLEAN) ((Msr.Bits.EXTD == 1) && (Msr.Bits.EN == 1));

  if (XapicEnabled) {
    IcrHigh = (UINT32) ApicID;
  } else {
    IcrHigh = (UINT32) LShiftU64 (ApicID, 24);
  }

  ApicBase    = Msr.Uint64 & 0xffffff000;

  /* If Extended XAPIC Mode is enabled,
     legacy xAPIC is no longer working.
     So, previous MMIO offset must be transferred to MSR offset R/W.
     ----------------------------------------------------------------
     MMIO Offset     MSR Offset     Register Name
     ----------------------------------------------------------------
     300h-310h        830h         Interrupt Command Register [63:0]
                      831h         [Reserved]
     ----------------------------------------------------------------
  */
  ///
  /// To write APIC register by MSR or MMIO
  ///
  if (XapicEnabled) {
    AsmWriteMsr64 (MSR_IA32_X2APIC_ICR, (((UINT64) LShiftU64 (IcrHigh, 32)) | (UINT64) IcrLow));
  } else {
    *(volatile UINT32 *) (UINTN) (ApicBase  + XAPIC_ICR_HIGH_OFFSET) = (UINT32) IcrHigh;
    *(volatile UINT32 *) (UINTN) (ApicBase  + XAPIC_ICR_LOW_OFFSET) = (UINT32) IcrLow;
  }

  MicroSecondDelay (10);

  ///
  /// To get APIC register from MSR or MMIO
  ///
  if (XapicEnabled) {
    IcrLow = (UINT32) AsmReadMsr64 (MSR_IA32_X2APIC_ICR);
  } else {
    IcrLow = (UINT32) *(volatile UINT32 *) (UINTN) (ApicBase + XAPIC_ICR_LOW_OFFSET);
  }

  if (IcrLow & BIT12) {
    return EFI_NOT_READY;
  }

  MicroSecondDelay (100);

  return EFI_SUCCESS;
}

/**
  Private helper function to convert various Turbo Power Limit Time from Seconds to CPU units

  @param[in] TimeInSeconds       Time in seconds
  @param[in] TimeWindowConvType  Time Window Convert Type

  @retval UINT8 Converted time in CPU units
**/
UINT8
GetConvertedTime (
  IN UINT32            TimeInSeconds,
  IN TIME_WINDOW_CONV  TimeWindowConvType
  )
{
  UINT8 ConvertedPowerLimitTime;
  UINT8 Index;

  ///
  /// Convert seconds to MSR value. Since not all values are programmable, we'll select
  /// the entry from mapping table which is either equal to the user selected value. OR to a value in the mapping table
  /// which is closest (but less than) to the user-selected value.
  ///
  ConvertedPowerLimitTime = 0;
  switch (TimeWindowConvType) {
    case SecondsTimeWindowConvert:
      ConvertedPowerLimitTime = (UINT8) mSecondsToMsrValueMapTable[0][1];
      for (Index = 0; mSecondsToMsrValueMapTable[Index][0] != END_OF_TIMETABLE; Index++) {
        if (TimeInSeconds == mSecondsToMsrValueMapTable[Index][0]) {
          ConvertedPowerLimitTime = (UINT8) mSecondsToMsrValueMapTable[Index][1];
          break;
        }
        if (TimeInSeconds > mSecondsToMsrValueMapTable[Index][0]) {
          ConvertedPowerLimitTime = (UINT8) mSecondsToMsrValueMapTable[Index][1];
        } else {
          break;
        }
      }
      break;
    case MilliSecondsTimeWindowConvert:
      ConvertedPowerLimitTime = (UINT8) mMilliSecondsToMsrValueMapTable[0][1];
      for (Index = 0; mMilliSecondsToMsrValueMapTable[Index][0] != END_OF_TIMETABLE; Index++) {
        if (TimeInSeconds == mMilliSecondsToMsrValueMapTable[Index][0]) {
          ConvertedPowerLimitTime = (UINT8) mMilliSecondsToMsrValueMapTable[Index][1];
          break;
        }
        if (TimeInSeconds > mMilliSecondsToMsrValueMapTable[Index][0]) {
          ConvertedPowerLimitTime = (UINT8) mMilliSecondsToMsrValueMapTable[Index][1];
        } else {
          break;
        }
      }
      break;
    default:
      break;
  }

  return ConvertedPowerLimitTime;
}

/**
  Get APIC ID of processor

  @retval APIC ID of processor
**/
UINT32
GetCpuApicId (
  VOID
  )
{
  EFI_CPUID_REGISTER CpuidRegisters;

  AsmCpuid (
    CPUID_VERSION_INFO,
    &CpuidRegisters.RegEax,
    &CpuidRegisters.RegEbx,
    &CpuidRegisters.RegEcx,
    &CpuidRegisters.RegEdx
    );
  return (UINT32) (CpuidRegisters.RegEbx >> 24);
}

/**
  Programs XAPIC registers.

  @param[in] Bsp             - Is this BSP?
**/
VOID
ProgramXApic (
  BOOLEAN Bsp
  )
{
  UINT64               ApicBaseReg;
  EFI_PHYSICAL_ADDRESS ApicBase;
  volatile UINT32      *EntryAddress;
  UINT32               EntryValue;

  ApicBaseReg = AsmReadMsr64 (MSR_IA32_APIC_BASE);
  ApicBase    = ApicBaseReg & 0xffffff000ULL;

  ///
  /// Program the spurious vector entry
  ///
  EntryAddress  = (UINT32 *) (UINTN) (ApicBase + XAPIC_SPURIOUS_VECTOR_OFFSET);
  EntryValue    = *EntryAddress;
  EntryValue &= 0xFFFFFD0F;
  EntryValue |= 0x10F;
  *EntryAddress = EntryValue;

  ///
  /// Program the LINT1 vector entry as extINT
  ///
  EntryAddress  = (UINT32 *) (UINTN) (ApicBase + XAPIC_LVT_LINT0_OFFSET);
  EntryValue    = *EntryAddress;

  if (Bsp) {
    EntryValue &= 0xFFFE00FF;
    EntryValue |= 0x700;
  } else {
    EntryValue |= 0x10000;
  }

  *EntryAddress = EntryValue;

  ///
  /// Program the LINT1 vector entry as NMI
  ///
  EntryAddress  = (UINT32 *) (UINTN) (ApicBase + XAPIC_LVT_LINT1_OFFSET);
  EntryValue    = *EntryAddress;
  EntryValue &= 0xFFFE00FF;
  if (Bsp) {
    EntryValue |= 0x400;
  } else {
    EntryValue |= 0x10400;
  }

  *EntryAddress = EntryValue;
}

/**
  This function is to disable BIOS Write Protect in SMM phase.
**/
VOID
EFIAPI
CpuSmmDisableBiosWriteProtect (
  VOID
  )
{
  UINT32      Data32;

  ///
  /// Read memory location FED30880h OR with 00000001h, place the result in EAX,
  /// and write data to lower 32 bits of MSR 1FEh (sample code available)
  ///
  Data32 = MmioRead32 (0xFED30880);
  AsmWriteMsr32 (MSR_SPCL_CHIPSET_USAGE, Data32 | BIT0);
  ///
  /// Read FED30880h back to ensure the setting went through.
  ///
  Data32 = MmioRead32 (0xFED30880);
}

/**
  This function is to enable BIOS Write Protect in SMM phase.
**/
VOID
EFIAPI
CpuSmmEnableBiosWriteProtect (
  VOID
  )
{
  UINT32      Data32;

  ///
  /// Read memory location FED30880h AND with FFFFFFFEh, place the result in EAX,
  /// and write data to lower 32 bits of MSR 1FEh (sample code available)
  ///
  Data32 = MmioRead32 (0xFED30880);
  AsmWriteMsr32 (MSR_SPCL_CHIPSET_USAGE, Data32 & (UINT32) (~BIT0));
  ///
  /// Read FED30880h back to ensure the setting went through.
  ///
  Data32 = MmioRead32 (0xFED30880);
}

/**
  This function returns the maximum number of cores supported in this physical processor package.

  @retval Maximum number of supported cores in the package.
**/
UINT8
GetMaxSupportedCoreCount (
  VOID
  )
{
  EFI_CPUID_REGISTER Cpuid;
  AsmCpuidEx (
    4,
    0,
    &Cpuid.RegEax,
    NULL,
    NULL,
    NULL
    );
  return (UINT8) (RShiftU64 (Cpuid.RegEax, 26) & 0x3f) + 1;
}

/**
  This function returns the actual factory-configured number of threads per core,
  and actual factory-configured number of cores in this physical processor package.

  @param[out] *ThreadsPerCore    - variable that will store Maximum enabled threads per core
  @param[out] *NumberOfCores     - variable that will store Maximum enabled cores per die
**/
VOID
GetSupportedCount (
  OUT UINT16 *ThreadsPerCore,  OPTIONAL
  OUT UINT16 *NumberOfCores    OPTIONAL
  )
{
  EFI_CPUID_REGISTER    CpuidRegs;
  UINT16                Threads;

  AsmCpuidEx (CPUID_EXTENDED_TOPOLOGY, 0, NULL, &CpuidRegs.RegEbx, NULL, NULL);
  Threads = (UINT16) CpuidRegs.RegEbx;

  if (ThreadsPerCore != NULL) {
    *ThreadsPerCore = Threads;
  }

  if (NumberOfCores != NULL) {
    AsmCpuidEx (CPUID_EXTENDED_TOPOLOGY, 1, NULL, &CpuidRegs.RegEbx, NULL, NULL);
    *NumberOfCores = (UINT16) (CpuidRegs.RegEbx / Threads);
  }
}

/**
  This function returns the maximum enabled Core per die, maximum enabled threads per core,
  maximum number of dies and packages

  @param[out] *NumberOfEnabledThreadsPerCore  - variable that will store Maximum enabled threads per core
  @param[out] *NumberOfEnabledCoresPerDie     - variable that will store Maximum enabled cores per die
  @param[out] *NumberOfDiesPerPackage         - variable that will store Maximum dies per package
  @param[out] *NumberOfPackages               - variable that will store Maximum Packages
**/
VOID
GetEnabledCount (
  OUT UINT16 *NumberOfEnabledThreadsPerCore,  OPTIONAL
  OUT UINT16 *NumberOfEnabledCoresPerDie,     OPTIONAL
  OUT UINT16 *NumberOfDiesPerPackage,         OPTIONAL
  OUT UINT16 *NumberOfPackages                OPTIONAL
  )
{
  UINT64 MsrValue;
  UINT16 NumCores;

  ///
  /// Read MSR_CORE_THREAD_COUNT (0x35)
  ///
  MsrValue = AsmReadMsr64 (MSR_CORE_THREAD_COUNT);

  NumCores = (UINT16) RShiftU64 (MsrValue, N_MSR_CORE_THREAD_COUNT_CORECOUNT_OFFSET);

  ///
  /// Get enabled core count in the package (BITS[31:16])
  ///
  if (NumberOfEnabledCoresPerDie != NULL) {
    *NumberOfEnabledCoresPerDie = NumCores;
  }

  ///
  /// Get enabled thread count in the package (BITS[15:0])
  ///
  if (NumberOfEnabledThreadsPerCore != NULL) {
    *NumberOfEnabledThreadsPerCore  = (UINT16) DivU64x32 ((UINT64) (MsrValue & B_MSR_CORE_THREAD_COUNT_THREADCOUNT_MASK), (UINT32) NumCores);
  }

  ///
  /// For client, the number of dies and packages will be one
  ///
  if (NumberOfDiesPerPackage != NULL) {
    *NumberOfDiesPerPackage  = 1;
  }

  if (NumberOfPackages != NULL) {
    *NumberOfPackages        = 1;
  }
}

/**
  Check to see if the executing thread is BSP

  @retval TRUE   Executing thread is BSP
  @retval FALSE  Executing thread is AP
**/
BOOLEAN
IsBsp (
  VOID
  )
{
  MSR_IA32_APIC_BASE_REGISTER Msr;

  Msr.Uint64  = AsmReadMsr64 (MSR_IA32_APIC_BASE);
  return (BOOLEAN) (Msr.Bits.BSP == 1);
}

/**
  Stop PBE timer if system is in Boot Guard boot

  @retval EFI_SUCCESS        - Stop PBE timer
  @retval EFI_UNSUPPORTED    - Not in Boot Guard boot mode.
**/
EFI_STATUS
StopPbeTimer (
  VOID
  )
{
  UINT64   BootGuardBootStatus;
  UINT64   BootGuardOperationMode;

  if (IsBootGuardSupported ()) {
    BootGuardBootStatus = (*(UINT64 *) (UINTN) (TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_BOOTSTATUS) & (BIT63|BIT62));
    BootGuardOperationMode = AsmReadMsr64 (MSR_BOOT_GUARD_SACM_INFO) & (B_BOOT_GUARD_SACM_INFO_MEASURED_BOOT | B_BOOT_GUARD_SACM_INFO_VERIFIED_BOOT);

    //
    // Stop PBET if Verified/Measured/NEM bit is set in MSR 0x13A or
    // Boot Guard fails to launch or fails to execute successfully for avoiding brick platform
    //

    if (BootGuardBootStatus == V_CPU_BOOT_GUARD_LOAD_ACM_SUCCESS) {
      if (BootGuardOperationMode == 0) {
        DEBUG ((DEBUG_INFO, "Platform is in Legacy boot mode.\n"));
        return EFI_UNSUPPORTED;
      } else {
        DEBUG ((DEBUG_INFO, "Platform in Boot Guard Boot mode.\n"));
      }
    } else {
      DEBUG ((DEBUG_ERROR, "Boot Guard ACM launch failed or ACM execution failed.\n"));
    }

    DEBUG ((DEBUG_INFO, "Disable PBET\n"));
    AsmWriteMsr64 (MSR_BC_PBEC, B_STOP_PBET);
  } else {
    DEBUG ((DEBUG_WARN, "Boot Guard is not supported.\n"));
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
  Return if C6DRAM is Enabled.

  @retval TRUE  - C6DRAM is enabled.
  @retval FALSE - C6DRAM is disabled.
**/
BOOLEAN
GetC6DramStatus (
  VOID
  )
{
  UINT32       MailboxStatus;
  UINT32       MailboxData;
  EFI_STATUS   Status;

  ///
  /// If C6DRAM is enabled, PCODE mailbox returns mailbox data bit 0 = 1.
  ///
  Status = MailboxRead (MAILBOX_TYPE_PCODE, MAILBOX_BIOS_CMD_READ_C6DRAM_CONFIG, &MailboxData, &MailboxStatus);
  if (Status != EFI_SUCCESS || MailboxStatus != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "Mailbox write command failed unexpectedly, C6DRAM is not supported. MailboxStatus = %x, Mailbox command return status %r \n", MailboxStatus, Status));
    return FALSE;
  }

  return (MailboxData & B_MAILBOX_BIOS_ALLOW_C6DRAM) == B_MAILBOX_BIOS_ALLOW_C6DRAM;
}

/**
  Set C6DRAM Enable/Disable and return if enabled or not.

  @param[in] C6DramStateRequest - Policy setting of C6DRAM

  @retval TRUE  - C6DRAM is enabled.
  @retval FALSE - C6DRAM is disabled.
**/
BOOLEAN
SetC6Dram (
  UINT32 C6DramStateRequest
  )
{
  UINT32     MailboxStatus;
  EFI_STATUS Status;

  Status = MailboxWrite (MAILBOX_TYPE_PCODE, MAILBOX_BIOS_CMD_WRITE_C6DRAM_CONFIG, C6DramStateRequest, &MailboxStatus);
  if (Status != EFI_SUCCESS || MailboxStatus != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "Mailbox write command failed, C6DRAM is not supported. MailboxStatus = %x, Mailbox command return status %x \n", MailboxStatus, Status));
    return FALSE;
  }

  return GetC6DramStatus ();
}

/**
  Check on the processor if PRM is supported.

  @param[in] Bsp             - Is current thread BSP

  @retval TRUE  if PRM supported
  @retval FALSE if PRM is not supported
**/
BOOLEAN
IsPrmrrSupported (
  BOOLEAN    IsBspInt
  )
{
  ///
  /// PRMRR configuration enabled, MSR IA32_MTRRCAP (FEh) [12] == 1
  ///
  if ((AsmReadMsr64 (MSR_IA32_MTRRCAP) & BIT12) != 0) {
    return TRUE;
  }
  //
  // Continue patch load without PRMRR initialization.
  // Patch load will be successful only if this is not SGX patch
  //
  if (IsBspInt) {
    DEBUG ((DEBUG_INFO, "PRMRR configuration not supported.\n"));
  }
  return FALSE;
}

VOID
SetCorePrmrr (
  UINT64 PrmrrBase,
  UINT32 PrmrrSize
  )
{
  UINT8              PhysicalAddressBits;
  UINT64             ValidPrmrrBitsMask;
  UINT64             PrmrrMask;
  EFI_CPUID_REGISTER Cpuid;
  BOOLEAN            IsBspInt;

  IsBspInt = IsBsp ();

  if (!IsPrmrrSupported (IsBspInt) || IsSecondaryThread ()) {
    return;
  }

  ///
  /// If PRMRR size is 0, only need to set bit lock on MSR 0x1f5
  ///
  if (PrmrrSize == 0) {
    if (!(AsmReadMsr64 (MSR_PRMRR_MASK) & B_MSR_PRMRR_MASK_L_MASK)) {

      ///
      /// Need to lock mask MSRs even if PRMRR size is zero
      ///
      if (IsBspInt) {
        DEBUG ((DEBUG_INFO, "PRMRR size is zero, only Locking PRMRR MASK MSR\n"));
      }
      AsmWriteMsr64 (MSR_PRMRR_MASK, B_MSR_PRMRR_MASK_L_MASK);
    }
  } else {

    ///
    /// Check returned value of Eax for extended CPUID functions
    ///
    AsmCpuid (
      CPUID_EXTENDED_FUNCTION,
      &Cpuid.RegEax,
      &Cpuid.RegEbx,
      &Cpuid.RegEcx,
      &Cpuid.RegEdx
      );
    PhysicalAddressBits = 36;

    ///
    /// If CPU supports extended functions, get the Physical Address size by reading EAX[7:0]
    ///
    if (Cpuid.RegEax > CPUID_EXTENDED_FUNCTION) {

      AsmCpuid (
        CPUID_VIR_PHY_ADDRESS_SIZE,
        &Cpuid.RegEax,
        &Cpuid.RegEbx,
        &Cpuid.RegEcx,
        &Cpuid.RegEdx);

      PhysicalAddressBits = (UINT8) Cpuid.RegEax;
    }

    ValidPrmrrBitsMask    = (LShiftU64 (1,PhysicalAddressBits) - 1) & 0xfffffffffffff000;
    PrmrrMask = ValidPrmrrBitsMask & (~((UINT64) (PrmrrSize - 1)));
    ///
    /// Set the PRMRR Base MSR with base, memory type, and configured status.Set PRMRR Mask MSR with the mask and lock bit.
    /// The valid bit on PRMRR Mask MSR will be set later by the microcode.
    ///
    if (!(AsmReadMsr64 (MSR_PRMRR_MASK) & B_MSR_PRMRR_MASK_L_MASK)) {
      AsmWriteMsr64 (MSR_PRMRR_BASE_0, PrmrrBase | CACHE_WRITEBACK | B_MSR_PRMRR_BASE_0_CONFIGURED_MASK);
      AsmWriteMsr64 (MSR_PRMRR_MASK, PrmrrMask | B_MSR_PRMRR_MASK_L_MASK );
    }
  }
}

/**
  Return TRUE if PRMRR base was already set on this core

  @dot
    digraph G {
      subgraph cluster_c0 {
        node [shape = box];
          b1[label="Return TRUE" fontsize=12 style=filled color=lightblue];
          b2[label="Return FALSE" fontsize=12 style=filled color=lightblue];

        node [shape = ellipse];
          e1[label="Start" fontsize=12 style=filled color=lightblue];
          e2[label="End" fontsize=12 style=filled color=lightblue];

        node [shape = diamond,style=filled,color=lightblue];
          d1[label="Are MSR_PRMRR_BASE_0 and\n B_MSR_PRMRR_MASK_L_MASK\n not equal to zero" fontsize=13];

        label = "IsPrmrrAlreadySet Flow"; fontsize=15; fontcolor=black; color=lightblue;
        e1 -> d1
        d1 -> b1 [label="Yes" fontsize=9]
        d1 -> b2 [label="No" fontsize=9]
        b1 -> e2
        b2 -> e2

      }
    }
  @enddot

  @retval TRUE  PRMRR base was already set
  @retval FALSE PRMRR base wasn't set
**/
BOOLEAN
IsPrmrrAlreadySet (
  VOID
  )
{
  if ((AsmReadMsr64 (MSR_PRMRR_BASE_0) != 0) && ((AsmReadMsr64 (MSR_PRMRR_MASK) & B_MSR_PRMRR_MASK_L_MASK) != 0)) {
    return TRUE;
  }
  return FALSE;
}


/**
  Enable AC# on Split Lock feature.
**/
VOID
EnableAcOnSplitLock (
  VOID
  )
{
  UINT64 MsrValue;

  MsrValue = AsmReadMsr64 (MSR_MEMORY_CONTROL);
  AsmWriteMsr64 (MSR_MEMORY_CONTROL, B_MSR_MEMORY_CONTROL_SPLIT_LOCK_DISABLE_MASK | MsrValue);
}

/**
  This function returns Number of CBO0 Bank Index.

  @retval CBO0 Bank Index.
**/
UINT8
GetCbo0BankIndex (
  VOID
  )
{
  CPU_GENERATION CpuGeneration;
  UINT8          Cbo0Index;

  //
  // Get CBO0 Bank Index.
  //
  CpuGeneration = GetCpuGeneration ();
  if(CpuGeneration == EnumTglCpu) {
    Cbo0Index = 8;
  } else if (CpuGeneration == EnumIclCpu || CpuGeneration == EnumRklCpu) {
    Cbo0Index = 7;
  } else {
    Cbo0Index = 6;
  }

  return (UINT8) Cbo0Index;
}