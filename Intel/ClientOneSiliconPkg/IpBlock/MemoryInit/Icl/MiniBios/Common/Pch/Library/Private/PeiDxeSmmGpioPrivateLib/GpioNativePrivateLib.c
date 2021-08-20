/** @file
  This file contains routines for GPIO native and chipset specific purpose
  used by Reference Code only.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#include "MrcOemPlatform.h"

#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Private/Library/GpioPrivateLib.h>
#include <Private/GpioNativePads.h>
#include <Library/PchInfoLib.h>
#include "GpioNativePrivateLibInternal.h"
#include <Register/PchRegsGpio.h>
#include <Register/PchRegsSerialIo.h>

#ifndef MRC_MINIBIOS_BUILD
/**
  This function sets SCS SD card controller pins into native mode

  @param[in]  none

  @retval Status
**/
EFI_STATUS
GpioEnableScsSdCard (
  VOID
  )
{
  EFI_STATUS                Status;
  UINTN                     Index;
  GPIO_PAD_NATIVE_FUNCTION  *SdCardGpio;
  UINT32                    NumOfSdCardPins;
  GPIO_CONFIG               PwrEnConfig;

  GpioGetScsSdCardPins (
    &SdCardGpio,
    &NumOfSdCardPins
    );

  if (SdCardGpio == NULL) {
    return EFI_UNSUPPORTED;
  }

  //
  // We need to leave the PWREN#
  // GPIO pad unlocked since it is controlled at runtime
  // by ACPI code. It is a work around for our SD card
  // controller not respecting PWREN# invertion settings
  // during D3. Since this pad will be in GPIO mode when
  // SD controller is in D3 we need to set correct pad config.
  //
  GpioUnlockPadCfg (SdCardGpio[0].Pad);
  GpioGetPadConfig (SdCardGpio[0].Pad, &PwrEnConfig);
  PwrEnConfig.PadMode = SdCardGpio[0].Mode;
  PwrEnConfig.Direction = GpioDirOut;
  PwrEnConfig.HostSoftPadOwn = GpioHostOwnAcpi;
  PwrEnConfig.InterruptConfig = GpioIntDis;
  PwrEnConfig.PowerConfig = GpioHostDeepReset;
  PwrEnConfig.LockConfig = GpioPadUnlock;
  GpioSetPadConfig (SdCardGpio[0].Pad, &PwrEnConfig);

  for (Index = 1; Index < NumOfSdCardPins; Index++) {
    Status = GpioSetPadMode (SdCardGpio[Index].Pad, SdCardGpio[Index].Mode);
    if (EFI_ERROR (Status)) {
      return EFI_UNSUPPORTED;
    }

    //
    // SD Card Pins GPP_G0 - G4 require Native Termination
    // Index in mPch[Lp/H]ScsSdCardGpio (depends on mPch[Lp/H]ScsSdCardGpio internal organization):
    // GPP_G0 = 1
    // GPP_G4 = 5
    //
    if (Index >= 1 && Index <= 5) {
      Status = GpioSetPadElectricalConfig (SdCardGpio[Index].Pad, GpioTermNative);
      ASSERT_EFI_ERROR (Status);
    }
  }
  return EFI_SUCCESS;
}

/**
  This function enables SCS Sd Card controller card detect pin

  @param[in]  none

  @retval Status
**/
EFI_STATUS
GpioEnableScsSdCardDetect (
  VOID
  )
{
  GPIO_CONFIG   PadConfig;
  GPIO_PAD      GpioPad;

  ZeroMem (&PadConfig, sizeof (PadConfig));

  ///
  /// vSD3_CD_B line is driven by GPPC_G_5_SD3_CDB
  /// and is used for interrupt for card detect event.
  /// GPPC_G_5_SD3_CDB cannot be used for interrupt because this pin
  /// is in native mode.
  ///
  GpioPad = GpioGetScsSdCardDetectPin ();
  PadConfig.PadMode         = GpioPadModeGpio;
  PadConfig.Direction       = GpioDirIn;
  PadConfig.HostSoftPadOwn  = GpioHostOwnGpio;
  PadConfig.InterruptConfig = GpioIntBothEdge;
  PadConfig.PowerConfig     = GpioHostDeepReset;

  // Unlock GPIO pad due to Host Software Pad Ownership is GPIO Driver mode.
  GpioUnlockPadCfg (GpioPad);

  return GpioSetPadConfig (GpioPad, &PadConfig);
}
/**
  This function sets SCS eMMC controller pins into native mode

  @param[in]  none

  @retval Status
**/
EFI_STATUS
GpioEnableScsEmmc (
  VOID
  )
{
  EFI_STATUS                Status;
  UINTN                     Index;
  GPIO_PAD_NATIVE_FUNCTION  *EmmcGpio;
  UINT32                    NumOfEmmcPins;

  GpioGetScsEmmcPins (
    &EmmcGpio,
    &NumOfEmmcPins
    );

  if (EmmcGpio == NULL) {
    return EFI_UNSUPPORTED;
  }

  for (Index = 0; Index < NumOfEmmcPins; Index++) {
    Status = GpioSetPadMode (EmmcGpio[Index].Pad, EmmcGpio[Index].Mode);
    if (EFI_ERROR (Status)) {
      return EFI_UNSUPPORTED;
    }
  }
  return EFI_SUCCESS;
}

