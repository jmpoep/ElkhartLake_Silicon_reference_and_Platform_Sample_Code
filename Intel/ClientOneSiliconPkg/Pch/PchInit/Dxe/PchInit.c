/** @file
  This is the Common driver that initializes the Intel PCH.

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
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/TimerLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/HobLib.h>

#include "PchInit.h"
#include <PchPolicyCommon.h>
#include <Library/SpiCommonLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/PchDmiLib.h>
#include <Library/SiScheduleResetLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PchPcrLib.h>
#include <IndustryStandard/Pci30.h>
#include <Library/SpiAccessPrivateLib.h>
#include <Library/EspiAccessPrivateLib.h>
#include <Library/PchPseIoLib.h>
#include <Library/PsfLib.h>
#include <Register/PchRegs.h>
#include <Register/PchPcrRegs.h>
#include <Register/PchRegsLpc.h>
#include <Register/SpiRegs.h>
#include <Register/PchRegsPsth.h>
#include <Register/PmcRegs.h>
#include <Register/HdaRegs.h>
#include <Register/TraceHubRegs.h>
#include <Register/PseRegs.h>
#include <Library/GpioCheckConflictLib.h>

//
// Module variables
//
GLOBAL_REMOVE_IF_UNREFERENCED PCH_CONFIG_HOB           *mPchConfigHob;
GLOBAL_REMOVE_IF_UNREFERENCED SI_CONFIG_HOB_DATA       *mSiConfigHobData;

//
// EFI_EVENT
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_EVENT mHeciEvent;

/**
  Common PchInit Module Entry Point
**/
VOID
PchInitEntryPointCommon (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS  HobPtr;

  DEBUG ((DEBUG_INFO, "PchInitEntryPointCommon() Start\n"));

  //
  // Get PCH Config HOB.
  //
  HobPtr.Guid   = GetFirstGuidHob (&gPchConfigHobGuid);
  ASSERT (HobPtr.Guid != NULL);
  mPchConfigHob = (PCH_CONFIG_HOB *) GET_GUID_HOB_DATA (HobPtr.Guid);

  //
  // Get Silicon Config data HOB
  //
  HobPtr.Guid   = GetFirstGuidHob (&gSiConfigHobGuid);
  ASSERT (HobPtr.Guid != NULL);
  mSiConfigHobData = (SI_CONFIG_HOB_DATA *) GET_GUID_HOB_DATA (HobPtr.Guid);

  DEBUG ((DEBUG_INFO, "PchInitEntryPointCommon() End\n"));

  return;
}

