/** @file
  Definitions for HECI driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2019 Intel Corporation.

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
#ifndef _HECI_INIT_LIB_H
#define _HECI_INIT_LIB_H


#include <CoreBiosMsg.h>
#include <Register/MeRegs.h>

/**
  Abstract ME BIOS Boot Path definitions.
  BIOS Boot Path vs. MEI1 Host Firmware Status 1, 4, and 5 registers:
  MeNormalBiosPath -
    If (HECI_FWS_REGISTER.r.CurrentState == ME_STATE_NORMAL AND
      HECI_FWS_REGISTER.r.ErrorCode == ME_ERROR_CODE_NO_ERROR)
    - BIOS takes the normal firmware BIOS path.

  MeErrorWithoutDidMsgBiosPath -
    If HECI_FWS_REGISTER.r.ErrorCode == ME_ERROR_CODE_IMAGE_FAILURE
    - The BIOS does not send any Intel MEI messages including DID and EOP message.
    - The BIOS does not invoke the Intel MEBX and should hide Intel MEBX hotkey entry.
    - MEI 1 device should be enabled by the BIOS so it allows the user to update the new firmware and
      take the firmware out of a recovery or error condition. Hide MEI 2, MEI3, SOL and IDER. In addition,
      Image Failure results in a platform involuntary 30-minute shut down triggered by Intel ME.
      BIOS shall post the warning message as part of the error handling flow.

  MeErrorBiosPath -
    If (HECI_FWS_REGISTER.r.FptBad == 0x01) OR
      (HECI_FWS_REGISTER.r.ErrorCode != ME_ERROR_CODE_NO_ERROR) OR
      (HECI_FWS_REGISTER.r.ErrorCode != ME_ERROR_CODE_IMAGE_FAILURE)
    - The BIOS does not send any Intel MEI messages except for the DRAM Init Done message. Moreover,
      the BIOS doesn't even send EOP message.
    - The BIOS does not invoke the Intel MEBX and should hide Intel MEBX hotkey entry.
    - MEI 1 device should be enabled by the BIOS so it allows the user to update the new firmware and
      take the firmware out of a recovery or error condition. Hide MEI 2, SOL and IDER.

  MeRecoveryBiosPath -
    If HECI_FWS_REGISTER.r.CurrentState == ME_STATE_RECOVERY
    - The BIOS does not send any Intel MEI messages except for the DRAM Init Done message. Moreover,
      the BIOS doesn't even send EOP message.
    - The BIOS does not invoke the Intel MEBX and should hide Intel MEBX hotkey entry.
    - MEI 1 device should be enabled by the BIOS so it allows the user to update the new firmware and
      take the firmware out of a recovery or error condition. Hide MEI 2, SOL and IDER.

  MeDebugModeBiosPath -
    If HECI_FWS_REGISTER.r.MeOperationMode == ME_OPERATION_MODE_DEBUG
    - The BIOS does not send any Intel MEI messages except DID and EOP message.
    - The BIOS does not invoke the Intel MEBX and should hide Intel MEBX hotkey entry.
    - Hide MEI1, MEI2, MEI3, SOL and IDER before OS boot. It means there is no MEI drivers loaded in OS environment.

  MeSwTempDisableBiosPath
    If (HECI_FWS_REGISTER.r.MeOperationMode == ME_OPERATION_MODE_SOFT_TEMP_DISABLE)
    - The BIOS does not send any Intel MEI messages except for the DRAM Init Done message, Set Me Enable message
      and Global Reset Message.
      Moreover, the BIOS doesn't even send EOP message.
    - The BIOS does not invoke the Intel MEBX and should hide Intel MEBX hotkey entry.
    - Hide MEI2, MEI3, SOL and IDER before OS boot. It means there is no MEI drivers loaded in OS environment.
      Hides MEI1 device after sending the Set Me Enable message or prior to boot.
      It means there is no MEI drivers loaded in OS environment.

  MeSecoverJmprBiosPath
    If (HECI_FWS_REGISTER.r.MeOperationMode == ME_OPERATION_MODE_SECOVR_JMPR)
    - The BIOS does not send any Intel MEI messages except for the DRAM Init Done message. Moreover,
      the BIOS doesn't even send EOP message.
    - The BIOS does not invoke the Intel MEBX and should hide Intel MEBX hotkey entry.
    - Hide MEI1, MEI2, MEI3, SOL and IDER before OS boot. It means there is no MEI drivers loaded in OS environment.

  MeSecoverMeiMsgBiosPath
    If HECI_FWS_REGISTER.r.MeOperationMode == ME_OPERATION_MODE_SECOVR_HECI_MSG
    - The BIOS does not send any Intel MEI messages except for the DRAM Init Done (DID) message and HMRFPO DISABLE message.
      The HMRFPO DISABLE message is to bring the firmware out of SECOVR_MEI_MSG operation mode back to normal.
    - The BIOS does not invoke the Intel MEBX and should hide Intel MEBX hotkey entry.
    - Hide MEI2, MEI3, SOL and IDER before OS boot.
      Hides MEI1 device after sending the HMRFPO DISABLE message.
      It means there is no MEI drivers loaded in OS environment.

  MeEnforcementWithoutDidMsgBiosPath
    If HECI_FW_STS4_REGISTER.r.FwInEnfFlow == 1
    - The BIOS does not send any Intel MEI messages including DID and EOP message.
    - The BIOS does not invoke the Intel MEBX and should hide Intel MEBX hotkey entry.
    - Hide MEI1, MEI2, MEI3, SOL and IDER before OS boot.
**/

