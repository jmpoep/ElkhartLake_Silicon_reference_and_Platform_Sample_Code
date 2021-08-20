/** @file
  The PEI VMD Init Library in SA init

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

#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PciSegmentLib.h>
#include <Uefi/UefiBaseType.h>
#include <PcieRegs.h>
#include <Library/PchPcieRpLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PostCodeLib.h>
#include <SaCommonDefinitions.h>
#include <Library/PeiVmdInitLib.h>
#include <Register/SaRegsHostBridge.h>
#include <Register/CpuPcieRegs.h>
#include <Library/PchInfoLib.h>
#include <Register/PchRegs.h>
#include <VmdInfoHob.h>
#include <Register/SataRegs.h>
#include <Register/VmdRegs.h>
#include <Library/SataLib.h>
#include <CpuPcieInfo.h>
#include <CpuSbInfo.h>

/**
  This function detects the mass storage devices attached to Peg60 and PCH Pcie Root ports and the Sata controller.
  @param[in]  *VmdInfoHob     pointer to VMD info Hob to store the information of detected devices.
  @retval     EFI_SUCCESS     Successfully initialized Pre-Mem configurations.
**/
EFI_STATUS
VmdDetectPcieStorageDevices (
  VMD_INFO_HOB          *VmdInfoHob
);


/**
  This function performs basic initialization for VMD in PEI phase (post-mem)
  @param VMD_PEI_PREMEM_CONFIG - Pointer to config data
  @retval     EFI_SUCCESS     Successfully initialized VMD
**/
EFI_STATUS
VmdInit (
  IN   VMD_PEI_CONFIG  *VmdPeiConfig
  )
{
  CFGBARSZ_VMD_STRUCT        VmdCfgBarSz;
  MEMBAR1SZ_VMD_STRUCT       VmdMemBar1Sz;
  MEMBAR2SZ_VMD_STRUCT       VmdMemBar2Sz;
  VMASSIGN_VMD_STRUCT        VmAssign;
  CFGBAR_N0_VMD_STRUCT       CfgBar;
  MEMBAR1_N0_VMD_STRUCT      MemBar1;
  MEMBAR2_N0_VMD_STRUCT      MemBar2;
  VMCONFIG_VMD_STRUCT        VmConfig;
  VMCAP_VMD_STRUCT           VmCap;

  FN0_ASSIGN_VMD_STRUCT      Fn0Assign;
  FN1_ASSIGN_VMD_STRUCT      Fn1Assign;
  FN2_ASSIGN_VMD_STRUCT      Fn2Assign;
  FN3_ASSIGN_VMD_STRUCT      Fn3Assign;
  FN4_ASSIGN_VMD_STRUCT      Fn4Assign;
  FN5_ASSIGN_VMD_STRUCT      Fn5Assign;
  FN6_ASSIGN_VMD_STRUCT      Fn6Assign;
  FN7_ASSIGN_VMD_STRUCT      Fn7Assign;

  UINT32                     DeviceBaseAddress;
  UINT8                      Attr;
  VMD_INFO_HOB               *VmdInfoHob;
  UINT8                      i;
  UINT16                     DidAssign;
  UINT32                     Data32;
  EFI_STATUS                 Status;

  //
  // VMD Initializations if the VMD IP is Supported
  // Read CAPID0_B Bit2 VMD_DIS to make sure VMD exists.
  //
  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  DEBUG ((DEBUG_INFO, "CAPID0_B value is 0x%x\n", Data32));
  if (Data32 & V_SA_MC_CAPID0_B_VMD_DIS) {
    DEBUG ((DEBUG_INFO, "------- Vmd is not supported -----\n"));
    return EFI_UNSUPPORTED;
  }
  DEBUG ((DEBUG_INFO, "-----------------VmdInit Start ----------------\n"));

  //
  // Create HOB for VMD INFO
  //
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (VMD_INFO_HOB),
             (VOID **) &VmdInfoHob
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Initialize default HOB data
  //
  VmdInfoHob->EfiHobGuidType.Name = gVmdInfoHobGuid;
  DEBUG ((DEBUG_INFO, "VmdInfoHob->EfiHobGuidType.Name: %g\n", &VmdInfoHob->EfiHobGuidType.Name));
  ZeroMem (&(VmdInfoHob->VmdPortInfo), sizeof (VMD_PORT_INFO));

  DEBUG ((DEBUG_INFO, "VmdInfoHob @ %X\n", VmdInfoHob));
  DEBUG ((DEBUG_INFO, "&(VmdInfoHob->VmdPortInfo) @ %X\n", &(VmdInfoHob->VmdPortInfo)));
  DEBUG ((DEBUG_INFO, "VmdHobSize - HobHeaderSize: %X\n", sizeof (VMD_INFO_HOB) - sizeof (EFI_HOB_GUID_TYPE)));
  DEBUG ((DEBUG_INFO, "VmdInfoSize: %X\n", sizeof (VMD_PORT_INFO)));

  //
  // Get the HOB for VMD INFO
  //
  VmdInfoHob = (VMD_INFO_HOB *) GetFirstGuidHob (&gVmdInfoHobGuid);
  if (VmdInfoHob == NULL) {
    DEBUG ((EFI_D_INFO, "Vmd Info Hob not found\n"));
    return EFI_NOT_FOUND;
  }

  //
  // Detect the mass storage devices/controller connected to CPU and PCH root ports
  //
  VmdDetectPcieStorageDevices (VmdInfoHob);

  DEBUG ((DEBUG_INFO, "Dumping port info\n"));
  for (i = 0; i < VMD_MAX_DEVICES; ++i) {
    DEBUG ((DEBUG_INFO, "RpDev  %d\t", VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev));
    DEBUG ((DEBUG_INFO, "RpFunc  %d\t", VmdInfoHob->VmdPortInfo.PortInfo[i].RpFunc));
    DEBUG ((DEBUG_INFO, "DevId  %d\n", VmdInfoHob->VmdPortInfo.PortInfo[i].DevId));
  }

  //
  // Initializations only if VMD is enabled
  //
  if (!VmdPeiConfig->VmdEnable) { // if VMD is not enabled by user
    //disable the devEnable bit for VMD device (bit 14) if its enabled
    if ((PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN))) & ((UINT32) (B_SA_DEVEN_D14F0EN_MASK))){
      PciSegmentAnd32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), (UINT32) ~(B_SA_DEVEN_D14F0EN_MASK));
    }
    DEBUG ((DEBUG_INFO, "\nVMD Device has been disabled\n"));
    return EFI_SUCCESS;
  }

  DEBUG((DEBUG_INFO, "VMD option is enabled in the setup \n"));
