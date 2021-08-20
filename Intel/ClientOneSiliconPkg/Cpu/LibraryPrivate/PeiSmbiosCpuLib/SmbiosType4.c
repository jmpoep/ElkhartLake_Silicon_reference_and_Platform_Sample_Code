/** @file
  SMBIOS Processor Info HOB data.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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
  System Management BIOS (SMBIOS) Reference Specification v3.0.0
  dated 2015-Feb-12 (DSP0134)
  http://www.dmtf.org/sites/default/files/standards/documents/DSP0134_3.0.0.pdf
**/

#include "SmbiosCpu.h"

///
/// Processor Information (Type 4)
///
GLOBAL_REMOVE_IF_UNREFERENCED SMBIOS_PROCESSOR_INFO SmbiosProcessorInfoData = {
  TO_BE_FILLED,             ///< TotalNumberOfSockets
  TO_BE_FILLED,             ///< CurrentSocketNumber
  CentralProcessor,         ///< ProcessorType
  TO_BE_FILLED,             ///< ProcessorFamily
  STRING_1,                 ///< ProcessorManufacturerStrIndex
  TO_BE_FILLED,             ///< ProcessorId
  STRING_2,                 ///< ProcessorVersionStrIndex
  TO_BE_FILLED,             ///< Voltage
  100,                      ///< ExternalClockInMHz
  TO_BE_FILLED,             ///< CurrentSpeedInMHz
  TO_BE_FILLED,             ///< Status
  TO_BE_FILLED,             ///< ProcessorUpgrade
  TO_BE_FILLED,             ///< CoreCount
  TO_BE_FILLED,             ///< EnabledCoreCount
  TO_BE_FILLED,             ///< ThreadCount
  TO_BE_FILLED,             ///< ProcessorCharacteristics
};
GLOBAL_REMOVE_IF_UNREFERENCED SMBIOS_PROCESSOR_INFO_STRING_ARRAY SmbiosProcessorInfoStrings = {
  INTEL_CORPORATION_STRING, ///< ProcessorManufacturer
  TO_BE_FILLED_STRING,      ///< ProcessorVersion
};

typedef struct _PROCESSOR_FAMILY_FIELD {
  CHAR8  ProcessorFamily[48];
  UINT16 ProcessorEnum;
} PROCESSOR_FAMILY_FIELD;

GLOBAL_REMOVE_IF_UNREFERENCED PROCESSOR_FAMILY_FIELD ProcessorFamilyField[] = {
  { "Intel(R) Core(TM) i7",  ProcessorFamilyIntelCoreI7 },
  { "Intel(R) Core(TM) i5",  ProcessorFamilyIntelCoreI5 },
  { "Intel(R) Core(TM) i3",  ProcessorFamilyIntelCoreI3 },
  { "Intel(R) Core(TM) m3",  0x2D },                       ///< This will be part of the future SMBIOS specification. @todo Use enum from MdePkg when "ProcessorFamilyIntelCoreM3" is added.
  { "Intel(R) Core(TM) m5",  0x2E },                       ///< This will be part of the future SMBIOS specification. @todo Use enum from MdePkg when "ProcessorFamilyIntelCoreM5" is added.
  { "Intel(R) Core(TM) m7",  0x2F },                       ///< This will be part of the future SMBIOS specification. @todo Use enum from MdePkg when "ProcessorFamilyIntelCoreM7" is added.
  { "Intel(R) Core(TM) M",   ProcessorFamilyIntelCoreM },
  { "Intel(R) Pentium(R)",   ProcessorFamilyPentium },
  { "Intel(R) Celeron(R)",   ProcessorFamilyCeleron },
  { "Intel(R) Atom(TM)",     ProcessorFamilyIntelAtom },
  { "Intel(R) Xeon(R)",      ProcessorFamilyIntelXeon },
};


