/**@file
  PEI DTBT Init library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <Private/Library/PeiDTbtInitLib.h>
#include <Ppi/PeiDTbtPolicy.h>

#include <SaRegs.h>

#define LTSSM_FSM_RESTORE 0xC74

/**
  The Task Table for DTBT
**/
GLOBAL_REMOVE_IF_UNREFERENCED TBT_CALL_TABLE_ENTRY  DTbtCallTable[] = {
  ///
  /// The functions are executed in the following order, as the policy flag dictates.
  /// TbtTask, TbtBootModeFlag, debug_string
  ///
  { DTbtSetTPch25Timing,          TBT_ALL,               "DTbtSetTPch25Timing"},
  { DTbtForcePower,               TBT_ALL,                    "DTbtForcePower"},
  { DTbtClearVgaRegisters,        TBT_ALL,             "DTbtClearVgaRegisters"},
  { DTbtBootOn,                TBT_NORMAL,              "Send_Boot_On_Mailbox"},
  { DTbtUsbOn,      (TBT_S4 | TBT_NORMAL),               "Send_USB_On_Mailbox"},
  { DTbtSxExitFlow,     (TBT_S3 | TBT_S4),              "Send_Sx_Exit_Mailbox"},
  { PassDTbtPolicyToHob, (TBT_S4 | TBT_NORMAL),      "Pass_DTbt_Policy_To_Hob"},
  { NULL ,                       TBT_NULL,                       "END_OF_TASK"}
};

/**
  set tPCH25 Timing to 10 ms for DTBT.

  @param[in]  VOID             PeiTbtConfig

  @retval     EFI_SUCCESS      The function completes successfully
  @retval     EFI_UNSUPPORTED  dTBT is not supported.
**/
EFI_STATUS
EFIAPI
DTbtSetTPch25Timing (
  IN  VOID  *PeiTbtConfig
)
{
  DEBUG ((DEBUG_INFO, "DTbtSetTPch25Timing call Inside\n"));

  //
  //During boot, reboot and wake  tPCH25 Timing should be set to 10 ms
  //
  PmcSetTPch25Timing(PmcTPch25_10ms);

  DEBUG((DEBUG_INFO, "DTbtSetTPch25Timing call Return\n"));
  return EFI_SUCCESS;
}

/**
  Do ForcePower for DTBT Controller

  @param[in]  VOID             PeiTbtConfig

  @retval     EFI_SUCCESS      The function completes successfully
  @retval     EFI_UNSUPPORTED  dTBT is not supported.
**/
EFI_STATUS
EFIAPI
DTbtForcePower (
  IN  VOID  *PeiTbtConfig
)
{
  UINT8    Index;
  PEI_DTBT_POLICY *PeiDTbtConfig;

  PeiDTbtConfig = PeiTbtConfig;

  DEBUG ((DEBUG_INFO, "DTbtForcePower call Inside\n"));

  for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
    if (PeiDTbtConfig->DTbtControllerConfig[Index].DTbtControllerEn == 1) {
      if (PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwr) {
        DEBUG((DEBUG_INFO, "ForcePwrGpio.GpioPad = %x \n", PeiDTbtConfig->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad));
        ForceDtbtPower(PeiDTbtConfig->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad, PeiDTbtConfig->DTbtControllerConfig[Index].ForcePwrGpio.GpioLevel);
        DEBUG((DEBUG_INFO, "ForceDtbtPower asserted \n"));
        MicroSecondDelay(PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwrDly * 1000);
        DEBUG((DEBUG_INFO, "Delay after ForceDtbtPower = 0x%x ms \n", PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwrDly));
      }
    }
  }

  DEBUG ((DEBUG_INFO, "DTbtForcePower call Return\n"));
  return EFI_SUCCESS;
}

