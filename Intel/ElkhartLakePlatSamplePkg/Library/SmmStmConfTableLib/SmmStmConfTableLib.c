/** @file
 CPU Configuration Library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2016 Intel Corporation.

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
#include <PiSmm.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>

#include <StmDefinition.h>
#include <SmmStmConfTable.h>
#include <TxtInfoHob.h>
#include <Protocol/SmmTxtStmService.h>
#include <Protocol/SmmTxtResource.h>
#include <Library/SmmStmConfTableLib.h>

///
/// Function prototypes.
///
/**
  Add resources in list to database. Allocate new memory areas as needed.

  @param[in]  ResourceList           A pointer to resource list to be added
  @param[in]  NumEntries             Optional number of entries. If 0 list must be
                                     terminated by END_OF_RESOURCES.
  @param[in]  StartOver              Reset area if directed

  @retval     EFI_SUCCESS            If resources are added
  @retval     ERROR_SMM_INVALID_RSC  If nested procedure detected resource failer
  @retval     EFI_OUT_OF_RESOURCES   If nested procedure returned it and we
                                     cannot allocate more areas.
**/
EFI_STATUS
EFIAPI
StmAddResources (
  IN  RESOURCE             *ResourceList,
  IN  UINT32               NumEntries OPTIONAL,
  IN  UINT32               StartOver
  );

/**
  Add all Resources in list to current area

  @param[in]  ResourceList           A pointer to pointer to resource list to be added
  @param[in]  NumEntries             Optional number of entries. If 0 list must be
                                     terminated by END_OF_RESOURCES.
  @param[in]  Area                   A pointer to area descriptor.

  @retval     EFI_SUCCESS            If list is successfully added
  @retval     ERROR_SMM_INVALID_RSC  If resource structure failed validation
  @retval     EFI_OUT_OF_RESOURCES   If nested procedure returned it.
                                     ResourceList is adjusted in this case
**/
EFI_STATUS
EFIAPI
StmAddAreaResource (
  IN  RESOURCE                 **ResourceList,
  IN  UINT32                   NumEntries OPTIONAL,
  IN  RESOURCE_AREA            *AreaPtr
  );

/**
  Scan entire area. For each of the records matching resource type call
  handling procedure which will adjust boundary as necessary.
  In case of resource already covered by existing record - do nothing,
  otherwise add record to the end of area database.

  @param[in]  Resource              A pointer to resource to be added
  @param[in]  Area                  A pointer to area descriptor.

  @retval     EFI_SUCCESS           If resource is added
  @retval     EFI_OUT_OF_RESOURCES  If Free space in area has insufficient size to add resource
**/
EFI_STATUS
EFIAPI
StmAddSingleResource (
  IN  RESOURCE      *Resource,
  IN  RESOURCE_AREA *AreaPtr
  );

/**
  Upper level code guarantees that both Resource and Record have the same
  resource type.

  Compare Resource and Record:
  a) If Record contains Resource - return STS_RESOURCE_PRESENT;
  b) If Record overlaps Resource - merge, erase
  current Record, don't promote Record pointer and return
  STS_CONTINUE_SEARCH;
  b) If Resource and Record are disjoint - promote Record pointer to next
  record and return STS_CONTINUE_SEARCH.

  Erasing of Record is done by moving down entire area starting from next
  Record over current Record and respective adjustment of values in
  AreaPtr.

  @param[in]  Resource              A pointer to resource to be handled
  @param[in]  RecordPtr             A pointer to the current record of resource in database.
  @param[in]  Area                  A pointer to area descriptor.

  @retval     STS_RESOURCE_PRESENT  If resource is already covered by record
  @retval     STS_CONTINUE_SEARCH   Signal to continue search with possibly adjusted boundaries.
**/
EFI_STATUS
EFIAPI
StmHandleSingleResource (
  IN  RESOURCE      *Resource,
  IN  RESOURCE      **AreaResource,
  IN  RESOURCE_AREA *AreaPtr
  );

