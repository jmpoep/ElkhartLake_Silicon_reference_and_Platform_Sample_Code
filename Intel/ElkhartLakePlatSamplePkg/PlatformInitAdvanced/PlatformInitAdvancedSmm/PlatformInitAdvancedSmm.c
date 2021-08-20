/** @file
  Platform Advanced SMM Driver.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include "PlatformInitAdvancedSmm.h"
#include <OemSetup.h>
#include <CpuRegs.h>
#include <PchPolicyCommon.h>
#include "PcieDockSmi.h"
#include "PlatformBoardId.h"
#include "AcpiCommon.h"

#define PROGRESS_CODE_S3_SUSPEND_START _gPcd_FixedAtBuild_PcdProgressCodeS3SuspendStart
#include <Library/PmcLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/GpioLib.h>
#include <Library/ItssLib.h>
#include <Library/TimerLib.h>
#include <Register/MeRegs.h>
#include <Register/HeciRegs.h>
#include <Protocol/PchTcoSmiDispatch.h>
#include <Protocol/SmmVariable.h>
#include <Protocol/SmmCpu.h>
#include <Library/PostCodeLib.h>
#include <PlatformPostCode.h>
#include <Register/PchRegs.h>
#include <Register/PchRegsLpc.h>
#include <Register/PmcRegs.h>
#include <Register/RtcRegs.h>
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
#include <Library/HobLib.h>
#include <Library/TopSwapLib.h>
#endif

//
// Global variables
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_SMM_SYSTEM_TABLE2                     *mSmst;

GLOBAL_REMOVE_IF_UNREFERENCED UINT16                                    mAcpiBaseAddr;
GLOBAL_REMOVE_IF_UNREFERENCED PLATFORM_NVS_AREA                         *mPlatformNvsAreaPtr = 0;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_ACPI_SMM_DEV                          mAcpiSmm;
//
// Setup variables
//
GLOBAL_REMOVE_IF_UNREFERENCED SETUP_DATA                                mSystemConfiguration;
GLOBAL_REMOVE_IF_UNREFERENCED PCH_SETUP                                 mPchSetup;
//
// HMRFPO lock output parameters
//

GLOBAL_REMOVE_IF_UNREFERENCED EFI_EC_ACCESS_PROTOCOL                    *mEcAccess = NULL;

GLOBAL_REMOVE_IF_UNREFERENCED UINT8                                     mPlatformFlavor;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                                     mBoardType;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                                     mEcPresent;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                                     mEcHandshakeEnable;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_SMM_CPU_PROTOCOL                      *mSmmCpu;

GLOBAL_REMOVE_IF_UNREFERENCED UINT8                                     mEctoPdControllerNegotiationInSx = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32                                    mFpsWakeGpio = 0;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                                   mGpioTier2WakeSupport;
#if FixedPcdGetBool(PcdCapsuleEnable) == 1
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                                   mEndOfDxe = FALSE;
#endif
/**
  Clear Port 80h

  SMI handler to enable ACPI mode

  Dispatched on reads from APM port with value EFI_ACPI_ENABLE_SW_SMI

  Disables the SW SMI Timer.
  ACPI events are disabled and ACPI event status is cleared.
  SCI mode is then enabled.

  Clear SLP SMI status
  Enable SLP SMI

  Disable SW SMI Timer

  Clear all ACPI event status and disable all ACPI events

  Disable PM sources except power button
  Clear status bits

  Disable GPE0 sources
  Clear status bits

  Disable GPE1 sources
  Clear status bits

  Guarantee day-of-month alarm is invalid (ACPI 1.0 section 4.7.2.4)

  Enable SCI

  Set 8254 timer clock gate enable if it's not set in early phase

  @param[in] DispatchHandle       - The handle of this callback, obtained when registering
  @param[in] DispatchContext      - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
  @param[in] CommBuffer           - A pointer to a collection of data in memory that will
                                    be conveyed from a non-SMM environment into an SMM environment.
  @param[in] CommBufferSize       - The size of the CommBuffer.
**/
EFI_STATUS
EFIAPI
EnableAcpiCallback (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  CONST VOID                    *DispatchContext,
  IN  OUT VOID                      *CommBuffer  OPTIONAL,
  IN  OUT UINTN                     *CommBufferSize  OPTIONAL
  )
{
  UINT32                              OutputValue;
  UINT32                              Pm1Cnt;
  EFI_STATUS                          Status;
  UINT32                              SmiEn;
  UINT32                              SmiSts;
  UINT32                              ULKMC;
  UINT64                              LpcBaseAddress;

  LpcBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                     DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_LPC,
                     PCI_FUNCTION_NUMBER_PCH_LPC,
                     0
                     );

  Status = EFI_SUCCESS;
  //
  // BIOS must also ensure that CF9GR is cleared and locked before handing control to the
  // OS in order to prevent the host from issuing global resets and resetting ME
  //
  // EDK2: To match PCCG current BIOS behavior, do not lock CF9 Global Reset
  // MmioWrite32 (
  //     PmcBaseAddress + R_PCH_PMC_ETR3),
  //     PmInit);

  //
  // Clear Port 80h
  //
  OutputValue = 0;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT16, 0x80, 1, &OutputValue);
  //
  // Disable SW SMI Timer and clean the status
  //
  mSmst->SmmIo.Io.Read (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_SMI_EN, 1, &SmiEn);
  SmiEn &= ~(B_ACPI_IO_SMI_EN_LEGACY_USB2 | B_ACPI_IO_SMI_EN_SWSMI_TMR | B_ACPI_IO_SMI_EN_LEGACY_USB);
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_SMI_EN, 1, &SmiEn);

  mSmst->SmmIo.Io.Read (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_SMI_STS, 1, &SmiSts);
  SmiSts |= B_ACPI_IO_SMI_EN_LEGACY_USB2 | B_ACPI_IO_SMI_EN_SWSMI_TMR | B_ACPI_IO_SMI_EN_LEGACY_USB;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_SMI_STS, 1, &SmiSts);

  //
  // Disable port 60/64 SMI trap if they are enabled
  //
  ULKMC = PciSegmentRead32 (LpcBaseAddress + R_LPC_CFG_ULKMC);
  ULKMC &= ~(B_LPC_CFG_ULKMC_60REN | B_LPC_CFG_ULKMC_60WEN | B_LPC_CFG_ULKMC_64REN | B_LPC_CFG_ULKMC_64WEN | B_LPC_CFG_ULKMC_A20PASSEN);
  PciSegmentWrite32 (LpcBaseAddress + R_LPC_CFG_ULKMC, ULKMC);

  //
  // Disable PM sources except power button
  //
  OutputValue = B_ACPI_IO_PM1_EN_PWRBTN;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT16, mAcpiBaseAddr + R_ACPI_IO_PM1_EN, 1, &OutputValue);
  //
  // Clear PM status except Power Button status for RapidStart Resume
  //
  // OutputValue = 0xFFFF;
  OutputValue = 0xFEFF;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT16, mAcpiBaseAddr + R_ACPI_IO_PM1_STS, 1, &OutputValue);

  //
  // Guarantee day-of-month alarm is invalid (ACPI 1.0 section 4.7.2.4)
  //
  OutputValue = R_RTC_IO_REGD;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT8, R_RTC_IO_INDEX_ALT, 1, &OutputValue);
  OutputValue = 0x0;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT8, R_RTC_IO_TARGET_ALT, 1, &OutputValue);

  //
  // Enable SCI
  //
  mSmst->SmmIo.Io.Read (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_PM1_CNT, 1, &Pm1Cnt);
  Pm1Cnt |= B_ACPI_IO_PM1_CNT_SCI_EN;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_PM1_CNT, 1, &Pm1Cnt);

  if (mEcPresent == 1) {
    //
    // Check the power state from EC and update it to global NVS area
    //
    if (PowerStateIsAc ()) {
      mPlatformNvsAreaPtr->PowerState = 1;
    } else {
      mPlatformNvsAreaPtr->PowerState = 0;
    }

    //
    // Disable SMI mode
    //
    Status = DisableEcSmiMode ();
    ASSERT_EFI_ERROR (Status);

    //
    // Commands EC to begin reading Thermal Diode and comparing to Critical Temperature.
    // Shutdown will occur when current temp equals or exceeds Critical temperature.
    //
    Status = EnableEcAcpiMode (TRUE);
    ASSERT_EFI_ERROR (Status);

    //
    // send command to EC to enable/disable ALS
    //
    if (mEcAccess != NULL) {
      mEcAccess->SMINotifyDisable ();
      mEcAccess->AcpiEnable ();
    }
  }

