/** @file
  Digital Thermal Sensor (DTS) driver.
  This SMM driver configures and supports the Digital Thermal Sensor features for the platform.

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

@par Specification Reference:
**/

#include <Library/SynchronizationLib.h>
#include <Library/MemoryAllocationLib.h>
#include "PowerMgmtSmm.h"
#include "PowerMgmtDts.h"

//
// Global variables
//
UINT8               mDtsValue;
BOOLEAN             mDtsEnabled;
UINT8               mDtsTjMax;
BOOLEAN             mUpdateDtsInEverySmi;
UINT8               mNoOfThresholdRanges;
UINT8               (*mDtsThresholdTable) [3];
UINT8               mIsPackageTempMsrAvailable;
UINT16              mNumCores;
UINT16              *mSmmCoreCpuIndex;

extern CPU_NVS_AREA *mCpuNvsAreaPtr;

///
/// The table is updated for the current CPU.
///
UINT8 mDigitalThermalSensorThresholdTable[DTS_NUMBER_THRESHOLD_RANGES][3] = {
  ///
  /// TJ_MAX = 110                ///< Current Temp.  Low Temp. High Temp.
  ///
  {TJ_MAX-80, 100, 75},      ///<    <= 30            10       35
  {TJ_MAX-70,  85, 65},      ///< 30  ~ 39            25       45
  {TJ_MAX-60,  75, 55},      ///< 40  ~ 49            35       55
  {TJ_MAX-50,  65, 45},      ///< 50  ~ 59            45       65
  {TJ_MAX-40,  55, 35},      ///< 60  ~ 69            55       75
  {TJ_MAX-30,  45, 25},      ///< 70  ~ 79            65       85
  {TJ_MAX-20,  35, 15},      ///< 80  ~ 89            75       95
  {TJ_MAX-10,  25, 05},      ///< 90  ~ 99            85       105
  {TJ_MAX-00,  15, 00}       ///< 100 ~ 109           95       110
};

//
// Function implementations
//

/**
  Check if primary thread.

  @param[out] Buffer  TRUE - if primary thread. FALSE - if secondary thread.

**/

VOID
EFIAPI
IsHt0 (
  VOID *Buffer
  )
{
  *(BOOLEAN*) Buffer = !IsSecondaryThread();
}

/**
  Read the temperature data per core/thread.
  This function must be AP safe.

  @param[in] Buffer        Pointer to UINT8 to update with the current temperature

  @retval EFI_SUCCESS   Digital Thermal Sensor temperature has updated successfully.
**/
VOID
EFIAPI
DigitalThermalSensorUpdateTemperature (
  VOID *Buffer
  )
{
  MSR_REGISTER       MsrData;
  UINT8              Temperature;

  ///
  /// Read the temperature
  ///
  MsrData.Qword = AsmReadMsr64 (MSR_IA32_THERM_STATUS);

  ///
  /// Find the DTS temperature.
  ///
  Temperature = mDtsTjMax - (MsrData.Bytes.ThirdByte & OFFSET_MASK);

  ///
  /// We only update the temperature if it is above the current temperature.
  ///
  if (Temperature > *(UINT8 *)Buffer) {
    *(UINT8 *) Buffer = Temperature;
  }
}

/**
  Read the maximum temperature of all the cores. Consumed by acpi thermal management PTID (PTMon) tool.

  @retval EFI_SUCCESS   Digital Thermal Sensor temperature has updated successfully.
**/
EFI_STATUS
DigitalThermalSensorUpdatePTID (
  VOID
  )
{
  UINT16 Index;
  UINT8  Temp;
  UINT8  MaxTemp = 0;

  ///
  /// Get DTS temperature for all cores.
  ///
  for (Index = 0; Index < mNumCores; Index++) {
     RunOnSpecificLogicalProcessor (DigitalThermalSensorUpdateTemperature, mSmmCoreCpuIndex[Index], &Temp);
     if (Temp > MaxTemp) {
       MaxTemp = Temp;
     }
  }

  mCpuNvsAreaPtr->PackageDTSTemperature = MaxTemp;

  return EFI_SUCCESS;
}

/**
  SMI handler to handle Digital Thermal Sensor CPU Local APIC SMI
  for thermal Out Of Spec interrupt

  @param[in] SmmImageHandle        Image handle returned by the SMM driver.
  @param[in] CommunicationBuffer   Pointer to the buffer that contains the communication Message
  @param[in] SourceSize            Size of the memory image to be used for handler.

  @retval EFI_SUCCESS           Callback Function Executed
**/
EFI_STATUS
EFIAPI
DtsOutOfSpecSmiCallback (
  IN EFI_HANDLE  SmmImageHandle,
  IN CONST VOID  *ContextData,         OPTIONAL
  IN OUT VOID    *CommunicationBuffer, OPTIONAL
  IN OUT UINTN   *SourceSize           OPTIONAL
  )
{

  DTS_EVENT_TYPE EventType;

  ///
  /// If not enabled; return.  (The DTS will be disabled upon S3 entry
  /// and will remain disabled until after re-initialized upon wake.)
  ///
  if (!mDtsEnabled) {
    return EFI_SUCCESS;
  }

  EventType = DtsEventNone;

  if (mIsPackageTempMsrAvailable) {
    ///
    /// Get the Package DTS Event Type
    ///
    DigitalThermalSensorEventCheckPackageMsr (&EventType);
  } else {
    ///
    /// Get the DTS Event Type
    ///
    DigitalThermalSensorEventCheck (&EventType);
  }
  ///
  /// Check if this a DTS Out Of Spec SMI event
  ///
  if (EventType == DtsEventOutOfSpec) {
    ///
    /// Return Critical temperature value to _TMP and generate GPE event for critical shutdown.
    ///
    mCpuNvsAreaPtr->EnableDigitalThermalSensor = DTS_OUT_OF_SPEC_OCCURRED;

    ///
    /// Generate SCI to shut down the system
    ///
    DigitalThermalSensorSetSwGpeSts ();
  }

  return EFI_SUCCESS;
}

