/** @file
  This file contains an implementation of the function call interfaces
  required by the main TXT PEIM file. Hopefully, future platform porting
  tasks will be mostly limited to modifying the functions in this file.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include <Library/TxtPeiLib.h>
#include <Library/CpuCommonLib.h>
#include <Library/TxtLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <PchResetPlatformSpecific.h>
#include <Library/PmcLib.h>
#include <Library/LocalApicLib.h>
#include <Ppi/MpServices.h>


/**
  This routine initializes and collects all PPIs and data required
  by the routines in this file.

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @exception EFI_UNSUPPORTED   - If any of the required PPIs or data are unavailable
  @retval EFI_SUCCESS       - In all cases not listed above
**/
EFI_STATUS
InitializeTxtPeiLib (
  IN TXT_INFO_HOB **TxtInfoHob
  )
{
  EFI_STATUS Status;
  UINT32     Ia32ApicBase;

  ///
  /// Find TxtInfoHob by platform code
  ///
  Status = CreateTxtInfoHob (TxtInfoHob);

  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "TXTPEI: TXT Info Hob not found or TXT is not supported.\n"));
    return EFI_UNSUPPORTED;
  }
  ///
  /// Print out the TxtInfo HOB if TXT_DEBUG_INFO is set
  ///
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtInfoHob passed from platform as:\n"));
  DEBUG ((DEBUG_INFO, "TXTPEI: ChipsetIsTxtCapable   = %x\n", (*TxtInfoHob)->Data.ChipsetIsTxtCapable));
  DEBUG ((DEBUG_INFO, "TXTPEI: ProcessorIsTxtCapable = %x\n", (*TxtInfoHob)->Data.ProcessorIsTxtCapable));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtMode               = %x\n", (*TxtInfoHob)->Data.TxtMode));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtAcheckRequest      = %x\n", (*TxtInfoHob)->Data.TxtAcheckRequest));
  DEBUG ((DEBUG_INFO, "TXTPEI: ResetAux              = %x\n", (*TxtInfoHob)->Data.ResetAux));
  DEBUG ((DEBUG_INFO, "TXTPEI: AcpiBase              = %x\n", (*TxtInfoHob)->Data.AcpiBase));
  DEBUG ((DEBUG_INFO, "TXTPEI: SinitMemorySize       = %x\n", (*TxtInfoHob)->Data.SinitMemorySize));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtHeapMemorySize     = %x\n", (*TxtInfoHob)->Data.TxtHeapMemorySize));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtDprMemoryBase      = %x\n", (*TxtInfoHob)->Data.TxtDprMemoryBase));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtDprMemorySize      = %x\n", (*TxtInfoHob)->Data.TxtDprMemorySize));
  DEBUG ((DEBUG_INFO, "TXTPEI: BiosAcmBase           = %x\n", (*TxtInfoHob)->Data.BiosAcmBase));
  DEBUG ((DEBUG_INFO, "TXTPEI: BiosAcmSize           = %x\n", (*TxtInfoHob)->Data.BiosAcmSize));
  DEBUG ((DEBUG_INFO, "TXTPEI: SinitAcmBase          = %x\n", (*TxtInfoHob)->Data.SinitAcmBase));
  DEBUG ((DEBUG_INFO, "TXTPEI: SinitAcmSize          = %x\n", (*TxtInfoHob)->Data.SinitAcmSize));
  DEBUG ((DEBUG_INFO, "TXTPEI: TgaSize               = %x\n", (*TxtInfoHob)->Data.TgaSize));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtLcpPdBase          = %x\n", (*TxtInfoHob)->Data.TxtLcpPdBase));
  DEBUG ((DEBUG_INFO, "TXTPEI: TxtLcpPdSize          = %x\n", (*TxtInfoHob)->Data.TxtLcpPdSize));
  DEBUG ((DEBUG_INFO, "TXTPEI: Flags                 = %x\n", (*TxtInfoHob)->Data.Flags));
  DEBUG ((DEBUG_INFO, "TXTPEI: ApStartupBase         = %x\n", (*TxtInfoHob)->Data.ApStartupBase));

  ///
  /// Check if platform specify BIOS ACM address by itself, BIOS ACM address must be 4K alignment in FLASH address space
  ///
  if ((*TxtInfoHob)->Data.BiosAcmBase != 0) {
    ///
    /// Check BIOS ACM is 4K alignment or not
    ///
    if (((*TxtInfoHob)->Data.BiosAcmBase & 0xFFF) != 0) {
      DEBUG ((DEBUG_WARN, "TXTPEI: BIOS ACM is not 4K aligned, force TxtMode=0 and unloaded!!\n"));
      (*TxtInfoHob)->Data.TxtMode = 0;
      return EFI_UNSUPPORTED;
    }
  } else {
    DEBUG ((DEBUG_ERROR, "TXTPEI: BIOS ACM not found, force TxtMode=0 and unloaded!\n"));
    (*TxtInfoHob)->Data.TxtMode = 0;
    return EFI_UNSUPPORTED;
  }
  ///
  /// Check ACM is matched to chipset or not, if not, disable TXT and return EFI_UNLOAD_IMAGE
  ///
  if (!CheckTxtAcmMatch ((ACM_HEADER*)(UINTN)((*TxtInfoHob)->Data.BiosAcmBase))) {
    DEBUG ((DEBUG_ERROR, "TXTPEI: BIOS ACM is not matched to chipset!! Force TxtMode=0 and unloaded!!\n"));
    (*TxtInfoHob)->Data.TxtMode = 0;
    return EFI_UNSUPPORTED;
  }

  /// Read ACM size from ACM header
  (*TxtInfoHob)->Data.BiosAcmSize = ((ACM_HEADER*)(UINTN)((*TxtInfoHob)->Data.BiosAcmBase))->Size << 2;

  ///
  /// Check if platform specify AP starup address
  ///
  if ((*TxtInfoHob)->Data.ApStartupBase == 0) {
    ///
    /// Get AP startup base from TxtInfoHob provided by platform code
    ///
    DEBUG ((DEBUG_INFO, "TXTPEI: AP Startup location not found\n"));
  }

  ///
  /// Initialize local APIC
  ///
  if ((((AsmReadMsr64 (MSR_IA32_APIC_BASE)) & (BIT11 + BIT10)) == BIT11 + BIT10)) {
    AsmWriteMsr64 (MSR_IA32_X2APIC_SIVR, 0x1FF);
  } else {
    ///
    /// Determine address of Local APIC
    ///
    Ia32ApicBase  = ((UINT32) AsmReadMsr64 (MSR_IA32_APIC_BASE)) & BASE_ADDR_MASK;
    *(UINT32 *) (Ia32ApicBase + APIC_SPURIOUS_VECTOR_REGISTER) = 0x1FF;
  }

  ///
  /// Make sure none of our pointers are still NULL
  ///
  if (!((*TxtInfoHob)->Data.BiosAcmBase)) {
    (*TxtInfoHob)->Data.TxtMode = 0;
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
  Determines whether or not the current processor is TXT Capable.

  @retval TRUE          - If the current processor supports TXT
  @retval FALSE         - If the current processor does not support TXT
**/
BOOLEAN
IsTxtProcessor (
  VOID
  )
{
  CPUID_VERSION_INFO_ECX Ecx;

  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);

  return (BOOLEAN) (Ecx.Bits.SMX == 1);
}

