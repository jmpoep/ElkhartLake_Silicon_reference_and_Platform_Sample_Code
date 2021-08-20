/** @file
  PEI ITSS Lib.

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

#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/HobLib.h>
#include <Library/PsfLib.h>
#include <Library/PeiP2sbPrivateLib.h>
#include <Library/GpioPrivateLib.h>
#include <Register/P2sbRegs.h>
#include <Register/ItssRegs.h>
#include <PchPcieRpInfo.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PciSegmentLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/PeiItssLib.h>

#include "ItssLibInternal.h"

/**
  Retrieve ITSS Interrupt Config policy

  @param[in]  SiPolicy  Policy

  @retval InterruptConfig
**/
STATIC
PCH_INTERRUPT_CONFIG*
ItssGetIntConfigPolicy (
  IN CONST SI_POLICY_PPI  *SiPolicy
  )
{
  EFI_STATUS                   Status;
  PCH_INTERRUPT_CONFIG         *InterruptConfig;
  STATIC PCH_INTERRUPT_CONFIG  *StaticInterruptConfig = NULL;

  if (StaticInterruptConfig != NULL) {
    return StaticInterruptConfig;
  }

  Status = GetConfigBlock ((VOID *) SiPolicy, &gInterruptConfigGuid, (VOID *) &InterruptConfig);
  ASSERT_EFI_ERROR (Status);

  StaticInterruptConfig = InterruptConfig;

  return InterruptConfig;
}

/**
  Before any interrupt is enabled, set master message enable.
**/
VOID
ItssSetMasterMessageEnable (
  VOID
  )
{
  ///
  /// Before any interrupt is enabled, set ITSS.MMC, PCR[ITSS] + 3334h[0] = 1b.
  ///
  PchPcrWrite16 (PID_ITSS, R_ITSS_PCR_MMC, (UINT16) B_ITSS_PCR_MMC_MSTRMSG_EN);
}

/**
  Write to mask registers of master and slave 8259 PICs.
**/
VOID
ItssMask8259Interrupts (
  VOID
  )
{
  IoWrite8 (R_ITSS_IO_8259_MASK_MASTER, 0xFF);
  IoWrite8 (R_ITSS_IO_8259_MASK_SLAVE, 0xFF);
}

/**
  This function will configure ITSS.PIRx registers for INTx->PIRy routing
  based on devices interrupt pin (INTx) and chosen IRQ for it.

  @param[in] DevIntConfigEntry       Table with interrupt assignment
  @param[in] DevIntConfigEntrySize   Number of entries in interrupt assignment table
**/
VOID
UpdatePirxRegs (
  IN PCH_DEVICE_INTERRUPT_CONFIG     *DevIntConfigEntry,
  IN UINT8                           DevIntConfigEntrySize
  )
{
  UINT16                    PirxIndex;
  UINT16                    DevIndex;
  UINT16                    Data16;
  CONST PCH_PIRX_REGISTER*  PirRegData;
  UINT32                    PirRegDataSize;
  CONST PCH_DEV_INT_INFO    *PchDeviceIntInfo;
  UINT32                    PchDeviceIntInfoSize;
  UINT8                     PchDeviceIntInfoIndex;
  BOOLEAN                   UsesPirq;

  PchDeviceIntInfo = GetInterruptInfoData (&PchDeviceIntInfoSize);

  PirRegData = GetPirxRegData (&PirRegDataSize);

  for (PirxIndex = 0; PirxIndex < PirRegDataSize; PirxIndex++) {
    //
    // Default value for each PIRx register is 3210h
    //
    Data16 = 0x3210;
    for (DevIndex = 0; DevIndex < DevIntConfigEntrySize; DevIndex++) {
      if (DevIntConfigEntry[DevIndex].Device == PirRegData[PirxIndex].Device) {

        UsesPirq = TRUE;
        //
        // Check if device is under INTx->PIRQy mapping
        //
        for (PchDeviceIntInfoIndex = 0; PchDeviceIntInfoIndex < PchDeviceIntInfoSize; PchDeviceIntInfoIndex++) {
          if ((DevIntConfigEntry[DevIndex].Device == PchDeviceIntInfo[PchDeviceIntInfoIndex].Device) &&
              (DevIntConfigEntry[DevIndex].Function == PchDeviceIntInfo[PchDeviceIntInfoIndex].Function)) {
            if (PchDeviceIntInfo[PchDeviceIntInfoIndex].UsesPirq == USES_PIRQ_NO) {
              UsesPirq = FALSE;
            }
            break;
          }
        }

        if (UsesPirq) {
          Data16 &= ~(UINT16) (0xF << (4*(DevIntConfigEntry[DevIndex].IntX - PchIntA)));
          Data16 |= (UINT16) ((DevIntConfigEntry[DevIndex].Irq - 16) << (4*(DevIntConfigEntry[DevIndex].IntX - PchIntA)));
        }
      }
    }
    PchPcrWrite16 (PID_ITSS, R_ITSS_PCR_PIR0 + PirRegData[PirxIndex].PirIndex * 0x2, Data16);
  }
}


