/** @file
  NHLT Create Library implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PcdLib.h>
#include <ConfigBlock.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PchInfoLib.h>
#include <DxeHdaNhlt.h>
#include <Library/DxeHdaNhltLib.h>
#include "DxeCreateNhltTableLib.h"
#include "NhltEndpoints.h"

HDA_NHLT_ENDPOINTS mHdaNhltEndpoints[HdaEndpointMax] =
{
  {HdaDmicX1,     B_HDA_DMIC_1CH_48KHZ_16BIT_FORMAT,                                              0, FALSE},
  {HdaDmicX2,     (B_HDA_DMIC_2CH_48KHZ_16BIT_FORMAT | B_HDA_DMIC_2CH_48KHZ_32BIT_FORMAT),        0, FALSE},
  {HdaDmicX4,     (B_HDA_DMIC_4CH_48KHZ_16BIT_FORMAT | B_HDA_DMIC_4CH_48KHZ_32BIT_FORMAT),        0, FALSE},
  {HdaBtRender,   (B_HDA_BT_NARROWBAND_FORMAT | B_HDA_BT_WIDEBAND_FORMAT | B_HDA_BT_A2DP_FORMAT), 0, FALSE},
  {HdaBtCapture,  (B_HDA_BT_NARROWBAND_FORMAT | B_HDA_BT_WIDEBAND_FORMAT),                        0, FALSE},
  {HdaI2sRender1, B_HDA_I2S_RTK274_RENDER_4CH_48KHZ_24BIT_FORMAT, B_HDA_I2S_RENDER_DEVICE_INFO,      FALSE},
  {HdaI2sRender2, B_HDA_I2S_RTK274_RENDER_4CH_48KHZ_24BIT_FORMAT, B_HDA_I2S_RENDER_DEVICE_INFO,      FALSE},
  {HdaI2sCapture, B_HDA_I2S_RTK274_CAPTURE_4CH_48KHZ_24BIT_FORMAT, B_HDA_I2S_CAPTURE_DEVICE_INFO,    FALSE}
};

/**
  Constructs FORMATS_CONFIGS structure based on given formats list.

  @param[in][out] *Endpoint     Endpoint for which format structures are created
  @param[in]      FormatBitmask Bitmask of formats supported for given endpoint

  @retval                       Size of created FORMATS_CONFIGS structure
**/
UINT32
NhltFormatsConstructor (
  IN OUT ENDPOINT_DESCRIPTOR    *Endpoint,
  IN CONST UINT32               FormatsBitmask
  )
{
  FORMATS_CONFIG         *FormatsConfig;
  FORMAT_CONFIG          *Format;
  UINT8                  FormatIndex;
  UINT32                 FormatsConfigLength;
  UINT8                  Index;
  HDA_NHLT_FORMAT_CONFIG *FormatConfig;

  DEBUG ((DEBUG_INFO, "NhltFormatsConstructor() Start, FormatsBitmask = 0x%08x\n", FormatsBitmask));

  FormatsConfig = NULL;
  FormatIndex = 0;
  FormatsConfigLength = 0;

  if (!FormatsBitmask) {
    DEBUG ((DEBUG_WARN, "No supported format found!\n"));
    return 0;
  }

  FormatsConfig = GetNhltEndpointFormatsConfig (Endpoint);
  FormatsConfig->FormatsCount = 0;

  for (Index = 0; Index < V_HDA_FORMAT_MAX; Index++) {
    FormatConfig = &mHdaNhltFormatConfigs[Index];
    if (FormatsBitmask & FormatConfig->BitMask) {
      DEBUG ((DEBUG_INFO, "Format: 0x%X\n", FormatConfig->BitMask));

      Format = GetNhltEndpointFormat (Endpoint, FormatIndex++);
      if (Format != NULL) {
        CopyMem (&(Format->Format), FormatConfig->WaveFormat, sizeof (WAVEFORMATEXTENSIBLE));
        Format->FormatConfiguration.CapabilitiesSize = FormatConfig->FormatConfigSize;
        CopyMem (Format->FormatConfiguration.Capabilities, FormatConfig->FormatConfig, FormatConfig->FormatConfigSize);

        FormatsConfigLength += sizeof (*Format)
          - sizeof (Format->FormatConfiguration.Capabilities)
          + Format->FormatConfiguration.CapabilitiesSize;
        FormatsConfig->FormatsCount++;
      }
    }
  }
  DEBUG ((DEBUG_INFO, "NhltFormatsConstructor() End, FormatsCount = %d, FormatsConfigLength = %d B\n", FormatsConfig->FormatsCount, FormatsConfigLength));
  return FormatsConfigLength;
}

