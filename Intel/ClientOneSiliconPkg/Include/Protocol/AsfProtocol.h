/** @file
  Definition of Alert Standard Format (ASF) 2.0

@copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2019 Intel Corporation.

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
#ifndef _ASF_PROTOCOL_H_
#define _ASF_PROTOCOL_H_

#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/AlertStandardFormatTable.h>
#include <AsfMsgs.h>

typedef enum {
  Byte1,
  Byte2
} OPTION_INDEX;


///
/// Sub-Command Attributes
///
#define ASF_BOOT_OPTIONS_PRESENT      0x16
#define ASF_BOOT_OPTIONS_NOT_PRESENT  0x17

///
/// ASF Internet Assigned Numbers Authority Manufacturer ID
/// (The firmware sends 0XBE110000 for decimal value 4542)
///
#define ASF_INDUSTRY_IANA             0x000011BE
#define ASF_INDUSTRY_CONVERTED_IANA   INTEL_IANA_SWAP32 (ASF_INDUSTRY_IANA)  ///< 0XBE110000, received from ME FW

///
/// Intel specific definitions start
///

///
/// Intel Internet Assigned Numbers Authority Manufacturer ID
/// (The firmware sends 0x57010000 for decimal value 343)
///
#define INTEL_IANA_SWAP32(x)      ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | \
                                    (((x) & 0xff0000) >> 8) | (((x) & 0xff000000) >> 24))
#define ASF_INTEL_IANA            0x00000157
#define ASF_INTEL_CONVERTED_IANA  INTEL_IANA_SWAP32 (ASF_INTEL_IANA)  ///< 0X57010000, received from ME

///
/// Intel OEM Special Command
///
#define ASF_INTEL_OEM_CMD                  0xC1

///
/// Intel OEM Parameters Byte1 values
///
#define USE_SOL                            BIT0 ///< 0000 0001 - bit 0, use SOL on the next boot

///
/// Intel Special Command Parameter Low byte values
///
#define USE_STORAGE_REDIR                  BIT0  ///< 0000 0001 - bit 0 High Byte will be used to indicate the channel
#define ENFORCE_SECURE_BOOT                BIT1  ///< 0000 0010 - bit 1 Enforce secure boot over Storage Redirection
#define REFLASH_BIOS                       BIT2  ///< 0000 0100 - bit 2
#define BIOS_SETUP                         BIT3  ///< 0000 1000 - bit 3
#define BIOS_PAUSE                         BIT4  ///< 0001 0000 - bit 4
#define USE_KVM                            BIT5  ///< 0010 0000 - bit 5
#define ENABLE_SECURE_ERASE                BIT6  ///< 0100 0000 - bit 6

///
/// Intel Special Command Parameter High byte values
///
/**
  00: SRoU is connected to CD/DVD device
  01: SRoU is connected to floppy device
**/
#define STORAGE_REDIRECTION_BOOT_DEVICE_MASK   (BIT1 | BIT0)

///
/// Intel specific definitions end
///

///
/// Alert Standard Format Protocol
/// This protocol provides interfaces to get ASF Boot Options
/// HECI protocol is consumed and used to send ASF messages and receive ASF Boot Options
///
typedef struct {
  ASF_BOOT_OPTIONS        AsfBootOptions;
} ALERT_STANDARD_FORMAT_PROTOCOL;

extern EFI_GUID gAlertStandardFormatProtocolGuid;

#endif
