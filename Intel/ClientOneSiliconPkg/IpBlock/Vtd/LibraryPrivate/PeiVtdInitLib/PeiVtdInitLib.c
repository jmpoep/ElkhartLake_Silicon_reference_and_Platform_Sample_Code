/** @file
  This code provides a initialization of intel VT-d (Virtualization Technology for Directed I/O).

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PostCodeLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiVtdInitLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/PsfLib.h>
#include <Library/BootGuardLib.h>
#include <Library/SaPlatformLib.h>
#if FixedPcdGetBool(PcdITbtEnable) == 1
#include <Library/ItbtPcieRpLib.h>
#endif
#include <Library/VtdInfoLib.h>
#include <Register/IpuRegs.h>
#include <Register/IgdRegs.h>
#include <Register/VtdRegs.h>
#include <CpuRegs.h>
#include <VtdDataHob.h>

extern EFI_GUID gVtdDataHobGuid;

/**
  Configure VT-d Base and capabilities.

  @param[in]   VTD_CONFIG                 VTD config block from SA Policy PPI

  @retval EFI_SUCCESS     - Vtd initialization complete
  @exception EFI_UNSUPPORTED - Vtd is not enabled by policy
**/
EFI_STATUS
VtdInit (
  IN       VTD_CONFIG                        *Vtd
  )
{
  UINT64         McD0BaseAddress;
  UINTN          MchBar;

  McD0BaseAddress  = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  MchBar           = PciSegmentRead32 (McD0BaseAddress + R_SA_MCHBAR) &~BIT0;


  //
  // Install VTD Data Hob
  //
  DEBUG ((DEBUG_INFO, "Install VTD DATA HOB\n"));
  InstallVtdDataHob ();

  if (IsBootGuardSupported()) {
    ClearDmaProtectionSetByBootGuard (MchBar);
  }

  if ((Vtd->VtdDisable) || (PciSegmentRead32 (McD0BaseAddress + R_SA_MC_CAPID0_A_OFFSET) & BIT23)) {
    DEBUG ((DEBUG_WARN, "VTd disabled or no capability!\n"));
    return EFI_UNSUPPORTED;
  }
  ///
  /// Check SA supports VTD and VTD is enabled in setup menu
  ///
  DEBUG ((DEBUG_INFO, "VTd enabled\n"));

  ///
  /// Enable VTd in PCH
  ///
  PchPsfEnableVtd ();

  ///
  /// Program Remap Engine Base Address
  ///

  ConfigureIgdVtdBar (Vtd, MchBar);
  ConfigureIopVtdBar (Vtd, MchBar);

  return EFI_SUCCESS;
}


/**
  Clear DMA Protection set by Boot Guard.

  @param[in]   MchBar        MchBar Value
**/
VOID
ClearDmaProtectionSetByBootGuard (
  IN  UINTN          MchBar
  )
{
  UINT32         MsrValue;
  UINT32         VtdBaseAddress3;
  UINT32         AcmPolicySts;

  MsrValue = (UINT32) AsmReadMsr64 (MSR_BOOT_GUARD_SACM_INFO);
  if ((MsrValue & B_BOOT_GUARD_SACM_INFO_NEM_ENABLED) != 0) {
    AcmPolicySts = MmioRead32 (MMIO_ACM_POLICY_STATUS );
    if  (AcmPolicySts & (BIT29)) {
      //dma protection is enabled
      DEBUG ((DEBUG_INFO, "[Boot Guard]Clear DMA protection set by BTG ACM\n"));
      VtdBaseAddress3 = MmioRead32 (MchBar + R_MCHBAR_VTD3_OFFSET) &~BIT0;
      if (VtdBaseAddress3 > 0) {
        MmioWrite32 ((VtdBaseAddress3 + R_VTD_PMEN_OFFSET) , 0);
        //Read-back
        MmioRead32 (VtdBaseAddress3 + R_VTD_PMEN_OFFSET);
        MmioWrite32 ((VtdBaseAddress3 + R_VTD_PLMBASE_OFFSET), 0);
        MmioWrite32 ((VtdBaseAddress3 + R_VTD_PLMLIMIT_OFFSET), 0);
        MmioWrite32 ((MchBar + R_MCHBAR_VTD3_OFFSET), 0);
      } //VtdBaseAddress3 > 0
    } // AcmPolicySts & (BIT29)
  }  //NEM enabled by SACM
}