/**
  The FW registers may report multiple status to reflect Me Bios boot path, BIOS will follow the
  prioritized Me Bios boot path to continue boot. If the priority will be changed, then
  BOOT_PATH enumeration shall be adjusted as well to reflect real priority.
**/
typedef enum {
  NormalPath = 0,
  ErrorPath,
  RecoveryPath,
  ErrorWithoutDidMsgPath,
  SecoverMeiMsgPath,
  SwTempDisablePath,
  SecoverJmprPath,
  DebugModePath,
  EnforcementWithoutDidMsgPath,
  SpsPath,
  SpsRcvPath,
  MaxPathValue
} ME_BIOS_BOOT_PATH;

/**
  Abstract devices map for CSME devices to be hidden
  Bit0 - MEI1
  Bit1 - MEI2
  Bit2 - MEI3
  Bit3 - MEI4
  Bit7 - SOL
**/
typedef UINT8 ME_DEV_EXPOSURE;

#define HIDE_MEI1                BIT0
#define HIDE_MEI2                BIT1
#define HIDE_MEI3                BIT2
#define HIDE_MEI4                BIT3
#define HIDE_SOL                 BIT7

#define HIDE_AMT_DEVICE          HIDE_SOL
#define HIDE_ALL_ME_DEVICE       (HIDE_MEI1|HIDE_MEI2|HIDE_MEI3|HIDE_MEI4|HIDE_AMT_DEVICE)
#define HIDE_SPS_DEVICE          (HIDE_MEI3|HIDE_MEI4|HIDE_AMT_DEVICE)

/**
  Abstract MEI message allowance in non MeNormalBiosPath definition
  Bit0 - IMR and DID messages are allowed to be sent with this BIOS path
  Bit1 - EOP message is allowed to be sent with this BIOS path
  Bit2 - HMRFPO DISABLE message is allowed to be sent with this BIOS path
  Bit3 - SET ME ENABLE message is allowed to be sent with this BIOS path
  Bit4 - GLOBAL RESET message is allowed to be sent with this BIOS path
  BIT5 - HMRFPO messages are allowed to be sent with this ME Bios boot path
  BIT6 - GEN messages are allowed to be sent with this ME Bios boot path
  BIT7 - MEI BUS messages are allowed to be sent with this ME Bios boot path
  BIT8 - Messages that for dynamic ME addressN are allowed to be sent with this ME Bios boot path
  BIT15- All messages are allowed to be sent with this ME Bios boot path
**/
typedef UINT16 MESSAGE_ALLOWANCE;

#define IMR_AND_DID_MSG_ALLOWANCE     BIT0
#define EOP_MSG_ALLOWANCE             BIT1
#define HMRFPO_DISABLE_MSG_ALLOWANCE  BIT2
#define SET_ME_ENABLE_MSG_ALLOWANCE   BIT3
#define GLOBAL_RST_MSG_ALLOWANCE      BIT4
#define HMRFPO_GRP_MSG_ALLOWANCE      BIT5
#define GEN_GRP_MSG_ALLOWANCE         BIT6
#define MEI_BUS_MSG_ALLOWANCE         BIT7
#define DYN_CLIENT_MSG_ALLOWANCE      BIT8
#define HOST_OWNERSHIP_MSG_ALLOWANCE  BIT9
#define ALL_MSG_ALLOWANCE             BIT15

//
// Prototypes
//
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
  );

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
  );

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
  IN HECI_DEVICE                  HeciDev
  );

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
  );

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
  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this message through this HECI
**/
EFI_STATUS
EFIAPI
HeciReceive (
  IN      HECI_DEVICE             HeciDev,
  IN      UINT32                  Blocking,
  IN OUT  UINT32                  *MessageBody,
  IN OUT  UINT32                  *Length
  );

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
  IN HECI_DEVICE                  HeciDev,
  IN UINT32                       *Message,
  IN UINT32                       Length,
  IN UINT8                        HostAddress,
  IN UINT8                        MeAddress
  );

/**
  Function sends one message through the HECI circular buffer and waits
  for the corresponding ACK message.

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
  IN      HECI_DEVICE             HeciDev,
  IN OUT  UINT32                  *Message,
  IN      UINT32                  Length,
  IN OUT  UINT32                  *RecLength,
  IN      UINT8                   HostAddress,
  IN      UINT8                   MeAddress
  );

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
  IN  HECI_DEVICE                 HeciDev,
  IN  UINT32                      Delay
  );

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
  IN  HECI_DEVICE                 HeciDev
  );

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
  OUT UINT32                      *MeStatus
  );

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
  OUT UINT32                       *MeMode
  );

//
// Prototype for ME Policy from PEI and DXE phase
//

/**
  Read the ME policy to see if HECI timeouts are enabled.
  @retval TRUE             Timeout is enabled
  @retval FALSE            Timeout is disabled
**/
extern
BOOLEAN
MeHeciTimeoutsEnabled (
  VOID
  );

/**
  Read the ME policy to see if HECI message check is enabled for Bios Boot Path.

  @retval TRUE             HECI message check is enabled
  @retval FALSE            HECI message check is disabled
**/
BOOLEAN
MeHeciMessageCheckEnabled (
  VOID
  );

#if FixedPcdGetBool(PcdBfxEnable) == 1
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
  );
#endif

#endif // _HECI_INIT_LIB_H

