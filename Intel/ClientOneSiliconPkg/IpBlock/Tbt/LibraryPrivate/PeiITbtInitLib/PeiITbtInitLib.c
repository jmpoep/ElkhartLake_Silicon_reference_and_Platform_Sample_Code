/**@file
  PEI ITBT Init library.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/PeiITbtInitLib.h>
#include <PeiITbtConfig.h>
#include <Library/CpuRegbarAccessLib.h>
#include <Library/PcdLib.h>
#include <Library/RngLib.h>
#include <Library/PreSiliconEnvDetectLib.h>

/**
  The Task Table for ITBT
**/
GLOBAL_REMOVE_IF_UNREFERENCED TBT_CALL_TABLE_ENTRY  ITbtCallTable[] = {
  ///
  /// The functions are executed in the following order, as the policy flag dictates.
  /// TbtTask, TbtBootModeFlag, debug_string
  ///
  ///
  /// TO DO: Temporarily blocking the calls to ITbtSetForcePower and ITbtSendCnctTpolgyCmd until simics env is fixed
  ///
  {ITbtSetForcePower,         TBT_ALL,              "ITbtSetForcePower"},
  {ITbtSetDmaUuid,            TBT_ALL,              "ITbtDmaUuidUpdate"},
  {ITbtClearVgaRegisters,     TBT_ALL,              "ITbtClearVgaRegisters"},
  {ITbtSetDmaLtr,             TBT_ALL,              "ITbtSetDmaLtr"},
  {ITbtSendCnctTpolgyCmd,     TBT_ALL,              "ITbtSendConnectTopologyCommand"},
  {PassITbtPolicyToHob,      (TBT_S4 | TBT_NORMAL), "Pass_ITbt_Policy_To_Hob"},
  {NULL ,                     TBT_NULL,             "END_OF_TASK"}
};