#if FixedPcdGetBool (PcdEmbeddedEnable) == 1
  //
  // Enable embedded specific stuff
  //
  if (mPlatformFlavor == FlavorEmbedded) {
    mPlatformNvsAreaPtr->PowerState = 0;
  }
#endif
  PlatformSpecificAcpiEnableHook ();
  //
  // Write ALT_GPI_SMI_EN to disable GPI1 (SMC_EXTSMI#)
  //
  OutputValue = 0;
  mSmst->SmmIo.Io.Read (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + 0x38, 1, &OutputValue);
  OutputValue = OutputValue & ~(1 << (UINTN) PcdGet8 (PcdSmcExtSmiBitPosition));
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + 0x38, 1, &OutputValue);

  //
  // Set 8254 timer clock gate enable if it's not set in early phase
  //
  if ((mPchSetup.Enable8254ClockGating != 1) && (mPchSetup.PchLegacyIoLowLatency != 1)) {
    Status = ItssSet8254ClockGateState (TRUE);
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}

/**
  Disable SCI

  @param[in] DispatchHandle       - The handle of this callback, obtained when registering
  @param[in] DispatchContext      - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
  @param[in] CommBuffer           - A pointer to a collection of data in memory that will
                                    be conveyed from a non-SMM environment into an SMM environment.
  @param[in] CommBufferSize       - The size of the CommBuffer.
**/
EFI_STATUS
EFIAPI
DisableAcpiCallback (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  CONST VOID                    *DispatchContext,
  IN  OUT VOID                      *CommBuffer  OPTIONAL,
  IN  UINTN                         *CommBufferSize  OPTIONAL
  )
{
  UINT32      Pm1Cnt;
  EFI_STATUS  Status;

  //
  // Disable SCI
  //
  mSmst->SmmIo.Io.Read (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_PM1_CNT, 1, &Pm1Cnt);
  Pm1Cnt &= ~B_ACPI_IO_PM1_CNT_SCI_EN;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_PM1_CNT, 1, &Pm1Cnt);

  //
  // Disable mobile specific stuff
  //
  PlatformSpecificAcpiDisableHook ();
  //
  //  Take EC out of ACPI Mode.
  //
  Status = EnableEcAcpiMode (FALSE);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Converts Decimal to BCD
  Only for 2 digit BCD.

  @param[in] Dec       - Decimal value to be converted to BCD

  @retval BCD for Dec number
**/
UINT8
DecToBCD (
  UINT8 Dec
  )
{
  UINT8 FirstDigit;
  UINT8 SecondDigit;

  FirstDigit  = Dec % 10;
  SecondDigit = Dec / 10;

  return (SecondDigit << 4) + FirstDigit;
}

/**
  Converts BCD to Dec number
  Only for 2 digit BCD.

  @param[in] BCD       - BCD number which needs to be converted to Dec

  @retval Dec value for given BCD
**/
UINT8
BCDToDec (
  UINT8 BCD
  )
{
  UINT8 FirstDigit;
  UINT8 SecondDigit;
  FirstDigit  = BCD & 0xf;
  SecondDigit = BCD >> 4;

  return SecondDigit * 10 + FirstDigit;
}

