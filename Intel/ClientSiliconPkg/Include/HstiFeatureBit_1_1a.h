 /** @file
  This file contains various definitions for IHV HSTI implementation
  including STATUS string definitions

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification
**/

#ifndef __HSTI_FEATURE_BIT_1_1A_H__
#define __HSTI_FEATURE_BIT_1_1A_H__

#define HSTI_SECURITY_FEATURE_SIZE        3

typedef enum {
  P2sbEpMask5RemAccMaskBits29To26UnexpSts    = BIT0,
  P2sbEpMask7RemAccMaskBits31To30UnexpSts    = BIT1,
  P2sbLockMaskBitUnexpSts                    = BIT2
} SMM_HSTI_UNEXP_STATUS_DATA;

#define HSTI_STATUS                                                               L" Status "
#define HSTI_UNEXP_STATUS                                                         L" Unexpected Status "
#define HSTI_PLATFORM_SECURITY_SPECIFICATION                                      L" Platform Security Specification"
#define HSTI_BOOTGUARD_CONFIGURATION                                              L" - Boot Guard Configuration -"
#define HSTI_SPI_FLASH_CONFIGURATION                                              L" - SPI Flash Configuration -"
#define HSTI_UFS_BOOT_MEDIA_CONFIGURATION                                         L" - UFS Boot Media Configuration -"
#define HSTI_PCH_SECURITY_CONFIGURATION                                           L" - PCH Security Configuration -"
#define HSTI_BIOS_GUARD_SECURITY_CONFIGURATION                                    L" - BIOS Guard Security Configuration -"
#define HSTI_MEASURED_BOOT_CONFIGURATION                                          L" - Measured Boot Configuration -"
#define HSTI_INTEGRATED_DEVICE_DMA_PROTECTION                                     L" - Integrated Device DMA Protection -"
#define HSTI_DEBUG_INTERFACE_SECURITY_CONFIGURATION                               L" - Debug Interface Security Configuration -"
#define HSTI_CPU_SECURITY_CONFIGURATION                                           L" - CPU Security Configuration -"
#define HSTI_MEMORY_MAP_SECURITY_CONFIGURATION                                    L" - Memory Map Security Configuration -"
#define HSTI_PROCESSOR_GRAPHICS_SECURITY_CONFIGURATION                            L" - Processor Graphics Security Configuration -"
#define HSTI_PROCESSOR_SPD_SECURITY_CONFIGURATION                                 L" - SPD Security Configuration -"
#define HSTI_PCH_SMM_SECURITY_CONFIGURATION                                       L" - Secure PCH SMM Security Configuration - "

#define HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY                                 BIT0
#define      HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY_UNEXP_STATUS_CODE_1        L"0x00000001"
#define      HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY_UNEXP_STATUS_STRING_1      L" Boot Guard configured without Verified Boot\r\n"
#define      HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY_UNEXP_STATUS_CODE_2        L"0x00000002"
#define      HSTI_BYTE0_HARDWARE_ROOTED_BOOT_INTEGRITY_UNEXP_STATUS_STRING_2      L" Boot Guard disabled\r\n"

#define HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION                                 BIT1
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_1        L"0x00010001"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_1      L" SPI Flash not write protected\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_2        L"0x00010002"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_2      L" SPI Flash descriptor overridden\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_3        L"0x00010003"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_3      L" SPI Controller configuration unlocked\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_4        L"0x00010004"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_4      L" SPI Controller BIOS Interface unlocked\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_5        L"0x00010005"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_5      L" Top Swap enabled\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_6        L"0x00010006"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_6      L" SPI Vendor Specific Component Capabilities unlocked\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_8        L"0x00010008"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_8      L" ME FW not in Normal Working State\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_9        L"0x00010009"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_9      L" Flash Descriptor Invalid\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_A        L"0x0001000A"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_A      L" SPI Region Access Rights Invalid\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_D        L"0x0001000D"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_D      L" Global SMI not enabled and locked\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_E        L"0x0001000E"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_E      L" TCO SMI not enabled and locked\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_F        L"0x0001000F"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_F      L" Allowed WriteStatus SPI OPCODE configuration incorrect\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_10       L"0x00010010"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_10     L" UFS LUN 1(Boot Media LUN) is not Write Protected\r\n"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_11       L"0x00010011"
#define      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_11     L" Power On Write Protection is NOT enabled on UFS Boot Media\r\n"

