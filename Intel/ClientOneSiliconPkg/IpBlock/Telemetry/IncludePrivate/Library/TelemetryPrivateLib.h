/** @file
  Header file for TelemetryPeiPrivateLib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#ifndef TELEMETRY_PEI_PRIVATE_LIB_H_
#define TELEMETRY_PEI_PRIVATE_LIB_H_

#include <Library/TelemetryLib.h>
#include <TelemetryPeiConfig.h>

//
// Structure of Cpu CrashLog Mailbox Interface
//
typedef union {
  struct {
    UINT32  Command         :8;
    UINT32  Param           :8;
    UINT32  Reserved        :15;
    UINT32  Busy            :1;
  } Fields;
  UINT32 InterfaceData;
} CPU_CRASHLOG_MAILBOX;

  /**
  Send CPU CrashLog Mailbox command

  @param[in]  Command             Command request for crashLog management.
  @param[in]  Param               Parameter associated with the requested command.

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_DEVICE_ERROR        Mailbox command failed with an error
  @retval EFI_TIMEOUT             Mailbox command did not complete
**/
EFI_STATUS
CpuCrashLogMailboxCommand (
  IN  UINT8                Command,
  IN  UINT8                Param
  );

/**
  Get CPU CrashLog Main pointer data

  @param[in]    BaseAddr          Pci configuration space MMIO address of CrashLog BAR
  @param[out]   *CrashDataBuff    Pointer to CrashLog Main data buffer
**/
EFI_STATUS
CpuCrashLogMainDiscovery (
  IN   UINT32                 BaseAddr,
  OUT  CPU_CRASHLOG_BUFFER    *CrashDataBuff
  );

/**
  Get CPU CrashLog Telemetry pointer data

  @param[in]    BaseAddr          Pci configuration space MMIO address of CrashLog BAR
  @param[out]   *CrashDataBuff    Pointer to CrashLog Telemetry data buffer
**/
EFI_STATUS
CpuCrashLogTelemetryDiscovery (
  IN   UINT32                 BaseAddr,
  OUT  CPU_CRASHLOG_BUFFER    *CrashDataBuff
  );

/**
  Get CPU CrashLog Trace pointer data

  @param[in]    BaseAddr          Pci configuration space MMIO address of CrashLog BAR
  @param[out]   *CrashDataBuff    Pointer to CrashLog Trace data buffer
**/
EFI_STATUS
CpuCrashLogTraceDiscovery (
  IN   UINT32                 BaseAddr,
  OUT  CPU_CRASHLOG_BUFFER    *CrashDataBuff
  );

/**
  This function disables cpu crash log

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_DEVICE_ERROR        Mailbox command failed with an error
  @retval EFI_TIMEOUT             Mailbox command did not complete
**/
EFI_STATUS
CpuCrashLogDisable (
  VOID
  );

/**
  This function configures the DEVEN for CrashLog Device

  @param[in]    CpuCrashLogDevice    Enable/Disable the CrashLog Device
**/
VOID
ConfigureCrashLogDevEn (
  BOOLEAN                 CpuCrashLogDevice
);

/**
  This function enable Telemetry's MSE after PciEnumerationComplete
**/
VOID
TelemetryMseEn (
  VOID
);

#endif
