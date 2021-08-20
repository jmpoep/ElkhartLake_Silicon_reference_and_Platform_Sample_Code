/** @file
  HECI Protocol

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#ifndef _HECI_PROTOCOL_H
#define _HECI_PROTOCOL_H

#include <MeState.h>
#include <Register/MeRegs.h>

///
/// HECI protocol provided for DXE phase
/// This protocol provides an interface to communicate with Intel ME subsystem via HECI
///
typedef struct _HECI_PROTOCOL  HECI_PROTOCOL;

#define NON_BLOCKING                        0
#define BLOCKING                            1

/**
  Function sends one message through the HECI circular buffer and waits
  for the corresponding ACK message.

  @param[in] HeciDev              The HECI device to be accessed.
  @param[in, out] *Message        Pointer to the message buffer.
  @param[in] Length               Length of the message in bytes.
  @param[in, out] *RecLength      Length of the message response in bytes.
  @param[in] HostAddress          Address of the sending entity.
  @param[in] MEAddress            Address of the ME entity that should receive the message.

  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
  @retval EFI_UNSUPPORTED         Current ME mode doesn't support send this message through this HECI
**/
typedef
EFI_STATUS
(EFIAPI *HECI_SENDWACK) (
  IN      HECI_DEVICE             HeciDev,
  IN OUT  UINT32                  *Message,
  IN OUT  UINT32                  Length,
  IN OUT  UINT32                  *RecLength,
  IN      UINT8                   HostAddress,
  IN      UINT8                   MEAddress
  );

/**
  Read the HECI Message from Intel ME with size in Length into
  buffer MessageBody. Set Blocking to BLOCKING and code will
  wait until one message packet is received. When set to
  NON_BLOCKING, if the circular buffer is empty at the time, the
  code will not wait for the message packet.
  This can only be used after sending a message through HECI first.

  @param[in] HeciDev              The HECI device to be accessed.
  @param[in] Blocking             Used to determine if the read is BLOCKING or NON_BLOCKING.
  @param[in] *MessageBody         Pointer to a buffer used to receive a message.
  @param[in, out] *Length         Pointer to the length of the buffer on input and the length of the message on return. (in bytes)

  @retval EFI_SUCCESS             One message packet read.
  @retval EFI_DEVICE_ERROR        Failed to initialize HECI or zero-length message packet read
  @retval EFI_TIMEOUT             HECI is not ready for communication
  @retval EFI_BUFFER_TOO_SMALL    The caller's buffer was not large enough
  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this message through this HECI
**/
typedef
EFI_STATUS
(EFIAPI *HECI_READ_MESSAGE) (
  IN      HECI_DEVICE             HeciDev,
  IN      UINT32                  Blocking,
  IN      UINT32                  *MessageBody,
  IN OUT  UINT32                  *Length
  );

/**
  Function sends one message (of any length) through the HECI circular buffer.

  @param[in] HeciDev              The HECI device to be accessed.
  @param[in] *Message             Pointer to the message data to be sent.
  @param[in] Length               Length of the message in bytes.
  @param[in] HostAddress          The address of the host processor.
  @param[in] MEAddress            Address of the ME subsystem the message is being sent to.

  @retval EFI_SUCCESS             One message packet sent.
  @retval EFI_DEVICE_ERROR        Failed to initialize HECI
  @retval EFI_TIMEOUT             HECI is not ready for communication
  @retval EFI_UNSUPPORTED         Current ME mode doesn't support send this message through this HECI
**/
typedef
EFI_STATUS
(EFIAPI *HECI_SEND_MESSAGE) (
  IN      HECI_DEVICE             HeciDev,
  IN      UINT32                  *Message,
  IN      UINT32                  Length,
  IN      UINT8                   HostAddress,
  IN      UINT8                   MEAddress
  );

/**
  Reset the HECI Controller with algorithm defined in the RS -
  Intel(R) Management Engine - Host Embedded Controller
  Interface Hardware Programming Specification (HPS)

  @param[in] HeciDev              The HECI device to be accessed.

  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_SUCCESS             Interface reset
**/
typedef
EFI_STATUS
(EFIAPI *HECI_RESET) (
  IN      HECI_DEVICE            HeciDev
  );