/**
  Reads the RTC Index register

  @param[in] Index - Index register

  @retval Value in Index register
**/
UINT8
ReadRtcIndex (
  IN UINT8 Index
  )
{
  UINT8           Value;
  UINT8           Addr;

  //
  // Use port RTC alternative ports 74h/75h to prevent from breaking NMI setting
  //

  //
  // Check if Data Time is valid
  //
  if (Index <= 9) {
    do {
      Addr = 0x0A;
      mSmst->SmmIo.Io.Write (
                        &mSmst->SmmIo,
                        SMM_IO_UINT8,
                        R_RTC_IO_INDEX_ALT,
                        1,
                        &Addr
                        );
      mSmst->SmmIo.Io.Read (
                        &mSmst->SmmIo,
                        SMM_IO_UINT8,
                        R_RTC_IO_TARGET_ALT,
                        1,
                        &Value
                        );
    } while (Value & 0x80);
  }

  Addr = Index;
  mSmst->SmmIo.Io.Write (
                    &mSmst->SmmIo,
                    SMM_IO_UINT8,
                    R_RTC_IO_INDEX_ALT,
                    1,
                    &Addr
                    );
  //
  // Read register.
  //
  mSmst->SmmIo.Io.Read (
                    &mSmst->SmmIo,
                    SMM_IO_UINT8,
                    R_RTC_IO_TARGET_ALT,
                    1,
                    &Value
                    );
  if (Index <= 9) {
    Value = BCDToDec (Value);
  }

  return (UINT8) Value;
}

/**
  Writes to an RTC Index register

  @param[in] Index   - Index to be written
  @param[in] Value   - Value to be written to Index register
**/
VOID
WriteRtcIndex (
  IN UINT8 Index,
  IN UINT8 Value
  )
{
  UINT8           Addr;

  //
  // Use port RTC alternative ports 74h/75h to prevent from breaking NMI setting
  //

  Addr = Index;
  mSmst->SmmIo.Io.Write (
                    &mSmst->SmmIo,
                    SMM_IO_UINT8,
                    R_RTC_IO_INDEX_ALT,
                    1,
                    &Addr
                    );
  if (Index <= 9) {
    Value = DecToBCD (Value);
  }
  //
  // Write Register.
  //
  mSmst->SmmIo.Io.Write (
                    &mSmst->SmmIo,
                    SMM_IO_UINT8,
                    R_RTC_IO_TARGET_ALT,
                    1,
                    &Value
                    );
}

/**
  Disable RTC alarm and clear RTC PM1 status.

**/
VOID
InitRtcWakeup (
  VOID
  )
{
  UINT16 Data16;

  //
  // Clear Alarm Flag (AF) by reading RTC Reg C
  //
  mSmst->SmmIo.Io.Read (
                    &mSmst->SmmIo,
                    SMM_IO_UINT16,
                    mAcpiBaseAddr + R_ACPI_IO_PM1_STS,
                    1,
                    &Data16
                    );
  Data16 = Data16 | B_ACPI_IO_PM1_STS_RTC;
  mSmst->SmmIo.Io.Write (
                    &mSmst->SmmIo,
                    SMM_IO_UINT16,
                    mAcpiBaseAddr + R_ACPI_IO_PM1_STS,
                    1,
                    &Data16
                    );
}


/**
  Turn off NGFF WWAN device when system is going to S5 state

**/
VOID
TurnNgffWwanOff (
  VOID
  )
{
  // Platform specific @ TBD
  // use PCH lib for GPIO attribute programming

}

/**
  Enable wake capability for that wake delivered via tier2 GPIO

  @retval EFI_SUCCESS           - Operation successfully performed
**/
EFI_STATUS
EnablePchTier2GpioWakeSupport (
  VOID
  )
{

  UINT16                             Data16;

  if (!mGpioTier2WakeSupport) {
    return EFI_UNSUPPORTED;
  }

  //
  // Enable wake capability when device is present
  //
  mSmst->SmmIo.Io.Read (
                    &mSmst->SmmIo,
                    SMM_IO_UINT16,
                    mAcpiBaseAddr + R_ACPI_IO_GPE0_EN_127_96,
                    1,
                    &Data16
                    );
  Data16 = Data16 | B_ACPI_IO_GPE0_STS_127_96_GPIO_TIER_2;
  mSmst->SmmIo.Io.Write (
                    &mSmst->SmmIo,
                    SMM_IO_UINT16,
                    mAcpiBaseAddr + R_ACPI_IO_GPE0_EN_127_96,
                    1,
                    &Data16
                    );

  return EFI_SUCCESS;
}

/**
  If PCIe native mode is disabled through BIOS setup options,
  Windows ACPI driver initializes the PM1 enable bits with PCIEXP_WAKE_DIS bit set to 1 provided the flag PCI_EXP_WAK is set in FADT.
  If the FADT flag is not set then Windows will not set the PCIEXP_WAKE_DIS bit.

  In summary OS is setting PCIEXP_WAKE_DIS if native PCIe support is disabled.

  To mitigate the wake issue bios will clear this bit in case of Sx entry which will allow system to detect any wake event from Add in card."

  @param[in] VOID

  @retval    VOID
**/
VOID
EnablePchPcieWakeSupport (
  VOID
)
{

  UINT16  Data16;

  if (!(mSystemConfiguration.PciExpNative)) {
    mSmst->SmmIo.Io.Read (
                      &mSmst->SmmIo,
                      SMM_IO_UINT16,
                      mAcpiBaseAddr + R_ACPI_IO_PM1_EN,
                      1,
                      &Data16
                      );
    Data16 = Data16 & (UINT16)~BIT14;
    mSmst->SmmIo.Io.Write (
                      &mSmst->SmmIo,
                      SMM_IO_UINT16,
                      mAcpiBaseAddr + R_ACPI_IO_PM1_EN,
                      1,
                      &Data16
                      );
  }
}

/**
  Add support to wake host via PSE

  @param[in] VOID

  @retval    VOID
**/
VOID
EnablePchPseWakeSupport (
  VOID
)
{
  UINT32                  Data32;
  mSmst->SmmIo.Io.Read (
                  &mSmst->SmmIo,
                  SMM_IO_UINT32,
                  mAcpiBaseAddr + R_ACPI_IO_GPE0_EN_127_96,
                  1,
                  &Data32
                  );
  Data32 = Data32 | (UINT32) (B_ACPI_IO_GPE0_STS_127_96_PSE) | (UINT32) (B_ACPI_IO_GPE0_STS_127_96_PME);
  mSmst->SmmIo.Io.Write (
                  &mSmst->SmmIo,
                  SMM_IO_UINT32,
                  mAcpiBaseAddr + R_ACPI_IO_GPE0_EN_127_96,
                  1,
                  &Data32
                  );
}

