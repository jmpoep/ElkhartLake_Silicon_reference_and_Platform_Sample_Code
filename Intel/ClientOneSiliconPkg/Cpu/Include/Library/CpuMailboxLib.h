/** @file
  Header file for Cpu Mailbox Lib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

#ifndef _CPU_MAILBOX_LIB_H_
#define _CPU_MAILBOX_LIB_H_

//
//  Mailbox Related Definitions
//
#define MAILBOX_TYPE_PCODE                    0x00000001
#define MAILBOX_TYPE_OC                       0x00000002
#define MAILBOX_TYPE_VR_MSR                   0x00000003
#define PCODE_MAILBOX_INTERFACE_OFFSET        0x5DA4
#define PCODE_MAILBOX_DATA_OFFSET             0x5DA0
#define BIOS_POST_CODE_PCU_CNL_REG            0x00005824
#define OC_MAILBOX_MSR                        0x00000150
#define VR_MAILBOX_MSR_INTERFACE              0x00000607
#define VR_MAILBOX_MSR_DATA                   0x00000608


#define READ_PEG_CRIO_CR                                     0x00000029
#define WRITE_PEG_CRIO_CR                                    0x0000002A
#define N_MAILBOX_TARGET_IO_BLOCK_OFFSET                     0x18

#define MAILBOX_BIOS_CMD_READ_C6DRAM_CONFIG                  0x0000001C
#define B_MAILBOX_BIOS_ALLOW_C6DRAM                          BIT0
#define B_MAILBOX_C6DRAM_SUPPORTED                           BIT1
#define MAILBOX_BIOS_CMD_WRITE_C6DRAM_CONFIG                 0x0000001D
#define MAILBOX_EDRAM_RATIO_CMD                              0x0000001E
#define EDRAM_RATIO_CMD_MASK                                 0x0000003F
#define MAILBOX_BCLK_FREQUENCY_CMD                           0x00000005
#define MAILBOX_READ_OC_TJ_MAX_OFFSET_CMD                    0x00000037
#define MAILBOX_WRITE_OC_TJ_MAX_OFFSET_CMD                   0x00000137

#define MAILBOX_BIOS_CMD_CRASHLOG_CONFIG_CMD                 0x0000003E
//
// HwP Misc Functions
//
#define MAILBOX_CMD_READ_AUTONOMOUS_PARAMS                   0x00000010
#define MAILBOX_CMD_WRITE_AUTONOMOUS_PARAMS                  0x00000011
#define MAILBOX_BIOS_CMD_READ_PCU_MISC_CONFIG                0x00000005
#define MAILBOX_BIOS_CMD_WRITE_PCU_MISC_CONFIG               0x00000006
#define MAILBOX_BIOS_CMD_READ_OOB_EPB_CONTROL                0x0000022B
#define MAILBOX_BIOS_CMD_WRITE_OOB_EPB_CONTROL               0x0000032B

#ifndef MAILBOX_WAIT_TIMEOUT
#define MAILBOX_WAIT_TIMEOUT  1000  ///< 1 millisecond
#endif
#ifndef MAILBOX_WAIT_STALL
#define MAILBOX_WAIT_STALL    1     ///< 1 microsecond
#endif
#ifndef MAILBOX_READ_TIMEOUT
#define MAILBOX_READ_TIMEOUT  10    ///< 10 microseconds
#endif

//
//  Pcode Mailbox completion codes
//
#define PCODE_MAILBOX_CC_SUCCESS                      0
#define PCODE_MAILBOX_CC_ILLEGAL_CMD                  1
#define PCODE_MAILBOX_CC_TIMEOUT                      2
#define PCODE_MAILBOX_CC_ILLEGAL_DATA                 3
#define PCODE_MAILBOX_CC_EDRAM_NOT_FUNCTIONAL         4
#define PCODE_MAILBOX_CC_ILLEGAL_VR_ID                5
#define PCODE_MAILBOX_CC_VR_INTERFACE_LOCKED          6
#define PCODE_MAILBOX_CC_VR_ERROR                     7
#define PCODE_MAILBOX_CC_EDRAM_CURRENTLY_UNAVAILABLE  0xA

///
/// VR Topology Data structure containing the address and en/dis information
/// for all SVID VR domains
///
typedef union VR_TOPOLOGY_DATA {
  UINT32 VrTopology;              ///< All bit fields as a 32-bit value.
  ///
  /// Individual bit fields.
  ///
  struct {
    UINT32 VrSaAddress      : 4;  ///< SA VR address
    UINT32 VrSaSvidType     : 1;  ///< SA VR Type. 1 - No SVID VR, 0 - SVID VR
    UINT32 VrIaAddress      : 4;  ///< IA VR address
    UINT32 VrIaSvidType     : 1;  ///< IA VR Type. 1 - No SVID VR, 0 - SVID VR
    UINT32 VrRingAddress    : 4;  ///< Ring VR address
    UINT32 VrRingSvidType   : 1;  ///< Ring VR Type. 1 - No SVID VR, 0 - SVID VR
    UINT32 VrGtAddress      : 4;  ///< GT VR address
    UINT32 VrGtSvidType     : 1;  ///< GT VR Type. 1 - No SVID VR, 0 - SVID VR
    UINT32 Reserved         : 5; ///< Reserved
    UINT32 VrFivrAddress    : 4;  ///< FIVR VR address
    UINT32 VrFivrSvidType   : 1;  ///< FIVR VR Type. 1 - No SVID VR, 0 - SVID VR
    UINT32 SvidDisable      : 1;  ///< Asserted when no SVID VR connected
    UINT32 PsysImonDisable  : 1;  ///< Imon Enable. 1 - Disable, 0 - Enable
  } Fields;
} VR_TOPOLOGY_DATA;

///
/// Expanded Overclocking Mailbox interface defintion, contains command id/completion code,
/// input parameters and the run/busy bit
///
typedef union _OC_MAILBOX_INTERFACE {
  UINT32 InterfaceData;          ///< All bit fields as a 32-bit value.
  ///
  /// Individual bit fields.
  ///
  struct {
    UINT8 CommandCompletion : 8; ///< Command ID and completion code
    UINT8 Param1            : 8; ///< Parameter 1, generally used to specify the CPU Domain ID
    UINT8 Param2            : 8; ///< Parameter 2, only current usage is as a core index for ratio limits message
    UINT8 Reserved          : 7; ///< Reserved for future use
    UINT8 RunBusy           : 1; ///< Run/Busy bit. This bit is set by BIOS to indicate the mailbox buffer is ready. pcode will clear this bit after the message is consumed.
  } Fields;
} OC_MAILBOX_INTERFACE;

///
///  Consolidated OC mailbox command structure containing both data and interface information
///
typedef struct _OC_MAILBOX_FULL {
  UINT32               Data;      ///< OC Mailbox read/write data
  OC_MAILBOX_INTERFACE Interface; ///< OC mailbox interface
} OC_MAILBOX_FULL;

///
///  Expanded Pcode Mailbox interface defintion, contains command id, address
///  and the run/busy bit
///
typedef union _PCODE_MAILBOX_INTERFACE {
  UINT32 InterfaceData;   ///< All bit fields as a 32-bit value.
  ///
  /// Individual bit fields.
  ///
  struct {
    UINT32 Command  : 8;  ///< Pcode mailbox command
    UINT32 Address  : 21; ///< Pcode mailbox address of command being issued
    UINT32 Reserved : 2;  ///< Reserved for future use
    UINT32 RunBusy  : 1;  ///< Run/Busy bit. This bit is set by BIOS to indicate the mailbox buffer is ready. pcode will clear this bit after the message is consumed.
  } Fields;
} PCODE_MAILBOX_INTERFACE;

///
///  Consolidated Pcode mailbox command structure containing both data and interface information
///
typedef struct _PCODE_MAILBOX_FULL {
  PCODE_MAILBOX_INTERFACE Interface; ///< Pcode mailbox interface
  UINT32                  Data;      ///< Pcode mailbox read/write data
} PCODE_MAILBOX_FULL;

/**
  Generic Mailbox function for mailbox write commands. This function will
  poll the mailbox interface for control, issue the write request, poll
  for completion, and verify the write was succussful.

  @param[in]  MailboxType     The type of mailbox interface to read. The Overclocking mailbox is defined as MAILBOX_TYPE_OC = 2.
  @param[in]  MailboxCommand  Overclocking mailbox command data
  @param[in]  MailboxData     Overclocking mailbox interface data
  @param[out] *MailboxStatus  Pointer to the mailbox status returned from pcode. Possible mailbox status values are:
                              - SUCCESS (0)               Command succeeded.
                              - OC_LOCKED (1)             Overclocking is locked. Service is read-only.
                              - INVALID_DOMAIN (2)        Invalid Domain ID provided in command data.
                              - MAX_RATIO_EXCEEDED (3)    Ratio exceeds maximum overclocking limits.
                              - MAX_VOLTAGE_EXCEEDED (4)  Voltage exceeds input VR's max voltage.
                              - OC_NOT_SUPPORTED (5)      Domain does not support overclocking.

  @retval EFI_STATUS
          - EFI_SUCCESS           Command succeeded.
          - EFI_INVALID_PARAMETER Invalid read data detected from pcode.
          - EFI_UNSUPPORTED       Unsupported MailboxType parameter.
**/
EFI_STATUS
EFIAPI
MailboxWrite (
  IN UINT32  MailboxType,
  IN UINT32  MailboxCommand,
  IN UINT32  MailboxData,
  OUT UINT32 *MailboxStatus
  );

