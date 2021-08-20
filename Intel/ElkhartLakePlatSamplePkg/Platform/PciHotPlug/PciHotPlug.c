/** @file
  Pci Hotplug Driver : This file will perform specific PCI-EXPRESS
  Devics resource configuration.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2019 Intel Corporation.

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

//
// Statements that include other files
//
#include "PciHotPlug.h"
#include "PciHotPlugHelpers.h"

#include <Protocol/ITbtPolicy.h>
#include <Protocol/DxeDTbtPolicy.h>

#include <Library/PchPcieRpLib.h>
#include <Library/TbtCommonLib.h>
#include <SaCommonDefinitions.h>
#include <PchPcieRpInfo.h>
#include <Library/ItbtPcieRpLib.h>
#include <SaDataHob.h>

#define DTBT_CONTROLLER                   0x00
#define ITBT_CONTROLLER                   0x80
#define INVALID_RP_CONTROLLER_TYPE        0xFF

#define PCIE_NUM  (24)

#define PEG_NUM   (4)

#define PADDING_BUS (1)
#define PADDING_NONPREFETCH_MEM (1)
#define PADDING_PREFETCH_MEM (1)
#define PADDING_IO (1)
#define PADDING_NUM (PADDING_BUS + PADDING_NONPREFETCH_MEM + PADDING_PREFETCH_MEM + PADDING_IO)

GLOBAL_REMOVE_IF_UNREFERENCED EFI_HPC_LOCATION          mPcieLocation[PCIE_NUM + PEG_NUM + MAX_ITBT_PCIE_PORT];
GLOBAL_REMOVE_IF_UNREFERENCED P2PB_RESOURCE_RECORD      mP2pbResourceRecord[MAX_P2PB_OF_TBT_DAISY_CHAIN];
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                     mP2pbResourceRecordCount = 0;
// Record the number of HotPlug capability Bridge on the same Bus.
GLOBAL_REMOVE_IF_UNREFERENCED NUMBER_OF_HOTPLUG_BRIDGE  mNumOfHotPlugBridge[MAX_P2PB_OF_TBT_DAISY_CHAIN];

GLOBAL_REMOVE_IF_UNREFERENCED UINTN mHpcCount = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN gItbtSegment = 0;

GLOBAL_REMOVE_IF_UNREFERENCED PCIE_HOT_PLUG_DEVICE_PATH mHotplugPcieDevicePathTemplate = {
  ACPI,
  PCI(0xFF, 0xFF), // Dummy Device no & Function no
  END
};

/**
  Entry point for the driver.

  This routine reads the PlatformType GPI on FWH and produces a protocol
  to be consumed by the chipset driver to effect those settings.

  @param[in]  ImageHandle    An image handle.
  @param[in]  SystemTable    A pointer to the system table.

  @retval     EFI_SUCCESS.
**/
EFI_STATUS
EFIAPI
PciHotPlug (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS                       Status;
  PCI_HOT_PLUG_INSTANCE            *PciHotPlug;
  UINTN                            Index;
  UINTN                            RpDev;
  UINTN                            RpFunc;
  PCIE_HOT_PLUG_DEVICE_PATH        *HotplugPcieDevicePath;
  UINTN                            VariableSize;
  PCH_SETUP                        PchSetup;
  ZeroMem (mP2pbResourceRecord, sizeof (mP2pbResourceRecord));
  ZeroMem (mNumOfHotPlugBridge, sizeof (mNumOfHotPlugBridge));

  VariableSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &PchSetup
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // PCH Rootports Hotplug device path creation
  //
  for (Index = 0; Index < PCIE_NUM; Index++) {
    if (PchSetup.PcieRootPortHPE[Index]) { // Check the Rootport no's hotplug is set
      Status = GetPchPcieRpDevFun (Index, &RpDev, &RpFunc); // Get the actual device/function no corresponding to the Rootport no provided
      ASSERT_EFI_ERROR (Status);

      HotplugPcieDevicePath = NULL;
      HotplugPcieDevicePath = AllocatePool (sizeof (PCIE_HOT_PLUG_DEVICE_PATH));
      ASSERT (HotplugPcieDevicePath != NULL);
      if (HotplugPcieDevicePath == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }
      CopyMem (HotplugPcieDevicePath, &mHotplugPcieDevicePathTemplate, sizeof (PCIE_HOT_PLUG_DEVICE_PATH));
      HotplugPcieDevicePath->PciRootPortNode.Device = (UINT8) RpDev; // Update real Device no
      HotplugPcieDevicePath->PciRootPortNode.Function = (UINT8) RpFunc; // Update real Function no

      mPcieLocation[mHpcCount].HpcDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)HotplugPcieDevicePath;
      mPcieLocation[mHpcCount].HpbDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)HotplugPcieDevicePath;
      mHpcCount++;

      DEBUG ((DEBUG_INFO, "(%02d) PciHotPlug (PCH RP#) : Bus 0x00, Device 0x%x, Function 0x%x is added to the Hotplug Device Path list \n", mHpcCount, RpDev, RpFunc));
    }
  }
  PciHotPlug = AllocatePool (sizeof (PCI_HOT_PLUG_INSTANCE));
  ASSERT (PciHotPlug != NULL);
  if (PciHotPlug == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Initialize driver private data.
  //
  ZeroMem (PciHotPlug, sizeof (PCI_HOT_PLUG_INSTANCE));

  PciHotPlug->Signature                               = PCI_HOT_PLUG_DRIVER_PRIVATE_SIGNATURE;
  PciHotPlug->HotPlugInitProtocol.GetRootHpcList      = GetRootHpcList;
  PciHotPlug->HotPlugInitProtocol.InitializeRootHpc   = InitializeRootHpc;
  PciHotPlug->HotPlugInitProtocol.GetResourcePadding  = GetResourcePadding;

  Status = gBS->InstallProtocolInterface (
                  &PciHotPlug->Handle,
                  &gEfiPciHotPlugInitProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &PciHotPlug->HotPlugInitProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  This procedure returns a list of Root Hot Plug controllers that require
  initialization during boot process

  @param[in]  This      The pointer to the instance of the EFI_PCI_HOT_PLUG_INIT protocol.
  @param[out] HpcCount  The number of Root HPCs returned.
  @param[out] HpcList   The list of Root HPCs. HpcCount defines the number of elements in this list.

  @retval EFI_SUCCESS.
**/
EFI_STATUS
EFIAPI
GetRootHpcList (
  IN EFI_PCI_HOT_PLUG_INIT_PROTOCOL    *This,
  OUT UINTN                            *HpcCount,
  OUT EFI_HPC_LOCATION                 **HpcList
  )
{
  *HpcCount = mHpcCount;
  *HpcList  = mPcieLocation;

  return EFI_SUCCESS;
}

/**
  This procedure Initializes one Root Hot Plug Controller
  This process may casue initialization of its subordinate buses

  @param[in]  This            The pointer to the instance of the EFI_PCI_HOT_PLUG_INIT protocol.
  @param[in]  HpcDevicePath   The Device Path to the HPC that is being initialized.
  @param[in]  HpcPciAddress   The address of the Hot Plug Controller function on the PCI bus.
  @param[in]  Event           The event that should be signaled when the Hot Plug Controller initialization is complete. Set to NULL if the caller wants to wait until the entire initialization process is complete. The event must be of the type EFI_EVT_SIGNAL.
  @param[out] HpcState        The state of the Hot Plug Controller hardware. The type EFI_Hpc_STATE is defined in section 3.1.

  @retval   EFI_SUCCESS.
**/
EFI_STATUS
EFIAPI
InitializeRootHpc (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL      *This,
  IN  EFI_DEVICE_PATH_PROTOCOL            *HpcDevicePath,
  IN  UINT64                              HpcPciAddress,
  IN  EFI_EVENT                           Event, OPTIONAL
  OUT EFI_HPC_STATE                       *HpcState
  )
{
  if (Event) {
    gBS->SignalEvent (Event);
  }

  *HpcState = EFI_HPC_STATE_INITIALIZED;

  return EFI_SUCCESS;
}

/**
  Selects the proper TBT Root port to assign resources
  based on the user input value

  @param[in]  SetupData          Pointer to Setup data

  @retval     TbtSelectorChosen  Rootport number.
**/
UINT8
GetRootporttoSetResourcesforTbt (
  IN SETUP_DATA *SetupData,
  IN UINTN    RpIndex,
  IN UINT8    TbtType
  )
{
  UINT8                    TbtSelectorChosen;
  UINT8                    Index;
  UINT8                    Rootportselected;
  DTBT_INFO_HOB            *DTbtInfoHob;

  TbtSelectorChosen = 0xFF;
  Rootportselected = 0;

  //
  // Get TBT INFO HOB
  //
  DTbtInfoHob = NULL;
  Rootportselected = 0;
  DTbtInfoHob = (DTBT_INFO_HOB *) GetFirstGuidHob (&gDTbtInfoHobGuid);

  if ((TbtType == (DTBT_CONTROLLER + TYPE_PCH)) || (TbtType == (DTBT_CONTROLLER + TYPE_PEG))) {
    if (DTbtInfoHob == NULL) {
      DEBUG ((DEBUG_INFO, "DTbtInfoHob not found\n"));
      return 0xFF;
    }
    for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
      if (DTbtInfoHob->DTbtControllerConfig[Index].DTbtControllerEn == 0x01) {
        //
        // Check if Root Index is for PCH PCIe or PEG
        //
        if (DTbtInfoHob->DTbtControllerConfig[Index].Type == TbtType) {
          //
          // Check if Controller is Enabled or not.
          if (SetupData->DTbtController[Index] == 0x01) {
            //
            // Get the Exact Root port number corresponding to the Controller Selected
            //
            Rootportselected = (DTbtInfoHob->DTbtControllerConfig[Index].PcieRpNumber - 1);
          }
          if (Rootportselected == (UINT8) RpIndex) {
            TbtSelectorChosen = Index;
            break;
          }
        } // Type
      }
    } // for loop
  } else if (TbtType == ITBT_CONTROLLER) {
    for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
      //
      // Check if Controller is set to AUTO and Enabled by default.
      //
      if (SetupData->ITbtRootPort[Index] == 0x01) {
        //
        // Get the Exact Root port number corresponding to the Controller Selected
        //
        Rootportselected = Index;
      }
      if (Rootportselected == (UINT8) RpIndex) {
        TbtSelectorChosen = Index;
        break;
      }
    } // for loop
  }

  DEBUG ((DEBUG_INFO, "TbtSelectorChosen = %x\n", TbtSelectorChosen));

  return (TbtSelectorChosen);
}

