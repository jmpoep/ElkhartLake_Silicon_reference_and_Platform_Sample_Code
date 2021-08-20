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

  //
  // Module specific Includes
  //
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>

#include <AcpiRes.h>


//**********************************************************************
// Implementation of ASL MACRO for ResourceTamplete
// see ACPI 2.0 spec section 16.2.4
//**********************************************************************

//will determine length in bytes of a package
UINTN GetPackageLen(AML_PACKAGE_LBYTE *Pck, UINT8 *BytesCnt){
  UINTN  len=0;
  UINT8  *p=(UINT8*)Pck;
//------------------
  if(BytesCnt)*BytesCnt=0;
  if(!Pck->ByteCount) len=Pck->Length;
  else {
    len |= (UINTN)(Pck->Length&0x0F);
    if(BytesCnt)*BytesCnt=Pck->ByteCount;
    switch(Pck->ByteCount){
      case 1:{
        UINT8  b=*(p+1);
        len |= (UINTN)(b<<4);
      } break;
      case 2: {
        UINT16 w=(UINT16)(*((UINT16*)(p+1)));
        len |= (UINTN)(w<<4);
      } break;
      case 3: {
        UINT32 d=(UINT32)(*((UINT32*)(p+1)));
        d&=0xffffff;
        len |= (UINTN)(d<<4);
      } break;
    } //switch
  }
  return len;
}

UINT32 ConvertAslName(UINT8 *AslName){
  AML_NAME_SEG  n;
  UINTN      l = AsciiStrLen ((CHAR8 *) AslName);
//-------------------------
  n.NAME=0x5F5F5F5F;
  CopyMem (&n.Name[0],AslName,l);
  return n.NAME;
}


VOID* FindAslObjectName(UINT8 *Start, UINT8 *ObjName, UINTN Len){
  unsigned int  i;
  UINT8      *p;
  AML_NAME_SEG  *obj,nm;
//------------------------------
  nm.NAME=ConvertAslName(ObjName);

  p=Start;
  for(i=0; i<Len; i++){
    obj=(AML_NAME_SEG*)(&p[i]);
    if(obj->NAME!=nm.NAME)continue;
    return &p[i];
  }
   return NULL;
}

BOOLEAN CheckOpCode(UINT8 *NameStart, UINT8 OpCode, UINT8 ExtOpCode, ASL_OBJ_INFO *ObjInfo){
  UINT8  *p, *p1;
  INTN  i;
//---------------------
  //Maximum number of bytes in PackageLength is 4
  if( (*(NameStart-1))==AML_PR_ROOT || (*(NameStart-1))==AML_PR_PARENT) NameStart--;

  //if we Looking For ASL Name Object its a special case.
  if(OpCode==AML_OP_NAME && !ExtOpCode){
    p=NameStart-1;
    if(*p==OpCode){
      ObjInfo->Object=p;
      ObjInfo->ObjName=NameStart;
      ObjInfo->Length=0;
      return TRUE;
    }
    return FALSE;
  }

  //if we Looking For ASL Name Object its a special case.
  if(OpCode==AML_OP_OPREG && ExtOpCode){
    p=NameStart-2;
    if(*p==ExtOpCode && *(p+1)==OpCode){
      ObjInfo->Object=p;
      ObjInfo->ObjName=NameStart;
      ObjInfo->Length=0;
      return TRUE;
    }
    return FALSE;
  }

  for(i=2; i<6; i++){
    p=NameStart-i;
    if(ExtOpCode) p1=p-1;
    else p1=NULL;

    if(p1)if(*p1!=ExtOpCode) continue;
    if(*p!=OpCode) continue;

    if(p1)ObjInfo->Object=p1;
    else ObjInfo->Object=p;

    ObjInfo->Length=GetPackageLen((AML_PACKAGE_LBYTE*)(p+1),NULL);
    ObjInfo->ObjName=NameStart;
    return TRUE;
  }
  return FALSE;
}


//Since the search is done by locating the OBJECT name.
//Caller must know what ASL Object Type he is looking for.
EFI_STATUS GetAslObj(UINT8 *Start, UINTN Length, UINT8 *Name, ASL_OBJ_TYPE ObjType, ASL_OBJ_INFO *ObjInfo)
{
  UINT8      *pn, *s, eop,op;
  UINTN      l, i;
  BOOLEAN      objfound=FALSE;

  s=Start;
  l=Length;

  while (!objfound){

    pn=FindAslObjectName(s,Name,l);

    if(!pn) return EFI_NOT_FOUND;

    //If we found the name let's check if it is the Object we are looking for
    //it could be just object referance, or field definition inside the object,
    //or double name, or multiple name definition we must filter such situations
    // and make sure we have got the actual object but not its reference instance
    switch (ObjType){
      case  otScope    :
        i=0;
        eop=0;
        op=AML_OP_SCOPE;
      break;
      case  otName    :
        i=0;
        eop=0;
        op=AML_OP_NAME;
      break;
      case  otProc    :
        i=6;
        eop=AML_PR_EXTOP;
        op=AML_OP_PROC;
      break;
      case  otTermal  :
        i=0;
        eop=AML_PR_EXTOP;
        op=AML_OP_THERMAL;
      break;
      case  otDevice  :
        i=0;
        eop=AML_PR_EXTOP;
        op=AML_OP_DEVICE;
      break;
      case  otMethod    :
        i=1;
        eop=0;
        op=AML_OP_METHOD;
      break;
      case  otPwrRes  :
        i=3;
        eop=AML_PR_EXTOP;
        op=AML_OP_PWRRES;
      break;
      case  otOpReg  :
        i=0;
        eop=AML_PR_EXTOP;
        op=AML_OP_OPREG;
      break;

      default: return EFI_NOT_FOUND;
     } //switch

    objfound=CheckOpCode(pn, op, eop, ObjInfo);
    if(!objfound){
      l-=(UINTN)(pn-s)-4;
      s=pn+4;
      continue;
    }
    ObjInfo->ObjType=ObjType;
    ObjInfo->DataStart=pn+i+4;

    return EFI_SUCCESS;
  } //while ()

  return EFI_NOT_FOUND;
}

