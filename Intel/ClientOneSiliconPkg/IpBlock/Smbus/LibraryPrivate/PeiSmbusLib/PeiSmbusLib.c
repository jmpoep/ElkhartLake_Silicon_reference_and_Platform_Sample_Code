/** @file
  PCH Smbus Library

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
#include "PeiSmbusLibInternal.h"
#include <Library/PeiSmbusLib.h>
#include <Register/PchRegs.h>
#include <Register/SmbusRegs.h>

/**
  Configures interrupt number and enables interrupt generation for TCO.

  @param[in] Irq                 IRQ number. If 0 do not enable interrupts for TCO
**/
VOID
PchTcoIrqSet (
  IN  UINT8          Irq
  )
{
  UINT32  Data32Or;

  if (Irq == 0) {
    return;
  }

  Data32Or = B_SMBUS_PCR_TCOCFG_IE;

  //
  // IRQx    Value to set in register
  // IRQ9    000b
  // IRQ10   001b
  // IRQ11   010b
  // IRQ20   100b
  // IRQ21   101b
  // IRQ22   110b
  // IRQ23   111b
  //
  switch (Irq) {
    case 9:  Data32Or |= V_SMBUS_PCR_TCOCFG_IRQ_9;  break;
    case 10: Data32Or |= V_SMBUS_PCR_TCOCFG_IRQ_10; break;
    case 11: Data32Or |= V_SMBUS_PCR_TCOCFG_IRQ_11; break;
    case 20: Data32Or |= V_SMBUS_PCR_TCOCFG_IRQ_20; break;
    case 21: Data32Or |= V_SMBUS_PCR_TCOCFG_IRQ_21; break;
    case 22: Data32Or |= V_SMBUS_PCR_TCOCFG_IRQ_22; break;
    case 23: Data32Or |= V_SMBUS_PCR_TCOCFG_IRQ_23; break;
    default:
      //
      // Unsupported TCO IRQ
      //
      ASSERT (FALSE);
      return;
  }

  PchPcrAndThenOr32 (
    PID_SMB, R_SMBUS_PCR_TCOCFG,
    ~(UINT32) (B_SMBUS_PCR_TCOCFG_IS | B_SMBUS_PCR_TCOCFG_IE),
    Data32Or
    );
}