/**
  This function sets HDA SSP interface pins into native mode

  @param[in]  SspInterfaceNumber   SSPx interface number

  @retval Status
**/
EFI_STATUS
GpioEnableHdaSsp (
  IN  UINT32            SspInterfaceNumber
  )
{
  EFI_STATUS               Status;
  UINTN                    Index;
  GPIO_PAD_NATIVE_FUNCTION *SspGpio;

  GpioGetHdaSspPins (
    SspInterfaceNumber,
    &SspGpio
    );

  if (SspGpio == NULL) {
    return EFI_UNSUPPORTED;
  }

  for (Index = 0; Index < PCH_GPIO_HDA_SSP_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (SspGpio[Index].Pad, SspGpio[Index].Mode);
    if (EFI_ERROR (Status)) {
      return EFI_UNSUPPORTED;
    }
  }

  return EFI_SUCCESS;
}

/**
  This function sets HDA SoundWire interface pins into native mode

  @param[in]  SndwInterfaceNumber   SNDWx interface number

  @retval Status
**/
EFI_STATUS
GpioEnableHdaSndw (
  IN  UINT32            SndwInterfaceNumber
  )
{
  EFI_STATUS               Status;
  UINTN                    Index;
  GPIO_PAD_NATIVE_FUNCTION *SndwGpio;

  GpioGetHdaSndwPins (
    SndwInterfaceNumber,
    &SndwGpio
    );

  if (SndwGpio == NULL) {
    return EFI_UNSUPPORTED;
  }

  for (Index = 0; Index < PCH_GPIO_HDA_SNDW_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (SndwGpio[Index].Pad, SndwGpio[Index].Mode);
    if (EFI_ERROR (Status)) {
      return EFI_UNSUPPORTED;
    }
  }

  return EFI_SUCCESS;
}
#endif // MRC_MINIBIOS_BUILD

/**
  This function sets SMBUS controller pins into native mode

  @param[in]  none

  @retval Status
**/
EFI_STATUS
GpioEnableSmbus (
  VOID
  )
{
  EFI_STATUS               Status;
  UINTN                    Index;
  GPIO_PAD_NATIVE_FUNCTION *SmbusGpio;

  GpioGetSmbusPins (&SmbusGpio);

  if (SmbusGpio == NULL) {
    return EFI_UNSUPPORTED;
  }

  for (Index = 0; Index < PCH_GPIO_SMBUS_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (SmbusGpio[Index].Pad, SmbusGpio[Index].Mode);
    if (EFI_ERROR (Status)) {
      return EFI_UNSUPPORTED;
    }
  }

  return EFI_SUCCESS;
}

/**
  This function sets SATA DevSlp pins into native mode

  @param[in]  SataCtrlIndex       SATA controller index
  @param[in]  SataPort            SATA port number

  @retval Status
**/
EFI_STATUS
GpioEnableSataDevSlpPin (
  IN  UINT32  SataCtrlIndex,
  IN  UINTN   SataPort
  )
{
  GPIO_PAD_NATIVE_FUNCTION  DevSlpGpio;

  GpioGetSataDevSlpPin (
    SataCtrlIndex,
    SataPort,
    &DevSlpGpio
    );

  GpioSetPadResetConfig (DevSlpGpio.Pad, GpioResumeReset);

  return GpioSetPadMode (DevSlpGpio.Pad, DevSlpGpio.Mode);
}

