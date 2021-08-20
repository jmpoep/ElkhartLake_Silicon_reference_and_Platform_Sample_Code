/** @file
  VMD PEI policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#ifndef _VMD_PEI_CONFIG_H_
#define _VMD_PEI_CONFIG_H_

#include <ConfigBlock.h>

#define VMD_PEI_CONFIG_REVISION 1
extern EFI_GUID gVmdPeiConfigGuid;

#pragma pack (push,1)


///
/// The VMD_PEI_CONFIG block describes VMD settings.
///
typedef struct {
  CONFIG_BLOCK_HEADER  Header;               ///< Offset 0-27 Config Block Header
  UINT8                VmdEnable;            ///< Offset 28 This field used to enable VMD controller 1=Enable and 0=Disable (default)
  UINT8                VmdPortAEnable;       ///< Offset 29 This field used to enable VMD portA Support  1=Enable and 0=Disable (default)
  UINT8                VmdPortBEnable;       ///< Offset 30 This field used to enable VMD portB Support  1=Enable and 0=Disable (default)
  UINT8                VmdPortCEnable;       ///< Offset 31 This field used to enable VMD portC Support  1=Enable and 0=Disable (default) .
  UINT8                VmdPortDEnable;       ///< Offset 32 This field used to enable VMD portD Support  1=Enable and 0=Disable (default) .
  UINT8                VmdCfgBarSz;          ///< Offset 33 This is used to set the VMD Config Bar Size.
  UINT8                VmdCfgBarAttr;        ///< Offset 34 This is used to set VMD Config Bar Attributes 0: VMD_32BIT_NONPREFETCH, 1: VMD_64BIT_NONPREFETCH, 2: VMD_64BIT_PREFETCH(Default)
  UINT8                VmdMemBarSz1;         ///< Offset 35 This is used to set the VMD Mem Bar1 size.
  UINT8                VmdMemBar1Attr;       ///< Offset 36 This is used to set VMD Mem Bar1 Attributes 0: VMD_32BIT_NONPREFETCH(Default) 1: VMD_64BIT_NONPREFETCH, 2: VMD_64BIT_PREFETCH
  UINT8                VmdMemBarSz2;         ///< Offset 37 This is used to set the VMD Mem Bar2 size.
  UINT8                VmdMemBar2Attr;       ///< Offset 38 This is used to set VMD Mem Bar2 Attributes 0: VMD_32BIT_NONPREFETCH 1: VMD_64BIT_NONPREFETCH(Default), 2: VMD_64BIT_PREFETCH
  UINT8                Rsvd;                 ///< Offset 39 Reserved for future use
} VMD_PEI_CONFIG;

#pragma pack (pop)

#endif /* _VMD_PEI_PREMEM_CONFIG_H_ */