#define FPS_FPC1021  06

/**
  Enable FInger Print Sensor Wake Support
  Default GPIO is configured as GPIO Driver Mode where FPS driver will take care in OS Environment.
  Here Enable Wake support by reconfiguring the GPIO with SCI Capability

  @param[in] VOID

  @retval    VOID
**/
VOID
EnableFingerPrintSensorWakeSupport (
  VOID
)
{
  UINT32                  Data32;
  GPIO_CONFIG             FpsDevicereadypin = { GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirIn,    GpioOutDefault, GpioIntLevel | GpioIntSci, GpioHostDeepReset,  GpioTermNone };
  if ((mSystemConfiguration.PchSpiFingerPrintType == FPS_FPC1021) && (mFpsWakeGpio)) {
    //
    // Enable GPIO Tier 2 SCI Before entering into Sx (incase if not enabled already)
    //
    mSmst->SmmIo.Io.Read (
                     &mSmst->SmmIo,
                     SMM_IO_UINT32,
                     mAcpiBaseAddr + R_ACPI_IO_GPE0_EN_127_96,
                     1,
                     &Data32
                    );
    Data32 = Data32 | (UINT32) (BIT15);
    mSmst->SmmIo.Io.Write (
                    &mSmst->SmmIo,
                    SMM_IO_UINT32,
                    mAcpiBaseAddr + R_ACPI_IO_GPE0_EN_127_96,
                    1,
                    &Data32
                   );
     GpioSetPadConfig (mFpsWakeGpio, &FpsDevicereadypin);
  }
}
#define DDR3_STANDBY_PWR_GPIO_PIN                      0                    // Platform specific @ TBD

/**
  S3 Sleep Entry Call Back.

  @param[in] DispatchHandle     - The handle of this callback, obtained when registering
  @param[in] DispatchContext    - The predefined context which contained sleep type and phase
  @param[in] CommBuffer         - A pointer to a collection of data in memory that will
                                  be conveyed from a non-SMM environment into an SMM environment.
  @param[in] CommBufferSize     - The size of the CommBuffer.

  @retval EFI_SUCCESS           - Operation successfully performed
**/
EFI_STATUS
EFIAPI
S3SleepEntryCallBack (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  CONST VOID                    *DispatchContext,
  IN  OUT VOID                      *CommBuffer  OPTIONAL,
  IN  UINTN                         *CommBufferSize  OPTIONAL
  )
{
  UINT8                   EcDataBuffer;
  UINT32                  Timeout;

  PostCode (BIOS_S3_ENTRY);

  EcDataBuffer = 0x03; // Input: 0x03 S3, 0x04 S4, 0x05S5
  if (mEctoPdControllerNegotiationInSx) {
    //
    // Send this EC command from SMM to notify EC and wait for response (EC_C_USBC_SX_ENTRY_WAIT for Sx Entry)
    //
    if (mPlatformFlavor == FlavorDesktop && mEcHandshakeEnable == 1) {
      Timeout = mSystemConfiguration.UsbcSxEntryTimeout;
      UsbcSxEntry (&EcDataBuffer, Timeout);
    }
  }
  //
  // Enable Wakesupport for PCIE Add-on Cards when Native support is disabled
  //
  EnablePchPcieWakeSupport ();

  //
  // Enable PSE wake support
  //
  EnablePchPseWakeSupport ();

  //
  // Enable Finger Print Sensor Wake support
  //
  EnableFingerPrintSensorWakeSupport ();

  if ((mPlatformFlavor == FlavorMobile) || (mPlatformFlavor == FlavorEmbedded)) {
    //
    // This GPIO operation is designed to take care of DDR3 Standby Power Reduction
    //  PullDown GPIO
    //
    //GpioSetPadElectricalConfig (DDR3_STANDBY_PWR_GPIO_PIN, GpioTermNone); //@todo, uncomment when DDR3_STANDBY_PWR_GPIO_PIN has been assigned correct GpioPad
  }

  //
  // Enable Tier2 GPIO Wake support
  //
  EnablePchTier2GpioWakeSupport ();

  //
  // WARNING!!! Please do not modify GP_LVL register after this point
  //

  return EFI_SUCCESS;
}

/**
  S4 Sleep Entry Call Back.

  @param[in] DispatchHandle     - The handle of this callback, obtained when registering
  @param[in] DispatchContext    - The predefined context which contained sleep type and phase
  @param[in] CommBuffer         - A pointer to a collection of data in memory that will
                                  be conveyed from a non-SMM environment into an SMM environment.
  @param[in] CommBufferSize     - The size of the CommBuffer.

  @retval EFI_SUCCESS           - Operation successfully performed
**/
EFI_STATUS
EFIAPI
S4SleepEntryCallBack (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  CONST VOID                    *DispatchContext,
  IN  OUT VOID                      *CommBuffer  OPTIONAL,
  IN  UINTN                         *CommBufferSize  OPTIONAL
  )
{
  UINT8                   EcDataBuffer;
  UINT32                  Timeout;

  PostCode (BIOS_S4_ENTRY);

  //
  // Put EC in non-ACPI mode.  This ensures EC takes over FAN control from now on till actual shutdown.
  //
  EnableEcAcpiMode (FALSE);
  if (mEctoPdControllerNegotiationInSx) {

    EcDataBuffer = 0x04; // Input: 0x03 S3, 0x04 S4, 0x05 S5
    //
    // Send this EC command from SMM to notify EC and wait for response (EC_C_USBC_SX_ENTRY_WAIT for Sx Entry)
    //
    if (mPlatformFlavor == FlavorDesktop && mEcHandshakeEnable == 1) {
      Timeout = mSystemConfiguration.UsbcSxEntryTimeout;
      UsbcSxEntry (&EcDataBuffer, Timeout);
    }
  }
  //
  // Enable Wakesupport for PCIE Add-on Cards when Native support is disabled
  //
  EnablePchPcieWakeSupport ();

  //
  // Enable PSE wake support
  //
  EnablePchPseWakeSupport ();

  //
  // WARNING!!! Please do not modify GP_LVL register after this point
  //

  //
  // Enable Tier2 GPIO Wake support
  //
  EnablePchTier2GpioWakeSupport ();

  return EFI_SUCCESS;
}

