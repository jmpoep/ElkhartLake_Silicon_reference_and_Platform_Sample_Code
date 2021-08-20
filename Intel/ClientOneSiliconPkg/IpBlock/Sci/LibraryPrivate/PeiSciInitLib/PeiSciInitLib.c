/** @file
  Initializes SCI Device in PEI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2020 Intel Corporation.

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
#include <Library/PciSegmentLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PmcPrivateLib.h>
#include <Ppi/SiPolicy.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/PchPcrRegs.h>
#include <Register/PsfRegsVer3.h>
#include <Register/PchRegsPsf.h>
#include <Register/SciRegs.h>
#include <Register/PchRegsSciEhl.h>
#include <IndustryStandard/Pci30.h>
#include <Library/IoLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PeiSciInitLib.h>
#include <Library/TimerLib.h>
#include <Library/GpioPrivateLib.h>

//
// CCITT 16-bit CRC table
//
static const UINT16 CrcTable[256] = {
  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
  0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
  0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
  0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
  0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
  0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
  0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
  0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
  0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
  0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
  0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
  0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
  0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
  0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
  0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
  0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
  0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
  0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
  0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
  0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
  0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
  0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
  0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
  0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
  0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
  0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
  0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
  0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
  0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
  0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
  0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
  0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

/**
  Calculate CRC 16.

  @param[in] CrcData      Pointer to the data to calculate CRC
  @param[in] CrcSize      Length of the CRC data size

  @retval    UINT16       CRC value of given data
**/
UINT16
CalculateCrc16 (
  IN UINT8   *CrcData,
  IN UINT16  CrcSize
  )
{
  UINT16  Index;
  UINT16  Crc16;
  UINT8   *CrcDataPtr;

  Crc16 = 0xFFFF;

  for (Index = 0, CrcDataPtr = CrcData; Index < CrcSize; Index++, CrcDataPtr++) {
    Crc16 = (Crc16 << 8) ^ CrcTable[(UINT8) (Crc16 >> 8) ^ *CrcDataPtr];
  }

  return (Crc16 ^ 0x0000);
}