///
/// Processor-specific routines
///
/**
  Returns the processor family and processor version of the processor installed in the system.

  @param[out] Processor Version - Returns the procesor version string installed in the system

  @retval                       - The Processor Family enum value
**/
UINT16
GetProcessorFamilyAndVersion (
  OUT CHAR8 **ProcessorVersion
  )
{
  UINTN              Index;
  EFI_CPUID_REGISTER CpuExtendedSupport;
  EFI_CPUID_REGISTER CpuBrandString;
  UINT16             ProcessorFamily;

  ProcessorFamily = ProcessorFamilyOther;

  ///
  /// Get Brand string
  ///
  AsmCpuid (
    CPUID_EXTENDED_FUNCTION,
    &CpuExtendedSupport.RegEax,
    &CpuExtendedSupport.RegEbx,
    &CpuExtendedSupport.RegEcx,
    &CpuExtendedSupport.RegEdx
    );

  ///
  /// Check if Brand ID String is supported as per SDM Vol. 2A Chapter 3 Instruction Set Reference - CPUID
  ///
  if (CpuExtendedSupport.RegEax >= 0x80000004) {
    AsmCpuid (
      CPUID_BRAND_STRING1,
      &CpuBrandString.RegEax,
      &CpuBrandString.RegEbx,
      &CpuBrandString.RegEcx,
      &CpuBrandString.RegEdx
      );
    CopyMem ((VOID *)(UINTN)*ProcessorVersion, (VOID *)(UINTN) &CpuBrandString, 16);
    AsmCpuid (
      CPUID_BRAND_STRING2,
      &CpuBrandString.RegEax,
      &CpuBrandString.RegEbx,
      &CpuBrandString.RegEcx,
      &CpuBrandString.RegEdx
      );
    CopyMem ((VOID *)(UINTN)(*ProcessorVersion + 16), (VOID *)(UINTN) &CpuBrandString, 16);
    AsmCpuid (
      CPUID_BRAND_STRING3,
      &CpuBrandString.RegEax,
      &CpuBrandString.RegEbx,
      &CpuBrandString.RegEcx,
      &CpuBrandString.RegEdx
      );
    CopyMem ((VOID *)(UINTN)(*ProcessorVersion + 32), (VOID *)(UINTN) &CpuBrandString, 16);

    *(*ProcessorVersion + MAXIMUM_CPU_BRAND_STRING_LENGTH) = 0;

    ///
    /// Remove preceeding spaces
    ///
    while (**ProcessorVersion == 0x20) {
      (*ProcessorVersion) ++;
    }
  } else {
    *ProcessorVersion = NULL;
    return ProcessorFamily;
  }

  for (Index = 0; Index < sizeof (ProcessorFamilyField) / sizeof (PROCESSOR_FAMILY_FIELD); Index++) {
    if (AsciiStrnCmp (
          *ProcessorVersion,
          ProcessorFamilyField[Index].ProcessorFamily,
          (AsciiStrLen (ProcessorFamilyField[Index].ProcessorFamily))
          ) == 0) {
      ProcessorFamily = ProcessorFamilyField[Index].ProcessorEnum;
      break;
    }
  }
  return ProcessorFamily;
}

/**
  Returns the processor voltage of the processor installed in the system.

  @retval Processor Voltage
**/
UINT8
GetProcessorVoltage (
  VOID
  )
{
  UINT8  SmbiosVoltage;
  UINT64 MsrValue;

  SmbiosVoltage = 0;
  MsrValue = 0;

  ///
  /// Core voltage = (float) IA32_PERF_STS(47:32) * (float) 1/(2^13)
  ///
  MsrValue = AsmReadMsr64 (MSR_IA32_PERF_STATUS);
  MsrValue = RShiftU64 (MsrValue, 32);
  MsrValue &= 0x0FFFF;

  ///
  /// Convert to Volts multiplied by 10 for SMBIOS data, and set bit 7. See spec for details.
  ///
  MsrValue = MultU64x32 (MsrValue, 10);
  MsrValue = RShiftU64 (MsrValue, 13);
  SmbiosVoltage = (UINT8) (MsrValue | BIT7);
  return SmbiosVoltage;
}

/**
  Get processor status for socket base only

  @retval PROCESSOR_STATUS_DATA for socket base only
**/
UINT8
GetProcessorStatus (
  VOID
  )
{
  PROCESSOR_STATUS_DATA ProcessorStatus;

  ProcessorStatus.Reserved1 = 0;
  ProcessorStatus.Reserved2 = 0;
  ProcessorStatus.SocketPopulated = TRUE;

  ///
  /// For BSP, processor is always enabled.
  ///
  ProcessorStatus.CpuStatus = CpuStatusEnabled;

  return *(UINT8 *) &ProcessorStatus;
}