///
/// Template of STM_RSC_END structure for copying.
///
static STM_RSC_END                  RscEndTpl = {
  {
    END_OF_RESOURCES,
    sizeof (STM_RSC_END)
  },
  0
};

///
/// Resource database.
/// Allocate initially 4K statically.
///
STM_RESOURCE_HEADER                 StmResourceHeader;
UINT8                               StmResources[0x1000];

static STM_CONFIGURATION_TABLE  mSmmStmSystemTable = {
  STM_INACTIVE,
  0,
  StmAddResources
};

SMM_TXT_STM_PROTOCOL mSmmStmProtocol = { (VOID *) StmResources };

/**
  STM library Initial Entry

  @param[in]  SystemTable       A pointer to the EFI System Table

  @retval     EFI_SUCCESS       If TXT initialization succeed
  @retval     EFI_UNLOAD_IMAGE  If TXT criterias are not met
**/
EFI_STATUS
EFIAPI
SmmStmConfTableInit (
  IN  EFI_SYSTEM_TABLE                          *SystemTable
  )
{
  EFI_STATUS    Status;
  EFI_HANDLE    Handle;

  Handle  = NULL;

  if (PcdGet32 (PcdCpuStmSize) != 0) {
    mSmmStmSystemTable.StmFlags |= STM_OPT_IN;
  } else {
    return EFI_UNSUPPORTED;
  }

  ///
  /// Install STM SMM System Table
  ///
  Status = gSmst->SmmInstallConfigurationTable (
                    gSmst,
                    &gSmmStmConfTableGuid,
                    &mSmmStmSystemTable,
                    sizeof (STM_CONFIGURATION_TABLE)
                    );
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }
  ///
  /// Pointer to array of SMM_ENTRY_INIT_STRUCT structures
  ///
  StmResourceHeader.NumAreas = 1;
  StmResourceHeader.Area[0].AreaAddress = (EFI_PHYSICAL_ADDRESS) StmResources;
  StmResourceHeader.Area[0].AreaSize = AREA_SIZE;
  StmResourceHeader.Area[0].FreeSize = AREA_SIZE - sizeof (STM_RSC_END);
  StmResourceHeader.Area[0].EndOfRscAddress = StmResourceHeader.Area[0].AreaAddress;
  StmResourceHeader.Area[0].FreeSpaceAddress = StmResourceHeader.Area[0].AreaAddress + sizeof (STM_RSC_END);
  *((STM_RSC_END *) StmResourceHeader.Area[0].EndOfRscAddress) = RscEndTpl;

  ///
  /// Install protocol interface
  ///
  Handle = NULL;
  Status = SystemTable->BootServices->InstallMultipleProtocolInterfaces (
                                        &Handle,
                                        &gSmmTxtStmProtocolGuid,
                                        &mSmmStmProtocol,
                                        NULL
                                        );

  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Add resources in list to database. Allocate new memory areas as needed.

  @param[in]  ResourceList           A pointer to resource list to be added
  @param[in]  NumEntries             Optional number of entries. If 0 list must be
                                     terminated by END_OF_RESOURCES.
  @param[in]  StartOver              Reset area if directed

  @retval     EFI_SUCCESS            If resources are added
  @retval     ERROR_SMM_INVALID_RSC  If nested procedure detected resource failer
  @retval     EFI_OUT_OF_RESOURCES   If nested procedure returned it and we
                                     cannot allocate more areas.
