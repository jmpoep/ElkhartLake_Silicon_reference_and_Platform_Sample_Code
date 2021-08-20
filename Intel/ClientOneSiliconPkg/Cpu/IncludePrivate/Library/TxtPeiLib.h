/** @file
  This file contains function definitions that can determine
  the TXT capabilities of a platform during PEI and perform
  certain specific platform tasks that are required for TXT
  during PEI.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

#ifndef _TXT_PEI_LIB_H_
#define _TXT_PEI_LIB_H_

#include <Library/PeiServicesLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include "Txt.h"
#include "CpuAccess.h"
#include <TxtInfoHob.h>
#include <Ppi/SiPolicy.h>
#include <Ppi/TpmInitialized.h>
#include <Library/PchCycleDecodingLib.h>
#include <Acm.h>

#define APIC_SPURIOUS_VECTOR_REGISTER 0xF0       ///< Offset of local APIC register
#define BASE_ADDR_MASK                0xFFFFF000 ///< Local APIC base address mask

#define TEST_PATTERN                  0x5A5A5A5A
//
// EDI parameter sent to SCHECK function
//
#define COLD_BOOT_PATH      0
#define S3_RESUME_PATH      1
///
/// Chipset register
///
#define TXT_OPT_IN_VMX_AND_SMX_MSR_VALUE    0xFF03


///
/// TXT PEI Context
///
typedef struct _TXT_PEI_LIB_CONTEXT {
  CONST EFI_PEI_SERVICES  **PeiServices;   ///< PeiServices pointer
  ACM_HEADER       *BiosAcmBase;           ///< Pointer to Bios ACM Base which is the ACM header
  UINT32           BiosAcmSize;            ///< BiosAc.bin size
  VOID             *ApStartup;             ///< ApStartup Address
  UINT32           Ia32ApicBase;           ///< ApicBase Address
  TXT_INFO_HOB     *Hob;                   ///< Txt Info HOB
} TXT_PEI_LIB_CONTEXT;

/**
  Processor Signature Structure
**/
typedef struct _PSS {
  UINT32 signature;     ///< PSS Processor Signature
  UINT32 procFlags;     ///< PSS Processor Flags (Platform ID)
  UINT32 checksum;      ///< PSS Checksum
} PSS;

/**
  Execute SCLEAN through BIOS ACM
**/
VOID
LaunchBiosAcmSclean (
  VOID
  );


/**
  Execute CLEAR SECRETS through BIOS ACM
**/
VOID
LaunchBiosAcmClearSecrets (
  VOID
  );

/**
  Execute ACHECK through BIOS ACM
**/
VOID
LaunchBiosAcmAcheck (
  VOID
  );

/**
  Issue a cpu-only reset through PCH and PORTCF9
**/
VOID
DoCpuReset (
  VOID
  );

/**
  Issue a HOST reset through PCH and PORTCF9
**/
VOID
DoHostReset (
  VOID
  );

/**
  Function is called in memory present environment on S3 resume
  path. Saves contents of all MTRRs into table plus some registers.

  @param[in]   ApCfg  - Base address of BIOS ACM location
**/

VOID
SaveApConfig (
  UINT64 *ApCfg
  );

/**
  Function is called in memory present environment on S3 resume path.
  Saves contents of all MTRRs into table plus some registers.

  @param[in]   BiosAcAddr - Point to BiosAc address in flash
**/
VOID
LaunchBiosAcm (
  IN UINT64 *BiosAcAddr,
  IN UINT64  Function,
  IN UINT64  BootMode
  );

/**
  Dispatch APs to execute *Function with parameter pointed by *Param

  @param[in] (*Function)  - Address of Function to be executed by APs
  @param[in] Param        - Function parameter to be passed to
**/
VOID
StartupAllAPs (
  VOID (*Function)(VOID *Param),
  UINT64 *Param
  );

/**
  Initial AP configuration for SCHECK on S3 resume

  @param[in] Param        - Function parameter to be passed to
**/
VOID
DoApInit (
  VOID *Param
  );

/**
  Put All APs into Wait-for-SIPI state
**/
VOID
PutApsInWfs (
  VOID
  );

/**
  Restore MTRR registers

  @param[in]  ApCfg - Point to the MTRR buffer
**/
VOID
RestoreMtrrProgramming (
  UINT64 *ApCfg
  );

