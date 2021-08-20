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

#ifndef __PEI_SERIAL_IO_INIT_PRIVATE_LIB_H__
#define __PEI_SERIAL_IO_INIT_PRIVATE_LIB_H__

#include <Library/PsfLib.h>
#include <Library/SerialIoPrivateLib.h>

/**
  Enables SerialIo Power Gating

  @param[in] PciCfgBase            Pci Config Offset
  @param[in] PchMasterPowerGating  PchMasterPowerGating

**/
VOID
SerialIoEnablePowerGating (
  IN UINT64                    PciCfgBase,
  IN BOOLEAN                   PchMasterPowerGating
  );

/**
  Configures SerialIo to work on fixed address assignment only through SEC/PEI phase.
  In Dxe MMIO will be reassigned.

  Note: Fixed memory is not allocated in OS as MotherBoard/Device resource

  @param[in] PciCfgBase          Pci Config Space Base
  @param[in] FixedBaseAddress    Fixed Base Address for BAR0

**/
VOID
SerialIoPciSetFixedMmio (
  IN UINT64        PciCfgBase,
  IN UINT32        FixedBaseAddress
  );

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
  );

/**
  Enables Pci mode in PSF for given Serial IO

  @param[in] PciConfgCtrAddr  Pci Config Register offset for  Serial IO
  @param[in] PsfPort          Psf Port data

**/
VOID
SerialIoPciPsfEnable (
  IN UINT16          PciConfgCtrAddr,
  IN PSF_PORT        PsfPort
  );

/**
  Disables Base Address Register 1 (MMIO BAR1) in Serial Io device

  @param[in] PciConfgCtrAddr  Pci Config Register offset for  Serial IO
  @param[in] PsfPort          Psf Port data

**/
VOID
SerialIoBar1Disable (
  IN UINT16          PciConfgCtrAddr,
  IN PSF_PORT        PsfPort
  );

/**
  Configures SerialIo device PSF

  @param[in] PciConfgCtrAddr  Pci Config Register offset for  Serial IO
  @param[in] PsfPort          Psf Port data

**/
VOID
SerialIoPciEnable (
  IN UINT16          PciConfgCtrAddr,
  IN PSF_PORT        PsfPort
  );

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
  );

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
  );

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
  );

/**
  Configures Serial IO Uart Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoUartInit (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  );

/**
  Configures Serial IO Uart Function 0 Disabled Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoUartFunction0Disable (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  );

/**
  Configures Serial IO Spi Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoSpiInit (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  );

/**
  Configures Serial IO Spi Function 0 Disabled Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoSpiFunction0Disable (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  );

/**
  Configures Serial IO I2c Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoI2cInit (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  );

/**
  Configures Serial IO I2c Function 0 Disabled Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoI2cFunction0Disable (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  );

/**
  Used to preserve current information about the device when it is configured in Pci mode in Pch Initialization.

  @param[in]     PciCfgBase    Pci Config Space Base
  @param[in/out] State         Pointer to state settings container

**/
VOID
SerialIoPciSave (
  IN     UINT64                      PciCfgBase,
  IN OUT SERIAL_IO_PCI_DEVICE_STATE  *State
  );

/**
  Used to restore device state after Pch Initialization.

  @param[in] PciCfgBase    Pci Config Space Base
  @param[in] State         Pointer to state settings container

**/
VOID
SerialIoPciRestore (
  IN UINT64                      PciCfgBase,
  IN SERIAL_IO_PCI_DEVICE_STATE  *State
  );

#endif //__PEI_SERIAL_IO_INIT_PRIVATE_LIB_H__
