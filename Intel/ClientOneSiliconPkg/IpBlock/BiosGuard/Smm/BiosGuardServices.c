/** @file
  BIOS Guard Driver implements the BIOS Guard Host Controller Compatibility Interface.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

#include <Base.h>
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <CpuAccess.h>
#include "BiosGuardServices.h"
#include <CpuInitDataHob.h>
#include <Library/CpuCommonLib.h>
#include <Library/SynchronizationLib.h>
#include <Library/WdtCommonLib.h>

///
/// Global variables
///
GLOBAL_REMOVE_IF_UNREFERENCED BIOSGUARD_PROTOCOL                *mBiosGuardProtocol;
GLOBAL_REMOVE_IF_UNREFERENCED BIOSGUARD_HOB                     *mBiosGuardHobPtr;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_BOOT_MODE                     mBootMode;
GLOBAL_REMOVE_IF_UNREFERENCED BIOSGUARD_NVS_AREA_PROTOCOL       *mBiosGuardNvsAreaProtocol = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED volatile UINT8                    mWaitTriggerAbort;
GLOBAL_REMOVE_IF_UNREFERENCED volatile UINT32                   mApThreadCount;

//
// Private GUID for BIOS Guard initializes
//
extern EFI_GUID                          gBiosGuardHobGuid;

/**
  This function is triggered by the BIOS update tool with an IO trap. It executes
  BIOS Guard protocol execute with the true flag indicating that there is an update package
  in the DPR region of memory.

  @param[in] DispatchHandle      Not used
  @param[in] CallbackContext     Not used
**/
VOID
EFIAPI
BiosGuardUpdateBios (
  IN EFI_HANDLE                             DispatchHandle,
  IN CONST VOID                             *CallbackContext,
  IN OUT VOID                               *CommBuffer,
  IN OUT UINTN                              *CommBufferSize
  )
{
  ///
  /// Invoke BIOS Guard Services for updating BIOS
  ///
  mBiosGuardProtocol->Execute (mBiosGuardProtocol, TRUE);

  if (mBootMode == BOOT_ON_FLASH_UPDATE) {
    ///
    /// A complete BGUP is provided for Capsule and Tool updates. Therefore, the BGUP header should not
    /// be overwritten in the event another erase or write operation occurs. The status from the IO Trap
    /// is alternately placed at the BGUP Certificate address.
    ///
    CopyMem ((UINT64 *) mBgupCertificate, &mBiosGuardFullStatus, sizeof (UINT64));
  } else {
    ///
    /// Based on the interface defined for Tools implementation, the status from the IO Trap needs to be
    /// placed at the address of the BGUP, essentially overwriting the header.
    /// The BGUP Header, along with the Script, Data and BGUP Certificate are written by the tools into DPR memory,
    /// therefore, we can safely overwrite the information in that address after execution as the next time tools does an
    /// update operation, it will pass the complete package providing the proper BGUP Header
    ///
    CopyMem (mBiosGuardUpdatePackagePtr, &mBiosGuardFullStatus, sizeof (UINT64));
  }

  return;
}

/**
  This method registers and sets up the IOTRAP and NVS area for the BIOS Guard tools interface
**/
VOID
EFIAPI
BiosGuardToolsInterfaceInit (
  VOID
  )
{
  EFI_STATUS                                Status;
  EFI_HANDLE                                PchIoTrapHandle;
  EFI_SMM_IO_TRAP_REGISTER_CONTEXT          PchIoTrapContext;
  EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL        *PchIoTrap;

  Status = gSmst->SmmLocateProtocol (&gEfiSmmIoTrapDispatch2ProtocolGuid, NULL, (VOID **) &PchIoTrap);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Locate BIOS Guard SMM Protocol
  ///
  Status = gSmst->SmmLocateProtocol (&gSmmBiosGuardProtocolGuid, NULL, (VOID **) &mBiosGuardProtocol);
  ASSERT_EFI_ERROR (Status);
  if (mBiosGuardProtocol != NULL) {
    ///
    /// Register BIOS Guard IO TRAP handler
    ///
    PchIoTrapContext.Type         = ReadWriteTrap;
    PchIoTrapContext.Length       = 4;
    PchIoTrapContext.Address      = 0;
    Status = PchIoTrap->Register (
                          PchIoTrap,
                          (EFI_SMM_HANDLER_ENTRY_POINT2) BiosGuardUpdateBios,
                          &PchIoTrapContext,
                          &PchIoTrapHandle
                          );
    ASSERT_EFI_ERROR (Status);

    mBiosGuardNvsAreaProtocol->Area->BiosGuardMemAddress     = mBiosGuardMemAddress;
    mBiosGuardNvsAreaProtocol->Area->BiosGuardMemSize        = (UINT8) RShiftU64 (mBiosGuardMemSize, 20);
    mBiosGuardNvsAreaProtocol->Area->BiosGuardIoTrapAddress  = PchIoTrapContext.Address;
    mBiosGuardNvsAreaProtocol->Area->BiosGuardIoTrapLength   = (UINT8) PchIoTrapContext.Length;
  }
}

