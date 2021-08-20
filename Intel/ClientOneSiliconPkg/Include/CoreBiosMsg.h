/** @file
  Core BIOS Messages

@copyright
  INTEL CONFIDENTIAL
  Copyright 2008 - 2019 Intel Corporation.

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
#ifndef CORE_BIOS_MSG_H
#define CORE_BIOS_MSG_H

#include <MkhiMsgs.h>

#pragma pack(1)

///
/// Host Address of Fixed Address MEI Header -
/// This is the logical address of the Host client of the message. This address
/// is assigned when the host client registers itself with the Host MEI driver.

/**
  Address 0 is statically allocated for MEI bus message protocol that assists in MEI bus
  enumeration, power management, error and other bus control functionality.
**/
#define BIOS_FIXED_HOST_ADDR                0
#define BIOS_ASF_HOST_ADDR                  1 ///< Statically allocated for host AMT/ASF message

///
/// ME Address of Fixed Address MEI Header -
/// This is the logical address of the Intel(R) ME client
/// of the message. This address is assigned during ME firmware initialization.
///
#define HECI_HBM_MESSAGE_ADDR               0x00
#define HECI_ASF_MESSAGE_ADDR               0x02
#define HECI_ISH_SERVICE_MESSAGE_ADDR       0x03
#define HECI_STORAGE_PROXY_MESSAGE_ADDR     0x06
#define HECI_MKHI_MESSAGE_ADDR              0x07
#define HECI_ICC_MESSAGE_ADDR               0x08
#define HECI_MCHI_MESSAGE_ADDR              0x09
#define HECI_HWA_MESSAGE_ADDR               0x0B
#define HECI_BIOS_STORAGE_MESSAGE_ADDR      0x0E
#define HECI_MAX_ME_FIXED_ADDR              0x1F  ///< Max ME address for fixed clients

//
// MKHI_CBM_GROUP_ID = 0x00
//

///
/// Reset request message data
///
typedef struct {
  UINT8 RequestOrigin;
  UINT8 ResetType;
} CBM_RESET_REQ_DATA;

///
/// Reset request MKHI message
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
  CBM_RESET_REQ_DATA  Data;
} CBM_RESET_REQ;

///
/// Reset request MKHI ack message
///
typedef struct {
  MKHI_MESSAGE_HEADER MkhiHeader;
} CBM_RESET_ACK;

//
// Enumerations used in Core BIOS Messages
//

//
// Reset Request Origin Codes.
//
#define CBM_RR_REQ_ORIGIN_BIOS_MEMORY_INIT 0x01
#define CBM_RR_REQ_ORIGIN_BIOS_POST        0x02
#define CBM_RR_REQ_ORIGIN_MEBX             0x03

//
// Reset Type Codes.
//
#define CBM_HRR_GLOBAL_RESET  0x01

//
// Reset Response Codes.
//
#define CBM_HRR_RES_REQ_NOT_ACCEPTED  0x01

#pragma pack()

#endif
