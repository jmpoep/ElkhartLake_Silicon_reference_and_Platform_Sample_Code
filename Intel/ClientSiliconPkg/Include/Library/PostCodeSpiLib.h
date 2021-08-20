/** @file
  Provides services to send progress/error codes to a POST card.

Copyright (c) 2018 - 2019, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __POST_CODE_SPI_LIB_H__
#define __POST_CODE_SPI_LIB_H__

#define    SERIAL_IO_SPI_POSTCODE_NUMBER   1

/**
  Write the Postcode's Phase Status code value into a scratchpad register

  @param[in]  PhaseCode - The PhaseCode value to save to scratchpad register

  @retval     None
**/
VOID
SetPhaseStatusCodeToScratchpadReg (
  UINT32 PhaseCode
  );

/**
Provide Post Code to a serial device Max6950

@param[in]    Same as ReportStatusCode PPI

**/
UINT32
EFIAPI
PostCode (
  IN UINT32  Value
  );
#endif