**/
EFI_STATUS
EFIAPI
StmAddResources (
  IN  RESOURCE               *ResourceList,
  IN  UINT32                 NumEntries OPTIONAL,
  IN  UINT32                 StartOver
  )
{
  EFI_STATUS            Status;
  EFI_PHYSICAL_ADDRESS  NewArea;
  UINT32                Index;
  EFI_PHYSICAL_ADDRESS  Link;

  RESOURCE              *List;

  Status  = 0;
  List    = ResourceList;

  ///
  /// Reset area if directed
  ///
  if (StartOver == START_OVER) {
    for (Index = 0; Index < StmResourceHeader.NumAreas; Index++) {
      ///
      /// Preserve link to next area
      ///
      NewArea = ((STM_RSC_END *) StmResourceHeader.Area[Index].EndOfRscAddress)->ResourceListContinuation;
      ///
      /// Initialize other fields
      ///
      StmResourceHeader.Area[Index].AreaSize          = AREA_SIZE;
      StmResourceHeader.Area[Index].FreeSize          = AREA_SIZE - sizeof (STM_RSC_END);
      StmResourceHeader.Area[Index].EndOfRscAddress   = StmResourceHeader.Area[Index].AreaAddress;
      StmResourceHeader.Area[Index].FreeSpaceAddress  = StmResourceHeader.Area[Index].AreaAddress + sizeof (STM_RSC_END);
      ///
      /// Install STM_RSC_END template at the beginning of area
      ///
      *((STM_RSC_END *) StmResourceHeader.Area[Index].EndOfRscAddress) = RscEndTpl;
      ///
      /// Restore link to next area
      ///
      ((STM_RSC_END *) StmResourceHeader.Area[Index].EndOfRscAddress)->ResourceListContinuation = NewArea;
    }
  }

  for (Index = 0; Index < StmResourceHeader.NumAreas; Index++) {

    Status = StmAddAreaResource (
               &List,
               NumEntries,
               &StmResourceHeader.Area[Index]
               );
    ///
    /// If success or any error beside of EFI_OUT_OF_RESOURCES return. If
    /// error EFI_OUT_OF_RESOURCES - continue with next area. List is
    /// adjusted in this case.
    ///
    if (Status != EFI_OUT_OF_RESOURCES) {
      return Status;
    }
  }
  ///
  /// EFI_OUT_OF_RESOURCES was returned and we tried all allocated
  /// areas. Try to allocate new area and add resource to it.
  ///
  if (StmResourceHeader.NumAreas == MAX_AREAS) {
    return Status;
  }

  Status = gSmst->SmmAllocatePages (
                    AllocateMaxAddress,
                    EfiRuntimeServicesData,
                    1,
                    &NewArea
                    );

  ASSERT_EFI_ERROR (Status);
  ///
  /// Update header values and link new area
  ///
  StmResourceHeader.NumAreas++;
  StmResourceHeader.Area[Index].AreaAddress         = NewArea;
  StmResourceHeader.Area[Index].AreaSize            = AREA_SIZE;
  StmResourceHeader.Area[Index].FreeSize            = AREA_SIZE - sizeof (STM_RSC_END);
  StmResourceHeader.Area[Index].EndOfRscAddress     = StmResourceHeader.Area[Index].AreaAddress;
  StmResourceHeader.Area[Index].FreeSpaceAddress    = StmResourceHeader.Area[Index].AreaAddress + sizeof (STM_RSC_END);
  Link = (UINT64) StmResourceHeader.Area[Index - 1].EndOfRscAddress;
  ((STM_RSC_END *) Link)->ResourceListContinuation = NewArea;

  ///
  /// Add resource to newly allocated area. In theory it is possible
  /// that input list is so large that cannot fit in newly allocated
  /// area and we need to loop several times repeating allocation of new
  /// area until we reach MAX_AREAS. This seems to be unlikely and thus
  /// impractical. We ignore such possibility to get simpler code.
  ///
  Status = StmAddAreaResource (
             &List,
             NumEntries,
             &StmResourceHeader.Area[Index]
             );

  return Status;
}