#ifndef MDEPKG_NDEBUG
/**
  Check interrupt assignment, provide information if detected improper interrupt setting

  @param[in] DevIntConfigEntry        Table with interrupt assignment
  @param[in] DevIntConfigEntrySize    Number of entries in interrupt assignment table
**/
STATIC
VOID
CheckInterruptSettings (
  IN PCH_DEVICE_INTERRUPT_CONFIG      *DevIntConfigEntry,
  IN UINT8                            DevIntConfigEntrySize
  )
{
  DEBUG_CODE_BEGIN ();
  //
  // Algorithm which will parse whole table and check it correctness, to prevent
  // users from trying to set PCH devices interrupt in non supported way.
  // Function is divided into few step, each verifying different cases:
  // Point 1.
  //  - Entry for certain DxFy appears more than once
  //  - Device is outside D18Fx-D31Fx range
  // Point 2.
  //  - InterruptConfig table contains invalid DxFy (does not generate interrupt or does not exist)
  //  - Device which falls under INTx->PIRQy mapping has its IRQ set outside IRQ16-23 range
  //  - Device uses IRQ 0, 2 or 8
  // Point 3.
  //  - Single function device does not use INTA
  // Point 4.
  //  - Within multifunctional devices same interrupt pin (INTx) is routed to different PIRQy (IRQ16-23)
  // Point 4b.
  //  -  Devices under the same INTx->PIRQy mapping register (PIRn) request conflicting routing
  // Point 5.
  //  - Devices which have interrupt pin setting as RWO are not programmed
  //  - Devices which have requirement for interrupt pin configuration are not programmed correctly
  //  - InterruptConfig has InterruptPin setting not matching default value of INTP register when it is RO
  // Point 6.
  //  - PCI Express Root Ports mapping are recommended to be programmed only with one set of values:
  //     D(29/28/27)Fy -> INTP = (y % 4) , IRQ = 16 + (y % 4)
  //    otherwise _PRT methods in ACPI for RootPorts would require additional patching as
  //    PCIe Endpoint Device Interrupt is further subjected to INTx to PIRQy Mapping
  // Point 7.
  //  - Devices which should have unique interrupt share it
  // Point 8.
  //  - GPIO pads which are routed to IOxAPIC cause an IRQ which is already in use by other device or pad
  //
  // Note: this routine is not able to check if eSPI device is using IRQ >=24 and if it collides with other devices or GPIO pads IRQ usage
  //
  CONST PCH_DEV_INT_INFO    *PchDeviceIntInfo;
  UINT32                    PchDeviceIntInfoIndex;
  UINT32                    PchDeviceIntInfoIndex2;
  UINT8                     DevIntConfigIndex;
  UINT8                     DevIntConfigIndex2;
  CONST PCH_PIRX_REGISTER   *PirRegData;
  UINT32                    PirRegDataSize;
  UINT8                     Index;
  UINT32                    PchDeviceIntInfoSize;
  BOOLEAN                   DevExist;
  BOOLEAN                   IrqError;
  BOOLEAN                   SingleFunctionDev;
  UINT32                    CurrentDevice;
  UINT8                     FunctionNumber;
  UINT8                     IntRouting[4];
  GPIO_GROUP                GroupMin;
  GPIO_GROUP                GroupMax;
  GPIO_GROUP                Group;
  UINT32                    PadNumber;
  GPIO_PAD                  GpioPad;
  UINT32                    GpioIrqNumber;
  GPIO_CONFIG               GpioData;
  GPIO_PAD_OWN              PadOwnVal;
  UINT8                     PirxIndex;
  UINT8                     PirxSubIndex;
  BOOLEAN                   FirstDeviceAnalyzed;
  UINT32                    MinDevNum;
  UINT32                    MaxDevNum;

  ///
  /// Value of 1 on selected bit position indicates that IRQ is being used
  /// IrqUsage[0] - for IRQ0-31
  /// IrqUsage[1] - for IRQ31-63
  /// IrqUsage[2] - for IRQ64-95
  /// IrqUsage[3] - for IRQ96-127
  ///
  UINT32         IrqUsage[4];

  ZeroMem (IrqUsage, sizeof (IrqUsage));

  PchDeviceIntInfoSize = 0;
  PchDeviceIntInfo = GetInterruptInfoData (&PchDeviceIntInfoSize);
  MinDevNum = PchDeviceIntInfo[0].Device;
  MaxDevNum = PchDeviceIntInfo[PchDeviceIntInfoSize - 1].Device;

  //
  // 1.Check if for each DxFy there is only one entry and if none of devices is outside the range of supported devices
  //
  for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {

    if ((DevIntConfigEntry[DevIntConfigIndex].Device < MinDevNum) ||
        (DevIntConfigEntry[DevIntConfigIndex].Device > MaxDevNum)) {
      //
      // Report an error if device number is outside 18-31 range
      //
      DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: InterruptConfig has a device (D%dF%d) which is outside D%d-D%d range!\n",
              DevIntConfigEntry[DevIntConfigIndex].Device,
              DevIntConfigEntry[DevIntConfigIndex].Function,
              MinDevNum,
              MaxDevNum));
      ASSERT (FALSE);
      return;
    }

    for (DevIntConfigIndex2 = DevIntConfigIndex + 1; DevIntConfigIndex2 < DevIntConfigEntrySize; DevIntConfigIndex2++) {

      if ((DevIntConfigEntry[DevIntConfigIndex].Device == DevIntConfigEntry[DevIntConfigIndex2].Device) &&
          (DevIntConfigEntry[DevIntConfigIndex].Function == DevIntConfigEntry[DevIntConfigIndex2].Function)) {
        //
        // Report an error if entry appears more than once
        //
        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Entry for D%dF%d appears more than once!\n",
                DevIntConfigEntry[DevIntConfigIndex].Device,
                DevIntConfigEntry[DevIntConfigIndex].Function));
        ASSERT (FALSE);
        return;
      }
    }
  }

  //
  // 2.Check if for each DnFx selected IRQ is supported for device. If device uses INTx->PIRQy mapping
  //   must have IRQ  >= 16 and IRQ <= 23. Report an error if DevIntConfigEntry[] consist of
  //   device which does not generate interrupts, is not a valid device or uses IRQ0,2,8
  //
  for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {

    DevExist = FALSE;

    PchDeviceIntInfoIndex = (DevIntConfigEntry[DevIntConfigIndex].Device - MinDevNum)*8 + DevIntConfigEntry[DevIntConfigIndex].Function;
    if (PchDeviceIntInfo[PchDeviceIntInfoIndex].ValidDevice == VALID_DEV_YES) {

      DevExist = TRUE;
      //
      // Check if InterruptConfig consist of entry for device which does not generate interrupt
      //
      if (PchDeviceIntInfo[PchDeviceIntInfoIndex].UsesInterrupts == INTERRUPT_NO) {
        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: D%dF%d does not generate interrupts!\n",
                DevIntConfigEntry[DevIntConfigIndex].Device,
                DevIntConfigEntry[DevIntConfigIndex].Function));
        ASSERT (FALSE);
        return;
      }

      //
      // Check if for device which uses INTx -> PIRQy mapping has its IRQ set outside 16 to 23 range
      // NOTE: If cAVS/HDa is going to be supported in ACPI mode then this check needs to be rewritten.
      // HDa in PCI mode is under INTx->PIRQy mapping but in ACPI mode can have its IRQ outside 16 to 23 range.
      //
      if (PchDeviceIntInfo[PchDeviceIntInfoIndex].UsesPirq == USES_PIRQ_YES) {
        if (DevIntConfigEntry[DevIntConfigIndex].Irq < 16 || DevIntConfigEntry[DevIntConfigIndex].Irq > 23) {
          DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: D%dF%d has its IRQ outside 16 to 23 range!\n",
                  DevIntConfigEntry[DevIntConfigIndex].Device,
                  DevIntConfigEntry[DevIntConfigIndex].Function));
          ASSERT (FALSE);
          return;
        }
      }

      //
      // Check if IRQ for device is not set to 0,2 or 8
      //
      if ((DevIntConfigEntry[DevIntConfigIndex].Irq == 0) ||
          (DevIntConfigEntry[DevIntConfigIndex].Irq == 2) ||
          (DevIntConfigEntry[DevIntConfigIndex].Irq == 8)) {
        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Device D%dF%d must not use IRQ%d!\n",
                DevIntConfigEntry[DevIntConfigIndex].Device,
                DevIntConfigEntry[DevIntConfigIndex].Function,
                DevIntConfigEntry[DevIntConfigIndex].Irq));
        ASSERT (FALSE);
        return;
      }
    }

    //
    // If device from InterruptConfig was not found in mPchDeviceInterruptInfo[] table then
    // it it is not a valid entry.
    //
    if (DevExist == FALSE) {
      DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: D%dF%d is not a valid device!\n",
              DevIntConfigEntry[DevIntConfigIndex].Device,
              DevIntConfigEntry[DevIntConfigIndex].Function));
      ASSERT (FALSE);
      return;
    }
  }

  //
  // 3.Check if single function device is set to use INTA
  //
  // Locate in mPchDeviceInterruptInfo table single function devices, if found one locate it in InterruptConfig
  // and check if it uses INTA.
  //
  for (PchDeviceIntInfoIndex = 0; PchDeviceIntInfoIndex < PchDeviceIntInfoSize; PchDeviceIntInfoIndex+=8) {
    if (PchDeviceIntInfo[PchDeviceIntInfoIndex].ValidDevice == VALID_DEV_NO) {
      //
      // If DxF0 is not a valid device move to next one.
      //
      continue;
    }
    SingleFunctionDev = TRUE;

    for (PchDeviceIntInfoIndex2 = PchDeviceIntInfoIndex + 1; PchDeviceIntInfoIndex2 < PchDeviceIntInfoIndex + 8; PchDeviceIntInfoIndex2++) {
      //
      // Check other functions of this device (DxF1-DxF7)
      //
      if (PchDeviceIntInfo[PchDeviceIntInfoIndex2].ValidDevice == VALID_DEV_YES) {
        //
        // If found another valid device for certain device number then this is not a signle function device.
        //
        SingleFunctionDev = FALSE;
        break;
      }
    }

    if (SingleFunctionDev == TRUE) {
      //
      // Found a single function device, try to locate it InterruptConfig
      //
      for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {

        if (DevIntConfigEntry[DevIntConfigIndex].Device == PchDeviceIntInfo[PchDeviceIntInfoIndex].Device) {
          //
          // Found device in InterruptConfig, check its interrupt pin
          //
          if (DevIntConfigEntry[DevIntConfigIndex].IntX != PchIntA) {
            //
            // If single function device doesn't use INTA report an error
            //
            DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Single function device %d isn't configured to use INTA!\n",DevIntConfigEntry[DevIntConfigIndex].Device));
            ASSERT (FALSE);
            return;
          }
        }
      }
    }
  }

  //
  // 4.Check if for one device which uses INTx->PIRQy mapping different functions
  //   with the same INTx are not routed to different PIRQs (IRQ16-23)
  //
  CurrentDevice = 0;
  for (PchDeviceIntInfoIndex = 0; PchDeviceIntInfoIndex < PchDeviceIntInfoSize; PchDeviceIntInfoIndex++) {
    if ((PchDeviceIntInfo[PchDeviceIntInfoIndex].Device == CurrentDevice) ||
        (PchDeviceIntInfo[PchDeviceIntInfoIndex].UsesPirq == USES_PIRQ_NO) ||
        (PchDeviceIntInfo[PchDeviceIntInfoIndex].ValidDevice == VALID_DEV_NO)) {
      //
      // Skip to next device if current was already analyzed,
      // it doesn't use INTx->PIRQy mapping or it is not a PCH device
      //
      continue;
    }
    CurrentDevice = PchDeviceIntInfo[PchDeviceIntInfoIndex].Device;
    ZeroMem (IntRouting, sizeof (IntRouting));

    for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {

      if (DevIntConfigEntry[DevIntConfigIndex].Device == CurrentDevice) {

        if ((DevIntConfigEntry[DevIntConfigIndex].IntX >= PchIntA) &&
            (DevIntConfigEntry[DevIntConfigIndex].IntX <= PchIntD)) {
          //
          // Check if INTx is mapped to the same PIRQy for all functions within one device.
          // NOTE: If cAVS/HDa is going to be supported in ACPI mode then this check needs to be rewritten.
          // HDa in PCI mode is under INTx->PIRQy mapping but when in ACPI mode it can have its IRQ set
          // outside 16 to 23 range and doesn't need to meet criteria analyzed here.
          //
          if (IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] == 0) {
            IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] = DevIntConfigEntry[DevIntConfigIndex].Irq;
          } else if (IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] != DevIntConfigEntry[DevIntConfigIndex].Irq) {
            // Modify this to warning instead of error and assertion because EHL DMA device requires distinctive IRQ#
            DEBUG ((DEBUG_ERROR, "InterruptConfig warning: For D%d INT%c is mapped to different IRQs!\n",
                    CurrentDevice,
                    DevIntConfigEntry[DevIntConfigIndex].IntX + 64));
            IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] = DevIntConfigEntry[DevIntConfigIndex].Irq;
          }
        }
      }
    }
  }

  PirRegData = GetPirxRegData (&PirRegDataSize);

  //
  // 4b. Check if devices under the same INTx->PIRQy mapping register (PIRn)
  //     do not request conflicting routing
  //
  for (PirxIndex = 0; PirxIndex < PirRegDataSize - 1; PirxIndex++) {

    //
    // Initialize INTx->PIRQy mapping table
    // 0xFF - mapping unspecified
    //
    SetMem (IntRouting, sizeof (IntRouting), 0xFF);
    FirstDeviceAnalyzed = FALSE;
    //
    // Check if more than one devices is mapped to the same PIRn register
    //
    for (PirxSubIndex = PirxIndex + 1; PirxSubIndex < PirRegDataSize; PirxSubIndex++) {
      if (PirRegData[PirxSubIndex].PirIndex == PirRegData[PirxIndex].PirIndex) {
        //
        // Two devices (Dxx) use the same PIRn register
        //
        // Get first devices INTx->PIRQy mapping
        //
        if (!FirstDeviceAnalyzed) {
          for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {
            if (DevIntConfigEntry[DevIntConfigIndex].Device == PirRegData[PirxIndex].Device) {
              //
              // Check if device is under INTx->PIRQy mapping
              //
              PchDeviceIntInfoIndex = (DevIntConfigEntry[DevIntConfigIndex].Device - MinDevNum)*8 + DevIntConfigEntry[DevIntConfigIndex].Function;
              if (PchDeviceIntInfo[PchDeviceIntInfoIndex].UsesPirq == USES_PIRQ_NO) {
                continue;
              }

              IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] = DevIntConfigEntry[DevIntConfigIndex].Irq;
            }
          }
          FirstDeviceAnalyzed = TRUE;
        }

        //
        // Analyze another device INTx->PIRQy mapping and check if it conflicts with previous one
        //
        for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {
          if (DevIntConfigEntry[DevIntConfigIndex].Device == PirRegData[PirxSubIndex].Device) {
            //
            // Check if device is under INTx->PIRQy mapping
            //
            PchDeviceIntInfoIndex = (DevIntConfigEntry[DevIntConfigIndex].Device - MinDevNum)*8 + DevIntConfigEntry[DevIntConfigIndex].Function;
            if (PchDeviceIntInfo[PchDeviceIntInfoIndex].UsesPirq == USES_PIRQ_NO) {
              continue;
            }

            //
            // If mapping for certain IntX was not specified by previous device update it
            //
            if (IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] == 0xFF) {
              IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] = DevIntConfigEntry[DevIntConfigIndex].Irq;

            //
            // Check if there is no conflicting mapping
            //
            } else if (IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] != DevIntConfigEntry[DevIntConfigIndex].Irq) {
              DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: For D%d and D%d there is conflicting INT%c to IRQ mapping!\n",
                      PirRegData[PirxIndex].Device,
                      PirRegData[PirxSubIndex].Device,
                      DevIntConfigEntry[DevIntConfigIndex].IntX + 64
                      ));
              ASSERT (FALSE);
              return;
            }
          }
        }
      }
    }
  }

  //
  // 5. Check if devices which have special requirement regarding InterruptPin
  //    are properly configured in InterruptConfig table
  //
  for (PchDeviceIntInfoIndex = 0; PchDeviceIntInfoIndex < PchDeviceIntInfoSize; PchDeviceIntInfoIndex++) {
    if ((PchDeviceIntInfo[PchDeviceIntInfoIndex].IntPinRequirement != INTP_NO_REQ) &&
        (PchDeviceIntInfo[PchDeviceIntInfoIndex].ValidDevice == VALID_DEV_YES)) {
      //
      // Found a device which has special requirement regarding interrupt pin.
      // If devices requires its INTP register programmed then entry for this device must be included
      // in InterruptConfig.
      // If INTP is RO register, then either this device may be omitted in InterruptConfig or
      // if included then InterruptPin value must match the one preset in this register.
      //
      DevExist = FALSE;
      for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {

        if ((DevIntConfigEntry[DevIntConfigIndex].Device == PchDeviceIntInfo[PchDeviceIntInfoIndex].Device) &&
            (DevIntConfigEntry[DevIntConfigIndex].Function == PchDeviceIntInfo[PchDeviceIntInfoIndex].Function)) {

          if (PchDeviceIntInfo[PchDeviceIntInfoIndex].IntPinRequirement == INTP_MUST_SET) {
            //
            // Device  which required its INTP to be set was found, move to next one
            //
            DevExist = TRUE;
            break;
          } else {
            //
            // If device has its INTP in RO register or there are other requirements for it,
            // then InterruptConfig must match expected configuration
            //
            if ((UINT32) (DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA) != (PchDeviceIntInfo[PchDeviceIntInfoIndex].IntPinRequirement - INTP_IS_INTA)) {
              DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Device D%dF%d can use only INT%c!\n",
                      PchDeviceIntInfo[PchDeviceIntInfoIndex].Device,
                      PchDeviceIntInfo[PchDeviceIntInfoIndex].Function,
                      PchDeviceIntInfo[PchDeviceIntInfoIndex].IntPinRequirement - INTP_IS_INTA + 65));
              ASSERT (FALSE);
              return;
            }
          }
        }
      }
      if ((DevExist == FALSE) &&
          (PchDeviceIntInfo[PchDeviceIntInfoIndex].IntPinRequirement == INTP_MUST_SET)) {
        //
        // If after analyzing all entries in DevIntConfigEntry[] table
        // there is no required device, report an error
        //
        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Device D%dF%d is not included in InterruptConfig table!\n",
                PchDeviceIntInfo[PchDeviceIntInfoIndex].Device,
                PchDeviceIntInfo[PchDeviceIntInfoIndex].Function));
        ASSERT (FALSE);
        return;
      }
    }
  }

  //
  // 6. Check if PCI Express Root Ports mapping is programmed in following way
  //    D(27-29)Fy -> INTP = (y % 4) , IRQ = 16 + (y % 4)
  //
  for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {
    if ((DevIntConfigEntry[DevIntConfigIndex].Device == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1) ||
        (DevIntConfigEntry[DevIntConfigIndex].Device == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3)) {

      FunctionNumber = DevIntConfigEntry[DevIntConfigIndex].Function;
      if ((DevIntConfigEntry[DevIntConfigIndex].Irq != (16 + (FunctionNumber % 4))) ||
          ((DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA) != (FunctionNumber % 4))) {

        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: RootPort Device D%dF%d is not programmed with recommended interrupt settings!\n",
                DevIntConfigEntry[DevIntConfigIndex].Device,
                DevIntConfigEntry[DevIntConfigIndex].Function));
        ASSERT (FALSE);
        return;
      }
    }
  }

  //
  // 7. Check if devices which need unique IRQ do not share it with other devices.
  //
  IrqError = FALSE;
  for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {
    //
    // Save IRQ number used by this device. This information will be needed for Step 7
    // for GPIO interrupts check.
    //
    IrqUsage[DevIntConfigEntry[DevIntConfigIndex].Irq >> 5]|= 0x1 << (DevIntConfigEntry[DevIntConfigIndex].Irq % 32);

    PchDeviceIntInfoIndex = (DevIntConfigEntry[DevIntConfigIndex].Device - MinDevNum) * 8 + DevIntConfigEntry[DevIntConfigIndex].Function;
    if (PchDeviceIntInfo[PchDeviceIntInfoIndex].IrqUnique == IRQ_UNIQUE_NO) {
      //
      // IRQ can be shared, move to next device
      //
      continue;
    }
    //
    // Device which needs unique IRQ was found, now search for another device which uses the same IRQ
    //
    for (DevIntConfigIndex2 = DevIntConfigIndex + 1; DevIntConfigIndex2 < DevIntConfigEntrySize; DevIntConfigIndex2++) {
      if (DevIntConfigEntry[DevIntConfigIndex].Irq == DevIntConfigEntry[DevIntConfigIndex2].Irq) {
        //
        // If found device with the same IRQ check its number,
        // if IRQ > 23 it must be unique - report an error,
        // If IRQ <= 23 it can be shared but only between devices with different PortID
        //
        if (DevIntConfigEntry[DevIntConfigIndex].Irq > 23 ) {
          IrqError = TRUE;
        } else {
          //
          // Check if device which has the same IRQ (which is <=23) can share interrupt
          //
          PchDeviceIntInfoIndex2 = (DevIntConfigEntry[DevIntConfigIndex2].Device - MinDevNum) * 8 + DevIntConfigEntry[DevIntConfigIndex2].Function;
          if (PchDeviceIntInfo[PchDeviceIntInfoIndex].IrqUnique == PchDeviceIntInfo[PchDeviceIntInfoIndex2].IrqUnique) {
            //
            // If both of these devices are the same type their IRQs must be unique
            //
            IrqError = TRUE;
          }
        }

        //
        // If found an IRQ sharing between devices which require unique interrupt then assert.
        //
        if (IrqError == TRUE) {
          DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Device D%dF%d and D%dF%d share interrupt (IRQ%d)!\n",
                  DevIntConfigEntry[DevIntConfigIndex].Device,
                  DevIntConfigEntry[DevIntConfigIndex].Function,
                  DevIntConfigEntry[DevIntConfigIndex2].Device,
                  DevIntConfigEntry[DevIntConfigIndex2].Function,
                  DevIntConfigEntry[DevIntConfigIndex].Irq));
          ASSERT (FALSE);
          return;
        }
      }
    }
  }

  //
  // 8. Check if any GPIO pad which is routed to IOxAPIC does not share it with
  //    other pads or any PCH device.
  //

  GroupMin = GpioGetLowestGroup ();
  GroupMax = GpioGetHighestGroup ();

  for (Group = GroupMin; Group <= GroupMax; Group++) {
    for (PadNumber = 0; PadNumber < GpioGetPadPerGroup (Group); PadNumber++) {

      GpioPad = GpioGetGpioPadFromGroupAndPadNumber (Group, PadNumber);

      GpioGetPadOwnership (GpioPad, &PadOwnVal);
      if (PadOwnVal != GpioPadOwnHost) {
        continue;
      }

      GpioGetPadConfig (GpioPad, &GpioData);

      if ((GpioData.InterruptConfig & GpioIntApic) != GpioIntApic) {
        //
        // This pad is not routed to IOxAPIC, move to next one
        //
        continue;
      }

      GpioGetPadIoApicIrqNumber (GpioPad, &GpioIrqNumber);
      if (((IrqUsage[GpioIrqNumber >> 5] >> (GpioIrqNumber % 32)) & BIT0) == 0x0) {
        //
        // If IRQ is not yet used, update IrqUsage[] table
        //
        IrqUsage[GpioIrqNumber >> 5]|= 0x1 << (GpioIrqNumber  % 32);
      } else {
        //
        // If IRQ is reported to be used then assert, as those interrupts
        // cannot be shareable
        //
        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: For %a IRQ%d is already in use!\n",
                GpioName (GpioPad),
                GpioIrqNumber));
        return;
      }
    }
  }

  //
  // Dump IRQ usage
  //
  DEBUG ((DEBUG_INFO, "------------------ IRQ Usage ------------------\n"));
  DEBUG ((DEBUG_INFO, "  IRQxxx  USED\n"));
  for (Index = 0; Index < 127; Index++) {
    DEBUG ((DEBUG_INFO, "  IRQ%03d  %x\n",Index,((IrqUsage[Index >> 5] >> (Index % 32)) & BIT0)));
  }
  DEBUG_CODE_END ();
}
#endif // MDEPKG_NDEBUG

