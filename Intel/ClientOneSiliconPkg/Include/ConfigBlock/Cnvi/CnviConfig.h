/** @file
  CNVi policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#ifndef _CNVI_CONFIG_H_
#define _CNVI_CONFIG_H_

#define CNVI_CONFIG_REVISION 1
extern EFI_GUID gCnviConfigGuid;

#pragma pack (push,1)

/**
  CNVi Mode options
**/
typedef enum {
  CnviModeDisabled = 0,
  CnviModeAuto
} CNVI_MODE;


/**
  CNVi signals pin muxing settings. If signal can be enable only on a single pin
  then this parameter is ignored by RC. Refer to GPIO_*_MUXING_CNVI_* in GpioPins*.h
  for supported settings on a given platform
**/
typedef struct {
  UINT32 RfReset; ///< RF_RESET# Pin mux configuration. Refer to GPIO_*_MUXING_CNVI_RF_RESET_*
  UINT32 Clkreq;  ///< CLKREQ Pin mux configuration. Refer to GPIO_*_MUXING_CNVI_*_CLKREQ_*
} CNVI_PIN_MUX;

/**
  The CNVI_CONFIG block describes the expected configuration of the CNVi IP.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;      ///< Config Block Header
  /**
    This option allows for automatic detection of Connectivity Solution.
    Auto Detection assumes that CNVi will be enabled when available;
    Disable allows for disabling CNVi.
    CnviModeDisabled = Disabled,
    <b>CnviModeAuto = Auto Detection</b>
  **/
  UINT32 Mode                  :  1;
  UINT32 BtCore                :  1; ///< The option to turn ON or OFF the BT Core. 0: Disabled, <b>1: Enabled</b>
  /**
    The option to enable or disable BT Audio Offload.
    <b>0: Disabled</b>, 1: Enabled
    @note This feature only support with Intel(R) Wireless-AX 22560
  **/
  UINT32 BtAudioOffload        :  1;
  UINT32 RsvdBits              : 29;
  /**
    CNVi PinMux Configuration
    RESET#/CLKREQ to CRF, can have two alternative mappings, depending on board routing requirements.
  **/
  CNVI_PIN_MUX          PinMux;
} CNVI_CONFIG;

#pragma pack (pop)

#endif // _CNVI_CONFIG_H_
