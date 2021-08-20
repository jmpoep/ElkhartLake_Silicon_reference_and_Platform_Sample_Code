/** @file
 Pei Serial Io Init Private Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PsfLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/SerialIoAccessLib.h>
#include <Library/SerialIoPrivateLib.h>
#include <IndustryStandard/Pci30.h>
#include <Include/PcieRegs.h>
#include <Register/PchRegs.h>
#include <Register/PchPcrRegs.h>
#include <Register/SerialIoRegs.h>

/**
  Enables SerialIo Power Gating

  @param[in] PciCfgBase            Pci Config Offset
  @param[in] PchMasterPowerGating  PchMasterPowerGating

**/
VOID
SerialIoEnablePowerGating (
  IN UINT64                    PciCfgBase,
  IN BOOLEAN                   PchMasterPowerGating
  )
{
  if (PchMasterPowerGating) {
    PciSegmentOr32 (PciCfgBase + R_SERIAL_IO_CFG_D0I3MAXDEVPG,
                     B_SERIAL_IO_CFG_D0I3MAXDEVPG_PGE |
                     B_SERIAL_IO_CFG_D0I3MAXDEVPG_I3E |
                     B_SERIAL_IO_CFG_D0I3MAXDEVPG_PMCRE
                   );
  } else {
    PciSegmentAnd32 (
      PciCfgBase + R_SERIAL_IO_CFG_D0I3MAXDEVPG,
      (UINT32)~(BIT19 | B_SERIAL_IO_CFG_D0I3MAXDEVPG_PGE | B_SERIAL_IO_CFG_D0I3MAXDEVPG_I3E | B_SERIAL_IO_CFG_D0I3MAXDEVPG_PMCRE)
      );
  }
}

/**
  Configures SerialIo to work on fixed address assignment only through SEC/PEI phase.
  In DXE MMIO will be reassigned.

  Note: Fixed memory is not allocated in OS as MotherBoard/Device resource

  @param[in] PciCfgBase          Pci Config Space Base
  @param[in] FixedBaseAddress    Fixed Base Address for BAR0

**/
VOID
SerialIoPciSetFixedMmio (
  IN UINT64        PciCfgBase,
  IN UINT32        FixedBaseAddress
  )
{
  SerialIoSetD3 (PciCfgBase);
  SerialIoDisableMse (PciCfgBase);

  PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR0_LOW,  FixedBaseAddress);
  PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR0_HIGH, 0x0);
  PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR1_LOW,  0x0);
  PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR1_HIGH, 0x0);

  SerialIoSetD0 (PciCfgBase);
  SerialIoEnableMse (PciCfgBase, FALSE);
}

/**
  Configures SerialIo to work on fixed address assignments
  Disables Pci Enumaration for given device in PSF

  @param[in] PciCfgBase          Pci Config Space Base
  @param[in] FixedBaseAddress    Fixed Base Address for BAR0
  @param[in] FixedPciCfgAddress  Fixed Pci Config Space for BAR1
  @param[in] PciConfgCtrAddr     Register offset for each Serial IO
  @param[in] PsfPort             Psf Port data

**/
VOID
SerialIoSetFixedMmio (
  IN UINT64          PciCfgBase,
  IN UINT32          FixedBaseAddress,
  IN UINT32          FixedPciCfgAddress,
  IN UINT16          PciConfgCtrAddr,
  IN PSF_PORT        PsfPort
  )
{
  //
  // Disable memory
  //
  SerialIoSetD3 (PciCfgBase);
  SerialIoDisableMse (PciCfgBase);
  //
  // Reenable BAR1 in case it was disabled earlier
  //
  PchPcrAndThenOr32WithReadback (
    PID_SERIALIO,
    PciConfgCtrAddr,
    (UINT32) ~(B_SERIAL_IO_PCR_PCICFGCTRL_BAR1_DIS),
    0x0
    );
  PsfEnableDeviceBar (PsfPort, BIT3 | BIT2);
  //
  // Assign BAR0 and BAR1 (access to Pci Config Space)
  //
  PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR0_LOW, FixedBaseAddress);
  PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR0_HIGH, 0x0);
  PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR1_LOW, FixedPciCfgAddress);
  PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR1_HIGH, 0x0);
  //
  // Enable MSE and set D0 before placing device in Hidden Mode, otherwise memory will not map
  //
  SerialIoSetD0 (PciCfgBase);
  SerialIoEnableMse (PciCfgBase, FALSE);
  //
  // Disable device's PciCfg and enable ACPI interrupts
  //
  PchPcrAndThenOr32WithReadback (
    PID_SERIALIO,
    PciConfgCtrAddr,
    0xFFFFFFFF,
    (B_SERIAL_IO_PCR_PCICFGCTRL_PCI_CFG_DIS | B_SERIAL_IO_PCR_PCICFGCTRL_ACPI_INTR_EN)
    );
  //
  // Disable device's PciCfg in PSF
  //
  PsfHideDevice (PsfPort);
}

