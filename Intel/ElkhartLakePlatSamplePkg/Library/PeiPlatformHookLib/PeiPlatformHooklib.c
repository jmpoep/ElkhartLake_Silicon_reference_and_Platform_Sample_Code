/** @file
  PEI Library Functions. Initialize GPIOs

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#include <PiPei.h>
#include <Board/Include/PeiPlatformHookLib.h>
#include <PlatformBoardId.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <SaPolicyCommon.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/TimerLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PeiPlatformLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/EcMiscLib.h>
#include <Library/EcLib.h>
#include <Library/PmcLib.h>
#include <IpBlock/Pmc/IncludePrivate/Library/PmcPrivateLib.h>
#include <Library/PeiSaPolicyLib.h>
#include <SaDataHob.h>
#include <Guid/ImageAuthentication.h>
#include <Library/CpuPlatformLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/GpioLib.h>
#include <Library/HdaLib.h>
#include <Pins/GpioPinsVer1Lp.h>
#include <Pins/GpioPinsVer1N.h>
#include <Library/PchInfoLib.h>
#include <Library/CnviLib.h>
#include <SioRegs.h>
#include <PlatformBoardConfig.h>
#include <Library/PchPcrLib.h>
#include <Register/PchRegs.h>
#include <IndustryStandard/Pci30.h>
#include <BoardConfigInit.h>
#include <Library/MemoryAllocationLib.h>

#define SIO_RUNTIME_REG_BASE_ADDRESS                          0x0680

#define RECOVERY_MODE_GPIO_PIN                    0                    // Platform specific @todo use PCD

#define MANUFACTURE_MODE_GPIO_PIN                 0                    // Platform specific @todo use PCD

/**
  Configures GPIO

  @param[in]  GpioTable       Point to Platform Gpio table
  @param[in]  GpioTableCount  Number of Gpio table entries

**/
VOID
ConfigureGpio (
  IN GPIO_INIT_CONFIG                 *GpioDefinition,
  IN UINT16                           GpioTableCount
  )
{
  DEBUG ((DEBUG_INFO, "ConfigureGpio() Start\n"));

  GpioConfigurePads (GpioTableCount, GpioDefinition);

  DEBUG ((DEBUG_INFO, "ConfigureGpio() End\n"));
}

/**
  Configure GPIO group GPE tier.

  @retval     none.
**/
VOID
GpioGroupTierInit (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "GpioGroupTierInit Start\n"));

  if (PcdGet32 (PcdGpioGroupToGpeDw0)) {
    GpioSetGroupToGpeDwX (PcdGet32 (PcdGpioGroupToGpeDw0),
                          PcdGet32 (PcdGpioGroupToGpeDw1),
                          PcdGet32 (PcdGpioGroupToGpeDw2));
  }
  DEBUG ((DEBUG_INFO, "GpioGroupTierInit End\n"));
}


/**
  Configure GPIO pads for TouchPanels use
**/
VOID
TouchPanelGpioInit (
  VOID
  )
{
  EFI_STATUS                      Status;
  PCH_SETUP                       PchSetup;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  UINTN                           VarSize;
  UINT16                          BoardId;
  GPIO_INIT_CONFIG*               TouchpanelPad;
  GPIO_PAD_OWN                    PadOwnVal;

  DEBUG ((DEBUG_INFO, "TouchPanelGpioInit Start\n"));

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "TouchPanelGpioInit: PeiServicesLocatePpi failed\n"));
    return;
  }

  VarSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &PchSetup
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "TouchPanelGpioInit: GetVariable (PchSetup) failed\n"));
    return;
  }
  BoardId = PcdGet16(PcdBoardId);

  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp:
    case BoardIdEhlDdr4Type3Rvp:
    case BoardIdEhlLp4xType3Crb:
    case BoardIdJslLp4xErb:
      //
      // Verify if THC0 or THC1 panels are enabled before changing GPIO configuration
      //
      if (PchSetup.ThcPort0Assignment == ThcAssignmentNone) {
        DEBUG ((DEBUG_INFO, "THC0 Disabled. Configuring GPIO Touch Panel 1 set for other controller use\n"));
        ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTableTouchPanel1), (UINTN) PcdGet16 (PcdBoardGpioTableTouchPanel1Size));
      }

      if (PchSetup.ThcPort1Assignment == ThcAssignmentNone) {
        DEBUG ((DEBUG_INFO, "THC1 Disabled. Configuring GPIO Touch Panel 2 set for other controller use\n"));
        ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTableTouchPanel2), (UINTN) PcdGet16 (PcdBoardGpioTableTouchPanel2Size));
      }
      break;
  }
  DEBUG ((DEBUG_INFO, "TouchPanelGpioInit End\n"));
}

