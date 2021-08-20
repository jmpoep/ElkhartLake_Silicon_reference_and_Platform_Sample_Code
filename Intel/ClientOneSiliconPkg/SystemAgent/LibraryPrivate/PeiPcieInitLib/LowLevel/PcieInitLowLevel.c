/** @file
  PCIe Initialization Low Level functions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

@par Specification
**/

#include "PcieLowLevel.h"

#include <Library/PcieInitLib.h>
#include <PcieRegs.h>


///
/// Implementation Functions not exposed in the Library API
///

/**
  Find the Offset to a given Capabilities ID
  CAPID list:
    0x01 = PCI Power Management Interface
    0x04 = Slot Identification
    0x05 = MSI Capability
    0x10 = PCI Express Capability

  @param[in] Segment   -   Pci Segment Number
  @param[in] Bus       -   Pci Bus Number
  @param[in] Device    -   Pci Device Number
  @param[in] Function  -   Pci Function Number
  @param[in] CapId     -   CAPID to search for

  @retval 0       - CAPID not found
  @retval Other   - CAPID found, Offset of desired CAPID
**/
UINT32
PcieLibFindCapId (
  IN UINT8   Segment,
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   CapId
  )
{
  UINT64 DeviceBaseAddress;
  UINT8  CapHeader;

  ///
  /// Always start at Offset 0x34
  ///
  DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (Segment, Bus, Device, Function, 0);
  CapHeader         = PciSegmentRead8 (DeviceBaseAddress + PCI_CAPBILITY_POINTER_OFFSET);
  if (CapHeader == 0xFF) {
    return 0;
  }

  while (CapHeader != 0) {
    ///
    /// Bottom 2 bits of the pointers are reserved per PCI Local Bus Spec 2.2
    ///
    CapHeader &= ~(BIT1 + BIT0);
    ///
    /// Search for desired CapID
    ///
    if (PciSegmentRead8 (DeviceBaseAddress + CapHeader) == CapId) {
      return CapHeader;
    }

    CapHeader = PciSegmentRead8 (DeviceBaseAddress + CapHeader + 1);
  }

  return 0;
}

///
/// Functions that are exposed through the Library API
///