/**
  Call from SMI handler to handle Package thermal temperature Digital Thermal Sensor CPU Local APIC SMI
  for thermal threshold interrupt
**/
VOID
PackageThermalDTS (
  VOID
  )
{
  DTS_EVENT_TYPE PkgEventType;

  PkgEventType = DtsEventNone;

  ///
  /// Check is this a Platform SMI event or the flag of update DTS temperature and threshold value in every SMI
  ///
  if (DigitalThermalSensorEventCheckPackageMsr (&PkgEventType) || mUpdateDtsInEverySmi) {
    ///
    /// Disable Local APIC SMI before programming the threshold
    ///
    RunOnAllLogicalProcessors (DigitalThermalSensorDisableSmi, NULL);

    do {
      ///
      /// Handle Package events
      ///

      ///
      /// Set the thermal trip toints as needed.
      ///
      mCpuNvsAreaPtr->PackageDTSTemperature = 0;

      ///
      /// Set the Package thermal sensor thresholds
      ///
      PackageDigitalThermalSensorSetThreshold (&mCpuNvsAreaPtr->PackageDTSTemperature);

      ///
      /// Set SWGPE Status to generate an SCI if we had any events
      ///
      if ((PkgEventType != DtsEventNone) || mUpdateDtsInEverySmi) {
        DigitalThermalSensorSetSwGpeSts ();
      }

    } while (DigitalThermalSensorEventCheckPackageMsr (&PkgEventType));
    ///
    /// Enable Local APIC SMI on all logical processors
    ///
    RunOnAllLogicalProcessors (DigitalThermalSensorEnableSmi, NULL);
  }
}

/**
  SMI handler to handle Digital Thermal Sensor CPU Local APIC SMI
  for thermal threshold interrupt

  @param[in] SmmImageHandle        Image handle returned by the SMM driver.
  @param[in] CommunicationBuffer   Pointer to the buffer that contains the communication Message
  @param[in] SourceSize            Size of the memory image to be used for handler.

  @retval EFI_SUCCESS           Callback Function Executed
**/
EFI_STATUS
EFIAPI
DtsSmiCallback (
  IN EFI_HANDLE  SmmImageHandle,
  IN CONST VOID  *ContextData,         OPTIONAL
  IN OUT VOID    *CommunicationBuffer, OPTIONAL
  IN OUT UINTN   *SourceSize           OPTIONAL
  )
{
  UINTN          Index;
  DTS_EVENT_TYPE EventType;
  UINT8          Temp;
  UINT8          MaxTemp = 0;

  ///
  /// If not enabled; return.  (The DTS will be disabled upon S3 entry
  /// and will remain disabled until after re-initialized upon wake.)
  ///
  if (!mDtsEnabled) {
    return EFI_SUCCESS;
  }
  ///
  /// Get the Package thermal temperature
  ///
  if (mIsPackageTempMsrAvailable) {
    RunOnAllLogicalProcessors (DigitalThermalSensorEnableSmi, NULL);
    PackageThermalDTS ();
  } else {
    ///
    /// We enable the Thermal interrupt on the AP's prior to the event check
    /// for the case where the AP has gone through the INIT-SIPI-SIPI sequence
    /// and does not have the interrupt enabled.  (This allows the AP thermal
    /// interrupt to be re-enabled due to chipset-based SMIs without waiting
    /// to receive a DTS event on the BSP.)
    ///
    for (Index = 0; Index < gSmst->NumberOfCpus; Index++) {
      if (Index == gSmst->CurrentlyExecutingCpu) continue;
      RunOnSpecificLogicalProcessor (DigitalThermalSensorEnableSmi, Index, NULL);
    }
    ///
    /// Check is this a DTS SMI event or the flag of update DTS temperature and threshold value in every SMI
    ///
    if (DigitalThermalSensorEventCheck (&EventType) || mUpdateDtsInEverySmi) {
      ///
      /// Disable Local APIC SMI before programming the threshold
      ///
      RunOnAllLogicalProcessors (DigitalThermalSensorDisableSmi, NULL);

      do {
        ///
        /// Handle BSP events
        ///

        ///
        /// Update temperatures for PTID
        ///
        DigitalThermalSensorUpdatePTID ();


        /// @todo: DigitalThermalSensorUpdatePTID sets thermal sensor data, then the code below clears. This needs to fixed.

        ///
        /// Set the thermal trip toints as needed.
        ///

        for (Index = 0; Index < mNumCores; Index++) {
          RunOnSpecificLogicalProcessor (
             DigitalThermalSensorSetThreshold,
             mSmmCoreCpuIndex[Index],
             &Temp
             );
          if (Temp > MaxTemp) {
            MaxTemp = Temp;
          }
        }

        mCpuNvsAreaPtr->PackageDTSTemperature  = MaxTemp;

        ///
        /// Set SWGPE Status to generate an SCI if we had any events
        ///
        if ((EventType != DtsEventNone) || mUpdateDtsInEverySmi) {
          DigitalThermalSensorSetSwGpeSts ();
        }

      } while (DigitalThermalSensorEventCheck (&EventType));
      ///
      /// Enable Local APIC SMI on all logical processors
      ///
      RunOnAllLogicalProcessors (DigitalThermalSensorEnableSmi, NULL);
    }
  }

  return EFI_SUCCESS;
}

