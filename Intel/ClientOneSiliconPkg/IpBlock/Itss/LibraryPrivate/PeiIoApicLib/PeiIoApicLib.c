/** @file
  Initializes PCH IO APIC in PEI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/HobLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PsfLib.h>
#include <Library/PeiP2sbPrivateLib.h>
#include <Register/P2sbRegs.h>
#include <Register/ItssRegs.h>

/**
  Initialize IOAPIC according to IoApicConfig policy of the PCH
  Policy PPI

  @param[in] SiPolicyPpi          The SI Policy PPI instance

**/
VOID
IoApicInit (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS            Status;
  UINT64                P2sbBase;
  PCH_IOAPIC_CONFIG     *IoApicConfig;
  UINT32                IoApicAddress;
  UINT32                IoApicId;
  UINT32                Data32;
  UINT8                 IoApicSelect;
  PCH_GENERAL_CONFIG    *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Set PSF Multicast EOI forwarding for ITSS (with IOAPIC controller)
  ///
  PsfConfigurEoiForItss ();

  //
  // Configure ITSS power management settings
  //
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gIoApicConfigGuid, (VOID *) &IoApicConfig);
  ASSERT_EFI_ERROR (Status);

  if (PchGeneralConfig->PchMasterClockGating != 0) {
    ///
    /// Set PCR[ITSS] + 3300h[4:0] = 11011b
    /// Set PCR[ITSS] + 3300h[2] = 1 in POST time only if 8254 timer is not used.
    ///
    Data32 = (B_ITSS_PCR_ITSSPRC_PGCBDCGE | B_ITSS_PCR_ITSSPRC_HPETDCGE | B_ITSS_PCR_ITSSPRC_IOSFICGE | B_ITSS_PCR_ITSSPRC_ITSSCGE);
    if (IoApicConfig->Enable8254ClockGating) {
      Data32 |= B_ITSS_PCR_ITSSPRC_8254CGE;
    }
    PchPcrAndThenOr32 (
      PID_ITSS, R_ITSS_PCR_ITSSPRC,
      ~0u,
      Data32
      );
  } else {
    PchPcrAndThenOr32 (
      PID_ITSS, R_ITSS_PCR_ITSSPRC,
      (UINT32)~(B_ITSS_PCR_ITSSPRC_PGCBDCGE | B_ITSS_PCR_ITSSPRC_HPETDCGE | B_ITSS_PCR_ITSSPRC_8254CGE | B_ITSS_PCR_ITSSPRC_IOSFICGE | B_ITSS_PCR_ITSSPRC_ITSSCGE),
      0
      );
  }

  P2sbBase = P2sbPciBase ();

  ///
  /// Program APIC Range Select bits that define address bits 19:12 for the IOxAPIC range.
  /// This value must not be changed unless the IOxAPIC Enable bit is cleared.
  ///
  IoApicAddress = PcdGet32 (PcdSiIoApicBaseAddress);
  ASSERT ((IoApicAddress & 0xFFF00FFF) == 0xFEC00000);
  IoApicSelect = (IoApicAddress >> N_IO_APIC_ASEL) & 0xFF;
  if (IoApicSelect != PciSegmentRead8 (P2sbBase + R_P2SB_CFG_IOAC)) {
    PciSegmentAnd16 (P2sbBase + R_P2SB_CFG_IOAC, (UINT16) ~(B_P2SB_CFG_IOAC_AE));
    PciSegmentAndThenOr16 (
      P2sbBase + R_P2SB_CFG_IOAC,
      (UINT16) ~(B_P2SB_CFG_IOAC_ASEL),
      (UINT16) IoApicSelect
      );
  }
  ///
  /// PCH BIOS Spec Section 6.6.2.1
  /// 1. Enable the IOAPIC by setting the APIC Enable bit, P2SB PCI offset 64h [8], if the
  ///    system needs to use the IOxAPIC. The APIC Enable bits needs read back after the bit is written.
  ///
  PciSegmentOr16 (P2sbBase + R_P2SB_CFG_IOAC, B_P2SB_CFG_IOAC_AE);
  ///
  /// Reads back for posted write to take effect
  ///
  PciSegmentRead16 (P2sbBase + R_P2SB_CFG_IOAC);

  ///
  /// Get current IO APIC ID
  ///
  MmioWrite8 ((UINTN) (IoApicAddress + R_IO_APIC_INDEX_OFFSET), 0);
  IoApicId = MmioRead32 ((UINTN) (IoApicAddress + R_IO_APIC_DATA_OFFSET)) >> 24;
  ///
  /// IO APIC ID is at APIC Identification Register [27:24]
  ///
  if ((IoApicConfig->IoApicId != IoApicId) && (IoApicConfig->IoApicId < 0x10)) {
    ///
    /// Program APIC ID
    ///
    MmioWrite8 ((UINTN) (IoApicAddress + R_IO_APIC_INDEX_OFFSET), 0);
    MmioWrite32 ((UINTN) (IoApicAddress + R_IO_APIC_DATA_OFFSET), (UINT32) (IoApicConfig->IoApicId << 24));
  }

  if (IoApicConfig->IoApicEntry24_119 == FALSE) {
    ///
    /// Program IOAPIC maximal entry to 24 in PCR[ITSS] + 31FCh[9]
    /// and in IOAPIC Version Register
    PchPcrAndThenOr16 (PID_ITSS, R_ITSS_PCR_GIC, 0xFFFF, (UINT16) B_ITSS_PCR_GIC_MAX_IRQ_24);
    MmioWrite8 ((UINTN) (IoApicAddress + R_IO_APIC_INDEX_OFFSET), 1);
    MmioWrite32 ((IoApicAddress + R_IO_APIC_DATA_OFFSET), 0x170020);
  } else {
    ///
    /// Program IOAPIC maximal entry to 119 in PCR[ITSS] + 31FCh[9]
    /// and in IOAPIC Version Register
    PchPcrAndThenOr16 (PID_ITSS, R_ITSS_PCR_GIC, (UINT16) (~B_ITSS_PCR_GIC_MAX_IRQ_24), 0x0);
    MmioWrite8 ((UINTN) (IoApicAddress + R_IO_APIC_INDEX_OFFSET), 1);
    MmioWrite32 ((IoApicAddress + R_IO_APIC_DATA_OFFSET), 0x770020);
  }

  //
  // Build the resource descriptor hob for IOAPIC address resource.
  //
  BuildResourceDescriptorHob (
    EFI_RESOURCE_MEMORY_MAPPED_IO,
    (EFI_RESOURCE_ATTRIBUTE_PRESENT    |
     EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE),
    IoApicAddress,
    0x1000
    );
  BuildMemoryAllocationHob (
    IoApicAddress,
    0x1000,
    EfiMemoryMappedIO
    );
}

