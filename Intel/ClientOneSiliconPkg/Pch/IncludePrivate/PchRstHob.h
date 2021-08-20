/** @file

  Definitions required to create RstHob

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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

#ifndef _PCH_RST_HOB_
#define _PCH_RST_HOB_

extern EFI_GUID  gPchRstHobGuid;

//
// This struct is used to record the fields that should be restored during device wake up
//
typedef struct {
  UINT8     PmCapPtr;
  UINT8     PcieCapPtr;
  UINT16    L1ssCapPtr;
  UINT8     EndpointL1ssControl2;
  UINT32    EndpointL1ssControl1;
  UINT16    LtrCapPtr;
  UINT32    EndpointLtrData;
  UINT16    EndpointLctlData16;
  UINT16    EndpointDctlData16;
  UINT16    EndpointDctl2Data16;
  UINT16    RootPortDctl2Data16;
} SAVED_DEVICE_CONFIG_SPACE;

//
// This structure is used to record the result of PCIe storageremapping for each cycle router
//
typedef struct {
  UINT8                                 RootPortNum;                      // Indicates the root port number with RST PCIe Storage Remapping remapping supported and PCIe storage device plugged on, numbering is 0-based
  UINT8                                 DeviceInterface;                  // Indicates the interface of the PCIe storage device (AHCI or NVMe)
  UINT32                                EndPointUniqueMsixTableBar;       // Records the PCIe storage device's MSI-X Table BAR if it supports unique MSI-X Table BAR
  UINT32                                EndPointUniqueMsixTableBarValue;  // Records the PCIe storage device's MSI-X Table BAR value if it supports unique MSI-X Table BAR
  UINT32                                EndPointUniqueMsixPbaBar;         // Records the PCIe storage device's MSI-X PBA BAR if it supports unique MSI-X PBA BAR
  UINT32                                EndPointUniqueMsixPbaBarValue;    // Records the PCIe storage device's MSI-X PBA BAR value if it supports unique MSI-X PBA BAR
} RST_CR_CONFIGURATION;

//
//  Passes to DXE results of PCIe storage remapping
//
typedef struct {
  //
  // Stores configuration information about cycle router
  //
  RST_CR_CONFIGURATION  RstCrConfiguration[PCH_MAX_RST_PCIE_STORAGE_CR];

  //
  // Saved fields from hidden device config space to be used later by RST driver
  //
  SAVED_DEVICE_CONFIG_SPACE  SavedRemapedDeviceConfigSpace[PCH_MAX_RST_PCIE_STORAGE_CR];
} PCH_RST_HOB;

#endif