/**
  Enables Pci mode in PSF for given Serial IO

  @param[in] PciConfgCtrAddr  Pci Config Register offset for  Serial IO
  @param[in] PsfPort          Psf Port data

**/
VOID
SerialIoPciPsfEnable (
  IN UINT16          PciConfgCtrAddr,
  IN PSF_PORT        PsfPort
  )
{
  PchPcrAndThenOr32WithReadback (
    PID_SERIALIO,
    PciConfgCtrAddr,
    (UINT32) ~(B_SERIAL_IO_PCR_PCICFGCTRL_PCI_CFG_DIS | B_SERIAL_IO_PCR_PCICFGCTRL_ACPI_INTR_EN),
    0x0
    );
  PsfUnhideDevice (PsfPort);
}

/**
  Disables Base Address Register 1 (MMIO BAR1) in Serial Io device

  @param[in] PciConfgCtrAddr  Pci Config Register offset for  Serial IO
  @param[in] PsfPort          Psf Port data

**/
VOID
SerialIoBar1Disable (
  IN UINT16          PciConfgCtrAddr,
  IN PSF_PORT        PsfPort
  )
{
  //
  // Disable Bar1 in PCR
  // Disable Bar1 in PSF
  //
  PchPcrAndThenOr32WithReadback (
    PID_SERIALIO,
    PciConfgCtrAddr,
    0xFFFFFFFF,
    B_SERIAL_IO_PCR_PCICFGCTRL_BAR1_DIS
    );
  PsfDisableDeviceBar (PsfPort, BIT3 | BIT2);
}

/**
  Configures SerialIo device PSF

  @param[in] PciConfgCtrAddr  Pci Config Register offset for  Serial IO
  @param[in] PsfPort          Psf Port data

**/
VOID
SerialIoPciEnable (
  IN UINT16          PciConfgCtrAddr,
  IN PSF_PORT        PsfPort
  )
{
  //
  // Reenable PciCfg in case it was disabled earlier
  //
  SerialIoPciPsfEnable (PciConfgCtrAddr, PsfPort);
  SerialIoBar1Disable (PciConfgCtrAddr, PsfPort);
}

/**
  Configures SerialIo devices interrupt pin and IRQ assignment

  @param[in] ConfigControlOffset  Pci Config Register offset for  Serial IO
  @param[in] InterruptPin         Interrupt pin: INTA-INTD (see PCH_INT_PIN for reference)
  @param[in] Irq                  IRQ number

**/
VOID
SerialIoInterruptSet (
  IN UINT16                      ConfigControlOffset,
  IN UINT8                       InterruptPin,
  IN UINT8                       Irq
  )
{
  UINT32    Data32Or;
  UINT32    Data32And;

  ASSERT (ConfigControlOffset != 0);

  //
  // Set Interrupt Pin and Irq number
  //
  Data32Or  = (UINT32) ((InterruptPin << N_SERIAL_IO_PCR_PCICFGCTRL_INT_PIN) |
                        (Irq << N_SERIAL_IO_PCR_PCICFGCTRL_PCI_IRQ));
  Data32And =~(UINT32) (B_SERIAL_IO_PCR_PCICFGCTRL_PCI_IRQ | B_SERIAL_IO_PCR_PCICFGCTRL_ACPI_IRQ | B_SERIAL_IO_PCR_PCICFGCTRL_INT_PIN);

  PchPcrAndThenOr32 (PID_SERIALIO, ConfigControlOffset, Data32And, Data32Or);
}

/**
  Configures SerialIo devices interrupt pin and IRQ assignment

  @param[in] ConfigControlOffset  Pci Config Register offset for  Serial IO
  @param[in] InterruptPin         Interrupt pin: INTA-INTD (see PCH_INT_PIN for reference)
  @param[in] Irq                  APIC IRQ number

**/
VOID
SerialIoAcpiInterruptSet (
  IN UINT16                      ConfigControlOffset,
  IN UINT8                       InterruptPin,
  IN UINT8                       Irq
  )
{
  UINT32    Data32Or;
  UINT32    Data32And;

  ASSERT (ConfigControlOffset != 0);

  //
  // Set Interrupt Pin and Irq number
  //
  Data32Or  = (UINT32) ((InterruptPin << N_SERIAL_IO_PCR_PCICFGCTRL_INT_PIN) |
                        (Irq << N_SERIAL_IO_PCR_PCICFGCTRL_ACPI_IRQ));
  Data32And =~(UINT32) (B_SERIAL_IO_PCR_PCICFGCTRL_PCI_IRQ | B_SERIAL_IO_PCR_PCICFGCTRL_ACPI_IRQ | B_SERIAL_IO_PCR_PCICFGCTRL_INT_PIN);

  PchPcrAndThenOr32 (PID_SERIALIO, ConfigControlOffset, Data32And, Data32Or);
}

