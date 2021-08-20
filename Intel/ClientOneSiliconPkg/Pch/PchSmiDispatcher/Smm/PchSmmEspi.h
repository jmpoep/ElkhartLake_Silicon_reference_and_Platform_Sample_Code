/** @file
  eSPI SMI Dispatch header

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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

#ifndef _PCH_SMM_ESPI_H_
#define _PCH_SMM_ESPI_H_

#include "PchSmmHelpers.h"

#define ESPI_SMI_INSTANCE_SIGNATURE       SIGNATURE_32 ('E', 'S', 'P', 'I')
#define ESPI_SMI_RECORD_SIGNATURE         SIGNATURE_32 ('E', 'S', 'R', 'C')

#define ESPI_INSTANCE_FROM_THIS(_this)      CR (_this, ESPI_SMI_INSTANCE, EfiEspiSmiDispatchProtocol, ESPI_SMI_INSTANCE_SIGNATURE)
#define ESPI_RECORD_FROM_LINK(_link)        CR (_link, ESPI_SMI_RECORD, Link, ESPI_SMI_RECORD_SIGNATURE)

typedef enum {
  EspiBiosWrProtect,    ///< BIOS Write Protect
  EspiSerialIrq,        ///< eSPI Master Asserted SMI
  EspiPmc,              ///< eSPI PMC SMI
  EspiTopLevelTypeMax
} ESPI_TOP_LEVEL_TYPE;

typedef enum {
  BiosWrProtect,        ///< BIOS Write Protect
  BiosWrReport,         ///< Peripheral Channel BIOS Write Protect
  PcNonFatalErr,        ///< Peripheral Channel Non Fatal Error
  PcFatalErr,           ///< Peripheral Channel Fatal Error
  VwNonFatalErr,        ///< Virtual Wire Non Fatal Error
  VwFatalErr,           ///< Virtual Wire Fatal Error
  FlashNonFatalErr,     ///< Flash Channel Non Fatal Error
  FlashFatalErr,        ///< Flash Channel Fatal Error
  LnkType1Err,          ///< Link Error
  EspiSlaveSmi,         ///< Espi Slave SMI
  EspiSmiTypeMax
} ESPI_SMI_TYPE;

///
/// This is used to classify ESPI_SMI_TYPE to ESPI_TOP_LEVEL_TYPE.
/// Used during dispatching and unregistering
///
typedef struct {
  ESPI_SMI_TYPE Start;
  ESPI_SMI_TYPE End;
} ESPI_SMI_TYPE_BARRIER;

typedef struct _ESPI_SMI_INSTANCE {
  ///
  /// Signature associated with this instance
  ///
  UINT32                          Signature;
  ///
  /// EFI_HANDLE acquired when installing PchEspiSmiDispatchProtocol
  ///
  EFI_HANDLE                      Handle;
  ///
  /// The protocol to register or unregister eSPI SMI callbacks
  ///
  PCH_ESPI_SMI_DISPATCH_PROTOCOL  PchEspiSmiDispatchProtocol;
  ///
  /// The handle acquired when registering eSPI SMI callback to PchSmiDispatch
  ///
  EFI_HANDLE                      PchSmiEspiHandle[EspiTopLevelTypeMax];
  ///
  /// The linked list for record database.
  ///
  LIST_ENTRY                      CallbackDataBase[EspiSmiTypeMax];
  ///
  /// This is an internal counter to track the number of eSPI master events have been registered.
  /// When unregistering, we can disable the SMI if the counter is zero
  ///
  UINTN                           EspiSmiEventCounter[EspiSmiTypeMax];
  ///
  /// Instance of barrier
  ///
  CONST ESPI_SMI_TYPE_BARRIER     Barrier[EspiTopLevelTypeMax];
} ESPI_SMI_INSTANCE;

typedef struct _ESPI_DESCRIPTOR {
  PCH_SMM_ADDRESS   Address;
  UINT32            SourceIsActiveAndMask;
  UINT32            SourceIsActiveValue;
  UINT32            ClearStatusAndMask;
  UINT32            ClearStatusOrMask;
} ESPI_DESCRIPTOR;

///
/// A simple record to store the callbacks associated with an eSPI SMI source
///
typedef struct _ESPI_SMI_RECORD {
  UINT32                          Signature;
  LIST_ENTRY                      Link;
  PCH_ESPI_SMI_DISPATCH_CALLBACK  Callback;
} ESPI_SMI_RECORD;

/**
  Installs and initialize this protocol

  @param[in]  ImageHandle   Not used

  @retval     EFI_SUCCESS   Installation succeed
  @retval     others        Installation failed
**/
EFI_STATUS
EFIAPI
InstallEspiSmi (
  IN EFI_HANDLE           ImageHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to register a BIOS Write Protect event

  @param[in]  This              Not used
  @param[in]  DispatchFunction  The callback to execute
  @param[out] DispatchHandle    The handle for this callback registration

  @retval     EFI_SUCCESS       Registration succeed
  @retval     EFI_ACCESS_DENIED Return access denied if the SmmReadyToLock event has been triggered
  @retval     others            Registration failed
**/
EFI_STATUS
EFIAPI
BiosWrProtectRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL  *This,
  IN  PCH_ESPI_SMI_DISPATCH_CALLBACK  DispatchFunction,
  OUT EFI_HANDLE                      *DispatchHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to register a BIOS Write Report event

  @param[in]  This              Not used
  @param[in]  DispatchFunction  The callback to execute
  @param[out] DispatchHandle    The handle for this callback registration

  @retval     EFI_SUCCESS       Registration succeed
  @retval     EFI_ACCESS_DENIED Return access denied if the SmmReadyToLock event has been triggered
  @retval     others            Registration failed
**/
EFI_STATUS
EFIAPI
BiosWrReportRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL  *This,
  IN  PCH_ESPI_SMI_DISPATCH_CALLBACK  DispatchFunction,
  OUT EFI_HANDLE                      *DispatchHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to register a Peripheral Channel Non Fatal Error event

  @param[in]  This              Not used
  @param[in]  DispatchFunction  The callback to execute
  @param[out] DispatchHandle    The handle for this callback registration

  @retval     EFI_SUCCESS       Registration succeed
  @retval     EFI_ACCESS_DENIED Return access denied if the SmmReadyToLock event has been triggered
  @retval     others            Registration failed
**/
EFI_STATUS
EFIAPI
PcNonFatalErrRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL  *This,
  IN  PCH_ESPI_SMI_DISPATCH_CALLBACK  DispatchFunction,
  OUT EFI_HANDLE                      *DispatchHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to register a Peripheral Channel Fatal Error event

  @param[in]  This              Not used
  @param[in]  DispatchFunction  The callback to execute
  @param[out] DispatchHandle    The handle for this callback registration

  @retval     EFI_SUCCESS       Registration succeed
  @retval     EFI_ACCESS_DENIED Return access denied if the SmmReadyToLock event has been triggered
  @retval     others            Registration failed
**/
EFI_STATUS
EFIAPI
PcFatalErrRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL  *This,
  IN  PCH_ESPI_SMI_DISPATCH_CALLBACK  DispatchFunction,
  OUT EFI_HANDLE                      *DispatchHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to register a Virtual Wire Non Fatal Error event

  @param[in]  This              Not used
  @param[in]  DispatchFunction  The callback to execute
  @param[out] DispatchHandle    The handle for this callback registration

  @retval     EFI_SUCCESS       Registration succeed
  @retval     EFI_ACCESS_DENIED Return access denied if the SmmReadyToLock event has been triggered
  @retval     others            Registration failed
**/
EFI_STATUS
EFIAPI
VwNonFatalErrRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL  *This,
  IN  PCH_ESPI_SMI_DISPATCH_CALLBACK  DispatchFunction,
  OUT EFI_HANDLE                      *DispatchHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to register a Virtual Wire Fatal Error event

  @param[in]  This              Not used
  @param[in]  DispatchFunction  The callback to execute
  @param[out] DispatchHandle    The handle for this callback registration

  @retval     EFI_SUCCESS       Registration succeed
  @retval     EFI_ACCESS_DENIED Return access denied if the SmmReadyToLock event has been triggered
  @retval     others            Registration failed
**/
EFI_STATUS
EFIAPI
VwFatalErrRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL  *This,
  IN  PCH_ESPI_SMI_DISPATCH_CALLBACK  DispatchFunction,
  OUT EFI_HANDLE                      *DispatchHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to register a Flash Channel Non Fatal Error event

  @param[in]  This              Not used
  @param[in]  DispatchFunction  The callback to execute
  @param[out] DispatchHandle    The handle for this callback registration

  @retval     EFI_SUCCESS       Registration succeed
  @retval     EFI_ACCESS_DENIED Return access denied if the SmmReadyToLock event has been triggered
  @retval     others            Registration failed
**/
EFI_STATUS
EFIAPI
FlashNonFatalErrRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL  *This,
  IN  PCH_ESPI_SMI_DISPATCH_CALLBACK  DispatchFunction,
  OUT EFI_HANDLE                      *DispatchHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to register a Flash Channel Fatal Error event

  @param[in]  This              Not used
  @param[in]  DispatchFunction  The callback to execute
  @param[out] DispatchHandle    The handle for this callback registration

  @retval     EFI_SUCCESS       Registration succeed
  @retval     EFI_ACCESS_DENIED Return access denied if the SmmReadyToLock event has been triggered
  @retval     others            Registration failed
**/
EFI_STATUS
EFIAPI
FlashFatalErrRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL  *This,
  IN  PCH_ESPI_SMI_DISPATCH_CALLBACK  DispatchFunction,
  OUT EFI_HANDLE                      *DispatchHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to register a Link Error event

  @param[in]  This              Not used
  @param[in]  DispatchFunction  The callback to execute
  @param[out] DispatchHandle    The handle for this callback registration

  @retval     EFI_SUCCESS       Registration succeed
  @retval     EFI_ACCESS_DENIED Return access denied if the SmmReadyToLock event has been triggered
  @retval     others            Registration failed
**/
EFI_STATUS
EFIAPI
LnkType1ErrRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL  *This,
  IN  PCH_ESPI_SMI_DISPATCH_CALLBACK  DispatchFunction,
  OUT EFI_HANDLE                      *DispatchHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to register a eSPI slave SMI
  NOTE: The register function is not available when the ESPI_SMI_LOCK bit is set.
        This runtine will also lock donw ESPI_SMI_LOCK bit after registration and
        prevent this handler from unregistration.
  On platform that supports more than 1 device through another chip select (SPT-H),
  the SMI handler itself needs to inspect both the eSPI devices' interrupt status registers
  (implementation specific for each Slave) in order to identify and service the cause.
  After servicing it, it has to clear the Slaves' internal SMI# status registers

  @param[in]  This                      Not used
  @param[in]  DispatchFunction          The callback to execute
  @param[out] DispatchHandle            The handle for this callback registration

  @retval     EFI_SUCCESS               Registration succeed
  @retval     EFI_ACCESS_DENIED         Return access denied if the SmmReadyToLock event has been triggered
  @retval     EFI_ACCESS_DENIED         The ESPI_SMI_LOCK is set and register is blocked.
  @retval     others                    Registration failed
**/
EFI_STATUS
EFIAPI
EspiSlaveSmiRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL    *This,
  IN  PCH_ESPI_SMI_DISPATCH_CALLBACK    DispatchFunction,
  OUT EFI_HANDLE                        *DispatchHandle
  );

/**
  eSPI SMI Dispatch Protocol instance to unregister a callback based on handle

  @param[in]  This                    Not used
  @param[in]  DispatchHandle          Handle acquired during registration

  @retval     EFI_SUCCESS             Unregister successful
  @retval     EFI_INVALID_PARAMETER   DispatchHandle is null
  @retval     EFI_INVALID_PARAMETER   DispatchHandle's forward link has bad pointer
  @retval     EFI_INVALID_PARAMETER   DispatchHandle does not exist in database
  @retval     EFI_ACCESS_DENIED       Unregistration is done after end of DXE
  @retval     EFI_ACCESS_DENIED       DispatchHandle is not allowed to unregistered
**/
EFI_STATUS
EFIAPI
EspiSmiUnRegister (
  IN  PCH_ESPI_SMI_DISPATCH_PROTOCOL  *This,
  IN  EFI_HANDLE                      DispatchHandle
  );

/**
  eSPI SMI handler for Fatal Error recovery flow

  @param[in]  DispatchHandle          Handle acquired during registration
**/
VOID
EspiDefaultFatalErrorHandler (
  VOID
  );


#endif
