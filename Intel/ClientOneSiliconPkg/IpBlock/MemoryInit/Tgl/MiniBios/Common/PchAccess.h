/** @file
  Macros that simplify accessing PCH devices's PCI registers.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#ifndef _PCH_ACCESS_H_
#define _PCH_ACCESS_H_

#include "PchLimits.h"
#include "PchReservedResources.h"

#ifndef STALL_ONE_MICRO_SECOND
#define STALL_ONE_MICRO_SECOND 1
#endif
#ifndef STALL_ONE_SECOND
#define STALL_ONE_SECOND 1000000
#endif

///
/// The default PCH PCI segment and bus number
///
#define DEFAULT_PCI_SEGMENT_NUMBER_PCH  0
#define DEFAULT_PCI_BUS_NUMBER_PCH      0

//
// Default Vendor ID and Subsystem ID
//
#define V_PCH_INTEL_VENDOR_ID   0x8086      ///< Default Intel PCH Vendor ID
#define V_PCH_DEFAULT_SID       0x7270      ///< Default Intel PCH Subsystem ID
#define V_PCH_DEFAULT_SVID_SID  (V_INTEL_VENDOR_ID + (V_PCH_DEFAULT_SID << 16))   ///< Default INTEL PCH Vendor ID and Subsystem ID

//
// Include device register definitions
//
//#include "PcieRegs.h"
#include "Register/PchRegsPcr.h"
//#include "Register/PchRegsP2sb.h"
//#include "Register/PchRegsHda.h"
//#include "Register/PchRegsHsio.h"
//#include "Register/PchRegsLan.h"
#include "Register/PchRegsLpc.h"
#include "Register/PchRegsLpcIcl.h"
#include "Register/PchRegsPmc.h"
#include "Register/PchRegsPmcCnl.h"
//#include "Register/PchRegsPcie.h"
//#include "Register/PchRegsSata.h"
#include "Register/PchRegsSmbus.h"
//#include "Register/PchRegsSpi.h"
//#include <Register/RegsUsb.h>
#include "Register/PchRegsGpio.h"
//#include "Register/PchRegsThermalIcl.h"
#include "Register/PchRegsGpioIcl.h"
#include "Register/PchRegsSerialIoIcl.h"
#include "Register/PchRegsSerialIo.h"
//#include "Register/PchRegsCnvi.h"
//#include "Register/PchRegsTraceHub.h"
//#include "Register/PchRegsScs.h"
#include "Register/PchRegsIsh.h"
#include "Register/PchRegsDmi.h"
//#include "Register/PchRegsDmi15.h"
//#include "Register/PchRegsItss.h"
//#include "Register/PchRegsPsth.h"
//#include "Register/PchRegsFia.h"
//#include "Register/PchRegsDci.h"
#include "Register/PchRegsPsf.h"
#include "Register/PchRegsPsfIcl.h"

#endif

