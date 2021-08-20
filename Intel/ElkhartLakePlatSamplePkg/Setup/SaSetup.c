/** @file
  The file contains SA related setup options

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

#include <SetupPrivate.h>
#include "OemSetup.h"
#include "SaSetup.h"
#include "PlatformBoardId.h"
#include "CpuRegs.h"
#include "DimmInfo.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/CpuPlatformLib.h>
#include <Protocol/SaPolicy.h>
#include <Protocol/SmbusHc.h>
#include <Protocol/MemInfo.h>
#include <Protocol/GopPolicy.h>
#if FixedPcdGetBool(PcdITbtEnable) == 1
#include "TcssDataHob.h"
#endif
#include <IpuDataHob.h>
#include <Library/CpuPcieInfoLib.h>
#include <Library/CpuPcieInitCommon.h>
#include <CpuPcieHob.h>
#include <Library/CpuRegbarAccessLib.h>
#include <Register/CpuPcieRegs.h>
#include <VmdInfoHob.h>
#include <Register/SataRegs.h>
#include <Library/SataLib.h>
#include <Register/IgdRegs.h>

static EFI_HII_HANDLE     gHiiHandle;


VOID
UpdatePegInfo (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  );

VOID
UpdateDmiInfo (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  );

EFI_STATUS
EFIAPI
UpdateVmdInfo (
  EFI_HII_HANDLE HiiHandle
  );
#define NB_MIN(a, b)  (((a) < (b)) ? (a) : (b))

EFI_STRING_ID  DimmSizeString[SLOT_NUM] = {
  STRING_TOKEN (STR_DIMM_SIZE_CH0_SLT0_VALUE),
  STRING_TOKEN (STR_DIMM_SIZE_CH0_SLT1_VALUE),
  STRING_TOKEN (STR_DIMM_SIZE_CH1_SLT0_VALUE),
  STRING_TOKEN (STR_DIMM_SIZE_CH1_SLT1_VALUE)
};

EFI_STRING_ID  RankInDimmString[SLOT_NUM] = {
  STRING_TOKEN (STR_DIMM_CH0_SLT0_RANK_VALUE),
  STRING_TOKEN (STR_DIMM_CH0_SLT1_RANK_VALUE),
  STRING_TOKEN (STR_DIMM_CH1_SLT0_RANK_VALUE),
  STRING_TOKEN (STR_DIMM_CH1_SLT1_RANK_VALUE)
};

EFI_STRING_ID  DimmMfgString[SLOT_NUM] = {
  STRING_TOKEN (STR_DIMM_CH0_SLT0_MFG_VALUE),
  STRING_TOKEN (STR_DIMM_CH0_SLT1_MFG_VALUE),
  STRING_TOKEN (STR_DIMM_CH1_SLT0_MFG_VALUE),
  STRING_TOKEN (STR_DIMM_CH1_SLT1_MFG_VALUE)
};

EFI_STRING_ID  DimmStatusString[SLOT_NUM] = {
  STRING_TOKEN (STR_DIMM_CH0_SLT0_STATUS),
  STRING_TOKEN (STR_DIMM_CH0_SLT1_STATUS),
  STRING_TOKEN (STR_DIMM_CH1_SLT0_STATUS),
  STRING_TOKEN (STR_DIMM_CH1_SLT1_STATUS)
};

EFI_STRING_ID  PegInfo[4] = {
  STRING_TOKEN (STR_PEG0_INFO_VALUE),
  STRING_TOKEN (STR_PEG1_INFO_VALUE),
  STRING_TOKEN (STR_PEG2_INFO_VALUE),
  STRING_TOKEN (STR_PEG3_INFO_VALUE)
};

VOID
InitSaStrings (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  )
{
  UINT8                           MemoryType;
  UINT8                           Profile;
  UINT64                          MemorySize;
  UINT16                          DdrFrequency;
  UINT16                          VendorId;
  EFI_STATUS                      Status;
  UINTN                           SaSetupVariableSize;
  UINTN                           SetupVolVariableSize;
  UINT32                          Value32;
  UINTN                           Slot;
  UINT8                           w;
  UINT8                           x;
  UINT8                           y;
  UINT8                           z;
  UINT8                           Rp0;
  UINT8                           Rpn;
  UINT16                          Data16;
  UINT8                           DimmStatus[SLOT_NUM];
  UINT8                           RankInDimm[SLOT_NUM];

  MEM_INFO_PROTOCOL               *MemInfoProtocol;
  MEMORY_INFO_DATA                *MemInfoData;
  MEMORY_TIMING                   *Timing;
  SA_POLICY_PROTOCOL              *SaPolicy;
  CHAR8                           *GtStr;
  CHAR8                           *DimmStatusStr;
  UINT32                          SaVariableAttributes;
  UINT32                          SetupVolAttributes;
  GRAPHICS_DXE_CONFIG             *GraphicsDxeConfig;
  UINT8                           CpuSku;
  UINT32                          EdramSize;
  UINT64                          IgdPciD2F0RegBase;
  IPU_DATA_HOB                    *IpuDataHob;


  if ((Class != MAIN_FORM_SET_CLASS) && (Class != ADVANCED_FORM_SET_CLASS)) {
    return;
  }

  DEBUG ((DEBUG_INFO, "<InitSaStrings>"));

  CpuSku = GetCpuSku();
  Status = gBS->LocateProtocol (&gSaPolicyProtocolGuid, NULL, (VOID **) &SaPolicy);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *)SaPolicy, &gGraphicsDxeConfigGuid, (VOID *)&GraphicsDxeConfig);
  ASSERT_EFI_ERROR (Status);

  SaSetupVariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  &SaVariableAttributes,
                  &SaSetupVariableSize,
                  &mSaSetup
                  );
  DEBUG((DEBUG_INFO, "GetVariable 'SaSetup' Status = %r\n", Status));

  SetupVolVariableSize = sizeof (SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  &SetupVolAttributes,
                  &SetupVolVariableSize,
                  &mSetupVolatileData
                  );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }


  //
  // Get the Memory Info HOB Protocol if it exists.
  //
  Status = gBS->LocateProtocol (&gMemInfoProtocolGuid, NULL, (VOID **) &MemInfoProtocol);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
  MemInfoData = &MemInfoProtocol->MemInfoData;

  //
  // Force the DiSM policy to the Max allowed DiSM size in GB, for the DDR space available
  //
  if ((MemInfoData->memSize == MEM_4GB) && (mSaSetup.DismSize >= 1)) {
    mSaSetup.DismSize = 1;
  } else if ((MemInfoData->memSize == MEM_8GB) && (mSaSetup.DismSize >= 3)) {
    mSaSetup.DismSize = 3;
  } else if ((MemInfoData->memSize == MEM_12GB) && (mSaSetup.DismSize >= 5)) {
    mSaSetup.DismSize = 5;
  }

  // For 2LM Sku, DSM is still required but only needs to be 4MB
  //
  if (mSaSetup.DismSize != 0) {
    mSaSetup.IgdDvmt50PreAlloc = 240; // 4 MB
  }

  MemoryType    = MemInfoData->DdrType;
  DdrFrequency  = MemInfoData->ddrFreq;
  Profile       = MemInfoData->Profile;
  Timing        = &MemInfoData->Timing[Profile];

  mSaSetup.XmpProfileEnable = MemInfoData->XmpProfileEnable;
  Status = gRT->SetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  SaVariableAttributes,
                  SaSetupVariableSize,
                  &mSaSetup
                  );
  for (Slot = 0; Slot < SLOT_NUM; Slot++) {
    DimmStatus[Slot] = MemInfoData->DimmStatus[Slot];
    RankInDimm[Slot] = MemInfoData->RankInDimm[Slot];
  }

  //
  // Update the memory size string for main page and chipset page
  //
  if ((Class == MAIN_FORM_SET_CLASS) || (Class == ADVANCED_FORM_SET_CLASS)) {
    MemorySize = MemInfoData->memSize;
    InitString (HiiHandle, STRING_TOKEN (STR_MEMORY_SIZE_VALUE), L"%5ld MB", MemorySize);
    InitString (HiiHandle, STRING_TOKEN (STR_MEMORY_FREQ_VALUE), L"%5ld MHz", DdrFrequency);

    //
    // MCDECS_CR_MRC_REVISION - MRC version
    //
    Value32 = MmioRead32 ((UINTN) PcdGet64 (PcdMchBaseAddress) + 0x5034);
    x       = (UINT8) ((Value32 & 0xFF000000) >> 24);
    y       = (UINT8) ((Value32 & 0xFF0000) >> 16);
    z       = (UINT8) ((Value32 & 0xFF00) >> 8);
    w       = (UINT8) (Value32 & 0xFF);

    InitString (HiiHandle, STRING_TOKEN (STR_MRC_REV_VALUE), L"%d.%d.%d.%d", x, y, z, w);
  }

  IgdPciD2F0RegBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);

    if (PciSegmentRead16 (IgdPciD2F0RegBase + 0x2) != 0xFFFF) {
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_CHIP_IGFX_GOP_REV_VALUE),
        L"%s",
        &GraphicsDxeConfig->GopVersion
      );
    }

  //
  // GT frequency setting
  //
  if ((PciSegmentRead16 (IgdPciD2F0RegBase + 0x2) != 0xFFFF)) {
    Value32 = MmioRead32 ((UINTN) PcdGet64 (PcdMchBaseAddress) + 0x5998);
    Rpn = (UINT8) ((Value32 & 0xFF0000) >> 16);
    Rp0 = (UINT8) (Value32 & 0xFF);
    InitString (HiiHandle, STRING_TOKEN (STR_GT_FREQ_HELP), L"Maximum GT frequency limited by the user. Choose between %dMHz (RPN) and %dMHz (RP0). Value beyond the range will be clipped to min/max supported by SKU", Rpn*50, Rp0*50);
  }

  if (Class == MAIN_FORM_SET_CLASS) {
    gHiiHandle = HiiHandle;
    //
    // DID to GT Sku mapping : X0Y = GT1, X1Y = GT2, X2Y = GT3, X3Y = GT4
    //
    Data16 = PciSegmentRead16 (IgdPciD2F0RegBase + 0x2);
    if (Data16 != 0xFFFF) {
      switch (Data16 & 0x30) {
        case 0x0:
          GtStr = "GT1";
          break;

        case 0x10:
          GtStr = "GT2";
          break;

        case 0x20:
          GtStr = "GT3";
          break;

        case 0x30:
          GtStr = "GT4";
          break;

        default:
          GtStr = "Unknown";
          break;
      }
      InitString (gHiiHandle, STRING_TOKEN (STR_PROCESSOR_GT_VALUE), L"%a (0x%X)", GtStr, Data16);
    }

    //
    // EDRAM Size display
    //
    if (AsmReadMsr64 (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_EDRAM_ENABLE_MASK) {
      EdramSize = 0;
      if ((CpuSku == EnumCpuUlt) || (CpuSku == EnumCpuUlx)) {
        EdramSize = 64;
      } else if ((CpuSku == EnumCpuTrad) || (CpuSku == EnumCpuHalo)) {
        EdramSize = 128;
      }
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_EDRAM_SIZE_VALUE),
        L"%d MB",
        EdramSize
      );
    }

  }

  if (Class == ADVANCED_FORM_SET_CLASS) {

    SetupVolVariableSize = sizeof (SETUP_VOLATILE_DATA);
    Status = gRT->GetVariable (
                    L"SetupVolatileData",
                    &gSetupVariableGuid,
                    &SetupVolAttributes,
                    &SetupVolVariableSize,
                    &mSetupVolatileData
                    );
    ASSERT_EFI_ERROR (Status);
    if (!EFI_ERROR (Status)) {
      for (Slot = 0; Slot < (CH_NUM * DIMM_NUM); Slot++) {
        InitString (
          HiiHandle,
          DimmSizeString[Slot],
          L"%4ld MB (%a)",
          MemInfoData->dimmSize[Slot],
          (MemoryType < MRC_DDR_TYPE_UNKNOWN) ? MemoryTypeStr[MemoryType] : "Unknown"
          );
      }

      for (Slot = 0; Slot < SLOT_NUM; Slot++) {
        if (DimmStatus[Slot] < DIMM_NOT_PRESENT) {
          mSetupVolatileData.DimmPresent[Slot] = 1;
          InitString (
            HiiHandle,
            RankInDimmString[Slot],
            L"%1d",
            RankInDimm[Slot]
            );

          DimmStatusStr = (DimmStatus[Slot] == DIMM_DISABLED) ? "Populated & Disabled" : "Populated & Enabled";

          /**
            Get the Memory Module Vendor JEDEC ID
            Byte 117-118 for DDR3/LPDDR3 and byte 320-321 for DDR4
            It's from first byte of SPD buffer.
          **/
          VendorId = *(UINT16 *) (UINTN) (MemInfoData->DimmsSpdData[Slot]);
          VendorId &= ~(BIT7);  // Clear the parity bit
          for (y = 0; y < MemoryModuleManufacturerListSize; y++) {
            if (VendorId == MemoryModuleManufacturerList[y].MfgId) {
              InitString (
                HiiHandle,
                DimmMfgString[Slot],
                L"%a",
                MemoryModuleManufacturerList[y].String
                );
              break;
            }
          }
        } else {
          mSetupVolatileData.DimmPresent[Slot] = 0;
          DimmStatusStr = "Not Populated / Disabled";
        }
        InitString (
          HiiHandle,
          DimmStatusString[Slot],
          L"%a",
          DimmStatusStr
          );
      } // for Slot
      //
      // SA PCIe code version
      //
      Value32 = MmioRead32 ((UINTN) PcdGet64 (PcdDmiBaseAddress) + R_SA_DMIBAR_SCRATCHPAD1_OFFSET);
      w       = (UINT8) ((Value32 & 0xFF000000) >> 24);
      x       = (UINT8) ((Value32 & 0x00FF0000) >> 16);
      y       = (UINT8) ((Value32 & 0x0000FF00) >> 8);
      z       = (UINT8)  (Value32 & 0x000000FF);

      InitString (
        HiiHandle,
        STRING_TOKEN (STR_CPU_PCIE_CODE_VERSION_VALUE),
        L"%d.%d.%d.%d",
        w,
        x,
        y,
        z
        );
      //
      // VT-d status report
      //
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_SA_VTD_VALUE),
        mSetupVolatileData.VTdAvailable ? L"Supported" : L"Unsupported"
        );

      //
      // IPU BIOS Setup option display
      //
      IpuDataHob = (IPU_DATA_HOB *) GetFirstGuidHob (&gIpuDataHobGuid);
      if (IpuDataHob != NULL) {
        mSetupVolatileData.IpuSupport = 1;
      } else {
        mSetupVolatileData.IpuSupport = 0;
      }

      Status = gRT->SetVariable (
                      L"SetupVolatileData",
                      &gSetupVariableGuid,
                      SetupVolAttributes,
                      SetupVolVariableSize,
                      &mSetupVolatileData
                      );
      ASSERT_EFI_ERROR (Status);
    } // if SetupVolatileData found
    //
    // Update the tCL, tRCD, tRP and tRAS string with data obtained from MemInfo protocol
    //
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_MEMORY_VDD_VALUE),
      L"%d",
      MemInfoData->VddVoltage[Profile]
      );

    InitString (
      HiiHandle,
      STRING_TOKEN (STR_MEMORY_TIMINGS_VALUE),
      L"%d-%d-%d-%d",
      Timing->tCL,
      Timing->tRCDtRP,
      Timing->tRCDtRP,
      Timing->tRAS
      );


  } // if ADVANCED_FORM_SET_CLASS

}

