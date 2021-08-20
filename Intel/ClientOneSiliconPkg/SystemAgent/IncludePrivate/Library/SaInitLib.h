/** @file
  Header file for the SA Init PEIM

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
#ifndef _SA_INIT_LIB_H_
#define _SA_INIT_LIB_H_

#include <Ppi/SiPolicy.h>
#include <SaDataHob.h>
#include <SaConfigHob.h>
#include <CpuPcieHob.h>
#include <Base.h>

#define MAX_ADDRESS_32BIT     0xFFFFFFFF

typedef struct {
  UINT32  BaseAddr;
  UINT32  Offset;
  UINT32  AndMask;
  UINT32  OrMask;
} BOOT_SCRIPT_REGISTER_SETTING;

//
// Functions
//
/**
  Check some SA policies are valid for debugging unexpected problem if these
  values are not initialized or assigned incorrect resource.

  @param[in] SiPreMemPolicyPpi    The SI PreMem Policy instance

**/
VOID
SaValidatePolicy (
  IN  SI_PREMEM_POLICY_PPI  *SiPreMemPolicyPpi
  );

/**
  <b>System Agent Initialization for early PEIM phase</b> \n
  - <b>Introduction</b> \n
    This module incorporates all SA initialization code required in PEI phase (early POST). Programming all needed System Agent BARs, initializing DMI link Gen2 (or Gen1), initializing PciExpress (PEG controller bifurcation) and Graphics (iGfx or external), and initializing DMI TC/VC mapping. This module needs to get executed before MRC.

  - @pre
    - SI_POLICY_PPI
    - _SI_CPU_POLICY_PPI
    - _PEI_STALL_PPI

  - @result
    All required SA BARs in PEI phase are initialized in this module (e.g. MCH_BAR, DMI_BAR and EP_BAR) with the data from SI_POLICY_PPI. PciExpress controllers (PEG Ports) are initialized based on the PEG bifurcation strapping and slot population; iGfx is initialized if no other external graphics is present; Via PCH_INIT_PPI, DMI GenX is programmed, TC/VC mapping is programmed and all SA and PCH VCs are polled for negotiation completion.
    - SA_DATA_HOB: A HOB created, containing a GUID and the some information about PEG and SMI.

  @retval EFI_SUCCESS           Function executed successfully
  @retval EFI_NOT_FOUND         The required PPI could not be located.
**/
EFI_STATUS
EFIAPI
SaOnPolicyInstalled (
  VOID
  );
/**
  SA late PEI Initialization.

  @retval EFI_SUCCESS           Function executed successfully
  @retval EFI_NOT_FOUND         The required PPI could not be located.
**/
EFI_STATUS
EFIAPI
SaInit (
  VOID
  );

/**
  Programs Sa Bars

  @param[in] MiscPeiPreMemConfig  - Instance of SA_MISC_PEI_PREMEM_CONFIG
**/
VOID
ProgramSaBars (
  IN SA_MISC_PEI_PREMEM_CONFIG      *MiscPeiPreMemConfig
  );


/**
  Init and Install SA Hob
  @param[in]  MiscPeiPreMemConfig - Instance of SA_MISC_PEI_PREMEM_CONFIG
  @param[out] SaDataHob           - SA_DATA_HOB instance installed by this function
  @param[out] SaConfigHob         - SA_CONFIG_HOB instance installed by this function
  @param[out] SaPegHob            - SA_PEG_HOB instance installed by this function
  @retval EFI_SUCCESS
**/
EFI_STATUS
InstallSaHob (
  IN       SA_MISC_PEI_PREMEM_CONFIG    *MiscPeiPreMemConfig,
  OUT      SA_DATA_HOB                  **SaDataHobOut,
  OUT      SA_CONFIG_HOB                **SaConfigHobOut
  );

/**
  Report the SA PCIe initialization code version.

  @param[in] MiscPeiPreMemConfig - Instance of SA_MISC_PEI_PREMEM_CONFIG

  @retval EFI_SUCCESS
**/
EFI_STATUS
ReportPcieVersion (
  IN    SA_MISC_PEI_PREMEM_CONFIG      *MiscPeiPreMemConfig
  );

/**
  BIOS_CPL_BIT is set for processor to activate the power and thermal management
  features on the platform.

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaResetComplete (
  VOID
  );

/**
  Function to handle SA at end of PEI

  @retval None

**/
EFI_STATUS
EFIAPI
SaOnEndOfPei (
  VOID
  );

/**
  This function handles SA S3 resume task

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
EFI_STATUS
SaS3ResumeAtEndOfPei (
  VOID
  );

/**
  This function does SA security lock
**/
VOID
SaSecurityLock (
  VOID
  );

/**
  This function enumerate all downstream bridge.

  @param[in] BusNum  - Primary bus number of current bridge

  @retval Current bus number: if current bus is an enpoint device
  @retval subordinate bus number: if current bus is a bridge
**/
UINT8
EnumerateDownstream (
  IN UINT8 BusNum
  );

/**
  Find the MMIO size that a given PCI device requires

  @param[in] BusNum     - Bus number of the device
  @param[in] DevNum     - device Number of the device
  @param[in] FunNum     - Function number of the device
  @param[out] MmioLength - MMIO Length in bytes
**/
VOID
FindPciDeviceMmioLength (
  IN UINT32  BusNum,
  IN UINT32  DevNum,
  IN UINT32  FunNum,
  OUT UINT32 *MmioLength
  );

/**
  Check if device has a legacy only OpROM (CSM required to dispatch device's OpROM)

  @param[in] OpRomScanTempMmioBar   - Temporary BAR to MMIO map OpROMs during VGA scanning
  @param[in] OpRomScanTempMmioLimit - Limit address for OpROM MMIO range
  @param[in] EpSegment              - Segment number for end point to check
  @param[in] EpBus                  - Bus number for end point to check
  @param[in] EpDev                  - Device number for end point to check
  @param[in] EpFunc                 - Function number for end point to check

  @retval TRUE if end point has a legacy only OpROM
  @retval FALSE if end point has a UEFI OpROM, Hybrid OpROM, or no OpROM
**/
BOOLEAN
CheckForLegacyOnlyOpRom (
  IN UINT32   OpRomScanTempMmioBar,
  IN UINT32   OpRomScanTempMmioLimit,
  IN UINT8    EpSegment,
  IN UINT8    EpBus,
  IN UINT8    EpDev,
  IN UINT8    EpFunc
  );

/**
  ProgramEdramMode - Disable EDRAM by default and enable it through HW Test Mode policy if needed

  @param[in] MiscPeiConfig - Instance of SA_MISC_PEI_CONFIG
**/
VOID
ProgramEdramMode (
  IN    SA_MISC_PEI_CONFIG          *MiscPeiConfig
  );


#endif