/**
  S5 Sleep Entry Call Back.

  @param[in] DispatchHandle     - The handle of this callback, obtained when registering
  @param[in] DispatchContext    - The predefined context which contained sleep type and phase
  @param[in] CommBuffer         - A pointer to a collection of data in memory that will
                                  be conveyed from a non-SMM environment into an SMM environment.
  @param[in] CommBufferSize     - The size of the CommBuffer.

  @retval EFI_SUCCESS           - Operation successfully performed
**/
EFI_STATUS
EFIAPI
S5SleepEntryCallBack (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  CONST VOID                    *DispatchContext,
  IN  OUT VOID                      *CommBuffer  OPTIONAL,
  IN  UINTN                         *CommBufferSize  OPTIONAL
  )
{
  UINT32    Data32;
  UINT16    Data16;
  UINT8     EcDataBuffer;
  UINT32    Timeout;

  PostCode (BIOS_S5_ENTRY);

  //
  // Put EC in non-ACPI mode.  This ensures EC takes over FAN control from now on till actual shutdown.
  //
  EnableEcAcpiMode (FALSE);

  EcDataBuffer = 0x05; // Input: 0x03 S3, 0x04 S4, 0x05 S5
  if (mEctoPdControllerNegotiationInSx) {
    //
    // Send this EC command from SMM to notify EC and wait for response (EC_C_USBC_SX_ENTRY_WAIT for Sx Entry)
    //

    if (mPlatformFlavor == FlavorDesktop && mEcHandshakeEnable == 1) {
      Timeout = mSystemConfiguration.UsbcSxEntryTimeout;
      UsbcSxEntry (&EcDataBuffer, Timeout);
    }
  }
  //
  // Enable Wakesupport for PCIE Add-on Cards when Native support is disabled
  //
  EnablePchPcieWakeSupport ();

  //
  // Enable PSE wake support
  //
  EnablePchPseWakeSupport ();

  if (mSystemConfiguration.WakeOnRTCS5 == 1) {
    //
    // Clear RTC PM1 status
    //
    mSmst->SmmIo.Io.Read (
                      &mSmst->SmmIo,
                      SMM_IO_UINT16,
                      mAcpiBaseAddr + R_ACPI_IO_PM1_STS,
                      1,
                      &Data16
                      );
    Data16 = Data16 | B_ACPI_IO_PM1_STS_RTC;
    mSmst->SmmIo.Io.Write (
                      &mSmst->SmmIo,
                      SMM_IO_UINT16,
                      mAcpiBaseAddr + R_ACPI_IO_PM1_STS,
                      1,
                      &Data16
                      );
    //
    // set RTC_EN bit in PM1_EN to wake up from the alarm
    //
    mSmst->SmmIo.Io.Read (
                      &mSmst->SmmIo,
                      SMM_IO_UINT16,
                      mAcpiBaseAddr + R_ACPI_IO_PM1_EN,
                      1,
                      &Data16
                      );
    Data16 = Data16 | B_ACPI_IO_PM1_EN_RTC;
    mSmst->SmmIo.Io.Write (
                      &mSmst->SmmIo,
                      SMM_IO_UINT16,
                      mAcpiBaseAddr + R_ACPI_IO_PM1_EN,
                      1,
                      &Data16
                      );
  }
  //
  // Read GPE0 enable register and set PME_B0 enable (bit 13) to enable
  // WOL from S5 state.
  //
  mSmst->SmmIo.Io.Read (
                        &mSmst->SmmIo,
                        SMM_IO_UINT32,
                        mAcpiBaseAddr + R_ACPI_IO_GPE0_EN_127_96,
                        1,
                        &Data32
                        );
  Data32 |= BIT13;
  mSmst->SmmIo.Io.Write (
                        &mSmst->SmmIo,
                        SMM_IO_UINT32,
                        mAcpiBaseAddr + R_ACPI_IO_GPE0_EN_127_96,
                        1,
                        &Data32
                        );

  // @todo Need to check if this is still needed for SKL SDS: This should be removed when WWAN RTD3 and CS function are functional.
  if (mBoardType == BoardTypeSds) {
    TurnNgffWwanOff ();
  }

  //
  // WARNING!!! Please do not modify GP_LVL register after this point
  //

  return EFI_SUCCESS;
}

/**
  When a power button event happens, it shuts off the machine

  @param[in] DispatchHandle    - Handle of this dispatch function
  @param[in] DispatchContext   - Pointer to the dispatch function's context
  @param[in] CommBuffer        - A pointer to a collection of data in memory that will
                                 be conveyed from a non-SMM environment into an SMM environment.
  @param[in] CommBufferSize    - The size of the CommBuffer.

  @retval EFI_SUCCESS          - Operation successfully performed
**/
EFI_STATUS
EFIAPI
PowerButtonCallback (
  IN  EFI_HANDLE                 DispatchHandle,
  IN  CONST VOID                 *DispatchContext,
  IN  OUT VOID                   *CommBuffer  OPTIONAL,
  IN  UINTN                      *CommBufferSize  OPTIONAL
  )
{
  UINT32  Buffer;
  UINT16  Data16;

  //
  // Clear Power Button Status
  //
  Data16 = B_ACPI_IO_PM1_STS_PWRBTN;
  mSmst->SmmIo.Io.Write (
                    &mSmst->SmmIo,
                    SMM_IO_UINT16,
                    mAcpiBaseAddr + R_ACPI_IO_PM1_STS,
                    1,
                    &Data16
                    );

  //
  // Shut it off now
  //
  mSmst->SmmIo.Io.Read (
                    &mSmst->SmmIo,
                    SMM_IO_UINT32,
                    mAcpiBaseAddr + R_ACPI_IO_PM1_CNT,
                    1,
                    &Buffer
                    );
  Buffer &= ~(B_ACPI_IO_PM1_CNT_SLP_EN | B_ACPI_IO_PM1_CNT_SLP_TYP);

  Buffer |= V_ACPI_IO_PM1_CNT_S5;

  mSmst->SmmIo.Io.Write (
                    &mSmst->SmmIo,
                    SMM_IO_UINT32,
                    mAcpiBaseAddr + R_ACPI_IO_PM1_CNT,
                    1,
                    &Buffer
                    );


  Buffer |= B_ACPI_IO_PM1_CNT_SLP_EN;

  mSmst->SmmIo.Io.Write (
                    &mSmst->SmmIo,
                    SMM_IO_UINT32,
                    mAcpiBaseAddr + R_ACPI_IO_PM1_CNT,
                    1,
                    &Buffer
                    );

  return EFI_SUCCESS;
}


