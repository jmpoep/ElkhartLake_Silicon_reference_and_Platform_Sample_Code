/** @file
  SPD tables for TGL boards.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

// LPDDR4 200b 8Gb die, DDP, 2 channels per die, x16
// Samsung K4F6E304Hx-MGCJ
// or Hynix H9HCNNNBUUxLHR-NMx
// or Micron MT53B512M32D2NP-053
// 3733, 32-34-34-79
// 2 ranks per channel, 2 SDRAMs per channel, 2x2x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4Ddp8Gb200bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x10,                                 ///< 2   DRAM Type: LPDDR4 SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5   15 Row bits, 10 Column bits
  0x94,                                 ///< 6   Non-Monolithic DRAM Device, 2 dies, 2 Channels per die, Signal Loading not specified
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x0A,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x22,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x00,                                 ///< 16  Signal Loading: not specified
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x05,                                 ///< 18  tCKAVGmin = 0.536 ns (LPDDR4-3733)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x01,                                 ///< 22  CAS Latencies supported (Third Byte) : 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8A,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.14 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xA0,                                 ///< 29  tRFCab = 180 ns (8 Gb dual-channel die)
  0x05,                                 ///< 30  tRFCab MSB
  0xD0,                                 ///< 31  tRFCpb = 90 ns (8 Gb dual-channel die)
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
  0x92,                                 ///< 123 FTB for tAAmin = 17.14 ns
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns
  0xA7,                                 ///< 125 FTB for tCKAVGmin = 0.536 ns (LPDDR4-3733)
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
  0x20,                                 ///< 325 Module Serial Number A
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

// LPDDR4X 556b 4Gb die, QDP, 1 channel per die, x16
// Micron MT53D512M64D4RQ-046 WT:E
// 4266
// 2 ranks per channel, 2 SDRAMs per channel, 2x4x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xQdp4Gb556bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x21,                                 ///< 5   16 Row bits, 10 Column bits
  0xB9,                                 ///< 6   Non-Monolithic DRAM Device, 4 dies, 1 Channels per die, Signal Loading not specified
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x02,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x03,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x00,                                 ///< 16  Signal Loading: Not Specific
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x04,                                 ///< 18  tCKAVGmin = 0.536 ns (LPDDR4-3733)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x05,                                 ///< 22  CAS Latencies supported (Third Byte) : 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x87,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.14 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (8 Gb single-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (8 Gb single-channel die)
  0x04,                                 ///< 32  tRFCpb MSB
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
  0xE5,                                 ///< 123 FTB for tAAmin = 17.14 ns (FTB = -0.11 ns)
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns (FTB = 0 ns)
  0xE1,                                 ///< 125 FTB for tCKAVGmin = 0.536 ns (FTB = -.089 ns) (LPDDR4-3733)
  0x85,                                 ///< 126 CRC A
  0x85,                                 ///< 127 CRC B
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
  0x56,                                 ///< 325 Module Serial Number A
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

// LPDDR4X 432b 16Gb die, QDP 2x16
// Samsung K3UH7H70MM-JGCJ
// 3733, 32-34-34-79
// 2 ranks per channel, 1 SDRAMs per rank, 4x16Gb = 8GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xQdp16Gb432bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x16,                                 ///< 4   8 Banks, no bank groups, 16 Gb SDRAM density
  0x21,                                 ///< 5   16 Row bits, 10 Column bits
  0xB4,                                 ///< 6   Non-Monolithic DRAM Device, 4 dies, 2 Channels per die, Signal Loading not specified
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
  0x05,                                 ///< 18  tCKAVGmin = 0.536 ns (LPDDR4-3733)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x01,                                 ///< 22  CAS Latencies supported (Third Byte) : 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8A,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.14 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (16 Gb dual-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (16 Gb dual-channel die)
  0x04,                                 ///< 32  tRFCpb MSB
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
  0x92,                                 ///< 123 FTB for tAAmin = 17.14 ns (FTB = -0.11 ns)
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns (FTB = 0 ns)
  0xA7,                                 ///< 125 FTB for tCKAVGmin = 0.536 ns (FTB = -.089 ns) (LPDDR4-3733)
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
  0x43,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x80,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0xCE,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
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

// LPDDR4X 556b 8Gb die, ODP, 1 channel per die, x16
// Micron MT53D1G64D8SQ-046
// 4266
// 2 ranks per channel, 2 SDRAMs per channel, 2x4x8Gb = 8GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xOdp8Gb556bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x21,                                 ///< 5   16 Row bits, 10 Column bits
  0xF0,                                 ///< 6   Non-Monolithic DRAM Device, 4 dies, 1 Channels per die, Signal Loading not specified
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x0A,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x01,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x00,                                 ///< 16  Signal Loading: Not Specific
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x05,                                 ///< 18  tCKAVGmin = 0.536 ns (LPDDR4-3733)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x01,                                 ///< 22  CAS Latencies supported (Third Byte) : 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8A,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.14 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (8 Gb single-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (8 Gb single-channel die)
  0x04,                                 ///< 32  tRFCpb MSB
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
  0x92,                                 ///< 123 FTB for tAAmin = 17.14 ns (FTB = -0.11 ns)
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns (FTB = 0 ns)
  0xA7,                                 ///< 125 FTB for tCKAVGmin = 0.536 ns (FTB = -.089 ns) (LPDDR4-3733)
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
  0x56,                                 ///< 325 Module Serial Number A
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

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4Ddp16Gb200b1rSpd[] = {
  0x23,                                 ///< 0 384 SPD bytes used, 512 total
  0x10,                                 ///< 1 SPD Revision 1.0
  0x11,                                 ///< 2 DRAM Type: LPDDR4X SDRAM
  0x0E,                                 ///< 3 Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4 8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5 15 Rows, 10 Columns
  0x95,                                 ///< 6 Non-Monolithic DRAM Device, 2 die, 2 Channels per package, Signal Loading Matrix 1
  0x08,                                 ///< 7 SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8 SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9 Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10 Reserved
  0x00,                                 ///< 11 Module Nominal Voltage: Reserved
  0x02,                                 ///< 12 Module Organization: 1 Ranks, x16 Device Width per Channel
  0x21,                                 ///< 13 Module Memory Bus width: 2 Channels, 16 bits channel width, no ECC
  0x00,                                 ///< 14 Module Thermal Sensor: none
  0x00,                                 ///< 15 Extended Module Type: Reserved
  0x48,                                 ///< 16 Signal Loading: Data/Strobe/Mask: 2 loads, CAC: 2 loads, CS: 1 load
  0x00,                                 ///< 17 MTB = 0.125ns, FTB = 1 ps
  0x05,                                 ///< 18  tCKAVGmin = 0.625 ns (LPDDR4-3200)
  0xFF,                                 ///< 19  tCKAVGmax = 32.002 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x55,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20, 16
  0x00,                                 ///< 22  CAS Latencies supported (Third Byte) :
  0x00,                                 ///< 23 CAS Latencies supported (Fourth Byte):
  0x8C,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.5 ns
  0x00,                                 ///< 25 Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26 Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27 Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28 Minimum row precharge time (tRPmin) = 18 ns
  0x90,                                 ///< 29 tRFCab = 210 ns (16 Gb dual-channel die)
  0x06,                                 ///< 30 tRFCab MSB
  0xD0,                                 ///< 31 tRFCpb = 90 ns (16 Gb dual-channel die)
  0x02,                                 ///< 32 tRFCpb MSB
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

// LPDDR5 496b 12Gb die, QDP 1x16
// Samsung K3LK2K20BM-BGCN
// 5500, ??-??-??-??
// 16 Banks, 4 bank groups, 12Gb SDRAM density
// 16 Row bits, 10 Column bits
// Non-Monolithic DRAM Device, 4 dies, 4 Channels per die,
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr5xQdp12Gb496bSpd[] = {
  // ************************************
  // Placeholder need correct SPD for LP5
  // ************************************
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x10,                                 ///< 1   SPD Revision 1.0
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5   5 15 Rows, 10 Columns
  0x95,                                 ///< 6   Non-Monolithic DRAM Device, 2 die, 2 Channels per package, Signal Loading Matrix 1
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x02,                                 ///< 12  Module Organization: 1 Ranks, x16 Device Width per Channel
  0x01,                                 ///< 13  Module Memory Bus width: 1 Channels, 16 bits channel width, no ECC
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
  0x90,                                 ///< 29  tRFCab = 210 ns (16 Gb dual-channel die)
  0x06,                                 ///< 30  tRFCab MSB
  0xD0,                                 ///< 31  tRFCpb = 90 ns (16 Gb dual-channel die)
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
  0x00,                                 ///< 125 FTB for tCKAVGmin = 0.469 ns (LPDDR4-4267)
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
  0x20,                                 ///< 325 Module ID: Module Serial Number
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

// LPDDR4X 200b 16Gb die, DDP, 2 channel per die, 2x8
// Samsung  K4U6E3S4AA-MGCL
// 4267, 36-39-39-90
// 1 rank per channel, 2 SDRAMs per channel, 2x8GB = 16GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xDdp16Gb200bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x10,                                 ///< 1   SPD Revision 1.0
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5   5 15 Rows, 10 Columns
  0x90,                                 ///< 6   Non-Monolithic DRAM Device, 2 die, 1 Channels per package, Signal Loading Matrix 1
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x02,                                 ///< 12  Module Organization: 1 Ranks, x16 Device Width per Channel
  0x01,                                 ///< 13  Module Memory Bus width: 1 Channels, 16 bits channel width, no ECC
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
  0x90,                                 ///< 29  tRFCab = 210 ns (16 Gb dual-channel die)
  0x06,                                 ///< 30  tRFCab MSB
  0xD0,                                 ///< 31  tRFCpb = 90 ns (16 Gb dual-channel die)
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
  0x00,                                 ///< 125 FTB for tCKAVGmin = 0.469 ns (LPDDR4-4267)
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
  0x20,                                 ///< 325 Module ID: Module Serial Number
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

// LPDDR4X 200b 8Gb die, DDP, 1 channel per die, x16
// Hynix H9HCNNNBKMMLHR-NEE
// Micron MT53D512M32D2NP-046
// 4267, 36-39-39-90
// 1 rank per channel, 2 SDRAMs per channel, 2x2x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8  mLpddr4xDdp8Gb200bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x11,                                 ///< 2   DRAM Type: LPDDR4X SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x21,                                 ///< 5   16 Row bits, 10 Column bits
  0x90,                                 ///< 6   Non-Monolithic DRAM Device, 2 dies, 1 Channel per die, Signal Loading not specified
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x02,                                 ///< 12  Module Organization: 1 Rank, x16 Device Width per Channel
  0x22,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x00,                                 ///< 16  Signal Loading: not specified
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x04,                                 ///< 18  tCKAVGmin = 0.469 ns (LPDDR4-4267)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x05,                                 ///< 22  CAS Latencies supported (Third Byte) : 36, 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x87,                                 ///< 24  Minimum CAS Latency (tAAmin) = 16.875 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (8 Gb single-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (8 Gb single-channel die)
  0x04,                                 ///< 32  tRFCpb MSB
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
  0x00,                                 ///< 123 FTB for tAAmin = 16.875 ns
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns
  0xE1,                                 ///< 125 FTB for tCKAVGmin = 0.469 ns (LPDDR4-4267)
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
  0x20,                                 ///< 325 Module ID: Module Serial Number
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

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 DDR4_SPD_MTA4ATF51264HZ_3G2E1[] = {
  0x23, 0x11, 0x0C, 0x03, 0x45, 0x21, 0x00, 0x08, 0x00, 0x60, 0x00, 0x03, 0x02, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x05, 0x0D, 0xF8, 0xFF, 0x2B, 0x00, 0x6E, 0x6E, 0x6E, 0x11, 0x00, 0x6E, 0xF0, 0x0A,
  0x20, 0x08, 0x00, 0x05, 0x00, 0xF0, 0x2B, 0x34, 0x28, 0x00, 0x78, 0x00, 0x14, 0x3C, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x36, 0x0B, 0x35,
  0x16, 0x36, 0x0B, 0x35, 0x00, 0x00, 0x16, 0x36, 0x0B, 0x35, 0x16, 0x36, 0x0B, 0x35, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 0xB5, 0x00, 0x00, 0x00, 0x00, 0xE7, 0x00, 0x30, 0x53,
  0x0F, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE2,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x2C, 0x0F, 0x18, 0x37, 0x1E, 0x5C, 0x85, 0x12, 0x34, 0x41, 0x54, 0x46, 0x35, 0x31, 0x32,
  0x36, 0x34, 0x48, 0x5A, 0x2D, 0x33, 0x47, 0x32, 0x45, 0x31, 0x20, 0x20, 0x20, 0x31, 0x80, 0x2C,
  0x45, 0x44, 0x50, 0x41, 0x4C, 0x35, 0x37, 0x51, 0x30, 0x30, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};