VOID
ConnectivityGpioInit (
  VOID
  )
{
  EFI_STATUS                      Status;
  PCH_SETUP                       PchSetup;
  SETUP_DATA                      SetupData;
  UINTN                           VarSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ConnectivityGpioInit: PeiServicesLocatePpi failed\n"));
    return;
  }

  VarSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &PchSetup
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ConnectivityGpioInit: GetVariable (PchSetup) failed\n"));
    return;
  }

  VarSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &SetupData
                               );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "ConnectivityGpioInit: GetVariable (SetupData) failed\n"));
    return;
  }
  if (!CnviIsPresent () || (PchSetup.CnviMode == CnviModeDisabled)) {
    //
    // Discrete BT Module Selection as Disabled, Over USB or UART
    //
    PcdSet8S (PcdDiscreteBtModule, SetupData.DiscreteBtModule);
  }

}

VOID
MipiCamConfigureGpio (
  IN GPIO_CONFIG *GpioConfig
  )
{
  ZeroMem(GpioConfig, sizeof(GPIO_CONFIG));
  GpioConfig->PadMode = GpioPadModeGpio;
  GpioConfig->HostSoftPadOwn = GpioHostOwnGpio;
  GpioConfig->Direction = GpioDirOut;
  GpioConfig->OutputState = GpioOutDefault;
  GpioConfig->InterruptConfig = GpioIntDis;
  GpioConfig->PowerConfig = GpioPlatformReset;
  GpioConfig->ElectricalConfig = GpioTermNone;
}