/**
  Configure IGD VTD BAR.
  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI
  @param[in]   MchBar           MchBar Value

  @retval EFI_SUCCESS           Function executed successfully
**/
EFI_STATUS
ConfigureIgdVtdBar (
  IN  VTD_CONFIG  *Vtd,
  IN  UINTN       MchBar
  )
{
  UINT32         Data32Or;

  ///
  /// Configure VTD1 BAR
  /// Skip GFXVTBAR if IGD is disabled
  ///
  if ((PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, PCI_VENDOR_ID_OFFSET)) != 0xFFFF) && (!IsDisplayOnlySku())  && (Vtd->VtdIgdEnable == 1)) {
    Data32Or = Vtd->BaseAddress[0];
    Data32Or |= 0x1;
    MmioWrite32 (MchBar + R_MCHBAR_VTD1_OFFSET, Data32Or);
    PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, R_SA_VTD_IGD_UBAR), 0);
    PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, R_SA_VTD_IGD_LBAR), Data32Or);
  }

  return EFI_SUCCESS;
}

/**
  Configure IPU VTD BAR.

  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI
  @param[in]   MchBar           MchBar Value

  @retval EFI_SUCCESS           Function executed successfully
  @retval EFI_NOT_FOUND         The required PPI could not be located.
**/
EFI_STATUS
ConfigureIpuVtdBar (
  IN  VTD_CONFIG           *Vtd,
  IN  UINTN                MchBar
  )
{

  return EFI_SUCCESS;
}

/**
  Configure IOP VTD BAR.

  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI
  @param[in]   MchBar           MchBar Value

  @retval EFI_SUCCESS           Function executed successfully
**/
EFI_STATUS
ConfigureIopVtdBar (
  IN  VTD_CONFIG  *Vtd,
  IN  UINTN       MchBar
  )
{
  UINT32         Data32Or;

  ///
  /// Configure VTD3 BAR
  ///
  if (Vtd->VtdIopEnable == 1) {
    Data32Or = Vtd->BaseAddress[2];
    Data32Or |= 0x1;
    MmioWrite32 (MchBar + R_MCHBAR_VTD3_OFFSET, Data32Or);
  }
  return EFI_SUCCESS;
}
#if FixedPcdGetBool(PcdITbtEnable) == 1
/**
  Clear ITBT VTD BAR.

  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI
  @param[in]   MchBar           MchBar Value
**/
VOID
ClearITbtVtdBar (
  IN  VTD_CONFIG  *Vtd,
  IN  UINTN          MchBar
  )
{
  UINTN          ItbtSegment;
  UINTN          ItbtBus;
  UINTN          ItbtDevice;
  UINTN          ItbtFunction;
  EFI_STATUS     Status;
  UINT8          Index;

  for(Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    Status = GetItbtPcieRpInfo (Index, &ItbtSegment, &ItbtBus, &ItbtDevice, &ItbtFunction);
    if (Status == EFI_SUCCESS) {
      MmioWrite32 (MchBar + (R_MCHBAR_ITBT_PCIE_0_VTD_HIGH_OFFSET + (8 * Index)), 0);
      MmioWrite32 (MchBar + (R_MCHBAR_ITBT_PCIE_0_VTD_LOW_OFFSET + (8 * Index)), 0);
      if (PciSegmentRead16(PCI_SEGMENT_LIB_ADDRESS (ItbtSegment, SA_ITBT_PCIE_BUS_NUM , SA_ITBT_PCIE_DEV_NUM , ItbtFunction, PCI_VENDOR_ID_OFFSET)) != 0xFFFF) {
        PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (ItbtSegment, SA_ITBT_PCIE_BUS_NUM, SA_ITBT_PCIE_DEV_NUM, ItbtFunction, R_SA_VTD_ITBT_PCIE_UBAR), 0);
        PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (ItbtSegment, SA_ITBT_PCIE_BUS_NUM, SA_ITBT_PCIE_DEV_NUM, ItbtFunction, R_SA_VTD_ITBT_PCIE_LBAR), 0);
      }
    }
  }
}
/**
  Configure ITbt VTD BAR.

  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI
  @param[in]   MchBar           MchBar Value

  @retval EFI_SUCCESS           Function executed successfully
**/
EFI_STATUS
ConfigureITbtVtdBar (
  IN  VTD_CONFIG  *Vtd,
  IN  UINTN       MchBar
  )
{
  UINTN          ItbtSegment;
  UINTN          ItbtBus;
  UINTN          ItbtDevice;
  UINTN          ItbtFunction;
  EFI_STATUS     Status;
  UINT8          Index;
  UINT32         Data32Or;

  for( Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    Status = GetItbtPcieRpInfo (Index, &ItbtSegment, &ItbtBus, &ItbtDevice, &ItbtFunction);
    if (Status == EFI_SUCCESS) {
      if ((PciSegmentRead16(PCI_SEGMENT_LIB_ADDRESS (ItbtSegment, SA_ITBT_PCIE_BUS_NUM , SA_ITBT_PCIE_DEV_NUM , ItbtFunction, PCI_VENDOR_ID_OFFSET)) != 0xFFFF)  && (Vtd->VtdItbtEnable == 1)) {
        Data32Or = Vtd->BaseAddress[Index + 3];
        Data32Or |= 0x1;
        MmioWrite32 (MchBar + (R_MCHBAR_ITBT_PCIE_0_VTD_HIGH_OFFSET + (8 * Index)), 0);
        MmioWrite32 (MchBar + (R_MCHBAR_ITBT_PCIE_0_VTD_LOW_OFFSET + (8 * Index)), Data32Or);
        PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (ItbtSegment, SA_ITBT_PCIE_BUS_NUM, SA_ITBT_PCIE_DEV_NUM, ItbtFunction, R_SA_VTD_ITBT_PCIE_UBAR), 0);
        PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (ItbtSegment, SA_ITBT_PCIE_BUS_NUM, SA_ITBT_PCIE_DEV_NUM, ItbtFunction, R_SA_VTD_ITBT_PCIE_LBAR), Data32Or);
        DEBUG ((DEBUG_INFO, "Itbt PCIE%d VTdBar : 0x%x \n", Index, Data32Or));
      }
    }
  }
  return EFI_SUCCESS;
}
#endif

