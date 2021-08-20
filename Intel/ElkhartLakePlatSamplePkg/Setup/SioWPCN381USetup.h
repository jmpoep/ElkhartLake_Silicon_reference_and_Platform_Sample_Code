/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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


#ifndef _WPCN381USETUP_H_
#define _WPCN381USETUP_H_
#ifdef __cplusplus
extern "C" {
#endif


  #pragma pack(1)

  //FDC Settings
  typedef struct {
    UINT8    FdcImplemented;
    UINT16    FdcBase1;
    UINT16    FdcBase2;
    UINT8    FdcIrq1;
    UINT8    FdcIrq2;
    UINT8    FdcDma1;
    UINT8    FdcDma2;
  } WPCN381U_FDC_V_DATA;

  typedef struct {
    UINT8    FdcEnable;
    UINT8    FdcPrsId;
    UINT8    FdcMode;
  } WPCN381U_FDC_NV_DATA;

  //COM A Settings
  typedef struct {
    UINT8    ComImplemented;
    UINT16    ComBase1;
    UINT16    ComBase2;
    UINT8    ComIrq1;
    UINT8    ComIrq2;
    UINT8    ComDma1;
    UINT8    ComDma2;
  } WPCN381U_COMA_V_DATA;

  typedef struct {
    UINT8    ComEnable;
    UINT8    ComPrsId;
    UINT8    ComMode;
  } WPCN381U_COMA_NV_DATA;


  //COM B Settings
  typedef struct {
    UINT8    ComImplemented;
    UINT16    ComBase1;
    UINT16    ComBase2;
    UINT8    ComIrq1;
    UINT8    ComIrq2;
    UINT8    ComDma1;
    UINT8    ComDma2;
  } WPCN381U_COMB_V_DATA;

  typedef struct {
    UINT8    ComEnable;
    UINT8    ComPrsId;
    UINT8    ComMode;
  } WPCN381U_COMB_NV_DATA;

  //LPT Settings
  typedef struct {
    UINT8    LptImplemented;
    UINT16    LptBase1;
    UINT16    LptBase2;
    UINT8    LptIrq1;
    UINT8    LptIrq2;
    UINT8    LptDma1;
    UINT8    LptDma2;
  }WPCN381U_LPT_V_DATA;

       typedef struct {
    UINT8    LptEnable;
    UINT8    LptPrsId;
    UINT8    LptMode;
  }WPCN381U_LPT_NV_DATA;


  #pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
