//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  The Legacy Interrupt Handler protocol definition.

Copyright (c) 2011 - 2013, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
**/
#ifndef _LEGACY_INTERRUPT_HANDLER_PROTOCOL_H_
#define _LEGACY_INTERRUPT_HANDLER_PROTOCOL_H_

#define EFI_LEGACY_INTERRUPT_HANDLER_PROTOCOL_GUID \
  { \
    0xd765bf98, 0x2f0b, 0x4e07, { 0xae, 0x77, 0x7e, 0x74, 0x1c, 0xb8, 0x9e, 0xff } \
  };

///
/// LegacyInterruptHandler Protocol structure.
///
#pragma pack(1)
typedef struct {
  UINT16     NextOffset;
  UINT16     NextSegment;
  VOID       *Code;
} INTERRUPT_HANDLER;

typedef struct {
  UINT16     Offset;
  UINT16     Segment;
} LEGACY_VECTOR;
#pragma pack()

typedef struct {
  UINTN              Number;
  INTERRUPT_HANDLER  *Handler;
  UINTN              Length;
} EFI_LEGACY_INTERRUPT_HANDLER_PROTOCOL;

extern EFI_GUID gEfiLegacyInterruptHandlerProtocolGuid;
#endif