/**
  Configure VT-d Base and capabilities for IPs available in PostMem

  @param[in]   VTD_CONFIG                 VTD config block from SA Policy PPI

  @retval EFI_SUCCESS     - Vtd initialization complete
  @exception EFI_UNSUPPORTED - Vtd is not enabled by policy
**/
EFI_STATUS
VtdLateInit (
  IN       VTD_CONFIG                        *Vtd
  )
{
  UINT32         VtdBase;
  BOOLEAN        IpuExisted;
  BOOLEAN        IgdExisted;
  BOOLEAN        VtdIntRemapSupport [VTD_ENGINE_NUMBER];
  VTD_DATA_HOB   *VtdDataHob;
  UINT8          Index;
  BOOLEAN        ItbtEnabled;
  BOOLEAN        ItbtIntRemapStatus;
#if FixedPcdGetBool(PcdITbtEnable) == 1
  UINT64         McD0BaseAddress;
  UINTN          MchBar;
  BOOLEAN        ItbtPciePortExisted[MAX_ITBT_PCIE_PORT];
  UINTN          ItbtSegment;
  UINTN          ItbtBus;
  UINTN          ItbtDevice;
  UINTN          ItbtFunction;
  EFI_STATUS     Status;
#endif

  DEBUG ((DEBUG_INFO, "VtdLateInit \n"));

  VtdDataHob       = NULL;
  VtdDataHob = GetFirstGuidHob (&gVtdDataHobGuid);
  if (VtdDataHob == NULL) {
    DEBUG ((DEBUG_WARN, "Failed to retrieve Vt-d Data Hob.! VT-d cannot be enabled!\n"));
    return EFI_UNSUPPORTED;
  }

  ItbtEnabled                 = FALSE;
  ItbtIntRemapStatus          = FALSE;
  IpuExisted                  = FALSE;
  IgdExisted                  = FALSE;
#if FixedPcdGetBool(PcdITbtEnable) == 1
  McD0BaseAddress             = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  MchBar                      = PciSegmentRead32 (McD0BaseAddress + R_SA_MCHBAR) &~BIT0;

  for(Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    ItbtPciePortExisted[Index] = FALSE;
  }

  //
  // Check whether Vt-d is supported
  //
  if ((PciSegmentRead32 (McD0BaseAddress + R_SA_MC_CAPID0_A_OFFSET) & BIT23)) {
    DEBUG ((DEBUG_WARN, "No VTd capability!\n"));
    return EFI_UNSUPPORTED;
  }

  //
  // BIOS need to clear iTBT VTDBAR if VT-d is disabled or not supported
  //
  if ((Vtd->VtdDisable) || (Vtd->VtdItbtEnable == 0)) {
    ClearITbtVtdBar(Vtd, MchBar);
    if (Vtd->VtdDisable){
      DEBUG ((DEBUG_WARN, "VTd disabled!\n"));
      return EFI_UNSUPPORTED;
    }
  }

#endif

  ///
  /// Check IGD existed or not
  ///
  if ((PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, PCI_VENDOR_ID_OFFSET)) != 0xFFFF) && (!IsDisplayOnlySku())) {
    IgdExisted = TRUE;
  }


