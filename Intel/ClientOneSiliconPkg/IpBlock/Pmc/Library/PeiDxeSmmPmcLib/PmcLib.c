/** @file
  PCH PMC Library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PmcLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PmcPrivateLib.h>
#include <PchReservedResources.h>
#include <Register/PmcRegs.h>
#include <Register/PchRegs.h>

/**
  Get PCH ACPI base address.

  @retval Address                   Address of PWRM base address.
**/
UINT16
PmcGetAcpiBase (
  VOID
  )
{
  return PcdGet16 (PcdAcpiBaseAddress);
}

/**
  Get PCH PWRM base address.

  @retval Address                   Address of PWRM base address.
**/
UINT32
PmcGetPwrmBase (
  VOID
  )
{
  return PCH_PWRM_BASE_ADDRESS;
}

/**
  This function enables Power Button SMI
**/
VOID
PmcEnablePowerButtonSmi (
  VOID
  )
{
  IoOr16 (PmcGetAcpiBase () + R_ACPI_IO_PM1_EN, B_ACPI_IO_PM1_EN_PWRBTN);
}

/**
  This function disables Power Button SMI
**/
VOID
PmcDisablePowerButtonSmi (
  VOID
  )
{
  IoAnd16 (PmcGetAcpiBase () + R_ACPI_IO_PM1_EN, (UINT16)~B_ACPI_IO_PM1_EN_PWRBTN);
}

/**
  This function reads PM Timer Count driven by 3.579545 MHz clock

  @retval PM Timer Count
**/
UINT32
PmcGetTimerCount (
  VOID
  )
{
  return IoRead32 (PmcGetAcpiBase () + R_ACPI_IO_PM1_TMR) & B_ACPI_IO_PM1_TMR_VAL;
}

/**
  Get Sleep Type that platform has waken from

  @retval SleepType                Sleep Type
**/
PMC_SLEEP_STATE
PmcGetSleepTypeAfterWake (
  VOID
  )
{
  UINT16  AcpiBase;
  UINT32  PmconA;

  AcpiBase = PmcGetAcpiBase ();
  PmconA   = MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_A);

  DEBUG ((DEBUG_INFO, "PWRM_PMCON_A = 0x%x\n", PmconA));

  //
  // If Global Reset Status, Power Failure. Host Reset Status bits are set, return S5 State
  //
  if ((PmconA & (B_PMC_PWRM_GEN_PMCON_A_GBL_RST_STS | B_PMC_PWRM_GEN_PMCON_A_PWR_FLR | B_PMC_PWRM_GEN_PMCON_A_HOST_RST_STS)) != 0) {
    return PmcNotASleepState;
  }

  if (IoRead16 (AcpiBase + R_ACPI_IO_PM1_STS) & B_ACPI_IO_PM1_STS_WAK) {
    switch (IoRead16 (AcpiBase + R_ACPI_IO_PM1_CNT) & B_ACPI_IO_PM1_CNT_SLP_TYP) {
      case V_ACPI_IO_PM1_CNT_S0:
        return PmcInS0State;

      case V_ACPI_IO_PM1_CNT_S1:
        return PmcS1SleepState;

      case V_ACPI_IO_PM1_CNT_S3:
        return PmcS3SleepState;

      case V_ACPI_IO_PM1_CNT_S4:
        return PmcS4SleepState;

      case V_ACPI_IO_PM1_CNT_S5:
        return PmcS5SleepState;

      default:
        ASSERT (FALSE);
        return PmcUndefinedState;
    }
  } else {
    return PmcNotASleepState;
  }
}

/**
  Clear PMC Wake Status
**/
VOID
PmcClearWakeStatus (
  VOID
  )
{
  IoWrite16 (PmcGetAcpiBase () + R_ACPI_IO_PM1_STS, B_ACPI_IO_PM1_STS_WAK);
}