VOID
MipiCamGpioInit (
  VOID
  )
{
  PCH_SETUP                       PchSetup;
  SETUP_DATA                      SetupData;
  UINTN                           VarSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  EFI_STATUS                      Status;
  GPIO_CONFIG                     GpioConfig;
  GPIO_PAD                        GpioPad;
  UINT8                           GpioPin;

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "MipiCamGpioInit: PeiServicesLocatePpi failed\n"));
    return;
  }

  VarSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &PchSetup
                               );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "MipiCamGpioInit: GetVariable (PchSetup) failed\n"));
    return;
  }

  VarSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &SetupData
                               );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "MipiCamGpioInit: GetVariable (SetupData) failed\n"));
    return;
  }

  MipiCamConfigureGpio (&GpioConfig);
  if ((SetupData.MipiCam_ControlLogic0) && (SetupData.MipiCam_ControlLogic0_Type == (UINT8)1) && (SetupData.MipiCam_ControlLogic0_GpioPinsEnabled)) {
    DEBUG((DEBUG_INFO, "MipiCamGpioInit ControlLogic0\n"));
    for (GpioPin = 0; GpioPin < SetupData.MipiCam_ControlLogic0_GpioPinsEnabled; GpioPin ++) {
      GpioPad = GpioGetGpioPadFromGroupIndexAndPadNumber (
                                   (UINT32)SetupData.MipiCam_ControlLogic0_GpioGroupNumber[GpioPin],
                                   (UINT32)SetupData.MipiCam_ControlLogic0_GpioGroupPadNumber[GpioPin]);
      DEBUG((DEBUG_INFO, "MipiCamGpioInit GpioPad 0x%x\n", GpioPad));
      GpioSetPadConfig (GpioPad, &GpioConfig);
    }
  }
  if ((SetupData.MipiCam_ControlLogic1) && (SetupData.MipiCam_ControlLogic1_Type == (UINT8)1) && (SetupData.MipiCam_ControlLogic1_GpioPinsEnabled)) {
    DEBUG((DEBUG_INFO, "MipiCamGpioInit ControlLogic1\n"));
    for (GpioPin = 0; GpioPin < SetupData.MipiCam_ControlLogic1_GpioPinsEnabled; GpioPin ++) {
      GpioPad = GpioGetGpioPadFromGroupIndexAndPadNumber (
                                   (UINT32)SetupData.MipiCam_ControlLogic1_GpioGroupNumber[GpioPin],
                                   (UINT32)SetupData.MipiCam_ControlLogic1_GpioGroupPadNumber[GpioPin]);
      DEBUG((DEBUG_INFO, "MipiCamGpioInit GpioPad 0x%x\n", GpioPad));
      GpioSetPadConfig (GpioPad, &GpioConfig);
    }
  }
  if ((SetupData.MipiCam_ControlLogic2) && (SetupData.MipiCam_ControlLogic2_Type == (UINT8)1) && (SetupData.MipiCam_ControlLogic2_GpioPinsEnabled)) {
    DEBUG((DEBUG_INFO, "MipiCamGpioInit ControlLogic2\n"));
    for (GpioPin = 0; GpioPin < SetupData.MipiCam_ControlLogic2_GpioPinsEnabled; GpioPin ++) {
      GpioPad = GpioGetGpioPadFromGroupIndexAndPadNumber (
                                   (UINT32)SetupData.MipiCam_ControlLogic2_GpioGroupNumber[GpioPin],
                                   (UINT32)SetupData.MipiCam_ControlLogic2_GpioGroupPadNumber[GpioPin]);
      DEBUG((DEBUG_INFO, "MipiCamGpioInit GpioPad 0x%x\n", GpioPad));
      GpioSetPadConfig (GpioPad, &GpioConfig);
    }
  }
  if ((SetupData.MipiCam_ControlLogic3) && (SetupData.MipiCam_ControlLogic3_Type == (UINT8)1) && (SetupData.MipiCam_ControlLogic3_GpioPinsEnabled)) {
    DEBUG((DEBUG_INFO, "MipiCamGpioInit ControlLogic3\n"));
    for (GpioPin = 0; GpioPin < SetupData.MipiCam_ControlLogic3_GpioPinsEnabled; GpioPin ++) {
      GpioPad = GpioGetGpioPadFromGroupIndexAndPadNumber (
                                   (UINT32)SetupData.MipiCam_ControlLogic3_GpioGroupNumber[GpioPin],
                                   (UINT32)SetupData.MipiCam_ControlLogic3_GpioGroupPadNumber[GpioPin]);
      DEBUG((DEBUG_INFO, "MipiCamGpioInit GpioPad 0x%x\n", GpioPad));
      GpioSetPadConfig (GpioPad, &GpioConfig);
    }
  }
  return;
}

/**
  Configure SCI GPIO
**/
VOID
SciGpioInit (
  VOID
  )
{
  // Skip GPIO configuration if SCI is not supported
  if ((!PmcIsSciSupported()) || (!PchIsSciSupported())) {
    return;
  }

  DEBUG((DEBUG_INFO, "SciGpioInit\n"));

  ConfigureGpio((VOID *) (UINTN) PcdGet32 (PcdGpioTableSci), (UINTN) PcdGet16 (PcdGpioTableSciSize));
}