/**
  This function checks if SataDevSlp pin is in native mode

  @param[in]  SataCtrlIndex       SATA controller index
  @param[in]  SataPort            SATA port
  @param[out] DevSlpPad           DevSlpPad
                                  This is an optional parameter and may be NULL.

  @retval TRUE                    DevSlp is in native mode
          FALSE                   DevSlp is not in native mode
**/
#ifndef MRC_MINIBIOS_BUILD
BOOLEAN
GpioIsSataDevSlpPinEnabled (
  IN  UINT32          SataCtrlIndex,
  IN  UINTN           SataPort,
  OUT GPIO_PAD        *DevSlpPad  OPTIONAL
  )
{
  GPIO_PAD_NATIVE_FUNCTION  DevSlpNativePad;
  GPIO_PAD_MODE             GpioMode;
  EFI_STATUS                Status;

  ASSERT (SataCtrlIndex < GetPchMaxSataControllerNum ());

  GpioGetSataDevSlpPin (
    SataCtrlIndex,
    SataPort,
    &DevSlpNativePad
    );

  Status = GpioGetPadMode (DevSlpNativePad.Pad, &GpioMode);

  if (EFI_ERROR (Status) || (GpioMode != DevSlpNativePad.Mode)) {
    if (DevSlpPad != NULL) {
      *DevSlpPad = GPIO_PAD_NONE;
    }
    return FALSE;
  } else {
    if (DevSlpPad != NULL) {
      *DevSlpPad = DevSlpNativePad.Pad;
    }
    return TRUE;
  }
}
#endif // MRC_MINIBIOS_BUILD
/**
  This function sets SATAGPx pin into native mode

  @param[in]  SataCtrlIndex       SATA controller index
  @param[in]  SataPort            SATA port number

  @retval Status
**/
EFI_STATUS
GpioEnableSataGpPin (
  IN  UINT32  SataCtrlIndex,
  IN  UINTN   SataPort
  )
{
  GPIO_PAD_NATIVE_FUNCTION  SataGpGpio;

  GpioGetSataGpPin (
    SataCtrlIndex,
    SataPort,
    &SataGpGpio
    );

  DEBUG_CODE_BEGIN ();
  GPIO_PAD_MODE  PadMode;
  GpioGetPadMode (SataGpGpio.Pad, &PadMode);
  if (PadMode == GpioPadModeNative1) {
    DEBUG ((DEBUG_ERROR, "GPIO ERROR: Cannot enable SATAGP%d, %a already used for SATAXPCIE_%d\n",
        SataPort,
        GpioName (SataGpGpio.Pad),
        SataPort));
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }
  DEBUG_CODE_END ();

  return GpioSetPadMode (SataGpGpio.Pad, SataGpGpio.Mode);
}

/**
  Returns a pad for given CLKREQ# index.

  @param[in]  ClkreqIndex       CLKREQ# number

  @return CLKREQ# pad.
**/
GPIO_PAD
GpioGetClkreqPad (
  IN     UINT32   ClkreqIndex
  )
{
  GPIO_PAD_NATIVE_FUNCTION  ClkReqGpio;

  GpioGetPcieClkReqPin (
    ClkreqIndex,
    &ClkReqGpio
    );

  return ClkReqGpio.Pad;
}

/**
  Enables CLKREQ# pad in native mode.

  @param[in]  ClkreqIndex       CLKREQ# number

  @return none
**/
#ifndef MRC_MINIBIOS_BUILD
VOID
GpioEnableClkreq (
  IN     UINT32   ClkreqIndex
  )
{
  GPIO_CONFIG               PadConfig;
  GPIO_PAD_NATIVE_FUNCTION  ClkReqGpio;

  ZeroMem (&PadConfig, sizeof (PadConfig));

  GpioGetPcieClkReqPin (
    ClkreqIndex,
    &ClkReqGpio
    );

  PadConfig.PadMode      = ClkReqGpio.Mode;
  PadConfig.Direction    = GpioDirNone;
  PadConfig.PowerConfig  = GpioHostDeepReset;
  DEBUG ((DEBUG_INFO, "Enabling CLKREQ%d\n", ClkreqIndex));
  GpioSetPadConfig (ClkReqGpio.Pad, &PadConfig);
}
#endif // MRC_MINIBIOS_BUILD

