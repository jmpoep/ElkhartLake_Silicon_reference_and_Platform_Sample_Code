/** @file
  Defines and prototypes for the Digital Thermal Sensor SMM driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#ifndef _POWER_MGMT_DTS_H_
#define _POWER_MGMT_DTS_H_

//
// Include files
//
#include <Protocol/SmmSxDispatch2.h>
#include <Protocol/SmmIoTrapDispatch2.h>
#include <CpuDataStruct.h>
#include <Protocol/CpuNvsArea.h>
#include <CpuInitDataHob.h>
#include <Library/AslUpdateLib.h>
#include <CpuRegs.h>
#include "PowerMgmtDtsLib.h"

///
/// Define module definitions
///
#define TJ_MAX                                110
#define DTS_CRITICAL_TEMPERATURE              255

//
// Generic definitions for DTS
//
#define DTS_OUT_OF_SPEC_ONLY                  2
#define DTS_OUT_OF_SPEC_OCCURRED              3

#define DTS_SAMPLE_RATE                       0x10
#define EFI_MSR_XAPIC_BASE                    0x1B
#define EFI_MSR_IA32_THERM_INTERRUPT          0x19B
#define TH1_VALUE                             8
#define TH1_ENABLE                            (1 << 15)
#define TH2_VALUE                             16
#define TH2_ENABLE                            (1 << 23)
#define OFFSET_MASK                           (0x7F)
#define OVERHEAT_INTERRUPT_ENABLE             (1 << 4)

#define B_OUT_OF_SPEC_STATUS                  (1 << 4)
#define B_OUT_OF_SPEC_STATUS_LOG              (1 << 5)
#define B_THERMAL_THRESHOLD_1_STATUS          (1 << 6)
#define B_THERMAL_THRESHOLD_1_STATUS_LOG      (1 << 7)
#define B_THERMAL_THRESHOLD_2_STATUS          (1 << 8)
#define B_THERMAL_THRESHOLD_2_STATUS_LOG      (1 << 9)
#define B_READING_VALID                       (1 << 31)

#define EFI_MSR_IA32_TEMPERATURE_TARGET       0x1A2
#define EFI_MSR_EXT_XAPIC_LVT_THERM           0x833
#define EFI_MSR_MISC_PWR_MGMT                 0x1AA
#define B_LOCK_THERMAL_INT                    (1 << 22)

#define THERM_STATUS_LOG_MASK                 (B_THERMAL_THRESHOLD_2_STATUS_LOG | B_THERMAL_THRESHOLD_1_STATUS_LOG | B_OUT_OF_SPEC_STATUS_LOG)
#define THERM_STATUS_THRESHOLD_LOG_MASK       (B_THERMAL_THRESHOLD_2_STATUS_LOG | B_THERMAL_THRESHOLD_1_STATUS_LOG)

#define EFI_MSR_IA32_PACKAGE_THERM_STATUS     0x1B1
#define EFI_MSR_IA32_PACKAGE_THERM_INTERRUPT  0x1B2

#define B_DTS_IO_TRAP                         (1 << 2)
#define DTS_IO_TRAP_REGISTER_LOW_DWORD        (0x00040001 + ICH_DTS_IO_TRAP_BASE_ADDRESS) ///< DigitalThermalSensor IO Trap High DWord value
#define DTS_IO_TRAP_REGISTER_HIGH_DWORD       0x000200F0                                  ///< DigitalThermalSensor IO Trap High DWord value
#define LOCAL_APIC_THERMAL_DEF                0xFEE00330
#define B_INTERRUPT_MASK                      (1 << 16)
#define B_DELIVERY_MODE                       (0x07 << 8)
#define V_MODE_SMI                            (0x02 << 8)
#define B_VECTOR                              (0xFF << 0)

#define DTS_NUMBER_THRESHOLD_RANGES           9     ///< How many ranges are in the threshold table
#define IO_TRAP_INIT_AP_DTS_FUNCTION          0x0A  ///< Enable AP DigitalThermalSensor function
#define IO_TRAP_INIT_DTS_FUNCTION_AFTER_S3    0x14  ///< Enable Digital Thermal Sensor function after resume from S3
#define IO_TRAP_DISABLE_UPDATE_DTS            0x1E  ///< Disable update DTS temperature and threshold value in every SMI
#define INIT_DTS_SCF_MIN                      0x10  ///< SCF Minimum value.
#define INIT_DTS_SCF_UNITY                    0x20  ///< SCF Unity Value.
#define INIT_DTS_SCF_MAX                      0x30  ///< SCF Maximum value.
#define UPDATE_DTS_EVERY_SMI                  TRUE  ///< Update DTS temperature and threshold value in every SMI

///
/// Enumerate a DTS event type
///
typedef enum {
  DtsEventNone,
  DtsEventThreshold,
  DtsEventOutOfSpec,
  DtsEventMax
} DTS_EVENT_TYPE;

//
// Function declarations
//
/**
  Runs the specified procedure on one specific logical processors, passing in the
  parameter buffer to the procedure.

  @param[in] Procedure     The function to be run.
  @param[in] Index         Indicate which logical processor should execute this procedure
  @param[in] Buffer        Pointer to a parameter buffer.

  @retval EFI_SUCCESS   Function executed successfully.
**/
STATIC
EFI_STATUS
RunOnSpecificLogicalProcessor (
  IN OUT EFI_AP_PROCEDURE Procedure,
  IN UINTN                Index,
  IN OUT VOID             *Buffer
  );

