/** @file
 Software Guard Setup Variables and Structures

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _SOFTWARE_GUARD_SETUP_DATA_H_
#define _SOFTWARE_GUARD_SETUP_DATA_H_

#define EPC_BIOS           L"EPCBIOS"
#define EPC_OS_CTRL        L"EPCSW"
#define SGX_POLICY         L"SOFTWAREGUARDSTATUS"

#pragma pack(1)

///
/// EPC data structure for OS Variable
///
typedef struct {
  UINT32 RequestedEpcSize; ///< Requested EPC size in MB
} EPC_OS_CONFIG;

///
/// EPC data structure for BIOS Variable
///
typedef struct _EPC_BIOS_CONFIG {
    UINT32  SupportedPrmBins; ///< supported EPC bins; Bit 0- Support for 1 MB, 1- Support for 2 MB, 2- Support for 4 MB,
    UINT32  MaxEpcSize;       ///< Maximum EPC size supported by platform in MB
    UINT32  AllocatedEpcSize; ///< Allocated EPC size in MB
    UINT32  EpcMap[32];       ///< Mapping of PRM size to corresponding EPC size
} EPC_BIOS_CONFIG;

///
/// Data structure for SGX Policy Status
/// The presence of this variable implies that SGX is supported
/// For backward compatibility:
/// Absence of this variable implies that SGX is supported and defaulted to 'Software Controlled'
///
typedef struct {
  /**
  Bitmap of SGX Policy setting
   - BIT[1:0]: SgxStatus
      - 00b = Disabled.
      - 01b = Enabled.
      - 10b = Software Controlled.
      - 11b = Reserved.
  **/
  UINT8 SgxStatus:2;
  UINT8 Reserved:6;  ///< Reserved 6 bits
} SOFTWARE_GUARD_STATUS;

#pragma pack()

#endif