VOID
UpdatePegInfo (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  )
{
  UINT16              Data16;
  UINT8               Index;
  UINT8               PegDeviceNumber;
  UINT8               PegFunctionNumber;
  UINTN               SetupVolVariableSize;
  UINT32              SetupVolAttributes;
  EFI_STATUS          Status;

  Data16 = 0;

  if (Class == ADVANCED_FORM_SET_CLASS) {

    SetupVolVariableSize = sizeof (SETUP_VOLATILE_DATA);
    Status = gRT->GetVariable (
                    L"SetupVolatileData",
                    &gSetupVariableGuid,
                    &SetupVolAttributes,
                    &SetupVolVariableSize,
                    &mSetupVolatileData
                    );
    ASSERT_EFI_ERROR (Status);

    for (Index = 0; Index < 4; Index++) {

      if (Index == 3) { // PEG 3 is at 0.6.0
        PegDeviceNumber   = SA_PEG3_DEV_NUM;
        PegFunctionNumber = SA_PEG3_FUN_NUM;
      } else {
        PegDeviceNumber   = SA_PEG0_DEV_NUM;
        PegFunctionNumber = Index;
      }

      //
      // Initialize PegPresent = 0 (Not Present)
      //
      mSetupVolatileData.PegPresent[Index] = 0;

      //
      // Check for DID VID to check Root Port is present
      //
      Data16 = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, PegDeviceNumber, PegFunctionNumber, 0x0));

      if (Data16 != 0xFFFF) {
        //
        // Read Slot Status register
        //
        Data16 = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, PegDeviceNumber, PegFunctionNumber, R_SA_PEG_SLOTSTS_OFFSET));

        //
        // Check for Presence Detect State SlotStatus 0xba[6]
        //
        if (Data16 & 0x40) {
          //
          // Read LinkStatus 0xb2[3-0]-Current Link Speed, [9-4]-Negotiated Link Width.
          //
          Data16 = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, PegDeviceNumber, PegFunctionNumber, R_SA_PEG_LSTS_OFFSET));

          InitString (
            HiiHandle,
            PegInfo[Index],
            L"x%d  Gen%1d",
            ((Data16 & 0x3f0) >> 4),
            (Data16 & 0xf)
            );

          //
          // Initialize PegPresent = 1 (Present)
          //
          mSetupVolatileData.PegPresent[Index] = 1;

        }
      }
    }
    //
    // for loop
    //
    Status = gRT->SetVariable (
                    L"SetupVolatileData",
                    &gSetupVariableGuid,
                    SetupVolAttributes,
                    SetupVolVariableSize,
                    &mSetupVolatileData
                    );
    ASSERT_EFI_ERROR (Status);

  }
  //
  // ADVANCED_FORM_SET_CLASS
  //
}

