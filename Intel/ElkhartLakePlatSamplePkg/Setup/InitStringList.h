/** @file
  Internal header of the Setup Component.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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

#ifndef _INIT_STRING_LIST_H_
#define _INIT_STRING_LIST_H_


#if  FixedPcdGetBool(PcdNat87393Present) == 1
#define NAT87393_STRINGS_INIT_LIST NatInitSioStrings,
#else
#define NAT87393_STRINGS_INIT_LIST
#endif

#ifdef SIO_WPCN381U
#define WPCN381U_STRINGS_INIT_LIST InitSioStrings_WPCN381U,
#else
#define WPCN381U_STRINGS_INIT_LIST
#endif

#define INIT_LIST \
  InitDebugStrings, \
  InitPciBusStrings, \
  InitCPUStrings, \
  InitSaStrings, \
  InitSBStrings, \
  InitAcpiStrings, \
  InitHhmMobileStrings, \
  InitMeInfo, \
  InitIccStrings, \
  InitOverClockStrings, \
  InitPlatformStrings, \
  InitReworkStrings, \
  InitConnectivityStrings, \
  InitBoardStrings, \
  InitBootTimeStrings, \
  WPCN381U_STRINGS_INIT_LIST \
  NAT87393_STRINGS_INIT_LIST \
//

#endif // _INIT_STRING_LIST_H_