/**
  This function detects if an endpoint is attached to each given root port and
  if so, reads data from the endpoint and fills in the remaining fields of the
  PCIE_PORT_INFO structure that could not be filled before initial link training

  @param[in]  This                        - Low level function table
  @param[out] PciePorts                   - Array of PCIe Root Ports
  @param[out] PciePortsLength             - Length of the PciePorts array
**/
VOID
EFIAPI
PcieDetectEndpointPresence (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePorts,
  IN  UINT8                             PciePortsLength
  )
{
  UINT64            B1BaseAddress;
  UINT32            Lcap;
  UINT32            CapOffset;
  UINT8             Index;
  UINT8             Width;
  UINT8             LaneIndex;

  B1BaseAddress = PCI_SEGMENT_LIB_ADDRESS (0, 1, 0, 0, 0);
  for (Index = 0; Index < PciePortsLength; Index++) {
    ///
    /// Get link width and set active lane list
    ///
    Width                                          = This->GetNegotiatedWidth (This, &(PciePorts[Index]));
    PciePorts[Index].SwEqData.ActiveLaneListLength = Width;
    for (LaneIndex = 0; LaneIndex < Width; LaneIndex++) {
      PciePorts[Index].SwEqData.ActiveLaneList[LaneIndex] = PciePorts[Index].MaxPortLaneList[LaneIndex];
    }
    ///
    /// Negotiation Done?
    ///
    if (!This->DataLinkLayerLinkActive (This, &(PciePorts[Index]))) {
      PciePorts[Index].EndpointPresent          = FALSE;
      PciePorts[Index].EndpointVendorIdDeviceId = 0xFFFFFFFF;
      PciePorts[Index].EndpointMaxLinkSpeed     = 0;
      PciePorts[Index].EndpointMaxLinkWidth     = 0;
      PciePorts[Index].SwEqData.MaxCapableSpeed = 0;
      PciePorts[Index].SwEqData.MaxCapableWidth = 0;
      DEBUG ((
               DEBUG_INFO,
               " PCIe RP (%x:%x:%x) - DL is not active! Skipping endpoint.\n",
               PciePorts[Index].Bus,
               PciePorts[Index].Device,
               PciePorts[Index].Function
               ));
    } else {
      PciePorts[Index].EndpointPresent = TRUE;
      ///
      /// Set PEG PortBus = 1 to Read Endpoint.
      ///
      PciSegmentAndThenOr32 (PciePorts[Index].ConfigSpaceBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0xFF0000FF, 0x00010100);

      ///
      /// A config write is required in order for the device to re-capture the Bus number,
      /// according to PCI Express Base Specification, 2.2.6.2
      /// Write to a read-only register VendorID to not cause any side effects.
      ///
      PciSegmentWrite16 (B1BaseAddress + PCI_VENDOR_ID_OFFSET, 0);

      ///
      /// Save end point vendor id and device id
      ///
      PciePorts[Index].EndpointVendorIdDeviceId = PciSegmentRead32 (B1BaseAddress + PCI_VENDOR_ID_OFFSET);

      if (PciePorts[Index].EndpointVendorIdDeviceId != 0xFFFFFFFF) {
        ///
        /// Get the pointer to the Port PCI Express Capability Structure.
        ///
        CapOffset = PcieLibFindCapId (0, 1, 0, 0, EFI_PCI_CAPABILITY_ID_PCIEXP);
      } else {
        CapOffset = 0;
      }
      if (CapOffset == 0) {
        PciePorts[Index].EndpointMaxLinkSpeed = This->GetCurrentLinkSpeed (This, &(PciePorts[Index]));
        PciePorts[Index].EndpointMaxLinkWidth = Width;

        DEBUG ((
                 DEBUG_INFO,
                 " PCIe RP (%x:%x:%x) - Endpoint has no PCIe Capability structure!\n",
                 PciePorts[Index].Bus,
                 PciePorts[Index].Device,
                 PciePorts[Index].Function
                 ));
        DEBUG ((DEBUG_INFO, "                      assuming negotiated speed and width are max.\n"));
      } else {
        Lcap = PciSegmentRead32 (B1BaseAddress + CapOffset + 0x0C);
        PciePorts[Index].EndpointMaxLinkSpeed = (UINT8) (Lcap & 0x0F);
        PciePorts[Index].EndpointMaxLinkWidth = (UINT8) ((Lcap >> 4) & 0x3F);
      }

      ///
      /// Restore bus numbers on the PEG bridge.
      ///
      PciSegmentAnd32 (PciePorts[Index].ConfigSpaceBase + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0xFF0000FF);

      ///
      /// Determine max link speed and width based on gathered data
      ///
      if (PciePorts[Index].MaxPortSpeed > PciePorts[Index].EndpointMaxLinkSpeed) {
        PciePorts[Index].SwEqData.MaxCapableSpeed = PciePorts[Index].EndpointMaxLinkSpeed;
      } else {
        PciePorts[Index].SwEqData.MaxCapableSpeed = PciePorts[Index].MaxPortSpeed;
      }
      if (PciePorts[Index].MaxPortWidth > PciePorts[Index].EndpointMaxLinkWidth) {
        PciePorts[Index].SwEqData.MaxCapableWidth = PciePorts[Index].EndpointMaxLinkWidth;
      } else {
        PciePorts[Index].SwEqData.MaxCapableWidth = PciePorts[Index].MaxPortWidth;
      }
    }
    ///
    /// Print out discovered data
    ///
    DEBUG ((
             DEBUG_INFO,
             " PCIe RP (%x:%x:%x) - Link Status:\n",
             PciePorts[Index].Bus,
             PciePorts[Index].Device,
             PciePorts[Index].Function
             ));
    DEBUG ((
             DEBUG_INFO,
             " Endpoint Present: %d, VID[%4.4X] DID[%4.4X]\n",
             PciePorts[Index].EndpointPresent,
             ((PciePorts[Index].EndpointVendorIdDeviceId      ) & 0xFFFF),
             ((PciePorts[Index].EndpointVendorIdDeviceId >> 16) & 0xFFFF)
             ));
    DEBUG ((
             DEBUG_INFO,
             " Endpoint Max Speed: %d Width: X%d\n",
             (UINTN) PciePorts[Index].EndpointMaxLinkSpeed,
             (UINTN) PciePorts[Index].EndpointMaxLinkWidth
             ));
    DEBUG ((
             DEBUG_INFO,
             "     Max Link Speed: %d Width: X%d\n\n",
             (UINTN) PciePorts[Index].SwEqData.MaxCapableSpeed,
             (UINTN) PciePorts[Index].SwEqData.MaxCapableWidth
             ));
    This->ReportPcieLinkStatus (This, &(PciePorts[Index]));
  } ///< End of for each port
}

