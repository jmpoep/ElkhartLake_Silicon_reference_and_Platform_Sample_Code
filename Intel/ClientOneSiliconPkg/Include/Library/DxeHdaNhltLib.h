/** @file
  Prototype of the DxePchHdaNhltLib library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

#ifndef _DXE_HDA_NHLT_LIB_H_
#define _DXE_HDA_NHLT_LIB_H_

#include <DxeHdaNhlt.h>

/**
  Returns pointer to Endpoint ENDPOINT_DESCRIPTOR structure.

  @param[in] *NhltTable    Endpoint for which Format address is retrieved
  @param[in] FormatIndex   Index of Format to be retrieved

  @retval                  Pointer to ENDPOINT_DESCRIPTOR structure with given index
**/
ENDPOINT_DESCRIPTOR *
GetNhltEndpoint (
  IN CONST NHLT_ACPI_TABLE      *NhltTable,
  IN CONST UINT8                EndpointIndex
  );

/**
  Returns pointer to Endpoint Specific Configuration SPECIFIC_CONFIG structure.

  @param[in] *Endpoint     Endpoint for which config address is retrieved

  @retval                  Pointer to SPECIFIC_CONFIG structure with endpoint's capabilities
**/
SPECIFIC_CONFIG *
GetNhltEndpointDeviceCapabilities (
  IN CONST ENDPOINT_DESCRIPTOR  *Endpoint
  );

/**
  Returns pointer to all Formats Configuration FORMATS_CONFIG structure.

  @param[in] *Endpoint     Endpoint for which Formats address is retrieved

  @retval                  Pointer to FORMATS_CONFIG structure
**/
FORMATS_CONFIG *
GetNhltEndpointFormatsConfig (
  IN CONST ENDPOINT_DESCRIPTOR  *Endpoint
  );

/**
  Returns pointer to Format Configuration FORMAT_CONFIG structure.

  @param[in] *Endpoint     Endpoint for which Format address is retrieved
  @param[in] FormatIndex   Index of Format to be retrieved

  @retval                  Pointer to FORMAT_CONFIG structure with given index
**/
FORMAT_CONFIG *
GetNhltEndpointFormat (
  IN CONST ENDPOINT_DESCRIPTOR  *Endpoint,
  IN CONST UINT8                FormatIndex
  );

/**
  Returns pointer to all Device Information DEVICES_INFO structure.

  @param[in] *Endpoint     Endpoint for which DevicesInfo address is retrieved

  @retval                  Pointer to DEVICES_INFO structure
**/
DEVICES_INFO *
GetNhltEndpointDevicesInfo (
  IN CONST ENDPOINT_DESCRIPTOR  *Endpoint
  );

/**
  Returns pointer to Device Information DEVICES_INFO structure.

  @param[in] *Endpoint       Endpoint for which Device Info address is retrieved
  @param[in] DeviceInfoIndex Index of Device Info to be retrieved

  @retval                    Pointer to DEVICE_INFO structure with given index
**/
DEVICE_INFO *
GetNhltEndpointDeviceInfo (
  IN CONST ENDPOINT_DESCRIPTOR  *Endpoint,
  IN CONST UINT8                DeviceInfoIndex
  );


/**
  Returns pointer to OED Configuration SPECIFIC_CONFIG structure.

  @param[in] *NhltTable    NHLT table for which OED address is retrieved

  @retval                  Pointer to SPECIFIC_CONFIG structure with NHLT capabilities
**/
SPECIFIC_CONFIG *
GetNhltOedConfig (
  IN CONST NHLT_ACPI_TABLE      *NhltTable
  );

/**
  Prints Format configuration.

  @param[in] *Format       Format to be printed

  @retval None
**/
VOID
NhltFormatDump (
  IN CONST FORMAT_CONFIG        *Format
  );


/**
  Prints Endpoint configuration.

  @param[in] *Endpoint     Endpoint to be printed

  @retval None
**/
VOID
NhltEndpointDump (
  IN CONST ENDPOINT_DESCRIPTOR  *Endpoint
  );

/**
  Prints OED (Offload Engine Driver) configuration.

  @param[in] *OedConfig   OED to be printed

  @retval None
**/
VOID
NhltOedConfigDump (
  IN CONST SPECIFIC_CONFIG      *OedConfig
  );

/**
  Prints NHLT (Non HDA-Link Table) to be exposed via ACPI (aka. OED (Offload Engine Driver) Configuration Table).

  @param[in] *NhltTable    The NHLT table to print

  @retval None
**/
VOID
NhltAcpiTableDump (
  IN NHLT_ACPI_TABLE            *NhltTable
  );

#endif // _DXE_HDA_NHLT_LIB_H_
