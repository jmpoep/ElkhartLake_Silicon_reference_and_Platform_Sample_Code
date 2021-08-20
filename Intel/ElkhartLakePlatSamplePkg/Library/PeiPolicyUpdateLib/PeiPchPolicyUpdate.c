/** @file
  This file is SampleCode of the library for Intel PCH PEI Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2020 Intel Corporation.

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

#include <Library/PeiPchPolicyUpdate.h>
#include "PeiPchPolicyUpdate.h"
#include <Guid/GlobalVariable.h>
#include <Guid/FmpCapsule.h>
#include <Ppi/PeiDTbtPolicy.h>
#include <Ppi/Spi.h>
#include <Library/SiPolicyLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/HobLib.h>
#include <Library/GbeLib.h>
#include <Library/PchInfoLib.h>
#include <Library/SataLib.h>
#include <Library/PchPcieRpLib.h>
#include <Library/PchPolicyLib.h>
#include <Library/RstCrLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Library/SerialPortParameterLib.h>
#include <Library/GpioConfig.h>
#include <Library/DebugLib.h>
#include <Library/CnviLib.h>
#include <SerialIoDevices.h>
#include <PlatformBoardConfig.h>
#include <Setup.h>
#include <Pins/GpioPinsVer3.h>
#include <Pins/GpioPinsVer1N.h>
#include <Library/PeiTsnMacAddrFvLib.h>
#include <Library/PeiPseTsnIpConfigFvLib.h>
#include <Library/PeiTsnConfigFvLib.h>
#include <Library/PeiSiipFvLib.h>
#include <Library/BootMediaLib.h>
#include <Library/PeiServicesLib.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspmUpd.h>
#include <FspsUpd.h>
#endif


#if FixedPcdGetBool(PcdCapsuleEnable) == 1
#include <Guid/SysFwUpdateProgress.h>

/**
  Return if input ImageGuid belongs to a FMP device which would perform BIOS update

  @param[in] ImageGuid A pointer to GUID

  @retval TRUE  ImageGuid belongs to a FMP which would perform BIOS update
  @retval FALSE ImageGuid does not belong to a FMP which would perform BIOS update

**/
BOOLEAN
IsFmpGuidForBiosUpdate (
  IN EFI_GUID   *ImageGuid
  )
{
  if (CompareGuid (ImageGuid, &gFmpDevicePlatformMonolithicGuid)  || \
      CompareGuid (ImageGuid, &gFmpCapsuleTsnMacAddrFileGuid)     || \
      CompareGuid (ImageGuid, &gFmpCapsulePseTsnIpConfigFileGuid) || \
      CompareGuid (ImageGuid, &gFmpCapsuleTsnConfigFileGuid)      || \
      CompareGuid (ImageGuid, &gFmpCapsuleSiipFwFileGuid)         || \
      CompareGuid (ImageGuid, &gFmpCapsuleOobConfigFileGuid)      || \
      CompareGuid (ImageGuid, &gFmpCapsuleTccConfigFileGuid)      || \
      CompareGuid (ImageGuid, &gFmpDevicePlatformBiosGuid)) {
    return TRUE;
  }

  return FALSE;
}

/**
  Detect if there is a FMP capsule which would perform BIOS update

  @retval TRUE        Such capsule is detected.
  @retval FALSE       No such capsules there.

**/
BOOLEAN
IsFmpCapsuleForBiosUpdateDetected (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS                          HobPointer;
  EFI_CAPSULE_HEADER                            *CapsuleHeader;
  EFI_FIRMWARE_MANAGEMENT_CAPSULE_HEADER        *FmpCapsuleHeader;
  EFI_FIRMWARE_MANAGEMENT_CAPSULE_IMAGE_HEADER  *ImageHeader;
  UINTN                                         Index;
  UINT64                                        *ItemOffsetList;

  //
  // Search all capsule images from hob
  //
  HobPointer.Raw = GetHobList ();
  while ((HobPointer.Raw = GetNextHob (EFI_HOB_TYPE_UEFI_CAPSULE, HobPointer.Raw)) != NULL) {
    CapsuleHeader = (EFI_CAPSULE_HEADER *) (UINTN) HobPointer.Capsule->BaseAddress;

    //
    // Must be a nested FMP capsule or FMP capsule with pre-defined GUIDs
    //
    if (IsFmpGuidForBiosUpdate (&CapsuleHeader->CapsuleGuid)) {
      CapsuleHeader = (EFI_CAPSULE_HEADER *)((UINT8 *)CapsuleHeader + CapsuleHeader->HeaderSize);
    }

    if (!CompareGuid (&gEfiFmpCapsuleGuid, &CapsuleHeader->CapsuleGuid)) {
      HobPointer.Raw = GET_NEXT_HOB (HobPointer);
      continue;
    }

    FmpCapsuleHeader = (EFI_FIRMWARE_MANAGEMENT_CAPSULE_HEADER *)((UINT8 *)CapsuleHeader + CapsuleHeader->HeaderSize);
    ItemOffsetList = (UINT64 *)(FmpCapsuleHeader + 1);
    for (Index = FmpCapsuleHeader->EmbeddedDriverCount; Index < (UINT32)FmpCapsuleHeader->EmbeddedDriverCount + FmpCapsuleHeader->PayloadItemCount; Index++) {
      ImageHeader = (EFI_FIRMWARE_MANAGEMENT_CAPSULE_IMAGE_HEADER *)((UINT8 *)FmpCapsuleHeader + ItemOffsetList[Index]);
      if (IsFmpGuidForBiosUpdate (&ImageHeader->UpdateImageTypeId)) {
        DEBUG ((DEBUG_INFO, "A FMP capsule for BIOS update is detected.\n"));
        return TRUE;
      }
    }

    HobPointer.Raw = GET_NEXT_HOB (HobPointer);
  }

  return FALSE;
}

/**
  Check if BIOS Update is going to happen during this boot.

  This function checks:
  1. If BootMode is BOOT_ON_FLASH_UPDATE and there is a Capsule to update BIOS region detected.
  2. If BIOS update is in progress in the last boot.
  If one of above confictions stands, set a GUID HOB as an indication to be consumed in DXE/BDS
  and return TRUE. Otherwise, return FALSE.

  @retval TRUE       BIOS Update is going to happen during this boot.
  @retval FALSE      No request of BIOS update is detected.

**/
STATIC
BOOLEAN
IsBiosUpdateRequired (
  VOID
  )
{
  EFI_HOB_GUID_TYPE               *GuidHob;

  GuidHob                 = NULL;

  GuidHob = GetFirstGuidHob (&gSysFwUpdateProgressGuid);

  if (((GetBootModeHob () == BOOT_ON_FLASH_UPDATE) && IsFmpCapsuleForBiosUpdateDetected ()) || \
      ((GuidHob != NULL) && \
       (((SYSTEM_FIRMWARE_UPDATE_PROGRESS *) GET_GUID_HOB_DATA (GuidHob))->Component == UpdatingBios))) {
    //
    // Build gSkipBiosLockForSysFwUpdateGuid HOB if it does not exist.
    //
    GuidHob = GetFirstGuidHob (&gSkipBiosLockForSysFwUpdateGuid);
    if (GuidHob == NULL) {
      DEBUG ((DEBUG_INFO, "Build gSkipBiosLockForSysFwUpdateGuid HOB to reset system before EndOfDxe\n"));
      BuildGuidHob (&gSkipBiosLockForSysFwUpdateGuid, 0);
    }

    return TRUE;
  }

  return FALSE;
}

#else // FixedPcdGetBool(PcdCapsuleEnable) != 1
/**
  Check if BIOS Update is going to happen during this boot.

  @retval TRUE       BIOS Update is going to happen during this boot.
  @retval FALSE      No request of BIOS update is detected.

**/
STATIC
BOOLEAN
IsBiosUpdateRequired (
  VOID
  )
{
  return FALSE;
}
#endif

/**
  Add verb table helper function.
  This function calculates verbtable number and shows verb table information.

  @param[in,out] VerbTableEntryNum      Input current VerbTable number and output the number after adding new table
  @param[in,out] VerbTableArray         Pointer to array of VerbTable
  @param[in]     VerbTable              VerbTable which is going to add into array
**/
STATIC
VOID
InternalAddVerbTable (
  IN OUT  UINT8                   *VerbTableEntryNum,
  IN OUT  UINT32                  *VerbTableArray,
  IN      HDAUDIO_VERB_TABLE      *VerbTable
  )
{
  if (VerbTable == NULL) {
    DEBUG ((DEBUG_INFO, "InternalAddVerbTable wrong input: VerbTable == NULL\n"));
    return;
  }

  VerbTableArray[*VerbTableEntryNum] = (UINT32) VerbTable;
  *VerbTableEntryNum += 1;

  DEBUG ((DEBUG_INFO,
    "HDA: Add verb table for vendor = 0x%04X devId = 0x%04X (size = %d DWords)\n",
    VerbTable->Header.VendorId,
    VerbTable->Header.DeviceId,
    VerbTable->Header.DataDwords)
    );
}

enum HDAUDIO_CODEC_SELECT {
  PchHdaCodecPlatformOnboard = 0,
  PchHdaCodecExternalKit     = 1
};

/**
  Add verb table function.
  This function update the verb table number and verb table ptr of policy.

  @param[in] HdAudioConfig            HDAudio config block
  @param[in] HdAudioPreMemConfig      HDAudio PreMem config block
  @param[in] FspsUpd                  A VOID pointer
  @param[in] FspmUpd                  A VOID pointer
  @param[in] CodecType                Platform codec type indicator
**/
STATIC
VOID
InternalAddPlatformVerbTables (
  IN  HDAUDIO_CONFIG                  *HdAudioConfig,
  IN  HDAUDIO_PREMEM_CONFIG           *HdAudioPreMemConfig,
  IN  VOID                            *FspsUpd,
  IN  VOID                            *FspmUpd,
  IN  UINT8                           CodecType
  )
{
  UINT8                           VerbTableEntryNum;
  UINT32                          VerbTableArray[6];
  UINT32                          *VerbTablePtr;
  BOOLEAN                         LinkEnable;

  VerbTableEntryNum = 0;

  InternalAddVerbTable (&VerbTableEntryNum, VerbTableArray, (VOID *) (UINTN) PcdGet32 (PcdDisplayAudioHdaVerbTable));

  GET_POLICY (!!((FSPM_UPD *)FspmUpd)->FspmConfig.PchHdaAudioLinkHdaEnable, !!HdAudioPreMemConfig->AudioLinkHda.Enable, LinkEnable);
  if (LinkEnable) {
    if (CodecType == PchHdaCodecPlatformOnboard) {
      DEBUG ((DEBUG_INFO, "HDA Policy: Onboard codec selected\n"));
      InternalAddVerbTable (&VerbTableEntryNum, VerbTableArray, (VOID *) (UINTN) PcdGet32 (PcdHdaVerbTable));
      InternalAddVerbTable (&VerbTableEntryNum, VerbTableArray, (VOID *) (UINTN) PcdGet32 (PcdHdaVerbTable2));
    } else {
      DEBUG ((DEBUG_INFO, "HDA Policy: External codec kit selected\n"));
      InternalAddVerbTable (&VerbTableEntryNum, VerbTableArray, (VOID *) (UINTN) PcdGet32 (PcdCommonHdaVerbTable1));
      InternalAddVerbTable (&VerbTableEntryNum, VerbTableArray, (VOID *) (UINTN) PcdGet32 (PcdCommonHdaVerbTable2));
      InternalAddVerbTable (&VerbTableEntryNum, VerbTableArray, (VOID *) (UINTN) PcdGet32 (PcdCommonHdaVerbTable3));
    }
  }

  UPDATE_POLICY (((FSPS_UPD *)FspsUpd)->FspsConfig.PchHdaVerbTableEntryNum, HdAudioConfig->VerbTableEntryNum, VerbTableEntryNum);

  VerbTablePtr = (UINT32 *) AllocateZeroPool (sizeof (UINT32) * VerbTableEntryNum);
  CopyMem (VerbTablePtr, VerbTableArray, sizeof (UINT32) * VerbTableEntryNum);
  UPDATE_POLICY (((FSPS_UPD *)FspsUpd)->FspsConfig.PchHdaVerbTablePtr, HdAudioConfig->VerbTablePtr, (UINT32) VerbTablePtr);
}

