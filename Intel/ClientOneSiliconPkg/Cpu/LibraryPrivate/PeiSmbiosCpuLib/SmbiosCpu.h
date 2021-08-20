/** @file
  Header file for SMBIOS related functions.

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

#ifndef _SMBIOS_CPU_H_
#define _SMBIOS_CPU_H_

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/HobLib.h>
#include <Library/CpuPlatformLib.h>
#include <SmbiosCacheInfoHob.h>
#include <SmbiosProcessorInfoHob.h>
#include <IndustryStandard/SmBios.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuAccess.h>
#include <Library/CpuCommonLib.h>

///
/// Non-static SMBIOS table data to be filled later with a dynamically generated value
///
#define TO_BE_FILLED  0
#define TO_BE_FILLED_STRING  " "        ///< Initial value should not be NULL

///
/// String references in SMBIOS tables. This eliminates the need for pointers. See spec for details.
///
#define NO_STRING_AVAILABLE  0
#define STRING_1  1
#define STRING_2  2
#define STRING_3  3
#define STRING_4  4
#define STRING_5  5
#define STRING_6  6
#define STRING_7  7

#define BRAND_STRING_UNSUPPORTED  "CPU Brand String Not Supported"
#define INTEL_CORPORATION_STRING  "Intel(R) Corporation"

///
/// This constant defines the maximum length of the CPU brand string. According to the
/// IA manual, the brand string is in EAX through EDX (thus 16 bytes) after executing
/// the CPUID instructions with EAX as 80000002, 80000003, 80000004.
///
#define MAXIMUM_CPU_BRAND_STRING_LENGTH 48

///
/// This constant defines the maximum size of any SMBIOS string provided by this library, including terminating null character.
///
#define MAXIMUM_SIZE_OF_CPU_SMBIOS_STRING 200

#define MAX_NUMBER_OF_CACHE_LEVELS 4

///
/// SMBIOS Table values with special meaning
///
#define SMBIOS_TYPE4_64BIT_CAPABLE            BIT2
#define SMBIOS_TYPE4_MULTI_CORE               BIT3
#define SMBIOS_TYPE4_HARDWARE_THREAD          BIT4
#define SMBIOS_TYPE4_EXECUTE_PROTECTION       BIT5
#define SMBIOS_TYPE4_ENHANCED_VIRTUALIZATION  BIT6
#define SMBIOS_TYPE4_POWER_PERF_CONTROL       BIT7

#define SMBIOS_TYPE7_SRAM_SYNCHRONOUS         BIT5

#pragma pack(1)
typedef struct {
  CHAR8 *ProcessorManufacturer;
  CHAR8 *ProcessorVersion;
} SMBIOS_PROCESSOR_INFO_STRING_ARRAY;
#define SMBIOS_PROCESSOR_INFO_NUMBER_OF_STRINGS  2

typedef struct {
  CHAR8 *SocketDesignation;
} SMBIOS_CACHE_INFO_STRING_ARRAY;
#define SMBIOS_CACHE_INFO_NUMBER_OF_STRINGS  1
#pragma pack()

typedef enum {
  CpuStatusUnknown        = 0,
  CpuStatusEnabled        = 1,
  CpuStatusDisabledByUser = 2,
  CpuStatusDisabledbyBios = 3,
  CpuStatusIdle           = 4,
  CpuStatusOther          = 7
} SMBIOS_TYPE4_CPU_STATUS;

typedef struct {
  UINT8      CpuStatus       :3;
  UINT8      Reserved1       :3;
  UINT8      SocketPopulated :1;
  UINT8      Reserved2       :1;
} PROCESSOR_STATUS_DATA;

typedef struct {
  UINT16  Level           :3;
  UINT16  Socketed        :1;
  UINT16  Reserved1       :1;
  UINT16  Location        :2;
  UINT16  Enable          :1;
  UINT16  OperationalMode :2;
  UINT16  Reserved2       :6;
} SMBIOS_TYPE7_CACHE_CONFIGURATION_DATA;

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
  );

/**
  This function produces an SMBIOS Processor Info HOB.

  @param[in] TotalNumberOfSockets - The total number of sockets detected on the system.
  @param[in] CurrentSocketNumber  - The processor socket number corresponding to the Processor Info HOB to produce.
**/
VOID
InitializeSmbiosProcessorInfoHob (
  IN  UINT16         TotalNumberOfSockets,
  IN  UINT16         CurrentSocketNumber
  );

/**
  This function produces SMBIOS Cache Info HOBs.

  @param[in] ProcessorSocketNumber - The processor socket number corresponding to the Cache Info HOBs to produce.
**/
VOID
InitializeSmbiosCacheInfoHobs (
  IN  UINT16        ProcessorSocketNumber
  );

#endif
