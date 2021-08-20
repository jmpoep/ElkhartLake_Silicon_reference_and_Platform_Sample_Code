#ifndef __MrcMcRegisterCnl4xxx_h__
#define __MrcMcRegisterCnl4xxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#pragma pack(push, 1)

//#define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_REG                         (0x00004600)

  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_OFF    ( 0)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_WID    ( 6)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_MSK    (0x0000003F)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_MIN    (0)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_MAX    (63) // 0x0000003F
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_DEF    (0x00000000)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_HSH    (0x06004600)

  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_OFF   ( 6)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_WID   ( 1)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_MSK   (0x00000040)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_MIN   (0)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_MAX   (1) // 0x00000001
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_DEF   (0x00000000)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_HSH   (0x01064600)

  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_OFF     ( 8)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_WID     ( 6)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_MSK     (0x00003F00)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_MIN     (0)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_MAX     (63) // 0x0000003F
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_DEF     (0x00000000)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_HSH     (0x06084600)

  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_OFF       (16)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_WID       ( 6)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_MSK       (0x003F0000)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_MIN       (0)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_MAX       (63) // 0x0000003F
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_DEF       (0x0000003F)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_HSH       (0x06104600)

  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_OFF        (22)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_WID        ( 1)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_MSK        (0x00400000)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_MIN        (0)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_MAX        (1) // 0x00000001
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_DEF        (0x00000000)
  #define CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_HSH        (0x01164600)

#define REUT_GLOBAL_CTL_REG                                        (0x00004800)

  #define REUT_GLOBAL_CTL_Global_Start_Test_OFF                    ( 0)
  #define REUT_GLOBAL_CTL_Global_Start_Test_WID                    ( 1)
  #define REUT_GLOBAL_CTL_Global_Start_Test_MSK                    (0x00000001)
  #define REUT_GLOBAL_CTL_Global_Start_Test_MIN                    (0)
  #define REUT_GLOBAL_CTL_Global_Start_Test_MAX                    (1) // 0x00000001
  #define REUT_GLOBAL_CTL_Global_Start_Test_DEF                    (0x00000000)
  #define REUT_GLOBAL_CTL_Global_Start_Test_HSH                    (0x01004800)

  #define REUT_GLOBAL_CTL_Global_Stop_Test_OFF                     ( 1)
  #define REUT_GLOBAL_CTL_Global_Stop_Test_WID                     ( 1)
  #define REUT_GLOBAL_CTL_Global_Stop_Test_MSK                     (0x00000002)
  #define REUT_GLOBAL_CTL_Global_Stop_Test_MIN                     (0)
  #define REUT_GLOBAL_CTL_Global_Stop_Test_MAX                     (1) // 0x00000001
  #define REUT_GLOBAL_CTL_Global_Stop_Test_DEF                     (0x00000000)
  #define REUT_GLOBAL_CTL_Global_Stop_Test_HSH                     (0x01014800)

  #define REUT_GLOBAL_CTL_Global_Clear_Errors_OFF                  ( 2)
  #define REUT_GLOBAL_CTL_Global_Clear_Errors_WID                  ( 1)
  #define REUT_GLOBAL_CTL_Global_Clear_Errors_MSK                  (0x00000004)
  #define REUT_GLOBAL_CTL_Global_Clear_Errors_MIN                  (0)
  #define REUT_GLOBAL_CTL_Global_Clear_Errors_MAX                  (1) // 0x00000001
  #define REUT_GLOBAL_CTL_Global_Clear_Errors_DEF                  (0x00000000)
  #define REUT_GLOBAL_CTL_Global_Clear_Errors_HSH                  (0x01024800)

  #define REUT_GLOBAL_CTL_Global_Stop_Test_On_Any_Error_OFF        ( 4)
  #define REUT_GLOBAL_CTL_Global_Stop_Test_On_Any_Error_WID        ( 1)
  #define REUT_GLOBAL_CTL_Global_Stop_Test_On_Any_Error_MSK        (0x00000010)
  #define REUT_GLOBAL_CTL_Global_Stop_Test_On_Any_Error_MIN        (0)
  #define REUT_GLOBAL_CTL_Global_Stop_Test_On_Any_Error_MAX        (1) // 0x00000001
  #define REUT_GLOBAL_CTL_Global_Stop_Test_On_Any_Error_DEF        (0x00000000)
  #define REUT_GLOBAL_CTL_Global_Stop_Test_On_Any_Error_HSH        (0x01044800)

#define REUT_GLOBAL_ERR_REG                                        (0x00004804)

  #define REUT_GLOBAL_ERR_Channel_Error_Status_0_OFF               ( 0)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_0_WID               ( 1)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_0_MSK               (0x00000001)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_0_MIN               (0)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_0_MAX               (1) // 0x00000001
  #define REUT_GLOBAL_ERR_Channel_Error_Status_0_DEF               (0x00000000)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_0_HSH               (0x01004804)

  #define REUT_GLOBAL_ERR_Channel_Error_Status_1_OFF               ( 1)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_1_WID               ( 1)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_1_MSK               (0x00000002)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_1_MIN               (0)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_1_MAX               (1) // 0x00000001
  #define REUT_GLOBAL_ERR_Channel_Error_Status_1_DEF               (0x00000000)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_1_HSH               (0x01014804)

  #define REUT_GLOBAL_ERR_Channel_Error_Status_2_OFF               ( 2)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_2_WID               ( 1)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_2_MSK               (0x00000004)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_2_MIN               (0)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_2_MAX               (1) // 0x00000001
  #define REUT_GLOBAL_ERR_Channel_Error_Status_2_DEF               (0x00000000)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_2_HSH               (0x01024804)

  #define REUT_GLOBAL_ERR_Channel_Error_Status_3_OFF               ( 3)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_3_WID               ( 1)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_3_MSK               (0x00000008)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_3_MIN               (0)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_3_MAX               (1) // 0x00000001
  #define REUT_GLOBAL_ERR_Channel_Error_Status_3_DEF               (0x00000000)
  #define REUT_GLOBAL_ERR_Channel_Error_Status_3_HSH               (0x01034804)

  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_0_OFF           (16)
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_0_WID           ( 1)
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_0_MSK           (0x00010000)
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_0_MIN           (0)
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_0_MAX           (1) // 0x00000001
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_0_DEF           (0x00000001)
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_0_HSH           (0x01104804)

  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_1_OFF           (17)
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_1_WID           ( 1)
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_1_MSK           (0x00020000)
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_1_MIN           (0)
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_1_MAX           (1) // 0x00000001
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_1_DEF           (0x00000001)
  #define REUT_GLOBAL_ERR_Channel_Test_Done_Status_1_HSH           (0x01114804)

#define REUT_CH0_SUBSEQ_CTL_0_REG                                  (0x00004808)

  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_MIN           (0)
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_HSH           (0x07004808)

  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_HSH     (0x01074808)

  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Wait_WID               (14)
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Wait_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Wait_HSH               (0x0E084808)

  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Type_OFF               (22)
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Type_WID               ( 4)
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Type_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Subsequence_Type_HSH               (0x04164808)

  #define REUT_CH0_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH0_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_HSH (0x011A4808)

  #define REUT_CH0_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH0_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_HSH (0x011B4808)

  #define REUT_CH0_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH0_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH0_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_HSH (0x021C4808)

  #define REUT_CH0_SUBSEQ_CTL_0_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH0_SUBSEQ_CTL_0_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH0_SUBSEQ_CTL_0_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH0_SUBSEQ_CTL_0_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_0_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Invert_Data_and_ECC_HSH            (0x011E4808)

  #define REUT_CH0_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH0_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4808)

#define REUT_CH0_SUBSEQ_CTL_1_REG                                  (0x0000480C)

  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_MIN           (0)
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_HSH           (0x0700480C)

  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_HSH     (0x0107480C)

  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Wait_WID               (14)
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Wait_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Wait_HSH               (0x0E08480C)

  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Type_OFF               (22)
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Type_WID               ( 4)
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Type_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Subsequence_Type_HSH               (0x0416480C)

  #define REUT_CH0_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH0_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_HSH (0x011A480C)

  #define REUT_CH0_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH0_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_HSH (0x011B480C)

  #define REUT_CH0_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH0_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH0_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_HSH (0x021C480C)

  #define REUT_CH0_SUBSEQ_CTL_1_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH0_SUBSEQ_CTL_1_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH0_SUBSEQ_CTL_1_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH0_SUBSEQ_CTL_1_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_1_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Invert_Data_and_ECC_HSH            (0x011E480C)

  #define REUT_CH0_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH0_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F480C)

#define REUT_CH0_SUBSEQ_CTL_2_REG                                  (0x00004810)

  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_MIN           (0)
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_HSH           (0x07004810)

  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_HSH     (0x01074810)

  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Wait_WID               (14)
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Wait_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Wait_HSH               (0x0E084810)

  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Type_OFF               (22)
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Type_WID               ( 4)
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Type_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Subsequence_Type_HSH               (0x04164810)

  #define REUT_CH0_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH0_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_HSH (0x011A4810)

  #define REUT_CH0_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH0_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_HSH (0x011B4810)

  #define REUT_CH0_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH0_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH0_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_HSH (0x021C4810)

  #define REUT_CH0_SUBSEQ_CTL_2_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH0_SUBSEQ_CTL_2_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH0_SUBSEQ_CTL_2_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH0_SUBSEQ_CTL_2_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_2_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Invert_Data_and_ECC_HSH            (0x011E4810)

  #define REUT_CH0_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH0_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4810)

#define REUT_CH0_SUBSEQ_CTL_3_REG                                  (0x00004814)

  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_MIN           (0)
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_HSH           (0x07004814)

  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_HSH     (0x01074814)

  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Wait_WID               (14)
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Wait_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Wait_HSH               (0x0E084814)

  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Type_OFF               (22)
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Type_WID               ( 4)
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Type_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Subsequence_Type_HSH               (0x04164814)

  #define REUT_CH0_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH0_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_HSH (0x011A4814)

  #define REUT_CH0_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH0_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_HSH (0x011B4814)

  #define REUT_CH0_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH0_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH0_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_HSH (0x021C4814)

  #define REUT_CH0_SUBSEQ_CTL_3_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH0_SUBSEQ_CTL_3_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH0_SUBSEQ_CTL_3_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH0_SUBSEQ_CTL_3_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_3_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Invert_Data_and_ECC_HSH            (0x011E4814)

  #define REUT_CH0_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH0_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4814)

#define REUT_CH0_SUBSEQ_CTL_4_REG                                  (0x00004818)

  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_MIN           (0)
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_HSH           (0x07004818)

  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_HSH     (0x01074818)

  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Wait_WID               (14)
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Wait_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Wait_HSH               (0x0E084818)

  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Type_OFF               (22)
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Type_WID               ( 4)
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Type_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Subsequence_Type_HSH               (0x04164818)

  #define REUT_CH0_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH0_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_HSH (0x011A4818)

  #define REUT_CH0_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH0_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_HSH (0x011B4818)

  #define REUT_CH0_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH0_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH0_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_HSH (0x021C4818)

  #define REUT_CH0_SUBSEQ_CTL_4_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH0_SUBSEQ_CTL_4_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH0_SUBSEQ_CTL_4_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH0_SUBSEQ_CTL_4_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_4_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Invert_Data_and_ECC_HSH            (0x011E4818)

  #define REUT_CH0_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH0_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4818)

#define REUT_CH0_SUBSEQ_CTL_5_REG                                  (0x0000481C)

  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_MIN           (0)
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_HSH           (0x0700481C)

  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_HSH     (0x0107481C)

  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Wait_WID               (14)
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Wait_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Wait_HSH               (0x0E08481C)

  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Type_OFF               (22)
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Type_WID               ( 4)
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Type_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Subsequence_Type_HSH               (0x0416481C)

  #define REUT_CH0_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH0_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_HSH (0x011A481C)

  #define REUT_CH0_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH0_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_HSH (0x011B481C)

  #define REUT_CH0_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH0_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH0_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_HSH (0x021C481C)

  #define REUT_CH0_SUBSEQ_CTL_5_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH0_SUBSEQ_CTL_5_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH0_SUBSEQ_CTL_5_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH0_SUBSEQ_CTL_5_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_5_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Invert_Data_and_ECC_HSH            (0x011E481C)

  #define REUT_CH0_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH0_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F481C)

#define REUT_CH0_SUBSEQ_CTL_6_REG                                  (0x00004820)

  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_MIN           (0)
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_HSH           (0x07004820)

  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_HSH     (0x01074820)

  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Wait_WID               (14)
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Wait_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Wait_HSH               (0x0E084820)

  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Type_OFF               (22)
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Type_WID               ( 4)
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Type_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Subsequence_Type_HSH               (0x04164820)

  #define REUT_CH0_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH0_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_HSH (0x011A4820)

  #define REUT_CH0_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH0_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_HSH (0x011B4820)

  #define REUT_CH0_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH0_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH0_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_HSH (0x021C4820)

  #define REUT_CH0_SUBSEQ_CTL_6_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH0_SUBSEQ_CTL_6_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH0_SUBSEQ_CTL_6_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH0_SUBSEQ_CTL_6_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_6_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Invert_Data_and_ECC_HSH            (0x011E4820)

  #define REUT_CH0_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH0_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4820)

#define REUT_CH0_SUBSEQ_CTL_7_REG                                  (0x00004824)

  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_MIN           (0)
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_HSH           (0x07004824)

  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_HSH     (0x01074824)

  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Wait_WID               (14)
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Wait_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Wait_HSH               (0x0E084824)

  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Type_OFF               (22)
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Type_WID               ( 4)
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Type_MIN               (0)
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Subsequence_Type_HSH               (0x04164824)

  #define REUT_CH0_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH0_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_HSH (0x011A4824)

  #define REUT_CH0_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH0_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_HSH (0x011B4824)

  #define REUT_CH0_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH0_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH0_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_HSH (0x021C4824)

  #define REUT_CH0_SUBSEQ_CTL_7_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH0_SUBSEQ_CTL_7_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH0_SUBSEQ_CTL_7_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH0_SUBSEQ_CTL_7_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_7_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Invert_Data_and_ECC_HSH            (0x011E4824)

  #define REUT_CH0_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH0_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH0_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH0_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4824)

#define REUT_CH1_SUBSEQ_CTL_0_REG                                  (0x00004830)

  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_MIN           (0)
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_HSH           (0x07004830)

  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Number_of_Cachelines_Scale_HSH     (0x01074830)

  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Wait_WID               (14)
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Wait_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Wait_HSH               (0x0E084830)

  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Type_OFF               (22)
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Type_WID               ( 4)
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Type_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Subsequence_Type_HSH               (0x04164830)

  #define REUT_CH1_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH1_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Save_Current_Base_Address_To_Start_HSH (0x011A4830)

  #define REUT_CH1_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH1_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_CTL_0_Reset_Current_Base_Address_To_Start_HSH (0x011B4830)

  #define REUT_CH1_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH1_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH1_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Data_and_ECC_Address_Inversion_HSH (0x021C4830)

  #define REUT_CH1_SUBSEQ_CTL_0_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH1_SUBSEQ_CTL_0_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH1_SUBSEQ_CTL_0_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH1_SUBSEQ_CTL_0_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_0_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Invert_Data_and_ECC_HSH            (0x011E4830)

  #define REUT_CH1_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH1_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_0_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4830)

#define REUT_CH1_SUBSEQ_CTL_1_REG                                  (0x00004834)

  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_MIN           (0)
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_HSH           (0x07004834)

  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Number_of_Cachelines_Scale_HSH     (0x01074834)

  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Wait_WID               (14)
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Wait_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Wait_HSH               (0x0E084834)

  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Type_OFF               (22)
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Type_WID               ( 4)
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Type_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Subsequence_Type_HSH               (0x04164834)

  #define REUT_CH1_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH1_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Save_Current_Base_Address_To_Start_HSH (0x011A4834)

  #define REUT_CH1_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH1_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_CTL_1_Reset_Current_Base_Address_To_Start_HSH (0x011B4834)

  #define REUT_CH1_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH1_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH1_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Data_and_ECC_Address_Inversion_HSH (0x021C4834)

  #define REUT_CH1_SUBSEQ_CTL_1_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH1_SUBSEQ_CTL_1_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH1_SUBSEQ_CTL_1_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH1_SUBSEQ_CTL_1_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_1_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Invert_Data_and_ECC_HSH            (0x011E4834)

  #define REUT_CH1_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH1_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_1_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4834)

#define REUT_CH1_SUBSEQ_CTL_2_REG                                  (0x00004838)

  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_MIN           (0)
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_HSH           (0x07004838)

  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Number_of_Cachelines_Scale_HSH     (0x01074838)

  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Wait_WID               (14)
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Wait_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Wait_HSH               (0x0E084838)

  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Type_OFF               (22)
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Type_WID               ( 4)
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Type_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Subsequence_Type_HSH               (0x04164838)

  #define REUT_CH1_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH1_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Save_Current_Base_Address_To_Start_HSH (0x011A4838)

  #define REUT_CH1_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH1_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_CTL_2_Reset_Current_Base_Address_To_Start_HSH (0x011B4838)

  #define REUT_CH1_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH1_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH1_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Data_and_ECC_Address_Inversion_HSH (0x021C4838)

  #define REUT_CH1_SUBSEQ_CTL_2_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH1_SUBSEQ_CTL_2_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH1_SUBSEQ_CTL_2_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH1_SUBSEQ_CTL_2_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_2_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Invert_Data_and_ECC_HSH            (0x011E4838)

  #define REUT_CH1_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH1_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_2_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4838)

#define REUT_CH1_SUBSEQ_CTL_3_REG                                  (0x0000483C)

  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_MIN           (0)
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_HSH           (0x0700483C)

  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Number_of_Cachelines_Scale_HSH     (0x0107483C)

  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Wait_WID               (14)
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Wait_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Wait_HSH               (0x0E08483C)

  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Type_OFF               (22)
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Type_WID               ( 4)
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Type_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Subsequence_Type_HSH               (0x0416483C)

  #define REUT_CH1_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH1_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Save_Current_Base_Address_To_Start_HSH (0x011A483C)

  #define REUT_CH1_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH1_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_CTL_3_Reset_Current_Base_Address_To_Start_HSH (0x011B483C)

  #define REUT_CH1_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH1_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH1_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Data_and_ECC_Address_Inversion_HSH (0x021C483C)

  #define REUT_CH1_SUBSEQ_CTL_3_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH1_SUBSEQ_CTL_3_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH1_SUBSEQ_CTL_3_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH1_SUBSEQ_CTL_3_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_3_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Invert_Data_and_ECC_HSH            (0x011E483C)

  #define REUT_CH1_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH1_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_3_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F483C)

#define REUT_CH1_SUBSEQ_CTL_4_REG                                  (0x00004840)

  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_MIN           (0)
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_HSH           (0x07004840)

  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Number_of_Cachelines_Scale_HSH     (0x01074840)

  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Wait_WID               (14)
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Wait_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Wait_HSH               (0x0E084840)

  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Type_OFF               (22)
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Type_WID               ( 4)
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Type_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Subsequence_Type_HSH               (0x04164840)

  #define REUT_CH1_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH1_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Save_Current_Base_Address_To_Start_HSH (0x011A4840)

  #define REUT_CH1_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH1_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_CTL_4_Reset_Current_Base_Address_To_Start_HSH (0x011B4840)

  #define REUT_CH1_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH1_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH1_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Data_and_ECC_Address_Inversion_HSH (0x021C4840)

  #define REUT_CH1_SUBSEQ_CTL_4_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH1_SUBSEQ_CTL_4_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH1_SUBSEQ_CTL_4_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH1_SUBSEQ_CTL_4_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_4_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Invert_Data_and_ECC_HSH            (0x011E4840)

  #define REUT_CH1_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH1_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_4_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4840)

#define REUT_CH1_SUBSEQ_CTL_5_REG                                  (0x00004844)

  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_MIN           (0)
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_HSH           (0x07004844)

  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Number_of_Cachelines_Scale_HSH     (0x01074844)

  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Wait_WID               (14)
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Wait_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Wait_HSH               (0x0E084844)

  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Type_OFF               (22)
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Type_WID               ( 4)
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Type_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Subsequence_Type_HSH               (0x04164844)

  #define REUT_CH1_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH1_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Save_Current_Base_Address_To_Start_HSH (0x011A4844)

  #define REUT_CH1_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH1_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_CTL_5_Reset_Current_Base_Address_To_Start_HSH (0x011B4844)

  #define REUT_CH1_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH1_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH1_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Data_and_ECC_Address_Inversion_HSH (0x021C4844)

  #define REUT_CH1_SUBSEQ_CTL_5_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH1_SUBSEQ_CTL_5_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH1_SUBSEQ_CTL_5_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH1_SUBSEQ_CTL_5_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_5_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Invert_Data_and_ECC_HSH            (0x011E4844)

  #define REUT_CH1_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH1_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_5_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4844)

#define REUT_CH1_SUBSEQ_CTL_6_REG                                  (0x00004848)

  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_MIN           (0)
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_HSH           (0x07004848)

  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Number_of_Cachelines_Scale_HSH     (0x01074848)

  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Wait_WID               (14)
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Wait_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Wait_HSH               (0x0E084848)

  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Type_OFF               (22)
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Type_WID               ( 4)
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Type_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Subsequence_Type_HSH               (0x04164848)

  #define REUT_CH1_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH1_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Save_Current_Base_Address_To_Start_HSH (0x011A4848)

  #define REUT_CH1_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH1_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_CTL_6_Reset_Current_Base_Address_To_Start_HSH (0x011B4848)

  #define REUT_CH1_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH1_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH1_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Data_and_ECC_Address_Inversion_HSH (0x021C4848)

  #define REUT_CH1_SUBSEQ_CTL_6_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH1_SUBSEQ_CTL_6_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH1_SUBSEQ_CTL_6_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH1_SUBSEQ_CTL_6_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_6_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Invert_Data_and_ECC_HSH            (0x011E4848)

  #define REUT_CH1_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH1_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_6_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F4848)

