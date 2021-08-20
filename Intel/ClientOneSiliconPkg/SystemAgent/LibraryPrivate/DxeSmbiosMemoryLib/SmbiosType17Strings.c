/** @file
  This library will determine memory configuration information from the chipset
  and memory and create SMBIOS memory structures appropriately.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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
#include "SmbiosMemory.h"

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *DeviceLocatorStringsDimm[][8] = {
 {"Controller0-ChannelA-DIMM0",
  "Controller0-ChannelA-DIMM1",
  "Controller0-ChannelB-DIMM0",
  "Controller0-ChannelB-DIMM1",
  "Controller0-ChannelC-DIMM0",
  "Controller0-ChannelC-DIMM1",
  "Controller0-ChannelD-DIMM0",
  "Controller0-ChannelD-DIMM1"},
 {"Controller1-ChannelA-DIMM0",
  "Controller1-ChannelA-DIMM1",
  "Controller1-ChannelB-DIMM0",
  "Controller1-ChannelB-DIMM1",
  "Controller1-ChannelC-DIMM0",
  "Controller1-ChannelC-DIMM1",
  "Controller1-ChannelD-DIMM0",
  "Controller1-ChannelD-DIMM1"}
};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *DeviceLocatorStringsMemoryDown[][8] = {
 {"Controller0-ChannelA",
  "Controller0-ChannelA",
  "Controller0-ChannelB",
  "Controller0-ChannelB",
  "Controller0-ChannelC",
  "Controller0-ChannelC",
  "Controller0-ChannelD",
  "Controller0-ChannelD"},
 {"Controller1-ChannelA",
  "Controller1-ChannelA",
  "Controller1-ChannelB",
  "Controller1-ChannelB",
  "Controller1-ChannelC",
  "Controller1-ChannelC",
  "Controller1-ChannelD",
  "Controller1-ChannelD"}
};

GLOBAL_REMOVE_IF_UNREFERENCED CHAR8 *BankLocatorStrings[] = {
  "BANK 0",
  "BANK 1",
  "BANK 2",
  "BANK 3"
};