//  check the devEnable bit for VMD device (bit 14)
  if ((PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN))) & ((UINT32) (B_SA_DEVEN_D14F0EN_MASK))) {
    DEBUG((DEBUG_INFO, "VMD device is alreday enabled\n"));
  } else {
    DEBUG((DEBUG_INFO, "Enabling VMD device in DevEn \n"));
    PciSegmentOr32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), (UINT32) (B_SA_DEVEN_D14F0EN_MASK));
  }

  DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_VMD_DEV_NUM, SA_VMD_FUNC_NUM,0);

  //
  // Reset and then Configure FUN assign registers as per the policy / user selection of Dev and Func
  //
  Fn0Assign.Data = 0;
  PciSegmentWrite32 ( DeviceBaseAddress + R_FN0_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn0Assign.Data);
  Fn1Assign.Data = 0;
  PciSegmentWrite32 ( DeviceBaseAddress + R_FN1_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn1Assign.Data);
  Fn2Assign.Data = 0;
  PciSegmentWrite32 ( DeviceBaseAddress + R_FN2_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn2Assign.Data);
  Fn3Assign.Data = 0;
  PciSegmentWrite32 ( DeviceBaseAddress + R_FN3_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn3Assign.Data);
  Fn4Assign.Data = 0;
  PciSegmentWrite32 ( DeviceBaseAddress + R_FN4_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn4Assign.Data);
  Fn5Assign.Data = 0;
  PciSegmentWrite32 ( DeviceBaseAddress + R_FN5_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn5Assign.Data);
  Fn6Assign.Data = 0;
  PciSegmentWrite32 ( DeviceBaseAddress + R_FN6_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn6Assign.Data);
  Fn7Assign.Data = 0;
  PciSegmentWrite32 ( DeviceBaseAddress + R_FN7_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn7Assign.Data);

  for (i = 0; i < VMD_MAX_DEVICES; ++i) {

    if ((i == 0 && VmdPeiConfig->VmdPortAEnable) || (i == 1 && VmdPeiConfig->VmdPortBEnable) ||
      (i == 2 && VmdPeiConfig->VmdPortCEnable) || (i == 3 && VmdPeiConfig->VmdPortDEnable)) {

    switch(VmdInfoHob->VmdPortInfo.PortInfo[i].RpFunc) {
      case 0:
      Fn0Assign.Data |= 1 << VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev;
      PciSegmentWrite32 ( DeviceBaseAddress + R_FN0_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn0Assign.Data);
      break;
      case 1:
      Fn1Assign.Data |= 1 << VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev;
      PciSegmentWrite32 ( DeviceBaseAddress + R_FN1_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn1Assign.Data);
      break;
      case 2:
      Fn2Assign.Data |= 1 << VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev;
      PciSegmentWrite32 ( DeviceBaseAddress + R_FN2_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn2Assign.Data);
      break;
      case 3:
      Fn3Assign.Data |= 1 << VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev;
      PciSegmentWrite32 ( DeviceBaseAddress + R_FN3_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn3Assign.Data);
      break;
      case 4:
      Fn4Assign.Data |= 1 << VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev;
      PciSegmentWrite32 ( DeviceBaseAddress + R_FN4_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn4Assign.Data);
      break;
      case 5:
      Fn5Assign.Data |= 1 << VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev;
      PciSegmentWrite32 ( DeviceBaseAddress + R_FN5_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn5Assign.Data);
      break;
      case 6:
      Fn6Assign.Data |= 1 << VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev;
      PciSegmentWrite32 ( DeviceBaseAddress + R_FN6_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn6Assign.Data);
      break;
      case 7:
      Fn7Assign.Data |= 1 << VmdInfoHob->VmdPortInfo.PortInfo[i].RpDev;
      PciSegmentWrite32 ( DeviceBaseAddress + R_FN7_ASSIGN_0_14_0_PCI_VMD_REG_OFFSET, Fn7Assign.Data);
      break;
    }
    }
  }
  // program VMAssign only when need to assign device and all its function under VMD
  VmAssign.Data = PciSegmentRead32 (DeviceBaseAddress + R_VMASSIGN_0_14_0_PCI_VMD_REG_OFFSET);
  // Skip VMD configuration if Config space is not valid.
  if (VmAssign.Data == 0xFFFFFFFF) {
    DEBUG((DEBUG_INFO, "VMD %02d not present%d\n",VmAssign.Data));
    return EFI_UNSUPPORTED;
  }

  // program CfgBarSz
  VmdCfgBarSz.Data  = PciSegmentRead8 (DeviceBaseAddress + R_CFGBARSZ_0_14_0_PCI_VMD_REG_OFFSET);
  VmdCfgBarSz.Bits.Size = VmdPeiConfig->VmdCfgBarSz;
  PciSegmentWrite8 (DeviceBaseAddress + R_CFGBARSZ_0_14_0_PCI_VMD_REG_OFFSET,VmdCfgBarSz.Data);

  // program MemBarSz 1/2
  VmdMemBar1Sz.Data = PciSegmentRead8 (DeviceBaseAddress + R_MEMBAR1SZ_0_14_0_PCI_VMD_REG_OFFSET);
  VmdMemBar1Sz.Bits.Size = VmdPeiConfig->VmdMemBarSz1;
  PciSegmentWrite8 (DeviceBaseAddress + R_MEMBAR1SZ_0_14_0_PCI_VMD_REG_OFFSET,VmdMemBar1Sz.Data);

  VmdMemBar2Sz.Data = PciSegmentRead8 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,
  SA_MC_BUS, SA_VMD_DEV_NUM, SA_VMD_FUNC_NUM, R_MEMBAR2SZ_0_14_0_PCI_VMD_REG_OFFSET));
  VmdMemBar2Sz.Bits.Size = VmdPeiConfig->VmdMemBarSz2;
  PciSegmentWrite8 (DeviceBaseAddress + R_MEMBAR2SZ_0_14_0_PCI_VMD_REG_OFFSET,VmdMemBar2Sz.Data);

  DEBUG ((DEBUG_INFO, "VMD VMAssign:%02x CfgBarSz:%02d MemBar1Sz:%02d MemBar2Size:%02d\n",
  VmAssign.Data, VmdCfgBarSz.Data, VmdMemBar1Sz.Data, VmdMemBar2Sz.Data));

  DEBUG((DEBUG_INFO, "Fn0Assign.Data = 0x%x \n", Fn0Assign.Data));
  DEBUG((DEBUG_INFO, "Fn1Assign.Data = 0x%x \n", Fn1Assign.Data));
  DEBUG((DEBUG_INFO, "Fn2Assign.Data = 0x%x \n", Fn2Assign.Data));
  DEBUG((DEBUG_INFO, "Fn3Assign.Data = 0x%x \n", Fn3Assign.Data));
  DEBUG((DEBUG_INFO, "Fn4Assign.Data = 0x%x \n", Fn4Assign.Data));
  DEBUG((DEBUG_INFO, "Fn5Assign.Data = 0x%x \n", Fn5Assign.Data));
  DEBUG((DEBUG_INFO, "Fn6Assign.Data = 0x%x \n", Fn6Assign.Data));
  DEBUG((DEBUG_INFO, "Fn7Assign.Data = 0x%x \n", Fn7Assign.Data));

  // program CfgBar attribute
  CfgBar.Data = PciSegmentRead32 (DeviceBaseAddress + R_CFGBAR_N0_0_14_0_PCI_VMD_REG_OFFSET);
  Attr = VmdPeiConfig->VmdCfgBarAttr;
  switch(Attr) {
    case VMD_32BIT_NONPREFETCH:  //32-bit non-prefetchable
    CfgBar.Bits.Prefetchable = 0;
    CfgBar.Bits.Type = 0;
    break;
    case VMD_64BIT_NONPREFETCH: //64-bit non-prefetcheble
    CfgBar.Bits.Prefetchable = 0;
    CfgBar.Bits.Type = 2;
    break;
    case VMD_64BIT_PREFETCH:  //64-bit prefetchable
    CfgBar.Bits.Prefetchable = 1;
    CfgBar.Bits.Type = 2;
    break;
  }
  PciSegmentWrite32 (DeviceBaseAddress + R_CFGBAR_N0_0_14_0_PCI_VMD_REG_OFFSET, CfgBar.Data);

  // program MemBar1 attribute
  MemBar1.Data = PciSegmentRead32 (DeviceBaseAddress + R_MEMBAR1_N0_0_14_0_PCI_VMD_REG_OFFSET);
  Attr = VmdPeiConfig->VmdMemBar1Attr;
  switch(Attr) {
    case VMD_32BIT_NONPREFETCH:  //32-bit non-prefetchable
    MemBar1.Bits.Prefetchable = 0;
    MemBar1.Bits.Type = 0;
    break;
    case VMD_64BIT_NONPREFETCH: //64-bit non-prefetchable
    MemBar1.Bits.Prefetchable = 0;
    MemBar1.Bits.Type = 2;
    break;
    case VMD_64BIT_PREFETCH:  //64-bit prefetchable
    MemBar1.Bits.Prefetchable = 1;
    MemBar1.Bits.Type = 2;
    break;
  }
  PciSegmentWrite32 (DeviceBaseAddress + R_MEMBAR1_N0_0_14_0_PCI_VMD_REG_OFFSET, MemBar1.Data);

  // program MemBar2 attribute
  MemBar2.Data = PciSegmentRead32 (DeviceBaseAddress + R_MEMBAR2_N0_0_14_0_PCI_VMD_REG_OFFSET);
  Attr = VmdPeiConfig->VmdMemBar2Attr;
  switch(Attr) {
    case VMD_32BIT_NONPREFETCH:  //32-bit non-prefetchable
    MemBar2.Bits.Prefetchable = 0;
    MemBar2.Bits.Type = 0;
    break;
    case VMD_64BIT_NONPREFETCH: // 64-bit non-prefetchable
    MemBar2.Bits.Prefetchable = 0;
    MemBar2.Bits.Type = 2;
    break;
    case VMD_64BIT_PREFETCH:  //64-bit prefetchable
    MemBar2.Bits.Prefetchable = 1;
    MemBar2.Bits.Type = 2;
    break;
  }
  PciSegmentWrite32 (DeviceBaseAddress + R_MEMBAR2_N0_0_14_0_PCI_VMD_REG_OFFSET, MemBar2.Data);

  DEBUG((DEBUG_INFO, "VMD VmAssign:0x%02x CfgBar:0x%02x MemBar1:0x%02x MemBar2:0x%02x\n",
  VmAssign.Data, CfgBar.Data, MemBar1.Data, MemBar2.Data));

  // program VMCAP and VMConfig to apply bus restrictions and select bus numbering
  VmCap.Data = PciSegmentRead32 (DeviceBaseAddress + R_VMCAP_0_14_0_PCI_VMD_REG_OFFSET);
  VmCap.Bits.BusRestrictCap = 0x1;
  PciSegmentWrite32 (DeviceBaseAddress + R_VMCAP_0_14_0_PCI_VMD_REG_OFFSET, VmCap.Data);

  VmConfig.Data = PciSegmentRead32 (DeviceBaseAddress + R_VMCONFIG_0_14_0_PCI_VMD_REG_OFFSET);
  DEBUG((DEBUG_INFO, "Read after write VmConfig 0x%x\n", VmConfig.Data));

  // Select bus numbers 225 to 255 for VMD
  VmConfig.Bits.BusRestrictions = 0x2;

  // write DID value to DID_ASSIGN field
  // BIOS can simply copy those 8 MSB from DID of device0.
  // BIOS should write the lower 8 MSB to 0x0B (this value is not expected to change)
  DidAssign = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM,SA_MC_BUS,
        SA_MC_DEV, SA_MC_FUN, PCI_DEVICE_ID_OFFSET));
  DidAssign = (DidAssign & 0xFF00) | VMD_DID_LSB;
  DEBUG((DEBUG_INFO, "DidAssign is 0x%x\n", DidAssign));

  VmConfig.Bits.Did_Assign = DidAssign;

  // program VMConfig to lock VMD registers
  VmConfig.Bits.VmdLock = 1;

  DEBUG((DEBUG_INFO, "value to be written to VmConfig 0x%x\n", VmConfig.Data));
  PciSegmentWrite32 (DeviceBaseAddress + R_VMCONFIG_0_14_0_PCI_VMD_REG_OFFSET, VmConfig.Data);
  VmConfig.Data = PciSegmentRead32 (DeviceBaseAddress + R_VMCONFIG_0_14_0_PCI_VMD_REG_OFFSET);
  DEBUG((DEBUG_INFO, "Read after write VmConfig 0x%x\n", VmConfig.Data));

  DEBUG((DEBUG_INFO, "Bus Restrictions are applied and Lock Bit is set for VMD \n"));
  DEBUG ((DEBUG_INFO, "------------------ VmdInit End ------------------\n"));
  return EFI_SUCCESS;
}