/**
  This catches IO trap SMI generated by the ASL code to enable the DTS AP function

  @param[in] DispatchHandle      Not used
  @param[in] CallbackContext     Not used
**/
VOID
EFIAPI
DtsIoTrapCallback (
  IN EFI_HANDLE                             DispatchHandle,
  IN CONST VOID                             *CallbackContext,
  IN OUT VOID                               *CommBuffer,
  IN OUT UINTN                              *CommBufferSize
  )
{
  UINT32 Index;
  UINT8  Temp;
  UINT8  MaxTemp = 0;

  ///
  /// Determine the function desired, passed in the global NVS area
  ///
  switch (mCpuNvsAreaPtr->DigitalThermalSensorSmiFunction) {
    ///
    /// Enable AP Digital Thermal Sensor function after resume from S3
    ///
    case IO_TRAP_INIT_DTS_FUNCTION_AFTER_S3:
      ///
      /// Enable the Package DTS on the processors.
      ///
      if (mIsPackageTempMsrAvailable) {
        PackageDigitalThermalSensorEnable (NULL);
      } else {
        ///
        /// Enable the DTS on all logical processors.
        ///
        RunOnAllLogicalProcessors (DigitalThermalSensorEnable, NULL);
      }

      if (mDtsValue != DTS_OUT_OF_SPEC_ONLY) {
        ///
        /// Set the thermal trip toints on all logical processors.
        /// Note:  We only save the highest temperature of each die in the NVS area when
        /// more than two logical processors are present as only the highest DTS reading
        /// is actually used by the current ASL solution.
        ///
        mCpuNvsAreaPtr->PackageDTSTemperature  = 0;

        if (mIsPackageTempMsrAvailable) {
          PackageDigitalThermalSensorSetThreshold (&mCpuNvsAreaPtr->PackageDTSTemperature);
        } else {
          ///
          /// Update temperatures for PTID
          ///
          DigitalThermalSensorUpdatePTID ();

          /// @todo: DigitalThermalSensorUpdatePTID sets thermal sensor data, then the code below clears. This needs to fixed.

          for (Index = 0; Index < mNumCores; Index++) {
            RunOnSpecificLogicalProcessor (
               DigitalThermalSensorSetThreshold,
               mSmmCoreCpuIndex[Index],
               &Temp
               );
            if (Temp > MaxTemp) {
              MaxTemp = Temp;
            }
          }
          mCpuNvsAreaPtr->PackageDTSTemperature  = MaxTemp;
        }
        ///
        /// Re-enable the DTS.
        ///
        mCpuNvsAreaPtr->EnableDigitalThermalSensor = CPU_FEATURE_ENABLE;
      } else {
        ///
        /// Enable Out Of Spec Interrupt
        ///
        if (mIsPackageTempMsrAvailable) {
          PackageDigitalThermalSensorSetOutOfSpecInterrupt (NULL);
        } else {
          RunOnAllLogicalProcessors (DigitalThermalSensorSetOutOfSpecInterrupt, NULL);
        }
        ///
        /// Re-enable the DTS which only handle Out-Of-Spec condition
        ///
        mCpuNvsAreaPtr->EnableDigitalThermalSensor = DTS_OUT_OF_SPEC_ONLY;
      }
      ///
      /// Enable the Local APIC SMI on all logical processors
      ///
      RunOnAllLogicalProcessors (DigitalThermalSensorEnableSmi, NULL);
      ///
      /// Set SWGPE Status
      ///
      DigitalThermalSensorSetSwGpeSts ();

      mUpdateDtsInEverySmi  = UPDATE_DTS_EVERY_SMI;
      mDtsEnabled           = TRUE;
      break;

      ///
      /// Disable update DTS temperature and threshold value in every SMI
      ///
    case IO_TRAP_DISABLE_UPDATE_DTS:
      mUpdateDtsInEverySmi = FALSE;
      break;

    default:
      break;
  }
  ///
  /// Store return value
  ///
  mCpuNvsAreaPtr->DigitalThermalSensorSmiFunction = 0;
}

/**
  This function executes DTS procedures for preparing to enter S3.

  @param[in] Handle    Handle of the callback
  @param[in] Context   The dispatch context

  @retval EFI_SUCCESS        DTS disabled
**/
EFI_STATUS
EFIAPI
DtsS3EntryCallBack (
  IN  EFI_HANDLE                DispatchHandle,
  IN CONST VOID                 *Context         OPTIONAL,
  IN OUT VOID                   *CommBuffer      OPTIONAL,
  IN OUT UINTN                  *CommBufferSize  OPTIONAL
  )
{
  ///
  /// Clear the Digital Thermal Sensor flag in ACPI NVS.
  ///
  mCpuNvsAreaPtr->EnableDigitalThermalSensor = CPU_FEATURE_DISABLE;
  ///
  /// Clear the enable flag.
  ///
  mDtsEnabled = FALSE;
  return EFI_SUCCESS;
}

/**
  Performs initialization of the threshold table.

  @todo Update this function as necessary for the tables used by the implementation.

  @retval EFI_SUCCESS  Threshold tables initialized successfully.
**/
EFI_STATUS
InitThresholdTable (
  VOID
  )
{
  UINTN i;
  UINT8 Delta;

  ///
  /// If the table must be updated, shift the thresholds by the difference between
  /// TJ_MAX=110 and DtsTjMax.
  ///
  if (mDtsTjMax != TJ_MAX) {
    Delta = TJ_MAX - mDtsTjMax;

    for (i = 0; i < mNoOfThresholdRanges; i++) {
      if (mDtsThresholdTable[i][1] <= mDtsTjMax) {
        mDtsThresholdTable[i][0] = mDtsThresholdTable[i][0] - Delta;
      } else {
        mDtsThresholdTable[i][0] = 0;
      }
    }
  }

  return EFI_SUCCESS;
}