#define HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE                                         BIT2
#define      HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_CODE_1                L"0x00020001"
#define      HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_STRING_1              L" BIOS Guard unsupported\r\n"
#define      HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_CODE_2                L"0x00020002"
#define      HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_STRING_2              L" BIOS Guard configuration unlocked\r\n"
#define      HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_CODE_3                L"0x00020001"
#define      HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_STRING_3              L" BIOS Guard disabled\r\n"

#define HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT                                      BIT3
#define      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_CODE_1             L"0x00030001"
#define      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_STRING_1           L" Chipset supports FW TPM, however no TPM enabled\r\n"
#define      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_CODE_2             L"0x00030002"
#define      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_STRING_2           L" PCR[7] is not initialized\r\n"
#define      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_CODE_3             L"0x00030003"
#define      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_STRING_3           L" Event Log is not published or invalid\r\n"
#define      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_CODE_4             L"0x00030004"
#define      HSTI_BYTE0_MEASURED_BOOT_ENFORCEMENT_UNEXP_STATUS_STRING_4           L" Platform Auth accessible via 0x00000000\r\n"

#define HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION                               BIT4
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_1      L"0x00040001"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_1    L" Bus Mastering Enabled for non-boot, integrated device - VTd Feature is not enabled in the CPU SKU\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_2      L"0x00040002"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_2    L" Bus Mastering Enabled for non-boot, integrated device - VTd1 is not enabled\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_3      L"0x00040003"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_3    L" Bus Mastering Enabled for non-boot, integrated device - VTd1 Region Address is not configured\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_4      L"0x00040004"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_4    L" Bus Mastering Enabled for non-boot, integrated device - VTd2 is not enabled\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_5      L"0x00040005"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_5    L" Bus Mastering Enabled for non-boot, integrated device - VTd2 Region Address is not configured\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_6      L"0x00040006"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_6    L" Bus Mastering Enabled for non-boot, integrated device - VTd3 is not enabled \r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_7      L"0x00040007"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_7    L" Bus Mastering Enabled for non-boot, integrated device - VTd3 Region Address is not configured\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_8      L"0x00040008"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_8    L" Bus Mastering Enabled for non-boot, integrated device - VTd4 is not enabled \r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_9      L"0x00040009"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_9    L" Bus Mastering Enabled for non-boot, integrated device - VTd4 Region Address is not configured\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_A      L"0x0004000A"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_A    L" Bus Mastering Enabled for non-boot, integrated device - VTd5 is not enabled\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_B      L"0x0004000B"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_B    L" Bus Mastering Enabled for non-boot, integrated device - VTd5 Region Address is not configured\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_C      L"0x0004000C"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_C    L" Bus Mastering Enabled for non-boot, integrated device - VTd6 is not enabled\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_D      L"0x0004000D"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_D    L" Bus Mastering Enabled for non-boot, integrated device - VTd6 Region Address is not configured\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_12     L"0x00040012"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_12   L" Bus Mastering Enabled for non-boot, integrated device - VTd9 is not enabled\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_13     L"0x00040013"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_13   L" Bus Mastering Enabled for non-boot, integrated device - VTd9 Region Address is not configured\r\n"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_10     L"0x00040010"
#define      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_10   L" Bus Mastering Enabled for non-boot, integrated device - VTd Feature is enabled in the CPU SKU but disabled in the Platform\r\n"