/**
  Return the specific ITBT controller is enabled or not

  @param[in]  PEI_ITBT_CONFIG  PeiITbtConfig
  @param[in]  ControllerIndex  The index of the controller

  @retval  TRUE            The specific ITBT controller is enabled
  @retval  FALSE           The specific ITBT controller is disabled
**/
BOOLEAN
IsITbtControllerEnable (
  IN  PEI_ITBT_CONFIG  *PeiITbtConfig,
  IN  UINT32           ControllerIndex
  )
{
  if ((PeiITbtConfig->ITbtRootPortConfig[2 * ControllerIndex].ITbtPcieRootPortEn == 1)
     || (PeiITbtConfig->ITbtRootPortConfig[(2 * ControllerIndex) + 1].ITbtPcieRootPortEn == 1)
     )
  {
    return TRUE;
  }

  return FALSE;
}
/**
  Program iTBT FP Register in order to bring iTBT micro controller up by applying Force Power.

  @param[in]  VOID                PeiTbtConfig

  @retval  EFI_SUCCESS            The function completes successfully
  @retval  EFI_UNSUPPORTED        ITBT is not supported.
**/
EFI_STATUS
EFIAPI
ITbtSetForcePower (
  IN  VOID  *PeiTbtConfig
  )
{
  EFI_STATUS                      Status;
  UINT8                           Index;
  UINTN                           ITbtDmaSegment;
  UINTN                           ITbtDmaBus;
  UINTN                           ITbtDmaDev;
  UINTN                           ITbtDmaFunc;
  UINT64                          BaseAddress;
  UINTN                           ForcePowerOnTimeoutInMs;
  UINT32                          RegVal;
  TCSS_DATA_HOB                   *TcssHob;
  PEI_ITBT_CONFIG                 *PeiITbtConfig;

  PeiITbtConfig = PeiTbtConfig;
  ForcePowerOnTimeoutInMs = (UINTN)PeiITbtConfig->ITbtGenericConfig.ITbtForcePowerOnTimeoutInMs;
  RegVal = 0;
  TcssHob = NULL;

  Status = EFI_UNSUPPORTED;

  DEBUG ((DEBUG_INFO, "[TBT] SetITbtForcePowerEnable call Inside\n"));

  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob != NULL) {
    if (!(TcssHob->TcssData.TbtImrStatus.Bits.Done && TcssHob->TcssData.TbtImrStatus.Bits.Valid)) {
      DEBUG ((DEBUG_ERROR, "TBT IMR is corrupt, skip the ForcePower task.\n"));
      return Status;
    }
  } else {
    DEBUG ((DEBUG_ERROR, "TcssHob is NULL\n"));
    if (!IsSimicsEnvironment ()) {
      ASSERT_EFI_ERROR (Status);
    }
    return Status;
  }


  for (Index = 0; Index < (MAX_ITBT_PCIE_PORT / 2); Index++) {
    if (IsITbtControllerEnable (PeiITbtConfig, Index) == TRUE) {
      ForcePowerOnTimeoutInMs = (UINTN)PeiITbtConfig->ITbtGenericConfig.ITbtForcePowerOnTimeoutInMs;
      Status = GetITbtDmaDevFun (Index, &ITbtDmaSegment, &ITbtDmaBus, &ITbtDmaDev, &ITbtDmaFunc);
      ASSERT_EFI_ERROR (Status);
      if (Status == EFI_SUCCESS) {
        BaseAddress = PCI_SEGMENT_LIB_ADDRESS ((UINT32)ITbtDmaSegment, (UINT32)ITbtDmaBus, (UINT32)ITbtDmaDev, (UINT32)ITbtDmaFunc, 0);
        PciSegmentAndThenOr32 (
          BaseAddress + R_SA_HOST_DMA_RTD3_FORCEPOWER,
          (UINT32) ~(B_SA_HOST_DMA_DMA_ACTIVE_DELAY_MASK),
          B_SA_HOST_DMA_FORCEPOWER_EN | (V_SA_HOST_DMA_DMA_ACTIVE_DELAY_VALUE << N_SA_HOST_DMA_DMA_ACTIVE_DELAY_OFFSET)
        );

        //
        //  Polling NVM FW version
        //
        Status = EFI_TIMEOUT;
        while (ForcePowerOnTimeoutInMs-- > 0) {
          RegVal = PciSegmentRead32 (BaseAddress + R_SA_HOST_DMA_ITBT_NVM_FW_REVISION);
            if ((RegVal & BIT31) == BIT31) {
              Status = EFI_SUCCESS;
              DEBUG ((DEBUG_INFO, "Controller %d (%d:%d:%d:%d) is ready\n", Index, ITbtDmaSegment, ITbtDmaBus, ITbtDmaDev, ITbtDmaFunc));
              break;
            }
          MicroSecondDelay (1000);
        }
        if (Status == EFI_TIMEOUT) {
          DEBUG ((DEBUG_ERROR, "Controller %d (%d:%d:%d:%d) is not ready\n", Index, ITbtDmaSegment, ITbtDmaBus, ITbtDmaDev, ITbtDmaFunc));
          if (!IsSimicsEnvironment ()) {
            ASSERT_EFI_ERROR (Status);
          }
        }
      } else {
        Status = EFI_NOT_FOUND;
        DEBUG ((DEBUG_ERROR, "No TBT DMA controller is enabled\n"));
        ASSERT_EFI_ERROR (Status);
      }
    }
  }

  DEBUG((DEBUG_INFO, "[TBT] SetITbtForcePowerEnable call Return\n"));
  return Status;
}

