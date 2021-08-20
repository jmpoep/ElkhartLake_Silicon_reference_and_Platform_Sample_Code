/** @file
  Header file for CPU and PCH TraceHub Lib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#ifndef _PEI_TRACEHUB_LIB_H_
#define _PEI_TRACEHUB_LIB_H_

/**
  Get Trace Hub PCI address

  @param[in]  TraceHubDevice    Specify CPU or PCH trace hub device

  @retval UINT64                Trace Hub Pci address
**/
UINT64
GetTraceHubPciBase (
  IN   TRACE_HUB_DEVICE         TraceHubDevice
  );

/**
  Get Trace Hub MTB Bar

  @param[in]  TraceHubDevice    Specify CPU or PCH trace hub device

  @retval UINT32                Trace Hub MTB bar
**/
UINT32
GetTraceHubMtbBar (
  IN   TRACE_HUB_DEVICE         TraceHubDevice
  );

/**
  Configure Trace Hub Msc operational region regarding to buffer base and size

  @param[in] TraceHubDevice     Specify CPU or PCH trace hub device
  @param[in] Msc0Base           Base Address of MSC0BAR
  @param[in] Msc0Size           Size of MSC0Size
  @param[in] Msc1Base           Base Address of MSC1BAR
  @param[in] Msc1Size           Size of MSC1Size
**/
VOID
ConfigureMscForTraceHub (
  IN  TRACE_HUB_DEVICE          TraceHubDevice,
  IN  UINT32                    Msc0Base,
  IN  UINT32                    Msc0Size,
  IN  UINT32                    Msc1Base,
  IN  UINT32                    Msc1Size
  );

/**
  This function performs CPU and PCH Trace Hub Buffer initialization.
  Trace memopry buffers need to be allocated as reserved memory with UC attribute.

  @param[in] TraceHubMemBase       Allocated Trace Hub memory base address
  @param[in[ PchMasterPowerGating  Enable or disable Pch Master Power Gating
**/
VOID
ConfigureMscForCpuAndPchTraceHub (
  IN  UINT32                   TraceHubMemBase,
  IN  BOOLEAN                  PchMasterPowerGating
  );

/**
  Check if debugger is in use

  @param[in] TraceHubDevice     Specify CPU or PCH trace hub device

  @retval TRUE                  debugger is in use
  @retval FALSE                 debugger is NOT in use
**/
BOOLEAN
IsDebuggerInUse (
  IN TRACE_HUB_DEVICE           TraceHubDevice
  );

#endif