/**
  SMI handler to handle Digital Thermal Sensor CPU Local APIC SMI
  for thermal threshold interrupt

  @param[in] SmmImageHandle        Image handle returned by the SMM driver.
  @param[in] CommunicationBuffer   Pointer to the buffer that contains the communication Message
  @param[in] SourceSize            Size of the memory image to be used for handler.

  @retval EFI_SUCCESS              Callback Function Executed
**/
EFI_STATUS
EFIAPI
DtsSmiCallback (
  IN EFI_HANDLE  SmmImageHandle,
  IN CONST VOID  *ContextData,         OPTIONAL
  IN OUT VOID    *CommunicationBuffer, OPTIONAL
  IN OUT UINTN   *SourceSize           OPTIONAL
  );

/**
  Call from SMI handler to handle Package thermal temperature Digital Thermal Sensor CPU Local APIC SMI
  for thermal threshold interrupt

  @retval None
**/
VOID
PackageThermalDTS (
  VOID
  );

/**
  Perform first time initialization of the Digital Thermal Sensor

  @retval EFI_SUCCESS  Init Digital Thermal Sensor successfully
**/
EFI_STATUS
InitDigitalThermalSensor (
  VOID
  );

/**
  Initializes the Thermal Sensor Control MSR

  This function must be AP safe.

  @param[in] Buffer        Unused.

  @retval EFI_SUCCESS   The function completed successfully.
**/
VOID
EFIAPI
DigitalThermalSensorEnable (
  VOID *Buffer
  );

/**
  Initializes the Package Thermal Sensor Control MSR

  @param[in] Buffer        Unused.

  @retval EFI_SUCCESS   The function completed successfully.
**/
EFI_STATUS
PackageDigitalThermalSensorEnable (
  VOID *Buffer
  );

/**
  Generates a _GPE._L02 SCI to an ACPI OS.
**/
VOID
DigitalThermalSensorSetSwGpeSts (
  VOID
  );

/**
  Checks for a Core Thermal Event by reading MSR.

  This function must be MP safe.

  @param[in] Buffer    Pointer to DTS_EVENT_TYPE
**/
VOID
EFIAPI
DigitalThermalSensorEventCheckMsr (
  IN VOID *Buffer
  );

/**
  Checks for a Package Thermal Event by reading MSR.

  @param[in] PkgEventType - DTS_EVENT_TYPE to indicate which DTS event type has been detected.

  @retval TRUE means this is a Package DTS Thermal event
  @retval FALSE means this is not a Package DTS Thermal event.
**/
BOOLEAN
DigitalThermalSensorEventCheckPackageMsr (
  DTS_EVENT_TYPE *PkgEventType
  );

/**
  Checks for a Core Thermal Event on any processor

  @param[in] EventType - DTS_EVENT_TYPE to indicate which DTS event type has been detected.

  @retval TRUE means this is a DTS Thermal event
  @retval FALSE means this is not a DTS Thermal event.
**/
BOOLEAN
DigitalThermalSensorEventCheck (
  DTS_EVENT_TYPE *EventType
  );

/**
  Read the temperature and reconfigure the thresholds.
  This function must be AP safe.

  @param[in] Buffer        Pointer to UINT8 to update with the current temperature

  @retval EFI_SUCCESS   Digital Thermal Sensor threshold programmed successfully
**/
VOID
EFIAPI
DigitalThermalSensorSetThreshold (
  VOID *Buffer
  );

/**
  Read the temperature and reconfigure the thresholds on the package

  @param[in] Buffer        Pointer to UINT8 to update with the current temperature

  @retval EFI_SUCCESS   Digital Thermal Sensor threshold programmed successfully
**/
EFI_STATUS
PackageDigitalThermalSensorSetThreshold (
  VOID *Buffer
  );

/**
  Set the Out Of Spec Interrupt in all cores
  This function must be AP safe.

  @param[in] Buffer        Unused

  @retval EFI_SUCCESS   Out Of Spec Interrupt programmed successfully
**/
VOID
EFIAPI
DigitalThermalSensorSetOutOfSpecInterrupt (
  VOID *Buffer
  );

/**
  Set the Out Of Spec Interrupt on the package

  @param[in] Buffer        Unused

  @retval EFI_SUCCESS   Out Of Spec Interrupt programmed successfully
**/
EFI_STATUS
PackageDigitalThermalSensorSetOutOfSpecInterrupt (
  VOID *Buffer
  );

/**
  Enables the Thermal Interrupt in the core Local APIC.

  @param[in] Buffer        Unused

  @retval EFI_SUCCESS   Enable Local APIC to generate a SMI successfully
**/
VOID
EFIAPI
DigitalThermalSensorEnableSmi (
  VOID *Buffer
  );

/**
  Disables the Thermal Interrupt in the core Local APIC.

  @param[in] Buffer        Unused

  @retval EFI_SUCCESS   Disable Local APIC to generate a SMI successfully
**/
VOID
EFIAPI
DigitalThermalSensorDisableSmi (
  VOID *Buffer
  );

/**
  Performs initialization of the threshold table.

  @todo Update this function as necessary for the tables used by the implementation.

  @retval EFI_SUCCESS  Threshold tables initialized successfully.
**/
EFI_STATUS
InitThresholdTable (
  VOID
  );

/**
  This function executes DTS procedures for preparing to enter S3.

  @param[in] Handle    Handle of the callback
  @param[in] Context   The dispatch context

  @retval EFI_SUCCESS        DTS disabled
**/
EFI_STATUS
EFIAPI
DtsS3EntryCallBack (
  IN  EFI_HANDLE   DispatchHandle,
  IN CONST VOID    *Context         OPTIONAL,
  IN OUT VOID      *CommBuffer      OPTIONAL,
  IN OUT UINTN     *CommBufferSize  OPTIONAL
  );
#endif