/**
  Determines whether or not the current chipset is TXT Capable.

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If the current chipset supports TXT
  @retval FALSE         - If the current chipset doesn't supports TXT
**/
BOOLEAN
IsTxtChipset (
  VOID
  )
{
  BOOLEAN TxtCapable;
  UINT32  Data32;

  TxtCapable  = FALSE;
  Data32      = CheckSmxCapabilities ();

  if ((Data32 & BIT0) != 0) {
    TxtCapable = TRUE;
  } else {
    TxtCapable = FALSE;
  }

  return TxtCapable;
}

/**
  Determines whether TXT is enabled by platform setting

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If TXT is enabled by platform setting
  @retval FALSE         - If TXT is disabled by platform setting
**/
BOOLEAN
IsTxtEnabled (
  IN TXT_INFO_HOB *TxtInfoHob
  )
{
  if (TxtInfoHob == NULL) {
    return FALSE;
  }
  return (BOOLEAN)TxtInfoHob->Data.TxtMode;
}

/**
  Determines whether Alias Check Request is enabled by platform setting

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If ACHECK REQUEST is enabled by platform setting
  @retval FALSE         - If ACHECK REQUEST is disabled by platform setting
**/
BOOLEAN
IsAcheckRequested (
  IN TXT_INFO_HOB *TxtInfoHob
  )
{
  if (TxtInfoHob == NULL) {
    return FALSE;
  }

  return (BOOLEAN) (TxtInfoHob->Data.TxtAcheckRequest);
}

/**
  Determines ACM is matched to chipset or not

  @param[in] TxtContextDataPtr         - Point to TXT_PEI_LIB_CONTEXT structure
  @param[in] BiosAcmBase  - A pointer to BIOS ACM location

  @retval TRUE          - BIOS ACM is matched to chipset
  @retval FALSE         - BIOS ACM is NOT matched to chipset
**/
BOOLEAN
CheckTxtAcmMatch (
  IN ACM_HEADER          *BiosAcmBase
  )
{
  BOOLEAN ChipsetIsProduction;
  BOOLEAN BiosAcmIsProduction;

  if (BiosAcmBase == NULL) {
    return FALSE;

  }
  ///
  /// Initializing ChipsetIsProduction default value
  ///
  ChipsetIsProduction = (*(UINT32 *) (TXT_PUBLIC_BASE + 0x200) & BIT31) ? TRUE : FALSE;

  ///
  /// Check ACM is production or not
  ///
  BiosAcmIsProduction = (BiosAcmBase->ModuleId & BIT31) ? FALSE : TRUE;

  return ChipsetIsProduction == BiosAcmIsProduction;
}

