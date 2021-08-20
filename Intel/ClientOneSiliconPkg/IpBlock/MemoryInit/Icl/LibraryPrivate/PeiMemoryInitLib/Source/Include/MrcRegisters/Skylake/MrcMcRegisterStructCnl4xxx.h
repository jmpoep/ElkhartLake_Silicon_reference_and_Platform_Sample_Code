#ifndef __MrcMcRegisterStructCnl4xxx_h__
#define __MrcMcRegisterStructCnl4xxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

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

typedef union {
  struct {
    UINT32 WDB_Increment_Rate                      :  6;  // Bits 5:0
    UINT32 WDB_Increment_Scale                     :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WDB_Start_Pointer                       :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_End_Pointer                         :  6;  // Bits 21:16
    UINT32 WDB_Xor_Enable                          :  1;  // Bits 22:22
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Global_Start_Test                       :  1;  // Bits 0:0
    UINT32 Global_Stop_Test                        :  1;  // Bits 1:1
    UINT32 Global_Clear_Errors                     :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Global_Stop_Test_On_Any_Error           :  1;  // Bits 4:4
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_GLOBAL_CTL_STRUCT;

typedef union {
  struct {
    UINT32 Channel_Error_Status_0                  :  1;  // Bits 0:0
    UINT32 Channel_Error_Status_1                  :  1;  // Bits 1:1
    UINT32 Channel_Error_Status_2                  :  1;  // Bits 2:2
    UINT32 Channel_Error_Status_3                  :  1;  // Bits 3:3
    UINT32                                         :  12;  // Bits 15:4
    UINT32 Channel_Test_Done_Status_0              :  1;  // Bits 16:16
    UINT32 Channel_Test_Done_Status_1              :  1;  // Bits 17:17
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_GLOBAL_ERR_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_CTL_2_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_CTL_3_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_CTL_4_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_CTL_5_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_CTL_6_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_CTL_7_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_CTL_2_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_CTL_3_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_CTL_4_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_CTL_5_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_CTL_6_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_CTL_7_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_OFFSET_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_OFFSET_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_OFFSET_CTL_2_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_OFFSET_CTL_3_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_OFFSET_CTL_4_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_OFFSET_CTL_5_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_OFFSET_CTL_6_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH0_SUBSEQ_OFFSET_CTL_7_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_OFFSET_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_OFFSET_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_OFFSET_CTL_2_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_OFFSET_CTL_3_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_OFFSET_CTL_4_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_OFFSET_CTL_5_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_OFFSET_CTL_6_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32 allow_mirror_both_sub_ch_cadb           :  1;  // Bits 5:5
    UINT32 sub_ch_to_block                         :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  1;  // Bits 17:17
    UINT32 Deselect_CADB_Seeds_Save_Enable         :  1;  // Bits 18:18
    UINT32 Deselect_CADB_Seeds_Reload_Enable       :  1;  // Bits 19:19
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32 Row_Increment_Enable                    :  1;  // Bits 28:28
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 29:29
    UINT32 Cmd_Mirror_Mode                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH1_SUBSEQ_OFFSET_CTL_7_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Stop_Base_Sequence_On_Wrap_Trigger      :  1;  // Bits 3:3
    UINT32                                         :  1;  // Bits 4:4
    UINT32 Address_Update_Rate_Mode                :  1;  // Bits 5:5
    UINT32                                         :  3;  // Bits 8:6
    UINT32 REUT_AllowOpp_Refresh                   :  1;  // Bits 9:9
    UINT32                                         :  1;  // Bits 10:10
    UINT32 Global_Control                          :  1;  // Bits 11:11
    UINT32 Initialization_Mode                     :  2;  // Bits 13:12
    UINT32                                         :  10;  // Bits 23:14
    UINT32 Subsequence_Start_Pointer               :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Subsequence_End_Pointer                 :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Start_Test_Delay                        :  10;  // Bits 41:32
    UINT32                                         :  6;  // Bits 47:42
    UINT32 SubSequence_Cacheline_Counter_Mode      :  1;  // Bits 48:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_CFG_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Stop_Base_Sequence_On_Wrap_Trigger      :  1;  // Bits 3:3
    UINT32                                         :  1;  // Bits 4:4
    UINT32 Address_Update_Rate_Mode                :  1;  // Bits 5:5
    UINT32                                         :  3;  // Bits 8:6
    UINT32 REUT_AllowOpp_Refresh                   :  1;  // Bits 9:9
    UINT32                                         :  1;  // Bits 10:10
    UINT32 Global_Control                          :  1;  // Bits 11:11
    UINT32 Initialization_Mode                     :  2;  // Bits 13:12
    UINT32                                         :  10;  // Bits 23:14
    UINT32 Subsequence_Start_Pointer               :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Subsequence_End_Pointer                 :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Start_Test_Delay                        :  10;  // Bits 41:32
    UINT32                                         :  6;  // Bits 47:42
    UINT32 SubSequence_Cacheline_Counter_Mode      :  1;  // Bits 48:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_CFG_1_STRUCT;

typedef union {
  struct {
    UINT32 Local_Start_Test                        :  1;  // Bits 0:0
    UINT32 Local_Stop_Test                         :  1;  // Bits 1:1
    UINT32 Local_Clear_Errors                      :  1;  // Bits 2:2
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32 Local_Start_Test                        :  1;  // Bits 0:0
    UINT32 Local_Stop_Test                         :  1;  // Bits 1:1
    UINT32 Local_Clear_Errors                      :  1;  // Bits 2:2
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32 Current_Loopcount                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_LOOPCOUNT_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Current_Loopcount                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_LOOPCOUNT_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32 Current_Subsequence_Pointer             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_SUBSEQ_PNTR_0_STRUCT;

typedef union {
  struct {
    UINT32 Current_Subsequence_Pointer             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_SUBSEQ_PNTR_1_STRUCT;

typedef union {
  struct {
    UINT32 Current_Cacheline                       :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_CACHELINE_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Current_Cacheline                       :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_CACHELINE_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  19;  // Bits 47:29
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_BASE_ADDR_START_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  19;  // Bits 47:29
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_BASE_ADDR_START_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32 Row_Address                             :  18;  // Bits 29:12
    UINT32                                         :  18;  // Bits 47:30
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_BASE_ADDR_WRAP_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32 Row_Address                             :  18;  // Bits 29:12
    UINT32                                         :  18;  // Bits 47:30
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_BASE_ADDR_WRAP_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  19;  // Bits 47:29
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_BASE_ADDR_CURRENT_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  19;  // Bits 47:29
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_BASE_ADDR_CURRENT_1_STRUCT;

typedef union {
  struct {
    UINT32 Base_Column_Address_Order               :  2;  // Bits 1:0
    UINT32 Base_Row_Address_Order                  :  2;  // Bits 3:2
    UINT32 Base_Bank_Address_Order                 :  2;  // Bits 5:4
    UINT32 Base_Rank_Address_Order                 :  2;  // Bits 7:6
    UINT32                                         :  5;  // Bits 12:8
    UINT32 Base_Address_Invert_Rate                :  3;  // Bits 15:13
    UINT32                                         :  4;  // Bits 19:16
    UINT32 Column_Base_Address_Invert_Enable       :  1;  // Bits 20:20
    UINT32 Row_Base_Address_Invert_Enable          :  1;  // Bits 21:21
    UINT32 Bank_Base_Address_Invert_Enable         :  1;  // Bits 22:22
    UINT32 Rank_Base_Address_Invert_Enable         :  1;  // Bits 23:23
    UINT32 Column_Base_Wrap_Trigger_Enable         :  1;  // Bits 24:24
    UINT32 Row_Base_Wrap_Trigger_Enable            :  1;  // Bits 25:25
    UINT32 Bank_Base_Wrap_Trigger_Enable           :  1;  // Bits 26:26
    UINT32 Rank_Base_Wrap_Trigger_Enable           :  1;  // Bits 27:27
    UINT32 Column_Base_Wrap_Carry_Enable           :  1;  // Bits 28:28
    UINT32 Row_Base_Wrap_Carry_Enable              :  1;  // Bits 29:29
    UINT32 Bank_Base_Wrap_Carry_Enable             :  1;  // Bits 30:30
    UINT32 Rank_Base_Wrap_Carry_Enable             :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32 Base_Column_Address_Order               :  2;  // Bits 1:0
    UINT32 Base_Row_Address_Order                  :  2;  // Bits 3:2
    UINT32 Base_Bank_Address_Order                 :  2;  // Bits 5:4
    UINT32 Base_Rank_Address_Order                 :  2;  // Bits 7:6
    UINT32                                         :  5;  // Bits 12:8
    UINT32 Base_Address_Invert_Rate                :  3;  // Bits 15:13
    UINT32                                         :  4;  // Bits 19:16
    UINT32 Column_Base_Address_Invert_Enable       :  1;  // Bits 20:20
    UINT32 Row_Base_Address_Invert_Enable          :  1;  // Bits 21:21
    UINT32 Bank_Base_Address_Invert_Enable         :  1;  // Bits 22:22
    UINT32 Rank_Base_Address_Invert_Enable         :  1;  // Bits 23:23
    UINT32 Column_Base_Wrap_Trigger_Enable         :  1;  // Bits 24:24
    UINT32 Row_Base_Wrap_Trigger_Enable            :  1;  // Bits 25:25
    UINT32 Bank_Base_Wrap_Trigger_Enable           :  1;  // Bits 26:26
    UINT32 Rank_Base_Wrap_Trigger_Enable           :  1;  // Bits 27:27
    UINT32 Column_Base_Wrap_Carry_Enable           :  1;  // Bits 28:28
    UINT32 Row_Base_Wrap_Carry_Enable              :  1;  // Bits 29:29
    UINT32 Bank_Base_Wrap_Carry_Enable             :  1;  // Bits 30:30
    UINT32 Rank_Base_Wrap_Carry_Enable             :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Base_Address_Increment           :  9;  // Bits 11:3
    UINT32 Column_Base_Address_Update_Rate         :  5;  // Bits 16:12
    UINT32                                         :  2;  // Bits 18:17
    UINT32 Column_Base_Address_Update_Scale        :  1;  // Bits 19:19
    UINT32 Row_Base_Address_Increment              :  12;  // Bits 31:20
    UINT32 Row_Base_Address_Update_Rate            :  4;  // Bits 35:32
    UINT32                                         :  1;  // Bits 36:36
    UINT32 Row_Base_Address_Update_Scale           :  1;  // Bits 37:37
    UINT32 Bank_Base_Address_Increment             :  5;  // Bits 42:38 5th bit is for B0+
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Bank_Base_Address_Update_Rate           :  5;  // Bits 48:44
    UINT32                                         :  2;  // Bits 50:49
    UINT32 Bank_Base_Address_Update_Scale          :  1;  // Bits 51:51
    UINT32 Rank_Base_Address_Increment             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank_Base_Address_Update_Rate           :  5;  // Bits 60:56
    UINT32                                         :  2;  // Bits 62:61
    UINT32 Rank_Base_Address_Update_Scale          :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Base_Address_Increment           :  9;  // Bits 11:3
    UINT32 Column_Base_Address_Update_Rate         :  5;  // Bits 16:12
    UINT32                                         :  2;  // Bits 18:17
    UINT32 Column_Base_Address_Update_Scale        :  1;  // Bits 19:19
    UINT32 Row_Base_Address_Increment              :  12;  // Bits 31:20
    UINT32 Row_Base_Address_Update_Rate            :  4;  // Bits 35:32
    UINT32                                         :  1;  // Bits 36:36
    UINT32 Row_Base_Address_Update_Scale           :  1;  // Bits 37:37
    UINT32 Bank_Base_Address_Increment             :  5;  // Bits 42:38 5th bit is for B0+
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Bank_Base_Address_Update_Rate           :  5;  // Bits 48:44
    UINT32                                         :  2;  // Bits 50:49
    UINT32 Bank_Base_Address_Update_Scale          :  1;  // Bits 51:51
    UINT32 Rank_Base_Address_Increment             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank_Base_Address_Update_Rate           :  5;  // Bits 60:56
    UINT32                                         :  2;  // Bits 62:61
    UINT32 Rank_Base_Address_Update_Scale          :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_OFFSET_ADDR_CURRENT_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_OFFSET_ADDR_CURRENT_1_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Row0_Swizzle        :  5;  // Bits 4:0
    UINT32 Logical_to_Physical_Row1_Swizzle        :  5;  // Bits 9:5
    UINT32 Logical_to_Physical_Row2_Swizzle        :  5;  // Bits 14:10
    UINT32 Logical_to_Physical_Row3_Swizzle        :  5;  // Bits 19:15
    UINT32 Logical_to_Physical_Row4_Swizzle        :  5;  // Bits 24:20
    UINT32 Logical_to_Physical_Row5_Swizzle        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_0_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Row0_Swizzle        :  5;  // Bits 4:0
    UINT32 Logical_to_Physical_Row1_Swizzle        :  5;  // Bits 9:5
    UINT32 Logical_to_Physical_Row2_Swizzle        :  5;  // Bits 14:10
    UINT32 Logical_to_Physical_Row3_Swizzle        :  5;  // Bits 19:15
    UINT32 Logical_to_Physical_Row4_Swizzle        :  5;  // Bits 24:20
    UINT32 Logical_to_Physical_Row5_Swizzle        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_1_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Row6_Swizzle        :  5;  // Bits 4:0
    UINT32 Logical_to_Physical_Row7_Swizzle        :  5;  // Bits 9:5
    UINT32 Logical_to_Physical_Row8_Swizzle        :  5;  // Bits 14:10
    UINT32 Logical_to_Physical_Row9_Swizzle        :  5;  // Bits 19:15
    UINT32 Logical_to_Physical_Row10_Swizzle       :  5;  // Bits 24:20
    UINT32 Logical_to_Physical_Row11_Swizzle       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
    UINT32 Logical_to_Physical_Row12_Swizzle       :  5;  // Bits 36:32
    UINT32 Logical_to_Physical_Row13_Swizzle       :  5;  // Bits 41:37
    UINT32 Logical_to_Physical_Row14_Swizzle       :  5;  // Bits 46:42
    UINT32 Logical_to_Physical_Row15_Swizzle       :  5;  // Bits 51:47
    UINT32 Logical_to_Physical_Row16_Swizzle       :  5;  // Bits 56:52
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_0_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Row6_Swizzle        :  5;  // Bits 4:0
    UINT32 Logical_to_Physical_Row7_Swizzle        :  5;  // Bits 9:5
    UINT32 Logical_to_Physical_Row8_Swizzle        :  5;  // Bits 14:10
    UINT32 Logical_to_Physical_Row9_Swizzle        :  5;  // Bits 19:15
    UINT32 Logical_to_Physical_Row10_Swizzle       :  5;  // Bits 24:20
    UINT32 Logical_to_Physical_Row11_Swizzle       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
    UINT32 Logical_to_Physical_Row12_Swizzle       :  5;  // Bits 36:32
    UINT32 Logical_to_Physical_Row13_Swizzle       :  5;  // Bits 41:37
    UINT32 Logical_to_Physical_Row14_Swizzle       :  5;  // Bits 46:42
    UINT32 Logical_to_Physical_Row15_Swizzle       :  5;  // Bits 51:47
    UINT32 Logical_to_Physical_Row16_Swizzle       :  5;  // Bits 56:52
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_1_STRUCT;

typedef union {
  struct {
    UINT32 Trigger_In_Global_Start                 :  1;  // Bits 0:0
    UINT32 Trigger_Out_Global_Start                :  1;  // Bits 1:1
    UINT32                                         :  5;  // Bits 6:2
    UINT32 Trigger_Out_On_Error_0                  :  1;  // Bits 7:7
    UINT32 Trigger_Out_On_Error_1                  :  1;  // Bits 8:8
    UINT32                                         :  6;  // Bits 14:9
    UINT32 Trigger_Out_On_Channel_Test_Done_Status_0:  1;  // Bits 15:15
    UINT32 Trigger_Out_On_Channel_Test_Done_Status_1:  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_ERR_TRIGGER_CTL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  19;  // Bits 47:29
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_BASE_ADDR_SAVE_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  19;  // Bits 47:29
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_CH_SEQ_BASE_ADDR_SAVE_1_STRUCT;

typedef union {
  struct {
    UINT32 Loopcount_Limit                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_LOOPCOUNT_LIMIT_0_STRUCT;

typedef union {
  struct {
    UINT32 Loopcount_Limit                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_LOOPCOUNT_LIMIT_1_STRUCT;

typedef union {
  struct {
    UINT32 Col_Enable                              :  9;  // Bits 8:0
    UINT32 Row_Enable                              :  17;  // Bits 25:9
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_ADDR_ENABLE_0_STRUCT;

typedef union {
  struct {
    UINT32 Col_Enable                              :  9;  // Bits 8:0
    UINT32 Row_Enable                              :  17;  // Bits 25:9
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_SEQ_ADDR_ENABLE_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Generator_Id                    :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 Pattern_Buffer_Entry                    :  3;  // Bits 10:8
    UINT32 ECC_Data_Source_Sel                     :  2;  // Bits 12:11
    UINT32 ECC_Replace_Byte_Control                :  2;  // Bits 14:13
    UINT32 SubSequence_Count_To_Shift              :  5;  // Bits 19:15
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_ID_PATTERN_BUFFER_CTL_STRUCT;

typedef union {
  struct {
    UINT32 Mux0_Control                            :  2;  // Bits 1:0
    UINT32                                         :  1;  // Bits 2:2
    UINT32 Mux1_Control                            :  2;  // Bits 4:3
    UINT32                                         :  1;  // Bits 5:5
    UINT32 Mux2_Control                            :  2;  // Bits 7:6
    UINT32 LFSR_Type_0                             :  3;  // Bits 10:8
    UINT32 spare                                   :  5;  // Bits 15:11
    UINT32 Save_LFSR_Seed_Rate                     :  8;  // Bits 23:16
    UINT32 Reload_LFSR_Seed_Rate                   :  5;  // Bits 28:24
    UINT32 Shift_Array_Enabled                     :  1;  // Bits 29:29
    UINT32                                         :  1;  // Bits 30:30
    UINT32 Reload_Save_LFSR_Seed_Rate_Mode         :  1;  // Bits 31:31
    UINT32 LFSR_Type_1                             :  3;  // Bits 34:32
    UINT32 LFSR_Type_2                             :  3;  // Bits 37:35
    UINT32 CMD_TYPE_TO_COUNT_CL                    :  1;  // Bits 38:38
  } A0Bits;
  struct {
    UINT32 Mux0_Control                            :  2;  // Bits 1:0
    UINT32                                         :  1;  // Bits 2:2
    UINT32 Mux1_Control                            :  2;  // Bits 4:3
    UINT32                                         :  1;  // Bits 5:5
    UINT32 Mux2_Control                            :  2;  // Bits 7:6
    UINT32 LFSR_Type_0                             :  4;  // Bits 11:8
    UINT32 spare                                   :  4;  // Bits 15:12
    UINT32 Save_LFSR_Seed_Rate                     :  8;  // Bits 23:16
    UINT32 Reload_LFSR_Seed_Rate                   :  5;  // Bits 28:24
    UINT32 Shift_Array_Enabled                     :  1;  // Bits 29:29
    UINT32                                         :  1;  // Bits 30:30
    UINT32 Reload_Save_LFSR_Seed_Rate_Mode         :  1;  // Bits 31:31
    UINT32 LFSR_Type_1                             :  4;  // Bits 35:32
    UINT32 LFSR_Type_2                             :  4;  // Bits 39:36
    UINT32 CMD_TYPE_TO_COUNT_CL                    :  1;  // Bits 40:40
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_PG_PAT_CL_MUX_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_WR_PB_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_WR_PB_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_WR_PB_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_WR_PB_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_WR_PB_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_WR_PB_STATUS_2_STRUCT;

typedef union {
  struct {
    UINT32 L_data_select                           :  1;  // Bits 0:0
    UINT32 Enable_Sweep_Frequency                  :  1;  // Bits 1:1
    UINT32                                         :  6;  // Bits 7:2
    UINT32 L_counter                               :  8;  // Bits 15:8
    UINT32 M_counter                               :  8;  // Bits 23:16
    UINT32 N_counter                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_LMN_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Inv_or_DC_Enable                    :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 Inv_or_DC_Shift_Rate                    :  4;  // Bits 19:16
    UINT32 DC_Polarity_Control                     :  1;  // Bits 20:20
    UINT32                                         :  9;  // Bits 29:21
    UINT32 Inv_or_DC_Control                       :  1;  // Bits 30:30
    UINT32 Inv_or_DC_Shift_Enable                  :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_INV_STRUCT;

typedef union {
  struct {
    UINT32 Data_Inv_or_DC_Enable                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_DATA_INV_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer_DataLow                  :  32;  // Bits 31:0
    UINT32 Pattern_Buffer_DataHigh                 :  5;  // Bits 36:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_PG_PATTERN_BUFFER_SHADOW_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_RD_PB_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_RD_PB_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_RD_PB_STATUS_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_RD_PB_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_RD_PB_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_MUX_RD_PB_2_STRUCT;

typedef union {
  struct {
    UINT32 Cl_Counter_For_Shift                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_PG_PAT_CL_COUNTER_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Chunk_Error_Status                      :  16;  // Bits 15:0
    UINT32 Rank_Error_Status                       :  4;  // Bits 19:16
    UINT32 Alert_Error_Status                      :  1;  // Bits 20:20
    UINT32 Byte_Group_Error_Status                 :  4;  // Bits 24:21
    UINT32 ECC_Byte_Group_Error_Status             :  1;  // Bits 25:25
    UINT32 WDB_Rd_Chunk_Num_Status                 :  4;  // Bits 29:26
    UINT32                                         :  2;  // Bits 31:30
    UINT32 ECC_Error_Status                        :  8;  // Bits 39:32
    UINT32 Nth_Error                               :  23;  // Bits 62:40
    UINT32 Nth_Error_Overflow                      :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Chunk_Error_Status                      :  16;  // Bits 15:0
    UINT32 Rank_Error_Status                       :  4;  // Bits 19:16
    UINT32 Alert_Error_Status                      :  1;  // Bits 20:20
    UINT32 Byte_Group_Error_Status                 :  4;  // Bits 24:21
    UINT32 ECC_Byte_Group_Error_Status             :  1;  // Bits 25:25
    UINT32 WDB_Rd_Chunk_Num_Status                 :  4;  // Bits 29:26
    UINT32                                         :  2;  // Bits 31:30
    UINT32 ECC_Error_Status                        :  8;  // Bits 39:32
    UINT32 Nth_Error                               :  23;  // Bits 62:40
    UINT32 Nth_Error_Overflow                      :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32 Chunk_Error_Status                      :  16;  // Bits 15:0
    UINT32 Rank_Error_Status                       :  4;  // Bits 19:16
    UINT32 Alert_Error_Status                      :  1;  // Bits 20:20
    UINT32 Byte_Group_Error_Status                 :  4;  // Bits 24:21
    UINT32 ECC_Byte_Group_Error_Status             :  1;  // Bits 25:25
    UINT32 WDB_Rd_Chunk_Num_Status                 :  4;  // Bits 29:26
    UINT32                                         :  2;  // Bits 31:30
    UINT32 ECC_Error_Status                        :  8;  // Bits 39:32
    UINT32 Nth_Error                               :  23;  // Bits 62:40
    UINT32 Nth_Error_Overflow                      :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_2_STRUCT;

typedef union {
  struct {
    UINT32 Chunk_Error_Status                      :  16;  // Bits 15:0
    UINT32 Rank_Error_Status                       :  4;  // Bits 19:16
    UINT32 Alert_Error_Status                      :  1;  // Bits 20:20
    UINT32 Byte_Group_Error_Status                 :  4;  // Bits 24:21
    UINT32 ECC_Byte_Group_Error_Status             :  1;  // Bits 25:25
    UINT32 WDB_Rd_Chunk_Num_Status                 :  4;  // Bits 29:26
    UINT32                                         :  2;  // Bits 31:30
    UINT32 ECC_Error_Status                        :  8;  // Bits 39:32
    UINT32 Nth_Error                               :  23;  // Bits 62:40
    UINT32 Nth_Error_Overflow                      :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_SUBCH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_3_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_Mask                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_DATA_MASK_0_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_Mask                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_DATA_MASK_1_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_Mask                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_DATA_MASK_2_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_Mask                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_DATA_MASK_3_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Error_Mask                          :  8;  // Bits 7:0
    UINT32 Stop_on_CA_ALERT                        :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_ERR_ECC_MASK_0_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Error_Mask                          :  8;  // Bits 7:0
    UINT32 Stop_on_CA_ALERT                        :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_ERR_ECC_MASK_1_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_Status                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_DATA_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_Status                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_DATA_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_Status                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_DATA_STATUS_2_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_Status                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_DATA_STATUS_3_STRUCT;

typedef union {
  struct {
    UINT32 Column_Address                          :  12;  // Bits 11:0
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  19;  // Bits 47:29
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th Bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  2;  // Bits 57:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_SUBCH_ERROR_ADDR_0_STRUCT;

typedef union {
  struct {
    UINT32 Column_Address                          :  12;  // Bits 11:0
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  19;  // Bits 47:29
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th Bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  2;  // Bits 57:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_SUBCH_ERROR_ADDR_1_STRUCT;

typedef union {
  struct {
    UINT32 Column_Address                          :  12;  // Bits 11:0
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  19;  // Bits 47:29
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th Bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  2;  // Bits 57:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_SUBCH_ERROR_ADDR_2_STRUCT;

typedef union {
  struct {
    UINT32 Column_Address                          :  12;  // Bits 11:0
    UINT32 Row_Address                             :  17;  // Bits 28:12
    UINT32                                         :  19;  // Bits 47:29
    UINT32 Bank_Address                            :  5;  // Bits 52:48 5th Bit is for B0+
    UINT32                                         :  3;  // Bits 55:53
    UINT32 Rank_Address                            :  2;  // Bits 57:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} REUT_SUBCH_ERROR_ADDR_3_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Overflow_Status                 :  9;  // Bits 8:0
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Overflow_Status                 :  9;  // Bits 8:0
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32 Write_Address_as_Data                   :  1;  // Bits 0:0
    UINT32 Read_Address_as_Data                    :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_0_STRUCT;

typedef union {
  struct {
    UINT32 Write_Address_as_Data                   :  1;  // Bits 0:0
    UINT32 Read_Address_as_Data                    :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_CH_PAT_ADDRESS_AS_DATA_CTRL_1_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_2_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_3_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_4_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_5_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_6_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_7_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_8_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_9_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_10_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_11_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_12_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_13_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_14_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_15_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_16_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_STATUS_17_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_2_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_3_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_4_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_5_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_6_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_7_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_8_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_9_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_10_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_11_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_12_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_13_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_14_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_15_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_16_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REUT_SUBCH_ERR_COUNTER_CTL_17_STRUCT;

typedef union {
  struct {
    UINT32 WDB_Increment_Rate                      :  6;  // Bits 5:0
    UINT32 WDB_Increment_Scale                     :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WDB_Start_Pointer                       :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_End_Pointer                         :  6;  // Bits 21:16
    UINT32 WDB_Xor_Enable                          :  1;  // Bits 22:22
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT;

#pragma pack(pop)
#endif