/**
  This hardware SMI handler will be run every time the BIOS Write Enable bit is set.

  @param[in] DispatchHandle       Not used

**/
VOID
EFIAPI
PchTcoTimeoutCallback (
  IN  EFI_HANDLE                              DispatchHandle
  )
{

  DEBUG((DEBUG_INFO, "PchTcoTimeoutCallback entry\n"));


  //
  // Stall for 3 seconds to trigger the second timeout.
  //
  MicroSecondDelay (3000 * 1000);

  //
  // A catastrophic crash happened (causing TCO timeout) when we reach here
  // Directly trigger a warm reboot here
  //
  IoWrite8 (R_PCH_IO_RST_CNT, V_PCH_IO_RST_CNT_HARDRESET);

  CpuDeadLoop ();

  return;
}

#if FixedPcdGetBool(PcdCapsuleEnable) == 1
/**
  SMM END_OF_DXE protocol notification event handler.

  @param  Protocol   Points to the protocol's unique identifier
  @param  Interface  Points to the interface instance
  @param  Handle     The handle on which the interface was installed

  @retval EFI_SUCCESS   SmmEndOfDxeCallback runs successfully

**/
EFI_STATUS
EFIAPI
SmmEndOfDxeCallback (
  IN CONST EFI_GUID                       *Protocol,
  IN VOID                                 *Interface,
  IN EFI_HANDLE                           Handle
  )
{
  DEBUG ((DEBUG_INFO, "[SmmPlatform]SMM_END_OF_DXE is signaled\n"));
  mEndOfDxe = TRUE;

  return EFI_SUCCESS;
}

/**
  Software SMI callback to set TopSwap bit. Only allowed to access TopSwap bit before EndOfDxe.

  @param[in]      DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]      DispatchContext Points to an optional handler context which was specified when the
                                  handler was registered.
  @param[in, out] CommBuffer      A pointer to a collection of data in memory that will
                                  be conveyed from a non-SMM environment into an SMM environment.
  @param[in, out] CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS             The interrupt was handled successfully.

**/
EFI_STATUS
EFIAPI
EnableTopSwapCallback (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  CONST VOID                    *DispatchContext,
  IN  OUT VOID                      *CommBuffer  OPTIONAL,
  IN  OUT UINTN                     *CommBufferSize  OPTIONAL
  )
{
  if (!mEndOfDxe) {
    TopSwapSet (TRUE);
  }

  return EFI_SUCCESS;
}

/**
  Software SMI callback to clear TopSwap bit. Only allowed to access TopSwap bit before EndOfDxe.

  @param[in]      DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]      DispatchContext Points to an optional handler context which was specified when the
                                  handler was registered.
  @param[in, out] CommBuffer      A pointer to a collection of data in memory that will
                                  be conveyed from a non-SMM environment into an SMM environment.
  @param[in, out] CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS             The interrupt was handled successfully.

**/
EFI_STATUS
EFIAPI
DisableTopSwapCallback (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  CONST VOID                    *DispatchContext,
  IN  OUT VOID                      *CommBuffer  OPTIONAL,
  IN  OUT UINTN                     *CommBufferSize  OPTIONAL
  )
{
  if (!mEndOfDxe) {
    TopSwapSet (FALSE);
  }

  return EFI_SUCCESS;
}

/**
  Register a SMI handler to set/clear TopSwap bit.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval Other                         SMI handler is not registered.
**/
EFI_STATUS
RegisterTopSwapSwSmiHandler (
  VOID
  )
{
  EFI_STATUS                                Status;
  VOID                                      *SmmEndOfDxeRegistration;
  EFI_SMM_SW_DISPATCH2_PROTOCOL             *SwDispatch;
  EFI_HANDLE                                SwHandle;
  EFI_SMM_SW_REGISTER_CONTEXT               SwContext;

  DEBUG((DEBUG_INFO, "RegisterTopSwapSwSmiHandler entry\n"));

  if (GetFirstGuidHob (&gSkipBiosLockForSysFwUpdateGuid) == NULL) {
    DEBUG ((DEBUG_INFO, "BIOS Update is not intended, skip to register TopSwap SMI callback\n"));
    return EFI_SUCCESS;
  }

  //
  // Register EFI_SMM_END_OF_DXE_PROTOCOL_GUID notify function.
  //
  Status = gSmst->SmmRegisterProtocolNotify (
                    &gEfiSmmEndOfDxeProtocolGuid,
                    SmmEndOfDxeCallback,
                    &SmmEndOfDxeRegistration
                    );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_READY;
  }

  Status = mSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, (VOID**)&SwDispatch);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_READY;
  }

  //
  // Register TopSwap enable/disable handler
  //
  SwContext.SwSmiInputValue = (UINTN) -1;
  Status = SwDispatch->Register (
                         SwDispatch,
                         EnableTopSwapCallback,
                         &SwContext,
                         &SwHandle
                         );
  ASSERT_EFI_ERROR (Status);
  if (Status == EFI_SUCCESS) {
    PcdSet8S (PcdTopSwapEnableSwSmi, (UINT8) SwContext.SwSmiInputValue);
  }

  SwContext.SwSmiInputValue = (UINTN) -1;;
  Status = SwDispatch->Register (
                         SwDispatch,
                         DisableTopSwapCallback,
                         &SwContext,
                         &SwHandle
                         );
  ASSERT_EFI_ERROR (Status);
  if (Status == EFI_SUCCESS) {
    PcdSet8S (PcdTopSwapDisableSwSmi, (UINT8) SwContext.SwSmiInputValue);
  }

  return EFI_SUCCESS;
}
#endif

