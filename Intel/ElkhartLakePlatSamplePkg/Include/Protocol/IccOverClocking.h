/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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


#ifndef _ICC_OVERCLOCKING_H_
#define _ICC_OVERCLOCKING_H_

/* Types used by ICC LIB */

typedef enum _ICC_LIB_STATUS
{
        ICC_LIB_STATUS_SUCCESS,
        ICC_LIB_STATUS_INVALID_PARAMS,
        ICC_LIB_STATUS_INVALID_CLOCK_NUMBER,
        ICC_LIB_STATUS_CLOCK_NOT_FOUND,
        ICC_LIB_STATUS_INVALID_FREQ_VALUE,
        ICC_LIB_STATUS_FREQ_TOO_LOW,
        ICC_LIB_STATUS_FREQ_TOO_HIGH,
        ICC_LIB_STATUS_FREQ_MUST_HAVE_ZERO_SSC,
        ICC_LIB_STATUS_SSC_CHANGE_NOT_ALLOWED,
        ICC_LIB_STATUS_INVALID_SSC_MODE,
        ICC_LIB_STATUS_SSC_MODE_NOT_SUPPORTED,
        ICC_LIB_STATUS_SSC_OUT_OF_RANGE,
        ICC_LIB_STATUS_SSC_TOO_HIGH,
        ICC_LIB_STATUS_SSC_TOO_LOW,
        ICC_LIB_STATUS_SSC_CHANGE_NOT_ALLOWED_SSC_DISABLED,
        ICC_LIB_STATUS_DYNAMIC_CHANGE_NOT_ALLOWED,
        ICC_LIB_STATUS_INVALID_DMI_PEG_RATIO,
        ICC_LIB_STATUS_REGISTER_IS_LOCKED,
        ICC_LIB_STATUS_MEI_INITIALIZATION_FAILED,
        ICC_LIB_STATUS_MEI_CONNECTION_FAILED,
        ICC_LIB_STATUS_UNEXPECTED_FW_ERROR,
        ICC_LIB_STATUS_UNSUPPORTED_HW,
        ICC_LIB_STATUS_CLOCK_DISABLED_FAILED_PROGRAMMING,
        ICC_LIB_STATUS_FREQ_AND_SSC_NOT_MATCH,
        ICC_LIB_STATUS_WAITING_FOR_WARM_RESET,
        ICC_LIB_STATUS_NOT_ALLOWED_IN_USER_MODE,
        ICC_LIB_STATUS_TOO_MANY_CONNECTIONS,
        ICC_LIB_STATUS_INVALID_COOKIE,
        ICC_LIB_STATUS_DMI_PEG_RATIO_CHANGE_NOT_ALLOWED,
        ICC_LIB_STATUS_NO_USAGE_DEFINED_FOR_THE_CLOCK,
        ICC_LIB_STATUS_DATA_NOT_AVAILABLE,

        ICC_LIB_STATUS_UNSPECIFIED_ERROR                 = 0xFFFF
} ICC_LIB_STATUS;

    typedef enum _ICC_CLOCK_USAGE
    {
        ICC_CLOCK_USAGE_BCLK = 0,
        ICC_CLOCK_USAGE_DMI,
        ICC_CLOCK_USAGE_PEG,
        ICC_CLOCK_USAGE_PCIE,
        ICC_CLOCK_USAGE_PCI33,
        ICC_CLOCK_USAGE_RESERVED,
        ICC_CLOCK_USAGE_SATA,
        ICC_CLOCK_USAGE_USB3,
        ICC_CLOCK_USAGE_DISPLAY,
        ICC_CLOCK_USAGE_DISPLAY_NON_SPREAD,
        ICC_CLOCK_USAGE_27MHZ_DOWN_GFX,
        ICC_CLOCK_USAGE_DISPLAY_VGA,
        ICC_CLOCK_USAGE_USB_LEGACY,
        ICC_CLOCK_USAGE_14_31818_MHZ
    } ICC_CLOCK_USAGE;

// @brief Defines a generic version structure used in the software build process.
typedef struct _ICC_LIB_VERSION
{
    UINT16      Major;
    UINT16      Minor;
    UINT16      Hotfix;
    UINT16      Build;
} ICC_LIB_VERSION;

typedef UINT32 ICC_CLOCK_FREQUENCY;

typedef UINT16 ICC_CLOCK_USAGE_MASK;

typedef struct _ICC_CLOCK_RANGES
{
    ICC_CLOCK_FREQUENCY FrequencyMin;
    ICC_CLOCK_FREQUENCY FrequencyMax;
    UINT8 SscChangeAllowed;
    UINT8 SscUpAllowed;
    UINT8 SscCenterAllowed;
    UINT8 SscDownAllowed;
    UINT8 SscPercentMax;
    // that field is actually still a bit mask, but usually applications will never use it.
    ICC_CLOCK_USAGE_MASK UsageMask;
    UINT8 SscHaltAllowed;
} ICC_CLOCK_RANGES;

typedef UINT8 ICC_CLOCK_ID;

typedef UINT32 ICC_CLOCK_ID_MASK;

typedef enum _ICC_RECORD_INVALIDATION_REASON
{
    ICC_LIB_RIR_RECORD_VALID            = 0,
    ICC_LIB_RIR_AC_POWER_LOSS,
  ICC_LIB_RIR_BOOT_WITH_DEFAULT,
    ICC_LIB_RIR_PLATFORM_BOOT_TIMEOUT,
    ICC_LIB_RIR_WDT_EXPIRED,
    ICC_LIB_RIR_RESERVED,
    ICC_LIB_RIR_INVALIDATE_BY_REQUEST,
    ICC_LIB_RIR_FW_BUG
} ICC_RECORD_INVALIDATION_REASON;

#endif /* _ICC_OVERCLOCKING_H_ */