/**
  This function enumerate all downstream bridge.

  @param[in] BusNum  - Primary bus number of current bridge.

  @retval BusNum: return current bus number if current bus is an enpoint device.
  @retval SubBus: return subordinate bus number if current bus is a bridge.
**/
UINT8
VmdEnumerateDownstream (
  IN UINT8  BusNum
  )
{
  UINT64  DeviceBaseAddress;
  UINT8   DevNum;
  UINT16  Buffer16;
  UINT8   SubBus;
  UINT8   SecBus;

  SubBus  = 0;

  SecBus  = BusNum;

  for (DevNum = 0; DevNum < 32; DevNum++) {
    ///
    /// Read Vendor ID to check if device exists
    /// if no device exists, then check next device
    ///
    DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, BusNum, DevNum, 0, 0);
    if (PciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
      continue;
    }

    Buffer16 = PciSegmentRead16 (DeviceBaseAddress + R_PCI_SCC_OFFSET);
    ///
    /// Check for PCI/PCI Bridge Device Base Class 6 with subclass 4
    ///
    if (Buffer16 == 0x0604) {
      SecBus++;
      PciSegmentWrite8 (DeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, BusNum);
      PciSegmentWrite8 (DeviceBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET, SecBus);
      ///
      /// Assign temporary subordinate bus number so that device behind this bridge can be seen
      ///
      PciSegmentWrite8 (DeviceBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET, 0xFF);

      ///
      /// A config write is required in order for the device to re-capture the Bus number,
      /// according to PCI Express Base Specification, 2.2.6.2
      /// Write to a read-only register VendorID to not cause any side effects.
      ///
      PciSegmentWrite16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SecBus, 0, 0, PCI_VENDOR_ID_OFFSET), 0);

      ///
      /// Enumerate bus behind this bridge by calling this function recursively
      ///
      SubBus = VmdEnumerateDownstream (SecBus);
      ///
      /// Update the correct subordinate bus number
      ///
      PciSegmentWrite8 (DeviceBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET, SubBus);
      SecBus = SubBus;
    }
  }

  if (SubBus == 0) {
    return BusNum;
  } else {
    return SubBus;
  }
}