/**
  Configures interrupts polarity for PCI devices.

  @param[in] PchInterruptConfig    PCH interrupt Configuration
**/
STATIC
VOID
SetInterruptsPolarityForPchInternalDevices (
  IN PCH_INTERRUPT_CONFIG    *InterruptConfig
  )
{
  UINTN   DevIntConfigIndex;
  UINT32  IpcXReg[PCH_MAX_ITSS_IPC_REGS];
  UINTN   IpcXIndex;

  ZeroMem (IpcXReg, sizeof (IpcXReg));

  //
  // PIRQA-H (IRQ16-23)
  // All PCI interrupts polarity have to be set as active low.
  // PCI specification rev. 2.2 December 18,1998 - chapter 2.2.6
  //
  IpcXReg[0] = 0x00FF0000;

  //
  // GPI legacy interrupt polarity can be either ActiveLow or ActiveHigh
  // OS can be informed about polarity by ACPI Interrupt{..} descriptor
  // We set GPI interrupt polarity to ActiveLow to be coherent
  // with PCI devices for simplicity
  //
  ASSERT (InterruptConfig->GpioIrqRoute < PCH_MAX_ITSS_IRQ_NUM);
  IpcXIndex = InterruptConfig->GpioIrqRoute / 32;
  if (IpcXIndex < PCH_MAX_ITSS_IPC_REGS) {
    IpcXReg[IpcXIndex] |= 0x1 << (InterruptConfig->GpioIrqRoute % 32);
  }

  //
  // All PCH internal devices appear as PCI devices.
  // Due to the fact that not all PCH internal devices use IRQs from range IRQ[16-23]
  // Get all IRQ numbers used by these and switch their interrupt to ActiveLow.
  //
  for (DevIntConfigIndex = 0; DevIntConfigIndex < InterruptConfig->NumOfDevIntConfig; DevIntConfigIndex++) {
    IpcXReg[InterruptConfig->DevIntConfig[DevIntConfigIndex].Irq >> 5] |= 0x1 << (InterruptConfig->DevIntConfig[DevIntConfigIndex].Irq % 32);
  }

  //
  // Program ITSS.IPC0-3 registers.
  // Setting only requested IRQs to active low AND NOT altering
  // previous configuration.
  //
  for (IpcXIndex = 0; IpcXIndex < PCH_MAX_ITSS_IPC_REGS; IpcXIndex++) {
    PchPcrAndThenOr32 (PID_ITSS, R_ITSS_PCR_IPC0 + (UINT16) IpcXIndex * 4, ~0u, IpcXReg[IpcXIndex]);
  }
}

