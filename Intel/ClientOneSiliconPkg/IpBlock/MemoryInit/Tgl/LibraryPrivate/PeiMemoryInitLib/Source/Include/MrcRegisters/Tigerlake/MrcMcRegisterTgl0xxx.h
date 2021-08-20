#ifndef __MrcMcRegisterTgl0xxx_h__
#define __MrcMcRegisterTgl0xxx_h__
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


#define DATA0CH0_CR_DDRDATADQRANK0LANE0_REG                            (0x00000000)

  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDqDCCOffset_OFF            ( 0)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDqDCCOffset_WID            ( 6)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDqDCCOffset_MSK            (0x0000003F)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDqDCCOffset_MIN            (-32)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDqDCCOffset_MAX            (31) // 0x0000001F
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDqDCCOffset_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDqDCCOffset_HSH            (0x86000000)

  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskewOffset_OFF   ( 6)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskewOffset_WID   ( 4)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskewOffset_MSK   (0x000003C0)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskewOffset_MIN   (0)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskewOffset_MAX   (15) // 0x0000000F
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskewOffset_DEF   (0x00000000)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskewOffset_HSH   (0x040C0000)

  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskew_OFF         (10)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskew_WID         ( 6)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskew_MSK         (0x0000FC00)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskew_MIN         (0)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskew_MAX         (63) // 0x0000003F
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskew_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQPerBitDeskew_HSH         (0x06140000)

  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset1_OFF          (16)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset1_WID          ( 5)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset1_MSK          (0x001F0000)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset1_MIN          (0)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset1_MAX          (31) // 0x0000001F
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset1_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset1_HSH          (0x05200000)

  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset0_OFF          (21)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset0_WID          ( 5)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset0_MSK          (0x03E00000)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset0_MIN          (0)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset0_MAX          (31) // 0x0000001F
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset0_DEF          (0x00000010)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_RxDQVrefOffset0_HSH          (0x052A0000)

  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDQPerBitDeskew_OFF         (26)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDQPerBitDeskew_WID         ( 6)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDQPerBitDeskew_MSK         (0xFC000000)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDQPerBitDeskew_MIN         (0)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDQPerBitDeskew_MAX         (63) // 0x0000003F
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDQPerBitDeskew_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRDATADQRANK0LANE0_TxDQPerBitDeskew_HSH         (0x06340000)

#define DATA0CH0_CR_DDRDATADQRANK0LANE1_REG                            (0x00000004)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK0LANE2_REG                            (0x00000008)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK0LANE3_REG                            (0x0000000C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK0LANE4_REG                            (0x00000010)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK0LANE5_REG                            (0x00000014)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK0LANE6_REG                            (0x00000018)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK0LANE7_REG                            (0x0000001C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK0LANE8_REG                            (0x00000020)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK1LANE0_REG                            (0x00000024)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK1LANE1_REG                            (0x00000028)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK1LANE2_REG                            (0x0000002C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK1LANE3_REG                            (0x00000030)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK1LANE4_REG                            (0x00000034)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK1LANE5_REG                            (0x00000038)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK1LANE6_REG                            (0x0000003C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK1LANE7_REG                            (0x00000040)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK1LANE8_REG                            (0x00000044)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK2LANE0_REG                            (0x00000048)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK2LANE1_REG                            (0x0000004C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK2LANE2_REG                            (0x00000050)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK2LANE3_REG                            (0x00000054)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK2LANE4_REG                            (0x00000058)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK2LANE5_REG                            (0x0000005C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK2LANE6_REG                            (0x00000060)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK2LANE7_REG                            (0x00000064)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK2LANE8_REG                            (0x00000068)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK3LANE0_REG                            (0x0000006C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK3LANE1_REG                            (0x00000070)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK3LANE2_REG                            (0x00000074)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK3LANE3_REG                            (0x00000078)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK3LANE4_REG                            (0x0000007C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK3LANE5_REG                            (0x00000080)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK3LANE6_REG                            (0x00000084)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK3LANE7_REG                            (0x00000088)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQRANK3LANE8_REG                            (0x0000008C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH0_CR_DDRDATADQSRANK0_REG                                (0x0000009C)

  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSDCCOffset_OFF               ( 0)
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSDCCOffset_WID               ( 7)
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSDCCOffset_MSK               (0x0000007F)
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSDCCOffset_MIN               (-64)
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSDCCOffset_MAX               (63) // 0x0000003F
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSDCCOffset_DEF               (0x00000000)
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSDCCOffset_HSH               (0x8700009C)

  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDQSVrefOffset_OFF              ( 7)
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDQSVrefOffset_WID              ( 5)
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDQSVrefOffset_MSK              (0x00000F80)
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDQSVrefOffset_MIN              (0)
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDQSVrefOffset_MAX              (31) // 0x0000001F
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDQSVrefOffset_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDQSVrefOffset_HSH              (0x050E009C)

  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSPerBitDeskew_OFF            (12)
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSPerBitDeskew_WID            ( 5)
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSPerBitDeskew_MSK            (0x0001F000)
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSPerBitDeskew_MIN            (0)
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSPerBitDeskew_MAX            (31) // 0x0000001F
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSPerBitDeskew_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRDATADQSRANK0_TxDQSPerBitDeskew_HSH            (0x0518009C)

  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDqsUnMatVrefOffset_OFF         (17)
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDqsUnMatVrefOffset_WID         ( 5)
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDqsUnMatVrefOffset_MSK         (0x003E0000)
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDqsUnMatVrefOffset_MIN         (0)
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDqsUnMatVrefOffset_MAX         (31) // 0x0000001F
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDqsUnMatVrefOffset_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRDATADQSRANK0_RxDqsUnMatVrefOffset_HSH         (0x0522009C)

  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPrNfTcoDelay_OFF              (22)
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPrNfTcoDelay_WID              ( 5)
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPrNfTcoDelay_MSK              (0x07C00000)
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPrNfTcoDelay_MIN              (0)
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPrNfTcoDelay_MAX              (31) // 0x0000001F
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPrNfTcoDelay_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPrNfTcoDelay_HSH              (0x052C009C)

  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPfNrTcoDelay_OFF              (27)
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPfNrTcoDelay_WID              ( 5)
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPfNrTcoDelay_MSK              (0xF8000000)
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPfNrTcoDelay_MIN              (0)
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPfNrTcoDelay_MAX              (31) // 0x0000001F
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPfNrTcoDelay_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRDATADQSRANK0_DqsPfNrTcoDelay_HSH              (0x0536009C)

#define DATA0CH0_CR_DDRDATADQSRANK1_REG                                (0x000000A0)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA0CH0_CR_DDRDATADQSRANK2_REG                                (0x000000A4)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA0CH0_CR_DDRDATADQSRANK3_REG                                (0x000000A8)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA0CH0_CR_RXCONTROL0RANK0_REG                                (0x000000AC)

  #define DATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_OFF                    ( 0)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_WID                    (11)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_MSK                    (0x000007FF)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_MIN                    (0)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_MAX                    (2047) // 0x000007FF
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_DEF                    (0x000007FF)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_HSH                    (0x0B0000AC)

  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsPDelayPi_OFF                (11)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsPDelayPi_WID                ( 8)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsPDelayPi_MSK                (0x0007F800)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsPDelayPi_MIN                (0)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsPDelayPi_MAX                (255) // 0x000000FF
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsPDelayPi_DEF                (0x00000000)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsPDelayPi_HSH                (0x081600AC)

  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsNDelayPi_OFF                (19)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsNDelayPi_WID                ( 8)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsNDelayPi_MSK                (0x07F80000)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsNDelayPi_MIN                (0)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsNDelayPi_MAX                (255) // 0x000000FF
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsNDelayPi_DEF                (0x00000000)
  #define DATA0CH0_CR_RXCONTROL0RANK0_RxDqsNDelayPi_HSH                (0x082600AC)

  #define DATA0CH0_CR_RXCONTROL0RANK0_Spare_OFF                        (27)
  #define DATA0CH0_CR_RXCONTROL0RANK0_Spare_WID                        ( 5)
  #define DATA0CH0_CR_RXCONTROL0RANK0_Spare_MSK                        (0xF8000000)
  #define DATA0CH0_CR_RXCONTROL0RANK0_Spare_MIN                        (0)
  #define DATA0CH0_CR_RXCONTROL0RANK0_Spare_MAX                        (31) // 0x0000001F
  #define DATA0CH0_CR_RXCONTROL0RANK0_Spare_DEF                        (0x00000000)
  #define DATA0CH0_CR_RXCONTROL0RANK0_Spare_HSH                        (0x053600AC)

#define DATA0CH0_CR_RXCONTROL0RANK1_REG                                (0x000000B0)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA0CH0_CR_RXCONTROL0RANK2_REG                                (0x000000B4)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA0CH0_CR_RXCONTROL0RANK3_REG                                (0x000000B8)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA0CH0_CR_TXCONTROL0RANK0_REG                                (0x000000BC)

  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqDelay_OFF                    ( 0)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqDelay_WID                    (11)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqDelay_MSK                    (0x000007FF)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqDelay_MIN                    (0)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqDelay_MAX                    (2047) // 0x000007FF
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqDelay_DEF                    (0x000007FF)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqDelay_HSH                    (0x0B0000BC)

  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqsDelay_OFF                   (11)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqsDelay_WID                   (11)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqsDelay_MSK                   (0x003FF800)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqsDelay_MIN                   (0)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqsDelay_MAX                   (2047) // 0x000007FF
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqsDelay_DEF                   (0x000007FF)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxDqsDelay_HSH                   (0x0B1600BC)

  #define DATA0CH0_CR_TXCONTROL0RANK0_TxEqualization_OFF               (22)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxEqualization_WID               ( 4)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxEqualization_MSK               (0x03C00000)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxEqualization_MIN               (0)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxEqualization_MAX               (15) // 0x0000000F
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxEqualization_DEF               (0x0000000F)
  #define DATA0CH0_CR_TXCONTROL0RANK0_TxEqualization_HSH               (0x042C00BC)

  #define DATA0CH0_CR_TXCONTROL0RANK0_Spare_OFF                        (26)
  #define DATA0CH0_CR_TXCONTROL0RANK0_Spare_WID                        ( 6)
  #define DATA0CH0_CR_TXCONTROL0RANK0_Spare_MSK                        (0xFC000000)
  #define DATA0CH0_CR_TXCONTROL0RANK0_Spare_MIN                        (0)
  #define DATA0CH0_CR_TXCONTROL0RANK0_Spare_MAX                        (63) // 0x0000003F
  #define DATA0CH0_CR_TXCONTROL0RANK0_Spare_DEF                        (0x00000000)
  #define DATA0CH0_CR_TXCONTROL0RANK0_Spare_HSH                        (0x063400BC)

