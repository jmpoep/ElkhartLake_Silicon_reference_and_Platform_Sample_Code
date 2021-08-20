/** @file
  SMM PPAM support functions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include "SmmCpuFeatures.h"

#define TXT_EVTYPE_BASE                  0x400
#define TXT_EVTYPE_PPAM_HASH              (TXT_EVTYPE_BASE + 14)

#define RDWR_ACCS             3
#define FULL_ACCS             7

#pragma pack(1)
typedef struct {
  UINT8       Jmp; // 0xE9
  UINT32      Address;
} SMM_ENTRY_POINT_TAIL;
#pragma pack()

VOID
PpamSmiEntryPointEnd (
  VOID
  );

/**
  Setup SMM Protected Mode context for processor.

  @param  ProcessorNumber    The processor number.
  @param  SmBase             The SMBASE value of the processor.
  @param  StackAddress       Stack address of the processor.
  @param  GdtBase            Gdt table base address of the processor.
  @param  GdtSize            Gdt table size of the processor.
  @param  CodeSegment        Code segment value.
  @param  ProtModeIdt        Pointer to protected-mode IDT descriptor.
**/
VOID
SetupSmmProtectedModeContext(
  IN UINTN                    ProcessorNumber,
  IN UINT32                   SmBase,
  IN UINT32                   StackAddress,
  IN UINTN                    GdtBase,
  IN UINTN                    GdtSize,
  IN UINT16                   CodeSegment,
  IN IA32_DESCRIPTOR          *ProtModeIdt
  );

extern volatile UINT32                     gSmmFeatureSmiStack;
extern UINT32                              gSmmStackSize;
extern UINT32                              gSmmFeatureSmiCr3;
extern UINT32                              gProtModeIdtr;
extern UINT32                              gPMStackDesc[2];
extern IA32_DESCRIPTOR                     gSmmFeatureSmiHandlerIdtr;
extern IA32_PROT_DESCRIPTOR                gGdtDesc;
extern BOOLEAN                             mSmmProtectedModeEnable;

EFI_HANDLE  mPpamSmmCpuHandle = NULL;

BOOLEAN mLockLoadMonitor = FALSE;

//
// System Configuration Table pointing to PPAM Configuration Table
//
GLOBAL_REMOVE_IF_UNREFERENCED
EFI_SM_MONITOR_INIT_PROTOCOL mPpamSmMonitorInitProtocol = {
  PpamLoadMonitor,
  PpamAddPiResource,
  PpamDeletePiResource,
  PpamGetPiResource,
  PpamGetMonitorState,
};

#define   CPUID1_EDX_XD_SUPPORT      0x100000

//
// External global variables associated with SMI Handler Template
//
extern UINT32                              gPpamSmbase;
extern volatile UINT32                     gPpamSmiStack;
extern UINT32                              gPpamSmiCr3;
extern volatile UINT8                      gcPpamSmiHandlerTemplate[];
extern CONST UINT16                        gcPpamSmiHandlerSize;
extern BOOLEAN                             gPpamXdSupported;

//
// Variables used by SMI Handler
//
IA32_DESCRIPTOR  gPpamSmiHandlerIdtr;

//
// MSEG Base and Length in SMRAM
//
UINTN  mMsegBase = 0;
UINTN  mMsegSize = 0;

BOOLEAN  mPpamConfigurationTableInitialized = FALSE;
SMM_ENTRY_POINT_HEADER             *mSmmEntryPointHeader;
SMM_ENTRY_POINT_INFORMATION_TABLE  *mSmmEntryPointInfoTable;