/**
  Configure SCI device registers

  @param[in] SiPolicy             The SI Policy PPI instance
**/
STATIC
VOID
ConfigureSciRegisters (
  IN  SI_POLICY_PPI               *SiPolicy
  )
{
  EFI_STATUS          Status;
  PCH_GENERAL_CONFIG  *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // Configure Power Management Control
  //
  if (PchGeneralConfig->PchMasterPowerGating != 0) {
    PchPcrWrite32 (
      PID_SCI,
      R_SCI_PCR_PMCTL,
      (BIT5| BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
      );
  } else {
    PchPcrWrite32 (
      PID_SCI,
      R_SCI_PCR_PMCTL,
      0
      );
  }
  //
  // Disable iosf2ocp BAR1
  //
  PchPcrAndThenOr32 (
    PID_SCI,
    R_SCI_PCR_PCICFGCTR_BASE,
    (UINT32) ~0,
    B_SCI_PCR_PCICFGCTR_BAR1DIS
    );
  //
  // Disable psf device BAR1
  //
  PchPcrAndThenOr32 (
    PID_PSF3,
    R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_ISI_REG_BASE + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    0xFFFFFFFF,
    (BIT3 | BIT2) << N_PCH_PSFX_PCR_T0_SHDW_PCIEN_BARXDIS
    );
}

/**
  Enable SCI MMIO space.

  @param[in] PciBaseAddress  Address of the controller's PCI space
  @param[in] MmioBase        MMIO address to use during initialization
**/
STATIC
VOID
SciEnableMmio (
  IN UINT64  PciBaseAddress,
  IN UINT32  MmioBase
  )
{
  PciSegmentAnd16 (PciBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  PciSegmentWrite32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, MmioBase);
  PciSegmentWrite32 (PciBaseAddress + (PCI_BASE_ADDRESSREG_OFFSET + 4), 0);
  PciSegmentOr16 (PciBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
}

/**
  Disable SCI MMIO space.

  @param[in] PciBaseAddress  Address of the controller's PCI space
**/
STATIC
VOID
SciDisableMmio (
  IN UINT64  PciBaseAddress
  )
{
  PciSegmentAnd16 (PciBaseAddress + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  PciSegmentWrite32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, 0);
}

/**
  Check the bit of doorbell in for mailbox readiness.

  @param[in] MmioBase  MMIO address to use during initialization

  @retval    BOOLEAN   TRUE if doorbell is ready, else FALSE
**/
STATIC
BOOLEAN
SciDoorbellInCheck (
  IN UINT32  MmioBase
  )
{
  UINT32    DoorBellIn;
  BOOLEAN   DrblInReady = FALSE;
  UINT8     RetryCount = 0;

  while ( (!DrblInReady) && (RetryCount < SCI_DRBL_CHECK_ATTEMPT)) {
    DoorBellIn = MmioRead32(MmioBase + R_SCI_MEM_DOORBELL_IN);

    // Doorbell is ready once we read '0' from bit0
    if (!(DoorBellIn & ((UINT32)B_SCI_MEM_DRBLIN_CHECK))) {
      DEBUG ((DEBUG_INFO, "Doorbell In ready\n"));
      DrblInReady = TRUE;
      break;
    }

    // Pause for a while before next check
    MicroSecondDelay (SCI_DRBL_DELAY);

    RetryCount++;
  }

  return DrblInReady;
}

/**
  Check the bit of doorbell out for mailbox readiness.

  @param[in] MmioBase  MMIO address to use during initialization

  @retval    BOOLEAN   TRUE if doorbell is ready, else FALSE
**/
STATIC
BOOLEAN
SciDoorbellOutCheck (
  IN UINT32  MmioBase
  )
{
  UINT32    DoorBellOut;
  BOOLEAN   DrblOutReady = FALSE;
  UINT8     RetryCount = 0;

  while ( (!DrblOutReady) && (RetryCount < SCI_DRBL_CHECK_ATTEMPT)) {
    DoorBellOut = MmioRead32(MmioBase + R_SCI_MEM_DOORBELL_OUT);

    // Doorbell is ready once we read '1' from bit0
    if (DoorBellOut & ((UINT32)B_SCI_MEM_DRBLOUT_CHECK)) {
      DEBUG ((DEBUG_INFO, "Doorbell Out ready\n"));
      DrblOutReady = TRUE;
      break;
    }

    // Pause for a while before next check
    MicroSecondDelay (SCI_DRBL_DELAY);

    RetryCount++;
  }

  return DrblOutReady;
}

/**
  Check the bit of doorbell in for mailbox readiness.

  @param[in] MbCommand    Mailbox command message
  @param[in] MbResponse   Mailbox response message

  @retval    BOOLEAN      TRUE if nothing is wrong, else FALSE
**/
STATIC
BOOLEAN
SciVerifyResponse (
  IN SCI_BOOT_CMPL_COMMAND    *MbCommand,
  IN SCI_BOOT_CMPL_RESPONSE   *MbResponse
  )
{
  UINT16  Crc16;
  UINT16  CrcResponse;

  // Verify the response data from certain parameters
  if ((MbResponse->MbHeader.Command != MbCommand->MbHeader.Command) ||
      (MbResponse->ResponseCode != 0) ||
      (!(MbResponse->MbHeader.Flags & (UINT8)SCI_FLAGS_BIT_RB))) {
    DEBUG ((DEBUG_INFO, "Invalid SCI response\n"));
    DEBUG ((DEBUG_INFO, "Command = 0x%x\n", MbResponse->MbHeader.Command));
    DEBUG ((DEBUG_INFO, "Response = 0x%x\n", MbResponse->ResponseCode));
    DEBUG ((DEBUG_INFO, "Flags = 0x%x\n", MbResponse->MbHeader.Flags));
    return FALSE;
  }

  // Now verify the CRC from response
  CrcResponse = MbResponse->MbHeader.Crc16;
  MbResponse->MbHeader.Crc16 = 0xFFFF;
  Crc16 = CalculateCrc16((UINT8*)MbResponse, SCI_BOOT_RESPONSE_LENGTH);
  MbResponse->MbHeader.Crc16 = CrcResponse;
  if (CrcResponse != Crc16) {
    DEBUG ((DEBUG_INFO, "CRC not matched\n"));
    return FALSE;
  }

  return TRUE;
}

/**
  Query SCI boot status.

  @retval    BOOLEAN   TRUE if SCI boot successful, else FALSE
**/
BOOLEAN
SciBootCheck (
  VOID
  )
{
  UINT64   PciBaseAddress;
  UINT32   MmioBase;
  UINT32   PciBarLo;
  UINT32   PciBarHi;
  UINT16   PciStatus;
  BOOLEAN  SciBootSts;

  SciBootSts = FALSE;

  PciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                     DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_SCI,
                     PCI_FUNCTION_NUMBER_PCH_SCI,
                     R_SCI_CFG_DEVICE_ID
                     );

  if (PciSegmentRead16 (PciBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    return FALSE;
  }

  // SCI shall enable Bus Master, SERR and PERR
  PciSegmentOr16 (PciBaseAddress + PCI_COMMAND_OFFSET,
                  EFI_PCI_COMMAND_SERR | EFI_PCI_COMMAND_PARITY_ERROR_RESPOND | EFI_PCI_COMMAND_BUS_MASTER);

  //
  // Keep the content as it is and not to overwrite
  //
  PciBarLo = PciSegmentRead32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET);
  PciBarHi = PciSegmentRead32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET + 4);
  PciStatus = PciSegmentRead16 (PciBaseAddress + PCI_PRIMARY_STATUS_OFFSET);

  //
  // Enable the MMIO mapping
  //
  MmioBase = PcdGet32(PcdSiliconInitTempMemBaseAddr);
  SciEnableMmio(PciBaseAddress, MmioBase);

  if ( V_SCI_MEM_BOOT_STATUS == MmioRead32 (MmioBase + R_SCI_MEM_SCRATCHPAD) ) {
    SciBootSts = TRUE;
  }

  //
  // MMIO is no longer needed so free it up
  //
  SciDisableMmio(PciBaseAddress);

  //
  // Restore the original mapping
  //
  PciSegmentWrite32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, PciBarLo);
  PciSegmentWrite32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET + 4, PciBarHi);
  PciSegmentWrite16 (PciBaseAddress + PCI_PRIMARY_STATUS_OFFSET, PciStatus);

  return SciBootSts;
}