/**
  Lock SPI register before boot
**/
VOID
LockSpiConfiguration (
  VOID
  )
{
  UINTN         Index;
  UINT16        Data16;
  UINT16        Data16And;
  UINT16        Data16Or;
  UINT32        Data32;
  UINT32        DlockValue;
  UINT64        PciSpiRegBase;
  UINT32        PchSpiBar0;
  UINT32        Timer;

  PciSpiRegBase   = PCI_SEGMENT_LIB_ADDRESS (
                      DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_SPI,
                      PCI_FUNCTION_NUMBER_PCH_SPI,
                      0
                      );

  //
  // Check for SPI controller presence before programming
  //
  if (PciSegmentRead32 (PciSpiRegBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return;
  }

  //
  // Make sure SPI BAR0 has fixed address before writing to boot script.
  // The same base address is set in PEI and will be used during resume.
  //
  PchSpiBar0 = PCH_SPI_BASE_ADDRESS;

  PciSegmentAnd8    (PciSpiRegBase + PCI_COMMAND_OFFSET, (UINT8) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  PciSegmentWrite32 (PciSpiRegBase + R_SPI_CFG_BAR0, PchSpiBar0);
  PciSegmentOr8     (PciSpiRegBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);

  //
  // Program the Flash Protection Range Register based on policy
  //
  DlockValue = MmioRead32 (PchSpiBar0 + R_SPI_MEM_DLOCK);
  for (Index = 0; Index < PCH_FLASH_PROTECTED_RANGES; ++Index) {
    if ((mPchConfigHob->ProtectRange[Index].WriteProtectionEnable ||
         mPchConfigHob->ProtectRange[Index].ReadProtectionEnable) != TRUE) {
      continue;
    }

    //
    // Proceed to program the register after ensure it is enabled
    //
    Data32 = 0;
    Data32 |= (mPchConfigHob->ProtectRange[Index].WriteProtectionEnable == TRUE) ? B_SPI_MEM_PRX_WPE : 0;
    Data32 |= (mPchConfigHob->ProtectRange[Index].ReadProtectionEnable == TRUE) ? B_SPI_MEM_PRX_RPE : 0;
    Data32 |= ((UINT32) mPchConfigHob->ProtectRange[Index].ProtectedRangeLimit << N_SPI_MEM_PRX_PRL) & B_SPI_MEM_PRX_PRL_MASK;
    Data32 |= ((UINT32) mPchConfigHob->ProtectRange[Index].ProtectedRangeBase << N_SPI_MEM_PRX_PRB) & B_SPI_MEM_PRX_PRB_MASK;
    DEBUG ((DEBUG_INFO, "Protected range %d: 0x%08x \n", Index, Data32));

    DlockValue |= (UINT32) (B_SPI_MEM_DLOCK_PR0LOCKDN << Index);
    MmioWrite32 ((UINTN) (PchSpiBar0 + (R_SPI_MEM_PR0 + (Index * S_SPI_MEM_PRX))), Data32);
    S3BootScriptSaveMemWrite (
      S3BootScriptWidthUint32,
      (UINTN) (PchSpiBar0 + (R_SPI_MEM_PR0 + (Index * S_SPI_MEM_PRX))),
      1,
      (VOID *) (UINTN) (PchSpiBar0 + (R_SPI_MEM_PR0 + (Index * S_SPI_MEM_PRX)))
      );
  }
  //
  // Program DLOCK register
  //
  MmioWrite32 ((UINTN) (PchSpiBar0 + R_SPI_MEM_DLOCK), DlockValue);
  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32,
    (UINTN) (PchSpiBar0 + R_SPI_MEM_DLOCK),
    1,
    (VOID *) (UINTN) (PchSpiBar0 + R_SPI_MEM_DLOCK)
    );

  ///
  /// PCH BIOS Spec Section 3.6 Flash Security Recommendation
  /// In PCH SPI controller the BIOS should set the Flash Configuration Lock-Down bit
  /// (SPI_BAR0 + 04[15]) at end of post.  When set to 1, those Flash Program Registers
  /// that are locked down by this FLOCKDN bit cannot be written.
  /// Please refer to the EDS for which program registers are impacted.
  /// Additionally BIOS must program SPI_BAR0 + 0x04 BIT11 (WRSDIS) to disable Write Status in HW sequencing
  ///

  //
  // Ensure there is no pending SPI trasaction before setting lock bits
  //
  Timer = 0;
  while (MmioRead16 (PchSpiBar0 + R_SPI_MEM_HSFSC) & B_SPI_MEM_HSFSC_SCIP) {
    if (Timer > SPI_WAIT_TIME) {
      //
      // SPI transaction is pending too long at this point, exit with error.
      //
      DEBUG ((DEBUG_ERROR, "SPI Cycle timeout\n"));
      ASSERT (FALSE);
      break;
    }
    MicroSecondDelay (SPI_WAIT_PERIOD);
    Timer += SPI_WAIT_PERIOD;
  }

  Data16And = B_SPI_MEM_HSFSC_SCIP;
  Data16    = 0;
  S3BootScriptSaveMemPoll (
    S3BootScriptWidthUint16,
    PchSpiBar0 + R_SPI_MEM_HSFSC,
    &Data16And,
    &Data16,
    SPI_WAIT_PERIOD,
    SPI_WAIT_TIME / SPI_WAIT_PERIOD
    );

  //
  // Clear any outstanding status
  //
  Data16Or  = B_SPI_MEM_HSFSC_SAF_DLE
            | B_SPI_MEM_HSFSC_SAF_ERROR
            | B_SPI_MEM_HSFSC_AEL
            | B_SPI_MEM_HSFSC_FCERR
            | B_SPI_MEM_HSFSC_FDONE;
  Data16And = 0xFFFF;
  MmioAndThenOr16 (PchSpiBar0 + R_SPI_MEM_HSFSC, Data16And, Data16Or);
  S3BootScriptSaveMemReadWrite (
    S3BootScriptWidthUint16,
    PchSpiBar0 + R_SPI_MEM_HSFSC,
    &Data16Or,
    &Data16And
    );

  //
  // Set WRSDIS
  //
  Data16Or  = B_SPI_MEM_HSFSC_WRSDIS;
  Data16And = 0xFFFF;
  MmioAndThenOr16 (PchSpiBar0 + R_SPI_MEM_HSFSC, Data16And, Data16Or);
  S3BootScriptSaveMemReadWrite (
    S3BootScriptWidthUint16,
    PchSpiBar0 + R_SPI_MEM_HSFSC,
    &Data16Or,
    &Data16And
    );

  //
  // Set FLOCKDN
  //
  Data16Or  = B_SPI_MEM_HSFSC_FLOCKDN;
  Data16And = 0xFFFF;
  MmioAndThenOr16 (PchSpiBar0 + R_SPI_MEM_HSFSC, Data16And, Data16Or);
  S3BootScriptSaveMemReadWrite (
    S3BootScriptWidthUint16,
    PchSpiBar0 + R_SPI_MEM_HSFSC,
    &Data16Or,
    &Data16And
    );

  ///
  /// SPI Flash Programming Guide Section 5.5.2 Vendor Component Lock
  /// It is strongly recommended that BIOS sets the Vendor Component Lock (VCL) bits. VCL applies
  /// the lock to both VSCC0 and VSCC1 even if VSCC0 is not used. Without the VCL bits set, it is
  /// possible to make Host/GbE VSCC register(s) changes in that can cause undesired host and
  /// integrated GbE Serial Flash functionality.
  ///
  MmioOr32 ((UINTN) (PchSpiBar0 + R_SPI_MEM_SFDP0_VSCC0), B_SPI_MEM_SFDP0_VSCC0_VCL);
  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32,
    (UINTN) (PchSpiBar0 + R_SPI_MEM_SFDP0_VSCC0),
    1,
    (VOID *) (UINTN) (PchSpiBar0 + R_SPI_MEM_SFDP0_VSCC0)
    );
}

