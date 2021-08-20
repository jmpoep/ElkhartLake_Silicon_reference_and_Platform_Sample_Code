
/** @file
  This PPI provides a service to explicitly measure firmware volumes.

@copyright
 Copyright (c) 2018 Intel Corporation. All rights reserved
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

#ifndef _PEI_TPM_MEASURE_PPI_H_
#define _PEI_TPM_MEASURE_PPI_H_

///
/// Global ID for the PEI_TPM_MEASURE_PPI.
///
#define PEI_TPM_MEASURE_PPI_GUID  \
  { \
    0x014ea963, 0x2ed4, 0x4876, { 0xbc, 0xdd, 0x59, 0x5e, 0xdf, 0x87, 0x1d, 0x56 } \
  }

///
/// Forward declaration for the PEI_TPM_MEASURE_PPI
///
typedef struct _PEI_TPM_MEASURE_PPI PEI_TPM_MEASURE_PPI;

/**
  Measure FV image.
  Add it into the measured FV list after the FV is measured successfully.

  @param[in]  FvBase            Base address of FV image.
  @param[in]  FvLength          Length of FV image.

  @retval EFI_SUCCESS           Fv image is measured successfully
                                or it has been already measured.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.

**/
typedef
EFI_STATUS
(EFIAPI *PEI_TPM_MEASURE_FV_IMAGE)(
  IN EFI_PHYSICAL_ADDRESS       FvBase,
  IN UINT64                     FvLength
  );

/**
  Measure main BIOS.

  @retval EFI_SUCCESS           Operation completed successfully.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.

**/
typedef
EFI_STATUS
(EFIAPI *PEI_TPM_MEASURE_MAIN_BIOS)(
  VOID
  );

///
/// This service provides the ability to explicitly measure firmware volumes.
///
struct _PEI_TPM_MEASURE_PPI {
  PEI_TPM_MEASURE_FV_IMAGE  MeasureFvImage;
  PEI_TPM_MEASURE_MAIN_BIOS MeasureMainBios;
};

extern EFI_GUID  gPeiTpmMeasurePpiGuid;

#endif