/**
  Entry point for the BIOS Guard protocol driver.

  @param[in] ImageHandle        Image handle of this driver.
  @param[in] SystemTable        Global system service table.

  @retval EFI_SUCCESS           Initialization complete.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  @retval EFI_ERROR             Driver exits abnormally.
  @retval EFI_NOT_FOUND         CPU Data HOB not available.
**/
EFI_STATUS
EFIAPI
InstallBiosGuardProtocol (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS                                Status;
  BIOSGUARD_INSTANCE                        *BiosGuardInstance;
  VOID                                      *BiosGuardProtocolAddr;
  BOOLEAN                                   BiosGuardToolsInterface;

  BiosGuardToolsInterface  = FALSE;

  ///
  /// Locate BIOS Guard Nvs
  ///
  Status = gBS->LocateProtocol (&gBiosGuardNvsAreaProtocolGuid, NULL, (VOID **) &mBiosGuardNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Allocate pool for BIOS Guard protocol instance
  ///
  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (BIOSGUARD_INSTANCE),
                    (VOID **) &BiosGuardInstance
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (BiosGuardInstance == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  ZeroMem ((VOID *) BiosGuardInstance, sizeof (BIOSGUARD_INSTANCE));
  BiosGuardInstance->Handle = NULL;
  BiosGuardProtocolAddr     = NULL;

  ///
  /// Initialize BIOS Guard protocol instance if BIOS Guard is supported and enabled
  ///
  if ((AsmReadMsr64 (MSR_PLATFORM_INFO)) & B_MSR_PLATFORM_INFO_PFAT_ENABLE_MASK) {
    if ((AsmReadMsr64 (MSR_PLAT_FRMW_PROT_CTRL)) & B_MSR_PLAT_FRMW_PROT_CTRL_PFAT_ENABLE_MASK) {
      mBootMode = GetBootModeHob ();

      ///
      /// Initialize the BIOS Guard protocol instance
      ///
      Status = BiosGuardProtocolConstructor (BiosGuardInstance);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      BiosGuardProtocolAddr = &(BiosGuardInstance->BiosGuardProtocol);

      ///
      /// Initialize tools support only if we are in Legacy flow
      ///
      if (mBiosGuardUpdatePackageInTseg == FALSE) {
        BiosGuardToolsInterface = TRUE;
      }
    } else {
      DEBUG ((DEBUG_INFO, "BIOS Guard Feature supported but disabled\n"));
    }
  } else {
    DEBUG ((DEBUG_WARN, "BIOS Guard Feature is not supported\n"));
  }

  ///
  /// Install the SMM BIOSGUARD_PROTOCOL interface
  ///
  Status = gSmst->SmmInstallProtocolInterface (
                    &(BiosGuardInstance->Handle),
                    &gSmmBiosGuardProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    BiosGuardProtocolAddr
                    );
  if (EFI_ERROR (Status)) {
    gSmst->SmmFreePool (BiosGuardInstance);
  } else {
    if (BiosGuardToolsInterface == TRUE) {
      BiosGuardToolsInterfaceInit ();
    }
  }

  return Status;
}

/**
  Initialize BIOS Guard protocol instance.

  @param[in] BiosGuardInstance  Pointer to BiosGuardInstance to initialize

  @retval EFI_SUCCESS           The protocol instance was properly initialized
  @retval EFI_NOT_FOUND         BIOS Guard Binary module was not found.
  @retval EFI_OUT_OF_RESOURCES  Allocated memory could not be freed.
**/
EFI_STATUS
BiosGuardProtocolConstructor (
  BIOSGUARD_INSTANCE *BiosGuardInstance
  )
{
  EFI_STATUS                      Status;
  BGPDT                           *Bgpdt;
  UINTN                           NumPages;
  EFI_PHYSICAL_ADDRESS            Addr;
  EFI_PHYSICAL_ADDRESS            BiosGuardModule;
  SA_CONFIG_HOB                   *SaConfigHobPtr;
  UINT32                          BiosGuardModuleSize;

  NumPages                      = BIOSGUARD_MEMORY_PAGES + ALIGNMENT_IN_PAGES;
  BiosGuardModuleSize           = 0;
  Addr                          = 0;
  mBiosGuardUpdatePackageInTseg = FALSE;

  DEBUG ((DEBUG_INFO, "BiosGuardProtocolConstructor\n"));

  mBiosGuardHobPtr = GetFirstGuidHob (&gBiosGuardHobGuid);
  if (mBiosGuardHobPtr == NULL) {
    DEBUG ((DEBUG_ERROR, "BIOS Guard HOB not available\n"));
    return EFI_NOT_FOUND;
  }

  if (mBiosGuardHobPtr->BiosGuardModulePtr == (EFI_PHYSICAL_ADDRESS) NULL) {
    return EFI_NOT_FOUND;
  }

  BiosGuardModuleSize  = *(UINT16*) (mBiosGuardHobPtr->BiosGuardModulePtr + BIOSGUARD_MODULE_SIZE_OFFSET);
  DEBUG ((DEBUG_ERROR, "BIOS Guard Module Size: %x\n", BiosGuardModuleSize));
  if (BiosGuardModuleSize == 0) {
    return EFI_NOT_FOUND;
  }

  ///
  /// Allocate memory buffer for BIOS Guard Module
  ///
  Status = gSmst->SmmAllocatePages (AllocateAnyPages, EfiRuntimeServicesData, NumPages, &Addr);
  if (EFI_ERROR (Status) || Addr == (EFI_PHYSICAL_ADDRESS) NULL) {
    DEBUG ((DEBUG_ERROR, "Allocation of buffer for BIOS Guard Module failed.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  ///
  /// Align address to 256K.
  ///
  BiosGuardModule  = Addr &~(ALIGN_256KB - 1);
  BiosGuardModule  = BiosGuardModule < Addr ? (BiosGuardModule + ALIGN_256KB) : BiosGuardModule;

  ///
  /// Checking if the size of pages to free is not zero
  ///
  if (Addr != BiosGuardModule) {
    ///
    /// Free all allocated pages till start of the aligned memory address
    ///
    Status = gSmst->SmmFreePages (
                      Addr,
                      EFI_SIZE_TO_PAGES (BiosGuardModule - Addr)
                      );

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Freeing of allocated pages till start of the aligned memory address failed.\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  }

  ///
  /// Checking if the size of pages to free is not zero
  ///
  if (((Addr + (ALIGN_256KB * 2)) - (BiosGuardModule + ALIGN_256KB)) != 0) {
    ///
    /// Free all allocated pages after the end of the aligned memory address
    ///
    Status = gSmst->SmmFreePages (
                      BiosGuardModule + ALIGN_256KB,
                      EFI_SIZE_TO_PAGES ((Addr + (ALIGN_256KB * 2)) - (BiosGuardModule + ALIGN_256KB))
                      );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Freeing of allocated pages after the end of the aligned memory address failed.\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  }

  ///
  /// Copy BIOS Guard Module into prepared buffer.
  ///
  CopyMem ((VOID*) BiosGuardModule,(VOID*) mBiosGuardHobPtr->BiosGuardModulePtr,BiosGuardModuleSize);

  SaConfigHobPtr = GetFirstGuidHob (&gSaConfigHobGuid);
  if (SaConfigHobPtr == NULL) {
    DEBUG ((DEBUG_ERROR, "SA Config HOB not available\n"));
    return EFI_NOT_FOUND;
  }

  ///
  /// Allocate pool for BGPDT Data
  ///
  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    mBiosGuardHobPtr->Bgpdt.BgpdtSize,
                    (VOID **) &Bgpdt
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  CopyMem (Bgpdt, &mBiosGuardHobPtr->Bgpdt, mBiosGuardHobPtr->Bgpdt.BgpdtSize);

  ///
  /// Determine if BGUP is to be placed in TSEG
  /// If the size allocated to BIOS Guard in DPR is 0, BGUP will be stored in TSEG
  /// Otherwise, BGUP will use the memory allocated within DPR
  ///
  if (SaConfigHobPtr->DprDirectory[EnumDprDirectoryBiosGuard].Size == 0) {
    mBiosGuardUpdatePackageInTseg = TRUE;
  }

  ///
  /// Legacy runtime flow or Capsule Update based flow, allocate BIOS Guard variables in DPR
  ///
  if (mBiosGuardUpdatePackageInTseg == FALSE) {
    ///
    /// First, initialize the BIOS Guard memory address in the pre-allocated space within DPR
    ///
    mBiosGuardMemAddress        = SaConfigHobPtr->DprDirectory[EnumDprDirectoryBiosGuard].PhysBase;
    mBiosGuardMemSize           = (UINT32) LShiftU64 (SaConfigHobPtr->DprDirectory[EnumDprDirectoryBiosGuard].Size, 20);

    ///
    /// The BGUP uses the majority of the space within the allocated region and uses the initial block of memory
    ///
    mBiosGuardUpdatePackagePtr  = (BGUP *) mBiosGuardMemAddress;

    ///
    /// A subset of the memory is allotted for the space required for the BIOS Guard certificate after the BGUP
    ///
    mBgupCertificate            = (EFI_PHYSICAL_ADDRESS) (mBiosGuardMemAddress + mBiosGuardMemSize - BGUPC_MEMORY_OFFSET);

    ///
    /// A final allocation is made for the BIOS Guard Log at the end of the buffer after the certificate
    ///
    mBiosGuardLogPtr            = (BIOSGUARD_LOG *) (mBiosGuardMemAddress + mBiosGuardMemSize - BIOSGUARD_LOG_MEMORY_OFFSET);
  } else {
    ///
    /// Non-BIOS update flow, allocate BGUP pointer within TSEG
    ///
    mBiosGuardMemSize = BGUP_TSEG_BUFFER_SIZE;
    NumPages = mBiosGuardMemSize / EFI_PAGE_SIZE;
    Status = gSmst->SmmAllocatePages (
                      AllocateAnyPages,
                      EfiRuntimeServicesData,
                      NumPages,
                      &mBiosGuardMemAddress
                      );
    if (Status != EFI_SUCCESS) {
      DEBUG ((DEBUG_ERROR, "Memory for BGUP not allocated in SMM!\n"));
      ASSERT_EFI_ERROR (Status);
      return Status;
    }

    ///
    /// During runtime, the TSEG memory is only allocated for BGUP
    ///
    mBiosGuardUpdatePackagePtr  = (BGUP *) mBiosGuardMemAddress;

    ///
    /// Initialize the Certificate memory and Log memory to NULL as it isn't available in the standard path
    ///
    mBgupCertificate = (EFI_PHYSICAL_ADDRESS) NULL;
    mBiosGuardLogPtr = NULL;
  }

  ///
  /// Save the Log & BGUP headers into a temporary location so it can be used for re-initialization of the log between BiosGuardProtocolExecute calls
  ///
  CopyMem (&mBiosGuardLogTemp, &mBiosGuardHobPtr->BiosGuardLog, sizeof (BIOSGUARD_LOG));
  CopyMem (&mBiosGuardBgupHeaderTemp, &mBiosGuardHobPtr->BgupHeader, sizeof (BGUP_HEADER));

  ///
  /// Initialize the BIOS Guard Update Package with the package header and zero out the rest of the buffer
  ///
  ZeroMem (mBiosGuardUpdatePackagePtr, mBiosGuardMemSize);
  CopyMem (&mBiosGuardUpdatePackagePtr->BgupHeader, &mBiosGuardHobPtr->BgupHeader, sizeof (BGUP_HEADER));
  mBiosGuardUpdatePackagePtr->BgupHeader.ScriptSectionSize  = 0;
  mBiosGuardUpdatePackagePtr->BgupHeader.DataSectionSize    = 0;
  mBiosGuardUpdateCounter = 0;

  ///
  /// Set Begin command
  ///
  mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter++] = BIOSGUARD_COMMAND_BEGIN;

  ///
  /// Initialize the BIOS Guard protocol instance
  ///
  BiosGuardInstance->Signature                                      = BIOSGUARD_SIGNATURE;
  BiosGuardInstance->BiosGuardProtocol.Write                        = BiosGuardProtocolWrite;
  BiosGuardInstance->BiosGuardProtocol.Erase                        = BiosGuardProtocolBlockErase;
  BiosGuardInstance->BiosGuardProtocol.Execute                      = BiosGuardProtocolExecute;
  BiosGuardInstance->BiosGuardDirectory[EnumBiosGuardModule]        = BiosGuardModule;
  BiosGuardInstance->BiosGuardDirectory[EnumBiosGuardModule]        |= LShiftU64 (BIOSGUARD_DIRECTORY_BIOSGUARD_MODULE_ENTRY, 56);
  BiosGuardInstance->BiosGuardDirectory[EnumBgpdt]                  = (EFI_PHYSICAL_ADDRESS) Bgpdt;
  BiosGuardInstance->BiosGuardDirectory[EnumBgpdt]                  |= LShiftU64 (BIOSGUARD_DIRECTORY_BGPDT_ENTRY, 56);
  BiosGuardInstance->BiosGuardDirectory[EnumBgup]                   = (EFI_PHYSICAL_ADDRESS) mBiosGuardUpdatePackagePtr;
  BiosGuardInstance->BiosGuardDirectory[EnumBgup]                   |= LShiftU64 (BIOSGUARD_DIRECTORY_BGUP_ENTRY, 56);
  BiosGuardInstance->BiosGuardDirectory[EnumBgupCertificate]        = 0;
  BiosGuardInstance->BiosGuardDirectory[EnumBgupCertificate]        |= LShiftU64 (BIOSGUARD_DIRECTORY_UNDEFINED_ENTRY, 56);
  BiosGuardInstance->BiosGuardDirectory[EnumBiosGuardLog]           = 0;
  BiosGuardInstance->BiosGuardDirectory[EnumBiosGuardLog]           |= LShiftU64 (BIOSGUARD_DIRECTORY_UNDEFINED_ENTRY, 56);
  BiosGuardInstance->BiosGuardDirectory[EnumBiosGuardDirectoryEnd]  = 0;
  BiosGuardInstance->BiosGuardDirectory[EnumBiosGuardDirectoryEnd]  |= LShiftU64 (BIOSGUARD_DIRECTORY_END_MARKER, 56);

  return EFI_SUCCESS;
}

/**
  This service invokes the BIOS Guard Binary.
  All AP threads are present and released by BSP to trigger MSR 0x116.

  Set MSR 0x115 with BIOS Guard DIRECTORY Address.
  Trigger MSR 0x116 to invoke BIOS Guard Binary.
  Read MSR 0x115 to get BIOS Guard Binary Status.

  @param[in] BiosGuardInstance              Pointer to BiosGuardInstance to initialize
**/
VOID
EFIAPI
BiosGuardModuleExecute (
  IN VOID          *BiosGuardInstancePtr
  )
{
  BIOSGUARD_INSTANCE *BiosGuardInstance;
  BOOLEAN            IsBspInt;
  UINT8              RetryTimeOut;

  BiosGuardInstance = BiosGuardInstancePtr;
  IsBspInt          = IsBsp (); // This gets System BSP not SMM BSP. SMM BSP may change each boot depending upon policy.

  if (!IsBspInt) {
    //
    // AP check-in and wait for BSP signal.
    //
    InterlockedIncrement (&mApThreadCount);
    while (mWaitTriggerAbort == BIOSGUARD_MODULE_EXECUTE_WAIT) {
      CpuPause ();
    }
  } else {
    //
    // BSP wait for APs to check-in with timeout. If AP is in Wait for SIPI, it won't check-in.
    //
    RetryTimeOut = 0;

    while ((mApThreadCount < (gSmst->NumberOfCpus - 1)) && (RetryTimeOut != BIOSGUARD_AP_SAFE_RETRY_LIMIT)) {
      MicroSecondDelay (BIOSGUARD_WAIT_PERIOD);
      RetryTimeOut++;
    }

    //
    // Signal if all APs checked-in in or not.
    //
    mWaitTriggerAbort = RetryTimeOut != BIOSGUARD_AP_SAFE_RETRY_LIMIT ? BIOSGUARD_MODULE_EXECUTE_TRIGGER :  BIOSGUARD_MODULE_EXECUTE_ABORT;
  }

  //
  // If not all APs check-in, then abort.
  //
  if (mWaitTriggerAbort == BIOSGUARD_MODULE_EXECUTE_ABORT) {
    return;
  }

  if (!IsBspInt) {
    //
    // Signal that AP is invoking BIOS Guard binary.
    //
    InterlockedDecrement (&mApThreadCount);

    //
    // Invoke BIOS Guard binary.
    //
    AsmWriteMsr64 (MSR_PLAT_FRMW_PROT_TRIG_PARAM, (UINT64) BiosGuardInstance->BiosGuardDirectory);
    AsmWriteMsr64 (MSR_PLAT_FRMW_PROT_TRIGGER, 0);
    return;
  }

  //
  // BSP wait for all APs to signal they are invoking BIOS Guard binary. BSP will invoke last.
  //
  while (mApThreadCount > 0) {
    CpuPause ();
  }

  //
  // Delay to allow last AP to enter BIOS Guard before BSP
  //
  MicroSecondDelay (BIOSGUARD_WAIT_PERIOD);

  //
  // Initialize signal to Wait, so caller will know when signal has changed, and System BSP (which maybe different than SMM BSP) has exited BIOS Guard binary.
  //
  mWaitTriggerAbort = BIOSGUARD_MODULE_EXECUTE_WAIT;

  ///
  /// BSP will then write final Trigger to invoke BIOS Guard Binary
  ///
  AsmWriteMsr64 (MSR_PLAT_FRMW_PROT_TRIG_PARAM, (UINT64) BiosGuardInstance->BiosGuardDirectory);
  AsmWriteMsr64 (MSR_PLAT_FRMW_PROT_TRIGGER, 0);
  ///
  /// Read MSR_PLAT_FRMW_PROT_TRIG_PARAM to get BIOS Guard Binary status
  ///
  BiosGuardInstance->MsrValue = AsmReadMsr64 (MSR_PLAT_FRMW_PROT_TRIG_PARAM);

  //
  // Signal that System BSP is exiting and that BIOS Guard Binary status has been updated.
  //
  mWaitTriggerAbort = BIOSGUARD_MODULE_EXECUTE_TRIGGER;
}

/**
  This service will write BIOSGUARD_DIRECTORY MSR and invoke the BIOS Guard Module by writing to PLAT_FRMW_PROT_TRIGGER MSR for writing/erasing to flash.
  BIOS should invoke BIOSGUARD_PROTOCOL.Write() or BIOSGUARD_PROTOCOL.Erase() function prior to calling BIOSGUARD_PROTOCOL.Execute() for flash writes/erases (except for IoTrapBasedRequest).
  Write()/Erase() function will render BIOS Guard script during execution.
  Execute() function will implement the following steps:
  1. Update BIOS Guard directory with address of BGUP.
  2. All the AP's except the master thread are put to sleep.
  3. BIOS Guard module is invoked from BSP to execute desired operation.
  If IoTrapBasedRequest flag is set to true, BGUP (BGUP Header + BIOS Guard Script + Update data) is part of data that is passed to SMI Handler. SMI Handler invokes BIOS Guard module to process the update.
  This function would be called by runtime driver, please do not use any MMIO macro here.

  @param[in] This                Pointer to the BIOSGUARD_PROTOCOL instance.
  @param[in] IoTrapBasedRequest  Flag to indicate flash update is requested from OS runtime via IO Trap (i.e. a Tool)

  @retval EFI_SUCCESS            Successfully completed flash operation.
  @retval EFI_INVALID_PARAMETER  The parameters specified are not valid.
  @retval EFI_UNSUPPORTED        The CPU or SPI memory is not supported.
  @retval EFI_DEVICE_ERROR       Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
BiosGuardProtocolExecute (
  IN BIOSGUARD_PROTOCOL *This,
  IN BOOLEAN            IoTrapBasedRequest
  )
{
  EFI_STATUS         Status;
  BIOSGUARD_INSTANCE *BiosGuardInstance;
  UINT16             BiosGuardStatus;
  UINT16             BiosGuardAdditionalData;
  UINT16             BiosGuardTerminalLine;
  UINT8              BiosGuardSE;
  UINTN              Index;
  BOOLEAN            DisallowedUpdate;
  BOOLEAN            OcWdtEnabled;
  BOOLEAN            ReloadOcWdt;
  UINT8              RetryTrigger;

  ///
  /// Initialize local variables
  ///
  BiosGuardStatus         = ERR_OK;
  BiosGuardAdditionalData = ERR_OK;
  BiosGuardTerminalLine   = ERR_OK;
  BiosGuardSE             = ERR_OK;
  DisallowedUpdate        = FALSE;
  OcWdtEnabled            = FALSE;
  ReloadOcWdt             = FALSE;
  Status                  = EFI_SUCCESS;
  RetryTrigger            = 0;

  DEBUG ((DEBUG_INFO, "BiosGuardProtocolExecute\n"));

  BiosGuardInstance = BIOSGUARD_INSTANCE_FROM_BIOSGUARDPROTOCOL (This);

  ///
  /// Prior to execution of the BIOS Guard module, reinitialize the BIOS Guard Log area & BIOS Guard Binary Return Status
  ///
  if (mBiosGuardLogPtr != NULL) {
    ZeroMem (mBiosGuardLogPtr, BIOSGUARD_LOG_MEMORY_SIZE);
    CopyMem (mBiosGuardLogPtr, &mBiosGuardLogTemp, sizeof (BIOSGUARD_LOG));
  }
  BiosGuardInstance->MsrValue = ERR_LAUNCH_FAIL;

  if (IoTrapBasedRequest == FALSE) {
    ///
    /// If Update Package has been created by the BIOS during POST then complete the script
    /// and create update Pkg
    ///

    ///
    /// First, finalize the script by adding the "End" command
    ///
    mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter++]  = BIOSGUARD_COMMAND_END;
    mBiosGuardUpdatePackagePtr->BgupHeader.ScriptSectionSize           = (mBiosGuardUpdateCounter * 8);

    ///
    /// Copy the BIOS Guard Update Data member variable into the BGUP buffer directly after the "End" command
    ///
    CopyMem (
      &mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter],
      &mBiosGuardUpdateData,
      (mBiosGuardUpdatePackagePtr->BgupHeader.DataSectionSize)
      );
  } else {
    ///
    /// If the Update Package was retrieved from the OS via Global NVS and IO Trap then require it to be signed
    ///
    if (mBiosGuardUpdatePackagePtr->BgupHeader.PkgAttributes) {
      BiosGuardInstance->BiosGuardDirectory[EnumBgupCertificate]  = mBgupCertificate;
      BiosGuardInstance->BiosGuardDirectory[EnumBgupCertificate] |= LShiftU64 (BIOSGUARD_DIRECTORY_BGUP_CERTIFICATE_ENTRY, 56);
      BiosGuardInstance->BiosGuardDirectory[EnumBiosGuardLog]     = (EFI_PHYSICAL_ADDRESS) mBiosGuardLogPtr;
      BiosGuardInstance->BiosGuardDirectory[EnumBiosGuardLog]    |= LShiftU64 (BIOSGUARD_DIRECTORY_BIOSGUARD_LOG_ENTRY, 56);
    } else {
      /// BIOS Updates will not be allowed to be passed through when there is no certificate required
      DisallowedUpdate = TRUE;
    }
  }

  ///
  /// BIOS Guard should prevent Overclocking Watchdog Timer timeout during script execution by disabling it.
  /// BIOS Guard module execution is prevented when Overclocking Watchdog Timer is locked and enabled.
  ///
  if (IsWdtEnabled ()) {
    OcWdtEnabled = TRUE;

    if (!IsWdtLocked ()) {
      ///
      /// Disable Overclocking Watchdog Timer
      ///
      WdtDisable ();
      OcWdtEnabled = FALSE;

      ///
      /// Overclocking Watchdog Timer will be reloaded after BIOS Guard module execution
      ///
      ReloadOcWdt  = TRUE;
    }
  }

  do {
    if ((RetryTrigger != 0) && (BiosGuardAdditionalData != ERR_OK)) {
      DEBUG ((DEBUG_INFO, "BiosGuardProtocolExecute Retry: %x of 3\n", RetryTrigger));
    }

    if (!DisallowedUpdate && !OcWdtEnabled) {
      mWaitTriggerAbort = BIOSGUARD_MODULE_EXECUTE_WAIT;
      mApThreadCount    = 0;

      ///
      /// Prior to launching the BIOS Guard Binary on the BSP, each of the APs must launch the BIOS Guard binary so that
      /// they can be accounted for and placed in sleep by the BIOS Guard binary.
      ///
      for (Index = 0; Index < gSmst->NumberOfCpus; Index++) {
        if (Index != gSmst->CurrentlyExecutingCpu) {
          Status = gSmst->SmmStartupThisAp (BiosGuardModuleExecute, Index, (VOID *) BiosGuardInstance);
          ASSERT_EFI_ERROR (Status);
        }
      }

      BiosGuardModuleExecute ((VOID *) BiosGuardInstance);

      ///
      /// Reload Overclocking Watchdog Timer if it was enabled prior to BIOS Guard module execution
      ///
      if (ReloadOcWdt) {
        WdtReloadAndStart (OC_WDT_TIMEOUT_VALUE);
      }

      if (mWaitTriggerAbort != BIOSGUARD_MODULE_EXECUTE_ABORT) {

        //
        // Wait for System BSP to complete and BIOS Guard Status is valid.
        //
        while (mWaitTriggerAbort == BIOSGUARD_MODULE_EXECUTE_WAIT) {
          CpuPause ();
        }

        BiosGuardStatus = (UINT16) RShiftU64 (
                                     (BiosGuardInstance->MsrValue & LShiftU64 (V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_STATUS_MASK,
                                                                      N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_STATUS_OFFSET)),
                                     N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_STATUS_OFFSET
                                     );

        switch (BiosGuardStatus) {
          case ERR_OK:
            Status = EFI_SUCCESS;
            break;

          case ERR_RANGE_VIOLATION:
          case ERR_SFAM_VIOLATION:
          case ERR_EXEC_LIMIT:
          case ERR_INTERNAL_ERROR:
            Status = EFI_DEVICE_ERROR;
            break;

          case ERR_UNSUPPORTED_CPU:
          case ERR_UNDEFINED_FLASH_OBJECT:
          case ERR_LAUNCH_FAIL:
            Status = EFI_UNSUPPORTED;
            break;

          default:

          case ERR_BAD_DIRECTORY:
          case ERR_BAD_BGPDT:
          case ERR_BAD_BGUP:
          case ERR_SCRIPT_SYNTAX:
          case ERR_INVALID_LINE:
          case ERR_BAD_BGUPC:
          case ERR_BAD_SVN:
          case ERR_UNEXPECTED_OPCODE:
          case ERR_OVERFLOW:
            Status = EFI_INVALID_PARAMETER;
        }
      } else {
        Status = EFI_DEVICE_ERROR;
      }
    } else {
      Status = EFI_UNSUPPORTED;
    }

    BiosGuardAdditionalData = (UINT16) RShiftU64 (
                                         (BiosGuardInstance->MsrValue & LShiftU64 (V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_DATA_MASK,
                                                                          N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_DATA_OFFSET)),
                                         N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_DATA_OFFSET
                                         );

    if ((EFI_ERROR (Status)) || (BiosGuardAdditionalData != ERR_OK)) {
      BiosGuardTerminalLine = (UINT16) RShiftU64 (
                                         (BiosGuardInstance->MsrValue & LShiftU64 (V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_TERMINAL_MASK,
                                                                          N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_TERMINAL_OFFSET)),
                                         N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_TERMINAL_OFFSET
                                         );
      BiosGuardSE = (UINT8) RShiftU64 (
                              (BiosGuardInstance->MsrValue & B_MSR_PLAT_FRMW_PROT_TRIG_PARAM_SE),
                              N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_SE_OFFSET
                              );
      DEBUG ((DEBUG_ERROR, "BIOS Guard Status            = 0x%X\n", BiosGuardStatus));
      DEBUG ((DEBUG_ERROR, "BIOS Guard Additional Data   = 0x%X\n", BiosGuardAdditionalData));
      DEBUG ((DEBUG_ERROR, "BIOS Guard Terminal Line     = 0x%X\n", BiosGuardTerminalLine));
      DEBUG ((DEBUG_ERROR, "BIOS Guard SE                = 0x%X\n", BiosGuardSE));
      if (DisallowedUpdate) {
        DEBUG ((DEBUG_ERROR, "BIOS Guard Disallowed Update\n"));
      }
      if (mWaitTriggerAbort == BIOSGUARD_MODULE_EXECUTE_ABORT) {
        DEBUG ((DEBUG_ERROR, "AP Timeout\n"));
      }
      if (OcWdtEnabled) {
        DEBUG ((DEBUG_ERROR, "Overclocking Watchdog Timer is enabled and locked\n"));
      }

      RetryTrigger++;
    }
  } while ((BiosGuardAdditionalData != ERR_OK) && (RetryTrigger < 4));

  mBiosGuardFullStatus = BiosGuardInstance->MsrValue;

  BiosGuardInstance->BiosGuardDirectory[EnumBgupCertificate] = 0;
  BiosGuardInstance->BiosGuardDirectory[EnumBgupCertificate] |= LShiftU64 (BIOSGUARD_DIRECTORY_UNDEFINED_ENTRY, 56);
  BiosGuardInstance->BiosGuardDirectory[EnumBiosGuardLog]    = 0;
  BiosGuardInstance->BiosGuardDirectory[EnumBiosGuardLog]    |= LShiftU64 (BIOSGUARD_DIRECTORY_UNDEFINED_ENTRY, 56);
  ZeroMem (mBiosGuardUpdatePackagePtr, mBiosGuardMemSize);
  CopyMem (&mBiosGuardUpdatePackagePtr->BgupHeader, &mBiosGuardBgupHeaderTemp, sizeof (BGUP_HEADER));
  mBiosGuardUpdatePackagePtr->BgupHeader.ScriptSectionSize    = 0;
  mBiosGuardUpdatePackagePtr->BgupHeader.DataSectionSize      = 0;
  mBiosGuardUpdateCounter = 0;

  ///
  /// Prep for the next script execution by adding the Begin command
  ///
  mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter++] = BIOSGUARD_COMMAND_BEGIN;

  return Status;
}

/**
  This service fills BIOS Guard script buffer for flash writes.
  BIOS should invoke this function prior to calling BIOSGUARD_PROTOCOL.Execute() with all the relevant data required for flash write.
  This function will not invoke BIOS Guard Module, only create script required for writing to flash.
  This function would be called by runtime driver, please do not use any MMIO macro here.

  @param[in] This           Pointer to the BIOSGUARD_PROTOCOL instance.
  @param[in] Offset         This value specifies the offset from the start of the SPI Flash component.
  @param[in] DataByteCount  Number of bytes in the data portion.
  @param[in] Buffer         Pointer to caller-allocated buffer containing the data sent.
**/
VOID
EFIAPI
BiosGuardProtocolWrite (
  IN BIOSGUARD_PROTOCOL *This,
  IN UINTN              Offset,
  IN UINT32             DataByteCount,
  IN OUT UINT8          *Buffer
  )
{
  ///
  /// Set Buffer Offset Index immediate command
  ///
  mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter++] =
    (LShiftU64 ((UINTN) mBiosGuardUpdatePackagePtr->BgupHeader.DataSectionSize, 32)) |
    (LShiftU64 (BIOSGUARD_B0_INDEX, 16)) |
    BIOSGUARD_COMMAND_SET_BUFFER_INDEX;
  ///
  /// Set Flash Index immediate command
  ///
  mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter++] = (LShiftU64 (Offset, 32)) | (LShiftU64 (BIOSGUARD_F0_INDEX, 16)) | BIOSGUARD_COMMAND_SET_FLASH_INDEX;
  ///
  /// Write to Flash Index from Buffer Offset Index with specific Size command
  ///
  mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter++] = (LShiftU64 (DataByteCount, 32)) | (LShiftU64 (BIOSGUARD_B0_INDEX, 24)) | (LShiftU64 (BIOSGUARD_F0_INDEX, 16)) | BIOSGUARD_COMMAND_WRITE_IMM;

  ///
  /// Read hardware status
  ///
  mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter++] = (LShiftU64 (BIOSGUARD_IF_INDEX, 16)) | BIOSGUARD_COMMAND_RD_STS;

  ///
  /// Place the data from the caller into the global BIOS Guard Update data
  ///
  CopyMem (&mBiosGuardUpdateData[mBiosGuardUpdatePackagePtr->BgupHeader.DataSectionSize], Buffer, DataByteCount);

  ///
  /// Update the size of the data section to match the input data size
  ///
  mBiosGuardUpdatePackagePtr->BgupHeader.DataSectionSize += DataByteCount;

  return;
}