/**
  Retrieve interrupt configuration for a given PCH device (DxFy)

  @param[in]  SiPolicy  Policy
  @param[in]  Device    Device number
  @param[in]  Function  Function number
  @param[out] IntPin    Interrupt pin: INTA-INTD (see PCH_INT_PIN for reference)
  @param[out] ApicIrq   APIC IRQ number
**/
VOID
ItssGetDevIntConfig (
  IN  CONST SI_POLICY_PPI  *SiPolicy,
  IN  UINT8                Device,
  IN  UINT8                Function,
  OUT UINT8                *IntPin,
  OUT UINT8                *ApicIrq
  )
{
  PCH_INTERRUPT_CONFIG  *InterruptConfig;
  UINT8                 Index;

  InterruptConfig = ItssGetIntConfigPolicy (SiPolicy);

  //
  // Loop through whole interrupt table and find matching device
  //
  for (Index = 0; Index < InterruptConfig->NumOfDevIntConfig; Index++) {
    if ((InterruptConfig->DevIntConfig[Index].Device == Device) &&
        (InterruptConfig->DevIntConfig[Index].Function == Function)) {
      *IntPin = InterruptConfig->DevIntConfig[Index].IntX;
      *ApicIrq = InterruptConfig->DevIntConfig[Index].Irq;
      return;
    }
  }

  //
  // Interrupt policy doesn't have interrupt config entry
  // for a device that is being enabled on the platform
  //
  DEBUG ((DEBUG_ERROR, "D%d F%d does not have interrupt config entry\n", Device, Function));
  ASSERT (FALSE);
}