/**
  Constructs DEVICES_INFO structure based on given device info list.

  @param[in][out] *Endpoint      Endpoint for which device info structures are created
  @param[in]      DevicesBitmask Bitmask of devices supported for given endpoint

  @retval                        Size of created DEVICES_INFO structure
**/
UINT32
NhltDevicesInfoConstructor (
  IN OUT   ENDPOINT_DESCRIPTOR  *Endpoint,
  IN CONST UINT32               DevicesBitmask
  )
{
  DEVICES_INFO  *DevicesInfo;
  DEVICE_INFO   *DeviceInfo;
  UINT8         DeviceIndex;
  UINT32        DevicesInfoLength;

  DEBUG ((DEBUG_INFO, "NhltDevicesInfoConstructor() Start, DevicesBitmask = 0x%08x\n", DevicesBitmask));

  DevicesInfo = NULL;
  DeviceIndex = 0;
  DevicesInfoLength = 0;

  if (!DevicesBitmask) {
    return 0;
  }

  DevicesInfo = GetNhltEndpointDevicesInfo (Endpoint);
  if (DevicesInfo == NULL) {
    return 0;
  }
  DevicesInfo->DeviceInfoCount = 0;

  if (DevicesBitmask & B_HDA_I2S_RENDER_DEVICE_INFO) {
    DEBUG ((DEBUG_INFO, "DeviceInfo: B_HDA_I2S_RENDER_DEVICE_INFO\n"));

    DeviceInfo = GetNhltEndpointDeviceInfo (Endpoint, DeviceIndex++);
    if (DeviceInfo != NULL) {
      CopyMem (DeviceInfo, &I2sRenderDeviceInfo, sizeof (DEVICE_INFO));
      DevicesInfo->DeviceInfoCount++;
    }
  }

  if (DevicesBitmask & B_HDA_I2S_CAPTURE_DEVICE_INFO) {
    DEBUG ((DEBUG_INFO, "DeviceInfo: B_HDA_I2S_CAPTURE_DEVICE_INFO\n"));

    DeviceInfo = GetNhltEndpointDeviceInfo (Endpoint, DeviceIndex++);
    if (DeviceInfo != NULL) {
      CopyMem (DeviceInfo, &I2sCaptureDeviceInfo, sizeof (DEVICE_INFO));
      DevicesInfo->DeviceInfoCount++;
    }
  }

  DevicesInfoLength = DevicesInfo->DeviceInfoCount * sizeof (DEVICE_INFO);

  DEBUG ((DEBUG_INFO, "NhltDevicesInfoConstructor() End, DevicesCount = %d, DevicesInfoLength = %d B\n", DevicesInfo->DeviceInfoCount, DevicesInfoLength));
  return DevicesInfoLength;
}