/**
  Create TXT Info HOB

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS   - If TXT Info Hob is found
  @exception EFI_NOT_FOUND - If TXT Info Hob is not found
  @exception EFI_UNSUPPORTED - If the platform is not TXT capable.
**/
EFI_STATUS
CreateTxtInfoHob (
  IN TXT_INFO_HOB **TxtInfoHob
  )
{
  EFI_STATUS                   Status;
  SI_PREMEM_POLICY_PPI         *SiPreMemPolicy;
  CPU_SECURITY_PREMEM_CONFIG   *CpuSecurityPreMemConfig;
  CPU_TXT_PREMEM_CONFIG        *CpuTxtPreMemConfig;

  *TxtInfoHob = NULL;
  //
  // Get TxtInfoHob if it is already present, then this is the reinitalize, just reload the hob and exit
  //
  *TxtInfoHob = (TXT_INFO_HOB *) GetFirstGuidHob (&gTxtInfoHobGuid);
  if (*TxtInfoHob != NULL) {
    return EFI_SUCCESS;
  }
  ///
  /// Locate Cpu policy ppi to initialized.
  ///
  Status = PeiServicesLocatePpi (
                  &gSiPreMemPolicyPpiGuid,
                  0,
                  NULL,
                  (VOID **) &SiPreMemPolicy
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gCpuTxtPreMemConfigGuid, (VOID *) &CpuTxtPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  ///
  /// Create hob for storing TXT data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (TXT_INFO_HOB),
             (VOID **) TxtInfoHob
             );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  (*TxtInfoHob)->EfiHobGuidType.Name = gTxtInfoHobGuid;
  ///
  /// Initiate Txt Info Hob
  ///
  ZeroMem (&((*TxtInfoHob)->Data), sizeof (TXT_INFO_DATA));

  (*TxtInfoHob)->Data.ChipsetIsTxtCapable = IsTxtChipset ();
  (*TxtInfoHob)->Data.ProcessorIsTxtCapable = IsTxtProcessor ();
  if (CpuSecurityPreMemConfig->Txt == 1) {
    (*TxtInfoHob)->Data.TxtMode = 1;
  }


  (*TxtInfoHob)->Data.AcpiBase           = PmcGetAcpiBase ();
  (*TxtInfoHob)->Data.TxtAcheckRequest   = (BOOLEAN) CpuSecurityPreMemConfig->TxtAcheckRequest;
  (*TxtInfoHob)->Data.ResetAux           = (BOOLEAN) CpuSecurityPreMemConfig->ResetAux;
  (*TxtInfoHob)->Data.SinitMemorySize    = (UINT64) CpuTxtPreMemConfig->SinitMemorySize;
  (*TxtInfoHob)->Data.TxtHeapMemorySize  = (UINT64) CpuTxtPreMemConfig->TxtHeapMemorySize;
  (*TxtInfoHob)->Data.TxtDprMemoryBase   = CpuTxtPreMemConfig->TxtDprMemoryBase;
  (*TxtInfoHob)->Data.TxtDprMemorySize   = (UINT64) CpuTxtPreMemConfig->TxtDprMemorySize;
  (*TxtInfoHob)->Data.BiosAcmBase        = CpuTxtPreMemConfig->BiosAcmBase;
  (*TxtInfoHob)->Data.BiosAcmSize        = (UINT64) CpuTxtPreMemConfig->BiosAcmSize;
  (*TxtInfoHob)->Data.TgaSize            = (UINT64) CpuTxtPreMemConfig->TgaSize;
  (*TxtInfoHob)->Data.TxtLcpPdBase       = CpuTxtPreMemConfig->TxtLcpPdBase;
  (*TxtInfoHob)->Data.TxtLcpPdSize       = CpuTxtPreMemConfig->TxtLcpPdSize;
  (*TxtInfoHob)->Data.ApStartupBase      = CpuTxtPreMemConfig->ApStartupBase;
  (*TxtInfoHob)->Data.Flags             |= (UINT64)CpuTxtPreMemConfig->IsTPMPresence;

  if ((*TxtInfoHob)->Data.BiosAcmBase != 0) {
    //
    // Parse the ACM header. Locate the ACM Info Table.
    // Get the ACM major/minor version
    //
    ACM_HEADER *AcmHeader = (ACM_HEADER*)(UINTN)((*TxtInfoHob)->Data.BiosAcmBase);
    UINT8 *AcmPtr = (UINT8 *)(AcmHeader + 1);
    AcmPtr += AcmHeader->KeySize * 4;
    if (AcmHeader->HeaderVersion < ACM_HEADER_VERSION_3) {
      AcmPtr += 4;
      AcmPtr += ACM_PKCS_1_5_RSA_SIGNATURE_SHA256_SIZE;
    } else {
      AcmPtr += ACM_PKCS_1_5_RSA_SIGNATURE_SHA384_SIZE;
    }
    AcmPtr += AcmHeader->ScratchSize * 4;

    //
    // Extract ACM Info Table version numbers
    //
    ACM_INFO_TABLE *AcmInfoTable = (ACM_INFO_TABLE *)AcmPtr;
    if (CompareGuid(&(AcmInfoTable->Guid), &gTxtAcmInfoTableGuid)) {
      (*TxtInfoHob)->Data.AcmMajorVersion = AcmInfoTable->AitRevision[0];
      (*TxtInfoHob)->Data.AcmMinorVersion = AcmInfoTable->AitRevision[1];
      (*TxtInfoHob)->Data.AcmRevision = AcmInfoTable->AitRevision[2];
    }
  }

  return EFI_SUCCESS;
}