/**
  Configure GPIO Before Memory is not ready.

**/
VOID
GpioInitPreMem (
  VOID
  )
{
  GPIO_INIT_CONFIG   *GpioInitConfig;
  UINT16             GpioCount;
  SA_SETUP           SaSetup;
  UINTN              VarSize;

  GpioInitConfig = PcdGetPtr (PcdBoardGpioTablePreMem);

  if (GpioInitConfig != 0) {
    GpioCount = 0;
    GetGpioTableSize (GpioInitConfig, &GpioCount);
    if (GpioCount != 0) {
      ConfigureGpio ((VOID *) GpioInitConfig, (UINTN) GpioCount);
    }
  }
  VarSize = sizeof (SA_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"SaSetup",
                               &gSaSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &SaSetup
                               );
  if (!EFI_ERROR(Status) && (SaSetup.DisplayDdiPortA == 0x2) {
    if (PcdGet32(PcdBoardGpioTableMipiPreMem) != 0 && PcdGet16(PcdBoardGpioTableMipiPreMemSize) != 0) {
      ConfigureGpio ((VOID *)(UINTN)PcdGet32(PcdBoardGpioTableMipiPreMem), (UINTN)PcdGet16(PcdBoardGpioTableMipiPreMemSize));
    }
  }
}

/**
  Basic GPIO configuration before memory is ready

**/
VOID
GpioInitEarlyPreMem (
  VOID
  )
{
  GPIO_CONFIG                     BbrstConfig;
  UINT32                          WwanBbrstGpio;

  WwanBbrstGpio = PcdGet32 (PcdWwanBbrstGpio);

  if (WwanBbrstGpio) {
    //
    // BIOS needs to reset modem if modem RESET# is not asserted via PLTRST# in the previous sleep state
    //
    GpioGetPadConfig (WwanBbrstGpio, &BbrstConfig);
    if ((PcdGetBool (PcdPcieWwanEnable) == FALSE) ||
        (PcdGetBool (PcdWwanResetWorkaround) == TRUE &&
        BbrstConfig.Direction == GpioDirOut &&
        BbrstConfig.OutputState == GpioOutHigh)) {
      //
      // Assert FULL_CARD_POWER_OFF#, RESET# and PERST# GPIOs
      //
      if (PcdGet32 (PcdBoardGpioTableWwanOffEarlyPreMem) != 0 && PcdGet16 (PcdBoardGpioTableWwanOffEarlyPreMemSize) != 0) {
        ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTableWwanOffEarlyPreMem), (UINTN) PcdGet16 (PcdBoardGpioTableWwanOffEarlyPreMemSize));
      }
      MicroSecondDelay (1 * 1000); // Delay by 1ms
    }

    if (PcdGetBool (PcdPcieWwanEnable) == TRUE) {
      if (PcdGet32 (PcdBoardGpioTableWwanOnEarlyPreMem) != 0 && PcdGet16 (PcdBoardGpioTableWwanOnEarlyPreMemSize) != 0) {
        ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTableWwanOnEarlyPreMem), (UINTN) PcdGet16 (PcdBoardGpioTableWwanOnEarlyPreMemSize));
      }
    }
  }
}

/**
  Configure GPIO

**/
VOID
GpioInit (
  VOID
  )
{
  GPIO_INIT_CONFIG   *GpioInitConfig;
  UINT16             GpioCount;

  DEBUG ((DEBUG_ERROR, "GpioInit()\n"));
  GpioInitConfig = PcdGetPtr (PcdBoardGpioTable);

  if (GpioInitConfig != 0) {
    GpioCount = 0;
    GetGpioTableSize (GpioInitConfig, &GpioCount);
    if (GpioCount != 0) {
      ConfigureGpio ((VOID *) GpioInitConfig, GpioCount);
    }
  }
  if (PcdGet32 (PcdBoardGpioTable2)) {
    ConfigureGpio ((VOID *) (UINTN) PcdGet32 (PcdBoardGpioTable2), (UINTN) PcdGet16 (PcdBoardGpioTable2Size));
  }


  TouchPanelGpioInit ();

  // Configure Connectivity options
  ConnectivityGpioInit();
  if (PcdGetBool (PcdMipiCamGpioEnable)) {
    MipiCamGpioInit();
  }


  SciGpioInit ();

  //
  // Lock pads after initializing platform GPIO.
  // Pads which were requested to be unlocked during configuration
  // will not be locked.
  //
  GpioLockPads ();

  return;
}

/**
  Configure Super IO

**/
VOID
SioInit (
  VOID
  )
{
  //
  // Program and Enable Default Super IO Configuration Port Addresses and range
  //
  PchLpcGenIoRangeSet (PcdGet16 (PcdLpcSioConfigDefaultPort) & (~0xF), 0x10);

  //
  // Enable LPC decode for KCS and mailbox SIO for iBMC communication
  //
  if (PcdGet8 (PcdPlatformFlavor) == FlavorUpServer) {
    PchLpcGenIoRangeSet (BMC_KCS_BASE_ADDRESS, 0x10);
    PchLpcGenIoRangeSet (PILOTIII_MAILBOX_BASE_ADDRESS, 0x10);
  } else {
  //
  // 128 Byte Boundary and SIO Runtime Register Range is 0x0 to 0xF;
  //
    PchLpcGenIoRangeSet (SIO_RUNTIME_REG_BASE_ADDRESS  & (~0x7F), 0x10);
  }
  //
  // We should not depend on SerialPortLib to initialize KBC for legacy USB
  // So initialize KBC for legacy USB driver explicitly here.
  // After we find how to enable mobile KBC, we will add enabling code for mobile then.
  //

  if ((PcdGet8 (PcdPlatformFlavor) == FlavorDesktop) ||
      (PcdGet8 (PcdPlatformFlavor) == FlavorWorkstation)) {

    //
    // Enable KBC for National PC8374 SIO
    //
    if (PcdGetBool (PcdPc8374SioKbcPresent)) {
      IoWrite8 (PcdGet16 (PcdDesktopLpcSioIndexDefaultPort), 0x07);
      IoWrite8 (PcdGet16 (PcdDesktopLpcSioDataDefaultPort), 0x06);
      IoWrite8 (PcdGet16 (PcdDesktopLpcSioIndexDefaultPort), 0x30);
      IoWrite8 (PcdGet16 (PcdDesktopLpcSioDataDefaultPort), 0x01);
    }
  }

  return;
}