/**
  Add all Resources in list to current area

  @param[in]  ResourceList           A pointer to pointer to resource list to be added
  @param[in]  NumEntries             Optional number of entries. If 0 list must be
                                     terminated by END_OF_RESOURCES.
  @param[in]  Area                   A pointer to area descriptor.

  @retval     EFI_SUCCESS            If list is successfully added
  @retval     ERROR_SMM_INVALID_RSC  If resource structure failed validation
  @retval     EFI_OUT_OF_RESOURCES   If nested procedure returned it.
                                     ResourceList is adjusted in this case
**/
EFI_STATUS
EFIAPI
StmAddAreaResource (
  IN OUT RESOURCE                 **ResourceList,
  IN     UINT32                   NumEntries OPTIONAL,
  IN     RESOURCE_AREA            *Area
  )
{
  EFI_STATUS  Status;
  UINT32      Count;
  UINT32      Index;
  RESOURCE    *Resource;

  ///
  /// If NumEntries == 0 make it very big. Scan will be terminated by
  /// END_OF_RESOURCES.
  ///
  if (NumEntries == 0) {
    Count = 0xFFFFFFFF;
  } else {
    Count = NumEntries;
  }
  ///
  /// Start from beginning of resource list.
  ///
  Resource = *ResourceList;

  for (Index = 0; Index < Count; Index++) {
    ///
    /// Validate resource.
    ///
    switch (Resource->hdr.RscType) {
      case END_OF_RESOURCES:
        if (Resource->hdr.Length != sizeof (STM_RSC_END)) {
          return ERROR_SMM_INVALID_RSC;
        }
        ///
        /// If we are passed actual number of resources to add,
        /// END_OF_RESOURCES structure between them is considered an
        /// error. If NumEntries == 0 END_OF_RESOURCES is a termination.
        ///
        if (NumEntries != 0) {
          return ERROR_SMM_INVALID_RSC;
        } else {
          ///
          /// If NumEntries == 0 and list reached end - return success.
          ///
          return EFI_SUCCESS;
        }
        break;

      case MEM_RANGE:
      case MMIO_RANGE:
        if (Resource->hdr.Length != sizeof (STM_RSC_MEM_DESC)) {
          return ERROR_SMM_INVALID_RSC;
        }

        if (Resource->mem.RWXAttributes > FULL_ACCS) {
          return ERROR_SMM_INVALID_RSC;
        }
        break;

      case IO_RANGE:
      case TRAPPED_IO_RANGE:
        if (Resource->hdr.Length != sizeof (STM_RSC_IO_DESC)) {
          return ERROR_SMM_INVALID_RSC;
        }

        if ((Resource->io.Base + Resource->io.Length) > 0xFFFF) {
          return ERROR_SMM_INVALID_RSC;
        }
        break;

      case PCI_CFG_RANGE:
        if (Resource->hdr.Length != sizeof (STM_RSC_PCI_CFG_DESC)) {
          return ERROR_SMM_INVALID_RSC;
        }

        if ((Resource->pci.PciDevicePath->PciDevice > 0x1F) || (Resource->pci.PciDevicePath->PciFunction > 7)) {
          return ERROR_SMM_INVALID_RSC;
        }

        if ((Resource->pci.Base + Resource->pci.Length) > 0xFFF) {
          return ERROR_SMM_INVALID_RSC;
        }
        break;

      case MACHINE_SPECIFIC_REG:
        if (Resource->hdr.Length != sizeof (STM_RSC_MSR_DESC)) {
          return ERROR_SMM_INVALID_RSC;
        }
        break;

      default:
        return ERROR_SMM_INVALID_RSC;
    }

    Status = StmAddSingleResource (
               Resource,
               Area
               );

    if (Status == EFI_SUCCESS) {
      ///
      /// Go to next resource.
      ///
      Resource = (RESOURCE *)((UINTN)Resource + (UINTN)Resource->hdr.Length);
    } else {
      ///
      /// Adjust list pointer
      ///
      *ResourceList = Resource;
      return Status;
    }
  }

  return EFI_SUCCESS;
}

