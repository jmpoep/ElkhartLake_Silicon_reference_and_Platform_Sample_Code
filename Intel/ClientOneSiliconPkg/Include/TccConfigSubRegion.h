/** @file
  TCC Config Sub Region Struct

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2019 - 2020 Intel Corporation.

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

@par Specification
**/

#ifndef _TCC_CONFIG_SUB_REGION_H_
#define _TCC_CONFIG_SUB_REGION_H_

#include <TccConfig.h>

#define PTCD_BIOS_FORMAT_VERSION  0x00000001
#define PTCD_TCC_FORMAT_VERSION   0x00000001
#define PTCD_REG_FORMAT_VERSION   0x00000001

#define PTCD_INVALID_ENTRY 0xFFFFFFFF

#define MAX_BUFFERS 8
#define MAX_STREAMS 8

#define TCC_REGISTERS_MAX 550

#pragma pack(1)

typedef struct {
  UINT8 Sstates;
  UINT8 Cstates;
  UINT8 Pstates;
  UINT8 Dstates;
  UINT8 CoreRapl;
  UINT8 MemoryRapl;
  UINT8 Turbo;
  UINT8 SaGv;
  UINT8 GtPm;
  UINT8 MemPm;
  UINT8 FabricPm;
  UINT8 GtRstRc6;
  UINT8 PcieAspm;
  UINT8 PcieClkGate;
  UINT8 PchPwrClkGate;
  UINT8 DmiAspm;
  UINT8 PcieRpL1;
  UINT8 HyperThreading;
  UINT8 FastGv;
  UINT8 VtdEn;
  UINT8 HwpEn;
  UINT8 DelayEnDmiAspm;
} BIOS_SETTINGS;

typedef struct {
  UINT32  FormatVersion;
  BIOS_SETTINGS BiosSettings;
} TCC_BIOS_POLICY_CONFIG;

typedef struct {
  UINT32 Valid;
  UINT32 SocketId;
  UINT32 ApicId;
  UINT32 BufferSize;
  UINT32 Latency;
  UINT64 ArithmeticIntensity;
  UINT8  BufferAllocType;
  UINT8  Behavior;
} BUFFER_CONFIGURATION;

typedef struct {
  UINT32 SocketId;
  UINT32 ApicId;
} CPU_CORE;

typedef struct {
  UINT32 DidVid;
} PCI_DEVICE;

typedef struct {
  UINT32 Latency;
} SYSTEM_MEMORY;

typedef enum {
  CPU_CORE_TYPE      = 0x00000001,
  PCI_DEVICE_TYPE    = 0x00000002,
  SYSTEM_MEMORY_TYPE = 0x00000003,
} STREAM_ENDPOINT_TYPE;

typedef struct {
  UINT32 EpType;
  union {
      CPU_CORE      CpuCore;
      PCI_DEVICE    PciDev;
      SYSTEM_MEMORY SystemMemory;
  } Info;
} STREAM_ENDPOINT;

typedef struct {
  UINT32          Valid;
  UINT32          Bandwidth;
  STREAM_ENDPOINT EpA;
  STREAM_ENDPOINT EpB;
} STREAM_CONFIGURATION;

typedef struct {
  UINT32 FormatVersion;
  BUFFER_CONFIGURATION Buffer[MAX_BUFFERS];
  STREAM_CONFIGURATION Streams[MAX_STREAMS];
} TCC_IO_CONFIG;

typedef enum {
  TCC_PRE_MEM_PHASE   = 0,
  TCC_POST_MEM_PHASE  = 1,
  TCC_LATE_INIT_PHASE = 2,
  TCC_PHASE_INVALID   = 0xFFFFFFFF
} TCC_REG_PHASE;

typedef enum {
  MMIO32          = 0,
  MMIO64          = 1,
  MSR             = 2,
  IOSFSB          = 3,
  MAILBOX         = 4,
  TCC_REG_INVALID = 0xFFFFFFFF
} TCC_REG_TYPE;

typedef enum {
  SABOX   = 0,
  MSRBOX  = 1
} MAILBOX_TARGET;

typedef struct {
  UINT32 U32Base; /* ECAM format B:D:F:R of BAR */
  UINT32 U32Addr; /* offset from BAR */
  UINT32 U32Mask; /* data bit-mask */
  UINT32 U32Data; /* data value */
} MMIO32_INFO;

typedef struct {
  union {
    UINT64 U64Value;
    UINTN  Value;
  } Base;         /* ECAM format B:D:F:R of BAR */
  union {
    UINT64 U64Value;
    UINTN  Value;
  } Addr;         /* offset from BAR */
  UINT64 U64Mask; /* data bit-mask */
  UINT64 U64Data; /* data value */
} MMIO64_INFO;

typedef struct {
  UINT32 U32Addr; /* ECX value */
  UINT64 U64Mask; /* EDX:EAX data bit-mask */
  UINT64 U64Data; /* EDX:EAX data value */
} MSR_INFO;

typedef struct {
  UINT8  Port;       /* IOSFSB Port ID */
  UINT8  IosfSbType; /* IOSFSB Register Type (command) */
  UINT32 U32Addr;    /* register address */
  UINT32 U32Mask;    /* data bit-mask */
  UINT32 U32Data;    /* data value */
} IOSFSB_INFO;

typedef struct {
  MAILBOX_TARGET MailboxType; /* Mailbox Register Type */
  UINT32         U32Cmd;      /* register address */
  UINT32         U32Mask;     /* data bit-mask */
  UINT32         U32Data;     /* data value */
} MAILBOX_INFO;

typedef struct
{
  UINT32  TccRegPhase;
  UINT32  TccRegType;
  union {
      MMIO32_INFO  Mmio32;
      MMIO64_INFO  Mmio64;
      MSR_INFO     Msr;
      IOSFSB_INFO  IosfSb;
      MAILBOX_INFO Mailbox;
  } Info;
} TCC_REGISTER;

typedef struct
{
  UINT32       FormatVersion;
  TCC_REGISTER TccRegisters[TCC_REGISTERS_MAX];
} TCC_REG_CONFIG;

typedef struct {
  UINT32                  FormatVersion;
  TCC_BIOS_POLICY_CONFIG  BiosConfig;       // TCC BIOS Settings
  TCC_IO_CONFIG           TccIoConfig;      // TCC Configuration
  TCC_REG_CONFIG          TccRegConfig;     // TCC Tuning Register
} PLATFORM_TUNING_CONFIG_DATA;

typedef union {
  PLATFORM_TUNING_CONFIG_DATA Config;
} TCC_CONFIG_SUB_REGION;

#pragma pack()

#endif