#define DATA0CH0_CR_TXCONTROL0RANK1_REG                                (0x000000C0)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA0CH0_CR_TXCONTROL0RANK2_REG                                (0x000000C4)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA0CH0_CR_TXCONTROL0RANK3_REG                                (0x000000C8)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA0CH0_CR_RCOMPDATA0_REG                                     (0x000000CC)

  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvUp_OFF                        ( 0)
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvUp_WID                        ( 6)
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvUp_MSK                        (0x0000003F)
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvUp_MIN                        (0)
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvUp_MAX                        (63) // 0x0000003F
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvUp_DEF                        (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvUp_HSH                        (0x060000CC)

  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvDown_OFF                      ( 6)
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvDown_WID                      ( 6)
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvDown_MSK                      (0x00000FC0)
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvDown_MIN                      (0)
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvDown_MAX                      (63) // 0x0000003F
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvDown_DEF                      (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA0_RcompDrvDown_HSH                      (0x060C00CC)

  #define DATA0CH0_CR_RCOMPDATA0_VssHiFF_OFF                           (12)
  #define DATA0CH0_CR_RCOMPDATA0_VssHiFF_WID                           ( 6)
  #define DATA0CH0_CR_RCOMPDATA0_VssHiFF_MSK                           (0x0003F000)
  #define DATA0CH0_CR_RCOMPDATA0_VssHiFF_MIN                           (0)
  #define DATA0CH0_CR_RCOMPDATA0_VssHiFF_MAX                           (63) // 0x0000003F
  #define DATA0CH0_CR_RCOMPDATA0_VssHiFF_DEF                           (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA0_VssHiFF_HSH                           (0x061800CC)

  #define DATA0CH0_CR_RCOMPDATA0_SlewRateComp_OFF                      (18)
  #define DATA0CH0_CR_RCOMPDATA0_SlewRateComp_WID                      ( 5)
  #define DATA0CH0_CR_RCOMPDATA0_SlewRateComp_MSK                      (0x007C0000)
  #define DATA0CH0_CR_RCOMPDATA0_SlewRateComp_MIN                      (0)
  #define DATA0CH0_CR_RCOMPDATA0_SlewRateComp_MAX                      (31) // 0x0000001F
  #define DATA0CH0_CR_RCOMPDATA0_SlewRateComp_DEF                      (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA0_SlewRateComp_HSH                      (0x052400CC)

  #define DATA0CH0_CR_RCOMPDATA0_DqsNTargetNUI_OFF                     (23)
  #define DATA0CH0_CR_RCOMPDATA0_DqsNTargetNUI_WID                     ( 2)
  #define DATA0CH0_CR_RCOMPDATA0_DqsNTargetNUI_MSK                     (0x01800000)
  #define DATA0CH0_CR_RCOMPDATA0_DqsNTargetNUI_MIN                     (0)
  #define DATA0CH0_CR_RCOMPDATA0_DqsNTargetNUI_MAX                     (3) // 0x00000003
  #define DATA0CH0_CR_RCOMPDATA0_DqsNTargetNUI_DEF                     (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA0_DqsNTargetNUI_HSH                     (0x022E00CC)

  #define DATA0CH0_CR_RCOMPDATA0_DqsNOffsetNUI_OFF                     (25)
  #define DATA0CH0_CR_RCOMPDATA0_DqsNOffsetNUI_WID                     ( 2)
  #define DATA0CH0_CR_RCOMPDATA0_DqsNOffsetNUI_MSK                     (0x06000000)
  #define DATA0CH0_CR_RCOMPDATA0_DqsNOffsetNUI_MIN                     (0)
  #define DATA0CH0_CR_RCOMPDATA0_DqsNOffsetNUI_MAX                     (3) // 0x00000003
  #define DATA0CH0_CR_RCOMPDATA0_DqsNOffsetNUI_DEF                     (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA0_DqsNOffsetNUI_HSH                     (0x023200CC)

  #define DATA0CH0_CR_RCOMPDATA0_RParkOdtDown_OFF                      (27)
  #define DATA0CH0_CR_RCOMPDATA0_RParkOdtDown_WID                      ( 5)
  #define DATA0CH0_CR_RCOMPDATA0_RParkOdtDown_MSK                      (0xF8000000)
  #define DATA0CH0_CR_RCOMPDATA0_RParkOdtDown_MIN                      (0)
  #define DATA0CH0_CR_RCOMPDATA0_RParkOdtDown_MAX                      (31) // 0x0000001F
  #define DATA0CH0_CR_RCOMPDATA0_RParkOdtDown_DEF                      (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA0_RParkOdtDown_HSH                      (0x053600CC)

#define DATA0CH0_CR_RCOMPDATA1_REG                                     (0x000000D0)

  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtUp_OFF                        ( 0)
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtUp_WID                        ( 6)
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtUp_MSK                        (0x0000003F)
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtUp_MIN                        (0)
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtUp_MAX                        (63) // 0x0000003F
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtUp_DEF                        (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtUp_HSH                        (0x060000D0)

  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtDown_OFF                      ( 6)
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtDown_WID                      ( 6)
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtDown_MSK                      (0x00000FC0)
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtDown_MIN                      (0)
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtDown_MAX                      (63) // 0x0000003F
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtDown_DEF                      (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA1_RcompOdtDown_HSH                      (0x060C00D0)

  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayN_OFF                       (12)
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayN_WID                       ( 8)
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayN_MSK                       (0x000FF000)
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayN_MIN                       (0)
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayN_MAX                       (255) // 0x000000FF
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayN_DEF                       (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayN_HSH                       (0x081800D0)

  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayP_OFF                       (20)
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayP_WID                       ( 8)
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayP_MSK                       (0x0FF00000)
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayP_MIN                       (0)
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayP_MAX                       (255) // 0x000000FF
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayP_DEF                       (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA1_RxDqsDelayP_HSH                       (0x082800D0)

  #define DATA0CH0_CR_RCOMPDATA1_DqsPTargetNUI_OFF                     (28)
  #define DATA0CH0_CR_RCOMPDATA1_DqsPTargetNUI_WID                     ( 2)
  #define DATA0CH0_CR_RCOMPDATA1_DqsPTargetNUI_MSK                     (0x30000000)
  #define DATA0CH0_CR_RCOMPDATA1_DqsPTargetNUI_MIN                     (0)
  #define DATA0CH0_CR_RCOMPDATA1_DqsPTargetNUI_MAX                     (3) // 0x00000003
  #define DATA0CH0_CR_RCOMPDATA1_DqsPTargetNUI_DEF                     (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA1_DqsPTargetNUI_HSH                     (0x023800D0)

  #define DATA0CH0_CR_RCOMPDATA1_DqsPOffsetNUI_OFF                     (30)
  #define DATA0CH0_CR_RCOMPDATA1_DqsPOffsetNUI_WID                     ( 2)
  #define DATA0CH0_CR_RCOMPDATA1_DqsPOffsetNUI_MSK                     (0xC0000000)
  #define DATA0CH0_CR_RCOMPDATA1_DqsPOffsetNUI_MIN                     (0)
  #define DATA0CH0_CR_RCOMPDATA1_DqsPOffsetNUI_MAX                     (3) // 0x00000003
  #define DATA0CH0_CR_RCOMPDATA1_DqsPOffsetNUI_DEF                     (0x00000000)
  #define DATA0CH0_CR_RCOMPDATA1_DqsPOffsetNUI_HSH                     (0x023C00D0)

#define DATA0CH0_CR_DATACOMPVTT_REG                                    (0x000000D4)

  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn0_OFF                      ( 0)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn0_WID                      ( 8)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn0_MSK                      (0x000000FF)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn0_MIN                      (0)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn0_MAX                      (255) // 0x000000FF
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn0_DEF                      (0x00000000)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn0_HSH                      (0x080000D4)

  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn1_OFF                      ( 8)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn1_WID                      ( 8)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn1_MSK                      (0x0000FF00)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn1_MIN                      (0)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn1_MAX                      (255) // 0x000000FF
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn1_DEF                      (0x00000000)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttDn1_HSH                      (0x081000D4)

  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp0_OFF                      (16)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp0_WID                      ( 8)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp0_MSK                      (0x00FF0000)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp0_MIN                      (0)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp0_MAX                      (255) // 0x000000FF
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp0_DEF                      (0x00000000)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp0_HSH                      (0x082000D4)

  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp1_OFF                      (24)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp1_WID                      ( 8)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp1_MSK                      (0xFF000000)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp1_MIN                      (0)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp1_MAX                      (255) // 0x000000FF
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp1_DEF                      (0x00000000)
  #define DATA0CH0_CR_DATACOMPVTT_PanicVttUp1_HSH                      (0x083000D4)

#define DATA0CH0_CR_DATATRAINFEEDBACK_REG                              (0x000000DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankOvrd_OFF                   ( 0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankOvrd_WID                   ( 1)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankOvrd_MSK                   (0x00000001)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankOvrd_MIN                   (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankOvrd_MAX                   (1) // 0x00000001
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankOvrd_DEF                   (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankOvrd_HSH                   (0x010000DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankValue_OFF                  ( 1)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankValue_WID                  ( 2)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankValue_MSK                  (0x00000006)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankValue_MIN                  (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankValue_MAX                  (3) // 0x00000003
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankValue_DEF                  (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RankValue_HSH                  (0x020200DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxAmpOffsetEn_OFF              ( 3)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxAmpOffsetEn_WID              ( 2)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxAmpOffsetEn_MSK              (0x00000018)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxAmpOffsetEn_MIN              (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxAmpOffsetEn_MAX              (3) // 0x00000003
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxAmpOffsetEn_DEF              (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxAmpOffsetEn_HSH              (0x020600DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxTrainingMode_OFF             ( 5)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxTrainingMode_WID             ( 1)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxTrainingMode_MSK             (0x00000020)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxTrainingMode_MIN             (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxTrainingMode_MAX             (1) // 0x00000001
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxTrainingMode_DEF             (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RxTrainingMode_HSH             (0x010A00DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_WLTrainingMode_OFF             ( 6)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_WLTrainingMode_WID             ( 2)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_WLTrainingMode_MSK             (0x000000C0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_WLTrainingMode_MIN             (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_WLTrainingMode_MAX             (3) // 0x00000003
  #define DATA0CH0_CR_DATATRAINFEEDBACK_WLTrainingMode_DEF             (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_WLTrainingMode_HSH             (0x020C00DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_RLTrainingMode_OFF             ( 8)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RLTrainingMode_WID             ( 1)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RLTrainingMode_MSK             (0x00000100)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RLTrainingMode_MIN             (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RLTrainingMode_MAX             (1) // 0x00000001
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RLTrainingMode_DEF             (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_RLTrainingMode_HSH             (0x011000DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_SenseampTrainingMode_OFF       ( 9)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_SenseampTrainingMode_WID       ( 1)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_SenseampTrainingMode_MSK       (0x00000200)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_SenseampTrainingMode_MIN       (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_SenseampTrainingMode_MAX       (1) // 0x00000001
  #define DATA0CH0_CR_DATATRAINFEEDBACK_SenseampTrainingMode_DEF       (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_SenseampTrainingMode_HSH       (0x011200DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_CATrainingMode_OFF             (10)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CATrainingMode_WID             ( 1)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CATrainingMode_MSK             (0x00000400)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CATrainingMode_MIN             (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CATrainingMode_MAX             (1) // 0x00000001
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CATrainingMode_DEF             (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CATrainingMode_HSH             (0x011400DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_DqsRFTrainingMode_OFF          (11)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DqsRFTrainingMode_WID          ( 1)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DqsRFTrainingMode_MSK          (0x00000800)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DqsRFTrainingMode_MIN          (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DqsRFTrainingMode_MAX          (1) // 0x00000001
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DqsRFTrainingMode_DEF          (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DqsRFTrainingMode_HSH          (0x011600DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_OFF          (12)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_WID          (10)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MSK          (0x003FF000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MIN          (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MAX          (1023) // 0x000003FF
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_DEF          (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_HSH          (0x0A1800DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityTrain_OFF              (22)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityTrain_WID              ( 1)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityTrain_MSK              (0x00400000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityTrain_MIN              (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityTrain_MAX              (1) // 0x00000001
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityTrain_DEF              (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityTrain_HSH              (0x012C00DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityOdd_OFF                (23)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityOdd_WID                ( 1)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityOdd_MSK                (0x00800000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityOdd_MIN                (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityOdd_MAX                (1) // 0x00000001
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityOdd_DEF                (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_CAParityOdd_HSH                (0x012E00DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_LPDDR5_OFF                     (24)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_LPDDR5_WID                     ( 1)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_LPDDR5_MSK                     (0x01000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_LPDDR5_MIN                     (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_LPDDR5_MAX                     (1) // 0x00000001
  #define DATA0CH0_CR_DATATRAINFEEDBACK_LPDDR5_DEF                     (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_LPDDR5_HSH                     (0x013000DC)

  #define DATA0CH0_CR_DATATRAINFEEDBACK_Spare_OFF                      (25)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_Spare_WID                      ( 7)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_Spare_MSK                      (0xFE000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_Spare_MIN                      (0)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_Spare_MAX                      (127) // 0x0000007F
  #define DATA0CH0_CR_DATATRAINFEEDBACK_Spare_DEF                      (0x00000000)
  #define DATA0CH0_CR_DATATRAINFEEDBACK_Spare_HSH                      (0x073200DC)

#define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG                            (0x000000E0)

  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_OFF        ( 0)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_WID        ( 6)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MSK        (0x0000003F)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MIN        (-32)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MAX        (31) // 0x0000001F
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_HSH        (0x860000E0)

  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_OFF      ( 6)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_WID      ( 6)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MSK      (0x00000FC0)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MIN      (-32)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MAX      (31) // 0x0000001F
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_DEF      (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_HSH      (0x860C00E0)

  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtCompOffset_OFF          (12)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtCompOffset_WID          ( 5)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtCompOffset_MSK          (0x0001F000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtCompOffset_MIN          (-16)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtCompOffset_MAX          (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtCompOffset_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtCompOffset_HSH          (0x851800E0)

  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_VssHiFFCompOffset_OFF        (17)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_VssHiFFCompOffset_WID        ( 5)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_VssHiFFCompOffset_MSK        (0x003E0000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_VssHiFFCompOffset_MIN        (-16)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_VssHiFFCompOffset_MAX        (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_VssHiFFCompOffset_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_VssHiFFCompOffset_HSH        (0x852200E0)

  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_OFF     (22)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_WID     ( 5)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MSK     (0x07C00000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MIN     (-16)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MAX     (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_DEF     (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_HSH     (0x852C00E0)

  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_RloadOffset_OFF              (27)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_RloadOffset_WID              ( 5)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_RloadOffset_MSK              (0xF8000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_RloadOffset_MIN              (-16)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_RloadOffset_MAX              (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_RloadOffset_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETCOMP_RloadOffset_HSH              (0x853600E0)

#define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG                           (0x000000E4)

  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_OFF             ( 0)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_WID             ( 6)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MSK             (0x0000003F)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MIN             (-32)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MAX             (31) // 0x0000001F
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_HSH             (0x860000E4)

  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_OFF             ( 6)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_WID             ( 7)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MSK             (0x00001FC0)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MIN             (-64)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MAX             (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_HSH             (0x870C00E4)

  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_OFF              (13)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_WID              ( 6)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MSK              (0x0007E000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MIN              (-32)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MAX              (31) // 0x0000001F
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_HSH              (0x861A00E4)

  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_OFF             (19)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_WID             ( 6)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MSK             (0x01F80000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MIN             (-32)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MAX             (31) // 0x0000001F
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_HSH             (0x862600E4)

  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_OFF              (25)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_WID              ( 7)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MSK              (0xFE000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MIN              (-64)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MAX              (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_HSH              (0x873200E4)

#define DATA0CH0_CR_DDRCRDATACONTROL0_REG                              (0x000000E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_OFF ( 0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_WID ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_MSK (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_MIN (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_MAX (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_HSH (0x010000E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_OFF            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_MSK            (0x00000002)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_DEF            (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_HSH            (0x010200E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsOdtVss_OFF                  ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsOdtVss_WID                  ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsOdtVss_MSK                  (0x00000004)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsOdtVss_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsOdtVss_MAX                  (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsOdtVss_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsOdtVss_HSH                  (0x010400E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_OFF           ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_WID           ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_MSK           (0x00000008)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_MAX           (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_HSH           (0x010600E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_OFF           ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_WID           ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MSK           (0x00000010)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MAX           (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_HSH           (0x010800E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_OFF                ( 5)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_WID                ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_MSK                (0x00000020)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_MIN                (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_MAX                (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_DEF                (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_HSH                (0x010A00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_OFF            ( 6)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_MSK            (0x00000040)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_HSH            (0x010C00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_OFF                     ( 7)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_WID                     ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_MSK                     (0x00000080)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_MIN                     (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_MAX                     (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_DEF                     (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_HSH                     (0x010E00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_OFF                       ( 8)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_WID                       ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_MSK                       (0x00000100)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_MIN                       (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_MAX                       (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_DEF                       (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_HSH                       (0x011000E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_OFF                  ( 9)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_WID                  ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_MSK                  (0x00000200)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_MAX                  (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_HSH                  (0x011200E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_OFF            (10)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_MSK            (0x00000400)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_HSH            (0x011400E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_OFF           (11)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_WID           ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_MSK           (0x00001800)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_MAX           (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_HSH           (0x021600E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_OFF                 (13)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_WID                 ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_MSK                 (0x00006000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_MAX                 (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_DEF                 (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_HSH                 (0x021A00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_OFF                 (15)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_WID                 ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_MSK                 (0x00018000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_MAX                 (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_DEF                 (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_HSH                 (0x021E00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_OFF                  (17)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_WID                  ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_MSK                  (0x00020000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_MAX                  (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_HSH                  (0x012200E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_OFF                  (18)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_WID                  ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_MSK                  (0x00040000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_MAX                  (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_HSH                  (0x012400E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_OFF                     (19)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_WID                     ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_MSK                     (0x00180000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_MIN                     (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_MAX                     (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_DEF                     (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_HSH                     (0x022600E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_OFF             (21)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_WID             ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_MSK             (0x00200000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_MIN             (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_MAX             (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_HSH             (0x012A00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_OFF             (22)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_WID             ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_MSK             (0x00400000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_MIN             (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_MAX             (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_HSH             (0x012C00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_OFF                 (23)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_WID                 ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_MSK                 (0x00800000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_MAX                 (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_DEF                 (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_HSH                 (0x012E00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_OFF           (24)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_WID           ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_MSK           (0x01000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_MAX           (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_HSH           (0x013000E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_OFF            (25)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MSK            (0x02000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_HSH            (0x013200E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_OFF                    (26)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_WID                    ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_MSK                    (0x0C000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_MIN                    (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_MAX                    (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_DEF                    (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_HSH                    (0x023400E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_OFF             (28)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_WID             ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_MSK             (0xF0000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_MIN             (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_MAX             (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_HSH             (0x043800E8)

#define DATA0CH0_CR_DDRCRDATACONTROL0_A0_REG                           (0x000000E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_A0_OFF ( 0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_A0_WID ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_A0_MSK (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_A0_MAX (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_A0_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_tx_clock_on_with_txanalogen_A0_HSH (0x010000E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_A0_OFF         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_A0_WID         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_A0_MSK         (0x00000002)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_A0_MIN         (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_A0_MAX         (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_A0_DEF         (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_local_gate_d0tx_A0_HSH         (0x010200E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_Spare_A0_OFF                   ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_Spare_A0_WID                   ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_Spare_A0_MSK                   (0x00000004)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_Spare_A0_MIN                   (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_Spare_A0_MAX                   (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_Spare_A0_DEF                   (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_Spare_A0_HSH                   (0x010400E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_A0_OFF        ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_A0_WID        ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_A0_MSK        (0x00000008)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_A0_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_A0_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_A0_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_A0_HSH        (0x010600E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_A0_OFF        ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_A0_WID        ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_A0_MSK        (0x00000010)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_A0_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_A0_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_A0_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_A0_HSH        (0x010800E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_A0_OFF             ( 5)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_A0_WID             ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_A0_MSK             (0x00000020)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_A0_MIN             (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_A0_MAX             (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_A0_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_WlLongDelEn_A0_HSH             (0x010A00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_A0_OFF         ( 6)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_A0_WID         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_A0_MSK         (0x00000040)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_A0_MIN         (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_A0_MAX         (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_A0_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDeskewForceOn_A0_HSH         (0x010C00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_A0_OFF                  ( 7)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_A0_WID                  ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_A0_MSK                  (0x00000080)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_A0_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_A0_MAX                  (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_A0_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_A0_HSH                  (0x010E00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_A0_OFF                    ( 8)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_A0_WID                    ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_A0_MSK                    (0x00000100)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_A0_MIN                    (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_A0_MAX                    (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_A0_DEF                    (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxOn_A0_HSH                    (0x011000E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_A0_OFF               ( 9)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_A0_WID               ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_A0_MSK               (0x00000200)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_A0_MIN               (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_A0_MAX               (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_A0_DEF               (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_A0_HSH               (0x011200E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_A0_OFF         (10)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_A0_WID         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_A0_MSK         (0x00000400)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_A0_MIN         (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_A0_MAX         (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_A0_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqOdtParkMode_A0_HSH         (0x011400E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_A0_OFF        (11)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_A0_WID        ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_A0_MSK        (0x00001800)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_A0_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_A0_MAX        (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_A0_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_EnDqsOdtParkMode_A0_HSH        (0x021600E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_A0_OFF              (13)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_A0_WID              ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_A0_MSK              (0x00006000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_A0_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_A0_MAX              (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_A0_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_BiasPMCtrl_A0_HSH              (0x021A00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_A0_OFF              (15)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_A0_WID              ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_A0_MSK              (0x00018000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_A0_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_A0_MAX              (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_A0_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_VrefPMCtrl_A0_HSH              (0x021E00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_A0_OFF               (17)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_A0_WID               ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_A0_MSK               (0x00020000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_A0_MIN               (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_A0_MAX               (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_A0_DEF               (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxDisable_A0_HSH               (0x012200E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_A0_OFF               (18)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_A0_WID               ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_A0_MSK               (0x00040000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_A0_MIN               (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_A0_MAX               (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_A0_DEF               (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_ForceRxOn_A0_HSH               (0x012400E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_A0_OFF                  (19)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_A0_WID                  ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_A0_MSK                  (0x00180000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_A0_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_A0_MAX                  (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_A0_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_RxMode_A0_HSH                  (0x022600E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_A0_OFF          (21)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_A0_WID          ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_A0_MSK          (0x00200000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_A0_MIN          (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_A0_MAX          (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_A0_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DqsNParkLowVoh_A0_HSH          (0x012A00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_A0_OFF          (22)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_A0_WID          ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_A0_MSK          (0x00400000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_A0_MIN          (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_A0_MAX          (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_A0_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtForceQDrvEn_A0_HSH          (0x012C00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_A0_OFF              (23)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_A0_WID              ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_A0_MSK              (0x00800000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_A0_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_A0_MAX              (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_A0_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtSampOff_A0_HSH              (0x012E00E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_A0_OFF        (24)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_A0_WID        ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_A0_MSK        (0x01000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_A0_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_A0_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_A0_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_A0_HSH        (0x013000E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_A0_OFF         (25)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_A0_WID         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_A0_MSK         (0x02000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_A0_MIN         (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_A0_MAX         (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_A0_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_A0_HSH         (0x013200E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_A0_OFF                 (26)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_A0_WID                 ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_A0_MSK                 (0x0C000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_A0_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_A0_MAX                 (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_A0_DEF                 (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_OdtMode_A0_HSH                 (0x023400E8)

  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_A0_OFF          (28)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_A0_WID          ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_A0_MSK          (0xF0000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_A0_MIN          (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_A0_MAX          (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_A0_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL0_TxRankMuxDelay_A0_HSH          (0x043800E8)

#define DATA0CH0_CR_DDRCRDATACONTROL1_REG                              (0x000000EC)

  #define DATA0CH0_CR_DDRCRDATACONTROL1_RXDeskewForceOn_OFF            ( 0)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_RXDeskewForceOn_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_RXDeskewForceOn_MSK            (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_RXDeskewForceOn_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_RXDeskewForceOn_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL1_RXDeskewForceOn_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_RXDeskewForceOn_HSH            (0x010000EC)

  #define DATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_OFF         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_WID         ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MSK         (0x0000001E)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MIN         (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MAX         (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_HSH         (0x040200EC)

  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDelay_OFF                ( 5)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDelay_WID                ( 6)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDelay_MSK                (0x000007E0)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDelay_MIN                (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDelay_MAX                (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDelay_DEF                (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDelay_HSH                (0x060A00EC)

  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDuration_OFF             (11)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDuration_WID             ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDuration_MSK             (0x00003800)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDuration_MIN             (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDuration_MAX             (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDuration_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqsOdtDuration_HSH             (0x031600EC)

  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDelay_OFF                 (14)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDelay_WID                 ( 5)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDelay_MSK                 (0x0007C000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDelay_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDelay_MAX                 (31) // 0x0000001F
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDelay_DEF                 (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDelay_HSH                 (0x051C00EC)

  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDuration_OFF              (19)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDuration_WID              ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDuration_MSK              (0x00780000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDuration_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDuration_MAX              (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDuration_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_DqOdtDuration_HSH              (0x042600EC)

  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_OFF              (23)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_WID              ( 5)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MSK              (0x0F800000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MAX              (31) // 0x0000001F
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_HSH              (0x052E00EC)

  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_OFF           (28)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_WID           ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MSK           (0xF0000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MAX           (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_HSH           (0x043800EC)

#define DATA0CH0_CR_DDRCRDATACONTROL2_REG                              (0x000000F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVddqProgMFC_OFF          ( 0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVddqProgMFC_WID          ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVddqProgMFC_MSK          (0x00000007)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVddqProgMFC_MIN          (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVddqProgMFC_MAX          (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVddqProgMFC_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVddqProgMFC_HSH          (0x030000F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_OFF           ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_WID           ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_MSK           (0x00000038)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_MAX           (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxVrefVttProgMFC_HSH           (0x030600F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxBurstLen_OFF                 ( 6)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxBurstLen_WID                 ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxBurstLen_MSK                 (0x000001C0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxBurstLen_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxBurstLen_MAX                 (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxBurstLen_DEF                 (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxBurstLen_HSH                 (0x030C00F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_OFF            ( 9)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MSK            (0x00000200)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_HSH            (0x011200F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnDqsNRcvEn_OFF                (10)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnDqsNRcvEn_WID                ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnDqsNRcvEn_MSK                (0x00000400)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnDqsNRcvEn_MIN                (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnDqsNRcvEn_MAX                (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnDqsNRcvEn_DEF                (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnDqsNRcvEn_HSH                (0x011400F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_adjustment_rsvd_OFF      (11)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_adjustment_rsvd_WID      ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_adjustment_rsvd_MSK      (0x00007800)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_adjustment_rsvd_MIN      (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_adjustment_rsvd_MAX      (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_adjustment_rsvd_DEF      (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_adjustment_rsvd_HSH      (0x041600F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_mindelay_ctl_OFF         (15)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_mindelay_ctl_WID         ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_mindelay_ctl_MSK         (0x00018000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_mindelay_ctl_MIN         (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_mindelay_ctl_MAX         (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_mindelay_ctl_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_xover_mindelay_ctl_HSH         (0x021E00F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_DisableDqsOdtStatic_OFF        (17)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DisableDqsOdtStatic_WID        ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DisableDqsOdtStatic_MSK        (0x00020000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DisableDqsOdtStatic_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DisableDqsOdtStatic_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DisableDqsOdtStatic_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_DisableDqsOdtStatic_HSH        (0x012200F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxPBDCalibration_OFF           (18)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxPBDCalibration_WID           ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxPBDCalibration_MSK           (0x000C0000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxPBDCalibration_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxPBDCalibration_MAX           (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxPBDCalibration_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxPBDCalibration_HSH           (0x022400F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_OFF               (20)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_WID               ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_MSK               (0x00100000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_MIN               (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_MAX               (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_DEF               (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_HSH               (0x012800F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxEqDis_OFF                    (21)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxEqDis_WID                    ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxEqDis_MSK                    (0x00200000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxEqDis_MIN                    (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxEqDis_MAX                    (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxEqDis_DEF                    (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_TxEqDis_HSH                    (0x012A00F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_OFF                (22)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_WID                ( 6)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MSK                (0x0FC00000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MIN                (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX                (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_DEF                (0x00000011)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_HSH                (0x062C00F0)

  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_OFF             (28)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_WID             ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_MSK             (0xF0000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_MIN             (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_MAX             (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_HSH             (0x043800F0)

#define DATA0CH0_CR_DDRCRDATACONTROL3_REG                              (0x000000F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_OFF                      ( 0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_WID                      ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_MSK                      (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_MIN                      (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_MAX                      (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_DEF                      (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_HSH                      (0x010000F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_OFF            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_MSK            (0x00000002)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_HSH            (0x010200F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_OFF            ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_MSK            (0x00000004)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_HSH            (0x010400F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_OFF          ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_WID          ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_MSK          (0x00000008)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_MIN          (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_MAX          (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_HSH          (0x010600F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_OFF              ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_WID              ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_MSK              (0x00000030)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_MAX              (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_HSH              (0x020800F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_OFF                 ( 6)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_WID                 ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_MSK                 (0x000001C0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_MAX                 (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_DEF                 (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_HSH                 (0x030C00F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_OFF            ( 9)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_MSK            (0x00000200)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_HSH            (0x011200F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_OFF                  (10)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_WID                  ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_MSK                  (0x00000400)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_MAX                  (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_DEF                  (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_HSH                  (0x011400F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_OFF                    (11)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_WID                    ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_MSK                    (0x00000800)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_MIN                    (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_MAX                    (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_DEF                    (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_HSH                    (0x011600F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_OFF        (12)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_WID        ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_MSK        (0x00001000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_DEF        (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_HSH        (0x011800F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_OFF                   (13)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_WID                   ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_MSK                   (0x00006000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_MIN                   (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_MAX                   (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_DEF                   (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_HSH                   (0x021A00F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_OFF           (15)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_WID           ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_MSK           (0x00008000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_MAX           (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_HSH           (0x011E00F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_OFF   (16)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_WID   ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_MSK   (0x00030000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_MIN   (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_MAX   (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_DEF   (0x00000003)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_HSH   (0x022000F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_OFF (18)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_WID ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_MSK (0x000C0000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_MIN (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_MAX (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_DEF (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_HSH (0x022400F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_BlockSdlWithRcvEn_OFF          (20)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_BlockSdlWithRcvEn_WID          ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_BlockSdlWithRcvEn_MSK          (0x00100000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_BlockSdlWithRcvEn_MIN          (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_BlockSdlWithRcvEn_MAX          (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_BlockSdlWithRcvEn_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_BlockSdlWithRcvEn_HSH          (0x012800F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_RcvEnExtFF_OFF                 (21)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RcvEnExtFF_WID                 ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RcvEnExtFF_MSK                 (0x00600000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RcvEnExtFF_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RcvEnExtFF_MAX                 (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RcvEnExtFF_DEF                 (0x00000002)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RcvEnExtFF_HSH                 (0x022A00F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_OFF               (23)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_WID               ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_MSK               (0x00800000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_MIN               (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_MAX               (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_DEF               (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_HSH               (0x012E00F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxRankMuxDelay_2ndStg_OFF      (24)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxRankMuxDelay_2ndStg_WID      ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxRankMuxDelay_2ndStg_MSK      (0x03000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxRankMuxDelay_2ndStg_MIN      (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxRankMuxDelay_2ndStg_MAX      (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxRankMuxDelay_2ndStg_DEF      (0x00000003)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxRankMuxDelay_2ndStg_HSH      (0x023000F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_OFF           (26)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_WID           ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_MSK           (0x0C000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_MAX           (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_HSH           (0x023400F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_OFF          (28)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_WID          ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_MSK          (0xF0000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_MIN          (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_MAX          (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_HSH          (0x043800F4)

#define DATA0CH0_CR_DDRCRDATACONTROL3_A0_REG                           (0x000000F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_A0_OFF                   ( 0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_A0_WID                   ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_A0_MSK                   (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_A0_MIN                   (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_A0_MAX                   (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_A0_DEF                   (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Gear1_A0_HSH                   (0x010000F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_A0_OFF         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_A0_WID         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_A0_MSK         (0x00000002)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_A0_MIN         (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_A0_MAX         (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_A0_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefBypassVssHi_A0_HSH         (0x010200F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_A0_OFF         ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_A0_WID         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_A0_MSK         (0x00000004)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_A0_MIN         (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_A0_MAX         (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_A0_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPwrMuxSelVdd2_A0_HSH         (0x010400F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_A0_OFF       ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_A0_WID       ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_A0_MSK       (0x00000008)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_A0_MIN       (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_A0_MAX       (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_A0_DEF       (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_VrefPwrMuxSelVdd2_A0_HSH       (0x010600F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_A0_OFF           ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_A0_WID           ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_A0_MSK           (0x00000030)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_A0_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_A0_MAX           (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_A0_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALTailCtrl_A0_HSH           (0x020800F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_A0_OFF              ( 6)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_A0_WID              ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_A0_MSK              (0x000001C0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_A0_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_A0_MAX              (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_A0_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_wrpreamble_A0_HSH              (0x030C00F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_A0_OFF         ( 9)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_A0_WID         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_A0_MSK         (0x00000200)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_A0_MIN         (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_A0_MAX         (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_A0_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxSALDFEOvrdSel_A0_HSH         (0x011200F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_A0_OFF               (10)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_A0_WID               ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_A0_MSK               (0x00000400)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_A0_MIN               (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_A0_MAX               (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_A0_DEF               (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiEnable_A0_HSH               (0x011400F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_A0_OFF                 (11)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_A0_WID                 ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_A0_MSK                 (0x00000800)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_A0_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_A0_MAX                 (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_A0_DEF                 (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DbiMode_A0_HSH                 (0x011600F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_A0_OFF     (12)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_A0_WID     ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_A0_MSK     (0x00001000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_A0_MIN     (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_A0_MAX     (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_A0_DEF     (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_QualifySdlWithRcvEn_A0_HSH     (0x011800F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_A0_OFF                (13)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_A0_WID                ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_A0_MSK                (0x00006000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_A0_MIN                (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_A0_MAX                (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_A0_DEF                (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_rxfoldcs_A0_HSH                (0x021A00F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_A0_OFF        (15)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_A0_WID        ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_A0_MSK        (0x00008000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_A0_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_A0_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_A0_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_dqspadmuxselvdd2_A0_HSH        (0x011E00F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_A0_OFF (16)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_A0_WID ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_A0_MSK (0x00030000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_A0_MAX (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_A0_DEF (0x00000003)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxEq_RankMuxDelay_offset_A0_HSH (0x022000F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_A0_OFF (18)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_A0_WID ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_A0_MSK (0x000C0000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_A0_MAX (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_A0_DEF (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxPerbit_RankMuxDelay_offset_A0_HSH (0x022400F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare1_A0_OFF                  (20)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare1_A0_WID                  ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare1_A0_MSK                  (0x00700000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare1_A0_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare1_A0_MAX                  (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare1_A0_DEF                  (0x00000002)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare1_A0_HSH                  (0x032800F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_A0_OFF            (23)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_A0_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_A0_MSK            (0x00800000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_A0_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_A0_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_A0_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_DisableTxDqs_A0_HSH            (0x012E00F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare2_A0_OFF                  (24)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare2_A0_WID                  ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare2_A0_MSK                  (0x03000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare2_A0_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare2_A0_MAX                  (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare2_A0_DEF                  (0x00000002)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_Spare2_A0_HSH                  (0x023000F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_A0_OFF        (26)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_A0_WID        ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_A0_MSK        (0x0C000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_A0_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_A0_MAX        (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_A0_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_RxPBDCalibration_A0_HSH        (0x023400F4)

  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_A0_OFF       (28)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_A0_WID       ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_A0_MSK       (0xF0000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_A0_MIN       (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_A0_MAX       (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_A0_DEF       (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_A0_HSH       (0x043800F4)

#define DATA0CH0_CR_DDRCRDATACONTROL4_REG                              (0x000000F8)

  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank0_OFF                  ( 0)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank0_WID                  ( 8)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank0_MSK                  (0x000000FF)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank0_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank0_MAX                  (255) // 0x000000FF
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank0_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank0_HSH                  (0x080000F8)

  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank1_OFF                  ( 8)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank1_WID                  ( 8)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank1_MSK                  (0x0000FF00)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank1_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank1_MAX                  (255) // 0x000000FF
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank1_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank1_HSH                  (0x081000F8)

  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank2_OFF                  (16)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank2_WID                  ( 8)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank2_MSK                  (0x00FF0000)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank2_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank2_MAX                  (255) // 0x000000FF
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank2_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank2_HSH                  (0x082000F8)

  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank3_OFF                  (24)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank3_WID                  ( 8)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank3_MSK                  (0xFF000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank3_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank3_MAX                  (255) // 0x000000FF
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank3_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL4_RxEqRank3_HSH                  (0x083000F8)

#define DATA0CH0_CR_DDRCRDATACONTROL5_REG                              (0x000000FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPUpPreDrvVccddq_OFF        ( 0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPUpPreDrvVccddq_WID        ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPUpPreDrvVccddq_MSK        (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPUpPreDrvVccddq_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPUpPreDrvVccddq_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPUpPreDrvVccddq_DEF        (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPUpPreDrvVccddq_HSH        (0x010000FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxBypassVssHi_OFF              ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxBypassVssHi_WID              ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxBypassVssHi_MSK              (0x00000002)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxBypassVssHi_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxBypassVssHi_MAX              (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxBypassVssHi_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxBypassVssHi_HSH              (0x010200FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_DataInvertNibble_OFF           ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DataInvertNibble_WID           ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DataInvertNibble_MSK           (0x0000000C)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DataInvertNibble_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DataInvertNibble_MAX           (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DataInvertNibble_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DataInvertNibble_HSH           (0x020400FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxPiOn_OFF                     ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxPiOn_WID                     ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxPiOn_MSK                     (0x00000010)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxPiOn_MIN                     (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxPiOn_MAX                     (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxPiOn_DEF                     (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxPiOn_HSH                     (0x010800FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPDnPreDrvVccddq_OFF        ( 5)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPDnPreDrvVccddq_WID        ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPDnPreDrvVccddq_MSK        (0x00000020)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPDnPreDrvVccddq_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPDnPreDrvVccddq_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPDnPreDrvVccddq_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_TxDqPDnPreDrvVccddq_HSH        (0x010A00FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasBypassVsxHi_OFF            ( 6)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasBypassVsxHi_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasBypassVsxHi_MSK            (0x00000040)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasBypassVsxHi_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasBypassVsxHi_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasBypassVsxHi_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasBypassVsxHi_HSH            (0x010C00FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasRloadVref_OFF              ( 7)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasRloadVref_WID              ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasRloadVref_MSK              (0x00000380)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasRloadVref_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasRloadVref_MAX              (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasRloadVref_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasRloadVref_HSH              (0x030E00FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasIrefAdj_OFF                (10)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasIrefAdj_WID                ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasIrefAdj_MSK                (0x00003C00)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasIrefAdj_MIN                (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasIrefAdj_MAX                (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasIrefAdj_DEF                (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasIrefAdj_HSH                (0x041400FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasPwrMuxSelVdd2_OFF          (14)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasPwrMuxSelVdd2_WID          ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasPwrMuxSelVdd2_MSK          (0x00004000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasPwrMuxSelVdd2_MIN          (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasPwrMuxSelVdd2_MAX          (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasPwrMuxSelVdd2_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasPwrMuxSelVdd2_HSH          (0x011C00FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasCasAdj_OFF                 (15)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasCasAdj_WID                 ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasCasAdj_MSK                 (0x00018000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasCasAdj_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasCasAdj_MAX                 (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasCasAdj_DEF                 (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_BiasCasAdj_HSH                 (0x021E00FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_ODTSingleSegEn_OFF             (17)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_ODTSingleSegEn_WID             ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_ODTSingleSegEn_MSK             (0x00020000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_ODTSingleSegEn_MIN             (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_ODTSingleSegEn_MAX             (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL5_ODTSingleSegEn_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_ODTSingleSegEn_HSH             (0x012200FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_DqsOdtCompOffset_OFF           (18)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DqsOdtCompOffset_WID           ( 5)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DqsOdtCompOffset_MSK           (0x007C0000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DqsOdtCompOffset_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DqsOdtCompOffset_MAX           (31) // 0x0000001F
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DqsOdtCompOffset_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_DqsOdtCompOffset_HSH           (0x052400FC)

  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxVref_OFF                     (23)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxVref_WID                     ( 9)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxVref_MSK                     (0xFF800000)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxVref_MIN                     (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxVref_MAX                     (511) // 0x000001FF
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxVref_DEF                     (0x000000C0)
  #define DATA0CH0_CR_DDRCRDATACONTROL5_RxVref_HSH                     (0x092E00FC)

#define DATA0CH0_CR_DDRCRDATACONTROL6_REG                              (0x00000100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdllbwctrl_OFF                 ( 0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdllbwctrl_WID                 ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdllbwctrl_MSK                 (0x0000000F)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdllbwctrl_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdllbwctrl_MAX                 (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdllbwctrl_DEF                 (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdllbwctrl_HSH                 (0x04000100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_OFF                  ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_WID                  ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_MSK                  (0x000000F0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_MAX                  (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_HSH                  (0x04080100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0picb_OFF                   ( 8)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0picb_WID                   ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0picb_MSK                   (0x00000F00)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0picb_MIN                   (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0picb_MAX                   (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0picb_DEF                   (0x00000002)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0picb_HSH                   (0x04100100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0bwctrl_OFF                 (12)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0bwctrl_WID                 ( 4)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0bwctrl_MSK                 (0x0000F000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0bwctrl_MIN                 (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0bwctrl_MAX                 (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0bwctrl_DEF                 (0x00000002)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_rxd0bwctrl_HSH                 (0x04180100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_UseDefaultRdPtrCalc_OFF        (16)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_UseDefaultRdPtrCalc_WID        ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_UseDefaultRdPtrCalc_MSK        (0x00010000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_UseDefaultRdPtrCalc_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_UseDefaultRdPtrCalc_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL6_UseDefaultRdPtrCalc_DEF        (0x00000001)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_UseDefaultRdPtrCalc_HSH        (0x01200100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_RstNumPre_OFF                  (17)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RstNumPre_WID                  ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RstNumPre_MSK                  (0x000E0000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RstNumPre_MIN                  (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RstNumPre_MAX                  (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RstNumPre_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RstNumPre_HSH                  (0x03220100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_PassRcvenOnDqsFall_OFF         (20)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_PassRcvenOnDqsFall_WID         ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_PassRcvenOnDqsFall_MSK         (0x00100000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_PassRcvenOnDqsFall_MIN         (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_PassRcvenOnDqsFall_MAX         (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL6_PassRcvenOnDqsFall_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_PassRcvenOnDqsFall_HSH         (0x01280100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_RXTogglePreAmble_OFF           (21)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RXTogglePreAmble_WID           ( 2)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RXTogglePreAmble_MSK           (0x00600000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RXTogglePreAmble_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RXTogglePreAmble_MAX           (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RXTogglePreAmble_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RXTogglePreAmble_HSH           (0x022A0100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxSALDFEOvrdSel_OFF            (23)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxSALDFEOvrdSel_WID            ( 1)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxSALDFEOvrdSel_MSK            (0x00800000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxSALDFEOvrdSel_MIN            (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxSALDFEOvrdSel_MAX            (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxSALDFEOvrdSel_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxSALDFEOvrdSel_HSH            (0x012E0100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_RcvEnWaveShape_OFF             (24)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RcvEnWaveShape_WID             ( 3)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RcvEnWaveShape_MSK             (0x07000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RcvEnWaveShape_MIN             (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RcvEnWaveShape_MAX             (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RcvEnWaveShape_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RcvEnWaveShape_HSH             (0x03300100)

  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxReadPointer_OFF              (27)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxReadPointer_WID              ( 5)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxReadPointer_MSK              (0xF8000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxReadPointer_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxReadPointer_MAX              (31) // 0x0000001F
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxReadPointer_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATACONTROL6_RxReadPointer_HSH              (0x05360100)

#define DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG                               (0x00000104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_OFF             ( 0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_WID             (11)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_MSK             (0x000007FF)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_MIN             (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_MAX             (2047) // 0x000007FF
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_HSH             (0x0B000104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_OFF               (11)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_WID               (11)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_MSK               (0x003FF800)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_MIN               (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_MAX               (2047) // 0x000007FF
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_DEF               (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_HSH               (0x0B160104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_OFF           (22)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_WID           ( 1)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_MSK           (0x00400000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_MIN           (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_MAX           (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_HSH           (0x012C0104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_OFF            (23)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_WID            ( 2)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_MSK            (0x01800000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_MIN            (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_MAX            (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_HSH            (0x022E0104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_OFF   (25)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_WID   ( 4)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_MSK   (0x1E000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_MIN   (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_MAX   (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_DEF   (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_HSH   (0x04320104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_OFF                       (29)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_WID                       ( 3)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_MSK                       (0xE0000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_MIN                       (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_MAX                       (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_DEF                       (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_HSH                       (0x033A0104)

#define DATA0CH0_CR_DDRCRCMDBUSTRAIN_P0_REG                            (0x00000104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_P0_OFF          ( 0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_P0_WID          (11)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_P0_MSK          (0x000007FF)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_P0_MIN          (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_P0_MAX          (2047) // 0x000007FF
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_P0_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdModeEn_P0_HSH          (0x0B000104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_P0_OFF            (11)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_P0_WID            (11)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_P0_MSK            (0x003FF800)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_P0_MIN            (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_P0_MAX            (2047) // 0x000007FF
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_P0_DEF            (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrDqOvrdData_P0_HSH            (0x0B160104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_P0_OFF        (22)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_P0_WID        ( 1)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_P0_MSK        (0x00400000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_P0_MIN        (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_P0_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_P0_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DDRCrDqsMaskValue_P0_HSH        (0x012C0104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_P0_OFF         (23)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_P0_WID         ( 2)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_P0_MSK         (0x01800000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_P0_MIN         (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_P0_MAX         (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_P0_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRNumOfPulses_P0_HSH         (0x022E0104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_P0_OFF (25)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_P0_WID ( 4)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_P0_MSK (0x1E000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_P0_MIN (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_P0_MAX (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_P0_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRMaskCntPulseNumStart_P0_HSH (0x04320104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRWrPostamble_P0_OFF         (29)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRWrPostamble_P0_WID         ( 1)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRWrPostamble_P0_MSK         (0x20000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRWrPostamble_P0_MIN         (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRWrPostamble_P0_MAX         (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRWrPostamble_P0_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_DdrCRWrPostamble_P0_HSH         (0x013A0104)

  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_P0_OFF                    (30)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_P0_WID                    ( 2)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_P0_MSK                    (0xC0000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_P0_MIN                    (0)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_P0_MAX                    (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_P0_DEF                    (0x00000000)
  #define DATA0CH0_CR_DDRCRCMDBUSTRAIN_spare_P0_HSH                    (0x023C0104)

#define DATA0CH0_CR_DCCFSMCONTROL_REG                                  (0x00000108)

  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_OFF                         ( 0)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_WID                         ( 2)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_MSK                         (0x00000003)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_MIN                         (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_MAX                         (3) // 0x00000003
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_DEF                         (0x00000003)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_HSH                         (0x02000108)

  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_OFF                         ( 2)
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_WID                         (10)
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_MSK                         (0x00000FFC)
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_MIN                         (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_MAX                         (1023) // 0x000003FF
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_DEF                         (0x000003FF)
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_HSH                         (0x0A040108)

  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_OFF                        (12)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_WID                        ( 2)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_MSK                        (0x00003000)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_MIN                        (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_MAX                        (3) // 0x00000003
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_DEF                        (0x00000002)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_HSH                        (0x02180108)

  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_OFF                     (14)
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_WID                     ( 5)
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_MSK                     (0x0007C000)
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_MIN                     (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_MAX                     (31) // 0x0000001F
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_HSH                     (0x051C0108)

  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_OFF                    (19)
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_WID                    ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_MSK                    (0x00080000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_MIN                    (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_MAX                    (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_DEF                    (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_HSH                    (0x01260108)

  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_OFF                         (20)
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_WID                         ( 3)
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_MSK                         (0x00700000)
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_MIN                         (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_MAX                         (7) // 0x00000007
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_DEF                         (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_HSH                         (0x03280108)

  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_OFF                     (23)
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_WID                     ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_MSK                     (0x00800000)
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_MIN                     (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_MAX                     (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_DEF                     (0x00000001)
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_HSH                     (0x012E0108)

  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_OFF                      (24)
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_WID                      ( 2)
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_MSK                      (0x03000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_MIN                      (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_MAX                      (3) // 0x00000003
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_DEF                      (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_HSH                      (0x02300108)

  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_OFF                    (26)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_WID                    ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_MSK                    (0x04000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_MIN                    (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_MAX                    (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_DEF                    (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_HSH                    (0x01340108)

  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_OFF                     (27)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_WID                     ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_MSK                     (0x08000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_MIN                     (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_MAX                     (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_HSH                     (0x01360108)

  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_OFF                  (28)
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_WID                  ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_MSK                  (0x10000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_MIN                  (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_MAX                  (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_DEF                  (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_HSH                  (0x01380108)

  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_OFF                           (29)
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_WID                           ( 3)
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_MSK                           (0xE0000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_MIN                           (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_MAX                           (7) // 0x00000007
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_DEF                           (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_HSH                           (0x033A0108)

#define DATA0CH0_CR_DCCFSMCONTROL_P0_REG                               (0x00000108)

  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_P0_OFF                      ( 0)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_P0_WID                      ( 2)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_P0_MSK                      (0x00000003)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_P0_MIN                      (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_P0_MAX                      (3) // 0x00000003
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_P0_DEF                      (0x00000003)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankEn_P0_HSH                      (0x02000108)

  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_P0_OFF                      ( 2)
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_P0_WID                      (10)
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_P0_MSK                      (0x00000FFC)
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_P0_MIN                      (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_P0_MAX                      (1023) // 0x000003FF
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_P0_DEF                      (0x000003FF)
  #define DATA0CH0_CR_DCCFSMCONTROL_LaneEn_P0_HSH                      (0x0A040108)

  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_P0_OFF                     (12)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_P0_WID                     ( 2)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_P0_MSK                     (0x00003000)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_P0_MIN                     (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_P0_MAX                     (3) // 0x00000003
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_P0_DEF                     (0x00000002)
  #define DATA0CH0_CR_DCCFSMCONTROL_RankMap_P0_HSH                     (0x02180108)

  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_P0_OFF                  (14)
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_P0_WID                  ( 5)
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_P0_MSK                  (0x0007C000)
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_P0_MIN                  (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_P0_MAX                  (31) // 0x0000001F
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_P0_DEF                  (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_DccSamples_P0_HSH                  (0x051C0108)

  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_P0_OFF                 (19)
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_P0_WID                 ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_P0_MSK                 (0x00080000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_P0_MIN                 (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_P0_MAX                 (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_P0_DEF                 (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SaveFullDcc_P0_HSH                 (0x01260108)

  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_P0_OFF                      (20)
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_P0_WID                      ( 3)
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_P0_MSK                      (0x00700000)
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_P0_MIN                      (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_P0_MAX                      (7) // 0x00000007
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_P0_DEF                      (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_RORank_P0_HSH                      (0x03280108)

  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_P0_OFF                  (23)
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_P0_WID                  ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_P0_MSK                  (0x00800000)
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_P0_MIN                  (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_P0_MAX                  (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_P0_DEF                  (0x00000001)
  #define DATA0CH0_CR_DCCFSMCONTROL_EnRankOvrd_P0_HSH                  (0x012E0108)

  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_P0_OFF                   (24)
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_P0_WID                   ( 2)
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_P0_MSK                   (0x03000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_P0_MIN                   (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_P0_MAX                   (3) // 0x00000003
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_P0_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_MeasPoint_P0_HSH                   (0x02300108)

  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_P0_OFF                 (26)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_P0_WID                 ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_P0_MSK                 (0x04000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_P0_MIN                 (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_P0_MAX                 (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_P0_DEF                 (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipCRWrite_P0_HSH                 (0x01340108)

  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_P0_OFF                  (27)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_P0_WID                  ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_P0_MSK                  (0x08000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_P0_MIN                  (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_P0_MAX                  (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_P0_DEF                  (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_SkipUpdate_P0_HSH                  (0x01360108)

  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_P0_OFF               (28)
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_P0_WID               ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_P0_MSK               (0x10000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_P0_MIN               (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_P0_MAX               (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_P0_DEF               (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_WaitForUpdate_P0_HSH               (0x01380108)

  #define DATA0CH0_CR_DCCFSMCONTROL_Restore4Ranks_P0_OFF               (29)
  #define DATA0CH0_CR_DCCFSMCONTROL_Restore4Ranks_P0_WID               ( 1)
  #define DATA0CH0_CR_DCCFSMCONTROL_Restore4Ranks_P0_MSK               (0x20000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_Restore4Ranks_P0_MIN               (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_Restore4Ranks_P0_MAX               (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMCONTROL_Restore4Ranks_P0_DEF               (0x00000001)
  #define DATA0CH0_CR_DCCFSMCONTROL_Restore4Ranks_P0_HSH               (0x013A0108)

  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_P0_OFF                        (30)
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_P0_WID                        ( 2)
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_P0_MSK                        (0xC0000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_P0_MIN                        (0)
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_P0_MAX                        (3) // 0x00000003
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_P0_DEF                        (0x00000000)
  #define DATA0CH0_CR_DCCFSMCONTROL_rsvd_P0_HSH                        (0x023C0108)

#define DATA0CH0_CR_DCCCALCCONTROL_REG                                 (0x0000010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_DccStepSize_OFF                   ( 0)
  #define DATA0CH0_CR_DCCCALCCONTROL_DccStepSize_WID                   ( 5)
  #define DATA0CH0_CR_DCCCALCCONTROL_DccStepSize_MSK                   (0x0000001F)
  #define DATA0CH0_CR_DCCCALCCONTROL_DccStepSize_MIN                   (0)
  #define DATA0CH0_CR_DCCCALCCONTROL_DccStepSize_MAX                   (31) // 0x0000001F
  #define DATA0CH0_CR_DCCCALCCONTROL_DccStepSize_DEF                   (0x00000010)
  #define DATA0CH0_CR_DCCCALCCONTROL_DccStepSize_HSH                   (0x0500010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR0_OFF                    ( 5)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR0_WID                    ( 4)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR0_MSK                    (0x000001E0)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR0_MIN                    (-8)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR0_MAX                    (7) // 0x00000007
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR0_DEF                    (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR0_HSH                    (0x840A010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR1_OFF                    ( 9)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR1_WID                    ( 4)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR1_MSK                    (0x00001E00)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR1_MIN                    (-8)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR1_MAX                    (7) // 0x00000007
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR1_DEF                    (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqTargetR1_HSH                    (0x8412010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR0_OFF                   (13)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR0_WID                   ( 4)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR0_MSK                   (0x0001E000)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR0_MIN                   (-8)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR0_MAX                   (7) // 0x00000007
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR0_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR0_HSH                   (0x841A010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR1_OFF                   (17)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR1_WID                   ( 4)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR1_MSK                   (0x001E0000)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR1_MIN                   (-8)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR1_MAX                   (7) // 0x00000007
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR1_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_DqsTargetR1_HSH                   (0x8422010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeLane_OFF              (21)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeLane_WID              ( 4)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeLane_MSK              (0x01E00000)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeLane_MIN              (0)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeLane_MAX              (15) // 0x0000000F
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeLane_DEF              (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeLane_HSH              (0x042A010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeMax_OFF               (25)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeMax_WID               ( 1)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeMax_MSK               (0x02000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeMax_MIN               (0)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeMax_MAX               (1) // 0x00000001
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeMax_DEF               (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeMax_HSH               (0x0132010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeRank_OFF              (26)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeRank_WID              ( 1)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeRank_MSK              (0x04000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeRank_MIN              (0)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeRank_MAX              (1) // 0x00000001
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeRank_DEF              (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_TrackExtremeRank_HSH              (0x0134010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_LargeChange_OFF                   (27)
  #define DATA0CH0_CR_DCCCALCCONTROL_LargeChange_WID                   ( 2)
  #define DATA0CH0_CR_DCCCALCCONTROL_LargeChange_MSK                   (0x18000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_LargeChange_MIN                   (0)
  #define DATA0CH0_CR_DCCCALCCONTROL_LargeChange_MAX                   (3) // 0x00000003
  #define DATA0CH0_CR_DCCCALCCONTROL_LargeChange_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_LargeChange_HSH                   (0x0236010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_WrLUTDq0_OFF                      (29)
  #define DATA0CH0_CR_DCCCALCCONTROL_WrLUTDq0_WID                      ( 1)
  #define DATA0CH0_CR_DCCCALCCONTROL_WrLUTDq0_MSK                      (0x20000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_WrLUTDq0_MIN                      (0)
  #define DATA0CH0_CR_DCCCALCCONTROL_WrLUTDq0_MAX                      (1) // 0x00000001
  #define DATA0CH0_CR_DCCCALCCONTROL_WrLUTDq0_DEF                      (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_WrLUTDq0_HSH                      (0x013A010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_Dcc2xStep_OFF                     (30)
  #define DATA0CH0_CR_DCCCALCCONTROL_Dcc2xStep_WID                     ( 1)
  #define DATA0CH0_CR_DCCCALCCONTROL_Dcc2xStep_MSK                     (0x40000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_Dcc2xStep_MIN                     (0)
  #define DATA0CH0_CR_DCCCALCCONTROL_Dcc2xStep_MAX                     (1) // 0x00000001
  #define DATA0CH0_CR_DCCCALCCONTROL_Dcc2xStep_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_Dcc2xStep_HSH                     (0x013C010C)

  #define DATA0CH0_CR_DCCCALCCONTROL_rsvd_OFF                          (31)
  #define DATA0CH0_CR_DCCCALCCONTROL_rsvd_WID                          ( 1)
  #define DATA0CH0_CR_DCCCALCCONTROL_rsvd_MSK                          (0x80000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_rsvd_MIN                          (0)
  #define DATA0CH0_CR_DCCCALCCONTROL_rsvd_MAX                          (1) // 0x00000001
  #define DATA0CH0_CR_DCCCALCCONTROL_rsvd_DEF                          (0x00000000)
  #define DATA0CH0_CR_DCCCALCCONTROL_rsvd_HSH                          (0x013E010C)

#define DATA0CH0_CR_DCCFSMSTATUS_REG                                   (0x00000110)

  #define DATA0CH0_CR_DCCFSMSTATUS_LaneDone_OFF                        ( 0)
  #define DATA0CH0_CR_DCCFSMSTATUS_LaneDone_WID                        (10)
  #define DATA0CH0_CR_DCCFSMSTATUS_LaneDone_MSK                        (0x000003FF)
  #define DATA0CH0_CR_DCCFSMSTATUS_LaneDone_MIN                        (0)
  #define DATA0CH0_CR_DCCFSMSTATUS_LaneDone_MAX                        (1023) // 0x000003FF
  #define DATA0CH0_CR_DCCFSMSTATUS_LaneDone_DEF                        (0x00000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_LaneDone_HSH                        (0x0A000110)

  #define DATA0CH0_CR_DCCFSMSTATUS_RankDone_OFF                        (10)
  #define DATA0CH0_CR_DCCFSMSTATUS_RankDone_WID                        ( 2)
  #define DATA0CH0_CR_DCCFSMSTATUS_RankDone_MSK                        (0x00000C00)
  #define DATA0CH0_CR_DCCFSMSTATUS_RankDone_MIN                        (0)
  #define DATA0CH0_CR_DCCFSMSTATUS_RankDone_MAX                        (3) // 0x00000003
  #define DATA0CH0_CR_DCCFSMSTATUS_RankDone_DEF                        (0x00000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_RankDone_HSH                        (0x02140110)

  #define DATA0CH0_CR_DCCFSMSTATUS_CalcState_OFF                       (12)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcState_WID                       ( 3)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcState_MSK                       (0x00007000)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcState_MIN                       (0)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcState_MAX                       (7) // 0x00000007
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcState_DEF                       (0x00000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcState_HSH                       (0x03180110)

  #define DATA0CH0_CR_DCCFSMSTATUS_CalcRank_OFF                        (15)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcRank_WID                        ( 2)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcRank_MSK                        (0x00018000)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcRank_MIN                        (0)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcRank_MAX                        (3) // 0x00000003
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcRank_DEF                        (0x00000002)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcRank_HSH                        (0x021E0110)

  #define DATA0CH0_CR_DCCFSMSTATUS_CalcLane_OFF                        (17)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcLane_WID                        ( 4)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcLane_MSK                        (0x001E0000)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcLane_MIN                        (0)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcLane_MAX                        (15) // 0x0000000F
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcLane_DEF                        (0x00000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_CalcLane_HSH                        (0x04220110)

  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateState_OFF                     (21)
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateState_WID                     ( 3)
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateState_MSK                     (0x00E00000)
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateState_MIN                     (0)
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateState_MAX                     (7) // 0x00000007
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateState_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateState_HSH                     (0x032A0110)

  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateRank_OFF                      (24)
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateRank_WID                      ( 2)
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateRank_MSK                      (0x03000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateRank_MIN                      (0)
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateRank_MAX                      (3) // 0x00000003
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateRank_DEF                      (0x00000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_UpdateRank_HSH                      (0x02300110)

  #define DATA0CH0_CR_DCCFSMSTATUS_LargeChange_OFF                     (26)
  #define DATA0CH0_CR_DCCFSMSTATUS_LargeChange_WID                     ( 1)
  #define DATA0CH0_CR_DCCFSMSTATUS_LargeChange_MSK                     (0x04000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_LargeChange_MIN                     (0)
  #define DATA0CH0_CR_DCCFSMSTATUS_LargeChange_MAX                     (1) // 0x00000001
  #define DATA0CH0_CR_DCCFSMSTATUS_LargeChange_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_LargeChange_HSH                     (0x01340110)

  #define DATA0CH0_CR_DCCFSMSTATUS_rsvd_OFF                            (27)
  #define DATA0CH0_CR_DCCFSMSTATUS_rsvd_WID                            ( 5)
  #define DATA0CH0_CR_DCCFSMSTATUS_rsvd_MSK                            (0xF8000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_rsvd_MIN                            (0)
  #define DATA0CH0_CR_DCCFSMSTATUS_rsvd_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCFSMSTATUS_rsvd_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCFSMSTATUS_rsvd_HSH                            (0x05360110)

#define DATA0CH0_CR_DCCLANESTATUS0_REG                                 (0x00000114)

  #define DATA0CH0_CR_DCCLANESTATUS0_Lane0Result_OFF                   ( 0)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane0Result_WID                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane0Result_MSK                   (0x000001FF)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane0Result_MIN                   (0)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane0Result_MAX                   (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane0Result_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane0Result_HSH                   (0x09000114)

  #define DATA0CH0_CR_DCCLANESTATUS0_Lane1Result_OFF                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane1Result_WID                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane1Result_MSK                   (0x0003FE00)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane1Result_MIN                   (0)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane1Result_MAX                   (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane1Result_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane1Result_HSH                   (0x09120114)

  #define DATA0CH0_CR_DCCLANESTATUS0_Lane2Result_OFF                   (18)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane2Result_WID                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane2Result_MSK                   (0x07FC0000)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane2Result_MIN                   (0)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane2Result_MAX                   (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane2Result_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS0_Lane2Result_HSH                   (0x09240114)

  #define DATA0CH0_CR_DCCLANESTATUS0_rsvd_OFF                          (27)
  #define DATA0CH0_CR_DCCLANESTATUS0_rsvd_WID                          ( 5)
  #define DATA0CH0_CR_DCCLANESTATUS0_rsvd_MSK                          (0xF8000000)
  #define DATA0CH0_CR_DCCLANESTATUS0_rsvd_MIN                          (0)
  #define DATA0CH0_CR_DCCLANESTATUS0_rsvd_MAX                          (31) // 0x0000001F
  #define DATA0CH0_CR_DCCLANESTATUS0_rsvd_DEF                          (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS0_rsvd_HSH                          (0x05360114)

#define DATA0CH0_CR_DCCLANESTATUS1_REG                                 (0x00000118)

  #define DATA0CH0_CR_DCCLANESTATUS1_Lane3Result_OFF                   ( 0)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane3Result_WID                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane3Result_MSK                   (0x000001FF)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane3Result_MIN                   (0)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane3Result_MAX                   (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane3Result_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane3Result_HSH                   (0x09000118)

  #define DATA0CH0_CR_DCCLANESTATUS1_Lane4Result_OFF                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane4Result_WID                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane4Result_MSK                   (0x0003FE00)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane4Result_MIN                   (0)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane4Result_MAX                   (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane4Result_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane4Result_HSH                   (0x09120118)

  #define DATA0CH0_CR_DCCLANESTATUS1_Lane5Result_OFF                   (18)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane5Result_WID                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane5Result_MSK                   (0x07FC0000)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane5Result_MIN                   (0)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane5Result_MAX                   (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane5Result_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS1_Lane5Result_HSH                   (0x09240118)

  #define DATA0CH0_CR_DCCLANESTATUS1_rsvd_OFF                          (27)
  #define DATA0CH0_CR_DCCLANESTATUS1_rsvd_WID                          ( 5)
  #define DATA0CH0_CR_DCCLANESTATUS1_rsvd_MSK                          (0xF8000000)
  #define DATA0CH0_CR_DCCLANESTATUS1_rsvd_MIN                          (0)
  #define DATA0CH0_CR_DCCLANESTATUS1_rsvd_MAX                          (31) // 0x0000001F
  #define DATA0CH0_CR_DCCLANESTATUS1_rsvd_DEF                          (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS1_rsvd_HSH                          (0x05360118)

#define DATA0CH0_CR_DCCLANESTATUS2_REG                                 (0x0000011C)

  #define DATA0CH0_CR_DCCLANESTATUS2_Lane6Result_OFF                   ( 0)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane6Result_WID                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane6Result_MSK                   (0x000001FF)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane6Result_MIN                   (0)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane6Result_MAX                   (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane6Result_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane6Result_HSH                   (0x0900011C)

  #define DATA0CH0_CR_DCCLANESTATUS2_Lane7Result_OFF                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane7Result_WID                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane7Result_MSK                   (0x0003FE00)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane7Result_MIN                   (0)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane7Result_MAX                   (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane7Result_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane7Result_HSH                   (0x0912011C)

  #define DATA0CH0_CR_DCCLANESTATUS2_Lane8Result_OFF                   (18)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane8Result_WID                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane8Result_MSK                   (0x07FC0000)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane8Result_MIN                   (0)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane8Result_MAX                   (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane8Result_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS2_Lane8Result_HSH                   (0x0924011C)

  #define DATA0CH0_CR_DCCLANESTATUS2_rsvd_OFF                          (27)
  #define DATA0CH0_CR_DCCLANESTATUS2_rsvd_WID                          ( 5)
  #define DATA0CH0_CR_DCCLANESTATUS2_rsvd_MSK                          (0xF8000000)
  #define DATA0CH0_CR_DCCLANESTATUS2_rsvd_MIN                          (0)
  #define DATA0CH0_CR_DCCLANESTATUS2_rsvd_MAX                          (31) // 0x0000001F
  #define DATA0CH0_CR_DCCLANESTATUS2_rsvd_DEF                          (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS2_rsvd_HSH                          (0x0536011C)

#define DATA0CH0_CR_DCCLANESTATUS3_REG                                 (0x00000120)

  #define DATA0CH0_CR_DCCLANESTATUS3_Lane9Result_OFF                   ( 0)
  #define DATA0CH0_CR_DCCLANESTATUS3_Lane9Result_WID                   ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS3_Lane9Result_MSK                   (0x000001FF)
  #define DATA0CH0_CR_DCCLANESTATUS3_Lane9Result_MIN                   (0)
  #define DATA0CH0_CR_DCCLANESTATUS3_Lane9Result_MAX                   (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS3_Lane9Result_DEF                   (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS3_Lane9Result_HSH                   (0x09000120)

  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeOffset_OFF                 ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeOffset_WID                 ( 7)
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeOffset_MSK                 (0x0000FE00)
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeOffset_MIN                 (0)
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeOffset_MAX                 (127) // 0x0000007F
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeOffset_DEF                 (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeOffset_HSH                 (0x07120120)

  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeCount_OFF                  (16)
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeCount_WID                  ( 9)
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeCount_MSK                  (0x01FF0000)
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeCount_MIN                  (0)
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeCount_MAX                  (511) // 0x000001FF
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeCount_DEF                  (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS3_ExtremeCount_HSH                  (0x09200120)

  #define DATA0CH0_CR_DCCLANESTATUS3_rsvd_OFF                          (25)
  #define DATA0CH0_CR_DCCLANESTATUS3_rsvd_WID                          ( 7)
  #define DATA0CH0_CR_DCCLANESTATUS3_rsvd_MSK                          (0xFE000000)
  #define DATA0CH0_CR_DCCLANESTATUS3_rsvd_MIN                          (0)
  #define DATA0CH0_CR_DCCLANESTATUS3_rsvd_MAX                          (127) // 0x0000007F
  #define DATA0CH0_CR_DCCLANESTATUS3_rsvd_DEF                          (0x00000000)
  #define DATA0CH0_CR_DCCLANESTATUS3_rsvd_HSH                          (0x07320120)

#define DATA0CH0_CR_DCCPILUT0_REG                                      (0x00000124)

  #define DATA0CH0_CR_DCCPILUT0_Fine0_OFF                              ( 0)
  #define DATA0CH0_CR_DCCPILUT0_Fine0_WID                              ( 6)
  #define DATA0CH0_CR_DCCPILUT0_Fine0_MSK                              (0x0000003F)
  #define DATA0CH0_CR_DCCPILUT0_Fine0_MIN                              (-32)
  #define DATA0CH0_CR_DCCPILUT0_Fine0_MAX                              (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT0_Fine0_DEF                              (0x00000000)
  #define DATA0CH0_CR_DCCPILUT0_Fine0_HSH                              (0x86000124)

  #define DATA0CH0_CR_DCCPILUT0_Fine1_OFF                              ( 6)
  #define DATA0CH0_CR_DCCPILUT0_Fine1_WID                              ( 6)
  #define DATA0CH0_CR_DCCPILUT0_Fine1_MSK                              (0x00000FC0)
  #define DATA0CH0_CR_DCCPILUT0_Fine1_MIN                              (-32)
  #define DATA0CH0_CR_DCCPILUT0_Fine1_MAX                              (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT0_Fine1_DEF                              (0x00000000)
  #define DATA0CH0_CR_DCCPILUT0_Fine1_HSH                              (0x860C0124)

  #define DATA0CH0_CR_DCCPILUT0_Fine2_OFF                              (12)
  #define DATA0CH0_CR_DCCPILUT0_Fine2_WID                              ( 6)
  #define DATA0CH0_CR_DCCPILUT0_Fine2_MSK                              (0x0003F000)
  #define DATA0CH0_CR_DCCPILUT0_Fine2_MIN                              (-32)
  #define DATA0CH0_CR_DCCPILUT0_Fine2_MAX                              (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT0_Fine2_DEF                              (0x00000000)
  #define DATA0CH0_CR_DCCPILUT0_Fine2_HSH                              (0x86180124)

  #define DATA0CH0_CR_DCCPILUT0_Fine3_OFF                              (18)
  #define DATA0CH0_CR_DCCPILUT0_Fine3_WID                              ( 6)
  #define DATA0CH0_CR_DCCPILUT0_Fine3_MSK                              (0x00FC0000)
  #define DATA0CH0_CR_DCCPILUT0_Fine3_MIN                              (-32)
  #define DATA0CH0_CR_DCCPILUT0_Fine3_MAX                              (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT0_Fine3_DEF                              (0x00000000)
  #define DATA0CH0_CR_DCCPILUT0_Fine3_HSH                              (0x86240124)

  #define DATA0CH0_CR_DCCPILUT0_Fine4_OFF                              (24)
  #define DATA0CH0_CR_DCCPILUT0_Fine4_WID                              ( 6)
  #define DATA0CH0_CR_DCCPILUT0_Fine4_MSK                              (0x3F000000)
  #define DATA0CH0_CR_DCCPILUT0_Fine4_MIN                              (-32)
  #define DATA0CH0_CR_DCCPILUT0_Fine4_MAX                              (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT0_Fine4_DEF                              (0x00000000)
  #define DATA0CH0_CR_DCCPILUT0_Fine4_HSH                              (0x86300124)

  #define DATA0CH0_CR_DCCPILUT0_rsvd_OFF                               (30)
  #define DATA0CH0_CR_DCCPILUT0_rsvd_WID                               ( 2)
  #define DATA0CH0_CR_DCCPILUT0_rsvd_MSK                               (0xC0000000)
  #define DATA0CH0_CR_DCCPILUT0_rsvd_MIN                               (0)
  #define DATA0CH0_CR_DCCPILUT0_rsvd_MAX                               (3) // 0x00000003
  #define DATA0CH0_CR_DCCPILUT0_rsvd_DEF                               (0x00000000)
  #define DATA0CH0_CR_DCCPILUT0_rsvd_HSH                               (0x023C0124)

#define DATA0CH0_CR_DCCPILUT1_REG                                      (0x00000128)

  #define DATA0CH0_CR_DCCPILUT1_Fine5_OFF                              ( 0)
  #define DATA0CH0_CR_DCCPILUT1_Fine5_WID                              ( 6)
  #define DATA0CH0_CR_DCCPILUT1_Fine5_MSK                              (0x0000003F)
  #define DATA0CH0_CR_DCCPILUT1_Fine5_MIN                              (-32)
  #define DATA0CH0_CR_DCCPILUT1_Fine5_MAX                              (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT1_Fine5_DEF                              (0x00000000)
  #define DATA0CH0_CR_DCCPILUT1_Fine5_HSH                              (0x86000128)

  #define DATA0CH0_CR_DCCPILUT1_Fine6_OFF                              ( 6)
  #define DATA0CH0_CR_DCCPILUT1_Fine6_WID                              ( 6)
  #define DATA0CH0_CR_DCCPILUT1_Fine6_MSK                              (0x00000FC0)
  #define DATA0CH0_CR_DCCPILUT1_Fine6_MIN                              (-32)
  #define DATA0CH0_CR_DCCPILUT1_Fine6_MAX                              (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT1_Fine6_DEF                              (0x00000000)
  #define DATA0CH0_CR_DCCPILUT1_Fine6_HSH                              (0x860C0128)

  #define DATA0CH0_CR_DCCPILUT1_Fine7_OFF                              (12)
  #define DATA0CH0_CR_DCCPILUT1_Fine7_WID                              ( 6)
  #define DATA0CH0_CR_DCCPILUT1_Fine7_MSK                              (0x0003F000)
  #define DATA0CH0_CR_DCCPILUT1_Fine7_MIN                              (-32)
  #define DATA0CH0_CR_DCCPILUT1_Fine7_MAX                              (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT1_Fine7_DEF                              (0x00000000)
  #define DATA0CH0_CR_DCCPILUT1_Fine7_HSH                              (0x86180128)

  #define DATA0CH0_CR_DCCPILUT1_rsvd_OFF                               (18)
  #define DATA0CH0_CR_DCCPILUT1_rsvd_WID                               (14)
  #define DATA0CH0_CR_DCCPILUT1_rsvd_MSK                               (0xFFFC0000)
  #define DATA0CH0_CR_DCCPILUT1_rsvd_MIN                               (0)
  #define DATA0CH0_CR_DCCPILUT1_rsvd_MAX                               (16383) // 0x00003FFF
  #define DATA0CH0_CR_DCCPILUT1_rsvd_DEF                               (0x00000000)
  #define DATA0CH0_CR_DCCPILUT1_rsvd_HSH                               (0x0E240128)

#define DATA0CH0_CR_DCCPILUT2_REG                                      (0x0000012C)

  #define DATA0CH0_CR_DCCPILUT2_Coarse0_OFF                            ( 0)
  #define DATA0CH0_CR_DCCPILUT2_Coarse0_WID                            ( 6)
  #define DATA0CH0_CR_DCCPILUT2_Coarse0_MSK                            (0x0000003F)
  #define DATA0CH0_CR_DCCPILUT2_Coarse0_MIN                            (-32)
  #define DATA0CH0_CR_DCCPILUT2_Coarse0_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT2_Coarse0_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCPILUT2_Coarse0_HSH                            (0x8600012C)

  #define DATA0CH0_CR_DCCPILUT2_Coarse1_OFF                            ( 6)
  #define DATA0CH0_CR_DCCPILUT2_Coarse1_WID                            ( 6)
  #define DATA0CH0_CR_DCCPILUT2_Coarse1_MSK                            (0x00000FC0)
  #define DATA0CH0_CR_DCCPILUT2_Coarse1_MIN                            (-32)
  #define DATA0CH0_CR_DCCPILUT2_Coarse1_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT2_Coarse1_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCPILUT2_Coarse1_HSH                            (0x860C012C)

  #define DATA0CH0_CR_DCCPILUT2_Coarse2_OFF                            (12)
  #define DATA0CH0_CR_DCCPILUT2_Coarse2_WID                            ( 6)
  #define DATA0CH0_CR_DCCPILUT2_Coarse2_MSK                            (0x0003F000)
  #define DATA0CH0_CR_DCCPILUT2_Coarse2_MIN                            (-32)
  #define DATA0CH0_CR_DCCPILUT2_Coarse2_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT2_Coarse2_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCPILUT2_Coarse2_HSH                            (0x8618012C)

  #define DATA0CH0_CR_DCCPILUT2_Coarse3_OFF                            (18)
  #define DATA0CH0_CR_DCCPILUT2_Coarse3_WID                            ( 6)
  #define DATA0CH0_CR_DCCPILUT2_Coarse3_MSK                            (0x00FC0000)
  #define DATA0CH0_CR_DCCPILUT2_Coarse3_MIN                            (-32)
  #define DATA0CH0_CR_DCCPILUT2_Coarse3_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT2_Coarse3_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCPILUT2_Coarse3_HSH                            (0x8624012C)

  #define DATA0CH0_CR_DCCPILUT2_Coarse4_OFF                            (24)
  #define DATA0CH0_CR_DCCPILUT2_Coarse4_WID                            ( 6)
  #define DATA0CH0_CR_DCCPILUT2_Coarse4_MSK                            (0x3F000000)
  #define DATA0CH0_CR_DCCPILUT2_Coarse4_MIN                            (-32)
  #define DATA0CH0_CR_DCCPILUT2_Coarse4_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT2_Coarse4_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCPILUT2_Coarse4_HSH                            (0x8630012C)

  #define DATA0CH0_CR_DCCPILUT2_rsvd_OFF                               (30)
  #define DATA0CH0_CR_DCCPILUT2_rsvd_WID                               ( 2)
  #define DATA0CH0_CR_DCCPILUT2_rsvd_MSK                               (0xC0000000)
  #define DATA0CH0_CR_DCCPILUT2_rsvd_MIN                               (0)
  #define DATA0CH0_CR_DCCPILUT2_rsvd_MAX                               (3) // 0x00000003
  #define DATA0CH0_CR_DCCPILUT2_rsvd_DEF                               (0x00000000)
  #define DATA0CH0_CR_DCCPILUT2_rsvd_HSH                               (0x023C012C)

#define DATA0CH0_CR_DCCPILUT3_REG                                      (0x00000130)

  #define DATA0CH0_CR_DCCPILUT3_Coarse5_OFF                            ( 0)
  #define DATA0CH0_CR_DCCPILUT3_Coarse5_WID                            ( 6)
  #define DATA0CH0_CR_DCCPILUT3_Coarse5_MSK                            (0x0000003F)
  #define DATA0CH0_CR_DCCPILUT3_Coarse5_MIN                            (-32)
  #define DATA0CH0_CR_DCCPILUT3_Coarse5_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT3_Coarse5_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCPILUT3_Coarse5_HSH                            (0x86000130)

  #define DATA0CH0_CR_DCCPILUT3_Coarse6_OFF                            ( 6)
  #define DATA0CH0_CR_DCCPILUT3_Coarse6_WID                            ( 6)
  #define DATA0CH0_CR_DCCPILUT3_Coarse6_MSK                            (0x00000FC0)
  #define DATA0CH0_CR_DCCPILUT3_Coarse6_MIN                            (-32)
  #define DATA0CH0_CR_DCCPILUT3_Coarse6_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT3_Coarse6_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCPILUT3_Coarse6_HSH                            (0x860C0130)

  #define DATA0CH0_CR_DCCPILUT3_Coarse7_OFF                            (12)
  #define DATA0CH0_CR_DCCPILUT3_Coarse7_WID                            ( 6)
  #define DATA0CH0_CR_DCCPILUT3_Coarse7_MSK                            (0x0003F000)
  #define DATA0CH0_CR_DCCPILUT3_Coarse7_MIN                            (-32)
  #define DATA0CH0_CR_DCCPILUT3_Coarse7_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT3_Coarse7_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCPILUT3_Coarse7_HSH                            (0x86180130)

  #define DATA0CH0_CR_DCCPILUT3_Coarse8_OFF                            (18)
  #define DATA0CH0_CR_DCCPILUT3_Coarse8_WID                            ( 6)
  #define DATA0CH0_CR_DCCPILUT3_Coarse8_MSK                            (0x00FC0000)
  #define DATA0CH0_CR_DCCPILUT3_Coarse8_MIN                            (-32)
  #define DATA0CH0_CR_DCCPILUT3_Coarse8_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT3_Coarse8_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCPILUT3_Coarse8_HSH                            (0x86240130)

  #define DATA0CH0_CR_DCCPILUT3_Coarse9_OFF                            (24)
  #define DATA0CH0_CR_DCCPILUT3_Coarse9_WID                            ( 6)
  #define DATA0CH0_CR_DCCPILUT3_Coarse9_MSK                            (0x3F000000)
  #define DATA0CH0_CR_DCCPILUT3_Coarse9_MIN                            (-32)
  #define DATA0CH0_CR_DCCPILUT3_Coarse9_MAX                            (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT3_Coarse9_DEF                            (0x00000000)
  #define DATA0CH0_CR_DCCPILUT3_Coarse9_HSH                            (0x86300130)

  #define DATA0CH0_CR_DCCPILUT3_rsvd_OFF                               (30)
  #define DATA0CH0_CR_DCCPILUT3_rsvd_WID                               ( 2)
  #define DATA0CH0_CR_DCCPILUT3_rsvd_MSK                               (0xC0000000)
  #define DATA0CH0_CR_DCCPILUT3_rsvd_MIN                               (0)
  #define DATA0CH0_CR_DCCPILUT3_rsvd_MAX                               (3) // 0x00000003
  #define DATA0CH0_CR_DCCPILUT3_rsvd_DEF                               (0x00000000)
  #define DATA0CH0_CR_DCCPILUT3_rsvd_HSH                               (0x023C0130)

#define DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG                           (0x00000134)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_OFF           ( 0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_WID           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_MSK           (0x0000003F)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_MAX           (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_DEF           (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_HSH           (0x06000134)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit1_OFF           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit1_WID           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit1_MSK           (0x00000FC0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit1_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit1_MAX           (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit1_DEF           (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit1_HSH           (0x060C0134)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit2_OFF           (12)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit2_WID           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit2_MSK           (0x0003F000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit2_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit2_MAX           (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit2_DEF           (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit2_HSH           (0x06180134)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit3_OFF           (18)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit3_WID           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit3_MSK           (0x00FC0000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit3_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit3_MAX           (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit3_DEF           (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit3_HSH           (0x06240134)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit4_OFF           (24)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit4_WID           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit4_MSK           (0x3F000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit4_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit4_MAX           (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit4_DEF           (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit4_HSH           (0x06300134)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_Spare_OFF                   (30)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_Spare_WID                   ( 2)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_Spare_MSK                   (0xC0000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_Spare_MIN                   (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_Spare_MAX                   (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_Spare_DEF                   (0x00000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL0_Spare_HSH                   (0x023C0134)

#define DATA0CH0_CR_DDRCRDATATCOCONTROL1_REG                           (0x00000138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_OFF           ( 0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_WID           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_MSK           (0x0000003F)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_MAX           (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_DEF           (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_HSH           (0x06000138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_OFF           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_WID           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_MSK           (0x00000FC0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_MAX           (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_DEF           (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_HSH           (0x060C0138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_OFF           (12)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_WID           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_MSK           (0x0003F000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_MAX           (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_DEF           (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_HSH           (0x06180138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_OFF              (18)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_WID              ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_MSK              (0x00FC0000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_MIN              (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_MAX              (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_HSH              (0x06240138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_TxVsxHiLeakerComp_OFF       (24)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_TxVsxHiLeakerComp_WID       ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_TxVsxHiLeakerComp_MSK       (0x3F000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_TxVsxHiLeakerComp_MIN       (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_TxVsxHiLeakerComp_MAX       (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_TxVsxHiLeakerComp_DEF       (0x00000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_TxVsxHiLeakerComp_HSH       (0x06300138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_OFF                   (30)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_WID                   ( 2)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_MSK                   (0xC0000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_MIN                   (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_MAX                   (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_DEF                   (0x00000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_HSH                   (0x023C0138)

#define DATA0CH0_CR_DDRCRDATATCOCONTROL1_A0_REG                        (0x00000138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_A0_OFF        ( 0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_A0_WID        ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_A0_MSK        (0x0000003F)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_A0_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_A0_MAX        (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_A0_DEF        (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_A0_HSH        (0x06000138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_A0_OFF        ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_A0_WID        ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_A0_MSK        (0x00000FC0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_A0_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_A0_MAX        (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_A0_DEF        (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_A0_HSH        (0x060C0138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_A0_OFF        (12)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_A0_WID        ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_A0_MSK        (0x0003F000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_A0_MIN        (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_A0_MAX        (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_A0_DEF        (0x00000020)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_A0_HSH        (0x06180138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_A0_OFF           (18)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_A0_WID           ( 6)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_A0_MSK           (0x00FC0000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_A0_MIN           (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_A0_MAX           (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_A0_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_DMITcoComp_A0_HSH           (0x06240138)

  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_A0_OFF                (24)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_A0_WID                ( 8)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_A0_MSK                (0xFF000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_A0_MIN                (0)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_A0_MAX                (255) // 0x000000FF
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_A0_DEF                (0x00000000)
  #define DATA0CH0_CR_DDRCRDATATCOCONTROL1_Spare_A0_HSH                (0x08300138)

#define DATA0CH0_CR_DCCPILUT4_REG                                      (0x0000013C)

  #define DATA0CH0_CR_DCCPILUT4_Coarse10_OFF                           ( 0)
  #define DATA0CH0_CR_DCCPILUT4_Coarse10_WID                           ( 6)
  #define DATA0CH0_CR_DCCPILUT4_Coarse10_MSK                           (0x0000003F)
  #define DATA0CH0_CR_DCCPILUT4_Coarse10_MIN                           (-32)
  #define DATA0CH0_CR_DCCPILUT4_Coarse10_MAX                           (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT4_Coarse10_DEF                           (0x00000000)
  #define DATA0CH0_CR_DCCPILUT4_Coarse10_HSH                           (0x8600013C)

  #define DATA0CH0_CR_DCCPILUT4_Coarse11_OFF                           ( 6)
  #define DATA0CH0_CR_DCCPILUT4_Coarse11_WID                           ( 6)
  #define DATA0CH0_CR_DCCPILUT4_Coarse11_MSK                           (0x00000FC0)
  #define DATA0CH0_CR_DCCPILUT4_Coarse11_MIN                           (-32)
  #define DATA0CH0_CR_DCCPILUT4_Coarse11_MAX                           (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT4_Coarse11_DEF                           (0x00000000)
  #define DATA0CH0_CR_DCCPILUT4_Coarse11_HSH                           (0x860C013C)

  #define DATA0CH0_CR_DCCPILUT4_Coarse12_OFF                           (12)
  #define DATA0CH0_CR_DCCPILUT4_Coarse12_WID                           ( 6)
  #define DATA0CH0_CR_DCCPILUT4_Coarse12_MSK                           (0x0003F000)
  #define DATA0CH0_CR_DCCPILUT4_Coarse12_MIN                           (-32)
  #define DATA0CH0_CR_DCCPILUT4_Coarse12_MAX                           (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT4_Coarse12_DEF                           (0x00000000)
  #define DATA0CH0_CR_DCCPILUT4_Coarse12_HSH                           (0x8618013C)

  #define DATA0CH0_CR_DCCPILUT4_Coarse13_OFF                           (18)
  #define DATA0CH0_CR_DCCPILUT4_Coarse13_WID                           ( 6)
  #define DATA0CH0_CR_DCCPILUT4_Coarse13_MSK                           (0x00FC0000)
  #define DATA0CH0_CR_DCCPILUT4_Coarse13_MIN                           (-32)
  #define DATA0CH0_CR_DCCPILUT4_Coarse13_MAX                           (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT4_Coarse13_DEF                           (0x00000000)
  #define DATA0CH0_CR_DCCPILUT4_Coarse13_HSH                           (0x8624013C)

  #define DATA0CH0_CR_DCCPILUT4_Coarse14_OFF                           (24)
  #define DATA0CH0_CR_DCCPILUT4_Coarse14_WID                           ( 6)
  #define DATA0CH0_CR_DCCPILUT4_Coarse14_MSK                           (0x3F000000)
  #define DATA0CH0_CR_DCCPILUT4_Coarse14_MIN                           (-32)
  #define DATA0CH0_CR_DCCPILUT4_Coarse14_MAX                           (31) // 0x0000001F
  #define DATA0CH0_CR_DCCPILUT4_Coarse14_DEF                           (0x00000000)
  #define DATA0CH0_CR_DCCPILUT4_Coarse14_HSH                           (0x8630013C)

  #define DATA0CH0_CR_DCCPILUT4_rsvd_OFF                               (30)
  #define DATA0CH0_CR_DCCPILUT4_rsvd_WID                               ( 1)
  #define DATA0CH0_CR_DCCPILUT4_rsvd_MSK                               (0x40000000)
  #define DATA0CH0_CR_DCCPILUT4_rsvd_MIN                               (0)
  #define DATA0CH0_CR_DCCPILUT4_rsvd_MAX                               (1) // 0x00000001
  #define DATA0CH0_CR_DCCPILUT4_rsvd_DEF                               (0x00000000)
  #define DATA0CH0_CR_DCCPILUT4_rsvd_HSH                               (0x013C013C)

  #define DATA0CH0_CR_DCCPILUT4_LUTHalfStep_OFF                        (31)
  #define DATA0CH0_CR_DCCPILUT4_LUTHalfStep_WID                        ( 1)
  #define DATA0CH0_CR_DCCPILUT4_LUTHalfStep_MSK                        (0x80000000)
  #define DATA0CH0_CR_DCCPILUT4_LUTHalfStep_MIN                        (0)
  #define DATA0CH0_CR_DCCPILUT4_LUTHalfStep_MAX                        (1) // 0x00000001
  #define DATA0CH0_CR_DCCPILUT4_LUTHalfStep_DEF                        (0x00000000)
  #define DATA0CH0_CR_DCCPILUT4_LUTHalfStep_HSH                        (0x013E013C)

#define DATA0CH0_CR_DCCLANETARGET_REG                                  (0x00000140)

  #define DATA0CH0_CR_DCCLANETARGET_TargetBit0_OFF                     ( 0)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit0_WID                     ( 4)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit0_MSK                     (0x0000000F)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit0_MIN                     (-8)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit0_MAX                     (7) // 0x00000007
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit0_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit0_HSH                     (0x84000140)

  #define DATA0CH0_CR_DCCLANETARGET_TargetBit1_OFF                     ( 4)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit1_WID                     ( 4)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit1_MSK                     (0x000000F0)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit1_MIN                     (-8)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit1_MAX                     (7) // 0x00000007
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit1_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit1_HSH                     (0x84080140)

  #define DATA0CH0_CR_DCCLANETARGET_TargetBit2_OFF                     ( 8)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit2_WID                     ( 4)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit2_MSK                     (0x00000F00)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit2_MIN                     (-8)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit2_MAX                     (7) // 0x00000007
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit2_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit2_HSH                     (0x84100140)

  #define DATA0CH0_CR_DCCLANETARGET_TargetBit3_OFF                     (12)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit3_WID                     ( 4)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit3_MSK                     (0x0000F000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit3_MIN                     (-8)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit3_MAX                     (7) // 0x00000007
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit3_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit3_HSH                     (0x84180140)

  #define DATA0CH0_CR_DCCLANETARGET_TargetBit4_OFF                     (16)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit4_WID                     ( 4)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit4_MSK                     (0x000F0000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit4_MIN                     (-8)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit4_MAX                     (7) // 0x00000007
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit4_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit4_HSH                     (0x84200140)

  #define DATA0CH0_CR_DCCLANETARGET_TargetBit5_OFF                     (20)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit5_WID                     ( 4)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit5_MSK                     (0x00F00000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit5_MIN                     (-8)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit5_MAX                     (7) // 0x00000007
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit5_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit5_HSH                     (0x84280140)

  #define DATA0CH0_CR_DCCLANETARGET_TargetBit6_OFF                     (24)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit6_WID                     ( 4)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit6_MSK                     (0x0F000000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit6_MIN                     (-8)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit6_MAX                     (7) // 0x00000007
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit6_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit6_HSH                     (0x84300140)

  #define DATA0CH0_CR_DCCLANETARGET_TargetBit7_OFF                     (28)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit7_WID                     ( 4)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit7_MSK                     (0xF0000000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit7_MIN                     (-8)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit7_MAX                     (7) // 0x00000007
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit7_DEF                     (0x00000000)
  #define DATA0CH0_CR_DCCLANETARGET_TargetBit7_HSH                     (0x84380140)

#define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG                   (0x00000144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_OFF ( 0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_MSK (0x00000007)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_HSH (0x03000144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_OFF ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_MSK (0x00000038)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_DEF (0x00000001)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_HSH (0x03060144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_OFF ( 6)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_MSK (0x000001C0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_DEF (0x00000002)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_HSH (0x030C0144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_OFF ( 9)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_MSK (0x00000E00)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_DEF (0x00000003)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_HSH (0x03120144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_OFF (12)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_MSK (0x00007000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_DEF (0x00000004)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_HSH (0x03180144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_OFF (15)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_MSK (0x00038000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_DEF (0x00000005)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_HSH (0x031E0144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_OFF (18)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_MSK (0x001C0000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_DEF (0x00000006)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_HSH (0x03240144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_OFF (21)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_MSK (0x00E00000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_DEF (0x00000007)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_HSH (0x032A0144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_OFF (24)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_WID ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_MSK (0x01000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_MAX (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_HSH (0x01300144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_OFF   (25)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_WID   ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_MSK   (0x02000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_MIN   (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_MAX   (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_DEF   (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_HSH   (0x01320144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_SerialMRROrder_OFF  (26)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_SerialMRROrder_WID  ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_SerialMRROrder_MSK  (0x04000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_SerialMRROrder_MIN  (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_SerialMRROrder_MAX  (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_SerialMRROrder_DEF  (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_SerialMRROrder_HSH  (0x01340144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataInvertNibble_OFF (27)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataInvertNibble_WID ( 2)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataInvertNibble_MSK (0x18000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataInvertNibble_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataInvertNibble_MAX (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataInvertNibble_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataInvertNibble_HSH (0x02360144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_OFF           (29)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_WID           ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_MSK           (0xE0000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_MIN           (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_MAX           (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_HSH           (0x033A0144)

#define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_A0_REG                (0x00000144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_A0_OFF ( 0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_A0_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_A0_MSK (0x00000007)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_A0_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_A0_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ0_A0_HSH (0x03000144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_A0_OFF ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_A0_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_A0_MSK (0x00000038)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_A0_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_A0_DEF (0x00000001)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ1_A0_HSH (0x03060144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_A0_OFF ( 6)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_A0_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_A0_MSK (0x000001C0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_A0_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_A0_DEF (0x00000002)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ2_A0_HSH (0x030C0144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_A0_OFF ( 9)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_A0_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_A0_MSK (0x00000E00)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_A0_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_A0_DEF (0x00000003)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ3_A0_HSH (0x03120144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_A0_OFF (12)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_A0_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_A0_MSK (0x00007000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_A0_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_A0_DEF (0x00000004)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ4_A0_HSH (0x03180144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_A0_OFF (15)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_A0_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_A0_MSK (0x00038000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_A0_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_A0_DEF (0x00000005)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ5_A0_HSH (0x031E0144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_A0_OFF (18)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_A0_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_A0_MSK (0x001C0000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_A0_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_A0_DEF (0x00000006)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ6_A0_HSH (0x03240144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_A0_OFF (21)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_A0_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_A0_MSK (0x00E00000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_A0_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_A0_DEF (0x00000007)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_DQ7_A0_HSH (0x032A0144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_A0_OFF (24)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_A0_WID ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_A0_MSK (0x01000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_A0_MAX (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_A0_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrain_ByteSel_A0_HSH (0x01300144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_A0_OFF (25)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_A0_WID ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_A0_MSK (0x02000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_A0_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_A0_MAX (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_A0_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_DataRetrainEn_A0_HSH (0x01320144)

  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_A0_OFF        (26)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_A0_WID        ( 6)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_A0_MSK        (0xFC000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_A0_MIN        (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_A0_MAX        (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_A0_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_Spare_A0_HSH        (0x06340144)

#define DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG                            (0x00000148)

  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_InitPiCode_OFF               ( 0)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_InitPiCode_WID               (10)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_InitPiCode_MSK               (0x000003FF)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_InitPiCode_MIN               (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_InitPiCode_MAX               (1023) // 0x000003FF
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_InitPiCode_DEF               (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_InitPiCode_HSH               (0x0A000148)

  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_DeltaPiCode_OFF              (10)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_DeltaPiCode_WID              ( 7)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_DeltaPiCode_MSK              (0x0001FC00)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_DeltaPiCode_MIN              (-64)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_DeltaPiCode_MAX              (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_DeltaPiCode_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_DeltaPiCode_HSH              (0x87140148)

  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_ROCount_OFF                  (17)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_ROCount_WID                  (15)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_ROCount_MSK                  (0xFFFE0000)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_ROCount_MIN                  (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_ROCount_MAX                  (32767) // 0x00007FFF
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_ROCount_DEF                  (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINRANK3_ROCount_HSH                  (0x0F220148)

#define DATA0CH0_CR_DDRCRWRRETRAINRANK2_REG                            (0x0000014C)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA0CH0_CR_DDRCRWRRETRAINRANK1_REG                            (0x00000150)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA0CH0_CR_DDRCRWRRETRAINRANK0_REG                            (0x00000154)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG                    (0x00000158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_InitTrain_OFF        ( 0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_InitTrain_WID        ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_InitTrain_MSK        (0x00000001)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_InitTrain_MIN        (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_InitTrain_MAX        (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_InitTrain_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_InitTrain_HSH        (0x01000158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_Duration_OFF         ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_Duration_WID         (10)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_Duration_MSK         (0x000007FE)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_Duration_MIN         (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_Duration_MAX         (1023) // 0x000003FF
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_Duration_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_Duration_HSH         (0x0A020158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_ResetStatus_OFF      (11)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_ResetStatus_WID      ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_ResetStatus_MSK      (0x00000800)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_ResetStatus_MIN      (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_ResetStatus_MAX      (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_ResetStatus_DEF      (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_ResetStatus_HSH      (0x01160158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeDelta_OFF (12)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeDelta_WID ( 3)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeDelta_MSK (0x00007000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeDelta_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeDelta_MAX (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeDelta_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeDelta_HSH (0x03180158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_UpdOnLargeChage_OFF  (15)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_UpdOnLargeChage_WID  ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_UpdOnLargeChage_MSK  (0x00008000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_UpdOnLargeChage_MIN  (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_UpdOnLargeChage_MAX  (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_UpdOnLargeChage_DEF  (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_UpdOnLargeChage_HSH  (0x011E0158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_StopOnLargeChange_OFF (16)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_StopOnLargeChange_WID ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_StopOnLargeChange_MSK (0x00010000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_StopOnLargeChange_MIN (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_StopOnLargeChange_MAX (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_StopOnLargeChange_DEF (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_StopOnLargeChange_HSH (0x01200158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R0Status_OFF         (17)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R0Status_WID         ( 2)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R0Status_MSK         (0x00060000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R0Status_MIN         (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R0Status_MAX         (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R0Status_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R0Status_HSH         (0x02220158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R1Status_OFF         (19)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R1Status_WID         ( 2)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R1Status_MSK         (0x00180000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R1Status_MIN         (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R1Status_MAX         (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R1Status_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R1Status_HSH         (0x02260158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R2Status_OFF         (21)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R2Status_WID         ( 2)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R2Status_MSK         (0x00600000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R2Status_MIN         (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R2Status_MAX         (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R2Status_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R2Status_HSH         (0x022A0158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R3Status_OFF         (23)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R3Status_WID         ( 2)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R3Status_MSK         (0x01800000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R3Status_MIN         (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R3Status_MAX         (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R3Status_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_R3Status_HSH         (0x022E0158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMStatus_OFF        (25)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMStatus_WID        ( 4)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMStatus_MSK        (0x1E000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMStatus_MIN        (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMStatus_MAX        (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMStatus_DEF        (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMStatus_HSH        (0x04320158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMRank_OFF          (29)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMRank_WID          ( 2)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMRank_MSK          (0x60000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMRank_MIN          (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMRank_MAX          (3) // 0x00000003
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMRank_DEF          (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_FSMRank_HSH          (0x023A0158)

  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeTrig_OFF  (31)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeTrig_WID  ( 1)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeTrig_MSK  (0x80000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeTrig_MIN  (0)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeTrig_MAX  (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeTrig_DEF  (0x00000000)
  #define DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_LargeChangeTrig_HSH  (0x013E0158)

#define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG                        (0x0000015C)

  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_RunTest_OFF              ( 0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_RunTest_WID              ( 1)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_RunTest_MSK              (0x00000001)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_RunTest_MIN              (0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_RunTest_MAX              (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_RunTest_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_RunTest_HSH              (0x0100015C)

  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_Param_OFF                ( 1)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_Param_WID                ( 3)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_Param_MSK                (0x0000000E)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_Param_MIN                (0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_Param_MAX                (7) // 0x00000007
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_Param_DEF                (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_Param_HSH                (0x0302015C)

  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinVal_OFF               ( 4)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinVal_WID               ( 7)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinVal_MSK               (0x000007F0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinVal_MIN               (0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinVal_MAX               (127) // 0x0000007F
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinVal_DEF               (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinVal_HSH               (0x0708015C)

  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MaxVal_OFF               (11)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MaxVal_WID               ( 7)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MaxVal_MSK               (0x0003F800)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MaxVal_MIN               (0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MaxVal_MAX               (127) // 0x0000007F
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MaxVal_DEF               (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MaxVal_HSH               (0x0716015C)

  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinWidth_OFF             (18)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinWidth_WID             ( 6)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinWidth_MSK             (0x00FC0000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinWidth_MIN             (0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinWidth_MAX             (63) // 0x0000003F
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinWidth_DEF             (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_MinWidth_HSH             (0x0624015C)

  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_CalcCenter_OFF           (24)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_CalcCenter_WID           ( 1)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_CalcCenter_MSK           (0x01000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_CalcCenter_MIN           (0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_CalcCenter_MAX           (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_CalcCenter_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_CalcCenter_HSH           (0x0130015C)

  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_IOLBCycles_OFF           (25)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_IOLBCycles_WID           ( 4)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_IOLBCycles_MSK           (0x1E000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_IOLBCycles_MIN           (0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_IOLBCycles_MAX           (15) // 0x0000000F
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_IOLBCycles_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_IOLBCycles_HSH           (0x0432015C)

  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_BurstIdleBurst_OFF       (29)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_BurstIdleBurst_WID       ( 1)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_BurstIdleBurst_MSK       (0x20000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_BurstIdleBurst_MIN       (0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_BurstIdleBurst_MAX       (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_BurstIdleBurst_DEF       (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_BurstIdleBurst_HSH       (0x013A015C)

  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_LaneResult_OFF           (30)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_LaneResult_WID           ( 1)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_LaneResult_MSK           (0x40000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_LaneResult_MIN           (0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_LaneResult_MAX           (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_LaneResult_DEF           (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_LaneResult_HSH           (0x013C015C)

  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_ForceOnRcvEn_OFF         (31)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_ForceOnRcvEn_WID         ( 1)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_ForceOnRcvEn_MSK         (0x80000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_ForceOnRcvEn_MIN         (0)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_ForceOnRcvEn_MAX         (1) // 0x00000001
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_ForceOnRcvEn_DEF         (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODECONTROL0_ForceOnRcvEn_HSH         (0x013E015C)

#define DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG                       (0x00000160)

  #define DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_result_OFF              ( 0)
  #define DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_result_WID              (32)
  #define DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_result_MSK              (0xFFFFFFFF)
  #define DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_result_MIN              (0)
  #define DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_result_MAX              (4294967295) // 0xFFFFFFFF
  #define DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_result_DEF              (0x00000000)
  #define DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_result_HSH              (0x20000160)

#define DATA0CH0_CR_DDRCRMARGINMODEDEBUGLSB0_REG                       (0x00000164)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA0CH1_CR_DDRDATADQRANK0LANE0_REG                            (0x00000200)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK0LANE1_REG                            (0x00000204)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK0LANE2_REG                            (0x00000208)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK0LANE3_REG                            (0x0000020C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK0LANE4_REG                            (0x00000210)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK0LANE5_REG                            (0x00000214)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK0LANE6_REG                            (0x00000218)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK0LANE7_REG                            (0x0000021C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK0LANE8_REG                            (0x00000220)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK1LANE0_REG                            (0x00000224)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK1LANE1_REG                            (0x00000228)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK1LANE2_REG                            (0x0000022C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK1LANE3_REG                            (0x00000230)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK1LANE4_REG                            (0x00000234)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK1LANE5_REG                            (0x00000238)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK1LANE6_REG                            (0x0000023C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK1LANE7_REG                            (0x00000240)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK1LANE8_REG                            (0x00000244)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK2LANE0_REG                            (0x00000248)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK2LANE1_REG                            (0x0000024C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK2LANE2_REG                            (0x00000250)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK2LANE3_REG                            (0x00000254)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK2LANE4_REG                            (0x00000258)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK2LANE5_REG                            (0x0000025C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK2LANE6_REG                            (0x00000260)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK2LANE7_REG                            (0x00000264)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK2LANE8_REG                            (0x00000268)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK3LANE0_REG                            (0x0000026C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK3LANE1_REG                            (0x00000270)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK3LANE2_REG                            (0x00000274)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK3LANE3_REG                            (0x00000278)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK3LANE4_REG                            (0x0000027C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK3LANE5_REG                            (0x00000280)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK3LANE6_REG                            (0x00000284)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK3LANE7_REG                            (0x00000288)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQRANK3LANE8_REG                            (0x0000028C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA0CH1_CR_DDRDATADQSRANK0_REG                                (0x0000029C)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA0CH1_CR_DDRDATADQSRANK1_REG                                (0x000002A0)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA0CH1_CR_DDRDATADQSRANK2_REG                                (0x000002A4)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA0CH1_CR_DDRDATADQSRANK3_REG                                (0x000002A8)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA0CH1_CR_RXCONTROL0RANK0_REG                                (0x000002AC)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA0CH1_CR_RXCONTROL0RANK1_REG                                (0x000002B0)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA0CH1_CR_RXCONTROL0RANK2_REG                                (0x000002B4)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA0CH1_CR_RXCONTROL0RANK3_REG                                (0x000002B8)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA0CH1_CR_TXCONTROL0RANK0_REG                                (0x000002BC)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA0CH1_CR_TXCONTROL0RANK1_REG                                (0x000002C0)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA0CH1_CR_TXCONTROL0RANK2_REG                                (0x000002C4)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA0CH1_CR_TXCONTROL0RANK3_REG                                (0x000002C8)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA0CH1_CR_RCOMPDATA0_REG                                     (0x000002CC)
//Duplicate of DATA0CH0_CR_RCOMPDATA0_REG

#define DATA0CH1_CR_RCOMPDATA1_REG                                     (0x000002D0)
//Duplicate of DATA0CH0_CR_RCOMPDATA1_REG

#define DATA0CH1_CR_DATACOMPVTT_REG                                    (0x000002D4)
//Duplicate of DATA0CH0_CR_DATACOMPVTT_REG

#define DATA0CH1_CR_DATATRAINFEEDBACK_REG                              (0x000002DC)
//Duplicate of DATA0CH0_CR_DATATRAINFEEDBACK_REG

#define DATA0CH1_CR_DDRCRDATAOFFSETCOMP_REG                            (0x000002E0)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG

#define DATA0CH1_CR_DDRCRDATAOFFSETTRAIN_REG                           (0x000002E4)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG

#define DATA0CH1_CR_DDRCRDATACONTROL0_REG                              (0x000002E8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL0_REG

#define DATA0CH1_CR_DDRCRDATACONTROL1_REG                              (0x000002EC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL1_REG

#define DATA0CH1_CR_DDRCRDATACONTROL2_REG                              (0x000002F0)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL2_REG

#define DATA0CH1_CR_DDRCRDATACONTROL3_REG                              (0x000002F4)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL3_REG

#define DATA0CH1_CR_DDRCRDATACONTROL4_REG                              (0x000002F8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL4_REG

#define DATA0CH1_CR_DDRCRDATACONTROL5_REG                              (0x000002FC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL5_REG

#define DATA0CH1_CR_DDRCRDATACONTROL6_REG                              (0x00000300)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL6_REG

#define DATA0CH1_CR_DDRCRCMDBUSTRAIN_REG                               (0x00000304)
//Duplicate of DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG

#define DATA0CH1_CR_DCCFSMCONTROL_REG                                  (0x00000308)
//Duplicate of DATA0CH0_CR_DCCFSMCONTROL_REG

#define DATA0CH1_CR_DCCCALCCONTROL_REG                                 (0x0000030C)
//Duplicate of DATA0CH0_CR_DCCCALCCONTROL_REG

#define DATA0CH1_CR_DCCFSMSTATUS_REG                                   (0x00000310)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define DATA0CH1_CR_DCCLANESTATUS0_REG                                 (0x00000314)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define DATA0CH1_CR_DCCLANESTATUS1_REG                                 (0x00000318)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define DATA0CH1_CR_DCCLANESTATUS2_REG                                 (0x0000031C)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS2_REG

#define DATA0CH1_CR_DCCLANESTATUS3_REG                                 (0x00000320)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS3_REG

#define DATA0CH1_CR_DCCPILUT0_REG                                      (0x00000324)
//Duplicate of DATA0CH0_CR_DCCPILUT0_REG

#define DATA0CH1_CR_DCCPILUT1_REG                                      (0x00000328)
//Duplicate of DATA0CH0_CR_DCCPILUT1_REG

#define DATA0CH1_CR_DCCPILUT2_REG                                      (0x0000032C)
//Duplicate of DATA0CH0_CR_DCCPILUT2_REG

#define DATA0CH1_CR_DCCPILUT3_REG                                      (0x00000330)
//Duplicate of DATA0CH0_CR_DCCPILUT3_REG

#define DATA0CH1_CR_DDRCRDATATCOCONTROL0_REG                           (0x00000334)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG

#define DATA0CH1_CR_DDRCRDATATCOCONTROL1_REG                           (0x00000338)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL1_REG

#define DATA0CH1_CR_DCCPILUT4_REG                                      (0x0000033C)
//Duplicate of DATA0CH0_CR_DCCPILUT4_REG

#define DATA0CH1_CR_DCCLANETARGET_REG                                  (0x00000340)
//Duplicate of DATA0CH0_CR_DCCLANETARGET_REG

#define DATA0CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG                   (0x00000344)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG

#define DATA0CH1_CR_DDRCRWRRETRAINRANK3_REG                            (0x00000348)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA0CH1_CR_DDRCRWRRETRAINRANK2_REG                            (0x0000034C)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA0CH1_CR_DDRCRWRRETRAINRANK1_REG                            (0x00000350)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA0CH1_CR_DDRCRWRRETRAINRANK0_REG                            (0x00000354)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA0CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_REG                    (0x00000358)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG

#define DATA0CH1_CR_DDRCRMARGINMODECONTROL0_REG                        (0x0000035C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG

#define DATA0CH1_CR_DDRCRMARGINMODEDEBUGMSB0_REG                       (0x00000360)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA0CH1_CR_DDRCRMARGINMODEDEBUGLSB0_REG                       (0x00000364)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA1CH0_CR_DDRDATADQRANK0LANE0_REG                            (0x00000400)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK0LANE1_REG                            (0x00000404)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK0LANE2_REG                            (0x00000408)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK0LANE3_REG                            (0x0000040C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK0LANE4_REG                            (0x00000410)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK0LANE5_REG                            (0x00000414)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK0LANE6_REG                            (0x00000418)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK0LANE7_REG                            (0x0000041C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK0LANE8_REG                            (0x00000420)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK1LANE0_REG                            (0x00000424)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK1LANE1_REG                            (0x00000428)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK1LANE2_REG                            (0x0000042C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK1LANE3_REG                            (0x00000430)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK1LANE4_REG                            (0x00000434)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK1LANE5_REG                            (0x00000438)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK1LANE6_REG                            (0x0000043C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK1LANE7_REG                            (0x00000440)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK1LANE8_REG                            (0x00000444)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK2LANE0_REG                            (0x00000448)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK2LANE1_REG                            (0x0000044C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK2LANE2_REG                            (0x00000450)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK2LANE3_REG                            (0x00000454)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK2LANE4_REG                            (0x00000458)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK2LANE5_REG                            (0x0000045C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK2LANE6_REG                            (0x00000460)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK2LANE7_REG                            (0x00000464)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK2LANE8_REG                            (0x00000468)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK3LANE0_REG                            (0x0000046C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK3LANE1_REG                            (0x00000470)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK3LANE2_REG                            (0x00000474)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK3LANE3_REG                            (0x00000478)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK3LANE4_REG                            (0x0000047C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK3LANE5_REG                            (0x00000480)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK3LANE6_REG                            (0x00000484)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK3LANE7_REG                            (0x00000488)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQRANK3LANE8_REG                            (0x0000048C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH0_CR_DDRDATADQSRANK0_REG                                (0x0000049C)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA1CH0_CR_DDRDATADQSRANK1_REG                                (0x000004A0)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA1CH0_CR_DDRDATADQSRANK2_REG                                (0x000004A4)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA1CH0_CR_DDRDATADQSRANK3_REG                                (0x000004A8)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA1CH0_CR_RXCONTROL0RANK0_REG                                (0x000004AC)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA1CH0_CR_RXCONTROL0RANK1_REG                                (0x000004B0)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA1CH0_CR_RXCONTROL0RANK2_REG                                (0x000004B4)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA1CH0_CR_RXCONTROL0RANK3_REG                                (0x000004B8)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA1CH0_CR_TXCONTROL0RANK0_REG                                (0x000004BC)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA1CH0_CR_TXCONTROL0RANK1_REG                                (0x000004C0)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA1CH0_CR_TXCONTROL0RANK2_REG                                (0x000004C4)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA1CH0_CR_TXCONTROL0RANK3_REG                                (0x000004C8)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA1CH0_CR_RCOMPDATA0_REG                                     (0x000004CC)
//Duplicate of DATA0CH0_CR_RCOMPDATA0_REG

#define DATA1CH0_CR_RCOMPDATA1_REG                                     (0x000004D0)
//Duplicate of DATA0CH0_CR_RCOMPDATA1_REG

#define DATA1CH0_CR_DATACOMPVTT_REG                                    (0x000004D4)
//Duplicate of DATA0CH0_CR_DATACOMPVTT_REG

#define DATA1CH0_CR_DATATRAINFEEDBACK_REG                              (0x000004DC)
//Duplicate of DATA0CH0_CR_DATATRAINFEEDBACK_REG

#define DATA1CH0_CR_DDRCRDATAOFFSETCOMP_REG                            (0x000004E0)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG

#define DATA1CH0_CR_DDRCRDATAOFFSETTRAIN_REG                           (0x000004E4)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG

#define DATA1CH0_CR_DDRCRDATACONTROL0_REG                              (0x000004E8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL0_REG

#define DATA1CH0_CR_DDRCRDATACONTROL1_REG                              (0x000004EC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL1_REG

#define DATA1CH0_CR_DDRCRDATACONTROL2_REG                              (0x000004F0)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL2_REG

#define DATA1CH0_CR_DDRCRDATACONTROL3_REG                              (0x000004F4)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL3_REG

#define DATA1CH0_CR_DDRCRDATACONTROL4_REG                              (0x000004F8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL4_REG

#define DATA1CH0_CR_DDRCRDATACONTROL5_REG                              (0x000004FC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL5_REG

#define DATA1CH0_CR_DDRCRDATACONTROL6_REG                              (0x00000500)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL6_REG

#define DATA1CH0_CR_DDRCRCMDBUSTRAIN_REG                               (0x00000504)
//Duplicate of DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG

#define DATA1CH0_CR_DCCFSMCONTROL_REG                                  (0x00000508)
//Duplicate of DATA0CH0_CR_DCCFSMCONTROL_REG

#define DATA1CH0_CR_DCCCALCCONTROL_REG                                 (0x0000050C)
//Duplicate of DATA0CH0_CR_DCCCALCCONTROL_REG

#define DATA1CH0_CR_DCCFSMSTATUS_REG                                   (0x00000510)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define DATA1CH0_CR_DCCLANESTATUS0_REG                                 (0x00000514)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define DATA1CH0_CR_DCCLANESTATUS1_REG                                 (0x00000518)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define DATA1CH0_CR_DCCLANESTATUS2_REG                                 (0x0000051C)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS2_REG

#define DATA1CH0_CR_DCCLANESTATUS3_REG                                 (0x00000520)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS3_REG

#define DATA1CH0_CR_DCCPILUT0_REG                                      (0x00000524)
//Duplicate of DATA0CH0_CR_DCCPILUT0_REG

#define DATA1CH0_CR_DCCPILUT1_REG                                      (0x00000528)
//Duplicate of DATA0CH0_CR_DCCPILUT1_REG

#define DATA1CH0_CR_DCCPILUT2_REG                                      (0x0000052C)
//Duplicate of DATA0CH0_CR_DCCPILUT2_REG

#define DATA1CH0_CR_DCCPILUT3_REG                                      (0x00000530)
//Duplicate of DATA0CH0_CR_DCCPILUT3_REG

#define DATA1CH0_CR_DDRCRDATATCOCONTROL0_REG                           (0x00000534)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG

#define DATA1CH0_CR_DDRCRDATATCOCONTROL1_REG                           (0x00000538)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL1_REG

#define DATA1CH0_CR_DCCPILUT4_REG                                      (0x0000053C)
//Duplicate of DATA0CH0_CR_DCCPILUT4_REG

#define DATA1CH0_CR_DCCLANETARGET_REG                                  (0x00000540)
//Duplicate of DATA0CH0_CR_DCCLANETARGET_REG

#define DATA1CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG                   (0x00000544)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG

#define DATA1CH0_CR_DDRCRWRRETRAINRANK3_REG                            (0x00000548)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA1CH0_CR_DDRCRWRRETRAINRANK2_REG                            (0x0000054C)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA1CH0_CR_DDRCRWRRETRAINRANK1_REG                            (0x00000550)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA1CH0_CR_DDRCRWRRETRAINRANK0_REG                            (0x00000554)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA1CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG                    (0x00000558)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG

#define DATA1CH0_CR_DDRCRMARGINMODECONTROL0_REG                        (0x0000055C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG

#define DATA1CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG                       (0x00000560)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA1CH0_CR_DDRCRMARGINMODEDEBUGLSB0_REG                       (0x00000564)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA1CH1_CR_DDRDATADQRANK0LANE0_REG                            (0x00000600)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK0LANE1_REG                            (0x00000604)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK0LANE2_REG                            (0x00000608)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK0LANE3_REG                            (0x0000060C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK0LANE4_REG                            (0x00000610)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK0LANE5_REG                            (0x00000614)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK0LANE6_REG                            (0x00000618)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK0LANE7_REG                            (0x0000061C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK0LANE8_REG                            (0x00000620)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK1LANE0_REG                            (0x00000624)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK1LANE1_REG                            (0x00000628)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK1LANE2_REG                            (0x0000062C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK1LANE3_REG                            (0x00000630)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK1LANE4_REG                            (0x00000634)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK1LANE5_REG                            (0x00000638)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK1LANE6_REG                            (0x0000063C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK1LANE7_REG                            (0x00000640)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK1LANE8_REG                            (0x00000644)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK2LANE0_REG                            (0x00000648)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK2LANE1_REG                            (0x0000064C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK2LANE2_REG                            (0x00000650)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK2LANE3_REG                            (0x00000654)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK2LANE4_REG                            (0x00000658)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK2LANE5_REG                            (0x0000065C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK2LANE6_REG                            (0x00000660)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK2LANE7_REG                            (0x00000664)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK2LANE8_REG                            (0x00000668)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK3LANE0_REG                            (0x0000066C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK3LANE1_REG                            (0x00000670)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK3LANE2_REG                            (0x00000674)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK3LANE3_REG                            (0x00000678)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK3LANE4_REG                            (0x0000067C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK3LANE5_REG                            (0x00000680)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK3LANE6_REG                            (0x00000684)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK3LANE7_REG                            (0x00000688)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQRANK3LANE8_REG                            (0x0000068C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA1CH1_CR_DDRDATADQSRANK0_REG                                (0x0000069C)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA1CH1_CR_DDRDATADQSRANK1_REG                                (0x000006A0)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA1CH1_CR_DDRDATADQSRANK2_REG                                (0x000006A4)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA1CH1_CR_DDRDATADQSRANK3_REG                                (0x000006A8)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA1CH1_CR_RXCONTROL0RANK0_REG                                (0x000006AC)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA1CH1_CR_RXCONTROL0RANK1_REG                                (0x000006B0)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA1CH1_CR_RXCONTROL0RANK2_REG                                (0x000006B4)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA1CH1_CR_RXCONTROL0RANK3_REG                                (0x000006B8)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA1CH1_CR_TXCONTROL0RANK0_REG                                (0x000006BC)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA1CH1_CR_TXCONTROL0RANK1_REG                                (0x000006C0)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA1CH1_CR_TXCONTROL0RANK2_REG                                (0x000006C4)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA1CH1_CR_TXCONTROL0RANK3_REG                                (0x000006C8)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA1CH1_CR_RCOMPDATA0_REG                                     (0x000006CC)
//Duplicate of DATA0CH0_CR_RCOMPDATA0_REG

#define DATA1CH1_CR_RCOMPDATA1_REG                                     (0x000006D0)
//Duplicate of DATA0CH0_CR_RCOMPDATA1_REG

#define DATA1CH1_CR_DATACOMPVTT_REG                                    (0x000006D4)
//Duplicate of DATA0CH0_CR_DATACOMPVTT_REG

#define DATA1CH1_CR_DATATRAINFEEDBACK_REG                              (0x000006DC)
//Duplicate of DATA0CH0_CR_DATATRAINFEEDBACK_REG

#define DATA1CH1_CR_DDRCRDATAOFFSETCOMP_REG                            (0x000006E0)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG

#define DATA1CH1_CR_DDRCRDATAOFFSETTRAIN_REG                           (0x000006E4)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG

#define DATA1CH1_CR_DDRCRDATACONTROL0_REG                              (0x000006E8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL0_REG

#define DATA1CH1_CR_DDRCRDATACONTROL1_REG                              (0x000006EC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL1_REG

#define DATA1CH1_CR_DDRCRDATACONTROL2_REG                              (0x000006F0)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL2_REG

#define DATA1CH1_CR_DDRCRDATACONTROL3_REG                              (0x000006F4)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL3_REG

#define DATA1CH1_CR_DDRCRDATACONTROL4_REG                              (0x000006F8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL4_REG

#define DATA1CH1_CR_DDRCRDATACONTROL5_REG                              (0x000006FC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL5_REG

#define DATA1CH1_CR_DDRCRDATACONTROL6_REG                              (0x00000700)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL6_REG

#define DATA1CH1_CR_DDRCRCMDBUSTRAIN_REG                               (0x00000704)
//Duplicate of DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG

#define DATA1CH1_CR_DCCFSMCONTROL_REG                                  (0x00000708)
//Duplicate of DATA0CH0_CR_DCCFSMCONTROL_REG

#define DATA1CH1_CR_DCCCALCCONTROL_REG                                 (0x0000070C)
//Duplicate of DATA0CH0_CR_DCCCALCCONTROL_REG

#define DATA1CH1_CR_DCCFSMSTATUS_REG                                   (0x00000710)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define DATA1CH1_CR_DCCLANESTATUS0_REG                                 (0x00000714)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define DATA1CH1_CR_DCCLANESTATUS1_REG                                 (0x00000718)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define DATA1CH1_CR_DCCLANESTATUS2_REG                                 (0x0000071C)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS2_REG

#define DATA1CH1_CR_DCCLANESTATUS3_REG                                 (0x00000720)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS3_REG

#define DATA1CH1_CR_DCCPILUT0_REG                                      (0x00000724)
//Duplicate of DATA0CH0_CR_DCCPILUT0_REG

#define DATA1CH1_CR_DCCPILUT1_REG                                      (0x00000728)
//Duplicate of DATA0CH0_CR_DCCPILUT1_REG

#define DATA1CH1_CR_DCCPILUT2_REG                                      (0x0000072C)
//Duplicate of DATA0CH0_CR_DCCPILUT2_REG

#define DATA1CH1_CR_DCCPILUT3_REG                                      (0x00000730)
//Duplicate of DATA0CH0_CR_DCCPILUT3_REG

#define DATA1CH1_CR_DDRCRDATATCOCONTROL0_REG                           (0x00000734)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG

#define DATA1CH1_CR_DDRCRDATATCOCONTROL1_REG                           (0x00000738)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL1_REG

#define DATA1CH1_CR_DCCPILUT4_REG                                      (0x0000073C)
//Duplicate of DATA0CH0_CR_DCCPILUT4_REG

#define DATA1CH1_CR_DCCLANETARGET_REG                                  (0x00000740)
//Duplicate of DATA0CH0_CR_DCCLANETARGET_REG

#define DATA1CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG                   (0x00000744)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG

#define DATA1CH1_CR_DDRCRWRRETRAINRANK3_REG                            (0x00000748)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA1CH1_CR_DDRCRWRRETRAINRANK2_REG                            (0x0000074C)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA1CH1_CR_DDRCRWRRETRAINRANK1_REG                            (0x00000750)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA1CH1_CR_DDRCRWRRETRAINRANK0_REG                            (0x00000754)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA1CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_REG                    (0x00000758)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG

#define DATA1CH1_CR_DDRCRMARGINMODECONTROL0_REG                        (0x0000075C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG

#define DATA1CH1_CR_DDRCRMARGINMODEDEBUGMSB0_REG                       (0x00000760)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA1CH1_CR_DDRCRMARGINMODEDEBUGLSB0_REG                       (0x00000764)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA2CH0_CR_DDRDATADQRANK0LANE0_REG                            (0x00000800)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK0LANE1_REG                            (0x00000804)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK0LANE2_REG                            (0x00000808)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK0LANE3_REG                            (0x0000080C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK0LANE4_REG                            (0x00000810)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK0LANE5_REG                            (0x00000814)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK0LANE6_REG                            (0x00000818)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK0LANE7_REG                            (0x0000081C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK0LANE8_REG                            (0x00000820)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK1LANE0_REG                            (0x00000824)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK1LANE1_REG                            (0x00000828)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK1LANE2_REG                            (0x0000082C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK1LANE3_REG                            (0x00000830)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK1LANE4_REG                            (0x00000834)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK1LANE5_REG                            (0x00000838)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK1LANE6_REG                            (0x0000083C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK1LANE7_REG                            (0x00000840)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK1LANE8_REG                            (0x00000844)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK2LANE0_REG                            (0x00000848)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK2LANE1_REG                            (0x0000084C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK2LANE2_REG                            (0x00000850)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK2LANE3_REG                            (0x00000854)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK2LANE4_REG                            (0x00000858)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK2LANE5_REG                            (0x0000085C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK2LANE6_REG                            (0x00000860)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK2LANE7_REG                            (0x00000864)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK2LANE8_REG                            (0x00000868)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK3LANE0_REG                            (0x0000086C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK3LANE1_REG                            (0x00000870)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK3LANE2_REG                            (0x00000874)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK3LANE3_REG                            (0x00000878)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK3LANE4_REG                            (0x0000087C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK3LANE5_REG                            (0x00000880)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK3LANE6_REG                            (0x00000884)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK3LANE7_REG                            (0x00000888)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQRANK3LANE8_REG                            (0x0000088C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH0_CR_DDRDATADQSRANK0_REG                                (0x0000089C)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA2CH0_CR_DDRDATADQSRANK1_REG                                (0x000008A0)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA2CH0_CR_DDRDATADQSRANK2_REG                                (0x000008A4)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA2CH0_CR_DDRDATADQSRANK3_REG                                (0x000008A8)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA2CH0_CR_RXCONTROL0RANK0_REG                                (0x000008AC)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA2CH0_CR_RXCONTROL0RANK1_REG                                (0x000008B0)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA2CH0_CR_RXCONTROL0RANK2_REG                                (0x000008B4)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA2CH0_CR_RXCONTROL0RANK3_REG                                (0x000008B8)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA2CH0_CR_TXCONTROL0RANK0_REG                                (0x000008BC)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA2CH0_CR_TXCONTROL0RANK1_REG                                (0x000008C0)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA2CH0_CR_TXCONTROL0RANK2_REG                                (0x000008C4)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA2CH0_CR_TXCONTROL0RANK3_REG                                (0x000008C8)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA2CH0_CR_RCOMPDATA0_REG                                     (0x000008CC)
//Duplicate of DATA0CH0_CR_RCOMPDATA0_REG

#define DATA2CH0_CR_RCOMPDATA1_REG                                     (0x000008D0)
//Duplicate of DATA0CH0_CR_RCOMPDATA1_REG

#define DATA2CH0_CR_DATACOMPVTT_REG                                    (0x000008D4)
//Duplicate of DATA0CH0_CR_DATACOMPVTT_REG

#define DATA2CH0_CR_DATATRAINFEEDBACK_REG                              (0x000008DC)
//Duplicate of DATA0CH0_CR_DATATRAINFEEDBACK_REG

#define DATA2CH0_CR_DDRCRDATAOFFSETCOMP_REG                            (0x000008E0)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG

#define DATA2CH0_CR_DDRCRDATAOFFSETTRAIN_REG                           (0x000008E4)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG

#define DATA2CH0_CR_DDRCRDATACONTROL0_REG                              (0x000008E8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL0_REG

#define DATA2CH0_CR_DDRCRDATACONTROL1_REG                              (0x000008EC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL1_REG

#define DATA2CH0_CR_DDRCRDATACONTROL2_REG                              (0x000008F0)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL2_REG

#define DATA2CH0_CR_DDRCRDATACONTROL3_REG                              (0x000008F4)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL3_REG

#define DATA2CH0_CR_DDRCRDATACONTROL4_REG                              (0x000008F8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL4_REG

#define DATA2CH0_CR_DDRCRDATACONTROL5_REG                              (0x000008FC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL5_REG

#define DATA2CH0_CR_DDRCRDATACONTROL6_REG                              (0x00000900)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL6_REG

#define DATA2CH0_CR_DDRCRCMDBUSTRAIN_REG                               (0x00000904)
//Duplicate of DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG

#define DATA2CH0_CR_DCCFSMCONTROL_REG                                  (0x00000908)
//Duplicate of DATA0CH0_CR_DCCFSMCONTROL_REG

#define DATA2CH0_CR_DCCCALCCONTROL_REG                                 (0x0000090C)
//Duplicate of DATA0CH0_CR_DCCCALCCONTROL_REG

#define DATA2CH0_CR_DCCFSMSTATUS_REG                                   (0x00000910)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define DATA2CH0_CR_DCCLANESTATUS0_REG                                 (0x00000914)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define DATA2CH0_CR_DCCLANESTATUS1_REG                                 (0x00000918)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define DATA2CH0_CR_DCCLANESTATUS2_REG                                 (0x0000091C)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS2_REG

#define DATA2CH0_CR_DCCLANESTATUS3_REG                                 (0x00000920)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS3_REG

#define DATA2CH0_CR_DCCPILUT0_REG                                      (0x00000924)
//Duplicate of DATA0CH0_CR_DCCPILUT0_REG

#define DATA2CH0_CR_DCCPILUT1_REG                                      (0x00000928)
//Duplicate of DATA0CH0_CR_DCCPILUT1_REG

#define DATA2CH0_CR_DCCPILUT2_REG                                      (0x0000092C)
//Duplicate of DATA0CH0_CR_DCCPILUT2_REG

#define DATA2CH0_CR_DCCPILUT3_REG                                      (0x00000930)
//Duplicate of DATA0CH0_CR_DCCPILUT3_REG

#define DATA2CH0_CR_DDRCRDATATCOCONTROL0_REG                           (0x00000934)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG

#define DATA2CH0_CR_DDRCRDATATCOCONTROL1_REG                           (0x00000938)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL1_REG

#define DATA2CH0_CR_DCCPILUT4_REG                                      (0x0000093C)
//Duplicate of DATA0CH0_CR_DCCPILUT4_REG

#define DATA2CH0_CR_DCCLANETARGET_REG                                  (0x00000940)
//Duplicate of DATA0CH0_CR_DCCLANETARGET_REG

#define DATA2CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG                   (0x00000944)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG

#define DATA2CH0_CR_DDRCRWRRETRAINRANK3_REG                            (0x00000948)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA2CH0_CR_DDRCRWRRETRAINRANK2_REG                            (0x0000094C)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA2CH0_CR_DDRCRWRRETRAINRANK1_REG                            (0x00000950)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA2CH0_CR_DDRCRWRRETRAINRANK0_REG                            (0x00000954)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA2CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG                    (0x00000958)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG

#define DATA2CH0_CR_DDRCRMARGINMODECONTROL0_REG                        (0x0000095C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG

#define DATA2CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG                       (0x00000960)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA2CH0_CR_DDRCRMARGINMODEDEBUGLSB0_REG                       (0x00000964)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA2CH1_CR_DDRDATADQRANK0LANE0_REG                            (0x00000A00)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK0LANE1_REG                            (0x00000A04)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK0LANE2_REG                            (0x00000A08)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK0LANE3_REG                            (0x00000A0C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK0LANE4_REG                            (0x00000A10)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK0LANE5_REG                            (0x00000A14)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK0LANE6_REG                            (0x00000A18)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK0LANE7_REG                            (0x00000A1C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK0LANE8_REG                            (0x00000A20)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK1LANE0_REG                            (0x00000A24)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK1LANE1_REG                            (0x00000A28)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK1LANE2_REG                            (0x00000A2C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK1LANE3_REG                            (0x00000A30)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK1LANE4_REG                            (0x00000A34)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK1LANE5_REG                            (0x00000A38)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK1LANE6_REG                            (0x00000A3C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK1LANE7_REG                            (0x00000A40)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK1LANE8_REG                            (0x00000A44)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK2LANE0_REG                            (0x00000A48)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK2LANE1_REG                            (0x00000A4C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK2LANE2_REG                            (0x00000A50)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK2LANE3_REG                            (0x00000A54)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK2LANE4_REG                            (0x00000A58)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK2LANE5_REG                            (0x00000A5C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK2LANE6_REG                            (0x00000A60)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK2LANE7_REG                            (0x00000A64)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK2LANE8_REG                            (0x00000A68)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK3LANE0_REG                            (0x00000A6C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK3LANE1_REG                            (0x00000A70)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK3LANE2_REG                            (0x00000A74)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK3LANE3_REG                            (0x00000A78)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK3LANE4_REG                            (0x00000A7C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK3LANE5_REG                            (0x00000A80)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK3LANE6_REG                            (0x00000A84)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK3LANE7_REG                            (0x00000A88)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQRANK3LANE8_REG                            (0x00000A8C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA2CH1_CR_DDRDATADQSRANK0_REG                                (0x00000A9C)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA2CH1_CR_DDRDATADQSRANK1_REG                                (0x00000AA0)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA2CH1_CR_DDRDATADQSRANK2_REG                                (0x00000AA4)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA2CH1_CR_DDRDATADQSRANK3_REG                                (0x00000AA8)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA2CH1_CR_RXCONTROL0RANK0_REG                                (0x00000AAC)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA2CH1_CR_RXCONTROL0RANK1_REG                                (0x00000AB0)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA2CH1_CR_RXCONTROL0RANK2_REG                                (0x00000AB4)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA2CH1_CR_RXCONTROL0RANK3_REG                                (0x00000AB8)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA2CH1_CR_TXCONTROL0RANK0_REG                                (0x00000ABC)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA2CH1_CR_TXCONTROL0RANK1_REG                                (0x00000AC0)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA2CH1_CR_TXCONTROL0RANK2_REG                                (0x00000AC4)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA2CH1_CR_TXCONTROL0RANK3_REG                                (0x00000AC8)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA2CH1_CR_RCOMPDATA0_REG                                     (0x00000ACC)
//Duplicate of DATA0CH0_CR_RCOMPDATA0_REG

#define DATA2CH1_CR_RCOMPDATA1_REG                                     (0x00000AD0)
//Duplicate of DATA0CH0_CR_RCOMPDATA1_REG

#define DATA2CH1_CR_DATACOMPVTT_REG                                    (0x00000AD4)
//Duplicate of DATA0CH0_CR_DATACOMPVTT_REG

#define DATA2CH1_CR_DATATRAINFEEDBACK_REG                              (0x00000ADC)
//Duplicate of DATA0CH0_CR_DATATRAINFEEDBACK_REG

#define DATA2CH1_CR_DDRCRDATAOFFSETCOMP_REG                            (0x00000AE0)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG

#define DATA2CH1_CR_DDRCRDATAOFFSETTRAIN_REG                           (0x00000AE4)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG

#define DATA2CH1_CR_DDRCRDATACONTROL0_REG                              (0x00000AE8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL0_REG

#define DATA2CH1_CR_DDRCRDATACONTROL1_REG                              (0x00000AEC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL1_REG

#define DATA2CH1_CR_DDRCRDATACONTROL2_REG                              (0x00000AF0)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL2_REG

#define DATA2CH1_CR_DDRCRDATACONTROL3_REG                              (0x00000AF4)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL3_REG

#define DATA2CH1_CR_DDRCRDATACONTROL4_REG                              (0x00000AF8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL4_REG

#define DATA2CH1_CR_DDRCRDATACONTROL5_REG                              (0x00000AFC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL5_REG

#define DATA2CH1_CR_DDRCRDATACONTROL6_REG                              (0x00000B00)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL6_REG

#define DATA2CH1_CR_DDRCRCMDBUSTRAIN_REG                               (0x00000B04)
//Duplicate of DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG

#define DATA2CH1_CR_DCCFSMCONTROL_REG                                  (0x00000B08)
//Duplicate of DATA0CH0_CR_DCCFSMCONTROL_REG

#define DATA2CH1_CR_DCCCALCCONTROL_REG                                 (0x00000B0C)
//Duplicate of DATA0CH0_CR_DCCCALCCONTROL_REG

#define DATA2CH1_CR_DCCFSMSTATUS_REG                                   (0x00000B10)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define DATA2CH1_CR_DCCLANESTATUS0_REG                                 (0x00000B14)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define DATA2CH1_CR_DCCLANESTATUS1_REG                                 (0x00000B18)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define DATA2CH1_CR_DCCLANESTATUS2_REG                                 (0x00000B1C)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS2_REG

#define DATA2CH1_CR_DCCLANESTATUS3_REG                                 (0x00000B20)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS3_REG

#define DATA2CH1_CR_DCCPILUT0_REG                                      (0x00000B24)
//Duplicate of DATA0CH0_CR_DCCPILUT0_REG

#define DATA2CH1_CR_DCCPILUT1_REG                                      (0x00000B28)
//Duplicate of DATA0CH0_CR_DCCPILUT1_REG

#define DATA2CH1_CR_DCCPILUT2_REG                                      (0x00000B2C)
//Duplicate of DATA0CH0_CR_DCCPILUT2_REG

#define DATA2CH1_CR_DCCPILUT3_REG                                      (0x00000B30)
//Duplicate of DATA0CH0_CR_DCCPILUT3_REG

#define DATA2CH1_CR_DDRCRDATATCOCONTROL0_REG                           (0x00000B34)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG

#define DATA2CH1_CR_DDRCRDATATCOCONTROL1_REG                           (0x00000B38)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL1_REG

#define DATA2CH1_CR_DCCPILUT4_REG                                      (0x00000B3C)
//Duplicate of DATA0CH0_CR_DCCPILUT4_REG

#define DATA2CH1_CR_DCCLANETARGET_REG                                  (0x00000B40)
//Duplicate of DATA0CH0_CR_DCCLANETARGET_REG

#define DATA2CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG                   (0x00000B44)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG

#define DATA2CH1_CR_DDRCRWRRETRAINRANK3_REG                            (0x00000B48)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA2CH1_CR_DDRCRWRRETRAINRANK2_REG                            (0x00000B4C)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA2CH1_CR_DDRCRWRRETRAINRANK1_REG                            (0x00000B50)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA2CH1_CR_DDRCRWRRETRAINRANK0_REG                            (0x00000B54)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA2CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_REG                    (0x00000B58)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG

#define DATA2CH1_CR_DDRCRMARGINMODECONTROL0_REG                        (0x00000B5C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG

#define DATA2CH1_CR_DDRCRMARGINMODEDEBUGMSB0_REG                       (0x00000B60)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA2CH1_CR_DDRCRMARGINMODEDEBUGLSB0_REG                       (0x00000B64)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA3CH0_CR_DDRDATADQRANK0LANE0_REG                            (0x00000C00)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK0LANE1_REG                            (0x00000C04)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK0LANE2_REG                            (0x00000C08)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK0LANE3_REG                            (0x00000C0C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK0LANE4_REG                            (0x00000C10)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK0LANE5_REG                            (0x00000C14)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK0LANE6_REG                            (0x00000C18)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK0LANE7_REG                            (0x00000C1C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK0LANE8_REG                            (0x00000C20)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK1LANE0_REG                            (0x00000C24)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK1LANE1_REG                            (0x00000C28)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK1LANE2_REG                            (0x00000C2C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK1LANE3_REG                            (0x00000C30)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK1LANE4_REG                            (0x00000C34)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK1LANE5_REG                            (0x00000C38)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK1LANE6_REG                            (0x00000C3C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK1LANE7_REG                            (0x00000C40)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK1LANE8_REG                            (0x00000C44)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK2LANE0_REG                            (0x00000C48)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK2LANE1_REG                            (0x00000C4C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK2LANE2_REG                            (0x00000C50)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK2LANE3_REG                            (0x00000C54)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK2LANE4_REG                            (0x00000C58)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK2LANE5_REG                            (0x00000C5C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK2LANE6_REG                            (0x00000C60)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK2LANE7_REG                            (0x00000C64)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK2LANE8_REG                            (0x00000C68)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK3LANE0_REG                            (0x00000C6C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK3LANE1_REG                            (0x00000C70)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK3LANE2_REG                            (0x00000C74)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK3LANE3_REG                            (0x00000C78)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK3LANE4_REG                            (0x00000C7C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK3LANE5_REG                            (0x00000C80)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK3LANE6_REG                            (0x00000C84)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK3LANE7_REG                            (0x00000C88)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQRANK3LANE8_REG                            (0x00000C8C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH0_CR_DDRDATADQSRANK0_REG                                (0x00000C9C)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA3CH0_CR_DDRDATADQSRANK1_REG                                (0x00000CA0)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA3CH0_CR_DDRDATADQSRANK2_REG                                (0x00000CA4)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA3CH0_CR_DDRDATADQSRANK3_REG                                (0x00000CA8)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA3CH0_CR_RXCONTROL0RANK0_REG                                (0x00000CAC)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA3CH0_CR_RXCONTROL0RANK1_REG                                (0x00000CB0)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA3CH0_CR_RXCONTROL0RANK2_REG                                (0x00000CB4)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA3CH0_CR_RXCONTROL0RANK3_REG                                (0x00000CB8)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA3CH0_CR_TXCONTROL0RANK0_REG                                (0x00000CBC)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA3CH0_CR_TXCONTROL0RANK1_REG                                (0x00000CC0)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA3CH0_CR_TXCONTROL0RANK2_REG                                (0x00000CC4)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA3CH0_CR_TXCONTROL0RANK3_REG                                (0x00000CC8)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA3CH0_CR_RCOMPDATA0_REG                                     (0x00000CCC)
//Duplicate of DATA0CH0_CR_RCOMPDATA0_REG

#define DATA3CH0_CR_RCOMPDATA1_REG                                     (0x00000CD0)
//Duplicate of DATA0CH0_CR_RCOMPDATA1_REG

#define DATA3CH0_CR_DATACOMPVTT_REG                                    (0x00000CD4)
//Duplicate of DATA0CH0_CR_DATACOMPVTT_REG

#define DATA3CH0_CR_DATATRAINFEEDBACK_REG                              (0x00000CDC)
//Duplicate of DATA0CH0_CR_DATATRAINFEEDBACK_REG

#define DATA3CH0_CR_DDRCRDATAOFFSETCOMP_REG                            (0x00000CE0)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG

#define DATA3CH0_CR_DDRCRDATAOFFSETTRAIN_REG                           (0x00000CE4)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG

#define DATA3CH0_CR_DDRCRDATACONTROL0_REG                              (0x00000CE8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL0_REG

#define DATA3CH0_CR_DDRCRDATACONTROL1_REG                              (0x00000CEC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL1_REG

#define DATA3CH0_CR_DDRCRDATACONTROL2_REG                              (0x00000CF0)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL2_REG

#define DATA3CH0_CR_DDRCRDATACONTROL3_REG                              (0x00000CF4)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL3_REG

#define DATA3CH0_CR_DDRCRDATACONTROL4_REG                              (0x00000CF8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL4_REG

#define DATA3CH0_CR_DDRCRDATACONTROL5_REG                              (0x00000CFC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL5_REG

#define DATA3CH0_CR_DDRCRDATACONTROL6_REG                              (0x00000D00)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL6_REG

#define DATA3CH0_CR_DDRCRCMDBUSTRAIN_REG                               (0x00000D04)
//Duplicate of DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG

#define DATA3CH0_CR_DCCFSMCONTROL_REG                                  (0x00000D08)
//Duplicate of DATA0CH0_CR_DCCFSMCONTROL_REG

#define DATA3CH0_CR_DCCCALCCONTROL_REG                                 (0x00000D0C)
//Duplicate of DATA0CH0_CR_DCCCALCCONTROL_REG

#define DATA3CH0_CR_DCCFSMSTATUS_REG                                   (0x00000D10)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define DATA3CH0_CR_DCCLANESTATUS0_REG                                 (0x00000D14)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define DATA3CH0_CR_DCCLANESTATUS1_REG                                 (0x00000D18)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define DATA3CH0_CR_DCCLANESTATUS2_REG                                 (0x00000D1C)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS2_REG

#define DATA3CH0_CR_DCCLANESTATUS3_REG                                 (0x00000D20)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS3_REG

#define DATA3CH0_CR_DCCPILUT0_REG                                      (0x00000D24)
//Duplicate of DATA0CH0_CR_DCCPILUT0_REG

#define DATA3CH0_CR_DCCPILUT1_REG                                      (0x00000D28)
//Duplicate of DATA0CH0_CR_DCCPILUT1_REG

#define DATA3CH0_CR_DCCPILUT2_REG                                      (0x00000D2C)
//Duplicate of DATA0CH0_CR_DCCPILUT2_REG

#define DATA3CH0_CR_DCCPILUT3_REG                                      (0x00000D30)
//Duplicate of DATA0CH0_CR_DCCPILUT3_REG

#define DATA3CH0_CR_DDRCRDATATCOCONTROL0_REG                           (0x00000D34)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG

#define DATA3CH0_CR_DDRCRDATATCOCONTROL1_REG                           (0x00000D38)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL1_REG

#define DATA3CH0_CR_DCCPILUT4_REG                                      (0x00000D3C)
//Duplicate of DATA0CH0_CR_DCCPILUT4_REG

#define DATA3CH0_CR_DCCLANETARGET_REG                                  (0x00000D40)
//Duplicate of DATA0CH0_CR_DCCLANETARGET_REG

#define DATA3CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG                   (0x00000D44)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG

#define DATA3CH0_CR_DDRCRWRRETRAINRANK3_REG                            (0x00000D48)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA3CH0_CR_DDRCRWRRETRAINRANK2_REG                            (0x00000D4C)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA3CH0_CR_DDRCRWRRETRAINRANK1_REG                            (0x00000D50)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA3CH0_CR_DDRCRWRRETRAINRANK0_REG                            (0x00000D54)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA3CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG                    (0x00000D58)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG

#define DATA3CH0_CR_DDRCRMARGINMODECONTROL0_REG                        (0x00000D5C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG

#define DATA3CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG                       (0x00000D60)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA3CH0_CR_DDRCRMARGINMODEDEBUGLSB0_REG                       (0x00000D64)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA3CH1_CR_DDRDATADQRANK0LANE0_REG                            (0x00000E00)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK0LANE1_REG                            (0x00000E04)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK0LANE2_REG                            (0x00000E08)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK0LANE3_REG                            (0x00000E0C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK0LANE4_REG                            (0x00000E10)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK0LANE5_REG                            (0x00000E14)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK0LANE6_REG                            (0x00000E18)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK0LANE7_REG                            (0x00000E1C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK0LANE8_REG                            (0x00000E20)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK1LANE0_REG                            (0x00000E24)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK1LANE1_REG                            (0x00000E28)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK1LANE2_REG                            (0x00000E2C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK1LANE3_REG                            (0x00000E30)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK1LANE4_REG                            (0x00000E34)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK1LANE5_REG                            (0x00000E38)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK1LANE6_REG                            (0x00000E3C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK1LANE7_REG                            (0x00000E40)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK1LANE8_REG                            (0x00000E44)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK2LANE0_REG                            (0x00000E48)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK2LANE1_REG                            (0x00000E4C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK2LANE2_REG                            (0x00000E50)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK2LANE3_REG                            (0x00000E54)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK2LANE4_REG                            (0x00000E58)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK2LANE5_REG                            (0x00000E5C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK2LANE6_REG                            (0x00000E60)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK2LANE7_REG                            (0x00000E64)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK2LANE8_REG                            (0x00000E68)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK3LANE0_REG                            (0x00000E6C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK3LANE1_REG                            (0x00000E70)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK3LANE2_REG                            (0x00000E74)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK3LANE3_REG                            (0x00000E78)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK3LANE4_REG                            (0x00000E7C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK3LANE5_REG                            (0x00000E80)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK3LANE6_REG                            (0x00000E84)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK3LANE7_REG                            (0x00000E88)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQRANK3LANE8_REG                            (0x00000E8C)
//Duplicate of DATA0CH0_CR_DDRDATADQRANK0LANE0_REG

#define DATA3CH1_CR_DDRDATADQSRANK0_REG                                (0x00000E9C)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA3CH1_CR_DDRDATADQSRANK1_REG                                (0x00000EA0)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA3CH1_CR_DDRDATADQSRANK2_REG                                (0x00000EA4)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA3CH1_CR_DDRDATADQSRANK3_REG                                (0x00000EA8)
//Duplicate of DATA0CH0_CR_DDRDATADQSRANK0_REG

#define DATA3CH1_CR_RXCONTROL0RANK0_REG                                (0x00000EAC)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA3CH1_CR_RXCONTROL0RANK1_REG                                (0x00000EB0)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA3CH1_CR_RXCONTROL0RANK2_REG                                (0x00000EB4)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA3CH1_CR_RXCONTROL0RANK3_REG                                (0x00000EB8)
//Duplicate of DATA0CH0_CR_RXCONTROL0RANK0_REG

#define DATA3CH1_CR_TXCONTROL0RANK0_REG                                (0x00000EBC)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA3CH1_CR_TXCONTROL0RANK1_REG                                (0x00000EC0)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA3CH1_CR_TXCONTROL0RANK2_REG                                (0x00000EC4)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA3CH1_CR_TXCONTROL0RANK3_REG                                (0x00000EC8)
//Duplicate of DATA0CH0_CR_TXCONTROL0RANK0_REG

#define DATA3CH1_CR_RCOMPDATA0_REG                                     (0x00000ECC)
//Duplicate of DATA0CH0_CR_RCOMPDATA0_REG

#define DATA3CH1_CR_RCOMPDATA1_REG                                     (0x00000ED0)
//Duplicate of DATA0CH0_CR_RCOMPDATA1_REG

#define DATA3CH1_CR_DATACOMPVTT_REG                                    (0x00000ED4)
//Duplicate of DATA0CH0_CR_DATACOMPVTT_REG

#define DATA3CH1_CR_DATATRAINFEEDBACK_REG                              (0x00000EDC)
//Duplicate of DATA0CH0_CR_DATATRAINFEEDBACK_REG

#define DATA3CH1_CR_DDRCRDATAOFFSETCOMP_REG                            (0x00000EE0)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG

#define DATA3CH1_CR_DDRCRDATAOFFSETTRAIN_REG                           (0x00000EE4)
//Duplicate of DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG

#define DATA3CH1_CR_DDRCRDATACONTROL0_REG                              (0x00000EE8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL0_REG

#define DATA3CH1_CR_DDRCRDATACONTROL1_REG                              (0x00000EEC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL1_REG

#define DATA3CH1_CR_DDRCRDATACONTROL2_REG                              (0x00000EF0)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL2_REG

#define DATA3CH1_CR_DDRCRDATACONTROL3_REG                              (0x00000EF4)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL3_REG

#define DATA3CH1_CR_DDRCRDATACONTROL4_REG                              (0x00000EF8)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL4_REG

#define DATA3CH1_CR_DDRCRDATACONTROL5_REG                              (0x00000EFC)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL5_REG

#define DATA3CH1_CR_DDRCRDATACONTROL6_REG                              (0x00000F00)
//Duplicate of DATA0CH0_CR_DDRCRDATACONTROL6_REG

#define DATA3CH1_CR_DDRCRCMDBUSTRAIN_REG                               (0x00000F04)
//Duplicate of DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG

#define DATA3CH1_CR_DCCFSMCONTROL_REG                                  (0x00000F08)
//Duplicate of DATA0CH0_CR_DCCFSMCONTROL_REG

#define DATA3CH1_CR_DCCCALCCONTROL_REG                                 (0x00000F0C)
//Duplicate of DATA0CH0_CR_DCCCALCCONTROL_REG

#define DATA3CH1_CR_DCCFSMSTATUS_REG                                   (0x00000F10)
//Duplicate of DATA0CH0_CR_DCCFSMSTATUS_REG

#define DATA3CH1_CR_DCCLANESTATUS0_REG                                 (0x00000F14)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS0_REG

#define DATA3CH1_CR_DCCLANESTATUS1_REG                                 (0x00000F18)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS1_REG

#define DATA3CH1_CR_DCCLANESTATUS2_REG                                 (0x00000F1C)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS2_REG

#define DATA3CH1_CR_DCCLANESTATUS3_REG                                 (0x00000F20)
//Duplicate of DATA0CH0_CR_DCCLANESTATUS3_REG

#define DATA3CH1_CR_DCCPILUT0_REG                                      (0x00000F24)
//Duplicate of DATA0CH0_CR_DCCPILUT0_REG

#define DATA3CH1_CR_DCCPILUT1_REG                                      (0x00000F28)
//Duplicate of DATA0CH0_CR_DCCPILUT1_REG

#define DATA3CH1_CR_DCCPILUT2_REG                                      (0x00000F2C)
//Duplicate of DATA0CH0_CR_DCCPILUT2_REG

#define DATA3CH1_CR_DCCPILUT3_REG                                      (0x00000F30)
//Duplicate of DATA0CH0_CR_DCCPILUT3_REG

#define DATA3CH1_CR_DDRCRDATATCOCONTROL0_REG                           (0x00000F34)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG

#define DATA3CH1_CR_DDRCRDATATCOCONTROL1_REG                           (0x00000F38)
//Duplicate of DATA0CH0_CR_DDRCRDATATCOCONTROL1_REG

#define DATA3CH1_CR_DCCPILUT4_REG                                      (0x00000F3C)
//Duplicate of DATA0CH0_CR_DCCPILUT4_REG

#define DATA3CH1_CR_DCCLANETARGET_REG                                  (0x00000F40)
//Duplicate of DATA0CH0_CR_DCCLANETARGET_REG

#define DATA3CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG                   (0x00000F44)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_REG

#define DATA3CH1_CR_DDRCRWRRETRAINRANK3_REG                            (0x00000F48)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA3CH1_CR_DDRCRWRRETRAINRANK2_REG                            (0x00000F4C)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA3CH1_CR_DDRCRWRRETRAINRANK1_REG                            (0x00000F50)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA3CH1_CR_DDRCRWRRETRAINRANK0_REG                            (0x00000F54)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINRANK3_REG

#define DATA3CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_REG                    (0x00000F58)
//Duplicate of DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG

#define DATA3CH1_CR_DDRCRMARGINMODECONTROL0_REG                        (0x00000F5C)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG

#define DATA3CH1_CR_DDRCRMARGINMODEDEBUGMSB0_REG                       (0x00000F60)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG

#define DATA3CH1_CR_DDRCRMARGINMODEDEBUGLSB0_REG                       (0x00000F64)
//Duplicate of DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_REG
#pragma pack(pop)
#endif