/**
  Perform first time initialization of the Digital Thermal Sensor

  @retval EFI_SUCCESS  Init Digital Thermal Sensor successfully
**/
EFI_STATUS
InitDigitalThermalSensor (
  VOID
  )
{
  UINT32 Index;
  UINT8  Temp;
  UINT8  MaxTemp = 0;

  if (mDtsValue != DTS_OUT_OF_SPEC_ONLY) {
    ///
    /// Initialize the DTS threshold table.
    ///
    InitThresholdTable ();

    ///
    /// Set the thermal trip points on all logical processors.
    /// Note:  We only save the highest temperature of each die in the NVS area when
    /// more than two logical processors are present as only the highest DTS reading
    /// is actually used by the current ASL solution.
    ///
    mCpuNvsAreaPtr->PackageDTSTemperature     = 0;

    if (mIsPackageTempMsrAvailable) {
      PackageDigitalThermalSensorSetThreshold (&mCpuNvsAreaPtr->PackageDTSTemperature);
    } else {
      ///
      /// Update temperatures for PTID
      ///
      DigitalThermalSensorUpdatePTID ();

      /// @todo: DigitalThermalSensorUpdatePTID sets thermal sensor data, then the code below clears. This needs to fixed.

      for (Index = 0; Index < mNumCores; Index++) {
        RunOnSpecificLogicalProcessor (
           DigitalThermalSensorSetThreshold,
           mSmmCoreCpuIndex[Index],
           &Temp
           );
        if (Temp > MaxTemp) {
          MaxTemp = Temp;
        }
      }

      mCpuNvsAreaPtr->PackageDTSTemperature = MaxTemp;
    }

    mCpuNvsAreaPtr->EnableDigitalThermalSensor = CPU_FEATURE_ENABLE;
  } else {
    ///
    /// Enable Out Of Spec Interrupt
    ///
    if (mIsPackageTempMsrAvailable) {
      PackageDigitalThermalSensorSetOutOfSpecInterrupt (NULL);
    } else {
      RunOnAllLogicalProcessors (DigitalThermalSensorSetOutOfSpecInterrupt, NULL);
    }

    mCpuNvsAreaPtr->EnableDigitalThermalSensor = DTS_OUT_OF_SPEC_ONLY;
  }
  ///
  /// Enable the Local APIC SMI on all logical processors
  ///
  RunOnAllLogicalProcessors (DigitalThermalSensorEnableSmi, NULL);
  ///
  /// Set Digital Thermal Sensor flag in ACPI NVS
  ///
  mUpdateDtsInEverySmi  = UPDATE_DTS_EVERY_SMI;
  mDtsEnabled           = TRUE;

  return EFI_SUCCESS;
}

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
  )
{
  MSR_REGISTER MsrData;

  ///
  /// First, clear our log bits
  ///
  MsrData.Qword = AsmReadMsr64 (MSR_IA32_THERM_STATUS);
  if (mDtsValue != DTS_OUT_OF_SPEC_ONLY) {
    MsrData.Qword &= (UINT64) ~THERM_STATUS_LOG_MASK;
  } else {
    MsrData.Qword &= (UINT64) ~B_OUT_OF_SPEC_STATUS_LOG;
  }

  AsmWriteMsr64 (MSR_IA32_THERM_STATUS, MsrData.Qword);

  ///
  /// Second, configure the thermal sensor control
  ///
  MsrData.Qword = AsmReadMsr64 (EFI_MSR_MISC_PWR_MGMT);

  ///
  /// Only lock interrupts if in CMP mode
  ///
  if (gSmst->NumberOfCpus > 1) {
    MsrData.Qword |= (UINT64) B_LOCK_THERMAL_INT;
  }

  AsmWriteMsr64 (EFI_MSR_MISC_PWR_MGMT, MsrData.Qword);
}

/**
  Initializes the Package Thermal Sensor Control MSR

  @param[in] Buffer        Unused.

  @retval EFI_SUCCESS   The function completed successfully.
**/
EFI_STATUS
PackageDigitalThermalSensorEnable (
  VOID *Buffer
  )
{
  MSR_REGISTER MsrData;

  ///
  /// First, clear our log bits
  ///
  MsrData.Qword = AsmReadMsr64 (EFI_MSR_IA32_PACKAGE_THERM_STATUS);
  if (mDtsValue != DTS_OUT_OF_SPEC_ONLY) {
    MsrData.Qword &= (UINT64) ~THERM_STATUS_LOG_MASK;
  } else {
    MsrData.Qword &= (UINT64) ~B_OUT_OF_SPEC_STATUS_LOG;
  }

  AsmWriteMsr64 (EFI_MSR_IA32_PACKAGE_THERM_STATUS, MsrData.Qword);

  ///
  /// Second, configure the thermal sensor control
  ///
  MsrData.Qword = AsmReadMsr64 (EFI_MSR_MISC_PWR_MGMT);

  ///
  /// Only lock interrupts if in CMP mode
  ///
  if (gSmst->NumberOfCpus > 1) {
    MsrData.Qword |= (UINT64) B_LOCK_THERMAL_INT;
  }

  AsmWriteMsr64 (EFI_MSR_MISC_PWR_MGMT, MsrData.Qword);

  return EFI_SUCCESS;
}

/**
  Generates a _GPE._L02 SCI to an ACPI OS.
**/
VOID
DigitalThermalSensorSetSwGpeSts (
  VOID
  )
{
  ///
  /// Check SCI enable
  ///
  if (PmcIsSciEnabled ()) {

    ///
    /// Set Software GPE
    ///
    PmcTriggerSwGpe ();
    ///
    /// Set Interrupt status to indicate DTS based interrupt
    ///
    mCpuNvsAreaPtr->DtsInterruptStatus = 1;
  }
}

/**
  Checks for a Core Thermal Event on any processor

  @param[in] EventType - DTS_EVENT_TYPE to indicate which DTS event type has been detected.

  @retval TRUE means this is a DTS Thermal event
  @retval FALSE means this is not a DTS Thermal event.
**/
BOOLEAN
DigitalThermalSensorEventCheck (
  DTS_EVENT_TYPE *EventType
  )
{
  ///
  /// Clear event status
  ///
  *EventType = DtsEventNone;

  RunOnAllLogicalProcessors (DigitalThermalSensorEventCheckMsr, EventType);
  ///
  /// Return TRUE if any logical processor reported an event.
  ///
  if (*EventType != DtsEventNone) {
    return TRUE;
  }

  return FALSE;
}