/**
  Scan entire area. For each of the records matching resource type call
  handling procedure which will adjust boundary as necessary.
  In case of resource already covered by existing record - do nothing,
  otherwise add record to the end of area database.

  @param[in]  Resource             A pointer to resource to be added
  @param[in]  Area                 A pointer to area descriptor.

  @retval    EFI_SUCCESS           If resource is added
  @retval    EFI_OUT_OF_RESOURCES  If Free space in area has insufficient size to add resource
**/
EFI_STATUS
EFIAPI
StmAddSingleResource (
  IN  RESOURCE      *Resource,
  IN  RESOURCE_AREA *Area
  )
{
  EFI_STATUS            Status;
  RESOURCE              *Record;
  EFI_PHYSICAL_ADDRESS  EndPtr;
  STM_RSC_END           Tmp;

  Status = 0;

  if (Area->FreeSize < Resource->hdr.Length) {
    return EFI_OUT_OF_RESOURCES;
  }
  ///
  /// Start from beginning of area.
  ///
  Record = (RESOURCE *) Area->AreaAddress;

  for (;;) {
    ///
    /// Break if reached end of area.
    ///
    if (Record->hdr.RscType == END_OF_RESOURCES) {
      break;
    }
    ///
    /// Go to next record if resource and record types don't match.
    ///
    if (Resource->hdr.RscType != Record->hdr.RscType) {

      Record = (RESOURCE *)((UINTN)Record + (UINTN)Record->hdr.Length);
      continue;
    }
    ///
    /// Additional checks
    ///
    /// Go to next record if MSR numbers are different.
    ///
    if ((Resource->hdr.RscType == MACHINE_SPECIFIC_REG) && (Resource->msr.MsrIndex != Record->msr.MsrIndex)) {

      Record = (RESOURCE *)((UINTN)Record + (UINTN)Record->hdr.Length);
      continue;
    }
    ///
    /// Go to next record if PFA are different.
    ///
    if ((Resource->hdr.RscType == PCI_CFG_RANGE) &&
        ((Resource->pci.OriginatingBusNumber != Record->pci.OriginatingBusNumber) ||
         (Resource->pci.PciDevicePath->PciDevice != Record->pci.PciDevicePath->PciDevice) ||
         (Resource->pci.PciDevicePath->PciFunction != Record->pci.PciDevicePath->PciFunction))) {

      Record = (RESOURCE *)((UINTN)Record + (UINTN)Record->hdr.Length);
      continue;
    }
    ///
    /// Record is handled inside of procedure - don't adjust.
    ///
    Status = StmHandleSingleResource (
               Resource,
               &Record,
               Area
               );

    if (Status == STS_RESOURCE_PRESENT) {
      return EFI_SUCCESS;
    }
  }
  ///
  /// Add resource to the end of area. Get pointer to STM_RSC_END marker
  ///
  EndPtr = Area->EndOfRscAddress;
  ///
  /// Save current STM_RSC_END in temporary variable
  ///
  CopyMem (&Tmp, (VOID *) EndPtr, sizeof(STM_RSC_END));
  //Tmp = *(STM_RSC_END *) EndPtr;

  ///
  /// Adjust area values
  ///
  Area->FreeSize -= Resource->hdr.Length;
  Area->EndOfRscAddress += Resource->hdr.Length;
  Area->FreeSpaceAddress += Resource->hdr.Length;

  ///
  /// Copy resource over current end marker
  ///
  switch (Resource->hdr.RscType) {
    case MEM_RANGE:
    case MMIO_RANGE:
      //* (STM_RSC_MEM_DESC *) EndPtr = Resource->mem;
      CopyMem ((VOID *) EndPtr, (VOID *)Resource, sizeof(STM_RSC_MEM_DESC));
      break;

    case IO_RANGE:
    case TRAPPED_IO_RANGE:
      //* (STM_RSC_IO_DESC *) EndPtr = Resource->io;
      CopyMem ((VOID *) EndPtr, (VOID *)Resource, sizeof(STM_RSC_IO_DESC));
      break;

    case MACHINE_SPECIFIC_REG:
      //* (STM_RSC_MSR_DESC *) EndPtr = Resource->msr;
      CopyMem ((VOID *) EndPtr, (VOID *)Resource, sizeof(STM_RSC_MSR_DESC));
      break;

    case PCI_CFG_RANGE:
      //* (STM_RSC_PCI_CFG_DESC *) EndPtr = Resource->pci;
      CopyMem ((VOID *) EndPtr, (VOID *)Resource, sizeof(STM_RSC_PCI_CFG_DESC));
      break;
  }
  ///
  /// Adjust pointer to new end marker
  ///
  EndPtr += Resource->hdr.Length;
  ///
  /// Copy end marker back to new position
  ///
  //*(STM_RSC_END *) EndPtr = Tmp;
  CopyMem ((VOID *) EndPtr, &Tmp, sizeof(STM_RSC_END));

  return EFI_SUCCESS;
}

