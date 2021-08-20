/** @file
  Header file for Config Block Lib implementation

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

@par Specification
**/

#ifndef _CONFIG_BLOCK_H_
#define _CONFIG_BLOCK_H_
#pragma pack (push,1)
//
// These definitions are only for MiniBios: Begin
//
///
/// Describes the format and size of the data inside the HOB.
/// All HOBs must contain this generic HOB header.
///
typedef struct {
  ///
  /// Identifies the HOB data structure type.
  ///
  UINT16    HobType;
  ///
  /// The length in bytes of the HOB.
  ///
  UINT16    HobLength;
  ///
  /// This field must always be set to zero.
  ///
  UINT32    Reserved;
} EFI_HOB_GENERIC_HEADER;

///
/// Allows writers of executable content in the HOB producer phase to
/// maintain and manage HOBs with specific GUID.
///
typedef struct {
  ///
  /// The HOB generic header. Header.HobType = EFI_HOB_TYPE_GUID_EXTENSION.
  ///
  EFI_HOB_GENERIC_HEADER      Header;
  ///
  /// A GUID that defines the contents of this HOB.
  ///
  EFI_GUID                    Name;
  //
  // Guid specific data goes here
  //
} EFI_HOB_GUID_TYPE;

#define EFI_HOB_TYPE_GUID_EXTENSION       0x0004

//
// These definitions are only for MiniBios: End
//


///
/// Config Block Header
///
typedef struct _CONFIG_BLOCK_HEADER {
  EFI_HOB_GUID_TYPE GuidHob;                      ///< Offset 0-23  GUID extension HOB header
  UINT8             Revision;                     ///< Offset 24    Revision of this config block
  UINT8             Attributes;                   ///< Offset 25    The main revision for config block
  UINT8             Reserved[2];                  ///< Offset 26-27 Reserved for future use
} CONFIG_BLOCK_HEADER;

///
/// Config Block
///
typedef struct _CONFIG_BLOCK {
  CONFIG_BLOCK_HEADER            Header;          ///< Offset 0-27  Header of config block
  //
  // Config Block Data
  //
} CONFIG_BLOCK;

///
/// Config Block Table Header
///
typedef struct _CONFIG_BLOCK_TABLE_STRUCT {
  CONFIG_BLOCK_HEADER            Header;          ///< Offset 0-27  GUID number for main entry of config block
  UINT8                          Rsvd0[2];        ///< Offset 28-29 Reserved for future use
  UINT16                         NumberOfBlocks;  ///< Offset 30-31 Number of config blocks (N)
  UINT32                         AvailableSize;   ///< Offset 32-35 Current config block table size
///
/// Individual Config Block Structures are added here in memory as part of AddConfigBlock()
///
} CONFIG_BLOCK_TABLE_HEADER;
#pragma pack (pop)

#endif // _CONFIG_BLOCK_H_