/**
  Configure GPIO and SIO before memory ready

  @retval  EFI_SUCCESS   Operation success.
**/
EFI_STATUS
BoardInitPreMem (
  VOID
  )
{
  //
  // Obtain Platform Info from HOB.
  //
  GpioInitPreMem ();
  GpioGroupTierInit ();
  SioInit ();

  return EFI_SUCCESS;
}

/**
  Configure GPIO and SIO

  @retval  EFI_SUCCESS   Operation success.
**/
EFI_STATUS
BoardInit (
  VOID
  )
{
  GpioInit ();

  return EFI_SUCCESS;
}

/**
  Detect recovery mode

  @retval  EFI_SUCCESS       System in Recovery Mode
  @retval  EFI_UNSUPPORTED   System doesn't support Recovery Mode
  @retval  EFI_NOT_FOUND     System is not in Recovery Mode
**/
EFI_STATUS
IsRecoveryMode (
  VOID
  )
{
  BOOLEAN               RecJumperFlag;
  UINT32                BitMask;
  EFI_STATUS            Status;
  UINT32                RecoveryModeGpio;
  PCD64_BLOB            Pcd64;

  //
  // Obtain Platform Info from HOB.
  //
  RecoveryModeGpio = 0;

  Pcd64.Blob = PcdGet64 (PcdRecoveryModeGpio);

  if (PcdGet8 (PcdPlatformFlavor) == FlavorUpServer) {
      return EFI_NOT_FOUND;
  } else if (Pcd64.BoardGpioConfig.Type != BoardGpioTypeNotSupported) {
    if (Pcd64.BoardGpioConfig.Type == BoardGpioTypePch) {
      Status = GpioGetInputValue (Pcd64.BoardGpioConfig.u.Pin, &RecoveryModeGpio);
      ASSERT_EFI_ERROR (Status);
      if (EFI_ERROR(Status)) {
        return Status;
      }
    } else {
      DEBUG ((DEBUG_ERROR, "Board Recovery Mode GPIO type is unidentified. Type = %x\n", Pcd64.BoardGpioConfig.Type));
      ASSERT (FALSE);
    }
    DEBUG ((DEBUG_INFO, "Expander value returned  %x\n",RecoveryModeGpio));
  } else {
    //
    // Read the status of the GPIO recovery jumper from the GPIO registers @ to do: GPIO will be assigned by board
    //
    //GpioGetInputValue (RECOVERY_MODE_GPIO_PIN, &RecoveryModeGpio); //@todo, uncomment when RECOVERY_MODE_GPIO_PIN has been assigned correct GpioPad
    RecoveryModeGpio = 0x1; //@todo, remove when RECOVERY_MODE_GPIO_PIN has been assigned correct GpioPad
  }
  //
  // Select/modify the GPIO initialization data based on the Board ID.
  //
  if (PcdGet8 (PcdBoardType) == BoardTypeSv || PcdGet8 (PcdBoardType) == BoardTypeRvpErb) {
    //
    // There is no Recovery jumper
    //
    return EFI_NOT_FOUND;
  } else {
    BitMask = BIT0;
  }

  RecJumperFlag = ((BOOLEAN) (!(RecoveryModeGpio & BitMask)));
  if (RecJumperFlag) {
    DEBUG ((DEBUG_INFO, "RecJumperFlag SET\n"));
    return EFI_SUCCESS;
  } else {
    DEBUG ((DEBUG_INFO, "RecJumperFlag NOT SET\n"));
    return EFI_NOT_FOUND;
  }
}