/**
  This is helper function for getting I2C Pads Internal Termination settings from Pcd

  @param[in]  Index            I2C Controller Index
**/
UINT8
STATIC
GetSerialIoI2cPadsTerminationFromPcd (
  IN UINT8 Index
  )
{
  switch (Index) {
    case 0:
      return PcdGet8 (PcdPchSerialIoI2c0PadInternalTerm);
    case 1:
      return PcdGet8 (PcdPchSerialIoI2c1PadInternalTerm);
    case 2:
      return PcdGet8 (PcdPchSerialIoI2c2PadInternalTerm);
    case 3:
      return PcdGet8 (PcdPchSerialIoI2c3PadInternalTerm);
    case 4:
      return PcdGet8 (PcdPchSerialIoI2c4PadInternalTerm);
    case 5:
      return PcdGet8 (PcdPchSerialIoI2c5PadInternalTerm);
    case 6:
      return PcdGet8 (PcdPchSerialIoI2c6PadInternalTerm);
    case 7:
      return PcdGet8 (PcdPchSerialIoI2c7PadInternalTerm);
    default:
      ASSERT (FALSE); // Invalid I2C Controller Index
  }
  return 0;
}

/**
  This function performs PCH Serial IO Platform Policy initialization

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              A VOID pointer
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
  @param[in] DebugConfigData      Pointer to DEBUG_CONFIG_DATA buffer
  @param[in] SetupVariables       Pointer to SETUP_DATA buffer
**/
VOID
UpdateSerialIoConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup,
  IN DEBUG_CONFIG_DATA         *DebugConfigData,
  IN SETUP_DATA                *SetupVariables
  )
{
  UINT8             Index;
  UINT8             CsIndex;
  SERIAL_IO_CONFIG  *SerialIoConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS        Status;
#endif

  SerialIoConfig = NULL;

#if FixedPcdGet8(PcdFspModeSelection) == 0
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSerialIoConfigGuid, (VOID *) &SerialIoConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#endif

  //
  // SPI
  //
  for (Index = 0; Index < GetPchMaxSerialIoSpiControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoSpiMode[Index], SerialIoConfig->SpiDeviceConfig[Index].Mode, (UINT8)(SERIAL_IO_SPI_MODE)PchSetup->PchSerialIoSpi[Index]);
  }

  for (Index = 0; Index < GetPchMaxSerialIoSpiControllersNum (); Index++) {
    for (CsIndex = 0; CsIndex < PCH_MAX_SERIALIO_SPI_CHIP_SELECTS; CsIndex++) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoSpiCsPolarity[PCH_MAX_SERIALIO_SPI_CHIP_SELECTS * Index + CsIndex], SerialIoConfig->SpiDeviceConfig[Index].CsPolarity[CsIndex], PchSetup->PchSpiCsPolarity[PCH_MAX_SERIALIO_SPI_CHIP_SELECTS * Index + CsIndex]);
    }
  }

  //
  // SPI1 chip select polarity must be adjusted to connected peripheral device
  //
  switch (SetupVariables->PchSpiFingerPrintType) {
    case 1: //FPC1011
    case 2: //FPC1020
    case 6: //FPC1021
    default:
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoSpiCsPolarity[2], SerialIoConfig->SpiDeviceConfig[1].CsPolarity[0], SerialIoSpiCsActiveLow);
      break;
  }

  //
  // I2C
  //
  for (Index = 0; Index < GetPchMaxSerialIoI2cControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoI2cMode[Index], SerialIoConfig->I2cDeviceConfig[Index].Mode, (UINT8)(SERIAL_IO_I2C_MODE)PchSetup->PchSerialIoI2c[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchSerialIoI2cPadsTermination[Index], SerialIoConfig->I2cDeviceConfig[Index].PadTermination, GetSerialIoI2cPadsTerminationFromPcd (Index));
  }
  if (IsPchH ()) {
    for (Index = 4; Index < 8; Index++) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoI2cMode[Index], SerialIoConfig->I2cDeviceConfig[Index].Mode, SerialIoI2cDisabled);
    }
  }
  if (IsPchLp ()) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchSerialIoI2cSdaPinMux[4],  SerialIoConfig->I2cDeviceConfig[4].PinMux.Sda,  GPIO_VER3_MUXING_SERIALIO_I2C4_SDA_GPP_H8);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchSerialIoI2cSclPinMux[4],  SerialIoConfig->I2cDeviceConfig[4].PinMux.Scl,  GPIO_VER3_MUXING_SERIALIO_I2C4_SCL_GPP_H9);
  }


  //
  // UART
  //
  for (Index = 0; Index < GetPchMaxSerialIoUartControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartMode[Index],       SerialIoConfig->UartDeviceConfig[Index].Mode,                (UINT8)(SERIAL_IO_UART_MODE)PchSetup->PchSerialIoUart[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartAutoFlow[Index],   SerialIoConfig->UartDeviceConfig[Index].Attributes.AutoFlow, PchSetup->PchUartHwFlowCtrl[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartPowerGating[Index],SerialIoConfig->UartDeviceConfig[Index].PowerGating,         PchSetup->PchUartPowerGating[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartDmaEnable[Index],  SerialIoConfig->UartDeviceConfig[Index].DmaEnable,           PchSetup->PchUartDmaEnable[Index]);
  }
  UPDATE_POLICY(((FSPS_UPD *)FspsUpd)->FspsConfig.SerialIoUartRxPinMuxPolicy[0], SerialIoConfig->UartDeviceConfig[0].PinMux.Rx, GPIO_VER3_MUXING_SERIALIO_UART0_RXD_GPP_T12);
  UPDATE_POLICY(((FSPS_UPD *)FspsUpd)->FspsConfig.SerialIoUartTxPinMuxPolicy[0], SerialIoConfig->UartDeviceConfig[0].PinMux.Tx, GPIO_VER3_MUXING_SERIALIO_UART0_TXD_GPP_T13);
  UPDATE_POLICY(((FSPS_UPD *)FspsUpd)->FspsConfig.SerialIoUartRtsPinMuxPolicy[0], SerialIoConfig->UartDeviceConfig[0].PinMux.Rts, GPIO_VER3_MUXING_SERIALIO_UART0_RTS_GPP_T14);
  UPDATE_POLICY(((FSPS_UPD *)FspsUpd)->FspsConfig.SerialIoUartCtsPinMuxPolicy[0], SerialIoConfig->UartDeviceConfig[0].PinMux.Cts, GPIO_VER3_MUXING_SERIALIO_UART0_CTS_GPP_T15);


  if ((PchSetup->OsDebugPort != 0) && ((PchSetup->OsDebugPort - 1) <= GetPchMaxSerialIoUartControllersNum ()) && (PchSetup->OsDebugPort != 0xFF)) {
    //
    // This UART controller will be used as OS debug port
    //
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartMode[PchSetup->OsDebugPort - 1], SerialIoConfig->UartDeviceConfig[PchSetup->OsDebugPort - 1].Mode, SerialIoUartHidden);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartDbg2[PchSetup->OsDebugPort - 1], SerialIoConfig->UartDeviceConfig[PchSetup->OsDebugPort - 1].DBG2,               TRUE);
  }

