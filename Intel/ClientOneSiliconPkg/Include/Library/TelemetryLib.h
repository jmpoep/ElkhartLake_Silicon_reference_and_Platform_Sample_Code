/** @file
  Header file for TelemetryLib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 -2019 Intel Corporation.

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
#ifndef _TELEMETRY_LIB_H_
#define _TELEMETRY_LIB_H_

//
// Structure of DEVSC registers
//
typedef union {
  struct {
    UINT32  PcieCapId             : 16;       ///< PCI Express Capability ID
    UINT32  CapVer                : 4;        ///< Capability Version
    UINT32  NextCapOffset         : 12;       ///< Next Capability Offset
  } Fields;
  UINT32 Data;
} CAP_DATA;

typedef union {
  struct {
    UINT64  DevscVenId            : 16;       ///< DVSEC_VENID
    UINT64  DevscVer              : 4;        ///< DVSEC_VER
    UINT64  DevscLen              : 12;       ///< DVSEC_LEN
    UINT64  DevscId               : 16;       ///< DVSEC_ID
    UINT64  NumEntries            : 8;        ///< Number of entries, describes the number of telemetry aggregators that would exist in this capability lookup table.
    UINT64  EntrySize             : 8;        ///< Entry Size in DWORDS
  } Fields;
  UINT64 Data64;
  UINT32 Data32[2];
} DEVSC_DATA;

typedef union {
  struct {
    UINT32  TBir                  : 3;         ///< tBIR, The BAR to be used
    UINT32  DiscoveryTableOffset  : 29;        ///< Discovery Table Offset
  } Fields;
  UINT32 Data;
} DISCOVERY_DATA;

typedef struct {
  CAP_DATA        CapData;
  DEVSC_DATA      DevscData;
  DISCOVERY_DATA  DiscoveryData;
} TEL_CRASHLOG_DEVSC_CAP;

//
// Structure of Cpu CrashLog Header
//
typedef union {
  struct {
    UINT64  AccessType        : 4;             ///< Access Type
    UINT64  CrashType         : 4;             ///< Crash Type
    UINT64  Count             : 8;
    UINT64  Reserved          : 16;
    UINT64  Guid              : 32;            ///< GLOBALLY_UNIQUE_ID
  } Fields;
  UINT64 HeaderData;
} CPU_CRASHLOG_HEADER;

//
// Structure of Cpu CrashLog Buffer
//
typedef union {
  struct {
    UINT32  DataBuffAddress;    ///< Base address within this BAR for the crashLog data buffer.
    UINT32  DataBuffSize;       ///< Number of dwords of data contained in the crashLog buffer.
  } Fields;
  UINT64 Data;
} CPU_CRASHLOG_BUFFER;

//
// Structure of Cpu CrashLog Struct
//
typedef struct {
  CPU_CRASHLOG_BUFFER  MainBuffer;
  CPU_CRASHLOG_BUFFER  TelemetryBuffer;
  CPU_CRASHLOG_BUFFER  TraceBuffer;
} CPU_CRASHLOG_STRUCT;

/**
  Find the address of Cpu CrashLog ID

  @param[out] CrashLogDevscCap     Pointer to structure of CrashLog DEVSC Data

  @retval EFI_UNSUPPORTED          Cpu CrashLog ID not found
  @retval EFI_SUCCESS              Cpu CrashLog ID found
**/
EFI_STATUS
GetCpuCrashLogCapability (
  OUT TEL_CRASHLOG_DEVSC_CAP  *CrashLogDevscCap
  );

/**
  This function returns the value of CPU CrashLog BAR.

  @param[in] CrashLogDevscCap     Structure of CrashLog DEVSC Data

  @retval BaseAddr                MMIO address of CrashLog BAR
**/
UINT32
GetCpuCrashLogBarAddress (
  IN TEL_CRASHLOG_DEVSC_CAP  CrashLogDevscCap
  );

/**
  This function clears cpu crash log

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_DEVICE_ERROR        Mailbox command failed with an error
  @retval EFI_TIMEOUT             Mailbox command did not complete
**/
EFI_STATUS
CpuCrashLogClear (
  VOID
  );

/**
  Get CPU CrashLog Header data

  @param[in]    BaseAddr              Pci configuration space MMIO address of CrashLog BAR
  @param[out]   *CrashLogHeaderBuff   Pointer to CrashLog Discovery Data
**/
VOID
GetCrashLogHeader (
  IN  UINT32                BaseAddr,
  OUT CPU_CRASHLOG_HEADER   *CrashLogHeaderBuff
  );

/**
  This function discovers CPU crashLog and gets the size of each

  @param[out] CrashLogStruct      Pointer to CrashLog Discovery Data

  @retval EFI_UNSUPPORTED         Cpu CrashLog is not supported
  @retval EFI_SUCCESS             Cpu CrashLog is supported
**/
EFI_STATUS
CpuCrashLogDiscovery (
  OUT  CPU_CRASHLOG_STRUCT    *CrashLogStruct
  );
#endif // _TELEMETRY_LIB_H_
