/** @file
  Heci driver core for PEI & DXE phases, determines the HECI device and
  initializes it.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2007 - 2019 Intel Corporation.

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

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BootMediaLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MeShowBufferLib.h>
#include <Library/ReportStatusCodeLib.h>
#include "HeciCore.h"
#include "HeciHpet.h"
#include <BupMsgs.h>
#include <MeState.h>
#include <Register/HeciRegs.h>
#include <Library/PciSegmentLib.h>
#if FixedPcdGetBool(PcdBfxEnable) == 1
#include <Library/CseVariableStorageStatusLib.h>
#include <HeciContextLib.h>
#endif
#include <Library/HeciInitLib.h>
#include <Protocol/HeciProtocol.h>
#include <PcieRegs.h>

/**
  Checks ME Boot path. The function provides ME BIOS boot path based on current
  HECI1 FW Status Register.  HECI1 must be enabled before invoking the function.
  The FW registers may report multiple statuses to reflect Me Bios boot path,
  BIOS will follow the prioritized Me Bios boot path to continue boot.
  If the priority changes, then BOOT_PATH enumerated type shall be
  adjusted as well to reflect the actual priority.

  @retval ME_BIOS_BOOT_PATH       Me-Bios Path taken based on FWSTS registers
                                    @see ME_BIOS_BOOT_PATH - for available paths
**/
ME_BIOS_BOOT_PATH
CheckMeBootPath (
  VOID
  )
{
  HECI_FWS_REGISTER     Hfsts1;
  HECI_FW_STS4_REGISTER Hfsts4;

  Hfsts1.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS));
  Hfsts4.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS_4));

  DEBUG ((DEBUG_INFO, "HECI1 Hfsts1 = %X, Hfsts4 = %x \n", Hfsts1.ul, Hfsts4.ul));

  if (Hfsts1.r.ErrorCode == ME_ERROR_CODE_NO_ERROR && Hfsts1.r.MeOperationMode == ME_OPERATION_MODE_SPS) {
    return (Hfsts1.r.CurrentState > ME_STATE_RECOVERY) ? SpsPath : SpsRcvPath;
  }

  if (Hfsts4.r.FwInEnfFlow == 0x01) {
    return EnforcementWithoutDidMsgPath;
  }

  if (Hfsts1.r.MeOperationMode == ME_OPERATION_MODE_DEBUG) {
    return DebugModePath;
  } else if (Hfsts1.r.MeOperationMode == ME_OPERATION_MODE_SECOVR_JMPR) {
    return SecoverJmprPath;
  } else if (Hfsts1.r.MeOperationMode == ME_OPERATION_MODE_SOFT_TEMP_DISABLE) {
    return SwTempDisablePath;
  } else if (Hfsts1.r.MeOperationMode == ME_OPERATION_MODE_SECOVR_HECI_MSG) {
    return SecoverMeiMsgPath;
  }

  if (Hfsts1.r.ErrorCode == ME_ERROR_CODE_IMAGE_FAILURE) {
    return ErrorWithoutDidMsgPath;
  }

  if (Hfsts1.r.CurrentState == ME_STATE_RECOVERY) {
    return RecoveryPath;
  }

  if (Hfsts1.r.FptBad == 0x01 || Hfsts1.r.ErrorCode != ME_ERROR_CODE_NO_ERROR) {
    return ErrorPath;
  }

  return NormalPath;
}

/**
  Returns the mapping of CSME devices that need to be hidden.
  The mapping is based only on ME-Bios boot path taken. Additional devices
  might be hidden later based on other platform policies.

  @retval ME_DEV_EXPOSURE   Mapping of CSME devices to be hidden
                              @see ME_DEV_EXPOSURE for bit assignment
**/
ME_DEV_EXPOSURE
GetBootPathMeDevHidePolicy (
  VOID
  )
{
  ME_BIOS_BOOT_PATH MeBiosPath;
  ME_DEV_EXPOSURE   MeDevHidePolicy;

  MeBiosPath = CheckMeBootPath ();

  DEBUG ((DEBUG_INFO, "Current MeBiosBootPath - %d\n", MeBiosPath));

  switch (MeBiosPath) {
    case NormalPath:
      MeDevHidePolicy = 0;
      break;
    case SecoverMeiMsgPath:
    case SwTempDisablePath:
      MeDevHidePolicy = (HIDE_MEI2 | HIDE_MEI3 | HIDE_AMT_DEVICE);
      break;
    case ErrorPath:
    case RecoveryPath:
      MeDevHidePolicy = (HIDE_MEI2 | HIDE_AMT_DEVICE);
      break;
    case SpsPath:
    case SpsRcvPath:
      MeDevHidePolicy = HIDE_SPS_DEVICE;
      break;
    case ErrorWithoutDidMsgPath:
    case SecoverJmprPath:
    case DebugModePath:
    case EnforcementWithoutDidMsgPath:
    default:
      MeDevHidePolicy = HIDE_ALL_ME_DEVICE;
  }

  return MeDevHidePolicy;
}

