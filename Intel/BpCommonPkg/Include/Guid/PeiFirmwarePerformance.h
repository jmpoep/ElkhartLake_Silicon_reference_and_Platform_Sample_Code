//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
 This file defines PEI Firmware Performance GUID and structures.

 Copyright (c) 2012 - 2016, Intel Corporation. All rights reserved.<BR>
 This software and associated documentation (if any) is furnished
 under a license and may only be used or copied in accordance
 with the terms of the license. Except as permitted by the
 license, no part of this software or documentation may be
 reproduced, stored in a retrieval system, or transmitted in any
 form or by any means without the express written consent of
 Intel Corporation.

@par Specification Reference:

**/

#ifndef __PEI_FIRMWARE_PERFORMANCE_DATA_H__
#define __PEI_FIRMWARE_PERFORMANCE_DATA_H__

#pragma pack(1)
typedef struct {
  UINT16    ProgressID;
  EFI_GUID  Guid;
  UINT32    ApicID;
  UINT64    Timestamp;
} PEI_GUID_EVENT_RECORD;
#pragma pack()

typedef struct {
  UINT32                 NumberOfEntries;
  UINT32                 Reserved;
  PEI_GUID_EVENT_RECORD  GuidEventRecord[1];
} PEI_FIRMWARE_PERFORMANCE_HOB;

extern EFI_GUID gPeiFirmwarePerformanceGuid;

#endif

