//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/**
  Header file to Manage & verify Timebased Authenticated varaibles in KeyEnroll tool.

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _AUTH_VARIABLE_H
#define _AUTH_VARIABLE_H

#include "KeyEnroll.h"
#include "VariableCommon.h"
#include "AuthVarCertDB.h"
#include "Pkcs7Verify.h"

/**
  The 3rd parameter of Pkcs7GetSigners will return all embedded
  X.509 certificate in one given PKCS7 signature. The format is:
  //
  // UINT8  CertNumber;
  // UINT32 Cert1Length;
  // UINT8  Cert1[];
  // UINT32 Cert2Length;
  // UINT8  Cert2[];
  // ...
  // UINT32 CertnLength;
  // UINT8  Certn[];
  //

  The two following C-structure are used for parsing CertStack more clearly.
**/
#pragma pack(1)

typedef struct {
  UINT32    CertDataLength;       // The length in bytes of X.509 certificate.
  UINT8     CertDataBuffer[1];    // The X.509 certificate content (DER).
} EFI_CERT_DATA;

typedef struct {
  UINT8             CertNumber;   // Number of X.509 certificate.
  //EFI_CERT_DATA   CertArray[];  // An array of X.509 certificate.
} EFI_CERT_STACK;

#pragma pack()

/*
  Process variable with EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS set.

  @param[in]    Name                      Name of Variable to be processed.
  @param[in]    Guid                      Variable vendor GUID.
  @param[in]    Data                      Data pointer.
  @param[in]    DataSize                  The size of Data in bytes.
  @param[in]    Attributes                Attribute value of the variable.
  @param[in]    OperType                  The operation type about variable.

  @retval       EFI_SUCCESS               The operation is finished successfully.
  @retval       EFI_INVALID_PARAMETER     Invalid input parameters, Name, Guid or Data is NULL.
  @retval       EFI_OUT_OF_RESOURCES      No more memory for allocation.
  @retval       Others                    Other errors as indicated.
*/
EFI_STATUS
ProcessAuthVar (
  IN    CHAR8                       *Name,
  IN    EFI_GUID                    *Guid,
  IN    VOID                        *Data,
  IN    UINTN                       DataSize,
  IN    UINT32                      Attributes,
  IN    EFI_COMMAND_OPER_TYPE       OperType
  );

#endif