/**
  Configure sleep state

  @param[in] SleepState         S0/S1/S3/S4/S5, refer to PMC_SLEEP_STATE
**/
VOID
PmcSetSleepState (
  PMC_SLEEP_STATE  SleepState
  )
{
  UINT16  Data16;

  switch (SleepState) {
    case PmcInS0State:
      Data16 = V_ACPI_IO_PM1_CNT_S0;
      break;

    case PmcS1SleepState:
      Data16 = V_ACPI_IO_PM1_CNT_S1;
      break;

    case PmcS3SleepState:
      Data16 = V_ACPI_IO_PM1_CNT_S3;
      break;

    case PmcS4SleepState:
      Data16 = V_ACPI_IO_PM1_CNT_S4;
      break;

    case PmcS5SleepState:
      Data16 = V_ACPI_IO_PM1_CNT_S5;
      break;

    default:
      ASSERT (FALSE);
      return;

  }
  IoAndThenOr16 (PmcGetAcpiBase () + R_ACPI_IO_PM1_CNT, (UINT16) ~B_ACPI_IO_PM1_CNT_SLP_TYP, Data16);
}

/**
  Check if platform boots after shutdown caused by power button override event

  @retval  TRUE   Power Button Override occurred in last system boot
  @retval  FALSE  Power Button Override didn't occur
**/
BOOLEAN
PmcIsPowerButtonOverrideDetected (
  VOID
  )
{
  return ((IoRead16 (PmcGetAcpiBase () + R_ACPI_IO_PM1_STS) & B_ACPI_IO_PM1_STS_PRBTNOR) != 0);
}

/**
  This function sets tPCH25 timing

  @param[in] TimingValue       tPCH25 timing value (10us, 100us, 1ms, 10ms)
**/
VOID
PmcSetTPch25Timing (
  IN PMC_TPCH25_TIMING    TimingValue
  )
{
  ASSERT (TimingValue <= PmcTPch25_10ms);

  MmioAndThenOr32 (
    (UINTN) (PmcGetPwrmBase () + R_PMC_PWRM_CFG),
    (UINT32)~(B_PMC_PWRM_CFG_TIMING_TPCH25),
    TimingValue
    );
}

/**
  This function checks if RTC Power Failure occurred by
  reading RTC_PWR_FLR bit

  @retval RTC Power Failure state: TRUE  - Battery is always present.
                                   FALSE - CMOS is cleared.
**/
BOOLEAN
PmcIsRtcBatteryGood (
  VOID
  )
{
  return ((MmioRead8 (PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_B) & B_PMC_PWRM_GEN_PMCON_B_RTC_PWR_STS) == 0);
}

/**
  This function checks if Power Failure occurred by
  reading PWR_FLR bit

  @retval Power Failure state
**/
BOOLEAN
PmcIsPowerFailureDetected (
  VOID
  )
{
  return ((MmioRead16 (PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_A) & B_PMC_PWRM_GEN_PMCON_A_PWR_FLR) != 0);
}

/**
  This function checks if Power Failure occurred by
  reading SUS_PWR_FLR bit

  @retval SUS Power Failure state
**/
BOOLEAN
PmcIsSusPowerFailureDetected (
  VOID
  )
{
  return ((MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_A) & B_PMC_PWRM_GEN_PMCON_A_SUS_PWR_FLR) != 0);
}

/**
  This function clears Power Failure status (PWR_FLR)
**/
VOID
PmcClearPowerFailureStatus (
  VOID
  )
{
  //
  // Write 1 to clear PWR_FLR
  // Avoid clearing other W1C bits
  //
  MmioAndThenOr8 (
    PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_A + 1,
    (UINT8) ~(B_PMC_PWRM_GEN_PMCON_A_HOST_RST_STS >> 8),
    B_PMC_PWRM_GEN_PMCON_A_PWR_FLR >> 8
    );
}
/**
  This function disables read from PMC (PMC_READ_DISABLE)
**/
VOID
PmcReadDisable (
  VOID
)
{
   //
  // Write 1 to clear PMC_READ_DISABLE
  // Avoid clearing other W1C bits
  //
  MmioAndThenOr8 (
    PmcGetPwrmBase () + R_PMC_PWRM_CFG + 2,
    (UINT8) ~0,
    B_PMC_PWRM_CFG_PMCREAD_DISABLE >> 16
    );
}

/**
  This function clears Global Reset status (GBL_RST_STS)
**/
VOID
PmcClearGlobalResetStatus (
  VOID
  )
{
  //
  // Write 1 to clear GBL_RST_STS
  // Avoid clearing other W1C bits
  //
  MmioAndThenOr8 (
    PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_A + 3,
    (UINT8) ~0,
    B_PMC_PWRM_GEN_PMCON_A_GBL_RST_STS >> 24
    );
}