/**
  This function sets DDP pins into native mode

  @param[in]  DdpInterface   DDPx interface

  @retval Status
**/
EFI_STATUS
GpioEnableDpInterface (
  IN  GPIO_DDP            DdpInterface
  )
{
  EFI_STATUS               Status;
  UINTN                    Index;
  GPIO_PAD_NATIVE_FUNCTION *DdpGpio;

  GpioGetDdpPins (
    DdpInterface,
    &DdpGpio
    );

  if (DdpGpio == NULL) {
    return EFI_UNSUPPORTED;
  }

  for (Index = 0; Index < PCH_GPIO_DDP_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (DdpGpio[Index].Pad, DdpGpio[Index].Mode);
    if (EFI_ERROR (Status)) {
      return EFI_UNSUPPORTED;
    }
  }

  return EFI_SUCCESS;
}

/**
  This function configures GPIO connection between CNVi and CRF
  @param[in]  None

  @retval Status
**/
EFI_STATUS
GpioConfigureCnviCrfConnection (
  VOID
  )
{
  EFI_STATUS               Status;
  UINT32                   Index;
  GPIO_PAD_NATIVE_FUNCTION *CnviBriRgiExternalPad;

  GpioGetCnvBriRgiPins (&CnviBriRgiExternalPad);

  if (CnviBriRgiExternalPad == NULL) {
    return EFI_UNSUPPORTED;
  }

  //
  // Configure CNVi BRI and RGI buses for high speed communication with CRF
  //
  for (Index = 0; Index < PCH_GPIO_CNVI_BRI_RGI_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (CnviBriRgiExternalPad[Index].Pad, CnviBriRgiExternalPad[Index].Mode);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return EFI_UNSUPPORTED;
    }
  }
  return EFI_SUCCESS;
}

/**
  This function checks if provided pin can potentially be a CNVi CRF connection pin

  @param[in]  GpioNativePad

  @retval TRUE: GpioPad can be used for CNVi CRF
          FALSE: GpioPad is different than CNVi CRF pins
**/
BOOLEAN
GpioIsCnviCrfPin (
  IN GPIO_NATIVE_PAD   GpioNativePad
  )
{
  UINT32                   Index;
  GPIO_PAD_NATIVE_FUNCTION *CnviBriRgiExternalPad;

  GpioGetCnvBriRgiPins (&CnviBriRgiExternalPad);

  if (CnviBriRgiExternalPad == NULL) {
    return FALSE;
  }

  for (Index = 0; Index < PCH_GPIO_CNVI_BRI_RGI_NUMBER_OF_PINS; Index++) {
    if (GPIO_NATIVE_GET_GPIO_PAD (GpioNativePad) == CnviBriRgiExternalPad[Index].Pad) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  This function configures virtual GPIO connection for CNVi Bluetooth UART

  @param[in]  ConnectionType

  @retval Status
**/
EFI_STATUS
GpioConfigureCnviBtUartConnection (
  IN  VGPIO_CNVI_BT_UART_CONNECTION_TYPE  ConnectionType
  )
{
  EFI_STATUS               Status;
  UINT32                   Index;
  GPIO_PAD                 *VCnviBtUartPad;
  GPIO_PAD_MODE            VCnviBtUartPadMode;
  GPIO_PAD                 *VUartForCnviBtPad;
  GPIO_PAD_MODE            VUartForCnviBtPadMode;
  GPIO_PAD_NATIVE_FUNCTION *CnviBtUartExternalPad;

  GpioGetCnviBtUartPins (
    ConnectionType,
    &VCnviBtUartPad,
    &VCnviBtUartPadMode,
    &VUartForCnviBtPad,
    &VUartForCnviBtPadMode
    );

  if ((VCnviBtUartPad == NULL) ||
      (VUartForCnviBtPad == NULL)) {
    return EFI_UNSUPPORTED;
  }

  //
  // Configure CNVi Bluetooth UART for certain connection
  //
  for (Index = 0; Index < PCH_GPIO_CNVI_UART_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (VCnviBtUartPad[Index], VCnviBtUartPadMode);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return EFI_UNSUPPORTED;
    }
  }

  //
  // Enable virtual connection for UART for Bluetooth
  //
  for (Index = 0; Index < PCH_GPIO_CNVI_UART_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (VUartForCnviBtPad[Index], VUartForCnviBtPadMode);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return EFI_UNSUPPORTED;
    }
  }

  //
  // Enable CNVi BT UART on external pads
  //
  if (ConnectionType == GpioCnviBtUartToExternalPads) {

    GpioGetCnviBtUartExternalPins (&CnviBtUartExternalPad);

    if (CnviBtUartExternalPad == NULL) {
      return EFI_UNSUPPORTED;
    }

    for (Index = 0; Index < PCH_GPIO_CNVI_UART_NUMBER_OF_PINS; Index++) {
      Status = GpioSetPadMode (CnviBtUartExternalPad[Index].Pad, CnviBtUartExternalPad[Index].Mode);
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
        return EFI_UNSUPPORTED;
      }
    }
  }
  return EFI_SUCCESS;
}

