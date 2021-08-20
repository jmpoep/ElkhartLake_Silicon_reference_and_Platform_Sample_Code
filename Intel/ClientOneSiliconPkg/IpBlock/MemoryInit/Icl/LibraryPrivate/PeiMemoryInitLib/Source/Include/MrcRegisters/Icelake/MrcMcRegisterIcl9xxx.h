#ifndef __MrcMcRegisterIcl9xxx_h__
#define __MrcMcRegisterIcl9xxx_h__
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


#define DDRBROADCAST_CR_DDRMULTICASTCONTROL_REG                        (0x00009F78)

  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_DdrGVCrBlock_OFF         ( 0)
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_DdrGVCrBlock_WID         ( 1)
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_DdrGVCrBlock_MSK         (0x00000001)
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_DdrGVCrBlock_MIN         (0)
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_DdrGVCrBlock_MAX         (1) // 0x00000001
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_DdrGVCrBlock_DEF         (0x00000000)
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_DdrGVCrBlock_HSH         (0x01009F78)

  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_Spare_OFF                ( 1)
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_Spare_WID                (31)
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_Spare_MSK                (0xFFFFFFFE)
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_Spare_MIN                (0)
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_Spare_MAX                (2147483647) // 0x7FFFFFFF
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_Spare_DEF                (0x00000000)
  #define DDRBROADCAST_CR_DDRMULTICASTCONTROL_Spare_HSH                (0x1F019F78)