/**
  Add extened elements to BiosOsData

  @param[in] TxtDxeCtx      - A pointer to an initialized TXT DXE Context data structure
  @param[in] Type        - The element's type
  @param[in] Buffer      - A pointer to buffer which need to append the element
  @param[in] Size        - return the size of the appened element.
**/
VOID
AppendElement (
  IN TXT_INFO_HOB         *TxtInfoHob,
  IN UINT32               Type,
  IN VOID                 *Buffer,
  OUT UINT32              *Size
  )
{
  VOID        *Element;
  UINT32      NumberOfAcm;
  UINT64      *AcmBase;
  EFI_STATUS  Status;
  NumberOfAcm = 1;
  AcmBase     = NULL;
  Element     = NULL;
  *Size       = 0;
  switch (Type) {
    case HEAP_EXTDATA_TYPE_BIOS_SPEC_VER:
      ///
      /// Fill BIOS spec ver element
      ///
      Status = PeiServicesAllocatePool (sizeof (HEAP_BIOS_SPEC_VER_ELEMENT),&Element);
      ASSERT_EFI_ERROR(Status);

      if (Element != NULL) {
        *Size = sizeof (HEAP_BIOS_SPEC_VER_ELEMENT);
        ((HEAP_BIOS_SPEC_VER_ELEMENT *) Element)->Header.Type     = HEAP_EXTDATA_TYPE_BIOS_SPEC_VER;
        ((HEAP_BIOS_SPEC_VER_ELEMENT *) Element)->Header.Size     = sizeof (HEAP_BIOS_SPEC_VER_ELEMENT);
        ((HEAP_BIOS_SPEC_VER_ELEMENT *) Element)->SpecVerMajor    = TXT_BIOS_SPEC_VER_MAJOR;
        ((HEAP_BIOS_SPEC_VER_ELEMENT *) Element)->SpecVerMinor    = TXT_BIOS_SPEC_VER_MINOR;
        ((HEAP_BIOS_SPEC_VER_ELEMENT *) Element)->SpecVerRevision = TXT_BIOS_SPEC_VER_REVISION;
      }
      break;

    case HEAP_EXTDATA_TYPE_BIOSACM:
      ///
      /// Fill BIOS ACM element
      ///
      Status = PeiServicesAllocatePool (sizeof (HEAP_BIOSACM_ELEMENT) + NumberOfAcm * sizeof (UINT64),&Element);
      ASSERT_EFI_ERROR(Status);

      if (Element != NULL) {
        *Size = sizeof (HEAP_BIOSACM_ELEMENT) + sizeof (UINT64) * NumberOfAcm;
        ((HEAP_BIOSACM_ELEMENT *) Element)->Header.Type = HEAP_EXTDATA_TYPE_BIOSACM;
        ((HEAP_BIOSACM_ELEMENT *) Element)->Header.Size = sizeof (HEAP_BIOSACM_ELEMENT) + NumberOfAcm * sizeof (UINT64);
        ((HEAP_BIOSACM_ELEMENT *) Element)->NumAcms     = NumberOfAcm;
        AcmBase = (UINT64 *) ((UINTN) Element + sizeof (HEAP_BIOSACM_ELEMENT));
        *AcmBase = TxtInfoHob->Data.BiosAcmBase;
      }
      break;

    case HEAP_EXTDATA_TYPE_END:
      ///
      /// Fill end type element
      ///
      Status = PeiServicesAllocatePool (sizeof (HEAP_EXT_DATA_ELEMENT),&Element);
      ASSERT_EFI_ERROR(Status);

      if (Element != NULL) {
        *Size = sizeof (HEAP_EXT_DATA_ELEMENT);
        ((HEAP_EXT_DATA_ELEMENT *) Element)->Type = HEAP_EXTDATA_TYPE_END;
        ((HEAP_EXT_DATA_ELEMENT *) Element)->Size = sizeof (HEAP_EXT_DATA_ELEMENT);
      }
      break;

    default:
      break;
  }

  if (Element != NULL) {
    CopyMem (Buffer, Element, *Size);
  }
}