VOID
UpdateDmiInfo (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  )
{
  UINT16  Data16;
  UINT64  DmiBar;

  //
  // Get DMIBAR
  //
  PciSegmentReadBuffer (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DMIBAR), sizeof (DmiBar), &DmiBar);
  DmiBar &= ~((UINT64) BIT0);

  //
  // LSTS 9:4 - DMI Link Negotiated Width, 3:0 - Max Link Speed, Gen2/Gen1 Infomation
  //
  Data16 = *(UINT16 *) (UINTN) (DmiBar + 0x8a);

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_DMI_INFO_VALUE),
    L"X%d  Gen%1d",
    ((Data16 >> 4) & 0xf),
    (Data16 & 0xf)
    );
}

EFI_STATUS
EFIAPI
TcssPcieRootPortCallback (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
#if FixedPcdGetBool(PcdITbtEnable) == 1
  SA_SETUP    *SaSetup;
  SETUP_DATA  *SetupData;
  UINTN       VarSize;
  EFI_STATUS  Status;
  EFI_STRING  RequestString;
  UINT8       TcssRootPort0;
  UINT8       TcssRootPort1;
  UINT8       TcssRootPort2;
  UINT8       TcssRootPort3;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  TcssRootPort0 = 0;
  TcssRootPort1 = 0;
  TcssRootPort2 = 0;
  TcssRootPort3 = 0;

  DEBUG ((EFI_D_INFO, "TcssPcieRootPortCallback()\n"));

  Status = EFI_SUCCESS;
  VarSize = sizeof (SA_SETUP);
  SaSetup = AllocatePool (VarSize);
  ASSERT (SaSetup != NULL);
  if (SaSetup == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  if (!HiiGetBrowserData (&gSaSetupVariableGuid, L"SaSetup", VarSize, (UINT8 *) SaSetup)) {
    Status = EFI_NOT_FOUND;
  }
  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR (Status)) {
    TcssRootPort0 = SaSetup->TcssItbtPcie0En;
    TcssRootPort1 = SaSetup->TcssItbtPcie1En;
    TcssRootPort2 = SaSetup->TcssItbtPcie2En;
    TcssRootPort3 = SaSetup->TcssItbtPcie3En;

    RequestString = NULL;

    if (RequestString != NULL) {
      if (!HiiSetBrowserData (&gSaSetupVariableGuid, L"SaSetup", VarSize, (UINT8 *) SaSetup, RequestString)) {
        Status = EFI_NOT_FOUND;
      }
      ASSERT_EFI_ERROR (Status);
      FreePool (RequestString);
    }
  }
  FreePool (SaSetup);

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

  if (!EFI_ERROR (Status)) {
    SetupData->ITbtRootPort[0] = TcssRootPort0;
    SetupData->ITbtRootPort[1] = TcssRootPort1;
    SetupData->ITbtRootPort[2] = TcssRootPort2;
    SetupData->ITbtRootPort[3] = TcssRootPort3;

    RequestString = NULL;
    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, ITbtRootPort[0]), sizeof(SetupData->ITbtRootPort[0]));
    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, ITbtRootPort[1]), sizeof(SetupData->ITbtRootPort[1]));
    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, ITbtRootPort[2]), sizeof(SetupData->ITbtRootPort[2]));
    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, ITbtRootPort[3]), sizeof(SetupData->ITbtRootPort[3]));

    if (RequestString != NULL) {
      if (!HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) SetupData, RequestString)) {
        Status = EFI_NOT_FOUND;
      }
      ASSERT_EFI_ERROR (Status);
      FreePool (RequestString);
    }
  }
  FreePool (SetupData);

  return Status;
