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

#define SETUP_ITEM_CALLBACK_LIST \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_SYS_TEMP_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_SYS_FAN_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_CPU_TEMP_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_CPU_FAN_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_AUX_TEMP_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_AUX_FAN_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_CPU_VCORE_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_3VCC_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_AVCC_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_VIN0_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_VIN1_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_VIN2_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,NCT_HWMON_VIN3_KEY,NctHwmonCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,THERMAL_SENSOR_1_KEY,HhmMobileCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,THERMAL_SENSOR_2_KEY,HhmMobileCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,THERMAL_SENSOR_3_KEY,HhmMobileCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,THERMAL_SENSOR_4_KEY,HhmMobileCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,THERMAL_SENSOR_5_KEY,HhmMobileCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,CPU_FAN_KEY,HhmMobileCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,PCH_DTS_TEMP_KEY,HhmMobileCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,TS_ON_DIMM0_TEMP_KEY,HhmMobileCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,TS_ON_DIMM1_TEMP_KEY,HhmMobileCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,SATA_DEVICE_KEY,SataDeviceCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,VOLT_1_5V_KEY,HhmCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,VOLT_3_3V_KEY,HhmCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,VOLT_5V_KEY,HhmCallBack), \
  ITEM_CALLBACK(ADVANCED_FORM_SET_CLASS,0,VOLT_12V_KEY,HhmCallBack), \
  ITEM_CALLBACK(MAIN_FORM_SET_CLASS,0,STM_REV_KEY,GetSTM32FwVersionCallback), \