#if FixedPcdGetBool(PcdITbtEnable) == 1
  ///
  /// Program Remap Engine Base Address
  ///
  ///
  /// Configure iTBT PCIE RP [0-3] VTD BAR
  /// Skip VTBAR if PCIE RP is disabled
  ///
  ConfigureITbtVtdBar (Vtd, MchBar);

  for(Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    Status = GetItbtPcieRpInfo (Index, &ItbtSegment, &ItbtBus, &ItbtDevice, &ItbtFunction);
    if (Status == EFI_SUCCESS) {
      if ((PciSegmentRead16(PCI_SEGMENT_LIB_ADDRESS (ItbtSegment, SA_ITBT_PCIE_BUS_NUM , SA_ITBT_PCIE_DEV_NUM , ItbtFunction, PCI_VENDOR_ID_OFFSET)) != 0xFFFF)  && (Vtd->VtdItbtEnable == 1)) {
        ItbtPciePortExisted[Index] = TRUE;
      }
    }
  }
#endif

  for (Index = 0; Index < VTD_ENGINE_NUMBER; Index++) {
    //
    // Set InterruptRemappingSupport default to FALSE
    //
    VtdIntRemapSupport[Index] = FALSE;
    VtdBase = ReadVtdBaseAddress (Index);

    ///
    /// skip if the VT bar is 0
    ///
    if (VtdBase == 0) {
      continue;
    }

    ///
    /// Check IR status and update the InterruptRemappingSupport
    ///
    if (MmioRead32 (VtdBase + R_VTD_ECAP_OFFSET) & B_VTD_ECAP_REG_IR) {
      VtdIntRemapSupport[Index] = TRUE;
    }
    DEBUG ((DEBUG_INFO, "VTd VtdIntRemapSupport[%d]: %x\n",Index,VtdIntRemapSupport[Index]));
  }

#if FixedPcdGetBool(PcdITbtEnable) == 1
  //
  // Set ItbtEnabled true if atleast one iTBT PCIE port present adn ItbtIntRemapStatus true only if all present iTBT ports supports it
  //
  for(Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    if (ItbtPciePortExisted[Index] == TRUE) {
      ItbtEnabled = TRUE;
      if (VtdIntRemapSupport[Index+3] == TRUE) {
        ItbtIntRemapStatus = TRUE;
      } else {
       ItbtIntRemapStatus = FALSE;
       break;
      }
    }
  }