/**
  Retrieve interrupt pin for a given PCH device (DxFy)

  @param[in]  SiPolicy  Policy
  @param[in]  Device    Device number
  @param[in]  Function  Function number

  @retval Interrupt pin: INTA-INTD (see PCH_INT_PIN for reference)
**/
UINT8
ItssGetDevIntPin (
  IN  CONST SI_POLICY_PPI  *SiPolicy,
  IN  UINT8                Device,
  IN  UINT8                Function
  )
{
  UINT8  IntPin;
  UINT8  ApicIrq;

  ItssGetDevIntConfig (SiPolicy, Device, Function, &IntPin, &ApicIrq);

  return IntPin;
}

/**
  Retrieve IRQ for GPIO controller

  @param[in]  SiPolicy  Policy

  @retval GpioIrq
**/
UINT8
ItssGetGpioDevIntConfig (
  IN CONST SI_POLICY_PPI  *SiPolicy
  )
{
  return ItssGetIntConfigPolicy (SiPolicy)->GpioIrqRoute;
}

/**
  Retrieve IRQ for TCO

  @param[in]  SiPolicy  Policy

  @retval TcoIrq     TCO IRQ. If 0 TCO interrupt is not to be enabled
**/
UINT8
ItssGetTcoDevIntConfig (
  IN CONST SI_POLICY_PPI  *SiPolicy
  )
{
  PCH_INTERRUPT_CONFIG  *InterruptConfig;

  InterruptConfig = ItssGetIntConfigPolicy (SiPolicy);

  if (InterruptConfig->TcoIrqEnable) {
    return InterruptConfig->TcoIrqSelect;
  } else {
    return 0;
  }
}