/**
  Checks for a Package Thermal Event by reading MSR.

  @param[in] PkgEventType - DTS_EVENT_TYPE to indicate which DTS event type has been detected.

  @retval TRUE means this is a Package DTS Thermal event
  @retval FALSE means this is not a Package DTS Thermal event.
**/
BOOLEAN
DigitalThermalSensorEventCheckPackageMsr (
  DTS_EVENT_TYPE *PkgEventType
  )
{
  MSR_REGISTER MsrData;

  ///
  /// Clear event status
  ///
  *PkgEventType = DtsEventNone;

  ///
  /// If Processor has already been flagged as Out-Of-Spec,
  /// just return.
  ///
  if (*PkgEventType != DtsEventOutOfSpec) {
    ///
    /// Read thermal status
    ///
    MsrData.Qword = AsmReadMsr64 (EFI_MSR_IA32_PACKAGE_THERM_STATUS);

    ///
    /// Check for Out-Of-Spec status.
    ///
    if (MsrData.Qword & B_OUT_OF_SPEC_STATUS_LOG) {
      *PkgEventType = DtsEventOutOfSpec;

      ///
      /// Check thresholds.
      ///
    } else if ((mDtsValue != DTS_OUT_OF_SPEC_ONLY) &&
               (MsrData.Qword & (B_THERMAL_THRESHOLD_1_STATUS_LOG | B_THERMAL_THRESHOLD_2_STATUS_LOG))
               ) {
      *PkgEventType = DtsEventThreshold;
    }
  }
  ///
  /// Return TRUE if processor reported an event.
  ///
  if (*PkgEventType != DtsEventNone) {
    return TRUE;
  }

  return FALSE;

}

/**
  Checks for a Core Thermal Event by reading MSR.

  This function must be MP safe.

  @param[in] Buffer    Pointer to DTS_EVENT_TYPE
**/
VOID
EFIAPI
DigitalThermalSensorEventCheckMsr (
  IN VOID *Buffer
  )
{
  MSR_REGISTER   MsrData;
  DTS_EVENT_TYPE *EventType;

  ///
  /// Cast to enhance readability.
  ///
  EventType = (DTS_EVENT_TYPE *) Buffer;

  ///
  /// If any processor has already been flagged as Out-Of-Spec,
  /// just return.
  ///
  if (*EventType != DtsEventOutOfSpec) {
    ///
    /// Read thermal status
    ///
    MsrData.Qword = AsmReadMsr64 (MSR_IA32_THERM_STATUS);

    ///
    /// Check for Out-Of-Spec status.
    ///
    if (MsrData.Qword & B_OUT_OF_SPEC_STATUS_LOG) {
      *EventType = DtsEventOutOfSpec;

      ///
      /// Check thresholds.
      ///
    } else if ((mDtsValue != DTS_OUT_OF_SPEC_ONLY) &&
               (MsrData.Qword & (B_THERMAL_THRESHOLD_1_STATUS_LOG | B_THERMAL_THRESHOLD_2_STATUS_LOG))
               ) {
      *EventType = DtsEventThreshold;
    }
  }
}

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
  )
{
  MSR_REGISTER MsrData;

  ///
  /// Enable Out Of Spec interrupt
  ///
  MsrData.Qword = AsmReadMsr64 (EFI_MSR_IA32_THERM_INTERRUPT);
  MsrData.Qword |= (UINT64) OVERHEAT_INTERRUPT_ENABLE;
  AsmWriteMsr64 (EFI_MSR_IA32_THERM_INTERRUPT, MsrData.Qword);
}

/**
  Set the Out Of Spec Interrupt on the package

  @param[in] Buffer        Unused

  @retval EFI_SUCCESS   Out Of Spec Interrupt programmed successfully
**/
EFI_STATUS
PackageDigitalThermalSensorSetOutOfSpecInterrupt (
  VOID *Buffer
  )
{
  MSR_REGISTER MsrData;

  ///
  /// Enable Out Of Spec interrupt
  ///
  MsrData.Qword = AsmReadMsr64 (EFI_MSR_IA32_PACKAGE_THERM_INTERRUPT);
  MsrData.Qword |= (UINT64) OVERHEAT_INTERRUPT_ENABLE;
  AsmWriteMsr64 (EFI_MSR_IA32_PACKAGE_THERM_INTERRUPT, MsrData.Qword);

  return EFI_SUCCESS;

}

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
  )
{
  UINT8        ThresholdEntry;
  MSR_REGISTER MsrData;
  UINT8        Temperature;

  ///
  /// Read the temperature
  ///
  MsrData.Qword = AsmReadMsr64 (MSR_IA32_THERM_STATUS);

  ///
  /// If Out-Of-Spec, return the critical shutdown temperature.
  ///
  if (MsrData.Qword & B_OUT_OF_SPEC_STATUS) {
    *((UINT8 *) Buffer) = DTS_CRITICAL_TEMPERATURE;
    return;
  } else if (MsrData.Qword & B_READING_VALID) {
    ///
    /// Find the DTS temperature.
    ///
    Temperature = mDtsTjMax - (MsrData.Bytes.ThirdByte & OFFSET_MASK);
    ///
    /// We only update the temperature if it is above the current temperature.
    ///
    if (Temperature > *((UINT8 *) Buffer)) {
      *((UINT8 *) Buffer) = Temperature;
    }
    ///
    /// Compare the current temperature to the Digital Thermal Sensor Threshold Table until
    /// a matching Value is found.
    ///
    ThresholdEntry = 0;
    while ((Temperature > mDtsThresholdTable[ThresholdEntry][0]) && (ThresholdEntry < (mNoOfThresholdRanges - 1))) {
      ThresholdEntry++;
    }
    ///
    /// Update the threshold values
    ///
    MsrData.Qword = AsmReadMsr64 (EFI_MSR_IA32_THERM_INTERRUPT);
    ///
    /// Low temp is threshold #2
    ///
    MsrData.Bytes.ThirdByte = mDtsThresholdTable[ThresholdEntry][1];
    ///
    /// High temp is threshold #1
    ///
    MsrData.Bytes.SecondByte = mDtsThresholdTable[ThresholdEntry][2];

    ///
    /// Enable interrupts
    ///
    MsrData.Qword |= (UINT64) TH1_ENABLE;
    MsrData.Qword |= (UINT64) TH2_ENABLE;

    ///
    /// If the high temp is at TjMax (offset == 0)
    /// We disable the int to avoid generating a large number of SMI because of TM1/TM2
    /// causing many threshold crossings
    ///
    if (MsrData.Bytes.SecondByte == 0x80) {
      MsrData.Qword &= (UINT64) ~TH1_ENABLE;
    }

    AsmWriteMsr64 (EFI_MSR_IA32_THERM_INTERRUPT, MsrData.Qword);
  }
  ///
  ///  Clear the threshold log bits
  ///
  MsrData.Qword = AsmReadMsr64 (MSR_IA32_THERM_STATUS);
  MsrData.Qword &= (UINT64) ~THERM_STATUS_THRESHOLD_LOG_MASK;
  AsmWriteMsr64 (MSR_IA32_THERM_STATUS, MsrData.Qword);
}

