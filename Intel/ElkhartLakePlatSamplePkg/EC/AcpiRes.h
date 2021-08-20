/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2016 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _ACPI_RES_DEFS
#define _ACPI_RES_DEFS

//AMP OP_CODE TYPE Definition
#define AML_OP_CODE     UINT8  //Normal OP_CODE
#define AML_EOP_CODE    UINT16 //Extended OP_CODE


//AML Name Object Size Preffix
#define AML_PR_BYTE     0x0A
#define AML_PR_WORD     0x0B
#define AML_PR_DWORD    0x0C
#define AML_PR_STRING   0x0D
#define AML_PR_QWORD    0x0E

#define AML_PR_DUALNAME 0x2E
#define AML_PR_MULTNAME 0x2F

#define AML_PR_EXTOP    0x5B //'['
#define AML_PR_ROOT     0x5C //'\'
#define AML_PR_PARENT   0x5E //'^'

#define AML_OP_ZERO     0x00
#define AML_OP_ONE      0x01
#define AML_OP_ONES     0xFF

#define AML_OP_ALIAS    0x06
#define AML_OP_NAME     0x08
#define AML_OP_SCOPE    0x10
#define AML_OP_BUFFER   0x11
#define AML_OP_PACKAGE  0x12
#define AML_OP_VARPACK  0x13
#define AML_OP_METHOD   0x14

#define AML_OP_RETURN   0xA4

#define AML_OP_OPREG    0x80
#define AML_OP_DEVICE   0x82
#define AML_OP_PROC     0x83
#define AML_OP_PWRRES   0x84
#define AML_OP_THERMAL  0x85

#define AML_NULL_NAME   0x00

//
//AML Definition for AML Objects NameString
//
#pragma pack(push, 1)

typedef union _AML_NAME_SEG{
  UINT32 NAME;
  UINT8  Name[4];
}AML_NAME_SEG;

//Type of object
typedef enum {
  otNone=0,
  otScope,
  otBuffer,
  otName,
  otProc,
  otTermal,
  otDevice,
  otMethod,
  otPwrRes,
  otOpReg
} ASL_OBJ_TYPE;

//Structure to store ASL Object Information
typedef struct _ASL_OBJ_INFO {
  VOID          *Object;
  VOID          *ObjName;
  VOID          *DataStart;
  ASL_OBJ_TYPE  ObjType;
  UINTN         Length;
} ASL_OBJ_INFO;

//AML Pckage Definition
typedef struct _AML_PACKAGE_LBYTE {
  UINT8  Length    : 6;
  UINT8  ByteCount : 2;
  //Package Length Following Bytes 0..3
} AML_PACKAGE_LBYTE;

#pragma pack(pop)

EFI_STATUS GetAslObj(UINT8 *Start, UINTN Length, UINT8 *Name, ASL_OBJ_TYPE ObjType, ASL_OBJ_INFO *ObjInfo);
UINTN GetPackageLen(AML_PACKAGE_LBYTE *Pck, UINT8 *BytesCnt);

#endif
