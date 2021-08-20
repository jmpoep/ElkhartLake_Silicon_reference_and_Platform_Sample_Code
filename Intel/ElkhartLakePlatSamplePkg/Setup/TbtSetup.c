/** @file
  Thunderbolt(TM) Setup Rountines.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

#include <Library/HiiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include "Base.h"
#include <Library/PciSegmentLib.h>
#include <SetupPrivate.h>
#include <Register/ItbtPcieRegs.h>
#include <PcieRegs.h>
#include "PlatformBoardId.h"
#include <DTbtInfoHob.h>
#include <Library/TbtCommonLib.h>
#include <Library/DTbtCommonLib.h>
#include <Guid/HobList.h>
#include <Library/TimerLib.h>
#include <Library/PcdLib.h>

#define LTSSM_FSM_RESTORE 0xC74

GLOBAL_REMOVE_IF_UNREFERENCED DTBT_INFO_HOB   *gDTbtInfoHob = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN         Entry = FALSE;


EFI_STATUS
EFIAPI
TbtFormCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  PCH_SETUP                   *PchSetup;
  SETUP_DATA                  *SetupData;
  UINTN                       VarSize;
  EFI_STATUS                  Status;
  volatile EFI_IFR_TYPE_VALUE lValue;
  BOOLEAN                     SaveOnExit;
  EFI_STRING                  RequestString;
  EFI_STRING                  SaRequestString;
  EFI_STRING                  PchRequestString;
  UINT8                       Rootportselected;
  UINT8                       Index;
  UINTN                       RpDev;
  UINTN                       RpFunc;
  UINT8                       HostRouterBus;
  UINTN                       PegBaseAddress;
  UINT8                       Vcn;
  UINT32                      MaxLoopCount;

  Status                  = EFI_SUCCESS;
  SaveOnExit              = FALSE;
  RequestString           = NULL;
  SaRequestString         = NULL;
  PchRequestString        = NULL;
  Rootportselected        = 0;

  DEBUG ((DEBUG_INFO, "TbtFormCallBackFunction \n"));

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED)
    return EFI_UNSUPPORTED;

  if (Action == EFI_BROWSER_ACTION_CHANGING)
    return EFI_SUCCESS;

  if ((Value == NULL) || (ActionRequest == NULL))
    return EFI_INVALID_PARAMETER;

  VarSize = sizeof (SETUP_DATA);
  SetupData = AllocatePool (VarSize);
  ASSERT (SetupData != NULL);
  if (SetupData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  if (!HiiGetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) SetupData)) {
    Status = EFI_NOT_FOUND;
  }
  ASSERT_EFI_ERROR (Status);


  VarSize = sizeof (PCH_SETUP);
  PchSetup = AllocatePool (VarSize);
  ASSERT (PchSetup != NULL);
  if (PchSetup == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  if (!HiiGetBrowserData (&gPchSetupVariableGuid, L"PchSetup", VarSize, (UINT8 *) PchSetup)) {
    Status = EFI_NOT_FOUND;
  }
  ASSERT_EFI_ERROR (Status);

  IoWrite16(0x80, (UINT16)KeyValue);

  lValue = *Value;

  DEBUG ((DEBUG_INFO, "Thunderbolt(TM) call back actions begin \n"));

  switch (KeyValue) {
    case KEY_DTBT_SUPPORT:
      DEBUG ((DEBUG_INFO, "KEY_TBT_SUPPORT CallBack \n"));
      if (SetupData->DiscreteTbtSupport == 1) {
        SetupData->PciExpNative = 0;
        SetupData->Rtd3Support = 0;
        SetupData->DTbtController[0] = 1;
        RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, Rtd3Support), sizeof (SetupData->Rtd3Support));
      } else {
        SetupData->TbtUsbOn = 0;
        SetupData->TbtBootOn = 0;
        SetupData->PciExpNative = 1;
        SetupData->DTbtController[0] = 0;
        RequestString   = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TbtUsbOn), sizeof (SetupData->TbtUsbOn));
        RequestString   = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TbtBootOn), sizeof (SetupData->TbtBootOn));
      }
      RequestString   = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, PciExpNative), sizeof (SetupData->PciExpNative));
      RequestString   = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtController[0]), sizeof (SetupData->DTbtController[0]));
    case KEY_DTBT_CONTROLLER0:
    case KEY_DTBT_CONTROLLER1:
    case KEY_DTBT_CONTROLLER2:
    case KEY_DTBT_CONTROLLER3:
      DEBUG ((DEBUG_INFO, " KEY_TBT_CONTROLLER0 / KEY_TBT_CONTROLLER1 / KEY_TBT_CONTROLLER2 / KEY_TBT_CONTROLLER3 CallBack  \n"));
      Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, (VOID **) &gDTbtInfoHob);
      if (!EFI_ERROR (Status)) {
        DEBUG ((DEBUG_INFO, "Searching Thunderbolt(TM) information Hob... \n"));
        gDTbtInfoHob = GetNextGuidHob (&gDTbtInfoHobGuid, gDTbtInfoHob);
      }
      if (gDTbtInfoHob != NULL) {
        for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
          if (SetupData->DTbtController[Index] == 0x01) {
              Rootportselected = (gDTbtInfoHob->DTbtControllerConfig[Index].PcieRpNumber - 1);
          }
          if (gDTbtInfoHob->DTbtControllerConfig[Index].Type == 0x01) {
            //
            //if PCH-Rootport is supported for TBT, check for the Port which is selected
            //
            if (SetupData->DiscreteTbtSupport == 1) {
              PchSetup->PcieRootPortHPE[Rootportselected] = 1;
            } else {
              PchSetup->PcieRootPortHPE[Rootportselected] = 0;
            }
            PchRequestString = HiiConstructRequestString (PchRequestString, OFFSET_OF (PCH_SETUP, PcieRootPortHPE[Rootportselected]), sizeof (PchSetup->PcieRootPortHPE[Rootportselected]));
          }
        }
      }
    break;

   case KEY_DTBT_CONTROLLER0_HOSTROUTER:
     DEBUG ((DEBUG_INFO, "KEY_TBT_HOSTROUTER 0 CallBack \n"));
     //
     //As per the Bios implementation Guide
     //(Table 2.3: Host Router resource allocation/reservation scheme) ,
     //we need to allocate enough  resources based on Host router type
     //one port or two port
     //
     if (SetupData->DTbthostRouterPortNumber[0] == 2) {
       SetupData->DTbtPcieExtraBusRsvd[0] = 106;
       SetupData->DTbtPcieMemRsvd[0] = 737;
       SetupData->DTbtPcieMemAddrRngMax[0] = 26;
       SetupData->DTbtPciePMemRsvd[0] = 1184;
       SetupData->DTbtPciePMemAddrRngMax[0] = 28;
     } else {
       SetupData->DTbtPcieExtraBusRsvd[0] = 56;
       SetupData->DTbtPcieMemRsvd[0] = 353;
       SetupData->DTbtPcieMemAddrRngMax[0] = 26;
       SetupData->DTbtPciePMemRsvd[0] = 544;
       SetupData->DTbtPciePMemAddrRngMax[0] = 28;
     }
     RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtPcieExtraBusRsvd[0]), sizeof (SetupData->DTbtPcieExtraBusRsvd[0]));
     RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtPcieMemRsvd[0]), sizeof (SetupData->DTbtPcieMemRsvd[0]));
     RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtPcieMemAddrRngMax[0]), sizeof (SetupData->DTbtPcieMemAddrRngMax[0]));
     RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtPciePMemRsvd[0]), sizeof (SetupData->DTbtPciePMemRsvd[0]));
     RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtPciePMemAddrRngMax[0]), sizeof (SetupData->DTbtPciePMemAddrRngMax[0]));

   break;
   case KEY_DTBT_CONTROLLER1_HOSTROUTER:
   //case KEY_DTBT_CONTROLLER2_HOSTROUTER:
   //case KEY_DTBT_CONTROLLER3_HOSTROUTER:
     DEBUG ((DEBUG_INFO, "KEY_TBT_HOSTROUTER 1 CallBack \n"));
     //
     //As per the Bios implementation Guide
     //(Table 2.3: Host Router resource allocation/reservation scheme) ,
     //we need to allocate enough  resources based on Host router type
     //one port or two port
     //

     if (SetupData->DTbthostRouterPortNumber[1] == 2) {
       SetupData->DTbtPcieExtraBusRsvd[1] = 106;
       SetupData->DTbtPcieMemRsvd[1] = 737;
       SetupData->DTbtPcieMemAddrRngMax[1] = 26;
       SetupData->DTbtPciePMemRsvd[1] = 1184;
       SetupData->DTbtPciePMemAddrRngMax[1] = 28;
     } else {
       SetupData->DTbtPcieExtraBusRsvd[1] = 56;
       SetupData->DTbtPcieMemRsvd[1] = 353;
       SetupData->DTbtPcieMemAddrRngMax[1] = 26;
       SetupData->DTbtPciePMemRsvd[1] = 544;
       SetupData->DTbtPciePMemAddrRngMax[1] = 28;
     }
     RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtPcieExtraBusRsvd[1]), sizeof (SetupData->DTbtPcieExtraBusRsvd[1]));
     RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtPcieMemRsvd[1]), sizeof (SetupData->DTbtPcieMemRsvd[1]));
     RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtPcieMemAddrRngMax[1]), sizeof (SetupData->DTbtPcieMemAddrRngMax[1]));
     RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtPciePMemRsvd[1]), sizeof (SetupData->DTbtPciePMemRsvd[1]));
     RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, DTbtPciePMemAddrRngMax[1]), sizeof (SetupData->DTbtPciePMemAddrRngMax[1]));

   break;
   case KEY_ITBT_SUPPORT:
     DEBUG ((DEBUG_INFO, "KEY_ITBT_SUPPORT CallBack \n"));
      if (SetupData->IntegratedTbtSupport == 1) {
        SetupData->TbtVtdBaseSecurity = 1;
        SetupData->ITbtRtd3 = 1;
      } else {
        for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
          SetupData->ITbtRootPort[Index] = 0;
          RequestString   = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, ITbtRootPort[Index]), sizeof (SetupData->ITbtRootPort[Index]));
        }
        SetupData->TbtVtdBaseSecurity = 0;
        SetupData->ITbtRtd3 = 0;
      }
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TbtVtdBaseSecurity), sizeof (SetupData->TbtVtdBaseSecurity));
      RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, ITbtRtd3), sizeof (SetupData->ITbtRtd3));
   break;
   case KEY_TBT_BOOT_ON:
   case KEY_TBT_USB_ON:
    if ((SetupData->TbtBootOn == 1) || (SetupData->TbtUsbOn == 1)) {
      SetupData->TbtSkipPciOprom = 0;
    }
    else {
      SetupData->TbtSkipPciOprom = 1;
    }
    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TbtSkipPciOprom), sizeof (SetupData->TbtSkipPciOprom));
    break;

    case TBT_SECURITY_LEVEL_KEY:
      DEBUG ((EFI_D_INFO, "TBT_SECURITY_LEVEL_KEY CallBack \n"));
      if (SetupData->DiscreteTbtSupport == 1) {
        Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, (VOID **) &gDTbtInfoHob);
        if (!EFI_ERROR (Status)) {
          DEBUG ((DEBUG_INFO, "Searching Thunderbolt(TM) information Hob... \n"));
          gDTbtInfoHob = GetNextGuidHob (&gDTbtInfoHobGuid, gDTbtInfoHob);
        }
        if (gDTbtInfoHob == NULL) {
          DEBUG ((DEBUG_INFO, "Thunderbolt(TM) information Hob is NULL \n"));
          return EFI_UNSUPPORTED;
        }
        for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
          if (SetupData->DTbtController[Index] == 0x01) {
            ForceDtbtPower (gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad, gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioLevel);
            gBS->Stall (SetupData->Gpio3ForcePwrDly * 1000);
            Status = GetDTbtRpDevFun (gDTbtInfoHob->DTbtControllerConfig[Index].Type, gDTbtInfoHob->DTbtControllerConfig[Index].PcieRpNumber - 1, &RpDev, &RpFunc);
            ASSERT_EFI_ERROR (Status);
            if (gDTbtInfoHob->DTbtControllerConfig[Index].Type == TYPE_PEG){
              PegBaseAddress = PCI_SEGMENT_LIB_ADDRESS (0, SA_PEG_BUS_NUM, (UINT32) RpDev, (UINT32) RpFunc, 0);
              if (((PciSegmentRead8(PegBaseAddress + R_SA_PEG_LCTL_OFFSET))& BIT4) == BIT4) {
                PciSegmentAnd8(PegBaseAddress + R_SA_PEG_AFEOVR_OFFSET, (UINT8)~BIT4);
                PciSegmentAnd8(PegBaseAddress + R_SA_PEG_AFEOVR_OFFSET, (UINT8)~BIT5);
                PciSegmentAnd8(PegBaseAddress + R_SA_PEG_CMNSPARE_OFFSET, (UINT8)~BIT3);
                PciSegmentAnd8(PegBaseAddress + R_SA_PEG_LCTL_OFFSET, (UINT8)~BIT4);
                PciSegmentOr8(PegBaseAddress + 0x508, BIT1);
                Vcn = (PciSegmentRead8(PegBaseAddress + R_SA_PEG_VC0RSTS_OFFSET) & BIT1);
                MaxLoopCount = 16;
                DEBUG((DEBUG_INFO, "TBT SETUP:polling for Vcn before %x \n", Vcn));
                while (MaxLoopCount-- > 0) {
                    if (Vcn == 0) {
                        break;
                    }
                    MicroSecondDelay(2000);
                }
              }
            }
            HostRouterBus = PciSegmentRead8 (PCI_SEGMENT_LIB_ADDRESS (0, 0x00, (UINT32)RpDev, (UINT32)RpFunc, PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET));
            DEBUG((DEBUG_INFO, "TBT_US_BUS = 0x%x \n", HostRouterBus));
            if (SetSecLevel (lValue.u8, FixedPcdGet8 (PcdDTbtToPcieRegister), FixedPcdGet8 (PcdPcieToDTbtRegister), HostRouterBus, 0, 0, PCIE2TBT_SET_SECURITY_LEVEL, TBT_5S_TIMEOUT) && (lValue.u8 == GetSecLevel (FixedPcdGet8 (PcdDTbtToPcieRegister), FixedPcdGet8 (PcdPcieToDTbtRegister), HostRouterBus, 0, 0, PCIE2TBT_GET_SECURITY_LEVEL, TBT_5S_TIMEOUT))) {
              SetupData->SecurityMode = lValue.u8;
              SaveOnExit = TRUE;
              //If selected security level is SL3 (Display Port and USB), BIOS should disable "Boot from  Thunderbolt" and "Boot from USB/USB at boot"
              if (SetupData->SecurityMode == 3) {
                SetupData->TbtUsbOn = 0;
                SetupData->TbtBootOn = 0;
                   SetupData->TbtSkipPciOprom = 1;
                RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TbtUsbOn), sizeof (SetupData->TbtUsbOn));
                RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TbtBootOn), sizeof (SetupData->TbtBootOn));
                RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TbtSkipPciOprom), sizeof (SetupData->TbtSkipPciOprom));
              }
            } else {
              SetupData->SecurityMode = 0;
            }

            if (SetupData->Gpio3ForcePwr == 0) {
              ForceDtbtPower (gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad, !(gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioLevel));
              gBS->Stall (SetupData->Gpio3ForcePwrDly * 1000);
            }
          }
        }
      }
      if (SetupData->IntegratedTbtSupport == 1) {
        for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index = Index + 2) {
          if ((SetupData->ITbtRootPort[Index] == 0x01) ||
              (SetupData->ITbtRootPort[Index + 1] == 0x01)) {

            Status = GetITbtDmaDevFun((Index/2), 0, 0, &RpDev, &RpFunc);
            if (EFI_ERROR (Status)) {
              DEBUG((DEBUG_INFO, "ITBT DMA input invalid \n"));
              continue;
            }
            DEBUG ((DEBUG_INFO, "ITBT DMA = 0x%x Device = 0x%x Function = 0x%x \n", Index/2,RpDev,RpFunc));
            if (SetSecLevel (lValue.u8, FixedPcdGet8 (PcdITbtToPcieRegister), FixedPcdGet8 (PcdPcieToITbtRegister), 0, (UINT8)RpDev, (UINT8)RpFunc, PCIE2TBT_SET_SECURITY_LEVEL, TBT_5S_TIMEOUT) && (lValue.u8 == GetSecLevel (FixedPcdGet8 (PcdITbtToPcieRegister), FixedPcdGet8 (PcdPcieToITbtRegister), 0, (UINT8)RpDev, (UINT8) RpFunc, PCIE2TBT_GET_SECURITY_LEVEL, TBT_5S_TIMEOUT))) {
              SetupData->SecurityMode = lValue.u8;
              SaveOnExit = TRUE;
              //If selected security level is SL3 (Display Port and USB), BIOS should disable "Boot from  Thunderbolt" and "Boot from USB/USB at boot"
              if (SetupData->SecurityMode == 3) {
                SetupData->TbtBootOn = 0;
                SetupData->TbtSkipPciOprom = 1;
                RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TbtBootOn), sizeof (SetupData->TbtBootOn));
                RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TbtSkipPciOprom), sizeof (SetupData->TbtSkipPciOprom));
              }
            } else {
              SetupData->SecurityMode = 0;
            }
          }
        }
      }
    break;

    default:
      return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "Thunderbolt(TM) call back - HiiSetBrowserData begin \n"));
  if (RequestString != NULL) {
    VarSize = sizeof (SETUP_DATA);
    if (!HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) SetupData, RequestString)) {
      Status = EFI_NOT_FOUND;
    }
    ASSERT_EFI_ERROR (Status);
    FreePool (RequestString);
  }
  if (PchRequestString != NULL) {
    VarSize = sizeof (PCH_SETUP);
    if (!HiiSetBrowserData (&gPchSetupVariableGuid, L"PchSetup", VarSize, (UINT8 *) PchSetup, PchRequestString)) {
      Status = EFI_NOT_FOUND;
    }
    ASSERT_EFI_ERROR (Status);
    FreePool (PchRequestString);
  }
  DEBUG ((DEBUG_INFO, "Thunderbolt(TM) call back - HiiSetBrowserData end \n"));
  FreePool (PchSetup);
  FreePool (SetupData);

  *ActionRequest = EFI_BROWSER_ACTION_REQUEST_NONE;
  if (SaveOnExit)
    *ActionRequest = EFI_BROWSER_ACTION_REQUEST_SUBMIT;

  DEBUG ((DEBUG_INFO, "Thunderbolt(TM) call back actions end \n"));

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TbtOsSelectorFormCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  PCH_SETUP                  *PchSetup;
  SETUP_DATA                 *SetupData;
  EFI_STRING                  RequestString;
  EFI_STRING                  SaRequestString;
  EFI_STRING                  PchRequestString;
  UINTN                       VarSize;
  EFI_STATUS                  Status;
  BOOLEAN                     SaveOnExit;
  UINT16                      DeviceId;
  UINT16                      CommandReg;
  UINT32                      Timeout;
  UINTN                       RpDev;
  UINTN                       RpFunc;
  UINT8                       HostRouterBus;
  UINT32                      RegVal;
  UINT8                       Index;
  UINT64                      Tbt2Pcie;
  volatile EFI_IFR_TYPE_VALUE lValue;

  Timeout = 50;
  SaveOnExit = FALSE;
  Status = EFI_SUCCESS;
  RequestString = NULL;
  SaRequestString = NULL;
  PchRequestString = NULL;

  DEBUG ((DEBUG_INFO, "TbtOsSelectorFormCallBackFunction \n"));
  if ((Value == NULL) || (ActionRequest == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, (VOID **) &gDTbtInfoHob);
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Searching Thunderbolt(TM) information Hob... \n"));
    gDTbtInfoHob = GetNextGuidHob (&gDTbtInfoHobGuid, gDTbtInfoHob);
  }

  if (gDTbtInfoHob == NULL) {
    DEBUG ((DEBUG_INFO, "Thunderbolt(TM) information Hob is NULL \n"));
    return EFI_UNSUPPORTED;
  }

  VarSize = sizeof (SETUP_DATA);
  SetupData = AllocatePool (VarSize);
  ASSERT (SetupData != NULL);
  if (SetupData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  if (!HiiGetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) SetupData)) {
    Status = EFI_NOT_FOUND;
  }
  ASSERT_EFI_ERROR (Status);
  VarSize = sizeof (PCH_SETUP);
  PchSetup = AllocatePool (VarSize);
  ASSERT (PchSetup != NULL);
  if (PchSetup == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  if (!HiiGetBrowserData (&gPchSetupVariableGuid, L"PchSetup", VarSize, (UINT8 *) PchSetup)) {
    Status = EFI_NOT_FOUND;
  }
  ASSERT_EFI_ERROR (Status);

  lValue = *Value;


  if (!Entry)
  {
    for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
      if (SetupData->DTbtController[Index] == 0x01) {
        Status = GetDTbtRpDevFun(gDTbtInfoHob->DTbtControllerConfig[Index].Type, gDTbtInfoHob->DTbtControllerConfig[Index].PcieRpNumber - 1, &RpDev, &RpFunc);
        ASSERT_EFI_ERROR (Status);
        HostRouterBus = PciSegmentRead8 (PCI_SEGMENT_LIB_ADDRESS (0, 0x00, (UINT32) RpDev, (UINT32) RpFunc, PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET));
        DEBUG((DEBUG_INFO, "TBT_US_BUS = 0x%x \n", HostRouterBus));
        DEBUG ((DEBUG_INFO, "TBT_OSSELECT_FORM_ID CallBack \n"));
        ForceDtbtPower (gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad, gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioLevel);
        gBS->Stall (SetupData->Gpio3ForcePwrDly * 1000);
        TbtSetPcie2TbtCommand (PCIE2TBT_GET_ENUMERATION_METHOD, FixedPcdGet8 (PcdDTbtToPcieRegister), FixedPcdGet8 (PcdPcieToDTbtRegister), 0x00, (UINT8) RpDev, (UINT8) RpFunc, TBT_5S_TIMEOUT);
        Tbt2Pcie = PCI_SEGMENT_LIB_ADDRESS (0, HostRouterBus, 0x00, 0x00, FixedPcdGet8 (PcdDTbtToPcieRegister));
        RegVal = PciSegmentRead32 (Tbt2Pcie);
        if (RegVal == 1) {
          SetupData->Win10Support = 1;
          RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, Win10Support), sizeof (SetupData->Win10Support));
        }
        else if (RegVal == 0) {
          SetupData->Win10Support = 0;
          RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, Win10Support), sizeof (SetupData->Win10Support));
        }
        else {
          SetupData->Win10Support = 2;
          RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, Win10Support), sizeof (SetupData->Win10Support));
        }
        ForceDtbtPower (gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad, (!gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioLevel));
        gBS->Stall (SetupData->Gpio3ForcePwrDly * 1000);
        Entry = TRUE;
      }
    }
  }
  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED)
    return EFI_UNSUPPORTED;

  if (Action == EFI_BROWSER_ACTION_CHANGING)
    return EFI_SUCCESS;

  if ((Value == NULL) || (ActionRequest == NULL))
    return EFI_INVALID_PARAMETER;

  switch (KeyValue) {
    case KEY_TBT_OS_SELECTOR:
      DEBUG ((DEBUG_INFO, "KEY_TBT_OS_SELECTOR CallBack \n"));
      for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
        if (SetupData->DTbtController[Index] == 0) {
          continue;
        }
        ForceDtbtPower (gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad, gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioLevel);
        gBS->Stall (SetupData->Gpio3ForcePwrDly * 1000);
        Status = GetDTbtRpDevFun (gDTbtInfoHob->DTbtControllerConfig[Index].Type, gDTbtInfoHob->DTbtControllerConfig[Index].PcieRpNumber - 1, &RpDev, &RpFunc);
        ASSERT_EFI_ERROR (Status);
        HostRouterBus = PciSegmentRead8 (PCI_SEGMENT_LIB_ADDRESS (0, 0x00, (UINT32) RpDev, (UINT32) RpFunc, PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET));
        DEBUG ((DEBUG_INFO, "TBT_US_BUS = 0x%x \n", HostRouterBus));
        if (SetSecLevel (lValue.u8, FixedPcdGet8 (PcdDTbtToPcieRegister), FixedPcdGet8 (PcdPcieToDTbtRegister), HostRouterBus, 0, 0, PCIE2TBT_SET_SECURITY_LEVEL, TBT_5S_TIMEOUT)) {
          SetupData->Win10Support = lValue.u8;
          TbtSetPcie2TbtCommand (PCIE2TBT_POWER_CYCLE, FixedPcdGet8 (PcdDTbtToPcieRegister), FixedPcdGet8 (PcdPcieToDTbtRegister), 0x00, (UINT8) RpDev, (UINT8) RpFunc, TBT_5S_TIMEOUT);
          DeviceId = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS(0, HostRouterBus, 0x00, 0x00, 0) + PCI_DEVICE_ID_OFFSET);
          CommandReg = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS(0, HostRouterBus, 0x00, 0x00, 0) + PCI_COMMAND_OFFSET);
          while (Timeout-- > 0) {
            if (0xFFFF == CommandReg) {
              //
              // Device is not here return now
              //
              break;
            }
            gBS->Stall (100 * 1000);
          }

           Timeout = 50;
           while (Timeout-- > 0) {
             if (0xFFFF != CommandReg) {
               //
               // Device is not here return now
               //
               break;
            }
            gBS->Stall (100 * 1000);
          }

          if (SetupData->Win10Support == 1) {
            if (0xFFFF != DeviceId) {
              SaveOnExit = TRUE;
              SetupData->TBTHotSMI = 0;
              SetupData->PciExpNative = 1;
              RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TBTHotSMI), sizeof (SetupData->TBTHotSMI));
              RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, PciExpNative), sizeof (SetupData->PciExpNative));
            }
          }
          else if (SetupData->Win10Support == 0){
            if (0xFFFF == DeviceId) {
              SetupData->TBTHotSMI = 1;
              SetupData->PciExpNative = 0;
              RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, TBTHotSMI), sizeof (SetupData->TBTHotSMI));
              RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, PciExpNative), sizeof (SetupData->PciExpNative));
              SaveOnExit = TRUE;
            }
          }
          else {
            SetupData->Win10Support = 2;
            SaveOnExit = FALSE;
          }
        }
        ForceDtbtPower (gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad, (!gDTbtInfoHob->DTbtControllerConfig[Index].ForcePwrGpio.GpioLevel));
        gBS->Stall (SetupData->Gpio3ForcePwrDly * 1000);
      }
      break;
    default:
      return EFI_SUCCESS;
  }

  if (RequestString != NULL) {
    VarSize = sizeof (SETUP_DATA);
    if (!HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) SetupData, RequestString)) {
      Status = EFI_NOT_FOUND;
    }
    ASSERT_EFI_ERROR (Status);
    FreePool (RequestString);
  }
  if (PchRequestString != NULL) {
    VarSize = sizeof (PCH_SETUP);
    if (!HiiSetBrowserData (&gPchSetupVariableGuid, L"PchSetup", VarSize, (UINT8 *) PchSetup, PchRequestString)) {
      Status = EFI_NOT_FOUND;
    }
    ASSERT_EFI_ERROR (Status);
    FreePool (PchRequestString);
  }
  DEBUG ((DEBUG_INFO, "Thunderbolt(TM) call back - HiiSetBrowserData end \n"));
  FreePool (PchSetup);
  FreePool (SetupData);

  *ActionRequest = EFI_BROWSER_ACTION_REQUEST_NONE;
  if (SaveOnExit)
    *ActionRequest = EFI_BROWSER_ACTION_REQUEST_SUBMIT;

  DEBUG ((DEBUG_INFO, "Thunderbolt(TM) call back actions end \n"));

  return EFI_SUCCESS;
}

/**
  Get uncommitted Vtd  Browser status from BIOS setup menu to check Vtd availability

  @retval EFI_SUCCESS           Vt-d is available.
  @retval EFI_UNSUPPORTED       Vt-d is not available.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to get buffer.
**/
EFI_STATUS
GetVtdStatusfromBrowser (
  VOID
  )
{
  SETUP_VOLATILE_DATA         *SetupVolatileData;
  UINTN                       VarSize;
  EFI_STATUS                  Status;

  //
  // Initialization
  //
  SetupVolatileData           = NULL;
  Status                      = EFI_SUCCESS;

  //
  // Allocate memory for SetupVolatileData
  //
  VarSize = sizeof (SETUP_VOLATILE_DATA);
  SetupVolatileData = AllocateZeroPool (VarSize);

  if (SetupVolatileData == NULL) {
    DEBUG ((DEBUG_ERROR, "Allocate SetupVolatileData size fail\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  //
  // Retrive uncommitted SetupVolatileData data from Browser
  //
  if (FALSE == HiiGetBrowserData (&gSetupVariableGuid, L"SetupVolatileData", VarSize, (UINT8 *) SetupVolatileData)) {
    DEBUG ((DEBUG_ERROR, "Not able to retrive SetupVolatileData\n"));
    Status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  //
  // Return VTd Support
  //
  if (SetupVolatileData->VTdAvailable == TRUE) {
    Status = EFI_SUCCESS;
  } else {
    Status = EFI_UNSUPPORTED;
  }

Exit:
  if (SetupVolatileData != NULL) {
    FreePool (SetupVolatileData);
  }
  return Status;
}


/**
  Get uncommitted Vtd TBT Base Security Browser value from BIOS setup menu

  @retval EFI_SUCCESS           TBT Base Security enable.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to get buffer.
  @retval EFI_UNSUPPORTED       TBT Base Security diable.
**/
EFI_STATUS
BaseSecurityGetBrowserValue (
  VOID
  )
{
  SETUP_DATA                  *SetupData;
  UINTN                       VarSize;
  EFI_STATUS                  Status;

  //
  // Initialization
  //
  SetupData = NULL;
  Status = EFI_SUCCESS;

  //
  // Allocate memory for SetupData
  //
  VarSize = sizeof (SETUP_DATA);
  SetupData = AllocateZeroPool (VarSize);
  if (SetupData == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to allocate SetupData size\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  //
  // Retrive uncommitted SetupData data from Browser
  //
  if (FALSE == HiiGetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) SetupData)) {
    DEBUG ((DEBUG_ERROR, "Failed to retrive SetupData\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  if (SetupData->TbtVtdBaseSecurity == FALSE) {
    Status = EFI_UNSUPPORTED;
  } else {
    Status = EFI_SUCCESS;
  }

Exit:
  if (SetupData != NULL) {
    FreePool (SetupData);
  }
  return Status;
}

/**
  Disable CSM from browser setup option

  @retval EFI_SUCCESS           Successfully disable CSM.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to get buffer.
  @retval EFI_INVALID_PARAMETER Failed to disable CSM
**/
EFI_STATUS
DisableCsm (
  VOID
  )
{
  SETUP_DATA                  *SetupData;
  UINTN                       VarSize;
  EFI_STATUS                  Status;
  EFI_STRING                  RequestString;

  //
  // Initialization
  //
  SetupData = NULL;
  Status = EFI_SUCCESS;
  RequestString = NULL;

  //
  // Allocate memory for SetupData
  //
  VarSize = sizeof (SETUP_DATA);
  SetupData = AllocateZeroPool (VarSize);
  if (SetupData == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to allocate SetupData size\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  //
  // Retrive uncommitted SetupData data from Browser
  //
  if (FALSE == HiiGetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) SetupData)) {
    DEBUG ((DEBUG_ERROR, "Failed to retrive SetupData\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  //
  // Disable CSM if CSM is enable
  //
  if (SetupData->CsmControl != EFI_CSM_CONTROL_ALWAYS_OFF) {

    SetupData->CsmControl = EFI_CSM_CONTROL_ALWAYS_OFF;

    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, CsmControl), sizeof (SetupData->CsmControl));
    if (RequestString != NULL) {
      VarSize = sizeof (SETUP_DATA);
      if (FALSE == HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) SetupData, RequestString)) {
        DEBUG ((DEBUG_ERROR, "Failed to enable CSM\n"));
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
      }

      DEBUG ((DEBUG_INFO, "Successfully disable CSM\n"));
    }
  }

Exit:
  if (RequestString != NULL) {
    FreePool (RequestString);
  }
  if (SetupData != NULL) {
    FreePool (SetupData);
  }

  return Status;
}


/**
  Setup VTD Setup option value
  @param[in]  BOOLEAN Config

  @retval EFI_SUCCESS           Successfully disable Legacy USB.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to get buffer.
  @retval EFI_INVALID_PARAMETER Failed to disable Legacy USB.
  @retval EFI_UNSUPPORTED       Vt-d is not available.
**/
EFI_STATUS
SetVtdFromBrowser (
  IN BOOLEAN Config
  )
{
  SA_SETUP                    *SaSetup;
  UINTN                       VarSize;
  EFI_STATUS                  Status;
  EFI_STRING                  RequestString;

  //
  // Initialization
  //
  SaSetup = NULL;
  Status = EFI_SUCCESS;
  RequestString = NULL;

  if (GetVtdStatusfromBrowser() == EFI_UNSUPPORTED) {
    DEBUG ((DEBUG_ERROR, "Vtd Support is unavailable\n"));
    Status = EFI_UNSUPPORTED;
    goto Exit;
  }

  //
  // Allocate memory for SaSetup
  //
  VarSize = sizeof (SA_SETUP);
  SaSetup = AllocateZeroPool (VarSize);
  if (SaSetup == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to allocate SaSetup size\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  //
  // Retrive uncommitted SaSetup data from Browser
  //
  if (FALSE == HiiGetBrowserData (&gSaSetupVariableGuid, L"SaSetup", VarSize, (UINT8 *) SaSetup)) {
    DEBUG ((DEBUG_ERROR, "Failed to retrive SaSetup\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  //
  // Config Vtd Browser setup option
  //
  if (Config == TRUE) {
    SaSetup->EnableVtd = TRUE;
  } else {
    SaSetup->EnableVtd = FALSE;
  }

  RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SA_SETUP, EnableVtd), sizeof (SaSetup->EnableVtd));
  if (RequestString != NULL) {
    //
    // Pass changed uncommitted data back to Form Browser
    //
    VarSize = sizeof (SA_SETUP);
    if (FALSE == HiiSetBrowserData (&gSaSetupVariableGuid, L"SaSetup", VarSize, (UINT8 *) SaSetup, RequestString)) {
      DEBUG ((DEBUG_INFO, "Failed to config Vtd\n"));
      Status = EFI_INVALID_PARAMETER;
      goto Exit;
    }

    DEBUG ((DEBUG_INFO, "Successfully config Vtd\n"));
  }

Exit:
  if (RequestString != NULL) {
    FreePool (RequestString);
  }
  if (SaSetup != NULL) {
    FreePool (SaSetup);
  }

  return Status;
}



/**
  TBTSecurityCallBackFunction
  @param[in] This             Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param[in] Action           Specifies the type of action taken by the browser.
  @param[in] KeyValue         A unique value which is sent to the original exporting driver
                              so that it can identify the type of data to expect of data to expect.
  @param[in] Type             The type of value for the question.
  @param[in] Value            A pointer to the data being sent to the original exporting driver.

  @retval EFI_SUCCESS         The callback successfully handled the action
  @retval EFI_UNSUPPORTED     The specified action is not supported by the callback
  @retval EFI_INVALID_PARAMETER Failed to disable Legacy USB.
**/
EFI_STATUS
EFIAPI
TBTSecurityCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  SETUP_VOLATILE_DATA         *SetupVolatileData;
  UINTN                       VarSize;
  EFI_STATUS                  Status;
  UINT32                      SetupVolAttributes;

  //
  // Initialization
  //
  VarSize                     = 0;
  Status                      = EFI_SUCCESS;
  SetupVolatileData           = NULL;
  SetupVolAttributes          = 0;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  if (Action == EFI_BROWSER_ACTION_CHANGING) {
    return EFI_SUCCESS;
  }

  if ((Value == NULL) || (ActionRequest == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((DEBUG_INFO, "[TBT] TBTSecurityCallBackFunction START\n"));
  IoWrite16 (0x80, (UINT16)KeyValue);
  //
  // Allocate memory for SetupVolatileData
  //
  VarSize = sizeof (SETUP_VOLATILE_DATA);
  SetupVolatileData = AllocateZeroPool (VarSize);

  if (SetupVolatileData == NULL) {
    DEBUG ((DEBUG_ERROR, "Allocate SetupVolatileData size fail\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  //
  // Retrive SetupVolatileData data from memory
  //
  Status = gRT->GetVariable (
                    L"SetupVolatileData",
                    &gSetupVariableGuid,
                    &SetupVolAttributes,
                    &VarSize,
                    SetupVolatileData
                    );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Not able to retrive SetupVolatileData from Nvram\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  //
  // Retrive uncommitted BaseSecurity data from Browser
  //
  if (BaseSecurityGetBrowserValue() == EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "User enable TbtVtdBaseSecurity. Set and grayout options\n"));
    SetupVolatileData->TbtVtdBaseSecurityGrayOut = TRUE;
    //
    // Enable VTd from browser
    //
    SetVtdFromBrowser (TRUE);

    //
    // Disable CSM from browser
    //
    DisableCsm ();

    //
    // Disable Legacy USB from browser
    //

  } else {
    DEBUG ((DEBUG_INFO, "User disable TbtVtdBaseSecurity\n"));
    SetupVolatileData->TbtVtdBaseSecurityGrayOut = FALSE;
  }

  //
  // Save SetupVolatileData data back to memory
  //
  Status = gRT->SetVariable (
                    L"SetupVolatileData",
                    &gSetupVariableGuid,
                    SetupVolAttributes,
                    VarSize,
                    SetupVolatileData
                    );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Not able to save SetupVolatileData\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

Exit:
  if (SetupVolatileData != NULL) {
    FreePool (SetupVolatileData);
  }

  DEBUG ((DEBUG_INFO, "[TBT] TBTSecurityCallBackFunction END\n"));
  return Status;
}