/**
  Process all the lock downs
**/
VOID
ProcessAllLocks (
  VOID
  )
{
  UINT16        Data16And;
  UINT16        Data16Or;
  UINT16        TcoBase;

  PchTcoBaseGet (&TcoBase);

  //
  // Lock function disable (ST and NST PG) register fields.
  //
  PmcLockFunctionDisableConfigWithS3BootScript ();

  ///
  /// CNL PCH BWG Additional PCH DMI and OP-DMI Programming Steps
  /// Lock DMI.
  ///
    PchDmiSetLockWithS3BootScript ();

  //
  // Lock SPI register before boot.
  //
  LockSpiConfiguration ();

  ///
  /// Additional Power Management Programming
  /// Step 3
  /// Lock configuration after stretch and ACPI base programming completed.
  ///
  PmcLockSlpSxStretchingPolicyWithS3BootScript ();

  //
  // Set BiosLock amd BIOS interface lock.
  //
  SpiBiosLockEnableAndBiosInterfaceLockWithS3BootScript (
    (BOOLEAN) mPchConfigHob->LockDown.BiosLock,
    (BOOLEAN) mPchConfigHob->LockDown.BiosInterface
    );
  EspiBiosLockEnableAndBiosInterfaceLockWithS3BootScript (
    (BOOLEAN) mPchConfigHob->LockDown.BiosLock,
    (BOOLEAN) mPchConfigHob->LockDown.BiosInterface
    );

  if (mPchConfigHob->LockDown.BiosInterface == TRUE) {
    ///
    /// Set BIOS interface Lock-Down
    ///
    PchDmiSetBiosLockDownWithS3BootScript ();
  }

  //
  // Lock Down TCO
  //
  Data16And = 0xFFFF;
  Data16Or  = B_TCO_IO_TCO1_CNT_LOCK;
  IoOr16 (TcoBase + R_TCO_IO_TCO1_CNT, Data16Or);
  S3BootScriptSaveIoReadWrite (
    S3BootScriptWidthUint16,
    (UINTN) (TcoBase + R_TCO_IO_TCO1_CNT),
    &Data16Or,  // Data to be ORed
    &Data16And  // Data to be ANDed
    );

  ///
  /// PCH BIOS Spec Section 5.15.1 Additional Chipset Initialization
  /// Step 1
  /// Lock PMC Set Strap Message Interface
  ///
  PmcLockSetStrapMsgInterfaceWithS3BootScript ();
  //
  // Lock Down PMC
  //
  PmcLockWithS3BootScript ();
}