/**
  Notify SCI with BIOS boot complete message.

  @retval     BOOLEAN   TRUE if communication successful, else FALSE
**/
BOOLEAN
SciBiosBootComplete (
  VOID
  )
{
  UINT64                  PciBaseAddress;
  UINT32                  MmioBase;
  UINT32                  PciBarLo;
  UINT32                  PciBarHi;
  UINT16                  PciStatus;
  UINT32                  *MbDataPtr;
  SCI_BOOT_CMPL_COMMAND   MbCommand;
  SCI_BOOT_CMPL_RESPONSE  MbResponse;
  UINT16                  Index;
  BOOLEAN                 RetStatus;
  UINT32                  HostIntrMsk;
  UINT32                  HostIntrSts;

  RetStatus = FALSE;

  //
  // Enable the MMIO mapping
  //
  PciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                     DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_SCI,
                     PCI_FUNCTION_NUMBER_PCH_SCI,
                     R_SCI_CFG_DEVICE_ID
                     );

  if (PciSegmentRead16 (PciBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    return FALSE;
  }

  //
  // Keep the content as it is and not to overwrite
  //
  PciBarLo = PciSegmentRead32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET);
  PciBarHi = PciSegmentRead32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET + 4);
  PciStatus = PciSegmentRead16 (PciBaseAddress + PCI_PRIMARY_STATUS_OFFSET);

  MmioBase = PcdGet32 (PcdSiliconInitTempMemBaseAddr);
  SciEnableMmio(PciBaseAddress, MmioBase);

  //
  // Mask the interrupt prior to doorbell polling
  // Otherwise this causes unattended MSI and it locks up
  // the SideBand channels.
  //
  HostIntrMsk = MmioRead32 (MmioBase + R_SCI_MEM_HOST_INTR_MASK)
                            & (B_SCI_MEM_DRBLIN_INTR | B_SCI_MEM_DRBLOUT_INTR);
  MmioOr32 (MmioBase + R_SCI_MEM_HOST_INTR_MASK, (B_SCI_MEM_DRBLIN_INTR | B_SCI_MEM_DRBLOUT_INTR));

  //
  // Prepare the message and send through mailbox registers
  //
  if (!SciDoorbellInCheck(MmioBase)) {
    DEBUG ((DEBUG_INFO, "Doorbell In busy\n"));
    goto Done;
  }

  MbCommand.MbHeader.Version   = SCI_DIAG_INTERFACE_VERSION;
  MbCommand.MbHeader.Reserved1 = SCI_DIAG_INTERFACE_RESERVED;
  MbCommand.MbHeader.Flags     = 0x0F | SCI_FLAGS_BIT_EOP | SCI_FLAGS_BIT_SOP;
  MbCommand.MbHeader.Length    = (UINT8)(SCI_BOOT_COMMAND_LENGTH/4);  // Length of every 4-byte
  MbCommand.MbHeader.Reserved2 = 0xFF;
  MbCommand.MbHeader.SeqNum    = (UINT8)SciBiosCompleteSeq;
  MbCommand.MbHeader.HostAddr  = SCI_HOST_ADDRESS;
  MbCommand.MbHeader.SciAddr   = SCI_ADDRESS;
  MbCommand.MbHeader.Crc16     = 0xFFFF;  // Default value before CRC calculation
  MbCommand.MbHeader.Command   = SCI_BOOT_COMPLETE;

  // Calculate the CRC of whole message
  MbCommand.MbHeader.Crc16 = CalculateCrc16 ((UINT8*)&MbCommand, SCI_BOOT_COMMAND_LENGTH);

  // Move the message to SCI RX RAM
  MbDataPtr = (UINT32*)&MbCommand;
  for (Index = 0; Index < SCI_BOOT_COMMAND_LENGTH; Index+=4, MbDataPtr++) {
    MmioWrite32(MmioBase + R_SCI_MEM_MB_RAM_RX + Index , *MbDataPtr);
  }


  // Inform SCI that a new message is ready
  MmioWrite32(MmioBase + R_SCI_MEM_TLP_CNT, 1);  // 1 message only
  MmioWrite32(MmioBase + R_SCI_MEM_RX_PKT_LENGTH, (UINT32)MbCommand.MbHeader.Length);
  MmioOr32(MmioBase + R_SCI_MEM_DOORBELL_IN, B_SCI_MEM_DRBLIN_CHECK);

  // Check to see if SCI consume the message
  if (!SciDoorbellInCheck(MmioBase)) {
    DEBUG ((DEBUG_INFO, "Doorbell In time out\n"));
    goto Done;
  }

  // Prepare to receive response from SCI
  if (!SciDoorbellOutCheck(MmioBase)) {
    DEBUG ((DEBUG_INFO, "Doorbell Out time out\n"));
    goto Done;
  }

  // Copy the reponse message from SCI TX RAM
  MbDataPtr = (UINT32*)&MbResponse;
  for (Index = 0; Index < SCI_BOOT_RESPONSE_LENGTH; Index+=4, MbDataPtr++) {
    *MbDataPtr = MmioRead32(MmioBase + R_SCI_MEM_MB_RAM_TX + Index);
  }

  // Finish the transaction and clear Doorbell out bit
  MmioAnd32(MmioBase + R_SCI_MEM_DOORBELL_OUT, ~((UINT32)B_SCI_MEM_DRBLOUT_CHECK));

  // Confirm that the right message is received
  if (!SciVerifyResponse(&MbCommand, &MbResponse)) {
    DEBUG ((DEBUG_INFO, "Response verification failed!\n"));
    goto Done;
  }

  //
  // Interrupt status must be cleared before restoring the interrupt mask
  // The status register is write-1-to-clear.
  //
  HostIntrSts = MmioRead32 (MmioBase + R_SCI_MEM_HOST_INTR_STATUS);
  DEBUG ((DEBUG_INFO, "HostIntrSts = 0x%x\n", HostIntrSts));
  DEBUG ((DEBUG_INFO, "HostIntrMsk = 0x%x\n", HostIntrMsk));
  MmioWrite32 (MmioBase + R_SCI_MEM_HOST_INTR_STATUS, HostIntrSts);
  MmioWrite32 (MmioBase + R_SCI_MEM_HOST_INTR_MASK, HostIntrMsk);

  RetStatus = TRUE;