DEBUG_CODE_BEGIN();
  if (GetDebugInterface () & STATUS_CODE_USE_SERIALIO) {
    UPDATE_POLICY (
      ((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartBaudRate[DebugConfigData->SerialIoUartDebugControllerNumber],
      SerialIoConfig->UartDeviceConfig[DebugConfigData->SerialIoUartDebugControllerNumber].Attributes.BaudRate,
      DebugConfigData->SerialIoUartDebugBaudRate
    );
    UPDATE_POLICY (
      ((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartDataBits[DebugConfigData->SerialIoUartDebugControllerNumber],
      SerialIoConfig->UartDeviceConfig[DebugConfigData->SerialIoUartDebugControllerNumber].Attributes.DataBits,
      DebugConfigData->SerialIoUartDebugDataBits
    );
    UPDATE_POLICY (
      ((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartStopBits[DebugConfigData->SerialIoUartDebugControllerNumber],
      SerialIoConfig->UartDeviceConfig[DebugConfigData->SerialIoUartDebugControllerNumber].Attributes.StopBits,
      DebugConfigData->SerialIoUartDebugStopBits
    );
    UPDATE_POLICY (
      ((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartParity[DebugConfigData->SerialIoUartDebugControllerNumber],
      SerialIoConfig->UartDeviceConfig[DebugConfigData->SerialIoUartDebugControllerNumber].Attributes.Parity,
      DebugConfigData->SerialIoUartDebugParity
    );
    UPDATE_POLICY (
      ((FSPS_UPD *) FspsUpd)->FspsConfig.SerialIoUartAutoFlow[DebugConfigData->SerialIoUartDebugControllerNumber],
      SerialIoConfig->UartDeviceConfig[DebugConfigData->SerialIoUartDebugControllerNumber].Attributes.AutoFlow,
      DebugConfigData->SerialIoUartDebugFlowControl
    );
  }
DEBUG_CODE_END();

}

/**
  This function updates USB OverCurrent policy mapping based on board design

  @param[in]  UsbConfig        Pointer to USB_CONFIG data buffer
  @param[in]  FspsUpd          A VOID pointer
**/
VOID
UpdateUsbOverCurrentPolicy (
  IN USB_CONFIG                 *UsbConfig,
  IN VOID                       *FspsUpd
  )
{
  USB_OC_MAP_TABLE    *UsbOcMappingTable;
  UINT8               PortIndex;
  UINT8               PortCount;

  //
  // Updating USB2 OC pin mapping
  //
  UsbOcMappingTable = (USB_OC_MAP_TABLE *) PcdGet32 (PcdUsb2OverCurrentPinTable);
  if (UsbOcMappingTable == NULL) {
    DEBUG ((DEBUG_ERROR, "UpdateUsbOverCurrentPolicy: No data for USB2 OC pin mapping provided.\n"));
    return;
  }

  //
  // Warning for size mismatch between data and port count
  //
  if (UsbOcMappingTable->Size != GetPchUsb2MaxPhysicalPortNum ()) {
    DEBUG ((DEBUG_WARN, "UpdateUsbOverCurrentPolicy: Mismatch between USB2 OC mapping table size and port count. Got: %d\n", UsbOcMappingTable->Size));
  }

  //
  // To avoid overflow get minimum from either table size or max USB2 port count
  //
  PortCount = MIN (GetPchUsb2MaxPhysicalPortNum (), UsbOcMappingTable->Size);
  DEBUG ((DEBUG_INFO, "UpdateUsbOverCurrentPolicy: Updating USB OC mapping for %d USB2 ports.\n", PortCount));

  for (PortIndex = 0; PortIndex < PortCount; PortIndex++) {
    if ((UsbOcMappingTable->Data[PortIndex] < UsbOverCurrentPinMax) || (UsbOcMappingTable->Data[PortIndex] == UsbOverCurrentPinSkip)) {
      UPDATE_POLICY (((FSPS_UPD *)FspsUpd)->FspsConfig.Usb2OverCurrentPin[PortIndex], UsbConfig->PortUsb20[PortIndex].OverCurrentPin, UsbOcMappingTable->Data[PortIndex]);
    } else {
      DEBUG ((DEBUG_ERROR, "UpdateUsbOverCurrentPolicy: Invalid OverCurrent pin specified USB2 port %d\n", PortIndex));
    }
  }

  //
  // Updating USB3 OC pin mapping
  //
  UsbOcMappingTable = (USB_OC_MAP_TABLE *) PcdGet32 (PcdUsb3OverCurrentPinTable);
  if (UsbOcMappingTable == NULL) {
    DEBUG ((DEBUG_INFO, "UpdateUsbOverCurrentPolicy: No data for USB3 OC pin mapping provided.\n"));
    return;
  }

  //
  // Warning for size mismatch between data and port count
  //
  if (UsbOcMappingTable->Size != GetPchXhciMaxUsb3PortNum ()) {
    DEBUG ((DEBUG_WARN, "UpdateUsbOverCurrentPolicy: Mismatch between USB3 OC mapping table size and port count. Got: %d\n", UsbOcMappingTable->Size));
  }

  //
  // To avoid overflow get minimum from either table size or max USB2 port count
  //
  PortCount = MIN (GetPchXhciMaxUsb3PortNum (), UsbOcMappingTable->Size);
  DEBUG ((DEBUG_INFO, "UpdateUsbOverCurrentPolicy: Updating USB OC mapping for %d USB3 ports.\n", PortCount));

  for (PortIndex = 0; PortIndex < PortCount; PortIndex++) {
    if ((UsbOcMappingTable->Data[PortIndex] < UsbOverCurrentPinMax) || (UsbOcMappingTable->Data[PortIndex] == UsbOverCurrentPinSkip)) {
      UPDATE_POLICY (((FSPS_UPD *)FspsUpd)->FspsConfig.Usb3OverCurrentPin[PortIndex], UsbConfig->PortUsb30[PortIndex].OverCurrentPin, UsbOcMappingTable->Data[PortIndex]);
    } else {
      DEBUG ((DEBUG_ERROR, "UpdateUsbOverCurrentPolicy: Invalid OverCurrent pin specified USB3 port %d\n", PortIndex));
    }
  }
}

/**
  Update Usb config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateUsbConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  UINTN           PortIndex;
  USB_CONFIG      *UsbConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsbConfigGuid, (VOID *) &UsbConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  UsbConfig = NULL;
#endif


  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchEnableComplianceMode, UsbConfig->EnableComplianceMode, PchSetup->EnableComplianceMode);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchUsbOverCurrentEnable, UsbConfig->OverCurrentEnable, !!PchSetup->PchEnableDbcObs ? FALSE : PchSetup->PchUsbOverCurrentEnable);

  for (PortIndex = 0; PortIndex < GetPchUsb2MaxPhysicalPortNum (); PortIndex++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PortUsb20Enable[PortIndex], UsbConfig->PortUsb20[PortIndex].Enable, !!PchSetup->PchUsbHsPort[PortIndex]);
  }
  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb3PortNum (); PortIndex++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PortUsb30Enable[PortIndex], UsbConfig->PortUsb30[PortIndex].Enable, !!PchSetup->PchUsbSsPort[PortIndex]);
  }
  for (PortIndex = 0; PortIndex < GetPchUsb2MaxPhysicalPortNum (); PortIndex++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.USB20Otg[PortIndex], UsbConfig->USB20Otg[PortIndex], PchSetup->PchUsbHsPortOtg[PortIndex]);
  }
  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb3PortNum (); PortIndex++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.USB30Otg[PortIndex], UsbConfig->USB30Otg[PortIndex], PchSetup->PchUsbSsPortOtg[PortIndex]);
  }
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.UsbClockGatingEnable, UsbConfig->UsbClockGatingEnable, PchSetup->PchMasterClockGating);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.UsbPowerGatingEnable, UsbConfig->UsbPowerGatingEnable, PchSetup->PchMasterPowerGating);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.USB3LinkSpeed, UsbConfig->USB3LinkSpeed, PchSetup->PchUsb3LinkSpeed);
  //
  // xDCI (USB device) related settings from setup variable
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.XdciEnable, UsbConfig->XdciConfig.Enable, !!PchSetup->PchXdciSupport);

  //
  // Update both USB2 and USB3 OC pin mapping based on platform design
  //
  UpdateUsbOverCurrentPolicy (UsbConfig, FspsUpd);
}

/**
  Update USB2 PHY config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdatePchUsb2PhyConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  USB2_PHY_CONFIG   *Usb2PhyConfig;
  USB2_PHY_TABLE    *Usb2PhyTuningTable;
  UINT8             PortIndex;
  UINT8             PortCount;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsb2PhyConfigGuid, (VOID *) &Usb2PhyConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  Usb2PhyConfig = NULL;
#endif

  //
  // Get USB2 PHY tuning table address and verify it's available
  //
  Usb2PhyTuningTable = (USB2_PHY_TABLE *) PcdGet32 (PcdUsb2PhyTuningTable);
  if (Usb2PhyTuningTable == NULL) {
    DEBUG ((DEBUG_INFO, "UpdateUsb2PhyPolicy: No data for USB2 PHY tuning provided.\n"));
    return;
  }

  //
  // Display warning for size difference
  //
  if (Usb2PhyTuningTable->Size != GetPchUsb2MaxPhysicalPortNum ()) {
    DEBUG ((DEBUG_WARN, "UpdateUsb2PhyPolicy: Invalid USB2 PHY tuning table size. Got: %d\n", Usb2PhyTuningTable->Size));
  }

  //
  // To avoid overflow get minimum from either table size or max USB2 port count
  //
  PortCount = MIN (Usb2PhyTuningTable->Size, GetPchUsb2MaxPhysicalPortNum ());
  DEBUG ((DEBUG_INFO, "UpdateUsb2PhyPolicy: USB2 PHY parameters will be updated for %d USB2 ports.\n", PortCount));

  for (PortIndex = 0; PortIndex < PortCount; PortIndex++) {
    UPDATE_POLICY (((FSPS_UPD *)FspsUpd)->FspsConfig.Usb2PhyPetxiset[PortIndex],  Usb2PhyConfig->Port[PortIndex].Petxiset , Usb2PhyTuningTable->Data[PortIndex].Petxiset);
    UPDATE_POLICY (((FSPS_UPD *)FspsUpd)->FspsConfig.Usb2PhyTxiset[PortIndex],    Usb2PhyConfig->Port[PortIndex].Txiset   , Usb2PhyTuningTable->Data[PortIndex].Txiset);
    UPDATE_POLICY (((FSPS_UPD *)FspsUpd)->FspsConfig.Usb2PhyPredeemp[PortIndex],  Usb2PhyConfig->Port[PortIndex].Predeemp , Usb2PhyTuningTable->Data[PortIndex].Predeemp);
    UPDATE_POLICY (((FSPS_UPD *)FspsUpd)->FspsConfig.Usb2PhyPehalfbit[PortIndex], Usb2PhyConfig->Port[PortIndex].Pehalfbit, Usb2PhyTuningTable->Data[PortIndex].Pehalfbit);
  }
}

/**
  Update eMMC configuration.

  @param[in] SiPolicy          Pointer to SI_POLICY_PPI
  @param[in] FspsUpd           Pointer to FSPS_UPD
  @param[in] PchSetup          Pointer to PCH_SETUP
  @param[in] VariableServices  Pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI
**/
STATIC
VOID
UpdateEmmcConfig (
  IN SI_POLICY_PPI  *SiPolicy,
  IN VOID           *FspsUpd,
  IN PCH_SETUP      *PchSetup
  )
{
  SCS_EMMC_CONFIG                    *EmmcConfig;
  UINT8                              Index;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                         Status;
#endif

  EmmcConfig = NULL;

#if FixedPcdGet8(PcdFspModeSelection) == 0
  Status = GetConfigBlock ((VOID *) SiPolicy, &gEmmcConfigGuid, (VOID *) &EmmcConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#endif

  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.ScsEmmcEnabled, EmmcConfig->Enable, PchSetup->PchScsEmmcEnabled);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.ScsEmmcHs400Enabled, EmmcConfig->Hs400Supported, PchSetup->PchScsEmmcHs400Enabled);

  //
  // Board specific DLL tuning. Right now all RVPs are working fine on default DLL values.
  //
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcUseCustomDlls, EmmcConfig->UseCustomDlls, FALSE);

  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioCmdPinMux, EmmcConfig->GpioConfig.Cmd.PinMux, 0);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioCmdPadTermination, EmmcConfig->GpioConfig.Cmd.PadTermination, GpioTermDefault);
  for (Index = 0; Index < SCS_EMMC_MAX_DATA_GPIOS; Index++) {
    UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioDataPinMux[Index], EmmcConfig->GpioConfig.Data[Index].PinMux, 0);
    UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioDataPadTermination[Index], EmmcConfig->GpioConfig.Data[Index].PadTermination, GpioTermDefault);
  }
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioRclkPinMux, EmmcConfig->GpioConfig.Rclk.PinMux, 0);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioRclkPadTermination, EmmcConfig->GpioConfig.Rclk.PadTermination, GpioTermDefault);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioClkPinMux, EmmcConfig->GpioConfig.Clk.PinMux, 0);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioClkPadTermination, EmmcConfig->GpioConfig.Clk.PadTermination, GpioTermDefault);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioResetbPinMux, EmmcConfig->GpioConfig.Resetb.PinMux, 0);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioResetbPadTermination, EmmcConfig->GpioConfig.Resetb.PadTermination, GpioTermDefault);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioHipMonPinMux, EmmcConfig->GpioConfig.HipMon.PinMux, 0);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.EmmcGpioHipMonPadTermination, EmmcConfig->GpioConfig.HipMon.PadTermination, GpioTermDefault);
}

/**
  Update SdCard configuration.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
  @param[in] PchSetup  Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateSdCardConfig (
  IN SI_POLICY_PPI  *SiPolicy,
  IN VOID           *FspsUpd,
  IN PCH_SETUP      *PchSetup
  )
{
  SCS_SDCARD_CONFIG  *SdCardConfig;
  UINT8              Index;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS         Status;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSdCardConfigGuid, (VOID *) &SdCardConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  SdCardConfig = NULL;
#endif

  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.ScsSdCardEnabled, SdCardConfig->Enable, PchSetup->PchScsSdCardEnabled);
  //
  // All of our RVP designs are using PWREN# as active high.
  //
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardPowerEnableActiveHigh, SdCardConfig->PowerEnableActiveHigh, TRUE);
  //
  // Board specific DLL tuning. Right now all RVPs are working fine on default DLL values.
  //
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardUseCustomDlls, SdCardConfig->UseCustomDlls, FALSE);

  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioPrwEnBPinMux, SdCardConfig->GpioConfig.PowerEnable.PinMux, 0);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioPrwEnBPadTermination, SdCardConfig->GpioConfig.PowerEnable.PadTermination, GpioTermDefault);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioCmdPinMux, SdCardConfig->GpioConfig.Cmd.PinMux, 0);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioCmdPadTermination, SdCardConfig->GpioConfig.Cmd.PadTermination, GpioTermNative);
  for (Index = 0; Index < SCS_SDCARD_MAX_DATA_GPIOS; Index++) {
    UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioDataPinMux[Index], SdCardConfig->GpioConfig.Data[Index].PinMux, 0);
    UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioDataPadTermination[Index], SdCardConfig->GpioConfig.Data[Index].PadTermination, GpioTermNative);
  }
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioCdbPinMux, SdCardConfig->GpioConfig.Cdb.PinMux, 0);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioCdbPadTermination, SdCardConfig->GpioConfig.Cdb.PadTermination, GpioTermDefault);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioClkPinMux, SdCardConfig->GpioConfig.Clk.PinMux, 0);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioClkPadTermination, SdCardConfig->GpioConfig.Clk.PadTermination, GpioTermDefault);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioWpPinMux, SdCardConfig->GpioConfig.Wp.PinMux, 0);
  UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.SdCardGpioWpPadTermination, SdCardConfig->GpioConfig.Wp.PadTermination, GpioTermDefault);
}

/**
  Update UFS configuration.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
  @param[in] PchSetup  Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateUfsConfig (
  IN SI_POLICY_PPI  *SiPolicy,
  IN VOID           *FspsUpd,
  IN PCH_SETUP      *PchSetup
  )
{
  UINT8           UfsIndex;
  SCS_UFS_CONFIG  *UfsConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS      Status;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gUfsConfigGuid, (VOID *) &UfsConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  UfsConfig = NULL;
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 1
  //
  // FSP has disjoint configuration space allocation so we check for both UFS number supported in code
  // and UFS supported by FSPS_UPD
  //
  for (UfsIndex = 0; (UfsIndex < PchGetMaxUfsNum ()) && UfsIndex < 2; UfsIndex++) {
#else
  for (UfsIndex = 0; UfsIndex < PchGetMaxUfsNum (); UfsIndex++) {
#endif
    UPDATE_POLICY(((FSPS_UPD *) FspsUpd)->FspsConfig.UfsEnable[UfsIndex], UfsConfig->UfsControllerConfig[UfsIndex].Enable, PchSetup->PchScsUfsEnable[UfsIndex]);
  }
}

/**
  Update HD Audio configuration.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
  @param[in] FspmUpd   Pointer to FSPM_UPD
  @param[in] PchSetup  Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateHdAudioConfig (
  IN SI_POLICY_PPI        *SiPolicy,
  IN SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi,
  IN VOID                 *FspsUpd,
  IN VOID                 *FspmUpd,
  IN PCH_SETUP            *PchSetup
  )
{
  HDAUDIO_CONFIG        *HdAudioConfig;
  HDAUDIO_PREMEM_CONFIG *HdAudioPreMemConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS        Status;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gHdAudioConfigGuid, (VOID *) &HdAudioConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHdAudioPreMemConfigGuid, (VOID *) &HdAudioPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  HdAudioConfig = NULL;
  HdAudioPreMemConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchHdaPme,                      HdAudioConfig->Pme,                      PchSetup->PchHdAudioPme);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchHdaLinkFrequency,            HdAudioConfig->HdAudioLinkFrequency,     PchSetup->PchHdaHdAudioLinkFreq);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchHdaCodecSxWakeCapability,    HdAudioConfig->CodecSxWakeCapability,    PchSetup->PchHdAudioCodecSxWakeCapability);

  //
  // Install HDA Link/iDisplay Codec Verb Table
  //
  if (PchSetup->PchHdAudio) {
    InternalAddPlatformVerbTables (HdAudioConfig, HdAudioPreMemConfig, (VOID *)FspsUpd, (VOID *)FspmUpd, PchSetup->PchHdAudioCodecSelect);
  }

}

/**
  Update IO APIC Configuration

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
  @param[in] SetupVariables       Pointer to SETUP_DATA buffer
**/
VOID
UpdateIoApicConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup,
  IN SETUP_DATA                *SetupVariables
  )
{
  PCH_IOAPIC_CONFIG   *IoApicConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS          Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gIoApicConfigGuid, (VOID *) &IoApicConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  IoApicConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchIoApicEntry24_119, IoApicConfig->IoApicEntry24_119, PchSetup->PchIoApic24119Entries);
  //
  // To support SLP_S0, it's required to disable 8254 timer.
  // Note that CSM may require this option to be disabled for correct operation.
  // Once 8254 timer disabled, some legacy OPROM and legacy OS will fail while using 8254 timer.
  // For some OS environment that it needs to set 8254CGE in late state it should
  // set this policy to FALSE and use PmcSet8254ClockGateState (TRUE) in SMM later.
  // This is also required during S3 resume.
  //
  // The Enable8254ClockGatingOnS3 is only applicable when Enable8254ClockGating is disabled.
  // If Enable8254ClockGating is enabled, RC will do 8254 CGE programming on S3 as well.
  // else, RC will do the programming on S3 when Enable8254ClockGatingOnS3 is enabled.
  // This avoids the SMI requirement for the programming.
  //
  if (PchSetup->Enable8254ClockGating == 1) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Enable8254ClockGating, IoApicConfig->Enable8254ClockGating, TRUE);
  } else if (PchSetup->Enable8254ClockGating == 2) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Enable8254ClockGating, IoApicConfig->Enable8254ClockGating, FALSE);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Enable8254ClockGatingOnS3, IoApicConfig->Enable8254ClockGatingOnS3, TRUE);
  } else {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Enable8254ClockGating, IoApicConfig->Enable8254ClockGating, FALSE);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.Enable8254ClockGatingOnS3, IoApicConfig->Enable8254ClockGatingOnS3, FALSE);
  }

}

