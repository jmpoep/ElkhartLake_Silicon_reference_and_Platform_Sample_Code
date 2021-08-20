/** @file
  Board Config Patch Table

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2020 Intel Corporation.

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

#ifndef _ELKHARTLAKE_CONFIG_PATCH_TABLE_H_
#define _ELKHARTLAKE_CONFIG_PATCH_TABLE_H_

#include <Library/SetupInitLib.h>
#include <SetupVariable.h>

CONFIG_PATCH_TABLE  mElkhartlakeDdr4RvpSetupConfigPatchTable[] = {
//{-Type------------------Size-------------------------------------------Offset------------------------------------Data-------------},
  { SIZE_OF_FIELD(SETUP_DATA, TbtLegacyModeSupport),                   OFFSET_OF(SETUP_DATA, TbtLegacyModeSupport),                    0 },
  { SIZE_OF_FIELD(SETUP_DATA, AuxOriOverrideSupport),                  OFFSET_OF(SETUP_DATA, AuxOriOverrideSupport),                   1 },
  { SIZE_OF_FIELD(SETUP_DATA, HebcValueSupport),                       OFFSET_OF(SETUP_DATA, HebcValueSupport),                        1 },
  { SIZE_OF_FIELD(SETUP_DATA, PchI2cSensorDevicePort[SERIAL_IO_I2C2]), OFFSET_OF (SETUP_DATA, PchI2cSensorDevicePort[SERIAL_IO_I2C2]), SERIAL_IO_I2C_TOUCHPANEL },
  { SIZE_OF_FIELD(SETUP_DATA, PchSpiSensorDevicePort[SERIAL_IO_SPI2]), OFFSET_OF (SETUP_DATA, PchSpiSensorDevicePort[SERIAL_IO_SPI2]), SERIAL_IO_SPI_FINGERPRINT }
};

CONFIG_PATCH_TABLE  mElkhartlakeDdr4RvpPchSetupConfigPatchTable[] = {
//{-Type------------------Size-------------------------------------------Offset------------------------------------Data-------------},
  { SIZE_OF_FIELD(PCH_SETUP, PchUartHwFlowCtrl[2]),               OFFSET_OF(PCH_SETUP, PchUartHwFlowCtrl[2]),               0 },
  { SIZE_OF_FIELD(PCH_SETUP, PchPsePwmEnable),                    OFFSET_OF(PCH_SETUP, PchPsePwmEnable),                    1 },
  { SIZE_OF_FIELD(PCH_SETUP, PchPseI2cEnable[2]),                 OFFSET_OF(PCH_SETUP, PchPseI2cEnable[2]),                 1 },
  { SIZE_OF_FIELD(PCH_SETUP, PchPseTgpioAllocatePins[0]),         OFFSET_OF(PCH_SETUP, PchPseTgpioAllocatePins[0]),         0 },
  { SIZE_OF_FIELD(PCH_SETUP, PchPseTgpioAllocatePins[1]),         OFFSET_OF(PCH_SETUP, PchPseTgpioAllocatePins[1]),         0 },
  { SIZE_OF_FIELD(PCH_SETUP, PchPseTgpioPinEnable[6]),            OFFSET_OF(PCH_SETUP, PchPseTgpioPinEnable[6]),            1 },
  { SIZE_OF_FIELD(PCH_SETUP, CnviMode),                           OFFSET_OF(PCH_SETUP, CnviMode),                           1 },
};

CONFIG_PATCH_TABLE  mElkhartlakeCRBPchSetupConfigPatchTable[] = {
//{-Type------------------Size-------------------------------------------Offset------------------------------------Data-------------},
  { SIZE_OF_FIELD(PCH_SETUP, PchUartHwFlowCtrl[2]),               OFFSET_OF(PCH_SETUP, PchUartHwFlowCtrl[2]),               0 },
  { SIZE_OF_FIELD(PCH_SETUP, PchPsePwmEnable),                    OFFSET_OF(PCH_SETUP, PchPsePwmEnable),                    1 },
  { SIZE_OF_FIELD(PCH_SETUP, PchPseI2cEnable[2]),                 OFFSET_OF(PCH_SETUP, PchPseI2cEnable[2]),                 1 },
  { SIZE_OF_FIELD(PCH_SETUP, PchPseTgpioAllocatePins[0]),         OFFSET_OF(PCH_SETUP, PchPseTgpioAllocatePins[0]),         0 },
  { SIZE_OF_FIELD(PCH_SETUP, PchPseTgpioAllocatePins[1]),         OFFSET_OF(PCH_SETUP, PchPseTgpioAllocatePins[1]),         0 },
  { SIZE_OF_FIELD(PCH_SETUP, PchPseTgpioPinEnable[6]),            OFFSET_OF(PCH_SETUP, PchPseTgpioPinEnable[6]),            1 },
  { SIZE_OF_FIELD(PCH_SETUP, CnviMode),                           OFFSET_OF(PCH_SETUP, CnviMode),                           1 },
};

CONFIG_PATCH_STRUCTURE mElkhartlakeDdr4RvpConfigPatchStruct[] = {
  { L"Setup",    &gSetupVariableGuid,    sizeof(SETUP_DATA), mElkhartlakeDdr4RvpSetupConfigPatchTable, SIZE_OF_TABLE(mElkhartlakeDdr4RvpSetupConfigPatchTable, CONFIG_PATCH_TABLE) },
  { L"SaSetup",  &gSaSetupVariableGuid,  sizeof(SA_SETUP),   NULL, 0 },
  { L"CpuSetup", &gCpuSetupVariableGuid, sizeof(CPU_SETUP),  NULL, 0 },
  { L"PchSetup", &gPchSetupVariableGuid, sizeof(PCH_SETUP),  mElkhartlakeDdr4RvpPchSetupConfigPatchTable, SIZE_OF_TABLE(mElkhartlakeDdr4RvpPchSetupConfigPatchTable, CONFIG_PATCH_TABLE) },
  { L"MeSetup",  &gMeSetupVariableGuid,  sizeof(ME_SETUP),   NULL, 0 }
};

CONFIG_PATCH_STRUCTURE mElkhartlakeCRBConfigPatchStruct[] = {
  { L"Setup",    &gSetupVariableGuid,    sizeof(SETUP_DATA), mElkhartlakeDdr4RvpSetupConfigPatchTable, SIZE_OF_TABLE(mElkhartlakeDdr4RvpSetupConfigPatchTable, CONFIG_PATCH_TABLE) },
  { L"SaSetup",  &gSaSetupVariableGuid,  sizeof(SA_SETUP),   NULL, 0 },
  { L"CpuSetup", &gCpuSetupVariableGuid, sizeof(CPU_SETUP),  NULL, 0 },
  { L"PchSetup", &gPchSetupVariableGuid, sizeof(PCH_SETUP),  mElkhartlakeCRBPchSetupConfigPatchTable, SIZE_OF_TABLE(mElkhartlakeCRBPchSetupConfigPatchTable, CONFIG_PATCH_TABLE) },
  { L"MeSetup",  &gMeSetupVariableGuid,  sizeof(ME_SETUP),   NULL, 0 }
};

#endif // _ELKHARTLAKE_CONFIG_PATCH_TABLE_H_
