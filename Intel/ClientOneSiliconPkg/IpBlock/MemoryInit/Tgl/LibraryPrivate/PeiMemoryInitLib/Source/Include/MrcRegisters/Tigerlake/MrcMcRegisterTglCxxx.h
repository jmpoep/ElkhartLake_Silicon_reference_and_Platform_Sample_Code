#ifndef __MrcMcRegisterTglCxxx_h__
#define __MrcMcRegisterTglCxxx_h__
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


#define MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_REG                         (0x0000C000)

  #define MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_Control_Policy_OFF        ( 0)
  #define MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_Control_Policy_WID        (64)
  #define MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_Control_Policy_MSK        (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_Control_Policy_MIN        (0)
  #define MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_Control_Policy_MAX        (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_Control_Policy_DEF        (0x40001000208)
  #define MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_Control_Policy_HSH        (0x4000C000)

#define MC0_CR_CPGC2_ACCESS_READ_POLICY_REG                            (0x0000C008)

  #define MC0_CR_CPGC2_ACCESS_READ_POLICY_Read_Policy_OFF              ( 0)
  #define MC0_CR_CPGC2_ACCESS_READ_POLICY_Read_Policy_WID              (64)
  #define MC0_CR_CPGC2_ACCESS_READ_POLICY_Read_Policy_MSK              (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CR_CPGC2_ACCESS_READ_POLICY_Read_Policy_MIN              (0)
  #define MC0_CR_CPGC2_ACCESS_READ_POLICY_Read_Policy_MAX              (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CR_CPGC2_ACCESS_READ_POLICY_Read_Policy_DEF              (0xFFFFFFFFFFFFFFFF)
  #define MC0_CR_CPGC2_ACCESS_READ_POLICY_Read_Policy_HSH              (0x4000C008)

#define MC0_CR_CPGC2_ACCESS_WRITE_POLICY_REG                           (0x0000C010)

  #define MC0_CR_CPGC2_ACCESS_WRITE_POLICY_Write_Policy_OFF            ( 0)
  #define MC0_CR_CPGC2_ACCESS_WRITE_POLICY_Write_Policy_WID            (64)
  #define MC0_CR_CPGC2_ACCESS_WRITE_POLICY_Write_Policy_MSK            (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CR_CPGC2_ACCESS_WRITE_POLICY_Write_Policy_MIN            (0)
  #define MC0_CR_CPGC2_ACCESS_WRITE_POLICY_Write_Policy_MAX            (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CR_CPGC2_ACCESS_WRITE_POLICY_Write_Policy_DEF            (0x4000100021A)
  #define MC0_CR_CPGC2_ACCESS_WRITE_POLICY_Write_Policy_HSH            (0x4000C010)

