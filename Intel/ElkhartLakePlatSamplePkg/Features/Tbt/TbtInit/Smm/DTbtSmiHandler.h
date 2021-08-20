/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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
#ifndef _DTBT_SMI_HANDLER_H_
#define _DTBT_SMI_HANDLER_H_

#include <Library/TbtCommonLib.h>
#include <Library/DTbtCommonLib.h>
#include <Library/SmmTbtCommonLib.h>

#ifdef PROGRESS_CODE
#undef PROGRESS_CODE
#endif

#define count(x)              (sizeof (x) / sizeof ((x)[0]))

enum {
  HR_US_PORT,
  HR_DS_PORT0,
  HR_DS_PORT3,
  HR_DS_PORT4,
  HR_DS_PORT5,
  HR_DS_PORT6,
  MAX_CFG_PORTS
};

enum {
  HR_DS_PORT1   = HR_DS_PORT3
};

//
// Alpine Ridge
//
enum {
  AR_DS_PORT1 = HR_DS_PORT3,
  AR_DS_PORT2,
  AR_DS_PORT3,
  AR_DS_PORT4
};

typedef struct _HR_CONFIG {
  UINT16  DeviceId;
  UINT8   HRBus;
  UINT8   MinDSNumber;
  UINT8   MaxDSNumber;
  UINT8   BridgeLoops;
} HR_CONFIG;

//
// Functions
//
VOID
DTbtCallback (
  VOID
  );

VOID
DTbtDisablePCIDevicesAndBridges (
  VOID
  );

VOID
EndOfThunderboltCallback(
  IN   UINTN      RpSegment,
  IN   UINTN      RpBus,
  IN   UINTN      RpDevice,
  IN   UINTN      RpFunction
);

VOID
ConfigureDTbtAspm(
  IN UINT16      Aspm
);

UINT8
PcieFindCapId (
  IN UINT8   Segment,
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   CapId
  );

#endif