/**
  Retieves MSEG information.

**/
VOID
GetMsegInfo (
  VOID
  )
{
  CPUID_VERSION_INFO_ECX  RegEcx;
  EFI_HOB_GUID_TYPE       *GuidHob;
  EFI_SMRAM_DESCRIPTOR    *SmramDescriptor;

  //
  // If CPU supports VMX, then determine SMRAM range for MSEG.
  //
  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &RegEcx.Uint32, NULL);
  if (RegEcx.Bits.VMX == 1) {
    GuidHob = GetFirstGuidHob (&gMsegSmramGuid);
    if (GuidHob != NULL) {
      DEBUG((DEBUG_INFO, "Found gMsegSmramGuid hob\n"));
      //
      // Retrieve MSEG location from MSEG SRAM HOB
      //
      SmramDescriptor = (EFI_SMRAM_DESCRIPTOR *) GET_GUID_HOB_DATA (GuidHob);
      if (SmramDescriptor->PhysicalSize > 0) {
        mMsegBase       = (UINTN)SmramDescriptor->CpuStart;
        mMsegSize       = (UINTN)SmramDescriptor->PhysicalSize;
      }
    } else if (PcdGet32 (PcdCpuMsegSize) > 0) {
      //
      // Allocate MSEG from SMRAM memory
      //
      mMsegBase = (UINTN)AllocatePages (EFI_SIZE_TO_PAGES (PcdGet32 (PcdCpuMsegSize)));
      if (mMsegBase > 0) {
        mMsegSize = ALIGN_VALUE (PcdGet32 (PcdCpuMsegSize), EFI_PAGE_SIZE);
      } else {
        DEBUG ((DEBUG_ERROR, "Not enough SMRAM resource to allocate MSEG size %08x\n", PcdGet32 (PcdCpuMsegSize)));
      }
    }
    if (mMsegBase > 0) {
      DEBUG ((DEBUG_INFO, "MsegBase: 0x%08x, MsegSize: 0x%08x\n", mMsegBase, mMsegSize));
    }
  }
}

/**
  Internal worker function that is called to complete CPU initialization at the
  end of SmmCpuFeaturesInitializeProcessor().

**/
VOID
FinishSmmCpuFeaturesInitializeProcessor (
  VOID
  )
{
  MSR_IA32_SMM_MONITOR_CTL_REGISTER  SmmMonitorCtl;

  //
  // Set MSEG Base Address in SMM Monitor Control MSR.
  //
  if (mMsegBase > 0) {
    SmmMonitorCtl.Uint64 = 0;
    SmmMonitorCtl.Bits.MsegBase = (UINT32)mMsegBase >> 12;
    SmmMonitorCtl.Bits.Valid = 1;
    AsmWriteMsr64 (MSR_IA32_SMM_MONITOR_CTL, SmmMonitorCtl.Uint64);
  }
}

/**
  SMM End Of Dxe event notification handler.

  PPAM support need patch AcpiRsdp in TXT_PROCESSOR_SMM_DESCRIPTOR.

  @param[in] Protocol   Points to the protocol's unique identifier.
  @param[in] Interface  Points to the interface instance.
  @param[in] Handle     The handle on which the interface was installed.

  @retval EFI_SUCCESS   Notification handler runs successfully.
**/
EFI_STATUS
EFIAPI
PpamSmmEndOfDxeEventNotify (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  )
{
  DEBUG ((DEBUG_INFO, "SmmEndOfDxeEventNotify\n"));

  mLockLoadMonitor = TRUE;

  return EFI_SUCCESS;
}

/**
  This function initializes the PPAM configuration table.
**/
VOID
PpamSmmConfigurationTableInit (
  VOID
  )
{
  EFI_STATUS    Status;
    VOID        *Registration;

  Status = gSmst->SmmInstallProtocolInterface (
                    &mPpamSmmCpuHandle,
                    &gEfiSmMonitorInitProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mPpamSmMonitorInitProtocol
                    );
  ASSERT_EFI_ERROR (Status);

  //
  //
  // Register SMM End of DXE Event
  //
  Status = gSmst->SmmRegisterProtocolNotify (
                    &gEfiSmmEndOfDxeProtocolGuid,
                    PpamSmmEndOfDxeEventNotify,
                    &Registration
                    );
  ASSERT_EFI_ERROR (Status);
}