/**
  Upper level code guarantees that both Resource and Record have the same
  resource type.

  Compare Resource and Record:
  a) If Record contains Resource - return STS_RESOURCE_PRESENT;
  b) If Record overlaps Resource - merge, erase
  current Record, don't promote Record pointer and return
  STS_CONTINUE_SEARCH;
  b) If Resource and Record are disjoint - promote Record pointer to next
  record and return STS_CONTINUE_SEARCH.

  Erasing of Record is done by moving down entire area starting from next
  Record over current Record and respective adjustment of values in
  AreaPtr.

  @param[in] Resource              A pointer to resource to be handled
  @param[in] RecordPtr             A pointer to the current record of resource in database.
  @param[in] Area                  A pointer to area descriptor.

  @retval    STS_RESOURCE_PRESENT  If resource is already covered by record
  @retval    STS_CONTINUE_SEARCH   Signal to continue search with possibly adjusted boundaries.
**/
EFI_STATUS
EFIAPI
StmHandleSingleResource (
  IN  RESOURCE      *Resource,
  IN  RESOURCE      **RecordPtr,
  IN  RESOURCE_AREA *Area
  )
{
  RESOURCE              *Record;
  UINT64                ResourceLo;
  UINT64                ResourceHi;
  UINT64                RecordLo;
  UINT64                RecordHi;
  EFI_PHYSICAL_ADDRESS  FromEndPtr;
  EFI_PHYSICAL_ADDRESS  FromStartPtr;
  UINT32                RecordLength;

  ResourceLo  = 0;
  ResourceHi  = 0;
  RecordLo    = 0;
  RecordHi    = 0;

  Record      = *RecordPtr;
  ///
  /// Calling code is responsible for making sure that
  /// Resource->hdr.RscType == (*Record)->hdr.RscType
  /// thus we use just one of them as switch variable.
  ///
  switch (Resource->hdr.RscType) {
    case MEM_RANGE:
    case MMIO_RANGE:
      ResourceLo  = Resource->mem.Base;
      ResourceHi  = Resource->mem.Base + Resource->mem.Length;
      RecordLo    = Record->mem.Base;
      RecordHi    = Record->mem.Base + Record->mem.Length;
      break;

    case IO_RANGE:
    case TRAPPED_IO_RANGE:
      ResourceLo  = (UINT64) Resource->io.Base;
      ResourceHi  = (UINT64) Resource->io.Base + (UINT64) Resource->io.Length;
      RecordLo    = (UINT64) Record->io.Base;
      RecordHi    = (UINT64) Record->io.Base + (UINT64) Record->io.Length;
      break;

    case PCI_CFG_RANGE:
      ResourceLo  = (UINT64) Resource->pci.Base;
      ResourceHi  = (UINT64) Resource->pci.Base + (UINT64) Resource->pci.Length;
      RecordLo    = (UINT64) Record->pci.Base;
      RecordHi    = (UINT64) Record->pci.Base + (UINT64) Record->pci.Length;
      break;

    case MACHINE_SPECIFIC_REG:
      ///
      /// New functionality - if resource is completely equal record except
      /// ignoreResource flag - update flag.
      ///
      if ((Record->msr.ReadMask == Resource->msr.ReadMask) && (Record->msr.WriteMask == Resource->msr.WriteMask)) {
        Record->hdr.IgnoreResource = Resource->hdr.IgnoreResource;
        return STS_RESOURCE_PRESENT;
      }
      ///
      /// Else special case - merge MSR masks in place.
      ///
      Record->msr.ReadMask |= Resource->msr.ReadMask;
      Record->msr.WriteMask |= Resource->msr.WriteMask;
      return STS_RESOURCE_PRESENT;
      break;
  }
  ///
  /// If resources are disjoint - adjust pointer and return.
  ///
  if ((ResourceHi < RecordLo) || (ResourceLo > RecordHi)) {
    Record = (RESOURCE *)((UINTN)Record + (UINTN)Record->hdr.Length);
    *RecordPtr = (RESOURCE *)Record;
    return STS_CONTINUE_SEARCH;
  }
  ///
  /// New functionality - if resource is completely equal record except
  /// ignoreResource flag - update flag.
  ///
  if ((ResourceLo == RecordLo) && (ResourceHi == RecordHi)) {
    if ((Resource->hdr.RscType != MEM_RANGE) && (Resource->hdr.RscType != MMIO_RANGE)) {
      ///
      /// If not a memory or mmio - no more fields to compare. Just
      /// update IgnoreResource flag
      ///
      Record->hdr.IgnoreResource = Resource->hdr.IgnoreResource;
      return STS_RESOURCE_PRESENT;
    }
    ///
    /// If memory or mmio - also compare attributes.
    ///
    if (Resource->mem.RWXAttributes == Record->mem.RWXAttributes) {
      Record->hdr.IgnoreResource = Resource->hdr.IgnoreResource;
      return STS_RESOURCE_PRESENT;
    }
  }
  ///
  /// If resource is consumed by record.
  ///
  if ((ResourceLo >= RecordLo) && (ResourceHi <= RecordHi)) {
    if ((Resource->hdr.RscType != MEM_RANGE) && (Resource->hdr.RscType != MMIO_RANGE)) {
      return STS_RESOURCE_PRESENT;
    }
    ///
    /// Additional requirement for MEM_RANGE & MMIO_RANGE
    /// Only if resource requests the same or lesser attributes it is
    /// considered "consumed".
    ///
    if (Resource->mem.RWXAttributes <= Record->mem.RWXAttributes) {
      return STS_RESOURCE_PRESENT;
    }
    ///
    /// Else this is disjoint range. Adjust pointer and continue.
    ///
    Record = (RESOURCE *)((UINTN)Record + (UINTN)Record->hdr.Length);
    *RecordPtr = (RESOURCE *)Record;
    return STS_CONTINUE_SEARCH;
  }
  ///
  /// Resources are overlapping.
  ///
  /// Additional requirement for MEM_RANGE & MMIO_RANGE
  ///
  if ((Resource->hdr.RscType == MEM_RANGE) || (Resource->hdr.RscType == MMIO_RANGE)) {
    ///
    /// If Resource consumes record but requests LESS attributes - we
    /// cannot merge and consider ranges disjoint.
    ///
    if ((ResourceLo <= RecordLo) &&
        (ResourceHi >= RecordHi) &&
        (Resource->mem.RWXAttributes < Record->mem.RWXAttributes) ) {

      Record = (RESOURCE *)((UINTN)Record + (UINTN)Record->hdr.Length);
      *RecordPtr = Record;
      return STS_CONTINUE_SEARCH;
    }
    ///
    /// Resource and Record are overlapping but don't competely include
    /// each other. If attributes are different we cannot merge and
    /// consider ranges disjoint.
    ///
    if (Resource->mem.RWXAttributes != Record->mem.RWXAttributes) {
      Record = (RESOURCE *)((UINTN)Record + (UINTN)Record->hdr.Length);
      *RecordPtr = Record;
      return STS_CONTINUE_SEARCH;
    }
  }
  ///
  /// Resource and record are merged.
  ///
  ResourceLo  = (ResourceLo < RecordLo) ? ResourceLo : RecordLo;
  ResourceHi  = (ResourceHi > RecordHi) ? ResourceHi : RecordHi;

  switch (Resource->hdr.RscType) {
    case MEM_RANGE:
    case MMIO_RANGE:
      Resource->mem.Base    = ResourceLo;
      Resource->mem.Length  = ResourceHi - ResourceLo;
      Resource->mem.RWXAttributes |= Record->mem.RWXAttributes;
      break;

    case IO_RANGE:
    case TRAPPED_IO_RANGE:
      Resource->io.Base   = (UINT16) ResourceLo;
      Resource->io.Length = (UINT16) (ResourceHi - ResourceLo);
      break;

    case PCI_CFG_RANGE:
      Resource->pci.Base    = (UINT16) ResourceLo;
      Resource->pci.Length  = (UINT16) (ResourceHi - ResourceLo);
      break;
  }
  ///
  /// Save record length before record get replaced as a result of
  /// erasure.
  ///
  RecordLength = Record->hdr.Length;
  ///
  /// Erase record
  /// End of data to move down is free space address.
  ///
  FromEndPtr = Area->FreeSpaceAddress;
  ///
  /// Start of data to move down is next record address
  ///
  FromStartPtr = (EFI_PHYSICAL_ADDRESS) Record + Record->hdr.Length;
  ///
  /// Address to move over is address of current record.
  ///
  CopyMem ((VOID *) Record, (VOID *) FromStartPtr, FromEndPtr - FromStartPtr);
  ///
  /// Adjust area values after we erase record.
  ///
  Area->FreeSize += RecordLength;
  Area->EndOfRscAddress -= RecordLength;
  Area->FreeSpaceAddress -= RecordLength;

  ///
  /// Don't adjust record address since after move it points to next
  /// record.
  ///
  return STS_CONTINUE_SEARCH;
}