Done:
  //
  // Restore the original mapping
  //
  PciSegmentWrite32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, PciBarLo);
  PciSegmentWrite32 (PciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET + 4, PciBarHi);
  PciSegmentWrite16 (PciBaseAddress + PCI_PRIMARY_STATUS_OFFSET, PciStatus);
  PciSegmentOr16 (PciBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);

  return RetStatus;
}

/**
  Initialize SCI device.

  @param[in] SiPolicy             The SI Policy PPI instance

**/
VOID
SciInit (
  IN  SI_POLICY_PPI               *SiPolicy
  )
{
  EFI_STATUS          Status;
  PCH_GENERAL_CONFIG  *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);

  ASSERT_EFI_ERROR (Status);

  //
  // Return if fuse/soft strap disabled or PCI device not found
  //
  if ((!PmcIsSciSupported ()) || (!PchIsSciSupported ())) {
    DEBUG ((DEBUG_INFO, "Sci not supported\n"));
    return;
  }

  DEBUG ((DEBUG_INFO, "SciInit() Start\n"));

  ConfigureSciRegisters (SiPolicy);

  if (PchGeneralConfig->SciPinMuxEnable) {
    GpioEnableSci ();
  }

  //
  // If SCI is up and running, check for a specific value
  //
  if (SciBootCheck ()) {
    DEBUG ((DEBUG_INFO, "SCI FW boot successful\n"));
  } else {
    DEBUG ((DEBUG_INFO, "SCI FW boot failure\n"));
  }

  DEBUG ((DEBUG_INFO, "SciInit() End\n"));
}