/**
  Send iTBT Connect Topology Command for Integrated Thunderbolt.

  @param[in]  VOID                PeiTbtConfig

  @retval  EFI_SUCCESS            The function completes successfully
  @retval  EFI_DEVICE_ERROR       Connect Topology Command is not executed successfully.
**/
EFI_STATUS
EFIAPI
ITbtSendCnctTpolgyCmd (
  IN  VOID  *PeiTbtConfig
  )
{
  EFI_STATUS                      Status;
  UINT8                           Index;
  UINTN                           ITbtDmaSegment;
  UINTN                           ITbtDmaBus;
  UINTN                           ITbtDmaDev;
  UINTN                           ITbtDmaFunc;
  UINT64                          BaseAddress;
  UINTN                           ConnectTopologyTimeoutInMs;
  BOOLEAN                         ReturnFlag;
  PEI_ITBT_CONFIG                 *PeiITbtConfig;

  PeiITbtConfig = PeiTbtConfig;
  ConnectTopologyTimeoutInMs = (UINTN)PeiITbtConfig->ITbtGenericConfig.ITbtConnectTopologyTimeoutInMs;
  Status = EFI_SUCCESS;

  DEBUG ((DEBUG_INFO, "[TBT] SendITbtCnctTpolgyCmd call Inside\n"));

  //
  // Each Controller will have 2 Root Ports + HIA
  // Based on the root ports enabled, execute Mail Box Communications on corresponding HIA
  //
  for (Index = 0; Index < (MAX_ITBT_PCIE_PORT / 2); Index++) {
    if(IsITbtControllerEnable (PeiITbtConfig, Index) == TRUE) {
      Status = GetITbtDmaDevFun (Index, &ITbtDmaSegment, &ITbtDmaBus, &ITbtDmaDev, &ITbtDmaFunc);
      ASSERT_EFI_ERROR (Status);
      if (Status == EFI_SUCCESS) {
        //
        // 1. BIOS send "CONNECT_TOPOLOGY" command to CM with 5 second timeout in Post Mem. CONNECT_TOPOLOGY command is targeted to 0x1F.
        // 2. BIOS dessert iTBT FP bit (0xFC) on each enabled iTBT instance (controller)
        //
        ReturnFlag = TbtSetPcie2TbtCommand (PCIE2TBT_CONNECT_TOPOLOGY_COMMAND, FixedPcdGet8 (PcdITbtToPcieRegister), FixedPcdGet8 (PcdPcieToITbtRegister), 0, (UINT8)ITbtDmaDev, (UINT8)ITbtDmaFunc, ConnectTopologyTimeoutInMs);
        if (ReturnFlag != TRUE) {
          DEBUG((DEBUG_ERROR, "SendITbtCnctTpolgyCmd call Return with Error Status= EFI_DEVICE_ERROR. DMA Index = %d\n", Index));
          return EFI_DEVICE_ERROR;
        }
        BaseAddress = PCI_SEGMENT_LIB_ADDRESS((UINT32)ITbtDmaSegment, (UINT32)ITbtDmaBus, (UINT32)ITbtDmaDev, (UINT32)ITbtDmaFunc, 0);
        PciSegmentAnd8 (BaseAddress + R_SA_HOST_DMA_RTD3_FORCEPOWER, (UINT8) (~B_SA_HOST_DMA_FORCEPOWER_EN));
      }
    }
  }

  DEBUG((DEBUG_INFO, "[TBT] SendITbtCnctTpolgyCmd call Return\n"));
  return Status;
}

/**
  Clear VGA Registers for Integrated Thunderbolt.

  @param[in]  VOID                PeiTbtConfig

  @retval  EFI_SUCCESS            The function completes successfully
  @retval  EFI_UNSUPPORTED        ITBT is not supported.
**/
EFI_STATUS
EFIAPI
ITbtClearVgaRegisters (
  IN  VOID  *PeiTbtConfig
  )
{
  EFI_STATUS                      Status;
  UINT8                           Index;
  UINTN                           RpSegment;
  UINTN                           RpBus;
  UINTN                           RpDev;
  UINTN                           RpFunc;
  PEI_ITBT_CONFIG                 *PeiITbtConfig;

  Status = EFI_SUCCESS;
  PeiITbtConfig = PeiTbtConfig;

  DEBUG ((DEBUG_INFO, "[TBT] ITbtClearVgaRegisters call Inside\n"));

    for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
      if (PeiITbtConfig->ITbtRootPortConfig[Index].ITbtPcieRootPortEn == 1) {
        Status = GetItbtPcieRpInfo ((UINTN)Index, &RpSegment, &RpBus, &RpDev, &RpFunc);
        ASSERT_EFI_ERROR (Status);

        //
        // VGA Enable and VGA 16-bit decode registers of Bridge control register of Root port where
        // Host router resides should be cleaned
        //
        TbtClearVgaRegisters (RpSegment, RpBus, RpDev, RpFunc);
      }
    }

  DEBUG((DEBUG_INFO, "[TBT] ITbtClearVgaRegisters call Return\n"));
  return Status;
}

