#ifndef __MrcMcRegisterStructIcl9xxx_h__
#define __MrcMcRegisterStructIcl9xxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

@copyright
  Copyright (c) 2010 - 2019 Intel Corporation. All rights reserved
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

@par Specification Reference:
**/

#pragma pack(push, 1)

typedef union {
  struct {
    UINT32 DdrGVCrBlock                            :  1;  // Bits 0:0
    UINT32 Spare                                   :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRBROADCAST_CR_DDRMULTICASTCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 View1_FubAddr                           :  7;  // Bits 6:0
    UINT32 View_AnalogEn                           :  1;  // Bits 7:7
    UINT32 view_Spare                              :  2;  // Bits 9:8
    UINT32 View1_Sel                               :  6;  // Bits 15:10
    UINT32 View0_FubAddr                           :  7;  // Bits 22:16
    UINT32 CompAnaView                             :  1;  // Bits 23:23
    UINT32 AnaViewSel                              :  1;  // Bits 24:24
    UINT32 View0_DllBias                           :  1;  // Bits 25:25
    UINT32 View0_Sel                               :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRBROADCAST_CR_DDRVIEW_STRUCT;

#pragma pack(pop)
#endif
