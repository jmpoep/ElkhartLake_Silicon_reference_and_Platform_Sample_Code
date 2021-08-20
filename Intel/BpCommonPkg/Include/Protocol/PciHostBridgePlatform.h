//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  PCI Host Bridge protocol consumed by PciHostBridgeLib returning
  the platform specific information about the PCI Host Bridge.

  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/
#ifndef _PCI_HOST_BRIDGE_PLATFORM_PROTOCOL_H_
#define _PCI_HOST_BRIDGE_PLATFORM_PROTOCOL_H_

#include <Library/PciHostBridgeLib.h>

#define EDKII_PCI_HOST_BRIDGE_PLATFORM_PROTOCOL_GUID \
  { \
    0x1ff4c0cb, 0x3b4e, 0x4ade, { 0x8a, 0x20, 0x56, 0x1d, 0x86, 0xb6, 0x21, 0x16 } \
  };

/**
  Return all the root bridge instances in an array.

  @param Count  Return the count of root bridge instances.

  @return All the root bridge instances in an array.
          The array should be passed into PciHostBridgeFreeRootBridges()
          when it's not used.
**/
typedef
PCI_ROOT_BRIDGE *
(EFIAPI *EDKII_PCI_HOST_BRIDGE_PLATFORM_GET_ROOT_BRIDGES)(
  UINTN *Count
  );

/**
  Free the root bridge instances array returned from PciHostBridgeGetRootBridges().

  @param  The root bridge instances array.
  @param  The count of the array.
**/
typedef
VOID
(EFIAPI *EDKII_PCI_HOST_BRIDGE_PLATFORM_FREE_ROOT_BRIDGES)(
  PCI_ROOT_BRIDGE *Bridges,
  UINTN           Count
  );

/**
  Inform the platform that the resource conflict happens.

  @param HostBridgeHandle Handle of the Host Bridge.
  @param Configuration    Pointer to PCI I/O and PCI memory resource descriptors.
                          The Configuration contains the resources for all the
                          root bridges. The resource for each root bridge is
                          terminated with END descriptor and an additional END
                          is appended indicating the end of the entire resources.
                          The resource descriptor field values follow the description
                          in EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL.SubmitResources().
**/
typedef
VOID
(EFIAPI *EDKII_PCI_HOST_BRIDGE_PLATFORM_RESOURCE_CONFLICT)(
  EFI_HANDLE           HostBridgeHandle,
  VOID                 *Configuration
  );

typedef struct {
  EDKII_PCI_HOST_BRIDGE_PLATFORM_GET_ROOT_BRIDGES  GetRootBridges;
  EDKII_PCI_HOST_BRIDGE_PLATFORM_FREE_ROOT_BRIDGES FreeRootBridges;
  EDKII_PCI_HOST_BRIDGE_PLATFORM_RESOURCE_CONFLICT ResourceConflict;
} EDKII_PCI_HOST_BRIDGE_PLATFORM_PROTOCOL;

extern EFI_GUID gEdkiiPciHostBridgePlatformProtocolGuid;

#endif