/**
  Update P2P Bridge Resource Record

  @param[in] *HpcDevicePath       The Device Path to the HPC that is being initialized.
  @param[in] HpcPciAddress        The address of the Hot Plug Controller function on the PCI bus.
  @param[in] RsvdExtraBusNum      Reserved Bus resource Number.
  @param[in] RsvdPcieMegaMem      Reserved Alignment of MEM resource.
  @param[in] PcieMemAddrRngMax    Alignment of MEM resource.
  @param[in] RsvdPciePMegaMem     Reserved Pcie Kilo Io Number.
  @param[in] PciePMemAddrRngMax   Alignment of PMEM resource.
  @param[in] RsvdPcieKiloIo       Reserved Pcie Kilo Io Number.

  @retval    EFI_SUCCESS.
**/
EFI_STATUS
UpdateP2pbResourceRecord (
  IN     EFI_DEVICE_PATH_PROTOCOL        *HpcDevicePath,
  IN     UINT64                          HpcPciAddress,
  IN     UINT8                           RsvdExtraBusNum,
  IN     UINT16                          RsvdPcieMegaMem,
  IN     UINT8                           PcieMemAddrRngMax,
  IN     UINT16                          RsvdPciePMegaMem,
  IN     UINT8                           PciePMemAddrRngMax,
  IN     UINT8                           RsvdPcieKiloIo
  )
{
  UINT16 Index;

  for (Index = 0; Index < MAX_P2PB_OF_TBT_DAISY_CHAIN; Index++) {
    if (mP2pbResourceRecord[Index].HpcPciAddress == 0) {
      continue;
    }
    if (mP2pbResourceRecord[Index].HpcPciAddress == HpcPciAddress) {
      //
      // Record already existed, so ignore it.
      //
      return EFI_ABORTED;
    }
  }
  //
  // Record the current HPC's resource assignment
  //
  mP2pbResourceRecord[mP2pbResourceRecordCount].HpcDevicePath = HpcDevicePath;
  mP2pbResourceRecord[mP2pbResourceRecordCount].HpcPciAddress = HpcPciAddress;
  mP2pbResourceRecord[mP2pbResourceRecordCount].RsvdExtraBusNum = RsvdExtraBusNum;
  mP2pbResourceRecord[mP2pbResourceRecordCount].RsvdPcieMegaMem = RsvdPcieMegaMem;
  mP2pbResourceRecord[mP2pbResourceRecordCount].PcieMemAddrRngMax = PcieMemAddrRngMax;
  mP2pbResourceRecord[mP2pbResourceRecordCount].RsvdPciePMegaMem = RsvdPciePMegaMem;
  mP2pbResourceRecord[mP2pbResourceRecordCount].PciePMemAddrRngMax = PciePMemAddrRngMax;
  mP2pbResourceRecord[mP2pbResourceRecordCount].RsvdPcieKiloIo = RsvdPcieKiloIo;
  DEBUG ((DEBUG_INFO, "mP2pbResourceRecord[%x].HpcDevicePath = %s \n", mP2pbResourceRecordCount, ConvertDevicePathToText (mP2pbResourceRecord[mP2pbResourceRecordCount].HpcDevicePath, TRUE, TRUE)));
  DEBUG ((DEBUG_INFO, "mP2pbResourceRecord[%x].HpcPciAddress = %lx \n", mP2pbResourceRecordCount, mP2pbResourceRecord[mP2pbResourceRecordCount].HpcPciAddress));
  DEBUG ((DEBUG_INFO, "mP2pbResourceRecord[%x].RsvdExtraBusNum = %x \n", mP2pbResourceRecordCount, mP2pbResourceRecord[mP2pbResourceRecordCount].RsvdExtraBusNum));
  DEBUG ((DEBUG_INFO, "mP2pbResourceRecord[%x].RsvdPcieMegaMem = %x \n", mP2pbResourceRecordCount, mP2pbResourceRecord[mP2pbResourceRecordCount].RsvdPcieMegaMem));
  DEBUG ((DEBUG_INFO, "mP2pbResourceRecord[%x].PcieMemAddrRngMax = %x \n", mP2pbResourceRecordCount, mP2pbResourceRecord[mP2pbResourceRecordCount].PcieMemAddrRngMax));
  DEBUG ((DEBUG_INFO, "mP2pbResourceRecord[%x].RsvdPciePMegaMem = %x \n", mP2pbResourceRecordCount, mP2pbResourceRecord[mP2pbResourceRecordCount].RsvdPciePMegaMem));
  DEBUG ((DEBUG_INFO, "mP2pbResourceRecord[%x].PciePMemAddrRngMax = %x \n", mP2pbResourceRecordCount, mP2pbResourceRecord[mP2pbResourceRecordCount].PciePMemAddrRngMax));
  DEBUG ((DEBUG_INFO, "mP2pbResourceRecord[%x].RsvdPcieKiloIo = %x \n", mP2pbResourceRecordCount, mP2pbResourceRecord[mP2pbResourceRecordCount].RsvdPcieKiloIo));

  return EFI_SUCCESS;
}

