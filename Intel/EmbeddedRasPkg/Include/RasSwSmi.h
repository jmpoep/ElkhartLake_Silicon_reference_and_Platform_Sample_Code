/** @file
  RAS SW SMI Input Values.
  Every value used in the RAS package to register a SW SMI dispatch function is
  listed in this file. These values are used to initialize SwSmiInputValue in
  the EFI_SMM_SW_REGISTER_CONTEXT structure, which is passed to Register.

  @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation. <BR>

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary    and
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
**/

#ifndef _RAS_SW_SMI_H_
#define _RAS_SW_SMI_H_

#define RAS_SW_SMI_ADDRESS_TRANSLATION_DSM  0x97
#define RAS_SW_SMI_EINJ_IIO_ERR_INJ_LCK     0x99
#define RAS_SW_SMI_EINJ_EXECUTE             0x9A
#define RAS_SW_SMI_EINJ_PATROL_SCRUB        0x9B
#define RAS_SW_SMI_ERST_EXECUTE             0x9C
#define RAS_SW_SMI_MCEJ_EXECUTE             0x9F

#endif // #ifndef _RAS_SW_SMI_H_
