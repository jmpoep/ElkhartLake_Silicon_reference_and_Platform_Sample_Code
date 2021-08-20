/** @file
  Internal header of the Setup Component.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2019 Intel Corporation.

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

#define EVAL(a) a

#define TPM_SETUP_ITEM_CALLBACK_LIST_EX \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_DEVICE_SELECT,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM2_GOTO,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_GOTO,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_ENABLE,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_DISABLE,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_ACTIVATE,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_DEACTIVATE,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_FORCE_CLEAR,TpmOptionCallback),

#ifndef TPM_SETUP_ITEM_CALLBACK_LIST_EX
#define TPM_SETUP_ITEM_CALLBACK_LIST_EX \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_GOTO,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_ENABLE,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_DISABLE,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_ACTIVATE,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_DEACTIVATE,TpmOptionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TPM_FORCE_CLEAR,TpmOptionCallback),
#endif

#define SETUP_ITEM_CALLBACK_LIST_EX \
  EVAL(TPM_SETUP_ITEM_CALLBACK_LIST_EX) \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_ICC_PROFILE,IccProfileCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_ICC_RATIO2,IccCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_ICC_FREQ2,IccCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_ICC_FREQ3,IccCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_ICC_SPREAD2,IccCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_ICC_SPREAD3,IccCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RatioLimit1,CpuFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RatioLimit2,CpuFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RatioLimit3,CpuFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RatioLimit4,CpuFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RatioLimit5,CpuFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RatioLimit6,CpuFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RatioLimit7,CpuFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RatioLimit8,CpuFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_XeVoltage,OcFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_MEMINFO_PROFILE,OcFormMemoryTimingCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_CpuRatioLimit,CpuFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RING_MAX_OC_RATIO_LIMIT,OcFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_DTBT_SUPPORT,TbtFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_ITBT_SUPPORT,TbtFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_DTBT_CONTROLLER0_HOSTROUTER,TbtFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_DTBT_CONTROLLER0,TbtFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_DTBT_CONTROLLER1_HOSTROUTER,TbtFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_DTBT_CONTROLLER1, TbtFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_DTBT_CONTROLLER2, TbtFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TBT_VTD_SECURITY_ID, TBTSecurityCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TBT_OS_SELECTOR,TbtOsSelectorFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,TBT_OSSELECT_FORM_ID,TbtOsSelectorFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TBT_BOOT_ON,TbtFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TBT_USB_ON,TbtFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,TBT_SECURITY_LEVEL_KEY,TbtFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_LOW_POWER_S0_IDLE,LowPowerS0IdleEnableCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_EpochChange,EpochChangeCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_SgxEpoch1,SgxEpoch1CallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_SgxChange,SgxFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,MNG_STATE_KEY,MeFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,PTT_TRIGGER_FORM_OPEN_ACTION_KEY,MeFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,PLATFORM_DEBUG_CONSENT_KEY,DebugFormCallBackFunction), \
  ITEM_CALLBACK_EX(BOOT_FORM_SET_CLASS,0,KEY_CSM_STATE,CsmControlCallBack),\
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TjMaxOffset, OcFormCallBackFunction),\
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RING_MIN_RATIO_LIMIT,OcFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_RING_MAX_RATIO_LIMIT,OcFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_CORE_MAX_OC_RATIO_LIMIT,OcFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_SA_TCSS_XHCI_EN, TcssXhciCallback),\
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_ENABLE_THERMAL_FUN, ThermalFunctionCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_BCLK_RFI_FREQ0,IccCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_BCLK_RFI_FREQ1,IccCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_BCLK_RFI_FREQ2,IccCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_BCLK_RFI_FREQ3,IccCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_CNV_BT_AUDIO_OFFLOAD, CnvFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_SA_TCSS_ROOT_PORT_0EN, TcssPcieRootPortCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_SA_TCSS_ROOT_PORT_1EN, TcssPcieRootPortCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_SA_TCSS_ROOT_PORT_2EN, TcssPcieRootPortCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_SA_TCSS_ROOT_PORT_3EN, TcssPcieRootPortCallback), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_SdevXhciAcpiPathNameDevice1,VtioFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_SdevXhciAcpiPathNameDevice2,VtioFormCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_MCC_TSN_GBE_LINK_SPEED,TsnGbeLinkSpeedCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_PSE_TSN_GBE0_LINK_SPEED,TsnGbeLinkSpeedCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_PSE_TSN_GBE1_LINK_SPEED,TsnGbeLinkSpeedCallBackFunction), \
  ITEM_CALLBACK_EX(ADVANCED_FORM_SET_CLASS,0,KEY_TCC_MODE,TccModeCallBackFunction),