/**
  Clear VGA Registers for DTBT.

  @param[in]  VOID             PeiTbtConfig

  @retval     EFI_SUCCESS      The function completes successfully
  @retval     EFI_UNSUPPORTED  dTBT is not supported.
**/
EFI_STATUS
EFIAPI
DTbtClearVgaRegisters (
  IN  VOID  *PeiTbtConfig
)
{
  UINTN           RpDev;
  UINTN           RpFunc;
  EFI_STATUS      Status;
  UINT8           Index;
  PEI_DTBT_POLICY *PeiDTbtConfig;

  DEBUG ((DEBUG_INFO, "DTbtClearVgaRegisters call Inside\n"));

  Status = EFI_SUCCESS;
  PeiDTbtConfig = PeiTbtConfig;

  for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
    if (PeiDTbtConfig->DTbtControllerConfig[Index].DTbtControllerEn == 1) {
      Status = GetDTbtRpDevFun(PeiDTbtConfig->DTbtControllerConfig[Index].Type, PeiDTbtConfig->DTbtControllerConfig[Index].PcieRpNumber - 1, &RpDev, &RpFunc);
      ASSERT_EFI_ERROR(Status);
      //
      // VGA Enable and VGA 16-bit decode registers of Bridge control register of Root port where
      // Host router resides should be cleaned
      //
      TbtClearVgaRegisters(0x00, 0x00, RpDev, RpFunc);
    }
  }

  DEBUG ((DEBUG_INFO, "DTbtClearVgaRegisters call Return\n"));
  return Status;
}

/**
  Exectue Mail box command "Boot On".

  @param[in]  VOID             PeiTbtConfig

  @retval     EFI_SUCCESS      The function completes successfully
  @retval     EFI_UNSUPPORTED  dTBT is not supported.
**/
EFI_STATUS
EFIAPI
DTbtBootOn(
  IN  VOID  *PeiTbtConfig
)
{
  EFI_STATUS      Status;
  UINT32          OrgBusNumberConfiguration;
  UINTN           RpDev;
  UINTN           RpFunc;
  UINT8           Index;
  PEI_DTBT_POLICY *PeiDTbtConfig;

  DEBUG((DEBUG_INFO, "DTbtBootOn call Inside\n"));

  Status = EFI_SUCCESS;
  PeiDTbtConfig = PeiTbtConfig;

  for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++)
  {
    if (PeiDTbtConfig->DTbtControllerConfig[Index].DTbtControllerEn == 1) {
      Status = GetDTbtRpDevFun(PeiDTbtConfig->DTbtControllerConfig[Index].Type, PeiDTbtConfig->DTbtControllerConfig[Index].PcieRpNumber - 1, &RpDev, &RpFunc);
      ASSERT_EFI_ERROR(Status);
      OrgBusNumberConfiguration = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, 0, RpDev, RpFunc, PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET));
      //
      // Set Sec/Sub buses to 0xF0
      //
      PciSegmentWrite32(PCI_SEGMENT_LIB_ADDRESS (0, 0, RpDev, RpFunc, PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET), (UINT32)((FixedPcdGet8 (PcdTbtTempBusNumber) << 16) | (FixedPcdGet8 (PcdTbtTempBusNumber) << 8)));
      //
      //When Thunderbolt(TM) boot [TbtBootOn] is enabled in bios setup we need to do the below:
      //Bios should send "Boot On" message through PCIE2TBT register
      //The Boot On command as described above would include the command and acknowledge from FW (with the default timeout in BIOS),
      //once the Boot On command is completed it is guaranteed that the AlpineRidge(AR) device is there and the PCI tunneling was done by FW,
      //next step from BIOS is enumeration using SMI
      //

      if (PeiDTbtConfig->DTbtGenericConfig.TbtBootOn) {
        //
        // Exectue Mail box command "Boot On"
        //
        //Command may be executed only during boot/reboot and not during Sx exit flow
        if (!TbtSetPcie2TbtCommand(PCIE2TBT_BOOT_ON, FixedPcdGet8 (PcdDTbtToPcieRegister), FixedPcdGet8 (PcdPcieToDTbtRegister), FixedPcdGet8 (PcdTbtTempBusNumber), 0, 0, TBT_5S_TIMEOUT)) {
          //
          // Nothing to wait, HR is not responsive
          //
          DEBUG((DEBUG_INFO, "<TbtPei> DTbtBootOn - Boot On message sent failed \n"));
        }
      }
      //
      // Reset Sec/Sub buses to original value
      //
      PciSegmentWrite32(PCI_SEGMENT_LIB_ADDRESS (0, 0, RpDev, RpFunc, PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET), OrgBusNumberConfiguration);
    }
  }

  DEBUG((DEBUG_INFO, "DTbtBootOn call Return\n"));
  return Status;
}

