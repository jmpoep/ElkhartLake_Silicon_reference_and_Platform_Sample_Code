/** @file
  @This file implements the parser functions to parse 3DXP device Mailbox output
  payload and populate the 2LM Info HOB.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#include <Uefi.h>
#include <Pi/PiBootMode.h>
#include <Pi/PiHob.h>
#include <Library/DebugLib.h>
#include <Library/TwoLmInitLib.h>

/**
This function would issue Identify2lmModuleInfo  Mailbox Command
And parse the output payload to store the required information in 2lm info HOB
to be used by the other boot stages.

@param[in]      TwoLmInfo            2LM HOB which will have necessary values to initialize FMHC.

@retval EFI_SUCCESS            Successfully retrieve 2LM module info
**/
EFI_STATUS
EFIAPI
GetTwoLmModuleInfo (
  IN TWOLM_INFO_HOB *TwoLmInfoHob
)
{
  UINT8                   DeviceReturnStatus;
  UINT8                   OutputPayloadSizeDw;
  DEVICE_2LM_INFORMATION   Device2lmInfo;
  EFI_STATUS               Status;

  DeviceReturnStatus  = 0;
  OutputPayloadSizeDw = sizeof(Device2lmInfo); //or maybe #define size as per the latest FIS version
  // Converting size in DW
  if ((OutputPayloadSizeDw & 0x3) == 0) {
    OutputPayloadSizeDw = OutputPayloadSizeDw / 4;
  } else {
    OutputPayloadSizeDw = (OutputPayloadSizeDw / 4) + 1;
  }

  DEBUG ((DEBUG_INFO, "2LM: Issuing Identify2lmModuleCommand to get the info from far memory device\n"));

  Status = Identify2lmModuleCommand (&DeviceReturnStatus, (UINT32 *)(&Device2lmInfo), OutputPayloadSizeDw);
  if (Status != EFI_SUCCESS){
    DEBUG ((DEBUG_INFO, "Mailbox Communication Error\n"));
    //@tbd check if need to RETRY for certain timeout value
    return Status;
  }
  if (DeviceReturnStatus) { // if the return Status is other than 00h (Success)
    DEBUG ((DEBUG_INFO, "3DXP Device Error\n"));
    return EFI_DEVICE_ERROR;
  }

  // Getting the Region Capabilities
  TwoLmInfoHob->TwoLmInfo.PlatformRegionRequired = (UINT8)Device2lmInfo.REGION_CAPABILITIES_Union.REGION_CAPABILITIES_Struct.PlatformRegionRequired;

  // Getting provisioning Status
  TwoLmInfoHob->TwoLmInfo.DeviceProvisioningStatus = Device2lmInfo.CAPABILITIES_2LM.Byte130_Union.Byte_130_Struct.RegionProvisioned;
  // Getting TotalNumberofRegions
  TwoLmInfoHob->TwoLmInfo.TotalNumberofRegions = Device2lmInfo.CAPABILITIES_2LM.Byte130_Union.Byte_130_Struct.TotalNumberOfRegions;
  // Getting encryption Status for 2LM
  TwoLmInfoHob->TwoLmInfo.MemoryEncryptionSupported = (UINT8)Device2lmInfo.MODULE_2LM_SKU_Union.MODULE_2LM_SKU_Struct.MemoryEncryption;

  // Getting max outstanding credit information
  TwoLmInfoHob->TwoLmInfo.Mrts = (UINT8)Device2lmInfo.CAPABILITIES_2LM.Mrts;
  TwoLmInfoHob->TwoLmInfo.Mwss = (UINT8)Device2lmInfo.CAPABILITIES_2LM.Mwss;
  TwoLmInfoHob->TwoLmInfo.Mcsrts = (UINT8)Device2lmInfo.CAPABILITIES_2LM.Mcsrts;

  // Getting device version information
  TwoLmInfoHob->TwoLmInfo.VendorId   = (UINT16)Device2lmInfo.VendorID;
  TwoLmInfoHob->TwoLmInfo.DevId      = (UINT16)Device2lmInfo.DeviceID;
  TwoLmInfoHob->TwoLmInfo.RevisionId = (UINT16)Device2lmInfo.RevisionID;
  TwoLmInfoHob->TwoLmInfo.Ifc        = (UINT16)Device2lmInfo.IFC;
  TwoLmInfoHob->TwoLmInfo.SerialNum  = *(UINT32*)Device2lmInfo.SerialNumber;

  // Getting 2LM Module SKU Information
  TwoLmInfoHob->TwoLmInfo.MemoryModeSupported = (UINT8)Device2lmInfo.MODULE_2LM_SKU_Union.MODULE_2LM_SKU_Struct.MemoryModeSupported;
  TwoLmInfoHob->TwoLmInfo.StorageModeSupported = (UINT8)Device2lmInfo.MODULE_2LM_SKU_Union.MODULE_2LM_SKU_Struct.StorageModeSupported;
  TwoLmInfoHob->TwoLmInfo.PMemModeSupported = (UINT8)Device2lmInfo.MODULE_2LM_SKU_Union.MODULE_2LM_SKU_Struct.PMemModeSupported;
  TwoLmInfoHob->TwoLmInfo.DieSparingCapable = (UINT8)Device2lmInfo.MODULE_2LM_SKU_Union.MODULE_2LM_SKU_Struct.DieSparingCapable;
  DEBUG ((DEBUG_INFO, "RevisionId: %d \t SerialNum: %d\n", TwoLmInfoHob->TwoLmInfo.RevisionId, TwoLmInfoHob->TwoLmInfo.SerialNum));
  DEBUG ((DEBUG_INFO, "MemoryModeSupported: %d \t PMemModeSupported: %d\n", TwoLmInfoHob->TwoLmInfo.MemoryModeSupported, TwoLmInfoHob->TwoLmInfo.PMemModeSupported));
  return EFI_SUCCESS;
}


