/** @file
  Header file for debug functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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


#ifndef __RAWDATA_DUMP_H__
#define __RAWDATA_DUMP_H__

#include <Library/PrintLib.h>

#define MSGPRINTF(s)                  Print s
#ifndef _T
#define _T(x)                         L##x
#endif
#define MSGRAWDUMP(s)                 RawdataDump s

#define RAWDATADUMP_COLNUM_PER_ROW    (16)

/**
  Dump content of buffer on screen.

  @param[in] Buffer                 Pointer to the buffer for dump.
  @param[in] Size                 This Size of the buffer.
**/
VOID
RawdataDump (
  IN VOID *Buffer,
  IN UINTN Size
);

/**
  Dump content of buffer from serial output.

  @param[in] Buffer               Pointer to the buffer for dump.
  @param[in] Size                 This Size of the buffer.
**/
VOID
DbgRawdataDump (
  IN VOID *Buffer,
  IN UINTN Size
);

#endif // __RAWDATA_DUMP_H__

