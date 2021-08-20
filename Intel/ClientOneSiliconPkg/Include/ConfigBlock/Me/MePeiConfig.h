/** @file
  ME config block for PEI phase

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2020 Intel Corporation.

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
#ifndef _ME_PEI_CONFIG_H_
#define _ME_PEI_CONFIG_H_

#define ME_PEI_PREMEM_CONFIG_REVISION 1
extern EFI_GUID gMePeiPreMemConfigGuid;

#ifndef PLATFORM_POR
#define PLATFORM_POR  0
#endif
#ifndef FORCE_ENABLE
#define FORCE_ENABLE  1
#endif
#ifndef FORCE_DISABLE
#define FORCE_DISABLE 2
#endif

#pragma pack (push,1)

/**
  ME Pei Pre-Memory Configuration Structure.

  <b>Revision 1:</b>
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                 ///< Config Block Header
  UINT32 HeciTimeouts                     : 1;  ///< 0: Disable; <b>1: Enable</b> - HECI Send/Receive Timeouts.
  /**
    <b>(Test)</b>
    <b>0: Disabled</b>
       1: ME DID init stat 0 - Success
       2: ME DID init stat 1 - No Memory in Channels
       3: ME DID init stat 2 - Memory Init Error
  **/
  UINT32 DidInitStat                      : 2;
  /**
    <b>(Test)</b>
    <b>0: Set to 0 to enable polling for CPU replacement</b>
       1: Set to 1 will disable polling for CPU replacement
  **/
  UINT32 DisableCpuReplacedPolling        : 1;
  UINT32 SendDidMsg                       : 1;  ///< <b>(Test)</b> 0: Disable; <b>1: Enable</b> - Enable/Disable to send DID message.
  /**
    <b>(Test)</b>
    <b>0: ME BIOS will check each messages before sending</b>
       1: ME BIOS always sends messages without checking
  **/
  UINT32 DisableMessageCheck              : 1;
  /**
    <b>(Test)</b>
    The SkipMbpHob policy determines whether ME BIOS Payload data will be requested during boot
    in a MBP message. If set to 1, BIOS will send the MBP message with SkipMbp flag
    set causing CSME to respond with MKHI header only and no MBP data
    <b>0: ME BIOS will keep MBP and create HOB for MBP data</b>
       1: ME BIOS will skip MBP data
  **/
  UINT32 SkipMbpHob                       : 1;
  UINT32 HeciCommunication2               : 1;  ///< <b>(Test)</b> <b>0: Disable</b>; 1: Enable - Enable/Disable HECI2.
  UINT32 HeciCommunication4               : 2;  ///< <b>(Test)</b> <b>0: POR</b>; 1: Enable; 2: Disable - Enable/Disable HECI4.  
  UINT32 KtDeviceEnable                   : 1;  ///< <b>(Test)</b> 0: Disable; <b>1: Enable</b> - Enable/Disable Kt Device.
  UINT32 RsvdBits                         : 21; ///< Reserved for future use & Config block alignment
  UINT32 Heci1BarAddress;                       ///< HECI1 BAR address.
  UINT32 Heci2BarAddress;                       ///< HECI2 BAR address.
  UINT32 Heci3BarAddress;                       ///< HECI3 BAR address.
  UINT32 Heci4BarAddress;                       ///< HECI4 BAR address.
} ME_PEI_PREMEM_CONFIG;
#pragma pack (pop)


#define ME_PEI_CONFIG_REVISION 1
extern EFI_GUID gMePeiConfigGuid;

#pragma pack (push,1)

/**
  ME Pei Post-Memory Configuration Structure.

  <b>Revision 1:</b>
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                 ///< Config Block Header

  /**
    HECI3 state from Mbp for reference in S3 path only
    <b>0: Disabled</b>; 1: Enabled
  **/
  UINT32 Heci3Enabled                     : 1;
  UINT32 DisableD0I3SettingForHeci        : 1;  ///< <b>(Test)</b> <b>0: Disable</b>; 1: Enable - Enable/Disable D0i3 for HECI.
  /**
    Enable/Disable Me Unconfig On Rtc Clear. If enabled, BIOS will send MeUnconfigOnRtcClearDisable Msg with parameter 0.
    It will cause ME to unconfig if RTC is cleared.
    -    0: Disable
    - <b>1: Enable</b>
    -    2: Cmos is clear, status unkonwn
    -    3: Reserved
  **/
  UINT32 MeUnconfigOnRtcClear             : 2;
  UINT32 MctpBroadcastCycle               : 1;   ///< <b>(Test)</b> <b>0: Disable</b>; 1: Enable - Program registers for MCTP Cycle.
  UINT32 RsvdBits                         : 27;  ///< Reserved for future use & Config block alignment
} ME_PEI_CONFIG;

#pragma pack (pop)

#endif // _ME_PEI_CONFIG_H_