#else
  return EFI_SUCCESS;
#endif
}
EFI_STATUS
EFIAPI
TcssXhciCallback (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  EFI_STATUS  Status;
  SETUP_DATA  *SetupData;
  UINTN       VarSize;
  EFI_STRING  RequestString;

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_INFO, "TcssXhciCallback()\n"));

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }

  if (Value->u8 != 0) {
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
  if (!EFI_ERROR (Status)) {
    SetupData->UsbcBiosTcssHandshake = 0;
    RequestString = NULL;
    RequestString = HiiConstructRequestString (RequestString, OFFSET_OF (SETUP_DATA, UsbcBiosTcssHandshake), sizeof (SetupData->UsbcBiosTcssHandshake));

    if (RequestString != NULL) {
      if (!HiiSetBrowserData (&gSetupVariableGuid, L"Setup", VarSize, (UINT8 *) SetupData, RequestString)) {
        Status = EFI_NOT_FOUND;
      }
      ASSERT_EFI_ERROR (Status);
      FreePool (RequestString);
    }
  }
  FreePool (SetupData);

  return Status;
}

EFI_STATUS
EFIAPI
UpdateVmdInfo (
  EFI_HII_HANDLE HiiHandle
  )
{
  EFI_STRING_ID   StrRef;
  VMD_INFO_HOB    *VmdInfoHob;
  int             i;

  DEBUG ((EFI_D_INFO, "UpdateVmdSetupInfo()\n"));

  VmdInfoHob = (VMD_INFO_HOB *) GetFirstGuidHob (&gVmdInfoHobGuid);
  if (VmdInfoHob == NULL) {
    DEBUG ((EFI_D_INFO, "Vmd Info Hob not found\n"));
    return EFI_NOT_FOUND;
  }

  for (i = 0; i < VMD_MAX_DEVICES; ++i) {
    switch(i) {
      case 0:
        StrRef = STRING_TOKEN (STR_RPA_BDF_VALUE);
        break;
      case 1:
        StrRef = STRING_TOKEN (STR_RPB_BDF_VALUE);
        break;
      case 2:
        StrRef = STRING_TOKEN (STR_RPC_BDF_VALUE);
        break;
      case 3:
        StrRef = STRING_TOKEN (STR_RPD_BDF_VALUE);
        break;
      default:
        StrRef = STRING_TOKEN (STR_RPA_BDF_VALUE);
    }
    if (VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev == SataDevNumber (0)) {
      InitString (
        HiiHandle,
        StrRef,
        L"%s", L"SATA Controller"
        );
    } else {
    InitString (
      HiiHandle,
      StrRef,
      L"%d/%d/%d",
      0,
      VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev,
      VmdInfoHob->VmdPortInfo.PortInfo[i].RpFunc
      );
    }
  }
  return EFI_SUCCESS;
}