/**
  Register a SMI handler for Tco timeout event.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid pointer passed.
**/
EFI_STATUS
EFIAPI
RegisterTcoTimeoutHandler (
  VOID
  )
{
  EFI_STATUS                                Status;
  PCH_TCO_SMI_DISPATCH_PROTOCOL             *mPchTcoSmiDispatchProtocol;
  EFI_HANDLE                                Handle;

  Status = mSmst->SmmLocateProtocol (&gPchTcoSmiDispatchProtocolGuid, NULL, (VOID **) &mPchTcoSmiDispatchProtocol);

  Handle = NULL;
  Status = mPchTcoSmiDispatchProtocol->TcoTimeoutRegister (
                                         mPchTcoSmiDispatchProtocol,
                                         PchTcoTimeoutCallback,
                                         &Handle
                                         );
  DEBUG((DEBUG_INFO, "RegisterTcoTimeoutHandler status = %x\n", Status));

  return Status;
}

/**
  Initializes the SMM Platform Driver

  @param[in] ImageHandle   - Pointer to the loaded image protocol for this driver
  @param[in] SystemTable   - Pointer to the EFI System Table

  @retval Status           - EFI_SUCCESS
  @retval Assert, otherwise.

**/
EFI_STATUS
EFIAPI
InitializePlatformSmm (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                                Status;
  EFI_HANDLE                                Handle;
  EFI_HANDLE                                PowerButtonHandle;
  EFI_HANDLE                                SwHandle;
  EFI_HANDLE                                S4SleepEntryHandle;
  EFI_HANDLE                                S5SleepEntryHandle;
#if FixedPcdGetBool (PcdS3Enable) == 1
  EFI_HANDLE                                S3SleepEntryHandle;
#endif

  EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL   *PowerButtonDispatch;
  EFI_SMM_SW_DISPATCH2_PROTOCOL             *SwDispatch;
  EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT     PowerButtonContext;
  EFI_SMM_SW_REGISTER_CONTEXT               SwContext;
  EFI_SMM_SX_DISPATCH2_PROTOCOL             *SxDispatch;
  EFI_SMM_SX_REGISTER_CONTEXT               EntryDispatchContext;
  PLATFORM_NVS_AREA_PROTOCOL                *PlatformNvsAreaProtocol;
  UINTN                                     DataSize;

  SETUP_CPU_FEATURES                        SetupCpuFeatures;
  UINT32                                    VariableAttr;
  UINT64                                    SmmFeatureMsr;
  PCH_ESPI_SMI_DISPATCH_PROTOCOL            *PchEspiSmiDispatchProtocol;

  Handle              = NULL;
  PowerButtonHandle   = NULL;
  SwHandle            = NULL;

  PostCode (PLATFORM_SMM_INIT_ENTRY);

  //
  // Great!  We're now in SMM!
  //
  mEctoPdControllerNegotiationInSx = PcdGetBool (PcdUsbcEcPdNegotiation) ? 1 : 0;
  mFpsWakeGpio = PcdGet32(PcdFingerPrintIrqGpio);
  //
  // Locate Platform Info Protocol.
  //
  mPlatformFlavor = PcdGet8 (PcdPlatformFlavor);
  mEcPresent      = PcdGetBool (PcdEcPresent);
  mGpioTier2WakeSupport = PcdGetBool (PcdGpioTier2WakeEnable);

  //
  // Initialize global variables
  //
  mSmst = gSmst;

  //
  // Locate setup variable
  // We assert if it is not found because we have a dependency on AcpiPlatform which is
  // dependent on protocols the setup driver produces.
  //
  DataSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &DataSize,
                  &mSystemConfiguration
                  );
//  ASSERT_EFI_ERROR (Status);

  //
  // Determine if EC TCSS handshake is enabled
  //
  mEcHandshakeEnable = 0;
  if ((mSystemConfiguration.UsbcBiosTcssHandshake == 1) && (!PcdGetBool(PcdBoardPmcPdEnable))) {
    mEcHandshakeEnable = 1;
  }

  DataSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &DataSize,
                  &mPchSetup
                  );
  //
  // Get the ACPI Base Address
  //
  mAcpiBaseAddr = PmcGetAcpiBase ();

  //
  // Disable RTC alarm and clear RTC PM1 status
  //
  InitRtcWakeup();

  //
  // Locate the ICH SMM Power Button dispatch protocol
  //
  Status = mSmst->SmmLocateProtocol (&gEfiSmmPowerButtonDispatch2ProtocolGuid, NULL, (VOID**)&PowerButtonDispatch);
  ASSERT_EFI_ERROR (Status);

  //
  // Register the power button SMM event
  //
  PowerButtonContext.Phase = EfiPowerButtonEntry;
  Status = PowerButtonDispatch->Register (
                                  PowerButtonDispatch,
                                  PowerButtonCallback,
                                  &PowerButtonContext,
                                  &PowerButtonHandle
                                  );
  ASSERT_EFI_ERROR (Status);

  //
  //  Locate the ICH SMM SW dispatch protocol
  //
  Status = mSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, (VOID**)&SwDispatch);
  ASSERT_EFI_ERROR (Status);

  //
  // Locate our shared data area
  //
  Status = gBS->LocateProtocol (&gPlatformNvsAreaProtocolGuid, NULL, (VOID **) &PlatformNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);
  mPlatformNvsAreaPtr = PlatformNvsAreaProtocol->Area;

  //
  // Register ACPI enable handler
  //
  SwContext.SwSmiInputValue = (UINTN) PcdGet8 (PcdAcpiEnableSwSmi);
  Status = SwDispatch->Register (
                         SwDispatch,
                         EnableAcpiCallback,
                         &SwContext,
                         &SwHandle
                         );
  ASSERT_EFI_ERROR (Status);

  //
  // Register ACPI disable handler
  //
  SwContext.SwSmiInputValue = (UINTN) PcdGet8 (PcdAcpiDisableSwSmi);
  Status = SwDispatch->Register (
                         SwDispatch,
                         DisableAcpiCallback,
                         &SwContext,
                         &SwHandle
                         );
  ASSERT_EFI_ERROR (Status);

