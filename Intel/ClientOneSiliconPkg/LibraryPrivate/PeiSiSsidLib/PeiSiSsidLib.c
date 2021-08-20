/** @file
  Program silicon SVID and SSID.

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

#include <Library/DebugLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PcieHelperLib.h>
#include <Library/PeiSiSsidLib.h>
#include <Ppi/SiPolicy.h>
#include <PcieRegs.h>

/**
  Get SVID offset for PCI DEV FUNC.

  @param[in] PciCfgBase    Pci base address

  @retval  SVID offset
**/
STATIC
UINT16
GetSvidOffset (
  UINT64 PciCfgBase
  )
{
  UINT16    SvidOffset;
  UINT16    BccScc;
  UINT8     CapList;

  //
  // Get Svid offset
  //
  SvidOffset = 0;
  BccScc = PciSegmentRead16 (PciCfgBase + R_PCI_SCC_OFFSET);
  if (BccScc == ((PCI_CLASS_BRIDGE << 8) | PCI_CLASS_BRIDGE_P2P)) {
    CapList = PcieBaseFindCapId (PciCfgBase, PCI_CAP_ID_SUBSYSTEM_VENDOR);
    if (CapList != 0) {
      SvidOffset = CapList + R_PCIE_SUBSYSTEM_VENDOR_ID_OFFSET;
    }
  }
  if (SvidOffset == 0) {
    SvidOffset = PCI_SVID_OFFSET;
  }
  return SvidOffset;
}

/**
  Override default SVID and SSID

  @param[in]      PciDevNum                 Pci device number
  @param[in]      PciFuncNum                Pci function number
  @param[in]      SsidTablePtr              Ssid policy table
  @param[in]      NumberOfSsidTableEntry    Side of Ssid policy table
  @param[in,out]  Svid                      Svid value
  @param[in,out]  Ssid                      Ssid value
**/
STATIC
VOID
OverrideSvidSsidValue (
  UINT32                 PciDevNum,
  UINT32                 PciFuncNum,
  SVID_SID_INIT_ENTRY    *SsidTablePtr,
  UINT16                 NumberOfSsidTableEntry,
  UINT16                 *Svid,
  UINT16                 *Ssid
  )
{
  UINT32    Index;

  if (SsidTablePtr != NULL) {
    for (Index = 0; Index < NumberOfSsidTableEntry; Index++) {
      if ((SsidTablePtr[Index].Address.Bits.Device == PciDevNum) &&
          (SsidTablePtr[Index].Address.Bits.Function == PciFuncNum))
      {
        *Svid = SsidTablePtr[Index].SvidSidValue.SubSystemVendorId;
        *Ssid = SsidTablePtr[Index].SvidSidValue.SubSystemId;
      }
    }
  }
}

/**
  Program devices Subsystem Vendor Identifier (SVID) and Subsystem Identifier (SID).

  @param[in] SiPolicy             The SI Policy PPI instance
  @param[in] SiSsidOverrideFunc   Silicon SSID override function
**/
VOID
SiProgramSsid (
  IN  SI_POLICY_PPI             *SiPolicy,
  IN  SI_SSID_OVERRIDE_FUNC     SiSsidOverrideFunc
  )
{
  UINT16                        NumberOfSsidTableEntry;
  SVID_SID_INIT_ENTRY           *SsidTablePtr;
  EFI_STATUS                    Status;
  SI_CONFIG                     *SiConfig;
  UINT16                        CommonSvid;
  UINT16                        CommonSsid;
  UINT16                        DataSvid;
  UINT16                        DataSsid;
  UINT32                        PciDevNum;
  UINT32                        PciFuncNum;
  UINT64                        PciCfgBase;
  UINT16                        SvidOffset;
  BOOLEAN                       IsMultiFunc;

  CommonSvid = DEFAULT_SSVID;
  CommonSsid = DEFAULT_SSDID;
  SsidTablePtr = NULL;
  NumberOfSsidTableEntry = 0;

  if (SiPolicy != NULL) {
    Status = GetConfigBlock ((VOID *) SiPolicy, &gSiConfigGuid, (VOID *) &SiConfig);
    if (!EFI_ERROR (Status) && (SiConfig != NULL)) {
      if (SiConfig->SkipSsidProgramming) {
        //
        // Skip all SSID programming
        //
        return;
      }
      if (SiConfig->CustomizedSvid != 0) {
        CommonSvid = SiConfig->CustomizedSvid;
      }
      if (SiConfig->CustomizedSsid != 0) {
        CommonSsid = SiConfig->CustomizedSsid;
      }
      //
      // Use SiPolicy Table and table counts
      //
      SsidTablePtr = (SVID_SID_INIT_ENTRY*) SiConfig->SsidTablePtr;
      NumberOfSsidTableEntry = SiConfig->NumberOfSsidTableEntry;
      ASSERT (NumberOfSsidTableEntry < SI_MAX_DEVICE_COUNT);
    }
  }

  //
  // Silicon code will scan all devices in BUS 0 and program SSID.
  //
  for (PciDevNum = 0; PciDevNum <= PCI_MAX_DEVICE; PciDevNum++) {
    IsMultiFunc = FALSE;
    for (PciFuncNum = 0; PciFuncNum <= PCI_MAX_FUNC; PciFuncNum++) {
      //
      // Skip high function if not multple function controller
      //
      if ((PciFuncNum > 0) && !IsMultiFunc) {
        break;
      }

      //
      // Skip if the device is not present
      //
      PciCfgBase = PCI_SEGMENT_LIB_ADDRESS (0, 0, PciDevNum, PciFuncNum, 0);
      if (PciSegmentRead32 (PciCfgBase + PCI_VENDOR_ID_OFFSET) == 0xFFFFFFFF) {
        continue;
      }

      //
      // Check if it's multiple function controller
      //
      if (PciFuncNum == 0) {
        IsMultiFunc = (PciSegmentRead8 (PciCfgBase + PCI_HEADER_TYPE_OFFSET) & HEADER_TYPE_MULTI_FUNCTION) != 0;
      }

      //
      // Get SVID offset
      //
      SvidOffset = GetSvidOffset (PciCfgBase);

      //
      // Get SVID SSID value
      //
      DataSvid = CommonSvid;
      DataSsid = CommonSsid;

      if ((SiSsidOverrideFunc == NULL) ||
          !SiSsidOverrideFunc (PciDevNum, PciFuncNum, &DataSvid, &DataSsid))
      {
        OverrideSvidSsidValue (PciDevNum, PciFuncNum, SsidTablePtr, NumberOfSsidTableEntry, &DataSvid, &DataSsid);
      }

      //
      // Register programming
      //
      PciSegmentWrite32 (PciCfgBase + SvidOffset, (DataSsid << 16) | DataSvid);
    }
  }
}
