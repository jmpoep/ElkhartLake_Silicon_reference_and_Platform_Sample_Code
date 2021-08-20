/** @file
  Header file for Dxe Install Nhlt Table Lib

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _DXE_INSTALL_NHLT_TABLE_LIB_H_
#define _DXE_INSTALL_NHLT_TABLE_LIB_H_

#define NHLT_ACPI_TABLE_SIGNATURE  SIGNATURE_32 ('N', 'H', 'L', 'T')

/**
  AudioDSP/iSST endpoints configuration exposed via NHLT ACPI table:
**/
typedef struct {
  UINT8  DspEndpointDmic;         ///< DMIC Select (PCH_HDAUDIO_DMIC_TYPE enum): 0: Disable; 1: 2ch array; <b>2: 4ch array</b>; 3: 1ch array
  UINT8  DspEndpointBluetooth;    ///< Bluetooth enablement: <b>0: Disable</b>; 1: Enable
  UINT8  DspEndpointI2s;          ///< I2S enablement: <b>0: Disable</b>; 1: Enable
  UINT8  DspExternalTable;        ///< Load NHLT from external binaries: <b>0: Disable</b>; 1: Enable
} HDA_NHLT_CONFIG;

/**
  Initialize and publish NHLT ACPI table.

  @retval   EFI_SUCCESS     The NHLT ACPI table is published successfully.
  @retval   EFI_NOT_FOUND   The NHLT ACPI table does not exist.
  @retval   EFI_LOAD_ERROR  The NHLT ACPI table has bad signature.
**/
EFI_STATUS
NhltPublishAcpiTable (
  HDA_NHLT_CONFIG *NhltConfig
  );

#endif