/**
  Allocates 1 MB of 1MB-aligned memory for use as TXT Device Memory.  Records
  the location of TXT Device Memory in TXT Chipset registers and then adds
  programming instructions for these registers into BootScript.

  @param[in] TxtDxeCtx      - A pointer to an initialized TXT DXE Context data structure

  @retval EFI_SUCCESS     - TXT Device memory has been successfully initialized.
  @exception EFI_UNSUPPORTED - TXT Device memory not available.
**/
EFI_STATUS
SetupTxtDeviceMemory (
  IN TXT_INFO_HOB *TxtInfoHob,
  IN UINTN        CpuCount
  )
{
  UINTN                       TopAddr;
  UINTN                       *Ptr;
  UINT64                      Value64;
  UINT32                      Value32;
  UINTN                       TxtHeapMemoryBase;
  UINTN                       TxtSinitMemoryBase;
  BOOLEAN                     Locked;
  BIOS_OS_DATA_REGION         *BiosOsDataRegion;
  TXT_INFO_DATA               *TxtInfoData;
  UINT8                       *Ptr8;

  DEBUG ((DEBUG_INFO, "TXTPEI::SetupTxtDeviceMemory\n"));

  TxtHeapMemoryBase         = 0;
  TxtSinitMemoryBase        = 0;
  Locked                    = FALSE;
  Ptr8                      = NULL;
  Value32                   = 0;

  TxtInfoData         = &(TxtInfoHob->Data);

  if ((TxtInfoData == 0) ||
      (TxtInfoData->TxtDprMemoryBase == 0) ||
      (TxtInfoData->TxtDprMemorySize == 0) ||
      (TxtInfoData->TxtHeapMemorySize == 0) ||
      (TxtInfoData->SinitMemorySize == 0)
      ) {

  DEBUG ((DEBUG_ERROR, "SetupTxtDeviceMemory : SinitMemorySize = 0x%x\n", TxtInfoData->SinitMemorySize));
  DEBUG ((DEBUG_ERROR, "SetupTxtDeviceMemory : TxtHeapMemorySize = 0x%x\n", TxtInfoData->TxtHeapMemorySize));
  DEBUG ((DEBUG_ERROR, "SetupTxtDeviceMemory : TxtDprMemoryBase = 0x%x\n", TxtInfoData->TxtDprMemoryBase));
  DEBUG ((DEBUG_ERROR, "SetupTxtDeviceMemory : TxtDprMemorySize = 0x%x\n", TxtInfoData->TxtDprMemorySize));

    return EFI_UNSUPPORTED;
  } else {
    ///
    /// Use address passed from PEI
    ///
    TopAddr             = (UINTN) (TxtInfoData->TxtDprMemoryBase + TxtInfoData->TxtDprMemorySize);

    TxtHeapMemoryBase   = (UINTN) (TopAddr - TxtInfoData->TxtHeapMemorySize);

    TxtSinitMemoryBase  = (UINTN) (TxtHeapMemoryBase - TxtInfoData->SinitMemorySize);
  }

  ASSERT ((TopAddr & 0x0FFFFF) == 0);

  ///
  /// DPR registers
  ///
  Ptr   = (UINTN *) (UINTN) (TXT_PUBLIC_BASE + TXT_DPR_SIZE_REG_OFF);
  Value64 = RShiftU64 (TxtInfoData->TxtDprMemorySize, 16) | 1;
  *Ptr = (UINTN) (Value64 | TopAddr);
  ///
  /// Assert error if programmed value is different from requested. This
  /// means error is requested size.
  ///
  Value64 = *Ptr;
  ASSERT ((LShiftU64 ((Value64 & 0xFFE), 16)) == TxtInfoData->TxtDprMemorySize);

  ///
  /// HEAP Registers
  /// Program size register first
  ///
  Ptr = (UINTN *) (UINTN) (TXT_PUBLIC_BASE + TXT_HEAP_SIZE_REG_OFF);

  ///
  /// Test register locked status. If locked, skip programming since
  /// this will be done by BIOS ACM
  ///
  *Ptr  = TEST_PATTERN;
  Value32 = *Ptr;
  if (Value32 != TEST_PATTERN) {
    Locked = TRUE;
  } else {
    ///
    /// To be safe invert pattern and try again
    ///
    *Ptr  = (UINTN) ~TEST_PATTERN;
    Value32 = *Ptr;
    if (Value32 != (UINTN) ~TEST_PATTERN) {
      Locked = TRUE;
    }
  }

  if (!Locked) {

    *Ptr = (UINTN) (TxtInfoData->TxtHeapMemorySize);
    ///
    /// Assert error if programmed value is different from requested. This
    /// means error is requested size.
    ///
    Value64 = *Ptr;
    ASSERT (Value64 == TxtInfoData->TxtHeapMemorySize);

    ///
    /// Program base register.
    ///
    Ptr   = (UINTN *) (UINTN) (TXT_PUBLIC_BASE + TXT_HEAP_BASE_REG_OFF);
    *Ptr  = TxtHeapMemoryBase;

    ///
    /// Assert error if programmed value is different from requested. This
    /// means error is requested size.
    ///
    Value64 = *Ptr;
    ASSERT (Value64 == TxtHeapMemoryBase);
  }
  ///
  /// SINIT Registers
  /// Program size register first
  ///
  Ptr   = (UINTN *) (UINTN) (TXT_PUBLIC_BASE + TXT_SINIT_SIZE_REG_OFF);
  *Ptr  = (UINT32) (TxtInfoData->SinitMemorySize);
  ///
  /// Assert error if programmed value is different from requested. This
  /// means error is requested size.
  ///
  Value64 = *Ptr;
  ASSERT (Value64 == TxtInfoData->SinitMemorySize);
  ///
  /// Program base register
  ///
  Ptr   = (UINTN *) (UINTN) (TXT_PUBLIC_BASE + TXT_SINIT_BASE_REG_OFF);
  *Ptr  = TxtSinitMemoryBase;
  ///
  /// Assert error if programmed value is different from requested. This
  /// means error is requested size.
  ///
  Value64 = *Ptr;
  ASSERT (Value64 == TxtSinitMemoryBase);

  ///
  /// Make sure TXT Device Memory has been zeroed
  ///
  ZeroMem (
    (VOID *) ((UINTN) TxtSinitMemoryBase),
    (UINTN) (TopAddr - TxtSinitMemoryBase)
    );

  if (TxtInfoData->TgaSize) {
    ;
    ///
    /// Placeholder for Trusted graphics support
    ///
  }

  Ptr   = (UINTN *) TxtHeapMemoryBase;
  *Ptr  = sizeof (BIOS_OS_DATA_REGION);

  ///
  /// BiosOsDataSize plus sizew of data size feld itself
  ///
  BiosOsDataRegion                          = (BIOS_OS_DATA_REGION *) (Ptr + 2);
  BiosOsDataRegion->Version                 = BIOS_OS_DATAREGION_VERSION;
  BiosOsDataRegion->BiosSinitSize           = 0;
  BiosOsDataRegion->LcpPdBase               = TxtInfoData->TxtLcpPdBase;
  BiosOsDataRegion->LcpPdSize               = TxtInfoData->TxtLcpPdSize;
  BiosOsDataRegion->NumOfLogicalProcessors  = CpuCount;
  BiosOsDataRegion->Flags                   = TxtInfoData->Flags;
  Ptr8 = (UINT8 *) (UINTN) &(BiosOsDataRegion->ExtData);
  AppendElement (TxtInfoHob, HEAP_EXTDATA_TYPE_BIOS_SPEC_VER, Ptr8, &Value32);
  Ptr8 += Value32;
  AppendElement (TxtInfoHob, HEAP_EXTDATA_TYPE_BIOSACM, Ptr8, &Value32);
  Ptr8 += Value32;
  AppendElement (TxtInfoHob, HEAP_EXTDATA_TYPE_END, Ptr8, &Value32);
  Value64 = (UINTN) Ptr8 - TxtHeapMemoryBase + Value32;
  *Ptr  = (Value64 & 0xFFFFFFFF);
  *(Ptr+1)  = (UINT32) (RShiftU64 (Value64,8));


  return EFI_SUCCESS;
}

/**
  Is Spt in PTT mode

  @retval TRUE          - If the PTT mode is asserted.
  @retval FALSE         - If the PTT mode is unasserted.
**/