/**
  This function configures virtual GPIO connection for CNVi Bluetooth I2S

  @param[in]  ConnectionType

  @retval Status
**/
EFI_STATUS
GpioConfigureCnviBtI2sConnection (
  IN  VGPIO_CNVI_BT_I2S_CONNECTION_TYPE  ConnectionType
  )
{
  EFI_STATUS               Status;
  UINT32                   Index;
  GPIO_PAD                 *VCnviBtI2sPad;
  GPIO_PAD_MODE            VCnviBtI2sPadMode;
  GPIO_PAD                 *VSspForCnviBtPad;
  GPIO_PAD_MODE            VSspForCnviBtPadMode;
  GPIO_PAD_NATIVE_FUNCTION *CnviBtI2sExternalPad;

  GpioGetCnviBtI2sPins (
    ConnectionType,
    &VCnviBtI2sPad,
    &VCnviBtI2sPadMode,
    &VSspForCnviBtPad,
    &VSspForCnviBtPadMode
    );

  if ((VCnviBtI2sPad == NULL) ||
      (VSspForCnviBtPad == NULL)) {
    return EFI_UNSUPPORTED;
  }

  //
  // Configure CNVi Bluetooth I2S for certain connection
  //
  for (Index = 0; Index < PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (VCnviBtI2sPad[Index], VCnviBtI2sPadMode);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return EFI_UNSUPPORTED;
    }
  }

  //
  // Enable virtual connection for SSP for Bluetooth
  //
  for (Index = 0; Index < PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (VSspForCnviBtPad[Index], VSspForCnviBtPadMode);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return EFI_UNSUPPORTED;
    }
  }

  //
  // Enable CNV BT I2S on external pads
  //
  if (ConnectionType == (VGPIO_CNVI_BT_I2S_CONNECTION_TYPE) GpioCnviBtI2sToExternalPads) {

    GpioGetCnviBtI2sExternalPins (&CnviBtI2sExternalPad);

    if (CnviBtI2sExternalPad == NULL) {
      return EFI_UNSUPPORTED;
    }

    for (Index = 0; Index < PCH_GPIO_CNVI_SSP_NUMBER_OF_PINS; Index++) {
      Status = GpioSetPadMode (CnviBtI2sExternalPad[Index].Pad, CnviBtI2sExternalPad[Index].Mode);
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
        return EFI_UNSUPPORTED;
      }
    }
  }
  return EFI_SUCCESS;
}