/**
  This service fills BIOS Guard script buffer for erasing blocks in flash.
  BIOS should invoke this function prior to calling BIOSGUARD_PROTOCOL.Execute() with all the relevant data required for flash erase.
  This function will not invoke BIOS Guard module, only create script required for erasing each block in the flash.
  This function would be called by runtime driver, please do not use any MMIO macro here.

  @param[in] This     Pointer to the BIOSGUARD_PROTOCOL instance.
  @param[in] Offset   This value specifies the offset from the start of the SPI Flash component.
**/
VOID
EFIAPI
BiosGuardProtocolBlockErase (
  IN BIOSGUARD_PROTOCOL *This,
  IN UINTN              Offset
  )
{
  ///
  /// Set Flash Index immediate command
  ///
  mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter++] = (LShiftU64 (Offset, 32)) | (LShiftU64 (BIOSGUARD_F0_INDEX, 16)) | BIOSGUARD_COMMAND_SET_FLASH_INDEX;

  ///
  /// Erase Flash Index command
  ///
  mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter++] = (LShiftU64 (BIOSGUARD_F0_INDEX, 16)) | BIOSGUARD_COMMAND_ERASE_BLK;

  ///
  /// Read hardware status
  ///
  mBiosGuardUpdatePackagePtr->BgupBuffer[mBiosGuardUpdateCounter++] = (LShiftU64 (BIOSGUARD_IF_INDEX, 16)) | BIOSGUARD_COMMAND_RD_STS;

  ///
  /// No change necessary to the data section size
  ///
  mBiosGuardUpdatePackagePtr->BgupHeader.DataSectionSize += 0;

  return;
}