BOOLEAN
IsSptPtt (
  VOID
  )
{
  UINT32 RegRead;

  RegRead = MmioRead32 (TXT_PUBLIC_BASE + TXT_PTT_FTIF_OFF);
  DEBUG ((DEBUG_INFO, "IsSptPtt: LT FTIF = %x\n", RegRead));
  RegRead = RegRead & TXT_PTT_PRESENT;
  if (RegRead == TXT_PTT_PRESENT) {
    DEBUG ((DEBUG_INFO, "IsSptPtt: PTT cycle\n"));
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Determines whether or not the platform has executed a TXT launch by
  examining the TPM Establishment bit.

  @param[in] TxtContextDataPtr      - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If the TPM establishment bit is asserted.
  @retval FALSE         - If the TPM establishment bit is unasserted.
**/
BOOLEAN
TxtIsEstablishmentBitAsserted (
  IN TXT_INFO_HOB *TxtInfoHob
  )
{
  UINT8  Access;
  UINT16 TimeOutCount;


  ///
  /// Set TPM.ACCESS polling timeout about 750ms
  ///
  TimeOutCount = TPM_TIME_OUT;
  do {
    ///
    /// Read TPM status register
    ///
    Access = MmioRead8 (TPM_STATUS_REG_ADDRESS);

    ///
    /// if TPM.Access == 0xFF, TPM is not present
    ///
    if (Access == 0xFF) {
      return FALSE;
    }
    ///
    /// Check tpmRegValidSts bit before checking establishment bit
    ///
    if ((Access & 0x80) != 0x80) {
      ///
      /// Delay 1ms
      ///
      MicroSecondDelay (1000);
    } else {
      ///
      /// tpmRegValidSts set, we can check establishment bit now.
      ///
      break;
    }

    TimeOutCount--;
  } while (TimeOutCount != 0);
  ///
  /// if tpmRegValidSts is not set, TPM is not usable
  ///
  if ((Access & 0x80) != 0x80) {
    DEBUG ((DEBUG_ERROR, "TXTPEI: TPM Valid Status is not set!! TPM.ACCESS=%x\n", Access));
    ASSERT (TRUE);
    CpuDeadLoop ();
  }
  ///
  /// The bit we're interested in uses negative logic:
  /// If bit 0 == 1 then return False
  /// Else return True
  ///
  return (Access & 0x1) ? FALSE : TRUE;
}

/**
  Determines whether or not the platform has encountered an error during
  a sleep or power-off state.

  @retval TRUE          - If the TXT_WAKE_ERROR bit is asserted.
  @retval FALSE         - If the TXT_WAKE_ERROR bit is unasserted.
**/
BOOLEAN
IsTxtWakeError (
  VOID
  )
{
  UINT8 Ests;

  ///
  /// Read TXT.ESTS register
  ///
  Ests = MmioRead8 (TXT_PUBLIC_BASE + TXT_ERROR_STATUS_REG_OFF);

  DEBUG ((DEBUG_INFO, "TXTPEI: TXT.ESTS=%x\n", Ests));

  return (Ests & (0x1 << 6)) ? TRUE : FALSE;
}

/**
  Determines whether or not the platform memory has been locked

  @retval TRUE          - If memroy is locked
  @retval FALSE         - If memory is unlocked
**/
BOOLEAN
IsMemoryLocked (
  VOID
  )
{
  UINT32 CpuMemLockStatus;

  ///
  /// Check status register for now.
  ///
  CpuMemLockStatus = MmioRead32 (TXT_PUBLIC_BASE + TXT_E2STS_REG_OFF);

  DEBUG ((DEBUG_INFO, "TXTPEI: CPU_UNCORE_MEMLOCK_STATUS=%x\n", CpuMemLockStatus));
  ///
  /// if BLOCK_MEM_STS (BIT2) is set to 1, memory is in unlock.
  ///
  return (CpuMemLockStatus & TXT_BLOCK_MEM_STS) ? TRUE : FALSE;
}

/**
  Determines whether or not POISON bit is set in status register

  @retval TRUE          - If the TPM reset bit is asserted.
  @retval FALSE         - If the TPM reset bit is unasserted.
**/
BOOLEAN
IsTxtResetSet (
  VOID
  )
{
  UINT8 Ests;
  ///
  /// Read TXT.ESTS register
  ///
  Ests = MmioRead8 (TXT_PUBLIC_BASE + TXT_ERROR_STATUS_REG_OFF);

  return (Ests & (0x1 << 0)) ? TRUE : FALSE;
}

/**
  Determines whether or not SECRETS.STS bit is set in E2STS status register

  @retval TRUE          - If the LT.SECRETS.STS bit is asserted.
  @retval FALSE         - If the LT.SECRETS.STS bit is unasserted.
**/
BOOLEAN
IsTxtSecretsSet (
  VOID
  )
{
  UINT8 E2sts;

  ///
  /// Read TXT.E2STS register
  ///
  E2sts = MmioRead8 (TXT_PUBLIC_BASE + TXT_E2STS_REG_OFF);

  DEBUG ((DEBUG_INFO, "TXTPEI: TXT.E2STS=%x\n", E2sts));

  return (E2sts & TXT_SECRETS_STS) ? TRUE : FALSE;
}

/**
  Determines presence of TPM in system

  @param[in] TxtContextDataPtr           - Point to TXT_PEI_LIB_CONTEXT structure
  @param[in] TxtPeiCtx      - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS          - If the TPM is present.
  @exception EFI_NOT_FOUND         - If the TPM is not present.
**/
EFI_STATUS
IsTpmPresent (
  IN TXT_INFO_HOB *TxtInfoHob
  )
{


  if((TxtInfoHob->Data.Flags & TPM_INIT_FAILED) == 0){
    return EFI_SUCCESS;
  } else {
    return EFI_DEVICE_ERROR;
  }
}

/**
  Clear Sleep Type register.

  @param[in] TxtContextDataPtr          - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS   - Always
**/
EFI_STATUS
ClearSlpTyp (
  IN TXT_INFO_HOB          *TxtInfoHob
  )
{
  UINT32 Pm1Addr;
  UINT32 Pm1Value;

  ///
  /// Make address for PM1_CNT
  ///
  Pm1Addr = ((UINT32) TxtInfoHob->Data.AcpiBase) + 4;

  ///
  /// Read 32-bits from PM1_CNT
  ///
  Pm1Value = IoRead32 ((UINTN) Pm1Addr);

  ///
  /// Clear SLP_TYP bits 10-12
  ///
  Pm1Value = Pm1Value & 0xffffe3ff;
  IoWrite32 (
    (UINTN) Pm1Addr,
    (UINT32) (Pm1Value)
    );

  return EFI_SUCCESS;
}

/**
  Issue a Global Reset
**/
VOID
IssueGlobalReset(
  VOID
  )
{
  PCH_RESET_DATA             ResetData;

  CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
  StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
  (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetPlatformSpecific, EFI_SUCCESS, sizeof (PCH_RESET_DATA), &ResetData);
}

/**
  Initializes values passed to AP

  @param[in] TxtContextDataPtr      - A pointer to an initialized TXT PEI Context data structure
**/
VOID
PrepareApParams (
  IN TXT_INFO_HOB          *TxtInfoHob
  )
{
  UINT32 TxtPublicSpace;

  TxtPublicSpace  = TXT_PUBLIC_BASE;

  *(UINT32 *) (TxtPublicSpace + BIOACM_ADDR)    = (UINT32) (TxtInfoHob->Data.BiosAcmBase);
  *(UINT32 *) (TxtPublicSpace + APINIT_ADDR)    = (UINT32) (TxtInfoHob->Data.ApStartupBase);
  *(UINT32 *) (TxtPublicSpace + SEMAPHORE)      = 0;
}

/**
  Invokes the SCLEAN/ACHECK function from the TXT BIOS ACM.
  1. Clearing of sleep type is necessary because SCLEAN/ACHECK destroys memory
  context, so S3 after it is run and system is reset is impossible. We
  do it here since there is no any indication that can sustain reset
  for any other module to do it on our behalf.
  2. APs are initialized before calling of SCLEAN/ACHECK
  3. SCLEAN/ACHECK function is invoked.

  @param[in] TxtContextDataPtr      - A pointer to an initialized TXT PEI Context data structure
  @param[in] func      - Acm function to be launch

  @retval EFI_SUCCESS   - Always.
**/
EFI_STATUS
DoAcmLaunch (
  IN TXT_INFO_HOB          *TxtInfoHob,
  IN UINT8               func
  )
{
  EFI_STATUS                    Status;
  SI_PREMEM_POLICY_PPI          *SiPreMemPolicy;
  CPU_SECURITY_PREMEM_CONFIG    *CpuSecurityPreMemConfig;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicy
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  ClearSlpTyp (TxtInfoHob);

  PrepareApParams (TxtInfoHob);

  if (CpuSecurityPreMemConfig->SkipStopPbet != TRUE) {
    ///
    /// Disable PBET before send IPI to APs
    ///
    StopPbeTimer ();
  }

  if (func == TXT_LAUNCH_CLEAR_SECRETS) {
    LaunchBiosAcmClearSecrets ();
  } else if (func == TXT_LAUNCH_ACHECK) {
    LaunchBiosAcmAcheck ();
  }

  return EFI_SUCCESS;
}

/**
  Launching of SCHECK function from the TXT BIOS ACM.

  @param[in] TxtContextDataPtr         - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS     - Always.
**/
VOID
EFIAPI
DummyFunc (
  IN OUT VOID  *Buffer
  )
{
  return;
}

/**
  Invoke BIOS ACM function

  @param[in]
     TxtInfoHob: pointer to TXT_INFO_HOB struct
     Function:   index of ACM function to invoke
     BootMode:   Cold boot or S3
**/
EFI_STATUS
DoPeiLaunchAcm (
  IN EFI_PEI_SERVICES  **PeiServices,
  IN TXT_INFO_HOB          *TxtInfoHob,
  IN UINT64                Function,
  IN UINT64                BootMode
  )
{
  ///
  /// ApCfg array contains 10 elements for 8 MTRRs + 10 element for
  /// IA32_MTRR_DEF_TYPE MTRR + 1 element for IDT + 1 element for
  /// IA32_MISC_ENABLE MSR
  ///
  UINT64  ApCfg[MSR_IA32_MTRR_PHYSMASK9 - MSR_IA32_MTRR_PHYSBASE0 + 4];
  UINT64  BiosAcAddr;
  UINT64  SavedSmiSourcesVariables[2];
  UINTN   NumberOfProcessors;
  UINTN   NumberOfEnabledProcessors;
  UINTN   MyCpuNumber;
  UINTN   Index;
  EFI_PEI_MP_SERVICES_PPI *MpServicesPpi = NULL;
  EFI_STATUS              Status = EFI_SUCCESS;

  Status = PeiServicesLocatePpi (
             &gEfiPeiMpServicesPpiGuid,
             0,
             NULL,
             (VOID **) &MpServicesPpi);
  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return Status;
  }
  Status = MpServicesPpi->GetNumberOfProcessors ((CONST EFI_PEI_SERVICES **) PeiServices, MpServicesPpi, (UINTN *)&NumberOfProcessors, (UINTN *)&NumberOfEnabledProcessors);
  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return Status;
  }
  Status = MpServicesPpi->WhoAmI (
                        (CONST EFI_PEI_SERVICES **) PeiServices,
                        MpServicesPpi,
                        &MyCpuNumber
                        );
  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return Status;
  }

  BiosAcAddr = (UINT64) (UINTN) TxtInfoHob->Data.BiosAcmBase;
  SaveApConfig (ApCfg);
  DisableSmiSources (TxtInfoHob, SavedSmiSourcesVariables, TRUE);

  ///
  /// Disable APs and put in WFS state
  ///
  for (Index = 0; Index < NumberOfProcessors; Index++) {
    if (Index != MyCpuNumber) {
      DEBUG ((DEBUG_INFO, "TXTPEI: disable AP Index=%x\n", Index));
      Status = MpServicesPpi->EnableDisableAP (
                            (CONST EFI_PEI_SERVICES **) PeiServices,
                            MpServicesPpi,
                            Index,
                            FALSE,
                            NULL
                            );
      ASSERT_EFI_ERROR (Status);
    }
  }
  SendInitIpiAllExcludingSelf();

  // Give the APs time to enter wait-for-SIPI state
  MicroSecondDelay (10 * STALL_ONE_MILLI_SECOND);

  ///
  /// Launch the BIOS ACM to run the requested function
  ///
  DEBUG ((DEBUG_INFO, "TXTPEI::Running of LaunchBiosAcm\n"));
  LaunchBiosAcm (&BiosAcAddr,Function,BootMode);

  ///
  /// Restart APs
  ///
  for (Index = 0; Index < NumberOfProcessors; Index++) {
    if (Index != MyCpuNumber) {
      DEBUG ((DEBUG_INFO, "TXTPEI: restart AP Index=%x\n", Index));
      Status = MpServicesPpi->EnableDisableAP (
                            (CONST EFI_PEI_SERVICES **) PeiServices,
                            MpServicesPpi,
                            Index,
                            TRUE,
                            NULL
                            );
      ASSERT_EFI_ERROR (Status);
    }
  }

  DisableSmiSources (TxtInfoHob, SavedSmiSourcesVariables, FALSE);
  RestoreMtrrProgramming (ApCfg);
  return EFI_SUCCESS;
}