/**
  Program LTR Registers for Integrated Thunderbolt.

  @param[in]  VOID                PeiTbtConfig

  @retval  EFI_SUCCESS            The function completes successfully
  @retval  EFI_UNSUPPORTED        ITBT is not supported.
**/
EFI_STATUS
EFIAPI
ITbtSetDmaLtr (
  IN  VOID  *PeiTbtConfig
  )
{
  UINT32                          Index;
  PEI_ITBT_CONFIG                 *PeiITbtConfig;

  DEBUG ((DEBUG_INFO, "[TBT] ITbtSetDmaLtr call Inside\n"));
  PeiITbtConfig = PeiTbtConfig;

  if (PeiITbtConfig == NULL) {
    DEBUG ((DEBUG_INFO, "PeiITbtConfig == NULL\n"));
    return EFI_INVALID_PARAMETER;
  }

  //
  // Program ITBT LTR to maximum snoop/non-snoop latency values
  //
  for (Index = 0; Index < SA_MAX_HOST_ITBT_DMA_NUMBER; Index++) {
    if (IsITbtControllerEnable (PeiITbtConfig, Index) == FALSE) {
      continue;
    }
    PciSegmentWrite16 (
      PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_HOST_DMA_BUS_NUM, SA_HOST_DMA_DEV_NUM, SA_HOST_DMA0_FUN_NUM + Index, R_SA_HOST_DMA_CFG_LTR_CAP),
      (UINT16) PeiITbtConfig->ITbtDmaLtr[Index]
    );
  }

  DEBUG ((DEBUG_INFO, "[TBT] ITbtSetDmaLtr call Return\n"));
  return EFI_SUCCESS;
}