/**
This function would issue QueryRegion  Mailbox Command
And parse the output payload to store the required information in 2lm info HOB
to be used by the other boot stages.

@param[in]      TwoLmInfo            2LM HOB which will have necessary values to initialize FMHC.

@retval EFI_SUCCESS            Successfully retrieve region info
**/
EFI_STATUS
EFIAPI
GetQueryRegionInfo (
  IN TWOLM_INFO_HOB *TwoLmInfoHob
)
{
  UINT8                       DeviceReturnStatus;
  UINT8                       OutputPayloadSizeDw;
  UINT8                       RegionId;
  REGION_LAYOUT_INFORMATION   RegionLayoutInfo[MAX_REGIONS];
  EFI_STATUS                  Status;
  int                         i;

  DeviceReturnStatus  = 0;
  RegionId            = 0xFF; // To query all the regions
  OutputPayloadSizeDw = sizeof(REGION_LAYOUT_INFORMATION)*MAX_REGIONS; //or maybe #define size as per the latest FIS version
  // Converting size in DW
  if ((OutputPayloadSizeDw & 0x3) == 0) {
    OutputPayloadSizeDw = OutputPayloadSizeDw / 4;
  } else {
    OutputPayloadSizeDw = (OutputPayloadSizeDw / 4) + 1;
  }

  if (!TwoLmInfoHob->TwoLmInfo.DeviceProvisioningStatus) {
    DEBUG ((DEBUG_INFO, "Device is not provisioned yet\n"));
    return EFI_DEVICE_ERROR;
  }
  if (TwoLmInfoHob->TwoLmInfo.TotalNumberofRegions > MAX_REGIONS) {
    DEBUG ((DEBUG_INFO, "Region Layout info buffer is small to read details of all regions\n"));
    return EFI_BUFFER_TOO_SMALL;
  }

  DEBUG ((DEBUG_INFO, "2LM: Issuing Query Region Layout to get the info of far memory device regions\n"));

  Status = QueryRegionLayoutCommand (&DeviceReturnStatus, (UINT32 *)RegionLayoutInfo, OutputPayloadSizeDw, RegionId);

  if (Status != EFI_SUCCESS){
    DEBUG ((DEBUG_INFO, "Mailbox Communication Error\n"));
    //@tbd check if need to RETRY for certain timeout value
    return Status;
  }
  if (DeviceReturnStatus) { // if the return Status is other than 00h (Success)
    DEBUG ((DEBUG_INFO, "3DXP Device Error\n"));
    return EFI_DEVICE_ERROR;
  }

  // Find out region details
  for (i=0; i < MAX_REGIONS; ++i) {
    if (!RegionLayoutInfo[i].DW0Data_Union.DW0Bits.RegionValidindicator) { // Check if region is valid
      continue;  //continue to find next valid region
    }
    switch (RegionLayoutInfo[i].DW0Data_Union.DW0Bits.BiosRegionType) {

      case NVMeStorage:
        if (RegionLayoutInfo[i].DW0Data_Union.DW0Bits.RegionAttr_Mem_Storage != StorageMode){
          DEBUG ((DEBUG_INFO, "Region Attribute Mismatch\n"));
          return EFI_DEVICE_ERROR;
        }
        TwoLmInfoHob->TwoLmInfo.RegionIdStorage = (UINT8)RegionLayoutInfo[i].DW0Data_Union.DW0Bits.RegionId;
        TwoLmInfoHob->TwoLmInfo.StorageSize = RegionLayoutInfo[i].RegionSize;
        DEBUG ((DEBUG_INFO, "2LM: StorageSize %d MB\n", TwoLmInfoHob->TwoLmInfo.StorageSize));
        break;

      case VolatileMemory:
        if (RegionLayoutInfo[i].DW0Data_Union.DW0Bits.RegionAttr_Mem_Storage != MemoryMode){
          DEBUG ((DEBUG_INFO, "Region Attribute Mismatch\n"));
          return EFI_DEVICE_ERROR;
        }
        TwoLmInfoHob->TwoLmInfo.RegionId2lm = (UINT8)RegionLayoutInfo[i].DW0Data_Union.DW0Bits.RegionId;
        TwoLmInfoHob->TwoLmInfo.FarMemSize = RegionLayoutInfo[i].RegionSize;
        TwoLmInfoHob->TwoLmInfo.FarMemFZS  = (UINT8)RegionLayoutInfo[i].DW0Data_Union.DW0Bits.RegionAttr_FastZero;
        DEBUG ((DEBUG_INFO, "2LM: FarMemSize %d MB\n", TwoLmInfoHob->TwoLmInfo.FarMemSize));
        break;

      case IntelReservedRegionMemory:
        if (RegionLayoutInfo[i].DW0Data_Union.DW0Bits.RegionAttr_Mem_Storage != MemoryMode){
          DEBUG ((DEBUG_INFO, "Region Attribute Mismatch\n"));
          return EFI_DEVICE_ERROR;
        }
        TwoLmInfoHob->TwoLmInfo.RegionIdIrr = (UINT8)RegionLayoutInfo[i].DW0Data_Union.DW0Bits.RegionId;
        TwoLmInfoHob->TwoLmInfo.IrrSize = RegionLayoutInfo[i].RegionSize;
        DEBUG ((DEBUG_INFO, "2LM: IrrSize %d MB\n", TwoLmInfoHob->TwoLmInfo.IrrSize));
        break;

      case PersistenceMemory:
        if (RegionLayoutInfo[i].DW0Data_Union.DW0Bits.RegionAttr_Mem_Storage != MemoryMode){
          DEBUG ((DEBUG_INFO, "Region Attribute Mismatch\n"));
          return EFI_DEVICE_ERROR;
        }
        TwoLmInfoHob->TwoLmInfo.RegionIdPMem = (UINT8)RegionLayoutInfo[i].DW0Data_Union.DW0Bits.RegionId;
        TwoLmInfoHob->TwoLmInfo.PMemSize = RegionLayoutInfo[i].RegionSize;
        DEBUG ((DEBUG_INFO, "2LM: PMemSize %d MB\n", TwoLmInfoHob->TwoLmInfo.PMemSize));
        break;

      default:
         break;
    } // End of switch-case

    // Check if this is the last region provisioned
    if (RegionLayoutInfo[i].DW0Data_Union.DW0Bits.LastRegionIndicator) {
      DEBUG ((DEBUG_INFO, "This is the last region provisioned, hence exiting the parser function\n"));
      return EFI_SUCCESS;
    }
  } // End of for

return EFI_SUCCESS;
}