/**
  Constructor for PPAM.
**/
VOID
PpamConstructor (
  VOID
  )
{
  EFI_STATUS  Status;
  VOID        *SmmEntryPointBuffer;
  UINTN       SmmEntryPointBufferSize;

  DEBUG ((DEBUG_INFO, "PpamConstructor\n"));
  //
  // Extract SmmEntryPoint binary from FV
  //
  SmmEntryPointBuffer = NULL;
  SmmEntryPointBufferSize = 0;

  Status = GetSectionFromAnyFv (
             PcdGetPtr(PcdSmmEntryPointBinFile),
             EFI_SECTION_RAW,
             0,
             &SmmEntryPointBuffer,
             &SmmEntryPointBufferSize
             );
  ASSERT_EFI_ERROR (Status);

  mSmmEntryPointHeader = (VOID *)(UINTN)SmmFeatureAllocateCodePages (EFI_SIZE_TO_PAGES(SmmEntryPointBufferSize));
  if (mSmmEntryPointHeader == NULL) {
    ASSERT(mSmmEntryPointHeader != NULL);
    return;
  }
  CopyMem ((VOID *)(UINTN)mSmmEntryPointHeader, SmmEntryPointBuffer, SmmEntryPointBufferSize);
  DEBUG ((DEBUG_INFO, "mSmmEntryPointHeader - 0x%x\n", mSmmEntryPointHeader));
  mSmmEntryPointInfoTable = (VOID *)((UINT8 *)mSmmEntryPointHeader + mSmmEntryPointHeader->InfoTableAddress);
  DEBUG ((DEBUG_INFO, "mSmmEntryPointInfoTable - 0x%x\n", mSmmEntryPointInfoTable));
  mSmmEntryPointHeader->InfoTableAddress = (UINT32)(UINTN)mSmmEntryPointInfoTable;

  gBS->FreePool ((VOID *)((UINTN)SmmEntryPointBuffer));
}

VOID
PatchSmmEntryPoint (
  IN VOID      *SmmEntryPointHeader,
  IN UINT8     Type,
  IN VOID      *Data,
  IN UINT8     DataSize
  )
{
  SMM_ENTRY_POINT_INFORMATION_ENTRY  *SmmInfoEntry;

  for (SmmInfoEntry = (VOID *)(mSmmEntryPointInfoTable + 1); ; SmmInfoEntry++) {
    if (SmmInfoEntry->Type == SMM_ENTRY_POINT_INFO_END) {
      break;
    }
    if (SmmInfoEntry->Type == Type) {
      ASSERT (SmmInfoEntry->DataSize == DataSize);
      CopyMem ((UINT8 *)SmmEntryPointHeader + SmmInfoEntry->DataOffset, Data, SmmInfoEntry->DataSize);
    }
  }
}

/**
  Return the size, in bytes, of a custom SMI Handler in bytes.  If 0 is
  returned, then a custom SMI handler is not provided by this library,
  and the default SMI handler must be used.

  @retval 0    Use the default SMI handler.
  @retval > 0  Use the SMI handler installed by SmmCpuFeaturesInstallSmiHandler()
               The caller is required to allocate enough SMRAM for each CPU to
               support the size of the custom SMI handler.
**/
UINTN
EFIAPI
SmmCpuFeaturesGetSmiHandlerSizePpam (
  VOID
  )
{
  //
  // Add 5 byte SMM_ENTRY_POINT_TAIL
  //
  return mSmmEntryPointInfoTable->SmmEntryPointSize + sizeof(SMM_ENTRY_POINT_TAIL);
}