/**
  The function performs SMBUS specific programming.

  @param[in] SiPolicyPpi       The SI Policy PPI instance

**/
VOID
SmbusConfigure (
  IN  SI_POLICY_PPI           *SiPolicyPpi
  )
{
  UINT64                      SmbusBaseAddress;
  UINT32                      Data32And;
  UINT32                      Data32Or;
  EFI_STATUS                  Status;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  PCH_SMBUS_PREMEM_CONFIG     *SmbusPreMemConfig;
  UINT16                      SmbusIoBase;
  UINT8                       InterruptPin;
  PCH_GENERAL_PREMEM_CONFIG   *PchGeneralPreMemConfig;

  Data32And = 0xFFFFFFFF;
  Data32Or = 0;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSmbusPreMemConfigGuid, (VOID *) &SmbusPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPchGeneralPreMemConfigGuid, (VOID *) &PchGeneralPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  SmbusBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                       DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                       DEFAULT_PCI_BUS_NUMBER_PCH,
                       PCI_DEVICE_NUMBER_PCH_SMBUS,
                       PCI_FUNCTION_NUMBER_PCH_SMBUS,
                       0
                       );

  if (PchGeneralPreMemConfig->PchMasterPowerGating == 0) {
    SmbusPreMemConfig->DynamicPowerGating = 0;
  }
  ///
  /// Enable SMBus dynamic clock gating by setting Smbus PCI offset 80h [20,16,14,12,10,8] = 0b and [5] = 1b respectively
  /// Configure SMBus dynamic clock gating of PGCB (80h[18]) based on policy
  ///
  if (PchGeneralPreMemConfig->PchMasterClockGating != 0) {
    Data32And = (UINT32) ~(BIT20 | BIT16 | BIT14 | BIT12 | BIT10 | BIT8);
    Data32Or  = (UINT32) (BIT5);
  } else {
    Data32And = (UINT32) ~(0);
    Data32Or  = (UINT32) (BIT20 | BIT16 | BIT14 | BIT12 | BIT10 | BIT8 | BIT5);
  }
  if (SmbusPreMemConfig->DynamicPowerGating) {
    Data32And &= (UINT32)~BIT18;
  } else {
    Data32Or |= BIT18;
  }
  PciSegmentAndThenOr32 (
    SmbusBaseAddress + R_SMBUS_CFG_80,
    Data32And,
    Data32Or
    );

  ///
  /// Set SMBUS PCR 0x10h [5] = 1 and clear [2,1,0] = 0
  ///
  if (PchGeneralPreMemConfig->PchMasterPowerGating != 0) {
    Data32And = (UINT32)~(BIT2 | BIT1 | BIT0);
  } else {
    Data32And = (UINT32)~(BIT5 | BIT3 | BIT2 | BIT1 | BIT0);
  }
  if (SmbusPreMemConfig->DynamicPowerGating) {
    Data32Or = (UINT32) B_SMBUS_PCR_PCE_HAE;
  } else {
    Data32Or = 0;
  }
  PchPcrAndThenOr32 (
    PID_SMB, R_SMBUS_PCR_PCE,
    Data32And,
    Data32Or
    );

  SmbusIoBase = PciSegmentRead16 (SmbusBaseAddress + R_SMBUS_CFG_BASE) & B_SMBUS_CFG_BASE_BAR;
  ASSERT (SmbusIoBase != 0);
  ASSERT (PciSegmentRead8 (SmbusBaseAddress + PCI_COMMAND_OFFSET) & EFI_PCI_COMMAND_IO_SPACE);

  ///
  /// Clear SMBUS Alert status in case it got set after enabling SMBALERT# pin
  ///
  IoWrite8 (SmbusIoBase + R_SMBUS_IO_HSTS, B_SMBUS_IO_SMBALERT_STS);

  ///
  /// Check to disable Smbus controller
  ///
  if (SmbusPreMemConfig->Enable == FALSE) {
    PchPcrAndThenOr32 (
      PID_SMB, R_SMBUS_PCR_GC,
      0xFFFFFFFF,
      B_SMBUS_PCR_GC_FD
      );

    ///
    /// Disable and hide SMBUS in PSF
    ///
    PsfDisableSmbusDevice ();
    return;
  }
  ///
  /// Configure SMBUS interrupt
  ///
  InterruptPin = ItssGetDevIntPin (SiPolicyPpi, PCI_DEVICE_NUMBER_PCH_SMBUS, PCI_FUNCTION_NUMBER_PCH_SMBUS);

  PciSegmentWrite8 (SmbusBaseAddress + PCI_INT_PIN_OFFSET, InterruptPin);

  ///
  /// Configure TCO IRQ
  ///
  PchTcoIrqSet (ItssGetTcoDevIntConfig (SiPolicyPpi));
}