/**
  Read the temperature and reconfigure the thresholds on the package

  @param[in] Buffer        Pointer to UINT8 to update with the current temperature

  @retval EFI_SUCCESS   Digital Thermal Sensor threshold programmed successfully
**/
EFI_STATUS
PackageDigitalThermalSensorSetThreshold (
  VOID *Buffer
  )
{
  UINT8        ThresholdEntry;
  MSR_REGISTER MsrData;
  UINT8        Temperature;

  ///
  /// Read the temperature
  ///
  MsrData.Qword = AsmReadMsr64 (EFI_MSR_IA32_PACKAGE_THERM_STATUS);

  ///
  /// If Out-Of-Spec, return the critical shutdown temperature.
  ///
  if (MsrData.Qword & B_OUT_OF_SPEC_STATUS) {
    *((UINT8 *) Buffer) = DTS_CRITICAL_TEMPERATURE;
    return EFI_SUCCESS;
  } else if (MsrData.Qword & B_READING_VALID) {
    ///
    /// Update temperatures for PTID
    ///
    DigitalThermalSensorUpdatePTID ();

    ///
    /// Find the DTS temperature.
    ///
    Temperature = mDtsTjMax - (MsrData.Bytes.ThirdByte & OFFSET_MASK);
    ///
    /// We only update the temperature if it is above the current temperature.
    ///
    if (Temperature > *((UINT8 *) Buffer)) {
      *((UINT8 *) Buffer) = Temperature;
    }
    ///
    /// Compare the current temperature to the Digital Thermal Sensor Threshold Table until
    /// a matching Value is found.
    ///
    ThresholdEntry = 0;
    while ((Temperature > mDtsThresholdTable[ThresholdEntry][0]) && (ThresholdEntry < (mNoOfThresholdRanges - 1))) {
      ThresholdEntry++;
    }
    ///
    /// Update the threshold values
    ///
    MsrData.Qword = AsmReadMsr64 (EFI_MSR_IA32_PACKAGE_THERM_INTERRUPT);
    ///
    /// Low temp is threshold #2
    ///
    MsrData.Bytes.ThirdByte = mDtsThresholdTable[ThresholdEntry][1];
    ///
    /// High temp is threshold #1
    ///
    MsrData.Bytes.SecondByte = mDtsThresholdTable[ThresholdEntry][2];

    ///
    /// Enable interrupts
    ///
    MsrData.Qword |= (UINT64) TH1_ENABLE;
    MsrData.Qword |= (UINT64) TH2_ENABLE;

    ///
    /// If the high temp is at TjMax (offset == 0)
    /// We disable the int to avoid generating a large number of SMI because of TM1/TM2
    /// causing many threshold crossings
    ///
    if (MsrData.Bytes.SecondByte == 0x80) {
      MsrData.Qword &= (UINT64) ~TH1_ENABLE;
    }

    AsmWriteMsr64 (EFI_MSR_IA32_PACKAGE_THERM_INTERRUPT, MsrData.Qword);
  }
  ///
  ///  Clear the threshold log bits
  ///
  MsrData.Qword = AsmReadMsr64 (EFI_MSR_IA32_PACKAGE_THERM_STATUS);
  MsrData.Qword &= (UINT64) ~THERM_STATUS_THRESHOLD_LOG_MASK;
  AsmWriteMsr64 (EFI_MSR_IA32_PACKAGE_THERM_STATUS, MsrData.Qword);

  return EFI_SUCCESS;
}

/**
  Enables the Thermal Interrupt in the core Local APIC.

  @param[in] Buffer        Unused

  @retval EFI_SUCCESS   Enable Local APIC to generate a SMI successfully
**/
VOID
EFIAPI
DigitalThermalSensorEnableSmi (
  VOID *Buffer
  )
{
  UINT32  ApicThermalValue;
  BOOLEAN x2ApicEnabled;

  x2ApicEnabled = (BOOLEAN) (((AsmReadMsr64 (EFI_MSR_XAPIC_BASE)) & (BIT11 + BIT10)) == BIT11 + BIT10);
  ///
  /// Configure the Local APIC to generate an SMI on Thermal events.  First,
  /// Clear BIT16, BIT10-BIT8, BIT7-BIT0.  Then, set BIT9 (delivery mode).
  /// Don't enable the interrupt if it's already enabled
  ///
  if (x2ApicEnabled) {
    ApicThermalValue = (UINT32) AsmReadMsr64 (EFI_MSR_EXT_XAPIC_LVT_THERM);
  } else {
    ApicThermalValue = *(UINT32 *) (UINTN) LOCAL_APIC_THERMAL_DEF;
  }

  if ((ApicThermalValue & (B_INTERRUPT_MASK | B_DELIVERY_MODE | B_VECTOR)) != V_MODE_SMI) {
    ApicThermalValue = (ApicThermalValue &~(B_INTERRUPT_MASK | B_DELIVERY_MODE | B_VECTOR)) | V_MODE_SMI;
    if (x2ApicEnabled) {
      AsmWriteMsr64 (EFI_MSR_EXT_XAPIC_LVT_THERM, ApicThermalValue);
    } else {
      *(UINT32 *) (UINTN) (LOCAL_APIC_THERMAL_DEF) = (UINT32) ApicThermalValue;
    }
  }
}

