/** @file
  Header file for HD Audio configuration.

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

#ifndef _HDA_H_
#define _HDA_H_

enum PCH_HDAUDIO_VC_TYPE {
  HdaVc0 = 0,
  HdaVc1 = 1
};

enum PCH_HDAUDIO_DMIC_TYPE {
  HdaDmicDisabled = 0,
  HdaDmic2chArray = 1,
  HdaDmic4chArray = 2,
  HdaDmic1chArray = 3
};

typedef enum {
  HdaLinkFreq6MHz  = 0,
  HdaLinkFreq12MHz = 1,
  HdaLinkFreq24MHz = 2,
  HdaLinkFreq48MHz = 3,
  HdaLinkFreq96MHz = 4,
  HdaLinkFreqInvalid
} HDAUDIO_LINK_FREQUENCY;

typedef enum  {
  HdaIDispMode2T  = 0,
  HdaIDispMode1T  = 1,
  HdaIDispMode4T  = 2,
  HdaIDispMode8T  = 3,
  HdaIDispMode16T = 4,
  HdaIDispTModeInvalid
} HDAUDIO_IDISP_TMODE;

typedef enum {
  HdaLink      = 0,
  HdaIDispLink = 1,
  HdaDmic      = 2,
  HdaSsp       = 3,
  HdaSndw      = 4,
  HdaLinkUnsupported
} HDAUDIO_LINK_TYPE;

#endif
