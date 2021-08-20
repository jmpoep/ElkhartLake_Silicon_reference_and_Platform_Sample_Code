/** @file
  BoardType used for Platform Info Data entries in the SBIOS/Setup/AcpiASL.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#ifndef _PLATFORM_BOARD_TYPE_H_
#define _PLATFORM_BOARD_TYPE_H_

#define BoardTypeRvp        0x00    // Reference Validation Platform
#define BoardTypeRvpSthi    0x01    // Boards with Special Test Hooks
#define BoardTypeRvpPpv     0x02    // Boards used for Processor Platform Validation
#define BoardTypeFfrd       0x03    // Form factor reference design Boards
#define BoardTypeRvpErb     0x04    // ERB Boards
#define BoardTypeRvpCpv     0x05    // Boards used for Chipset Platform Validation
#define BoardTypeSv         0x06    // Boards used for Silicon Validation
#define BoardTypeUpServer   0x07    // Server Boards
#define BoardTypeSds        0x08    // Solution Development system
#define BoardTypeFfvs       0x09    // Form factor Validation system
#define BoardTypeTdv        0x0A    // Technology Development Vehicle
#define BoardTypeMax        0x0B

#endif