#endif

  //
  // Set IR support default as false
  //
  VtdDataHob->InterruptRemappingSupport = FALSE;
  if (IgdExisted == TRUE && IpuExisted == TRUE && ItbtEnabled == TRUE) {
    if (VtdIntRemapSupport[0] == TRUE && VtdIntRemapSupport[1] == TRUE && VtdIntRemapSupport[2] == TRUE && ItbtIntRemapStatus == TRUE) {
      VtdDataHob->InterruptRemappingSupport = TRUE;
    }
  } else if (IgdExisted == TRUE && IpuExisted == FALSE && ItbtEnabled == TRUE) {
    if (VtdIntRemapSupport[0] == TRUE && VtdIntRemapSupport[2] == TRUE && ItbtIntRemapStatus == TRUE) {
      VtdDataHob->InterruptRemappingSupport = TRUE;
    }
  } else if (IgdExisted == FALSE && IpuExisted == TRUE && ItbtEnabled == TRUE) {
    if (VtdIntRemapSupport[1] == TRUE && VtdIntRemapSupport[2] == TRUE && ItbtIntRemapStatus == TRUE) {
      VtdDataHob->InterruptRemappingSupport = TRUE;
    }
  } else if (IgdExisted == TRUE && IpuExisted == TRUE && ItbtEnabled == FALSE) {
    if (VtdIntRemapSupport[0] == TRUE && VtdIntRemapSupport[1] == TRUE && VtdIntRemapSupport[2] == TRUE) {
      VtdDataHob->InterruptRemappingSupport = TRUE;
    }
  } else if (IgdExisted == FALSE && IpuExisted == FALSE && ItbtEnabled == TRUE) {
    if (VtdIntRemapSupport[2] == TRUE && ItbtIntRemapStatus == TRUE) {
      VtdDataHob->InterruptRemappingSupport = TRUE;
    }
  } else if (IgdExisted == TRUE && IpuExisted == FALSE && ItbtEnabled == FALSE) {
    if (VtdIntRemapSupport[0] == TRUE && VtdIntRemapSupport[2] == TRUE) {
      VtdDataHob->InterruptRemappingSupport = TRUE;
    }
    if(Vtd->VtdIgdEnable == FALSE && VtdIntRemapSupport[2] == TRUE) {
      VtdDataHob->InterruptRemappingSupport = TRUE;
    }
  } else if (IgdExisted == FALSE && IpuExisted == TRUE && ItbtEnabled == FALSE) {
    if (VtdIntRemapSupport[1] == TRUE && VtdIntRemapSupport[2] == TRUE) {
      VtdDataHob->InterruptRemappingSupport = TRUE;
    }
  } else {
    if (VtdIntRemapSupport[2] == TRUE) {
      VtdDataHob->InterruptRemappingSupport = TRUE;
    }
  }

  DEBUG ((DEBUG_INFO, "VTd InterruptRemappingSupport: %x\n",VtdDataHob->InterruptRemappingSupport));

  return EFI_SUCCESS;
}

/**
  Installs VTD Data Hob

  @retval EFI_SUCCESS           The HOB was successfully created.
  @retval EFI_OUT_OF_RESOURCES  There is no additional space for HOB creation.
**/
EFI_STATUS
InstallVtdDataHob (
  VOID
  )
{
  EFI_STATUS                  Status;
  VTD_DATA_HOB                *VtdDataHob;

  ///
  /// Create HOB for VTD Data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (VTD_DATA_HOB),
             (VOID **) &VtdDataHob
             );
  ASSERT_EFI_ERROR (Status);
  ///
  /// Initialize default HOB data
  ///
  VtdDataHob->EfiHobGuidType.Name = gVtdDataHobGuid;
  DEBUG ((DEBUG_INFO, "VtdDataHob->EfiHobGuidType.Name: %g\n", &VtdDataHob->EfiHobGuidType.Name));
  ZeroMem (&(VtdDataHob->VtdDisable), sizeof (VTD_DATA_HOB) - sizeof (EFI_HOB_GUID_TYPE));

  DEBUG ((DEBUG_INFO, "VtdDataHob @ %X\n", VtdDataHob));
  DEBUG ((DEBUG_INFO, "VtdDataHobSize - HobHeader: %X\n", sizeof (VTD_DATA_HOB) - sizeof (EFI_HOB_GUID_TYPE)));
  DEBUG ((DEBUG_INFO, "VtdDataHobSize: %X\n", sizeof (VTD_DATA_HOB)));

  return Status;
}
