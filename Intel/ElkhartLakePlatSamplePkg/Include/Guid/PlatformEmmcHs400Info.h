/** @file
  GUID used for Platform Emmc Hs400 Tuning Info NVRAM Data

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
#ifndef _PLATFORM_EMMC_HS400_TUNING_INFO_GUID_H_
#define _PLATFORM_EMMC_HS400_TUNING_INFO_GUID_H_

#define HS400_TUNING_DATA_VAR         L"Hs400TuningData"

/**
 This structure describes the variable to be set with the returned EMMC_TUNING_DATA
 from EMMC_TUNE protocol.
**/
typedef struct _PLATFORM_EMMC_TUNING_DATA {
  /**
    eMMC HS400 Data Validation Status
    0: HS400 Data is invalid, 1: HS400 Data is valid
  **/
  UINT8    Hs400DataValid;
  UINT8    Hs400RxStrobe1Dll;  ///< Rx Strobe Delay Control - Rx Strobe Delay DLL 1 (HS400 Mode)
  UINT8    Hs400TxDataDll;     ///< Tx Data Delay Control 1 - Tx Data Delay (HS400 Mode)
} PLATFORM_EMMC_TUNING_DATA;


#endif
