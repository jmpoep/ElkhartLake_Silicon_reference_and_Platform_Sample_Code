/** @file
  This file contains common definitions, enums, and structs for CPGC 2.0.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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
#ifndef _CPGC_20_H_
#define _CPGC_20_H_

/// Definitions

/// Bank and Bank Group definitions
//@todo confirm that these are correct
#define CPGC20_MAX_BANKS_PER_CHANNEL      (32)
#define CPGC20_BANK_GROUP_FIELD_OFFSET    (2)
#define CPGC20_BANK_FIELD_OFFSET          (0)
#define CPGC20_MAX_ADDRESS_INSTRUCTION    (4)
#define CPGC20_MAX_ALGORITHM_INSTRUCTION  (8)
#define CPGC20_MAX_COMMAND_INSTRUCTION    (24)
#define CPGC20_MAX_DATA_INSTRUCTION       (4)

/// CPGC Modes
typedef enum {
  CPGC20_IDLE_MODE,
  CPGC20_ACTIVE_MODE
} CPGC20_INIT_MODES;

/// CPGC Address Increment Order
typedef enum {
  CPGC20_ROW_COL_2_BANK_2_RANK,
  CPGC20_BANK_2_ROW_COL_2_RANK,
  CPGC20_ROW_COL_2_RANK_2_BANK,
  CPGC20_RANK_2_ROW_COL_2_BANK,
  CPGC20_BANK_2_RANK_2_ROW_COL,
  CPGC20_RANK_2_BANK_2_ROW_COL
} CPGC20_ADDRESS_INCREMENT_ORDER;

/// CPGC Address Direction
typedef enum {
  CPGC20_FAST_Y,
  CPGC20_DIAGONAL,
  CPGC20_FAST_X,
  CPGC20_DIAGONAL2,
  CPGC20_INVERSE_FAST_Y,
  CPGC20_INVERSE_DIAGONAL,
  CPGC20_INVERSE_FAST_X,
  CPGC20_INVERSE_DIAGONAL2
} CPGC20_ADDRESS_DIRECTION;

/// CPGC Algorithm Wait Clock Frequency
typedef enum {
  CPGC20_1GHZ_FREQ,
  CPGC20_1MHZ_FREQ,
  CPGC20_1KHZ_FREQ,
  CPGC20_NATIVE_DUNIT_FREQ
} CPGC20_ALGO_WAIT_CLOCK_FREQ;

/// CADB Modes
typedef enum {
  Cadb20ModeOff,
  Cadb20ModeAlwaysOn,
  Cadb20ModeContinousDeselect,
  Cadb20ModeTriggerDeselect,
  Cadb20ModeOffDontUse,
  Cadb20ModeMrsModeDontUse,
  Cadb20ModeContinousDeselectDontUse,
  Cadb20ModeTriggerDeselectDontUse,
  Cadb20ModeMax
} CADB20_MODE;

#endif