/**
  Install a custom SMI handler for the CPU specified by CpuIndex.  This function
  is only called if SmmCpuFeaturesGetSmiHandlerSize() returns a size is greater
  than zero and is called by the CPU that was elected as monarch during System
  Management Mode initialization.

  @param[in] CpuIndex   The index of the CPU to install the custom SMI handler.
                        The value must be between 0 and the NumberOfCpus field
                        in the System Management System Table (SMST).
  @param[in] SmBase     The SMBASE address for the CPU specified by CpuIndex.
  @param[in] SmiStack   The stack to use when an SMI is processed by the
                        the CPU specified by CpuIndex.
  @param[in] StackSize  The size, in bytes, if the stack used when an SMI is
                        processed by the CPU specified by CpuIndex.
  @param[in] GdtBase    The base address of the GDT to use when an SMI is
                        processed by the CPU specified by CpuIndex.
  @param[in] GdtSize    The size, in bytes, of the GDT used when an SMI is
                        processed by the CPU specified by CpuIndex.
  @param[in] IdtBase    The base address of the IDT to use when an SMI is
                        processed by the CPU specified by CpuIndex.
  @param[in] IdtSize    The size, in bytes, of the IDT used when an SMI is
                        processed by the CPU specified by CpuIndex.
  @param[in] Cr3        The base address of the page tables to use when an SMI
                        is processed by the CPU specified by CpuIndex.
**/
VOID
EFIAPI
SmmCpuFeaturesInstallSmiHandlerPpam (
  IN UINTN   CpuIndex,
  IN UINT32  SmBase,
  IN VOID    *SmiStack,
  IN UINTN   StackSize,
  IN UINTN   GdtBase,
  IN UINTN   GdtSize,
  IN UINTN   IdtBase,
  IN UINTN   IdtSize,
  IN UINT32  Cr3
  )
{
  SMM_ENTRY_POINT_TAIL  *SmmEntryPointTail;

  DEBUG ((DEBUG_INFO, "SmmCpuFeaturesInstallSmiHandlerPpam (%d)\n", CpuIndex));

  if (mSmmProtectedModeEnable) {
    //
    // Initialize protected mode IDT
    //
    InitProtectedModeIdt (Cr3);
  }

  //
  // Initialize values in template before copy
  //
  gSmmFeatureSmiStack   = (UINT32)((UINTN)SmiStack + StackSize - sizeof (UINTN));
  gSmmStackSize         = (UINT32)(StackSize - sizeof (UINTN));
  gSmmFeatureSmiCr3     = Cr3;
  gSmmFeatureSmiHandlerIdtr.Base = IdtBase;
  gSmmFeatureSmiHandlerIdtr.Limit = (UINT16)(IdtSize - 1);
  gGdtDesc.Base = (UINT32)GdtBase;
  gGdtDesc.Limit = (UINT16)(GdtSize - 1);

  //
  // Set the value at the top of the CPU stack to the CPU Index
  //
  *(UINTN*)(UINTN)gSmmFeatureSmiStack = CpuIndex;
  gPMStackDesc[0] = gSmmFeatureSmiStack;
  gSmmSupovrStateLockData = 0;

  //
  // Patch EntryPoint based upon InfoTable Entry
  //
  PatchSmmEntryPoint (mSmmEntryPointHeader, SMM_ENTRY_POINT_INFO_GDT, &gGdtDesc, sizeof(gGdtDesc));
  PatchSmmEntryPoint (mSmmEntryPointHeader, SMM_ENTRY_POINT_INFO_IDT, &gSmmFeatureSmiHandlerIdtr, sizeof(gSmmFeatureSmiHandlerIdtr));
  PatchSmmEntryPoint (mSmmEntryPointHeader, SMM_ENTRY_POINT_INFO_CR3, &gSmmFeatureSmiCr3, sizeof(gSmmFeatureSmiCr3));
  PatchSmmEntryPoint (mSmmEntryPointHeader, SMM_ENTRY_POINT_INFO_SUPOVR_STATE_LOCK, &gSmmSupovrStateLockData, sizeof(gSmmSupovrStateLockData));
  PatchSmmEntryPoint (mSmmEntryPointHeader, SMM_ENTRY_POINT_INFO_STACK, (VOID *)&gSmmFeatureSmiStack, sizeof(gSmmFeatureSmiStack));
  PatchSmmEntryPoint (mSmmEntryPointHeader, SMM_ENTRY_POINT_INFO_STACK_SIZE, &gSmmStackSize, sizeof(gSmmStackSize));

  //
  // Copy template to CPU specific SMI handler location
  //
  CopyMem (
    (VOID*)((UINTN)SmBase + SMM_HANDLER_OFFSET),
    (VOID*)mSmmEntryPointHeader,
    mSmmEntryPointInfoTable->SmmEntryPointSize
    );

  //
  // Patch SmmEntryPointTail: JMP PpamSmiEntryPointEnd
  //
  SmmEntryPointTail = (VOID*)((UINTN)SmBase + SMM_HANDLER_OFFSET + mSmmEntryPointInfoTable->SmmEntryPointSize);
  SmmEntryPointTail->Jmp = 0xE9;
  SmmEntryPointTail->Address = (UINT32)((UINTN)PpamSmiEntryPointEnd - ((UINTN)SmBase + SMM_HANDLER_OFFSET + mSmmEntryPointInfoTable->SmmEntryPointSize + sizeof(SMM_ENTRY_POINT_TAIL)));

  if (mSmmProtectedModeEnable) {
    //
    // Prepare for the SMMSEG structure
    //
    SetupSmmProtectedModeContext (
      CpuIndex,
      (UINT32)SmBase,
      gSmmFeatureSmiStack,
      GdtBase,
      GdtSize,
      SMMSEG_PROTECT_MODE_CODE_SEGMENT,
      (IA32_DESCRIPTOR *)(UINTN)gProtModeIdtr
      );
  }

  if (!mPpamConfigurationTableInitialized) {
    PpamSmmConfigurationTableInit ();
    mPpamConfigurationTableInitialized = TRUE;
  }
}