/**
  This function Update UUID number to ITBT DMA Host controller.

  @param[in]  VOID                PeiTbtConfig

  @retval  EFI_SUCCESS            The function completes successfully
  @retval  EFI_INVALID_PARAMETER  PeiITbtConfig is invalide.
**/
EFI_STATUS
EFIAPI
ITbtSetDmaUuid (
  IN  VOID  *PeiTbtConfig
  )
{
  UINT32          Index;
  UINT64          RandomNum;
  UINT64          SetUuid;
  UINT16          VendorId;
  PEI_ITBT_CONFIG *PeiITbtConfig;

  DEBUG ((DEBUG_INFO, "[TBT] ITbtSetDmaUuid call Inside\n"));
  PeiITbtConfig = PeiTbtConfig;
  VendorId = 0x8086;
  SetUuid = 0;
  RandomNum = 0;

  if (PeiITbtConfig == NULL) {
    DEBUG ((DEBUG_INFO, "PeiITbtConfig == NULL\n"));
    return EFI_INVALID_PARAMETER;
  }

  for (Index = 0; Index < SA_MAX_HOST_ITBT_DMA_NUMBER; Index++) {

    if (IsITbtControllerEnable (PeiITbtConfig, Index) == FALSE) {
      continue;
    }

    if(GetRandomNumber64(&RandomNum) != FALSE) {
      SetUuid = (UINT64) (((UINT64) RandomNum >> 16) | (UINT64) VendorId << 48); // Program VendorID
      SetUuid = (UINT64) (SetUuid & 0xFFFFFFFFFFFFFFF0);
      SetUuid = (UINT64) (SetUuid | (UINT64) Index); // set instance

      //
      // UUID[31:0]
      //
      PciSegmentWrite32 (
        PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_HOST_DMA_BUS_NUM,SA_HOST_DMA_DEV_NUM,SA_HOST_DMA0_FUN_NUM + Index,R_SA_HOST_DMA_ITBT_SECURITY_LEVEL),
        (UINT32) SetUuid
        );

      //
      // UUID[63:32]
      //
      PciSegmentWrite32 (
        PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_HOST_DMA_BUS_NUM,SA_HOST_DMA_DEV_NUM,SA_HOST_DMA0_FUN_NUM + Index,R_SA_HOST_DMA_UUID),
        ((UINT32) (SetUuid >> 32))
        );
    } else {
      //
      // write UUID[31:0] to 0
      //
        PciSegmentWrite32 (
        PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_HOST_DMA_BUS_NUM,SA_HOST_DMA_DEV_NUM,SA_HOST_DMA0_FUN_NUM + Index,R_SA_HOST_DMA_ITBT_SECURITY_LEVEL),
        (UINT32) SetUuid
        );

      //
      // write UUID[63:32] to 0
      //
      PciSegmentWrite32 (
        PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_HOST_DMA_BUS_NUM,SA_HOST_DMA_DEV_NUM,SA_HOST_DMA0_FUN_NUM + Index,R_SA_HOST_DMA_UUID),
        ((UINT32) (SetUuid >> 32))
        );
    }
  }

  DEBUG ((DEBUG_INFO, "[TBT] ITbtSetDmaUuid call Return\n"));
  return EFI_SUCCESS;
}

/**
  This function pass PEI ITbt Policy to Hob.

  @param[in]  VOID             PeiTbtConfig

  @retval     EFI_SUCCESS      The function completes successfully
  @retval     EFI_UNSUPPORTED  iTBT is not supported.
**/
EFI_STATUS
EFIAPI
PassITbtPolicyToHob(
  IN  VOID  *PeiTbtConfig
)
{
  EFI_STATUS            Status;
  UINT8                 Index;
  PEI_ITBT_CONFIG       *PeiITbtConfig;
  ITBT_INFO_HOB         *ITbtInfoHob;

  DEBUG((DEBUG_INFO, "PassITbtPolicyToHob - Start\n"));
  PeiITbtConfig = PeiTbtConfig;

  ITbtInfoHob = GetFirstGuidHob (&gITbtInfoHobGuid);
  if (ITbtInfoHob == NULL) {
    //
    // Create HOB for ITBT Data
    //
    Status = PeiServicesCreateHob (
               EFI_HOB_TYPE_GUID_EXTENSION,
               sizeof (ITBT_INFO_HOB),
               (VOID **) &ITbtInfoHob
               );
    DEBUG ((DEBUG_INFO, "ITbtInfoHob Created \n"));
    ASSERT_EFI_ERROR (Status);
  }

  if (ITbtInfoHob != NULL) {
    //
    // Initialize the ITBT INFO HOB data.
    //
    ITbtInfoHob->EfiHobGuidType.Name = gITbtInfoHobGuid;

    //
    // Update ITBT Policy
    //
    for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
      ITbtInfoHob->ITbtRootPortConfig[Index].ITbtPcieRootPortEn = PeiITbtConfig->ITbtRootPortConfig[Index].ITbtPcieRootPortEn;
    }
    ITbtInfoHob->ITbtForcePowerOnTimeoutInMs    = PeiITbtConfig->ITbtGenericConfig.ITbtForcePowerOnTimeoutInMs;
    ITbtInfoHob->ITbtConnectTopologyTimeoutInMs = PeiITbtConfig->ITbtGenericConfig.ITbtConnectTopologyTimeoutInMs;
  } else {
    return EFI_NOT_FOUND;
  }

  DEBUG((DEBUG_INFO, "PassITbtPolicyToHob - End\n"));

  return EFI_SUCCESS;
}