/**
  Disable or restore possible SMI sources before or after SCHECK on S3 resume.

  @param[in] TxtContextDataPtr               - A pointer to an initialized TXT PEI Context data structure
  @param[in] SavedSmiSourcesVariablesPointer - Saved SMI source Variable
  @param[in] Operation
                                             - Boolean value telling what operation is requested:
                                             - TRUE: save and then disable possible SMI sources.
                                             - FALSE: restore original SMI settings.

  @retval EFI_SUCCESS   - Always.
**/
EFI_STATUS
DisableSmiSources (
  IN TXT_INFO_HOB          *TxtInfoHob,
  IN UINT64*               SavedSmiSourcesVariablesPointer,
  IN BOOLEAN               Operation
  )
{
  UINT64        GlobalSmiControlIoAddr;
  UINT32        SavedSmiControl;
  UINT64        SavedIa32ThermInterruptMsr;

  GlobalSmiControlIoAddr = TxtInfoHob->Data.AcpiBase + 0x30;

  if (Operation == TRUE) {
    SavedIa32ThermInterruptMsr = AsmReadMsr64 ((UINT32) MSR_IA32_THERM_INTERRUPT);
    //
    // Cannot use static variables because of PEI phase, static variables would be in code region which is read-only.
    //
    *SavedSmiSourcesVariablesPointer = SavedIa32ThermInterruptMsr;
    AsmWriteMsr64 (
      (UINT32) MSR_IA32_THERM_INTERRUPT,
      (UINT64) (SavedIa32ThermInterruptMsr & ~(BIT0 + BIT1 + BIT2 + BIT4 + BIT15 + BIT23))
      );
    SavedSmiControl = IoRead32 ((UINTN) GlobalSmiControlIoAddr);
    *((UINT64 *) (SavedSmiSourcesVariablesPointer + 1)) = SavedSmiControl;
    //
    // We can not disable Global SMI since it should be locked after SCHECK. we can only disable SMI sources individually.
    //

    IoWrite32 ((UINTN) GlobalSmiControlIoAddr, (UINT32) (SavedSmiControl & 0x01));
  } else {
    //
    // We can not disable Global SMI since it should be locked after SCHECK. we can only disable SMI sources individually.
    // Restore original SMI setting after SCHECK
    //

    SavedSmiControl = (UINT32) *((UINT64 *) (SavedSmiSourcesVariablesPointer + 1));
    IoWrite32 (
      (UINTN) GlobalSmiControlIoAddr,
      (UINT32) (SavedSmiControl)
      );

    SavedIa32ThermInterruptMsr = *SavedSmiSourcesVariablesPointer;
    //
    // Restore IA32_THERMAL_INTERRUPT MSR
    //
    AsmWriteMsr64 (
      (UINT32) MSR_IA32_THERM_INTERRUPT,
      (UINT64) SavedIa32ThermInterruptMsr
      );
  }

  return EFI_SUCCESS;
}