/**

  Get PPAM state.

  @return PPAM state

**/
EFI_SM_MONITOR_STATE
EFIAPI
PpamGetMonitorState (
  VOID
  )
{
  return 0;
}

/**

  Add resources in list to database. Allocate new memory areas as needed.

  @param ResourceList  A pointer to resource list to be added
  @param NumEntries    Optional number of entries.
                       If 0, list must be terminated by END_OF_RESOURCES.

  @retval EFI_SUCCESS            If resources are added
  @retval EFI_INVALID_PARAMETER  If nested procedure detected resource failer
  @retval EFI_OUT_OF_RESOURCES   If nested procedure returned it and we cannot allocate more areas.

**/
EFI_STATUS
EFIAPI
PpamAddPiResource (
  IN  STM_RSC    *ResourceList,
  IN  UINT32      NumEntries OPTIONAL
  )
{
  return EFI_UNSUPPORTED;
}

/**

  Delete resources in list to database.

  @param ResourceList  A pointer to resource list to be deleted
                       NULL means delete all resources.
  @param NumEntries    Optional number of entries.
                       If 0, list must be terminated by END_OF_RESOURCES.

  @retval EFI_SUCCESS            If resources are deleted
  @retval EFI_INVALID_PARAMETER  If nested procedure detected resource failer

**/
EFI_STATUS
EFIAPI
PpamDeletePiResource (
  IN  STM_RSC    *ResourceList,
  IN  UINT32      NumEntries OPTIONAL
  )
{
  return EFI_UNSUPPORTED;
}

/**

  Get BIOS resources.

  @param ResourceList  A pointer to resource list to be filled
  @param ResourceSize  On input it means size of resource list input.
                       On output it means size of resource list filled,
                       or the size of resource list to be filled if size of too small.

  @retval EFI_SUCCESS            If resources are returned.
  @retval EFI_BUFFER_TOO_SMALL   If resource list buffer is too small to hold the whole resources.

**/
EFI_STATUS
EFIAPI
PpamGetPiResource (
  OUT    STM_RSC *ResourceList,
  IN OUT UINT32  *ResourceSize
  )
{
  return EFI_UNSUPPORTED;
}