/**
  Update PCIe Root Port Configuration

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
  @param[in] SetupVariables       Pointer to SETUP_DATA buffer
**/
VOID
UpdatePcieRpConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup,
  IN SETUP_DATA                *SetupVariables
  )
{
  UINT8                           Index;
  EFI_STATUS                      Status;
  PCH_PCIE_CONFIG                 *PcieRpConfig;
  PEI_DTBT_POLICY                 *PeiDTbtConfig;
  UINT8                           TbtSelector;
  UINTN                           MaxPciePorts;

  MaxPciePorts = GetPchMaxPciePortNum ();
  PcieRpConfig = NULL;
  PeiDTbtConfig = NULL;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#endif

  if (SetupVariables->DiscreteTbtSupport == 1) {
    //
    // Obtain TBT Info from PEI TBT Policy.
    //
    Status = PeiServicesLocatePpi (
               &gPeiDTbtPolicyPpiGuid,
               0,
               NULL,
               (VOID **) &PeiDTbtConfig
               );
    if (PeiDTbtConfig != NULL) {
      for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
        TbtSelector = PeiDTbtConfig->DTbtControllerConfig[Index].PcieRpNumber - 1;
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpMaxPayload[TbtSelector], PcieRpConfig->RootPort[TbtSelector].MaxPayload, PchPcieMaxPayload128);
        DEBUG ((DEBUG_INFO, "PCIe RootPort[%x]= %x\n", TbtSelector, PcieRpConfig->RootPort[TbtSelector].MaxPayload));

        if (PchSetup->PchPcieLtrEnable[TbtSelector] == 1) {
          UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpSnoopLatencyOverrideMode[Index],          PcieRpConfig->RootPort[TbtSelector].PcieRpLtrConfig.SnoopLatencyOverrideMode,          1);
          UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpSnoopLatencyOverrideMultiplier[Index],    PcieRpConfig->RootPort[TbtSelector].PcieRpLtrConfig.SnoopLatencyOverrideMultiplier,    2);
          UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpSnoopLatencyOverrideValue[Index],         PcieRpConfig->RootPort[TbtSelector].PcieRpLtrConfig.SnoopLatencyOverrideValue,        85);
          UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpNonSnoopLatencyOverrideMode[Index],       PcieRpConfig->RootPort[TbtSelector].PcieRpLtrConfig.NonSnoopLatencyOverrideMode,       1);
          UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpNonSnoopLatencyOverrideMultiplier[Index], PcieRpConfig->RootPort[TbtSelector].PcieRpLtrConfig.NonSnoopLatencyOverrideMultiplier, 2);
          UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpNonSnoopLatencyOverrideValue[Index],      PcieRpConfig->RootPort[TbtSelector].PcieRpLtrConfig.NonSnoopLatencyOverrideValue,     85);
        }
      }
    }
  }

  //
  // PCI express config
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEnablePeerMemoryWrite,      PcieRpConfig->EnablePeerMemoryWrite,      PchSetup->PcieRootPortPeerMemoryWriteEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieComplianceTestMode,         PcieRpConfig->ComplianceTestMode,         PchSetup->PcieComplianceTestMode);
  UPDATE_POLICY (((FSPS_UPD *)FspsUpd)->FspsConfig.TestPcieClockGating,             PcieRpConfig->TestPcieClockGating,        PchSetup->TestPcieClockGating);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpFunctionSwap,             PcieRpConfig->RpFunctionSwap,             PchSetup->RpFunctionSwap);

  for (Index = 0; Index < MaxPciePorts; Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpMaxPayload[Index],                     PcieRpConfig->RootPort[Index].MaxPayload,         PchPcieMaxPayload256);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpPhysicalSlotNumber[Index],             PcieRpConfig->RootPort[Index].PhysicalSlotNumber, (UINT8) Index);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpClkReqDetect[Index],                   PcieRpConfig->RootPort[Index].ClkReqDetect,       TRUE);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpAspm[Index],                           PcieRpConfig->RootPort[Index].Aspm,               PchSetup->PcieRootPortAspm[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpL1Substates[Index],                    PcieRpConfig->RootPort[Index].L1Substates,        PchSetup->PcieRootPortL1SubStates[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpPcieSpeed[Index],                      PcieRpConfig->RootPort[Index].PcieSpeed,          PchSetup->PcieRootPortSpeed[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpAcsEnabled[Index],                     PcieRpConfig->RootPort[Index].AcsEnabled,         PchSetup->PcieRootPortACS[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpMultiVcEnabled[Index],                 PcieRpConfig->RootPort[Index].MultiVcEnabled,     PchSetup->PcieRootPortMVCE[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PciePtm[Index], PcieRpConfig->RootPort[Index].PtmEnabled, PchSetup->PcieRootPortPTM[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieDpc[Index], PcieRpConfig->RootPort[Index].DpcEnabled, PchSetup->PcieRootPortDPC[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEdpc[Index], PcieRpConfig->RootPort[Index].RpDpcExtensionsEnabled, PchSetup->PcieRootPortEDPC[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpSlotImplemented[Index],                PcieRpConfig->RootPort[Index].SlotImplemented,                PchSetup->PcieRootPortSI[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpPmSci[Index],                          PcieRpConfig->RootPort[Index].PmSci,                          PchSetup->PcieRootPortPMCE[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpHotPlug[Index],                        PcieRpConfig->RootPort[Index].HotPlug,                        PchSetup->PcieRootPortHPE[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpAdvancedErrorReporting[Index],         PcieRpConfig->RootPort[Index].AdvancedErrorReporting,         PchSetup->PcieRootPortAER[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpUnsupportedRequestReport[Index],       PcieRpConfig->RootPort[Index].UnsupportedRequestReport,       PchSetup->PcieRootPortURE[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpFatalErrorReport[Index],               PcieRpConfig->RootPort[Index].FatalErrorReport,               PchSetup->PcieRootPortFEE[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpNoFatalErrorReport[Index],             PcieRpConfig->RootPort[Index].NoFatalErrorReport,             PchSetup->PcieRootPortNFE[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpCorrectableErrorReport[Index],         PcieRpConfig->RootPort[Index].CorrectableErrorReport,         PchSetup->PcieRootPortCEE[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpSystemErrorOnFatalError[Index],        PcieRpConfig->RootPort[Index].SystemErrorOnFatalError,        PchSetup->PcieRootPortSFE[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpSystemErrorOnNonFatalError[Index],     PcieRpConfig->RootPort[Index].SystemErrorOnNonFatalError,     PchSetup->PcieRootPortSNE[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpSystemErrorOnCorrectableError[Index],  PcieRpConfig->RootPort[Index].SystemErrorOnCorrectableError,  PchSetup->PcieRootPortSCE[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpTransmitterHalfSwing[Index],           PcieRpConfig->RootPort[Index].TransmitterHalfSwing,           PchSetup->PcieRootPortTHS[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpDetectTimeoutMs[Index],                PcieRpConfig->RootPort[Index].DetectTimeoutMs,                PchSetup->PcieDetectTimeoutMs[Index]);
  }

  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
#if FixedPcdGet8(PcdFspModeSelection) == 1
    if (IsPchLp ()) {
      ((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrMaxSnoopLatency[Index]   = 0x1003;
      ((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrMaxNoSnoopLatency[Index] = 0x1003;
    }
    if (IsPchH ()) {
      ((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrMaxSnoopLatency[Index]   = 0x0846;
      ((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrMaxNoSnoopLatency[Index] = 0x0846;
    }
#endif
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrEnable[Index], PcieRpConfig->RootPort[Index].LtrEnable, PchSetup->PchPcieLtrEnable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieRpLtrConfigLock[Index], PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrConfigLock, PchSetup->PchPcieLtrConfigLock[Index]);
  }

  //
  // Update EQ settigns
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqOverrideDefault, PcieRpConfig->OverrideEqualizationDefaults, PchSetup->PcieEqOverrideDefault);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqMethod, PcieRpConfig->PcieLinkEqPlatformSettings.PcieLinkEqMethod, PchSetup->PcieEqMethod);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqMode, PcieRpConfig->PcieLinkEqPlatformSettings.PcieLinkEqMode, PchSetup->PcieEqMode);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqLocalTransmitterOverrideEnable, PcieRpConfig->PcieLinkEqPlatformSettings.LocalTransmitterOverrideEnable, PchSetup->PcieEqPh2LocalTransmitterOverrideEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqPh1DownstreamPortTransmitterPreset, PcieRpConfig->PcieLinkEqPlatformSettings.Ph1DownstreamPortTransmitterPreset, PchSetup->PcieEqPh1DownstreamPortTransmitterPreset);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqPh1UpstreamPortTransmitterPreset, PcieRpConfig->PcieLinkEqPlatformSettings.Ph1UpstreamPortTransmitterPreset, PchSetup->PcieEqPh1UpstreamPortTransmitterPreset);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqPh3NumberOfPresetsOrCoefficients, PcieRpConfig->PcieLinkEqPlatformSettings.Ph3NumberOfPresetsOrCoefficients, PchSetup->PcieEqPh3NumberOfPresetsOrCoefficients);
  for (Index = 0; Index < PCIE_LINK_EQ_COEFFICIENTS_MAX; Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqPh3PreCursorList[Index], PcieRpConfig->PcieLinkEqPlatformSettings.Ph3CoefficientsList[Index].PreCursor, PchSetup->PcieEqPh3PreCursorList[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqPh3PostCursorList[Index], PcieRpConfig->PcieLinkEqPlatformSettings.Ph3CoefficientsList[Index].PostCursor, PchSetup->PcieEqPh3PostCursorList[Index]);
  }
  for (Index = 0; Index < PCIE_LINK_EQ_PRESETS_MAX; Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqPh3PresetList[Index], PcieRpConfig->PcieLinkEqPlatformSettings.Ph3PresetList[Index], PchSetup->PcieEqPh3PresetList[Index]);
  }
  if (PchSetup->PcieEqPh2LocalTransmitterOverrideEnable) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PcieEqPh2LocalTransmitterOverridePreset, PcieRpConfig->PcieLinkEqPlatformSettings.Ph2LocalTransmitterOverridePreset, PchSetup->PcieEqPh2LocalTransmitterOverridePreset);
  }
}

/**
  Update PSE config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdatePseConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  UINT8                           Index;
  PSE_CONFIG                      *PseConfig;

#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPseConfigGuid, (VOID *) &PseConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PseConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseLogOutputChannel,     PseConfig->PseLogOutputChannel,   PchSetup->PchPseLogOutputChannel);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseLogOutputSize,        PseConfig->PseLogOutputSize,      PchSetup->PchPseLogOutputSize);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseLogOutputOffset,      PseConfig->PseLogOutputOffset,    PchSetup->PchPseLogOutputOffset);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseJtagEnabled,          PseConfig->PseJtagEnabled,        PchSetup->PchPseJtagEnabled);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseJtagPinMux,           PseConfig->PseJtagPinMux,         PchSetup->PchPseJtagPinMux);

  for (Index = 0; Index < GetPchMaxPseI2sControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2sEnable[Index],    PseConfig->I2s[Index].OwnerShip,                  PchSetup->PchPseI2sEnable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2sSbInterruptEnable[Index],  PseConfig->I2s[Index].SbInterruptEnable, PchSetup->PchPseI2sSbInterruptEnable[Index]);
  }

  if(PchSetup->PchPseI2s0PinAssignment == 0) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2sTxPinMux[0],       PseConfig->I2s[0].PinMux.Tx,      GPIO_VER3_MUXING_PSE_I2S0_TXD_GPP_E16);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2sRxPinMux[0],       PseConfig->I2s[0].PinMux.Rx,      GPIO_VER3_MUXING_PSE_I2S0_RXD_GPP_E15);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2sSfrmPinMux[0],     PseConfig->I2s[0].PinMux.Sfrm,    GPIO_VER3_MUXING_PSE_I2S0_SFRM_GPP_E21);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2sSclkPinMux[0],     PseConfig->I2s[0].PinMux.Clk,     GPIO_VER3_MUXING_PSE_I2S0_SCLK_GPP_E20);
  } else {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2sTxPinMux[0],       PseConfig->I2s[0].PinMux.Tx,      GPIO_VER3_MUXING_PSE_I2S0_TXD_GPP_R2);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2sRxPinMux[0],       PseConfig->I2s[0].PinMux.Rx,      GPIO_VER3_MUXING_PSE_I2S0_RXD_GPP_R3);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2sSfrmPinMux[0],     PseConfig->I2s[0].PinMux.Sfrm,    GPIO_VER3_MUXING_PSE_I2S0_SFRM_GPP_R1);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2sSclkPinMux[0],     PseConfig->I2s[0].PinMux.Clk,     GPIO_VER3_MUXING_PSE_I2S0_SCLK_GPP_R0);
  }

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmEnable,            PseConfig->Pwm.OwnerShip,         PchSetup->PchPsePwmEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmSbInterruptEnable, PseConfig->Pwm.SbInterruptEnable, PchSetup->PchPsePwmSbInterruptEnable);

  for (Index = 0; Index < GetPchMaxPsePwmControllerPinsNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmPinEnable[Index],   PseConfig->Pwm.PinEnable[Index], PchSetup->PchPsePwmPinEnable[Index]);
  }

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmPinMux[8],         PseConfig->Pwm.PinMux.Pin[8],     GPIO_VER3_MUXING_PSE_PWM_08_GPP_E4);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmPinMux[9],         PseConfig->Pwm.PinMux.Pin[9],     GPIO_VER3_MUXING_PSE_PWM_09_GPP_E5);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmPinMux[10],        PseConfig->Pwm.PinMux.Pin[10],    GPIO_VER3_MUXING_PSE_PWM_10_GPP_E6);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmPinMux[11],        PseConfig->Pwm.PinMux.Pin[11],    GPIO_VER3_MUXING_PSE_PWM_11_GPP_E17);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmPinMux[12],        PseConfig->Pwm.PinMux.Pin[12],    GPIO_VER3_MUXING_PSE_PWM_12_GPP_E18);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmPinMux[13],        PseConfig->Pwm.PinMux.Pin[13],    GPIO_VER3_MUXING_PSE_PWM_13_GPP_E19);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmPinMux[14],        PseConfig->Pwm.PinMux.Pin[14],    GPIO_VER3_MUXING_PSE_PWM_14_GPP_H10);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPsePwmPinMux[15],        PseConfig->Pwm.PinMux.Pin[15],    GPIO_VER3_MUXING_PSE_PWM_15_GPP_H11);

  for (Index = 0; Index < GetPchMaxPseUartControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseUartEnable[Index],            PseConfig->Uart[Index].OwnerShip,         PchSetup->PchPseUartEnable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseUartSbInterruptEnable[Index], PseConfig->Uart[Index].SbInterruptEnable, PchSetup->PchPseUartSbInterruptEnable[Index]);
  }

  for (Index = 0; Index < GetPchMaxPseHsuartControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseHsuartEnable[Index],         PseConfig->Hsuart[Index].OwnerShip,      PchSetup->PchPseHsuartEnable[Index]);
  }

  for (Index = 0; Index < GetPchMaxPseGbeControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseGbeEnable[Index],            PseConfig->Gbe[Index].OwnerShip,         PchSetup->PchPseGbeEnable[Index]);
  }
  for (Index = 0; Index < GetPchMaxPseDmaControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseDmaEnable[Index],            PseConfig->Dma[Index].OwnerShip,         PchSetup->PchPseDmaEnable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseDmaSbInterruptEnable[Index], PseConfig->Dma[Index].SbInterruptEnable, PchSetup->PchPseDmaSbInterruptEnable[Index]);
  }
  for (Index = 0; Index < GetPchMaxPseQepControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseQepEnable[Index],            PseConfig->Qep[Index].OwnerShip,         PchSetup->PchPseQepEnable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseQepSbInterruptEnable[Index], PseConfig->Qep[Index].SbInterruptEnable, PchSetup->PchPseQepSbInterruptEnable[Index]);
  }
  for (Index = 0; Index < GetPchMaxPseI2cControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2cEnable[Index],             PseConfig->I2c[Index].OwnerShip,        PchSetup->PchPseI2cEnable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseI2cSbInterruptEnable[Index],  PseConfig->I2c[Index].SbInterruptEnable, PchSetup->PchPseI2cSbInterruptEnable[Index]);
  }
  for (Index = 0; Index < GetPchMaxPseSpiControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseSpiEnable[Index],             PseConfig->Spi[Index].OwnerShip,         PchSetup->PchPseSpiEnable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseSpiSbInterruptEnable[Index],  PseConfig->Spi[Index].SbInterruptEnable, PchSetup->PchPseSpiSbInterruptEnable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseSpiCs0Enable[Index],          PseConfig->Spi[Index].CsEnable[0],       PchSetup->PchPseSpiCs0Enable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseSpiCs1Enable[Index],          PseConfig->Spi[Index].CsEnable[1],       PchSetup->PchPseSpiCs1Enable[Index]);
  }

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseSpiMosiPinMux[1],        PseConfig->Spi[1].PinMux.Mosi,      GPIO_VER3_MUXING_PSE_SPI1_MOSI_GPP_D3);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseSpiMisoPinMux[1],        PseConfig->Spi[1].PinMux.Miso,      GPIO_VER3_MUXING_PSE_SPI1_MISO_GPP_D2);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseSpiClkPinMux[1],         PseConfig->Spi[1].PinMux.Clk,       GPIO_VER3_MUXING_PSE_SPI1_SCLK_GPP_D1);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseSpiCs0PinMux[1],         PseConfig->Spi[1].PinMux.Cs[0],     GPIO_VER3_MUXING_PSE_SPI1_CSB0_GPP_D0);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseAdcEnable,               PseConfig->Adc.OwnerShip,           PchSetup->PchPseAdcEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseAdcSbInterruptEnable,    PseConfig->Adc.SbInterruptEnable,   PchSetup->PchPseAdcSbInterruptEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseLh2PseSbInterruptEnable, PseConfig->Lh2Pse.SbInterruptEnable, PchSetup->PchPseLh2PseSbInterruptEnable);
  for (Index = 0; Index < GetPchMaxPseCanControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseCanEnable[Index],              PseConfig->Can[Index].OwnerShip,          PchSetup->PchPseCanEnable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseCanSbInterruptEnable[Index],   PseConfig->Can[Index].SbInterruptEnable,  PchSetup->PchPseCanSbInterruptEnable[Index]);
  }
  for (Index = 0; Index < GetPchMaxPseTimedGpioControllersNum (); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTimedGpioEnable[Index],        PseConfig->TimedGpio[Index].OwnerShip,     PchSetup->PchPseTgpioEnable[Index]);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTimedGpioPinAllocation[Index], PseConfig->TimedGpio[Index].PinAllocation, PchSetup->PchPseTgpioAllocatePins[Index]);
  }
  for (Index = 0; Index < GetPchMaxPseTimdedGpioPinsNum(); Index++) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTimedGpioPinEnable[Index],    PseConfig->TimedGpioPinEnable[Index], PchSetup->PchPseTgpioPinEnable[Index]);
  }
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio6PinMux,       PseConfig->TimedGpioPinMux.Pin[6],       GPIO_VER3_MUXING_PSE_TGPIO6_GPP_B5);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio7PinMux,       PseConfig->TimedGpioPinMux.Pin[7],       GPIO_VER3_MUXING_PSE_TGPIO7_GPP_G11);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio8PinMux,       PseConfig->TimedGpioPinMux.Pin[8],       GPIO_VER3_MUXING_PSE_TGPIO8_GPP_B7);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio9PinMux,       PseConfig->TimedGpioPinMux.Pin[9],       GPIO_VER3_MUXING_PSE_TGPIO9_GPP_B8);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio10PinMux,      PseConfig->TimedGpioPinMux.Pin[10],      GPIO_VER3_MUXING_PSE_TGPIO10_GPP_U7);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio11PinMux,      PseConfig->TimedGpioPinMux.Pin[11],      GPIO_VER3_MUXING_PSE_TGPIO11_GPP_U11);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio12PinMux,      PseConfig->TimedGpioPinMux.Pin[12],      GPIO_VER3_MUXING_PSE_TGPIO12_GPP_U19);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio13PinMux,      PseConfig->TimedGpioPinMux.Pin[13],      GPIO_VER3_MUXING_PSE_TGPIO13_GPP_D12);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio14PinMux,      PseConfig->TimedGpioPinMux.Pin[14],      GPIO_VER3_MUXING_PSE_TGPIO14_GPP_E20);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio15PinMux,      PseConfig->TimedGpioPinMux.Pin[15],      GPIO_VER3_MUXING_PSE_TGPIO15_GPP_E3);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio16PinMux,      PseConfig->TimedGpioPinMux.Pin[16],      GPIO_VER3_MUXING_PSE_TGPIO16_GPP_E7);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio17PinMux,      PseConfig->TimedGpioPinMux.Pin[17],      GPIO_VER3_MUXING_PSE_TGPIO17_GPP_E15);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio18PinMux,      PseConfig->TimedGpioPinMux.Pin[18],      GPIO_VER3_MUXING_PSE_TGPIO18_GPP_E6);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPseTgpio19PinMux,      PseConfig->TimedGpioPinMux.Pin[19],      GPIO_VER3_MUXING_PSE_TGPIO19_GPP_C1);
}

/**
  Update THC config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateThcConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  THC_CONFIG  *ThcConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS  Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gThcConfigGuid, (VOID *) &ThcConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  ThcConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ThcPort0Assignment,      ThcConfig->ThcPort[0].Assignment,      PchSetup->ThcPort0Assignment);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.ThcPort1Assignment,      ThcConfig->ThcPort[1].Assignment,      PchSetup->ThcPort1Assignment);
}

/**
  Update CNVi config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateCnviConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  CNVI_CONFIG                     *CnviConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;

  CnviConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gCnviConfigGuid, (VOID *) &CnviConfig);

  if (EFI_ERROR (Status) || CnviConfig == NULL) {
    return;
  }
#else
  CnviConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CnviMode,           CnviConfig->Mode,           PchSetup->CnviMode);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CnviBtCore,         CnviConfig->BtCore,         PchSetup->CnviBtCore);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CnviBtAudioOffload, CnviConfig->BtAudioOffload, PchSetup->CnviBtAudioOffload);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CnviRfResetPinMux, CnviConfig->PinMux.RfReset, GPIO_VER3_MUXING_CNVI_RF_RESET_GPP_G8);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.CnviClkreqPinMux,  CnviConfig->PinMux.Clkreq,  GPIO_VER3_MUXING_CNVI_CRF_XTAL_CLKREQ_GPP_G9);

}

/**
  Update Thermal config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
  @param[in] SaSetup              Pointer to SA_SETUP
**/
STATIC
VOID
UpdateThermalConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup,
  IN SA_SETUP                  *SaSetup
  )
{
  THERMAL_CONFIG                  *ThermalConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gThermalConfigGuid, (VOID *) &ThermalConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  ThermalConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryPmsyncEnable[TsGpioC],     ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioC].PmsyncEnable,     TRUE);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryPmsyncEnable[TsGpioD],     ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioD].PmsyncEnable,     TRUE);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryC0TransmitEnable[TsGpioC], ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioC].C0TransmitEnable, TRUE);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryC0TransmitEnable[TsGpioD], ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioD].C0TransmitEnable, TRUE);

  if ((SaSetup->MemoryThermalManagement != FALSE) && ((SaSetup->ExttsViaTsOnBoard != FALSE) || (SaSetup->ExttsViaTsOnDimm != FALSE))) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryThrottlingEnable,          ThermalConfig->MemoryThrottling.Enable,                                     TRUE);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryPmsyncEnable[TsGpioC],     ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioC].PmsyncEnable,     PcdGetBool (PcdMemoryThermalSensorGpioCPmsyncEnable));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryPmsyncEnable[TsGpioD],     ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioD].PmsyncEnable,     PcdGetBool (PcdMemoryThermalSensorGpioDPmsyncEnable));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryC0TransmitEnable[TsGpioC], ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioC].C0TransmitEnable, TRUE);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryC0TransmitEnable[TsGpioD], ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioD].C0TransmitEnable, TRUE);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryPinSelection[TsGpioC],     ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioC].PinSelection,     1);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryPinSelection[TsGpioD],     ThermalConfig->MemoryThrottling.TsGpioPinSetting[TsGpioD].PinSelection,     0);
  } else {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMemoryThrottlingEnable,          ThermalConfig->MemoryThrottling.Enable,                                     FALSE);
  }

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchHotEnable, ThermalConfig->PchHotEnable, PcdGetBool (PcdPchThermalHotEnable));

  //
  // Program Thermal Throttling Level
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataThermalSuggestedSetting, ThermalConfig->TTLevels.SuggestedSetting,   PchSetup->PchTtLevelSuggestSet);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TTCrossThrottling,           ThermalConfig->TTLevels.PchCrossThrottling, PchSetup->PchCrossThrottling);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchTTLock,                   ThermalConfig->TTLevels.TTLock,             PchSetup->PchThrmTtLock);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchTTState13Enable,          ThermalConfig->TTLevels.TTState13Enable,    PchSetup->PchThrmTtState13Enable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchTTEnable,                 ThermalConfig->TTLevels.TTEnable,           PchSetup->PchThrmTtEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchT2Level,                  ThermalConfig->TTLevels.T2Level,            PchSetup->PchThrmT2Level);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchT1Level,                  ThermalConfig->TTLevels.T1Level,            PchSetup->PchThrmT1Level);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchT0Level,                  ThermalConfig->TTLevels.T0Level,            PchSetup->PchThrmT0Level);

  //
  // Program DMI Thermal Throttling
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TTSuggestedSetting, ThermalConfig->DmiHaAWC.SuggestedSetting, PchSetup->PchDmiTsSuggestSet);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DmiTS3TW,           ThermalConfig->DmiHaAWC.TS3TW,            PchSetup->PchTs3Width);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DmiTS2TW,           ThermalConfig->DmiHaAWC.TS2TW,            PchSetup->PchTs2Width);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DmiTS1TW,           ThermalConfig->DmiHaAWC.TS1TW,            PchSetup->PchTs1Width);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DmiTS0TW,           ThermalConfig->DmiHaAWC.TS0TW,            PchSetup->PchTs0Width);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchDmiTsawEn,       ThermalConfig->DmiHaAWC.DmiTsawEn,        PchSetup->PchDmiTsawEn);
}