/**
  Exectue Mail box command "USB On".

  @param[in]  VOID             PeiTbtConfig

  @retval     EFI_SUCCESS      The function completes successfully
  @retval     EFI_UNSUPPORTED  dTBT is not supported.
**/
EFI_STATUS
EFIAPI
DTbtUsbOn(
  IN  VOID  *PeiTbtConfig
)
{
  EFI_STATUS                      Status;
  UINTN                           RpDev;
  UINTN                           RpFunc;
  UINT32                          OrgBusNumberConfiguration;
  UINT8                           Index;
  UINT64                          TbtBaseAddress;
  UINT32                          MaxWaitIter;
  UINT32                          RegVal;
  PEI_DTBT_POLICY                 *PeiDTbtConfig;

  DEBUG((DEBUG_INFO, "DTbtUsbOn call Inside\n"));

  Status = EFI_SUCCESS;
  PeiDTbtConfig = PeiTbtConfig;

  for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++)
  {
    if (PeiDTbtConfig->DTbtControllerConfig[Index].DTbtControllerEn == 1) {
      Status = GetDTbtRpDevFun(PeiDTbtConfig->DTbtControllerConfig[Index].Type, PeiDTbtConfig->DTbtControllerConfig[Index].PcieRpNumber - 1, &RpDev, &RpFunc);
      ASSERT_EFI_ERROR(Status);
      OrgBusNumberConfiguration = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS (0, 0, RpDev, RpFunc, PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET));
      //
      // Set Sec/Sub buses to 0xF0
      //
      PciSegmentWrite32(PCI_SEGMENT_LIB_ADDRESS (0, 0, RpDev, RpFunc, PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET), (UINT32)((FixedPcdGet8 (PcdTbtTempBusNumber) << 16) | (FixedPcdGet8 (PcdTbtTempBusNumber) << 8)));

      //
      //When Thunderbolt(TM) Usb boot [TbtUsbOn] is enabled in bios setup we need to do the below:
      //Bios should send "Usb On" message through PCIE2TBT register
      //The Usb On command as described above would include the command and acknowledge from FW (with the default timeout in BIOS),
      //once the Usb On command is completed it is guaranteed that the AlpineRidge(AR) device is there and the PCI tunneling was done by FW,
      //next step from BIOS is enumeration using SMI
      //
      if (PeiDTbtConfig->DTbtGenericConfig.TbtUsbOn) {
        if (PeiDTbtConfig->DTbtGenericConfig.TbtBootOn) {
          MaxWaitIter = 50;   // Wait 5 sec
          TbtBaseAddress = PCI_SEGMENT_LIB_ADDRESS(0, FixedPcdGet8 (PcdTbtTempBusNumber), 0, 0, 0);
          //
          // Driver clears the PCIe2TBT Valid bit to support two consicutive mailbox commands
          //
          PciSegmentWrite32(TbtBaseAddress + FixedPcdGet8 (PcdPcieToDTbtRegister), 0);
          DEBUG((DEBUG_INFO, "TbtBaseAddress + DTBT_PCIE2TBT_R = 0x%lx \n", TbtBaseAddress + FixedPcdGet8 (PcdPcieToDTbtRegister)));
          while (MaxWaitIter-- > 0) {
            RegVal = PciSegmentRead32(TbtBaseAddress + FixedPcdGet8 (PcdDTbtToPcieRegister));
            if (0xFFFFFFFF == RegVal) {
              //
              // Device is not here return now
              //
              DEBUG((DEBUG_INFO, "TBT device is not present \n"));
              break;
            }

            if (!(RegVal & TBT2PCIE_DON_R)) {
              break;
            }
            MicroSecondDelay(100 * 1000);
          }
        }

        //
        // Exectue Mail box command "Usb On"
        //
        //Command may be executed only during boot/reboot and not during S3 exit flow
        if (!TbtSetPcie2TbtCommand(PCIE2TBT_USB_ON, FixedPcdGet8 (PcdDTbtToPcieRegister), FixedPcdGet8 (PcdPcieToDTbtRegister), FixedPcdGet8 (PcdTbtTempBusNumber), 0, 0, TBT_5S_TIMEOUT)) {
          //
          // Nothing to wait, HR is not responsive
          //
          DEBUG((DEBUG_INFO, "<TbtPei> TbtBootSupport - Usb On message sent failed \n"));
        }
      }
      //
      // Reset Sec/Sub buses to original value
      //
      PciSegmentWrite32(PCI_SEGMENT_LIB_ADDRESS (0, 0, RpDev, RpFunc, PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET), OrgBusNumberConfiguration);
    }
  }

  DEBUG((DEBUG_INFO, "DTbtUsbOn call return\n"));
  return Status;
}