/**

  Set valid bit for MSEG MSR.

  @param Buffer Ap function buffer. (not used)

**/
VOID
EFIAPI
EnableMsegMsr (
  IN VOID  *Buffer
  )
{
  MSR_IA32_SMM_MONITOR_CTL_REGISTER  SmmMonitorCtl;

  SmmMonitorCtl.Uint64 = AsmReadMsr64 (MSR_IA32_SMM_MONITOR_CTL);
  SmmMonitorCtl.Bits.Valid = 1;
  AsmWriteMsr64 (MSR_IA32_SMM_MONITOR_CTL, SmmMonitorCtl.Uint64);
}

/**

  Get 4K page aligned VMCS size.

  @return 4K page aligned VMCS size

**/
UINT32
GetVmcsSize (
  VOID
  )
{
  MSR_IA32_VMX_BASIC_REGISTER  VmxBasic;

  //
  // Read VMCS size and and align to 4KB
  //
  VmxBasic.Uint64 = AsmReadMsr64 (MSR_IA32_VMX_BASIC);
  return ALIGN_VALUE (VmxBasic.Bits.VmcsSize, SIZE_4KB);
}

/**

  Check PPAM image size.

  @param PpamImage      PPAM image
  @param PpamImageSize  PPAM image size

  @retval TRUE  check pass
  @retval FALSE check fail
**/
BOOLEAN
PpamCheckPpamImage (
  IN EFI_PHYSICAL_ADDRESS PpamImage,
  IN UINTN                PpamImageSize
  )
{
  UINTN                     MinMsegSize;
  PPAM_HEADER               *PpamHeader;
  IA32_VMX_MISC_REGISTER    VmxMiscMsr;

  //
  // Check to see if PPAM image is compatible with CPU
  //
  PpamHeader = (PPAM_HEADER *)(UINTN)PpamImage;
  VmxMiscMsr.Uint64 = AsmReadMsr64 (MSR_IA32_VMX_MISC);
  if (PpamHeader->HwPpamHdr.HardwareHeaderRevision != VmxMiscMsr.Bits.MsegRevisionIdentifier) {
    DEBUG ((DEBUG_ERROR, "PPAM Image not compatible with CPU\n"));
    DEBUG ((DEBUG_ERROR, "  PpamHeader->HwPpamHdr.HardwareHeaderRevision = %08x\n", PpamHeader->HwPpamHdr.HardwareHeaderRevision));
    DEBUG ((DEBUG_ERROR, "  VmxMiscMsr.Bits.MsegRevisionIdentifier = %08x\n", VmxMiscMsr.Bits.MsegRevisionIdentifier));
    return FALSE;
  }

  //
  // Get Minimal required Mseg size
  //
  MinMsegSize = (EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (PpamHeader->SwPpamHdr.StaticImageSize)) +
                 PpamHeader->SwPpamHdr.AdditionalDynamicMemorySize +
                 (PpamHeader->SwPpamHdr.PerProcDynamicMemorySize + GetVmcsSize ()) * gSmst->NumberOfCpus);
  if (MinMsegSize < PpamImageSize) {
    MinMsegSize = PpamImageSize;
  }

  if (PpamHeader->HwPpamHdr.Cr3Offset >= PpamHeader->SwPpamHdr.StaticImageSize) {
    //
    // We will create page table, just in case that SINIT does not create it.
    //
    if (MinMsegSize < PpamHeader->HwPpamHdr.Cr3Offset + EFI_PAGES_TO_SIZE(6)) {
      MinMsegSize = PpamHeader->HwPpamHdr.Cr3Offset + EFI_PAGES_TO_SIZE(6);
    }
  }

  //
  // Check if it exceeds MSEG size
  //
  if (MinMsegSize > mMsegSize) {
    DEBUG ((DEBUG_ERROR, "MSEG too small.  Min MSEG Size = %08x  Current MSEG Size = %08x\n", MinMsegSize, mMsegSize));
    DEBUG ((DEBUG_ERROR, "  PpamHeader->SwPpamHdr.StaticImageSize             = %08x\n", PpamHeader->SwPpamHdr.StaticImageSize));
    DEBUG ((DEBUG_ERROR, "  PpamHeader->SwPpamHdr.AdditionalDynamicMemorySize = %08x\n", PpamHeader->SwPpamHdr.AdditionalDynamicMemorySize));
    DEBUG ((DEBUG_ERROR, "  PpamHeader->SwPpamHdr.PerProcDynamicMemorySize    = %08x\n", PpamHeader->SwPpamHdr.PerProcDynamicMemorySize));
    DEBUG ((DEBUG_ERROR, "  VMCS Size                                         = %08x\n", GetVmcsSize ()));
    DEBUG ((DEBUG_ERROR, "  Max CPUs                                          = %08x\n", gSmst->NumberOfCpus));
    DEBUG ((DEBUG_ERROR, "  PpamHeader->HwPpamHdr.Cr3Offset                   = %08x\n", PpamHeader->HwPpamHdr.Cr3Offset));
    return FALSE;
  }

  return TRUE;
}

