/**@file
  Pse Fw header and manifest struct header file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#ifndef _PSE_FW_STRUCT_H_
#define _PSE_FW_STRUCT_H_

#define   MAX_VALID_MANIFEST_ENTRIES        15
#define   MAX_COMP_NAME_STRING_SIZE         4                            ///< Maximum comp name string size in bytes
#define   MAX_VENDOR_NAME_STRING_SIZE       4                            ///< Maximum vendor name string size in bytes
#define   MAX_BUP_SIZE_FOR_CHECKSUM         0x3000                       ///< The Bup size should be no more than 12KB, if it exceeds 12KB, the checksum will only cover the first 12KB block of Bup.
#define   PSE_MEM_TSN_DATA_LOAD_ADDR        0x70008800
#define   PSE_GBE_SUB_REGION_COMP_NAME      "GBER"
#define   PSE_GBE_SUB_REGION_VENDOR_NAME    "INTL"

typedef struct {
  CHAR8                  CompName[MAX_COMP_NAME_STRING_SIZE];            ///< Name of the component
  CHAR8                  VendorName[MAX_VENDOR_NAME_STRING_SIZE];        ///< Vendor's name of the component
  UINT32                 CodeOffset;                                     ///< The offset of the module's binary block in Pse Fw
  UINT32                 ModuleSize;                                     ///< The size of the module's binary block in bytes
  UINT32                 LoadAddr;                                       ///< The internal physical address in PSE that the binary block of the module should be loaded to
  UINT32                 CompFlags;                                      ///< Reserved
  UINT32                 DebugLevel;                                     ///< Reserved
  UINT32                 TraceLevel;                                     ///< Reserved
} PSE_MANIFEST_ENTRY;

typedef struct {
  PSE_MANIFEST_ENTRY     ManifestEntry[MAX_VALID_MANIFEST_ENTRIES];
} PSE_MANIFEST;

typedef struct {
  UINT32                 Checksum;                                       ///< Checksum
  UINT32                 HeaderVersion;                                  ///< Version of the header structure
  UINT16                 BupOffset;                                      ///< Offset to the binary block of BringUp
  UINT16                 HeaderSize;                                     ///< Size of the header structure
  UINT32                 VecTblAddr;                                     ///< Address of the vector table of the PSE firmware
  UINT32                 Reserved;                                       ///< Reserved
  UINT32                 BupSize;                                        ///< Size of the BringUp
  UINT32                 ManifestVersion;                                ///< Version of the manifest structure
  UINT8                  ValidEntryNum;                                  ///< Count of the valid entries in the manifest table
  UINT8                  IccmLimit;                                      ///< ICCM limit in 64KB unit
  UINT16                 Misc;                                           ///< Miscellaneous opitons
} PSE_HEADER;

typedef struct {
  PSE_HEADER    PseHeader;
  PSE_MANIFEST  PseManifest;
} PSE_FW;

#endif // _PSE_FW_STRUCT_H_