/**
  Update GBE config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateGbeConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  GBE_CONFIG                   *GbeConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gGbeConfigGuid, (VOID *) &GbeConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  GbeConfig = NULL;
#endif
  //
  // LAN Config
  // Check Gbe Region to determine if hide LAN controller setup option
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchLanEnable, GbeConfig->Enable, IsGbePresent () ? PchSetup->PchLan : FALSE);
}

/**
  Update SIIP config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateSiipConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  SIIP_CONFIG                  *SiipConfig;
  SIIP_FV_INFO                 SiipFvInfo;
  EFI_BOOT_MODE                BootMode;
  EFI_STATUS                   Status;

  Status  = EFI_SUCCESS;

#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSiipConfigGuid, (VOID *) &SiipConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  SiipConfig = NULL;
#endif
  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  //
  // Acquire SIIP FV
  //
  InstallSiipFv ();
  GetSiipFvInfo (&SiipFvInfo);
  //
  // Update SIIP base address and size
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SiipRegionBase, SiipConfig->BaseAddress,  SiipFvInfo.Address);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SiipRegionSize, SiipConfig->Size,         SiipFvInfo.Size);
}

/**
  Update PCH & PSE TSN config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateTsnConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  TSN_CONFIG                              *TsnConfig;
  TSN_MAC_ADDR_SUB_REGION                 *TsnMacAddrSubRegion;
  PSE_IP_CONFIG_SUB_REGION                *PseTsnIpConfigSubRegion;
  PSE_TSN_CONFIG_SUB_REGION               *TsnConfigSubRegion;
  UINT32                                  TsnMacAddrSubRegionSize;
  UINT32                                  PseTsnIpConfigSubRegionSize;
  UINT32                                  TsnConfigSubRegionSize;

#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gTsnConfigGuid, (VOID *) &TsnConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  TsnConfig = NULL;
#endif

  InstallTsnMacAddrFv ();
  InstallPseTsnIpConfigFv ();
  InstallTsnConfigFv ();

  GetTsnMacAddrSubRegion (&TsnMacAddrSubRegion, &TsnMacAddrSubRegionSize);
  GetPseTsnIpConfigSubRegion (&PseTsnIpConfigSubRegion, &PseTsnIpConfigSubRegionSize);
  GetTsnConfigSubRegion (&TsnConfigSubRegion, &TsnConfigSubRegionSize);

  /*
  TsnSubRegion[0] - Tsn Mac Address Sub-region
  TsnSubRegion[1] - Pse Tsn Ip Config Sub-region
  TsnSubRegion[2] - Tsn Config Sub-region
  */
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TsnMacAddrBase,            TsnConfig->TsnSubRegion[0].BaseAddress, (UINTN) TsnMacAddrSubRegion);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TsnMacAddrSize,            TsnConfig->TsnSubRegion[0].Size,        (UINT32) TsnMacAddrSubRegionSize);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PseTsnIpConfigBase,        TsnConfig->TsnSubRegion[1].BaseAddress, (UINTN) PseTsnIpConfigSubRegion);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PseTsnIpConfigSize,        TsnConfig->TsnSubRegion[1].Size,        (UINT32) PseTsnIpConfigSubRegionSize);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TsnConfigBase,             TsnConfig->TsnSubRegion[2].BaseAddress, (UINTN) TsnConfigSubRegion);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TsnConfigSize,             TsnConfig->TsnSubRegion[2].Size,        (UINT32) TsnConfigSubRegionSize);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchTsnEnable,              TsnConfig->PchTsnEnable,                PchSetup->PchTsnEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchTsnGbeMultiVcEnable,    TsnConfig->PchTsnGbeMultiVcEnable,      PchSetup->PchTsnGbeMultiVcEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchTsnGbeLinkSpeed,        TsnConfig->PchTsnGbeLinkSpeed,          PchSetup->PchTsnGbeLinkSpeed);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchTsnGbeSgmiiEnable,      TsnConfig->PchTsnGbeSgmiiEnable,        PchSetup->PchTsnGbeSgmiiEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PseTsnGbeMultiVcEnable[0], TsnConfig->PseTsnGbeMultiVcEnable[0],   PchSetup->PseTsnGbeMultiVcEnable[0]);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PseTsnGbeLinkSpeed[0],     TsnConfig->PseTsnGbeLinkSpeed[0],       PchSetup->PseTsnGbeLinkSpeed[0]);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PseTsnGbeSgmiiEnable[0],   TsnConfig->PseTsnGbeSgmiiEnable[0],     PchSetup->PseTsnGbeSgmiiEnable[0]);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PseTsnGbeMultiVcEnable[1], TsnConfig->PseTsnGbeMultiVcEnable[1],   PchSetup->PseTsnGbeMultiVcEnable[1]);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PseTsnGbeLinkSpeed[1],     TsnConfig->PseTsnGbeLinkSpeed[1],       PchSetup->PseTsnGbeLinkSpeed[1]);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PseTsnGbeSgmiiEnable[1],   TsnConfig->PseTsnGbeSgmiiEnable[1],     PchSetup->PseTsnGbeSgmiiEnable[1]);
}