/**
  Exectue Mail box command "Sx Exit".

  @param[in]  VOID             PeiTbtConfig

  @retval     EFI_SUCCESS      The function completes successfully
  @retval     EFI_UNSUPPORTED  dTBT is not supported.
**/
EFI_STATUS
EFIAPI
DTbtSxExitFlow(
  IN  VOID  *PeiTbtConfig
)
{
  EFI_STATUS                      Status;
  UINT32                          OrgBusNumberConfiguration;
  UINTN                           RpDev;
  UINTN                           RpFunc;
  UINT8                           Index;
  PEI_DTBT_POLICY                 *PeiDTbtConfig;

  DEBUG((DEBUG_INFO, "DTbtSxExitFlow call Inside\n"));

  Status = EFI_SUCCESS;
  PeiDTbtConfig = PeiTbtConfig;

  for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++)
  {
    if (PeiDTbtConfig->DTbtControllerConfig[Index].DTbtControllerEn != 0) {
      Status = GetDTbtRpDevFun(PeiDTbtConfig->DTbtControllerConfig[Index].Type, PeiDTbtConfig->DTbtControllerConfig[Index].PcieRpNumber - 1, &RpDev, &RpFunc);
      ASSERT_EFI_ERROR(Status);
      OrgBusNumberConfiguration = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS (0, 0, RpDev, RpFunc, PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET));
      //
      // Set Sec/Sub buses to 0xF0
      //
      PciSegmentWrite32(PCI_SEGMENT_LIB_ADDRESS (0, 0, RpDev, RpFunc, PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET), (UINT32)((FixedPcdGet8 (PcdTbtTempBusNumber) << 16) | (FixedPcdGet8 (PcdTbtTempBusNumber) << 8)));

      //
      // 1. Execute "Sx_Exit_TBT_Connected" mailbox command.
      // 2. If procedure above returns true, BIOS should perform "wait for fast link bring-up" loop
      // 3. Continue regular wake flow.
      //
      //
      // Exectue Mail box command and perform "wait for fast link bring-up" loop
      //
      TbtSetSxMode(FixedPcdGet8 (PcdDTbtToPcieRegister), FixedPcdGet8 (PcdPcieToDTbtRegister), FixedPcdGet8 (PcdTbtTempBusNumber), 0, 0);
      //
      // Reset Sec/Sub buses to original value
      //
      PciSegmentWrite32(PCI_SEGMENT_LIB_ADDRESS (0, 0, RpDev, RpFunc, PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET), OrgBusNumberConfiguration);
    }
  }

  DEBUG((DEBUG_INFO, "DTbtSxExitFlow call Return\n"));
  return Status;
}