/**
  Set HD Audio PME bit
**/
VOID
ConfigureHdAudioPme (
  VOID
  )
{
  UINT64 HdaPciBase;

  HdaPciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_HDA,
                 PCI_FUNCTION_NUMBER_PCH_HDA,
                 0
                 );

  if (PciSegmentRead16 (HdaPciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return;
  }

  ///
  /// PME Enable for Audio controller
  ///
  if (mPchConfigHob->HdAudio.Pme == TRUE) {
    PciSegmentOr32 (HdaPciBase + R_HDA_CFG_PCS, (UINT32) B_HDA_CFG_PCS_PMEE);
  }
}

/**
  Set eSPI BME bit
**/
VOID
ConfigureEspiBme (
  VOID
  )
{
  UINT64 EspiPciBase;

  EspiPciBase = PCI_SEGMENT_LIB_ADDRESS (
                  DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                  DEFAULT_PCI_BUS_NUMBER_PCH,
                  PCI_DEVICE_NUMBER_PCH_LPC,
                  PCI_FUNCTION_NUMBER_PCH_LPC,
                  0
                  );

  if (PciSegmentRead16 (EspiPciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return;
  }
  if ((PciSegmentRead32 (EspiPciBase + R_ESPI_CFG_PCBC) & B_ESPI_CFG_PCBC_ESPI_EN) == 0) {
    return;
  }

  //
  // Refer to PCH BWG.
  // To enable eSPI bus mastering BIOS must enable BME in eSPI controller
  // and also set BME bit in the respective slave devices through Configuration
  // and Capabilities register of each slave using Get_Configuration and Set_Configuration functionality.
  //
  // NOTE: The setting is also done in PEI, but might be cleared by PCI bus during PCI enumeration.
  //       Therefore, reeable it after PCI enumeration done.
  //
  if (mPchConfigHob->Espi.BmeMasterSlaveEnabled == TRUE) {
    PciSegmentOr8 (EspiPciBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_BUS_MASTER);
  }
}

/**
  Set TraceHub MSE and BME bit
**/
VOID
ConfigureTraceHubMse (
  VOID
  )
{
  UINT64  TraceHubBaseAddress;

  //
  // Check if Trace Hub Device is present
  //
  TraceHubBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                          DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_TRACE_HUB,
                          PCI_FUNCTION_NUMBER_PCH_TRACE_HUB,
                          0
                          );

  if (PciSegmentRead16 (TraceHubBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return;
  }

  if (mPchConfigHob->PchTraceHub.PchTraceHubMode == 0x1) {
    ///
    /// Enable MSE and BME
    ///
    DEBUG ((DEBUG_INFO, "Enable TraceHub MSE and BME\n"));
    PciSegmentOr8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER);
  }
}

