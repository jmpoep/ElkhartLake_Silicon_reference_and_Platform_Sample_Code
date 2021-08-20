/** @file
  This file provides services for Sample PEI MEMORY_CONFIG_NO_CRC Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#include <SaPolicyCommon.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MmPciLib.h>
#include <Library/MemoryAllocationLib.h>
#include "MrcOemPlatform.h"
#include <Library/GpioLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/RngLib.h>
#include <Library/CpuMailboxLib.h>

const UINT8 mDqsMapCpu2DramTglRvp[2][4][2] =  {
  // Ch 0      1      2      3
     {{0,1}, {0,1}, {0,1}, {0,1}}, // Controller 0
     {{0,1}, {0,1}, {0,1}, {0,1}}  // Controller 1
};

const UINT8 mDqMapCpu2DramTglRvp[8][2][8] =  {
  //Controller 0
  {{  0,  1,  2,  3,  4,  5,  6,  7 },   // Byte 0
   {  8,  9, 10, 11, 12, 13, 14, 15 }},  // Byte 1
  {{  0,  1,  2,  3,  4,  5,  6,  7 },   // Byte 2
   {  8,  9, 10, 11, 12, 13, 14, 15 }},  // Byte 3
  {{  0,  1,  2,  3,  4,  5,  6,  7 },   // Byte 4
   {  8,  9, 10, 11, 12, 13, 14, 15 }},  // Byte 5
  {{  0,  1,  2,  3,  4,  5,  6,  7 },   // Byte 6
   {  8,  9, 10, 11, 12, 13, 14, 15 }},  // Byte 7
  //Controller 1
  {{  0,  1,  2,  3,  4,  5,  6,  7 },   // Byte 0
   {  8,  9, 10, 11, 12, 13, 14, 15 }},  // Byte 1
  {{  0,  1,  2,  3,  4,  5,  6,  7 },   // Byte 2
   {  8,  9, 10, 11, 12, 13, 14, 15 }},  // Byte 3
  {{  0,  1,  2,  3,  4,  5,  6,  7 },   // Byte 4
   {  8,  9, 10, 11, 12, 13, 14, 15 }},  // Byte 5
  {{  0,  1,  2,  3,  4,  5,  6,  7 },   // Byte 6
   {  8,  9, 10, 11, 12, 13, 14, 15 }}   // Byte 7
};


// LPDDR4 200b 8Gb die, DDP
// Samsung K4U6E304AC-MGCJ
// Hynix
// Micron
// 3200, 28-29-29-68
// 2 ranks per channel, 2 SDRAMs per rank, 4x8Gb = 4GB total per channel
const UINT8 mLpddr4xDdp8Gb200bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x10,                                 ///< 1   SPD Revision 1.0
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5   15 Rows, 10 Columns
  0x95,                                 ///< 6   Non-Monolithic DRAM Device, 2 die, 2 Channels per package, Signal Loading Matrix 1
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x0A,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x22,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x48,                                 ///< 16  Signal Loading: Data/Strobe/Mask: 2 loads, CAC: 2 loads, CS: 1 load
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x05,                                 ///< 18  tCKAVGmin = 0.625 ns (LPDDR4-3200)
  0xFF,                                 ///< 19  tCKAVGmax = 32.002 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x55,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20, 16
  0x00,                                 ///< 22  CAS Latencies supported (Third Byte) :
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8C,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.5 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xA0,                                 ///< 29  tRFCab = 180 ns (8 Gb)
  0x05,                                 ///< 30  tRFCab MSB
  0xD0,                                 ///< 31  tRFCpb = 90 ns (8 Gb)
  0x02,                                 ///< 32  tRFCpb MSB
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 FTB for Row precharge time per bank (tRPpb) = 18 ns
  0x00,                                 ///< 121 FTB for Row precharge time for all banks (tRPab) = 21 ns
  0x00,                                 ///< 122 FTB for Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0x00,                                 ///< 123 FTB for tAAmin = 17.5 ns
  0x7F,                                 ///< 124 FTB for tCKAVGmax = 32.002 ns
  0x00,                                 ///< 125 FTB for tCKAVGmin = 0.625 ns (LPDDR4-3200)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x55,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};

/**
  SaLoadSamplePolicyPreMem - Load some policy default for reference board.

  @param[in] ConfigBlockTableAddress    The pointer for SA config blocks

**/
VOID
SaLoadSamplePolicyPreMem (
  IN VOID           *ConfigBlockTableAddress
  )
{
  SA_FUNCTION_CALLS     *MemCall;
  EFI_STATUS            Status;
  MEMORY_CONFIG_NO_CRC  *MemConfigNoCrc;
  UINT32                Controller;
  UINT32                Channel;

  MemConfigNoCrc = NULL;
  Status = GetConfigBlock (ConfigBlockTableAddress, &gMemoryConfigNoCrcGuid, (VOID *) &MemConfigNoCrc);
  ASSERT_EFI_ERROR (Status);
  if (MemConfigNoCrc == NULL) {
    return;
  }

  DEBUG ((DEBUG_INFO, "Applying Sample policy defaults for LPDDR4\n"));
  MemCall                       = &MemConfigNoCrc->SaCall;
  MemCall->IoRead8              = &IoRead8;
  MemCall->IoRead16             = &IoRead16;
  MemCall->IoRead32             = &IoRead32;
  MemCall->IoWrite8             = &IoWrite8;
  MemCall->IoWrite16            = &IoWrite16;
  MemCall->IoWrite32            = &IoWrite32;
  MemCall->MmioRead8            = &MmioRead8;
  MemCall->MmioRead16           = &MmioRead16;
  MemCall->MmioRead32           = &MmioRead32;
  MemCall->MmioRead64           = &SaMmioRead64;
  MemCall->MmioWrite8           = &MmioWrite8;
  MemCall->MmioWrite16          = &MmioWrite16;
  MemCall->MmioWrite32          = &MmioWrite32;
  MemCall->MmioWrite64          = &SaMmioWrite64;
  MemCall->SmbusRead8           = &SmBusReadDataByte;
  MemCall->SmbusRead16          = &SmBusReadDataWord;
  MemCall->SmbusWrite8          = &SmBusWriteDataByte;
  MemCall->SmbusWrite16         = &SmBusWriteDataWord;
  MemCall->GetPciDeviceAddress  = &GetPciDeviceAddress;
  MemCall->GetPcieDeviceAddress = &GetPcieDeviceAddress;
  MemCall->GetRtcTime           = &GetRtcTime;
  MemCall->GetCpuTime           = &GetCpuTime;
  MemCall->CopyMem              = &CopyMem;
  MemCall->SetMem               = &SetMem;
  MemCall->SetMemWord           = &SetMemWord;
  MemCall->SetMemDword          = &SetMemDword;
  MemCall->LeftShift64          = &LShiftU64;
  MemCall->RightShift64         = &RShiftU64;
  MemCall->MultU64x32           = &MultU64x32;
  MemCall->DivU64x64            = &DivU64x64Remainder;
  MemCall->GetSpdData           = &GetSpdData;
  MemCall->GetRandomNumber      = &GetRandomNumber32;
  MemCall->CpuMailboxRead       = &MailboxRead;
  MemCall->CpuMailboxWrite      = &MailboxWrite;
  MemCall->GetMemoryVdd         = &GetMemoryVdd;
  MemCall->SetMemoryVdd         = &SetMemoryVdd;
  MemCall->CheckPoint           = &CheckPoint;
  MemCall->DebugHook            = &DebugHook;
  MemCall->DebugPrint           = &SaDebugPrint;
  MemCall->GetRtcCmos           = &PeiRtcRead;
  MemCall->ReadMsr64            = &AsmReadMsr64;
  MemCall->WriteMsr64           = &AsmWriteMsr64;
  MemCall->MrcReturnFromSmc     = &ReturnFromSmc;
  MemCall->MrcDramReset         = &SaDramReset;
  MemCall->MrcDelayNs           = &DelayNs;

  for (Controller = 0; Controller < MEM_CFG_MAX_CONTROLLERS; Controller++) {
    for (Channel = 0; Channel < MEM_CFG_MAX_CHANNELS; Channel++) {
      // Setting the configuration for full population of LPDDR4, which only has 1 DIMM
      CopyMem ((VOID *) MemConfigNoCrc->SpdData->SpdData[Controller][Channel][0], mLpddr4xDdp8Gb200bSpd, sizeof (mLpddr4xDdp8Gb200bSpd));
    }
  }
  CopyMem ((VOID *) MemConfigNoCrc->DqDqsMap->DqsMapCpu2Dram, mDqsMapCpu2DramTglRvp, sizeof (UINT8) * MEM_CFG_MAX_CONTROLLERS * MEM_CFG_MAX_CHANNELS * MEM_CFG_NUM_BYTES_MAPPED);
  CopyMem ((VOID *) MemConfigNoCrc->DqDqsMap->DqMapCpu2Dram, mDqMapCpu2DramTglRvp, sizeof (UINT8) * MEM_CFG_MAX_CONTROLLERS * MEM_CFG_MAX_CHANNELS * MEM_CFG_NUM_BYTES_MAPPED * 8);
}