/**
  Determines message allowance based on current ME Bios boot path.
  HECI1 must be enabled before invoking the function.

  @retval MESSAGE_ALLOWANCE   Mapping of allowed messages
                                @see MESSAGE_ALLOWANCE for bit assignment
**/
MESSAGE_ALLOWANCE
GetMsgAllowance (
  VOID
  )
{
  ME_BIOS_BOOT_PATH MeBiosPath;
  MESSAGE_ALLOWANCE MessageAllowance;

  MeBiosPath = CheckMeBootPath ();
  switch (MeBiosPath) {
    case NormalPath:
    case SpsPath:
      MessageAllowance = ALL_MSG_ALLOWANCE;
      break;
    case ErrorPath:
    case SecoverJmprPath:
    case DebugModePath:
      MessageAllowance = IMR_AND_DID_MSG_ALLOWANCE;
      break;
    case RecoveryPath:
      MessageAllowance = (IMR_AND_DID_MSG_ALLOWANCE | HMRFPO_GRP_MSG_ALLOWANCE | MEI_BUS_MSG_ALLOWANCE | DYN_CLIENT_MSG_ALLOWANCE |  HOST_OWNERSHIP_MSG_ALLOWANCE);
      break;
    case SecoverMeiMsgPath:
      MessageAllowance = (IMR_AND_DID_MSG_ALLOWANCE | HMRFPO_DISABLE_MSG_ALLOWANCE);
      break;
    case SwTempDisablePath:
      MessageAllowance = (IMR_AND_DID_MSG_ALLOWANCE | SET_ME_ENABLE_MSG_ALLOWANCE | GLOBAL_RST_MSG_ALLOWANCE);
      break;
    case SpsRcvPath:
      MessageAllowance = (IMR_AND_DID_MSG_ALLOWANCE | HMRFPO_GRP_MSG_ALLOWANCE | GEN_GRP_MSG_ALLOWANCE);
      break;
    default:
      MessageAllowance = 0;
  }
  return MessageAllowance;
}

/**
  Check if this message is allowed with the current ME Bios boot path.
  HECI1 must be enabled before invoking the function.

  @param[in] HeciDev            The HECI device to be accessed.
  @param[in] HostAddr           The address of the host processor.
  @param[in] MeAddr             Address of the ME subsystem the message is being sent to.
  @param[in] MkhiHeader         Pointer to the message header.

  @retval TRUE                  This message is allowed
  @retval FALSE                 This message is blocked
**/
BOOLEAN
CheckMsgAllowance (
  IN HECI_DEVICE                HeciDev,
  IN UINT8                      HostAddr,
  IN UINT8                      MeAddr,
  IN MKHI_MESSAGE_HEADER        *MkhiHeader
  )
{
  MESSAGE_ALLOWANCE MessageAllowance;
  ///
  /// Check message allowance on HECI1 device only
  ///
  if (HeciDev != HECI1_DEVICE) {
    return TRUE;
  }

  MessageAllowance = GetMsgAllowance ();
  ///
  /// End of Post needs to be send always if HECI1 remains enabled due to security reasons
  ///
  if ((MessageAllowance & ALL_MSG_ALLOWANCE) != 0 ||
      ((MkhiHeader->Fields.Command == GEN_END_OF_POST_CMD) && (MkhiHeader->Fields.GroupId == MKHI_GEN_GROUP_ID))) {
    return TRUE;
  }

  DEBUG ((DEBUG_INFO, "%a() - ", __FUNCTION__));
  if ((MessageAllowance & IMR_AND_DID_MSG_ALLOWANCE) &&
      (MkhiHeader->Fields.GroupId == BUP_COMMON_GROUP_ID) &&
      ((MkhiHeader->Fields.Command == DRAM_INIT_DONE_CMD) || (MkhiHeader->Fields.Command == GET_IMR_SIZE_CMD))) {
    DEBUG ((DEBUG_INFO, "IMR and DID commands"));
  } else if ((MessageAllowance & HMRFPO_DISABLE_MSG_ALLOWANCE) &&
             (MkhiHeader->Fields.Command == HMRFPO_DISABLE_CMD) && (MkhiHeader->Fields.GroupId == BUP_COMMON_GROUP_ID)) {
    DEBUG ((DEBUG_INFO, "HMRFPO_DISABLE command\n"));
  } else if ((MessageAllowance & SET_ME_ENABLE_MSG_ALLOWANCE) &&
             (MkhiHeader->Fields.Command == ME_ENABLE_CMD) && (MkhiHeader->Fields.GroupId == BUP_COMMON_GROUP_ID)) {
    DEBUG ((DEBUG_INFO, "Set Me Enabled command"));
  } else if ((MessageAllowance & GLOBAL_RST_MSG_ALLOWANCE) &&
             (MkhiHeader->Fields.Command == CBM_RESET_CMD) && (MkhiHeader->Fields.GroupId == MKHI_CBM_GROUP_ID)) {
    DEBUG ((DEBUG_INFO, "Global Reset Request command\n"));
  } else if ((MessageAllowance & HMRFPO_GRP_MSG_ALLOWANCE) && MkhiHeader->Fields.GroupId == MKHI_HMRFPO_GROUP_ID) {
    DEBUG ((DEBUG_INFO, "HMRFPO Group commands"));
  } else if ((MessageAllowance & GEN_GRP_MSG_ALLOWANCE) && MkhiHeader->Fields.GroupId == MKHI_GEN_GROUP_ID) {
    DEBUG ((DEBUG_INFO, "GEN Group commands"));
  } else if ((MessageAllowance & MEI_BUS_MSG_ALLOWANCE) &&
          (HostAddr == BIOS_FIXED_HOST_ADDR) && (MeAddr == HECI_HBM_MESSAGE_ADDR)) {
    DEBUG ((DEBUG_INFO, "MEI BUS commands"));
  } else if ((MessageAllowance & DYN_CLIENT_MSG_ALLOWANCE) && (HostAddr > BIOS_FIXED_HOST_ADDR) && (MeAddr > HECI_MAX_ME_FIXED_ADDR)) {
    DEBUG ((DEBUG_INFO, "DYNCLIENT commands"));
  } else {
    DEBUG ((DEBUG_WARN, "This message is not supported on HECI1 with current Me Bios boot path"));
    DEBUG ((DEBUG_WARN, ": %08x (GroudId:%x, CommandId:%x)\n", MkhiHeader->Data, MkhiHeader->Fields.GroupId, MkhiHeader->Fields.Command));
    return FALSE;
  }
  DEBUG ((DEBUG_INFO, "allowed with this Me Bios boot path.\n"));
  return TRUE;
}