/**
  Do platform specific programming. For example, EC init, Chipset programming

  @retval  EFI_SUCCESS       The function completed successfully.
**/
EFI_STATUS
PlatformSpecificInitPreMem (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_BOOT_MODE                   BootMode;
  SA_SETUP                        SaSetup;
  PCH_SETUP                       PchSetup;
  SETUP_DATA                      SystemConfiguration;
  UINTN                           VarSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  ASSERT_EFI_ERROR (Status);

  VarSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &PchSetup
                               );

  if (!EFI_ERROR(Status) && PcdGetBool (PcdEcPresent)) {
    EcInit (PchSetup.PchLan, BootMode);
  }

  VarSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &SystemConfiguration
                               );
  if (!EFI_ERROR(Status)) {
    //
    // Selecting charging method
    //
    if (PcdGetBool (PcdEcPresent)) {
      if (SystemConfiguration.EcChargingMethod == 1) {
        //
        // Fast charging
        //
        DfctFastChargingMode (TRUE);
      } else {
        //
        // Normal charging
        //
        DfctFastChargingMode (FALSE);
      }
    }

    VarSize = sizeof (SA_SETUP);
    Status = VariableServices->GetVariable (
                                 VariableServices,
                                 L"SaSetup",
                                 &gSaSetupVariableGuid,
                                 NULL,
                                 &VarSize,
                                 &SaSetup
                                 );
    if (!EFI_ERROR(Status)) {
      if (PcdGet8 (PcdPlatformType) == TypeUltUlx) {
        // Force Valid Sensor Settings depending on the Option selected in Sensor Hub Type Setup Option.
        if(SystemConfiguration.SensorHubType == 0) {
          SystemConfiguration.UsbSensorHub = 0;
        } else if (SystemConfiguration.SensorHubType == 1) {
          SaSetup.AlsEnable = 0;
          SystemConfiguration.UsbSensorHub = 0;
        } else {
          SaSetup.AlsEnable = 0;
          SystemConfiguration.UsbSensorHub = 1;
        }
      }
    }
  }
  return EFI_SUCCESS;
}

/**
  Do platform specific programming post-memory.

  @retval  EFI_SUCCESS       The function completed successfully.
**/

