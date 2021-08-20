/** @file
  Data for SMBIOS Cache tables (Type 7).

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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
/// Cache Information (Type 7)
///
GLOBAL_REMOVE_IF_UNREFERENCED SMBIOS_CACHE_INFO SmbiosCacheInfoData = {
  TO_BE_FILLED,                  ///< ProcessorSocketNumber
  TO_BE_FILLED,                  ///< NumberOfCacheLevels
  STRING_1,                      ///< SocketDesignationStrIndex
  TO_BE_FILLED,                  ///< CacheConfiguration
  TO_BE_FILLED,                  ///< MaxCacheSize
  TO_BE_FILLED,                  ///< InstalledSize
  SMBIOS_TYPE7_SRAM_SYNCHRONOUS, ///< SupportedSramType
  SMBIOS_TYPE7_SRAM_SYNCHRONOUS, ///< CurrentSramType
  0,                             ///< CacheSpeed
  TO_BE_FILLED,                  ///< ErrorCorrectionType
  TO_BE_FILLED,                  ///< SystemCacheType
  TO_BE_FILLED,                  ///< Associativity
};
GLOBAL_REMOVE_IF_UNREFERENCED SMBIOS_CACHE_INFO_STRING_ARRAY SmbiosCacheInfoStrings = {
  TO_BE_FILLED_STRING, ///< SocketDesignation
};

///
/// Convert Cache Type Field to SMBIOS format
///
#define SMBIOS_CACHE_TYPE_MAX 5
GLOBAL_REMOVE_IF_UNREFERENCED UINT8 SmbiosCacheTypeFieldConverter[SMBIOS_CACHE_TYPE_MAX] = {
  CacheTypeUnknown,
  CacheTypeData,
  CacheTypeInstruction,
  CacheTypeUnified,
  CacheTypeOther
};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *CacheStrings[] = {
  "L1 Cache",
  "L2 Cache",
  "L3 Cache"
};
GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 UnknownString[] = "Unknown";


/**
  This function produces SMBIOS Cache Info HOBs.

  @param[in] ProcessorSocketNumber - The processor socket number corresponding to the Cache Info HOBs to produce.
**/
VOID
InitializeSmbiosCacheInfoHobs (
  IN  UINT16               ProcessorSocketNumber
  )
{
  UINT8                                 CacheIndex;
  CPUID_CACHE_PARAMS_EAX                Eax;
  CPUID_CACHE_PARAMS_EBX                Ebx;
  UINT32                                RegEcx;
  UINT8                                 CacheLevel[MAX_NUMBER_OF_CACHE_LEVELS];
  UINT8                                 LxCacheType[MAX_NUMBER_OF_CACHE_LEVELS];
  UINT32                                Ways[MAX_NUMBER_OF_CACHE_LEVELS];
  UINT32                                Partitions;
  UINT32                                LineSets;
  UINT32                                Sets;
  UINT32                                MaxCacheSize[MAX_NUMBER_OF_CACHE_LEVELS];
  UINT16                                NumberOfCacheLevels;
  UINT16                                SupportedCores;
  UINT16                                EnabledCores;
  BOOLEAN                               CombineL1DataAndInstruction;
  UINT8                                 Index;
  SMBIOS_TYPE7_CACHE_CONFIGURATION_DATA CacheConfig;

  DEBUG ((DEBUG_INFO, "InitializeSmbiosCacheInfoHobs() - Start\n"));

  for (CacheIndex = 0; CacheIndex < MAX_NUMBER_OF_CACHE_LEVELS; CacheIndex++) {
    CacheLevel[CacheIndex] = 0;
    LxCacheType[CacheIndex] = 0;
    Ways[CacheIndex] = 0;
    MaxCacheSize[CacheIndex] = 0;
  }

  NumberOfCacheLevels = 0;

  ///
  /// Find the total number of cache levels reported via CPUID instruction.
  /// Save the CPUID output for later use.
  ///
  for (CacheIndex = 0;; CacheIndex++) {
    AsmCpuidEx (CPUID_CACHE_PARAMS, CacheIndex, &Eax.Uint32, &Ebx.Uint32, &RegEcx, NULL);
    if (Eax.Bits.CacheType == 0) {
      break;
    }

    NumberOfCacheLevels++;
    if (NumberOfCacheLevels > MAX_NUMBER_OF_CACHE_LEVELS) {
      DEBUG ((DEBUG_ERROR, "Error producing Cache Info HOBs. Total number of reported cache levels exceeded limit.\n"));
      break;
    }

    CacheLevel[CacheIndex]  = (UINT8) Eax.Bits.CacheLevel;
    LxCacheType[CacheIndex] = (UINT8) Eax.Bits.CacheType;

    Ways[CacheIndex]        = Ebx.Bits.Ways + 1;
    Partitions              = Ebx.Bits.LinePartitions + 1;
    LineSets                = Ebx.Bits.LineSize + 1;
    Sets                    = RegEcx + 1;

    MaxCacheSize[CacheIndex] = (Ways[CacheIndex] * Partitions * LineSets * Sets) / 1024;
  }

  ///
  /// Determine the number of supported and active cores for L1/L2 total cache size.
  ///
  GetSupportedCount (NULL, &SupportedCores);
  GetEnabledCount (NULL, &EnabledCores, NULL, NULL);

  ///
  /// Check if L1 Data cache and L1 instruction cache can be combined.
  ///
  CombineL1DataAndInstruction = FALSE;
  if (NumberOfCacheLevels == 4) {
    if ((CacheLevel[0] == 1) && (CacheLevel[1] == 1) && (Ways[0] == Ways[1]) && (MaxCacheSize[0] == MaxCacheSize[1])) {
      ///
      /// If one is Data cache, and the other is Instruction cache.
      ///
      if (((LxCacheType[0] == 1) && (LxCacheType[1] == 2)) || ((LxCacheType[0] == 2) && (LxCacheType[1] == 1))) {
        CombineL1DataAndInstruction = TRUE;
        LxCacheType[1] = 3; //Unified
        MaxCacheSize[1] = MaxCacheSize[0] + MaxCacheSize[1];
        NumberOfCacheLevels = 3;
      }
    }
  }

  SmbiosCacheInfoData.ProcessorSocketNumber = ProcessorSocketNumber;
  SmbiosCacheInfoData.NumberOfCacheLevels = NumberOfCacheLevels;

  for (CacheIndex = 0; CacheIndex < NumberOfCacheLevels; CacheIndex++) {
    Index = CacheIndex;
    if (CombineL1DataAndInstruction == TRUE) {
      Index = CacheIndex + 1;
    }

    ///
    /// Index can never be >= MAX_NUMBER_OF_CACHE_LEVELS
    ///
    if (Index >= MAX_NUMBER_OF_CACHE_LEVELS) {
      ASSERT (FALSE);
      return;
    }

    ///
    /// Make CacheLevel zero-based for indexing and for SMBIOS Cache Configuration format
    ///
    if (CacheLevel[Index] == 0) {
      ASSERT (FALSE);
      return;
    }
    CacheLevel[Index]--;

    if (CacheLevel[Index] < 3) {
      SmbiosCacheInfoStrings.SocketDesignation = CacheStrings[CacheLevel[Index]];
    } else {
      SmbiosCacheInfoStrings.SocketDesignation = (CHAR8 *) &UnknownString;
    }

    CacheConfig.Level = CacheLevel[Index];
    CacheConfig.Socketed = 0;           // Not Socketed
    CacheConfig.Reserved1 = 0;
    CacheConfig.Location = 0;           // Internal Cache
    CacheConfig.Enable = 1;             // Cache enabled
    CacheConfig.OperationalMode = 1;    // Write Back
    CacheConfig.Reserved2 = 0;
    SmbiosCacheInfoData.CacheConfiguration = *(UINT16 *) &CacheConfig;

    SmbiosCacheInfoData.MaxCacheSize = (UINT16) MaxCacheSize[Index];
    SmbiosCacheInfoData.InstalledSize = (UINT16) MaxCacheSize[Index];

    ///
    /// For L1 and L2 cache, multiply size by the number of cores.
    ///
    if (CacheLevel[Index] < 2) {
      SmbiosCacheInfoData.MaxCacheSize = SmbiosCacheInfoData.MaxCacheSize * SupportedCores;
      SmbiosCacheInfoData.InstalledSize = SmbiosCacheInfoData.InstalledSize * EnabledCores;
    }

    switch (CacheLevel[Index]) {
      case 0:
        SmbiosCacheInfoData.ErrorCorrectionType = CacheErrorParity;
        break;
      case 1:
        SmbiosCacheInfoData.ErrorCorrectionType = CacheErrorSingleBit;
        break;
      case 2:
        SmbiosCacheInfoData.ErrorCorrectionType = CacheErrorMultiBit;
        break;
      default:
        SmbiosCacheInfoData.ErrorCorrectionType = CacheErrorUnknown;
        break;
    }

    ///
    /// If cache type is larger or equal than 5, this is undefined type so mark it as "Other" Cache type.
    ///
    if (LxCacheType[Index] >= SMBIOS_CACHE_TYPE_MAX) {
      LxCacheType[Index] = SMBIOS_CACHE_TYPE_MAX - 1;
    }
    SmbiosCacheInfoData.SystemCacheType = SmbiosCacheTypeFieldConverter[LxCacheType[Index]];

    ///
    /// Convert Associativity Ways to SMBIOS format
    ///
    switch (Ways[Index]) {
      case 2:
        Ways[Index] = CacheAssociativity2Way;
        break;
      case 4:
        Ways[Index] = CacheAssociativity4Way;
        break;
      case 8:
        Ways[Index] = CacheAssociativity8Way;
        break;
      case 12:
        Ways[Index] = CacheAssociativity12Way;
        break;
      case 16:
        Ways[Index] = CacheAssociativity16Way;
        break;
      case 24:
        Ways[Index] = CacheAssociativity24Way;
        break;
      case 32:
        Ways[Index] = CacheAssociativity32Way;
        break;
      case 48:
        Ways[Index] = CacheAssociativity48Way;
        break;
      case 64:
        Ways[Index] = CacheAssociativity64Way;
        break;
      default:
        Ways[Index] = CacheAssociativityOther;
        break;
    }
    SmbiosCacheInfoData.Associativity = (UINT8) Ways[Index];

    AddSmbiosStringsAndBuildGuidDataHob (
      (VOID *) &SmbiosCacheInfoData,
      sizeof (SMBIOS_CACHE_INFO),
      (CHAR8 **) &SmbiosCacheInfoStrings,
      SMBIOS_CACHE_INFO_NUMBER_OF_STRINGS,
      &gSmbiosCacheInfoHobGuid
      );
  }

  DEBUG ((DEBUG_INFO, "InitializeSmbiosCacheInfoHobs() - End\n"));

  return;
}

