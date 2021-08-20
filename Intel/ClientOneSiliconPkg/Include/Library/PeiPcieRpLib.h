/** @file
  Header file for PEI PCIe functionality

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _PEI_PCIE_LIB_H_
#define _PEI_PCIE_LIB_H_

extern EFI_GUID gPciImrHobGuid;

typedef struct {
  EFI_HOB_GUID_TYPE Header;
  UINT64            PciImrBase;
} PCI_IMR_HOB;

/**
  Read the PCIe PreMem policy to check port number for PCIe IMR

  @retval   port number
**/
UINT8
GetPcieImrPortNumber (
  VOID
  );

/**
  Read the PCIe Premem policy to see if PCIe IMR is enabled.

  @retval TRUE             PCIe IMR is enabled
  @retval FALSE            PCIe IMR is disabled
**/
BOOLEAN
IsPcieImrEnabled (
  VOID
  );

/**
  Read the PCIE policy to check port Location for PCIe IMR

  @retval   RootPort Location
**/
UINT8
GetPcieImrPortLocation (
  VOID
  );

/**
  Read the PCIe policy to get PCIe IMR Size.

  @retval PcieImrSize      Size of PCIe Imr in MB
**/
UINT16
GetPcieImrSize (
  VOID
  );

/**
  This function puts PCIe IMR related information into HOB

  @param[in] BaseLow    lower 32 bits of PCIe IMR address
  @param[in] BaseHigh   higher 32 bits of PCIe IMR address
**/
VOID
BuildPciImrHob (
  UINT32 BaseLow,
  UINT32 BaseHigh
  );

#endif