/**
  Get Mseg Size

  @retval Size  Get Mseg Size
**/
UINT64
GetMsegSize (
  VOID
)
{
  TXT_INFO_HOB  *TxtHob;

  TxtHob  = NULL;

  ///
  /// Retrieve info from TXT HOB
  ///
  TxtHob = (TXT_INFO_HOB *)GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtHob == NULL) {
    return 0;
  }

  return TxtHob->Data.MsegSize;
}

/**
  Fill Mseg Base/Size to TxtHobInfo

  @param[in] Base  Mseg base address
  @param[in] Size  Mseg Size
**/
VOID
FillMseg (
  IN  UINT32         Base,
  IN  UINT32         Size
)
{
  TXT_INFO_HOB  *TxtHob;

  TxtHob  = NULL;

  ///
  /// Retrieve info from TXT HOB
  ///
  TxtHob = (TXT_INFO_HOB *)GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtHob == NULL) {
    return ;
  }

  TxtHob->Data.MsegBase = (EFI_PHYSICAL_ADDRESS)Base;
  TxtHob->Data.MsegSize = (UINT64)Size;
}

/**
  Fill Tseg Base/Size to TxtHobInfo

  @param[in] Base  Mseg base address
  @param[in] Size  Mseg Size
**/
VOID
FillTseg (
  IN  UINT32         Base,
  IN  UINT32         Size
)
{
  TXT_INFO_HOB  *TxtHob;

  TxtHob  = NULL;

  ///
  /// Retrieve info from TXT HOB
  ///
  TxtHob = (TXT_INFO_HOB *)GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtHob == NULL) {
    return ;
  }

  TxtHob->Data.TsegBase = (EFI_PHYSICAL_ADDRESS)Base;
  TxtHob->Data.TsegSize = (UINT64)Size;
}