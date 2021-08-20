/** @file
  Header file of CPU feature control module

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

@par Specification
**/
#ifndef _FEATURES_H_
#define _FEATURES_H_

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SynchronizationLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/CpuInitLib.h>
#include <CpuInitDataHob.h>
#include <Ppi/MpServices.h>
#include <Ppi/SiPolicy.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuAccess.h>
#include <PowerMgmtNvsStruct.h>
#include <Register/HeciRegs.h>
#include <Register/MeRegs.h>

///
/// Processor feature definitions.
///
#define TXT_SUPPORT        1
#define VMX_SUPPORT        (1 << 1)
#define XD_SUPPORT         (1 << 2)
#define DCA_SUPPORT        (1 << 3)
#define X2APIC_SUPPORT     (1 << 4)
#define AES_SUPPORT        (1 << 5)
#define HT_SUPPORT         (1 << 6)
#define DEBUG_SUPPORT      (1 << 7)
#define DEBUG_LOCK_SUPPORT (1 << 8)
#define PROC_TRACE_SUPPORT (1 << 9)

#define OPTION_FEATURE_RESERVED_MASK        0xFFF900F8  ///< @todo: Remove if possible. Bits 31:19, 16, 7:3
#define OPTION_FEATURE_CONFIG_RESERVED_MASK 0xFFFFFFFC  ///< bits 2:31

#define MAX_CPU_S3_MTRR_ENTRY               0x0020
#define MAX_CPU_S3_TABLE_SIZE               0x0400

#define MAX_TOPA_ENTRY_COUNT                2
#define MAX_PROCESSOR_TRACE_SIZE            0x08000000  ///< 128 MB
#define MIN_PROCESSOR_TRACE_SIZE            0x1000      ///< 4 KB

///
/// PPIN (Protected Processor Inventory Number) Support
///
#define B_PPIN_FEATURE_EN                  BIT23 ///< Indicated in MSR_PLATFORM_INFO 0xCE.
#define B_PPIN_CTL_LOCK                    BIT0
#define B_PPIN_CTL_EN                      BIT1

extern EFI_PEI_MP_SERVICES_PPI  *gMpServicesPpi;

typedef struct {
  UINT16 Index;
  UINT64 Value;
} MTRR_VALUES;

///
/// Define MP data block which consumes individual processor block.
///
typedef struct {
  UINTN                  TotalCpusForThisSystem;
  UINTN                  BSP;
  BOOLEAN                HdcSupported;
  UINTN                  CommonFeatures;
  UINTN                  SetupFeatures;
  CPU_CONFIG_DATA        CpuConfigData;
  FVID_TABLE             FvidTable[TPSS_FVID_MAX_STATES + 1];
} MP_SYSTEM_DATA;

typedef struct {
  UINT64   TopaEntry[MAX_TOPA_ENTRY_COUNT];
} PROC_TRACE_TOPA_TABLE;

/**
  Create feature control structure which will be used to program each feature on each core.
**/
VOID
InitializeFeaturePerSetup (
  VOID
  );

/**
  Program all processor features basing on desired settings

  @param[in] Buffer - .A pointer to a buffer used to pass Cpu Policy PPI
**/
VOID
EFIAPI
ProgramProcessorFeature (
  IN VOID *Buffer
  );

/**
  Detect each processor feature and log all supported features
**/
VOID
EFIAPI
CollectProcessorFeature (
  VOID
  );

/**
  Lock feature bits on the processor.
**/
VOID
LockFeatureBit (
  VOID
  );


/**
  Program CPU Monitor if supported or disable it if not supported

  @param[in] Enable  - Enable or Disable Misc Features
**/
VOID
ProgramCpuMonitor (
  BOOLEAN Enable
  );

/**
  Get Trace Hub Acpi Base address for BSP
**/
VOID
EFIAPI
GetTraceHubAcpiBaseAddressForBsp (
  VOID
  );

/**
  Programs the VR parameters for the external VR's which support SVID communication.

  @param[in] SiPolicyPpi   The SI Policy PPI instance
**/
VOID
ConfigureSvidVrs(
  IN OUT SI_POLICY_PPI *SiPolicyPpi
  );

/**
  Programs the PID parameters

  @param[in] SiPolicyPpi   The SI Policy PPI instance
**/
VOID
ConfigurePidSettings(
  IN OUT SI_POLICY_PPI *SiPolicyPpi
  );

/**
  Initialize performance and power management features before RESET_CPL at Post-memory phase.

  @param[in] PeiServices      Pointer to PEI Services Table
  @param[in] SiPolicyPpi     The SI Policy PPI instance.
**/
VOID
CpuInitPreResetCpl (
  IN CONST EFI_PEI_SERVICES   **PeiServices,
  IN SI_POLICY_PPI            *SiPolicyPpi
  );


/**
  This will check if the microcode address is valid for this processor, and if so, it will
  load it to the processor.

  @param[in]  MicrocodeAddress - The address of the microcode update binary (in memory).
  @param[out] FailedRevision   - The microcode revision that fails to be loaded.

  @retval EFI_SUCCESS           - A new microcode update is loaded.
  @retval Other                 - Due to some reason, no new microcode update is loaded.
**/
EFI_STATUS
InitializeMicrocode (
  IN  CPU_MICROCODE_HEADER *MicrocodeAddress,
  OUT UINT32               *FailedRevision
  );

#endif