/**
  This function clears Host Reset status (HOST_RST_STS)
**/
VOID
PmcClearHostResetStatus (
  VOID
  )
{
  //
  // Write 1 to clear HOST_RST_STS
  // Avoid clearing other W1C bits
  //
  MmioAndThenOr8 (
    PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_A + 1,
    (UINT8) ~(B_PMC_PWRM_GEN_PMCON_A_PWR_FLR >> 8),
    B_PMC_PWRM_GEN_PMCON_A_HOST_RST_STS >> 8
    );
}

/**
  This function clears SUS Power Failure status (SUS_PWR_FLR)
**/
VOID
PmcClearSusPowerFailureStatus (
  VOID
  )
{
  //
  // BIOS clears this bit by writing a '1' to it.
  // Take care of other fields, so we don't clear them accidentally.
  //
  MmioAndThenOr8 (
    PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_A + 2,
    (UINT8) ~(B_PMC_PWRM_GEN_PMCON_A_MS4V >> 16),
    B_PMC_PWRM_GEN_PMCON_A_SUS_PWR_FLR >> 16
    );
}

/**
  This function sets state to which platform will get after power is reapplied

  @param[in] PowerStateAfterG3          0: S0 state (boot)
                                        1: S5/S4 State
**/
VOID
PmcSetPlatformStateAfterPowerFailure (
  IN UINT8 PowerStateAfterG3
  )
{
  UINT32                PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();

  if (PowerStateAfterG3) {
    MmioOr8 (PchPwrmBase + R_PMC_PWRM_GEN_PMCON_A, B_PMC_PWRM_GEN_PMCON_A_AFTERG3_EN);
  } else {
    MmioAnd8 (PchPwrmBase + R_PMC_PWRM_GEN_PMCON_A, (UINT8)~B_PMC_PWRM_GEN_PMCON_A_AFTERG3_EN);
  }
}

/**
  This function will set the DISB - DRAM Initialization Scratchpad Bit.
**/
VOID
PmcSetDramInitScratchpad (
  VOID
  )
{
  //
  // Set B_CNL_PCH_PWRM_GEN_PMCON_A_DISB.
  // NOTE: Byte access and not clear BIT18 and BIT16 (W1C bits)
  //
  MmioAndThenOr8 (
    PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_A + 2,
    (UINT8) ~((B_PMC_PWRM_GEN_PMCON_A_MS4V | B_PMC_PWRM_GEN_PMCON_A_SUS_PWR_FLR) >> 16),
    B_PMC_PWRM_GEN_PMCON_A_DISB >> 16
    );
}

/**
  This function returns PMC, PUNIT and CPU Crashlog Size allocated on PMC SSRAM

  @param[out] PmcLogSize        Pointer to PMC CrashLog Size
  @param[out] PunitLogSize      Pointer to PUNIT CrashLog Size
  @param[out] CpuLogSize        Pointer to CPU CrashLog Size
**/
VOID
PmcSsramGetCrashLogSize (
  OUT UINT32     *PmcLogSize,
  OUT UINT32     *PunitLogSize,
  OUT UINT32     *CpuLogSize
  )
{
  PmcSsramSocCrashLogSize (PmcLogSize, PunitLogSize, CpuLogSize);
}