/**
This function detects the mass storage devices attached to Peg60 and PCH Pcie Root ports and the Sata controller.

@param[in]      *VmdInfoHob     pointer to VMD info Hob to store the information of detected devices.

@retval EFI_SUCCESS            Successfully initialized Pre-Mem configurations.
**/

EFI_STATUS
EFIAPI
VmdDetectPcieStorageDevices (
    VMD_INFO_HOB               *VmdInfoHob
)
{
  EFI_STATUS  Status;
  UINTN       RpDev;
  UINTN       RpFunc;
  UINTN       RpIndex;
  UINT64      RpDeviceBaseAddress;
  UINT64      EpDeviceBaseAddress;
  UINT32      PcieBusNum;
  UINT8       Bus;
  UINT8       Dev;
  UINT8       Func;
  UINT8       MaxFunction;
  UINT8       NumOfDevices;
  UINT8       HeaderType;
  UINT32      DevId;
  UINT8       SubBusNum;
  UINT16      Buffer16;

  NumOfDevices = 0;
  ///
  /// Initialize Secondary and Subordinate bus number for first Pcie root port
  ///
  PcieBusNum  = 0x00010100;


  DEBUG ((DEBUG_INFO, "VMD: VmdDetectPcieStorageDevices Start\n"));

  DEBUG ((DEBUG_INFO, "checking device connection on peg60 port \n"));

  RpDev = SA_PEG3_DEV_NUM;
  RpFunc = 0;
  RpDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_PEG3_DEV_NUM, 0, 0);
  if (PciSegmentRead16 (RpDeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "VMD: RP 0/6/0 is not enabled\n"));
  } else {     // Enumerate and check if any of the devices connected to 0/6/0 is storage device
    PciSegmentWrite32 (RpDeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, PcieBusNum); // Assigning temp Bus
    for (Dev = 0; Dev <= 31; ++Dev) {
      //
      // Read Vendor ID to check if device exists
      // if no device exists, then check next device
      //
      EpDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 1, Dev, 0, 0);
      if (PciSegmentRead16 (EpDeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
        continue;
      }
      //
      // Check for a multifunction device
      //
      HeaderType = PciSegmentRead8 (EpDeviceBaseAddress + PCI_HEADER_TYPE_OFFSET);
      if ((HeaderType & HEADER_TYPE_MULTI_FUNCTION) != 0) {
        MaxFunction = 7;
      } else {
        MaxFunction = 0;
      }
      for (Func = 0; Func <= MaxFunction; ++Func) {
        EpDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 1, Dev, Func, 0);
        if (PciSegmentRead16 (EpDeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
          continue;
        } else {
          // Check if the device is mass storage device
          if (PciSegmentRead16 (EpDeviceBaseAddress + R_PCI_SCC_OFFSET) == 0x0108) {
              DevId = (PciSegmentRead16 (EpDeviceBaseAddress + PCI_DEVICE_ID_OFFSET));
              VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].DeviceDetected = 1;
              VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].DevId = DevId;
              VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].RpDev  = (UINT8)RpDev;
              VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].RpFunc = (UINT8)RpFunc;
              ++NumOfDevices;

              DEBUG ((DEBUG_INFO, "NVMe device found \n" ));
              DEBUG ((DEBUG_INFO, "for Bus / device / Func %d %d \n", RpDev, RpFunc));
              DEBUG ((DEBUG_INFO, "VMD: DevId 0x%x\n", DevId));
        }
      }
    }
  }
  //
  // Need to clear the assigned temporary bus no
  //
  RpDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_PEG3_DEV_NUM, 0, 0);
  PciSegmentWrite32 (RpDeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0);
  }

  DEBUG ((DEBUG_INFO, "VMD: Checking device on PCH PCIe ports \n" ));
  for (RpIndex = 0; RpIndex < GetPchMaxPciePortNum (); RpIndex++) {
    PcieBusNum  = 0x00010100;
    ///
    /// Check if root port exists
    ///
    Status = GetPchPcieRpDevFun (RpIndex, &RpDev, &RpFunc);
    ASSERT_EFI_ERROR (Status);

    RpDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, (UINT32) RpDev, (UINT32) RpFunc, 0);
    if (PciSegmentRead16 (RpDeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
      continue;
    }

    PciSegmentWrite32 (RpDeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, PcieBusNum);
    Bus = PciSegmentRead8 (RpDeviceBaseAddress + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);

    ///
    /// Assign temporary subordinate bus number so that device this bridge can be seen
    ///
    PciSegmentWrite8 (RpDeviceBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET, 0xFF);

    SubBusNum                       = VmdEnumerateDownstream (Bus);
    ///
    /// Update the actual subordinate bus number
    ///
    PciSegmentWrite8 (RpDeviceBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET, SubBusNum);
    //PcieBusNum = (SubBusNum + 1) << 8;

    for (Bus = 1; Bus <= SubBusNum; Bus++) {
      for (Dev = 0; Dev < 32; Dev++) {
        ///
        /// Read Vendor ID to check if device exists
        /// if no device exists, then check next device
        ///
        EpDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, Bus, Dev, 0, 0);
        if (PciSegmentRead16 (EpDeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
          continue;
        }
        ///
        /// Check for a multifunction device
        ///
        HeaderType = PciSegmentRead8 (EpDeviceBaseAddress + PCI_HEADER_TYPE_OFFSET);
        if ((HeaderType & HEADER_TYPE_MULTI_FUNCTION) != 0) {
          MaxFunction = 7;
        } else {
          MaxFunction = 0;
        }

        for (Func = 0; Func <= MaxFunction; Func++) {
          if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, Bus, Dev, Func, PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
            continue;
          }

          // Check if the device is mass storage device
          if (PciSegmentRead16 (EpDeviceBaseAddress + R_PCI_SCC_OFFSET) == 0x0108) {
              DevId = (PciSegmentRead16 (EpDeviceBaseAddress + PCI_DEVICE_ID_OFFSET));
              VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].DeviceDetected = 1;
              VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].DevId = DevId;
              VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].RpDev  = (UINT8) RpDev;
              VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].RpFunc = (UINT8) RpFunc;
              ++NumOfDevices;

              DEBUG ((DEBUG_INFO, "VMD: NVMe device found \t" ));
              DEBUG ((DEBUG_INFO, "on Bus/device/Func  0/%d/%d \t", RpDev, RpFunc));
              DEBUG ((DEBUG_INFO, "DevId 0x%x\n", DevId));
            }
        }
      }
    }
    ///
    /// Clear bus number on all the bridges that we have opened so far.
    /// We have to do it in the reverse Bus number order.
    ///
    for (Bus = SubBusNum; Bus >= 1; Bus--) {
      for (Dev = 0; Dev < 32; Dev++) {
        ///
        /// Read Vendor ID to check if device exists
        /// if no device exists, then check next device
        ///
        EpDeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, Bus, Dev, 0, 0);
        if (PciSegmentRead16 (EpDeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
          continue;
        }

        Buffer16 = PciSegmentRead16 (EpDeviceBaseAddress + R_PCI_SCC_OFFSET);
        ///
        /// Clear Bus Number for PCI/PCI Bridge Device
        ///
        if (Buffer16 == 0x0604) {
          PciSegmentWrite32 (EpDeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0);
        }
      }
    }
      ///
      /// Clear bus numbers so that PCIe slots are hidden
      ///
      PciSegmentWrite32 (RpDeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0);
      //reset the nus numbers
  } // End of PCH PCIe Rp

  DEBUG ((DEBUG_INFO, "VMD: Checking the availability of SATA controller(0/23/0) for sata devices \n" ));
  RpDeviceBaseAddress = SataRegBase (SATA_1_CONTROLLER_INDEX);
  if (PciSegmentRead16 (RpDeviceBaseAddress + PCI_VENDOR_ID_OFFSET) != 0xFFFF) {
    DevId = (PciSegmentRead16 (RpDeviceBaseAddress + PCI_DEVICE_ID_OFFSET));
    VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].DeviceDetected = 1;
    VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].DevId = DevId;
    VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].RpDev  = SataDevNumber (SATA_1_CONTROLLER_INDEX);
    VmdInfoHob->VmdPortInfo.PortInfo[NumOfDevices].RpFunc =  SataFuncNumber (SATA_1_CONTROLLER_INDEX);
    ++NumOfDevices;
    DEBUG ((DEBUG_INFO, "VMD: Sata device found \t" ));
    DEBUG ((DEBUG_INFO, "DevId 0x%x\n", DevId));
  }
  return EFI_SUCCESS;
}