/**
  This function configures virtual GPIO connection for CNVi MFUART1

  @param[in]  ConnectionType

  @retval Status
**/
EFI_STATUS
GpioConfigureCnviMfUart1Connection (
  IN  VGPIO_CNVI_MF_UART1_CONNECTION_TYPE  ConnectionType
  )
{
  EFI_STATUS               Status;
  UINT32                   Index;
  GPIO_PAD                 *VCnviMfUart1Pad;
  GPIO_PAD_MODE            VCnviMfUart1PadMode;
  GPIO_PAD                 *VUartForCnviMfUart1Pad;
  GPIO_PAD_MODE            VUartForCnviMfUart1PadMode;
  GPIO_PAD_NATIVE_FUNCTION *CnviMfUart1ExternalPad;

  GpioGetCnviMfUart1Pins (
    ConnectionType,
    &VCnviMfUart1Pad,
    &VCnviMfUart1PadMode,
    &VUartForCnviMfUart1Pad,
    &VUartForCnviMfUart1PadMode
    );

  if ((VCnviMfUart1Pad == NULL) ||
      (VUartForCnviMfUart1Pad == NULL)) {
    return EFI_UNSUPPORTED;
  }

  //
  // Configure CNVi MFUART1 for certain connection
  //
  for (Index = 0; Index < PCH_GPIO_CNVI_UART_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (VCnviMfUart1Pad[Index], VCnviMfUart1PadMode);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return EFI_UNSUPPORTED;
    }
  }

  //
  // Enable virtual connection for MFUART1
  //
  for (Index = 0; Index < PCH_GPIO_CNVI_UART_NUMBER_OF_PINS; Index++) {
    Status = GpioSetPadMode (VUartForCnviMfUart1Pad[Index], VUartForCnviMfUart1PadMode);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return EFI_UNSUPPORTED;
    }
  }

  //
  // Enable CNV MFUART1 on external pads
  //
  if (ConnectionType == GpioCnviMfUart1ToExternalPads) {

    GpioGetCnviMfUart1ExternalPins (&CnviMfUart1ExternalPad);

    if (CnviMfUart1ExternalPad == NULL) {
      return EFI_UNSUPPORTED;
    }

    for (Index = 0; Index < PCH_GPIO_CNVI_UART_NUMBER_OF_PINS; Index++) {
      Status = GpioSetPadMode (CnviMfUart1ExternalPad[Index].Pad, CnviMfUart1ExternalPad[Index].Mode);
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
        return EFI_UNSUPPORTED;
      }
    }
  }
  return EFI_SUCCESS;
}

