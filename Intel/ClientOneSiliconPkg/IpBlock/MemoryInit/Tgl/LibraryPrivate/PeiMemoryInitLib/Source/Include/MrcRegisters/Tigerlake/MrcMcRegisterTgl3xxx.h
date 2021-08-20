#ifndef __MrcMcRegisterTgl3xxx_h__
#define __MrcMcRegisterTgl3xxx_h__
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


#define DLLDDRDATA6_CR_MASTERDLLCFG_REG                                (0x00003000)
//Duplicate of DLLDDRDATA0_CR_MASTERDLLCFG_REG

#define DLLDDRDATA6_CR_CBTUNE0_REG                                     (0x00003004)
//Duplicate of DLLDDRDATA0_CR_CBTUNE0_REG

#define DLLDDRDATA6_CR_CBTUNE1_REG                                     (0x00003008)
//Duplicate of DLLDDRDATA0_CR_CBTUNE1_REG

#define DLLDDRDATA6_CR_ADCCFG_REG                                      (0x0000300C)
//Duplicate of DLLDDRDATA0_CR_ADCCFG_REG

#define DLLDDRDATA6_CR_CBTUNE2_REG                                     (0x00003010)
//Duplicate of DLLDDRDATA0_CR_CBTUNE2_REG

#define DLLDDRDATA6_CR_PIDFTDLY_REG                                    (0x00003018)
//Duplicate of DLLDDRDATA0_CR_PIDFTDLY_REG

#define DLLDDRDATA6_CR_DLLPITESTANDADC_REG                             (0x0000301C)
//Duplicate of DLLDDRDATA0_CR_DLLPITESTANDADC_REG

#define DLLDDRDATA6_CR_DLLSTATUS_REG                                   (0x00003020)
//Duplicate of DLLDDRDATA0_CR_DLLSTATUS_REG

#define DLLDDRDATA6_CR_DLLWEAKLOCK_REG                                 (0x00003024)
//Duplicate of DLLDDRDATA0_CR_DLLWEAKLOCK_REG

#define DLLDDRDATA6_CR_DDRCRVCCDLLFFCONTROL_REG                        (0x00003028)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG

#define DLLDDRDATA6_CR_DDRCRVCCDLLFFNBIAS_REG                          (0x0000302C)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_REG

#define DLLDDRDATA6_CR_DDRCRVCCDLLCOMPDLL_REG                          (0x00003030)
//Duplicate of DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_REG

#define DLLDDRDATA6_CR_DDRCRVCCDLLCOMPDATACCC_REG                      (0x00003034)
//Duplicate of DDRPHY_COMP_CR_VCCDLLCOMPDATACCC_REG

#define DLLDDRDATA6_CR_DDRCRVCCDLLCOMPOFFSET_REG                       (0x00003038)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_REG

#define DLLDDRDATA6_CR_DDRCRVCCDLLVSXHIFF_REG                          (0x0000303C)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_REG

#define DLLDDRDATA6_CR_DDRCRVCCDLLCOUPLINGCAP_REG                      (0x00003040)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_REG

#define DLLDDRDATA6_CR_PITUNE_REG                                      (0x00003044)
//Duplicate of DLLDDRDATA0_CR_PITUNE_REG

#define DLLDDRDATA7_CR_MASTERDLLCFG_REG                                (0x00003080)
//Duplicate of DLLDDRDATA0_CR_MASTERDLLCFG_REG

#define DLLDDRDATA7_CR_CBTUNE0_REG                                     (0x00003084)
//Duplicate of DLLDDRDATA0_CR_CBTUNE0_REG

#define DLLDDRDATA7_CR_CBTUNE1_REG                                     (0x00003088)
//Duplicate of DLLDDRDATA0_CR_CBTUNE1_REG

#define DLLDDRDATA7_CR_ADCCFG_REG                                      (0x0000308C)
//Duplicate of DLLDDRDATA0_CR_ADCCFG_REG

#define DLLDDRDATA7_CR_CBTUNE2_REG                                     (0x00003090)
//Duplicate of DLLDDRDATA0_CR_CBTUNE2_REG

#define DLLDDRDATA7_CR_PIDFTDLY_REG                                    (0x00003098)
//Duplicate of DLLDDRDATA0_CR_PIDFTDLY_REG

#define DLLDDRDATA7_CR_DLLPITESTANDADC_REG                             (0x0000309C)
//Duplicate of DLLDDRDATA0_CR_DLLPITESTANDADC_REG

#define DLLDDRDATA7_CR_DLLSTATUS_REG                                   (0x000030A0)
//Duplicate of DLLDDRDATA0_CR_DLLSTATUS_REG

#define DLLDDRDATA7_CR_DLLWEAKLOCK_REG                                 (0x000030A4)
//Duplicate of DLLDDRDATA0_CR_DLLWEAKLOCK_REG

#define DLLDDRDATA7_CR_DDRCRVCCDLLFFCONTROL_REG                        (0x000030A8)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG

#define DLLDDRDATA7_CR_DDRCRVCCDLLFFNBIAS_REG                          (0x000030AC)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_REG

#define DLLDDRDATA7_CR_DDRCRVCCDLLCOMPDLL_REG                          (0x000030B0)
//Duplicate of DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_REG

#define DLLDDRDATA7_CR_DDRCRVCCDLLCOMPDATACCC_REG                      (0x000030B4)
//Duplicate of DDRPHY_COMP_CR_VCCDLLCOMPDATACCC_REG

#define DLLDDRDATA7_CR_DDRCRVCCDLLCOMPOFFSET_REG                       (0x000030B8)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_REG

#define DLLDDRDATA7_CR_DDRCRVCCDLLVSXHIFF_REG                          (0x000030BC)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_REG

#define DLLDDRDATA7_CR_DDRCRVCCDLLCOUPLINGCAP_REG                      (0x000030C0)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_REG

#define DLLDDRDATA7_CR_PITUNE_REG                                      (0x000030C4)
//Duplicate of DLLDDRDATA0_CR_PITUNE_REG

#define DLLDDRCCC0_CR_MASTERDLLCFG_REG                                 (0x00003100)
//Duplicate of DLLDDRDATA0_CR_MASTERDLLCFG_REG

#define DLLDDRCCC0_CR_CBTUNE0_REG                                      (0x00003104)
//Duplicate of DLLDDRDATA0_CR_CBTUNE0_REG

#define DLLDDRCCC0_CR_CBTUNE1_REG                                      (0x00003108)
//Duplicate of DLLDDRDATA0_CR_CBTUNE1_REG

#define DLLDDRCCC0_CR_ADCCFG_REG                                       (0x0000310C)
//Duplicate of DLLDDRDATA0_CR_ADCCFG_REG

#define DLLDDRCCC0_CR_CBTUNE2_REG                                      (0x00003110)
//Duplicate of DLLDDRDATA0_CR_CBTUNE2_REG

#define DLLDDRCCC0_CR_PIDFTDLY_REG                                     (0x00003118)
//Duplicate of DLLDDRDATA0_CR_PIDFTDLY_REG

#define DLLDDRCCC0_CR_DLLPITESTANDADC_REG                              (0x0000311C)
//Duplicate of DLLDDRDATA0_CR_DLLPITESTANDADC_REG

#define DLLDDRCCC0_CR_DLLSTATUS_REG                                    (0x00003120)
//Duplicate of DLLDDRDATA0_CR_DLLSTATUS_REG

#define DLLDDRCCC0_CR_DLLWEAKLOCK_REG                                  (0x00003124)
//Duplicate of DLLDDRDATA0_CR_DLLWEAKLOCK_REG

#define DLLDDRCCC0_CR_DDRCRVCCDLLFFCONTROL_REG                         (0x00003128)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG

#define DLLDDRCCC0_CR_DDRCRVCCDLLFFNBIAS_REG                           (0x0000312C)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_REG

#define DLLDDRCCC0_CR_DDRCRVCCDLLCOMPDLL_REG                           (0x00003130)
//Duplicate of DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_REG

#define DLLDDRCCC0_CR_DDRCRVCCDLLCOMPDATACCC_REG                       (0x00003134)
//Duplicate of DDRPHY_COMP_CR_VCCDLLCOMPDATACCC_REG

#define DLLDDRCCC0_CR_DDRCRVCCDLLCOMPOFFSET_REG                        (0x00003138)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_REG

#define DLLDDRCCC0_CR_DDRCRVCCDLLVSXHIFF_REG                           (0x0000313C)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_REG

#define DLLDDRCCC0_CR_DDRCRVCCDLLCOUPLINGCAP_REG                       (0x00003140)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_REG

#define DLLDDRCCC0_CR_PITUNE_REG                                       (0x00003144)
//Duplicate of DLLDDRDATA0_CR_PITUNE_REG

#define DLLDDRCCC1_CR_MASTERDLLCFG_REG                                 (0x00003180)
//Duplicate of DLLDDRDATA0_CR_MASTERDLLCFG_REG

#define DLLDDRCCC1_CR_CBTUNE0_REG                                      (0x00003184)
//Duplicate of DLLDDRDATA0_CR_CBTUNE0_REG

#define DLLDDRCCC1_CR_CBTUNE1_REG                                      (0x00003188)
//Duplicate of DLLDDRDATA0_CR_CBTUNE1_REG

#define DLLDDRCCC1_CR_ADCCFG_REG                                       (0x0000318C)
//Duplicate of DLLDDRDATA0_CR_ADCCFG_REG

#define DLLDDRCCC1_CR_CBTUNE2_REG                                      (0x00003190)
//Duplicate of DLLDDRDATA0_CR_CBTUNE2_REG

#define DLLDDRCCC1_CR_PIDFTDLY_REG                                     (0x00003198)
//Duplicate of DLLDDRDATA0_CR_PIDFTDLY_REG

#define DLLDDRCCC1_CR_DLLPITESTANDADC_REG                              (0x0000319C)
//Duplicate of DLLDDRDATA0_CR_DLLPITESTANDADC_REG

#define DLLDDRCCC1_CR_DLLSTATUS_REG                                    (0x000031A0)
//Duplicate of DLLDDRDATA0_CR_DLLSTATUS_REG

#define DLLDDRCCC1_CR_DLLWEAKLOCK_REG                                  (0x000031A4)
//Duplicate of DLLDDRDATA0_CR_DLLWEAKLOCK_REG

#define DLLDDRCCC1_CR_DDRCRVCCDLLFFCONTROL_REG                         (0x000031A8)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG

#define DLLDDRCCC1_CR_DDRCRVCCDLLFFNBIAS_REG                           (0x000031AC)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_REG

#define DLLDDRCCC1_CR_DDRCRVCCDLLCOMPDLL_REG                           (0x000031B0)
//Duplicate of DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_REG

#define DLLDDRCCC1_CR_DDRCRVCCDLLCOMPDATACCC_REG                       (0x000031B4)
//Duplicate of DDRPHY_COMP_CR_VCCDLLCOMPDATACCC_REG

#define DLLDDRCCC1_CR_DDRCRVCCDLLCOMPOFFSET_REG                        (0x000031B8)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_REG

#define DLLDDRCCC1_CR_DDRCRVCCDLLVSXHIFF_REG                           (0x000031BC)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_REG

#define DLLDDRCCC1_CR_DDRCRVCCDLLCOUPLINGCAP_REG                       (0x000031C0)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_REG

#define DLLDDRCCC1_CR_PITUNE_REG                                       (0x000031C4)
//Duplicate of DLLDDRDATA0_CR_PITUNE_REG

#define DLLDDRCCC2_CR_MASTERDLLCFG_REG                                 (0x00003200)
//Duplicate of DLLDDRDATA0_CR_MASTERDLLCFG_REG

#define DLLDDRCCC2_CR_CBTUNE0_REG                                      (0x00003204)
//Duplicate of DLLDDRDATA0_CR_CBTUNE0_REG

#define DLLDDRCCC2_CR_CBTUNE1_REG                                      (0x00003208)
//Duplicate of DLLDDRDATA0_CR_CBTUNE1_REG

#define DLLDDRCCC2_CR_ADCCFG_REG                                       (0x0000320C)
//Duplicate of DLLDDRDATA0_CR_ADCCFG_REG

#define DLLDDRCCC2_CR_CBTUNE2_REG                                      (0x00003210)
//Duplicate of DLLDDRDATA0_CR_CBTUNE2_REG

#define DLLDDRCCC2_CR_PIDFTDLY_REG                                     (0x00003218)
//Duplicate of DLLDDRDATA0_CR_PIDFTDLY_REG

#define DLLDDRCCC2_CR_DLLPITESTANDADC_REG                              (0x0000321C)
//Duplicate of DLLDDRDATA0_CR_DLLPITESTANDADC_REG

#define DLLDDRCCC2_CR_DLLSTATUS_REG                                    (0x00003220)
//Duplicate of DLLDDRDATA0_CR_DLLSTATUS_REG

#define DLLDDRCCC2_CR_DLLWEAKLOCK_REG                                  (0x00003224)
//Duplicate of DLLDDRDATA0_CR_DLLWEAKLOCK_REG

#define DLLDDRCCC2_CR_DDRCRVCCDLLFFCONTROL_REG                         (0x00003228)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG

#define DLLDDRCCC2_CR_DDRCRVCCDLLFFNBIAS_REG                           (0x0000322C)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_REG

#define DLLDDRCCC2_CR_DDRCRVCCDLLCOMPDLL_REG                           (0x00003230)
//Duplicate of DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_REG

#define DLLDDRCCC2_CR_DDRCRVCCDLLCOMPDATACCC_REG                       (0x00003234)
//Duplicate of DDRPHY_COMP_CR_VCCDLLCOMPDATACCC_REG

#define DLLDDRCCC2_CR_DDRCRVCCDLLCOMPOFFSET_REG                        (0x00003238)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_REG

#define DLLDDRCCC2_CR_DDRCRVCCDLLVSXHIFF_REG                           (0x0000323C)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_REG

#define DLLDDRCCC2_CR_DDRCRVCCDLLCOUPLINGCAP_REG                       (0x00003240)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_REG

#define DLLDDRCCC2_CR_PITUNE_REG                                       (0x00003244)
//Duplicate of DLLDDRDATA0_CR_PITUNE_REG

#define DLLDDRCCC3_CR_MASTERDLLCFG_REG                                 (0x00003280)
//Duplicate of DLLDDRDATA0_CR_MASTERDLLCFG_REG

#define DLLDDRCCC3_CR_CBTUNE0_REG                                      (0x00003284)
//Duplicate of DLLDDRDATA0_CR_CBTUNE0_REG

#define DLLDDRCCC3_CR_CBTUNE1_REG                                      (0x00003288)
//Duplicate of DLLDDRDATA0_CR_CBTUNE1_REG

#define DLLDDRCCC3_CR_ADCCFG_REG                                       (0x0000328C)
//Duplicate of DLLDDRDATA0_CR_ADCCFG_REG

#define DLLDDRCCC3_CR_CBTUNE2_REG                                      (0x00003290)
//Duplicate of DLLDDRDATA0_CR_CBTUNE2_REG

#define DLLDDRCCC3_CR_PIDFTDLY_REG                                     (0x00003298)
//Duplicate of DLLDDRDATA0_CR_PIDFTDLY_REG

#define DLLDDRCCC3_CR_DLLPITESTANDADC_REG                              (0x0000329C)
//Duplicate of DLLDDRDATA0_CR_DLLPITESTANDADC_REG

#define DLLDDRCCC3_CR_DLLSTATUS_REG                                    (0x000032A0)
//Duplicate of DLLDDRDATA0_CR_DLLSTATUS_REG

#define DLLDDRCCC3_CR_DLLWEAKLOCK_REG                                  (0x000032A4)
//Duplicate of DLLDDRDATA0_CR_DLLWEAKLOCK_REG

#define DLLDDRCCC3_CR_DDRCRVCCDLLFFCONTROL_REG                         (0x000032A8)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG

#define DLLDDRCCC3_CR_DDRCRVCCDLLFFNBIAS_REG                           (0x000032AC)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_REG

#define DLLDDRCCC3_CR_DDRCRVCCDLLCOMPDLL_REG                           (0x000032B0)
//Duplicate of DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_REG

#define DLLDDRCCC3_CR_DDRCRVCCDLLCOMPDATACCC_REG                       (0x000032B4)
//Duplicate of DDRPHY_COMP_CR_VCCDLLCOMPDATACCC_REG

#define DLLDDRCCC3_CR_DDRCRVCCDLLCOMPOFFSET_REG                        (0x000032B8)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_REG

#define DLLDDRCCC3_CR_DDRCRVCCDLLVSXHIFF_REG                           (0x000032BC)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_REG

#define DLLDDRCCC3_CR_DDRCRVCCDLLCOUPLINGCAP_REG                       (0x000032C0)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_REG

#define DLLDDRCCC3_CR_PITUNE_REG                                       (0x000032C4)
//Duplicate of DLLDDRDATA0_CR_PITUNE_REG

#define DLLDDRCOMP_CR_MASTERDLLCFG_REG                                 (0x00003300)
//Duplicate of DLLDDRDATA0_CR_MASTERDLLCFG_REG

#define DLLDDRCOMP_CR_CBTUNE0_REG                                      (0x00003304)
//Duplicate of DLLDDRDATA0_CR_CBTUNE0_REG

#define DLLDDRCOMP_CR_CBTUNE1_REG                                      (0x00003308)
//Duplicate of DLLDDRDATA0_CR_CBTUNE1_REG

#define DLLDDRCOMP_CR_ADCCFG_REG                                       (0x0000330C)
//Duplicate of DLLDDRDATA0_CR_ADCCFG_REG

#define DLLDDRCOMP_CR_CBTUNE2_REG                                      (0x00003310)
//Duplicate of DLLDDRDATA0_CR_CBTUNE2_REG

#define DLLDDRCOMP_CR_PIDFTDLY_REG                                     (0x00003318)
//Duplicate of DLLDDRDATA0_CR_PIDFTDLY_REG

#define DLLDDRCOMP_CR_DLLPITESTANDADC_REG                              (0x0000331C)
//Duplicate of DLLDDRDATA0_CR_DLLPITESTANDADC_REG

#define DLLDDRCOMP_CR_DLLSTATUS_REG                                    (0x00003320)
//Duplicate of DLLDDRDATA0_CR_DLLSTATUS_REG

#define DLLDDRCOMP_CR_DLLWEAKLOCK_REG                                  (0x00003324)
//Duplicate of DLLDDRDATA0_CR_DLLWEAKLOCK_REG

#define DLLDDRCOMP_CR_DDRCRVCCDLLFFCONTROL_REG                         (0x00003328)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG

#define DLLDDRCOMP_CR_DDRCRVCCDLLFFNBIAS_REG                           (0x0000332C)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_REG

#define DLLDDRCOMP_CR_DDRCRVCCDLLCOMPDLL_REG                           (0x00003330)
//Duplicate of DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_REG

#define DLLDDRCOMP_CR_DDRCRVCCDLLCOMPDATACCC_REG                       (0x00003334)
//Duplicate of DDRPHY_COMP_CR_VCCDLLCOMPDATACCC_REG

#define DLLDDRCOMP_CR_DDRCRVCCDLLCOMPOFFSET_REG                        (0x00003338)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_REG

#define DLLDDRCOMP_CR_DDRCRVCCDLLVSXHIFF_REG                           (0x0000333C)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_REG

#define DLLDDRCOMP_CR_DDRCRVCCDLLCOUPLINGCAP_REG                       (0x00003340)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_REG

#define DLLDDRCOMP_CR_PITUNE_REG                                       (0x00003344)
//Duplicate of DLLDDRDATA0_CR_PITUNE_REG

#define DLLDDRDATA8_CR_MASTERDLLCFG_P0_REG                             (0x00003380)
//Duplicate of DLLDDRDATA0_CR_MASTERDLLCFG_P0_REG

#define DLLDDRDATA8_CR_CBTUNE0_P0_REG                                  (0x00003384)
//Duplicate of DLLDDRDATA0_CR_CBTUNE0_P0_REG

#define DLLDDRDATA8_CR_CBTUNE1_P0_REG                                  (0x00003388)
//Duplicate of DLLDDRDATA0_CR_CBTUNE1_P0_REG

#define DLLDDRDATA8_CR_ADCCFG_P0_REG                                   (0x0000338C)
//Duplicate of DLLDDRDATA0_CR_ADCCFG_P0_REG

#define DLLDDRDATA8_CR_CBTUNE2_P0_REG                                  (0x00003390)
//Duplicate of DLLDDRDATA0_CR_CBTUNE2_P0_REG

#define DLLDDRDATA8_CR_PIDFTDLY_P0_REG                                 (0x00003398)
//Duplicate of DLLDDRDATA0_CR_PIDFTDLY_P0_REG

#define DLLDDRDATA8_CR_DLLPITESTANDADC_P0_REG                          (0x0000339C)
//Duplicate of DLLDDRDATA0_CR_DLLPITESTANDADC_P0_REG

#define DLLDDRDATA8_CR_DLLSTATUS_P0_REG                                (0x000033A0)
//Duplicate of DLLDDRDATA0_CR_DLLSTATUS_P0_REG

#define DLLDDRDATA8_CR_DLLWEAKLOCK_P0_REG                              (0x000033A4)
//Duplicate of DLLDDRDATA0_CR_DLLWEAKLOCK_P0_REG

#define DLLDDRDATA8_CR_DDRCRVCCDLLFFCONTROL_P0_REG                     (0x000033A8)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_P0_REG

#define DLLDDRDATA8_CR_DDRCRVCCDLLFFNBIAS_P0_REG                       (0x000033AC)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_P0_REG

#define DLLDDRDATA8_CR_DDRCRVCCDLLCOMPDLL_P0_REG                       (0x000033B0)
//Duplicate of DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_P0_REG

#define DLLDDRDATA8_CR_DDRCRVCCDLLCOMPDATACCC_P0_REG                   (0x000033B4)
//Duplicate of DDRPHY_COMP_CR_VCCDLLCOMPDATACCC_P0_REG

#define DLLDDRDATA8_CR_DDRCRVCCDLLCOMPOFFSET_P0_REG                    (0x000033B8)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_P0_REG

#define DLLDDRDATA8_CR_DDRCRVCCDLLVSXHIFF_P0_REG                       (0x000033BC)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_P0_REG

#define DLLDDRDATA8_CR_DDRCRVCCDLLCOUPLINGCAP_P0_REG                   (0x000033C0)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_P0_REG

#define DLLDDRDATA8_CR_PITUNE_P0_REG                                   (0x000033C4)
//Duplicate of DLLDDRDATA0_CR_PITUNE_P0_REG

#define DLLDDRDATA9_CR_MASTERDLLCFG_P0_REG                             (0x00003400)
//Duplicate of DLLDDRDATA0_CR_MASTERDLLCFG_P0_REG

#define DLLDDRDATA9_CR_CBTUNE0_P0_REG                                  (0x00003404)
//Duplicate of DLLDDRDATA0_CR_CBTUNE0_P0_REG

#define DLLDDRDATA9_CR_CBTUNE1_P0_REG                                  (0x00003408)
//Duplicate of DLLDDRDATA0_CR_CBTUNE1_P0_REG

#define DLLDDRDATA9_CR_ADCCFG_P0_REG                                   (0x0000340C)
//Duplicate of DLLDDRDATA0_CR_ADCCFG_P0_REG

#define DLLDDRDATA9_CR_CBTUNE2_P0_REG                                  (0x00003410)
//Duplicate of DLLDDRDATA0_CR_CBTUNE2_P0_REG

#define DLLDDRDATA9_CR_PIDFTDLY_P0_REG                                 (0x00003418)
//Duplicate of DLLDDRDATA0_CR_PIDFTDLY_P0_REG

#define DLLDDRDATA9_CR_DLLPITESTANDADC_P0_REG                          (0x0000341C)
//Duplicate of DLLDDRDATA0_CR_DLLPITESTANDADC_P0_REG

#define DLLDDRDATA9_CR_DLLSTATUS_P0_REG                                (0x00003420)
//Duplicate of DLLDDRDATA0_CR_DLLSTATUS_P0_REG

#define DLLDDRDATA9_CR_DLLWEAKLOCK_P0_REG                              (0x00003424)
//Duplicate of DLLDDRDATA0_CR_DLLWEAKLOCK_P0_REG

#define DLLDDRDATA9_CR_DDRCRVCCDLLFFCONTROL_P0_REG                     (0x00003428)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_P0_REG

#define DLLDDRDATA9_CR_DDRCRVCCDLLFFNBIAS_P0_REG                       (0x0000342C)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_P0_REG

#define DLLDDRDATA9_CR_DDRCRVCCDLLCOMPDLL_P0_REG                       (0x00003430)
//Duplicate of DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_P0_REG

#define DLLDDRDATA9_CR_DDRCRVCCDLLCOMPDATACCC_P0_REG                   (0x00003434)
//Duplicate of DDRPHY_COMP_CR_VCCDLLCOMPDATACCC_P0_REG

#define DLLDDRDATA9_CR_DDRCRVCCDLLCOMPOFFSET_P0_REG                    (0x00003438)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_P0_REG

#define DLLDDRDATA9_CR_DDRCRVCCDLLVSXHIFF_P0_REG                       (0x0000343C)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_P0_REG

#define DLLDDRDATA9_CR_DDRCRVCCDLLCOUPLINGCAP_P0_REG                   (0x00003440)
//Duplicate of DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_P0_REG

#define DLLDDRDATA9_CR_PITUNE_P0_REG                                   (0x00003444)
//Duplicate of DLLDDRDATA0_CR_PITUNE_P0_REG

#define FLL_CMD_CFG_REG_REG                                            (0x00003500)

  #define FLL_CMD_CFG_REG_FLL_RATIO_OFF                                ( 0)
  #define FLL_CMD_CFG_REG_FLL_RATIO_WID                                ( 8)
  #define FLL_CMD_CFG_REG_FLL_RATIO_MSK                                (0x000000FF)
  #define FLL_CMD_CFG_REG_FLL_RATIO_MIN                                (0)
  #define FLL_CMD_CFG_REG_FLL_RATIO_MAX                                (255) // 0x000000FF
  #define FLL_CMD_CFG_REG_FLL_RATIO_DEF                                (0x00000012)
  #define FLL_CMD_CFG_REG_FLL_RATIO_HSH                                (0x08003500)

  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_OFF                          ( 8)
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_WID                          ( 1)
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_MSK                          (0x00000100)
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_MIN                          (0)
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_MAX                          (1) // 0x00000001
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_DEF                          (0x00000000)
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_HSH                          (0x01103500)

  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_OFF                          ( 9)
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_WID                          ( 1)
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_MSK                          (0x00000200)
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_MIN                          (0)
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_MAX                          (1) // 0x00000001
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_DEF                          (0x00000000)
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_HSH                          (0x01123500)

  #define FLL_CMD_CFG_REG_FLL_ENABLE_OFF                               (10)
  #define FLL_CMD_CFG_REG_FLL_ENABLE_WID                               ( 1)
  #define FLL_CMD_CFG_REG_FLL_ENABLE_MSK                               (0x00000400)
  #define FLL_CMD_CFG_REG_FLL_ENABLE_MIN                               (0)
  #define FLL_CMD_CFG_REG_FLL_ENABLE_MAX                               (1) // 0x00000001
  #define FLL_CMD_CFG_REG_FLL_ENABLE_DEF                               (0x00000000)
  #define FLL_CMD_CFG_REG_FLL_ENABLE_HSH                               (0x01143500)

  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_OFF                           (11)
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_WID                           ( 1)
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_MSK                           (0x00000800)
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_MIN                           (0)
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_MAX                           (1) // 0x00000001
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_DEF                           (0x00000000)
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_HSH                           (0x01163500)

  #define FLL_CMD_CFG_REG_BYPASS_AMPREF_FLT_OFF                        (12)
  #define FLL_CMD_CFG_REG_BYPASS_AMPREF_FLT_WID                        ( 1)
  #define FLL_CMD_CFG_REG_BYPASS_AMPREF_FLT_MSK                        (0x00001000)
  #define FLL_CMD_CFG_REG_BYPASS_AMPREF_FLT_MIN                        (0)
  #define FLL_CMD_CFG_REG_BYPASS_AMPREF_FLT_MAX                        (1) // 0x00000001
  #define FLL_CMD_CFG_REG_BYPASS_AMPREF_FLT_DEF                        (0x00000000)
  #define FLL_CMD_CFG_REG_BYPASS_AMPREF_FLT_HSH                        (0x01183500)

  #define FLL_CMD_CFG_REG_FLLVR_BYPASS_OFF                             (13)
  #define FLL_CMD_CFG_REG_FLLVR_BYPASS_WID                             ( 1)
  #define FLL_CMD_CFG_REG_FLLVR_BYPASS_MSK                             (0x00002000)
  #define FLL_CMD_CFG_REG_FLLVR_BYPASS_MIN                             (0)
  #define FLL_CMD_CFG_REG_FLLVR_BYPASS_MAX                             (1) // 0x00000001
  #define FLL_CMD_CFG_REG_FLLVR_BYPASS_DEF                             (0x00000000)
  #define FLL_CMD_CFG_REG_FLLVR_BYPASS_HSH                             (0x011A3500)

  #define FLL_CMD_CFG_REG_DCO_EN_HR_OFF                                (14)
  #define FLL_CMD_CFG_REG_DCO_EN_HR_WID                                ( 2)
  #define FLL_CMD_CFG_REG_DCO_EN_HR_MSK                                (0x0000C000)
  #define FLL_CMD_CFG_REG_DCO_EN_HR_MIN                                (0)
  #define FLL_CMD_CFG_REG_DCO_EN_HR_MAX                                (3) // 0x00000003
  #define FLL_CMD_CFG_REG_DCO_EN_HR_DEF                                (0x00000000)
  #define FLL_CMD_CFG_REG_DCO_EN_HR_HSH                                (0x021C3500)

  #define FLL_CMD_CFG_REG_DCO_CB_OFF                                   (16)
  #define FLL_CMD_CFG_REG_DCO_CB_WID                                   ( 3)
  #define FLL_CMD_CFG_REG_DCO_CB_MSK                                   (0x00070000)
  #define FLL_CMD_CFG_REG_DCO_CB_MIN                                   (0)
  #define FLL_CMD_CFG_REG_DCO_CB_MAX                                   (7) // 0x00000007
  #define FLL_CMD_CFG_REG_DCO_CB_DEF                                   (0x00000000)
  #define FLL_CMD_CFG_REG_DCO_CB_HSH                                   (0x03203500)

  #define FLL_CMD_CFG_REG_DCO_IREFTUNE_OFF                             (19)
  #define FLL_CMD_CFG_REG_DCO_IREFTUNE_WID                             ( 4)
  #define FLL_CMD_CFG_REG_DCO_IREFTUNE_MSK                             (0x00780000)
  #define FLL_CMD_CFG_REG_DCO_IREFTUNE_MIN                             (0)
  #define FLL_CMD_CFG_REG_DCO_IREFTUNE_MAX                             (15) // 0x0000000F
  #define FLL_CMD_CFG_REG_DCO_IREFTUNE_DEF                             (0x00000004)
  #define FLL_CMD_CFG_REG_DCO_IREFTUNE_HSH                             (0x04263500)

  #define FLL_CMD_CFG_REG_FASTRAMP_EN_OFF                              (23)
  #define FLL_CMD_CFG_REG_FASTRAMP_EN_WID                              ( 1)
  #define FLL_CMD_CFG_REG_FASTRAMP_EN_MSK                              (0x00800000)
  #define FLL_CMD_CFG_REG_FASTRAMP_EN_MIN                              (0)
  #define FLL_CMD_CFG_REG_FASTRAMP_EN_MAX                              (1) // 0x00000001
  #define FLL_CMD_CFG_REG_FASTRAMP_EN_DEF                              (0x00000001)
  #define FLL_CMD_CFG_REG_FASTRAMP_EN_HSH                              (0x012E3500)

  #define FLL_CMD_CFG_REG_LKR_ALWAYS_ON_OFF                            (24)
  #define FLL_CMD_CFG_REG_LKR_ALWAYS_ON_WID                            ( 1)
  #define FLL_CMD_CFG_REG_LKR_ALWAYS_ON_MSK                            (0x01000000)
  #define FLL_CMD_CFG_REG_LKR_ALWAYS_ON_MIN                            (0)
  #define FLL_CMD_CFG_REG_LKR_ALWAYS_ON_MAX                            (1) // 0x00000001
  #define FLL_CMD_CFG_REG_LKR_ALWAYS_ON_DEF                            (0x00000000)
  #define FLL_CMD_CFG_REG_LKR_ALWAYS_ON_HSH                            (0x01303500)

  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_OVRD_EN_OFF                  (25)
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_OVRD_EN_WID                  ( 1)
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_OVRD_EN_MSK                  (0x02000000)
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_OVRD_EN_MIN                  (0)
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_OVRD_EN_MAX                  (1) // 0x00000001
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_OVRD_EN_DEF                  (0x00000000)
  #define FLL_CMD_CFG_REG_FLL_OUT_CLK_REQ_OVRD_EN_HSH                  (0x01323500)

  #define FLL_CMD_CFG_REG_LDO_ENABLE_DLY_SEL_OFF                       (26)
  #define FLL_CMD_CFG_REG_LDO_ENABLE_DLY_SEL_WID                       ( 2)
  #define FLL_CMD_CFG_REG_LDO_ENABLE_DLY_SEL_MSK                       (0x0C000000)
  #define FLL_CMD_CFG_REG_LDO_ENABLE_DLY_SEL_MIN                       (0)
  #define FLL_CMD_CFG_REG_LDO_ENABLE_DLY_SEL_MAX                       (3) // 0x00000003
  #define FLL_CMD_CFG_REG_LDO_ENABLE_DLY_SEL_DEF                       (0x00000002)
  #define FLL_CMD_CFG_REG_LDO_ENABLE_DLY_SEL_HSH                       (0x02343500)

  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_OVRD_EN_OFF                  (28)
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_OVRD_EN_WID                  ( 1)
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_OVRD_EN_MSK                  (0x10000000)
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_OVRD_EN_MIN                  (0)
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_OVRD_EN_MAX                  (1) // 0x00000001
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_OVRD_EN_DEF                  (0x00000000)
  #define FLL_CMD_CFG_REG_FREQ_CHANGE_REQ_OVRD_EN_HSH                  (0x01383500)

  #define FLL_CMD_CFG_REG_LKR_STRENGTH_CFG_OFF                         (29)
  #define FLL_CMD_CFG_REG_LKR_STRENGTH_CFG_WID                         ( 1)
  #define FLL_CMD_CFG_REG_LKR_STRENGTH_CFG_MSK                         (0x20000000)
  #define FLL_CMD_CFG_REG_LKR_STRENGTH_CFG_MIN                         (0)
  #define FLL_CMD_CFG_REG_LKR_STRENGTH_CFG_MAX                         (1) // 0x00000001
  #define FLL_CMD_CFG_REG_LKR_STRENGTH_CFG_DEF                         (0x00000001)
  #define FLL_CMD_CFG_REG_LKR_STRENGTH_CFG_HSH                         (0x013A3500)

  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_OVRD_EN_OFF                   (30)
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_OVRD_EN_WID                   ( 1)
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_OVRD_EN_MSK                   (0x40000000)
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_OVRD_EN_MIN                   (0)
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_OVRD_EN_MAX                   (1) // 0x00000001
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_OVRD_EN_DEF                   (0x00000000)
  #define FLL_CMD_CFG_REG_FLL_LDO_ENABLE_OVRD_EN_HSH                   (0x013C3500)

  #define FLL_CMD_CFG_REG_SELEXTREF_OFF                                (31)
  #define FLL_CMD_CFG_REG_SELEXTREF_WID                                ( 1)
  #define FLL_CMD_CFG_REG_SELEXTREF_MSK                                (0x80000000)
  #define FLL_CMD_CFG_REG_SELEXTREF_MIN                                (0)
  #define FLL_CMD_CFG_REG_SELEXTREF_MAX                                (1) // 0x00000001
  #define FLL_CMD_CFG_REG_SELEXTREF_DEF                                (0x00000000)
  #define FLL_CMD_CFG_REG_SELEXTREF_HSH                                (0x013E3500)

#define FLL_STATIC_CFG_0_REG_REG                                       (0x00003504)

  #define FLL_STATIC_CFG_0_REG_FAST_CAL_WINDOW_VAL_OFF                 ( 0)
  #define FLL_STATIC_CFG_0_REG_FAST_CAL_WINDOW_VAL_WID                 ( 3)
  #define FLL_STATIC_CFG_0_REG_FAST_CAL_WINDOW_VAL_MSK                 (0x00000007)
  #define FLL_STATIC_CFG_0_REG_FAST_CAL_WINDOW_VAL_MIN                 (0)
  #define FLL_STATIC_CFG_0_REG_FAST_CAL_WINDOW_VAL_MAX                 (7) // 0x00000007
  #define FLL_STATIC_CFG_0_REG_FAST_CAL_WINDOW_VAL_DEF                 (0x00000001)
  #define FLL_STATIC_CFG_0_REG_FAST_CAL_WINDOW_VAL_HSH                 (0x03003504)

  #define FLL_STATIC_CFG_0_REG_SLOW_CAL_WINDOW_VAL_OFF                 ( 3)
  #define FLL_STATIC_CFG_0_REG_SLOW_CAL_WINDOW_VAL_WID                 ( 3)
  #define FLL_STATIC_CFG_0_REG_SLOW_CAL_WINDOW_VAL_MSK                 (0x00000038)
  #define FLL_STATIC_CFG_0_REG_SLOW_CAL_WINDOW_VAL_MIN                 (0)
  #define FLL_STATIC_CFG_0_REG_SLOW_CAL_WINDOW_VAL_MAX                 (7) // 0x00000007
  #define FLL_STATIC_CFG_0_REG_SLOW_CAL_WINDOW_VAL_DEF                 (0x00000002)
  #define FLL_STATIC_CFG_0_REG_SLOW_CAL_WINDOW_VAL_HSH                 (0x03063504)

  #define FLL_STATIC_CFG_0_REG_WAIT2FINALLOCK_SEL_OFF                  ( 6)
  #define FLL_STATIC_CFG_0_REG_WAIT2FINALLOCK_SEL_WID                  ( 2)
  #define FLL_STATIC_CFG_0_REG_WAIT2FINALLOCK_SEL_MSK                  (0x000000C0)
  #define FLL_STATIC_CFG_0_REG_WAIT2FINALLOCK_SEL_MIN                  (0)
  #define FLL_STATIC_CFG_0_REG_WAIT2FINALLOCK_SEL_MAX                  (3) // 0x00000003
  #define FLL_STATIC_CFG_0_REG_WAIT2FINALLOCK_SEL_DEF                  (0x00000000)
  #define FLL_STATIC_CFG_0_REG_WAIT2FINALLOCK_SEL_HSH                  (0x020C3504)

  #define FLL_STATIC_CFG_0_REG_SKIP_COARSE_CAL_OFF                     ( 8)
  #define FLL_STATIC_CFG_0_REG_SKIP_COARSE_CAL_WID                     ( 1)
  #define FLL_STATIC_CFG_0_REG_SKIP_COARSE_CAL_MSK                     (0x00000100)
  #define FLL_STATIC_CFG_0_REG_SKIP_COARSE_CAL_MIN                     (0)
  #define FLL_STATIC_CFG_0_REG_SKIP_COARSE_CAL_MAX                     (1) // 0x00000001
  #define FLL_STATIC_CFG_0_REG_SKIP_COARSE_CAL_DEF                     (0x00000000)
  #define FLL_STATIC_CFG_0_REG_SKIP_COARSE_CAL_HSH                     (0x01103504)

  #define FLL_STATIC_CFG_0_REG_FINE_CAL_ENABLE_OFF                     ( 9)
  #define FLL_STATIC_CFG_0_REG_FINE_CAL_ENABLE_WID                     ( 1)
  #define FLL_STATIC_CFG_0_REG_FINE_CAL_ENABLE_MSK                     (0x00000200)
  #define FLL_STATIC_CFG_0_REG_FINE_CAL_ENABLE_MIN                     (0)
  #define FLL_STATIC_CFG_0_REG_FINE_CAL_ENABLE_MAX                     (1) // 0x00000001
  #define FLL_STATIC_CFG_0_REG_FINE_CAL_ENABLE_DEF                     (0x00000001)
  #define FLL_STATIC_CFG_0_REG_FINE_CAL_ENABLE_HSH                     (0x01123504)

  #define FLL_STATIC_CFG_0_REG_RUNTIME_CAL_OFF                         (10)
  #define FLL_STATIC_CFG_0_REG_RUNTIME_CAL_WID                         ( 1)
  #define FLL_STATIC_CFG_0_REG_RUNTIME_CAL_MSK                         (0x00000400)
  #define FLL_STATIC_CFG_0_REG_RUNTIME_CAL_MIN                         (0)
  #define FLL_STATIC_CFG_0_REG_RUNTIME_CAL_MAX                         (1) // 0x00000001
  #define FLL_STATIC_CFG_0_REG_RUNTIME_CAL_DEF                         (0x00000001)
  #define FLL_STATIC_CFG_0_REG_RUNTIME_CAL_HSH                         (0x01143504)

  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_HI_OFF                       (11)
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_HI_WID                       ( 6)
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_HI_MSK                       (0x0001F800)
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_HI_MIN                       (0)
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_HI_MAX                       (63) // 0x0000003F
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_HI_DEF                       (0x00000003)
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_HI_HSH                       (0x06163504)

  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_LO_OFF                       (17)
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_LO_WID                       ( 6)
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_LO_MSK                       (0x007E0000)
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_LO_MIN                       (0)
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_LO_MAX                       (63) // 0x0000003F
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_LO_DEF                       (0x00000003)
  #define FLL_STATIC_CFG_0_REG_CAL_THRESH_LO_HSH                       (0x06223504)

  #define FLL_STATIC_CFG_0_REG_DCO_ON_IN_OFF_STATE_OFF                 (23)
  #define FLL_STATIC_CFG_0_REG_DCO_ON_IN_OFF_STATE_WID                 ( 1)
  #define FLL_STATIC_CFG_0_REG_DCO_ON_IN_OFF_STATE_MSK                 (0x00800000)
  #define FLL_STATIC_CFG_0_REG_DCO_ON_IN_OFF_STATE_MIN                 (0)
  #define FLL_STATIC_CFG_0_REG_DCO_ON_IN_OFF_STATE_MAX                 (1) // 0x00000001
  #define FLL_STATIC_CFG_0_REG_DCO_ON_IN_OFF_STATE_DEF                 (0x00000000)
  #define FLL_STATIC_CFG_0_REG_DCO_ON_IN_OFF_STATE_HSH                 (0x012E3504)

  #define FLL_STATIC_CFG_0_REG_COARSE_CAL_TIME_SEL_OFF                 (24)
  #define FLL_STATIC_CFG_0_REG_COARSE_CAL_TIME_SEL_WID                 ( 3)
  #define FLL_STATIC_CFG_0_REG_COARSE_CAL_TIME_SEL_MSK                 (0x07000000)
  #define FLL_STATIC_CFG_0_REG_COARSE_CAL_TIME_SEL_MIN                 (0)
  #define FLL_STATIC_CFG_0_REG_COARSE_CAL_TIME_SEL_MAX                 (7) // 0x00000007
  #define FLL_STATIC_CFG_0_REG_COARSE_CAL_TIME_SEL_DEF                 (0x00000000)
  #define FLL_STATIC_CFG_0_REG_COARSE_CAL_TIME_SEL_HSH                 (0x03303504)

  #define FLL_STATIC_CFG_0_REG_ISOLATION_MODE_ON_OFF                   (27)
  #define FLL_STATIC_CFG_0_REG_ISOLATION_MODE_ON_WID                   ( 1)
  #define FLL_STATIC_CFG_0_REG_ISOLATION_MODE_ON_MSK                   (0x08000000)
  #define FLL_STATIC_CFG_0_REG_ISOLATION_MODE_ON_MIN                   (0)
  #define FLL_STATIC_CFG_0_REG_ISOLATION_MODE_ON_MAX                   (1) // 0x00000001
  #define FLL_STATIC_CFG_0_REG_ISOLATION_MODE_ON_DEF                   (0x00000000)
  #define FLL_STATIC_CFG_0_REG_ISOLATION_MODE_ON_HSH                   (0x01363504)

  #define FLL_STATIC_CFG_0_REG_LDO_VREFSEL_OFF                         (28)
  #define FLL_STATIC_CFG_0_REG_LDO_VREFSEL_WID                         ( 4)
  #define FLL_STATIC_CFG_0_REG_LDO_VREFSEL_MSK                         (0xF0000000)
  #define FLL_STATIC_CFG_0_REG_LDO_VREFSEL_MIN                         (0)
  #define FLL_STATIC_CFG_0_REG_LDO_VREFSEL_MAX                         (15) // 0x0000000F
  #define FLL_STATIC_CFG_0_REG_LDO_VREFSEL_DEF                         (0x00000004)
  #define FLL_STATIC_CFG_0_REG_LDO_VREFSEL_HSH                         (0x04383504)

#define FLL_STATIC_CFG_1_REG_REG                                       (0x00003508)

  #define FLL_STATIC_CFG_1_REG_COARSECAL_CNTR_EN_OFF                   ( 0)
  #define FLL_STATIC_CFG_1_REG_COARSECAL_CNTR_EN_WID                   ( 4)
  #define FLL_STATIC_CFG_1_REG_COARSECAL_CNTR_EN_MSK                   (0x0000000F)
  #define FLL_STATIC_CFG_1_REG_COARSECAL_CNTR_EN_MIN                   (0)
  #define FLL_STATIC_CFG_1_REG_COARSECAL_CNTR_EN_MAX                   (15) // 0x0000000F
  #define FLL_STATIC_CFG_1_REG_COARSECAL_CNTR_EN_DEF                   (0x0000000F)
  #define FLL_STATIC_CFG_1_REG_COARSECAL_CNTR_EN_HSH                   (0x04003508)

  #define FLL_STATIC_CFG_1_REG_FINECAL_CNTR_EN_OFF                     ( 4)
  #define FLL_STATIC_CFG_1_REG_FINECAL_CNTR_EN_WID                     ( 4)
  #define FLL_STATIC_CFG_1_REG_FINECAL_CNTR_EN_MSK                     (0x000000F0)
  #define FLL_STATIC_CFG_1_REG_FINECAL_CNTR_EN_MIN                     (0)
  #define FLL_STATIC_CFG_1_REG_FINECAL_CNTR_EN_MAX                     (15) // 0x0000000F
  #define FLL_STATIC_CFG_1_REG_FINECAL_CNTR_EN_DEF                     (0x00000002)
  #define FLL_STATIC_CFG_1_REG_FINECAL_CNTR_EN_HSH                     (0x04083508)

  #define FLL_STATIC_CFG_1_REG_DELAY_FLLENABLE_OFF                     ( 8)
  #define FLL_STATIC_CFG_1_REG_DELAY_FLLENABLE_WID                     ( 3)
  #define FLL_STATIC_CFG_1_REG_DELAY_FLLENABLE_MSK                     (0x00000700)
  #define FLL_STATIC_CFG_1_REG_DELAY_FLLENABLE_MIN                     (0)
  #define FLL_STATIC_CFG_1_REG_DELAY_FLLENABLE_MAX                     (7) // 0x00000007
  #define FLL_STATIC_CFG_1_REG_DELAY_FLLENABLE_DEF                     (0x00000003)
  #define FLL_STATIC_CFG_1_REG_DELAY_FLLENABLE_HSH                     (0x03103508)

  #define FLL_STATIC_CFG_1_REG_RCOMPENSATION_CFG_OFF                   (11)
  #define FLL_STATIC_CFG_1_REG_RCOMPENSATION_CFG_WID                   ( 2)
  #define FLL_STATIC_CFG_1_REG_RCOMPENSATION_CFG_MSK                   (0x00001800)
  #define FLL_STATIC_CFG_1_REG_RCOMPENSATION_CFG_MIN                   (0)
  #define FLL_STATIC_CFG_1_REG_RCOMPENSATION_CFG_MAX                   (3) // 0x00000003
  #define FLL_STATIC_CFG_1_REG_RCOMPENSATION_CFG_DEF                   (0x00000003)
  #define FLL_STATIC_CFG_1_REG_RCOMPENSATION_CFG_HSH                   (0x02163508)

  #define FLL_STATIC_CFG_1_REG_REFCLK_DIVIDE_RATIO_SEL_OFF             (13)
  #define FLL_STATIC_CFG_1_REG_REFCLK_DIVIDE_RATIO_SEL_WID             ( 2)
  #define FLL_STATIC_CFG_1_REG_REFCLK_DIVIDE_RATIO_SEL_MSK             (0x00006000)
  #define FLL_STATIC_CFG_1_REG_REFCLK_DIVIDE_RATIO_SEL_MIN             (0)
  #define FLL_STATIC_CFG_1_REG_REFCLK_DIVIDE_RATIO_SEL_MAX             (3) // 0x00000003
  #define FLL_STATIC_CFG_1_REG_REFCLK_DIVIDE_RATIO_SEL_DEF             (0x00000001)
  #define FLL_STATIC_CFG_1_REG_REFCLK_DIVIDE_RATIO_SEL_HSH             (0x021A3508)

  #define FLL_STATIC_CFG_1_REG_COMPUTE_LENGTH_SEL_OFF                  (15)
  #define FLL_STATIC_CFG_1_REG_COMPUTE_LENGTH_SEL_WID                  ( 2)
  #define FLL_STATIC_CFG_1_REG_COMPUTE_LENGTH_SEL_MSK                  (0x00018000)
  #define FLL_STATIC_CFG_1_REG_COMPUTE_LENGTH_SEL_MIN                  (0)
  #define FLL_STATIC_CFG_1_REG_COMPUTE_LENGTH_SEL_MAX                  (3) // 0x00000003
  #define FLL_STATIC_CFG_1_REG_COMPUTE_LENGTH_SEL_DEF                  (0x00000000)
  #define FLL_STATIC_CFG_1_REG_COMPUTE_LENGTH_SEL_HSH                  (0x021E3508)

  #define FLL_STATIC_CFG_1_REG_DAC_SETTLE_LENGTH_SEL_OFF               (17)
  #define FLL_STATIC_CFG_1_REG_DAC_SETTLE_LENGTH_SEL_WID               ( 2)
  #define FLL_STATIC_CFG_1_REG_DAC_SETTLE_LENGTH_SEL_MSK               (0x00060000)
  #define FLL_STATIC_CFG_1_REG_DAC_SETTLE_LENGTH_SEL_MIN               (0)
  #define FLL_STATIC_CFG_1_REG_DAC_SETTLE_LENGTH_SEL_MAX               (3) // 0x00000003
  #define FLL_STATIC_CFG_1_REG_DAC_SETTLE_LENGTH_SEL_DEF               (0x00000000)
  #define FLL_STATIC_CFG_1_REG_DAC_SETTLE_LENGTH_SEL_HSH               (0x02223508)

  #define FLL_STATIC_CFG_1_REG_MISC_CFG_OFF                            (19)
  #define FLL_STATIC_CFG_1_REG_MISC_CFG_WID                            ( 3)
  #define FLL_STATIC_CFG_1_REG_MISC_CFG_MSK                            (0x00380000)
  #define FLL_STATIC_CFG_1_REG_MISC_CFG_MIN                            (0)
  #define FLL_STATIC_CFG_1_REG_MISC_CFG_MAX                            (7) // 0x00000007
  #define FLL_STATIC_CFG_1_REG_MISC_CFG_DEF                            (0x00000000)
  #define FLL_STATIC_CFG_1_REG_MISC_CFG_HSH                            (0x03263508)

  #define FLL_STATIC_CFG_1_REG_VREFSEL_FASTRAMP_OFF                    (22)
  #define FLL_STATIC_CFG_1_REG_VREFSEL_FASTRAMP_WID                    ( 4)
  #define FLL_STATIC_CFG_1_REG_VREFSEL_FASTRAMP_MSK                    (0x03C00000)
  #define FLL_STATIC_CFG_1_REG_VREFSEL_FASTRAMP_MIN                    (0)
  #define FLL_STATIC_CFG_1_REG_VREFSEL_FASTRAMP_MAX                    (15) // 0x0000000F
  #define FLL_STATIC_CFG_1_REG_VREFSEL_FASTRAMP_DEF                    (0x00000000)
  #define FLL_STATIC_CFG_1_REG_VREFSEL_FASTRAMP_HSH                    (0x042C3508)

  #define FLL_STATIC_CFG_1_REG_VSUPPLY_CFG_OFF                         (26)
  #define FLL_STATIC_CFG_1_REG_VSUPPLY_CFG_WID                         ( 2)
  #define FLL_STATIC_CFG_1_REG_VSUPPLY_CFG_MSK                         (0x0C000000)
  #define FLL_STATIC_CFG_1_REG_VSUPPLY_CFG_MIN                         (0)
  #define FLL_STATIC_CFG_1_REG_VSUPPLY_CFG_MAX                         (3) // 0x00000003
  #define FLL_STATIC_CFG_1_REG_VSUPPLY_CFG_DEF                         (0x00000000)
  #define FLL_STATIC_CFG_1_REG_VSUPPLY_CFG_HSH                         (0x02343508)

  #define FLL_STATIC_CFG_1_REG_REFCLK_INPUT_CLKGATE_OVRD_OFF           (28)
  #define FLL_STATIC_CFG_1_REG_REFCLK_INPUT_CLKGATE_OVRD_WID           ( 1)
  #define FLL_STATIC_CFG_1_REG_REFCLK_INPUT_CLKGATE_OVRD_MSK           (0x10000000)
  #define FLL_STATIC_CFG_1_REG_REFCLK_INPUT_CLKGATE_OVRD_MIN           (0)
  #define FLL_STATIC_CFG_1_REG_REFCLK_INPUT_CLKGATE_OVRD_MAX           (1) // 0x00000001
  #define FLL_STATIC_CFG_1_REG_REFCLK_INPUT_CLKGATE_OVRD_DEF           (0x00000000)
  #define FLL_STATIC_CFG_1_REG_REFCLK_INPUT_CLKGATE_OVRD_HSH           (0x01383508)

  #define FLL_STATIC_CFG_1_REG_SEQUENCE_FSM_CLKGATE_OVRD_OFF           (29)
  #define FLL_STATIC_CFG_1_REG_SEQUENCE_FSM_CLKGATE_OVRD_WID           ( 1)
  #define FLL_STATIC_CFG_1_REG_SEQUENCE_FSM_CLKGATE_OVRD_MSK           (0x20000000)
  #define FLL_STATIC_CFG_1_REG_SEQUENCE_FSM_CLKGATE_OVRD_MIN           (0)
  #define FLL_STATIC_CFG_1_REG_SEQUENCE_FSM_CLKGATE_OVRD_MAX           (1) // 0x00000001
  #define FLL_STATIC_CFG_1_REG_SEQUENCE_FSM_CLKGATE_OVRD_DEF           (0x00000000)
  #define FLL_STATIC_CFG_1_REG_SEQUENCE_FSM_CLKGATE_OVRD_HSH           (0x013A3508)

  #define FLL_STATIC_CFG_1_REG_REQACK_FSM_CLKGATE_OVRD_OFF             (30)
  #define FLL_STATIC_CFG_1_REG_REQACK_FSM_CLKGATE_OVRD_WID             ( 1)
  #define FLL_STATIC_CFG_1_REG_REQACK_FSM_CLKGATE_OVRD_MSK             (0x40000000)
  #define FLL_STATIC_CFG_1_REG_REQACK_FSM_CLKGATE_OVRD_MIN             (0)
  #define FLL_STATIC_CFG_1_REG_REQACK_FSM_CLKGATE_OVRD_MAX             (1) // 0x00000001
  #define FLL_STATIC_CFG_1_REG_REQACK_FSM_CLKGATE_OVRD_DEF             (0x00000000)
  #define FLL_STATIC_CFG_1_REG_REQACK_FSM_CLKGATE_OVRD_HSH             (0x013C3508)

  #define FLL_STATIC_CFG_1_REG_DCO_CODE_UPDATE_CLKGATE_OVRD_OFF        (31)
  #define FLL_STATIC_CFG_1_REG_DCO_CODE_UPDATE_CLKGATE_OVRD_WID        ( 1)
  #define FLL_STATIC_CFG_1_REG_DCO_CODE_UPDATE_CLKGATE_OVRD_MSK        (0x80000000)
  #define FLL_STATIC_CFG_1_REG_DCO_CODE_UPDATE_CLKGATE_OVRD_MIN        (0)
  #define FLL_STATIC_CFG_1_REG_DCO_CODE_UPDATE_CLKGATE_OVRD_MAX        (1) // 0x00000001
  #define FLL_STATIC_CFG_1_REG_DCO_CODE_UPDATE_CLKGATE_OVRD_DEF        (0x00000000)
  #define FLL_STATIC_CFG_1_REG_DCO_CODE_UPDATE_CLKGATE_OVRD_HSH        (0x013E3508)

#define FLL_DEBUG_CFG_REG_REG                                          (0x0000350C)

  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_OFF                       ( 0)
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_WID                       ( 1)
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_MSK                       (0x00000001)
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_MIN                       (0)
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_MAX                       (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_DEF                       (0x00000000)
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_HSH                       (0x0100350C)

  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_EN_OFF                    ( 1)
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_EN_WID                    ( 1)
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_EN_MSK                    (0x00000002)
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_EN_MIN                    (0)
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_EN_MAX                    (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_EN_DEF                    (0x00000000)
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_EN_HSH                    (0x0102350C)

  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_EN_OFF                    ( 2)
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_EN_WID                    ( 1)
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_EN_MSK                    (0x00000004)
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_EN_MIN                    (0)
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_EN_MAX                    (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_EN_DEF                    (0x00000000)
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_EN_HSH                    (0x0104350C)

  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_EN_OFF            ( 3)
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_EN_WID            ( 1)
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_EN_MSK            (0x00000008)
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_EN_MIN            (0)
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_EN_MAX            (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_EN_DEF            (0x00000000)
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_EN_HSH            (0x0106350C)

  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_EN_OFF                 ( 4)
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_EN_WID                 ( 1)
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_EN_MSK                 (0x00000010)
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_EN_MIN                 (0)
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_EN_MAX                 (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_EN_DEF                 (0x00000000)
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_EN_HSH                 (0x0108350C)

  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH0_OFF                     ( 5)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH0_WID                     ( 1)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH0_MSK                     (0x00000020)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH0_MIN                     (0)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH0_MAX                     (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH0_DEF                     (0x00000000)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH0_HSH                     (0x010A350C)

  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH1_OFF                     ( 6)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH1_WID                     ( 1)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH1_MSK                     (0x00000040)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH1_MIN                     (0)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH1_MAX                     (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH1_DEF                     (0x00000000)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_DFX_EN_CH1_HSH                     (0x010C350C)

  #define FLL_DEBUG_CFG_REG_VIEWANA_SEL_OFF                            ( 7)
  #define FLL_DEBUG_CFG_REG_VIEWANA_SEL_WID                            ( 4)
  #define FLL_DEBUG_CFG_REG_VIEWANA_SEL_MSK                            (0x00000780)
  #define FLL_DEBUG_CFG_REG_VIEWANA_SEL_MIN                            (0)
  #define FLL_DEBUG_CFG_REG_VIEWANA_SEL_MAX                            (15) // 0x0000000F
  #define FLL_DEBUG_CFG_REG_VIEWANA_SEL_DEF                            (0x00000000)
  #define FLL_DEBUG_CFG_REG_VIEWANA_SEL_HSH                            (0x040E350C)

  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH0_OFF                        (11)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH0_WID                        ( 4)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH0_MSK                        (0x00007800)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH0_MIN                        (0)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH0_MAX                        (15) // 0x0000000F
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH0_DEF                        (0x00000000)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH0_HSH                        (0x0416350C)

  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH1_OFF                        (15)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH1_WID                        ( 4)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH1_MSK                        (0x00078000)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH1_MIN                        (0)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH1_MAX                        (15) // 0x0000000F
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH1_DEF                        (0x00000000)
  #define FLL_DEBUG_CFG_REG_VIEWDIG_SEL_CH1_HSH                        (0x041E350C)

  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_EN_OFF                    (19)
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_EN_WID                    ( 1)
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_EN_MSK                    (0x00080000)
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_EN_MIN                    (0)
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_EN_MAX                    (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_EN_DEF                    (0x00000000)
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_EN_HSH                    (0x0126350C)

  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_TRIGGER_OFF               (20)
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_TRIGGER_WID               ( 1)
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_TRIGGER_MSK               (0x00100000)
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_TRIGGER_MIN               (0)
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_TRIGGER_MAX               (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_TRIGGER_DEF               (0x00000000)
  #define FLL_DEBUG_CFG_REG_SINGLE_STEP_MODE_TRIGGER_HSH               (0x0128350C)

  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_0_OFF                         (21)
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_0_WID                         ( 3)
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_0_MSK                         (0x00E00000)
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_0_MIN                         (0)
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_0_MAX                         (7) // 0x00000007
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_0_DEF                         (0x00000000)
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_0_HSH                         (0x032A350C)

  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_EN_OFF                    (24)
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_EN_WID                    ( 1)
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_EN_MSK                    (0x01000000)
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_EN_MIN                    (0)
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_EN_MAX                    (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_EN_DEF                    (0x00000000)
  #define FLL_DEBUG_CFG_REG_FLL_CORE_EN_OVRD_EN_HSH                    (0x0130350C)

  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_OFF                       (25)
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_WID                       ( 1)
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_MSK                       (0x02000000)
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_MIN                       (0)
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_MAX                       (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_DEF                       (0x00000000)
  #define FLL_DEBUG_CFG_REG_REG_WR_DONE_OVRD_HSH                       (0x0132350C)

  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_OFF                       (26)
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_WID                       ( 1)
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_MSK                       (0x04000000)
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_MIN                       (0)
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_MAX                       (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_DEF                       (0x00000000)
  #define FLL_DEBUG_CFG_REG_HV_PWR_GOOD_OVRD_HSH                       (0x0134350C)

  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_OFF               (27)
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_WID               ( 1)
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_MSK               (0x08000000)
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_MIN               (0)
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_MAX               (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_DEF               (0x00000000)
  #define FLL_DEBUG_CFG_REG_DLY_COUNTERS_BYPASS_OVRD_HSH               (0x0136350C)

  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_OFF                    (28)
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_WID                    ( 1)
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_MSK                    (0x10000000)
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_MIN                    (0)
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_MAX                    (1) // 0x00000001
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_DEF                    (0x00000000)
  #define FLL_DEBUG_CFG_REG_NODELAY_FLL_EN_OVRD_HSH                    (0x0138350C)

  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_1_OFF                         (29)
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_1_WID                         ( 3)
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_1_MSK                         (0xE0000000)
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_1_MIN                         (0)
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_1_MAX                         (7) // 0x00000007
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_1_DEF                         (0x00000000)
  #define FLL_DEBUG_CFG_REG_RESERVED_DBG_1_HSH                         (0x033A350C)

#define FLL_DYNAMIC_CFG_REG_REG                                        (0x00003510)

  #define FLL_DYNAMIC_CFG_REG_VBIAS_CODE_2FLLCORE_OVRD_OFF             ( 0)
  #define FLL_DYNAMIC_CFG_REG_VBIAS_CODE_2FLLCORE_OVRD_WID             (16)
  #define FLL_DYNAMIC_CFG_REG_VBIAS_CODE_2FLLCORE_OVRD_MSK             (0x0000FFFF)
  #define FLL_DYNAMIC_CFG_REG_VBIAS_CODE_2FLLCORE_OVRD_MIN             (0)
  #define FLL_DYNAMIC_CFG_REG_VBIAS_CODE_2FLLCORE_OVRD_MAX             (65535) // 0x0000FFFF
  #define FLL_DYNAMIC_CFG_REG_VBIAS_CODE_2FLLCORE_OVRD_DEF             (0x00000000)
  #define FLL_DYNAMIC_CFG_REG_VBIAS_CODE_2FLLCORE_OVRD_HSH             (0x10003510)

  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_ON_OFF                      (16)
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_ON_WID                      ( 1)
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_ON_MSK                      (0x00010000)
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_ON_MIN                      (0)
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_ON_MAX                      (1) // 0x00000001
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_ON_DEF                      (0x00000000)
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_ON_HSH                      (0x01203510)

  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_OFF_OFF                     (17)
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_OFF_WID                     ( 1)
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_OFF_MSK                     (0x00020000)
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_OFF_MIN                     (0)
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_OFF_MAX                     (1) // 0x00000001
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_OFF_DEF                     (0x00000000)
  #define FLL_DYNAMIC_CFG_REG_FORCE_OUTCLK_OFF_HSH                     (0x01223510)

  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_0_OFF                       (18)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_0_WID                       ( 4)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_0_MSK                       (0x003C0000)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_0_MIN                       (0)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_0_MAX                       (15) // 0x0000000F
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_0_DEF                       (0x00000000)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_0_HSH                       (0x04243510)

  #define FLL_DYNAMIC_CFG_REG_CAL_CODE_VALID_REG_OFF                   (22)
  #define FLL_DYNAMIC_CFG_REG_CAL_CODE_VALID_REG_WID                   ( 1)
  #define FLL_DYNAMIC_CFG_REG_CAL_CODE_VALID_REG_MSK                   (0x00400000)
  #define FLL_DYNAMIC_CFG_REG_CAL_CODE_VALID_REG_MIN                   (0)
  #define FLL_DYNAMIC_CFG_REG_CAL_CODE_VALID_REG_MAX                   (1) // 0x00000001
  #define FLL_DYNAMIC_CFG_REG_CAL_CODE_VALID_REG_DEF                   (0x00000000)
  #define FLL_DYNAMIC_CFG_REG_CAL_CODE_VALID_REG_HSH                   (0x012C3510)

  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_2_OFF                       (23)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_2_WID                       ( 1)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_2_MSK                       (0x00800000)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_2_MIN                       (0)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_2_MAX                       (1) // 0x00000001
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_2_DEF                       (0x00000000)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_2_HSH                       (0x012E3510)

  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_3_OFF                       (24)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_3_WID                       ( 1)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_3_MSK                       (0x01000000)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_3_MIN                       (0)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_3_MAX                       (1) // 0x00000001
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_3_DEF                       (0x00000000)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_3_HSH                       (0x01303510)

  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_1_OFF                       (25)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_1_WID                       ( 7)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_1_MSK                       (0xFE000000)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_1_MIN                       (0)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_1_MAX                       (127) // 0x0000007F
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_1_DEF                       (0x00000000)
  #define FLL_DYNAMIC_CFG_REG_RESERVED_DYN_1_HSH                       (0x07323510)

#define FLL_EXTIP_STAT_REG_REG                                         (0x00003514)

  #define FLL_EXTIP_STAT_REG_FLL_ENABLE_OFF                            ( 0)
  #define FLL_EXTIP_STAT_REG_FLL_ENABLE_WID                            ( 1)
  #define FLL_EXTIP_STAT_REG_FLL_ENABLE_MSK                            (0x00000001)
  #define FLL_EXTIP_STAT_REG_FLL_ENABLE_MIN                            (0)
  #define FLL_EXTIP_STAT_REG_FLL_ENABLE_MAX                            (1) // 0x00000001
  #define FLL_EXTIP_STAT_REG_FLL_ENABLE_DEF                            (0x00000000)
  #define FLL_EXTIP_STAT_REG_FLL_ENABLE_HSH                            (0x01003514)

  #define FLL_EXTIP_STAT_REG_DIST_RESET_B_OFF                          ( 1)
  #define FLL_EXTIP_STAT_REG_DIST_RESET_B_WID                          ( 1)
  #define FLL_EXTIP_STAT_REG_DIST_RESET_B_MSK                          (0x00000002)
  #define FLL_EXTIP_STAT_REG_DIST_RESET_B_MIN                          (0)
  #define FLL_EXTIP_STAT_REG_DIST_RESET_B_MAX                          (1) // 0x00000001
  #define FLL_EXTIP_STAT_REG_DIST_RESET_B_DEF                          (0x00000000)
  #define FLL_EXTIP_STAT_REG_DIST_RESET_B_HSH                          (0x01023514)

  #define FLL_EXTIP_STAT_REG_FLL_EARLY_LOCK_OFF                        ( 2)
  #define FLL_EXTIP_STAT_REG_FLL_EARLY_LOCK_WID                        ( 1)
  #define FLL_EXTIP_STAT_REG_FLL_EARLY_LOCK_MSK                        (0x00000004)
  #define FLL_EXTIP_STAT_REG_FLL_EARLY_LOCK_MIN                        (0)
  #define FLL_EXTIP_STAT_REG_FLL_EARLY_LOCK_MAX                        (1) // 0x00000001
  #define FLL_EXTIP_STAT_REG_FLL_EARLY_LOCK_DEF                        (0x00000000)
  #define FLL_EXTIP_STAT_REG_FLL_EARLY_LOCK_HSH                        (0x01043514)

  #define FLL_EXTIP_STAT_REG_FLL_FINAL_LOCK_OFF                        ( 3)
  #define FLL_EXTIP_STAT_REG_FLL_FINAL_LOCK_WID                        ( 1)
  #define FLL_EXTIP_STAT_REG_FLL_FINAL_LOCK_MSK                        (0x00000008)
  #define FLL_EXTIP_STAT_REG_FLL_FINAL_LOCK_MIN                        (0)
  #define FLL_EXTIP_STAT_REG_FLL_FINAL_LOCK_MAX                        (1) // 0x00000001
  #define FLL_EXTIP_STAT_REG_FLL_FINAL_LOCK_DEF                        (0x00000000)
  #define FLL_EXTIP_STAT_REG_FLL_FINAL_LOCK_HSH                        (0x01063514)

  #define FLL_EXTIP_STAT_REG_RAMP_DONE_OFF                             ( 4)
  #define FLL_EXTIP_STAT_REG_RAMP_DONE_WID                             ( 1)
  #define FLL_EXTIP_STAT_REG_RAMP_DONE_MSK                             (0x00000010)
  #define FLL_EXTIP_STAT_REG_RAMP_DONE_MIN                             (0)
  #define FLL_EXTIP_STAT_REG_RAMP_DONE_MAX                             (1) // 0x00000001
  #define FLL_EXTIP_STAT_REG_RAMP_DONE_DEF                             (0x00000000)
  #define FLL_EXTIP_STAT_REG_RAMP_DONE_HSH                             (0x01083514)

  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_REQ_OFF                       ( 5)
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_REQ_WID                       ( 1)
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_REQ_MSK                       (0x00000020)
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_REQ_MIN                       (0)
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_REQ_MAX                       (1) // 0x00000001
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_REQ_DEF                       (0x00000000)
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_REQ_HSH                       (0x010A3514)

  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_DONE_OFF                      ( 6)
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_DONE_WID                      ( 1)
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_DONE_MSK                      (0x00000040)
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_DONE_MIN                      (0)
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_DONE_MAX                      (1) // 0x00000001
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_DONE_DEF                      (0x00000000)
  #define FLL_EXTIP_STAT_REG_FREQ_CHANGE_DONE_HSH                      (0x010C3514)

  #define FLL_EXTIP_STAT_REG_REG_WRITES_DONE_OFF                       ( 7)
  #define FLL_EXTIP_STAT_REG_REG_WRITES_DONE_WID                       ( 1)
  #define FLL_EXTIP_STAT_REG_REG_WRITES_DONE_MSK                       (0x00000080)
  #define FLL_EXTIP_STAT_REG_REG_WRITES_DONE_MIN                       (0)
  #define FLL_EXTIP_STAT_REG_REG_WRITES_DONE_MAX                       (1) // 0x00000001
  #define FLL_EXTIP_STAT_REG_REG_WRITES_DONE_DEF                       (0x00000000)
  #define FLL_EXTIP_STAT_REG_REG_WRITES_DONE_HSH                       (0x010E3514)

  #define FLL_EXTIP_STAT_REG_VBIAS_CODE_2FLLCORE_OFF                   ( 8)
  #define FLL_EXTIP_STAT_REG_VBIAS_CODE_2FLLCORE_WID                   (16)
  #define FLL_EXTIP_STAT_REG_VBIAS_CODE_2FLLCORE_MSK                   (0x00FFFF00)
  #define FLL_EXTIP_STAT_REG_VBIAS_CODE_2FLLCORE_MIN                   (0)
  #define FLL_EXTIP_STAT_REG_VBIAS_CODE_2FLLCORE_MAX                   (65535) // 0x0000FFFF
  #define FLL_EXTIP_STAT_REG_VBIAS_CODE_2FLLCORE_DEF                   (0x00000000)
  #define FLL_EXTIP_STAT_REG_VBIAS_CODE_2FLLCORE_HSH                   (0x10103514)

  #define FLL_EXTIP_STAT_REG_FLL_RATIO_OFF                             (24)
  #define FLL_EXTIP_STAT_REG_FLL_RATIO_WID                             ( 8)
  #define FLL_EXTIP_STAT_REG_FLL_RATIO_MSK                             (0xFF000000)
  #define FLL_EXTIP_STAT_REG_FLL_RATIO_MIN                             (0)
  #define FLL_EXTIP_STAT_REG_FLL_RATIO_MAX                             (255) // 0x000000FF
  #define FLL_EXTIP_STAT_REG_FLL_RATIO_DEF                             (0x00000000)
  #define FLL_EXTIP_STAT_REG_FLL_RATIO_HSH                             (0x08303514)

#define FLL_DIAG_STAT_REG_REG                                          (0x00003518)

  #define FLL_DIAG_STAT_REG_FLL_REFCLK_REQ_OFF                         ( 0)
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_REQ_WID                         ( 1)
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_REQ_MSK                         (0x00000001)
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_REQ_MIN                         (0)
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_REQ_MAX                         (1) // 0x00000001
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_REQ_DEF                         (0x00000000)
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_REQ_HSH                         (0x01003518)

  #define FLL_DIAG_STAT_REG_FLL_REFCLK_ACK_OFF                         ( 1)
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_ACK_WID                         ( 1)
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_ACK_MSK                         (0x00000002)
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_ACK_MIN                         (0)
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_ACK_MAX                         (1) // 0x00000001
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_ACK_DEF                         (0x00000000)
  #define FLL_DIAG_STAT_REG_FLL_REFCLK_ACK_HSH                         (0x01023518)

  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_REQ_OFF                         ( 2)
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_REQ_WID                         ( 1)
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_REQ_MSK                         (0x00000004)
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_REQ_MIN                         (0)
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_REQ_MAX                         (1) // 0x00000001
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_REQ_DEF                         (0x00000000)
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_REQ_HSH                         (0x01043518)

  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_ACK_OFF                         ( 3)
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_ACK_WID                         ( 1)
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_ACK_MSK                         (0x00000008)
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_ACK_MIN                         (0)
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_ACK_MAX                         (1) // 0x00000001
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_ACK_DEF                         (0x00000000)
  #define FLL_DIAG_STAT_REG_FLL_OUTCLK_ACK_HSH                         (0x01063518)

  #define FLL_DIAG_STAT_REG_FLL_COUNTER_ERR_OFF                        ( 4)
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_ERR_WID                        (12)
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_ERR_MSK                        (0x0000FFF0)
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_ERR_MIN                        (-2048)
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_ERR_MAX                        (2047) // 0x000007FF
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_ERR_DEF                        (0x00000000)
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_ERR_HSH                        (0x8C083518)

  #define FLL_DIAG_STAT_REG_FLL_COUNTER_SUM_OFF                        (16)
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_SUM_WID                        (12)
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_SUM_MSK                        (0x0FFF0000)
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_SUM_MIN                        (0)
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_SUM_MAX                        (4095) // 0x00000FFF
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_SUM_DEF                        (0x00000000)
  #define FLL_DIAG_STAT_REG_FLL_COUNTER_SUM_HSH                        (0x0C203518)

  #define FLL_DIAG_STAT_REG_HV_PWR_GOOD_OFF                            (28)
  #define FLL_DIAG_STAT_REG_HV_PWR_GOOD_WID                            ( 1)
  #define FLL_DIAG_STAT_REG_HV_PWR_GOOD_MSK                            (0x10000000)
  #define FLL_DIAG_STAT_REG_HV_PWR_GOOD_MIN                            (0)
  #define FLL_DIAG_STAT_REG_HV_PWR_GOOD_MAX                            (1) // 0x00000001
  #define FLL_DIAG_STAT_REG_HV_PWR_GOOD_DEF                            (0x00000000)
  #define FLL_DIAG_STAT_REG_HV_PWR_GOOD_HSH                            (0x01383518)

  #define FLL_DIAG_STAT_REG_LDOEN_DLY_CNTR_DONE_OFF                    (29)
  #define FLL_DIAG_STAT_REG_LDOEN_DLY_CNTR_DONE_WID                    ( 1)
  #define FLL_DIAG_STAT_REG_LDOEN_DLY_CNTR_DONE_MSK                    (0x20000000)
  #define FLL_DIAG_STAT_REG_LDOEN_DLY_CNTR_DONE_MIN                    (0)
  #define FLL_DIAG_STAT_REG_LDOEN_DLY_CNTR_DONE_MAX                    (1) // 0x00000001
  #define FLL_DIAG_STAT_REG_LDOEN_DLY_CNTR_DONE_DEF                    (0x00000000)
  #define FLL_DIAG_STAT_REG_LDOEN_DLY_CNTR_DONE_HSH                    (0x013A3518)

  #define FLL_DIAG_STAT_REG_FASTRAMPDONE_CNTR_DONE_OFF                 (30)
  #define FLL_DIAG_STAT_REG_FASTRAMPDONE_CNTR_DONE_WID                 ( 1)
  #define FLL_DIAG_STAT_REG_FASTRAMPDONE_CNTR_DONE_MSK                 (0x40000000)
  #define FLL_DIAG_STAT_REG_FASTRAMPDONE_CNTR_DONE_MIN                 (0)
  #define FLL_DIAG_STAT_REG_FASTRAMPDONE_CNTR_DONE_MAX                 (1) // 0x00000001
  #define FLL_DIAG_STAT_REG_FASTRAMPDONE_CNTR_DONE_DEF                 (0x00000000)
  #define FLL_DIAG_STAT_REG_FASTRAMPDONE_CNTR_DONE_HSH                 (0x013C3518)

  #define FLL_DIAG_STAT_REG_LDO_RAMP_TIMER_DONE_OFF                    (31)
  #define FLL_DIAG_STAT_REG_LDO_RAMP_TIMER_DONE_WID                    ( 1)
  #define FLL_DIAG_STAT_REG_LDO_RAMP_TIMER_DONE_MSK                    (0x80000000)
  #define FLL_DIAG_STAT_REG_LDO_RAMP_TIMER_DONE_MIN                    (0)
  #define FLL_DIAG_STAT_REG_LDO_RAMP_TIMER_DONE_MAX                    (1) // 0x00000001
  #define FLL_DIAG_STAT_REG_LDO_RAMP_TIMER_DONE_DEF                    (0x00000000)
  #define FLL_DIAG_STAT_REG_LDO_RAMP_TIMER_DONE_HSH                    (0x013E3518)

#define FLL_DIAG_STAT_1_REG_REG                                        (0x0000351C)

  #define FLL_DIAG_STAT_1_REG_FLL_COUNTER_OVF_OFF                      ( 0)
  #define FLL_DIAG_STAT_1_REG_FLL_COUNTER_OVF_WID                      (10)
  #define FLL_DIAG_STAT_1_REG_FLL_COUNTER_OVF_MSK                      (0x000003FF)
  #define FLL_DIAG_STAT_1_REG_FLL_COUNTER_OVF_MIN                      (0)
  #define FLL_DIAG_STAT_1_REG_FLL_COUNTER_OVF_MAX                      (1023) // 0x000003FF
  #define FLL_DIAG_STAT_1_REG_FLL_COUNTER_OVF_DEF                      (0x00000000)
  #define FLL_DIAG_STAT_1_REG_FLL_COUNTER_OVF_HSH                      (0x0A00351C)

  #define FLL_DIAG_STAT_1_REG_COUNTER_OVERFLOW_STICKY_OFF              (10)
  #define FLL_DIAG_STAT_1_REG_COUNTER_OVERFLOW_STICKY_WID              ( 1)
  #define FLL_DIAG_STAT_1_REG_COUNTER_OVERFLOW_STICKY_MSK              (0x00000400)
  #define FLL_DIAG_STAT_1_REG_COUNTER_OVERFLOW_STICKY_MIN              (0)
  #define FLL_DIAG_STAT_1_REG_COUNTER_OVERFLOW_STICKY_MAX              (1) // 0x00000001
  #define FLL_DIAG_STAT_1_REG_COUNTER_OVERFLOW_STICKY_DEF              (0x00000000)
  #define FLL_DIAG_STAT_1_REG_COUNTER_OVERFLOW_STICKY_HSH              (0x0114351C)

  #define FLL_DIAG_STAT_1_REG_MEASUREMENT_ENABLE_DLY_VER_OFF           (11)
  #define FLL_DIAG_STAT_1_REG_MEASUREMENT_ENABLE_DLY_VER_WID           ( 1)
  #define FLL_DIAG_STAT_1_REG_MEASUREMENT_ENABLE_DLY_VER_MSK           (0x00000800)
  #define FLL_DIAG_STAT_1_REG_MEASUREMENT_ENABLE_DLY_VER_MIN           (0)
  #define FLL_DIAG_STAT_1_REG_MEASUREMENT_ENABLE_DLY_VER_MAX           (1) // 0x00000001
  #define FLL_DIAG_STAT_1_REG_MEASUREMENT_ENABLE_DLY_VER_DEF           (0x00000000)
  #define FLL_DIAG_STAT_1_REG_MEASUREMENT_ENABLE_DLY_VER_HSH           (0x0116351C)

  #define FLL_DIAG_STAT_1_REG_RESERVED_DIAG_STS_1_OFF                  (12)
  #define FLL_DIAG_STAT_1_REG_RESERVED_DIAG_STS_1_WID                  (20)
  #define FLL_DIAG_STAT_1_REG_RESERVED_DIAG_STS_1_MSK                  (0xFFFFF000)
  #define FLL_DIAG_STAT_1_REG_RESERVED_DIAG_STS_1_MIN                  (0)
  #define FLL_DIAG_STAT_1_REG_RESERVED_DIAG_STS_1_MAX                  (1048575) // 0x000FFFFF
  #define FLL_DIAG_STAT_1_REG_RESERVED_DIAG_STS_1_DEF                  (0x00000000)
  #define FLL_DIAG_STAT_1_REG_RESERVED_DIAG_STS_1_HSH                  (0x1418351C)

#define FLL_STATIC_CFG_2_REG_REG                                       (0x00003520)

  #define FLL_STATIC_CFG_2_REG_LDO_FAST_RAMP_TIME_SEL_OFF              ( 0)
  #define FLL_STATIC_CFG_2_REG_LDO_FAST_RAMP_TIME_SEL_WID              ( 2)
  #define FLL_STATIC_CFG_2_REG_LDO_FAST_RAMP_TIME_SEL_MSK              (0x00000003)
  #define FLL_STATIC_CFG_2_REG_LDO_FAST_RAMP_TIME_SEL_MIN              (0)
  #define FLL_STATIC_CFG_2_REG_LDO_FAST_RAMP_TIME_SEL_MAX              (3) // 0x00000003
  #define FLL_STATIC_CFG_2_REG_LDO_FAST_RAMP_TIME_SEL_DEF              (0x00000001)
  #define FLL_STATIC_CFG_2_REG_LDO_FAST_RAMP_TIME_SEL_HSH              (0x02003520)

  #define FLL_STATIC_CFG_2_REG_RESERVED_STATIC_CFG_2_OFF               ( 2)
  #define FLL_STATIC_CFG_2_REG_RESERVED_STATIC_CFG_2_WID               (30)
  #define FLL_STATIC_CFG_2_REG_RESERVED_STATIC_CFG_2_MSK               (0xFFFFFFFC)
  #define FLL_STATIC_CFG_2_REG_RESERVED_STATIC_CFG_2_MIN               (0)
  #define FLL_STATIC_CFG_2_REG_RESERVED_STATIC_CFG_2_MAX               (1073741823) // 0x3FFFFFFF
  #define FLL_STATIC_CFG_2_REG_RESERVED_STATIC_CFG_2_DEF               (0x00000000)
  #define FLL_STATIC_CFG_2_REG_RESERVED_STATIC_CFG_2_HSH               (0x1E043520)

#define FLL_DIAG_STAT_2_REG_REG                                        (0x00003524)

  #define FLL_DIAG_STAT_2_REG_RESERVED_DIAG_STS_2_OFF                  ( 0)
  #define FLL_DIAG_STAT_2_REG_RESERVED_DIAG_STS_2_WID                  (32)
  #define FLL_DIAG_STAT_2_REG_RESERVED_DIAG_STS_2_MSK                  (0xFFFFFFFF)
  #define FLL_DIAG_STAT_2_REG_RESERVED_DIAG_STS_2_MIN                  (0)
  #define FLL_DIAG_STAT_2_REG_RESERVED_DIAG_STS_2_MAX                  (4294967295) // 0xFFFFFFFF
  #define FLL_DIAG_STAT_2_REG_RESERVED_DIAG_STS_2_DEF                  (0x00000000)
  #define FLL_DIAG_STAT_2_REG_RESERVED_DIAG_STS_2_HSH                  (0x20003524)

#define CH0CCC_CR_DDRCRCACOMP_REG                                      (0x00003600)

  #define CH0CCC_CR_DDRCRCACOMP_Scomp_OFF                              ( 0)
  #define CH0CCC_CR_DDRCRCACOMP_Scomp_WID                              ( 6)
  #define CH0CCC_CR_DDRCRCACOMP_Scomp_MSK                              (0x0000003F)
  #define CH0CCC_CR_DDRCRCACOMP_Scomp_MIN                              (0)
  #define CH0CCC_CR_DDRCRCACOMP_Scomp_MAX                              (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCACOMP_Scomp_DEF                              (0x00000000)
  #define CH0CCC_CR_DDRCRCACOMP_Scomp_HSH                              (0x06003600)

  #define CH0CCC_CR_DDRCRCACOMP_Spare1_OFF                             ( 6)
  #define CH0CCC_CR_DDRCRCACOMP_Spare1_WID                             ( 6)
  #define CH0CCC_CR_DDRCRCACOMP_Spare1_MSK                             (0x00000FC0)
  #define CH0CCC_CR_DDRCRCACOMP_Spare1_MIN                             (0)
  #define CH0CCC_CR_DDRCRCACOMP_Spare1_MAX                             (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCACOMP_Spare1_DEF                             (0x00000000)
  #define CH0CCC_CR_DDRCRCACOMP_Spare1_HSH                             (0x060C3600)

  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvUp_OFF                         (12)
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvUp_WID                         ( 6)
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvUp_MSK                         (0x0003F000)
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvUp_MIN                         (0)
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvUp_MAX                         (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvUp_DEF                         (0x00000000)
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvUp_HSH                         (0x06183600)

  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvDown_OFF                       (18)
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvDown_WID                       ( 6)
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvDown_MSK                       (0x00FC0000)
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvDown_MIN                       (0)
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvDown_MAX                       (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvDown_DEF                       (0x00000000)
  #define CH0CCC_CR_DDRCRCACOMP_RcompDrvDown_HSH                       (0x06243600)

  #define CH0CCC_CR_DDRCRCACOMP_VssHiFF_OFF                            (24)
  #define CH0CCC_CR_DDRCRCACOMP_VssHiFF_WID                            ( 6)
  #define CH0CCC_CR_DDRCRCACOMP_VssHiFF_MSK                            (0x3F000000)
  #define CH0CCC_CR_DDRCRCACOMP_VssHiFF_MIN                            (0)
  #define CH0CCC_CR_DDRCRCACOMP_VssHiFF_MAX                            (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCACOMP_VssHiFF_DEF                            (0x00000000)
  #define CH0CCC_CR_DDRCRCACOMP_VssHiFF_HSH                            (0x06303600)

  #define CH0CCC_CR_DDRCRCACOMP_Spare_OFF                              (30)
  #define CH0CCC_CR_DDRCRCACOMP_Spare_WID                              ( 2)
  #define CH0CCC_CR_DDRCRCACOMP_Spare_MSK                              (0xC0000000)
  #define CH0CCC_CR_DDRCRCACOMP_Spare_MIN                              (0)
  #define CH0CCC_CR_DDRCRCACOMP_Spare_MAX                              (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCACOMP_Spare_DEF                              (0x00000000)
  #define CH0CCC_CR_DDRCRCACOMP_Spare_HSH                              (0x023C3600)

#define CH2CCC_CR_DDRCRCACOMP_P0_REG                                   (0x00003600)

  #define CH2CCC_CR_DDRCRCACOMP_Scomp_P0_OFF                           ( 0)
  #define CH2CCC_CR_DDRCRCACOMP_Scomp_P0_WID                           ( 6)
  #define CH2CCC_CR_DDRCRCACOMP_Scomp_P0_MSK                           (0x0000003F)
  #define CH2CCC_CR_DDRCRCACOMP_Scomp_P0_MIN                           (0)
  #define CH2CCC_CR_DDRCRCACOMP_Scomp_P0_MAX                           (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCACOMP_Scomp_P0_DEF                           (0x00000000)
  #define CH2CCC_CR_DDRCRCACOMP_Scomp_P0_HSH                           (0x06003600)

  #define CH2CCC_CR_DDRCRCACOMP_Spare1_P0_OFF                          ( 6)
  #define CH2CCC_CR_DDRCRCACOMP_Spare1_P0_WID                          ( 6)
  #define CH2CCC_CR_DDRCRCACOMP_Spare1_P0_MSK                          (0x00000FC0)
  #define CH2CCC_CR_DDRCRCACOMP_Spare1_P0_MIN                          (0)
  #define CH2CCC_CR_DDRCRCACOMP_Spare1_P0_MAX                          (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCACOMP_Spare1_P0_DEF                          (0x00000000)
  #define CH2CCC_CR_DDRCRCACOMP_Spare1_P0_HSH                          (0x060C3600)

  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvUp_P0_OFF                      (12)
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvUp_P0_WID                      ( 6)
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvUp_P0_MSK                      (0x0003F000)
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvUp_P0_MIN                      (0)
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvUp_P0_MAX                      (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvUp_P0_DEF                      (0x00000000)
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvUp_P0_HSH                      (0x06183600)

  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvDown_P0_OFF                    (18)
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvDown_P0_WID                    ( 6)
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvDown_P0_MSK                    (0x00FC0000)
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvDown_P0_MIN                    (0)
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvDown_P0_MAX                    (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvDown_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DDRCRCACOMP_RcompDrvDown_P0_HSH                    (0x06243600)

  #define CH2CCC_CR_DDRCRCACOMP_VssHiFF_P0_OFF                         (24)
  #define CH2CCC_CR_DDRCRCACOMP_VssHiFF_P0_WID                         ( 6)
  #define CH2CCC_CR_DDRCRCACOMP_VssHiFF_P0_MSK                         (0x3F000000)
  #define CH2CCC_CR_DDRCRCACOMP_VssHiFF_P0_MIN                         (0)
  #define CH2CCC_CR_DDRCRCACOMP_VssHiFF_P0_MAX                         (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCACOMP_VssHiFF_P0_DEF                         (0x00000000)
  #define CH2CCC_CR_DDRCRCACOMP_VssHiFF_P0_HSH                         (0x06303600)

  #define CH2CCC_CR_DDRCRCACOMP_Spare_P0_OFF                           (30)
  #define CH2CCC_CR_DDRCRCACOMP_Spare_P0_WID                           ( 2)
  #define CH2CCC_CR_DDRCRCACOMP_Spare_P0_MSK                           (0xC0000000)
  #define CH2CCC_CR_DDRCRCACOMP_Spare_P0_MIN                           (0)
  #define CH2CCC_CR_DDRCRCACOMP_Spare_P0_MAX                           (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCACOMP_Spare_P0_DEF                           (0x00000000)
  #define CH2CCC_CR_DDRCRCACOMP_Spare_P0_HSH                           (0x023C3600)

#define CH0CCC_CR_DDRCRCLKCOMP_REG                                     (0x00003604)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define CH2CCC_CR_DDRCRCLKCOMP_P0_REG                                  (0x00003604)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH0CCC_CR_DDRCRCTLCOMP_REG                                     (0x00003608)

  #define CH0CCC_CR_DDRCRCTLCOMP_Scomp_OFF                             ( 0)
  #define CH0CCC_CR_DDRCRCTLCOMP_Scomp_WID                             ( 6)
  #define CH0CCC_CR_DDRCRCTLCOMP_Scomp_MSK                             (0x0000003F)
  #define CH0CCC_CR_DDRCRCTLCOMP_Scomp_MIN                             (0)
  #define CH0CCC_CR_DDRCRCTLCOMP_Scomp_MAX                             (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCTLCOMP_Scomp_DEF                             (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCOMP_Scomp_HSH                             (0x06003608)

  #define CH0CCC_CR_DDRCRCTLCOMP_Spare1_OFF                            ( 6)
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare1_WID                            ( 6)
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare1_MSK                            (0x00000FC0)
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare1_MIN                            (0)
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare1_MAX                            (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare1_DEF                            (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare1_HSH                            (0x060C3608)

  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                        (12)
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvUp_WID                        ( 6)
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                        (0x0003F000)
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                        (0)
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                        (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                        (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                        (0x06183608)

  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                      (18)
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvDown_WID                      ( 6)
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                      (0x00FC0000)
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                      (0)
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                      (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                      (0x0000003F)
  #define CH0CCC_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                      (0x06243608)

  #define CH0CCC_CR_DDRCRCTLCOMP_VssHiFF_OFF                           (24)
  #define CH0CCC_CR_DDRCRCTLCOMP_VssHiFF_WID                           ( 6)
  #define CH0CCC_CR_DDRCRCTLCOMP_VssHiFF_MSK                           (0x3F000000)
  #define CH0CCC_CR_DDRCRCTLCOMP_VssHiFF_MIN                           (0)
  #define CH0CCC_CR_DDRCRCTLCOMP_VssHiFF_MAX                           (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCTLCOMP_VssHiFF_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCOMP_VssHiFF_HSH                           (0x06303608)

  #define CH0CCC_CR_DDRCRCTLCOMP_Spare_OFF                             (30)
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare_WID                             ( 2)
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare_MSK                             (0xC0000000)
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare_MIN                             (0)
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare_MAX                             (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare_DEF                             (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCOMP_Spare_HSH                             (0x023C3608)

#define CH0CCC_CR_DDRCRCTLCOMP_A0_REG                                  (0x00003608)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_A0_REG

#define CH2CCC_CR_DDRCRCTLCOMP_P0_REG                                  (0x00003608)

  #define CH2CCC_CR_DDRCRCTLCOMP_Scomp_P0_OFF                          ( 0)
  #define CH2CCC_CR_DDRCRCTLCOMP_Scomp_P0_WID                          ( 6)
  #define CH2CCC_CR_DDRCRCTLCOMP_Scomp_P0_MSK                          (0x0000003F)
  #define CH2CCC_CR_DDRCRCTLCOMP_Scomp_P0_MIN                          (0)
  #define CH2CCC_CR_DDRCRCTLCOMP_Scomp_P0_MAX                          (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCTLCOMP_Scomp_P0_DEF                          (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCOMP_Scomp_P0_HSH                          (0x06003608)

  #define CH2CCC_CR_DDRCRCTLCOMP_Spare1_P0_OFF                         ( 6)
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare1_P0_WID                         ( 6)
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare1_P0_MSK                         (0x00000FC0)
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare1_P0_MIN                         (0)
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare1_P0_MAX                         (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare1_P0_DEF                         (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare1_P0_HSH                         (0x060C3608)

  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvUp_P0_OFF                     (12)
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvUp_P0_WID                     ( 6)
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvUp_P0_MSK                     (0x0003F000)
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvUp_P0_MIN                     (0)
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvUp_P0_MAX                     (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvUp_P0_DEF                     (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvUp_P0_HSH                     (0x06183608)

  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvDown_P0_OFF                   (18)
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvDown_P0_WID                   ( 6)
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvDown_P0_MSK                   (0x00FC0000)
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvDown_P0_MIN                   (0)
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvDown_P0_MAX                   (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvDown_P0_DEF                   (0x0000003F)
  #define CH2CCC_CR_DDRCRCTLCOMP_RcompDrvDown_P0_HSH                   (0x06243608)

  #define CH2CCC_CR_DDRCRCTLCOMP_VssHiFF_P0_OFF                        (24)
  #define CH2CCC_CR_DDRCRCTLCOMP_VssHiFF_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRCTLCOMP_VssHiFF_P0_MSK                        (0x3F000000)
  #define CH2CCC_CR_DDRCRCTLCOMP_VssHiFF_P0_MIN                        (0)
  #define CH2CCC_CR_DDRCRCTLCOMP_VssHiFF_P0_MAX                        (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCTLCOMP_VssHiFF_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCOMP_VssHiFF_P0_HSH                        (0x06303608)

  #define CH2CCC_CR_DDRCRCTLCOMP_Spare_P0_OFF                          (30)
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare_P0_WID                          ( 2)
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare_P0_MSK                          (0xC0000000)
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare_P0_MIN                          (0)
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare_P0_MAX                          (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare_P0_DEF                          (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCOMP_Spare_P0_HSH                          (0x023C3608)

#define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG                          (0x0000360C)

  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_OFF         ( 0)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_WID         ( 4)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_MSK         (0x0000000F)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_MIN         (-8)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_MAX         (7) // 0x00000007
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_DEF         (0x00000000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_HSH         (0x8400360C)

  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_OFF                 ( 4)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_WID                 ( 4)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_MSK                 (0x000000F0)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_MIN                 (0)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_MAX                 (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_DEF                 (0x00000000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_HSH                 (0x0408360C)

  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_OFF    ( 8)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_WID    ( 4)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_MSK    (0x00000F00)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_MIN    (-8)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_MAX    (7) // 0x00000007
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_DEF    (0x00000000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_HSH    (0x8410360C)

  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_OFF  (12)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_WID  ( 4)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_MSK  (0x0000F000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_MIN  (-8)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_MAX  (7) // 0x00000007
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_DEF  (0x00000000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_HSH  (0x8418360C)

  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_OFF            (16)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_WID            ( 4)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_MSK            (0x000F0000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_MIN            (-8)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_MAX            (7) // 0x00000007
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_DEF            (0x00000000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_HSH            (0x8420360C)

  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_OFF             (20)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_WID             ( 4)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_MSK             (0x00F00000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_MIN             (-8)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_MAX             (7) // 0x00000007
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_DEF             (0x00000000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_HSH             (0x8428360C)

  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_OFF            (24)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_WID            ( 4)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_MSK            (0x0F000000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_MIN            (-8)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_MAX            (7) // 0x00000007
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_DEF            (0x00000000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_HSH            (0x8430360C)

  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_OFF                  (28)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_WID                  ( 4)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_MSK                  (0xF0000000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_MIN                  (0)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_MAX                  (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_DEF                  (0x00000000)
  #define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_HSH                  (0x0438360C)

#define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG                       (0x0000360C)

  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_P0_OFF      ( 0)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_P0_WID      ( 4)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_P0_MSK      (0x0000000F)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_P0_MIN      (-8)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_P0_MAX      (7) // 0x00000007
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_P0_DEF      (0x00000000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkScompOffset_P0_HSH      (0x8400360C)

  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_P0_OFF              ( 4)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_P0_WID              ( 4)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_P0_MSK              (0x000000F0)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_P0_MIN              (0)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_P0_MAX              (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_P0_DEF              (0x00000000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare1_P0_HSH              (0x0408360C)

  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_P0_OFF ( 8)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_P0_WID ( 4)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_P0_MSK (0x00000F00)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_P0_MIN (-8)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_P0_MAX (7) // 0x00000007
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_P0_DEF (0x00000000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvUpOffset_P0_HSH (0x8410360C)

  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_P0_OFF (12)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_P0_WID ( 4)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_P0_MSK (0x0000F000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_P0_MIN (-8)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_P0_MAX (7) // 0x00000007
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_P0_DEF (0x00000000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkRcompDrvDownOffset_P0_HSH (0x8418360C)

  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_P0_OFF         (16)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_P0_WID         ( 4)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_P0_MSK         (0x000F0000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_P0_MIN         (-8)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_P0_MAX         (7) // 0x00000007
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_P0_DEF         (0x00000000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CtlFFOffset_P0_HSH         (0x8420360C)

  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_P0_OFF          (20)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_P0_WID          ( 4)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_P0_MSK          (0x00F00000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_P0_MIN          (-8)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_P0_MAX          (7) // 0x00000007
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_P0_DEF          (0x00000000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_CaFFOffset_P0_HSH          (0x8428360C)

  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_P0_OFF         (24)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_P0_WID         ( 4)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_P0_MSK         (0x0F000000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_P0_MIN         (-8)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_P0_MAX         (7) // 0x00000007
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_P0_DEF         (0x00000000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_ClkFFOffset_P0_HSH         (0x8430360C)

  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_P0_OFF               (28)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_P0_WID               ( 4)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_P0_MSK               (0xF0000000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_P0_MIN               (0)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_P0_MAX               (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_P0_DEF               (0x00000000)
  #define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_Spare_P0_HSH               (0x0438360C)

#define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_REG                             (0x00003610)

  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_OFF            ( 0)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_WID            ( 4)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_MSK            (0x0000000F)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_MIN            (-8)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_MAX            (7) // 0x00000007
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_DEF            (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_HSH            (0x84003610)

  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_OFF                    ( 4)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_WID                    ( 4)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_MSK                    (0x000000F0)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_MIN                    (0)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_MAX                    (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_DEF                    (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_HSH                    (0x04083610)

  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_OFF       ( 8)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_WID       ( 4)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_MSK       (0x00000F00)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_MIN       (-8)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_MAX       (7) // 0x00000007
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_DEF       (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_HSH       (0x84103610)

  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_OFF     (12)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_WID     ( 4)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_MSK     (0x0000F000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_MIN     (-8)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_MAX     (7) // 0x00000007
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_DEF     (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_HSH     (0x84183610)

  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_OFF             (16)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_WID             ( 4)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_MSK             (0x000F0000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_MIN             (-8)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_MAX             (7) // 0x00000007
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_DEF             (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_HSH             (0x84203610)

  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_OFF                    (20)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_WID                    ( 4)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_MSK                    (0x00F00000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_MIN                    (0)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_MAX                    (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_DEF                    (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_HSH                    (0x04283610)

  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_OFF        (24)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_WID        ( 4)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_MSK        (0x0F000000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_MIN        (-8)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_MAX        (7) // 0x00000007
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_DEF        (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_HSH        (0x84303610)

  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_OFF      (28)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_WID      ( 4)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_MSK      (0xF0000000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_MIN      (-8)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_MAX      (7) // 0x00000007
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_DEF      (0x00000000)
  #define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_HSH      (0x84383610)

#define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG                          (0x00003610)

  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_P0_OFF         ( 0)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_P0_WID         ( 4)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_P0_MSK         (0x0000000F)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_P0_MIN         (-8)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_P0_MAX         (7) // 0x00000007
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_P0_DEF         (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlScompOffset_P0_HSH         (0x84003610)

  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_P0_OFF                 ( 4)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_P0_WID                 ( 4)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_P0_MSK                 (0x000000F0)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_P0_MAX                 (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare1_P0_HSH                 (0x04083610)

  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_P0_OFF    ( 8)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_P0_WID    ( 4)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_P0_MSK    (0x00000F00)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_P0_MIN    (-8)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_P0_MAX    (7) // 0x00000007
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_P0_DEF    (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvUpOffset_P0_HSH    (0x84103610)

  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_P0_OFF  (12)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_P0_WID  ( 4)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_P0_MSK  (0x0000F000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_P0_MIN  (-8)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_P0_MAX  (7) // 0x00000007
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_P0_DEF  (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CtlRcompDrvDownOffset_P0_HSH  (0x84183610)

  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_P0_OFF          (16)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_P0_WID          ( 4)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_P0_MSK          (0x000F0000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_P0_MIN          (-8)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_P0_MAX          (7) // 0x00000007
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_P0_DEF          (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaScompOffset_P0_HSH          (0x84203610)

  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_P0_OFF                 (20)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_P0_WID                 ( 4)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_P0_MSK                 (0x00F00000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_P0_MAX                 (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_Spare2_P0_HSH                 (0x04283610)

  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_P0_OFF     (24)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_P0_WID     ( 4)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_P0_MSK     (0x0F000000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_P0_MIN     (-8)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_P0_MAX     (7) // 0x00000007
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_P0_DEF     (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvUpOffset_P0_HSH     (0x84303610)

  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_P0_OFF   (28)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_P0_WID   ( 4)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_P0_MSK   (0xF0000000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_P0_MIN   (-8)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_P0_MAX   (7) // 0x00000007
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_P0_DEF   (0x00000000)
  #define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_CaRcompDrvDownOffset_P0_HSH   (0x84383610)

#define CH0CCC_CR_DDRCRCCCPIDIVIDER_REG                                (0x00003614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_OFF                     ( 0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_WID                     ( 1)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_MSK                     (0x00000001)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_MAX                     (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_HSH                     (0x01003614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_OFF                       ( 1)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_WID                       ( 2)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_MSK                       (0x00000006)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_MIN                       (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_MAX                       (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_DEF                       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_HSH                       (0x02023614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_OFF                     ( 3)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_WID                     ( 1)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_MSK                     (0x00000008)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_MAX                     (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_HSH                     (0x01063614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_OFF                       ( 4)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_WID                       ( 2)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_MSK                       (0x00000030)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_MIN                       (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_MAX                       (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_DEF                       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_HSH                       (0x02083614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_OFF                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_WID                     ( 1)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_MSK                     (0x00000040)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_MAX                     (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_HSH                     (0x010C3614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_OFF                       ( 7)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_WID                       ( 2)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_MSK                       (0x00000180)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_MIN                       (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_MAX                       (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_DEF                       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_HSH                       (0x020E3614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_OFF                     ( 9)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_WID                     ( 1)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_MSK                     (0x00000200)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_MAX                     (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_HSH                     (0x01123614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_OFF                       (10)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_WID                       ( 2)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_MSK                       (0x00000C00)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_MIN                       (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_MAX                       (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_DEF                       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_HSH                       (0x02143614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_OFF                     (12)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_WID                     ( 1)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_MSK                     (0x00001000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_MAX                     (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_HSH                     (0x01183614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_OFF                       (13)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_WID                       ( 2)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_MSK                       (0x00006000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_MIN                       (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_MAX                       (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_DEF                       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_HSH                       (0x021A3614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_OFF             (15)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_WID             ( 1)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_MSK             (0x00008000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_MIN             (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_MAX             (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_DEF             (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_HSH             (0x011E3614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_OFF               (16)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_WID               ( 2)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_MSK               (0x00030000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_MIN               (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_MAX               (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_DEF               (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_HSH               (0x02203614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_OFF                (18)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_WID                ( 2)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_MSK                (0x000C0000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_MIN                (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_MAX                (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_DEF                (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_HSH                (0x02243614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_OFF              (20)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_WID              ( 1)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_MSK              (0x00100000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_MIN              (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_MAX              (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_DEF              (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_HSH              (0x01283614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_OFF                (21)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_WID                ( 3)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_MSK                (0x00E00000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_MIN                (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_MAX                (7) // 0x00000007
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_DEF                (0x00000007)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_HSH                (0x032A3614)

  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Spare_OFF                        (24)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Spare_WID                        ( 8)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Spare_MSK                        (0xFF000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Spare_MIN                        (0)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Spare_MAX                        (255) // 0x000000FF
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Spare_DEF                        (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPIDIVIDER_Spare_HSH                        (0x08303614)

#define CH2CCC_CR_DDRCRCCCPIDIVIDER_P0_REG                             (0x00003614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_P0_OFF                  ( 0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_P0_WID                  ( 1)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_P0_MSK                  (0x00000001)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_P0_MAX                  (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0DivEn_P0_HSH                  (0x01003614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_P0_OFF                    ( 1)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_P0_WID                    ( 2)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_P0_MSK                    (0x00000006)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_P0_MIN                    (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_P0_MAX                    (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi0Inc_P0_HSH                    (0x02023614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_P0_OFF                  ( 3)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_P0_WID                  ( 1)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_P0_MSK                  (0x00000008)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_P0_MAX                  (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1DivEn_P0_HSH                  (0x01063614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_P0_OFF                    ( 4)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_P0_WID                    ( 2)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_P0_MSK                    (0x00000030)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_P0_MIN                    (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_P0_MAX                    (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi1Inc_P0_HSH                    (0x02083614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_P0_OFF                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_P0_WID                  ( 1)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_P0_MSK                  (0x00000040)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_P0_MAX                  (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2DivEn_P0_HSH                  (0x010C3614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_P0_OFF                    ( 7)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_P0_WID                    ( 2)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_P0_MSK                    (0x00000180)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_P0_MIN                    (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_P0_MAX                    (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi2Inc_P0_HSH                    (0x020E3614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_P0_OFF                  ( 9)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_P0_WID                  ( 1)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_P0_MSK                  (0x00000200)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_P0_MAX                  (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3DivEn_P0_HSH                  (0x01123614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_P0_OFF                    (10)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_P0_WID                    ( 2)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_P0_MSK                    (0x00000C00)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_P0_MIN                    (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_P0_MAX                    (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi3Inc_P0_HSH                    (0x02143614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_P0_OFF                  (12)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_P0_WID                  ( 1)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_P0_MSK                  (0x00001000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_P0_MAX                  (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEn_P0_HSH                  (0x01183614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_P0_OFF                    (13)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_P0_WID                    ( 2)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_P0_MSK                    (0x00006000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_P0_MIN                    (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_P0_MAX                    (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4Inc_P0_HSH                    (0x021A3614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_P0_OFF          (15)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_P0_WID          ( 1)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_P0_MSK          (0x00008000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_P0_MIN          (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_P0_MAX          (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_P0_DEF          (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4DivEnPreamble_P0_HSH          (0x011E3614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_P0_OFF            (16)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_P0_WID            ( 2)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_P0_MSK            (0x00030000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_P0_MIN            (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_P0_MAX            (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_P0_DEF            (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Pi4IncPreamble_P0_HSH            (0x02203614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_P0_OFF             (18)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_P0_WID             ( 2)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_P0_MSK             (0x000C0000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_P0_MIN             (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_P0_MAX             (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_P0_DEF             (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiSyncDivider_P0_HSH             (0x02243614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_P0_OFF           (20)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_P0_WID           ( 1)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_P0_MSK           (0x00100000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_P0_MIN           (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_P0_MAX           (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_P0_DEF           (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_WckHalfPreamble_P0_HSH           (0x01283614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_P0_OFF             (21)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_P0_WID             ( 3)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_P0_MSK             (0x00E00000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_P0_MIN             (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_P0_MAX             (7) // 0x00000007
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_P0_DEF             (0x00000007)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_P0_HSH             (0x032A3614)

  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Spare_P0_OFF                     (24)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Spare_P0_WID                     ( 8)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Spare_P0_MSK                     (0xFF000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Spare_P0_MIN                     (0)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Spare_P0_MAX                     (255) // 0x000000FF
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Spare_P0_DEF                     (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPIDIVIDER_Spare_P0_HSH                     (0x08303614)

#define CH0CCC_CR_DDRCRCCCPICODING0_REG                                (0x00003618)

  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode0_OFF                      ( 0)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode0_WID                      ( 9)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode0_MSK                      (0x000001FF)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode0_MIN                      (0)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode0_MAX                      (511) // 0x000001FF
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode0_DEF                      (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode0_HSH                      (0x09003618)

  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode1_OFF                      ( 9)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode1_WID                      ( 9)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode1_MSK                      (0x0003FE00)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode1_MIN                      (0)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode1_MAX                      (511) // 0x000001FF
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode1_DEF                      (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode1_HSH                      (0x09123618)

  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode2_OFF                      (18)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode2_WID                      ( 9)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode2_MSK                      (0x07FC0000)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode2_MIN                      (0)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode2_MAX                      (511) // 0x000001FF
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode2_DEF                      (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPICODING0_PiCode2_HSH                      (0x09243618)

  #define CH0CCC_CR_DDRCRCCCPICODING0_Reserved_OFF                     (27)
  #define CH0CCC_CR_DDRCRCCCPICODING0_Reserved_WID                     ( 5)
  #define CH0CCC_CR_DDRCRCCCPICODING0_Reserved_MSK                     (0xF8000000)
  #define CH0CCC_CR_DDRCRCCCPICODING0_Reserved_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPICODING0_Reserved_MAX                     (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRCCCPICODING0_Reserved_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPICODING0_Reserved_HSH                     (0x05363618)

#define CH2CCC_CR_DDRCRCCCPICODING0_P0_REG                             (0x00003618)

  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode0_P0_OFF                   ( 0)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode0_P0_WID                   ( 9)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode0_P0_MSK                   (0x000001FF)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode0_P0_MIN                   (0)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode0_P0_MAX                   (511) // 0x000001FF
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode0_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode0_P0_HSH                   (0x09003618)

  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode1_P0_OFF                   ( 9)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode1_P0_WID                   ( 9)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode1_P0_MSK                   (0x0003FE00)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode1_P0_MIN                   (0)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode1_P0_MAX                   (511) // 0x000001FF
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode1_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode1_P0_HSH                   (0x09123618)

  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode2_P0_OFF                   (18)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode2_P0_WID                   ( 9)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode2_P0_MSK                   (0x07FC0000)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode2_P0_MIN                   (0)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode2_P0_MAX                   (511) // 0x000001FF
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode2_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPICODING0_PiCode2_P0_HSH                   (0x09243618)

  #define CH2CCC_CR_DDRCRCCCPICODING0_Reserved_P0_OFF                  (27)
  #define CH2CCC_CR_DDRCRCCCPICODING0_Reserved_P0_WID                  ( 5)
  #define CH2CCC_CR_DDRCRCCCPICODING0_Reserved_P0_MSK                  (0xF8000000)
  #define CH2CCC_CR_DDRCRCCCPICODING0_Reserved_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPICODING0_Reserved_P0_MAX                  (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRCCCPICODING0_Reserved_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPICODING0_Reserved_P0_HSH                  (0x05363618)

#define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG                   (0x0000361C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare12_OFF         ( 0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare12_WID         ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare12_MSK         (0x0000001F)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare12_MIN         (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare12_MAX         (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare12_DEF         (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare12_HSH         (0x0500361C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_OFF           ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_WID           ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_MSK           (0x000003E0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_MIN           (-16)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_MAX           (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_HSH           (0x850A361C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_OFF           (10)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_WID           ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_MSK           (0x00007C00)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_MIN           (-16)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_MAX           (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_HSH           (0x8514361C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_OFF           (15)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_WID           ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_MSK           (0x000F8000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_MIN           (-16)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_MAX           (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_HSH           (0x851E361C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_OFF          (20)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_WID          ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_MSK          (0x01F00000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_MIN          (-16)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_MAX          (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_DEF          (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_HSH          (0x8528361C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare1112_OFF       (25)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare1112_WID       ( 2)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare1112_MSK       (0x06000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare1112_MIN       (-2)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare1112_MAX       (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare1112_DEF       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_Spare1112_HSH       (0x8232361C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_EnFeedback_OFF      (27)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_EnFeedback_WID      ( 3)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_EnFeedback_MSK      (0x38000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_EnFeedback_MIN      (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_EnFeedback_MAX      (7) // 0x00000007
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_EnFeedback_DEF      (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_EnFeedback_HSH      (0x0336361C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_OFF    (30)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_WID    ( 2)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_MSK    (0xC0000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_MIN    (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_MAX    (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_DEF    (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_HSH    (0x023C361C)

#define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG                (0x0000361C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC12_P0_OFF        ( 0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC12_P0_WID        ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC12_P0_MSK        (0x0000001F)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC12_P0_MIN        (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC12_P0_MAX        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC12_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC12_P0_HSH        (0x0500361C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_P0_OFF        ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_P0_WID        ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_P0_MSK        (0x000003E0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_P0_MIN        (-16)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_P0_MAX        (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC34_P0_HSH        (0x850A361C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_P0_OFF        (10)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_P0_WID        ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_P0_MSK        (0x00007C00)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_P0_MIN        (-16)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_P0_MAX        (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC56_P0_HSH        (0x8514361C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_P0_OFF        (15)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_P0_WID        ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_P0_MSK        (0x000F8000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_P0_MIN        (-16)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_P0_MAX        (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC78_P0_HSH        (0x851E361C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_P0_OFF       (20)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_P0_WID       ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_P0_MSK       (0x01F00000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_P0_MIN       (-16)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_P0_MAX       (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_P0_DEF       (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC910_P0_HSH       (0x8528361C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC1112_P0_OFF      (25)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC1112_P0_WID      ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC1112_P0_MSK      (0x3E000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC1112_P0_MIN      (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC1112_P0_MAX      (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC1112_P0_DEF      (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_CCC1112_P0_HSH      (0x0532361C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_P0_OFF (30)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_P0_WID ( 2)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_P0_MSK (0xC0000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_P0_MIN (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_P0_MAX (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_P0_DEF (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_PrNfFeedback_P0_HSH (0x023C361C)

#define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_REG                              (0x00003620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_OFF            ( 0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_WID            ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_MSK            (0x00000001)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_MIN            (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_MAX            (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_DEF            (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_HSH            (0x01003620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_OFF           ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_WID           ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_MSK           (0x00000002)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_MIN           (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_MAX           (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_HSH           (0x01023620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_OFF           ( 2)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_WID           ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_MSK           (0x00000004)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_MIN           (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_MAX           (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_HSH           (0x01043620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_OFF            ( 3)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_WID            ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_MSK            (0x00000008)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_MIN            (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_MAX            (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_DEF            (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_HSH            (0x01063620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_OFF           ( 4)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_WID           ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_MSK           (0x00000010)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_MIN           (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_MAX           (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_HSH           (0x01083620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_OFF          ( 5)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_WID          ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_MSK          (0x00000020)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_MIN          (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_MAX          (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_DEF          (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_HSH          (0x010A3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_OFF          ( 6)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_WID          ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_MSK          (0x00000040)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_MIN          (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_MAX          (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_DEF          (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_HSH          (0x010C3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_OFF        ( 7)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_WID        ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_MSK        (0x00000080)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_MIN        (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_MAX        (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_DEF        (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_HSH        (0x010E3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_OFF        ( 8)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_WID        ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_MSK        (0x00000100)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_MIN        (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_MAX        (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_DEF        (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_HSH        (0x01103620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_OFF         ( 9)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_WID         ( 2)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_MSK         (0x00000600)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_MIN         (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_MAX         (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_DEF         (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_HSH         (0x02123620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_OFF         (11)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_WID         ( 2)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_MSK         (0x00001800)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_MIN         (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_MAX         (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_DEF         (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_HSH         (0x02163620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_OFF               (13)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_WID               ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_MSK               (0x00002000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_MIN               (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_MAX               (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_DEF               (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_HSH               (0x011A3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_OFF                (14)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_WID                ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_MSK                (0x00004000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_MIN                (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_MAX                (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_DEF                (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_HSH                (0x011C3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_OFF           (15)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_WID           ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_MSK           (0x00008000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_MIN           (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_MAX           (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_DEF           (0x00000001)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_HSH           (0x011E3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_OFF        (16)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_WID        ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_MSK        (0x00010000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_MIN        (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_MAX        (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_DEF        (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_HSH        (0x01203620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_OFF        (17)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_WID        ( 4)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_MSK        (0x001E0000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_MIN        (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_MAX        (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_DEF        (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_HSH        (0x04223620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_OFF           (21)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_WID           ( 2)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_MSK           (0x00600000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_MIN           (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_MAX           (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_HSH           (0x022A3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_OFF               (23)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_WID               ( 2)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_MSK               (0x01800000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_MIN               (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_MAX               (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_DEF               (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_HSH               (0x022E3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_OFF          (25)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_WID          ( 6)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_MSK          (0x7E000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_MIN          (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_MAX          (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_DEF          (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_HSH          (0x06323620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_OFF                      (31)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_WID                      ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_MSK                      (0x80000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_MIN                      (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_MAX                      (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_DEF                      (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_HSH                      (0x013E3620)

#define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_A0_REG                           (0x00003620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_A0_OFF         ( 0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_A0_WID         ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_A0_MSK         (0x00000001)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_A0_MIN         (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_A0_MAX         (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_A0_DEF         (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_A0_HSH         (0x01003620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_A0_OFF        ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_A0_WID        ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_A0_MSK        (0x00000002)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_A0_MIN        (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_A0_MAX        (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_A0_DEF        (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_A0_HSH        (0x01023620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_A0_OFF        ( 2)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_A0_WID        ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_A0_MSK        (0x00000004)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_A0_MIN        (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_A0_MAX        (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_A0_DEF        (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_A0_HSH        (0x01043620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_A0_OFF         ( 3)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_A0_WID         ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_A0_MSK         (0x00000008)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_A0_MIN         (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_A0_MAX         (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_A0_DEF         (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_A0_HSH         (0x01063620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_A0_OFF        ( 4)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_A0_WID        ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_A0_MSK        (0x00000010)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_A0_MIN        (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_A0_MAX        (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_A0_DEF        (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_A0_HSH        (0x01083620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_A0_OFF       ( 5)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_A0_WID       ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_A0_MSK       (0x00000020)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_A0_MIN       (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_A0_MAX       (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_A0_DEF       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_A0_HSH       (0x010A3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_A0_OFF       ( 6)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_A0_WID       ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_A0_MSK       (0x00000040)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_A0_MIN       (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_A0_MAX       (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_A0_DEF       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_A0_HSH       (0x010C3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_A0_OFF     ( 7)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_A0_WID     ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_A0_MSK     (0x00000080)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_A0_MIN     (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_A0_MAX     (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_A0_DEF     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_A0_HSH     (0x010E3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_A0_OFF     ( 8)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_A0_WID     ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_A0_MSK     (0x00000100)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_A0_MIN     (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_A0_MAX     (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_A0_DEF     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_A0_HSH     (0x01103620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_A0_OFF      ( 9)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_A0_WID      ( 2)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_A0_MSK      (0x00000600)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_A0_MIN      (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_A0_MAX      (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_A0_DEF      (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_A0_HSH      (0x02123620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_A0_OFF      (11)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_A0_WID      ( 2)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_A0_MSK      (0x00001800)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_A0_MIN      (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_A0_MAX      (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_A0_DEF      (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_A0_HSH      (0x02163620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_A0_OFF            (13)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_A0_WID            ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_A0_MSK            (0x00002000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_A0_MIN            (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_A0_MAX            (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_A0_DEF            (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_A0_HSH            (0x011A3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_A0_OFF             (14)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_A0_WID             ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_A0_MSK             (0x00004000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_A0_MIN             (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_A0_MAX             (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_A0_DEF             (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_A0_HSH             (0x011C3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_A0_OFF        (15)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_A0_WID        ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_A0_MSK        (0x00008000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_A0_MIN        (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_A0_MAX        (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_A0_DEF        (0x00000001)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_A0_HSH        (0x011E3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_A0_OFF     (16)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_A0_WID     ( 1)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_A0_MSK     (0x00010000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_A0_MIN     (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_A0_MAX     (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_A0_DEF     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_A0_HSH     (0x01203620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_A0_OFF     (17)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_A0_WID     ( 4)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_A0_MSK     (0x001E0000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_A0_MIN     (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_A0_MAX     (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_A0_DEF     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_A0_HSH     (0x04223620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_A0_OFF        (21)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_A0_WID        ( 2)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_A0_MSK        (0x00600000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_A0_MIN        (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_A0_MAX        (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_A0_DEF        (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_A0_HSH        (0x022A3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_A0_OFF            (23)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_A0_WID            ( 2)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_A0_MSK            (0x01800000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_A0_MIN            (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_A0_MAX            (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_A0_DEF            (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_A0_HSH            (0x022E3620)

  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_A0_OFF                   (25)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_A0_WID                   ( 7)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_A0_MSK                   (0xFE000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_A0_MIN                   (0)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_A0_MAX                   (127) // 0x0000007F
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_A0_DEF                   (0x00000000)
  #define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_A0_HSH                   (0x07323620)

#define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG                           (0x00003620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_P0_OFF         ( 0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_P0_WID         ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_P0_MSK         (0x00000001)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_P0_MIN         (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_P0_MAX         (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_P0_DEF         (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_PredrvUseVcciog_P0_HSH         (0x01003620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_P0_OFF        ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_P0_WID        ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_P0_MSK        (0x00000002)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_P0_MIN        (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_P0_MAX        (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlVoltageSelect_P0_HSH        (0x01023620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_P0_OFF        ( 2)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_P0_WID        ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_P0_MSK        (0x00000004)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_P0_MIN        (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_P0_MAX        (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkVoltageSelect_P0_HSH        (0x01043620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_P0_OFF         ( 3)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_P0_WID         ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_P0_MSK         (0x00000008)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_P0_MIN         (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_P0_MAX         (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_P0_DEF         (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaVoltageSelect_P0_HSH         (0x01063620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_P0_OFF        ( 4)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_P0_WID        ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_P0_MSK        (0x00000010)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_P0_MIN        (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_P0_MAX        (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CaPDPreDrvVccddq_P0_HSH        (0x01083620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_P0_OFF       ( 5)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_P0_WID       ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_P0_MSK       (0x00000020)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_P0_MIN       (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_P0_MAX       (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_P0_DEF       (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CtlPDPreDrvVccddq_P0_HSH       (0x010A3620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_P0_OFF       ( 6)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_P0_WID       ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_P0_MSK       (0x00000040)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_P0_MIN       (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_P0_MAX       (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_P0_DEF       (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_ClkPDPreDrvVccddq_P0_HSH       (0x010C3620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_P0_OFF     ( 7)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_P0_WID     ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_P0_MSK     (0x00000080)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_P0_MIN     (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_P0_MAX     (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_P0_DEF     (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVddqMode_P0_HSH     (0x010E3620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_P0_OFF     ( 8)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_P0_WID     ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_P0_MSK     (0x00000100)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_P0_MIN     (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_P0_MAX     (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_P0_DEF     (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_VssHiBypassVdd2Mode_P0_HSH     (0x01103620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_P0_OFF      ( 9)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_P0_WID      ( 2)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_P0_MSK      (0x00000600)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_P0_MIN      (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_P0_MAX      (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_P0_DEF      (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVddq_P0_HSH      (0x02123620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_P0_OFF      (11)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_P0_WID      ( 2)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_P0_MSK      (0x00001800)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_P0_MIN      (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_P0_MAX      (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_P0_DEF      (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DlyMatchCtlForVdd2_P0_HSH      (0x02163620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_P0_OFF            (13)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_P0_WID            ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_P0_MSK            (0x00002000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_P0_MIN            (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_P0_MAX            (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_P0_DEF            (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CkUseCtlComp_P0_HSH            (0x011A3620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_P0_OFF             (14)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_P0_WID             ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_P0_MSK             (0x00004000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_P0_MIN             (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_P0_MAX             (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_P0_DEF             (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CsUseCaComp_P0_HSH             (0x011C3620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_P0_OFF        (15)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_P0_WID        ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_P0_MSK        (0x00008000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_P0_MIN        (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_P0_MAX        (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_P0_DEF        (0x00000001)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_CccStaticLegCtrl_P0_HSH        (0x011E3620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_P0_OFF     (16)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_P0_WID     ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_P0_MSK     (0x00010000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_P0_MIN     (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_P0_MAX     (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_P0_DEF     (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisVddqPathWithVddq_P0_HSH     (0x01203620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_P0_OFF     (17)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_P0_WID     ( 4)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_P0_MSK     (0x001E0000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_P0_MIN     (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_P0_MAX     (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_P0_DEF     (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverAdjustmentRsvd_P0_HSH     (0x04223620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_P0_OFF        (21)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_P0_WID        ( 2)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_P0_MSK        (0x00600000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_P0_MIN        (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_P0_MAX        (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_XoverMinDelayCtl_P0_HSH        (0x022A3620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_P0_OFF            (23)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_P0_WID            ( 2)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_P0_MSK            (0x01800000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_P0_MIN            (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_P0_MAX            (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_P0_DEF            (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_DisWckPupDcc_P0_HSH            (0x022E3620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_P0_OFF       (25)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_P0_WID       ( 6)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_P0_MSK       (0x7E000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_P0_MIN       (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_P0_MAX       (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_P0_DEF       (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_TxVsxHiLeakerComp_P0_HSH       (0x06323620)

  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_P0_OFF                   (31)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_P0_WID                   ( 1)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_P0_MSK                   (0x80000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_P0_MIN                   (0)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_P0_MAX                   (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_Spare_P0_HSH                   (0x013E3620)

#define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_REG                            (0x00003624)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_OFF                     ( 0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_MSK                     (0x0000003F)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_HSH                     (0x06003624)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_OFF                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_MSK                     (0x00000FC0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_HSH                     (0x060C3624)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_OFF                     (12)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_MSK                     (0x0003F000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_HSH                     (0x06183624)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_OFF                     (18)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_MSK                     (0x00FC0000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_HSH                     (0x06243624)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_OFF                     (24)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_MSK                     (0x3F000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_HSH                     (0x06303624)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_OFF                (30)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_WID                ( 2)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_MSK                (0xC0000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_MIN                (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_MAX                (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_DEF                (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_HSH                (0x023C3624)

#define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG                         (0x00003624)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_P0_OFF                  ( 0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_P0_MSK                  (0x0000003F)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC0_P0_HSH                  (0x06003624)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_P0_OFF                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_P0_MSK                  (0x00000FC0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC1_P0_HSH                  (0x060C3624)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_P0_OFF                  (12)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_P0_MSK                  (0x0003F000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC2_P0_HSH                  (0x06183624)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_P0_OFF                  (18)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_P0_MSK                  (0x00FC0000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC3_P0_HSH                  (0x06243624)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_P0_OFF                  (24)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_P0_MSK                  (0x3F000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_CCC4_P0_HSH                  (0x06303624)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_P0_OFF             (30)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_P0_WID             ( 2)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_P0_MSK             (0xC0000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_P0_MIN             (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_P0_MAX             (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_P0_DEF             (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_deskewcal_P0_HSH             (0x023C3624)

#define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_REG                            (0x00003628)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_OFF                     ( 0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_MSK                     (0x0000003F)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_HSH                     (0x06003628)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_OFF                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_MSK                     (0x00000FC0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_HSH                     (0x060C3628)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_OFF                     (12)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_MSK                     (0x0003F000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_HSH                     (0x06183628)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_OFF                     (18)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_MSK                     (0x00FC0000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_HSH                     (0x06243628)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_OFF                     (24)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_MSK                     (0x3F000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_HSH                     (0x06303628)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_OFF               (30)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_WID               ( 2)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_MSK               (0xC0000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_MIN               (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_MAX               (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_DEF               (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_HSH               (0x023C3628)

#define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG                         (0x00003628)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_P0_OFF                  ( 0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_P0_MSK                  (0x0000003F)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC5_P0_HSH                  (0x06003628)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_P0_OFF                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_P0_MSK                  (0x00000FC0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC6_P0_HSH                  (0x060C3628)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_P0_OFF                  (12)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_P0_MSK                  (0x0003F000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC7_P0_HSH                  (0x06183628)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_P0_OFF                  (18)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_P0_MSK                  (0x00FC0000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC8_P0_HSH                  (0x06243628)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_P0_OFF                  (24)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_P0_MSK                  (0x3F000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_CCC9_P0_HSH                  (0x06303628)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_P0_OFF            (30)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_P0_WID            ( 2)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_P0_MSK            (0xC0000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_P0_MIN            (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_P0_MAX            (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_P0_DEF            (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_FFPBDDelay_P0_HSH            (0x023C3628)

#define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_REG                            (0x0000362C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_OFF                    ( 0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_WID                    ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_MSK                    (0x0000003F)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_MIN                    (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_MAX                    (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_DEF                    (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_HSH                    (0x0600362C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_OFF                    ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_WID                    ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_MSK                    (0x00000FC0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_MIN                    (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_MAX                    (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_DEF                    (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_HSH                    (0x060C362C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_OFF                    (12)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_WID                    ( 6)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_MSK                    (0x0003F000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_MIN                    (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_MAX                    (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_DEF                    (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_HSH                    (0x0618362C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_OFF                    (18)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_WID                    (13)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_MSK                    (0x7FFC0000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_MIN                    (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_MAX                    (8191) // 0x00001FFF
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_DEF                    (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_HSH                    (0x0D24362C)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_OFF          (31)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_WID          ( 1)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_MSK          (0x80000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_MIN          (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_MAX          (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_DEF          (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_HSH          (0x013E362C)

#define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG                         (0x0000362C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_P0_OFF                 ( 0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_P0_WID                 ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_P0_MSK                 (0x0000003F)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_P0_MAX                 (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC10_P0_HSH                 (0x0600362C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_P0_OFF                 ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_P0_WID                 ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_P0_MSK                 (0x00000FC0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_P0_MAX                 (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC11_P0_HSH                 (0x060C362C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_P0_OFF                 (12)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_P0_WID                 ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_P0_MSK                 (0x0003F000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_P0_MAX                 (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC12_P0_HSH                 (0x0618362C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC13_P0_OFF                 (18)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC13_P0_WID                 ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC13_P0_MSK                 (0x00FC0000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC13_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC13_P0_MAX                 (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC13_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC13_P0_HSH                 (0x0624362C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC14_P0_OFF                 (24)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC14_P0_WID                 ( 6)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC14_P0_MSK                 (0x3F000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC14_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC14_P0_MAX                 (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC14_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_CCC14_P0_HSH                 (0x0630362C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_P0_OFF                 (30)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_P0_WID                 ( 1)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_P0_MSK                 (0x40000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_P0_MAX                 (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_Spare_P0_HSH                 (0x013C362C)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_P0_OFF       (31)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_P0_WID       ( 1)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_P0_MSK       (0x80000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_P0_MIN       (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_P0_MAX       (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_P0_DEF       (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_txdeskewpoweren_P0_HSH       (0x013E362C)

#define CH0CCC_CR_DDRCRPINSUSED_REG                                    (0x00003630)

  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_OFF                             ( 0)
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_WID                             (13)
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_MSK                             (0x00001FFF)
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_MIN                             (0)
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_MAX                             (8191) // 0x00001FFF
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_DEF                             (0x00001FFF)
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_HSH                             (0x0D003630)

  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_OFF                     (13)
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_WID                     ( 2)
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_MSK                     (0x00006000)
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_MIN                     (0)
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_MAX                     (3) // 0x00000003
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_HSH                     (0x021A3630)

  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_OFF                             (15)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_WID                             ( 5)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_MSK                             (0x000F8000)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_MIN                             (0)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_MAX                             (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_DEF                             (0x0000001F)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_HSH                             (0x051E3630)

  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_OFF                         (20)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_WID                         ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_MSK                         (0x00100000)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_MIN                         (0)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_MAX                         (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_DEF                         (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_HSH                         (0x01283630)

  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_OFF                (21)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_WID                ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_MSK                (0x00200000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_MIN                (0)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_MAX                (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_DEF                (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_HSH                (0x012A3630)

  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_OFF               (22)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_WID               ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_MSK               (0x00400000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_MIN               (0)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_MAX               (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_DEF               (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_HSH               (0x012C3630)

  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_OFF               (23)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_WID               ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_MSK               (0x00800000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_MIN               (0)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_MAX               (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_DEF               (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_HSH               (0x012E3630)

  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_OFF                            (24)
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_WID                            ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_MSK                            (0x01000000)
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_MIN                            (0)
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_MAX                            (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_DEF                            (0x00000001)
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_HSH                            (0x01303630)

  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_OFF                       (25)
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_WID                       ( 3)
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_MSK                       (0x0E000000)
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_MIN                       (0)
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_MAX                       (7) // 0x00000007
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_DEF                       (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_HSH                       (0x03323630)

  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_OFF                      (28)
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_WID                      ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_MSK                      (0x10000000)
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_MIN                      (0)
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_MAX                      (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_DEF                      (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_HSH                      (0x01383630)

  #define CH0CCC_CR_DDRCRPINSUSED_SEClk_OFF                            (29)
  #define CH0CCC_CR_DDRCRPINSUSED_SEClk_WID                            ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_SEClk_MSK                            (0x20000000)
  #define CH0CCC_CR_DDRCRPINSUSED_SEClk_MIN                            (0)
  #define CH0CCC_CR_DDRCRPINSUSED_SEClk_MAX                            (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_SEClk_DEF                            (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_SEClk_HSH                            (0x013A3630)

  #define CH0CCC_CR_DDRCRPINSUSED_Spare_OFF                            (30)
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_WID                            ( 2)
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_MSK                            (0xC0000000)
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_MIN                            (0)
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_MAX                            (3) // 0x00000003
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_DEF                            (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_HSH                            (0x023C3630)

#define CH0CCC_CR_DDRCRPINSUSED_A0_REG                                 (0x00003630)

  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_A0_OFF                          ( 0)
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_A0_WID                          (13)
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_A0_MSK                          (0x00001FFF)
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_A0_MIN                          (0)
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_A0_MAX                          (8191) // 0x00001FFF
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_A0_DEF                          (0x00001FFF)
  #define CH0CCC_CR_DDRCRPINSUSED_TxEn_A0_HSH                          (0x0D003630)

  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_A0_OFF                  (13)
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_A0_WID                  ( 2)
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_A0_MSK                  (0x00006000)
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_A0_MIN                  (0)
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_A0_MAX                  (3) // 0x00000003
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_A0_DEF                  (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_CCCMuxSelect_A0_HSH                  (0x021A3630)

  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_A0_OFF                          (15)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_A0_WID                          ( 5)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_A0_MSK                          (0x000F8000)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_A0_MIN                          (0)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_A0_MAX                          (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_A0_DEF                          (0x0000001F)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEn_A0_HSH                          (0x051E3630)

  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_A0_OFF                      (20)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_A0_WID                      ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_A0_MSK                      (0x00100000)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_A0_MIN                      (0)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_A0_MAX                      (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_A0_DEF                      (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_PiEnOvrd_A0_HSH                      (0x01283630)

  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_A0_OFF             (21)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_A0_WID             ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_A0_MSK             (0x00200000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_A0_MIN             (0)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_A0_MAX             (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_A0_DEF             (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_A0_HSH             (0x012A3630)

  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_A0_OFF            (22)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_A0_WID            ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_A0_MSK            (0x00400000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_A0_MIN            (0)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_A0_MAX            (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_A0_DEF            (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_A0_HSH            (0x012C3630)

  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_A0_OFF            (23)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_A0_WID            ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_A0_MSK            (0x00800000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_A0_MIN            (0)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_A0_MAX            (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_A0_DEF            (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_A0_HSH            (0x012E3630)

  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_A0_OFF                         (24)
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_A0_WID                         ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_A0_MSK                         (0x01000000)
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_A0_MIN                         (0)
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_A0_MAX                         (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_A0_DEF                         (0x00000001)
  #define CH0CCC_CR_DDRCRPINSUSED_Gear1_A0_HSH                         (0x01303630)

  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_A0_OFF                    (25)
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_A0_WID                    ( 3)
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_A0_MSK                    (0x0E000000)
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_A0_MIN                    (0)
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_A0_MAX                    (7) // 0x00000007
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_A0_DEF                    (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_TimerXXClk_A0_HSH                    (0x03323630)

  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_A0_OFF                   (28)
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_A0_WID                   ( 1)
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_A0_MSK                   (0x10000000)
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_A0_MIN                   (0)
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_A0_MAX                   (1) // 0x00000001
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_A0_DEF                   (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_KeepXXClkOn_A0_HSH                   (0x01383630)

  #define CH0CCC_CR_DDRCRPINSUSED_Spare_A0_OFF                         (29)
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_A0_WID                         ( 3)
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_A0_MSK                         (0xE0000000)
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_A0_MIN                         (0)
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_A0_MAX                         (7) // 0x00000007
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_A0_DEF                         (0x00000000)
  #define CH0CCC_CR_DDRCRPINSUSED_Spare_A0_HSH                         (0x033A3630)

#define CH2CCC_CR_DDRCRPINSUSED_P0_REG                                 (0x00003630)

  #define CH2CCC_CR_DDRCRPINSUSED_TxEn_P0_OFF                          ( 0)
  #define CH2CCC_CR_DDRCRPINSUSED_TxEn_P0_WID                          (15)
  #define CH2CCC_CR_DDRCRPINSUSED_TxEn_P0_MSK                          (0x00007FFF)
  #define CH2CCC_CR_DDRCRPINSUSED_TxEn_P0_MIN                          (0)
  #define CH2CCC_CR_DDRCRPINSUSED_TxEn_P0_MAX                          (32767) // 0x00007FFF
  #define CH2CCC_CR_DDRCRPINSUSED_TxEn_P0_DEF                          (0x00001FFF)
  #define CH2CCC_CR_DDRCRPINSUSED_TxEn_P0_HSH                          (0x0F003630)

  #define CH2CCC_CR_DDRCRPINSUSED_CCCMuxSelect_P0_OFF                  (15)
  #define CH2CCC_CR_DDRCRPINSUSED_CCCMuxSelect_P0_WID                  ( 2)
  #define CH2CCC_CR_DDRCRPINSUSED_CCCMuxSelect_P0_MSK                  (0x00018000)
  #define CH2CCC_CR_DDRCRPINSUSED_CCCMuxSelect_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRPINSUSED_CCCMuxSelect_P0_MAX                  (3) // 0x00000003
  #define CH2CCC_CR_DDRCRPINSUSED_CCCMuxSelect_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRPINSUSED_CCCMuxSelect_P0_HSH                  (0x021E3630)

  #define CH2CCC_CR_DDRCRPINSUSED_PiEn_P0_OFF                          (17)
  #define CH2CCC_CR_DDRCRPINSUSED_PiEn_P0_WID                          ( 5)
  #define CH2CCC_CR_DDRCRPINSUSED_PiEn_P0_MSK                          (0x003E0000)
  #define CH2CCC_CR_DDRCRPINSUSED_PiEn_P0_MIN                          (0)
  #define CH2CCC_CR_DDRCRPINSUSED_PiEn_P0_MAX                          (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPINSUSED_PiEn_P0_DEF                          (0x0000001F)
  #define CH2CCC_CR_DDRCRPINSUSED_PiEn_P0_HSH                          (0x05223630)

  #define CH2CCC_CR_DDRCRPINSUSED_PiEnOvrd_P0_OFF                      (22)
  #define CH2CCC_CR_DDRCRPINSUSED_PiEnOvrd_P0_WID                      ( 1)
  #define CH2CCC_CR_DDRCRPINSUSED_PiEnOvrd_P0_MSK                      (0x00400000)
  #define CH2CCC_CR_DDRCRPINSUSED_PiEnOvrd_P0_MIN                      (0)
  #define CH2CCC_CR_DDRCRPINSUSED_PiEnOvrd_P0_MAX                      (1) // 0x00000001
  #define CH2CCC_CR_DDRCRPINSUSED_PiEnOvrd_P0_DEF                      (0x00000000)
  #define CH2CCC_CR_DDRCRPINSUSED_PiEnOvrd_P0_HSH                      (0x012C3630)

  #define CH2CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_P0_OFF             (23)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_P0_WID             ( 1)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_P0_MSK             (0x00800000)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_P0_MIN             (0)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_P0_MAX             (1) // 0x00000001
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_P0_DEF             (0x00000000)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCaSlwDlyBypass_P0_HSH             (0x012E3630)

  #define CH2CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_P0_OFF            (24)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_P0_WID            ( 1)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_P0_MSK            (0x01000000)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_P0_MIN            (0)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_P0_MAX            (1) // 0x00000001
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_P0_DEF            (0x00000000)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrCtlSlwDlyBypass_P0_HSH            (0x01303630)

  #define CH2CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_P0_OFF            (25)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_P0_WID            ( 1)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_P0_MSK            (0x02000000)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_P0_MIN            (0)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_P0_MAX            (1) // 0x00000001
  #define CH2CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_P0_DEF            (0x00000000)
  #define CH2CCC_CR_DDRCRPINSUSED_DdrClkSlwDlyBypass_P0_HSH            (0x01323630)

  #define CH2CCC_CR_DDRCRPINSUSED_Gear1_P0_OFF                         (26)
  #define CH2CCC_CR_DDRCRPINSUSED_Gear1_P0_WID                         ( 1)
  #define CH2CCC_CR_DDRCRPINSUSED_Gear1_P0_MSK                         (0x04000000)
  #define CH2CCC_CR_DDRCRPINSUSED_Gear1_P0_MIN                         (0)
  #define CH2CCC_CR_DDRCRPINSUSED_Gear1_P0_MAX                         (1) // 0x00000001
  #define CH2CCC_CR_DDRCRPINSUSED_Gear1_P0_DEF                         (0x00000001)
  #define CH2CCC_CR_DDRCRPINSUSED_Gear1_P0_HSH                         (0x01343630)

  #define CH2CCC_CR_DDRCRPINSUSED_TimerXXClk_P0_OFF                    (27)
  #define CH2CCC_CR_DDRCRPINSUSED_TimerXXClk_P0_WID                    ( 3)
  #define CH2CCC_CR_DDRCRPINSUSED_TimerXXClk_P0_MSK                    (0x38000000)
  #define CH2CCC_CR_DDRCRPINSUSED_TimerXXClk_P0_MIN                    (0)
  #define CH2CCC_CR_DDRCRPINSUSED_TimerXXClk_P0_MAX                    (7) // 0x00000007
  #define CH2CCC_CR_DDRCRPINSUSED_TimerXXClk_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DDRCRPINSUSED_TimerXXClk_P0_HSH                    (0x03363630)

  #define CH2CCC_CR_DDRCRPINSUSED_KeepXXClkOn_P0_OFF                   (30)
  #define CH2CCC_CR_DDRCRPINSUSED_KeepXXClkOn_P0_WID                   ( 1)
  #define CH2CCC_CR_DDRCRPINSUSED_KeepXXClkOn_P0_MSK                   (0x40000000)
  #define CH2CCC_CR_DDRCRPINSUSED_KeepXXClkOn_P0_MIN                   (0)
  #define CH2CCC_CR_DDRCRPINSUSED_KeepXXClkOn_P0_MAX                   (1) // 0x00000001
  #define CH2CCC_CR_DDRCRPINSUSED_KeepXXClkOn_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DDRCRPINSUSED_KeepXXClkOn_P0_HSH                   (0x013C3630)

  #define CH2CCC_CR_DDRCRPINSUSED_SEClk_P0_OFF                         (31)
  #define CH2CCC_CR_DDRCRPINSUSED_SEClk_P0_WID                         ( 1)
  #define CH2CCC_CR_DDRCRPINSUSED_SEClk_P0_MSK                         (0x80000000)
  #define CH2CCC_CR_DDRCRPINSUSED_SEClk_P0_MIN                         (0)
  #define CH2CCC_CR_DDRCRPINSUSED_SEClk_P0_MAX                         (1) // 0x00000001
  #define CH2CCC_CR_DDRCRPINSUSED_SEClk_P0_DEF                         (0x00000000)
  #define CH2CCC_CR_DDRCRPINSUSED_SEClk_P0_HSH                         (0x013E3630)

#define CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG                              (0x00003634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_OFF             ( 0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_WID             ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_MSK             (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_MIN             (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_DEF             (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_HSH             (0x01003634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_OFF                ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_WID                ( 2)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_MSK                (0x00000006)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_MIN                (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_MAX                (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_DEF                (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_HSH                (0x02023634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_OFF                        ( 3)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_WID                        ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_MSK                        (0x00000008)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_MIN                        (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_MAX                        (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_DEF                        (0x00000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_HSH                        (0x01063634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_OFF                    ( 4)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_WID                    ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_MSK                    (0x00000010)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_MIN                    (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_MAX                    (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_DEF                    (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_HSH                    (0x01083634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_OFF       ( 5)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_WID       ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_MSK       (0x00000020)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_MIN       (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_MAX       (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_DEF       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_HSH       (0x010A3634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_OFF       ( 6)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_WID       ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_MSK       (0x00000040)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_MIN       (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_MAX       (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_DEF       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_HSH       (0x010C3634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_OFF                     ( 7)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_WID                     ( 5)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_MSK                     (0x00000F80)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_MAX                     (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_DEF                     (0x0000000C)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_HSH                     (0x050E3634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_OFF                    (12)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_WID                    ( 5)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_MSK                    (0x0001F000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_MIN                    (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_MAX                    (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_DEF                    (0x0000000C)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_HSH                    (0x05183634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_OFF                    (17)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_WID                    ( 5)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_MSK                    (0x003E0000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_MIN                    (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_MAX                    (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_DEF                    (0x0000000C)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_HSH                    (0x05223634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_OFF                   (22)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_WID                   ( 2)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_MSK                   (0x00C00000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_MIN                   (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_MAX                   (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_DEF                   (0x00000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_HSH                   (0x022C3634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_OFF         (24)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_WID         ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_MSK         (0x01000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_MIN         (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_MAX         (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_DEF         (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_HSH         (0x01303634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_OFF                     (25)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_WID                     ( 6)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_MSK                     (0x7E000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_MAX                     (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_HSH                     (0x06323634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_OFF              (31)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_WID              ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_MSK              (0x80000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_MIN              (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_MAX              (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_DEF              (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_HSH              (0x013E3634)

#define CH0CCC_CR_DDRCRCCCCLKCONTROLS_A0_REG                           (0x00003634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_A0_OFF          ( 0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_A0_WID          ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_A0_MSK          (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_A0_MIN          (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_A0_MAX          (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_A0_DEF          (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_A0_HSH          (0x01003634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_A0_OFF             ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_A0_WID             ( 2)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_A0_MSK             (0x00000006)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_A0_MIN             (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_A0_MAX             (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_A0_DEF             (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_A0_HSH             (0x02023634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_A0_OFF                     ( 3)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_A0_WID                     ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_A0_MSK                     (0x00000008)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_A0_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_A0_MAX                     (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_A0_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RTO_A0_HSH                     (0x01063634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_A0_OFF                 ( 4)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_A0_WID                 ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_A0_MSK                 (0x00000010)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_A0_MIN                 (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_A0_MAX                 (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_A0_DEF                 (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_A0_HSH                 (0x01083634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_A0_OFF    ( 5)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_A0_WID    ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_A0_MSK    (0x00000020)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_A0_MIN    (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_A0_MAX    (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_A0_DEF    (0x00000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_A0_HSH    (0x010A3634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_A0_OFF    ( 6)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_A0_WID    ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_A0_MSK    (0x00000040)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_A0_MIN    (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_A0_MAX    (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_A0_DEF    (0x00000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_A0_HSH    (0x010C3634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_A0_OFF                  ( 7)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_A0_WID                  ( 5)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_A0_MSK                  (0x00000F80)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_A0_MIN                  (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_A0_MAX                  (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_A0_DEF                  (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_A0_HSH                  (0x050E3634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_A0_OFF                 (12)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_A0_WID                 ( 5)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_A0_MSK                 (0x0001F000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_A0_MIN                 (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_A0_MAX                 (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_A0_DEF                 (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_A0_HSH                 (0x05183634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_A0_OFF                 (17)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_A0_WID                 ( 5)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_A0_MSK                 (0x003E0000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_A0_MIN                 (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_A0_MAX                 (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_A0_DEF                 (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_A0_HSH                 (0x05223634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_A0_OFF                (22)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_A0_WID                ( 2)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_A0_MSK                (0x00C00000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_A0_MIN                (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_A0_MAX                (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_A0_DEF                (0x00000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_A0_HSH                (0x022C3634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_A0_OFF      (24)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_A0_WID      ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_A0_MSK      (0x01000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_A0_MIN      (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_A0_MAX      (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_A0_DEF      (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_A0_HSH      (0x01303634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_A0_OFF                  (25)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_A0_WID                  ( 6)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_A0_MSK                  (0x7E000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_A0_MIN                  (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_A0_MAX                  (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_A0_DEF                  (0x00000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_A0_HSH                  (0x06323634)

  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_A0_OFF           (31)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_A0_WID           ( 1)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_A0_MSK           (0x80000000)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_A0_MIN           (0)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_A0_MAX           (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_A0_DEF           (0x00000001)
  #define CH0CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_A0_HSH           (0x013E3634)

#define CH2CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG                           (0x00003634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_P0_OFF          ( 0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_P0_WID          ( 1)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_P0_MSK          (0x00000001)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_P0_MIN          (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_P0_MAX          (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_P0_DEF          (0x00000001)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkGateDisable_P0_HSH          (0x01003634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_P0_OFF             ( 1)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_P0_WID             ( 2)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_P0_MSK             (0x00000006)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_P0_MIN             (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_P0_MAX             (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_P0_DEF             (0x00000001)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_DefDrvEnLow_P0_HSH             (0x02023634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RTO_P0_OFF                     ( 3)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RTO_P0_WID                     ( 1)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RTO_P0_MSK                     (0x00000008)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RTO_P0_MIN                     (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RTO_P0_MAX                     (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RTO_P0_DEF                     (0x00000000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RTO_P0_HSH                     (0x01063634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_P0_OFF                 ( 4)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_P0_WID                 ( 1)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_P0_MSK                 (0x00000010)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_P0_MAX                 (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_P0_DEF                 (0x00000001)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_IntCkOn_P0_HSH                 (0x01083634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_P0_OFF    ( 5)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_P0_WID    ( 1)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_P0_MSK    (0x00000020)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_P0_MIN    (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_P0_MAX    (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_P0_DEF    (0x00000000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CkeIdlePiGateDisable_P0_HSH    (0x010A3634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_P0_OFF    ( 6)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_P0_WID    ( 1)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_P0_MSK    (0x00000040)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_P0_MIN    (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_P0_MAX    (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_P0_DEF    (0x00000000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaValidPiGateDisable_P0_HSH    (0x010C3634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_P0_OFF                  ( 7)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_P0_WID                  ( 5)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_P0_MSK                  (0x00000F80)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_P0_MAX                  (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_P0_DEF                  (0x0000000C)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CaTxEq_P0_HSH                  (0x050E3634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_P0_OFF                 (12)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_P0_WID                 ( 5)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_P0_MSK                 (0x0001F000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_P0_MAX                 (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_P0_DEF                 (0x0000000C)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlTxEq_P0_HSH                 (0x05183634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_P0_OFF                 (17)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_P0_WID                 ( 5)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_P0_MSK                 (0x003E0000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_P0_MIN                 (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_P0_MAX                 (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_P0_DEF                 (0x0000000C)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_ClkTxEq_P0_HSH                 (0x05223634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_P0_OFF                (22)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_P0_WID                ( 2)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_P0_MSK                (0x00C00000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_P0_MIN                (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_P0_MAX                (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_P0_DEF                (0x00000000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_CtlSRDrv_P0_HSH                (0x022C3634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_P0_OFF      (24)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_P0_WID      ( 1)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_P0_MSK      (0x01000000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_P0_MIN      (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_P0_MAX      (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_P0_DEF      (0x00000001)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_c3segsel_b_for_cke_P0_HSH      (0x01303634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_P0_OFF                  (25)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_P0_WID                  ( 6)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_P0_MSK                  (0x7E000000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_P0_MAX                  (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_RxVref_P0_HSH                  (0x06323634)

  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_P0_OFF           (31)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_P0_WID           ( 1)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_P0_MSK           (0x80000000)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_P0_MIN           (0)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_P0_MAX           (1) // 0x00000001
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_P0_DEF           (0x00000001)
  #define CH2CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst_P0_HSH           (0x013E3634)

#define CH0CCC_CR_DDRCRBSCANDATA_REG                                   (0x00003638)

  #define CH0CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_OFF                  ( 0)
  #define CH0CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_WID                  ( 1)
  #define CH0CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_MSK                  (0x00000001)
  #define CH0CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_MIN                  (0)
  #define CH0CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_MAX                  (1) // 0x00000001
  #define CH0CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_DEF                  (0x00000000)
  #define CH0CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_HSH                  (0x01003638)

  #define CH0CCC_CR_DDRCRBSCANDATA_DataValue_OFF                       ( 1)
  #define CH0CCC_CR_DDRCRBSCANDATA_DataValue_WID                       (14)
  #define CH0CCC_CR_DDRCRBSCANDATA_DataValue_MSK                       (0x00007FFE)
  #define CH0CCC_CR_DDRCRBSCANDATA_DataValue_MIN                       (0)
  #define CH0CCC_CR_DDRCRBSCANDATA_DataValue_MAX                       (16383) // 0x00003FFF
  #define CH0CCC_CR_DDRCRBSCANDATA_DataValue_DEF                       (0x00000000)
  #define CH0CCC_CR_DDRCRBSCANDATA_DataValue_HSH                       (0x0E023638)

  #define CH0CCC_CR_DDRCRBSCANDATA_BiasRloadVref_OFF                   (15)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasRloadVref_WID                   ( 3)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasRloadVref_MSK                   (0x00038000)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasRloadVref_MIN                   (0)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasRloadVref_MAX                   (7) // 0x00000007
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasRloadVref_DEF                   (0x00000004)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasRloadVref_HSH                   (0x031E3638)

  #define CH0CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_OFF                     (18)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_WID                     ( 4)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_MSK                     (0x003C0000)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_MIN                     (0)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_MAX                     (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_DEF                     (0x00000008)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_HSH                     (0x04243638)

  #define CH0CCC_CR_DDRCRBSCANDATA_BiasCasAdj_OFF                      (22)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasCasAdj_WID                      ( 2)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasCasAdj_MSK                      (0x00C00000)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasCasAdj_MIN                      (0)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasCasAdj_MAX                      (3) // 0x00000003
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasCasAdj_DEF                      (0x00000002)
  #define CH0CCC_CR_DDRCRBSCANDATA_BiasCasAdj_HSH                      (0x022C3638)

  #define CH0CCC_CR_DDRCRBSCANDATA_Spare_OFF                           (24)
  #define CH0CCC_CR_DDRCRBSCANDATA_Spare_WID                           ( 8)
  #define CH0CCC_CR_DDRCRBSCANDATA_Spare_MSK                           (0xFF000000)
  #define CH0CCC_CR_DDRCRBSCANDATA_Spare_MIN                           (0)
  #define CH0CCC_CR_DDRCRBSCANDATA_Spare_MAX                           (255) // 0x000000FF
  #define CH0CCC_CR_DDRCRBSCANDATA_Spare_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRBSCANDATA_Spare_HSH                           (0x08303638)

#define CH2CCC_CR_DDRCRBSCANDATA_P0_REG                                (0x00003638)

  #define CH2CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_P0_OFF               ( 0)
  #define CH2CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_P0_WID               ( 1)
  #define CH2CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_P0_MSK               (0x00000001)
  #define CH2CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_P0_MIN               (0)
  #define CH2CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_P0_MAX               (1) // 0x00000001
  #define CH2CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_P0_DEF               (0x00000000)
  #define CH2CCC_CR_DDRCRBSCANDATA_DdrBscanEnable_P0_HSH               (0x01003638)

  #define CH2CCC_CR_DDRCRBSCANDATA_DataValue_P0_OFF                    ( 1)
  #define CH2CCC_CR_DDRCRBSCANDATA_DataValue_P0_WID                    (15)
  #define CH2CCC_CR_DDRCRBSCANDATA_DataValue_P0_MSK                    (0x0000FFFE)
  #define CH2CCC_CR_DDRCRBSCANDATA_DataValue_P0_MIN                    (0)
  #define CH2CCC_CR_DDRCRBSCANDATA_DataValue_P0_MAX                    (32767) // 0x00007FFF
  #define CH2CCC_CR_DDRCRBSCANDATA_DataValue_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DDRCRBSCANDATA_DataValue_P0_HSH                    (0x0F023638)

  #define CH2CCC_CR_DDRCRBSCANDATA_BiasRloadVref_P0_OFF                (16)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasRloadVref_P0_WID                ( 3)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasRloadVref_P0_MSK                (0x00070000)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasRloadVref_P0_MIN                (0)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasRloadVref_P0_MAX                (7) // 0x00000007
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasRloadVref_P0_DEF                (0x00000004)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasRloadVref_P0_HSH                (0x03203638)

  #define CH2CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_P0_OFF                  (19)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_P0_WID                  ( 4)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_P0_MSK                  (0x00780000)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_P0_MAX                  (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_P0_DEF                  (0x00000008)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasIrefAdj_P0_HSH                  (0x04263638)

  #define CH2CCC_CR_DDRCRBSCANDATA_BiasCasAdj_P0_OFF                   (23)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasCasAdj_P0_WID                   ( 2)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasCasAdj_P0_MSK                   (0x01800000)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasCasAdj_P0_MIN                   (0)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasCasAdj_P0_MAX                   (3) // 0x00000003
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasCasAdj_P0_DEF                   (0x00000002)
  #define CH2CCC_CR_DDRCRBSCANDATA_BiasCasAdj_P0_HSH                   (0x022E3638)

  #define CH2CCC_CR_DDRCRBSCANDATA_Spare_P0_OFF                        (25)
  #define CH2CCC_CR_DDRCRBSCANDATA_Spare_P0_WID                        ( 7)
  #define CH2CCC_CR_DDRCRBSCANDATA_Spare_P0_MSK                        (0xFE000000)
  #define CH2CCC_CR_DDRCRBSCANDATA_Spare_P0_MIN                        (0)
  #define CH2CCC_CR_DDRCRBSCANDATA_Spare_P0_MAX                        (127) // 0x0000007F
  #define CH2CCC_CR_DDRCRBSCANDATA_Spare_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRBSCANDATA_Spare_P0_HSH                        (0x07323638)

#define CH0CCC_CR_DDRCRMISR_REG                                        (0x0000363C)

  #define CH0CCC_CR_DDRCRMISR_EnOnFuncEn_OFF                           ( 0)
  #define CH0CCC_CR_DDRCRMISR_EnOnFuncEn_WID                           ( 1)
  #define CH0CCC_CR_DDRCRMISR_EnOnFuncEn_MSK                           (0x00000001)
  #define CH0CCC_CR_DDRCRMISR_EnOnFuncEn_MIN                           (0)
  #define CH0CCC_CR_DDRCRMISR_EnOnFuncEn_MAX                           (1) // 0x00000001
  #define CH0CCC_CR_DDRCRMISR_EnOnFuncEn_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRMISR_EnOnFuncEn_HSH                           (0x0100363C)

  #define CH0CCC_CR_DDRCRMISR_StartOnFuncEn_OFF                        ( 1)
  #define CH0CCC_CR_DDRCRMISR_StartOnFuncEn_WID                        ( 1)
  #define CH0CCC_CR_DDRCRMISR_StartOnFuncEn_MSK                        (0x00000002)
  #define CH0CCC_CR_DDRCRMISR_StartOnFuncEn_MIN                        (0)
  #define CH0CCC_CR_DDRCRMISR_StartOnFuncEn_MAX                        (1) // 0x00000001
  #define CH0CCC_CR_DDRCRMISR_StartOnFuncEn_DEF                        (0x00000000)
  #define CH0CCC_CR_DDRCRMISR_StartOnFuncEn_HSH                        (0x0102363C)

  #define CH0CCC_CR_DDRCRMISR_EnLFSR_OFF                               ( 2)
  #define CH0CCC_CR_DDRCRMISR_EnLFSR_WID                               ( 1)
  #define CH0CCC_CR_DDRCRMISR_EnLFSR_MSK                               (0x00000004)
  #define CH0CCC_CR_DDRCRMISR_EnLFSR_MIN                               (0)
  #define CH0CCC_CR_DDRCRMISR_EnLFSR_MAX                               (1) // 0x00000001
  #define CH0CCC_CR_DDRCRMISR_EnLFSR_DEF                               (0x00000000)
  #define CH0CCC_CR_DDRCRMISR_EnLFSR_HSH                               (0x0104363C)

  #define CH0CCC_CR_DDRCRMISR_MaskNonDetA_OFF                          ( 3)
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetA_WID                          ( 1)
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetA_MSK                          (0x00000008)
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetA_MIN                          (0)
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetA_MAX                          (1) // 0x00000001
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetA_DEF                          (0x00000000)
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetA_HSH                          (0x0106363C)

  #define CH0CCC_CR_DDRCRMISR_MaskNonDetB_OFF                          ( 4)
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetB_WID                          ( 1)
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetB_MSK                          (0x00000010)
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetB_MIN                          (0)
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetB_MAX                          (1) // 0x00000001
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetB_DEF                          (0x00000000)
  #define CH0CCC_CR_DDRCRMISR_MaskNonDetB_HSH                          (0x0108363C)

  #define CH0CCC_CR_DDRCRMISR_EnCycles_OFF                             ( 5)
  #define CH0CCC_CR_DDRCRMISR_EnCycles_WID                             ( 3)
  #define CH0CCC_CR_DDRCRMISR_EnCycles_MSK                             (0x000000E0)
  #define CH0CCC_CR_DDRCRMISR_EnCycles_MIN                             (0)
  #define CH0CCC_CR_DDRCRMISR_EnCycles_MAX                             (7) // 0x00000007
  #define CH0CCC_CR_DDRCRMISR_EnCycles_DEF                             (0x00000000)
  #define CH0CCC_CR_DDRCRMISR_EnCycles_HSH                             (0x030A363C)

  #define CH0CCC_CR_DDRCRMISR_MaskBits_OFF                             ( 8)
  #define CH0CCC_CR_DDRCRMISR_MaskBits_WID                             ( 8)
  #define CH0CCC_CR_DDRCRMISR_MaskBits_MSK                             (0x0000FF00)
  #define CH0CCC_CR_DDRCRMISR_MaskBits_MIN                             (0)
  #define CH0CCC_CR_DDRCRMISR_MaskBits_MAX                             (255) // 0x000000FF
  #define CH0CCC_CR_DDRCRMISR_MaskBits_DEF                             (0x00000000)
  #define CH0CCC_CR_DDRCRMISR_MaskBits_HSH                             (0x0810363C)

  #define CH0CCC_CR_DDRCRMISR_Data_OFF                                 (16)
  #define CH0CCC_CR_DDRCRMISR_Data_WID                                 (16)
  #define CH0CCC_CR_DDRCRMISR_Data_MSK                                 (0xFFFF0000)
  #define CH0CCC_CR_DDRCRMISR_Data_MIN                                 (0)
  #define CH0CCC_CR_DDRCRMISR_Data_MAX                                 (65535) // 0x0000FFFF
  #define CH0CCC_CR_DDRCRMISR_Data_DEF                                 (0x00000000)
  #define CH0CCC_CR_DDRCRMISR_Data_HSH                                 (0x1020363C)

#define CH2CCC_CR_DDRCRMISR_P0_REG                                     (0x0000363C)

  #define CH2CCC_CR_DDRCRMISR_EnOnFuncEn_P0_OFF                        ( 0)
  #define CH2CCC_CR_DDRCRMISR_EnOnFuncEn_P0_WID                        ( 1)
  #define CH2CCC_CR_DDRCRMISR_EnOnFuncEn_P0_MSK                        (0x00000001)
  #define CH2CCC_CR_DDRCRMISR_EnOnFuncEn_P0_MIN                        (0)
  #define CH2CCC_CR_DDRCRMISR_EnOnFuncEn_P0_MAX                        (1) // 0x00000001
  #define CH2CCC_CR_DDRCRMISR_EnOnFuncEn_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRMISR_EnOnFuncEn_P0_HSH                        (0x0100363C)

  #define CH2CCC_CR_DDRCRMISR_StartOnFuncEn_P0_OFF                     ( 1)
  #define CH2CCC_CR_DDRCRMISR_StartOnFuncEn_P0_WID                     ( 1)
  #define CH2CCC_CR_DDRCRMISR_StartOnFuncEn_P0_MSK                     (0x00000002)
  #define CH2CCC_CR_DDRCRMISR_StartOnFuncEn_P0_MIN                     (0)
  #define CH2CCC_CR_DDRCRMISR_StartOnFuncEn_P0_MAX                     (1) // 0x00000001
  #define CH2CCC_CR_DDRCRMISR_StartOnFuncEn_P0_DEF                     (0x00000000)
  #define CH2CCC_CR_DDRCRMISR_StartOnFuncEn_P0_HSH                     (0x0102363C)

  #define CH2CCC_CR_DDRCRMISR_EnLFSR_P0_OFF                            ( 2)
  #define CH2CCC_CR_DDRCRMISR_EnLFSR_P0_WID                            ( 1)
  #define CH2CCC_CR_DDRCRMISR_EnLFSR_P0_MSK                            (0x00000004)
  #define CH2CCC_CR_DDRCRMISR_EnLFSR_P0_MIN                            (0)
  #define CH2CCC_CR_DDRCRMISR_EnLFSR_P0_MAX                            (1) // 0x00000001
  #define CH2CCC_CR_DDRCRMISR_EnLFSR_P0_DEF                            (0x00000000)
  #define CH2CCC_CR_DDRCRMISR_EnLFSR_P0_HSH                            (0x0104363C)

  #define CH2CCC_CR_DDRCRMISR_MaskNonDetA_P0_OFF                       ( 3)
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetA_P0_WID                       ( 1)
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetA_P0_MSK                       (0x00000008)
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetA_P0_MIN                       (0)
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetA_P0_MAX                       (1) // 0x00000001
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetA_P0_DEF                       (0x00000000)
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetA_P0_HSH                       (0x0106363C)

  #define CH2CCC_CR_DDRCRMISR_MaskNonDetB_P0_OFF                       ( 4)
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetB_P0_WID                       ( 1)
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetB_P0_MSK                       (0x00000010)
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetB_P0_MIN                       (0)
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetB_P0_MAX                       (1) // 0x00000001
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetB_P0_DEF                       (0x00000000)
  #define CH2CCC_CR_DDRCRMISR_MaskNonDetB_P0_HSH                       (0x0108363C)

  #define CH2CCC_CR_DDRCRMISR_EnCycles_P0_OFF                          ( 5)
  #define CH2CCC_CR_DDRCRMISR_EnCycles_P0_WID                          ( 3)
  #define CH2CCC_CR_DDRCRMISR_EnCycles_P0_MSK                          (0x000000E0)
  #define CH2CCC_CR_DDRCRMISR_EnCycles_P0_MIN                          (0)
  #define CH2CCC_CR_DDRCRMISR_EnCycles_P0_MAX                          (7) // 0x00000007
  #define CH2CCC_CR_DDRCRMISR_EnCycles_P0_DEF                          (0x00000000)
  #define CH2CCC_CR_DDRCRMISR_EnCycles_P0_HSH                          (0x030A363C)

  #define CH2CCC_CR_DDRCRMISR_MaskBits_P0_OFF                          ( 8)
  #define CH2CCC_CR_DDRCRMISR_MaskBits_P0_WID                          ( 8)
  #define CH2CCC_CR_DDRCRMISR_MaskBits_P0_MSK                          (0x0000FF00)
  #define CH2CCC_CR_DDRCRMISR_MaskBits_P0_MIN                          (0)
  #define CH2CCC_CR_DDRCRMISR_MaskBits_P0_MAX                          (255) // 0x000000FF
  #define CH2CCC_CR_DDRCRMISR_MaskBits_P0_DEF                          (0x00000000)
  #define CH2CCC_CR_DDRCRMISR_MaskBits_P0_HSH                          (0x0810363C)

  #define CH2CCC_CR_DDRCRMISR_Data_P0_OFF                              (16)
  #define CH2CCC_CR_DDRCRMISR_Data_P0_WID                              (16)
  #define CH2CCC_CR_DDRCRMISR_Data_P0_MSK                              (0xFFFF0000)
  #define CH2CCC_CR_DDRCRMISR_Data_P0_MIN                              (0)
  #define CH2CCC_CR_DDRCRMISR_Data_P0_MAX                              (65535) // 0x0000FFFF
  #define CH2CCC_CR_DDRCRMISR_Data_P0_DEF                              (0x00000000)
  #define CH2CCC_CR_DDRCRMISR_Data_P0_HSH                              (0x1020363C)

#define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG                   (0x00003640)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare12_OFF         ( 0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare12_WID         ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare12_MSK         (0x0000001F)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare12_MIN         (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare12_MAX         (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare12_DEF         (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare12_HSH         (0x05003640)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_OFF           ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_WID           ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_MSK           (0x000003E0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_MIN           (-16)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_MAX           (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_HSH           (0x850A3640)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_OFF           (10)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_WID           ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_MSK           (0x00007C00)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_MIN           (-16)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_MAX           (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_HSH           (0x85143640)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_OFF           (15)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_WID           ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_MSK           (0x000F8000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_MIN           (-16)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_MAX           (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_HSH           (0x851E3640)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_OFF          (20)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_WID          ( 5)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_MSK          (0x01F00000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_MIN          (-16)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_MAX          (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_DEF          (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_HSH          (0x85283640)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare1112_OFF       (25)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare1112_WID       ( 2)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare1112_MSK       (0x06000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare1112_MIN       (-2)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare1112_MAX       (1) // 0x00000001
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare1112_DEF       (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_Spare1112_HSH       (0x82323640)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_EnFeedback_OFF      (27)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_EnFeedback_WID      ( 3)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_EnFeedback_MSK      (0x38000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_EnFeedback_MIN      (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_EnFeedback_MAX      (7) // 0x00000007
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_EnFeedback_DEF      (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_EnFeedback_HSH      (0x03363640)

  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_OFF    (30)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_WID    ( 2)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_MSK    (0xC0000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_MIN    (0)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_MAX    (3) // 0x00000003
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_DEF    (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_HSH    (0x023C3640)

#define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG                (0x00003640)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC12_P0_OFF        ( 0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC12_P0_WID        ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC12_P0_MSK        (0x0000001F)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC12_P0_MIN        (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC12_P0_MAX        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC12_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC12_P0_HSH        (0x05003640)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_P0_OFF        ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_P0_WID        ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_P0_MSK        (0x000003E0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_P0_MIN        (-16)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_P0_MAX        (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC34_P0_HSH        (0x850A3640)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_P0_OFF        (10)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_P0_WID        ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_P0_MSK        (0x00007C00)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_P0_MIN        (-16)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_P0_MAX        (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC56_P0_HSH        (0x85143640)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_P0_OFF        (15)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_P0_WID        ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_P0_MSK        (0x000F8000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_P0_MIN        (-16)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_P0_MAX        (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC78_P0_HSH        (0x851E3640)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_P0_OFF       (20)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_P0_WID       ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_P0_MSK       (0x01F00000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_P0_MIN       (-16)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_P0_MAX       (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_P0_DEF       (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC910_P0_HSH       (0x85283640)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC1112_P0_OFF      (25)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC1112_P0_WID      ( 5)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC1112_P0_MSK      (0x3E000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC1112_P0_MIN      (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC1112_P0_MAX      (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC1112_P0_DEF      (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_CCC1112_P0_HSH      (0x05323640)

  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_P0_OFF (30)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_P0_WID ( 2)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_P0_MSK (0xC0000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_P0_MIN (0)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_P0_MAX (3) // 0x00000003
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_P0_DEF (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_PfNrFeedback_P0_HSH (0x023C3640)

#define CH0CCC_CR_DCCFSMCONTROL_REG                                    (0x00003644)

  #define CH0CCC_CR_DCCFSMCONTROL_RankEn_OFF                           ( 0)
  #define CH0CCC_CR_DCCFSMCONTROL_RankEn_WID                           ( 2)
  #define CH0CCC_CR_DCCFSMCONTROL_RankEn_MSK                           (0x00000003)
  #define CH0CCC_CR_DCCFSMCONTROL_RankEn_MIN                           (0)
  #define CH0CCC_CR_DCCFSMCONTROL_RankEn_MAX                           (3) // 0x00000003
  #define CH0CCC_CR_DCCFSMCONTROL_RankEn_DEF                           (0x00000001)
  #define CH0CCC_CR_DCCFSMCONTROL_RankEn_HSH                           (0x02003644)

  #define CH0CCC_CR_DCCFSMCONTROL_LaneEn_OFF                           ( 2)
  #define CH0CCC_CR_DCCFSMCONTROL_LaneEn_WID                           (10)
  #define CH0CCC_CR_DCCFSMCONTROL_LaneEn_MSK                           (0x00000FFC)
  #define CH0CCC_CR_DCCFSMCONTROL_LaneEn_MIN                           (0)
  #define CH0CCC_CR_DCCFSMCONTROL_LaneEn_MAX                           (1023) // 0x000003FF
  #define CH0CCC_CR_DCCFSMCONTROL_LaneEn_DEF                           (0x00000004)
  #define CH0CCC_CR_DCCFSMCONTROL_LaneEn_HSH                           (0x0A043644)

  #define CH0CCC_CR_DCCFSMCONTROL_RankMap_OFF                          (12)
  #define CH0CCC_CR_DCCFSMCONTROL_RankMap_WID                          ( 2)
  #define CH0CCC_CR_DCCFSMCONTROL_RankMap_MSK                          (0x00003000)
  #define CH0CCC_CR_DCCFSMCONTROL_RankMap_MIN                          (0)
  #define CH0CCC_CR_DCCFSMCONTROL_RankMap_MAX                          (3) // 0x00000003
  #define CH0CCC_CR_DCCFSMCONTROL_RankMap_DEF                          (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_RankMap_HSH                          (0x02183644)

  #define CH0CCC_CR_DCCFSMCONTROL_DccSamples_OFF                       (14)
  #define CH0CCC_CR_DCCFSMCONTROL_DccSamples_WID                       ( 5)
  #define CH0CCC_CR_DCCFSMCONTROL_DccSamples_MSK                       (0x0007C000)
  #define CH0CCC_CR_DCCFSMCONTROL_DccSamples_MIN                       (0)
  #define CH0CCC_CR_DCCFSMCONTROL_DccSamples_MAX                       (31) // 0x0000001F
  #define CH0CCC_CR_DCCFSMCONTROL_DccSamples_DEF                       (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_DccSamples_HSH                       (0x051C3644)

  #define CH0CCC_CR_DCCFSMCONTROL_SaveFullDcc_OFF                      (19)
  #define CH0CCC_CR_DCCFSMCONTROL_SaveFullDcc_WID                      ( 1)
  #define CH0CCC_CR_DCCFSMCONTROL_SaveFullDcc_MSK                      (0x00080000)
  #define CH0CCC_CR_DCCFSMCONTROL_SaveFullDcc_MIN                      (0)
  #define CH0CCC_CR_DCCFSMCONTROL_SaveFullDcc_MAX                      (1) // 0x00000001
  #define CH0CCC_CR_DCCFSMCONTROL_SaveFullDcc_DEF                      (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_SaveFullDcc_HSH                      (0x01263644)

  #define CH0CCC_CR_DCCFSMCONTROL_RORank_OFF                           (20)
  #define CH0CCC_CR_DCCFSMCONTROL_RORank_WID                           ( 3)
  #define CH0CCC_CR_DCCFSMCONTROL_RORank_MSK                           (0x00700000)
  #define CH0CCC_CR_DCCFSMCONTROL_RORank_MIN                           (0)
  #define CH0CCC_CR_DCCFSMCONTROL_RORank_MAX                           (7) // 0x00000007
  #define CH0CCC_CR_DCCFSMCONTROL_RORank_DEF                           (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_RORank_HSH                           (0x03283644)

  #define CH0CCC_CR_DCCFSMCONTROL_EnRankOvrd_OFF                       (23)
  #define CH0CCC_CR_DCCFSMCONTROL_EnRankOvrd_WID                       ( 1)
  #define CH0CCC_CR_DCCFSMCONTROL_EnRankOvrd_MSK                       (0x00800000)
  #define CH0CCC_CR_DCCFSMCONTROL_EnRankOvrd_MIN                       (0)
  #define CH0CCC_CR_DCCFSMCONTROL_EnRankOvrd_MAX                       (1) // 0x00000001
  #define CH0CCC_CR_DCCFSMCONTROL_EnRankOvrd_DEF                       (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_EnRankOvrd_HSH                       (0x012E3644)

  #define CH0CCC_CR_DCCFSMCONTROL_MeasPoint_OFF                        (24)
  #define CH0CCC_CR_DCCFSMCONTROL_MeasPoint_WID                        ( 2)
  #define CH0CCC_CR_DCCFSMCONTROL_MeasPoint_MSK                        (0x03000000)
  #define CH0CCC_CR_DCCFSMCONTROL_MeasPoint_MIN                        (0)
  #define CH0CCC_CR_DCCFSMCONTROL_MeasPoint_MAX                        (3) // 0x00000003
  #define CH0CCC_CR_DCCFSMCONTROL_MeasPoint_DEF                        (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_MeasPoint_HSH                        (0x02303644)

  #define CH0CCC_CR_DCCFSMCONTROL_SkipCRWrite_OFF                      (26)
  #define CH0CCC_CR_DCCFSMCONTROL_SkipCRWrite_WID                      ( 1)
  #define CH0CCC_CR_DCCFSMCONTROL_SkipCRWrite_MSK                      (0x04000000)
  #define CH0CCC_CR_DCCFSMCONTROL_SkipCRWrite_MIN                      (0)
  #define CH0CCC_CR_DCCFSMCONTROL_SkipCRWrite_MAX                      (1) // 0x00000001
  #define CH0CCC_CR_DCCFSMCONTROL_SkipCRWrite_DEF                      (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_SkipCRWrite_HSH                      (0x01343644)

  #define CH0CCC_CR_DCCFSMCONTROL_SkipUpdate_OFF                       (27)
  #define CH0CCC_CR_DCCFSMCONTROL_SkipUpdate_WID                       ( 1)
  #define CH0CCC_CR_DCCFSMCONTROL_SkipUpdate_MSK                       (0x08000000)
  #define CH0CCC_CR_DCCFSMCONTROL_SkipUpdate_MIN                       (0)
  #define CH0CCC_CR_DCCFSMCONTROL_SkipUpdate_MAX                       (1) // 0x00000001
  #define CH0CCC_CR_DCCFSMCONTROL_SkipUpdate_DEF                       (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_SkipUpdate_HSH                       (0x01363644)

  #define CH0CCC_CR_DCCFSMCONTROL_WaitForUpdate_OFF                    (28)
  #define CH0CCC_CR_DCCFSMCONTROL_WaitForUpdate_WID                    ( 1)
  #define CH0CCC_CR_DCCFSMCONTROL_WaitForUpdate_MSK                    (0x10000000)
  #define CH0CCC_CR_DCCFSMCONTROL_WaitForUpdate_MIN                    (0)
  #define CH0CCC_CR_DCCFSMCONTROL_WaitForUpdate_MAX                    (1) // 0x00000001
  #define CH0CCC_CR_DCCFSMCONTROL_WaitForUpdate_DEF                    (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_WaitForUpdate_HSH                    (0x01383644)

  #define CH0CCC_CR_DCCFSMCONTROL_UpdateTcoComp_OFF                    (29)
  #define CH0CCC_CR_DCCFSMCONTROL_UpdateTcoComp_WID                    ( 1)
  #define CH0CCC_CR_DCCFSMCONTROL_UpdateTcoComp_MSK                    (0x20000000)
  #define CH0CCC_CR_DCCFSMCONTROL_UpdateTcoComp_MIN                    (0)
  #define CH0CCC_CR_DCCFSMCONTROL_UpdateTcoComp_MAX                    (1) // 0x00000001
  #define CH0CCC_CR_DCCFSMCONTROL_UpdateTcoComp_DEF                    (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_UpdateTcoComp_HSH                    (0x013A3644)

  #define CH0CCC_CR_DCCFSMCONTROL_rsvd_OFF                             (30)
  #define CH0CCC_CR_DCCFSMCONTROL_rsvd_WID                             ( 2)
  #define CH0CCC_CR_DCCFSMCONTROL_rsvd_MSK                             (0xC0000000)
  #define CH0CCC_CR_DCCFSMCONTROL_rsvd_MIN                             (0)
  #define CH0CCC_CR_DCCFSMCONTROL_rsvd_MAX                             (3) // 0x00000003
  #define CH0CCC_CR_DCCFSMCONTROL_rsvd_DEF                             (0x00000000)
  #define CH0CCC_CR_DCCFSMCONTROL_rsvd_HSH                             (0x023C3644)

#define CH2CCC_CR_DCCFSMCONTROL_P0_REG                                 (0x00003644)

  #define CH2CCC_CR_DCCFSMCONTROL_RankEn_P0_OFF                        ( 0)
  #define CH2CCC_CR_DCCFSMCONTROL_RankEn_P0_WID                        ( 2)
  #define CH2CCC_CR_DCCFSMCONTROL_RankEn_P0_MSK                        (0x00000003)
  #define CH2CCC_CR_DCCFSMCONTROL_RankEn_P0_MIN                        (0)
  #define CH2CCC_CR_DCCFSMCONTROL_RankEn_P0_MAX                        (3) // 0x00000003
  #define CH2CCC_CR_DCCFSMCONTROL_RankEn_P0_DEF                        (0x00000001)
  #define CH2CCC_CR_DCCFSMCONTROL_RankEn_P0_HSH                        (0x02003644)

  #define CH2CCC_CR_DCCFSMCONTROL_LaneEn_P0_OFF                        ( 2)
  #define CH2CCC_CR_DCCFSMCONTROL_LaneEn_P0_WID                        (10)
  #define CH2CCC_CR_DCCFSMCONTROL_LaneEn_P0_MSK                        (0x00000FFC)
  #define CH2CCC_CR_DCCFSMCONTROL_LaneEn_P0_MIN                        (0)
  #define CH2CCC_CR_DCCFSMCONTROL_LaneEn_P0_MAX                        (1023) // 0x000003FF
  #define CH2CCC_CR_DCCFSMCONTROL_LaneEn_P0_DEF                        (0x00000004)
  #define CH2CCC_CR_DCCFSMCONTROL_LaneEn_P0_HSH                        (0x0A043644)

  #define CH2CCC_CR_DCCFSMCONTROL_RankMap_P0_OFF                       (12)
  #define CH2CCC_CR_DCCFSMCONTROL_RankMap_P0_WID                       ( 2)
  #define CH2CCC_CR_DCCFSMCONTROL_RankMap_P0_MSK                       (0x00003000)
  #define CH2CCC_CR_DCCFSMCONTROL_RankMap_P0_MIN                       (0)
  #define CH2CCC_CR_DCCFSMCONTROL_RankMap_P0_MAX                       (3) // 0x00000003
  #define CH2CCC_CR_DCCFSMCONTROL_RankMap_P0_DEF                       (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_RankMap_P0_HSH                       (0x02183644)

  #define CH2CCC_CR_DCCFSMCONTROL_DccSamples_P0_OFF                    (14)
  #define CH2CCC_CR_DCCFSMCONTROL_DccSamples_P0_WID                    ( 5)
  #define CH2CCC_CR_DCCFSMCONTROL_DccSamples_P0_MSK                    (0x0007C000)
  #define CH2CCC_CR_DCCFSMCONTROL_DccSamples_P0_MIN                    (0)
  #define CH2CCC_CR_DCCFSMCONTROL_DccSamples_P0_MAX                    (31) // 0x0000001F
  #define CH2CCC_CR_DCCFSMCONTROL_DccSamples_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_DccSamples_P0_HSH                    (0x051C3644)

  #define CH2CCC_CR_DCCFSMCONTROL_SaveFullDcc_P0_OFF                   (19)
  #define CH2CCC_CR_DCCFSMCONTROL_SaveFullDcc_P0_WID                   ( 1)
  #define CH2CCC_CR_DCCFSMCONTROL_SaveFullDcc_P0_MSK                   (0x00080000)
  #define CH2CCC_CR_DCCFSMCONTROL_SaveFullDcc_P0_MIN                   (0)
  #define CH2CCC_CR_DCCFSMCONTROL_SaveFullDcc_P0_MAX                   (1) // 0x00000001
  #define CH2CCC_CR_DCCFSMCONTROL_SaveFullDcc_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_SaveFullDcc_P0_HSH                   (0x01263644)

  #define CH2CCC_CR_DCCFSMCONTROL_RORank_P0_OFF                        (20)
  #define CH2CCC_CR_DCCFSMCONTROL_RORank_P0_WID                        ( 3)
  #define CH2CCC_CR_DCCFSMCONTROL_RORank_P0_MSK                        (0x00700000)
  #define CH2CCC_CR_DCCFSMCONTROL_RORank_P0_MIN                        (0)
  #define CH2CCC_CR_DCCFSMCONTROL_RORank_P0_MAX                        (7) // 0x00000007
  #define CH2CCC_CR_DCCFSMCONTROL_RORank_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_RORank_P0_HSH                        (0x03283644)

  #define CH2CCC_CR_DCCFSMCONTROL_EnRankOvrd_P0_OFF                    (23)
  #define CH2CCC_CR_DCCFSMCONTROL_EnRankOvrd_P0_WID                    ( 1)
  #define CH2CCC_CR_DCCFSMCONTROL_EnRankOvrd_P0_MSK                    (0x00800000)
  #define CH2CCC_CR_DCCFSMCONTROL_EnRankOvrd_P0_MIN                    (0)
  #define CH2CCC_CR_DCCFSMCONTROL_EnRankOvrd_P0_MAX                    (1) // 0x00000001
  #define CH2CCC_CR_DCCFSMCONTROL_EnRankOvrd_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_EnRankOvrd_P0_HSH                    (0x012E3644)

  #define CH2CCC_CR_DCCFSMCONTROL_MeasPoint_P0_OFF                     (24)
  #define CH2CCC_CR_DCCFSMCONTROL_MeasPoint_P0_WID                     ( 2)
  #define CH2CCC_CR_DCCFSMCONTROL_MeasPoint_P0_MSK                     (0x03000000)
  #define CH2CCC_CR_DCCFSMCONTROL_MeasPoint_P0_MIN                     (0)
  #define CH2CCC_CR_DCCFSMCONTROL_MeasPoint_P0_MAX                     (3) // 0x00000003
  #define CH2CCC_CR_DCCFSMCONTROL_MeasPoint_P0_DEF                     (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_MeasPoint_P0_HSH                     (0x02303644)

  #define CH2CCC_CR_DCCFSMCONTROL_SkipCRWrite_P0_OFF                   (26)
  #define CH2CCC_CR_DCCFSMCONTROL_SkipCRWrite_P0_WID                   ( 1)
  #define CH2CCC_CR_DCCFSMCONTROL_SkipCRWrite_P0_MSK                   (0x04000000)
  #define CH2CCC_CR_DCCFSMCONTROL_SkipCRWrite_P0_MIN                   (0)
  #define CH2CCC_CR_DCCFSMCONTROL_SkipCRWrite_P0_MAX                   (1) // 0x00000001
  #define CH2CCC_CR_DCCFSMCONTROL_SkipCRWrite_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_SkipCRWrite_P0_HSH                   (0x01343644)

  #define CH2CCC_CR_DCCFSMCONTROL_SkipUpdate_P0_OFF                    (27)
  #define CH2CCC_CR_DCCFSMCONTROL_SkipUpdate_P0_WID                    ( 1)
  #define CH2CCC_CR_DCCFSMCONTROL_SkipUpdate_P0_MSK                    (0x08000000)
  #define CH2CCC_CR_DCCFSMCONTROL_SkipUpdate_P0_MIN                    (0)
  #define CH2CCC_CR_DCCFSMCONTROL_SkipUpdate_P0_MAX                    (1) // 0x00000001
  #define CH2CCC_CR_DCCFSMCONTROL_SkipUpdate_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_SkipUpdate_P0_HSH                    (0x01363644)

  #define CH2CCC_CR_DCCFSMCONTROL_WaitForUpdate_P0_OFF                 (28)
  #define CH2CCC_CR_DCCFSMCONTROL_WaitForUpdate_P0_WID                 ( 1)
  #define CH2CCC_CR_DCCFSMCONTROL_WaitForUpdate_P0_MSK                 (0x10000000)
  #define CH2CCC_CR_DCCFSMCONTROL_WaitForUpdate_P0_MIN                 (0)
  #define CH2CCC_CR_DCCFSMCONTROL_WaitForUpdate_P0_MAX                 (1) // 0x00000001
  #define CH2CCC_CR_DCCFSMCONTROL_WaitForUpdate_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_WaitForUpdate_P0_HSH                 (0x01383644)

  #define CH2CCC_CR_DCCFSMCONTROL_UpdateTcoComp_P0_OFF                 (29)
  #define CH2CCC_CR_DCCFSMCONTROL_UpdateTcoComp_P0_WID                 ( 1)
  #define CH2CCC_CR_DCCFSMCONTROL_UpdateTcoComp_P0_MSK                 (0x20000000)
  #define CH2CCC_CR_DCCFSMCONTROL_UpdateTcoComp_P0_MIN                 (0)
  #define CH2CCC_CR_DCCFSMCONTROL_UpdateTcoComp_P0_MAX                 (1) // 0x00000001
  #define CH2CCC_CR_DCCFSMCONTROL_UpdateTcoComp_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_UpdateTcoComp_P0_HSH                 (0x013A3644)

  #define CH2CCC_CR_DCCFSMCONTROL_rsvd_P0_OFF                          (30)
  #define CH2CCC_CR_DCCFSMCONTROL_rsvd_P0_WID                          ( 2)
  #define CH2CCC_CR_DCCFSMCONTROL_rsvd_P0_MSK                          (0xC0000000)
  #define CH2CCC_CR_DCCFSMCONTROL_rsvd_P0_MIN                          (0)
  #define CH2CCC_CR_DCCFSMCONTROL_rsvd_P0_MAX                          (3) // 0x00000003
  #define CH2CCC_CR_DCCFSMCONTROL_rsvd_P0_DEF                          (0x00000000)
  #define CH2CCC_CR_DCCFSMCONTROL_rsvd_P0_HSH                          (0x023C3644)

#define CH0CCC_CR_DCCCALCCONTROL_REG                                   (0x00003648)

  #define CH0CCC_CR_DCCCALCCONTROL_DccStepSize_OFF                     ( 0)
  #define CH0CCC_CR_DCCCALCCONTROL_DccStepSize_WID                     ( 5)
  #define CH0CCC_CR_DCCCALCCONTROL_DccStepSize_MSK                     (0x0000001F)
  #define CH0CCC_CR_DCCCALCCONTROL_DccStepSize_MIN                     (0)
  #define CH0CCC_CR_DCCCALCCONTROL_DccStepSize_MAX                     (31) // 0x0000001F
  #define CH0CCC_CR_DCCCALCCONTROL_DccStepSize_DEF                     (0x00000010)
  #define CH0CCC_CR_DCCCALCCONTROL_DccStepSize_HSH                     (0x05003648)

  #define CH0CCC_CR_DCCCALCCONTROL_CKTargetElse_OFF                    ( 5)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTargetElse_WID                    ( 5)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTargetElse_MSK                    (0x000003E0)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTargetElse_MIN                    (-16)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTargetElse_MAX                    (15) // 0x0000000F
  #define CH0CCC_CR_DCCCALCCONTROL_CKTargetElse_DEF                    (0x00000000)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTargetElse_HSH                    (0x850A3648)

  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget56_OFF                      (10)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget56_WID                      ( 5)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget56_MSK                      (0x00007C00)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget56_MIN                      (-16)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget56_MAX                      (15) // 0x0000000F
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget56_DEF                      (0x00000000)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget56_HSH                      (0x85143648)

  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget78_OFF                      (15)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget78_WID                      ( 5)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget78_MSK                      (0x000F8000)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget78_MIN                      (-16)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget78_MAX                      (15) // 0x0000000F
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget78_DEF                      (0x00000000)
  #define CH0CCC_CR_DCCCALCCONTROL_CKTarget78_HSH                      (0x851E3648)

  #define CH0CCC_CR_DCCCALCCONTROL_rsvd2_OFF                           (20)
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd2_WID                           ( 1)
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd2_MSK                           (0x00100000)
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd2_MIN                           (0)
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd2_MAX                           (1) // 0x00000001
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd2_DEF                           (0x00000000)
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd2_HSH                           (0x01283648)

  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeLane_OFF                (21)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeLane_WID                ( 4)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeLane_MSK                (0x01E00000)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeLane_MIN                (0)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeLane_MAX                (15) // 0x0000000F
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeLane_DEF                (0x00000000)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeLane_HSH                (0x042A3648)

  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeMax_OFF                 (25)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeMax_WID                 ( 1)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeMax_MSK                 (0x02000000)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeMax_MIN                 (0)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeMax_MAX                 (1) // 0x00000001
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeMax_DEF                 (0x00000000)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeMax_HSH                 (0x01323648)

  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeRank_OFF                (26)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeRank_WID                ( 1)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeRank_MSK                (0x04000000)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeRank_MIN                (0)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeRank_MAX                (1) // 0x00000001
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeRank_DEF                (0x00000000)
  #define CH0CCC_CR_DCCCALCCONTROL_TrackExtremeRank_HSH                (0x01343648)

  #define CH0CCC_CR_DCCCALCCONTROL_LargeChange_OFF                     (27)
  #define CH0CCC_CR_DCCCALCCONTROL_LargeChange_WID                     ( 2)
  #define CH0CCC_CR_DCCCALCCONTROL_LargeChange_MSK                     (0x18000000)
  #define CH0CCC_CR_DCCCALCCONTROL_LargeChange_MIN                     (0)
  #define CH0CCC_CR_DCCCALCCONTROL_LargeChange_MAX                     (3) // 0x00000003
  #define CH0CCC_CR_DCCCALCCONTROL_LargeChange_DEF                     (0x00000000)
  #define CH0CCC_CR_DCCCALCCONTROL_LargeChange_HSH                     (0x02363648)

  #define CH0CCC_CR_DCCCALCCONTROL_Dcc2xStep_OFF                       (29)
  #define CH0CCC_CR_DCCCALCCONTROL_Dcc2xStep_WID                       ( 1)
  #define CH0CCC_CR_DCCCALCCONTROL_Dcc2xStep_MSK                       (0x20000000)
  #define CH0CCC_CR_DCCCALCCONTROL_Dcc2xStep_MIN                       (0)
  #define CH0CCC_CR_DCCCALCCONTROL_Dcc2xStep_MAX                       (1) // 0x00000001
  #define CH0CCC_CR_DCCCALCCONTROL_Dcc2xStep_DEF                       (0x00000000)
  #define CH0CCC_CR_DCCCALCCONTROL_Dcc2xStep_HSH                       (0x013A3648)

  #define CH0CCC_CR_DCCCALCCONTROL_rsvd_OFF                            (30)
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd_WID                            ( 2)
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd_MSK                            (0xC0000000)
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd_MIN                            (0)
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd_MAX                            (3) // 0x00000003
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd_DEF                            (0x00000000)
  #define CH0CCC_CR_DCCCALCCONTROL_rsvd_HSH                            (0x023C3648)

#define CH2CCC_CR_DCCCALCCONTROL_P0_REG                                (0x00003648)

  #define CH2CCC_CR_DCCCALCCONTROL_DccStepSize_P0_OFF                  ( 0)
  #define CH2CCC_CR_DCCCALCCONTROL_DccStepSize_P0_WID                  ( 5)
  #define CH2CCC_CR_DCCCALCCONTROL_DccStepSize_P0_MSK                  (0x0000001F)
  #define CH2CCC_CR_DCCCALCCONTROL_DccStepSize_P0_MIN                  (0)
  #define CH2CCC_CR_DCCCALCCONTROL_DccStepSize_P0_MAX                  (31) // 0x0000001F
  #define CH2CCC_CR_DCCCALCCONTROL_DccStepSize_P0_DEF                  (0x00000010)
  #define CH2CCC_CR_DCCCALCCONTROL_DccStepSize_P0_HSH                  (0x05003648)

  #define CH2CCC_CR_DCCCALCCONTROL_CKTargetElse_P0_OFF                 ( 5)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTargetElse_P0_WID                 ( 5)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTargetElse_P0_MSK                 (0x000003E0)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTargetElse_P0_MIN                 (-16)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTargetElse_P0_MAX                 (15) // 0x0000000F
  #define CH2CCC_CR_DCCCALCCONTROL_CKTargetElse_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTargetElse_P0_HSH                 (0x850A3648)

  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget56_P0_OFF                   (10)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget56_P0_WID                   ( 5)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget56_P0_MSK                   (0x00007C00)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget56_P0_MIN                   (-16)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget56_P0_MAX                   (15) // 0x0000000F
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget56_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget56_P0_HSH                   (0x85143648)

  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget78_P0_OFF                   (15)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget78_P0_WID                   ( 5)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget78_P0_MSK                   (0x000F8000)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget78_P0_MIN                   (-16)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget78_P0_MAX                   (15) // 0x0000000F
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget78_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DCCCALCCONTROL_CKTarget78_P0_HSH                   (0x851E3648)

  #define CH2CCC_CR_DCCCALCCONTROL_rsvd2_P0_OFF                        (20)
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd2_P0_WID                        ( 1)
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd2_P0_MSK                        (0x00100000)
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd2_P0_MIN                        (0)
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd2_P0_MAX                        (1) // 0x00000001
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd2_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd2_P0_HSH                        (0x01283648)

  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeLane_P0_OFF             (21)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeLane_P0_WID             ( 4)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeLane_P0_MSK             (0x01E00000)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeLane_P0_MIN             (0)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeLane_P0_MAX             (15) // 0x0000000F
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeLane_P0_DEF             (0x00000000)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeLane_P0_HSH             (0x042A3648)

  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeMax_P0_OFF              (25)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeMax_P0_WID              ( 1)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeMax_P0_MSK              (0x02000000)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeMax_P0_MIN              (0)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeMax_P0_MAX              (1) // 0x00000001
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeMax_P0_DEF              (0x00000000)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeMax_P0_HSH              (0x01323648)

  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeRank_P0_OFF             (26)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeRank_P0_WID             ( 1)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeRank_P0_MSK             (0x04000000)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeRank_P0_MIN             (0)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeRank_P0_MAX             (1) // 0x00000001
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeRank_P0_DEF             (0x00000000)
  #define CH2CCC_CR_DCCCALCCONTROL_TrackExtremeRank_P0_HSH             (0x01343648)

  #define CH2CCC_CR_DCCCALCCONTROL_LargeChange_P0_OFF                  (27)
  #define CH2CCC_CR_DCCCALCCONTROL_LargeChange_P0_WID                  ( 2)
  #define CH2CCC_CR_DCCCALCCONTROL_LargeChange_P0_MSK                  (0x18000000)
  #define CH2CCC_CR_DCCCALCCONTROL_LargeChange_P0_MIN                  (0)
  #define CH2CCC_CR_DCCCALCCONTROL_LargeChange_P0_MAX                  (3) // 0x00000003
  #define CH2CCC_CR_DCCCALCCONTROL_LargeChange_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DCCCALCCONTROL_LargeChange_P0_HSH                  (0x02363648)

  #define CH2CCC_CR_DCCCALCCONTROL_Dcc2xStep_P0_OFF                    (29)
  #define CH2CCC_CR_DCCCALCCONTROL_Dcc2xStep_P0_WID                    ( 1)
  #define CH2CCC_CR_DCCCALCCONTROL_Dcc2xStep_P0_MSK                    (0x20000000)
  #define CH2CCC_CR_DCCCALCCONTROL_Dcc2xStep_P0_MIN                    (0)
  #define CH2CCC_CR_DCCCALCCONTROL_Dcc2xStep_P0_MAX                    (1) // 0x00000001
  #define CH2CCC_CR_DCCCALCCONTROL_Dcc2xStep_P0_DEF                    (0x00000000)
  #define CH2CCC_CR_DCCCALCCONTROL_Dcc2xStep_P0_HSH                    (0x013A3648)

  #define CH2CCC_CR_DCCCALCCONTROL_rsvd_P0_OFF                         (30)
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd_P0_WID                         ( 2)
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd_P0_MSK                         (0xC0000000)
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd_P0_MIN                         (0)
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd_P0_MAX                         (3) // 0x00000003
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd_P0_DEF                         (0x00000000)
  #define CH2CCC_CR_DCCCALCCONTROL_rsvd_P0_HSH                         (0x023C3648)

#define CH0CCC_CR_DCCFSMSTATUS_REG                                     (0x0000364C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define CH2CCC_CR_DCCFSMSTATUS_P0_REG                                  (0x0000364C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_P0_REG

#define CH0CCC_CR_DCCLANESTATUS0_REG                                   (0x00003650)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define CH2CCC_CR_DCCLANESTATUS0_P0_REG                                (0x00003650)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_P0_REG

#define CH0CCC_CR_DCCLANESTATUS1_REG                                   (0x00003654)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define CH2CCC_CR_DCCLANESTATUS1_P0_REG                                (0x00003654)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_P0_REG

#define CH0CCC_CR_DDRCRPERBITTCO0_REG                                  (0x00003658)

  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC0_OFF                           ( 0)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC0_WID                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC0_MSK                           (0x0000003F)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC0_MIN                           (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC0_MAX                           (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC0_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC0_HSH                           (0x86003658)

  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC1_OFF                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC1_WID                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC1_MSK                           (0x00000FC0)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC1_MIN                           (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC1_MAX                           (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC1_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC1_HSH                           (0x860C3658)

  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC2_OFF                           (12)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC2_WID                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC2_MSK                           (0x0003F000)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC2_MIN                           (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC2_MAX                           (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC2_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC2_HSH                           (0x86183658)

  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC3_OFF                           (18)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC3_WID                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC3_MSK                           (0x00FC0000)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC3_MIN                           (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC3_MAX                           (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC3_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC3_HSH                           (0x86243658)

  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC4_OFF                           (24)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC4_WID                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC4_MSK                           (0x3F000000)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC4_MIN                           (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC4_MAX                           (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC4_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO0_CCC4_HSH                           (0x86303658)

  #define CH0CCC_CR_DDRCRPERBITTCO0_Spare_OFF                          (30)
  #define CH0CCC_CR_DDRCRPERBITTCO0_Spare_WID                          ( 2)
  #define CH0CCC_CR_DDRCRPERBITTCO0_Spare_MSK                          (0xC0000000)
  #define CH0CCC_CR_DDRCRPERBITTCO0_Spare_MIN                          (0)
  #define CH0CCC_CR_DDRCRPERBITTCO0_Spare_MAX                          (3) // 0x00000003
  #define CH0CCC_CR_DDRCRPERBITTCO0_Spare_DEF                          (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO0_Spare_HSH                          (0x023C3658)

#define CH2CCC_CR_DDRCRPERBITTCO0_P0_REG                               (0x00003658)

  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC0_P0_OFF                        ( 0)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC0_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC0_P0_MSK                        (0x0000003F)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC0_P0_MIN                        (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC0_P0_MAX                        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC0_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC0_P0_HSH                        (0x86003658)

  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC1_P0_OFF                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC1_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC1_P0_MSK                        (0x00000FC0)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC1_P0_MIN                        (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC1_P0_MAX                        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC1_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC1_P0_HSH                        (0x860C3658)

  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC2_P0_OFF                        (12)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC2_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC2_P0_MSK                        (0x0003F000)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC2_P0_MIN                        (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC2_P0_MAX                        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC2_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC2_P0_HSH                        (0x86183658)

  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC3_P0_OFF                        (18)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC3_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC3_P0_MSK                        (0x00FC0000)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC3_P0_MIN                        (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC3_P0_MAX                        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC3_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC3_P0_HSH                        (0x86243658)

  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC4_P0_OFF                        (24)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC4_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC4_P0_MSK                        (0x3F000000)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC4_P0_MIN                        (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC4_P0_MAX                        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC4_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO0_CCC4_P0_HSH                        (0x86303658)

  #define CH2CCC_CR_DDRCRPERBITTCO0_Spare_P0_OFF                       (30)
  #define CH2CCC_CR_DDRCRPERBITTCO0_Spare_P0_WID                       ( 2)
  #define CH2CCC_CR_DDRCRPERBITTCO0_Spare_P0_MSK                       (0xC0000000)
  #define CH2CCC_CR_DDRCRPERBITTCO0_Spare_P0_MIN                       (0)
  #define CH2CCC_CR_DDRCRPERBITTCO0_Spare_P0_MAX                       (3) // 0x00000003
  #define CH2CCC_CR_DDRCRPERBITTCO0_Spare_P0_DEF                       (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO0_Spare_P0_HSH                       (0x023C3658)

#define CH0CCC_CR_DDRCRPERBITTCO1_REG                                  (0x0000365C)

  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC5_OFF                           ( 0)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC5_WID                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC5_MSK                           (0x0000003F)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC5_MIN                           (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC5_MAX                           (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC5_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC5_HSH                           (0x8600365C)

  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC6_OFF                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC6_WID                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC6_MSK                           (0x00000FC0)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC6_MIN                           (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC6_MAX                           (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC6_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC6_HSH                           (0x860C365C)

  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC7_OFF                           (12)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC7_WID                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC7_MSK                           (0x0003F000)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC7_MIN                           (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC7_MAX                           (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC7_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC7_HSH                           (0x8618365C)

  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC8_OFF                           (18)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC8_WID                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC8_MSK                           (0x00FC0000)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC8_MIN                           (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC8_MAX                           (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC8_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC8_HSH                           (0x8624365C)

  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC9_OFF                           (24)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC9_WID                           ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC9_MSK                           (0x3F000000)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC9_MIN                           (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC9_MAX                           (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC9_DEF                           (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO1_CCC9_HSH                           (0x8630365C)

  #define CH0CCC_CR_DDRCRPERBITTCO1_Spare_OFF                          (30)
  #define CH0CCC_CR_DDRCRPERBITTCO1_Spare_WID                          ( 2)
  #define CH0CCC_CR_DDRCRPERBITTCO1_Spare_MSK                          (0xC0000000)
  #define CH0CCC_CR_DDRCRPERBITTCO1_Spare_MIN                          (0)
  #define CH0CCC_CR_DDRCRPERBITTCO1_Spare_MAX                          (3) // 0x00000003
  #define CH0CCC_CR_DDRCRPERBITTCO1_Spare_DEF                          (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO1_Spare_HSH                          (0x023C365C)

#define CH2CCC_CR_DDRCRPERBITTCO1_P0_REG                               (0x0000365C)

  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC5_P0_OFF                        ( 0)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC5_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC5_P0_MSK                        (0x0000003F)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC5_P0_MIN                        (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC5_P0_MAX                        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC5_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC5_P0_HSH                        (0x8600365C)

  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC6_P0_OFF                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC6_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC6_P0_MSK                        (0x00000FC0)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC6_P0_MIN                        (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC6_P0_MAX                        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC6_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC6_P0_HSH                        (0x860C365C)

  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC7_P0_OFF                        (12)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC7_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC7_P0_MSK                        (0x0003F000)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC7_P0_MIN                        (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC7_P0_MAX                        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC7_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC7_P0_HSH                        (0x8618365C)

  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC8_P0_OFF                        (18)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC8_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC8_P0_MSK                        (0x00FC0000)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC8_P0_MIN                        (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC8_P0_MAX                        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC8_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC8_P0_HSH                        (0x8624365C)

  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC9_P0_OFF                        (24)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC9_P0_WID                        ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC9_P0_MSK                        (0x3F000000)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC9_P0_MIN                        (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC9_P0_MAX                        (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC9_P0_DEF                        (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO1_CCC9_P0_HSH                        (0x8630365C)

  #define CH2CCC_CR_DDRCRPERBITTCO1_EnClkRFFeedback_P0_OFF             (30)
  #define CH2CCC_CR_DDRCRPERBITTCO1_EnClkRFFeedback_P0_WID             ( 2)
  #define CH2CCC_CR_DDRCRPERBITTCO1_EnClkRFFeedback_P0_MSK             (0xC0000000)
  #define CH2CCC_CR_DDRCRPERBITTCO1_EnClkRFFeedback_P0_MIN             (0)
  #define CH2CCC_CR_DDRCRPERBITTCO1_EnClkRFFeedback_P0_MAX             (3) // 0x00000003
  #define CH2CCC_CR_DDRCRPERBITTCO1_EnClkRFFeedback_P0_DEF             (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO1_EnClkRFFeedback_P0_HSH             (0x023C365C)

#define CH0CCC_CR_DDRCRPERBITTCO2_REG                                  (0x00003660)

  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC10_OFF                          ( 0)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC10_WID                          ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC10_MSK                          (0x0000003F)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC10_MIN                          (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC10_MAX                          (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC10_DEF                          (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC10_HSH                          (0x86003660)

  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC11_OFF                          ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC11_WID                          ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC11_MSK                          (0x00000FC0)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC11_MIN                          (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC11_MAX                          (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC11_DEF                          (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC11_HSH                          (0x860C3660)

  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC12_OFF                          (12)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC12_WID                          ( 6)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC12_MSK                          (0x0003F000)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC12_MIN                          (-32)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC12_MAX                          (31) // 0x0000001F
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC12_DEF                          (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO2_CCC12_HSH                          (0x86183660)

  #define CH0CCC_CR_DDRCRPERBITTCO2_Spare_OFF                          (18)
  #define CH0CCC_CR_DDRCRPERBITTCO2_Spare_WID                          (14)
  #define CH0CCC_CR_DDRCRPERBITTCO2_Spare_MSK                          (0xFFFC0000)
  #define CH0CCC_CR_DDRCRPERBITTCO2_Spare_MIN                          (0)
  #define CH0CCC_CR_DDRCRPERBITTCO2_Spare_MAX                          (16383) // 0x00003FFF
  #define CH0CCC_CR_DDRCRPERBITTCO2_Spare_DEF                          (0x00000000)
  #define CH0CCC_CR_DDRCRPERBITTCO2_Spare_HSH                          (0x0E243660)

#define CH2CCC_CR_DDRCRPERBITTCO2_P0_REG                               (0x00003660)

  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC10_P0_OFF                       ( 0)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC10_P0_WID                       ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC10_P0_MSK                       (0x0000003F)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC10_P0_MIN                       (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC10_P0_MAX                       (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC10_P0_DEF                       (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC10_P0_HSH                       (0x86003660)

  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC11_P0_OFF                       ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC11_P0_WID                       ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC11_P0_MSK                       (0x00000FC0)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC11_P0_MIN                       (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC11_P0_MAX                       (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC11_P0_DEF                       (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC11_P0_HSH                       (0x860C3660)

  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC12_P0_OFF                       (12)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC12_P0_WID                       ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC12_P0_MSK                       (0x0003F000)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC12_P0_MIN                       (-32)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC12_P0_MAX                       (31) // 0x0000001F
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC12_P0_DEF                       (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC12_P0_HSH                       (0x86183660)

  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC13_P0_OFF                       (18)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC13_P0_WID                       ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC13_P0_MSK                       (0x00FC0000)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC13_P0_MIN                       (0)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC13_P0_MAX                       (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC13_P0_DEF                       (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC13_P0_HSH                       (0x06243660)

  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC14_P0_OFF                       (24)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC14_P0_WID                       ( 6)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC14_P0_MSK                       (0x3F000000)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC14_P0_MIN                       (0)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC14_P0_MAX                       (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC14_P0_DEF                       (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO2_CCC14_P0_HSH                       (0x06303660)

  #define CH2CCC_CR_DDRCRPERBITTCO2_EnClkRFFeedback_P0_OFF             (30)
  #define CH2CCC_CR_DDRCRPERBITTCO2_EnClkRFFeedback_P0_WID             ( 2)
  #define CH2CCC_CR_DDRCRPERBITTCO2_EnClkRFFeedback_P0_MSK             (0xC0000000)
  #define CH2CCC_CR_DDRCRPERBITTCO2_EnClkRFFeedback_P0_MIN             (0)
  #define CH2CCC_CR_DDRCRPERBITTCO2_EnClkRFFeedback_P0_MAX             (3) // 0x00000003
  #define CH2CCC_CR_DDRCRPERBITTCO2_EnClkRFFeedback_P0_DEF             (0x00000000)
  #define CH2CCC_CR_DDRCRPERBITTCO2_EnClkRFFeedback_P0_HSH             (0x023C3660)

#define CH0CCC_CR_DDRCRCCCPICODING1_REG                                (0x00003664)

  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode3_OFF                      ( 0)
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode3_WID                      ( 9)
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode3_MSK                      (0x000001FF)
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode3_MIN                      (0)
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode3_MAX                      (511) // 0x000001FF
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode3_DEF                      (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode3_HSH                      (0x09003664)

  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode4_OFF                      ( 9)
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode4_WID                      ( 9)
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode4_MSK                      (0x0003FE00)
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode4_MIN                      (0)
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode4_MAX                      (511) // 0x000001FF
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode4_DEF                      (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPICODING1_PiCode4_HSH                      (0x09123664)

  #define CH0CCC_CR_DDRCRCCCPICODING1_Reserved_OFF                     (18)
  #define CH0CCC_CR_DDRCRCCCPICODING1_Reserved_WID                     (14)
  #define CH0CCC_CR_DDRCRCCCPICODING1_Reserved_MSK                     (0xFFFC0000)
  #define CH0CCC_CR_DDRCRCCCPICODING1_Reserved_MIN                     (0)
  #define CH0CCC_CR_DDRCRCCCPICODING1_Reserved_MAX                     (16383) // 0x00003FFF
  #define CH0CCC_CR_DDRCRCCCPICODING1_Reserved_DEF                     (0x00000000)
  #define CH0CCC_CR_DDRCRCCCPICODING1_Reserved_HSH                     (0x0E243664)

#define CH2CCC_CR_DDRCRCCCPICODING1_P0_REG                             (0x00003664)

  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode3_P0_OFF                   ( 0)
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode3_P0_WID                   ( 9)
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode3_P0_MSK                   (0x000001FF)
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode3_P0_MIN                   (0)
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode3_P0_MAX                   (511) // 0x000001FF
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode3_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode3_P0_HSH                   (0x09003664)

  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode4_P0_OFF                   ( 9)
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode4_P0_WID                   ( 9)
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode4_P0_MSK                   (0x0003FE00)
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode4_P0_MIN                   (0)
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode4_P0_MAX                   (511) // 0x000001FF
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode4_P0_DEF                   (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPICODING1_PiCode4_P0_HSH                   (0x09123664)

  #define CH2CCC_CR_DDRCRCCCPICODING1_Reserved_P0_OFF                  (18)
  #define CH2CCC_CR_DDRCRCCCPICODING1_Reserved_P0_WID                  (14)
  #define CH2CCC_CR_DDRCRCCCPICODING1_Reserved_P0_MSK                  (0xFFFC0000)
  #define CH2CCC_CR_DDRCRCCCPICODING1_Reserved_P0_MIN                  (0)
  #define CH2CCC_CR_DDRCRCCCPICODING1_Reserved_P0_MAX                  (16383) // 0x00003FFF
  #define CH2CCC_CR_DDRCRCCCPICODING1_Reserved_P0_DEF                  (0x00000000)
  #define CH2CCC_CR_DDRCRCCCPICODING1_Reserved_P0_HSH                  (0x0E243664)

#define CH0CCC_CR_DDRCRMARGINMODECONTROL_REG                           (0x00003668)

  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_RunTest_OFF                 ( 0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_RunTest_WID                 ( 1)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_RunTest_MSK                 (0x00000001)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_RunTest_MIN                 (0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_RunTest_MAX                 (1) // 0x00000001
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_RunTest_DEF                 (0x00000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_RunTest_HSH                 (0x01003668)

  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_Param_OFF                   ( 1)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_Param_WID                   ( 3)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_Param_MSK                   (0x0000000E)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_Param_MIN                   (0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_Param_MAX                   (7) // 0x00000007
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_Param_DEF                   (0x00000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_Param_HSH                   (0x03023668)

  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinVal_OFF                  ( 4)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinVal_WID                  ( 7)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinVal_MSK                  (0x000007F0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinVal_MIN                  (0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinVal_MAX                  (127) // 0x0000007F
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinVal_DEF                  (0x00000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinVal_HSH                  (0x07083668)

  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_OFF                  (11)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_WID                  ( 7)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_MSK                  (0x0003F800)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_MIN                  (0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_MAX                  (127) // 0x0000007F
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_DEF                  (0x00000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_HSH                  (0x07163668)

  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_OFF                (18)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_WID                ( 6)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_MSK                (0x00FC0000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_MIN                (0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_MAX                (63) // 0x0000003F
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_DEF                (0x00000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_HSH                (0x06243668)

  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_OFF              (24)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_WID              ( 1)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_MSK              (0x01000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_MIN              (0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_MAX              (1) // 0x00000001
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_DEF              (0x00000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_HSH              (0x01303668)

  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_OFF              (25)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_WID              ( 4)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_MSK              (0x1E000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_MIN              (0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_MAX              (15) // 0x0000000F
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_DEF              (0x00000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_HSH              (0x04323668)

  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_OFF             (29)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_WID             ( 1)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_MSK             (0x20000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_MIN             (0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_MAX             (1) // 0x00000001
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_DEF             (0x00000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_HSH             (0x013A3668)

  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_OFF           (30)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_WID           ( 1)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_MSK           (0x40000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_MIN           (0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_MAX           (1) // 0x00000001
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_DEF           (0x00000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_HSH           (0x013C3668)

  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_OFF              (31)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_WID              ( 1)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_MSK              (0x80000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_MIN              (0)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_MAX              (1) // 0x00000001
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_DEF              (0x00000000)
  #define CH0CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_HSH              (0x013E3668)

#define CH2CCC_CR_DDRCRMARGINMODECONTROL_P0_REG                        (0x00003668)

  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_RunTest_P0_OFF              ( 0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_RunTest_P0_WID              ( 1)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_RunTest_P0_MSK              (0x00000001)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_RunTest_P0_MIN              (0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_RunTest_P0_MAX              (1) // 0x00000001
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_RunTest_P0_DEF              (0x00000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_RunTest_P0_HSH              (0x01003668)

  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_Param_P0_OFF                ( 1)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_Param_P0_WID                ( 3)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_Param_P0_MSK                (0x0000000E)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_Param_P0_MIN                (0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_Param_P0_MAX                (7) // 0x00000007
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_Param_P0_DEF                (0x00000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_Param_P0_HSH                (0x03023668)

  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinVal_P0_OFF               ( 4)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinVal_P0_WID               ( 7)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinVal_P0_MSK               (0x000007F0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinVal_P0_MIN               (0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinVal_P0_MAX               (127) // 0x0000007F
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinVal_P0_DEF               (0x00000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinVal_P0_HSH               (0x07083668)

  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_P0_OFF               (11)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_P0_WID               ( 7)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_P0_MSK               (0x0003F800)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_P0_MIN               (0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_P0_MAX               (127) // 0x0000007F
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_P0_DEF               (0x00000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MaxVal_P0_HSH               (0x07163668)

  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_P0_OFF             (18)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_P0_WID             ( 6)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_P0_MSK             (0x00FC0000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_P0_MIN             (0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_P0_MAX             (63) // 0x0000003F
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_P0_DEF             (0x00000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MinWidth_P0_HSH             (0x06243668)

  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_P0_OFF           (24)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_P0_WID           ( 1)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_P0_MSK           (0x01000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_P0_MIN           (0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_P0_MAX           (1) // 0x00000001
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_P0_DEF           (0x00000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_CalcCenter_P0_HSH           (0x01303668)

  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_P0_OFF           (25)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_P0_WID           ( 4)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_P0_MSK           (0x1E000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_P0_MIN           (0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_P0_MAX           (15) // 0x0000000F
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_P0_DEF           (0x00000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLBCycles_P0_HSH           (0x04323668)

  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_P0_OFF          (29)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_P0_WID          ( 1)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_P0_MSK          (0x20000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_P0_MIN          (0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_P0_MAX          (1) // 0x00000001
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_P0_DEF          (0x00000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_MisrRunOvrd_P0_HSH          (0x013A3668)

  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_P0_OFF        (30)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_P0_WID        ( 1)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_P0_MSK        (0x40000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_P0_MIN        (0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_P0_MAX        (1) // 0x00000001
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_P0_DEF        (0x00000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_IOLB_CPGCMode_P0_HSH        (0x013C3668)

  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_P0_OFF           (31)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_P0_WID           ( 1)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_P0_MSK           (0x80000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_P0_MIN           (0)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_P0_MAX           (1) // 0x00000001
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_P0_DEF           (0x00000000)
  #define CH2CCC_CR_DDRCRMARGINMODECONTROL_LaneResult_P0_HSH           (0x013E3668)

#define CH0CCC_CR_DDRCRMARGINMODEDEBUGMSB_REG                          (0x0000366C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH2CCC_CR_DDRCRMARGINMODEDEBUGMSB_P0_REG                       (0x0000366C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH0CCC_CR_DDRCRMARGINMODEDEBUGLSB_REG                          (0x00003670)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH2CCC_CR_DDRCRMARGINMODEDEBUGLSB_P0_REG                       (0x00003670)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH0CCC_CR_DCCLANESTATUS2_REG                                   (0x00003674)

  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeOffset_OFF                   ( 0)
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeOffset_WID                   ( 7)
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeOffset_MSK                   (0x0000007F)
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeOffset_MIN                   (0)
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeOffset_MAX                   (127) // 0x0000007F
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeOffset_DEF                   (0x00000000)
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeOffset_HSH                   (0x07003674)

  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeCount_OFF                    ( 7)
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeCount_WID                    ( 9)
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeCount_MSK                    (0x0000FF80)
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeCount_MIN                    (0)
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeCount_MAX                    (511) // 0x000001FF
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeCount_DEF                    (0x00000000)
  #define CH0CCC_CR_DCCLANESTATUS2_ExtremeCount_HSH                    (0x090E3674)

  #define CH0CCC_CR_DCCLANESTATUS2_rsvd_OFF                            (16)
  #define CH0CCC_CR_DCCLANESTATUS2_rsvd_WID                            (16)
  #define CH0CCC_CR_DCCLANESTATUS2_rsvd_MSK                            (0xFFFF0000)
  #define CH0CCC_CR_DCCLANESTATUS2_rsvd_MIN                            (0)
  #define CH0CCC_CR_DCCLANESTATUS2_rsvd_MAX                            (65535) // 0x0000FFFF
  #define CH0CCC_CR_DCCLANESTATUS2_rsvd_DEF                            (0x00000000)
  #define CH0CCC_CR_DCCLANESTATUS2_rsvd_HSH                            (0x10203674)

#define CH2CCC_CR_DCCLANESTATUS2_P0_REG                                (0x00003674)

  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeOffset_P0_OFF                ( 0)
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeOffset_P0_WID                ( 7)
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeOffset_P0_MSK                (0x0000007F)
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeOffset_P0_MIN                (0)
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeOffset_P0_MAX                (127) // 0x0000007F
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeOffset_P0_DEF                (0x00000000)
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeOffset_P0_HSH                (0x07003674)

  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeCount_P0_OFF                 ( 7)
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeCount_P0_WID                 ( 9)
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeCount_P0_MSK                 (0x0000FF80)
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeCount_P0_MIN                 (0)
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeCount_P0_MAX                 (511) // 0x000001FF
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeCount_P0_DEF                 (0x00000000)
  #define CH2CCC_CR_DCCLANESTATUS2_ExtremeCount_P0_HSH                 (0x090E3674)

  #define CH2CCC_CR_DCCLANESTATUS2_rsvd_P0_OFF                         (16)
  #define CH2CCC_CR_DCCLANESTATUS2_rsvd_P0_WID                         (16)
  #define CH2CCC_CR_DCCLANESTATUS2_rsvd_P0_MSK                         (0xFFFF0000)
  #define CH2CCC_CR_DCCLANESTATUS2_rsvd_P0_MIN                         (0)
  #define CH2CCC_CR_DCCLANESTATUS2_rsvd_P0_MAX                         (65535) // 0x0000FFFF
  #define CH2CCC_CR_DCCLANESTATUS2_rsvd_P0_DEF                         (0x00000000)
  #define CH2CCC_CR_DCCLANESTATUS2_rsvd_P0_HSH                         (0x10203674)

#define CH0CCC_CR_DDRCRCACOMP_P0_REG                                   (0x00003680)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH0CCC_CR_DDRCRCLKCOMP_P0_REG                                  (0x00003684)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH0CCC_CR_DDRCRCTLCOMP_P0_REG                                  (0x00003688)
//Duplicate of CH2CCC_CR_DDRCRCTLCOMP_P0_REG

#define CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG                       (0x0000368C)
//Duplicate of CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG

#define CH0CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG                          (0x00003690)
//Duplicate of CH2CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG

#define CH0CCC_CR_DDRCRCCCPIDIVIDER_P0_REG                             (0x00003694)
//Duplicate of CH2CCC_CR_DDRCRCCCPIDIVIDER_P0_REG

#define CH0CCC_CR_DDRCRCCCPICODING0_P0_REG                             (0x00003698)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING0_P0_REG

#define CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG                (0x0000369C)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG

#define CH0CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG                           (0x000036A0)
//Duplicate of CH2CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG

#define CH0CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG                         (0x000036A4)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG

#define CH0CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG                         (0x000036A8)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG

#define CH0CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG                         (0x000036AC)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG

#define CH0CCC_CR_DDRCRPINSUSED_P0_REG                                 (0x000036B0)
//Duplicate of CH2CCC_CR_DDRCRPINSUSED_P0_REG

#define CH0CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG                           (0x000036B4)
//Duplicate of CH2CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG

#define CH0CCC_CR_DDRCRBSCANDATA_P0_REG                                (0x000036B8)
//Duplicate of CH2CCC_CR_DDRCRBSCANDATA_P0_REG

#define CH0CCC_CR_DDRCRMISR_P0_REG                                     (0x000036BC)
//Duplicate of CH2CCC_CR_DDRCRMISR_P0_REG

#define CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG                (0x000036C0)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG

#define CH0CCC_CR_DCCFSMCONTROL_P0_REG                                 (0x000036C4)
//Duplicate of CH2CCC_CR_DCCFSMCONTROL_P0_REG

#define CH0CCC_CR_DCCCALCCONTROL_P0_REG                                (0x000036C8)
//Duplicate of CH2CCC_CR_DCCCALCCONTROL_P0_REG

#define CH0CCC_CR_DCCFSMSTATUS_P0_REG                                  (0x000036CC)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_P0_REG

#define CH0CCC_CR_DCCLANESTATUS0_P0_REG                                (0x000036D0)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_P0_REG

#define CH0CCC_CR_DCCLANESTATUS1_P0_REG                                (0x000036D4)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_P0_REG

#define CH0CCC_CR_DDRCRPERBITTCO0_P0_REG                               (0x000036D8)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO0_P0_REG

#define CH0CCC_CR_DDRCRPERBITTCO1_P0_REG                               (0x000036DC)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO1_P0_REG

#define CH0CCC_CR_DDRCRPERBITTCO2_P0_REG                               (0x000036E0)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO2_P0_REG

#define CH0CCC_CR_DDRCRCCCPICODING1_P0_REG                             (0x000036E4)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING1_P0_REG

#define CH0CCC_CR_DDRCRMARGINMODECONTROL_P0_REG                        (0x000036E8)
//Duplicate of CH2CCC_CR_DDRCRMARGINMODECONTROL_P0_REG

#define CH0CCC_CR_DDRCRMARGINMODEDEBUGMSB_P0_REG                       (0x000036EC)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH0CCC_CR_DDRCRMARGINMODEDEBUGLSB_P0_REG                       (0x000036F0)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH0CCC_CR_DCCLANESTATUS2_P0_REG                                (0x000036F4)
//Duplicate of CH2CCC_CR_DCCLANESTATUS2_P0_REG

#define CH1CCC_CR_DDRCRCACOMP_REG                                      (0x00003700)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define CH3CCC_CR_DDRCRCACOMP_P0_REG                                   (0x00003700)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH1CCC_CR_DDRCRCLKCOMP_REG                                     (0x00003704)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define CH3CCC_CR_DDRCRCLKCOMP_P0_REG                                  (0x00003704)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH1CCC_CR_DDRCRCTLCOMP_REG                                     (0x00003708)
//Duplicate of CH0CCC_CR_DDRCRCTLCOMP_REG

#define CH3CCC_CR_DDRCRCTLCOMP_P0_REG                                  (0x00003708)
//Duplicate of CH2CCC_CR_DDRCRCTLCOMP_P0_REG

#define CH1CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG                          (0x0000370C)
//Duplicate of CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG

#define CH3CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG                       (0x0000370C)
//Duplicate of CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG

#define CH1CCC_CR_DDRCRCTLCACOMPOFFSET_REG                             (0x00003710)
//Duplicate of CH0CCC_CR_DDRCRCTLCACOMPOFFSET_REG

#define CH3CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG                          (0x00003710)
//Duplicate of CH2CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG

#define CH1CCC_CR_DDRCRCCCPIDIVIDER_REG                                (0x00003714)
//Duplicate of CH0CCC_CR_DDRCRCCCPIDIVIDER_REG

#define CH3CCC_CR_DDRCRCCCPIDIVIDER_P0_REG                             (0x00003714)
//Duplicate of CH2CCC_CR_DDRCRCCCPIDIVIDER_P0_REG

#define CH1CCC_CR_DDRCRCCCPICODING0_REG                                (0x00003718)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING0_REG

#define CH3CCC_CR_DDRCRCCCPICODING0_P0_REG                             (0x00003718)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING0_P0_REG

#define CH1CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG                   (0x0000371C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG

#define CH3CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG                (0x0000371C)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG

#define CH1CCC_CR_DDRCRCCCVOLTAGEUSED_REG                              (0x00003720)
//Duplicate of CH0CCC_CR_DDRCRCCCVOLTAGEUSED_REG

#define CH3CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG                           (0x00003720)
//Duplicate of CH2CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG

#define CH1CCC_CR_DDRCRCCCPERBITDESKEW0_REG                            (0x00003724)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW0_REG

#define CH3CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG                         (0x00003724)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG

#define CH1CCC_CR_DDRCRCCCPERBITDESKEW1_REG                            (0x00003728)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW1_REG

#define CH3CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG                         (0x00003728)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG

#define CH1CCC_CR_DDRCRCCCPERBITDESKEW2_REG                            (0x0000372C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW2_REG

#define CH3CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG                         (0x0000372C)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG

#define CH1CCC_CR_DDRCRPINSUSED_REG                                    (0x00003730)
//Duplicate of CH0CCC_CR_DDRCRPINSUSED_REG

#define CH3CCC_CR_DDRCRPINSUSED_P0_REG                                 (0x00003730)
//Duplicate of CH2CCC_CR_DDRCRPINSUSED_P0_REG

#define CH1CCC_CR_DDRCRCCCCLKCONTROLS_REG                              (0x00003734)
//Duplicate of CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG

#define CH3CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG                           (0x00003734)
//Duplicate of CH2CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG

#define CH1CCC_CR_DDRCRBSCANDATA_REG                                   (0x00003738)
//Duplicate of CH0CCC_CR_DDRCRBSCANDATA_REG

#define CH3CCC_CR_DDRCRBSCANDATA_P0_REG                                (0x00003738)
//Duplicate of CH2CCC_CR_DDRCRBSCANDATA_P0_REG

#define CH1CCC_CR_DDRCRMISR_REG                                        (0x0000373C)
//Duplicate of CH0CCC_CR_DDRCRMISR_REG

#define CH3CCC_CR_DDRCRMISR_P0_REG                                     (0x0000373C)
//Duplicate of CH2CCC_CR_DDRCRMISR_P0_REG

#define CH1CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG                   (0x00003740)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG

#define CH3CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG                (0x00003740)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG

#define CH1CCC_CR_DCCFSMCONTROL_REG                                    (0x00003744)
//Duplicate of CH0CCC_CR_DCCFSMCONTROL_REG

#define CH3CCC_CR_DCCFSMCONTROL_P0_REG                                 (0x00003744)
//Duplicate of CH2CCC_CR_DCCFSMCONTROL_P0_REG

#define CH1CCC_CR_DCCCALCCONTROL_REG                                   (0x00003748)
//Duplicate of CH0CCC_CR_DCCCALCCONTROL_REG

#define CH3CCC_CR_DCCCALCCONTROL_P0_REG                                (0x00003748)
//Duplicate of CH2CCC_CR_DCCCALCCONTROL_P0_REG

#define CH1CCC_CR_DCCFSMSTATUS_REG                                     (0x0000374C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define CH3CCC_CR_DCCFSMSTATUS_P0_REG                                  (0x0000374C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_P0_REG

#define CH1CCC_CR_DCCLANESTATUS0_REG                                   (0x00003750)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define CH3CCC_CR_DCCLANESTATUS0_P0_REG                                (0x00003750)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_P0_REG

#define CH1CCC_CR_DCCLANESTATUS1_REG                                   (0x00003754)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define CH3CCC_CR_DCCLANESTATUS1_P0_REG                                (0x00003754)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_P0_REG

#define CH1CCC_CR_DDRCRPERBITTCO0_REG                                  (0x00003758)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO0_REG

#define CH3CCC_CR_DDRCRPERBITTCO0_P0_REG                               (0x00003758)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO0_P0_REG

#define CH1CCC_CR_DDRCRPERBITTCO1_REG                                  (0x0000375C)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO1_REG

#define CH3CCC_CR_DDRCRPERBITTCO1_P0_REG                               (0x0000375C)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO1_P0_REG

#define CH1CCC_CR_DDRCRPERBITTCO2_REG                                  (0x00003760)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO2_REG

#define CH3CCC_CR_DDRCRPERBITTCO2_P0_REG                               (0x00003760)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO2_P0_REG

#define CH1CCC_CR_DDRCRCCCPICODING1_REG                                (0x00003764)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING1_REG

#define CH3CCC_CR_DDRCRCCCPICODING1_P0_REG                             (0x00003764)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING1_P0_REG

#define CH1CCC_CR_DDRCRMARGINMODECONTROL_REG                           (0x00003768)
//Duplicate of CH0CCC_CR_DDRCRMARGINMODECONTROL_REG

#define CH3CCC_CR_DDRCRMARGINMODECONTROL_P0_REG                        (0x00003768)
//Duplicate of CH2CCC_CR_DDRCRMARGINMODECONTROL_P0_REG

#define CH1CCC_CR_DDRCRMARGINMODEDEBUGMSB_REG                          (0x0000376C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH3CCC_CR_DDRCRMARGINMODEDEBUGMSB_P0_REG                       (0x0000376C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH1CCC_CR_DDRCRMARGINMODEDEBUGLSB_REG                          (0x00003770)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH3CCC_CR_DDRCRMARGINMODEDEBUGLSB_P0_REG                       (0x00003770)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH1CCC_CR_DCCLANESTATUS2_REG                                   (0x00003774)
//Duplicate of CH0CCC_CR_DCCLANESTATUS2_REG

#define CH3CCC_CR_DCCLANESTATUS2_P0_REG                                (0x00003774)
//Duplicate of CH2CCC_CR_DCCLANESTATUS2_P0_REG

#define CH1CCC_CR_DDRCRCACOMP_P0_REG                                   (0x00003780)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH1CCC_CR_DDRCRCLKCOMP_P0_REG                                  (0x00003784)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH1CCC_CR_DDRCRCTLCOMP_P0_REG                                  (0x00003788)
//Duplicate of CH2CCC_CR_DDRCRCTLCOMP_P0_REG

#define CH1CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG                       (0x0000378C)
//Duplicate of CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG

#define CH1CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG                          (0x00003790)
//Duplicate of CH2CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG

#define CH1CCC_CR_DDRCRCCCPIDIVIDER_P0_REG                             (0x00003794)
//Duplicate of CH2CCC_CR_DDRCRCCCPIDIVIDER_P0_REG

#define CH1CCC_CR_DDRCRCCCPICODING0_P0_REG                             (0x00003798)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING0_P0_REG

#define CH1CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG                (0x0000379C)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG

#define CH1CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG                           (0x000037A0)
//Duplicate of CH2CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG

#define CH1CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG                         (0x000037A4)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG

#define CH1CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG                         (0x000037A8)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG

#define CH1CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG                         (0x000037AC)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG

#define CH1CCC_CR_DDRCRPINSUSED_P0_REG                                 (0x000037B0)
//Duplicate of CH2CCC_CR_DDRCRPINSUSED_P0_REG

#define CH1CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG                           (0x000037B4)
//Duplicate of CH2CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG

#define CH1CCC_CR_DDRCRBSCANDATA_P0_REG                                (0x000037B8)
//Duplicate of CH2CCC_CR_DDRCRBSCANDATA_P0_REG

#define CH1CCC_CR_DDRCRMISR_P0_REG                                     (0x000037BC)
//Duplicate of CH2CCC_CR_DDRCRMISR_P0_REG

#define CH1CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG                (0x000037C0)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG

#define CH1CCC_CR_DCCFSMCONTROL_P0_REG                                 (0x000037C4)
//Duplicate of CH2CCC_CR_DCCFSMCONTROL_P0_REG

#define CH1CCC_CR_DCCCALCCONTROL_P0_REG                                (0x000037C8)
//Duplicate of CH2CCC_CR_DCCCALCCONTROL_P0_REG

#define CH1CCC_CR_DCCFSMSTATUS_P0_REG                                  (0x000037CC)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_P0_REG

#define CH1CCC_CR_DCCLANESTATUS0_P0_REG                                (0x000037D0)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_P0_REG

#define CH1CCC_CR_DCCLANESTATUS1_P0_REG                                (0x000037D4)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_P0_REG

#define CH1CCC_CR_DDRCRPERBITTCO0_P0_REG                               (0x000037D8)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO0_P0_REG

#define CH1CCC_CR_DDRCRPERBITTCO1_P0_REG                               (0x000037DC)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO1_P0_REG

#define CH1CCC_CR_DDRCRPERBITTCO2_P0_REG                               (0x000037E0)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO2_P0_REG

#define CH1CCC_CR_DDRCRCCCPICODING1_P0_REG                             (0x000037E4)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING1_P0_REG

#define CH1CCC_CR_DDRCRMARGINMODECONTROL_P0_REG                        (0x000037E8)
//Duplicate of CH2CCC_CR_DDRCRMARGINMODECONTROL_P0_REG

#define CH1CCC_CR_DDRCRMARGINMODEDEBUGMSB_P0_REG                       (0x000037EC)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH1CCC_CR_DDRCRMARGINMODEDEBUGLSB_P0_REG                       (0x000037F0)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH1CCC_CR_DCCLANESTATUS2_P0_REG                                (0x000037F4)
//Duplicate of CH2CCC_CR_DCCLANESTATUS2_P0_REG

#define CH2CCC_CR_DDRCRCACOMP_REG                                      (0x00003800)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define CH5CCC_CR_DDRCRCACOMP_P0_REG                                   (0x00003800)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH2CCC_CR_DDRCRCLKCOMP_REG                                     (0x00003804)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define CH5CCC_CR_DDRCRCLKCOMP_P0_REG                                  (0x00003804)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH2CCC_CR_DDRCRCTLCOMP_REG                                     (0x00003808)
//Duplicate of CH0CCC_CR_DDRCRCTLCOMP_REG

#define CH5CCC_CR_DDRCRCTLCOMP_P0_REG                                  (0x00003808)
//Duplicate of CH2CCC_CR_DDRCRCTLCOMP_P0_REG

#define CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG                          (0x0000380C)
//Duplicate of CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG

#define CH5CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG                       (0x0000380C)
//Duplicate of CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG

#define CH2CCC_CR_DDRCRCTLCACOMPOFFSET_REG                             (0x00003810)
//Duplicate of CH0CCC_CR_DDRCRCTLCACOMPOFFSET_REG

#define CH5CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG                          (0x00003810)
//Duplicate of CH2CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG

#define CH2CCC_CR_DDRCRCCCPIDIVIDER_REG                                (0x00003814)
//Duplicate of CH0CCC_CR_DDRCRCCCPIDIVIDER_REG

#define CH5CCC_CR_DDRCRCCCPIDIVIDER_P0_REG                             (0x00003814)
//Duplicate of CH2CCC_CR_DDRCRCCCPIDIVIDER_P0_REG

#define CH2CCC_CR_DDRCRCCCPICODING0_REG                                (0x00003818)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING0_REG

#define CH5CCC_CR_DDRCRCCCPICODING0_P0_REG                             (0x00003818)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING0_P0_REG

#define CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG                   (0x0000381C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG

#define CH5CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG                (0x0000381C)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG

#define CH2CCC_CR_DDRCRCCCVOLTAGEUSED_REG                              (0x00003820)
//Duplicate of CH0CCC_CR_DDRCRCCCVOLTAGEUSED_REG

#define CH5CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG                           (0x00003820)
//Duplicate of CH2CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG

#define CH2CCC_CR_DDRCRCCCPERBITDESKEW0_REG                            (0x00003824)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW0_REG

#define CH5CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG                         (0x00003824)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG

#define CH2CCC_CR_DDRCRCCCPERBITDESKEW1_REG                            (0x00003828)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW1_REG

#define CH5CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG                         (0x00003828)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG

#define CH2CCC_CR_DDRCRCCCPERBITDESKEW2_REG                            (0x0000382C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW2_REG

#define CH5CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG                         (0x0000382C)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG

#define CH2CCC_CR_DDRCRPINSUSED_REG                                    (0x00003830)
//Duplicate of CH0CCC_CR_DDRCRPINSUSED_REG

#define CH5CCC_CR_DDRCRPINSUSED_P0_REG                                 (0x00003830)
//Duplicate of CH2CCC_CR_DDRCRPINSUSED_P0_REG

#define CH2CCC_CR_DDRCRCCCCLKCONTROLS_REG                              (0x00003834)
//Duplicate of CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG

#define CH5CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG                           (0x00003834)
//Duplicate of CH2CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG

#define CH2CCC_CR_DDRCRBSCANDATA_REG                                   (0x00003838)
//Duplicate of CH0CCC_CR_DDRCRBSCANDATA_REG

#define CH5CCC_CR_DDRCRBSCANDATA_P0_REG                                (0x00003838)
//Duplicate of CH2CCC_CR_DDRCRBSCANDATA_P0_REG

#define CH2CCC_CR_DDRCRMISR_REG                                        (0x0000383C)
//Duplicate of CH0CCC_CR_DDRCRMISR_REG

#define CH5CCC_CR_DDRCRMISR_P0_REG                                     (0x0000383C)
//Duplicate of CH2CCC_CR_DDRCRMISR_P0_REG

#define CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG                   (0x00003840)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG

#define CH5CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG                (0x00003840)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG

#define CH2CCC_CR_DCCFSMCONTROL_REG                                    (0x00003844)
//Duplicate of CH0CCC_CR_DCCFSMCONTROL_REG

#define CH5CCC_CR_DCCFSMCONTROL_P0_REG                                 (0x00003844)
//Duplicate of CH2CCC_CR_DCCFSMCONTROL_P0_REG

#define CH2CCC_CR_DCCCALCCONTROL_REG                                   (0x00003848)
//Duplicate of CH0CCC_CR_DCCCALCCONTROL_REG

#define CH5CCC_CR_DCCCALCCONTROL_P0_REG                                (0x00003848)
//Duplicate of CH2CCC_CR_DCCCALCCONTROL_P0_REG

#define CH2CCC_CR_DCCFSMSTATUS_REG                                     (0x0000384C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define CH5CCC_CR_DCCFSMSTATUS_P0_REG                                  (0x0000384C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_P0_REG

#define CH2CCC_CR_DCCLANESTATUS0_REG                                   (0x00003850)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define CH5CCC_CR_DCCLANESTATUS0_P0_REG                                (0x00003850)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_P0_REG

#define CH2CCC_CR_DCCLANESTATUS1_REG                                   (0x00003854)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define CH5CCC_CR_DCCLANESTATUS1_P0_REG                                (0x00003854)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_P0_REG

#define CH2CCC_CR_DDRCRPERBITTCO0_REG                                  (0x00003858)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO0_REG

#define CH5CCC_CR_DDRCRPERBITTCO0_P0_REG                               (0x00003858)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO0_P0_REG

#define CH2CCC_CR_DDRCRPERBITTCO1_REG                                  (0x0000385C)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO1_REG

#define CH5CCC_CR_DDRCRPERBITTCO1_P0_REG                               (0x0000385C)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO1_P0_REG

#define CH2CCC_CR_DDRCRPERBITTCO2_REG                                  (0x00003860)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO2_REG

#define CH5CCC_CR_DDRCRPERBITTCO2_P0_REG                               (0x00003860)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO2_P0_REG

#define CH2CCC_CR_DDRCRCCCPICODING1_REG                                (0x00003864)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING1_REG

#define CH5CCC_CR_DDRCRCCCPICODING1_P0_REG                             (0x00003864)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING1_P0_REG

#define CH2CCC_CR_DDRCRMARGINMODECONTROL_REG                           (0x00003868)
//Duplicate of CH0CCC_CR_DDRCRMARGINMODECONTROL_REG

#define CH5CCC_CR_DDRCRMARGINMODECONTROL_P0_REG                        (0x00003868)
//Duplicate of CH2CCC_CR_DDRCRMARGINMODECONTROL_P0_REG

#define CH2CCC_CR_DDRCRMARGINMODEDEBUGMSB_REG                          (0x0000386C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH5CCC_CR_DDRCRMARGINMODEDEBUGMSB_P0_REG                       (0x0000386C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH2CCC_CR_DDRCRMARGINMODEDEBUGLSB_REG                          (0x00003870)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH5CCC_CR_DDRCRMARGINMODEDEBUGLSB_P0_REG                       (0x00003870)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH2CCC_CR_DCCLANESTATUS2_REG                                   (0x00003874)
//Duplicate of CH0CCC_CR_DCCLANESTATUS2_REG

#define CH5CCC_CR_DCCLANESTATUS2_P0_REG                                (0x00003874)
//Duplicate of CH2CCC_CR_DCCLANESTATUS2_P0_REG

#define CH7CCC_CR_DDRCRCACOMP_P0_REG                                   (0x00003880)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH7CCC_CR_DDRCRCLKCOMP_P0_REG                                  (0x00003884)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH7CCC_CR_DDRCRCTLCOMP_P0_REG                                  (0x00003888)
//Duplicate of CH2CCC_CR_DDRCRCTLCOMP_P0_REG

#define CH7CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG                       (0x0000388C)
//Duplicate of CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG

#define CH7CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG                          (0x00003890)
//Duplicate of CH2CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG

#define CH7CCC_CR_DDRCRCCCPIDIVIDER_P0_REG                             (0x00003894)
//Duplicate of CH2CCC_CR_DDRCRCCCPIDIVIDER_P0_REG

#define CH7CCC_CR_DDRCRCCCPICODING0_P0_REG                             (0x00003898)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING0_P0_REG

#define CH7CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG                (0x0000389C)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG

#define CH7CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG                           (0x000038A0)
//Duplicate of CH2CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG

#define CH7CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG                         (0x000038A4)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG

#define CH7CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG                         (0x000038A8)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG

#define CH7CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG                         (0x000038AC)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG

#define CH7CCC_CR_DDRCRPINSUSED_P0_REG                                 (0x000038B0)
//Duplicate of CH2CCC_CR_DDRCRPINSUSED_P0_REG

#define CH7CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG                           (0x000038B4)
//Duplicate of CH2CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG

#define CH7CCC_CR_DDRCRBSCANDATA_P0_REG                                (0x000038B8)
//Duplicate of CH2CCC_CR_DDRCRBSCANDATA_P0_REG

#define CH7CCC_CR_DDRCRMISR_P0_REG                                     (0x000038BC)
//Duplicate of CH2CCC_CR_DDRCRMISR_P0_REG

#define CH7CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG                (0x000038C0)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG

#define CH7CCC_CR_DCCFSMCONTROL_P0_REG                                 (0x000038C4)
//Duplicate of CH2CCC_CR_DCCFSMCONTROL_P0_REG

#define CH7CCC_CR_DCCCALCCONTROL_P0_REG                                (0x000038C8)
//Duplicate of CH2CCC_CR_DCCCALCCONTROL_P0_REG

#define CH7CCC_CR_DCCFSMSTATUS_P0_REG                                  (0x000038CC)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_P0_REG

#define CH7CCC_CR_DCCLANESTATUS0_P0_REG                                (0x000038D0)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_P0_REG

#define CH7CCC_CR_DCCLANESTATUS1_P0_REG                                (0x000038D4)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_P0_REG

#define CH7CCC_CR_DDRCRPERBITTCO0_P0_REG                               (0x000038D8)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO0_P0_REG

#define CH7CCC_CR_DDRCRPERBITTCO1_P0_REG                               (0x000038DC)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO1_P0_REG

#define CH7CCC_CR_DDRCRPERBITTCO2_P0_REG                               (0x000038E0)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO2_P0_REG

#define CH7CCC_CR_DDRCRCCCPICODING1_P0_REG                             (0x000038E4)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING1_P0_REG

#define CH7CCC_CR_DDRCRMARGINMODECONTROL_P0_REG                        (0x000038E8)
//Duplicate of CH2CCC_CR_DDRCRMARGINMODECONTROL_P0_REG

#define CH7CCC_CR_DDRCRMARGINMODEDEBUGMSB_P0_REG                       (0x000038EC)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH7CCC_CR_DDRCRMARGINMODEDEBUGLSB_P0_REG                       (0x000038F0)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH7CCC_CR_DCCLANESTATUS2_P0_REG                                (0x000038F4)
//Duplicate of CH2CCC_CR_DCCLANESTATUS2_P0_REG

#define CH3CCC_CR_DDRCRCACOMP_REG                                      (0x00003900)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define CH4CCC_CR_DDRCRCACOMP_P0_REG                                   (0x00003900)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH3CCC_CR_DDRCRCLKCOMP_REG                                     (0x00003904)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define CH4CCC_CR_DDRCRCLKCOMP_P0_REG                                  (0x00003904)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH3CCC_CR_DDRCRCTLCOMP_REG                                     (0x00003908)
//Duplicate of CH0CCC_CR_DDRCRCTLCOMP_REG

#define CH4CCC_CR_DDRCRCTLCOMP_P0_REG                                  (0x00003908)
//Duplicate of CH2CCC_CR_DDRCRCTLCOMP_P0_REG

#define CH3CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG                          (0x0000390C)
//Duplicate of CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG

#define CH4CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG                       (0x0000390C)
//Duplicate of CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG

#define CH3CCC_CR_DDRCRCTLCACOMPOFFSET_REG                             (0x00003910)
//Duplicate of CH0CCC_CR_DDRCRCTLCACOMPOFFSET_REG

#define CH4CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG                          (0x00003910)
//Duplicate of CH2CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG

#define CH3CCC_CR_DDRCRCCCPIDIVIDER_REG                                (0x00003914)
//Duplicate of CH0CCC_CR_DDRCRCCCPIDIVIDER_REG

#define CH4CCC_CR_DDRCRCCCPIDIVIDER_P0_REG                             (0x00003914)
//Duplicate of CH2CCC_CR_DDRCRCCCPIDIVIDER_P0_REG

#define CH3CCC_CR_DDRCRCCCPICODING0_REG                                (0x00003918)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING0_REG

#define CH4CCC_CR_DDRCRCCCPICODING0_P0_REG                             (0x00003918)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING0_P0_REG

#define CH3CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG                   (0x0000391C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG

#define CH4CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG                (0x0000391C)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG

#define CH3CCC_CR_DDRCRCCCVOLTAGEUSED_REG                              (0x00003920)
//Duplicate of CH0CCC_CR_DDRCRCCCVOLTAGEUSED_REG

#define CH4CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG                           (0x00003920)
//Duplicate of CH2CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG

#define CH3CCC_CR_DDRCRCCCPERBITDESKEW0_REG                            (0x00003924)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW0_REG

#define CH4CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG                         (0x00003924)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG

#define CH3CCC_CR_DDRCRCCCPERBITDESKEW1_REG                            (0x00003928)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW1_REG

#define CH4CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG                         (0x00003928)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG

#define CH3CCC_CR_DDRCRCCCPERBITDESKEW2_REG                            (0x0000392C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW2_REG

#define CH4CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG                         (0x0000392C)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG

#define CH3CCC_CR_DDRCRPINSUSED_REG                                    (0x00003930)
//Duplicate of CH0CCC_CR_DDRCRPINSUSED_REG

#define CH4CCC_CR_DDRCRPINSUSED_P0_REG                                 (0x00003930)
//Duplicate of CH2CCC_CR_DDRCRPINSUSED_P0_REG

#define CH3CCC_CR_DDRCRCCCCLKCONTROLS_REG                              (0x00003934)
//Duplicate of CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG

#define CH4CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG                           (0x00003934)
//Duplicate of CH2CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG

#define CH3CCC_CR_DDRCRBSCANDATA_REG                                   (0x00003938)
//Duplicate of CH0CCC_CR_DDRCRBSCANDATA_REG

#define CH4CCC_CR_DDRCRBSCANDATA_P0_REG                                (0x00003938)
//Duplicate of CH2CCC_CR_DDRCRBSCANDATA_P0_REG

#define CH3CCC_CR_DDRCRMISR_REG                                        (0x0000393C)
//Duplicate of CH0CCC_CR_DDRCRMISR_REG

#define CH4CCC_CR_DDRCRMISR_P0_REG                                     (0x0000393C)
//Duplicate of CH2CCC_CR_DDRCRMISR_P0_REG

#define CH3CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG                   (0x00003940)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG

#define CH4CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG                (0x00003940)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG

#define CH3CCC_CR_DCCFSMCONTROL_REG                                    (0x00003944)
//Duplicate of CH0CCC_CR_DCCFSMCONTROL_REG

#define CH4CCC_CR_DCCFSMCONTROL_P0_REG                                 (0x00003944)
//Duplicate of CH2CCC_CR_DCCFSMCONTROL_P0_REG

#define CH3CCC_CR_DCCCALCCONTROL_REG                                   (0x00003948)
//Duplicate of CH0CCC_CR_DCCCALCCONTROL_REG

#define CH4CCC_CR_DCCCALCCONTROL_P0_REG                                (0x00003948)
//Duplicate of CH2CCC_CR_DCCCALCCONTROL_P0_REG

#define CH3CCC_CR_DCCFSMSTATUS_REG                                     (0x0000394C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define CH4CCC_CR_DCCFSMSTATUS_P0_REG                                  (0x0000394C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_P0_REG

#define CH3CCC_CR_DCCLANESTATUS0_REG                                   (0x00003950)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define CH4CCC_CR_DCCLANESTATUS0_P0_REG                                (0x00003950)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_P0_REG

#define CH3CCC_CR_DCCLANESTATUS1_REG                                   (0x00003954)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define CH4CCC_CR_DCCLANESTATUS1_P0_REG                                (0x00003954)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_P0_REG

#define CH3CCC_CR_DDRCRPERBITTCO0_REG                                  (0x00003958)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO0_REG

#define CH4CCC_CR_DDRCRPERBITTCO0_P0_REG                               (0x00003958)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO0_P0_REG

#define CH3CCC_CR_DDRCRPERBITTCO1_REG                                  (0x0000395C)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO1_REG

#define CH4CCC_CR_DDRCRPERBITTCO1_P0_REG                               (0x0000395C)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO1_P0_REG

#define CH3CCC_CR_DDRCRPERBITTCO2_REG                                  (0x00003960)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO2_REG

#define CH4CCC_CR_DDRCRPERBITTCO2_P0_REG                               (0x00003960)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO2_P0_REG

#define CH3CCC_CR_DDRCRCCCPICODING1_REG                                (0x00003964)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING1_REG

#define CH4CCC_CR_DDRCRCCCPICODING1_P0_REG                             (0x00003964)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING1_P0_REG

#define CH3CCC_CR_DDRCRMARGINMODECONTROL_REG                           (0x00003968)
//Duplicate of CH0CCC_CR_DDRCRMARGINMODECONTROL_REG

#define CH4CCC_CR_DDRCRMARGINMODECONTROL_P0_REG                        (0x00003968)
//Duplicate of CH2CCC_CR_DDRCRMARGINMODECONTROL_P0_REG

#define CH3CCC_CR_DDRCRMARGINMODEDEBUGMSB_REG                          (0x0000396C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH4CCC_CR_DDRCRMARGINMODEDEBUGMSB_P0_REG                       (0x0000396C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH3CCC_CR_DDRCRMARGINMODEDEBUGLSB_REG                          (0x00003970)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH4CCC_CR_DDRCRMARGINMODEDEBUGLSB_P0_REG                       (0x00003970)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH3CCC_CR_DCCLANESTATUS2_REG                                   (0x00003974)
//Duplicate of CH0CCC_CR_DCCLANESTATUS2_REG

#define CH4CCC_CR_DCCLANESTATUS2_P0_REG                                (0x00003974)
//Duplicate of CH2CCC_CR_DCCLANESTATUS2_P0_REG

#define CH6CCC_CR_DDRCRCACOMP_P0_REG                                   (0x00003980)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH6CCC_CR_DDRCRCLKCOMP_P0_REG                                  (0x00003984)
//Duplicate of CH2CCC_CR_DDRCRCACOMP_P0_REG

#define CH6CCC_CR_DDRCRCTLCOMP_P0_REG                                  (0x00003988)
//Duplicate of CH2CCC_CR_DDRCRCTLCOMP_P0_REG

#define CH6CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG                       (0x0000398C)
//Duplicate of CH2CCC_CR_DDRCRVSSHICLKCOMPOFFSET_P0_REG

#define CH6CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG                          (0x00003990)
//Duplicate of CH2CCC_CR_DDRCRCTLCACOMPOFFSET_P0_REG

#define CH6CCC_CR_DDRCRCCCPIDIVIDER_P0_REG                             (0x00003994)
//Duplicate of CH2CCC_CR_DDRCRCCCPIDIVIDER_P0_REG

#define CH6CCC_CR_DDRCRCCCPICODING0_P0_REG                             (0x00003998)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING0_P0_REG

#define CH6CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG                (0x0000399C)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_P0_REG

#define CH6CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG                           (0x000039A0)
//Duplicate of CH2CCC_CR_DDRCRCCCVOLTAGEUSED_P0_REG

#define CH6CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG                         (0x000039A4)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW0_P0_REG

#define CH6CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG                         (0x000039A8)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW1_P0_REG

#define CH6CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG                         (0x000039AC)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEW2_P0_REG

#define CH6CCC_CR_DDRCRPINSUSED_P0_REG                                 (0x000039B0)
//Duplicate of CH2CCC_CR_DDRCRPINSUSED_P0_REG

#define CH6CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG                           (0x000039B4)
//Duplicate of CH2CCC_CR_DDRCRCCCCLKCONTROLS_P0_REG

#define CH6CCC_CR_DDRCRBSCANDATA_P0_REG                                (0x000039B8)
//Duplicate of CH2CCC_CR_DDRCRBSCANDATA_P0_REG

#define CH6CCC_CR_DDRCRMISR_P0_REG                                     (0x000039BC)
//Duplicate of CH2CCC_CR_DDRCRMISR_P0_REG

#define CH6CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG                (0x000039C0)
//Duplicate of CH2CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_P0_REG

#define CH6CCC_CR_DCCFSMCONTROL_P0_REG                                 (0x000039C4)
//Duplicate of CH2CCC_CR_DCCFSMCONTROL_P0_REG

#define CH6CCC_CR_DCCCALCCONTROL_P0_REG                                (0x000039C8)
//Duplicate of CH2CCC_CR_DCCCALCCONTROL_P0_REG

#define CH6CCC_CR_DCCFSMSTATUS_P0_REG                                  (0x000039CC)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_P0_REG

#define CH6CCC_CR_DCCLANESTATUS0_P0_REG                                (0x000039D0)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_P0_REG

#define CH6CCC_CR_DCCLANESTATUS1_P0_REG                                (0x000039D4)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_P0_REG

#define CH6CCC_CR_DDRCRPERBITTCO0_P0_REG                               (0x000039D8)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO0_P0_REG

#define CH6CCC_CR_DDRCRPERBITTCO1_P0_REG                               (0x000039DC)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO1_P0_REG

#define CH6CCC_CR_DDRCRPERBITTCO2_P0_REG                               (0x000039E0)
//Duplicate of CH2CCC_CR_DDRCRPERBITTCO2_P0_REG

#define CH6CCC_CR_DDRCRCCCPICODING1_P0_REG                             (0x000039E4)
//Duplicate of CH2CCC_CR_DDRCRCCCPICODING1_P0_REG

#define CH6CCC_CR_DDRCRMARGINMODECONTROL_P0_REG                        (0x000039E8)
//Duplicate of CH2CCC_CR_DDRCRMARGINMODECONTROL_P0_REG

#define CH6CCC_CR_DDRCRMARGINMODEDEBUGMSB_P0_REG                       (0x000039EC)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH6CCC_CR_DDRCRMARGINMODEDEBUGLSB_P0_REG                       (0x000039F0)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_P0_REG

#define CH6CCC_CR_DCCLANESTATUS2_P0_REG                                (0x000039F4)
//Duplicate of CH2CCC_CR_DCCLANESTATUS2_P0_REG

#define CH4CCC_CR_DDRCRCACOMP_REG                                      (0x00003A00)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define DDRVTT0_CR_DDRCRVTTGENCONTROL_P0_REG                           (0x00003A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Target_P0_OFF                  ( 0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Target_P0_WID                  ( 8)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Target_P0_MSK                  (0x000000FF)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Target_P0_MIN                  (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Target_P0_MAX                  (255) // 0x000000FF
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Target_P0_DEF                  (0x0000004C)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Target_P0_HSH                  (0x08003A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic0_P0_OFF                  ( 8)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic0_P0_WID                  ( 4)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic0_P0_MSK                  (0x00000F00)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic0_P0_MIN                  (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic0_P0_MAX                  (15) // 0x0000000F
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic0_P0_DEF                  (0x00000005)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic0_P0_HSH                  (0x04103A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic1_P0_OFF                  (12)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic1_P0_WID                  ( 5)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic1_P0_MSK                  (0x0001F000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic1_P0_MIN                  (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic1_P0_MAX                  (31) // 0x0000001F
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic1_P0_DEF                  (0x00000009)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Panic1_P0_HSH                  (0x05183A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare1_P0_OFF                  (17)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare1_P0_WID                  ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare1_P0_MSK                  (0x00020000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare1_P0_MIN                  (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare1_P0_MAX                  (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare1_P0_DEF                  (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare1_P0_HSH                  (0x01223A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DisOffset_P0_OFF               (18)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DisOffset_P0_WID               ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DisOffset_P0_MSK               (0x00040000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DisOffset_P0_MIN               (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DisOffset_P0_MAX               (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DisOffset_P0_DEF               (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DisOffset_P0_HSH               (0x01243A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare3_P0_OFF                  (19)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare3_P0_WID                  ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare3_P0_MSK                  (0x00080000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare3_P0_MIN                  (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare3_P0_MAX                  (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare3_P0_DEF                  (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare3_P0_HSH                  (0x01263A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnDacPM_P0_OFF                 (20)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnDacPM_P0_WID                 ( 2)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnDacPM_P0_MSK                 (0x00300000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnDacPM_P0_MIN                 (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnDacPM_P0_MAX                 (3) // 0x00000003
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnDacPM_P0_DEF                 (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnDacPM_P0_HSH                 (0x02283A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_P0_OFF         (22)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_P0_WID         ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_P0_MSK         (0x00400000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_P0_MIN         (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_P0_MAX         (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_P0_DEF         (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_P0_HSH         (0x012C3A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_P0_OFF                (23)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_P0_WID                ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_P0_MSK                (0x00800000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_P0_MIN                (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_P0_MAX                (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_P0_DEF                (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_P0_HSH                (0x012E3A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_WakeUpDelay_P0_OFF             (24)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_WakeUpDelay_P0_WID             ( 3)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_WakeUpDelay_P0_MSK             (0x07000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_WakeUpDelay_P0_MIN             (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_WakeUpDelay_P0_MAX             (7) // 0x00000007
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_WakeUpDelay_P0_DEF             (0x00000001)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_WakeUpDelay_P0_HSH             (0x03303A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_UseFLLDuringDVFS_P0_OFF        (27)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_UseFLLDuringDVFS_P0_WID        ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_UseFLLDuringDVFS_P0_MSK        (0x08000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_UseFLLDuringDVFS_P0_MIN        (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_UseFLLDuringDVFS_P0_MAX        (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_UseFLLDuringDVFS_P0_DEF        (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_UseFLLDuringDVFS_P0_HSH        (0x01363A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_LockTimer_P0_OFF               (28)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_LockTimer_P0_WID               ( 2)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_LockTimer_P0_MSK               (0x30000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_LockTimer_P0_MIN               (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_LockTimer_P0_MAX               (3) // 0x00000003
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_LockTimer_P0_DEF               (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_LockTimer_P0_HSH               (0x02383A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_AckOffset_P0_OFF               (30)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_AckOffset_P0_WID               ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_AckOffset_P0_MSK               (0x40000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_AckOffset_P0_MIN               (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_AckOffset_P0_MAX               (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_AckOffset_P0_DEF               (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_AckOffset_P0_HSH               (0x013C3A00)

  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare_P0_OFF                   (31)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare_P0_WID                   ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare_P0_MSK                   (0x80000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare_P0_MIN                   (0)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare_P0_MAX                   (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare_P0_DEF                   (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENCONTROL_Spare_P0_HSH                   (0x013E3A00)

#define CH4CCC_CR_DDRCRCLKCOMP_REG                                     (0x00003A04)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define DDRVTT0_CR_DDRCRVTTGENSTATUS_P0_REG                            (0x00003A04)

  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_EnCount_P0_OFF                  ( 0)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_EnCount_P0_WID                  ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_EnCount_P0_MSK                  (0x00000001)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_EnCount_P0_MIN                  (0)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_EnCount_P0_MAX                  (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_EnCount_P0_DEF                  (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_EnCount_P0_HSH                  (0x01003A04)

  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_SelCount_P0_OFF                 ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_SelCount_P0_WID                 ( 3)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_SelCount_P0_MSK                 (0x0000000E)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_SelCount_P0_MIN                 (0)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_SelCount_P0_MAX                 (7) // 0x00000007
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_SelCount_P0_DEF                 (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_SelCount_P0_HSH                 (0x03023A04)

  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_RstCount_P0_OFF                 ( 4)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_RstCount_P0_WID                 ( 1)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_RstCount_P0_MSK                 (0x00000010)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_RstCount_P0_MIN                 (0)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_RstCount_P0_MAX                 (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_RstCount_P0_DEF                 (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_RstCount_P0_HSH                 (0x01083A04)

  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Count_P0_OFF                    ( 5)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Count_P0_WID                    (16)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Count_P0_MSK                    (0x001FFFE0)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Count_P0_MIN                    (0)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Count_P0_MAX                    (65535) // 0x0000FFFF
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Count_P0_DEF                    (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Count_P0_HSH                    (0x100A3A04)

  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Spare_P0_OFF                    (21)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Spare_P0_WID                    (11)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Spare_P0_MSK                    (0xFFE00000)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Spare_P0_MIN                    (0)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Spare_P0_MAX                    (2047) // 0x000007FF
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Spare_P0_DEF                    (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTGENSTATUS_Spare_P0_HSH                    (0x0B2A3A04)

#define CH4CCC_CR_DDRCRCTLCOMP_REG                                     (0x00003A08)
//Duplicate of CH0CCC_CR_DDRCRCTLCOMP_REG

#define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_P0_REG                           (0x00003A08)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_SpareNmosCompOfst_P0_OFF       ( 0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_SpareNmosCompOfst_P0_WID       ( 6)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_SpareNmosCompOfst_P0_MSK       (0x0000003F)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_SpareNmosCompOfst_P0_MIN       (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_SpareNmosCompOfst_P0_MAX       (63) // 0x0000003F
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_SpareNmosCompOfst_P0_DEF       (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_SpareNmosCompOfst_P0_HSH       (0x06003A08)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo0CompOfst_P0_OFF        ( 6)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo0CompOfst_P0_WID        ( 6)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo0CompOfst_P0_MSK        (0x00000FC0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo0CompOfst_P0_MIN        (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo0CompOfst_P0_MAX        (63) // 0x0000003F
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo0CompOfst_P0_DEF        (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo0CompOfst_P0_HSH        (0x060C3A08)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo1CompOfst_P0_OFF        (12)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo1CompOfst_P0_WID        ( 6)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo1CompOfst_P0_MSK        (0x0003F000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo1CompOfst_P0_MIN        (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo1CompOfst_P0_MAX        (63) // 0x0000003F
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo1CompOfst_P0_DEF        (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicLo1CompOfst_P0_HSH        (0x06183A08)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi0CompOfst_P0_OFF        (18)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi0CompOfst_P0_WID        ( 6)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi0CompOfst_P0_MSK        (0x00FC0000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi0CompOfst_P0_MIN        (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi0CompOfst_P0_MAX        (63) // 0x0000003F
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi0CompOfst_P0_DEF        (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi0CompOfst_P0_HSH        (0x06243A08)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi1CompOfst_P0_OFF        (24)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi1CompOfst_P0_WID        ( 6)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi1CompOfst_P0_MSK        (0x3F000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi1CompOfst_P0_MIN        (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi1CompOfst_P0_MAX        (63) // 0x0000003F
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi1CompOfst_P0_DEF        (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_PanicHi1CompOfst_P0_HSH        (0x06303A08)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_spare_P0_OFF                   (30)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_spare_P0_WID                   ( 2)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_spare_P0_MSK                   (0xC0000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_spare_P0_MIN                   (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_spare_P0_MAX                   (3) // 0x00000003
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_spare_P0_DEF                   (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET_spare_P0_HSH                   (0x023C3A08)

#define CH4CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG                          (0x00003A0C)
//Duplicate of CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG

#define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_P0_REG                          (0x00003A0C)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_SparePmosCompOfst_P0_OFF      ( 0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_SparePmosCompOfst_P0_WID      ( 6)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_SparePmosCompOfst_P0_MSK      (0x0000003F)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_SparePmosCompOfst_P0_MIN      (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_SparePmosCompOfst_P0_MAX      (63) // 0x0000003F
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_SparePmosCompOfst_P0_DEF      (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_SparePmosCompOfst_P0_HSH      (0x06003A0C)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo0UsePmos_P0_OFF        ( 6)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo0UsePmos_P0_WID        ( 1)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo0UsePmos_P0_MSK        (0x00000040)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo0UsePmos_P0_MIN        (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo0UsePmos_P0_MAX        (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo0UsePmos_P0_DEF        (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo0UsePmos_P0_HSH        (0x010C3A0C)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo1UsePmos_P0_OFF        ( 7)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo1UsePmos_P0_WID        ( 1)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo1UsePmos_P0_MSK        (0x00000080)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo1UsePmos_P0_MIN        (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo1UsePmos_P0_MAX        (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo1UsePmos_P0_DEF        (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicLo1UsePmos_P0_HSH        (0x010E3A0C)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi0UsePmos_P0_OFF        ( 8)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi0UsePmos_P0_WID        ( 1)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi0UsePmos_P0_MSK        (0x00000100)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi0UsePmos_P0_MIN        (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi0UsePmos_P0_MAX        (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi0UsePmos_P0_DEF        (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi0UsePmos_P0_HSH        (0x01103A0C)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi1UsePmos_P0_OFF        ( 9)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi1UsePmos_P0_WID        ( 1)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi1UsePmos_P0_MSK        (0x00000200)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi1UsePmos_P0_MIN        (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi1UsePmos_P0_MAX        (1) // 0x00000001
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi1UsePmos_P0_DEF        (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_PanicHi1UsePmos_P0_HSH        (0x01123A0C)

  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_spare_P0_OFF                  (10)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_spare_P0_WID                  (22)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_spare_P0_MSK                  (0xFFFFFC00)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_spare_P0_MIN                  (0)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_spare_P0_MAX                  (4194303) // 0x003FFFFF
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_spare_P0_DEF                  (0x00000000)
  #define DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_spare_P0_HSH                  (0x16143A0C)

#define CH4CCC_CR_DDRCRCTLCACOMPOFFSET_REG                             (0x00003A10)
//Duplicate of CH0CCC_CR_DDRCRCTLCACOMPOFFSET_REG

#define CH4CCC_CR_DDRCRCCCPIDIVIDER_REG                                (0x00003A14)
//Duplicate of CH0CCC_CR_DDRCRCCCPIDIVIDER_REG

#define CH4CCC_CR_DDRCRCCCPICODING0_REG                                (0x00003A18)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING0_REG

#define CH4CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG                   (0x00003A1C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG

#define CH4CCC_CR_DDRCRCCCVOLTAGEUSED_REG                              (0x00003A20)
//Duplicate of CH0CCC_CR_DDRCRCCCVOLTAGEUSED_REG

#define CH4CCC_CR_DDRCRCCCPERBITDESKEW0_REG                            (0x00003A24)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW0_REG

#define CH4CCC_CR_DDRCRCCCPERBITDESKEW1_REG                            (0x00003A28)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW1_REG

#define CH4CCC_CR_DDRCRCCCPERBITDESKEW2_REG                            (0x00003A2C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW2_REG

#define CH4CCC_CR_DDRCRPINSUSED_REG                                    (0x00003A30)
//Duplicate of CH0CCC_CR_DDRCRPINSUSED_REG

#define CH4CCC_CR_DDRCRCCCCLKCONTROLS_REG                              (0x00003A34)
//Duplicate of CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG

#define CH4CCC_CR_DDRCRBSCANDATA_REG                                   (0x00003A38)
//Duplicate of CH0CCC_CR_DDRCRBSCANDATA_REG

#define CH4CCC_CR_DDRCRMISR_REG                                        (0x00003A3C)
//Duplicate of CH0CCC_CR_DDRCRMISR_REG

#define CH4CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG                   (0x00003A40)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG

#define CH4CCC_CR_DCCFSMCONTROL_REG                                    (0x00003A44)
//Duplicate of CH0CCC_CR_DCCFSMCONTROL_REG

#define CH4CCC_CR_DCCCALCCONTROL_REG                                   (0x00003A48)
//Duplicate of CH0CCC_CR_DCCCALCCONTROL_REG

#define CH4CCC_CR_DCCFSMSTATUS_REG                                     (0x00003A4C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define CH4CCC_CR_DCCLANESTATUS0_REG                                   (0x00003A50)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define CH4CCC_CR_DCCLANESTATUS1_REG                                   (0x00003A54)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define CH4CCC_CR_DDRCRPERBITTCO0_REG                                  (0x00003A58)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO0_REG

#define CH4CCC_CR_DDRCRPERBITTCO1_REG                                  (0x00003A5C)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO1_REG

#define CH4CCC_CR_DDRCRPERBITTCO2_REG                                  (0x00003A60)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO2_REG

#define CH4CCC_CR_DDRCRCCCPICODING1_REG                                (0x00003A64)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING1_REG

#define CH4CCC_CR_DDRCRMARGINMODECONTROL_REG                           (0x00003A68)
//Duplicate of CH0CCC_CR_DDRCRMARGINMODECONTROL_REG

#define CH4CCC_CR_DDRCRMARGINMODEDEBUGMSB_REG                          (0x00003A6C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH4CCC_CR_DDRCRMARGINMODEDEBUGLSB_REG                          (0x00003A70)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH4CCC_CR_DCCLANESTATUS2_REG                                   (0x00003A74)
//Duplicate of CH0CCC_CR_DCCLANESTATUS2_REG

#define DDRVTT1_CR_DDRCRVTTGENCONTROL_P0_REG                           (0x00003A80)
//Duplicate of DDRVTT0_CR_DDRCRVTTGENCONTROL_P0_REG

#define DDRVTT1_CR_DDRCRVTTGENSTATUS_P0_REG                            (0x00003A84)
//Duplicate of DDRVTT0_CR_DDRCRVTTGENSTATUS_P0_REG

#define DDRVTT1_CR_DDRCRVTTCOMPOFFSET_P0_REG                           (0x00003A88)
//Duplicate of DDRVTT0_CR_DDRCRVTTCOMPOFFSET_P0_REG

#define DDRVTT1_CR_DDRCRVTTCOMPOFFSET2_P0_REG                          (0x00003A8C)
//Duplicate of DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_P0_REG

#define CH5CCC_CR_DDRCRCACOMP_REG                                      (0x00003B00)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define DDRVTT2_CR_DDRCRVTTGENCONTROL_P0_REG                           (0x00003B00)
//Duplicate of DDRVTT0_CR_DDRCRVTTGENCONTROL_P0_REG

#define CH5CCC_CR_DDRCRCLKCOMP_REG                                     (0x00003B04)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define DDRVTT2_CR_DDRCRVTTGENSTATUS_P0_REG                            (0x00003B04)
//Duplicate of DDRVTT0_CR_DDRCRVTTGENSTATUS_P0_REG

#define CH5CCC_CR_DDRCRCTLCOMP_REG                                     (0x00003B08)
//Duplicate of CH0CCC_CR_DDRCRCTLCOMP_REG

#define DDRVTT2_CR_DDRCRVTTCOMPOFFSET_P0_REG                           (0x00003B08)
//Duplicate of DDRVTT0_CR_DDRCRVTTCOMPOFFSET_P0_REG

#define CH5CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG                          (0x00003B0C)
//Duplicate of CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG

#define DDRVTT2_CR_DDRCRVTTCOMPOFFSET2_P0_REG                          (0x00003B0C)
//Duplicate of DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_P0_REG

#define CH5CCC_CR_DDRCRCTLCACOMPOFFSET_REG                             (0x00003B10)
//Duplicate of CH0CCC_CR_DDRCRCTLCACOMPOFFSET_REG

#define CH5CCC_CR_DDRCRCCCPIDIVIDER_REG                                (0x00003B14)
//Duplicate of CH0CCC_CR_DDRCRCCCPIDIVIDER_REG

#define CH5CCC_CR_DDRCRCCCPICODING0_REG                                (0x00003B18)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING0_REG

#define CH5CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG                   (0x00003B1C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG

#define CH5CCC_CR_DDRCRCCCVOLTAGEUSED_REG                              (0x00003B20)
//Duplicate of CH0CCC_CR_DDRCRCCCVOLTAGEUSED_REG

#define CH5CCC_CR_DDRCRCCCPERBITDESKEW0_REG                            (0x00003B24)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW0_REG

#define CH5CCC_CR_DDRCRCCCPERBITDESKEW1_REG                            (0x00003B28)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW1_REG

#define CH5CCC_CR_DDRCRCCCPERBITDESKEW2_REG                            (0x00003B2C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW2_REG

#define CH5CCC_CR_DDRCRPINSUSED_REG                                    (0x00003B30)
//Duplicate of CH0CCC_CR_DDRCRPINSUSED_REG

#define CH5CCC_CR_DDRCRCCCCLKCONTROLS_REG                              (0x00003B34)
//Duplicate of CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG

#define CH5CCC_CR_DDRCRBSCANDATA_REG                                   (0x00003B38)
//Duplicate of CH0CCC_CR_DDRCRBSCANDATA_REG

#define CH5CCC_CR_DDRCRMISR_REG                                        (0x00003B3C)
//Duplicate of CH0CCC_CR_DDRCRMISR_REG

#define CH5CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG                   (0x00003B40)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG

#define CH5CCC_CR_DCCFSMCONTROL_REG                                    (0x00003B44)
//Duplicate of CH0CCC_CR_DCCFSMCONTROL_REG

#define CH5CCC_CR_DCCCALCCONTROL_REG                                   (0x00003B48)
//Duplicate of CH0CCC_CR_DCCCALCCONTROL_REG

#define CH5CCC_CR_DCCFSMSTATUS_REG                                     (0x00003B4C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define CH5CCC_CR_DCCLANESTATUS0_REG                                   (0x00003B50)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define CH5CCC_CR_DCCLANESTATUS1_REG                                   (0x00003B54)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define CH5CCC_CR_DDRCRPERBITTCO0_REG                                  (0x00003B58)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO0_REG

#define CH5CCC_CR_DDRCRPERBITTCO1_REG                                  (0x00003B5C)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO1_REG

#define CH5CCC_CR_DDRCRPERBITTCO2_REG                                  (0x00003B60)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO2_REG

#define CH5CCC_CR_DDRCRCCCPICODING1_REG                                (0x00003B64)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING1_REG

#define CH5CCC_CR_DDRCRMARGINMODECONTROL_REG                           (0x00003B68)
//Duplicate of CH0CCC_CR_DDRCRMARGINMODECONTROL_REG

#define CH5CCC_CR_DDRCRMARGINMODEDEBUGMSB_REG                          (0x00003B6C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH5CCC_CR_DDRCRMARGINMODEDEBUGLSB_REG                          (0x00003B70)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH5CCC_CR_DCCLANESTATUS2_REG                                   (0x00003B74)
//Duplicate of CH0CCC_CR_DCCLANESTATUS2_REG

#define DDRVTT3_CR_DDRCRVTTGENCONTROL_P0_REG                           (0x00003B80)
//Duplicate of DDRVTT0_CR_DDRCRVTTGENCONTROL_P0_REG

#define DDRVTT3_CR_DDRCRVTTGENSTATUS_P0_REG                            (0x00003B84)
//Duplicate of DDRVTT0_CR_DDRCRVTTGENSTATUS_P0_REG

#define DDRVTT3_CR_DDRCRVTTCOMPOFFSET_P0_REG                           (0x00003B88)
//Duplicate of DDRVTT0_CR_DDRCRVTTCOMPOFFSET_P0_REG

#define DDRVTT3_CR_DDRCRVTTCOMPOFFSET2_P0_REG                          (0x00003B8C)
//Duplicate of DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_P0_REG

#define CH6CCC_CR_DDRCRCACOMP_REG                                      (0x00003C00)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define DDRVTT4_CR_DDRCRVTTGENCONTROL_P0_REG                           (0x00003C00)
//Duplicate of DDRVTT0_CR_DDRCRVTTGENCONTROL_P0_REG

#define CH6CCC_CR_DDRCRCLKCOMP_REG                                     (0x00003C04)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define DDRVTT4_CR_DDRCRVTTGENSTATUS_P0_REG                            (0x00003C04)
//Duplicate of DDRVTT0_CR_DDRCRVTTGENSTATUS_P0_REG

#define CH6CCC_CR_DDRCRCTLCOMP_REG                                     (0x00003C08)
//Duplicate of CH0CCC_CR_DDRCRCTLCOMP_REG

#define DDRVTT4_CR_DDRCRVTTCOMPOFFSET_P0_REG                           (0x00003C08)
//Duplicate of DDRVTT0_CR_DDRCRVTTCOMPOFFSET_P0_REG

#define CH6CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG                          (0x00003C0C)
//Duplicate of CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG

#define DDRVTT4_CR_DDRCRVTTCOMPOFFSET2_P0_REG                          (0x00003C0C)
//Duplicate of DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_P0_REG

#define CH6CCC_CR_DDRCRCTLCACOMPOFFSET_REG                             (0x00003C10)
//Duplicate of CH0CCC_CR_DDRCRCTLCACOMPOFFSET_REG

#define CH6CCC_CR_DDRCRCCCPIDIVIDER_REG                                (0x00003C14)
//Duplicate of CH0CCC_CR_DDRCRCCCPIDIVIDER_REG

#define CH6CCC_CR_DDRCRCCCPICODING0_REG                                (0x00003C18)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING0_REG

#define CH6CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG                   (0x00003C1C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG

#define CH6CCC_CR_DDRCRCCCVOLTAGEUSED_REG                              (0x00003C20)
//Duplicate of CH0CCC_CR_DDRCRCCCVOLTAGEUSED_REG

#define CH6CCC_CR_DDRCRCCCPERBITDESKEW0_REG                            (0x00003C24)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW0_REG

#define CH6CCC_CR_DDRCRCCCPERBITDESKEW1_REG                            (0x00003C28)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW1_REG

#define CH6CCC_CR_DDRCRCCCPERBITDESKEW2_REG                            (0x00003C2C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW2_REG

#define CH6CCC_CR_DDRCRPINSUSED_REG                                    (0x00003C30)
//Duplicate of CH0CCC_CR_DDRCRPINSUSED_REG

#define CH6CCC_CR_DDRCRCCCCLKCONTROLS_REG                              (0x00003C34)
//Duplicate of CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG

#define CH6CCC_CR_DDRCRBSCANDATA_REG                                   (0x00003C38)
//Duplicate of CH0CCC_CR_DDRCRBSCANDATA_REG

#define CH6CCC_CR_DDRCRMISR_REG                                        (0x00003C3C)
//Duplicate of CH0CCC_CR_DDRCRMISR_REG

#define CH6CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG                   (0x00003C40)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG

#define CH6CCC_CR_DCCFSMCONTROL_REG                                    (0x00003C44)
//Duplicate of CH0CCC_CR_DCCFSMCONTROL_REG

#define CH6CCC_CR_DCCCALCCONTROL_REG                                   (0x00003C48)
//Duplicate of CH0CCC_CR_DCCCALCCONTROL_REG

#define CH6CCC_CR_DCCFSMSTATUS_REG                                     (0x00003C4C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define CH6CCC_CR_DCCLANESTATUS0_REG                                   (0x00003C50)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define CH6CCC_CR_DCCLANESTATUS1_REG                                   (0x00003C54)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define CH6CCC_CR_DDRCRPERBITTCO0_REG                                  (0x00003C58)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO0_REG

#define CH6CCC_CR_DDRCRPERBITTCO1_REG                                  (0x00003C5C)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO1_REG

#define CH6CCC_CR_DDRCRPERBITTCO2_REG                                  (0x00003C60)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO2_REG

#define CH6CCC_CR_DDRCRCCCPICODING1_REG                                (0x00003C64)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING1_REG

#define CH6CCC_CR_DDRCRMARGINMODECONTROL_REG                           (0x00003C68)
//Duplicate of CH0CCC_CR_DDRCRMARGINMODECONTROL_REG

#define CH6CCC_CR_DDRCRMARGINMODEDEBUGMSB_REG                          (0x00003C6C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH6CCC_CR_DDRCRMARGINMODEDEBUGLSB_REG                          (0x00003C70)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH6CCC_CR_DCCLANESTATUS2_REG                                   (0x00003C74)
//Duplicate of CH0CCC_CR_DCCLANESTATUS2_REG

#define DDRVTT5_CR_DDRCRVTTGENCONTROL_P0_REG                           (0x00003C80)
//Duplicate of DDRVTT0_CR_DDRCRVTTGENCONTROL_P0_REG

#define DDRVTT5_CR_DDRCRVTTGENSTATUS_P0_REG                            (0x00003C84)
//Duplicate of DDRVTT0_CR_DDRCRVTTGENSTATUS_P0_REG

#define DDRVTT5_CR_DDRCRVTTCOMPOFFSET_P0_REG                           (0x00003C88)
//Duplicate of DDRVTT0_CR_DDRCRVTTCOMPOFFSET_P0_REG

#define DDRVTT5_CR_DDRCRVTTCOMPOFFSET2_P0_REG                          (0x00003C8C)
//Duplicate of DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_P0_REG

#define CH7CCC_CR_DDRCRCACOMP_REG                                      (0x00003D00)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define CH7CCC_CR_DDRCRCLKCOMP_REG                                     (0x00003D04)
//Duplicate of CH0CCC_CR_DDRCRCACOMP_REG

#define CH7CCC_CR_DDRCRCTLCOMP_REG                                     (0x00003D08)
//Duplicate of CH0CCC_CR_DDRCRCTLCOMP_REG

#define CH7CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG                          (0x00003D0C)
//Duplicate of CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG

#define CH7CCC_CR_DDRCRCTLCACOMPOFFSET_REG                             (0x00003D10)
//Duplicate of CH0CCC_CR_DDRCRCTLCACOMPOFFSET_REG

#define CH7CCC_CR_DDRCRCCCPIDIVIDER_REG                                (0x00003D14)
//Duplicate of CH0CCC_CR_DDRCRCCCPIDIVIDER_REG

#define CH7CCC_CR_DDRCRCCCPICODING0_REG                                (0x00003D18)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING0_REG

#define CH7CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG                   (0x00003D1C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG

#define CH7CCC_CR_DDRCRCCCVOLTAGEUSED_REG                              (0x00003D20)
//Duplicate of CH0CCC_CR_DDRCRCCCVOLTAGEUSED_REG

#define CH7CCC_CR_DDRCRCCCPERBITDESKEW0_REG                            (0x00003D24)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW0_REG

#define CH7CCC_CR_DDRCRCCCPERBITDESKEW1_REG                            (0x00003D28)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW1_REG

#define CH7CCC_CR_DDRCRCCCPERBITDESKEW2_REG                            (0x00003D2C)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEW2_REG

#define CH7CCC_CR_DDRCRPINSUSED_REG                                    (0x00003D30)
//Duplicate of CH0CCC_CR_DDRCRPINSUSED_REG

#define CH7CCC_CR_DDRCRCCCCLKCONTROLS_REG                              (0x00003D34)
//Duplicate of CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG

#define CH7CCC_CR_DDRCRBSCANDATA_REG                                   (0x00003D38)
//Duplicate of CH0CCC_CR_DDRCRBSCANDATA_REG

#define CH7CCC_CR_DDRCRMISR_REG                                        (0x00003D3C)
//Duplicate of CH0CCC_CR_DDRCRMISR_REG

#define CH7CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG                   (0x00003D40)
//Duplicate of CH0CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG

#define CH7CCC_CR_DCCFSMCONTROL_REG                                    (0x00003D44)
//Duplicate of CH0CCC_CR_DCCFSMCONTROL_REG

#define CH7CCC_CR_DCCCALCCONTROL_REG                                   (0x00003D48)
//Duplicate of CH0CCC_CR_DCCCALCCONTROL_REG

#define CH7CCC_CR_DCCFSMSTATUS_REG                                     (0x00003D4C)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define CH7CCC_CR_DCCLANESTATUS0_REG                                   (0x00003D50)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define CH7CCC_CR_DCCLANESTATUS1_REG                                   (0x00003D54)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define CH7CCC_CR_DDRCRPERBITTCO0_REG                                  (0x00003D58)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO0_REG

#define CH7CCC_CR_DDRCRPERBITTCO1_REG                                  (0x00003D5C)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO1_REG

#define CH7CCC_CR_DDRCRPERBITTCO2_REG                                  (0x00003D60)
//Duplicate of CH0CCC_CR_DDRCRPERBITTCO2_REG

#define CH7CCC_CR_DDRCRCCCPICODING1_REG                                (0x00003D64)
//Duplicate of CH0CCC_CR_DDRCRCCCPICODING1_REG

#define CH7CCC_CR_DDRCRMARGINMODECONTROL_REG                           (0x00003D68)
//Duplicate of CH0CCC_CR_DDRCRMARGINMODECONTROL_REG

#define CH7CCC_CR_DDRCRMARGINMODEDEBUGMSB_REG                          (0x00003D6C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH7CCC_CR_DDRCRMARGINMODEDEBUGLSB_REG                          (0x00003D70)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define CH7CCC_CR_DCCLANESTATUS2_REG                                   (0x00003D74)
//Duplicate of CH0CCC_CR_DCCLANESTATUS2_REG

#define DDRSCRAM_CR_DDRSCRAMBLECH0_REG                                 (0x00003E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_OFF                       ( 0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_WID                       ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_MSK                       (0x00000001)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_MIN                       (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_MAX                       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_HSH                       (0x01003E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_OFF                      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_WID                      (16)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_MSK                      (0x0001FFFE)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_MIN                      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_MAX                      (65535) // 0x0000FFFF
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_DEF                      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_HSH                      (0x10023E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_OFF                   (17)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_WID                   ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_MSK                   (0x00060000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_MAX                   (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_HSH                   (0x02223E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_OFF                    (19)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_WID                    ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_MSK                    (0x00180000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_MIN                    (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_MAX                    (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_HSH                    (0x02263E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_OFF                   (21)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_WID                   ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_MSK                   (0x00200000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_HSH                   (0x012A3E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_OFF                   (22)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_WID                   ( 4)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_MSK                   (0x03C00000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_MAX                   (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_HSH                   (0x042C3E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_OFF               (26)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_WID               ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_MSK               (0x04000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_MIN               (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_MAX               (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_HSH               (0x01343E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_OFF       (27)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_WID       ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_MSK       (0x08000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_MIN       (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_MAX       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_DEF       (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_HSH       (0x01363E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Write0En_OFF                      (28)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Write0En_WID                      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Write0En_MSK                      (0x10000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Write0En_MIN                      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Write0En_MAX                      (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Write0En_DEF                      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Write0En_HSH                      (0x01383E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_OFF                         (29)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_WID                         ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_MSK                         (0x20000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_MIN                         (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_MAX                         (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_DEF                         (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_HSH                         (0x013A3E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EarlyRankRdValidSwitch_OFF        (30)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EarlyRankRdValidSwitch_WID        ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EarlyRankRdValidSwitch_MSK        (0x40000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EarlyRankRdValidSwitch_MIN        (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EarlyRankRdValidSwitch_MAX        (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EarlyRankRdValidSwitch_DEF        (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EarlyRankRdValidSwitch_HSH        (0x013C3E00)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_OFF                 (31)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_WID                 ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_MSK                 (0x80000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_MIN                 (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_MAX                 (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_DEF                 (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_HSH                 (0x013E3E00)

#define DDRSCRAM_CR_DDRSCRAMBLECH1_REG                                 (0x00003E04)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_OFF                       ( 0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_WID                       ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_MSK                       (0x00000001)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_MIN                       (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_MAX                       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_HSH                       (0x01003E04)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_OFF                      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_WID                      (16)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_MSK                      (0x0001FFFE)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_MIN                      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_MAX                      (65535) // 0x0000FFFF
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_DEF                      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_HSH                      (0x10023E04)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_OFF                   (17)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_WID                   ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_MSK                   (0x00060000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_MAX                   (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_HSH                   (0x02223E04)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_OFF                    (19)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_WID                    ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_MSK                    (0x00180000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_MIN                    (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_MAX                    (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_HSH                    (0x02263E04)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_OFF                   (21)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_WID                   ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_MSK                   (0x00200000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_HSH                   (0x012A3E04)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_OFF                   (22)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_WID                   ( 4)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_MSK                   (0x03C00000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_MAX                   (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_HSH                   (0x042C3E04)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_OFF                         (26)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_WID                         ( 6)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_MSK                         (0xFC000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_MIN                         (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_MAX                         (63) // 0x0000003F
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_DEF                         (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_HSH                         (0x06343E04)

#define DDRSCRAM_CR_DDRSCRAMBLECH2_REG                                 (0x00003E08)
//Duplicate of DDRSCRAM_CR_DDRSCRAMBLECH1_REG

#define DDRSCRAM_CR_DDRSCRAMBLECH3_REG                                 (0x00003E0C)
//Duplicate of DDRSCRAM_CR_DDRSCRAMBLECH1_REG

#define DDRSCRAM_CR_DDRSCRAMBLECH4_REG                                 (0x00003E10)
//Duplicate of DDRSCRAM_CR_DDRSCRAMBLECH1_REG

#define DDRSCRAM_CR_DDRSCRAMBLECH5_REG                                 (0x00003E14)
//Duplicate of DDRSCRAM_CR_DDRSCRAMBLECH1_REG

#define DDRSCRAM_CR_DDRSCRAMBLECH6_REG                                 (0x00003E18)
//Duplicate of DDRSCRAM_CR_DDRSCRAMBLECH1_REG

#define DDRSCRAM_CR_DDRSCRAMBLECH7_REG                                 (0x00003E1C)
//Duplicate of DDRSCRAM_CR_DDRSCRAMBLECH1_REG

#define DDRSCRAM_CR_DDRMISCCONTROL0_REG                                (0x00003E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_OFF                       ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_WID                       ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_MSK                       (0x0000000F)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_MIN                       (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_MAX                       (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_HSH                       (0x04003E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_OFF       ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_WID       ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_MSK       (0x00000010)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_MIN       (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_MAX       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_DEF       (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_HSH       (0x01083E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_OFF              ( 5)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_WID              ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_MSK              (0x00000020)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_MAX              (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_HSH              (0x010A3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_OFF                       ( 6)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_WID                       ( 2)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_MSK                       (0x000000C0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_MIN                       (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_MAX                       (3) // 0x00000003
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_HSH                       (0x020C3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_OFF                      ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_WID                      ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_MSK                      (0x00000100)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_MIN                      (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_MAX                      (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_DEF                      (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_HSH                      (0x01103E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_OFF                    ( 9)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_WID                    ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_MSK                    (0x00000200)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_MIN                    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_MAX                    (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_HSH                    (0x01123E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_OFF            (10)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_WID            ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_MSK            (0x00000400)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_MAX            (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_DEF            (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_HSH            (0x01143E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_OFF                   (11)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_WID                   ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_MSK                   (0x00000800)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_HSH                   (0x01163E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_OFF                        (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_WID                        ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_MSK                        (0x00001000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_MIN                        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_MAX                        (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_DEF                        (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_HSH                        (0x01183E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_OFF              (13)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_WID              ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_MSK              (0x0001E000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_MAX              (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_HSH              (0x041A3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_OFF                    (17)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_WID                    ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_MSK                    (0x00020000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_MIN                    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_MAX                    (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_HSH                    (0x01223E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_OFF               (18)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_WID               ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_MSK               (0x00040000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_MIN               (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_MAX               (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_HSH               (0x01243E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_OFF         (19)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_WID         ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_MSK         (0x00080000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_MIN         (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_MAX         (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_DEF         (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_HSH         (0x01263E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_OFF               (20)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_WID               ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_MSK               (0x00100000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_MIN               (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_MAX               (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_HSH               (0x01283E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_OFF                   (21)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_WID                   ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_MSK                   (0x00200000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_HSH                   (0x012A3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_OFF        (22)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_WID        ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_MSK        (0x3FC00000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_MIN        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_MAX        (255) // 0x000000FF
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_DEF        (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_HSH        (0x082C3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_OFF         (30)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_WID         ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_MSK         (0x40000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_MIN         (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_MAX         (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_DEF         (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_HSH         (0x013C3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_OFF          (31)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_WID          ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_MSK          (0x80000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_MIN          (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_MAX          (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_DEF          (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_HSH          (0x013E3E20)

#define DDRSCRAM_CR_DDRMISCCONTROL0_P0_REG                             (0x00003E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_P0_OFF                    ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_P0_WID                    ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_P0_MSK                    (0x0000000F)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_P0_MIN                    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_P0_MAX                    (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_P0_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare0_P0_HSH                    (0x04003E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_P0_OFF    ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_P0_WID    ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_P0_MSK    (0x00000010)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_P0_MIN    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_P0_MAX    (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_P0_DEF    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_OvrdPeriodicToDvfsComp_P0_HSH    (0x01083E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_P0_OFF           ( 5)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_P0_WID           ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_P0_MSK           (0x00000020)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_P0_MIN           (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_P0_MAX           (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_P0_DEF           (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_P0_HSH           (0x010A3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_P0_OFF                    ( 6)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_P0_WID                    ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_P0_MSK                    (0x00000040)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_P0_MIN                    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_P0_MAX                    (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_P0_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_spare1_P0_HSH                    (0x010C3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_P0_OFF                   ( 7)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_P0_WID                   ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_P0_MSK                   (0x00000080)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_P0_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_P0_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_P0_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Lp5Mode_P0_HSH                   (0x010E3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_P0_OFF                ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_P0_WID                ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_P0_MSK                (0x00000100)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_P0_MIN                (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_P0_MAX                (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_P0_DEF                (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_P0_HSH                (0x01103E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_P0_OFF                 ( 9)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_P0_WID                 ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_P0_MSK                 (0x00000200)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_P0_MIN                 (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_P0_MAX                 (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_P0_DEF                 (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr5_Mode_P0_HSH                 (0x01123E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_P0_OFF         (10)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_P0_WID         ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_P0_MSK         (0x00000400)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_P0_MIN         (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_P0_MAX         (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_P0_DEF         (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_P0_HSH         (0x01143E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_P0_OFF                (11)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_P0_WID                ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_P0_MSK                (0x00000800)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_P0_MIN                (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_P0_MAX                (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_P0_DEF                (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_P0_HSH                (0x01163E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_P0_OFF                     (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_P0_WID                     ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_P0_MSK                     (0x00001000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_P0_MIN                     (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_P0_MAX                     (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_P0_DEF                     (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_P0_HSH                     (0x01183E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_P0_OFF           (13)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_P0_WID           ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_P0_MSK           (0x0001E000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_P0_MIN           (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_P0_MAX           (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_P0_DEF           (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_P0_HSH           (0x041A3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_P0_OFF                 (17)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_P0_WID                 ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_P0_MSK                 (0x00020000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_P0_MIN                 (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_P0_MAX                 (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_P0_DEF                 (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_P0_HSH                 (0x01223E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_P0_OFF            (18)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_P0_WID            ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_P0_MSK            (0x00040000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_P0_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_P0_MAX            (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_P0_DEF            (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_P0_HSH            (0x01243E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_P0_OFF      (19)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_P0_WID      ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_P0_MSK      (0x00080000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_P0_MIN      (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_P0_MAX      (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_P0_DEF      (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_P0_HSH      (0x01263E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_P0_OFF            (20)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_P0_WID            ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_P0_MSK            (0x00100000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_P0_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_P0_MAX            (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_P0_DEF            (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp5wck2ckratio_P0_HSH            (0x01283E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_P0_OFF                (21)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_P0_WID                ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_P0_MSK                (0x00200000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_P0_MIN                (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_P0_MAX                (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_P0_DEF                (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_P0_HSH                (0x012A3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_P0_OFF     (22)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_P0_WID     ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_P0_MSK     (0x3FC00000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_P0_MIN     (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_P0_MAX     (255) // 0x000000FF
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_P0_DEF     (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_P0_HSH     (0x082C3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_P0_OFF      (30)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_P0_WID      ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_P0_MSK      (0x40000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_P0_MIN      (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_P0_MAX      (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_P0_DEF      (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_P0_HSH      (0x013C3E20)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_P0_OFF       (31)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_P0_WID       ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_P0_MSK       (0x80000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_P0_MIN       (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_P0_MAX       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_P0_DEF       (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceDeltaDQSUpdate_P0_HSH       (0x013E3E20)

#define DDRSCRAM_CR_DDRMISCCONTROL1_REG                                (0x00003E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGGndRefBypass_OFF               ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGGndRefBypass_WID               ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGGndRefBypass_MSK               (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGGndRefBypass_MIN               (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGGndRefBypass_MAX               (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGGndRefBypass_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGGndRefBypass_HSH               (0x01003E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGBiasTrim_OFF                   ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGBiasTrim_WID                   ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGBiasTrim_MSK                   (0x0000000E)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGBiasTrim_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGBiasTrim_MAX                   (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGBiasTrim_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGBiasTrim_HSH                   (0x03023E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGAgshTrim_OFF                   ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGAgshTrim_WID                   ( 2)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGAgshTrim_MSK                   (0x00000030)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGAgshTrim_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGAgshTrim_MAX                   (3) // 0x00000003
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGAgshTrim_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_BGAgshTrim_HSH                   (0x02083E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_OFF             ( 6)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_WID             ( 2)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_MSK             (0x000000C0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_MAX             (3) // 0x00000003
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_DEF             (0x00000003)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_HSH             (0x020C3E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_OFF             ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_MSK             (0x00000F00)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_DEF             (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_HSH             (0x04103E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_OFF             (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_MSK             (0x0000F000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_DEF             (0x00000002)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_HSH             (0x04183E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_OFF            (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_MSK            (0x000F0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_DEF            (0x00000004)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_HSH            (0x04203E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_OFF            (20)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_MSK            (0x00F00000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_DEF            (0x00000006)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_HSH            (0x04283E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_OFF                 (24)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_WID                 ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_MSK                 (0x01000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_MIN                 (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_MAX                 (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_DEF                 (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_HSH                 (0x01303E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_OFF      (25)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_WID      ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_MSK      (0x02000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_MIN      (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_MAX      (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_DEF      (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_HSH      (0x01323E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_OFF        (26)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_WID        ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_MSK        (0x3C000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_MIN        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_MAX        (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_DEF        (0x0000000F)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_HSH        (0x04343E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CompAndDeltaDqsUpdateClkGateDisable_OFF (30)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CompAndDeltaDqsUpdateClkGateDisable_WID ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CompAndDeltaDqsUpdateClkGateDisable_MSK (0x40000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CompAndDeltaDqsUpdateClkGateDisable_MIN (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CompAndDeltaDqsUpdateClkGateDisable_MAX (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CompAndDeltaDqsUpdateClkGateDisable_DEF (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CompAndDeltaDqsUpdateClkGateDisable_HSH (0x013C3E24)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_spare_OFF                        (31)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_spare_WID                        ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_spare_MSK                        (0x80000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_spare_MIN                        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_spare_MAX                        (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL1_spare_DEF                        (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_spare_HSH                        (0x013E3E24)

#define DDRSCRAM_CR_DDRMISCCONTROL2_REG                                (0x00003E28)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_OFF             ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_MSK             (0x0000000F)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_DEF             (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_HSH             (0x04003E28)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_OFF             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_MSK             (0x000000F0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_DEF             (0x00000003)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_HSH             (0x04083E28)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_OFF             ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_MSK             (0x00000F00)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_DEF             (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_HSH             (0x04103E28)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_OFF             (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_MSK             (0x0000F000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_DEF             (0x00000002)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_HSH             (0x04183E28)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_OFF            (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_MSK            (0x000F0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_DEF            (0x00000004)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_HSH            (0x04203E28)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_OFF            (20)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_MSK            (0x00F00000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_DEF            (0x00000006)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_HSH            (0x04283E28)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_lpdeltadqstrainmode_OFF          (24)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lpdeltadqstrainmode_WID          ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lpdeltadqstrainmode_MSK          (0x01000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lpdeltadqstrainmode_MIN          (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lpdeltadqstrainmode_MAX          (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lpdeltadqstrainmode_DEF          (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lpdeltadqstrainmode_HSH          (0x01303E28)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_OFF        (25)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_WID        ( 7)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_MSK        (0xFE000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_MIN        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_MAX        (127) // 0x0000007F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_DEF        (0x00000064)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_HSH        (0x07323E28)

#define MCMISCS_WRITECFGCH0_REG                                        (0x00003E2C)

  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_OFF                    ( 0)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_WID                    ( 7)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_MSK                    (0x0000007F)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_MIN                    (0)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_MAX                    (127) // 0x0000007F
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_DEF                    (0x00000000)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_HSH                    (0x07003E2C)

  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_OFF                    ( 7)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_WID                    ( 7)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_MSK                    (0x00003F80)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_MIN                    (0)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_MAX                    (127) // 0x0000007F
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_DEF                    (0x00000000)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_HSH                    (0x070E3E2C)

  #define MCMISCS_WRITECFGCH0_Spare_OFF                                (14)
  #define MCMISCS_WRITECFGCH0_Spare_WID                                ( 4)
  #define MCMISCS_WRITECFGCH0_Spare_MSK                                (0x0003C000)
  #define MCMISCS_WRITECFGCH0_Spare_MIN                                (0)
  #define MCMISCS_WRITECFGCH0_Spare_MAX                                (15) // 0x0000000F
  #define MCMISCS_WRITECFGCH0_Spare_DEF                                (0x00000000)
  #define MCMISCS_WRITECFGCH0_Spare_HSH                                (0x041C3E2C)

  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_OFF                       (18)
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_WID                       ( 1)
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_MSK                       (0x00040000)
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_MIN                       (0)
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_MAX                       (1) // 0x00000001
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_DEF                       (0x00000000)
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_HSH                       (0x01243E2C)

  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_OFF                       (19)
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_WID                       ( 1)
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_MSK                       (0x00080000)
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_MIN                       (0)
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_MAX                       (1) // 0x00000001
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_DEF                       (0x00000000)
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_HSH                       (0x01263E2C)

  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_OFF                        (20)
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_WID                        ( 1)
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_MSK                        (0x00100000)
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_MIN                        (0)
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_MAX                        (1) // 0x00000001
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_DEF                        (0x00000000)
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_HSH                        (0x01283E2C)

  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_OFF                    (21)
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_WID                    ( 3)
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_MSK                    (0x00E00000)
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_MIN                    (0)
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_MAX                    (7) // 0x00000007
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_DEF                    (0x00000007)
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_HSH                    (0x032A3E2C)

  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_OFF                     (24)
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_WID                     ( 7)
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MSK                     (0x7F000000)
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MIN                     (0)
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MAX                     (127) // 0x0000007F
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_DEF                     (0x0000003F)
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_HSH                     (0x07303E2C)

  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_OFF            (31)
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_WID            ( 1)
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_MSK            (0x80000000)
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_MIN            (0)
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_MAX            (1) // 0x00000001
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_DEF            (0x00000000)
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_HSH            (0x013E3E2C)

#define MCMISCS_WRITECFGCH1_REG                                        (0x00003E30)
//Duplicate of MCMISCS_WRITECFGCH0_REG

#define MCMISCS_WRITECFGCH2_REG                                        (0x00003E34)
//Duplicate of MCMISCS_WRITECFGCH0_REG

#define MCMISCS_WRITECFGCH3_REG                                        (0x00003E38)
//Duplicate of MCMISCS_WRITECFGCH0_REG

#define MCMISCS_WRITECFGCH4_REG                                        (0x00003E3C)
//Duplicate of MCMISCS_WRITECFGCH0_REG

#define MCMISCS_WRITECFGCH5_REG                                        (0x00003E40)
//Duplicate of MCMISCS_WRITECFGCH0_REG

#define MCMISCS_WRITECFGCH6_REG                                        (0x00003E44)
//Duplicate of MCMISCS_WRITECFGCH0_REG

#define MCMISCS_WRITECFGCH7_REG                                        (0x00003E48)
//Duplicate of MCMISCS_WRITECFGCH0_REG

#define MCMISCS_READCFGCH0_REG                                         (0x00003E4C)

  #define MCMISCS_READCFGCH0_Spare_OFF                                 ( 0)
  #define MCMISCS_READCFGCH0_Spare_WID                                 (13)
  #define MCMISCS_READCFGCH0_Spare_MSK                                 (0x00001FFF)
  #define MCMISCS_READCFGCH0_Spare_MIN                                 (0)
  #define MCMISCS_READCFGCH0_Spare_MAX                                 (8191) // 0x00001FFF
  #define MCMISCS_READCFGCH0_Spare_DEF                                 (0x00000000)
  #define MCMISCS_READCFGCH0_Spare_HSH                                 (0x0D003E4C)

  #define MCMISCS_READCFGCH0_tCL4RcvEn_OFF                             (13)
  #define MCMISCS_READCFGCH0_tCL4RcvEn_WID                             ( 7)
  #define MCMISCS_READCFGCH0_tCL4RcvEn_MSK                             (0x000FE000)
  #define MCMISCS_READCFGCH0_tCL4RcvEn_MIN                             (0)
  #define MCMISCS_READCFGCH0_tCL4RcvEn_MAX                             (127) // 0x0000007F
  #define MCMISCS_READCFGCH0_tCL4RcvEn_DEF                             (0x00000000)
  #define MCMISCS_READCFGCH0_tCL4RcvEn_HSH                             (0x071A3E4C)

  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_OFF                      (20)
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_WID                      ( 7)
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_MSK                      (0x07F00000)
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_MIN                      (0)
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_MAX                      (127) // 0x0000007F
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_DEF                      (0x00000000)
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_HSH                      (0x07283E4C)

  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_OFF                  (27)
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_WID                  ( 4)
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_MSK                  (0x78000000)
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_MIN                  (0)
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_MAX                  (15) // 0x0000000F
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_DEF                  (0x00000001)
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_HSH                  (0x04363E4C)

  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_OFF                  (31)
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_WID                  ( 1)
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_MSK                  (0x80000000)
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_MIN                  (0)
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_MAX                  (1) // 0x00000001
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_HSH                  (0x013E3E4C)

#define MCMISCS_READCFGCH1_REG                                         (0x00003E50)
//Duplicate of MCMISCS_READCFGCH0_REG

#define MCMISCS_READCFGCH2_REG                                         (0x00003E54)
//Duplicate of MCMISCS_READCFGCH0_REG

#define MCMISCS_READCFGCH3_REG                                         (0x00003E58)
//Duplicate of MCMISCS_READCFGCH0_REG

#define MCMISCS_READCFGCH4_REG                                         (0x00003E5C)
//Duplicate of MCMISCS_READCFGCH0_REG

#define MCMISCS_READCFGCH5_REG                                         (0x00003E60)
//Duplicate of MCMISCS_READCFGCH0_REG

#define MCMISCS_READCFGCH6_REG                                         (0x00003E64)
//Duplicate of MCMISCS_READCFGCH0_REG

#define MCMISCS_READCFGCH7_REG                                         (0x00003E68)
//Duplicate of MCMISCS_READCFGCH0_REG

#define DDRSCRAM_CR_DDRMISCCONTROL7_REG                                (0x00003E6C)

  #define DDRSCRAM_CR_DDRMISCCONTROL7_TxBurstLen_OFF                   ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TxBurstLen_WID                   ( 5)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TxBurstLen_MSK                   (0x0000001F)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TxBurstLen_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TxBurstLen_MAX                   (31) // 0x0000001F
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TxBurstLen_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TxBurstLen_HSH                   (0x05003E6C)

  #define DDRSCRAM_CR_DDRMISCCONTROL7_RxBurstLen_OFF                   ( 5)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_RxBurstLen_WID                   ( 5)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_RxBurstLen_MSK                   (0x000003E0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_RxBurstLen_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_RxBurstLen_MAX                   (31) // 0x0000001F
  #define DDRSCRAM_CR_DDRMISCCONTROL7_RxBurstLen_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_RxBurstLen_HSH                   (0x050A3E6C)

  #define DDRSCRAM_CR_DDRMISCCONTROL7_CmdDuration_OFF                  (10)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_CmdDuration_WID                  ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_CmdDuration_MSK                  (0x00001C00)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_CmdDuration_MIN                  (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_CmdDuration_MAX                  (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL7_CmdDuration_DEF                  (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_CmdDuration_HSH                  (0x03143E6C)

  #define DDRSCRAM_CR_DDRMISCCONTROL7_DataInvertNibble_OFF             (13)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_DataInvertNibble_WID             ( 2)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_DataInvertNibble_MSK             (0x00006000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_DataInvertNibble_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_DataInvertNibble_MAX             (3) // 0x00000003
  #define DDRSCRAM_CR_DDRMISCCONTROL7_DataInvertNibble_DEF             (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_DataInvertNibble_HSH             (0x021A3E6C)

  #define DDRSCRAM_CR_DDRMISCCONTROL7_Run1stComp_OFF                   (15)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Run1stComp_WID                   ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Run1stComp_MSK                   (0x00008000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Run1stComp_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Run1stComp_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Run1stComp_DEF                   (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Run1stComp_HSH                   (0x011E3E6C)

  #define DDRSCRAM_CR_DDRMISCCONTROL7_Cas2FSWCk_OFF                    (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Cas2FSWCk_WID                    ( 7)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Cas2FSWCk_MSK                    (0x007F0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Cas2FSWCk_MIN                    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Cas2FSWCk_MAX                    (127) // 0x0000007F
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Cas2FSWCk_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_Cas2FSWCk_HSH                    (0x07203E6C)

  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkSyncRatio_OFF            (23)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkSyncRatio_WID            ( 2)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkSyncRatio_MSK            (0x01800000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkSyncRatio_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkSyncRatio_MAX            (3) // 0x00000003
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkSyncRatio_DEF            (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkSyncRatio_HSH            (0x022E3E6C)

  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkEn_OFF                   (25)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkEn_WID                   ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkEn_MSK                   (0x02000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkEn_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkEn_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkEn_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_TrainWCkEn_HSH                   (0x01323E6C)

  #define DDRSCRAM_CR_DDRMISCCONTROL7_spare_OFF                        (26)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_spare_WID                        ( 6)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_spare_MSK                        (0xFC000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_spare_MIN                        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_spare_MAX                        (63) // 0x0000003F
  #define DDRSCRAM_CR_DDRMISCCONTROL7_spare_DEF                        (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL7_spare_HSH                        (0x06343E6C)

#define MCMISCS_SYNAUTOTRDYSTART_REG                                   (0x00003E70)

  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_OFF                   ( 0)
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_WID                   ( 1)
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_MSK                   (0x00000001)
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_MIN                   (0)
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_MAX                   (1) // 0x00000001
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_DEF                   (0x00000000)
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_HSH                   (0x01003E70)

  #define MCMISCS_SYNAUTOTRDYSTART_Spare_OFF                           ( 1)
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_WID                           (31)
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_MSK                           (0xFFFFFFFE)
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_MIN                           (0)
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_MAX                           (2147483647) // 0x7FFFFFFF
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_DEF                           (0x00000000)
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_HSH                           (0x1F023E70)

#define MCMISCS_SYNAUTOTRDYEND_REG                                     (0x00003E74)

  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_OFF                   ( 0)
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_WID                   ( 1)
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_MSK                   (0x00000001)
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_MIN                   (0)
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_MAX                   (1) // 0x00000001
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_DEF                   (0x00000000)
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_HSH                   (0x01003E74)

  #define MCMISCS_SYNAUTOTRDYEND_Spare_OFF                             ( 1)
  #define MCMISCS_SYNAUTOTRDYEND_Spare_WID                             (31)
  #define MCMISCS_SYNAUTOTRDYEND_Spare_MSK                             (0xFFFFFFFE)
  #define MCMISCS_SYNAUTOTRDYEND_Spare_MIN                             (0)
  #define MCMISCS_SYNAUTOTRDYEND_Spare_MAX                             (2147483647) // 0x7FFFFFFF
  #define MCMISCS_SYNAUTOTRDYEND_Spare_DEF                             (0x00000000)
  #define MCMISCS_SYNAUTOTRDYEND_Spare_HSH                             (0x1F023E74)

#define MCMISCS_WRITECFGCH01_REG                                       (0x00003E80)

  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChADel_OFF             ( 0)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChADel_WID             ( 3)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChADel_MSK             (0x00000007)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChADel_MIN             (0)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChADel_MAX             (7) // 0x00000007
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChADel_DEF             (0x00000000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChADel_HSH             (0x03003E80)

  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChADel_OFF             ( 3)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChADel_WID             ( 3)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChADel_MSK             (0x00000038)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChADel_MIN             (0)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChADel_MAX             (7) // 0x00000007
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChADel_DEF             (0x00000000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChADel_HSH             (0x03063E80)

  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChADel_OFF             ( 6)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChADel_WID             ( 3)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChADel_MSK             (0x000001C0)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChADel_MIN             (0)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChADel_MAX             (7) // 0x00000007
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChADel_DEF             (0x00000000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChADel_HSH             (0x030C3E80)

  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChADel_OFF             ( 9)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChADel_WID             ( 3)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChADel_MSK             (0x00000E00)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChADel_MIN             (0)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChADel_MAX             (7) // 0x00000007
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChADel_DEF             (0x00000000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChADel_HSH             (0x03123E80)

  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChBDel_OFF             (12)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChBDel_WID             ( 3)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChBDel_MSK             (0x00007000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChBDel_MIN             (0)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChBDel_MAX             (7) // 0x00000007
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChBDel_DEF             (0x00000000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank0ChBDel_HSH             (0x03183E80)

  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChBDel_OFF             (15)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChBDel_WID             ( 3)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChBDel_MSK             (0x00038000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChBDel_MIN             (0)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChBDel_MAX             (7) // 0x00000007
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChBDel_DEF             (0x00000000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank1ChBDel_HSH             (0x031E3E80)

  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChBDel_OFF             (18)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChBDel_WID             ( 3)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChBDel_MSK             (0x001C0000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChBDel_MIN             (0)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChBDel_MAX             (7) // 0x00000007
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChBDel_DEF             (0x00000000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank2ChBDel_HSH             (0x03243E80)

  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChBDel_OFF             (21)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChBDel_WID             ( 3)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChBDel_MSK             (0x00E00000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChBDel_MIN             (0)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChBDel_MAX             (7) // 0x00000007
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChBDel_DEF             (0x00000000)
  #define MCMISCS_WRITECFGCH01_TxDqFifoRdEnRank3ChBDel_HSH             (0x032A3E80)

  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_cha_OFF          (24)
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_cha_WID          ( 1)
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_cha_MSK          (0x01000000)
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_cha_MIN          (0)
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_cha_MAX          (1) // 0x00000001
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_cha_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_cha_HSH          (0x01303E80)

  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_chb_OFF          (25)
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_chb_WID          ( 1)
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_chb_MSK          (0x02000000)
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_chb_MIN          (0)
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_chb_MAX          (1) // 0x00000001
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_chb_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCH01_tx_analog_clk_gate_dis_chb_HSH          (0x01323E80)

  #define MCMISCS_WRITECFGCH01_Spare_OFF                               (26)
  #define MCMISCS_WRITECFGCH01_Spare_WID                               ( 6)
  #define MCMISCS_WRITECFGCH01_Spare_MSK                               (0xFC000000)
  #define MCMISCS_WRITECFGCH01_Spare_MIN                               (0)
  #define MCMISCS_WRITECFGCH01_Spare_MAX                               (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH01_Spare_DEF                               (0x00000000)
  #define MCMISCS_WRITECFGCH01_Spare_HSH                               (0x06343E80)

#define MCMISCS_WRITECFGCH23_REG                                       (0x00003E84)
//Duplicate of MCMISCS_WRITECFGCH01_REG

#define MCMISCS_WRITECFGCH45_REG                                       (0x00003E88)
//Duplicate of MCMISCS_WRITECFGCH01_REG

#define MCMISCS_WRITECFGCH67_REG                                       (0x00003E8C)
//Duplicate of MCMISCS_WRITECFGCH01_REG

#define MCMISCS_READCFGCH01_REG                                        (0x00003E90)

  #define MCMISCS_READCFGCH01_RcvEnRank0ChADel_OFF                     ( 0)
  #define MCMISCS_READCFGCH01_RcvEnRank0ChADel_WID                     ( 3)
  #define MCMISCS_READCFGCH01_RcvEnRank0ChADel_MSK                     (0x00000007)
  #define MCMISCS_READCFGCH01_RcvEnRank0ChADel_MIN                     (0)
  #define MCMISCS_READCFGCH01_RcvEnRank0ChADel_MAX                     (7) // 0x00000007
  #define MCMISCS_READCFGCH01_RcvEnRank0ChADel_DEF                     (0x00000000)
  #define MCMISCS_READCFGCH01_RcvEnRank0ChADel_HSH                     (0x03003E90)

  #define MCMISCS_READCFGCH01_RcvEnRank1ChADel_OFF                     ( 3)
  #define MCMISCS_READCFGCH01_RcvEnRank1ChADel_WID                     ( 3)
  #define MCMISCS_READCFGCH01_RcvEnRank1ChADel_MSK                     (0x00000038)
  #define MCMISCS_READCFGCH01_RcvEnRank1ChADel_MIN                     (0)
  #define MCMISCS_READCFGCH01_RcvEnRank1ChADel_MAX                     (7) // 0x00000007
  #define MCMISCS_READCFGCH01_RcvEnRank1ChADel_DEF                     (0x00000000)
  #define MCMISCS_READCFGCH01_RcvEnRank1ChADel_HSH                     (0x03063E90)

  #define MCMISCS_READCFGCH01_RcvEnRank2ChADel_OFF                     ( 6)
  #define MCMISCS_READCFGCH01_RcvEnRank2ChADel_WID                     ( 3)
  #define MCMISCS_READCFGCH01_RcvEnRank2ChADel_MSK                     (0x000001C0)
  #define MCMISCS_READCFGCH01_RcvEnRank2ChADel_MIN                     (0)
  #define MCMISCS_READCFGCH01_RcvEnRank2ChADel_MAX                     (7) // 0x00000007
  #define MCMISCS_READCFGCH01_RcvEnRank2ChADel_DEF                     (0x00000000)
  #define MCMISCS_READCFGCH01_RcvEnRank2ChADel_HSH                     (0x030C3E90)

  #define MCMISCS_READCFGCH01_RcvEnRank3ChADel_OFF                     ( 9)
  #define MCMISCS_READCFGCH01_RcvEnRank3ChADel_WID                     ( 3)
  #define MCMISCS_READCFGCH01_RcvEnRank3ChADel_MSK                     (0x00000E00)
  #define MCMISCS_READCFGCH01_RcvEnRank3ChADel_MIN                     (0)
  #define MCMISCS_READCFGCH01_RcvEnRank3ChADel_MAX                     (7) // 0x00000007
  #define MCMISCS_READCFGCH01_RcvEnRank3ChADel_DEF                     (0x00000000)
  #define MCMISCS_READCFGCH01_RcvEnRank3ChADel_HSH                     (0x03123E90)

  #define MCMISCS_READCFGCH01_RcvEnRank0ChBDel_OFF                     (12)
  #define MCMISCS_READCFGCH01_RcvEnRank0ChBDel_WID                     ( 3)
  #define MCMISCS_READCFGCH01_RcvEnRank0ChBDel_MSK                     (0x00007000)
  #define MCMISCS_READCFGCH01_RcvEnRank0ChBDel_MIN                     (0)
  #define MCMISCS_READCFGCH01_RcvEnRank0ChBDel_MAX                     (7) // 0x00000007
  #define MCMISCS_READCFGCH01_RcvEnRank0ChBDel_DEF                     (0x00000000)
  #define MCMISCS_READCFGCH01_RcvEnRank0ChBDel_HSH                     (0x03183E90)

  #define MCMISCS_READCFGCH01_RcvEnRank1ChBDel_OFF                     (15)
  #define MCMISCS_READCFGCH01_RcvEnRank1ChBDel_WID                     ( 3)
  #define MCMISCS_READCFGCH01_RcvEnRank1ChBDel_MSK                     (0x00038000)
  #define MCMISCS_READCFGCH01_RcvEnRank1ChBDel_MIN                     (0)
  #define MCMISCS_READCFGCH01_RcvEnRank1ChBDel_MAX                     (7) // 0x00000007
  #define MCMISCS_READCFGCH01_RcvEnRank1ChBDel_DEF                     (0x00000000)
  #define MCMISCS_READCFGCH01_RcvEnRank1ChBDel_HSH                     (0x031E3E90)

  #define MCMISCS_READCFGCH01_RcvEnRank2ChBDel_OFF                     (18)
  #define MCMISCS_READCFGCH01_RcvEnRank2ChBDel_WID                     ( 3)
  #define MCMISCS_READCFGCH01_RcvEnRank2ChBDel_MSK                     (0x001C0000)
  #define MCMISCS_READCFGCH01_RcvEnRank2ChBDel_MIN                     (0)
  #define MCMISCS_READCFGCH01_RcvEnRank2ChBDel_MAX                     (7) // 0x00000007
  #define MCMISCS_READCFGCH01_RcvEnRank2ChBDel_DEF                     (0x00000000)
  #define MCMISCS_READCFGCH01_RcvEnRank2ChBDel_HSH                     (0x03243E90)

  #define MCMISCS_READCFGCH01_RcvEnRank3ChBDel_OFF                     (21)
  #define MCMISCS_READCFGCH01_RcvEnRank3ChBDel_WID                     ( 3)
  #define MCMISCS_READCFGCH01_RcvEnRank3ChBDel_MSK                     (0x00E00000)
  #define MCMISCS_READCFGCH01_RcvEnRank3ChBDel_MIN                     (0)
  #define MCMISCS_READCFGCH01_RcvEnRank3ChBDel_MAX                     (7) // 0x00000007
  #define MCMISCS_READCFGCH01_RcvEnRank3ChBDel_DEF                     (0x00000000)
  #define MCMISCS_READCFGCH01_RcvEnRank3ChBDel_HSH                     (0x032A3E90)

  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_cha_OFF           (24)
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_cha_WID           ( 1)
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_cha_MSK           (0x01000000)
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_cha_MIN           (0)
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_cha_MAX           (1) // 0x00000001
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_cha_DEF           (0x00000000)
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_cha_HSH           (0x01303E90)

  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_chb_OFF           (25)
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_chb_WID           ( 1)
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_chb_MSK           (0x02000000)
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_chb_MIN           (0)
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_chb_MAX           (1) // 0x00000001
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_chb_DEF           (0x00000000)
  #define MCMISCS_READCFGCH01_rx_analog_clk_gate_dis_chb_HSH           (0x01323E90)

  #define MCMISCS_READCFGCH01_Spare_OFF                                (26)
  #define MCMISCS_READCFGCH01_Spare_WID                                ( 6)
  #define MCMISCS_READCFGCH01_Spare_MSK                                (0xFC000000)
  #define MCMISCS_READCFGCH01_Spare_MIN                                (0)
  #define MCMISCS_READCFGCH01_Spare_MAX                                (63) // 0x0000003F
  #define MCMISCS_READCFGCH01_Spare_DEF                                (0x00000000)
  #define MCMISCS_READCFGCH01_Spare_HSH                                (0x06343E90)

#define MCMISCS_READCFGCH23_REG                                        (0x00003E94)
//Duplicate of MCMISCS_READCFGCH01_REG

#define MCMISCS_READCFGCH45_REG                                        (0x00003E98)
//Duplicate of MCMISCS_READCFGCH01_REG

#define MCMISCS_READCFGCH67_REG                                        (0x00003E9C)
//Duplicate of MCMISCS_READCFGCH01_REG

#define MCMISCS_RXDQFIFORDENCH01_REG                                   (0x00003EA0)

  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_OFF         ( 0)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_WID         ( 4)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_MSK         (0x0000000F)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_MIN         (0)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_MAX         (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_DEF         (0x00000000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChADel_HSH         (0x04003EA0)

  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChADel_OFF         ( 4)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChADel_WID         ( 4)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChADel_MSK         (0x000000F0)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChADel_MIN         (0)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChADel_MAX         (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChADel_DEF         (0x00000000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChADel_HSH         (0x04083EA0)

  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChADel_OFF         ( 8)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChADel_WID         ( 4)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChADel_MSK         (0x00000F00)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChADel_MIN         (0)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChADel_MAX         (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChADel_DEF         (0x00000000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChADel_HSH         (0x04103EA0)

  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChADel_OFF         (12)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChADel_WID         ( 4)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChADel_MSK         (0x0000F000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChADel_MIN         (0)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChADel_MAX         (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChADel_DEF         (0x00000000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChADel_HSH         (0x04183EA0)

  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChBDel_OFF         (16)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChBDel_WID         ( 4)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChBDel_MSK         (0x000F0000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChBDel_MIN         (0)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChBDel_MAX         (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChBDel_DEF         (0x00000000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank0ChBDel_HSH         (0x04203EA0)

  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChBDel_OFF         (20)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChBDel_WID         ( 4)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChBDel_MSK         (0x00F00000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChBDel_MIN         (0)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChBDel_MAX         (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChBDel_DEF         (0x00000000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank1ChBDel_HSH         (0x04283EA0)

  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChBDel_OFF         (24)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChBDel_WID         ( 4)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChBDel_MSK         (0x0F000000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChBDel_MIN         (0)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChBDel_MAX         (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChBDel_DEF         (0x00000000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank2ChBDel_HSH         (0x04303EA0)

  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChBDel_OFF         (28)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChBDel_WID         ( 4)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChBDel_MSK         (0xF0000000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChBDel_MIN         (0)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChBDel_MAX         (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChBDel_DEF         (0x00000000)
  #define MCMISCS_RXDQFIFORDENCH01_RxDqFifoRdEnRank3ChBDel_HSH         (0x04383EA0)

#define MCMISCS_RXDQFIFORDENCH23_REG                                   (0x00003EA4)
//Duplicate of MCMISCS_RXDQFIFORDENCH01_REG

#define MCMISCS_RXDQFIFORDENCH45_REG                                   (0x00003EA8)
//Duplicate of MCMISCS_RXDQFIFORDENCH01_REG

#define MCMISCS_RXDQFIFORDENCH67_REG                                   (0x00003EAC)
//Duplicate of MCMISCS_RXDQFIFORDENCH01_REG

#define MCMISCS_SPINEGATING_REG                                        (0x00003EB0)

  #define MCMISCS_SPINEGATING_EnableSpineGate_OFF                      ( 0)
  #define MCMISCS_SPINEGATING_EnableSpineGate_WID                      ( 1)
  #define MCMISCS_SPINEGATING_EnableSpineGate_MSK                      (0x00000001)
  #define MCMISCS_SPINEGATING_EnableSpineGate_MIN                      (0)
  #define MCMISCS_SPINEGATING_EnableSpineGate_MAX                      (1) // 0x00000001
  #define MCMISCS_SPINEGATING_EnableSpineGate_DEF                      (0x00000000)
  #define MCMISCS_SPINEGATING_EnableSpineGate_HSH                      (0x01003EB0)

  #define MCMISCS_SPINEGATING_SleepCycles_OFF                          ( 1)
  #define MCMISCS_SPINEGATING_SleepCycles_WID                          ( 3)
  #define MCMISCS_SPINEGATING_SleepCycles_MSK                          (0x0000000E)
  #define MCMISCS_SPINEGATING_SleepCycles_MIN                          (0)
  #define MCMISCS_SPINEGATING_SleepCycles_MAX                          (7) // 0x00000007
  #define MCMISCS_SPINEGATING_SleepCycles_DEF                          (0x00000000)
  #define MCMISCS_SPINEGATING_SleepCycles_HSH                          (0x03023EB0)

  #define MCMISCS_SPINEGATING_AwakeCycles_OFF                          ( 4)
  #define MCMISCS_SPINEGATING_AwakeCycles_WID                          ( 2)
  #define MCMISCS_SPINEGATING_AwakeCycles_MSK                          (0x00000030)
  #define MCMISCS_SPINEGATING_AwakeCycles_MIN                          (0)
  #define MCMISCS_SPINEGATING_AwakeCycles_MAX                          (3) // 0x00000003
  #define MCMISCS_SPINEGATING_AwakeCycles_DEF                          (0x00000000)
  #define MCMISCS_SPINEGATING_AwakeCycles_HSH                          (0x02083EB0)

  #define MCMISCS_SPINEGATING_EnHiPhase_OFF                            ( 6)
  #define MCMISCS_SPINEGATING_EnHiPhase_WID                            ( 2)
  #define MCMISCS_SPINEGATING_EnHiPhase_MSK                            (0x000000C0)
  #define MCMISCS_SPINEGATING_EnHiPhase_MIN                            (0)
  #define MCMISCS_SPINEGATING_EnHiPhase_MAX                            (3) // 0x00000003
  #define MCMISCS_SPINEGATING_EnHiPhase_DEF                            (0x00000000)
  #define MCMISCS_SPINEGATING_EnHiPhase_HSH                            (0x020C3EB0)

  #define MCMISCS_SPINEGATING_GraceLimitEntry_OFF                      ( 8)
  #define MCMISCS_SPINEGATING_GraceLimitEntry_WID                      ( 3)
  #define MCMISCS_SPINEGATING_GraceLimitEntry_MSK                      (0x00000700)
  #define MCMISCS_SPINEGATING_GraceLimitEntry_MIN                      (0)
  #define MCMISCS_SPINEGATING_GraceLimitEntry_MAX                      (7) // 0x00000007
  #define MCMISCS_SPINEGATING_GraceLimitEntry_DEF                      (0x00000000)
  #define MCMISCS_SPINEGATING_GraceLimitEntry_HSH                      (0x03103EB0)

  #define MCMISCS_SPINEGATING_rsvd_OFF                                 (11)
  #define MCMISCS_SPINEGATING_rsvd_WID                                 (21)
  #define MCMISCS_SPINEGATING_rsvd_MSK                                 (0xFFFFF800)
  #define MCMISCS_SPINEGATING_rsvd_MIN                                 (0)
  #define MCMISCS_SPINEGATING_rsvd_MAX                                 (2097151) // 0x001FFFFF
  #define MCMISCS_SPINEGATING_rsvd_DEF                                 (0x00000000)
  #define MCMISCS_SPINEGATING_rsvd_HSH                                 (0x15163EB0)

#define MCMISCS_DDRWCKCONTROL_REG                                      (0x00003EB4)

  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_OFF                          ( 0)
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_WID                          ( 7)
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_MSK                          (0x0000007F)
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_MIN                          (0)
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_MAX                          (127) // 0x0000007F
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_DEF                          (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_HSH                          (0x07003EB4)

  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_OFF                          ( 7)
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_WID                          ( 7)
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_MSK                          (0x00003F80)
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_MIN                          (0)
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_MAX                          (127) // 0x0000007F
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_DEF                          (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_HSH                          (0x070E3EB4)

  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_OFF                       (14)
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_WID                       ( 3)
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_MSK                       (0x0001C000)
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_MIN                       (0)
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_MAX                       (7) // 0x00000007
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_DEF                       (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_HSH                       (0x031C3EB4)

  #define MCMISCS_DDRWCKCONTROL_tWckPre_OFF                            (17)
  #define MCMISCS_DDRWCKCONTROL_tWckPre_WID                            ( 5)
  #define MCMISCS_DDRWCKCONTROL_tWckPre_MSK                            (0x003E0000)
  #define MCMISCS_DDRWCKCONTROL_tWckPre_MIN                            (0)
  #define MCMISCS_DDRWCKCONTROL_tWckPre_MAX                            (31) // 0x0000001F
  #define MCMISCS_DDRWCKCONTROL_tWckPre_DEF                            (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_tWckPre_HSH                            (0x05223EB4)

  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_OFF                      (22)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_WID                      ( 1)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_MSK                      (0x00400000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_MIN                      (0)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_MAX                      (1) // 0x00000001
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_DEF                      (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_HSH                      (0x012C3EB4)

  #define MCMISCS_DDRWCKCONTROL_Lp5Mode_OFF                            (23)
  #define MCMISCS_DDRWCKCONTROL_Lp5Mode_WID                            ( 1)
  #define MCMISCS_DDRWCKCONTROL_Lp5Mode_MSK                            (0x00800000)
  #define MCMISCS_DDRWCKCONTROL_Lp5Mode_MIN                            (0)
  #define MCMISCS_DDRWCKCONTROL_Lp5Mode_MAX                            (1) // 0x00000001
  #define MCMISCS_DDRWCKCONTROL_Lp5Mode_DEF                            (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_Lp5Mode_HSH                            (0x012E3EB4)

  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_OFF                   (24)
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_WID                   ( 1)
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_MSK                   (0x01000000)
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_MIN                   (0)
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_MAX                   (1) // 0x00000001
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_DEF                   (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_HSH                   (0x01303EB4)

  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_OFF                         (25)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_WID                         ( 4)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_MSK                         (0x1E000000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_MIN                         (0)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_MAX                         (15) // 0x0000000F
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_DEF                         (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_HSH                         (0x04323EB4)

  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_OFF                       (29)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_WID                       ( 3)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_MSK                       (0xE0000000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_MIN                       (0)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_MAX                       (7) // 0x00000007
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_DEF                       (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_HSH                       (0x033A3EB4)

#define MCMISCS_DDRWCKCONTROL_P0_REG                                   (0x00003EB4)

  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_P0_OFF                       ( 0)
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_P0_WID                       ( 7)
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_P0_MSK                       (0x0000007F)
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_P0_MIN                       (0)
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_P0_MAX                       (127) // 0x0000007F
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_P0_DEF                       (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_cas2rdwck_P0_HSH                       (0x07003EB4)

  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_P0_OFF                       ( 7)
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_P0_WID                       ( 7)
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_P0_MSK                       (0x00003F80)
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_P0_MIN                       (0)
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_P0_MAX                       (127) // 0x0000007F
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_P0_DEF                       (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_cas2wrwck_P0_HSH                       (0x070E3EB4)

  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_P0_OFF                    (14)
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_P0_WID                    ( 3)
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_P0_MSK                    (0x0001C000)
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_P0_MIN                    (0)
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_P0_MAX                    (7) // 0x00000007
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_P0_DEF                    (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_tWckHalfRate_P0_HSH                    (0x031C3EB4)

  #define MCMISCS_DDRWCKCONTROL_tWckPre_P0_OFF                         (17)
  #define MCMISCS_DDRWCKCONTROL_tWckPre_P0_WID                         ( 5)
  #define MCMISCS_DDRWCKCONTROL_tWckPre_P0_MSK                         (0x003E0000)
  #define MCMISCS_DDRWCKCONTROL_tWckPre_P0_MIN                         (0)
  #define MCMISCS_DDRWCKCONTROL_tWckPre_P0_MAX                         (31) // 0x0000001F
  #define MCMISCS_DDRWCKCONTROL_tWckPre_P0_DEF                         (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_tWckPre_P0_HSH                         (0x05223EB4)

  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_P0_OFF                   (22)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_P0_WID                   ( 1)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_P0_MSK                   (0x00400000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_P0_MIN                   (0)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_P0_MAX                   (1) // 0x00000001
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_P0_DEF                   (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkPulse_P0_HSH                   (0x012C3EB4)

  #define MCMISCS_DDRWCKCONTROL_Spare_P0_OFF                           (23)
  #define MCMISCS_DDRWCKCONTROL_Spare_P0_WID                           ( 1)
  #define MCMISCS_DDRWCKCONTROL_Spare_P0_MSK                           (0x00800000)
  #define MCMISCS_DDRWCKCONTROL_Spare_P0_MIN                           (0)
  #define MCMISCS_DDRWCKCONTROL_Spare_P0_MAX                           (1) // 0x00000001
  #define MCMISCS_DDRWCKCONTROL_Spare_P0_DEF                           (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_Spare_P0_HSH                           (0x012E3EB4)

  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_P0_OFF                (24)
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_P0_WID                ( 1)
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_P0_MSK                (0x01000000)
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_P0_MIN                (0)
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_P0_MAX                (1) // 0x00000001
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_P0_DEF                (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_WCkDiffLowInIdle_P0_HSH                (0x01303EB4)

  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_P0_OFF                      (25)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_P0_WID                      ( 4)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_P0_MSK                      (0x1E000000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_P0_MIN                      (0)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_P0_MAX                      (15) // 0x0000000F
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_P0_DEF                      (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkBL_P0_HSH                      (0x04323EB4)

  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_P0_OFF                    (29)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_P0_WID                    ( 3)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_P0_MSK                    (0xE0000000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_P0_MIN                    (0)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_P0_MAX                    (7) // 0x00000007
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_P0_DEF                    (0x00000000)
  #define MCMISCS_DDRWCKCONTROL_TrainWCkMask_P0_HSH                    (0x033A3EB4)

#define DDRSCRAM_CR_DDRLASTCR_REG                                      (0x00003EB8)

  #define DDRSCRAM_CR_DDRLASTCR_EnInitComplete_OFF                     ( 0)
  #define DDRSCRAM_CR_DDRLASTCR_EnInitComplete_WID                     ( 1)
  #define DDRSCRAM_CR_DDRLASTCR_EnInitComplete_MSK                     (0x00000001)
  #define DDRSCRAM_CR_DDRLASTCR_EnInitComplete_MIN                     (0)
  #define DDRSCRAM_CR_DDRLASTCR_EnInitComplete_MAX                     (1) // 0x00000001
  #define DDRSCRAM_CR_DDRLASTCR_EnInitComplete_DEF                     (0x00000000)
  #define DDRSCRAM_CR_DDRLASTCR_EnInitComplete_HSH                     (0x01003EB8)

  #define DDRSCRAM_CR_DDRLASTCR_Spare_OFF                              ( 1)
  #define DDRSCRAM_CR_DDRLASTCR_Spare_WID                              (31)
  #define DDRSCRAM_CR_DDRLASTCR_Spare_MSK                              (0xFFFFFFFE)
  #define DDRSCRAM_CR_DDRLASTCR_Spare_MIN                              (0)
  #define DDRSCRAM_CR_DDRLASTCR_Spare_MAX                              (2147483647) // 0x7FFFFFFF
  #define DDRSCRAM_CR_DDRLASTCR_Spare_DEF                              (0x00000000)
  #define DDRSCRAM_CR_DDRLASTCR_Spare_HSH                              (0x1F023EB8)
#pragma pack(pop)
#endif