#define HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_CONFIGURATION                         BIT5
#define      HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_CODE_1              L"0x00050001"
#define      HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_STRING_1            L" Debug MSR enabled\r\n"
#define      HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_CODE_2              L"0x00050002"
#define      HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_STRING_2            L" Debug interface unlocked\r\n"
#define      HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_CODE_3              L"0x00050003"
#define      HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_STRING_3            L" OPI Debug interface unlocked\r\n"

#define HSTI_BYTE0_SECURE_CPU_CONFIGURATION                                       BIT6
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_1              L"0x00060001"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_1            L" Minimum uCode patch revision not met\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_2              L"0x00060002"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_2            L" Pre-production silicon in use\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_3              L"0x00060003"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_3            L" VMX & Senter feature configuration unlocked\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_4              L"0x00060004"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_4            L" SMM Code Fetch feature configuration unlocked\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_5              L"0x00060005"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_5            L" AES-NI Feature configuration unlocked\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_6              L"0x00060006"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_6            L" FIT table not present\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_7              L"0x00060007"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_7            L" Microcode Range Registers improperly configured or unlocked\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_8              L"0x00060008"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_8            L" SMM Configuration Unlocked\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_9              L"0x00060009"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_9            L" TSEG not naturally aligned\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_A              L"0x0006000A"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_A            L" Improper SMRR configuration\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_B              L"0x0006000B"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_B            L" SMM Code Fetch outside SMRAM detection feature is disabled\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_C              L"0x0006000C"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_C            L" BIOS DONE MSR is not set\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_D              L"0x0006000D"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_D            L" Intel TXT configuration unlocked\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_E              L"0x0006000E"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_E            L" Processor Reserved Memory Range Register is Supported but Disabled\r\n"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_CODE_F              L"0x0006000F"
#define      HSTI_BYTE0_SECURE_CPU_CONFIGURATION_UNEXP_STATUS_STRING_F            L" Volume Management Device is Unlocked\r\n"

#define HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION                                BIT0
#define      HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_UNEXP_STATUS_CODE_1       L"0x00080001"
#define      HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_UNEXP_STATUS_STRING_1     L" Memory BAR configuration unlocked\r\n"
#define      HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_UNEXP_STATUS_CODE_2       L"0x00080002"
#define      HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_UNEXP_STATUS_STRING_2     L" Fixed MMIO regions overlap\r\n"
#define      HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_UNEXP_STATUS_CODE_3       L"0x00080003"
#define      HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_UNEXP_STATUS_STRING_3     L" Non lockable MMIO ranges overlap other critical regions\r\n"

#define HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION                              BIT1
#define      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_CODE_1     L"0x00090001"
#define      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_STRING_1   L" Graphics configuration unlocked\r\n"
#define      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_CODE_2     L"0x00090002"
#define      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_STRING_2   L" Invalid Graphics Memory Alignment\r\n"
#define      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_CODE_3     L"0x00090003"
#define      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_STRING_3   L" Reserved Check failed\r\n"

#define HSTI_BYTE1_SECURE_PCH_CONFIGURATION                                              BIT2
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_1                     L"0x000A0001"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_1                   L" Thermal Configuration unlocked\r\n"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_2                     L"0x000A0002"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_2                   L" BAR's unlocked\r\n"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_3                     L"0x000A0003"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_3                   L" Reserved Check failure\r\n"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_4                     L"0x000A0004"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_4                   L" SPD not write protected\r\n"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_5                     L"0x000A0005"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_5                   L" ACS ECH Root Port is not Configured\r\n"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_6                     L"0x000A0006"
#define      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_6                   L" VR CONFIG Bit is Unlocked\r\n"
// HSTI IHV PCH P2SB SMM
#define      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_CODE_1                 L"0x000A0010"
#define      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_STRING_1               L" P2SB EPMASK5 Remove Access Mask is not Configured\r\n"
#define      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_CODE_2                 L"0x000A0020"
#define      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_STRING_2               L" P2SB EPMASK7 Remove Access Mask is not Configured\r\n"
#define      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_CODE_3                 L"0x000A0030"
#define      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_STRING_3               L" P2SB Mask Bit is Unlocked\r\n"


#endif
