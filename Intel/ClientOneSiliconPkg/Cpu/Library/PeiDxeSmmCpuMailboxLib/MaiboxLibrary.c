/** @file
  Mailbox Library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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
#include "MaiboxLibrary.h"

/**
  Generic Mailbox function for mailbox write commands. This function will
  poll the mailbox interface for control, issue the write request, poll
  for completion, and verify the write was succussful.

  @param[in]  MailboxType
  @param[in]  MailboxCommand
  @param[in]  MailboxData
  @param[out] *MailboxStatus

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
MailboxWrite (
  IN UINT32  MailboxType,
  IN UINT32  MailboxCommand,
  IN UINT32  MailboxData,
  OUT UINT32 *MailboxStatus
  )
{
  EFI_STATUS         Status;
  UINT64             MsrData;
  UINT32             MchBar;
  OC_MAILBOX_FULL    OcMailboxFull;
  OC_MAILBOX_FULL    OcMailboxFullVerify;
  PCODE_MAILBOX_FULL PcodeMailboxFull;
  PCODE_MAILBOX_FULL PcodeMailboxFullVerify;

  ///
  ///  Poll the run/busy to ensure the interface is available
  ///
  Status = PollMailboxReady (MailboxType);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = %Xh\n", MailboxCommand));
  DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Data    = %Xh\n", MailboxData));

  switch (MailboxType) {
    case MAILBOX_TYPE_PCODE:
      ///
      /// Copy in Mailbox data and write the PCODE mailbox DATA field
      ///
      PcodeMailboxFull.Interface.InterfaceData = MailboxCommand;
      PcodeMailboxFull.Data = MailboxData;
      MchBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MCHBAR)) & ~BIT0;

      MmioWrite32 ((MchBar + PCODE_MAILBOX_DATA_OFFSET), PcodeMailboxFull.Data);

      ///
      /// Set the Run/Busy bit to signal mailbox data is ready to process
      ///
      PcodeMailboxFull.Interface.Fields.RunBusy = 1;
      MmioWrite32 ((MchBar + PCODE_MAILBOX_INTERFACE_OFFSET), PcodeMailboxFull.Interface.InterfaceData);

      ///
      /// Poll run/busy to indicate the completion of write request
      ///
      PollMailboxReady (MailboxType);

      ///
      /// Read the BIOS PCODE mailbox to verify write completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      ///
      PcodeMailboxFull.Interface.InterfaceData = MmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFull.Data = MmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

      MicroSecondDelay (MAILBOX_READ_TIMEOUT);

      ///
      /// Read twice to verify data is consitent
      ///
      PcodeMailboxFullVerify.Interface.InterfaceData = MmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFullVerify.Data = MmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (PcodeMailboxFull.Interface.InterfaceData != PcodeMailboxFullVerify.Interface.InterfaceData) {
        if (PcodeMailboxFull.Data  != PcodeMailboxFullVerify.Data) {
          DEBUG ((DEBUG_ERROR, "(MAILBOX) Mailbox read data is corrupted.\n"));
          return EFI_INVALID_PARAMETER;
        }
      }

      ///
      ///  Copy PCODE mailbox completion code
      ///
      *MailboxStatus = (UINT32) PcodeMailboxFull.Interface.Fields.Command;
      break;

    case MAILBOX_TYPE_OC:
      ///
      /// Set the Run/Busy bit to signal mailbox data is ready to process
      ///
      OcMailboxFull.Interface.InterfaceData = MailboxCommand;
      OcMailboxFull.Data = MailboxData;
      OcMailboxFull.Interface.Fields.RunBusy = 1;
      CopyMem (&MsrData, &OcMailboxFull, sizeof (MsrData));

      ///
      /// Write mailbox command to OC mailbox
      ///
      AsmWriteMsr64 (OC_MAILBOX_MSR, MsrData);

      ///
      /// Poll run/busy to indicate the completion of write request
      ///
      PollMailboxReady (MailboxType);

      ///
      /// Read the mailbox command from OC mailbox. Read twice to ensure data.
      ///
      MsrData = AsmReadMsr64 (OC_MAILBOX_MSR);
      CopyMem (&OcMailboxFull, &MsrData, sizeof (OcMailboxFull));

      MicroSecondDelay (MAILBOX_READ_TIMEOUT);

      MsrData = AsmReadMsr64 (OC_MAILBOX_MSR);
      CopyMem (&OcMailboxFullVerify, &MsrData, sizeof (OcMailboxFullVerify));

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (OcMailboxFull.Interface.InterfaceData != OcMailboxFullVerify.Interface.InterfaceData) {
        if (OcMailboxFull.Data != OcMailboxFullVerify.Data) {
          DEBUG ((DEBUG_ERROR, "(MAILBOX) Mailbox read data is corrupted.\n"));
          return EFI_INVALID_PARAMETER;
        }
      }

      ///
      ///  Copy Overclocking mailbox completion code and read results
      ///
      *MailboxStatus = OcMailboxFull.Interface.Fields.CommandCompletion;
      break;

    case MAILBOX_TYPE_VR_MSR:
      ///
      /// Copy in Mailbox data and write the PCODE MSR mailbox DATA field
      ///
      PcodeMailboxFull.Interface.InterfaceData = MailboxCommand;
      PcodeMailboxFull.Interface.Fields.RunBusy = 1;
      PcodeMailboxFull.Data = MailboxData;

      ///
      /// Write mailbox command to VR mailbox
      ///
      AsmWriteMsr64 (VR_MAILBOX_MSR_DATA, (UINT64) PcodeMailboxFull.Data);
      AsmWriteMsr64 (VR_MAILBOX_MSR_INTERFACE, (UINT64) PcodeMailboxFull.Interface.InterfaceData);

      ///
      /// Poll run/busy to indicate the completion of write request
      ///
      PollMailboxReady (MailboxType);

      ///
      /// Read the mailbox command from VR MSR mailbox. Read twice to ensure data.
      ///
      MsrData = AsmReadMsr64 (VR_MAILBOX_MSR_INTERFACE);
      CopyMem (&PcodeMailboxFull, &MsrData, sizeof (PcodeMailboxFull));

      MicroSecondDelay (MAILBOX_READ_TIMEOUT);

      MsrData = AsmReadMsr64 (VR_MAILBOX_MSR_INTERFACE);
      CopyMem (&PcodeMailboxFullVerify, &MsrData, sizeof (PcodeMailboxFullVerify));

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (PcodeMailboxFull.Interface.InterfaceData != PcodeMailboxFullVerify.Interface.InterfaceData) {
        if (PcodeMailboxFull.Data != PcodeMailboxFullVerify.Data) {
          DEBUG ((DEBUG_ERROR, "(MAILBOX) Mailbox read data is corrupted.\n"));
          return EFI_INVALID_PARAMETER;
        }
      }

      ///
      ///  Copy Overclocking mailbox completion code and read results
      ///
      *MailboxStatus = PcodeMailboxFull.Interface.Fields.Command;
      break;

    default:
      DEBUG ((DEBUG_ERROR, "(MAILBOX) Unrecognized Mailbox Type.\n"));
      Status = EFI_UNSUPPORTED;
      break;
  }

  DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Status = %2Xh\n", *MailboxStatus));
  return Status;
}

/**
  Generic Mailbox function for mailbox read commands. This function will write
  the read request, and populate the read results in the output data.

  @param[in]  MailboxType
  @param[in]  MailboxCommand
  @param[out] *MailboxDataPtr
  @param[out] *MailboxStatus

  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
MailboxRead (
  IN UINT32  MailboxType,
  IN UINT32  MailboxCommand,
  OUT UINT32 *MailboxDataPtr,
  OUT UINT32 *MailboxStatus
  )
{
  EFI_STATUS         Status;
  UINT64             MsrData;
  UINT32             MchBar;
  PCODE_MAILBOX_FULL PcodeMailboxFull;
  PCODE_MAILBOX_FULL PcodeMailboxFullVerify;
  OC_MAILBOX_FULL    OcMailboxFull;
  OC_MAILBOX_FULL    OcMailboxFullVerify;

  ///
  ///  Poll the run/busy to ensure the interface is available
  ///
  Status = PollMailboxReady (MailboxType);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Read Command = %Xh\n", MailboxCommand));

  switch (MailboxType) {
    case MAILBOX_TYPE_PCODE:
      ///
      /// Write the PCODE mailbox read request.
      /// Read requests only require a write to the PCODE interface mailbox.
      /// The read results will be updated in the data mailbox.
      ///
      PcodeMailboxFull.Interface.InterfaceData = MailboxCommand;
      PcodeMailboxFull.Interface.Fields.RunBusy = 1;
      MchBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MCHBAR)) & ~BIT0;

      MmioWrite32 ((MchBar + PCODE_MAILBOX_INTERFACE_OFFSET), PcodeMailboxFull.Interface.InterfaceData);

      ///
      /// Poll run/busy to indicate the completion of read request
      ///
      PollMailboxReady (MailboxType);

      ///
      /// Read the BIOS PCODE mailbox to verify read completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      ///
      PcodeMailboxFull.Interface.InterfaceData = MmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFull.Data = MmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

      MicroSecondDelay (MAILBOX_READ_TIMEOUT);

      ///
      /// Read twice to verify data is consitent
      ///
      PcodeMailboxFullVerify.Interface.InterfaceData = MmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFullVerify.Data = MmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (PcodeMailboxFull.Interface.InterfaceData != PcodeMailboxFullVerify.Interface.InterfaceData) {
        if (PcodeMailboxFull.Data  != PcodeMailboxFullVerify.Data) {
          DEBUG ((DEBUG_ERROR, "(MAILBOX) Mailbox read data is corrupted.\n"));
          return EFI_INVALID_PARAMETER;
        }
      }

      ///
      ///  Copy PCODE mailbox completion code and read results
      ///
      *MailboxStatus = (UINT32) PcodeMailboxFull.Interface.InterfaceData;
      CopyMem (MailboxDataPtr, &PcodeMailboxFull.Data, sizeof (UINT32));
      break;

    case MAILBOX_TYPE_OC:
      ///
      /// Set the Run/Busy bit to signal mailbox data is ready to process
      ///
      OcMailboxFull.Interface.InterfaceData = MailboxCommand;
      OcMailboxFull.Data = *MailboxDataPtr;
      OcMailboxFull.Interface.Fields.RunBusy = 1;
      CopyMem (&MsrData, &OcMailboxFull, sizeof (MsrData));

      ///
      /// Write mailbox command to OC mailbox
      ///
      AsmWriteMsr64 (OC_MAILBOX_MSR, MsrData);

      ///
      /// Poll run/busy to indicate the completion of write request
      ///
      PollMailboxReady (MailboxType);

      ///
      /// Read the OC mailbox to verify read completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      ///
      MsrData = AsmReadMsr64 (OC_MAILBOX_MSR);
      CopyMem (&OcMailboxFull, &MsrData, sizeof (OcMailboxFull));

      MicroSecondDelay (MAILBOX_READ_TIMEOUT);

      MsrData = AsmReadMsr64 (OC_MAILBOX_MSR);
      CopyMem (&OcMailboxFullVerify, &MsrData, sizeof (OcMailboxFullVerify));

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (OcMailboxFull.Interface.InterfaceData != OcMailboxFullVerify.Interface.InterfaceData) {
        if (OcMailboxFull.Data != OcMailboxFullVerify.Data) {
          DEBUG ((DEBUG_ERROR, "(MAILBOX) Mailbox read data is corrupted.\n"));
          return EFI_INVALID_PARAMETER;
        }
      }

      ///
      ///  Copy Overclocking mailbox completion code and read results
      ///
      *MailboxStatus = OcMailboxFull.Interface.Fields.CommandCompletion;
      CopyMem (MailboxDataPtr, &OcMailboxFull.Data, sizeof (UINT32));
      break;

    case MAILBOX_TYPE_VR_MSR:
      ///
      /// Set the Run/Busy bit to signal mailbox data is ready to process
      ///
      PcodeMailboxFull.Interface.InterfaceData = MailboxCommand;
      PcodeMailboxFull.Data = *MailboxDataPtr;
      PcodeMailboxFull.Interface.Fields.RunBusy = 1;

      ///
      /// Write mailbox command to VR MSR mailbox
      ///
      AsmWriteMsr64 (VR_MAILBOX_MSR_INTERFACE, (UINT64) PcodeMailboxFull.Interface.InterfaceData);

      ///
      /// Poll run/busy to indicate the completion of write request
      ///
      PollMailboxReady (MailboxType);

      ///
      /// Read the VR MSR mailbox to verify read completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      ///
      MsrData = AsmReadMsr64 (VR_MAILBOX_MSR_INTERFACE);
      CopyMem (&PcodeMailboxFull.Interface.InterfaceData, &MsrData, sizeof (PcodeMailboxFull.Interface));
      MsrData = AsmReadMsr64 (VR_MAILBOX_MSR_DATA);
      CopyMem (&PcodeMailboxFull.Data, &MsrData, sizeof (PcodeMailboxFull.Data));


      MicroSecondDelay (MAILBOX_READ_TIMEOUT);

      MsrData = AsmReadMsr64 (VR_MAILBOX_MSR_INTERFACE);
      CopyMem (&PcodeMailboxFullVerify.Interface.InterfaceData, &MsrData, sizeof (PcodeMailboxFull.Interface));
      MsrData = AsmReadMsr64 (VR_MAILBOX_MSR_DATA);
      CopyMem (&PcodeMailboxFullVerify.Data, &MsrData, sizeof (PcodeMailboxFull.Data));

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (PcodeMailboxFull.Interface.InterfaceData != PcodeMailboxFullVerify.Interface.InterfaceData) {
        if (PcodeMailboxFull.Data != PcodeMailboxFullVerify.Data) {
          DEBUG ((DEBUG_ERROR, "(MAILBOX) Mailbox read data is corrupted.\n"));
          return EFI_INVALID_PARAMETER;
        }
      }

      ///
      ///  Copy VR MSR mailbox completion code and read results
      ///
      *MailboxStatus = PcodeMailboxFull.Interface.Fields.Command;
      CopyMem (MailboxDataPtr, &PcodeMailboxFull.Data, sizeof (UINT32));
      break;

    default:
      DEBUG ((DEBUG_ERROR, "(MAILBOX) Unrecognized Mailbox Type.\n"));
      Status = EFI_UNSUPPORTED;
      break;
  }

  DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Status = %2Xh\n", *MailboxStatus));

  return Status;
}

/**
  Poll the run/busy bit of the mailbox until available or timeout expires.

  @param[in]  MailboxType

  @retval EFI_STATUS
          - EFI_SUCCESS           Command succeeded.
          - EFI_TIMEOUT           Command timeout.
**/
EFI_STATUS
EFIAPI
PollMailboxReady (
  IN UINT32 MailboxType
  )
{
  EFI_STATUS              Status;
  UINT16                  StallCount;
  UINT8                   RunBusyBit;
  UINT64                  MsrData;
  UINT32                  MchBar;
  OC_MAILBOX_FULL         OcMailboxFull;
  PCODE_MAILBOX_INTERFACE PcodeMailboxInterface;
  PCODE_MAILBOX_FULL      PcodeMailboxFull;

  Status = EFI_SUCCESS;
  StallCount = 0;
  RunBusyBit = 1;

  do {
    switch (MailboxType) {
      case MAILBOX_TYPE_PCODE:
        ///
        /// Read the MMIO run/busy state
        ///
        MchBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MCHBAR)) & ~BIT0;
        PcodeMailboxInterface.InterfaceData = MmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
        RunBusyBit = (UINT8) PcodeMailboxInterface.Fields.RunBusy;
        break;

      case MAILBOX_TYPE_OC:
        ///
        /// Read the OC mailbox run/busy state
        ///
        MsrData = AsmReadMsr64 (OC_MAILBOX_MSR);
        CopyMem (&OcMailboxFull.Data, &MsrData, sizeof (OcMailboxFull));
        RunBusyBit = OcMailboxFull.Interface.Fields.RunBusy;
        break;

      case MAILBOX_TYPE_VR_MSR:
        ///
        /// Read the VR mailbox run/busy state
        ///
        MsrData = AsmReadMsr64 (VR_MAILBOX_MSR_INTERFACE);
        CopyMem (&PcodeMailboxFull.Interface.InterfaceData, &MsrData, sizeof (PcodeMailboxFull));
        RunBusyBit = (UINT8) PcodeMailboxFull.Interface.Fields.RunBusy;
        break;

      default:
        break;
    }
    //
    // Wait for 1us
    //
    MicroSecondDelay (MAILBOX_WAIT_STALL);
    StallCount++;
  }
  while ((RunBusyBit == 1) && (StallCount < MAILBOX_WAIT_TIMEOUT));

  if ((RunBusyBit == 1) && (StallCount == MAILBOX_WAIT_TIMEOUT)) {
    DEBUG ((DEBUG_ERROR, "(MAILBOX) Mailbox interface timed out.\n"));
    Status = EFI_TIMEOUT;
  }
  return Status;
}