/**
  Handle the Resource Padding For RootPort

  @param[in] *HpcDevicePath       The Device Path to the HPC that is being initialized.
  @param[in] HpcPciAddress        The address of the Hot Plug Controller function on the PCI bus.
  @param[in] RsvdExtraBusNum      Reserved Bus resource Number.
  @param[in] RsvdPcieMegaMem      Reserved Alignment of MEM resource.
  @param[in] PcieMemAddrRngMax    Alignment of MEM resource.
  @param[in] RsvdPciePMegaMem     Reserved Pcie Kilo Io Number.
  @param[in] PciePMemAddrRngMax   Alignment of PMEM resource.
  @param[in] RsvdPcieKiloIo       Reserved Pcie Kilo Io Number.

**/
VOID
HandleResourcePaddingForRootPort (
  IN     EFI_DEVICE_PATH_PROTOCOL        *HpcDevicePath,
  IN     UINT64                          HpcPciAddress,
  OUT    UINT8                           *RsvdExtraBusNum,
  OUT    UINT16                          *RsvdPcieMegaMem,
  OUT    UINT8                           *PcieMemAddrRngMax,
  OUT    UINT16                          *RsvdPciePMegaMem,
  OUT    UINT8                           *PciePMemAddrRngMax,
  OUT    UINT8                           *RsvdPcieKiloIo
  )
{
  EFI_STATUS                        Status;
  UINTN                             RpIndex;
  UINTN                             VariableSize;
  EFI_STATUS                        Status3;
  PCH_SETUP                         PchSetup;
  UINTN                             RpBus;
  UINTN                             RpDev;
  UINTN                             RpFunc;

  RpIndex = 0;
  RpBus   = (UINTN) ((HpcPciAddress >> 24) & 0xFF);
  RpDev   = (UINTN) ((HpcPciAddress >> 16) & 0xFF);
  RpFunc  = (UINTN) ((HpcPciAddress >> 8) & 0xFF);

  VariableSize = sizeof (PCH_SETUP);
  Status3 = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &PchSetup
                  );
    if((RpDev == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1) || (RpDev == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2) || (RpDev == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3)) {
    // PCH
    Status = GetPchPcieRpNumber (RpDev, RpFunc, &RpIndex);
    DEBUG ((DEBUG_INFO, "GetResourcePadding : PCH Rootport no %02d Bus 0x%x, Device 0x%x, Function 0x%x \n", RpIndex, RpBus, RpDev, RpFunc));
  } else {
    // Non-Rootport
    DEBUG ((DEBUG_INFO, "GetResourcePadding : Non-Rootport no %02d Bus 0x%x, Device 0x%x, Function 0x%x \n", RpIndex, RpBus, RpDev, RpFunc));
  }
      if((RpBus == 0) && ((RpDev == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1) || (RpDev == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2) || (RpDev == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3))){
      if (!EFI_ERROR(Status3)) {
        // PCH
        *RsvdExtraBusNum = PchSetup.PcieExtraBusRsvd[RpIndex];
        *RsvdPcieMegaMem = PchSetup.PcieMemRsvd[RpIndex];
        *RsvdPcieKiloIo  = PchSetup.PcieIoRsvd[RpIndex];
      }
    }
}

