/** @file
  PEI Heci PPI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2016 Intel Corporation.

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
#ifndef _HECI_PPI_H_
#define _HECI_PPI_H_

#include <Protocol/HeciProtocol.h>

///
/// HECI PPI GUID
/// This PPI provides an interface to communicate with Intel ME in PEI phase
///

extern EFI_GUID gHeciPpiGuid;

///
/// Revision
///
#define HECI_PPI_REVISION  1

typedef struct _HECI_PPI  HECI_PPI;

///
/// HECI PPI
/// The interface functions are for sending/receiving HECI messages between host and Intel ME subsystem
/// in PEI phase
///
struct _HECI_PPI {
  HECI_SENDWACK               SendwAck;       ///< Send HECI message and wait for respond
  HECI_READ_MESSAGE           ReadMsg;        ///< Read message from HECI
  HECI_SEND_MESSAGE           SendMsg;        ///< Send message to HECI
  HECI_INIT                   InitializeHeci; ///< Init HECI
  HECI_GET_ME_STATUS          GetMeStatus;    ///< Get Intel ME Status register
  HECI_GET_ME_MODE            GetMeMode;      ///< Get Intel ME mode
};

#endif