/**
  Return number of filled slots in HECI circular buffer.
  Corresponds to HECI HPS (part of) section 4.2.1

  @param[in] Offset        Offset to Host/Me Control Status Register

  @retval FilledSlots      Number of filled slots in circular buffer
  @retval HECI_CB_OVERFLOW Circular buffer overflow has occured
**/
UINT32
GetFilledSlots (
  IN HECI_CONTROL_STATUS_REGISTER ControlStatusRegister
  )
{
  UINT8 FilledSlots;

  FilledSlots = (INT8)ControlStatusRegister.Fields.CBWritePointer - (INT8)ControlStatusRegister.Fields.CBReadPointer;

  return (FilledSlots > (UINT8)ControlStatusRegister.Fields.CBDepth) ? HECI_CB_OVERFLOW : FilledSlots;
}

/**
  This function provides a standard way to verify the HECI cmd and MBAR regs
  in its PCI cfg space are setup properly and that the local mHeciContext
  variable matches this info.

  @param[in] HeciDev              HECI device to be accessed.

  @retval HeciMemBar              HECI Memory BAR.
                                  0 - invalid BAR value returned.
**/
UINTN
CheckAndFixHeciForAccess (
  IN HECI_DEVICE HeciDev
  )
{
  UINT64               HeciBaseAddress;
  UINT64               MemBar;

  ///
  /// Check if HECI_MBAR has changed
  ///
  HeciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER + HeciDev, 0);
  ///
  /// Check for HECI PCI device availability
  ///
  if (PciSegmentRead16 (HeciBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
#if FixedPcdGetBool(PcdBfxEnable) == 1
    MemBar = GetHeciContextBar0 (HeciDev);
    if (MemBar != 0) {
      return ((UINTN) MemBar);
    }
#endif
    DEBUG ((DEBUG_WARN, "HECI%d is not enabled in this phase\n", HECI_NAME_MAP (HeciDev)));
    return 0;
  }

  MemBar = PciSegmentRead32 (HeciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0;
  if ((PciSegmentRead32 (HeciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET) & B_PCI_BAR_MEMORY_TYPE_MASK) == B_PCI_BAR_MEMORY_TYPE_64) {
    MemBar += LShiftU64 ((UINT64)PciSegmentRead32 (HeciBaseAddress + (PCI_BASE_ADDRESSREG_OFFSET + 4)), 32);
  }

  if (MemBar == 0) {
    DEBUG ((DEBUG_WARN, "CheckAndFixHeciForAccess () - MMIO Bar for HECI%d isn't programmed in this phase\n", HECI_NAME_MAP (HeciDev)));
    return 0;
  }
  ///
  /// Enable HECI MSE
  ///
#if FixedPcdGetBool(PcdBfxEnable) == 1
  if (IsCseVariableStorageDevice (HeciDev)) {
    PciSegmentOr8 (HeciBaseAddress + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER));
  } else {
#endif
    PciSegmentOr8 (HeciBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
#if FixedPcdGetBool(PcdBfxEnable) == 1
  }
  SetHeciContextBar0 (HeciDev, MemBar);
#endif

  return (UINTN)MemBar;
}

/**
  Checks if ME is ready for communication over the HECI interface.

  @param[in] HeciMemBar HECI Memory BAR
  @param[in] Timeout    Timeout value

  @retval TRUE   ME is ready
  @retval FALSE  ME is not ready
**/
BOOLEAN
IsMeReady (
  IN UINTN  HeciMemBar,
  IN UINT32 Timeout
  )
{
  HECI_CONTROL_STATUS_REGISTER HeciCsrMeHra;
  UINT32                       TimerStart;
  UINT32                       TimerEnd;
    StartTimer (&TimerStart, &TimerEnd, Timeout);

  do {
    HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
    ///
    /// Check for reset first and then for ME Ready
    ///
    if (HeciCsrMeHra.Fields.Reset) {
      return FALSE;
    } else if (HeciCsrMeHra.Fields.Ready) {
      return TRUE;
    }
  } while (!IsHeciTimeout (TimerStart, TimerEnd));
  DEBUG ((DEBUG_ERROR, "HECI Interface ERROR: Timeout due to ME_RDY bit not set after %d seconds\n", Timeout));
  return FALSE;
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
  UINT64                              HeciBaseAddress;
  HECI_CONTROL_STATUS_REGISTER        HeciCsrHost;
  HECI_FWS_REGISTER                   MeFirmwareStatus;
  UINTN                               HeciMemBar;
  EFI_STATUS                          Status;

  DEBUG ((DEBUG_INFO, "HeciInitialize () - Start\n"));

  ///
  /// Check for the HECI PCI device availability
  /// Get MBAR
  ///
  HeciMemBar = CheckAndFixHeciForAccess (HeciDev);
  if (HeciMemBar == 0) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_INIT_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_DEVICE_ERROR));
    return EFI_DEVICE_ERROR;
  }

  HeciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER + HeciDev, 0);

  HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
  ///
  /// Read H_RDY bit to check if we're already initialized
  ///
  if (HeciCsrHost.Fields.Ready == 1) {
    DEBUG ((DEBUG_INFO, "InitializeHeci () - H_RDY is already initialized\n"));
    return EFI_SUCCESS;
  }

  MeFirmwareStatus.ul = PciSegmentRead32 (HeciBaseAddress + R_ME_HFS);
  DEBUG ((DEBUG_INFO, "[HECI%d] HfSts1 = 0x%08X\n", HECI_NAME_MAP (HeciDev), MeFirmwareStatus.ul));
  if (MeFirmwareStatus.ul == 0 || MeFirmwareStatus.ul == 0xFFFFFFFF) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_INIT_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_DEVICE_ERROR));
    return EFI_DEVICE_ERROR;
  }
  ///
  /// Check for ME FPT Bad
  ///
  if (MeFirmwareStatus.r.FptBad) {
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Set HECI interrupt delivery mode.
  /// HECI-1 using legacy/MSI interrupt
  ///
  PciSegmentAnd8 (HeciBaseAddress + R_ME_HIDM, 0xFC);

  ///
  /// Need to do following on ME init:
  ///
  ///  1) wait for ME_CSR_HA reg ME_RDY bit set
  ///
  if (!IsMeReady (HeciMemBar, HECI_INIT_TIMEOUT)) {
    Status = ResetHeciInterface (HeciDev);
    if (EFI_ERROR (Status)) {
      REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_INIT_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (Status));
      return Status;
    }
  }
  ///
  ///  2) setup H_CSR reg as follows:
  ///     a) Make sure H_RST is clear
  ///     b) Set H_RDY
  ///     c) Set H_IG
  ///
  DEBUG ((DEBUG_INFO, "InitializeHeci () -  Set H_RDY\n"));
  HeciCsrHost.Data  = MmioRead32 (HeciMemBar + H_CSR);
  if (HeciCsrHost.Fields.Ready == 0) {
    HeciCsrHost.Fields.Reset       = 0;
    HeciCsrHost.Fields.Ready       = 1;
    HeciCsrHost.Fields.IntGenerate = 1;
    MmioWrite32 (HeciMemBar + H_CSR, HeciCsrHost.Data);
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
  HECI_CONTROL_STATUS_REGISTER    HeciCsrHost;
  EFI_STATUS                      Status;
  UINTN                           HeciMemBar;

  HeciMemBar = CheckAndFixHeciForAccess (HeciDev);
  if (HeciMemBar == 0) {
    return EFI_DEVICE_ERROR;
  }
  DEBUG ((DEBUG_INFO, "HeciReInitialize..... \n"));

  Status = EFI_SUCCESS;
  ///
  /// Need to do following on ME init:
  ///
  ///  1) wait for HOST_CSR_HA reg H_RDY bit set
  ///
  ///    if (WaitForHostReady() != EFI_SUCCESS) {
  ///
  if (MeResetWait (HeciDev, HECI_INIT_TIMEOUT) != EFI_SUCCESS) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_REINIT_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (Status));
    return EFI_TIMEOUT;
  }

  HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
  if (HeciCsrHost.Fields.Ready == 0) {
    Status = ResetHeciInterface (HeciDev);
  }

  if (EFI_ERROR (Status)) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_REINIT_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (Status));
  }

  return Status;
}