/**
  Handle the Resource Padding For Non-RootPort

  @param[in] *HpcDevicePath       The Device Path to the HPC that is being initialized.
  @param[in] HpcPciAddress        The address of the Hot Plug Controller function on the PCI bus.
  @param[in] RsvdExtraBusNum      Reserved Bus resource Number.
  @param[in] RsvdPcieMegaMem      Reserved Alignment of MEM resource.
  @param[in] PcieMemAddrRngMax    Alignment of MEM resource.
  @param[in] RsvdPciePMegaMem     Reserved Pcie Kilo Io Number.
  @param[in] PciePMemAddrRngMax   Alignment of PMEM resource.
  @param[in] RsvdPcieKiloIo       Reserved Pcie Kilo Io Number.

**/
VOID
HandleResourcePaddingForNonRootPort (
  IN  EFI_DEVICE_PATH_PROTOCOL        *HpcDevicePath,
  IN  UINT64                          HpcPciAddress,
  OUT UINT8                           *RsvdExtraBusNum,
  OUT UINT16                          *RsvdPcieMegaMem,
  OUT UINT8                           *PcieMemAddrRngMax,
  OUT UINT16                          *RsvdPciePMegaMem,
  OUT UINT8                           *PciePMemAddrRngMax,
  OUT UINT8                           *RsvdPcieKiloIo
  )
{
  UINT8       RpSeg;
  UINTN       RpBus;
  UINTN       RpDev;
  UINTN       RpFunc;
  UINT64      ParentPciAddress;
  EFI_STATUS  Status;
  UINT8       Index;

  RpSeg  = (UINT8) ((HpcPciAddress >> 32) & 0x01);
  RpBus  = (UINTN) ((HpcPciAddress >> 24) & 0xFF);
  RpDev  = (UINTN) ((HpcPciAddress >> 16) & 0xFF);
  RpFunc = (UINTN) ((HpcPciAddress >> 8) & 0xFF);

  // Non-Rootport
  DEBUG ((DEBUG_INFO, "GetResourcePadding : Non-Rootport Seg 0x%x, Bus 0x%x, Device 0x%x, Function 0x%x \n", RpSeg, RpBus, RpDev, RpFunc));

  *RsvdPcieKiloIo  = 0;

  ParentPciAddress = GetParentPciAddress (RpSeg, RpBus);

  GetParentResourceSize (ParentPciAddress, RsvdExtraBusNum, RsvdPcieMegaMem, RsvdPciePMegaMem, RsvdPcieKiloIo);
  DEBUG ((DEBUG_INFO, "Parent's resource as below \n"));
  DEBUG ((DEBUG_INFO, "BusNum = %x \n", *RsvdExtraBusNum));
  DEBUG ((DEBUG_INFO, "PcieMegaMem = %x \n", *RsvdPcieMegaMem));
  DEBUG ((DEBUG_INFO, "PciePMegaMem = %x \n", *RsvdPciePMegaMem));
  DEBUG ((DEBUG_INFO, "PcieKiloIo = %x \n", *RsvdPcieKiloIo));

  Index = 0;
  Status = GetCurrentBusP2pbHotPlug(RpSeg, (UINT8)RpBus, &Index);
  if (Status == EFI_SUCCESS) {
    *RsvdExtraBusNum = (*RsvdExtraBusNum - mNumOfHotPlugBridge[Index].NumOfP2pbNonHotPlug)/mNumOfHotPlugBridge[Index].NumOfP2pbHotPlug;
    *RsvdPcieMegaMem = (*RsvdPcieMegaMem - mNumOfHotPlugBridge[Index].NumOfP2pbNonHotPlug)/mNumOfHotPlugBridge[Index].NumOfP2pbHotPlug;
    *RsvdPciePMegaMem = (*RsvdPciePMegaMem)/mNumOfHotPlugBridge[Index].NumOfP2pbHotPlug;
    *RsvdPcieKiloIo = (*RsvdPcieKiloIo)/mNumOfHotPlugBridge[Index].NumOfP2pbHotPlug;
    DEBUG ((DEBUG_INFO, "Current resource as below \n"));
    DEBUG ((DEBUG_INFO, "BusNum = %x \n", *RsvdExtraBusNum));
    DEBUG ((DEBUG_INFO, "PcieMegaMem = %x \n", *RsvdPcieMegaMem));
    DEBUG ((DEBUG_INFO, "PciePMegaMem = %x \n", *RsvdPciePMegaMem));
    DEBUG ((DEBUG_INFO, "PcieKiloIo = %x \n", *RsvdPcieKiloIo));
  } else {
    DEBUG ((DEBUG_INFO, "GetCurrentBusP2pbHotPlug Stauts =%r\n", Status));
  }
}