/**
  Returns the processor characteristics based on the processor's capabilities.

  @retval Processor Characteristics
**/
UINT16
GetProcessorCharacteristics (
  VOID
  )
{
  UINT16                     ProcessorCharacteristics;
  UINT32                     RegEax;
  CPUID_VERSION_INFO_ECX     VersionInfoEcx;
  CPUID_EXTENDED_CPU_SIG_EDX CpuSigEdx;
  UINT16                     ThreadsPerCore;
  UINT16                     SupportedCores;

  ProcessorCharacteristics = 0;

  ///
  /// Check 64-bit and Execute Protection
  ///
  AsmCpuid (CPUID_EXTENDED_FUNCTION, &RegEax, NULL, NULL, NULL);
  if (RegEax >= CPUID_EXTENDED_CPU_SIG) {
    AsmCpuid (CPUID_EXTENDED_CPU_SIG, NULL, NULL, NULL, &CpuSigEdx.Uint32);
    //
    // Check Intel 64-bit capable (EDX[29])
    //
    if (CpuSigEdx.Bits.LM == 1) {
      ProcessorCharacteristics |= SMBIOS_TYPE4_64BIT_CAPABLE;
    }

    //
    // Execute Protection
    //
    if (CpuSigEdx.Bits.NX == 1) {
      ProcessorCharacteristics |= SMBIOS_TYPE4_EXECUTE_PROTECTION;
    }
  }

  ///
  /// Multi-Core and HT capabilities
  ///
  GetSupportedCount (&ThreadsPerCore, &SupportedCores);
  if (SupportedCores > 1) {
    ProcessorCharacteristics |= SMBIOS_TYPE4_MULTI_CORE;
  }
  if (ThreadsPerCore > 1) {
    ProcessorCharacteristics |= SMBIOS_TYPE4_HARDWARE_THREAD;
  }

  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &VersionInfoEcx.Uint32, NULL);

  ///
  /// Enhanced Virtualization
  ///
  if (VersionInfoEcx.Bits.VMX == 1) {
    ProcessorCharacteristics |= SMBIOS_TYPE4_ENHANCED_VIRTUALIZATION;
  }

  ///
  /// Power/Performance Control
  ///
  if (VersionInfoEcx.Bits.EIST == 1) {
    ProcessorCharacteristics |= SMBIOS_TYPE4_POWER_PERF_CONTROL;
  }

  return ProcessorCharacteristics;
}

/**
  Add SMBIOS strings to the end of the HOB, then call the BuildGuidDataHob function.
  Add each non-null string, plus the terminating (double) null.

  @param[in]  FixedDataRegion       The data for the fixed portion of the HOB.
  @param[in]  FixedRegionSize       The size of the fixed portion of the HOB.
  @param[in]  TableStrings          Set of string pointers to append onto the full record.
                                    If TableStrings is null, no strings are appended. Null strings
                                    are skipped.
  @param[in]  NumberOfStrings       Number of TableStrings to append, null strings are skipped.
  @param[in]  HobGuid               The GUID to pass to the BuildGuidDataHob function.
**/
VOID
AddSmbiosStringsAndBuildGuidDataHob (
  IN  VOID          *FixedDataRegion,
  IN  UINT8         FixedRegionSize,
  IN  CHAR8         **TableStrings,
  IN  UINT8         NumberOfStrings,
  IN  EFI_GUID      *HobGuid
  )
{
  CHAR8                   *StringPtr;
  UINTN                   Size;
  UINTN                   HobSize;
  UINTN                   CurrentStringSize;
  UINTN                   Index;
  VOID                    *HobData;

  Size = FixedRegionSize;

  ///
  /// Add the size of each non-null string
  ///
  if (TableStrings != NULL) {
    for (Index = 0; Index < NumberOfStrings; Index++) {
      if ((TableStrings[Index] != NULL) && (*TableStrings[Index] != '\0')) {
        Size += AsciiStrSize (TableStrings[Index]);
      }
    }
  }

  ///
  /// Add the size of the terminating double null
  /// If there were any strings added, just add the second null
  ///
  if (Size == FixedRegionSize) {
    Size += 2;
  } else {
    Size += 1;
  }
  HobSize = Size;

  ///
  /// Initialize the full record
  ///
  HobData = AllocateZeroPool (HobSize);
  if (HobData == NULL) {
    return;
  }
  CopyMem (HobData, FixedDataRegion, FixedRegionSize);

  ///
  /// Copy the strings to the end of the record
  ///
  StringPtr = ((CHAR8 *) HobData) + FixedRegionSize;
  if (TableStrings != NULL) {
    for (Index = 0; Index < NumberOfStrings; Index++) {
      if ((TableStrings[Index] != NULL) && (*TableStrings[Index] != '\0')) {
        AsciiStrnCpyS (StringPtr, MAXIMUM_SIZE_OF_CPU_SMBIOS_STRING, TableStrings[Index], Size - FixedRegionSize - 1);
        CurrentStringSize = AsciiStrSize (TableStrings[Index]);
        StringPtr += CurrentStringSize;
        Size -= CurrentStringSize;
      }
    }
  }

  BuildGuidDataHob (
    HobGuid,
    HobData,
    HobSize
    );

  return;
}