/**

  Load PPAM image to MSEG.

  @param PpamImage      PPAM image
  @param PpamImageSize  PPAM image size

**/
VOID
PpamLoadPpamImage (
  IN EFI_PHYSICAL_ADDRESS PpamImage,
  IN UINTN                PpamImageSize
  )
{
  MSR_IA32_SMM_MONITOR_CTL_REGISTER  SmmMonitorCtl;
  UINT32                             MsegBase;
  PPAM_HEADER                        *PpamHeader;

  //
  // Get MSEG base address from MSR_IA32_SMM_MONITOR_CTL
  //
  SmmMonitorCtl.Uint64 = AsmReadMsr64 (MSR_IA32_SMM_MONITOR_CTL);
  MsegBase = SmmMonitorCtl.Bits.MsegBase << 12;

  //
  // Zero all of MSEG base address
  //
  ZeroMem ((VOID *)(UINTN)MsegBase, mMsegSize);

  //
  // Copy PPAM Image into MSEG
  //
  CopyMem ((VOID *)(UINTN)MsegBase, (VOID *)(UINTN)PpamImage, PpamImageSize);

  //
  // PPAM Header is at the beginning of the PPAM Image
  //
  PpamHeader = (PPAM_HEADER *)(UINTN)PpamImage;

  PpamGen4GPageTable ((UINTN)MsegBase + PpamHeader->HwPpamHdr.Cr3Offset);
}

/**

  Load PPAM image to MSEG.

  @param PpamImage      PPAM image
  @param PpamImageSize  PPAM image size

  @retval EFI_SUCCESS            Load PPAM to MSEG successfully
  @retval EFI_ALREADY_STARTED    PPAM image is already loaded to MSEG
  @retval EFI_BUFFER_TOO_SMALL   MSEG is smaller than minimal requirement of PPAM image
  @retval EFI_UNSUPPORTED        MSEG is not enabled

**/
EFI_STATUS
EFIAPI
PpamLoadMonitor (
  IN EFI_PHYSICAL_ADDRESS PpamImage,
  IN UINTN                PpamImageSize
  )
{
  MSR_IA32_SMM_MONITOR_CTL_REGISTER  SmmMonitorCtl;

  if (mLockLoadMonitor) {
    return EFI_ACCESS_DENIED;
  }

  SmmMonitorCtl.Uint64 = AsmReadMsr64 (MSR_IA32_SMM_MONITOR_CTL);
  if (SmmMonitorCtl.Bits.MsegBase == 0) {
    return EFI_UNSUPPORTED;
  }

  if (!PpamCheckPpamImage (PpamImage, PpamImageSize)) {
    return EFI_BUFFER_TOO_SMALL;
  }

  PpamLoadPpamImage (PpamImage, PpamImageSize);

  return EFI_SUCCESS;
}