#ifdef DOCK_ENABLE
  //
  // Register PCIe Dock Bridges IO MEM Base Limit Patch Handler
  //
  SwContext.SwSmiInputValue = (UINTN) PcdGet8 (PcdPcieDockBridgeResourcePatchSmi);
  Status = SwDispatch->Register (
                         SwDispatch,
                         PcieDockSmiCallback,
                         &SwContext,
                         &SwHandle
                         );
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // Locate the SmmSxDispatch protocol
  //
  Status = mSmst->SmmLocateProtocol (&gEfiSmmSxDispatch2ProtocolGuid, NULL, (VOID**)&SxDispatch);
  if (EFI_ERROR (Status)) {
    return Status;
  }

#if FixedPcdGetBool (PcdS3Enable) == 1
  //
  // Register S3 entry phase call back function
  //
  EntryDispatchContext.Type  = SxS3;
  EntryDispatchContext.Phase = SxEntry;
  Status = SxDispatch->Register (
                         SxDispatch,
                         S3SleepEntryCallBack,
                         &EntryDispatchContext,
                         &S3SleepEntryHandle
                         );
#endif
  //
  // Register S4-Entry phase callback function
  //
  EntryDispatchContext.Type  = SxS4;
  EntryDispatchContext.Phase = SxEntry;
  Status = SxDispatch->Register (
                         SxDispatch,
                         S4SleepEntryCallBack,
                         &EntryDispatchContext,
                         &S4SleepEntryHandle
                         );
  //
  // Register S5 entry phase call back function
  //
  EntryDispatchContext.Type  = SxS5;
  EntryDispatchContext.Phase = SxEntry;
  Status = SxDispatch->Register (
                         SxDispatch,
                         S5SleepEntryCallBack,
                         &EntryDispatchContext,
                         &S5SleepEntryHandle
                         );

  //
  // Check MSR SMM_MCA_CAP(0x17D) whether supports CPU SMM Enhancement Feature
  //
  DataSize = sizeof (SETUP_CPU_FEATURES);
  Status = gRT->GetVariable (
                  L"SetupCpuFeatures",
                  &gSetupVariableGuid,
                  &VariableAttr,
                  &DataSize,
                  &SetupCpuFeatures
                  );
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "Get CPU Feature variable failure \n"));
  }

  SetupCpuFeatures.SmmEnhancementSupported = 0;
  SetupCpuFeatures.SmmTargetedSmiAvailable = 0;
  SetupCpuFeatures.SmmCpuSvrstrAvailable = 0;
  SetupCpuFeatures.SmmLongFlowAvailable = 0;
  SmmFeatureMsr = AsmReadMsr64 (MSR_SMM_MCA_CAP);
  if ((SmmFeatureMsr & (B_MSR_SMM_MCA_CAP_TARGETED_SMI_MASK | B_MSR_SMM_MCA_CAP_SMM_CPU_SVRSTR_MASK | B_MSR_SMM_MCA_CAP_SMM_CODE_ACCESS_CHK_MASK | B_MSR_SMM_MCA_CAP_LONG_FLOW_INDICATION_MASK)) != 0) {
    SetupCpuFeatures.SmmEnhancementSupported = 1;
    SetupCpuFeatures.SmmTargetedSmiAvailable = (UINT8) RShiftU64((SmmFeatureMsr & B_MSR_SMM_MCA_CAP_TARGETED_SMI_MASK), N_MSR_SMM_MCA_CAP_TARGETED_SMI_OFFSET);
    SetupCpuFeatures.SmmCpuSvrstrAvailable   = (UINT8) RShiftU64((SmmFeatureMsr & B_MSR_SMM_MCA_CAP_SMM_CPU_SVRSTR_MASK), N_MSR_SMM_MCA_CAP_SMM_CPU_SVRSTR_OFFSET);
    SetupCpuFeatures.SmmLongFlowAvailable    = (UINT8) RShiftU64((SmmFeatureMsr & B_MSR_SMM_MCA_CAP_LONG_FLOW_INDICATION_MASK), N_MSR_SMM_MCA_CAP_LONG_FLOW_INDICATION_OFFSET);
  }

  Status = gRT->SetVariable (
                  L"SetupCpuFeatures",
                  &gSetupVariableGuid,
                  VariableAttr,
                  DataSize,
                  &SetupCpuFeatures
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Set CPU Feature variable failure \n"));
  }

#if FixedPcdGetBool(PcdS3Enable) == 1
  //
  // Initialize RuntimeScriptTable base address
  //
  Status = InitializeSmmScriptLib (SystemTable, 2, &(mAcpiSmm.RuntimeScriptTableBase));
  DEBUG((DEBUG_INFO, "RuntimeScriptTableBase is 0x%x\n", mAcpiSmm.RuntimeScriptTableBase));
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // Lock HMRFPO
  // Output parameters are stored in global variables that can be used in subsequent calls in SMM
  // call back functions, e.g., HMRFPO Enable
  //

  //
  //   Locate the PCH eSPI SMI dispatch protocol.
  //
  PchEspiSmiDispatchProtocol = NULL;
  Status = mSmst->SmmLocateProtocol (&gPchEspiSmiDispatchProtocolGuid, NULL, (VOID **) &PchEspiSmiDispatchProtocol);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "Locate the PCH eSPI SMI dispatch protocol failure\n"));
  } else {

    //
    // Register an eSPI EC SMI callback function.
    //
    Handle = NULL;
    Status = PchEspiSmiDispatchProtocol->EspiSlaveSmiRegister (
                                       PchEspiSmiDispatchProtocol,
                                       eSpiEcSmiCallback,
                                       &Handle
                                       );
    if (EFI_ERROR(Status)) {
      DEBUG((DEBUG_ERROR, "Register eSPI EC SMI callback function failure\n"));
    }
  }

  //
  // Register TCO timeout SMI handler
  //
  Status = RegisterTcoTimeoutHandler ();

#if FixedPcdGetBool(PcdCapsuleEnable) == 1
  //
  // TopSwap Manipulation SMI handler
  //
  Status = RegisterTopSwapSwSmiHandler ();
#endif

  PostCode(PLATFORM_SMM_INIT_EXIT);

  return EFI_SUCCESS;
}