/**
  Restore APs' registers

  @param[in]  ApCfg  - Point to APs' registers buffer
**/
VOID
RestoreApConfig (
  void *ApCfg
  );

/**
  Initializes values passed to AP

  @param[in] pctx      - A pointer to an initialized TXT PEI Context data structure
**/
VOID
PrepareApParams (
  IN TXT_INFO_HOB *TxtInfoHob
  );

/**
  This routine initializes and collects all PPIs and data required
  by the routines in this file.

  @param[in] pctx          - A pointer to an initialized TXT PEI Context data structure

  @exception EFI_UNSUPPORTED   - If any of the required PPIs or data are unavailable
  @retval EFI_SUCCESS       - In all cases not listed above
**/
EFI_STATUS
InitializeTxtPeiLib (
  IN TXT_INFO_HOB **TxtInfoHob
 );

/**
  Determines whether or not the current processor is TXT Capable.

  @retval TRUE          - If the current processor supports TXT
  @retval FALSE         - If the current processor does not support TXT
**/
BOOLEAN
IsTxtProcessor (
  VOID
  );

/**
  Determines whether or not the current chipset is TXT Capable.

  @param[in] pctx          - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If the current chipset supports TXT
  @retval FALSE         - If the current chipset doesn't supports TXT
**/
BOOLEAN
IsTxtChipset (
  VOID
  );

/**
  Determines whether or not POISON bit is set in status register

  @retval TRUE          - If the TPM reset bit is asserted.
  @retval FALSE         - If the TPM reset bit is unasserted.
**/
BOOLEAN
IsTxtResetSet (
  VOID
  );

/**
  Determines whether or not SECRETS.STS bit is set in E2STS status register

  @retval TRUE          - If the LT.SECRETS.STS bit is asserted.
  @retval FALSE         - If the LT.SECRETS.STS bit is unasserted.
**/
BOOLEAN
IsTxtSecretsSet (
  VOID
  );

/**
  Determines whether or not the platform has executed an TXT launch by
  examining the TPM Establishment bit.

  @param[in] pctx       - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If the TPM establishment bit is asserted.
  @retval FALSE         - If the TPM establishment bit is unasserted.
**/
BOOLEAN
TxtIsEstablishmentBitAsserted (
  IN TXT_INFO_HOB *TxtInfoHob
  );

/**
  Determines whether or not the platform has encountered an error during
  a sleep or power-off state.

  @retval TRUE          - If the TXT_WAKE_ERROR bit is asserted.
  @retval FALSE         - If the TXT_WAKE_ERROR bit is unasserted.
**/
BOOLEAN
IsTxtWakeError (
  VOID
  );

/**
  Determines whether or not the platform memory has been locked

  @retval TRUE          - If memroy is locked
  @retval FALSE         - If memory is unlocked
**/
BOOLEAN
IsMemoryLocked (
  VOID
  );

/**
  @param[in] pctx          - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If TXT is enabled by platform setting
  @retval FALSE         - If TXT is disabled by platform setting
**/
BOOLEAN
IsTxtEnabled (
  IN TXT_INFO_HOB *TxtInfoHob
  );

/**
  Determines whether Alias Check Request is enabled by platform setting

  @param[in] pctx          - A pointer to an initialized TXT PEI Context data structure

  @retval TRUE          - If ACHECK REQUEST is enabled by platform setting
  @retval FALSE         - If ACHECK REQUEST is disabled by platform setting
**/
BOOLEAN
IsAcheckRequested (
  IN TXT_INFO_HOB *TxtInfoHob
  );

/**
  Determines ACM is matched to chipset or not

  @param[in] pctx         - A pointer to an initialized TXT PEI Context data structure
  @param[in] BiosAcmBase  - A pointer to BIOS ACM location

  @retval TRUE          - BIOS ACM is matched to chipset
  @retval FALSE         - BIOS ACM is NOT matched to chipset
**/
BOOLEAN
CheckTxtAcmMatch (
  ACM_HEADER          *BiosAcmBase
  );

/**
  Clear Sleep Type register.

  @param[in] pctx          - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS   - Always
**/
EFI_STATUS
ClearSlpTyp (
  IN TXT_INFO_HOB *TxtInfoHob
  );

/**
Issue a Global Reset
**/
VOID
IssueGlobalReset(
  VOID
  );

