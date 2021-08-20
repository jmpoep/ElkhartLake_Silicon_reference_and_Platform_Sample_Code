/** @file
  Header for ME type library

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _ME_TYPE_LIB_H_
#define _ME_TYPE_LIB_H_

///
/// Define all the types of CSME firmware
///
typedef enum {
  MeTypeUndef  = 0,
  MeTypeClient = 1,
  MeTypeSps    = 2,
  MeTypeMax
} ME_TYPE;

/**
  Get type of firmware running in ME

  @return One of ME_TYPE values is returned.

**/
ME_TYPE
MeTypeGet(
  VOID
  );

/**
  Verify type of firmware running in ME

  @return TRUE if it is client firmware running in ME, otherwise FALSE.

**/
#define MeTypeIsClient() (MeTypeGet() == MeTypeClient)

/**
  Verify type of firmware running in ME

  @return TRUE if it is SPS firmware running in ME, otherwise FALSE.

**/
#define MeTypeIsSps()    (MeTypeGet() == MeTypeSps)

/**
  Verify type of firmware running in ME

  @return TRUE if it is SPS recovery firmware running in ME, otherwise FALSE.

**/
BOOLEAN
MeTypeIsSpsRecovery(
  VOID
  );

#endif // _ME_TYPE_LIB_H_

