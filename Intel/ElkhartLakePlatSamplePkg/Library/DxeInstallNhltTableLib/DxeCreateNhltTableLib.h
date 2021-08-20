/** @file
  This library provides HD Audio NHLT functions.

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

#ifndef _DXE_CREATE_NHLT_TABLE_LIB_
#define _DXE_CREATE_NHLT_TABLE_LIB_

#include <DxeHdaNhlt.h>
#include "NhltEndpoints.h"
#include <Library/DxeInstallNhltTableLib.h>
#include <Library/DxeHdaNhltLib.h>

/**
  Prints NHLT (Non HDA-Link Table) to be exposed via ACPI (aka. OED (Offload Engine Driver) Configuration Table).

  @param[in] *NhltAcpiTable    The NHLT table to print
**/
VOID
NhltAcpiTableDump(
  IN NHLT_ACPI_TABLE           *NhltTable
  );

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
  );

#endif
