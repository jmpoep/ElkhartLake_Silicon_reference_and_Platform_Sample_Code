/** @file
  Fsp related definitions

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification
**/

#ifndef __FSP_H__
#define __FSP_H__

//
// Fv Header
//
#define FVH_SIGINATURE_OFFSET         0x28
#define FVH_SIGINATURE_VALID_VALUE    0x4856465F  // valid signature:_FVH
#define FVH_HEADER_LENGTH_OFFSET      0x30
#define FVH_EXTHEADER_OFFSET_OFFSET   0x34
#define FVH_EXTHEADER_SIZE_OFFSET     0x10

//
// Ffs Header
//
#define FSP_HEADER_GUID_DWORD1        0x912740BE
#define FSP_HEADER_GUID_DWORD2        0x47342284
#define FSP_HEADER_GUID_DWORD3        0xB08471B9
#define FSP_HEADER_GUID_DWORD4        0x0C3F3527
#define FFS_HEADER_SIZE_VALUE         0x18

//
// Section Header
//
#define SECTION_HEADER_TYPE_OFFSET    0x03
#define RAW_SECTION_HEADER_SIZE_VALUE 0x04

//
// Fsp Header
//
#define FSP_HEADER_IMAGEBASE_OFFSET     0x1C
#define FSP_HEADER_TEMPRAMINIT_OFFSET   0x30

//
// Protected Mode Entry Point
//
#define PROTECTED_MODE_ENTRY_POINT_GUID_DWORD1  0x50626249
#define PROTECTED_MODE_ENTRY_POINT_GUID_DWORD2  0x746E456D
#define PROTECTED_MODE_ENTRY_POINT_GUID_DWORD3  0x6F507972
#define PROTECTED_MODE_ENTRY_POINT_GUID_DWORD4  0x00746E69

#endif
