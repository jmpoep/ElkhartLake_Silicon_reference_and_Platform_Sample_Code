/** @file
  Header file for BIOS Guard Driver.

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

#ifndef _BIOSGUARD_SERVICES_H_
#define _BIOSGUARD_SERVICES_H_

#include <Protocol/FirmwareVolume2.h>
#include <SaConfigHob.h>
#include <Protocol/SmmIoTrapDispatch2.h>
#include <BiosGuard.h>
#include <Library/AslUpdateLib.h>
#include <Protocol/CpuNvsArea.h>
#include <Protocol/BiosGuard.h>
#include <Protocol/BiosGuardNvsArea.h>

UINT8                mBiosGuardUpdateData[BGUP_TSEG_BUFFER_SIZE];
static UINT16        mBiosGuardUpdateCounter;
BGUP                 *mBiosGuardUpdatePackagePtr;
EFI_PHYSICAL_ADDRESS mBgupCertificate;
BIOSGUARD_LOG        *mBiosGuardLogPtr;
BIOSGUARD_LOG        mBiosGuardLogTemp;
BGUP_HEADER          mBiosGuardBgupHeaderTemp;
EFI_PHYSICAL_ADDRESS mBiosGuardMemAddress;
UINT32               mBiosGuardMemSize;
UINT64               mBiosGuardFullStatus;
UINT8                mBiosGuardUpdatePackageInTseg;

///
/// Private data structure definitions for the driver
///
#define BIOSGUARD_SIGNATURE  SIGNATURE_32 ('B', 'G', 'R', 'D')

#define BIOSGUARD_DIRECTORY_MAX_SIZE               6
#define BIOSGUARD_DIRECTORY_BIOSGUARD_MODULE_ENTRY 0x00
#define BIOSGUARD_DIRECTORY_BGPDT_ENTRY            0x01
#define BIOSGUARD_DIRECTORY_BGUP_ENTRY             0x02
#define BIOSGUARD_DIRECTORY_BGUP_CERTIFICATE_ENTRY 0x03
#define BIOSGUARD_DIRECTORY_BIOSGUARD_LOG_ENTRY    0x04
#define BIOSGUARD_DIRECTORY_UNDEFINED_ENTRY        0xFE
#define BIOSGUARD_DIRECTORY_END_MARKER             0xFF

///
/// Stall period in microseconds
///
#define BIOSGUARD_WAIT_PERIOD                      1
#define BIOSGUARD_AP_SAFE_RETRY_LIMIT              50

#define BIOSGUARD_MODULE_EXECUTE_WAIT              0
#define BIOSGUARD_MODULE_EXECUTE_TRIGGER           1
#define BIOSGUARD_MODULE_EXECUTE_ABORT             2

typedef enum {
  EnumBiosGuardModule        = 0,
  EnumBgpdt,
  EnumBgup,
  EnumBgupCertificate,
  EnumBiosGuardLog,
  EnumBiosGuardDirectoryEnd
} BIOSGUARD_DIRECTORY;

typedef struct {
  UINTN                Signature;
  EFI_HANDLE           Handle;
  BIOSGUARD_PROTOCOL   BiosGuardProtocol;
  EFI_PHYSICAL_ADDRESS BiosGuardDirectory[BIOSGUARD_DIRECTORY_MAX_SIZE];
  UINT64               MsrValue;
} BIOSGUARD_INSTANCE;

#define BIOSGUARD_INSTANCE_FROM_BIOSGUARDPROTOCOL(a)  CR (a, BIOSGUARD_INSTANCE, BiosGuardProtocol, BIOSGUARD_SIGNATURE)

/**
  Initialize BIOS Guard protocol instance.

  @param[in] BiosGuardInstance  Pointer to BiosGuardInstance to initialize

  @retval EFI_SUCCESS      The protocol instance was properly initialized
**/
EFI_STATUS
BiosGuardProtocolConstructor (
  BIOSGUARD_INSTANCE *BiosGuardInstance
  );

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
  IN VOID          *BiosGuardInstance
  );

/**
  This service will write BIOSGUARD_DIRECTORY MSR and invoke the BIOS Guard Module by writing to PLAT_FRMW_PROT_TRIGGER MSR for writing/erasing to flash.
  BIOS should invoke BIOSGUARD_PROTOCOL.Write() or BIOSGUARD_PROTOCOL.Erase() function prior to calling BIOSGUARD_PROTOCOL.Execute() for flash writes/erases (except for BiosUpdate).
  Write()/Erase() function will render BIOS Guard script during execution.
  Execute() function will implement the following steps:
  1. Update BIOS Guard directory with address of BGUP.
  2. All the AP's except the master thread are put to sleep.
  3. BIOS Guard module is invoked from BSP to execute desired operation.
  If BiosUpdate flag is set to true, BGUP (BGUP Header + BIOS Guard Script + Update data) is part of data that is passed to SMI Handler. SMI Handler invokes BIOS Guard module to process the update.
  This function would be called by runtime driver, please do not use any MMIO macro here.

  @param[in] This                Pointer to the BIOSGUARD_PROTOCOL instance.
  @param[in] BiosUpdate          Flag to indicate flash update is requested by the Tool

  @retval EFI_SUCCESS            Successfully completed flash operation.
  @retval EFI_INVALID_PARAMETER  The parameters specified are not valid.
  @retval EFI_UNSUPPORTED        The CPU or SPI memory is not supported.
  @retval EFI_DEVICE_ERROR       Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
BiosGuardProtocolExecute (
  IN BIOSGUARD_PROTOCOL *This,
  IN BOOLEAN            BiosUpdate
  );

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
  );

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
  );

#endif