/**
  Constructs NHLT_ENDPOINT structure based on given endpoint type.

  @param[in][out] *NhltTable              NHLT table for which endpoint is created
  @param[in]      EndpointType            Type of endpoint to be created
  @param[in]      EndpointFormatsBitmask  Bitmask of formats supported by endpoint
  @param[in]      EndpointDevicesBitmask  Bitmask of device info for endpoint
  @param[in]      EndpointIndex           Endpoint index in NHLT table

  @retval                       Size of created NHLT_ENDPOINT structure
**/
UINT32
NhltEndpointConstructor (
  IN OUT NHLT_ACPI_TABLE        *NhltTable,
  IN NHLT_ENDPOINT              EndpointType,
  IN UINT32                     EndpointFormatsBitmask,
  IN UINT32                     EndpointDevicesBitmask,
  IN UINT8                      EndpointIndex
  )
{

  ENDPOINT_DESCRIPTOR *Endpoint;
  SPECIFIC_CONFIG     *EndpointConfig;
  CONST UINT8         *EndpointConfigBuffer;
  UINT32              EndpointConfigBufferSize;
  UINT32              EndpointDescriptorLength;
  UINT8               Index;

  DEBUG ((DEBUG_INFO, "NhltEndpointConstructor() Start, EndpointIndex = %d\n", EndpointIndex));

  EndpointConfigBuffer     = NULL;
  EndpointConfigBufferSize = 0;
  EndpointDescriptorLength = 0;
  Endpoint = GetNhltEndpoint (NhltTable, EndpointIndex);
  if (Endpoint == NULL) {
    return 0;
  }
  EndpointDescriptorLength = sizeof (ENDPOINT_DESCRIPTOR)
    - sizeof (SPECIFIC_CONFIG)
    - sizeof (FORMAT_CONFIG)
    - sizeof (DEVICE_INFO);

  for (Index = 0; Index < HdaEndpointMax; Index++) {
    if (EndpointType == mHdaNhltEndpointConfigs[Index].Endpoint) {
      DEBUG ((DEBUG_INFO, "Endpoint: %r\n", mHdaNhltEndpointConfigs[Index].Endpoint));
      CopyMem (Endpoint, mHdaNhltEndpointConfigs[Index].Description, sizeof (ENDPOINT_DESCRIPTOR));
      EndpointConfigBuffer = mHdaNhltEndpointConfigs[Index].Config;
      EndpointConfigBufferSize = mHdaNhltEndpointConfigs[Index].ConfigSize;
      break;
    }
  }

  if (EndpointConfigBuffer == NULL) {
    return 0;
  }

  switch (EndpointType) {
    case HdaI2sRender1:
      if (EndpointFormatsBitmask & B_HDA_I2S_RTK5660_SPEAKER_RENDER_4CH_48KHZ_24BIT_FORMAT) {
        Endpoint->VirtualBusId = 0;
      }
      break;
    case HdaI2sRender2:
      if (EndpointFormatsBitmask & B_HDA_I2S_RTK5660_HEADPHONES_RENDER_4CH_48KHZ_24BIT_FORMAT) {
        Endpoint->VirtualBusId = 0;
      }
      break;
    case HdaI2sCapture:
      if (EndpointFormatsBitmask & B_HDA_I2S_RTK5660_HEADPHONES_CAPTURE_4CH_48KHZ_24BIT_FORMAT) {
        Endpoint->VirtualBusId = 0;
      }
      break;
  }

  EndpointConfig = GetNhltEndpointDeviceCapabilities (Endpoint);
  EndpointConfig->CapabilitiesSize = EndpointConfigBufferSize;
  ASSERT (EndpointConfigBuffer != NULL);
  CopyMem (EndpointConfig->Capabilities, EndpointConfigBuffer, EndpointConfig->CapabilitiesSize);
  EndpointDescriptorLength += sizeof (*EndpointConfig)
    - sizeof (EndpointConfig->Capabilities)
    + EndpointConfig->CapabilitiesSize;

  EndpointDescriptorLength += NhltFormatsConstructor (Endpoint, EndpointFormatsBitmask);
  EndpointDescriptorLength += NhltDevicesInfoConstructor (Endpoint, EndpointDevicesBitmask);

  Endpoint->EndpointDescriptorLength = EndpointDescriptorLength;

  DEBUG ((DEBUG_INFO, "NhltEndpointConstructor() End, EndpointDescriptorLength = %d B\n", Endpoint->EndpointDescriptorLength));
  return Endpoint->EndpointDescriptorLength;
}

/**
  Constructs SPECIFIC_CONFIG structure for OED configuration.

  @param[in][out] *NhltTable    NHLT table for which OED config is created

  @retval                       Size of created SPECIFIC_CONFIG structure
**/
UINT32
NhltOedConfigConstructor (
  IN OUT NHLT_ACPI_TABLE        *NhltTable
  )
{
  SPECIFIC_CONFIG *OedConfig;
  UINT32          OedConfigLength;

  OedConfigLength = 0;
  OedConfig = GetNhltOedConfig (NhltTable);

  OedConfig->CapabilitiesSize = NhltConfigurationSize;
  CopyMem (OedConfig->Capabilities, (UINT8*) NhltConfiguration, NhltConfigurationSize);

  OedConfigLength = sizeof (*OedConfig)
    - sizeof (OedConfig->Capabilities)
    + OedConfig->CapabilitiesSize;

  return OedConfigLength;
}