#define DDRBROADCAST_CR_DDRVIEW_REG                                    (0x00009F7C)

  #define DDRBROADCAST_CR_DDRVIEW_View1_FubAddr_OFF                    ( 0)
  #define DDRBROADCAST_CR_DDRVIEW_View1_FubAddr_WID                    ( 7)
  #define DDRBROADCAST_CR_DDRVIEW_View1_FubAddr_MSK                    (0x0000007F)
  #define DDRBROADCAST_CR_DDRVIEW_View1_FubAddr_MIN                    (0)
  #define DDRBROADCAST_CR_DDRVIEW_View1_FubAddr_MAX                    (127) // 0x0000007F
  #define DDRBROADCAST_CR_DDRVIEW_View1_FubAddr_DEF                    (0x00000000)
  #define DDRBROADCAST_CR_DDRVIEW_View1_FubAddr_HSH                    (0x07009F7C)

  #define DDRBROADCAST_CR_DDRVIEW_View_AnalogEn_OFF                    ( 7)
  #define DDRBROADCAST_CR_DDRVIEW_View_AnalogEn_WID                    ( 1)
  #define DDRBROADCAST_CR_DDRVIEW_View_AnalogEn_MSK                    (0x00000080)
  #define DDRBROADCAST_CR_DDRVIEW_View_AnalogEn_MIN                    (0)
  #define DDRBROADCAST_CR_DDRVIEW_View_AnalogEn_MAX                    (1) // 0x00000001
  #define DDRBROADCAST_CR_DDRVIEW_View_AnalogEn_DEF                    (0x00000000)
  #define DDRBROADCAST_CR_DDRVIEW_View_AnalogEn_HSH                    (0x01079F7C)

  #define DDRBROADCAST_CR_DDRVIEW_view_Spare_OFF                       ( 8)
  #define DDRBROADCAST_CR_DDRVIEW_view_Spare_WID                       ( 2)
  #define DDRBROADCAST_CR_DDRVIEW_view_Spare_MSK                       (0x00000300)
  #define DDRBROADCAST_CR_DDRVIEW_view_Spare_MIN                       (0)
  #define DDRBROADCAST_CR_DDRVIEW_view_Spare_MAX                       (3) // 0x00000003
  #define DDRBROADCAST_CR_DDRVIEW_view_Spare_DEF                       (0x00000000)
  #define DDRBROADCAST_CR_DDRVIEW_view_Spare_HSH                       (0x02089F7C)

  #define DDRBROADCAST_CR_DDRVIEW_View1_Sel_OFF                        (10)
  #define DDRBROADCAST_CR_DDRVIEW_View1_Sel_WID                        ( 6)
  #define DDRBROADCAST_CR_DDRVIEW_View1_Sel_MSK                        (0x0000FC00)
  #define DDRBROADCAST_CR_DDRVIEW_View1_Sel_MIN                        (0)
  #define DDRBROADCAST_CR_DDRVIEW_View1_Sel_MAX                        (63) // 0x0000003F
  #define DDRBROADCAST_CR_DDRVIEW_View1_Sel_DEF                        (0x00000000)
  #define DDRBROADCAST_CR_DDRVIEW_View1_Sel_HSH                        (0x060A9F7C)

  #define DDRBROADCAST_CR_DDRVIEW_View0_FubAddr_OFF                    (16)
  #define DDRBROADCAST_CR_DDRVIEW_View0_FubAddr_WID                    ( 7)
  #define DDRBROADCAST_CR_DDRVIEW_View0_FubAddr_MSK                    (0x007F0000)
  #define DDRBROADCAST_CR_DDRVIEW_View0_FubAddr_MIN                    (0)
  #define DDRBROADCAST_CR_DDRVIEW_View0_FubAddr_MAX                    (127) // 0x0000007F
  #define DDRBROADCAST_CR_DDRVIEW_View0_FubAddr_DEF                    (0x00000000)
  #define DDRBROADCAST_CR_DDRVIEW_View0_FubAddr_HSH                    (0x07109F7C)

  #define DDRBROADCAST_CR_DDRVIEW_CompAnaView_OFF                      (23)
  #define DDRBROADCAST_CR_DDRVIEW_CompAnaView_WID                      ( 1)
  #define DDRBROADCAST_CR_DDRVIEW_CompAnaView_MSK                      (0x00800000)
  #define DDRBROADCAST_CR_DDRVIEW_CompAnaView_MIN                      (0)
  #define DDRBROADCAST_CR_DDRVIEW_CompAnaView_MAX                      (1) // 0x00000001
  #define DDRBROADCAST_CR_DDRVIEW_CompAnaView_DEF                      (0x00000000)
  #define DDRBROADCAST_CR_DDRVIEW_CompAnaView_HSH                      (0x01179F7C)

  #define DDRBROADCAST_CR_DDRVIEW_AnaViewSel_OFF                       (24)
  #define DDRBROADCAST_CR_DDRVIEW_AnaViewSel_WID                       ( 1)
  #define DDRBROADCAST_CR_DDRVIEW_AnaViewSel_MSK                       (0x01000000)
  #define DDRBROADCAST_CR_DDRVIEW_AnaViewSel_MIN                       (0)
  #define DDRBROADCAST_CR_DDRVIEW_AnaViewSel_MAX                       (1) // 0x00000001
  #define DDRBROADCAST_CR_DDRVIEW_AnaViewSel_DEF                       (0x00000000)
  #define DDRBROADCAST_CR_DDRVIEW_AnaViewSel_HSH                       (0x01189F7C)

  #define DDRBROADCAST_CR_DDRVIEW_View0_DllBias_OFF                    (25)
  #define DDRBROADCAST_CR_DDRVIEW_View0_DllBias_WID                    ( 1)
  #define DDRBROADCAST_CR_DDRVIEW_View0_DllBias_MSK                    (0x02000000)
  #define DDRBROADCAST_CR_DDRVIEW_View0_DllBias_MIN                    (0)
  #define DDRBROADCAST_CR_DDRVIEW_View0_DllBias_MAX                    (1) // 0x00000001
  #define DDRBROADCAST_CR_DDRVIEW_View0_DllBias_DEF                    (0x00000000)
  #define DDRBROADCAST_CR_DDRVIEW_View0_DllBias_HSH                    (0x01199F7C)

  #define DDRBROADCAST_CR_DDRVIEW_View0_Sel_OFF                        (26)
  #define DDRBROADCAST_CR_DDRVIEW_View0_Sel_WID                        ( 6)
  #define DDRBROADCAST_CR_DDRVIEW_View0_Sel_MSK                        (0xFC000000)
  #define DDRBROADCAST_CR_DDRVIEW_View0_Sel_MIN                        (0)
  #define DDRBROADCAST_CR_DDRVIEW_View0_Sel_MAX                        (63) // 0x0000003F
  #define DDRBROADCAST_CR_DDRVIEW_View0_Sel_DEF                        (0x00000000)
  #define DDRBROADCAST_CR_DDRVIEW_View0_Sel_HSH                        (0x061A9F7C)
#pragma pack(pop)
#endif