/**
  Update DMI config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateDmiConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  PCH_DMI_CONFIG                  *DmiConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchDmiConfigGuid, (VOID *) &DmiConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  DmiConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchDmiAspmCtrl, DmiConfig->DmiAspmCtrl, PchSetup->PchDmiAspm);
}

/**
  Get Bios Guard variable

  @param[in] FspmUpd                   Pointer to FSPM_UPD struct
  @param[in] CpuSecurityPreMemConfig   Pointer to CPU Security PreMem Config
**/
STATIC
UINT32
GetBiosGuardEnable (
  IN VOID                        *FspmUpd,
  IN CPU_SECURITY_PREMEM_CONFIG  *CpuSecurityPreMemConfig
  )
{
  UINT32 BiosGuard;
  GET_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.BiosGuard, CpuSecurityPreMemConfig->BiosGuard, BiosGuard);

  return BiosGuard;
}

/**
  Update LockDown config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
  @param[in] BiosGuardEnable      BIOS Guard enable
**/
STATIC
VOID
UpdateLockDownConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup,
  IN UINT32                    BiosGuardEnable
  )
{
  PCH_LOCK_DOWN_CONFIG            *LockDownConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gLockDownConfigGuid, (VOID *) &LockDownConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  LockDownConfig = NULL;
#endif

  //
  // BiosGuard is capable of overriding PCH BIOS protection.
  // So only need to consider the case when BiosGuard is disabled here
  //
  if (IsBiosUpdateRequired () && !BiosGuardEnable) {
    DEBUG ((DEBUG_INFO, "Disabling BIOS lock for BIOS Update Process\n"));
    PchSetup->PchBiosLock = 0;

    DEBUG ((DEBUG_INFO, "Disabling BIOS interface lockdown for supporting Fault tolerant BIOS Update\n"));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchLockDownBiosInterface, LockDownConfig->BiosInterface, FALSE);
  }

  if (BiosGuardEnable) {
    DEBUG ((DEBUG_INFO, "Enable InSMM.STS (EISS) and BIOS Lock Enable (BLE) since BIOS Guard is enabled.\n"));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchLockDownBiosLock, LockDownConfig->BiosLock, TRUE);
  } else {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchLockDownBiosLock, LockDownConfig->BiosLock, PchSetup->PchBiosLock);
  }
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchUnlockGpioPads, LockDownConfig->UnlockGpioPads, PchSetup->UnlockGpioPads);
}

/**
  Update Pm config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
  @param[in] SetupVariables       Pointer to SETUP_DATA buffer
**/
STATIC
VOID
UpdatePmConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup,
  IN SETUP_DATA                *SetupVariables
  )
{
  PCH_PM_CONFIG                   *PmConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PmConfig = NULL;
#endif
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmDeepSxPol,          PmConfig->PchDeepSxPol,                  PchSetup->DeepSxMode);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmWolEnableOverride,  PmConfig->WakeConfig.WolEnableOverride,  PchSetup->PchWakeOnLan);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmWoWlanEnable,       PmConfig->WakeConfig.WoWlanEnable,       PchSetup->PchWakeOnWlan);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmWoWlanDeepSxEnable, PmConfig->WakeConfig.WoWlanDeepSxEnable, PchSetup->PchWakeOnWlanDeepSx);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmLanWakeFromDeepSx , PmConfig->WakeConfig.LanWakeFromDeepSx,  PchSetup->LanWakeFromDeepSx);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmSlpLanLowDc,        PmConfig->SlpLanLowDc,                   PchSetup->SlpLanLowDc);

  // Power Button Override Period (PBOP): refer to EDS for detail
  // Encoding:
  // 000b - 4 seconds
  // 011b - 10 seconds
  // power button behavior will depend on this setting and other features
  // such as power button SMI which will shutdown system immediately when it is enabled in pre-OS.
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmPwrBtnOverridePeriod, PmConfig->PwrBtnOverridePeriod, !!SetupVariables->LowPowerS0Idle? 0x3 : 0);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmDisableDsxAcPresentPulldown, PmConfig->DisableDsxAcPresentPulldown, PchSetup->DisableDsxAcPresentPulldown);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmMeWakeSts,              PmConfig->MeWakeSts,             TRUE);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmPciePllSsc,             PmConfig->PciePllSsc,            PchSetup->PciePllSsc);
  //
  // TCO Timer Enable required for Simics
  //
  if (IsSimicsEnvironment ()) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableTcoTimer,              PmConfig->EnableTcoTimer,        TRUE);
  } else {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableTcoTimer,              PmConfig->EnableTcoTimer,        PchSetup->EnableTcoTimer);
  }
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableTimedGpio0,            PmConfig->EnableTimedGpio0,      PchSetup->EnableTimedGpio0);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.EnableTimedGpio1,            PmConfig->EnableTimedGpio1,      PchSetup->EnableTimedGpio1);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmcDbgMsgEn,                 PmConfig->PmcDbgMsgEn,           PchSetup->PmcDbgMsgEn);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmVrAlert,                PmConfig->VrAlert,               PcdGetBool (PcdVrAlertEnable));
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmcCpuC10GatePinEnable,      PmConfig->CpuC10GatePinEnable,   1);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmcModPhySusPgEnable,        PmConfig->ModPhySusPgEnable,     IsPchLp ());
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmcUsb2PhySusPgEnable,       PmConfig->Usb2PhySusPgEnable,    PchSetup->PchUsb2SusWellPgEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmcOsIdleEnable,             PmConfig->OsIdleEnable,          0);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmcGrTscEnable,              PmConfig->GrTscEnable,           PchSetup->PmcGrTscEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchS0ixAutoDemotion,         PmConfig->S0ixAutoDemotion,      PchSetup->PchS0ixAutoDemotion);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchPmLatchEventsC10Exit,     PmConfig->LatchEventsC10Exit,    PchSetup->PchLatchEventsC10Exit);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmcV1p05PhyExtFetControlEn,  PmConfig->V1p05PhyExtFetControlEn,  PchSetup->V1p05PhyExtFetControlEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PmcV1p05IsExtFetControlEn,   PmConfig->V1p05IsExtFetControlEn,   PchSetup->V1p05IsExtFetControlEnable);
}