/**
  Retrieve IRQ for PMC SCI

  @param[in]  SiPolicy  Policy

  @retval PmcSciIrq
**/
UINT8
ItssGetPmcSciDevIntConfig (
  IN CONST SI_POLICY_PPI  *SiPolicy
  )
{
  return ItssGetIntConfigPolicy (SiPolicy)->SciIrqSelect;
}

/**
  Configures PCH interrupts

  @param[in] SiPolicy    Policy
**/
VOID
ItssConfigureInterrupts (
  IN CONST SI_POLICY_PPI  *SiPolicy
  )
{
  PCH_INTERRUPT_CONFIG  *InterruptConfig;

  InterruptConfig = ItssGetIntConfigPolicy (SiPolicy);

  if (InterruptConfig->NumOfDevIntConfig >= PCH_MAX_DEVICE_INTERRUPT_CONFIG) {
    ASSERT (FALSE);
    return;
  }

#ifndef MDEPKG_NDEBUG
  //
  // Check interrupt settings
  //
  CheckInterruptSettings (
    InterruptConfig->DevIntConfig,
    InterruptConfig->NumOfDevIntConfig
    );
#endif //MDEPKG_NDEBUG


  //
  // Set Pirx Interrupt routing register
  //
  UpdatePirxRegs (
    InterruptConfig->DevIntConfig,
    InterruptConfig->NumOfDevIntConfig
    );

  SetInterruptsPolarityForPchInternalDevices (InterruptConfig);
}

