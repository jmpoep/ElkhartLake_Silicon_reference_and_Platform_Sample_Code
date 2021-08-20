/** @file
 Intel PEI SA Policy update by board configuration

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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
#include "PeiPolicyBoardConfig.h"
#include <TcssPeiPreMemConfig.h>
#include <TcssPeiConfig.h>
#include <Pins/GpioPinsVer1Lp.h>
#include <PlatformBoardId.h>
#include <Register/IomRegs.h>

IOM_AUX_ORI_PAD_CONFIG mIomAuxEhlD4Table[MAX_IOM_AUX_BIAS_COUNT] = {
  // Pull UP GPIO Pin, Pull Down GPIO pin
  {0,                  0}, // Port 0
  {0,                  0}, // Port 1
  {GPIO_VER1_LP_GPP_E23, GPIO_VER1_LP_GPP_E22},  // Port 2
  {0,                  0}, // Port 3
};

IOM_AUX_ORI_PAD_CONFIG mIomAuxNullTable[MAX_IOM_AUX_BIAS_COUNT] = {
  // Pull UP GPIO Pin, Pull Down GPIO pin
  {0,                  0}, // Port 0
  {0,                  0}, // Port 1
  {0,                  0}, // Port 2
  {0,                  0}, // Port 3
};

/**
  This function performs PEI SA Policy update by board configuration.

  @retval EFI_SUCCESS             The SI Policy is successfully updated.
  @retval Others                  The SI Policy is not successfully updated.
**/
EFI_STATUS
EFIAPI
UpdatePeiSaPolicyBoardConfig (
  VOID
  )
{
  EFI_STATUS                         Status;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                               *FspsUpd;
#else
  SI_POLICY_PPI                      *SiPolicyPpi;
  TCSS_PEI_CONFIG                    *TcssConfig;
#endif
  UINT32                             PortIndex;
  UINT16                             BoardId;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI    *VariableServices;
  UINTN                              VariableSize;
  SETUP_DATA                         SetupData;

  DEBUG ((DEBUG_INFO, "Updating SA Policy by board config in Post-Mem\n"));

  Status = EFI_SUCCESS;
  PortIndex = 0;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = NULL;
#else
  SiPolicyPpi = NULL;
  TcssConfig  = NULL;
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = (FSPS_UPD *) PcdGet32 (PcdFspsUpdDataAddress);
  ASSERT (FspsUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicyPpi);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gTcssPeiConfigGuid, (VOID *) &TcssConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                  VariableServices,
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupData
                  );
  ASSERT_EFI_ERROR (Status);

#if FixedPcdGet8(PcdFspModeSelection) == 1
  if (FspsUpd != NULL) {
#else
  if (TcssConfig != NULL) {
#endif

    //
    // Ascertain BoardId
    //
    BoardId = PcdGet16(PcdBoardId);
    DEBUG((DEBUG_INFO, "UpdatePeiSaPolicyBoardConfig - BoardId is 0x%04X\n", BoardId));

    //
    // Set Aux and HSL orientation based on BoardId value.
    //
    // TODO: As platforms are defined and added, new cases and values will need to be
    //       added to the below switch to set Aux and HSL orientations as appropriate.
    //
    switch (BoardId) {
      case BoardIdEhlLp4xType4Erb:
      case BoardIdEhlLp4xType4Rvp1:
      case BoardIdEhlDdr4Type3Rvp2:
      case BoardIdEhlLp4xType3Crb:
      case BoardIdJslLp4xType4Rvp1:
      case BoardIdJslLp4xErb:
      default:
        for (PortIndex = 0; PortIndex < MAX_IOM_AUX_BIAS_COUNT; PortIndex++) {
          //
          // The TypeC Port GPIO config setting refernce on board design
          //
          UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.IomTypeCPortPadCfg[(PortIndex * 2)],     TcssConfig->IomConfig.IomAuxPortPad[PortIndex].GpioPullN, mIomAuxNullTable[PortIndex].GpioPullN);
          UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.IomTypeCPortPadCfg[(PortIndex * 2) + 1], TcssConfig->IomConfig.IomAuxPortPad[PortIndex].GpioPullP, mIomAuxNullTable[PortIndex].GpioPullP);
        }

        //
        // Provide defaults for Aux and HSL orientation
        //
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TcssAuxOri, TcssConfig->IomConfig.IomOverrides.AuxOri, 0x0000);
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TcssHslOri, TcssConfig->IomConfig.IomOverrides.HslOri, 0x0000);
        DEBUG ((DEBUG_INFO, "UpdatePeiSaPolicy - Unhandled BoardId 0x%04X\n", BoardId));
        break;
    }
  }
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CpuUsb3OverCurrentPin[0], TcssConfig->UsbConfig.PortUsb30[0].OverCurrentPin, PcdGet8 (PcdCpuUsb30OverCurrentPinPort0));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CpuUsb3OverCurrentPin[1], TcssConfig->UsbConfig.PortUsb30[1].OverCurrentPin, PcdGet8 (PcdCpuUsb30OverCurrentPinPort1));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CpuUsb3OverCurrentPin[2], TcssConfig->UsbConfig.PortUsb30[2].OverCurrentPin, PcdGet8 (PcdCpuUsb30OverCurrentPinPort2));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CpuUsb3OverCurrentPin[3], TcssConfig->UsbConfig.PortUsb30[3].OverCurrentPin, PcdGet8 (PcdCpuUsb30OverCurrentPinPort3));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CpuUsb3OverCurrentPin[4], TcssConfig->UsbConfig.PortUsb30[4].OverCurrentPin, PcdGet8 (PcdCpuUsb30OverCurrentPinPort4));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CpuUsb3OverCurrentPin[5], TcssConfig->UsbConfig.PortUsb30[5].OverCurrentPin, PcdGet8 (PcdCpuUsb30OverCurrentPinPort5));

#if FixedPcdGet8(PcdFspModeSelection) == 1
  ((FSPS_UPD *) FspsUpd)->FspsConfig.UsbTcPortEn = PcdGet8 (PcdCpuUsb30PortEnable);
#endif
  for (PortIndex = 0; PortIndex < TCSS_MAX_USB3_PORTS; PortIndex++) {
#if FixedPcdGet8(PcdFspModeSelection) == 1
    ((FSPS_UPD *) FspsUpd)->FspsConfig.PortUsb30Enable[PortIndex] = (PcdGet8 (PcdCpuUsb30PortEnable) >> PortIndex) & 0x01;
#else
    TcssConfig->UsbConfig.PortUsb30[PortIndex].Enable             = (PcdGet8 (PcdCpuUsb30PortEnable) >> PortIndex) & 0x01;
#endif
  }
  return Status;
}