#define MC0_CR_CPGC2_VISA_MUX_SEL_REG                                  (0x0000C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_or_Dpat0_or_Err0_OFF          ( 0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_or_Dpat0_or_Err0_WID          ( 2)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_or_Dpat0_or_Err0_MSK          (0x00000003)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_or_Dpat0_or_Err0_MIN          (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_or_Dpat0_or_Err0_MAX          (3) // 0x00000003
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_or_Dpat0_or_Err0_DEF          (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_or_Dpat0_or_Err0_HSH          (0x4200C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_or_Dpat1_or_Cmd0_OFF          ( 2)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_or_Dpat1_or_Cmd0_WID          ( 2)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_or_Dpat1_or_Cmd0_MSK          (0x0000000C)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_or_Dpat1_or_Cmd0_MIN          (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_or_Dpat1_or_Cmd0_MAX          (3) // 0x00000003
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_or_Dpat1_or_Cmd0_DEF          (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_or_Dpat1_or_Cmd0_HSH          (0x4204C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_or_Exe1_or_Cmd1_or_Err1_OFF   ( 4)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_or_Exe1_or_Cmd1_or_Err1_WID   ( 2)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_or_Exe1_or_Cmd1_or_Err1_MSK   (0x00000030)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_or_Exe1_or_Cmd1_or_Err1_MIN   (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_or_Exe1_or_Cmd1_or_Err1_MAX   (3) // 0x00000003
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_or_Exe1_or_Cmd1_or_Err1_DEF   (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_or_Exe1_or_Cmd1_or_Err1_HSH   (0x4208C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd0_grp_Sel_OFF                   ( 6)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd0_grp_Sel_WID                   ( 2)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd0_grp_Sel_MSK                   (0x000000C0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd0_grp_Sel_MIN                   (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd0_grp_Sel_MAX                   (3) // 0x00000003
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd0_grp_Sel_DEF                   (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd0_grp_Sel_HSH                   (0x420CC018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd1_grp_Sel_OFF                   ( 8)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd1_grp_Sel_WID                   ( 2)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd1_grp_Sel_MSK                   (0x00000300)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd1_grp_Sel_MIN                   (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd1_grp_Sel_MAX                   (3) // 0x00000003
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd1_grp_Sel_DEF                   (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Cmd1_grp_Sel_HSH                   (0x4210C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_grp_Sel_OFF                  (10)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_grp_Sel_WID                  ( 1)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_grp_Sel_MSK                  (0x00000400)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_grp_Sel_MIN                  (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_grp_Sel_MAX                  (1) // 0x00000001
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_grp_Sel_DEF                  (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_grp_Sel_HSH                  (0x4114C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_grp_Sel_OFF                  (11)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_grp_Sel_WID                  ( 1)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_grp_Sel_MSK                  (0x00000800)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_grp_Sel_MIN                  (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_grp_Sel_MAX                  (1) // 0x00000001
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_grp_Sel_DEF                  (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_grp_Sel_HSH                  (0x4116C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_grp_Sel_OFF                   (12)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_grp_Sel_WID                   ( 2)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_grp_Sel_MSK                   (0x00003000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_grp_Sel_MIN                   (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_grp_Sel_MAX                   (3) // 0x00000003
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_grp_Sel_DEF                   (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_grp_Sel_HSH                   (0x4218C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_grp_Sel_OFF                   (14)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_grp_Sel_WID                   ( 2)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_grp_Sel_MSK                   (0x0000C000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_grp_Sel_MIN                   (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_grp_Sel_MAX                   (3) // 0x00000003
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_grp_Sel_DEF                   (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_grp_Sel_HSH                   (0x421CC018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_grp_Sel_OFF                   (16)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_grp_Sel_WID                   ( 2)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_grp_Sel_MSK                   (0x00030000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_grp_Sel_MIN                   (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_grp_Sel_MAX                   (3) // 0x00000003
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_grp_Sel_DEF                   (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe0_grp_Sel_HSH                   (0x4220C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe1_grp_Sel_OFF                   (18)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe1_grp_Sel_WID                   ( 2)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe1_grp_Sel_MSK                   (0x000C0000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe1_grp_Sel_MIN                   (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe1_grp_Sel_MAX                   (3) // 0x00000003
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe1_grp_Sel_DEF                   (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Exe1_grp_Sel_HSH                   (0x4224C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_grp_Sel_OFF                   (20)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_grp_Sel_WID                   ( 1)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_grp_Sel_MSK                   (0x00100000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_grp_Sel_MIN                   (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_grp_Sel_MAX                   (1) // 0x00000001
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_grp_Sel_DEF                   (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx0_grp_Sel_HSH                   (0x4128C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_grp_Sel_OFF                   (21)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_grp_Sel_WID                   ( 1)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_grp_Sel_MSK                   (0x00200000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_grp_Sel_MIN                   (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_grp_Sel_MAX                   (1) // 0x00000001
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_grp_Sel_DEF                   (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Lbx1_grp_Sel_HSH                   (0x412AC018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_pgc_Sel_OFF                  (22)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_pgc_Sel_WID                  ( 3)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_pgc_Sel_MSK                  (0x01C00000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_pgc_Sel_MIN                  (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_pgc_Sel_MAX                  (7) // 0x00000007
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_pgc_Sel_DEF                  (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat0_pgc_Sel_HSH                  (0x432CC018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_pgc_Sel_OFF                  (25)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_pgc_Sel_WID                  ( 3)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_pgc_Sel_MSK                  (0x0E000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_pgc_Sel_MIN                  (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_pgc_Sel_MAX                  (7) // 0x00000007
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_pgc_Sel_DEF                  (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Dpat1_pgc_Sel_HSH                  (0x4332C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_rr_Sel_OFF                    (28)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_rr_Sel_WID                    ( 3)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_rr_Sel_MSK                    (0x70000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_rr_Sel_MIN                    (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_rr_Sel_MAX                    (7) // 0x00000007
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_rr_Sel_DEF                    (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err0_rr_Sel_HSH                    (0x4338C018)

  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_rr_Sel_OFF                    (31)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_rr_Sel_WID                    ( 3)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_rr_Sel_MSK                    (0x0000000380000000ULL)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_rr_Sel_MIN                    (0)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_rr_Sel_MAX                    (7) // 0x00000007
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_rr_Sel_DEF                    (0x00000000)
  #define MC0_CR_CPGC2_VISA_MUX_SEL_Err1_rr_Sel_HSH                    (0x433EC018)

#define MC0_CR_CPGC2_STG_CHICKEN_REG                                   (0x0000C020)

  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_WTRMRK_OFF                      ( 0)
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_WTRMRK_WID                      (16)
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_WTRMRK_MSK                      (0x0000FFFF)
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_WTRMRK_MIN                      (0)
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_WTRMRK_MAX                      (65535) // 0x0000FFFF
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_WTRMRK_DEF                      (0x00000000)
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_WTRMRK_HSH                      (0x5000C020)

  #define MC0_CR_CPGC2_STG_CHICKEN_STG_WTRMRK_OFF                      (16)
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_WTRMRK_WID                      (16)
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_WTRMRK_MSK                      (0xFFFF0000)
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_WTRMRK_MIN                      (0)
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_WTRMRK_MAX                      (65535) // 0x0000FFFF
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_WTRMRK_DEF                      (0x00000000)
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_WTRMRK_HSH                      (0x5020C020)

  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_PRELOAD_OFF                     (32)
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_PRELOAD_WID                     (16)
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_PRELOAD_MSK                     (0x0000FFFF00000000ULL)
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_PRELOAD_MIN                     (0)
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_PRELOAD_MAX                     (65535) // 0x0000FFFF
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_PRELOAD_DEF                     (0x00000000)
  #define MC0_CR_CPGC2_STG_CHICKEN_RTN_PRELOAD_HSH                     (0x5040C020)

  #define MC0_CR_CPGC2_STG_CHICKEN_STG_PRELOAD_OFF                     (48)
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_PRELOAD_WID                     (16)
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_PRELOAD_MSK                     (0xFFFF000000000000ULL)
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_PRELOAD_MIN                     (0)
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_PRELOAD_MAX                     (65535) // 0x0000FFFF
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_PRELOAD_DEF                     (0x00000000)
  #define MC0_CR_CPGC2_STG_CHICKEN_STG_PRELOAD_HSH                     (0x5060C020)

#define MC0_CR_CPGC2_CREDIT_CFG_REG                                    (0x0000C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_OFF              ( 0)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_WID              ( 8)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_MSK              (0x000000FF)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_MIN              (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_MAX              (255) // 0x000000FF
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_DEF              (0x00000008)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_HSH              (0x0800C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_OFF                 ( 8)
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_WID                 ( 8)
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_MSK                 (0x0000FF00)
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_MIN                 (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_MAX                 (255) // 0x000000FF
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_DEF                 (0x00000004)
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_HSH                 (0x0810C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_OFF              (24)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_WID              ( 1)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_MSK              (0x01000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_MIN              (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_MAX              (1) // 0x00000001
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_DEF              (0x00000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_HSH              (0x0130C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_OFF                 (26)
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_WID                 ( 1)
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_MSK                 (0x04000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_MIN                 (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_MAX                 (1) // 0x00000001
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_DEF                 (0x00000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_HSH                 (0x0134C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_ISM_IDLE_OFF                         (30)
  #define MC0_CR_CPGC2_CREDIT_CFG_ISM_IDLE_WID                         ( 1)
  #define MC0_CR_CPGC2_CREDIT_CFG_ISM_IDLE_MSK                         (0x40000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_ISM_IDLE_MIN                         (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_ISM_IDLE_MAX                         (1) // 0x00000001
  #define MC0_CR_CPGC2_CREDIT_CFG_ISM_IDLE_DEF                         (0x00000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_ISM_IDLE_HSH                         (0x013CC028)

  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_OFF              (31)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_WID              ( 1)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_MSK              (0x80000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_MIN              (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_MAX              (1) // 0x00000001
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_DEF              (0x00000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_HSH              (0x013EC028)

#define MC0_CR_CPGC2_CREDIT_CFG_A0_REG                                 (0x0000C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_A0_OFF           ( 0)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_A0_WID           ( 8)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_A0_MSK           (0x000000FF)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_A0_MIN           (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_A0_MAX           (255) // 0x000000FF
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_A0_DEF           (0x00000008)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_CPL_CREDITS_INIT_A0_HSH           (0x0800C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_A0_OFF              ( 8)
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_A0_WID              ( 8)
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_A0_MSK              (0x0000FF00)
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_A0_MIN              (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_A0_MAX              (255) // 0x000000FF
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_A0_DEF              (0x00000004)
  #define MC0_CR_CPGC2_CREDIT_CFG_RSP_CREDITS_INIT_A0_HSH              (0x0810C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_INIT_A0_OFF            (16)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_INIT_A0_WID            ( 8)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_INIT_A0_MSK            (0x00FF0000)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_INIT_A0_MIN            (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_INIT_A0_MAX            (255) // 0x000000FF
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_INIT_A0_DEF            (0x00000010)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_INIT_A0_HSH            (0x0820C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_A0_OFF           (24)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_A0_WID           ( 1)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_A0_MSK           (0x01000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_A0_MIN           (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_A0_MAX           (1) // 0x00000001
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_A0_DEF           (0x00000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_CONFIG_DONE_A0_HSH           (0x0130C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_OVERRIDE_A0_OFF        (25)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_OVERRIDE_A0_WID        ( 1)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_OVERRIDE_A0_MSK        (0x02000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_OVERRIDE_A0_MIN        (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_OVERRIDE_A0_MAX        (1) // 0x00000001
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_OVERRIDE_A0_DEF        (0x00000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_RD_WR_CREDITS_OVERRIDE_A0_HSH        (0x0132C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_A0_OFF              (26)
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_A0_WID              ( 1)
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_A0_MSK              (0x04000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_A0_MIN              (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_A0_MAX              (1) // 0x00000001
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_A0_DEF              (0x00000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_FORCE_ISM_ACTIVE_A0_HSH              (0x0134C028)

  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_A0_OFF           (31)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_A0_WID           ( 1)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_A0_MSK           (0x80000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_A0_MIN           (0)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_A0_MAX           (1) // 0x00000001
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_A0_DEF           (0x00000000)
  #define MC0_CR_CPGC2_CREDIT_CFG_CREDITS_INITIALIZED_A0_HSH           (0x013EC028)

#define MC0_CR_CPGC2_V_CHICKEN_REG                                     (0x0000C02C)

  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_OFF                     ( 0)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_WID                     ( 6)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_MSK                     (0x0000003F)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_MIN                     (0)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_MAX                     (63) // 0x0000003F
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_DEF                     (0x00000008)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_HSH                     (0x0600C02C)

  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_OFF                   ( 7)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_WID                   ( 1)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_MSK                   (0x00000080)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_MIN                   (0)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_MAX                   (1) // 0x00000001
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_DEF                   (0x00000000)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_HSH                   (0x010EC02C)

  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_OFF                     ( 8)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_WID                     ( 6)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_MSK                     (0x00003F00)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_MIN                     (0)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_MAX                     (63) // 0x0000003F
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_DEF                     (0x00000008)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_HSH                     (0x0610C02C)

  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_OFF                   (15)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_WID                   ( 1)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_MSK                   (0x00008000)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_MIN                   (0)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_MAX                   (1) // 0x00000001
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_DEF                   (0x00000000)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_HSH                   (0x011EC02C)

  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_OFF                (16)
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_WID                ( 1)
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_MSK                (0x00010000)
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_MIN                (0)
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_MAX                (1) // 0x00000001
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_DEF                (0x00000000)
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_HSH                (0x0120C02C)

  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_OFF                 (24)
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_WID                 ( 1)
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_MSK                 (0x01000000)
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_MIN                 (0)
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_MAX                 (1) // 0x00000001
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_DEF                 (0x00000000)
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_HSH                 (0x0130C02C)

  #define MC0_CR_CPGC2_V_CHICKEN_INTERNAL_ERR_OFF                      (31)
  #define MC0_CR_CPGC2_V_CHICKEN_INTERNAL_ERR_WID                      ( 1)
  #define MC0_CR_CPGC2_V_CHICKEN_INTERNAL_ERR_MSK                      (0x80000000)
  #define MC0_CR_CPGC2_V_CHICKEN_INTERNAL_ERR_MIN                      (0)
  #define MC0_CR_CPGC2_V_CHICKEN_INTERNAL_ERR_MAX                      (1) // 0x00000001
  #define MC0_CR_CPGC2_V_CHICKEN_INTERNAL_ERR_DEF                      (0x00000000)
  #define MC0_CR_CPGC2_V_CHICKEN_INTERNAL_ERR_HSH                      (0x013EC02C)

#define MC0_CR_CPGC2_V_CHICKEN_A0_REG                                  (0x0000C02C)

  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_A0_OFF                  ( 0)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_A0_WID                  ( 6)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_A0_MSK                  (0x0000003F)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_A0_MIN                  (0)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_A0_MAX                  (63) // 0x0000003F
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_A0_DEF                  (0x00000008)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_CREDIT_A0_HSH                  (0x0600C02C)

  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_A0_OFF                ( 7)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_A0_WID                ( 1)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_A0_MSK                (0x00000080)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_A0_MIN                (0)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_A0_MAX                (1) // 0x00000001
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_A0_DEF                (0x00000000)
  #define MC0_CR_CPGC2_V_CHICKEN_XPQ_CH_OVERRIDE_A0_HSH                (0x010EC02C)

  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_A0_OFF                  ( 8)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_A0_WID                  ( 6)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_A0_MSK                  (0x00003F00)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_A0_MIN                  (0)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_A0_MAX                  (63) // 0x0000003F
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_A0_DEF                  (0x00000008)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_CREDIT_A0_HSH                  (0x0610C02C)

  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_A0_OFF                (15)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_A0_WID                ( 1)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_A0_MSK                (0x00008000)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_A0_MIN                (0)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_A0_MAX                (1) // 0x00000001
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_A0_DEF                (0x00000000)
  #define MC0_CR_CPGC2_V_CHICKEN_STG_CH_OVERRIDE_A0_HSH                (0x011EC02C)

  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_A0_OFF             (16)
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_A0_WID             ( 1)
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_A0_MSK             (0x00010000)
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_A0_MIN             (0)
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_A0_MAX             (1) // 0x00000001
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_A0_DEF             (0x00000000)
  #define MC0_CR_CPGC2_V_CHICKEN_RTN_BYPASS_DISABLE_A0_HSH             (0x0120C02C)

  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_A0_OFF              (24)
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_A0_WID              ( 1)
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_A0_MSK              (0x01000000)
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_A0_MIN              (0)
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_A0_MAX              (1) // 0x00000001
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_A0_DEF              (0x00000000)
  #define MC0_CR_CPGC2_V_CHICKEN_MPR_TEST_REQ_DBLR_A0_HSH              (0x0130C02C)

#define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_REG                          (0x0000C030)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Address_Decode_Rotate_Repeats_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Address_Decode_Rotate_Repeats_WID ( 6)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Address_Decode_Rotate_Repeats_MSK (0x0000003F)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Address_Decode_Rotate_Repeats_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Address_Decode_Rotate_Repeats_MAX (63) // 0x0000003F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Address_Decode_Rotate_Repeats_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Address_Decode_Rotate_Repeats_HSH (0x0600C030)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Order_OFF    (16)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Order_WID    ( 3)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Order_MSK    (0x00070000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Order_MIN    (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Order_MAX    (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Order_DEF    (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Order_HSH    (0x0320C030)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Direction_OFF (19)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Direction_WID ( 3)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Direction_MSK (0x00380000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Direction_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Direction_MAX (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Direction_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_FastY_Address_Direction_HSH (0x0326C030)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Column_Addr_Invert_Select_OFF (24)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Column_Addr_Invert_Select_WID ( 2)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Column_Addr_Invert_Select_MSK (0x03000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Column_Addr_Invert_Select_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Column_Addr_Invert_Select_MAX (3) // 0x00000003
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Column_Addr_Invert_Select_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Column_Addr_Invert_Select_HSH (0x0230C030)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Row_Addr_Invert_Select_OFF (26)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Row_Addr_Invert_Select_WID ( 2)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Row_Addr_Invert_Select_MSK (0x0C000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Row_Addr_Invert_Select_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Row_Addr_Invert_Select_MAX (3) // 0x00000003
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Row_Addr_Invert_Select_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Row_Addr_Invert_Select_HSH (0x0234C030)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Bank_Addr_Invert_Select_OFF (28)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Bank_Addr_Invert_Select_WID ( 2)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Bank_Addr_Invert_Select_MSK (0x30000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Bank_Addr_Invert_Select_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Bank_Addr_Invert_Select_MAX (3) // 0x00000003
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Bank_Addr_Invert_Select_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_Bank_Addr_Invert_Select_HSH (0x0238C030)

#define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG                    (0x0000C034)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Order_OFF    ( 0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Order_WID    ( 3)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Order_MSK    (0x00000007)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Order_MIN    (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Order_MAX    (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Order_DEF    (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Order_HSH    (0x0300C034)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Direction_OFF ( 3)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Direction_WID ( 3)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Direction_MSK (0x00000038)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Direction_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Direction_MAX (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Direction_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Direction_HSH (0x0306C034)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Decode_Enable_OFF ( 6)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Decode_Enable_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Decode_Enable_MSK (0x00000040)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Decode_Enable_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Decode_Enable_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Decode_Enable_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Address_Decode_Enable_HSH (0x010CC034)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Last_OFF             ( 7)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Last_WID             ( 1)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Last_MSK             (0x00000080)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Last_MIN             (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Last_MAX             (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Last_DEF             (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_Last_HSH             (0x010EC034)

#define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_1_REG                    (0x0000C035)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_2_REG                    (0x0000C036)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_3_REG                    (0x0000C037)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_DATA_CONTROL_REG                             (0x0000C038)

  #define MC0_REQ0_CR_CPGC2_DATA_CONTROL_Data_Select_Rotation_Repeats_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_DATA_CONTROL_Data_Select_Rotation_Repeats_WID ( 8)
  #define MC0_REQ0_CR_CPGC2_DATA_CONTROL_Data_Select_Rotation_Repeats_MSK (0x000000FF)
  #define MC0_REQ0_CR_CPGC2_DATA_CONTROL_Data_Select_Rotation_Repeats_MIN (0)
  #define MC0_REQ0_CR_CPGC2_DATA_CONTROL_Data_Select_Rotation_Repeats_MAX (255) // 0x000000FF
  #define MC0_REQ0_CR_CPGC2_DATA_CONTROL_Data_Select_Rotation_Repeats_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_DATA_CONTROL_Data_Select_Rotation_Repeats_HSH (0x0800C038)

#define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG                       (0x0000C03C)

  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Data_Background_OFF     ( 0)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Data_Background_WID     ( 4)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Data_Background_MSK     (0x0000000F)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Data_Background_MIN     (0)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Data_Background_MAX     (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Data_Background_DEF     (0x00000000)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Data_Background_HSH     (0x0400C03C)

  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Background_Mode_OFF     ( 4)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Background_Mode_WID     ( 1)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Background_Mode_MSK     (0x00000010)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Background_Mode_MIN     (0)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Background_Mode_MAX     (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Background_Mode_DEF     (0x00000000)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Background_Mode_HSH     (0x0108C03C)

  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Alt_Data_Rotate_En_OFF  ( 5)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Alt_Data_Rotate_En_WID  ( 1)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Alt_Data_Rotate_En_MSK  (0x00000020)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Alt_Data_Rotate_En_MIN  (0)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Alt_Data_Rotate_En_MAX  (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Alt_Data_Rotate_En_DEF  (0x00000000)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Alt_Data_Rotate_En_HSH  (0x010AC03C)

  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Invert_Data_OFF         ( 6)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Invert_Data_WID         ( 1)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Invert_Data_MSK         (0x00000040)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Invert_Data_MIN         (0)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Invert_Data_MAX         (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Invert_Data_DEF         (0x00000000)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Invert_Data_HSH         (0x010CC03C)

  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Last_OFF                ( 7)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Last_WID                ( 1)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Last_MSK                (0x00000080)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Last_MIN                (0)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Last_MAX                (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Last_DEF                (0x00000000)
  #define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_Last_HSH                (0x010EC03C)

#define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_1_REG                       (0x0000C03D)
//Duplicate of MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_2_REG                       (0x0000C03E)
//Duplicate of MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_3_REG                       (0x0000C03F)
//Duplicate of MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_REG                      (0x0000C040)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Address_Decode_Rotate_Repeats_Current_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Address_Decode_Rotate_Repeats_Current_WID ( 6)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Address_Decode_Rotate_Repeats_Current_MSK (0x0000003F)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Address_Decode_Rotate_Repeats_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Address_Decode_Rotate_Repeats_Current_MAX (63) // 0x0000003F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Address_Decode_Rotate_Repeats_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Address_Decode_Rotate_Repeats_Current_HSH (0x0600C040)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Data_Select_Rotation_Repeats_Current_OFF (16)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Data_Select_Rotation_Repeats_Current_WID ( 8)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Data_Select_Rotation_Repeats_Current_MSK (0x00FF0000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Data_Select_Rotation_Repeats_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Data_Select_Rotation_Repeats_Current_MAX (255) // 0x000000FF
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Data_Select_Rotation_Repeats_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_Data_Select_Rotation_Repeats_Current_HSH (0x0820C040)

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG                  (0x0000C044)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Command_Start_Pointer_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Command_Start_Pointer_WID ( 5)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Command_Start_Pointer_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Command_Start_Pointer_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Command_Start_Pointer_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Command_Start_Pointer_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Command_Start_Pointer_HSH (0x0500C044)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Inverse_Direction_OFF ( 5)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Inverse_Direction_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Inverse_Direction_MSK (0x00000020)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Inverse_Direction_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Inverse_Direction_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Inverse_Direction_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Inverse_Direction_HSH (0x010AC044)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Invert_Data_OFF    ( 6)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Invert_Data_WID    ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Invert_Data_MSK    (0x00000040)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Invert_Data_MIN    (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Invert_Data_MAX    (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Invert_Data_DEF    (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Invert_Data_HSH    (0x010CC044)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Last_OFF           ( 7)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Last_WID           ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Last_MSK           (0x00000080)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Last_MIN           (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Last_MAX           (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Last_DEF           (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_Last_HSH           (0x010EC044)

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_1_REG                  (0x0000C045)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_2_REG                  (0x0000C046)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_3_REG                  (0x0000C047)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_4_REG                  (0x0000C048)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_5_REG                  (0x0000C049)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_6_REG                  (0x0000C04A)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_7_REG                  (0x0000C04B)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG             (0x0000C04C)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_FastY_Init_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_FastY_Init_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_FastY_Init_MSK (0x00000001)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_FastY_Init_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_FastY_Init_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_FastY_Init_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_FastY_Init_HSH (0x0100C04C)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Base_Range_Row_OFF ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Base_Range_Row_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Base_Range_Row_MSK (0x00000002)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Base_Range_Row_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Base_Range_Row_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Base_Range_Row_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Base_Range_Row_HSH (0x0102C04C)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Clear_OFF ( 2)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Clear_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Clear_MSK (0x00000004)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Clear_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Clear_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Clear_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Clear_HSH (0x0104C04C)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Start_OFF ( 3)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Start_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Start_MSK (0x00000008)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Start_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Start_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Start_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Count_Start_HSH (0x0106C04C)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Event_Start_OFF ( 4)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Event_Start_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Event_Start_MSK (0x00000010)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Event_Start_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Event_Start_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Event_Start_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Wait_Event_Start_HSH (0x0108C04C)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Deselect_On_OFF ( 5)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Deselect_On_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Deselect_On_MSK (0x00000020)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Deselect_On_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Deselect_On_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Deselect_On_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Deselect_On_HSH (0x010AC04C)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Select_On_OFF ( 6)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Select_On_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Select_On_MSK (0x00000040)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Select_On_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Select_On_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Select_On_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_Select_On_HSH (0x010CC04C)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_BE_Train_Err_En_OFF ( 7)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_BE_Train_Err_En_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_BE_Train_Err_En_MSK (0x00000080)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_BE_Train_Err_En_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_BE_Train_Err_En_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_BE_Train_Err_En_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_BE_Train_Err_En_HSH (0x010EC04C)

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_1_REG             (0x0000C04D)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_2_REG             (0x0000C04E)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_3_REG             (0x0000C04F)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_4_REG             (0x0000C050)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_5_REG             (0x0000C051)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_6_REG             (0x0000C052)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_7_REG             (0x0000C053)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_REG             (0x0000C054)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_Wait_Timer_Current_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_Wait_Timer_Current_WID (16)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_Wait_Timer_Current_MSK (0x0000FFFF)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_Wait_Timer_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_Wait_Timer_Current_MAX (65535) // 0x0000FFFF
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_Wait_Timer_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_Wait_Timer_Current_HSH (0x1000C054)

#define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_REG             (0x0000C058)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Time_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Time_WID (16)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Time_MSK (0x0000FFFF)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Time_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Time_MAX (65535) // 0x0000FFFF
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Time_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Time_HSH (0x1000C058)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Timer_OFF     (20)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Timer_WID     ( 4)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Timer_MSK     (0x00F00000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Timer_MIN     (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Timer_MAX     (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Timer_DEF     (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Timer_HSH     (0x0428C058)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Clock_Frequency_OFF (24)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Clock_Frequency_WID ( 2)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Clock_Frequency_MSK (0x03000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Clock_Frequency_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Clock_Frequency_MAX (3) // 0x00000003
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Clock_Frequency_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Wait_Clock_Frequency_HSH (0x0230C058)

  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Select_Event_OFF (30)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Select_Event_WID ( 2)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Select_Event_MSK (0xC0000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Select_Event_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Select_Event_MAX (3) // 0x00000003
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Select_Event_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_Select_Event_HSH (0x023CC058)

#define MC0_REQ0_CR_CPGC2_BASE_REPEATS_REG                             (0x0000C05C)

  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_Base_Repeats_OFF              ( 0)
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_Base_Repeats_WID              (32)
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_Base_Repeats_MSK              (0xFFFFFFFF)
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_Base_Repeats_MIN              (0)
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_Base_Repeats_MAX              (4294967295) // 0xFFFFFFFF
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_Base_Repeats_DEF              (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_Base_Repeats_HSH              (0x2000C05C)

#define MC0_REQ0_CR_CPGC2_BASE_REPEATS_CURRENT_REG                     (0x0000C060)

  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_CURRENT_Base_Repeats_Current_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_CURRENT_Base_Repeats_Current_WID (32)
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_CURRENT_Base_Repeats_Current_MSK (0xFFFFFFFF)
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_CURRENT_Base_Repeats_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_CURRENT_Base_Repeats_Current_MAX (4294967295) // 0xFFFFFFFF
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_CURRENT_Base_Repeats_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_REPEATS_CURRENT_Base_Repeats_Current_HSH (0x2000C060)

#define MC0_REQ0_CR_CPGC2_BASE_COL_REPEATS_REG                         (0x0000C064)

  #define MC0_REQ0_CR_CPGC2_BASE_COL_REPEATS_Base_Col_Repeats_OFF      ( 0)
  #define MC0_REQ0_CR_CPGC2_BASE_COL_REPEATS_Base_Col_Repeats_WID      (32)
  #define MC0_REQ0_CR_CPGC2_BASE_COL_REPEATS_Base_Col_Repeats_MSK      (0xFFFFFFFF)
  #define MC0_REQ0_CR_CPGC2_BASE_COL_REPEATS_Base_Col_Repeats_MIN      (0)
  #define MC0_REQ0_CR_CPGC2_BASE_COL_REPEATS_Base_Col_Repeats_MAX      (4294967295) // 0xFFFFFFFF
  #define MC0_REQ0_CR_CPGC2_BASE_COL_REPEATS_Base_Col_Repeats_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_COL_REPEATS_Base_Col_Repeats_HSH      (0x2000C064)

#define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_REG                            (0x0000C068)

  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_Block_Repeats_OFF            ( 0)
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_Block_Repeats_WID            (32)
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_Block_Repeats_MSK            (0xFFFFFFFF)
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_Block_Repeats_MIN            (0)
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_Block_Repeats_MAX            (4294967295) // 0xFFFFFFFF
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_Block_Repeats_DEF            (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_Block_Repeats_HSH            (0x2000C068)

#define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_CURRENT_REG                    (0x0000C06C)

  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_CURRENT_Block_Repeats_Current_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_CURRENT_Block_Repeats_Current_WID (32)
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_CURRENT_Block_Repeats_Current_MSK (0xFFFFFFFF)
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_CURRENT_Block_Repeats_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_CURRENT_Block_Repeats_Current_MAX (4294967295) // 0xFFFFFFFF
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_CURRENT_Block_Repeats_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_CURRENT_Block_Repeats_Current_HSH (0x2000C06C)

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG                    (0x0000C070)

  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_WriteCmd_OFF         ( 0)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_WriteCmd_WID         ( 1)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_WriteCmd_MSK         (0x00000001)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_WriteCmd_MIN         (0)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_WriteCmd_MAX         (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_WriteCmd_DEF         (0x00000000)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_WriteCmd_HSH         (0x0100C070)

  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_Group_Srsp_OFF ( 1)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_Group_Srsp_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_Group_Srsp_MSK (0x00000002)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_Group_Srsp_MIN (0)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_Group_Srsp_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_Group_Srsp_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_Group_Srsp_HSH (0x0102C070)

  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_OFF           ( 2)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_WID           ( 1)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_MSK           (0x00000004)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_MIN           (0)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_MAX           (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_DEF           (0x00000000)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Offset_HSH           (0x0104C070)

  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Hammer_OFF           ( 3)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Hammer_WID           ( 1)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Hammer_MSK           (0x00000008)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Hammer_MIN           (0)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Hammer_MAX           (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Hammer_DEF           (0x00000000)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Hammer_HSH           (0x0106C070)

  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Alternate_Data_OFF   ( 4)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Alternate_Data_WID   ( 1)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Alternate_Data_MSK   (0x00000010)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Alternate_Data_MIN   (0)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Alternate_Data_MAX   (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Alternate_Data_DEF   (0x00000000)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Alternate_Data_HSH   (0x0108C070)

  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Address_Decode_or_PRBS_En_OFF ( 5)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Address_Decode_or_PRBS_En_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Address_Decode_or_PRBS_En_MSK (0x00000020)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Address_Decode_or_PRBS_En_MIN (0)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Address_Decode_or_PRBS_En_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Address_Decode_or_PRBS_En_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Address_Decode_or_PRBS_En_HSH (0x010AC070)

  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Invert_Data_OFF      ( 6)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Invert_Data_WID      ( 1)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Invert_Data_MSK      (0x00000040)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Invert_Data_MIN      (0)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Invert_Data_MAX      (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Invert_Data_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Invert_Data_HSH      (0x010CC070)

  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Last_OFF             ( 7)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Last_WID             ( 1)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Last_MSK             (0x00000080)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Last_MIN             (0)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Last_MAX             (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Last_DEF             (0x00000000)
  #define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_Last_HSH             (0x010EC070)

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_1_REG                    (0x0000C071)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_2_REG                    (0x0000C072)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_3_REG                    (0x0000C073)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_4_REG                    (0x0000C074)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_5_REG                    (0x0000C075)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_6_REG                    (0x0000C076)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_7_REG                    (0x0000C077)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_8_REG                    (0x0000C078)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_9_REG                    (0x0000C079)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_10_REG                   (0x0000C07A)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_11_REG                   (0x0000C07B)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_12_REG                   (0x0000C07C)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_13_REG                   (0x0000C07D)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_14_REG                   (0x0000C07E)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_15_REG                   (0x0000C07F)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_16_REG                   (0x0000C080)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_17_REG                   (0x0000C081)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_18_REG                   (0x0000C082)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_19_REG                   (0x0000C083)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_20_REG                   (0x0000C084)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_21_REG                   (0x0000C085)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_22_REG                   (0x0000C086)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_23_REG                   (0x0000C087)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_REG                           (0x0000C088)

  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_Hammer_Repeats_OFF          ( 0)
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_Hammer_Repeats_WID          (32)
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_Hammer_Repeats_MSK          (0xFFFFFFFF)
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_Hammer_Repeats_MIN          (0)
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_Hammer_Repeats_MAX          (4294967295) // 0xFFFFFFFF
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_Hammer_Repeats_DEF          (0x00000000)
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_Hammer_Repeats_HSH          (0x2000C088)

#define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_CURRENT_REG                   (0x0000C08C)

  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_CURRENT_Hammer_Repeats_Current_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_CURRENT_Hammer_Repeats_Current_WID (32)
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_CURRENT_Hammer_Repeats_Current_MSK (0xFFFFFFFF)
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_CURRENT_Hammer_Repeats_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_CURRENT_Hammer_Repeats_Current_MAX (4294967295) // 0xFFFFFFFF
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_CURRENT_Hammer_Repeats_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_CURRENT_Hammer_Repeats_Current_HSH (0x2000C08C)

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG             (0x0000C090)

  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_Adj_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_Adj_WID ( 2)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_Adj_MSK (0x00000003)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_Adj_MIN (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_Adj_MAX (3) // 0x00000003
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_Adj_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_Adj_HSH (0x0200C090)

  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_En_OFF ( 2)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_En_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_En_MSK (0x00000004)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_En_MIN (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_En_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_En_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Periodic_Data_Inv_En_HSH (0x0104C090)

  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Address_Direction_OFF ( 3)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Address_Direction_WID ( 3)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Address_Direction_MSK (0x00000038)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Address_Direction_MIN (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Address_Direction_MAX (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Address_Direction_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Address_Direction_HSH (0x0306C090)

  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Stripe_OFF    ( 6)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Stripe_WID    ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Stripe_MSK    (0x00000040)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Stripe_MIN    (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Stripe_MAX    (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Stripe_DEF    (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Stripe_HSH    (0x010CC090)

  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Last_OFF      ( 7)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Last_WID      ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Last_MSK      (0x00000080)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Last_MIN      (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Last_MAX      (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Last_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_Last_HSH      (0x010EC090)

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_1_REG             (0x0000C091)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_2_REG             (0x0000C092)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_3_REG             (0x0000C093)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_4_REG             (0x0000C094)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_5_REG             (0x0000C095)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_6_REG             (0x0000C096)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_7_REG             (0x0000C097)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_8_REG             (0x0000C098)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_9_REG             (0x0000C099)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_10_REG            (0x0000C09A)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_11_REG            (0x0000C09B)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_12_REG            (0x0000C09C)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_13_REG            (0x0000C09D)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_14_REG            (0x0000C09E)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_15_REG            (0x0000C09F)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG             (0x0000C0A0)

  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_WriteCmd_OFF  ( 0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_WriteCmd_WID  ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_WriteCmd_MSK  (0x00000001)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_WriteCmd_MIN  (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_WriteCmd_MAX  (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_WriteCmd_DEF  (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_WriteCmd_HSH  (0x0100C0A0)

  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Srsp_OFF      ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Srsp_WID      ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Srsp_MSK      (0x00000002)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Srsp_MIN      (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Srsp_MAX      (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Srsp_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Srsp_HSH      (0x0102C0A0)

  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Offset_OFF    ( 2)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Offset_WID    ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Offset_MSK    (0x00000004)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Offset_MIN    (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Offset_MAX    (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Offset_DEF    (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Offset_HSH    (0x0104C0A0)

  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Hammer_OFF    ( 3)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Hammer_WID    ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Hammer_MSK    (0x00000008)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Hammer_MIN    (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Hammer_MAX    (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Hammer_DEF    (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Hammer_HSH    (0x0106C0A0)

  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Alternate_Data_OFF ( 4)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Alternate_Data_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Alternate_Data_MSK (0x00000010)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Alternate_Data_MIN (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Alternate_Data_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Alternate_Data_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Alternate_Data_HSH (0x0108C0A0)

  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Invert_Data_OFF ( 6)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Invert_Data_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Invert_Data_MSK (0x00000040)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Invert_Data_MIN (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Invert_Data_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Invert_Data_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Invert_Data_HSH (0x010CC0A0)

  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Last_OFF      ( 7)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Last_WID      ( 1)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Last_MSK      (0x00000080)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Last_MIN      (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Last_MAX      (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Last_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_Last_HSH      (0x010EC0A0)

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_1_REG             (0x0000C0A1)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_2_REG             (0x0000C0A2)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_3_REG             (0x0000C0A3)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_4_REG             (0x0000C0A4)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_5_REG             (0x0000C0A5)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_6_REG             (0x0000C0A6)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_7_REG             (0x0000C0A7)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_8_REG             (0x0000C0A8)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_9_REG             (0x0000C0A9)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_10_REG            (0x0000C0AA)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_11_REG            (0x0000C0AB)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_CURRENT_REG                   (0x0000C0AC)

  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_CURRENT_Offset_Repeats_Current_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_CURRENT_Offset_Repeats_Current_WID (32)
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_CURRENT_Offset_Repeats_Current_MSK (0xFFFFFFFF)
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_CURRENT_Offset_Repeats_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_CURRENT_Offset_Repeats_Current_MAX (4294967295) // 0xFFFFFFFF
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_CURRENT_Offset_Repeats_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_CURRENT_Offset_Repeats_Current_HSH (0x2000C0AC)

#define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_REG                         (0x0000C0B0)

  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_Offset_Repeats_OFF        ( 0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_Offset_Repeats_WID        (32)
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_Offset_Repeats_MSK        (0xFFFFFFFF)
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_Offset_Repeats_MIN        (0)
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_Offset_Repeats_MAX        (4294967295) // 0xFFFFFFFF
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_Offset_Repeats_DEF        (0x00000000)
  #define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_Offset_Repeats_HSH        (0x2000C0B0)

#define MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_1_REG                         (0x0000C0B4)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_REG

#define MC0_REQ0_CR_CPGC2_REGION_LOW_REG                               (0x0000C0B8)

  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Col_OFF                     ( 0)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Col_WID                     (10)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Col_MSK                     (0x000003FF)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Col_MIN                     (0)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Col_MAX                     (1023) // 0x000003FF
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Col_DEF                     (0x00000000)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Col_HSH                     (0x4A00C0B8)

  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Rank_OFF                    (24)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Rank_WID                    ( 5)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Rank_MSK                    (0x1F000000)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Rank_MIN                    (0)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Rank_MAX                    (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Rank_DEF                    (0x00000000)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Rank_HSH                    (0x4530C0B8)

  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Row_OFF                     (32)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Row_WID                     (18)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Row_MSK                     (0x0003FFFF00000000ULL)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Row_MIN                     (0)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Row_MAX                     (262143) // 0x0003FFFF
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Row_DEF                     (0x00000000)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Row_HSH                     (0x5240C0B8)

  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Bank_OFF                    (56)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Bank_WID                    ( 5)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Bank_MSK                    (0x1F00000000000000ULL)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Bank_MIN                    (0)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Bank_MAX                    (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Bank_DEF                    (0x00000000)
  #define MC0_REQ0_CR_CPGC2_REGION_LOW_Low_Bank_HSH                    (0x4570C0B8)

#define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REG                             (0x0000C0D8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Col_OFF       ( 0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Col_WID       ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Col_MSK       (0x0000001F)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Col_MIN       (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Col_MAX       (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Col_DEF       (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Col_HSH       (0x4500C0D8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Row_OFF       ( 8)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Row_WID       ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Row_MSK       (0x00001F00)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Row_MIN       (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Row_MAX       (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Row_DEF       (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Bits_Row_HSH       (0x4510C0D8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Bank_OFF       (16)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Bank_WID       ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Bank_MSK       (0x001F0000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Bank_MIN       (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Bank_MAX       (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Bank_DEF       (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Bank_HSH       (0x4520C0D8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Rank_OFF       (24)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Rank_WID       ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Rank_MSK       (0x1F000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Rank_MIN       (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Rank_MAX       (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Rank_DEF       (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Block_Size_Max_Rank_HSH       (0x4530C0D8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Col_OFF      (32)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Col_WID      ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Col_MSK      (0x0000001F00000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Col_MIN      (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Col_MAX      (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Col_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Col_HSH      (0x4540C0D8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Row_OFF      (40)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Row_WID      ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Row_MSK      (0x00001F0000000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Row_MIN      (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Row_MAX      (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Row_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Bits_Row_HSH      (0x4550C0D8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Bank_OFF      (48)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Bank_WID      ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Bank_MSK      (0x001F000000000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Bank_MIN      (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Bank_MAX      (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Bank_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Bank_HSH      (0x4560C0D8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Rank_OFF      (56)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Rank_WID      ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Rank_MSK      (0x1F00000000000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Rank_MIN      (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Rank_MAX      (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Rank_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_Region_Size_Max_Rank_HSH      (0x4570C0D8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REQUEST_DATA_SIZE_OFF         (62)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REQUEST_DATA_SIZE_WID         ( 1)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REQUEST_DATA_SIZE_MSK         (0x4000000000000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REQUEST_DATA_SIZE_MIN         (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REQUEST_DATA_SIZE_MAX         (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REQUEST_DATA_SIZE_DEF         (0x00000001)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REQUEST_DATA_SIZE_HSH         (0x417CC0D8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_BL_CHOP_EN_OFF                (63)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_BL_CHOP_EN_WID                ( 1)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_BL_CHOP_EN_MSK                (0x8000000000000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_BL_CHOP_EN_MIN                (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_BL_CHOP_EN_MAX                (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_BL_CHOP_EN_DEF                (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_BL_CHOP_EN_HSH                (0x417EC0D8)

#define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_REG                     (0x0000C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_One_Col_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_One_Col_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_One_Col_MSK (0x00000001)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_One_Col_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_One_Col_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_One_Col_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_One_Col_HSH (0x0100C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_Half_Block_OFF ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_Half_Block_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_Half_Block_MSK (0x00000002)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_Half_Block_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_Half_Block_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_Half_Block_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Col_Move_Half_Block_HSH (0x0102C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Hammer_Inc_Rate_OFF   ( 2)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Hammer_Inc_Rate_WID   ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Hammer_Inc_Rate_MSK   (0x00000004)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Hammer_Inc_Rate_MIN   (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Hammer_Inc_Rate_MAX   (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Hammer_Inc_Rate_DEF   (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Hammer_Inc_Rate_HSH   (0x0104C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Bank_Move_One_OFF ( 3)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Bank_Move_One_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Bank_Move_One_MSK (0x00000008)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Bank_Move_One_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Bank_Move_One_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Bank_Move_One_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Bank_Move_One_HSH (0x0106C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_One_Row_OFF ( 4)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_One_Row_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_One_Row_MSK (0x00000010)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_One_Row_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_One_Row_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_One_Row_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_One_Row_HSH (0x0108C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_Half_Block_OFF ( 5)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_Half_Block_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_Half_Block_MSK (0x00000020)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_Half_Block_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_Half_Block_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_Half_Block_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Row_Move_Half_Block_HSH (0x010AC0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Row_Inc_OFF           ( 6)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Row_Inc_WID           ( 4)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Row_Inc_MSK           (0x000003C0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Row_Inc_MIN           (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Row_Inc_MAX           (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Row_Inc_DEF           (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Row_Inc_HSH           (0x040CC0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Rank_Move_One_OFF (10)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Rank_Move_One_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Rank_Move_One_MSK (0x00000400)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Rank_Move_One_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Rank_Move_One_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Rank_Move_One_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Block_Rank_Move_One_HSH (0x0114C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Col_Inc_OFF           (11)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Col_Inc_WID           ( 4)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Col_Inc_MSK           (0x00007800)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Col_Inc_MIN           (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Col_Inc_MAX           (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Col_Inc_DEF           (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Col_Inc_HSH           (0x0416C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Bank_Inc_OFF          (15)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Bank_Inc_WID          ( 3)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Bank_Inc_MSK          (0x00038000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Bank_Inc_MIN          (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Bank_Inc_MAX          (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Bank_Inc_DEF          (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Bank_Inc_HSH          (0x031EC0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Reserved_Rank_Inc_OFF (18)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Reserved_Rank_Inc_WID ( 3)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Reserved_Rank_Inc_MSK (0x001C0000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Reserved_Rank_Inc_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Reserved_Rank_Inc_MAX (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Reserved_Rank_Inc_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Reserved_Rank_Inc_HSH (0x0324C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Order0_Inc_Rate_OFF (21)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Order0_Inc_Rate_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Order0_Inc_Rate_MSK (0x00200000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Order0_Inc_Rate_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Order0_Inc_Rate_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Order0_Inc_Rate_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Order0_Inc_Rate_HSH (0x012AC0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Enable_OFF (22)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Enable_WID ( 4)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Enable_MSK (0x03C00000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Enable_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Enable_MAX (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Enable_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Enable_HSH (0x042CC0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Rate_OFF (26)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Rate_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Rate_MSK (0x04000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Rate_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Rate_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Rate_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Address_Inversion_Rate_HSH (0x0134C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Carry_Mode_OFF (27)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Carry_Mode_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Carry_Mode_MSK (0x08000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Carry_Mode_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Carry_Mode_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Carry_Mode_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Carry_Mode_HSH (0x0136C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Col_En_OFF  (28)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Col_En_WID  ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Col_En_MSK  (0x10000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Col_En_MIN  (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Col_En_MAX  (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Col_En_DEF  (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Col_En_HSH  (0x0138C0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Row_En_OFF  (29)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Row_En_WID  ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Row_En_MSK  (0x20000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Row_En_MIN  (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Row_En_MAX  (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Row_En_DEF  (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Row_En_HSH  (0x013AC0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Bnk_En_OFF  (30)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Bnk_En_WID  ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Bnk_En_MSK  (0x40000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Bnk_En_MIN  (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Bnk_En_MAX  (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Bnk_En_DEF  (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Bnk_En_HSH  (0x013CC0E0)

  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Rnk_En_OFF  (31)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Rnk_En_WID  ( 1)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Rnk_En_MSK  (0x80000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Rnk_En_MIN  (0)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Rnk_En_MAX  (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Rnk_En_DEF  (0x00000000)
  #define MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_Addr_Prbs_Rnk_En_HSH  (0x013EC0E0)

#define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_REG                        (0x0000C0E8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Column_Seed_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Column_Seed_WID (10)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Column_Seed_MSK (0x000003FF)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Column_Seed_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Column_Seed_MAX (1023) // 0x000003FF
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Column_Seed_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Column_Seed_HSH (0x4A00C0E8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Rank_Seed_OFF (24)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Rank_Seed_WID ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Rank_Seed_MSK (0x1F000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Rank_Seed_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Rank_Seed_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Rank_Seed_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Rank_Seed_HSH (0x4530C0E8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Row_Seed_OFF (32)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Row_Seed_WID (18)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Row_Seed_MSK (0x0003FFFF00000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Row_Seed_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Row_Seed_MAX (262143) // 0x0003FFFF
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Row_Seed_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Row_Seed_HSH (0x5240C0E8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Bank_Seed_OFF (56)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Bank_Seed_WID ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Bank_Seed_MSK (0x1F00000000000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Bank_Seed_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Bank_Seed_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Bank_Seed_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_Address_PRBS_Bank_Seed_HSH (0x4570C0E8)

#define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_REG                     (0x0000C0F0)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Column_Current_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Column_Current_WID (10)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Column_Current_MSK (0x000003FF)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Column_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Column_Current_MAX (1023) // 0x000003FF
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Column_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Column_Current_HSH (0x4A00C0F0)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Rank_Current_OFF (24)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Rank_Current_WID ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Rank_Current_MSK (0x1F000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Rank_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Rank_Current_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Rank_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Rank_Current_HSH (0x4530C0F0)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Row_Current_OFF (32)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Row_Current_WID (18)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Row_Current_MSK (0x0003FFFF00000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Row_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Row_Current_MAX (262143) // 0x0003FFFF
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Row_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Row_Current_HSH (0x5240C0F0)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Bank_Current_OFF (56)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Bank_Current_WID ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Bank_Current_MSK (0x1F00000000000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Bank_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Bank_Current_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Bank_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_Address_PRBS_Bank_Current_HSH (0x4570C0F0)

#define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_REG                        (0x0000C0F8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Column_Save_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Column_Save_WID (10)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Column_Save_MSK (0x000003FF)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Column_Save_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Column_Save_MAX (1023) // 0x000003FF
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Column_Save_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Column_Save_HSH (0x4A00C0F8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Rank_Save_OFF (24)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Rank_Save_WID ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Rank_Save_MSK (0x1F000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Rank_Save_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Rank_Save_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Rank_Save_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Rank_Save_HSH (0x4530C0F8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Row_Save_OFF (32)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Row_Save_WID (18)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Row_Save_MSK (0x0003FFFF00000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Row_Save_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Row_Save_MAX (262143) // 0x0003FFFF
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Row_Save_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Row_Save_HSH (0x5240C0F8)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Bank_Save_OFF (56)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Bank_Save_WID ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Bank_Save_MSK (0x1F00000000000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Bank_Save_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Bank_Save_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Bank_Save_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_Address_PRBS_Bank_Save_HSH (0x4570C0F8)

#define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_REG                        (0x0000C100)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Column_Poly_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Column_Poly_WID (10)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Column_Poly_MSK (0x000003FF)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Column_Poly_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Column_Poly_MAX (1023) // 0x000003FF
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Column_Poly_DEF (0x00000072)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Column_Poly_HSH (0x4A00C100)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Rank_Poly_OFF (24)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Rank_Poly_WID ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Rank_Poly_MSK (0x1F000000)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Rank_Poly_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Rank_Poly_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Rank_Poly_DEF (0x00000003)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Rank_Poly_HSH (0x4530C100)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Row_Poly_OFF (32)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Row_Poly_WID (18)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Row_Poly_MSK (0x0003FFFF00000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Row_Poly_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Row_Poly_MAX (262143) // 0x0003FFFF
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Row_Poly_DEF (0x00009924)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Row_Poly_HSH (0x5240C100)

  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Bank_Poly_OFF (56)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Bank_Poly_WID ( 5)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Bank_Poly_MSK (0x1F00000000000000ULL)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Bank_Poly_MIN (0)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Bank_Poly_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Bank_Poly_DEF (0x00000006)
  #define MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_Address_PRBS_Bank_Poly_HSH (0x4570C100)

#define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_REG                        (0x0000C108)

  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_WID (12)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_MSK (0x00000FFF)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_MAX (4095) // 0x00000FFF
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_DEF (0x00000001)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_HSH (0x0C00C108)

  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_OFF           (16)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_WID           (12)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_MSK           (0x0FFF0000)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_MIN           (0)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_MAX           (4095) // 0x00000FFF
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_DEF           (0x00000190)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_HSH           (0x0C20C108)

  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_OFF      (28)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_WID      ( 4)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_MSK      (0xF0000000)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_MIN      (0)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_MAX      (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_DEF      (0x00000001)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_HSH      (0x0438C108)

#define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_A0_REG                     (0x0000C108)

  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_A0_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_A0_WID (10)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_A0_MSK (0x000003FF)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_A0_MIN (0)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_A0_MAX (1023) // 0x000003FF
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_A0_DEF (0x00000001)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Prescaler_for_Clock_Freq_A0_HSH (0x0A00C108)

  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_A0_OFF        (16)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_A0_WID        (10)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_A0_MSK        (0x03FF0000)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_A0_MIN        (0)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_A0_MAX        (1023) // 0x000003FF
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_A0_DEF        (0x00000190)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Clock_Freq_A0_HSH        (0x0A20C108)

  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_A0_OFF   (28)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_A0_WID   ( 4)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_A0_MSK   (0xF0000000)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_A0_MIN   (0)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_A0_MAX   (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_A0_DEF   (0x00000001)
  #define MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_Increment_Value_A0_HSH   (0x0438C108)

#define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_REG                          (0x0000C10C)

  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Command_Instruction_Current_OFF ( 0)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Command_Instruction_Current_WID ( 3)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Command_Instruction_Current_MSK (0x00000007)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Command_Instruction_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Command_Instruction_Current_MAX (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Command_Instruction_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Command_Instruction_Current_HSH (0x0300C10C)

  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Address_Instruction_Current_OFF ( 3)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Address_Instruction_Current_WID ( 3)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Address_Instruction_Current_MSK (0x00000038)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Address_Instruction_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Address_Instruction_Current_MAX (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Address_Instruction_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Address_Instruction_Current_HSH (0x0306C10C)

  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Group_Instruction_Current_OFF ( 6)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Group_Instruction_Current_WID ( 1)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Group_Instruction_Current_MSK (0x00000040)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Group_Instruction_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Group_Instruction_Current_MAX (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Group_Instruction_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Offset_Group_Instruction_Current_HSH (0x010CC10C)

  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Command_Instruction_Current_OFF ( 8)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Command_Instruction_Current_WID ( 5)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Command_Instruction_Current_MSK (0x00001F00)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Command_Instruction_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Command_Instruction_Current_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Command_Instruction_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Command_Instruction_Current_HSH (0x0510C10C)

  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Algorithm_Instruction_Current_OFF (15)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Algorithm_Instruction_Current_WID ( 3)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Algorithm_Instruction_Current_MSK (0x00038000)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Algorithm_Instruction_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Algorithm_Instruction_Current_MAX (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Algorithm_Instruction_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Algorithm_Instruction_Current_HSH (0x031EC10C)

  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Data_Instruction_Current_OFF (24)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Data_Instruction_Current_WID ( 2)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Data_Instruction_Current_MSK (0x03000000)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Data_Instruction_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Data_Instruction_Current_MAX (3) // 0x00000003
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Data_Instruction_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Data_Instruction_Current_HSH (0x0230C10C)

  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Address_Instruction_Current_OFF (28)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Address_Instruction_Current_WID ( 2)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Address_Instruction_Current_MSK (0x30000000)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Address_Instruction_Current_MIN (0)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Address_Instruction_Current_MAX (3) // 0x00000003
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Address_Instruction_Current_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_Address_Instruction_Current_HSH (0x0238C10C)

#define MC0_REQ0_CR_CPGC_SEQ_CFG_A_REG                                 (0x0000C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_OFF         ( 8)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_WID         ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_MSK         (0x00000100)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_MIN         (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_MAX         (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_DEF         (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_HSH         (0x0110C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_OFF       ( 9)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_WID       ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_MSK       (0x00000200)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_MIN       (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_MAX       (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_DEF       (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_HSH       (0x0112C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_OFF             (10)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_WID             ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_MSK             (0x00000400)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_MIN             (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_MAX             (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_DEF             (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_HSH             (0x0114C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_OFF              (11)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_WID              ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_MSK              (0x00000800)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_MIN              (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_MAX              (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_DEF              (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_HSH              (0x0116C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_OFF           (12)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_WID           ( 3)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_MSK           (0x00007000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_MIN           (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_MAX           (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_DEF           (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_HSH           (0x0318C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_OFF                (16)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_WID                ( 4)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_MSK                (0x000F0000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_MIN                (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_MAX                (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_DEF                (0x00000001)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_HSH                (0x0420C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_OFF         (24)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_WID         ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_MSK         (0x01000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_MIN         (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_MAX         (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_DEF         (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_HSH         (0x0130C110)

#define MC0_REQ0_CR_CPGC_SEQ_CFG_A_P0_REG                              (0x0000C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_OFF      ( 8)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_WID      ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_MSK      (0x00000100)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_MIN      (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_MAX      (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_HSH      (0x0110C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_OFF    ( 9)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_WID    ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_MSK    (0x00000200)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_MIN    (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_MAX    (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_DEF    (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_HSH    (0x0112C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_OFF          (10)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_WID          ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_MSK          (0x00000400)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_MIN          (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_MAX          (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_DEF          (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_HSH          (0x0114C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_OFF           (11)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_WID           ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_MSK           (0x00000800)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_MIN           (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_MAX           (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_DEF           (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_HSH           (0x0116C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_OFF        (12)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_WID        ( 3)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_MSK        (0x00007000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_MIN        (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_MAX        (7) // 0x00000007
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_DEF        (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_HSH        (0x0318C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_OFF             (16)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_WID             ( 4)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_MSK             (0x000F0000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_MIN             (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_MAX             (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_DEF             (0x00000001)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_HSH             (0x0420C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_OFF      (24)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_WID      ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_MSK      (0x01000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_MIN      (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_MAX      (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_HSH      (0x0130C110)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_OFF      (25)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_WID      ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_MSK      (0x02000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_MIN      (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_MAX      (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_DEF      (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_HSH      (0x0132C110)

#define MC0_REQ0_CR_CPGC_SEQ_CFG_B_REG                                 (0x0000C114)

  #define MC0_REQ0_CR_CPGC_SEQ_CFG_B_START_DELAY_OFF                   ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_B_START_DELAY_WID                   (10)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_B_START_DELAY_MSK                   (0x000003FF)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_B_START_DELAY_MIN                   (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_B_START_DELAY_MAX                   (1023) // 0x000003FF
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_B_START_DELAY_DEF                   (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CFG_B_START_DELAY_HSH                   (0x0A00C114)

#define MC0_REQ0_CR_CPGC_SEQ_CTL_REG                                   (0x0000C118)

  #define MC0_REQ0_CR_CPGC_SEQ_CTL_START_TEST_OFF                      ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_START_TEST_WID                      ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_START_TEST_MSK                      (0x00000001)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_START_TEST_MIN                      (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_START_TEST_MAX                      (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_START_TEST_DEF                      (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_START_TEST_HSH                      (0x0100C118)

  #define MC0_REQ0_CR_CPGC_SEQ_CTL_STOP_TEST_OFF                       ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_STOP_TEST_WID                       ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_STOP_TEST_MSK                       (0x00000002)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_STOP_TEST_MIN                       (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_STOP_TEST_MAX                       (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_STOP_TEST_DEF                       (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_STOP_TEST_HSH                       (0x0102C118)

  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CLEAR_ERRORS_OFF                    ( 2)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CLEAR_ERRORS_WID                    ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CLEAR_ERRORS_MSK                    (0x00000004)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CLEAR_ERRORS_MIN                    (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CLEAR_ERRORS_MAX                    (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CLEAR_ERRORS_DEF                    (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CLEAR_ERRORS_HSH                    (0x0104C118)

  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_CMD_MODE_OFF                 ( 8)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_CMD_MODE_WID                 ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_CMD_MODE_MSK                 (0x00000100)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_CMD_MODE_MIN                 (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_CMD_MODE_MAX                 (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_CMD_MODE_DEF                 (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_CMD_MODE_HSH                 (0x0110C118)

  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CONTINUE_SINGLE_MODE_OFF            ( 9)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CONTINUE_SINGLE_MODE_WID            ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CONTINUE_SINGLE_MODE_MSK            (0x00000200)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CONTINUE_SINGLE_MODE_MIN            (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CONTINUE_SINGLE_MODE_MAX            (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CONTINUE_SINGLE_MODE_DEF            (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_CONTINUE_SINGLE_MODE_HSH            (0x0112C118)

  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_MARCH_ELEMENT_MODE_OFF       (10)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_MARCH_ELEMENT_MODE_WID       ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_MARCH_ELEMENT_MODE_MSK       (0x00000400)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_MARCH_ELEMENT_MODE_MIN       (0)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_MARCH_ELEMENT_MODE_MAX       (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_MARCH_ELEMENT_MODE_DEF       (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_CTL_SINGLE_MARCH_ELEMENT_MODE_HSH       (0x0114C118)

#define MC0_REQ0_CR_CPGC_SEQ_STATUS_REG                                (0x0000C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_INTERNAL_ERR_OFF                 (13)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_INTERNAL_ERR_WID                 ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_INTERNAL_ERR_MSK                 (0x00002000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_INTERNAL_ERR_MIN                 (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_INTERNAL_ERR_MAX                 (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_INTERNAL_ERR_DEF                 (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_INTERNAL_ERR_HSH                 (0x011AC11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_OFF          (14)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_WID          ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_MSK          (0x00004000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_MIN          (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_MAX          (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_DEF          (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_HSH          (0x011CC11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_OFF              (15)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_WID              ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_MSK              (0x00008000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_MIN              (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_MAX              (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_DEF              (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_HSH              (0x011EC11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_OFF            (16)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_WID            ( 4)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_MSK            (0x000F0000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_MIN            (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_MAX            (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_DEF            (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_HSH            (0x0420C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_OFF                 (24)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_WID                 ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_MSK                 (0x01000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_MIN                 (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_MAX                 (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_DEF                 (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_HSH                 (0x0130C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_OFF               (25)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_WID               ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_MSK               (0x02000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_MIN               (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_MAX               (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_DEF               (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_HSH               (0x0132C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_OFF                    (26)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_WID                    ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_MSK                    (0x04000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_MIN                    (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_MAX                    (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_DEF                    (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_HSH                    (0x0134C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_OFF           (27)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_WID           ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_MSK           (0x08000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_MIN           (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_MAX           (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_DEF           (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_HSH           (0x0136C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_OFF                    (28)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_WID                    ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_MSK                    (0x10000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_MIN                    (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_MAX                    (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_DEF                    (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_HSH                    (0x0138C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_OFF        (29)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_WID        ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_MSK        (0x20000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_MIN        (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_MAX        (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_DEF        (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_HSH        (0x013AC11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_OFF                    (30)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_WID                    ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_MSK                    (0x40000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_MIN                    (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_MAX                    (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_DEF                    (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_HSH                    (0x013CC11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_OFF                    (31)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_WID                    ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_MSK                    (0x80000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_MIN                    (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_MAX                    (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_DEF                    (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_HSH                    (0x013EC11C)

#define MC0_REQ0_CR_CPGC_SEQ_STATUS_A0_REG                             (0x0000C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_A0_OFF       (14)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_A0_WID       ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_A0_MSK       (0x00004000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_A0_MIN       (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_A0_MAX       (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_A0_DEF       (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CREDITS_INITIALIZED_A0_HSH       (0x011CC11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_A0_OFF           (15)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_A0_WID           ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_A0_MSK           (0x00008000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_A0_MIN           (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_A0_MAX           (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_A0_DEF           (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_CFG_ERR_A0_HSH           (0x011EC11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_A0_OFF         (16)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_A0_WID         ( 4)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_A0_MSK         (0x000F0000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_A0_MIN         (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_A0_MAX         (15) // 0x0000000F
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_A0_DEF         (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_CHANNEL_AVAILABLE_A0_HSH         (0x0420C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_A0_OFF              (24)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_A0_WID              ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_A0_MSK              (0x01000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_A0_MIN              (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_A0_MAX              (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_A0_DEF              (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_ABORTED_A0_HSH              (0x0130C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_A0_OFF            (25)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_A0_WID            ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_A0_MSK            (0x02000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_A0_MIN            (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_A0_MAX            (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_A0_DEF            (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_EVENT_NOT_SEEN_A0_HSH            (0x0132C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_A0_OFF                 (26)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_A0_WID                 ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_A0_MSK                 (0x04000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_A0_MIN                 (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_A0_MAX                 (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_A0_DEF                 (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_WAIT_A0_HSH                 (0x0134C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_A0_OFF        (27)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_A0_WID        ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_A0_MSK        (0x08000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_A0_MIN        (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_A0_MAX        (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_A0_DEF        (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_SINGLE_MODE_PAUSED_A0_HSH        (0x0136C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_A0_OFF                 (28)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_A0_WID                 ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_A0_MSK                 (0x10000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_A0_MIN                 (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_A0_MAX                 (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_A0_DEF                 (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_ALGO_DONE_A0_HSH                 (0x0138C11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_A0_OFF     (29)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_A0_WID     ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_A0_MSK     (0x20000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_A0_MIN     (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_A0_MAX     (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_A0_DEF     (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_START_TEST_DELAY_BUSY_A0_HSH     (0x013AC11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_A0_OFF                 (30)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_A0_WID                 ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_A0_MSK                 (0x40000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_A0_MIN                 (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_A0_MAX                 (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_A0_DEF                 (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_BUSY_A0_HSH                 (0x013CC11C)

  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_A0_OFF                 (31)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_A0_WID                 ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_A0_MSK                 (0x80000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_A0_MIN                 (0)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_A0_MAX                 (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_A0_DEF                 (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_STATUS_TEST_DONE_A0_HSH                 (0x013EC11C)

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG                     (0x0000C120)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_CONTENT_OFF           ( 0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_CONTENT_WID           (64)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_CONTENT_MSK           (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_CONTENT_MIN           (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_CONTENT_MAX           (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_CONTENT_DEF           (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_CONTENT_HSH           (0x4000C120)

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_1_REG                     (0x0000C128)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_2_REG                     (0x0000C130)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_3_REG                     (0x0000C138)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_4_REG                     (0x0000C140)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_5_REG                     (0x0000C148)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_6_REG                     (0x0000C150)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_7_REG                     (0x0000C158)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_ECC_0_REG                 (0x0000C160)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_ECC_1_REG                 (0x0000C168)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_REG                (0x0000C170)

  #define MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_Read_Command_Count_Current_OFF ( 0)
  #define MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_Read_Command_Count_Current_WID (32)
  #define MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_Read_Command_Count_Current_MSK (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_Read_Command_Count_Current_MIN (0)
  #define MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_Read_Command_Count_Current_MAX (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_Read_Command_Count_Current_DEF (0x00000000)
  #define MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_Read_Command_Count_Current_HSH (0x2000C170)

#define MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_REG                   (0x0000C174)

  #define MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_Mask_First_N_Reads_OFF ( 0)
  #define MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_Mask_First_N_Reads_WID (32)
  #define MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_Mask_First_N_Reads_MSK (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_Mask_First_N_Reads_MIN (0)
  #define MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_Mask_First_N_Reads_MAX (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_Mask_First_N_Reads_DEF (0x00000000)
  #define MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_Mask_First_N_Reads_HSH (0x2000C174)

#define MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_REG                             (0x0000C178)

  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_Error_Summary_OFF             ( 0)
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_Error_Summary_WID             (32)
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_Error_Summary_MSK             (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_Error_Summary_MIN             (0)
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_Error_Summary_MAX             (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_Error_Summary_DEF             (0x00000000)
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_Error_Summary_HSH             (0x2000C178)

#define MC0_CH0_CR_CPGC2_ERR_SUMMARY_B_REG                             (0x0000C17C)
//Duplicate of MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_REG

#define MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_REG                             (0x0000C180)

  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_Error_Summary_OFF             ( 0)
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_Error_Summary_WID             ( 8)
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_Error_Summary_MSK             (0x000000FF)
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_Error_Summary_MIN             (0)
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_Error_Summary_MAX             (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_Error_Summary_DEF             (0x00000000)
  #define MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_Error_Summary_HSH             (0x0800C180)

#define MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_REG                          (0x0000C184)

  #define MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_FAIL_MAX_OFF               ( 0)
  #define MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_FAIL_MAX_WID               (32)
  #define MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_FAIL_MAX_MSK               (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_FAIL_MAX_MIN               (0)
  #define MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_FAIL_MAX_MAX               (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_FAIL_MAX_DEF               (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_FAIL_MAX_HSH               (0x2000C184)

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_REG                        (0x0000C188)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_OFF       ( 0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_WID       ( 2)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_MSK       (0x00000003)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_MIN       (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_MAX       (3) // 0x00000003
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_HSH       (0x0200C188)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_OFF          ( 2)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_WID          ( 2)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_MSK          (0x0000000C)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_MIN          (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_MAX          (3) // 0x00000003
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_DEF          (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_HSH          (0x0204C188)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_OFF          ( 4)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_WID          ( 2)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_MSK          (0x00000030)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_MIN          (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_MAX          (3) // 0x00000003
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_DEF          (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_HSH          (0x0208C188)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_OFF         ( 6)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_WID         ( 1)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_MSK         (0x00000040)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_MIN         (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_DEF         (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_HSH         (0x010CC188)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_OFF      ( 7)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_WID      ( 1)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_MSK      (0x00000080)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_MIN      (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_DEF      (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_HSH      (0x010EC188)

#define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_P0_REG                     (0x0000C188)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_P0_OFF       ( 2)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_P0_WID       ( 2)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_P0_MSK       (0x0000000C)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_P0_MIN       (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_P0_MAX       (3) // 0x00000003
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_MODE3_BANKS_P0_HSH       (0x0204C188)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_P0_OFF       ( 4)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_P0_WID       ( 2)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_P0_MSK       (0x00000030)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_P0_MIN       (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_P0_MAX       (3) // 0x00000003
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_UPPER_BANKS_P0_HSH       (0x0208C188)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_P0_OFF      ( 6)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_P0_WID      ( 1)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_P0_MSK      (0x00000040)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_P0_MIN      (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_P0_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_StopOnRaster_P0_HSH      (0x010CC188)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_P0_OFF   ( 7)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_P0_WID   ( 1)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_P0_MSK   (0x00000080)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_P0_MIN   (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_P0_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoClear_P0_HSH   (0x010EC188)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_P0_OFF    ( 8)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_P0_WID    ( 3)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_P0_MSK    (0x00000700)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_P0_MIN    (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_P0_MAX    (7) // 0x00000007
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_RasterRepoMode_P0_HSH    (0x0310C188)

#define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_REG                        (0x0000C18C)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_BitmapValid_OFF          ( 0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_BitmapValid_WID          ( 1)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_BitmapValid_MSK          (0x00000001)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_BitmapValid_MIN          (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_BitmapValid_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_BitmapValid_DEF          (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_BitmapValid_HSH          (0x0100C18C)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_SummaryValid_OFF         ( 1)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_SummaryValid_WID         ( 1)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_SummaryValid_MSK         (0x00000002)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_SummaryValid_MIN         (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_SummaryValid_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_SummaryValid_DEF         (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_SummaryValid_HSH         (0x0102C18C)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailExcessAll_OFF        ( 2)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailExcessAll_WID        ( 1)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailExcessAll_MSK        (0x00000004)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailExcessAll_MIN        (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailExcessAll_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailExcessAll_DEF        (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailExcessAll_HSH        (0x0104C18C)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailAnyAll_OFF           ( 3)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailAnyAll_WID           ( 1)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailAnyAll_MSK           (0x00000008)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailAnyAll_MIN           (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailAnyAll_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailAnyAll_DEF           (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_FailAnyAll_HSH           (0x0106C18C)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_NumErrLogged_OFF         ( 4)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_NumErrLogged_WID         ( 3)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_NumErrLogged_MSK         (0x00000070)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_NumErrLogged_MIN         (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_NumErrLogged_MAX         (7) // 0x00000007
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_NumErrLogged_DEF         (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_NumErrLogged_HSH         (0x0308C18C)

  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_RasterRepoFull_OFF       ( 7)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_RasterRepoFull_WID       ( 1)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_RasterRepoFull_MSK       (0x00000080)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_RasterRepoFull_MIN       (0)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_RasterRepoFull_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_RasterRepoFull_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_RasterRepoFull_HSH       (0x010EC18C)

#define MC0_CH0_CR_CPGC_DPAT_CFG_REG                                   (0x0000C190)

  #define MC0_CH0_CR_CPGC_DPAT_CFG_LANE_ROTATE_RATE_OFF                ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_LANE_ROTATE_RATE_WID                ( 6)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_LANE_ROTATE_RATE_MSK                (0x0000003F)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_LANE_ROTATE_RATE_MIN                (0)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_LANE_ROTATE_RATE_MAX                (63) // 0x0000003F
  #define MC0_CH0_CR_CPGC_DPAT_CFG_LANE_ROTATE_RATE_DEF                (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_LANE_ROTATE_RATE_HSH                (0x0600C190)

  #define MC0_CH0_CR_CPGC_DPAT_CFG_WRITE_ADDRESS_AS_DATA_OFF           ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_WRITE_ADDRESS_AS_DATA_WID           ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_WRITE_ADDRESS_AS_DATA_MSK           (0x00000100)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_WRITE_ADDRESS_AS_DATA_MIN           (0)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_WRITE_ADDRESS_AS_DATA_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_CFG_WRITE_ADDRESS_AS_DATA_DEF           (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_WRITE_ADDRESS_AS_DATA_HSH           (0x0110C190)

  #define MC0_CH0_CR_CPGC_DPAT_CFG_READ_ADDRESS_AS_DATA_OFF            ( 9)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_READ_ADDRESS_AS_DATA_WID            ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_READ_ADDRESS_AS_DATA_MSK            (0x00000200)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_READ_ADDRESS_AS_DATA_MIN            (0)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_READ_ADDRESS_AS_DATA_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_CFG_READ_ADDRESS_AS_DATA_DEF            (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_READ_ADDRESS_AS_DATA_HSH            (0x0112C190)

  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DISABLE_OFF                     (13)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DISABLE_WID                     ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DISABLE_MSK                     (0x00002000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DISABLE_MIN                     (0)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DISABLE_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DISABLE_DEF                     (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DISABLE_HSH                     (0x011AC190)

  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_REPLACE_BYTE_CONTROL_OFF        (14)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_REPLACE_BYTE_CONTROL_WID        ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_REPLACE_BYTE_CONTROL_MSK        (0x00004000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_REPLACE_BYTE_CONTROL_MIN        (0)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_REPLACE_BYTE_CONTROL_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_REPLACE_BYTE_CONTROL_DEF        (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_REPLACE_BYTE_CONTROL_HSH        (0x011CC190)

  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DATA_SOURCE_SEL_OFF             (15)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DATA_SOURCE_SEL_WID             ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DATA_SOURCE_SEL_MSK             (0x00008000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DATA_SOURCE_SEL_MIN             (0)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DATA_SOURCE_SEL_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DATA_SOURCE_SEL_DEF             (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_ECC_DATA_SOURCE_SEL_HSH             (0x011EC190)

  #define MC0_CH0_CR_CPGC_DPAT_CFG_SAVE_LFSR_SEED_RATE_OFF             (16)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_SAVE_LFSR_SEED_RATE_WID             ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_SAVE_LFSR_SEED_RATE_MSK             (0x00FF0000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_SAVE_LFSR_SEED_RATE_MIN             (0)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_SAVE_LFSR_SEED_RATE_MAX             (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_DPAT_CFG_SAVE_LFSR_SEED_RATE_DEF             (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_SAVE_LFSR_SEED_RATE_HSH             (0x0820C190)

  #define MC0_CH0_CR_CPGC_DPAT_CFG_RELOAD_LFSR_SEED_RATE_OFF           (24)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_RELOAD_LFSR_SEED_RATE_WID           ( 5)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_RELOAD_LFSR_SEED_RATE_MSK           (0x1F000000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_RELOAD_LFSR_SEED_RATE_MIN           (0)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_RELOAD_LFSR_SEED_RATE_MAX           (31) // 0x0000001F
  #define MC0_CH0_CR_CPGC_DPAT_CFG_RELOAD_LFSR_SEED_RATE_DEF           (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_CFG_RELOAD_LFSR_SEED_RATE_HSH           (0x0530C190)

#define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_REG                             (0x0000C194)

  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_ECC_INV_DC_MASK_OFF           ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_ECC_INV_DC_MASK_WID           ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_ECC_INV_DC_MASK_MSK           (0x000000FF)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_ECC_INV_DC_MASK_MIN           (0)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_ECC_INV_DC_MASK_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_ECC_INV_DC_MASK_DEF           (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_ECC_INV_DC_MASK_HSH           (0x0800C194)

  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_RATE_OFF          ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_RATE_WID          ( 4)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_RATE_MSK          (0x00000F00)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_RATE_MIN          (0)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_RATE_MAX          (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_RATE_DEF          (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_RATE_HSH          (0x0410C194)

  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_BYTEGROUP_MAPPING_OFF         (16)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_BYTEGROUP_MAPPING_WID         ( 9)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_BYTEGROUP_MAPPING_MSK         (0x01FF0000)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_BYTEGROUP_MAPPING_MIN         (0)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_BYTEGROUP_MAPPING_MAX         (511) // 0x000001FF
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_BYTEGROUP_MAPPING_DEF         (0x000000AA)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_BYTEGROUP_MAPPING_HSH         (0x0920C194)

  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_POL_OFF                    (29)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_POL_WID                    ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_POL_MSK                    (0x20000000)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_POL_MIN                    (0)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_POL_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_POL_DEF                    (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_POL_HSH                    (0x013AC194)

  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_OR_INV_OFF                 (30)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_OR_INV_WID                 ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_OR_INV_MSK                 (0x40000000)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_OR_INV_MIN                 (0)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_OR_INV_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_OR_INV_DEF                 (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_DC_OR_INV_HSH                 (0x013CC194)

  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_EN_OFF            (31)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_EN_WID            ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_EN_MSK            (0x80000000)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_EN_MIN            (0)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_EN_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_EN_DEF            (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_MASK_ROTATE_EN_HSH            (0x013EC194)

#define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_REG                               (0x0000C198)

  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_RATE_OFF           ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_RATE_WID           ( 6)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_RATE_MSK           (0x0000003F)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_RATE_MIN           (0)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_RATE_MAX           (63) // 0x0000003F
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_RATE_DEF           (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_RATE_HSH           (0x0600C198)

  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_SCALE_OFF          ( 6)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_SCALE_WID          ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_SCALE_MSK          (0x00000040)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_SCALE_MIN          (0)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_SCALE_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_SCALE_DEF          (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_PNTR_INC_SCALE_HSH          (0x010CC198)

  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_STRT_PNTR_OFF               ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_STRT_PNTR_WID               ( 4)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_STRT_PNTR_MSK               (0x00000F00)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_STRT_PNTR_MIN               (0)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_STRT_PNTR_MAX               (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_STRT_PNTR_DEF               (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_STRT_PNTR_HSH               (0x0410C198)

  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_END_PNTR_OFF                (16)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_END_PNTR_WID                ( 4)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_END_PNTR_MSK                (0x000F0000)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_END_PNTR_MIN                (0)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_END_PNTR_MAX                (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_END_PNTR_DEF                (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_BUF_END_PNTR_HSH                (0x0420C198)

  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_WR_BUF_PTR_OFF                  (24)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_WR_BUF_PTR_WID                  ( 4)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_WR_BUF_PTR_MSK                  (0x0F000000)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_WR_BUF_PTR_MIN                  (0)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_WR_BUF_PTR_MAX                  (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_WR_BUF_PTR_DEF                  (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_WR_BUF_PTR_HSH                  (0x0430C198)

  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_RD_BUF_PTR_OFF                  (28)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_RD_BUF_PTR_WID                  ( 4)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_RD_BUF_PTR_MSK                  (0xF0000000)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_RD_BUF_PTR_MIN                  (0)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_RD_BUF_PTR_MAX                  (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_RD_BUF_PTR_DEF                  (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_BUF_CFG_RD_BUF_PTR_HSH                  (0x0438C198)

#define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_REG                           (0x0000C19C)

  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_RATE_OFF       ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_RATE_WID       ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_RATE_MSK       (0x000000FF)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_RATE_MIN       (0)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_RATE_MAX       (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_RATE_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_RATE_HSH       (0x0800C19C)

  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_STRT_PNTR_OFF           ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_STRT_PNTR_WID           ( 5)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_STRT_PNTR_MSK           (0x00001F00)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_STRT_PNTR_MIN           (0)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_STRT_PNTR_MAX           (31) // 0x0000001F
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_STRT_PNTR_DEF           (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_STRT_PNTR_HSH           (0x0510C19C)

  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_ZRO_SHFT_OFF       (14)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_ZRO_SHFT_WID       ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_ZRO_SHFT_MSK       (0x00004000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_ZRO_SHFT_MIN       (0)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_ZRO_SHFT_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_ZRO_SHFT_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_ZRO_SHFT_HSH       (0x011CC19C)

  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_SCALE_OFF      (15)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_SCALE_WID      ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_SCALE_MSK      (0x00008000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_SCALE_MIN      (0)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_SCALE_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_SCALE_DEF      (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_SCALE_HSH      (0x011EC19C)

  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_END_PNTR_OFF            (16)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_END_PNTR_WID            ( 5)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_END_PNTR_MSK            (0x001F0000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_END_PNTR_MIN            (0)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_END_PNTR_MAX            (31) // 0x0000001F
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_END_PNTR_DEF            (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_END_PNTR_HSH            (0x0520C19C)

  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_MODE_OFF       (22)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_MODE_WID       ( 2)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_MODE_MSK       (0x00C00000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_MODE_MIN       (0)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_MODE_MAX       (3) // 0x00000003
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_MODE_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_BUF_PNTR_INC_MODE_HSH       (0x022CC19C)

  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_ZERO_DATA_EN_OFF            (24)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_ZERO_DATA_EN_WID            ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_ZERO_DATA_EN_MSK            (0xFF000000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_ZERO_DATA_EN_MIN            (0)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_ZERO_DATA_EN_MAX            (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_ZERO_DATA_EN_DEF            (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_ZERO_DATA_EN_HSH            (0x0830C19C)

#define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG                             (0x0000C1A0)

  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_MODE_OFF               ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_MODE_WID               ( 2)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_MODE_MSK               (0x00000003)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_MODE_MIN               (0)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_MODE_MAX               (3) // 0x00000003
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_MODE_DEF               (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_MODE_HSH               (0x0200C1A0)

  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_STAGGER_OFF       ( 3)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_STAGGER_WID       ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_STAGGER_MSK       (0x00000008)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_STAGGER_MIN       (0)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_STAGGER_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_STAGGER_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_STAGGER_HSH       (0x0106C1A0)

  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 4)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000070)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0308C1A0)

#define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_1_REG                             (0x0000C1A1)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH0_CR_CPGC_DPAT_USQ_CFG_2_REG                             (0x0000C1A2)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG                              (0x0000C1A8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_PATTERN_BUFFER_OFF             ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_PATTERN_BUFFER_WID             (32)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_PATTERN_BUFFER_MSK             (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_PATTERN_BUFFER_MIN             (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_PATTERN_BUFFER_MAX             (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_PATTERN_BUFFER_DEF             (0xAA55AA55)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_PATTERN_BUFFER_HSH             (0x2000C1A8)

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_1_REG                              (0x0000C1AC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_2_REG                              (0x0000C1B0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG                         (0x0000C1B8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_GALOIS_POLY_OFF           ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_GALOIS_POLY_WID           (32)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_GALOIS_POLY_MSK           (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_GALOIS_POLY_MIN           (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_GALOIS_POLY_MAX           (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_GALOIS_POLY_DEF           (0x80000000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_GALOIS_POLY_HSH           (0x2000C1B8)

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_1_REG                         (0x0000C1BC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_2_REG                         (0x0000C1C0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG                        (0x0000C1C8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR1_POLY_OFF          ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR1_POLY_WID          ( 7)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR1_POLY_MSK          (0x0000007F)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR1_POLY_MIN          (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR1_POLY_MAX          (127) // 0x0000007F
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR1_POLY_DEF          (0x00000001)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR1_POLY_HSH          (0x0700C1C8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR2_POLY_OFF          ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR2_POLY_WID          ( 7)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR2_POLY_MSK          (0x00007F00)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR2_POLY_MIN          (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR2_POLY_MAX          (127) // 0x0000007F
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR2_POLY_DEF          (0x00000001)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR2_POLY_HSH          (0x0710C1C8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR3_POLY_OFF          (16)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR3_POLY_WID          ( 7)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR3_POLY_MSK          (0x007F0000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR3_POLY_MIN          (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR3_POLY_MAX          (127) // 0x0000007F
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR3_POLY_DEF          (0x00000001)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR3_POLY_HSH          (0x0720C1C8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR4_POLY_OFF          (24)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR4_POLY_WID          ( 7)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR4_POLY_MSK          (0x7F000000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR4_POLY_MIN          (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR4_POLY_MAX          (127) // 0x0000007F
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR4_POLY_DEF          (0x00000001)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_STAGR4_POLY_HSH          (0x0730C1C8)

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_1_REG                        (0x0000C1CC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_2_REG                        (0x0000C1D0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG                          (0x0000C1D8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_SEL_OFF                  ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_SEL_WID                  ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_SEL_MSK                  (0x00000001)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_SEL_MIN                  (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_SEL_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_SEL_DEF                  (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_SEL_HSH                  (0x0100C1D8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_FREQ_SWEEP_EN_OFF          ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_FREQ_SWEEP_EN_WID          ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_FREQ_SWEEP_EN_MSK          (0x00000002)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_FREQ_SWEEP_EN_MIN          (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_FREQ_SWEEP_EN_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_FREQ_SWEEP_EN_DEF          (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_FREQ_SWEEP_EN_HSH          (0x0102C1D8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNT_EN_OFF             ( 2)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNT_EN_WID             ( 1)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNT_EN_MSK             (0x00000004)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNT_EN_MIN             (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNT_EN_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNT_EN_DEF             (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNT_EN_HSH             (0x0104C1D8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNTER_HI_OFF           ( 4)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNTER_HI_WID           ( 4)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNTER_HI_MSK           (0x000000F0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNTER_HI_MIN           (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNTER_HI_MAX           (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNTER_HI_DEF           (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_COUNTER_HI_HSH           (0x0408C1D8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_CNT_OFF                  ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_CNT_WID                  ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_CNT_MSK                  (0x0000FF00)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_CNT_MIN                  (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_CNT_MAX                  (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_CNT_DEF                  (0x00000001)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_L_CNT_HSH                  (0x0810C1D8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_M_CNT_OFF                  (16)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_M_CNT_WID                  ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_M_CNT_MSK                  (0x00FF0000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_M_CNT_MIN                  (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_M_CNT_MAX                  (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_M_CNT_DEF                  (0x00000001)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_M_CNT_HSH                  (0x0820C1D8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_N_CNT_OFF                  (24)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_N_CNT_WID                  ( 8)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_N_CNT_MSK                  (0xFF000000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_N_CNT_MIN                  (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_N_CNT_MAX                  (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_N_CNT_DEF                  (0x00000001)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_N_CNT_HSH                  (0x0830C1D8)

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_1_REG                          (0x0000C1DC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_2_REG                          (0x0000C1E0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_REG                        (0x0000C1E8)

  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_DATA_INV_DC_MASK_LO_OFF  ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_DATA_INV_DC_MASK_LO_WID  (32)
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_DATA_INV_DC_MASK_LO_MSK  (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_DATA_INV_DC_MASK_LO_MIN  (0)
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_DATA_INV_DC_MASK_LO_MAX  (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_DATA_INV_DC_MASK_LO_DEF  (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_DATA_INV_DC_MASK_LO_HSH  (0x2000C1E8)

#define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_REG                        (0x0000C1EC)

  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_DATA_INV_DC_MASK_HI_OFF  ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_DATA_INV_DC_MASK_HI_WID  (32)
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_DATA_INV_DC_MASK_HI_MSK  (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_DATA_INV_DC_MASK_HI_MIN  (0)
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_DATA_INV_DC_MASK_HI_MAX  (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_DATA_INV_DC_MASK_HI_DEF  (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_DATA_INV_DC_MASK_HI_HSH  (0x2000C1EC)

#define MC0_CH0_CR_CPGC_DPAT_DRAMDM_REG                                (0x0000C1F0)

  #define MC0_CH0_CR_CPGC_DPAT_DRAMDM_DATA_MASK_LO_OFF                 ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_DRAMDM_DATA_MASK_LO_WID                 (32)
  #define MC0_CH0_CR_CPGC_DPAT_DRAMDM_DATA_MASK_LO_MSK                 (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_DRAMDM_DATA_MASK_LO_MIN                 (0)
  #define MC0_CH0_CR_CPGC_DPAT_DRAMDM_DATA_MASK_LO_MAX                 (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_DRAMDM_DATA_MASK_LO_DEF                 (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_DRAMDM_DATA_MASK_LO_HSH                 (0x2000C1F0)

#define MC0_CH0_CR_CPGC_DPAT_XDRAMDM_REG                               (0x0000C1F4)

  #define MC0_CH0_CR_CPGC_DPAT_XDRAMDM_DATA_MASK_HI_OFF                ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_XDRAMDM_DATA_MASK_HI_WID                (32)
  #define MC0_CH0_CR_CPGC_DPAT_XDRAMDM_DATA_MASK_HI_MSK                (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_XDRAMDM_DATA_MASK_HI_MIN                (0)
  #define MC0_CH0_CR_CPGC_DPAT_XDRAMDM_DATA_MASK_HI_MAX                (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_XDRAMDM_DATA_MASK_HI_DEF                (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_XDRAMDM_DATA_MASK_HI_HSH                (0x2000C1F4)

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG                       (0x0000C1F8)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_UNISEQ_WRSTAT_OFF       ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_UNISEQ_WRSTAT_WID       (32)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_UNISEQ_WRSTAT_MSK       (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_UNISEQ_WRSTAT_MIN       (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_UNISEQ_WRSTAT_MAX       (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_UNISEQ_WRSTAT_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_UNISEQ_WRSTAT_HSH       (0x2000C1F8)

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_1_REG                       (0x0000C1FC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_2_REG                       (0x0000C200)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG                       (0x0000C208)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_UNISEQ_RDSTAT_OFF       ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_UNISEQ_RDSTAT_WID       (32)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_UNISEQ_RDSTAT_MSK       (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_UNISEQ_RDSTAT_MIN       (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_UNISEQ_RDSTAT_MAX       (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_UNISEQ_RDSTAT_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_UNISEQ_RDSTAT_HSH       (0x2000C208)

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_1_REG                       (0x0000C20C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_2_REG                       (0x0000C210)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG                          (0x0000C218)

  #define MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_LMN_WRSTAT_OFF             ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_LMN_WRSTAT_WID             (32)
  #define MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_LMN_WRSTAT_MSK             (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_LMN_WRSTAT_MIN             (0)
  #define MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_LMN_WRSTAT_MAX             (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_LMN_WRSTAT_DEF             (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_LMN_WRSTAT_HSH             (0x2000C218)

#define MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_1_REG                          (0x0000C21C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_2_REG                          (0x0000C220)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG                          (0x0000C228)

  #define MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_LMN_RDSTAT_OFF             ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_LMN_RDSTAT_WID             (32)
  #define MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_LMN_RDSTAT_MSK             (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_LMN_RDSTAT_MIN             (0)
  #define MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_LMN_RDSTAT_MAX             (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_LMN_RDSTAT_DEF             (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_LMN_RDSTAT_HSH             (0x2000C228)

#define MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_1_REG                          (0x0000C22C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_2_REG                          (0x0000C230)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG                       (0x0000C238)

  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_PATTERN_BUFFER_OFF      ( 0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_PATTERN_BUFFER_WID      (32)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_PATTERN_BUFFER_MSK      (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_PATTERN_BUFFER_MIN      (0)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_PATTERN_BUFFER_MAX      (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_PATTERN_BUFFER_DEF      (0x00000000)
  #define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_PATTERN_BUFFER_HSH      (0x2000C238)

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_1_REG                       (0x0000C23C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_2_REG                       (0x0000C240)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSAVE_0_REG                       (0x0000C248)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSAVE_1_REG                       (0x0000C24C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSAVE_2_REG                       (0x0000C250)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH0_CR_CPGC_ERR_LNEN_LO_REG                                (0x0000C258)

  #define MC0_CH0_CR_CPGC_ERR_LNEN_LO_DATA_ERRCHK_MASK_LO_OFF          ( 0)
  #define MC0_CH0_CR_CPGC_ERR_LNEN_LO_DATA_ERRCHK_MASK_LO_WID          (32)
  #define MC0_CH0_CR_CPGC_ERR_LNEN_LO_DATA_ERRCHK_MASK_LO_MSK          (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_ERR_LNEN_LO_DATA_ERRCHK_MASK_LO_MIN          (0)
  #define MC0_CH0_CR_CPGC_ERR_LNEN_LO_DATA_ERRCHK_MASK_LO_MAX          (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_ERR_LNEN_LO_DATA_ERRCHK_MASK_LO_DEF          (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_LNEN_LO_DATA_ERRCHK_MASK_LO_HSH          (0x2000C258)

#define MC0_CH0_CR_CPGC_ERR_LNEN_HI_REG                                (0x0000C25C)

  #define MC0_CH0_CR_CPGC_ERR_LNEN_HI_DATA_ERRCHK_MASK_HI_OFF          ( 0)
  #define MC0_CH0_CR_CPGC_ERR_LNEN_HI_DATA_ERRCHK_MASK_HI_WID          (32)
  #define MC0_CH0_CR_CPGC_ERR_LNEN_HI_DATA_ERRCHK_MASK_HI_MSK          (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_ERR_LNEN_HI_DATA_ERRCHK_MASK_HI_MIN          (0)
  #define MC0_CH0_CR_CPGC_ERR_LNEN_HI_DATA_ERRCHK_MASK_HI_MAX          (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_ERR_LNEN_HI_DATA_ERRCHK_MASK_HI_DEF          (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_LNEN_HI_DATA_ERRCHK_MASK_HI_HSH          (0x2000C25C)

#define MC0_CH0_CR_CPGC_ERR_XLNEN_REG                                  (0x0000C260)

  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_OFF                ( 0)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_WID                ( 8)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_MSK                (0x000000FF)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_MIN                (0)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_MAX                (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_DEF                (0x000000FF)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_HSH                (0x0800C260)

  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_OFF               (16)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_WID               ( 4)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_MSK               (0x000F0000)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_MIN               (0)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_MAX               (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_DEF               (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_HSH               (0x0420C260)

#define MC0_CH0_CR_CPGC_ERR_XLNEN_P0_REG                               (0x0000C260)

  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_P0_OFF             ( 0)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_P0_WID             ( 8)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_P0_MSK             (0x000000FF)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_P0_MIN             (0)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_P0_MAX             (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_P0_DEF             (0x000000FF)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_ECC_ERRCHK_MASK_P0_HSH             (0x0800C260)

  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_P0_OFF            (16)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_P0_WID            ( 8)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_P0_MSK            (0x00FF0000)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_P0_MIN            (0)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_P0_MAX            (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_XLNEN_RANK_ERRCHK_MASK_P0_HSH            (0x0820C260)

#define MC0_CH0_CR_CPGC_ERR_CTL_REG                                    (0x0000C264)

  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_N_OFF                        ( 0)
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_N_WID                        ( 6)
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_N_MSK                        (0x0000003F)
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_N_MIN                        (0)
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_N_MAX                        (63) // 0x0000003F
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_N_DEF                        (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_N_HSH                        (0x0600C264)

  #define MC0_CH0_CR_CPGC_ERR_CTL_BE_TRAIN_ERR_EN_OFF                  ( 8)
  #define MC0_CH0_CR_CPGC_ERR_CTL_BE_TRAIN_ERR_EN_WID                  ( 1)
  #define MC0_CH0_CR_CPGC_ERR_CTL_BE_TRAIN_ERR_EN_MSK                  (0x00000100)
  #define MC0_CH0_CR_CPGC_ERR_CTL_BE_TRAIN_ERR_EN_MIN                  (0)
  #define MC0_CH0_CR_CPGC_ERR_CTL_BE_TRAIN_ERR_EN_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_ERR_CTL_BE_TRAIN_ERR_EN_DEF                  (0x00000001)
  #define MC0_CH0_CR_CPGC_ERR_CTL_BE_TRAIN_ERR_EN_HSH                  (0x0110C264)

  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_ERROR_CTL_OFF                (12)
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_ERROR_CTL_WID                ( 2)
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_ERROR_CTL_MSK                (0x00003000)
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_ERROR_CTL_MIN                (0)
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_ERROR_CTL_MAX                (3) // 0x00000003
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_ERROR_CTL_DEF                (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_CTL_STOP_ON_ERROR_CTL_HSH                (0x0218C264)

  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CHUNK_OFF                (16)
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CHUNK_WID                ( 8)
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CHUNK_MSK                (0x00FF0000)
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CHUNK_MIN                (0)
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CHUNK_MAX                (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CHUNK_DEF                (0x000000FF)
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CHUNK_HSH                (0x0820C264)

  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CACHELINE_OFF            (24)
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CACHELINE_WID            ( 8)
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CACHELINE_MSK            (0xFF000000)
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CACHELINE_MIN            (0)
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CACHELINE_MAX            (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CACHELINE_DEF            (0x000000FF)
  #define MC0_CH0_CR_CPGC_ERR_CTL_ERRCHK_MASK_CACHELINE_HSH            (0x0830C264)

#define MC0_CH0_CR_CPGC_ERR_STAT03_REG                                 (0x0000C268)

  #define MC0_CH0_CR_CPGC_ERR_STAT03_LANE_ERR_STAT_LO_OFF              ( 0)
  #define MC0_CH0_CR_CPGC_ERR_STAT03_LANE_ERR_STAT_LO_WID              (32)
  #define MC0_CH0_CR_CPGC_ERR_STAT03_LANE_ERR_STAT_LO_MSK              (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_ERR_STAT03_LANE_ERR_STAT_LO_MIN              (0)
  #define MC0_CH0_CR_CPGC_ERR_STAT03_LANE_ERR_STAT_LO_MAX              (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_ERR_STAT03_LANE_ERR_STAT_LO_DEF              (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_STAT03_LANE_ERR_STAT_LO_HSH              (0x2000C268)

#define MC0_CH0_CR_CPGC_ERR_STAT47_REG                                 (0x0000C26C)

  #define MC0_CH0_CR_CPGC_ERR_STAT47_LANE_ERR_STAT_HI_OFF              ( 0)
  #define MC0_CH0_CR_CPGC_ERR_STAT47_LANE_ERR_STAT_HI_WID              (32)
  #define MC0_CH0_CR_CPGC_ERR_STAT47_LANE_ERR_STAT_HI_MSK              (0xFFFFFFFF)
  #define MC0_CH0_CR_CPGC_ERR_STAT47_LANE_ERR_STAT_HI_MIN              (0)
  #define MC0_CH0_CR_CPGC_ERR_STAT47_LANE_ERR_STAT_HI_MAX              (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CPGC_ERR_STAT47_LANE_ERR_STAT_HI_DEF              (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_STAT47_LANE_ERR_STAT_HI_HSH              (0x2000C26C)

#define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG                     (0x0000C270)

  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_OFF ( 0)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_WID ( 8)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_MSK (0x000000FF)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_MIN (0)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_DEF (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_HSH (0x0800C270)

  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_OFF    ( 8)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_WID    ( 8)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_MSK    (0x0000FF00)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_MIN    (0)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_MAX    (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_DEF    (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_HSH    (0x0810C270)

  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_OFF     (16)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_WID     ( 4)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_MSK     (0x000F0000)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_MIN     (0)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_MAX     (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_DEF     (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_HSH     (0x0420C270)

#define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_P0_REG                  (0x0000C270)

  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_P0_OFF ( 0)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_P0_WID ( 8)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_P0_MSK (0x000000FF)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_P0_MIN (0)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_P0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_P0_DEF (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_ECC_LANE_ERR_STAT_P0_HSH (0x0800C270)

  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_P0_OFF ( 8)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_P0_WID ( 8)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_P0_MSK (0x0000FF00)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_P0_MIN (0)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_P0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_P0_DEF (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_CHUNK_ERR_STAT_P0_HSH (0x0810C270)

  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_P0_OFF  (16)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_P0_WID  ( 8)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_P0_MSK  (0x00FF0000)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_P0_MIN  (0)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_P0_MAX  (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_RANK_ERR_STAT_P0_HSH  (0x0820C270)

#define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG                      (0x0000C274)

  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_BYTEGRP_ERR_STAT_OFF   ( 0)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_BYTEGRP_ERR_STAT_WID   ( 8)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_BYTEGRP_ERR_STAT_MSK   (0x000000FF)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_BYTEGRP_ERR_STAT_MIN   (0)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_BYTEGRP_ERR_STAT_MAX   (255) // 0x000000FF
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_BYTEGRP_ERR_STAT_DEF   (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_BYTEGRP_ERR_STAT_HSH   (0x0800C274)

  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_ECCGRP_ERR_STAT_OFF    ( 8)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_ECCGRP_ERR_STAT_WID    ( 1)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_ECCGRP_ERR_STAT_MSK    (0x00000100)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_ECCGRP_ERR_STAT_MIN    (0)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_ECCGRP_ERR_STAT_MAX    (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_ECCGRP_ERR_STAT_DEF    (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_ECCGRP_ERR_STAT_HSH    (0x0110C274)

  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_RD_CHUNK_NUM_STAT_OFF  (20)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_RD_CHUNK_NUM_STAT_WID  ( 3)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_RD_CHUNK_NUM_STAT_MSK  (0x00700000)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_RD_CHUNK_NUM_STAT_MIN  (0)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_RD_CHUNK_NUM_STAT_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_RD_CHUNK_NUM_STAT_DEF  (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_RD_CHUNK_NUM_STAT_HSH  (0x0328C274)

  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_Nth_ERROR_OFF          (24)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_Nth_ERROR_WID          ( 6)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_Nth_ERROR_MSK          (0x3F000000)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_Nth_ERROR_MIN          (0)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_Nth_ERROR_MAX          (63) // 0x0000003F
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_Nth_ERROR_DEF          (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_Nth_ERROR_HSH          (0x0630C274)

#define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG                              (0x0000C278)

  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_POINTER_OFF            ( 0)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_POINTER_WID            ( 7)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_POINTER_MSK            (0x0000007F)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_POINTER_MIN            (0)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_POINTER_MAX            (127) // 0x0000007F
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_POINTER_DEF            (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_POINTER_HSH            (0x0700C278)

  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SEL_OFF        ( 8)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SEL_WID        ( 2)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SEL_MSK        (0x00000300)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SEL_MIN        (0)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SEL_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SEL_DEF        (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SEL_HSH        (0x0210C278)

  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_UI_OFF         (10)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_UI_WID         ( 2)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_UI_MSK         (0x00000C00)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_UI_MIN         (0)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_UI_MAX         (3) // 0x00000003
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_UI_DEF         (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_UI_HSH         (0x0214C278)

  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SCOPE_OFF      (12)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SCOPE_WID      ( 1)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SCOPE_MSK      (0x00001000)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SCOPE_MIN      (0)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SCOPE_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SCOPE_DEF      (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_COUNTER_CONTROL_SCOPE_HSH      (0x0118C278)

#define MC0_CH0_CR_CPGC_ERR_CNTRCTL_1_REG                              (0x0000C27C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTRCTL_2_REG                              (0x0000C280)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTRCTL_3_REG                              (0x0000C284)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTRCTL_4_REG                              (0x0000C288)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTRCTL_5_REG                              (0x0000C28C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTRCTL_6_REG                              (0x0000C290)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTRCTL_7_REG                              (0x0000C294)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTRCTL_8_REG                              (0x0000C298)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTR_0_REG                                 (0x0000C2A0)

  #define MC0_CH0_CR_CPGC_ERR_CNTR_0_ERROR_COUNTER_OFF                 ( 0)
  #define MC0_CH0_CR_CPGC_ERR_CNTR_0_ERROR_COUNTER_WID                 (23)
  #define MC0_CH0_CR_CPGC_ERR_CNTR_0_ERROR_COUNTER_MSK                 (0x007FFFFF)
  #define MC0_CH0_CR_CPGC_ERR_CNTR_0_ERROR_COUNTER_MIN                 (0)
  #define MC0_CH0_CR_CPGC_ERR_CNTR_0_ERROR_COUNTER_MAX                 (8388607) // 0x007FFFFF
  #define MC0_CH0_CR_CPGC_ERR_CNTR_0_ERROR_COUNTER_DEF                 (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_CNTR_0_ERROR_COUNTER_HSH                 (0x1700C2A0)

#define MC0_CH0_CR_CPGC_ERR_CNTR_1_REG                                 (0x0000C2A4)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTR_2_REG                                 (0x0000C2A8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTR_3_REG                                 (0x0000C2AC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTR_4_REG                                 (0x0000C2B0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTR_5_REG                                 (0x0000C2B4)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTR_6_REG                                 (0x0000C2B8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTR_7_REG                                 (0x0000C2BC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTR_8_REG                                 (0x0000C2C0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH0_CR_CPGC_ERR_CNTR_OV_REG                                (0x0000C2C8)

  #define MC0_CH0_CR_CPGC_ERR_CNTR_OV_ERROR_COUNTER_OVERFLOW_OFF       ( 0)
  #define MC0_CH0_CR_CPGC_ERR_CNTR_OV_ERROR_COUNTER_OVERFLOW_WID       ( 9)
  #define MC0_CH0_CR_CPGC_ERR_CNTR_OV_ERROR_COUNTER_OVERFLOW_MSK       (0x000001FF)
  #define MC0_CH0_CR_CPGC_ERR_CNTR_OV_ERROR_COUNTER_OVERFLOW_MIN       (0)
  #define MC0_CH0_CR_CPGC_ERR_CNTR_OV_ERROR_COUNTER_OVERFLOW_MAX       (511) // 0x000001FF
  #define MC0_CH0_CR_CPGC_ERR_CNTR_OV_ERROR_COUNTER_OVERFLOW_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_CNTR_OV_ERROR_COUNTER_OVERFLOW_HSH       (0x0900C2C8)

#define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_REG                          (0x0000C2CC)

  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_OFF           ( 0)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_WID           (20)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_MSK           (0x000FFFFF)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_MIN           (0)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_MAX           (1048575) // 0x000FFFFF
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_DEF           (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_HSH           (0x1400C2CC)

  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_OFF       (20)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_WID       ( 4)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_MSK       (0x00F00000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_MIN       (0)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_MAX       (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_DEF       (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_HSH       (0x0428C2CC)

  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_OFF    (24)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_WID    ( 4)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_MSK    (0x0F000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_MIN    (0)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_MAX    (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_DEF    (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_HSH    (0x0430C2CC)

  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_INTERNAL_ERR_OFF (28)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_INTERNAL_ERR_WID ( 4)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_INTERNAL_ERR_MSK (0xF0000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_INTERNAL_ERR_MIN (0)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_INTERNAL_ERR_MAX (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_INTERNAL_ERR_DEF (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_INTERNAL_ERR_HSH (0x0438C2CC)

#define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_A0_REG                       (0x0000C2CC)

  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_A0_OFF        ( 0)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_A0_WID        (20)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_A0_MSK        (0x000FFFFF)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_A0_MIN        (0)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_A0_MAX        (1048575) // 0x000FFFFF
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_A0_DEF        (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ERROR_STATUS_A0_HSH        (0x1400C2CC)

  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_A0_OFF    (20)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_A0_WID    ( 4)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_A0_MSK    (0x00F00000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_A0_MIN    (0)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_A0_MAX    (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_A0_DEF    (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_TEST_IN_PROGRESS_A0_HSH    (0x0428C2CC)

  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_A0_OFF (24)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_A0_WID ( 4)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_A0_MSK (0x0F000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_A0_MIN (0)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_A0_MAX (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_A0_DEF (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_ALGO_WAIT_TEST_DONE_A0_HSH (0x0430C2CC)

  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_A0_OFF      (28)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_A0_WID      ( 4)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_A0_MSK      (0xF0000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_A0_MIN      (0)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_A0_MAX      (15) // 0x0000000F
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_A0_DEF      (0x00000000)
  #define MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_EVENT_NOT_SEEN_A0_HSH      (0x0438C2CC)

#define MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG                                (0x0000C2D0)

  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE0_OFF                   ( 0)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE0_WID                   ( 8)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE0_MSK                   (0x000000FF)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE0_MIN                   (0)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE0_MAX                   (255) // 0x000000FF
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE0_DEF                   (0x000000AA)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE0_HSH                   (0x0800C2D0)

  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE1_OFF                   ( 8)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE1_WID                   ( 8)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE1_MSK                   (0x0000FF00)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE1_MIN                   (0)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE1_MAX                   (255) // 0x000000FF
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE1_DEF                   (0x000000AA)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE1_HSH                   (0x0810C2D0)

  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE2_OFF                   (16)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE2_WID                   ( 8)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE2_MSK                   (0x00FF0000)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE2_MIN                   (0)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE2_MAX                   (255) // 0x000000FF
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE2_DEF                   (0x000000AA)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE2_HSH                   (0x0820C2D0)

  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE3_OFF                   (24)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE3_WID                   ( 8)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE3_MSK                   (0xFF000000)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE3_MIN                   (0)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE3_MAX                   (255) // 0x000000FF
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE3_DEF                   (0x000000AA)
  #define MC0_BUF0_CPGC_DPAT_EXTBUF_0_DATA_LINE3_HSH                   (0x0830C2D0)

#define MC0_BUF0_CPGC_DPAT_EXTBUF_1_REG                                (0x0000C2D4)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_2_REG                                (0x0000C2D8)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_3_REG                                (0x0000C2DC)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_4_REG                                (0x0000C2E0)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_5_REG                                (0x0000C2E4)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_6_REG                                (0x0000C2E8)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_7_REG                                (0x0000C2EC)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_8_REG                                (0x0000C2F0)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_9_REG                                (0x0000C2F4)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_10_REG                               (0x0000C2F8)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_11_REG                               (0x0000C2FC)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_12_REG                               (0x0000C300)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_13_REG                               (0x0000C304)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_14_REG                               (0x0000C308)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_DPAT_EXTBUF_15_REG                               (0x0000C30C)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF0_CPGC_B_DUMMY_REG                                      (0x0000C310)

  #define MC0_BUF0_CPGC_B_DUMMY_DUMMY_OFF                              ( 0)
  #define MC0_BUF0_CPGC_B_DUMMY_DUMMY_WID                              (64)
  #define MC0_BUF0_CPGC_B_DUMMY_DUMMY_MSK                              (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_BUF0_CPGC_B_DUMMY_DUMMY_MIN                              (0)
  #define MC0_BUF0_CPGC_B_DUMMY_DUMMY_MAX                              (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_BUF0_CPGC_B_DUMMY_DUMMY_DEF                              (0x00000000)
  #define MC0_BUF0_CPGC_B_DUMMY_DUMMY_HSH                              (0x4000C310)

#define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG                    (0x0000C320)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK0_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK0_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK0_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK0_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK0_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK0_MAPPING_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK0_MAPPING_HSH (0x0500C320)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK1_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK1_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK1_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK1_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK1_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK1_MAPPING_DEF (0x00000001)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK1_MAPPING_HSH (0x050AC320)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK2_MAPPING_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK2_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK2_MAPPING_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK2_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK2_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK2_MAPPING_DEF (0x00000002)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK2_MAPPING_HSH (0x0514C320)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK3_MAPPING_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK3_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK3_MAPPING_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK3_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK3_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK3_MAPPING_DEF (0x00000003)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK3_MAPPING_HSH (0x051EC320)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK4_MAPPING_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK4_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK4_MAPPING_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK4_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK4_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK4_MAPPING_DEF (0x00000004)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK4_MAPPING_HSH (0x0528C320)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK5_MAPPING_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK5_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK5_MAPPING_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK5_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK5_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK5_MAPPING_DEF (0x00000005)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK5_MAPPING_HSH (0x0532C320)

#define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_REG                    (0x0000C324)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK6_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK6_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK6_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK6_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK6_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK6_MAPPING_DEF (0x00000006)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK6_MAPPING_HSH (0x0500C324)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK7_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK7_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK7_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK7_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK7_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK7_MAPPING_DEF (0x00000007)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK7_MAPPING_HSH (0x050AC324)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK8_MAPPING_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK8_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK8_MAPPING_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK8_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK8_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK8_MAPPING_DEF (0x00000008)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK8_MAPPING_HSH (0x0514C324)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK9_MAPPING_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK9_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK9_MAPPING_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK9_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK9_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK9_MAPPING_DEF (0x00000009)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK9_MAPPING_HSH (0x051EC324)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK10_MAPPING_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK10_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK10_MAPPING_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK10_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK10_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK10_MAPPING_DEF (0x0000000A)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK10_MAPPING_HSH (0x0528C324)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK11_MAPPING_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK11_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK11_MAPPING_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK11_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK11_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK11_MAPPING_DEF (0x0000000B)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_L2P_RANK11_MAPPING_HSH (0x0532C324)

#define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_REG                    (0x0000C328)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK12_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK12_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK12_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK12_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK12_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK12_MAPPING_DEF (0x0000000C)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK12_MAPPING_HSH (0x0500C328)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK13_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK13_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK13_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK13_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK13_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK13_MAPPING_DEF (0x0000000D)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK13_MAPPING_HSH (0x050AC328)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK14_MAPPING_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK14_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK14_MAPPING_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK14_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK14_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK14_MAPPING_DEF (0x0000000E)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK14_MAPPING_HSH (0x0514C328)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK15_MAPPING_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK15_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK15_MAPPING_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK15_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK15_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK15_MAPPING_DEF (0x0000000F)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK15_MAPPING_HSH (0x051EC328)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK16_MAPPING_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK16_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK16_MAPPING_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK16_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK16_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK16_MAPPING_DEF (0x00000010)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK16_MAPPING_HSH (0x0528C328)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK17_MAPPING_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK17_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK17_MAPPING_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK17_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK17_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK17_MAPPING_DEF (0x00000011)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_L2P_RANK17_MAPPING_HSH (0x0532C328)

#define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_REG                    (0x0000C32C)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK18_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK18_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK18_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK18_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK18_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK18_MAPPING_DEF (0x00000012)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK18_MAPPING_HSH (0x0500C32C)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK19_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK19_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK19_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK19_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK19_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK19_MAPPING_DEF (0x00000013)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK19_MAPPING_HSH (0x050AC32C)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK20_MAPPING_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK20_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK20_MAPPING_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK20_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK20_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK20_MAPPING_DEF (0x00000014)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK20_MAPPING_HSH (0x0514C32C)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK21_MAPPING_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK21_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK21_MAPPING_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK21_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK21_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK21_MAPPING_DEF (0x00000015)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK21_MAPPING_HSH (0x051EC32C)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK22_MAPPING_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK22_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK22_MAPPING_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK22_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK22_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK22_MAPPING_DEF (0x00000016)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK22_MAPPING_HSH (0x0528C32C)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK23_MAPPING_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK23_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK23_MAPPING_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK23_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK23_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK23_MAPPING_DEF (0x00000017)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_L2P_RANK23_MAPPING_HSH (0x0532C32C)

#define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_REG                    (0x0000C330)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK24_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK24_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK24_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK24_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK24_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK24_MAPPING_DEF (0x00000018)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK24_MAPPING_HSH (0x0500C330)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK25_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK25_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK25_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK25_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK25_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK25_MAPPING_DEF (0x00000019)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK25_MAPPING_HSH (0x050AC330)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK26_MAPPING_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK26_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK26_MAPPING_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK26_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK26_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK26_MAPPING_DEF (0x0000001A)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK26_MAPPING_HSH (0x0514C330)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK27_MAPPING_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK27_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK27_MAPPING_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK27_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK27_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK27_MAPPING_DEF (0x0000001B)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK27_MAPPING_HSH (0x051EC330)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK28_MAPPING_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK28_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK28_MAPPING_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK28_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK28_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK28_MAPPING_DEF (0x0000001C)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK28_MAPPING_HSH (0x0528C330)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK29_MAPPING_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK29_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK29_MAPPING_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK29_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK29_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK29_MAPPING_DEF (0x0000001D)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_L2P_RANK29_MAPPING_HSH (0x0532C330)

#define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_REG                    (0x0000C334)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK30_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK30_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK30_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK30_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK30_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK30_MAPPING_DEF (0x0000001E)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK30_MAPPING_HSH (0x0500C334)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK31_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK31_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK31_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK31_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK31_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK31_MAPPING_DEF (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_L2P_RANK31_MAPPING_HSH (0x050AC334)

#define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_REG                    (0x0000C338)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK0_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK0_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK0_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK0_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK0_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK0_MAPPING_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK0_MAPPING_HSH (0x0500C338)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK1_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK1_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK1_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK1_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK1_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK1_MAPPING_DEF (0x00000001)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK1_MAPPING_HSH (0x050AC338)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK2_MAPPING_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK2_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK2_MAPPING_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK2_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK2_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK2_MAPPING_DEF (0x00000002)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK2_MAPPING_HSH (0x0514C338)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK3_MAPPING_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK3_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK3_MAPPING_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK3_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK3_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK3_MAPPING_DEF (0x00000003)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK3_MAPPING_HSH (0x051EC338)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK4_MAPPING_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK4_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK4_MAPPING_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK4_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK4_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK4_MAPPING_DEF (0x00000004)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK4_MAPPING_HSH (0x0528C338)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK5_MAPPING_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK5_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK5_MAPPING_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK5_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK5_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK5_MAPPING_DEF (0x00000005)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_L2P_BANK5_MAPPING_HSH (0x0532C338)

#define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_REG                    (0x0000C33C)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK6_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK6_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK6_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK6_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK6_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK6_MAPPING_DEF (0x00000006)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK6_MAPPING_HSH (0x0500C33C)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK7_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK7_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK7_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK7_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK7_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK7_MAPPING_DEF (0x00000007)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK7_MAPPING_HSH (0x050AC33C)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK8_MAPPING_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK8_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK8_MAPPING_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK8_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK8_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK8_MAPPING_DEF (0x00000008)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK8_MAPPING_HSH (0x0514C33C)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK9_MAPPING_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK9_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK9_MAPPING_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK9_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK9_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK9_MAPPING_DEF (0x00000009)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK9_MAPPING_HSH (0x051EC33C)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK10_MAPPING_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK10_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK10_MAPPING_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK10_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK10_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK10_MAPPING_DEF (0x0000000A)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK10_MAPPING_HSH (0x0528C33C)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK11_MAPPING_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK11_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK11_MAPPING_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK11_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK11_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK11_MAPPING_DEF (0x0000000B)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_L2P_BANK11_MAPPING_HSH (0x0532C33C)

#define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_REG                    (0x0000C340)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK12_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK12_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK12_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK12_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK12_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK12_MAPPING_DEF (0x0000000C)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK12_MAPPING_HSH (0x0500C340)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK13_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK13_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK13_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK13_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK13_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK13_MAPPING_DEF (0x0000000D)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK13_MAPPING_HSH (0x050AC340)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK14_MAPPING_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK14_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK14_MAPPING_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK14_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK14_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK14_MAPPING_DEF (0x0000000E)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK14_MAPPING_HSH (0x0514C340)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK15_MAPPING_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK15_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK15_MAPPING_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK15_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK15_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK15_MAPPING_DEF (0x0000000F)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK15_MAPPING_HSH (0x051EC340)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK16_MAPPING_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK16_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK16_MAPPING_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK16_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK16_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK16_MAPPING_DEF (0x00000010)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK16_MAPPING_HSH (0x0528C340)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK17_MAPPING_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK17_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK17_MAPPING_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK17_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK17_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK17_MAPPING_DEF (0x00000011)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_L2P_BANK17_MAPPING_HSH (0x0532C340)

#define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_REG                    (0x0000C344)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK18_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK18_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK18_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK18_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK18_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK18_MAPPING_DEF (0x00000012)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK18_MAPPING_HSH (0x0500C344)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK19_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK19_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK19_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK19_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK19_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK19_MAPPING_DEF (0x00000013)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK19_MAPPING_HSH (0x050AC344)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK20_MAPPING_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK20_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK20_MAPPING_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK20_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK20_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK20_MAPPING_DEF (0x00000014)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK20_MAPPING_HSH (0x0514C344)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK21_MAPPING_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK21_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK21_MAPPING_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK21_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK21_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK21_MAPPING_DEF (0x00000015)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK21_MAPPING_HSH (0x051EC344)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK22_MAPPING_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK22_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK22_MAPPING_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK22_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK22_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK22_MAPPING_DEF (0x00000016)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK22_MAPPING_HSH (0x0528C344)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK23_MAPPING_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK23_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK23_MAPPING_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK23_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK23_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK23_MAPPING_DEF (0x00000017)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_L2P_BANK23_MAPPING_HSH (0x0532C344)

#define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_REG                    (0x0000C348)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK24_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK24_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK24_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK24_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK24_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK24_MAPPING_DEF (0x00000018)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK24_MAPPING_HSH (0x0500C348)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK25_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK25_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK25_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK25_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK25_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK25_MAPPING_DEF (0x00000019)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK25_MAPPING_HSH (0x050AC348)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK26_MAPPING_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK26_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK26_MAPPING_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK26_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK26_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK26_MAPPING_DEF (0x0000001A)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK26_MAPPING_HSH (0x0514C348)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK27_MAPPING_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK27_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK27_MAPPING_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK27_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK27_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK27_MAPPING_DEF (0x0000001B)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK27_MAPPING_HSH (0x051EC348)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK28_MAPPING_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK28_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK28_MAPPING_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK28_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK28_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK28_MAPPING_DEF (0x0000001C)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK28_MAPPING_HSH (0x0528C348)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK29_MAPPING_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK29_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK29_MAPPING_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK29_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK29_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK29_MAPPING_DEF (0x0000001D)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_L2P_BANK29_MAPPING_HSH (0x0532C348)

#define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_REG                    (0x0000C34C)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK30_MAPPING_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK30_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK30_MAPPING_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK30_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK30_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK30_MAPPING_DEF (0x0000001E)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK30_MAPPING_HSH (0x0500C34C)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK31_MAPPING_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK31_MAPPING_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK31_MAPPING_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK31_MAPPING_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK31_MAPPING_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK31_MAPPING_DEF (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_L2P_BANK31_MAPPING_HSH (0x050AC34C)

#define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_REG                     (0x0000C350)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK0_SWIZZLE_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK0_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK0_SWIZZLE_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK0_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK0_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK0_SWIZZLE_DEF (0x00000018)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK0_SWIZZLE_HSH (0x0500C350)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK1_SWIZZLE_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK1_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK1_SWIZZLE_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK1_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK1_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK1_SWIZZLE_DEF (0x00000019)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK1_SWIZZLE_HSH (0x050AC350)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK2_SWIZZLE_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK2_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK2_SWIZZLE_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK2_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK2_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK2_SWIZZLE_DEF (0x0000001A)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK2_SWIZZLE_HSH (0x0514C350)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK3_SWIZZLE_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK3_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK3_SWIZZLE_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK3_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK3_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK3_SWIZZLE_DEF (0x0000001B)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK3_SWIZZLE_HSH (0x051EC350)

  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK4_SWIZZLE_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK4_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK4_SWIZZLE_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK4_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK4_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK4_SWIZZLE_DEF (0x0000001C)
  #define MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_L2P_RANK4_SWIZZLE_HSH (0x0528C350)

#define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_REG                     (0x0000C354)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK0_SWIZZLE_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK0_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK0_SWIZZLE_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK0_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK0_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK0_SWIZZLE_DEF (0x00000018)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK0_SWIZZLE_HSH (0x0500C354)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK1_SWIZZLE_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK1_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK1_SWIZZLE_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK1_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK1_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK1_SWIZZLE_DEF (0x00000019)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK1_SWIZZLE_HSH (0x050AC354)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK2_SWIZZLE_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK2_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK2_SWIZZLE_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK2_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK2_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK2_SWIZZLE_DEF (0x0000001A)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK2_SWIZZLE_HSH (0x0514C354)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK3_SWIZZLE_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK3_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK3_SWIZZLE_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK3_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK3_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK3_SWIZZLE_DEF (0x0000001B)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK3_SWIZZLE_HSH (0x051EC354)

  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK4_SWIZZLE_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK4_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK4_SWIZZLE_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK4_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK4_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK4_SWIZZLE_DEF (0x0000001C)
  #define MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_L2P_BANK4_SWIZZLE_HSH (0x0528C354)

#define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_REG                    (0x0000C358)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW0_SWIZZLE_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW0_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW0_SWIZZLE_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW0_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW0_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW0_SWIZZLE_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW0_SWIZZLE_HSH (0x0500C358)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW1_SWIZZLE_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW1_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW1_SWIZZLE_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW1_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW1_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW1_SWIZZLE_DEF (0x00000001)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW1_SWIZZLE_HSH (0x050AC358)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW2_SWIZZLE_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW2_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW2_SWIZZLE_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW2_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW2_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW2_SWIZZLE_DEF (0x00000002)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW2_SWIZZLE_HSH (0x0514C358)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW3_SWIZZLE_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW3_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW3_SWIZZLE_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW3_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW3_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW3_SWIZZLE_DEF (0x00000003)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW3_SWIZZLE_HSH (0x051EC358)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW4_SWIZZLE_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW4_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW4_SWIZZLE_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW4_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW4_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW4_SWIZZLE_DEF (0x00000004)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW4_SWIZZLE_HSH (0x0528C358)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW5_SWIZZLE_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW5_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW5_SWIZZLE_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW5_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW5_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW5_SWIZZLE_DEF (0x00000005)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_L2P_ROW5_SWIZZLE_HSH (0x0532C358)

#define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_REG                    (0x0000C35C)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW6_SWIZZLE_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW6_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW6_SWIZZLE_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW6_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW6_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW6_SWIZZLE_DEF (0x00000006)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW6_SWIZZLE_HSH (0x0500C35C)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW7_SWIZZLE_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW7_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW7_SWIZZLE_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW7_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW7_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW7_SWIZZLE_DEF (0x00000007)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW7_SWIZZLE_HSH (0x050AC35C)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW8_SWIZZLE_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW8_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW8_SWIZZLE_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW8_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW8_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW8_SWIZZLE_DEF (0x00000008)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW8_SWIZZLE_HSH (0x0514C35C)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW9_SWIZZLE_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW9_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW9_SWIZZLE_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW9_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW9_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW9_SWIZZLE_DEF (0x00000009)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW9_SWIZZLE_HSH (0x051EC35C)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW10_SWIZZLE_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW10_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW10_SWIZZLE_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW10_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW10_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW10_SWIZZLE_DEF (0x0000000A)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW10_SWIZZLE_HSH (0x0528C35C)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW11_SWIZZLE_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW11_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW11_SWIZZLE_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW11_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW11_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW11_SWIZZLE_DEF (0x0000000B)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_L2P_ROW11_SWIZZLE_HSH (0x0532C35C)

#define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_REG                    (0x0000C360)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW12_SWIZZLE_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW12_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW12_SWIZZLE_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW12_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW12_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW12_SWIZZLE_DEF (0x0000000C)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW12_SWIZZLE_HSH (0x0500C360)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW13_SWIZZLE_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW13_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW13_SWIZZLE_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW13_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW13_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW13_SWIZZLE_DEF (0x0000000D)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW13_SWIZZLE_HSH (0x050AC360)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW14_SWIZZLE_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW14_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW14_SWIZZLE_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW14_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW14_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW14_SWIZZLE_DEF (0x0000000E)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW14_SWIZZLE_HSH (0x0514C360)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW15_SWIZZLE_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW15_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW15_SWIZZLE_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW15_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW15_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW15_SWIZZLE_DEF (0x0000000F)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW15_SWIZZLE_HSH (0x051EC360)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW16_SWIZZLE_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW16_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW16_SWIZZLE_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW16_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW16_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW16_SWIZZLE_DEF (0x00000010)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW16_SWIZZLE_HSH (0x0528C360)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW17_SWIZZLE_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW17_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW17_SWIZZLE_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW17_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW17_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW17_SWIZZLE_DEF (0x00000011)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_L2P_ROW17_SWIZZLE_HSH (0x0532C360)

#define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_REG                    (0x0000C364)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW0_XOR_SWIZZLE_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW0_XOR_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW0_XOR_SWIZZLE_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW0_XOR_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW0_XOR_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW0_XOR_SWIZZLE_DEF (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW0_XOR_SWIZZLE_HSH (0x0500C364)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW1_XOR_SWIZZLE_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW1_XOR_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW1_XOR_SWIZZLE_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW1_XOR_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW1_XOR_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW1_XOR_SWIZZLE_DEF (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW1_XOR_SWIZZLE_HSH (0x050AC364)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW2_XOR_SWIZZLE_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW2_XOR_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW2_XOR_SWIZZLE_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW2_XOR_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW2_XOR_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW2_XOR_SWIZZLE_DEF (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW2_XOR_SWIZZLE_HSH (0x0514C364)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW3_XOR_SWIZZLE_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW3_XOR_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW3_XOR_SWIZZLE_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW3_XOR_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW3_XOR_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW3_XOR_SWIZZLE_DEF (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_L2P_ROW3_XOR_SWIZZLE_HSH (0x051EC364)

  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_ADDR_DQ_INV_EN_OFF   (29)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_ADDR_DQ_INV_EN_WID   ( 1)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_ADDR_DQ_INV_EN_MSK   (0x20000000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_ADDR_DQ_INV_EN_MIN   (0)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_ADDR_DQ_INV_EN_MAX   (1) // 0x00000001
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_ADDR_DQ_INV_EN_DEF   (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_ADDR_DQ_INV_EN_HSH   (0x013AC364)

#define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_REG                    (0x0000C368)

  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL0_SWIZZLE_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL0_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL0_SWIZZLE_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL0_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL0_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL0_SWIZZLE_DEF (0x00000000)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL0_SWIZZLE_HSH (0x0500C368)

  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL1_SWIZZLE_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL1_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL1_SWIZZLE_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL1_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL1_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL1_SWIZZLE_DEF (0x00000001)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL1_SWIZZLE_HSH (0x050AC368)

  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL2_SWIZZLE_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL2_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL2_SWIZZLE_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL2_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL2_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL2_SWIZZLE_DEF (0x00000002)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL2_SWIZZLE_HSH (0x0514C368)

  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL3_SWIZZLE_OFF (15)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL3_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL3_SWIZZLE_MSK (0x000F8000)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL3_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL3_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL3_SWIZZLE_DEF (0x00000003)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL3_SWIZZLE_HSH (0x051EC368)

  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL4_SWIZZLE_OFF (20)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL4_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL4_SWIZZLE_MSK (0x01F00000)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL4_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL4_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL4_SWIZZLE_DEF (0x00000004)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL4_SWIZZLE_HSH (0x0528C368)

  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL5_SWIZZLE_OFF (25)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL5_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL5_SWIZZLE_MSK (0x3E000000)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL5_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL5_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL5_SWIZZLE_DEF (0x00000005)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_L2P_COL5_SWIZZLE_HSH (0x0532C368)

#define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_REG                    (0x0000C36C)

  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL6_SWIZZLE_OFF ( 0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL6_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL6_SWIZZLE_MSK (0x0000001F)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL6_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL6_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL6_SWIZZLE_DEF (0x00000006)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL6_SWIZZLE_HSH (0x0500C36C)

  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL7_SWIZZLE_OFF ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL7_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL7_SWIZZLE_MSK (0x000003E0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL7_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL7_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL7_SWIZZLE_DEF (0x00000007)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL7_SWIZZLE_HSH (0x050AC36C)

  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL8_SWIZZLE_OFF (10)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL8_SWIZZLE_WID ( 5)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL8_SWIZZLE_MSK (0x00007C00)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL8_SWIZZLE_MIN (0)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL8_SWIZZLE_MAX (31) // 0x0000001F
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL8_SWIZZLE_DEF (0x00000008)
  #define MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_L2P_COL8_SWIZZLE_HSH (0x0514C36C)

#define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP0_REG                      (0x0000C370)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP1_REG                      (0x0000C374)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define MC0_REQ0_CR_CPGC_A_DUMMY_REG                                   (0x0000C378)
//Duplicate of MC0_BUF0_CPGC_B_DUMMY_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_CONTROL_REG                          (0x0000C430)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_CONTROL_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG                    (0x0000C434)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_INSTRUCTION_1_REG                    (0x0000C435)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_INSTRUCTION_2_REG                    (0x0000C436)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_INSTRUCTION_3_REG                    (0x0000C437)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_DATA_CONTROL_REG                             (0x0000C438)
//Duplicate of MC0_REQ0_CR_CPGC2_DATA_CONTROL_REG

#define MC0_REQ1_CR_CPGC2_DATA_INSTRUCTION_0_REG                       (0x0000C43C)
//Duplicate of MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_DATA_INSTRUCTION_1_REG                       (0x0000C43D)
//Duplicate of MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_DATA_INSTRUCTION_2_REG                       (0x0000C43E)
//Duplicate of MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_DATA_INSTRUCTION_3_REG                       (0x0000C43F)
//Duplicate of MC0_REQ0_CR_CPGC2_DATA_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_DATA_STATUS_REG                      (0x0000C440)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_DATA_STATUS_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG                  (0x0000C444)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_1_REG                  (0x0000C445)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_2_REG                  (0x0000C446)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_3_REG                  (0x0000C447)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_4_REG                  (0x0000C448)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_5_REG                  (0x0000C449)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_6_REG                  (0x0000C44A)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_7_REG                  (0x0000C44B)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG             (0x0000C44C)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_1_REG             (0x0000C44D)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_2_REG             (0x0000C44E)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_3_REG             (0x0000C44F)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_4_REG             (0x0000C450)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_5_REG             (0x0000C451)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_6_REG             (0x0000C452)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_7_REG             (0x0000C453)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_REG             (0x0000C454)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_REG

#define MC0_REQ1_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_REG             (0x0000C458)
//Duplicate of MC0_REQ0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_REG

#define MC0_REQ1_CR_CPGC2_BASE_REPEATS_REG                             (0x0000C45C)
//Duplicate of MC0_REQ0_CR_CPGC2_BASE_REPEATS_REG

#define MC0_REQ1_CR_CPGC2_BASE_REPEATS_CURRENT_REG                     (0x0000C460)
//Duplicate of MC0_REQ0_CR_CPGC2_BASE_REPEATS_CURRENT_REG

#define MC0_REQ1_CR_CPGC2_BASE_COL_REPEATS_REG                         (0x0000C464)
//Duplicate of MC0_REQ0_CR_CPGC2_BASE_COL_REPEATS_REG

#define MC0_REQ1_CR_CPGC2_BLOCK_REPEATS_REG                            (0x0000C468)
//Duplicate of MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_REG

#define MC0_REQ1_CR_CPGC2_BLOCK_REPEATS_CURRENT_REG                    (0x0000C46C)
//Duplicate of MC0_REQ0_CR_CPGC2_BLOCK_REPEATS_CURRENT_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_0_REG                    (0x0000C470)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_1_REG                    (0x0000C471)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_2_REG                    (0x0000C472)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_3_REG                    (0x0000C473)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_4_REG                    (0x0000C474)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_5_REG                    (0x0000C475)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_6_REG                    (0x0000C476)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_7_REG                    (0x0000C477)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_8_REG                    (0x0000C478)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_9_REG                    (0x0000C479)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_10_REG                   (0x0000C47A)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_11_REG                   (0x0000C47B)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_12_REG                   (0x0000C47C)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_13_REG                   (0x0000C47D)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_14_REG                   (0x0000C47E)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_15_REG                   (0x0000C47F)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_16_REG                   (0x0000C480)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_17_REG                   (0x0000C481)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_18_REG                   (0x0000C482)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_19_REG                   (0x0000C483)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_20_REG                   (0x0000C484)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_21_REG                   (0x0000C485)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_22_REG                   (0x0000C486)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_COMMAND_INSTRUCTION_23_REG                   (0x0000C487)
//Duplicate of MC0_REQ0_CR_CPGC2_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_HAMMER_REPEATS_REG                           (0x0000C488)
//Duplicate of MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_REG

#define MC0_REQ1_CR_CPGC2_HAMMER_REPEATS_CURRENT_REG                   (0x0000C48C)
//Duplicate of MC0_REQ0_CR_CPGC2_HAMMER_REPEATS_CURRENT_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG             (0x0000C490)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_1_REG             (0x0000C491)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_2_REG             (0x0000C492)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_3_REG             (0x0000C493)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_4_REG             (0x0000C494)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_5_REG             (0x0000C495)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_6_REG             (0x0000C496)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_7_REG             (0x0000C497)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_8_REG             (0x0000C498)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_9_REG             (0x0000C499)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_10_REG            (0x0000C49A)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_11_REG            (0x0000C49B)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_12_REG            (0x0000C49C)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_13_REG            (0x0000C49D)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_14_REG            (0x0000C49E)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_15_REG            (0x0000C49F)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG             (0x0000C4A0)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_1_REG             (0x0000C4A1)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_2_REG             (0x0000C4A2)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_3_REG             (0x0000C4A3)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_4_REG             (0x0000C4A4)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_5_REG             (0x0000C4A5)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_6_REG             (0x0000C4A6)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_7_REG             (0x0000C4A7)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_8_REG             (0x0000C4A8)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_9_REG             (0x0000C4A9)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_10_REG            (0x0000C4AA)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_11_REG            (0x0000C4AB)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_REPEATS_CURRENT_REG                   (0x0000C4AC)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_CURRENT_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_REPEATS_0_REG                         (0x0000C4B0)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_REG

#define MC0_REQ1_CR_CPGC2_OFFSET_REPEATS_1_REG                         (0x0000C4B4)
//Duplicate of MC0_REQ0_CR_CPGC2_OFFSET_REPEATS_0_REG

#define MC0_REQ1_CR_CPGC2_REGION_LOW_REG                               (0x0000C4B8)
//Duplicate of MC0_REQ0_CR_CPGC2_REGION_LOW_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_SIZE_REG                             (0x0000C4D8)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REG

#define MC0_REQ1_CR_CPGC2_BASE_ADDRESS_CONTROL_REG                     (0x0000C4E0)
//Duplicate of MC0_REQ0_CR_CPGC2_BASE_ADDRESS_CONTROL_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_PRBS_SEED_REG                        (0x0000C4E8)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SEED_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_PRBS_CURRENT_REG                     (0x0000C4F0)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_CURRENT_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_PRBS_SAVE_REG                        (0x0000C4F8)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_SAVE_REG

#define MC0_REQ1_CR_CPGC2_ADDRESS_PRBS_POLY_REG                        (0x0000C500)
//Duplicate of MC0_REQ0_CR_CPGC2_ADDRESS_PRBS_POLY_REG

#define MC0_REQ1_CR_CPGC2_BASE_CLOCK_CONFIG_REG                        (0x0000C508)
//Duplicate of MC0_REQ0_CR_CPGC2_BASE_CLOCK_CONFIG_REG

#define MC0_REQ1_CR_CPGC2_CMD_FSM_CURRENT_REG                          (0x0000C50C)
//Duplicate of MC0_REQ0_CR_CPGC2_CMD_FSM_CURRENT_REG

#define MC0_REQ1_CR_CPGC_SEQ_CFG_A_REG                                 (0x0000C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_OFF         ( 8)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_WID         ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_MSK         (0x00000100)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_MIN         (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_MAX         (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_DEF         (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_HSH         (0x0110C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_OFF       ( 9)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_WID       ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_MSK       (0x00000200)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_MIN       (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_MAX       (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_DEF       (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_HSH       (0x0112C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_OFF             (10)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_WID             ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_MSK             (0x00000400)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_MIN             (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_MAX             (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_DEF             (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_HSH             (0x0114C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_OFF              (11)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_WID              ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_MSK              (0x00000800)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_MIN              (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_MAX              (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_DEF              (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_HSH              (0x0116C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_OFF           (12)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_WID           ( 3)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_MSK           (0x00007000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_MIN           (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_MAX           (7) // 0x00000007
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_DEF           (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_HSH           (0x0318C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_OFF                (16)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_WID                ( 4)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_MSK                (0x000F0000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_MIN                (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_MAX                (15) // 0x0000000F
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_DEF                (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_HSH                (0x0420C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_OFF         (24)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_WID         ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_MSK         (0x01000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_MIN         (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_MAX         (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_DEF         (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_HSH         (0x0130C510)

#define MC0_REQ1_CR_CPGC_SEQ_CFG_A_P0_REG                              (0x0000C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_OFF      ( 8)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_WID      ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_MSK      (0x00000100)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_MIN      (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_MAX      (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_DEF      (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_CLEAR_ERR_BIND_P0_HSH      (0x0110C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_OFF    ( 9)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_WID    ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_MSK    (0x00000200)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_MIN    (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_MAX    (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_DEF    (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_ON_ERR_BIND_P0_HSH    (0x0112C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_OFF          (10)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_WID          ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_MSK          (0x00000400)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_MIN          (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_MAX          (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_DEF          (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_START_BIND_P0_HSH          (0x0114C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_OFF           (11)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_WID           ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_MSK           (0x00000800)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_MIN           (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_MAX           (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_DEF           (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_GLOBAL_STOP_BIND_P0_HSH           (0x0116C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_OFF        (12)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_WID        ( 3)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_MSK        (0x00007000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_MIN        (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_MAX        (7) // 0x00000007
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_DEF        (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_INITIALIZATION_MODE_P0_HSH        (0x0318C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_OFF             (16)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_WID             ( 4)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_MSK             (0x000F0000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_MIN             (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_MAX             (15) // 0x0000000F
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_DEF             (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_CHANNEL_ASSIGN_P0_HSH             (0x0420C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_OFF      (24)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_WID      ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_MSK      (0x01000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_MIN      (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_MAX      (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_DEF      (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_STRICT_WR_TO_RD_ORDER_P0_HSH      (0x0130C510)

  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_OFF      (25)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_WID      ( 1)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_MSK      (0x02000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_MIN      (0)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_MAX      (1) // 0x00000001
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_DEF      (0x00000000)
  #define MC0_REQ1_CR_CPGC_SEQ_CFG_A_POSTED_WR_TO_RD_ORDER_P0_HSH      (0x0132C510)

#define MC0_REQ1_CR_CPGC_SEQ_CFG_B_REG                                 (0x0000C514)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_CFG_B_REG

#define MC0_REQ1_CR_CPGC_SEQ_CTL_REG                                   (0x0000C518)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_CTL_REG

#define MC0_REQ1_CR_CPGC_SEQ_STATUS_REG                                (0x0000C51C)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_STATUS_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONTENT_0_REG                     (0x0000C520)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONTENT_1_REG                     (0x0000C528)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONTENT_2_REG                     (0x0000C530)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONTENT_3_REG                     (0x0000C538)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONTENT_4_REG                     (0x0000C540)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONTENT_5_REG                     (0x0000C548)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONTENT_6_REG                     (0x0000C550)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONTENT_7_REG                     (0x0000C558)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONTENT_ECC_0_REG                 (0x0000C560)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONTENT_ECC_1_REG                 (0x0000C568)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH1_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_REG                (0x0000C570)
//Duplicate of MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_REG

#define MC0_CH1_CR_CPGC2_MASK_ERRS_FIRST_N_READS_REG                   (0x0000C574)
//Duplicate of MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_REG

#define MC0_CH1_CR_CPGC2_ERR_SUMMARY_A_REG                             (0x0000C578)
//Duplicate of MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_REG

#define MC0_CH1_CR_CPGC2_ERR_SUMMARY_B_REG                             (0x0000C57C)
//Duplicate of MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_REG

#define MC0_CH1_CR_CPGC2_ERR_SUMMARY_C_REG                             (0x0000C580)
//Duplicate of MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_REG

#define MC0_CH1_CR_CPGC2_RASTER_MODE3_MAX_REG                          (0x0000C584)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONFIG_REG                        (0x0000C588)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_CONFIG_P0_REG                     (0x0000C588)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_P0_REG

#define MC0_CH1_CR_CPGC2_RASTER_REPO_STATUS_REG                        (0x0000C58C)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_REG

#define MC0_CH1_CR_CPGC_DPAT_CFG_REG                                   (0x0000C590)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_CFG_REG

#define MC0_CH1_CR_CPGC_DPAT_INVDC_CFG_REG                             (0x0000C594)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_REG

#define MC0_CH1_CR_CPGC_DPAT_BUF_CFG_REG                               (0x0000C598)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_BUF_CFG_REG

#define MC0_CH1_CR_CPGC_DPAT_ALT_BUF_CFG_REG                           (0x0000C59C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_REG

#define MC0_CH1_CR_CPGC_DPAT_USQ_CFG_0_REG                             (0x0000C5A0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH1_CR_CPGC_DPAT_USQ_CFG_1_REG                             (0x0000C5A1)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH1_CR_CPGC_DPAT_USQ_CFG_2_REG                             (0x0000C5A2)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_0_REG                              (0x0000C5A8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_1_REG                              (0x0000C5AC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_2_REG                              (0x0000C5B0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_POLY_0_REG                         (0x0000C5B8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_POLY_1_REG                         (0x0000C5BC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_POLY_2_REG                         (0x0000C5C0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG                        (0x0000C5C8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_STAGR_1_REG                        (0x0000C5CC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_STAGR_2_REG                        (0x0000C5D0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_LMN_0_REG                          (0x0000C5D8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_LMN_1_REG                          (0x0000C5DC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_LMN_2_REG                          (0x0000C5E0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH1_CR_CPGC_DPAT_INV_DC_MASK_LO_REG                        (0x0000C5E8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_REG

#define MC0_CH1_CR_CPGC_DPAT_INV_DC_MASK_HI_REG                        (0x0000C5EC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_REG

#define MC0_CH1_CR_CPGC_DPAT_DRAMDM_REG                                (0x0000C5F0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_DRAMDM_REG

#define MC0_CH1_CR_CPGC_DPAT_XDRAMDM_REG                               (0x0000C5F4)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_XDRAMDM_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG                       (0x0000C5F8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_WRSTAT_1_REG                       (0x0000C5FC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_WRSTAT_2_REG                       (0x0000C600)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG                       (0x0000C608)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_RDSTAT_1_REG                       (0x0000C60C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_RDSTAT_2_REG                       (0x0000C610)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_LMN_WRSTAT_0_REG                          (0x0000C618)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_LMN_WRSTAT_1_REG                          (0x0000C61C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_LMN_WRSTAT_2_REG                          (0x0000C620)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_LMN_RDSTAT_0_REG                          (0x0000C628)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_LMN_RDSTAT_1_REG                          (0x0000C62C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_LMN_RDSTAT_2_REG                          (0x0000C630)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG                       (0x0000C638)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_WRSAVE_1_REG                       (0x0000C63C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_WRSAVE_2_REG                       (0x0000C640)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_RDSAVE_0_REG                       (0x0000C648)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_RDSAVE_1_REG                       (0x0000C64C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH1_CR_CPGC_DPAT_UNISEQ_RDSAVE_2_REG                       (0x0000C650)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH1_CR_CPGC_ERR_LNEN_LO_REG                                (0x0000C658)
//Duplicate of MC0_CH0_CR_CPGC_ERR_LNEN_LO_REG

#define MC0_CH1_CR_CPGC_ERR_LNEN_HI_REG                                (0x0000C65C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_LNEN_HI_REG

#define MC0_CH1_CR_CPGC_ERR_XLNEN_REG                                  (0x0000C660)
//Duplicate of MC0_CH0_CR_CPGC_ERR_XLNEN_REG

#define MC0_CH1_CR_CPGC_ERR_CTL_REG                                    (0x0000C664)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CTL_REG

#define MC0_CH1_CR_CPGC_ERR_STAT03_REG                                 (0x0000C668)
//Duplicate of MC0_CH0_CR_CPGC_ERR_STAT03_REG

#define MC0_CH1_CR_CPGC_ERR_STAT47_REG                                 (0x0000C66C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_STAT47_REG

#define MC0_CH1_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG                     (0x0000C670)
//Duplicate of MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG

#define MC0_CH1_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG                      (0x0000C674)
//Duplicate of MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG

#define MC0_CH1_CR_CPGC_ERR_CNTRCTL_0_REG                              (0x0000C678)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTRCTL_1_REG                              (0x0000C67C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTRCTL_2_REG                              (0x0000C680)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTRCTL_3_REG                              (0x0000C684)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTRCTL_4_REG                              (0x0000C688)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTRCTL_5_REG                              (0x0000C68C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTRCTL_6_REG                              (0x0000C690)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTRCTL_7_REG                              (0x0000C694)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTRCTL_8_REG                              (0x0000C698)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTR_0_REG                                 (0x0000C6A0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTR_1_REG                                 (0x0000C6A4)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTR_2_REG                                 (0x0000C6A8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTR_3_REG                                 (0x0000C6AC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTR_4_REG                                 (0x0000C6B0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTR_5_REG                                 (0x0000C6B4)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTR_6_REG                                 (0x0000C6B8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTR_7_REG                                 (0x0000C6BC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTR_8_REG                                 (0x0000C6C0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH1_CR_CPGC_ERR_CNTR_OV_REG                                (0x0000C6C8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_OV_REG

#define MC0_CH1_CR_CPGC_ERR_TEST_ERR_STAT_REG                          (0x0000C6CC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_0_REG                                (0x0000C6D0)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_1_REG                                (0x0000C6D4)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_2_REG                                (0x0000C6D8)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_3_REG                                (0x0000C6DC)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_4_REG                                (0x0000C6E0)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_5_REG                                (0x0000C6E4)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_6_REG                                (0x0000C6E8)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_7_REG                                (0x0000C6EC)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_8_REG                                (0x0000C6F0)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_9_REG                                (0x0000C6F4)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_10_REG                               (0x0000C6F8)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_11_REG                               (0x0000C6FC)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_12_REG                               (0x0000C700)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_13_REG                               (0x0000C704)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_14_REG                               (0x0000C708)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_DPAT_EXTBUF_15_REG                               (0x0000C70C)
//Duplicate of MC0_BUF0_CPGC_DPAT_EXTBUF_0_REG

#define MC0_BUF1_CPGC_B_DUMMY_REG                                      (0x0000C710)
//Duplicate of MC0_BUF0_CPGC_B_DUMMY_REG

#define MC0_REQ1_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG                    (0x0000C720)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG

#define MC0_REQ1_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_REG                    (0x0000C724)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_REG

#define MC0_REQ1_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_REG                    (0x0000C728)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_REG

#define MC0_REQ1_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_REG                    (0x0000C72C)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_REG

#define MC0_REQ1_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_REG                    (0x0000C730)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_REG

#define MC0_REQ1_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_REG                    (0x0000C734)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_REG

#define MC0_REQ1_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_REG                    (0x0000C738)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_REG

#define MC0_REQ1_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_REG                    (0x0000C73C)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_REG

#define MC0_REQ1_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_REG                    (0x0000C740)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_REG

#define MC0_REQ1_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_REG                    (0x0000C744)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_REG

#define MC0_REQ1_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_REG                    (0x0000C748)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_REG

#define MC0_REQ1_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_REG                    (0x0000C74C)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_REG

#define MC0_REQ1_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_REG                     (0x0000C750)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_REG

#define MC0_REQ1_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_REG                     (0x0000C754)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_REG

#define MC0_REQ1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_REG                    (0x0000C758)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_REG

#define MC0_REQ1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_REG                    (0x0000C75C)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_REG

#define MC0_REQ1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_REG                    (0x0000C760)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_REG

#define MC0_REQ1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_REG                    (0x0000C764)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_REG

#define MC0_REQ1_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_REG                    (0x0000C768)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_REG

#define MC0_REQ1_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_REG                    (0x0000C76C)
//Duplicate of MC0_REQ0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_REG

#define MC0_REQ1_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP0_REG                      (0x0000C770)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define MC0_REQ1_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP1_REG                      (0x0000C774)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define MC0_REQ1_CR_CPGC_A_DUMMY_REG                                   (0x0000C778)
//Duplicate of MC0_BUF0_CPGC_B_DUMMY_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONTENT_0_REG                     (0x0000C920)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONTENT_1_REG                     (0x0000C928)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONTENT_2_REG                     (0x0000C930)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONTENT_3_REG                     (0x0000C938)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONTENT_4_REG                     (0x0000C940)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONTENT_5_REG                     (0x0000C948)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONTENT_6_REG                     (0x0000C950)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONTENT_7_REG                     (0x0000C958)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONTENT_ECC_0_REG                 (0x0000C960)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONTENT_ECC_1_REG                 (0x0000C968)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH2_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_REG                (0x0000C970)
//Duplicate of MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_REG

#define MC0_CH2_CR_CPGC2_MASK_ERRS_FIRST_N_READS_REG                   (0x0000C974)
//Duplicate of MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_REG

#define MC0_CH2_CR_CPGC2_ERR_SUMMARY_A_REG                             (0x0000C978)
//Duplicate of MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_REG

#define MC0_CH2_CR_CPGC2_ERR_SUMMARY_B_REG                             (0x0000C97C)
//Duplicate of MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_REG

#define MC0_CH2_CR_CPGC2_ERR_SUMMARY_C_REG                             (0x0000C980)
//Duplicate of MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_REG

#define MC0_CH2_CR_CPGC2_RASTER_MODE3_MAX_REG                          (0x0000C984)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONFIG_REG                        (0x0000C988)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_CONFIG_P0_REG                     (0x0000C988)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_P0_REG

#define MC0_CH2_CR_CPGC2_RASTER_REPO_STATUS_REG                        (0x0000C98C)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_REG

#define MC0_CH2_CR_CPGC_DPAT_CFG_REG                                   (0x0000C990)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_CFG_REG

#define MC0_CH2_CR_CPGC_DPAT_INVDC_CFG_REG                             (0x0000C994)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_REG

#define MC0_CH2_CR_CPGC_DPAT_BUF_CFG_REG                               (0x0000C998)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_BUF_CFG_REG

#define MC0_CH2_CR_CPGC_DPAT_ALT_BUF_CFG_REG                           (0x0000C99C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_REG

#define MC0_CH2_CR_CPGC_DPAT_USQ_CFG_0_REG                             (0x0000C9A0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH2_CR_CPGC_DPAT_USQ_CFG_1_REG                             (0x0000C9A1)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH2_CR_CPGC_DPAT_USQ_CFG_2_REG                             (0x0000C9A2)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_0_REG                              (0x0000C9A8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_1_REG                              (0x0000C9AC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_2_REG                              (0x0000C9B0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_POLY_0_REG                         (0x0000C9B8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_POLY_1_REG                         (0x0000C9BC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_POLY_2_REG                         (0x0000C9C0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG                        (0x0000C9C8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_STAGR_1_REG                        (0x0000C9CC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_STAGR_2_REG                        (0x0000C9D0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_LMN_0_REG                          (0x0000C9D8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_LMN_1_REG                          (0x0000C9DC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_LMN_2_REG                          (0x0000C9E0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH2_CR_CPGC_DPAT_INV_DC_MASK_LO_REG                        (0x0000C9E8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_REG

#define MC0_CH2_CR_CPGC_DPAT_INV_DC_MASK_HI_REG                        (0x0000C9EC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_REG

#define MC0_CH2_CR_CPGC_DPAT_DRAMDM_REG                                (0x0000C9F0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_DRAMDM_REG

#define MC0_CH2_CR_CPGC_DPAT_XDRAMDM_REG                               (0x0000C9F4)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_XDRAMDM_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG                       (0x0000C9F8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_WRSTAT_1_REG                       (0x0000C9FC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_WRSTAT_2_REG                       (0x0000CA00)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG                       (0x0000CA08)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_RDSTAT_1_REG                       (0x0000CA0C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_RDSTAT_2_REG                       (0x0000CA10)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_LMN_WRSTAT_0_REG                          (0x0000CA18)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_LMN_WRSTAT_1_REG                          (0x0000CA1C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_LMN_WRSTAT_2_REG                          (0x0000CA20)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_LMN_RDSTAT_0_REG                          (0x0000CA28)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_LMN_RDSTAT_1_REG                          (0x0000CA2C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_LMN_RDSTAT_2_REG                          (0x0000CA30)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG                       (0x0000CA38)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_WRSAVE_1_REG                       (0x0000CA3C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_WRSAVE_2_REG                       (0x0000CA40)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_RDSAVE_0_REG                       (0x0000CA48)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_RDSAVE_1_REG                       (0x0000CA4C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH2_CR_CPGC_DPAT_UNISEQ_RDSAVE_2_REG                       (0x0000CA50)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH2_CR_CPGC_ERR_LNEN_LO_REG                                (0x0000CA58)
//Duplicate of MC0_CH0_CR_CPGC_ERR_LNEN_LO_REG

#define MC0_CH2_CR_CPGC_ERR_LNEN_HI_REG                                (0x0000CA5C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_LNEN_HI_REG

#define MC0_CH2_CR_CPGC_ERR_XLNEN_REG                                  (0x0000CA60)
//Duplicate of MC0_CH0_CR_CPGC_ERR_XLNEN_REG

#define MC0_CH2_CR_CPGC_ERR_CTL_REG                                    (0x0000CA64)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CTL_REG

#define MC0_CH2_CR_CPGC_ERR_STAT03_REG                                 (0x0000CA68)
//Duplicate of MC0_CH0_CR_CPGC_ERR_STAT03_REG

#define MC0_CH2_CR_CPGC_ERR_STAT47_REG                                 (0x0000CA6C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_STAT47_REG

#define MC0_CH2_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG                     (0x0000CA70)
//Duplicate of MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG

#define MC0_CH2_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG                      (0x0000CA74)
//Duplicate of MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG

#define MC0_CH2_CR_CPGC_ERR_CNTRCTL_0_REG                              (0x0000CA78)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTRCTL_1_REG                              (0x0000CA7C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTRCTL_2_REG                              (0x0000CA80)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTRCTL_3_REG                              (0x0000CA84)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTRCTL_4_REG                              (0x0000CA88)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTRCTL_5_REG                              (0x0000CA8C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTRCTL_6_REG                              (0x0000CA90)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTRCTL_7_REG                              (0x0000CA94)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTRCTL_8_REG                              (0x0000CA98)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTR_0_REG                                 (0x0000CAA0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTR_1_REG                                 (0x0000CAA4)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTR_2_REG                                 (0x0000CAA8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTR_3_REG                                 (0x0000CAAC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTR_4_REG                                 (0x0000CAB0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTR_5_REG                                 (0x0000CAB4)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTR_6_REG                                 (0x0000CAB8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTR_7_REG                                 (0x0000CABC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTR_8_REG                                 (0x0000CAC0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH2_CR_CPGC_ERR_CNTR_OV_REG                                (0x0000CAC8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_OV_REG

#define MC0_CH2_CR_CPGC_ERR_TEST_ERR_STAT_REG                          (0x0000CACC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONTENT_0_REG                     (0x0000CD20)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONTENT_1_REG                     (0x0000CD28)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONTENT_2_REG                     (0x0000CD30)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONTENT_3_REG                     (0x0000CD38)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONTENT_4_REG                     (0x0000CD40)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONTENT_5_REG                     (0x0000CD48)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONTENT_6_REG                     (0x0000CD50)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONTENT_7_REG                     (0x0000CD58)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONTENT_ECC_0_REG                 (0x0000CD60)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONTENT_ECC_1_REG                 (0x0000CD68)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONTENT_0_REG

#define MC0_CH3_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_REG                (0x0000CD70)
//Duplicate of MC0_CH0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_REG

#define MC0_CH3_CR_CPGC2_MASK_ERRS_FIRST_N_READS_REG                   (0x0000CD74)
//Duplicate of MC0_CH0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_REG

#define MC0_CH3_CR_CPGC2_ERR_SUMMARY_A_REG                             (0x0000CD78)
//Duplicate of MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_REG

#define MC0_CH3_CR_CPGC2_ERR_SUMMARY_B_REG                             (0x0000CD7C)
//Duplicate of MC0_CH0_CR_CPGC2_ERR_SUMMARY_A_REG

#define MC0_CH3_CR_CPGC2_ERR_SUMMARY_C_REG                             (0x0000CD80)
//Duplicate of MC0_CH0_CR_CPGC2_ERR_SUMMARY_C_REG

#define MC0_CH3_CR_CPGC2_RASTER_MODE3_MAX_REG                          (0x0000CD84)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_MODE3_MAX_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONFIG_REG                        (0x0000CD88)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_CONFIG_P0_REG                     (0x0000CD88)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_CONFIG_P0_REG

#define MC0_CH3_CR_CPGC2_RASTER_REPO_STATUS_REG                        (0x0000CD8C)
//Duplicate of MC0_CH0_CR_CPGC2_RASTER_REPO_STATUS_REG

#define MC0_CH3_CR_CPGC_DPAT_CFG_REG                                   (0x0000CD90)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_CFG_REG

#define MC0_CH3_CR_CPGC_DPAT_INVDC_CFG_REG                             (0x0000CD94)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_REG

#define MC0_CH3_CR_CPGC_DPAT_BUF_CFG_REG                               (0x0000CD98)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_BUF_CFG_REG

#define MC0_CH3_CR_CPGC_DPAT_ALT_BUF_CFG_REG                           (0x0000CD9C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_REG

#define MC0_CH3_CR_CPGC_DPAT_USQ_CFG_0_REG                             (0x0000CDA0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH3_CR_CPGC_DPAT_USQ_CFG_1_REG                             (0x0000CDA1)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH3_CR_CPGC_DPAT_USQ_CFG_2_REG                             (0x0000CDA2)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_0_REG                              (0x0000CDA8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_1_REG                              (0x0000CDAC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_2_REG                              (0x0000CDB0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_POLY_0_REG                         (0x0000CDB8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_POLY_1_REG                         (0x0000CDBC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_POLY_2_REG                         (0x0000CDC0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_POLY_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG                        (0x0000CDC8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_STAGR_1_REG                        (0x0000CDCC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_STAGR_2_REG                        (0x0000CDD0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_STAGR_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_LMN_0_REG                          (0x0000CDD8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_LMN_1_REG                          (0x0000CDDC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_LMN_2_REG                          (0x0000CDE0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_LMN_0_REG

#define MC0_CH3_CR_CPGC_DPAT_INV_DC_MASK_LO_REG                        (0x0000CDE8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_REG

#define MC0_CH3_CR_CPGC_DPAT_INV_DC_MASK_HI_REG                        (0x0000CDEC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_REG

#define MC0_CH3_CR_CPGC_DPAT_DRAMDM_REG                                (0x0000CDF0)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_DRAMDM_REG

#define MC0_CH3_CR_CPGC_DPAT_XDRAMDM_REG                               (0x0000CDF4)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_XDRAMDM_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG                       (0x0000CDF8)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_WRSTAT_1_REG                       (0x0000CDFC)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_WRSTAT_2_REG                       (0x0000CE00)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG                       (0x0000CE08)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_RDSTAT_1_REG                       (0x0000CE0C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_RDSTAT_2_REG                       (0x0000CE10)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_LMN_WRSTAT_0_REG                          (0x0000CE18)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_LMN_WRSTAT_1_REG                          (0x0000CE1C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_LMN_WRSTAT_2_REG                          (0x0000CE20)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_WRSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_LMN_RDSTAT_0_REG                          (0x0000CE28)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_LMN_RDSTAT_1_REG                          (0x0000CE2C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_LMN_RDSTAT_2_REG                          (0x0000CE30)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_LMN_RDSTAT_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG                       (0x0000CE38)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_WRSAVE_1_REG                       (0x0000CE3C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_WRSAVE_2_REG                       (0x0000CE40)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_RDSAVE_0_REG                       (0x0000CE48)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_RDSAVE_1_REG                       (0x0000CE4C)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH3_CR_CPGC_DPAT_UNISEQ_RDSAVE_2_REG                       (0x0000CE50)
//Duplicate of MC0_CH0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_REG

#define MC0_CH3_CR_CPGC_ERR_LNEN_LO_REG                                (0x0000CE58)
//Duplicate of MC0_CH0_CR_CPGC_ERR_LNEN_LO_REG

#define MC0_CH3_CR_CPGC_ERR_LNEN_HI_REG                                (0x0000CE5C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_LNEN_HI_REG

#define MC0_CH3_CR_CPGC_ERR_XLNEN_REG                                  (0x0000CE60)
//Duplicate of MC0_CH0_CR_CPGC_ERR_XLNEN_REG

#define MC0_CH3_CR_CPGC_ERR_CTL_REG                                    (0x0000CE64)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CTL_REG

#define MC0_CH3_CR_CPGC_ERR_STAT03_REG                                 (0x0000CE68)
//Duplicate of MC0_CH0_CR_CPGC_ERR_STAT03_REG

#define MC0_CH3_CR_CPGC_ERR_STAT47_REG                                 (0x0000CE6C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_STAT47_REG

#define MC0_CH3_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG                     (0x0000CE70)
//Duplicate of MC0_CH0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_REG

#define MC0_CH3_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG                      (0x0000CE74)
//Duplicate of MC0_CH0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG

#define MC0_CH3_CR_CPGC_ERR_CNTRCTL_0_REG                              (0x0000CE78)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTRCTL_1_REG                              (0x0000CE7C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTRCTL_2_REG                              (0x0000CE80)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTRCTL_3_REG                              (0x0000CE84)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTRCTL_4_REG                              (0x0000CE88)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTRCTL_5_REG                              (0x0000CE8C)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTRCTL_6_REG                              (0x0000CE90)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTRCTL_7_REG                              (0x0000CE94)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTRCTL_8_REG                              (0x0000CE98)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTRCTL_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTR_0_REG                                 (0x0000CEA0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTR_1_REG                                 (0x0000CEA4)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTR_2_REG                                 (0x0000CEA8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTR_3_REG                                 (0x0000CEAC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTR_4_REG                                 (0x0000CEB0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTR_5_REG                                 (0x0000CEB4)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTR_6_REG                                 (0x0000CEB8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTR_7_REG                                 (0x0000CEBC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTR_8_REG                                 (0x0000CEC0)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_0_REG

#define MC0_CH3_CR_CPGC_ERR_CNTR_OV_REG                                (0x0000CEC8)
//Duplicate of MC0_CH0_CR_CPGC_ERR_CNTR_OV_REG

#define MC0_CH3_CR_CPGC_ERR_TEST_ERR_STAT_REG                          (0x0000CECC)
//Duplicate of MC0_CH0_CR_CPGC_ERR_TEST_ERR_STAT_REG
#pragma pack(pop)
#endif
