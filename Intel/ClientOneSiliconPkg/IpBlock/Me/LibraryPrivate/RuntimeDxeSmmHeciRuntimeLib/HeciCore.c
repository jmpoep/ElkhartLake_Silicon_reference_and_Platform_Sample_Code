/** @file
  HECI driver core for Runtime DXE and SMM phases.

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

#include "HeciRuntime.h"
#include <HeciContextLib.h>

extern BOOLEAN                     mAtRuntime;
extern HECI_RUNTIME_DEVICE_CONTEXT mHeciDeviceContext[HeciMax];

/**
  This function provides a standard way to verify the HECI cmd and MBAR regs
  in its PCI cfg space are setup properly and that the local mHeciContext
  variable matches this info.

  @param[in] HeciDev              HECI device to be accessed.

  @retval HeciMemBar              HECI Memory BAR.
                                  0 - invalid BAR value returned.
**/
EFI_PHYSICAL_ADDRESS
EFIAPI
CheckAndFixHeciForAccess (
  IN HECI_CONTEXT_DEVICE HeciDev
  )
{
  EFI_PHYSICAL_ADDRESS HeciSegmentBaseAddress;
  EFI_PHYSICAL_ADDRESS HeciBarAddress;

  ///
  /// Check if HECI_MBAR has changed
  ///
  HeciSegmentBaseAddress = mHeciDeviceContext[HeciDev].SegmentBaseAddress;

  ///
  /// Check for HECI PCI device availability
  ///
  if (HeciSegmentBaseAddress == 0 || PciSegmentRead16 (HeciSegmentBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    HeciBarAddress = (EFI_PHYSICAL_ADDRESS) GetHeciContextBar0 (HeciDev);
    if (HeciBarAddress != 0) {
      return ((EFI_PHYSICAL_ADDRESS) HeciBarAddress);
    }
    return 0;
  }

  HeciBarAddress = PciSegmentRead32 (HeciSegmentBaseAddress + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0;
  if ((PciSegmentRead32 (HeciSegmentBaseAddress + PCI_BASE_ADDRESSREG_OFFSET) & B_PCI_BAR_MEMORY_TYPE_MASK) == B_PCI_BAR_MEMORY_TYPE_64) {
    HeciBarAddress += LShiftU64 (PciSegmentRead32 (HeciSegmentBaseAddress + (PCI_BASE_ADDRESSREG_OFFSET + 4)), 32);
  }

  if (HeciBarAddress == 0) {
    return 0;
  }

  if (!mAtRuntime) {
    ///
    /// Enable HECI MSE
    ///
    if (IsCseVariableStorageDevice (HeciDev)) {
      PciSegmentOr8 (HeciSegmentBaseAddress + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER));
    } else {
      PciSegmentOr8 (HeciSegmentBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
    }
  }

  ///
  /// Update the BAR for this HECI device
  ///
  mHeciDeviceContext[HeciDev].Bar0Address = HeciBarAddress;

  return HeciBarAddress;
}

/**
  Function sends one message through the HECI circular buffer and waits
  for the corresponding ACK message with retry mechanism.

  @param[in] HeciDev              The HECI device to be accessed.
  @param[in][out] Message         Pointer to the message buffer.
  @param[in] Length               Length of the message in bytes.
  @param[in][out] RecLength       Length of the message response in bytes.
  @param[in] HostAddress          Address of the sending entity.
  @param[in] MeAddress            Address of the ME entity that should receive the message.

  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        Failed to initialize HECI
  @retval EFI_NOT_READY           HECI is not ready for communication
  @retval EFI_TIMEOUT             CSME failed to empty or fill the circular buffer
  @retval EFI_UNSUPPORTED         Current ME mode doesn't support send this message through this HECI
**/
EFI_STATUS
EFIAPI
HeciSendwAck (
  IN      HECI_DEVICE HeciDev,
  IN OUT  UINT32      *Message,
  IN      UINT32      Length,
  IN OUT  UINT32      *RecLength,
  IN      UINT8       HostAddress,
  IN      UINT8       MeAddress
  )
{
  EFI_STATUS           Status = EFI_SUCCESS;

  //
  // Send the message to CSE
  //
  Status = HeciSend (HeciDev, Message, Length, HostAddress, MeAddress);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Receive message from CSE
  //
  Status = HeciReceive (HeciDev, BLOCKING, Message, RecLength);

  return Status;
}

/**
  Reads a message from CSME through HECI.

  @param[in] HeciDev              The HECI device to be accessed.
  @param[in] Blocking             Used to determine if the read is BLOCKING or NON_BLOCKING.
  @param[in, out] MessageBody     Pointer to a buffer used to receive a message.
  @param[in, out] Length          Pointer to the length of the buffer on input and the length
                                  of the message on return. (in bytes)

  @retval EFI_SUCCESS             One message packet read.
  @retval EFI_DEVICE_ERROR        Failed to initialize HECI
  @retval EFI_NOT_READY           HECI is not ready for communication
  @retval EFI_TIMEOUT             Failed to receive a full message on time
  @retval EFI_NO_RESPONSE         No response from CSME
  @retval EFI_BUFFER_TOO_SMALL    The caller's buffer was not large enough
**/
EFI_STATUS
EFIAPI
HeciReceive (
  IN      HECI_DEVICE HeciDev,
  IN      UINT32      Blocking,
  IN OUT  UINT32      *MessageBody,
  IN OUT  UINT32      *Length
  )
{
  UINTN                MaxBuffer;
  UINTN                ReadSize;
  UINTN                Index;
  UINTN                StallCount;
  UINTN                MaxCount;
  UINTN                OverAllDelay;

  BOOLEAN              TimeOut;
  HECI_CONTEXT_DEVICE  HeciContextDev;
  HECI_MESSAGE_HEADER  MessageHeader;

  volatile UINT32                        *ReadBuffer;
  volatile HECI_CONTROL_STATUS_REGISTER  *HostControlReg;
  volatile HECI_CONTROL_STATUS_REGISTER  *MeControlReg;

  if (HeciDev > HECI_MAX_FUNC) {
    return EFI_INVALID_PARAMETER;
  }
  HeciContextDev = HECI_DEV_TO_CONTEXT_MAP (HeciDev);
  if (mAtRuntime) {
    if (!mHeciDeviceContext[HeciContextDev].RuntimeAccessible) {
      return EFI_UNSUPPORTED;
    }
  } else {
    CheckAndFixHeciForAccess (HeciContextDev);
  }
  HostControlReg =  (volatile HECI_CONTROL_STATUS_REGISTER *) (UINTN) (
                      mHeciDeviceContext[HeciContextDev].Bar0Address + H_CSR
                      );
  MeControlReg = (volatile HECI_CONTROL_STATUS_REGISTER *) (UINTN) (
                   mHeciDeviceContext[HeciContextDev].Bar0Address + ME_CSR_HA
                   );

  ReadBuffer = (UINT32 *) (UINTN) (mHeciDeviceContext[HeciContextDev].Bar0Address + ME_CB_RW);

  MaxBuffer = HostControlReg->Fields.CBDepth;
  ReadSize = 0;
  OverAllDelay = 0;
  TimeOut = FALSE;

  MaxCount = HECI_RECEIVE_TIMEOUT_MS;

  while (TRUE) {
    StallCount = 0;
    while ((HostControlReg->Fields.IntStatus == 0) && (MeControlReg->Fields.CBReadPointer == MeControlReg->Fields.CBWritePointer) && (StallCount < MaxCount)) {
      if (!Blocking) {
        return EFI_TIMEOUT;
      }
      MicroSecondDelay (STALL_1_MILLISECOND);
      StallCount += 1;
    }
    if (StallCount == MaxCount) {
      TimeOut = TRUE;
      break;
    }

    OverAllDelay += StallCount;  // in Millisec

    HostControlReg->Fields.Ready = 1;
    HostControlReg->Fields.IntEnable = 0;

    StallCount = 0;
    while ((MeControlReg->Fields.CBReadPointer == MeControlReg->Fields.CBWritePointer) && (StallCount < MaxCount)) {
      if (!Blocking) {
        return EFI_TIMEOUT;
      }
      MicroSecondDelay (STALL_1_MILLISECOND);
      StallCount += 1;
    }
    if (StallCount >= MaxCount) {
      TimeOut = TRUE;
      break;
    }

    OverAllDelay += StallCount;  // in Millisec

    MessageHeader.Data = *ReadBuffer;
    *Length = MessageHeader.Fields.Length;

    for (Index = 0; Index < (MessageHeader.Fields.Length + 3) / 4; Index++) {
      StallCount = 0;
      while ((MeControlReg->Fields.CBReadPointer == MeControlReg->Fields.CBWritePointer) && (StallCount < MaxCount)) {
        if (!Blocking) {
          return EFI_TIMEOUT;
        }
        MicroSecondDelay (STALL_1_MILLISECOND);
        StallCount += 1;
      }
      if (StallCount >= MaxCount) {
        TimeOut = TRUE;
        break;
      }
      OverAllDelay += StallCount;  // in Millisec
      MessageBody[Index + ReadSize] = *ReadBuffer;
    }

    HostControlReg->Fields.IntStatus = 1;
    HostControlReg->Fields.Ready = 1;
    HostControlReg->Fields.IntEnable = 1;
    HostControlReg->Fields.IntGenerate = 1;

    if (MessageHeader.Fields.MessageComplete == 1) {
      TimeOut = FALSE;
      break;
    } else {
      //
      // If this was a NON-BLOCKING message and it is a multipacket message, we need to change the
      // parameter to BLOCKING because it will take a non-zero value of time until a new packet appears
      //
      Blocking = BLOCKING;
      MicroSecondDelay (STALL_1_MILLISECOND);
      OverAllDelay += 1;
      ReadSize += Index;
      if (OverAllDelay >= MaxCount) {
        TimeOut = TRUE;
        break;
      }
    }
  }

  return ((TimeOut) ? EFI_TIMEOUT : EFI_SUCCESS);
}

/**
  Function sends one message (of any length) through the HECI circular buffer.

  @param[in] HeciDev              The HECI device to be accessed.
  @param[in] Message              Pointer to the message data to be sent.
  @param[in] Length               Length of the message in bytes.
  @param[in] HostAddress          The address of the host processor.
  @param[in] MeAddress            Address of the ME subsystem the message is being sent to.

  @retval EFI_SUCCESS             One message packet sent.
  @retval EFI_DEVICE_ERROR        Failed to initialize HECI
  @retval EFI_NOT_READY           HECI is not ready for communication
  @retval EFI_TIMEOUT             CSME failed to empty the circular buffer
  @retval EFI_UNSUPPORTED         Current ME mode doesn't support send this message through this HECI
**/
EFI_STATUS
EFIAPI
HeciSend (
  IN HECI_DEVICE               HeciDev,
  IN UINT32                    *Message,
  IN UINT32                    Length,
  IN UINT8                     HostAddress,
  IN UINT8                     MeAddress
  )
{
  UINTN                LeftSize;
  UINTN                MaxBuffer;
  UINTN                WriteSize;
  UINTN                Size;
  UINTN                Index;
  UINTN                StallCount;
  UINTN                MaxCount;
  UINTN                OverAllDelay;

  BOOLEAN              TimeOut;
  HECI_CONTEXT_DEVICE  HeciContextDev;
  HECI_MESSAGE_HEADER  MessageHeader;

  volatile UINT32                           *WriteBuffer;
  volatile HECI_CONTROL_STATUS_REGISTER     *HostControlReg;
  volatile HECI_CONTROL_STATUS_REGISTER     *MeControlReg;

  if (HeciDev > HECI_MAX_FUNC) {
    return EFI_INVALID_PARAMETER;
  }
  HeciContextDev = HECI_DEV_TO_CONTEXT_MAP (HeciDev);
  if (mAtRuntime) {
    if (!mHeciDeviceContext[HeciContextDev].RuntimeAccessible) {
      return EFI_UNSUPPORTED;
    }
  } else {
    CheckAndFixHeciForAccess (HeciContextDev);
  }
  HostControlReg =  (volatile HECI_CONTROL_STATUS_REGISTER *) (UINTN) (
                      mHeciDeviceContext[HeciContextDev].Bar0Address + H_CSR
                      );
  MeControlReg = (volatile HECI_CONTROL_STATUS_REGISTER *) (UINTN) (
                   mHeciDeviceContext[HeciContextDev].Bar0Address + ME_CSR_HA
                   );

  WriteBuffer = (UINT32 *) (UINTN) (mHeciDeviceContext[HeciContextDev].Bar0Address + H_CB_WW);

  MaxBuffer = HostControlReg->Fields.CBDepth;
  OverAllDelay = 0;
  TimeOut = FALSE;

  MaxCount = HECI_SEND_TIMEOUT_MS;

  //
  // The first DWORD is used for send MessageHeader, so usable buffer size should Be MaxBuffer-1;
  //
  MaxBuffer -= 1;
  LeftSize = (Length + 3) / 4;
  WriteSize = 0;
  HostControlReg->Fields.Ready = 1;

  while (LeftSize > 0) {
    StallCount = 0;
    while ((MeControlReg->Fields.Ready == 0) && (StallCount < MaxCount)) {
      MicroSecondDelay (STALL_1_MILLISECOND);
      StallCount += 1;
    }
    if (StallCount == MaxCount) {
      TimeOut = TRUE;
      break;
    }

    HostControlReg->Fields.Ready = 1;
    HostControlReg->Fields.IntEnable = 0;

    Size = (LeftSize > MaxBuffer) ? MaxBuffer : LeftSize;
    LeftSize -= Size;

    //
    // Prepare message header
    //
    MessageHeader.Data = 0;
    MessageHeader.Fields.MeAddress = MeAddress;
    MessageHeader.Fields.HostAddress = HostAddress;
    MessageHeader.Fields.MessageComplete = (LeftSize > 0) ? 0 : 1;
    MessageHeader.Fields.Length = (UINT32)((LeftSize > 0) ? Size * sizeof (UINT32) : Length - WriteSize * sizeof (UINT32));

    //
    // Wait for the Circular buffer Empty.
    // When H_CBRP == H_CBWP, then Host side circular buffer is empty, and allowed to write into it.
    //
    StallCount = 0;
    while ((HostControlReg->Fields.CBReadPointer != HostControlReg->Fields.CBWritePointer) && (StallCount < MaxCount)) {
      MicroSecondDelay (STALL_1_MILLISECOND);
      StallCount += 1;
    }
    if (StallCount == MaxCount) {
      TimeOut = TRUE;
      break;
    }
    *WriteBuffer = MessageHeader.Data;
    for (Index = 0; Index < Size; Index++) {
      *WriteBuffer = Message[Index + WriteSize];
    }

    //
    // Send the Interrupt;
    //
    HostControlReg->Fields.IntStatus = 1;
    HostControlReg->Fields.Ready = 1;
    HostControlReg->Fields.IntEnable = 1;
    HostControlReg->Fields.IntGenerate = 1;

    WriteSize += Size;
    if (LeftSize > 0) {
      StallCount = 0;
      while ((HostControlReg->Fields.IntStatus == 0) && (StallCount < MaxCount)) {
        MicroSecondDelay (STALL_1_MILLISECOND);
        StallCount += 1;
      }
      if (StallCount == MaxCount)  {
        TimeOut = TRUE;
        break;
      }
    }
  }

  return ((TimeOut) ? EFI_TIMEOUT : EFI_SUCCESS);
}

/**
  Function forces a reinit of the heci interface by following the reset heci interface via host algorithm
  in HPS section 4.1.1.1

  @param[in] HeciDev              The HECI device to be accessed.

  @retval EFI_SUCCESS             Interface reset successful
  @retval EFI_TIMEOUT             ME is not ready
**/
EFI_STATUS
EFIAPI
ResetHeciInterface (
  IN  HECI_DEVICE              HeciDev
  )
{
  HECI_CONTROL_STATUS_REGISTER HeciCsrHost;
  HECI_CONTROL_STATUS_REGISTER HeciCsrMeHra;
  HECI_CONTEXT_DEVICE          HeciContextDev;
  UINTN                        HeciMemBar;
  UINT32                       StallCount;

  if (HeciDev > HECI_MAX_FUNC) {
    return EFI_INVALID_PARAMETER;
  }
  HeciContextDev = HECI_DEV_TO_CONTEXT_MAP (HeciDev);
  if (mAtRuntime) {
    if (!mHeciDeviceContext[HeciContextDev].RuntimeAccessible) {
      return EFI_UNSUPPORTED;
    }
  } else {
    CheckAndFixHeciForAccess (HeciContextDev);
  }

  ///
  /// Make sure that HECI device BAR is correct and device is enabled.
  ///
  HeciMemBar = (UINTN) mHeciDeviceContext[HeciContextDev].Bar0Address;
  if (HeciMemBar == 0) {
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Enable Reset
  ///
  HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);

  if (!HeciCsrHost.Fields.Reset) {
    HeciCsrHost.Fields.Reset       = 1;
    HeciCsrHost.Fields.IntGenerate = 1;
    MmioWrite32 (HeciMemBar + H_CSR, HeciCsrHost.Data);
  }

  ///
  /// Make sure that the reset started
  ///
  StallCount = 0;
  do {
    if (StallCount++ >= HECI_INIT_TIMEOUT_MS) {
      return EFI_TIMEOUT;
    }
    HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
    MicroSecondDelay (STALL_1_MILLISECOND);
  } while (HeciCsrHost.Fields.Ready == 1);

  ///
  /// Wait for ME to perform reset
  ///
  HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
  do {
    if (StallCount++ >= HECI_INIT_TIMEOUT_MS) {
      return EFI_TIMEOUT;
    }
    HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
    MicroSecondDelay (STALL_1_MILLISECOND);
  } while (HeciCsrMeHra.Fields.Ready == 0);

  ///
  /// Enable host side interface. Host SW writes the value read back to the H_CSR register.
  /// This clears the H_IS and bit in H_CSR to 0
  ///
  HeciCsrHost.Data               = MmioRead32 (HeciMemBar + H_CSR);
  HeciCsrHost.Fields.Reset       = 0;
  HeciCsrHost.Fields.IntGenerate = 1;
  HeciCsrHost.Fields.Ready       = 1;
  MmioWrite32 (HeciMemBar + H_CSR, HeciCsrHost.Data);

  return EFI_SUCCESS;
}

/**
  Determines if the HECI device is present.
  If present, initializes it to be used by the BIOS.

  @param[in] HeciDev              The HECI device to be accessed.

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_DEVICE_ERROR        No HECI device
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_UNSUPPORTED         HECI MSG is unsupported
**/
EFI_STATUS
EFIAPI
HeciInitialize (
  IN HECI_DEVICE                      HeciDev
  )
{
  HECI_CONTROL_STATUS_REGISTER          HeciRegHCsr;
  volatile HECI_CONTROL_STATUS_REGISTER *HeciRegHCsrPtr;
  HECI_FWS_REGISTER                     MeFirmwareStatus;
  HECI_CONTEXT_DEVICE                   HeciContextDev;

  if (HeciDev > HECI_MAX_FUNC) {
    return EFI_INVALID_PARAMETER;
  }
  HeciContextDev = HECI_DEV_TO_CONTEXT_MAP (HeciDev);
  if (mAtRuntime) {
    if (!mHeciDeviceContext[Heci1].RuntimeAccessible || !mHeciDeviceContext[HeciContextDev].RuntimeAccessible) {
      return EFI_UNSUPPORTED;
    }
  } else {
    CheckAndFixHeciForAccess (HeciContextDev);
  }
  if (mHeciDeviceContext[Heci1].BaseAddress == 0 || mHeciDeviceContext[HeciContextDev].Bar0Address == 0) {
    return EFI_NOT_FOUND;
  }

  HeciRegHCsrPtr = (VOID *) (UINTN) (mHeciDeviceContext[HeciContextDev].Bar0Address + H_CSR);
  HeciRegHCsr.Data = HeciRegHCsrPtr->Data;

  //
  // Read Ready bit to check if we're already initialized
  //
  if (HeciRegHCsr.Fields.Ready == 1) {
    return EFI_SUCCESS;
  }
  MeFirmwareStatus.ul = MmioRead32 (mHeciDeviceContext[Heci1].BaseAddress + R_ME_HFS);
  if (MeFirmwareStatus.ul == 0 || MeFirmwareStatus.ul == 0xFFFFFFFF) {
    return EFI_DEVICE_ERROR;
  }
  //
  // Check for CSE FW status and proceed only if CSE is in normal mode
  //

  if ((MeFirmwareStatus.r.FwUpdateInprogress != 0) ||
    (MeFirmwareStatus.r.FptBad != 0) ||
    (MeFirmwareStatus.r.ErrorCode != ME_ERROR_CODE_NO_ERROR) ||
    (MeFirmwareStatus.r.MeOperationMode == ME_OPERATION_MODE_SECOVR_JMPR) ||
    (MeFirmwareStatus.r.MeOperationMode == ME_ERROR_CODE_DISABLED)
    )
  {
    return EFI_UNSUPPORTED;
  }

  ///
  /// Set HECI interrupt delivery mode.
  /// HECI-1 using legacy/MSI interrupt
  ///
  MmioAnd8 (mHeciDeviceContext[HeciContextDev].BaseAddress + R_ME_HIDM, 0xFC);

  HeciRegHCsr.Data = HeciRegHCsrPtr->Data;
  if (HeciRegHCsrPtr->Fields.Ready == 0) {
    HeciRegHCsr.Fields.Reset = 0;
    HeciRegHCsr.Fields.Ready = 1;
    HeciRegHCsr.Fields.IntGenerate = 1;
    HeciRegHCsrPtr->Data = HeciRegHCsr.Data;
  }

  return EFI_SUCCESS;
}

/**
  Heci Re-initialization for Host

  @param[in] HeciDev              The HECI device to be accessed.

  @retval EFI_SUCCESS             Heci Re-initialization successful
  @retval EFI_TIMEOUT             ME is not ready
  @retval EFI_DEVICE_ERROR        Failed to initialize HECI
**/
EFI_STATUS
EFIAPI
HeciReInitialize (
  IN HECI_DEVICE                  HeciDev
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Me reset and waiting for ready

  @param[in] HeciDev              The HECI device to be accessed.
  @param[in] Delay                The biggest waiting time

  @retval EFI_SUCCESS             Host Ready bit cleared
  @retval EFI_TIMEOUT             Host Ready bit not cleared
  @retval EFI_DEVICE_ERROR        Failed to initialize HECI
**/
EFI_STATUS
EFIAPI
MeResetWait (
  IN  HECI_DEVICE              HeciDev,
  IN  UINT32                   Delay
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Get an abstract Intel HECI1 State from Firmware Status Register.
  This is used to control BIOS flow for different Intel ME functions.

  @param[out] MeStatus            Pointer for status report
                                    @see MeState.h - Abstract ME status definitions.

  @retval EFI_SUCCESS             MeStatus copied
  @retval EFI_INVALID_PARAMETER   Pointer to MeStatus is invalid
  @retval EFI_NOT_FOUND           HECI1 Device hidden
**/
EFI_STATUS
EFIAPI
HeciGetMeStatus (
  OUT UINT32        *MeStatus
  )
{
  HECI_FWS_REGISTER MeFirmwareStatus;

  if (MeStatus == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (mAtRuntime && !mHeciDeviceContext[Heci1].RuntimeAccessible) {
    return EFI_NOT_FOUND;
  } else if (mHeciDeviceContext[Heci1].BaseAddress == 0) {
    return EFI_NOT_FOUND;
  }

  MeFirmwareStatus.ul = MmioRead32 (mHeciDeviceContext[Heci1].BaseAddress + R_ME_HFS);

  if (MeFirmwareStatus.r.CurrentState == ME_STATE_NORMAL && MeFirmwareStatus.r.ErrorCode == ME_ERROR_CODE_NO_ERROR) {
    *MeStatus = ME_READY;
  } else if (MeFirmwareStatus.r.CurrentState == ME_STATE_RECOVERY) {
    *MeStatus = ME_IN_RECOVERY_MODE;
  } else if (MeFirmwareStatus.r.CurrentState == ME_STATE_INIT) {
    *MeStatus = ME_INITIALIZING;
  } else if (MeFirmwareStatus.r.CurrentState == ME_STATE_DISABLE_WAIT) {
    *MeStatus = ME_DISABLE_WAIT;
  } else if (MeFirmwareStatus.r.CurrentState == ME_STATE_TRANSITION) {
    *MeStatus = ME_TRANSITION;
  } else {
    *MeStatus = ME_NOT_READY;
  }

  if (MeFirmwareStatus.r.FwUpdateInprogress) {
    *MeStatus |= ME_FW_UPDATES_IN_PROGRESS;
  }

  if (MeFirmwareStatus.r.FwInitComplete == ME_FIRMWARE_COMPLETED) {
    *MeStatus |= ME_FW_INIT_COMPLETE;
  }

  if (MeFirmwareStatus.r.MeBootOptionsPresent == ME_BOOT_OPTIONS_PRESENT) {
    *MeStatus |= ME_FW_BOOT_OPTIONS_PRESENT;
  }

  return EFI_SUCCESS;
}

/**
  Get HECI1 Mode

  @param[out] MeMode              Pointer for HECI1 Mode report
                                    @see MeState.h - Abstract ME Mode definitions.

  @retval EFI_SUCCESS             MeMode copied
  @retval EFI_INVALID_PARAMETER   Pointer to MeMode is invalid
  @retval EFI_NOT_FOUND           HECI1 Device hidden
**/
EFI_STATUS
EFIAPI
HeciGetMeMode (
  OUT UINT32        *MeMode
  )
{
  HECI_FWS_REGISTER MeFirmwareStatus;

  if (MeMode == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (mAtRuntime && !mHeciDeviceContext[Heci1].RuntimeAccessible) {
    return EFI_NOT_FOUND;
  } else if (mHeciDeviceContext[Heci1].BaseAddress == 0) {
    return EFI_NOT_FOUND;
  }

  MeFirmwareStatus.ul = MmioRead32 (mHeciDeviceContext[Heci1].BaseAddress + R_ME_HFS);
    switch (MeFirmwareStatus.r.MeOperationMode) {
      case ME_OPERATION_MODE_NORMAL:
        *MeMode = ME_MODE_NORMAL;
        break;

      case ME_OPERATION_MODE_DEBUG:
        *MeMode = ME_MODE_DEBUG;
        break;

      case ME_OPERATION_MODE_SOFT_TEMP_DISABLE:
        *MeMode = ME_MODE_TEMP_DISABLED;
        break;

      case ME_OPERATION_MODE_SECOVR_JMPR:
      case ME_OPERATION_MODE_SECOVR_HECI_MSG:
        *MeMode = ME_MODE_SECOVER;
        break;

      case ME_OPERATION_MODE_SPS:
        *MeMode = ME_MODE_SPS;
        break;

      default:
        *MeMode = ME_MODE_FAILED;
    }

  return EFI_SUCCESS;
}

/**
  Initialize's HECI device context that may be used through OS runtime.

**/
VOID
EFIAPI
InitializeHeciDeviceContext (
  VOID
  )
{
  UINT32        DeviceIndex;

  for (DeviceIndex = Heci1; DeviceIndex < HeciMax; DeviceIndex++) {
    mHeciDeviceContext[DeviceIndex].SegmentBaseAddress =  PCI_SEGMENT_LIB_ADDRESS (
                                                            ME_SEGMENT,
                                                            ME_BUS,
                                                            ME_DEVICE_NUMBER,
                                                            HECI_FUNCTION_NUMBER + HECI_CONTEXT_TO_DEV_MAP (DeviceIndex),
                                                            0
                                                            );
    if (mHeciDeviceContext[DeviceIndex].SegmentBaseAddress != 0) {
      mHeciDeviceContext[DeviceIndex].BaseAddress = mHeciDeviceContext[DeviceIndex].SegmentBaseAddress +
                                                      (UINTN) PcdGet64 (PcdPciExpressBaseAddress);
    }
    mHeciDeviceContext[DeviceIndex].Bar0Address = CheckAndFixHeciForAccess (
                                                    DeviceIndex
                                                    );
    mHeciDeviceContext[DeviceIndex].Bar0Address &= 0xFFFFFFF0;
    if (mHeciDeviceContext[DeviceIndex].Bar0Address == 0) {
      DEBUG ((DEBUG_WARN, "HECI%d BAR is unavailable.\n", (DeviceIndex + 1)));
    }

    ///
    /// Determines if the HECI device is configured for Runtime DXE access after Exit Boot Services.
    /// In general, HECI1 should always be enabled if another device is to allow ME mode and status checks.
    ///
    mHeciDeviceContext[DeviceIndex].RuntimeAccessible = IsCseVariableStorageDevice (HECI_CONTEXT_TO_DEV_MAP (DeviceIndex));

    DEBUG ((DEBUG_INFO, "HECI Device Initial Context:\n"));
    DEBUG ((DEBUG_INFO, "  Device: HECI%d.\n", (DeviceIndex + 1)));
    DEBUG ((DEBUG_INFO, "  Base Address: 0x%x.\n", mHeciDeviceContext[DeviceIndex].BaseAddress));
    DEBUG ((DEBUG_INFO, "  BAR Address: 0x%x.\n", mHeciDeviceContext[DeviceIndex].Bar0Address));
    DEBUG ((
      DEBUG_INFO,
      "  Runtime Accessible: %a.\n",
      ((mHeciDeviceContext[DeviceIndex].RuntimeAccessible) ? "True" : "False")
      ));
  }
}
