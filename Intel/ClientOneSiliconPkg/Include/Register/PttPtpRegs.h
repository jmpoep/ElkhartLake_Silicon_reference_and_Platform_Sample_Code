/** @file
  Register definitions for PTT HCI (Platform Trust Technology - Host Controller Interface).

  Conventions:

  - Prefixes:
    Definitions beginning with "R_" are registers
    Definitions beginning with "B_" are bits within registers
    Definitions beginning with "V_" are meaningful values of bits within the registers
    Definitions beginning with "S_" are register sizes
    Definitions beginning with "N_" are the bit position

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

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

@par Specification
**/
#ifndef _PTT_HCI_REGS_H_
#define _PTT_HCI_REGS_H_


///
/// FTPM HCI register base address
///
#define R_PTT_HCI_BASE_ADDRESS             0xFED40000
#define R_PTT_TXT_STS_FTIF                 0xFED30800

///
/// FTIF ftpm present value
///
#define V_FTIF_FTPM_PRESENT                0x00070000

//
// FTPM HCI Control Area
//
#define R_PTT_LOCALITY_STATE                0x00
#define R_TPM_LOCALITY_CONTROL              0X08
#define R_TPM_LOCALITY_STATUS               0x0C
#define R_TPM_INTERFACE_ID                  0x30
#define R_CRB_CONTROL_EXT                   0x38
#define R_CRB_CONTROL_REQ                   0x40
#define R_CRB_CONTROL_STS                   0x44
#define R_CRB_CONTROL_CANCEL                0x48
#define R_CRB_CONTROL_START                 0x4C
#define R_CRB_CONTROL_INT                   0x50
#define R_CRB_CONTROL_CMD_SIZE              0x58
#define R_CRB_CONTROL_CMD_LOW               0x5C
#define R_CRB_CONTROL_CMD_HIGH              0x60
#define R_CRB_CONTROL_RESPONSE_SIZE         0x64
#define R_CRB_CONTROL_RESPONSE_ADDR         0x68
#define R_CRB_DATA_BUFFER                   0x80

//
// R_CRB_CONTROL_STS Bits
//
#define B_CRB_CONTROL_STS_TPM_STATUS             0x00000001 ///< BIT0
#define B_CRB_CONTROL_STS_TPM_IDLE               0x00000002 ///< BIT1

//
// R_CRB_CONTROL_REQ Bits
//
#define B_CRB_CONTROL_REQ_COMMAND_READY          0x00000001 ///< BIT0
#define B_CRB_CONTROL_REQ_GO_IDLE                0x00000002 ///< BIT1

//
// R_CRB_CONTROL_START Bits
//
#define B_CRB_CONTROL_START                      0x00000001 ///< BIT0

//
// R_TPM_LOCALITY_STATUS Bits
//
#define B_CRB_LOCALITY_STS_GRANTED               0x00000001 ///< BIT0
#define B_CRB_LOCALITY_STS_BEEN_SEIZED           0x00000002 ///< BIT1

//
// R_TPM_LOCALITY_CONTROL Bits
//
#define B_CRB_LOCALITY_CTL_REQUEST_ACCESS       0x00000001 ///< BIT0
#define B_CRB_LOCALITY_CTL_RELINQUISH           0x00000002 ///< BIT1
#define B_CRB_LOCALITY_CTL_SEIZE                0x00000004 ///< BIT2

//
// R_PTT_LOCALITY_STATE Bits
//
#define B_CRB_LOCALITY_STATE_TPM_ESTABLISHED    0x00000001 ///< BIT0
#define B_CRB_LOCALITY_STATE_LOCALITY_ASSIGNED  0x00000002 ///< BIT1
#define B_CRB_LOCALITY_STATE_REGISTER_VALID     0x00000080 ///< BIT7

//
// R_PTT_LOCALITY_STATE Mask Values
//
#define V_CRB_LOCALITY_STATE_ACTIVE_LOC_MASK    0x0000001C /// Bits [4:2]

//
// R_PTT_RESERVED
//
#define B_PTT_RESERVED_BIT    0x00080000 /// Bit [19]

//
// Value written to R_PTT_HCI_CMD and CA_START
// to indicate that a command is available for processing
//
#define V_PTT_HCI_COMMAND_AVAILABLE_START  0x00000001
#define V_PTT_HCI_COMMAND_AVAILABLE_CMD    0x00000000
#define V_PTT_HCI_BUFFER_ADDRESS_RDY       0x00000003

///
/// Ignore bit setting mask for WaitRegisterBits
///
#define V_PTT_HCI_IGNORE_BITS              0x00000000

///
/// All bits clear mask for WaitRegisterBits
///
#define V_PTT_HCI_ALL_BITS_CLEAR           0xFFFFFFFF
#define V_PTT_HCI_START_CLEAR              0x00000001

///
/// Max FTPM command/response buffer length
///
#define S_PTT_HCI_CRB_LENGTH               3968 ///< 0xFED40080:0xFED40FFF = 3968 Bytes

#endif
