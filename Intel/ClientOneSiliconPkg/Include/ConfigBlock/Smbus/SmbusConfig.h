/** @file
  Smbus policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#ifndef _SMBUS_CONFIG_H_
#define _SMBUS_CONFIG_H_

#define SMBUS_PREMEM_CONFIG_REVISION 1
extern EFI_GUID gSmbusPreMemConfigGuid;

#pragma pack (push,1)

#define PCH_MAX_SMBUS_RESERVED_ADDRESS 128

///
/// The SMBUS_CONFIG block lists the reserved addresses for non-ARP capable devices in the platform.
///
typedef struct {
  /**
    Revision 1: Init version
  **/
  CONFIG_BLOCK_HEADER   Header;         ///< Config Block Header
  /**
    This member describes whether or not the SMBus controller of PCH should be enabled.
    0: Disable; <b>1: Enable</b>.
  **/
  UINT32  Enable             :  1;
  UINT32  ArpEnable          :  1;      ///< Enable SMBus ARP support, <b>0: Disable</b>; 1: Enable.
  UINT32  DynamicPowerGating :  1;      ///< <b>(Test)</b> <b>Disable</b> or Enable Smbus dynamic power gating.
  ///
  /// <b>(Test)</b> SPD Write Disable, 0: leave SPD Write Disable bit; <b>1: set SPD Write Disable bit.</b>
  /// For security recommendations, SPD write disable bit must be set.
  ///
  UINT32  SpdWriteDisable    :  1;
  UINT32  SmbAlertEnable     :  1;      ///< Enable SMBus Alert pin (SMBALERT#). 0: <b>Disabled<b>, 1: Enabled.
  UINT32  RsvdBits0          : 27;      ///< Reserved bits
  UINT16  SmbusIoBase;                  ///< SMBUS Base Address (IO space). Default is <b>0xEFA0</b>.
  UINT8   Rsvd0;                        ///< Reserved bytes
  UINT8   NumRsvdSmbusAddresses;        ///< The number of elements in the RsvdSmbusAddressTable.
  /**
    Array of addresses reserved for non-ARP-capable SMBus devices.
  **/
  UINT8   RsvdSmbusAddressTable[PCH_MAX_SMBUS_RESERVED_ADDRESS];
} PCH_SMBUS_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _SMBUS_CONFIG_H_