/**
  Disables the Thermal Interrupt in the core Local APIC.

  @param[in] Buffer        Unused

  @retval EFI_SUCCESS   Disable Local APIC to generate a SMI successfully
**/
VOID
EFIAPI
DigitalThermalSensorDisableSmi (
  VOID *Buffer
  )
{
  UINT32  ApicThermalValue;
  BOOLEAN x2ApicEnabled;

  x2ApicEnabled = (BOOLEAN) (((AsmReadMsr64 (EFI_MSR_XAPIC_BASE)) & (BIT11 + BIT10)) == BIT11 + BIT10);
  ///
  /// Disable Local APIC thermal entry
  ///
  if (x2ApicEnabled) {
    ApicThermalValue = (UINT32) AsmReadMsr64 (EFI_MSR_EXT_XAPIC_LVT_THERM);
  } else {
    ApicThermalValue = *(UINT32 *) (UINTN) LOCAL_APIC_THERMAL_DEF;
  }
  ///
  /// Following descriptions were from SSE BIOS
  /// We set the interrupt mode at the same time as the interrupt is disabled to
  /// avoid the "Received Illegal Vector" being set in the Error Status Register.
  ///  and eax, 0FFFEF800h
  ///  or  eax, 000010200h     ; Clear Mask, Set Delivery
  ///
  ApicThermalValue = (ApicThermalValue &~(B_INTERRUPT_MASK | B_DELIVERY_MODE | B_VECTOR)) | (B_INTERRUPT_MASK | V_MODE_SMI);
  if (x2ApicEnabled) {
    AsmWriteMsr64 (EFI_MSR_EXT_XAPIC_LVT_THERM, ApicThermalValue);
  } else {
    *(UINT32 *) (UINTN) (LOCAL_APIC_THERMAL_DEF) = (UINT32) ApicThermalValue;
  }
}

/**
  Digital Thermal Sensor (DTS) SMM driver function.

  @retval EFI_SUCCESS            Driver initialization completed successfully
  @retval EFI_OUT_OF_RESOURCES   Error when allocating required memory buffer.
**/
EFI_STATUS
EFIAPI
InstallDigitalThermalSensor (
  VOID
  )
{
  EFI_STATUS                   Status;
  EFI_HANDLE                   Handle;
  UINT32                       Index;
  UINT16                       CpuIndex;
  MSR_REGISTER                 MsrData;
  CPU_NVS_AREA_PROTOCOL        *CpuNvsAreaProtocol;
  EFI_HANDLE                   SxDispatchHandle;
  EFI_HANDLE                   PchIoTrapHandle;
  EFI_CPUID_REGISTER           Cpuid06;
  EFI_SMM_SX_REGISTER_CONTEXT               SxDispatchContext;
  EFI_SMM_SX_DISPATCH2_PROTOCOL             *SxDispatchProtocol;
  EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL        *PchIoTrap;
  EFI_SMM_IO_TRAP_REGISTER_CONTEXT          PchIoTrapContext;
  DXE_CPU_POLICY_PROTOCOL                   *CpuPolicyData;
  Handle  = NULL;

  ///
  /// Get CPU DXE Policy
  ///
  Status = gBS->LocateProtocol (&gDxeCpuPolicyProtocolGuid, NULL, (VOID **) &CpuPolicyData);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_ERROR,"Failed to locate DxeCpuPolicyProtocolGuid Protocol\n"));
    return Status;
  }

  ///
  /// Initialize DTS setup value
  ///
  mDtsValue = (UINT8) CpuPolicyData->EnableDts;

  ///
  /// Check if DTS disabled in setup.
  ///
  if (mDtsValue == CPU_FEATURE_DISABLE) {
    DEBUG ((DEBUG_WARN, "DTS not enabled/supported, so driver not loaded into SMM\n"));
    return EFI_SUCCESS;
  }

  MsrData.Qword = AsmReadMsr64 (MSR_CORE_THREAD_COUNT);
  mNumCores = (UINT16) (MsrData.Dwords.Low >> N_MSR_CORE_THREAD_COUNT_CORECOUNT_OFFSET);

  mSmmCoreCpuIndex = AllocateZeroPool (sizeof (UINT16) * mNumCores);
  if (mSmmCoreCpuIndex == NULL) {
    ASSERT (mSmmCoreCpuIndex != NULL);
    return EFI_OUT_OF_RESOURCES;
  }

  ///
  /// Set SmmIndex to match the index hyper thread 0 for each core.
  ///
  Index = 0;
  for (CpuIndex = 0; CpuIndex < gSmst->NumberOfCpus; CpuIndex++) {
    BOOLEAN HT0;
    RunOnSpecificLogicalProcessor (
      IsHt0,
      CpuIndex,
      &HT0
      );
    if (HT0) {
      ASSERT (Index < mNumCores);
      mSmmCoreCpuIndex[Index] = (UINT8) CpuIndex;
      Index++;
    }
  }

  ///
  /// Locate Cpu Nvs area
  ///
  Status = gBS->LocateProtocol (&gCpuNvsAreaProtocolGuid, NULL, (VOID **) &CpuNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);
  mCpuNvsAreaPtr = CpuNvsAreaProtocol->Area;
  ///
  /// CPU_ID 6, EAX bit 6 for the Package temperature MSR support
  ///
  ZeroMem (&Cpuid06, sizeof (Cpuid06));
  AsmCpuid (6, &Cpuid06.RegEax, &Cpuid06.RegEbx, &Cpuid06.RegEcx, &Cpuid06.RegEdx);

  mIsPackageTempMsrAvailable                 = (BOOLEAN) ((Cpuid06.RegEax >> 6) & 0x01);
  mCpuNvsAreaPtr->IsPackageTempMSRAvailable  = mIsPackageTempMsrAvailable;

  ///
  /// Locate the PCH Trap dispatch protocol
  ///
  Status = gSmst->SmmLocateProtocol (&gEfiSmmIoTrapDispatch2ProtocolGuid, NULL, (VOID **) &PchIoTrap);
  ASSERT_EFI_ERROR (Status);

  PchIoTrapContext.Type         = ReadWriteTrap;
  PchIoTrapContext.Length       = 4;
  PchIoTrapContext.Address      = 0;
  Status = PchIoTrap->Register (
                        PchIoTrap,
                        (EFI_SMM_HANDLER_ENTRY_POINT2) DtsIoTrapCallback,
                        &PchIoTrapContext,
                        &PchIoTrapHandle
                        );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Update two ASL items.
  /// 1: Operating Region for DTS IO Trap.
  /// 2: Resource Consumption in LPC Device.
  ///
  ASSERT (PchIoTrapContext.Length <= (UINT8) (-1));

  mCpuNvsAreaPtr->DtsIoTrapAddress = PchIoTrapContext.Address;
  mCpuNvsAreaPtr->DtsIoTrapLength = (UINT8) PchIoTrapContext.Length;

  ///
  /// Register a callback function to handle Digital Thermal Sensor SMIs.
  ///
    if (mDtsValue != DTS_OUT_OF_SPEC_ONLY) {
      Status = gSmst->SmiHandlerRegister (DtsSmiCallback, NULL, &Handle);
      ASSERT_EFI_ERROR (Status);
    } else {
      Status = gSmst->SmiHandlerRegister (DtsOutOfSpecSmiCallback, NULL, &Handle);
      ASSERT_EFI_ERROR (Status);
    }

  ///
  /// Locate the Sx Dispatch Protocol
  ///
  Status = gSmst->SmmLocateProtocol (&gEfiSmmSxDispatch2ProtocolGuid, NULL, (VOID**)&SxDispatchProtocol);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Register the callback for S3 entry
  ///
  SxDispatchContext.Type  = SxS3;
  SxDispatchContext.Phase = SxEntry;
  Status = SxDispatchProtocol->Register (
                                 SxDispatchProtocol,
                                 DtsS3EntryCallBack,
                                 &SxDispatchContext,
                                 &SxDispatchHandle
                                 );
  ASSERT_EFI_ERROR (Status);

  if (mDtsValue != DTS_OUT_OF_SPEC_ONLY) {
    ///
    /// Get the TCC Activation Temperature and use it for TjMax.
    ///
    MsrData.Qword         = AsmReadMsr64 (EFI_MSR_IA32_TEMPERATURE_TARGET);

    mDtsTjMax             = (MsrData.Bytes.ThirdByte);
    mDtsThresholdTable    = mDigitalThermalSensorThresholdTable;
    mNoOfThresholdRanges  = DTS_NUMBER_THRESHOLD_RANGES;
  }

  if (mIsPackageTempMsrAvailable) {
    ///
    /// Enable the DTS on package.
    ///
    PackageDigitalThermalSensorEnable (NULL);
  } else {
    ///
    /// Enable the DTS on all logical processors.
    ///
    RunOnAllLogicalProcessors (DigitalThermalSensorEnable, NULL);
  }
  ///
  /// Initialize Digital Thermal Sensor Function in POST
  ///
  InitDigitalThermalSensor ();

  return EFI_SUCCESS;
}