/**
  This function produces an SMBIOS Processor Info HOB.

  @param[in] TotalNumberOfSockets - The total number of sockets detected on the system.
  @param[in] CurrentSocketNumber  - The processor socket number corresponding to the Processor Info HOB to produce.
**/
VOID
InitializeSmbiosProcessorInfoHob (
  IN  UINT16         TotalNumberOfSockets,
  IN  UINT16         CurrentSocketNumber
  )
{
  CHAR8              BrandIdString[MAXIMUM_CPU_BRAND_STRING_LENGTH + 1];
  UINT16             SupportedCoreCount;
  PROCESSOR_ID_DATA  ProcessorId;
  CPU_SKU            CpuSku;

  DEBUG ((DEBUG_INFO, "InitializeSmbiosProcessorInfoHob() - Start\n"));

  SmbiosProcessorInfoData.TotalNumberOfSockets = TotalNumberOfSockets;
  SmbiosProcessorInfoData.CurrentSocketNumber = CurrentSocketNumber;

  SmbiosProcessorInfoStrings.ProcessorVersion = (CHAR8 *) &BrandIdString;

  SmbiosProcessorInfoData.ProcessorFamily = GetProcessorFamilyAndVersion (&SmbiosProcessorInfoStrings.ProcessorVersion);
  if (SmbiosProcessorInfoStrings.ProcessorVersion == NULL) {
    AsciiStrnCpyS ((CHAR8 *) &BrandIdString, MAXIMUM_CPU_BRAND_STRING_LENGTH + 1, (CHAR8 *) &BRAND_STRING_UNSUPPORTED, (sizeof (BrandIdString) / sizeof (CHAR8)) - 1);
    SmbiosProcessorInfoStrings.ProcessorVersion = (CHAR8 *) &BrandIdString;
  }

  AsmCpuid (CPUID_VERSION_INFO, (UINT32 *) &ProcessorId.Signature, NULL, NULL, (UINT32 *) &ProcessorId.FeatureFlags);
  SmbiosProcessorInfoData.ProcessorId = *(UINT64 *) &ProcessorId;

  SmbiosProcessorInfoData.Voltage = GetProcessorVoltage ();
  SmbiosProcessorInfoData.CurrentSpeedInMHz =
  (UINT16) (100 *
            (
              ((UINT32) AsmReadMsr64 (MSR_IA32_PERF_STATUS) >> N_IA32_PERF_STSP_STATE_TARGET)
              & B_IA32_PERF_STSP_STATE_MASK
              )
            );
  SmbiosProcessorInfoData.Status = GetProcessorStatus ();

  CpuSku = GetCpuSku ();
  switch (CpuSku) {
    case EnumCpuTrad:
      SmbiosProcessorInfoData.ProcessorUpgrade = ProcessorUpgradeOther; ///< @todo: set to value of ProcessorUpgradeSocketLGA1151, once it is assigned by DMTF
      break;

    case EnumCpuUlt:
      SmbiosProcessorInfoData.ProcessorUpgrade = ProcessorUpgradeOther; ///< @todo: set to value of ProcessorUpgradeSocketBGA1356, once it is assigned by DMTF
      break;

    case EnumCpuHalo:
      SmbiosProcessorInfoData.ProcessorUpgrade = ProcessorUpgradeOther; ///< @todo: set to value of ProcessorUpgradeSocketBGA1440, once it is assigned by DMTF
      break;

    case EnumCpuUlx:
      SmbiosProcessorInfoData.ProcessorUpgrade = ProcessorUpgradeOther; ///< @todo: set to value of ProcessorUpgradeSocketBGA1515, once it is assigned by DMTF
      break;

    default:
      SmbiosProcessorInfoData.ProcessorUpgrade = ProcessorUpgradeOther;
      break;
  }

  GetSupportedCount (NULL, &SupportedCoreCount);

  SmbiosProcessorInfoData.CoreCount = SupportedCoreCount;
  SmbiosProcessorInfoData.EnabledCoreCount = GetEnabledCoreCount ();
  SmbiosProcessorInfoData.ThreadCount = GetEnabledThreadCount ();

  SmbiosProcessorInfoData.ProcessorCharacteristics = GetProcessorCharacteristics ();

  AddSmbiosStringsAndBuildGuidDataHob (
    (VOID *) &SmbiosProcessorInfoData,
    sizeof (SMBIOS_PROCESSOR_INFO),
    (CHAR8 **) &SmbiosProcessorInfoStrings,
    SMBIOS_PROCESSOR_INFO_NUMBER_OF_STRINGS,
    &gSmbiosProcessorInfoHobGuid
    );

  //
  // ProcessorVersion pointer is no longer valid.
  //
  SmbiosProcessorInfoStrings.ProcessorVersion = NULL;

  DEBUG ((DEBUG_INFO, "InitializeSmbiosProcessorInfoHob() - End\n"));

  return;
}