/**
  Function to be called when SMBus.Execute happens. This will check if
  the SMBus Host Controller has received a Host Notify command. If so, it will
  see if a notification has been reqested on that event and make any callbacks
  that may be necessary.

  @param[in] Private              Pointer to the SMBUS_INSTANCE

**/
STATIC
VOID
CheckNotification (
  IN SMBUS_INSTANCE *Private
  )
{
  EFI_SMBUS_DEVICE_ADDRESS  SlaveAddress;
  UINT8                     SstsReg;
  UINTN                     Data;
  UINTN                     Index;

  if (Private->ArpEnable == FALSE) {
    return;
  }

  DEBUG ((DEBUG_INFO, "PEI CheckNotification() Start\n"));

  if (Private->NotifyFunctionNum == 0) {
    ///
    /// Since no one register it, not need to check.
    ///
    return;
  }

  SstsReg = SmbusIoRead (R_SMBUS_IO_SSTS);
  if (!(SstsReg & B_SMBUS_IO_HOST_NOTIFY_STS)) {
    ///
    /// Host Notify has not been received
    ///
    return;
  }
  ///
  /// There was a Host Notify, see if any one wants to know about it
  ///
  SlaveAddress.SmbusDeviceAddress = (SmbusIoRead (R_SMBUS_IO_NDA)) >> 1;

  for (Index = 0; Index < Private->NotifyFunctionNum; Index++) {

    if (Private->NotifyFunctionList[Index].SlaveAddress.SmbusDeviceAddress == SlaveAddress.SmbusDeviceAddress) {
      Data = (SmbusIoRead (R_SMBUS_IO_NDHB) << 8) + (SmbusIoRead (R_SMBUS_IO_NDLB));
      if ((UINT16) Private->NotifyFunctionList[Index].Data == (UINT16) Data) {
        ///
        /// We have a match, notify the requested function
        ///
        Private->NotifyFunctionList[Index].NotifyFunction (
                                             &Private->SmbusPpi,
                                             SlaveAddress,
                                             Data
                                             );
      }
    }
  }
  ///
  /// Clear the Notify Status bit and exit.
  ///
  SmbusIoWrite (R_SMBUS_IO_SSTS, B_SMBUS_IO_HOST_NOTIFY_STS);

  DEBUG ((DEBUG_INFO, "PEI CheckNotification() End\n"));
}

/**
  This function provides a standard way to execute an SMBUS command
  PPI as defined in the SMBus Specification. The data can either be of
  the length byte, word, or a block of data (1 to 32 bytes long).
  The resulting transaction will be either the SMBus Slave Device accepts
  this transaction or this function returns with an error

  @param[in] This                 PEI_SMBUS_PPI instance
  @param[in] SlaveAddress         Smbus Slave device address
  @param[in] Command              Command to be sent
  @param[in] Operation            Which SMBus PPI will be used
  @param[in] PecCheck             Defines if Packet Error Code Checking is to be used
  @param[in, out] Length          How many bytes to read/write. Must be 1 <= Length <= 32 depending on the Operation
  @param[in, out] Buffer          Data buffer

  @retval EFI_SUCCESS             Operation success.
                                  Length will contain the actual number of bytes read.
                                  Buffer will contain the data read.
  @retval Otherwise               Operation failed.
**/
EFI_STATUS
EFIAPI
SmbusExecute (
  IN CONST EFI_PEI_SMBUS2_PPI *This,
  IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
  IN EFI_SMBUS_DEVICE_COMMAND Command,
  IN EFI_SMBUS_OPERATION      Operation,
  IN BOOLEAN                  PecCheck,
  IN OUT UINTN                *Length,
  IN OUT VOID                 *Buffer
  )
{
  EFI_STATUS     Status;
  SMBUS_INSTANCE *Private;
  DEBUG ((DEBUG_EVENT, "PEI SmbusExecute() Start, SmbusDeviceAddress=%x, Command=%x, Operation=%x\n", (SlaveAddress.SmbusDeviceAddress << 1), Command, Operation));
  Private = SMBUS_PRIVATE_DATA_FROM_PPI_THIS (This);

  Status = SmbusExec (
             SlaveAddress,
             Command,
             Operation,
             PecCheck,
             Length,
             Buffer
             );
  ///
  /// Last step, check notification
  ///
  CheckNotification (Private);
  DEBUG ((DEBUG_EVENT, "PEI SmbusExecute() End\n"));
  return Status;
}