/**
  Invokes the SCLEAN/ACHECK function from the TXT BIOS ACM.
  1. Clearing of sleep type is necessary because SCLEAN/ACHECK destroys memory
  context, so S3 after it is run and system is reset is impossible. We
  do it here since there is no any indication that can sustain reset
  for any other module to do it on our behalf.
  2. APs are initialized before calling of SCLEAN/ACHECK
  3. SCLEAN/ACHECK function is invoked.

  @param[in] pctx      - A pointer to an initialized TXT PEI Context data structure
  @param[in] func      - Acm function to be launch

  @retval EFI_SUCCESS   - Always.
**/
EFI_STATUS
DoAcmLaunch (
  IN TXT_INFO_HOB *TxtInfoHob,
  IN UINT8               func
  );

/**
  Determines presence of TPM in system

  @param[in] pctx         - Point to TXT_PEI_LIB_CONTEXT structure

  @retval EFI_SUCCESS          - If the TPM is present.
  @retval EFI_NOT_FOUND        - If the TPM is not present.
**/
EFI_STATUS
IsTpmPresent (
  IN TXT_INFO_HOB *TxtInfoHob
  );

/**
  Parses Hob list for TXT Info HOB

  @param[in] pctx          - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS   - If TXT Info Hob is found
  @retval EFI_NOT_FOUND - If TXT Info Hob is not found
**/
EFI_STATUS
CreateTxtInfoHob (
  IN TXT_INFO_HOB **TxtInfoHob
  );

/**
  Launching of SCHECK function from the TXT BIOS ACM.

  @param[in] pctx         - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS     - Always.
**/
EFI_STATUS
DoPeiLaunchAcm (
  IN EFI_PEI_SERVICES **PeiServices,
  IN TXT_INFO_HOB *TxtInfoHob,
  IN UINT64       Function,
  IN UINT64       BootMode
  );

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
  IN TXT_INFO_HOB *TxtInfoHob,
  IN UINT64*               SavedSmiSourcesVariablesPointer,
  IN BOOLEAN               Operation
  );

/**
  Unlock memory when security is set and TxT is not enabled

  @param[in] pctx      - A pointer to an initialized TXT PEI Context data structure

  @retval EFI_SUCCESS     - Complete memory unlock
  @exception EFI_UNSUPPORTED - CPU doesn't support TxT.
**/
EFI_STATUS
TxtUnlockMemory (
  IN TXT_INFO_HOB *TxtInfoHob
  );

/**
  Fix up pointers since they are located in real memory now.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The memory discovered PPI.  Not used.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
DprUpdate (
  IN TXT_INFO_HOB *TxtInfoHob
  );


/**
  Allocates 1 MB of 1MB-aligned memory for use as TXT Device Memory.  Records
  the location of TXT Device Memory in TXT Chipset registers and then adds
  programming instructions for these registers into BootScript.

  @param[in] TxtInfoHob          - A pointer to TXT PEI HOB data structure

  @retval     EFI_SUCCESS   TXT Device memory has been successfully initialized.
  @retval     EFI_ERROR     TXT Device memory not awailable.
**/


EFI_STATUS
SetupTxtDeviceMemory (
  IN TXT_INFO_HOB *TxtInfoHob,
  IN UINTN        CpuCount
  );


 /**
  Initialize Txt feature
**/
EFI_STATUS
TxtInit (
  VOID
  );

/**
  This is AliasCheck entry point for MRC call.  The routine checks for an TXT
  capable platform and determines whether ACHECK should be run.  If so,
  it launches the BIOS ACM to run ACHECK (which will reset the platform).
  The AliasCheck routine is in peitxtlib.

  @exception EFI_UNSUPPORTED  - If the platform is not TXT capable.
  @retval EFI_SUCCESS         - In all other cases not listed above.
**/

EFI_STATUS
EFIAPI
AliasCheck (
  VOID
  );

/**
  This is ClearSecretsBit entry point for MRC call.

  @exception EFI_UNSUPPORTED  - If the platform is not TXT capable.
  @retval EFI_SUCCESS         - In all other cases not listed above.
**/
EFI_STATUS
EFIAPI
ClearSecretsBit (
  VOID
  );

/**
  This is SetPowerDownRequest entry point for MRC call.

  @exception EFI_UNSUPPORTED  - If the platform is not TXT capable.
  @retval EFI_SUCCESS         - In all other cases not listed above.
**/
EFI_STATUS
EFIAPI
SetPowerDownRequest (
  VOID
  );

#endif
