/** @file
  This file provides P2SB public library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#ifndef _P2SB_LIB_H_
#define _P2SB_LIB_H_

/**
  Get P2SB PCI device number

  @retval PCI dev number
**/
UINT8
P2sbDevNumber (
  VOID
  );

/**
  Get P2SB PCI function number

  @retval PCI fun number
**/
UINT8
P2sbFuncNumber (
  VOID
  );

/**
  Get P2SB EPMASK setting
  Note: after end of pei this function can be used only in SMM

  @param[in]    EpMaskNum  EPMASK number

  @retval       EPMASKx setting
**/
UINT32
P2sbGetEpmask (
  IN UINT32  EpMaskNum
  );

/**
  Check P2SB EPMASK is locked
  Note: after end of pei this function can be used only in SMM

  @retval TRUE  P2SB EPMASK is locked
          FALSE P2SB EPMASK is not locked
**/
BOOLEAN
P2sbIsEpmaskLock (
  VOID
  );

#endif // _P2SB_LIB_H_