/**
  Returns the resource padding required by the PCI bus that is controlled by the specified Hot Plug Controller.

  @param[in]  This           The pointer to the instance of the EFI_PCI_HOT_PLUG_INIT protocol. initialized.
  @param[in]  HpcDevicePath  The Device Path to the Hot Plug Controller.
  @param[in]  HpcPciAddress  The address of the Hot Plug Controller function on the PCI bus.
  @param[out] HpcState       The state of the Hot Plug Controller hardware. The type EFI_HPC_STATE is defined in section 3.1.
  @param[out] Padding        This is the amount of resource padding required by the PCI bus under the control of the specified Hpc. Since the caller does not know the size of this buffer, this buffer is allocated by the callee and freed by the caller.
  @param[out] Attribute      Describes how padding is accounted for.

  @retval     EFI_SUCCESS.
**/
EFI_STATUS
EFIAPI
GetResourcePadding (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL  *This,
  IN  EFI_DEVICE_PATH_PROTOCOL        *HpcDevicePath,
  IN  UINT64                          HpcPciAddress,
  OUT EFI_HPC_STATE                   *HpcState,
  OUT VOID                            **Padding,
  OUT EFI_HPC_PADDING_ATTRIBUTES      *Attributes
  )
{
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *PaddingResource;
  EFI_STATUS                        Status;
  UINT8                             RsvdExtraBusNum = 0;
  UINT16                            RsvdPcieMegaMem = 10;
  UINT8                             PcieMemAddrRngMax = 1;
  UINT16                            RsvdPciePMegaMem = 10;
  UINT8                             PciePMemAddrRngMax = 1;
  UINT8                             RsvdPcieKiloIo = 4;
  UINTN                             RpBus;
  CHAR16                            *DevicePathStr;
  SA_DATA_HOB                      *SaDataHob;

  PaddingResource = AllocatePool (PADDING_NUM * sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR));
  ASSERT (PaddingResource != NULL);
  if (PaddingResource == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  *Padding = (VOID *) PaddingResource;

  // Record the segment number in Bit[32] of HpcPciAddress.
  DevicePathStr = ConvertDevicePathToText (HpcDevicePath, TRUE, TRUE);
  if (DevicePathStr != NULL) {
    if (StrnCmp (DevicePathStr, PCI_ROOT_0_STRING, StrLen (PCI_ROOT_0_STRING)) == 0) {
      DEBUG ((DEBUG_INFO, "Segment0 \n"));
      HpcPciAddress &= ~BIT32;
    } else if (StrnCmp (DevicePathStr, PCI_ROOT_1_STRING, StrLen (PCI_ROOT_1_STRING)) == 0) {
      DEBUG ((DEBUG_INFO, "Segment1 \n"));
      HpcPciAddress |= BIT32;
    }
  } else {
      return EFI_OUT_OF_RESOURCES;
  }

  RpBus  = (UINTN) ((HpcPciAddress >> 24) & 0xFF);

  if (RpBus == 0x00) {
    //
    // Handle the GetResourcePadding for RootPort
    //
    HandleResourcePaddingForRootPort (
      HpcDevicePath,
      HpcPciAddress,
      &RsvdExtraBusNum,
      &RsvdPcieMegaMem,
      &PcieMemAddrRngMax,
      &RsvdPciePMegaMem,
      &PciePMemAddrRngMax,
      &RsvdPcieKiloIo
    );
  } else {
    //
    // Handle the GetResourcePadding for Non-RootPort
    //
    HandleResourcePaddingForNonRootPort (
      HpcDevicePath,
      HpcPciAddress,
      &RsvdExtraBusNum,
      &RsvdPcieMegaMem,
      &PcieMemAddrRngMax,
      &RsvdPciePMegaMem,
      &PciePMemAddrRngMax,
      &RsvdPcieKiloIo
    );
  }

  Status = UpdateP2pbResourceRecord (
    HpcDevicePath,
    HpcPciAddress,
    RsvdExtraBusNum,
    RsvdPcieMegaMem,
    PcieMemAddrRngMax,
    RsvdPciePMegaMem,
    PciePMemAddrRngMax,
    RsvdPcieKiloIo
    );
  if (Status == EFI_SUCCESS) {
    mP2pbResourceRecordCount ++;
  }

  //
  // Padding for bus
  //
  ZeroMem (PaddingResource, PADDING_NUM * sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) + sizeof (EFI_ACPI_END_TAG_DESCRIPTOR));
  *Attributes                   = EfiPaddingPciBus;

  PaddingResource->Desc         = 0x8A;
  PaddingResource->Len          = 0x2B;
  PaddingResource->ResType      = ACPI_ADDRESS_SPACE_TYPE_BUS;
  PaddingResource->GenFlag      = 0x0;
  PaddingResource->SpecificFlag = 0;
  PaddingResource->AddrRangeMin = 0;
  PaddingResource->AddrRangeMax = 0;
  PaddingResource->AddrLen      = RsvdExtraBusNum;

  //
  // Padding for non-prefetchable memory
  //
  PaddingResource++;
  PaddingResource->Desc                 = 0x8A;
  PaddingResource->Len                  = 0x2B;
  PaddingResource->ResType              = ACPI_ADDRESS_SPACE_TYPE_MEM;
  PaddingResource->GenFlag              = 0x0;

  SaDataHob = NULL;
  SaDataHob = (SA_DATA_HOB *) GetFirstGuidHob (&gSaDataHobGuid);

  if ((SaDataHob != NULL) && (SaDataHob->EnableAbove4GBMmio == 1)) {
    PaddingResource->AddrSpaceGranularity = 64;
  } else {
    PaddingResource->AddrSpaceGranularity = 32;
  }
  PaddingResource->SpecificFlag         = 0;
  //
  // Pad non-prefetchable
  //
  PaddingResource->AddrRangeMin = 0;
  PaddingResource->AddrLen      = RsvdPcieMegaMem * 0x100000;
  PaddingResource->AddrRangeMax = (1 << PcieMemAddrRngMax) - 1;

  //
  // Padding for prefetchable memory
  //
  PaddingResource++;
  PaddingResource->Desc                 = 0x8A;
  PaddingResource->Len                  = 0x2B;
  PaddingResource->ResType              = ACPI_ADDRESS_SPACE_TYPE_MEM;
  PaddingResource->GenFlag              = 0x0;
  if ((SaDataHob != NULL) && (SaDataHob->EnableAbove4GBMmio == 1)) {
    PaddingResource->AddrSpaceGranularity = 64;
  } else {
    PaddingResource->AddrSpaceGranularity = 32;
  }
  PaddingResource->SpecificFlag         = 06;
  //
  // Padding for prefetchable memory
  //
  PaddingResource->AddrRangeMin = 0;
  PaddingResource->AddrLen      = (UINT64) RsvdPciePMegaMem * 0x100000;
  //
  // Pad 16 MB of MEM
  //
  PaddingResource->AddrRangeMax = (1 << PciePMemAddrRngMax) - 1;

  //
  // Alignment
  //
  // Padding for I/O
  //
  PaddingResource++;
  PaddingResource->Desc         = 0x8A;
  PaddingResource->Len          = 0x2B;
  PaddingResource->ResType      = ACPI_ADDRESS_SPACE_TYPE_IO;
  PaddingResource->GenFlag      = 0x0;
  PaddingResource->SpecificFlag = 0;
  PaddingResource->AddrRangeMin = 0;
  PaddingResource->AddrLen      = RsvdPcieKiloIo * 0x400;
  //
  // Pad 4K of IO
  //
  PaddingResource->AddrRangeMax = 1;
  //
  // Alignment
  //
  // Terminate the entries.
  //
  PaddingResource++;
  ((EFI_ACPI_END_TAG_DESCRIPTOR *) PaddingResource)->Desc     = ACPI_END_TAG_DESCRIPTOR;
  ((EFI_ACPI_END_TAG_DESCRIPTOR *) PaddingResource)->Checksum = 0x0;

  *HpcState = EFI_HPC_STATE_INITIALIZED | EFI_HPC_STATE_ENABLED;

  return EFI_SUCCESS;
}