/**
  This function initializes the SmBus driver in PEI.

  @param[in] Private              SMBUS private data structure
  @param[in] SmbusPreMemConfig    Smbus PREMEM config block

**/
VOID
InitializePeiPrivate (
  IN SMBUS_INSTANCE               *Private,
  IN PCH_SMBUS_PREMEM_CONFIG      *SmbusPreMemConfig
  )
{
  Private->Signature    = PCH_SMBUS_PRIVATE_DATA_SIGNATURE;

  Private->PlatformNumRsvd          = SmbusPreMemConfig->NumRsvdSmbusAddresses;
  CopyMem (
    Private->PlatformRsvdAddr,
    SmbusPreMemConfig->RsvdSmbusAddressTable,
    sizeof (SmbusPreMemConfig->RsvdSmbusAddressTable)
    );
  Private->ArpEnable                = (BOOLEAN) SmbusPreMemConfig->ArpEnable;

  Private->PpiDescriptor.Flags      = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  Private->PpiDescriptor.Guid       = &gEfiPeiSmbus2PpiGuid;

  Private->PpiDescriptor.Ppi        = &Private->SmbusPpi;

  Private->SmbusPpi.Execute         = SmbusExecute;
  Private->SmbusPpi.ArpDevice       = SmbusArpDevice;
  Private->SmbusPpi.GetArpMap       = SmbusGetArpMap;
  Private->SmbusPpi.Notify          = SmbusNotify;

  Private->DeviceMapEntries         = 0;
  Private->NotifyFunctionNum        = 0;

  return;
}