/**
  Update Fivr config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateFivrConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  UINT8                        Index;
  PCH_FIVR_CONFIG              *FivrConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gFivrConfigGuid, (VOID *) &FivrConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  FivrConfig = NULL;
#endif

  for (Index = 0; Index < FIVR_RAIL_S0IX_SX_STATES_MAX; Index++) {
    OR_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtV1p05RailEnabledStates,  FivrConfig->ExtV1p05Rail.EnabledStates, (PchSetup->ExternalV1p05StateEnable[Index] << Index));
    OR_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtVnnRailEnabledStates,    FivrConfig->ExtVnnRail.EnabledStates,   (PchSetup->ExternalVnnStateEnable[Index] << Index));
    OR_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtVnnRailSxEnabledStates,  FivrConfig->ExtVnnRailSx.EnabledStates, (PchSetup->ExternalVnnSxStateEnable[Index] << Index));
  }
  for (Index = 0; Index < FIVR_RAIL_EXT_VOLTAGE_STATES_MAX; Index++) {
    OR_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtV1p05RailSupportedVoltageStates,  FivrConfig->ExtV1p05Rail.SupportedVoltageStates, (PchSetup->ExternalV1p05SupportedVoltageStates[Index] << Index));
    OR_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtVnnRailSupportedVoltageStates,    FivrConfig->ExtVnnRail.SupportedVoltageStates,   (PchSetup->ExternalVnnSupportedVoltageStates[Index] << Index));
  }
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtV1p05RailIccMax,  FivrConfig->ExtV1p05Rail.IccMax,  PchSetup->ExternalV1p05IccMax);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtV1p05RailVoltage, FivrConfig->ExtV1p05Rail.Voltage, PchSetup->ExternalV1p05Voltage);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtVnnRailIccMax,    FivrConfig->ExtVnnRail.IccMax,    PchSetup->ExternalVnnIccMax);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtVnnRailVoltage,   FivrConfig->ExtVnnRail.Voltage,   PchSetup->ExternalVnnVoltage);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtVnnRailSxIccMax,  FivrConfig->ExtVnnRailSx.IccMax , PchSetup->ExternalVnnSxIccMax);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrExtVnnRailSxVoltage, FivrConfig->ExtVnnRailSx.Voltage, PchSetup->ExternalVnnSxVoltage);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrVccinAuxLowToHighCurModeVolTranTime, FivrConfig->VccinAux.LowToHighCurModeVolTranTime, PchSetup->PchLowToHighCurModeVolTranTime);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrVccinAuxRetToHighCurModeVolTranTime, FivrConfig->VccinAux.RetToHighCurModeVolTranTime, PchSetup->PchRetToHighCurModeVolTranTime);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrVccinAuxRetToLowCurModeVolTranTime,  FivrConfig->VccinAux.RetToLowCurModeVolTranTime , PchSetup->PchRetToLowCurModeVolTranTime);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrVccinAuxOffToHighCurModeVolTranTime, FivrConfig->VccinAux.OffToHighCurModeVolTranTime, PchSetup->PchOffToHighCurModeVolTranTime);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchFivrDynPm, FivrConfig->FivrDynPm, PchSetup->PchFivrDynPm);
}

/**
  Update Espi config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateEspiConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  PCH_ESPI_CONFIG                 *EspiConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gEspiConfigGuid, (VOID *) &EspiConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  EspiConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchEspiLgmrEnable, EspiConfig->LgmrEnable, PchSetup->PchEspiLgmrEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchEspiHostC10ReportEnable, EspiConfig->HostC10ReportEnable, PchSetup->PchEspiHostC10ReportEnable);
}

/**
  Update Psf config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdatePsfConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  PSF_CONFIG                 *PsfConfig;
#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
  EFI_STATUS                 Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPsfConfigGuid, (VOID *) &PsfConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PsfConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PsfTccEnable, PsfConfig->TccEnable, PchSetup->PsfTccEnable);
}

/**
  Update FIA configuration.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
  @param[in] PchSetup  Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateFiaConfig (
  IN SI_POLICY_PPI  *SiPolicy,
  IN VOID           *FspsUpd,
  IN PCH_SETUP      *PchSetup
  )
{
  PCH_FIA_CONFIG   *FiaConfig;

#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
  EFI_STATUS        Status;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gFiaConfigGuid, (VOID *) &FiaConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  FiaConfig = NULL;
#endif
  //
  // FIA Configuration
  //
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.FiaLaneReversalEnable, FiaConfig->LaneReversalEnable, ((PchSetup->FiaLaneReversalEnable[0] << 0)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[1] << 1)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[2] << 2)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[3] << 3)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[4] << 4)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[5] << 5)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[6] << 6)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[7] << 7)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[8] << 8)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[9] << 9)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[10] << 10)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[11] << 11)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[12] << 12)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[13] << 13)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[14] << 14)
                                                                                                          |(PchSetup->FiaLaneReversalEnable[15] << 15)) & 0xFFFF);
}

/**
  Update FlashProtection config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
  @param[in] BiosGuardEnable      BIOS Guard enable
**/
STATIC
VOID
UpdateFlashProtectionConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup,
  IN UINT32                    BiosGuardEnable
  )
{
  UINT32                          BaseAddr;
  UINT32                          RegionSize;
  BOOLEAN                         FlashProtectionEnabled;
  EFI_STATUS                      Status;
  PCH_SPI_PPI                     *SpiPpi;
  UINT16                          ProtectedRangeBase;
  UINT16                          ProtectedRangeLimit;
  PCH_FLASH_PROTECTION_CONFIG     *FlashProtectionConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  Status = GetConfigBlock ((VOID *) SiPolicy, &gFlashProtectionConfigGuid, (VOID *) &FlashProtectionConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  FlashProtectionConfig = NULL;
#endif
  FlashProtectionEnabled = PchSetup->FprrEnable;

  //
  // BiosGuard is capable of overriding PCH BIOS protection.
  // So only need to consider the case when BiosGuard is disabled here
  //
  if (IsBiosUpdateRequired () && !BiosGuardEnable) {
    DEBUG ((DEBUG_INFO, "Disable Flash Protection Range Registers for BIOS Update Process\n"));
    FlashProtectionEnabled = FALSE;
  }

  //
  // Flash Protection Range Register initialization
  //
  if (FlashProtectionEnabled) {
    Status = PeiServicesLocatePpi (
               &gPchSpiPpiGuid,
               0,
               NULL,
               (VOID **)&SpiPpi
               );

    DEBUG ((DEBUG_INFO, "Enabling Flash Protection Range: LocatePpi gPchSpiPpiGuid = %r\n", Status));
    if (EFI_ERROR (Status)) {
      return;
    }
    //
    // Find the base address for BIOS region
    //
    Status = SpiPpi->GetRegionAddress (SpiPpi, FlashRegionBios, &BaseAddr, &RegionSize);
    DEBUG ((DEBUG_INFO, "BIOS Region: %r - Start Address: 0x%x - Size: 0x%x\n", Status, BaseAddr, RegionSize));
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return;
    }
    //
    // Initialize flash protection
    //
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchWriteProtectionEnable[0], FlashProtectionConfig->ProtectRange[0].WriteProtectionEnable, TRUE);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchReadProtectionEnable[0],  FlashProtectionConfig->ProtectRange[0].ReadProtectionEnable, FALSE);
    //
    // Assign FPRR ranges
    //
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchProtectedRangeBase[0],   FlashProtectionConfig->ProtectRange[0].ProtectedRangeBase,  (UINT16)((BaseAddr + FixedPcdGet32 (PcdFlashNvStorageSize)) >> 12));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchProtectedRangeLimit[0],  FlashProtectionConfig->ProtectRange[0].ProtectedRangeLimit, (UINT16)(((BaseAddr + RegionSize) - 1) >> 12));

    GET_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchProtectedRangeBase[0], FlashProtectionConfig->ProtectRange[0].ProtectedRangeBase, ProtectedRangeBase);
    GET_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchProtectedRangeLimit[0], FlashProtectionConfig->ProtectRange[0].ProtectedRangeLimit, ProtectedRangeLimit);
    DEBUG ((DEBUG_INFO, "FlashProtectionConfig->ProtectRange[0].ProtectedRangeBase  %x\n", ProtectedRangeBase));
    DEBUG ((DEBUG_INFO, "FlashProtectionConfig->ProtectRange[0].ProtectedRangeLimit %x\n", ProtectedRangeLimit));
  }
}