/**
  Initialize the HECI Controller with algorithm defined in the
  RS - Intel(R) Management Engine - Host Embedded Controller
  Interface Hardware Programming Specification (HPS).
  Determines if the HECI device is present and, if present,
  initializes it for use by the BIOS.

  @param[in] HeciDev              The HECI device to be accessed.

  @retval EFI_SUCCESS             HECI device is present and initialized
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
typedef
EFI_STATUS
(EFIAPI *HECI_INIT) (
  IN  HECI_DEVICE                 HeciDev
  );

/**
  Re-initialize the HECI Controller with algorithm defined in the RS - Intel(R) Management Engine
  - Host Embedded Controller Interface Hardware Programming Specification (HPS).
  Heci Re-initializes it for Host

  @param[in] HeciDev              The HECI device to be accessed.

  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_STATUS              Status code returned by ResetHeciInterface
**/
typedef
EFI_STATUS
(EFIAPI *HECI_REINIT) (
  IN  HECI_DEVICE                 HeciDev
  );

/**
  Reset Intel ME and timeout if Ready is not set after Delay timeout

  @param[in] HeciDev              The HECI device to be accessed.
  @param[in] Delay                Timeout value in microseconds

  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_SUCCESS             Me is ready
**/
typedef
EFI_STATUS
(EFIAPI *HECI_RESET_WAIT) (
  IN HECI_DEVICE                  HeciDev,
  IN UINT32                       Delay
  );

/**
  Get an abstract Intel ME State from Firmware Status Register.
  This is used to control BIOS flow for different Intel ME
  functions.
  The ME status information is obtained by sending HECI messages
  to Intel ME and is used both by the platform code and
  reference code. This will optimize boot time because system
  BIOS only sends each HECI message once. It is recommended to
  send the HECI messages to Intel ME only when ME mode is normal
  (Except for HMRFPO Disable Message) and ME State is NORMAL or
  RECOVERY (Suitable for AT and Kernel Messaging only).

  @param[out] MeStatus            Pointer for abstract status report
                                  @see MeState.h - Abstract ME status definitions.

  @retval EFI_SUCCESS             MeStatus copied
  @retval EFI_INVALID_PARAMETER   Pointer of MeStatus is invalid
**/
typedef
EFI_STATUS
(EFIAPI *HECI_GET_ME_STATUS) (
  OUT UINT32                      *Status
  )
;

/**
  Get an abstract ME operation mode from firmware status
  register. This is used to control BIOS flow for different
  Intel ME functions.

  @param[out] MeMode              Pointer for ME Mode report,
                                  @see MeState.h - Abstract ME Mode definitions.

  @retval EFI_SUCCESS             MeMode copied
  @retval EFI_INVALID_PARAMETER   Pointer of MeMode is invalid
**/
typedef
EFI_STATUS
(EFIAPI *HECI_GET_ME_MODE) (
  OUT UINT32                       *Mode
  );

/**
  HECI protocol provided for DXE phase
  The interface functions are for sending/receiving HECI messages between host and Intel ME subsystem.
  There is also support to control HECI Initialization and get Intel ME status.
**/
struct _HECI_PROTOCOL {
  HECI_SENDWACK              SendwAck;    ///< Send HECI message and wait for respond
  HECI_READ_MESSAGE          ReadMsg;     ///< Receive HECI message
  HECI_SEND_MESSAGE          SendMsg;     ///< Send HECI message
  HECI_RESET                 ResetHeci;   ///< Reset HECI device
  HECI_INIT                  InitHeci;    ///< Initialize HECI device
  HECI_RESET_WAIT            MeResetWait; ///< Intel ME Reset Wait Timer
  HECI_REINIT                ReInitHeci;  ///< Re-initialize HECI
  HECI_GET_ME_STATUS         GetMeStatus; ///< Get Intel ME Status register
  HECI_GET_ME_MODE           GetMeMode;   ///< Get Intel ME mode
};

extern EFI_GUID gHeciProtocolGuid;

#endif // _EFI_HECI_H