/**
  Function to pull one message packet off the HECI circular buffer up to its capacity.
  Corresponds to HECI HPS (part of) section 4.2.4.
  BIOS does not rely on Interrupt Status bit, since this bit can be set due to several reasons:
    a) CSME has finished reading data from H_CSR
    b) CSME has finished writing data to ME_CSR
    c) Reset has occured
  Because of above - additional checks must be conducted in order to prevent misinterpretations.

  @param[in] HeciMemBar           HECI Memory BAR.
  @param[in] Timeout              Timeout value for first Dword to appear in circular buffer.
  @param[out] MessageHeader       Pointer to message header buffer.
  @param[in] MessageData          Pointer to receive buffer.
  @param[in, out] BufferLength    On input is the size of the caller's buffer in bytes.
                                  On output is the size of the data copied to the buffer.
  @param[out] PacketSize          Size of the packet in bytes. This might be greater than buffer size.

  @retval EFI_SUCCESS             One message packet read.
  @retval EFI_DEVICE_ERROR        The circular buffer is overflowed or transaction error.
  @retval EFI_NO_RESPONSE         The circular buffer is empty
  @retval EFI_TIMEOUT             Failed to receive a full message on time
  @retval EFI_BUFFER_TOO_SMALL    Message packet is larger than caller's buffer
**/
EFI_STATUS
HeciPacketRead (
  IN      UINTN               HeciMemBar,
  IN      UINT32              Timeout,
  OUT     HECI_MESSAGE_HEADER *MessageHeader,
  OUT     UINT32              *MessageData,
  IN OUT  UINT32              *BufferLength,
  OUT     UINT32              *PacketSize
  )
{
  EFI_STATUS                   Status;
  UINT32                       TimerStart;
  UINT32                       TimerEnd;
  UINT32                       i;
  UINT32                       FilledSlots;
  UINT32                       LengthInDwords;
  UINT32                       TempBuffer;
  UINT32                       ByteCount;
  HECI_CONTROL_STATUS_REGISTER HeciCsrMeHra;
  HECI_CONTROL_STATUS_REGISTER HeciCsrHost;

  *PacketSize = 0;
  Status      = EFI_SUCCESS;

  HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
  FilledSlots = GetFilledSlots (HeciCsrMeHra);

  ///
  /// For BLOCKING read, wait until data appears in the CB or timeout occurs
  ///
  if (Timeout != 0) {
    StartTimer (&TimerStart, &TimerEnd, Timeout);
    while (FilledSlots == 0) {
      if (MeHeciTimeoutsEnabled () && IsHeciTimeout (TimerStart, TimerEnd)) {
        return EFI_TIMEOUT;
      }
      HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
      FilledSlots = GetFilledSlots (HeciCsrMeHra);
    }
  }

  ///
  /// Check for empty and overflowed CB
  ///
  if (FilledSlots == 0) {
    *BufferLength = 0;
    return EFI_NO_RESPONSE;
  } else if (FilledSlots == HECI_CB_OVERFLOW) {
    *BufferLength = 0;
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Eat the HECI Message header
  ///
  MessageHeader->Data = MmioRead32 (HeciMemBar + ME_CB_RW);
  ///
  /// Compute required message length in DWORDS
  ///
  LengthInDwords = ((MessageHeader->Fields.Length + 3) / 4);

  if (LengthInDwords > HeciCsrMeHra.Fields.CBDepth) {
    ///
    /// Make sure that the message does not overflow the circular buffer.
    ///
    *BufferLength = 0;
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Wait until whole message appears in circular buffer.
  ///
  StartTimer (&TimerStart, &TimerEnd, HECI_READ_TIMEOUT);
  do {
    HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
    if (MeHeciTimeoutsEnabled () && IsHeciTimeout (TimerStart, TimerEnd)) {
      return EFI_TIMEOUT;
    }
  } while (GetFilledSlots (HeciCsrMeHra) < LengthInDwords);


  ///
  /// Update status to signal if buffer can hold the message
  ///
  if ((MessageHeader->Fields.Length) <= *BufferLength) {
    Status = EFI_SUCCESS;
  } else {
    Status = EFI_BUFFER_TOO_SMALL;
  }
  ///
  /// Copy as much bytes as there is space left in the message buffer.
  /// Excessive bytes will be dismissed.
  ///
  ByteCount = 0;
  for (i = 0; i < LengthInDwords; i++) {
    TempBuffer = MmioRead32 (HeciMemBar + ME_CB_RW);
    CopyMem (&MessageData[i], &TempBuffer, MIN(sizeof(TempBuffer),*BufferLength));
    ByteCount += MIN(sizeof(TempBuffer),*BufferLength);
    *BufferLength -= MIN(sizeof(TempBuffer),*BufferLength);
  }
  *BufferLength = ByteCount;
  *PacketSize = MessageHeader->Fields.Length;

  ///
  /// Read ME_CSR_HA.  If the ME_RDY bit is 0, then an ME reset occurred during the
  /// transaction and the message should be discarded as bad data may have been retrieved
  /// from the host's circular buffer
  ///
  HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
  if (HeciCsrMeHra.Fields.Ready == 0) {
    *BufferLength = 0;
    *PacketSize   = 0;
    return EFI_NOT_READY;
  }

  ///
  /// Set Interrupt Generate bit and clear Interrupt Status bit if there are no more messages in the buffer.
  ///
  HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
  if (GetFilledSlots (HeciCsrMeHra) == 0) {
    HeciCsrHost.Data                = MmioRead32 (HeciMemBar + H_CSR);
    HeciCsrHost.Fields.IntGenerate  = 1;
    HeciCsrHost.Fields.IntStatus    = 1;
    MmioWrite32 (HeciMemBar + H_CSR, HeciCsrHost.Data);
    HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
  }

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
  UINTN               HeciMemBar;
  HECI_MESSAGE_HEADER PacketHeader;
  EFI_STATUS          Status;
  UINT32              TotalLength;
  UINT32              PacketSize;
  UINT32              PacketBuffer;
  UINT32              ReadTimeout;
  UINT32              InitTimeout;

  if (HeciDev == ISH_HECI) {
    return IshHeciReceive (Blocking, MessageBody, Length);
  }

  if (HeciDev == PSE_HECI) {
    return PseHeciReceive (Blocking, MessageBody, Length);
  }

  PacketHeader.Data = 0;
  TotalLength       = 0;
  PacketBuffer      = *Length;
  Status            = EFI_SUCCESS;

  ///
  /// Make sure that HECI device BAR is correct and device is enabled.
  ///
  HeciMemBar = CheckAndFixHeciForAccess (HeciDev);
  if (HeciMemBar == 0) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_RECEIVE_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_DEVICE_ERROR));
    return EFI_DEVICE_ERROR;
  }

  if (Blocking) {
    InitTimeout = HECI_INIT_TIMEOUT;
    ReadTimeout = HECI_READ_TIMEOUT;
  } else {
    InitTimeout = 0;
    ReadTimeout = 0;
  }

  if (!IsMeReady(HeciMemBar, InitTimeout)) {
    //
    // Return as CB will be empty after reset and CSME will not put any data
    //
    ResetHeciInterface (HeciDev);
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_RECEIVE_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_NOT_READY));
    return EFI_NOT_READY;
  }

  //
  // Read until MessageComplete bit is set
  //
  while (!PacketHeader.Fields.MessageComplete) {
    Status = HeciPacketRead (
                  HeciMemBar,
                  ReadTimeout,
                  &PacketHeader,
                  (UINT32 *) &MessageBody[TotalLength / 4],
                  &PacketBuffer,
                  &PacketSize
                  );

    DEBUG_CODE (
      if (Status != EFI_NO_RESPONSE || ReadTimeout != 0) {
        DEBUG ((DEBUG_INFO, "[HECI%d] Got msg %r: %08X\n", HECI_NAME_MAP (HeciDev), Status, PacketHeader.Data));
        if (!BootMediaIsUfs () || HeciDev == HECI1_DEVICE) {
          //
          // Showing the buffer has a very large impact on UFS boot time due to the BIOS proxy
          //
          ShowBuffer ((UINT8 *) &MessageBody[TotalLength / 4], PacketBuffer);
        }
      }
      );
    ///
    /// If timeout occured we need to reset the interface to clear the data that could possibly come later.
    /// Also buffer overflow and transaction errors will require a reset.
    /// We need to continue read even if buffer too small to clear the data and signal the buffer size.
    ///
    if (EFI_ERROR (Status) && Status != EFI_BUFFER_TOO_SMALL) {
      if (Status != EFI_NO_RESPONSE) {
        ResetHeciInterface (HeciDev);
      }
      *Length = TotalLength;
      REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_RECEIVE_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (Status));
      return Status;
    }
    ///
    /// Track the length of what we have read so far
    ///
    TotalLength += PacketSize;
    ///
    /// To do message size calculations we are using 3 different variables:
    /// PacketBuffer - on input -> space left in the buffer, on output -> number of bytes written to buffer
    /// Length       - max buffer size
    /// TotalLength  - Total message size -> sum of all bytes in multiple packets
    ///
    if (TotalLength < *Length) {
      PacketBuffer = *Length - TotalLength;
    } else {
      PacketBuffer = 0;
    }
    ///
    /// If this was a NON-BLOCKING message and it is a multipacket message, we need to change the
    /// parameter to BLOCKING because it will take a non-zero value of time until a new packet appears
    ///
    ReadTimeout = HECI_READ_TIMEOUT;
  }

  *Length = TotalLength;

  if (EFI_ERROR (Status)) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_RECEIVE_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (Status));
  }
  return Status;
}