/**
  Constructs NHLT_ACPI_TABLE structure based on given Endpoints list.

  @param[in]      *EndpointTable List of endpoints for NHLT
  @param[in][out] **NhltTable    NHLT table to be created
  @param[in][out] *NhltTableSize Size of created NHLT table

  @retval EFI_SUCCESS            NHLT created successfully
  @retval EFI_BAD_BUFFER_SIZE    Not enough resources to allocate NHLT
**/
EFI_STATUS
NhltConstructor (
  IN     HDA_NHLT_CONFIG                   *NhltConfig,
  IN OUT EFI_ACPI_DESCRIPTION_HEADER       **NhltTable,
  IN OUT UINT32                            *NhltTableSize
  )
{
  HDA_NHLT_ENDPOINTS         *EndpointTable;
  EFI_STATUS                 Status;
  UINT8                      Index;
  UINT32                     TableSize;
  UINT32                     EndpointDescriptorsLength;
  UINT32                     OedConfigLength;
  NHLT_ACPI_TABLE            *Table;

  Status                    = EFI_SUCCESS;
  EndpointTable             = &mHdaNhltEndpoints[0];
  TableSize                 = PCH_HDA_NHLT_TABLE_SIZE;
  EndpointDescriptorsLength = 0;
  OedConfigLength           = 0;


  switch (NhltConfig->DspEndpointDmic) {
    case HdaDmic1chArray:
      mHdaNhltEndpoints[HdaDmicX1].Enable   = TRUE;
      break;
    case HdaDmic2chArray:
      mHdaNhltEndpoints[HdaDmicX2].Enable   = TRUE;
      break;
    case HdaDmic4chArray:
      mHdaNhltEndpoints[HdaDmicX4].Enable   = TRUE;
      break;
    case HdaDmicDisabled:
    default:
      mHdaNhltEndpoints[HdaDmicX2].Enable   = FALSE;
      mHdaNhltEndpoints[HdaDmicX4].Enable   = FALSE;
  }

  if (NhltConfig->DspEndpointBluetooth) {
    mHdaNhltEndpoints[HdaBtRender].Enable   = TRUE;
    mHdaNhltEndpoints[HdaBtCapture].Enable  = TRUE;
  }

  if (NhltConfig->DspEndpointI2s) {
    mHdaNhltEndpoints[HdaI2sRender1].Enable = TRUE;
    mHdaNhltEndpoints[HdaI2sRender2].Enable = FALSE;
    mHdaNhltEndpoints[HdaI2sCapture].Enable = TRUE;
    mHdaNhltEndpoints[HdaI2sRender1].EndpointFormatsBitmask = B_HDA_I2S_RTK5660_SPEAKER_RENDER_4CH_48KHZ_24BIT_FORMAT;
    mHdaNhltEndpoints[HdaI2sCapture].EndpointFormatsBitmask = B_HDA_I2S_RTK5660_HEADPHONES_CAPTURE_4CH_48KHZ_24BIT_FORMAT;
  } else {
    mHdaNhltEndpoints[HdaI2sRender1].Enable = FALSE;
    mHdaNhltEndpoints[HdaI2sRender2].Enable = FALSE;
    mHdaNhltEndpoints[HdaI2sCapture].Enable = FALSE;
  }

  Table = AllocateZeroPool (TableSize);

  if (Table == NULL) {
    return EFI_BAD_BUFFER_SIZE;
  }

  Table->EndpointCount = 0;

  for (Index = 0; Index < HdaEndpointMax; Index++) {
    if (EndpointTable[Index].Enable == TRUE) {
      EndpointDescriptorsLength += NhltEndpointConstructor (Table,
                                     EndpointTable[Index].EndpointType,
                                     EndpointTable[Index].EndpointFormatsBitmask,
                                     EndpointTable[Index].EndpointDevicesBitmask,
                                     Table->EndpointCount++);
    }
  }
  DEBUG ((DEBUG_INFO, "NhltConstructor: EndpointCount = %d, All EndpointDescriptorsLength = %d B\n", Table->EndpointCount, EndpointDescriptorsLength));

  OedConfigLength = NhltOedConfigConstructor (Table);
  DEBUG ((DEBUG_INFO, "NhltConstructor: OedConfigLength = %d B\n", OedConfigLength));

  TableSize = EndpointDescriptorsLength + OedConfigLength;

  *NhltTableSize = (UINT32) (TableSize + sizeof (NHLT_ACPI_TABLE) - sizeof (ENDPOINT_DESCRIPTOR) - sizeof (SPECIFIC_CONFIG));
  *NhltTable = (EFI_ACPI_DESCRIPTION_HEADER *) Table;

  return Status;
}
