/** @file
  This file provides services for Thermal PEI policy function

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <ThermalConfig.h>

/**
  Print THERMAL_CONFIG settings.

  @param[in] SiPolicyPpi    Instance of SI_POLICY_PPI
**/
VOID
ThermalPrintConfig (
  IN  SI_POLICY_PPI         *SiPolicyPpi
  )
{
  EFI_STATUS                Status;
  UINTN                     Index;
  THERMAL_CONFIG  *ThermalConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gThermalConfigGuid, (VOID *) &ThermalConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ PCH Thermal Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " TTLevels T0Level %x centigrade degree\n", ThermalConfig->TTLevels.T0Level));
  DEBUG ((DEBUG_INFO, " TTLevels T1Level %x centigrade degree\n", ThermalConfig->TTLevels.T1Level));
  DEBUG ((DEBUG_INFO, " TTLevels T2Level %x centigrade degree\n", ThermalConfig->TTLevels.T2Level));
  DEBUG ((DEBUG_INFO, " TTLevels TTEnable %x\n", ThermalConfig->TTLevels.TTEnable));
  DEBUG ((DEBUG_INFO, " TTLevels TTState13Enable %x\n", ThermalConfig->TTLevels.TTState13Enable));
  DEBUG ((DEBUG_INFO, " TTLevels TTLock %x\n", ThermalConfig->TTLevels.TTLock));
  DEBUG ((DEBUG_INFO, " TTLevels SuggestedSetting %x\n", ThermalConfig->TTLevels.SuggestedSetting));
  DEBUG ((DEBUG_INFO, " TTLevels PchCrossThrottling %x\n", ThermalConfig->TTLevels.PchCrossThrottling));

  DEBUG ((DEBUG_INFO, " DmiHaAWC DmiTsawEn %x\n", ThermalConfig->DmiHaAWC.DmiTsawEn));
  DEBUG ((DEBUG_INFO, " DmiHaAWC TS0TW %x\n", ThermalConfig->DmiHaAWC.TS0TW));
  DEBUG ((DEBUG_INFO, " DmiHaAWC TS1TW %x\n", ThermalConfig->DmiHaAWC.TS1TW));
  DEBUG ((DEBUG_INFO, " DmiHaAWC TS2TW %x\n", ThermalConfig->DmiHaAWC.TS2TW));
  DEBUG ((DEBUG_INFO, " DmiHaAWC TS3TW %x\n", ThermalConfig->DmiHaAWC.TS3TW));
  DEBUG ((DEBUG_INFO, " DmiHaAWC SuggestedSetting %x\n", ThermalConfig->DmiHaAWC.SuggestedSetting));

  DEBUG ((DEBUG_INFO, " MemoryThrottling Enable= %x\n", ThermalConfig->MemoryThrottling.Enable));
  for (Index = 0; Index < MaxTsGpioPin; Index++) {
    DEBUG ((DEBUG_INFO, " MemoryThrottling TsGpioPinSetting PmsyncEnable= %x\n", ThermalConfig->MemoryThrottling.TsGpioPinSetting[Index].PmsyncEnable));
    DEBUG ((DEBUG_INFO, " MemoryThrottling TsGpioPinSetting C0TransmitEnable= %x\n", ThermalConfig->MemoryThrottling.TsGpioPinSetting[Index].C0TransmitEnable));
    DEBUG ((DEBUG_INFO, " MemoryThrottling TsGpioPinSetting PinSelection= %x\n", ThermalConfig->MemoryThrottling.TsGpioPinSetting[Index].PinSelection));
  }
  DEBUG ((DEBUG_INFO, " PchHotEnable = %x\n", ThermalConfig->PchHotEnable));
  DEBUG ((DEBUG_INFO, " PchHotLevel = %x\n", ThermalConfig->PchHotLevel));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
ThermalLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  THERMAL_CONFIG  *ThermalConfig;
  ThermalConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "ThermalConfig->Header.GuidHob.Name = %g\n", &ThermalConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "ThermalConfig->Header.GuidHob.Header.HobLength = 0x%x\n", ThermalConfig->Header.GuidHob.Header.HobLength));

  /********************************
    Thermal configuration.
  ********************************/
  ThermalConfig->PchHotLevel                 = 0x73;
  ThermalConfig->TTLevels.SuggestedSetting   = TRUE;
  ThermalConfig->TTLevels.PchCrossThrottling = TRUE;
  ThermalConfig->DmiHaAWC.SuggestedSetting   = TRUE;

  ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioC].PmsyncEnable     = TRUE;
  ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioC].C0TransmitEnable = TRUE;
  ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioD].PmsyncEnable     = TRUE;
  ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioD].C0TransmitEnable = TRUE;
}

STATIC COMPONENT_BLOCK_ENTRY  mThermalBlocks = {
  &gThermalConfigGuid,
  sizeof (THERMAL_CONFIG),
  THERMAL_CONFIG_REVISION,
  ThermalLoadConfigDefault
};

/**
  Get Thermal config block table size.

  @retval      Size of config block
**/
UINT16
ThermalGetConfigBlockTotalSize (
  VOID
  )
{
  return mThermalBlocks.Size;
}

/**
  Add Thermal ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
ThermalAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mThermalBlocks, 1);
  return Status;
}