/**
  Set PSE related IPs BME bit
**/
VOID
ConfigurePseBmeAndPme (
  VOID
  )
{
  UINTN             PchPseBase;

  DEBUG ((DEBUG_INFO, "Set BME for PSE CAN0 and CAN1 devices\n"));
  // Set PSE CAN0 and CAN1 BME after PCI enumeration
  PchPseBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_PSE_CAN0,
                 PCI_FUNCTION_NUMBER_PCH_PSE_CAN0,
                 0
                 );
  if (PciSegmentRead16 (PchPseBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF) {
    PciSegmentOr16 (PchPseBase + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_BUS_MASTER));
  }

  PchPseBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_PSE_CAN1,
                 PCI_FUNCTION_NUMBER_PCH_PSE_CAN1,
                 0
                 );
  if (PciSegmentRead16 (PchPseBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF) {
    PciSegmentOr16 (PchPseBase + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_BUS_MASTER));
  }

  PchPseBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_PSE_LH2PSE,
                 PCI_FUNCTION_NUMBER_PCH_PSE_LH2PSE,
                 0
                 );
  if (PciSegmentRead16 (PchPseBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF) {
    PciSegmentOr32 (PchPseBase + R_PSE_PME_ENABLE, (UINT32) B_PSE_PME_ENABLE);
  }
}

/**
  Common PCH initialization before Boot Sript Table is closed

**/
VOID
PchOnPciEnumCompleteCommon (
  VOID
  )
{
  UINT32                                    Data32Or;
  UINT32                                    Data32And;
  BOOLEAN                                   ResetStatus;

  DEBUG ((DEBUG_INFO, "PchOnPciEnumCompleteCommon() Start\n"));

  if (SiScheduleResetIsRequired ()) {
    ResetStatus = SiScheduleResetPerformReset ();
    ASSERT (!ResetStatus);
  }

  ProcessAllLocks ();

  //
  // Perform remaining configuration for SATA on End of DXE
  //
  ConfigureSataOnEndOfDxe ();
  //
  // PSTHCTL (0xD00h[2]) = 1, PSTH IOSF Primary Trunk Clock Gating Enable (PSTHIOSFPTCGE)
  //
  Data32And = 0xFFFFFFFF;
  Data32Or =  B_PSTH_PCR_PSTHIOSFPTCGE;
  PchPcrAndThenOr32 (PID_PSTH, R_PSTH_PCR_PSTHCTL, Data32And, Data32Or);
  PCH_PCR_BOOT_SCRIPT_READ_WRITE (
    S3BootScriptWidthUint32,
    PID_PSTH, R_PSTH_PCR_PSTHCTL,
    &Data32Or,
    &Data32And
    );

  //
  // Set eSPI BME after PCI enumeration
  //
  ConfigureEspiBme ();

  //
  // Set TraceHub MSE and BME after PCI enumeration
  //
  ConfigureTraceHubMse ();

  // Set PSE BME and PME after PCI enumeration
  //
  ConfigurePseBmeAndPme ();

  //
  // Set HD Audio PME after PCI Enumeration since bit gets cleared by PCI bus driver
  //
  ConfigureHdAudioPme ();

  ///
  /// Set PMC_READ_DISABLE bit to prohibit reads from PMC
  ///
  PmcReadDisable ();

  ///
  /// Clear Global Reset Status, Power Failure and Host Reset Status bits
  ///
  PmcClearGlobalResetStatus ();
  PmcClearPowerFailureStatus ();
  PmcClearHostResetStatus ();

  GpioCheckConflict ();

  DEBUG ((DEBUG_INFO, "PchOnPciEnumCompleteCommon() End\n"));
}