/**
  Enable SerialIo memory encoding

  @param[in] PciCfgBase       Pci Config Offset
  @param[in] AssignTempBar    Use temporary mem base address or not
  @param[in] Hidden           Mode that determines access type
  @param[out] Base            Base address

  @retval TRUE                Base address was obtained successfully
          FALSE               Failed to obtain Base Address Register address
**/
BOOLEAN
SerialIoMmioEnable (
  IN UINT64                    PciCfgBase,
  IN BOOLEAN                   AssignTempBar,
  IN BOOLEAN                   Hidden,
  OUT UINT64                   *Base
  )
{
  if (!Hidden) {
    if (PciSegmentRead32 (PciCfgBase + PCI_VENDOR_ID_OFFSET) == 0xFFFFFFFF) {
      ASSERT (FALSE);
      return FALSE;
    }
    if (AssignTempBar == TRUE) {
      PciSegmentAnd16 (PciCfgBase + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
      PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR0_LOW,  PcdGet32 (PcdSiliconInitTempMemBaseAddr));
      PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR0_HIGH, 0x0);
    }
    SerialIoEnableMse (PciCfgBase, Hidden);
  }

  SerialIoSetD0 (PciCfgBase);

  *Base = GetSerialIoBar (PciCfgBase);
  if ((*Base == 0xFFFFFFFFFFFFF000ULL) || (*Base == 0xFFFFF000ULL) || (*Base == 0x0)) {
    ASSERT (FALSE);
    return FALSE;
  }

  //
  // Get controller out of reset
  //
  MmioOr32 ((UINTN) (*Base + R_SERIAL_IO_MEM_PPR_RESETS), B_SERIAL_IO_MEM_PPR_RESETS_FUNC | B_SERIAL_IO_MEM_PPR_RESETS_APB | B_SERIAL_IO_MEM_PPR_RESETS_IDMA);

  return TRUE;
}

/**
  Used to preserve current information about the device when it is configured in Pci mode in Pch Initialization.

  @param[in]     PciCfgBase    Pci Config Space Base
  @param[in/out] State         Pointer to state settings container

**/
VOID
SerialIoPciSave (
  IN     UINT64                      PciCfgBase,
  IN OUT SERIAL_IO_PCI_DEVICE_STATE  *State
  )
{
  State->PciCfgBar0 = GetSerialIoBar (PciCfgBase);
  if ((State->PciCfgBar0 == 0xFFFFFFFFFFFFF000ULL) || (State->PciCfgBar0 == 0xFFFFF000ULL) || (State->PciCfgBar0 == 0x0)) {
    return; // No save/restore required
  }
  State->PciCfgPmeCtrlSts = PciSegmentRead8 ((UINTN) (PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS));
  State->PciCfgCommand    = PciSegmentRead8 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET));
  State->PprReset         = MmioRead8 ((UINTN) (State->PciCfgBar0 + R_SERIAL_IO_MEM_PPR_RESETS));
}

/**
  Used to restore device state after Pch Initialization.

  @param[in] PciCfgBase    Pci Config Space Base
  @param[in] State         Pointer to state settings container

**/
VOID
SerialIoPciRestore (
  IN UINT64                      PciCfgBase,
  IN SERIAL_IO_PCI_DEVICE_STATE  *State
  )
{
  if (State->PciCfgBar0 == 0x0) {
    return; // No save/restore required
  }
  MmioWrite8 ((UINTN) (State->PciCfgBar0 + R_SERIAL_IO_MEM_PPR_RESETS), State->PprReset);
  PciSegmentWrite32 ((UINTN) (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET), (UINT32) (State->PciCfgBar0 & 0xFFFFF000));
  PciSegmentWrite32 ((UINTN) (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET + 4), (UINT32) RShiftU64 (State->PciCfgBar0, 32));
  PciSegmentWrite8 ((UINTN) (PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS), State->PciCfgPmeCtrlSts);
  PciSegmentWrite8 ((UINTN) (PciCfgBase + PCI_COMMAND_OFFSET), State->PciCfgCommand);
}