/**
  Unlock memory when security is set and TxT is not enabled

  @param[in] TxtContextDataPtr      - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS  - If address has been found
  @exception EFI_UNSUPPORTED - CPU doesn't support TxT.
**/
EFI_STATUS
TxtUnlockMemory (
  IN TXT_INFO_HOB          *TxtInfoHob
  )
{
  BOOLEAN EstablishmentBitAsserted;

  EstablishmentBitAsserted = TxtIsEstablishmentBitAsserted (TxtInfoHob);

  ///
  /// Need to read FED40000 before unlocking memory
  ///
  if (!EstablishmentBitAsserted) {
    DEBUG ((DEBUG_INFO, "TXTPEI::Unlock memory\n"));
    AsmWriteMsr64 (MSR_LT_UNLOCK_MEMORY, 0);
  } else {
    ///
    /// Lunch SCLEAN if wake error bit is set.
    ///
    if (IsTxtWakeError ()) {
      ///
      /// If TXTRESET is set , we must clean TXTRESET bit otherwise SCLEAN
      /// will fail
      ///
      if (IsTxtResetSet ()) {
        IssueGlobalReset ();
      }

      if ((TxtInfoHob->Data.BiosAcmBase == 0) || (TxtInfoHob->Data.ApStartupBase == 0)) {
        return EFI_UNSUPPORTED;
      }
      ///
      /// Setup and Launch SCLEAN
      ///
      DEBUG ((DEBUG_INFO, "TXTPEI::Entering SCLEAN to unlock memory\n"));

    } else {
      return EFI_UNSUPPORTED;
    }
  }

  return EFI_SUCCESS;
}
