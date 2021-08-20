/** @file
  Header file for the NEM Map Library.

@copyright
 Copyright (c) 2017 - 2019 Intel Corporation. All rights reserved
 This software and associated documentation (if any) is furnished
 under a license and may only be used or copied in accordance
 with the terms of the license. Except as permitted by the
 license, no part of this software or documentation may be
 reproduced, stored in a retrieval system, or transmitted in any
 form or by any means without the express written consent of
 Intel Corporation.
 This file contains an 'Intel Peripheral Driver' and is uniquely
 identified as "Intel Reference Module" and is licensed for Intel
 CPUs and chipsets under the terms of your license agreement with
 Intel or your vendor. This file may be modified by the user, subject
 to additional terms of the license agreement.

@par Specification
**/

#ifndef _NEM_MAP_LIB_H_
#define _NEM_MAP_LIB_H_

#include <Uefi.h>

/**
  Determines the Intel Boot Block (IBB) base address and size.

  @param[out] IbbBase         The IBB base address.
  @param[out] IbbSize         The IBB size.

  @retval       EFI_SUCCESS       The operation completed successfully.
  @retval       EFI_NOT_FOUND     The gNemMapStructureHobGuid was not found.
  @retval       EFI_DEVICE_ERROR  The GUID in the NEM map structure is invalid.
**/
EFI_STATUS
EFIAPI
GetIbbBaseAndSize (
  OUT UINTN     *IbbBase, OPTIONAL
  OUT UINT32    *IbbSize  OPTIONAL
  );

/**
  Determines the Non-Eviction Mode (NEM) region base address and size.

  @param[out] NemBase         The NEM region base address.
  @param[out] NemSize         The NEM region size.

  @retval       EFI_SUCCESS       The operation completed successfully.
  @retval       EFI_NOT_FOUND     The gNemMapStructureHobGuid was not found.
  @retval       EFI_DEVICE_ERROR  The GUID in the NEM map structure is invalid.
**/
EFI_STATUS
EFIAPI
GetNemBaseAndSize (
  OUT UINTN       *NemBase, OPTIONAL
  OUT UINT32      *NemSize  OPTIONAL
  );

/**
  Determines the Temporary RAM (T-RAM) base address and size.

  @param[out] TempRamBase     The T-RAM base address.
  @param[out] TempRamSize     The T-RAM size.

  @retval       EFI_SUCCESS       The operation completed successfully.
  @retval       EFI_NOT_FOUND     The gNemMapStructureHobGuid was not found.
  @retval       EFI_DEVICE_ERROR  The GUID in the NEM map structure is invalid.
**/
EFI_STATUS
EFIAPI
GetTempRamBaseAndSize (
  OUT UINTN       *TempRamBase, OPTIONAL
  OUT UINT32      *TempRamSize  OPTIONAL
  );

/**
  Determines the Firmware Interface Table (FIT) base address.

  @param[out]   FitBase           The FIT base address.

  @retval       EFI_SUCCESS       The operation completed successfully.
  @retval       EFI_NOT_FOUND     The gNemMapStructureHobGuid was not found
  @retval       EFI_NOT_FOUND     The FIT table could not be found (or is no longer available)
  @retval       EFI_DEVICE_ERROR  The GUID in the NEM map structure is invalid.
**/
EFI_STATUS
EFIAPI
GetFitBase (
  OUT UINTN       *FitBase
  );

/**
  Copies FIT data from a pre-existing FIT location to a FIT HOB.

  Future FIT API requests will return information from the FIT HOB after this API is invoked. The FIT entries
  may be trimmed to BIOS-relevant entries to reduce memory consumption. This allows the total HOB size to be less
  than the maximum HOB size and reduces memory usage if this API is used in pre-memory.

  @param[in]  FitSourceBase         The base address of a pre-existing FIT.

  @retval     EFI_SUCCESS           The FIT HOB was produced successfully.
  @retval     EFI_INVALID_PARAMETER The parameter given is invalid.
  @retval     EFI_NOT_FOUND         The source FIT table could not be found.
**/
EFI_STATUS
EFIAPI
ProduceFitHob (
  IN UINTN FitSourceBase
  );

#endif
