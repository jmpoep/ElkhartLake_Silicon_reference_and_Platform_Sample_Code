/** @file
  HECI Flow Protocol

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
#ifndef _HECI_FLOW_PROTOCOL_H
#define _HECI_FLOW_PROTOCOL_H

typedef struct _HECI_FLOW_PROTOCOL  HECI_FLOW_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *HECI_FLOW_SEND_AND_RECEIVE) (
  IN       HECI_DEVICE             HeciDev,
  IN OUT   VOID                    *Message,
  IN       UINT32                  Length,
  IN OUT   UINT32                  *RecLength,
  IN CONST EFI_GUID                *Guid
  );

typedef
EFI_STATUS
(EFIAPI *HECI_FLOW_SEND) (
  IN       HECI_DEVICE             HeciDev,
  IN OUT   VOID                    *Message,
  IN OUT   UINT32                  Length,
  IN CONST EFI_GUID                *Guid
  );

/*
  This protocol allows sending HECI messages, over a connection with flow control, to CSME clients
  identified by GUID rather than hardcoded address. This simple API wraps all connection-related complexity,
  such as search for GUIDs, establishing connections, flow control token management and disconnection.
  HECI_FLOW_PROTOCOL is an extension of HECI_PROTOCOL. They can be used together, at the same time.
  Limitation:
  Except for flow control tokens, no response is expected for Send and only a single response message is expected for
  SendAndReceive. It is not allowed to use HECI_FLOW_PROTOCOL to create connections that will result in CSME sending
  more messages than that. Unexpected response message will not be consumed and will jam the underlying HECI_PROTOCOL.
*/
struct _HECI_FLOW_PROTOCOL {
  HECI_FLOW_SEND_AND_RECEIVE SendAndReceive; ///< Send HECI message with flow control and wait for response
  HECI_FLOW_SEND             Send;           ///< Send HECI message with flow control, do not expect response
};

extern EFI_GUID gHeciFlowProtocolGuid;

#endif // _HECI_FLOW_PROTOCOL_H