/**
  Initialize the Smbus PPI and program the Smbus BAR

  @param[in]  SiPreMemPolicyPpi   The SI PreMem Policy PPI instance

  @retval EFI_SUCCESS             The function completes successfully
  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create database
**/
EFI_STATUS
SmbusInit (
  IN  SI_PREMEM_POLICY_PPI   *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                  Status;
  SMBUS_INSTANCE              *Private;
  UINT64                      SmbusRegBase;
  PCH_SMBUS_PREMEM_CONFIG     *SmbusPreMemConfig;

  DEBUG ((DEBUG_INFO, "InitializePchSmbus() Start\n"));

  Private = (SMBUS_INSTANCE *) AllocatePool (sizeof (SMBUS_INSTANCE));
  if (Private == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to allocate memory for Private! \n"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSmbusPreMemConfigGuid, (VOID *) &SmbusPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  InitializePeiPrivate (Private, SmbusPreMemConfig);

  SmbusRegBase = PCI_SEGMENT_LIB_ADDRESS (
                   DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_SMBUS,
                   PCI_FUNCTION_NUMBER_PCH_SMBUS,
                   0
                   );
  ///
  /// Set SMBus PCI 0x64 = 0x0A0A0000
  ///
  PciSegmentWrite32 (SmbusRegBase + R_SMBUS_CFG_64, 0x0A0A0000);
  ///
  /// Since PEI has no PCI enumerator, set the BAR & I/O space enable ourselves
  ///
  PciSegmentAndThenOr32 (SmbusRegBase + R_SMBUS_CFG_BASE, B_SMBUS_CFG_BASE_BAR, SmbusPreMemConfig->SmbusIoBase);

  PciSegmentOr8 (SmbusRegBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_IO_SPACE);

  if (SmbusPreMemConfig->SpdWriteDisable) {
    ///
    /// PCH BIOS Spec section 5.16 Security Recommendations - Set SPD write disable bit, Smbus PCI offset 40h[4] = 1b
    ///
    PciSegmentOr8 (SmbusRegBase + R_SMBUS_CFG_HOSTC, B_SMBUS_CFG_HOSTC_SPDWD);
  }

  ///
  /// Reset the SMBus host controller
  ///
  PciSegmentOr8 (SmbusRegBase + R_SMBUS_CFG_HOSTC, B_SMBUS_CFG_HOSTC_SSRESET);

  ///
  /// Enable the SMBus host controller
  ///
  PciSegmentAndThenOr8 (
    SmbusRegBase + R_SMBUS_CFG_HOSTC,
    (UINT8) (~(B_SMBUS_CFG_HOSTC_SMI_EN | B_SMBUS_CFG_HOSTC_I2C_EN)),
    B_SMBUS_CFG_HOSTC_HST_EN
    );

  ///
  /// Clear Status Register before anyone uses the interfaces
  ///
  SmbusIoWrite (R_SMBUS_IO_HSTS, B_SMBUS_IO_HSTS_ALL);

  Status = PeiServicesInstallPpi (&Private->PpiDescriptor);
  ASSERT_EFI_ERROR (Status);

  //
  // Enable SMBUS interface pins
  //
  if (SmbusPreMemConfig->Enable) {
    GpioEnableSmbus ();
    if (SmbusPreMemConfig->SmbAlertEnable) {
      GpioEnableSmbusAlert ();
    }
  }

  DEBUG ((DEBUG_INFO, "InitializePchSmbus() End\n"));

  return EFI_SUCCESS;
}
/**
  This function install a data HOB if any devices were ARPed during PEI.
  It describes what devices were ARPed and  passes these info to DXE.

  @retval EFI_SUCCESS             The function completed successfully.
**/
STATIC
EFI_STATUS
PchSmbusArpEnableInstallDataHob (
  VOID
  )
{
  EFI_STATUS              Status;
  EFI_PEI_PPI_DESCRIPTOR  *SmbusDescriptor;
  EFI_PEI_SMBUS2_PPI      *SmbusPpi;
  SMBUS_INSTANCE          *Private;
  UINTN                   BufferSize;
  VOID                    *Hob;

  Status = PeiServicesLocatePpi (
             &gEfiPeiSmbus2PpiGuid, /// GUID
             0,                     /// INSTANCE
             &SmbusDescriptor,      /// PEI_PPI_DESCRIPTOR
             (VOID **) &SmbusPpi    /// PPI
             );
  ASSERT_EFI_ERROR (Status);

  Private     = SMBUS_PRIVATE_DATA_FROM_DESCRIPTOR_THIS (SmbusDescriptor);
  BufferSize  = sizeof (EFI_SMBUS_DEVICE_MAP) * Private->DeviceMapEntries;

  Hob = BuildGuidDataHob (
          &gEfiSmbusArpMapGuid,
          Private->DeviceMap,
          BufferSize
          );
  ASSERT (Hob != NULL);

  return EFI_SUCCESS;
}


/**
  Set Slave address for an Smbus device with a known UDID or perform a general
  ARP of all devices.

  @param[in] This                 Pointer to the instance of the PEI_SMBUS_PPI.
  @param[in] ArpAll               If TRUE, do a full ARP. Otherwise, just ARP the specified UDID.
  @param[in] SmbusUdid            When doing a directed ARP, ARP the device with this UDID.
  @param[in, out] SlaveAddress    Buffer to store new Slave Address during directed ARP.

  @exception EFI_UNSUPPORTED      This functionality is not supported
  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
SmbusArpDevice (
  IN CONST EFI_PEI_SMBUS2_PPI       *This,
  IN      BOOLEAN                   ArpAll,
  IN      EFI_SMBUS_UDID            *SmbusUdid OPTIONAL,
  IN OUT  EFI_SMBUS_DEVICE_ADDRESS  *SlaveAddress OPTIONAL
  )
{
  SMBUS_INSTANCE *Private;
  EFI_STATUS     Status;
  UINT8          OldMapEntries;

  DEBUG ((DEBUG_INFO, "PEI SmbusArpDevice() Start\n"));

  Private       = SMBUS_PRIVATE_DATA_FROM_PPI_THIS (This);

  if (Private->ArpEnable == FALSE) {
    return EFI_UNSUPPORTED;
  }

  OldMapEntries = Private->DeviceMapEntries;

  if (ArpAll) {
    Status = SmbusFullArp (Private);
  } else {
    if ((SmbusUdid == NULL) || (SlaveAddress == NULL)) {
      return EFI_INVALID_PARAMETER;
    }

    Status = SmbusDirectedArp (Private, SmbusUdid, SlaveAddress);
  }

  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// If we just added the first entry in the device map, set up a HOB so
  /// we can pass the map to DXE.
  ///
  if ((OldMapEntries == 0) && (Private->DeviceMapEntries > 0)) {
    Status = PchSmbusArpEnableInstallDataHob ();
    ASSERT_EFI_ERROR (Status);
  }

  DEBUG ((DEBUG_INFO, "PEI SmbusArpDevice() End\n"));

  return EFI_SUCCESS;
}

/**
  Get a pointer to the assigned mappings of UDID's to Slave Addresses.

  @param[in] This                 Pointer to the instance of the PEI_SMBUS_PPI.
  @param[in, out] Length          Buffer to contain the lenght of the Device Map.
  @param[in, out] SmbusDeviceMap  Buffer to contian a pointer to the Device Map.

  @exception EFI_UNSUPPORTED      This functionality is not supported
  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
SmbusGetArpMap (
  IN CONST EFI_PEI_SMBUS2_PPI   *This,
  IN OUT   UINTN                *Length,
  IN OUT   EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
  )
{
  SMBUS_INSTANCE          *Private;

  Private         = SMBUS_PRIVATE_DATA_FROM_PPI_THIS (This);

  if (Private->ArpEnable == FALSE) {
    return EFI_UNSUPPORTED;
  }

  *Length         = Private->DeviceMapEntries * sizeof (EFI_SMBUS_DEVICE_MAP);
  *SmbusDeviceMap = Private->DeviceMap;
  return EFI_SUCCESS;
}

/**
  Register a callback in the event of a Host Notify command being sent by a
  specified Slave Device.

  @param[in] This                 The PPI instance
  @param[in] SlaveAddress         Address of the device whose Host Notify command we want to trap.
  @param[in] Data                 Data of the Host Notify command we want to trap.
  @param[in] NotifyFunction       Function to be called in the event the desired Host Notify command occurs.

  @exception EFI_UNSUPPORTED      This functionality is not supported
  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
SmbusNotify (
  IN CONST EFI_PEI_SMBUS2_PPI             *This,
  IN       EFI_SMBUS_DEVICE_ADDRESS       SlaveAddress,
  IN       UINTN                          Data,
  IN       EFI_PEI_SMBUS_NOTIFY2_FUNCTION NotifyFunction
  )
{
  SMBUS_INSTANCE          *Private;

  DEBUG ((DEBUG_INFO, "PEI SmbusNotify() Start\n"));

  Private = SMBUS_PRIVATE_DATA_FROM_PPI_THIS (This);

  if (Private->ArpEnable == FALSE) {
    return EFI_UNSUPPORTED;
  }

  if (NotifyFunction == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  ///
  /// NOTE: Currently there is no periodic event in PEI.
  /// So we just check the Notification at the end of in each
  /// Smbus.Execute function.
  ///
  if (Private->NotifyFunctionNum >= MAX_SMBUS_NOTIFICATION) {
    return EFI_OUT_OF_RESOURCES;
  }

  Private->NotifyFunctionList[Private->NotifyFunctionNum].SlaveAddress.SmbusDeviceAddress = SlaveAddress.SmbusDeviceAddress;
  Private->NotifyFunctionList[Private->NotifyFunctionNum].Data                            = Data;
  Private->NotifyFunctionList[Private->NotifyFunctionNum].NotifyFunction                  = NotifyFunction;
  Private->NotifyFunctionNum++;

  ///
  /// Last step, check notification
  ///
  CheckNotification (Private);

  DEBUG ((DEBUG_INFO, "PEI SmbusNotify() End\n"));

  return EFI_SUCCESS;
}