/**
  This function sends PMC IPC CrashLog Discovery Command

  @param[out] DiscoveryBuffer     Pointer to CrashLog Discovery Data

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_INVALID_PARAMETER   NULL argument
  @retval EFI_DEVICE_ERROR        Crash Log Discovery command failed with an error
  @retval EFI_TIMEOUT             Crash Log Discovery command did not complete
**/
EFI_STATUS
PmcCrashLogDiscovery (
  OUT PMC_IPC_DISCOVERY_BUF     *DiscoveryBuffer
  )
{
  EFI_STATUS                Status;
  PMC_IPC_COMMAND_BUFFER    Wbuf;
  PMC_IPC_COMMAND_BUFFER    Rbuf;

  if (DiscoveryBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  ZeroMem (&Wbuf, sizeof (PMC_IPC_COMMAND_BUFFER));
  ZeroMem (&Rbuf, sizeof (PMC_IPC_COMMAND_BUFFER));
  Status = PmcSendCommand (V_PMC_PWRM_IPC_CMD_COMMAND_CRASHLOG, V_PMC_PWRM_IPC_CMD_CMD_ID_CRASHLOG_DISCOVERY, 4, &Wbuf, &Rbuf);
  if (!EFI_ERROR (Status)) {
    DiscoveryBuffer->Uint32 = Rbuf.Buf0;
  }
  return Status;
}

/**
  This function sends PMC IPC CrashLog Disable Command

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_DEVICE_ERROR        Crash Log Disable command failed with an error
  @retval EFI_TIMEOUT             Crash Log Disable command did not complete
**/
EFI_STATUS
PmcCrashLogDisable (
  VOID
  )
{
  PMC_IPC_COMMAND_BUFFER    Wbuf;

  ZeroMem (&Wbuf, sizeof (PMC_IPC_COMMAND_BUFFER));
  return PmcSendCommand (V_PMC_PWRM_IPC_CMD_COMMAND_CRASHLOG, V_PMC_PWRM_IPC_CMD_CMD_ID_CRASHLOG_DISABLE, 4, &Wbuf, NULL);
}

/**
  This function sends PMC IPC to clear CrashLog from PMC SSRAM area

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_DEVICE_ERROR        Crash Log Clear command failed with an error
  @retval EFI_TIMEOUT             Crash Log Clear command did not complete
**/
EFI_STATUS
PmcCrashLogClear (
  VOID
  )
{
  PMC_IPC_COMMAND_BUFFER    Wbuf;

  ZeroMem (&Wbuf, sizeof (PMC_IPC_COMMAND_BUFFER));
  return PmcSendCommand (V_PMC_PWRM_IPC_CMD_COMMAND_CRASHLOG, V_PMC_PWRM_IPC_CMD_CMD_ID_CRASHLOG_ERASE, 4, &Wbuf, NULL);
}

/**
  This function sends PMC IPC to populate CrashLog on all reboot. The SSRAM area will be cleared on G3 by PMC automatically

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_DEVICE_ERROR        Crash Log command failed with an error
  @retval EFI_TIMEOUT             Crash Log command did not complete
**/
EFI_STATUS
PmcCrashLogOnAllReset (
  VOID
  )
{
  PMC_IPC_COMMAND_BUFFER    Wbuf;

  ZeroMem (&Wbuf, sizeof (PMC_IPC_COMMAND_BUFFER));
  return PmcSendCommand (V_PMC_PWRM_IPC_CMD_COMMAND_CRASHLOG, V_PMC_PWRM_IPC_CMD_CMD_ID_CRASHLOG_ON_RESET, 4, &Wbuf, NULL);;
}

/**
  Check global SMI enable is set

  @retval TRUE  Global SMI enable is set
          FALSE Global SMI enable is not set
**/
BOOLEAN
PmcIsGblSmiEn (
  VOID
  )
{
  return !!(IoRead32 (PmcGetAcpiBase () + R_ACPI_IO_SMI_EN) & B_ACPI_IO_SMI_EN_GBL_SMI);
}

/**
  This function checks if SMI Lock is set

  @retval SMI Lock state
**/
BOOLEAN
PmcIsSmiLockSet (
  VOID
  )
{
  return ((MmioRead8 ((PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_B)) & B_PMC_PWRM_GEN_PMCON_B_SMI_LOCK) != 0);
}

/**
  This function checks if Debug Mode is locked

  @retval Debug Mode Lock state
**/
BOOLEAN
PmcIsDebugModeLocked (
  VOID
  )
{
  //
  // Get lock info from PWRMBASE + PM_CFG
  //
  return ((MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_CFG) & B_PMC_PWRM_CFG_DBG_MODE_LOCK) != 0);
}

/**
  This function checks PMC Set Strap Message interface lock

  @retval State of PMC Set Strap Message Interface lock
**/
BOOLEAN
PmcIsSetStrapMsgInterfaceLocked (
  VOID
  )
{
  return ((MmioRead32 ((PmcGetPwrmBase () + R_PMC_PWRM_SSML)) & B_PMC_PWRM_SSML_SSL) != 0);
}