volatile UINT32 mProcedureWrapperCount = 0; // This is used synchronize All APs.

typedef struct {
  EFI_AP_PROCEDURE Procedure;
  VOID             *Buffer;
} PROCEDURE_WRAPPER_DATA;


/**
  Wrapper used to track number of APs completed, so BSP can wait before continuing.

  @param[in, out] Buffer  Pointer to procedure to execute and Buffer.

**/

VOID EFIAPI ProcedureWrapper (
  IN OUT VOID *Buffer
  )
{
  PROCEDURE_WRAPPER_DATA *WrapperData = (PROCEDURE_WRAPPER_DATA *) Buffer;

  WrapperData->Procedure (WrapperData->Buffer);

  InterlockedDecrement (&mProcedureWrapperCount);
}


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
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  PROCEDURE_WRAPPER_DATA WrapperData;


  if (Index == gSmst->CurrentlyExecutingCpu) {
    (*Procedure) (Buffer);  // Run the procedure on BSP.
  } else {
    WrapperData.Procedure = Procedure;
    WrapperData.Buffer = Buffer;
    mProcedureWrapperCount = 1;
    Status = gSmst->SmmStartupThisAp (ProcedureWrapper, Index, &WrapperData);
    ASSERT_EFI_ERROR (Status);
    if (Status != EFI_SUCCESS) {
      mProcedureWrapperCount = 0;
      return Status;
    }

    while (mProcedureWrapperCount > 0);  //Wait for AP
  }

  return EFI_SUCCESS;
}

/**
  Runs the specified procedure on all logical processors, passing in the
  parameter buffer to the procedure.

  @param[in] Procedure     The function to be run.
  @param[in] Buffer        Pointer to a parameter buffer.

  @retval EFI_SUCCESS
**/
EFI_STATUS
RunOnAllLogicalProcessors (
  IN OUT EFI_AP_PROCEDURE Procedure,
  IN OUT VOID             *Buffer
  )
{
  UINTN      Index;
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_STATUS ApStatus;
  PROCEDURE_WRAPPER_DATA WrapperData;

  WrapperData.Procedure = Procedure;
  WrapperData.Buffer = Buffer;

  mProcedureWrapperCount = (UINT32) gSmst->NumberOfCpus - 1;  // Don't count BSP.

  ///
  /// Run the procedure on all CPUs.
  ///
  for (Index = 0; Index < gSmst->NumberOfCpus; Index++) {
    if (Index == gSmst->CurrentlyExecutingCpu) {
      (*Procedure) (Buffer);  // Run the procedure on BSP.
    } else {
      ApStatus = gSmst->SmmStartupThisAp (ProcedureWrapper, Index, &WrapperData);
      ASSERT_EFI_ERROR (ApStatus);

      if (ApStatus != EFI_SUCCESS) {
        InterlockedDecrement (&mProcedureWrapperCount); // Error, so wrapper function didn't decrement.
        Status = ApStatus;  // Report error if 1 AP reported error.
      }
    }
  }

  while (mProcedureWrapperCount > 0);  //Wait for APs

  return Status;
}

