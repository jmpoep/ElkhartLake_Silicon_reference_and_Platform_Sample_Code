/** @file
  Initializes PCH Primary To Sideband Bridge (P2SB) Device in PEI

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
#include <Library/HobLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PciSegmentLib.h>
#include <Ppi/SiPolicy.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/P2sbRegs.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include "PeiP2sbPrivateLibInternal.h"

#define R_HPET_MEM_GEN_CFG            0x10
#define B_HPET_MEM_GEN_CFG_ENABLE_CNF BIT0

/**
  Get P2SB pci segment address.

  @retval P2SB pci segment base address
**/
UINT64
P2sbPciBase (
  VOID
  )
{
  UINT64 P2sbBase;
  P2sbBase = PCI_SEGMENT_LIB_ADDRESS (
               DEFAULT_PCI_SEGMENT_NUMBER_PCH,
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_P2SB,
               PCI_FUNCTION_NUMBER_PCH_P2SB,
               0
               );
  ASSERT (PciSegmentRead16 (P2sbBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF);
  return P2sbBase;
}

/**
  Hide P2SB device.

  @param[in]  P2sbBase                  Pci segment base address of P2SB controller.
**/
STATIC
VOID
P2sbHideDevice (
  IN  UINT64                            P2sbBase,
  SI_CONFIG                             *SiConfig
  )
{
  PciSegmentWrite8 (P2sbBase + R_P2SB_CFG_E0 + 1, BIT0);
}

/**
  Check SBREG readiness.

  @retval TRUE                SBREG is ready
  @retval FALSE               SBREG is not ready
**/
BOOLEAN
P2sbIsSbregReady (
  VOID
  )
{
  if ((PciSegmentRead32 (P2sbPciBase () + R_P2SB_CFG_SBREG_BAR) & B_P2SB_CFG_SBREG_RBA) == 0) {
    return FALSE;
  }
  return TRUE;
}

/**
  Internal function performing HPET initin early PEI phase
**/
VOID
P2sbHpetInit (
  VOID
  )
{
  UINT64                                P2sbBase;
  UINT32                                HpetBase;

  P2sbBase = P2sbPciBase ();

  //
  // Initial and enable HPET High Precision Timer memory address for basic usage
  // If HPET base is not set, the default would be 0xFED00000.
  //
  HpetBase = PcdGet32 (PcdSiHpetBaseAddress);
  ASSERT ((HpetBase & 0xFFFFCFFF) == 0xFED00000);
  PciSegmentAndThenOr8 (
    P2sbBase + R_P2SB_CFG_HPTC,
    (UINT8) ~B_P2SB_CFG_HPTC_AS,
    (UINT8) (((HpetBase >> N_HPET_ADDR_ASEL) & B_P2SB_CFG_HPTC_AS) | B_P2SB_CFG_HPTC_AE)
    );
  //
  // Read back for posted write to take effect
  //
  PciSegmentRead8 (P2sbBase + R_P2SB_CFG_HPTC);
  //
  // Set HPET Timer enable to start counter spinning
  //
  MmioOr32 (HpetBase + R_HPET_MEM_GEN_CFG, B_HPET_MEM_GEN_CFG_ENABLE_CNF);
  //
  // Build the resource descriptor hob for HPET address resource.
  // HPET only claims 0x400 in size, but the minimal size to reserve memory
  // is one page 0x1000.
  //
  BuildResourceDescriptorHob (
    EFI_RESOURCE_MEMORY_MAPPED_IO,
    (EFI_RESOURCE_ATTRIBUTE_PRESENT    |
     EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE),
    HpetBase,
    0x1000
    );
  BuildMemoryAllocationHob (
    HpetBase,
    0x1000,
    EfiMemoryMappedIO
    );
}

/**
 Early init P2SB configuration
**/
VOID
P2sbEarlyConfig (
  VOID
  )
{
  UINT64                  P2sbBase;

  P2sbBase  = P2sbPciBase ();

  ///
  /// BIOS shall program the PCI Capability List to 0 for P2SB controller.
  ///
  PciSegmentWrite8 (P2sbBase + PCI_CAPBILITY_POINTER_OFFSET, 0);
  ///
  /// For GPIO and ITSS that support sideband posted write, they can support
  /// back to back write after their correspoing bits under P2SB PCI Config
  /// 200h-21Fh are set.
  /// For CNL PCH-LP and CNL PCH-H, program the following at early PCH BIOS init
  /// 1. Set P2SB PCI offset 200h to 0
  /// 2. Set P2SB PCI offset 204h to 0
  /// 3. Set P2SB PCI offset 208h to 0
  /// 4. Set P2SB PCI offset 20Ch to 00007C00h
  /// 5. Set P2SB PCI offset 210h to 0
  /// 6. Set P2SB PCI offset 214h to 0
  /// 7. Set P2SB PCI offset 218h to 00000010h
  /// 8. Set P2SB PCI offset 21Ch to 0
  ///
  PciSegmentWrite32 (P2sbBase + R_P2SB_CFG_200, 0);
  PciSegmentWrite32 (P2sbBase + R_P2SB_CFG_204, 0);
  PciSegmentWrite32 (P2sbBase + R_P2SB_CFG_208, 0);
  PciSegmentWrite32 (P2sbBase + R_P2SB_CFG_20C, 0x00007C00);
  PciSegmentWrite32 (P2sbBase + R_P2SB_CFG_210, 0);
  PciSegmentWrite32 (P2sbBase + R_P2SB_CFG_214, 0);
  PciSegmentWrite32 (P2sbBase + R_P2SB_CFG_218, 0x00000010);
  PciSegmentWrite32 (P2sbBase + R_P2SB_CFG_21C, 0);
  ///
  /// Set P2SB PCI offset 0xF4[0] = 1
  ///
  PciSegmentOr8 (P2sbBase + R_P2SB_CFG_F4, BIT0);
}

/**
  The function performs P2SB initialization.

  @param[in] SiPolicy         The SI Policy PPI instance
**/
VOID
P2sbConfigure (
  IN  SI_POLICY_PPI           *SiPolicy
  )
{
  UINT64                      P2sbBase;
  PCH_GENERAL_CONFIG          *PchGeneralConfig;
  EFI_STATUS                  Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  P2sbBase = P2sbPciBase ();

  //
  // HPET and APIC BDF programming
  // Assign 0:30:6 for HPET and 0:30:7 for APIC statically.
  //
  PciSegmentWrite16 (
    P2sbBase + R_P2SB_CFG_HBDF,
    (V_P2SB_CFG_HBDF_BUS << 8) | (V_P2SB_CFG_HBDF_DEV << 3) | V_P2SB_CFG_HBDF_FUNC
    );
  PciSegmentWrite16 (
    P2sbBase + R_P2SB_CFG_IBDF,
    (V_P2SB_CFG_IBDF_BUS << 8) | (V_P2SB_CFG_IBDF_DEV << 3) | V_P2SB_CFG_IBDF_FUNC
    );

  //
  // Set P2SB PCI offset 0xE0[4] = 1.
  //
  PciSegmentOr8 (P2sbBase + R_P2SB_CFG_E0, BIT4);

  //
  // P2SB power management settings.
  //

  P2sbPowerGatingConfigure (
      (BOOLEAN) PchGeneralConfig->PchMasterClockGating,
      (BOOLEAN) PchGeneralConfig->PchMasterPowerGating,
      PchGeneralConfig->LegacyIoLowLatency
      );

  //
  // If Legacy IO Low Latency is enabled
  //  set P2SB PCI offset 0xE8[1, 0] = 1's
  //  set P2SB PCI offset 0xEA[1, 0] = 1's
  //
  if (PchGeneralConfig->PchMasterClockGating != 0) {
    if (PchGeneralConfig->LegacyIoLowLatency) {
      PciSegmentOr16 (P2sbBase + R_P2SB_CFG_E8,  BIT0 | BIT1);
      PciSegmentOr16 (P2sbBase + R_P2SB_CFG_EA,  BIT0 | BIT1);
    }
  } else {
    PciSegmentOr16 (P2sbBase + R_P2SB_CFG_E8, BIT0 | BIT1);
    PciSegmentOr16 (P2sbBase + R_P2SB_CFG_EA, BIT0 | BIT1);
  }

  ///
  /// Set LFIORIEC to 0 for IEC not supported.
  /// P2SB PCI offset 0x74 = 0
  ///
  PciSegmentWrite8 (P2sbBase + R_P2SB_CFG_LFIORIEC, 0);
}

/**
  Bios will remove the host accessing right to PSF register range
  prior to any 3rd party code execution.

  @param[in] P2sbBase         P2SB PCI base address
**/
STATIC
VOID
P2sbRemovePsfAccess (
  IN UINT64                   P2sbBase
  )
{
  UINT32                      RegisterOff;
  UINT32                      BitNo;
  UINT16                      *EndpointMaskTable;
  UINT32                      EndpointMaskTableLength;
  UINTN                       Index;

  P2sbGetEndpointMaskedPids (&EndpointMaskTable, &EndpointMaskTableLength);

  for (Index = 0; Index < EndpointMaskTableLength; ++Index) {
    ///
    /// Set the bit corresponding to IOSF-SB endpoint id in the P2SB.EPMASK[0-7] register to remove the access
    ///
    RegisterOff = (EndpointMaskTable[Index] / 32) * sizeof (UINT32); // Calculate which 32 bit mask register
    BitNo = EndpointMaskTable[Index] % 32;                          // Calculate the bit number to be set in the mask register
    PciSegmentOr32 ((UINTN) (P2sbBase + R_P2SB_CFG_EPMASK0 + RegisterOff), (UINT32) 1 << BitNo);
    DEBUG ((DEBUG_INFO, "Removing PSF access: EPMASK offset %x, BIT%d, endpoint: %x\n", RegisterOff, BitNo, EndpointMaskTable[Index]));
  }
  ///
  ///    Set P2SB PCI offset 23Ch [31, 30] to [1, 1] to remove access of Broadcast and Multicast.
  ///
  PciSegmentOr32 (P2sbBase + R_P2SB_CFG_EPMASK7, BIT31 | BIT30);
  ///
  /// 2) Set the "Endpoint Mask Lock", P2SB PCI offset E2h bit[1] to 1.
  ///
  PciSegmentOr8 (P2sbBase + R_P2SB_CFG_E0 + 2, BIT1);
}

/**
  The function performs P2SB lock programming.

  @param[in] SiPolicy         The SI Policy PPI instance
**/
VOID
P2sbLock (
  IN  SI_POLICY_PPI           *SiPolicy
  )
{
  EFI_STATUS             Status;
  UINT64                 P2sbBase;
  PCH_P2SB_CONFIG        *P2sbConfig;
  SI_CONFIG              *SiConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSiConfigGuid, (VOID *) &SiConfig);
  ASSERT_EFI_ERROR (Status);

  P2sbBase = P2sbPciBase ();

  //
  // Do P2SB SBI lock, Sideband access removal, Hide P2SB, and set PostBootSai in EndOfPei.
  //
  Status = GetConfigBlock ((VOID *) SiPolicy, &gP2sbConfigGuid, (VOID *) &P2sbConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // Program EPMASK.
  // @note, doing EPMASK in end of pei will block the HECI device disable in EndOfPost.
  //
  if (P2sbConfig->SbAccessUnlock == 0) {
    P2sbRemovePsfAccess (P2sbBase);
  }

  //@todo. W/A for simics and hfpga since it doesn't support POSTBOOT SAI to block P2SB access.
  //
  // Hide P2SB controller in the end of PEI.
  //
  P2sbHideDevice (P2sbBase, SiConfig);
}