/**
  Update Rtc config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateRtcConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  RTC_CONFIG                   *RtcConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gRtcConfigGuid, (VOID *) &RtcConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  RtcConfig = NULL;
#endif
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.RtcBiosInterfaceLock, RtcConfig->BiosInterfaceLock, TRUE);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.RtcMemoryLock, RtcConfig->MemoryLock, PchSetup->PchRtcMemoryLock);
}

/**
  Update SATA Controller configuration.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
  @param[in] PchSetup  Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateSataConfig (
  IN SI_POLICY_PPI  *SiPolicy,
  IN VOID           *FspsUpd,
  IN PCH_SETUP      *PchSetup
  )
{
  SATA_CONFIG         *SataConfig;
  UINTN               SataCtrlIndex;
  UINT8               MaxSataPorts;
  UINT8               Index;

  SataConfig = NULL;

#if FixedPcdGet8(PcdFspModeSelection) == 0
  for (SataCtrlIndex = 0; SataCtrlIndex < MaxSataControllerNum (); SataCtrlIndex++) {
    SataConfig = GetPchSataConfig (SiPolicy, SataCtrlIndex);
#else
  for (SataCtrlIndex = 0; SataCtrlIndex < MaxSataControllerNum () && SataCtrlIndex < 1; SataCtrlIndex++) {
#endif
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataEnable,       SataConfig->Enable,       PchSetup->PchSata);

    MaxSataPorts = MaxSataPortNum (SataCtrlIndex);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataMode,         SataConfig->SataMode,     PchSetup->SataInterfaceMode);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPwrOptEnable, SataConfig->PwrOptEnable, TRUE);

    for (Index = 0; Index < MaxSataPorts; Index++) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsEnable[Index], SataConfig->PortSettings[Index].Enable, !!PchSetup->SataTestMode ? TRUE : PchSetup->SataPort[Index]);

      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsHotPlug[Index],          SataConfig->PortSettings[Index].HotPlug,          PchSetup->SataHotPlug[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsSpinUp[Index],           SataConfig->PortSettings[Index].SpinUp,           PchSetup->SataSpinUp[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsExternal[Index],         SataConfig->PortSettings[Index].External,         PchSetup->SataExternal[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsDevSlp[Index],           SataConfig->PortSettings[Index].DevSlp,           PchSetup->PxDevSlp[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsEnableDitoConfig[Index], SataConfig->PortSettings[Index].EnableDitoConfig, PchSetup->EnableDitoConfig[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsDmVal[Index],            SataConfig->PortSettings[Index].DmVal,            PchSetup->DmVal[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsDitoVal[Index],          SataConfig->PortSettings[Index].DitoVal,          PchSetup->DitoVal[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsSolidStateDrive[Index],  SataConfig->PortSettings[Index].SolidStateDrive,  PchSetup->SataType[Index]);
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsRxPolarity[Index],       SataConfig->PortSettings[Index].RxPolarity,       PchSetup->SataRxPolarity[Index]);
    }
    if (PchSeries () == PCH_LP) {
      //
      // Only Mobile boards has interlock switches in SATA Port 0, 1 and 2
      //
#if FixedPcdGet8(PcdFspModeSelection) == 0
      for (Index = 0; Index < MaxSataPorts; Index++) {
#else
      for (Index = 0; Index < MaxSataPorts && Index < 8; Index++) {
#endif
        if (PchSetup->SataHotPlug[Index]) {
          UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortsInterlockSw[Index], SataConfig->PortSettings[Index].InterlockSw, PchSetup->SataMechanicalSw[Index]);
        }
      }
    }

    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstInterrupt,            SataConfig->SataRstInterrupt,                   PchSetup->SataRstInterrupt);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataSalpSupport,             SataConfig->SalpSupport,                        PchSetup->SataSalp);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataPortMultiplier,          SataConfig->PortMultiplier,                     PchSetup->SataPortMultiplier);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstRaidDeviceId,         SataConfig->RaidDeviceId,                       PchSetup->RaidDeviceId);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataLedEnable,               SataConfig->LedEnable,                          PcdGetBool (PcdSataLedEnable));
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataThermalSuggestedSetting, SataConfig->ThermalThrottling.SuggestedSetting, PchSetup->PchSataTsSuggestSet);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP1TDispFinit,            SataConfig->ThermalThrottling.P1TDispFinit,     PchSetup->PchP1TDispFinit);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP1Tinact,                SataConfig->ThermalThrottling.P1Tinact,         PchSetup->PchP1Tinact);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP1TDisp,                 SataConfig->ThermalThrottling.P1TDisp,          PchSetup->PchP1TDisp);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP1T3M,                   SataConfig->ThermalThrottling.P1T3M,            PchSetup->PchP1T3M);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP1T2M,                   SataConfig->ThermalThrottling.P1T2M,            PchSetup->PchP1T2M);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP1T1M,                   SataConfig->ThermalThrottling.P1T1M,            PchSetup->PchP1T1M);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP0TDispFinit,            SataConfig->ThermalThrottling.P0TDispFinit,     PchSetup->PchP0TDispFinit);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP0Tinact,                SataConfig->ThermalThrottling.P0Tinact,         PchSetup->PchP0Tinact);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP0TDisp,                 SataConfig->ThermalThrottling.P0TDisp,          PchSetup->PchP0TDisp);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP0T3M,                   SataConfig->ThermalThrottling.P0T3M,            PchSetup->PchP0T3M);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP0T2M,                   SataConfig->ThermalThrottling.P0T2M,            PchSetup->PchP0T2M);
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataP0T1M,                   SataConfig->ThermalThrottling.P0T1M,            PchSetup->PchP0T1M);
  }
}

/**
  Update RST configuration.

  @param[in] SiPolicy     Pointer to SI_POLICY_PPI
  @param[in] FspsUpd      Pointer to FSPS_UPD
  @param[in] PchSetup     Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateRstConfig (
  IN SI_POLICY_PPI  *SiPolicy,
  IN VOID           *FspsUpd,
  IN PCH_SETUP      *PchSetup
  )
{
  UINT8               Index;
  UINT32              CycleRouterNum;
  RST_CONFIG          *RstConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS          Status;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gRstConfigGuid, (VOID *) &RstConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  RstConfig = NULL;
#endif
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstLegacyOrom,         RstConfig->LegacyOrom,         PchSetup->SataLegacyOrom);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstRaid0,              RstConfig->Raid0,              PchSetup->SataRaidR0);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstRaid1,              RstConfig->Raid1,              PchSetup->SataRaidR1);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstRaid10,             RstConfig->Raid10,             PchSetup->SataRaidR10);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstRaid5,              RstConfig->Raid5,              PchSetup->SataRaidR5);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstIrrt,               RstConfig->Irrt,               PchSetup->SataRaidIrrt);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstOromUiBanner,       RstConfig->OromUiBanner,       PchSetup->SataRaidOub);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstHddUnlock,          RstConfig->HddUnlock,          PchSetup->SataHddlk);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstLedLocate,          RstConfig->LedLocate,          PchSetup->SataLedl);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstIrrtOnly,           RstConfig->IrrtOnly,           PchSetup->SataRaidIooe);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstSmartStorage,       RstConfig->SmartStorage,       PchSetup->SataRaidSrt);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstOromUiDelay,        RstConfig->OromUiDelay,        PchSetup->SataRaidOromDelay);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstOptaneMemory,       RstConfig->OptaneMemory,       PchSetup->SataRstOptaneMemory);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstCpuAttachedStorage, RstConfig->CpuAttachedStorage, PchSetup->SataRstCpuAttachedStorage);

  if (PchSetup->PchSata == TRUE && PchSetup->SataInterfaceMode == SATA_MODE_RAID) {
    for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
      CycleRouterNum = RstGetCycleRouterNumber (Index);
      if (PchSetup->RstPcieRemapEnabled[Index] && CycleRouterNum != RST_PCIE_STORAGE_CR_INVALID) {
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstPcieEnable[CycleRouterNum],      RstConfig->HardwareRemappedStorageConfig[CycleRouterNum].Enable, 1);
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstPcieStoragePort[CycleRouterNum], RstConfig->HardwareRemappedStorageConfig[CycleRouterNum].RstPcieStoragePort, Index + 1);
      }
    }
  } else {
    for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
      UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SataRstPcieEnable[Index], RstConfig->HardwareRemappedStorageConfig[Index].Enable, FALSE);
    }
  }
}

#if FixedPcdGet8(PcdFspModeSelection) == 1
/**
  Update DevInt config

  @param[in] FspsUpd              Pointer to FspsUpd structure
**/
STATIC
VOID
UpdateDevIntConfig (
  IN VOID                      *FspsUpd
  )
{
  ((FSPS_UPD *) FspsUpd)->FspsConfig.DevIntConfigPtr = (UINT32) NULL;
}
#endif

/**
  Update Ieh config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateIehConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  IEH_CONFIG                  *IehConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                  Status;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gIehConfigGuid, (VOID *) &IehConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  IehConfig = NULL;
#endif
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.IehMode, IehConfig->Mode, PchSetup->IehMode);
}

/**
  Update Interrupt config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdateInterruptConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  PCH_INTERRUPT_CONFIG         *InterruptConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gInterruptConfigGuid, (VOID *) &InterruptConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  InterruptConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.GpioIrqRoute, InterruptConfig->GpioIrqRoute, PchSetup->PchGpioIrqRoute);
}

/**
  Update PCH General config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
UpdatePchGeneralConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{
  PCH_GENERAL_CONFIG           *PchGeneralConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                   Status;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PchGeneralConfig = NULL;
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchCrid, PchGeneralConfig->Crid, PchSetup->PchCrid);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchLegacyIoLowLatency, PchGeneralConfig->LegacyIoLowLatency, PchSetup->PchLegacyIoLowLatency);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMasterClockGating, PchGeneralConfig->PchMasterClockGating, PchSetup->PchMasterClockGating);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PchMasterPowerGating, PchGeneralConfig->PchMasterPowerGating, PchSetup->PchMasterPowerGating);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SciPinMuxEnable,      PchGeneralConfig->SciPinMuxEnable,      PchSetup->SciPinMuxEnable);
}

/**
  Correct mismatch configuration of ISH and Serial IO

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
**/
STATIC
VOID
CorrectMismatchConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup
  )
{

}

/**
  Update Fusa config

  @param[in] SiPolicy             Pointer to SI_POLICY_PPI
  @param[in] FspsUpd              Pointer to FspsUpd structure
  @param[in] PchSetup             Pointer to PCH_SETUP buffer
  @param[in] SaSetup              Pointer to SA_SETUP buffer
**/
STATIC
VOID
UpdateFusaConfig (
  IN SI_POLICY_PPI             *SiPolicy,
  IN VOID                      *FspsUpd,
  IN PCH_SETUP                 *PchSetup,
  IN SA_SETUP                  *SaSetup
  )
{
  FUSA_CONFIG                *FusaConfig;
  FusaConfig = NULL;

#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                 Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gFusaConfigGuid, (VOID *) &FusaConfig);
  if (EFI_ERROR (Status)) {
    return;
  }
#endif
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.DisplayFusaConfigEnable, FusaConfig->DisplayFusaConfigEnable, SaSetup->DisplayFusaConfigEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.GraphicFusaConfigEnable, FusaConfig->GraphicFusaConfigEnable, SaSetup->GraphicFusaConfigEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.OpioFusaConfigEnable, FusaConfig->OpioFusaConfigEnable, SaSetup->OpioFusaConfigEnable);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.PsfFusaConfigEnable, FusaConfig->PsfFusaConfigEnable, PchSetup->PsfFusaConfigEnable);
}

/**
  This function performs PCH PEI Policy initialization.

  @retval EFI_SUCCESS             The PPI is installed and initialized.
  @retval EFI ERRORS              The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
UpdatePeiPchPolicy (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  UINTN                           VariableSize;
  SA_SETUP                        SaSetup;
  CPU_SETUP                       CpuSetup;
  PCH_SETUP                       PchSetup;
  SETUP_DATA                      SetupVariables;
  DEBUG_CONFIG_DATA               DebugConfigData;
  VOID                            *FspsUpd;
  SI_POLICY_PPI                   *SiPolicy;
  UINT32                          BiosGuardEnable;
  VOID                            *FspmUpd;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  CPU_SECURITY_PREMEM_CONFIG      *CpuSecurityPreMemConfig;

  DEBUG ((DEBUG_INFO, "Update PeiPchPolicyUpdate Pos-Mem Start\n"));

  FspsUpd                 = NULL;
  FspmUpd                 = NULL;
  SiPolicy                = NULL;
  CpuSecurityPreMemConfig = NULL;
  SiPreMemPolicyPpi       = NULL;

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = (FSPM_UPD *) PcdGet32 (PcdFspmUpdDataAddress);
  ASSERT (FspmUpd != NULL);
  FspsUpd = (FSPS_UPD *) PcdGet32 (PcdFspsUpdDataAddress);
  ASSERT (FspsUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }
#endif

  BiosGuardEnable = GetBiosGuardEnable (FspmUpd, CpuSecurityPreMemConfig);

  //
  // Retrieve Setup variable
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid, // GUID
             0,                                // INSTANCE
             NULL,                             // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices       // PPI
             );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SetupVariables
                               );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SA_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"SaSetup",
                               &gSaSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SaSetup
                               );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (CPU_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"CpuSetup",
                               &gCpuSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &CpuSetup
                               );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &PchSetup
                               );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (DEBUG_CONFIG_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"DebugConfigData",
                               &gDebugConfigVariableGuid,
                               NULL,
                               &VariableSize,
                               &DebugConfigData
                               );
DEBUG_CODE_BEGIN();
  ASSERT_EFI_ERROR (Status);
DEBUG_CODE_END();

#if FixedPcdGet8(PcdFspModeSelection) == 1
  //
  // Interrupt Config
  //
  UpdateDevIntConfig (FspsUpd);
#endif

  UpdatePchGeneralConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateGbeConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateTsnConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateSataConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateThcConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateDmiConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdatePcieRpConfig (SiPolicy, FspsUpd, &PchSetup, &SetupVariables);
  UpdateHdAudioConfig (SiPolicy, SiPreMemPolicyPpi, FspsUpd, FspmUpd, &PchSetup);
  UpdateLockDownConfig (SiPolicy, FspsUpd, &PchSetup, BiosGuardEnable);
  UpdateRtcConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateFlashProtectionConfig (SiPolicy, FspsUpd, &PchSetup, BiosGuardEnable);
  //
  //  FIVR Configuration
  //
  UpdateFivrConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateIehConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateIoApicConfig (SiPolicy, FspsUpd, &PchSetup, &SetupVariables);
  UpdateInterruptConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateSerialIoConfig (SiPolicy, FspsUpd, &PchSetup, &DebugConfigData, &SetupVariables);
  UpdatePmConfig (SiPolicy, FspsUpd, &PchSetup, &SetupVariables);
  UpdateThermalConfig (SiPolicy, FspsUpd, &PchSetup, &SaSetup);
  UpdateUsbConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdatePchUsb2PhyConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateEmmcConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateSdCardConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateUfsConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateSiipConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdatePseConfig (SiPolicy, FspsUpd, &PchSetup);
  CorrectMismatchConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateCnviConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateEspiConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdatePsfConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateFiaConfig (SiPolicy, FspsUpd, &PchSetup);
  UpdateFusaConfig (SiPolicy, FspsUpd, &PchSetup, &SaSetup);

  return EFI_SUCCESS;
}