#ifndef MRC_MINIBIOS_BUILD
/**
  This function sets CNVi Bluetooth Enable value

  @param[in] Value                CNVi BT enable value
                                  0: Disable, 1: Enable
  @retval Status
**/
EFI_STATUS
GpioSetCnviBtEnState (
  IN  UINT32  Value
  )
{
  EFI_STATUS  Status;
  GPIO_PAD    CnviBtEnPad;
  GPIO_CONFIG PadConfig;

  ZeroMem (&PadConfig, sizeof (PadConfig));

  PadConfig.PadMode        = GpioPadModeGpio;
  PadConfig.HostSoftPadOwn = GpioHostOwnGpio;
  PadConfig.Direction      = GpioDirOut;
  if (Value == 1) {
    PadConfig.OutputState  = GpioOutHigh;
  } else {
    PadConfig.OutputState  = GpioOutLow;
  }
  CnviBtEnPad = GpioGetCnviBtEnablePin ();

  // Unlock GPIO pad due to Host Software Pad Ownership is GPIO Driver mode and it is GPO
  GpioUnlockPadCfg (CnviBtEnPad);
  GpioUnlockPadCfgTx (CnviBtEnPad);
  Status = GpioSetPadConfig (CnviBtEnPad, &PadConfig);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  This function sets CNVi Bluetooth main host interface

  @param[in] BtInterface          CNVi BT Interface Select value
                                  GpioCnviBtIfUart: UART, GpioCnviBtIfUsb: USB
  @retval Status
**/
EFI_STATUS
GpioSetCnviBtInterface (
  IN  VGPIO_CNVI_BT_INTERFACE  BtInterface
  )
{
  EFI_STATUS  Status;
  GPIO_CONFIG PadConfig;

  ZeroMem (&PadConfig, sizeof (PadConfig));

  PadConfig.PadMode        = GpioPadModeGpio;
  PadConfig.Direction      = GpioDirOut;
  if (BtInterface == GpioCnviBtIfUsb) {
    PadConfig.OutputState  = GpioOutHigh;
  } else {
    PadConfig.OutputState  = GpioOutLow;
  }

  Status = GpioSetPadConfig (GpioGetCnviBtIfSelectPin (), &PadConfig);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  This function sets CNVi Bluetooth Wireless Charging support

  @param[in] BtWirelessCharging   CNVi BT Wireless Charging support
                                  0: Normal BT operation (no Wireless Charging support)
                                  1: Enable BT Wireless Charging
  @retval Status
**/
EFI_STATUS
GpioSetCnviBtWirelessCharging (
  IN  UINT32  BtWirelessCharging
  )
{
  EFI_STATUS                Status;
  GPIO_CONFIG               CnviBtChargingPadConfig;
  GPIO_PAD_NATIVE_FUNCTION  A4WpPad;

  ZeroMem (&CnviBtChargingPadConfig, sizeof (CnviBtChargingPadConfig));

  CnviBtChargingPadConfig.PadMode        = GpioPadModeGpio;
  CnviBtChargingPadConfig.Direction      = GpioDirOut;

  if (BtWirelessCharging == 1) {
    CnviBtChargingPadConfig.OutputState  = GpioOutHigh;

    GpioGetCnviA4WpPin (&A4WpPad);

    Status = GpioSetPadMode (A4WpPad.Pad, A4WpPad.Mode);
    ASSERT_EFI_ERROR (Status);

  } else {
    CnviBtChargingPadConfig.OutputState  = GpioOutLow;
  }

  Status = GpioSetPadConfig (GpioGetCnviBtChargingPin (), &CnviBtChargingPadConfig);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  This function enables and configures CNVi Bluetooth Host wake-up interrupt

  @param[in] None

  @retval Status
**/
EFI_STATUS
GpioConfigureCnviBtHostWakeInt (
  VOID
  )
{
  EFI_STATUS  Status;
  GPIO_PAD    CnviBtHostWakeIntPad;
  GPIO_CONFIG PadConfig;

  ZeroMem (&PadConfig, sizeof (PadConfig));

  PadConfig.PadMode = GpioPadModeGpio;
  PadConfig.Direction = GpioDirIn;
  PadConfig.HostSoftPadOwn = GpioHostOwnGpio;
  PadConfig.InterruptConfig = GpioIntEdge;
  PadConfig.PowerConfig  = GpioHostDeepReset;
  CnviBtHostWakeIntPad = GpioGetCnviBtHostWakeIntPin ();

  // Unlock GPIO pad due to Host Software Pad Ownership is GPIO Driver mode.
  GpioUnlockPadCfg (CnviBtHostWakeIntPad);
  Status = GpioSetPadConfig (CnviBtHostWakeIntPad, &PadConfig);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  This function enables IMGU CLKOUT native pin

  @param[in] ImguClkOutPinIndex    The index of IMGU CLKOUT natine pin

  @retval Status
**/
EFI_STATUS
GpioEnableImguClkOut (
  IN UINT8 ImguClkOutPinIndex
  )
{
  EFI_STATUS                Status;
  GPIO_PAD_NATIVE_FUNCTION  *ImguClkOutGpio;
  UINT32                    NoOfNativePins;

  GpioGetImgClkOutPins (
    &ImguClkOutGpio,
    &NoOfNativePins
    );

  if (ImguClkOutGpio == NULL) {
    return EFI_UNSUPPORTED;
  }

  if (ImguClkOutPinIndex >= NoOfNativePins) {
    return EFI_UNSUPPORTED;
  }

  Status = GpioSetPadMode (ImguClkOutGpio[ImguClkOutPinIndex].Pad, ImguClkOutGpio[ImguClkOutPinIndex].Mode);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
  Power button debounce configuration
  Debounce time can be specified in microseconds. Only certain values according
  to below formula are supported:
   DebounceTime = (2 ^ PADCFG_DW2.DEBOUNCE)*(glitch filter clock period).
  RTC clock with f = 32 KHz is used for glitch filter.
   DebounceTime = (2 ^ PADCFG_DW2.DEBOUNCE)*(31.25 us).
  Supported DebounceTime values are following:
   DebounceTime = 0 -> Debounce feature disabled
   DebounceTime > 0 && < 250us -> Not supported
   DebounceTime = 250us - 1024000us -> Supported range (DebounceTime = 250us * 2^n)
  For values not supported by HW, they will be rounded down to closest supported one

  @param[in] DebounceTime    Debounce Time in microseconds
                             If Debounce Time = 0, Debouncer feature will be disabled
                             Function will set DebounceTime argument to rounded supported value
**/
VOID
GpioSetPwrBtnDebounceTimer (
  IN UINT32                DebounceTime
  )
{
  GpioSetDebounceTimer (GpioGetPwrBtnPin (), &DebounceTime);
}
#endif // MRC_MINIBIOS_BUILD