/**
This function would issue SetHwParametersCommand  Mailbox Command to set the HW parameters
of far memory device as per internal/external user selection.
HW Parameter must be sent for every PERST cycle (cold or warm boot).
The value is only stick over low power state but not PERST

@param[in]      TwoLmConfig            2LM Config block.

@retval         EFI_SUCCESS            Successful completion of command
**/
EFI_STATUS
EFIAPI
SetHardwareParameters (
   IN TWOLM_PREMEM_CONFIG      *TwoLmPreMemConfig
)
{
  UINT8                   DeviceReturnStatus;
  UINT8                   InputPayloadSizeDw;
  HW_PARAMETERS           HwParameters;
  EFI_STATUS               Status;

  DeviceReturnStatus  = 0;
  InputPayloadSizeDw = sizeof(HwParameters);
  // Converting size in DW
  if ((InputPayloadSizeDw & 0x3) == 0) {
    InputPayloadSizeDw = InputPayloadSizeDw / 4;
  } else {
    InputPayloadSizeDw = (InputPayloadSizeDw / 4) + 1;
  }

  // Set the HwParemeters command buffer as per the user selection
  if (TwoLmPreMemConfig->SetHwParameters) {
    HwParameters.Ltr_L1D2_ThVal   =   (UINT16)TwoLmPreMemConfig->Ltr_L1D2_ThVal;
    HwParameters.Ltr_L1D2_ThScale   =   (UINT16)TwoLmPreMemConfig->Ltr_L1D2_ThScale;
    HwParameters.SysPwrState   =   (UINT8)TwoLmPreMemConfig->SysPwrState;
    HwParameters.MediaDeathNotification   =  (UINT16) TwoLmPreMemConfig->MediaDeathNotification;
    HwParameters.HealthLogNotification   =   (UINT16) TwoLmPreMemConfig->HealthLogNotification;
    HwParameters.TempBelowThrottleNotification   = (UINT16)  TwoLmPreMemConfig->TempBelowThrottleNotification;
    HwParameters.TempAboveThrottleNotification   =  (UINT16) TwoLmPreMemConfig->TempAboveThrottleNotification;
    HwParameters.MissingCommitBitNotification   =  (UINT16) TwoLmPreMemConfig->MissingCommitBitNotification;
  } else {
    DEBUG ((DEBUG_INFO, "2LM: Setting of HwParameters is not enabled \n"));
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "2LM: Issuing SetHwParametersCommand \n"));

  Status = SetHwParametersCommand (&DeviceReturnStatus, (UINT32 *)&HwParameters, InputPayloadSizeDw);
  if (Status != EFI_SUCCESS){
    DEBUG ((DEBUG_INFO, "Mailbox Communication Error\n"));
    return Status;
  }
  if (DeviceReturnStatus) { // if the return Status is other than 00h (Success)
    DEBUG ((DEBUG_INFO, "3DXP Device Error\n"));
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}