/**
  Gets the PCIe Capability Structure Pointer

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port

  @retval Offset to the PCIe Capability Structure
**/
UINT8
EFIAPI
PcieGetPcieCapOffset (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort
  )
{
  return (UINT8) PcieLibFindCapId (PciePort->Segment, PciePort->Bus, PciePort->Device, PciePort->Function, EFI_PCI_CAPABILITY_ID_PCIEXP);
}

/**
  Checks if the Data Link Layer is in DL_Active state on the given root port

  @param[in]  This                        - Low level function table
  @param[in]  PciePorts                   - Root Port to check for VC0 negotiation complete

  @retval TRUE  - Data Link Layer is in DL_Active state
  @retval FALSE - Data Link Layer is NOT in DL_Active state
**/
BOOLEAN
EFIAPI
PcieDataLinkLayerLinkActive (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort
  )
{
  if ((B_PCIE_LSTS_LA & PciSegmentRead16 (PciePort->ConfigSpaceBase + PciePort->PcieCapOffset + R_PCIE_LSTS_OFFSET)) == B_PCIE_LSTS_LA) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Returns the current value of the PCIe Slot Status Presence Detect bit

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port

  @retval Slot Presence Detect bit state
**/
BOOLEAN
EFIAPI
PcieGetSlotPresenceDetect (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort
  )
{
  if ((PciSegmentRead16 (PciePort->ConfigSpaceBase + PciePort->PcieCapOffset + R_PCIE_SLSTS_OFFSET) & B_PCIE_SLSTS_PDS) != 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Set the Link Disable bit in the PCIe Link Control Register

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
  @param[in]  LinkDisable                 - New value for link disable bit
**/
VOID
EFIAPI
PcieSetLinkDisable (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort,
  IN  BOOLEAN                           LinkDisable
  )
{
  if (LinkDisable) {
    PciSegmentOr16  (PciePort->ConfigSpaceBase + PciePort->PcieCapOffset + R_PCIE_LCTL_OFFSET, B_PCIE_LCTL_LD);
  } else {
    PciSegmentAnd16 (PciePort->ConfigSpaceBase + PciePort->PcieCapOffset + R_PCIE_LCTL_OFFSET, (UINT16) ~(B_PCIE_LCTL_LD));
  }
}

/**
  Retrain the PCIe link

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
**/
VOID
EFIAPI
PcieRetrainLink (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort
  )
{
  PciSegmentOr16 (PciePort->ConfigSpaceBase + PciePort->PcieCapOffset + R_PCIE_LCTL_OFFSET, B_PCIE_LCTL_RL);
}

/**
  Get Negotiated Link Width

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
**/
UINT8
EFIAPI
PcieGetNegotiatedWidth (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort
  )
{
  UINT16 Lsts;

  Lsts = PciSegmentRead16 (PciePort->ConfigSpaceBase + PciePort->PcieCapOffset + R_PCIE_LSTS_OFFSET);

  return (UINT8) ((Lsts >> 4) & 0x3F);
}

/**
  Get Current Link Speed

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
**/
UINT8
EFIAPI
PcieGetCurrentLinkSpeed (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort
  )
{
  UINT16 Lsts;

  Lsts = PciSegmentRead16 (PciePort->ConfigSpaceBase + PciePort->PcieCapOffset + R_PCIE_LSTS_OFFSET);

  return (UINT8) (Lsts & 0xF);
}

/**
  Get Target Link Speed

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
**/
UINT8
EFIAPI
PcieGetTargetLinkSpeed (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort
  )
{
  return PciSegmentRead16 (PciePort->ConfigSpaceBase + PciePort->PcieCapOffset + R_PCIE_LCTL2_OFFSET) & 0xF;
}

/**
  Set Target Link Speed

  @param[in]  This                        - Low level function table
  @param[in]  PciePort                    - PCIe Root Port
  @param[in]  TargetLinkSpeed             - Target Link Speed
**/
VOID
EFIAPI
PcieSetTargetLinkSpeed (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort,
  IN  UINT8                             TargetLinkSpeed
  )
{
  PciSegmentAndThenOr16 (
    PciePort->ConfigSpaceBase + PciePort->PcieCapOffset + R_PCIE_LCTL2_OFFSET,
    0xFFF0,
    (UINT16) (TargetLinkSpeed & 0xF));
}

/**
  Program the same TxEQ to all lanes on the endpoint attached to the given root port.

  @param[in]  This                        - Low level function table
  @param[in]  PciePorts                   - PCIe Root Ports
  @param[in]  Preset                      - Preset to program
**/
VOID
EFIAPI
PcieProgramUniformPortPhase3TxEq (
  IN  PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *This,
  IN  PCIE_PORT_INFO                    *PciePort,
  IN  UINT8                             Preset
  )
{
  UINT8   Presets[PCIE_MAX_LANE];

  if (PciePort->SwEqData.ActiveLaneListLength <= PCIE_MAX_LANE) {
    SetMem (&(Presets[0]), PciePort->SwEqData.ActiveLaneListLength, Preset);
    This->ProgramPortPhase3TxEq (This, PciePort, &(Presets[0]));
  }
}

/**
  This function gets the table of generic low level function calls for the PCIe
  interface.  These function calls use PCIe spec defined mechanisms and can be
  overrided by a silicon specific implementation if needed.

  @param[out] PcieLowLevel - Table of function calls for PCIe

  @retval EFI_SUCCESS - Table of function calls returned successfully
**/
EFI_STATUS
GetGenericPcieLowLevelFunctionCalls (
  OUT PCIE_SI_LOW_LEVEL_FUNCTION_CALLS  *PcieLowLevelFunctionCalls
  )
{
  PcieLowLevelFunctionCalls->PrivateData                  = NULL;
  PcieLowLevelFunctionCalls->DetectEndpointPresence       = PcieDetectEndpointPresence;
  PcieLowLevelFunctionCalls->GetPcieCapOffset             = PcieGetPcieCapOffset;
  PcieLowLevelFunctionCalls->DataLinkLayerLinkActive      = PcieDataLinkLayerLinkActive;
  PcieLowLevelFunctionCalls->GetSlotPresenceDetect        = PcieGetSlotPresenceDetect;
  PcieLowLevelFunctionCalls->SetLinkDisable               = PcieSetLinkDisable;
  PcieLowLevelFunctionCalls->RetrainLink                  = PcieRetrainLink;
  PcieLowLevelFunctionCalls->GetNegotiatedWidth           = PcieGetNegotiatedWidth;
  PcieLowLevelFunctionCalls->GetCurrentLinkSpeed          = PcieGetCurrentLinkSpeed;
  PcieLowLevelFunctionCalls->GetTargetLinkSpeed           = PcieGetTargetLinkSpeed;
  PcieLowLevelFunctionCalls->SetTargetLinkSpeed           = PcieSetTargetLinkSpeed;
  PcieLowLevelFunctionCalls->ProgramUniformPortPhase3TxEq = PcieProgramUniformPortPhase3TxEq;
  PcieLowLevelFunctionCalls->SetPerst                     = PcieSetPerst;
  PcieLowLevelFunctionCalls->EnsureLinkIsHealthy          = PcieEnsureLinkIsHealthy;
  return EFI_SUCCESS;
}
