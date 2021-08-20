/** @file
  Header file for PEI SCI Init Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#ifndef _PEI_SCI_INIT_LIB_H_
#define _PEI_SCI_INIT_LIB_H_

#include <Ppi/SiPolicy.h>

#define SCI_DIAG_INTERFACE_VERSION   0x1
#define SCI_DIAG_INTERFACE_RESERVED  0xF
#define SCI_DRBL_CHECK_ATTEMPT       30
#define SCI_DRBL_DELAY               1000

//
// SCI Flags bit definitions
//
#define SCI_FLAGS_BIT_SOP  BIT4
#define SCI_FLAGS_BIT_EOP  BIT5
#define SCI_FLAGS_BIT_RB   BIT6
#define SCI_FLAGS_BIT_RT   BIT7

#define SCI_HOST_ADDRESS  0x1
#define SCI_ADDRESS       0x1

#define SCI_BOOT_COMPLETE         0x0206
#define SCI_BOOT_COMMAND_LENGTH   12    // Total number of byte
#define SCI_BOOT_RESPONSE_LENGTH  16    // Total number of byte

typedef enum {
  SciBiosCompleteSeq   = 0x01,
  SciMaxSeq            = 0xFF   // This is the last sequence
}SCI_MESSAGE_SEQ;

#pragma pack(1)
typedef struct {
  UINT8   Version   :4;
  UINT8   Reserved1 :4;
  UINT8   Flags;
  UINT8   Length;
  UINT8   Reserved2;
  UINT16  SeqNum;
  UINT8   HostAddr;
  UINT8   SciAddr;
  UINT16  Crc16;
  UINT16  Command;
}SCI_GENERIC_MB_HEADER;

typedef struct {
  SCI_GENERIC_MB_HEADER  MbHeader;
}SCI_BOOT_CMPL_COMMAND;

typedef struct {
  SCI_GENERIC_MB_HEADER  MbHeader;
  UINT16  ResponseCode;
  UINT16  Reserved;
}SCI_BOOT_CMPL_RESPONSE;
#pragma pack()

/**
  Query SCI boot status.

  @retval     BOOLEAN           TRUE if SCI boot successful, else FALSE
**/
BOOLEAN
SciBootCheck (
  VOID
  );

/**
  Notify SCI with BIOS boot complete message.

  @retval     BOOLEAN   TRUE if communication successful, else FALSE
**/
BOOLEAN
SciBiosBootComplete (
  VOID
  );

/**
  Initialize SCI device.

  @param[in] SiPolicy             The SI Policy PPI instance
**/
VOID
SciInit (
  IN  SI_POLICY_PPI      *SiPolicy
  );

#endif // _PEI_SCI_INIT_LIB_H_