/**
  Check TCO second timeout status.

  @retval  TRUE   TCO reboot happened.
  @retval  FALSE  TCO reboot didn't happen.
**/
BOOLEAN
TcoSecondToHappened (
  VOID
  )
{
  ///
  /// Read the Second TO status bit
  ///
  if ((IoRead8 (PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO2_STS) & R_TCO_IO_TCO2_STS) != 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  This function clears the Second TO status bit
**/
VOID
TcoClearSecondToStatus (
  VOID
  )
{
  IoWrite8 (PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO2_STS, B_TCO_IO_TCO2_STS_SECOND_TO);
}

/**
  Check TCO SMI ENABLE is locked

  @retval TRUE  TCO SMI ENABLE is locked
          FALSE TCO SMI ENABLE is not locked
**/
BOOLEAN
TcoIsSmiLock (
  VOID
  )
{
  return !!(IoRead16 (PcdGet16 (PcdTcoBaseAddress) + R_TCO_IO_TCO1_CNT) & B_TCO_IO_TCO1_CNT_LOCK);
}

/**
  This function verify VR Config Bit is Locked

  @retval TRUE       VR Config Bit is Locked.
  @retval FALSE      VR Config Bit is Unlocked.
**/
BOOLEAN
PmcIsFivrConfigLocked (
  VOID
  )
{
  return ((MmioRead32 (PmcGetPwrmBase () + R_PMC_PWRM_GEN_PMCON_B) & B_PMC_PWRM_GEN_PMCON_B_FIVR_LOCK) != 0);
}

/**
   Check if user wants to turn off in PEI phase and power it off
   CAUTION: this function will potentially turn off your system
**/
VOID
CheckPowerOffNow (
  VOID
  )
{
  UINT16  ABase;
  UINT16  Pm1Sts;

  ABase = PmcGetAcpiBase ();

  //
  // Read and check the ACPI registers
  //
  Pm1Sts = IoRead16 (ABase + R_ACPI_IO_PM1_STS);

  DEBUG ((DEBUG_ERROR, "CheckPowerOffNow ()- Pm1Sts= 0x%04x\n", Pm1Sts));

  if ((Pm1Sts & B_ACPI_IO_PM1_STS_PWRBTN) != 0) {
    IoWrite16 (ABase + R_ACPI_IO_PM1_STS, B_ACPI_IO_PM1_STS_PWRBTN);
    IoWrite16 (ABase + R_ACPI_IO_PM1_CNT, V_ACPI_IO_PM1_CNT_S5);
    IoWrite16 (ABase + R_ACPI_IO_PM1_CNT, V_ACPI_IO_PM1_CNT_S5 | B_ACPI_IO_PM1_CNT_SLP_EN);
  }
}

/**
 Clear any SMI status or wake status.
**/
VOID
ClearSmiAndWake (
  VOID
  )
{
  UINT16              ABase;
  UINT16              Pm1Sts;

  ABase = PmcGetAcpiBase ();

  //
  // Clear any SMI or wake state from the boot
  //
  Pm1Sts = B_ACPI_IO_PM1_STS_PWRBTN;

  IoWrite16 (ABase + R_ACPI_IO_PM1_STS, Pm1Sts);

  //
  // Clear the GPE and PM enable
  //
  IoWrite16 (ABase + R_ACPI_IO_PM1_EN, 0);
  IoWrite32 (ABase + R_ACPI_IO_GPE0_EN_127_96, 0);
}


/**
  Function to check if Dirty Warm Reset occurs
  (Global Reset has been converted to Host Reset)

  @reval TRUE DWR occurs
  @reval FALSE Normal boot flow
**/
BOOLEAN
PmcIsDwrBootMode (
  VOID
  )
{
  UINT32      PchPwrmBase;

  PchPwrmBase = PmcGetPwrmBase ();
  ASSERT (PchPwrmBase != 0);

  return !!(MmioRead32 (PchPwrmBase + R_PMC_PWRM_HPR_CAUSE0) & B_PMC_PWRM_HPR_CAUSE0_GBL_TO_HOST);
}

/**
  Sets the GPE Ctrl bit to generate a _GPE._L62 SCI to an ACPI OS

  @param  VOID

  @retval VOID
**/
VOID
PmcSetSwGpeSts (
  VOID
  )
{
  //
  // Check SCI enable bit
  //
  if (PmcIsSciEnabled ()) {

    //
    // Set SWGPE Status
    //
    PmcTriggerSwGpe ();
  }
}