/**
  Initialize IOAPIC according to IoApicConfig policy of the PCH
  Policy PPI

  @param[in] SiPolicyPpi          The SI Policy PPI instance

**/
VOID
ItssInitIoApic (
  IN CONST SI_POLICY_PPI  *SiPolicy
  )
{
  EFI_STATUS            Status;
  UINT64                P2sbBase;
  PCH_IOAPIC_CONFIG     *IoApicConfig;
  UINT32                IoApicAddress;
  UINT32                IoApicId;
  UINT32                Data32;
  UINT32                Data32And;
  UINT8                 IoApicSelect;
  EFI_BOOT_MODE         BootMode;
  PCH_GENERAL_CONFIG    *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gIoApicConfigGuid, (VOID *) &IoApicConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Set PSF Multicast EOI forwarding for ITSS (with IOAPIC controller)
  ///
  PsfConfigurEoiForItss ();

  //
  // Configure ITSS power management settings
  //
  if (PchGeneralConfig->PchMasterClockGating) {
    if (PchGeneralConfig->LegacyIoLowLatency) {
      ///
      /// Set PCR[ITSS] + 3300h[4:0] = 00000b
      ///
      Data32 = 0;
      Data32And = (UINT32) ~(B_ITSS_PCR_ITSSPRC_PGCBDCGE | B_ITSS_PCR_ITSSPRC_HPETDCGE | B_ITSS_PCR_ITSSPRC_8254CGE | B_ITSS_PCR_ITSSPRC_IOSFICGE | B_ITSS_PCR_ITSSPRC_ITSSCGE);
    } else {
      ///
      /// Set PCR[ITSS] + 3300h[4:0] = 11011b
      /// Set PCR[ITSS] + 3300h[2] = 1 in POST time only if 8254 timer is not used.
      ///
      Data32And = ~0u;
      Data32 = (B_ITSS_PCR_ITSSPRC_PGCBDCGE | B_ITSS_PCR_ITSSPRC_HPETDCGE | B_ITSS_PCR_ITSSPRC_IOSFICGE | B_ITSS_PCR_ITSSPRC_ITSSCGE);
      if (IoApicConfig->Enable8254ClockGating) {
        Data32 |= B_ITSS_PCR_ITSSPRC_8254CGE;
      } else {
        //
        // During S3 resume path, if Enable8254ClockGating is disabled and
        // Enable8254ClockGatingOnS3 is enabled, RC will set 8254CGE with BOOT_SAI
        // to avoid of SMI requirement of setting this.
        //
        Status = PeiServicesGetBootMode (&BootMode);
        ASSERT_EFI_ERROR (Status);
        if ((BootMode == BOOT_ON_S3_RESUME) &&
            IoApicConfig->Enable8254ClockGatingOnS3) {
          Data32 |= B_ITSS_PCR_ITSSPRC_8254CGE;
        }
      }
    }

    PchPcrAndThenOr32 (
      PID_ITSS, R_ITSS_PCR_ITSSPRC,
      Data32And,
      Data32
      );
  } else {
    PchPcrAndThenOr32 (
      PID_ITSS, R_ITSS_PCR_ITSSPRC,
      (UINT32)~(B_ITSS_PCR_ITSSPRC_PGCBDCGE | B_ITSS_PCR_ITSSPRC_HPETDCGE | B_ITSS_PCR_ITSSPRC_8254CGE | B_ITSS_PCR_ITSSPRC_IOSFICGE | B_ITSS_PCR_ITSSPRC_ITSSCGE),
      0
      );
  }

  P2sbBase = P2sbPciBase ();

  ///
  /// Program APIC Range Select bits that define address bits 19:12 for the IOxAPIC range.
  /// This value must not be changed unless the IOxAPIC Enable bit is cleared.
  ///
  IoApicAddress = PcdGet32 (PcdSiIoApicBaseAddress);
  ASSERT ((IoApicAddress & 0xFFF00FFF) == 0xFEC00000);
  IoApicSelect = (IoApicAddress >> N_IO_APIC_ASEL) & 0xFF;
  if (IoApicSelect != PciSegmentRead8 (P2sbBase + R_P2SB_CFG_IOAC)) {
    PciSegmentAnd16 (P2sbBase + R_P2SB_CFG_IOAC, (UINT16) ~(B_P2SB_CFG_IOAC_AE));
    PciSegmentAndThenOr16 (
      P2sbBase + R_P2SB_CFG_IOAC,
      (UINT16) ~(B_P2SB_CFG_IOAC_ASEL),
      (UINT16) IoApicSelect
      );
  }
  ///
  /// PCH BIOS Spec Section 6.6.2.1
  /// 1. Enable the IOAPIC by setting the APIC Enable bit, P2SB PCI offset 64h [8], if the
  ///    system needs to use the IOxAPIC. The APIC Enable bits needs read back after the bit is written.
  ///
  PciSegmentOr16 (P2sbBase + R_P2SB_CFG_IOAC, B_P2SB_CFG_IOAC_AE);
  ///
  /// Reads back for posted write to take effect
  ///
  PciSegmentRead16 (P2sbBase + R_P2SB_CFG_IOAC);

  ///
  /// Get current IO APIC ID
  ///
  MmioWrite8 ((UINTN) (IoApicAddress + R_IO_APIC_MEM_INDEX_OFFSET), 0);
  IoApicId = MmioRead32 ((UINTN) (IoApicAddress + R_IO_APIC_MEM_DATA_OFFSET)) >> 24;
  ///
  /// IO APIC ID is at APIC Identification Register [27:24]
  ///
  if ((IoApicConfig->IoApicId != IoApicId) && (IoApicConfig->IoApicId < 0x10)) {
    ///
    /// Program APIC ID
    ///
    MmioWrite8 ((UINTN) (IoApicAddress + R_IO_APIC_MEM_INDEX_OFFSET), 0);
    MmioWrite32 ((UINTN) (IoApicAddress + R_IO_APIC_MEM_DATA_OFFSET), (UINT32) (IoApicConfig->IoApicId << 24));
  }

  if (IoApicConfig->IoApicEntry24_119 == FALSE) {
    ///
    /// Program IOAPIC maximal entry to 24 in PCR[ITSS] + 31FCh[9]
    /// and in IOAPIC Version Register
    PchPcrAndThenOr16 (PID_ITSS, R_ITSS_PCR_GIC, 0xFFFF, (UINT16) B_ITSS_PCR_GIC_MAX_IRQ_24);
    MmioWrite8 ((UINTN) (IoApicAddress + R_IO_APIC_MEM_INDEX_OFFSET), 1);
    MmioWrite32 ((IoApicAddress + R_IO_APIC_MEM_DATA_OFFSET), 0x170020);
  } else {
    ///
    /// Program IOAPIC maximal entry to 119 in PCR[ITSS] + 31FCh[9]
    /// and in IOAPIC Version Register
    PchPcrAndThenOr16 (PID_ITSS, R_ITSS_PCR_GIC, (UINT16) (~B_ITSS_PCR_GIC_MAX_IRQ_24), 0x0);
    MmioWrite8 ((UINTN) (IoApicAddress + R_IO_APIC_MEM_INDEX_OFFSET), 1);
    MmioWrite32 ((IoApicAddress + R_IO_APIC_MEM_DATA_OFFSET), 0x770020);
  }

  //
  // Build the resource descriptor hob for IOAPIC address resource.
  //
  BuildResourceDescriptorHob (
    EFI_RESOURCE_MEMORY_MAPPED_IO,
    (EFI_RESOURCE_ATTRIBUTE_PRESENT    |
     EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE),
    IoApicAddress,
    0x1000
    );
  BuildMemoryAllocationHob (
    IoApicAddress,
    0x1000,
    EfiMemoryMappedIO
    );
}
