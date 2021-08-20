/** @file

  Platform CMOS Access Library.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Base.h>

#include <Library/PcdLib.h>
#include <Library/PlatformCmosAccessLib.h>
#include <CmosMap.h>

#define EXCLUDE_FROM_CHECKSUM    CMOS_EXCLUDE_FROM_CHECKSUM
#define EXCLUDE_FROM_INIT_DATA   CMOS_EXCLUDE_FROM_INIT_DATA

// Add the CMOS entry below
GLOBAL_REMOVE_IF_UNREFERENCED CMOS_ENTRY mCmosTable[] = {
{ RTC_ADDRESS_CENTURY,            DEFAULT_VALUE,          EXCLUDE_FROM_CHECKSUM },
{ CPU_HT_POLICY,                  CPU_HT_POLICY_DISABLED, EXCLUDE_FROM_CHECKSUM },
{ TPM_POLICY,                     TPM_POLICY_ENABLED,     EXCLUDE_FROM_CHECKSUM },
{ CMOS_CPU_BSP_SELECT,            DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_CPU_RATIO_OFFSET,          DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_ICH_PORT80_OFFSET,         DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_MAXRATIO_CONFIG_REG,       DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_SERIAL_BAUD_RATE_REG,      (UINT8)(FixedPcdGet32 (PcdSerialBaudRate) & 0xFF), EXCLUDE_FROM_CHECKSUM },
{ CMOS_SERIAL_BAUD_RATE_1_REG,    (UINT8)((FixedPcdGet32 (PcdSerialBaudRate) >> 8) & 0xFF), EXCLUDE_FROM_CHECKSUM },
{ CMOS_SERIAL_BAUD_RATE_2_REG,    (UINT8)((FixedPcdGet32 (PcdSerialBaudRate) >> 16) & 0xFF), EXCLUDE_FROM_CHECKSUM },
{ CMOS_SERIAL_BAUD_RATE_3_REG,    (UINT8)((FixedPcdGet32 (PcdSerialBaudRate) >> 24) & 0xFF), EXCLUDE_FROM_CHECKSUM },
{ CMOS_DEBUG_PRINT_LEVEL_REG,     (UINT8)(FixedPcdGet32 (PcdCmosDebugPrintErrorLevelDefaultValue) & 0xFF), EXCLUDE_FROM_CHECKSUM },
{ CMOS_DEBUG_PRINT_LEVEL_1_REG,   (UINT8)((FixedPcdGet32 (PcdCmosDebugPrintErrorLevelDefaultValue) >> 8) & 0xFF), EXCLUDE_FROM_CHECKSUM },
{ CMOS_DEBUG_PRINT_LEVEL_2_REG,   (UINT8)((FixedPcdGet32 (PcdCmosDebugPrintErrorLevelDefaultValue) >> 16) & 0xFF), EXCLUDE_FROM_CHECKSUM },
{ CMOS_DEBUG_PRINT_LEVEL_3_REG,   (UINT8)((FixedPcdGet32 (PcdCmosDebugPrintErrorLevelDefaultValue) >> 24) & 0xFF), EXCLUDE_FROM_CHECKSUM },
{ USB_DEBUG_PORT_BUS_REG,         DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ USB_DEBUG_PORT_DEVICE_REG,      DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ USB_DEBUG_PORT_FUNCTION_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ USB_DEBUG_PORT_TEMP_RAM_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM | EXCLUDE_FROM_INIT_DATA },
{ USB_DEBUG_PORT_TEMP_RAM_1_REG,  DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM | EXCLUDE_FROM_INIT_DATA },
{ USB_DEBUG_PORT_TEMP_RAM_2_REG,  DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM | EXCLUDE_FROM_INIT_DATA },
{ USB_DEBUG_PORT_TEMP_RAM_3_REG,  DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM | EXCLUDE_FROM_INIT_DATA },
{ USB3_DEBUG_PORT_BUS_REG,        DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ USB3_DEBUG_PORT_DEVICE_REG,     DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ USB3_DEBUG_PORT_FUNCTION_REG,   DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ USB3_DEBUG_XHC_MODE,            DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_DEBUG_PRINT_ENDPOINTS,     FixedPcdGet8 (PcdStatusCodeFlags), EXCLUDE_FROM_CHECKSUM },
{ CMOS_TBTHR_PRESENT_ON_RESUME,   DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_BOOT_REGISTER_REG,         DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_FLAG_REG,           DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_CONFIG_REG,         DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_SCRAMBLER_SEED_REG0,   DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_SCRAMBLER_SEED_REG1,   DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH00_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH01_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH02_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH03_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH04_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH05_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH06_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH07_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH08_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH09_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH10_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH11_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH12_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH13_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH14_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH15_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH16_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH17_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH18_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH19_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH20_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH21_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH22_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH23_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH24_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH25_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH26_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH27_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH28_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH29_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH30_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FFS_NV_HASH31_DATA_REG,    DEFAULT_VALUE, EXCLUDE_FROM_CHECKSUM },
{ CMOS_FAST_BOOT_REG,             FixedPcdGet8 (PcdCmosFastBootDefaultValue), EXCLUDE_FROM_CHECKSUM },
{ 0xFE, 0, CMOS_CHECKSUM_LOCATION },
{ 0xFF, 0, CMOS_CHECKSUM_LOCATION }
};

/**
  Return the platform CMOS entries.

  @param [out] EntryCount Return the count of platform CMOS entries.

  @return Platform CMOS entries.
**/
CMOS_ENTRY *
EFIAPI
PlatformCmosGetEntry (
  OUT UINTN       *EntryCount
  )
{
  *EntryCount = sizeof(mCmosTable) / sizeof(mCmosTable[0]);
  return mCmosTable;
}

/**
  Return the NMI enable status.
**/
BOOLEAN
EFIAPI
PlatformCmosGetNmiState (
  VOID
  )
{
  return TRUE;
}