/**
  Function sends one message packet through the HECI circular buffer
  Corresponds to HECI HPS (part of) section 4.2.3

  @param[in] HeciMemBar           HECI Memory BAR.
  @param[in] MessageHeader        Pointer to the message header.
  @param[in] MessageData          Pointer to the actual message data.

  @retval EFI_SUCCESS             One message packet sent
  @retval EFI_ABORTED             Fatal error has occured during transmission of the message
  @retval EFI_DEVICE_ERROR        Unrecoverable fatal error has occured during transmission of the message
  @retval EFI_TIMEOUT             CSME failed to empty the circular buffer
  @retval EFI_NOT_READY           Fatal error has occured during transmission of the message
**/
EFI_STATUS
HeciPacketWrite (
  IN  UINTN                    HeciMemBar,
  IN  HECI_MESSAGE_HEADER      *MessageHeader,
  IN  UINT32                   *MessageData
  )
{
  UINT32                       TimerStart;
  UINT32                       TimerEnd;
  UINT32                       i;
  UINT32                       LengthInDwords;
  HECI_CONTROL_STATUS_REGISTER HeciCsrHost;
  HECI_CONTROL_STATUS_REGISTER HeciCsrMeHra;

  ///
  /// Start timeout counter
  ///
  StartTimer (&TimerStart, &TimerEnd, HECI_SEND_TIMEOUT);

  ///
  /// Compute message length in DWORDS
  ///
  LengthInDwords = ((MessageHeader->Fields.Length + 3) / 4);

  ///
  /// Wait until there is sufficient room in the circular buffer
  /// Must have room for message and message header
  ///
  HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
  while ((LengthInDwords + 1) > (HeciCsrHost.Fields.CBDepth - GetFilledSlots (HeciCsrHost))) {
    if (MeHeciTimeoutsEnabled () && IsHeciTimeout (TimerStart, TimerEnd)) {
      DEBUG ((DEBUG_ERROR, "HeciPacketWrite: EFI_TIMEOUT due to circular buffer never emptied after 5 seconds waiting"));
      return EFI_TIMEOUT;
    }
    HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
  }
  ///
  /// Write Message Header
  ///
  MmioWrite32 (HeciMemBar + H_CB_WW, MessageHeader->Data);

  ///
  /// Write Message Body
  ///
  for (i = 0; i < LengthInDwords; i++) {
    MmioWrite32 (HeciMemBar + H_CB_WW, MessageData[i]);
  }
  ///
  /// Set Interrupt Generate bit
  ///
  HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
  HeciCsrHost.Fields.IntGenerate = 1;
  MmioWrite32 (HeciMemBar + H_CSR, HeciCsrHost.Data);

  ///
  /// Test if ME Ready bit is set to 1, if set to 0 a fatal error occured during
  /// the transmission of this message.
  ///
  HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
    HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
    if (HeciCsrMeHra.Fields.Ready == 0) {
      return EFI_NOT_READY;
    }

  return EFI_SUCCESS;
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
  EFI_STATUS                   Status;
  HECI_MESSAGE_HEADER          MessageHeader;
  HECI_CONTROL_STATUS_REGISTER HeciCsrHost;
  UINT32                       CircularBufferDepth;
  UINT32                       SendLength;
  UINT32                       BytesLeft;
  UINT32                       MeMode;
  UINTN                        HeciMemBar;

  if (HeciDev == ISH_HECI) {
    return IshHeciSend (Message, Length, HostAddress, MeAddress);
  }

  if (HeciDev == PSE_HECI) {
    return PseHeciSend (Message, Length, HostAddress, MeAddress);
  }

  ///
  /// Make sure that HECI device BAR is correct and device is enabled.
  ///
  HeciMemBar = CheckAndFixHeciForAccess (HeciDev);
  if (HeciMemBar == 0) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_SEND_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_DEVICE_ERROR));
    return EFI_DEVICE_ERROR;
  }

  if (MeHeciMessageCheckEnabled () == TRUE) {
    if (CheckMsgAllowance (HeciDev, HostAddress, MeAddress, (MKHI_MESSAGE_HEADER *) Message) == FALSE) {
      DEBUG ((DEBUG_INFO, "CheckMsgAllowance fail: [HECI%d] HostAddress: %x, MeAddress: %x, Length: %x\n",
        HECI_NAME_MAP(HeciDev), HostAddress, MeAddress, Length));
      DEBUG_CODE (
        ShowBuffer ((UINT8 *) Message, Length);
      );
      REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_SEND_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_UNSUPPORTED));
      return EFI_UNSUPPORTED;
    }
  }

  HeciGetMeMode (&MeMode);
  if (MeMode == ME_MODE_SECOVER) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_SEND_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_UNSUPPORTED));
    return EFI_UNSUPPORTED;
  }
  ///
  /// Make sure that HECI is ready for communication
  ///
  if (!IsMeReady (HeciMemBar, HECI_INIT_TIMEOUT)) {
    ///
    /// If reset successful, continue as the interface should be healthy now
    ///
    Status = ResetHeciInterface (HeciDev);
    if (EFI_ERROR(Status)) {
      REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_SEND_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_NOT_READY));
      return EFI_NOT_READY;
    }
  }
  ///
  /// Set up memory mapped registers
  ///
  HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);

  ///
  /// Grab Circular Buffer length and convert it from Dword to bytes
  ///
  CircularBufferDepth = 4 * HeciCsrHost.Fields.CBDepth;

  ///
  /// Prepare message header
  ///
  MessageHeader.Data               = 0;
  MessageHeader.Fields.MeAddress   = MeAddress;
  MessageHeader.Fields.HostAddress = HostAddress;

  BytesLeft = Length;
  ///
  /// Break message up into CB-sized packets and loop until completely sent
  ///
  while (BytesLeft) {
    ///
    /// Set the Message Complete bit if this is our last packet in the message.
    /// Needs to be less or equal to CB depth minus one Dword for HECI header.
    ///
    if (BytesLeft <= CircularBufferDepth - sizeof (MessageHeader)) {
      MessageHeader.Fields.MessageComplete = 1;
    }
    ///
    /// Calculate length for Message Header:
    /// It will be the smaller value of circular buffer or remaining message.
    ///
    SendLength = MIN(CircularBufferDepth - sizeof (MessageHeader),BytesLeft);
    MessageHeader.Fields.Length = SendLength;
    ///
    /// Send the current packet
    ///
    DEBUG ((DEBUG_INFO, "[HECI%d] Send msg: %08X\n", HECI_NAME_MAP (HeciDev), MessageHeader.Data));
    if (!BootMediaIsUfs () || HeciDev == HECI1_DEVICE) {
      //
      // Showing the buffer has a very large impact on UFS boot time due to the BIOS proxy
      //
      DEBUG_CODE (
        ShowBuffer ((UINT8 *) ((UINTN)Message + (Length-BytesLeft)), MessageHeader.Fields.Length);
        );
    }
    Status = HeciPacketWrite (HeciMemBar, &MessageHeader, (UINT32*)((UINTN)Message + (Length-BytesLeft)));
    if (EFI_ERROR (Status)) {
      ResetHeciInterface (HeciDev);
      REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_SEND_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (Status));
      return Status;
    }
    ///
    /// Update the length information
    ///
    BytesLeft -= SendLength;
  }
  return EFI_SUCCESS;
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
  EFI_STATUS          Status;

  if (HeciDev == ISH_HECI) {
    return IshHeciSendAndReceive (Message, Length, RecLength, HostAddress, MeAddress);
  }

  if (HeciDev == PSE_HECI) {
    return PseHeciSendAndReceive (Message, Length, RecLength, HostAddress, MeAddress);
  }

  ///
  /// Send the message
  ///
  Status = HeciSend (HeciDev, Message, Length, HostAddress, MeAddress);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "[HECI%d] HeciSendwAck failed on send, Status: %r, abort!\n", HECI_NAME_MAP (HeciDev), Status));
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_ACK_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (Status));
    return Status;
  }
  ///
  /// Receive the message
  ///
  Status = HeciReceive (HeciDev, BLOCKING, Message, RecLength);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "[HECI%d] HeciSendwAck failed on read, Status: %r\n", HECI_NAME_MAP (HeciDev), Status));
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_ACK_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (Status));
  }

  return Status;
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
  HECI_CONTROL_STATUS_REGISTER HeciCsrHost;
  UINT32                       TimerStart;
  UINT32                       TimerEnd;
  UINTN                        HeciMemBar;

  ///
  /// Make sure that HECI device BAR is correct and device is enabled.
  ///
  HeciMemBar = CheckAndFixHeciForAccess (HeciDev);
  if (HeciMemBar == 0) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_RESETWAIT_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_DEVICE_ERROR));
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Wait for the HOST Ready bit to be cleared to signal a reset
  ///
  StartTimer (&TimerStart, &TimerEnd, Delay);
  HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
  while (HeciCsrHost.Fields.Ready == 1) {
    ///
    /// If timeout has expired, return fail
    ///
    if (IsHeciTimeout (TimerStart, TimerEnd)) {
      REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_RESETWAIT_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_TIMEOUT));
      return EFI_TIMEOUT;
    }

    HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
  }

  return EFI_SUCCESS;
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
  UINT32                       TimerStart;
  UINT32                       TimerEnd;
  UINTN                        HeciMemBar;


  DEBUG ((DEBUG_INFO, "[HECI%d] Resetting interface\n", HECI_NAME_MAP (HeciDev)));

  ///
  /// Make sure that HECI device BAR is correct and device is enabled.
  ///
  HeciMemBar = CheckAndFixHeciForAccess (HeciDev);
  if (HeciMemBar == 0) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_RESET_HECI_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_DEVICE_ERROR));
    return EFI_DEVICE_ERROR;
  }

  ///
  /// Enable Reset
  ///
  HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
  DEBUG ((DEBUG_INFO, "[HECI%d] - Step1 Enable Host Reset : H_CSR = 0x%08X\n", HECI_NAME_MAP (HeciDev), HeciCsrHost.Data));

  if (!HeciCsrHost.Fields.Reset) {
    HeciCsrHost.Fields.Reset       = 1;
    HeciCsrHost.Fields.IntGenerate = 1;
    MmioWrite32 (HeciMemBar + H_CSR, HeciCsrHost.Data);
  }

  ///
  /// Make sure that the reset started
  ///
  DEBUG ((DEBUG_INFO, "[HECI%d] - Step2 Wait for reset started: H_CSR = 0x%08X\n", HECI_NAME_MAP (HeciDev), HeciCsrHost.Data));
  StartTimer (&TimerStart, &TimerEnd, HECI_INIT_TIMEOUT);
  do {
    if (IsHeciTimeout (TimerStart, TimerEnd)) {
      REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_RESET_HECI_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_TIMEOUT));
      return EFI_TIMEOUT;
    }
    HeciCsrHost.Data = MmioRead32 (HeciMemBar + H_CSR);
  } while (HeciCsrHost.Fields.Ready == 1);

  ///
  /// Wait for ME to perform reset
  ///
  HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
  DEBUG ((DEBUG_INFO, "[HECI%d] - Step3  Wait for ME reset: ME_CSR_HA = 0x%08X\n", HECI_NAME_MAP (HeciDev), HeciCsrMeHra.Data));
  do {
    if (IsHeciTimeout (TimerStart, TimerEnd)) {
      DEBUG ((DEBUG_INFO, "[HECI%d] - Step3  ME has failed to reset Heci: ME_CSR_HA = 0x%08X\n", HECI_NAME_MAP (HeciDev), HeciCsrMeHra.Data));
      REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_RESET_HECI_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_TIMEOUT));
      return EFI_TIMEOUT;
    }
    HeciCsrMeHra.Data = MmioRead32 (HeciMemBar + ME_CSR_HA);
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
  UINT64            HeciBaseAddress;

  if (MeStatus == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  HeciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, 0);
  if (PciSegmentRead16 (HeciBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_GET_STATUS_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_NOT_FOUND));
    return EFI_NOT_FOUND;
  }

  MeFirmwareStatus.ul = PciSegmentRead32 (HeciBaseAddress + R_ME_HFS);

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

  DEBUG ((DEBUG_INFO, "[HECI1] MeStatus 0x%X (Hfsts1: %08X)\n", *MeStatus, MeFirmwareStatus.ul));

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
  UINT64            HeciBaseAddress;

  if (MeMode == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  HeciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, 0);
  if (PciSegmentRead16 (HeciBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_GET_MODE_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_NOT_FOUND));
    return EFI_NOT_FOUND;
  }

  MeFirmwareStatus.ul = PciSegmentRead32 (HeciBaseAddress + R_ME_HFS);
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

  DEBUG ((DEBUG_INFO, "[HECI1] MeMode %d (Hfsts1: %08X)\n", *MeMode, MeFirmwareStatus.ul));

  return EFI_SUCCESS;
}