EFI_STATUS
PlatformSpecificInit (
  VOID
  )
{
  EFI_STATUS                      Status;
  CPU_SETUP                       CpuSetup;
  UINTN                           VarSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  ASSERT_EFI_ERROR (Status);


  VarSize = sizeof (CPU_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"CpuSetup",
                               &gCpuSetupVariableGuid,
                               NULL,
                               &VarSize,
                               &CpuSetup
                               );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Checks if Premium PMIC present (VendorID == 1Fh)

  @retval  TRUE  if present
  @retval  FALSE it discrete/other PMIC
**/
BOOLEAN
IsPremiumPmicPresent (
  VOID
  )
{
  UINT8                           PmicVendorID;

  PmicVendorID = 0;
  //Send KSC Command to detect vendor ID of PMIC is present on the system(Applicable only for ULT/ULX Platforms)
  DetectPmicVendorID (&PmicVendorID);
  DEBUG((DEBUG_INFO, "Vendor ID of the Pmic Present on the system is: %x\n", PmicVendorID));

  if (PmicVendorID == 0x1F) {
    return TRUE;
  }

  return FALSE;
}

/**
  Pmic Programming to supprort LPAL Feature

  @retval     EFI_SUCCESS       Operation success.
**/
VOID
PremiumPmicDisableSlpS0Voltage (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT8                           EcDataV085ACNT;

  //
  // Disable voltage margining for Premium PMIC
  //
  EcDataV085ACNT = 0x3A;
  Status = SetSlpS0Voltage (EcDataV085ACNT); //Set or reset the V085ACNT[7:6] register based on Pmic Vendor ID
  ASSERT_EFI_ERROR (Status);
}

/**
Pmic Programming to Enable Voltage Margining
**/
VOID
PremiumPmicEnableSlpS0Voltage (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT8                           EcDataV085ACNT;
  UINT64                          HdaPciBase;
  BOOLEAN                         PremiumPmicPresent;

  HdaPciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 HdaDevNumber (),
                 HdaFuncNumber (),
                 0
                 );
  PremiumPmicPresent = IsPremiumPmicPresent();
  if ((PciSegmentRead16(HdaPciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) && (PremiumPmicPresent == TRUE)) { // If HDA Device is not detected & Premium PMIC is present
    DEBUG((DEBUG_INFO, "Enable VM in case Premium PMIC is Detected and HDA Disabled\n"));
    EcDataV085ACNT = 0x7A; //Enable Voltage Margining in case HDA is disabled
    Status = SetSlpS0Voltage(EcDataV085ACNT);
    ASSERT_EFI_ERROR(Status);
  }
}

/**
  Pmic Voltage Selection as directed by User

  @param[in]  SystemConfiguration
**/
VOID
PmicVoltageSelect (
  IN SETUP_DATA              *SystemConfiguration
  )
{
  EFI_STATUS                      Status;
  UINT8                           EcDataVcc;
  UINT8                           EcDataVddq;

  if ((SystemConfiguration->PmicVccLevel == 7) && (SystemConfiguration->PmicVddqLevel == 8)) {
    return;
  }

  switch (SystemConfiguration->PmicVccLevel) {
    case 0:
      EcDataVcc = 0x01;
      break;
    case 1:
      EcDataVcc = 0x00;
      break;
    case 2:
      EcDataVcc = 0x02;
      break;
    case 3:
      EcDataVcc = 0x03;
      break;
    case 4:
      EcDataVcc = 0x04;
      break;
    case 5:
      EcDataVcc = 0x08;
      break;
    case 6:
      EcDataVcc = 0xDA;
      break;
    default:
      EcDataVcc = 0x1A;
      break;
  }
  switch (SystemConfiguration->PmicVddqLevel) {
    case 0:
      EcDataVddq = 0x00;
      break;
    case 1:
      EcDataVddq = 0x01;
      break;
    case 2:
      EcDataVddq = 0x02;
      break;
    case 3:
      EcDataVddq = 0x03;
      break;
    case 4:
      EcDataVddq = 0x04;
      break;
    case 5:
      EcDataVddq = 0x05;
      break;
    case 6:
      EcDataVddq = 0x06;
      break;
    case 7:
      EcDataVddq = 0x07;
      break;
    default:
      EcDataVddq = 0x0A;
      break;
  }
  Status = SetPmicVoltage (EcDataVcc, EcDataVddq);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR(Status)) {
    return;
  }
}


/**
  Configure EC for specific devices

  @param[in] PchLan       - The PchLan of PCH_SETUP variable.
  @param[in] BootMode     - The current boot mode.
**/
VOID
EcInit (
  IN UINT8                PchLan,
  IN EFI_BOOT_MODE        BootMode
  )
{
  EFI_STATUS              Status;

  Status = EFI_SUCCESS;
  if (PchLan != PEI_DEVICE_DISABLED) {
    Status = EnableLanPower (TRUE);
  } else {
    Status = EnableLanPower (FALSE);
  }
  ASSERT_EFI_ERROR (Status);

  //
  // Clear 10sec PB Override mode in EC so that Power button is always available during POST.
  //
  ClearTenSecPwrButtonMode ();
}


/**
  This function returns the state of the MFG_MODE jumper.

  @retval TRUE              - The system is booting in manufacturing mode
  @retval FALSE             - Normal Boot
**/
BOOLEAN
IsManufacturingMode (
  VOID
  )
{
  BOOLEAN               ManufacturingMode;
  UINT32                ManufactureModeGpioVal;
  UINT8                 MfgModeGpio;

  ManufacturingMode = FALSE;

  if (PcdGet8 (PcdPlatformType) == TypeTrad) {
    GpioGetInputValue (MANUFACTURE_MODE_GPIO_PIN, &ManufactureModeGpioVal);
    ManufacturingMode = (BOOLEAN) ManufactureModeGpioVal;
  }

  if (PcdGet8 (PcdPlatformType) == TypeUltUlx) {
    MfgModeGpio = IoRead8 (PcdGet16 (PcdSioBaseAddress) + 0x0C);
    ManufacturingMode = (BOOLEAN) ((MfgModeGpio & 0x02) == 0);
  }

  return ManufacturingMode;
}