/**
  This function pass PEI DTbt Policy to Hob.

  @param[in]  VOID             PeiTbtConfig

  @retval     EFI_SUCCESS      The function completes successfully
  @retval     EFI_UNSUPPORTED  dTBT is not supported.
**/
EFI_STATUS
EFIAPI
PassDTbtPolicyToHob(
  IN  VOID  *PeiTbtConfig
)
{
  EFI_STATUS            Status;
  UINT8                 Index;
  DTBT_INFO_HOB         *DTbtInfoHob;
  PEI_DTBT_POLICY       *PeiDTbtConfig;

  DEBUG((DEBUG_INFO, "PassDTbtPolicyToHob - Start\n"));

  PeiDTbtConfig = PeiTbtConfig;
  DTbtInfoHob = GetFirstGuidHob (&gDTbtInfoHobGuid);
  if (DTbtInfoHob == NULL) {
    //
    // Create HOB for DTBT Data
    //
    Status = PeiServicesCreateHob (
               EFI_HOB_TYPE_GUID_EXTENSION,
               sizeof (DTBT_INFO_HOB),
               (VOID **) &DTbtInfoHob
               );
    DEBUG ((DEBUG_INFO, "DTbtInfoHob Created \n"));
    ASSERT_EFI_ERROR (Status);
  }

  if (DTbtInfoHob != NULL) {
    //
    // Initialize the DTBT INFO HOB data.
    //
    DTbtInfoHob->EfiHobGuidType.Name = gDTbtInfoHobGuid;

    //
    // Update DTBT Policy to Hob
    //
    for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
      DTbtInfoHob->DTbtControllerConfig[Index].DTbtControllerEn = PeiDTbtConfig->DTbtControllerConfig[Index].DTbtControllerEn;
      DTbtInfoHob->DTbtControllerConfig[Index].Type = PeiDTbtConfig->DTbtControllerConfig[Index].Type;
      DTbtInfoHob->DTbtControllerConfig[Index].PcieRpNumber = PeiDTbtConfig->DTbtControllerConfig[Index].PcieRpNumber;
      DTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad = PeiDTbtConfig->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad;
      DTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioLevel = PeiDTbtConfig->DTbtControllerConfig[Index].ForcePwrGpio.GpioLevel;
      DTbtInfoHob->DTbtControllerConfig[Index].CioPlugEventGpio.GpioPad = PeiDTbtConfig->DTbtControllerConfig[Index].CioPlugEventGpio.GpioPad;
      DTbtInfoHob->DTbtControllerConfig[Index].CioPlugEventGpio.AcpiGpeSignature = PeiDTbtConfig->DTbtControllerConfig[Index].CioPlugEventGpio.AcpiGpeSignature;
      DTbtInfoHob->DTbtControllerConfig[Index].CioPlugEventGpio.AcpiGpeSignaturePorting = PeiDTbtConfig->DTbtControllerConfig[Index].CioPlugEventGpio.AcpiGpeSignaturePorting;
      DTbtInfoHob->DTbtControllerConfig[Index].PcieRstGpio.GpioPad = PeiDTbtConfig->DTbtControllerConfig[Index].PcieRstGpio.GpioPad;
      DTbtInfoHob->DTbtControllerConfig[Index].PcieRstGpio.GpioLevel = PeiDTbtConfig->DTbtControllerConfig[Index].PcieRstGpio.GpioLevel;
    }
    DTbtInfoHob->DTbtGenericConfig.TbtBootOn = PeiDTbtConfig->DTbtGenericConfig.TbtBootOn;
    DTbtInfoHob->DTbtGenericConfig.TbtUsbOn = PeiDTbtConfig->DTbtGenericConfig.TbtUsbOn;
    DTbtInfoHob->DTbtGenericConfig.Gpio3ForcePwr = PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwr;
    DTbtInfoHob->DTbtGenericConfig.Gpio3ForcePwrDly = PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwrDly;
    DTbtInfoHob->DTbtGenericConfig.DTbtSharedGpioConfiguration = PeiDTbtConfig->DTbtGenericConfig.DTbtSharedGpioConfiguration;
    DTbtInfoHob->DTbtGenericConfig.PcieRstSupport = PeiDTbtConfig->DTbtGenericConfig.PcieRstSupport;
  } else {
    return EFI_NOT_FOUND;
  }

  DEBUG((DEBUG_INFO, "PassDTbtPolicyToHob - End\n"));

  return EFI_SUCCESS;
}