#define REUT_CH1_SUBSEQ_CTL_7_REG                                  (0x0000484C)

  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_OFF           ( 0)
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_WID           ( 7)
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_MSK           (0x0000007F)
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_MIN           (0)
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_MAX           (127) // 0x0000007F
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_DEF           (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_HSH           (0x0700484C)

  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_OFF     ( 7)
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_WID     ( 1)
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_MSK     (0x00000080)
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_MIN     (0)
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Number_of_Cachelines_Scale_HSH     (0x0107484C)

  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Wait_OFF               ( 8)
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Wait_WID               (14)
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Wait_MSK               (0x003FFF00)
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Wait_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Wait_MAX               (16383) // 0x00003FFF
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Wait_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Wait_HSH               (0x0E08484C)

  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Type_OFF               (22)
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Type_WID               ( 4)
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Type_MSK               (0x03C00000)
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Type_MIN               (0)
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Type_MAX               (15) // 0x0000000F
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Type_DEF               (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Subsequence_Type_HSH               (0x0416484C)

  #define REUT_CH1_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_OFF (26)
  #define REUT_CH1_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Save_Current_Base_Address_To_Start_HSH (0x011A484C)

  #define REUT_CH1_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_OFF (27)
  #define REUT_CH1_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_MSK (0x08000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_CTL_7_Reset_Current_Base_Address_To_Start_HSH (0x011B484C)

  #define REUT_CH1_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_OFF (28)
  #define REUT_CH1_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_WID ( 2)
  #define REUT_CH1_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_MSK (0x30000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_MAX (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Data_and_ECC_Address_Inversion_HSH (0x021C484C)

  #define REUT_CH1_SUBSEQ_CTL_7_Invert_Data_and_ECC_OFF            (30)
  #define REUT_CH1_SUBSEQ_CTL_7_Invert_Data_and_ECC_WID            ( 1)
  #define REUT_CH1_SUBSEQ_CTL_7_Invert_Data_and_ECC_MSK            (0x40000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Invert_Data_and_ECC_MIN            (0)
  #define REUT_CH1_SUBSEQ_CTL_7_Invert_Data_and_ECC_MAX            (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_7_Invert_Data_and_ECC_DEF            (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Invert_Data_and_ECC_HSH            (0x011E484C)

  #define REUT_CH1_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_OFF (31)
  #define REUT_CH1_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH1_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_MSK (0x80000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH1_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_CTL_7_Stop_Base_Subsequence_On_Wrap_Trigger_HSH (0x011F484C)

#define REUT_CH0_SUBSEQ_OFFSET_CTL_0_REG                           (0x00004858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_HSH (0x05004858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_HSH (0x01054858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_WID         ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_HSH         (0x01064858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_HSH (0x05084858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_HSH   (0x01144858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_HSH    (0x01154858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_OFF      (22)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_MIN      (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_HSH      (0x01164858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_HSH  (0x01174858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_OFF  (24)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_HSH  (0x01184858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_HSH (0x01194858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_OFF (26)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_HSH (0x011A4858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_OFF     (27)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_WID     ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_MIN     (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_HSH     (0x011B4858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_OFF    (28)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_HSH    (0x011C4858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_HSH (0x011D4858)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_HSH         (0x021E4858)

#define REUT_CH0_SUBSEQ_OFFSET_CTL_1_REG                           (0x0000485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_HSH (0x0500485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_HSH (0x0105485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_WID         ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_HSH         (0x0106485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_HSH (0x0508485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_HSH (0x0110485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_HSH (0x0112485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_HSH (0x0113485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_HSH   (0x0114485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_HSH    (0x0115485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_OFF      (22)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_MIN      (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_HSH      (0x0116485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_HSH  (0x0117485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_OFF  (24)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_HSH  (0x0118485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_HSH (0x0119485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_OFF (26)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_HSH (0x011A485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_OFF     (27)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_WID     ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_MIN     (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_HSH     (0x011B485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_OFF    (28)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_HSH    (0x011C485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_HSH (0x011D485C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_HSH         (0x021E485C)

#define REUT_CH0_SUBSEQ_OFFSET_CTL_2_REG                           (0x00004860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_HSH (0x05004860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_HSH (0x01054860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_WID         ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_HSH         (0x01064860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_HSH (0x05084860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_HSH   (0x01144860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_HSH    (0x01154860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_OFF      (22)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_MIN      (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_HSH      (0x01164860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_HSH  (0x01174860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_OFF  (24)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_HSH  (0x01184860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_HSH (0x01194860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_OFF (26)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_HSH (0x011A4860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_OFF     (27)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_WID     ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_MIN     (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_HSH     (0x011B4860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_OFF    (28)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_HSH    (0x011C4860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_HSH (0x011D4860)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_HSH         (0x021E4860)

#define REUT_CH0_SUBSEQ_OFFSET_CTL_3_REG                           (0x00004864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_HSH (0x05004864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_HSH (0x01054864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_WID         ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_HSH         (0x01064864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_HSH (0x05084864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_HSH   (0x01144864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_HSH    (0x01154864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_OFF      (22)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_MIN      (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_HSH      (0x01164864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_HSH  (0x01174864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_OFF  (24)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_HSH  (0x01184864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_HSH (0x01194864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_OFF (26)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_HSH (0x011A4864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_OFF     (27)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_WID     ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_MIN     (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_HSH     (0x011B4864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_OFF    (28)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_HSH    (0x011C4864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_HSH (0x011D4864)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_HSH         (0x021E4864)

#define REUT_CH0_SUBSEQ_OFFSET_CTL_4_REG                           (0x00004868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_HSH (0x05004868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_HSH (0x01054868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_WID         ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_HSH         (0x01064868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_HSH (0x05084868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_HSH   (0x01144868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_HSH    (0x01154868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_OFF      (22)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_MIN      (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_HSH      (0x01164868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_HSH  (0x01174868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_OFF  (24)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_HSH  (0x01184868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_HSH (0x01194868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_OFF (26)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_HSH (0x011A4868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_OFF     (27)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_WID     ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_MIN     (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_HSH     (0x011B4868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_OFF    (28)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_HSH    (0x011C4868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_HSH (0x011D4868)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_HSH         (0x021E4868)

#define REUT_CH0_SUBSEQ_OFFSET_CTL_5_REG                           (0x0000486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_HSH (0x0500486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_HSH (0x0105486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_WID         ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_HSH         (0x0106486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_HSH (0x0508486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_HSH (0x0110486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_HSH (0x0112486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_HSH (0x0113486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_HSH   (0x0114486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_HSH    (0x0115486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_OFF      (22)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_MIN      (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_HSH      (0x0116486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_HSH  (0x0117486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_OFF  (24)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_HSH  (0x0118486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_HSH (0x0119486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_OFF (26)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_HSH (0x011A486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_OFF     (27)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_WID     ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_MIN     (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_HSH     (0x011B486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_OFF    (28)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_HSH    (0x011C486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_HSH (0x011D486C)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_HSH         (0x021E486C)

#define REUT_CH0_SUBSEQ_OFFSET_CTL_6_REG                           (0x00004870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_HSH (0x05004870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_HSH (0x01054870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_WID         ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_HSH         (0x01064870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_HSH (0x05084870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_HSH   (0x01144870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_HSH    (0x01154870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_OFF      (22)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_MIN      (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_HSH      (0x01164870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_HSH  (0x01174870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_OFF  (24)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_HSH  (0x01184870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_HSH (0x01194870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_OFF (26)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_HSH (0x011A4870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_OFF     (27)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_WID     ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_MIN     (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_HSH     (0x011B4870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_OFF    (28)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_HSH    (0x011C4870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_HSH (0x011D4870)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_HSH         (0x021E4870)

#define REUT_CH0_SUBSEQ_OFFSET_CTL_7_REG                           (0x00004874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_HSH (0x05004874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_HSH (0x01054874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_WID         ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_HSH         (0x01064874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_HSH (0x05084874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_HSH   (0x01144874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_HSH    (0x01154874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_OFF      (22)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_MIN      (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_HSH      (0x01164874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_HSH  (0x01174874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_OFF  (24)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_WID  ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_MIN  (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_HSH  (0x01184874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_HSH (0x01194874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_OFF (26)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_HSH (0x011A4874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_OFF     (27)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_WID     ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_MIN     (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_HSH     (0x011B4874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_OFF    (28)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_MIN    (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_HSH    (0x011C4874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_HSH (0x011D4874)

  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH0_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_HSH         (0x021E4874)

#define REUT_CH1_SUBSEQ_OFFSET_CTL_0_REG                           (0x00004880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Offset_Address_Update_Rate_HSH (0x05004880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_allow_mirror_both_sub_ch_cadb_HSH (0x01054880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_WID         ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_sub_ch_to_block_HSH         (0x01064880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Repeat_Rate_HSH (0x05084880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Subsequence_Type_HSH   (0x01144880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Deselect_Enable_HSH    (0x01154880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_OFF      (22)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_MIN      (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Select_Enable_HSH      (0x01164880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Save_Enable_HSH  (0x01174880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_OFF  (24)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Order_HSH  (0x01184880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_CADB_Seeds_Reload_Enable_HSH (0x01194880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_OFF (26)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Column_Increment_Enable_HSH (0x011A4880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_OFF     (27)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_WID     ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_MIN     (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Order_HSH     (0x011B4880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_OFF    (28)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Row_Increment_Enable_HSH    (0x011C4880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Base_Invert_Data_and_ECC_HSH (0x011D4880)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_0_Cmd_Mirror_Mode_HSH         (0x021E4880)

#define REUT_CH1_SUBSEQ_OFFSET_CTL_1_REG                           (0x00004884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Offset_Address_Update_Rate_HSH (0x05004884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_allow_mirror_both_sub_ch_cadb_HSH (0x01054884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_WID         ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_sub_ch_to_block_HSH         (0x01064884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Repeat_Rate_HSH (0x05084884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Subsequence_Type_HSH   (0x01144884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Deselect_Enable_HSH    (0x01154884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_OFF      (22)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_MIN      (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Select_Enable_HSH      (0x01164884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Save_Enable_HSH  (0x01174884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_OFF  (24)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Order_HSH  (0x01184884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_CADB_Seeds_Reload_Enable_HSH (0x01194884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_OFF (26)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Column_Increment_Enable_HSH (0x011A4884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_OFF     (27)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_WID     ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_MIN     (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Order_HSH     (0x011B4884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_OFF    (28)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Row_Increment_Enable_HSH    (0x011C4884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Base_Invert_Data_and_ECC_HSH (0x011D4884)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_1_Cmd_Mirror_Mode_HSH         (0x021E4884)

#define REUT_CH1_SUBSEQ_OFFSET_CTL_2_REG                           (0x00004888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Offset_Address_Update_Rate_HSH (0x05004888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_allow_mirror_both_sub_ch_cadb_HSH (0x01054888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_WID         ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_sub_ch_to_block_HSH         (0x01064888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Repeat_Rate_HSH (0x05084888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Subsequence_Type_HSH   (0x01144888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Deselect_Enable_HSH    (0x01154888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_OFF      (22)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_MIN      (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Select_Enable_HSH      (0x01164888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Save_Enable_HSH  (0x01174888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_OFF  (24)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Order_HSH  (0x01184888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_CADB_Seeds_Reload_Enable_HSH (0x01194888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_OFF (26)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Column_Increment_Enable_HSH (0x011A4888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_OFF     (27)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_WID     ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_MIN     (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Order_HSH     (0x011B4888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_OFF    (28)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Row_Increment_Enable_HSH    (0x011C4888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Base_Invert_Data_and_ECC_HSH (0x011D4888)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_2_Cmd_Mirror_Mode_HSH         (0x021E4888)

#define REUT_CH1_SUBSEQ_OFFSET_CTL_3_REG                           (0x0000488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Offset_Address_Update_Rate_HSH (0x0500488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_allow_mirror_both_sub_ch_cadb_HSH (0x0105488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_WID         ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_sub_ch_to_block_HSH         (0x0106488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Repeat_Rate_HSH (0x0508488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Offset_Wrap_Trigger_Enable_HSH (0x0110488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Save_Enable_HSH (0x0112488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Deselect_CADB_Seeds_Reload_Enable_HSH (0x0113488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Subsequence_Type_HSH   (0x0114488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Deselect_Enable_HSH    (0x0115488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_OFF      (22)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_MIN      (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Select_Enable_HSH      (0x0116488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Save_Enable_HSH  (0x0117488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_OFF  (24)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Order_HSH  (0x0118488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_CADB_Seeds_Reload_Enable_HSH (0x0119488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_OFF (26)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Column_Increment_Enable_HSH (0x011A488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_OFF     (27)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_WID     ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_MIN     (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Order_HSH     (0x011B488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_OFF    (28)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Row_Increment_Enable_HSH    (0x011C488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Base_Invert_Data_and_ECC_HSH (0x011D488C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_3_Cmd_Mirror_Mode_HSH         (0x021E488C)

#define REUT_CH1_SUBSEQ_OFFSET_CTL_4_REG                           (0x00004890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Offset_Address_Update_Rate_HSH (0x05004890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_allow_mirror_both_sub_ch_cadb_HSH (0x01054890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_WID         ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_sub_ch_to_block_HSH         (0x01064890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Repeat_Rate_HSH (0x05084890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Subsequence_Type_HSH   (0x01144890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Deselect_Enable_HSH    (0x01154890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_OFF      (22)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_MIN      (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Select_Enable_HSH      (0x01164890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Save_Enable_HSH  (0x01174890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_OFF  (24)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Order_HSH  (0x01184890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_CADB_Seeds_Reload_Enable_HSH (0x01194890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_OFF (26)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Column_Increment_Enable_HSH (0x011A4890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_OFF     (27)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_WID     ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_MIN     (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Order_HSH     (0x011B4890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_OFF    (28)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Row_Increment_Enable_HSH    (0x011C4890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Base_Invert_Data_and_ECC_HSH (0x011D4890)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_4_Cmd_Mirror_Mode_HSH         (0x021E4890)

#define REUT_CH1_SUBSEQ_OFFSET_CTL_5_REG                           (0x00004894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Offset_Address_Update_Rate_HSH (0x05004894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_allow_mirror_both_sub_ch_cadb_HSH (0x01054894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_WID         ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_sub_ch_to_block_HSH         (0x01064894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Repeat_Rate_HSH (0x05084894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Subsequence_Type_HSH   (0x01144894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Deselect_Enable_HSH    (0x01154894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_OFF      (22)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_MIN      (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Select_Enable_HSH      (0x01164894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Save_Enable_HSH  (0x01174894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_OFF  (24)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Order_HSH  (0x01184894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_CADB_Seeds_Reload_Enable_HSH (0x01194894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_OFF (26)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Column_Increment_Enable_HSH (0x011A4894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_OFF     (27)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_WID     ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_MIN     (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Order_HSH     (0x011B4894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_OFF    (28)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Row_Increment_Enable_HSH    (0x011C4894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Base_Invert_Data_and_ECC_HSH (0x011D4894)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_5_Cmd_Mirror_Mode_HSH         (0x021E4894)

#define REUT_CH1_SUBSEQ_OFFSET_CTL_6_REG                           (0x00004898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Offset_Address_Update_Rate_HSH (0x05004898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_allow_mirror_both_sub_ch_cadb_HSH (0x01054898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_WID         ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_sub_ch_to_block_HSH         (0x01064898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Repeat_Rate_HSH (0x05084898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F4898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Offset_Wrap_Trigger_Enable_HSH (0x01104898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Save_Enable_HSH (0x01124898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Deselect_CADB_Seeds_Reload_Enable_HSH (0x01134898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Subsequence_Type_HSH   (0x01144898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Deselect_Enable_HSH    (0x01154898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_OFF      (22)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_MIN      (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Select_Enable_HSH      (0x01164898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Save_Enable_HSH  (0x01174898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_OFF  (24)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Order_HSH  (0x01184898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_CADB_Seeds_Reload_Enable_HSH (0x01194898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_OFF (26)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Column_Increment_Enable_HSH (0x011A4898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_OFF     (27)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_WID     ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_MIN     (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Order_HSH     (0x011B4898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_OFF    (28)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Row_Increment_Enable_HSH    (0x011C4898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Base_Invert_Data_and_ECC_HSH (0x011D4898)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_6_Cmd_Mirror_Mode_HSH         (0x021E4898)

#define REUT_CH1_SUBSEQ_OFFSET_CTL_7_REG                           (0x0000489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_OFF ( 0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_MSK (0x0000001F)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Offset_Address_Update_Rate_HSH (0x0500489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_OFF ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_MSK (0x00000020)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_allow_mirror_both_sub_ch_cadb_HSH (0x0105489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_OFF         ( 6)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_WID         ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_MSK         (0x00000040)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_MAX         (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_sub_ch_to_block_HSH         (0x0106489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_OFF ( 8)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_WID ( 5)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_MSK (0x00001F00)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_MAX (31) // 0x0000001F
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_DEF (0x00000002)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Repeat_Rate_HSH (0x0508489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_OFF (15)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_MSK (0x00008000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Offset_Wrap_Trigger_Enable_HSH (0x010F489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_OFF (16)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_MSK (0x00010000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_DEF (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Offset_Wrap_Trigger_Enable_HSH (0x0110489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_OFF (18)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_MSK (0x00040000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Save_Enable_HSH (0x0112489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_OFF (19)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_MSK (0x00080000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Deselect_CADB_Seeds_Reload_Enable_HSH (0x0113489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_OFF   (20)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_WID   ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_MSK   (0x00100000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_MIN   (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_MAX   (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_DEF   (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Subsequence_Type_HSH   (0x0114489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_OFF    (21)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_MSK    (0x00200000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_DEF    (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Deselect_Enable_HSH    (0x0115489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_OFF      (22)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_WID      ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_MSK      (0x00400000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_MIN      (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_MAX      (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_DEF      (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Select_Enable_HSH      (0x0116489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_OFF  (23)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_MSK  (0x00800000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_DEF  (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Save_Enable_HSH  (0x0117489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_OFF  (24)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_WID  ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_MSK  (0x01000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_MIN  (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_MAX  (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_DEF  (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Order_HSH  (0x0118489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_OFF (25)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_MSK (0x02000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_CADB_Seeds_Reload_Enable_HSH (0x0119489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_OFF (26)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_MSK (0x04000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Column_Increment_Enable_HSH (0x011A489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_OFF     (27)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_WID     ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_MSK     (0x08000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_MIN     (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_MAX     (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_DEF     (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Order_HSH     (0x011B489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_OFF    (28)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_WID    ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_MSK    (0x10000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_MIN    (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_MAX    (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_DEF    (0x00000001)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Row_Increment_Enable_HSH    (0x011C489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_OFF (29)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_WID ( 1)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_MSK (0x20000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_MIN (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_MAX (1) // 0x00000001
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_DEF (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Base_Invert_Data_and_ECC_HSH (0x011D489C)

  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_OFF         (30)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_WID         ( 2)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_MSK         (0xC0000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_MIN         (0)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_MAX         (3) // 0x00000003
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_DEF         (0x00000000)
  #define REUT_CH1_SUBSEQ_OFFSET_CTL_7_Cmd_Mirror_Mode_HSH         (0x021E489C)

#define REUT_CH_SEQ_CFG_0_REG                                      (0x000048A8)

  #define REUT_CH_SEQ_CFG_0_Stop_Base_Sequence_On_Wrap_Trigger_OFF ( 3)
  #define REUT_CH_SEQ_CFG_0_Stop_Base_Sequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH_SEQ_CFG_0_Stop_Base_Sequence_On_Wrap_Trigger_MSK (0x00000008)
  #define REUT_CH_SEQ_CFG_0_Stop_Base_Sequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH_SEQ_CFG_0_Stop_Base_Sequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_0_Stop_Base_Sequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH_SEQ_CFG_0_Stop_Base_Sequence_On_Wrap_Trigger_HSH (0x410348A8)

  #define REUT_CH_SEQ_CFG_0_Address_Update_Rate_Mode_OFF           ( 5)
  #define REUT_CH_SEQ_CFG_0_Address_Update_Rate_Mode_WID           ( 1)
  #define REUT_CH_SEQ_CFG_0_Address_Update_Rate_Mode_MSK           (0x00000020)
  #define REUT_CH_SEQ_CFG_0_Address_Update_Rate_Mode_MIN           (0)
  #define REUT_CH_SEQ_CFG_0_Address_Update_Rate_Mode_MAX           (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_0_Address_Update_Rate_Mode_DEF           (0x00000000)
  #define REUT_CH_SEQ_CFG_0_Address_Update_Rate_Mode_HSH           (0x410548A8)

  #define REUT_CH_SEQ_CFG_0_Enable_Dummy_Reads_OFF_A0           ( 7)
  #define REUT_CH_SEQ_CFG_0_Enable_Dummy_Reads_WID_A0           ( 1)
  #define REUT_CH_SEQ_CFG_0_Enable_Dummy_Reads_MSK_A0           (0x00000080)
  #define REUT_CH_SEQ_CFG_0_Enable_Dummy_Reads_MIN_A0           (0)
  #define REUT_CH_SEQ_CFG_0_Enable_Dummy_Reads_MAX_A0           (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_0_Enable_Dummy_Reads_DEF_A0           (0x00000000)
  #define REUT_CH_SEQ_CFG_0_Enable_Dummy_Reads_HSH_A0           (0x410748A8)

  #define REUT_CH_SEQ_CFG_0_REUT_AllowOpp_Refresh_OFF           ( 9)
  #define REUT_CH_SEQ_CFG_0_REUT_AllowOpp_Refresh_WID           ( 1)
  #define REUT_CH_SEQ_CFG_0_REUT_AllowOpp_Refresh_MSK           (0x00000200)
  #define REUT_CH_SEQ_CFG_0_REUT_AllowOpp_Refresh_MIN           (0)
  #define REUT_CH_SEQ_CFG_0_REUT_AllowOpp_Refresh_MAX           (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_0_REUT_AllowOpp_Refresh_DEF           (0x00000000)
  #define REUT_CH_SEQ_CFG_0_REUT_AllowOpp_Refresh_HSH           (0x410948A8)

  #define REUT_CH_SEQ_CFG_0_Global_Control_OFF                     (11)
  #define REUT_CH_SEQ_CFG_0_Global_Control_WID                     ( 1)
  #define REUT_CH_SEQ_CFG_0_Global_Control_MSK                     (0x00000800)
  #define REUT_CH_SEQ_CFG_0_Global_Control_MIN                     (0)
  #define REUT_CH_SEQ_CFG_0_Global_Control_MAX                     (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_0_Global_Control_DEF                     (0x00000000)
  #define REUT_CH_SEQ_CFG_0_Global_Control_HSH                     (0x410B48A8)

  #define REUT_CH_SEQ_CFG_0_Initialization_Mode_OFF                (12)
  #define REUT_CH_SEQ_CFG_0_Initialization_Mode_WID                ( 2)
  #define REUT_CH_SEQ_CFG_0_Initialization_Mode_MSK                (0x00003000)
  #define REUT_CH_SEQ_CFG_0_Initialization_Mode_MIN                (0)
  #define REUT_CH_SEQ_CFG_0_Initialization_Mode_MAX                (3) // 0x00000003
  #define REUT_CH_SEQ_CFG_0_Initialization_Mode_DEF                (0x00000000)
  #define REUT_CH_SEQ_CFG_0_Initialization_Mode_HSH                (0x420C48A8)

  #define REUT_CH_SEQ_CFG_0_Subsequence_Start_Pointer_OFF          (24)
  #define REUT_CH_SEQ_CFG_0_Subsequence_Start_Pointer_WID          ( 3)
  #define REUT_CH_SEQ_CFG_0_Subsequence_Start_Pointer_MSK          (0x07000000)
  #define REUT_CH_SEQ_CFG_0_Subsequence_Start_Pointer_MIN          (0)
  #define REUT_CH_SEQ_CFG_0_Subsequence_Start_Pointer_MAX          (7) // 0x00000007
  #define REUT_CH_SEQ_CFG_0_Subsequence_Start_Pointer_DEF          (0x00000000)
  #define REUT_CH_SEQ_CFG_0_Subsequence_Start_Pointer_HSH          (0x431848A8)

  #define REUT_CH_SEQ_CFG_0_Subsequence_End_Pointer_OFF            (28)
  #define REUT_CH_SEQ_CFG_0_Subsequence_End_Pointer_WID            ( 3)
  #define REUT_CH_SEQ_CFG_0_Subsequence_End_Pointer_MSK            (0x70000000)
  #define REUT_CH_SEQ_CFG_0_Subsequence_End_Pointer_MIN            (0)
  #define REUT_CH_SEQ_CFG_0_Subsequence_End_Pointer_MAX            (7) // 0x00000007
  #define REUT_CH_SEQ_CFG_0_Subsequence_End_Pointer_DEF            (0x00000001)
  #define REUT_CH_SEQ_CFG_0_Subsequence_End_Pointer_HSH            (0x431C48A8)

  #define REUT_CH_SEQ_CFG_0_Start_Test_Delay_OFF                   (32)
  #define REUT_CH_SEQ_CFG_0_Start_Test_Delay_WID                   (10)
  #define REUT_CH_SEQ_CFG_0_Start_Test_Delay_MSK                   (0x000003FF00000000ULL)
  #define REUT_CH_SEQ_CFG_0_Start_Test_Delay_MIN                   (0)
  #define REUT_CH_SEQ_CFG_0_Start_Test_Delay_MAX                   (1023) // 0x000003FF
  #define REUT_CH_SEQ_CFG_0_Start_Test_Delay_DEF                   (0x00000000)
  #define REUT_CH_SEQ_CFG_0_Start_Test_Delay_HSH                   (0x4A2048A8)

  #define REUT_CH_SEQ_CFG_0_SubSequence_Cacheline_Counter_Mode_OFF (48)
  #define REUT_CH_SEQ_CFG_0_SubSequence_Cacheline_Counter_Mode_WID ( 1)
  #define REUT_CH_SEQ_CFG_0_SubSequence_Cacheline_Counter_Mode_MSK (0x0001000000000000ULL)
  #define REUT_CH_SEQ_CFG_0_SubSequence_Cacheline_Counter_Mode_MIN (0)
  #define REUT_CH_SEQ_CFG_0_SubSequence_Cacheline_Counter_Mode_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_0_SubSequence_Cacheline_Counter_Mode_DEF (0x00000000)
  #define REUT_CH_SEQ_CFG_0_SubSequence_Cacheline_Counter_Mode_HSH (0x413048A8)

#define REUT_CH_SEQ_CFG_1_REG                                      (0x000048B0)

  #define REUT_CH_SEQ_CFG_1_Stop_Base_Sequence_On_Wrap_Trigger_OFF ( 3)
  #define REUT_CH_SEQ_CFG_1_Stop_Base_Sequence_On_Wrap_Trigger_WID ( 1)
  #define REUT_CH_SEQ_CFG_1_Stop_Base_Sequence_On_Wrap_Trigger_MSK (0x00000008)
  #define REUT_CH_SEQ_CFG_1_Stop_Base_Sequence_On_Wrap_Trigger_MIN (0)
  #define REUT_CH_SEQ_CFG_1_Stop_Base_Sequence_On_Wrap_Trigger_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_1_Stop_Base_Sequence_On_Wrap_Trigger_DEF (0x00000000)
  #define REUT_CH_SEQ_CFG_1_Stop_Base_Sequence_On_Wrap_Trigger_HSH (0x410348B0)

  #define REUT_CH_SEQ_CFG_1_Address_Update_Rate_Mode_OFF           ( 5)
  #define REUT_CH_SEQ_CFG_1_Address_Update_Rate_Mode_WID           ( 1)
  #define REUT_CH_SEQ_CFG_1_Address_Update_Rate_Mode_MSK           (0x00000020)
  #define REUT_CH_SEQ_CFG_1_Address_Update_Rate_Mode_MIN           (0)
  #define REUT_CH_SEQ_CFG_1_Address_Update_Rate_Mode_MAX           (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_1_Address_Update_Rate_Mode_DEF           (0x00000000)
  #define REUT_CH_SEQ_CFG_1_Address_Update_Rate_Mode_HSH           (0x410548B0)

  #define REUT_CH_SEQ_CFG_1_Enable_Dummy_Reads_OFF_A0           ( 7)
  #define REUT_CH_SEQ_CFG_1_Enable_Dummy_Reads_WID_A0           ( 1)
  #define REUT_CH_SEQ_CFG_1_Enable_Dummy_Reads_MSK_A0           (0x00000080)
  #define REUT_CH_SEQ_CFG_1_Enable_Dummy_Reads_MIN_A0           (0)
  #define REUT_CH_SEQ_CFG_1_Enable_Dummy_Reads_MAX_A0           (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_1_Enable_Dummy_Reads_DEF_A0           (0x00000000)
  #define REUT_CH_SEQ_CFG_1_Enable_Dummy_Reads_HSH_A0           (0x410748B0)

  #define REUT_CH_SEQ_CFG_1_REUT_AllowOpp_Refresh_OFF           ( 9)
  #define REUT_CH_SEQ_CFG_1_REUT_AllowOpp_Refresh_WID           ( 1)
  #define REUT_CH_SEQ_CFG_1_REUT_AllowOpp_Refresh_MSK           (0x00000200)
  #define REUT_CH_SEQ_CFG_1_REUT_AllowOpp_Refresh_MIN           (0)
  #define REUT_CH_SEQ_CFG_1_REUT_AllowOpp_Refresh_MAX           (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_1_REUT_AllowOpp_Refresh_DEF           (0x00000000)
  #define REUT_CH_SEQ_CFG_1_REUT_AllowOpp_Refresh_HSH           (0x410948B0)

  #define REUT_CH_SEQ_CFG_1_Global_Control_OFF                     (11)
  #define REUT_CH_SEQ_CFG_1_Global_Control_WID                     ( 1)
  #define REUT_CH_SEQ_CFG_1_Global_Control_MSK                     (0x00000800)
  #define REUT_CH_SEQ_CFG_1_Global_Control_MIN                     (0)
  #define REUT_CH_SEQ_CFG_1_Global_Control_MAX                     (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_1_Global_Control_DEF                     (0x00000000)
  #define REUT_CH_SEQ_CFG_1_Global_Control_HSH                     (0x410B48B0)

  #define REUT_CH_SEQ_CFG_1_Initialization_Mode_OFF                (12)
  #define REUT_CH_SEQ_CFG_1_Initialization_Mode_WID                ( 2)
  #define REUT_CH_SEQ_CFG_1_Initialization_Mode_MSK                (0x00003000)
  #define REUT_CH_SEQ_CFG_1_Initialization_Mode_MIN                (0)
  #define REUT_CH_SEQ_CFG_1_Initialization_Mode_MAX                (3) // 0x00000003
  #define REUT_CH_SEQ_CFG_1_Initialization_Mode_DEF                (0x00000000)
  #define REUT_CH_SEQ_CFG_1_Initialization_Mode_HSH                (0x420C48B0)

  #define REUT_CH_SEQ_CFG_1_Subsequence_Start_Pointer_OFF          (24)
  #define REUT_CH_SEQ_CFG_1_Subsequence_Start_Pointer_WID          ( 3)
  #define REUT_CH_SEQ_CFG_1_Subsequence_Start_Pointer_MSK          (0x07000000)
  #define REUT_CH_SEQ_CFG_1_Subsequence_Start_Pointer_MIN          (0)
  #define REUT_CH_SEQ_CFG_1_Subsequence_Start_Pointer_MAX          (7) // 0x00000007
  #define REUT_CH_SEQ_CFG_1_Subsequence_Start_Pointer_DEF          (0x00000000)
  #define REUT_CH_SEQ_CFG_1_Subsequence_Start_Pointer_HSH          (0x431848B0)

  #define REUT_CH_SEQ_CFG_1_Subsequence_End_Pointer_OFF            (28)
  #define REUT_CH_SEQ_CFG_1_Subsequence_End_Pointer_WID            ( 3)
  #define REUT_CH_SEQ_CFG_1_Subsequence_End_Pointer_MSK            (0x70000000)
  #define REUT_CH_SEQ_CFG_1_Subsequence_End_Pointer_MIN            (0)
  #define REUT_CH_SEQ_CFG_1_Subsequence_End_Pointer_MAX            (7) // 0x00000007
  #define REUT_CH_SEQ_CFG_1_Subsequence_End_Pointer_DEF            (0x00000001)
  #define REUT_CH_SEQ_CFG_1_Subsequence_End_Pointer_HSH            (0x431C48B0)

  #define REUT_CH_SEQ_CFG_1_Start_Test_Delay_OFF                   (32)
  #define REUT_CH_SEQ_CFG_1_Start_Test_Delay_WID                   (10)
  #define REUT_CH_SEQ_CFG_1_Start_Test_Delay_MSK                   (0x000003FF00000000ULL)
  #define REUT_CH_SEQ_CFG_1_Start_Test_Delay_MIN                   (0)
  #define REUT_CH_SEQ_CFG_1_Start_Test_Delay_MAX                   (1023) // 0x000003FF
  #define REUT_CH_SEQ_CFG_1_Start_Test_Delay_DEF                   (0x00000000)
  #define REUT_CH_SEQ_CFG_1_Start_Test_Delay_HSH                   (0x4A2048B0)

  #define REUT_CH_SEQ_CFG_1_SubSequence_Cacheline_Counter_Mode_OFF (48)
  #define REUT_CH_SEQ_CFG_1_SubSequence_Cacheline_Counter_Mode_WID ( 1)
  #define REUT_CH_SEQ_CFG_1_SubSequence_Cacheline_Counter_Mode_MSK (0x0001000000000000ULL)
  #define REUT_CH_SEQ_CFG_1_SubSequence_Cacheline_Counter_Mode_MIN (0)
  #define REUT_CH_SEQ_CFG_1_SubSequence_Cacheline_Counter_Mode_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_CFG_1_SubSequence_Cacheline_Counter_Mode_DEF (0x00000000)
  #define REUT_CH_SEQ_CFG_1_SubSequence_Cacheline_Counter_Mode_HSH (0x413048B0)

#define REUT_CH_SEQ_CTL_0_REG                                      (0x000048B8)

  #define REUT_CH_SEQ_CTL_0_Local_Start_Test_OFF                   ( 0)
  #define REUT_CH_SEQ_CTL_0_Local_Start_Test_WID                   ( 1)
  #define REUT_CH_SEQ_CTL_0_Local_Start_Test_MSK                   (0x00000001)
  #define REUT_CH_SEQ_CTL_0_Local_Start_Test_MIN                   (0)
  #define REUT_CH_SEQ_CTL_0_Local_Start_Test_MAX                   (1) // 0x00000001
  #define REUT_CH_SEQ_CTL_0_Local_Start_Test_DEF                   (0x00000000)
  #define REUT_CH_SEQ_CTL_0_Local_Start_Test_HSH                   (0x010048B8)

  #define REUT_CH_SEQ_CTL_0_Local_Stop_Test_OFF                    ( 1)
  #define REUT_CH_SEQ_CTL_0_Local_Stop_Test_WID                    ( 1)
  #define REUT_CH_SEQ_CTL_0_Local_Stop_Test_MSK                    (0x00000002)
  #define REUT_CH_SEQ_CTL_0_Local_Stop_Test_MIN                    (0)
  #define REUT_CH_SEQ_CTL_0_Local_Stop_Test_MAX                    (1) // 0x00000001
  #define REUT_CH_SEQ_CTL_0_Local_Stop_Test_DEF                    (0x00000000)
  #define REUT_CH_SEQ_CTL_0_Local_Stop_Test_HSH                    (0x010148B8)

  #define REUT_CH_SEQ_CTL_0_Local_Clear_Errors_OFF                 ( 2)
  #define REUT_CH_SEQ_CTL_0_Local_Clear_Errors_WID                 ( 1)
  #define REUT_CH_SEQ_CTL_0_Local_Clear_Errors_MSK                 (0x00000004)
  #define REUT_CH_SEQ_CTL_0_Local_Clear_Errors_MIN                 (0)
  #define REUT_CH_SEQ_CTL_0_Local_Clear_Errors_MAX                 (1) // 0x00000001
  #define REUT_CH_SEQ_CTL_0_Local_Clear_Errors_DEF                 (0x00000000)
  #define REUT_CH_SEQ_CTL_0_Local_Clear_Errors_HSH                 (0x010248B8)

#define REUT_CH_SEQ_CTL_1_REG                                      (0x000048BC)

  #define REUT_CH_SEQ_CTL_1_Local_Start_Test_OFF                   ( 0)
  #define REUT_CH_SEQ_CTL_1_Local_Start_Test_WID                   ( 1)
  #define REUT_CH_SEQ_CTL_1_Local_Start_Test_MSK                   (0x00000001)
  #define REUT_CH_SEQ_CTL_1_Local_Start_Test_MIN                   (0)
  #define REUT_CH_SEQ_CTL_1_Local_Start_Test_MAX                   (1) // 0x00000001
  #define REUT_CH_SEQ_CTL_1_Local_Start_Test_DEF                   (0x00000000)
  #define REUT_CH_SEQ_CTL_1_Local_Start_Test_HSH                   (0x010048BC)

  #define REUT_CH_SEQ_CTL_1_Local_Stop_Test_OFF                    ( 1)
  #define REUT_CH_SEQ_CTL_1_Local_Stop_Test_WID                    ( 1)
  #define REUT_CH_SEQ_CTL_1_Local_Stop_Test_MSK                    (0x00000002)
  #define REUT_CH_SEQ_CTL_1_Local_Stop_Test_MIN                    (0)
  #define REUT_CH_SEQ_CTL_1_Local_Stop_Test_MAX                    (1) // 0x00000001
  #define REUT_CH_SEQ_CTL_1_Local_Stop_Test_DEF                    (0x00000000)
  #define REUT_CH_SEQ_CTL_1_Local_Stop_Test_HSH                    (0x010148BC)

  #define REUT_CH_SEQ_CTL_1_Local_Clear_Errors_OFF                 ( 2)
  #define REUT_CH_SEQ_CTL_1_Local_Clear_Errors_WID                 ( 1)
  #define REUT_CH_SEQ_CTL_1_Local_Clear_Errors_MSK                 (0x00000004)
  #define REUT_CH_SEQ_CTL_1_Local_Clear_Errors_MIN                 (0)
  #define REUT_CH_SEQ_CTL_1_Local_Clear_Errors_MAX                 (1) // 0x00000001
  #define REUT_CH_SEQ_CTL_1_Local_Clear_Errors_DEF                 (0x00000000)
  #define REUT_CH_SEQ_CTL_1_Local_Clear_Errors_HSH                 (0x010248BC)

#define REUT_CH_SEQ_LOOPCOUNT_STATUS_0_REG                         (0x000048C0)

  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_0_Current_Loopcount_OFF     ( 0)
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_0_Current_Loopcount_WID     (32)
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_0_Current_Loopcount_MSK     (0xFFFFFFFF)
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_0_Current_Loopcount_MIN     (0)
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_0_Current_Loopcount_MAX     (4294967295) // 0xFFFFFFFF
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_0_Current_Loopcount_DEF     (0x00000000)
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_0_Current_Loopcount_HSH     (0x200048C0)

#define REUT_CH_SEQ_LOOPCOUNT_STATUS_1_REG                         (0x000048C4)

  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_1_Current_Loopcount_OFF     ( 0)
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_1_Current_Loopcount_WID     (32)
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_1_Current_Loopcount_MSK     (0xFFFFFFFF)
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_1_Current_Loopcount_MIN     (0)
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_1_Current_Loopcount_MAX     (4294967295) // 0xFFFFFFFF
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_1_Current_Loopcount_DEF     (0x00000000)
  #define REUT_CH_SEQ_LOOPCOUNT_STATUS_1_Current_Loopcount_HSH     (0x200048C4)

#define REUT_CH_SEQ_SUBSEQ_PNTR_0_REG                              (0x000048C8)

  #define REUT_CH_SEQ_SUBSEQ_PNTR_0_Current_Subsequence_Pointer_OFF ( 0)
  #define REUT_CH_SEQ_SUBSEQ_PNTR_0_Current_Subsequence_Pointer_WID ( 3)
  #define REUT_CH_SEQ_SUBSEQ_PNTR_0_Current_Subsequence_Pointer_MSK (0x00000007)
  #define REUT_CH_SEQ_SUBSEQ_PNTR_0_Current_Subsequence_Pointer_MIN (0)
  #define REUT_CH_SEQ_SUBSEQ_PNTR_0_Current_Subsequence_Pointer_MAX (7) // 0x00000007
  #define REUT_CH_SEQ_SUBSEQ_PNTR_0_Current_Subsequence_Pointer_DEF (0x00000000)
  #define REUT_CH_SEQ_SUBSEQ_PNTR_0_Current_Subsequence_Pointer_HSH (0x030048C8)

#define REUT_CH_SEQ_SUBSEQ_PNTR_1_REG                              (0x000048CC)

  #define REUT_CH_SEQ_SUBSEQ_PNTR_1_Current_Subsequence_Pointer_OFF ( 0)
  #define REUT_CH_SEQ_SUBSEQ_PNTR_1_Current_Subsequence_Pointer_WID ( 3)
  #define REUT_CH_SEQ_SUBSEQ_PNTR_1_Current_Subsequence_Pointer_MSK (0x00000007)
  #define REUT_CH_SEQ_SUBSEQ_PNTR_1_Current_Subsequence_Pointer_MIN (0)
  #define REUT_CH_SEQ_SUBSEQ_PNTR_1_Current_Subsequence_Pointer_MAX (7) // 0x00000007
  #define REUT_CH_SEQ_SUBSEQ_PNTR_1_Current_Subsequence_Pointer_DEF (0x00000000)
  #define REUT_CH_SEQ_SUBSEQ_PNTR_1_Current_Subsequence_Pointer_HSH (0x030048CC)

#define REUT_CH_SEQ_CACHELINE_STATUS_0_REG                         (0x000048D0)

  #define REUT_CH_SEQ_CACHELINE_STATUS_0_Current_Cacheline_OFF     ( 0)
  #define REUT_CH_SEQ_CACHELINE_STATUS_0_Current_Cacheline_WID     (16)
  #define REUT_CH_SEQ_CACHELINE_STATUS_0_Current_Cacheline_MSK     (0x0000FFFF)
  #define REUT_CH_SEQ_CACHELINE_STATUS_0_Current_Cacheline_MIN     (0)
  #define REUT_CH_SEQ_CACHELINE_STATUS_0_Current_Cacheline_MAX     (65535) // 0x0000FFFF
  #define REUT_CH_SEQ_CACHELINE_STATUS_0_Current_Cacheline_DEF     (0x00000000)
  #define REUT_CH_SEQ_CACHELINE_STATUS_0_Current_Cacheline_HSH     (0x100048D0)

#define REUT_CH_SEQ_CACHELINE_STATUS_1_REG                         (0x000048D4)

  #define REUT_CH_SEQ_CACHELINE_STATUS_1_Current_Cacheline_OFF     ( 0)
  #define REUT_CH_SEQ_CACHELINE_STATUS_1_Current_Cacheline_WID     (16)
  #define REUT_CH_SEQ_CACHELINE_STATUS_1_Current_Cacheline_MSK     (0x0000FFFF)
  #define REUT_CH_SEQ_CACHELINE_STATUS_1_Current_Cacheline_MIN     (0)
  #define REUT_CH_SEQ_CACHELINE_STATUS_1_Current_Cacheline_MAX     (65535) // 0x0000FFFF
  #define REUT_CH_SEQ_CACHELINE_STATUS_1_Current_Cacheline_DEF     (0x00000000)
  #define REUT_CH_SEQ_CACHELINE_STATUS_1_Current_Cacheline_HSH     (0x100048D4)

#define REUT_CH_SEQ_BASE_ADDR_START_0_REG                          (0x000048D8)

  #define REUT_CH_SEQ_BASE_ADDR_START_0_Column_Address_OFF         ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Column_Address_WID         ( 9)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Column_Address_MSK         (0x00000FF8)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Column_Address_MIN         (0)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Column_Address_MAX         (511) // 0x000001FF
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Column_Address_DEF         (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Column_Address_HSH         (0x490348D8)

  #define REUT_CH_SEQ_BASE_ADDR_START_0_Row_Address_OFF            (12)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Row_Address_WID            (17)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Row_Address_MSK            (0x1FFFF000)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Row_Address_MIN            (0)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Row_Address_MAX            (131071) // 0x0001FFFF
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Row_Address_DEF            (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Row_Address_HSH            (0x510C48D8)

  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_OFF           (48)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_WID           ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_MSK           (0x001F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_WID_A0        ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_MSK_A0        (0x000F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_MIN           (0)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_MAX           (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_MAX_A0        (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_DEF           (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_HSH           (0x453048D8)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Bank_Address_HSH_A0        (0x443048D8)

  #define REUT_CH_SEQ_BASE_ADDR_START_0_Rank_Address_OFF           (56)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Rank_Address_WID           ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Rank_Address_MSK           (0x0700000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Rank_Address_MIN           (0)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Rank_Address_MAX           (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Rank_Address_DEF           (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_START_0_Rank_Address_HSH           (0x433848D8)

#define REUT_CH_SEQ_BASE_ADDR_START_1_REG                          (0x000048E0)

  #define REUT_CH_SEQ_BASE_ADDR_START_1_Column_Address_OFF         ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Column_Address_WID         ( 9)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Column_Address_MSK         (0x00000FF8)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Column_Address_MIN         (0)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Column_Address_MAX         (511) // 0x000001FF
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Column_Address_DEF         (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Column_Address_HSH         (0x490348E0)

  #define REUT_CH_SEQ_BASE_ADDR_START_1_Row_Address_OFF            (12)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Row_Address_WID            (17)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Row_Address_MSK            (0x1FFFF000)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Row_Address_MIN            (0)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Row_Address_MAX            (131071) // 0x0001FFFF
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Row_Address_DEF            (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Row_Address_HSH            (0x510C48E0)

  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_OFF           (48)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_WID           ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_MSK           (0x001F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_WID_A0        ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_MSK_A0        (0x000F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_MIN           (0)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_MAX           (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_MAX_A0        (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_DEF           (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_HSH           (0x453048E0)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Bank_Address_HSH_A0        (0x443048E0)

  #define REUT_CH_SEQ_BASE_ADDR_START_1_Rank_Address_OFF           (56)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Rank_Address_WID           ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Rank_Address_MSK           (0x0700000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Rank_Address_MIN           (0)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Rank_Address_MAX           (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Rank_Address_DEF           (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_START_1_Rank_Address_HSH           (0x433848E0)

#define REUT_CH_SEQ_BASE_ADDR_WRAP_0_REG                           (0x000048E8)

  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Column_Address_OFF          ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Column_Address_WID          ( 9)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Column_Address_MSK          (0x00000FF8)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Column_Address_MIN          (0)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Column_Address_MAX          (511) // 0x000001FF
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Column_Address_DEF          (0x000000FF)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Column_Address_HSH          (0x490348E8)

  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Row_Address_OFF             (12)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Row_Address_WID             (18)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Row_Address_MSK             (0x3FFFF000)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Row_Address_MIN             (0)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Row_Address_MAX             (262143) // 0x0003FFFF
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Row_Address_DEF             (0x0000FFFF)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Row_Address_HSH             (0x520C48E8)

  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_OFF            (48)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_WID            ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_MSK            (0x001F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_WID_A0         ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_MSK_A0         (0x000F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_MIN            (0)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_MAX            (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_MAX_A0         (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_DEF            (0x00000007)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_HSH            (0x453048E8)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Bank_Address_HSH_A0         (0x443048E8)

  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Rank_Address_OFF            (56)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Rank_Address_WID            ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Rank_Address_MSK            (0x0700000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Rank_Address_MIN            (0)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Rank_Address_MAX            (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Rank_Address_DEF            (0x00000007)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_0_Rank_Address_HSH            (0x433848E8)

#define REUT_CH_SEQ_BASE_ADDR_WRAP_1_REG                           (0x000048F0)

  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Column_Address_OFF          ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Column_Address_WID          ( 9)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Column_Address_MSK          (0x00000FF8)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Column_Address_MIN          (0)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Column_Address_MAX          (511) // 0x000001FF
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Column_Address_DEF          (0x000000FF)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Column_Address_HSH          (0x490348F0)

  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Row_Address_OFF             (12)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Row_Address_WID             (18)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Row_Address_MSK             (0x3FFFF000)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Row_Address_MIN             (0)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Row_Address_MAX             (262143) // 0x0003FFFF
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Row_Address_DEF             (0x0000FFFF)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Row_Address_HSH             (0x520C48F0)

  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_OFF            (48)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_WID            ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_MSK            (0x001F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_WID_A0         ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_MSK_A0         (0x000F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_MIN            (0)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_MAX            (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_MAX_A0         (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_DEF            (0x00000007)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_HSH            (0x453048F0)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Bank_Address_HSH_A0         (0x443048F0)

  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Rank_Address_OFF            (56)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Rank_Address_WID            ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Rank_Address_MSK            (0x0700000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Rank_Address_MIN            (0)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Rank_Address_MAX            (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Rank_Address_DEF            (0x00000007)
  #define REUT_CH_SEQ_BASE_ADDR_WRAP_1_Rank_Address_HSH            (0x433848F0)

#define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_REG                        (0x000048F8)

  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Column_Address_OFF       ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Column_Address_WID       ( 9)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Column_Address_MSK       (0x00000FF8)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Column_Address_MIN       (0)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Column_Address_MAX       (511) // 0x000001FF
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Column_Address_DEF       (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Column_Address_HSH       (0x490348F8)

  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Row_Address_OFF          (12)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Row_Address_WID          (17)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Row_Address_MSK          (0x1FFFF000)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Row_Address_MIN          (0)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Row_Address_MAX          (131071) // 0x0001FFFF
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Row_Address_DEF          (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Row_Address_HSH          (0x510C48F8)

  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_OFF         (48)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_WID         ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_MSK         (0x001F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_WID_A0      ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_MSK_A0      (0x000F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_MIN         (0)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_MAX         (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_MAX_A0      (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_DEF         (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_HSH         (0x453048F8)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Bank_Address_HSH_A0      (0x443048F8)

  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Rank_Address_OFF         (56)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Rank_Address_WID         ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Rank_Address_MSK         (0x0700000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Rank_Address_MIN         (0)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Rank_Address_MAX         (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Rank_Address_DEF         (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_0_Rank_Address_HSH         (0x433848F8)

#define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_REG                        (0x00004900)

  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Column_Address_OFF       ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Column_Address_WID       ( 9)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Column_Address_MSK       (0x00000FF8)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Column_Address_MIN       (0)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Column_Address_MAX       (511) // 0x000001FF
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Column_Address_DEF       (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Column_Address_HSH       (0x49034900)

  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Row_Address_OFF          (12)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Row_Address_WID          (17)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Row_Address_MSK          (0x1FFFF000)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Row_Address_MIN          (0)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Row_Address_MAX          (131071) // 0x0001FFFF
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Row_Address_DEF          (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Row_Address_HSH          (0x510C4900)

  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_OFF         (48)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_WID         ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_MSK         (0x001F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_WID_A0      ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_MSK_A0      (0x000F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_MIN         (0)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_MAX_A0      (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_MAX         (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_DEF         (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_HSH         (0x45304900)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Bank_Address_HSH_A0      (0x44304900)

  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Rank_Address_OFF         (56)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Rank_Address_WID         ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Rank_Address_MSK         (0x0700000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Rank_Address_MIN         (0)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Rank_Address_MAX         (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Rank_Address_DEF         (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_CURRENT_1_Rank_Address_HSH         (0x43384900)

#define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_REG         (0x00004908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Column_Address_Order_OFF ( 0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Column_Address_Order_WID ( 2)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Column_Address_Order_MSK (0x00000003)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Column_Address_Order_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Column_Address_Order_MAX (3) // 0x00000003
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Column_Address_Order_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Column_Address_Order_HSH (0x02004908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Row_Address_Order_OFF ( 2)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Row_Address_Order_WID ( 2)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Row_Address_Order_MSK (0x0000000C)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Row_Address_Order_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Row_Address_Order_MAX (3) // 0x00000003
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Row_Address_Order_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Row_Address_Order_HSH (0x02024908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Bank_Address_Order_OFF ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Bank_Address_Order_WID ( 2)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Bank_Address_Order_MSK (0x00000030)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Bank_Address_Order_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Bank_Address_Order_MAX (3) // 0x00000003
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Bank_Address_Order_DEF (0x00000002)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Bank_Address_Order_HSH (0x02044908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Rank_Address_Order_OFF ( 6)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Rank_Address_Order_WID ( 2)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Rank_Address_Order_MSK (0x000000C0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Rank_Address_Order_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Rank_Address_Order_MAX (3) // 0x00000003
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Rank_Address_Order_DEF (0x00000003)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Rank_Address_Order_HSH (0x02064908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Address_Invert_Rate_OFF (13)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Address_Invert_Rate_WID ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Address_Invert_Rate_MSK (0x0000E000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Address_Invert_Rate_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Address_Invert_Rate_MAX (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Address_Invert_Rate_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Base_Address_Invert_Rate_HSH (0x030D4908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Address_Invert_Enable_OFF (20)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Address_Invert_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Address_Invert_Enable_MSK (0x00100000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Address_Invert_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Address_Invert_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Address_Invert_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Address_Invert_Enable_HSH (0x01144908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Address_Invert_Enable_OFF (21)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Address_Invert_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Address_Invert_Enable_MSK (0x00200000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Address_Invert_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Address_Invert_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Address_Invert_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Address_Invert_Enable_HSH (0x01154908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Address_Invert_Enable_OFF (22)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Address_Invert_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Address_Invert_Enable_MSK (0x00400000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Address_Invert_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Address_Invert_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Address_Invert_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Address_Invert_Enable_HSH (0x01164908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Address_Invert_Enable_OFF (23)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Address_Invert_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Address_Invert_Enable_MSK (0x00800000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Address_Invert_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Address_Invert_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Address_Invert_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Address_Invert_Enable_HSH (0x01174908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Trigger_Enable_OFF (24)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Trigger_Enable_MSK (0x01000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Trigger_Enable_HSH (0x01184908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Trigger_Enable_OFF (25)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Trigger_Enable_MSK (0x02000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Trigger_Enable_HSH (0x01194908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Trigger_Enable_OFF (26)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Trigger_Enable_MSK (0x04000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Trigger_Enable_HSH (0x011A4908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Trigger_Enable_OFF (27)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Trigger_Enable_MSK (0x08000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Trigger_Enable_HSH (0x011B4908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Carry_Enable_OFF (28)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Carry_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Carry_Enable_MSK (0x10000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Carry_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Carry_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Carry_Enable_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Column_Base_Wrap_Carry_Enable_HSH (0x011C4908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Carry_Enable_OFF (29)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Carry_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Carry_Enable_MSK (0x20000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Carry_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Carry_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Carry_Enable_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Row_Base_Wrap_Carry_Enable_HSH (0x011D4908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Carry_Enable_OFF (30)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Carry_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Carry_Enable_MSK (0x40000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Carry_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Carry_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Carry_Enable_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Bank_Base_Wrap_Carry_Enable_HSH (0x011E4908)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Carry_Enable_OFF (31)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Carry_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Carry_Enable_MSK (0x80000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Carry_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Carry_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Carry_Enable_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_Rank_Base_Wrap_Carry_Enable_HSH (0x011F4908)

#define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_REG         (0x0000490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Column_Address_Order_OFF ( 0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Column_Address_Order_WID ( 2)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Column_Address_Order_MSK (0x00000003)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Column_Address_Order_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Column_Address_Order_MAX (3) // 0x00000003
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Column_Address_Order_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Column_Address_Order_HSH (0x0200490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Row_Address_Order_OFF ( 2)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Row_Address_Order_WID ( 2)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Row_Address_Order_MSK (0x0000000C)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Row_Address_Order_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Row_Address_Order_MAX (3) // 0x00000003
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Row_Address_Order_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Row_Address_Order_HSH (0x0202490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Bank_Address_Order_OFF ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Bank_Address_Order_WID ( 2)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Bank_Address_Order_MSK (0x00000030)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Bank_Address_Order_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Bank_Address_Order_MAX (3) // 0x00000003
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Bank_Address_Order_DEF (0x00000002)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Bank_Address_Order_HSH (0x0204490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Rank_Address_Order_OFF ( 6)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Rank_Address_Order_WID ( 2)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Rank_Address_Order_MSK (0x000000C0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Rank_Address_Order_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Rank_Address_Order_MAX (3) // 0x00000003
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Rank_Address_Order_DEF (0x00000003)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Rank_Address_Order_HSH (0x0206490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Address_Invert_Rate_OFF (13)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Address_Invert_Rate_WID ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Address_Invert_Rate_MSK (0x0000E000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Address_Invert_Rate_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Address_Invert_Rate_MAX (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Address_Invert_Rate_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Base_Address_Invert_Rate_HSH (0x030D490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Address_Invert_Enable_OFF (20)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Address_Invert_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Address_Invert_Enable_MSK (0x00100000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Address_Invert_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Address_Invert_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Address_Invert_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Address_Invert_Enable_HSH (0x0114490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Address_Invert_Enable_OFF (21)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Address_Invert_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Address_Invert_Enable_MSK (0x00200000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Address_Invert_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Address_Invert_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Address_Invert_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Address_Invert_Enable_HSH (0x0115490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Address_Invert_Enable_OFF (22)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Address_Invert_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Address_Invert_Enable_MSK (0x00400000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Address_Invert_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Address_Invert_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Address_Invert_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Address_Invert_Enable_HSH (0x0116490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Address_Invert_Enable_OFF (23)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Address_Invert_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Address_Invert_Enable_MSK (0x00800000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Address_Invert_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Address_Invert_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Address_Invert_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Address_Invert_Enable_HSH (0x0117490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Trigger_Enable_OFF (24)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Trigger_Enable_MSK (0x01000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Trigger_Enable_HSH (0x0118490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Trigger_Enable_OFF (25)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Trigger_Enable_MSK (0x02000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Trigger_Enable_HSH (0x0119490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Trigger_Enable_OFF (26)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Trigger_Enable_MSK (0x04000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Trigger_Enable_HSH (0x011A490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Trigger_Enable_OFF (27)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Trigger_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Trigger_Enable_MSK (0x08000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Trigger_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Trigger_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Trigger_Enable_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Trigger_Enable_HSH (0x011B490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Carry_Enable_OFF (28)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Carry_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Carry_Enable_MSK (0x10000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Carry_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Carry_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Carry_Enable_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Column_Base_Wrap_Carry_Enable_HSH (0x011C490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Carry_Enable_OFF (29)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Carry_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Carry_Enable_MSK (0x20000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Carry_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Carry_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Carry_Enable_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Row_Base_Wrap_Carry_Enable_HSH (0x011D490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Carry_Enable_OFF (30)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Carry_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Carry_Enable_MSK (0x40000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Carry_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Carry_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Carry_Enable_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Bank_Base_Wrap_Carry_Enable_HSH (0x011E490C)

  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Carry_Enable_OFF (31)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Carry_Enable_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Carry_Enable_MSK (0x80000000)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Carry_Enable_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Carry_Enable_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Carry_Enable_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_Rank_Base_Wrap_Carry_Enable_HSH (0x011F490C)

#define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_REG                        (0x00004910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Increment_OFF ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Increment_WID ( 9)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Increment_MSK (0x00000FF8)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Increment_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Increment_MAX (511) // 0x000001FF
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Increment_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Increment_HSH (0x49034910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Rate_OFF (12)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Rate_WID ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Rate_MSK (0x0001F000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Rate_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Rate_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Rate_HSH (0x450C4910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Scale_OFF (19)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Scale_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Scale_MSK (0x00080000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Scale_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Scale_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Scale_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Column_Base_Address_Update_Scale_HSH (0x41134910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Increment_OFF (20)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Increment_WID (12)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Increment_MSK (0xFFF00000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Increment_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Increment_MAX (4095) // 0x00000FFF
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Increment_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Increment_HSH (0x4C144910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Rate_OFF (32)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Rate_WID ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Rate_MSK (0x0000000F00000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Rate_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Rate_MAX (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Rate_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Rate_HSH (0x44204910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Scale_OFF (37)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Scale_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Scale_MSK (0x0000002000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Scale_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Scale_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Scale_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Row_Base_Address_Update_Scale_HSH (0x41254910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_OFF (38)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_WID ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_MSK (0x000007C000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_WID_A0 ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_MSK_A0 (0x000003C000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_MAX_A0 (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_HSH (0x45264910)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Increment_HSH_A0 (0x44264910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Rate_OFF (44)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Rate_WID ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Rate_MSK (0x0001F00000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Rate_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Rate_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Rate_HSH (0x452C4910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Scale_OFF (51)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Scale_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Scale_MSK (0x0008000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Scale_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Scale_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Scale_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Bank_Base_Address_Update_Scale_HSH (0x41334910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Increment_OFF (52)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Increment_WID ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Increment_MSK (0x0070000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Increment_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Increment_MAX (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Increment_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Increment_HSH (0x43344910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Rate_OFF (56)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Rate_WID ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Rate_MSK (0x1F00000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Rate_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Rate_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Rate_HSH (0x45384910)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Scale_OFF (63)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Scale_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Scale_MSK (0x8000000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Scale_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Scale_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Scale_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_Rank_Base_Address_Update_Scale_HSH (0x413F4910)

#define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_REG                        (0x00004918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Increment_OFF ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Increment_WID ( 9)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Increment_MSK (0x00000FF8)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Increment_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Increment_MAX (511) // 0x000001FF
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Increment_DEF (0x00000001)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Increment_HSH (0x49034918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Rate_OFF (12)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Rate_WID ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Rate_MSK (0x0001F000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Rate_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Rate_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Rate_HSH (0x450C4918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Scale_OFF (19)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Scale_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Scale_MSK (0x00080000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Scale_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Scale_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Scale_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Column_Base_Address_Update_Scale_HSH (0x41134918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Increment_OFF (20)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Increment_WID (12)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Increment_MSK (0xFFF00000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Increment_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Increment_MAX (4095) // 0x00000FFF
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Increment_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Increment_HSH (0x4C144918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Rate_OFF (32)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Rate_WID ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Rate_MSK (0x0000000F00000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Rate_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Rate_MAX (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Rate_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Rate_HSH (0x44204918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Scale_OFF (37)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Scale_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Scale_MSK (0x0000002000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Scale_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Scale_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Scale_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Row_Base_Address_Update_Scale_HSH (0x41254918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_OFF (38)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_WID ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_MSK (0x000007C000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_WID_A0 ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_MSK_A0 (0x000003C000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_MAX_A0 (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_HSH (0x45264918)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Increment_HSH_A0 (0x44264918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Rate_OFF (44)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Rate_WID ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Rate_MSK (0x0001F00000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Rate_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Rate_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Rate_HSH (0x452C4918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Scale_OFF (51)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Scale_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Scale_MSK (0x0008000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Scale_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Scale_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Scale_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Bank_Base_Address_Update_Scale_HSH (0x41334918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Increment_OFF (52)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Increment_WID ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Increment_MSK (0x0070000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Increment_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Increment_MAX (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Increment_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Increment_HSH (0x43344918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Rate_OFF (56)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Rate_WID ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Rate_MSK (0x1F00000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Rate_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Rate_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Rate_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Rate_HSH (0x45384918)

  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Scale_OFF (63)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Scale_WID ( 1)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Scale_MSK (0x8000000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Scale_MIN (0)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Scale_MAX (1) // 0x00000001
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Scale_DEF (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_Rank_Base_Address_Update_Scale_HSH (0x413F4918)

#define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_REG                      (0x00004920)

  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Column_Address_OFF     ( 3)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Column_Address_WID     ( 9)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Column_Address_MSK     (0x00000FF8)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Column_Address_MIN     (0)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Column_Address_MAX     (511) // 0x000001FF
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Column_Address_DEF     (0x00000000)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Column_Address_HSH     (0x49034920)

  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Row_Address_OFF        (12)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Row_Address_WID        (17)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Row_Address_MSK        (0x1FFFF000)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Row_Address_MIN        (0)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Row_Address_MAX        (131071) // 0x0001FFFF
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Row_Address_DEF        (0x00000000)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_Row_Address_HSH        (0x510C4920)

#define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_REG                      (0x00004928)

  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Column_Address_OFF     ( 3)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Column_Address_WID     ( 9)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Column_Address_MSK     (0x00000FF8)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Column_Address_MIN     (0)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Column_Address_MAX     (511) // 0x000001FF
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Column_Address_DEF     (0x00000000)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Column_Address_HSH     (0x49034928)

  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Row_Address_OFF        (12)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Row_Address_WID        (17)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Row_Address_MSK        (0x1FFFF000)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Row_Address_MIN        (0)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Row_Address_MAX        (131071) // 0x0001FFFF
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Row_Address_DEF        (0x00000000)
  #define REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_Row_Address_HSH        (0x510C4928)

#define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_REG                   (0x00004938)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row0_Swizzle_OFF ( 0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row0_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row0_Swizzle_MSK (0x0000001F)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row0_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row0_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row0_Swizzle_DEF (0x00000000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row0_Swizzle_HSH (0x05004938)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row1_Swizzle_OFF ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row1_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row1_Swizzle_MSK (0x000003E0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row1_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row1_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row1_Swizzle_DEF (0x00000001)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row1_Swizzle_HSH (0x05054938)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row2_Swizzle_OFF (10)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row2_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row2_Swizzle_MSK (0x00007C00)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row2_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row2_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row2_Swizzle_DEF (0x00000002)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row2_Swizzle_HSH (0x050A4938)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row3_Swizzle_OFF (15)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row3_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row3_Swizzle_MSK (0x000F8000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row3_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row3_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row3_Swizzle_DEF (0x00000003)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row3_Swizzle_HSH (0x050F4938)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row4_Swizzle_OFF (20)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row4_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row4_Swizzle_MSK (0x01F00000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row4_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row4_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row4_Swizzle_DEF (0x00000004)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row4_Swizzle_HSH (0x05144938)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row5_Swizzle_OFF (25)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row5_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row5_Swizzle_MSK (0x3E000000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row5_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row5_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row5_Swizzle_DEF (0x00000005)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_Logical_to_Physical_Row5_Swizzle_HSH (0x05194938)

#define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_REG                   (0x0000493C)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row0_Swizzle_OFF ( 0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row0_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row0_Swizzle_MSK (0x0000001F)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row0_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row0_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row0_Swizzle_DEF (0x00000000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row0_Swizzle_HSH (0x0500493C)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row1_Swizzle_OFF ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row1_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row1_Swizzle_MSK (0x000003E0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row1_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row1_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row1_Swizzle_DEF (0x00000001)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row1_Swizzle_HSH (0x0505493C)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row2_Swizzle_OFF (10)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row2_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row2_Swizzle_MSK (0x00007C00)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row2_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row2_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row2_Swizzle_DEF (0x00000002)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row2_Swizzle_HSH (0x050A493C)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row3_Swizzle_OFF (15)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row3_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row3_Swizzle_MSK (0x000F8000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row3_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row3_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row3_Swizzle_DEF (0x00000003)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row3_Swizzle_HSH (0x050F493C)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row4_Swizzle_OFF (20)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row4_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row4_Swizzle_MSK (0x01F00000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row4_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row4_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row4_Swizzle_DEF (0x00000004)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row4_Swizzle_HSH (0x0514493C)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row5_Swizzle_OFF (25)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row5_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row5_Swizzle_MSK (0x3E000000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row5_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row5_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row5_Swizzle_DEF (0x00000005)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_Logical_to_Physical_Row5_Swizzle_HSH (0x0519493C)

#define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_REG                   (0x00004940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row6_Swizzle_OFF ( 0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row6_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row6_Swizzle_MSK (0x0000001F)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row6_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row6_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row6_Swizzle_DEF (0x00000006)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row6_Swizzle_HSH (0x45004940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row7_Swizzle_OFF ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row7_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row7_Swizzle_MSK (0x000003E0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row7_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row7_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row7_Swizzle_DEF (0x00000007)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row7_Swizzle_HSH (0x45054940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row8_Swizzle_OFF (10)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row8_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row8_Swizzle_MSK (0x00007C00)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row8_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row8_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row8_Swizzle_DEF (0x00000008)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row8_Swizzle_HSH (0x450A4940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row9_Swizzle_OFF (15)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row9_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row9_Swizzle_MSK (0x000F8000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row9_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row9_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row9_Swizzle_DEF (0x00000009)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row9_Swizzle_HSH (0x450F4940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row10_Swizzle_OFF (20)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row10_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row10_Swizzle_MSK (0x01F00000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row10_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row10_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row10_Swizzle_DEF (0x0000000A)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row10_Swizzle_HSH (0x45144940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row11_Swizzle_OFF (25)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row11_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row11_Swizzle_MSK (0x3E000000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row11_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row11_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row11_Swizzle_DEF (0x0000000B)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row11_Swizzle_HSH (0x45194940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row12_Swizzle_OFF (32)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row12_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row12_Swizzle_MSK (0x0000001F00000000ULL)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row12_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row12_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row12_Swizzle_DEF (0x0000000C)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row12_Swizzle_HSH (0x45204940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row13_Swizzle_OFF (37)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row13_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row13_Swizzle_MSK (0x000003E000000000ULL)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row13_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row13_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row13_Swizzle_DEF (0x0000000D)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row13_Swizzle_HSH (0x45254940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row14_Swizzle_OFF (42)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row14_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row14_Swizzle_MSK (0x00007C0000000000ULL)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row14_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row14_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row14_Swizzle_DEF (0x0000000E)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row14_Swizzle_HSH (0x452A4940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row15_Swizzle_OFF (47)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row15_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row15_Swizzle_MSK (0x000F800000000000ULL)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row15_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row15_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row15_Swizzle_DEF (0x0000000F)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row15_Swizzle_HSH (0x452F4940)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row16_Swizzle_OFF (52)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row16_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row16_Swizzle_MSK (0x01F0000000000000ULL)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row16_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row16_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row16_Swizzle_DEF (0x00000010)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_Logical_to_Physical_Row16_Swizzle_HSH (0x45344940)

#define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_REG                   (0x00004948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row6_Swizzle_OFF ( 0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row6_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row6_Swizzle_MSK (0x0000001F)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row6_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row6_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row6_Swizzle_DEF (0x00000006)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row6_Swizzle_HSH (0x45004948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row7_Swizzle_OFF ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row7_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row7_Swizzle_MSK (0x000003E0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row7_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row7_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row7_Swizzle_DEF (0x00000007)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row7_Swizzle_HSH (0x45054948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row8_Swizzle_OFF (10)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row8_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row8_Swizzle_MSK (0x00007C00)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row8_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row8_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row8_Swizzle_DEF (0x00000008)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row8_Swizzle_HSH (0x450A4948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row9_Swizzle_OFF (15)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row9_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row9_Swizzle_MSK (0x000F8000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row9_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row9_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row9_Swizzle_DEF (0x00000009)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row9_Swizzle_HSH (0x450F4948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row10_Swizzle_OFF (20)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row10_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row10_Swizzle_MSK (0x01F00000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row10_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row10_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row10_Swizzle_DEF (0x0000000A)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row10_Swizzle_HSH (0x45144948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row11_Swizzle_OFF (25)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row11_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row11_Swizzle_MSK (0x3E000000)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row11_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row11_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row11_Swizzle_DEF (0x0000000B)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row11_Swizzle_HSH (0x45194948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row12_Swizzle_OFF (32)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row12_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row12_Swizzle_MSK (0x0000001F00000000ULL)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row12_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row12_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row12_Swizzle_DEF (0x0000000C)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row12_Swizzle_HSH (0x45204948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row13_Swizzle_OFF (37)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row13_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row13_Swizzle_MSK (0x000003E000000000ULL)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row13_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row13_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row13_Swizzle_DEF (0x0000000D)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row13_Swizzle_HSH (0x45254948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row14_Swizzle_OFF (42)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row14_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row14_Swizzle_MSK (0x00007C0000000000ULL)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row14_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row14_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row14_Swizzle_DEF (0x0000000E)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row14_Swizzle_HSH (0x452A4948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row15_Swizzle_OFF (47)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row15_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row15_Swizzle_MSK (0x000F800000000000ULL)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row15_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row15_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row15_Swizzle_DEF (0x0000000F)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row15_Swizzle_HSH (0x452F4948)

  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row16_Swizzle_OFF (52)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row16_Swizzle_WID ( 5)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row16_Swizzle_MSK (0x01F0000000000000ULL)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row16_Swizzle_MIN (0)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row16_Swizzle_MAX (31) // 0x0000001F
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row16_Swizzle_DEF (0x00000010)
  #define REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_Logical_to_Physical_Row16_Swizzle_HSH (0x45344948)

#define REUT_CH_ERR_TRIGGER_CTL_REG                                (0x0000496C)

  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_In_Global_Start_OFF      ( 0)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_In_Global_Start_WID      ( 1)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_In_Global_Start_MSK      (0x00000001)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_In_Global_Start_MIN      (0)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_In_Global_Start_MAX      (1) // 0x00000001
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_In_Global_Start_DEF      (0x00000000)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_In_Global_Start_HSH      (0x0100496C)

  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_Global_Start_OFF     ( 1)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_Global_Start_WID     ( 1)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_Global_Start_MSK     (0x00000002)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_Global_Start_MIN     (0)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_Global_Start_MAX     (1) // 0x00000001
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_Global_Start_DEF     (0x00000000)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_Global_Start_HSH     (0x0101496C)

  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_0_OFF       ( 7)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_0_WID       ( 1)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_0_MSK       (0x00000080)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_0_MIN       (0)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_0_MAX       (1) // 0x00000001
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_0_DEF       (0x00000000)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_0_HSH       (0x0107496C)

  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_1_OFF       ( 8)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_1_WID       ( 1)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_1_MSK       (0x00000100)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_1_MIN       (0)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_1_MAX       (1) // 0x00000001
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_1_DEF       (0x00000000)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Error_1_HSH       (0x0108496C)

  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_0_OFF (15)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_0_WID ( 1)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_0_MSK (0x00008000)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_0_MIN (0)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_0_MAX (1) // 0x00000001
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_0_DEF (0x00000000)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_0_HSH (0x010F496C)

  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_1_OFF (16)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_1_WID ( 1)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_1_MSK (0x00010000)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_1_MIN (0)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_1_MAX (1) // 0x00000001
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_1_DEF (0x00000000)
  #define REUT_CH_ERR_TRIGGER_CTL_Trigger_Out_On_Channel_Test_Done_Status_1_HSH (0x0110496C)

#define REUT_CH_SEQ_BASE_ADDR_SAVE_0_REG                           (0x00004970)
#define REUT_CH_SEQ_BASE_ADDR_SAVE_0_REG_A0                        (0x00004990)

  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Column_Address_OFF          ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Column_Address_WID          ( 9)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Column_Address_MSK          (0x00000FF8)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Column_Address_MIN          (0)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Column_Address_MAX          (511) // 0x000001FF
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Column_Address_DEF          (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Column_Address_HSH          (0x49034970)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Column_Address_HSH_A0       (0x49034990)

  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Row_Address_OFF             (12)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Row_Address_WID             (17)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Row_Address_MSK             (0x1FFFF000)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Row_Address_MIN             (0)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Row_Address_MAX             (131071) // 0x0001FFFF
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Row_Address_DEF             (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Row_Address_HSH             (0x510C4970)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Row_Address_HSH_A0          (0x510C4990)

  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_OFF            (48)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_WID            ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_MSK            (0x001F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_WID_A0         ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_MSK_A0         (0x000F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_MIN            (0)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_MAX            (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_MAX_A0         (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_DEF            (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_HSH            (0x45304970)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Bank_Address_HSH_A0         (0x44304990)

  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Rank_Address_OFF            (56)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Rank_Address_WID            ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Rank_Address_MSK            (0x0700000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Rank_Address_MIN            (0)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Rank_Address_MAX            (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Rank_Address_DEF            (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Rank_Address_HSH            (0x43384970)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_0_Rank_Address_HSH_A0         (0x43384990)

#define REUT_CH_SEQ_BASE_ADDR_SAVE_1_REG                           (0x00004978)
#define REUT_CH_SEQ_BASE_ADDR_SAVE_1_REG_A0                        (0x00004998)

  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Column_Address_OFF          ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Column_Address_WID          ( 9)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Column_Address_MSK          (0x00000FF8)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Column_Address_MIN          (0)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Column_Address_MAX          (511) // 0x000001FF
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Column_Address_DEF          (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Column_Address_HSH          (0x49034978)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Column_Address_HSH_A0       (0x49034998)

  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Row_Address_OFF             (12)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Row_Address_WID             (17)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Row_Address_MSK             (0x1FFFF000)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Row_Address_MIN             (0)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Row_Address_MAX             (131071) // 0x0001FFFF
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Row_Address_DEF             (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Row_Address_HSH             (0x510C4978)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Row_Address_HSH_A0          (0x510C4998)

  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_OFF            (48)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_WID            ( 5)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_MSK            (0x001F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_WID_A0         ( 4)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_MSK_A0         (0x000F000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_MIN            (0)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_MAX            (31) // 0x0000001F
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_MAX_A0         (15) // 0x0000000F
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_DEF            (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_HSH            (0x45304978)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Bank_Address_HSH_A0         (0x44304998)

  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Rank_Address_OFF            (56)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Rank_Address_WID            ( 3)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Rank_Address_MSK            (0x0700000000000000ULL)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Rank_Address_MIN            (0)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Rank_Address_MAX            (7) // 0x00000007
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Rank_Address_DEF            (0x00000000)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Rank_Address_HSH            (0x43384978)
  #define REUT_CH_SEQ_BASE_ADDR_SAVE_1_Rank_Address_HSH_A0         (0x43384998)

#define REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_REG                          (0x00004980)
#define REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_REG_A0                       (0x000049A0)

  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_Loopcount_Limit_OFF        ( 0)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_Loopcount_Limit_WID        (32)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_Loopcount_Limit_MSK        (0xFFFFFFFF)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_Loopcount_Limit_MIN        (0)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_Loopcount_Limit_MAX        (4294967295) // 0xFFFFFFFF
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_Loopcount_Limit_DEF        (0x00000000)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_Loopcount_Limit_HSH        (0x20004980)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_Loopcount_Limit_HSH_A0     (0x200049A0)

#define REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_REG                          (0x00004984)
#define REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_REG_A0                       (0x000049A4)

  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_Loopcount_Limit_OFF        ( 0)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_Loopcount_Limit_WID        (32)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_Loopcount_Limit_MSK        (0xFFFFFFFF)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_Loopcount_Limit_MIN        (0)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_Loopcount_Limit_MAX        (4294967295) // 0xFFFFFFFF
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_Loopcount_Limit_DEF        (0x00000000)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_Loopcount_Limit_HSH        (0x20004984)
  #define REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_Loopcount_Limit_HSH_A0     (0x200049A4)

#define REUT_CH_SEQ_ADDR_ENABLE_0_REG                              (0x00004988)
#define REUT_CH_SEQ_ADDR_ENABLE_0_REG_A0                           (0x000049A8)

  #define REUT_CH_SEQ_ADDR_ENABLE_0_Col_Enable_OFF                 ( 0)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Col_Enable_WID                 ( 9)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Col_Enable_MSK                 (0x000001FF)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Col_Enable_MIN                 (0)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Col_Enable_MAX                 (511) // 0x000001FF
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Col_Enable_DEF                 (0x000001FF)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Col_Enable_HSH                 (0x09004988)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Col_Enable_HSH_A0              (0x090049A8)

  #define REUT_CH_SEQ_ADDR_ENABLE_0_Row_Enable_OFF                 ( 9)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Row_Enable_WID                 (17)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Row_Enable_MSK                 (0x03FFFE00)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Row_Enable_MIN                 (0)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Row_Enable_MAX                 (131071) // 0x0001FFFF
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Row_Enable_DEF                 (0x0001FFFF)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Row_Enable_HSH                 (0x11094988)
  #define REUT_CH_SEQ_ADDR_ENABLE_0_Row_Enable_HSH_A0              (0x110949A8)

#define REUT_CH_SEQ_ADDR_ENABLE_1_REG                              (0x0000498C)
#define REUT_CH_SEQ_ADDR_ENABLE_1_REG_A0                           (0x000049AC)

  #define REUT_CH_SEQ_ADDR_ENABLE_1_Col_Enable_OFF                 ( 0)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Col_Enable_WID                 ( 9)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Col_Enable_MSK                 (0x000001FF)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Col_Enable_MIN                 (0)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Col_Enable_MAX                 (511) // 0x000001FF
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Col_Enable_DEF                 (0x000001FF)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Col_Enable_HSH                 (0x0900498C)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Col_Enable_HSH_A0              (0x090049AC)

  #define REUT_CH_SEQ_ADDR_ENABLE_1_Row_Enable_OFF                 ( 9)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Row_Enable_WID                 (17)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Row_Enable_MSK                 (0x03FFFE00)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Row_Enable_MIN                 (0)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Row_Enable_MAX                 (131071) // 0x0001FFFF
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Row_Enable_DEF                 (0x0001FFFF)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Row_Enable_HSH                 (0x1109498C)
  #define REUT_CH_SEQ_ADDR_ENABLE_1_Row_Enable_HSH_A0              (0x110949AC)

#define REUT_PG_ID_PATTERN_BUFFER_CTL_REG                          (0x00004990)
#define REUT_PG_ID_PATTERN_BUFFER_CTL_REG_A0                       (0x000049B0)

  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Generator_Id_OFF   ( 0)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Generator_Id_WID   ( 6)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Generator_Id_MSK   (0x0000003F)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Generator_Id_MIN   (0)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Generator_Id_MAX   (63) // 0x0000003F
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Generator_Id_DEF   (0x00000000)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Generator_Id_HSH   (0x06004990)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Generator_Id_HSH_A0   (0x060049B0)

  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Buffer_Entry_OFF   ( 8)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Buffer_Entry_WID   ( 3)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Buffer_Entry_MSK   (0x00000700)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Buffer_Entry_MIN   (0)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Buffer_Entry_MAX   (7) // 0x00000007
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Buffer_Entry_DEF   (0x00000000)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Buffer_Entry_HSH   (0x03084990)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_Pattern_Buffer_Entry_HSH_A0   (0x030849B0)

  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Data_Source_Sel_OFF    (11)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Data_Source_Sel_WID    ( 2)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Data_Source_Sel_MSK    (0x00001800)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Data_Source_Sel_MIN    (0)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Data_Source_Sel_MAX    (3) // 0x00000003
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Data_Source_Sel_DEF    (0x00000000)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Data_Source_Sel_HSH    (0x020B4990)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Data_Source_Sel_HSH_A0    (0x020B49B0)

  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Replace_Byte_Control_OFF (13)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Replace_Byte_Control_WID ( 2)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Replace_Byte_Control_MSK (0x00006000)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Replace_Byte_Control_MIN (0)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Replace_Byte_Control_MAX (3) // 0x00000003
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Replace_Byte_Control_DEF (0x00000000)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Replace_Byte_Control_HSH (0x020D4990)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_ECC_Replace_Byte_Control_HSH_A0 (0x020D49B0)

  #define REUT_PG_ID_PATTERN_BUFFER_CTL_SubSequence_Count_To_Shift_OFF (15)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_SubSequence_Count_To_Shift_WID ( 5)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_SubSequence_Count_To_Shift_MSK (0x000F8000)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_SubSequence_Count_To_Shift_MIN (0)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_SubSequence_Count_To_Shift_MAX (31) // 0x0000001F
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_SubSequence_Count_To_Shift_DEF (0x00000000)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_SubSequence_Count_To_Shift_HSH (0x050F4990)
  #define REUT_PG_ID_PATTERN_BUFFER_CTL_SubSequence_Count_To_Shift_HSH_A0 (0x050F49B0)

#define REUT_PG_PAT_CL_MUX_CFG_REG                                 (0x00004A00)

  #define REUT_PG_PAT_CL_MUX_CFG_Mux0_Control_OFF                  ( 0)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux0_Control_WID                  ( 2)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux0_Control_MSK                  (0x00000003)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux0_Control_MIN                  (0)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux0_Control_MAX                  (3) // 0x00000003
  #define REUT_PG_PAT_CL_MUX_CFG_Mux0_Control_DEF                  (0x00000001)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux0_Control_HSH                  (0x42004A00)

  #define REUT_PG_PAT_CL_MUX_CFG_Mux1_Control_OFF                  ( 3)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux1_Control_WID                  ( 2)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux1_Control_MSK                  (0x00000018)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux1_Control_MIN                  (0)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux1_Control_MAX                  (3) // 0x00000003
  #define REUT_PG_PAT_CL_MUX_CFG_Mux1_Control_DEF                  (0x00000001)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux1_Control_HSH                  (0x42034A00)

  #define REUT_PG_PAT_CL_MUX_CFG_Mux2_Control_OFF                  ( 6)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux2_Control_WID                  ( 2)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux2_Control_MSK                  (0x000000C0)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux2_Control_MIN                  (0)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux2_Control_MAX                  (3) // 0x00000003
  #define REUT_PG_PAT_CL_MUX_CFG_Mux2_Control_DEF                  (0x00000001)
  #define REUT_PG_PAT_CL_MUX_CFG_Mux2_Control_HSH                  (0x42064A00)

  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_OFF                   ( 8)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_WID                   ( 4)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_MSK                   (0x00000F00)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_WID_A0                ( 3)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_MSK_A0                (0x00000700)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_MIN                   (0)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_MAX                   (15) // 0x0000000F
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_MAX_A0                (7) // 0x00000007
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_DEF                   (0x00000007)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_HSH                   (0x44084A00)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_0_HSH_A0                (0x43084A00)

  #define REUT_PG_PAT_CL_MUX_CFG_spare_OFF                         (12)
  #define REUT_PG_PAT_CL_MUX_CFG_spare_WID                         ( 4)
  #define REUT_PG_PAT_CL_MUX_CFG_spare_MSK                         (0x0000F000)
  #define REUT_PG_PAT_CL_MUX_CFG_spare_MIN                         (0)
  #define REUT_PG_PAT_CL_MUX_CFG_spare_MAX                         (15) // 0x0000000F
  #define REUT_PG_PAT_CL_MUX_CFG_spare_DEF                         (0x00000000)
  #define REUT_PG_PAT_CL_MUX_CFG_spare_HSH                         (0x440C4A00)

  #define REUT_PG_PAT_CL_MUX_CFG_Save_LFSR_Seed_Rate_OFF           (16)
  #define REUT_PG_PAT_CL_MUX_CFG_Save_LFSR_Seed_Rate_WID           ( 8)
  #define REUT_PG_PAT_CL_MUX_CFG_Save_LFSR_Seed_Rate_MSK           (0x00FF0000)
  #define REUT_PG_PAT_CL_MUX_CFG_Save_LFSR_Seed_Rate_MIN           (0)
  #define REUT_PG_PAT_CL_MUX_CFG_Save_LFSR_Seed_Rate_MAX           (255) // 0x000000FF
  #define REUT_PG_PAT_CL_MUX_CFG_Save_LFSR_Seed_Rate_DEF           (0x00000000)
  #define REUT_PG_PAT_CL_MUX_CFG_Save_LFSR_Seed_Rate_HSH           (0x48104A00)

  #define REUT_PG_PAT_CL_MUX_CFG_Reload_LFSR_Seed_Rate_OFF         (24)
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_LFSR_Seed_Rate_WID         ( 5)
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_LFSR_Seed_Rate_MSK         (0x1F000000)
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_LFSR_Seed_Rate_MIN         (0)
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_LFSR_Seed_Rate_MAX         (31) // 0x0000001F
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_LFSR_Seed_Rate_DEF         (0x00000000)
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_LFSR_Seed_Rate_HSH         (0x45184A00)

  #define REUT_PG_PAT_CL_MUX_CFG_Shift_Array_Enabled_OFF           (29)
  #define REUT_PG_PAT_CL_MUX_CFG_Shift_Array_Enabled_WID           ( 1)
  #define REUT_PG_PAT_CL_MUX_CFG_Shift_Array_Enabled_MSK           (0x20000000)
  #define REUT_PG_PAT_CL_MUX_CFG_Shift_Array_Enabled_MIN           (0)
  #define REUT_PG_PAT_CL_MUX_CFG_Shift_Array_Enabled_MAX           (1) // 0x00000001
  #define REUT_PG_PAT_CL_MUX_CFG_Shift_Array_Enabled_DEF           (0x00000000)
  #define REUT_PG_PAT_CL_MUX_CFG_Shift_Array_Enabled_HSH           (0x411D4A00)

  #define REUT_PG_PAT_CL_MUX_CFG_Reload_Save_LFSR_Seed_Rate_Mode_OFF (31)
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_Save_LFSR_Seed_Rate_Mode_WID ( 1)
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_Save_LFSR_Seed_Rate_Mode_MSK (0x80000000)
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_Save_LFSR_Seed_Rate_Mode_MIN (0)
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_Save_LFSR_Seed_Rate_Mode_MAX (1) // 0x00000001
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_Save_LFSR_Seed_Rate_Mode_DEF (0x00000000)
  #define REUT_PG_PAT_CL_MUX_CFG_Reload_Save_LFSR_Seed_Rate_Mode_HSH (0x411F4A00)

  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_OFF                   (32)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_WID                   ( 4)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_MSK                   (0x0000000F00000000ULL)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_WID_A0                ( 3)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_MSK_A0                (0x0000000700000000ULL)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_MIN                   (0)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_MAX                   (15) // 0x0000000F
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_MAX_A0                (7) // 0x00000007
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_DEF                   (0x00000007)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_HSH                   (0x44204A00)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_1_HSH_A0                (0x43204A00)

  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_OFF                   (36)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_WID                   ( 4)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_MSK                   (0x000000F000000000ULL)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_OFF_A0                (35)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_WID_A0                ( 3)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_MSK_A0                (0x0000003800000000ULL)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_MIN                   (0)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_MAX                   (15) // 0x0000000F
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_MAX_A0                (7) // 0x00000007
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_DEF                   (0x00000007)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_HSH                   (0x44244A00)
  #define REUT_PG_PAT_CL_MUX_CFG_LFSR_Type_2_HSH_A0                (0x43234A00)

  #define REUT_PG_PAT_CL_MUX_CFG_CMD_TYPE_TO_COUNT_CL_OFF          (40)
  #define REUT_PG_PAT_CL_MUX_CFG_CMD_TYPE_TO_COUNT_CL_OFF_A0       (38)
  #define REUT_PG_PAT_CL_MUX_CFG_CMD_TYPE_TO_COUNT_CL_WID          ( 1)
  #define REUT_PG_PAT_CL_MUX_CFG_CMD_TYPE_TO_COUNT_CL_MSK          (0x0000010000000000ULL)
  #define REUT_PG_PAT_CL_MUX_CFG_CMD_TYPE_TO_COUNT_CL_MSK_A0       (0x0000004000000000ULL)
  #define REUT_PG_PAT_CL_MUX_CFG_CMD_TYPE_TO_COUNT_CL_MIN          (0)
  #define REUT_PG_PAT_CL_MUX_CFG_CMD_TYPE_TO_COUNT_CL_MAX          (1) // 0x00000001
  #define REUT_PG_PAT_CL_MUX_CFG_CMD_TYPE_TO_COUNT_CL_DEF          (0x00000000)
  #define REUT_PG_PAT_CL_MUX_CFG_CMD_TYPE_TO_COUNT_CL_HSH          (0x41284A00)
  #define REUT_PG_PAT_CL_MUX_CFG_CMD_TYPE_TO_COUNT_CL_HSH_A0       (0x41264A00)

#define REUT_PG_PAT_CL_MUX_WR_PB_0_REG                             (0x00004A08)

  #define REUT_PG_PAT_CL_MUX_WR_PB_0_Pattern_Buffer_OFF            ( 0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_0_Pattern_Buffer_WID            (24)
  #define REUT_PG_PAT_CL_MUX_WR_PB_0_Pattern_Buffer_MSK            (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_WR_PB_0_Pattern_Buffer_MIN            (0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_0_Pattern_Buffer_MAX            (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_WR_PB_0_Pattern_Buffer_DEF            (0x00000000)
  #define REUT_PG_PAT_CL_MUX_WR_PB_0_Pattern_Buffer_HSH            (0x18004A08)

#define REUT_PG_PAT_CL_MUX_WR_PB_1_REG                             (0x00004A0C)

  #define REUT_PG_PAT_CL_MUX_WR_PB_1_Pattern_Buffer_OFF            ( 0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_1_Pattern_Buffer_WID            (24)
  #define REUT_PG_PAT_CL_MUX_WR_PB_1_Pattern_Buffer_MSK            (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_WR_PB_1_Pattern_Buffer_MIN            (0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_1_Pattern_Buffer_MAX            (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_WR_PB_1_Pattern_Buffer_DEF            (0x00000000)
  #define REUT_PG_PAT_CL_MUX_WR_PB_1_Pattern_Buffer_HSH            (0x18004A0C)

#define REUT_PG_PAT_CL_MUX_WR_PB_2_REG                             (0x00004A10)

  #define REUT_PG_PAT_CL_MUX_WR_PB_2_Pattern_Buffer_OFF            ( 0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_2_Pattern_Buffer_WID            (24)
  #define REUT_PG_PAT_CL_MUX_WR_PB_2_Pattern_Buffer_MSK            (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_WR_PB_2_Pattern_Buffer_MIN            (0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_2_Pattern_Buffer_MAX            (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_WR_PB_2_Pattern_Buffer_DEF            (0x00000000)
  #define REUT_PG_PAT_CL_MUX_WR_PB_2_Pattern_Buffer_HSH            (0x18004A10)

#define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_0_REG                      (0x00004A14)

  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_0_Pattern_Buffer_OFF     ( 0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_0_Pattern_Buffer_WID     (24)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_0_Pattern_Buffer_MSK     (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_0_Pattern_Buffer_MIN     (0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_0_Pattern_Buffer_MAX     (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_0_Pattern_Buffer_DEF     (0x00000000)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_0_Pattern_Buffer_HSH     (0x18004A14)

#define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_1_REG                      (0x00004A18)

  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_1_Pattern_Buffer_OFF     ( 0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_1_Pattern_Buffer_WID     (24)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_1_Pattern_Buffer_MSK     (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_1_Pattern_Buffer_MIN     (0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_1_Pattern_Buffer_MAX     (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_1_Pattern_Buffer_DEF     (0x00000000)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_1_Pattern_Buffer_HSH     (0x18004A18)

#define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_2_REG                      (0x00004A1C)

  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_2_Pattern_Buffer_OFF     ( 0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_2_Pattern_Buffer_WID     (24)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_2_Pattern_Buffer_MSK     (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_2_Pattern_Buffer_MIN     (0)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_2_Pattern_Buffer_MAX     (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_2_Pattern_Buffer_DEF     (0x00000000)
  #define REUT_PG_PAT_CL_MUX_WR_PB_STATUS_2_Pattern_Buffer_HSH     (0x18004A1C)

#define REUT_PG_PAT_CL_MUX_LMN_REG                                 (0x00004A20)

  #define REUT_PG_PAT_CL_MUX_LMN_L_data_select_OFF                 ( 0)
  #define REUT_PG_PAT_CL_MUX_LMN_L_data_select_WID                 ( 1)
  #define REUT_PG_PAT_CL_MUX_LMN_L_data_select_MSK                 (0x00000001)
  #define REUT_PG_PAT_CL_MUX_LMN_L_data_select_MIN                 (0)
  #define REUT_PG_PAT_CL_MUX_LMN_L_data_select_MAX                 (1) // 0x00000001
  #define REUT_PG_PAT_CL_MUX_LMN_L_data_select_DEF                 (0x00000000)
  #define REUT_PG_PAT_CL_MUX_LMN_L_data_select_HSH                 (0x01004A20)

  #define REUT_PG_PAT_CL_MUX_LMN_Enable_Sweep_Frequency_OFF        ( 1)
  #define REUT_PG_PAT_CL_MUX_LMN_Enable_Sweep_Frequency_WID        ( 1)
  #define REUT_PG_PAT_CL_MUX_LMN_Enable_Sweep_Frequency_MSK        (0x00000002)
  #define REUT_PG_PAT_CL_MUX_LMN_Enable_Sweep_Frequency_MIN        (0)
  #define REUT_PG_PAT_CL_MUX_LMN_Enable_Sweep_Frequency_MAX        (1) // 0x00000001
  #define REUT_PG_PAT_CL_MUX_LMN_Enable_Sweep_Frequency_DEF        (0x00000000)
  #define REUT_PG_PAT_CL_MUX_LMN_Enable_Sweep_Frequency_HSH        (0x01014A20)

  #define REUT_PG_PAT_CL_MUX_LMN_L_counter_OFF                     ( 8)
  #define REUT_PG_PAT_CL_MUX_LMN_L_counter_WID                     ( 8)
  #define REUT_PG_PAT_CL_MUX_LMN_L_counter_MSK                     (0x0000FF00)
  #define REUT_PG_PAT_CL_MUX_LMN_L_counter_MIN                     (0)
  #define REUT_PG_PAT_CL_MUX_LMN_L_counter_MAX                     (255) // 0x000000FF
  #define REUT_PG_PAT_CL_MUX_LMN_L_counter_DEF                     (0x00000001)
  #define REUT_PG_PAT_CL_MUX_LMN_L_counter_HSH                     (0x08084A20)

  #define REUT_PG_PAT_CL_MUX_LMN_M_counter_OFF                     (16)
  #define REUT_PG_PAT_CL_MUX_LMN_M_counter_WID                     ( 8)
  #define REUT_PG_PAT_CL_MUX_LMN_M_counter_MSK                     (0x00FF0000)
  #define REUT_PG_PAT_CL_MUX_LMN_M_counter_MIN                     (0)
  #define REUT_PG_PAT_CL_MUX_LMN_M_counter_MAX                     (255) // 0x000000FF
  #define REUT_PG_PAT_CL_MUX_LMN_M_counter_DEF                     (0x00000001)
  #define REUT_PG_PAT_CL_MUX_LMN_M_counter_HSH                     (0x08104A20)

  #define REUT_PG_PAT_CL_MUX_LMN_N_counter_OFF                     (24)
  #define REUT_PG_PAT_CL_MUX_LMN_N_counter_WID                     ( 8)
  #define REUT_PG_PAT_CL_MUX_LMN_N_counter_MSK                     (0xFF000000)
  #define REUT_PG_PAT_CL_MUX_LMN_N_counter_MIN                     (0)
  #define REUT_PG_PAT_CL_MUX_LMN_N_counter_MAX                     (255) // 0x000000FF
  #define REUT_PG_PAT_CL_MUX_LMN_N_counter_DEF                     (0x00000001)
  #define REUT_PG_PAT_CL_MUX_LMN_N_counter_HSH                     (0x08184A20)

#define REUT_PG_PAT_INV_REG                                        (0x00004A24)

  #define REUT_PG_PAT_INV_ECC_Inv_or_DC_Enable_OFF                 ( 0)
  #define REUT_PG_PAT_INV_ECC_Inv_or_DC_Enable_WID                 ( 8)
  #define REUT_PG_PAT_INV_ECC_Inv_or_DC_Enable_MSK                 (0x000000FF)
  #define REUT_PG_PAT_INV_ECC_Inv_or_DC_Enable_MIN                 (0)
  #define REUT_PG_PAT_INV_ECC_Inv_or_DC_Enable_MAX                 (255) // 0x000000FF
  #define REUT_PG_PAT_INV_ECC_Inv_or_DC_Enable_DEF                 (0x00000000)
  #define REUT_PG_PAT_INV_ECC_Inv_or_DC_Enable_HSH                 (0x08004A24)

  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Rate_OFF                 (16)
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Rate_WID                 ( 4)
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Rate_MSK                 (0x000F0000)
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Rate_MIN                 (0)
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Rate_MAX                 (15) // 0x0000000F
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Rate_DEF                 (0x00000000)
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Rate_HSH                 (0x04104A24)

  #define REUT_PG_PAT_INV_DC_Polarity_Control_OFF                  (20)
  #define REUT_PG_PAT_INV_DC_Polarity_Control_WID                  ( 1)
  #define REUT_PG_PAT_INV_DC_Polarity_Control_MSK                  (0x00100000)
  #define REUT_PG_PAT_INV_DC_Polarity_Control_MIN                  (0)
  #define REUT_PG_PAT_INV_DC_Polarity_Control_MAX                  (1) // 0x00000001
  #define REUT_PG_PAT_INV_DC_Polarity_Control_DEF                  (0x00000000)
  #define REUT_PG_PAT_INV_DC_Polarity_Control_HSH                  (0x01144A24)

  #define REUT_PG_PAT_INV_Inv_or_DC_Control_OFF                    (30)
  #define REUT_PG_PAT_INV_Inv_or_DC_Control_WID                    ( 1)
  #define REUT_PG_PAT_INV_Inv_or_DC_Control_MSK                    (0x40000000)
  #define REUT_PG_PAT_INV_Inv_or_DC_Control_MIN                    (0)
  #define REUT_PG_PAT_INV_Inv_or_DC_Control_MAX                    (1) // 0x00000001
  #define REUT_PG_PAT_INV_Inv_or_DC_Control_DEF                    (0x00000000)
  #define REUT_PG_PAT_INV_Inv_or_DC_Control_HSH                    (0x011E4A24)

  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Enable_OFF               (31)
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Enable_WID               ( 1)
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Enable_MSK               (0x80000000)
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Enable_MIN               (0)
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Enable_MAX               (1) // 0x00000001
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Enable_DEF               (0x00000000)
  #define REUT_PG_PAT_INV_Inv_or_DC_Shift_Enable_HSH               (0x011F4A24)

#define REUT_PG_PAT_DATA_INV_REG                                   (0x00004A28)

  #define REUT_PG_PAT_DATA_INV_Data_Inv_or_DC_Enable_OFF           ( 0)
  #define REUT_PG_PAT_DATA_INV_Data_Inv_or_DC_Enable_WID           (32)
  #define REUT_PG_PAT_DATA_INV_Data_Inv_or_DC_Enable_MSK           (0xFFFFFFFF)
  #define REUT_PG_PAT_DATA_INV_Data_Inv_or_DC_Enable_MIN           (0)
  #define REUT_PG_PAT_DATA_INV_Data_Inv_or_DC_Enable_MAX           (4294967295) // 0xFFFFFFFF
  #define REUT_PG_PAT_DATA_INV_Data_Inv_or_DC_Enable_DEF           (0x00000000)
  #define REUT_PG_PAT_DATA_INV_Data_Inv_or_DC_Enable_HSH           (0x20004A28)

#define REUT_PG_PATTERN_BUFFER_SHADOW_REG                          (0x00004A30)

  #define REUT_PG_PATTERN_BUFFER_SHADOW_Pattern_Buffer_Data_OFF    ( 0)
  #define REUT_PG_PATTERN_BUFFER_SHADOW_Pattern_Buffer_Data_WID    (37)
  #define REUT_PG_PATTERN_BUFFER_SHADOW_Pattern_Buffer_Data_MSK    (0x0000001FFFFFFFFFULL)
  #define REUT_PG_PATTERN_BUFFER_SHADOW_Pattern_Buffer_Data_MIN    (0)
  #define REUT_PG_PATTERN_BUFFER_SHADOW_Pattern_Buffer_Data_MAX    (137438953471ULL) // 0x1FFFFFFFFF
  #define REUT_PG_PATTERN_BUFFER_SHADOW_Pattern_Buffer_Data_DEF    (0x00000000)
  #define REUT_PG_PATTERN_BUFFER_SHADOW_Pattern_Buffer_Data_HSH    (0x65004A30)

#define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_0_REG                      (0x00004A38)

  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_0_Pattern_Buffer_OFF     ( 0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_0_Pattern_Buffer_WID     (24)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_0_Pattern_Buffer_MSK     (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_0_Pattern_Buffer_MIN     (0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_0_Pattern_Buffer_MAX     (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_0_Pattern_Buffer_DEF     (0x00000000)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_0_Pattern_Buffer_HSH     (0x18004A38)

#define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_1_REG                      (0x00004A3C)

  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_1_Pattern_Buffer_OFF     ( 0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_1_Pattern_Buffer_WID     (24)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_1_Pattern_Buffer_MSK     (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_1_Pattern_Buffer_MIN     (0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_1_Pattern_Buffer_MAX     (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_1_Pattern_Buffer_DEF     (0x00000000)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_1_Pattern_Buffer_HSH     (0x18004A3C)

#define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_2_REG                      (0x00004A40)

  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_2_Pattern_Buffer_OFF     ( 0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_2_Pattern_Buffer_WID     (24)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_2_Pattern_Buffer_MSK     (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_2_Pattern_Buffer_MIN     (0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_2_Pattern_Buffer_MAX     (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_2_Pattern_Buffer_DEF     (0x00000000)
  #define REUT_PG_PAT_CL_MUX_RD_PB_STATUS_2_Pattern_Buffer_HSH     (0x18004A40)

#define REUT_PG_PAT_CL_MUX_RD_PB_0_REG                             (0x00004A44)

  #define REUT_PG_PAT_CL_MUX_RD_PB_0_Pattern_Buffer_OFF            ( 0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_0_Pattern_Buffer_WID            (24)
  #define REUT_PG_PAT_CL_MUX_RD_PB_0_Pattern_Buffer_MSK            (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_RD_PB_0_Pattern_Buffer_MIN            (0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_0_Pattern_Buffer_MAX            (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_RD_PB_0_Pattern_Buffer_DEF            (0x00000000)
  #define REUT_PG_PAT_CL_MUX_RD_PB_0_Pattern_Buffer_HSH            (0x18004A44)

#define REUT_PG_PAT_CL_MUX_RD_PB_1_REG                             (0x00004A48)

  #define REUT_PG_PAT_CL_MUX_RD_PB_1_Pattern_Buffer_OFF            ( 0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_1_Pattern_Buffer_WID            (24)
  #define REUT_PG_PAT_CL_MUX_RD_PB_1_Pattern_Buffer_MSK            (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_RD_PB_1_Pattern_Buffer_MIN            (0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_1_Pattern_Buffer_MAX            (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_RD_PB_1_Pattern_Buffer_DEF            (0x00000000)
  #define REUT_PG_PAT_CL_MUX_RD_PB_1_Pattern_Buffer_HSH            (0x18004A48)

#define REUT_PG_PAT_CL_MUX_RD_PB_2_REG                             (0x00004A4C)

  #define REUT_PG_PAT_CL_MUX_RD_PB_2_Pattern_Buffer_OFF            ( 0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_2_Pattern_Buffer_WID            (24)
  #define REUT_PG_PAT_CL_MUX_RD_PB_2_Pattern_Buffer_MSK            (0x00FFFFFF)
  #define REUT_PG_PAT_CL_MUX_RD_PB_2_Pattern_Buffer_MIN            (0)
  #define REUT_PG_PAT_CL_MUX_RD_PB_2_Pattern_Buffer_MAX            (16777215) // 0x00FFFFFF
  #define REUT_PG_PAT_CL_MUX_RD_PB_2_Pattern_Buffer_DEF            (0x00000000)
  #define REUT_PG_PAT_CL_MUX_RD_PB_2_Pattern_Buffer_HSH            (0x18004A4C)

#define REUT_PG_PAT_CL_COUNTER_CFG_REG                             (0x00004A50)

  #define REUT_PG_PAT_CL_COUNTER_CFG_Cl_Counter_For_Shift_OFF      ( 0)
  #define REUT_PG_PAT_CL_COUNTER_CFG_Cl_Counter_For_Shift_WID      (32)
  #define REUT_PG_PAT_CL_COUNTER_CFG_Cl_Counter_For_Shift_MSK      (0xFFFFFFFF)
  #define REUT_PG_PAT_CL_COUNTER_CFG_Cl_Counter_For_Shift_MIN      (0)
  #define REUT_PG_PAT_CL_COUNTER_CFG_Cl_Counter_For_Shift_MAX      (4294967295) // 0xFFFFFFFF
  #define REUT_PG_PAT_CL_COUNTER_CFG_Cl_Counter_For_Shift_DEF      (0x00000000)
  #define REUT_PG_PAT_CL_COUNTER_CFG_Cl_Counter_For_Shift_HSH      (0x20004A50)

#define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_REG        (0x00004AD8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Chunk_Error_Status_OFF ( 0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Chunk_Error_Status_WID (16)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Chunk_Error_Status_MSK (0x0000FFFF)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Chunk_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Chunk_Error_Status_MAX (65535) // 0x0000FFFF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Chunk_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Chunk_Error_Status_HSH (0x50004AD8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Rank_Error_Status_OFF (16)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Rank_Error_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Rank_Error_Status_MSK (0x000F0000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Rank_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Rank_Error_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Rank_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Rank_Error_Status_HSH (0x44104AD8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Alert_Error_Status_OFF (20)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Alert_Error_Status_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Alert_Error_Status_MSK (0x00100000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Alert_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Alert_Error_Status_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Alert_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Alert_Error_Status_HSH (0x41144AD8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Byte_Group_Error_Status_OFF (21)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Byte_Group_Error_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Byte_Group_Error_Status_MSK (0x01E00000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Byte_Group_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Byte_Group_Error_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Byte_Group_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Byte_Group_Error_Status_HSH (0x44154AD8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Byte_Group_Error_Status_OFF (25)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Byte_Group_Error_Status_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Byte_Group_Error_Status_MSK (0x02000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Byte_Group_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Byte_Group_Error_Status_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Byte_Group_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Byte_Group_Error_Status_HSH (0x41194AD8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_WDB_Rd_Chunk_Num_Status_OFF (26)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_WDB_Rd_Chunk_Num_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_WDB_Rd_Chunk_Num_Status_MSK (0x3C000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_WDB_Rd_Chunk_Num_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_WDB_Rd_Chunk_Num_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_WDB_Rd_Chunk_Num_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_WDB_Rd_Chunk_Num_Status_HSH (0x441A4AD8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Error_Status_OFF (32)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Error_Status_WID ( 8)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Error_Status_MSK (0x000000FF00000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Error_Status_MAX (255) // 0x000000FF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_ECC_Error_Status_HSH (0x48204AD8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_OFF (40)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_WID (23)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_MSK (0x7FFFFF0000000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_MAX (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_HSH (0x57284AD8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_Overflow_OFF (63)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_Overflow_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_Overflow_MSK (0x8000000000000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_Overflow_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_Overflow_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_Overflow_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_Nth_Error_Overflow_HSH (0x413F4AD8)

#define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_REG        (0x00004AE0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Chunk_Error_Status_OFF ( 0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Chunk_Error_Status_WID (16)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Chunk_Error_Status_MSK (0x0000FFFF)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Chunk_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Chunk_Error_Status_MAX (65535) // 0x0000FFFF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Chunk_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Chunk_Error_Status_HSH (0x50004AE0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Rank_Error_Status_OFF (16)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Rank_Error_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Rank_Error_Status_MSK (0x000F0000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Rank_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Rank_Error_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Rank_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Rank_Error_Status_HSH (0x44104AE0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Alert_Error_Status_OFF (20)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Alert_Error_Status_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Alert_Error_Status_MSK (0x00100000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Alert_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Alert_Error_Status_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Alert_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Alert_Error_Status_HSH (0x41144AE0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Byte_Group_Error_Status_OFF (21)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Byte_Group_Error_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Byte_Group_Error_Status_MSK (0x01E00000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Byte_Group_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Byte_Group_Error_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Byte_Group_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Byte_Group_Error_Status_HSH (0x44154AE0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Byte_Group_Error_Status_OFF (25)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Byte_Group_Error_Status_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Byte_Group_Error_Status_MSK (0x02000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Byte_Group_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Byte_Group_Error_Status_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Byte_Group_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Byte_Group_Error_Status_HSH (0x41194AE0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_WDB_Rd_Chunk_Num_Status_OFF (26)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_WDB_Rd_Chunk_Num_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_WDB_Rd_Chunk_Num_Status_MSK (0x3C000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_WDB_Rd_Chunk_Num_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_WDB_Rd_Chunk_Num_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_WDB_Rd_Chunk_Num_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_WDB_Rd_Chunk_Num_Status_HSH (0x441A4AE0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Error_Status_OFF (32)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Error_Status_WID ( 8)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Error_Status_MSK (0x000000FF00000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Error_Status_MAX (255) // 0x000000FF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_ECC_Error_Status_HSH (0x48204AE0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_OFF (40)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_WID (23)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_MSK (0x7FFFFF0000000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_MAX (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_HSH (0x57284AE0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_Overflow_OFF (63)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_Overflow_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_Overflow_MSK (0x8000000000000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_Overflow_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_Overflow_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_Overflow_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_Nth_Error_Overflow_HSH (0x413F4AE0)

#define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_REG        (0x00004AE8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Chunk_Error_Status_OFF ( 0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Chunk_Error_Status_WID (16)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Chunk_Error_Status_MSK (0x0000FFFF)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Chunk_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Chunk_Error_Status_MAX (65535) // 0x0000FFFF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Chunk_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Chunk_Error_Status_HSH (0x50004AE8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Rank_Error_Status_OFF (16)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Rank_Error_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Rank_Error_Status_MSK (0x000F0000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Rank_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Rank_Error_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Rank_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Rank_Error_Status_HSH (0x44104AE8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Alert_Error_Status_OFF (20)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Alert_Error_Status_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Alert_Error_Status_MSK (0x00100000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Alert_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Alert_Error_Status_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Alert_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Alert_Error_Status_HSH (0x41144AE8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Byte_Group_Error_Status_OFF (21)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Byte_Group_Error_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Byte_Group_Error_Status_MSK (0x01E00000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Byte_Group_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Byte_Group_Error_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Byte_Group_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Byte_Group_Error_Status_HSH (0x44154AE8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Byte_Group_Error_Status_OFF (25)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Byte_Group_Error_Status_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Byte_Group_Error_Status_MSK (0x02000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Byte_Group_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Byte_Group_Error_Status_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Byte_Group_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Byte_Group_Error_Status_HSH (0x41194AE8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_WDB_Rd_Chunk_Num_Status_OFF (26)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_WDB_Rd_Chunk_Num_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_WDB_Rd_Chunk_Num_Status_MSK (0x3C000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_WDB_Rd_Chunk_Num_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_WDB_Rd_Chunk_Num_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_WDB_Rd_Chunk_Num_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_WDB_Rd_Chunk_Num_Status_HSH (0x441A4AE8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Error_Status_OFF (32)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Error_Status_WID ( 8)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Error_Status_MSK (0x000000FF00000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Error_Status_MAX (255) // 0x000000FF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_ECC_Error_Status_HSH (0x48204AE8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_OFF (40)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_WID (23)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_MSK (0x7FFFFF0000000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_MAX (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_HSH (0x57284AE8)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_Overflow_OFF (63)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_Overflow_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_Overflow_MSK (0x8000000000000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_Overflow_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_Overflow_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_Overflow_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_Nth_Error_Overflow_HSH (0x413F4AE8)

#define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_REG        (0x00004AF0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Chunk_Error_Status_OFF ( 0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Chunk_Error_Status_WID (16)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Chunk_Error_Status_MSK (0x0000FFFF)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Chunk_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Chunk_Error_Status_MAX (65535) // 0x0000FFFF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Chunk_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Chunk_Error_Status_HSH (0x50004AF0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Rank_Error_Status_OFF (16)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Rank_Error_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Rank_Error_Status_MSK (0x000F0000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Rank_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Rank_Error_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Rank_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Rank_Error_Status_HSH (0x44104AF0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Alert_Error_Status_OFF (20)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Alert_Error_Status_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Alert_Error_Status_MSK (0x00100000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Alert_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Alert_Error_Status_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Alert_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Alert_Error_Status_HSH (0x41144AF0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Byte_Group_Error_Status_OFF (21)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Byte_Group_Error_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Byte_Group_Error_Status_MSK (0x01E00000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Byte_Group_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Byte_Group_Error_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Byte_Group_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Byte_Group_Error_Status_HSH (0x44154AF0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Byte_Group_Error_Status_OFF (25)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Byte_Group_Error_Status_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Byte_Group_Error_Status_MSK (0x02000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Byte_Group_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Byte_Group_Error_Status_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Byte_Group_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Byte_Group_Error_Status_HSH (0x41194AF0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_WDB_Rd_Chunk_Num_Status_OFF (26)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_WDB_Rd_Chunk_Num_Status_WID ( 4)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_WDB_Rd_Chunk_Num_Status_MSK (0x3C000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_WDB_Rd_Chunk_Num_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_WDB_Rd_Chunk_Num_Status_MAX (15) // 0x0000000F
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_WDB_Rd_Chunk_Num_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_WDB_Rd_Chunk_Num_Status_HSH (0x441A4AF0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Error_Status_OFF (32)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Error_Status_WID ( 8)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Error_Status_MSK (0x000000FF00000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Error_Status_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Error_Status_MAX (255) // 0x000000FF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Error_Status_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_ECC_Error_Status_HSH (0x48204AF0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_OFF (40)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_WID (23)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_MSK (0x7FFFFF0000000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_MAX (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_HSH (0x57284AF0)

  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_Overflow_OFF (63)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_Overflow_WID ( 1)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_Overflow_MSK (0x8000000000000000ULL)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_Overflow_MIN (0)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_Overflow_MAX (1) // 0x00000001
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_Overflow_DEF (0x00000000)
  #define REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_Nth_Error_Overflow_HSH (0x413F4AF0)

#define REUT_SUBCH_ERR_DATA_MASK_0_REG                             (0x00004AF8)

  #define REUT_SUBCH_ERR_DATA_MASK_0_Data_Error_Mask_OFF           ( 0)
  #define REUT_SUBCH_ERR_DATA_MASK_0_Data_Error_Mask_WID           (32)
  #define REUT_SUBCH_ERR_DATA_MASK_0_Data_Error_Mask_MSK           (0xFFFFFFFF)
  #define REUT_SUBCH_ERR_DATA_MASK_0_Data_Error_Mask_MIN           (0)
  #define REUT_SUBCH_ERR_DATA_MASK_0_Data_Error_Mask_MAX           (4294967295) // 0xFFFFFFFF
  #define REUT_SUBCH_ERR_DATA_MASK_0_Data_Error_Mask_DEF           (0x00000000)
  #define REUT_SUBCH_ERR_DATA_MASK_0_Data_Error_Mask_HSH           (0x20004AF8)

#define REUT_SUBCH_ERR_DATA_MASK_1_REG                             (0x00004AFC)

  #define REUT_SUBCH_ERR_DATA_MASK_1_Data_Error_Mask_OFF           ( 0)
  #define REUT_SUBCH_ERR_DATA_MASK_1_Data_Error_Mask_WID           (32)
  #define REUT_SUBCH_ERR_DATA_MASK_1_Data_Error_Mask_MSK           (0xFFFFFFFF)
  #define REUT_SUBCH_ERR_DATA_MASK_1_Data_Error_Mask_MIN           (0)
  #define REUT_SUBCH_ERR_DATA_MASK_1_Data_Error_Mask_MAX           (4294967295) // 0xFFFFFFFF
  #define REUT_SUBCH_ERR_DATA_MASK_1_Data_Error_Mask_DEF           (0x00000000)
  #define REUT_SUBCH_ERR_DATA_MASK_1_Data_Error_Mask_HSH           (0x20004AFC)

#define REUT_SUBCH_ERR_DATA_MASK_2_REG                             (0x00004B00)

  #define REUT_SUBCH_ERR_DATA_MASK_2_Data_Error_Mask_OFF           ( 0)
  #define REUT_SUBCH_ERR_DATA_MASK_2_Data_Error_Mask_WID           (32)
  #define REUT_SUBCH_ERR_DATA_MASK_2_Data_Error_Mask_MSK           (0xFFFFFFFF)
  #define REUT_SUBCH_ERR_DATA_MASK_2_Data_Error_Mask_MIN           (0)
  #define REUT_SUBCH_ERR_DATA_MASK_2_Data_Error_Mask_MAX           (4294967295) // 0xFFFFFFFF
  #define REUT_SUBCH_ERR_DATA_MASK_2_Data_Error_Mask_DEF           (0x00000000)
  #define REUT_SUBCH_ERR_DATA_MASK_2_Data_Error_Mask_HSH           (0x20004B00)

#define REUT_SUBCH_ERR_DATA_MASK_3_REG                             (0x00004B04)

  #define REUT_SUBCH_ERR_DATA_MASK_3_Data_Error_Mask_OFF           ( 0)
  #define REUT_SUBCH_ERR_DATA_MASK_3_Data_Error_Mask_WID           (32)
  #define REUT_SUBCH_ERR_DATA_MASK_3_Data_Error_Mask_MSK           (0xFFFFFFFF)
  #define REUT_SUBCH_ERR_DATA_MASK_3_Data_Error_Mask_MIN           (0)
  #define REUT_SUBCH_ERR_DATA_MASK_3_Data_Error_Mask_MAX           (4294967295) // 0xFFFFFFFF
  #define REUT_SUBCH_ERR_DATA_MASK_3_Data_Error_Mask_DEF           (0x00000000)
  #define REUT_SUBCH_ERR_DATA_MASK_3_Data_Error_Mask_HSH           (0x20004B04)

#define REUT_CH_ERR_ECC_MASK_0_REG                                 (0x00004B08)

  #define REUT_CH_ERR_ECC_MASK_0_ECC_Error_Mask_OFF                ( 0)
  #define REUT_CH_ERR_ECC_MASK_0_ECC_Error_Mask_WID                ( 8)
  #define REUT_CH_ERR_ECC_MASK_0_ECC_Error_Mask_MSK                (0x000000FF)
  #define REUT_CH_ERR_ECC_MASK_0_ECC_Error_Mask_MIN                (0)
  #define REUT_CH_ERR_ECC_MASK_0_ECC_Error_Mask_MAX                (255) // 0x000000FF
  #define REUT_CH_ERR_ECC_MASK_0_ECC_Error_Mask_DEF                (0x00000000)
  #define REUT_CH_ERR_ECC_MASK_0_ECC_Error_Mask_HSH                (0x08004B08)

  #define REUT_CH_ERR_ECC_MASK_0_Stop_on_CA_ALERT_OFF              ( 8)
  #define REUT_CH_ERR_ECC_MASK_0_Stop_on_CA_ALERT_WID              ( 1)
  #define REUT_CH_ERR_ECC_MASK_0_Stop_on_CA_ALERT_MSK              (0x00000100)
  #define REUT_CH_ERR_ECC_MASK_0_Stop_on_CA_ALERT_MIN              (0)
  #define REUT_CH_ERR_ECC_MASK_0_Stop_on_CA_ALERT_MAX              (1) // 0x00000001
  #define REUT_CH_ERR_ECC_MASK_0_Stop_on_CA_ALERT_DEF              (0x00000000)
  #define REUT_CH_ERR_ECC_MASK_0_Stop_on_CA_ALERT_HSH              (0x01084B08)

#define REUT_CH_ERR_ECC_MASK_1_REG                                 (0x00004B0C)

  #define REUT_CH_ERR_ECC_MASK_1_ECC_Error_Mask_OFF                ( 0)
  #define REUT_CH_ERR_ECC_MASK_1_ECC_Error_Mask_WID                ( 8)
  #define REUT_CH_ERR_ECC_MASK_1_ECC_Error_Mask_MSK                (0x000000FF)
  #define REUT_CH_ERR_ECC_MASK_1_ECC_Error_Mask_MIN                (0)
  #define REUT_CH_ERR_ECC_MASK_1_ECC_Error_Mask_MAX                (255) // 0x000000FF
  #define REUT_CH_ERR_ECC_MASK_1_ECC_Error_Mask_DEF                (0x00000000)
  #define REUT_CH_ERR_ECC_MASK_1_ECC_Error_Mask_HSH                (0x08004B0C)

  #define REUT_CH_ERR_ECC_MASK_1_Stop_on_CA_ALERT_OFF              ( 8)
  #define REUT_CH_ERR_ECC_MASK_1_Stop_on_CA_ALERT_WID              ( 1)
  #define REUT_CH_ERR_ECC_MASK_1_Stop_on_CA_ALERT_MSK              (0x00000100)
  #define REUT_CH_ERR_ECC_MASK_1_Stop_on_CA_ALERT_MIN              (0)
  #define REUT_CH_ERR_ECC_MASK_1_Stop_on_CA_ALERT_MAX              (1) // 0x00000001
  #define REUT_CH_ERR_ECC_MASK_1_Stop_on_CA_ALERT_DEF              (0x00000000)
  #define REUT_CH_ERR_ECC_MASK_1_Stop_on_CA_ALERT_HSH              (0x01084B0C)

#define REUT_SUBCH_ERR_DATA_STATUS_0_REG                           (0x00004B10)

  #define REUT_SUBCH_ERR_DATA_STATUS_0_Data_Error_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_DATA_STATUS_0_Data_Error_Status_WID       (32)
  #define REUT_SUBCH_ERR_DATA_STATUS_0_Data_Error_Status_MSK       (0xFFFFFFFF)
  #define REUT_SUBCH_ERR_DATA_STATUS_0_Data_Error_Status_MIN       (0)
  #define REUT_SUBCH_ERR_DATA_STATUS_0_Data_Error_Status_MAX       (4294967295) // 0xFFFFFFFF
  #define REUT_SUBCH_ERR_DATA_STATUS_0_Data_Error_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_DATA_STATUS_0_Data_Error_Status_HSH       (0x20004B10)

#define REUT_SUBCH_ERR_DATA_STATUS_1_REG                           (0x00004B14)

  #define REUT_SUBCH_ERR_DATA_STATUS_1_Data_Error_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_DATA_STATUS_1_Data_Error_Status_WID       (32)
  #define REUT_SUBCH_ERR_DATA_STATUS_1_Data_Error_Status_MSK       (0xFFFFFFFF)
  #define REUT_SUBCH_ERR_DATA_STATUS_1_Data_Error_Status_MIN       (0)
  #define REUT_SUBCH_ERR_DATA_STATUS_1_Data_Error_Status_MAX       (4294967295) // 0xFFFFFFFF
  #define REUT_SUBCH_ERR_DATA_STATUS_1_Data_Error_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_DATA_STATUS_1_Data_Error_Status_HSH       (0x20004B14)

#define REUT_SUBCH_ERR_DATA_STATUS_2_REG                           (0x00004B18)

  #define REUT_SUBCH_ERR_DATA_STATUS_2_Data_Error_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_DATA_STATUS_2_Data_Error_Status_WID       (32)
  #define REUT_SUBCH_ERR_DATA_STATUS_2_Data_Error_Status_MSK       (0xFFFFFFFF)
  #define REUT_SUBCH_ERR_DATA_STATUS_2_Data_Error_Status_MIN       (0)
  #define REUT_SUBCH_ERR_DATA_STATUS_2_Data_Error_Status_MAX       (4294967295) // 0xFFFFFFFF
  #define REUT_SUBCH_ERR_DATA_STATUS_2_Data_Error_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_DATA_STATUS_2_Data_Error_Status_HSH       (0x20004B18)

#define REUT_SUBCH_ERR_DATA_STATUS_3_REG                           (0x00004B1C)

  #define REUT_SUBCH_ERR_DATA_STATUS_3_Data_Error_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_DATA_STATUS_3_Data_Error_Status_WID       (32)
  #define REUT_SUBCH_ERR_DATA_STATUS_3_Data_Error_Status_MSK       (0xFFFFFFFF)
  #define REUT_SUBCH_ERR_DATA_STATUS_3_Data_Error_Status_MIN       (0)
  #define REUT_SUBCH_ERR_DATA_STATUS_3_Data_Error_Status_MAX       (4294967295) // 0xFFFFFFFF
  #define REUT_SUBCH_ERR_DATA_STATUS_3_Data_Error_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_DATA_STATUS_3_Data_Error_Status_HSH       (0x20004B1C)

#define REUT_SUBCH_ERROR_ADDR_0_REG                                (0x00004B20)

  #define REUT_SUBCH_ERROR_ADDR_0_Column_Address_OFF               ( 0)
  #define REUT_SUBCH_ERROR_ADDR_0_Column_Address_WID               (12)
  #define REUT_SUBCH_ERROR_ADDR_0_Column_Address_MSK               (0x00000FFF)
  #define REUT_SUBCH_ERROR_ADDR_0_Column_Address_MIN               (0)
  #define REUT_SUBCH_ERROR_ADDR_0_Column_Address_MAX               (4095) // 0x00000FFF
  #define REUT_SUBCH_ERROR_ADDR_0_Column_Address_DEF               (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_0_Column_Address_HSH               (0x4C004B20)

  #define REUT_SUBCH_ERROR_ADDR_0_Row_Address_OFF                  (12)
  #define REUT_SUBCH_ERROR_ADDR_0_Row_Address_WID                  (17)
  #define REUT_SUBCH_ERROR_ADDR_0_Row_Address_MSK                  (0x1FFFF000)
  #define REUT_SUBCH_ERROR_ADDR_0_Row_Address_MIN                  (0)
  #define REUT_SUBCH_ERROR_ADDR_0_Row_Address_MAX                  (131071) // 0x0001FFFF
  #define REUT_SUBCH_ERROR_ADDR_0_Row_Address_DEF                  (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_0_Row_Address_HSH                  (0x510C4B20)

  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_OFF                 (48)
  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_WID                 ( 5)
  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_MSK                 (0x001F000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_WID_A0              ( 4)
  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_MSK_A0              (0x000F000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_MIN                 (0)
  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_MAX                 (31) // 0x0000001F
  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_MAX_A0              (15) // 0x0000000F
  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_DEF                 (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_HSH                 (0x45304B20)
  #define REUT_SUBCH_ERROR_ADDR_0_Bank_Address_HSH_A0              (0x44304B20)

  #define REUT_SUBCH_ERROR_ADDR_0_Rank_Address_OFF                 (56)
  #define REUT_SUBCH_ERROR_ADDR_0_Rank_Address_WID                 ( 2)
  #define REUT_SUBCH_ERROR_ADDR_0_Rank_Address_MSK                 (0x0300000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_0_Rank_Address_MIN                 (0)
  #define REUT_SUBCH_ERROR_ADDR_0_Rank_Address_MAX                 (3) // 0x00000003
  #define REUT_SUBCH_ERROR_ADDR_0_Rank_Address_DEF                 (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_0_Rank_Address_HSH                 (0x42384B20)

#define REUT_SUBCH_ERROR_ADDR_1_REG                                (0x00004B28)

  #define REUT_SUBCH_ERROR_ADDR_1_Column_Address_OFF               ( 0)
  #define REUT_SUBCH_ERROR_ADDR_1_Column_Address_WID               (12)
  #define REUT_SUBCH_ERROR_ADDR_1_Column_Address_MSK               (0x00000FFF)
  #define REUT_SUBCH_ERROR_ADDR_1_Column_Address_MIN               (0)
  #define REUT_SUBCH_ERROR_ADDR_1_Column_Address_MAX               (4095) // 0x00000FFF
  #define REUT_SUBCH_ERROR_ADDR_1_Column_Address_DEF               (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_1_Column_Address_HSH               (0x4C004B28)

  #define REUT_SUBCH_ERROR_ADDR_1_Row_Address_OFF                  (12)
  #define REUT_SUBCH_ERROR_ADDR_1_Row_Address_WID                  (17)
  #define REUT_SUBCH_ERROR_ADDR_1_Row_Address_MSK                  (0x1FFFF000)
  #define REUT_SUBCH_ERROR_ADDR_1_Row_Address_MIN                  (0)
  #define REUT_SUBCH_ERROR_ADDR_1_Row_Address_MAX                  (131071) // 0x0001FFFF
  #define REUT_SUBCH_ERROR_ADDR_1_Row_Address_DEF                  (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_1_Row_Address_HSH                  (0x510C4B28)

  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_OFF                 (48)
  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_WID                 ( 5)
  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_MSK                 (0x001F000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_WID_A0              ( 4)
  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_MSK_A0              (0x000F000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_MIN                 (0)
  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_MAX                 (31) // 0x0000001F
  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_MAX_A0              (15) // 0x0000000F
  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_DEF                 (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_HSH                 (0x45304B28)
  #define REUT_SUBCH_ERROR_ADDR_1_Bank_Address_HSH_A0              (0x44304B28)

  #define REUT_SUBCH_ERROR_ADDR_1_Rank_Address_OFF                 (56)
  #define REUT_SUBCH_ERROR_ADDR_1_Rank_Address_WID                 ( 2)
  #define REUT_SUBCH_ERROR_ADDR_1_Rank_Address_MSK                 (0x0300000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_1_Rank_Address_MIN                 (0)
  #define REUT_SUBCH_ERROR_ADDR_1_Rank_Address_MAX                 (3) // 0x00000003
  #define REUT_SUBCH_ERROR_ADDR_1_Rank_Address_DEF                 (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_1_Rank_Address_HSH                 (0x42384B28)

#define REUT_SUBCH_ERROR_ADDR_2_REG                                (0x00004B30)

  #define REUT_SUBCH_ERROR_ADDR_2_Column_Address_OFF               ( 0)
  #define REUT_SUBCH_ERROR_ADDR_2_Column_Address_WID               (12)
  #define REUT_SUBCH_ERROR_ADDR_2_Column_Address_MSK               (0x00000FFF)
  #define REUT_SUBCH_ERROR_ADDR_2_Column_Address_MIN               (0)
  #define REUT_SUBCH_ERROR_ADDR_2_Column_Address_MAX               (4095) // 0x00000FFF
  #define REUT_SUBCH_ERROR_ADDR_2_Column_Address_DEF               (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_2_Column_Address_HSH               (0x4C004B30)

  #define REUT_SUBCH_ERROR_ADDR_2_Row_Address_OFF                  (12)
  #define REUT_SUBCH_ERROR_ADDR_2_Row_Address_WID                  (17)
  #define REUT_SUBCH_ERROR_ADDR_2_Row_Address_MSK                  (0x1FFFF000)
  #define REUT_SUBCH_ERROR_ADDR_2_Row_Address_MIN                  (0)
  #define REUT_SUBCH_ERROR_ADDR_2_Row_Address_MAX                  (131071) // 0x0001FFFF
  #define REUT_SUBCH_ERROR_ADDR_2_Row_Address_DEF                  (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_2_Row_Address_HSH                  (0x510C4B30)

  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_OFF                 (48)
  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_WID                 ( 5)
  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_MSK                 (0x001F000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_WID_A0              ( 4)
  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_MSK_A0              (0x000F000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_MIN                 (0)
  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_MAX                 (31) // 0x0000001F
  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_MAX_A0              (15) // 0x0000000F
  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_DEF                 (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_HSH                 (0x45304B30)
  #define REUT_SUBCH_ERROR_ADDR_2_Bank_Address_HSH_A0              (0x44304B30)

  #define REUT_SUBCH_ERROR_ADDR_2_Rank_Address_OFF                 (56)
  #define REUT_SUBCH_ERROR_ADDR_2_Rank_Address_WID                 ( 2)
  #define REUT_SUBCH_ERROR_ADDR_2_Rank_Address_MSK                 (0x0300000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_2_Rank_Address_MIN                 (0)
  #define REUT_SUBCH_ERROR_ADDR_2_Rank_Address_MAX                 (3) // 0x00000003
  #define REUT_SUBCH_ERROR_ADDR_2_Rank_Address_DEF                 (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_2_Rank_Address_HSH                 (0x42384B30)

#define REUT_SUBCH_ERROR_ADDR_3_REG                                (0x00004B38)

  #define REUT_SUBCH_ERROR_ADDR_3_Column_Address_OFF               ( 0)
  #define REUT_SUBCH_ERROR_ADDR_3_Column_Address_WID               (12)
  #define REUT_SUBCH_ERROR_ADDR_3_Column_Address_MSK               (0x00000FFF)
  #define REUT_SUBCH_ERROR_ADDR_3_Column_Address_MIN               (0)
  #define REUT_SUBCH_ERROR_ADDR_3_Column_Address_MAX               (4095) // 0x00000FFF
  #define REUT_SUBCH_ERROR_ADDR_3_Column_Address_DEF               (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_3_Column_Address_HSH               (0x4C004B38)

  #define REUT_SUBCH_ERROR_ADDR_3_Row_Address_OFF                  (12)
  #define REUT_SUBCH_ERROR_ADDR_3_Row_Address_WID                  (17)
  #define REUT_SUBCH_ERROR_ADDR_3_Row_Address_MSK                  (0x1FFFF000)
  #define REUT_SUBCH_ERROR_ADDR_3_Row_Address_MIN                  (0)
  #define REUT_SUBCH_ERROR_ADDR_3_Row_Address_MAX                  (131071) // 0x0001FFFF
  #define REUT_SUBCH_ERROR_ADDR_3_Row_Address_DEF                  (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_3_Row_Address_HSH                  (0x510C4B38)

  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_OFF                 (48)
  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_WID                 ( 5)
  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_MSK                 (0x001F000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_WID_A0              ( 4)
  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_MSK_A0              (0x000F000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_MIN                 (0)
  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_MAX                 (31) // 0x0000001F
  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_MAX_A0              (15) // 0x0000000F
  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_DEF                 (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_HSH                 (0x45304B38)
  #define REUT_SUBCH_ERROR_ADDR_3_Bank_Address_HSH_A0              (0x44304B38)

  #define REUT_SUBCH_ERROR_ADDR_3_Rank_Address_OFF                 (56)
  #define REUT_SUBCH_ERROR_ADDR_3_Rank_Address_WID                 ( 2)
  #define REUT_SUBCH_ERROR_ADDR_3_Rank_Address_MSK                 (0x0300000000000000ULL)
  #define REUT_SUBCH_ERROR_ADDR_3_Rank_Address_MIN                 (0)
  #define REUT_SUBCH_ERROR_ADDR_3_Rank_Address_MAX                 (3) // 0x00000003
  #define REUT_SUBCH_ERROR_ADDR_3_Rank_Address_DEF                 (0x00000000)
  #define REUT_SUBCH_ERROR_ADDR_3_Rank_Address_HSH                 (0x42384B38)

#define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_0_REG                  (0x00004B40)

  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_0_Counter_Overflow_Status_OFF ( 0)
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_0_Counter_Overflow_Status_WID ( 9)
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_0_Counter_Overflow_Status_MSK (0x000001FF)
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_0_Counter_Overflow_Status_MIN (0)
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_0_Counter_Overflow_Status_MAX (511) // 0x000001FF
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_0_Counter_Overflow_Status_DEF (0x00000000)
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_0_Counter_Overflow_Status_HSH (0x09004B40)

#define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_1_REG                  (0x00004B44)

  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_1_Counter_Overflow_Status_OFF ( 0)
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_1_Counter_Overflow_Status_WID ( 9)
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_1_Counter_Overflow_Status_MSK (0x000001FF)
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_1_Counter_Overflow_Status_MIN (0)
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_1_Counter_Overflow_Status_MAX (511) // 0x000001FF
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_1_Counter_Overflow_Status_DEF (0x00000000)
  #define REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_1_Counter_Overflow_Status_HSH (0x09004B44)

#define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_REG                     (0x00004B48)

  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Write_Address_as_Data_OFF ( 0)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Write_Address_as_Data_WID ( 1)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Write_Address_as_Data_MSK (0x00000001)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Write_Address_as_Data_MIN (0)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Write_Address_as_Data_MAX (1) // 0x00000001
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Write_Address_as_Data_DEF (0x00000000)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Write_Address_as_Data_HSH (0x01004B48)

  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Read_Address_as_Data_OFF ( 1)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Read_Address_as_Data_WID ( 1)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Read_Address_as_Data_MSK (0x00000002)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Read_Address_as_Data_MIN (0)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Read_Address_as_Data_MAX (1) // 0x00000001
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Read_Address_as_Data_DEF (0x00000000)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_Read_Address_as_Data_HSH (0x01014B48)

#define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_REG                     (0x00004B4C)

  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Write_Address_as_Data_OFF ( 0)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Write_Address_as_Data_WID ( 1)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Write_Address_as_Data_MSK (0x00000001)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Write_Address_as_Data_MIN (0)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Write_Address_as_Data_MAX (1) // 0x00000001
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Write_Address_as_Data_DEF (0x00000000)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Write_Address_as_Data_HSH (0x01004B4C)

  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Read_Address_as_Data_OFF ( 1)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Read_Address_as_Data_WID ( 1)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Read_Address_as_Data_MSK (0x00000002)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Read_Address_as_Data_MIN (0)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Read_Address_as_Data_MAX (1) // 0x00000001
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Read_Address_as_Data_DEF (0x00000000)
  #define REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_Read_Address_as_Data_HSH (0x01014B4C)

#define REUT_SUBCH_ERR_COUNTER_STATUS_0_REG                        (0x00004B50)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_0_Counter_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_0_Counter_Status_WID       (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_0_Counter_Status_MSK       (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_0_Counter_Status_MIN       (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_0_Counter_Status_MAX       (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_0_Counter_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_0_Counter_Status_HSH       (0x17004B50)

#define REUT_SUBCH_ERR_COUNTER_STATUS_1_REG                        (0x00004B54)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_1_Counter_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_1_Counter_Status_WID       (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_1_Counter_Status_MSK       (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_1_Counter_Status_MIN       (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_1_Counter_Status_MAX       (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_1_Counter_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_1_Counter_Status_HSH       (0x17004B54)

#define REUT_SUBCH_ERR_COUNTER_STATUS_2_REG                        (0x00004B58)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_2_Counter_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_2_Counter_Status_WID       (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_2_Counter_Status_MSK       (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_2_Counter_Status_MIN       (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_2_Counter_Status_MAX       (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_2_Counter_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_2_Counter_Status_HSH       (0x17004B58)

#define REUT_SUBCH_ERR_COUNTER_STATUS_3_REG                        (0x00004B5C)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_3_Counter_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_3_Counter_Status_WID       (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_3_Counter_Status_MSK       (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_3_Counter_Status_MIN       (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_3_Counter_Status_MAX       (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_3_Counter_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_3_Counter_Status_HSH       (0x17004B5C)

#define REUT_SUBCH_ERR_COUNTER_STATUS_4_REG                        (0x00004B60)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_4_Counter_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_4_Counter_Status_WID       (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_4_Counter_Status_MSK       (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_4_Counter_Status_MIN       (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_4_Counter_Status_MAX       (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_4_Counter_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_4_Counter_Status_HSH       (0x17004B60)

#define REUT_SUBCH_ERR_COUNTER_STATUS_5_REG                        (0x00004B64)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_5_Counter_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_5_Counter_Status_WID       (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_5_Counter_Status_MSK       (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_5_Counter_Status_MIN       (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_5_Counter_Status_MAX       (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_5_Counter_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_5_Counter_Status_HSH       (0x17004B64)

#define REUT_SUBCH_ERR_COUNTER_STATUS_6_REG                        (0x00004B68)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_6_Counter_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_6_Counter_Status_WID       (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_6_Counter_Status_MSK       (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_6_Counter_Status_MIN       (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_6_Counter_Status_MAX       (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_6_Counter_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_6_Counter_Status_HSH       (0x17004B68)

#define REUT_SUBCH_ERR_COUNTER_STATUS_7_REG                        (0x00004B6C)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_7_Counter_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_7_Counter_Status_WID       (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_7_Counter_Status_MSK       (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_7_Counter_Status_MIN       (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_7_Counter_Status_MAX       (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_7_Counter_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_7_Counter_Status_HSH       (0x17004B6C)

#define REUT_SUBCH_ERR_COUNTER_STATUS_8_REG                        (0x00004B70)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_8_Counter_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_8_Counter_Status_WID       (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_8_Counter_Status_MSK       (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_8_Counter_Status_MIN       (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_8_Counter_Status_MAX       (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_8_Counter_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_8_Counter_Status_HSH       (0x17004B70)

#define REUT_SUBCH_ERR_COUNTER_STATUS_9_REG                        (0x00004B74)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_9_Counter_Status_OFF       ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_9_Counter_Status_WID       (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_9_Counter_Status_MSK       (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_9_Counter_Status_MIN       (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_9_Counter_Status_MAX       (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_9_Counter_Status_DEF       (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_9_Counter_Status_HSH       (0x17004B74)

#define REUT_SUBCH_ERR_COUNTER_STATUS_10_REG                       (0x00004B78)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_10_Counter_Status_OFF      ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_10_Counter_Status_WID      (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_10_Counter_Status_MSK      (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_10_Counter_Status_MIN      (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_10_Counter_Status_MAX      (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_10_Counter_Status_DEF      (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_10_Counter_Status_HSH      (0x17004B78)

#define REUT_SUBCH_ERR_COUNTER_STATUS_11_REG                       (0x00004B7C)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_11_Counter_Status_OFF      ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_11_Counter_Status_WID      (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_11_Counter_Status_MSK      (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_11_Counter_Status_MIN      (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_11_Counter_Status_MAX      (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_11_Counter_Status_DEF      (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_11_Counter_Status_HSH      (0x17004B7C)

#define REUT_SUBCH_ERR_COUNTER_STATUS_12_REG                       (0x00004B80)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_12_Counter_Status_OFF      ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_12_Counter_Status_WID      (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_12_Counter_Status_MSK      (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_12_Counter_Status_MIN      (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_12_Counter_Status_MAX      (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_12_Counter_Status_DEF      (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_12_Counter_Status_HSH      (0x17004B80)

#define REUT_SUBCH_ERR_COUNTER_STATUS_13_REG                       (0x00004B84)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_13_Counter_Status_OFF      ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_13_Counter_Status_WID      (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_13_Counter_Status_MSK      (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_13_Counter_Status_MIN      (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_13_Counter_Status_MAX      (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_13_Counter_Status_DEF      (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_13_Counter_Status_HSH      (0x17004B84)

#define REUT_SUBCH_ERR_COUNTER_STATUS_14_REG                       (0x00004B88)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_14_Counter_Status_OFF      ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_14_Counter_Status_WID      (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_14_Counter_Status_MSK      (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_14_Counter_Status_MIN      (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_14_Counter_Status_MAX      (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_14_Counter_Status_DEF      (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_14_Counter_Status_HSH      (0x17004B88)

#define REUT_SUBCH_ERR_COUNTER_STATUS_15_REG                       (0x00004B8C)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_15_Counter_Status_OFF      ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_15_Counter_Status_WID      (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_15_Counter_Status_MSK      (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_15_Counter_Status_MIN      (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_15_Counter_Status_MAX      (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_15_Counter_Status_DEF      (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_15_Counter_Status_HSH      (0x17004B8C)

#define REUT_SUBCH_ERR_COUNTER_STATUS_16_REG                       (0x00004B90)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_16_Counter_Status_OFF      ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_16_Counter_Status_WID      (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_16_Counter_Status_MSK      (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_16_Counter_Status_MIN      (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_16_Counter_Status_MAX      (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_16_Counter_Status_DEF      (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_16_Counter_Status_HSH      (0x17004B90)

#define REUT_SUBCH_ERR_COUNTER_STATUS_17_REG                       (0x00004B94)

  #define REUT_SUBCH_ERR_COUNTER_STATUS_17_Counter_Status_OFF      ( 0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_17_Counter_Status_WID      (23)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_17_Counter_Status_MSK      (0x007FFFFF)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_17_Counter_Status_MIN      (0)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_17_Counter_Status_MAX      (8388607) // 0x007FFFFF
  #define REUT_SUBCH_ERR_COUNTER_STATUS_17_Counter_Status_DEF      (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_STATUS_17_Counter_Status_HSH      (0x17004B94)

#define REUT_SUBCH_ERR_COUNTER_CTL_0_REG                           (0x00004B98)

  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Pointer_OFF         ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Pointer_WID         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Pointer_MSK         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Pointer_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Pointer_MAX         (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Pointer_DEF         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Pointer_HSH         (0x07004B98)

  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Control_OFF         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Control_WID         ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Control_MSK         (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Control_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Control_MAX         (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Control_DEF         (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_0_Counter_Control_HSH         (0x02074B98)

#define REUT_SUBCH_ERR_COUNTER_CTL_1_REG                           (0x00004B9C)

  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Pointer_OFF         ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Pointer_WID         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Pointer_MSK         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Pointer_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Pointer_MAX         (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Pointer_DEF         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Pointer_HSH         (0x07004B9C)

  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Control_OFF         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Control_WID         ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Control_MSK         (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Control_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Control_MAX         (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Control_DEF         (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_1_Counter_Control_HSH         (0x02074B9C)

#define REUT_SUBCH_ERR_COUNTER_CTL_2_REG                           (0x00004BA0)

  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Pointer_OFF         ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Pointer_WID         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Pointer_MSK         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Pointer_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Pointer_MAX         (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Pointer_DEF         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Pointer_HSH         (0x07004BA0)

  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Control_OFF         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Control_WID         ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Control_MSK         (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Control_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Control_MAX         (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Control_DEF         (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_2_Counter_Control_HSH         (0x02074BA0)

#define REUT_SUBCH_ERR_COUNTER_CTL_3_REG                           (0x00004BA4)

  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Pointer_OFF         ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Pointer_WID         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Pointer_MSK         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Pointer_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Pointer_MAX         (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Pointer_DEF         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Pointer_HSH         (0x07004BA4)

  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Control_OFF         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Control_WID         ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Control_MSK         (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Control_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Control_MAX         (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Control_DEF         (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_3_Counter_Control_HSH         (0x02074BA4)

#define REUT_SUBCH_ERR_COUNTER_CTL_4_REG                           (0x00004BA8)

  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Pointer_OFF         ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Pointer_WID         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Pointer_MSK         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Pointer_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Pointer_MAX         (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Pointer_DEF         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Pointer_HSH         (0x07004BA8)

  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Control_OFF         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Control_WID         ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Control_MSK         (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Control_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Control_MAX         (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Control_DEF         (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_4_Counter_Control_HSH         (0x02074BA8)

#define REUT_SUBCH_ERR_COUNTER_CTL_5_REG                           (0x00004BAC)

  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Pointer_OFF         ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Pointer_WID         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Pointer_MSK         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Pointer_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Pointer_MAX         (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Pointer_DEF         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Pointer_HSH         (0x07004BAC)

  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Control_OFF         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Control_WID         ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Control_MSK         (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Control_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Control_MAX         (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Control_DEF         (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_5_Counter_Control_HSH         (0x02074BAC)

#define REUT_SUBCH_ERR_COUNTER_CTL_6_REG                           (0x00004BB0)

  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Pointer_OFF         ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Pointer_WID         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Pointer_MSK         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Pointer_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Pointer_MAX         (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Pointer_DEF         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Pointer_HSH         (0x07004BB0)

  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Control_OFF         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Control_WID         ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Control_MSK         (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Control_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Control_MAX         (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Control_DEF         (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_6_Counter_Control_HSH         (0x02074BB0)

#define REUT_SUBCH_ERR_COUNTER_CTL_7_REG                           (0x00004BB4)

  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Pointer_OFF         ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Pointer_WID         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Pointer_MSK         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Pointer_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Pointer_MAX         (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Pointer_DEF         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Pointer_HSH         (0x07004BB4)

  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Control_OFF         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Control_WID         ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Control_MSK         (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Control_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Control_MAX         (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Control_DEF         (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_7_Counter_Control_HSH         (0x02074BB4)

#define REUT_SUBCH_ERR_COUNTER_CTL_8_REG                           (0x00004BB8)

  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Pointer_OFF         ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Pointer_WID         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Pointer_MSK         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Pointer_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Pointer_MAX         (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Pointer_DEF         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Pointer_HSH         (0x07004BB8)

  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Control_OFF         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Control_WID         ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Control_MSK         (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Control_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Control_MAX         (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Control_DEF         (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_8_Counter_Control_HSH         (0x02074BB8)

#define REUT_SUBCH_ERR_COUNTER_CTL_9_REG                           (0x00004BBC)

  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Pointer_OFF         ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Pointer_WID         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Pointer_MSK         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Pointer_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Pointer_MAX         (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Pointer_DEF         (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Pointer_HSH         (0x07004BBC)

  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Control_OFF         ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Control_WID         ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Control_MSK         (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Control_MIN         (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Control_MAX         (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Control_DEF         (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_9_Counter_Control_HSH         (0x02074BBC)

#define REUT_SUBCH_ERR_COUNTER_CTL_10_REG                          (0x00004BC0)

  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Pointer_OFF        ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Pointer_WID        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Pointer_MSK        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Pointer_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Pointer_MAX        (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Pointer_DEF        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Pointer_HSH        (0x07004BC0)

  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Control_OFF        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Control_WID        ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Control_MSK        (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Control_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Control_MAX        (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Control_DEF        (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_10_Counter_Control_HSH        (0x02074BC0)

#define REUT_SUBCH_ERR_COUNTER_CTL_11_REG                          (0x00004BC4)

  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Pointer_OFF        ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Pointer_WID        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Pointer_MSK        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Pointer_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Pointer_MAX        (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Pointer_DEF        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Pointer_HSH        (0x07004BC4)

  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Control_OFF        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Control_WID        ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Control_MSK        (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Control_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Control_MAX        (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Control_DEF        (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_11_Counter_Control_HSH        (0x02074BC4)

#define REUT_SUBCH_ERR_COUNTER_CTL_12_REG                          (0x00004BC8)

  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Pointer_OFF        ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Pointer_WID        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Pointer_MSK        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Pointer_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Pointer_MAX        (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Pointer_DEF        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Pointer_HSH        (0x07004BC8)

  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Control_OFF        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Control_WID        ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Control_MSK        (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Control_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Control_MAX        (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Control_DEF        (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_12_Counter_Control_HSH        (0x02074BC8)

#define REUT_SUBCH_ERR_COUNTER_CTL_13_REG                          (0x00004BCC)

  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Pointer_OFF        ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Pointer_WID        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Pointer_MSK        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Pointer_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Pointer_MAX        (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Pointer_DEF        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Pointer_HSH        (0x07004BCC)

  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Control_OFF        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Control_WID        ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Control_MSK        (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Control_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Control_MAX        (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Control_DEF        (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_13_Counter_Control_HSH        (0x02074BCC)

#define REUT_SUBCH_ERR_COUNTER_CTL_14_REG                          (0x00004BD0)

  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Pointer_OFF        ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Pointer_WID        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Pointer_MSK        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Pointer_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Pointer_MAX        (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Pointer_DEF        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Pointer_HSH        (0x07004BD0)

  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Control_OFF        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Control_WID        ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Control_MSK        (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Control_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Control_MAX        (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Control_DEF        (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_14_Counter_Control_HSH        (0x02074BD0)

#define REUT_SUBCH_ERR_COUNTER_CTL_15_REG                          (0x00004BD4)

  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Pointer_OFF        ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Pointer_WID        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Pointer_MSK        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Pointer_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Pointer_MAX        (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Pointer_DEF        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Pointer_HSH        (0x07004BD4)

  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Control_OFF        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Control_WID        ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Control_MSK        (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Control_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Control_MAX        (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Control_DEF        (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_15_Counter_Control_HSH        (0x02074BD4)

#define REUT_SUBCH_ERR_COUNTER_CTL_16_REG                          (0x00004BD8)

  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Pointer_OFF        ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Pointer_WID        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Pointer_MSK        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Pointer_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Pointer_MAX        (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Pointer_DEF        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Pointer_HSH        (0x07004BD8)

  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Control_OFF        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Control_WID        ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Control_MSK        (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Control_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Control_MAX        (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Control_DEF        (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_16_Counter_Control_HSH        (0x02074BD8)

#define REUT_SUBCH_ERR_COUNTER_CTL_17_REG                          (0x00004BDC)

  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Pointer_OFF        ( 0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Pointer_WID        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Pointer_MSK        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Pointer_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Pointer_MAX        (127) // 0x0000007F
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Pointer_DEF        (0x0000007F)
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Pointer_HSH        (0x07004BDC)

  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Control_OFF        ( 7)
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Control_WID        ( 2)
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Control_MSK        (0x00000180)
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Control_MIN        (0)
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Control_MAX        (3) // 0x00000003
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Control_DEF        (0x00000000)
  #define REUT_SUBCH_ERR_COUNTER_CTL_17_Counter_Control_HSH        (0x02074BDC)

//#define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_REG                          (0x00004E00)

  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_OFF     ( 0)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_WID     ( 6)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_MSK     (0x0000003F)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_MIN     (0)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_MAX     (63) // 0x0000003F
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_DEF     (0x00000000)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Rate_HSH     (0x06004E00)

  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_OFF    ( 6)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_WID    ( 1)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_MSK    (0x00000040)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_MIN    (0)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_MAX    (1) // 0x00000001
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_DEF    (0x00000000)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Increment_Scale_HSH    (0x01064E00)

  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_OFF      ( 8)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_WID      ( 6)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_MSK      (0x00003F00)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_MIN      (0)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_MAX      (63) // 0x0000003F
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_DEF      (0x00000000)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Start_Pointer_HSH      (0x06084E00)

  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_OFF        (16)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_WID        ( 6)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_MSK        (0x003F0000)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_MIN        (0)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_MAX        (63) // 0x0000003F
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_DEF        (0x0000003F)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_End_Pointer_HSH        (0x06104E00)

  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_OFF         (22)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_WID         ( 1)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_MSK         (0x00400000)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_MIN         (0)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_MAX         (1) // 0x00000001
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_DEF         (0x00000000)
  #define BC_CR_REUT_CH_PAT_WDB_CL_CTRL_WDB_Xor_Enable_HSH         (0x01164E00)

#define BIOS_POST_CODE_PCU_REG                                     (0x00005824)

  #define BIOS_POST_CODE_PCU_PostCode_OFF                          ( 0)
  #define BIOS_POST_CODE_PCU_PostCode_WID                          (32)
  #define BIOS_POST_CODE_PCU_PostCode_MSK                          (0xFFFFFFFF)
  #define BIOS_POST_CODE_PCU_PostCode_MIN                          (0)
  #define BIOS_POST_CODE_PCU_PostCode_MAX                          (4294967295) // 0xFFFFFFFF
  #define BIOS_POST_CODE_PCU_PostCode_DEF                          (0x00000000)
  #define BIOS_POST_CODE_PCU_PostCode_HSH                          (0x20005824)

#define BIOS_MAILBOX_DATA_PCU_REG                                  (0x00005DA0)

  #define BIOS_MAILBOX_DATA_PCU_DATA_OFF                           ( 0)
  #define BIOS_MAILBOX_DATA_PCU_DATA_WID                           (32)
  #define BIOS_MAILBOX_DATA_PCU_DATA_MSK                           (0xFFFFFFFF)
  #define BIOS_MAILBOX_DATA_PCU_DATA_MIN                           (0)
  #define BIOS_MAILBOX_DATA_PCU_DATA_MAX                           (4294967295) // 0xFFFFFFFF
  #define BIOS_MAILBOX_DATA_PCU_DATA_DEF                           (0x00000000)
  #define BIOS_MAILBOX_DATA_PCU_DATA_HSH                           (0x20005DA0)

#define BIOS_MAILBOX_INTERFACE_PCU_REG                             (0x00005DA4)

  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_OFF                   ( 0)
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_WID                   ( 8)
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_MSK                   (0x000000FF)
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_MIN                   (0)
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_MAX                   (255) // 0x000000FF
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_DEF                   (0x00000000)
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_HSH                   (0x08005DA4)

  #define BIOS_MAILBOX_INTERFACE_PCU_ADDR_OFF                      ( 8)
  #define BIOS_MAILBOX_INTERFACE_PCU_ADDR_WID                      (21)
  #define BIOS_MAILBOX_INTERFACE_PCU_ADDR_MSK                      (0x1FFFFF00)
  #define BIOS_MAILBOX_INTERFACE_PCU_ADDR_MIN                      (0)
  #define BIOS_MAILBOX_INTERFACE_PCU_ADDR_MAX                      (2097151) // 0x001FFFFF
  #define BIOS_MAILBOX_INTERFACE_PCU_ADDR_DEF                      (0x00000000)
  #define BIOS_MAILBOX_INTERFACE_PCU_ADDR_HSH                      (0x15085DA4)

  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_OFF                  (31)
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_WID                  ( 1)
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_MSK                  (0x80000000)
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_MIN                  (0)
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_MAX                  (1) // 0x00000001
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_DEF                  (0x00000000)
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_HSH                  (0x011F5DA4)

#pragma pack(pop)
#endif