/**
  Generic Mailbox function for mailbox read commands. This function will write
  the read request from MailboxType, and populate the read results in the MailboxDataPtr.

  @param[in]  MailboxType     The type of mailbox interface to read. The Overclocking mailbox is defined as MAILBOX_TYPE_OC = 2.
  @param[in]  MailboxCommand  Overclocking mailbox command data
  @param[out] *MailboxDataPtr Pointer to the overclocking mailbox interface data
  @param[out] *MailboxStatus  Pointer to the mailbox status returned from pcode. Possible mailbox status are
                              - SUCCESS (0)               Command succeeded.
                              - OC_LOCKED (1)             Overclocking is locked. Service is read-only.
                              - INVALID_DOMAIN (2)        Invalid Domain ID provided in command data.
                              - MAX_RATIO_EXCEEDED (3)    Ratio exceeds maximum overclocking limits.
                              - MAX_VOLTAGE_EXCEEDED (4)  Voltage exceeds input VR's max voltage.
                              - OC_NOT_SUPPORTED (5)      Domain does not support overclocking.

  @retval EFI_STATUS
          - EFI_SUCCESS           Command succeeded.
          - EFI_INVALID_PARAMETER Invalid read data detected from pcode.
          - EFI_UNSUPPORTED       Unsupported MailboxType parameter.

**/
EFI_STATUS
EFIAPI
MailboxRead (
  IN UINT32  MailboxType,
  IN UINT32  MailboxCommand,
  OUT UINT32 *MailboxDataPtr,
  OUT UINT32 *MailboxStatus
  );

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
  );
#endif
